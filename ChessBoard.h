/********************************************************************
* Header file for ChessBoard. This file includes the function
* signature for use on a ChessBoard, including checking the state of 
* the board (checkmate, stalemate etc.). It also includes each 
* ChessPiece as its data member.
********************************************************************/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "constants.h"
#include "ChessPiece.h"

class ChessBoard{
  ChessPiece** board = new ChessPiece* [BOARD_LEN*BOARD_LEN-1];
  bool turn = false; // white moves first
  /*  
  bool is_stale(); // returns true if it is a stalemate
  bool is_check();  // returns true if check
  bool is_checkmate(); // returns true if checkmate
  char* locate_queen(); // returns the position of the queen on board
  bool is_self_check(); // check if move leaves own King in check
  */ 
  
  void change_turn();
    
 public:
  ChessBoard(){resetBoard();};

  void submitMove(const char source[2], const char destination[2]); // make a move
  void resetBoard();   // resets Board to starting position
  void display_board() const;  // prints the board for debugging
};

// ========== Generic Helper Functions ==========

// returns an integer equal to the index in the chesspiece array
int board_index(const char source[2]);
 


#endif
