#include "Computer.h"

namespace angelogames {

	Computer::Computer() {
		// init computer

		m_difficulty = 0;
		m_bestMinimaxVal = -1000;
		m_bestMove = -1;

        m_board = new Board();
	
	}

	Computer::Computer(int difficulty) {
		m_difficulty = difficulty;
		m_bestMinimaxVal = -1000;
		m_bestMove = -1;
        m_board = new Board();
	}

    Computer::~Computer() {
        delete m_board;
    }

	void Computer::calculateBestMove(char playerPiece) {

		switch (m_difficulty) {
		case 0:
			for (int i = 0; i < m_board->getBoardSize(); i++) {

				if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) {
					// set next available position
                    m_board->m_pBoardBuffer[i] = m_computerPiece;
					//std::cout << std::endl << m_pBoardBuffer[i] << std::endl;
					break;
				}
			}
			break;
		
		case 1:

            // run minimax in all empty positions and plays the optimal position
			for (int i = 0; i < m_board->getBoardSize(); i++) {

				if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
					
					// save char
					//char temp = m_board->m_pBoardBuffer[i];
					// make the move
                    //m_board->m_pBoardBuffer[i] = m_computerPiece;

					// compute evaluation minimax function for this move
					int moveVal = minimax(m_board->getBoardSize - 1, true, playerPiece);

					// put back initial char
                    //m_board->m_pBoardBuffer[i] = temp;

					if (moveVal > m_bestMinimaxVal) {
						m_bestMove = i;
						m_bestMinimaxVal = moveVal;
						// play computer's best move
                        
					}

				}

			}
            // computer plays optimal move
            m_board->m_pBoardBuffer[m_bestMove] = m_computerPiece;
			break;
		}
	}

	void Computer::setDifficulty(int level) {
		m_difficulty = level;
	}
	
	int Computer::minimax(int depth, bool isMax, char playerPiece) {

        int score = m_board->evaluateWinner(playerPiece, m_computerPiece);

        // dont think i need depth cos the base condition is when someone wins, so depth is max in a way. plus the for inside is locked to
        //if (depth == 0) {
            // reached the maximum of depth
            //return 0;
        //}

        // If Maximiser (computer, 10) or Minimiser (player, -10) won the game return evaluated score 
        if (score == 10 || score == -10) { return score; }


        // If this maximizer's move; THE COMPUTER
        if (isMax){
            int best = -1000;

            // Traverse all cells 
            for (int i = 0; i < m_board->getBoardSize(); i++){
                // Check if cell is empty 
                if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
                        
                    // save character in position of the board
                    char temp = '0' + i + 1;

                    // Make the test move 
                    m_board->m_pBoardBuffer[i] = m_computerPiece;
                    // Call minimax recursively and choose the maximum value 
                    best = std::max(best, minimax(depth - 1, !isMax, playerPiece));
                    // Undo the move 
                    m_board->m_pBoardBuffer[i] = temp;
                }
                
            }
            return best;
        }

        // If this minimizer's move; THE PLAYER
        else
        {
            int best = 1000;

            // Traverse all cells 
            for (int i = 0; i < m_board->getBoardSize(); i++) {

                // Check if cell is empty 
                if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
                
                    // save position
                    char temp = m_board->m_pBoardBuffer[i];
                    // Make the test move 
                    m_board->m_pBoardBuffer[i] = playerPiece;
                    // Call minimax recursively and choose the minimum value 
                    best = std::min(best,minimax(depth - 1, !isMax, playerPiece));
                    // Undo the move 
                    m_board->m_pBoardBuffer[i] = temp;
                }
            
            }
            return best;
        }

		return 0;
	}


}