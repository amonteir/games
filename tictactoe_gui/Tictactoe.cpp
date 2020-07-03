#include "Tictactoe.hpp"

namespace angelogames {

    Tictactoe::Tictactoe() {
        log = new Logging("tictactoe.log");

        human = new Player();
        computer = new Computer(1);
        board = new Board();
        screen = new Screen();
        log->write("Tic Tac Toe game initiated successfully.");

    }

    Tictactoe::~Tictactoe() {
        delete human;
        delete computer;
        delete board;
        delete screen;
        log->write("Tic Tac Toe game deleted successfully.");

        log->close();
        delete log;
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
                if (e.type == SDL_QUIT) {
                    //screen->playSound("QUIT");
                    //SDL_Delay(2000);
                    quit = true;
                }
                
                // player is in the main menu, so let's check if there is any event related to main menu
                if (gameStack.top() == int(GameState::MAINMENU)) {
                   
                    human->playerMove = screen->mainMenuEventHandler(&e);                   

                    if (human->playerMove == int(Screen::MainMenu::PLAY)) { // player wants to play
                        gameStack.push(int(GameState::PLAY));
                        screen->playSound("STEP_INTO_MENU");
                        screen->renderGameBoard();
                    }
                    else if (human->playerMove == int(Screen::MainMenu::OPTIONS)) { // player wants to go to options menu
                        gameStack.push(int(GameState::OPTIONSMENU));
                        screen->playSound("STEP_INTO_MENU");
                        screen->renderOptionsMenu(NULL, 0, NULL);
                    }
                    else if (human->playerMove == int(Screen::MainMenu::QUIT)) 
                        quit = true;
                    
                }
                // player is in the options menu, so let's check if there is any event related to options menu
                else if (gameStack.top() == int(GameState::OPTIONSMENU)) {

                    human->playerMove = screen->optionsMenuEventHandler(&e, computer->getDifficulty());

                    // player wants to change difficulty of the game
                    if (human->playerMove == int(Screen::OptionsMenu::EASY)) {
                        computer->setDifficulty((int)Computer::Difficulty::EASY);
                        screen->playSound("STEP_INTO_MENU");
                    }

                    else if (human->playerMove == int(Screen::OptionsMenu::MEDIUM)) {
                        computer->setDifficulty((int)Computer::Difficulty::MEDIUM);
                        screen->playSound("STEP_INTO_MENU");
                    }
                    else if (human->playerMove == int(Screen::OptionsMenu::HARD)) {
                        computer->setDifficulty((int)Computer::Difficulty::HARD);
                        screen->playSound("STEP_INTO_MENU");
                    }
                    else if (human->playerMove == int(Screen::OptionsMenu::BACK)) {
                        gameStack.pop(); // pops the options menu from the stack
                        screen->playSound("STEP_OUT_MENU");
                        screen->renderMainMenu(NULL, 0, NULL);
                    }
                }
                // game is running
                else if (gameStack.top() == int(GameState::PLAY)) {

                    human->playerMove = screen->gameEventHandler(&e);

                    if (board->validatePlayerMove(human->playerMove)) { // check if board location was not previously taken by player or computer

                        board->createPlayerMove(human->playerMove, human->getPlayerPiece()); // saves move in the board
                        screen->renderBoardPiece(human->playerMove, "human");

                        // check if human won with his/her move
                        if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == -1) {
                            // player won
                            //std::cout << "YOU WON!!!" << std::endl;
                            screen->playSound("WON");
                            screen->renderResults((int)PlayerResult::WON);
                            SDL_Delay(3000);
                            restart();
                            continue;
                        }
                        // check if it turns out to be a draw
                        if ((board->m_boardDepth == 0) && (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 0)) {
                            //std::cout << "It's a draw!" << std::endl;
                            screen->playSound("DRAW");
                            screen->renderResults((int)PlayerResult::DRAW);
                            SDL_Delay(3000);
                            restart();
                            continue;
                        }

                        SDL_Delay(1000);

                        computerMove = computer->calculateBestMove(board, human->getPlayerPiece()); // computer plays
                        screen->renderBoardPiece(computerMove, "computer");

                        // check if computer won with its move
                        if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 1) {
                            // computer won
                            //std::cout << "Sorry but the computer won." << std::endl;
                            screen->playSound("LOST");
                            screen->renderResults((int)PlayerResult::LOST);
                            SDL_Delay(3000);
                            restart();
                            continue;
                        }

                    }
                    else { // board location picked by player is taken, try a new number
                        //std::cout << "Position taken, try again. " << std::flush;
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
        log->write("Game restarted successfully.");
    }
 }