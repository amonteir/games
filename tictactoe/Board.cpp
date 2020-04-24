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
			m_pBoardBuffer[i] = position;
			position++;
		}
	}

	Board::~Board() {
		delete[] m_pBoardBuffer;
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
				cout << m_pBoardBuffer[i] << endl;
				counter = 0;
				continue;
			}
			cout << m_pBoardBuffer[i] << " | " << flush;
			counter++;

		}
		cout << endl;
	}

	void Board::createPlayerMove(int position, char piece) {

		m_pBoardBuffer[position-1] = piece;

	}

	bool Board::validatePlayerMove(int playerMove) {

		char playerMoveChar = '0' + playerMove; // converts x in 'x'

		if (m_pBoardBuffer[playerMove - 1] == playerMoveChar) {
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
		if ((m_pBoardBuffer[0] == m_pBoardBuffer[1]) && (m_pBoardBuffer[0] == m_pBoardBuffer[2])) {
			winner = m_pBoardBuffer[0];
		}
		// vertical line of 1
		else if ((m_pBoardBuffer[0] == m_pBoardBuffer[3]) && (m_pBoardBuffer[0] == m_pBoardBuffer[6])) {
			winner = m_pBoardBuffer[0];
		}
		// diagonal of 1
		else if ((m_pBoardBuffer[0] == m_pBoardBuffer[4]) && (m_pBoardBuffer[0] == m_pBoardBuffer[8])) {
			winner = m_pBoardBuffer[0];
		}
		// vertical of 2
		else if ((m_pBoardBuffer[1] == m_pBoardBuffer[4]) && (m_pBoardBuffer[1] == m_pBoardBuffer[7])) {
			winner = m_pBoardBuffer[1];
		}
		// vertical of 3
		else if ((m_pBoardBuffer[2] == m_pBoardBuffer[5]) && (m_pBoardBuffer[2] == m_pBoardBuffer[8])) {
			winner = m_pBoardBuffer[2];
		}
		// diagonal of 3
		else if ((m_pBoardBuffer[2] == m_pBoardBuffer[4]) && (m_pBoardBuffer[2] == m_pBoardBuffer[6])) {
			winner = m_pBoardBuffer[2];
		}
		// horizontal line of 4
		else if ((m_pBoardBuffer[3] == m_pBoardBuffer[4]) && (m_pBoardBuffer[3] == m_pBoardBuffer[5])) {
			winner = m_pBoardBuffer[3];
		}
		// horizontal line of 7
		else if ((m_pBoardBuffer[6] == m_pBoardBuffer[7]) && (m_pBoardBuffer[6] == m_pBoardBuffer[8])) {
			winner = m_pBoardBuffer[6];
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

	int Board::evaluateWinner(char playerPiece, char computerPiece) {
		/*
		0 1 2
		3 4 5
		6 7 8
		*/

		char winner = '0';

		// horizontal line of 1
		if ((m_pBoardBuffer[0] == m_pBoardBuffer[1]) && (m_pBoardBuffer[0] == m_pBoardBuffer[2])) {
			winner = m_pBoardBuffer[0];
		}
		// vertical line of 1
		else if ((m_pBoardBuffer[0] == m_pBoardBuffer[3]) && (m_pBoardBuffer[0] == m_pBoardBuffer[6])) {
			winner = m_pBoardBuffer[0];
		}
		// diagonal of 1
		else if ((m_pBoardBuffer[0] == m_pBoardBuffer[4]) && (m_pBoardBuffer[0] == m_pBoardBuffer[8])) {
			winner = m_pBoardBuffer[0];
		}
		// vertical of 2
		else if ((m_pBoardBuffer[1] == m_pBoardBuffer[4]) && (m_pBoardBuffer[1] == m_pBoardBuffer[7])) {
			winner = m_pBoardBuffer[1];
		}
		// vertical of 3
		else if ((m_pBoardBuffer[2] == m_pBoardBuffer[5]) && (m_pBoardBuffer[2] == m_pBoardBuffer[8])) {
			winner = m_pBoardBuffer[2];
		}
		// diagonal of 3
		else if ((m_pBoardBuffer[2] == m_pBoardBuffer[4]) && (m_pBoardBuffer[2] == m_pBoardBuffer[6])) {
			winner = m_pBoardBuffer[2];
		}
		// horizontal line of 4
		else if ((m_pBoardBuffer[3] == m_pBoardBuffer[4]) && (m_pBoardBuffer[3] == m_pBoardBuffer[5])) {
			winner = m_pBoardBuffer[3];
		}
		// horizontal line of 7
		else if ((m_pBoardBuffer[6] == m_pBoardBuffer[7]) && (m_pBoardBuffer[6] == m_pBoardBuffer[8])) {
			winner = m_pBoardBuffer[6];
		}
		else { winner = '0'; }

		if (winner == playerPiece) {
			return -10;
		}
		else if (winner == computerPiece) {
			return 10;
		}
		else { return 0; }
	}
}