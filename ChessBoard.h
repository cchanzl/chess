/********************************************************************
* Header file for ChessBoard. This file includes the function
* signature for use on a ChessBoard, including checking the state of 
* the board (checkmate, stalemate etc.). It also includes each 
* ChessPiece as its data member.
********************************************************************/

/*****************************************************
     SAMPLE PRINT OUT OF CHESSBOARD (IF ENABLED)  
 
 NUMBERS IN A4 AND F4 SHOW REFERENCE BY AXIS [r][c]
 NUMBERS IN C4 AND E6 SHOW REFERENCE BY INDEX 0 to 63

 where  INDEX = ( r * 8 ) + c

     A   B   C   D   E   F   G   H
   +---+---+---+---+---+---+---+---+
 8 |bR1|bN2|bB1|bQ1|bK1|bB2|bN1|bR2|
   +---+---+---+---+---+---+---+---+
 7 |bP1|bP2|bP3|bP4|bP5|bP6|bP7|bP8|
   +---+---+---+---+---+---+---+---+
 6 |   |   |   |   | 44|   |   |   |
   +---+---+---+---+---+---+---+---+
 5 |4.0|   |   |   |   |   |   |   |
   +---+---+---+---+---+---+---+---+
 4 |   |   | 26|   |   |3.5|   |   |
   +---+---+---+---+---+---+---+---+
 3 |   |   |   |   |   |   |   |   |
   +---+---+---+---+---+---+---+---+
 2 |wP1|wP2|wP3|wP4|wP5|wP6|wP7|wP8|
   +---+---+---+---+---+---+---+---+
 1 |wR1|wN2|wB1|wQ1|wK1|wB2|wN1|wR2|
   +---+---+---+---+---+---+---+---+

   <--- queenside --   - kingside ->

****************************************************/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "constants.h"
#include "ChessPiece.h"

class ChessBoard{
  bool turn = false; // white moves first
 
  bool is_stale(const bool colour); // returns true if "colour" has no possible moves
  bool is_checkmate(const bool colour); // returns true if "colour" is checkmated
  void locate_king(const bool colour, char king[2]) const;
  bool is_self_check(const bool colour, const char source[2], const char destination[2]); // returns true if player self-checks    
  void change_turn();   // changes the turn
  bool is_castling(const char source[2], const char destination[2]) const{
    int scol = static_cast<int>(source[0]) - ASCII_OFFSET_A;
    int srow = static_cast<int>(source[1]) - ASCII_OFFSET_0;
    int dcol = static_cast<int>(destination[0]) - ASCII_OFFSET_A;
  
    if ( board[srow][scol]->getLongName() == "King" && abs(dcol-scol) == 2 ) return true;
    return false;
  }; // returns true if king moved by two steps
  
 public:
  ChessPiece* board[BOARD_LEN][BOARD_LEN]; // row by column


  ChessBoard(){resetBoard();};  
  bool is_check(const bool colour, const char destination[2]) const;  // returns true if the "colour" is checked for that destination provided
  void submitMove(const char source[2], const char destination[2]); // make a move
  void resetBoard();   // resets Board to starting position
  void display_board() const;  // prints the board for debugging
};

// ========== Generic Helper Functions ==========

// returns true if positional input is appropriate
bool check_position(const char position[2]);
 


#endif
