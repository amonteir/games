#include "Computer.h"

namespace angelogames {

	Computer::Computer() {
		// init computer

		m_difficulty = 0;
		m_bestMinimaxVal = -100; // minimax infinity
        m_bestMove = -1;
        m_board = new Board();
	
	}

	Computer::Computer(int difficulty) {
		m_difficulty = difficulty;
		m_bestMinimaxVal = -100; // minimax infinity
		m_bestMove = -1;
        m_board = new Board();
	}

    Computer::~Computer() {
        delete m_board;
    }

    void Computer::setDifficulty(int level) {
        m_difficulty = level;
    }

	void Computer::calculateBestMove(char playerPiece) {

		switch (m_difficulty) {
		// computer plays the next position available in the board
        case 0:
			for (int i = 0; i < m_board->getBoardSize(); i++) {

				if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) {
					// set next available position
                    m_board->m_pBoardBuffer[i] = m_computerPiece;
                    --m_board->m_boardDepth; // update depth of the board ie available moves
					break;
				}
			}
			break;
		
        // computer uses minimax to compute best move
		case 1:
            int boardSize = m_board->getBoardSize();         
            int depth = m_board->m_boardDepth - 1;

            // run minimax in all empty positions and plays the optimal position
			for (int i = 0; i < boardSize; i++) {
				if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
					
                    // let's try this position
                    m_board->m_pBoardBuffer[i] = m_computerPiece;
                    
                    // compute evaluation minimax function for this move
                    // we let the player's minimax test move go first because this loop already goes through the possible
                    // options for this depth of the game
					int moveVal = minimax(&depth, false, playerPiece);

					// revert move
                    m_board->m_pBoardBuffer[i] = '0' + i + 1;

					if (moveVal > m_bestMinimaxVal) {
						m_bestMove = i;
						m_bestMinimaxVal = moveVal;                        
					}

				}

			}
            // computer plays optimal move
            m_board->m_pBoardBuffer[m_bestMove] = m_computerPiece;
            m_bestMinimaxVal = -100; // reset best minimax value
            --m_board->m_boardDepth; // update depth of the board ie available moves
            break;

            
		}
	}

    // Minimax function. Computes the optimal move for a maximiser
	int Computer::minimax(int* depth, bool maximizingPlayer, char playerPiece) {

       int minimaxValue = m_board->evaluateMinimaxWinnerCondition(playerPiece, m_computerPiece);

        // If Maximiser (ie computer) has won the game, then return +1
        // If Minimiser (ie player) has won the game, then returns -1
        if (minimaxValue == 1) {
            minimaxValue += *depth;
            //++* depth;
            return minimaxValue;
        }
        if(minimaxValue == -1) {
            minimaxValue -= *depth;
            //++* depth;
            return minimaxValue;
        }
        
        // depth is exhausted, return the best score known
        if (*depth == 0) {
            if (maximizingPlayer) { // previous depth was minimiser so depth ADDS to minimaxValue
                    minimaxValue = 0 + *depth;
              //      ++* depth;
                    return minimaxValue;
            }
            else { // previous depth was maximiser so depth SUBTRACTS from minimaxValue
                minimaxValue = 0 - *depth;
                //++* depth;
                return minimaxValue;
            } // board is full and it's a draw
        }

        // If this maximizer's move; THE COMPUTER who i want to win here
        if (maximizingPlayer){
            int utility = -100;
            int boardSize = m_board->getBoardSize();
            --* depth; // update depth cos maximiser is going to play a test move now

            // Traverse all cells 
            for (int i = 0; i < boardSize; i++){
                // Check if cell is empty 
                if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available    
                    
                    
                    // play test move
                    m_board->m_pBoardBuffer[i] = m_computerPiece;

                    // Call minimax recursively and choose the maximum value 
                    utility = std::max(utility, minimax(depth, !maximizingPlayer, playerPiece));
                    
                    // Undo the move 
                    m_board->m_pBoardBuffer[i] = '0' + (i + 1);
                }
            }
            
            ++* depth; // going one level up in depth so need to increment it
            return utility;
        }
        // If this minimizer's move; THE PLAYER
        else{
            int utility = 100;
            int boardSize = m_board->getBoardSize();
            --* depth; // update depth cos minimiser is going to play a test move now

            // Traverse all cells 
            for (int i = 0; i < boardSize; i++) {
                // Check if cell is empty 
                if ((m_board->m_pBoardBuffer[i] != playerPiece) && (m_board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
                    
                    
                    // play test move 
                    m_board->m_pBoardBuffer[i] = playerPiece;

                    
                    // Call minimax recursively and choose the minimum value 
                    utility = std::min(utility,minimax(depth, !maximizingPlayer, playerPiece));
                    
                    // Undo the move 
                    m_board->m_pBoardBuffer[i] = '0' + (i + 1);
                }
            }
           
            ++* depth; // going one level up in depth so need to increment it
            return utility;
        }
	}
}