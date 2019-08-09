/*
 * @author: tirthasheshpatel
 * @e-mail: tirthasheshpatel@gmail.com
 * @github: tirthasheshpatel@github.com
 * Summary: Implemented hash tables and resolved
 *          collisions using (primarily) chaining
 *          and open addressing.
 */

// Including necessary libraries.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Defining `M` which is the number of slots 
// in our hash table. Because we extract a
// 14-bit least significant bits of the hashed
// key, the maximum size of the slots, hash
// function would hash to, becomes 2^14.
#define M 16385

// The constant A which is used to perform
// hash by multiplication method is defined
// as `PHI` (conjugate of the golden number) 
// as stated in Knuth(2003) and cited in the
// book `Introduction to Algorithms` Section 11.
#define PHI 0.6180339887

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
    // Step 3: First element in the list so doesn't 
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


// A function to find the Hash Code of a integer key
// using the division method.
// h(k) = k modulo m;
// where m is the size of the hash table.
size_type hash_by_division_method(size_type key)
{
    /*
     * Arguments: `key` (size_type) -> A integer key to be hashed.
     * Hashes the given key using the division method for hashing.
     * Returns:   (size_type)       -> Hashed key.
     */
	return key%M;
}

// A function to find the hash code of the
// key using multiplication method proposed
// in the book `Introduction to algorithms`.
size_type hash_by_multiplication_method(size_type key)
{
    /*
     * Arguments: `key` (size_type) -> A integer key to be Hashed.
     * Hashes and returns the entered key using the multiplication method.
     * Returns  :       (size_type) -> 14-bit Hash Code of the given key.
     */


    // Set the bit-width 32 because at the end
    // we are going to multiply two 32 bit integers
    // to get a 64 bit long integer. Using 64 bit 
    // integer may lead to possible loss of data.
    unsigned long w = 4294967296; // Bit-width w = 2^32

    // Now, we have a constant A = PHI, that we 
    // need to convert in the form ` s / w `
    // such that `s` is the nearest integer that can
    // be represented as ` A * w `. As
    // `A = PHI`, we have `s = floor(PHI * w)`.
    // Then, we multiply the key with obtained `s`
    // => `l = key * s`
    // Now, we have `l = w * r1 + r0` where
    // `r0` is the fractional part of `l`.
    // We extract 14 most significant bits of `r0` 
    // to get our 14 bit hash key.
    return  ( ( ( (size_type)fmod((key*floor(PHI*w)),w) ) >> (32-14)) & ( 16384 - 1 ) );
}

// A function to find Hash Code of the key
// using linear probing. Used by hash tables
// in which collision is resolved by open addressing.
size_type open_address_linear_probing(size_type key, size_type probe)
{
    /*
     * Arguments: `key`   (size_type) -> Key to be hashed
     *            `probe` (size_type) -> Probe number assigned to the key.
     * Hashes the provided key using Linear Probing method
     * used to resolve collisions in hash tables using 
     * open addressing. The equation used to hash the key is:
     * `h(k) = ( h'(k) + probe ) modulo `M` where `k` = key
     * `h` = hash function, `h'` = other hash function, `M` = slots in the hash table
     * and `probe` = probe number of key `k`.
     * Returns:           (size_type) -> Hash Code of key.
     */
    return (hash_by_multiplication_method(key) + probe)%M;
}

// A function to find the hash code of a key
// using Quadratic Probing. Used by hash tables
// in which collision is resolved through
// open addressing.
size_type open_address_quadratic_probing(size_type key, size_type probe)
{
    /*
     * Arguments: `key`   (size_type) -> Key to be hashed.
     *            `probe` (size_type) -> Probe number assigned to the key.
     * Hashes the provided key using Quadratic Probing method
     * used to resolve collisions in hash tables using
     * open addressing. The equation used to hash the key is:
     * `h(k) = ( h'(k) + a*(probe) + b*(probe^2)) modulo M`
     * where `M` = Slots in the table, `k` = Key to be hashed,
     * `h'` = hash function, `a` and `b` = arbitary constants,
     * `probe` = Probe number of key `k`.
     * Returns:          (size_type) -> Hash Code of the key.
     */
    return (hash_by_multiplication_method(key) + 4*probe + 5*probe*probe)%M;
}

// A function to find the hash of a key
// using Double Hashing method used to 
// resolve the collisions in hash tables.
size_type open_address_double_hashing(size_type key, size_type probe)
{
    /*
     * Arguments: `key`   (size_type) -> Key to be hashed.
     *            `probe` (size_type) -> Probe number assigned to the key.
     * Hashes the provided key using two other hash functions
     * used to resolve collisions by providing the property of
     * almost random behaviour. It is used in hash tables
     * using Open Addressing to resolve collisions.
     * Returns:           (size_type) -> Hash Code of the key.
     */
    return ( hash_by_multiplication_method(key) + probe*hash_by_division_method(key) )%M;
}

// A function that inserts a key into the hash table in O(1) time.
void insert_in_hash_table(list_iterator *table, size_type key)
{
    /*
     * Arguments: `table` (list_iterator) -> A hash table with slots M.
     *            `key`   (size_type)     -> A key to be stored in the table.
     * Stores the entered key into the hash table in O(1) time.
     * The hash table resolves collisions through `Chaining`.
     * So, the keys are stored in a doubly linked list.
     * Returns: -
     */

    // Check if key to be stored is valid.
    if(key <= 0) return;

    // Find the 14-bit hash code of the key `key` using multiplication method.
    size_type hash = hash_by_multiplication_method(key);

    // The hash code of the key is now our new key or the 
    // index where the original key is to be stored
    // in the hash tables.
    if(table[hash]->key == -1) // Check if the slot is empty
    {
        // If empty, store the key in the first node of the doubly linked list.
        table[hash]->key = key;
        table[hash]->next = 0; // No next and previous node is present.
        table[hash]->prev = 0;
        return;
    }

    // If the slot is not empty, add a node to the list and store the key there.
    table[hash] = insert_in_front_of_the_doubly_linked_list(table[hash], key);
    return;
}


// Delete a key from the slot of the table in a average-case time O(ALPHA)
// where ALPHA = load factor = N/M. N = No of keys to be inserted, M = Slots present.
void delete_from_hash_table(list_iterator *table, size_type key)
{
    // Find the hash code of a key `key` using Multiplication Method.
    size_type hash = hash_by_multiplication_method(key);
    // Delete element from the doubly linked
    // list present at the hashed slot.
    // This function runs in linear time by first searching
    // for the key and deleting the found node if any.
    table[hash] = delete_from_the_doubly_linked_list(table[hash], key);
    return;
}

// Searches for a key in the hash table in linear time.
list_iterator search_in_hash_table(list_iterator *table, size_type key)
{
    /*
     * Arguments: `table`   (list_iterator) -> An object of Hash Table.
     *            `key`     (size_type)     -> A key to be stored in the hash table.
     * Hashes the key and searches for the original key in the hashed slot
     * using search function of doubly linked list.
     * Returns  : `element` (list_iterator) -> The found node where the key is present.
     */

    // Hash the key.
    size_type hash = hash_by_multiplication_method(key);
    // Search in the doubly linked list from the start.
    list_iterator element = search_from_start_in_the_doubly_linked_list(table[hash], key);
    return element; // return element if found otherwise return empty pointer.
}

int main()
{
    int key = 123456;
    printf("%lu\n", hash_by_multiplication_method(key));
}
