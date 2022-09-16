//game.hpp

#ifndef GAME_HPP
#define GAME_HPP

class Item
{
private:
	std::string name;
public:
	int restoredHP;
	int restoredSP;
	std::string description;
	short int num;
	std::string getName() { return name; };

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription) :
		name(inputName), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(0) {};

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription, short int inputNum) :
		name(inputName), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(inputNum) {};
};

class Key
{
private:
	int keyNum;
public:
	std::string name;
	std::string description;
	int getKeyNum() { return keyNum; };
	
	Key(int inputKeyNum, std::string inputName, std::string inputDescription) :
		keyNum(inputKeyNum), name(inputName), description(inputDescription) {};
};

class Object
{
private:
	std::string name;
public:
	std::string description;
	bool isVisible;
	bool hasSecret;
	short int itemNum;
	short int keyNum;
	short int answerNum = 0;
	std::string secretText;

	std::string getName() { return name; };

	Object(std::string inputName, std::string inputDescription, bool inputIsVisible, bool inputHasSecret, short int inputItemNum, short int inputKeyNum) :
		name(inputName), description(inputDescription), isVisible(inputIsVisible), hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum) {};

	Object(std::string inputName, std::string inputDescription, bool inputIsVisible, bool inputHasSecret, short int inputItemNum, short int inputKeyNum,
		short int inputAnswerNum, std::string inputSecretText) : name(inputName), description(inputDescription), isVisible(inputIsVisible),
		hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum), answerNum(inputAnswerNum), secretText(inputSecretText) {};
};

class Door
{
private:
	std::pair<int, int> rooms;
public:
	std::string name;
	bool isLocked;
	int lockNum;
	std::string lockedMessage;
	std::string unlockedMessage;

	std::pair<int, int> getRooms() { return rooms; };

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), lockNum(0), lockedMessage(""), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, int inputLockNum, std::string inputLockedMessage, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), lockNum(inputLockNum), lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};
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
	std::vector<Item> items{};
	std::vector<Key> keys{};

	Room(int inputNumber, std::string inputName, std::vector<Object> inputObjects, std::vector<Door> inputDoors, std::vector<Item> inputItems, std::vector<Key> inputKeys) :
		number(inputNumber), name(inputName), objects(inputObjects), doors(inputDoors), items(inputItems), keys(inputKeys) {};
};

Player startGame();
int getDecision(const int minChoice, const int maxChoice);
void checkInput(int & roomNum, Player& player, std::vector<Item>& items, std::vector<Key>& keys, Room& room);
void showHelp(Player& player);
void checkArgument(int & i, const bool & isDoor, Room & room, std::vector<Item> & items, std::vector<Key> & keys);
void enterDoor(Door& door, int & roomNum);
void checkInventory(Player& player, std::vector<Item>& items, std::vector<Key>& keys, Room& room);
void displayItems(std::vector<Item>& items);
void displayKeys(std::vector<Key>& keys);
void showInvHelp();
void checkItems(std::vector<Item>& items, std::string& argument);
void checkKeys(std::vector<Key>& keys, std::string& argument);
void useItems(Player& player, std::vector<Item>& items, std::string& argument);
void useKeys(Player& player, std::vector<Item>& items, std::vector<Key>& keys, Room& room, std::string& argument);
void explore(Player& player, int& floor, int& roomNum, std::vector<Item>& items, std::vector<Key>& keys);
void floor0(Player& player, int& roomNum, std::vector<Item>& items, std::vector<Key>& keys);
void dblEndl();

//Function Definitions found in combat.cpp
void fight(std::vector<Player>& players, std::vector<Enemy>& enemies, std::vector<Item>& items);
void displayItemsBattle(std::vector<Item>& items);

#endif