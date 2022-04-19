#include "exercice7.h"


typedef struct block_tree_cell {
    Block* block;
    struct block_tree_cell* father;
    struct block_tree_cell* firstChild;
    struct block_tree_cell* nextBro;
    int height;
} CellTree;



CellTree* create_node(Block*);

int update_height(CellTree*, CellTree*);

void add_child(CellTree*, CellTree*);

void delete_node(CellTree*);

void print_tree(CellTree*);

void delete_tree(CellTree*);

CellTree* highest_child(CellTree*);

CellTree* last_node(CellTree*);

CellProtected* fusion_chaines(CellProtected*, CellProtected*);

CellProtected* get_trusted_votes(CellTree*);
