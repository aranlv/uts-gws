#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    Node *up, *bottom;
} *top;

Node *createNode(int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value; 
  newNode->up = newNode->bottom = NULL;   
  return newNode;         
}

void pushStack(int value) //push new top
{
    Node *newNode = createNode(value); 
    if (!top) //if LL is empty                      
    {
        top = newNode; 
    }
    else //if more than one node exists
    {
        top->up = newNode;      //points top to new node
        newNode->bottom = top;  //points new node to top
        top = newNode;          //move top label to new node      
    }
}

void popStack() //pop top element
{
    if (!top) // if LL is empty
    {
        return;
    }
    else if(!top->bottom) //if only one node
    {
        free(top); 
        top = NULL;
    }
    else 
    {
        Node *newTop = top->bottom;      //second top is labeled newTop
        top->bottom = newTop->up = NULL; //isolate current top
        free(top);                       //free allocated memory
        top = newTop;                    //move top label to newTop
    }
}

int topStack() //return value of top element
{
    return top->value;
}

int main()
{
    pushStack(3);
    pushStack(5);
    pushStack(2);
    pushStack(1);
    pushStack(4);
    pushStack(7);
    printf("Current top value is %d\n", topStack()); //supposed to be 7
    popStack();
    popStack();
    printf("Current top value is %d\n", topStack()); //supposed to be 1

    return 0;
}