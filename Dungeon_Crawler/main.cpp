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

	int floorNum = 0;
	int roomNum = 0;

	//CODE FOR TESTING ACCESSORIES
	/*
	Accessory placeholder("Placeholder", "Just a placeholder", 1, 2, 3);
	std::shared_ptr<Accessory> placeholderPtr = std::make_shared<Accessory>(placeholder);
	inventory.accessories.push_back(placeholderPtr);
	*/

	//CODE FOR TESTING COMBAT
	/*
	Skill ratPunch("Punch", 2, false, false, 0, right, "The rat jumps up and punches you in the neck");
	Skill doubleSlash("Double Slash", 3, false, false, 2, "Player 2 makes two quick diagonal slashes using each of their swords");
	Enemy rat("Rat", 10, 10, 10, { "" }, { ratPunch });
	Enemy bat("Bat", 10, 10, 10, { "" }, { ratPunch });
	Player player2("Player 2", 1, 10, 10, { doubleSlash });
	players.push_back(player2);
	vector<Enemy> enemies = { rat, bat, rat };
	Item grapefruit("Grapefruit", 5, 5, "A juicy fruit, for sure");
	inventory.items.push_back(grapefruit);
	fight(players, enemies, inventory.items);
	*/

	//CODE FOR TESTING LEVEL UPS
	/*
	Skill doubleSlash("Double Slash", 3, false, false, 2, "Selena makes two quick diagonal slashes using each of their swords");
	Player player2("Selena", 10, 10, { doubleSlash });
	vector<Player> players = { player, player2 };
	Skill ratPunch("Punch", 2, false, false, 0, "The rat jumps up and punches you in the neck");
	Enemy rat("Rat", 10, 10, 30, { "" }, { ratPunch });
	vector<Enemy> enemies = { rat, rat };
	victory(players, enemies);
	*/

	explore(players, floorNum, roomNum, inventory);

}