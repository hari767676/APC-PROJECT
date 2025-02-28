#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int insert_first(Dlist **head,Dlist **tail, int data);
int addition(Dlist** head1, Dlist** tail1, Dlist** head2, Dlist** tail2, Dlist** headR,Dlist** tailR);
void dl_delete_list(Dlist **head,Dlist **tail); 


int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	int result, i, carry = 0, count = 0,is_negative = 0;
	Dlist *temp1=*tail1, *temp2=*tail2, *res1=NULL,*res2=NULL,*res3=NULL,*t1=NULL,*t2=NULL,*t3=NULL;

    if (((*head1)->data < 0 && (*head2)->data >= 0) || ((*head2)->data < 0 && (*head1)->data >= 0)) 
        is_negative = 1;
    
	if ((*head1)->data < 0)
        (*head1)->data *= -1;
    
    if ((*head2)->data < 0)
        (*head2)->data *= -1;
    
	while(temp1)
    {
		result=(temp1->data * temp2->data) + carry;
		carry = result/10;
		result %=10 ;
		insert_first(&res1,&t1,result);
		temp1=temp1->prev;
	}
	count++;
	if(carry != 0)
		insert_first(&res1,&t1,carry);
	
	temp2=temp2->prev;
	while(temp2)
    {
		for(i=0;i<count;i++)
			insert_first(&res2,&t2,0);
		temp1=*tail1;
		carry=0;
		while(temp1)
        {
			result=(temp1->data * temp2->data) + carry;
			carry = result/10;
			result %=10 ;
			insert_first(&res2,&t2,result);
			temp1=temp1->prev;
		} 
		
		if(carry != 0)
			insert_first(&res2,&t2,carry);
		addition(&res1, &t1,  &res2, &t2, &res3, &t3);
		dl_delete_list(&res1,&t1);
		dl_delete_list(&res2,&t2);
        
        res1 = res3;
        t1 = t3;
        res3 = NULL;
        t3 = NULL;
		count++;
		temp2=temp2->prev;
	}
	temp1=t1;
	while(temp1)
    {
		insert_first(headR,tailR,temp1->data);
		temp1=temp1->prev;
	}

	while (*headR != NULL && (*headR)->data == 0 && (*headR)->next != NULL) 
    {
        Dlist* temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    if (is_negative)
        (*headR)->data *= -1;

	dl_delete_list(&res1,&t1);
    return SUCCESS;
}



