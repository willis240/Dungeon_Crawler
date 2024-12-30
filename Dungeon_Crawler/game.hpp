//game.hpp

#ifndef GAME_HPP
#define GAME_HPP

class Item
{
private:
	std::string name;
public:
	std::vector<std::string> aliases;
	int restoredHP;
	int restoredSP;
	std::string description;
	short int num;
	std::string getName() { return name; };
	bool purposeKnown;
	std::string personWithExpertise = "";
	std::string expertiseDescription;

	Item(std::string inputName, std::vector<std::string> inputAliases, int inputRestoredHP, int inputRestoredSP,
		std::string inputDescription) : name(inputName), aliases(inputAliases), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP),
		description(inputDescription), num(0), purposeKnown(true) {};

	Item(std::string inputName, std::vector<std::string> inputAliases, int inputRestoredHP, int inputRestoredSP,
		std::string inputDescription, short int inputNum) : name(inputName), aliases(inputAliases), restoredHP(inputRestoredHP),
		restoredSP(inputRestoredSP), description(inputDescription), num(inputNum), purposeKnown(true) {};

	Item(std::string inputName, std::vector<std::string> inputAliases, int inputRestoredHP, int inputRestoredSP, std::string inputDescription,
		short int inputNum, bool inputPurposeKnown, std::string inputPersonWithExpertise, std::string inputExpertiseDescription) : name(inputName),
		aliases(inputAliases), restoredHP(inputRestoredHP), restoredSP(inputRestoredSP), description(inputDescription), num(inputNum),
		purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise), expertiseDescription(inputExpertiseDescription) {};
};

enum GearType {notGear, weapon, armor, accessory};

class Key
{
private:
	int keyNum;
public:
	std::string name;
	std::vector<std::string> aliases;
	std::string description;
	int getKeyNum() { return keyNum; };
	bool reclaimable = false;
	bool purposeKnown = true;
	std::string personWithExpertise = "";
	std::string expertiseDescription = "";
	GearType actuallyGear = notGear;
	
	Key(int inputKeyNum, std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription) :
		keyNum(inputKeyNum), name(inputName), aliases(inputAliases), description(inputDescription) {};

	Key(int inputKeyNum, std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputReclaimable) :
		keyNum(inputKeyNum), name(inputName), aliases(inputAliases), description(inputDescription), reclaimable(inputReclaimable) {};

	Key(int inputKeyNum, std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputPurposeKnown,
		std::string inputPersonWithExpertise, std::string inputExpertiseDescription) : keyNum(inputKeyNum), name(inputName), aliases(inputAliases),
		description(inputDescription), purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise),
		expertiseDescription(inputExpertiseDescription) {};

	Key(int inputKeyNum, std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputPurposeKnown,
		std::string inputPersonWithExpertise, std::string inputExpertiseDescription, GearType inputActuallyGear) : keyNum(inputKeyNum), name(inputName),
		aliases(inputAliases), description(inputDescription), purposeKnown(inputPurposeKnown), personWithExpertise(inputPersonWithExpertise),
		expertiseDescription(inputExpertiseDescription), actuallyGear(inputActuallyGear) {};
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
	std::vector<std::string> aliases;
	std::string description;
	bool isVisible = true;
	bool hasSecret = false;
	bool isLocked = false;
	short int itemNum;
	short int keyNum;
	short int answerNum = 0;
	short int revealsDoor = 0;
	short int checkSecret = 0;
	std::string secretText;
	std::string lockedText;

	std::string getName() { return name; };

	//Basic Object
	Object(std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputIsVisible, bool inputHasSecret, 
		short int inputItemNum, short int inputKeyNum) : name(inputName), aliases(inputAliases), description(inputDescription), isVisible(inputIsVisible), 
		hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum) {};

	//Object with a Secret
	Object(std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputIsVisible, bool inputHasSecret,
		short int inputItemNum, short int inputKeyNum, short int inputAnswerNum, std::string inputSecretText) : name(inputName), aliases(inputAliases),
		description(inputDescription), isVisible(inputIsVisible), hasSecret(inputHasSecret), itemNum(inputItemNum), keyNum(inputKeyNum),
		answerNum(inputAnswerNum), secretText(inputSecretText) {};

	//Lockable Object
	Object(std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputIsLocked,
		short int inputItemNum, short int inputKeyNum, short int inputAnswerNum, std::string inputLockedText) : name(inputName), aliases(inputAliases),
		description(inputDescription), isLocked(inputIsLocked), itemNum(inputItemNum), keyNum(inputKeyNum),
		answerNum(inputAnswerNum), lockedText(inputLockedText) {};

	Object(std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, bool inputIsVisible, bool inputHasSecret,
		short int inputItemNum, short int inputKeyNum, short int inputAnswerNum, short int inputRevealsDoor, short int inputCheckSecret,
		std::string inputSecretText) : name(inputName), aliases(inputAliases), description(inputDescription), isVisible(inputIsVisible), hasSecret(inputHasSecret),
		itemNum(inputItemNum), keyNum(inputKeyNum), answerNum(inputAnswerNum), revealsDoor(inputRevealsDoor), checkSecret(inputCheckSecret), secretText(inputSecretText) {};
};

class Door
{
private:
	std::pair<int, int> rooms;
	std::pair<int, int> floors = std::make_pair(-1, -1);
public:
	std::string name;
	std::vector<std::string> aliases;
	bool isLocked;
	bool isVisible;
	int lockNum;
	std::string lockedMessage;
	std::string unlockedMessage;

	std::pair<int, int> getRooms() { return rooms; };
	std::pair<int, int> getFloors() { return floors; };

	Door(std::pair<int, int> inputRooms, std::string inputName, std::vector<std::string> inputAliases, bool inputIsLocked,
		std::string inputUnlockedMessage) : rooms(inputRooms), name(inputName), aliases(inputAliases), isLocked(inputIsLocked),
		isVisible(true), lockNum(0), lockedMessage(""), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, std::vector<std::string> inputAliases, bool inputIsLocked, int inputLockNum,
		std::string inputLockedMessage, std::string inputUnlockedMessage) : rooms(inputRooms), name(inputName), aliases(inputAliases),
		isLocked(inputIsLocked), isVisible(true), lockNum(inputLockNum), lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, std::vector<std::string> inputAliases, bool inputIsLocked, bool inputIsVisible,
		int inputLockNum, std::string inputUnlockedMessage) : rooms(inputRooms), name(inputName), aliases(inputAliases), isLocked(inputIsLocked),
		isVisible(inputIsVisible), lockNum(inputLockNum), unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::string inputName, std::vector<std::string> inputAliases, bool inputIsLocked, bool inputIsVisible,
		int inputLockNum, std::string inputLockedMessage, std::string inputUnlockedMessage) : rooms(inputRooms), name(inputName), aliases(inputAliases),
		isLocked(inputIsLocked), isVisible(inputIsVisible), lockNum(inputLockNum), lockedMessage(inputLockedMessage),
		unlockedMessage(inputUnlockedMessage) {};

	Door(std::pair<int, int> inputRooms, std::pair<int, int> inputFloors, std::string inputName, std::vector<std::string> inputAliases, 
		bool inputIsLocked, bool inputIsVisible, int inputLockNum, std::string inputLockedMessage, std::string inputUnlockedMessage) : 
		rooms(inputRooms), floors(inputFloors), name(inputName), aliases(inputAliases), isLocked(inputIsLocked), isVisible(inputIsVisible),
		lockNum(inputLockNum), lockedMessage(inputLockedMessage), unlockedMessage(inputUnlockedMessage) {};
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
std::string checkInput(int& roomNum, int& floorNum, std::vector<Player>& players, Inventory& inventory, Room& room);
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
void checkGear(Inventory& inventory, std::string& argument);
void useItems(std::vector<Player>& players, std::vector<Item>& items, std::string& argument);
bool useItemOnPlayer(std::vector<Player>& players, std::vector<Item>& items, int& i);
bool useKeys(std::vector<Player>& players, Inventory& inventory, Room& room, std::string& argument);
bool useKeyOnThing(std::vector<Player>& players, Inventory& inventory, Room& room, int& i);
bool unlockDoor(Inventory& inventory, Room& room, int& i, int& ii);
bool unlockObject(Inventory& inventory, Room& room, int& i, int& ii);

void showStatus(std::vector<Player>& players);
void showItems(std::vector<Player>& players, std::vector<Item>& items, std::string& argument);
void showItemToPlayer(std::vector<Player>& players, std::vector<Item>& items, int& i);
void showKeys(std::vector<Player>& players, Inventory& inventory, std::string& argument);
void showKeyToPlayer(std::vector<Player>& players, Inventory& inventory, int& i);

void equipGear(std::vector<Player>& players, std::vector<std::shared_ptr<Weapon>>& weapons, std::vector<std::shared_ptr<Armor>>& armors,
	std::vector<std::shared_ptr<Accessory>>& accessories, std::string& argument);
void equipWeapon(std::vector<Player>& players, std::vector<std::shared_ptr<Weapon>>& weapons, int& i);
void equipArmor(std::vector<Player>& players, std::vector<std::shared_ptr<Armor>>& armors, int& i);
void equipAccessory(std::vector<Player>& players, std::vector<std::shared_ptr<Accessory>>& accessories, int& i);

void unequipGear(std::vector<Player>& players, std::vector<std::shared_ptr<Weapon>>& weapons, std::vector<std::shared_ptr<Armor>>& armors,
	std::vector<std::shared_ptr<Accessory>>& accessories, std::string& argument);
void unequipWeapon(std::vector<Player>& players, std::vector<std::shared_ptr<Weapon>>& weapons, int& i);
void unequipArmor(std::vector<Player>& players, std::vector<std::shared_ptr<Armor>>& armors, int& i);
void unequipAccessory(std::vector<Player>& players, std::vector<std::shared_ptr<Accessory>>& accessories, int& i);

void teamUp(int& i, Inventory& inventory, Room& room);

void explore(std::vector<Player>& players, int& floor, int& roomNum, Inventory& inventory);
void floor0(std::vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory, bool& seeOpening, bool& encounteredRat);
void floor1(std::vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory, bool& floor1FirstTime, bool& foundAria,
	bool& greenhouseFirstTime, bool& openedSafe, bool& entrywayFirstTime);
void floor2(std::vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory);
void dblEndl();

//Function Definitions found in combat.cpp
void fight(std::vector<Player>& players, std::vector<Enemy>& enemies, std::vector<Item>& items);
void displayItemsBattle(std::vector<Item>& items);

#endif