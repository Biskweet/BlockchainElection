#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>


int is_prime_naif(long);

long modpow_naif(long, long, long);

long modpow(long, long, long);

int witness(long, long, long, long);

long rand_long(long, long);

int is_prime_miller(long, int);

long random_prime_number(int, int, int);
