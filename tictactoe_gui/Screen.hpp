#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <tuple>
#include <stdexcept>
#include <stack>
#include <array>
#include "Logging.hpp"

namespace angelogames {

	class Screen
	{
	private:
		const static int m_SCREEN_WIDTH = 1024;
		const static int m_SCREEN_HEIGHT = 768;
		const static int m_BOARD_WIDTH = 600;
		const static int m_BOARD_HEIGHT = 600;

		const std::string PATH_MENU_BG_JPG = "img/buttons-close-up-controller-dark-596750.jpg";
		const std::string PATH_BOARD_PNG = "img/1024x768-black-solid-color-background.jpg";
		const std::string PATH_X_PIECE_PNG = "img/player.png";
		const std::string PATH_O_PIECE_PNG = "img/computer.png";

		SDL_Window* m_window; //The window we'll be rendering to
		SDL_Renderer* m_renderer; //The window renderer

		SDL_Texture* m_textureMainMenuBackground;
		SDL_Texture* m_textureBoard;
		SDL_Texture* m_textureXPiece;
		SDL_Texture* m_textureOPiece;

		// array of tuples that stores the information to be rendered the menus
		// string = the text we want to render, texture, x, y, w, h
		std::array<std::tuple<std::string, SDL_Texture*, int, int, int, int>, 4> m_mainMenuTextData;
		std::array<std::tuple<std::string, SDL_Texture*, int, int, int, int>, 5> m_optionsMenuTextData;

		Mix_Chunk* m_sound;

		Logging* log;

	public:
		const enum class MainMenu { GAME_NAME, PLAY, OPTIONS, QUIT, Count};
		const enum class OptionsMenu { BACK, DIFFICULTY, EASY, MEDIUM, HARD, Count};


	private:
		bool init();
		SDL_Texture* loadTexture(std::string path);
		SDL_Texture* createTextureFromText(std::string textToTexture, TTF_Font* font, SDL_Color textColour, int* textureWidth, int* textureHeight);
		
		SDL_Rect getPlayerMove(int position); // returns the coords of each square in the board
		
		void reset();
		bool loadGameBoard();
		bool loadMainMenu();
		void createMainMenuTuples(TTF_Font* font, SDL_Color textColour);
		void createOptionsMenuTuples(TTF_Font* font, SDL_Color textColour);

		
		
	public:
		Screen();
		virtual ~Screen();
		void renderMainMenu(SDL_Rect* clip, double angle, SDL_Point* center);
		void renderOptionsMenu(SDL_Rect* clip, double angle, SDL_Point* center);
		void renderGameBoard();
		void renderBoardPiece(int boardPosition, std::string player);
		int optionsMenuEventHandler(SDL_Event* event, int currentGameDifficulty);
		int mainMenuEventHandler(SDL_Event* event);
		int gameEventHandler(SDL_Event* event); // returns the position that the player wants to make in the board
		void renderResults(int result);
		void playSound(std::string sound);
	};

}