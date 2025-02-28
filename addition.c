 #include "apc.h"
 #include<stdio.h>
 #include<stdlib.h>
int insert_first(Dlist **head,Dlist**tail,int data);

int addition(Dlist** head1, Dlist** tail1, Dlist** head2, Dlist** tail2, Dlist** headR,Dlist **tailR) 
{
    int carry = 0;
    int sum;
    
    Dlist* temp1 = *tail1;
    Dlist* temp2 = *tail2;
   
    while (temp1 != NULL || temp2 != NULL || carry) 
    {
        sum = carry;
        int num1 = 0, num2 = 0;

        if (temp1 != NULL) 
        {
            num1 = temp1->data;
            sum += num1;
            temp1 = temp1->prev;
        }

        if (temp2 != NULL) 
        {
            num2 = temp2->data;
            sum += num2;
            temp2 = temp2->prev;
        }

        if (insert_first(headR,tailR, sum % 10) == FAILURE) 
            return FAILURE;
        carry = sum / 10;
    }
    return SUCCESS;
}
