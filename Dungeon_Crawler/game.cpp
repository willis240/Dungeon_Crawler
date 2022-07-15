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

void checkInput(int& roomNum)
{
	while (true)
	{
		string input;
		getline(cin, input);
		//SPLIT INPUT INTO TWO SEPERATE STRINGS, FIRST ONE ACTING AS THE COMMAND AND THE SECOND ACTING AS THE OBJECT THE COMMAND APPLIES TO
		//EXAMPLES: CHECK VASE, ENTER WOODEN DOOR

		//MAKE A VECTOR CONTAINING ALL POSSIBLE COMMANDS, PERHAPS AS A MEMBER VARIABLE OF THE PLAYER OBJECT CALLED exploreOptions
		if (input == "help")
		{
			cout << endl;
			showHelp();
			break;
		}
	}
}

void showHelp()
{
	cout << "check (object) -- observe an object more closely" << endl;
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