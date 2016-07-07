#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "matrice.h"
#include "element.h"
#include "timer.h"

#ifdef _OPENMP
    #include <omp.h>
    #define threshold_omp 30 //valeur à partir de laquelle il est plus judicieux d'exécuter le programme en parallèle
#endif



Element *multiple_64(Element *ptr){ 
	while((uint64_t)ptr % 64 != 0){
		ptr++;
	}
	return ptr;
}


/**************************** fonctions de manipulation de nos matrices *************************/

matrice allocation_matrice_alignee(int n){
	matrice m={0,NULL,NULL};
	Element *ptr;
	
	m.debut_mem = (Element *) malloc(n*n*sizeof(Element)+64);
	if (m.debut_mem != NULL){
	    m.n = n;
		ptr = multiple_64(m.debut_mem);
		m.donnees = ptr;
		m.donnees = m.debut_mem;
	}

	return(m);
}

matrice allocation_matrice(int n){
	matrice m={0,NULL,NULL};
	
	m.debut_mem = (Element *) malloc(n*n*sizeof(Element)+64);
	if (m.debut_mem != NULL){
	    m.n = n;
		m.donnees = m.debut_mem;
	}

	return(m);
}


void liberer_matrice(matrice m){
	free(m.debut_mem);
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
	
	for(i=0; i<taille_matrice(m); i++){
		for(j=0; j<taille_matrice(m); j++){
		    *acces_matrice(m,i,j) = randomElement();
		}
    }
}


void transpose_matrice(matrice m){
	double tmp = ZERO_ELEMENT;
	int i,j;

	#pragma omp parallel for default(none) schedule(static)	\
		 shared(m) private(i,j,tmp) 
	for(i=0; i<taille_matrice(m); i++){
		for(j=i;j<taille_matrice(m);j++){
			tmp = *acces_matrice(m,i,j);
			*acces_matrice(m,i,j) = *acces_matrice(m,j,i);
			*acces_matrice(m,j,i) = tmp;
		}
	}
}	
			



/***************************** opérations sur les matrices ******************************/



void produit_matriciel(matrice a,matrice b,matrice c,Timer *t){
	int i,j,k;
	Element *resultat;
	
	startTimer(t); //on lance le timer au début du calcul
	
    /* calcul de l'élément c(i,j) */
#pragma omp parallel for if(taille_matrice(c) > threshold_omp) \
	     default(none) schedule(static) \
		 shared(a,b,c) private(i,j,k,resultat) 
	for(i=0; i<taille_matrice(c); i++){
		for(j=0; j<taille_matrice(c); j++){
			resultat = acces_matrice(c, i, j);
			*resultat = 0;
			for(k=0; k<taille_matrice(c); k++){
				*resultat += (*acces_matrice(a,i,k))*(*acces_matrice(b,k,j));
			}
		}
	} /* fin de la zone parallèle */

	stopTimer(t); //on arrête le timer à la fin du calcul
}


void produit_matriciel_transpose(matrice a,matrice b,matrice c,Timer *t){
	int i,j,k;
	Element *resultat;
	
	startTimer(t); //on lance le timer au début du calcul

	transpose_matrice(b); //on transpose la matrice b afin d'ameliorer les performances

     /* calcul de l'élément c(i,j) */
     #pragma omp parallel for if(taille_matrice(c) > threshold_omp) \
	    default(none) schedule(static) \
	    shared(a,b,c) private(i,j,k,resultat) 
	for(i=0; i<taille_matrice(c); i++){
		for(j=0; j<taille_matrice(c); j++){
			resultat = acces_matrice(c, i, j);
			*resultat = 0;
			for(k=0; k<taille_matrice(c); k++){
				*resultat += (*acces_matrice(a,i,k))*(*acces_matrice(b,j,k));
			}
		}
	} /* fin de la zone parallèle */

	stopTimer(t); //on arrête le timer à la fin du calcul
}
	

	
