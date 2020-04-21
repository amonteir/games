#include <iostream>
#include "Board.h"

using namespace std;


namespace angelogames{

	Board::Board() {
		// initialise board
		/*
		1 | 2 | 3
		4 | 5 | 6
		7 | 8 | 9
		*/

		MAX_MOVES = 9;

		pBoardBuffer[1] = '|';
		pBoardBuffer[3] = '|';
		pBoardBuffer[6] = '|';
		pBoardBuffer[8] = '|';
		pBoardBuffer[11] = '|';
		pBoardBuffer[13] = '|';

		char position = '1';

		for (int i = 0; i < m_boardSize; i++) {
			if(pBoardBuffer[i] != '|'){
				pBoardBuffer[i] = position;
				position++;
			}
		}
	}

	Board::~Board() {
		delete[] pBoardBuffer;
		//std::cout << "Board destroyed." << std::endl;
	}

	void Board::print() {
		
		int counter = 0;

		for (int i = 0; i < m_boardSize; i++) {
			if (counter == BOARD_COLS - 1) {
				cout << pBoardBuffer[i] << endl;
				counter = 0;
				continue;
			}
			cout << pBoardBuffer[i] << flush;
			counter++;

		}
		cout << endl;
	}

	void Board::createPlayerMove(int position, char piece) {
		switch (position) {
		case 1:
			pBoardBuffer[0] = piece;
			break;
		case 2:
			pBoardBuffer[2] = piece;
			break;
		case 3:
			pBoardBuffer[4] = piece;
			break;
		case 4:
			pBoardBuffer[5] = piece;
			break;
		case 5:
			pBoardBuffer[7] = piece;
			break;
		case 6:
			pBoardBuffer[9] = piece;
			break;
		case 7:
			pBoardBuffer[10] = piece;
			break;
		case 8:
			pBoardBuffer[12] = piece;
			break;
		case 9:
			pBoardBuffer[14] = piece;
			break;
		default:
			break;
		}
	}

	bool Board::validatePlayerMove(int playerMove) {

		bool isValidMove = false;

		switch (playerMove) {
		case 1:
			if (pBoardBuffer[0] == '1') {
				isValidMove = true;
				break;
			}
			break;
		case 2:
			if (pBoardBuffer[2] == '2') {
				isValidMove = true;
				break;
			}
			break;
		case 3:
			if (pBoardBuffer[4] == '3') {
				isValidMove = true;
				break;
			}
			break;
		case 4:
			if (pBoardBuffer[5] == '4') {
				isValidMove = true;
				break;
			}
			break;
		case 5:
			if (pBoardBuffer[7] == '5') {
				isValidMove = true;
				break;
			}
			break;
		case 6:
			if (pBoardBuffer[9] == '6') {
				isValidMove = true;
				break;
			}
			break;
		case 7:
			if (pBoardBuffer[10] == '7') {
				isValidMove = true;
				break;
			}
			break;
		case 8:
			if (pBoardBuffer[12] == '8') {
				isValidMove = true;
				break;
			}
			break;
		case 9:
			if (pBoardBuffer[14] == '9') {
				isValidMove = true;
				break;
			}
			break;
		default:
			break;
		}

		return isValidMove;
	}



	char Board::checkWinner() {
		/*
		1 | 2 | 3
		4 | 5 | 6
		7 | 8 | 9
		*/
		// horizontal line of 1
		if ((pBoardBuffer[0] == pBoardBuffer[2]) && (pBoardBuffer[0] == pBoardBuffer[4])) {
			return pBoardBuffer[0];
		}
		// vertical line of 1
		else if ((pBoardBuffer[0] == pBoardBuffer[5]) && (pBoardBuffer[0] == pBoardBuffer[10])) {
			return pBoardBuffer[0];
		}
		// diagonal of 1
		else if ((pBoardBuffer[0] == pBoardBuffer[7]) && (pBoardBuffer[0] == pBoardBuffer[14])) {
			return pBoardBuffer[0];
		}
		// vertical of 2
		else if ((pBoardBuffer[2] == pBoardBuffer[7]) && (pBoardBuffer[2] == pBoardBuffer[12])) {
			return pBoardBuffer[2];
		}
		// vertical of 3
		else if ((pBoardBuffer[4] == pBoardBuffer[9]) && (pBoardBuffer[4] == pBoardBuffer[14])) {
			return pBoardBuffer[4];
		}
		// diagonal of 3
		else if ((pBoardBuffer[4] == pBoardBuffer[7]) && (pBoardBuffer[4] == pBoardBuffer[10])) {
			return pBoardBuffer[4];
		}
		// horizontal line of 4
		else if ((pBoardBuffer[5] == pBoardBuffer[7]) && (pBoardBuffer[5] == pBoardBuffer[9])) {
			return pBoardBuffer[5];
		}
		// horizontal line of 7
		else if ((pBoardBuffer[10] == pBoardBuffer[12]) && (pBoardBuffer[10] == pBoardBuffer[14])) {
			return pBoardBuffer[10];
		}
		else { return '0'; }
	}
}