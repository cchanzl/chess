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

      int position = ( row * BOARD_LEN ) + col;

      std::string name;
      if ( !board[position] ) name = "   ";
      else name = board[position]->getShortName();
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

  for ( int position = 0; position < BOARD_LEN*BOARD_LEN; position++){

    // Set colour
    bool colour = false;  // true = black, false = white
    if ( position > 2*BOARD_LEN-1 ) colour = true;
     
    // Initialise empty cells
    if ( position > 15 && position < 48 ) board[position] = NULL;
    
    // Initialise rook
    else if ( position == 0 || position == 7 || position == 56 || position == 63){ 
      board[position] = new Rook(colour, position);
    }

    // Initialise knight
    else if ( position == 1 || position == 6 || position == 57 || position == 62){ 
      board[position] = new Knight(colour, position);
    }

    // Initialise bishop
    else if ( position == 2 || position == 5 || position == 58 || position == 61){ 
      board[position] = new Bishop(colour, position);
    }

    // Initialise king
    else if ( position == 3 || position == 59){ 
      board[position] = new King(colour, position);
    }

    // Initialise queen
    else if ( position == 4 || position == 60){ 
      board[position] = new Queen(colour, position);
    }

    else {
      board[position] = new Pawn(colour, position);   
    }
  }
}

void ChessBoard::submitMove(const char source[2], const char destination[2]){

  // check source and destination is in the right format
  // ...
  
  // obtain source position by index
  int start = board_index(source);
  int end = board_index(destination);

  // check if there is a piece at that position
  if( !board[start] ) {
    std::cout << "There is no piece at position " << source[0] << source [1]  << "!" << std::endl;
  }
  // check colour of piece and if it is the right turn
  else if ( board[start]->getColour() != turn ) {
    std::cout << "It is not " << print_colour(!turn) << "'s turn to move!" << std::endl;
  }
  // check if destination is occupied by the same colour
  else if ( board[end] && board[end]->getColour() == board[start]->getColour() ){
    std::cout << print_colour(turn) << "'s " <<  board[end]->getLongName() << " cannot move to " << destination[0] << destination [1]  << "!" << std::endl;
  }

  // ...
  
  change_turn();
}
