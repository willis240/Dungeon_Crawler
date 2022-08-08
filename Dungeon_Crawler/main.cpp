//main.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

int main()
{
	Player player = startGame();
	std::vector<Item> items{};
	std::vector<Key> keys{};

	int floorNum = 0;
	int roomNum = 0;

	explore(player, floorNum, roomNum, items, keys);

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