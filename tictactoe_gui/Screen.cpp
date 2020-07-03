#include "Screen.hpp"


namespace angelogames {

	Screen::Screen() {

		log = new Logging("screen.log");

		if (!init())
			log->write("Failed to initialize screen.");

	}

	Screen::~Screen() {

		for (auto& menuOption : m_mainMenuTextData)
			std::get<1>(menuOption) = nullptr;

		m_textureMainMenuBackground = nullptr;
		SDL_DestroyTexture(m_textureMainMenuBackground);
		m_textureBoard = nullptr;
		SDL_DestroyTexture(m_textureBoard);
		m_textureXPiece = nullptr;
		SDL_DestroyTexture(m_textureXPiece);
		m_textureOPiece = nullptr;
		SDL_DestroyTexture(m_textureOPiece);

		Mix_FreeChunk(m_sound);
		m_sound = nullptr;


		m_renderer = nullptr;
		SDL_DestroyRenderer(m_renderer);
		m_window = nullptr;
		SDL_DestroyWindow(m_window);

		//Quit SDL subsystems
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		log->close();
		delete log;
		
	}

	bool Screen::init() {

		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			log->write(SDL_GetError());
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				log->write("Warning: Linear texture filtering not enabled!");
			}

			//Create window
			m_window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (m_window == nullptr)
			{
				log->write(SDL_GetError());
				success = false;
			}
			else{
				//Create renderer for window
				m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (m_renderer == nullptr) {
					log->write(SDL_GetError());
					success = false;
				}
				else
				{

					//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 'linear');

					// set logical resolution
					//SDL_RenderSetLogicalSize(m_renderer, 1024, 768);

					//Initialize renderer color
					SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int image_flags = IMG_INIT_PNG;
					// load support for the JPG and PNG image formats
					int flags = IMG_INIT_JPG | IMG_INIT_PNG;
					int initted = IMG_Init(flags);
					if ((initted & flags) != flags) {
						log->write(IMG_GetError());
						success = false;
					}

					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						log->write(TTF_GetError());
						success = false;
					}

					if (!loadMainMenu())
						success = false;
					if (!loadGameBoard())
						success = false;

					//Initialize SDL_mixer
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						log->write(Mix_GetError());
						success = false;
					}

				}
			}
		}
		return success;
	}

	void Screen::playSound(std::string sound){
		//The sound effects that will be used
		m_sound = nullptr;

		//Load sound effects
		if (sound == "STEP_INTO_MENU")
			m_sound = Mix_LoadWAV("sounds/woosh.wav");
		else if (sound == "STEP_OUT_MENU")
			m_sound = Mix_LoadWAV("sounds/woosh.wav");
		else if (sound == "DRAW")
			m_sound = Mix_LoadWAV("sounds/vader-not-have-come-back.wav");
		else if (sound == "WON")
			m_sound = Mix_LoadWAV("sounds/won.wav");
		else if (sound == "LOST")
			m_sound = Mix_LoadWAV("sounds/jabba-the-hutt-laughing.wav");
		else if (sound == "QUIT")
			m_sound = Mix_LoadWAV("sounds/dont-do-that.wav");

		if (m_sound == nullptr)
			log->write(Mix_GetError());
		
		Mix_PlayChannel(-1, m_sound, 0);
	}


	bool Screen::loadMainMenu() {
		//Loading success flag
		bool success = true;

		//Open the font
		TTF_Font* font = TTF_OpenFont("fonts/Open_Sans/OpenSans-Light.ttf", 28);
		if (font == nullptr){
			log->write(TTF_GetError());
			success = false;
		}
		else{
			//Render text
			
			SDL_Color textColour = { 255, 255, 255 }; // white text
			
			createMainMenuTuples(font, textColour);

			createOptionsMenuTuples(font, textColour);
			
		}

		//Load main menu background
		m_textureMainMenuBackground = loadTexture(PATH_MENU_BG_JPG);
		if (m_textureMainMenuBackground == nullptr) {
			log->write("Error loading texture");
		}

		TTF_CloseFont(font); 

		return success;
	}

	void Screen::createMainMenuTuples(TTF_Font* font, SDL_Color textColour) {

		std::string text[(unsigned int)MainMenu::Count] = { "TIC TAC TOE", "Play", "Options", "Quit" };
		int x0 = 60;
		int y_coords[(unsigned int)MainMenu::Count] = { 100, 380, 430, 480 };

		for (int i = 0; i < (int)MainMenu::Count; i++) {

			int textureWidth = -1;
			int textureHeight = -1;

			SDL_Texture* newTexture = createTextureFromText(text[i], font, textColour, &textureWidth, &textureHeight);

			m_mainMenuTextData[i] = std::make_tuple(text[i],newTexture,
				x0, y_coords[i], textureWidth, textureHeight);

		}

	}

	void Screen::createOptionsMenuTuples(TTF_Font* font, SDL_Color textColour) {

		std::string text[(unsigned int)OptionsMenu::Count] = { "Back", "Difficulty", "Easy", "Medium", "Hard" };
		int x0 = 60;
		int y_coords[(unsigned int)OptionsMenu::Count] = { 380, 430, 430, 480, 530 };

		for (int i = 0; i < (int)OptionsMenu::Count; i++) {

			int textureWidth = -1;
			int textureHeight = -1;

			SDL_Texture* newTexture = createTextureFromText(text[i], font, textColour, &textureWidth, &textureHeight);

			if (i == 2)
				x0 += std::get<4>(m_optionsMenuTextData[i - 1]);

			if (i < 2)
				m_optionsMenuTextData[i] = std::make_tuple(text[i], newTexture,
					x0, y_coords[i], textureWidth, textureHeight);
			else
				m_optionsMenuTextData[i] = std::make_tuple(text[i], newTexture,
					x0 + 30, y_coords[i], textureWidth, textureHeight);

		}

	}

	SDL_Texture* Screen::createTextureFromText(std::string textToTexture, TTF_Font* font, SDL_Color textColor, int* textureWidth, int* textureHeight) {

		SDL_Texture* newTexture = nullptr;

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, textToTexture.c_str(), textColor);
		if (textSurface == nullptr)
			log->write(TTF_GetError());
		else
		{
			//Create and save texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
			//save texture dimensions
			*textureWidth = textSurface->w;
			*textureHeight = textSurface->h;
		
			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		return newTexture;
	}

	void Screen::renderMainMenu(SDL_Rect* clip, double angle, SDL_Point* center) {

		reset();

		int padding = 20;
		
		// render main menu's background image
		SDL_RenderCopy(m_renderer, m_textureMainMenuBackground, nullptr, nullptr);
		SDL_RenderPresent(m_renderer);

		//Render rectangle to hold main menu's text
		//SDL_Rect fillRect = { x - padding, mainMenuYs[1] - padding , 200, mainMenuYs[4] - mainMenuYs[1] };
		//SDL_SetRenderDrawColor(m_renderer, 0x20, 0x20, 0x20, 0xFF);
		//SDL_RenderFillRect(m_renderer, &fillRect);

		for (auto& menuData : m_mainMenuTextData) {

			if (std::get<1>(menuData) != nullptr) {

				//Set rendering space and render to screen
				// Texture's x, y, w, h
				SDL_Rect renderQuad = { std::get<2>(menuData), std::get<3>(menuData),
					std::get<4>(menuData), std::get<5>(menuData) };

				//Set clip rendering dimensions
				if (clip != nullptr)
				{
					renderQuad.w = clip->w;
					renderQuad.h = clip->h;
				}

				//Render to screen
				SDL_RenderCopyEx(m_renderer, std::get<1>(menuData), clip, &renderQuad, angle, center, SDL_FLIP_NONE);
				SDL_RenderPresent(m_renderer);

			}
			else {
				break;
			}
		}


	}

	int Screen::mainMenuEventHandler(SDL_Event* e) {

		//If mouse event happened
		if (e->type == SDL_MOUSEBUTTONUP) {

			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			// play
			auto coords = m_mainMenuTextData[1]; // tuple: 0 = text, 1 = texture, 2 = x, 3 = y, 4 = w, 5 = h
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35))
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords)))
					return int(MainMenu::PLAY);

			// options
			coords = m_mainMenuTextData[2];
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35))
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords)))
					return int(MainMenu::OPTIONS);
			// quit
			coords = m_mainMenuTextData[3];
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35))
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords)))
					return int(MainMenu::QUIT);

		}
		return -1;
	}

void Screen::renderOptionsMenu(SDL_Rect* clip, double angle, SDL_Point* center) {
		
		reset();

		int padding = 20;

		// render main menu's background image
		SDL_RenderCopy(m_renderer, m_textureMainMenuBackground, nullptr, nullptr);

		for (auto& menuData : m_optionsMenuTextData) {

			if (std::get<1>(menuData) != nullptr) {

				//Set rendering space and render to screen
				// Texture's x, y, w, h
				SDL_Rect renderQuad = { std::get<2>(menuData), std::get<3>(menuData),
					std::get<4>(menuData), std::get<5>(menuData) };

				//Set clip rendering dimensions
				if (clip != nullptr)
				{
					renderQuad.w = clip->w;
					renderQuad.h = clip->h;
				}

				//Render to screen's back buffer
				SDL_RenderCopyEx(m_renderer, std::get<1>(menuData), clip, &renderQuad, angle, center, SDL_FLIP_NONE);
				

			}
			else {
				break;
			}
		}
		SDL_RenderPresent(m_renderer); 
	}

	int Screen::optionsMenuEventHandler(SDL_Event* e, int currentGameDifficulty) {

		// highlights the current difficulty of the game
		SDL_SetRenderDrawColor(m_renderer, 0, 204, 204, 0xFF);
		auto index = -1;
		if (currentGameDifficulty == 0) // HARDCODED, TBD
			index = int(OptionsMenu::EASY);
		else if (currentGameDifficulty == 1)
			index = int(OptionsMenu::MEDIUM);
		else if (currentGameDifficulty == 2)
			index = int(OptionsMenu::HARD);

		auto y0 = std::get<3>(m_optionsMenuTextData[index]);
		auto y1 = y0 + std::get<5>(m_optionsMenuTextData[index]) + 2;
		auto x0 = std::get<2>(m_optionsMenuTextData[index]);
		auto x1 = x0 + std::get<4>(m_optionsMenuTextData[index]);

		SDL_RenderDrawLine(m_renderer, x0, y1, x1, y1);
		SDL_RenderPresent(m_renderer); // need to present it before any other events are processed
		
		// MOUSE EVENTS BEGIN
		//If mouse event happened
		if (e->type == SDL_MOUSEBUTTONUP) {

			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			// BACK
			auto coords = m_optionsMenuTextData[0]; // tuple: 0 = text, 1 = texture, 2 = x, 3 = y, 4 = w, 5 = h
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35))
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords)))
					return int(OptionsMenu::BACK);

			// difficulty - easy
			coords = m_optionsMenuTextData[(int)OptionsMenu::EASY];
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35)) {
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords))) {

					if (currentGameDifficulty != 0) { // HARDCODED - NEEDS TO BE DYNAMIC
						// highlight EASY option
						renderOptionsMenu(NULL, 0, NULL);
						SDL_SetRenderDrawColor(m_renderer, 0, 204, 204, 0xFF);
						auto y0 = std::get<3>(m_optionsMenuTextData[int(OptionsMenu::EASY)]);
						auto y1 = y0 + std::get<5>(m_optionsMenuTextData[int(OptionsMenu::EASY)]) + 2;
						auto x0 = std::get<2>(m_optionsMenuTextData[int(OptionsMenu::EASY)]);
						auto x1 = x0 + std::get<4>(m_optionsMenuTextData[int(OptionsMenu::EASY)]);

						SDL_RenderDrawLine(m_renderer, x0, y1, x1, y1);
						SDL_RenderPresent(m_renderer);
					}
					return int(OptionsMenu::EASY);
				}
			}

			// difficulty - medium
			coords = m_optionsMenuTextData[(int)OptionsMenu::MEDIUM];
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35)) {
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords))) {

					if (currentGameDifficulty != 1) { // HARDCODED - NEEDS TO BE DYNAMIC
						// highlight medium option
						renderOptionsMenu(NULL, 0, NULL);
						SDL_SetRenderDrawColor(m_renderer, 0, 204, 204, 0xFF);
						auto y0 = std::get<3>(m_optionsMenuTextData[int(OptionsMenu::MEDIUM)]);
						auto y1 = y0 + std::get<5>(m_optionsMenuTextData[int(OptionsMenu::MEDIUM)]) + 2;
						auto x0 = std::get<2>(m_optionsMenuTextData[int(OptionsMenu::MEDIUM)]);
						auto x1 = x0 + std::get<4>(m_optionsMenuTextData[int(OptionsMenu::MEDIUM)]);

						SDL_RenderDrawLine(m_renderer, x0, y1, x1, y1);
						SDL_RenderPresent(m_renderer);
					}

					return int(OptionsMenu::MEDIUM);
				}
			}

			// difficulty - hard
			coords = m_optionsMenuTextData[(int)OptionsMenu::HARD];
			if (y >= std::get<3>(coords) && y <= (std::get<3>(coords) + 35)) {
				if (x >= std::get<2>(coords) && x <= (std::get<2>(coords) + std::get<4>(coords))) {

					if (currentGameDifficulty != 2) { // HARDCODED - NEEDS TO BE DYNAMIC
						// highlight medium option
						renderOptionsMenu(NULL, 0, NULL);
						SDL_SetRenderDrawColor(m_renderer, 0, 204, 204, 0xFF);
						auto y0 = std::get<3>(m_optionsMenuTextData[int(OptionsMenu::HARD)]);
						auto y1 = y0 + std::get<5>(m_optionsMenuTextData[int(OptionsMenu::HARD)]) + 2;
						auto x0 = std::get<2>(m_optionsMenuTextData[int(OptionsMenu::HARD)]);
						auto x1 = x0 + std::get<4>(m_optionsMenuTextData[int(OptionsMenu::HARD)]);

						SDL_RenderDrawLine(m_renderer, x0, y1, x1, y1);
						SDL_RenderPresent(m_renderer);
					}

					return int(OptionsMenu::HARD);
				}
			}
		}
		return -1;
	}


	bool Screen::loadGameBoard() {

		//Loading success flag
		bool success = true;

		//Load PNG texture
		m_textureBoard = loadTexture(PATH_BOARD_PNG);

		if (m_textureBoard == nullptr) {
			log->write("Error loading texture");
			success = false;
		}

		// load piece textures to memory to be used by the render when player or computer plays
		m_textureXPiece = loadTexture(PATH_X_PIECE_PNG);
		if (m_textureXPiece == nullptr){
			log->write("Failed to load texture image!");
		success = false;
		}

		m_textureOPiece = loadTexture(PATH_O_PIECE_PNG);
		if (m_textureOPiece == nullptr){
			log->write("Failed to load texture image!");
			success = false;
		}
		return success;

	}

	void Screen::renderGameBoard() {

		reset();

		//SDL_RenderCopy(m_renderer, m_textureMainMenuBackground, nullptr, nullptr);
		//SDL_RenderPresent(m_renderer);

		//SDL_Rect renderQuad = { m_SCREEN_WIDTH/2 - m_BOARD_WIDTH/2, m_SCREEN_HEIGHT/2 - m_BOARD_HEIGHT/2, 
			//					m_BOARD_WIDTH, m_BOARD_HEIGHT };

		//SDL_RenderCopy(m_renderer, m_textureBoard, nullptr, &renderQuad);

		SDL_RenderCopy(m_renderer, m_textureBoard, nullptr, nullptr);
		SDL_RenderPresent(m_renderer);
		
		// game's event handler is called in the game loop outside this class
	}
	

	SDL_Texture* Screen::loadTexture(std::string path) {

		//The final texture
		SDL_Texture* newTexture = nullptr;
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == nullptr)
			log->write("Error");
		else {
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);

			if (newTexture == nullptr)
				log->write("Error");

			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	// obtains the coords for the board position picked by the player
	SDL_Rect Screen::getPlayerMove(int position) {

		SDL_Rect stretchRect = { 0, 0, 0, 0 };

		auto offset = 30;

		auto x0 = m_SCREEN_WIDTH / 2 - m_BOARD_WIDTH / 2;
		auto y0 = m_SCREEN_HEIGHT / 2 - m_BOARD_HEIGHT / 2;

		// this code is specific to the tic tac toe board layout
		switch (position) {
		case 1:
			stretchRect.x = x0;
			stretchRect.y = y0;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 2:
			stretchRect.x = x0 + m_BOARD_WIDTH / 3;
			stretchRect.y = y0;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 3:
			stretchRect.x = x0 + 2 * m_BOARD_WIDTH / 3;
			stretchRect.y = y0;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 4:
			stretchRect.x = x0;
			stretchRect.y = y0 + m_BOARD_HEIGHT / 3;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 5:
			stretchRect.x = x0 + m_BOARD_WIDTH / 3;
			stretchRect.y = y0 + m_BOARD_HEIGHT / 3;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 6:
			stretchRect.x = x0 + 2 * m_BOARD_WIDTH / 3;
			stretchRect.y = y0 + m_BOARD_HEIGHT / 3;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 7:
			stretchRect.x = x0;
			stretchRect.y = y0 + 2 * m_BOARD_HEIGHT / 3;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 8:
			stretchRect.x = x0 + m_BOARD_WIDTH / 3;
			stretchRect.y = y0 + 2 * m_BOARD_HEIGHT / 3;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
			break;
		case 9:
			stretchRect.x = x0 + 2 * m_BOARD_WIDTH / 3;
			stretchRect.y = y0 + 2 * m_BOARD_HEIGHT / 3;
			stretchRect.w = m_BOARD_WIDTH / 3;
			stretchRect.h = m_BOARD_HEIGHT / 3;
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

			auto x0 = m_SCREEN_WIDTH / 2 - m_BOARD_WIDTH / 2;
			auto y0 = m_SCREEN_HEIGHT / 2 - m_BOARD_HEIGHT / 2;

			// check position of the mouse in the board and saves the position value in local boardPosition variable
			if (y >= y0 && y <= (y0 + m_BOARD_HEIGHT / 3 - pixelsOffset)) {
				if ((x >= x0 + pixelsOffset) && (x <= (x0 + m_BOARD_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 1;
				}
				else if ((x >= x0 + m_BOARD_WIDTH / 3 + pixelsOffset) && (x <= (x0 + 2 * m_BOARD_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 2;
				}
				else if ((x >= x0 + 2 * m_BOARD_WIDTH / 3 + pixelsOffset) && (x <= (x0 + m_BOARD_WIDTH - pixelsOffset))) {
					boardPosition = 3;
				}
			}
			else if (y >= (y0 + m_BOARD_HEIGHT / 3 + pixelsOffset) && y <= (y0 + 2 * m_BOARD_HEIGHT / 3 - pixelsOffset)) {
				if ((x >= x0 + pixelsOffset) && (x <= (x0 + m_BOARD_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 4;
				}
				else if ((x >= x0 + m_BOARD_WIDTH / 3 + pixelsOffset) && (x <= (x0 + 2 * m_BOARD_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 5;
				}
				else if ((x >= x0 + 2 * m_BOARD_WIDTH / 3 + pixelsOffset) && (x <= (x0 + m_BOARD_WIDTH - pixelsOffset))) {
					boardPosition = 6;
				}
			}
			else if (y >= (y0 + 2 * m_BOARD_HEIGHT / 3 + pixelsOffset) && y <= (y0 + m_BOARD_HEIGHT - pixelsOffset)) {
				if ((x >= x0 + pixelsOffset) && (x <= (x0 + m_BOARD_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 7;
				}
				else if ((x >= x0 + m_BOARD_WIDTH / 3 + pixelsOffset) && (x <= (x0 + 2 * m_BOARD_WIDTH / 3 - pixelsOffset))) {
					boardPosition = 8;
				}
				else if ((x >= x0 + 2 * m_BOARD_WIDTH / 3 + pixelsOffset) && (x <= (x0 + m_BOARD_WIDTH - pixelsOffset))) {
					boardPosition = 9;
				}			
			}
			else { boardPosition = -1; }
		}
		
		return boardPosition;
		
	}

	void Screen::renderBoardPiece(int boardPosition, std::string player) {

		SDL_Rect stretchRect = getPlayerMove(boardPosition); // obtains the coords for the board position picked by the player

		if (player == "human")
			SDL_RenderCopy(m_renderer, m_textureXPiece, nullptr, &stretchRect);
		if (player == "computer")
			SDL_RenderCopy(m_renderer, m_textureOPiece, nullptr, &stretchRect);
		
		SDL_RenderPresent(m_renderer);
	}

	void Screen::renderResults(int result) {
		//reset();

		//Open the font
		TTF_Font* font = TTF_OpenFont("fonts/Open_Sans/OpenSans-Bold.ttf", 40);
		if (font == nullptr)
			log->write(TTF_GetError());
		else {
			//Render text
			int textureWidth = -1;
			int textureHeight = -1;
			SDL_Color textColour = { 0, 255, 255 };
			std::string text[3] = { "YOU WON !", "YOU LOST :(", "IT'S A DRAW"};

			std::string textToTexture;

			switch (result) {

			case 0:
				textToTexture = text[0];
				break;
			case 1:
				textToTexture = text[1];
				break;
			case 2:
				textToTexture = text[2];
				break;
			}

			SDL_Texture * newTexture = createTextureFromText(textToTexture, font, textColour, &textureWidth, &textureHeight);

			SDL_Rect renderQuad = { (m_SCREEN_WIDTH-textureWidth)/2, 20, textureWidth, textureHeight};

			//Render to screen
			SDL_RenderCopyEx(m_renderer, newTexture, nullptr, &renderQuad, 0, nullptr, SDL_FLIP_NONE);
			SDL_RenderPresent(m_renderer);
		
			SDL_DestroyTexture(newTexture);
		
		}

	}

	void Screen::reset() {
		//reset renderer color
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		/* Clear the entire screen's back buffer to our selected color. */
		SDL_RenderClear(m_renderer);
	}

}