// tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Computer.h"
#include "Player.h"

using namespace angelogames;


int main()
{
    unsigned int playerMove = 0;

    Board board;
    Computer computer;
    Player player;

    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl << "Pick your move using numbers 1-9 from the board." << std::endl << "Or press 0 to quit." << std::endl;
    std::cout << "Good luck" << std::endl;
    std::cout << std::endl;

    board.print();

    do {

        if (board.MAX_MOVES == 0){
            std::cout << "It's a draw!" << std::endl;
            break;
        }

        std::cout << "Your move: " << std::flush;
        std::cin >> playerMove;

        if (playerMove == 0) {
            break;
        }
        else if (playerMove >= 1 && playerMove <= 9) {
        
            if (board.validatePlayerMove(playerMove)) { // check if board location was not previously taken by player or computer

                board.createPlayerMove(playerMove, player.getPlayerPiece()); // saves move in the board
                board.print();
                //player.savePlayerMove(playerMove); // saves move in player moves
                std::cout << "Computer played:" << std::endl;
                computer.calculateMove(board.pBoardBuffer, board.getBoardSize()); // computer plays
                board.print();

                board.MAX_MOVES--;

                // check if there is a winner
                if (board.checkWinner() == player.getPlayerPiece()) {
                    std::cout << "Well done! You won !!!" << std::endl;
                    break;
                }
                else if (board.checkWinner() == computer.getComputerPiece()) {
                    std::cout << "Sorry but the computer won." << std::endl;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                std::cout << "Try again. " << std::flush ;
            }

            
        }
        else {
            std::cout << "Unrecognised option. Try again." << std::endl;
        }
        
       
    } while (true);

    std::cout << "Exiting now..." << std::endl;

    return 0;
}
