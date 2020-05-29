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

        resetGame(&quit);
  
        int computerMove = -1;
        SDL_Event e;

        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0){
                //User requests quit
                if (e.type == SDL_QUIT)
                    quit = true;

                human->playerMove = screen->gameEventHandler(&e);

                if (board->validatePlayerMove(human->playerMove)) { // check if board location was not previously taken by player or computer

                    board->createPlayerMove(human->playerMove, human->getPlayerPiece()); // saves move in the board
                    //board->print();
                    screen->renderBoardPiece(human->playerMove, "human");

                    // check if human won with his/her move
                    if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == -1) {
                        // player won
                        std::cout << "YOU WON!!!" << std::endl;
                        resetGame(&quit);
                        continue;
                    }
                    // check if it turns out to be a draw
                    if ((board->m_boardDepth == 0) && (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 0)) {
                        std::cout << "It's a draw!" << std::endl;
                        resetGame(&quit);
                        continue;
                    }

                    //std::cout << "Computer played:" << std::endl;
                    computerMove = computer->calculateBestMove(board, human->getPlayerPiece()); // computer plays
                    screen->renderBoardPiece(computerMove, "computer");

                    // check if computer won with its move
                    if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 1) {
                        // computer won
                        std::cout << "Sorry but the computer won." << std::endl;
                        resetGame(&quit);
                        continue;
                    }

                }
                else { // board location picked by player is taken, try a new number
                    std::cout << "Position taken, try again. " << std::flush;
                }

            }
        }
                    
    }
    
    void Tictactoe::resetGame(bool* quit) {
        board->reset();
        computer->reset();

        if (board->m_boardDepth == board->getBoardSize())
            human->playerMove = screen->renderMainMenu(NULL, 0, NULL);

        // QUIT FROM MAIN MENU
        if (human->playerMove == screen->QUIT) {
            *quit = true;
            return;
        }
        else if (human->playerMove == screen->EASY) {
            computer->setDifficulty(0);
            *quit = false;
        }
        else if (human->playerMove == screen->HARD) {
            computer->setDifficulty(1);
            *quit = false;
        }
        else {
            *quit = true;
            return;
        }

        // PLAY THE GAME
        if (human->playerMove == screen->EASY || human->playerMove == screen->HARD) {

            screen->renderGameBoard();
        }
    }
 }