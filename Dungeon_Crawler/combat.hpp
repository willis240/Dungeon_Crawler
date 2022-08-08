//combat.hpp

#ifndef COMBAT_HPP
#define COMBAT_HPP

class Enemy
{
private:
	std::string name;

public:
	int maxHP;
	int currentHP;
	int maxSP;
	int currentSP;

	std::string getName() { return name; };

	Enemy(std::string inputName, int inputMaxHP, int inputMaxSP) : name(inputName),
		maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP) {};
};

void fight(std::vector<Player>& players, std::vector<Enemy>& enemies);

#endif