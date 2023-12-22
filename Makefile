# Project: parking

OBJ  = sem_op.o shm_op.o aleatoire.o
BIN  = vente_place_cinema entree sortie caisse
CFLAGS = -g #-Wall

all: $(BIN)

vente_place_cinema: parking.o $(OBJ) shm_const.h
	$(CC) parking.o $(OBJ) -o vente_place_cinema $(CFLAGS)

sortie: sortie.o $(OBJ) shm_const.h
	$(CC) sortie.o $(OBJ) -o sortie $(CFLAGS)

entree: entree.o $(OBJ) shm_const.h
	$(CC) entree.o $(OBJ) -o entree $(CFLAGS)

caisse: caisse.o $(OBJ) shm_const.h
	$(CC) caisse.o $(OBJ) -o caisse $(CFLAGS)

sem_op.o: sem_op.c shm_const.h
	$(CC) -c sem_op.c $(CFLAGS)

shm_op.o: shm_op.c shm_const.h
	$(CC) -c shm_op.c $(CFLAGS)

aleatoire.o: aleatoire.c
	$(CC) -c aleatoire.c $(CFLAGS)

clean: 
	rm -f $(OBJ) $(BIN) *.o
