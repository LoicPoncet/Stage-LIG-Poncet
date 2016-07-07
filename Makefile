#définition des variables
CC = gcc
CFLAGS = -Wall -fopenmp -g
EXEC=run


all: $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: run.o matrice.o timer.o element.o
	$(CC) -fopenmp -o run run.o matrice.o timer.o element.o

run.o: run.c matrice.h timer.h
	$(CC) $(CFLAGS) -c run.c

matrice.o: matrice.c timer.h element.h
	$(CC) $(CFLAGS) -c matrice.c



#clean
clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)
