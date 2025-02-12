//game.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;

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
	Player player(playerName, 0, 10, 10, {punch});

	cout << "Ah, " << player.getName() << "! I like it." << endl << endl;
	system("pause");

	return player;
}

string checkInput(int& roomNum, int& floorNum, vector<Player>& players, Inventory& inventory, Room& room)
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
				argument = argument + x;

			if (x == ' ')
				commandDone = true;
			else if (!commandDone)
				command = command + x;
		}

		if (players[0].exploreOptions.size() > 0)
		{
			if (command == players[0].exploreOptions[0]) //help
			{
				cout << endl;
				showHelp(players[0]);
				return input;
			}
		}
		if (players[0].exploreOptions.size() > 1)
		{
			if (command == players[0].exploreOptions[1] || command == "c") //check
			{
				for (int i = 0; i < room.objects.size(); i++)
				{
					if (argument == room.objects[i].getName())
					{
						checkArgument(i, false, room, inventory);
						input = "";
						input += players[0].exploreOptions[1];
						input += " ";
						input += room.objects[i].getName();
					}

					for (int ii = 0; ii < room.objects[i].aliases.size(); ii++)
					{
						if (argument == room.objects[i].aliases[ii])
						{
							checkArgument(i, false, room, inventory);
							input = "";
							input += players[0].exploreOptions[1];
							input += " ";
							input += room.objects[i].getName();
						}
							
					}
				}
				for (int i = 0; i < room.doors.size(); i++)
				{
					if (argument == room.doors[i]->name)
					{
						checkArgument(i, true, room, inventory);
						input = "";
						input += players[0].exploreOptions[1];
						input += " ";
						input += room.doors[i]->name;
					}
					for (int ii = 0; ii < room.doors[i]->aliases.size(); ii++)
					{
						if (argument == room.doors[i]->aliases[ii])
						{
							checkArgument(i, true, room, inventory);
							input = "";
							input += players[0].exploreOptions[1];
							input += " ";
							input += room.doors[i]->name;
						}
					}
				}
				return input;
			}
		}
		if (players[0].exploreOptions.size() > 2)
		{
			if (command == players[0].exploreOptions[2] || command == "e") //enter
			{
				for (int i = 0; i < room.doors.size(); i++)
				{
					if (argument == room.doors[i]->name)
					{
						enterDoor(*room.doors[i], roomNum, floorNum);
						input = "";
						input += players[0].exploreOptions[2];
						input += " ";
						input += room.doors[i]->name;
					}
						

					for (int ii = 0; ii < room.doors[i]->aliases.size(); ii++)
					{
						if (argument == room.doors[i]->aliases[ii])
						{
							enterDoor(*room.doors[i], roomNum, floorNum);
							input = "";
							input += players[0].exploreOptions[2];
							input += " ";
							input += room.doors[i]->name;
						}
					}
				}
				return input;
			}
		}
		if (players[0].exploreOptions.size() > 3)
		{
			if (command == players[0].exploreOptions[3] || command == "i") //inv
			{
				cout << endl;
				checkInventory(players, inventory, room);
				return input;
			}
		}
		if (players[0].exploreOptions.size() > 4)
		{
			if (command == players[0].exploreOptions[4] || command == "t") //teamup
			{
				cout << endl;
				for (int i = 0; i < room.objects.size(); i++)
				{
					if (argument == room.objects[i].getName())
						teamUp(i, inventory, room);

					for (int ii = 0; ii < room.objects[i].aliases.size(); ii++)
					{
						if (argument == room.objects[i].aliases[ii])
							teamUp(i, inventory, room);
					}
				}
				return input;
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
		cout << "teamup (object) -- team up with your party members to find secrets" << endl;
	cout << endl;
}

void checkArgument(int & i, const bool & isDoor, Room & room, Inventory& inventory)
{
	if (!isDoor)
	{
		if (room.objects[i].isVisible)
		{
			if (room.objects[i].isLocked)
			{
				cout << endl << room.objects[i].lockedText << endl << endl;
				return;
			}
			else
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
							inventory.items.push_back(room.items[ii]);
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
							if (room.keys[ii].reclaimable)
							{
								cout << "Do you take the " << room.keys[ii].name << "?" << endl;
								cout << "(1) Yes" << endl;
								cout << "(2) No" << endl;
								int input = getDecision(1, 2);

								if (input == 1)
								{
									cout << "You grabbed the " << room.keys[ii].name << "." << endl << endl;
									inventory.keys.push_back(room.keys[ii]);
									room.objects[i].isLocked = true;
									room.objects[i].keyNum = 0;
									room.keys.erase(room.keys.begin() + ii);
								}
								return;
							}
							cout << "You grabbed the " << room.keys[ii].name << "." << endl << endl;
							inventory.keys.push_back(room.keys[ii]);
							if (room.keys[ii].actuallyGear == weapon)
							{
								for (int iii = 0; iii < room.weapons.size(); iii++)
								{
									if (room.weapons[iii]->keyNum == room.keys[ii].getKeyNum())
									{
										inventory.weapons.push_back(room.weapons[iii]);
										room.weapons.erase(room.weapons.begin() + iii);
									}
								}
							}
							if (room.keys[ii].actuallyGear == accessory)
							{
								for (int iii = 0; iii < room.accessories.size(); iii++)
								{
									if (room.accessories[iii]->keyNum == room.keys[ii].getKeyNum())
									{
										inventory.accessories.push_back(room.accessories[iii]);
										room.accessories.erase(room.accessories.begin() + iii);
									}
								}
							}
							room.keys.erase(room.keys.begin() + ii);
						}
					}
				}
			}
			else
			{
				if (room.objects[i].checkSecret != 0)
				{
					int foundObject = room.objects[i].checkSecret;
					room.objects[foundObject].isVisible = true;
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

void enterDoor(Door& door, int & roomNum, int & floorNum)
{
	if (door.isVisible)
	{
		if (door.isLocked)
			cout << endl << door.lockedMessage << endl << endl;
		else
		{
			cout << endl << "You entered the " << door.name << ".";
			dblEndl();
			if (door.getFloors().first != -1)
			{
				if (door.getFloors().first == floorNum)
					floorNum = door.getFloors().second;
				else
					floorNum = door.getFloors().first;
			}
			if (door.getRooms().first == roomNum)
				roomNum = door.getRooms().second;
			else
				roomNum = door.getRooms().first;
		}
	}
}

void checkInventory(vector<Player>& players, Inventory& inventory, Room & room)
{
	while (true)
	{
		displayInventoryHeader(players);
		displayItems(inventory.items);
		displayKeys(inventory.keys);
		displayGear(inventory.weapons, inventory.armors, inventory.accessories);

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
				argument = argument + x;

			if (x == ' ')
				commandDone = true;
			else if (!commandDone)
				command = command + x;
		}

		if (command == "back")
			break;

		if (command == "help")
		{
			showInvHelp(players, inventory);
			system("pause");
		}

		if (command == "check" || command == "c")
		{
			checkItems(inventory, argument);
			checkKeys(inventory, argument);
			checkGear(inventory, argument);
			system("pause");
		}
		
		if (command == "use" || command == "u")
		{
			bool exitInv = false;
			useItems(players, inventory.items, argument);
			exitInv = useKeys(players, inventory, room, argument);
			if (exitInv)
				return;
			system("pause");
		}

		if (command == "status" || command == "st")
		{
			showStatus(players);
			system("pause");
		}

		if (players.size() > 1)
		{
			if (command == "show" || command == "s")
			{
				showItems(players, inventory.items, argument);
				showKeys(players, inventory, argument);
				system("pause");
			}
		}

		if (command == "equip" || command == "e")
		{
			equipGear(players, inventory.weapons, inventory.armors, inventory.accessories, argument);
			system("pause");
		}

		if (command == "unequip" || command == "ue")
		{
			unequipGear(players, inventory.weapons, inventory.armors, inventory.accessories, argument);
			system("pause");
		}

		system("CLS");
	}
}

void displayInventoryHeader(vector<Player>& players)
{
	int spacing = 0;
	cout << "-------------" << endl;
	cout << "- INVENTORY -" << endl;
	cout << "-------------" << endl << endl;

	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].getName();
		spacing = players[i].getName().size();
		displaySpacing(spacing, 11);
		cout << "HP: " << players[i].currentHP << " / " << players[i].maxHP;
		spacing = findDigits(players[i].currentHP);
		spacing += 6;
		spacing += findDigits(players[i].maxHP);
		displaySpacing(spacing, 13);
		cout << "SP: " << players[i].currentSP << " / " << players[i].maxSP << "    ";
		cout << endl;
	}
	cout << endl;
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

void displayGear(vector<shared_ptr<Weapon>>& weapons, vector<shared_ptr<Armor>>& armors, vector<shared_ptr<Accessory>>& accessories)
{
	int spacing = 0;
	int spaceMax = 25;
	int iterLimit;
	int weaponOffset = 0;
	int weaponIter = 0;
	int armorOffset = 0;
	int armorIter = 0;
	int accessoryOffset = 0;
	int accessoryIter = 0;
	bool showGear = false;

	if (accessories.size() > 0)
	{
		if (accessories[0]->beenDiscovered)
			showGear = true;
	}
	if (weapons.size() > 0)
	{
		if (weapons[0]->beenDiscovered)
			showGear = true;
	}
	if (showGear)
	{
		cout << "    WEAPONS";
		spacing = 7;
		displaySpacing(spacing, spaceMax);
		cout << "ARMOR";
		spacing = 5;
		displaySpacing(spacing, spaceMax);
		cout << "ACCESSORIES" << endl;

		if (accessories.size() < weapons.size())
			iterLimit = weapons.size();
		else
			iterLimit = accessories.size();
		if (iterLimit < armors.size())
			iterLimit = armors.size();

		for (int i = 0; i < iterLimit; i++)
		{	
			cout << "    ";

			weaponIter = i + weaponOffset;
			if (weapons.size() > weaponIter)
			{
				if (!weapons[weaponIter]->beenDiscovered)
				{
					for (int ii = weaponIter; ii < weapons.size(); ii++)
					{
						if (!weapons[ii]->beenDiscovered)
							weaponOffset++;
						else
							break;
					}
					weaponIter = i + weaponOffset;
				}
				if (weapons.size() > weaponIter)
				{
					if (weapons[weaponIter]->equippedNum != -1)
					{
						cout << "[E] ";
						spacing = weapons[weaponIter]->getName().length() + 4;
					}
					else
						spacing = weapons[weaponIter]->getName().length();
					cout << weapons[weaponIter]->getName();
				}
				else
					spacing = 0;
			}
			else
				spacing = 0;
			displaySpacing(spacing, spaceMax);

			armorIter = i + armorOffset;
			if (armors.size() > armorIter)
			{
				if (!armors[armorIter]->beenDiscovered)
				{
					for (int ii = armorIter; ii < armors.size(); ii++)
					{
						if (!armors[ii]->beenDiscovered)
							armorOffset++;
						else
							break;
					}
					armorIter = i + armorOffset;
				}
				if (armors.size() > armorIter)
				{
					if (armors[armorIter]->equippedNum != -1)
					{
						cout << "[E] ";
						spacing = armors[armorIter]->getName().length() + 4;
					}
					else
						spacing = armors[armorIter]->getName().length();
					cout << armors[armorIter]->getName();
				}
				else
					spacing = 0;
			}
			else
				spacing = 0;
			displaySpacing(spacing, spaceMax);
				
			accessoryIter = i + accessoryOffset;
			if (accessories.size() > accessoryIter)
			{
				if (!accessories[accessoryIter]->beenDiscovered)
				{
					for (int ii = accessoryIter; ii < accessories.size(); ii++)
					{
						if (!accessories[ii]->beenDiscovered)
							accessoryOffset++;
						else
							break;
					}
					accessoryIter = i + accessoryOffset;
				}
				if (accessories.size() > accessoryIter)
				{
					if (accessories[accessoryIter]->equippedNum != -1)
					{
						cout << "[E] ";
						spacing = accessories[accessoryIter]->getName().length() + 4;
					}
					else
						spacing = accessories[accessoryIter]->getName().length();
					cout << accessories[accessoryIter]->getName();
				}
				else
					spacing = 0;
			}
			else
				spacing = 0;
			displaySpacing(spacing, spaceMax);

			if (weaponIter >= weapons.size() && armorIter >= armors.size() && accessoryIter >= accessories.size())
				break;

			cout << endl;
		}
		cout << endl;
	}
}

void displayWeapons(vector<shared_ptr<Weapon>>& weapons)
{
	if (weapons.size() > 0)
	{
		if (weapons[0]->beenDiscovered)
		{
			cout << "    WEAPONS" << endl;
			for (int i = 0; i < weapons.size(); i++)
			{
				if (weapons[i]->beenDiscovered)
				{
					cout << "    ";
					if (weapons[i]->equippedNum != -1)
						cout << "[E] ";
					cout << weapons[i]->getName() << endl;
				}
			}
			cout << endl;
		}
	}
}

void displayAccessories(vector<shared_ptr<Accessory>>& accessories)
{
	if (accessories.size() > 0)
	{
		if (accessories[0]->beenDiscovered)
		{
			cout << "    ACCESSORIES" << endl;
			for (int i = 0; i < accessories.size(); i++)
			{
				if (accessories[i]->beenDiscovered)
				{
					cout << "    ";
					if (accessories[i]->equippedNum != -1)
						cout << "[E] ";
					cout << accessories[i]->getName() << endl;
				}
			}
			cout << endl;
		}
	}
}

void showInvHelp(vector<Player>& players, Inventory& inventory)
{
	cout << endl;
	cout << "check (item/key) -- observe the item or key more closely" << endl;
	cout << "use (item/key)   -- use an item to heal or key item to progress" << endl;
	if (players.size() > 1)
		cout << "show (item/key)  -- show the item or key to a party member so they may identify it" << endl;
	if (inventory.accessories.size() > 0 || inventory.weapons.size())
	{
		if (inventory.accessories[0]->beenDiscovered || inventory.weapons[0]->beenDiscovered)
		{
			cout << "status           -- check your stats and equipment" << endl;
			cout << "check (gear)     -- check the stat bonuses of equipment" << endl;
			cout << "equip (gear)     -- equip gear to a party member to affect their stats" << endl;
			cout << "unequip (gear)   -- unequip gear to remove its affects from that party member" << endl;
		}
	}
	cout << "back             -- exit your inventory to continue your exploration" << endl;
	cout << endl;
}

void checkItems(Inventory& inventory, string& argument)
{
	for (int i = 0; i < inventory.items.size(); i++)
	{
		if (argument == inventory.items[i].getName())
			cout << endl << inventory.items[i].getName() << " -- " << inventory.items[i].description << endl << endl;
		else
		{
			for (int ii = 0; ii < inventory.items[i].aliases.size(); ii++)
			{
				if (argument == inventory.items[i].aliases[ii])
					cout << endl << inventory.items[i].getName() << " -- " << inventory.items[i].description << endl << endl;
			}
		}
	}
}

void checkKeys(Inventory& inventory, string& argument)
{
	for (int i = 0; i < inventory.keys.size(); i++)
	{
		if (argument == inventory.keys[i].name)
			cout << endl << inventory.keys[i].name << " -- " << inventory.keys[i].description << endl << endl;
		else
		{
			for (int ii = 0; ii < inventory.keys[i].aliases.size(); ii++)
			{
				if (argument == inventory.keys[i].aliases[ii])
					cout << endl << inventory.keys[i].name << " -- " << inventory.keys[i].description << endl << endl;
			}
		}
	}
}

void checkGear(Inventory& inventory, string& argument)
{
	for (int i = 0; i < inventory.weapons.size(); i++)
	{
		if (argument == inventory.weapons[i]->getName())
		{
			cout << endl << inventory.weapons[i]->getName() << ":   HP " << inventory.weapons[i]->HP << "   SP " << inventory.weapons[i]->SP << "   STR " << inventory.weapons[i]->str;
			dblEndl();
			return;
		}
	}

	for (int i = 0; i < inventory.armors.size(); i++)
	{
		if (argument == inventory.armors[i]->getName())
		{
			cout << endl << inventory.armors[i]->getName() << ":   HP " << inventory.armors[i]->HP << "   SP " << inventory.armors[i]->SP << "   STR " << inventory.armors[i]->str;
			dblEndl();
			return;
		}
	}

	for (int i = 0; i < inventory.accessories.size(); i++)
	{
		if (argument == inventory.accessories[i]->getName())
		{
			cout << endl << inventory.accessories[i]->getName() << ":   HP " << inventory.accessories[i]->HP << "   SP " << inventory.accessories[i]->SP << "   STR " << inventory.accessories[i]->str;
			dblEndl();
			return;
		}
	}
}

void useItems(vector<Player>& players, vector<Item>& items, string& argument)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (argument == items[i].getName())
		{
			useItemOnPlayer(players, items, i);
		}
		else
		{
			for (int ii = 0; ii < items[i].aliases.size(); ii++)
			{
				if (argument == items[i].aliases[ii])
				{
					if (useItemOnPlayer(players, items, i))
						return;
				}
			}
		}
	}
	cout << endl;
}

bool useItemOnPlayer(vector<Player>& players, vector<Item>& items, int & i)
{
	if (items[i].purposeKnown)
	{
		string input;
		if (players.size() > 1)
		{
			cout << "Use " << items[i].getName() << " on who?";
			dblEndl();
			cout << "Just say \"back\" if you change your mind and want to return to exploration.";
			dblEndl();

			getline(cin, input);

			if (input == "back")
				return false;
		}
		else
		{
			input = players[0].getName();
		}

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
				cout << (players[ii].currentSP - beforeSP) << " SP!" << endl << endl;
				items.erase(items.begin() + i);
				return true;
			}
		}
	}
	else
	{
		cout << "You do not know how to use this item, so you figure it would be best not" << endl;
		cout << "to try or else you may waste it." << endl << endl;
		return false;
	}
}

bool useKeys(vector<Player>& players, Inventory& inventory, Room& room, string& argument)
{
	for (int i = 0; i < inventory.keys.size(); i++)
	{
		if (argument == inventory.keys[i].name)
		{
			return useKeyOnThing(players, inventory, room, i);
		}
		for (int ii = 0; ii < inventory.keys[i].aliases.size(); ii++)
		{
			if (argument == inventory.keys[i].aliases[ii])
				return useKeyOnThing(players, inventory, room, i);
		}
	}
	return false;
}

bool useKeyOnThing(vector<Player>& players, Inventory& inventory, Room& room, int& i)
{
	cout << "Use " << inventory.keys[i].name << " on what?";
	dblEndl();
	cout << "Just say \"back\" if you change your mind and want to return to exploration.";
	dblEndl();

	string input;
	getline(cin, input);

	if (input == "back")
		return true;

	for (int ii = 0; ii < room.doors.size(); ii++)
	{
		if (input == room.doors[ii]->name)
		{
			return unlockDoor(inventory, room, i, ii);
		}
		for (int aliasIter = 0; aliasIter < room.doors[ii]->aliases.size(); aliasIter++)
		{
			if (input == room.doors[ii]->aliases[aliasIter])
			{
				return unlockDoor(inventory, room, i, ii);
			}
		}
	}
	for (int ii = 0; ii < room.objects.size(); ii++)
	{
		if (input == room.objects[ii].getName())
		{
			bool exit = unlockObject(inventory, room, i, ii);
			if (exit)
				return exit;
		}
		for (int aliasIter = 0; aliasIter < room.objects[ii].aliases.size(); aliasIter++)
		{
			if (input == room.objects[ii].aliases[aliasIter])
			{
				bool exit = unlockObject(inventory, room, i, ii);
				if (exit)
					return exit;
			}
		}
	}
}

bool unlockDoor(Inventory& inventory, Room& room, int& i, int& ii)
{
	if (room.doors[ii]->isVisible)
	{
		if (room.doors[ii]->isLocked)
		{
			if (inventory.keys[i].getKeyNum() == room.doors[ii]->lockNum)
			{
				room.doors[ii]->isLocked = false;
				cout << "You used the " << inventory.keys[i].name << " and unlocked the " << room.doors[ii]->name << ".";
				dblEndl();
				inventory.keys.erase(inventory.keys.begin() + i);
				return true;
			}
			else
			{
				cout << "Unfortunately, the " << inventory.keys[i].name << " does not fit in the " << room.doors[ii]->name << ".";
				dblEndl();
				return false;
			}
		}
	}
	else
	{
		cout << "Actually, the " << room.doors[ii]->name << " is already unlocked.";
		dblEndl();
		return true;
	}
}

bool unlockObject(Inventory& inventory, Room& room, int& i, int& ii)
{
	if (room.objects[ii].hasSecret)
	{
		if (inventory.keys[i].getKeyNum() == room.objects[ii].answerNum)
		{
			room.objects[ii].hasSecret = false;
			system("CLS");
			cout << room.objects[ii].secretText;
			dblEndl();
			inventory.keys.erase(inventory.keys.begin() + i);
			for (int iii = 0; iii < room.keys.size(); iii++)
			{
				if (room.keys[iii].getKeyNum() == room.objects[ii].keyNum)
				{
					cout << "You obtained the " << room.keys[iii].name << "." << endl << endl;
					inventory.keys.push_back(room.keys[iii]);
					room.keys.erase(room.keys.begin() + iii);
				}
			}
			for (int iii = 0; iii < room.items.size(); iii++)
			{
				if (room.items[iii].num == room.objects[ii].itemNum)
				{
					cout << "You obtained the " << room.items[iii].getName() << "." << endl << endl;
					inventory.items.push_back(room.items[iii]);
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
			return true;
		}
	}

	if (room.objects[ii].isLocked)
	{
		if (inventory.keys[i].getKeyNum() == room.objects[ii].answerNum)
		{
			room.objects[ii].isLocked = false;
			system("CLS");
			cout << room.objects[ii].description;
			dblEndl();
			if (inventory.keys[i].reclaimable)
			{
				room.objects[ii].keyNum = inventory.keys[i].getKeyNum();
				room.keys.push_back(inventory.keys[i]);
			}
			inventory.keys.erase(inventory.keys.begin() + i);
		}
	}
	return false;
}

void showStatus(vector<Player>& players)
{
	system("CLS");
	cout << "----------" << endl;
	cout << "- STATUS -" << endl;
	cout << "----------";
	dblEndl();

	int spacing = 0;
	int spaceMax = 28;

	int equipBonus = 0;

	//Names
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].getName();
		spacing = players[i].getName().size();
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//LV
	for (int i = 0; i < players.size(); i++)
	{
		cout << "Lv " << players[i].lv;
		spacing = findDigits(players[i].lv);
		spacing += 3;
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//EXP & EXP til next level
	for (int i = 0; i < players.size(); i++)
	{
		cout << "EXP: " << players[i].exp << " / " << players[i].lvEXP;
		spacing = findDigits(players[i].exp);
		spacing += 8;
		spacing += findDigits(players[i].lvEXP);
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//Relationship
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].relationship;
		spacing = players[i].relationship.size();
		displaySpacing(spacing, spaceMax);
	}
	dblEndl();

	//HP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "HP: " << players[i].currentHP << " / " << players[i].maxHP;

		equipBonus = players[i].weaponEquipped->HP;
		equipBonus += players[i].armorEquipped->HP;
		equipBonus += players[i].accEquipped->HP;
		spacing = findDigits(players[i].currentHP);
		spacing += 7;
		spacing += findDigits(players[i].maxHP);

		if (equipBonus != 0)
		{
			if (equipBonus > 0)
			{
				cout << " (+" << equipBonus << ")";
			}
			else
			{
				cout << " (-" << equipBonus << ")";
			}
			spacing += 4;
			spacing += findDigits(equipBonus);
		}

		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//SP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "SP: " << players[i].currentSP << " / " << players[i].maxSP;

		equipBonus = players[i].weaponEquipped->SP;
		equipBonus += players[i].armorEquipped->SP;
		equipBonus += players[i].accEquipped->SP;
		spacing = findDigits(players[i].currentSP);
		spacing += 7;
		spacing += findDigits(players[i].maxSP);

		if (equipBonus != 0)
		{
			if (equipBonus > 0)
			{
				cout << " (+" << equipBonus << ")";
			}
			else
			{
				cout << " (-" << equipBonus << ")";
			}
			spacing += 4;
			spacing += findDigits(equipBonus);
		}

		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//STR
	for (int i = 0; i < players.size(); i++)
	{
		cout << "STR: " << players[i].str;

		equipBonus = players[i].weaponEquipped->str;
		equipBonus += players[i].armorEquipped->str;
		equipBonus += players[i].accEquipped->str;
		spacing = findDigits(players[i].str);
		spacing += 5;

		if (equipBonus != 0)
		{
			if (equipBonus > 0)
			{
				cout << " (+" << equipBonus << ")";
			}
			else
			{
				cout << " (-" << equipBonus << ")";
			}
			spacing += 4;
			spacing += findDigits(equipBonus);
		}

		displaySpacing(spacing, spaceMax);
	}
	dblEndl();

	//Weapon
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].weaponEquipped->getName();
		spacing = players[i].weaponEquipped->getName().size();
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	for (int i = 0; i < players.size(); i++)
	{
		cout << " HP +" << players[i].weaponEquipped->HP;
		cout << " SP +" << players[i].weaponEquipped->SP;
		cout << " STR +" << players[i].weaponEquipped->str;
		spacing = 16;
		spacing += findDigits(players[i].weaponEquipped->HP);
		spacing += findDigits(players[i].weaponEquipped->SP);
		spacing += findDigits(players[i].weaponEquipped->str);
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//Armor
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].armorEquipped->getName();
		spacing = players[i].armorEquipped->getName().size();
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	for (int i = 0; i < players.size(); i++)
	{
		cout << " HP +" << players[i].armorEquipped->HP;
		cout << " SP +" << players[i].armorEquipped->SP;
		cout << " STR +" << players[i].armorEquipped->str;
		spacing = 16;
		spacing += findDigits(players[i].armorEquipped->HP);
		spacing += findDigits(players[i].armorEquipped->SP);
		spacing += findDigits(players[i].armorEquipped->str);
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	//Accessory
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].accEquipped->getName();
		spacing = players[i].accEquipped->getName().size();
		displaySpacing(spacing, spaceMax);
	}
	cout << endl;

	for (int i = 0; i < players.size(); i++)
	{
		cout << " HP +" << players[i].accEquipped->HP;
		cout << " SP +" << players[i].accEquipped->SP;
		cout << " STR +" << players[i].accEquipped->str;
		spacing = 16;
		spacing += findDigits(players[i].accEquipped->HP);
		spacing += findDigits(players[i].accEquipped->SP);
		spacing += findDigits(players[i].accEquipped->str);
		displaySpacing(spacing, spaceMax);
	}
	dblEndl();
}

void showItems(vector<Player>& players, vector<Item>& items, string& argument)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (argument == items[i].getName())
		{
			showItemToPlayer(players, items, i);
			return;
		}
		else
		{
			for (int ii = 0; ii < items[i].aliases.size(); ii++)
			{
				if (argument == items[i].aliases[ii])
				{
					showItemToPlayer(players, items, i);
					return;
				}
			}
		}
	}
}

void showItemToPlayer(vector<Player>& players, vector<Item>& items, int& i)
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

void showKeys(vector<Player>& players, Inventory& inventory, string& argument)
{
	for (int i = 0; i < inventory.keys.size(); i++)
	{
		if (argument == inventory.keys[i].name)
		{
			showKeyToPlayer(players, inventory, i);
			return;
		}

		for (int aliasIter = 0; aliasIter < inventory.keys[i].aliases.size(); aliasIter++)
		{
			if (argument == inventory.keys[i].aliases[aliasIter])
			{
				showKeyToPlayer(players, inventory, i);
				return;
			}
		}
	}
}

void showKeyToPlayer(vector<Player>& players, Inventory& inventory, int& i)
{
	cout << "Show " << inventory.keys[i].name << " to who?";
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
			if (players[ii].getName() == inventory.keys[i].personWithExpertise)
			{
				cout << inventory.keys[i].expertiseDescription;
				dblEndl();
				inventory.keys[i].purposeKnown = true;
				if (inventory.keys[i].actuallyGear == weapon)
				{
					for (int iii = 0; iii < inventory.weapons.size(); iii++)
					{
						if (inventory.weapons[iii]->keyNum == inventory.keys[i].getKeyNum())
						{
							inventory.weapons[iii]->beenDiscovered = true;
							inventory.keys.erase(inventory.keys.begin() + i);
							return;
						}
					}
				}
				if (inventory.keys[i].actuallyGear == accessory)
				{
					for (int iii = 0; iii < inventory.accessories.size(); iii++)
					{
						if (inventory.accessories[iii]->keyNum == inventory.keys[i].getKeyNum())
						{
							inventory.accessories[iii]->beenDiscovered = true;
							inventory.keys.erase(inventory.keys.begin() + i);
							return;
						}
					}
				}
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

void equipGear(vector<Player>& players, vector<shared_ptr<Weapon>>& weapons, vector<shared_ptr<Armor>>& armors, 
	vector<shared_ptr<Accessory>>& accessories, string& argument)
{
	for (int i = 0; i < weapons.size(); i++)
	{
		if (argument == weapons[i]->getName())
		{
			equipWeapon(players, weapons, i);
			return;
		}

		for (int ii = 0; ii < weapons[i]->aliases.size(); ii++)
		{
			if (argument == weapons[i]->aliases[ii])
			{
				equipWeapon(players, weapons, i);
				return;
			}
		}
	}
	
	for (int i = 0; i < armors.size(); i++)
	{
		if (argument == armors[i]->getName())
		{
			equipArmor(players, armors, i);
			return;
		}

		for (int ii = 0; ii < armors[i]->aliases.size(); ii++)
		{
			if (argument == armors[i]->aliases[ii])
			{
				equipArmor(players, armors, i);
				return;
			}
		}
	}

	for (int i = 0; i < accessories.size(); i++)
	{
		if (argument == accessories[i]->getName())
		{
			equipAccessory(players, accessories, i);
			return;
		}

		for (int ii = 0; ii < accessories[i]->aliases.size(); ii++)
		{
			if (argument == accessories[i]->aliases[ii])
			{
				equipAccessory(players, accessories, i);
				return;
			}
		}
	}
}

void equipWeapon(vector<Player>& players, vector<shared_ptr<Weapon>>& weapons, int& i)
{
	string recipient = "";
	int recipientNum = -1;
	int currentOwner = -1;
	int input = 0;

	if (weapons[i]->beenDiscovered)
	{
		cout << "Equip to who?" << endl;
		getline(cin, recipient);

		for (int ii = 0; ii < players.size(); ii++)
		{
			if (players[ii].getName() == recipient)
				recipientNum = ii;
			if (players[ii].weaponEquipped->getName() == weapons[i]->getName())
			{
				currentOwner = ii;
				cout << endl;
				cout << players[ii].getName() << " already has this equipped. Would you like to take it from them?" << endl;
				cout << "(1) Yes" << endl;
				cout << "(2) No" << endl;
				input = getDecision(1, 2);

				if (recipientNum != -1)
					break;
			}
		}

		if (recipientNum != -1)
		{
			if (input == 0)
			{
				cout << endl;
				players[recipientNum].weaponEquipped->equippedNum = -1;
				players[recipientNum].unequipWeapon();
				players[recipientNum].equipWeapon(weapons[i]);
				weapons[i]->equippedNum = players[recipientNum].getPlayerNum();
				cout << players[recipientNum].getName() << " equipped the " << weapons[i]->getName() << ".";
			}
			else if (input == 1)
			{
				players[recipientNum].weaponEquipped->equippedNum = -1;
				players[recipientNum].unequipWeapon();
				players[currentOwner].unequipWeapon();
				players[recipientNum].equipWeapon(weapons[i]);
				weapons[i]->equippedNum = players[recipientNum].getPlayerNum();
				cout << players[recipientNum].getName() << " equipped the " << weapons[i]->getName() << ".";
			}
			else
			{
				cout << "The " << weapons[i]->getName() << " remains on " << players[currentOwner].getName() << ".";
			}
			dblEndl();
		}
	}
	return;
}

void equipArmor(vector<Player>& players, vector<shared_ptr<Armor>>& armors, int& i)
{
	string recipient = "";
	int recipientNum = -1;
	int currentOwner = -1;
	int input = 0;

	if (armors[i]->beenDiscovered)
	{
		cout << "Equip to who?" << endl;
		getline(cin, recipient);

		for (int ii = 0; ii < players.size(); ii++)
		{
			if (players[ii].getName() == recipient)
				recipientNum = ii;
			if (players[ii].armorEquipped->getName() == armors[i]->getName())
			{
				currentOwner = ii;
				cout << endl;
				cout << players[ii].getName() << " already has this equipped. Would you like to take it from them?" << endl;
				cout << "(1) Yes" << endl;
				cout << "(2) No" << endl;
				input = getDecision(1, 2);

				if (recipientNum != -1)
					break;
			}
		}

		if (recipientNum != -1)
		{
			if (input == 0)
			{
				cout << endl;
				players[recipientNum].armorEquipped->equippedNum = -1;
				players[recipientNum].unequipArmor();
				players[recipientNum].equipArmor(armors[i]);
				armors[i]->equippedNum = players[recipientNum].getPlayerNum();
				cout << players[recipientNum].getName() << " equipped the " << armors[i]->getName() << ".";
			}
			else if (input == 1)
			{
				players[recipientNum].armorEquipped->equippedNum = -1;
				players[recipientNum].unequipArmor();
				players[currentOwner].unequipArmor();
				players[recipientNum].equipArmor(armors[i]);
				armors[i]->equippedNum = players[recipientNum].getPlayerNum();
				cout << players[recipientNum].getName() << " equipped the " << armors[i]->getName() << ".";
			}
			else
			{
				cout << "The " << armors[i]->getName() << " remains on " << players[currentOwner].getName() << ".";
			}
			dblEndl();
		}
	}
	return;
}

void equipAccessory(vector<Player>& players, vector<shared_ptr<Accessory>>& accessories, int& i)
{
	string recipient = "";
	int recipientNum = -1;
	int currentOwner = -1;
	int input = 0;

	if (accessories[i]->beenDiscovered)
	{
		cout << "Equip to who?" << endl;
		getline(cin, recipient);

		for (int ii = 0; ii < players.size(); ii++)
		{
			if (players[ii].getName() == recipient)
				recipientNum = ii;
			if (players[ii].accEquipped->getName() == accessories[i]->getName())
			{
				currentOwner = ii;
				cout << endl;
				cout << players[ii].getName() << " already has this equipped. Would you like to take it from them?" << endl;
				cout << "(1) Yes" << endl;
				cout << "(2) No" << endl;
				input = getDecision(1, 2);

				if (recipientNum != -1)
					break;
			}
		}

		if (recipientNum != -1)
		{
			if (input == 0)
			{
				cout << endl;
				players[recipientNum].accEquipped->equippedNum = -1;
				players[recipientNum].unequipAccessory();
				players[recipientNum].equipAccessory(accessories[i]);
				accessories[i]->equippedNum = players[recipientNum].getPlayerNum();
				cout << players[recipientNum].getName() << " equipped the " << accessories[i]->getName() << ".";
			}
			else if (input == 1)
			{
				players[recipientNum].accEquipped->equippedNum = -1;
				players[recipientNum].unequipAccessory();
				players[currentOwner].unequipAccessory();
				players[recipientNum].equipAccessory(accessories[i]);
				accessories[i]->equippedNum = players[recipientNum].getPlayerNum();
				cout << players[recipientNum].getName() << " equipped the " << accessories[i]->getName() << ".";
			}
			else
			{
				cout << "The " << accessories[i]->getName() << " remains on " << players[currentOwner].getName() << ".";
			}
			dblEndl();
		}
	}
	return;
}

void unequipGear(vector<Player>& players, vector<shared_ptr<Weapon>>& weapons, vector<shared_ptr<Armor>>& armors,
	vector<shared_ptr<Accessory>>& accessories, string& argument)
{
	for (int i = 0; i < weapons.size(); i++)
	{
		if (argument == weapons[i]->getName())
		{
			unequipWeapon(players, weapons, i);
			return;
		}

		for (int ii = 0; ii < weapons[i]->aliases.size(); ii++)
		{
			if (argument == weapons[i]->aliases[ii])
			{
				unequipWeapon(players, weapons, i);
				return;
			}
		}
	}
	
	for (int i = 0; i < armors.size(); i++)
	{
		if (argument == armors[i]->getName())
		{
			unequipArmor(players, armors, i);
			return;
		}
		for (int ii = 0; ii < armors[i]->aliases.size(); ii++)
		{
			if (argument == armors[i]->aliases[ii])
			{
				unequipArmor(players, armors, i);
				return;
			}
		}
	}

	for (int i = 0; i < accessories.size(); i++)
	{
		if (argument == accessories[i]->getName())
		{
			unequipAccessory(players, accessories, i);
			return;
		}
		for (int ii = 0; ii < accessories[i]->aliases.size(); ii++)
		{
			if (argument == accessories[i]->aliases[ii])
			{
				unequipAccessory(players, accessories, i);
				return;
			}
		}
	}
}

void unequipWeapon(vector<Player>& players, vector<shared_ptr<Weapon>>& weapons, int& i)
{
	if (weapons[i]->beenDiscovered)
	{
		if (weapons[i]->equippedNum != -1)
		{
			for (int ii = 0; ii < players.size(); ii++)
			{
				if (players[ii].getPlayerNum() == weapons[i]->equippedNum)
				{
					players[ii].unequipWeapon();
					weapons[i]->equippedNum = -1;
					cout << players[ii].getName() << " unequipped the " << weapons[i]->getName() << ".";
					dblEndl();
					return;
				}
			}
		}
	}
}

void unequipArmor(vector<Player>& players, vector<shared_ptr<Armor>>& armors, int& i)
{
	if (armors[i]->beenDiscovered)
	{
		if (armors[i]->equippedNum != -1)
		{
			for (int ii = 0; ii < players.size(); ii++)
			{
				if (players[ii].getPlayerNum() == armors[i]->equippedNum)
				{
					players[ii].unequipArmor();
					armors[i]->equippedNum = -1;
					cout << players[ii].getName() << " unequipped the " << armors[i]->getName() << ".";
					dblEndl();
					return;
				}
			}
		}
	}
}

void unequipAccessory(vector<Player>& players, vector<shared_ptr<Accessory>>& accessories, int& i)
{
	if (accessories[i]->beenDiscovered)
	{
		if (accessories[i]->equippedNum != -1)
		{
			for (int ii = 0; ii < players.size(); ii++)
			{
				if (players[ii].getPlayerNum() == accessories[i]->equippedNum)
				{
					players[ii].unequipAccessory();
					accessories[i]->equippedNum = -1;
					cout << players[ii].getName() << " unequipped the " << accessories[i]->getName() << ".";
					dblEndl();
					return;
				}
			}
		}
	}
}

void teamUp(int & i, Inventory& inventory, Room& room)
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
						inventory.keys.push_back(room.keys[ii]);
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
						inventory.items.push_back(room.items[ii]);
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

void explore(vector<Player>& players, int& floor, int& roomNum, Inventory& inventory)
{
	//Floor 0 Bools
	bool seeOpening = true;
	bool encounteredRat = false;

	//Floor 1 Bools
	bool floor1FirstTime = true;
	bool foundAria = false;
	bool greenhouseFirstTime = true;
	bool openedSafe = false;
	bool entrywayFirstTime = true;

	while (true)
	{
		if (floor == 0)
		{
			floor0(players, roomNum, floor, inventory, seeOpening, encounteredRat);
		}
		if (floor == 1)
		{
			floor1(players, roomNum, floor, inventory, floor1FirstTime, foundAria, greenhouseFirstTime, openedSafe, entrywayFirstTime);
		}
		if (floor == 2)
		{
			floor2(players, roomNum, floor, inventory);
		}
	}
}