#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start_time, end_time;
    long long elapsed_usec;

    // Get the start time
    gettimeofday(&start_time, NULL);

    // Perform some operation to measure
    // For example, a loop that does nothing
    for (int i = 0; i < 1000000; ++i) {
        // Do nothing
    }

    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    function(long interations){
        // Get the start time
        gettimeofday(&start_time, NULL);

        // Perform some operation to measure
        // For example, a loop that does nothing
        for (int i = 0; i < interations; ++i) {
            // Do nothing
        }

        // Get the end time
        gettimeofday(&end_time, NULL);

        double elapsed_usec = (end_time.tv_sec - start_time.tv_sec) * 1000000LL +
                   (end_time.tv_usec - start_time.tv_usec);
                   return elapsed_usec

    }
    

    

    // Print the elapsed time
    printf("Elapsed time: %lld microseconds\n", elapsed_usec);

    return 0;
}
