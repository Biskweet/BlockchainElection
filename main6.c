#include "exercice6.h"
#define NBVOTERS 5000
#define NBCANDIDATES 10


int main(int argc, char const *argv[]) {
    generate_random_data(NBVOTERS, NBVOTERS);

    CellProtected* declarations = read_protected("declarations.txt");
    CellKey* voters = read_public_keys("keys.txt");
    CellKey* candidates = read_public_keys("candidates.txt");

    supprimer_invalides(&declarations);

    Key* winner = compute_winner(declarations, candidates, voters, NBCANDIDATES, NBVOTERS);

    delete_list_keys(voters);
    delete_list_protected(declarations);

    return 0;
}
