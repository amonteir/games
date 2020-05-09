#include "Tictactoe.h"

namespace angelogames {

    Tictactoe::Tictactoe() {
        human = new Player();
        computer = new Computer(1);
        board = new Board();
        showMainMenu();
        board->print();
    }

    Tictactoe::~Tictactoe() {
        delete human;
        delete computer;
        delete board;
    }

    void Tictactoe::showMainMenu() {

        std::cout << std::endl << "Welcome to Tic-Tac-Toe!" << std::endl << std::endl;
        std::cout << "Choose difficulty level, easy [0] or godlike [1]: " << std::flush;
        int difficulty;
        std::cin >> difficulty;
        computer->setDifficulty(difficulty);
            
        std::cout << std::endl << "Now.. pick your move using numbers 1-9 from the board." << std::endl << "Or press 0 to quit." << std::endl;
        std::cout << "Good luck !" << std::endl;
        std::cout << std::endl;
    }

    void Tictactoe::play() {

        do {
            std::cout << "Your move: " << std::flush;
            std::cin >> human->playerMove;

            if (human->playerMove == 0)
                break;

            else if (human->playerMove >= 1 && human->playerMove <= 9) {

                if (board->validatePlayerMove(human->playerMove)) { // check if board location was not previously taken by player or computer

                    board->createPlayerMove(human->playerMove, human->getPlayerPiece()); // saves move in the board
                    board->print();

                    // check if human won with his/her move
                    if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == -1) {
                        // player won
                        std::cout << "YOU WON!!!" << std::endl;
                        resetGame();
                        continue;
                    }
                    // check if it turns out to be a draw
                    if ((board->m_boardDepth == 0) && (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 0)) {
                        std::cout << "It's a draw!" << std::endl;
                        resetGame();
                        continue;
                    }

                    std::cout << "Computer played:" << std::endl;
                    computer->calculateBestMove(board, human->getPlayerPiece()); // computer plays
                    board->print();

                    // check if computer won with its move
                    if (board->evaluateWinCondition(human->getPlayerPiece(), computer->getComputerPiece()) == 1) {
                        // computer won
                        std::cout << "Sorry but the computer won." << std::endl;
                        resetGame();
                        continue;
                    }

                }
                else { // board location picked by player is taken, try a new number
                    std::cout << "Position taken, try again. " << std::flush;
                }
            }
            else { // user input was not correct
                std::cout << "Unrecognised option. Try again." << std::endl;
            }
        } while (true);
    }
    
    void Tictactoe::resetGame() {
        board->reset();
        computer->reset();
        showMainMenu();
        board->print();
    }
}