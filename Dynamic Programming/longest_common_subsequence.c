#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCS(char X[], char Y[])
{
    int m = strlen(X)+1;
    int n = strlen(Y)+1;
    int c[m][n];
    char b[m][n];
    for(int i=0;i<m;i++) c[i][0] = 0;
    for(int i=0;i<n;i++) c[0][i] = 0;
    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            if(X[i-1] == Y[j-1])
            {
                c[i][j] = c[i-1][j-1]+1;
                b[i][j] = '\\';
            }
            else if(c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = '|';
            }
            else 
            {
                c[i][j] = c[i][j-1];
                b[i][j] = '-';
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%c ", b[i][j]);
        }
        printf("\n");
        for(int j=0;j<n;j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char A[] = "ABCBDAB";
    char B[] = "BDCABA";
    LCS(A,B);
}
