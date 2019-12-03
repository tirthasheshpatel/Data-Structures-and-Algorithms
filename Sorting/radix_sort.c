#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max_element(int arr[], int n)
{
    int max_index=0;
    for(int i=0;i<n;i++) if(arr[i]>arr[max_index]) max_index=i;
    return max_index;
}

void _counting_sort_for_radix_sort(int arr[], int digit, int n)
{
    int aux[n];
    int freq[10] = {0};
    for(int i=0;i<n;i++) freq[(arr[i]/(int)pow(10.,digit-1))%10]++;
    for(int i=1;i<10;i++) freq[i] += freq[i-1];
    for(int i=0;i<n;i++)
    {
        int ind = (arr[i]/(int)pow(10.,digit-1))%10;
        aux[freq[ind]-1] = arr[i];
        freq[ind]--;
    }
    for(int i=0;i<n;i++) printf("%d ", aux[i]);
    printf("\n");
    for(int i=0;i<n;i++) arr[i] = aux[i];
}

void radix_sort(int arr[], int n)
{
    int max_index = max_element(arr, n);
    int digits = (int)log10(arr[max_index])+1;
    printf("%d ", digits);
    printf("\n");
    for(int i=1;i<=digits;i++)
    {
        _counting_sort_for_radix_sort(arr, i, n);
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1124,1233,4325,452,1231,5674,4433,2085,8890,9101};
    int aux[10];
    radix_sort(arr, 10);
    for(int i=0;i<10;i++) printf("%d ", arr[i]);

    return 0;
}