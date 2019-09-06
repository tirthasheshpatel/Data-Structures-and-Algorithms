#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node
{
    int value;
    Node* right;
    Node* left;
};

int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
int parent(int i) { return ceil((float)i / 2) - 1; }


void min_heapify(int arr[], int i, int n)
{
	int l = left(i);
	int r = right(i);
	int lowest;
	if (l < n && arr[l] < arr[i])
		lowest = l;
	else lowest = i;
	if (r < n && arr[r] < arr[lowest])
		lowest = r;
	if (lowest != i) {
		swap(&arr[i], &arr[lowest]);
		min_heapify(arr, lowest, n);
	}
}

int heap_extract_min(int arr[], int *n)
{
	if ((*n) < 1) return -10000;
	int min = arr[0];
	swap(&arr[0], &arr[(*n) - 1]);
	(*n)--;
	min_heapify(arr, 0, (*n));
	return min;
}

void huffman(Node* tree[], int nb_characters)
{
    
}