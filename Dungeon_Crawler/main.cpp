//main.cpp

#include "player.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

int main()
{
	Player player = startGame();

	int floorNum = 0;
	int roomNum = 0;

	explore(player, floorNum, roomNum);

}