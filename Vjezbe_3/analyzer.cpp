#include "ElementaryParticle.h"



int main() {
	ElementaryParticle *pointer;
	pointer = new ElementaryParticle("Higgs", 125.10, 1);
	pointer->printInfo();	
	pointer->Input(1,1,1);
	pointer->Transversal();
	
	ElementaryParticle decayParticle_1 = ElementaryParticle();
	ElementaryParticle decayParticle_2 = ElementaryParticle();
	
	//pointer->bosonDecay(decayParticle_1, decayParticle_2);

	return 0;

}
