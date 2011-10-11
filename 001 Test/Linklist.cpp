#include <iostream>

using namespace std;

typedef struct Foo { int data; node *tail; node *head; } node;

void printList(node *ptr);

node* insertFront(node *ptr, int num);
node* insertBack(node *ptr, int num);

node* freeAll(node *pointer);
node* freeOne(node *pointer);



int main(){
}

void printList(node *ptr){
  
}
