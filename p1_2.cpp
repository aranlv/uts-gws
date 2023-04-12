#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 9

struct hashNode{
	char name[20];
	int key;
} *table[SIZE];

hashNode* make(char name[], int key){
	hashNode* newNode = (hashNode*)malloc(sizeof(hashNode));
	strcpy(newNode->name, name);
	newNode->key = key;
}

int hashFunction(char name[]){
	int key = 0;
	for(int i=0; i<strlen(name); i++){
		key += name[i];
	}
	printf("hash %s | sum: %d, key: %d\n", name, key, key%SIZE);
	return key % SIZE;
}	

void insert(char name[]){
	int idx = hashFunction(name);
	hashNode* newNode = make(name, idx);
	
	if(!table[idx]) table[idx] = newNode; 			// check availability di idx yang sebenarnya
	else{ 											// kalau full, cari next available space
		for(int i = (idx+1)%SIZE; i!=idx; i++){		// start from idx+1 modulo SIZE, until i comes back to idx
			if(!table[i]){
				table[i] = newNode; 
				return;
			}
		}
	}
}

void print(){
	for(int i=0; i<SIZE; i++){
		printf("%d -> %s\n", i, table[i]);
	}
}

int main(){
	insert("yve");
	insert("pharsa");
	insert("estes");
	insert("miya");
	insert("aulus");
	insert("lylia");
	insert("gusion");

	print();
	
	return 0;
}
