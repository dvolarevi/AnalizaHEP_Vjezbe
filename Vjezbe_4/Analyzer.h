#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class ElementaryParticle {
	public:
		ElementaryParticle(string s, double m, int b);
		ElementaryParticle();
		string ime;
		double mass;
		int b;
		double px, py, pz;
		void printInfo();
	/*
		double Impuls(double p1, double p2, double p3);
		void RandomImpuls();
		void RandomImpuls(int i); //ovaj bolje mijenja seed
		void Ispis();
		string _ime;
		double _mass;
		int _bozon;
		void MomentumInput(); //consol input
		void Transversal();
		void bosonDecay(ElementaryParticle *c1, ElementaryParticle *c2, int i);
		void bosonDecay(ElementaryParticle c1, ElementaryParticle c2);
	*/
	private:
		double p0, pT, E;
		//double px, py, pz;
		
};
