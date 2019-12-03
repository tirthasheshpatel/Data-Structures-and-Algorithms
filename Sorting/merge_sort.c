#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int arr[], int left, int mid, int right)
{
    int left_size = mid-left+1;
    int right_size = right-mid;
    int arr_left[left_size], arr_right[right_size];

    for(int i=left;i<=mid;i++) arr_left[i-left] = arr[i];
    for(int i=mid+1;i<=right;i++) arr_right[i-mid-1] = arr[i];

    int i=left, j=0, k=0;
    while(j<left_size && k<=right_size)
    {
        if(arr_left[j]<arr_right[k]) arr[i++] = arr_left[j++];
        else arr[i++] = arr_right[k++];
    }

    while(j<left_size) arr[i++] = arr_left[j++];
    while(k<right_size) arr[i++] = arr_right[k++];
}

void merge_sort(int arr[], int left, int right)
{
    if(left<right)
    {
        int mid = (left+right)/2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1124,1233,4325,452,1231,5674,4433,2085,8890,9101};
    merge_sort(arr, 0, 9);
    for(int i=0;i<10;i++) printf("%d ", arr[i]);

    return 0;
}