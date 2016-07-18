#ifndef __MATRICE_H_INCLUDED__
#define __MATRICE_H_INCLUDED__

#include "element.h"
#include "timer.h"


/* définition d'un type matrice carrée linéaire en mémoire
   n étant la taille de la matrice
   donnees étant le pointeur vers le début de la matrice
   debut_mem le pointeur vers le premier élément ayant été alloué, debut_mem <= donnees
*/
typedef struct{
	Element *donnees;
	Element *debut_mem;
	int n;
	
}matrice;




/*************************************************** Partie concernant les matrices par bloc *****************************************/

/* définition du type bloc pour le produit matriciel
   taille_mat étant la taille de la matrice contenant le bloc */
typedef struct{
	Element *donnees;
	int lignes_bloc,colonnes_bloc,taille_mat;
}bloc;


/* Fonction allouant en mémoire un tableau de blocs et renvoyant un pointeur vers le debut de celui-ci */
bloc *allocation_tab_blocs(int n);


void liberer_blocs(bloc *tab);



/* Fonction assignant au bloc (i,j) le pointeur vers l'adresse correspondante de la matrice m */
Element *pointeur_vers_bloc(int taille_bloc,int i,int j, matrice m);



/* fonction renvoyant le nombre de lignes du bloc b */
int lignes_bloc(bloc b);


/* fonction renvoyant le nombre de colonnes du bloc b */
int colonnes_bloc(bloc b);



/* fonction permettant de diviser la matrice m en plusieurs blocs carrés de taille b */
void diviser_matrice_en_blocs(bloc *tab, int b, matrice m, int nb_blocs_ligne);



/* fonction renvoyant un pointeur vers l'élément (i,j) du bloc b  */
Element *acces_bloc(bloc b, int i, int j);



/* fonction réalisant la multiplication des blocs a et b
   le résultat est dans le bloc c */
void mul_blocs(bloc a, bloc b, bloc c);



/* fonction réalisant le produit par blocs des matrices A et B et mesurant le temps de calcul */
void produit_matriciel_par_blocs(matrice A,matrice B,matrice C,Timer *t,int b);




/************************************************* fonctions de manipulation de nos matrices ******************************************/


/* fonction permettant d'aligner nos matrices sur un multiple de 64 */
Element *multiple_64(Element *ptr);




/*  fonction allouant une matrice linéaire de taille nxn en mémoire 
    et renvoyant cette dernière
	m.donnees est un multiple de 64
	si l'allocation n'a pas pu se faire, la fonction renvoie NULL */
matrice allocation_matrice_alignee(int n);


/* identique à la fonction allocation_matrice_alignee sauf que m.donnees n'est pas forcément un multiple de 64 */
matrice allocation_matrice(int n);



/* fonction libérant une matrice précedemment
   allouée en mémoire à l'aide de l'instruction
   "malloc" */
void liberer_matrice(matrice m);
		
	
/* fonction renvoyant la taille de la matrice m */	
int taille_matrice(matrice m);	


/* fonction renvoyant 0 si la matrice est valide, 1 sinon */
int est_matrice_valide(matrice m);


/* fonction renvoyant un pointeur vers l'élément (i,j) de la matrice m */
Element *acces_matrice(matrice m, int i, int j);


/* fonction affichant à l'écran la matrice m */
void affiche_matrice(matrice m);


/* assigne une valeur aléatoire à tous les éléments de la matrice m */
void initialiser_matrice(matrice m);

/* assigne la valeur n à tous les éléments de la matrice m */
void initialiser_matrice_variable(matrice m,double n);


/* Realise la transposée de la matrice m, permet un gain de temps lors du produit matriciel */
void transpose_matrice(matrice m);



/* fonction renvoyant 1 si les matrices sont différentes, 0 sinon */
int comparer_matrice(matrice A, matrice B);



/******************************************* opérations sur les matrices *************************************************/




/* fonction réalisant le produit matriciel de a avec b et stockant le résultat dans c */
void produit_matriciel(matrice a,matrice b,matrice c,Timer *t);


/* fonction réalisant le produit matriciel de a avec la transposee de b et stockant le résultat dans c */
void produit_matriciel_transposee(matrice a,matrice b,matrice c,Timer *t);



#endif
