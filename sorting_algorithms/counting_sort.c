#include <stdio.h>
#include <stdlib.h>

int max_element(int arr[], int n)
{
    int max_index=0;
    for(int i=0;i<n;i++) if(arr[i]>arr[max_index]) max_index=i;
    return max_index;
}

void counting_sort(int arr[], int aux[], int n)
{
    // Step 1: Count the frequency of each digit.
    int max_index = max_element(arr, n);
    int freq_arr_size = arr[max_index]+1;
    int *freq = (int*)calloc(freq_arr_size, sizeof(int));
    for(int i=0;i<n;i++)
    {
        freq[arr[i]]++;
    }
    for(int i=1;i<arr[max_index]+1;i++) freq[i] += freq[i-1];

    // Step 3: Start arranging
    for(int i=0;i<n;i++)
    {
        aux[freq[arr[i]]-1] = arr[i];
        freq[arr[i]]--;
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1124,1233,4325,452,1231,5674,4433,2085,8890,9101};
    int aux[10];
    counting_sort(arr, aux, 10);
    for(int i=0;i<10;i++) printf("%d ", aux[i]);

    return 0;
}