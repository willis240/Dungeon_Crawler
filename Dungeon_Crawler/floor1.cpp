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
using std::make_pair;

void floor1(vector<Player>& players, int& roomNum, int& floorNum, Inventory& inventory, bool& floor1FirstTime, bool& foundAria,
	bool& greenhouseFirstTime, bool& openedSafe, bool& entrywayFirstTime)
{
	string playerInput = "";
	bool foughtRat2 = false;

	//Room 0: Hall of Opportunity
	Door rightDoor(make_pair(0, 1), "Right Door", {"right door", "right"}, false,
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is pretty \n"
		"much identical to both of the other doors in the room.");
	auto rightDoorPtr = make_shared<Door>(rightDoor);
	Door leftDoor(make_pair(0, 2), "Left Door", {"left door", "left"}, true, true, 1,
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is identical \n"
		"to both of the other doors in the room, except for a green rim around the doorknob. Upon trying the handle, you \n"
		"find that it is locked.",
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is identical \n"
		"to both of the other doors in the room, except for a green rim around the doorknob. Since you stuck the Green \n"
		"Key in it, it is now unlocked.");
	auto leftDoorPtr = make_shared<Door>(leftDoor);
	Door middleDoor(make_pair(0, 3), "Middle Door", { "middle door", "middle" }, true, true, 8,
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is near \n"
		"identical to both of the other doors in the room. Upon trying the handle, you find that it is locked. \n",
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is near \n"
		"identical to both of the other doors in the room. Since you stuck the Middle Key in it, it is now unlocked.");
	auto middleDoorPtr = make_shared<Door>(middleDoor);
	Weapon fireIron("Fire Iron", {"fire iron"},
		"An iron rod which is sharpened at the end, which in hindsight makes it a pretty decent weapon. \n"
		"Also used to stoke fires.",
		0, 0, 2, 5, false);
	auto fireIronPtr = make_shared<Weapon>(fireIron);
	Door bookshelfPassage(std::make_pair(3, 0), std::make_pair(0, 1), "Bookshelf Passage", { "bookshelf passage", "staircase" }, false, true, 0, "",
		"It is a secret passage which was hidden behind the bookshelf. Or at least, that's how it appeared downstairs. \n"
		"From here it seems just as conspicuous as any staircase. Should you desire to go back to the ground floor, \n"
		"this would be the way to do it.");
	auto bookshelfPassagePtr = make_shared<Door>(bookshelfPassage);
	Room hallway(0, "Hallway", {}, {rightDoorPtr, leftDoorPtr, middleDoorPtr, bookshelfPassagePtr}, {}, {});

	//Room 1: Bedroom
	Object closet("Closet", {"closet"},
		"You put your hand on the knob of the bifold door and try to pull it open, but there is some serious \n"
		"resistance coming from the other side. You stop for a moment, and then try again, harder. However, as you \n"
		"pull harder, the resistance from the other side increases to match. You turn to Selena, and begin whispering. \n"
		"\"It doesn't feel like the door is getting caught on something behind it. I think there's someone IN there.\" \n \n"
		"\"Hey, we know you're in there. Come on out. We won't hurt you... unless you're that thug or that weirdo with the \n"
		"monocle. Then we're gonna hurt you.\" \n \n"
		"Despite Selena's... comforting... words, whoever is behind the closet does not budge. All that you hear is a quiet \n"
		"rumbling from behind the bifold doors and then... silence.",
		true, true, 0, 0, 3,
		"You hold up the pomegranate a couple of feet in front of your face, as if you were observing a work of art. \"Ah, \n"
		"the pomegranate. Truly God's masterpiece of fruit. Wouldn't you agree, Selena?\" \n \n"
		"\"Most certainly, my good sir. From the beautiful red outer husk to the white inner wall and the crimson seeds within, \n"
		"this fruit is a delight simply for the eyes, to say nothing of the tongue and stomach. To speak of the taste, though-\" \n \n"
		"\"Oh, utterly delectable. The initial wave of tart, followed by a familiar sweetness. I simply don't understand how-\" \n \n"
		"\"I CAN'T TAKE ANYMORE!!!\" A shout pierces through the closet's bifold doors before a girl throws them open and \n"
		"bursts through the opening. Suddenly, in a flash the pomegranate in your hand disappears. You turn to find the girl \n"
		"now sitting on the bed, munching on the pomegranate. Success.");
	Object queenBed("Queen Size Bed", {"queen size bed", "bed"},
		"As you press your hand down upon it, you find that the bed is soft--very soft. The violet blanket covering\n"
		"it is well-insulated and comforting to the touch. You simply can't resist. You throw yourself upon the bed,\n"
		"back first. A dumb grin widens across your face as the bed soothes your back. Selena raises an eyebrow, acting\n"
		"as the resident comfortability skeptic, you suppose. However, in order to be a fair judge, she reaches a hand \n"
		"out to the bed and clutches the blanket... Needless to say, she then jumps onto the bed alongside you as a stupid \n"
		"grin finds its way onto her face. \n \n"
		"\"\"Ahhhhh...\"\", you both sigh in relief. A delightful respite.",
		true, false, 0, 0);
	Key greenKey(1, "Green Key", {"green key"}, "A standard door key, albeit with a green coloring scheme.");
	Object nightstand("Nightstand", {"nightstand"},
		"It appears to be a simple, yet elegant nightstand. The edges are all black, but the rest of the surfaces\n"
		"have a brown marble aesthetic. There is a drawer in the nightstand. While everything else you've done to\n"
		"this point could at worst be described as looting a family room, this feels like it would be a bit too personal. \n \n"
		"Welp, there's a first for everything. \n \n"
		"You open the drawer, and find a Green Key. \"That was easy.\"",
		true, false, 0, 1);
	Object window("Window", {"window"},
		"You run to the window, hoping to get a look at the outside for the first time since you woke up. Perhaps if you \n"
		"see what the outside looks like, you can get an idea of where you are and also get some ever-desirable Vitamin D.\n"
		"You make it to the window and find that the outside looks like... a wall. \n \n"
		"In hindsight, you saw from the previous hallway that there was a room directly to the left of this one. Still, \n"
		"the people who constructed this building could've at least put more than an inch between this room and the next \n"
		"if they were going to leave outdoor space between them and make a window. You found this simultaneously bewildering \n"
		"and disappointing. Selena then describes the situation succinctly: \"This window sucks.\"",
		true, false, 0, 0);
	Key diary(7, "Diary", {"diary"},
		"A diary detailing many events in a young girl's life. It seems she would write in it once a week, every week, \n"
		"and did so for years. The beginning is quite dull, so you decide to skim the book for anything that could be \n"
		"interesting. \n \n"
		"\"May 5th- \n"
		"Miranda is a dear friend and I love her, but she really has some poor taste. She says that the new Gargoyle \n"
		"Wars movie is way better than The Stars Beyond Our Reach, when the new Gargoyle Wars movie is actual hot garbage. \n"
		"I mean, it COMPLETELY obliterates all of the character development that Gray went through in the previous movie, \n"
		"acting as if it just never even happened! It is horribly frustrating to watch as someone who was such a big fan \n"
		"up to this point.\" \n \n"
		"\"May 12th- \n"
		"Oh my gosh Miranda keeps talking about the new Gargoyle Wars movie. I've said my piece to her about how I feel \n"
		"about the movie, but I was polite about it since I knew that she really liked it. If I hear her talking about \n"
		"that stupid fricking movie one more time I am going to tear it to shreds. It's like comparing an apple to a \n"
		"pomegranate; one is a delicious snack with a deep, delectable flavor and the other is best used as a thrown \n"
		"weapon. The only thing an apple is good for is for apple pie. Still, I'd prefer eating five apples to watching \n"
		"Gargoyle Wars 8 again.\" \n \n"
		"\"May 19th- \n"
		"Okay, if I had to write about the stupid movie a third week in a row I would lose my mind. Thankfully, it's been \n"
		"quiet on that front. Miranda and I went together with Abby and Toby yesterday to the ice cream shop and got some \n"
		"milkshakes. There were a lot of options there, including orange, strawberry, banana, and even some really strange \n"
		"flavors like tomato and carrot. I'm not a fan of any of those fruit, but I still consider myself to be a gal with \n"
		"simple taste. I went with chocolate. It was SO GOOD!! Ah, I love the spring.\" \n \n"
		"\"This girl gets it. Gargoyle Wars 8 freaking sucks.\"");
	Key middleKey(8, "Middle Key", { "middle key" }, "A standard key. Unlocks the Middle Door.");
	Object desk("Desk", {"desk"},
		"You find that it is a simple wooden desk. It does not have any particular decorations to make it stand out \n"
		"or feel fancy. It has a single drawer under its mid-section, inside of which is a book. One look at the cover \n"
		"and you immediately realize it's a diary. \n \n"
		"\"You're not seriously going to-\" \n \n"
		"\"Desperate times call for desperate measures. There could be a clue in here. Or a hollowed-out section with \n"
		"a key in it! This book holds too much potential for us to simply ignore it!\" \n \n"
		"Selena ponders for a moment, a slightly grumpy frown showcasing her displeasure for intruding on another's \n"
		"privacy. You speak up once again, \"Tell you what: If we come across this journal's owner, then I will let \n"
		"them read my journal and learn all of the juicy secrets within it, just to be fair.\" \n \n"
		"Selena chuckled. \"I'll hold you to that.\" After a short pause, she added, \"I just know I wouldn't want \n"
		"some random person to read all of my diary.\"",
		true, false, 0, 7);
	Skill quickSlap("Quick Slap", 2, false, false, 2, "Aria delivers a swift backhand!");
	Player Aria("Aria", 2, 9, 11, {quickSlap});
	Room bedroom(1, "Bedroom", { closet, queenBed, nightstand, window, desk }, { rightDoorPtr }, {}, { greenKey, diary});

	//Room 2: Greenhouse Room
	Accessory fingerlessGloves("Fingerless Gloves", {"fingerless gloves", "gloves"},
		"A pair of gloves with holes where your fingers go. Not useful for dealing with firewood.",
		0, 0, 2);
	auto fingerlessGlovesPtr = make_shared<Accessory>(fingerlessGloves);
	Accessory redArmband("Red Armband", {"red armband", "armband"},
		"An armband with a scarlet hue. Some might call it fashionable.", 2, 2, 0);
	auto redArmbandPtr = make_shared<Accessory>(redArmband);
	Key tomato(2, "Tomato", {"tomato"}, "A plump, red tomato. Good on sandwiches.");
	Object tallPlant("Tall Plant", {"tall plant", "plant"},
		"The Tall Plant stands straight and green. Notably, it would likely not stand so straight were it not being supported \n"
		"by what looks to be a wireframe. After feeling around the plant's leaves you begin to hypothesize that this is a \n"
		"tomato plant. Your hypothesis is backed up by the several soft red fruit growing on the plant. Might as well take one.",
		true, false, 0, 2);
	Key pomegranate(3, "Pomegranate", {"pomegranate"}, "An red fruit which is at first tart, but then sweet. An old favorite of Selena's.");
	Object greenTree("Green Tree", {"green tree"},
		"The tree, though small by tree standards, has a strong trunk with the kind of standard brown bark one would commonly \n"
		"associate with trees. The top of the tree has many green leaves covering it, enough to obscure a significant part of \n"
		"the window behind it from view. You look around its leaves and find something resembling a fruit hiding there. You \n"
		"grab the object, and before you have time to comment on it, you hear Selena from over your shoulder: \"Ooo, a pomegranate! \n"
		"I used to have these with my lunch all the time when I was a kid.\" She then proceeds to reach for a pomegranate from \n"
		"the tree as well and takes a big chomp out of it. \"Mmm. Still good.\"",
		true, false, 0, 3);
	Key apple(4, "Apple", {"apple"}, "An iconic red fruit, said to keep those with PhDs away.");
	Object appleTree("Apple Tree", {"apple tree"},
		"Now this was a tree you could easily recognize at a glance. You would recognize that crisp, red fruit anywhere. You \n"
		"reach up and pluck an Apple from one of the lower branches. It was at this moment that you realized the ceiling of \n"
		"of this room is quite high. All the better for growing the trees and taller plants, you suppose.",
		true, false, 0, 4);
	Key coconut(5, "Coconut", {"coconut"}, "A big, brown, durable fruit. Not entirely unlike a bowling ball.");
	Object palmTree("Palm Tree", {"palm tree"},
		"Amongst all of the different plants in the room, this one stands out quite a bit. Its large leaves lend it a visual \n"
		"flavor that is distinct. The fruit it carries likewise have a distinct look to them. They are brown, and similar \n"
		"in shape to a bowling ball. You kick off of the palm tree and manage to snag one of the \"bowling balls\". \n \n"
		"Next, you turn toward Selena, who appears to be investigating a different plant with her back facing you. Big mistake. \n"
		"You then roll the home-grown bowling ball toward Selena's \"pins\", and manage to strike one. \"Ow!\" She lifts her \n"
		"struck leg and grabs the back of her calf, but the other pin still stands. Before you have time to think of securing \n"
		"a spare, she shoots a deadly glare in your direction. Next time.",
		true, false, 0, 5);
	Key carrot(6, "Carrot", {"carrot"}, "An orange vegetable. Rumored to improve eyesight.");
	Object buriedVeggies("Buried Veggies", {"buried veggies", "veggies"},
		"While you recognize that the green leaves sticking out of the dirt indicate that there are vegetables hiding below, \n"
		"you are not exactly a botanist. Pinpointing which vegetable it is exactly will have to fall to the tried-and-true \n"
		"approach. As you yank the veggie out of the dirt, you find a familiar orange shape.",
		true, false, 0, 6);
	Room greenhouseRoom(2, "Greenhouse Room", {tallPlant, greenTree, appleTree, palmTree, buriedVeggies}, {leftDoorPtr},
		{}, {tomato, pomegranate, apple, coconut, carrot});

	//Room 3: Family Room
	string passwordAttempt = "";
	Object couch("Couch", { "couch", "sofa" },
		"The couch is a dark blue color, and it looks well-loved.\n \n"
		"\"This is our living room couch\" Aria says, gesturing toward it. \"Go ahead. Sit on it.\" \n \n"
		"You shrug and decide you might as well. Upon sitting on it you realize ohhhh it's comfy. Very comfy. \n \n"
		"\"It's nice, right?\" \n \n"
		"You don't bother speaking. You simply let your back sink into the couch and give a thumbs-up.",
		true, false, 0, 0);
	Key cableHDMI(9, "HDMI Cable", { "hdmi cable", "hdmi", "cable", "Cable" },
		"A cable for transmitting audio and video signals from a device to a monitor.", true);
	Object television("Television", { "television", "TV", "tv" },
		"Upon turning the TV on, the login screen for a game console appears. You recognize it as the first thing you see \n"
		"after booting up a Vcube 220. You look to the right and, sure enough, just a few inches to the right of the TV \n"
		"is a Vcube 220, connected via an HDMI Cable. Looking back at the screen, you see an account named \"Supreme297.\" \n \n"
		"\"Yeah, that's my brother's account\", Aria states. \"I think he called it Supreme because he wanted to sound \n"
		"cool, but it just makes me think of a nacho supreme every time.\" \n \n"
		"Selena lets out a small chuckle. \"Honestly, I cringed a bit when I first saw the name.\" \n \n"
		"\"Yeah... I think he was in middle school when he made the account.\" \n \n"
		"\"You know\", you begin, \"suddenly I feel like naming my account GamerLord20X wasn't a bad idea.\" \n \n"
		"Selena laughs. \"That sounds way cringier than just supreme.\" \n \n"
		"\"Hey\", you point at her as you declare: \"Go big or go home.\"",
		false, 0, 9, 9,
		"Upon turning the TV on, you see a bright blue screen along with text in the top left stating \"HDMI 3\".\n"
		"It would appear that nothing is hooked up to the TV's HDMI 3 port."
		);
	Object computer("Computer", { "computer", "PC", "pc" },
		"Upon turning on the computer you find yourself at the login screen for an account named \"Supercool\". You \n"
		"slowly turn your head toward Aria. \n \n"
		"\"What?\" She says as her cheeks begin to flush. \"I mean, I wasn't going to use my name. Using this name \n"
		"basically provides me with an extra layer of security.\" \n \n"
		"You deliver unto her a smug grin. \n \n"
		"\"Like you have room to talk, \'GamerLord\'.\" Aria retorts as she logs into her profile. Your smug grin \n"
		"doesn't budge an inch. \n \n"
		"Upon logging into Aria's profile the first thing that pops up is a popular chatting app called Bliscord, \n"
		"which is often used for communicating with others over the internet via text or voice chat. Aria immediately \n"
		"notices that there is an unread message from one Supreme297. \"What?!\" She opens up the chat feed, only to see \n"
		"that it was from 10 days ago. The message said: \n \n"
		"\"Hey Aria, I'm fine, but it might be a while before you see me again. I promise I will come back as soon\n"
		"as I can. If you find yourself stuck, \'Remember Me\'.\" \n \n"
		"A droplet of water begins to form in Aria's right eye. She wipes it away. \"Well, I'm glad my brother was okay \n"
		"ten days ago... I can only hope that that's still true now.\"",
		true, 0, 0, 9,
		"Upon turning the computer and the monitor on, you hear fans start up and see a blue screen appear. The screen \n"
		"boldly proclaims \"NO SIGNAL\". Upon feeling around the back of the monitor you realize that it is not connected \n"
		"to the Computer at all."
		);
	Object entertainmentCenter("Entertainment Center", { "entertainment center", "entertainment", "center" },
		"The entertainment center upon which the TV rests is a wooden one, with cabinet doors. You open the doors to \n"
		"find a couple of older game consoles, as well as a movie player. \n \n"
		"\"Ah, so you really are a gamer\", you declare to Aria. \n \n"
		"\"Yeah, me and my brother played a lot of games together growing up, and it just kinda stuck.\" Aria notices \n"
		"the blank expression upon Selena's face and decides to add her to the conversation. \"What about you, Selena? \n"
		"Do you play any video games?\" \n \n"
		"\"Well, I dabble. I've played some games a good chunk, but not, like, a TON, you know?\" \n \n"
		"You decide to not say anything for now, but you fear you may have let a casual gamer into your party.",
		true, false, 0, 0
		);
	Item mountainDont("Mountain Don't", { "mountain don't", "Mountain", "mountain" }, 0, 8,
		"A popular soda known for its distinct flavor and distinct lack of nutritional benefits.\n Provides energy, though.", 1);
	Object miniFridge("Mini Fridge", { "mini fridge", "Fridge", "fridge" },
		"The mini fridge is a smooth black variant, although its glossy exterior has left it prone to visible \n"
		"fingerprints. Upon opening the door, you find a largely barren interior with one exception: a single \n"
		"can of Mountain Don't. \n \n"
		"\"Ooo, sweet!\" Selena exclaims as she yoinks the can from right under your nose. \"I haven't had one \n"
		"of these in ages!\" \n \n"
		"As you contemplate tearing the can from Selena's clutches, you hear Aria speak up,\"Have at it. There's \n"
		"a reason that can's still there. I can't stand the flavor.\" \n \n"
		"You can't let that one slide completely. \"You dislike Mountain Don't? Is that still legal?\" \n \n"
		"Aria chuckles. \"Heh, yes, thankfully. You can thank my brother for that can being here at all.\" \n \n"
		"Selena raises the can above her head with both of her hands. \"Thank you, Person I Have Never Met, \n"
		"for your wonderful taste in soda!\"",
		true, false, 1, 0);
	Object table("Table", { "table" },
		"The table is of the wooden variety. Nothing too fancy, but it is a fairly nice table. It is certainly more \n"
		"pleasant to the eye than a plastic one. It seems to be large enough to seat six people comfortably. \n \n"
		"\"I like this table\", says Aria, unprovoked. \"You wanna see the coolest part?\" \n \n"
		"You and Selena both shrug. \"\"Sure\"\". \n \n"
		"Aria reaches around the lip of the table and flicks a switch underneath the table top. She then crawls under \n"
		"the table and pulls open a hidden hatch in one of the table's legs. Inside is a small black box. \n \n"
		"In hindsight, the table's legs are rather large. Probably should have noted that sooner. \n \n"
		"\"This,\" Aria starts, gesturing to the black box, \"is my brother's portable safe. He never told me the passcode, \n"
		"but I just really wanted to show off the secret compartment in the table.\" \n \n"
		"While you agree that the secret compartment is cool, you can't help but feel that her wanting to show it off \n"
		"defeats its purpose.",
		true, true, 0, 0, 0, 0, 6, "");
	Object safe("Safe", { "safe" },
		"The safe is a small black box, just large enough to hold comfortably in two hands but not in one. On its face \n"
		"is a screen with a keypad. The screen says \"Username: Supreme297\", and under that there is a line requesting \n"
		"a password. \n \n"
		"\"You know, my brother never did tell me the password.\" Aria states. \"Only he knows what's hiding in there.\" \n \n"
		"...It couldn't hurt to take a guess. What do you enter?",
		false, false, 0, 0);
	Key entrywayKey(10, "Entryway Key", { "entryway key", "entryway", "Entryway key" },
		"A fairly standard key, just a tad larger than most of the others.");
	Door entrywayDoor(make_pair(3, 4), "Entryway Door", { "entryway door", "Entryway door" }, true, true, 10,
		"The door to the entryway is of good quality. Certainly not the kind which one would be able to easily bust open... \n"
		"It's a shame it locks from the other side.",
		"The door to the entryway is of good quality. Certainly not the kind which one would be able to easily bust open... \n"
		"It may lock from the other side, but at least it's unlocked now... Never lose that key.");
	auto entrywayDoorPtr = make_shared<Door>(entrywayDoor);
	Room familyRoom(3, "Family Room", {couch, television, computer, entertainmentCenter, miniFridge, table, safe}, {middleDoorPtr, entrywayDoorPtr},
		{mountainDont}, {cableHDMI});

	//Room 4: Entryway
	Room entryway(4, "Entryway", {}, {}, {}, {});

	while (true)
	{
		if (floorNum != 1)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			cout << "Upon reaching the top of the stairs, you find yourself in a hallway. There are some pictures of abstract" << endl;
			cout << "art on the wall, spaced evenly apart throughout the hallway. Between the pictures there are three doors:" << endl;
			cout << "a Left Door, a Middle Door, and a Right Door. Of course, there is also the Bookshelf Passage through" << endl;
			cout << "which you first entered this hallway.";
			dblEndl();
			
			if (floor1FirstTime)
			{
				Skill rapidShank("Rapid Shank", 3, false, false, 0, noDirection, "The man on the left shanks rapidly, one after the next!");
				Skill quickSlash("Quick Slash", 4, false, false, 0, left, "The man on the left slashes from the left!");
				Enemy manOnTheLeft("The Left Man", 12, 12, 10, { "" }, { rapidShank, quickSlash });

				Skill caneTwirl("Cane Twirl", 2, false, false, 0, right, "The man on the right twirls his cane, hitting you in the chin repeatedly!");
				Enemy manOnTheRight("The Right Man", 16, 12, 10, { "" }, { caneTwirl });

				cout << "Additionally, you hear footsteps above you.";
				dblEndl();
				system("pause");
				system("CLS");
				cout << "Suddenly, two holes burst from the ceiling and two men drop through them at the same time.";
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
				cout << "\"Yeah, you should be a good boy and girl and go back to where you belong real quick-like.\"";
				dblEndl();
				cout << "(1) No, I don't think we will" << endl;
				cout << "(2) Yes, that would be appropriate" << endl;

				int input = getDecision(1, 2);

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
					cout << "before the tea becomes lukewarm.\"";
					dblEndl();
					cout << "You and Selena ready yourselves!";
					dblEndl();
					system("pause");
					
					vector<Enemy> enemies = { manOnTheLeft, manOnTheRight };
					fight(players, enemies, inventory.items);
				}
				else
				{
					cout << "Selena follows up: \"Yeah, we're not gonna just- wait, what? You're kidding, right? You're not seriously" << endl;
					cout << "just gonna go back?\"";
					dblEndl();
					cout << "(1) Haha, just kidding!" << endl;
					cout << "(2) Oh yes I am." << endl;

					int input2 = getDecision(1, 2);

					if (input2 == 1)
					{
						cout << "Selena glares at you for a second--the disappointment in your sense of humor exceedingly palpable--and" << endl;
						cout << "then returns her focus to the two men in front of you.";
						dblEndl();
						cout << "The man on the right looks toward you. \"I'm afraid that not even your partner appreciated your \'jest\'." << endl;
						cout << "I cannot say that I am a fan, either, personally, but every man is allowed his... eccentricities.\"";
						dblEndl();
						cout << "The man on the left let out his opinion as well. \"I've heard cuter quips from quails in a quesadilla!" << endl;
						cout << "You're going back in that room\", he pauses as he points his knife straight at you, \"with your fingers" << endl;
						cout << "or without!\" The man leaps at you!";
						dblEndl();
						system("pause");
					}
					else
					{
						cout << "Selena's face transforms into a cross between disappointment and bewilderment. \"Let me get this straight:" << endl;
						cout << "You rescue me from my cell and team up with me to increase our odds of finding our way out of here, but" << endl;
						cout << "then give up at the first sign of trouble?\"";
						dblEndl();
						cout << "\"Yes.\"";
						dblEndl();
						cout << "Selena's expression is simply one of disgust at this point. Suddenly, she sprints at the two men in front of" << endl;
						cout << "you and gives the man on the left a mean right hook! The man on the left recoils from the pain, and Selena" << endl;
						cout << "immediately turns to punch the gentlemanly man as well. She knocks his monocle clean off his face and onto the" << endl;
						cout << "the floor, and the man takes a step back after the hit. As she closes in, the other man reaches around from behind" << endl;
						cout << "her and holds her still. The gentlemanly man watches as she flails her arms toward him while trying to kick the" << endl;
						cout << "man behind her.";
						dblEndl();
						cout << "Selena is now in a position where she cannot reach either of them for a good hit, and the gentlemanly man begins" << endl;
						cout << "walking toward her now that she has been restricted. His eyes are focused entirely on Selena, leaving him wide" << endl;
						cout << "open for a potential surprise attack from her partner!";
						dblEndl();
						system("pause");
						system("CLS");
						cout << "It is a good thing that you are a man of your word.";
						dblEndl();
						cout << "You sit down with your legs crossed and watch as the two men work to subdue your furious partner. She continues" << endl;
						cout << "flailing her arms and legs, but the man restricting her prevents her from getting any good hits on the gentleman." << endl;
						cout << "The gentlemen, now in close, pulls a cloth from his suit and puts it up against her face. After a few seconds," << endl;
						cout << "her limbs begin slowing down before finally ceasing movement.";
						dblEndl();
						cout << "Both men let out a sigh of relief, and then the man on the left sets Selena down gently on the floor. They then" << endl;
						cout << "both wipe the sweat from their brows. Finally, they turn towards you and their eyes go wide. They must have" << endl;
						cout << "forgotten you were here for a moment. After a brief moment of silence, the man on the left speaks up: \"Whattya" << endl;
						cout << "doin' sittin' there like that? Did ya seriously just watch that whole thing and do nothing?\"";
						dblEndl();
						cout << "\"I thought you guys said you were gonna take us back to our rooms. Doesn't sound too bad to me. It comes with" << endl;
						cout << "free food, doesn't it?\"";
						dblEndl();
						cout << "\"Yes\", the gentleman responds as he starts walking toward you. \"I suppose it does.\" Suddenly, the gentlemen is" << endl;
						cout << "right in front of you, and then the cloth covers your face. It's a funny feeling, you were wide awake just a moment" << endl;
						cout << "ago, but now... now you can feel the sweet tug of sleep dropping your eyelids. Right before your last drop of" << endl;
						cout << "consciousness drips out of your head, you swear you hear the men talking. \"We should install new locks on their" << endl;
						cout << "respective doors, with new keys made for only specific personnel to use. They will not escape again.\"";
						dblEndl();
						system("pause");
						gameOver();
					}
				}
				cout << "The man with the knife runs at you and stabs rapidly! You swivel left and right, narrowly" << endl;
				cout << "avoiding each of the possible puncture wounds. \"Ugh!\" The man releases a spurt of frustration" << endl;
				cout << "before going in for a powerful thrust! You slide a foot to the right and, noticing a prime" << endl;
				cout << "opportunity, you punch his elbow. In the opposite of the direction its supposed to go.";
				dblEndl();
				cout << "The man leaps back. \"Aggh!\", he exclaims as he rubs his elbow. He glares at you, his eyes" << endl;
				cout << "aflame with anger.";
				dblEndl();
				cout << "Meanwhile, the gentleman and Selena cross their cane and Fire Iron as if they were both" << endl;
				cout << "swords. They both repeatedly strike at the other, only for a skillful deflect to follow each" << endl;
				cout << "attack. They appear to be at a standstill, but then Selena gets a glint in her eye.";
				dblEndl();
				cout << "Selena quickly changes her grip on the fire iron and hurls it like a javelin at the gentleman's" << endl;
				cout << "head. He jerks to the side, dodging the weapon, but he was not prepared for what was to come." << endl;
				cout << "Selena had already jumped up, and was now parallel to the floor with her knees tucked in." << endl;
				cout << "Selena's legs both burst forward, colliding into the gentleman's stomach. The missile dropkick" << endl;
				cout << "blew the gentleman all the way back until he hit the wall and fell onto the floor.";
				dblEndl();
				system("pause");
				system("CLS");

				cout << "The gentleman worked his way back to standing, although he was clearly in pain. Both of the men were" << endl;
				cout << "now right next to each other, standing side-to-side. \"I must say,\" the gentleman started, \"that" << endl;
				cout << "you do not fight like any lady I have ever seen. You do not care about honour in a battle all that" << endl;
				cout << "much, do you?\"";
				dblEndl();
				cout << "Selena brushed her hair out of her face. \"Nah, I'm much more of a win first, tell stories later kind of gal.\"" << endl;
				cout << "Needless to say, she smirked.";
				dblEndl();
				cout << "\"Yeah, I'd say that both of ya are dirty blighters in a fight\", the other man interjected, still" << endl;
				cout << "rubbing his elbow. \"'Though I almost respect that.\"";
				dblEndl();
				cout << "\"Nonetheless, it would appear we underestimated the both of you. You put up a good fight. We shall" << endl;
				cout << "retreat, but you should heed this warning: A gentleman is at his weakest just before teatime. It will" << endl;
				cout << "not be this easy next time.";
				dblEndl();
				cout << "\"\"Next time?!\"\", you and Selena both exclaim. But by then, it was too late.";
				dblEndl();
				cout << "A rope drops down through each hole in the ceiling, and each man scurries up at a rapid pace. Once they" << endl;
				cout << "reached the next floor, they both looked down through their respective holes. \"Ah, I almost forgot to" << endl;
				cout << "introduce myself! I must apologize for that. My name is Jarvis\", the gentleman proclaimed.";
				dblEndl();
				cout << "\"And my name is Jack\", the other man added. \"And like he said, you won't be so lucky next time.\"";
				dblEndl();
				cout << "\"Oh yeah? Well good luck with that! We're going to climb up those ropes of yours and finish-\" but Jack" << endl;
				cout << "cut the ropes in a flash before Selena could finish. \"...Oh.\"";
				dblEndl();
				system("pause");
				system("CLS");

				cout << "After hearing some footsteps, you both assume that Jack and Jarvis are gone. \"Well, that was something." << endl;
				cout << "Did you encounter anyone else like those two before you found me?\"";
				dblEndl();
				cout << "\"No, you were the first person I met. Closest thing before that was a rat.\"";
				dblEndl();
				cout << "\"Huh. Well, the way that that Jarvis spoke made it sound like there may be more people trying to keep us" << endl;
				cout << "locked up. I know that there is the guy who would bring me food, but maybe there are still more we have yet" << endl;
				cout << "to meet.\"";
				dblEndl();
				cout << "\"Yeah, I guess that's pretty likely. Maybe there'll be other people who wound up here like we did, too." << endl;
				cout << "Nonetheless,\" you say as you turn to Selena, \"there's only one thing left for us to do-\"";
				dblEndl();
				cout << "\"Continue exploring!\" Selena finishes, as she raises her fist in the air, feigning excitement.";
				dblEndl();
				system("pause");
				system("CLS");
				floor1FirstTime = false;
			}
			else
			{
				playerInput = checkInput(roomNum, floorNum, players, inventory, hallway);
				system("pause");
			}
		}
		if (roomNum == 1)
		{
			system("CLS");
			cout << "You find yourself inside a bedroom. Going clockwise starting from the Right Door, there is a Queen Size Bed to" << endl;
			cout << "your left, then a Nightstand against the wall. Next up is a Window with a Desk just to the right of it. Along" << endl;
			cout << "the back wall is a pair of bifold doors, likely concealing a Closet.";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, bedroom);

			if (!foundAria)
			{
				if (!bedroom.objects[0].hasSecret)
				{
					foundAria = true;
					closet.description = "Behind the bifold doors are a bunch of girl's clothes on hangers. Primarily simple dresses \n"
						"and button-up shirts. There are also some skirts and pants folded up neatly along the wall. \n"
						"While there may be no dresser, it is clear the owner of these clothes is rather organized.";
					system("pause");
					system("CLS");

					cout << "\"So, who are you and what were you doing in that closet?\"";
					dblEndl();
					cout << "\"Well, my name is Aria\", the girl stated, still chowing down on the pomegranate, \"and I live here. Really," << endl;
					cout << "I should be asking why YOU two are here in my room.\"";
					dblEndl();
					cout << "You and Selena share a wide-eyed glance before turning back to Aria. \"So wait, this is YOUR room? You live here?\"";
					dblEndl();
					cout << "\"Uh, yeah.\"";
					dblEndl();
					cout << "\"Tell us the way out of here. Now.\" However, before Aria could respond, Selena followed up with a \n";
					cout << "question.";
					dblEndl();
					cout << "\"Why do you have a secret passageway with a prison cell in your house?\"";
					dblEndl();
					cout << "Aria's eyebrows straightened. \"What?\"";
					dblEndl();
					cout << "\"Beneath the bar downstairs there is a secret passageway leading to a cell. That's where I found her\", you \n";
					cout << "clarify as you gesture toward Selena.";
					dblEndl();
					cout << "\"I... I never knew about a secret passage. Honestly, I hardly do anything with the bar anyway. I like the \n";
					cout << "fruity drinks but I'm not particularly a fan of alcohol. \"";
					dblEndl();
					cout << "Selena's face contorts to one of frustration. \"Then why do you have a bar in your house?! Does anyone else live \n";
					cout << "here?\"";
					dblEndl();
					system("pause");
					system("CLS");

					cout << "Aria's eyes retreat from Selena's. \"Well, my brother lived here with me, but... I haven't seen him or heard \n";
					cout << "from him in a week or two.\" Both your face and Selena's form up for the obvious question that comes next, but \n";
					cout << "Aria already knew it was coming. \"I looked around the house for him right when he first disappeared, but I \n";
					cout << "couldn't find him anywhere. Then I heard some strange men talking, and when I peeked around the corner I didn't \n";
					cout << "recognize them.\"";
					dblEndl();
					cout << "\"And you didn't leave? Maybe even call the cops?\"";
					dblEndl();
					cout << "\"I went to the front door, but they have someone stationed there. From what I've been able to tell they must have \n";
					cout << "rotating shifts because someone is always stationed there. As for calling the cops, I tried. But for some reason, \n";
					cout << "I'm not getting any signal anymore.\" She shows both you and Selena her cell phone and, sure enough, the three \n";
					cout << "bars representing cell signal are all empty.";
					dblEndl();
					cout << "\"But you used to have cell signal?\"";
					dblEndl();
					cout << "\"Yes, but right around when my brother disappeared, the cell signal did too. Anyway, ever since those strange \n";
					cout << "men showed up I've mostly been hiding in my room. I went out to check on the front door a couple times early on \n";
					cout << "but, like I said, they've always got someone there so I haven't tried escaping. After a couple days of waiting \n";
					cout << "I made a run into the kitchen and grabbed all the food I could. Since then I've just been hiding in here, but as \n";
					cout << "you seemed to have caught onto, I ran out of food a day or two ago.\"";
					dblEndl();
					cout << "You think back to how barren the kitchen was. Her story so far seems to add up. But- \"If you were hiding in here, \n";
					cout << "then why did you leave the door unlocked?\"";
					dblEndl();
					system("pause");
					system("CLS");

					cout << "Aria sighs. \"The lock on my door is broken so I've been barricading the door with my desk. But, you see, I'm starving. \n";
					cout << "I was going to go to the indoor greenhouse and see if some of the fruits and veggies were ready to eat. So, I pulled \n";
					cout << "my desk away from the door, but then I heard some TALKING outside my door, and I ran for the closet.\"";
					dblEndl();
					cout << "You put two and two together. \"Ah, so what you probably heard was Selena and I encountering those weirdos in the \n";
					cout << "hallway.\"";
					dblEndl();
					cout << "Aria turns her head toward the ceiling, takes a deep breath, and then turns back to facing you and Selena, a \n";
					cout << "fiery determination in her eyes. \"So, obviously you guys are not working with the other people here. I really \n";
					cout << "don't want to starve, and I can't get past those guys at the door by myself. I'm sure you can tell where I'm";
					cout << "going with this.\"";
					dblEndl();
					cout << "You sure can.";
					dblEndl();
					cout << "\"I can help you guys out. I know my house and the neighborhood pretty well. I would be a valuable asset for \n";
					cout << "getting out of here and staying out of here. What do you say?\"";
					dblEndl();
					cout << "You and Selena share a glance and you then hold a finger up to Aria, signifying \"just a moment\". You both \n";
					cout << "turn away from her and whisper next to the door.";
					dblEndl();
					cout << "\"You know, I really empathize with her\", Selena started. \"She's in essentially the same position I was in. ";
					dblEndl();
					cout << "(1) \"Her story seems to add up, but I still think we should exercise caution here.\"" << endl;
					cout << "(2) \"Yeah, having a guide could be real useful. Plus, it'd feel wrong to just leave her here.\"" << endl;
					cout << "(3) \"I don't know about letting her join. What if she's like you?\"" << endl;

					int input = getDecision(1, 3);
					system("CLS");

					if (input == 1)
					{
						cout << "Selena thinks for a moment. \"Yeah, you're right. We can't necessarily trust her. Still, I don't think \n";
						cout << "we should just leave her here. \"";
						dblEndl();
						cout << "\"She could lead us into a trap if we follow her blindly.\"";
						dblEndl();
						cout << "Selena's face contorts into a frown. It doesn't appear to be directed toward you, but more toward the \n";
						cout << "situation itself. This must be her thinking face. \n";
						dblEndl();
						cout << "You decide to offer a solution. \"I'll tell you what: We can have her join us, but we keep a close eye \n";
						cout << "on her for a while until we feel we can really trust her.\"";
						dblEndl();
						cout << "Selena nods in agreement. \"Yeah, I can get behind that idea.\"";
						dblEndl();
					}
					else if (input == 2)
					{
						cout << "\"Yeah, she could be a huge help. Plus, since this is her house, I would imagine she would have the \n";
						cout << "keys for unlocking some of the doors here.\"";
						dblEndl();
						cout << "\"You position your fingers on your chin, striking a ruminating pose. \"It does seem like she could \n";
						cout << "be a huge help. I think we should let her join.\"";
						dblEndl();
						cout << "Selena mimics your pose playfully. \"Mm, yes, I believe we should.\"";
					}
					else
					{
						cout << "\"Then we would be incredibly lucky\", Selena retorted with a big grin on her face.";
						dblEndl();
						cout << "\"Well, I suppose I could use more \'pins\' for my bowling practice\", you say with \n";
						cout << "a self-satisfied smirk upon your face.";
						dblEndl();
						cout << "Selena's grin evaporates, leaving a frown in its stead. \"Really? THAT's why you \n";
						cout << "would have her join us? So you can have better bowling practice the next time we \n";
						cout << "find a coconut?\"";
						dblEndl();
						cout << "\"I still have the first one.\"";
						dblEndl();
						cout << "Selena pauses for a moment to process. She turns her head and mumbles something under \n";
						cout << "her breath. You couldn't hear her clearly, but you could swear you heard something like, \n";
						cout << "\"Maybe having her could take some of the aggro off of me...";
					}
					dblEndl();
					cout << "You both turn toward Aria.";
					dblEndl();
					cout << "(1) \"We'd be happy to have you.\"" << endl;
					cout << "(2) \"Don't slow us down.\"" << endl;
					cout << "(3) \"We only accept Gargoyle Wars 8 haters in this group.\"" << endl;

					input = getDecision(1, 3);
					system("CLS");

					if (input == 1)
					{
						cout << "A smile grows upon Aria's face. \"Thank you! Trust me, it won't be long before you'll \n";
						cout << "be wondering how you ever got anywhere without me!\" She finishes this statement while \n";
						cout << "confidently pointing at you and Selena.";
						dblEndl();
						cout << "\"We'll hold you to that\", you respond as you return both the smile and the pointing \n";
						cout << "gesture. Considering that she lives here, you figure she's probably right.";
						Aria.friendship += 3;
					}
					else if (input == 2)
					{
						cout << "\"You don't have to worry on that front. Like I said, I know this place. If anything \n";
						cout << "I'll help you guys get out of here a lot quicker.";
						dblEndl();
						cout << "You maintain a straight face. \"Alright then. Welcome aboard.\"";
						Aria.friendship += 1;
					}
					else
					{
						cout << "\"Oh, I DESPISE Gargoyle Wars 8. It's just an unneccessary sequel rushed out to make \n";
						cout << "a quick buck. A disgusting black stain on the franchise.\"";
						dblEndl();
						cout << "You can't help but laugh. \"Oh, we couldn't agree more. It's not even just that the \n";
						cout << "previous film had an superbly satisfying conclusion for the franchise, but the fact \n";
						cout << "that they go out of their way to undermine that just so they can repeat Gray's same \n";
						cout << "exact character arc.\"";
						dblEndl();
						cout << "\"RIGHT?! And don't even get me started on how they ruined my girl Helena.\"";
						dblEndl();
						cout << "After a couple minutes of roasting Gargoyle Wars 8, you feel a tap on your shoulder. \n";
						cout << "\"Umm... what's Gargoyle Wars?\" Selena's sincere question forces your brain to pause \n";
						cout << "and register the fact that you now know someone who has never heard of the most popular \n";
						cout << "sci-fi franchise in history. Wow.";
						Aria.friendship += 5;
					}

					dblEndl();
					cout << "\"Oh! Right! I nearly forgot!\" Aria exckaims as she begins digging in her back pocket.\n";
					cout << "\"This is the key to the middle door in the hallway. That's where we'll need to go if \n";
					cout << "we wanna try getting out of here.\"";

					dblEndl();
					cout << "You obtained the Middle Key!";
					players.push_back(Aria);
					inventory.keys.push_back(middleKey);
					dblEndl();
				}
			}
			system("pause");
		}

		if (roomNum == 2)
		{
			system("CLS");
			cout << "The room is bright--very bright. This is because unlike any other room up to this point, it has windows which" << endl;
			cout << "provide a direct line-of-sight to the sun. As you look around the rest of the room, you can't help but notice" << endl;
			cout << "the wide variety of flora present. There are a few rows of white folding tables taking up most of the space" << endl;
			cout << "in the room, each with plants atop them. There is a Tall Plant, a Green Tree, an Apple Tree, a Palm Tree, and" << endl;
			cout << "there are some plants which likely conceal some Buried Veggies as well.";
			dblEndl();

			if (greenhouseFirstTime)
			{
				cout << "That being said... you then notice a small rodent on a table about 6 feet away from you.";
				dblEndl();
				system("pause");
				system("CLS");

				if (players[0].ratlationship > 0)
				{
					cout << "It's not just any rodent; it appears to be the rat which you gave a chicken nugget to earlier. Not any" << endl;
					cout << "later than you recognize it, it turns around and pulls an item out from behind one of the potted plants." << endl;
					cout << "It appears to be a fingerless glove. The rat then runs back behind the potted plant and into a hole in" << endl;
					cout << "the wall only slightly larger than the rat itself. About 10 seconds later, the rat returns with a second" << endl;
					cout << "fingerless glove. It puts the glove on top of the first one, and then nudges them both with its nose.";
					dblEndl();
					cout << "\"Are these for me? Thanks, little buddy.\" As you say this, you pet the top of the rat's head with your" << endl;
					cout << "index finger. You could swear you saw him smile a bit while you were petting him, too.";
					dblEndl();
					cout << "...Selena is horribly confused.";
					dblEndl();
					cout << "You got the Fingerless Gloves!";
					dblEndl();
					inventory.accessories.push_back(fingerlessGlovesPtr);
					players[0].ratlationship++;
					system("pause");
					system("CLS");
				}
				else
				{
					//fight with the rat, followed by opportunity to give it some food to build ratlationship
					Skill jumpSlash("Jump Slash", 5, false, false, 0, high, "The rat leaps into the air and brings its knife down!");
					Skill sweepSlash("Sweep Slash", 3, false, true, 0, low,
						"The rat dashes around your legs from all directions, making rapid cuts all the while");
					Enemy hungryRat("Hungry Rat", 20, 10, 20, {}, { jumpSlash, sweepSlash });
					cout << "You lock eyes with the rodent. You recognize it as the rat you met before. No sooner than you recognize" << endl;
					cout << "it, it leaps at you with a knife! You sidestep the attack, and the rat immediately follows up with a" << endl;
					cout << "sweeping attack at your feet. You dodge by jumping back a couple of feet, then crack your knuckles in" << endl;
					cout << "response. It's time for a fight!";
					dblEndl();
					system("pause");
					system("CLS");

					vector<Enemy> enemies = { hungryRat };
					fight(players, enemies, inventory.items);

					foughtRat2 = true;
					cout << "The rat sits down, its back against a flower pot on the table. It is clearly exhausted from the fight." << endl;
					cout << "It makes a move to get up and retreat through a hole in the wall. What do you do?";
					dblEndl();
					cout << "(1) Let it leave" << endl;
					cout << "(2) Tell it to wait";
					dblEndl();
					int input = getDecision(1, 2);
					system("CLS");

					if (input == 1)
					{
						cout << "The rat hobbles away into the hole in the wall. As it disappears into the shadows, you swear" << endl;
						cout << "you hear what sounds like a stomach grumbling.";
						dblEndl();
						cout << "\"I think he may have just been hungry.\" Selena stated, breaking the silence. \"Still, that's" << endl;
						cout << "an incredibly aggressive way to \'ask\' for food.\"";
						dblEndl();
						cout << "\"No kidding. And that sucker just had some cheese not that long ago!\"";
						dblEndl();
						cout << "\"Wait, what?\" Selena raises an eyebrow as she turns to you. \"You've met that rat before? And you" << endl;
						cout << "recognize that it is that same rat?\"";
						dblEndl();
						cout << "\"He has distinct mannerisms.\" Selena's eyebrow gets closer to Heaven. \"Th-they're obvious once you" << endl;
						cout << "notice them!\" She folds her arms. \"He was just wielding a freaking KNIFE! Have you seen any other" << endl;
						cout << "rats do that kind of crap?!\"";
						dblEndl();
						cout << "Selena puts two fingers to her chin, contemplatively. \"You know what, that's a fair point. What a" << endl;
						cout << "strange creature.\"";
						dblEndl();
						system("pause");
						system("CLS");
					}
					else
					{
						// the rat waits, and the player can either feed the rat or try to attack it
						while (true)
						{
							cout << "The rat stops for a moment after hearing your voice. It slowly turns toward you, with its eyes flicking" << endl;
							cout << "between your face and your hands. It is clearly on the defensive. That being said, it has stopped and is" << endl;
							cout << "waiting to see what you told it to wait for.";
							dblEndl();
							cout << "What do you do?";
							dblEndl();
							cout << "(1) Give the rat some food" << endl;
							cout << "(2) Give him a good sucker punch" << endl;
							cout << "(3) On second thought, do nothing";
							dblEndl();
							int input = getDecision(1, 3);
							system("CLS");

							if (input == 1)
							{
								cout << "You look through your bag of items to see what you would like to give to the hungry rat.";
								dblEndl();
								displayItemsBattle(inventory.items);
								int pickItem = getDecisionEscapable(0, inventory.items.size() - 1);
								if (pickItem != -1)
								{
									cout << "You gave the rat your " << inventory.items[pickItem].getName() << "." << endl;
									cout << "It nibbles through the entire " << inventory.items[pickItem].getName() << " ravenously, finishing it ";
									cout << "in mere seconds.";
									dblEndl();
									inventory.items.erase(inventory.items.begin() + pickItem);
									cout << "The rat's face appears content upon finishing the food you gave him. He looks up at you, a small tear" << endl;
									cout << "forming in his right eye. Perhaps he is grateful that you fed him, and also moved that such an act of" << endl;
									cout << "kindness took place after he had already attacked you.";
									dblEndl();
									cout << "The rat scurries away into a hole in the wall. A few seconds later, it comes back from the hole with" << endl;
									cout << "something in its mouth. It sits up and drops the item near the edge of the table. It seems he wants" << endl;
									cout << "you to have it.";
									dblEndl();
									cout << "You got the Red Armband!" << endl;
									inventory.accessories.push_back(redArmbandPtr);
									players[0].ratlationship++;
									dblEndl();
									cout << "The rat smiles at you, and you smile back. \"Thanks, little buddy.\" You briefly consider petting him" << endl;
									cout << "before remembering that rats are infamous for carrying diseases. Instead, as the rat begins heading back" << endl;
									cout << "you wave goodbye.";
									dblEndl();
									cout << "\"...The heck was that all about?\" Perhaps Selena's surprise was to be expected, all things considered." << endl;
									cout << "You decide to tell her about your previous encounters with the rat, even though you think that not telling" << endl;
									cout << "her would be kinda funny.";
									dblEndl();
									system("pause");
									break;
								}
								system("CLS");
							}
							else if (input == 2)
							{
								cout << "You take a quick step forward and take a swing with your right arm. Your knuckles collide with the rat's" << endl;
								cout << "left cheek, although given the size of the rat the rest of your fist ends up connecting with the rat's" << endl;
								cout << "entire upper half. The rat launches away several feet, hitting the wall. As it gets back up on its paws" << endl;
								cout << "it glares at you with murder in its eyes. At last, it scurries away into a hole in the wall, and all you" << endl;
								cout << "hear is tapping in the walls growing increasingly distant.";
								dblEndl();
								cout << "\"I know he attacked us, but was decking him afterward really necessary?\" Selena questioned. \"He was" << endl;
								cout << "already going to leave.\"";
								dblEndl();
								cout << "\"It's about sending a message. He attacked us, clearly thinking he could win. We need to show him that" << endl;
								cout << "attacking us is not a good idea. He's met me before, so if he is still willing to strike at me like that," << endl;
								cout << "then I must have been too soft on him.\"";
								dblEndl();
								cout << "\"...Okay. You could still try not being underhanded next time.\"";
								dblEndl();
								cout << "\"...Maybe.";
								dblEndl();
								players[0].ratlationship--;
								system("pause");
								break;
							}
							else
							{
								cout << "You wait and simply do nothing. After about twenty seconds of nobody doing anything, the rat turns around" << endl;
								cout << "and retreats into the hole in the wall it was heading toward just before.";
								dblEndl();
								cout << "Selena turns to you with an eyebrow raised. \"What was that? Why'd you tell it to wait if you weren't going" << endl;
								cout << "to do anything?\"";
								dblEndl();
								cout << "\"I don't really know why I did it. Although, you've gotta admit it was pretty neat that the rat listened" << endl;
								cout << "when I told it to wait.\"";
								dblEndl();
								cout << "Selena tilts her head as she looks at you for a second. She lets out a small chuckle. \"Alright, that was" << endl;
								cout << "pretty neat. That is easily the weirdest rat I've ever seen.";
								dblEndl();
								cout << "\"Yeah, that was, like, the third time I've seen him and it's still a little weird to me.\"";
								dblEndl();
								cout << "\"Wait, you've seen that rat before?\"";
								dblEndl();
								cout << "You decide to tell Selena about your prior encounters with the rat. Once you finish up, you both opt to" << endl;
								cout << "return to exploring the room proper.";
								dblEndl();
								system("pause");
								break;
							}
						}
					}
				}
				greenhouseFirstTime = false;
			}
			else
			{
				playerInput = checkInput(roomNum, floorNum, players, inventory, greenhouseRoom);
				system("pause");
			}
		}

		if (roomNum == 3)
		{
			system("CLS");
			if (!familyRoom.objects[6].isVisible)
			{
				cout << "From the Middle Door, there is a small entryway which leads into a large, open room. The room has \n";
				cout << "many amenities which make it appear to be a family room. On the north end of the room is a flat-screen \n";
				cout << "Television atop an Entertainment Center. Naturally, about six feet away from it is a Couch. Along the \n";
				cout << "east wall is a Mini Fridge as well as a desk with a Computer atop it. In the southwest corner of the room \n";
				cout << "is a Table with some chairs at each side. Finally, along the west wall is a door which Aria refers to as \n";
				cout << "the Entryway Door.";
				dblEndl();
			}
			else
			{
				cout << "From the Middle Door, there is a small entryway which leads into a large, open room. The room has \n";
				cout << "many amenities which make it appear to be a family room. On the north end of the room is a flat-screen \n";
				cout << "Television atop an Entertainment Center. Naturally, about six feet away from it is a Couch. Along the \n";
				cout << "east wall is a Mini Fridge as well as a desk with a Computer atop it. In the southwest corner of the room \n";
				cout << "is a Table with some chairs at each side. As Aria showed you, hidden within one of the legs of the Table \n";
				cout << "is a small Safe. Finally, along the west wall is a door which Aria refers to as the Entryway Door.";
				dblEndl();
			}

			playerInput = checkInput(roomNum, floorNum, players, inventory, familyRoom);

			if (playerInput == "check Safe")
			{
				
				cout << "Username: Supreme297" << endl;
				cout << "Password: ";
				getline(cin, passwordAttempt);
				cout << endl;

				if (passwordAttempt == "Supreme297")
				{
					if (!openedSafe)
					{
						system("CLS");
						cout << "You hear a clicking sound as the safe's door opens. You pull the small safe door open and find a key.";
						dblEndl();
						cout << "\"So that's where he put it!\" Aria exclaimed. \"I was wondering where his key to the entryway went.\"";
						dblEndl();
						cout << "\"So this will let us get to the front of the house?\" you ask.";
						dblEndl();
						cout << "\"Yes, which is good, because I misplaced my key since the last time I used it.\"";
						dblEndl();
						cout << "\"Why does the door lock at all, let alone from the side closer to the front of the house?\"";
						dblEndl();
						cout << "Aria shrugs. \"It was that way when we bought the house.\"";
						dblEndl();
						cout << "\"But if someone breaks in they can just lock you into the rest of the house.\"";
						dblEndl();
						cout << "\"...The house was very affordable for its size.\"";
						dblEndl();
						cout << "\"While I'm questioning things here, why does the safe ask for a username? Password, I get, but a" << endl;
						cout << "username?\"";
						dblEndl();
						cout << "\"Well, that's because it has a feature where a different compartment will open up depending on which" << endl;
						cout << "username and password you enter correctly. Plus needing a username is an extra layer of security.\"" << endl;
						cout << "You've gotta admit, that's pretty neat. But, wait a minute-";
						dblEndl();
						cout << "\"Why did your brother make his password the same as his username, then? That defeats the purpose of" << endl;
						cout << "having an extra layer of security. Also, it's just a bad idea.\"";
						dblEndl();
						cout << "\"Look, I don't freaking know. At least it's not 1111.\"";
						dblEndl();
						cout << "You got the Entryway Key!";
						dblEndl();
						inventory.keys.push_back(entrywayKey);
						openedSafe = true;
					}
					else
					{
						cout << "The safe is still enpty from when you looted it last. As it turns out, keys don't respawn.";
						dblEndl();
					}
				}
				else
				{
					cout << "Nothing happens. It must not have been the correct password.";
					dblEndl();
				}
			}
			system("pause");
		}

		if (roomNum == 4)
		{
			system("CLS");
			if (entrywayFirstTime)
			{
				cout << "After walking through the Entryway Door you find yourself in a hallway leading to your right. You walk \n";
				cout << "quietly to the end of the hallway and find a very tall, extraordinarily muscular man leaning against the \n";
				cout << "wall next to the Front Door of the house. You jump back, but he doesn't seem to have noticed you yet.";
				dblEndl();
				cout << "\"\"Holy crap!\"\" Selena and Aria both kept their exclamation quiet, but it needed to be said. The man \n";
				cout << "wore a black t-shirt which was tight against his well-sculpted frame, although not too tight. He wore blue \n";
				cout << "jeans and... some sort of shoes. You never really pay much attention to shoes, but they look alright.";
				dblEndl();
				cout << "Before you stands an intimidating foe. What do you tell your comrades?";
				dblEndl();

				cout << "(1) \"There's 3 of us and only 1 of him. We can take him.\"" << endl;
				cout << "(2) \"We should wait for a bit and watch for an opening.\"" << endl;
				int input = getDecision(1, 2);
				system("CLS");

				if (input == 1)
				{
					//Fight the ripped guard
					Skill backBreaker("Back Breaker", 8, false, false, 0, low, "The Muscular Man lifts his target up and slams their back into his knee!");
					Skill friendlyFire("Friendly Fire", 5, false, true, 10, high, "The Muscular Man lifts you by your arm and swings you at your comrades!");
					Enemy muscularMan("Muscular Man", 1, 20, 40, { "" }, {backBreaker, friendlyFire});

					cout << "Aria looks at you with a worried expression on her face. You turn to Selena and see her fists clenched \n";
					cout << "and a smile. \"Yeah, let's do this!\" You both rush forward, with Aria behind you.";
					dblEndl();
					cout << "As you rush toward the muscular man he turns toward the sound of the footsteps. But not in a quick, \n";
					cout << "startled way. No, he turns slowly--methodically--as if he knew someone would come down that hallway. \n";
					cout << "When you consider that this hallway is the primary throughway to this room it makes sense, but it doesn't \n";
					cout << "make his actions seem less foreboding.";
					dblEndl();
					cout << "\"Trying to escape, huh?\" The ripped guard asks. Likely a formality given the obviousness of your goal here.";
					dblEndl();
					cout << "\"It won't just be \'trying\' a couple minutes from now\", Selena retorts.";
					dblEndl();
					cout << "\"Yeah, we're getting out of here! Even if we have to go through you!\" You follow up.";
					dblEndl();
					cout << "\"I don't know why you guys took over my house, but I'm going to make sure you regret that you ever did!\"";
					dblEndl();
					cout << "The muscular man crosses his massive arms and chuckles. \"Well, alright then. I'm sure you know it's my job \n";
					cout << "to keep people from passing through this door. And I like getting paid. So, if you're gonna fight, then you'd \n";
					cout << "better give me all you got.\"";
					dblEndl();
					system("pause");

					vector<Enemy> enemies = { muscularMan };
					fight(players, enemies, inventory.items);
					
					cout << "The muscular man falls to his knee. \"Heh, not bad. I'm kinda impressed, even if there are three of you.\"";
					dblEndl();
					cout << "You catch your breath. \"Yeah, you shouldn't have picked a fight with us!\"";
					dblEndl();
					cout << "Aria turns to you. \"But weren't we-\"";
					dblEndl();
					cout << "\"You shouldn't have picked a fight with us.\"";
					dblEndl();
					cout << "With that, the muscular man let out a \"Heh\" before falling forward, unconscious.";
					dblEndl();
					system("pause");
					system("CLS");

					cout << "You hear footsteps. They're getting louder. As you turn toward the hallway you entered from you see a \n";
					cout << "staircase just on the other side of its right wall. From that staircase comes a scrawny man, probably \n";
					cout << "about 5 feet and 2 inches tall. He stops abruptly at the bottom of the stairs. His face freezes as he \n";
					cout << "sees you, Selena, and Aria, as well as the unconscious muscular guard. A couple seconds pass.";
					dblEndl();
					cout << "\"That's not your brother, is it?\"";
					dblEndl();
					cout << "Aria shakes her head. \"Nope.\"";
					dblEndl();
					cout << "You take a step forward and crack your knuckles, and that proves to be enough for the small man to panic.";
					dblEndl();
					cout << "\"AH! HuhuhuHUHUHuhuhuhuh-\" The small man's breathing grows fast and erratic as he sprints back up the \n";
					cout << "the stairs on all fours. You hear something metallic hit the floor, and he disappears from sight at the \n";
					cout << "top of the staircase.";
					dblEndl();
					cout << "Selena walks halfway up the staircase to see what dropped. \"Huh. These should come in handy.\" She turns \n";
					cout << "to you and holds up a keychain with a smile.";
					dblEndl();
					//ADD THE KEYS THAT THE SMALL GUARD HAD... PROBABLY TO DOOR AT TOP OF STAIRCASE AND A DOOR ON THE CURRENT FLOOR... NOT DONE!!!

				}
				else
				{
					//Wait, then end up fighting a scrawny guard
					cout << "\"Yeah, that makes sense to me.\" Aria says. You all stay crouched by the wall in the hallway, peeking \n";
					cout << "around the corner at the ripped guard. While nothing is happening he decides to do a quick 50 push-ups, \n";
					cout << "followed by 100 sit-ups. Yes, you counted. Perhaps the most concerning part is that afterward you only  \n";
					cout << "see a single bead of sweat forming on his forehead.";
					dblEndl();
					cout << "Following his workout he stands back up and resumes leaning against the wall. A few minutes later, a small \n";
					cout << "man comes up to the ripped guard.";
					dblEndl();
					cout << "The small man sighs. \"Hahhhh, alright, I'm here to replace you.\"";
					dblEndl();
					cout << "The ripped guard looks at his wristwatch and smiles. \"Nice! Actually got to end my shift on time for once!\"";
					dblEndl();
					cout << "The small man shrugs. \"Yeah, I try. More than I can say for some of the others.\"";
					dblEndl();
					cout << "\"I appreciate you, Little Bro. Hope your shift doesn't suck.\" The ripped guard then walks by the hallway \n";
					cout << "you're hiding in, likely blinded by the excitement of being freshly off the job, and heads upstairs.";
					dblEndl();
					system("pause");
					system("CLS");

					cout << "With the ripped guard gone, you adjust your focus to the small man who replaced him. If you had to guess, \n";
					cout << "he looks to be about 5 feet 2 inches tall. He looks relatively scrawny, with more apparent bone than muscle. \n";
					cout << "All things considered, with the three of you against him, plus the element of surprise, he's uhh...\n";
					cout << "He's pretty screwed.";
					dblEndl();
					cout << "(1) Rush him down \n";
					cout << "(2) Talk to the guy and try to get information \n";
					int input2 = getDecision(1, 2);
					system("CLS");
					
					if (input2 == 1)
					{
						//RUSH THAT FRICKING FRICK DOWN AND BEAT HIM
						Skill elbowJab("Elbow Jab", 5, false, false, 0, right, "The Small Man jabs his bony elbow into his poor target!");
						Skill rapidShinKicks("Rapid Shin Kicks", 3, false, true, 0, low, "The Small Man yells \"I JUST GOT HERE!\" before kicking "
							"each one of you in your shins.");
						Enemy smallMan("Small Man", 30, 26, 10, 10, 15, { "" }, {elbowJab, rapidShinKicks});

						cout << "You charge down the hallway at your maximum speed, backed up by the sound of footsteps behind you. \n";
						cout << "As the small man turns toward the sound of the footsteps, his eyes explode open. \"WH-WHAT THE-\" \n";
						cout << "but his exclamation was cut short by the unification of your fist with his face.";
						dblEndl();
						system("pause");

						vector<Enemy> enemies = { smallMan };
						fight(players, enemies, inventory.items);

						cout << "The small man lets out an \"Oof!\" before falling to the floor unconscious.";
						dblEndl();
						if (foughtRat2)
						{
							cout << "\"Well, that was easy\", Selena comments. She turns toward you. \"Honestly, I think that rat we fought \n";
							cout << "was tougher.\"";
							dblEndl();
							cout << "You think for a moment. The rat might have been easier, but you might as well dunk on the guy while he's \n";
							cout << "here just in case he can hear you while he's out. \"Oh yeah, this guy had nothing on that rat.\"";
							dblEndl();
							cout << "\"...You guys fought a rat?\" Aria looks understandably confused.";
							dblEndl();
							cout << "\"We'll tell you about it later.\" You say as you wave your hand nonchalantly.";
						}
						else
						{
							cout << "\"Well, that was easy\", Selena comments. \"Three against one was hardly fair, though, I suppose.\"";
							dblEndl();
							cout << "\"Don't forget we ambushed him\", you add.";
							dblEndl();
							cout << "\"Heh, yeah, poor guy didn't really stand a chance.\"";
							dblEndl();
						}

						cout << "\"Well, let's see if he has anything we can use\", Aria says as she bends over to start checking the small \n";
						cout << "man's pockets.";
						dblEndl();
						cout << "You hesitate for a moment. \"Doesn't it feel kind of... wrong to loot his pockets?\" Selena asks.";
						dblEndl();
						cout << "Aria turns around toward Selena. \"We just rushed a guy and beat him up and looting his pockets is where \n";
						cout << "you start feeling we're doing something wrong?\"";
						dblEndl();
						cout << "\"Well, I guess\", Selena pauses for a moment, \"I'm used to getting in bouts with people from my time I've spent \n";
						cout << "in fencing classes. Plus, growing up with siblings gets you used to suddenly getting into fights.\"";
						dblEndl();
						cout << "Aria nods knowingly. \"Yeah, siblings can be a real pain. But them you at least would feel bad about beating \n";
						cout << "up. These people made me a prisoner in my own home. I'm not gonna waste my time feeling bad about taking their \n";
						cout << "stuff.\"";
						dblEndl();
						cout << "You and Selena both nod in agreement with Aria, and wait to see what she finds in the small man's pockets.";
						//ADD WHAT THE SMALL MAN HAS IN HIS POCKETS, PROBABLY KEYS TO UPSTAIRS DOOR AND CURRENT FLOOR DOOR... NOT DONE YET!!!!!!

					}
					else
					{
						//Talk to the scrawny guard, give him a chance to not get beat up
						cout << "You walk up to the small guard quietly, your comrades immediately behind you. The guard turns and his eyes \n";
						cout << "go wide. His mouth opens wide and you cover it with your hand.";
						dblEndl();
						cout << "\"No need to yell. All we want is to get out of here. You let us out, and we won't give you any trouble.\"";
						dblEndl();
						cout << "The small man's eyes dart between your hand and your face. After a few trips back and forth, they stay on your \n";
						cout << "face. The small man nods rapidly in understanding.";
						dblEndl();
						cout << "\"I wouldn't try anything if I were you\", warns Aria.";
						dblEndl();
						cout << "You slowly remove your hand from the man's mouth, your intense gaze never leaving his face. He opens his mouth \n";
						cout << "slowly, inhales, and--noticing your intimidating expression--exhales silently.";
						dblEndl();
						cout << "\"Please don't kill me! I-I-I only ever took this gig because I thought getting paid to stand around sounded \n";
						cout << "like a sweet deal! I never wanted to actually have to deal with people!";
						dblEndl();
						cout << "\"...Surely you figured you'd have to deal with someone eventually?\" Selena questioned.";
						dblEndl();
						cout << "\"W-Well, that was always Tomorrow Me's problem!\"";
						dblEndl();
						cout << "What do you say?";
						dblEndl();
						cout << "(1) \"Well, we're just gonna leave, but seeing as this place has had plenty of questionable decisions \n";
						cout << "     regarding locks and keys already, are there any other keys we're gonna need to get out of here?\"";
						dblEndl();
						cout << "(2) \"I guess Yesterday You should've thought that through better!\" *Punch his head* \n";
						int input3 = getDecision(1, 2);
						system("CLS");

						if (input3 == 1)
						{
							//Asked Small Guard about keys
							cout << "\"W-well, uh, if you're just gonna leave, then you just gotta go through the front door there.\" \n";
							cout << "The small man points to the door behind him.";
							dblEndl();
							cout << "It takes just one glance to see a metal bar placed across the front of the door, secured in its place \n";
							cout << "by a padlock. You look back at the small man. \"I'm sure you have the key to it, then?\"";
							dblEndl();
							cout << "\"I, uh, yes, I do, but I REALLY shouldn't be giving it to you because of my job and all, and I uh...\" \n";
							cout << "He pauses for a moment. \"Ugh, this sucks.\" He reaches into his pocket and procures a couple of keys. \n";
							cout << "\"D-do me a favor, will you? If you run into any of my superiors for some reason, could you tell them \n";
							cout << "I put up a fight and the three of you just beat me up?\"";
							dblEndl();
							cout << "As he holds out the keys, you take them. \"Well, hopefully, we shouldn't be seeing any of you guys \n";
							cout << "ever again.\"";
							dblEndl();
							cout << "\"Y-yeah, fair point.\" The small man walks over to the wall and lies down in an awkward way, likely \n";
							cout << "pretending to have been knocked unconscious. After just a moment, he has already entered the realm of \n";
							cout << "sleep. He likely has had plenty of practice while \"working\".";
							dblEndl();
						}
						else
						{
							//Decked Small Guard in the head
							cout << "\"OOF!\" The small man gets knocked back and hits his head on the wall before landing on the floor \n";
							cout << "unconscious. Selena and Aria pause, their eyes widened. They look at the small guard on the floor, and \n";
							cout << "watch as he breathes.";
							dblEndl();
							cout << "\"What was that about?\" Selena asks.";
							dblEndl();
							cout << "\"Didn't like his work ethic.\"";
							dblEndl();
							cout << "\"Huh. Well, I can't say I cared much for him, given what he's doing here.\" Selena shrugs.";
							dblEndl();
							cout << "\"Does he have anything useful on him?\" Aria inquires.";
							dblEndl();
							cout << "You reach into his pockets and find a couple of keys. \"I bet these'll come in handy.\"";
							dblEndl();
						}
					}
				}
			}
			else
			{
				cout << "After walking through the Entryway Door you find yourself in a hallway leading to your right. At the end \n";
				cout << "of the hallway the room widens considerably, with the Front Door to the house immediately in front of you. \n";
				cout << "On both sides of the Front Door are Windows, although the curtains prevent you from seeing outside currently. \n";
				cout << "To the right of the door are several Coat Hangers with coats on them. Further right is a simple Table with \n";
				cout << "foldable legs. To the left of the door is a mat with several pairs of Shoes on it. Further left you see \n";
				cout << "an upward Staircase running parallel to the hallway.";
				dblEndl();

				playerInput = checkInput(roomNum, floorNum, players, inventory, greenhouseRoom);
			}
			system("pause");
		}
	}
}