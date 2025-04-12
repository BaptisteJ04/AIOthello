#include <stdbool.h>

#define N 8

void init_grille(int mat[N][N]);

void print_grille(int mat[N][N]);

bool coup_valide(int mat[N][N], int line, int col, int player);

bool evolution_grille(int mat[N][N], int line, int col,int player);

bool test_valide(int mat[N][N],int player,int x, int y,int i,int a,int b);