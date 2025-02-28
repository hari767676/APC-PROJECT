#include "apc.h"
#include <stdio.h>
#include<stdlib.h>
int compare_lists(Dlist *head1, Dlist *head2);
int get_count(Dlist *head);
int print_list(Dlist* head);
int insert_last(Dlist** head, Dlist** tail, int data);
int insert_first(Dlist **head,Dlist**tail,int data);
void delete_leading_zeroes(Dlist **head, Dlist **tail);

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int count1 = get_count(*head1);
    int count2 = get_count(*head2);
    int check = compare_lists(*head1, *head2);

    if (count1 < count2) 
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }
    
    if (check < 0 && count1 == count2)
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }
    
    if (check == 0)
    {
        insert_first(headR, tailR, 1);
        return SUCCESS;
    }
    
    Dlist *temp = *head1;
    Dlist *res1_head = NULL;
    Dlist *res1_tail = NULL;
    Dlist *res2_head = NULL;
    Dlist *res2_tail = NULL;
    int count;
    
    while (temp != NULL)
    {
        insert_last(&res1_head, &res1_tail, temp->data);
        temp = temp->next;

        delete_leading_zeroes(&res1_head, &res1_tail);
        

        int check = compare_lists(res1_head, *head2);
        
        if (check < 0)
        {
            insert_last(headR, tailR, 0);
            continue;
        }

        count = 0;
        while (compare_lists(res1_head, *head2) >= 0)
        {
            subtraction(&res1_head, &res1_tail, head2, tail2, &res2_head, &res2_tail);
            res1_head = res2_head;
            res1_tail = res2_tail;
            res2_head = NULL;
            res2_tail = NULL;
            count++;
        }

        insert_last(headR, tailR, count);
        delete_leading_zeroes(headR, tailR);
        
    }
    return SUCCESS;
}




