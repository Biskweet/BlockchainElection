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
    HashCell* hshcl = (HashCell*) malloc(sizeof(key));

    if (hshcl == NULL) {
        printf("Erreur d'allocation (create_hashcell)\n");
        return NULL;
    }

    hshcl->key = key;
    hshcl->val = 0;

    return hshcl;
}


int hash_function(Key* key, int size) {
    return (key->val + key->n) % size;
}


int find_position(HashTable* t, Key* key) {
    int index = hash_function(key, t->size);
    if ((t->tab[index] != NULL)) {
        if ((t->tab[index]->key->val == key->val) && (t->tab[index]->key->n == key->n)) {
            return index;  // If the key is identical (i.e. already inserted)
        } else {
            for (int i = 0; i < t->size; i++) {
                if (t->tab[(index + i) % t->size] == NULL) {
                    return (index + i) % t->size;
                }
            }
            return -1;
        }
    } else {
        return index;
    }
}


HashTable* create_hashtable(CellKey* keys, int size) {
    HashTable* hshtb = (HashTable*) malloc(sizeof(HashTable));

    if (hshtb == NULL) {
        printf("Erreur d'allocation (create_hashtable)\n");
        return NULL;
    }

    hshtb->size = size;
    hshtb->tab = (HashCell**) malloc(sizeof(HashCell*) * size);

    if (hshtb->tab == NULL) {
        printf("Erreur d'allocation (create_hashtable)\n");
        return NULL;
    }

    CellKey* prev = NULL;
    while (keys != NULL) {
        int index = find_position(hshtb, keys->data);

        if (hshtb->tab[index] == NULL) {
            hshtb->tab[index] = create_hashcell(keys->data);
        } else {
            prev->next = keys->next;
            delete_cell_key(keys);
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


Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) {
    Key* vote;
    int index;

    HashTable* h_c = create_hashtable(candidates, sizeC);
    HashTable* h_v = create_hashtable(voters, sizeV);    

    while (decl != NULL) {
        index = find_position(h_v, decl->data->pKey);
        
        if (h_v->tab[index]->val == 0) {
            vote = str_to_key(decl->data->msg);

            h_c->tab[find_position(h_c, vote)]->val += 1;
            h_v->tab[index]->val = 1;
            
            free(vote);
        }

        decl = decl->next;
    }

    Key* winner;
    int max = 0;

    // Determining the winner
    for (int i = 0; i < h_v->size; i++) {
        if (h_c->tab[i]->val > max) {
            max = h_c->tab[i]->val;
            winner = h_c->tab[i]->key;
        }
    }

    delete_hashtable(h_c);
    delete_hashtable(h_v);

    return winner;
}
