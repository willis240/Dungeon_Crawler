//floor2.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_pair;

void floor2(vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory)
{
	string playerInput = "";

	//Room 0: Hall of Resolve
	//Probably gonna make like 3 doors along the left and right sides, with 2 at the back
	Door staircaseDoor(make_pair(4, 0), make_pair(1, 2), "Staircase Door", { "staircase door", "staircase" }, false, true, 11,
		"The door sits at the top of the staircase leading to the second floor. It stands guard to any intruder who \n"
		"would manage to make it past the front door... or at least you assume that's the reason it is locked. Of \n"
		"course, unlocking it should be incredibly easy, all things considered.",
		"The Staircase Door, now unlocked, acts as a simple passage between the front entryway and the second floor of \n"
		"Aria's house.");
	auto staircaseDoorPtr = make_shared<Door>(staircaseDoor);
	Room hallOfResolve(0, "Hall of Resolve", {}, { staircaseDoorPtr }, {}, {});

	while (true)
	{
		if (floorNum != 2)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			cout << "You've made it to Floor 2!!!";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, hallOfResolve);
		}
	}
}