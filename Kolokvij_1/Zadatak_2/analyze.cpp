#include "analyzer.h"
int main(){
	analyzer *a;
	a = new analyzer();
	a->PlotHistogram();
	//a->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");
	//a->FillCanvass();
	
	return 0;
}
