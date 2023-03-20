//combat.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;

void Player::equipWeapon(std::shared_ptr<Weapon> weaponToEquip)
{
	weaponEquipped = std::move(weaponToEquip);
	maxHP += weaponEquipped->HP;
	maxSP += weaponEquipped->SP;
	str += weaponEquipped->str;
	if (maxHP < currentHP)
		currentHP = maxHP;
	if (maxSP < currentSP)
		currentSP = maxSP;
}

void Player::unequipWeapon()
{
	maxHP -= weaponEquipped->HP;
	maxSP -= weaponEquipped->SP;
	str -= weaponEquipped->str;
	if (maxHP < currentHP)
		currentHP = maxHP;
	if (maxSP < currentSP)
		currentSP = maxSP;
	weaponEquipped = noWeaponPtr;
}

void Player::equipArmor(std::shared_ptr<Armor> armorToEquip)
{
	armorEquipped = std::move(armorToEquip);
	maxHP += armorEquipped->HP;
	maxSP += armorEquipped->SP;
	str += armorEquipped->str;
	if (maxHP < currentHP)
		currentHP = maxHP;
	if (maxSP < currentSP)
		currentSP = maxSP;
}

void Player::unequipArmor()
{
	maxHP -= armorEquipped->HP;
	maxSP -= armorEquipped->SP;
	str -= armorEquipped->str;
	if (maxHP < currentHP)
		currentHP = maxHP;
	if (maxSP < currentSP)
		currentSP = maxSP;
	armorEquipped = noArmorPtr;
}

void Player::equipAccessory(std::shared_ptr<Accessory> accToEquip)
{
	accEquipped = std::move(accToEquip);
	maxHP += accEquipped->HP;
	maxSP += accEquipped->SP;
	str += accEquipped->str;
	if (maxHP < currentHP)
		currentHP = maxHP;
	if (maxSP < currentSP)
		currentSP = maxSP;
}

void Player::unequipAccessory()
{
	maxHP -= accEquipped->HP;
	maxSP -= accEquipped->SP;
	str -= accEquipped->str;
	if (maxHP < currentHP)
		currentHP = maxHP;
	if (maxSP < currentSP)
		currentSP = maxSP;
	accEquipped = nothingPtr;
}

void Player::restoreHP(int& healedHP)
{
	currentHP += healedHP;
	if (currentHP > maxHP)
		currentHP = maxHP;
}

void Player::restoreSP(int& healedSP)
{
	currentSP += healedSP;
	if (currentSP > maxSP)
		currentSP = maxSP;
}

void Player::reduceHP(int& lostHP)
{
	currentHP -= lostHP;
	if (currentHP < 0)
		currentHP = 0;
}

void Player::reduceSP(int& lostSP)
{
	currentSP -= lostSP;
	if (currentSP < 0)
		currentSP = 0;
}

void Enemy::reduceHP(int& lostHP)
{
	currentHP -= lostHP;
	if (currentHP < 0)
		currentHP = 0;
}

void Enemy::reduceSP(int& lostSP)
{
	currentSP -= lostSP;
	if (currentSP < 0)
		currentSP = 0;
}

void fight(vector<Player> & players, vector<Enemy> & enemies, vector<Item> & items)
{
	countEnemyNames(enemies);

	while (true)
	{
		short playersKO = 0;
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].currentHP == 0)
				playersKO++;

			if (playersKO == players.size())
				gameOver();
		}

		vector<short> enemyActionsTaken = {};
		vector<short> enemiesTargets = {};
		
		for (int i = 0; i < enemies.size(); i++)
		{
			std::mt19937 rng(time(NULL));
			std::uniform_int_distribution<int> gen(0, enemies[i].skills.size() - 1);
			enemyActionsTaken.push_back(gen(rng));

			std::mt19937 targetRng(time(NULL));
			std::uniform_int_distribution<int> targetGen(0, players.size() - 1);
			short target = targetGen(targetRng);
			if (players[target].currentHP == 0)
			{
				for (int i = 0; i < players.size(); i++)
				{
					if (players[i].currentHP > 0)
					{
						target = i;
						break;
					}
				}
			}
			enemiesTargets.push_back(target);
		}

		short playerNum = 0;
		while (playerNum < players.size())
		{
			players[playerNum].guardDirection = noDirection;
			if (players[playerNum].currentHP > 0)
			{
				system("CLS");
				displayEnemiesTargets(players, enemies, enemiesTargets);
				displayCombatStats(players, enemies);
				displayPlayerActions(players[playerNum]);

				int input = getDecision(0, players[playerNum].actions.size() - 1);

				switch (input)
				{
					//Attack
					case 0:
					{
						system("CLS");
						displayAttackTargets(players, enemies);
						int target = getDecisionEscapable(0, enemies.size() - 1);

						if (target != -1)
						{
							int damageDealt = players[playerNum].str;

							if (enemies[target].offBalance)
								damageDealt *= 2;

							if (enemies[target].currentHP > 0)
							{
								cout << players[playerNum].getName() << " attacks " << enemies[target].getName() << "!" << endl;
								if (enemies[target].offBalance)
									cout << "It's a critical hit!!!" << endl;
								cout << enemies[target].getName() << " receives " << damageDealt << " points of damage!" << endl << endl;
							}
							else
							{
								cout << players[playerNum].getName() << " wasted a perfectly good turn on attacking " << enemies[target].getName() << "'s corpse." << endl;
								cout << "Alright. That sure was a turn, I guess." << endl << endl;
							}

							enemies[target].reduceHP(damageDealt);
								
							system("pause");
							cout << endl;

							playerNum++;
						}
					}
					break;

					//Skills
					case 1:
					{
						system("CLS");
						displayCombatStats(players, enemies);
						displayPlayerSkills(players[playerNum]);

						int pickSkill = getDecisionEscapable(0, players[playerNum].skills.size() - 1);

						if (pickSkill != -1)
						{
							if (players[playerNum].currentSP >= players[playerNum].skills[pickSkill].SPcost)
							{
								if (players[playerNum].skills[pickSkill].hasAOE)
								{
									cout << players[playerNum].skills[pickSkill].description << endl;
									players[playerNum].reduceSP(players[playerNum].skills[pickSkill].SPcost);
									int damageDealt = 0;
									for (int i = 0; i < enemies.size(); i++)
									{
										if (enemies[i].currentHP > 0)
										{
											damageDealt = players[playerNum].str + players[playerNum].skills[pickSkill].damage;
											if (enemies[i].offBalance)
											{
												cout << "It's a critical hit!!!" << endl;
												damageDealt *= 2;
											}
											cout << enemies[i].getName() << " receives " << damageDealt << " points of damage!";
											dblEndl();
											enemies[i].reduceHP(damageDealt);
											system("pause");
											cout << endl;
										}
									}
									playerNum++;
								}
								else
								{
									system("CLS");
									displayAttackTargets(players, enemies);
									int target = getDecisionEscapable(0, enemies.size() - 1);

									if (target != -1)
									{
										int damageDealt = players[playerNum].str + players[playerNum].skills[pickSkill].damage;
										players[playerNum].reduceSP(players[playerNum].skills[pickSkill].SPcost);

										if (enemies[target].offBalance)
											damageDealt *= 2;

										if (enemies[target].currentHP > 0)
										{
											cout << players[playerNum].skills[pickSkill].description << endl;
											if (enemies[target].offBalance)
												cout << "It's a critical hit!!!" << endl;
											cout << enemies[target].getName() << " receives " << damageDealt << " points of damage!" << endl << endl;
										}
										else
										{
											cout << players[playerNum].getName() << " wastes a perfectly good " << players[playerNum].skills[pickSkill].getName();
											cout << " on " << enemies[target].getName() << "'s corpse." << endl;
											cout << "Huh. Well, I guess it is your turn. Who am I to tell you what to do?" << endl << endl;
										}
										enemies[target].reduceHP(damageDealt);

										system("pause");
										cout << endl;
										playerNum++;
									}
								}
							}
							else
							{
								cout << players[playerNum].getName() << " did not have enough SP to use " << players[playerNum].skills[pickSkill].getName() << "!" << endl;
								system("pause");
								cout << endl;
							}
						}
					}
					break;

					//Items
					case 2:
					{
						system("CLS");
						displayCombatStats(players, enemies);
						displayItemsBattle(items);

						int pickItem = getDecisionEscapable(0, items.size() - 1);

						if (pickItem != -1)
						{
							system("CLS");
							displaySupportTargets(players, enemies);
							int target = getDecisionEscapable(0, players.size() - 1);

							if (target != -1)
							{
								players[target].restoreHP(items[pickItem].restoredHP);
								players[target].restoreSP(items[pickItem].restoredSP);
								items.erase(items.begin() + pickItem);
								playerNum++;
							}
						}
					}
					break;

					//Defend
					case 3:
					{
						cout << "Choose a direction to focus your defense on: " << endl << endl;
						cout << "(0) Left" << endl;
						cout << "(1) Right" << endl;
						cout << "(2) High" << endl;
						cout << "(3) Low" << endl;
						short pickDirection = getDecisionEscapable(0, 3);

						if (pickDirection != -1)
						{
							if (pickDirection == 0)
								players[playerNum].guardDirection = left;
							else if (pickDirection == 1)
								players[playerNum].guardDirection = right;
							else if (pickDirection == 2)
								players[playerNum].guardDirection = high;
							else if (pickDirection == 3)
								players[playerNum].guardDirection = low;
							playerNum++;
						}
					}
					break;
				}

				short enemyKO = 0;
				for (int i = 0; i < enemies.size(); i++)
				{
					if (enemies[i].currentHP == 0)
						enemyKO++;

					if (enemyKO == enemies.size())
					{
						victory(players, enemies);
						return;
					}
				}
			}
			else
			{
				playerNum++;
			}
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].currentHP > 0)
			{
				enemies[i].offBalance = false;

				if (enemies[i].skills[enemyActionsTaken[i]].hasAOE)
				{
					GuardType playerBlock = none;
					vector<int> damagesDealt = {};
					vector<int> partySPRestored = {};

					cout << enemies[i].getName() << " unleashes " << enemies[i].skills[enemyActionsTaken[i]].getName() << " upon the ENTIRE party!!" << endl;
					for (int ii = 0; ii < players.size(); ii++)
					{
						playerBlock = determineGuardType(enemies[i], players[ii], enemyActionsTaken[i]);
						damagesDealt.push_back(calculateDamage(enemies[i], players[ii], enemyActionsTaken[i], playerBlock));
						partySPRestored.push_back(dealDamage(enemies[i], players[ii], damagesDealt[ii], playerBlock));

						if (playerBlock == perfect)
						{
							cout << players[ii].getName() << " perfectly blocked " << enemies[i].getName() << "'s attack!!" << endl;
							cout << players[ii].getName() << " takes " << damagesDealt[ii] << " damage and restores " << partySPRestored[ii] << " SP!" << endl;
							cout << enemies[i].getName() << " is now off-balance and incredibly susceptible to attacks!" << endl << endl;
							system("pause");
							cout << endl;
						}
						else if (playerBlock == standard)
						{
							cout << players[ii].getName() << " blocked " << enemies[i].getName() << "'s attack!" << endl;
							cout << players[ii].getName() << " takes " << damagesDealt[ii] << " damage and restores " << partySPRestored[ii] << " SP!" << endl << endl;
							system("pause");
							cout << endl;
						}
						else
						{
							cout << players[ii].getName() << " takes " << enemies[i].skills[enemyActionsTaken[i]].damage << " damage." << endl << endl;
							system("pause");
							cout << endl;
						}
					}
				}
				else
				{
					GuardType playerBlock = determineGuardType(enemies[i], players[enemiesTargets[i]], enemyActionsTaken[i]);
					int damageDealt = calculateDamage(enemies[i], players[enemiesTargets[i]], enemyActionsTaken[i], playerBlock);
					int healedSP = dealDamage(enemies[i], players[enemiesTargets[i]], damageDealt, playerBlock);

					if (playerBlock == perfect)
					{
						//Perfect Block
						cout << enemies[i].getName() << " uses " << enemies[i].skills[enemyActionsTaken[i]].getName() << "!" << endl;
						cout << players[enemiesTargets[i]].getName() << " perfectly blocked " << enemies[i].getName() << "'s attack!!" << endl;
						cout << players[enemiesTargets[i]].getName() << " takes " << damageDealt << " damage and restores " << healedSP << " SP!" << endl;
						cout << enemies[i].getName() << " is now off-balance and incredibly susceptible to attacks!" << endl << endl;
						system("pause");
						cout << endl;
					}
					else if (playerBlock == standard)
					{
						//Normal Block
						cout << enemies[i].getName() << " uses " << enemies[i].skills[enemyActionsTaken[i]].getName() << "!" << endl;
						cout << players[enemiesTargets[i]].getName() << " blocked " << enemies[i].getName() << "'s attack!" << endl;
						cout << players[enemiesTargets[i]].getName() << " takes " << damageDealt << " damage and restores " << healedSP << " SP!" << endl << endl;
						system("pause");
						cout << endl;
					}
					else
					{
						//No Block
						cout << enemies[i].getName() << " uses " << enemies[i].skills[enemyActionsTaken[i]].getName() << "!" << endl;
						cout << players[enemiesTargets[i]].getName() << " takes " << enemies[i].skills[enemyActionsTaken[i]].damage << " damage." << endl << endl;
						system("pause");
						cout << endl;
					}
				}
			}
		}
	}
}

GuardType determineGuardType(Enemy& enemy, Player& player, short& enemyAction)
{
	GuardType block = none;

	if (player.guardDirection == enemy.skills[enemyAction].attackDirection)
	{
		if (player.guardDirection != noDirection)
			block = perfect;
	}
	else if (player.guardDirection != noDirection)
		block = standard;
	else
		block = none;

	return block;
}

int calculateDamage(Enemy& enemy, Player& player, short& enemyAction, GuardType& block)
{
	int damageDealt = 0;
	if (block == perfect)
	{
		damageDealt = enemy.skills[enemyAction].damage * 0.2;
	}
	else if (block == standard)
	{
		damageDealt = enemy.skills[enemyAction].damage * 0.5;
	}
	else
	{
		damageDealt = enemy.skills[enemyAction].damage;
	}
	return damageDealt;
}

int dealDamage(Enemy& enemy, Player& player, int& damageDealt, GuardType& block)
{
	int healedSP = 0;
	if (block == perfect)
	{
		healedSP = player.maxSP * 0.2;
		enemy.offBalance = true;
	}
	else if (block == standard)
	{
		healedSP = player.maxSP * 0.1;
	}
	else
		healedSP = 0;

	player.restoreSP(healedSP);
	player.reduceHP(damageDealt);

	return healedSP;
}

void countEnemyNames(vector<Enemy>& enemies)
{
	map<string, int> enemyNameTracker;
	for (int i = 0; i < enemies.size(); i++)
	{
		auto result = enemyNameTracker.insert(std::pair<string, int>(enemies[i].getName(), 1));
		if (result.second == false)
			result.first->second++;
	}
	for (auto& elem : enemyNameTracker)
	{
		int enemyNum = 1;
		if (elem.second > 1)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].getName() == elem.first)
				{
					string nameEdit = " " + std::to_string(enemyNum);
					enemies[i].alterName(nameEdit);
					enemyNum++;
				}
			}
		}
	}
}

void displayEnemiesTargets(vector<Player>& players, vector<Enemy>& enemies, vector<short>& enemiesTargets)
{
	int targetIter = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].currentHP > 0)
		{
			cout << enemies[i].getName() << " eyes " << players[enemiesTargets[targetIter]].getName() << " suspiciously." << endl;
			targetIter++;
		}
	}
	cout << endl;
}

void displayCombatStats(vector<Player>& players, vector<Enemy>& enemies)
{
	int spacing = 0;

	//Enemy Names
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << enemies[i].getName();
		spacing = enemies[i].getName().size();
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Enemy HP
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << "HP " << enemies[i].currentHP << " / " << enemies[i].maxHP;
		spacing = 6;
		spacing += findDigits(enemies[i].currentHP);
		spacing += findDigits(enemies[i].maxHP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	dblEndl();

	//Player Names
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].getName();
		spacing = players[i].getName().size();
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Player HP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "HP " << players[i].currentHP << " / " << players[i].maxHP;
		spacing = 6;
		spacing += findDigits(players[i].currentHP);
		spacing += findDigits(players[i].maxHP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Player SP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "SP " << players[i].currentSP << " / " << players[i].maxSP;
		spacing = 6;
		spacing += findDigits(players[i].currentSP);
		spacing += findDigits(players[i].maxSP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	dblEndl();
}

void displayPlayerActions(Player& player)
{
	cout << "It's " << player.getName() << "'s turn!";
	dblEndl();
	for (int i = 0; i < player.actions.size(); i++)
	{
		cout << "(" << i << ") " << player.actions[i] << endl;
	}
}

void displayPlayerSkills(Player& player)
{
	cout << "It's " << player.getName() << "'s turn!";
	dblEndl();
	cout << "SKILLS" << endl;
	for (int i = 0; i < player.skills.size(); i++)
	{
		cout << "(" << i << ") " << player.skills[i].getName() << " - " << player.skills[i].SPcost << " SP" << endl;
	}
}

void displayAttackTargets(vector<Player>& players, vector<Enemy>& enemies)
{
	int spacing = 0;

	//Enemy Names
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << "(" << i << ") " << enemies[i].getName();
		spacing = enemies[i].getName().size();
		displaySpacing(spacing, 15);
		spacing = 0;
	}
	cout << endl;

	//Enemy HP
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << "HP " << enemies[i].currentHP << " / " << enemies[i].maxHP;
		spacing = 6;
		spacing += findDigits(enemies[i].currentHP);
		spacing += findDigits(enemies[i].maxHP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	dblEndl();

	//Player Names
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].getName();
		spacing = players[i].getName().size();
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Player HP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "HP " << players[i].currentHP << " / " << players[i].maxHP;
		spacing = 6;
		spacing += findDigits(players[i].currentHP);
		spacing += findDigits(players[i].maxHP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Player SP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "SP " << players[i].currentSP << " / " << players[i].maxSP;
		spacing = 6;
		spacing += findDigits(players[i].currentSP);
		spacing += findDigits(players[i].maxSP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	dblEndl();

	cout << "Enter the number of your target: ";
}

void displaySupportTargets(vector<Player>& players, vector<Enemy>& enemies)
{
	int spacing = 0;

	//Enemy Names
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << enemies[i].getName();
		spacing = enemies[i].getName().size();
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Enemy HP
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << "HP " << enemies[i].currentHP << " / " << enemies[i].maxHP;
		spacing = 6;
		spacing += findDigits(enemies[i].currentHP);
		spacing += findDigits(enemies[i].maxHP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	dblEndl();

	//Player Names
	for (int i = 0; i < players.size(); i++)
	{
		cout << "(" << i << ") " << players[i].getName();
		spacing = players[i].getName().size();
		displaySpacing(spacing, 15);
		spacing = 0;
	}
	cout << endl;

	//Player HP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "HP " << players[i].currentHP << " / " << players[i].maxHP;
		spacing = 6;
		spacing += findDigits(players[i].currentHP);
		spacing += findDigits(players[i].maxHP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	//Player SP
	for (int i = 0; i < players.size(); i++)
	{
		cout << "SP " << players[i].currentSP << " / " << players[i].maxSP;
		spacing = 6;
		spacing += findDigits(players[i].currentSP);
		spacing += findDigits(players[i].maxSP);
		displaySpacing(spacing, 19);
		spacing = 0;
	}
	cout << endl;

	dblEndl();

	cout << "Enter the number of your target: ";
}

int getDecisionEscapable(const int minChoice, const int maxChoice)
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
			return (-1);
		}
		else
		{
			return input;
		}
	}
}

void displayItemsBattle(vector<Item>& items)
{
	cout << "ITEMS" << endl;
	if (items.size() > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			cout << "(" << i << ") " << items[i].getName();
			cout << " -- Restores " << items[i].restoredHP << " HP and " << items[i].restoredSP << " SP" << endl;
		}
	}
	else
		cout << "none";
	dblEndl();
}

void displaySpacing(int& spacing, const int spaceMax)
{
	while (spacing < spaceMax)
	{
		cout << " ";
		spacing++;
	}
}

int findDigits(int number)
{
	int spacing = 0;

	if (number == 0)
		spacing++;

	while (number)
	{
		number /= 10;
		spacing++;
	}

	return spacing;
}

void victory(vector<Player>& players, vector<Enemy>& enemies)
{
	system("CLS");

	int battleEXP = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		battleEXP += enemies[i].expWorth;
	}

	cout << "Victory!" << endl;
	if (players.size() == 1)
		cout << players[0].getName() << " gained " << battleEXP << " EXP!" << endl << endl;
	else
		cout << "The party gained " << battleEXP << " EXP!" << endl << endl;

	system("pause");

	for (int i = 0; i < players.size(); i++)
	{
		system("CLS");
		players[i].guardDirection = noDirection;

		players[i].exp += battleEXP;
		if (players[i].exp >= players[i].lvEXP)
		{
			int initialLv = players[i].lv;
			while (players[i].exp >= players[i].lvEXP)
			{
				players[i].lv++;
				players[i].exp -= players[i].lvEXP;
				players[i].lvEXP *= 2;
			}

			cout << "LEVEL UP!!" << endl;
			cout << players[i].getName() << "'s level increased from " << initialLv << " to " << players[i].lv << endl << endl;
			
			while (initialLv < players[i].lv)
			{
				cout << players[i].getName() << "'s current stats:" << endl;
				cout << "Max HP: " << players[i].maxHP << endl;
				cout << "Max SP: " << players[i].maxSP << endl;
				cout << "STR:    " << players[i].str;
				dblEndl();

				cout << "Pick a stat to increase: " << endl << endl;
				cout << "(0) Max HP +2" << endl;
				cout << "(1) Max SP +2" << endl;
				cout << "(2) Str    +1" << endl;
				cout << endl;

				int input = getDecision(0, 2);

				switch (input)
				{
					//Max HP
					case 0:
					{
						int tempMaxHP = players[i].maxHP;
						players[i].maxHP += 2;
						cout << players[i].getName() << "'s Max HP increased from " << tempMaxHP << " to " << players[i].maxHP << "!";
						dblEndl();
					}
					break;

					//Max SP
					case 1:
					{
						int tempMaxSP = players[i].maxSP;
						players[i].maxSP += 2;
						cout << players[i].getName() << "'s Max HP increased from " << tempMaxSP << " to " << players[i].maxSP << "!";
						dblEndl();
					}
					break;

					//Str
					case 2:
					{
						int tempSTR = players[i].str;
						players[i].str += 1;
						cout << players[i].getName() << "'s STR increased from " << tempSTR << " to " << players[i].str << "!";
						dblEndl();
					}
					break;
				}
				initialLv++;
				system("pause");
				system("CLS");
			}
		}
	}
}

void gameOver()
{
	system("CLS");
	cout << "And so you fall, never realizing your freedom." << endl;
	system("pause");
	exit(1);
}