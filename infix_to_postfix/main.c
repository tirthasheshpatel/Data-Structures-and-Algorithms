#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 65535

struct stack{
    int top;
    char s_content[MAX+1];

};

void PUSH(struct stack *s, char value)
{
    if(s->top==MAX)  perror("Overflow");
    s->top++;
    s->s_content[s->top]=value;

}

char POP(struct stack *s){

    if(s->top==-1)   perror("Underflow !!!");
    char element = s->s_content[s->top];
    s->s_content[s->top]=0;
    s->top--;
    return element;
}

int f(char a)
{
    if(a=='(') return 9;
    if(isalpha(a))  return 7;
    if(a=='^')  return 6;
    if(a=='*' || a=='/') return 3;
    if(a=='+' || a=='-') return 1;
    if(a==')' || a=='#') return 0;
    return -1000;
}

int g(char a)
{
    if(isalpha(a))  return 8;
    if(a=='^')  return 5;
    if(a=='*' || a=='/') return 4;
    if(a=='+' || a=='-') return 2;
    if(a==')' || a=='#') return -1;
    return 0;
}

int r(char a)
{
    if(isalpha(a))  return 1;
    if(a=='+' || a=='-' || a=='*' || a=='/' || a=='^') return -1;
    if(a=='#') return 0;
    return -1;

}

void infix_to_postfix(char infix[])
{
    char postfix[500];
    int rank=0;

    struct stack s = {-1,0};
    int i=0,j=0;

    PUSH(&s,'#');

    while(infix[i]!='#')
    {
        while(g(s.s_content[s.top]) >= f(infix[i]))
        {
            char temp= POP(&s);
            if(temp!='(' && temp!=')')
                {
                    postfix[j++]=temp;
                    rank+= r(temp);
                }


        }

    PUSH(&s,infix[i++]);

    }

    while(s.s_content[s.top] != '#')
    {

        char temp= POP(&s);
        if(temp != '(' && temp != ')')
        {
             postfix[j++]=temp;
             rank += r(temp);
        }

    }

    postfix[j]='\0';
    printf("Postfix expression is : ");
    puts(postfix);

}

int main()
{
    printf("Enter the expression :");
    char infix[100];
    gets(infix);
    strcat(infix, "#");
    infix_to_postfix(infix);
}
