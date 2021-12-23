#include "analyzer.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TColor.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <THStack.h>
#include <TF1.h>
#include <TLine.h>
#include <iostream>
#include <TPave.h>
#include <cmath>
#include <stdlib.h>
using namespace std;


Analyzer::Analyzer(){

};

//zad1:

double Analyzer::binomial(int r, double p, int N)
{
double biny = (factorial(N)/(factorial(r)*factorial(N-r)))*pow(p,r)*pow((1-p),(N-r));
return biny;

//cout << "binomna = " << bino2 << endl;  
};

int Analyzer::factorial(int n)
{
int fac=1;
if(n>1){
	for(int i=1; i<=n; i++){	
		fac*=i;
	}	
}
//cout << "Factorial of " << n << " = " << fac;  
return fac;  
};


//zad2

double Analyzer::cp_gornji(int r, int N, double C)
{
double p=1.0;
double b_sum=0.0;
double sum=0.0;
//r = r+1;
while(b_sum<(1.0-C)/2.0){
	for(int i=r; i<=N; i++){
		sum+=binomial(i, p, N);
	}
	p-=0.001;
	b_sum=1-sum;
	sum=0.0;
}
//cout<<"gornji \t"<<p<<endl;
return p;
};

double Analyzer::cp_donji(int r, int N, double C)
{
double p=1.0;
double b_sum=1.0;
double sum=0.0;
while(b_sum>(1.0-C)/2.0){
	for(int i=0; i<r; i++){
		sum+=binomial(i, p, N);
	}
	p-=0.001;
	b_sum=1-sum;
	sum=0.0;
}
//cout<<"donji \t"<<p<<endl;
return p;
};

//zad3

void Analyzer::crtanje(int N, double C){
	TCanvas *canvas = new TCanvas("canvas", "error graf",600,400);
	THStack *stakulja = new THStack("staky", "staky;n;p");
	TH1F *gornji= new TH1F("histo1", "histo1",10,0,10);
	TH1F *dornji= new TH1F("histo2", "histo2",10,0,10);
	gornji->SetStats(0);
	dornji->SetStats(0);
	
	for(int i=1;i<=N;i++){
		gornji->SetBinContent(i,cp_gornji(i,N,C));
		dornji->SetBinContent(i,cp_donji(i,N,C));
	}
	//gornji->SetFillColor(kAzure);
	dornji->SetFillColor(kWhite);
	stakulja->Add(gornji);
	stakulja->Add(dornji);
	stakulja->Draw("nostack");
	
	
	canvas->SaveAs("zinger.png");
};


//zad4

void Analyzer::dice(int N, double C){
	srand(time(NULL));
	int broj_pon=1000;
	int i,j;
	int counter=0;
	int faves=0;
	double true_p=1.0/6.0;
	double cpg, cpd;
	for(i=0;i<broj_pon;i++){
		counter=0;
		for(j=0;j<N;j++){
			if((rand()%6+1)==6){
				counter++;
			}
		}
		//cout<<i<<"\t"<<counter<<endl;
		if(counter!=0){
			cpg = cp_gornji(counter,N,C);
			cpd = cp_donji(counter,N,C);
			//cout<<cpd<<"\t"<<cpg<<"\t"<<true_p<<endl;
			if(cpg>=true_p && cpd<=true_p){
				faves++;
			}
		}
	}
	double normalizacija=(double)faves/(double)broj_pon;
	cout << "p unutar cp za N,C ="<<N<<"\t"<<C*100<<"\t" << normalizacija<<"%" << endl;
	
	
};
