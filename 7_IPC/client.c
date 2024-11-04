#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define SHM_SIZE 1024 // Size of the shared memory segment

int main() {
    key_t key = ftok("server.c", 65); // Create a unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Get shared memory segment
    char *str = (char*) shmat(shmid, NULL, 0); // Attach to the shared memory

    // Read the message from shared memory
    printf("Client: Reading from shared memory...\n");
    printf("Client: %s\n", str); // Print the message read from shared memory

    // Detach from shared memory
    shmdt(str);

    return 0;
}