//combat.hpp

#ifndef COMBAT_HPP
#define COMBAT_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<random>
#include<sstream>
#include <Windows.h>

enum Direction { noDirection, left, right, high, low };
enum GuardType { perfect, standard, none };
//enum Relation {strangers, acquaintances, friends, bestFriends};

class Skill
{
private:
	std::string name;

public:
	int damage;
	bool isHealing;
	bool hasAOE;
	int SPcost;
	Direction attackDirection = noDirection;
	std::string description;

	std::string getName() { return name; };

	Skill(std::string inputName, int inputDamage, bool inputIsHealing, bool inputHasAOE, int inputSPcost, std::string inputDescription) :
		name(inputName), damage(inputDamage), isHealing(inputIsHealing), hasAOE(inputHasAOE), SPcost(inputSPcost), description(inputDescription) {};

	Skill(std::string inputName, int inputDamage, bool inputIsHealing, bool inputHasAOE, int inputSPcost, Direction inputAttackDirection, std::string inputDescription) :
		name(inputName), damage(inputDamage), isHealing(inputIsHealing), hasAOE(inputHasAOE), SPcost(inputSPcost), attackDirection(inputAttackDirection),
		description(inputDescription) {};
};

class Equipment
{
private:
	std::string name;

public:
	std::string description;
	std::string getName() { return name; };
	std::vector<std::string> aliases;
	int HP;
	int SP;
	int str;
	int keyNum = 0;
	int equippedNum = -1;
	bool beenDiscovered = true;

	Equipment() : name("Nothing"), aliases(), description("Just nothing"), HP(0), SP(0), str(0) {};

	Equipment(std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, int inputHP, int inputSP, int inputStr) :
		name(inputName), aliases(inputAliases), description(inputDescription), HP(inputHP), SP(inputSP), str(inputStr) {};

	Equipment(std::string inputName, std::vector<std::string> inputAliases, std::string inputDescription, int inputHP, int inputSP, int inputStr,
		int inputKeyNum, bool inputBeenDiscovered) : name(inputName), aliases(inputAliases), description(inputDescription), HP(inputHP),
		SP(inputSP), str(inputStr), keyNum(inputKeyNum), beenDiscovered(inputBeenDiscovered) {};
};

class Weapon : public Equipment
{
	using Equipment::Equipment;
};

class Armor : public Equipment
{
	using Equipment::Equipment;
};

class Accessory : public Equipment
{
	using Equipment::Equipment;
};

class Player
{
private:
	std::string name;
	int playerNum;

public:
	//Stats
	int maxHP;
	int currentHP;
	int maxSP;
	int currentSP;
	int str = 1;
	int exp = 0;
	int lv = 1;
	int lvEXP = 20;
	int friendship = 0;
	std::string relationship = "Stranger";
	int ratlationship = 0;

	Direction guardDirection = noDirection;

	//Equipment
	Weapon noWeapon;
	std::shared_ptr<Weapon> noWeaponPtr = std::make_shared<Weapon>(noWeapon);
	std::shared_ptr<Weapon> weaponEquipped = noWeaponPtr;
	Armor noArmor;
	std::shared_ptr<Armor> noArmorPtr = std::make_shared<Armor>(noArmor);
	std::shared_ptr<Armor> armorEquipped = noArmorPtr;
	Accessory nothing;
	std::shared_ptr<Accessory> nothingPtr = std::make_shared<Accessory>(nothing);
	std::shared_ptr<Accessory> accEquipped = nothingPtr;

	//Member Vectors
	std::vector<std::string> exploreOptions{"help", "check", "enter", "inv"};
	std::vector<std::string> actions{"Attack", "Skills", "Items", "Defend"};
	std::vector<Skill> skills;

	//Member Functions
	std::string getName() { return name; };
	int getPlayerNum() { return playerNum; };
	void equipWeapon(std::shared_ptr<Weapon> weaponToEquip);
	void unequipWeapon();
	void equipArmor(std::shared_ptr<Armor> armorToEquip);
	void unequipArmor();
	void equipAccessory(std::shared_ptr<Accessory> accToEquip);
	void unequipAccessory();
	void restoreHP(int& healedHP);
	void restoreSP(int& healedSP);
	void reduceHP(int& lostHP);
	void reduceSP(int& lostSP);

	//Constructors
	Player(std::string inputName, int inputPlayerNum, int inputMaxHP, int inputMaxSP, std::vector<Skill> inputSkills) :
		name(inputName), playerNum(inputPlayerNum), maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP),
		currentSP(inputMaxSP), skills(inputSkills) {};
};

class Enemy
{
private:
	std::string name;

public:
	int maxHP;
	int currentHP;
	int maxSP;
	int currentSP;
	int expWorth;
	bool offBalance = false;
	std::vector<std::string> stances;
	std::vector<Skill> skills;
	std::vector<short> aggro{0, 0, 0, 0};

	std::string getName() { return name; };
	void alterName(std::string& nameEdit) { name += nameEdit; };
	void reduceHP(int& lostHP);
	void reduceSP(int& lostSP);

	Enemy(std::string inputName, int inputMaxHP, int inputMaxSP, int inputExpWorth, std::vector<std::string> inputStances,
		std::vector<Skill> inputSkills) : name(inputName), maxHP(inputMaxHP), currentHP(inputMaxHP), maxSP(inputMaxSP), 
		currentSP(inputMaxSP), expWorth(inputExpWorth), stances(inputStances), skills(inputSkills) {};

	//For when the enemy starts with current HP not equal to their max HP (or the same thing with SP)
	Enemy(std::string inputName, int inputMaxHP, int inputCurrentHP, int inputMaxSP, int inputCurrentSP, int inputExpWorth,
		std::vector<std::string> inputStances, std::vector<Skill> inputSkills) : name(inputName), maxHP(inputMaxHP), currentHP(inputCurrentHP),
		maxSP(inputMaxSP), currentSP(inputCurrentSP), expWorth(inputExpWorth), stances(inputStances), skills(inputSkills) {};
};

GuardType determineGuardType(Enemy& enemy, Player& player, short& enemyAction);
int calculateDamage(Enemy& enemy, Player& player, short& enemyAction, GuardType& block);
int dealDamage(Enemy& enemy, Player& player, int& damageDealt, GuardType& block);
void countEnemyNames(std::vector<Enemy>& enemies);
void displayEnemiesTargets(std::vector<Player>& players, std::vector<Enemy>& enemies, std::vector<short>& enemiesTargets);
void displayCombatStats(std::vector<Player>& players, std::vector<Enemy>& enemies);
void displayPlayerActions(Player& player);
void displayPlayerSkills(Player& player);
void displayAttackTargets(std::vector<Player>& players, std::vector<Enemy>& enemies);
void displaySupportTargets(std::vector<Player>& players, std::vector<Enemy>& enemies);
int getDecisionEscapable(const int minChoice, const int maxChoice);
void displaySpacing(int& spacing, const int spaceMax);
int findDigits(int number);
void victory(std::vector<Player>& players, std::vector<Enemy>& enemies);
void gameOver();

#endif
