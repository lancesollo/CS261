#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "zemaphore.h" 

int philoCount;                // Number of philosophers
Zem_t *forks;                       // Array of semaphores representing forks
Zem_t table;                        // Semaphore for table access

int algorithmChoice;                //variable for algorithm selection

void *philoActivity(void *arg) {
    int philoID = *(int *)arg;
    free(arg);

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philoID);
        sleep(rand() % 3 + 1); 

        // Hungry
        printf("Philosopher %d is hungry.\n", philoID);

        switch (algorithmChoice) {
            case 1:
                // Algorithm 1: Picks up left fork, then the right fork
                Zem_wait(&forks[philoID]);
                Zem_wait(&forks[(philoID + 1) % philoCount]);
                break;
            case 2:
                // Algorithm 2: Pickx up both forks if bothforks aren't taken
                while (1) {
                    Zem_wait(&forks[philoID]);
                    if (pthread_mutex_trylock(&forks[(philoID + 1) % philoCount].lock) == 0) {
                        break;
                    } else {
                        Zem_post(&forks[philoID]);
                        usleep(1000); // Short wait before retrying
                    }
                }
                break;
            case 3:
                // Algorithm 3: Only N-1 philosophers can sit at the table
                Zem_wait(&table);
                Zem_wait(&forks[philoID]);
                Zem_wait(&forks[(philoID + 1) % philoCount]);
                break;
        }

        // Eating
        printf("Philosopher %d is eating.\n", philoID);
        sleep(rand() % 3 + 1); // Simulate eating time

        // Release forks
        Zem_post(&forks[philoID]);
        Zem_post(&forks[(philoID + 1) % philoCount]);

        if (algorithmChoice == 3) {
            Zem_post(&table);
        }

        printf("Philosopher %d has finished eating.\n", philoID);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_of_philosophers> <algorithm_choice>\n", argv[0]);
        fprintf(stderr, "Algorithm Choices:\n");
        fprintf(stderr, "1 - Picked the left fork, then right fork (deadlock prone)\n");
        fprintf(stderr, "2 - Picked up both forks if both aren't \n");
        fprintf(stderr, "3 - Only N-1 philosophers can be at the table\n");
        return EXIT_FAILURE;
    }

    philoCount = atoi(argv[1]);
    algorithmChoice = atoi(argv[2]);

    if (philoCount < 3 || philoCount > 20) {
        fprintf(stderr, "Number of philosophers must be between 3 and 20.\n");
        return EXIT_FAILURE;
    }

    if (algorithmChoice < 1 || algorithmChoice > 3) {
        fprintf(stderr, "Invalid algorithm choice. Choose 1, 2, or 3.\n");
        return EXIT_FAILURE;
    }

    // Initialize semaphores
    forks = malloc(philoCount * sizeof(Zem_t));
    for (int i = 0; i < philoCount; ++i) {
        Zem_init(&forks[i], 1); // Each fork starts available
    }

    if (algorithmChoice == 3) {
        Zem_init(&table, philoCount - 1); // Allow only N-1 philosophers at the table
    }

    // Create philosopher threads
    pthread_t threads[philoCount];
    for (int i = 0; i < philoCount; ++i) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, philoActivity, id);
    }

    // Join philosopher threads
    for (int i = 0; i < philoCount; ++i) {
        pthread_join(threads[i], NULL);
    }

   
    free(forks);
    return EXIT_SUCCESS;
}
