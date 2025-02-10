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
	Object picture("Picture", { "picture" },
		"The picture appears to be of Aria and a young man, smiling. The young man is about a head taller than her,\n"
		"with short black hair and a toned physique. \n\n"
		"\"Is that your brother?\" You ask Aria as you point at the young man in the picture. \n\n"
		"Aria forms a half-hearted smile. \"Yeah. It is.\"\n\n"
		"\"Hey.\" Selena puts her hand on Aria's shoulder. \"We'll find him.\"\n\n"
		"\"...Thanks, guys.\"",
		true, false, 0, 0);
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
	auto dentedDoorPtr = make_shared<Door>(dentedDoor);
	Room hallOfResolve(0, "Hall of Resolve", { picture }, { staircaseDoorPtr, yellowDoorPtr, dentedDoorPtr }, {}, {});

	//Room 1: Dan's Bedroom (Bedroom of the Brother)
	Room danBedroom(1, "Dan's Bedroom", {}, { yellowDoorPtr }, {}, {});

	while (true)
	{
		if (floorNum != 2)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			cout << "You find yourself in a hallway perpendicular to the staircase. The hallway has a few doors. There \n";
			cout << "is the Staircase Door leading downstairs, a Yellow Door on the left side of the hall, and a Dented \n";
			cout << "Door on the right side of the hall. The hallway is mostly plain, with the only things of note being \n";
			cout << "a Picture between the Yellow Door and Dented Door and the white paint on the walls.";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, hallOfResolve);
			system("pause");
		}

		if (roomNum == 1)
		{
			system("CLS");
			cout << "You find yourself in a bedroom. The Red Bed immediately to your right makes that \n";
			cout << "abundantly clear. ";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, danBedroom);
			system("pause");
		}

	}
}