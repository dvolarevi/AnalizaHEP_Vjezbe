#include <iostream>
using namespace std;

double _my_cube(double x) {
	return x*x*x;
}

int main ()
{
  double i;
  cout << "Unesi realan broj: ";
  cin >> i;
  cout << "Uneseni broj je " << i;
  cout << ", njegov kub je " << _my_cube(i) << ".\n";
  return 0;
}


