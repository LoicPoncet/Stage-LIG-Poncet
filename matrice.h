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
	int n;
	Element *donnees;
	Element *debut_mem;
}matrice;

/* définition du type bloc pour le produit matriciel récursif */
typedef matrice bloc;  


/* fonction permettant d'aligner nos matrices sur un multiple de 64 */
Element *multiple_64(Element *ptr);



/**************************** fonctions de manipulation de nos matrices *************************/

/*  fonction allouant une matrice de taille nxn en mémoire 
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


/* Realise la transposée de la matrice m, permet un gain de temps lors du produit matriciel */
void transpose_matrice(matrice m);



/***************************** opérations sur les matrices ******************************/


/* fonction réalisant le produit matriciel de a avec b et stockant le résultat dans c */
void produit_matriciel(matrice a,matrice b,matrice c,Timer *t);

/* fonction réalisant le produit matriciel de a avec la transposee de b et stockant le résultat dans c */
void produit_matriciel_transpose(matrice a,matrice b,matrice c,Timer *t);


/* fonction réalisant le produit matriciel de a avec b en utilisant un algorithme récursif 
pré-condition: la taille des matrices de départ doit être une puissance de 2 */
//void produit_matriciel_recursif(matrice a,matrice b,matrice c);

#endif
