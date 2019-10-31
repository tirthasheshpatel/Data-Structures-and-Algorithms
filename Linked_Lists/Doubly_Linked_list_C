#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Making the `size_t` keyword easier to interpret.
typedef size_t size_type;
// A pointer to the nodes in the list
// is defined for easy use in functions.
typedef struct Node* list_iterator;


// A structure of `Node` used in the
// doubly linked list for storing keys
// and pointers to neighbouring Nodes.
struct Node
{
    int key; // Stores the value to be accessed by the user at runtime.
    // Pointers to the next and previous elements in the list.
    struct Node *prev, *next;
};


// A function that creates and initializes the
// doubly linked list.
list_iterator create_doubly_linked_list(int key)
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
list_iterator insert_in_front_of_the_doubly_linked_list(list_iterator first, int key)
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


// Insert a Node at the end of the linked list in O(1) time.
list_iterator insert_in_end_of_the_doubly_linked_list(list_iterator last, int key)
{
    /*
     * Argments: `last` (list_iterator) -> A pointer to the last element in the list.
     *           `key`  (int)           -> The element to be stored in the list.
     * This function is used to insert a Node at the end of the 
     * doubly linked list. The Node is intialized by the provided value
     * of the key and other attributes are initalized according to
     * the previously allocated nodes.
     * Returns: `new_node` (list_iterator) -> A pointer variable pointing at the new
     *                                        Node inserted using this function.
     */

    // Step 1: Allocate memory required to store the new node to be inserted in the list.
    list_iterator new_node = (list_iterator)malloc(sizeof(struct Node));

    // Step 2: Initialize the key according to the value of key
    //         provided by the user.
    // Step 3: The attribute `prev` will be a pointer to the last node
    //         in the list. i.e. `last`.
    // Step 4: Don't forget to change the `next` attribute of the 
    //         node `last` to `new_node`.
    // Step 5: The next member of the list is still NULL.
    new_node->key = key;
    new_node->prev = last;
    last->next = new_node;
    new_node->next = 0;

    // Step 6: Return a pointer to the newly allocated element in the list.
    return new_node;
}

// Delete a Node from the end of a linked list in O(1) time.
list_iterator delete_from_the_front_of_the_doubly_linked_list(list_iterator first)
{
    /*
     * Arguments: `first` (list_iterator) -> A pointer to the first element in the list.
     * Deletes the first element in the linked list.
     * Returns: `second`  (list_iterator) -> A pointer to second element in the list. 
     */

    // Step 1: Check if there is any other node present in the list.
    //         If no node is present, delete the `first` pointer and 
    //         hence the whole linked list.
    //         Return new linked list initialized by key -1.
    if(first->next == 0){ free(first);return create_doubly_linked_list(-1); }

    // Step 2: Create a pointer to the next element in the list.
    list_iterator second = first->next;

    // Step 3: Delete the `first` pointer pointing to the first element in the list.
    free(first);

    // Step 4: Update the `prev` attribute of the second node to NULL.
    second->prev = 0;

    // Step 5: Return thr second element.
    return second;
}

// Delete a Node from the end of the linked list in O(1) time.
list_iterator delete_from_the_end_of_the_doubly_linked_list(list_iterator last)
{
    /*
     * Arguments: `last`    (list_iterator) -> A pointer to the last element in the list.
     * Deletes the last element in the linked list.
     * Returns: `previous`  (list_iterator) -> A pointer to second element in the list. 
     */

    // Step 1: Check if there is any other node present in the list.
    //         If no node is present, delete the `last` pointer and 
    //         hence the whole linked list.
    //         Return new linked list initialized by key -1.
    if(last->prev == 0){ free(last);return create_doubly_linked_list(-1); }

    // Step 2: Create a pointer to the previous element in the list.
    list_iterator previous = last->prev;
    // Step 3: Delete the `last` pointer pointing to the last element in the list.
    free(last);
    // Step 4: Update the `next` attribute of the previous node to NULL.
    previous->next = 0;
    // Step 5: Return thr previous element.
    return previous;
}

// Deletes a element from the linked list in O(n) time.
list_iterator delete_from_the_doubly_linked_list(list_iterator first, size_type key)
{
    /*
     * Arguments: `first` (list_iterator) -> A pointer to the first element in the list.
     *            `key`   (size_type)     -> A key to be deleted from the linked list.
     * Deletes the key from the linked list.
     */

    // Step 1: Make a copy of `first` list_iterator.
    list_iterator it = first;

    // Step 2: Now, iterate through the list until no more elements are left.
    while(it != 0)
    {
        // Step 3: If the key is found then
        if(it->key == key){
            // Case 1: It is the first element in the list.
            //         So, delete it using `delete_from_the_front_of_the_doubly_linked_list`.
            if(it == first){ 
                first = delete_from_the_front_of_the_doubly_linked_list(it);
                return first; // return the new first pointer to the list.
            }
            // Case 2: It is the last element in the list.
            //         So, delete it using `delete_from_the_end_of_the_doubly_linked_list`
            if(it->next == 0){
                delete_from_the_end_of_the_doubly_linked_list(it);
                return first; // return original first pointer.
            }

            // Case 3: It is a element somewhere in between the linked list.
            list_iterator temp1 = it->prev; // Make a copy of `prev` and `next` nodes of found node.
            list_iterator temp2 = it->next;
            // Now, the new `next` member of the node `temp1` is the `next` member of `it`.
            temp1->next = it->next;
            // Similarly, change the pointer `prev` of temp2 to be the next node of `it`.
            temp2->prev = it->prev;
            free(it); // Delete `it`.
            break; // terminate loop as we found the key.
        }
        // move ahead in the list.
        it = it->next;
    }
    return first; // return the new/original first pointer to the list.
}

// Searches a element with specified key
list_iterator search_from_start_in_the_doubly_linked_list(list_iterator first, int key)
{
    /*
     * Arguments: `first` (list_iterator) -> A pointer to the first node in the list.
     *            `key`   (int)           -> A key to be retrived during search.
     * Search and returns a pointer to the node having the specified key.
     * Returns:   `temp`  (list_iterator) -> A pointer to the found node.
     */

    // Make a copy of the first pointer to use
    // it during iteration.
    list_iterator current_node = first;
    // Iterate until key is found and the node pointer is not empty.
    while(current_node != 0 && current_node->key != key) current_node = current_node->next; // move ahead in the list
    if(current_node != 0) return current_node; // if the node is not empty return.
    list_iterator temp = 0; // else return a empty pointer.
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

int main()
{
    // Creating a doubly linked list.
    list_iterator first = create_doubly_linked_list(10);
    
    // Insert 10 20 and 30 in the front of the doubly linked list.
    first = insert_in_front_of_the_doubly_linked_list(first, 10);
    first = insert_in_front_of_the_doubly_linked_list(first, 20);
    first = insert_in_front_of_the_doubly_linked_list(first, 30);
    
    // Print the list
    list_iterator it = first;
    while(it!=0){
        printf("%d ", it->key);
        it = it->next;
    }
}
