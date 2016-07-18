#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "timer.h"
#include "matrice.h"



/* programme principal réalisant le produit par blocs de deux matrices carrées de mêmes dimensions et affichant le temps de calcul 
   il prend 4 arguments, 1) la taille des matrices, 2) la taille de nos blocs, 3) Run_ID, 4) le nom du fichier résultat */
int main(int argc, char *argv[]){
	int b, n, run_id;
	matrice A, B, C;
	Timer *t;
	FILE* fichier = NULL;
	
	
	if(argc != 5){
		printf("Syntaxe: ./run taille_matrice nombre_de_blocs run_ID nom_fichier_resultat\n");
		exit(1);
	}

	/* ouverture du fichier résultat */
	fichier = fopen(argv[4], "a");
	if (fichier == NULL){
		printf("Ouverture du fichier %s impossible\n", argv[4]);
		exit(1);
	}

	n = atoi(argv[1]); // on récupère la taille des matrices
	b = atoi(argv[2]); // on récupère la taille de nos blocs
	run_id = atoi(argv[3]);


    srand(time(NULL));
	
	
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
	initialiser_matrice_variable(C,0);
	

	/* test de validité de la matrice résultat */
	if (est_matrice_valide(C)){
		printf("Allocation de la matrice resultat impossible\n");
		exit(1);
	}

	
	/* calcul du produit a*b */
	produit_matriciel_par_blocs(A,B,C,t,b);

	
    /* affichage du temps de calcul dans le fichier résultat */
	fprintf(fichier, "%d;%d;%d;%lg\n",n,b,run_id,getTimerValue(t));

	/* on libère notre timer */
	freeTimer(t);


	/* on libère la matrice résultat */
	liberer_matrice(C);	
	
	/* on libere les matrices precedemment declarées */
	liberer_matrice(A); liberer_matrice(B);

	fclose(fichier);
	
	return(0);
}
