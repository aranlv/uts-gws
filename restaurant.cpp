#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct data
{
    char name[100];
    char status[100];
    char table[100];
    int priority;
    data *next;
    data *prev;
}*head=NULL, *tail=NULL;

data *cnode(char *name, char *status)
{
    data *node = (data*)malloc(sizeof(data));
    strcpy(node->name, name);
    strcpy(node->status, status);
    node->next = NULL;
    node->prev = NULL;

    if(strcmp(node->status, "VVIP") == 0)
    {
		node->priority = 4;
		strcpy(node->table, "VVIP table");
	}
	else if(strcmp(node->status, "VIP") == 0)
    {
		node->priority = 3;
		strcpy(node->table, "VIP table");
	}
	else if(strcmp(node->status, "Member") == 0)
    {
		node->priority = 2;
		strcpy(node->table, "regular table");
	}
	else if(strcmp(node->status, "Guest") == 0)
    {
		node->priority = 1;
		strcpy(node->table, "regular table");
	}
	
	return node;
}

void push(char *name, char *status)
{
    data *push = cnode(name, status);
    if(head==NULL)
    {
        head=tail=push;
        return;
    } else if(push->priority > head->priority){
        head->prev = push;
        push->next = head;
        head = push;
    } else if(push->priority <= tail->priority){
        tail->next = push;
        push->prev = tail; 
        tail = push;
    } else
    {
        data* curr = head; 
        while(curr->priority >= push->priority) curr = curr->next;

        curr->prev->next = push;
        push->prev = curr->prev;
        curr->prev = push;
        push->next = curr;

        return;
    }
}

void pop()
{
    if(head==NULL)
    {
        printf("No customers in queue.\n");
        return;
    }
    else if(head==tail)
    {
        if (strcmp(head->status, "VVIP") == 0)
        {
            printf("Attention! %s is being served at VVIP Table\n", head->name);
        }
        else if (strcmp(head->status, "VIP") == 0)
        {
            printf("Attention! %s is being served at VIP Table\n", head->name);
        }
        else
        {
            printf("Attention! %s is being served at Regular Table\n", head->name);
        }
        
        free(head);
        head=tail=NULL;
    } else
    {
        if (strcmp(head->status, "VVIP") == 0)
        {
            printf("Attention! %s is being served at VVIP Table\n", head->name);
        }
        else if (strcmp(head->status, "VIP") == 0)
        {
            printf("Attention! %s is being served at VIP Table\n", head->name);
        }
        else
        {
            printf("Attention! %s is being served at Regular Table\n", head->name);
        }
        data* temp=head;
        head=head->next;
        free(temp);
        head->prev=NULL;
    }
}

void popAll()
{
    if (head==NULL) 
    {
        printf("No customers in queue.\n");
        return;
    }
    
    // data *curr = head;
    while (head) 
    {
        pop();
        // curr = curr->next;
    }
}

void dismiss()
{
    data *temp = head;
    while (temp != NULL)
    {
        head = temp->next;
        free(temp);
        temp = head;
    }
    printf("\nEnd of the day\n");
}

void view()
{
    int q = 1;
    data *curr=head;
    if(curr==NULL)
    {
        printf("Queue is empty\n");
    }
    while(curr!=NULL)
    {
        printf("%d. %s\n", q++, curr->name);
        curr=curr->next;
    }
}



int menu()
{
    int choice;
    char name[100];
    char status[100];

    do{
        printf("============================\n");
        printf("SUNIB Restaurant Reservation\n");
        printf("============================\n");
        printf("\nWaiting Line:\n");
        view();
        printf("\n1. Add Customer to Queue\n");
        printf("2. Serve One\n");
        printf("3. Serve All\n");
        printf("4. Dismiss Queue\n");
        printf("0. Exit\n");
        printf("Input Menu Number: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Input Customer Name and Status: ");
                scanf("%s %s", name, status);
                push(name, status);
                break;
            case 2:
                pop();
                break;
            case 3:
                popAll();
                break;
            case 4:
                dismiss();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid Menu Number\n");
        }
    } while(choice!=0);
}

int main()
{
    srand(time(NULL));
    menu();
    return 0;
}