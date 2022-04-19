#include "exercice9.h"


void submit_vote(Protected *p){
    FILE * f = fopen("pending_votes.txt","a");

    if (f == NULL){
        printf("Erreur lors de l'ouverture du fichier dans submit_vote\n");
        return;
    }

    char * s = protected_to_str(p);
    fprintf(f,"%s\n", s);

    free(s);
    fclose(f);
}

void create_block(CellTree* tree, Key* author, int d){
    Block * b =  (Block *)malloc(sizeof(Block));

    if (b == NULL){
        printf("Erreur lors de l'allocation dans create_block\n");
        return;
    }

    CellProtected* c = read_protected("pending_votes.txt");
    remove("pending_votes.txt");

    b->votes = c;
    b->author = author;
    b->nonce = 0;

    CellTree * previous = last_node(tree);

    if (previous == NULL){
        b->previous_hash = NULL;
    }
    else{
        b->previous_hash = (unsigned char*)strdup((char*)previous->block->hash);
    }

    char * s = block_to_str(b);
    b->hash = hash_str((unsigned char*) s);

    compute_proof_of_work(b,d);

    write_block("pending_block.txt", b);

    while (c != NULL){
        liberer_protected(c->data);
        c = c->next;
    }
    delete_block(b);
    free(s);
}

void add_block(int d, char* name){
    Block *b = read_block("pending_block.txt");

    if (b == NULL) return;

    if (verify_block(b,d)==1){
        char * s = (char *)malloc(sizeof(char)*156);
        sprintf(s, "blockchain/%s",name);
        write_block(s, b);
        free(s);
    }


    remove("pending_block.txt");
}

CellTree * read_tree(){

    DIR * rep = opendir("./blockchain/");
    if (rep == NULL){
        printf("Erreur lors de l'ouverture du répertoire dans read_tree\n");
        return NULL;
    }

    struct dirent * dir;
    int cmp = 0;

    while((dir = readdir(rep))){
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
            cmp++;
        }
    }

    rewinddir(rep);
    CellTree* t[cmp];

    for (int i = 0; i < cmp; i++){
        t[i] = NULL;
    }

    Block * b;
    char path[100];
    CellTree* c;
    int i = 0;
    while ((dir = readdir(rep))){
        sprintf(path, "./blockchain/");
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..")!= 0){
            strcat(path, dir->d_name);
            b = read_block(path);
            c = create_node(b);
            for (int j = 0; j < i; j++){
                if (t[j]->block->hash != NULL && c->block->previous_hash != NULL){
                    if (strcmp((char*)t[j]->block->hash,(char*)c->block->previous_hash)==0){
                        c->father = t[j];
                    }
                }
            }
            t[i] = c;
            i++;
        }
    }

    closedir(rep);
    unsigned char * hash;

    for (int j = 0; j < cmp ; j++){
        hash = t[j]->block->hash;
        for (int k = 0; k < cmp; k++){
            if ((t[k]->block->previous_hash != NULL) && (strcmp((char*)t[k]->block->previous_hash, (char*)hash) == 0)){
                add_child(t[j], t[k]);
            }
        }
    }

    for (int j = 0; j < cmp; j++){
        if (t[j]->father == NULL){
            return t[j];
        }
    }

    //Cas où il n'y a pas de racine
    return NULL;
}

Key * compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){

    CellProtected * fusion = get_trusted_votes(tree);
    supprimer_invalides(&fusion);
    Key * winner = compute_winner(fusion, candidates, voters, sizeC, sizeV);

    delete_list_protected(fusion);

    return winner;

}

