#include <iostream>
#include <cstring>

#include "ChessBoard.h"


//================= Internal Helper Functions =====================

// prints horizontal frame of chess board
void print_frame(){
  std::cout << "   +---+---+---+---+---+---+---+---+" << '\n';
}

// returns colour of piece in 'White' or 'Black'
std::string print_colour(bool colour){
  std::string name;
  (colour)? name = "Black" : name = "White"; 
  return name;
}

// returns true if positional input is appropriate
bool check_position(const char position[2]){

  if ( !isalpha(position[0]) || !isupper(position[0]) ){
    std::cerr << position[0] << " is not a valid input character (input characters must be upper case letters A-H)!" << std::endl;
    return false;
  }

  if ( !isdigit(position[1]) ) {
    std::cerr << position[1] << " is not a valid input character (input characters must be numeric 0-7)!" << std::endl;
    return false;
  }

  int col = static_cast<int>(position[0]) - ASCII_OFFSET_A;
  int row = static_cast<int>(position[1]) - ASCII_OFFSET_0;

  if ( row < 0 || row > 7 || col < 0 || col > 7 ) {
    std::cerr << "Move " << position[0] << position [1] << " is not within board!" << std::endl;
    return false;
  }
  return true;
}

//================= ChessBoard member Functions =====================

// change turn after every valid move
void ChessBoard::change_turn(){
  (turn)? turn = false : turn = true; 
}

// prints the entire chessboard for debugging purposes
void ChessBoard::display_board() const{
  std::cout << "  ";
  for ( int i = 0; i < BOARD_LEN; i++){
    std::cout << "   " << (char) ('A' + i);
  }

  std::cout << std::endl;

  for ( int row = BOARD_LEN - 1; row >= 0; row--){
    print_frame();
    std::cout << " " << row + 1 << " ";  
    for( int col = 0; col < BOARD_LEN; col++){

      std::string name;
      if ( !board[row][col] ) name = "   ";
      else name = board[row][col]->getShortName();
      std::cout << "|" << name;
    }
    std::cout << "|" << "\n";
  }
  print_frame();
  std::cout << std::endl;
}


// initialise starting chess board
void ChessBoard::resetBoard(){
  std::cout << "A new chess game is started!\n" << std::endl;

  for ( int row = 0; row < BOARD_LEN; row++){
    for ( int col = 0; col < BOARD_LEN; col++ ){

      // calculate index
      int index = row * BOARD_LEN + col;
      
      // Set colour
      bool colour = false;  // false = white, true = black
      if ( row > BOARD_LEN / 2 ) colour = true;
     
      // Initialise empty cells
      if ( row  > 1 && row < 6 ) board[row][col] = NULL;
    
      // Initialise rook
      else if ( index == 0 || index == 7 || index == 56 || index == 63){ 
	board[row][col] = new Rook(colour, row, col);
      }

      // Initialise knight
      else if ( index == 1 || index == 6 || index == 57 || index == 62){ 
	board[row][col] = new Knight(colour, row, col);
      }

      // Initialise bishop
      else if ( index == 2 || index == 5 || index == 58 || index == 61){ 
	board[row][col] = new Bishop(colour, row, col);
      }

      // Initialise king
      else if ( index == 4 || index == 60){ 
	board[row][col] = new King(colour, row, col);
      }

      // Initialise queen
      else if ( index == 3 || index == 59){ 
	board[row][col] = new Queen(colour, row, col);
      }

      else {
	board[row][col] = new Pawn(colour, row, col);   
      }
    }
  }
}

void ChessBoard::submitMove(const char source[2], const char destination[2]){

  // check source and destination is in the right format
  if ( !check_position(source) || !check_position(destination) ) return;

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;
  
  // check if there is a piece at the starting position
  if( !board[srow][scol] ) {
    std::cout << "There is no piece at position " << source[0] << source [1]  << "!" << std::endl;
    return;
  }
  
  // check colour of piece being moved if it is the right turn
  else if ( board[srow][scol]->getColour() != turn ) {
    std::cout << "It is not " << print_colour(!turn) << "'s turn to move!" << std::endl;
    return;
  }
  
  // check if destination is occupied by the same colour as start
  else if ( board[drow][dcol] && board[drow][dcol]->getColour() == board[srow][scol]->getColour() ){
    std::cout << print_colour(turn) << "'s " <<  board[srow][scol]->getLongName() << " cannot move to " << destination[0] << destination [1]  << "!" << std::endl;
  }

  // check if it is a valid move
  else if ( board[srow][scol]->is_valid(*this, source, destination) ){

    std::cout << print_colour(turn) <<"'s " << board[srow][scol]->getLongName() << " moves from " << source[0] << source[1] << " to " << destination[0] << destination [1];

    // eliminate opponent piece if present at destination
    if ( board[drow][dcol] ) {
      std::cout << " taking " << print_colour(!turn) << "'s " << board[drow][dcol]->getLongName() << std::endl;
      delete board[drow][dcol];
      board[drow][dcol] = nullptr;
    }

    // assign new move to destination
    std::cout << std::endl;
    board[drow][dcol] = board[srow][scol];
    board[srow][scol] = nullptr;
    
    // change turn
    change_turn();

    // print board after move
    display_board();
  }

  // if it is not a valid move
  else {
    std::cout << print_colour(turn) << "'s " <<  board[srow][scol]->getLongName() << " cannot move to " << destination[0] << destination [1]  << "!" << std::endl;   
    return;
  }
  
}
