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

// returns true if the "colour" is checkmated
bool ChessBoard::is_checkmate(const bool colour){

  // setup
  char king[2];
  locate_king(colour, king);
  
  // returns false if there is not even a check
  if ( !is_check(colour) ) return false;	  
  
  // check for checkmate
  // Outer loop: Looks for chesspieces of the "colour" 
  for ( int r = 0; r < BOARD_LEN; r++){
    for ( int c = 0; c < BOARD_LEN; c++){

      // if board is occupied and of the same colour
      if ( board[r][c] && board[r][c]->getColour() == colour){
	char source[2] = {static_cast<char>(c + ASCII_OFFSET_A),
			  static_cast<char>(r + ASCII_OFFSET_0)};
  	
	// Inner loop: If piece is found, make a move and see if it resolves the check  
	for ( int x = 0; x < BOARD_LEN; x++){
	  for ( int y = 0; y < BOARD_LEN; y++){

	    char destination[2] = {static_cast<char>(y + ASCII_OFFSET_A),
				   static_cast<char>(x + ASCII_OFFSET_0)};
	    
	    if ( board[x][y] && board[x][y]->getColour() == colour) continue;

	    if ( board[r][c]->is_valid(*this, source, destination) && !is_self_check(colour, source, destination) ) return false;    
	  }
	}
      }
    }
  }
  return true;
}

// updates king [2] with the position of king of the specified colour
void ChessBoard::locate_king(const bool colour, char king[2]) const{

  int krow, kcol;
  for ( int r = 0; r < BOARD_LEN; r++){
    for ( int c = 0; c < BOARD_LEN; c++){

      // continue if empty
      if ( !board[r][c] ) continue;
      // test if it is King
      if ( board[r][c]->getLongName() == "King" && board[r][c]->getColour() == colour ){
	krow = r;
	kcol = c;
	break;
      }
    }
  }
  king[0] = static_cast<char>(kcol + ASCII_OFFSET_A);
  king[1] = static_cast<char>(krow + ASCII_OFFSET_0);
}

// returns true if the "colour" is checked
bool ChessBoard::is_check(const bool colour) const{
  char king[2];
  locate_king(colour, king);

  // check for check by moving opponent piece to opposite King, cell by cell
  for ( int r = 0; r < BOARD_LEN; r++){
    for ( int c = 0; c < BOARD_LEN; c++){

      // continue if empty / null
      if ( !board[r][c] ) continue;
      
      // Check if it is an opponent piece
      if ( board[r][c]->getColour() == !colour ) {
	char source[2] = {static_cast<char>(c + ASCII_OFFSET_A),
			  static_cast<char>(r + ASCII_OFFSET_0)};

	// returns true if any opponent piece can reach the king
	if ( board[r][c]->is_valid(*this, source, king) ){
	  return true;
	}
      }
    }
  }
  return false;
}

// returns true if a player self-checks after a move
bool ChessBoard::is_self_check(const bool colour, const char source[2], const char destination[2]){

  // obtain column and row
  int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
  int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
  int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  int drow = static_cast<int>(destination[1]) - ASCII_OFFSET_0;

  // create temp pointer to hold destination piece, if any
  ChessPiece* temp = nullptr;
  temp = board[drow][dcol];

  // assign new move to destination
  board[drow][dcol] = board[srow][scol];
  board[srow][scol] = nullptr;

  // check for self-check
  if ( is_check(colour) ){
    // revert board once check is completed
    board[srow][scol] = board[drow][dcol];
    board[drow][dcol] = temp;
    return true;	  
  }
 
  // revert board once check is completed
  board[srow][scol] = board[drow][dcol];
  board[drow][dcol] = temp;
	 
  return false;
}

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
  std::cout << "A new chess game is started!" << std::endl;

  // set to White's turn at every reset
  turn = false;
  
  for ( int row = 0; row < BOARD_LEN; row++){
    for ( int col = 0; col < BOARD_LEN; col++ ){

      // calculate index
      int index = row * BOARD_LEN + col;
      
      // Set colour
      bool colour = false;  // false = white, true = black
      if ( row > BOARD_LEN / 2 ) colour = true;
     
      // Initialise empty cells
      if ( row  > 1 && row < 6 ) board[row][col] = nullptr;
    
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

// submit move to the board
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
  
  // check colour of piece being moved, if it is on the right turn
  else if ( board[srow][scol]->getColour() != turn ) {
    std::cout << "It is not " << print_colour(!turn) << "'s turn to move!" << std::endl;
    return;
  }
  
  // check if destination is occupied by the same colour as start
  else if ( board[drow][dcol] && board[drow][dcol]->getColour() == board[srow][scol]->getColour() ){
    std::cout << print_colour(turn) << "'s " <<  board[srow][scol]->getLongName() << " cannot move to " << destination[0] << destination [1]  << "!" << std::endl;
  }

  // check if it is a valid move and there is no self_check
  else if ( board[srow][scol]->is_valid(*this, source, destination) && !is_self_check(turn, source, destination) ){
    
    // output statement confirming move    
    std::cout << print_colour(turn) <<"'s " << board[srow][scol]->getLongName() << " moves from " << source[0] << source[1] << " to " << destination[0] << destination [1];
 
    // eliminate opponent piece if present at destination
    if ( board[drow][dcol] ) {
      std::cout << " taking " << print_colour(!turn) << "'s " << board[drow][dcol]->getLongName();
      delete board[drow][dcol];
      board[drow][dcol] = nullptr;
    }

    // assign new move to destination
    board[drow][dcol] = board[srow][scol];
    board[srow][scol] = nullptr;

    // check if it is check
    if ( is_check(!turn) ){
      std::cout << std::endl;
      std::cout << print_colour(!turn) << " is in check";
      // check if it is checkmate
      if ( is_checkmate(!turn) ){
	std::cout << "mate" << std::endl;
      }
      else std::cout << std::endl;
    }
    else std::cout << std::endl;
    
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
