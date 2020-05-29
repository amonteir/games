#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

namespace angelogames {

	class Screen
	{
	private:
		const int m_SCREEN_WIDTH = 600;
		const int m_SCREEN_HEIGHT = 600;

		static const int m_N_TEXTURES_MAINMENU = 5;
		const int mainMenuYs[m_N_TEXTURES_MAINMENU] = { 100, 180, 230, 280, 360 };

		const std::string PATH_BOARD_PNG = "img/grey_bg.png";
		const std::string PATH_X_PIECE_PNG = "img/spider_resized.png";
		const std::string PATH_O_PIECE_PNG = "img/fortnite-oblivion_resized.png";

		SDL_Window* m_window; //The window we'll be rendering to
		SDL_Renderer* m_renderer; //The window renderer

		SDL_Texture* m_textureBoard;
		SDL_Texture* m_textureXPiece;
		SDL_Texture* m_textureOPiece;

		// Texture arrays
		SDL_Texture* m_texturesMainMenu[m_N_TEXTURES_MAINMENU]; // holds the textures for the main menu
		int m_texturesMainMenuWidth[m_N_TEXTURES_MAINMENU];
		int m_texturesMainMenuHeight[m_N_TEXTURES_MAINMENU];

	public:
		const enum MainMenuOptions { NO_OPTION, EASY, HARD, QUIT };
		int m_difficulty;

	private:
		bool init();
		SDL_Texture* loadTexture(std::string path);
		bool createTextureFromText(std::string textToTexture, SDL_Color textColor, TTF_Font* font);
		
		SDL_Rect calculateRectangle(int position); // returns the coords of each square in the board
		int mainMenuEventHandler(SDL_Event* event);
		void reset();
		bool loadGameBoard();
		bool loadMainMenu();
		

	public:
		Screen();
		virtual ~Screen();
		int renderMainMenu(SDL_Rect* clip, double angle, SDL_Point* center);
		void renderGameBoard();
		void renderBoardPiece(int boardPosition, std::string player);
		int gameEventHandler(SDL_Event* event); // returns the position that the player wants to make in the board
	};

}