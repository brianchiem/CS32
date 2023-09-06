// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if (nHoles < 0)
    {
        nHoles = 1;
    }
    if (nInitialBeansPerHole < 0)
    {
        nInitialBeansPerHole = 0;
    }
    m_nHoles = nHoles;
    m_nInitalBeansPerHole = nInitialBeansPerHole;

    // set up north's pot
    m_northPot.holeNumber = 0;
    m_northPot.beans = 0;
    m_northPot.isPot = true;
    m_northPot.s = NORTH;

    // set up south's pot
    m_southPot.holeNumber = 0;
    m_southPot.beans = 0;
    m_southPot.isPot = true;
    m_southPot.s = SOUTH;

    m_Board.push_back(m_northPot); // add the northpot first
    for (int i = 1; i <= nHoles; i++) // then it will be south's holes
    {
        Hole southHole;
        southHole.beans = m_nInitalBeansPerHole;
        southHole.holeNumber = i;
        southHole.isPot = false;
        southHole.s = SOUTH;
        m_Board.push_back(southHole);
    }
    m_Board.push_back(m_southPot); // after south's holes it is their pot
    for (int i = 0; i < nHoles; i++) // then it is north's holes
    {
        Hole northHole;
        northHole.beans = m_nInitalBeansPerHole;
        northHole.holeNumber = nHoles - i;
        northHole.isPot = false;
        northHole.s = NORTH;
        m_Board.push_back(northHole);
    }
} // figure something out later that makes this vector circular

int Board::holes() const
{
    return m_nHoles;
}

int Board::beans(Side s, int hole) const
{
    if (hole > m_nHoles)
    {
        return -1;
    }
    for (int i = 0; i < m_Board.size(); i++) // loop through vector
    {
        if (m_Board[i].holeNumber == hole && m_Board[i].s == s) // find the hole we want
        {
            return m_Board[i].beans;
        }
    }
    return -1;
}

int Board::beansInPlay(Side s) const
{
    int counter = 0;
    for (int i = 0; i < m_Board.size(); i++) // loop through board
    {
        if (m_Board[i].isPot != true && m_Board[i].s == s) // if the hole we're on isn't a pot and is the side we want
        {
            counter = counter + m_Board[i].beans; // add the beans to counter
        }
    }
    return counter;
}

int Board::totalBeans() const
{
    int counter = 0;
    for (int i = 0; i < m_Board.size(); i++) // loop through board
    {
        counter = counter + m_Board[i].beans; // add up all beans
    }
    return counter;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if (hole == 0) // check for pot
    {
        return false;
    }
    for (int i = 0; i < m_Board.size(); i++) // find the hole we want
    {
        if (m_Board[i].s == s && m_Board[i].holeNumber == hole) // this is the hole we want
        {
            if (m_Board[i].beans == 0) // check empty
            {
                return false;
            }
            int beansToAdd = m_Board[i].beans; // keep track of our initial bean count
            int k = 1; // need this to keep track of where the last bean ends up
            m_Board[i].beans = 0;
            if (m_Board[i].s == NORTH && m_Board[i].holeNumber == 1)
            {
                i = -1;
            }
            for (; k <= beansToAdd; k++)
            {
                if (m_Board[i + k].s == NORTH && m_Board[i + k].holeNumber == 1) // if we are at the last item in the vector
                {
                    m_Board[i + k].beans = m_Board[i + k].beans + 1;
                    if (k < beansToAdd) // if we still need to add beans and we reached the end of the vector
                    {
                        i = 0 - k - 1;// we need to make it so that however many beans we still need to add we go back to the first item
                    }
                }
                else if (m_Board[i + k].isPot == true && m_Board[i + k].s != s) // if the hole we are looking at is the enemy pot
                {
                    beansToAdd = beansToAdd + 1; // we want to extend the loop by 1, which skips it
                }
                else // otherwise just add 1 to the next pot
                {
                    m_Board[i + k].beans = m_Board[i + k].beans + 1; 
                }
            }
            endSide = m_Board[i + k - 1].s; // sub 1 because the loop will add an extra
            endHole = m_Board[i + k - 1].holeNumber;
            return true;
        }
    }
    return false;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (hole == 0) // check for pot
    {
        return false;
    }
    for (int i = 0; i < m_Board.size(); i++) // loop through board
    {
        if (m_Board[i].s == s && m_Board[i].holeNumber == hole) // find hole we are referring to
        {
            if (potOwner == NORTH) // if giving to NORTH
            {
                for (int k = 0; k < m_Board.size(); k++) // loop again and find the pot
                {
                    if (m_Board[k].isPot == true && m_Board[k].s == NORTH)
                    {
                        m_Board[k].beans = m_Board[k].beans + m_Board[i].beans;
                        m_Board[i].beans = 0;
                        return true;
                    }
                }
            }
            else
            {
                for (int k = 0; k < m_Board.size(); k++) // if giving to SOUTH
                {
                    if (m_Board[k].isPot == true && m_Board[k].s == SOUTH) // loop again and find the pot
                    {
                        m_Board[k].beans = m_Board[k].beans + m_Board[i].beans;
                        m_Board[i].beans = 0;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    for (int i = 0; i < m_Board.size(); i++)
    {
        if (m_Board[i].holeNumber == hole && m_Board[i].s == s)
        {
            if (m_Board[i].beans < 0)
            {
                return false;
            }
            m_Board[i].beans = beans;
            return true;
        }
    }
    return false;
}

// void Board::dump()
// {
//     for (int i = 0; i < m_Board.size(); i++)
//     {
//         if (m_Board[i].s == NORTH)
//             cout << "North " << m_Board[i].holeNumber << ": " << m_Board[i].beans << endl;
//         else
//             cout << "South " << m_Board[i].holeNumber << ": " << m_Board[i].beans << endl;
//     }
// }

// int main()
// {
//     Board test(6, 4);
//     test.dump();
//     cout << "holes: " << test.holes() << endl;
//     cout << "totalBeans: " << test.totalBeans() << endl;
//     cout << "SOUTH beansInPlay: " << test.beansInPlay(SOUTH) << endl;
//     cout << "NORTH beansInPlay: " << test.beansInPlay(NORTH) << endl;
//     Side endSide;
//     int endHole;
//     test.sow(SOUTH, 1, endSide, endHole);
//     test.moveToPot(SOUTH, 2, SOUTH);
//     test.dump();
//     cout << "endHole: " << endHole << endl;
//     return 0;
// }