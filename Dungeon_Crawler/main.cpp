//main.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;

int main()
{
	Player player = startGame();
	vector<Player> players = { player };
	Inventory inventory;

	int floorNum = 1;
	int roomNum = 0;

	//A SECOND PLAYER CHARACTER, FOR TESTING
	/*
	Player Selena("Selena", 1, 7, 13, {});
	players.push_back(Selena);
	*/

	explore(players, floorNum, roomNum, inventory);

}