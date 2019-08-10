#include <stdio.h>
#include <stdlib.h>

typedef struct node* tree_iterator;
typedef struct node Node;

struct node
{
    int key;
    tree_iterator left, right, parent;
    char color;
};

tree_iterator insert_root(int key)
{
    tree_iterator root = (tree_iterator)malloc(sizeof(Node));
    root->key = key;
    root->color = 'B';
    root->left = 0;
    root->right = 0;
    root->parent = 0;
}

tree_iterator left_rotate(tree_iterator root, tree_iterator x)
{
    tree_iterator y = x->right;
    x->right = y->left;
    if(y->left != 0) y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == 0) root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

tree_iterator right_rotate(tree_iterator root, tree_iterator x)
{
    tree_iterator y = x->parent;
    y->left = x->right;
    if(x->right != 0) x->right->parent = y;
    x->parent = y->parent;
    if(y->parent == 0) root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
    return root;

}

int main()
{
    tree_iterator root = insert_root(10);
    root->left = (tree_iterator)malloc(sizeof(Node));
    root->left->parent = root;
    root->left->right = 0;
    root->left->left = 0;
    root->left->color = 'R';
    root->left->key = 5;
    root->right = (tree_iterator)malloc(sizeof(Node));
    root->right->parent = root;
    root->right->right = 0;
    root->right->left = 0;
    root->right->color = 'B';
    root->right->key = 20;
    printf("left: %d root: %d right: %d", root->left->key, root->key, root->right->key);
}