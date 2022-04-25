#include "exercice1.h"


int is_prime_naif(long p) {
    for (unsigned long i = 2; i < p; i++) {
        if (p % i == 0) return 0;  // Complexité n
    }
    return 1;
}


long modpow_naif(long a, long m, long n) {
    int res = 1;
    for (long i = 0; i < m; i++) {
        res = res * a;  // Complexité m
        res = res % n;
    }

    return res;
}


long modpow(long a, long m, long n) {
    if (m == 0) {
        return 1 % n;  // In case n == 1, 1 % n would equal 0
    }

    long b = modpow(a, m/2, n);

    if (m & 1) {  // If m is odd
        return (a * b * b) % n;
    } else {
        return (b * b) % n;
    }
}


int witness(long a, long b, long d, long p) {
    long x = modpow(a, d, p);
    
    if (x == 1) {
        return 0;
    }

    for (long i = 0; i < b ; i++) {
        if (x == p - 1) {
            return 0;
        }
        x = modpow(x, 2, p);
    }

    return 1;
}


long rand_long(long low, long up) {
    return rand() % (up - low + 1) + low;
}


int is_prime_miller(long p, int k) {
    if (p == 2) {
        return 1;
    }

    if (!(p & 1) || p <= 1) {  // On verifie que p est impair et different de 1
        return 0;
    }

    // On determine b et d :
    long b = 0;
    long d = p - 1;

    while (!(d & 1)) {  // Tant que d est pair
        d = d / 2;
        b = b + 1;
    }

    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;

    for (i = 0; i < k; i++) {
        a = rand_long(2, p - 1) ;
        if (witness(a, b, d, p)) {
            return 0;
        }
    }

    return 1;
}


long random_prime_number(int low_size, int up_size, int k) {
    long min = pow(2, low_size), max = pow(2, up_size);

    long pivot = rand_long(min, max);  // Take a random integer in the interval

    // Iterating upwards to the first prime number found starting from the pivot
    for (long i = pivot; i <= max; i += (i & 1 ? 2 : 1)) {  // (i & 1 ? 2 : 1) ensures checking only odd numbers
        if (is_prime_miller(i, k)) return i;
    }

    // If nothing found, iterating downwards in the interval
    for (long i = pivot; i >= min; i -= (i & 1 ? 2 : 1)) {
        if (is_prime_miller(i, k)) return i;
    }

    // Should never trigger (the interval should always have prime numbers)
    printf("Pas de nombre premier dans l'intervalle donné.\n"); return -1;
}


void printerror(char* str) {
    printf("\033[31m%s\033[0m", str);
}
