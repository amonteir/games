#pragma once
#include <algorithm>
#include "Board.h"

namespace angelogames {
	class Computer
	{
	private:
		int m_difficulty; 
		const char m_computerPiece = 'O';
		int m_bestMinimaxVal;
		int m_bestMove;

	private:
		int minimax(Board* board, int* depth, bool isMax, char playerPiece);

	public:
		Computer(int difficulty);
		virtual ~Computer();
		void reset();
		void setDifficulty(int level);
		int calculateBestMove(Board* board, char playerPiece); // writes computer's position in the board and returns position for screen rendering
		char getComputerPiece() { return m_computerPiece; }
	};

}