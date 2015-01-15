#include <iostream>
#include <cstdlib>
#include "block.h"
#include "sblock.h"
#include "zblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "tblock.h"
#include "iblock.h"
#include "level.h"
#include <fstream>

using namespace std;

Level::Level(string file,bool seed,int seeder): ignore(1), level(0), file(file){
  ifstream f(file.c_str());
  char c;
  int num = 0;
  while (f >> c){
    num++;
  }
  count = num;
  if(seed){
    srand(seeder);
  }
}
//==============================================================================
char Level::zero(){
  char s;
  ifstream f(file.c_str());
  if (ignore > count){
    ignore = 1;
  }
  for (int i = 1; i < ignore; i++){
    f >> s;
  }
  f >> s;
  ignore++;
  return s;
}
//=============================================================================
char Level::random12(){
  int max = 12;
  int min = 0;
  int range = max - min + 1;
    int num = rand() % range + min;
  
  if (num == 1){
    return 'S';
  }else if (num == 2){
    return 'Z';
  }else if ((num == 3) || (num == 4)){
    return 'T';
  }else if ((num == 5) || (num == 6)){
    return 'I';
  }else if ((num == 7) || (num == 8)){
    return 'L';
  }else if ((num == 9) || (num == 10)){
    return 'O';
  }else{
    return 'J';
  }
}
//================================================================
char Level::random7(){
  int max = 7;
  int min = 0;
  int range = max - min + 1;
  int num = rand() % range + min;
  
  if (num == 1){
    return 'S';
  }else if (num == 2){
    return 'Z';
  }else if (num == 3){
    return 'I';
  }else if (num == 4){
    return 'L';
  }else if (num == 5){
    return 'O';
  }else if (num == 6){
    return 'J';
  }else{
    return 'T';
  }
}
//===============================================================
char Level::random9(){
  int max = 9;
  int min = 0;
  int range = max - min + 1;
  int num = rand() % range + min;
  
  if ((num == 1) || (num == 2)){
    return 'S';
  }else if ((num == 3) || (num == 4)){
    return 'Z';
  }else if (num == 5){
    return 'I';
  }else if (num == 6){
    return 'L';
  }else if (num == 7){
    return 'O';
  }else if (num == 8){
    return 'J';
  }else{
    return 'T';
  }
}
//===============================================================
void Level::setlevel(int n){
  this->level = n;
}
//===============================================================
Block* Level::getBlock(){
  char b;
  
  if (level == 1){
    b = random12();
  }else if (level == 2){
    b = random7();
  }else if (level == 3){
    b = random9();
  }else if (level == 0){
    b = zero();
  }
  
  if (b == 'S'){
    return new SBlock(level);
  }else  if (b == 'Z') {
    return new ZBlock(level);
  }else if (b == 'O'){
    return new OBlock(level);
  }else if (b == 'J'){
    return new JBlock(level);
  }else if (b == 'L'){
    return new LBlock(level);
  }else if (b == 'T'){
    return new TBlock(level);
  }else{
    return new IBlock(level);
  }
}
//=======================================================
