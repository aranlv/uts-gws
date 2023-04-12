#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
	int key;
	Node* left;
	Node* right;
};

Node* createNode(int key){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* insertNode(Node* root, int key){
	if(!root) return createNode(key);
	else if(key < root->key) root->left = insertNode(root->left, key);
	else if(key > root->key) root->right = insertNode(root->right, key);
	
	return root;
}

bool searchNode(Node* root, int key){
	if(root){
		if(root->key == key) return true;
		else if(root->key > key) return searchNode(root->left, key);
		else if(root->key < key) return searchNode(root->right, key);
	}
	
	return false;
}

Node* successor(Node* root){
	Node* temp = root->right;
	while(temp->left) temp = temp->left;
	return temp;
}

Node* deleteNode(Node* root, int key){
	if(!root) return root;
	else if(root->key < key) root->right = deleteNode(root->right, key);
	else if(root->key > key) root->left = deleteNode(root->left, key);
	else{
		if(!root->right || !root->left){
      Node* temp;
      //kalau root right exist, isi temp dengan root right 
      if(root->right != NULL) temp = root->right;
      //else (root left exist, atau root left and right doesnt exist)
      //isi temp dgn rootleft (or ketika both child doesnt exist, temp bkl null)
      else temp = root->left;

			root->left = root->right = NULL;
			free(root);
			root = NULL;
      //kalau temp tadi null (both child doesnt exist, bkl return null)
			return temp;
		}
		else{
			Node* temp = successor(root);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
	}
	
	return root;
}

int height(Node* root){
	if(!root) return 0;
	else{
		int right = height(root->right);
		int left = height(root->left);
		
		if(right >= left) return right + 1;
		else return left + 1;
	}
}

void deleteTree(Node* root){
	if(!root) return;
	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
	return;
} //kayak postorder

void checkTree(Node* root, int count){
	if(!root) return;
	checkTree(root->right, count+1);
	for(int i=0; i<count; i++) printf("\t");
	printf("%d\n", root->key);
	checkTree(root->left, count+1);
} //inorder kebalik, count is height

int main(){
	Node *root = NULL;
	root = insertNode(root, 10);
	root = insertNode(root, 5);
	root = insertNode(root, 3);
	root = insertNode(root, 15);
	root = insertNode(root, 11);
	root = insertNode(root, 16);
	root = insertNode(root, 7);

	puts("");

	printf("%d", searchNode(root, 10));
	
//	printf("\nPre-Order: "); preOrder(root);
//	printf("\nIn-Order: "); inOrder(root);
//	printf("\nPost-Order: "); postOrder(root); 
	
	puts("\n======================");
	
	checkTree(root, 0);
	
	deleteNode(root, 5);
	puts("======================");
	checkTree(root, 0);
	
	deleteNode(root, 10);
	puts("======================");
	checkTree(root, 0);
	
	printf("\nHeight of tree is %d\n", height(root));
	
	return 0;
}