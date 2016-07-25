#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "timer.h"
#include "matrice.h"



/* programme principal réalisant le produit de deux matrices carrées de mêmes dimensions et affichant le temps de calcul 
   il prend 3 arguments, 1) la taille des matrices, 2) Run_ID, 3) le nom du fichier résultat */
int main(int argc, char *argv[]){
	int n, run_id;
	matrice A, B, C;
	Timer *t;
	FILE* fichier = NULL;
	
	
	if(argc != 4){
		printf("Syntaxe: ./run taille_matrice run_ID nom_fichier_resultat\n");
		exit(1);
	}

	/* ouverture du fichier résultat */
	fichier = fopen(argv[3], "a");
	if (fichier == NULL){
		printf("Ouverture du fichier %s impossible\n", argv[3]);
		exit(1);
	}

	/* récupèration de nos paramètres */
	n = atoi(argv[1]); 
	run_id = atoi(argv[2]);

	srand(time(NULL)); //initialisation pour Timer
	
	
	/* Allocation de nos matrices */
    	A = allocation_matrice_alignee(n);
	B = allocation_matrice_alignee(n);
	
	/* initialisation de la matrice a avec des éléments aléatoires */
	initialiser_matrice(A);
	
	/* initialisation de la matrice b avec des éléments aléatoires */
    	initialiser_matrice(B);


	/* on initialise notre timer */
	t = initialiserTimer();

	
	/* allocation de la matrice résultat */
	C = allocation_matrice_alignee(n);
	

	/* test de validité de la matrice résultat */
	if (est_matrice_valide(C)){
		printf("Allocation de la matrice resultat impossible\n");
		exit(1);
	}

	
	/* calcul du produit a*b */
	produit_matriciel_transposee(A,B,C,t);

	
    	/* affichage du temps de calcul dans le fichier résultat */
	fprintf(fichier, "%d;%d;%lg\n",n,run_id,getTimerValue(t));

	/* on libère notre timer */
	freeTimer(t);


	/* on libère la matrice résultat */
	liberer_matrice(C);	
	
	/* on libere les matrices precedemment declarées */
	liberer_matrice(A); liberer_matrice(B);

	fclose(fichier);
	
	return(0);
}

		
		
		
		
		
	
