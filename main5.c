#include "exercice6.h"


int main(int argc, char const *argv[]) {
    
    CellKey* keys = read_public_keys("keys.txt");
    print_list_keys(keys);

    printf("Liste CellProtected :\n");
    CellProtected* declarations = read_protected("declarations.txt");
    print_list_pr(declarations);

    supprimer_invalides(&declarations);

    printf("Après correction :\n");
    print_list_pr(declarations);

    delete_list_keys(keys);
    delete_list_protected(declarations);
    return 0;
}
