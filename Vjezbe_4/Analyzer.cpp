#include "Analyzer.h"
#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
#include <fstream>
using namespace std;
ElementaryParticle::ElementaryParticle(string s, double m, int b) {
	ime = s;
	mass = m;
	b = b;
	};
ElementaryParticle::ElementaryParticle(){
	ime = "";
	mass = 0;
	b = 0;
	};
void ElementaryParticle::printInfo(){
	cout << ime << "," << mass << ",";
	if (b==1){
		cout<< "bozon."<< endl;
		}
	else
		{
		cout<< "fermion."<< endl;
		}
	};
