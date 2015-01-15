#include "game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include <sstream>
#include <ncurses.h>
#include <fstream>
#include "multiplier.h"
using namespace std;

//KeyBoard Keys:
//W -> Move Up
//A -> Move Left
//S -> Move Down
//D -> Move Right
//SPACE -> Drop
//N -> Rotate CounterClockwise
//M -> Rotate Clockwise
//+ -> Level up
//- -> Level down
//=============================================
int main(int argc, char *argv[]){
  bool text = false;
  bool seed = false;
  string inputFile = "shortcut.txt";
  int seeder = 0;
  string file = "sequence.txt";
  int level = 0;
  string arg = "";
  bool keyboard = false;
  //Command-Line Options
  for (int i = 1; i < argc; i++){
    arg = argv[i];
    if (arg == "text"){
      text = true;
    }else if (arg == "seed"){
      seed = true;
      seeder = atoi(argv[i+1]);			//argv[i+1] is char*
    }else if (arg == "scriptfile"){
      file = argv[i+1];
    }else if (arg == "startlevel"){
      level = atoi(argv[i+1]);			//argv[i+1] is char*
    }else if (arg == "keyboard"){
      keyboard = true;
    }
  }
   
  Game g(text,seed,file,seeder,level,keyboard);
  
  g.makeBlock();

  if(!keyboard){
    string command = "";
    string result = "";
    string multi = "";
    int multiplier = 0;
    int counter = 0;  
    if (g.didIlose()){
      cout << "Sorry, You lost\n";
    }
    cout << g << endl;
    while(true){
      cin >> command;
      if (cin.eof()){
	return 0;
      }
      //....................................
      if(command[0] != '0'){
	int len = command.length();
	for (int i = 0; i < len; i++){
	  if(isdigit(command[i])){
	    multi += command[i];
	    counter++;
	  }
	}
	if (multi == ""){
	  multiplier = 0;
	}else{
	  multiplier = atoi(multi.c_str());
	}
	result = command.substr(counter, len);
	//...Extract commands from a file.
	string inp;
	ifstream f(inputFile.c_str());
	while(f >> inp){
	  if(inp == result){
	    f >> result;
	    break;
	  }
	}
      }
      //....................................
      if (result == "clockwise"){
	recrotate(multiplier, "cw", g);
      }else if(result == "counterclockwise"){
	recrotate(multiplier, "ccw", g);
      }else if(result == "up"){
	recmove(multiplier, 'u', g);
      }else if(result == "down"){
	recmove(multiplier, 'd', g);
      }else if(result == "right"){
	recmove(multiplier, 'r', g);
      }else if(result == "left"){
	recmove(multiplier, 'l', g);
      }else if(result == "drop"){
	if(recdrop(multiplier, g)){
	  g.clear();
	  g.makeBlock();
	}
	g.didIlose();
      }else if(result == "restart"){
	g.emptyBoard();
      }else if(result == "levelup"){
	reclvup(multiplier, g);
      }else if(result == "leveldown"){
	reclvdown(multiplier,g);	
      }
      cout << g << endl;
      g.clear();
      result = "";
      multi = "";
      multiplier = 0;
      counter = 0;
    }
  }else{
    //Uses only keyboard input using ncurses..Extra feature**GRAPHICS ONLY 
    initscr();
    int result;
    while ((result=getch())!= 27){
      if (result == 27) break;
      if (result == 'm'){
	g.rotate("cw");
      }else if(result == 'n'){
	g.rotate("ccw");
      }else if(result == 'w'){
	g.move('u');
      }else if(result == 's'){
	g.move('d');
      }else if(result == 'd'){
	g.move('r');
      }else if(result == 'a'){
	g.move('l');
      }else if(result == ' '){
	g.drop();
	g.clear();
	g.makeBlock();
        g.didIlose();
      }else if(result == 'r'){
	g.emptyBoard();
      }else if(result == '+'){
	g.levelup();
      }else if(result == '-'){
	g.leveldown();
      }
      g.clear();
      clear();
    }
    endwin();
  }
}

