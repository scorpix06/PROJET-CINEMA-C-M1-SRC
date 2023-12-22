#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Declaration of attente_aleatoire function
void attente_aleatoire(unsigned int delais);

extern int *attacher_segment_memoire();
extern int P();
extern int V();

void vente_billets(int *mem, int semid, const char *titre_film) {
    P(semid);

    if (*mem > 0) {
        int billets_achetes = nombre_aleatoire(1, 7); // Random number of tickets between 1 and 7
        if (billets_achetes <= *mem) {
            attente_aleatoire(3); // Random processing time between 1 and 3 seconds
            *mem -= billets_achetes;
            printf("Caisse vend %d billets pour \"%s\".\n", billets_achetes, titre_film);
        } else {
            printf("Caisse ne peut pas satisfaire la demande.\n");
        }
    } else {
        printf("Plus de places disponibles pour \"%s\".\n", titre_film);
    }

    V(semid);
}

int main(int argc, char *argv[]) {
    int shmid = atoi(argv[1]);
    int semid = atoi(argv[2]);
    const char *titre_film = argv[3];

    int *mem = attacher_segment_memoire(mem, &shmid);

    while (*mem > 0) {
        vente_billets(mem, semid, titre_film);
        attente_ale
