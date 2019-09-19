#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct node* tree_iterator;

struct node
{
    int key;
    tree_iterator parent, left, right;
};

tree_iterator create(int key)
{
    tree_iterator root = (tree_iterator)malloc(sizeof(Node));
    root->key = key;
    root->left = 0;
    root->right = 0;
    root->parent = 0;
    return root;
}

tree_iterator insert(int key, tree_iterator root)
{
    tree_iterator it = root;
    if(root==0) return root;
    while(1)
    {
        if(key < it->key){
            if(it->left == 0) break;
            it = it->left;
        }
        else{
            if(it->right == 0) break;
            it = it->right;
        }
    }
    tree_iterator newNode = (tree_iterator)malloc(sizeof(Node));
    newNode->key = key;
    newNode->parent = it;
    newNode->left = 0;
    newNode->right = 0;
    if(key<it->key) it->left = newNode;
    else it->right = newNode;
    return root;
}

void inorder(tree_iterator root)
{
    if(root==0) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(tree_iterator root)
{
    if(root==0) return;
    preorder(root->left);
    preorder(root->right);
    printf("%d ", root->key);
}

void postorder(tree_iterator root)
{
    if(root==0) return;
    printf("%d ", root->key);
    postorder(root->left);
    postorder(root->right);
}

int main()
{
    tree_iterator root = create(10);
    root = insert(20,root);
    root = insert(5,root);
    root = insert(1,root);
    root = insert(8,root);
    root = insert(6,root);
    inorder(root);
}