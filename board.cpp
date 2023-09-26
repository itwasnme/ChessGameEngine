#include <windows.h>
#include <stdlib.h>
#include <algorithm>
#include "board.h"
#include "figures.h"

using namespace std;


// Initialize the chessboard and variables for a new match
board::board(){

  // Initialize the chessboard with pieces for a new game...
  
  chessboard.push_back(new rook("black"));
  chessboard.push_back(new knight("black"));
  chessboard.push_back(new bishop("black"));
  chessboard.push_back(new queen("black"));
  chessboard.push_back(new king("black"));
  chessboard.push_back(new bishop("black"));
  chessboard.push_back(new knight("black"));
  chessboard.push_back(new rook("black"));
  for(int i = 0; i < 8; i++){
    chessboard.push_back(new pawn("black"));
  }
  
  for(int i = 0; i < 32; i++){
    chessboard.push_back(new piece());
  }
  for(int i = 0; i < 8; i++){
    chessboard.push_back(new pawn("white"));
  }
  chessboard.push_back(new rook("white"));
  chessboard.push_back(new knight("white"));
  chessboard.push_back(new bishop("white"));
  chessboard.push_back(new queen("white"));
  chessboard.push_back(new king("white"));
  chessboard.push_back(new bishop("white"));
  chessboard.push_back(new knight("white"));
  chessboard.push_back(new rook("white"));

  // A boolean variable to track the current player's turn (true for whites, false for blacks)
  turn = true;

  // Initialize the position of the white king at the start of the game
  white_king_position = 60;

  // Initialize the position of the black king at the start of the game
  black_king_position = 4;

  // Initialize a tracker for white's piece positions
  for(int i = 0; i < 16; i++){
    black_positions.push_back(i);
  }

  // Initialize a tracker for black's piece positions
  for(int i = 48; i < 64; i++){
    white_positions.push_back(i);
  } 

  // Initialize flag to keep track of check status 
  in_check = false;

  // Initialize flag to keep track of gameover
  end = false;

}

// Verify the validity of the 'from' and 'to' coordinates before making a move
bool board::sanitize_input(int x, int y){

  // Verify if the input coordinates are within the valid range (0 to 63)
  if(x > 63 || x < 0 || y > 63 || y < 0){ 
    invalidMove("Invalid input coordinates. Coordinates must be in the range 0 to 63.");
    return false;
  }

  // Ensure the user is trying to move from a non-empty position
  if(chessboard[x]->name == ""){ 
    invalidMove("Invalid move. You are trying to move from an empty position.");
    return false;
  }

  // Verify that the user is attempting to move a piece of their own color (whites)
  if(chessboard[x]->color == "white" && !turn){
    invalidMove("Invalid move. You cannot move an opponent's piece during your turn.");
    return false;
  }

  // Verify that the user is attempting to move a piece of their own color (blacks)
  if(chessboard[x]->color == "black" && turn){ 
    invalidMove("Invalid move. You cannot move an opponent's piece during your turn.");
    return false;
  }

  // Ensuring that the user is not moving their own color's piece onto a square occupied by their own color (except for castling TODO)
  if(chessboard[x]->color == chessboard[y] -> color && chessboard[x] ->name != "king"){ 
    invalidMove("Invalid move. You cannot move your own piece to a square occupied by your own color.");
    return false;
  }

  // Passes basic sanitation checks
  return true;

}
 
// Returns 0 if there's no check, 1 if it's white's turn and they are in check, and 2 if it's black's turn and they are in check.
int board::who_is_in_check(){ 

  // Get updated list with current positions for both whites and blacks pieces, and their kings positions.
  vector <int> temp_white_positions;
  vector <int> temp_black_positions;
  int temp_white_king_position;
  int temp_black_king_position;
  for(int i = 0; i<64; i++){
    if(chessboard[i]->color == "black"){
      temp_black_positions.push_back(i);
      if(chessboard[i]->name == "king"){
        temp_black_king_position = i;
      }
    }
    if(chessboard[i]->color == "white"){
      temp_white_positions.push_back(i);
      if(chessboard[i]->name == "king"){
        temp_white_king_position = i;
      }
    }
  }

  vector <int> moves;

  // Check if, during white's turn, their king is in check.
  if(turn){ 
    for(int i = 0; i < temp_black_positions.size(); i++){
      moves = chessboard[temp_black_positions[i]] -> get_all_moves(chessboard, temp_black_positions[i]);
      if(count(moves.begin(), moves.end(), temp_white_king_position)){
        return 1;
      }
    }
  // Check if, during black's turn, their king is in check.
  }else{
    for(int i = 0; i < temp_white_positions.size(); i++){
      moves = chessboard[temp_white_positions[i]] -> get_all_moves(chessboard, temp_white_positions[i]);
      if(count(moves.begin(), moves.end(), temp_black_king_position)) {
        return 2;
      }
    }
  }
  return 0;

}

// Castling
void board::castling(int x, int y){
  // Before reaching this point, we've already confirmed that castling is valid
  // by calling legal_move, ensuring that:
  // 1) The king wasn't in check before, during, and after castling,
  // 2) The king and rook are in the correct positions, and
  // 3) Neither the king nor the rook has moved previously.
  
  // Update the "touched" status for the king
  chessboard[x] -> touched = true;

  // Update positions vector, king position variable, "touched" status for the rook,
  // and perform the move on the board; there are four possible scenarios.
  if(y == 2){
    for(int i = 0; i<black_positions.size(); i++){
      if(black_positions[i] == 0){ //Rook update
        black_positions[i] = 3;
      }
      if(black_positions[i] == 4){ //King update
        black_positions[i] = 2;
      }      
    }
    black_king_position = 2;

    delete (chessboard[y]);
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();
    delete (chessboard[3]);
    chessboard[3] = chessboard[0];
    chessboard[0] = new piece();
    chessboard[3] -> touched == true;

  }else if(y == 6){
    for(int i = 0; i<black_positions.size(); i++){
      if(black_positions[i] == 7){ //Rook update
        black_positions[i] = 5;
      }
      if(black_positions[i] == 4){ //King update
        black_positions[i] = 6;
      }      
    }
    black_king_position = 6;

    delete (chessboard[y]);
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();
    delete (chessboard[5]);
    chessboard[5] = chessboard[7];
    chessboard[7] = new piece();
    chessboard[5] -> touched == true;

  }else if(y == 58){
    for(int i = 0; i<white_positions.size(); i++){
      if(white_positions[i] == 56){ //Rook update
        white_positions[i] = 59;
      }
      if(white_positions[i] == 60){ //King update
        white_positions[i] = 58;
      }
    }
    white_king_position = 58;

    delete (chessboard[y]);
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();
    delete (chessboard[59]);
    chessboard[59] = chessboard[56];
    chessboard[56] = new piece();
    chessboard[59] -> touched == true;

  }else if(y == 62){
    for(int i = 0; i<white_positions.size(); i++){
      if(white_positions[i] == 63){ //Rook update
        white_positions[i] = 61;
      }
      if(white_positions[i] == 60){ //King update
        white_positions[i] = 62;
      }
    }
    white_king_position = 62;

    delete (chessboard[y]);
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();
    delete (chessboard[61]);
    chessboard[61] = chessboard[63];
    chessboard[63] = new piece();
    chessboard[61] -> touched == true;

  }else{
    invalidMove("Something is wrong with castling implementation");
  }

  // Print the updated chessboard
  this->printBoard();

  // Switch the player's turn
  if(turn){
    turn = false;
  }else{
    turn = true;
  }

  // Inform players if their king is in check before they choose their next move
  int check_status = who_is_in_check();
  if(check_status != 0){
    if(check_status == 1){
      if(checkmate()){ //TODO
        cout<<"White's king is in checkmate. You lose!"<<endl;
        end = true;
      }else{
        in_check = true;
        cout<<"White's king is in check."<<endl;
      }
    }else if(check_status == 2){
      if(checkmate()){ //TODO
        cout<<"Black's king is in checkmate. You lose!"<<endl;
        end = true;
      }else{
        in_check = true;
        cout<<"Black's king is in check."<<endl;
      }
    }
  }

  return;
}

// Check if a movement is valid. If it is, update the board and change the turn.
void board::move(int x, int y){

  // First checkpoint: Sanitize input
  if(!sanitize_input(x,y)){
    return;
  }

  // -> TODO: Castling implementation elsewhere and return...
  if(chessboard[x] -> name == "king" && chessboard[x] -> color == "white" && x == 60 && (y == 62 || y == 58)){
    if(in_check){
      invalidMove("You cannot perform castling when your king is in check");
      return;
    }
    king* temp = dynamic_cast<king*>(chessboard[x]);
    if(temp->legal_castling(chessboard,x,y)){
      castling(x,y);
    }else{
      invalidMove("Your " + chessboard[x] -> name + " can't be moved to position " + to_string(y));
    }
    return;
  }
  if(chessboard[x] -> name == "king" && chessboard[x] -> color == "black" && x == 4 && (y == 6 || y == 2)){
    if(in_check){
      invalidMove("You cannot perform castling when your king is in check");
      return;
    }    
    king* temp = dynamic_cast<king*>(chessboard[x]);
    if(temp->legal_castling(chessboard,x,y)){
      castling(x,y);
    }else{
      invalidMove("Your " + chessboard[x] -> name + " can't be moved to position " + to_string(y));
    }
    return;
  }

  // Second checkpoint: Check if the selected piece can make the intended move based on the current board status
  if( !(*chessboard[x]).legal_move(chessboard,x,y) ){
    invalidMove("Your " + chessboard[x] -> name + " can't be moved to position " + to_string(y));
    return;
  }

  // Third checkpoint: Check if the current player's king is in check; if their attempted move prevents it set the in_check flag to false and continue.
  // If check is not prevened, they must select another move.
  if(in_check){

    //Temporarily update board
    piece * temp = chessboard[y];
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();

    int check_status = who_is_in_check();
    if(check_status != 0){
      invalidMove("You are in check, your move must prevent it!");
      delete (chessboard[x]);
      chessboard[x] = chessboard[y];
      chessboard[y] = temp;
      return;
    }else{
      delete (chessboard[x]);
      chessboard[x] = chessboard[y];
      chessboard[y] = temp;
      in_check = false;
    }

  }
  
  // Check if the proposed move results in a checkmate position
  if(!in_check){
    //Temporarily update board
    piece * temp = chessboard[y];
    chessboard[y] = chessboard[x];
    chessboard[x] = new piece();
    //Check if the person who just moved put themself in checkmate
    int check_status = who_is_in_check();
    if(check_status == 1){
      invalidMove("Warning whites: Moving there would lead to a checkmate!");
      //Revert
      delete (chessboard[x]);
      chessboard[x] = chessboard[y];
      chessboard[y] = temp;
      return;
    }
    if(check_status == 2){
      invalidMove("Warning blacks: Moving there would lead to a checkmate!");
      //Revert
      delete (chessboard[x]);
      chessboard[x] = chessboard[y];
      chessboard[y] = temp;     
      return;
    }
    //Revert
    delete (chessboard[x]);
    chessboard[x] = chessboard[y];
    chessboard[y] = temp;
  }

  // Update the position lists for both black and white pieces 
  if(turn){
    // Update the white piece positions
    for(int i = 0; i<white_positions.size(); i++){
      if(white_positions[i] == x){
        white_positions[i] = y;
        break;
      }
    }
    // Check if the destination square has a black piece and update the black piece positions
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
    // Update the black piece positions
    for(int i = 0; i<black_positions.size(); i++){
      if(black_positions[i] == x){
        black_positions[i] = y;
        break;
      }
    }
    // Check if the destination square has a white piece and update the white piece positions
    if((*chessboard[y]).color == "white"){
      for(int i = 0; i<white_positions.size(); i++){
        if(white_positions[i] == y){
          white_positions.erase(white_positions.begin()+i);
          break;
        }
      }
    }
  }

  // Update the king's position if it's a king piece. For castling, update king's touched variable here.
  if(chessboard[x] -> name == "king"){
    chessboard[x] -> touched = true;
    if(chessboard[x] -> color == "white"){
      white_king_position = y;
    }else{
      black_king_position = y;
    }
  }

  // For castling, update rook's touched variable here.
  if(chessboard[x] -> name == "rook"){
    chessboard[x] -> touched = true;
  }

  // Update the chessboard with the move (perform the move)... 
  delete (chessboard[y]);
  chessboard[y] = chessboard[x];
  chessboard[x] = new piece();

  // Check for pawn promotion
  if(turn && y<8 && chessboard[y]->name=="pawn" || !turn && y>55 && chessboard[y]->name=="pawn"){
    while(true){
      cout<<"Choose promotion: [0] Queen    [1] Rook    [2] Knight    [3] Bishop  "<<endl;
      string option;
      cin>>option;
      if(option == "0"){
        if(turn){
          delete (chessboard[y]);
          chessboard[y] = new queen("white");
          break;
        }
        else{
          delete (chessboard[y]);
          chessboard[y] = new queen("black");
          break;
        }
      }
      if(option == "1"){
        if(turn){
          delete (chessboard[y]);
          chessboard[y] = new rook("white");
          break;
        }
        else{
          delete (chessboard[y]);
          chessboard[y] = new rook("black");
          break;
        }
      }
      if(option == "2"){
        if(turn){
          delete (chessboard[y]);
          chessboard[y] = new knight("white");
          break;
        }
        else{
          delete (chessboard[y]);
          chessboard[y] = new knight("black");
          break;
        }
      }
      if(option == "3"){
        if(turn){
          delete (chessboard[y]);
          chessboard[y] = new bishop("white");
          break;
        }
        else{
          delete (chessboard[y]);
          chessboard[y] = new bishop("black");
          break;
        }
      }
    }
  }

  // Print the updated chessboard
  this->printBoard();

  // Switch the player's turn
  if(turn){
    turn = false;
  }else{
    turn = true;
  }

  // Inform players if their king is in check before they choose their next move
  int check_status = who_is_in_check();
  if(check_status != 0){
    if(check_status == 1){
      if(checkmate()){ //TODO
        cout<<"White's king is in checkmate. You lose!"<<endl;
        end = true;
      }else{
        in_check = true;
        cout<<"White's king is in check."<<endl;
      }
    }else if(check_status == 2){
      if(checkmate()){ //TODO
        cout<<"Black's king is in checkmate. You lose!"<<endl;
        end = true;
      }else{
        in_check = true;
        cout<<"Black's king is in check."<<endl;
      }
    }
  }

}

// Checking the checkmate status (called after a player's move results in a check on their opponent)
bool board::checkmate(){
  if(turn){
    for(int i = 0; i < white_positions.size(); i++){ //For all positions currently occupied by white pieces
      vector <int> moves = chessboard[white_positions[i]]->get_all_moves(chessboard, white_positions[i]); //Get list with their possible moves from their current position
      for(int j = 0; j < moves.size(); j++){ //And for all their possible moves from their current position
        piece * temp = chessboard[moves[j]]; //Update the board as if the move was done
        chessboard[moves[j]] = chessboard[white_positions[i]];
        chessboard[white_positions[i]] = new piece();
        int check_status = who_is_in_check(); //Call check_status to see if performing the previous move would revert the check
        if(check_status != 1){ //If not 1, whites are no longer in check, and there is not checkmate yet.
          delete (chessboard[white_positions[i]]); //Revert board to original configuration
          chessboard[white_positions[i]] = chessboard[moves[j]];
          chessboard[moves[j]] = temp;
          return false; //Return false
        }else if (check_status == 1){ //If 1, whites are still in check
          delete (chessboard[white_positions[i]]); //Revert board to original configuration and continue the loop...
          chessboard[white_positions[i]] = chessboard[moves[j]];
          chessboard[moves[j]] = temp;
        }else{
          cout<<"LOGIC ERROR!"<<endl;
        }
      }
    }
  }else{
    for(int i = 0; i < black_positions.size(); i++){ //For all positions currently occupied by black pieces
      vector <int> moves = chessboard[black_positions[i]]->get_all_moves(chessboard, black_positions[i]); //Get list with their possible moves from their current position
      for(int j = 0; j < moves.size(); j++){ //And for all their possible moves from their current position
        piece * temp = chessboard[moves[j]]; //Update the board as if the move was done
        chessboard[moves[j]] = chessboard[black_positions[i]];
        chessboard[black_positions[i]] = new piece();
        int check_status = who_is_in_check(); //Call check_status to see if performing the previous move would revert the check
        if(check_status != 2){ //If not 2, blacks are no longer in check, and there is not checkmate yet.
          delete (chessboard[black_positions[i]]); //Revert board to original configuration
          chessboard[black_positions[i]] = chessboard[moves[j]];
          chessboard[moves[j]] = temp;
          return false; //Return false
        }else if (check_status == 2){ //If 2, blacks are still in check
          delete (chessboard[black_positions[i]]); //Revert board to original configuration and continue the loop...
          chessboard[black_positions[i]] = chessboard[moves[j]];
          chessboard[moves[j]] = temp;
        }else{
          cout<<"LOGIC ERROR!"<<endl;
        }
      }
    }
  }
  
  return true;
}

// Display the chessboard on the console (for Windows OS only)
void board::printBoard(){
  system("cls"); //https://cplusplus.com/articles/j3wTURfi/
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


    //MAP//
    if(i==7){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   8"; 
    }
    if(i==15){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   7"; 
    }
    if(i==23){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   6"; 
    }
    if(i==31){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   5"; 
    }
    if(i==39){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   4"; 
    }
    if(i==47){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   3"; 
    }
    if(i==55){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   2"; 
    }
    if(i==63){
      SetConsoleTextAttribute(hConsole, 7);
      cout<<"   1"; 
    }                            
    //MAP-END//

    if ( (i+1) % 8 == 0 ){
      cout << "\n";
    }

  }
  SetConsoleTextAttribute(hConsole, 7);
  cout<<"\n    A          B         C         D         E         F         G         H         \n"<<endl;
}

// Display an error message
void board::invalidMove(string error){
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 12);
  if(error.empty()){
    cout<<"INVALID MOVE!\n"<<endl;
  }else{
    cout<< error + "\n" <<endl;
  }
  SetConsoleTextAttribute(hConsole, 7);
}
