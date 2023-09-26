#include <iostream>
#include <limits>
#include <fstream> //Testing
#include <sstream> //Testing
#include "board.h"
#include "piece.h"


using namespace std;

  /* Board Layout
  00 - 01 - 02 - 03 - 04 - 05 - 06 - 07    -> Row 1
  08 - 09 - 10 - 11 - 12 - 13 - 14 - 15
  16 - 17 - 18 - 19 - 20 - 21 - 22 - 23
  24 - 25 - 26 - 27 - 28 - 29 - 30 - 31
  32 - 33 - 34 - 35 - 36 - 37 - 38 - 39
  40 - 41 - 42 - 43 - 44 - 45 - 46 - 47
  48 - 49 - 50 - 51 - 52 - 53 - 54 - 55
  56 - 57 - 58 - 59 - 60 - 61 - 62 - 63

   |
   v
   Column 1
  */
int translate(char x, char y){
  int letter;
  int number;
  if(x == 'a' || x == 'A'){
    letter = 0;
  }else if(x == 'b' || x == 'B'){
    letter = 1;
  }else if(x == 'c' || x == 'C'){
    letter = 2;
  }else if(x == 'd' || x == 'D'){
    letter = 3;
  }else if(x == 'e' || x == 'E'){
    letter = 4;
  }else if(x == 'f' || x == 'F'){
    letter = 5;
  }else if(x == 'g' || x == 'G'){
    letter = 6;
  }else if(x == 'h' || x == 'H'){
    letter = 7;
  }else{
    letter = 200;
  }

  if(y == '1'){
    number = 7;
  }else if(y == '2'){
    number = 6;
  }else if(y == '3'){
    number = 5;
  }else if(y == '4'){
    number = 4;
  }else if(y == '5'){
    number = 3;
  }else if(y == '6'){
    number = 2;
  }else if(y == '7'){
    number = 1;
  }else if(y == '8'){
    number = 0;
  }else{
    number = 100;
  }
  return ( (number*8)+letter );
}

void testing(board *tablero){
  ifstream movesFile("testingMoves.txt");
  string line;
  int count = 1;
  if (movesFile.is_open()) {
      string from, to;
      while (getline(movesFile, line)) {
        istringstream iss(line);
        if (!(iss >> from >> to)) {
          std::cerr << "Error parsing line #" << count <<": " << line << std::endl;
          continue;
        }
        if(tablero -> turn){
          cout<<"         WHITES TURN\n"<<endl;
          cout << count << endl;
        }
        else{
          cout<<"         BLACKS TURN\n"<<endl;
          cout << count << endl;
        }
        int x = translate(from[0], from[1]);
        int y = translate(to[0], to[1]);
        tablero -> move(x, y);   
        count++;
      }
      movesFile.close();
  } else {
      std::cerr << "Unable to open the file." << std::endl;
  }
}

void menu(){
  cout << "********************" << endl;
  cout << "*     CHESS GAME    *" << endl;
  cout << "********************" << endl << endl;

  cout << "[1] Player 1 vs Player 2" << endl;
  cout << "[2] Player 1 vs AI" << endl;
  cout << "[3] How to Play" << endl;
  cout << "[4] Quit" << endl;
}

int  main(){

  while(true){

    menu();
    string option;
    while ((cin >> option)) {

      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      if(option == "1"){
        board tablero;
        string from, to;
        tablero.printBoard();
        //testing(&tablero);
        while(1){
          if(tablero.end){
            cout<<"GG!"<<endl;
            cout<<"Press Enter to return to the main menu"<<endl;
            cin.get();    // Wait for the user to press Enter
            system("cls");
            break;
          }
          if(tablero.turn){
            cout<<"         WHITES TURN\n"<<endl;
          }
          else{
            cout<<"         BLACKS TURN\n"<<endl;
          }

          cout<<"FROM: ";
          cin >> from;
          if(from == "exit"){
            system("cls");
            break;
          }
          int x = translate(from[0], from[1]);

          cout<<"TO: ";
          cin >> to;
          if(to == "exit"){
            system("cls");
            break;
          }
          int y = translate(to[0], to[1]);

          tablero.move(x, y);
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      }
      else if (option == "2"){
        system("cls");
        cout<<"Player 1 vs AI is COMING SOON!\n"<<endl;
      }
      else if (option == "3") {
        system("cls");

        cout << "Welcome to the Chess Game! To make a move, follow these steps:" << endl << endl;

        cout << "1. Type the current location of the piece you want to move." << endl;
        cout << "   - Use the format \"From: [A-H][1-8]\" (e.g., \"From: e2\")." << endl;
        cout << "   - Press Enter after typing." << endl << endl;

        cout << "2. Type the destination location where you want to move the piece." << endl;
        cout << "   - Use the format \"To: [A-H][1-8]\" (e.g., \"To: e4\")." << endl;
        cout << "   - Press Enter after typing." << endl << endl;

        cout << "3. Alternatively, you can directly input both 'From' and 'To' in the same line, separated by a space." << endl;
        cout << "   - Example: \"e2 e4\"" << endl << endl;

        cout << "Repeat steps 1 and 2 to complete your move. If you want to return to the main menu at any time," << endl;
        cout << "simply type \"exit\" when prompted in either \"From\" or \"To\" input. Typing \"exit\" will terminate" << endl;
        cout << "the current match and take you back to the main menu." << endl << endl;

        cout << "Enjoy playing chess!\n" << endl;

      }
      else if (option == "4"){
        return 0;
      }
      else{
        system("cls");   
        cout << "Invalid choice. Please enter 0, 1, 2, or 3." << endl;    
      }
      
      menu();

    }

  }

  return 0;

}
