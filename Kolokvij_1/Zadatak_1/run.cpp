#include "stat.h"
#include <fstream>


int main() {
	//a) pi
	Statistics *picalc = new Statistics();
	picalc->CalculatePi(5000);
	picalc->CalculatePiVol(500);

	//b) norm dist
	Statistics *a_range = new Statistics();
	a_range->NormalDistribution(0,10,0.8,0.7);
	
	Statistics *a1 = new Statistics();
	a1->NormalDistribution(185,178.2,6.4);
	Statistics *a2 = new Statistics();
	a2->NormalDistribution(205,178.2,6.4);
	Statistics *a3 = new Statistics();
	a3->NormalDistribution(185,160.2,7.2);


	Statistics *a_range2 = new Statistics();
	a_range2->NormalDistribution(0.9,2.7);

return 0;
}
