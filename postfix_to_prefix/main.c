/*
->Author  : Tirth Hihoriya
->Editor  : Tirth Hihoriya
->E-mail  : tirth.hihoriya@gmail.com
->Summary : Converting `postfix` to  `prefix` using STACK
*/

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h> // malloc, calloc
#include <ctype.h> // isalpha
#include <string.h> // strlen, strcpy, strcat
#include <errno.h> // perror

// Making a Structure of Stack that can store
// a string
struct stack
{
    int top; // integer indicating the size of the string array
    // An array of maximum 100 string type element.
    char st[100][100];
};

// PUSH is a operation
// to add an element onto the stack.
void PUSH(struct stack *s,char n3[])
{
    /*
     * Arguments: `s`  (stack) -> A stack object in which you want to push.
     *            `n3` (c_str) -> A string object to be pushed to the stack `s`.
     * Inserts the string `n3` on the top of the stack.
     * Returns: -
     */

     // If stack is full print error "Overflow!"
    if(s->top==100) perror("Overflow");

    // Else, increment the top attribute of the stack
    // and insert element at the new index of the `st` attribute
    // of stack.
    else
    {
        s->top++; // increment top
        strcpy(s->st[s->top],n3); // Copy the passed string onto the stack.
    }

}


// POP element from the top of the stack
void POP(struct stack *s, char element[])
{
    /*
     * Arguments: `s` (stack)       -> A stack object from which the element
     *                                 is being poped.
     *            `element` (c_str) -> A string object in which the poped element
     *                                 is stored.
     * Deletes top element from the `st` attribute of the stack object
     * and stores the deleted object in string `element`.
     * Returns: -
     */

     // If the stack is empty, print error "Underflow"
    if(s->top==-1) perror("Underflow\n");

    // Else, copy the top string and decrement `top` attribute by 1.
    else{
        strcpy(element,s->st[s->top]); // copy top of stack in `element`
        s->top--; // decrement top
        return;
    }
}


// Converts a postfix strint to infix.
void postfix_to_infix(char p[])
{
    // Make a stack object and initialize the `top` as -1.
    struct stack s = {-1};
    int i=0;  // used to iterate through the infix string.
    do
    {
        if(isalpha(p[i])) //isalpha(p[i]) will return true if
						  //p[i] is alphabet i.e. for us `variable name`
        {
            char temp[100];  //it is temporary string to copy the `variable name`
            temp[0]=p[i];
            temp[1]='\0';   //because string should end with `\0`
            PUSH(&s,temp);  //it will push the `temp` to the stack of string
        }

		// Now if while scanning the postfix if any operator aqppears then
		// POP the last  `variable_name` then append the operator then
		// again POP  the `variable_name` and also append it.
        else if(p[i]=='+' || p[i]=='-' || p[i]=='*' || p[i]=='/' || p[i]=='%')  //these are some binary operator
        {
            char n3[100];            //`n3` is for the final string after appending the expresstion.
            strcpy(n3,"");          //initializing `n3` with `(` so that precedece is maintainted.
            char n2[100];            //`n2` is for the second `variable_name`
            POP(&s, n2);
            char n1[100];            //`n1` is for the first `variable_name`
            POP(&s, n1);
            size_t sz = strlen(n3);
            n3[sz]=p[i];             // appending the operator in `n3`
            n3[sz+1]='\0';
            strcat(n3,n1);           // concatenating `n1` in `n3`.
            size_t sze = strlen(n3);
            n3[sze+1]='\0';           // storing length of `n3` in `sze` variable.
                                    // every string ends with `\0`.
            strcat(n3,n2);			//appending `n2` in `n3`.

            PUSH(&s,n3);           // push this expression`n3` as `variable_name` in stack.
        }
        i++;
    }while(p[i]!='\0');           // loop terminates when `\0` is scanned from `postfix`.

    char infix[100];
    POP(&s, infix);
    puts(infix);
}

int main()
{
    char p[100];                       //`p` to store postfix expression.
    printf("Enter the postfix : ");
    scanf("%s", p);                    // scan postfix expresstion from user.
	postfix_to_infix(p);
}
