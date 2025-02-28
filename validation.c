#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
int insert_first(Dlist **head,Dlist **tail,int data);
int print_list(Dlist *head);
int compare_lists(Dlist *head1, Dlist *head2); 
void dl_delete_list(Dlist **head,Dlist **tail); 
int insert_last(Dlist** head, Dlist** tail, int data);
int get_count(Dlist *head);
int store_list(char* str, Dlist** head, Dlist** tail);
void delete_leading_zeroes(Dlist **head, Dlist **tail);
void handle_addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR); 
void handle_subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
void handle_division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int insert_first(Dlist **head,Dlist **tail,int data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    if (new_node == NULL)
    {
        return FAILURE;
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }
    else
        *tail = new_node;
    *head = new_node;
    return SUCCESS;
}

void delete_leading_zeroes(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
        return;


    while (*head != NULL && (*head)->data == 0)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(temp);
    }

    if (*head == NULL)
    {
        *tail = NULL;
    }
}


int compare_lists(Dlist *head1, Dlist *head2) 
{
    // Step 1: Compare list lengths
    int count1 = get_count(head1);
    int count2 = get_count(head2);

    if (count1 < count2)
        return -1;  // List 1 is smaller
    else if (count1 > count2)
        return 1;   // List 1 is larger

    // Step 2: Compare node data
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while (temp1 != NULL && temp2 != NULL) 
    {
        if (temp1->data < temp2->data)
            return -1;  // List 1 is lexicographically smaller
        else if (temp1->data > temp2->data)
            return 1;   // List 1 is lexicographically larger
        
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;  // Both lists are equal
}

void dl_delete_list(Dlist **head,Dlist **tail) 
{
    Dlist *temp = *head;
    while (temp != NULL)
     {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
     }
    *head = NULL;
}


int insert_last(Dlist** head, Dlist** tail, int data)
{
    Dlist* new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        return FAILURE;
    }

    new->data = data;
    new->prev = *tail;
    new->next = NULL;

    if (*tail != NULL)
    {
        (*tail)->next = new;
    }
    else
    {
        *head = new;
    }

    *tail = new;
    return SUCCESS;
}

int print_list(Dlist *head)
{
	if (head == NULL)
	{
		//printf("INFO : List is empty\n");
		return FAILURE;
	}	
	else
	{
	    while (head)		
	    {
           printf("%d",head->data);
		    head = head -> next;
	    }
    }
	return SUCCESS;
}

int store_list(char* str, Dlist** head, Dlist** tail) 
{
    int i=0;

    int is_negative = 0;
    if (*str == '-') 
    {
        is_negative = 1;
        str++; 
    }

    while (*str == '0')
        str++;
    
    if (*str == '\0')
    {
        Dlist* new = malloc(sizeof(Dlist));
        if (new == NULL)
            return FAILURE;
        
        new->data = 0;
        new->prev = NULL;
        new->next = NULL;
        *head = *tail = new;
        return SUCCESS;
    }

     while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            printf("Error: Invalid character '%c' in input. Only digits are allowed.\n", str[i]);
            return FAILURE;
        }
        i++;
    }

    while (*str != '\0') 
    {
        if (insert_last(head, tail, *str - '0') == FAILURE)
            return FAILURE;
        str++;
    }

    if (is_negative && *head != NULL)
        (*head)->data *= -1; 
    
    return SUCCESS;
}

int get_count(Dlist *head)
{
    int count = 0;
    Dlist *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}


void handle_addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{ 
    if ((*head1)->data < 0 && (*head2)->data < 0)
    {
        (*head1)->data *= -1;
        (*head2)->data *= -1;
        addition(head1, tail1, head2, tail2, headR, tailR);
        if (*headR != NULL)
            (*headR)->data *= -1; 
    }
    else if ((*head1)->data < 0 && (*head2)->data >= 0)
    {
        (*head1)->data *= -1;
        subtraction(head2, tail2, head1, tail1, headR, tailR);
    }
    else if ((*head1)->data >= 0 && (*head2)->data < 0)
    {
        (*head2)->data *= -1;
        subtraction(head1, tail1, head2, tail2, headR, tailR);
    }
    else
        addition(head1, tail1, head2, tail2, headR, tailR);
}


void handle_subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if ((*head1)->data < 0 && (*head2)->data < 0) 
    {
        (*head1)->data *= -1;  
        (*head2)->data *= -1;  
        subtraction(head1, tail1, head2, tail2, headR, tailR);  
        if (*headR != NULL)
            (*headR)->data *= -1;  
    }
    else if ((*head1)->data < 0 && (*head2)->data >= 0)  
    {
        (*head1)->data *= -1;  
        addition(head2, tail2, head1, tail1, headR, tailR); 
        if (*headR != NULL)
            (*headR)->data *= -1; 
    }
    else if ((*head1)->data >= 0 && (*head2)->data < 0) 
    {
        (*head2)->data *= -1;  
        addition(head1, tail1, head2, tail2, headR, tailR); 
    }
    else  
        subtraction(head1, tail1, head2, tail2, headR, tailR); 
}

void handle_division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if ((*head2)->data == 0)
    {
        printf("Error: Division by zero is not allowed.");
        return;
    }

    if ((*head1)->data < 0 && (*head2)->data < 0)  
    {
        (*head1)->data *= -1;
        (*head2)->data *= -1;  
        division(head1, tail1, head2, tail2, headR, tailR);  
    }
    else if ((*head1)->data < 0 && (*head2)->data >= 0)  
    {
        (*head1)->data *= -1;  
        division(head1, tail1, head2, tail2, headR, tailR);  
        if (*headR != NULL)
            (*headR)->data *= -1;  
    }
    else if ((*head1)->data >= 0 && (*head2)->data < 0)  
    {
        (*head2)->data *= -1;  
        division(head1, tail1, head2, tail2, headR, tailR);  
        if (*headR != NULL)
            (*headR)->data *= -1;  
    }
    else
        division(head1, tail1, head2, tail2, headR, tailR);  
    
}
