#include "exercice9.h"
#define NBVOTERS 20
#define NBCANDIDATES 1


int main(int argc, char const *argv[]) {
    srand(time(NULL));

    system("rm -f ./blockchain/*");
    generate_random_data(NBVOTERS, NBCANDIDATES);

    CellProtected* votes = read_protected("declarations.txt");
    CellKey* keys = read_public_keys("keys.txt");
    CellKey* candidates = read_public_keys("candidates.txt");

    CellProtected* votes_copy = votes;
    CellTree* tree = NULL;

    votes_copy = votes;
    int count = 0, file_number = 0;
    char file_name[16];

    while (votes_copy != NULL) {
        submit_vote(votes_copy->data);

        count++;
        if (count == 10) {
            create_block(tree, give_random_cellkey(keys, NBVOTERS)->data, NO_ZEROS);

            file_number++;
            sprintf(file_name, "block_%d", file_number);
            add_block(NO_ZEROS, file_name);

            count = 0;

            free_all_protected_in_tree(tree);
            delete_tree(tree);

            tree = read_tree();
        }

        votes_copy = votes_copy->next;
    }

    // If some votes have not been block'd yet (if NBVOTERS % 10 != 0)
    if (count != 0) {
        create_block(tree, give_random_cellkey(keys, NBVOTERS)->data, NO_ZEROS);

        file_number++;
        sprintf(file_name, "block_%d", file_number);
        add_block(NO_ZEROS, file_name);

        free_all_protected_in_tree(tree);
        delete_tree(tree);

        tree = read_tree();
    }


    print_tree(tree);
    printf("\n");

    Key* winner = compute_winner_BT(tree, candidates, keys, NBCANDIDATES, NBVOTERS);
    if (winner != NULL) {
        printf("Winner: (%lx, %lx)\n", winner->val, winner->n);
        free(winner);
    }

    // free_all_protected_in_tree(tree);
    delete_tree(tree);
    delete_list_protected(votes);
    delete_list_keys(keys);
    delete_list_keys(candidates);

    return 0;
}
