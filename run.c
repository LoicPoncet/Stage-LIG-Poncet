#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "timer.h"
#include "matrice.h"



/* programme principal réalisant le produit de deux matrices carrées de mêmes dimensions et affichant le temps de calcul */
int main(int argc, char *argv[]){
	int n,run_id;
	matrice a, b, c;
	Timer *t;
	FILE* fichier = NULL;
	
	if(argc != 4){
		printf("Syntaxe: ./run taille_matrice run_ID nom_fichier_resultat\n");
		exit(1);
	}

	fichier = fopen(argv[3], "a");
	if (fichier == NULL){
		printf("Ouverture du fichier %s impossible\n", argv[3]);
		exit(1);
	}

	n = atoi(argv[1]);
	run_id = atoi(argv[2]);
	
	/* Allocation de nos matrices */
    a = allocation_matrice(n);
	b = allocation_matrice(n);
	
	/* initialisation de la matrice a avec des éléments aléatoires */
	initialiser_matrice(a);
	
	/* initialisation de la matrice b avec des éléments aléatoires */
    initialiser_matrice(b);

	/* on initialise notre timer */
	t = initialiserTimer();


	/* allocation de la matrice résultat */
	c = allocation_matrice(n);

	/* test de validité de la matrice résultat */
	if (est_matrice_valide(c)){
		printf("Allocation de la matrice resultat impossible\n");
		exit(1);
	}
	
	/* calcul du produit a*b */
	produit_matriciel(a,b,c,t);
		
    /* affichage du temps de calcul dans le fichier résultat */
	fprintf(fichier, "\n%d;%d;%lg",n,run_id,getTimerValue(t));

	/* on libère notre timer */
	freeTimer(t);

	/* on libère la matrice résultat */
	liberer_matrice(c);	
	
	/* on libere les matrices precedemment declarées */
	liberer_matrice(a); liberer_matrice(b);

	fclose(fichier);
	
	return(0);
}

		
		
		
		
		
	
