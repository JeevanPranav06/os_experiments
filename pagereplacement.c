#include <stdio.h>

int pages[100], n, size, hits[3], faults[3];

void display(int page, int frames[], int hit) {
    printf("%-8d", page);
    for (int i = 0; i < size; i++) {
        if (frames[i] == -1) {
            printf("%-5s", "-");
        } else {
            printf("%-5d", frames[i]);
        }
    }
    printf("%s\n", hit ? "Hit" : "Fault");
}

void fifo() {
    int frames[20], next = 0, hit;

    for (int i = 0; i < size; i++) {
        frames[i] = -1;
    }

    printf("\nFIFO:\nPage\tFrames\t\tStatus\n");
    for (int i = 0; i < n; i++) {
        hit = 0;
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            frames[next] = pages[i];
            next = (next + 1) % size;
            faults[0]++;
        }
        display(pages[i], frames, hit);
    }
    hits[0] = n - faults[0];
}

void lru() {
    int frames[20], recent[20], pos, hit;

    for (int i = 0; i < size; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU:\nPage\tFrames\t\tStatus\n");
    for (int i = 0; i < n; i++) {
        hit = 0;
        pos = 0;

        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                pos = j;
                break;
            }
        }

        if (!hit) {
            for (int j = 1; j < size; j++) {
                if (recent[j] < recent[pos]) {
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            faults[1]++;
        }

        recent[pos] = i;
        display(pages[i], frames, hit);
    }
    hits[1] = n - faults[1];
}

void optimal() {
    int frames[20], pos, next, far, hit;

    for (int i = 0; i < size; i++) {
        frames[i] = -1;
    }

    printf("\nOptimal:\nPage\tFrames\t\tStatus\n");
    for (int i = 0; i < n; i++) {
        hit = 0;

        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            pos = 0;
            far = -1;

            for (int j = 0; j < size; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }

                next = n;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        next = k;
                        break;
                    }
                }

                if (next > far) {
                    far = next;
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            faults[2]++;
        }
        display(pages[i], frames, hit);
    }
    hits[2] = n - faults[2];
}

int main() {
    int choice;
    int preset[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    char *names[] = {"FIFO", "LRU", "Optimal"};

    printf("1. Preset Input\n2. User Input\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        n = sizeof(preset) / sizeof(preset[0]);
        size = 3;

        for (int i = 0; i < n; i++) {
            pages[i] = preset[i];
        }
    } else if (choice == 2) {
        printf("Enter number of pages: ");
        scanf("%d", &n);

        if (n < 1 || n > 100) {
            return 1;
        }

        printf("Enter page reference string: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &pages[i]);
        }

        printf("Enter number of frames: ");
        scanf("%d", &size);

        if (size < 1 || size > 20) {
            return 1;
        }
    } else {
        printf("Invalid choice\n");
        return 1;
    }

    printf("\nReference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\nFrames: %d\n", size);

    fifo();
    lru();
    optimal();

    printf("\nFINAL COMPARISON TABLE\n");
    printf("%-12s %-8s %-8s %-12s %-12s\n",
           "Algorithm", "Hits", "Faults", "Hit Ratio", "Fault Ratio");

    for (int i = 0; i < 3; i++) {
        printf("%-12s %-8d %-8d %-12.2f %-12.2f\n",
               names[i], hits[i], faults[i],
               (float)hits[i] / n, (float)faults[i] / n);
    }

    return 0;
}
