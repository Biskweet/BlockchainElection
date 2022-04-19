#include "exercice6.h"


void supprimer_invalides(CellProtected** l) {
    CellProtected* copie = *l;

    if (copie == NULL) return;

    // Will check the first elemement at the end
    while (copie->next != NULL) {
        if (!verify(copie->next->data)) {
            CellProtected* temp = copie->next;
            copie->next = copie->next->next;
            delete_cell_protected(temp);
        } else {
            copie = copie->next;
        }
    }

    copie = *l;

    // Checking the first element
    if (!verify(copie->data)) {
        *l = copie->next;
        delete_cell_protected(copie); 
    }
}


HashCell* create_hashcell(Key* key) {
    HashCell* hshcl = (HashCell*) malloc(sizeof(HashCell));
    if (hshcl == NULL) {
        printerror("Erreur d'allocation (create_hashcell)\n");
        return NULL;
    }

    hshcl->key = (Key*) malloc(sizeof(Key));
    if (hshcl->key == NULL) {
        printerror("Erreur d'allocation (create_hashcell)\n");
        return NULL;
    }

    hshcl->key->val = key->val;
    hshcl->key->n = key->n;
    hshcl->val = 0;

    return hshcl;
}


int hash_function(Key* key, int size) {
    return (key->val + key->n) % size;
}


HashTable* create_hashtable(CellKey* keys, int size) {
    HashTable* hshtb = (HashTable*) malloc(sizeof(HashTable));

    if (hshtb == NULL) {
        printerror("Erreur d'allocation (create_hashtable)\n");
        return NULL;
    }

    hshtb->size = size;
    hshtb->tab = (HashCell**) malloc(sizeof(HashCell*) * size);

    for (int i = 0; i < size; i++) {
        hshtb->tab[i] = NULL;
    }

    if (hshtb->tab == NULL) {
        printerror("Erreur d'allocation (create_hashtable)\n");
        return NULL;
    }

    CellKey* prev;
    while (keys != NULL) {
        int index = find_position(hshtb, keys->data);

        if (hshtb->tab[index] == NULL) {
            hshtb->tab[index] = create_hashcell(keys->data);
        } else {
            prev->next = keys->next;
            delete_cell_key(keys);  // Freeing non-placable keys
            keys = prev; 
        }

        prev = keys;
        keys = keys->next;
    }

    return hshtb;
}


void delete_hashtable(HashTable* t) {
    for (int i = 0; i < t->size; i++) {
        if (t->tab[i] == NULL) continue;  // Avoid freeing an empty cell

        free(t->tab[i]->key);
        free(t->tab[i]);
    }

    free(t->tab);
    free(t);
}


int find_position(HashTable* t, Key* key) {
    int index = hash_function(key, t->size);
    int cp = index;

    while (t->tab[index] != NULL && t->tab[index]->key->val != key->val && t->tab[index]->key->n != key->n) {
        index = (index + 1) % t->size;

        if (index == cp) return -1;  // If the array has been iterated over entirely
    }

    return index;
}


Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) {
    Key* vote;
    int index;

    HashTable* h_c = create_hashtable(candidates, sizeC);
    HashTable* h_v = create_hashtable(voters, sizeV);


    while (decl != NULL) {
        index = find_position(h_v, decl->data->pKey);
        
        if (h_v->tab[index]->val == 0) {
            vote = str_to_key(decl->data->msg);

            int pos = find_position(h_c, vote);

            h_c->tab[pos]->val += 1;
            h_v->tab[index]->val = 1;
            
            free(vote);
        }

        decl = decl->next;
    }

    Key* winner = NULL;
    int max = 0;

    // Determining the winner
    for (int i = 0; i < h_c->size; i++) {
        if (h_c->tab[i] != NULL && h_c->tab[i]->val > max) {
            max = h_c->tab[i]->val;
            winner = h_c->tab[i]->key;
        }
    }

    Key* winner_copy = (Key*) malloc(sizeof(Key));
    if (winner_copy == NULL) {
        printerror("Erreur d'allocation (compute_winner)\n");
    } else {
        init_key(winner_copy, winner->val, winner->n);
    }

    delete_hashtable(h_c);
    delete_hashtable(h_v);

    return winner_copy;
}
