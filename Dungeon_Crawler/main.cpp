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
	player.relationship = "Self";
	vector<Player> players = { player };
	Inventory inventory;

	int floorNum = 0;
	int roomNum = 0;

	//A SECOND PLAYER CHARACTER, FOR TESTING
	/*
	Player Selena("Selena", 1, 7, 13, {});
	players.push_back(Selena);
	Skill oblivionSlash("Oblivion Slash", 3, false, true, 5, noDirection, "Selena cuts through all of her foes in the blink of an eye!");
	players[1].skills.push_back(oblivionSlash);

	Key pomegranate(3, "Pomegranate", "An red fruit which is at first tart, but then sweet. An old favorite of Selena's.");
	inventory.keys.push_back(pomegranate);
	
	Weapon fireIron("Fire Iron",
		"An iron rod which is sharpened at the end, which in hindsight makes it a pretty decent weapon. \n"
		"Also used to stoke fires.",
		0, 0, 2, 5, false);
	auto fireIronPtr = std::make_shared<Weapon>(fireIron);
	players[1].equipWeapon(fireIronPtr);
	*/

	/*
	Weapon brassKnucks("Brass Knuckles", "Put 'em on ya hands", 2, 1, 4);
	auto brassKnucksPtr = std::make_shared<Weapon>(brassKnucks);
	players[0].equipWeapon(brassKnucksPtr);

	Accessory pocketWatch("Pocket Watch", "Tick, tock, tick, tock", 4, 0, 1);
	auto pocketWatchPtr = std::make_shared<Accessory>(pocketWatch);
	players[1].equipAccessory(pocketWatchPtr);

	//AN EXAMPLE FIGHT, ALSO FOR TESTING
	/*
	Skill quickSlash("Quick Slash", 4, false, true, 0, left, "The man on the left slashes from the left!");
	Enemy manOnTheLeft("The Left Man", 12, 12, 10, { "" }, { quickSlash });
	vector<Enemy> enemies = { manOnTheLeft, manOnTheLeft };
	fight(players, enemies, inventory.items);
	*/
	explore(players, floorNum, roomNum, inventory);

}