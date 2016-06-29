#ifndef __MATRICE_H_INCLUDED__
#define __MATRICE_H_INCLUDED__

#include "element.h"
#include "timer.h"


/* définition d'un type matrice carrée linéaire en mémoire
   n étant la taille de la matrice */
typedef struct{
	int n;
	Element *donnees;
}matrice;

/**************************** fonctions de manipulation de nos matrices *************************/

/*  fonction allouant une matrice de taille nxn en mémoire 
    et renvoyant cette dernière
	si l'allocation n'a pas pu se faire, la fonction renvoie NULL */
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



/***************************** opérations sur les matrices ******************************/


/* fonction réalisant le produit matriciel de a avec b et stockant le résultat dans c */
void produit_matriciel(matrice a,matrice b,matrice c,Timer *t);

#endif
