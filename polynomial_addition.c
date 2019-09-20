#include <stdio.h>
#include <stdlib.h>

typedef struct node* iterator;

typedef struct node
{
    int coef;
    int expo;
    struct node* next;
}Node;

iterator create_singly_linked_list(int coef, int expo)
{
    iterator head = (iterator)malloc(sizeof(Node));
    head->coef = coef;
    head->expo = expo;
    head->next = 0;
    return head;
}

iterator insert_inorder(int coef, int expo, iterator head)
{
    iterator it = head;
    iterator prev = 0;
    if(head->expo < expo)
    {
        iterator new = (iterator)malloc(sizeof(Node));
        new->coef = coef;
        new->expo = expo;
        new->next = head;
        head = new;
        return head;
    }
    while(it->expo > expo)
    {
        if(it->next == 0)
        {
            if(it->coef == coef)
            {
                it->coef += coef;
                return head;
            }
            iterator new = (iterator)malloc(sizeof(Node));
            new->coef = coef;
            new->expo = expo;
            new->next = 0;
            it->next = new;
            return head;
        }
        prev = it;
        it = it->next;
    }
    if(it->expo == expo)
    {
        it->coef += coef;
        return head;
    }
    iterator new = (iterator)malloc(sizeof(Node));
    new->coef = coef;
    new->expo = expo;
    new->next = it;
    prev->next = new;
    return head;
}

iterator insert_at_end(int coef, int expo, iterator head)
{
    iterator it = head;
    while(it->next != 0) it = it->next;
    iterator new = (iterator)malloc(sizeof(Node));
    new->coef = coef;
    new->expo = expo;
    new->next = 0;
    it->next = new;
    return head;
}

iterator add_polynomials(iterator head1, iterator head2)
{
    iterator temp1 = head1;
    iterator temp2 = head2;
    iterator head3 = 0;
    while(temp1 != 0 && temp2 != 0)
    {
        if(temp1->expo < temp2->expo)
        {
            if(head3 == 0){
                head3 = create_singly_linked_list(temp2->coef, temp2->expo);
            }
            else{
                head3 = insert_at_end(temp2->coef, temp2->expo, head3);
            }
            temp2 = temp2->next;
        }
        else if(temp1->expo > temp2->expo)
        {
            if(head3 == 0){
                head3 = create_singly_linked_list(temp1->coef, temp1->expo);
            }
            else{
                head3 = insert_at_end(temp1->coef, temp1->expo, head3);
            }
            temp1 = temp1->next;
        }
        else
        {
            if(head3 == 0){
                head3 = create_singly_linked_list(temp1->coef + temp2->coef, temp1->expo);
            }
            else{
                head3 = insert_at_end(temp1->coef + temp2->coef, temp1->expo, head3);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    iterator it = head3;
    while(it->next != 0) it = it->next;
    if(temp1 == 0 && temp2 != 0) it->next = temp2;
    else if(temp2 == 0 && temp1 != 0) it->next = temp1;
    return head3;
}

void display_sll(iterator head)
{
    iterator it = head;
    while(it->next != 0)
    {
        printf("%d * x^%d + ", it->coef, it->expo);
        it = it->next;
    }
    printf("%d * x^%d", it->coef, it->expo);
    printf("\n");
}

int main()
{
    iterator head1 = 0;
    iterator head2 = 0;
    int terms1, terms2;
    printf("Enter the number of terms in first polynomial: ");
    scanf("%d", &terms1);
    printf("Enter the coeficient and exponent for all terms of first polynomial: ");
    for(int i=0;i<terms1;i++)
    {
        int coef, expo;
        scanf("%d%d", &coef, &expo);
        if(head1 == 0) head1 = create_singly_linked_list(coef, expo);
        else head1 = insert_inorder(coef, expo, head1);
    }
    display_sll(head1);
    printf("Enter the number of terms in second polynomial: ");
    scanf("%d", &terms2);
    printf("Enter the coeficient and exponent for all terms of second polynomial: ");
    for(int i=0;i<terms2;i++)
    {
        int coef, expo;
        scanf("%d%d", &coef, &expo);
        if(head2 == 0) head2 = create_singly_linked_list(coef, expo);
        else head2 = insert_inorder(coef, expo, head2);
    }
    display_sll(head2);
    iterator head3 = add_polynomials(head1, head2);
    display_sll(head3);
}