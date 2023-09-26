#ifndef FIGURES_H
#define FIGURES_H

#include <vector>
#include <string>
#include "piece.h"

class pawn : public piece{
public:
  pawn(string color);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class rook : public piece{
public:
  rook(string color);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class knight : public piece{
public:
  knight(string color);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class bishop : public piece{
public:
  bishop(string color);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class queen : public piece{
public:
  queen(string color);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class king : public piece{
public:
  king(string color);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
  bool legal_castling (vector<piece *> chessboard, int x, int y); 
};

#endif
