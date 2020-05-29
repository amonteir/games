#include "Screen.h"

namespace angelogames {

	Screen::Screen() {

		m_window = nullptr;
		m_renderer = nullptr;

		for (int i = 0; i < m_N_TEXTURES_MAINMENU; i++) {
			m_texturesMainMenu[i] = nullptr;
			m_texturesMainMenuWidth[i] = -1;
			m_texturesMainMenuHeight[i] = -1;
		}

		m_difficulty = -1;

		if (!init())
			std::cout << "Failed to initialize!" << std::endl;

	}

	Screen::~Screen() {

		for (int i = 0; i < m_N_TEXTURES_MAINMENU; i++) {
			m_texturesMainMenu[i] = nullptr;
		}

		m_textureBoard = NULL;
		SDL_DestroyTexture(m_textureBoard);
		m_textureXPiece = NULL;
		SDL_DestroyTexture(m_textureXPiece);
		m_textureOPiece = NULL;
		SDL_DestroyTexture(m_textureOPiece);

		m_renderer = NULL;
		SDL_DestroyRenderer(m_renderer);
		m_window = NULL;
		SDL_DestroyWindow(m_window);

		//Quit SDL subsystems
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	bool Screen::init() {

		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
			}

			//Create window
			m_window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (m_window == nullptr)
			{
				std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Create renderer for window
				m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (m_renderer == nullptr) {
					std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int image_flags = IMG_INIT_PNG;
					// load support for the JPG and PNG image formats
					int flags = IMG_INIT_JPG | IMG_INIT_PNG;
					int initted = IMG_Init(flags);
					if ((initted & flags) != flags) {
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}

					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					}
					if (!loadMainMenu())
						success = false;

					if (!loadGameBoard())
						success = false;

				}
			}
		}
		return success;
	}

	bool Screen::loadMainMenu() {
		//Loading success flag
		bool success = true;

		//Open the font
		TTF_Font* font = TTF_OpenFont("Open_Sans/OpenSans-Light.ttf", 28);
		if (font == nullptr){
			std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
			success = false;
		}
		else{
			//Render text
			SDL_Color textColor = { 0, 0, 0 };

			std::string mainMenuMessage = "Welcome to Tic Tac Toe";
			if (!createTextureFromText(mainMenuMessage, textColor, font)) {
				printf("Failed to render text texture!\n");
				success = false;
			}

			mainMenuMessage = "Choose difficulty";
			if (!createTextureFromText(mainMenuMessage, textColor, font)){
				printf("Failed to render text texture!\n");
				success = false;
			}
			mainMenuMessage = "Easy";
			if (!createTextureFromText(mainMenuMessage, textColor, font)){
				printf("Failed to render text texture!\n");
				success = false;
			}
			mainMenuMessage = "Hard";
			if (!createTextureFromText(mainMenuMessage, textColor, font)){
				printf("Failed to render text texture!\n");
				success = false;
			}
			mainMenuMessage = "Quit";
			if (!createTextureFromText(mainMenuMessage, textColor, font)){
				printf("Failed to render text texture!\n");
				success = false;
			}
		}

		TTF_CloseFont(font); // do i need this here?

		return success;
	}

	bool Screen::createTextureFromText(std::string textToTexture, SDL_Color textColor, TTF_Font* font) {
		//Loading success flag
		bool success = true;

		//Render text surface
		//SDL_Surface* textSurface = TTF_RenderText_Solid(font, textToTexture.c_str(), textColor);
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, textToTexture.c_str(), textColor);
		if (textSurface == nullptr)
		{
			std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create texture from surface pixels
			for (int i = 0; i < m_N_TEXTURES_MAINMENU; i++) {
				if (m_texturesMainMenu[i] == nullptr) {
					m_texturesMainMenu[i] = SDL_CreateTextureFromSurface(m_renderer, textSurface);
					//get image dimensions
					m_texturesMainMenuWidth[i] = textSurface->w;
					m_texturesMainMenuHeight[i] = textSurface->h;
					break;
				}
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		return success;
	}

	int Screen::renderMainMenu(SDL_Rect* clip, double angle, SDL_Point* center) {

		reset();

		for (int i = 0; i < m_N_TEXTURES_MAINMENU; i++) {
			if (m_texturesMainMenu[i] != nullptr) {

				int x = (m_SCREEN_WIDTH - m_texturesMainMenuWidth[i]) / 2;

				//Set rendering space and render to screen
				SDL_Rect renderQuad = { x, mainMenuYs[i], m_texturesMainMenuWidth[i], m_texturesMainMenuHeight[0] };

				//Set clip rendering dimensions
				if (clip != NULL)
				{
					renderQuad.w = clip->w;
					renderQuad.h = clip->h;
				}

				//Render to screen
				SDL_RenderCopyEx(m_renderer, m_texturesMainMenu[i], clip, &renderQuad, angle, center, SDL_FLIP_NONE);
				SDL_RenderPresent(m_renderer);

			}
		}

		bool quit = false;

		SDL_Event ev;

		while (!quit) {
			//Handle events on queue
			while (SDL_PollEvent(&ev) != 0)
			{
				//User requests quit
				if (ev.type == SDL_QUIT)
				{
					quit = true;
				}

				m_difficulty = mainMenuEventHandler(&ev);

				if (m_difficulty == EASY || m_difficulty == HARD || m_difficulty == QUIT)
					quit = true;

			}
		}

		return m_difficulty;
	}

	int Screen::mainMenuEventHandler(SDL_Event* e) {

		//If mouse event happened
		if (e->type == SDL_MOUSEBUTTONUP) {

			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			// easy
			if (y >= mainMenuYs[2] && y <= (mainMenuYs[2] + 35))
				if (x >= m_SCREEN_WIDTH / 3 && x <= 2 * m_SCREEN_WIDTH / 3)
					return EASY;

			// hard
			if (y >= mainMenuYs[3] && y <= (mainMenuYs[3] + 35))
				if (x >= m_SCREEN_WIDTH / 3 && x <= 2 * m_SCREEN_WIDTH / 3)
					return HARD;

			// quit
			if (y >= mainMenuYs[4] && y <= (mainMenuYs[4] + 35))
				if (x >= m_SCREEN_WIDTH / 3 && x <= 2 * m_SCREEN_WIDTH / 3)
					return QUIT;

		}
		return NO_OPTION;
	}

	bool Screen::loadGameBoard() {

		//Loading success flag
		bool success = true;

		//Load PNG texture
		m_textureBoard = loadTexture(PATH_BOARD_PNG);

		if (m_textureBoard == NULL) {
			std::cout << "Error loading texture" << std::endl;
			success = false;
		}

		// load piece textures to memory to be used by the render when player or computer plays
		m_textureXPiece = loadTexture(PATH_X_PIECE_PNG);
		if (m_textureXPiece == NULL){
			printf("Failed to load texture image!\n");
		success = false;
		}

		m_textureOPiece = loadTexture(PATH_O_PIECE_PNG);
		if (m_textureOPiece == NULL){
			printf("Failed to load texture image!\n");
			success = false;
		}
		return success;

	}

	void Screen::renderGameBoard() {

		reset();

		SDL_RenderCopy(m_renderer, m_textureBoard, NULL, NULL);
		SDL_RenderPresent(m_renderer);

		// game's event handler is called in the game loop outside this class
	}
	

	SDL_Texture* Screen::loadTexture(std::string path) {

		//The final texture
		SDL_Texture* newTexture = NULL;
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == NULL)
			std::cout << "Error" << std::endl;
		else {
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);

			if (newTexture == NULL)
				std::cout << "Error" << std::endl;

			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	// 
	SDL_Rect Screen::calculateRectangle(int position) {
		SDL_Rect stretchRect = { 0, 0, 0, 0 };

		// this code is specific to the tic tac toe board layout
		switch (position) {
		case 1:
			stretchRect.x = 0;
			stretchRect.y = 0;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 2:
			stretchRect.x = m_SCREEN_WIDTH / 3;
			stretchRect.y = 0;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 3:
			stretchRect.x = 2 * m_SCREEN_WIDTH / 3;
			stretchRect.y = 0;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 4:
			stretchRect.x = 0;
			stretchRect.y = m_SCREEN_HEIGHT / 3;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 5:
			stretchRect.x = m_SCREEN_WIDTH / 3;
			stretchRect.y = m_SCREEN_HEIGHT / 3;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 6:
			stretchRect.x = 2 * m_SCREEN_WIDTH / 3;
			stretchRect.y = m_SCREEN_HEIGHT / 3;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 7:
			stretchRect.x = 0;
			stretchRect.y = 2 * m_SCREEN_HEIGHT / 3;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 8:
			stretchRect.x = m_SCREEN_WIDTH / 3;
			stretchRect.y = 2 * m_SCREEN_HEIGHT / 3;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		case 9:
			stretchRect.x = 2 * m_SCREEN_WIDTH / 3;
			stretchRect.y = 2 * m_SCREEN_HEIGHT / 3;
			stretchRect.w = m_SCREEN_WIDTH / 3;
			stretchRect.h = m_SCREEN_HEIGHT / 3;
			break;
		}

		return stretchRect;
	}

	int Screen::gameEventHandler(SDL_Event* event) {

		int pixelsOffset = 10;
		int boardPosition = -1;

		//If mouse event happened
		if (event->type == SDL_MOUSEBUTTONUP) {

			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			// check position of the mouse in the board and saves the position value in local boardPosition variable
			if (y >= 0 && y <= (m_SCREEN_HEIGHT / 3 + pixelsOffset)) {
				if ((x >= pixelsOffset) && (x <= (m_SCREEN_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 1;
				}
				else if ((x >= m_SCREEN_WIDTH / 3 + pixelsOffset) && (x <= (2 * m_SCREEN_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 2;
				}
				else if ((x >= 2 * m_SCREEN_WIDTH / 3 + pixelsOffset) && (x <= (m_SCREEN_WIDTH - pixelsOffset))) {
					boardPosition = 3;
				}
				else { boardPosition = -1; }
			}
			else if (y >= (m_SCREEN_HEIGHT / 3 + pixelsOffset) && y <= (2 * m_SCREEN_HEIGHT / 3 - pixelsOffset)) {
				if ((x >= pixelsOffset) && (x <= (m_SCREEN_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 4;
				}
				else if ((x >= m_SCREEN_WIDTH / 3 + pixelsOffset) && (x <= (2 * m_SCREEN_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 5;
				}
				else if ((x >= 2 * m_SCREEN_WIDTH / 3 + pixelsOffset) && (x <= (m_SCREEN_WIDTH - pixelsOffset))) {
					boardPosition = 6;
				}
				else { boardPosition = -1; }
			}
			else if (y >= (2 * m_SCREEN_HEIGHT / 3 + pixelsOffset) && y <= (m_SCREEN_HEIGHT - pixelsOffset)) {
				if ((x >= pixelsOffset) && (x <= (m_SCREEN_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 7;
				}
				else if ((x >= m_SCREEN_WIDTH / 3 + pixelsOffset) && (x <= (2 * m_SCREEN_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 8;
				}
				else if ((x >= 2 * m_SCREEN_WIDTH / 3 + pixelsOffset) && (x <= (m_SCREEN_WIDTH - pixelsOffset))) {
					boardPosition = 9;
				}
				else { boardPosition = -1; }
			}
			else { boardPosition = -1; }
		}
		
		return boardPosition;
		
	}

	void Screen::renderBoardPiece(int boardPosition, std::string player) {

		SDL_Rect stretchRect = calculateRectangle(boardPosition); // obtains the coords for the board position picked by the player

		if (player == "human")
			SDL_RenderCopy(m_renderer, m_textureXPiece, NULL, &stretchRect);
		if (player == "computer")
			SDL_RenderCopy(m_renderer, m_textureOPiece, NULL, &stretchRect);
		
		SDL_RenderPresent(m_renderer);
	}

	void Screen::reset() {
		//reset renderer color
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		/* Clear the entire screen to our selected color. */
		SDL_RenderClear(m_renderer);
		SDL_RenderPresent(m_renderer);

	}
}