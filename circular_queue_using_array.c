/*
 * @author: Urvashi, 18bce247@nirmauni.ac.in
 * Editor: tirthasheshpatel@gmail.com
 * Implemented circular queue using array in C.
 */

#include<stdio.h>
#include<stdlib.h>


struct queue
{
    int size;
    int front;
    int rear;
    int *que;
};


void insert(struct queue *q,int val)
{
    if(q->front==(q->rear+1)%q->size)
        printf("\nQueue Overflow!");
    else
    {
        q->rear=(q->rear+1)%q->size;
        q->que[q->rear]=val;
        if(q->front==-1)
            q->front=0;
    }
}


int delete(struct queue *q)
{
    if(q->front==-1)
    {
        printf("\nQueue Underflow!");
        exit(1);
    }
    
    else
    {
        int ele;
        ele=q->que[q->front];
        if(q->front==q->rear)
        {
            q->front=-1;
            q->rear=-1;
        }
        else
            q->front=(q->front+1)%q->size;
        return ele;
    }
}


void display(struct queue *q)
{
    printf("\nThe elements in queue are ");
    if(q->rear >= q->front){
        for(int i=q->front;i<=q->rear;i++)
        {
            printf("%d ",q->que[i]);
        }
    }
    else
    {
        for(int i=q->front;i<q->size || i%q->size<=q->rear;i++)
        {
            printf("%d ",q->que[i%q->size]);
        }
    }
}


int main()
{
    struct queue q;
    q.front=-1;
    q.rear=-1;
    printf("\nEnter the size of queue: ");
    scanf("%d",&q.size);
    q.que=(int *) malloc(q.size*sizeof(int));
    int val,ch;
    do
    {
        printf("\n1. Insert \n2. Delete \n3. Display \n4. Quit");
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        getchar();
        switch(ch)
        {
            case 1: printf("\nEnter the value to insert: ");
                    scanf("%d",&val);
                    insert(&q,val);
                    break;
            case 2: val=delete(&q);
                    printf("\nDeleted element is %d",val);
                    break;
            case 3: display(&q);
                    break;
            case 4: ch=4;
                    break;
            default: printf("\nEnter a valid choice!");
                    break;
        }
    } while (ch!=4);
}