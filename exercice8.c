#include "exercice8.h"


CellTree* create_node(Block* block) {
    CellTree* node = (CellTree*) malloc(sizeof(CellTree));
    if (node == NULL) {
        printerror("Erreur d'allocation (create_node).\n");
        return NULL;
    }

    node->block = block;
    node->father = NULL;
    node->firstChild = NULL;
    node->nextBro = NULL;
    node->height = 0;

    return node;
}


int update_height(CellTree* father, CellTree* child) {
    if (father->height < (child->height + 1)) {
        father->height = child->height + 1;
        return 1;
    } else {
        return 0;
    }
}


void add_child(CellTree* father, CellTree* child) {
    child->father = father;
    
    if (father->firstChild == NULL) {
        // Father does not have a child yet
        father->firstChild = child;
    } else {
        // Searching the last brother and attributing the child as its brother
        CellTree* iter = father->firstChild;
        while (iter->nextBro != NULL) iter = iter->nextBro;
        iter->nextBro = child;
    }

    while (father != NULL) {
        update_height(father, child);
        child = father;
        father = father->father;
    }
}


void print_tree(CellTree* tree) {
    if (tree == NULL) return;

    printf("\nHauteur %d : %s\n", tree->height, tree->block->hash);
    printf("\tSelf : %p\n\tfather : %p\n\tfirstChild : %p\n\tnextBro : %p\n\tPrevious_hash : %s\n",tree, tree->father, tree->firstChild, tree->nextBro, (char*) tree->block->previous_hash);
    
    print_tree(tree->nextBro);
    print_tree(tree->firstChild);
}


void delete_node(CellTree* node) {
    delete_block(node->block);
    free(node);
}


void delete_tree(CellTree* node) {
    if (node == NULL) return;

    delete_tree(node->nextBro);
    delete_tree(node->firstChild);

    delete_node(node);
}


CellTree* highest_child(CellTree* tree) {
    CellTree* current = tree->firstChild; 
    CellTree* highest = current;
    
    while (current != NULL) {
        if (current->height > highest->height) {
            highest = current;
        }
        current = current->nextBro;
    }

    return highest;
}


CellTree* last_node(CellTree* tree) {
    if (tree == NULL) return NULL;

    CellTree* current = highest_child(tree);

    // In case the tree has no child
    if (current == NULL) return tree;

    while (current->height != 0) {
        current = highest_child(current);
    }

    return current;
}


CellProtected* fusion_chaines(CellProtected* chaine1, CellProtected* chaine2) {
    CellProtected* chaine = NULL;

    while (chaine1 != NULL) {
        ajout_tete_cp(&chaine, create_cell_protected(chaine1->data));
        chaine1 = chaine1->next;
    }

    while (chaine2 != NULL) {
        ajout_tete_cp(&chaine, create_cell_protected(chaine2->data));
        chaine2 = chaine2->next;
    }

    return chaine;
}


CellProtected* get_trusted_votes(CellTree* tree) {
    if (tree == NULL) return NULL;

    CellProtected* votes = tree->block->votes;

    CellTree* current = tree;

    while (current->height != 0) {
        current = highest_child(current);
        votes = fusion_chaines(votes, current->block->votes);
    }

    return votes;
}
