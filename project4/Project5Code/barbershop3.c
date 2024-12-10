#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared resources and synchronization primitives
#define MAX_CHAIRS 5  // Number of waiting chairs

int waitingCustomers = 0;   // Count of customers waiting
pthread_mutex_t shopMutex;  // Mutex to protect shared resources
pthread_cond_t barberReady; // Condition for barber readiness
pthread_cond_t customerReady; // Condition for customer arrival

// Barber thread function
void *barber(void *args) {
    while (1) {
        pthread_mutex_lock(&shopMutex);

        // Waits until there are customers
        while (waitingCustomers == 0) {
            printf("Barber is sleeping.\n");
            pthread_cond_wait(&customerReady, &shopMutex);
        }

        // Serves a customer
        waitingCustomers--;
        printf("Barber is cutting hair. Waiting customers: %d\n", waitingCustomers);

        // Signal the customer that the barber is ready
        pthread_cond_signal(&barberReady);
        pthread_mutex_unlock(&shopMutex);

        // Simulate hair-cutting time
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

// Customer thread function
void *customer(void *args) {
    pthread_mutex_lock(&shopMutex);

    if (waitingCustomers < MAX_CHAIRS) {
        // If there are chairs, wait
        waitingCustomers++;
        printf("Customer sits and waits. Waiting customers: %d\n", waitingCustomers);

        // Notify barber
        pthread_cond_signal(&customerReady);

        // Wait for the barber to serve
        pthread_cond_wait(&barberReady, &shopMutex);
        printf("Customer is getting a haircut.\n");
    } else {
        // No available chairs
        printf("Customer leaves as no chairs are available.\n");
    }

    pthread_mutex_unlock(&shopMutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_customers>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numCustomers = atoi(argv[1]);
    if (numCustomers <= 0) {
        fprintf(stderr, "Number of customers must be greater than 0.\n");
        return EXIT_FAILURE;
    }

    // Initialize synchronization primitives
    pthread_mutex_init(&shopMutex, NULL);
    pthread_cond_init(&barberReady, NULL);
    pthread_cond_init(&customerReady, NULL);

    // Create barber thread
    pthread_t barberThread;
    pthread_create(&barberThread, NULL, barber, NULL);

    // Create customer threads
    pthread_t customerThreads[numCustomers];
    for (int i = 0; i < numCustomers; i++) {
        pthread_create(&customerThreads[i], NULL, customer, NULL);
        sleep(rand() % 2); // Simulate customer arrival time
    }

    // Wait for all customer threads to finish
    for (int i = 0; i < numCustomers; i++) {
        pthread_join(customerThreads[i], NULL);
    }

    // Terminate barber thread
    pthread_cancel(barberThread);

    // Cleans up
    pthread_mutex_destroy(&shopMutex);
    pthread_cond_destroy(&barberReady);
    pthread_cond_destroy(&customerReady);

    return EXIT_SUCCESS;
}
