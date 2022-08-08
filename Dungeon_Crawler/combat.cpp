//combat.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::string;

void fight(std::vector<Player> & players, std::vector<Enemy> & enemies)
{
	cout << enemies[0].getName() << ": " << enemies[0].currentHP << " / " << enemies[0].maxHP << endl;
}