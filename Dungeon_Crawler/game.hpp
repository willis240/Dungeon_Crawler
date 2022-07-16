//game.hpp

#ifndef GAME_HPP
#define GAME_HPP

Player startGame();
int getDecision(const int minChoice, const int maxChoice);
void checkInput(int & roomNum, Player & player);
void showHelp(Player & player);
void explore(Player& player, int& floor, int& room);
void floor0(Player& player, int& roomNum);
void dblEndl();

class Room
{
private:
	int number;
public:
	std::string name;
	int getNumber() { return number; };

	Room(int inputNumber, std::string inputName) : number(inputNumber), name(inputName) {};
};

class Door
{
private:
	std::pair<int, int> rooms;
public:
	std::string name;
	bool lockStatus;
	std::string lockMessage;

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputLockStatus) :
		rooms(inputRooms), name(inputName), lockStatus(inputLockStatus), lockMessage("") {};
};

#endif