#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {      // This loop runs n times
        if (arr[i] == target) return i; // Each comparison is O(1)
    }
    return -1;
}

int main() {
    FILE *fp;
    fp = fopen("linear_search_results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    
    int sizes[] = {10000000, 30000000, 50000000, 70000000, 90000000, 100000000};
    int num_sizes = 6;

    fprintf(fp, "size,time\n");
    printf(" size\t time (seconds)\n");
    printf("--------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr[j] = j;

        int target = n - 1;

        clock_t start = clock();
        linear_search(arr, n, target);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "%d,%f\n", n, time_taken);
        printf("%6d\t %f\n", n, time_taken);

        free(arr);
    }

    fclose(fp);
    printf("\nResults written to linear_search_results.txt\n");
    return 0;
}