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
  std::string shortName;
  std::string longName;
  bool status;       // true if alive
  bool colour;       // 1 if black and 0 if white
  int row;  // position of the chesspiece
  int col;  // position of the chesspiece
  
  // generic move in desired direction and distance. up/down must be between 0 and 7
  // returns true if move is possible
  bool move_piece(const int up, const int down, const char source[2]);
    
public:
  ChessPiece(){};
  ChessPiece(const std::string longName, const bool colour, int row, int col);

  // pure virtual function
  virtual bool is_valid(const ChessBoard cb, const char source[2], const char destination[2]) = 0;  
  
  std::string getShortName(){return shortName;};
  std::string getLongName(){return longName;};
  
  bool getColour(){return colour;};
  void change_status();   // change status to 0 if captured
  bool is_alive();        // return status of ChessPiece
  //void update_position(const char dstination[2]);
  
};

// derived class of ChessPiece
class King: public ChessPiece {

public:
  King(const bool colour2, int row, int col)
    :ChessPiece("King", colour2, row, col) {};

 // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb, const char source[2], const char destination[2]); 
 
};


class Rook: public ChessPiece {
public:
  Rook(const bool colour2, int row, int col)
    :ChessPiece("Rook", colour2, row, col) {};

   // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 

};


class Bishop: public ChessPiece {
public:
  Bishop(const bool  colour2, int row, int col)
    :ChessPiece("Bishop", colour2, row, col) {};
 
 // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 
  
};


class Queen: public ChessPiece {
public:
  Queen(const bool colour2, int row, int col)
    :ChessPiece("Queen", colour2, row, col) {};

   // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 

};


class Knight: public ChessPiece {
public:
  Knight(const bool colour2, int row, int col)
    :ChessPiece("Knight", colour2, row, col) {};

  // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard cb,const char source[2], const char destination[2]); 
 

};


class Pawn: public ChessPiece {
public:
  Pawn(const bool colour2, int row, int col)
    :ChessPiece("Pawn", colour2, row, col) {};
  
  // returns true if a move from source to destination is valid
  bool is_valid(const ChessBoard cb, const char source[2], const char destination[2]) override; 
 

};

#endif
