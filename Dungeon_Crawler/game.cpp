//game.cpp

#include "player.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

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

void checkInput(int & roomNum, Player & player, std::vector<Item>& items, std::vector<Key>& keys, Room & room)
{
	while (true)
	{
		string input;
		getline(cin, input);

		string command = "";
		string argument = "";
		bool commandDone = false;

		for (auto x : input)
		{
			if (commandDone)
			{ 
				argument = argument + x;
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

		if (player.exploreOptions.size() > 0)
		{
			if (command == player.exploreOptions[0]) //help
			{
				cout << endl;
				showHelp(player);
				break;
			}
		}
		if (player.exploreOptions.size() > 1)
		{
			if (command == player.exploreOptions[1]) //check
			{
				for (int i = 0; i < room.objects.size(); i++)
				{
					if (argument == room.objects[i].getName())
					{
						checkArgument(i, false, room);
					}
				}
				for (int i = 0; i < room.doors.size(); i++)
				{
					if (argument == room.doors[i].name)
					{
						checkArgument(i, true, room);
					}
				}
				break;
			}
		}
		if (player.exploreOptions.size() > 2)
		{
			if (command == player.exploreOptions[2]) //enter
			{
				for (auto i : room.doors)
				{
					if (argument == i.name)
						enterDoor(i, roomNum);
				}
				break;
			}
		}
		if (player.exploreOptions.size() > 3)
		{
			if (command == player.exploreOptions[3]) //inv
			{
				checkInventory(player, items, keys);
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
	if (player.exploreOptions.size() > 3)
		cout << "inv            -- view your inventory and use items" << endl;
	cout << endl;
}

void checkArgument(int & i, const bool & isDoor, Room & room)
{
	if (!isDoor)
	{
		if (room.objects[i].isVisible)
			cout << endl << room.objects[i].description << endl << endl;
	}
	else
	{
		if (room.doors[i].isLocked)
			cout << endl << room.doors[i].lockedMessage << endl << endl;
		else
			cout << endl << room.doors[i].unlockedMessage << endl << endl;
	}
}

void enterDoor(Door& door, int & roomNum)
{
	if (door.isLocked)
		cout << endl << door.lockedMessage << endl << endl;
	else
	{
		cout << endl << "You entered the " << door.name << ".";
		dblEndl();
		if (door.getRooms().first == roomNum)
			roomNum = door.getRooms().second;
		else
			roomNum = door.getRooms().first;
	}
}

void checkInventory(Player& player, vector<Item>& items, vector<Key>& keys)
{
	int startValue;
	displayItems(items, 0);
	startValue = items.size();
	displayKeys(keys, startValue);
}

void displayItems(vector<Item>& items, const int& startValue)
{
	cout << "	ITEMS" << endl;
	if (items.size() > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			cout << "	(" << i << ") " << items[i].getName() << endl;
		}
	}
	else
		cout << "	none";
	dblEndl();
}

void displayKeys(vector<Key>& keys, const int& startValue)
{
	cout << "	KEYS" << endl;
	if (keys.size() > 0)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			cout << "	(" << (i + startValue) << ") " << keys[i].name << endl;
		}
	}
	else
		cout << "	none";
	dblEndl();
}

int getDecision(const int minChoice, const int maxChoice)
{
	while (true)
	{
		int input;
		cin >> input;
		dblEndl();

		if (!cin || input < minChoice || input > maxChoice)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Sorry, I don't understand. Please input the number corresponding to your" << endl;
			cout << "desired option.";
			dblEndl();
		}
		else
		{
			return input;
		}
	}
}

void explore(Player& player, int& floor, int& roomNum, vector<Item>& items, vector<Key>& keys)
{
	while (true)
	{
		if (floor == 0)
		{
			floor0(player, roomNum, items, keys);
		}
	}
}