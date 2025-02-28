#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int insert_first(Dlist **head,Dlist **tailR, int data);
int compare_lists(Dlist *head1, Dlist *head2); 

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR) 
{
    int borrow = 0;
    int diff;
    int sign = 0;

    int comparison = compare_lists(*head1, *head2);
    if (comparison == FAILURE) 
    {
        Dlist *temp_head = *head1;
        Dlist *temp_tail = *tail1;
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = temp_head;
        *tail2 = temp_tail;
         sign = 1; 
    }

    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    while (temp1 != NULL || temp2 != NULL || borrow) 
    {
        diff = 0; 
        int num1 = 0, num2 = 0;

        if (temp1 != NULL) 
        {
            num1 = temp1->data;
            diff = num1;
            temp1 = temp1->prev;
        }

        if (temp2 != NULL) 
        {
            num2 = temp2->data;
            diff =diff - num2;
            temp2 = temp2->prev;
        }
        diff = diff - borrow;

        if (diff < 0) 
        {
            diff =diff + 10;
            borrow = 1;
        } 
        else 
            borrow = 0;
        if (insert_first(headR,tailR, diff) == FAILURE)
            return FAILURE;
    }

    while ( (*headR != NULL) && (*headR)->data == 0 ) 
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        if (*headR != NULL) 
            (*headR)->prev = NULL;
        free(temp);
    }

    if (*headR == NULL)
        insert_first(headR,tailR, 0);
    
    if (sign && *headR != NULL) 
        (*headR)->data =  (*headR)->data * -1; 

    return SUCCESS;
}

