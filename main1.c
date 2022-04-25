#include "exercice1.h"

int main(int argc, char const *argv[]) {
    printf("Entering test main. Uncomment the part you want to test. No output = everything under comment.\n\n");
    clock_t debut, fin;
    debut = 0; fin = 0;

// 1.2 :
    // double diff = 0;
    // int prime;
    // long p = 10001;
    // while (diff < 0.002) {
    //     p += 2;

    //     debut = clock();
    //     prime = is_prime_naif(p);
    //     fin = clock();

    //     if (prime) {
    //         diff = (double) (fin - debut) / CLOCKS_PER_SEC;
    //     }

    //     printf("%lf sec.\n", diff);
    // }

    // printf("Premier : %ld\n", p);

// 1.5 :
    double t1, t2;

    FILE* file = fopen("benchmarks.txt", "w");

    for (int i = 1000; i <= 1000000; i += 1000) {
        debut = clock();
        modpow(2147481647, i, 34694);
        fin = clock();
        t1 = (double) (fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        modpow_naif(2147481647, i, 34694);
        fin = clock();
        t2 = (double) (fin - debut) / CLOCKS_PER_SEC;

        fprintf(file, "%d %lf %lf\n", i, t1, t2);

        if (i % 100 == 0) printf("%d\n", i);
    }

    fclose(file);

// 1.8 :
     // srand(time(NULL));

     // debut = clock();
     // long random = random_prime_number(15, 20, 10);
     // fin = clock();

     // printf("Random prime number: %ld (%lfs)\n", random, (double) (fin - debut) / CLOCKS_PER_SEC);


    return 0;
}
