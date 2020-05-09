#pragma once
#include <iostream>
#include "Player.h"
#include "Computer.h"
#include "Board.h"

namespace angelogames {
	class Tictactoe
	{
	private:
		void showMainMenu();
		void resetGame();

	public:
		// this class contains a pointer to each element of the game: the player,
		// the human and the board itself
		Player* human;
		Computer* computer;
		Board* board;

	public:
		Tictactoe();
		virtual ~Tictactoe();
		void play();
	};

}


