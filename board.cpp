#include <windows.h>
#include <stdlib.h>
#include "board.h"
#include "figures.h"
#include <algorithm>



using namespace std;



// CONSTRUCTOR PARA ORDERNAR EL TABLERO PARA UNA NUEVA PARTIDA
board::board(){

  chessboard.push_back(new rook("black"));
  chessboard.push_back(new knight("black"));
  chessboard.push_back(new bishop("black"));
  chessboard.push_back(new queen("black"));
  chessboard.push_back(new king("black"));
  chessboard.push_back(new bishop("black"));
  chessboard.push_back(new knight("black"));
  chessboard.push_back(new rook("black"));
  for(int i = 0; i < 8; i++){
    //chessboard.push_back(new pawn("black"));
    chessboard.push_back(new piece());
  }
  for(int i = 0; i < 32; i++){
    chessboard.push_back(new piece());
  }
  for(int i = 0; i < 8; i++){
    //chessboard.push_back(new pawn("white"));
    chessboard.push_back(new piece());
  }
  chessboard.push_back(new rook("white"));
  chessboard.push_back(new knight("white"));
  chessboard.push_back(new bishop("white"));
  chessboard.push_back(new queen("white"));
  chessboard.push_back(new king("white"));
  chessboard.push_back(new bishop("white"));
  chessboard.push_back(new knight("white"));
  chessboard.push_back(new rook("white"));

  turn = true; // blancas primero
  white_king_position = 60; //Default
  black_king_position = 4; //Default

  for(int i = 0; i < 64; i++){
    if(chessboard[i] -> color == "black"){
      black_positions.push_back(i);
    }
    if(chessboard[i] -> color == "white"){
      white_positions.push_back(i);
    }
  }

}



bool board::sanitize_input(int x, int y){
  if(x > 64 || x < 0 || y > 64 || y < 0){ // Input fuera del tablero?
    invalidMove("");
    return false;
  }
  if(chessboard[x]->name == ""){ // Moviendo desde una casilla sin pieza?
    invalidMove("");
    return false;
  }
  if(chessboard[x]->color == "white" && !turn){ // Moviendo una blanca cuando no es tu turno?
    invalidMove("");
    return false;
  }
  if(chessboard[x]->color == "black" && turn){ // Moviento una negra cuando no es tu turno?
    invalidMove("");
    return false;
  }
  if(chessboard[x]->color == chessboard[y] -> color && chessboard[x] ->name != "king"){ // Moviento una pieza de un color hacia una pieza del mismo color y no es enroque?
    invalidMove("");
    return false;
  }
  return true;
}

int board::who_is_in_check(){  // returns 0 if no one, 1 if white, 2 if black.
  //Estoy en hacke? Mi movimiento tiene que evitarlo, si no, es invalido. Si no se puede, ya perdi!!!
  vector <int> moves;
  if(turn){ // Ver si las blancas estan en jaque
    for(int i = 0; i < black_positions.size(); i++){
      moves = chessboard[black_positions[i]] -> get_all_moves(chessboard, black_positions[i]);
      if(count(moves.begin(), moves.end(), white_king_position)){
        return 1;
      }
    }
  }else{
    for(int i = 0; i < white_positions.size(); i++){
      moves = chessboard[white_positions[i]] -> get_all_moves(chessboard, white_positions[i]);
      if(count(moves.begin(), moves.end(), black_king_position)) {
        return 2;
      }
    }
  }
  return 0;
}



// Revisar si un movimineto es valido, y relizarlo. Cambiar de turno.
void board::move(int x, int y){
  //Sanitize input...
  if(!sanitize_input(x,y)){
    return;
  }


  //Estoy en hacke? Mi movimiento tiene que evitarlo, si no, es invalido. Si no se puede, ya perdi!!!
  int check_status = who_is_in_check(); //0 means no one, 1 means white is in check, 2 black.
  if(check_status != 0){
    if(check_status == 1){
      cout<<"whites are on check"<<endl;
    }else if(check_status == 2){
      cout<<"blacks are on check"<<endl;
    }
  }


  /////----///---

  //if(chessboard[x] -> legal_move(x,y)){
  if( (*chessboard[x]).legal_move(chessboard,x,y)){ //Legal move only if i dont put myself in check...

    //did i move the king? update it
    if(chessboard[x] -> name == "king"){
      if(chessboard[x] -> color == "white"){
        white_king_position = y;
      }else{
        black_king_position = y;
      }
    }

    //update positions
    if(turn){
      for(int i = 0; i<white_positions.size(); i++){
        if(white_positions[i] == x){
          white_positions.erase(white_positions.begin()+i);
          white_positions.push_back(y);
          break;
        }
      }
      if(chessboard[y] -> color == "black"){
        for(int i = 0; i<black_positions.size(); i++){
          if(black_positions[i] == y){
            black_positions.erase(black_positions.begin()+i);
            break;
          }
        }
      }
    }

    else{
      for(int i = 0; i<black_positions.size(); i++){
        if(black_positions[i] == x){
          black_positions.erase(black_positions.begin()+i);
          black_positions.push_back(y);
          break;
        }
      }
      if((*chessboard[y]).color == "white"){
        for(int i = 0; i<white_positions.size(); i++){
          if(white_positions[i] == y){
            white_positions.erase(white_positions.begin()+i);
            break;
          }
        }
      }
    }


    //Actual board update (do the move)...
    delete (chessboard[y]);
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();

    //print board
    this->printBoard();

    // cambiar turno
    if(turn){
      turn = false;
    }else{
      turn = true;
    }
  }
}



//// IMPRIMIR EL TABLERO
void board::printBoard(){
  //system("cls");
  cout<<"\n"<<endl;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 16);
  for(int i = 0; i < 64; i++){

    if(i<8){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }
    }else if(i>7 && i<16){
      if( i % 2 == 0){
        if( i % 2 == 0){
          if(chessboard[i]->color=="black"){
            SetConsoleTextAttribute(hConsole, 18); //negro
          }else{
            SetConsoleTextAttribute(hConsole, 23);
          }
        }
      }else{
        if(chessboard[i]->color=="black"){
            SetConsoleTextAttribute(hConsole, 10); // azul
          }else{
            SetConsoleTextAttribute(hConsole, 15);
          }
        }
    }else if(i>15 && i<24){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }
    }else if(i>23 && i<32){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }
    }else if(i>31 && i<40){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }
    }else if(i>39 && i<48){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }
    }else if(i>47 && i<56){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }
    }else if(i>55){
      if( i % 2 == 0){
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 18); //negro
        }else{
          SetConsoleTextAttribute(hConsole, 23);
        }
      }else{
        if(chessboard[i]->color=="black"){
          SetConsoleTextAttribute(hConsole, 10); // azul
        }else{
          SetConsoleTextAttribute(hConsole, 15);
        }
      }
    }



    if(chessboard[i]->name=="pawn"){
      cout <<"   "<<(*chessboard[i]).name << "   ";
    }
    if(chessboard[i]->name=="rook"){
      cout <<"   "<<(*chessboard[i]).name << "   ";
    }
    if(chessboard[i]->name=="knight"){
      cout <<"  "<<(*chessboard[i]).name << "  ";
    }
    if(chessboard[i]->name=="bishop"){
      cout <<"  "<<(*chessboard[i]).name << "  ";
    }
    if(chessboard[i]->name=="queen"){
      cout <<"  "<<(*chessboard[i]).name << "   ";
    }
    if(chessboard[i]->name=="king"){
      cout <<"   "<<(*chessboard[i]).name << "   ";
    }
    if(chessboard[i]->name==""){
      cout <<"          ";
    }

    if ( (i+1) % 8 == 0 ){
      cout << "\n";
    }
  }
  SetConsoleTextAttribute(hConsole, 7);
  cout<<"\n"<<endl;
}

/// Imprimir error
void board::invalidMove(string error){
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 12);
  cout<<"INVALID MOVE!\n"<<endl;
  SetConsoleTextAttribute(hConsole, 7);
}
