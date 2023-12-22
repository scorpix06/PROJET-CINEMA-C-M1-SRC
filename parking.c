#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "shm_const.h"

extern int creer_initialiser_semaphore();
extern int *attacher_segment_memoire();
extern int P();
extern int V();

extern int creer_segment_memoire();
extern void attente_aleatoire();

int main(int argc, char *argv[]) {
    pid_t *pid_caisses;  
    pid_t pid_afficheur; 

    int code_retour_fin_caisse;
    int code_retour_fin_afficheur;

    int nombre_places_cinema; // Nombre de place total
    char *titre_film;         // Titre du film

    int shmid; //
    int semid; // ID du semaphore

    char shmid_str[20]; 
    char semid_str[20];

    int *mem; // Pointeur vers la memoire partagé

    if (argc != 4) {
        fprintf(stderr, "Usage: %s nombre_caisses titre_film nombre_places\n", argv[0]);
        return 1;
    }

    int nombre_caisses = atoi(argv[1]);
    titre_film = argv[2];
    nombre_places_cinema = atoi(argv[3]);

    creer_initialiser_semaphore(CLE_SEM, &semid);
    creer_segment_memoire(CLE_SHM, &shmid);
    mem = attacher_segment_memoire(mem, &shmid);
    *mem = nombre_places_cinema;


    sprintf(shmid_str, "%d", shmid);
    sprintf(semid_str, "%d", semid);


    pid_caisses = malloc(nombre_caisses * sizeof(pid_t));

    // Creation de processus caisse
    for (int i = 0; i < nombre_caisses; ++i) {
        pid_caisses[i] = fork();

        if (pid_caisses[i] == -1) {
            perror("Error in fork for caisse process");
            return 1;
        }

        if (pid_caisses[i] == 0) {
            execl("caisse", "caisse", shmid_str, semid_str, titre_film, NULL);
            perror("Error in execl for caisse process");
            return 1;
        }
    }

    // Creation de l'afficher 
    pid_afficheur = fork();

    if (pid_afficheur == -1) {
        perror("Error in fork for afficheur process");
        return 1;
    }

    if (pid_afficheur == 0) {
        execl("afficheur", "afficheur", shmid_str, semid_str, titre_film, NULL);
        perror("Error in execl for afficheur process");
        return 1;
    }

    for (int i = 0; i < nombre_caisses; ++i) {
        waitpid(pid_caisses[i], &code_retour_fin_caisse, 0);
    }

    waitpid(pid_afficheur, &code_retour_fin_afficheur, 0);

    system("./clean_ipc.sh");

    free(pid_caisses);

    return 0;
}
