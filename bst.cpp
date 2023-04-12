// Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value; // key to compare, remember that left < root and right > root
  Node *left, *right; // left and right child
};

Node *createNode(int value) {
  Node *newNode = (Node*)malloc(sizeof(Node)); // allocate memory and cast it to Node*
  newNode->value = value; // initialize the key
  newNode->left = newNode->right = NULL; // initialize both childs to point to NULL
  return newNode; // return the newly created Node
}

Node* insertNode(Node *root, int value) {
  if(!root) { // if current position is empty
    return createNode(value); // create the node at the specified position
  } else if(value < root->value) { // if value to be inserted is lower than root
    root->left = insertNode(root->left, value); // traverse to the left subtree
  } else if(value > root->value) { // if value to be inserted is higher than root
    root->right = insertNode(root->right, value); // traverse to the right subtree
  }

  return root; // return back the root the previous recursive call
}

// return true jika ketemu angkanya, false jika engga ketemu
bool searchNode(Node *root, int query) {
  if(root){
      if(root->value == query) {
      return true;
    } else if(query < root->value) {
      return searchNode(root->left, query);
    } else if(query > root->value) {
      return searchNode(root->right, query);
    }
  }
  
  return false;
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("%d\n", root->value);
    inOrder(root->right);
  }
}

Node *inOrderSuccessor(Node *root) {
  Node *curr = root->right; // enter the right subtree (value bigger than root)
  while(curr && curr->left) { // traverse the left subtree until NULL
    curr = curr->left; // go to the left
  }
  return curr; // return the sucessor (value bigger but closest to root)
}

Node *deleteNode(Node *root, int value) {
  if(!root) {    // can't find the value that needs to be deleted
    return root; // return unchanged tree
  } else if(value < root->value) { // if value to be deleted is smaller than root
    root->left = deleteNode(root->left, value); // enter left subtree
  } else if(value > root->value) { // if value to be deleted is higher than root
    root->right = deleteNode(root->right, value); // enter right subtree
  } else { // value == root->value, found the value that needs to be deletde
    if(!root->left || !root->right) { // 0/1 child
      // if left child is null, new root is right child
      // if right child is null, new root is left child
      Node *newRoot = root->left ? root->left : root->right;
      root->left = root->right = NULL; // isolate the node
      free(root); // free allocated memory
      root = NULL; // set the value to null
      return newRoot; // return the new root
    }

    // 2 children
    Node *newRoot = inOrderSuccessor(root); // find the in order successor
    root->value = newRoot->value; // copy the value from newRoot to existing root
    root->right = deleteNode(root->right, newRoot->value); // delete the newRoot
  }

  return root;
}

int main() {
  // Node *baseRoot = NULL;
  // baseRoot = insertNode(baseRoot, 40);
  // baseRoot = insertNode(baseRoot, 10);
  // baseRoot = insertNode(baseRoot, 30);
  // inOrder(baseRoot);
  // printf("%d", searchNode(baseRoot, 30));
  // puts("=========");
  // baseRoot = deleteNode(baseRoot, 10);
  // baseRoot = deleteNode(baseRoot, 40);
  // baseRoot = deleteNode(baseRoot, 30);
  // baseRoot = deleteNode(baseRoot, 15);
  // inOrder(baseRoot);

  	Node *root = NULL;
	root = insertNode(root, 10);
	root = insertNode(root, 5);
	root = insertNode(root, 3);
	root = insertNode(root, 15);
	root = insertNode(root, 11);
	root = insertNode(root, 16);
	root = insertNode(root, 7);
  inOrder(root);
  puts("=====");
  	deleteNode(root, 5);
	deleteNode(root, 10);
inOrder(root);
  return 0;
}