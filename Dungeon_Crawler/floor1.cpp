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
				Skill rapidShank("Rapid Shank", 3, false, false, 0, noDirection, "The man on the left shanks rapidly, one after the next!");
				Skill quickSlash("Quick Slash", 4, false, false, 0, left, "The man on the left slashes from the left!");
				Enemy manOnTheLeft("The Left Man", 12, 12, 10, { "" }, { rapidShank, quickSlash });

				Skill caneTwirl("Cane Twirl", 2, false, false, 0, right, "The man on the right twirls his cane, hitting you in the chin repeatedly!");
				Enemy manOnTheRight("The Right Man", 16, 12, 10, { "" }, { caneTwirl });

				cout << "Upon reaching the top of the stairs, you find yourself in a hallway. There are three doors" << endl;
				cout << "spaced apart evenly throughout the hallway: a Left Door, a Middle Door, and a Right Door." << endl;
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
			}
		}
	}
}