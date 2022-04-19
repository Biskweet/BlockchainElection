#include "exercice2.h"


long extended_gcd(long s, long t, long *u, long *v) {
    if (t == 0) {
        *u = 1;
        *v = 1;
        return s;
    }

    long uPrim, vPrim;
    long gcd = extended_gcd(t, s % t, &uPrim, &vPrim);

    *u = vPrim;
    *v = uPrim - (s / t) * vPrim;

    return gcd;
}


void generate_keys_values(long p, long q, long* n, long* s, long* u) {
    *n = p * q;
    long t = (p - 1) * (q - 1);
    long v = 1;

    do {
        *s = rand_long(0, t);
    } while (extended_gcd(*s, t, u, &v) != 1);

    while (*u < 2) *u = *u + t;
}


long* encrypt(char* chaine, long s, long n) {
    long* encrypted = (long*) malloc(sizeof(long) * strlen(chaine));

    if (encrypted == NULL) {
        printerror("Erreur d'allocation (encrypt).\n");
        return NULL;
    }

    for (int i = 0; chaine[i] != '\0'; i++) {
        encrypted[i] = modpow((long) chaine[i], s, n);
    }

    return encrypted;
}


char* decrypt(long* crypted, int size, long u, long n) {
    char* message = (char*) malloc(sizeof(char) * (size + 1));

    if (message == NULL) {
        printerror("Erreur d'allocation (decrypt).\n");
        return NULL;
    }

    int i;
    for (i = 0; i < size; i++) {
        message[i] = (char) modpow(crypted[i], u, n);
    }

    message[i] = '\0';  // Terminating null character

    return message;
}


void print_long_vector(long* result, int size) {
    printf("Vector: [ ");
    for (int i = 0; i < size; i++) {
        printf("%lx ", result[i]);
    }
    printf("]\n");
}
