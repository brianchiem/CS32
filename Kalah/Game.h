// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#ifndef GAME_H
#define GAME_H

#include "Side.h"
#include "Board.h"
#include "Player.h"

class Game
{
    public:
        Game(const Board& b, Player* south, Player* north);
        void display() const;
        void status(bool& over, bool& hasWinner, Side& winner) const;
        bool move(Side s);
        void play();
        int beans(Side s, int hole) const;

    private:
        Board m_board;
        Player* m_southPlayer;
        Player* m_northPlayer;
        Side m_turn;
        bool m_gameOver = false;
};

#endif