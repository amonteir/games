# Tic Tac Toe game in C++98

I appreciate that my implementation might not be the most optimised because, at this point, I'm solely interested in functionality rather than speed, code elegance or modern C++ features. 

I decided to create 4 classes to keep things a bit more readable and modular: 
- Board: contains the board information and the methods that check the game status. It is also here that I calculate winning condition.
- Computer: this class is all about the artificial intelligence that plays against the player. In here you will find the minimax algorithm used to calculate computer's best move, for instance.
- TicTacToe: contains the pointers to all other classes and the game loop. FYI, I decided to use composition rather than inheritance.
- Player: at this point this class is a bit useless because I process the user input in the TicTacToe class.

main.cpp is only calling the method play() with the game loop in the TicTacToe class.
