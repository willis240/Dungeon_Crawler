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
	vector<Item> items{};
	vector<Key> keys{};

	int floorNum = 0;
	int roomNum = 0;

	//CODE FOR TESTING COMBAT, REMOVE LATER
	Skill ratPunch("Punch", 2, false, false, 0, "The rat jumps up and punches you in the neck");
	Skill doubleSlash("Double Slash", 3, false, false, 2, "Player 2 makes two quick diagonal slashes using each of their swords");
	Enemy rat("Rat", 10, 10, 10, { "" }, { ratPunch });
	Player player2("Player 2", 10, 10, { doubleSlash });
	vector<Player> players = { player, player2 };
	vector<Enemy> enemies = { rat, rat };
	Item grapefruit("Grapefruit", 5, 5, "A juicy fruit, for sure");
	items.push_back(grapefruit);
	fight(players, enemies, items);

	explore(player, floorNum, roomNum, items, keys);

}