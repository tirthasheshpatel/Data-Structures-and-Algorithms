#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int callbacks = 0;

int max(int num1, int num2)
{
    return (num1>num2)?num1:num2;
}

int cut_rod_top_down(int n, int rev[])
{
    callbacks++;
    if(n == 0) return 0;
    int r = INT_MIN;
    for(int i=0;i<n;i++)
    {
        r = max(r, rev[i] + cut_rod_top_down(n-i-1, rev));
    }
    return r;
}

int memoized_cut_rod(int n, int rev[], int memo[])
{
    callbacks++;
    if(n == 0) return 0;
    else if(memo[n-1] != -1)
    {
        return memo[n-1];
    }
    int r = INT_MIN;
    for(int i=0;i<n;i++)
    {
        r = max(r, rev[i] + memoized_cut_rod(n-i-1, rev, memo));
    }
    memo[n-1] = r;
    return r;
}

int main()
{
    int revenue[] = {1,5,8,9,10,17,17,20,24,30};
    int n = 6;
    printf("%d\n", cut_rod_top_down(n,revenue));
    printf("%d\n", callbacks);

    callbacks = 0;

    int memo[10];
    for(int i=0;i<10;i++) memo[i] = -1;
    printf("%d\n", memoized_cut_rod(n,revenue, memo));
    printf("%d\n", callbacks);
}