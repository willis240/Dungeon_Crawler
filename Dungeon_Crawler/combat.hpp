//combat.hpp

#ifndef COMBAT_HPP
#define COMBAT_HPP

#include<iostream>
#include<string>
#include<vector>

class Action
{
private:
	std::string name;

public:
	int damage;
	bool hasAOE;
	std::string description;

	std::string getName() { return name; };

	Action(std::string inputName, int inputDamage, bool inputHasAOE, std::string inputDescription) :
		name(inputName), damage(inputDamage), hasAOE(inputHasAOE), description(inputDescription) {};
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
	std::vector<Action> actions;

	//Member Functions
	std::string getName() { return name; };
	void restoreHP(int& healedHP);
	void restoreSP(int& healedSP);

	//Constructors
	Player(std::string inputName, int inputMaxHP, int inputMaxSP) : name(inputName),
		maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP) {};

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
	std::vector<Action> actions;

	std::string getName() { return name; };

	Enemy(std::string inputName, int inputMaxHP, int inputMaxSP, std::vector<std::string> inputStances, std::vector<Action> inputActions) :
		name(inputName), maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP), stances(inputStances), actions(inputActions) {};
};

void fight(std::vector<Player>& players, std::vector<Enemy>& enemies);

#endif
