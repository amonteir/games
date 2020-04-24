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

    Computer computer;
    Player player;

    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl << "Pick your move using numbers 1-9 from the board." << std::endl << "Or press 0 to quit." << std::endl;
    std::cout << "Good luck" << std::endl;
    std::cout << std::endl;

    computer.getBoard()->print();

    do {

        if (computer.getBoard()->MAX_MOVES == 0){
            std::cout << "It's a draw!" << std::endl;
            break;
        }

        std::cout << "Your move: " << std::flush;
        std::cin >> playerMove;

        if (playerMove == 0) {
            break;
        }
        else if (playerMove >= 1 && playerMove <= 9) {
        
            if (computer.getBoard()->validatePlayerMove(playerMove)) { // check if board location was not previously taken by player or computer

                computer.getBoard()->createPlayerMove(playerMove, player.getPlayerPiece()); // saves move in the board
                computer.getBoard()->print();

                // check if there is a winner
                if (computer.getBoard()->checkWinner(player.getPlayerPiece(), computer.getComputerPiece())) {
                    break; // winner found
                }
                else {
                    computer.getBoard()->MAX_MOVES--; // continue the game
                }

                std::cout << "Computer played:" << std::endl;
                computer.calculateBestMove(player.getPlayerPiece()); // computer plays
                computer.getBoard()->print();

                // check if there is a winner
                if(computer.getBoard()->checkWinner(player.getPlayerPiece(), computer.getComputerPiece())){
                    break; // winner found
                }
                else {
                    computer.getBoard()->MAX_MOVES--; // continue the game
                }

            }
            else { // board location picked by player is taken, try a new number
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
