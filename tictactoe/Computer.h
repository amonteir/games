#pragma once

namespace angelogames {
	class Computer
	{
	private:
		int m_difficulty; 
		const char m_computerPiece = 'O';

	public:
		Computer();
		Computer(int difficulty);
		virtual ~Computer() {};
		void setDifficulty(int level);
		void calculateMove(char* pBoardBuffer, int boardSize, char playerPiece); // writes computer's position in the board
		char getComputerPiece() { return m_computerPiece; }
		int minimax(char* pBoardBuffer, int depth, bool isMax);
	};

}