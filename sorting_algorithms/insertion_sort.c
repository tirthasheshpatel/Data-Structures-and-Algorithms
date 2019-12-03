#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int n)
{
    for(int i=1;i<n;i++)
    {
        int key = arr[i];
        int j=i-1;
        if(key<arr[j])
        {
            while(j>=0 && key<arr[j])
            {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1124,1233,4325,452,1231,5674,4433,2085,8890,9101};
    insertion_sort(arr, 10);
    for(int i=0;i<10;i++) printf("%d ", arr[i]);

    return 0;
}