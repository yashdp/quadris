#ifndef _MULTIPLIER_H_
#define _MULTIPLIER_H_
#include "game.h"



void recmove(int n, char direction, Game &g); //Move the block n times
bool recdrop(int n, Game &g); //drop n blocks
void recrotate(int n, std::string command, Game &g);  //rotate n times
void reclvup(int n, Game &g); //level up n times
void reclvdown(int n, Game &g); //level down n times

#endif
