#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "matrice.h"
#include "element.h"
#include "timer.h" 


/**************************** fonctions de manipulation de nos matrices *************************/

matrice allocation_matrice(int n){
	matrice m={0,0,NULL};

	m.donnees = malloc(n*n*sizeof(Element));
	if (m.donnees != NULL){
	    m.n = n;
	}

	return(m);
}


void liberer_matrice(matrice m){
	free(m.donnees);
	m.n = 0;
}


int taille_matrice(matrice m){
	return m.n;
}


int est_matrice_valide(matrice m){
	return (taille_matrice(m) == 0);
}


Element *acces_matrice(matrice m, int i, int j){
    Element *resultat = NULL;

	resultat = m.donnees;
	resultat += (i*taille_matrice(m))+j;

	return(resultat);
}


void affiche_matrice(matrice m){
	int i,j;

	printf("[");
	for(i=0; i<taille_matrice(m);i++){
		for(j=0; j<taille_matrice(m);j++){
			printf(" %lg,", *acces_matrice(m,i,j));
		}
		printf("\n");
	}
	printf("]\n");
}


void initialiser_matrice(matrice m){
	int i,j;
	srand(time(NULL));
	for(i=0; i<taille_matrice(m); i++){
		for(j=0; j<taille_matrice(m); j++){
		    *acces_matrice(m,i,j) = randomElement();
		}
    }
}



/***************************** opérations sur les matrices ******************************/



void produit_matriciel(matrice a,matrice b,matrice c,Timer *t){
	int i,j,k;
	Element *resultat;
	
	startTimer(t); //on lance le timer au début du calcul
	
    /* calcul de l'élément c(i,j) */
	  #pragma omp parallel for default(none)		\
	    shared(a,b,c) private(i,j,k,resultat) 
	for(i=0; i<taille_matrice(c); i++){
		for(j=0; j<taille_matrice(c); j++){
	    	resultat = acces_matrice(c, i, j);
			for(k=0; k<taille_matrice(a); k++){
				*resultat += (*acces_matrice(a,i,k))*(*acces_matrice(b,k,j));
			}
		}
	} /* fin de la zone parallèle */

	stopTimer(t); //on arrête le timer à la fin du calcul
}

	
