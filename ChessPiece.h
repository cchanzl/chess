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

class ChessBoard;

// this is an abstract class
class ChessPiece {
  std::string shortName;
  std::string longName;
  bool status;       // true if alive
  bool colour;       // 1 if black and 0 if white
  int position;  // position of the chesspiece

  // pure virtual function
  virtual bool is_valid(ChessBoard board, const char source[2], const char destination[2]) = 0;
  
public:
  ChessPiece(){};
  ChessPiece(const std::string longName, const bool colour, const int position) // constructor
    : longName(longName), status(true), colour(colour), position(position){

    // set name
    std::string name = "w";
    if ( colour == true ) name = "b";

    // set piece name
    if ( longName == "Knight" ) name.push_back('N');
    else name.push_back(longName[0]);
    
    // set piece number
    if ( longName == "Queen" || longName == "King" ) name.push_back('1');
    else if ( longName == "Pawn") name.push_back( ((position % 8) + 1) + '0' );
    else name.push_back((position % 2)? '2' : '1');
    
    shortName = name;

  };

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
  King(const bool colour2, const int position2)
    :ChessPiece("King", colour2, position2) {};

 // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard board, const char source[2], const char destination[2]); 
 
};


class Rook: public ChessPiece {
public:
  Rook(const bool colour2, const int position2)
    :ChessPiece("Rook", colour2, position2) {};

   // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard board,const char source[2], const char destination[2]); 
 

};


class Bishop: public ChessPiece {
public:
  Bishop(const bool  colour2, const int position2)
    :ChessPiece("Bishop", colour2, position2) {};
 
 // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard board,const char source[2], const char destination[2]); 
 
  
};


class Queen: public ChessPiece {
public:
  Queen(const bool colour2, const int position2)
    :ChessPiece("Queen", colour2, position2) {};

   // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard board,const char source[2], const char destination[2]); 
 

};


class Knight: public ChessPiece {
public:
  Knight(const bool colour2, const int position2)
    :ChessPiece("Knight", colour2, position2) {};

  // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard board,const char source[2], const char destination[2]); 
 

};


class Pawn: public ChessPiece {
public:
  Pawn(const bool colour2, const int position2)
    :ChessPiece("Pawn", colour2, position2) {};
  
  // returns true if a move from source to destination is valid
  bool is_valid(ChessBoard board,const char source[2], const char destination[2]); 
 

};

#endif
