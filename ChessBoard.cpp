#include <iostream>
#include <cstring>

#include "ChessBoard.h"

//================= Internal Helper Functions =====================

// prints horizontal frame of chess board
void print_frame(){
  std::cout << "   +---+---+---+---+---+---+---+---+" << '\n';
}



//================= ChessBoard member Functions =====================


// prints the entire chessboard for debugging purposes
void ChessBoard::display_board() const{
  std::cout << "  ";
  for ( int i = 0; i < BOARD_LEN; i++){
    std::cout << "   " << (char) ('A' + i);
  }

  std::cout << std::endl;

  for ( int row = BOARD_LEN - 1; row >= 0; row--){
    print_frame();
    std::cout << " " << BOARD_LEN - row << " ";  
    for( int col = 0; col < BOARD_LEN; col++){

      int position = ( row * BOARD_LEN ) + col;

      std::string name;
      if ( !board[position] ) name = "   ";
      else name = board[position]->getName();
      std::cout << "|" << name;
    }
    std::cout << "|" << "\n";
  }
  print_frame();
}


// initialise starting chess board
void ChessBoard::resetBoard(){
  for ( int position = 0; position < BOARD_LEN*BOARD_LEN; position++){

    // Set colour
    bool colour = false;  // true = black, false = white
    if ( position > 2*BOARD_LEN-1 ) colour = true;

    // set name
    std::string name = "w";
    if ( colour == true ) name = "b";
        
    // Initialise empty cells
    if ( position > 15 && position < 48 ) board[position] = NULL;
    
    // Initialise rook
    else if ( position == 0 || position == 7 || position == 56 || position == 63){ 
      name.push_back('r');
      name.push_back((position % 2)? '2' : '1');
      board[position] = new Rook(name, colour, position);
    }

    // Initialise knight
    else if ( position == 1 || position == 6 || position == 57 || position == 62){ 
      name.push_back('n');
      name.push_back((position % 2)? '2' : '1');
      board[position] = new Knight(name, colour, position);
    }

    // Initialise bishop
    else if ( position == 2 || position == 5 || position == 58 || position == 61){ 
      name.push_back('b');
      name.push_back((position % 2)? '2' : '1');
      board[position] = new Bishop(name, colour, position);
    }

    // Initialise king
    else if ( position == 3 || position == 59){ 
      name.push_back('k');
      name.push_back('1');
      board[position] = new King(name, colour, position);
    }

    // Initialise queen
    else if ( position == 4 || position == 60){ 
      name.push_back('q');
      name.push_back('1');
      board[position] = new Queen(name, colour, position);
    }

    else {
      name.push_back('p');
      char number = ((position % 8) + 1) + '0';
      name.push_back(number);
      board[position] = new Pawn(name, colour, position);   
    }
  }
}
