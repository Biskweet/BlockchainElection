#include "exercice9.h"
#define SIZE_V 50
#define SIZE_C 5
#define D 2

int main(){
    srand(time(NULL));
    system("rm ./blockchain/* -f");
    
    generate_random_data(SIZE_V,SIZE_C);

    CellProtected * declarations = read_protected("declarations.txt");
    CellKey * voters = read_public_keys("keys.txt");
    CellKey * candidates = read_public_keys("candidates.txt");
    CellProtected * temp = declarations;
    CellTree *t = NULL;
    CellTree *temp2 = NULL;
    CellProtected* temp3 = NULL;
    int j = 1;

    while (temp != NULL){
        for (int i = 0; i < 10; i++){
            submit_vote(temp->data);
            temp = temp->next;
            if (temp == NULL){
                i = 10;
            }
        }
        create_block(t,voters->data,D);
        char * name = (char*)malloc(sizeof(char)*100);
        sprintf(name, "Block_%d",j);
        j++;
        add_block(D, name);
        free(name);
        temp2 = t;
        while (temp2 != NULL){
            temp3 = temp2->block->votes;
            while (temp3 != NULL){
                liberer_protected(temp3->data);
                temp3 = temp3->next;
            }
            temp2 = temp2->firstChild;
        }
        delete_tree(t);
        t = read_tree();
    }

    printf("1\n");

    printf("Arbre final : \n");
    print_tree(t);

    Key * winner = compute_winner_BT(t, candidates, voters, SIZE_C, SIZE_V);
    char * res = key_to_str(winner);

    printf("Le gagnant est : %s\n", res);

    free(res);
    free(winner);

    delete_list_protected(declarations);
    delete_list_keys(candidates);
    delete_list_keys(voters);

    return 0;
}
