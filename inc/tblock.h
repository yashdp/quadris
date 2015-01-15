#ifndef _TBLOCK_H_
#define _TBLOCK_H_
#include "block.h"
#include "pos.h"
#include <iostream>


/*
TBlock class: subclass inherited from Block class
*/
class TBlock: public Block{
  char d; //Current Direction
  Pos *temp[4]; //Stores initial configuration of the TBlock
 public:
  TBlock(int Level);
  void notifyDisplay(TextDisplay &t); //Notifies the Display
  void rotate(std::string w, TextDisplay &t); //Rotate
  void move(char w, TextDisplay &t); //Move
  void notifyBottom(TextDisplay &t); //Notify the next block display
  ~TBlock();
  void setvisited(); //Set the block as deleted
  void replace(int oldx, int oldy, int newx, int newy); //Replace the coordinates
};
 
  
#endif
