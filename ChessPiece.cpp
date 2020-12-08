#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"

//================= Internal Helper Functions =====================








//================= ChessPiece member Functions =====================

// ChessPiece constructor
ChessPiece::ChessPiece(const std::string longName, const bool colour, int row, int col)
  : longName(longName), colour(colour), row(row), col(col){

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

// generic move in desired direction and distance. up/down must be between 0 and 7  
// returns true if move is within board
bool ChessPiece::is_within_board(const int row, const int col, const char source[2]){
 
  // convert position to index
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;

  // check final position is within board
  if( srow+row < 0 || srow+row > BOARD_LEN-1 || scol+col < 0 || scol+col > BOARD_LEN-1 ){
    return false;
  }
  return true;
}

// returns true if source can move to destination diagonally ("X")
bool ChessPiece::is_diag_valid(ChessBoard cb, const char source[2], const char destination[2]){;

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  int count = 0;
  // {row, col}
  int direction[4][2] = {{ 1, 1}, {-1, 1},
			 { 1,-1}, {-1,-1}};
  
  // move one cell by one cell along the 'X' diagonal
  while ( count < 4 ){
    int r_direction = direction[count][0];
    int c_direction = direction[count][1];
    
    
    for ( int i = 1; i < BOARD_LEN; i++){
     
      // Condition 1: Move must be within the board
      if( !is_within_board(i*r_direction, i*c_direction, source) ) break;
      
      // Condition 2: Check if there is a piece in next move
      if ( cb.board[srow + i*r_direction][scol + i*c_direction] ){
	// Condition 2.1: If a piece is in next move, it must not be same colour
	if ( cb.board[srow + i*r_direction][scol + i*c_direction]->getColour() == colour) break;
	// Condition 2.2: If next piece is opposite colour, check if it is destination
	if ( srow + i*r_direction == drow && scol + i*c_direction == dcol ){    
	  row = drow;
	  col = dcol;
	  return true;
	}
	break;
      }
    
      // Condition 3: Move must have the same position as destination after move
      if ( srow + i*r_direction == drow && scol + i*c_direction == dcol ){    
	row = drow;
	col = dcol;
	return true;
      }
    }
    count++;
  }
  
  return false;
}

// returns true if source can move to destination linearly ("+")
bool ChessPiece::is_line_valid(ChessBoard cb, const char source[2], const char destination[2]){;

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  int count = 0;
  // {row, col}
  int direction[4][2] = {{ 0, 1}, { 0,-1},
			 { 1, 0}, {-1, 0}};

  // move one cell by one cell along the 'X' diagonal
  while ( count < 4 ){

    int r_direction = direction[count][0];
    int c_direction = direction[count][1];
    
    for ( int i = 1; i < BOARD_LEN; i++){
     
      // Condition 1: Move must be within the board
      if( !is_within_board(i*r_direction, i*c_direction, source) ) break;
      
      // Condition 2: Check if there is a piece in next move
      if ( cb.board[srow + i*r_direction][scol + i*c_direction] ){
	// Condition 2.1: If a piece is in next move, it must not be same colour
	if ( cb.board[srow + i*r_direction][scol + i*c_direction]->getColour() == colour) break;
	// Condition 2.2: If next piece is opposite colour, check if it is destination
	if ( srow + i*r_direction == drow && scol + i*c_direction == dcol ){    
	  row = drow;
	  col = dcol;
	  return true;
	}
	break;
      }
    
      // Condition 3: Move must have the same position as destination after move
      if ( srow + i*r_direction == drow && scol + i*c_direction == dcol ){    
	row = drow;
	col = dcol;
	return true;
      }
    }
    count++;
  }
  return false;
}


//================= Member Functions of individual pieces =====================

// attempt to make a move from source to destination
bool Queen::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  // check if there is any valid diagonal("X") / linear("+") move
  if ( is_diag_valid(cb, source, destination )) return true;
  if ( is_line_valid(cb, source, destination )) return true;
  return false;
}

// attempt to make a move from source to destination
bool Rook::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  // check if there is any valid linear move ("+")
  return is_line_valid(cb, source, destination);
}

// attempt to make a move from source to destination
bool Bishop::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  // check if there is any valid diagonal move ("X")
  return is_diag_valid(cb, source, destination);
}

// attempt to make a move from source to destination
bool King::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
 
  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  // {row, col}
  int direction[8][2] = {{ 1, 0}, { 1, 1},
			 { 1,-1}, { 0, 1},
			 { 0,-1}, {-1,-1},
			 {-1, 0}, {-1, 1}};

  for ( int i = 0; i < BOARD_LEN; i++){  
    // initialise direction
    int r_direction = direction[i][0];
    int c_direction = direction[i][1];

    // Condition 1: Move must be within the board
    if( !is_within_board(r_direction, c_direction, source) ) {
      continue;
    }
    
    // Condition 2: Check if there is a piece in destination
    if ( cb.board[srow + r_direction][scol + c_direction] ){
      // Condition 2.1: If a piece is in destination, it must not be same colour
      if ( cb.board[srow + r_direction][scol + c_direction]->getColour() == colour) continue;
      // Condition 2.2: If next piece is opposite colour, check if it is destination
      if ( srow + r_direction == drow && scol + c_direction == dcol ){    
	row = drow;
	col = dcol;
	return true;
      }
    }

    // Condition 3: Move must have the same position as destination after move
    if ( srow + r_direction == drow && scol + c_direction == dcol ){    
      row = drow;
      col = dcol;
      return true;
    }
  }
  return false;
}

// attempt to make a move from source to destination
bool Knight::is_valid(ChessBoard cb, const char source[2], const char destination[2]){
  
  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  // {row, col}
  int direction[8][2] = {{ 2, 1}, { 2,-1},
			 { 1, 2}, { 1,-2},
			 {-2, 1}, {-2,-1},
			 {-1, 2}, {-1,-2}};

  for ( int i = 0; i < BOARD_LEN; i++){  
    // initialise direction
    int r_direction = direction[i][0];
    int c_direction = direction[i][1];

    // Condition 1: Move must be within the board
    if( !is_within_board(r_direction, c_direction, source) ) {
      continue;
    }
    
    // Condition 2: Check if there is a piece in destination
    if ( cb.board[srow + r_direction][scol + c_direction] ){
      // Condition 2.1: If a piece is in destination, it must not be same colour
      if ( cb.board[srow + r_direction][scol + c_direction]->getColour() == colour) continue;
      // Condition 2.2: If next piece is opposite colour, check if it is destination
      if ( srow + r_direction == drow && scol + c_direction == dcol ){    
	row = drow;
	col = dcol;
	return true;
      }
    }

    // Condition 3: Move must have the same position as destination after move
    if ( srow + r_direction == drow && scol + c_direction == dcol ){    
      row = drow;
      col = dcol;
      return true;
    }
  }
  return false;
}


// attempt to make a move from source to destination
bool Pawn::is_valid(const ChessBoard cb, const char source[2], const char destination[2]){

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;
  
  // Set direction to -1 if black
  int vertDir = 1;
  (colour)? vertDir = -1 : vertDir = 1;
  
  // allow for advancing two squares at the start if it is at start position
  // Condition 1: Move must have the same position as destination after move
  if ( (srow + 2*vertDir) == drow && scol == dcol ){
    // Condition 2: White and Black Pawn must be in rows 1 and 6 respectively
    if( ( srow == 1 && colour == false ) || ( srow == 6 && colour == true )){
      // Condition 3: No piece in the next two row of the same column
      if ( !cb.board[srow + vertDir][scol] && !cb.board[srow + 2*vertDir][scol] ){     
      row = drow;
      col = dcol;
      return true;
      }
    }
  }

  // allow for diagonal movement
  // Condition 1: Destination must be exactly 1 row and 1 col away from source
  if ( drow - srow == vertDir && abs(dcol - scol) == abs(vertDir) ) {
    // Condition 2: There must be opponent piece at destination
    if ( cb.board[drow][dcol] ){
      row = drow;
      col = dcol;
      return true;
    }
  }

  // allow for advancement of one cell
  // Condition 1: Move must have the same position as destination after move
  if ( srow + vertDir == drow && scol == dcol ){
    // Condition 2: No Opponent piece at destination
    if ( !cb.board[drow][dcol] ){
      row = drow;
      col = dcol;
      return true;
    }
  }
    
  return false;
}




