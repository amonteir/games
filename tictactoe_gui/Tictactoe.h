#pragma once
#include <iostream>
#include "Player.h"
#include "Computer.h"
#include "Board.h"
#include "Screen.h"

namespace angelogames {
	class Tictactoe
	{
	public:
		// this class contains a pointer to each element of the game: the player,
		// the human, the board and SDL2 game window
		Player* human;
		Computer* computer;
		Board* board;
		Screen* screen;

	private:
		void resetGame(bool* quit);

	public:
		Tictactoe();
		virtual ~Tictactoe();
		void play();
	};

}


