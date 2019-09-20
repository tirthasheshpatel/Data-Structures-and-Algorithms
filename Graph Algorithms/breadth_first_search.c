#include <stdio.h>
#include <stdlib.h>
#include "boilerplate.h"

#define print printf
#define scan scanf

void BFS(vertex_iterator source)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    initalize_queue(q, 1000);
    source->color = 'G';
    source->depth = 0;
    source->parent = 0;
    enqueue(q, source);
    while(q->front != -1)
    {
        vertex_iterator u = dequeue(q);
        list_iterator temp = u->adj_list;
        while(temp != 0)
        {
            if(temp->key->color == 'W')
            {
                // print("New vertex found at %x!\n", temp->key);
                temp->key->color = 'G';
                temp->key->depth = u->depth + 1;
                temp->key->parent = u;
                enqueue(q, temp->key);
            }
            temp = temp->next;
        }
        u->color = 'B';
        print("Node with value %d fount at depth %d\n", u->value, u->depth);
    }
}

int main(int argc, char *argv[])
{
    int nb_vertices;
    print("Enter the number of vertices in your graph: ");
    scan("%d", &nb_vertices);

    vertex_iterator* graph = (vertex_iterator*)malloc(nb_vertices*sizeof(vertex_iterator));

    print("Enter value of all the vertices: ");
    fflush(stdin);
    for(int i=0;i<nb_vertices;i++)
    {
        int temp;
        scan("%d", &temp);
        graph[i] = (vertex_iterator)malloc(sizeof(Vertex));
        graph[i]->value = temp;
        graph[i]->color = 'W';
        graph[i]->depth = -1;
        graph[i]->parent = 0;
        graph[i]->adj_list = 0;
        graph[i]->end = -1;
        graph[i]->start = -1;
        // print("Vertex added to graph\n");
    }

    print("Enter the index of nodes in the adjecent list of vertex with value \n");
    for(int i=0;i<nb_vertices;i++)
    {
        list_iterator templ = 0;
        int ind = 0;
        print("%d (terminate with `-1`): ", graph[i]->value);
        while(ind!=-1)
        {
            scan("%d", &ind);
            if(ind == -1) break;

            if(templ==0) templ = create_doubly_linked_list(graph[ind]);
            else templ = insert_in_front_of_the_doubly_linked_list(templ, graph[ind]);
        }
        graph[i]->adj_list = templ;
        fflush(stdin);
    }
    int index;
    print("Enter the source to run BFS on: ");
    scan("%d", &index);
    print("\n\n");
    BFS(graph[index]);
}