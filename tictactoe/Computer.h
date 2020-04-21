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
		void calculateMove(char* pBoardBuffer, int boardSize); // returns position to be written in the board
		char getComputerPiece() { return m_computerPiece; }
	};

}