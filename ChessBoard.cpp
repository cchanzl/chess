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

// returns an integer equal to the index in the chesspiece array
int board_index(const char source[2]){
  int col = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int row = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  return row * BOARD_LEN + col;
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
      else if ( index == 3 || index == 59){ 
	board[row][col] = new King(colour, row, col);
      }

      // Initialise queen
      else if ( index == 4 || index == 60){ 
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
  // ...

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;
  
  // check if there is a piece at that position
  if( !board[srow][scol] ) {
    std::cout << "There is no piece at position " << source[0] << source [1]  << "!" << std::endl;
  }
  // check colour of piece and if it is the right turn
  else if ( board[srow][scol]->getColour() != turn ) {
    std::cout << "It is not " << print_colour(!turn) << "'s turn to move!" << std::endl;
  }
  // check if destination is occupied by the same colour as start
  else if ( board[drow][dcol] && board[drow][dcol]->getColour() == board[srow][scol]->getColour() ){
    std::cout << print_colour(turn) << "'s " <<  board[drow][dcol]->getLongName() << " cannot move to " << destination[0] << destination [1]  << "!" << std::endl;
  }
  else if ( board[srow][scol]->is_valid(*this, source, destination) ){
    board[drow][dcol] = board[srow][scol];
    board[srow][scol] = nullptr;
    std::cout << print_colour(turn) <<"'s " << board[drow][dcol]->getLongName() << " moves from " << source[0] << source[1] << " to " << destination[0] << destination [1] << std::endl;

    display_board();
  }
  
  change_turn();
}
