#include "ElementaryParticle.h"

#include <iostream>
using namespace std;

ElementaryParticle::ElementaryParticle(string s, double m, int b) {
		ime = s;
		mass = m;
		bozon = b;
		};

void ElementaryParticle::printInfo(){
	cout << ime << "," << mass << ",";
	if (bozon==1){
		cout<< "bozon."<< endl;
		}
	else
		{
		cout<< "fermion."<< endl;
		}
	};


