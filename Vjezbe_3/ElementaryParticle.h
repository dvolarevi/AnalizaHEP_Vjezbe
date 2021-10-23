#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class ElementaryParticle {
	public:
		ElementaryParticle(string s, double m, int b);
		ElementaryParticle();
		double p1, p2, p3;
		void printInfo();
		double Input(double p1, double p2, double p3);
		//void MomentumInput();
		void Transversal();
		void bosonDecay(ElementaryParticle c1, ElementaryParticle c2);
	
	private:
		string ime;
		double mass;
		int bozon;
		double p0, pT, E;
		double px, py, pz;
		
};


class Random {
	private:
		double min, max;
	public:
		Random(double min, double max);
		Random();
		double NextFloat(double min, double max);
		double NextFloat(double min, double max, int precision);
		double NextFloat();
};
