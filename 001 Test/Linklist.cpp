#include <iostream>

// Create LinkList structure with head and tail

using namespace std;

typedef struct Foo { int data; node *tail; node *head; } node;

void printOne(node *ptr);
void printList(node *ptr);
void printAll(node *ptr);

node* insertFront(node *ptr, int num);
node* insertBack(node *ptr, int num);

node* freeAll(node *pointer);
node* freeOne(node *pointer);

int listLength(node *pointer);



int main(){
  node *address = (node*)malloc(sizeof(node));
  address = NULL;
  
  address -> head = insertFront(address, 10);
  address = address -> head;
}

void printOne(node *point){
  cout << point -> data << endl;
}

void printList(node *point){
  while(point){
    cout << point -> data << ", ";
    point = point -> tail;
  }
  point?cout << "SegFault\n" : cout << "Null\n";
}

void printAll(node *point){
  while(point->head){
    point = point -> head;
  }
  printList(point);
}

node* insertFront(node *point, int num){
  node *new = (node*)malloc(sizeof(node));
  new -> data = num;
  new -> tail = point;
  new -> head = point -> head;
  return new;
}

node* insert back(node *point, int num){
  node *new = (node*)malloc(sizeof(node));
  new -> data = num;
  new -> tail = point -> tail;
  new -> head = point;
  return new;
}

node* freeAll(node *pointer){
  while(point->head){
    point = point -> head;
  }
  
  node *ptr  = point;
  while(point){
    point = point -> tail;
    free(ptr);
    ptr = point;
  }
  
  return point;
}

node* freeOne(node *pointer){
  (point -> head) -> tail = point -> tail;
  (point -> tail) -> head = point -> head;
  free(point);
  point = NULL;
  
  return point;
}

int listLength(node *pointer){
  while(point->head){
    point = point -> head;
  }
  int i = 0;
  while (point){
    i++;
  }
  
  return i;
}
