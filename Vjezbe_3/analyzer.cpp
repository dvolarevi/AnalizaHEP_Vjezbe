#include "ElementaryParticle.h"
#include <fstream>


int main() {
/*
//pocetni testing
	ElementaryParticle *pointer;
	pointer = new ElementaryParticle("Higgs", 125.10, 1);
	pointer->printInfo();	
	pointer->Impuls(2,1,1);
	pointer->Transversal();
	
	ElementaryParticle *c1 = new ElementaryParticle();
	ElementaryParticle *c2 = new ElementaryParticle();

	pointer->bosonDecay(c1, c2);
	c1->printInfo();
	c2->printInfo();
*/
	
	ElementaryParticle *c0, *c1, *c2;
	int N=10000;
	ofstream file;
	file.open("ispis.txt");
	file << "#iter.\t ime \t mass \t bozon \t px1 \t py1 \t pz1 \t px2 \t py2 \t pz2" << endl;
	for(int i=0; i<N;i++){
		c0 = new ElementaryParticle("Higgs", 125.10, 1);
		c1 = new ElementaryParticle();
		c2 = new ElementaryParticle();
		c0->RandomImpuls(i);
		c0->bosonDecay(c1,c2,i);
		c1->Ispis();
		c2->Ispis();
		file << i << ". \t"<< c1->_ime << "\t" << c1->_mass << "\t" << c1->_bozon << "\t" << c1->p1 << "\t" << c1->p2 << "\t" << c1->p3 << "\t" << c2->p1 << "\t" << c2->p2 << "\t" << c2->p3 << endl;
 		}
	file.close();
	return 0;

}
