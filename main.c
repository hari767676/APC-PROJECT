/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for all the functions
***************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int store_list(char *str, Dlist **head, Dlist **tail);
int print_list(Dlist *head);
int insert_last(Dlist **head, Dlist **tail, int data);

void handle_addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
void handle_subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
void handle_division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;
    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;
    Dlist *headR = NULL;
    Dlist *tailR = NULL;
    char operator;

    if (argc != 4)
    {
        printf("Error: Insufficient arguments. Usage: ./a.out <number1> <operator> <number2>\n");
        return FAILURE;
    }

    if (store_list(argv[1], &head1, &tail1) == FAILURE)
    {
        printf("Error: Failed to store List 1.\n");
        return FAILURE;
    }
    printf("List 1  : ");
    print_list(head1);
    printf("\n");

    if (store_list(argv[3], &head2, &tail2) == FAILURE)
    {
        printf("Error: Failed to store List 2.\n");
        return FAILURE;
    }
    printf("List 2  : ");
    print_list(head2);
    printf("\n");

    operator = argv[2][0];
    printf("Operator: %c\n", operator);
    switch (operator)
    {
        case '+':
            handle_addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            break;

        case '-':
            handle_subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);  
            break;

        case 'x':
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            break;

        case '/':
            handle_division(&head1, &tail1, &head2, &tail2, &headR, &tailR);  
            break;

        default:
            printf("Invalid Input: Invalid operator. Try again...\n");
            return FAILURE;
    }
    if(headR!= NULL)
        printf("Result  : ");
    print_list(headR);
    printf("\n");

    return SUCCESS;
}