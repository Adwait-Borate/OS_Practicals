#include <stdio.h>
//#include <pthread.h>
//#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READS 5
#define NUM_WRITES 5

sem_t full, empty, mutex; // Reusing similar semaphore names
int read_count = 0;        // Number of readers currently reading
int shared_data = 0;       // The shared data

void *reader(void *arg) {
    for (int i = 0; i < NUM_READS; i++) {
        sem_wait(&mutex); // Mutex to protect read_count

        read_count++;
        if (read_count == 1) {
            sem_wait(&full); // First reader locks full, blocking writers
        }
        sem_post(&mutex);

        // Reading the shared data
        printf("Reader reads: %d\n", shared_data);
        sleep(1); // Simulate reading time

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&full); // Last reader unlocks full, allowing writers
        }
        sem_post(&mutex);
        sleep(1); // Simulate time between reads
    }
    return NULL;
}

void *writer(void *arg) {
    for (int i = 0; i < NUM_WRITES; i++) {
        sem_wait(&empty); // Wait for the empty slot (for mutual exclusion)
        sem_wait(&full);  // Only one writer allowed at a time

        shared_data = rand() % 100; // Writing new data
        printf("Writer writes: %d\n", shared_data);
        sleep(1); // Simulate writing time

        sem_post(&full);
        sem_post(&empty); // Release the slot
        sleep(2); // Simulate time between writes
    }
    return NULL;
}

int main() {
    pthread_t readers[3], writer_thread;

    sem_init(&full, 0, 1);  // Semaphore for writer access
    sem_init(&empty, 0, 1); // Semaphore to simulate empty state
    sem_init(&mutex, 0, 1); // Mutex for read_count access

    // Create reader and writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    pthread_create(&writer_thread, NULL, writer, NULL);

    // Join reader and writer threads
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

    return 0;
}
