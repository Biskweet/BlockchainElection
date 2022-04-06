#include "exercice3.h"


void init_key(Key* key, long val, long n) {
    key->val = val;
    key->n = n;
}


void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size) {
    long n, s, u;
    long p, q;

    p = random_prime_number(low_size, up_size, 1000);
    
    do {
        q = random_prime_number(low_size, up_size, 1000);
    } while (p == q);

    generate_keys_values(p, q, &n, &s, &u);

    init_key(pKey, s, n);
    init_key(sKey, u, n);
}


char* key_to_str(Key* key) {
    /*
     * convert key values in a string and return them
     */

    char* str = (char*) malloc(sizeof(char) * 12);

    if (str == NULL) {
        printf("Erreur d'allocation (key_to_str).\n");
        return NULL;
    }

    sprintf(str, "(%lx,%lx)", key->val, key->n);
    return str;
}


Key* str_to_key(char* str) {
    Key* key = (Key*) malloc(sizeof(Key));

    if (key == NULL) {
        printf("Erreur d'allocation (str_to_key).\n");
        return NULL;
    }

    sscanf(str, "(%lx,%lx)", &(key->val), &(key->n));
    return key;
}


Signature* init_signature(long* content, int size) {
    Signature* signature = (Signature*) malloc(sizeof(Signature));

    if (signature == NULL) {
        printf("Erreur d'allocation (init_signature).\n");
        return NULL;
    }

    signature->size = size;

    signature->data = (long*) malloc(sizeof(long) * size);

    if (signature->data == NULL) {
        printf("Erreur d'allocation (init_signature).\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        signature->data[i] = content[i];
    }

    return signature;
}


Signature* sign(char* mess, Key* sKey) {
    long *tab = encrypt(mess, sKey->val, sKey->n);
    Signature* s = (Signature*) malloc(sizeof(Signature));

    if (s == NULL) {
        printf("Erreur d'allocation (sign).\n");
        return NULL;
    }

    s->data = tab;
    s->size = strlen(mess);

    return s;
}


char* signature_to_str(Signature* sgn) {
    char* result = (char*) malloc(sizeof(char) * ((sgn->size) * 5 + 2));

    if (result == NULL) {
        printf("Erreur d'allocation (signature_to_str).\n");
        return NULL;
    }

    result[0] = '#';
    int pos = 1;
    char buffer[5];

    for (int i = 0; i < sgn->size; i++) {
        sprintf(buffer, "%lx", sgn->data[i]);
        for (int j = 0; j < strlen(buffer); j++) {
            result[pos] = buffer[j];
            pos++;
        }
        result[pos] = '#';
        pos++;
    }
    result[pos] = '\0';
    result = realloc(result, sizeof(char) * (pos + 1));
    return result;
}


Signature* str_to_signature(char* str) {
    int len = strlen(str), num = 0, pos = 0;
    long* content = (long*) malloc(sizeof(long) * len);

    if (content == NULL) {
        printf("Erreur d'allocation (str_to_signature).\n");
        return NULL;
    }

    char buffer[5];

    for (int i = 0; i < len; i++) {
        if (str[i] != '#') {
            buffer[pos] = str[i];
            pos++;
        } else {
            if (pos != 0) {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num++;
                pos = 0;
            }
        }
    }
    content = realloc(content, sizeof(long) * num);
    Signature* t = init_signature(content, num);
    free(content);
    return t;
}


Protected* init_protected(Key* pKey, char* mess, Signature* sign) {
    Protected* p = (Protected*) malloc(sizeof(Protected));

    if (p == NULL) {
        printf("Erreur d'allocation (init_protected).\n");
        return NULL;
    }

    p->pKey = pKey;
    p->msg = strdup(mess);
    p->signature = sign;

    return p;
}


int verify(Protected* pr) {
    char* msg = decrypt(pr->signature->data, pr->signature->size, pr->pKey->val, pr->pKey->n);
    int res = strcmp(pr->msg, msg) == 0;
    free(msg);
    return res;
}


char* protected_to_str(Protected* pr) {
    char* str = malloc(sizeof(char) * 81);

    if (str == NULL) {
        printf("Erreur d'allocation (protected_to_str).\n");
        return NULL;
    }

    char* key = key_to_str(pr->pKey);
    char* signature = signature_to_str(pr->signature);
    sprintf(str, "%s %s %s", key, pr->msg, signature);
    free(key);
    free(signature);
    return str;
}


Protected* str_to_protected(char* str) {
    Protected* p = (Protected*) malloc(sizeof(Protected));

    if (p == NULL) {
        printf("Erreur d'allocation (str_to_protected).\n");
        return NULL;
    }

    p->msg = (char*) malloc(sizeof(char) * 12);

    if (p->msg == NULL) {
        printf("Erreur d'allocation (str_to_protected).\n");
        return NULL;
    }

    char key[12], signature[57];

    sscanf(str, "%s %s %s", key, p->msg, signature);

    p->pKey = str_to_key(key);
    p->signature = str_to_signature(signature);

    return p;
}


void liberer_signature(Signature* sig) {
    free(sig->data);
    free(sig);
}


void liberer_protected(Protected* pr) {
    free(pr->msg);
    liberer_signature(pr->signature);
    free(pr->pKey);
    free(pr);
}
