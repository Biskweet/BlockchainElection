# Rapport de projet
*Damoiseau-Malraux Gaspard & Blanchard-Billard Raphaël*  

Ce projet cherche à reproduire un système de vote électronique sécurisé qui utilise le chiffrement par **RSA**, qui permet le chiffrement asymétrique de messages à l'aide d'une **clef privée** et d'une **clef publique**. La structure des données fonctionne selon un système de **blockchain**, pour assurer la **sécurité**, **l'authentification des votes** et la **décentralisation**.



### Table des matières
1. [Préambule et structure générale du code](###préambule-et-structure-générale-du-code)
1. [Organisation des fichiers](###organisation-des-fichiers)
1. [Structures utilisées](###structures-utilisées)
1. [Jeux de test](###jeux-de-test)
1. [Réponses aux questions](###réponses-aux-questions)
1. 



### Préambule et structure générale du code

Le programme se décompose en plusieurs fichiers sources (`exercice`$_i$ ) et de tests (`main`$_i$), qui contiennent les tests des fonctions des fichiers `exercice` correspondants. Chaque fichier source $exercice_i.c$ inclut le fichier source $exercice_{i-1}.c$ . Ainsi, par cascade, exécuter le fichier $main_i.c$ revient à tester l'intégralité des fonctions définies précédemment.

Attention : le fichier `main9.c` est le seul *main* à ne pas proposer de simples tests, mais une simulation complète d'une élection en automatique et aléatoire. Il est encouragé de tester individuellement les *main* dans l'ordre.

Ne pas oublier de créer le dossier `blockchain/`, ni supprimer les fichiers `block.txt` et `testvotes.txt` qui sont utilisés dans des tests !



### Organisation des fichiers

Tous les fichiers de définitions des fonctions importent un fichier *header* jumeau comportant les structures utilisées et les prototypes de fontions.

* `exercice1.c` : fonctions de calculs de nombres premiers et d'exponentiation modulaire, versions naïves et non naïves, opérations mathématiques ;

* `exercice2.c` : génération des valeurs correctes de clefs, chiffrement et déchiffrement de messages selon ces clefs ;

* `exercice3.c` :  création des clefs, des signatures¹ et des protected², signature d'un vote, convertissement de chacune de ces structures en chaîne de caractères et opération inverse ;

* `exercice4.c` : génération de données aléatoires et leur écriture dans 3 fichiers : `nv` votants dans `keys.txt`, `nc` candidats dans `candidates.txt` et `nv` déclarations de votes dans `declarations.txt` ;

* `exercice5.c` : lecture de ces fichiers et restitution en structures, introduction des listes chaînées de clefs et de protected, et opérations sur ces listes (création, insertion, affichage, suppression) ;

* `exercice6.c` : vérification de la validité des déclarations, introduction des tables de hachages et de la fonction de hachage choisie, détermination du vainqueur selon les déclarations lues ;
* `exercice7.c` : introduction des blocs pour la *blockchain*, convertissement d'un bloc en chaîne de caractères et opération inverse, hachage de blocs selon la méthode SHA256, calcul de la *proof of work* (temps de calcul supplémentaire artificiel) ;
* `exercice8.c` : introduction des nœuds de l'arbre pour la *blockchain* (création, initialisation, insertion, gestion de la hauteur), fonction de recherche du chemin le plus long, fusion des votes contenus ;
* `exercice9.c` : ajout des votes à un bloc, ajout de blocs à la *blockchain*, lecture des blocs de cette dernière et création des liens entre eux (*via* le `previous_hash`), détermination du vainqueur de l'élection en comptant les voix de la plus grande chaîne de l'arbre.

Note : la simulation effectuée en fin de projet est parfaite, c'est-à-dire qu'elle ne génère pas de fraude. **Par conséquent, il est normal que l'arbre obtenu ait la forme d'une chaîne simple de nœuds.**

[1, 2] : voir les structures dans [Structures utilisées](###structures-utilisées).




### Structures utilisées

Les structures utilisées sont :

- Dans `exercice3.h` :

```c
typedef struct {
    unsigned long val;
    unsigned long n;
} Key;
```

`Key` contient une valeur `val` unique à la clef et `n` commune à la paire privée/publique.

```c
typedef struct {
    long* data;
    unsigned int size;
} Signature;
```

`Signature` contient un tableau de `long` et la longueur dudit tableau. Le tableau `data` contient chaque caractère, chiffré, du message initial, sous forme d'un entier `long`.

```c
typedef struct {
    Key* pKey;
    char* msg;
    Signature* signature;
} Protected;
```

`Protected` contient la clef publique `pKey`, une chaîne de caractère `msg` et la signature correspondante dans `Signature`.

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
    HashCell** tab;
    int size;
} HashTable;
```

```c
typedef struct {
    Key* key;
    int val;
} HashCell;
```

`HashTable`représente une tableau de hachage de taille `size`. `HashCell` est comme son nom l'indique une cellule du tableau. La valeur `val` sert à marquer un votant ayant voté, ou à compter le nombre de voix d'un candidat.



### Jeux de test

* `main1.c` teste de performance des fonctions mathématiques ;
* `main2.c` crée un couple de valeurs clefs, les affiches, puis encode et décode une chaîne de caractère ;
* `main3.c` crée deux couple de clef et les convertit en chaîne de caractère. Ces clef sont  ensuite utilisées pour créé une signature qui est ensuite affichée et convertie en chaîne de caractères. Cette chaîne est ensuite reconvertit en signature pour vérifier la réversibilité de l'opération. Enfin, la protection des signature est testée ;
* `main4.c` teste la fonction `generate_random_data` qui génère des votants, des candidats parmi eux et les déclarations de votes. Chacun des votants vote pour un candidat aléatoire. Ces données sont ensuite écrites dans les fichiers `keys.txt`, `candidates.txt` et `declaration.txt` respectivement ;
* `main5.c` affiche les fichiers `keys.txt` et `declaration.txt` générés précédemment, puis supprime toutes les déclarations invalides et les affiche après correction ;
* `main6.c` génère des votants et des candidats dans des fichier comme expliqué précédemment. On extrait ensuite les données des fichiers et on les vérifie. A partir des données vérifiées, on calcule et affiche le vainqueur de l'élection ;
* `main7.c` teste les fonction de hachage `SHA256` et `hash_str`. On lit ensuite un bloc de `block.txt` et on mesure le temps de calcul de la *proof of work* ;
* `main8.c` crée deux blocs arbitrairement à l'aide des votes de `testvotes.txt` et crée un arbre à partir d'eux deux. Vérification du fonctionnement des fonctions basiques de l'exercice 8 ;
* `main9.c` contient le test final : il génère des données aléatoires, stocke les votes par paquets de 10 dans des blocs et reconstruit l'arbre de la *blockchain* à chaque fois pour déterminer le dernier nœud de l'arbre.  On détermine ensuite le vainqueur à partir de l'arbre.
  * Le jeu de tests n°9 indique une relativement petite fuite de mémoire dans `compute_winner_BT` (relative comparée à la quantité de mémoire gérée par le programme). Ce bug est connu mais n'a pas pu être corrigé par faute de temps. Nous soupçonnons la non libération des `CellProtected` dans la fusion des votes, qui doivent être dupliqués pour ne pas altérer l'arbre.



### Réponses aux questions

1. La complexité de la fonction `is_prime_naif` est $O(p)$.
2. Le plus petit nombre premier calculé en 2 millisecondes ou plus est $318683$.
3. La complexité de la fonction `modpow_naif` est $O(m)$.

5. Performances des fonctions d'exponentiation modulaire :

![image-20220328194609462](./graph.png)

On voit clairement l'efficacité supérieure du `modpow` non naïf en termes de temps de calcul de $a^m \text{ mod } n$ lorsque $m$ devient très grand (pour $a=2147481647$ et $n=34694$).