#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

int arr[MAX_SIZE];
int moratab_arr[MAX_SIZE];

typedef struct {
    int start;
    int end;
    int *array;
} ThreadData;


void bubbleSort(int *array, int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - 1 - (i - start); j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void* sort(void* param) {
    ThreadData* data = (ThreadData*) param;
    bubbleSort(data->array, data->start, data->end);
    pthread_exit(NULL);
}

void mergeArrays(int *arr1, int start1, int end1, int *arr2, int start2, int end2, int *out) {
    int i = start1, j = start2, k = 0;
    while (i < end1 && j < end2) {
        if (arr1[i] < arr2[j]) {
            out[k++] = arr1[i++];
        } else {
            out[k++] = arr2[j++];
        }
    }
    while (i < end1) {
        out[k++] = arr1[i++];
    }
    while (j < end2) {
        out[k++] = arr2[j++];
    }
}

int main() {
    int n;
    printf(" tedad adad ra vared konid (hadaksar %d): ", MAX_SIZE);
    scanf("%d", &n);
    if (n > MAX_SIZE || n <= 0) {
        printf("tedad bin 1 %d bashad.\n", MAX_SIZE);
        return 1;
    }

    printf("adad ra vared konid :\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int mid = n / 2;

    pthread_t t1, t2, t3;
    ThreadData data1, data2;

    data1.start = 0;
    data1.end = mid;
    data1.array = arr;

    data2.start = mid;
    data2.end = n;
    data2.array = arr;

    pthread_create(&t1, NULL, sort, &data1);
    pthread_create(&t2, NULL, sort, &data2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    mergeArrays(arr, 0, mid, arr, mid, n, moratab_arr);

    printf("list:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", moratab_arr[i]);
    }
    printf("\n");

    return 0;
}
