#include <stdio.h>
#include <stdlib.h>

void recursive_activity_selector(int (*set)[2], int a[], int i, int n, int k)
{
    int m = k+1;
    while(m < n && set[m][0] < set[k][1])
    {
        m++;
    }
    if(m<n)
    {
        a[i++] = m+1;
        recursive_activity_selector(set, a, i, n, m);
    }
}

void activity_selector(int (*set)[2], int a[], int n)
{
    recursive_activity_selector(set, a, 0, n, -1);
}

int main()
{
    int activities[][2] = {
        // {start, finish}
        {1,4},
        {3,5},
        {0,6},
        {5,7},
        {3,9},
        {5,9},
        {6,10},
        {8,11},
        {8,12},
        {2,14},
        {12,16}
    };
    int *a = (int*)calloc(11,sizeof(int));
    activity_selector(activities, a, 11);
    for(int i=0;i<11;i++) printf("%d ", a[i]);
}