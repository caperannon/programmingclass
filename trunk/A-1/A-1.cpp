#include <iostream>
using namespace std;

int main()
{
	int num1,num2,num3,averageI;
	float averageD;
	char correct,repeat;
	correct = 'n';
	repeat = 'y';
	while(repeat=='y' || repeat=='Y')
	{
	while(correct=='n' || correct=='N')
	{
		cout << "Please enter your first value..." << endl;
		cin >> num1;
		cout << "Read " << num1 << ". Is that correct? (y/n)" << endl;
		cin >> correct;
	}
	correct = 'n';
	while(correct=='n' || correct=='N')
	{
		cout << "Please enter your second value..." << endl;
		cin >> num2;
		cout << "Read " << num2 << ". Is that correct? (y/n)" << endl;
		cin >> correct;
	}
	correct = 'n';
	while(correct=='n'||correct=='N')
	{
		cout << "Please enter your third value..." << endl;
		cin >> num3;
		cout << "Read " << num3 << ". Is that correct? (y/n)" << endl;
		cin >> correct;
	}
	correct = 'n';
	cout << "Averaging " << num1 << ", " << num2 << " and " << num3 << "..." << endl;
	averageI = (num1 + num2 + num3)/3;
	averageD = (((float)num1) + num2 + num3)/3;
	cout << "The average is " << averageD << endl;
	cout << "Would you like to go again?" << endl;
	cin >> repeat;
	}
	cout << "Exiting..." << endl;
	return 0;
}
