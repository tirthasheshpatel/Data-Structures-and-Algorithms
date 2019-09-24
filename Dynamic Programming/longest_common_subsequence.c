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
    printf("\n");
    printf("  - ");
    for(int i=0;i<n;i++) printf("%c ", Y[i]);
    printf("\n");
    for(int i=0;i<m;i++)
    {
        printf("  ");
        for(int j=0;j<n;j++)
        {
            printf("%c ", b[i][j]);
        }
        printf("\n");
        if(i == 0) printf("- "); 
        else printf("%c ", X[i-1]);
        for(int j=0;j<n;j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    char lcs[c[m-1][n-1]+1];
    int i=m-1, j=n-1, k=c[m-1][n-1]-1;
    while(i!=0 && j!=0)
    {
        if(X[i-1] == Y[j-1])
        {
            lcs[k] = X[i-1];
            k--;
            i--;
            j--;
        }
        else if(c[i-1][j] >= c[i][j-1])
        {
            i--;
        }
        else j--;
    }
    lcs[c[m-1][n-1]] = '\0';
    printf("The lcs of %s and %s is %s.", X, Y, lcs);
}

int main()
{
    char A[] = "tirthasheshpatel";
    char B[] = "letaphsehsahtrit";
    LCS(A,B);
}
