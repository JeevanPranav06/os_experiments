#include <stdio.h>

int main() {
    int n, i, j, temp, burst[20], process[20], wait[20], turn[20];
    float avgWait = 0, avgTurn = 0;

    printf("Number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Burst time P%d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (burst[i] > burst[j]) {
                temp = burst[i]; burst[i] = burst[j]; burst[j] = temp;
                temp = process[i]; process[i] = process[j]; process[j] = temp;
            }
        }
    }

    printf("\nProcess\tBurst\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        if (i == 0) {
            wait[i] = 0;
        } else {
            wait[i] = turn[i - 1];
        }
        turn[i] = wait[i] + burst[i];
        avgWait += wait[i];
        avgTurn += turn[i];
        printf("P%d\t%d\t%d\t%d\n", process[i], burst[i], wait[i], turn[i]);
    }

    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("| P%d ", process[i]);
    }
    printf("|\n0");
    for (i = 0; i < n; i++) {
        printf("%5d", turn[i]);
    }

    printf("\n\nAverage WT = %.2f\nAverage TAT = %.2f\n",
           avgWait / n, avgTurn / n);
    return 0;
}
