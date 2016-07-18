#définition des variables
CC = gcc
CFLAGS = -Wall -fopenmp -g
EXEC=run run_blocs effet_cache test


all: run

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: run.o matrice.o timer.o element.o
	$(CC) -fopenmp -o run run.o matrice.o timer.o element.o -lm

run.o: run.c matrice.h timer.h
	$(CC) $(CFLAGS) -c run.c

run_blocs: run_blocs.o matrice.o timer.o element.o
	$(CC) -fopenmp -o run_blocs run_blocs.o matrice.o timer.o element.o -lm

run_blocs.o: run_blocs.c matrice.h timer.h
	$(CC) $(CFLAGS) -c run_blocs.c

matrice.o: matrice.c timer.h element.h
	$(CC) $(CFLAGS) -c matrice.c

effet_cache: effet_cache.o timer.o
	$(CC) -o effet_cache effet_cache.o timer.o

effet_cache.o: effet_cache.c timer.h
	$(CC) -Wall -g -c effet_cache.c

test: test_algo.o matrice.o timer.o element.o
	$(CC) -fopenmp -o test test_algo.o matrice.o timer.o element.o -lm

test_algo.o: test_algo.c matrice.h timer.h
	$(CC) $(CFLAGS) -c test_algo.c



#clean
clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)
