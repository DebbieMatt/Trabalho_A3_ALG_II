#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long comparisons = 0;
unsigned long swaps = 0;
unsigned long comparisons_qs = 0;
unsigned long swaps_qs = 0;

void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    swaps_qs++;
}

int particao(int arr[], int baixo, int alto) {
    int pivoIndex = baixo + (alto - baixo + 1);
    troca(&arr[baixo], &arr[pivoIndex]);
    int pivo = arr[baixo];
    int i = baixo + 1;
    int j = alto;

    while (1) {
        while (i <= j && arr[i] > pivo) {
            comparisons_qs++;
            i++;
        }
        while (j >= i && arr[j] < pivo) {
            comparisons_qs++;
            j--;
        }
        if (i >= j) {
            break;
        }
        troca(&arr[i], &arr[j]);
    }
    troca(&arr[baixo], &arr[j]);
    return j;
}

void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particao(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

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
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[1000];
    int arr2[100];
    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        arr[i] = rand() % 1000;
    }

    for (int i = 0; i < 100; i++) {
        arr2[i] = rand() % 100;
    }

    int n = sizeof(arr) / sizeof(arr[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    // ARRAY DO MergeSort

    printf("Array desordenado de 1000 elementos:\n");
    imprimirArray(arr, n);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    
    printf("\nArray ordenado com mergeSort:\n");
    imprimirArray(arr, n);
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações (MergeSort): %lu\n", comparisons);
    printf("Número de trocas (MergeSort): %lu\n", swaps);
    
    // ARRAY DO quickSort 
    
    printf("\nArray desordenado de 100 elementos:\n");
    imprimirArray(arr2, n2);
    
    start = clock();
    quickSort(arr2, 0, n2 - 1);
    end = clock();

    printf("\nArray ordenado com quickSort:\n");
    imprimirArray(arr2, n2);

    printf("Número de comparações (QuickSort): %lu\n", comparisons_qs);
    printf("Número de trocas (QuickSort): %lu\n", swaps_qs);

    size_t total_memory = sizeof(arr) + sizeof(arr2);
    printf("Memória utilizada: %zu bytes\n", total_memory);

    return 0;
}
