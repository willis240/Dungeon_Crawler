//main.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;

int main()
{
	Player player = startGame();
	vector<Player> players = { player };
	Inventory inventory;

	int floorNum = 1;
	int roomNum = 0;

	//A SECOND PLAYER CHARACTER, FOR TESTING
	
	Player Selena("Selena", 1, 7, 13, {});
	players.push_back(Selena);

	Skill quickSlash("Quick Slash", 4, false, false, 0, left, "The man on the left slashes from the left!");
	Enemy manOnTheLeft("The Left Man", 12, 12, 10, { "" }, { quickSlash });
	vector<Enemy> enemies = { manOnTheLeft };
	fight(players, enemies, inventory.items);

	explore(players, floorNum, roomNum, inventory);

}