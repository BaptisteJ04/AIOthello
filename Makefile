jothello: fonction_othello.o main.o MinMax.o
	gcc fonction_othello.o main.o MinMax.o -o jothello -Wall -Werror -g -O0 -L. -lothello

fonction_othello.o:fonction_othello.c fonction_othello.h
	gcc -c fonction_othello.c  -o fonction_othello.o -Wall -Werror -g -O0 

main.o:main_othello.c main_othello.h
	gcc -c main_othello.c -o main.o -Wall -Werror -g -O0 

MinMax.o:MinMax.c MinMax.h
	gcc -c MinMax.c -o MinMax.o -Wall -Werror -g -O0 

arbre: class_Arbre.c
	gcc class_Arbre.c -o arbre -Wall -Werror -g -O0 && ./arbre

clean: 
	rm *.o
