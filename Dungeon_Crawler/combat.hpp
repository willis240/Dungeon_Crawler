//combat.hpp

#ifndef COMBAT_HPP
#define COMBAT_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<random>
#include<sstream>
#include <Windows.h>

class Skill
{
private:
	std::string name;

public:
	int damage;
	bool isHealing;
	bool hasAOE;
	int SPcost;
	short attackDirection = -1;
	std::string description;

	std::string getName() { return name; };

	Skill(std::string inputName, int inputDamage, bool inputIsHealing, bool inputHasAOE, int inputSPcost, std::string inputDescription) :
		name(inputName), damage(inputDamage), isHealing(inputIsHealing), hasAOE(inputHasAOE), SPcost(inputSPcost), description(inputDescription) {};

	Skill(std::string inputName, int inputDamage, bool inputIsHealing, bool inputHasAOE, int inputSPcost, short inputAttackDirection, std::string inputDescription) :
		name(inputName), damage(inputDamage), isHealing(inputIsHealing), hasAOE(inputHasAOE), SPcost(inputSPcost), attackDirection(inputAttackDirection),
		description(inputDescription) {};
};

class Weapon
{
public:
	std::string name;
	int might;

	Weapon(std::string inputName, int inputMight) : name(inputName), might(inputMight) {};
};

class Player
{
private:
	std::string name;

public:
	//Member Variables
	int maxHP;
	int currentHP;
	int maxSP;
	int currentSP;
	int str = 1;
	int exp = 0;
	int lv = 1;
	int lvEXP = 20;
	short guardDirection = -1;
	std::vector<std::string> exploreOptions{"help", "check", "enter", "inv"};
	std::vector<std::string> actions{"Attack", "Skills", "Items", "Defend"};
	std::vector<Skill> skills;

	//Member Functions
	std::string getName() { return name; };
	void restoreHP(int& healedHP);
	void restoreSP(int& healedSP);
	void reduceHP(int& lostHP);
	void reduceSP(int& lostSP);

	//Constructors
	Player(std::string inputName, int inputMaxHP, int inputMaxSP, std::vector<Skill> inputSkills) :
		name(inputName), maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP), skills(inputSkills) {};

};

class Enemy
{
private:
	std::string name;

public:
	int maxHP;
	int currentHP;
	int maxSP;
	int currentSP;
	int expWorth;
	bool offBalance = false;
	std::vector<std::string> stances;
	std::vector<Skill> skills;

	std::string getName() { return name; };
	void alterName(std::string& nameEdit) { name += nameEdit; };
	void reduceHP(int& lostHP);
	void reduceSP(int& lostSP);

	Enemy(std::string inputName, int inputMaxHP, int inputMaxSP, int inputExpWorth, std::vector<std::string> inputStances, std::vector<Skill> inputSkills) :
		name(inputName), maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP), expWorth(inputExpWorth), stances(inputStances), skills(inputSkills) {};
};

void countEnemyNames(std::vector<Enemy>& enemies);
void displayEnemiesTargets(std::vector<Player>& players, std::vector<Enemy>& enemies, std::vector<short>& enemiesTargets);
void displayCombatStats(std::vector<Player>& players, std::vector<Enemy>& enemies);
void displayPlayerActions(Player& player);
void displayPlayerSkills(Player& player);
void displayAttackTargets(std::vector<Player>& players, std::vector<Enemy>& enemies);
void displaySupportTargets(std::vector<Player>& players, std::vector<Enemy>& enemies);
int getDecisionEscapable(const int minChoice, const int maxChoice);
void displaySpacing(int& spacing, const int spaceMax);
int findDigits(int number);
void victory(std::vector<Player>& players, std::vector<Enemy>& enemies);
void gameOver();

#endif
