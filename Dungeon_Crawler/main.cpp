//main.cpp

#include "player.hpp"
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