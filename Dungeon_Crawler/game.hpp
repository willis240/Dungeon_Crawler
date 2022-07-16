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

class Room
{
private:
	int number;
public:
	std::string name;
	int getNumber() { return number; };
	std::vector<Object> objects{};

	Room(int inputNumber, std::string inputName) : number(inputNumber), name(inputName), objects{} {};
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