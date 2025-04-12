#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonction_othello.h"
#include "main_othello.h"
#include "MinMax.h"
#include "userNetwork.h" 

#define BLACK 1 

int main(int argc,char *argv[]){
int V=0;
int nulle=0;
int D=0;
//while(true){
    int grille[8][8];
    init_grille(grille);
    int best[2];
    game *g;
    int move; 

	if ((g=allocateGameOthello()) == NULL ) { return(EXIT_FAILURE); }

	if (argc > 3 ) { 
		g->userId=atoi(argv[3]); 
		g->address=argv[2]; 
	}
	else { fprintf(stderr,"usage : %s <userPasswd> <ip ad> <userId>\n",argv[0]); exit(-1); }

	g->port=8080; //par exemple

	if (registerGameOthello(g,argv[1]) < 0 ) { exit(-1); }	// test de l'authentification auprès du serveur 

	if (startGameOthello(g) < 0 ) { // cet appel est bloquant en attendant un adversaire 
		fprintf(stderr,"error Starting Game\n"); 
		return (EXIT_FAILURE); 
	}
	printf("I am player %s\n",(g->myColor==BLACK)?"Black":"White"); 

	// debut de partie
	while (g->state == PLAYING && !feof(stdin)) {
	 	if (g->myColor != g->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(g)) == 0 ) {
				printf("Game status %d: \t",g->state); 
				if (g->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8); 
                    coup_valide(grille,g->move%8,g->move/8,g->currentPlayer);
				}
			}
		}
	 	else { 		
			g->move=65; // si scanf correct cette valeur est modifiée, sinon cela terminera la partie. 
			// recuperation du coup sur stdin 
			best[0]=0;
			best[1]=8;
			numberone(best,grille,g->currentPlayer,g->currentPlayer,0);
			if(best[2]!=8) coup_valide(grille,best[0],best[1],g->currentPlayer);
			g->move=best[1]*8+best[0];
			print_grille(grille);
			printf("playing move %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8);
			doMoveOthello(g);	// envoie du coup à l'adversaire 
	   	}
		g->currentPlayer=!g->currentPlayer; 
	} 
	// fin de partie 
	printf("Final game status = %d\n",g->state); 
	if(g->state==3){
		V++;
	}
	else if(g->state==4){
		D++;
	}
	else{
		nulle++;
	}
	printf("V:%d\nD:%d\nN:%d\n",V,D,nulle);
	freeGameOthello(g);
//}
	return 0; 
}