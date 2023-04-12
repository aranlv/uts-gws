#include<stdio.h>
#include<stdlib.h>

struct Node{
  int value;
  Node *front, *back;
} *first;

Node *createNode(int value)
{
  Node *newNode =(Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->front = newNode->back = NULL;
  return newNode;
}

void pushQueue(int value) //insert node in back
{
  Node *newNode = createNode(value);
  if (!first) //no nodes
  {
    first = newNode;
  }
  else //one or more nodes
  {
    Node *temp = first;
    while(temp->back){
      temp = temp->back;
    } //temp is now last or most back node
    temp->back = newNode;
    newNode->front = temp;
  }
}

void popQueue() //remove node in front
{
  if (!first) //if there is no nodes
  {
    return;
  } 
  else if(!first->back) //only one node
  {
    free(first);  //free the allocated memory
    first = NULL; //unassign label
  }
  else //one or more nodes
  {
    Node *newFirst = first->back;         //access new first
    first->back = newFirst->front = NULL; //isolate first
    free(first);                          //free the allocated memory of first
    first = newFirst;                     //move first label 
  }
}

int topQueue() //return value of first element
{
  return first->value;
}

int main()
{
  pushQueue(3);
  pushQueue(5);
  pushQueue(2);
  pushQueue(1);
  pushQueue(4);
  pushQueue(7);
  printf("Current first value is %d\n", topQueue()); //supposed to be 3
  popQueue();
  popQueue();
  printf("Current first value is %d\n", topQueue()); //supposed to be 2

  return 0;
}