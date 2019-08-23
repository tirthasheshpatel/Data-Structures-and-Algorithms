#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 3

typedef struct queue Queue;

struct queue
{
    int front;
    int rear;
    int q[MAX+1][2];
};

// Deletes a element from the front of the Queue.
int* dequeue(Queue* q)
{
    /*
     * Arguments: `q` (Queue*) -> A referance to a Queue object
     * Deletes and returns the first element present in the Queue `q`.
     * Returns  : `ele` (int)  -> First element in the Queue `q`
     */

    // If the `front` and `rear` attributes of 
    // Queue `q` are overlapping
    // and are not equal to -1 means there is
    // only one element present in the Queue
    // which we will delete and reset the attributes
    // again to -1.
    if(q->front == q->rear && q->front != -1)
    {
        int *ele = q->q[q->front]; // get element in front of the queue
        q->q[q->front][0] = 0; // reinitialize the element
        q->q[q->front][1] = 0; // reinitialize priority
        q->front = q->rear = -1; // reset the attributes
        return ele; // return element.
    }

    // If the front or the rear attributes
    // are -1 means there are no elements
    // present in the queue and further
    // deletion doesn't make sense. So,
    // print error.
    else if(q->front == -1)
    {
        printf("Queue Underflow!\nTerminating Program...\n");
        exit(1); // terminate program
    }
    
    // Else delete element and increament
    // `front` attribute of Queue `q`.
    else
    {
        // extract the element
        int *ele = q->q[q->front];
        q->q[q->front][0] = 0; // reinitialize the element
        q->q[q->front][1] = 0;  // reinitialize priority
        q->front++; // increment front
        return ele; // return element
    }
}

void enqueue(Queue* q, int key, int priority)
{
    /*
     * Arguments: `q` (Queue*) -> A referance to a queue `q`.
     *            `key` (int)  -> A value to be inserted in the queue `q`.
     * Inserts `key` at the top of the queue `q`.
     */

    // If the rear of the queue has reached its
    // maximum `MAX` print error Overflow.
    if(q->rear == MAX){
        printf("Queue Overflow\nTerminating Program...\n");
        exit(1);
    }

    // Else insert key at the end of
    // the queue `q`.
    else
    {
        if(q->rear!=-1){
            int insertInd = q->rear;
            q->rear++; // increment attribute `rear`
            while(priority < q->q[insertInd][1])
            {
                q->q[insertInd+1][0] = q->q[insertInd][0];
                q->q[insertInd+1][1] = q->q[insertInd][1];
                insertInd--;
            }
            q->q[insertInd+1][0] = key; // insert key
            q->q[insertInd+1][1] = priority; // insert priority
        }
        else
        {
            q->rear++;
            q->q[q->rear][0] = key; // insert key
            q->q[q->rear][1] = priority; // insert priority
            q->front++;
        }
        
    }
}

void disp_queue(Queue* q)
{
    if(q->front == -1) printf("No elements present in the queue!");
    else for(int i=q->front;i<=q->rear;i++) printf("[%d]%d ", q->q[i][1], q->q[i][0]);
    printf("\n");
}

void init_queue(Queue* q)
{
    q->front = -1;
    q->rear = -1;
    for(int i=0;i<MAX;i++)
    {
        q->q[i][0] = q->q[i][1] = 0;
    }
}

int main()
{
    Queue que;
    init_queue(&que);
    enqueue(&que, 10, 1);
    enqueue(&que, 20, 2);
    enqueue(&que, 30, 3);
    enqueue(&que, 40, 1);
    disp_queue(&que);
}