#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "block.h"


class Level{
  
  int ignore; //Number of Chars in custom scriptfile
  int level; 
  char random7(); //level 2 difficulty
  char random9(); //level 3 difficulty
  char random12();//level 1 difficulty
  char zero();	  //level 0 difficulty
  std::string file; //Scriptfile
  int count; //Position of number of Chars extracted from the file
 public:
  Block* getBlock(); //Return a Block
  Level(std::string file, bool seed, int seeder); 
  void setlevel(int n); //Sets the level
};

#endif
