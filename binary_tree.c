#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct TreeNode
{
    int key;
    struct TreeNode* right;
    struct TreeNode* left;
    struct TreeNode* parent;
};

struct TreeNode *new_tree_node(int value, struct TreeNode* parent)
{
    struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    n->key = value;
    n->left = NULL;
    n->right = NULL;
    n->parent = parent;
    return n;
}

struct TreeNode* insert_root_in_binary_tree(int key)
{
    return new_tree_node(key, 0);
}


struct TreeNode* insert_in_binary_tree(struct TreeNode* node, struct TreeNode* parent, int key)
{
    if(node == NULL) return new_tree_node(key, parent);
    if(node->key == key) perror("key already present in the tree!");
    if(key < node->key) node->left = insert_in_binary_tree(node->left, key, node);
    else node->right = insert_in_binary_tree(node->right, key, node);
    return node;
}

struct TreeNode* tree_successor(struct TreeNode* node)
{
    if(node->right != 0) return tree_minimum(node->right);
    struct TreeNode* x = node;
    struct TreeNode* y = node->parent;
    while(y != 0 && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
    
}

// Deleting has not been implemented yet! Please come later.
/*
void delete_from_binary_tree(struct TreeNode* node)
{
    if(node->left == 0 && node->right == 0) free(node);
    else if(node->left == 0){
        struct TreeNode* temp = node->parent;
        node->right->parent = temp;
        if(temp->left == node) temp->left = node->right;
        else temp->right = node->right;
        free(node);
    }
    else if(node->right == 0){ 
        struct TreeNode* temp = node->parent;
        node->left->parent = temp;
        if(temp->left == node) temp->left = node->left;
        else temp->right = node->left;
        free(node);
    }
    else if()
}
*/

void inorder_transversal(struct TreeNode* node)
{
    if(node != NULL){
        inorder_transversal(node->left);
        printf("%d ", node->key);
        inorder_transversal(node->right);
    }
}

void preorder_transversal(struct TreeNode* node)
{
    if(node != NULL){
        printf("%d ", node->key);
        preorder_transversal(node->left);
        preorder_transversal(node->right);
    }
}

void postorder_transversal(struct TreeNode* node)
{
    if(node != NULL){
        postorder_transversal(node->left);
        postorder_transversal(node->right);
        printf("%d ", node->key);
    }
}

int search_in_binary_tree(struct TreeNode* node, int key)
{
    if(node == NULL) return 0;
    if(key == node->key) return 1;
    else if(key < node->key) return search_in_binary_tree(node->left, key);
    else return search_in_binary_tree(node->right, key);
}

int tree_minimum(struct TreeNode* root)
{
    if(root->left != 0 ) return tree_minimum(root->left);
    return root->key;
}

int tree_maximum(struct TreeNode* root)
{
    if(root->right != 0 ) return tree_maximum(root->right);
    return root->key;
}

int main()
{
    struct TreeNode* root = insert_root_in_binary_tree(10);
    insert_in_binary_tree(root, 70, root->parent);
    insert_in_binary_tree(root, 30, root->parent);
    insert_in_binary_tree(root, 50, root->parent);
    insert_in_binary_tree(root, 40, root->parent);
    insert_in_binary_tree(root, 20, root->parent);
    insert_in_binary_tree(root, 60, root->parent);
    inorder_transversal(root);
    printf("\n");
    preorder_transversal(root);

}
