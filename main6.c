#include "exercice6.h"
#define NBVOTERS 600
#define NBCANDIDATES 10


int main(int argc, char const *argv[]) {
    printf("Running election with %d voters and %d candidates.\n", NBVOTERS, NBCANDIDATES);

    generate_random_data(NBVOTERS, NBCANDIDATES);

    CellProtected* declarations = read_protected("declarations.txt");
    CellKey* voters = read_public_keys("keys.txt");
    CellKey* candidates = read_public_keys("candidates.txt");

    supprimer_invalides(&declarations);

    Key* winner = compute_winner(declarations, candidates, voters, NBCANDIDATES, NBVOTERS);

    if (winner != NULL) {
        printf("Winner: (%lx, %lx)\n", winner->val, winner->n);
        free(winner);
    }

    delete_list_protected(declarations);
    delete_list_keys(voters);
    delete_list_keys(candidates);

    return 0;
}
