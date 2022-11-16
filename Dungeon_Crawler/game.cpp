//game.cpp

#include "combat.hpp"
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
	string playerName;
	int fails = 0;
	while (true)
	{
		cout << "Greetings, Player, and welcome to my Role-Playing Game!\n" << endl;
		cout << "So, uh, what is your name?" << endl;

		getline(cin, playerName);
		cout << endl;

		if (playerName.length() <= 10)
			break;
		else
		{
			fails++;
			if (fails < 3)
				cout << "Sorry, please keep your name under the 10-character limit." << endl << endl;
			else if (fails == 3)
				cout << "Really? Exceeding the character limit a third time? Alright." << endl << endl;
			else if (fails == 4)
				cout << "Okay, you have got to have read about the character limit at least once, right?" << endl << endl;
			else if (fails == 5)
			{
				cout << "You're doing this ON PURPOSE!!! There is NO other explanation! You're wasting MY time," << endl;
				cout << "and you're wasting YOUR time. Come on, just give me a name that's 10 characters or less." << endl << endl;
			}
			else if (fails == 6)
				cout << "Just make a valid name and PLAY THE FREAKING GAME ALREADY! COME ON!" << endl << endl;
			else if (fails == 7)
			{
				cout << "Screw this." << endl << endl;
				exit(0);
			}
			system("pause");
			system("CLS");
		}
	}
	
	Skill punch("Punch", 3, false, false, 2, "You throw your clenched fist into your foe!");
	Player player(playerName, 10, 10, {punch});

	cout << "Ah, " << player.getName() << "! I like it." << endl << endl;
	system("pause");

	return player;
}

void checkInput(int & roomNum, vector<Player> & players, vector<Item>& items, vector<Key>& keys,
	vector<Accessory>& accessories, Room & room)
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

		if (players[0].exploreOptions.size() > 0)
		{
			if (command == players[0].exploreOptions[0]) //help
			{
				cout << endl;
				showHelp(players[0]);
				break;
			}
		}
		if (players[0].exploreOptions.size() > 1)
		{
			if (command == players[0].exploreOptions[1]) //check
			{
				for (int i = 0; i < room.objects.size(); i++)
				{
					if (argument == room.objects[i].getName())
					{
						checkArgument(i, false, room, items, keys, accessories);
					}
				}
				for (int i = 0; i < room.doors.size(); i++)
				{
					if (argument == room.doors[i]->name)
					{
						checkArgument(i, true, room, items, keys, accessories);
					}
				}
				break;
			}
		}
		if (players[0].exploreOptions.size() > 2)
		{
			if (command == players[0].exploreOptions[2]) //enter
			{
				for (int i = 0; i < room.doors.size(); i++)
				{
					if (argument == room.doors[i]->name)
						enterDoor(*room.doors[i], roomNum);
				}
				break;
			}
		}
		if (players[0].exploreOptions.size() > 3)
		{
			if (command == players[0].exploreOptions[3]) //inv
			{
				cout << endl;
				checkInventory(players, items, keys, accessories, room);
				break;
			}
		}
		if (players[0].exploreOptions.size() > 4)
		{
			if (command == players[0].exploreOptions[4]) //teamwork
			{
				cout << endl;
				for (int i = 0; i < room.objects.size(); i++)
				{
					if (argument == room.objects[i].getName())
						teamUp(i, items, keys, room);
				}
				break;
			}
		}
	}
}

void showHelp(Player & player)
{
	if(player.exploreOptions.size() > 1)
		cout << "check (object)   -- observe an object more closely" << endl;
	if (player.exploreOptions.size() > 2)
		cout << "enter (door)     -- proceed through the specified door" << endl;
	if (player.exploreOptions.size() > 3)
		cout << "inv              -- view your inventory and use items" << endl;
	if (player.exploreOptions.size() > 4)
		cout << "teamwork (object) -- team up with your party members to find secrets" << endl;
	cout << endl;
}

void checkArgument(int & i, const bool & isDoor, Room & room, vector<Item> & items, vector<Key> & keys,
	vector<Accessory>& accessories)
{
	if (!isDoor)
	{
		if (room.objects[i].isVisible)
		{
			cout << endl << room.objects[i].description << endl << endl;
			if (!room.objects[i].hasSecret)
			{
				if (room.objects[i].itemNum != 0)
				{
					for (int ii = 0; ii < room.items.size(); ii++)
					{
						if (room.items[ii].num == room.objects[i].itemNum)
						{
							cout << "You grabbed the " << room.items[ii].getName() << "." << endl << endl;
							items.push_back(room.items[ii]);
							room.items.erase(room.items.begin() + ii);
						}
					}
				}
				if (room.objects[i].keyNum != 0)
				{
					for (int ii = 0; ii < room.keys.size(); ii++)
					{
						if (room.keys[ii].getKeyNum() == room.objects[i].keyNum)
						{
							cout << "You grabbed the " << room.keys[ii].name << "." << endl << endl;
							keys.push_back(room.keys[ii]);
							if (room.keys[ii].actuallyGear == accessory)
							{
								for (int iii = 0; iii < room.accessories.size(); iii++)
								{
									if (room.accessories[iii].keyNum == room.keys[ii].getKeyNum())
									{
										accessories.push_back(room.accessories[iii]);
										room.accessories.erase(room.accessories.begin() + iii);
									}
								}
							}
							room.keys.erase(room.keys.begin() + ii);
						}
					}
				}
			}
		}
	}
	else
	{
		if (room.doors[i]->isVisible)
		{
			if (room.doors[i]->isLocked)
				cout << endl << room.doors[i]->lockedMessage << endl << endl;
			else
				cout << endl << room.doors[i]->unlockedMessage << endl << endl;
		}
	}
}

void enterDoor(Door& door, int & roomNum)
{
	if (door.isVisible)
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
}

void checkInventory(vector<Player>& players, vector<Item>& items, vector<Key>& keys,
	vector<Accessory>& accessories, Room & room)
{
	while (true)
	{
		int spacing = 0;
		for (int i = 0; i < players.size(); i++)
		{
			cout << players[i].getName();
			spacing = players[i].getName().size();
			displaySpacing(spacing, 10);
			cout << "HP: " << players[i].currentHP << " / " << players[i].maxHP;
			spacing = findDigits(players[i].currentHP);
			spacing += 6;
			spacing += findDigits(players[i].maxHP);
			displaySpacing(spacing, 13);
			cout << "SP: " << players[i].currentSP << " / " << players[i].maxSP << "    ";
			cout << endl;
		}
		cout << endl;
		displayItems(items);
		displayKeys(keys);
		displayAccessories(accessories);

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
			showInvHelp(players);

		if (command == "check")
		{
			checkItems(items, argument);
			checkKeys(keys, argument);
		}
		
		if (command == "use")
		{
			useItems(players, items, argument);
			useKeys(players, items, keys, room, argument);
			return;
		}

		if (players.size() > 1)
		{
			if (command == "show")
			{
				showItems(players, items, argument);
				showKeys(players, keys, accessories, argument);
			}
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
		cout << endl;
	}
	else
	{
		cout << "    none";
		dblEndl();
	}
	
}

void displayKeys(vector<Key>& keys)
{
	cout << "    KEY ITEMS" << endl;
	if (keys.size() > 0)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			cout << "    " << keys[i].name << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "    none";
		dblEndl();
	}
}

void displayAccessories(vector<Accessory>& accessories)
{
	if (accessories.size() > 0)
	{
		if (accessories[0].beenDiscovered)
		{
			cout << "    ACCESSORIES" << endl;
			for (int i = 0; i < accessories.size(); i++)
			{
				if (accessories[i].beenDiscovered)
				{
					cout << "    " << accessories[i].getName() << endl;
				}
			}
			cout << endl;
		}
	}
}

void showInvHelp(vector<Player>& players)
{
	cout << endl;
	cout << "check (item/key) -- observe the item or key more closely" << endl;
	cout << "use (item)       -- use an item to restore your vitals to their former glory" << endl;
	cout << "use (key)        -- use a key item to open the path forward" << endl;
	if (players.size() > 1)
		cout << "show (item/key)  -- show the item or key to a party member so they may identify it" << endl;
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

void useItems(vector<Player>& players, vector<Item>& items, string& argument)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (argument == items[i].getName())
		{
			if (items[i].purposeKnown)
			{
				cout << "Use " << items[i].getName() << " on who?";
				dblEndl();
				cout << "Just say \"back\" if you change your mind and want to return to exploration.";
				dblEndl();

				string input;
				getline(cin, input);

				if (input == "back")
					return;

				for (int ii = 0; ii < players.size(); ii++)
				{
					if (input == players[ii].getName())
					{
						int beforeHP = players[ii].currentHP;
						int beforeSP = players[ii].currentSP;
						players[ii].restoreHP(items[i].restoredHP);
						players[ii].restoreSP(items[i].restoredSP);
						cout << endl;
						cout << players[ii].getName() << " used " << items[i].getName() << "!" << endl;
						cout << players[ii].getName() << " restored " << (players[ii].currentHP - beforeHP) << " HP and ";
						cout << (players[ii].currentSP - beforeSP) << " SP!" << endl;
						items.erase(items.begin() + i);
						return;
					}
				}
			}
			else
			{
				cout << "You do not know how to use this item, so you figure it would be best not" << endl;
				cout << "to try or else you may waste it." << endl;
			}
		}
	}
	cout << endl;
}

void useKeys(vector<Player>& players, vector<Item>& items, vector<Key>& keys, Room& room, string& argument)
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

			for (int ii = 0; ii < room.doors.size(); ii++)
			{
				if (input == room.doors[ii]->name)
				{
					if (room.doors[ii]->isVisible)
					{
						if (room.doors[ii]->isLocked)
						{
							if (keys[i].getKeyNum() == room.doors[ii]->lockNum)
							{
								room.doors[ii]->isLocked = false;
								cout << "You used the " << keys[i].name << " and unlocked the " << room.doors[ii]->name << ".";
								dblEndl();
								keys.erase(keys.begin() + i);
							}
							else
							{
								cout << "Unfortunately, the " << keys[i].name << " does not fit in the " << room.doors[ii]->name << ".";
								dblEndl();
							}
							return;
						}
					}
					else
					{
						cout << "Actually, the " << room.doors[ii]->name << " is already unlocked.";
						dblEndl();
						return;
					}
				}
			}
			for (int ii = 0; ii < room.objects.size(); ii++)
			{
				if (input == room.objects[ii].getName())
				{
					if (room.objects[ii].hasSecret)
					{
						if (keys[i].getKeyNum() == room.objects[ii].answerNum)
						{
							room.objects[ii].hasSecret = false;
							system("CLS");
							cout << room.objects[ii].secretText;
							dblEndl();
							keys.erase(keys.begin() + i);
							for (int iii = 0; iii < room.keys.size(); iii++)
							{
								if (room.keys[iii].getKeyNum() == room.objects[ii].keyNum)
								{
									cout << "You obtained the " << room.keys[iii].name << "." << endl << endl;
									keys.push_back(room.keys[iii]);
									room.keys.erase(room.keys.begin() + iii);
								}
							}
							for (int iii = 0; iii < room.items.size(); iii++)
							{
								if (room.items[iii].num == room.objects[ii].itemNum)
								{
									cout << "You obtained the " << room.items[iii].getName() << "." << endl << endl;
									items.push_back(room.items[iii]);
									room.items.erase(room.items.begin() + iii);
								}
							}
							if (room.objects[ii].revealsDoor != 0)
							{
								for (int iii = 0; iii < room.doors.size(); iii++)
								{
									if (room.objects[ii].revealsDoor == room.doors[iii]->lockNum)
										room.doors[iii]->isVisible = true;
								}
							}
							return;
						}
					}
				}
			}
		}
	}
}

void showItems(vector<Player>& players, vector<Item>& items, string& argument)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (argument == items[i].getName())
		{
			cout << "Show " << items[i].getName() << " to who?";
			dblEndl();
			cout << "Just say \"back\" if you change your mind and want to return to exploration.";
			dblEndl();

			string input;
			getline(cin, input);
			cout << endl;

			if (input == "back")
				return;

			for (int ii = 0; ii < players.size(); ii++)
			{
				if (input == players[ii].getName())
				{
					if (players[ii].getName() == items[i].personWithExpertise)
					{
						cout << items[i].expertiseDescription;
						dblEndl();
						items[i].purposeKnown = true;
						return;
					}
					else
					{
						cout << players[ii].getName() << " turns to you and says, \"I don't know what you want me to do with this.\"";
						dblEndl();
						return;
					}
				}
			}
		}
	}
}

void showKeys(vector<Player>& players, vector<Key>& keys, vector<Accessory>& accessories, string& argument)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (argument == keys[i].name)
		{
			cout << "Show " << keys[i].name << " to who?";
			dblEndl();
			cout << "Just say \"back\" if you change your mind and want to return to exploration.";
			dblEndl();

			string input;
			getline(cin, input);
			cout << endl;

			if (input == "back")
				return;

			for (int ii = 0; ii < players.size(); ii++)
			{
				if (input == players[ii].getName())
				{
					if (players[ii].getName() == keys[i].personWithExpertise)
					{
						cout << keys[i].expertiseDescription;
						dblEndl();
						keys[i].purposeKnown = true;
						if (keys[i].actuallyGear == accessory)
						{
							for (int iii = 0; iii < accessories.size(); iii++)
							{
								if (accessories[iii].keyNum == keys[i].getKeyNum())
								{
									accessories[iii].beenDiscovered = true;
									break;
								}
							}
							keys.erase(keys.begin() + i);
						}
						return;
					}
					else
					{
						cout << players[ii].getName() << " turns to you and says, \"I don't know what you want me to do with this.\"";
						dblEndl();
						return;
					}
				}
			}
		}
	}
}

void teamUp(int & i, vector<Item>& items, vector<Key>& keys, Room& room)
{
	if (room.objects[i].answerNum == -1)
	{
		if (room.objects[i].revealsDoor != 0)
		{
			for (int ii = 0; ii < room.doors.size(); ii++)
			{
				if (room.doors[ii]->lockNum == room.objects[i].revealsDoor)
				{
					cout << room.objects[i].secretText;
					dblEndl();
					room.doors[ii]->isVisible = true;
				}
			}
		}
		if (room.objects[i].hasSecret)
		{
			cout << room.objects[i].secretText;
			dblEndl();
			if (room.objects[i].itemNum != 0)
			{
				for (int ii = 0; ii < room.keys.size(); ii++)
				{
					if (room.keys[ii].getKeyNum() == room.objects[i].keyNum)
					{
						cout << "You obtained the " << room.keys[ii].name << "." << endl << endl;
						keys.push_back(room.keys[ii]);
						room.keys.erase(room.keys.begin() + ii);
					}
				}
			}
			if (room.objects[i].keyNum != 0)
			{
				for (int ii = 0; ii < room.items.size(); ii++)
				{
					if (room.items[ii].num == room.objects[i].itemNum)
					{
						cout << "You obtained the " << room.items[ii].getName() << "." << endl << endl;
						items.push_back(room.items[ii]);
						room.items.erase(room.items.begin() + ii);
					}
				}
			}
		}
	}
	else
	{
		cout << "You can't think of a way you could team up to tackle that object, and you wouldn't" << endl;
		cout << "want to look dumb for suggesting teaming up without even a single idea of how to" << endl;
		cout << "approach it. Boy, would you look silly if you did that." << endl << endl;
	}
}

int getDecision(const int minChoice, const int maxChoice)
{
	while (true)
	{
		int input;
		cin >> input;
		cout << endl;

		if (!cin || input < minChoice || input > maxChoice)
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Sorry, I don't understand. Please input the number corresponding to your" << endl;
			cout << "desired option." << endl;
		}
		else
		{
			return input;
		}
	}
}

void explore(vector<Player>& players, int& floor, int& roomNum, vector<Item>& items, vector<Key>& keys, vector<Accessory>& accessories)
{
	while (true)
	{
		if (floor == 0)
		{
			floor0(players, roomNum, items, keys, accessories);
		}
	}
}