#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "pos.h"
#include "textdisplay.h"
#include <iostream>

/*
Abstract Superclass used to create different Block types.
*/

class Block{
 protected:
  Pos *cords[4]; //Stores the current Coordinates of the Block
  Pos *prev[4];  //Stores the counterclockwise rotation Coordinates of the Block
  Pos *next[4];  //Stores the clockwise rotation Coordinates of the Block
  int level;     //Stores the level when the Block was created
  bool visited;  //Wheater the whole block is deleted off the board or not
 public:
  virtual void notifyDisplay(TextDisplay &t)=0; //Notifies the display
  virtual void notifyBottom(TextDisplay &t);   //Notifies the Next Block Display
  virtual void rotate(std::string w, TextDisplay &t)=0; //Rotates the Block cw and ccw
  virtual void move(char w, TextDisplay &t)=0; //Moves the block in all 4 directions
  virtual ~Block();   
  virtual void setvisited()=0;  //Deletes the Block of the actual Board
  virtual void replace(int oldx, int oldy, int newx, int newy)=0; //Replaces coordinates
  int getX(char arr, int i); //Returns X position of a coordinate
  int getY(char arr, int i); //Returns Y position of a coordinate
  int getL(); //Return the level
  bool isOff(); //Returns if the block is deleted
  void turnOff(int x); //Turns off a all block contained in row x
  bool isVisited(); //Return Visited
};


#endif
