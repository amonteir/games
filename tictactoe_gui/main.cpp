// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tictactoe.hpp"

using namespace angelogames;

int main(int argc, char* argv[]) {

    Tictactoe* game = new Tictactoe();

    game->play();

    std::cout << "Bye for now." << std::endl;

    delete game;

    return 0;
}
