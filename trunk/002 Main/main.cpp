#include "ballistic.h"
#include "collisionSink.h"
#include <cstdlib>
#include <iostream>

int main(){
  init();
  while(exit){
    updatePosition();
    check();
    updateGUI();
  }
}

void init(){
}

void updatePosition(){
  if(playerpressedsoandsokey)
    actionsrelatingtokey();
}

void check(){
  collisionSinkFunction();
}

void updateGUI(){
  for(int i = 0; i < objectTable.size(); i++){
    draw(i.getXLoc, i.getYLoc);
  }
}
