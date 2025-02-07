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
	Door yellowDoor(make_pair(0, 1), "Yellow Door", { "yellow door" }, false,
		"A standard wooden door, but with a lemon yellow hue. The color makes it fairly distinct.");
	auto yellowDoorPtr = make_shared<Door>(yellowDoor);
	Door dentedDoor(make_pair(0, 2), "Dented Door", { "dented door" }, true, true, 14,
		"A standard wooden door, but- \n \n"
		"\"WHO put this big freaking dent in my door?!\" \n \n"
		"...Yeah, that's not coming out. \n \n"
		"\"These jerks come into my house and take over, and they can't even treat it with RESPECT!\" Aria clenches \n"
		"her fist. \"Ohhh, I'm going to kill whoever did this.\"");
	Room hallOfResolve(0, "Hall of Resolve", {}, { staircaseDoorPtr }, {}, {});

	while (true)
	{
		if (floorNum != 2)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			cout << "The hallway on the second floor has a few doors. There is the Staircase Door which \n";
			cout << "leads back to the first floor, a Yellow Door, and a Dented Door. The hall itself is perpendicular \n";
			cout << "to the top of the stairs, with the Yellow Door on the left side of the hall, and the Dented \n";
			cout << "Door on the right.";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, hallOfResolve);
		}
	}
}