#include <stdio.h>
#include <stdlib.h>

void run_warshall(int graph[][4])
{
    int num_iterations = 4 + 1;
    for(int i=0;i<num_iterations;i++)
    {
        
    }
}

int main()
{
    int num_vertices = 4;
    int graph[4][4] = {
        {0 , 1 , 0 , 0},
        {1 , 0 , 1 , 0},
        {0 , 0 , 0 , 1},
        {1 , 0 , 0 , 0}
    };
    int set[4] = {-1};
    run_warshall(graph);

}