#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
static const int RANDOM_MIN = 0;
static const int RANDOM_MAX = 101;
static int cNum, pNum, randMin, randMax, guesses;
static char pChoice, cont;
static bool done;
void player();
void computer();
void reset();
int main()
{
	reset();
	cout << "Welcome to guess a number!" << endl;
	do
	{
		cout << "\nWho would you like to choose a number?\nComputer - c\nPlayer - p\n" << "Your choice: ";
		cin >> pChoice;
		if((pChoice == 'p') || (pChoice == 'P'))
		{
			reset();
			player();
		}
		else if((pChoice == 'c') || (pChoice == 'C'))
		{
			reset();
			computer();
		}
		else if((pChoice == 'q') || (pChoice == 'Q'))
		{
			done = true;
		}
	}
	while(!done);
	cout << "Exiting..." << endl;
	return 0;
}
void player()
{
	cout << "Please enter your number: ";
	cin >> pNum;
	srand(time(0));
	do
	{
		if(randMax - randMin == 2)
		{
			cNum = randMin + 1;
		}
		else
		{
			do
			{
				cNum = rand() % (randMax - randMin) + randMin + 1;
			}
			while((cNum <= randMin) || (cNum >= randMax));
		}
		guesses ++;
		if(pNum == cNum)
		{
			cout << "The computers guess is: " << cNum << "\nThe computer guessed it in " << guesses << " guesses!" << endl;
		}
		else
		{
			cout << "The computers guess is: " << cNum << "\nWas the computers guess too high or low? (h/l)\n" << "Your choice: ";
			cin >> pChoice;
			if((pChoice == 'h') || (pChoice == 'H'))
			{
				randMax = cNum;
			}
			else if((pChoice == 'l') || (pChoice == 'L'))
			{
				randMin = cNum;
			}
			else if((pChoice == 'q') || (pChoice == 'Q'))
			{
				cNum = pNum;
			}
			else
			{
				cout << "That was not a choice!" << endl;
				guesses --;
			}
		}
	}
	while(cNum != pNum);
	cout << "Would you like to play again? (y/n)\n" << "Your choice: ";
	cin >> cont;
	if((cont == 'n') || (cont == 'N'))
	{
		done = true;
	}
}
void computer()
{
	srand(time(0));
	cNum = (rand() % (randMax - randMin)) + (randMin + 1);
	do
	{
		cout << "Please enter your number: ";
		cin >> pNum;
		guesses ++;
		if(pNum > cNum)
		{
			cout << "Your guess was too high!" << endl;
		}
		else if(pNum < cNum)
		{
			cout << "Your guess was too low!" << endl;
		}
		else if(pNum == cNum)
		{
			cout << "You guessed it in " << guesses << " guesses!" << endl;
		}
	}
	while(pNum != cNum);
	cout << "Would you like to play again? (y/n)\n" << "Your choice: ";
	cin >> cont;
	if((cont == 'n') || (cont == 'N'))
	{
		done = true;
	}
}
void reset()
{
	guesses = 0;
	randMin = RANDOM_MIN;
	randMax = RANDOM_MAX;
}
