#include <stdio.h>
#include <pthread.h>
#include <sys/sysinfo.h> // For getting the number of CPUs
#include <stdlib.h>
#include <sys/time.h>

#define NUM_INCREMENTS 1000000

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *args) {
    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    int num_cpus = get_nprocs_conf(); // Get the number of CPUs
    pthread_t threads[num_cpus];
    struct timeval start_time, end_time;

    // Get the start time
    gettimeofday(&start_time, NULL);

    // Create threads
    for (int i = 0; i < num_cpus; ++i) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Join threads
    for (int i = 0; i < num_cpus; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    long long elapsed_usec = (end_time.tv_sec - start_time.tv_sec) * 1000000LL +
                             (end_time.tv_usec - start_time.tv_usec);

    // Print the elapsed time
    printf("Elapsed time: %lld microseconds\n", elapsed_usec);

    printf("Counter value: %d\n", counter);

    return 0;
}
