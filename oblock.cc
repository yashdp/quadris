#include <iostream>
#include <string>
#include "oblock.h"
#include "pos.h"

using namespace std;

//=================================================
OBlock::OBlock(int Level){
  level = Level;
  cords[0] = new Pos(0, 0,true);
  cords[1] = new Pos(0, 1,true);
  cords[2] = new Pos(1, 0,true);
  cords[3] = new Pos(1, 1,true);
  for(int i = 0; i < 4; i++){
    prev[i] = NULL;
    next[i] = NULL;	
    visited = false;
  }
}
//=======================================================
void OBlock:: replace(int oldx, int oldy, int newx, int newy){
  for(int i = 0; i < 4; i++){
    if((cords[i]->x == oldx)&&(cords[i]->y == oldy)){
      cords[i]->x = newx;
      cords[i]->y = newy;
      return;
    }
  }
}
//=========================================================
void OBlock :: setvisited(){
  visited = true;
}
//========================================================
void OBlock:: notifyDisplay(TextDisplay &t){
  for(int i= 0; i < 4; i++){
    t.notifymiddle(cords[i]->x, cords[i]->y, 'O');
  }
}
//========================================
void OBlock:: notifyBottom(TextDisplay &t){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 4; j++){
      t.notifybottom(i,j, ' ');
    }
  }
  for(int i= 0; i < 4; i++){
    t.notifybottom(cords[i]->x, cords[i]->y, 'O');
  }
}
//=======================================
void OBlock:: move(char w, TextDisplay &t){
  for(int i=0; i < 4; i++){
    if (w == 'u'){
      cords[i]->change((cords[i]->x)-1, (cords[i]->y));
    }else if(w == 'd'){
      cords[i]->change((cords[i]->x)+1, (cords[i]->y));
    }else if (w == 'r'){
      cords[i]->change((cords[i]->x), (cords[i]->y)+1);
    }else if(w == 'l'){
      cords[i]->change((cords[i]->x), (cords[i]->y)-1);
    }
  }
}
//=====================================================

void OBlock::rotate(string w, TextDisplay &t){}
