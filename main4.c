#include "exercice4.h"
#define NBVOTERS 1500
#define NBCANDIDATES 10


int main(int argc, char const *argv[]) {
    srand(time(NULL));

    printf("Generating random data...\n");
    generate_random_data(NBVOTERS, NBCANDIDATES);
    printf("Generated %d voters & %d candidates.\n", NBVOTERS, NBCANDIDATES);

    return 0;
}
