#include "game.h"
//#include "window.h"
#include "pos.h"
#include "block.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
using namespace std;


Game::Game(bool text, bool seed, string file, int seeder, int level, bool keyboard): height(18), width(10), level(level), sequence(file),key(keyboard) {
    
  w = NULL;
  del = false;
  highscore = 0;
  score = 0;

  if(!text){
    w = new Xwindow;
    w->fillRectangle(0,0,650,680,Xwindow::Black); 
    for(int i = 0; i <=650 ; i += 25){
      w->drawString(380,i,"|",0);
    }
    w->drawString(490,50,"Q",Xwindow::Orange);
    w->drawString(500,45,"U",Xwindow::Blue);
    w->drawString(510,40,"A",Xwindow::Green);
    w->drawString(520,35,"D",Xwindow::Red);
    w->drawString(530,40,"R",Xwindow::Magenta);
    w->drawString(540,45,"I",Xwindow::OliveDrab);
    w->drawString(550,50,"S",Xwindow::Cyan);
    w->drawString(0,120,"****************************************************************",0);
  }
  //***********************************
  l = new Level(sequence,seed,seeder);
  l->setlevel(level);
  curblock = NULL;
  nextblock = NULL;
  if(text){
    t = new TextDisplay(width, height, NULL);//
  }else{
    t = new TextDisplay(width, height, w);//
  }
  //*********************************
  //Initializing the gameBoard
  gameBoard = new char*[height];
  for (int i = 0; i < height; i++){
    gameBoard[i] = new char[width];
    for(int j = 0; j < width; j++){
      gameBoard[i][j] = ' ';
    }
  }
  //********************************
  updateScore(score);
  updateLevel(level);
  updateHighscore(highscore);
}
//=====================================================================================
void Game:: emptyBoard(){
  //clear the gameBoard
  for (int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      gameBoard[i][j] = ' ';
    }
  }
  int len = v.size();
  //delete all the blocks ever create excluding the 
  //current block and next block
  for(int i =0; i < len-1; i++){
    delete v[i];
  }
  v.erase(v.begin(),v.end()-1);
  t->clear();
  updateScore(0);
}
//============================================================================
void Game:: turnOffRow(int x){
  int len = v.size();
  for(int i = 0; i < len; i++){
    v[i]->turnOff(x);
  }
}
//===========================================================================
int Game:: blockRemoved(){
  int tempscore = 0;
  int len = v.size();
  //Calculates the score of the removed blocks
  for(int i =0; i < len; i++){
    if((v[i]->isOff())&&(!v[i]->isVisited())){
      v[i]->setvisited();
      tempscore += ((v[i]->getL() + 1)*(v[i]->getL() + 1));
    }
  }
  return tempscore;
}
//=============================================================================
void Game:: updateScore(int s){
  score = s;
  if (score > highscore){
    updateHighscore(score);
  }
  t->setScore(score);
}
//=========================================================================
void Game::levelup(){
  if(level < 3){
    updateLevel(level+1);
  }
}
//==========================================================================
void Game::leveldown(){
   if(level > 0){
     updateLevel(level-1);
   }
}
//==========================================================================
void Game:: updateHighscore(int hs){
  highscore = hs;
  t->setHighscore(highscore);
}
//==========================================================================
void Game:: updateLevel(int l){
  level = l;
  t->setLevel(level);
  this->l->setlevel(level);
}
//=========================================================================
void Game:: makeBlock(){
  if((curblock != NULL)&&(!del)){
    update();
    del= false;
  }
  if (nextblock == NULL){
    curblock = l->getBlock();
    nextblock = l->getBlock();
  }else{
    curblock = nextblock;
    nextblock = l->getBlock();
  }
  if (dynamic_cast<TBlock *>(curblock)) { curblock->move('d',*t);}
  firsttime = true;
  v.push_back(curblock);
  curblock->notifyDisplay(*t);
  nextblock->notifyBottom(*t);
}

//============================================================================
void Game:: update(){
  for(int i= 0; i < 4; i++){
    gameBoard[curblock->getX('c',i)][curblock->getY('c',i)] = 'X';
  }
}
//==========================================================================
void Game:: remove(int r){
  turnOffRow(r);
  for (int x = r - 1; x >= 0; x--) {
    for (int c = 0; c < width; c++) {
      gameBoard[x + 1][c] = gameBoard[x][c];
      //useD for Changing every cordinates that contains (x,c)->(x+1,c)
      int len = v.size();
      for(int i = 0; i < len; i++){
	v[i]->replace(x,c,x+1,c);
      }
    }
  }
}
//=============================================================================
bool Game::didIlose(){
  int num;
  if (isitT()){
    num = 2;
  }else{
    num = 3;
  }
  //Determines if the game is lost
  //T is considered special block because of its unique starting position
  for (int i = 0; i < 4; i++){
    if (gameBoard[curblock->getX('c', i) + num][curblock->getY('c', i)] != ' '){
      if(w != NULL){
	if(!key){
	  cout << *t << endl;
	  cout << "Sorry, you lost\n";
	}
	//Some User friendly animation when the game is Lost
	w->drawBigString(150, 300, "Game Over", Xwindow::DeepSkyBlue);
	w->drawBigString(400, 550, "Restarting in..", Xwindow::DeepSkyBlue);
	sleep(1);
	w->drawBigString(400, 550, "Restarting in..");
	w->drawBigString(500,500, "3...",Xwindow::DeepSkyBlue);
	sleep(1);
    	w->drawBigString(500,500, "3...");
        w->drawBigString(500,500, "2..",Xwindow::DeepSkyBlue);
	sleep(1);
	w->drawBigString(500,500, "2..");
	w->drawBigString(500,500, "1.",Xwindow::DeepSkyBlue);
        sleep(1);
	w->drawBigString(500,500, "1.");
	w->drawBigString(150, 300, "Game Over");
	emptyBoard();
	return true;
      }else{
	cout << *t << endl;
	cout << "Sorry, you lost\n";
	emptyBoard();
      }
      return true;
    }
  }
  return false;
}

//===============================================================================
void Game::drop(){
  while(moveable('d')){
    move('d');
  }
  update();
}

//direction is one of: 'u', 'd', 'l', 'r'
//================================================================================
bool Game::moveable(char direction){
  for (int i = 0; i < 4; i++){
    //Check if the block can be moved up
    if (direction == 'u'){
      if (curblock->getX('c',i) - 1 < 3){
	return false;
      }else{
        if(!(gameBoard[curblock->getX('c',i) - 1][curblock->getY('c',i) ] == ' ')){
          return false;
        }
      }
    }
    //Check if the block can be moved down
    if (direction == 'd'){
      if (curblock->getX('c',i) + 1 >= height){
	return false;
      }else{
	if(!(gameBoard[curblock->getX('c',i) + 1][curblock->getY('c',i)] == ' ')){
	  return false;
	}
      }
    }
    //Check if the block can be moved left
    if (direction == 'l'){
      if (!((gameBoard[curblock->getX('c',i)][curblock->getY('c',i)- 1] == ' ') &&
	    (curblock->getY('c',i) - 1 >= 0))){
	return false;
      }
    }
    //Check if the block can be moved right
    if (direction == 'r'){
      if (!((gameBoard[curblock->getX('c',i)][curblock->getY('c',i)+ 1] == ' ') &&
	    (curblock->getY('c',i) + 1 <= width))){
	return false;
      }
    }
  }
  return true;
}
//==================================================================
bool Game:: isitT(){
  return (((dynamic_cast<TBlock *> (curblock))&&(curblock->getX('c',3) == 2))||
	  ((dynamic_cast<JBlock *> (curblock))&&(curblock->getX('c',0) == 2)&&(curblock->getX('c',1) == 1))||
	  ((dynamic_cast<LBlock *> (curblock))&&(curblock->getX('c',0) == 2)&&(curblock->getX('c',1) == 1)));
}
//======================================================================
bool Game::rotatable(string command){

  if((curblock->getX('n',0) == 999) || (curblock->getX('p',0) == 999)) return true;
  for (int i = 0; i < 4; i++){
    //Check if the block is rotatable Clockwise
    if (command == "cw"){
      if (!((curblock->getX('n',i) < height) &&
	    (curblock->getX('n',i)  >= 0) &&
	    (curblock->getY('n',i)  <= width) &&
	    (curblock->getY('n',i)  >= 0)&&
	    (gameBoard[curblock->getX('n',i)][curblock->getY('n',i)] == ' '))){
	return false;
      }
      if ((!firsttime)&&(curblock->getX('n',i)  < 3)){
	return false;
      }
    }
    //Check if the block is rotatable Counterclockwise
    if (command == "ccw"){
      if (!((curblock->getX('p',i) < height) &&
	    (curblock->getX('p',i) >= 0) &&
	    (curblock->getY('p',i) <= width) &&
	    (curblock->getY('p',i) >= 0)&&
	    (gameBoard[curblock->getX('p',i)][curblock->getY('p',i)] == ' '))){
	return false;
      }
      if ((!firsttime)&&(curblock->getX('p',i)  < 3)){
        return false;
      }
    }
  }
  return true;
}

//=====================================================================
void Game::move(char direction){
  if((firsttime)&&(direction == 'd')){
    for(int i =0; i < 4 ; i++){
      t->notifymiddle(curblock->getX('c',i),curblock->getY('c',i),' ');
    }
    //Move down to get out of the reserved row when down is called for the first time
    if(isitT()){
      curblock->move('d', *t);
      curblock->move('d', *t);
    }else{
      curblock->move('d',*t);
      curblock-> move('d',*t);
      curblock->move('d',*t);
    }
    curblock->notifyDisplay(*t);
    firsttime = false;
    return;
  }
  //Move regularly by 1 unit if out of the reserved rows
  if (moveable(direction)){
    for(int i =0; i < 4 ; i++){
      t->notifymiddle(curblock->getX('c',i),curblock->getY('c',i),' ');
    }
    curblock->move(direction, *t);
    curblock->notifyDisplay(*t);
  }else{
    //cout << "Can't Move!!";
  }
}
//=====================================================================
void Game::rotate(string command){
  if (rotatable(command)){
    for(int i =0; i < 4 ; i++){
      t->notifymiddle(curblock->getX('c',i),curblock->getY('c',i),' ');
    }
    curblock->rotate(command, *t);
    curblock->notifyDisplay(*t);
  }else{
    //cout << "Can't Rotate";
  }
}
//==================================================================
void Game::clear(){
  int blockscore = 0;
  for (int i = 0; i < height; i++){
    //Checks if there exist a row which is filled
    if ((gameBoard[i][0] != ' ') && (gameBoard[i][1] != ' ') && (gameBoard[i][2] != ' ') &&
	(gameBoard[i][3] != ' ') && (gameBoard[i][4] != ' ') && (gameBoard[i][5] != ' ') &&
	(gameBoard[i][6] != ' ') && (gameBoard[i][7] != ' ') && (gameBoard[i][8] != ' ') &&
	(gameBoard[i][9] != ' ')){
      t->removeRow(i);
      remove(i);
      del = true;
      blockscore = blockRemoved();
      //Updates the score
      score += ((level + 1)*(level + 1))+ blockscore;
      updateScore(score);
    }
  }
}
//=================================================================
Game::~Game(){
  for (int i = 0; i < height; i++){
    delete [] gameBoard[i];
  }
  delete [] gameBoard;
  delete l;
  int len = v.size();
  for(int i = 0; i < len; i++){
    delete v[i];
  }
  delete w;
  delete nextblock;
  delete t;
}
//================================================================
ostream &operator << (ostream &out, const Game &g){
  out << *g.t;
  return out;
}
//================================================================
