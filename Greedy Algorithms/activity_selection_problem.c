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

void greedy_activity_selector(int (*set)[2], int a[], int n)
{
    recursive_activity_selector(set, a, 0, n, -1);
}

// void dynamic_activity_selector(int (*set)[2], int a[], int n)
// {
//     int c[n][n];
//     for(int i=0;i<n;i++)
//     {
//         c[i][i] = 0;
//     }
//     for(int i=0;i<n-1;i++)
//     {
//         for(int j=i+1;j<n;j++)
//         {
//             c[i][j]=0;
//             for(int k=i;k<=j;k++)
//             {
//                 c[i][j] = max(c[i][j], c[i][k] + c[k][j] + 1);
//             }
//         }
//     }
//     printf("%d ", c[0][n-1]);
// }

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
    greedy_activity_selector(activities, a, 11);
    for(int i=0;i<11;i++) printf("%d ", a[i]);
}