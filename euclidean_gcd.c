#include <stdio.h>
#include <stdlib.h>

int gcd(int m, int n)
{
    if(n == 0) return m;
    else if(n>m) return gcd(n,m);
    else return gcd(n, m%n);
}

int main()
{
    
}
