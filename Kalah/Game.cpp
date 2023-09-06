// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north) : 
m_board(b), m_southPlayer(south), m_northPlayer(north), m_turn(SOUTH) {}

void Game::display() const
{
    cout << m_northPlayer->name() << endl; // LINE 1: NORTH'S NAME
    cout << "    ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << i << " ";
    }
    cout << endl; // LINE 2: HOLE NUMBERS
    cout << "- - ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << "- ";
    }
    cout << "- - ";
    cout << endl; // LINE 3: LINES
    cout << "    ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << m_board.beans(NORTH, i) << " ";
    }
    cout << endl; // LINE 4: NORTH'S HOLES
    cout << " " << m_board.beans(NORTH, 0) << "   ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << "  ";
    }
    cout << m_board.beans(SOUTH, 0) << endl; // LINE 5: NORTH AND SOUTH'S POTS
    cout << "    ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << m_board.beans(SOUTH, i) << " ";
    }
    cout << endl; // LINE 6: SOUTH'S HOLES
    cout << "- - ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << "- ";
    }
    cout << "- - ";
    cout << endl; // LINE 7: LINES
    cout << "    ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << i << " ";
    }
    cout << endl; // LINE 8: HOLE NUMBERS
    cout << "    ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << "  ";
    }
    cout << m_southPlayer->name() << endl; // LINE 9: SOUTH'S NAME
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if (m_board.beansInPlay(SOUTH) == 0 && m_board.beansInPlay(NORTH) == 0)
    { // if there are no beans on either side, game is over
        over = true;
        if (m_board.beans(NORTH, 0) == m_board.beans(SOUTH, 0))
        { // if pots have same beans, there is no winner
            hasWinner = false;
        }
        else // there is a winner and we need to compare
        {
            if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0))
            {
                hasWinner = true;
                winner = NORTH;
            }
            else
            {
                hasWinner = true;
                winner = SOUTH;
            }
        }
    }
    else // game is not over
    {
        over = false;
    }
}
// this one turned out too complicated. it worked, but it was just too ugly and probably inefficient, so I made a v2
// bool Game::move(Side s)
// {
//     bool gameOver;
//     bool turnOver = false;
//     bool hasWinner;
//     Side winner;
//     while (turnOver != true)
//     {
//         if (m_board.beansInPlay(s) == 0)
//             {
//                 for (int i = 1; i <= m_board.holes(); i++)
//                 {
//                     if (s == SOUTH)
//                         m_board.moveToPot(NORTH, i, NORTH);
//                     else
//                         m_board.moveToPot(SOUTH, i, SOUTH);
//                 }
//                 if (s == SOUTH)
//                 {
//                     cout << m_southPlayer->name() << " has no beans left to sow." << endl;
//                     cout << "Sweeping remaining beans into " << m_northPlayer->name() << "'s pot." << endl;
//                 }
//                 else
//                 {
//                     cout << m_northPlayer->name() << " has no beans left to sow." << endl;
//                     cout << "Sweeping remaining beans into " << m_southPlayer->name() << "'s pot." << endl;
//                 }
//                 return false;
//             }
//         if (s == SOUTH && m_southPlayer->isInteractive() == true)
//         {
//             Side endSide;
//             int endHole;
//             int choice = m_southPlayer->chooseMove(m_board, s);
//             m_board.sow(s, choice, endSide, endHole);
//             if (endSide == SOUTH && endHole == 0)
//             {
//                 m_turn = SOUTH;
//                 display();
//                 status(gameOver, hasWinner, winner);
//                 if (gameOver == true)
//                 {
//                     turnOver = true;
//                 }
//             }
//             else
//             {
//                 m_turn = NORTH;
//                 turnOver = true;
//             }
//         }
//         else if (s == NORTH && m_northPlayer->isInteractive() == true)
//         {
//             Side endSide;
//             int endHole;
//             int choice = m_northPlayer->chooseMove(m_board, s);
//             m_board.sow(s, choice, endSide, endHole);
//             if (endSide == NORTH && endHole == 0)
//             {
//                 m_turn = NORTH;
//                 display();
//                 status(gameOver, hasWinner, winner);
//                 if (gameOver == true)
//                 {
//                     turnOver = true;
//                 }
//             }
//             else
//             {
//                 m_turn = SOUTH;
//                 turnOver = true;
//             }
//         }
//         else if (s == SOUTH)
//         {
//             Side endSide;
//             int endHole;
//             int choice = m_southPlayer->chooseMove(m_board, s);
//             m_board.sow(s, choice, endSide, endHole);
//             if (endSide == SOUTH && endHole == 0)
//             {
//                 m_turn = SOUTH;
//                 display();
//                 status(gameOver, hasWinner, winner);
//                 if (gameOver == true)
//                 {
//                     turnOver = true;
//                 }
//             }
//             else
//             {
//                 m_turn = NORTH;
//                 turnOver = true;
//             }
//             cout << m_southPlayer->name() << " chooses hole " << choice << endl;
//         }
//         else if (s == NORTH)
//         {
//             Side endSide;
//             int endHole;
//             int choice = m_northPlayer->chooseMove(m_board, s);
//             m_board.sow(s, choice, endSide, endHole);
//             if (endSide == NORTH && endHole == 0)
//             {
//                 m_turn = NORTH;
//                 display();
//                 status(gameOver, hasWinner, winner);
//                 if (gameOver == true)
//                 {
//                     turnOver = true;
//                 }
//             }
//             else
//             {
//                 m_turn = SOUTH;
//                 turnOver = true;
//             }
//             cout << m_northPlayer->name() << " chooses hole " << choice << endl;
//         }
//     }
//     return true;
// }

bool Game::move(Side s)
{
    Side endSide;
    int endHole;
    if (m_board.beansInPlay(s) == 0) // if the turn begins and we have no beans
    {
        for (int i = 1; i <= m_board.holes(); i++) // move all beans into respective pots
        {
            if (s == SOUTH)
                m_board.moveToPot(NORTH, i, NORTH);
            else
                m_board.moveToPot(SOUTH, i, SOUTH);
        }
        if (s == SOUTH) // write message
        {
            cout << m_southPlayer->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_northPlayer->name() << "'s pot." << endl;
        }
        else
        {
            cout << m_northPlayer->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_southPlayer->name() << "'s pot." << endl;
        }
        return false;
    }
    if (s == SOUTH) // if it is south's turn
    {
        int choice = m_southPlayer->chooseMove(m_board, SOUTH); // get a move given the board
        m_board.sow(s, choice, endSide, endHole); // play the move
        if (endHole == 0 && endSide == SOUTH) // if they end on their pot we set the turn to them again
        {
            m_turn = SOUTH;
        }
        else
        {
            m_turn = NORTH;
        }
        if (endSide == SOUTH && m_board.beans(SOUTH, endHole) == 1 && m_board.beans(NORTH, endHole) != 0)
        { // if we end on a previously empty hole on our side, we get steal
            m_board.moveToPot(SOUTH, endHole, SOUTH);
            m_board.moveToPot(NORTH, endHole, SOUTH);
        }
        if (m_southPlayer->isInteractive() == false)
        { // if we are a bot
            cout << m_southPlayer->name() << " chooses hole " << choice << endl; 
        }
        if (m_board.beansInPlay(s) == 0)
        { // check again for end game
        for (int i = 1; i <= m_board.holes(); i++)
        {
            if (s == SOUTH)
                m_board.moveToPot(NORTH, i, NORTH);
            else
                m_board.moveToPot(SOUTH, i, SOUTH);
        }
        if (s == SOUTH)
        {
            cout << m_southPlayer->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_northPlayer->name() << "'s pot." << endl;
        }
        else
        {
            cout << m_northPlayer->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_southPlayer->name() << "'s pot." << endl;
        }
        return false;
        }
        return true;
    }
    else if (s == NORTH)
    {
        int choice = m_northPlayer->chooseMove(m_board, NORTH);
        m_board.sow(s, choice, endSide, endHole);
        if (endHole == 0 && endSide == NORTH)
        { // same as south
            m_turn = NORTH;
        }
        else
        {
            m_turn = SOUTH;
        }
        if (endSide == NORTH && m_board.beans(NORTH, endHole) == 1 && m_board.beans(SOUTH, endHole) != 0)
        {
            m_board.moveToPot(NORTH, endHole, NORTH);
            m_board.moveToPot(SOUTH, endHole, NORTH);
        }
        if (m_northPlayer->isInteractive() == false)
        {
            cout << m_northPlayer->name() << " chooses hole " << choice << endl; 
        }
        if (m_board.beansInPlay(s) == 0)
        {
        for (int i = 1; i <= m_board.holes(); i++)
        {
            if (s == SOUTH)
                m_board.moveToPot(NORTH, i, NORTH);
            else
                m_board.moveToPot(SOUTH, i, SOUTH);
        }
        if (s == SOUTH)
        {
            cout << m_southPlayer->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_northPlayer->name() << "'s pot." << endl;
        }
        else
        {
            cout << m_northPlayer->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_southPlayer->name() << "'s pot." << endl;
        }
        return false;
        }
        return true;
    }
    return false;
}

void Game::play()
{
    bool gameOver = false;
    bool hasWinner;
    Side winner;
    if (m_northPlayer->isInteractive() == false && m_southPlayer->isInteractive() == false)
    { // if both players are bots we go into a special mode
        cout << "Spectator Mode Activated!" << endl;
        while (gameOver != true)
        {
            display();
            move(m_turn);
            status(gameOver, hasWinner, winner);
            if (gameOver != true)
            {
                display();
                cout << "Press ENTER to continue watching ";
                cin.ignore(10000, '\n' );
            }
        }
    }
    else
    {
        while (gameOver != true) // depend on status to end the while loop
        {
            display();
            move(m_turn);
            status(gameOver, hasWinner, winner);
        }
    }
    if (hasWinner == false)
    {
        display();
        cout << "It was a tie." << endl;
    }
    else
    {
        if (winner == NORTH)
        {
            display();
            cout << m_northPlayer->name() << " wins!" << endl;
        }
        else
        {
            display();
            cout << m_southPlayer->name() << " wins!" << endl;
        }
    }
}

int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}

// int main()
// {
//     Board board(4, 3);
//     HumanPlayer* southPlayer = new HumanPlayer("Brian");
//     BadPlayer* northPlayer = new BadPlayer("Bot");
//     Game testGame(board, southPlayer, northPlayer);
//     testGame.play();
//     return 0;
// }