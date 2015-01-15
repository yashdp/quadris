#include <iostream>
#include "iblock.h"
#include "pos.h"

using namespace std;
IBlock:: IBlock(int Level){
  this->level = Level;
  visited = false;
  d = 'e';
  for(int i = 0; i < 4; i++){
    cords[i] = new Pos(0,i,true);
  }
  prev[0] = new Pos(1, 1,true);
  prev[1] = new Pos(0, 1,true);
  prev[2] = new Pos(-1, 1,true);
  prev[3] = new Pos(-2, 1,true);
  next[0] = new Pos(-1,1,true);
  next[1] = new Pos(0,1,true);
  next[2] = new Pos(1,1,true);
  next[3] = new Pos(2,1,true);
}
//==========================

void IBlock:: replace(int oldx, int oldy, int newx, int newy){
  for(int i = 0; i < 4; i++){
    if((cords[i]->x == oldx)&&(cords[i]->y == oldy)){
      cords[i]->x = newx;
      cords[i]->y = newy;
      return;
    }
  }
}

void IBlock :: setvisited(){
  visited = true;
}
//=========================  
void IBlock:: notifyDisplay(TextDisplay &t){
  for(int i= 0; i < 4; i++){
    t.notifymiddle(cords[i]->x, cords[i]->y, 'I');
  }
}
//========================
void IBlock:: notifyBottom(TextDisplay &t){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 4; j++){
      t.notifybottom(i,j, ' ');
    }
  }
  for(int i= 0; i < 4; i++){
    t.notifybottom(cords[i]->x, cords[i]->y, 'I');
  }
}
//=========================
void IBlock:: rotate(string w, TextDisplay &t){
  if(w == "ccw"){
    rotate("cw", t);
    rotate("cw", t);
    rotate("cw", t);
    return;
  }
  if( w == "cw"){
    for(int i= 0; i < 4; i++){
      if((d == 'e')&&(i == 3)){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+2, cords[i]->y-2);
	next[i]->change(cords[i]->x-2, cords[i]->y-2);
      }else if((d == 's')&&(i == 3)){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-2, cords[i]->y-2);
	next[i]->change(cords[i]->x-2, cords[i]->y+2);
      }else if((d == 'w')&&(i == 3)) {
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-2, cords[i]->y+2);
	next[i]->change(cords[i]->x+2, cords[i]->y+2);
      }else if((d == 'n')&&(i == 3)) {
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+2, cords[i]->y+2);
	next[i]->change(cords[i]->x+2, cords[i]->y-2);
      }else if(((d == 'e')&&(i == 0))||((d == 'w')&&(i == 2))){ //<----works
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-1, cords[i]->y+1);
	next[i]->change(cords[i]->x+1, cords[i]->y+1);
      }else if(((d == 'e')&&(i == 2))||((d == 'w')&&(i == 0))){ //<----works
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+1, cords[i]->y-1);
	next[i]->change(cords[i]->x-1, cords[i]->y-1);
      }else if((d == 's')&&(i == 0)){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+1, cords[i]->y+1);
	next[i]->change(cords[i]->x+1, cords[i]->y-1);
      }else if((d == 'n')&&(i == 2)){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+1, cords[i]->y+1);
	next[i]->change(cords[i]->x+1, cords[i]->y-1);
      }else if((d == 's')&&(i == 2)){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-1, cords[i]->y-1);
	next[i]->change(cords[i]->x-1, cords[i]->y+1);
      }else if((d == 'n')&&(i == 0)){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-1, cords[i]->y-1);
	next[i]->change(cords[i]->x-1, cords[i]->y+1);
      }else{
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x, cords[i]->y);
	*(next[i]) = *(cords[i]);
      }
    }
  }
  if (w == "cw"){
    if(d == 'e'){ d = 's';}
    else if(d == 'w'){ d = 'n';}
    else if(d == 's'){ d = 'w';}
    else{ d = 'e';}
  }else{
    if(d == 'e'){ d = 'n';}
    else if(d == 'w'){ d = 's';}
    else if(d == 's'){ d = 'e';}
    else{ d = 'w';}
  }
}

//=======================
void IBlock:: move(char w, TextDisplay &t){
  for(int i=0; i < 4; i++){
    if (w == 'u'){
      cords[i]->change((cords[i]->x)-1, (cords[i]->y));
      prev[i]->change((prev[i]->x)-1, (prev[i]->y));
      next[i]->change((next[i]->x)-1, (next[i]->y));
    }else if(w == 'd'){
      cords[i]->change((cords[i]->x)+1, (cords[i]->y));
      prev[i]->change((prev[i]->x)+1, (prev[i]->y));
      next[i]->change((next[i]->x)+1, (next[i]->y));
    }else if (w == 'r'){
      cords[i]->change((cords[i]->x), (cords[i]->y)+1);
      prev[i]->change((prev[i]->x), (prev[i]->y)+1);
      next[i]->change((next[i]->x), (next[i]->y)+1);
    }else if(w == 'l'){
      cords[i]->change((cords[i]->x), (cords[i]->y)-1);
      prev[i]->change((prev[i]->x), (prev[i]->y)-1);
      next[i]->change((next[i]->x), (next[i]->y)-1);
    }
  }
}
//=====================================================
