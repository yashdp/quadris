#include <iostream>
#include "pos.h"
using namespace std;

Pos::Pos(int x, int y, bool on):x(x),y(y),isOn(on){}

void Pos:: change(int x, int y){
  this->x = x;
  this->y=y;
}
