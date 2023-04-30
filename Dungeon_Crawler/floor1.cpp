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
	bool& greenhouseFirstTime)
{
	//Room 0: Hall of Opportunity
	Door rightDoor(make_pair(0, 1), "Right Door", false,
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is pretty \n"
		"much identical to both of the other doors in the room.");
	auto rightDoorPtr = make_shared<Door>(rightDoor);
	Door leftDoor(make_pair(0, 2), "Left Door", true, true, 1,
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is identical \n"
		"to both of the other doors in the room, except for a green rim around the doorknob. Upon trying the handle, you \n"
		"find that it is locked.",
		"The door is a white door with some rectangular indentations in it, presumably for style's sake. It is identical \n"
		"to both of the other doors in the room, except for a green rim around the doorknob. Since you stuck the Green \n"
		"Key in it, it is now unlocked.");
	auto leftDoorPtr = make_shared<Door>(leftDoor);
	Room hallway(0, "Hallway", {}, {rightDoorPtr, leftDoorPtr}, {}, {});

	//Room 1: Bedroom
	Object closet("Closet", 
		"You put your hand on the knob of the bifold door and try to pull it open, but there is some serious \n"
		"resistance coming from the other side. You stop for a moment, and then try again, harder. However, as you \n"
		"pull harder, the resistance from the other side increases to match. You turn to Selena, and begin whispering. \n"
		"\"It doesn't feel like the door is getting caught on something behind it. I think there's someone IN there.\" \n \n"
		"\"Hey, we know you're in there. Come on out. We won't hurt you... unless you're that thug or that weirdo with the \n"
		"monocle. Then we're gonna hurt you.\" \n \n"
		"Despite Selena's... comforting... words, whoever is behind the closet does not budge. All that you hear is a quiet \n"
		"rumbling from behind the bifold doors and then... silence.",
		true, true, 0, 0, 3,
		"You hold up the pomegranate a couple of feet in front of your face, as if you were observing a work of art. \"Ah,"
		"the pomegranate. Truly God's masterpiece of fruit. Wouldn't you agree, Selena?\" \n \n"
		"\"Most certainly, my good sir. From the beautiful red outer husk to the white inner wall and the crimson seeds within, \n"
		"this fruit is a delight simply for the eyes, to say nothing of the tongue and stomach. To speak of the taste, though-\" \n \n"
		"\"Oh, utterly delectable. The initial wave of tart, followed by a familiar sweetness. I simply don't understand how-\" \n \n"
		"\"I CAN'T TAKE ANYMORE!!!\" A shout pierced through the closet's bifold doors before a girl threw them open and \n"
		"bursted threw the opening. Suddenly, in a flash the pomegranate in your hand disappeared. You turn to find the girl \n"
		"now sitting on the bed, munching on the pomegranate. Success.");
	Object queenBed("Queen Size Bed", 
		"As you press your hand down upon it, you find that the bed is soft--very soft. The violet blanket covering\n"
		"it is well-insulated and comforting to the touch. You simply can't resist. You throw yourself upon the bed,\n"
		"back first. A dumb grin widens across your face as the bed soothes your back. Selena raises an eyebrow, acting\n"
		"as the resident comfortability skeptic, you suppose. However, in order to be a fair judge, she reaches a hand \n"
		"out to the bed and clutches the blanket... Needless to say, she then jumps onto the bed alongside you as a stupid \n"
		"grin finds its way onto her face. \n \n"
		"\"\"Ahhhhh...\"\", you both sigh in relief. A delightful respite.",
		true, false, 0, 0);
	Key greenKey(1, "Green Key", "A standard door key, albeit with a green coloring scheme.");
	Object nightstand("Nightstand", 
		"It appears to be a simple, yet elegant nightstand. The edges are all black, but the rest of the surfaces\n"
		"have a brown marble aesthetic. There is a drawer in the nightstand. While everything else you've done to\n"
		"this point could at worst be described as looting a family room, this feels like it would be a bit too personal. \n \n"
		"Welp, there's a first for everything. \n \n"
		"You open the drawer, and find a Green Key. \"That was easy.\"",
		true, false, 0, 1);
	Object window("Window", 
		"You run to the window, hoping to get a look at the outside for the first time since you woke up. Perhaps if you \n"
		"see what the outside looks like, you can get an idea of where you are and also get some ever-desirable Vitamin D.\n"
		"You make it to the window and find that the outside looks like... a wall. \n \n"
		"In hindsight, you saw from the previous hallway that there was a room directly to the left of this one. Still, \n"
		"the people who constructed this building could've at least put more than an inch between this room and the next \n"
		"if they were going to leave outdoor space between them and make a window. You found this simultaneously bewildering \n"
		"and disappointing. Selena then describes the situation succinctly: \"This window sucks.\"",
		true, false, 0, 0);
	Room bedroom(1, "Bedroom", { closet, queenBed, nightstand, window }, { rightDoorPtr }, {}, {greenKey});

	//Room 2: Greenhouse Room
	Accessory fingerlessGloves("Fingerless Gloves", "A pair of gloves with holes where your fingers go. Not useful for dealing with firewood.",
		0, 0, 2);
	auto fingerlessGlovesPtr = make_shared<Accessory>(fingerlessGloves);
	Accessory redArmband("Red Armband", "An armband with a scarlet hue. Some might call it fashionable.", 2, 2, 0);
	auto redArmbandPtr = make_shared<Accessory>(redArmband);
	Key tomato(2, "Tomato", "A plump, red tomato. Good on sandwiches.");
	Object tallPlant("Tall Plant",
		"The Tall Plant stands straight and green. Notably, it would likely not stand so straight were it not being supported \n"
		"by what looks to be a wireframe. After feeling around the plant's leaves you begin to hypothesize that this is a \n"
		"tomato plant. Your hypothesis is backed up by the several soft red fruit growing on the plant. Might as well take one.",
		true, false, 0, 2);
	Key persimmon(3, "Persimmon", "An orange fruit, similar to a tomato in terms of stature. An old favorite of Selena's.");
	Object greenTree("Green Tree",
		"The tree, though small by tree standards, has a strong trunk with the kind of standard brown bark one would commonly \n"
		"associate with trees. The top of the tree has many green leaves covering it, enough to obscure a significant part of \n"
		"the window behind it from view. You look around its leaves and find something resembling a fruit hiding there. You \n"
		"grab the object, and before you have time to comment on it, you hear Selena from over your shoulder: \"Ooo, a Persimmon! \n"
		"I used to have these with my lunch all the time when I was a kid.\" She then proceeds to reach for a Persimmon from \n"
		"the tree as well and takes a big chomp out of it. \"Mmm. Still good.\"",
		true, false, 0, 3);
	Key apple(4, "Apple", "An iconic red fruit, said to keep those with PhDs away.");
	Object appleTree("Apple Tree",
		"Now this was a tree you could easily recognize at a glance. You would recognize that crisp, red fruit anywhere. You \n"
		"reach up and pluck an Apple from one of the lower branches. It was at this moment that you realized the ceiling of \n"
		"of this room is quite high. All the better for growing the trees and taller plants, you suppose.",
		true, false, 0, 4);
	Key coconut(5, "Coconut", "A big, brown, durable fruit. Not entirely unlike a bowling ball.");
	Object palmTree("Palm Tree",
		"Amongst all of the different plants in the room, this one stands out quite a bit. Its large leaves lend it a visual \n"
		"flavor that is distinct. The fruit it carries likewise have a distinct look to them. They are brown, and similar \n"
		"in shape to a bowling ball. You kick off of the palm tree and manage to snag one of the \"bowling balls\". \n \n"
		"Next, you turn toward Selena, who appears to be investigating a different plant with her back facing you. Big mistake. \n"
		"You then roll the home-grown bowling ball toward Selena's \"pins\", and manage to strike one. \"Ow!\" She lifts her \n"
		"struck leg and grabs the back of her calf, but the other pin still stands. Before you have time to think of securing \n"
		"a spare, she shoots a deadly glare in your direction. You decide that leaving one pin standing doesn't sound so bad.",
		true, false, 0, 5);
	//Green Tree, Apple Tree, Palm Tree, Buried Veggies
	Room greenhouseRoom(2, "Greenhouse Room", {tallPlant, greenTree, appleTree, palmTree}, {leftDoorPtr}, {}, {tomato, persimmon, apple, coconut});

	while (true)
	{
		if (floorNum != 1)
			return;
		if (roomNum == 0)
		{
			system("CLS");
			cout << "Upon reaching the top of the stairs, you find yourself in a hallway. There are some pictures of abstract" << endl;
			cout << "art on the wall, spaced evenly apart throughout the hallway. Between the pictures there are three doors:" << endl;
			cout << "a Left Door, a Middle Door, and a Right Door.";
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
						cout << "Selena glares at you for a second--the disappointment in your sense of humor abundantly palpable--and" << endl;
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
						cout << "her limbs start slowing down before finally ceasing movement.";
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
						cout << "of consciousness drips out of your head, you swear you hear the men talking. \"We should install new locks on their" << endl;
						cout << "respective doors, with new keys made for only specific personnel to use. They will not escape again.\"";
						dblEndl();
						system("pause");
						gameOver();
					}
				}
				cout << "The man with the knife runs at you and stabs rapidly! You swivel left and right, narrowly" << endl;
				cout << "avoiding each of the possible puncture wounds. \"Agh!\" The man releases a spurt of frustration" << endl;
				cout << "before going in for a powerful thrust! You slide a foot to the right and, noticing a prime" << endl;
				cout << "opportunity, you punch his elbow. In the opposite of the direction its supposed to go.";
				dblEndl();
				cout << "The man leaps back. \"Aggh!\", he exclaims as he rubs his elbow. He glares at you, his eyes" << endl;
				cout << "aflame with anger.";
				dblEndl();
				cout << "Meanwhile, the gentleman and Selena cross their cane and Fire Iron as if they were both" << endl;
				cout << "swords. They both repeatedly strike at the other, only for a skillful block to follow each" << endl;
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
				cout << "The gentleman works his way back to standing, although he is clearly in pain. Both of the men are" << endl;
				cout << "right next to each other now, standing side-to-side. \"I must say,\" the gentleman started, \"that" << endl;
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
				checkInput(roomNum, floorNum, players, inventory, hallway);
				system("pause");
			}
		}
		if (roomNum == 1)
		{
			system("CLS");
			cout << "You find yourself inside a bedroom. There is a Queen Size Bed just a few feet to your left. Also, there is" << endl;
			cout << "a pair of bifold doors at the other end of the room, likely concealing a Closet. On the opposite side of the" << endl;
			cout << "bed is a Nightstand, with a reading lamp atop it. Lastly, there is a Window next to the Nightstand.";
			dblEndl();
			cout << "Of course, you mustn't forget about the hallway's Right Door from which you entered the bedroom.";
			dblEndl();
			checkInput(roomNum, floorNum, players, inventory, bedroom);
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
				checkInput(roomNum, floorNum, players, inventory, greenhouseRoom);
				system("pause");
			}
		}
	}
}