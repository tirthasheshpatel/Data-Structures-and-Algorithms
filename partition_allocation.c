#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int search(int size, int partitions[], int n_partitions, const char method)
{
    int index = INT_MAX;
    if(method == 'f') {
        for(int i=0;i<n_partitions;i++) {
            if(partitions[i]>=size) {
                return i;
            }
        }
    }
    else if(method == 'n') {
        for(int i=n_partitions-1;i>=0;i--) {
            if(partitions[i]>=size) {
                return i;
            }
        }
    }
    else if(method == 'b') {
        int min_req = INT_MAX, min_ind = INT_MAX;
        for(int i=0;i<n_partitions;i++) {
            if(partitions[i]>=size && partitions[i]<min_req) {
                min_req = partitions[i];
                min_ind = i;
            }
        }
        return min_ind;
    }
    else if(method == 'w') {
        int max_req = INT_MIN, max_ind = INT_MAX;
        for(int i=0;i<n_partitions;i++) {
            if(partitions[i]>=size && partitions[i]>max_req) {
                max_req = partitions[i];
                max_ind = i;
            }
        }
        return max_ind;
    }
    else {
        printf("method %c not found.\n", method);
    }
    return index;
}

bool allocate_process(int processes[], int n_processes, int partitions[], int n_partitions, const char method)
{
    int **allocated_processes;
    allocated_processes = (int**)calloc(n_processes, sizeof(int*));
    for(int process=0;process<n_processes;process++)
    {
        int size = processes[process];
        int index = search(size, partitions, n_partitions, method);
        if(index>n_partitions) {
            printf("unable to allocate process %d.\n", process);
            printf("size of process: %d.\n", size);
            printf("available sizes of partitions: ");
            for(int i=0;i<n_partitions;i++) {
                printf("%d ", partitions[i]);
            }
            return false;
        }
        allocated_processes[process] = (int*)calloc(2, sizeof(int*));
        allocated_processes[process][0] = size;
        allocated_processes[process][1] = index;
        partitions[index] -= size;
    }
    printf("Processes allocated successfully!\n");
    printf("Process index\tSize    \tAllocated partition\n");
    for(int process=0;process<n_processes;process++) {
        printf("%-13d\t%-8d\t%d\n", 
                                  process,
                                  allocated_processes[process][0],
                                  allocated_processes[process][1]);
    }
    return true;
}

int main()
{
    int partitions[] = {100,200,300,400,500};
    int process[] = {150,350,50,25,50,50};
    allocate_process(process, 6, partitions, 5, 'l');
}