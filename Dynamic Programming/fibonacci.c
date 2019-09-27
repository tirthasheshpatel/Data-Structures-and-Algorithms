
/*
 * @author: tirthasheshpatel@gmail.com
 * Implement a program to find n'th term
 * in the fibonacci sequence through 
 * dynamic programming.
 */

#include <stdio.h>
#include <stdlib.h>

// We take as arguments: `n` -> The integer representing the term
//                              of the fibonacci sequence we want.
//                       `memo` -> A array storing the already appeared
//                                 fibonacci term.
int fibo(int n, int memo[])
{
    // If we have already came up with
    // the n'th fibonacci term return it.
    if(memo[n] != 0) return memo[n];
    // Otherwise, if n is 0 or 1 then return 1.
    else if(n == 0 || n == 1) return 1;
    // Otherwise, get the result and store it in the memory.
    int result = fibo(n-1, memo) + fibo(n-2, memo);
    memo[n] = result; // store result at index `n`
    return result; // return the result.
}

int fibo_bottom_up(int n)
{
    if(n == 0 || n == 1) return 1;
    int memo[n+1];
    memo[0] = 0;
    memo[1] = 1;
    for(int i=2;i<=n;i++)
    {
        memo[i] = memo[i-1] + memo[i-2]; 
    }
    return memo[n];
}

int main()
{
    int memo[11] = {0};
    printf("%d\n", fibo(10, memo));
    printf("%d\n", fibo_bottom_up(11));
}