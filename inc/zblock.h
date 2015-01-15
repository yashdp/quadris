#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_

#include "block.h"
#include "pos.h"
#include <iostream>

/*
ZBlock class: subclass inherited from Block class
*/
class ZBlock: public Block{
  char d; //Current Direction
 public:
  ZBlock(int Level);
  void notifyDisplay(TextDisplay &t); //Notifies the Display
  void rotate(std::string w, TextDisplay &t); //Rotate
  void move(char w, TextDisplay &t); //Move
  void notifyBottom(TextDisplay &t); //Notify the next block display
  void setvisited() ; //Set the block as deleted
  void replace(int oldx, int oldy, int newx, int newy); //Replace the coordinates
};
 
  
#endif
