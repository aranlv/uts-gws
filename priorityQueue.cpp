#include<stdio.h>
#include<stdlib.h>

struct Node{
  int value;
  Node *front, *back;
} *first;

Node *createNode(int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->front = newNode->back = NULL;
  return newNode;
}

void pushQueue(int value) //insert a node
{
  Node *newNode = createNode(value);
  if (!first)//there are no existing nodes
  {
    first = newNode;
  }
  else if (value > first->value) //if newNode is bigger than first 
  {
    first->front = newNode; 
    newNode->back = first;
    first = newNode;
  }
  //did not create a seperate else if for value < last node because we don't track the tail
  else //one or more nodes
  {     
    Node *current = first;
    while(current->back && !(current->back->value < value))
    { //while exists a node behind current and that back node's value is not yet smaller than value
      //this is to ensure FIFO for elements with the same priority (same value)
      current = current->back;
    } //until current is either the last node or newNode's front 
    
    if(!current->back) //if current is last node
    {
      newNode->front = current;
      current->back = newNode;
    }
    else //if current is in the middle of LL
    {
      newNode->back = current->back;
      current->back->front = newNode;
      newNode->front = current;
      current->back = newNode;
    }
   
  }
}

void popQueue() //get the first value out (remove first)
{
  if (!first) //if no nodes exist
  {
    return;
  }
  else if (!first->back) //if only one node exist
  {
    free(first);
    first = NULL;
  }
  else
  {
    Node *newFirst = first->back;
    first->back = newFirst->front = NULL;
    free(first);
    first = newFirst;
  }
  
}

void printQueue()
{
  for (Node *temp = first; temp != NULL; temp = temp->back)
  {
    printf("%d\n", temp->value);
    puts("|");
    puts("v");
  }
  puts("NULL");
}

int main()
{
  pushQueue(30);
  pushQueue(70);
  pushQueue(20);
  pushQueue(40);
  pushQueue(50);
  pushQueue(60);
  pushQueue(55);
  pushQueue(35);
  pushQueue(15);
  pushQueue(25);
  popQueue();
  popQueue();
  popQueue();
  printQueue(); //supposedly sorted, without 70, 60, and 55 on the list
  return 0;
}