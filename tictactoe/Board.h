#pragma once
//#include <string.h>

namespace angelogames {
	class Board
	{

	private:
		const int BOARD_ROWS = 3;
		const int BOARD_COLS = 5;
		int m_boardSize = BOARD_ROWS * BOARD_COLS;

	public:
		char* pBoardBuffer = new char[BOARD_ROWS * BOARD_COLS];
		int MAX_MOVES;

		//char* pLastElementBoardBuffer = &pBoardBuffer[BOARD_ROWS * BOARD_COLS];

	public:
		Board();
		virtual ~Board();
		void print();
		void createPlayerMove(int position, char piece);
		int getBoardSize() { return m_boardSize; }
		bool validatePlayerMove(int playerMove);
		char checkWinner();
	};
}
