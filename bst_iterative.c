#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _node {
    int key;
    struct _node* right;
    struct _node* left;
}Node;

void createTree(Node **root, int key)
{
    *root = (Node*)malloc(sizeof(Node));
    (*root)->key = key;
    (*root)->right = 0;
    (*root)->left = 0;
}

void insertRecursive(Node **root_ref, int key)
{
    if(!*root_ref) {
        createTree(root_ref, key);
        return;
    }
    if(key < (*root_ref)->key) {
        if((*root_ref)->left==0) {
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->key = key;
            temp->right = 0;
            temp->left = 0;
            (*root_ref)->left = temp;
            return;
        }
        insertRecursive(&(*root_ref)->left, key);
    }
    else if(key > (*root_ref)->key) {
        if((*root_ref)->right==0) {
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->key = key;
            temp->right = 0;
            temp->left = 0;
            (*root_ref)->right = temp;
            return;
        }
        insertRecursive(&(*root_ref)->right, key);
    }
    else if(key == (*root_ref)->key) {
        printf(key + " already present in the tree!");
        return;
    }
}

void insertIterative(Node **root_ref, int key)
{
    if(!*root_ref) {
        createTree(root_ref, key);
        return;
    }
    Node *root = *root_ref;
    Node *temp = root;
    while(1)
    {
        if(key < temp->key) {
            if(temp->left==0) {
                Node *new = (Node*)malloc(sizeof(Node));
                new->key = key;
                new->right = 0;
                new->left = 0;
                temp->left = new;
                return;
            }
            temp = temp->left;
        }
        else if(key > temp->key) {
            if(temp->right==0) {
                Node *new = (Node*)malloc(sizeof(Node));
                new->key = key;
                new->right = 0;
                new->left = 0;
                temp->right = new;
                return;
            }
            temp = temp->right;
        }
        else if(key == temp->key) {
            printf(key + " already present in the tree!");
            return;
        }
    }
}

void inorderTraversalRecursive(Node* root)
{
    if(!root) return;
    inorderTraversalRecursive(root->left);
    printf("%d ", root->key);
    inorderTraversalRecursive(root->right);
}

void inorderTraversalIterative(Node* root)
{
    Node* calls[100000];
    int top_call = -1;
    Node* temp;
    temp = root;
    while(temp!=0||top_call!=-1)
    {
        for(;temp;temp=temp->left) calls[++top_call]=temp;
        temp = calls[top_call--];
        printf("%d ", temp->key);
        temp = temp->right;
    }
    printf("\n");
}

void preorderTraversalIterative(Node* root)
{
    Node* calls[100000];
    int top_call = -1;
    Node* temp = root;
    while(temp!=0 || top_call!=-1)
    {
        for(;temp;temp=temp->left){
            printf("%d ", temp->key);
            calls[++top_call] = temp;
        }
        temp = calls[top_call--];
        temp = temp->right;
    }
    printf("\n");
}

void postorderTraversalIterative(Node* root)
{
    Node* calls[100000];
    int top_call = -1;
    Node* temp = root;
    do {
        while(root) {
            if(root->right) calls[++top_call] = root->right;
            calls[++top_call] = root;
            root = root->left;
        }
        root = calls[top_call--];
        if(root->right && calls[top_call]==root->right) {
            calls[top_call--];
            calls[++top_call] = root;
            root = root->right;
        }
        else {
            printf("%d ", root->key);
            root = 0;
        }
    }while(top_call!=-1);
    printf("\n");
}

int main(int argc, char** argv)
{
    Node* root = 0;
    insertIterative(&root, 10);
    insertIterative(&root, 5);
    insertIterative(&root, 20);
    insertIterative(&root, 15);
    insertIterative(&root, 12);
    insertIterative(&root, 6);
    inorderTraversalIterative(root);
    preorderTraversalIterative(root);
    postorderTraversalIterative(root);
}