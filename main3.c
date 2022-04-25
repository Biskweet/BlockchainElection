#include "exercice3.h"


int main(int argc, char const *argv[]) {
    srand(time(NULL));

    Key* pKey = malloc(sizeof(Key));
    Key* sKey = malloc(sizeof(Key));

    init_pair_keys(pKey, sKey ,3 ,7);

    printf("pKey : (%lx, %lx)\n", pKey->val, pKey->n);
    printf("sKey : (%lx, %lx)\n", sKey->val, sKey->n);

    char *chaine = key_to_str(pKey);
    printf("key to str : %s\n", chaine);

    Key *k = str_to_key(chaine);
    printf("str to key : (%lx, %lx)\n", k->val, k->n);


    Key* pKeyC = malloc(sizeof(Key));
    Key* sKeyC = malloc(sizeof(Key));

    init_pair_keys(pKeyC, sKeyC, 3, 7);

    char* msg = key_to_str(pKeyC);
    char* msg2 = key_to_str(pKey);

    printf("%s vote pour %s\n", msg2, msg);

    Signature *sig = sign(msg, sKey);

    printf("Signature: ");
    print_long_vector(sig->data, sig->size);

    char* chaine2 = signature_to_str(sig);
    printf("signature_to_str: %s\n", chaine2);

    Signature * sig2 = str_to_signature(chaine2);
    printf("str_to_signature: ");
    print_long_vector(sig2->data, sig2->size);


    Protected *pr = init_protected(pKey, msg, sig2);

    if (verify(pr)) {
      printf("Signature valide.\n");
    } else {
      printf("Signature non valide.\n");
    }

    char* chaine3 = protected_to_str(pr);
    printf("protected_to_str: %s\n", chaine3);

    Protected* pr2 = str_to_protected(chaine3);
    char* msg3 = key_to_str(pr2->pKey);
    char* msg4 = signature_to_str(pr2->signature);
    printf("str_to_protected: %s %s %s\n", msg3, pr2->msg, msg4);

    free(sKey); free(pKeyC); free(sKeyC);
    free(k);
    free(chaine); free(chaine2); free(chaine3);
    free(msg); free(msg2); free(msg3); free(msg4);
    liberer_signature(sig);
    liberer_protected(pr); liberer_protected(pr2);

    return 0;
}
