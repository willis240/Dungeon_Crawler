//floor1.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

void floor1(vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory, bool& floor1FirstTime)
{
	//Room 0: Hall of Opportunity
	Room hallway(0, "Hallway", {}, {}, {}, {});
	while (true)
	{
		if (floorNum != 1)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			if (floor1FirstTime)
			{
				cout << "Upon reaching the top of the stairs, you find yourself in a hallway. There are three doors" << endl;
				cout << "spaced apart evenly throughout the hallway: a Left Door, a Middle Door, and a Right Door." << endl;
				cout << "Additionally, you hear footsteps above you.";
				dblEndl();
				system("pause");
				
				system("CLS");
				cout << "Suddenly, two holes burst from the ceiling and two men drop down at the same time.";
				dblEndl();
				cout << "\"Well, look at what we have here, Jarvis\", the man on the left said, as he twirled the" << endl;
				cout << "knife in his hand.";
				dblEndl();
				cout << "\"Yes, it would appear we have found some persons who do not belong\", the man on the right" << endl;
				cout << "responded as he adjusted his broken monocle.";
				dblEndl();
				system("pause");
				system("CLS");
				cout << "The man on the left wore a hoodie and a black cap, and had a particular glint in his eye which" << endl;
				cout << "was reflected by the knife in his hand. Meanwhile, the man on the right's distinctive features" << endl;
				cout << "of clothing were the top hat atop his head and the broken monocle \"covering\" his left eye." << endl;
				cout << "You and Selena share a glance for a moment before looking back toward the men.";
				dblEndl();
				cout << "\"It is my understanding that you both have rooms in which you belong. Rooms which, as it happens," << endl;
				cout << "are not the room we are in currently.\"";
				dblEndl();
				cout << "\"Yeah, you should be a good boy and girl and go back to where you belong real quick-like.";
				dblEndl();
				cout << "(1) No, I don't think we will" << endl;
				cout << "(2) Yes, that would be appropriate" << endl;

				int input = getDecision(1, 2);
				cout << endl;

				if (input == 1)
				{
					cout << "Selena leans against the wall and adds, \"I think we belong somewhere with a bit more pizzazz" << endl;
					cout << "than some tiny old cell. At least, like, a mother-in-law apartment.\"";
					dblEndl();
					cout << "\"While I do agree that your lodgings are less than proper hospitality... the decision is not mine" << endl;
					cout << "to make. All I can do is ask that you acquiesce.\"";
					dblEndl();
					cout << "You point at the gentlemanly man on the right. \"We've made it clear: we are not going back.\"";
					dblEndl();
					cout << "The man on the left's eyes focus on you. \"Well, you'll find that my buddy here is more persuasive" << endl;
					cout << "than I am.\" As he says this, he points his knife straight toward you.";
					dblEndl();
					cout << "The man on the right adjusts the cuffs of his sleeves as he sighs. \"Alright, then. Let's get this done" << endl;
					cout << "before the tea cools off.";
					dblEndl();
					cout << "You and Selena ready yourselves!";
					dblEndl();
				}
				else
				{
					cout << "Selena follows up: \"Yeah, we're not gonna just- wait, what? You're kidding, right? You're not seriously" << endl;
					cout << "just gonna go back?\"";
				}
			}
			checkInput(roomNum, floorNum, players, inventory, hallway);
		}
	}
}