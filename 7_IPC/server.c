#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 // Size of the shared memory segment
// K-SAWD
int main() {
    // K: Key creation
    key_t key = ftok("server.c", 65); // Create a unique key

    // S: Shared memory creation
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Create shared memory segment

    // A: Attach memory
    char *str = (char*) shmat(shmid, NULL, 0); // Attach to the shared memory

    // W: Write to memory
    printf("Server: Enter a message: ");
    fgets(str, SHM_SIZE, stdin); // Read input from the user
    str[strcspn(str, "\n")] = 0; // Remove newline character if present
    printf("Server: Message written to shared memory.\n");

    // D: Detach memory
    shmdt(str); // Detach from shared memory

    return 0;
}