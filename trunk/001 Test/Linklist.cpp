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
  printOne(address -> tail -> tail);                // 2-1-0, prints value at 0
  printOne(address -> tail -> head);                // 2-1-0, prints value at 2
  printOne(address -> tail);                        // 2-1-0,prints value at 1
  freeOne(address -> tail);
  printOne(address -> tail);                        // What does 2 think is tailing it? 1 or 0?
  printOne(address -> tail -> head);                // What does 0 think is before it? 2 or 1?

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
  while(pointer){
    dbNode *ptr = new dbNode();
    ptr = pointer;
    pointer = pointer -> tail;
    delete ptr;
    ptr = NULL;
  }

  return pointer;
}

dbNode* freeOne(dbNode *pointer){
  (pointer -> head) -> tail = pointer -> tail;
  (pointer -> tail) -> head = pointer -> head;
  delete pointer;

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
