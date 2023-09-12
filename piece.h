#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class piece{

public:
  string name = "";
  string color = "";
  virtual bool legal_move (vector<piece *> chessboard, int x, int y); 
  virtual vector <int> get_all_moves(vector<piece *> chessboard, int x);
};
#endif
