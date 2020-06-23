#include "Computer.hpp"

namespace angelogames {

	Computer::Computer(int difficulty) {
		m_difficulty = difficulty;
		m_bestMinimaxVal = -100; // minimax infinity
		m_bestMove = -1;
	}

    Computer::~Computer() {}

    void Computer::reset() {
        m_bestMinimaxVal = -100; // minimax infinity
        m_bestMove = -1;

    }

    void Computer::setDifficulty(int level) {
        m_difficulty = level;
    }

	int Computer::calculateBestMove(Board* board, char playerPiece) {

		// computer plays the next position available in the board
        if (m_difficulty == (int)Difficulty::EASY) {
            int i;
            for (i = 0; i < board->getBoardSize(); i++) {

                if ((board->m_pBoardBuffer[i] != playerPiece) && (board->m_pBoardBuffer[i] != m_computerPiece)) {
                    // set next available position
                    board->m_pBoardBuffer[i] = m_computerPiece;
                    --board->m_boardDepth; // update depth of the board ie available moves
                    break;
                }
            }

            return i + 1; // screen consumes 1-9 and not 0-8 as board positions
        }

        // computer uses minimax to compute best move
        else{ 
            int depth = -1;
            int boardSize = -1;

            boardSize = board->getBoardSize();

            if (m_difficulty == (int)Difficulty::MEDIUM) {
                if (board->m_boardDepth > 2)
                    depth = 2;
                else
                    depth = board->m_boardDepth - 1;
            }
            else if (m_difficulty == (int)Difficulty::HARD)
                depth = board->m_boardDepth - 1;
            

            // run minimax in all empty positions and plays the optimal position
            // max at the top level is done with the if at the bottom of the for loop
			for (int i = 0; i < boardSize; i++) {
				if ((board->m_pBoardBuffer[i] != playerPiece) && (board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
					
                    // let's try this position
                    board->m_pBoardBuffer[i] = m_computerPiece;
                    
                    // compute evaluation minimax function for this move
                    // we let the player's minimax test move go first because this loop already goes through the possible
                    // options for this depth of the game
					int moveVal = minimax(board, &depth, false, playerPiece);

					// revert move
                    board->m_pBoardBuffer[i] = '0' + i + 1;

                    // top maximiser computation
					if (moveVal > m_bestMinimaxVal) {
						m_bestMove = i;
						m_bestMinimaxVal = moveVal;                        
					}
				}
			}
            // computer plays optimal move
            board->m_pBoardBuffer[m_bestMove] = m_computerPiece;
            --board->m_boardDepth; // update depth of the board ie available moves
            int bestMove = m_bestMove;
            reset(); // reset the computer ie the next time this function is called previous computed data move should not be there

            return bestMove + 1; // screen consumes 1-9 and not 0-8 as board positions
		}
        return -1;
	}

    // Minimax function. Computes the optimal move for a maximiser
	int Computer::minimax(Board* board, int* depth, bool maximizingPlayer, char playerPiece) {

       int minimaxValue = board->evaluateWinCondition(playerPiece, m_computerPiece);

        // If Maximiser (ie computer) has won the game, then return +1
        // If Minimiser (ie player) has won the game, then returns -1
        if (minimaxValue == 1) {
            minimaxValue += *depth;
            return minimaxValue;
        }
        if(minimaxValue == -1) {
            minimaxValue -= *depth;
            return minimaxValue;
        }
        
        // depth is exhausted, return the best score known
        if (*depth == 0) {
            if (maximizingPlayer) { // previous depth was minimiser so depth ADDS to minimaxValue
                    minimaxValue = 0 + *depth;
                    return minimaxValue;
            }
            else { // previous depth was maximiser so depth SUBTRACTS from minimaxValue
                minimaxValue = 0 - *depth;
                return minimaxValue;
            } // board is full and it's a draw
        }

        // If this maximizer's move; THE COMPUTER who i want to win here
        if (maximizingPlayer){
            int utility = -100;
            int boardSize = board->getBoardSize();
            --* depth; // update depth cos maximiser is going to play a test move now

            // Traverse all cells 
            for (int i = 0; i < boardSize; i++){
                // Check if cell is empty 
                if ((board->m_pBoardBuffer[i] != playerPiece) && (board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available    
                    
                    // play test move
                    board->m_pBoardBuffer[i] = m_computerPiece;

                    // Call minimax recursively and choose the maximum value 
                    utility = std::max(utility, minimax(board, depth, !maximizingPlayer, playerPiece));
                    
                    // Undo the test move 
                    board->m_pBoardBuffer[i] = '0' + (i + 1);
                }
            }
            
            ++* depth; // going one level up in depth so need to increment it
            return utility;
        }
        // If this minimizer's move; THE PLAYER
        else{
            int utility = 100;
            int boardSize = board->getBoardSize();
            --* depth; // update depth cos minimiser is going to play a test move now

            // Traverse all cells 
            for (int i = 0; i < boardSize; i++) {
                // Check if cell is empty 
                if ((board->m_pBoardBuffer[i] != playerPiece) && (board->m_pBoardBuffer[i] != m_computerPiece)) { // if position available
                    
                    // play test move 
                    board->m_pBoardBuffer[i] = playerPiece;

                    // Call minimax recursively and choose the minimum value 
                    utility = std::min(utility,minimax(board, depth, !maximizingPlayer, playerPiece));
                    
                    // Undo the test move 
                    board->m_pBoardBuffer[i] = '0' + (i + 1);
                }
            }
           
            ++* depth; // going one level up in depth so need to increment it
            return utility;
        }
	}
}