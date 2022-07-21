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
		1, 0);
	Room startRoom(0, "Starting Room", {nightLight}, {plainDoor});

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
				Sleep(5000);
				cout << "You realize that you don't know how to open a door. This is most unfortunate," << endl;
				cout << "as if you do not soon find out, you will likely die of loneliness, starvation," << endl;
				cout << "ligma, etc.";
				dblEndl();
				Sleep(5000);
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
			cout << "You step into a room which the creator of this game has not" << endl;
			cout << "yet written anything for..." << endl << endl;
			system("pause");
		}
	}

}