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
			}
			checkInput(roomNum, floorNum, players, inventory, hallway);
		}
	}
}