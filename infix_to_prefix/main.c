#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 65535

struct stack{
    int top;
    char s_content[MAX+1];

}ss;

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
    if(isalpha(a))  return 3;
    if(a=='+' || a=='-') return 1;
    if(a=='*' || a=='/') return 2;
    if(a=='#') return 0;
    return -1000;
}

int r(char a)
{
    if(isalpha(a))  return 1;
    if(a=='+' || a=='-' || a=='*' || a=='/') return -1;
    if(a=='#') return 0;
    return -1000;

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
        while(f(s.s_content[s.top]) >= f(infix[i]))
        {
            char temp= POP(&s);
            postfix[j++]=temp;
            rank+= r(temp);
            if(rank<1) perror("Invalid expression !!!");

        }

    PUSH(&s,infix[i++]);

    }

    while(s.s_content[s.top] != '#')
    {

        char temp= POP(&s);
        postfix[j++]=temp;
        rank += r(temp);
        if(rank<1) perror("Invalid exp !!");
    }

    postfix[j]='\0';


     char postfix_final[100];
     strcpy(postfix_final,"");
    int j2=0;
    for(int i=strlen(postfix)-1;i>=0;i--)
    {
        postfix_final[j2]=postfix[i];
        j2++;
    }
    postfix_final[j2]='\0';

    printf("Postfix expression is : ");
    puts(postfix_final);

}

int main()
{
    printf("Enter the Infix : ");
    char infix_0[100];
    gets(infix_0);

    char infix[100];
    int j=0;
    for(int i=strlen(infix_0)-1;i>=0;i--)
    {
        infix[j]=infix_0[i];
        j++;
    }
    infix[j]='#';
    infix[j+1]='/0';

    infix_to_postfix(infix);
}
