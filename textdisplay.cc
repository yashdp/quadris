#include <iostream>
#include <string>
#include "textdisplay.h"
#include "window.h"
#include <sstream>
using namespace std;


TextDisplay:: TextDisplay(int w, int h, Xwindow *g ):  gridH(w),gridW(h){
  this->w = g;
  score = 0;
  highscore = 0;
  level = 0;
  //Game Display (Middle)---------------------------
  gameDisplay = new char*[gridW];
  for(int i = 0; i < gridW; i++){
    gameDisplay[i] = new char[gridH];
    for(int j = 0; j < gridH; j++){
      gameDisplay[i][j] = ' ';
    } 
  }
  //Bottom Display
  bottomDisplay = new char*[2];
  for(int i = 0; i < 2; i++){
    bottomDisplay[i] = new char[4];
    for(int j = 0; j < 4; j++){
      bottomDisplay[i][j] = ' ';
    }
  }
}
//==============================================
void TextDisplay:: setScore(int s){
  ostringstream old;
  string  b = "Score: ";
  old << b << score; 
  score = s;
  
  if (w != NULL){ 
    ostringstream ss;
    ss << "Score: " << score;
    w->drawString(500,200,old.str());
    w->drawString(500,200,ss.str(),Xwindow::MediumOrchid);
  }
}
//==============================================
void TextDisplay:: clear(){
  for(int i = 3; i < gridW; i++){
    for(int j = 0; j < gridH; j++){
      notifymiddle(i,j,' ');
    }
  }
}
//=============================================
void TextDisplay:: setHighscore(int hs){
  ostringstream old;
  string  b = "Hi Score: ";
  old << b << highscore;
  
  highscore = hs;
  if (w != NULL){
    ostringstream ss;
    ss << "Hi Score: " << highscore;
    w->drawString(500,150,old.str());
    w->drawString(500,150,ss.str(),Xwindow::DeepSkyBlue);
  }
}
//==============================================
void TextDisplay :: setLevel(int l){

  ostringstream old;
  string  b = "Level: ";
  old << b << level;
  
  level = l;
  if(w != NULL){  
    ostringstream ss;
    ss << "Level: " << level;
    w->drawString(500,100,old.str());
    w->drawString(500,100,ss.str(),Xwindow::OliveDrab);
  }
}
//===============================================
void TextDisplay:: draw(int r, int c, char ch){
  //  int height = 37;
  // int width = 37;
  if(ch == ' '){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Black);
  }else if(ch == 'I'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Red);
  }else if(ch  == 'O'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Green);
  }else if(ch == 'J'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Cyan);
  }else if(ch  == 'L'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Blue);
  }else if(ch  == 'T'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::OliveDrab);
  }else if(ch  == 'S'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Orange);
  }else if(ch  == 'Z'){
    w->fillRectangle(c+(37)*c,r+(37)*r,37,37, Xwindow::Magenta);
  }
  w->drawString(0,120,"****************************************************************",0);
}
//================================================
void TextDisplay:: notifymiddle(int r, int c, char ch){
  gameDisplay[r][c] = ch;
  if (w != NULL){
    draw(r,c,ch);
  }
}
//===============================================
void TextDisplay:: notifybottom(int r, int c, char ch){
  bottomDisplay[r][c] = ch;
  if (w != NULL){
    w->drawString(500,250,"NEXT:",Xwindow::BlueViolet);
    draw(r+7,c+13,ch);
  }
}
//================================================
TextDisplay:: ~TextDisplay(){
  for(int i = 0; i < gridW; i++){ 
    delete [] gameDisplay[i];
  }
  for(int i = 0; i < 2; i++){
    delete [] bottomDisplay[i];
  }
  delete [] bottomDisplay;
  delete [] gameDisplay;
}
//==============================================
void TextDisplay:: removeRow(int r){
  for (int x = r - 1; x >= 0; x--){
    for (int c = 0; c < gridW; c++){
      notifymiddle(x+1,c,gameDisplay[x][c]);
    }
  }
}
//===========================================
ostream &operator<<(ostream &out, const TextDisplay &td){
  //top.....
  cout << "Level: "<< td.level << endl;
  cout << "Score: " << td.score << endl;
  cout << "Hi Score: " << td.highscore <<endl;
  //middle.....
  cout << "XXXXXXXXXX" << endl;
  for(int i = 0; i < td.gridW; i++){
    if (i != 0){
      cout << "|" <<endl;
    }
    if(i == 3){
      cout << "-----------" << endl;
    }
    for(int j = 0; j < td.gridH; j++){
      out << td.gameDisplay[i][j];
    }
  }
  cout << "|" << endl << "XXXXXXXXXX" <<endl;
  //bottrom....
  cout << "Next:" << endl;
  for(int i = 0; i < 2; i++){
    if (i != 0){
      cout <<endl;
    }
    for(int j = 0; j < 4; j++){
      out << td.bottomDisplay[i][j];
    }
  }
  cout << endl << "==========" ;
  return out;
}
//=======================================================
