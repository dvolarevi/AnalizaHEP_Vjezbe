#include "analyzer.h"
int main(){
	analyzer *a, *b;
	a = new analyzer();
	a->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
	a->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");
	a->FillCanvass();
	a->Fullpod();
	
	return 0;
}
