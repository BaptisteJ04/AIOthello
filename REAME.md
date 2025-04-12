# Projet Othello IA

## Introduction

Ce projet consiste en la création d'un jeu Othello en réseau, où les joueurs peuvent s'affronter soit contre l'IA, soit contre un autre joueur en ligne. Le cœur du projet repose sur l'utilisation de l'algorithme Minimax pour permettre à l'IA de prendre des décisions stratégiques et jouer de manière optimale.

Les principales fonctionnalités incluent :
- La gestion du jeu Othello, avec l'initialisation de la grille et la gestion des coups valides.
- L'implémentation de l'algorithme Minimax avec élagage alpha-bêta pour prendre les meilleures décisions possibles.
- La possibilité de jouer contre une IA en utilisant un réseau avec communication entre le client et le serveur.
- L'intégration d'un système de tournois avec une simulation de parties entre plusieurs IA.

Ce projet utilise un système de communication réseau pour l'authentification et la gestion des parties. Le joueur est identifié via son mot de passe et son identifiant, et peut participer à une partie en ligne contre un autre joueur ou l'IA.


## 📝 Explication du fichier `othello.c`

Ce fichier contient plusieurs fonctions nécessaires à la mise en place et au fonctionnement du jeu Othello (aussi connu sous le nom de Reversi). Il utilise une grille de 8x8 pour représenter le plateau de jeu et permet de valider les coups, d'afficher le plateau et de gérer l'évolution du jeu.

### Fonctions principales :

1. **`init_grille(int mat[8][8])`** :
   Cette fonction initialise la grille du jeu en remplissant toute la matrice avec des valeurs indiquant des cases vides (`2`). Ensuite, elle place les 4 pions de départ : les deux pions noirs (représentés par `0`) et les deux pions blancs (représentés par `1`) au centre de la grille (positions `(3,3)`, `(4,3)`, `(3,4)` et `(4,4)`).

2. **`print_grille(int mat[8][8])`** :
   Cette fonction affiche la grille de jeu dans la console. Elle imprime les indices des lignes et des colonnes, puis parcourt la matrice pour afficher chaque case. Les pions noirs sont affichés en jaune (`\033[33m`), les pions blancs en cyan (`\033[36m`), et les cases vides sont affichées par des espaces.

3. **`coup_valide(int mat[8][8], int line, int col, int player)`** :
   Cette fonction vérifie si un coup joué à une position donnée (ligne, colonne) est valide pour le joueur spécifié. Un coup est valide si :
   - La case est vide (indiquée par `2` dans la matrice).
   - Il existe une évolution de la grille résultant de ce coup, ce qui signifie que ce coup permettra de capturer des pions adverses selon les règles d'Othello. Cette évolution est vérifiée par la fonction `evolution_grille`.

4. **`evolution_grille(int mat[8][8], int line, int col, int player)`** :
   Cette fonction vérifie si un coup permet de capturer des pions adverses dans toutes les directions possibles autour de la case ciblée : haut, bas, gauche, droite, et les 4 diagonales. Elle fait appel à la fonction `test_valide` pour vérifier chaque direction.

5. **`test_valide(int mat[8][8], int player, int x, int y, int i, int a, int b)`** :
   La fonction `test_valide` est utilisée pour tester la validité d'une direction donnée en partant d'une case spécifique sur la grille. Elle vérifie si une séquence de pions adverses est capturable dans la direction spécifiée, puis si un coup peut effectivement être joué en renversant ces pions.

### Conclusion

Le fichier `othello.c` permet de gérer les principales mécaniques du jeu Othello, y compris l'initialisation du plateau, la validation des coups, l'évolution de la grille et l'affichage de l'état du jeu. Il met en œuvre les règles de base du jeu et les conditions nécessaires pour que les coups soient valides et les pions capturés selon les règles d'Othello.


## 📝 Explication du fichier `MinMax.c`

Ce fichier implémente un système d'intelligence artificielle (IA) pour le jeu Othello, en utilisant les techniques de recherche minimax avec élagage alpha-bêta. L'objectif est de permettre à un ordinateur de jouer à Othello de manière compétitive contre un joueur humain ou contre une autre IA. Le fichier utilise plusieurs fonctions pour évaluer les coups possibles et choisir le meilleur coup à jouer en fonction d'une profondeur donnée de recherche.

### Fonctions principales :

1. **`numberone(int best[2], int grille[8][8], int joueur, int curent, int profondeur)`** :
   Cette fonction explore toutes les cases de la grille à la recherche du meilleur coup pour l'IA. Elle évalue chaque coup valide à l'aide de l'algorithme MinMax et choisit le coup avec le meilleur score. Le coup optimal est stocké dans le tableau `best` sous forme de coordonnées (ligne, colonne).

2. **`inter(int grille[8][8], int joueur, int curent, int profondeur, int alpha, int beta)`** :
   L'algorithme MinMax avec élagage alpha-bêta. Cette fonction est récursive et évalue les coups possibles à différentes profondeurs. Elle permet de simuler les mouvements successifs des joueurs (l'IA et l'adversaire) et d'estimer la "valeur" de chaque position de jeu. 
   - L'argument `alpha` représente la meilleure valeur que le joueur maximisateur peut garantir jusqu'à ce point.
   - L'argument `beta` représente la meilleure valeur que le joueur minimisateur peut garantir jusqu'à ce point.
   - Si le score d'une position dépasse `beta` (pour le joueur minimisateur) ou est inférieur à `alpha` (pour le joueur maximisateur), l'élagage alpha-bêta permet d'éviter l'exploration de cette branche de l'arbre de recherche.

3. **`evaluation_1(int grille[8][8], int joueur)`** :
   Cette fonction évalue la grille de jeu en comptant simplement le nombre de pions du joueur sur le plateau. Chaque pion du joueur rapporte 1 point, et chaque pion de l'adversaire retire 1 point. C'est une évaluation simple qui peut être utilisée pour des décisions rapides mais basiques.

4. **`evaluation_2(int grille[8][8], int joueur)`** :
   Cette fonction utilise une évaluation pondérée basée sur un tableau `teval` qui attribue des poids différents à chaque case du plateau, en fonction de sa position. Par exemple, les coins du plateau sont plus importants que les cases centrales. Cette approche vise à privilégier les positions stratégiques du jeu.

5. **`evaluation_3(int grille[8][8], int joueur)`** :
   Une amélioration de l'évaluation précédente, prenant en compte à la fois la position des pions et le nombre de cases vides restantes. Cette fonction pondère la grille de manière à maximiser les cases les plus avantageuses tout en tenant compte des cases vides disponibles pour de futurs coups. Elle essaie également de donner un score plus élevé aux situations où un joueur peut contrôler plus de cases à long terme.

6. **`copie(int grille[8][8], int p[8][8])`** :
   Cette fonction copie l'état actuel du plateau de jeu (`grille`) dans un autre tableau (`p`). Cela est nécessaire pour ne pas modifier la grille de jeu originale pendant les simulations de coups dans l'algorithme MinMax.

### Conclusion

Le fichier `othello_ai.c` implémente une IA pour le jeu Othello en utilisant l'algorithme MinMax avec élagage alpha-bêta, ainsi que plusieurs méthodes d'évaluation pour estimer la qualité des positions sur le plateau. Ces évaluations permettent à l'IA de choisir ses coups de manière stratégique en fonction de la situation sur le terrain. Ce fichier constitue le cœur de l'IA dans le jeu Othello, lui permettant de prendre des décisions compétitives et de jouer contre un humain ou une autre IA.


## 📝 Explication du fichier `main_othello.c`

Ce fichier implémente le programme principal pour jouer à Othello (Reversi) en mode réseau, en se connectant à un serveur pour jouer contre un autre joueur humain ou une IA. Le programme utilise plusieurs fonctions externes, notamment celles définies dans les fichiers `fonction_othello.h`, `main_othello.h`, `MinMax.h` et `userNetwork.h`, pour gérer le jeu, l'interface réseau et les stratégies d'intelligence artificielle. Voici une explication détaillée des parties principales du fichier.

### Initialisation et Authentification

- **Variables globales :**
  - `V`, `D`, `nulle` : Compteurs pour les victoires, défaites et nuls.
  - `grille[8][8]` : Tableau représentant le plateau de jeu.
  - `best[2]` : Tableau contenant les coordonnées du meilleur coup calculé par l'IA.
  - `g` : Pointeur vers une structure représentant une partie de jeu (`game`).

- **Authentification auprès du serveur :**
  - Le programme commence par allouer une nouvelle partie en utilisant la fonction `allocateGameOthello()`.
  - Ensuite, il récupère l'ID utilisateur, l'adresse IP et le mot de passe depuis les arguments de ligne de commande. Si ces informations ne sont pas fournies, une erreur est affichée et le programme se termine.
  - Le programme s'enregistre auprès du serveur en appelant la fonction `registerGameOthello()`. Si l'enregistrement échoue, le programme se termine.
  - La fonction `startGameOthello()` est appelée pour commencer la partie. Elle est bloquante et attend un adversaire pour commencer le jeu.

### Boucle de Jeu

Le jeu fonctionne de manière asynchrone avec un adversaire (soit un humain, soit une IA) qui joue à tour de rôle. La boucle de jeu se poursuit tant que l'état de la partie est "en cours" (`g->state == PLAYING`) et que l'entrée de l'utilisateur n'atteint pas la fin du fichier (`feof(stdin)`).

- **Attente du coup de l'adversaire :**
  Si ce n'est pas le tour du joueur local (déterminé par la comparaison de `g->myColor` et `g->currentPlayer`), le programme attend un mouvement de l'adversaire en appelant `waitMoveOthello(g)`. Si un mouvement est reçu, il est vérifié et appliqué avec la fonction `coup_valide()`, qui vérifie si le coup est valide sur le plateau.

- **Calcul du coup de l'IA :**
  Si c'est le tour du joueur local, le programme utilise la fonction `numberone()` pour calculer le meilleur coup possible en fonction de l'algorithme MinMax (défini dans les fichiers `MinMax.h`). Cette fonction est appelée pour générer le meilleur mouvement en analysant la grille et les positions possibles.

  - Si un coup valide est trouvé, il est joué en appelant `coup_valide()`.
  - Le coup est ensuite envoyé à l'adversaire via la fonction `doMoveOthello()`, qui transmet le coup au serveur.

### Fin de Partie

Une fois que le jeu se termine (lorsque l'état de la partie n'est plus "en cours"), le programme affiche le statut final du jeu (`g->state`) et met à jour les compteurs des victoires (`V`), des défaites (`D`) et des égalités (`nulle`). Le jeu est ensuite libéré avec `freeGameOthello(g)`.

### Conclusion

Ce fichier constitue le cœur de l'application de jeu Othello en réseau. Il gère la connexion au serveur, l'authentification, l'échange de coups avec l'adversaire, ainsi que l'implémentation de la logique de jeu pour un joueur humain ou une IA utilisant l'algorithme MinMax. Il permet de jouer à Othello de manière interactive et compétitive contre un autre joueur en ligne.

## 💻 Utilisation du code avec le Makefile

### Prérequis
Avant de pouvoir compiler et exécuter le programme, assurez-vous que les outils nécessaires sont installés sur votre machine :
- **GCC** : Le compilateur C de GNU.
- **Make** : L'outil d'automatisation de la compilation.

### Compilation du projet

Le `Makefile` fourni permet de compiler les différentes parties du projet de manière simple et rapide. Pour compiler le projet, il vous suffit d'exécuter la commande suivante dans votre terminal :

```bash
make
```

## Conclusion

Dans le cadre de ce projet, notre professeur a organisé un tournoi interne au sein de nos groupes de TP, lors duquel chaque étudiant a développé son IA pour participer. Nous avons mis en place un système de match entre toutes les IA, permettant de tester la robustesse et l'efficacité de chaque stratégie implémentée. Après de nombreuses parties intenses, notre IA a remporté le tournoi, prouvant ainsi la solidité et l'efficacité de notre approche Minimax avec élagage alpha-bêta.

Ce projet nous a permis non seulement d'approfondir nos connaissances en algorithmie, en intelligence artificielle et en programmation réseau, mais aussi de travailler de manière collaborative et compétitive, tout en développant un jeu complet et interactif.

Nous sommes fiers de cette réalisation et de notre victoire dans ce tournoi ! 🎉