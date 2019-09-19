/*
 * author: @tirthasheshpatel
 * Base code for all Graph Algorithms
 * Contains implementation of: Queue, Stack, Linked Lists.
 */

#ifndef GUARD_BOILERPLATE_H
#define GUARD_BOILERPLATE_H

// Importing dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define INF 2147483647;

// Making the `size_t` keyword easier to interpret.
typedef size_t size_type;
// A pointer to the nodes in the list
// is defined for easy use in functions.
typedef struct Node* list_iterator;
typedef struct vertex* vertex_iterator;


// A structure of `Node` used in the
// doubly linked list for storing keys
// and pointers to neighbouring Nodes.
struct Node
{
    vertex_iterator key; // Stores the value to be accessed by the user at runtime.
    // Pointers to the next and previous elements in the list.
    list_iterator prev, next;
};


typedef struct vertex
{
    int value;
    char color;
    int depth;
    vertex_iterator parent;
    list_iterator adj_list;
}Vertex;


typedef struct queue
{
    int size;
    int front;
    int rear;
    vertex_iterator* que;
}Queue;


// A function that creates and initializes the
// doubly linked list.
list_iterator create_doubly_linked_list(vertex_iterator key)
{

    /*
     * Arguments: `key`   (int)           -> A value to be stored in the list.
     * Creates a doubly linked list.
     * Returns  : `first` (list_iterator) -> A pointer to the first element of list.
     */

    // Step 1: Allocate memory to store a variable of type `Node`.
    list_iterator first = (list_iterator)malloc(sizeof(struct Node));
    // Step 2: Initialize key as provided by the user.
    first->key = key;
    // Step 3: First element in the list so it doesn't 
    // have next and prev elements.
    first->prev = 0;
    first->next = 0;

    // Step 4: Return the pointer to allocated node.
    return first;
}

// Insert a node at the front of the linked list in O(1) time.
list_iterator insert_in_front_of_the_doubly_linked_list(list_iterator first, vertex_iterator key)
{
    /*
     * Argments: `first` (list_iterator) -> A pointer to the first element in the list.
     *                                      Initialize the list using `create_doubly_linked_list()`
     *                                      to get this pointer variable
     *           `key`   (int)           -> The element to be stored in the list.
     * This function is used to insert a Node at the front of the 
     * doubly linked list. The Node is intialized by the provided value
     * of the key and other attributes are initalized according to
     * the previously allocated nodes.
     * Returns: `new_node` (list_iterator) -> A pointer variable pointing at the new
     *                                        Node inserted using this function.
     */

    // Step 1: Allocate memory for the new node to be stored.
    list_iterator new_node = (list_iterator)malloc(sizeof(struct Node));

    // Step 2: Initialize the key using the key provided by user.
    // Step 3: This node has the `next` member as `first`
    //         which used to be the first Node in the list.
    // Step 4: Also, don't forget to add the newly allocated
    //         node as the previous member of the `first` Node.
    // Step 5: The previous member is still `NULL`.
    new_node->key = key;
    new_node->next = first;
    first->prev = new_node;
    new_node->prev = 0;

    // Step 6: Return the newly allocated node which will act as the 'first' node in the list.
    return new_node;
}

void initalize_queue(Queue* q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->que = (vertex_iterator*)malloc(size*sizeof(vertex_iterator));
    for(int i=0;i<q->size;i++)
    {
        q->que[i] = 0;
    }
    // printf("Queue Initialized!!\n\n");
}

void reintialize_in_queue(Queue* q)
{
    q->que[q->front] = 0;
}

void enqueue(Queue* q, vertex_iterator val)
{
    if(q->front==(q->rear+1)%q->size){
        printf("\nQueue Overflow!");
        exit(1);
    }
    else
    {
        q->rear=(q->rear+1)%q->size;
        q->que[q->rear]=val;
        if(q->front==-1)
            q->front=0;
    }
}


vertex_iterator dequeue(Queue* q)
{
    if(q->front==-1)
    {
        printf("\nQueue Underflow!");
        exit(1);
    }
    else
    {
        vertex_iterator ele;
        ele=q->que[q->front];
        if(q->front==q->rear)
        {
            reintialize_in_queue(q);
            q->front=-1;
            q->rear=-1;
        }
        else
        {
            reintialize_in_queue(q);
            q->front=(q->front+1)%q->size;
        }
        return ele;
    }
}

#endif