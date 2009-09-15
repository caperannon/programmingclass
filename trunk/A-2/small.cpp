#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
static const int RANDOM_MIN = 0;
static const int RANDOM_MAX = 101;
static int cNum, pNum, randMin, randMax, guesses;
static char pChoice;
static bool done;
int main()
{
	cout << "Welcome to guess my number!" << endl;
	srand(time(0));
	do {
		done = false;
		guesses = 0;
		pChoice = 1;
		cNum = 0;
		pNum = 1;
		randMin = RANDOM_MIN;
		randMax = RANDOM_MAX;
		cout << "\nWho would you like to choose a number?\nComputer - c\nPlayer - p\nQuit - q\nYour choice: ";
		cin >> pChoice;
		if((pChoice == 'p') || (pChoice == 'P')) {
			do {
				cout << "Please enter your number: ";
				cin >> pNum;
				if((pNum <= randMin) || (pNum >= randMax)) {
					cout << "Please enter a valid number between " << RANDOM_MIN + 1 << " and " << RANDOM_MAX << "." << endl;
				}
			} while((pNum <= RANDOM_MIN) || (pNum >= RANDOM_MAX));
			do {
				if(randMax - randMin == 2) {
					cNum = randMin + 1;
				}
				else {
					do {
						cNum = rand() % (randMax - randMin) + randMin + 1;
					} while((cNum <= randMin) || (cNum >= randMax));
				}
				guesses++;
				if(pNum == cNum) {
					cout << "The computers guess is: " << cNum << "\nThe computer guessed it in " << guesses << " guesses!" << endl;
				}
				else {
					cout << "The computers guess is: " << cNum << "\nWas the computers guess too high or low? (h/l)\n";
					do {
						cout << "Your Choice: ";
						cin >> pChoice;
					} while((pChoice != 'h') && (pChoice != 'H') && (pChoice != 'l') && (pChoice != 'L') && (pChoice != 'q') && (pChoice != 'Q'));
					if((pChoice == 'h') || (pChoice == 'H')) {
						randMax = cNum;
					}
					else if((pChoice == 'l') || (pChoice == 'L')) {
						randMin = cNum;
					}
					else if((pChoice == 'q') || (pChoice == 'Q')) {
						cNum = pNum;
					}
				}
			} while(cNum != pNum);
			cout << "Would you like to play again? (y/n)\n" << "Your choice: ";
			cin >> pChoice;
			if((pChoice == 'n') || (pChoice == 'N')) {
				done = true;
			}
		}
		else if((pChoice == 'c') || (pChoice == 'C')) {
			cNum = (rand() % (randMax - randMin)) + randMin + 1;
			cout << "The computer has chosen a number..." << endl;
			do {
				do {
					cout << "Please enter your number: ";
					cin >> pNum;
				} while((pNum <= RANDOM_MIN) || (pNum >= RANDOM_MAX));
				guesses++;
				if(pNum > cNum) {
					cout << "Your guess was too high!" << endl;
				}
				else if(pNum < cNum) {
					cout << "Your guess was too low!" << endl;
				}
				else if(pNum == cNum) {
					cout << "You guessed it in " << guesses << " guesses!" << endl;
				}
			} while(pNum != cNum);
			cout << "Would you like to play again? (y/n)\n" << "Your choice: ";
			cin >> pChoice;
			if((pChoice == 'n') || (pChoice == 'N')) {
				done = true;
			}
		}
		else if((pChoice == 'q') || (pChoice == 'Q')) {
			done = true;
		}
	} while(!done);
	cout << "Exiting..." << endl;
	return 0;
}
