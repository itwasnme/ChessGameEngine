#include "figures.h"
#include <string>
#include <algorithm>

/* Chatgpt lololo
vector <int> coordinates(int x){
  int row = (x - 1) / 8 + 1;
  int col = (x - 1) % 8 + 1;
  return {row, col};
}
*/

vector <int> coordinates(int x){
  vector <int> coordinates;

  //Enconrar en que row esta...
  if(x<=7){
    coordinates.push_back(1);
  }else if(x<=15){
    coordinates.push_back(2);
  }else if(x<=23){
    coordinates.push_back(3);
  }else if(x<=31){
    coordinates.push_back(4);
  }else if(x<=39){
    coordinates.push_back(5);
  }else if(x<=47){
    coordinates.push_back(6);
  }else if(x<=55){
    coordinates.push_back(7);
  }else if(x<=63){
    coordinates.push_back(8);
  }

  //Encontrar en que columna esta...
  if(x==0){ //Column 1
    coordinates.push_back(1);
  }else if((x+0) % 8 == 0){ //Column 1
    coordinates.push_back(1);
  }else if((x+7) % 8 == 0){
    coordinates.push_back(2);
  }else if((x+6) % 8 == 0){
    coordinates.push_back(3);
  }else if((x+5) % 8 == 0){
    coordinates.push_back(4);
  }else if((x+4) % 8 == 0){
    coordinates.push_back(5);
  }else if((x+3) % 8 == 0){
    coordinates.push_back(6);
  }else if((x+2) % 8 == 0){
    coordinates.push_back(7);
  }else if((x+1) % 8 == 0){ //Column 8
    coordinates.push_back(8);
  }

  return coordinates;
} //[row,col]



//PAWNS
pawn::pawn(string color){
  this -> name = "pawn";
  this -> color = color;
}

vector <int> pawn::get_all_moves(vector<piece *> chessboard, int x){
  //BUG CUANDO ESTA POR LLEGA AL OTRO LADO DEL TABLERO (SEG FAULT AL ACCEDER VECTOR)

  vector <int> moves;
  if(chessboard[x] -> color == "white"){

    if(chessboard[x-7] -> color == "black" && (x+1) % 8 != 0){ //Peon puede comer diagonal derecha?
      moves.push_back(x-7);
    }

    if(chessboard[x-9] -> color == "black" && (x) % 8 != 0){ //Peon puede comer diagonal izquierda?
      moves.push_back(x-9);
    }

    if(chessboard[x-8] -> name == ""){ //Peon puede avanza 1 hacia adelante?
      moves.push_back(x-8);
      if(48 <= x && x <= 55 && chessboard[x-16] -> name ==""){ //Ver si esta en la linea de inicio
        moves.push_back(x-16); // Peon puede avanzar 2 hacia adelante...
      }
    }
  }
  //Peon negro
  if(chessboard[x]->color == "black"){
    if(chessboard[x+9] -> color == "white" && (x+1) % 8 != 0){ //Peon puede comer diagonal derecha?
      moves.push_back(x+9);
    }

    if(chessboard[x+7] -> color == "white" && (x) % 8 != 0){ //Peon puede comer diagonal izquierda?
      moves.push_back(x+7);
    }

    if(chessboard[x+8] -> name == ""){ //Peon puede avanza 1 hacia adelante?
      moves.push_back(x+8);
      if(8 <= x && x <= 15 && chessboard[x+16] -> name ==""){ //Ver si esta en la linea de inicio
        moves.push_back(x+16); // Peon puede avanzar 2 hacia adelante...
      }
    }
  }
  return moves;
}

bool pawn::legal_move(vector<piece *> chessboard, int x, int y){
  vector <int> moves = get_all_moves(chessboard, x); //Vector to store possible moves based on the piece selected by the player

  if(count(moves.begin(), moves.end(), y)) {
    return true;
  }else{
    for(int i=0; i<moves.size();i++){
      cout<<moves[i]<<" ";
    }
    cout<<"\n"<<endl;
    return false;
  }
}


//ROOCK
rook::rook(string color){
  this -> name = "rook";
  this -> color = color;
}

vector <int> rook::get_all_moves(vector<piece *> chessboard, int x){
  vector <int> moves = coordinates(x);
  int row = moves[0];
  int col = moves[1];

    //Encontrar el numero de casillas que hay horizontal y verticalmente en base a la posicion (row,col)...
  int abajo = 8 - row;
  int arriba = 7 - abajo;

  int derecha = 8 - col;
  int izquierda = 7 - derecha;

  moves.clear();
  //cuanto hacia adelante, atras, izquierda, y derecha?

  for(int i = 0; i < abajo; i++){
    if(chessboard[x+(8*(i+1))]->name == ""){
      moves.push_back(x+(8*(i+1)));
    }else if(chessboard[x+(8*(i+1))]->color != chessboard[x]-> color){
      moves.push_back(x+(8*(i+1)));
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < arriba; i++){
    if(chessboard[x-(8*(i+1))]->name == ""){
      moves.push_back(x-(8*(i+1)));
    }else if(chessboard[x-(8*(i+1))]->color != chessboard[x]-> color){
      moves.push_back(x-(8*(i+1)));
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < derecha; i++){
    if(chessboard[x+(i+1)]->name == ""){
      moves.push_back(x+(i+1));
    }else if(chessboard[x+(i+1)]->color != chessboard[x]-> color){
      moves.push_back(x+(i+1));
      break;
    }else{
      break;
    }
  }


  for(int i = 0; i < izquierda; i++){
    if(chessboard[x-(i+1)]->name == ""){
      moves.push_back(x-(i+1));
    }else if(chessboard[x-(i+1)]->color != chessboard[x]-> color){
      moves.push_back(x-(i+1));
      break;
    }else{
      break;
    }
  }
  return moves;
}

bool rook::legal_move(vector<piece *> chessboard, int x, int y){

  vector <int> moves = get_all_moves(chessboard, x);

  if(count(moves.begin(), moves.end(), y)) {
    return true;
  }else{
    for(int i=0; i<moves.size();i++){
      cout<<moves[i]<<" ";
    }
    cout<<"\n"<<endl;
    return false;
  }
}


//KNIGHT
knight::knight(string color){
  this -> name = "knight";
  this -> color = color;
}

vector <int> knight::get_all_moves(vector<piece *> chessboard, int x){

  vector <int> temp;
  vector <int> moves = coordinates(x);
  int row = moves[0];
  int col = moves[1];

  moves.clear();

  // MAX of 8 possible jumps...

  int daud = x-15; //Si existe, tiene que estar dos rows sobre, 1  col a la derecha.
  if( (daud > 0) && (daud < 64) && (chessboard[daud]->color != chessboard[x]->color) ){
    temp = coordinates(daud);
    if(row - 2 == temp[0] && col + 1 == temp[1]){
      moves.push_back(daud);
    }
    temp.clear();
  }

  int daui = x-17; //Si existe, tiene que estar dos rows sobre, 1 col a la izquierda
  if(daui > 0 && daui < 64 && chessboard[daui]->color != chessboard[x]->color){
    temp = coordinates(daui);
    if(row - 2 == temp[0] && col - 1 == temp[1]){
      moves.push_back(daui);
    }
    temp.clear();
  }

  int uadd = x-6; //Si existe, tiene que estar una row sobre, dos col a la derecha
  if(uadd > 0 && uadd < 64 && chessboard[uadd]->color != chessboard[x]->color){
    temp = coordinates(uadd);
    if(row - 1 == temp[0] && col + 2 == temp[1]){
      moves.push_back(uadd);
    }
    temp.clear();
  }

  int uadi = x-10; //Si existe, tiene que estar una row sobre, dos col a la izquierda
  if(uadi > 0 && uadi < 64 && chessboard[uadi]->color != chessboard[x]->color){
    temp = coordinates(uadi);
    if(row - 1 == temp[0] && col - 2 == temp[1]){
      moves.push_back(uadi);
    }
    temp.clear();
  }

  int ddud = x+17; //Si existe, tiene que estar dos rows abajp, una col a la derecha
  if(ddud > 0 && ddud < 64 && chessboard[ddud]->color != chessboard[x]->color){
    temp = coordinates(ddud);
    if(row + 2 == temp[0] && col + 1 == temp[1]){
      moves.push_back(ddud);
    }
    temp.clear();
  }

  int ddui = x+15; //Si existe, tiene que estar dos rows abajo, una col a la izquierda
  if(ddui > 0 && ddui < 64 && chessboard[ddui]->color != chessboard[x]->color){
    temp = coordinates(ddui);
    if(row + 2 == temp[0] && col - 1 == temp[1]){
      moves.push_back(ddui);
    }
    temp.clear();
  }

  int uddd = x+10; //Si existe, tiene que estar una rows abajp, dos col a la derecha
  if(uddd > 0 && uddd < 64 && chessboard[uddd]->color != chessboard[x]->color){
    temp = coordinates(uddd);
    if(row + 1 == temp[0] && col + 2 == temp[1]){
      moves.push_back(uddd);
    }
    temp.clear();
  }

  int uddi = x+6; //Si existe, tiene que estar una rows abajo, dos col a la izquierda
  if(uddi > 0 && uddi < 64 && chessboard[uddi]->color != chessboard[x]->color){
    temp = coordinates(uddi);
    if(row + 1 == temp[0] && col - 2 == temp[1]){
      moves.push_back(uddi);
    }
    temp.clear();
  }

  return moves;
}


bool knight::legal_move(vector<piece *> chessboard, int x, int y){
  vector <int> moves = get_all_moves(chessboard, x);
  if(count(moves.begin(), moves.end(), y)) {
    return true;
  }else{
    for(int i=0; i<moves.size();i++){
      cout<<moves[i]<<" ";
    }
    cout<<"\n"<<endl;
    return false;
  }
}

/////////////////////////////////////////////////////////////// BISHOP
bishop::bishop(string color){
  this -> name = "bishop";
  this -> color = color;
}

vector <int> bishop::get_all_moves(vector<piece *> chessboard, int x){

  vector <int> moves = coordinates(x);
  int row = moves[0];
  int col = moves[1];
    //Enconrar en que row esta...
  int abajo = 8 - row;
  int arriba = 7 - abajo;
  int derecha = 8 - col;
  int izquierda = 7 - derecha;
  int upr;
  int upl;
  int dor;
  int dol;
  moves.clear();

  if(arriba<=derecha){
    upr = arriba;
  }else{
    upr = derecha;
  }

  if(arriba<=izquierda){
    upl = arriba;
  }else{
    upl = izquierda;
  }

  if(abajo<=derecha){
    dor = abajo;
  }else{
    dor = derecha;
  }

  if(abajo<=izquierda){
    dol = abajo;
  }else{
    dol = izquierda;
  }

  for(int i = 0; i < upr; i++){
    if(chessboard[ (x - ( 8*(i+1) )) + (i+1) ] -> name == ""){
      moves.push_back( (x - ( 8*(i+1) )) + (i+1) );
    }else if(chessboard[ (x - ( 8*(i+1) )) + (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x - ( 8*(i+1) )) + (i+1) );
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < upl; i++){
    if(chessboard[ (x - ( 8*(i+1) )) - (i+1) ] -> name == ""){
      moves.push_back( (x - ( 8*(i+1) )) - (i+1) );
    }else if(chessboard[ (x - ( 8*(i+1) )) - (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x - ( 8*(i+1) )) - (i+1) );
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < dor; i++){
    if(chessboard[ (x + ( 8*(i+1) )) + (i+1) ] -> name == ""){
      moves.push_back( (x + ( 8*(i+1) )) + (i+1) );
    }else if(chessboard[ (x + ( 8*(i+1) )) + (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x + ( 8*(i+1) )) + (i+1) );
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < dol; i++){
    if(chessboard[ (x + ( 8*(i+1) )) - (i+1) ] -> name == ""){
      moves.push_back( (x + ( 8*(i+1) )) - (i+1) );
    }else if(chessboard[ (x + ( 8*(i+1) )) - (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x + ( 8*(i+1) )) - (i+1) );
      break;
    }else{
      break;
    }
  }

  return moves;
}

bool bishop::legal_move(vector<piece *> chessboard, int x, int y){
  vector <int> moves = get_all_moves(chessboard, x);

  if(count(moves.begin(), moves.end(), y)) {
    return true;
  }else{
    for(int i=0; i<moves.size();i++){
      cout<<moves[i]<<" ";
    }
    cout<<"\n"<<endl;
    return false;
  }

}


/////////////////////////////////////////////////////////////// QUEEN
queen::queen(string color){
  this -> name = "queen";
  this -> color = color;
}

vector <int> queen::get_all_moves(vector<piece *> chessboard, int x){
  vector <int> moves = coordinates(x);
  int row = moves[0];
  int col = moves[1];
    //Enconrar en que row esta...
  int abajo = 8 - row;
  int arriba = 7 - abajo;
  int derecha = 8 - col;
  int izquierda = 7 - derecha;
  int upr;
  int upl;
  int dor;
  int dol;
  moves.clear();

  for(int i = 0; i < abajo; i++){
    if(chessboard[x+(8*(i+1))]->name == ""){
      moves.push_back(x+(8*(i+1)));
    }else if(chessboard[x+(8*(i+1))]->color != chessboard[x]-> color){
      moves.push_back(x+(8*(i+1)));
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < arriba; i++){
    if(chessboard[x-(8*(i+1))]->name == ""){
      moves.push_back(x-(8*(i+1)));
    }else if(chessboard[x-(8*(i+1))]->color != chessboard[x]-> color){
      moves.push_back(x-(8*(i+1)));
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < derecha; i++){
    if(chessboard[x+(i+1)]->name == ""){
      moves.push_back(x+(i+1));
    }else if(chessboard[x+(i+1)]->color != chessboard[x]-> color){
      moves.push_back(x+(i+1));
      break;
    }else{
      break;
    }
  }


  for(int i = 0; i < izquierda; i++){
    if(chessboard[x-(i+1)]->name == ""){
      moves.push_back(x-(i+1));
    }else if(chessboard[x-(i+1)]->color != chessboard[x]-> color){
      moves.push_back(x-(i+1));
      break;
    }else{
      break;
    }
  }

  if(arriba<=derecha){
    upr = arriba;
  }else{
    upr = derecha;
  }

  if(arriba<=izquierda){
    upl = arriba;
  }else{
    upl = izquierda;
  }

  if(abajo<=derecha){
    dor = abajo;
  }else{
    dor = derecha;
  }

  if(abajo<=izquierda){
    dol = abajo;
  }else{
    dol = izquierda;
  }

  for(int i = 0; i < upr; i++){
    if(chessboard[ (x - ( 8*(i+1) )) + (i+1) ] -> name == ""){
      moves.push_back( (x - ( 8*(i+1) )) + (i+1) );
    }else if(chessboard[ (x - ( 8*(i+1) )) + (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x - ( 8*(i+1) )) + (i+1) );
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < upl; i++){
    if(chessboard[ (x - ( 8*(i+1) )) - (i+1) ] -> name == ""){
      moves.push_back( (x - ( 8*(i+1) )) - (i+1) );
    }else if(chessboard[ (x - ( 8*(i+1) )) - (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x - ( 8*(i+1) )) - (i+1) );
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < dor; i++){
    if(chessboard[ (x + ( 8*(i+1) )) + (i+1) ] -> name == ""){
      moves.push_back( (x + ( 8*(i+1) )) + (i+1) );
    }else if(chessboard[ (x + ( 8*(i+1) )) + (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x + ( 8*(i+1) )) + (i+1) );
      break;
    }else{
      break;
    }
  }

  for(int i = 0; i < dol; i++){
    if(chessboard[ (x + ( 8*(i+1) )) - (i+1) ] -> name == ""){
      moves.push_back( (x + ( 8*(i+1) )) - (i+1) );
    }else if(chessboard[ (x + ( 8*(i+1) )) - (i+1) ] -> color != chessboard[x] -> color){
      moves.push_back( (x + ( 8*(i+1) )) - (i+1) );
      break;
    }else{
      break;
    }
  }

  return moves;
  }

bool queen::legal_move(vector<piece *> chessboard, int x, int y){
  vector <int> moves = get_all_moves(chessboard, x);

  if(count(moves.begin(), moves.end(), y)) {
    return true;
  }else{
    for(int i=0; i<moves.size();i++){
      cout<<moves[i]<<" ";
    }
    cout<<"\n"<<endl;
    return false;
  }
}


/////////////////////////////////////////////////////////////// KING
king::king(string color){
  this -> name = "king";
  this -> color = color;
}

vector <int> king::get_all_moves(vector<piece *> chessboard, int x){
  vector <int> moves = coordinates(x);
  int row = moves[0];
  int col = moves[1];
    //Enconrar en que row esta...
  int abajo = 8 - row;
  int arriba = 7 - abajo;
  int derecha = 8 - col;
  int izquierda = 7 - derecha;

  moves.clear();

  if(abajo > 0){
    if(chessboard[x+8] -> color != chessboard[x] -> color){
      moves.push_back(x+8);
    }
  }

  if(arriba > 0){
    if(chessboard[x-8] -> color != chessboard[x] -> color){
      moves.push_back(x-8);
    }
  }

  if(derecha > 0){
    if(chessboard[x+1] -> color != chessboard[x] -> color){
      moves.push_back(x+1);
    }
  }

  if(izquierda > 0){
    if(chessboard[x-1] -> color != chessboard[x] -> color){
      moves.push_back(x-1);
    }
  }

  if(abajo > 0 && derecha > 0){ //puede ir diagonal abajo-izquierda
    if(chessboard[x+7] -> color != chessboard[x] -> color){
      moves.push_back(x+7);
    }
  }

  if(abajo > 0 && izquierda > 0){ // pudede ir diagonal abajo-derecha
    if(chessboard[x+9] -> color != chessboard[x] -> color){
      moves.push_back(x+9);
    }
  }

  if(arriba > 0 && derecha > 0){ //puede ir diagonal arriba-izquierda
    if(chessboard[x-9] -> color != chessboard[x] -> color){
      moves.push_back(x-9);
    }
  }

  if(arriba > 0 && izquierda > 0){ // pudede ir diagonal arriba-derecha
    if(chessboard[x-7] -> color != chessboard[x] -> color){
      moves.push_back(x-7);
    }
  }
  return moves;
}

bool king::legal_move(vector<piece *> chessboard, int x, int y){
  vector <int> moves = get_all_moves(chessboard, x);

  if(count(moves.begin(), moves.end(), y)) {
    return true;
  }else{
    for(int i=0; i<moves.size();i++){
      cout<<moves[i]<<" ";
    }
    cout<<"\n"<<endl;
    return false;
  }
}


///////////////////////////////////////////////////////////////
