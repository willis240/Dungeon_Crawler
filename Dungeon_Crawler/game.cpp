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
				cout << endl;
				checkInventory(player, items, keys, room.doors);
			}
			break;
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

void checkInventory(Player& player, vector<Item>& items, vector<Key>& keys, vector<Door>& doors)
{
	while (true)
	{
		cout << "    " << player.getName() << "    HP: " << player.currentHP << " / " << player.maxHP << "    SP: " << player.currentSP << " / " << player.maxSP;
		dblEndl();
		displayItems(items);
		displayKeys(keys);

		cout << "Call for \"help\" if you need to know how to work with your inventory";
		dblEndl();

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

		if (command == "back")
			break;

		if (command == "help")
			showInvHelp();

		if (command == "check")
		{
			checkItems(items, argument);
			checkKeys(keys, argument);
		}
		else if (command == "use")
		{
			useItems(player, items, argument);
			useKeys(player, keys, doors, argument);
			return;
		}
	}
}

void displayItems(vector<Item>& items)
{
	cout << "    ITEMS" << endl;
	if (items.size() > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			cout << "    " << items[i].getName() << endl;
		}
	}
	else
		cout << "    none";
	dblEndl();
}

void displayKeys(vector<Key>& keys)
{
	cout << "    KEYS" << endl;
	if (keys.size() > 0)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			cout << "    " << keys[i].name << endl;
		}
	}
	else
		cout << "    none";
	dblEndl();
}

void showInvHelp()
{
	cout << endl;
	cout << "check (item/key) -- observe the item or key more closely" << endl;
	cout << "use (item)       -- use an item to restore your vitals to their former glory" << endl;
	cout << "use (key)        -- use a key item to open the path forward" << endl;
	cout << "back             -- exit your inventory to continue your exploration" << endl;
	cout << endl;
}

void checkItems(vector<Item>& items, string& argument)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (argument == items[i].getName())
			cout << endl << items[i].getName() << " -- " << items[i].description << endl << endl;
	}
}

void checkKeys(vector<Key>& keys, string& argument)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (argument == keys[i].name)
			cout << endl << keys[i].name << " -- " << keys[i].description << endl << endl;
	}
}

void useItems(Player& player, vector<Item>& items, string& argument)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (argument == items[i].getName())
		{
			int beforeHP = player.currentHP;
			int beforeSP = player.currentSP;
			player.restoreHP(items[i].restoredHP);
			player.restoreSP(items[i].restoredSP);
			cout << endl;
			cout << player.getName() << " used " << items[i].getName() << "!" << endl;
			cout << player.getName() << " restored " << (player.currentHP - beforeHP) << " HP and " << (player.currentSP - beforeSP) << " SP!" << endl;
			items.erase(items.begin() + i);
			return;
		}
	}
	cout << endl;
}

void useKeys(Player& player, vector<Key>& keys, vector<Door>& doors, string& argument)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (argument == keys[i].name)
		{
			cout << "Use " << keys[i].name << " on what?";
			dblEndl();
			cout << "Just say \"back\" if you change your mind and want to return to exploration.";
			dblEndl();

			string input;
			getline(cin, input);

			if (input == "back")
				return;

			for (int ii = 0; ii < doors.size(); ii++)
			{
				if (input == doors[ii].name)
				{
					if (doors[ii].isLocked)
					{
						if (keys[i].getKeyNum() == doors[ii].lockNum)
						{
							doors[ii].isLocked = false;
							cout << "You used the " << keys[i].name << " and unlocked the " << doors[ii].name << ".";
							dblEndl();
							keys.erase(keys.begin() + i);
							return;
						}
					}
				}
			}
		}
	}
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