#include "analyzer.h"

using namespace std;

int main(){

	analyzer *a = new analyzer();
	a->Loop();
	a->generacija();
	
	//francuska 164.7+-7.1
	//italija 166.1+-6.5
	//nizozemska 170.3+-7.5
	a->testiranje(164.7,7.1,"francuska");
	a->testiranje(166.1,6.5,"italija");
	a->testiranje(170.3,7.5,"nizozemska");
	
	
return 0;
}
