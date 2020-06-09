# C++ games repo

I'm an enthusiastic C++ programer who enjoys coding games and game-related algorithms. 

After passing a C++ beginners course on Udemy, I decided to start my own adventure in C++ development and I thought 
that games can teach you a lot about programming. And I love games. So it's a 2x1 for me really, as to many of you, 
I'm sure.

The next question was, which game do I choose as my first game? I picked Tic Tac Toe because it's one of the simplest
games you can find in terms of board size and game complexity. It also felt appropriate to develop a console version before venturing into graphics APIs.

So this is the list of games I want to develop: 
1. [Tictactoe](https://en.wikipedia.org/wiki/Tic-tac-toe)
   * [Console version](https://github.com/amonteir/games/tree/master/tictactoe): fully functional windows console game available now. Written in C++98. 2 difficulty levels: easy and godlike. For the latter, I implemented the [Minimax](https://en.wikipedia.org/wiki/Minimax) algorithm with depth to improve the performance of the AI - it's impossible to beat the machine, you can either draw or lose. Try for yourself :)
   * [GUI version](https://github.com/amonteir/games/tree/master/tictactoe_gui): Built on top of the console version but now with a  graphical interface using [SDL](https://www.libsdl.org/). Added C++11 features like a stack to control the game loop and enum classes for code readibility and manipulation. Work in progress: improve main menu, add notifications like player won/computer won etc, add audio, improve images, and add error log file.
2. Pac-Man
3. Basic platforms game
4. Basic fighting game
5. Beat 'em up game

I am groot.
