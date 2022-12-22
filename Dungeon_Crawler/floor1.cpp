//floor1.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

void floor1(vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory)
{
	//Room 0: Hall of Opportunity
	Room hallway(0, "Hallway", {}, {}, {}, {});
	while (true)
	{
		if (floorNum != 1)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			cout << "You made it to the next floor!!!!!!" << endl;
			checkInput(roomNum, floorNum, players, inventory, hallway);
		}
	}
}