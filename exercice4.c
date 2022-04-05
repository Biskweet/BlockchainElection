#include "exercice4.h"


void generate_random_data(int nv, int nc) {
    FILE* f = fopen("keys.txt", "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n"); return;
    }

    Key *pKey, *sKey;

    Key* klist[nv][2];

    for (int i = 0; i < nv; i++) {
        pKey = (Key*) malloc(sizeof(Key));
        sKey = (Key*) malloc(sizeof(Key));

        if ((pKey == NULL) || (sKey == NULL)) {
            printf("Erreur d'allocation (generate_random_data).\n");
            return;
        }

        init_pair_keys(pKey, sKey, 3, 7);

        klist[i][0] = pKey;
        klist[i][1] = sKey;

        char* pKey_str = key_to_str(pKey);
        char* sKey_str = key_to_str(sKey);
        fprintf(f, "%s %s\n", pKey_str, sKey_str);

        free(pKey_str);
        free(sKey_str);
    }

    fclose(f);

    Key* candidates[nc];
    for (int i = 0; i < nc; i++) candidates[i] = NULL;  // To be able to iterate over it more easily

    f = fopen("candidates.txt", "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n"); return;
    }

    for (int i = 0; i < nc; i++) {
        int index;
        do {
            index = rand() % nv;  // So there are no duplicates in candidates
        } while (is_in(klist[index][0], candidates));

        candidates[i] = klist[index][0];

        char* cKey_str = key_to_str(candidates[i]);
        fprintf(f, "%s\n", cKey_str);

        free(cKey_str);
    }

    fclose(f);

    f = fopen("declarations.txt", "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n"); return;
    }

    Protected* pr;
    char* choice;
    Signature* signature;
    char* declaration;

    for (int i = 0; i < nv; i++) {
        int index = rand() % nc;
        choice = key_to_str(candidates[index]);
        signature = sign(choice, klist[i][1]);
        pr = init_protected(klist[i][0], choice, signature);

        declaration = protected_to_str(pr);

        fprintf(f, "%s\n", declaration);

        free(choice);
        free(declaration);
        free(pr->msg);
        liberer_signature(pr->signature);
        free(pr);
    }

    for (int i = 0; i < nv; i++) {
        free(klist[i][0]);
        free(klist[i][1]);
    }

    fclose(f);
}


int is_in(Key* x, Key* klist[]) {
    for(int i = 0; klist[i] != NULL; i++) {
        if (klist[i] == x) {
            return 1;
        }
    }
    return 0;
}
