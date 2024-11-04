#include <stdio.h>          // Standard I/O for printing
#include <pthread.h>        // Library for using pthreads
#include <semaphore.h>      // Library for using semaphores
#include <unistd.h>         // Library for sleep function

#define NUM_READERS 3       // Number of reader threads
#define NUM_READS 3         // Number of read operations per reader
#define NUM_WRITES 3        // Number of write operations by the writer

sem_t rw_mutex;             // Semaphore to ensure mutual exclusion between readers and writers
sem_t mutex;                // Semaphore to protect access to read_count
int read_count = 0;         // Counter for the number of readers currently reading
int shared_data = 0;        // Shared data resource to be read/written

// Reader thread function
void *reader(void *arg) {
    for (int i = 0; i < NUM_READS; i++) {  // Each reader reads NUM_READS times
        sem_wait(&mutex);                  // Lock mutex to update read_count
        read_count++;                      // Increment reader count
        if (read_count == 1) {             // If this is the first reader
            sem_wait(&rw_mutex);           // Lock rw_mutex to prevent writers
        }
        sem_post(&mutex);                  // Unlock mutex after updating read_count

        // Critical section: reading the shared data
        printf("Reader %ld reads: %d\n", (long)arg, shared_data);  // Print shared data
        sleep(1);                         // Simulate time taken to read

        sem_wait(&mutex);                 // Lock mutex to update read_count
        read_count--;                     // Decrement reader count
        if (read_count == 0) {            // If this is the last reader
            sem_post(&rw_mutex);          // Unlock rw_mutex to allow writers
        }
        sem_post(&mutex);                 // Unlock mutex after updating read_count

        sleep(1);                         // Simulate time between reads
    }
    return NULL;                          // Exit thread
}

// Writer thread function
void *writer(void *arg) {
    for (int i = 0; i < NUM_WRITES; i++) {  // Writer writes NUM_WRITES times
        sem_wait(&rw_mutex);                // Lock rw_mutex to ensure exclusive access

        // Critical section: writing to the shared data
        shared_data = rand() % 100;         // Write new random data
        printf("Writer writes: %d\n", shared_data);  // Print the written data
        sleep(1);                           // Simulate time taken to write

        sem_post(&rw_mutex);                // Unlock rw_mutex after writing
        sleep(2);                           // Simulate time between writes
    }
    return NULL;                            // Exit thread
}

int main() {
    pthread_t r_threads[NUM_READERS];  // Array to hold reader thread identifiers
    pthread_t w_thread;                // Identifier for the writer thread

    sem_init(&rw_mutex, 0, 1);         // Initialize rw_mutex semaphore to 1
    sem_init(&mutex, 0, 1);            // Initialize mutex semaphore to 1

    // Create reader threads
    for (long i = 0; i < NUM_READERS; i++) {
        pthread_create(&r_threads[i], NULL, reader, (void *)i);  // Create reader thread
    }

    // Create writer thread
    pthread_create(&w_thread, NULL, writer, NULL);  // Create writer thread

    // Join reader threads (wait for all readers to finish)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(r_threads[i], NULL);  // Wait for reader thread to finish
    }

    // Join writer thread (wait for writer to finish)
    pthread_join(w_thread, NULL);  // Wait for writer thread to finish

    // Destroy semaphores
    sem_destroy(&rw_mutex);        // Destroy rw_mutex semaphore
    sem_destroy(&mutex);           // Destroy mutex semaphore

    return 0;                      // Exit program
}
