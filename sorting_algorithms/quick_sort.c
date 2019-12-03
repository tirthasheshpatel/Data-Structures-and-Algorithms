#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int start, int end)
{
    int pivot = arr[end];
    int i = start-1,j=start,k=end;
    while(j != k)
    {
        if(arr[j] <= arr[k])
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
        j++;
    }
    swap(&arr[i+1], &arr[k]);
    return i+1;
}

void quick_sort(int arr[], int start, int end)
{
    if(start<end)
    {
        int i = partition(arr, start, end);
        quick_sort(arr, start, i-1);
        quick_sort(arr, i+1, end);
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1124,1233,4325,452,1231,5674,4433,2085,8890,9101};
    quick_sort(arr, 0, 9);
    for(int i=0;i<10;i++) printf("%d ", arr[i]);

    return 0;
}