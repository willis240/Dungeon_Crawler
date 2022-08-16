//combat.hpp

#ifndef COMBAT_HPP
#define COMBAT_HPP

#include<iostream>
#include<string>
#include<vector>
#include<random>

class Skill
{
private:
	std::string name;

public:
	int damage;
	bool isHealing;
	bool hasAOE;
	std::string description;

	std::string getName() { return name; };

	Skill(std::string inputName, int inputDamage, bool inputIsHealing, bool inputHasAOE, std::string inputDescription) :
		name(inputName), damage(inputDamage), isHealing(inputIsHealing), hasAOE(inputHasAOE), description(inputDescription) {};
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
	std::vector<std::string> exploreOptions{};
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
	std::vector<std::string> stances;
	std::vector<Skill> skills;

	std::string getName() { return name; };
	void reduceHP(int& lostHP);
	void reduceSP(int& lostSP);

	Enemy(std::string inputName, int inputMaxHP, int inputMaxSP, std::vector<std::string> inputStances, std::vector<Skill> inputSkills) :
		name(inputName), maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP), stances(inputStances), skills(inputSkills) {};
};

void displayCombatStats(std::vector<Player>& players, std::vector<Enemy>& enemies);
void displayPlayerActions(Player& player);
void displayAttackTargets(std::vector<Player>& players, std::vector<Enemy>& enemies);
void fight(std::vector<Player>& players, std::vector<Enemy>& enemies);
void victory(std::vector<Player>& players, std::vector<Enemy>& enemies);
void gameOver();

#endif
