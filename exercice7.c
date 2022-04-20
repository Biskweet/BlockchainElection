#include "exercice7.h"
#include <unistd.h>


void write_block(char* filename, Block* block) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printerror("Erreur lors de l'ouverture du fichier (write_block).\n"); return;
    }

    char* buffer = key_to_str(block->author);
    fprintf(f, "%s %s %s %d\n", buffer, block->hash, block->previous_hash, block->nonce);
    free(buffer);

    CellProtected* iter = block->votes;
    while (iter != NULL) {
        buffer = protected_to_str(iter->data);

        fprintf(f, "%s\n", buffer);
        free(buffer);

        iter = iter->next;
    }

    fclose(f);
}


Block* read_block(char* filename) {
    char buff[256];
    getcwd(buff, sizeof(buff));

    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printerror("Erreur lors de l'ouverture du fichier (read_block).\n"); return NULL;
    }

    int nonce;
    char key_str[16], hash[128], prev_hash[128];   
    fscanf(f, "%s %s %s %d\n", key_str, hash, prev_hash, &nonce);

    Key* key = str_to_key(key_str);

    // Creating the block
    Block* block = (Block*) malloc(sizeof(Block));
    if (block == NULL) {
        printerror("Erreur d'allocation (read_block).\n");
        return NULL;
    }

    // Storing known values
    block->author = key;
    block->nonce = nonce;
    if (strcmp(hash, "(null)") == 0) block->hash = (unsigned char*) NULL;
    else block->hash = (unsigned char*) strdup(hash);

    if (strcmp(prev_hash, "(null)") == 0) block->previous_hash = (unsigned char*) NULL;
    else block->previous_hash = (unsigned char*) strdup(prev_hash);

    // Reading votes
    char pr_str[128], temp1[128], temp2[128];
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

    block->votes = liste;

    return block;
}


char* block_to_str(Block* block) {
    int str_size = 256;
    char* res = (char*) malloc(sizeof(char) * str_size);
    if (res == NULL) {
        printerror("Erreur d'allocation (block_to_str).\n"); return NULL;
    }

    // Writing author, previous hash, PoW
    char* buffer = key_to_str(block->author);
    sprintf(res, "%s %s %d\n", buffer, block->previous_hash, block->nonce);
    free(buffer);

    CellProtected* current = block->votes;
    // Writing all votes
    while (current != NULL) {
        buffer = protected_to_str(current->data);

        // Calculating the new string size and reallocating it
        str_size = str_size + strlen(buffer) + 2;
        res = realloc(res, str_size);

        strcat(strcat(res, buffer), " ");

        free(buffer);

        current = current->next;
    }

    return res;
}


unsigned char* hash_str(unsigned char* str) {
    char* result = (char*) malloc(sizeof(unsigned char) * 126);
    if (result == NULL) {
        printerror("Erreur d'allocation (create_hashcell)\n");
        return NULL;
    }

    unsigned char* hashed = SHA256((unsigned char*) str, strlen((char*) str), 0);

    sprintf(result, "%02x", hashed[0]);

    char buffer[8];
    for (int i = 1; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(buffer, "%02x", hashed[i]);
        strcat(result, buffer);
    }

    return (unsigned char*) result;
}


void compute_proof_of_work(Block* b, int d) {
    if (verify_block(b, d)) {
        return;
    } else {
        while (!verify_block(b, d)) {
            unsigned char* new_hash = hash_str(b->hash);
            
            // Overwriting the old hash
            free(b->hash);
            b->hash = new_hash;

            b->nonce += 1;
        }
    }
}


int verify_block(Block* b, int n) {
    for (int i = 0; i < n; i++) {
        if (b->hash[i] != '0') return 0;
    }
    return 1;
}


void delete_block(Block* b) {
    if (b->hash != NULL) free(b->hash);
    if (b->previous_hash != NULL) free(b->previous_hash);

    CellProtected* temp;
    while (b->votes != NULL) {
        temp = b->votes->next;
        free(b->votes);
        b->votes = temp;
    }

    free(b);
}
