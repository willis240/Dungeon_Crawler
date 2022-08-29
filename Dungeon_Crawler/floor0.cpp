//floor0.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

void floor0(Player& player, int& roomNum, std::vector<Item>& items, std::vector<Key>& keys)
{
	//Room 0: The Starting Room
	bool seeOpening = true;
	bool stoleFromRat = false;
	Item nibbledCheese("Nibbled Cheese", 5, 0,
		"Cheese that has already been nibbled by a rat. Hey, at least there's still a good chunk of cheese left. \n"
		"Eating it would probably restore around 10HP, if you had to guess.");
	Door plainDoor(std::make_pair(0, 1), "Plain Door", false,
		"It is a simple wooden door, and it is slightly ajar. It's a good thing it's not locked.");
	Object nightLight("Night Light",
		"The night light is plugged into an outlet in the wall. The lightbulb itself is in the shape of a thumbs-up. \n"
		"Considering the fact that the night light is what allowed you to see in this small dark room in the first place, \n"
		"you decide to give it a thumbs-up in return. \n \n \"Stay cool, little light dude.\"",
		true, false, 0, 0);
	Room startRoom(0, "Starting Room", { nightLight }, { plainDoor }, {}, {});

	//Room 1: The Living Room
	bool gotBrittleKey = false;
	Key brittleKey(1, "Brittle Key",
		"A key which feels like it has been used a million times. It has a crack stretching vertically down the middle. \n"
		"...Hopefully it'll still unlock what it needs to.");
	Object vase("Vase",
		"The vase has a white color, and appears to be ceramic. It seems quite old, and has clearly not been dusted in \n"
		"a long while. While it is rather dirty, you imagine it must've looked rather eye-catching when it was clean. \n"
		"Clearly, it's purpose here was to add some flavor to the room, some style and grace, rather than to do something \n"
		"menial like hide some--Oh, look, there's a key inside.",
		true, false, 0, 1);
	Object sofa("Sofa",
		"The sofa is a dark blue color, and it looks like the cushions are rather soft. However, there also appears to be \n"
		"a lot of dust on them. You wouldn't dare sit on this dusty sofa--what if it made your butt look all dusty? You'd \n"
		"be patting it off for the rest of your days.",
		true, false, 0, 0);
	Door brittleDoor(std::make_pair(1, 2), "Brittle Door", true, 1, 
		"It is undoubtedly an old and well-loved door--as long as \"well-loved\" means that it has been used many, many \n"
		"times over several decades without any maintenance. Nevertheless, the door is locked, and stands between you \n"
		"and the room that lies behind it. It may be close to retirement, but it still proudly stands and performs its duty.",
		"After you unlocked the door and opened it, it never recovered. It seems to be stuck wide open. It must have put \n"
		"everything it had into opening one final time. The Brittle Key you inserted, likewise, does not budge. It would \n"
		"seem that both the door and its key have finally found their eternal rest, together.");
	Door whiteDoor(std::make_pair(1, 3), "White Door", true, 2,
		"This door is painted white, and has a sheen to it that is impossible to miss. It certainly acts as a stark contrast \n"
		"to the Brittle Door. It looks shiny and well-maintained--polished, even--and it looks like it would still last for \n"
		"decades to come. You'd even say the only thing the doors have in common is that they both stand in your way quite well \n"
		"when they are locked. And you can tell just by the sheer confidence on display by the White Door that it is indeed locked.",
		"Whereas the door had looked rather intimidating with its sheer confidence when it was locked, it feels surprisingly \n"
		"welcoming upon inserting the key. It feels like seeing a good friend for the first time in a while and having them \n"
		"invite you into their home so you can pick up where you left off.");
	Room livingRoom(1, "Living Room", {vase, sofa}, {plainDoor, brittleDoor, whiteDoor}, {}, {brittleKey});

	//Room 2: The Kitchen
	bool grabbedNugget = false;
	bool encounteredRat = false;
	bool helpedRat = false;
	Item chickenNugget("Chicken Nugget", 5, 0,
		"One singular chicken nugget. While it may not be much, it is like a drop from heaven and men have certainly \n"
		"killed for less.", 1);
	Object refrigerator("Refrigerator",
		"Upon throwing open the refrigerator door, you find that there is no food left inside. Just crumbs. Great. \n"
		"Oh, wait! There's a single chicken nugget in the very back of the second shelf down. Score!",
		true, false, 1, 0);
	Room kitchen(2, "Kitchen", {refrigerator}, {brittleDoor}, {chickenNugget}, {});

	while (true)
	{
		if (roomNum == 0)
		{
			if (seeOpening)
			{
				system("CLS");

				cout << "You wake up in a room just large enough that you can lie down and not touch" << endl;
				cout << "any walls. There is a door right in front of you, and a rat munching on some cheese" << endl;
				cout << "in the corner. What do you do?" << endl << endl;

				cout << "(1) Leave the rat alone" << endl;
				cout << "(2) Swipe the rat's cheese" << endl << endl;

				int input = getDecision(1, 2);

				if (input == 1)
				{
					system("CLS");
					cout << "You watch as the rat continues nibbling on its cheese for a bit. It then" << endl;
					cout << "notices your presence. It stares for all of five seconds before scurrying" << endl;
					cout << "along through a hole in the wall.";
					dblEndl();
					system("pause");
				}
				else if (input == 2)
				{
					system("CLS");
					cout << "You snag the cheese literally from right under the rat's nose. You may" << endl;
					cout << "not understand the inner workings of a rat's mind, but you recognize" << endl;
					cout << "its sorrowful eyes all the same. After a couple of minutes of staring" << endl;
					cout << "at the cheese longingly, the rat dejectedly exits through a hole in the" << endl;
					cout << "wall.";
					dblEndl();
					system("pause");

					items.push_back(nibbledCheese);
					stoleFromRat = true;
				}

				system("CLS");
				cout << "Well, now that you are the only living thing in the room, you feel a tinge" << endl;
				cout << "of loneliness crawl down your back. You decide it would be best to leave.";
				dblEndl();
				
				cout << "You realize that you don't know how to open a door. This is most unfortunate," << endl;
				cout << "as if you do not soon find out, you will likely die of loneliness, starvation," << endl;
				cout << "ligma, etc.";
				dblEndl();
				
				cout << "Perhaps, if you were to call for \"help\", then you could figure out how to" << endl;
				cout << "go through the door.";
				dblEndl();
				player.exploreOptions.push_back("help");
				player.exploreOptions.push_back("check");
				player.exploreOptions.push_back("enter");
				player.exploreOptions.push_back("inv");
				checkInput(roomNum, player, items, keys, startRoom);
				system("pause");
				seeOpening = false;
			}
			else
			{
				system("CLS");
				cout << "Looking around, you see that the room is small and largely empty. However, there is" << endl;
				cout << "a Night Light in the corner, as well as a Plain Door directly in front of you.";
				dblEndl();
				checkInput(roomNum, player, items, keys, startRoom);
				system("pause");
			}
		}

		if (roomNum == 1)
		{
			system("CLS");
			cout << "You step into a room which is much larger than the room you awoke in. It appears to be a" << endl;
			cout << "living space. There is a Brittle Door in front of you, as well as a Vase sitting on a table" << endl;
			cout << "off in the corner. There is a Sofa against the wall, just to the right of the Plain Door from" << endl;
			cout << "which you first entered this room. On top of that, there is a White Door to your right as well.";
			dblEndl();

			checkInput(roomNum, player, items, keys, livingRoom);
			system("pause");
		}

		if (roomNum == 2)
		{
			system("CLS");
			if (!encounteredRat)
			{
				cout << "Upon entering the room you immediately recognize it as a kitchen. As you feel your stomach" << endl;
				cout << "rumble, your eyes immediately gravitate toward the Refrigerator directly in front of you.";
				dblEndl();

				checkInput(roomNum, player, items, keys, kitchen);
				system("pause");
				for (int i = 0; i < items.size(); i++)
				{
					if (items[i].getName() == "Chicken Nugget")
						grabbedNugget = true;
				}

				if (grabbedNugget)
				{
					system("CLS");
					cout << "Suddenly, you catch a glimpse of something out of the corner of your eye.";
					dblEndl();
					system("pause");
					if (stoleFromRat)
					{
						system("CLS");
						cout << "You instinctively duck behind the open refrigerator door and hear a loud \"clank!\"" << endl;
						cout << "as something metal strikes the door and falls to the floor.";
						dblEndl();
						cout << "You close the fridge door to find that the object that was launched at you was a knife." << endl;
						cout << "As you look up from the knife, you see there is a rat on the countertop. Not just any" << endl;
						cout << "rat, though. You recognize that it is the rat that you stole that cheese from earlier." << endl;
						cout << "And it looks furious. It hops to the floor and picks the knife back up. You notice the" << endl;
						cout << "murderous glint in its eye and prepare yourself!";
						dblEndl();
						system("pause");

						Skill ratPunch("Punch", 2, false, false, 0, "The rat jumps up and punches you in the neck");
						Enemy rat("Rat", 10, 10, 10, { "" }, { ratPunch });
						vector<Player> players = { player };
						vector<Enemy> enemies = { rat };
						fight(players, enemies, items);
						encounteredRat = true;
					}
					else
					{
						system("CLS");
						cout << "You peek over the top of the refrigerator door to find a rat on the counter. Not just any" << endl;
						cout << "rat, though. You recognize this rat as the one that was nibbling on cheese just earlier." << endl;
						cout << "He is staring longingly at the pocket you put the chicken nugget away in. It would seem" << endl;
						cout << "that he is still hungry." << endl << endl;

						cout << "(1) Give the rat the chicken nugget" << endl;
						cout << "(2) Bro, I found this nugget fair and square" << endl << endl;

						int input = getDecision(1, 2);

						if (input == 1) // Give the rat the chicken nugget
						{
							system("CLS");
							helpedRat = true;
							cout << "You hold out the chicken nugget and the rat snatches it up faster than you could blink." << endl;
							cout << "The next thing you know, the rat is back on the counter, nugget in hand. It looks at you" << endl;
							cout << "and nods before heading off through a hole in the wall. It better enjoy that nugget." << endl << endl;
							for (int i = 0; i < items.size(); i++)
							{
								if (items[i].getName() == "Chicken Nugget")
									items.erase(items.begin() + i);
							}
							system("pause");
						}
						else if (input == 2) // Keep the chicken nugget
						{
							system("CLS");
							cout << "You look the rat in the eye. \"I'm starving, man. Go find your own food.\" The rat," << endl;
							cout << "with tears beginning to form in its eyes, seems to nod in understanding. It would likely" << endl;
							cout << "do the same were it in your position. It leaves through the hole in the wall from whence" << endl;
							cout << "it came." << endl << endl;
							system("pause");
						}
						encounteredRat = true;
					}
				}
			}
			else
			{
				// NORMAL KITCHEN DESCRIPTION AND CODE
			}
		}
	}

}