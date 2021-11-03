#include "Analyzer.h"
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
/*
void analyze()
{
	ElementaryParticle *c0, *c1, *c2;
	c0 = new ElementaryParticle();
	c1 = new ElementaryParticle();
	c2 = new ElementaryParticle();
	string iter;
	int b;
	double p0[4];
	double p1[3], p2[3];
	string ime;
	ifstream file("/home/dvolarevic/Vjezbe/Vjezbe_4/ispis.txt");
	
	string tmp;
	if( !file ){
		cerr << "Can't open " << endl;
	}
	while( file >> iter >> ime >> p0[0] >> b >> p0[1] >> p0[2] >> p0[3] >> p1[0] >> p1[1] >> p1[2] >> p2[0] >> p2[1] >> p2[2]){
		c0->ime="Higgs";
		c0->mass=125.10;
		c0->b=1;
		c0->px=p0[1];
		c0->py=p0[2];
		c0->pz=p0[3];
		c1->ime=ime;
		c1->mass=p0[0];
		c1->b=b;
		c1->px=p1[0];
		c1->py=p1[1];
		c1->pz=p1[2];
		c2->ime=ime;
		c2->mass=p0[0];
		c2->b=b;
		c2->px=p2[0];
		c2->py=p2[1];
		c2->pz=p2[2];
		c1->printInfo();
		c1->Transversal();
		hist->Fill(c1->pT);
		
	}
	file.close();
	return 0;
}*/
int main(){
	Analyzer *a;
	a = new Analyzer();
	a->convertTxtToRootFile("/home/dvolarevic/Vjezbe/Vjezbe_4/ispis.txt");
	return 0;
}

