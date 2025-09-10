#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Iterative matrix multiplication
void multiply_iterative(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));
    FILE *fp = fopen("iterative.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Matrix sizes to test (must be square)
    int sizes[] = {2, 4, 8, 16, 32, 64, 128,256};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int trials = 5;  // average over multiple runs

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        // Dynamically allocate matrices
        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));

        if (!A || !B || !C) {
            printf("Memory allocation failed for %d x %d matrix!\n", n, n);
            continue;
        }

        double total_time = 0.0;

        for (int t = 0; t < trials; t++) {
            // Fill with random numbers
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    A[i][j] = rand() % 10;
                    B[i][j] = rand() % 10;
                }

            clock_t start = clock();
            multiply_iterative(n, A, B, C);
            clock_t end = clock();

            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        double avg_time = total_time / trials;

        // Print to console
        printf("%d x %d -> %.9f sec\n", n, n, avg_time);

        // Save to file
        fprintf(fp, "%d %.9f\n", n, avg_time);

        free(A);
        free(B);
        free(C);
    }

    fclose(fp);
   
    return 0;
}
