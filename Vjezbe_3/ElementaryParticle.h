#include <iostream>
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
