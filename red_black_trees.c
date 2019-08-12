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
    return root;
}

tree_iterator left_rotate(tree_iterator root, tree_iterator x)
{
    tree_iterator y = x->right;
    tree_iterator x_cpy = (tree_iterator)malloc(sizeof(Node));
    tree_iterator y_cpy = (tree_iterator)malloc(sizeof(Node));
    tree_iterator root_cpy = 0;
    
    x_cpy->color = x->color;
    x_cpy->left = x->left;
    x_cpy->key = x->key;
    x_cpy->parent = y;
    x_cpy->right = y->left;

    y_cpy->left = x;
    y_cpy->right = y->right;
    y_cpy->parent = x->parent;
    y_cpy->color = y->color;
    y_cpy->key = y->key;

    if(x->parent == 0){
        root_cpy = (tree_iterator)malloc(sizeof(Node));
        root_cpy->color = y->color;
        root_cpy->key = y->key;
        root_cpy->left = y->left;
        root_cpy->right = y->right;
        root_cpy->parent = 0;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y_cpy;
    }
    else
    {
        x->parent->right = y_cpy;
    }
    free(x_cpy);
    free(y_cpy);
    if(root_cpy != 0){
        root = root_cpy;
        free(root_cpy);
    }
    return root;
}

// tree_iterator right_rotate(tree_iterator root, tree_iterator x)
// {
// }

int main()
{
    tree_iterator root = insert_root(10);
    root->left = (tree_iterator)malloc(sizeof(Node));
    root->left->parent = root;
    root->left->left = 0;
    root->left->color = 'R';
    root->left->key = 5;
    root->right = (tree_iterator)malloc(sizeof(Node));
    root->right->parent = root;
    root->right->right = 0;
    root->right->left = 0;
    root->right->color = 'B';
    root->right->key = 20;
    root->left->right->key = 50;
    root->left->right->color = 'B';
    root->left->right->right = 0;
    root->left->right->left = 0;
    root->left->right->parent = root->left->right;
    printf("left: %d root: %d right: %d\n", root->left->key, root->key, root->right->key);
    root = left_rotate(root, root->left);
    printf("left: %d root: %d right: %d\n", root->left->key, root->key, root->right->key);
}