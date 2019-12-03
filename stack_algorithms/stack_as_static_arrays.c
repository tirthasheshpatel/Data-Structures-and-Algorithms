#include <stdio.h> // Handles standard input/output
#include <errno.h> // Error Handling library
#include <stdlib.h>

// The maximum number of elements that can be stored in a stack.
#define MAX 65535

// Structure of stack
struct stack
{
	// A integer pointing at the top of the stack.
	int top;
	// A array to hold the values of stack.
	int arr[MAX+1];
}s;

// Deletes and returns the top element in a stack.
int POP(struct stack* s)
{
	// IMPLEMENT POP

	// Handle error when stack is empty.
	if(s->top == -1) perror("Stack Underflow!");

	// Get a copy of value at the top of the stack
	// in a variable `element` that we are going to return.
	int element = s->arr[s->top];

	// Initialize the value at the top of the stack again to 0.
	s->arr[s->top] = 0;
	// Decrease the value of `top` by 1.
	s->top--;

	// Finally, return `element`.
	return element;
}

// Adds a element onto the top of stack
void PUSH(struct stack* s, int value)
{
	// IMPLEMENT PUSH

	// Handle error in case the stack has reached its maximum limit `MAX`.
	if(s->top == MAX) perror("Stack Overflow!");

	// Increase the value of `top` by 1.
	s->top++;
	// Insert element at the index `top`.
	s->arr[s->top] = value;
}

// Returns the i'th element from the top of the stack
int PEEP(struct stack* s, int index)
{
	// IMPLEMENT PEEP

	// Handle error if index is not valid
	if(index <= 0 || index > MAX) perror("index out of range!");
	return s->arr[s->top - index]; // return the i'th element from the top.
}

void CHANGE(struct stack* s, int index, int new_value)
{
	// IMPLEMENT CHANGE

	// Handle error in case of out of range access.
	if(index <= 0 || index > MAX) perror("index out of range!");

	// Insert the new value at index `top-index`.
	s->arr[s->top - index] = new_value;

}

void PRINT_STACK(struct stack* s)
{
    if(s->top == -1) perror("Nothing present in stack!");
	for(int i=0;i<=s->top;i++){
		printf("%d ", PEEP(s, s->top-i));
	}
	printf("\n");
}


int main()
{
	struct stack s = {-1, 0};
	char command;
	while(1)
	{
		printf("Enter command: ");
		scanf("%c", &command);
		fflush(stdout);
		fflush(stdin);
		if(command == 'i'){
			printf("Enter the value to insert: ");
			int value;
			scanf("%d", &value);
			PUSH(&s, value);
		}
		else if(command == 'd'){
			int deleted_element = POP(&s);
			printf("The element popped is: %d", deleted_element);
		}
		else if(command == 'p'){
			printf("Enter the index at which you wnat to peep: ");
			int index;
			scanf("%d", &index);
			int peeped_element = PEEP(&s, index);
			printf("Peeped Element: ", peeped_element);
		}
		else if(command == 'c'){
			printf("Enter the index you wnat to edit: ");
			int index;
			scanf("%d", &index);
			printf("Enter the new value: ");
			int new_value;
			scanf("%d", &new_value);
			CHANGE(&s, index, new_value);
		}
		else if(command == 's') PRINT_STACK(&s);
		else if(command == 'q') break;
		else perror("Command not found!");
	    
	}
}

