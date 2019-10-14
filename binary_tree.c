#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct node* tree_iterator;

struct node
{
    int key;
    tree_iterator parent, left, right;
};

int totalNodesInTree(tree_iterator root)
{
    if(root == 0) return 0;
    return totalNodesInTree(root->left) + totalNodesInTree(root->right) + 1;
}

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
        if(key == it->key)
        {
            printf("Node with same value exists!\n\nTerminating Program...\n\n");
            exit(1);
        }
        else if(key < it->key){
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

tree_iterator minValueRoot(tree_iterator root)
{
    if(0 == root) return root;
    if(0 == root->left) return root;
    return minValueRoot(root->left);
}

tree_iterator delete(int key, tree_iterator root)
{
    if(0 == root) return root;
    if(key < root->key) //the key is in the left branch
    {
        if(0 == root->left)
        {
            printf("Node with %d value dont exists!\n\nTerminating Program...\n\n", key);
            exit(1);
        }
        root->left = delete(key, root->left);
        return root;
    }
    else if(key > root->key) //the key is in the right branch
    {
        if(0 == root->right)
        {
            printf("Node with %d value dont exists!\n\nTerminating Program...\n\n", key);
            exit(1);
        }
        root->right = delete(key, root->right);
        return root;
    }
    else //the root has key
    {
        if(0 == root->left && 0 == root->right) //has no child
        {
            free(root);
            return 0;
        }
        else if(0 == root->right) //has one child(left)
        {
            tree_iterator temp_node = root->left;
            temp_node->parent = root->parent;
            free(root);
            return temp_node;
        }
        else if(0 == root->left) //has one child(right)
        {
            tree_iterator temp_node = root->right;
            temp_node->parent = root->parent;
            free(root);
            return temp_node;
        }
        else //has two child
        {
            tree_iterator mvr = minValueRoot(root->right);
				    root->key = mvr->key;
				    root->right = delete(mvr->key, root->right);
        }
    }
    return root;
}

void inorder(tree_iterator root)
{
    if(root==0) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void postorder(tree_iterator root)
{
    if(root==0) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

void preorder(tree_iterator root)
{
    if(root==0) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void printTree(tree_iterator root, int space)
{
    if(0 == root) return;
    printTree(root->right, space+4); //for indent we add space by 4
    printf("\n");
    for(int s=0; s<space; s++)
    {
        printf(" ");
    }
    printf("%d", root->key);
    printTree(root->left, space+4);
}

int main()
{
    tree_iterator root = create(10);
    root = insert(20,root);
    root = insert(5,root);
    root = insert(1,root);
    root = insert(8,root);
    root = insert(6,root);
    root = delete(5,root);

    printf("Tree shape:\n");
    printTree(root, 0);
    printf("\nPreorder: ");
    preorder(root);
    printf("\nInorder: ");
    inorder(root);
    printf("\nPostorder: ");
    postorder(root);
    int nb_nodes = totalNodesInTree(root);
    printf("\nTotal nodes: %d\n", nb_nodes);
}

