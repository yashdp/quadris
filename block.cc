#include <iostream>
#include "block.h"
using namespace std;


//==================================
void Block:: notifyBottom(TextDisplay &t){}
//==================================
int Block:: getX(char arr, int i){
  if(arr == 'c'){
    return cords[i]->x;
  }else if(arr == 'p'){
    if(prev[i] == NULL){
      return 999;
    }
    return prev[i]->x;
  }else{
    if(next[i] == NULL){
      return 999;
    }
    return next[i]->x;
  }
}
//==============================

//=============================
int Block:: getL(){
  return level;
}
//===============================
int Block:: getY(char arr, int i){
  if(arr == 'c'){
    return cords[i]->y;
  }else if(arr == 'p'){
    if(prev[i] == NULL){
      return 999;
    }
    return prev[i]->y;
  }else{
    if(next[i] == NULL){
      return 999;
    }
    return next[i]->y;
  }
}
//================================
bool Block::isOff(){
  for(int i =0; i < 4; i++){
    if (cords[i]->isOn){
      return false;
    }
  }
  return true;
}
//===============================
void Block::turnOff(int x){
  for(int i = 0; i < 4; i++){
    if(cords[i]->x == x){
	 cords[i]->isOn = false;
    }
  }
}

//===============================
Block::~Block(){
  for (int i = 0; i < 4; i++){
    delete cords[i];
    delete prev[i];
    delete next[i];
  }
}
//==================================
bool Block:: isVisited(){
  return visited;
}
