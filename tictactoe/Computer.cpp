#include "Computer.h"
//#include <iostream>

namespace angelogames {

	Computer::Computer() {
		// init computer

		m_difficulty = 0;
	
	}

	Computer::Computer(int difficulty) {
		m_difficulty = difficulty;
	}

	void Computer::calculateMove(char* pBoardBuffer, int boardSize, char playerPiece) {

		switch (m_difficulty) {
		case 0:
			for (int i = 0; i < boardSize; i++) {

				if ((pBoardBuffer[i] != playerPiece) && (pBoardBuffer[i] != m_computerPiece)) {
					// set next available position
					pBoardBuffer[i] = m_computerPiece;
					//std::cout << std::endl << pBoardBuffer[i] << std::endl;
					break;
				}
			}
			break;
		
		case 1:

			// to do with minimax

			break;
		}
	}
	void Computer::setDifficulty(int level) {
		m_difficulty = level;
	}
	
	int minimax(char* pBoardBuffer, int depth, bool isMax) {

		//int score = 

	}


}