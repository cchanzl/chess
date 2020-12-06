/***********************************************************************
* Header file for ChessPiece. This file contains the abstract class
* ChessPiece which is the base class for each individual ChessPiece 
* such as King, Queen, Rook etc. No objects of ChessPiece can be 
* created and each individual piece inherits pure virtual function and
* overrides them based on their unique movement.
***********************************************************************/

#include <iostream>

// this is an abstract class
class ChessPiece{
  std::string name;
  bool status;       // true if alive
  bool colour;       // 1 if black and 0 if white
  int position;  // position of the chesspiece
  /*
  virtual void make_move(const char source[2], const char destination[2]) = 0; // pure virtual function
  */
public:
  ChessPiece(){};
  ChessPiece(const std::string name, const bool colour, const int position) // constructor
    : name(name), status(true), colour(colour), position(position){};

  std::string getName(){return name;};
  /*
  void change_status(){   // change status to 0 if captured
    if ( status ) status = false;
    else cerr << "Piece is already dead!" << endl;
  };
  bool is_alive(){ return status;}
  void update_position(const char dstination[2]);
  */
};

// derived class of ChessPiece
class King: public ChessPiece {

public:
  King(const std::string name2, const bool colour2, const int position2)
    :ChessPiece(name2, colour2, position2) {};
  /*
  void make_move(const char source[2], const char destination[2]);  // attempt to make a move from source to destination
  void check_move(const char source[2], const char destination[2]); // check if move is appropriate
  */
};


class Rook: public ChessPiece {
public:
  Rook(const std::string name2, const bool colour2, const int position2)
    :ChessPiece(name2, colour2, position2) {};
 

};


class Bishop: public ChessPiece {
public:
  Bishop(const std::string name2, const bool  colour2, const int position2)
    :ChessPiece(name2, colour2, position2) {};
 

};


class Queen: public ChessPiece {
public:
  Queen(const std::string name2, const bool colour2, const int position2)
    :ChessPiece(name2, colour2, position2) {};
 

};


class Knight: public ChessPiece {
public:
  Knight(const std::string name2, const bool colour2, const int position2)
    :ChessPiece(name2, colour2, position2) {};
 

};


class Pawn: public ChessPiece {
public:
  Pawn(const std::string name2, const bool colour2, const int position2)
    :ChessPiece(name2, colour2, position2) {};
 

};
