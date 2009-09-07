/*
Author: Michael Robinette
Date: 8/27/09

Description: (A * means it is in the process of being implemented)
	A program that will either guess the players number, or have the player guess a random number from the computer.
	The program will begin by displaying several choices. 
		The first choice is to play a full game in which the player and the computer will sawp picking a number after each correct guess. The first person to pick a number is random.
		The second choice will be for the player to pick the number.
		The third choice will be for the computer to pick the number.
		The fourth choice will be for the computer to randomly pick one of the first two options.
		There is also a hidden fifth choice that is mainly for debugging and will be removed for the final version.
	After one choice is successfully ran it will ask the user if they want to continue.
		If they do want to continue it will loop back and promt the user for their choice.
		If they do not want it will exit the program.
	There is also a scoring system that keeps track of the total number of guesses each person has made. Only matters in a full game.
		The highest ratio of numbers correct to numbers incorrect is winning.
	Anti-cheating system
		If the computers guess is high but you respond by saying low or if its guess is low and you say high it will automatically add a random number of guesses to your guess counter.
		
NOTES:
	If the rand() is seeded by using srand(time(0)) and ran in a loop several times with no interruptions all randomized numbers will be the same. I believe this is due to the fact that after seeding with time the random number will not change until the time changes down to the second. If you need to run it several times and have the numbers change you have to use rand() without seeding it, however this will cause the randomized numbers to come out in a predictable order and therefore is not random.
 */

/*
iostream - Standard input/output
cstdlib  - Contains the random function
ctime    - Allows the program to read the current time
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

// Sets the default namespace to std
using namespace std;

/*
Declares the following values:
	Constants:
		RAND_MIN 	= The default random minimum.
		RAND_MAX 	= The default random maximum.
		AUTHOR		= The authors name.
		VERSION		= The version number. (Major Changes . Added features . Compile #)
		NUM_CHOICES	= Holds the number of choices to be displayed on the main menu.
		NUM_NOTES	= Holds the number of notes to be displayed on the main menu.
		PROMPT_USR	= To ask the user for their input.
		PROMPT_DIF	= To ask the user for the difficulty level.
		CHOICES		= To contain an array of the choices for the main menu, also conatins the error message at [NUM_CHOICES - 1][1].
		NOTES			= Contains the notes to be displayed on the main menu.
	Integers:
		pNum 			= The number the player inputs as a guess or the number for the computer to guess.
		cNum 			= The number the computer guesses or the number the player must guess.
		rMin 			= Sets the minimum number that will be randomized. NOTE: This number is excluded from the valid number range.
		rMax 			= Sets the maximum number that will be randomized. NOTE: This number is excluded from the valid number range.
		randN 		= A random number
		tries 		= The number of guesses made during one session, is reset after each correct guess.
		times 		= The number of times the random choice is ran, used to make sure the number it chooses is never the same order.
		loop			= A number used to run the determine how many times a loop is run. Used for debug only.
		pRight		= The number of correct guesses for the player.
		pGuesses		= The number of incorrect guesses for the player.
		cRight		= The number of correct guesses for the computer.
		cGuesses		= The number of incorrect guesses for the computer.
		pGuessA 		= The average number of guesses it takes the player to guess correctly.
		cGuessA		= The average number of guesses it takes the computer to guess correctly.
		smartG		= A number that was choosen by finding the middle number.
		difficulty	= The choice for difficulty. 1 for easy, 2 for hard.
	Floats:
	Strings:
	Characters:
		cont 			= The choice the player makes to continue playing or not.
		pChoice 		= The players choice as to wich person picks a number.
		pHL 			= The players responce for the computers guess, h (high) or l (low).
	Booleans:
		done 			= True if the number was correctly guessed to break out of the loop and return to the continue loop, false to keep running the guessing loop.
*/
static const int RANDOM_MIN = 1;
static const int RANDOM_MAX = 100;
static const string AUTHOR = "Michael Robinette";
static const string VERSION = "1.5.9";
static const int NUM_CHOICES = 8;
static const int NUM_NOTES = 2;
static const string PROMPT_USR = "Your choice: ";
static const string PROMPT_DIF = "Difficulty? (NOTE: Hard mode does not use randomizing, but rather chooses a number logically)\n1 - Easy\n2 - Hard\n";
enum fields {NAME, DESCRIPTION, NUM_FIELDS};
static const string CHOICES[NUM_CHOICES][NUM_FIELDS] =
{
	{"Full Game - f\n", "Plays a whole game in which the player and computer swap places after each correct guess. Resets scores.\n\n"},
	{"Player Picks - p\n", "Plays one game in which the player picks a number and the computer guesses it.\n\n"},
	{"Computer Picks - c\n", "Plays one game in which the computer picks a number and the computer guesses it.\n\n"},
	{"Random - r\n", "Randomly chooses a person to pick the first number.\n\n"},
	{"Debug - d\n", "Runs the debugging function. NOT FOR PLAY.\n\n"},
	{"New Game - n\n", "Allows you to reset all values to defaults. Are you sure you want to do this?\n"},
	{"Display Scores - s\n", ""},
	{"Would you like to play again? (y/n)\n", "Im sorry, that was not a choice...\n"}
};
static const string NOTES[NUM_NOTES][1] =
{
	{"THE SCORING SYSTEM ONLY MATTERS IN A FULL GAME\n"},
	{"TO RUN THE PROGRAM AND MEET THE ASSIGNMENTS REQS PLEASE RUN WITH BY CHOOSING P AND EASY DIFFICULTY\n"}
};
static int pNum, cNum, rMin, rMax, randN, tries, times, c, loop, pRight, pGuesses, cRight, cGuesses, pGuessA, cGuessA, smartG, difficulty;
static char cont, pChoice, pHL;
static bool done;

int randomNumber();
int smartGuess();
int randomNumber(int min, int max);
void antiCheat();
void reset(bool all);
void resetUser(bool all);
void updateScores(char person);
void displayScores();
void player();
void computer();
void randomChoose();
void fullGame();
void debug();
bool checkValid(int num);
void newGame();

int main()
{
	cout << "Welcome to Guess my number!\nAuthor: " << AUTHOR << "\nVersion: " << VERSION << endl;
	for(int l = 0; l < NUM_NOTES; l++)
	{
		cout << "NOTE: " << NOTES[l][0];
	}
	cout << endl;
	reset(true);
	do
	{
		cout << "Who do you want to pick the number? (Or q to quit)\n";
		for(int l = 0; l < (NUM_CHOICES - 1); l++)
		{
			cout << CHOICES[l][0];
		}
		cout << "\n" << PROMPT_USR;
		cin >> pChoice;
		switch(pChoice)
		{
			case 'f':
			case 'F':
			{
				cout << endl;
				cout << CHOICES[0][1];
				do
				{
					if((difficulty != 1) && (difficulty != 2))
					{
						cout << PROMPT_DIF << PROMPT_USR;
						cin >> difficulty;
						if((difficulty != 1) && (difficulty != 2))
						{
							cout << CHOICES[NUM_CHOICES - 1][1];
						}
					}
					cout << endl;
				}
				while((difficulty != 1) && (difficulty != 2));
				do
				{
					reset(false);
					fullGame();
				}
				while(!done);
				break;
			}
			case 'p':
			case 'P':
			{
				cout << endl;
				cout << CHOICES[1][1];
				do
				{
					if((difficulty != 1) && (difficulty != 2))
					{
						cout << PROMPT_DIF << PROMPT_USR;
						cin >> difficulty;
						if((difficulty != 1) && (difficulty != 2))
						{
							cout << CHOICES[NUM_CHOICES - 1][1];
						}
					}
					cout << endl;
				}
				while((difficulty != 1) && (difficulty != 2));
				do
				{
					reset(false);
					player();
				}
				while(!done);
				break;
			}
			case 'c':
			case 'C':
			{
				cout << endl;
				cout << CHOICES[2][1];
				do
				{
					if((difficulty != 1) && (difficulty != 2))
					{
						cout << PROMPT_DIF << PROMPT_USR;
						cin >> difficulty;
						if((difficulty != 1) && (difficulty != 2))
						{
							cout << CHOICES[NUM_CHOICES - 1][1];
						}
					}
					cout << endl;
				}
				while((difficulty != 1) && (difficulty != 2));
				do
				{
					reset(false);
					computer();
				}
				while(!done);
				break;
			}
			case 'r':
			case 'R':
			{
				cout << endl;
				cout << CHOICES[3][1];
				do
				{
					if((difficulty != 1) && (difficulty != 2))
					{
						cout << PROMPT_DIF << PROMPT_USR;
						cin >> difficulty;
						if((difficulty != 1) && (difficulty != 2))
						{
							cout << CHOICES[NUM_CHOICES - 1][1];
						}
					}
					cout << endl;
				}
				while((difficulty != 1) && (difficulty != 2));
				do
				{
					reset(false);
					randomChoose();
				}
				while(!done);
				break;
			}
			case 'd':
			case 'D':
			{
				cout << endl;
				cout << CHOICES[4][1];
				debug();
				break;
			}
			case 'q':
			case 'Q':
			{
				done = true;
				cont = 'n';
				break;
			}
			case 'z':
			case 'Z':
			{
				cont = 'y';
				break;
			}
			case 'n':
			case 'N':
			{
				newGame();
				cont = 'y';
				break;
			}
			case 's':
			case 'S':
			{
				displayScores();
				cout << endl;
				cont = 'y';
				break;
			}
			default:
			{
				cout << endl;
				cout << CHOICES[NUM_CHOICES - 1][1];
				done = true;
				cont = 'y';
				break;
			}
		}
	}
	while((cont == 'y') || (cont == 'Y'));
	// Done!
	cout << "Exiting..." << endl;
	return 0;
}

// Will generate a psudo random number seeded with the system time
int randomNumber()
{
	// Seeds rand() with the current time
	srand(time(0)); 																
	randN = 0;
	// If there are more than a difference of 2 between the min and max randomize normally
	if((rMax - rMin) > 2)
	{
		// Keeps generating a number until it is between the min and max
		do
		{
			randN = rand();
			randN = (randN % RANDOM_MAX) + RANDOM_MIN;
		}
		while((randN <= rMin) || (randN >= rMax));
	}
	else if(((rMax - rMin) <= 2) && ((rMax - rMin) > 0))
	{
		// So that if the min is default 1 and max is 2 than returns the min
		if((rMax == (rMin + 1)) && (rMin != 99))
		{
			randN = rMin;
		}
		// Otherwise see if the min is 99 and if max is the default 100 and returns the max
		else if((rMax == (rMin + 1)) && (rMin == 99))
		{
			randN = rMax;
		}
		// Otherwise return the number between them
		else
		{
			randN = rMin + 1;
		}
	}
	else
	{
		cout << "You should not see this... Ever." << endl;
	}
	// If the program is done than it will return the same number it started, otherwise it will return the random number
	if(!done)
	{
		return randN;
	}
	else
	{
		return cNum;
	}
}

// Smart guesses what number to choose
int smartGuess()
{
	if(rMin == (RANDOM_MAX - 1))
		smartG = RANDOM_MAX;
	else
		smartG = (rMax + rMin) / 2;
	return smartG;
}

// Will generate a psudo random number seeded with the system time
// For use in the antiCheat function
int randomNumber(int min, int max)
{
	// Seeds rand() with the current time
	srand(time(0)); 																
	randN = 0;
	// Keeps generating a number until it is between the min and max
	do
	{
		randN = rand();
		randN = (randN % RANDOM_MAX) + RANDOM_MIN;
	}
	while((randN < min) || (randN > max));
	return randN;
}

// Anti-cheating system (IN PROGRESS)
void antiCheat()
{
	cout << "Anti-cheating system activated...\nChanging your scores... Completed!" << endl;
	// Randoms a number between 15 and 30 and adds it to the players number of guesses.
	pGuesses += randomNumber(15,30);
	// Here because if taken out a cheat would count as a guess for the computer even though it guesses the same number.
	tries --;
}

// Resets certain values to their defaults, only used internally
void reset(bool all)
{
	if(all)
	{
		done = false;
		cont = 'n';
		rMin = RANDOM_MIN;
		rMax = RANDOM_MAX;
		pChoice = '1';
		randN = rand();
		tries = 0;
		times = 1;
		pRight = 0;
		pGuesses = 0;
		pGuessA = 0;
		cRight = 0;
		cGuesses = 0;
		cGuessA = 0;
		loop = 0;
		difficulty = 0;
	}
	else
	{
		done = false;
		rMin = RANDOM_MIN;
		rMax = RANDOM_MAX;
		pChoice = '1';
		cNum = 0;
		pNum = 0;
		tries = 0;
	}
}

// For use by the user directly
void resetUser(bool all)
{
	if(all)
	{
		done = false;
		cont = 'n';
		rMin = RANDOM_MIN;
		rMax = RANDOM_MAX;
		pChoice = '1';
		randN = rand();
		tries = 0;
		times = 1;
		pRight = 0;
		pGuesses = 0;
		pGuessA = 0;
		cRight = 0;
		cGuesses = 0;
		cGuessA = 0;
		loop = 10;
		difficulty = 0;
		cout << "All values have been reset!\n\n";
	}
}

// Updates the scores
void updateScores(char person)
{
	if(person == 'p')
	{
		cRight ++;
		cGuesses += tries;
		cGuessA = cGuesses / cRight;
		if((pRight == 0) || (pGuesses == 0))
		{
			pGuessA = pGuesses;
		}
		else
		{
			pGuessA = pGuesses / pRight;
		}
	}
	else if(person == 'c')
	{
		pRight ++;
		pGuesses += tries;
		pGuessA = pGuesses / pRight;
		if((cRight == 0) || (cGuesses == 0))
		{
			cGuessA = cGuesses;
		}
		else
		{
			cGuessA = cGuesses / cRight;
		}
	}
	else
	{
		cout << "If you see this the problem is in the update scores..." << endl;
	}
	displayScores();
}
void displayScores()
{
	cout << "\nThe scores are:\nPlayer: " << pGuessA << " Guess Average\nComputer: " << cGuessA << " Guess Average\n" << endl;
	if((pGuessA < cGuessA) && (pGuessA != 0))
	{
		cout << "Congrats, you are winnning!" << endl;
	}
	else if((cGuessA < pGuessA) && (cGuessA != 0))
	{
		cout << "Sorry, you are loosing!" << endl;
	}
	else if((pGuessA == cGuessA) && (pGuessA != 0))
	{
		cout << "You are tied." << endl;
	}
	else
	{
		cout << "This is a new game." << endl;
	}
}

// Player picks a number
void player()
{
	do
	{
		cout << "Please enter your number (" << RANDOM_MIN << "-" << RANDOM_MAX << ")" << endl;
		cout << PROMPT_USR;
		cin >> pNum;
		cout << endl;
	}
	while(!checkValid(pNum));
	cout << "Computer is guessing...\n\n";
	if(difficulty == 1)
	{
		randN = randomNumber();
		cNum = (randN % RANDOM_MAX) + RANDOM_MIN;
	}
	else
	{
		cNum = smartGuess();
	}
	while(!done)
	{
		tries ++;
		if(cNum == pNum)
		{
			done = true;
			rMax = cNum;
			rMin = cNum;
		}
		else
		{
			cout << "The computer guessed: " << cNum << "\n\n";
			cout << "Was this too high or too low? (h/l)\n" << PROMPT_USR;
			cin >> pHL;
			cout << endl;
		}
		if(((pHL == 'h') || (pHL == 'H')) && (!done)) // Checks user input and the done value
		{
			if(cNum < pNum)
			{
				antiCheat();
			}
			else
			{
				rMax = cNum;
				if(difficulty == 1)
				{
					cNum = randomNumber();
				}
				else
				{
					cNum = smartGuess();
				}
			}
		}
		else if(((pHL == 'l') || (pHL == 'L')) && (!done))
		{
			if(cNum > pNum)
			{
				antiCheat();
			}
			else
			{
				rMin = cNum;
				if(difficulty == 1)
				{
					cNum = randomNumber();
				}
				else
				{
					cNum = smartGuess();
				}
			}
		}
		else if((pHL == 'q') || (pHL == 'Q'))
		{
			done = true;
		}
		else if(!done)
		{
			cout << CHOICES[NUM_CHOICES - 1][1];
		}
	}
	if(done)
	{
		if(cNum == pNum)
		{
			cout << "The computer guessed: " << cNum << endl;
			cout << "The computer correctly guessed your number in " << tries << " tries." << endl;
			updateScores('p');
		}
	}
	cout << CHOICES[NUM_CHOICES - 1][0] << PROMPT_USR;
	cin >> cont;
	if((cont == 'y') || (cont == 'Y'))
	{
		cout << endl;
	}
}

// Computer picks a number
void computer()
{
	cNum = randomNumber();
	cout << "The computer has chosen a number...\n\n";
	while(pNum != cNum)
	{
		cout << "Please enter a number... (0 for a Hint)\nYour guess: ";
		cin >> pNum;
		cout << endl;
		if((checkValid(pNum)) || (pNum == 0))
		{
			if(pNum == 0)
			{
				cout << "The valid range is: " << rMin << "-" << rMax << "\nI would guess " << ((rMin + rMax) / 2) << endl;
				tries --;
			}
			else if(pNum < cNum)
			{
				cout << "Your guess was too low...\n\n";
				rMin = pNum ++;
			}
			else if(pNum > cNum)
			{
				cout << "Your guess was too high...\n\n";
				rMax = pNum --;
			}
			else
			{
				cout << "You got it!!!" << endl;
			}
			tries++;
		}
		else
		{
			cout << CHOICES[NUM_CHOICES - 1][1] << endl;;
		}
	}
	cout << "You guessed the number in " << tries << " tries.\n";
	done = true;
	updateScores('c');
	cout << CHOICES[NUM_CHOICES - 1][0] << PROMPT_USR;
	cin >> cont;
	if((cont == 'y') || (cont == 'Y'))
	{
		cout << endl;
	}
}

// Randomly chooses a person to start
void randomChoose()
{
	times = times + randomNumber();
	done = false;
	for(int loopT = 0; loopT <= times; loopT++)
	{
		randN = randomNumber();
	}
	if(c > (RANDOM_MAX / 2))
	{
		pChoice='p';
	}
	else
	{
		pChoice='c';
	}
	times++;
}

// Runs a full game until the user wants to stop, switching players each time
void fullGame()
{
	if((pGuesses > 0) || (cGuesses > 0))
	{
		reset(true);
		cout << "Resetting scores...\n";
	}
	cout << "Playing a full game on ";
	if(difficulty == 1)
	{
		cout << "easy";
	}
	else
	{
		cout << "hard";
	}
	cout << "... Good luck!" << endl;
	randomChoose();
	do
	{
		if(pChoice == 'p')
		{
			player();
			if((cont == 'y') || (cont == 'Y'))
			{
				reset(false);
				pChoice = 'c';
			}
		}
		else
		{
			computer();
			if((cont == 'y') || (cont == 'Y'))
			{
				reset(false);
				pChoice = 'p';
			}
		}
	}
	while((cont == 'y') || (cont == 'Y'));
	done = true;
}

// Function used to debug
void debug()
{
	cout << "Debug function running..." << endl;
	loop = 1;
	pChoice = 100;
	if(pChoice == 100)
	{
		cout << "The value of pChoice = " << pChoice << endl;
	}
	done = true;
}

// Checks a number to see if it is valid
bool checkValid(int num)
{
	if((num == 1) || (num == 2))
	{
		return true;
	}
	else if((num < rMax + 1) && (num > rMin + 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Allows the user to reset the scores from the main menu
void newGame()
{
	do
	{
		cout << "\n" << CHOICES[5][1];
		cout << PROMPT_USR;
		cin >> pChoice;
		cout << endl;
		switch(pChoice)
		{
			case 'y':
			case 'Y':
			{
				resetUser(true);
				break;
			}
			case 'n':
			case 'N':
			{
				break;
			}
			default:
			{
				cout << CHOICES[NUM_CHOICES - 1][1] << endl;
				pChoice = '1';
				break;
			}
		}
	}
	while(pChoice != '1');
}
