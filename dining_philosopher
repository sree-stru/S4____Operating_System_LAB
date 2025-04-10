#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_number + N - 1) % N
#define RIGHT (philosopher_number + 1) % N

int state[N];
sem_t mutex;
sem_t S[N];

void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY &&
        state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher_number] = EATING;
        sleep(2);
        printf("Philosopher %d takes chopstick %d and %d and is eating\n",
               philosopher_number + 1, LEFT + 1, philosopher_number + 1);
        sem_post(&S[philosopher_number]);
    }
}

void take_chopstick(int philosopher_number) {
    sem_wait(&mutex);
    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher_number + 1);
    test(philosopher_number);
    sem_post(&mutex);
    sem_wait(&S[philosopher_number]);
    sleep(1);
}

void put_chopstick(int philosopher_number) {
    sem_wait(&mutex);
    state[philosopher_number] = THINKING;
    printf("Philosopher %d put chopstick %d and %d down\n",
           philosopher_number + 1, LEFT + 1, philosopher_number + 1);
    printf("Philosopher %d is thinking\n", philosopher_number + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    int philosopher_number = *(int*)num;
    free(num);
    while (1) {
        sleep(1);
        take_chopstick(philosopher_number);
        sleep(0);
        put_chopstick(philosopher_number);
    }
}

int main() {
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (int i = 0; i < N; i++) {
        int* philosopher_number = malloc(sizeof(int));
        *philosopher_number = i;
        pthread_create(&thread_id[i], NULL, philosopher, philosopher_number);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}
