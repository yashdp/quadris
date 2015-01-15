#ifndef _POS_H_
#define _POS_H_

#include <iostream>
class Pos{
 public:
  int x;
  int y;
  bool isOn;
  void change(int x, int y);
  Pos(int x, int y, bool on);
};


#endif
