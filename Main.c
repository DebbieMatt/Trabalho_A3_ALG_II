#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long comparisons = 0;
unsigned long swaps = 0;


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            comparisons++;
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swaps++;
            }
        }
    }
} // PRONTO BUBBLE

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            swaps++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
} // PRONTO MERGE

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
} // PRONTO MERGE

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    comparisons++;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    comparisons++;
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        swaps++;
        heapify(arr, n, largest);
    }
} // PRONTO HEAP

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        swaps++;
        heapify(arr, i, 0);
    }
} // PRONTO HEAP

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
} // PRONTO 

int main() {
    
    int arr1[100]; // Base 1: 100 elementos aleatórios
    int arr2[1000]; // Base 2: 1000 elementos em ordem decrescente
    int arr3[10000]; // Base 3: 10.000 elementos com 50% ordenados

    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        arr1[i] = rand() % 100;
    }
    for (int i = 0; i < 1000; i++) {
        arr2[i] = 1000 - i;
    }
    for (int i = 0; i < 5000; i++) {
        arr3[i] = rand() % 10000;
    }
    for (int i = 5000; i < 10000; i++) {
        arr3[i] = i;
    }

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    clock_t start, end;
    double cpu_time_used;
    
    // <------------------- BubbleSort ------------------->
    
    // Testando Bubble Sort com Base 1
    printf("Base 1: Array desordenado de 100 elementos:\n");
    //imprimirArray(arr1, n1);
    
    start = clock();
    bubbleSort(arr1, n1);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Bubble Sort:\n");
    //imprimirArray(arr1, n1);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);
    comparisons = 0;
    swaps = 0;

    // Testando Bubble Sort com Base 2
    printf("\nBase 2: Array desordenado de 1000 elementos:\n");
    //imprimirArray(arr2, n2);
    
    start = clock();
    bubbleSort(arr2, n2);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Bubble Sort:\n");
    //imprimirArray(arr2, n2);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);

    // Testando Bubble Sort com Base 3
    printf("\nBase 3: Array desordenado de 10.000 elementos:\n");
    //imprimirArray(arr3, n3);
    
    start = clock();
    bubbleSort(arr3, n3);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Bubble Sort:\n");
    //imprimirArray(arr3, n3);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);
    
    // <------------------- MergeSort ------------------->
    
    // Testando Merge Sort com Base 1
    printf("\nBase 1: Array desordenado de 100 elementos:\n");
    //imprimirArray(arr1, n1);
    
    start = clock();
    mergeSort(arr1, 0, n1 - 1);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Merge Sort:\n");
    //imprimirArray(arr1, n1);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);
    comparisons = 0;
    swaps = 0;

    // Testando Merge Sort com Base 2
    printf("\nBase 2: Array desordenado de 1000 elementos:\n");
    //imprimirArray(arr2, n2);
    
    start = clock();
    mergeSort(arr2, 0, n2 - 1);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Merge Sort:\n");
    //imprimirArray(arr2, n2);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);
    comparisons = 0;
    swaps = 0;

    // Testando Merge Sort com Base 3
    printf("\nBase 3: Array desordenado de 10.000 elementos:\n");
    //imprimirArray(arr3, n3);
    
    start = clock();
    mergeSort(arr3, 0, n3 - 1);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Merge Sort:\n");
    //imprimirArray(arr3, n3);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);

    // <------------------- HeapSort ------------------->
    
    // Testando Heap Sort com Base 1
    printf("Base 1: Array desordenado de 100 elementos:\n");
    //imprimirArray(arr1, n1);
    
    start = clock();
    heapSort(arr1, n1);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Heap Sort:\n");
    //imprimirArray(arr1, n1);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);
    

    // Testando Heap Sort com Base 2
    printf("\nBase 2: Array desordenado de 1000 elementos:\n");
    //imprimirArray(arr2, n2);
    
    start = clock();
    heapSort(arr2, n2);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Heap Sort:\n");
    //imprimirArray(arr2, n2);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);

    // Testando Heap Sort com Base 3
    printf("\nBase 3: Array desordenado de 10.000 elementos:\n");
    //imprimirArray(arr3, n3);
    
    start = clock();
    heapSort(arr3, n3);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Array ordenado com Heap Sort:\n");
    //imprimirArray(arr3, n3);
    
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lu\n", comparisons);
    printf("Número de trocas: %lu\n", swaps);

    return 0;
}
