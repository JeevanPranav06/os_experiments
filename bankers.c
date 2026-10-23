#include <stdio.h>

int main() {
    int n, m, i, j, k, count = 0, found;
    int alloc[20][20], max[20][20], need[20][20];
    int avail[20], work[20], finish[20] = {0}, safe[20];

    printf("Enter processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
        work[j] = avail[j];
    }

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    while (count < n) {
        found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    for (k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            break;
        }
    }

    if (count == n) {
        printf("\nSystem is in SAFE state\nSafe Sequence: ");
        for (i = 0; i < n; i++) {
            printf("P%d", safe[i]);
            if (i < n - 1) {
                printf(" -> ");
            }
        }
    } else {
        printf("\nSystem is in UNSAFE state");
    }

    printf("\n");
    return 0;
}
