#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonction_othello.h"
#include "main_othello.h"
#include "MinMax.h"

#define DEPTH 7

void numberone(int best[2],int grille[8][8],int joueur,int curent,int profondeur){
    int score;
    int max;
    int p[8][8];
    max= -9999;
    for(int line=0;line<=7;line++){
        for(int col=0;col<=7;col++){
            copie(grille,p);
            if(coup_valide(p,line,col,curent)){
                score = inter(p,joueur,(curent+1)%2,profondeur+1,-9999,9999);
                if(score>max){
                    max=score;
                    best[0]=line;
                    best[1]=col;
                }
            }
        }
    }
    if(max == -9999){
        max = inter(p,joueur,(curent+1)%2,profondeur+1,-9999,9999);
        best[0]=0;
        best[1]=8; 
    }
}


int inter(int grille[8][8],int joueur,int curent,int profondeur,int alpha,int beta){
    if(profondeur == DEPTH){
	    return evaluation_3(grille,joueur);
    }
    int score;
    int max;
    int p[8][8];
    if(joueur==curent){
        max= -9999;
        for(int line=0;line<=7;line++){
            for(int col=0;col<=7;col++){
                copie(grille,p);
                if(coup_valide(p,line,col,curent)){
                    score = inter(p,joueur,(curent+1)%2,profondeur+1,alpha,beta);
                    if(score>max){
                        max=score;
                    }
                    if(max>=beta)return max;
                    if(alpha<max)alpha=max;
                }
            }
        }
        if(max == -9999){
            max = inter(p,joueur,(curent+1)%2,profondeur+1,alpha,beta);
            if(max>=beta)return max;
            if(alpha<max)alpha=max;
        }
    }
    else if(joueur==(curent+1)%2){
        max= 9999;
        for(int line=0;line<=7;line++){
            for(int col=0;col<=7;col++){
                copie(grille,p);
                if(coup_valide(p,line,col,curent)){
                    score = inter(p,joueur,(curent+1)%2,profondeur+1,alpha,beta);
                    if(score<max){
                        max=score;  
                    }
                    if (alpha>=max) return max;
                    if(beta>max) beta = max;
                }
            }
        }
	
        if(max == 9999){
            max = inter(p,joueur,(curent+1)%2,profondeur+1,alpha,beta);
            if (alpha>=max) return max;
            if(beta<max) beta = max;
        }
    }
    return max;
}

int evaluation_1(int grille[8][8],int joueur){
    int eval=0;
    for(int line=0;line<8;line++){
        for(int col=0;col<8;col++){
            if(grille[line][col]==joueur){
                eval++;
            }
            if(grille[line][col]==(joueur+1)%2){
                eval--;
            }
        }
    }
    return eval;
}

void copie(int grille[8][8],int p[8][8]){
    for(int line=0;line<8;line++){
        for(int col=0;col<8;col++){
            p[line][col]=grille[line][col];
        }
    }
}

int evaluation_2(int grille[8][8],int joueur){
    int eval=0;
    int teval[8][8]={
	    {40,3,15,10,10,15,3,40},
	    {3,0,9,12,12,9,0,3},
	    {15,9,11,15,15,11,9,15},
	    {10,12,15,18,18,15,12,10},
	    {10,12,15,18,18,15,12,10},
	    {15,9,11,15,15,11,9,15},
	    {3,0,9,12,12,9,0,3},
	    {40,3,15,10,10,15,3,40}};
    for(int line=0;line<8;line++){
        for(int col=0;col<8;col++){
            if(grille[line][col]==joueur){
                eval=eval+teval[line][col];
            }
            else if(grille[line][col]==(joueur+1)%2){
                eval=eval-teval[line][col];
            }
        }
    }
    return eval;
}

int evaluation_3(int grille[8][8],int joueur){
    int eval2=0;
    int eval1 =0;
    int case_vide=0;
    int teval[8][8]={
    {40,1 ,15,10,10,15,1 ,40},
    {1 ,0 ,9 ,12,12,9 ,0 ,1 },
    {15,9 ,11,15,15,11,9 ,15},
    {10,12,15,18,18,15,12,10},
    {10,12,15,18,18,15,12,10},
    {15,9 ,11,15,15,11,9 ,15},
    {1 ,0 ,9 ,12,12,9 ,0 ,1} ,
    {40,1 ,15,10,10,15,1 ,40}};
    for(int line=0;line<8;line++){
        for(int col=0;col<8;col++){
            if(grille[line][col]==joueur){
                eval2=eval2+teval[line][col];
                eval1++;
            }
            else if(grille[line][col]==(joueur+1)%2){
                eval2=eval2-teval[line][col];
                eval1--;
            }
            else case_vide++;
        }
    }
    return (((case_vide)*eval2)+((60-case_vide)*eval1));
}
