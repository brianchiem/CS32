// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Side.h"
#include "Board.h"

class Player
{
    public:
        Player(std::string name);
        std::string name() const;
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const = 0;
        virtual ~Player();

    private:
        std::string m_name;

};

class HumanPlayer : public Player
{
    public:
        HumanPlayer(std::string name);
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer : public Player
{
    public:
        BadPlayer(std::string name);
        virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player
{
    public:
        SmartPlayer(std::string name);
        virtual int chooseMove(const Board& b, Side s) const;
};

#endif