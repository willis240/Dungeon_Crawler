//player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include<iostream>
#include<string>
#include<vector>

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

	//Member Functions
	std::string getName() { return name; };

	//Constructors
	Player(std::string inputName, int inputMaxHP, int inputMaxSP) : name(inputName),
		maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), currentSP(inputMaxSP) {};

};

#endif
