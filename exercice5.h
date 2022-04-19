#include "exercice4.h"


typedef struct cellProtected {
    Protected* data;
    struct cellProtected * next;
} CellProtected;


typedef struct cellKey {
    Key* data;
    struct cellKey * next;
} CellKey;


CellKey* create_cell_key(Key*);

void ajout_tete_ck(CellKey**, CellKey*);

CellKey* read_public_keys(char*);

void print_list_keys(CellKey*);

void delete_cell_key(CellKey*);

void delete_list_keys(CellKey*);

CellProtected* create_cell_protected(Protected*);

void ajout_tete_cp(CellProtected**, CellProtected*);

CellProtected* read_protected(char*);

void print_list_pr(CellProtected*);

void delete_cell_protected(CellProtected*);

void delete_list_protected(CellProtected*);
