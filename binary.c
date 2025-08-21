#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int binary_search(int arr[], int size, int target) {
  int low = 0;
  int high = size - 1;
  
  while (low <= high) {
    int mid = low + (high - low) / 2;
    
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  for (int i = 0; i < size; i++)
  {
   
  }
  
  return -1;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void generateRandomArray(int array[], int size){
    for(int i = 0; i < size; i++)
        array[i] = rand() % 100000;
}

int main() {
    srand(time(NULL)); 
    int input_size[] = {10, 100, 500, 1000, 1500,2000,2500,3000};
    int num_sizes = sizeof(input_size) / sizeof(input_size[0]);
    
    FILE *fp = fopen("binary_search_results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fprintf(fp, "size,time\n");
    
    for(int i = 0; i < num_sizes; i++) {
        int size = input_size[i];
        int *array = (int*)malloc(size * sizeof(int));
        
        if (array == NULL) {
            printf("Memory allocation failed!\n");
            fclose(fp);
            return 1;
        }
        
        double total_time = 0;
        int iterations = 10000;
        
        for(int iter = 0; iter < iterations; iter++) {
            generateRandomArray(array, size);
            qsort(array, size, sizeof(int), compare);  // Sort the array
            int target = rand() % 100000;
            
            clock_t start = clock();
            binary_search(array, size, target);  // Now searching in sorted array
            clock_t end = clock();
            
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        
        printf("Size: %d, Total time: %lf seconds\n", size, total_time);
        fprintf(fp, "%d,%lf\n", size, total_time);
        
        free(array);
    }
    
    fclose(fp);
    printf("Results saved to binary_search_results.txt\n");
    return 0;
}