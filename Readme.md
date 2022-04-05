# Rapport de projet
*Damoiseau-Malraux Gaspard & Blanchard-Billard Raphaël*  
Ce projet cherche à reproduire un système de vote électronique par chiffrement RSA, qui permet le chiffrement asymétrique de messages à l'aide d'une **clef privée** et d'une **clef publique**.



### Table des matières
1. [Organisation des fichiers](###organisation-des-fichiers)
1. [Structures utilisées](###structures-utilisées)
1. [Réponses aux questions](###réponses-aux-questions)
1. 




### Organisation des fichiers

Notes : tous les fichiers incluent les fichiers des exercices précédents. Les fichiers `main1.c`, `main2.c`, `main3.c`, `main4.c`, `main5.c`, `main6.c` contiennent les tests des fonctions des fichiers `exercice` correspondant.

* `exercice1.c` et `exercice1.h` contiennent toutes les fonctions permettant les opérations mathématiques (exponentiation modulaire, vérification de nombre premiers) ;
* `exercice2.c` et `exercice2.h` contiennent les fonctions permettant la génération des valeurs des clefs ainsi que le chiffrement et le déchiffrement de ces valeurs ;
* `exercice3.c` et `exercice3.h` contiennent les fonction pour initialiser les structures de clefs et de signatures ainsi que les fonctions pour les vérifier et les convertir en chaîne de caractère ;
* `exercice4.c` et `exercice4.h` contiennent la fonction de génération de votants, de candidats et de clefs et leur écriture dans un fichier ;
* `exercice5.c` et `exercice5.h` permettent la lecture des clefs depuis un fichier.

### Structures utilisées

Les structures utilisées sont :

- Dans `exercice3.h` :

```c
typedef struct {
    unsigned long val;
    unsigned long n;
} Key;
```

```c
typedef struct {
    long* data;
    unsigned int size;
} Signature;
```

```c
typedef struct {
    Key* pKey;
    char* msg;
    Signature* signature;
} Protected;
```

* Dans `exercice4.h` :

```c
typedef struct cellProtected {
    Protected* data;
    struct cellProtected * next;
} CellProtected;
```

```c
typedef struct cellKey {
    Key* data;
    struct cellKey * next;
} CellKey;
```

Ces deux dernières structures représentent des listes chaînées des structures respectives.

* Dans `exercice6.h` :

```c
typedef struct {
    Key* key;
    int val;
} HashCell;
```

```c
typedef struct {
    HashCell** tab;
    int size;
} HashTable;
```

Ces deux dernières structures représentent une table de hachage de clefs.

### Réponses aux questions

1. La complexité de la fonction `is_prime_naif` est $O(p)$.
2. Le plus petit nombre premier calculé en 2 millisecondes ou plus est $318683$.
3. La complexité de la fonction `modpow_naif` est $O(m)$.

5. Performances des fonctions d'exponentiation modulaire :

![image-20220328194609462](./graph.png)

On voit clairement l'efficacité supérieure du `modpow` non naïf en termes de temps de calcul de $a^m \text{ mod } n$ lorsque $m$ devient très grand (pour $a=2147481647$ et $n=34694$).