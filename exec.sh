#!/bin/bash

for i in `seq $1 $2 $3`;
do
	for j in `seq 1 30`;
	do
		./run $i $j Mesures/mesures2.csv
	done
done    
