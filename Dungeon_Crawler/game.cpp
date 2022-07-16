//game.cpp

#include "player.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;

void dblEndl()
{
	cout << endl << endl;
}

Player startGame()
{
	cout << "Greetings, Player, and welcome to my Role-Playing Game!\n" << endl;
	cout << "So, uh, what is your name?" << endl;

	string playerName;
	getline(cin, playerName);

	Player player(playerName, 10, 5);

	cout << "Ah, " << player.getName() << "! I like it." << endl << endl;
	system("pause");

	return player;
}

void checkInput(int& roomNum, Player & player)
{
	while (true)
	{
		string input;
		getline(cin, input);
		//SPLIT INPUT INTO TWO SEPERATE STRINGS, FIRST ONE ACTING AS THE COMMAND AND THE SECOND ACTING AS THE OBJECT THE COMMAND APPLIES TO
		//EXAMPLES: CHECK VASE, ENTER WOODEN DOOR

		string command = "";
		string object = "";
		bool commandDone = false;

		for (auto x : input)
		{
			if (commandDone)
			{ 
				object = object + x;
			}

			if (x == ' ')
			{
				commandDone = true;
			}
			else if (!commandDone)
			{
				command = command + x;
			}
		}

		cout << "command: " << command << endl;
		cout << "object: " << object << endl;

		if (player.exploreOptions.size() > 0)
		{
			if (input == player.exploreOptions[0]) //help
			{
				cout << endl;
				showHelp(player);
				break;
			}
		}
		if (player.exploreOptions.size() > 1)
		{
			if (input == player.exploreOptions[1]) //check
			{
				cout << "check code will go here I swear" << endl;
				break;
			}
		}
		if (player.exploreOptions.size() > 2)
		{
			if (input == player.exploreOptions[2]) //enter
			{
				cout << "enter code will go here I swear" << endl;
				break;
			}
		}
	}
}

void showHelp(Player & player)
{
	if(player.exploreOptions.size() > 1)
		cout << "check (object) -- observe an object more closely" << endl;
	if (player.exploreOptions.size() > 2)
		cout << "enter (door)   -- proceed through the specified door" << endl;
}

int getDecision(const int minChoice, const int maxChoice)
{
	while (true)
	{
		int input;
		cin >> input;
		cout << endl << endl;

		if (!cin || input < minChoice || input > maxChoice)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Sorry, I don't understand. Please input the number corresponding to your" << endl;
			cout << "desired option." << endl << endl;
		}
		else
		{
			return input;
		}
	}
}

void explore(Player& player, int& floor, int& room)
{
	while (true)
	{
		if (floor == 0)
		{
			floor0(player, room);
		}
	}
}