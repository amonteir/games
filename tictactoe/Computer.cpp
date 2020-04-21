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

	void Computer::calculateMove(char* pBoardBuffer, int boardSize) {

		switch (m_difficulty) {
		case 0:
			for (int i = 0; i < boardSize; i++) {

				if ((pBoardBuffer[i] != '|') && (pBoardBuffer[i] != 'X') && (pBoardBuffer[i] != m_computerPiece)) {
					// set next available position
					pBoardBuffer[i] = m_computerPiece;
					//std::cout << std::endl << pBoardBuffer[i] << std::endl;
					break;
				}

			}
			break;
		
		case 1:

			// to do with rand

			int availablePositions[9] = { -1 };
			int position = 0;

			for (int i = 0; i < boardSize; i++) {

				if ((pBoardBuffer[i] != '|') && (pBoardBuffer[i] != 'X') && (pBoardBuffer[i] != m_computerPiece)) {
					// set next available position
					pBoardBuffer[i] = m_computerPiece;
					//std::cout << std::endl << pBoardBuffer[i] << std::endl;
					break;
				}

			}
			break;
		}
	}
	void Computer::setDifficulty(int level) {
		m_difficulty = level;
	}
	
}