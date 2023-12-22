# Project: vente_place_cinema

OBJ = sem_op.o shm_op.o aleatoire.o
LINKOBJ = $(OBJ)
BIN = vente_place_cinema entree sortie caisse afficheur
CFLAGS = -g #-Wall

all: vente_place_cinema entree sortie caisse afficheur

vente_place_cinema: $(LINKOBJ) shm_const.h parking.c
	$(CC) parking.c $(LINKOBJ) -o vente_place_cinema $(CFLAGS)

sortie: $(LINKOBJ) shm_const.h sortie.c
	$(CC) sortie.c $(LINKOBJ) -o sortie $(CFLAGS)

entree: $(LINKOBJ) shm_const.h entree.c
	$(CC) entree.c $(LINKOBJ) -o entree $(CFLAGS)

caisse: $(LINKOBJ) shm_const.h caisse.c
	$(CC) caisse.c $(LINKOBJ) -o caisse $(CFLAGS)

afficheur: $(LINKOBJ) shm_const.h afficheur.c
	$(CC) afficheur.c $(LINKOBJ) -o afficheur $(CFLAGS)

shm_op.o: shm_op.c shm_const.h
	$(CC) -c shm_op.c $(CFLAGS)

sem_op.o: sem_op.c shm_const.h
	$(CC) -c sem_op.c $(CFLAGS)

aleatoire.o: aleatoire.c
	$(CC) -c aleatoire.c $(CFLAGS)

clean:
	rm -f $(OBJ) $(BIN)
