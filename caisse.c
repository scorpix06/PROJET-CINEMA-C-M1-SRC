#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

extern void attente_aleatoire();
extern int *attacher_segment_memoire();
extern int P();
extern int V();

int vente_billets(int *mem, int semid, const char *titre_film) {
    bool billets_vendus = false;

    P(semid);

    if (*mem > 0) {
        int billets_achetes = rand() % 7 + 1;
        if (billets_achetes <= *mem) {
            *mem -= billets_achetes;
            printf("Caisse vend %d billets pour \"%s\".\n", billets_achetes, titre_film);
            billets_vendus = true;
        } else {
            printf("Caisse ne peut pas satisfaire la demande.\n");
        }
    } else {
        printf("Plus de places disponibles pour \"%s\".\n", titre_film);
    }

    V(semid);

    return billets_vendus;
}

int main(int argc, char *argv[]) {
    unsigned int delais = 3;

    int shmid = atoi(argv[1]);
    int semid = atoi(argv[2]);
    const char *titre_film = argv[3];

    int *mem = attacher_segment_memoire(mem, &shmid);

    while (1) {
        attente_aleatoire(delais);
        printf("Caisse pour \"%s\": Un client se présente.\n", titre_film);
        while (!vente_billets(mem, semid, titre_film)) {
            sleep(1);
        }
    }

    return 0;
}
