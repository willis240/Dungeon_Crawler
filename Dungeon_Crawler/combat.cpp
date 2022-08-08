//combat.cpp

#include "player.hpp"
#include "game.hpp"
#include "combat.hpp"
using std::cout;
using std::endl;
using std::string;

void fight(std::vector<Player> & players, std::vector<Enemy> & enemies)
{
	//dummy
	cout << enemies[0].getName() << ": " << enemies[0].currentHP << " / " << enemies[0].maxHP << endl;
}