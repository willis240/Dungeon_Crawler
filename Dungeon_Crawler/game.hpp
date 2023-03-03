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
	std::string personWithExpertise = "";
	std::string expertiseDescription;

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription) :
		name(inputName), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(0),
		purposeKnown(true) {};

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription, short int inputNum) :
		name(inputName), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(inputNum),
		purposeKnown(true) {};

	Item(std::string inputName, int inputRestoredHP, int inputRestoredSP, std::string inputDescription, short int inputNum,
		bool inputPurposeKnown, std::string inputPersonWithExpertise, std::string inputExpertiseDescription) : name(inputName),
		restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(inputNum),
		purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription) {};
};

enum GearType {notGear, weapon, armor, accessory};

class Key
{
private:
	int keyNum;
public:
	std::string name;
	std::string description;
	int getKeyNum() { return keyNum; };
	bool purposeKnown = true;
	std::string personWithExpertise = "";
	std::string expertiseDescription = "";
	GearType actuallyGear = notGear;
	
	Key(int inputKeyNum, std::string inputName, std::string inputDescription) :
		keyNum(inputKeyNum), name(inputName), description(inputDescription) {};

	Key(int inputKeyNum, std::string inputName, std::string inputDescription, bool inputPurposeKnown, std::string inputPersonWithExpertise,
		std::string inputExpertiseDescription) : keyNum(inputKeyNum), name(inputName), description(inputDescription), purposeKnown(inputPurposeKnown),
		personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription) {};

	Key(int inputKeyNum, std::string inputName, std::string inputDescription, bool inputPurposeKnown, std::string inputPersonWithExpertise,
		std::string inputExpertiseDescription, GearType inputActuallyGear) : keyNum(inputKeyNum), name(inputName), description(inputDescription),
		purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription),
		actuallyGear(inputActuallyGear) {};
};

class Inventory
{
public:
	std::vector<Item> items;
	std::vector<Key> keys;
	std::vector<std::shared_ptr<Weapon>> weapons;
	std::vector<std::shared_ptr<Armor>> armors;
	std::vector<std::shared_ptr<Accessory>> accessories;

	Inventory() {};
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
	std::pair<int, int> floors = std::make_pair(-1, -1);
public:
	std::string name;
	bool isLocked;
	bool isVisible;
	int lockNum;
	std::string lockedMessage;
	std::string unlockedMessage;

	std::pair<int, int> getRooms() { return rooms; };
	std::pair<int, int> getFloors() { return floors; };

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

	Door(std::pair<int, int> inputRooms, std::pair<int, int> inputFloors, std::string inputName, bool inputIsLocked, bool inputIsVisible, int inputLockNum,
		std::string inputLockedMessage, std::string inputUnlockedMessage) : rooms(inputRooms), floors(inputFloors), name(inputName), isLocked(inputIsLocked),
		isVisible(inputIsVisible), lockNum(inputLockNum), lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};
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
	std::vector<std::shared_ptr<Weapon>> weapons{};
	std::vector<std::shared_ptr<Accessory>> accessories{};

	Room(int inputNumber, std::string inputName, std::vector<Object> inputObjects, std::vector<std::shared_ptr<Door>> inputDoors,
		std::vector<Item> inputItems, std::vector<Key> inputKeys) : number(inputNumber), name(inputName), objects(inputObjects),
		doors(inputDoors), items(inputItems), keys(inputKeys) {};

	Room(int inputNumber, std::string inputName, std::vector<Object> inputObjects, std::vector<std::shared_ptr<Door>> inputDoors,
		std::vector<Item> inputItems, std::vector<Key> inputKeys, std::vector<std::shared_ptr<Weapon>> inputWeapons,
		std::vector<std::shared_ptr<Accessory>> inputAccessories) : number(inputNumber), name(inputName), objects(inputObjects),
		doors(inputDoors), items(inputItems), keys(inputKeys), weapons(inputWeapons), accessories(inputAccessories) {};
};

Player startGame();
int getDecision(const int minChoice, const int maxChoice);
void checkInput(int& roomNum, int& floorNum, std::vector<Player>& players, Inventory& inventory, Room& room);
void showHelp(Player& player);
void checkArgument(int& i, const bool& isDoor, Room& room, Inventory& inventory);
void enterDoor(Door& door, int& roomNum, int& floorNum);
void checkInventory(std::vector<Player>& players, Inventory& inventory, Room& room);
void displayInventoryHeader(std::vector<Player>& players);
void displayItems(std::vector<Item>& items);
void displayKeys(std::vector<Key>& keys);
void displayGear(std::vector<std::shared_ptr<Weapon>>& weapons, std::vector<std::shared_ptr<Armor>>& armors, std::vector<std::shared_ptr<Accessory>>& accessories);
void displayWeapons(std::vector<std::shared_ptr<Weapon>>& weapons);
void displayAccessories(std::vector<std::shared_ptr<Accessory>>& accessories);
void showInvHelp(std::vector<Player>& players, Inventory& inventory);
void checkItems(Inventory& inventory, std::string& argument);
void checkKeys(Inventory& inventory, std::string& argument);
void useItems(std::vector<Player>& players, std::vector<Item>& items, std::string& argument);
bool useKeys(std::vector<Player>& players, Inventory& inventory, Room& room, std::string& argument);
void showStatus(std::vector<Player>& players);
void showItems(std::vector<Player>& players, std::vector<Item>& items, std::string& argument);
void showKeys(std::vector<Player>& players, Inventory& inventory, std::string& argument);
void equipGear(std::vector<Player>& players, std::vector<std::shared_ptr<Weapon>>& weapons, std::vector<std::shared_ptr<Armor>>& armors,
	std::vector<std::shared_ptr<Accessory>>& accessories, std::string& argument);
void unequipGear(std::vector<Player>& players, std::vector<std::shared_ptr<Weapon>>& weapons, std::vector<std::shared_ptr<Armor>>& armors,
	std::vector<std::shared_ptr<Accessory>>& accessories, std::string& argument);
void teamUp(int& i, Inventory& inventory, Room& room);
void explore(std::vector<Player>& players, int& floor, int& roomNum, Inventory& inventory);
void floor0(std::vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory);
void floor1(std::vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory, bool& floor1FirstTime, bool& foundAria);
void dblEndl();

//Function Definitions found in combat.cpp
void fight(std::vector<Player>& players, std::vector<Enemy>& enemies, std::vector<Item>& items);
void displayItemsBattle(std::vector<Item>& items);

#endif