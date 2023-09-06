// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#ifndef BOARD_H
#define BOARD_H

#include "Side.h"
#include <vector>

using namespace std;

class Board
{
    public:
        Board(int nHoles, int nInitialBeansPerHole);
        int holes() const;
        int beans(Side s, int hole) const;
        int beansInPlay(Side s) const;
        int totalBeans() const;
        bool sow(Side s, int hole, Side& endSide, int& endHole);
        bool moveToPot(Side s, int hole, Side potOwner);
        bool setBeans(Side s, int hole, int beans);
        //void dump();

    private:
        int m_nHoles;
        int m_nInitalBeansPerHole;
        struct Hole
        {
            int holeNumber;
            int beans;
            bool isPot;
            Side s;
        };
        Hole m_northPot;
        Hole m_southPot;
        vector<Hole> m_Board;
};

#endif