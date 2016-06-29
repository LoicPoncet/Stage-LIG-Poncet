#!/bin/bash

# script réalisant le produit de matrices et prenant 5 arguments
# $1 taille de matrice de départ
# $2 valeur d'incrémentation de notre taille de matrice
# $3 taille de matrice d'arrivée
# $4 nombre d'exécution par taille de matrice
# $5 nom du fichier résultat

for i in `seq $1 $2 $3`;
do
	for j in `seq 1 $4`;
	do
		./run $i $j Mesures/$5
	done
done    
