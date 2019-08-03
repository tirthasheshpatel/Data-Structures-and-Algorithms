#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef size_t size_type;
typedef struct Node* list_iterator;

struct Node
{
    int key;
    struct Node *prev, *next;
};

list_iterator create_doubly_linked_list(int key)
{
    list_iterator first = (list_iterator)malloc(sizeof(struct Node));
    first->key = key;
    first->prev = 0;
    first->next = 0;
    return first;
}

list_iterator insert_in_front_of_the_doubly_linked_list(list_iterator first, int key)
{
    list_iterator new_node = (list_iterator)malloc(sizeof(struct Node));
    new_node->key = key;
    new_node->next = first;
    first->prev = new_node;
    new_node->prev = 0;
    return new_node;
}

list_iterator insert_in_end_of_the_doubly_linked_list(list_iterator last, int key)
{
    list_iterator new_node = (list_iterator)malloc(sizeof(struct Node));
    new_node->key = key;
    new_node->prev = last;
    last->next = new_node;
    new_node->next = 0;
    return new_node;
}

list_iterator delete_from_the_front_of_the_doubly_linked_list(list_iterator first)
{
    if(first->next == 0){ free(first);return create_doubly_linked_list(-1); }
    list_iterator second = first->next;
    free(first);
    second->prev = 0;
    return second;
}

list_iterator delete_from_the_end_of_the_doubly_linked_list(list_iterator last)
{
    if(last->prev == 0){ free(last);return create_doubly_linked_list(-1); }
    list_iterator previous = last->prev;
    free(last);
    previous->next = 0;
    return previous;
}

list_iterator delete_from_the_doubly_linked_list(list_iterator first, size_type key)
{
    list_iterator it = first;
    while(it != 0)
    {
        if(it->key == key){
            if(it == first){ 
                first = delete_from_the_front_of_the_doubly_linked_list(it);
                return first;
            }
            if(it->next == 0){
                delete_from_the_end_of_the_doubly_linked_list(it);
                return first;
            }
            list_iterator temp1 = it->prev;
            list_iterator temp2 = it->next;
            temp1->next = it->next;
            temp2->prev = it->prev;
            free(it);
            break;
        }
        it = it->next;
    }
    return first;
}

list_iterator search_from_start_in_the_doubly_linked_list(list_iterator first, int key)
{
    list_iterator current_node = first;
    while(current_node != 0 && current_node->key != key) current_node = current_node->next;
    if(current_node != 0) return current_node;
    list_iterator temp = 0;
    return temp;
}

list_iterator search_from_end_in_the_doubly_linked_list(list_iterator last, int key)
{
    list_iterator current_node = last;
    while(current_node->key != key && current_node != 0) current_node = current_node->prev;
    if(current_node != 0) return current_node;
    list_iterator temp = 0;
    return temp;
}