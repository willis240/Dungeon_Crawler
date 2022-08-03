//floor0.cpp

#include "player.hpp"
#include "game.hpp"
#include <Windows.h>
using std::cout;
using std::endl;
using std::cin;
using std::string;


void floor0(Player& player, int& roomNum, std::vector<Item>& items, std::vector<Key>& keys)
{
	//Room 0: The Starting Room
	bool seeOpening = true;
	bool stoleFromRat = false;
	Item nibbledCheese("Nibbled Cheese", 10, 0,
		"Cheese that has already been nibbled by a rat. Hey, at least there's still a good chunk of cheese left. \n"
		"Eating it would probably restore around 10HP, if you had to guess.");
	Door plainDoor(std::make_pair(0, 1), "Plain Door", false,
		"It is a simple wooden door, and it is slightly ajar. It's a good thing it's not locked.");
	Object nightLight("Night Light",
		"The night light is plugged into an outlet in the wall. The lightbulb itself is in the shape of a thumbs-up. \n"
		"Considering the fact that the night light is what allowed you to see in this small dark room in the first place, \n"
		"you decide to give it a thumbs-up in return. \n \n \"Stay cool, little light dude.\"",
		true, false, 0, 0);
	Room startRoom(0, "Starting Room", { nightLight }, { plainDoor }, {}, {});

	//Room 1: The Living Room
	bool gotBrittleKey = false;
	Key brittleKey(1, "Brittle Key",
		"A key which feels like it has been used a million times. It has a crack stretching vertically down the middle. \n"
		"...Hopefully it'll still unlock what it needs to.");
	Object vase("Vase",
		"The vase has a white color, and appears to be ceramic. It seems quite old, and has clearly not been dusted in \n"
		"a long while. While it is rather dirty, you imagine it must've looked rather eye-catching when it was clean. \n"
		"Clearly, it's purpose here was to add some flavor to the room, some style and grace, rather than to do something \n"
		"menial like hide some--Oh, look, there's a key inside.",
		true, false, 0, 1);
	Door brittleDoor(std::make_pair(1, 2), "Brittle Door", true, 1, 
		"It is undoubtedly an old and well-loved door--as long as \"well-loved\" means that it has been used many, many \n"
		"times over several decades without any maintenance. Nevertheless, the door is locked, and stands between you \n"
		"and the room that lies behind it. It may be close to retirement, but it still proudly stands and performs its duty.",
		"After you unlocked the door and opened it, it never recovered. It seems to be stuck wide open. It must have put \n"
		"everything it had into opening one final time. The Brittle Key you inserted, likewise, does not budge. It would \n"
		"seem that both the door and its key have finally found their eternal rest, together.");
	Room livingRoom(1, "Living Room", {vase}, { brittleDoor }, {}, {brittleKey});

	while (true)
	{
		if (roomNum == 0)
		{
			if (seeOpening)
			{
				system("CLS");

				cout << "You wake up in a room just large enough that you can lie down and not touch" << endl;
				cout << "any walls. There is a door right in front of you, and a rat munching on some cheese" << endl;
				cout << "in the corner. What do you do?" << endl;

				cout << "(1) Leave the rat alone" << endl;
				cout << "(2) Swipe the rat's cheese" << endl;

				int input = getDecision(1, 2);

				if (input == 1)
				{
					system("CLS");
					cout << "You watch as the rat continues nibbling on its cheese for a bit. It then" << endl;
					cout << "notices your presence. It stares for all of five seconds before scurrying" << endl;
					cout << "along through a hole in the wall.";
					dblEndl();
					system("pause");
				}
				else if (input == 2)
				{
					system("CLS");
					cout << "You snag the cheese literally from right under the rat's nose. You may" << endl;
					cout << "not understand the inner workings of a rat's mind, but you recognize" << endl;
					cout << "its sorrowful eyes all the same. After a couple of minutes of staring" << endl;
					cout << "at the cheese longingly, the rat dejectedly exits through a hole in the" << endl;
					cout << "wall.";
					dblEndl();
					system("pause");

					items.push_back(nibbledCheese);
					stoleFromRat = true;
				}

				system("CLS");
				cout << "Well, now that you are the only living thing in the room, you feel a tinge" << endl;
				cout << "of loneliness crawl down your back. You decide it would be best to leave.";
				dblEndl();
				
				cout << "You realize that you don't know how to open a door. This is most unfortunate," << endl;
				cout << "as if you do not soon find out, you will likely die of loneliness, starvation," << endl;
				cout << "ligma, etc.";
				dblEndl();
				
				cout << "Perhaps, if you were to call for \"help\", then you could figure out how to" << endl;
				cout << "go through the door.";
				dblEndl();
				player.exploreOptions.push_back("help");
				player.exploreOptions.push_back("check");
				player.exploreOptions.push_back("enter");
				player.exploreOptions.push_back("inv");
				checkInput(roomNum, player, items, keys, startRoom);
				system("pause");
				seeOpening = false;
			}
			else
			{
				system("CLS");
				cout << "Looking around, you see that the room is small and largely empty. However, there is" << endl;
				cout << "a Night Light in the corner, as well as a Plain Door directly in front of you.";
				dblEndl();
				checkInput(roomNum, player, items, keys, startRoom);
				system("pause");
			}
		}

		if (roomNum == 1)
		{
			system("CLS");
			cout << "You step into a room which is much larger than the room you awoke in. It appears to be a" << endl;
			cout << "living space. There is a Brittle Door in front of you, as well as a Vase sitting on a table" << endl;
			cout << "off in the corner.";
			dblEndl();

			checkInput(roomNum, player, items, keys, livingRoom);
			system("pause");
		}

		if (roomNum == 2)
		{
			system("CLS");
			cout << "Wowza! You made it to Room 2 before anything was written for it!" << endl;
			dblEndl();
			system("pause");
		}
	}

}