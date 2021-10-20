#include "ElementaryParticle.h"

#include <iostream>
#include <math.h>
#include <random>
using namespace std;

ElementaryParticle::ElementaryParticle(string s, double m, int b) {
		ime = s;
		mass = m;
		bozon = b;
		};

ElementaryParticle::ElementaryParticle(){
	ime = "";
	mass = 0;
	bozon = 0;
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
/*
void ElementaryParticle::MomentumInput(){
	cout << "px = ";
	cin >> p1;
	cout << "py = ";
	cin >> p2;
	cout << "pz = ";
	cin >> p3;
	E=sqrt(pow(p1,2)+pow(p2,2)+pow(p3,2)+pow(mass,2));
	cout << "\n Energija cestice = " << E << endl;
	}
*/
double ElementaryParticle::Input(double p1, double p2, double p3){
	px = p1;
	py = p2;
	pz = p3;
	E=sqrt(pow(p1,2)+pow(p2,2)+pow(p3,2)+pow(mass,2));
	cout << "\n Energija cestice = " << E << endl;
	}

void ElementaryParticle::Transversal(){
	pT=sqrt(pow(px,2)+pow(py,2));
	cout << "\n pT = " << pT << endl;
	}

void ElementaryParticle::bosonDecay(ElementaryParticle c1, ElementaryParticle c2){
	double r;
	if (bozon!=1){
		cout<< "\n Raspad nije moguc."<< endl;
		}
	else{

	}
	
	};


