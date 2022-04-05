#include "exercice5.h"


typedef struct {
    Key* key;
    int val;
} HashCell;


typedef struct {
    HashCell** tab;
    int size;
} HashTable;


void supprimer_invalides(CellProtected**);

HashCell* create_hashcell(Key*);

int hash_function(Key*, int);

int find_position(HashTable*, Key*);

HashTable* create_hashtable(CellKey*, int);

void delete_hashtable(HashTable*);

Key* compute_winner(CellProtected*, CellKey*, CellKey*, int, int);
