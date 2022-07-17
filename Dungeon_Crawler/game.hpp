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

class Object
{
private: 
	std::string name;
public:
	std::string description;
	bool isVisible;
	bool hasSecret;

	Object(std::string inputName, std::string inputDescription, bool inputIsVisible, bool inputHasSecret) :
		name(inputName), description(inputDescription), isVisible(inputIsVisible), hasSecret(inputHasSecret) {};
};

class Door
{
private:
	std::pair<int, int> rooms;
public:
	std::string name;
	bool isLocked;
	std::string lockedMessage;
	std::string unlockedMessage;

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), lockedMessage(""), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, std::string inputLockedMessage, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};
};

class Room
{
private:
	int number;
public:
	std::string name;
	int getNumber() { return number; };
	std::vector<Object> objects{};
	std::vector<Door> doors{};

	Room(int inputNumber, std::string inputName, std::vector<Object> inputObjects, std::vector<Door> inputDoors) :
		number(inputNumber), name(inputName), objects(inputObjects), doors(inputDoors) {};
};

#endif