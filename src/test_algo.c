#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "timer.h"


/* 
   Programme permettant de comparer les résultats obtenus avec les différents algos, affiche un message à l'écran si les résultats diffèrent 
   Les deux arguments nécessaires sont 1) la taille des matrices; 2) la taille des blocs pour l'algorithme de calcul par blocs. 
*/

int main(int argc, char *argv[]){
	int b, n;
	matrice A, B, TEST1, TEST2, TEST3;
	Timer *t;

	if(argc != 3){
		printf("syntaxe: ./test taille_matrice taille_blocs\n");
		exit(1);
	}

	/* on récupère nos paramètres  */
	n = atoi(argv[1]);
	b = atoi(argv[2]);

	/* Allocation de nos matrices */
    A = allocation_matrice(n);
	B = allocation_matrice(n);

	TEST1 = allocation_matrice(n);
	initialiser_matrice_variable(TEST1,0);

	TEST2 = allocation_matrice(n);
	initialiser_matrice_variable(TEST2,0);

	TEST3 = allocation_matrice(n);
	initialiser_matrice_variable(TEST3,0);
	
	/* initialisation de la matrice a avec des éléments aléatoires */
	initialiser_matrice(A);
	
	/* initialisation de la matrice b avec des éléments aléatoires */
    initialiser_matrice(B);


	/* on initialise notre timer (obsolète ici) */
	t = initialiserTimer();

	produit_matriciel(A,B,TEST1,t);

	produit_matriciel_transposee(A,B,TEST2,t);
	
	/* calcul du produit a*b */
	produit_matriciel_par_blocs(A,B,TEST3,t,b);

	if(comparer_matrice(TEST1,TEST2) || comparer_matrice(TEST2,TEST3)){
		printf("L'un des algos est incorrect!\n");
	}	


	/* on libère notre timer */
	freeTimer(t);

	/* on libère les matrices résultat */
	liberer_matrice(TEST3);
	liberer_matrice(TEST2);
	liberer_matrice(TEST1);
	
	/* on libere les matrices precedemment declarées */
	liberer_matrice(A); liberer_matrice(B);
	
	return(0);
}	
