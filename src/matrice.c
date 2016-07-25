#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "matrice.h"
#include "element.h"
#include "timer.h"

#ifdef _OPENMP
    #include <omp.h>
    #define threshold_omp 30 //taille de matrice à partir de laquelle il est plus judicieux d'exécuter le programme en parallèle
#endif




/*************************************************** Partie concernant les matrices par blocs *****************************************/



bloc *allocation_tab_blocs(int n){
	return((bloc *)malloc(n*sizeof(bloc)));
}


void liberer_blocs(bloc *tab){
	free(tab);
}	



int lignes_bloc(bloc b){
	return (b.lignes_bloc);
}



int colonnes_bloc(bloc b){
	return(b.colonnes_bloc);
}



void diviser_matrice_en_blocs(bloc *tab, int b, matrice m,int nb_blocs_ligne){
	int i = 0, j;
	int multiple;
	Element *ptr;

	multiple = ((taille_matrice(m)%b) == 0); // multiple = 1 si la taille de nos matrices est un multiple de la taille de nos blocs

	while(i<nb_blocs_ligne){
		j = 0;
		ptr = acces_matrice(m,i*b,0);
		while(j<nb_blocs_ligne){
			/* on traite les différents cas possibles */

			if(multiple || ((i != nb_blocs_ligne-1) && (j != nb_blocs_ligne-1))){
				tab[i*nb_blocs_ligne+j].lignes_bloc = b;
				tab[i*nb_blocs_ligne+j].colonnes_bloc = b;
			}
			else if((i == nb_blocs_ligne-1) && (j == nb_blocs_ligne-1)){
				tab[i*nb_blocs_ligne+j].lignes_bloc = taille_matrice(m)%b;
				tab[i*nb_blocs_ligne+j].colonnes_bloc = taille_matrice(m)%b;
			}
			else if(i == nb_blocs_ligne-1){
				tab[i*nb_blocs_ligne+j].lignes_bloc = taille_matrice(m)%b;
				tab[i*nb_blocs_ligne+j].colonnes_bloc = b;
			}
			else{
				tab[i*nb_blocs_ligne+j].lignes_bloc = b;
				tab[i*nb_blocs_ligne+j].colonnes_bloc = taille_matrice(m)%b;
			}

			tab[i*nb_blocs_ligne+j].taille_mat = taille_matrice(m);
			tab[i*nb_blocs_ligne+j].donnees = ptr;
			
			ptr += b;
			j++;
		}
		i++;   
	}
}


Element *acces_bloc(bloc b, int i, int j){
	Element *resultat;

	resultat = b.donnees;
	resultat += i*b.taille_mat + j;
	return(resultat);
}	



void mul_blocs(bloc a, bloc b, bloc c){
	int i,j,k;
	Element *ptr;

	/* algorithme classique */
	for(i=0; i<lignes_bloc(a); i++){
		for(j=0; j<colonnes_bloc(b); j++){
			ptr = acces_bloc(c,i,j);
			for(k=0; k<colonnes_bloc(a); k++){
				*ptr += (*acces_bloc(a,i,k))*(*acces_bloc(b,k,j));
			}
		}
	}	
}


void mul_blocs_transposee(bloc a, bloc b, bloc c){
	int i,j,k;
	Element *ptr;

	/* algorithme transposée */
	for(i=0; i<lignes_bloc(a); i++){
		for(j=0; j<colonnes_bloc(b); j++){
			ptr = acces_bloc(c,i,j);
			for(k=0; k<colonnes_bloc(a); k++){
				*ptr += (*acces_bloc(a,i,k))*(*acces_bloc(b,j,k));
			}
		}
	}	
}	




void produit_matriciel_par_blocs(matrice A,matrice B,matrice C,Timer *t,int b){
	bloc *tab_bloc_a, *tab_bloc_b, *tab_bloc_c;
	int bi,bj,bk;
	int nb_blocs_ligne;
	

	nb_blocs_ligne = taille_matrice(C)/b;
	// dans le cas où notre taille de blocs ne serait pas un diviseur de la taille de nos matrices on incrémente nb_blocs_ligne
	if ((taille_matrice(C)%b) != 0){
		nb_blocs_ligne++;
	}

	// allocations de nos tableaux de blocs en mémoire
	tab_bloc_a = allocation_tab_blocs(nb_blocs_ligne*nb_blocs_ligne);
	if (tab_bloc_a == NULL){
		printf("L'allocation du bloc a échoué\n");
		exit(1);
	}	

	tab_bloc_b = allocation_tab_blocs(nb_blocs_ligne*nb_blocs_ligne);
	if (tab_bloc_a == NULL){
		printf("L'allocation du bloc a échoué\n");
		exit(1);
	}
	
	tab_bloc_c = allocation_tab_blocs(nb_blocs_ligne*nb_blocs_ligne);
	if (tab_bloc_a == NULL){
		printf("L'allocation du bloc a échoué\n");
		exit(1);
	}

	transpose_matrice(B);
	
	// division de nos matrices en un maximum de blocs de taille b puis si besoin des blocs plus petits
	diviser_matrice_en_blocs(tab_bloc_a,b,A,nb_blocs_ligne);
	diviser_matrice_en_blocs(tab_bloc_b,b,B,nb_blocs_ligne);
	diviser_matrice_en_blocs(tab_bloc_c,b,C,nb_blocs_ligne);

	startTimer(t); //on lance le timer

	// calcul du bloc (bi,bj) de la matrice résultat
#pragma omp parallel for num_threads(4) default(none) schedule(static) \
		 shared(tab_bloc_a,tab_bloc_b,tab_bloc_c,nb_blocs_ligne) private(bi,bj,bk)
	for(bi = 0; bi < nb_blocs_ligne; bi++){
		for(bj = 0; bj < nb_blocs_ligne; bj++){
			for(bk = 0; bk < nb_blocs_ligne; bk++){
				mul_blocs_transposee(tab_bloc_a[bi*nb_blocs_ligne+bk], tab_bloc_b[bj*nb_blocs_ligne+bk], tab_bloc_c[bi*nb_blocs_ligne+bj]);
			}
		}
	} // fin de la zone parallèle


	stopTimer(t); // on arrête le timer à la fin du calcul

	liberer_blocs(tab_bloc_a);
	liberer_blocs(tab_bloc_b);
	liberer_blocs(tab_bloc_c);
}	



/**************************** fonctions de manipulation de nos matrices *************************/



Element *multiple_64(Element *ptr){ 
	while((uint64_t)ptr % 64 != 0){
		ptr++;
	}
	return ptr;
}




matrice allocation_matrice_alignee(int n){
	matrice m={NULL,NULL,0};
	Element *ptr;
	
	m.debut_mem = (Element *)malloc(n*n*sizeof(Element)+64);
	if (m.debut_mem != NULL){
	    m.n = n;
		ptr = multiple_64(m.debut_mem);
		m.donnees = ptr;
		m.donnees = m.debut_mem;
	}

	return(m);
}

matrice allocation_matrice(int n){
	matrice m={NULL,NULL,0};
	
	m.debut_mem = (Element *)malloc(n*n*sizeof(Element)+64);
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

	#pragma omp parallel for default(none) schedule(static)	\
		 shared(m) private(i,j)
	for(i=0; i<taille_matrice(m); i++){
		for(j=0; j<taille_matrice(m); j++){
		    *acces_matrice(m,i,j) = randomElement();
		}
    }
}


void initialiser_matrice_variable(matrice m,double n){
	int i,j;

	#pragma omp parallel for default(none) schedule(static)	\
		shared(m,n) private(i,j)
	for(i=0; i<taille_matrice(m); i++){
		for(j=0; j<taille_matrice(m); j++){
		    *acces_matrice(m,i,j) = n;
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
    


int comparer_matrice(matrice A, matrice B){
	int i,j,resultat=0;

	if (taille_matrice(A) != taille_matrice(B)){
		printf("Tailles différentes\n");
		exit(1);
	}

	for(i=0;i<taille_matrice(A);i++){
		for(j=0;j<taille_matrice(A);j++){
			if ((*acces_matrice(A,i,j)) != (*acces_matrice(B,i,j))){
				resultat = 1;
			}
		}
	}

	return(resultat);
}	



	

    
	
	
			



/***************************** opérations sur les matrices ******************************/



void produit_matriciel(matrice a,matrice b,matrice c,Timer *t){
	int i,j,k;
	Element *resultat;
	
	startTimer(t); //on lance le timer au début du calcul
	
    /* calcul de l'élément c(i,j) */
    #pragma omp parallel for if(taille_matrice(c) > threshold_omp)	\
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



void produit_matriciel_transposee(matrice a,matrice b,matrice c,Timer *t){
	int i,j,k;
	Element *resultat;
	
	startTimer(t); //on lance le timer au début du calcul

	transpose_matrice(b); //on transpose la matrice b afin d'ameliorer les performances

     /* calcul de l'élément c(i,j) */
     #pragma omp parallel for if(taille_matrice(c) > threshold_omp) \
	    default(none) schedule(dynamic) \
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

	transpose_matrice(b); //on la transpose de nouveau au cas où il y'aurait besoin d'effecter d'autres calculs dessus
}




		
		
