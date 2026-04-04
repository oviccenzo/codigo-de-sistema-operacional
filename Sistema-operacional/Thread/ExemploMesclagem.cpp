#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *arr;
    int start;
    int end;
} ThreadData;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
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
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void *thread_sort(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    mergeSort(data->arr, data->start, data->end);
    pthread_exit(NULL);
}

void *thread_merge(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int mid = data->start + (data->end - data->start) / 2;
    merge(data->arr, data->start, mid, data->end);
    pthread_exit(NULL);
}

int main() {
    int original_list[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
    int n = sizeof(original_list) / sizeof(original_list[0]);
    int mid = n / 2;

    pthread_t thread1, thread2, thread3;
    ThreadData data1, data2, data3;

    data1.arr = original_list;
    data1.start = 0;
    data1.end = mid - 1;

    data2.arr = original_list;
    data2.start = mid;
    data2.end = n - 1;

    data3.arr = original_list;
    data3.start = 0;
    data3.end = n - 1;

    pthread_create(&thread1, NULL, thread_sort, &data1);
    pthread_create(&thread2, NULL, thread_sort, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_create(&thread3, NULL, thread_merge, &data3);
    pthread_join(thread3, NULL);

    printf("Lista ordenada: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", original_list[i]);
    }
    printf("\n");

    return 0;
}