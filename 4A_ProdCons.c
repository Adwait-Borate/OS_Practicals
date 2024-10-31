#include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Smaller buffer size for simplicity
#define NUM_ITEMS 10  // Total items to produce and consume

int buffer[BUFFER_SIZE];
sem_t full, empty, mutex;
int in = 0, out = 0;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100; // Produce a random item
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&mutex); // Enter critical section

        buffer[in] = item; // Add item to buffer
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Wrap around

        sem_post(&mutex); // Exit critical section
        sem_post(&full); // Signal that a new item is available
        sleep(1); // Simulate production time
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Wait for a full slot
        sem_wait(&mutex); // Enter critical section

        int item = buffer[out]; // Remove item from buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Wrap around

        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal that an empty slot is available
        sleep(2); // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&full, 0, 0);  // No items in the buffer
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are empty
    sem_init(&mutex, 0, 1);  // Mutex for critical section

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

    return 0;
}
