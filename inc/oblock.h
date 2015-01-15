#ifndef _OBLOCK_H_
#define _OBLOCK_H_

#include "block.h"
#include "pos.h"

/*
OBlock class: subclass inherited from Block class
*/
class OBlock : public Block{
 public:
  OBlock(int Level);
  void notifyDisplay(TextDisplay &t); //Notifies the Display
  void rotate(std::string w, TextDisplay &t); //Rotate
  void move(char w, TextDisplay &t); //Move
  void notifyBottom(TextDisplay &t); //Notify the next block
  void setvisited() ; //Set the block as deleted
  void replace(int oldx, int oldy, int newx, int newy); //Replace the coordinates
};

#endif
