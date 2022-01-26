#include "analyzer.h"
using namespace std;
int main(){
	Analyzer *a;
	a = new Analyzer();
	a->teorija();
	a->higsgaus();
	a->pval();

	return 0;
}
