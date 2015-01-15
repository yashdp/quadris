#include <iostream>
#include "tblock.h"
#include "pos.h"

using namespace std;
TBlock:: TBlock(int Level){
  level = Level;
  d = 'n';
  cords[0]= new Pos(0,0,true); // This should be the first one
  cords[1]= new Pos(0,1,true);
  cords[2]= new Pos(0,2,true);
  cords[3] = new Pos(1,1,true);
  prev[0] = new Pos(-1,1,true);
  prev[1] = new Pos(0, 1,true);
  prev[2] = new Pos(1,1,true);
  prev[3] = new Pos(0,0,true);
  next[0] = new Pos(1,1,true);
  next[1] = new Pos(0,1,true);
  next[2] = new Pos(-1,1,true);
  next[3] = new Pos(0,2,true);
  visited = false;
  for(int i = 0; i < 4; i++){
    temp[i] = new Pos(cords[i]->x, cords[i]->y,true);
  }
}
//==================================================
void TBlock:: replace(int oldx, int oldy, int newx, int newy){
  for(int i = 0; i < 4; i++){
    if((cords[i]->x == oldx)&&(cords[i]->y == oldy)){
      cords[i]->x = newx;
      cords[i]->y = newy;
      return;
    }
  }
}

//=========================
TBlock::~TBlock(){  
  for (int i = 0; i < 4; i++){
    delete temp[i];
  }
}
//=========================
void TBlock ::setvisited(){
  visited = true;
}
//==========================  
void TBlock:: notifyDisplay(TextDisplay &t){
  for(int i= 0; i < 4; i++){
    t.notifymiddle(cords[i]->x, cords[i]->y, 'T');
  }
}
//========================
void TBlock:: notifyBottom(TextDisplay &t){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 4; j++){
      t.notifybottom(i,j, ' ');
    }
  }
  for(int i= 0; i < 4; i++){
    t.notifybottom(cords[i]->x, cords[i]->y, 'T');
  }
}
//=========================
void TBlock:: rotate(string w, TextDisplay &t){
  if (w == "ccw") {
    rotate("cw", t);
    rotate("cw", t);
    rotate("cw", t);
    return;
  }
  //-----------------
  if(d == 'n'){
    for(int k = 0; k < 4; k++){
      cords[k]->change(temp[k]->x, temp[k]->y);
    }
  }
  if( w == "cw"){
    for(int i= 0; i < 4; i++){
      if(((d == 'n')&&(i == 0))||((d == 's')&&(i == 2))||((d == 'e')&&(i == 3))){ 
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-1, cords[i]->y+1);
	next[i]->change(cords[i]->x+1, cords[i]->y+1);
      }else if(((d == 'n')&&(i == 2))||((d == 'w')&&(i == 3))||((d == 's')&&(i == 0))){ 
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+1, cords[i]->y-1);
	next[i]->change(cords[i]->x-1, cords[i]->y-1);
      }else if(((d == 'n')&&(i == 3))||((d == 'w')&&(i == 0))||((d == 'e')&&(i == 2))){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-1, cords[i]->y-1);
	next[i]->change(cords[i]->x-1, cords[i]->y+1);
      }else if(((d == 'w')&&(i == 2))||((d == 's')&&(i == 3))||((d == 'e')&&(i == 0))){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x+1, cords[i]->y+1);
	next[i]->change(cords[i]->x+1, cords[i]->y-1);
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
void TBlock:: move(char w, TextDisplay &t){
  for(int i=0; i < 4; i++){
    if (w == 'u'){
      cords[i]->change((cords[i]->x)-1, (cords[i]->y));
      prev[i]->change((prev[i]->x)-1, (prev[i]->y));
      next[i]->change((next[i]->x)-1, (next[i]->y));
      temp[i]->change((temp[i]->x) - 1, (temp[i]->y));
    }else if(w == 'd'){
      cords[i]->change((cords[i]->x)+1, (cords[i]->y));
      temp[i]->change((temp[i]->x) + 1, (temp[i]->y));
      prev[i]->change((prev[i]->x)+1, (prev[i]->y));
      next[i]->change((next[i]->x)+1, (next[i]->y));
    }else if (w == 'r'){
      cords[i]->change((cords[i]->x), (cords[i]->y)+1);
      temp[i]->change((temp[i]->x), (temp[i]->y)+1);
      prev[i]->change((prev[i]->x), (prev[i]->y)+1);
      next[i]->change((next[i]->x), (next[i]->y)+1);
    }else if(w == 'l'){
      cords[i]->change((cords[i]->x), (cords[i]->y)-1);
      temp[i]->change((temp[i]->x), (temp[i]->y)-1);
      prev[i]->change((prev[i]->x), (prev[i]->y)-1);
      next[i]->change((next[i]->x), (next[i]->y)-1);
    }
  }
}
//=====================================================
