#pragma once
//#include <string.h>

namespace angelogames {
	class Board
	{

	private:
		const int BOARD_ROWS = 3;
		const int BOARD_COLS = 3;
		unsigned int m_boardSize = BOARD_ROWS * BOARD_COLS;

	public:
		char* m_pBoardBuffer = new char[m_boardSize];
		int m_boardDepth;

	public:
		Board();
		virtual ~Board();
		void reset();
		void print();
		void createPlayerMove(int position, char piece);
		int getBoardSize() { return m_boardSize; }
		bool validatePlayerMove(int playerMove);
		int evaluateWinCondition(char playerPiece, char computerPiece);
		void generateTestBoard();
	};
}

