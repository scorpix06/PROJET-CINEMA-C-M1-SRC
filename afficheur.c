#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int *attacher_segment_memoire();
extern int P();
extern int V();

void afficher_places_restantes(int *mem, int semid, const char *titre_film) {
    P(semid);
    printf("Afficheur pour \"%s\": Nombre de places restantes : %d\n", titre_film, *mem);
    V(semid);
}

int main(int argc, char *argv[]) {
    unsigned int delais = 5;

    int shmid = atoi(argv[1]);
    int semid = atoi(argv[2]);
    const char *titre_film = argv[3];

    int *mem = attacher_segment_memoire(mem, &shmid);

    while (1) {
        afficher_places_restantes(mem, semid, titre_film);
        sleep(delais);
    }

    return 0;
}
