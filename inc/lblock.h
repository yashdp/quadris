#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include "block.h"
#include "pos.h"
#include <iostream>


/*
LBlock class: subclass inherited from Block class
*/
class LBlock: public Block{
  char d; //Current Direction
 public:
  LBlock(int Level); 
  void notifyDisplay(TextDisplay &t); //Notifies the Display
  void rotate(std::string w, TextDisplay &t);//Rotate
  void move(char w, TextDisplay &t);//Move
  void notifyBottom(TextDisplay &t); //Notify the next block
  void setvisited() ; //Set the block as deleted
  void replace(int oldx, int oldy, int newx, int newy); //Replace the coordinates
};
 
  
#endif
