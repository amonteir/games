#include <iostream>
#include "Board.h"

using namespace std;


namespace angelogames{

	Board::Board() {
		// initialise board
		/*
		1 2 3
		4 5 6
		7 8 9
		*/

		MAX_MOVES = m_boardSize;

		char position = '1';

		for (int i = 0; i < m_boardSize; i++) {
			pBoardBuffer[i] = position;
			position++;
		}
	}

	Board::~Board() {
		delete[] pBoardBuffer;
		//std::cout << "Board destroyed." << std::endl;
	}

	void Board::print() {
		/*
		1 | 2 | 3
		4 | 5 | 6
		7 | 8 | 9
		*/
		int counter = 0;

		for (int i = 0; i < m_boardSize; i++) {
			if (counter == BOARD_COLS - 1) {
				cout << pBoardBuffer[i] << endl;
				counter = 0;
				continue;
			}
			cout << pBoardBuffer[i] << " | " << flush;
			counter++;

		}
		cout << endl;
	}

	void Board::createPlayerMove(int position, char piece) {

		pBoardBuffer[position-1] = piece;

	}

	bool Board::validatePlayerMove(int playerMove) {

		char playerMoveChar = '0' + playerMove; // converts x in 'x'

		if (pBoardBuffer[playerMove - 1] == playerMoveChar) {
			return true;
		}
		else {
			return false;
		}
	}


	bool Board::checkWinner(char playerPiece, char computerPiece) {
		/*
		0 1 2
		3 4 5
		6 7 8
		*/

		char winner = '0';

		// horizontal line of 1
		if ((pBoardBuffer[0] == pBoardBuffer[1]) && (pBoardBuffer[0] == pBoardBuffer[2])) {
			winner = pBoardBuffer[0];
		}
		// vertical line of 1
		else if ((pBoardBuffer[0] == pBoardBuffer[3]) && (pBoardBuffer[0] == pBoardBuffer[6])) {
			winner = pBoardBuffer[0];
		}
		// diagonal of 1
		else if ((pBoardBuffer[0] == pBoardBuffer[4]) && (pBoardBuffer[0] == pBoardBuffer[8])) {
			winner = pBoardBuffer[0];
		}
		// vertical of 2
		else if ((pBoardBuffer[1] == pBoardBuffer[4]) && (pBoardBuffer[1] == pBoardBuffer[7])) {
			winner = pBoardBuffer[1];
		}
		// vertical of 3
		else if ((pBoardBuffer[2] == pBoardBuffer[5]) && (pBoardBuffer[2] == pBoardBuffer[8])) {
			winner = pBoardBuffer[2];
		}
		// diagonal of 3
		else if ((pBoardBuffer[2] == pBoardBuffer[4]) && (pBoardBuffer[2] == pBoardBuffer[6])) {
			winner = pBoardBuffer[2];
		}
		// horizontal line of 4
		else if ((pBoardBuffer[3] == pBoardBuffer[4]) && (pBoardBuffer[3] == pBoardBuffer[5])) {
			winner = pBoardBuffer[3];
		}
		// horizontal line of 7
		else if ((pBoardBuffer[6] == pBoardBuffer[7]) && (pBoardBuffer[6] == pBoardBuffer[8])) {
			winner = pBoardBuffer[6];
		}
		else { winner = '0'; }

		if (winner == playerPiece) {
			std::cout << "Well done! You won !!!" << std::endl;
			return true;
		}
		else if (winner == computerPiece) {
			std::cout << "Sorry but the computer won." << std::endl;
			return true;
		}
		else { return false; }
	}
}