#include "analyzer.h"
using namespace std;
int main(){
	Analyzer *a;
	a = new Analyzer();
	//a->plothisto();
	//a->hisq();
	//a->factorial(0);
	//a->binomial(5,0.03,8);
/*
	cout << "r = 0" << endl;
	a->binomial(0,0.03,8);
	cout << "r = N" << endl;
	a->binomial(8,0.03,8);
	cout << "p = 0" << endl;
	a->binomial(2,0,8);
	cout << "p = 1" << endl;
	a->binomial(3,1,8);
	cout << "max N = 34, za N>34 floating point exception" << endl;
	a->binomial(3,0.5,34);
*/
	//a->binomial(1,0.01,4);
	//a->cp_gornji(1, 4, 0.6827);
	//a->cp_donji(1, 4, 0.6827);
	
	//a->crtanje(10,0.6827);
	
	a->dice(10, 0.6827);
	a->dice(10, 0.9544);
	return 0;
}
