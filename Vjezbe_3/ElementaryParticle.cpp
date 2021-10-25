#include "ElementaryParticle.h"
#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
#include <fstream>
using namespace std;
//#######################
//rng
//#######################
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
Random::Random(double min, double max, int i) {
	srand(time(NULL)+i);
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
	};
double Random::NextFloat(double min, double max, int precision){
	double value;
	value = rand()%(int)pow(10,precision);
	value = min + (value/pow(10,precision))*(max-min);
	return value;
	};
double Random::NextFloat(){
	int precision = 2;
	double value;
	value = rand()%(int)pow(10,precision);
	value = min + (value/pow(10,precision))*(max-min);
	return value;
	};
//#######################
//particle
//#######################
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
double ElementaryParticle::Impuls(double p1, double p2, double p3){
	px = p1;
	py = p2;
	pz = p3;
	E=sqrt(pow(p1,2)+pow(p2,2)+pow(p3,2)+pow(mass,2));
	cout << "\n Energija cestice = " << E << endl;
	};
void ElementaryParticle::RandomImpuls(){
	Random R(-100,100);
	px = R.NextFloat();
	py = R.NextFloat();
	pz = R.NextFloat();
	E=sqrt(pow(p1,2)+pow(p2,2)+pow(p3,2)+pow(mass,2));
	};
void ElementaryParticle::RandomImpuls(int i){
	Random R(-100,100, i);
	px = R.NextFloat();
	py = R.NextFloat();
	pz = R.NextFloat();
	E=sqrt(pow(p1,2)+pow(p2,2)+pow(p3,2)+pow(mass,2));
	};
void ElementaryParticle::Transversal(){
	pT=sqrt(pow(px,2)+pow(py,2));
	cout << "\n pT = " << pT << endl;
	};
void ElementaryParticle::bosonDecay(ElementaryParticle *c1, ElementaryParticle *c2, int i){
	double r;
	if (bozon!=1){
		cout<< "\n Raspad nije moguc."<< endl;
		}
	else{
		Random R(0,100, i);
		double r = R.NextFloat();
		if(r<=21.4){
			cout<< "W bozon."<< endl;
			c1->ime = "W";
			c1->mass = 80.379;
			c1->bozon = 1;	
			c2->ime = "W";
			c2->mass = 80.379;
			c2->bozon = 1;	
			}
		if(r>21.4 && r<=27.8){
			cout<< "Tau lepton."<< endl;
			c1->ime = "Tau";
			c1->mass = 1.777;
			c1->bozon = 0;
			c2->ime = "Tau";
			c2->mass = 1.777;
			c2->bozon = 0;
			}
		if(r>27.8 && r<=30.4){
			cout<< "Z bozon."<< endl;
			c1->ime = "Z";
			c1->mass = 91.187;
			c1->bozon = 1;
			c2->ime = "Z";
			c2->mass = 91.187;
			c2->bozon = 1;
			}
		if(r>30.4){
			cout<< "b kvark."<< endl;
			c1->ime = "b";
			c1->mass = 4.18;
			c1->bozon = 0;
			c2->ime = "b";
			c2->mass = 4.18;
			c2->bozon = 0;
			}
		Random R2(0,1,i+3);
		r = R2.NextFloat();
		double r2 = 1-r;
		c1->px = r*px;
		c2->px = r2*px;
		cout << "px = " << px << "\n c1.px = " << c1->px << "\n c2.px = " << c2->px << endl;
		r = R2.NextFloat();
		r2 = 1-r;
		c1->py = r*py;
		c2->py = r2*py;
		cout << "py = " << py << "\n c1.py = " << c1->py << "\n c2.py = " << c2->py << endl;
		r = R2.NextFloat();
		r2 = 1-r;
		c1->pz = r*pz;
		c2->pz = r2*pz;
		cout << "pz = " << pz << "\n c1.pz = " << c1->pz << "\n c2.pz = " << c2->pz << endl;
		}
	};
void ElementaryParticle::Ispis(){
	_ime=ime;
	_mass=mass;
	_bozon=bozon;
	p1=px;
	p2=py;
	p3=pz;
	};
//manual input
void ElementaryParticle::MomentumInput(){
	cout << "px = ";
	cin >> p1;
	cout << "py = ";
	cin >> p2;
	cout << "pz = ";
	cin >> p3;
	E=sqrt(pow(p1,2)+pow(p2,2)+pow(p3,2)+pow(mass,2));
	cout << "\n Energija cestice = " << E << endl;
	};
