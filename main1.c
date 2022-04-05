#include "exercice1.h"

int main(int argc, char const *argv[]) {

// 1.2 :
    // clock_t debut, fin;
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
//     clock_t debut, fin;
//     double t1, t2;

//     FILE* file = fopen("benchmarks.txt", "w");

//     for (int i = 1000; i <= 1000000; i += 1000) {
//         debut = clock();
//         modpow(2147481647, i, 34694);
//         fin = clock();
//         t1 = (double) (fin - debut) / CLOCKS_PER_SEC;

//         debut = clock();
//         modpow_naif(2147481647, i, 34694);
//         fin = clock();
//         t2 = (double) (fin - debut) / CLOCKS_PER_SEC;

//         fprintf(file, "%d %lf %lf\n", i, t1, t2);

//         if (i % 100 == 0) printf("%d\n", i);
//     }

//     fclose(file);

// 1.8 :
     // srand(time(NULL));

     // long random = random_prime_number(15, 20, 10);
     // printf("%ld\n", random);


    return 0;
}
