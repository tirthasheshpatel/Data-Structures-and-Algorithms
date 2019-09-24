#include <stdio.h>
#include <stdlib.h>
#include "boilerplate.h"

#define print printf
#define scan scanf

void DFS(vertex_iterator* graph, int nb_vertices, vertex_iterator source)
{
    // graph = 1->2->3->4->5, source = 1
    int currTime = 0, explored = 0;
    Stack* s = (Stack*)malloc(sizeof(Stack));;
    init_stack(s);
    while(1)
    {
        push(s, source);
        source->color = 'G';
        source->start = currTime++;
        while(s->empty != 1)
        {
            vertex_iterator v = pop(s);
            list_iterator temp = v->adj_list;
            while(temp != 0)
            {
                currTime++;
                if(temp->key->color == 'W')
                {
                    temp->key->start = currTime;
                    temp->key->parent = v;
                    temp->key->color = 'G';
                    push(s, temp->key);
                }
                temp = temp->next;
            }
            v->end = ++currTime;
            v->color = 'B';
            print("Node with value %d fount at time %d and its exploration ended at time %d\n", v->value, v->start, v->end);
        }
        printf("Stack emptied!");

        explored = 1;
        for(int i=0;i<nb_vertices;i++)
        {
            if(graph[i]->color == 'W') 
            {
                source = graph[i];
                explored = 0;
                break;
            }
        }

        if(explored == 0) continue;
        free(s);
        break;
    }
}

int main(int argc, int argv[])
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
    print("Enter the source to run DFS on: ");
    scan("%d", &index);
    print("\n\n");
    DFS(graph, nb_vertices, graph[index]);
}