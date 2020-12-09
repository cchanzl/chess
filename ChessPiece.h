/***********************************************************************
* Header file for ChessPiece. This file contains the abstract class
* ChessPiece which is the base class for each individual ChessPiece 
* such as King, Queen, Rook etc. No objects of ChessPiece can be 
* created and each individual piece inherits pure virtual function and
* overrides them based on their unique movement.
***********************************************************************/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include "constants.h"

class ChessBoard;

// this is an abstract class
class ChessPiece {
protected:
  std::string shortName; // short name of length 3 for printing to board on command line
  std::string longName;  // full name of piece for cout messages
  bool moved = false;    // true if a piece has moved. used for castling (Rook/King)
  bool colour;           // 1 if black and 0 if white
  int row;               // position of the chesspiece
  int col;               // position of the chesspiece

  // 4 combinations of {row, col} for multiple steps "+" shaped movement
  int direction_line[4][2] = {{ 0, 1}, { 0,-1},
			      { 1, 0}, {-1, 0}};  

  // 4 combinations of {row, col} for single step "*" shaped movement
  int direction_diag[4][2] = {{ 1, 1}, {-1, 1},
			      { 1,-1}, {-1,-1}};

  // 8 combinations of {row, col} for single step "*" shaped movement
  int direction_star[8][2] = {{ 1, 0}, { 1, 1},
			      { 1,-1}, { 0, 1},
			      { 0,-1}, {-1,-1},
			      {-1, 0}, {-1, 1}};

  // 8 combinations of {row, col} for single step "L" shaped movement
  int direction_L[8][2] = {{ 2, 1}, { 2,-1},
			   { 1, 2}, { 1,-2},
			   {-2, 1}, {-2,-1},
			   {-1, 2}, {-1,-2}};
  
  // make moves in desired direction and distance. up/down must be between 0 and 7
  // returns true if move is within board
  bool is_within_board(const int row, const int col, const char source[2]);

  // returns true if source can move to destination diagonally and linearly ("X" & "+")
  // For Rook, Bishop and Queen, depending on direction matrix provided
  bool is_star_valid(ChessBoard cb, const char source[2], const char destination[2], const int direction[4][2]);

  // returns true if source can move one step in one of eight direction ("*")
  // For King and Knight, depending on direction matrix provided
  bool is_eight_valid(ChessBoard cb, const char source[2], const char destination[2], const int direction[BOARD_LEN][2]);
  
public:
  ChessPiece(){};
  ChessPiece(const std::string longName, const bool colour, int row, int col);

  // pure virtual function
  virtual bool is_valid(const ChessBoard cb, const char source[2], const char destination[2]) = 0;  

  // returns short name of piece for printing of ChessBoard to command line
  std::string getShortName();

  // returns long name of piece for printing of move to std::cout
  std::string getLongName();

  // set to true if piece has made a first successful move
  void setFirstMove();

  // returns colour of chess piece
  bool getColour();

  virtual ~ChessPiece(){};
  
};

// derived class of ChessPiece
class King: public ChessPiece {

public:
  King(const bool colour2, int row, int col)
    :ChessPiece("King", colour2, row, col) {};

 // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb, const char source[2], const char destination[2]); 

  ~King() override{};
  
};


class Rook: public ChessPiece {
public:
  Rook(const bool colour2, int row, int col)
    :ChessPiece("Rook", colour2, row, col) {};

   // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 
  ~Rook() override{};
  
};


class Bishop: public ChessPiece {
public:
  Bishop(const bool  colour2, int row, int col)
    :ChessPiece("Bishop", colour2, row, col) {};
 
 // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 
  ~Bishop() override{};
  
};


class Queen: public ChessPiece {
public:
  Queen(const bool colour2, int row, int col)
    :ChessPiece("Queen", colour2, row, col) {};

   // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 
  ~Queen() override{};
  
};


class Knight: public ChessPiece {
public:
  Knight(const bool colour2, int row, int col)
    :ChessPiece("Knight", colour2, row, col) {};

  // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 

  ~Knight() override{};

};


class Pawn: public ChessPiece {  
public:
  Pawn(const bool colour2, int row, int col)
    :ChessPiece("Pawn", colour2, row, col) {};
  
  // returns true if a move from source to destination is valid
  bool is_valid(const ChessBoard cb, const char source[2], const char destination[2]) override; 
 
  ~Pawn() override{};
  
};

#endif
