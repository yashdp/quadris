#ifndef __GAME_H__
#define __GAME_H__

#include "block.h"
#include "textdisplay.h"
#include <string>
#include "sblock.h"
#include "zblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "tblock.h"
#include "iblock.h"
#include "level.h"
#include "window.h"//
#include <vector>

class Game{
  Block *curblock; 
  Block *nextblock;
  char **gameBoard; //GameBoard to check the collisions
  Level *l; 
  TextDisplay *t;
  int height;
  int width; 
  Xwindow *w;
  int level;
  int score;
  int highscore;
  std::string sequence;
  bool key; //If game is played using the keyboad..BONUS
  bool del; 
  std::vector <Block *> v;
  bool firsttime; //If the block is being moved the first time
 public:
  void levelup();			
  void leveldown();			
  void emptyBoard(); //Resets the Game
  void clear(); //Clear a row if it can be cleared
  bool didIlose(); //Checks if the game is lost
  void move(char direction);
  void drop(); 
  bool moveable(char direction); //Checks if the block is moveable
  bool rotatable(std::string command); //Check if the block is rotatable
  void rotate(std::string command); 
  void update(); //update
  void remove(int r); //remove the row r and shifts above blocks one column down
  void makeBlock(); //Make new current block and next block
  bool isitT(); 
  void updateLevel(int l); 
  void updateScore(int s);
  void updateHighscore(int hs);
  void turnOffRow(int x); //turn off every blocks coordinates which contains a row x
  int blockRemoved(); //Returns the score of blocks removed while clearing a row
  Game(bool text,bool seed,std::string file,int seeder,int level, bool keyboard);
  ~Game();
  friend std::ostream &operator << (std::ostream &out, const Game &g);

};

#endif
