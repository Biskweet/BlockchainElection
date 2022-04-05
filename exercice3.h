#include "exercice2.h"


typedef struct {
    unsigned long val;
    unsigned long n;
} Key;


typedef struct {
    long* data;
    unsigned int size;
} Signature;


typedef struct {
    Key* pKey;
    char* msg;
    Signature* signature;
} Protected;


void init_key(Key*, long, long);

void init_pair_keys(Key*, Key*, long, long);

char* key_to_str(Key*);

Key* str_to_key(char*);

Signature* init_signature(long*, int);

Signature* sign(char*, Key*);

char* signature_to_str(Signature*);

Signature* str_to_signature(char*);

Protected* init_protected(Key*, char*, Signature*);

int verify(Protected*);

char* protected_to_str(Protected*);

Protected* str_to_protected(char*);

void liberer_signature(Signature*);

void liberer_protected(Protected*);
