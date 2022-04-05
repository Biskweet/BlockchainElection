#include "exercice2.h"


int main() {
    
// 2.2 :
    srand(time(NULL));

    long p, q;
    p = random_prime_number(3, 7, 5000);

    do {
        q = random_prime_number(3, 7, 5000);
    } while (p == q);

    long n, s, u;
    generate_keys_values(p, q, &n, &s, &u);

    if (u < 0) {
        u = u + (p - 1) * (q - 1);
    }

    printf("Clef publique = (%lx, %lx)\n", s, n);
    printf("Clef privée = (%lx, %lx)\n", u, n);

    char msg[10] = "Hello";
    int len = strlen(msg);

    long* crypted = encrypt(msg, s, n);

    printf("Initial message : %s (length: %d)\n", msg, (int) strlen(msg));
    printf("Encoded representation : ");
    print_long_vector(crypted, len);

    char* decoded = decrypt(crypted, len, u, n);
    printf("Decoded : %s (length: %d)\n", decoded, (int) strlen(decoded));

    free(crypted);
    free(decoded);

    return 0;
}