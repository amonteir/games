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

		//char* pLastElementBoardBuffer = &pBoardBuffer[BOARD_ROWS * BOARD_COLS];

	public:
		Board();
		virtual ~Board();
		void print();
		void createPlayerMove(int position, char piece);
		int getBoardSize() { return m_boardSize; }
		int getBoardRows() { return BOARD_ROWS; }
		int getBoardCols() { return BOARD_COLS; }
		bool validatePlayerMove(int playerMove);
		bool checkWinner(char playerPiece, char computerPiece);
		int evaluateMinimaxWinnerCondition(char playerPiece, char computerPiece);
		bool checkBoardFull();
	};
}

