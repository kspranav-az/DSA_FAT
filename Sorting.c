#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void bubble_sort(int arr[],int n){
    int i, j ;
    for(i = 0 ; i < n - 1; i++){
        for(j = 0 ; j< n - 1; j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertion_sort(int arr[],int n){
    int i , key , j;
    for(i = 1; i < n ; i++){
        key = arr[i];
        j = i -1;
        while(j>=0 && arr[j] > key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void selection_sort(int arr[],int n){
    int i, j, position, swap;
    for (i = 0; i < (n - 1); i++) {
        position = i;
        for (j = i + 1; j < n; j++) {
            if (arr[position] > arr[j])
            position = j;
        }
        if (position != i) {
            swap = arr[i];
            arr[i] = arr[position];
            arr[position] = swap;
        }
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
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

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

    
        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}


int main(){
    int arr[] = {64,34,25,12,22,11,90};
    int n = sizeof(arr)/sizeof(arr[0]);
    // bubble_sort(arr,n);
    //insertion_sort(arr,n);
    // selection_sort(arr,n);
    //merge_sort(arr,0,n-1);
    // quick_sort(arr,0,n-1);
    printf("Sorted array:");
    for(int i = 0 ; i < n ; i++ ){
        printf("%d ",arr[i]);
    }
    return 0;
}