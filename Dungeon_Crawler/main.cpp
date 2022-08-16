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
	Skill ratPunch("Punch", 2, false, false, "The rat jumps up and punches you in the neck");
	Skill doubleSlash("Double Slash", 3, false, false, "Player 2 makes two quick diagonal slashes using each of their swords");
	Enemy rat("Rat", 10, 10, { "" }, { ratPunch });
	Player player2("Player 2", 10, 10, { doubleSlash });
	vector<Player> players = { player, player2 };
	vector<Enemy> enemies = { rat, rat };
	fight(players, enemies);

	explore(player, floorNum, roomNum, items, keys);

}