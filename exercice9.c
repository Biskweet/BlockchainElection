#include "exercice9.h"


void submit_vote(Protected* p) {
    FILE* f = fopen("pending_votes.txt", "a");
    if (f == NULL) {
        printerror("Erreur lors de l'ouverture du fichier (submit_votes).\n"); return;
    }

    char* pr_str = protected_to_str(p); 
    fprintf(f, "%s\n", pr_str);
    free(pr_str);

    fclose(f);
}


void create_block(CellTree* tree, Key* author, int d)  {
    CellProtected* votes = read_protected("pending_votes.txt");
    remove("pending_votes.txt");

    Block* block = (Block*) malloc(sizeof(Block));
    if (block == NULL) {
        printerror("Erreur d'allocation (create_block).\n"); return;
    }

    block->author = author;
    block->votes = votes;
    block->nonce = 0;

    CellTree* node = last_node(tree);

    if (node != NULL) block->previous_hash = (unsigned char*) strdup((char*) node->block->hash);
    else block->previous_hash = NULL;

    // Hashing a first time
    unsigned char* block_str = (unsigned char*) block_to_str(block);
    block->hash = hash_str(block_str);
    free(block_str);

    compute_proof_of_work(block, d);

    write_block("pending_block.txt", block);

    while (votes != NULL) {
        liberer_protected(votes->data);
        votes = votes->next;
    }
    delete_block(block);  // Might break
}


void add_block(int d, char* name) {
    Block* block = read_block("pending_block.txt");

    if (block == NULL) return;

    if (verify_block(block, d)) {
        char filepath[128];
        sprintf(filepath, "./blockchain/%s", name);
        write_block(filepath, block);
    }

    delete_block(block);
    remove("pending_block.txt");
}


CellTree* read_tree() {
    DIR* rep = opendir("./blockchain/");
    struct dirent* dir;

    int file_no = 0, i = 0;

    if (rep != NULL) {
        // Counting all files
        while ((dir = readdir(rep))) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                file_no++;
            }
        }
    } else return NULL;

    CellTree* node_arr[file_no];

    rewinddir(rep);
    chdir("./blockchain/");          // Moving to the correct directory
    while ((dir = readdir(rep))) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            Block* block = read_block(dir->d_name);
            node_arr[i] = create_node(block);  // Will break
            i++;
        }
    }

    closedir(rep);
    chdir("..");

    for (i = 0; i < file_no; i++) {
        for (int j = 0; j < file_no; j++) {
            if (i == j) continue;  // Do not compare with self

            if ((node_arr[j]->block->previous_hash) && (strcmp((char*)node_arr[i]->block->hash, (char*)node_arr[j]->block->previous_hash) == 0)) {
                add_child(node_arr[i], node_arr[j]);
            }
        }
    }

    CellTree* root = NULL;
    for (int i = 0; i < file_no; i++) {
        if (node_arr[i]->father == NULL) root = node_arr[i];
    }

    // for (i = 0; i < file_no; i++) {
    //     delete_node(node_arr[i]);
    // }

    if (root == NULL) printerror("Returning NULL in read_tree.\n");
    return root;
}


Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) {
    CellProtected* votes = get_trusted_votes(tree);
    supprimer_invalides(&votes);

    print_list_pr(votes);

    Key* winner = compute_winner(votes, candidates, voters, sizeC, sizeV);
    delete_list_protected(votes);

    return winner;
}


CellKey* give_random_cellkey(CellKey* keys, int size) {
    int number = rand() % size;

    while (number-- != 0) {
        keys = keys->next;
    }

    return keys;
}


void free_all_protected_in_tree(CellTree* tree) {
    while (tree != NULL) {
        CellProtected* vote_copy = tree->block->votes;

        while (vote_copy != NULL) {
            liberer_protected(vote_copy->data);
            vote_copy = vote_copy->next;
        }

        tree = tree->firstChild;
    }
}

void free_all_authors_in_tree(CellTree* tree) {
    while (tree != NULL) {        
        free(tree->block->author);
        tree = tree->firstChild;
    }
}
