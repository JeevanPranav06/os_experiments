#include <stdio.h>

int main() {
    int n, quantum, i, time = 0, done, run;
    int burst[20], remaining[20], wait[20], turn[20];
    int chart[10000], end[10000], count = 0;
    float avgWait = 0, avgTurn = 0;

    printf("Number of processes and time quantum: ");
    scanf("%d%d", &n, &quantum);

    for (i = 0; i < n; i++) {
        printf("Burst time P%d: ", i + 1);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                done = 0;

                if (remaining[i] > quantum) {
                    run = quantum;
                } else {
                    run = remaining[i];
                }

                time += run;
                remaining[i] -= run;
                chart[count] = i + 1;
                end[count] = time;
                count++;

                if (remaining[i] == 0) {
                    turn[i] = time;
                    wait[i] = turn[i] - burst[i];
                }
            }
        }
    } while (!done);

    printf("\nProcess\tBurst\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        avgWait += wait[i];
        avgTurn += turn[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, burst[i], wait[i], turn[i]);
    }

    printf("\nGantt Chart:\n");
    for (i = 0; i < count; i++) {
        printf("| P%d ", chart[i]);
    }
    printf("|\n0");
    for (i = 0; i < count; i++) {
        printf("%5d", end[i]);
    }

    printf("\n\nAverage WT = %.2f\nAverage TAT = %.2f\n",
           avgWait / n, avgTurn / n);
    return 0;
}
