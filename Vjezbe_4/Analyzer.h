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
		double p1, p2, p3;
		double px, py, pz;
		void printInfo();
		void Transversal();
		//void Impuls(double p1, double p2, double p3);
		double Impuls(double p1, double p2, double p3);
		void RandomImpuls();
		void RandomImpuls(int i); //ovaj bolje mijenja seed
		void Ispis();
		string _ime;
		double _mass;
		int _bozon;
		void MomentumInput(); //consol input
		void bosonDecay(ElementaryParticle *c1, ElementaryParticle *c2, int i);
		void bosonDecay(ElementaryParticle c1, ElementaryParticle c2);
		double p0, pT, E;
	private:
		//double px, py, pz;
		double temporrary;
};

class Random {
	private:
		double min, max;
	public:
		Random(double min, double max);
		Random(double min, double max, int i); //+seed za bolji loop
		Random();
		double NextFloat(double min, double max);
		double NextFloat(double min, double max, int precision);
		double NextFloat();
};

class Analyzer {
	public:
		Analyzer();
		void convertTxtToRootFile(string path);
};
