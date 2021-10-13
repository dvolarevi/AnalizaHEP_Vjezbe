#include <iostream>
using namespace std;

class ElementaryParticle {
	public:
		ElementaryParticle(string s, double m, int b);
		void printInfo();
	
	private:
		string ime;
		double mass;
		int bozon;
};
