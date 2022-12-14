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
	int roomNum = 5;

	//CODE FOR TESTING GEAR
	Weapon stabbyThingy("Stabby Thingy", "Just a thing for stabbing", 1, 2, 3);
	std::shared_ptr<Weapon> stabbyThingyPtr = std::make_shared<Weapon>(stabbyThingy);
	inventory.weapons.push_back(stabbyThingyPtr);

	Weapon stabbyThingy2("Stabby Thingy 2", "Just a thing for stabbing", 0, 5, 3);
	std::shared_ptr<Weapon> stabbyThingy2Ptr = std::make_shared<Weapon>(stabbyThingy2);
	inventory.weapons.push_back(stabbyThingy2Ptr);

	Armor somePlate("Some Plate", "Some random piece of metal", 5, 0, 0);
	std::shared_ptr<Armor> somePlatePtr = std::make_shared<Armor>(somePlate);
	inventory.armors.push_back(somePlatePtr);

	Armor otherPlate("Other Plate", "Other random piece of metal", 8, -2, 0);
	std::shared_ptr<Armor> otherPlatePtr = std::make_shared<Armor>(otherPlate);
	inventory.armors.push_back(otherPlatePtr);
	
	Accessory placeholder("Placeholder", "Just a placeholder", 1, 2, 3);
	std::shared_ptr<Accessory> placeholderPtr = std::make_shared<Accessory>(placeholder);
	inventory.accessories.push_back(placeholderPtr);

	Accessory placeholder2("Placeholder2", "Just a placeholder2", 0, 3, 3);
	std::shared_ptr<Accessory> placeholder2Ptr = std::make_shared<Accessory>(placeholder2);
	inventory.accessories.push_back(placeholder2Ptr);

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