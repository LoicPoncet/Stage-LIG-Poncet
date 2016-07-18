Impact de la hiérarchie mémoire sur les performances parallèles

Stage réalisé au Laboratoire d'Informatique de Grenoble dans le cadre des stages d'excellence en deuxième année de Licence Mathématiques et Informatique à l'Université Grenoble Alpes (UGA).

Tous les résultats ont été obtenu sur un HP Z800 Workstation avec deux processeur quad-core Intel(R) Xeon(R) E5620 2.40GHz.

Taille du cache: -L1d: 32KB
	   	  		 -L1i: 32KB
				 -L2: 256KB
				 -L3: 12288KB

Compilateur: gcc version 5.3.1


Description des fichiers:

- effet_cache.c: programme très simple permettant de montrer les effets du cache sur les temps d'exécutions. Pour se faire il suffit de changer l'odre des boucles For et de comparer les temps affichés.

- element.c/h: définition du type "Element" permettant l'abstraction pour nos calculs matriciels.

- exec_blocs.sh: script bash permettant de lancer plusieurs exécutions du programme run_blocs.c avec différents paramètres (voir les différents codes).

- exec.sh: idem au-dessus avec run.c

- Makefile: fichier de compilation automatique.

- matrice.c/h: fichier de déclaration et d'implémentation de notre type matrice ainsi que de l'ensemble des fonctions associées.

- run_blocs.c: fichier principal de l'algo de multiplication par blocs (voir code pour les détails).

- run.c: idem au-dessus.

- test_algo.c: programme permettant de vérifier que nos différents algos donnent le même (bon) résultat.

- timer.c/h: déclaration et implémentation de notre timer.



