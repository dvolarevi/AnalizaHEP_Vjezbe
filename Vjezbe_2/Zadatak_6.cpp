#include <iostream>
using namespace std;

class ElementaryParticle {
	public:
		ElementaryParticle(string s, double m, int b){
		ime = s;
		mass = m;
		bozon = b;
		}
/*
	void printInfo(ElementaryParticle E) {
	cout<< E.ime << "," << E.mass << ",";
	if (E.bozon==1){
		cout<< "bozon."<< endl;
		}
	else
		{
		cout<< "fermion."<< endl;
		}
	}
*/
	void printInfo(){
	cout << ime << "," << mass << ",";
	if (bozon==1){
		cout<< "bozon."<< endl;
		}
	else
		{
		cout<< "fermion."<< endl;
		}
	}
	
	private:
	string ime;
	double mass;
	int bozon;
};


int main() {
	/*
	HiggsBozon.ime = "Higgsov Bozon";
	HiggsBozon.mass = 125;
	HiggsBozon.bozon = 1;
	ZBozon.ime = "Z Bozon";
	ZBozon.mass = 91.1876;
	ZBozon.bozon = 1;
	TopKvark.ime = "Top Kvark";
	TopKvark.mass = 176.76;
	TopKvark.bozon = 0;
	*/
	
	ElementaryParticle HiggsBozon("Higgsov Bozon", 125, 1);
	ElementaryParticle TopKvark("Top Kvark", 176.76, 0);
	ElementaryParticle ZBozon("Z Bozon", 91.1876, 1);
	ElementaryParticle *pointer;
	pointer = &ZBozon;
	pointer->printInfo();
	


	
	return 0;

}
