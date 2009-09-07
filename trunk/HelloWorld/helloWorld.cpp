#include <iostream>
using namespace std;

int main()
{
  char x;
  int num,prog;
  num = -40;
  while(num<0)
  {
    cout << "How many times do you want it to say Hello World?" << endl;
    cin >> num;
    for(prog=0; prog<num; prog++)
    {
      cout << "Hello World!!" << endl;
    }
    if(num<0)
      cout << "Try entering a positive number..." << endl;
  }
  cout << "Enter any key to quit..." << endl;
  cin >> x;
  return 0;
}
