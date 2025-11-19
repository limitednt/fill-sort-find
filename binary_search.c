#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define GREY "\033[90m"
#define RED "\033[0;31m"
#define WHITE "\033[97m"

void binary_search(int n, int arr[], int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid] == key) {
            printf("the number %d is found in the array at the index %d\n", key, mid);
            return;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf(RED "number not found in the array\n" WHITE);
}

int main() {
    // this is the file reading section, i dont know how exactly how it works yet
    FILE *pFILE = fopen("output.txt", "r");
    if (pFILE == NULL) {
        printf(RED"\nerror file couldnt be open\n"WHITE);
        return 1;
    }
    int n;
    if (fscanf(pFILE, "%d", &n) != 1) {
        printf(RED"bad size,too small\n"WHITE);
        fclose(pFILE);
        return 1;
    }

    int *a = malloc(n * sizeof *a);

    if (a == NULL) {
        fprintf(stderr, "out of memory\n");
        fclose(pFILE);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(pFILE, "%d", &a[i]) != 1) {
            fprintf(stderr, "bad data\n");
            free(a);
            fclose(pFILE);
            return 1;
        }
    }
    //------------------------------------------------ 
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("[%d]", a[i]);
    }
    printf("\n");

    // this is where the binary search happens
    int key;
    printf("enter the number you want to search for:\n");
    scanf("%d", &key);
    binary_search(n, a, key);
    fclose(pFILE);
    free(a);
    return 0;
}
