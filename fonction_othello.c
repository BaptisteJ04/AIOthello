#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonction_othello.h"
#include "main_othello.h"
#include "MinMax.h"


void init_grille(int mat[8][8]){
    for(int line = 0; line<8; line++){
        for(int col = 0; col<8; col++){
            mat[line][col] = 2;
        }
    }
    mat[3][3] = 0;
    mat[4][3] = 1;
    mat[3][4] = 1;
    mat[4][4] = 0;
}

void print_grille(int mat[8][8]){
    printf("\n  01234567\n  ________\n");
    for(int line = 0; line<8; line++){
        printf("%d|",line);
        for(int col = 0; col<N; col++){
           if(mat[col][line] == 2){
                printf(" ");
            }
            else if(mat[col][line] == 0){
                printf("\033[33m0");
            }
            else printf("\033[36m0");
            printf("\033[37m");
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

bool coup_valide(int mat[8][8], int line, int col, int player){
    if(line < 0 || col < 0 || line > 7 || col > 7) return false;
    if(mat[line][col] != 2) return false;
    if(!evolution_grille(mat, line, col, player)) return false;
    mat[line][col] = player;
    return true;
}


bool evolution_grille(int mat[8][8], int line, int col,int player){
    bool res_b = test_valide(mat,player,line+1,col,0,1,0);
    bool res_b_d = test_valide(mat,player,line+1,col+1,0,1,1);
    bool res_d = test_valide(mat,player,line,col+1,0,0,1);
    bool res_h_d = test_valide(mat,player,line-1,col+1,0,-1,1);
    bool res_h = test_valide(mat,player,line-1,col,0,-1,0);
    bool res_h_g = test_valide(mat,player,line-1,col-1,0,-1,-1);
    bool res_g = test_valide(mat,player,line,col-1,0,0,-1);
    bool res_b_g = test_valide(mat,player,line+1,col-1,0,1,-1);

    if(res_b || res_b_d || res_d || res_h_d || res_h || res_h_g || res_g || res_b_g){
        return true;
    }
    return false;
}

//On va tester toute la diagonale bas droite en partant de la premiere case en diag jusqu'à un autre de nos pion ou le vide

bool test_valide(int mat[8][8],int player,int x, int y,int i,int a,int b){
    if(x<0 || y<0 || x>7 || y>7 || mat[x][y]==2 ||(mat[x][y]==player && i==0)) return false;  //sort de la grille ou place vide 
    else if(mat[x][y]==player && i>0) return true;
    bool res = test_valide(mat,player,x+a,y+b,1,a,b);
    if(res){
        mat[x][y]=player;
    }
    return res;
}

