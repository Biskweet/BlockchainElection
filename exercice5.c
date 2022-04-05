#include "exercice5.h"


CellKey* create_cell_key(Key* key) {
    CellKey* ckey = (CellKey*) malloc(sizeof(CellKey));
    if (ckey == NULL) {
        printf("Erreur d'allocation (create_cell_key).\n");
        return NULL;
    }

    ckey->data = key;
    ckey->next = NULL;
    return ckey;
}


void ajout_tete_ck(CellKey** liste, CellKey* item) {
    item->next = *liste;
    *liste = item;
}


CellKey* read_public_keys(char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier (read_public_keys).\n");
        return NULL;
    }

    char buffer[12];
    long pKey_val, pKey_n;
    Key *pKey;
    CellKey *ck, *liste = NULL;
    while (!feof(f)) {
        fscanf(f, "(%lx,%lx)%s\n", &pKey_val, &pKey_n, buffer);
        pKey = (Key*) malloc(sizeof(Key));
        
        if (pKey == NULL) {
            printf("Erreur d'allocation (read_public_keys).\n");
            return NULL;
        }

        init_key(pKey, pKey_val, pKey_n);
        ck = create_cell_key(pKey);
        ajout_tete_ck(&liste, ck);
    }

    fclose(f);

    return liste;
}


void print_list_keys(CellKey* LCK) {
    while (LCK != NULL) {
        char* key_str = key_to_str(LCK->data);
        printf("%s\n", key_str);
        LCK = LCK->next;
        free(key_str);
    }
}


void delete_cell_key(CellKey* c) {
    free(c->data);
    free(c);
}


void delete_list_keys(CellKey* LCK) {
    if (LCK != NULL) {
        delete_list_keys(LCK->next);
        delete_cell_key(LCK);
    }
}


CellProtected* create_cell_protected(Protected* pr) {
    CellProtected* cellp = (CellProtected*) malloc(sizeof(CellProtected));

    if (cellp == NULL) {
        printf("Erreur d'allocation (create_cell_protected).\n");
        return NULL;
    }

    cellp->data = pr;
    cellp->next = NULL;
    return cellp;
}


void ajout_tete_cp(CellProtected** liste, CellProtected* item) {
    item->next = *liste;
    *liste = item;
}


CellProtected* read_protected() {
    FILE* f = fopen("declarations.txt", "r");

    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier (read_protected).\n");
        return NULL;
    }

    char pr_str[81], temp1[64], temp2[128];
    Protected* pr;
    CellProtected *cpr, *liste = NULL;
    while (!feof(f)) {
        fscanf(f, "%s %s %s\n", pr_str, temp1, temp2);
        strcat(strcat(strcat(strcat(pr_str, " "), temp1)," "), temp2);
        pr = str_to_protected(pr_str);
        cpr = create_cell_protected(pr);
        ajout_tete_cp(&liste, cpr);
    }

    fclose(f);

    return liste;
}


void print_list_pr(CellProtected* LCP) {
    while (LCP != NULL) {
        char* pr_str = protected_to_str(LCP->data);
        printf("%s\n", pr_str);
        LCP = LCP->next;
        free(pr_str);
    }
}


void delete_cell_protected(CellProtected* cpr) {
    liberer_protected(cpr->data);
    free(cpr);
}


void delete_list_protected(CellProtected* cpr) {
    CellProtected* temp = cpr;
    while (cpr != NULL) {
        cpr = cpr->next;
        delete_cell_protected(temp);
        temp = cpr;
    }
}
