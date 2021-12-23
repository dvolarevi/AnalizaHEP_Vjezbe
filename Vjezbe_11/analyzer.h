#include <TROOT.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <THStack.h>
#include <TF1.h>

class Analyzer{
	public:
	Analyzer();
	
	int factorial(int n);
	double binomial(int r, double p, int N);
	double cp_gornji(int r, int N, double C);
	double cp_donji(int r, int N, double C);
	void crtanje(int N, double C);
	void dice(int N, double C);
	int a;
};

