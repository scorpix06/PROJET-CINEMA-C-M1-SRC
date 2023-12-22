# Project: parking

OBJ  = sem_op.o shm_op.o aleatoire.o
BIN  = vente_place_cinema entree sortie caisse
CFLAGS = -g #-Wall

all: $(BIN)

vente_place_cinema: $(OBJ) shm_const.h parking.c
	$(CC) parking.c $(OBJ) -o vente_place_cinema $(CFLAGS)

sortie: $(OBJ) shm_const.h sortie.c
	$(CC) sortie.c $(OBJ) -o sortie $(CFLAGS)

entree: $(OBJ) shm_const.h entree.c
	$(CC) entree.c $(OBJ) -o entree $(CFLAGS)

caisse: $(OBJ) shm_const.h caisse.c
	$(CC) caisse.c $(OBJ) -o caisse $(CFLAGS)

sem_op.o: sem_op.c shm_const.h
	$(CC) -c sem_op.c $(CFLAGS)

shm_op.o: shm_op.c shm_const.h
	$(CC) -c shm_op.c $(CFLAGS)

aleatoire.o: aleatoire.c
	$(CC) -c aleatoire.c $(CFLAGS)

clean: 
	rm -f $(OBJ) $(BIN)
