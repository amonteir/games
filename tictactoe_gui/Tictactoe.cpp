#include "Tictactoe.h"

namespace angelogames {

    Tictactoe::Tictactoe() {
        human = new Player();
        computer = new Computer(1);
        board = new Board();
        screen = new Screen();
    }

    Tictactoe::~Tictactoe() {
        delete human;
        delete computer;
        delete board;
        delete screen;
    }

    void Tictactoe::play() {

        //Main game loop flag
        bool quit = false;
      
        gameStack.push(int(GameState::MAINMENU)); // main menu always stays at bottom of the stack
        screen->renderMainMenu(NULL, 0, NULL);

        auto computerMove = -1;
        SDL_Event e;

        while (!quit) {

            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit
                if (e.type == SDL_QUIT)
                    quit = true;
                
                // player is in the main menu, so let's check if there is any event related to main menu
                if (gameStack.top() == int(GameState::MAINMENU)) {
                   
                    human->playerMove = screen->mainMenuEventHandler(&e);                   

                    if (human->playerMove == int(Screen::MainMenu::PLAY)) { // player wants to play
                        gameStack.push(int(GameState::PLAY));
                        screen->renderGameBoard();
                    }
                    else if (human->playerMove == int(Screen::MainMenu::OPTIONS)) { // player wants to go to options menu
                        gameStack.push(int(GameState::OPTIONSMENU));
                        screen->renderOptionsMenu(NULL, 0, NULL);
                    }
                    else if (human->playerMove == int(Screen::MainMenu::QUIT))
                        quit = true;
                }
                // player is in the options menu, so let's check if there is any event related to options menu
                else if (gameStack.top() == int(GameState::OPTIONSMENU)) {

                    human->playerMove = screen->optionsMenuEventHandler(&e, computer->getDifficulty());

                    // player wants to change difficulty of the game
                    if (human->playerMove == int(Screen::OptionsMenu::EASY))
                        computer->setDifficulty((int)Computer::Difficulty::EASY);

                    else if (human->playerMove == int(Screen::OptionsMenu::MEDIUM))
                        computer->setDifficulty((int)Computer::Difficulty::MEDIUM);

                    else if (human->playerMove == int(Screen::OptionsMenu::HARD)) 
                        computer->setDifficulty((int)Computer::Difficulty::HARD);
                
                    else if (human->playerMove == int(Screen::OptionsMenu::BACK)) {
                        gameStack.pop(); // pops the options menu from the stack
                        screen->renderMainMenu(NULL, 0, NULL);
                    }
                }
                // game is running
                else if (gameStack.top() == int(GameState::PLAY)) {

                    human->playerMove = screen->gameEventHandler(&e);

                    if (board->validatePlayerMove(human->playerMove)) { // check if board location was not previously taken by player or computer

                        board->createPlayerMove(human->playerMove, human->getPlayerPiece()); // saves move in the board
                        //board->print();
                        screen->renderBoardPiece(human->playerMove, "human");

                        // check if human won with his/her move
                        if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == -1) {
                            // player won
                            std::cout << "YOU WON!!!" << std::endl;
                            screen->renderResults((int)PlayerResult::WON);
                            SDL_Delay(2000);
                            restart();
                            continue;
                        }
                        // check if it turns out to be a draw
                        if ((board->m_boardDepth == 0) && (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 0)) {
                            std::cout << "It's a draw!" << std::endl;
                            SDL_Delay(2000);
                            restart();
                            continue;
                        }

                        SDL_Delay(1000);

                        //std::cout << "Computer played:" << std::endl;
                        computerMove = computer->calculateBestMove(board, human->getPlayerPiece()); // computer plays
                        screen->renderBoardPiece(computerMove, "computer");

                        // check if computer won with its move
                        if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 1) {
                            // computer won
                            std::cout << "Sorry but the computer won." << std::endl;
                            SDL_Delay(2000);
                            restart();
                            continue;
                        }

                    }
                    else { // board location picked by player is taken, try a new number
                        std::cout << "Position taken, try again. " << std::flush;
                    }
                }
            }
        }
    }
    
    void Tictactoe::restart() {
        board->reset();
        computer->reset();
        gameStack.pop(); // pops PLAY from the stack and goes back to main menu (always stays at the bottom of the stack)
        screen->renderMainMenu(NULL, 0, NULL);
    }
 }