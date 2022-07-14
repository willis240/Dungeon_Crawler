//floor0.cpp

#include "player.hpp"
#include "game.hpp"
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

			cout << "(1) Exit through the door" << endl;
			cout << "(2) Swipe the rat's cheese" << endl;

			int input = getInput(1, 2);

			if (input == 1)
			{
				roomNum = 1;
			}
			else if (input == 2)
			{
				system("CLS");
				cout << "You snag the cheese literally from right under the rat's nose. You may" << endl;
				cout << "not understand the inner workings of a rat's mind, but you recognize" << endl;
				cout << "its sorrowful eyes all the same." << endl << endl;
				system("pause");

				//ADD CHEESE TO INVENTORY

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