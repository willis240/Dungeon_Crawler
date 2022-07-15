//floor0.cpp

#include "player.hpp"
#include "game.hpp"
#include <Windows.h>
using std::cout;
using std::endl;
using std::cin;
using std::string;


void floor0(Player& player, int& roomNum)
{
	while (true)
	{
		if (roomNum == 0)
		{
			system("CLS");

			//ADD A CHECK TO SEE IF PLAYER ALREADY HAS TAKEN THE CHEESE

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

				//ADD CHEESE TO INVENTORY

			}

			system("CLS");
			cout << "Well, now that you are the only living thing in the room, you feel a tinge" << endl;
			cout << "of loneliness crawl down your back. You decide it would be best to leave.";
			dblEndl();
			Sleep(7500);
			cout << "You realize that you don't know how to open a door. This is most unfortunate," << endl;
			cout << "as if you do not soon find out, you will likely die of loneliness, starvation," << endl;
			cout << "ligma, etc.";
			dblEndl();
			Sleep(7500);
			cout << "Perhaps, if you were to call for \"help\", then you could figure out how to" << endl;
			cout << "go through the door." << endl;
			while (true)
			{
				//Check for input in order to proceed
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