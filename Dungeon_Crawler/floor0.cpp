//floor0.cpp

#include "combat.hpp"
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

void floor0(vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory, bool& seeOpening, bool& encounteredRat)
{
	//Room 0: The Starting Room
	Item nibbledCheese("Nibbled Cheese", 5, 0,
		"Cheese that has already been nibbled by a rat. Hey, at least there's still a good chunk of cheese left. \n"
		"Eating it would probably restore around 10HP, if you had to guess.");
	Door plainDoor(std::make_pair(0, 1), "Plain Door", false,
		"It is a simple wooden door, and it is slightly ajar. It's a good thing it's not locked.");
	auto plainDoorPtr = make_shared<Door>(plainDoor);
	Object nightLight("Night Light", {"night light", "light"},
		"The night light is plugged into an outlet in the wall. The lightbulb itself is in the shape of a thumbs-up. \n"
		"Considering the fact that the night light is what allowed you to see in this small dark room in the first place, \n"
		"you decide to give it a thumbs-up in return. \n \n \"Stay cool, little light dude.\"",
		true, false, 0, 0);
	Room startRoom(0, "Starting Room", { nightLight }, { plainDoorPtr }, {}, {});

	//Room 1: The Living Room
	Key brittleKey(1, "Brittle Key",
		"A key which feels like it has been used a million times. It has a crack stretching vertically down the middle. \n"
		"...Hopefully it'll still unlock what it needs to.");
	Object vase("Vase", {"vase"},
		"The vase has a white color, and appears to be ceramic. It seems quite old, and has clearly not been dusted in \n"
		"a long while. While it is rather dirty, you imagine it must've looked rather eye-catching when it was clean. \n"
		"Clearly, it's purpose here was to add some flavor to the room, some style and grace, rather than to do something \n"
		"menial like hide some--Oh, look, there's a key inside.",
		true, false, 0, 1);
	Object sofa("Sofa", {"sofa", "couch"},
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
	auto brittleDoorPtr = make_shared<Door>(brittleDoor);
	Door whiteDoor(std::make_pair(1, 3), "White Door", true, 2,
		"This door is painted white, and has a sheen to it that is impossible to miss. It certainly acts as a stark contrast \n"
		"to the Brittle Door. It looks shiny and well-maintained--polished, even--and it looks like it would still last for \n"
		"decades to come. You'd even say the only thing the doors have in common is that they both stand in your way quite well \n"
		"when they are locked. And you can tell just by the sheer confidence on display by the White Door that it is indeed locked.",
		"Whereas the door had looked rather intimidating with its sheer confidence when it was locked, it feels surprisingly \n"
		"welcoming upon inserting the key. It feels like seeing a good friend for the first time in a while and having them \n"
		"invite you into their home so you can pick up where you left off.");
	auto whiteDoorPtr = make_shared<Door>(whiteDoor);
	Room livingRoom(1, "Living Room", { vase, sofa }, { plainDoorPtr, brittleDoorPtr, whiteDoorPtr },
		{}, { brittleKey });

	//Room 2: The Kitchen
	bool grabbedNugget = false;
	Item chickenNugget("Chicken Nugget", 5, 0,
		"One singular chicken nugget. While it may not be much, it is like a drop from heaven and men have certainly \n"
		"killed for less.", 1);
	Object refrigerator("Refrigerator", {"refrigerator", "fridge"},
		"Upon throwing open the refrigerator door, you find that there is no food left inside. Just crumbs. Great. \n"
		"Oh, wait! There's a single chicken nugget in the very back of the second shelf down. Score!",
		true, false, 1, 0);
	Key rawApplePie(3, "Raw Apple Pie",
		"All of the ingredients for a good apple pie. Has yet to be cooked, though. Eating it raw would be \n"
		"a waste.");
	Item applePie("Apple Pie", 12, 12,
		"A beautiful baked apple pie... with a hole in the center where the White Key (and your hand) used to be. \n"
		"Hey, no one is perfect.", 2);
	Key whiteKey(2, "White Key",
		"Once you look past all of the pie residue, it appears to be a rather beautiful white key.");
	Key smallRing(4, "Small Ring",
		"It is a small ring made of iron. Perhaps someone else would be better at ascertaining its worth.",
		false, "Selena",
		"You put the ring between your fingertips and hold it out to Selena. \n \n"
		"\"Wow, you sure work fast, don't you? We just met.\" \n \n"
		"You let out a pained expression as she follows up, \"I'm just kidding. In all honesty, though, I bet we \n"
		"could really use this. We could wear something like this to aid us should things get ugly.\" \n \n"
		"Naturally, you respond to this by raising a singular eyebrow. \n \n"
		"She holds out her hands as she defends herself against your psychological attack. \"No, seriously! I noticed \n"
		"my jailer put on this bandana and afterward, he just seemed stronger. I'M NOT CRAZY, THAT'S HOW IT WORKS!!\"",
		accessory);
	Accessory ironRing("Iron Ring",
		"It is a small ring made of iron, and in hindsight, it looks quite equippable. Grants STR +2.",
		0, 0, 1, 4, false);
	auto ironRingPtr = make_shared<Accessory>(ironRing);
	Object pantry("Pantry", {"pantry"},
		"You open the pantry door to take a look inside. You see an assortment of empty boxes of snack foods, ranging \n"
		"from chips to crackers to cereal. Looking inside the boxes, you realize that not even a crumb remains. Whether \n"
		"it was people or the rats, whoever ate these snacks was thorough. \n \n"
		"That being said, you also see a different food item within the Pantry. There is a pie crust, filled with all of \n"
		"the ingredients necessary for a delicious Apple Pie. It just hasn't been cooked yet. You believe that this \n"
		"could be handy, so you take the Raw Apple Pie.",
		true, false, 0, 3);
	Object oven("Oven", {"oven"},
		"The oven has a black door, and despite the transparent glass on the door, the inside is impossible to view \n"
		"due to how dark it is inside. Once you open the door, however, you see a perfectly usable oven rack.",
		true, true, 2, 2, 3,
		"After inserting the Raw Apple Pie into the oven, you close the door and turn the oven on. You then realize \n"
		"why you don't bake very often: it is a process that takes its sweet time. \n \n"
		"An hour later, you pull the pie out of the oven. It looks exquisite. You simply can't help yourself. \n"
		"You grab at the center of the pie like a freak and reel back in shock at how hot the center is. \n"
		"Sure, the whole pie is piping hot, but the center is especially so. You reach in once more and \n"
		"this time you yank the center of the pie out when you reel back from the pain. When you look at \n"
		"your hand, you find a white key.");
	Object cabinets("Cabinets", {"cabinets"},
		"Rather than simply open each cabinet one by one, you zoom around the room opening each of the cabinets rapidly \n"
		"as if you were some sort of tornado. Upon opening the last one you stand in the center of the room and gaze upon \n"
		"all of the open cabinets. Most of them have dust and crumbs but not much else. Finding it hard to believe that \n"
		"you wouldn't at least get SOMETHING for your efforts, you decide to scrutinize the cabinets further. \n \n"
		"Finally, in the very back corner of one of the cabinets, you find a Small Ring.",
		true, false, 0, 4);
	Room kitchen(2, "Kitchen", { refrigerator, pantry, oven, cabinets }, { brittleDoorPtr }, { chickenNugget, applePie },
		{ rawApplePie, whiteKey, smallRing }, {}, { ironRingPtr });

	//Room 3: The Fancy Room
	Object whiteRecliner("White Recliner", {"white recliner", "recliner"},
		"The entire chair is a pristine white, with no signs of stains, dirt, or dust. You could fix that. You feel the \n"
		"seat cushion with your hand and it is soft, yet firm. Everything about this chair seems perfect. You know that \n"
		"there has GOT to be SOMETHING wrong with this chair. You pull down the lever at the side of the chair, and watch \n"
		"as the back of the chair lowers and the foot of the recliner kicks out. The entire process looks remarkably smooth, \n"
		"and you can tell just by looking that it is incredibly comfortable. This recliner is entirely devoid of imperfections. \n"
		"Dang. \n \n"
		"On the bright side, thanks to your thorough inspection, you find a Small Key hiding underneath the recliner.",
		true, false, 0, 6);
	Key smallKey(6, "Small Key",
		"It is a small key, likely made of iron. It is a little odd that is here, though, as there does not appear to be any doors \n"
		"in this room other than the White Door which you have already unlocked.");
	Key firePoker(5, "Fire Poker",
		"An iron rod which is sharpened at the end and used to stoke fires.",
		false, "Selena",
		"\"Oh hey, this Fire Iron would work great as a weapon!\" \n \n"
		"\"...You mean this Fire Poker?\" \n \n"
		"\"Fire Iron sounds cooler.\" \n \n"
		"You realize that you agree, but you're not gonna tell her that.", weapon);
	Weapon fireIron("Fire Iron",
		"An iron rod which is sharpened at the end, which in hindsight makes it a pretty decent weapon. \n"
		"Also used to stoke fires.",
		0, 0, 2, 5, false);
	auto fireIronPtr = make_shared<Weapon>(fireIron);
	Object fireplace("Fireplace", {"fireplace"},
		"The fireplace has a clean brick aesthetic, with a real fire burning and providing warmth to the room. You note that \n"
		"there is a Fire Poker hanging on a hook to the right of the fireplace, but the fire is already burning quite well. \n"
		"The wood inside consists of cleanly cut logs. They clearly were cut by someone who must view woodcutting as a work \n"
		"of art. Perhaps even more interesting, though, is the fact that there is still a lot of wood in the fireplace. This \n"
		"fire must have been started recently. \n \n"
		"Upon giving it a second thought, you decide to take the Fire Poker. It could come in handy.",
		true, false, 0, 5);
	Object bar("Bar", {"bar"},
		"The bar counter, like much of the room, is a pristine white. The bar stools are black, and act to complement the bar's \n"
		"aesthetic quite well. There are many bottles of beverages on some shelves lined up against the wall, most of which appear \n"
		"to be alcoholic. Upon going behind the counter, you see that there are even more bottles beneath the counter. After grabbing \n"
		"a couple of bottles to check them out, you find a small keyhole behind one of the bottles.",
		true, true, 0, 0, 6, 7,
		"Upon inserting the Small Key into the keyhole behind the counter and turning, you hear a clicking sound from your left. You \n"
		"turn toward the left side of the area behind the counter and watch as a section of the floor slides under the adjacent floor \n"
		"panel, revealing a ladder leading down. You debate whether it would be a good idea to enter the Bar's Secret Passage.");
	Door barSecretPassage(std::make_pair(3, 4), "Bar's Secret Passage", false, false, 7,
		"The secret passage is a square hole in the floor, about 4 feet by 4 feet. The ladder goes down about 10 feet, to some \n"
		"underground room. You wonder what could possibly necessitate having a secret passageway like this.");
	auto barSecretPassagePtr = make_shared<Door>(barSecretPassage);
	Object tallBookshelf("Tall Bookshelf", {"tall bookshelf", "bookshelf"},
		"The bookshelf stretches up to the ceiling, just about. Its shelves are all filled to the brim with books many of which \n"
		"look quite thick. After observing the books a bit more closely, you realize that this collection is more or less an \n"
		"assortment of classics. You recognize many of the titles, although you have probably only read a couple out of the \n"
		"dozens that are here. \n \n"
		"As you step away from the bookshelf you realize that there is an indentation in the carpet that makes it look like \n"
		"this bookshelf has been moved. You step to the side of the bookshelf and start pushing. \"Holy crap\", you mutter \n"
		"as you realize that this bookshelf will be harder to move than you realized.",
		true, false, 0, 0, -1, 8,
		"You stand shoulder-to-shoulder with Selena, and start counting to 3. On 3, you both put all of your weight into \n"
		"pushing the bookshelf and manage to get it to budge! From that point on, it's smooth sailing. Together, the two \n"
		"of you push the bookshelf several feet away from its starting position, revealing a secret staircase leading \n"
		"upward. Huh.");
	Door bookshelfPassage(std::make_pair(3, 0), std::make_pair(0, 1), "Bookshelf Passage", false, false, 8, "",
		"It is a secret passage which was hidden behind the bookshelf. The passage has a staircase leading upwards, \n"
		"undoubtedly heading to the next floor.");
	auto bookshelfPassagePtr = make_shared<Door>(bookshelfPassage);
	Room fancyRoom(3, "Fancy Room", { whiteRecliner, fireplace, bar, tallBookshelf }, { whiteDoorPtr, barSecretPassagePtr, bookshelfPassagePtr },
		{}, { smallKey, firePoker }, { fireIronPtr }, {});

	//Room 4: The Cell Exterior
	Door metalDoor(std::make_pair(4, 5), "Metal Door", false,
		"The door seems quite sturdy, and it appears to be locked from your side via a deadbolt and a chain. You decide to \n"
		"look through the door's barred window and see what is being kept in this secret chamber. \n \n"
		"Inside is a young woman with long black hair. She appears to be sitting against the wall with her head in \n"
		"her knees. Despite the fact that she likely heard you given how silent the room is otherwise, she doesn't \n"
		"raise her head to check. You can't help but wonder what a young woman is doing locked up here. What IS this \n"
		"place?");
	auto metalDoorPtr = make_shared<Door>(metalDoor);
	Room cellExterior(4, "Cell Exterior", {}, { barSecretPassagePtr, metalDoorPtr }, {}, {});

	//Room 5: The Cell Interior
	Skill rapidJabs("Rapid Jabs", 5, false, false, 4, "Selena unleashes repeated jabs at the enemy!");
	Player Selena("Selena", 1, 7, 13, {rapidJabs});
	Room cellInterior(5, "Cell Interior", {}, { metalDoorPtr }, {}, {});

	while (true)
	{
		if (floorNum != 0)
			return;
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

					inventory.items.push_back(nibbledCheese);
					players[0].ratlationship -= 2;
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
				checkInput(roomNum, floorNum, players, inventory, startRoom);
				system("pause");
				seeOpening = false;
			}
			else
			{
				system("CLS");
				cout << "Looking around, you see that the room is small and largely empty. However, there is" << endl;
				cout << "a Night Light in the corner, as well as a Plain Door directly in front of you.";
				dblEndl();
				checkInput(roomNum, floorNum, players, inventory, startRoom);
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

			checkInput(roomNum, floorNum, players, inventory, livingRoom);
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

				checkInput(roomNum, floorNum, players, inventory, kitchen);
				system("pause");
				for (int i = 0; i < inventory.items.size(); i++)
				{
					if (inventory.items[i].getName() == "Chicken Nugget")
						grabbedNugget = true;
				}

				if (grabbedNugget)
				{
					system("CLS");
					cout << "Suddenly, you catch a glimpse of something out of the corner of your eye.";
					dblEndl();
					system("pause");
					if (players[0].ratlationship < 0)
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

						Skill ratPunch("Punch", 2, false, false, 0, right, "The rat jumps up and punches you in the neck");
						Enemy rat("Rat", 10, 10, 10, { "" }, { ratPunch });
						vector<Enemy> enemies = { rat };
						fight(players, enemies, inventory.items);

						cout << "The rat is now slumped against the wall, beaten. Its face contorts to one of anger and frustration." << endl;
						cout << "The rat slams its clenched fist against the wall, making a quiet little \"thump\" before it retreats back" << endl;
						cout << "into the hole in the wall.";
						dblEndl();
						cout << "Congratulations! You defended yourself and your nugget!" << endl << endl;
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
							players[0].ratlationship += 1;
							cout << "You hold out the chicken nugget and the rat snatches it up faster than you could blink." << endl;
							cout << "The next thing you know, the rat is back on the counter, nugget in hand. It looks at you" << endl;
							cout << "and nods before heading off through a hole in the wall. It better enjoy that nugget." << endl << endl;
							for (int i = 0; i < inventory.items.size(); i++)
							{
								if (inventory.items[i].getName() == "Chicken Nugget")
									inventory.items.erase(inventory.items.begin() + i);
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
				cout << "Looking around the kitchen once more, you realize that there is more in here than just a Refrigerator." << endl;
				cout << "There is also a Pantry, an Oven, and Cabinets lining the majority of the room's perimeter. Lastly, there" << endl;
				cout << "is the Brittle Door which you used to enter the kitchen in the first place.";
				dblEndl();
				checkInput(roomNum, floorNum, players, inventory, kitchen);
				system("pause");
			}
		}

		if (roomNum == 3)
		{
			system("CLS");
			if (!barSecretPassagePtr->isVisible)
			{
				cout << "Upon entering the room, you find a remarkably clean environment. Everything in the room is pristine. Considering" << endl;
				cout << "that the majority of the room is the color white, it is very impressive. There is a White Recliner facing a" << endl;
				cout << "Fireplace that is in the center of the wall opposite the White Door. To your left is a small Bar, fitted with a" << endl;
				cout << "high counter, bar stools, and many bottles of liquid. Lastly, there is a Tall Bookshelf which reaches the ceiling" << endl;
				cout << "just a few feet to the left of the Fireplace.";
			}
			else if (barSecretPassagePtr->isVisible && !bookshelfPassagePtr->isVisible)
			{
				cout << "Upon entering the room, you find a remarkably clean environment. Everything in the room is pristine. Considering" << endl;
				cout << "that the majority of the room is the color white, it is very impressive. There is a White Recliner facing a" << endl;
				cout << "Fireplace that is in the center of the wall opposite the White Door. To your left is a small Bar, fitted with a" << endl;
				cout << "high counter, bar stools, and many bottles of liquid. Also worthy of note is the Bar's Secret Passage leading" << endl;
				cout << "down below the floor. Lastly, there is a Tall Bookshelf which reaches the ceiling just a few feet to the left" << endl;
				cout << "of the Fireplace.";
			}
			else
			{
				cout << "Upon entering the room, you find a remarkably clean environment. Everything in the room is pristine. Considering" << endl;
				cout << "that the majority of the room is the color white, it is very impressive. There is a White Recliner facing a" << endl;
				cout << "Fireplace that is in the center of the wall opposite the White Door. To your left is a small Bar, fitted with a" << endl;
				cout << "high counter, bar stools, and many bottles of liquid. Also worthy of note is the Bar's Secret Passage leading" << endl;
				cout << "down below the floor as well as the Bookshelf Passage leading upstairs now that it is no longer hidden by the" << endl;
				cout << "Tall Bookshelf. Lastly, there is a cozy fireplace in the center of the back wall.";
			}
			dblEndl();

			if (players.size() > 1)
			{
				cout << "\"Alright! It's nice being outside of that stupid underground room! Okay! First thing's first--we should look" << endl;
				cout << "for something that I could use to defend myself. Preferably something sharp.\"";
				dblEndl();
				if (players[0].exploreOptions.size() < 5)
				{
					cout << "Suddenly, an idea pops into your head. \"Hey, Selena? We should try teaming to take care of some things. I feel" << endl;
					cout << "if we work together to investigate some objects, we'll be able to uncover more than we would otherwise be able to.\"";
					dblEndl();
					cout << "Selena tilts her head for a second as she thinks, before responding,\"Yeah, sure. That makes sense. If you ever" << endl;
					cout << "find yourself in need of THESE GUNS\", she says as she flexes her fairly average-sized arms, \"then you know who" << endl;
					cout << "to call.\"";
					dblEndl();
					cout << "You can't help but let out a small chuckle in response to that.";
					dblEndl();
					cout << "Selena puts her hands on her hips. \"Oh, come on, I'm working on it. It's hard to stay in shape when you're stuck" << endl;
					cout << "in a cell for who knows how long.\"";
					dblEndl();
					cout << "You can now use the \"teamwork\" exploration ability!";
					dblEndl();
					players[0].exploreOptions.push_back("teamwork");
				}
			}

			checkInput(roomNum, floorNum, players, inventory, fancyRoom);
			system("pause");
		}

		if (roomNum == 4)
		{
			system("CLS");
			cout << "Once you are at the bottom of the ladder, you get a much better look at the room down here. Your new surroundings" << endl;
			cout << "are cold, both in terms of atmosphere and the actual temperature. The walls are made of black concrete, and the room" << endl;
			cout << "is dimly lit, with hardly any light coming through the Bar's Secret Passage. There is only one lightbulb in the room," << endl;
			cout << "and its light is weak and takes on a yellow hue. As you look around a bit more, you realize there is nothing else of" << endl;
			cout << "note in this small room except for a Metal Door with a barred window at eye level.";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, cellExterior);
			system("pause");
		}

		if (roomNum == 5)
		{
			system("CLS");
			cout << "From right in front of the metal door, you get a better look at the room here. Like the room outside, the walls are" << endl;
			cout << "entirely composed of black concrete, and there is one dim bulb attempting to light up the place. Like the other" << endl;
			cout << "room, it appears largely empty and cold. There isn't much to note here other than the Metal Door you entered through.";
			dblEndl();
			if (players.size() < 2)
			{
				cout << "Well, that and the young woman sitting against the wall with her head in her knees.";
				dblEndl();
				system("pause");

				system("CLS");
				cout << "Now that you are in the cell, the woman looks up from her knees. While her eyes initially look exhausted," << endl;
				cout << "they widen considerably once she sees you, and the door you left wide open. ";
				dblEndl();
				cout << "\"W-who are you? I've never seen you before.\"";
				dblEndl();
				cout << "(1) \"My name is " << players[0].getName() << ". I just woke up here, like, 15 minutes ago. I don't know where I am.\"" << endl;
				cout << "(2) \"Why don't you introduce yourself first?\"" << endl;
				cout << "(3) \"I'm your worst nightmare.\"";
				dblEndl();
				int input = getDecision(1, 3);

				if (input == 1)
				{
					cout << "\"You don't know where you are either? This could be perfect! Oh, uh, right! My name is Selena. Some man" << endl;
					cout << "has me locked up in this cell, but I don't know how I got here. You want to get out of here, too, right?" << endl;
					cout << "Two people are better than one! How about it?\"";
					dblEndl();
					cout << "A small smile forms on Selena's face, and her pupils enlarge as she stares directly at you, waiting for" << endl;
					cout << "your response.";
					dblEndl();
					cout << "(1) \"Yeah, that sounds great! Having a partner would make things a lot easier.\"" << endl;
					cout << "(2) \"Alright! I don't even remember the last time I spoke to a girl!\"" << endl;
					cout << "(3) \"Not in a million years.\"";
					dblEndl();
					int input2 = getDecision(1, 3);

					if (input2 == 1)
					{
						cout << "\"Yes! Okay! Come on, let's get out of here!\"";
						dblEndl();
						cout << "Selena jumps up from her spot on the floor with a hopeful smile on her face. She walks over to you" << endl;
						cout << "and shakes your hand. You look her in her brown eyes as she looks back at you.";
						dblEndl();
						cout << "\"I am not too experienced in a fight, but I have a lot of practice with a rapier from my time" << endl;
						cout << "taking some fencing classes for the last few years. If we find something I could use to stab things,\"" << endl;
						cout << "her eyes widen and she holds out her hands as she realizes what she just said, \"purely for self-defense," << endl;
						cout << "then I would feel a lot better about our chances should things take a turn for the worse.\"";
						dblEndl();
						cout << "You eye her skeptically. \"Alright, I think I may have seen something like that nearby...\"";
						dblEndl();
						players.push_back(Selena);
					}
					else if (input2 == 2)
					{
						cout << "Selena's hopeful expression quickly adjusts to one of concern. \"You don't know where you are, you find" << endl;
						cout << "someone locked in a hidden cell who also doesn't know where they are, and the thing you're focused on is" << endl;
						cout << "the fact that the person you found is a girl?\"";
						dblEndl();
						cout << "\"Yes.\"";
						dblEndl();
						cout << "Selena looks herself over briefly, likely reconsidering her proposal, and then looks back up at you." << endl;
						cout << "As she brushes some strands of her hair off to the side of her face, she responds, \"Alright. Let's" << endl;
						cout << "see if the novelty lasts.\"";
						dblEndl();
						players.push_back(Selena);
					}
					else if (input2 == 3)
					{
						cout << "Selena's eyes open wide as her pupils shrink instantaniously in shock. She then quickly adapts her" << endl;
						cout << "expression to a grin as she chuckles nervously. \"Haha, you nearly got me with that one. That's some" << endl;
						cout << "kind of joke to spring on someone in dire need who you just met.\"";
						dblEndl();
						cout << "\"Who said anything about a joke? Get lost.\"";
						dblEndl();
						cout << "Her grin evaporates. \"I AM LOST!\" She then gestures toward you with both of her arms. \"YOU ARE, TOO!" << endl;
						cout << "It just makes sense that we would work together! It's a mutually beneficial arrangement!\"";
						dblEndl();
						cout << "\"Yeah, right. Any arrangement where I have to partner up with someone I don't know is primed with" << endl;
						cout << "risk. You could be an incessant whiner for all I know.\"";
						dblEndl();
						cout << "\"I DON'T WHINE...much. I'm a hard worker! I put effort into everything that I do! And I have an" << endl;
						cout << "award-winning personality! You will LOVE me!\"";
						dblEndl();
						cout << "You put your index finger and thumb up to your chin as you ponder her claims. \"What you're saying" << endl;
						cout << "sure SOUNDS nice, but it all sounds pretty subjective to me.\"";
						dblEndl();
						cout << "Selena straightens her posture as her face turns serious and professional. \"Listen, I have years of" << endl;
						cout << "experience fencing, and I was in the top 10% of my class. I'm good in a fight, and I'm not stupid either." << endl;
						cout << "I stand by everything I said before, as well. Trust me, partnering with me will make your life a whole lot better.";
						dblEndl();
						cout << "It was a good sales pitch. And what she was saying made sense. \"Alright. I guess a million years passes" << endl;
						cout << "by quicker than one would expect.\" You then hold out your hand.";
						dblEndl();
						cout << "Selena reaches out and shakes your hand. She then looks you straight in the eyes with a determined expression." << endl;
						cout << "\"Trust me, you won't regret this.\"";
						dblEndl();
						players.push_back(Selena);
					}
				}
				else if (input == 2)
				{
					cout << "\"O-okay. My name is Selena. I just woke up in this cell one day and I have no idea how I got here." << endl;
					cout << "You don't work here, do you? You're not with that man?";
					dblEndl();
					cout << "A puzzled look forms on your face as you wonder what she meant by \"that man\". Selena seems to catch on" << endl;
					cout << "to your confused expression.";
					dblEndl();
					cout << "\"He comes in here and checks on me every now and again. Sometimes he brings food, other times he just talks" << endl;
					cout << "and talks and expects me to listen. He's the only person I've seen since I've arrived here, until now.\"";
					dblEndl();
					cout << "(1) \"My name is " << players[0].getName() << ". I also don't know where I am.\"" << endl;
					cout << "(2) \"Well, this is your lucky day. The name's " << players[0].getName() << ". Let's get out of here." << endl;
					cout << "(3) \"Hey, free food is nothing to shake a stick at. Sounds like you've got a sweet gig going on here.\"";
					dblEndl();
					int input2 = getDecision(1, 3);

					if (input2 == 1)
					{
						cout << "\"Ah, so we're in the same boat, then.\" Selena pauses for a moment. \"Tell you what, how about we team" << endl;
						cout << "up? I feel like we would greatly increase our chances of getting out of here if we work together.\"";
						dblEndl();
						cout << "\"What you're saying makes sense, but how can I know that I can trust you?\" You fold your arms and" << endl;
						cout << "raise one eyebrow to assert your skepticism.";
						dblEndl();
						cout << "Selena lets out a sigh. \"There's no possible way I can truly prove to you that I can be trusted, but" << endl;
						cout << "something I CAN do is give you a firm handshake.\" Selena throws her hand out toward you, her face a smile" << endl;
						cout << "brimming with determination.";
						dblEndl();
						cout << "You eye her for a bit before finally deciding to put your hand out there as well. As it turns out, she wasn't" << endl;
						cout << "lying; she really could give a firm handshake. At the end of the day, you've gotta respect a good handshake." << endl;
						cout << "And if she turns out to be some kind of freak who uses handshakes to trick people... then you can deal with" << endl;
						cout << "her later.";
						dblEndl();
						players.push_back(Selena);
					}
					else if (input2 == 2)
					{
						cout << "As soon as you finish talking, you wink at her. Her eyes widen in surprise at the combination of your" << endl;
						cout << "abrupt change in attitude and sheer confidence on display. \"Well, I, uhh... I agree that teaming up" << endl;
						cout << "would give us our greatest chances of finding our way out of here. But, uhh... why are you so confident?" << endl;
						cout << "Do you know how to get out of here?\"";
						dblEndl();
						cout << "\"Nope.\"";
						dblEndl();
						cout << "\"Oh, well, do you have an good lead, then?\"";
						dblEndl();
						cout << "You respond with a smug grin. \"Not at all. I've actually currently at a dead end.\"";
						dblEndl();
						cout << "Selena's eyes move toward the side as she lets out a sigh. \"Oh.\" She may have a look of both concern and" << endl;
						cout << "disappointment on her face, but you know that you'll find your way out somehow. Probably. \"Well, let's get" << endl;
						cout << "going, I guess. I'd much rather get stuck somewhere else than spend another day in here.\" She then shakes her" << endl;
						cout << "head quickly to psyche herself up. \"Alright! Let's go find a way out of this place!\"";
						dblEndl();
						players.push_back(Selena);
					}
					else if (input2 == 3)
					{
						cout << "Selena looks at you with wide eyes like you're crazy. \"Didn't you hear me? I'm trapped here! Being stuck in" << endl;
						cout << "this room with nothing to do sucks! All I can do is wonder where I am and why I'm being kept here in the first" << endl;
						cout << "place! It's both boring and creepy.\"";
						dblEndl();
						cout << "\"I suppose. Still, though, I haven't seen much food around here. The kitchen was practically bare. Where" << endl;
						cout << "could they have gotten it from?\"";
						dblEndl();
						cout << "Selena leans in closer and responds with a sharp, determined tone. \"I would rather scrounge around for crumbs" << endl;
						cout << "out there than spend another day in this cell.\"";
						dblEndl();
						cout << "\"Alright. Tell you what: help me find a way out of here and I might just share some food I've come across. Deal?\"" << endl;
						cout << "You hold out your fist.";
						dblEndl();
						cout << "Selena pounds your fist, completing the fist bump. \"Deal.\", she replies, smiling.";
						dblEndl();
						players.push_back(Selena);
					}
				}
				else if (input == 3)
				{
					cout << "The woman freezes for a second before her face shifts to one of bewilderment.";
					dblEndl();
					cout << "\"Who introduces themselves like that?\"";
					dblEndl();
					cout << "\"I do, apparently.\"";
					dblEndl();
					cout << "The woman seems to contemplate something for a solid 15 seconds before she sighs and begins to speak again.";
					dblEndl();
					cout << "\"...Do you want to get out of here like I do? Mathematically, we would be more likely to escape if we worked" << endl;
					cout << "together.\"";
					dblEndl();
					cout << "(1) \"Sure, but how did you know I would want to get out of here?\"" << endl;
					cout << "(2) \"Yeah, that sounds wise.\"" << endl;
					cout << "(3) \"Nah, I'm more the lone wolf type.\"";
					dblEndl();
					int input2 = getDecision(1, 3);

					if (input2 == 1)
					{
						cout << "\"I've only seen one other person here, and I don't see an associate of his having your... sense of humor. \"";
						dblEndl();
						cout << "\"You've seen another person? Why didn't you team up with them?\"";
						dblEndl();
						cout << "\"He is the one who has kept me fed. I do not know why he seems to want me in this cell, but yeah, he " << endl;
						cout << "isn't exactly a good candidate for a partner.\"";
						dblEndl();
						cout << "You nod your head. \"I guess that makes sense. Let's get out of here, then. My name is " << players[0].getName();
						cout << ", by the way. Not Your Nightmare.\"";
						dblEndl();
						cout << "\"Ah, is that so? And here you had almost had me.\" The woman lets out a small grin. \"My name's Selena.\"";
						dblEndl();
						cout << "She holds out her hand. You reach out and give it a good shake. Here's hoping this partnership goes well.";
						dblEndl();
						players.push_back(Selena);
					}
					else if (input2 == 2)
					{
						cout << "\"Alright, let's get going, then, \'My Worst Nightmare\'. I'd like to get out of this cell as soon as" << endl;
						cout << "I can, and to never see it again while I'm at it.\"";
						dblEndl();
						cout << "\"My name is \'YOUR Worst Nightmare\', thank you very much. But hey, I appreciate you trying.\" As you finish" << endl;
						cout << "saying this, you make an intentionally smug grin.";
						dblEndl();
						cout << "The woman chuckles. \"Heh, alright, my bad. Have you got something I can call you that's less of a mouthful?\"";
						dblEndl();
						cout << "\"I suppose you could call me " << players[0].getName() << ", if the other name is too much for you.\"";
						dblEndl();
						cout << "She smiles and replies, \"My name is Selena. And " << players[0].getName() << " will work just fine. Alright," << endl;
						cout << "let's go find our way out of here.\"";
						dblEndl();
						players.push_back(Selena);
					}
					else if (input2 == 3)
					{
						cout << "The woman's pupils shrink as she hears your declaration. \"W-well what if you come across some heavy object" << endl;
						cout << "you'd need a second person for to help lift? Or if you come across some item you don't recognize or" << endl;
						cout << "understand? Having a second person around could help your chances of escaping here greatly!\"";
						dblEndl();
						cout << "\"Nah, I'm good. I'm kinda the best there is.\"";
						dblEndl();
						cout << "The woman blinks rapidly in disbelief at the words she is hearing. \"W-well, think about this: In addition to" << endl;
						cout << "helping you explore, I can also help you carry stuff so you don't have to carry as much!\" She smiles, but" << endl;
						cout << "it is a desperate smile. Still, though...";
						dblEndl();
						cout << "\"I do hate carrying a bunch of stuff... Why do you want to work with me so badly?\"";
						dblEndl();
						cout << "\"Uh, would you believe me if I said I genuinely believe in the stuff I'm saying?\"";
						dblEndl();
						cout << "You stare at her. And stare at her. Annnnd keep staring.";
						dblEndl();
						cout << "The woman looks down at the floor and adds quietly, \"Or that I'm lonely and bored and want someone to talk to?\"";
						dblEndl();
						cout << "\"Theeeeeere we go. Well, alright then. But if I'm going to start making fun of- I mean, talking to someone," << endl;
						cout << "then I'm going to need to know their name.\"";
						dblEndl();
						cout << "The woman glares at you briefly, before forming a smile on her face. \"My name is Selena. I look forward to" << endl;
						cout << "to getting out of here.\" She extends her hand, and you shake it.";
						dblEndl();
						cout << "\"" << players[0].getName() << ". Let's get out of here.\"";
						dblEndl();
						players.push_back(Selena);
					}
				}
				system("pause");
			}
			else
			{
				checkInput(roomNum, floorNum, players, inventory, cellInterior);
				system("pause");
			}
		}
	}
}