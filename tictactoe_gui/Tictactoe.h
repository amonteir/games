#pragma once
#include <iostream>
#include "Player.h"
#include "Computer.h"
#include "Board.h"
#include "Screen.h"

namespace angelogames {
	class Tictactoe
	{
	private:
		const enum class GameState { PLAY, MAINMENU, OPTIONSMENU, QUIT };
		std::stack<int> gameStack; // this stack is used to keep track of the current and previous states of the game (play or menus)

		const enum class PlayerResult {WON, LOST, DRAW };

	public:
		// this class contains a pointer to each element of the game: the player,
		// the human, the board and SDL2 game window
		Player* human;
		Computer* computer;
		Board* board;
		Screen* screen;

	private:
		void restart();

	public:
		Tictactoe();
		virtual ~Tictactoe();
		void play();
	};

}


