#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include "window.h"

/*
TextDisplay class responsible for displaying both text 
output and graphical output
 */
class TextDisplay {
  char **gameDisplay; //Main Display 10 by 18
  char **bottomDisplay; //Bottom Display for Next block
  const int gridH; 
  const int gridW; 
  Xwindow *w; 
  int level; 
  int  score;
  int highscore;
 public:
  TextDisplay(int w, int h , Xwindow *g);
  void notifymiddle(int r, int c, char ch); //Notifies the middle display
  void removeRow(int r); //Removes the Row and shifts every row above r 1 column down
  void draw(int r,int c, char ch); //Draws on the graphics Xwindow graphics display
  void notifybottom(int r, int c, char ch); //Notifies the Next Block Board
  void setScore(int s); //Updates the score
  void setHighscore(int hs); //Updates the HighScore
  void setLevel(int l); //Updates the level
  void clear(); //Clears the whole gameboard
  ~TextDisplay();
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
