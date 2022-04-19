#include "exercice7.h"


int main(int argc, char const *argv[]) {
    // const char* s = "Rosetta code";
    // unsigned char* d = SHA256((unsigned char*) s, strlen(s), 0);
    // for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) printf("%02x", d[i]);
    // putchar('\n');

    // unsigned char* res = hash_str((unsigned char*) "binouze");
    // printf("%s\n", res);
    // free(res);

    Block* b = read_block("block.txt");

    char* block_str = block_to_str(b);
    printf("\n%s\n\n", block_str);
    free(block_str);

    FILE* f = fopen("benchmarks_proofofwork.txt", "w");

    time_t debut, fin;
    double time;
    for (int i = 1; i <= 7; i++) {
        printf("Before computing PoW: %s\n", b->hash);
        
        debut = clock(); 
        compute_proof_of_work(b, i);
        fin = clock();

        time = (double) (fin - debut) / CLOCKS_PER_SEC;

        printf("After computing PoW : %s (nonce=%d, calc time is %lfs)\n\n", b->hash, b->nonce, time);
        fprintf(f, "%d %lf\n", i, time);
    }

    fclose(f);

    delete_block(b);

    return 0;
}
