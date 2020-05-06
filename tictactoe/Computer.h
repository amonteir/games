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
		Board* m_board; // computer has to know about the board

	public:
		Computer();
		Computer(int difficulty);
		virtual ~Computer();
		void setDifficulty(int level);
		void calculateBestMove(char playerPiece); // writes computer's position in the board
		char getComputerPiece() { return m_computerPiece; }
		int minimax(int* depth, bool isMax, char playerPiece);
		Board* getBoard() { return m_board; }
	};

}