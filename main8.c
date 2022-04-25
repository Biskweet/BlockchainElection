#include "exercice8.h"


int main() {
    Block * b = (Block*) malloc(sizeof(Block));
    b->author = (Key*) malloc(sizeof(Key));
    init_key(b->author, 1583, 15049);
    b->votes = read_protected("testvotes.txt");
    b->hash = NULL;
    b->previous_hash = NULL;
    b->nonce = 0;

    CellTree * t = create_node(b);

    Block * b2 = (Block*) malloc(sizeof(Block));
    b2->author = (Key*) malloc(sizeof(Key));
    init_key(b->author, 1583, 15049);
    b2->votes = read_protected("testvotes.txt");
    b2->hash = NULL;
    b2->previous_hash = NULL;
    b2->nonce = 0;

    CellTree * t2 = create_node(b2);

    int h = update_height(t, t2);
    printf("h = %d\nt height = %d\nt2 height = %d\n", h, t->height, t2->height);

    add_child(t,t2);
    print_tree(t);

    printf("h = %d\nt height = %d\nt2 height = %d\n", h, t->height, t2->height);

    CellTree * highestchild = highest_child(t);
    print_tree(highestchild);
    CellTree * lastnode = last_node(t);
    print_tree(lastnode);
    printf("\n");

    CellProtected * votes = get_trusted_votes(t);
    print_list_pr(votes);
    delete_list_protected(votes);

    free(b->author);
    free(b2->author);
    delete_tree(t, 0);

    return 0;
}
