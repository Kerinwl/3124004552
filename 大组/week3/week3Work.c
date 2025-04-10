#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

// ��������
void InsertSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// �鲢����������
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// �鲢����
void MergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ���������������
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// ��������(�ݹ��)
void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// ��������
void CountSort(int arr[], int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    
    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) count[arr[i] - min]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    
    free(count);
    free(output);
}

// ������������ - ��ȡ���λ��
int getMaxDigits(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    int digits = 0;
    while (max != 0) {
        digits++;
        max /= 10;
    }
    return digits;
}

// ������������
void RadixCountSort(int arr[], int n) {
    int max_digits = getMaxDigits(arr, n);
    int exp = 1;
    int *output = (int *)malloc(n * sizeof(int));
    
    for (int d = 0; d < max_digits; d++) {
        int count[10] = {0};
        
        for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = 0; i < n; i++) arr[i] = output[i];
        exp *= 10;
    }
    free(output);
}

// �����������
void generateRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

// ��������
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// ���������㷨�ڴ��������µ�����
void testLargeDataPerformance() {
    int sizes[] = {10000, 50000, 200000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("���������������ܲ���:\n");
    printf("Size\tInsertSort\tMergeSort\tQuickSort\tCountSort\tRadixCountSort\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        int *temp = (int *)malloc(n * sizeof(int));
        
        generateRandomArray(arr, n, 0, 10000);
        
        printf("%d\t", n);
        
        // InsertSort
        copyArray(arr, temp, n);
        clock_t start = clock();
        InsertSort(temp, n);
        printf("%.3f\t", (double)(clock() - start) / CLOCKS_PER_SEC);
        
        // MergeSort
        copyArray(arr, temp, n);
        start = clock();
        MergeSort(temp, 0, n - 1);
        printf("%.3f\t", (double)(clock() - start) / CLOCKS_PER_SEC);
        
        // QuickSort
        copyArray(arr, temp, n);
        start = clock();
        QuickSort(temp, 0, n - 1);
        printf("%.3f\t", (double)(clock() - start) / CLOCKS_PER_SEC);
        
        // CountSort
        copyArray(arr, temp, n);
        start = clock();
        CountSort(temp, n);
        printf("%.3f\t", (double)(clock() - start) / CLOCKS_PER_SEC);
        
        // RadixCountSort
        copyArray(arr, temp, n);
        start = clock();
        RadixCountSort(temp, n);
        printf("%.3f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
        
        free(arr);
        free(temp);
    }
}

// ���������㷨��С������������������
void testSmallDataPerformance() {
    const int small_size = 100;
    const int iterations = 100000;
    int *arr = (int *)malloc(small_size * sizeof(int));
    int *temp = (int *)malloc(small_size * sizeof(int));
    
    printf("\nС����������������ܲ���(%d������%d������):\n", iterations, small_size);
    printf("Algorithm\tTotal Time\tAvg Time\n");
    
    generateRandomArray(arr, small_size, 0, 100);
    
    // InsertSort
    clock_t total_time = 0;
    for (int i = 0; i < iterations; i++) {
        copyArray(arr, temp, small_size);
        clock_t start = clock();
        InsertSort(temp, small_size);
        total_time += clock() - start;
    }
    printf("InsertSort\t%.3f\t%.6f\n", (double)total_time / CLOCKS_PER_SEC, 
           (double)total_time / (CLOCKS_PER_SEC * iterations));
    
    // MergeSort
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        copyArray(arr, temp, small_size);
        clock_t start = clock();
        MergeSort(temp, 0, small_size - 1);
        total_time += clock() - start;
    }
    printf("MergeSort\t%.3f\t%.6f\n", (double)total_time / CLOCKS_PER_SEC, 
           (double)total_time / (CLOCKS_PER_SEC * iterations));
    
    // QuickSort
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        copyArray(arr, temp, small_size);
        clock_t start = clock();
        QuickSort(temp, 0, small_size - 1);
        total_time += clock() - start;
    }
    printf("QuickSort\t%.3f\t%.6f\n", (double)total_time / CLOCKS_PER_SEC, 
           (double)total_time / (CLOCKS_PER_SEC * iterations));
    
    // CountSort
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        copyArray(arr, temp, small_size);
        clock_t start = clock();
        CountSort(temp, small_size);
        total_time += clock() - start;
    }
    printf("CountSort\t%.3f\t%.6f\n", (double)total_time / CLOCKS_PER_SEC, 
           (double)total_time / (CLOCKS_PER_SEC * iterations));
    
    // RadixCountSort
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        copyArray(arr, temp, small_size);
        clock_t start = clock();
        RadixCountSort(temp, small_size);
        total_time += clock() - start;
    }
    printf("RadixCountSort\t%.3f\t%.6f\n", (double)total_time / CLOCKS_PER_SEC, 
           (double)total_time / (CLOCKS_PER_SEC * iterations));
    
    free(arr);
    free(temp);
}

// ���ɲ������ݲ����浽�ļ�
void generateTestDataToFile(const char *filename, int n, int min, int max) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", rand() % (max - min + 1) + min);
    }
    
    fclose(file);
    printf("Generated %d numbers to %s\n", n, filename);
}

// ���ļ���ȡ���ݲ�����
void sortDataFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    int n;
    fscanf(file, "%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    
    printf("\nSorting data from %s (size: %d)\n", filename, n);

    // ����ÿ�������㷨
    clock_t start;
    
    // InsertSort
    copyArray(arr, temp, n);
    start = clock();
    InsertSort(temp, n);
    printf("InsertSort time: %.3f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    // MergeSort
    copyArray(arr, temp, n);
    start = clock();
    MergeSort(temp, 0, n - 1);
    printf("MergeSort time: %.3f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    // QuickSort
    copyArray(arr, temp, n);
    start = clock();
    QuickSort(temp, 0, n - 1);
    printf("QuickSort time: %.3f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    // CountSort
    copyArray(arr, temp, n);
    start = clock();
    CountSort(temp, n);
    printf("CountSort time: %.3f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    // RadixCountSort
    copyArray(arr, temp, n);
    start = clock();
    RadixCountSort(temp, n);
    printf("RadixCountSort time: %.3f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    free(arr);
    free(temp);
}

int main() {
    srand(time(NULL));
    
    // ���Դ���������������
    testLargeDataPerformance();
    
    // ����С�����������������
    testSmallDataPerformance();
    
    // ���ɲ������ݲ����浽�ļ�
    generateTestDataToFile("test_data.txt", 100000, 0, 10000);
    
    // ���ļ���ȡ���ݲ�����
    sortDataFromFile("test_data.txt");
    
    return 0;
}

