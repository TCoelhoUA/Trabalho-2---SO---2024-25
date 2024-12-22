#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include "sharedMemory.h"
#include "semaphore.h"

int main() {
    int semgid, shmid;
    int key;

    // Generate the same key as the main program
    if ((key = ftok(".", 'a')) == -1) {
        perror("Error generating key");
        exit(EXIT_FAILURE);
    }

    // Access the semaphore and shared memory
    if ((semgid = semget(key, 0)) == -1) {
        perror("Error accessing semaphore");
    } else if (semDestroy(semgid) == -1) {
        perror("Error destroying semaphore");
    } else {
        printf("Semaphore destroyed successfully.\n");
    }

    if ((shmid = shmemConnect(key)) == -1) {
        perror("Error accessing shared memory");
    } else if (shmemDestroy(shmid) == -1) {
        perror("Error destroying shared memory");
    } else {
        printf("Shared memory destroyed successfully.\n");
    }

    return 0;
}
