#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

// Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(NULL));
    FILE *fp;

    // Predefined array of sizes
    int sizes[10] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 10000};

    fp = fopen("merge.txt", "w"); // overwrite each run
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int trials = 5; // average over 5 runs

    for (int k = 0; k < 10; k++) {
        int n = sizes[k];
        if (n == 0) {
            fprintf(fp, "0 0.0\n");
            printf("0 0.0\n");
            continue;
        }

        double total_time = 0.0;

        for (int t = 0; t < trials; t++) {
            int *arr = (int*)malloc(n * sizeof(int));
            if (arr == NULL) {
                printf("Memory allocation failed for size %d!\n", n);
                continue;
            }

            // Generate random numbers
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100000;
            }

            clock_t start, end;
            start = clock();
            mergeSort(arr, 0, n - 1);
            end = clock();

            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;

            free(arr);
        }

        double avg_time = total_time / trials;

        // Print result
        printf("%d %.6f\n", n, avg_time);

        // Save to file
        fprintf(fp, "%d %.6f\n", n, avg_time);
    }

    fclose(fp);
    return 0;
}