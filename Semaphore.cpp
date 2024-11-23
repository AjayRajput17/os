#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5      // Size of the shared buffer
#define TOTAL_ITEMS 20     // Total number of items to be produced/consumed

int buffer[BUFFER_SIZE];   // Shared buffer
int count = 0;             // Tracks the current number of items in the buffer
int totalProduced = 0;     // Total items produced so far
int totalConsumed = 0;     // Total items consumed so far

// Mutex and semaphores
pthread_mutex_t mutex;     // Mutex to protect shared resources
sem_t emptySlots;          // Semaphore for empty slots in the buffer
sem_t fullSlots;           // Semaphore for full slots in the buffer

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        // Check if the total production limit is reached
        pthread_mutex_lock(&mutex);
        if (totalProduced >= TOTAL_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break; // Exit the loop
        }
        pthread_mutex_unlock(&mutex);

        // Produce an item (random number)
        item = rand() % 100; // Random number between 0-99
        sleep(1);            // Simulate production time

        // Wait for an empty slot and lock the buffer
        sem_wait(&emptySlots);
        pthread_mutex_lock(&mutex);

        // Add the item to the buffer
        buffer[count] = item;
        count++;
        totalProduced++;
        printf("Producer produced: %d (Buffer count: %d, Total produced: %d)\n", 
               item, count, totalProduced);

        // Unlock the mutex and signal a full slot
        pthread_mutex_unlock(&mutex);
        sem_post(&fullSlots);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        // Check if the total consumption limit is reached
        pthread_mutex_lock(&mutex);
        if (totalConsumed >= TOTAL_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break; // Exit the loop
        }
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simulate consumption time

        // Wait for a full slot and lock the buffer
        sem_wait(&fullSlots);
        pthread_mutex_lock(&mutex);

        // Remove the item from the buffer
        count--;
        item = buffer[count];
        totalConsumed++;
        printf("Consumer consumed: %d (Buffer count: %d, Total consumed: %d)\n", 
               item, count, totalConsumed);

        // Unlock the mutex and signal an empty slot
        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);
    }
    return NULL;
}

int main() {
    pthread_t producerThreads[5], consumerThreads[3];

    // Initialize the mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&emptySlots, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&fullSlots, 0, 0);            // Initially, no slots are full

    // Create producer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&producerThreads[i], NULL, producer, NULL);
    }

    // Create consumer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&consumerThreads[i], NULL, consumer, NULL);
    }

    // Wait for producer threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(producerThreads[i], NULL);
    }

    // Wait for consumer threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(consumerThreads[i], NULL);
    }

    // Clean up resources
    pthread_mutex_destroy(&mutex);
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

    return 0;
}



