#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(NULL));
    FILE *fp;

    // Predefined array of sizes
    int sizes[10] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 10000};

    fp = fopen("quicksort_data.txt", "w"); // overwrite each run
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int trials = 10; // number of repetitions for averaging

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
            quickSort(arr, 0, n - 1);
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
