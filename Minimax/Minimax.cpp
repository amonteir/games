// Minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

struct Move
{
    int row, col;
};

char player = 'x', computer = 'o';

// This function returns true if there are moves 
// remaining on the board. It returns false if 
// there are no moves left to play. 
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// This is the evaluation function as discussed 
// in the previous article ( http://goo.gl/sJgv68 ) 
int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory. 
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == computer)
                return +10;
            else if (b[row][0] == player)
                return -10;
        }
    }

    // Checking for Columns for X or O victory. 
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == computer)
                return +10;

            else if (b[0][col] == player)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory. 
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == computer)
            return +10;
        else if (b[0][0] == player)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == computer)
            return +10;
        else if (b[0][2] == player)
            return -10;
    }

    // Else if none of them have won then return 0 
    return 0;
}

// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[3][3], int depth, bool isMax)
{
    if (depth == 0 || isMovesLeft(board) == false) {
     
    
        int score = evaluate(board);

        // If Maximizer has won the game return his/her 
        // evaluated score 
        if (score == 10)
            return score;

        // If Minimizer has won the game return his/her 
        // evaluated score 
        if (score == -10)
            return score;
    }

    // If this maximizer's move 
    if (isMax)
    {
        int utility = -1000;

        // Traverse all cells 
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                // Check if cell is empty 
                if (board[i][j] == '_'){
                    // Make the move 
                    board[i][j] = computer;

                    // Call minimax recursively and choose 
                    // the maximum value 
                    utility = std::max(utility,minimax(board, depth - 1, !isMax));

                    // Undo the move 
                    board[i][j] = '_';
                }
            }
        }
        return utility;
    }

    // If this minimizer's move 
    else
    {
        int utility = 1000;

        // Traverse all cells 
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty 
                if (board[i][j] == '_')
                {
                    // Make the move 
                    board[i][j] = player;

                    // Call minimax recursively and choose 
                    // the minimum value 
                    utility = std::min(utility,minimax(board, depth - 1, !isMax));

                    // Undo the move 
                    board[i][j] = '_';
                }
            }
        }
        return utility;
    }
}

// This will return the best possible move for the player 
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for 
    // all empty cells. And return the cell with optimal 
    // value. 
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            // Check if cell is empty 
            if (board[i][j] == '_'){

                // compute evaluation function for this move. 
                int moveVal = minimax(board, 5, true);

                // If the value of the current move is 
                // more than the best value, then update 
                // best/ 
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
        bestVal);

    return bestMove;
}

// Driver code 
int main()
{
    char board[3][3] =
    {
        { 'o', 'o', '_' },
        { 'o', 'x', 'x' },
        { '_', '_', 'x' }
    };

    Move bestMove = findBestMove(board);

    printf("The Optimal Move is :\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row,
        bestMove.col);
    return 0;
}