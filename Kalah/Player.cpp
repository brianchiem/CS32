// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#include "Player.h"

#include <iostream>

using namespace std;

// Player 

// constructor
Player::Player(std::string name)
{
    m_name = name;
}

// name
std::string Player::name() const
{
    return m_name;
}
// isInteractive, will only vary in human player
bool Player::isInteractive() const
{
    return false;
}
// need a virtual destructor
Player::~Player() {}

// HumanPlayer 

// constructor
HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

// special case
bool HumanPlayer::isInteractive() const
{
    return true;
}

// HumanPlayer chooseMove
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0) // check if there are even valid moves
    {
        return -1;
    }
    int playerInput;
    bool validInput = false;
    while (validInput != true) // just loop around until they give a valid hole
    {
        std::cout << "Select a hole, " << this->name() << ": ";
        std::cin >> playerInput;
        if (playerInput > b.holes() || playerInput < 1) // if out of range
        {
            cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        }
        else if (b.beans(s, playerInput) == 0) // if that hole has no beans
        {
            cout << "There are no beans in that hole." << endl;
        }
        else
        {
            validInput = true; // kill the while
        }
    }
    return playerInput;
}

// BadPlayer

// constructor
BadPlayer::BadPlayer(std::string name) : Player(name) {}

// BadPlayer chooseMove
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        return -1;
    }
    srand (time(NULL)); // random number using library
    int randomNumber; 
    bool validNumber = false;
    while (validNumber != true)
    {
        randomNumber = 1 + (std::rand() % b.holes()); // random number from 1 to hole number 
        if (b.beans(s, randomNumber) == 0)
        {
            ;
        }
        else
        {
            validNumber = true;
        }
    }
    return randomNumber;
}
// SmartPlayer

// constructor
SmartPlayer::SmartPlayer(std::string name) : Player(name) {}

// helper functions forward declarations
int evaluateBoard(const Board& b, Side s); // evaluates a board state and assigns a score to it
int miniMax(const Board& b, Side s, int depth, bool maxOrMin);
// explores the game tree up to the specified depth

int SmartPlayer::chooseMove(const Board& b, Side s) const 
{
    int bestScore = -1000000; // initially a very small number close to negative infinity
    int bestMove = -1;
    int depth = 6; // modify the depth of our tree

    // go through all possible moves for the player
    for (int hole = 1; hole <= b.holes(); ++hole) 
    {
        if (b.beans(s, hole) > 0) 
        {
            Board copyBoard = b;
            Side endSide;
            int endHole;
            copyBoard.sow(s, hole, endSide, endHole);

            int score = miniMax(copyBoard, opponent(s), depth, false); // a depth of 6-8 seems good, further takes so long
            // #1 we set our opponent to be the minimized player,
            // finding the move they would do given a board to minimize our players score.

            if (score > bestScore) 
            {
                bestScore = score;
                bestMove = hole;
            }
        }
    }

    return bestMove; // returns the best move
}

// explore our game tree up to the depth, find the best possible move
// reach max depth or game overs, we get that board state
// the opponent wants to minimize the score that we get
// we want to maximize our score.
int miniMax(const Board& b, Side s, int depth, bool maxOrMin) 
{
    if (depth == 0 || b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0) // how we stop our recursion
    {
        // Reached maximum depth or gameover, return evaluation score
        if (maxOrMin == true)
        {
            return evaluateBoard(b, s); // should be the final score of some play of a board
        }
        else
        {
            return evaluateBoard(b, opponent(s)); // same here
        }
    }

    if (maxOrMin == true) // maximizing
    {
        int maxScore = -1000000; // really small number

        for (int hole = 1; hole <= b.holes(); ++hole) 
        {
            if (b.beans(s, hole) > 0) // go through each valid hole (> 0)
            {
                Board copyBoard = b;
                Side endSide;
                int endHole;
                copyBoard.sow(s, hole, endSide, endHole);

                int score = miniMax(copyBoard, opponent(s), depth - 1, false); // recurse a depth down
                // #3: compare score with the minimizing player. keep doing this until the game is over
                if (score > maxScore) 
                {
                    maxScore = score;
                }
            }
        }

        return maxScore; // return this score
    } 
    else // minimizing
    {
        int minScore = 1000000; // a really big number

        for (int hole = 1; hole <= b.holes(); ++hole) 
        {
            if (b.beans(s, hole) > 0) // go through each valid play
            {
                Board copyBoard = b;
                Side endSide;
                int endHole;
                copyBoard.sow(s, hole, endSide, endHole);

                int score = miniMax(copyBoard, opponent(s), depth - 1, true); // recurse a depth down
                // #2: recurse a depth down and maximize our opponent, which should be the current player
                if (score < minScore) // compare the maximized score with our minimized score
                {
                    minScore = score;
                }
            }
        }

        return minScore;
    }
}

int evaluateBoard(const Board& b, Side s) 
{
    return b.beans(s, 0) - b.beans(opponent(s), 0); // difference in beans in pot, higher is better
}

// int main()
// {
//     Board board(3, 4);
//     BadPlayer player("Brian");
//     int output = player.chooseMove(board, SOUTH);
//     cout << output;
//     return 0;
// }
