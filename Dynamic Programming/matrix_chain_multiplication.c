#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_param_of_matrix_chain(int (*s)[6],int i, int j, int n)
{
    if(i == j) printf(" A[%d] ", i+1);
    else{ 
        printf("( ");
        print_param_of_matrix_chain(s, i, s[i][j], n);
        print_param_of_matrix_chain(s, s[i][j]+1, j, n);
        printf(" )");
    }
}

void matrix_chain_multiplication(int (*shape)[2], int n)
{
    int nb_mul[n][n],div[n][n],temp=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            nb_mul[i][j] = 0;
            div[i][j] = 0;
        }
    }
    for(int l=1;l<=n;l++)
    {
        for(int i=0;i<n-l;i++)
        {
            int j = i+l;
            nb_mul[i][j] = INT_MAX;
            for(int k=i;k<j;k++)
            {
                temp = nb_mul[i][k]+nb_mul[k+1][j]+shape[i][0]*shape[j][1]*shape[k][1];
                if(temp<nb_mul[i][j])
                {
                    nb_mul[i][j] = temp;
                    div[i][j] = k;
                }
            }
        }
    }
    printf("Multiplication Matrix: [start][end][cut]nb_mul\n");
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            printf("[%d][%d][%d]%d\n", i+1, j+1, div[i][j]+1, nb_mul[i][j]);
        }
    }
    printf("The optimal paranthesization is: ");
    print_param_of_matrix_chain(div,0,5,6);
}


int main()
{
    int n = 6;
    int shapes[6][2] = {
        {30,35},
        {35,15},
        {15,5},
        {5,10},
        {10,20},
        {20,25}
    };
    matrix_chain_multiplication(shapes, 6);



}