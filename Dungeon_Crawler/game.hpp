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
	bool purposeKnown;
	short int personWithExpertise;
	std::string expertiseDescription;

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription) :
		name(inputName), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(0),
		purposeKnown(true), personWithExpertise(0) {};

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription, short int inputNum) :
		name(inputName), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(inputNum),
		purposeKnown(true), personWithExpertise(0) {};

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription, short int inputNum,
		bool inputPurposeKnown, short int inputPersonWithExpertise, std::string inputExpertiseDescription) : name(inputName),
		restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(inputNum),
		purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription) {};
};

class Key
{
private:
	int keyNum;
public:
	std::string name;
	std::string description;
	int getKeyNum() { return keyNum; };
	bool purposeKnown = true;
	short int personWithExpertise = 0;
	std::string expertiseDescription = "";
	bool actuallyAccessory = false;
	
	Key(int inputKeyNum, std::string inputName, std::string inputDescription) :
		keyNum(inputKeyNum), name(inputName), description(inputDescription) {};

	Key(int inputKeyNum, std::string inputName, std::string inputDescription, bool inputPurposeKnown, short int inputPersonWithExpertise,
		std::string inputExpertiseDescription) : keyNum(inputKeyNum), name(inputName), description(inputDescription), purposeKnown(inputPurposeKnown),
		personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription) {};

	Key(int inputKeyNum, std::string inputName, std::string inputDescription, bool inputPurposeKnown, short int inputPersonWithExpertise,
		std::string inputExpertiseDescription, bool inputActuallyAccessory) : keyNum(inputKeyNum), name(inputName), description(inputDescription),
		purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription),
		actuallyAccessory(inputActuallyAccessory) {};
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
	short int revealsDoor = 0;
	std::string secretText;

	std::string getName() { return name; };

	Object(std::string inputName, std::string inputDescription, bool inputIsVisible, bool inputHasSecret, short int inputItemNum, short int inputKeyNum) :
		name(inputName), description(inputDescription), isVisible(inputIsVisible), hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum) {};

	Object(std::string inputName, std::string inputDescription, bool inputIsVisible, bool inputHasSecret, short int inputItemNum, short int inputKeyNum,
		short int inputAnswerNum, std::string inputSecretText) : name(inputName), description(inputDescription), isVisible(inputIsVisible),
		hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum), answerNum(inputAnswerNum), secretText(inputSecretText) {};

	Object(std::string inputName, std::string inputDescription, bool inputIsVisible, bool inputHasSecret, short int inputItemNum, short int inputKeyNum,
		short int inputAnswerNum, short int inputRevealsDoor, std::string inputSecretText) : name(inputName), description(inputDescription), isVisible(inputIsVisible),
		hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum), answerNum(inputAnswerNum), revealsDoor(inputRevealsDoor), secretText(inputSecretText) {};
};

class Door
{
private:
	std::pair<int, int> rooms;
public:
	std::string name;
	bool isLocked;
	bool isVisible;
	int lockNum;
	std::string lockedMessage;
	std::string unlockedMessage;

	std::pair<int, int> getRooms() { return rooms; };

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), isVisible(true), lockNum(0), lockedMessage(""), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, int inputLockNum, std::string inputLockedMessage, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), isVisible(true), lockNum(inputLockNum), lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, bool inputIsVisible, int inputLockNum, std::string inputUnlockedMessage) :
		rooms(inputRooms), name(inputName), isLocked(inputIsLocked), isVisible(inputIsVisible), lockNum(inputLockNum), 
		unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, bool inputIsLocked, bool inputIsVisible, int inputLockNum, std::string inputLockedMessage,
		std::string inputUnlockedMessage) : rooms(inputRooms), name(inputName), isLocked(inputIsLocked), isVisible(inputIsVisible), lockNum(inputLockNum),
		lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};
};

class Room
{
private:
	int number;
public:
	std::string name;
	int getNumber() { return number; };
	std::vector<Object> objects{};
	std::vector<std::shared_ptr<Door>> doors{};
	std::vector<Item> items{};
	std::vector<Key> keys{};
	std::vector<Accessory> accessories{};

	Room(int inputNumber, std::string inputName, std::vector<Object> inputObjects, std::vector<std::shared_ptr<Door>> inputDoors,
		std::vector<Item> inputItems, std::vector<Key> inputKeys) : number(inputNumber), name(inputName), objects(inputObjects),
		doors(inputDoors), items(inputItems), keys(inputKeys) {};

	Room(int inputNumber, std::string inputName, std::vector<Object> inputObjects, std::vector<std::shared_ptr<Door>> inputDoors,
		std::vector<Item> inputItems, std::vector<Key> inputKeys, std::vector<Accessory> inputAccessories) : number(inputNumber),
		name(inputName), objects(inputObjects), doors(inputDoors), items(inputItems), keys(inputKeys), accessories(inputAccessories) {};
};

Player startGame();
int getDecision(const int minChoice, const int maxChoice);
void checkInput(int & roomNum, std::vector<Player>& players, std::vector<Item>& items, std::vector<Key>& keys,
	std::vector<Accessory>& accessories, Room& room);
void showHelp(Player& player);
void checkArgument(int& i, const bool& isDoor, Room& room, std::vector<Item>& items, std::vector<Key>& keys,
	std::vector<Accessory>& accessories);
void enterDoor(Door& door, int & roomNum);
void checkInventory(std::vector<Player>& players, std::vector<Item>& items, std::vector<Key>& keys,
	std::vector<Accessory>& accessories, Room& room);
void displayItems(std::vector<Item>& items);
void displayKeys(std::vector<Key>& keys);
void displayAccessories(std::vector<Accessory>& accessories);
void showInvHelp(std::vector<Player>& players);
void checkItems(std::vector<Item>& items, std::string& argument);
void checkKeys(std::vector<Key>& keys, std::string& argument);
void useItems(std::vector<Player>& players, std::vector<Item>& items, std::string& argument);
void useKeys(std::vector<Player>& players, std::vector<Item>& items, std::vector<Key>& keys, Room& room, std::string& argument);
void showItems(std::vector<Player>& players, std::vector<Item>& items, std::string& argument);
void showKeys(std::vector<Player>& players, std::vector<Key>& keys, std::vector<Accessory>& accessories, std::string& argument);
void teamUp(int& i, std::vector<Item>& items, std::vector<Key>& keys, Room& room);
void explore(std::vector<Player>& players, int& floor, int& roomNum, std::vector<Item>& items, std::vector<Key>& keys,
	std::vector<Accessory>& accessories);
void floor0(std::vector<Player>& players, int& roomNum, std::vector<Item>& items, std::vector<Key>& keys,
	std::vector<Accessory>& accessories);
void dblEndl();

//Function Definitions found in combat.cpp
void fight(std::vector<Player>& players, std::vector<Enemy>& enemies, std::vector<Item>& items);
void displayItemsBattle(std::vector<Item>& items);

#endif