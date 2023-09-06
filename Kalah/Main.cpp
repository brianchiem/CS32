// Brian Chiem
// 705973390
// "Kalah: CS32 Project 3"
#include <iostream>
#include <cassert>

using namespace std;

#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Side.h"

void playAgainstBadPlayer()
{
    string name;
    cout << "Enter your name: ";
    cin >> name;
    Board board(6, 4);
    BadPlayer* badBot = new BadPlayer("Bad BOT");
    HumanPlayer* human = new HumanPlayer(name);
    Game game(board, human, badBot);
    game.play();
}

void playAgainstSmartPlayer()
{
    string name;
    cout << "Enter your name: ";
    cin >> name;
    Board board(6, 4);
    SmartPlayer* smartBot = new SmartPlayer("Smart BOT");
    HumanPlayer* human = new HumanPlayer(name);
    Game game(board, human, smartBot);
    game.play();
}

void pitTwoBadBotsAgainstEachOther()
{
    Board board(6, 4);
    BadPlayer* badBot1 = new BadPlayer("CPU 1");
    BadPlayer* badBot2 = new BadPlayer("CPU 2");
    Game game(board, badBot2, badBot1);
    game.play();
}

void pitTwoSmartBotsAgainstEachOther()
{
    Board board(6, 4);
    SmartPlayer* SmartBot1 = new SmartPlayer("CPU 1");
    SmartPlayer* SmartBot2 = new SmartPlayer("CPU 2");
    Game game(board, SmartBot2, SmartBot1);
    game.play();
}

int main()
{
    //playAgainstBadPlayer();
    playAgainstSmartPlayer();
    //pitTwoBadBotsAgainstEachOther();
    //pitTwoSmartBotsAgainstEachOther();
    return 0;
}

// #include "Game.h"
// 	#include "Player.h"
// 	#include "Board.h"
// 	#include "Side.h"
// 	#include <iostream>
// 	#include <cassert>
// 	using namespace std;

// 	void doGameTests()
// 	{
// 	    BadPlayer bp1("Bart");
// 	    BadPlayer bp2("Homer");
// 	    Board b(3, 0);
// 	    b.setBeans(SOUTH, 1, 2);
// 	    b.setBeans(NORTH, 2, 1);
// 	    b.setBeans(NORTH, 3, 2);
// 	    Game g(b, &bp1, &bp2);
// 	    bool over;
// 	    bool hasWinner;
// 	    Side winner;
// 	      //    Homer
// 	      //   0  1  2
// 	      // 0         0
// 	      //   2  0  0
// 	      //    Bart
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
// 		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
// 		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

// 	    g.move(SOUTH);
// 	      //   0  1  0
// 	      // 0         3
// 	      //   0  1  0
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
// 		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

// 	    g.move(NORTH);
// 	      //   1  0  0
// 	      // 0         3
// 	      //   0  1  0
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
// 		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

// 	    g.move(SOUTH);
// 	      //   1  0  0
// 	      // 0         3
// 	      //   0  0  1
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
// 		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

// 	    g.move(NORTH);
// 	      //   0  0  0
// 	      // 1         4
// 	      //   0  0  0
// 	    g.status(over, hasWinner, winner);
// 	    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
// 		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
// 	    assert(hasWinner && winner == SOUTH);
// 	}

// 	int main()
// 	{
// 	    doGameTests();
// 	    cout << "Passed all tests" << endl;
// 	}

