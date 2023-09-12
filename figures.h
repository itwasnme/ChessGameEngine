#ifndef FIGURES_H
#define FIGURES_H

#include "piece.h"
#include <vector>
#include <string>

class pawn : public piece{
public:
  pawn(string color);
  bool legal_move(vector<piece *> chessboard, int x, int y);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class rook : public piece{
public:
  rook(string color);
  bool legal_move(vector<piece *> chessboard, int x, int y);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class knight : public piece{
public:
  knight(string color);
  bool legal_move(vector<piece *> chessboard, int x, int y);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class bishop : public piece{
public:
  bishop(string color);
  bool legal_move(vector<piece *> chessboard, int x, int y);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class queen : public piece{
public:
  queen(string color);
  bool legal_move(vector<piece *> chessboard, int x, int y);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

class king : public piece{
public:
  king(string color);
  bool legal_move(vector<piece *> chessboard, int x, int y);
  vector <int> get_all_moves(vector<piece *> chessboard, int x);
};

#endif
