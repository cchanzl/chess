#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"

//================= ChessPiece member Functions =====================

// returns the bool status as true if a piece has made its first move. false otherwise. 
bool ChessPiece::getMoved() const{
  return moved;
}

// returns short name of piece for printing of ChessBoard to command line
std::string ChessPiece::getShortName(){
  return shortName;
}

// returns long name of piece for printing of move to std::cout
std::string ChessPiece::getLongName(){
  return longName;
}

// set moved to true once the piece has made its first move. used for castling.
void ChessPiece::setFirstMove(){
  moved = true;
}

// returns colour of chess piece. true if white and false if black.
bool ChessPiece::getColour(){
  return colour;
}

// ChessPiece constructor
ChessPiece::ChessPiece(const std::string longName, const bool colour, const int row, const int col)
  : longName(longName), colour(colour), row(row), col(col){

  // calculate index on board
  int index = row * BOARD_LEN + col;
  
  // set colour
  std::string name = "w";
  if ( colour == true ) name = "b";

  // set piece name for printing to command line
  if ( longName == "Knight" ) name.push_back('N');
  else name.push_back(longName[0]);
    
  // set piece number for printing to command line
  if ( longName == "Queen" || longName == "King" ) name.push_back('1');
  else if ( longName == "Pawn") name.push_back( ((index % 8)) + ASCII_OFFSET_0 );
  else name.push_back((index % 2)? '2' : '1');

  // initialise 3 letter shortName
  shortName = name;
}

// generic move in desired direction and distance. row/col must be between 0 and 7  
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

// returns true if source can move to destination diagonally and linearly ("X" & "+")
// For Rook, Bishop and Queen, depending on direction matrix provided
bool ChessPiece::is_star_valid(const ChessBoard& cb, const char source[2], const char destination[2], const int direction[BOARD_LEN/2][2]){;

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  int count = 0;

  // move one cell by one cell along 'X' or '+'
  while ( count < BOARD_LEN/2 ){
    // initialise direction
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
	// next piece is opposite colour but not destination, break to next direction
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

// returns true if source can move one step in one of eight directions ("*" or "L")
// For King and Knight, depending on direction matrix provided
bool ChessPiece::is_eight_valid(const ChessBoard& cb, const char source[2], const char destination[2], const int direction[BOARD_LEN][2]){

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  for ( int i = 0; i < BOARD_LEN; i++){  
    // initialise direction
    int r_direction = direction[i][0];
    int c_direction = direction[i][1];

    // Condition 1: Move must be within the board
    if( !is_within_board(r_direction, c_direction, source) ) continue;
    
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
      // next piece is oppostie colour but not destination, continue to next move
      continue;
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

//================= Member Functions of individual pieces =====================

// attempt to make a move from source to destination
bool Queen::is_valid(const ChessBoard& cb, const char source[2], const char destination[2]){
  // check if there is any valid diagonal("X") move
  if ( is_star_valid(cb, source, destination, direction_diag )) return true;
  // check if there is any valid linear("+") move
  return is_star_valid(cb, source, destination, direction_line);
}

// attempt to make a move from source to destination
bool Rook::is_valid(const ChessBoard& cb, const char source[2], const char destination[2]){
  // check if there is any valid linear move ("+")
  return is_star_valid(cb, source, destination, direction_line);
}

// attempt to make a move from source to destination
bool Bishop::is_valid(const ChessBoard& cb, const char source[2], const char destination[2]){
  // check if there is any valid diagonal move ("X")
  return is_star_valid(cb, source, destination, direction_diag);
}

// attempt to make a move from source to destination
bool King::is_valid(const ChessBoard& cb, const char source[2], const char destination[2]){
  // check if it is a standard one cell move in one of eight directions
  if ( is_eight_valid(cb, source, destination, direction_star) ) return true;

  //// check for castling move

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0; 
  
  // adjust offset to be +7 if black
  int black_offset = BOARD_LEN - 1;
  (colour)? black_offset = BOARD_LEN - 1 : black_offset = 0;
 
  // set king and rook initial positions {r , c}
  int king[2] = {0 + black_offset, BOARD_LEN/2 };
 
  // Condition 1: Source[2] is in King's original position and King must not have moved 
  if ( srow != king[0] || scol != king[1] || moved != false ) return false;
  
  // Condition 2: Destination[2] must be 2 squares either queenside or kingside
  if ( abs(dcol - scol) != 2 || drow != srow ) return false;

  // Condition 3: There must be an unmoved Rook of the same colour on the castling side
  int rookRow = srow; 
  int rookCol = BOARD_LEN - 1;  // castling kingside
  (dcol - scol > 0)? rookCol = BOARD_LEN - 1 : rookCol = 0;
    
  if ( cb.board[rookRow][rookCol]->getLongName() != "Rook" || cb.board[rookRow][rookCol]->getMoved() != false || cb.board[rookRow][rookCol]->getColour() != colour) return false;

  // Condition 4: King is not currently in check
  if ( cb.is_check(colour, source) ) return false;
  
  // Condition 5: No piece between Rook and King and King path not under attack
  if ( rookCol == BOARD_LEN - 1) { // castling kingside
    for ( int i = 1; i < rookCol - scol; i++){
      // Condition 5.1a: There must not be any piece in between King and Rook
      if ( cb.board[srow][scol+i] != nullptr ) return false;
      // Condition 5.2b: Path of King must not be under attack
      char path[2] = {static_cast<char>(scol + ASCII_OFFSET_A + i), // col
		      static_cast<char>(srow + ASCII_OFFSET_0)};    // row
      if ( cb.is_check(colour, path) ) return false;
    }
  }
  else { // castling queenside
    for ( int i = 1; i < scol - rookCol; i++){
      // Condition 5.1a: There must not be any piece in between King and Rook
      if ( cb.board[srow][scol-i] != nullptr ) return false;
      // Condition 5.2b: Path of King must not be under attack
      if ( i == scol - rookCol - 1 ) break; 
      char path[2] = {static_cast<char>(scol + ASCII_OFFSET_A - i), // col
		      static_cast<char>(srow + ASCII_OFFSET_0)};    // row
      if ( cb.is_check(colour, path) ) return false;
    }
  }
  return true;
}

// attempt to make a move from source to destination
bool Knight::is_valid(const ChessBoard& cb, const char source[2], const char destination[2]){
  return is_eight_valid(cb, source, destination, direction_L); 
}


// attempt to make a move from source to destination
bool Pawn::is_valid(const ChessBoard& cb, const char source[2], const char destination[2]){

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;
  
  // Set direction to -1 if black
  int vertDir = 1;
  (colour)? vertDir = -1 : vertDir = 1;
  
  //// allow for advancing two squares at the start if it is at start position

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

  //// allow for diagonal movement

  // Condition 1: Destination must be exactly 1 row and 1 col away from source
  if ( drow - srow == vertDir && abs(dcol - scol) == abs(vertDir) ) {
    // Condition 2: There must be an opponent piece at destination
    if ( cb.board[drow][dcol] ){
      row = drow;
      col = dcol;
      return true;
    }
  }

  //// allow for advancement of one cell

  // Condition 1: Move must have the same position as destination after move
  if ( srow + vertDir == drow && scol == dcol ){
    // Condition 2: No Opponent piece at destination
    // Piece of same colour at destination was already checked
    if ( !cb.board[drow][dcol] ){
      row = drow;
      col = dcol;
      return true;
    }
  }
    
  return false;
}




