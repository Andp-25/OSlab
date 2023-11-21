#include <stdio.h>
#include <stdbool.h>

bool isSafe(int n, int available[3], int max[4][3], int allocation[4][3]) {
    int work[3];
    int finish[4];

    for (int i = 0; i < 3; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int safeSeq[n];
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                bool canAllocate = true;

                for (int j = 0; j < 3; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < 3; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // No safe sequence
        }
    }

    // Safe sequence found, print it
    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        int available[3];
        scanf("%d %d %d", &available[0], &available[1], &available[2]);

        int max[4][3];
        int allocation[4][3];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &allocation[i][j]);
            }
            for (int j = 0; j < 3; j++) {
                scanf("%d", &max[i][j]);
            }
        }

        if (!isSafe(n, available, max, allocation)) {
            printf("-1\n");
        }
    }

    return 0;
}