//game.hpp

#ifndef GAME_HPP
#define GAME_HPP

Player startGame();
int getInput(const int minChoice, const int maxChoice);
void explore(Player& player, int& floor, int& room);
void floor0(Player& player, int& roomNum);

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

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputLockStatus) :
		rooms(inputRooms), name(inputName), lockStatus(inputLockStatus) {};
};

#endif