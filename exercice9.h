#include "exercice8.h"
#include <dirent.h>
#include <unistd.h>
#define NO_ZEROS 2


void submit_vote(Protected*);

void create_block(CellTree*, Key*, int);

void add_block(int, char*);

CellTree* read_tree();

Key* compute_winner_BT(CellTree*, CellKey*, CellKey*, int, int);

CellKey* give_random_cellkey(CellKey*, int);

void free_all_protected_in_tree(CellTree*);
