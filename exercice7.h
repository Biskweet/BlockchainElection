#include "exercice6.h"
#include <openssl/sha.h>


typedef struct {
    Key* author;                            // Owner's public key
    CellProtected* votes;                   // Declaration linked list
    unsigned char* hash;                    // Hashed value of block
    unsigned char* previous_hash;           // Hashed value of prev block
    int nonce;                              // Proof of work
} Block;


void write_block(char*, Block*);

Block* read_block(char*);

char* block_to_str(Block*);

unsigned char* hash_str(unsigned char*);

void compute_proof_of_work(Block*, int);

int verify_block(Block*, int);

void delete_block(Block*);
