#include "multiplier.h"
#include <iostream>

using namespace std;


//=====================================
void recmove(int n, char direction, Game &g){
  if ((n == 1) || (n == 0)){
    g.move(direction);
  }else{
    g.move(direction);
    recmove(n - 1, direction, g);
  }
}

//================================
bool recdrop(int n, Game &g){
  if ((n == 1) || (n == 0)){
    g.drop();
    g.clear();
    return true;
  }else{
    g.drop();
    g.clear();
    g.makeBlock();
    if (g.didIlose()){
        return false;
    }
    recdrop(n - 1, g);
  }
}
//===========================================
void recrotate(int n, string command, Game &g){
  if ((n == 1) || (n == 0)){
    g.rotate(command);
  }else{
    g.rotate(command);
    recrotate(n - 1, command, g);
  }
}

//=========================================
void reclvup(int n, Game &g){
  if ((n == 1) || (n == 0)){
    g.levelup();
  }else{
    g.levelup();
    reclvup(n - 1, g);
  }
}
//==========================================
void reclvdown(int n, Game &g){
  if ((n == 1) || (n == 0)){
    g.leveldown();
  }else{
    g.leveldown();
    reclvdown(n - 1, g);
  }
}
//=============================================

