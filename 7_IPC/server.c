#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#define SHM_SIZE 1024 // Size of the shared memory segment
int main() {
key_t key = ftok("server.c", 65); // Create a unique key
int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Create shared memory segment
char *str = (char*) shmat(shmid, NULL, 0); // Attach to the shared memory
// Get a message from the user
printf("Server: Enter a message: ");
fgets(str, SHM_SIZE, stdin); // Read input from the user
str[strcspn(str, "\n")] = 0; // Remove newline character if present
printf("Server: Message written to shared memory.\n");
// Detach from shared memory
shmdt(str);
return 0;
}