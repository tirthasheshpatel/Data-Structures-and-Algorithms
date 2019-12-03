/*
 * @author: tirthasheshpatel
 * @g-mail: tirthasheshpatel@gmail.com
 * Summary: Queue implemented using static array
 */

// Inclusing necessary libraries
#include <stdio.h> // printf, scanf, fflush
#include <stdlib.h> 

#define MAX 65535

// Alternate for `struct queue`
typedef struct queue Queue;
// Alternate for `size_t`
typedef size_t size_type;

// A stucture for Queue holding attributes:
// `front`: A integer indicating the first element in the array
// `rear` : A integer indicating the last element in the array.
// `q`    : A array (of size `MAX`) holding values in the queue.
struct queue
{
    int front;
    int rear;
    int q[MAX+1];
};

// Deletes a element from the front of the Queue.
int dequeue(Queue* q)
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
        int ele = q->q[q->front]; // get element in front of the queue
        q->q[q->front] = 0; // reinitialize the element
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
        int ele = q->q[q->front];
        q->q[q->front] = 0; // reinitialize the element
        q->front++; // increment front
        return ele; // return element
    }
}

void enqueue(Queue* q, int key)
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
        q->rear++; // increment attribute `rear`
        q->q[q->rear] = key; // insert key
        // If this is the first element inserted
        // in the Queue, do q->front = 0;
        if(q->front == -1) q->front++;
    }
}

void disp_queue(Queue* q)
{
    if(q->front == -1) printf("No elements present in the queue!");
    else for(int i=q->front;i<=q->rear;i++) printf("%d ", q->q[i]);
    printf("\n");
}

int main()
{
    Queue que = {-1,-1,0};
    enqueue(&que, 10);
    enqueue(&que, 20);
    disp_queue(&que);
    dequeue(&que);
    disp_queue(&que);
    dequeue(&que);
    disp_queue(&que);
}