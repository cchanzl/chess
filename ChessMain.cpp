#include "ChessBoard.h"
#include <iostream>
#include <cstring>
#include <fstream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cout << '\n';
	
	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';	

	cb.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';

	// Testing below. TO BE DELETED.
	/*
	cout << "=========================\n";
	cout << "         TESTING         \n";
	cout << "=========================\n\n";
	
	cb.resetBoard();
	cout << '\n';
		
	std::ifstream in("testing.txt");
	std::string input;
	int count = 1;
	while (in >> input){
	  
	  if( isdigit(input[0])) continue;
	  
	  char source[2] = {input[0], input[1]};
	  char destination[2] = {toupper(input[2]), input[3]};

	  cb.submitMove(source, destination);
	  if ( count % 2 == 0 ) cout << '\n';
	  count++;
	  }
		
	while (true){

	  std::string sou, des;
	  std::cin >> sou >> des;
	  
	  char source[2];
	  char destination[2];

	  strcpy(source, sou.c_str());
	  strcpy(destination, des.c_str());

	  cb.submitMove(source, destination);
	  cout << '\n';
	  }*/
		
	return 0;
}
