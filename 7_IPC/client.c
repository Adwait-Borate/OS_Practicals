#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 // Size of the shared memory segment
//K-ARRD
int main() {
    // K: Key usage
    key_t key = ftok("server.c", 65); // Use the same unique key as server

    // A: Attach memory
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Access shared memory segment
    char *str = (char*) shmat(shmid, NULL, 0); // Attach to the shared memory

    // R: Read memory
    printf("Client: Reading from shared memory...\n");
    printf("Client: %s\n", str); // Print the message stored in shared memory

    // D: Detach memory
    shmdt(str); // Detach from shared memory

    return 0;
}