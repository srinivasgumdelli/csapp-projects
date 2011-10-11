#include <iostream>

// Create LinkList structure with head and tail

using namespace std;

typedef struct foo { int data; foo *tail; foo *head; } dbNode;

void printOne(dbNode *ptr);
void printList(dbNode *ptr);
void printAll(dbNode *ptr);

dbNode* insertFront(dbNode *ptr, int num);
dbNode* insertBack(dbNode *ptr, int num);

dbNode* freeAll(dbNode *pointer);
dbNode* freeOne(dbNode *pointer);

int listLength(dbNode *pointer);



int main(){
  dbNode *address = (dbNode*)malloc(sizeof(dbNode));
  address = NULL;
 
  address -> head = insertFront(address, 10);
  address = address -> head;
}

void printOne(dbNode *point){
  cout << point -> data << endl;
}

void printList(dbNode *point){
  while(point){
    cout << point -> data << ", ";
    point = point -> tail;
  }
  point?cout << "SegFault\n" : cout << "Null\n";
}

void printAll(dbNode *point){
  while(point->head){
    point = point -> head;
  }
  printList(point);
}

dbNode* insertFront(dbNode *point, int num){
  dbNode* snode = (dbNode*)malloc(sizeof(dbNode));
  snode -> data = num;
  snode -> tail = point;
  snode -> head = point -> head;
  return snode;
}

dbNode* insertBack(dbNode *point, int num){
  dbNode *snode = (dbNode*)malloc(sizeof(dbNode));
  snode -> data = num;
  snode -> tail = point -> tail;
  snode -> head = point;
  return snode;
}

dbNode* freeAll(dbNode *pointer){
  while(pointer->head){
    pointer = pointer -> head;
  }
 
  dbNode *ptr  = pointer;
  while(pointer){
    pointer = pointer -> tail;
    free(ptr);
    ptr = pointer;
  }
 
  return pointer;
}

dbNode* freeOne(dbNode *pointer){
  (pointer -> head) -> tail = pointer -> tail;
  (pointer -> tail) -> head = pointer -> head;
  free(pointer);
  pointer = NULL;
 
  return pointer;
}

int listLength(dbNode *pointer){
  while(pointer->head){
    pointer = pointer -> head;
  }
  int i = 0;
  while (pointer){
    i++;
  }
 
  return i;
}
