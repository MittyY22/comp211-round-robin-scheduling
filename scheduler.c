/* Educational CPU scheduling model: all jobs arrive at time 0.
 * One core, no I/O, and no context-switch cost.
 * AI-assisted starter example for COMP 211 Checkoff 3.
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_JOBS 26
#define MAX_WORK 10000

static int positive_int(const char *text) {
    char *end;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (errno || end == text || *end != '\0' || value < 1 || value > MAX_WORK)
        return -1;
    return (int)value;
}

static void simulate(const int burst[], int count, int quantum,
                     const char *label) {
    int remaining[MAX_JOBS], first[MAX_JOBS], completion[MAX_JOBS];
    int time = 0, finished = 0;
    double response_sum = 0, turnaround_sum = 0;
    for (int i = 0; i < count; i++) {
        remaining[i] = burst[i];
        first[i] = -1;
        completion[i] = 0;
    }

    printf("\n%s (quantum = %d ms)\n", label, quantum);
    printf("Schedule:\n");
    /* With simultaneous arrivals and no blocking, cyclic scanning is
     * equivalent to taking the head of a queue and requeuing unfinished jobs.
     */
    while (finished < count) {
        for (int i = 0; i < count; i++) {
            if (remaining[i] == 0) continue;
            if (first[i] == -1) first[i] = time;
            int duration = remaining[i] < quantum ? remaining[i] : quantum;
            printf("  %3d-%-3d ms  %c\n", time, time + duration, 'A' + i);
            time += duration;
            remaining[i] -= duration;
            if (remaining[i] == 0) {
                completion[i] = time;
                finished++;
            }
        }
    }

    printf("Process  Burst  First run  Completion  Response  Turnaround (ms)\n");
    for (int i = 0; i < count; i++) {
        /* Arrival is zero, so first run = response and completion = turnaround. */
        printf("   %c     %5d  %9d  %10d  %8d  %10d\n",
               'A' + i, burst[i], first[i], completion[i], first[i], completion[i]);
        response_sum += first[i];
        turnaround_sum += completion[i];
    }
    printf("Average response: %.2f ms\n", response_sum / count);
    printf("Average turnaround: %.2f ms\n", turnaround_sum / count);
    printf("Total useful CPU work: %d ms\n", time);
}

int main(int argc, char *argv[]) {
    int burst[MAX_JOBS] = {4, 4, 4};
    int count = 3, quantum = 0, maximum = 0, total = 0;
    if (argc > 1) {
        quantum = positive_int(argv[1]);
        if (quantum < 0 || argc > MAX_JOBS + 2) {
            fprintf(stderr, "Usage: %s [positive_quantum [positive_burst ...]]\n", argv[0]);
            return 1;
        }
        if (argc > 2) {
            count = argc - 2;
            for (int i = 0; i < count; i++) {
                burst[i] = positive_int(argv[i + 2]);
                if (burst[i] < 0) {
                    fprintf(stderr, "Bursts must be integers from 1 to %d ms.\n", MAX_WORK);
                    return 1;
                }
            }
        }
    }
    for (int i = 0; i < count; i++) {
        if (burst[i] > maximum) maximum = burst[i];
        total += burst[i];
    }
    if (total > MAX_WORK) {
        fprintf(stderr, "Total CPU work must be at most %d ms.\n", MAX_WORK);
        return 1;
    }

    puts("All processes arrive at 0 ms in alphabetical order.");
    puts("Single core, no I/O, context-switch cost ignored.");
    /* A quantum at least as large as every burst produces the FCFS schedule. */
    simulate(burst, count, maximum, "FCFS baseline");
    if (quantum) {
        simulate(burst, count, quantum, "Round robin");
    } else {
        for (int q = 1; q <= 4; q *= 2)
            simulate(burst, count, q, "Round robin");
    }
    return 0;
}
