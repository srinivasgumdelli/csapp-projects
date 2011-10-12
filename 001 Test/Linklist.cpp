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
  dbNode *address = new dbNode();

  address = insertFront(address, 1);
  address = insertFront(address, 2);

  cout << "Doubly-Linked List length is " << listLength(address) << endl;
  printAll(address);
  printOne(address -> tail -> tail);                // 1-2-3, prints value at 3
  printOne(address -> tail -> head);                // 1-2-3, prints value at 1
  printOne(address -> tail);                        // 1-2-3,prints value at 2
  freeOne(address -> tail);
  printOne(address -> tail);                        // What does 1 think is tailing it? 2 or 3?
  printOne(address -> tail -> head);        // What does 3 think is before it? 1 or 2?

  freeAll(address);
  printAll(address);

  int i;
  cin >> i;
}

void printOne(dbNode *point){
  cout << point -> data << endl;
}

void printList(dbNode *point){
  while(point){
    cout << (point->data) << ", ";
    point = point -> tail;
  }
  point?cout << "SegFault\n" : cout << "Null\n";
}

void printAll(dbNode *point){
  while(point->head){
    point = point -> head;
  }
  while(point){
      cout << (point-> data) << ", ";
      point = point -> tail;
  }
  point?cout << "SegFault\n" : cout << "Null\n";
}

dbNode* insertFront(dbNode *point, int num){
  dbNode* snode = new dbNode();
  snode -> data = num;
  snode -> tail = point;
  snode -> head = point -> head;

  point -> head = snode;
  return snode;
}

dbNode* insertBack(dbNode *point, int num){
  dbNode *snode = new dbNode();
  snode -> data = num;
  snode -> tail = point -> tail;
  snode -> head = point;

  point -> head = snode;
  return snode;
}

dbNode* freeAll(dbNode *pointer){
  while(pointer->head){
    pointer = pointer -> head;
  }

  dbNode *ptr  = pointer;
  while(pointer){
    pointer = pointer -> tail;
    delete ptr;
    ptr = pointer;
  }

  return pointer;
}

dbNode* freeOne(dbNode *pointer){
  (pointer -> head) -> tail = pointer -> tail;
  (pointer -> tail) -> head = pointer -> head;
  delete pointer;
  pointer = NULL;

  return pointer;
}

int listLength(dbNode *pointer){
  while(pointer->head){
    pointer = pointer -> head;
  }
  int i = 0;
  while (pointer){
    pointer = pointer->tail;
    i++;
  }

  return i;
}
