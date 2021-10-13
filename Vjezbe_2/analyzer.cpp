#include "ElementaryParticle.h"



int main() {
	
	ElementaryParticle *pointer;
	pointer = new ElementaryParticle("Z Bozon", 91.1876, 1);
	pointer->printInfo();
	

	return 0;

}
