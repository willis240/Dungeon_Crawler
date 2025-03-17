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
	Object redBed("Red Bed", { "red bed" },
		"The bed has a red wooden frame, as well as a red blanket messily thrown about on top of it. \n\n"
		"\"Wait, was your brother taken by those men while he was sleeping?\" Selena posits, pointing toward the bed.\" \n\n"
		"\"I don't think so. He's a bit of a light sleeper, and it doesn't look like anything else in the room has \n"
		"been tossed around. As for the blanket, he never makes his bed in the morning.\" \n\n"
		"\"Wait, seriously?\" \n\n"
		"\"I guess it just doesn't bother him. I can't do it, though. If I left my bed looking like that it would \n"
		"just haunt me from the back of my head all day long.\"", true, false, 0, 0);
	Object poster("Poster", { "poster" },
		"The poster appears to be a promotion for-- \n \n"
		"\"Wait, your brother has a poster for Gargoyle Wars 8 in his room? Don't tell me he actually-\"\n\n"
		"\"No, he isn't a big fan of it, thankfully. I won this poster as a consolation prize in a drawing. I was \n"
		"gonna just throw it away but he said, \'What? But you won this. That'd be a waste.\' I told him the movie \n"
		"was a waste of everyone's time on this planet. He told me that if I wasn't going to use it, then he'd take \n"
		"it. I think he put it up here strategically just so that every time I forget the stupid thing is in my house \n"
		"I see it again.\"", true, false, 0, 0);
	Room danBedroom(1, "Dan's Bedroom", {redBed, poster}, { yellowDoorPtr }, {}, {});

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
			cout << "abundantly clear. There is also a Poster on the wall to the left of the bed.";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, danBedroom);
			system("pause");
		}

	}
}