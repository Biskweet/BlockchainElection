#include "exercice9.h"
#define NBVOTERS 1000
#define NBCANDIDATES 5


int main(int argc, char const *argv[]) {
    srand(time(NULL));

    system("rm -f ./blockchain/*");

    printf("Generating random data... "); fflush(stdout);
    generate_random_data(NBVOTERS, NBCANDIDATES);
    printf("done.\n");

    printf("Reading files... "); fflush(stdout);
    CellProtected* votes = read_protected("declarations.txt");
    CellKey* keys = read_public_keys("keys.txt");
    CellKey* candidates = read_public_keys("candidates.txt");
    printf("done.\n");

    CellProtected* votes_copy = votes;
    CellTree* tree = NULL;

    int count = 0, file_number = 0;
    char file_name[16];

    printf("Building tree... "); fflush(stdout);
    while (votes != NULL) {
        submit_vote(votes->data);

        count++;
        if (count == 10) {
            create_block(tree, give_random_cellkey(keys, NBVOTERS)->data, NO_ZEROS);

            file_number++;
            sprintf(file_name, "block_%d.txt", file_number);
            add_block(NO_ZEROS, file_name);

            count = 0;

            free_all_protected_in_tree(tree);
            free_all_authors_in_tree(tree);
            delete_tree(tree);

            tree = read_tree();
        }

        votes = votes->next;
    }

    // If some votes have not been block'd yet (if NBVOTERS % 10 != 0)
    if (count != 0) {
        create_block(tree, give_random_cellkey(keys, NBVOTERS)->data, NO_ZEROS);

        file_number++;
        sprintf(file_name, "block_%d.txt", file_number);
        add_block(NO_ZEROS, file_name);

        free_all_protected_in_tree(tree);
        free_all_authors_in_tree(tree);
        delete_tree(tree);

        tree = read_tree();
    }
    printf("done.\n");

    int should_print;
    printf("\nPrint tree ? (0: No, 1: Yes) ");
    scanf(" %d", &should_print);
    if (should_print) print_tree(tree);

    printf("\n");

    Key* winner = compute_winner_BT(tree, candidates, keys, NBCANDIDATES, NBVOTERS);

    if (winner != NULL) {
        printf("Winner: (%lx, %lx)\n", winner->val, winner->n);
        free(winner);
    }

    // Freeing tree
    free_all_authors_in_tree(tree);
    free_all_protected_in_tree(tree);
    delete_tree(tree);

    // Freeing voters, candidates and votes 
    delete_list_protected(votes_copy);
    delete_list_keys(keys);
    delete_list_keys(candidates);
    
    return 0;
}
