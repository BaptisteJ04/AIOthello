#include <stdbool.h>

int evaluation_1(int grille[8][8],int joueur);
int evaluation_2(int grille[8][8],int joueur);
int evaluation_3(int grille[8][8],int joueur);

void copie(int grille[8][8],int p[8][8]);

void numberone(int best[2],int grille[8][8],int joueur,int current,int profondeur);
int inter(int grille[8][8],int joueur,int current,int profondeur,int alpha,int beta);