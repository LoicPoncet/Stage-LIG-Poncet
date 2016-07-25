#!/bin/bash

# script réalisant le produit de matrices par blocs et prenant 6 arguments
# $1 taille de matrice
# $2 taille de blocs de départ
# $3 taille d'incrémentation des blocs
# $4 taille de blocs d'arrivée
# $5 nombre d'exécution par taille de blocs
# $6 nom du fichier résultat

for ((i = $2; i <= $4; i += $3));
do
	for j in `seq 1 $5`;
	do
		./run_blocs $1 $i $j ~/Stage-LIG-Poncet/Mesures/Blocs/$6
	done
done    
