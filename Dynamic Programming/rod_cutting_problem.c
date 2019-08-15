#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct pair Pair;

struct pair
{
    int x;
    int y;
};

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

int memoized_cut_rod_top_down(int n, int rev[], int memo[])
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
        r = max(r, rev[i] + memoized_cut_rod_top_down(n-i-1, rev, memo));
    }
    memo[n-1] = r;
    return r;
}

int memoized_cut_rod_bottom_up(int n, int rev[])
{
    int memo[n+1];
    memo[0] = 0;
    int r;
    for(int i=1;i<=n;i++)
    {
        r = INT_MIN;
        for(int j=1;j<=i;j++)
        {
            r = max(r, rev[j-1] + memo[i-j]);
        }
        memo[i] = r;
    }
    return memo[n];
}

Pair extended_memoized_cut_rod_bottom_up(int n, int rev[])
{
    int memo[n+1];
    int cuts[n+1];
    Pair p = {-1,-1};
    memo[0] = 0;
    int r;
    for(int i=1;i<=n;i++)
    {
        r = INT_MIN;
        for(int j=1;j<=i;j++)
        {
            if(r < rev[j-1] + memo[i-j]){
                r = rev[j-1] + memo[i-j];
                cuts[i] = j;
            }
        }
        memo[i] = r;
    }
    p.x = memo[n];
    p.y = cuts[n];
    return p;
}

int main()
{
    int revenue[] = {1,5,8,9,10,17,17,20,24,30};
    int n = 10;
    printf("Top-Down  : %d\n", cut_rod_top_down(n,revenue));
    printf("Callbacks : %d\n\n", callbacks);

    callbacks = 0;

    int memo[10];
    for(int i=0;i<10;i++) memo[i] = -1;
    printf("Memoized top-down : %d\n", memoized_cut_rod_top_down(n,revenue, memo));
    printf("Callbacks         : %d\n\n", callbacks);

    printf("Memoized bottom-up: %d\n\n", memoized_cut_rod_bottom_up(n,revenue));

    for(int i=0;i<=n;i++)
    {
        Pair p = extended_memoized_cut_rod_bottom_up(i, revenue);
        printf("Revenue: %d Optimum Cut: %d\n", p.x, p.y);
    }
}