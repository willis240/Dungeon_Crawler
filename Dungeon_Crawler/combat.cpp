//combat.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

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
	while (true)
	{
		short playerNum = 0;
		while (playerNum < players.size())
		{
			if (players[playerNum].currentHP > 0)
			{
				system("CLS");
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

						for (int ii = 0; ii < enemies.size(); ii++)
						{
							if (ii == target)
							{
								enemies[ii].reduceHP(players[playerNum].str);
								playerNum++;
							}
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
							system("CLS");
							displayAttackTargets(players, enemies);
							int target = getDecisionEscapable(0, enemies.size() - 1);

							for (int ii = 0; ii < enemies.size(); ii++)
							{
								if (ii == target)
								{
									int damageDealt = players[playerNum].str + players[playerNum].skills[pickSkill].damage;
									enemies[ii].reduceHP(damageDealt);
									playerNum++;
								}
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
						}
					}
					break;

					//Defend
					case 3:
					{

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
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].currentHP > 0)
			{
				system("CLS");
				displayCombatStats(players, enemies);

				std::mt19937 rng(time(NULL));
				std::uniform_int_distribution<int> gen(0, enemies[i].skills.size() - 1);
				int actionTaken = gen(rng);

				std::mt19937 targetRng(time(NULL));
				std::uniform_int_distribution<int> targetGen(0, players.size() - 1);
				int targetChosen = targetGen(targetRng);

				players[targetChosen].reduceHP(enemies[i].skills[actionTaken].damage);

				short partyKO = 0;
				for (int i = 0; i < players.size(); i++)
				{
					if (players[i].currentHP == 0)
						partyKO++;

					if (partyKO == players.size())
						gameOver();
				}
			}
		}
	}
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
		cout << "(" << i << ") " << player.skills[i].getName() << endl;
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
	cout << "    ITEMS" << endl;
	if (items.size() > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			cout << "    (" << i << ") " << items[i].getName();
			cout << " -- Restores " << items[i].restoredHP << " HP and " << items[i].restoredSP << " SP" << endl;
		}
	}
	else
		cout << "    none";
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
	while (number)
	{
		number /= 10;
		spacing++;
	}

	return spacing;
}

void victory(vector<Player>& players, vector<Enemy>& enemies)
{
	//Give EXP to player characters, check for level ups, ask player what stats they want to increase
	system("CLS");
	cout << "Victory!" << endl;
	system("pause");
}

void gameOver()
{
	system("CLS");
	cout << "And so you fall, never realizing your freedom." << endl;
	system("pause");
	exit(1);
}