#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int left(int i){ return 2*i+1; }
int right(int i){ return 2*i+2; }
int parent(int i){ return i/2; } // Not used

void max_heapify(int arr[], int i, int n)
{
    int largest = i;
    int right_child = right(i);
    int left_child = left(i);
    if(right_child<n&&arr[right_child]>arr[largest]) largest = right_child;
    if(left_child<n&&arr[left_child]>arr[largest]) largest = left_child;
    if(largest!=i) {
        swap(&arr[largest], &arr[i]);
        max_heapify(arr, largest, n);
    }
}

void create_max_heap(int arr[], int n)
{
    for(int i=n/2-1;i>=0;i--) max_heapify(arr, i, n);
}

void heap_sort(int arr[], int n)
{
    create_max_heap(arr, n);
    while(n)
    {
        swap(&arr[0], &arr[--n]);
        max_heapify(arr, 0, n);
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1124,1233,4325,452,1231,5674,4433,2085,8890,9101};
    heap_sort(arr, 10);
    for(int i=0;i<10;i++) printf("%d ", arr[i]);

    return 0;
}