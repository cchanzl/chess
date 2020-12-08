# include <iostream>

#include "ChessPiece.h"
#include "ChessBoard.h"

//================= Internal Helper Functions =====================








//================= ChessPiece member Functions =====================

// ChessPiece constructor
ChessPiece::ChessPiece(const std::string longName, const bool colour, int row, int col)
  : longName(longName), status(true), colour(colour), row(row), col(col){

  // calculate index on board
  int index = row * BOARD_LEN + col;
  
  // set name
  std::string name = "w";
  if ( colour == true ) name = "b";

  // set piece name
  if ( longName == "Knight" ) name.push_back('N');
  else name.push_back(longName[0]);
    
  // set piece number
  if ( longName == "Queen" || longName == "King" ) name.push_back('1');
  else if ( longName == "Pawn") name.push_back( ((index % 8) + 1) + '0' );
  else name.push_back((index % 2)? '2' : '1');
    
  shortName = name;

}

// Change a ChessPiece status from alive to eliminated
void ChessPiece::change_status(){
  if ( status ) status = false;
  else std::cerr << "Piece is already dead!" << std::endl;
}

// returns true if ChessPiece is alive. false if otherwise.
bool ChessPiece::is_alive(){
  return status;
}

// generic move in desired direction and distance. up/down must be between 0 and 7  
// returns true if move is possible
bool ChessPiece::move_piece(const int up, const int down, const char source[2]){
 
  // convert position to index
  int col = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int row = static_cast<int>(source[1]) - ASCII_OFFSET_0;

  // check direction is appropriate
  if ( up < 0 || up > BOARD_LEN-1 || down < 0 || down > BOARD_LEN-1 ){
    std::cerr << "Direction must be between 0 and 7 (inclusive)." << std::endl;
  }
  
  // make one cell move according to direction
  if ( (col + up) < BOARD_LEN && (row + down) < BOARD_LEN ) return true;
  
  return false;
}


//================= Inidivudal pieces member Functions =====================

// attempt to make a move from source to destination
bool King::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  return true;
}

// attempt to make a move from source to destination
bool Rook::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  return true;
}

// attempt to make a move from source to destination
bool Bishop::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  return true;
}

// attempt to make a move from source to destination
bool Queen::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  return true;
}

// attempt to make a move from source to destination
bool Knight::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  return true;
}


// attempt to make a move from source to destination
bool Pawn::is_valid(ChessBoard cb, const char source[2], const char destination[2]){

  // obtain column and row
  int col = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int row = static_cast<int>(source[1]) - ASCII_OFFSET_0;

  // Set direction to -1 if black
  int vertDir = 1;
  (this->getColour())? vertDir = -1 : vertDir = 1;
  /*
  // allow for advancing two squares at the start if it is at start position
  if ( ( row == 1 && this->getColour() == false ) || ( row == 6 && this->getColour() == true ) ) {

    if ( cb.board[start   
    
    }*/

  
  return true;
}




