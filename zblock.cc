#include <iostream>
#include "zblock.h"
#include "pos.h"

using namespace std;
ZBlock:: ZBlock(int Level){
  level = Level;
  d = 'e';
  visited = false;
  cords[0]= new Pos(0,0,true); // This should be the first one
  cords[1]= new Pos(0,1,true); //Fixed block
  cords[2]= new Pos(1,1,true);
  cords[3] = new Pos(1,2,true);
  
  next[0]= new Pos(0,2,true); // This should be the first one
  next[1]= new Pos(1,2,true); //Fixed block
  next[2]= new Pos(1,1,true);
  next[3] = new Pos(2,1,true);
  
  prev[0]= new Pos(2,0,true); // This should be the first one
  prev[1]= new Pos(1,0,true); //Fixed block
  prev[2]= new Pos(1,1,true);
  prev[3] = new Pos(0,1,true);
}
//=======================================
void ZBlock:: replace(int oldx, int oldy, int newx, int newy){
  for(int i = 0; i < 4; i++){
    if((cords[i]->x == oldx)&&(cords[i]->y == oldy)){
      cords[i]->x = newx;
      cords[i]->y = newy;
      return;
    }
  }
}
//===================================
void ZBlock :: setvisited(){
  visited = true;
}
//==========================  
void ZBlock:: notifyDisplay(TextDisplay &t){
  for(int i= 0; i < 4; i++){
    t.notifymiddle(cords[i]->x, cords[i]->y, 'Z');
  }
}
//========================
void ZBlock:: notifyBottom(TextDisplay &t){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 4; j++){
      t.notifybottom(i,j, ' ');
    }
  }
  for(int i= 0; i < 4; i++){
    t.notifybottom(cords[i]->x, cords[i]->y, 'Z');
  }
}
//=========================
void ZBlock:: rotate(string w, TextDisplay &t){
  
  for(int i= 0; i < 4; i++){
    if( i >= 2){
      *(prev[i]) = *(cords[i]);
      cords[i]->change(cords[i]->x, cords[i]->y);
      *(next[i]) = *(cords[i]);
    } 
    if((d == 'e')||(d == 'w')){
      if(i == 0){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x, cords[i]->y+2);
	next[i]->change(cords[i]->x, cords[i]->y -2);
      }
      if (i == 1){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x +2, cords[i]->y);
	next[i]->change(cords[i]->x-2, cords[i]->y);
      }
    }
    if ((d == 'n') || (d == 's')){	
      if( i == 0){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x, cords[i]->y -2);
	next[i]->change(cords[i]->x, cords[i]->y+2);
      }
      if (i == 1){
	*(prev[i]) = *(cords[i]);
	cords[i]->change(cords[i]->x-2, cords[i]->y);
	next[i]->change(cords[i]->x +2, cords[i]->y);
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
void ZBlock:: move(char w, TextDisplay &t){
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
    
