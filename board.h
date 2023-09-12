#ifndef BOARD_H
#define BOARD_H

#include<vector>
#include "piece.h"

using namespace std;

class board{
 public:
  board(); //El contructor crea un tablero de ajedrez con las piezas en su lugar inicial.
  bool turn; //True for white turn, false for black turn.
  int white_king_position;
  int black_king_position;
  vector <int> white_positions;
  vector <int> black_positions;
  vector<piece *> chessboard;

  void move(int x, int y);
  void printBoard();
  void invalidMove(string error);
  bool sanitize_input(int x, int y);
  int who_is_in_check(); //0 means no one, 1 means white is in check, 2 black.
};
#endif
