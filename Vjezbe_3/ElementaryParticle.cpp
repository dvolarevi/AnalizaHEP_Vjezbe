#include "ElementaryParticle.h"

#include <iostream>
#include <math.h>
#include <random>
using namespace std;

Random::Random(){
	srand(time(NULL));
	this->min=min;
	this->max=max;
	};

Random::Random(double min, double max) {
	srand(time(NULL));
	if (max>min){
		this->min=max;
		this->max=min;
	}
	else{
		this->min=min;
		this->max=max;
	}
};

double Random::NextFloat(double min, double max){
	int precision = 2;
	double value;
	value = rand()%(int)pow(10,precision);
	value = min + (value/pow(10,precision))*(max-min);
	return value;
}
double Random::NextFloat(double min, double max, int precision){
	double value;
	value = rand()%(int)pow(10,precision);
	value = min + (value/pow(10,precision))*(max-min);
	return value;
}
double Random::NextFloat(){
	int precision = 2;
	double value;
	value = rand()%(int)pow(10,precision);
	value = min + (value/pow(10,precision))*(max-min);
	return value;
}

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
	};

void ElementaryParticle::Transversal(){
	pT=sqrt(pow(px,2)+pow(py,2));
	cout << "\n pT = " << pT << endl;
	};

void ElementaryParticle::bosonDecay(ElementaryParticle c1, ElementaryParticle c2){
	double r;
	if (bozon!=1){
		cout<< "\n Raspad nije moguc."<< endl;
		}
	else{
		Random R(0,100);
		double r = R.NextFloat();
		if(r<=21.4){
			cout<< "W bozon."<< endl;	
		}
		if(r>21.4 && r<=27.8){
			cout<< "Tau lepton."<< endl;
		}
		if(r>27.8 && r<=30.4){
			cout<< "Z bozon."<< endl;
		}
		if(r>30.4){
			cout<< "b kvark."<< endl;
		}
	}
	
	};
