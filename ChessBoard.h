#include <iostream>


class ChessBoard{
  chesspiece positions[8][8];

  // black chess pieces
  King ki1;   // black king
  Rook r11;   // black rook 1
  Rook r12;   // black rook 2
  Bishop b11;   // black bishop 1
  Bishop b12;   // black bishop 2
  Queen q1;    // black queen 1
  Knight n11;  // black knight 1
  Knight n12;  // black knight 2
  Pawn p11;   // black pawn 1
  Pawn p12;   // black pawn 2
  Pawn p13;   // black pawn 3
  Pawn p14;   // black pawn 4
  Pawn p15;   // black pawn 5
  Pawn p16;   // black pawn 6
  Pawn p17;   // black pawn 7
  Pawn p18;   // black pawn 8 
  
  // white chess pieces
  King ki0;   // white king
  Rook r01;   // white rook 1
  Rook r02;   // white rook 2
  Bishop b01;   // white bishop 1
  Bishop b02;   // white bishop 2
  Queen q0;    // white queen 1
  Knight n01;  // white knight 1
  Knight n02;  // white knight 2
  Pawn p01;   // white pawn 1
  Pawn p02;   // white pawn 2
  Pawn p03;   // white pawn 3
  Pawn p04;   // white pawn 4
  Pawn p05;   // white pawn 5
  Pawn p06;   // white pawn 6
  Pawn p07;   // white pawn 7
  Pawn p08;   // white pawn 8 
  

  bool is_stale(); // returns true if it is a stalemate
  bool is_check();  // returns true if check
  bool is_checkmate(); // returns true if checkmate
  char* locate_queen(); // returns the position of the queen on board
  
 public:
  void submitMove(const char source[2], const char destination[2]); // make a move
  void resetBoard(); // resets Board to starting position
 
 
};


class ChessPiece{
  bool status;  // true if the piece is still alive
  bool colour;  // 1 if black and 0 if white
  char position[2]; // position of the chesspiece

  void check_check(); // check if move leaves own King in check

 public:
 ChessPiece(bool status, bool colour, char* position) // constructor
   : status(status), colours(colour), position(position){};
  
  void change_status(ChessPiece chesspiece);  // change status to 0 if captured
  
};


class King: public ChessPiece {

  void make_move(const char source[2], const char destination[2]);
  void check_move(const char source[2], const char destination[2]);
  
};


class Rook: public ChessPiece {


};


class Bishop: public ChessPiece {


};


class Queen: public ChessPiece {


};


class Knight: public ChessPiece {


};


class Pawn: public ChessPiece {


};
