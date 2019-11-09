#include <stdio.h>
#include <stdlib.h>
typedef struct node Node;
typedef struct node* list_iterator;

struct node
{
    int key;
    list_iterator next;
};

list_iterator create_singly_linked_list(int key)
{
    list_iterator first = (list_iterator)malloc(sizeof(Node));
    first->key = key;
    first->next = 0;
    return first;
}

list_iterator insert_after_in_singly_linked_list(int key, int prev_key, list_iterator first)
{
    list_iterator it = first;
    while(it->key != prev_key)
    {
        if(it->next == 0)
        {
            printf("Key not found!\n");
            return first;
        }
        it = it->next;
    }
    list_iterator new_node = (list_iterator)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = it->next;
    it->next = new_node;
    return first;
}

list_iterator insert_in_front_of_singly_linked_list(int key, list_iterator first)
{
    list_iterator new_node = (list_iterator)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = first;
    first->next = new_node;
    return first;
}

list_iterator insert_in_end_of_singly_linked_list(int key, list_iterator first)
{
    list_iterator it = first;
    while(it->next != 0)
    {
        it = it->next;
    }
    list_iterator new_node = (list_iterator)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = NULL;
    it->next = new_node;
    return first;
}

list_iterator insert_before_in_singly_linked_list(int key, int prev_key, list_iterator first)
{
    list_iterator it = first;
    list_iterator prev=  0;
    while(it->key != prev_key)
    {
        if(it->next == 0)
        {
            printf("Key not found!\n");
            return first;
        }
        prev = it;
        it = it->next;
    }
    if(prev == 0)
    {
        first = insert_in_front_of_singly_linked_list(key, first);
        return first;
    }
    list_iterator new_node = (list_iterator)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = it;
    prev->next = new_node;
    return first;
}

list_iterator delete_from_singly_linked_list(int key, list_iterator first)
{
    list_iterator prev = 0;
    list_iterator it = first;
    while(it->key != key)
    {
        if(it->next == 0)
        {
            printf("Key not found!\n");
            return first;
        }
        prev = it;
        it = it->next;
    }
    if(it == first)
    {
        first = first->next;
        free(it);
        return first;
    }
    prev->next = it->next;
    free(it);
    return first;
}

void transverse_in_singly_linked_list(list_iterator first)
{
    if(first == 0){
        printf("Empty!\n");
        return;
    }
    list_iterator it = first;
    while(it->next != 0)
    {
        printf("%d -> ", it->key);
        it = it->next;
    }
    printf("%d\n", it->key);
}

int main()
{
    list_iterator first = create_singly_linked_list(10);
    // 10
    first = insert_after_in_singly_linked_list(20, 10, first);
    first = insert_after_in_singly_linked_list(30, 20, first);
    first = insert_before_in_singly_linked_list(60, 30, first);
    first = insert_after_in_singly_linked_list(40, 10, first);
    transverse_in_singly_linked_list(first);
    first = delete_from_singly_linked_list(10, first);
    first = delete_from_singly_linked_list(30, first);
    transverse_in_singly_linked_list(first);
    first = delete_from_singly_linked_list(40, first);
    first = delete_from_singly_linked_list(20, first);
    transverse_in_singly_linked_list(first);
}
