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
#include <TRandom3.h>
using namespace std;


Analyzer::Analyzer(){

};


void Analyzer::teorija()
{
	TRandom3 *r3 = new TRandom3();

	TCanvas *c = new TCanvas("canvas", "canvas", 1400,800);

	TH1F *histo = new TH1F("histo","teorija",200, 0, 700);
	histo->GetXaxis()->SetTitle("m_yy");
	histo->GetYaxis()->SetTitle("#");
	
	//TH1F *chisto = new TH1F("chisto","chi^2",250,0,25);
	chisto->GetXaxis()->SetTitle("chi^2");
	chisto->GetYaxis()->SetTitle("#");
	
	TF1 *ekspo = new TF1("ekspo", "[0]*exp(-x/[1])",0.0,300.0);
	ekspo->SetParName(0,"N");
	ekspo->SetParameter(0, 200);
	ekspo->SetParName(1,"zeta");
	ekspo->FixParameter(1, 100);
	
	for (int i=0; i<1000; i++){
		for(int j=0; j<100000; j++){
			histo->Fill(r3->Exp(100));
		}
		for(int m=10; m<695; m=m+5){
			histo->Fit("ekspo", "q", "", m-10, m+10);
			chisto->Fill(ekspo->GetChisquare());
		}
		histo->Reset();
	}
	chisto->Scale(1.0/chisto->Integral());
    chisto->Draw("hist");
	
	c->SaveAs("teorija.png");
	delete c;
	delete histo;
}

//ovaj sam ostavio jer inace ne mogu lijepo nacrtat histogram od 2A
void Analyzer::higsgaus()
{
	TRandom3 *r3 = new TRandom3();
	
	TCanvas *c = new TCanvas("canvas", "canvas", 1400,800);
	
	TH1F *histo = new TH1F("histo","histogaus",200, 0, 700);
	
	TF1 *ekspo = new TF1("ekspo", "[0]*exp(-x/[1])",0.0,300.0);
	ekspo->SetParName(0,"N");
	ekspo->SetParameter(0, 200);
	ekspo->SetParName(1,"zeta");
	ekspo->FixParameter(1, 100);
	
	double m, NH;
		for(int j=10; j<695; j=j+5){
			m=j/1.0;
			NH = pow((m-190),2)+0.02;
			for(int i=0;i<10000;i++){
				if(r3->Rndm()>NH/1000){
					histo->Fill(r3->Gaus(m,0.0236*m));
				}
				else{
					histo->Fill(r3->Exp(100));
				}
			}
			histo->Fit(ekspo,"Q","",m-10,m+10);
			
		}
	histo->Scale(1.0/histo->Integral());
	histo->Draw("hist");
	c->SaveAs("zad2a.png");
	
	
	delete c;
	delete histo;
};


/*
double m, NH;
		for(int j=10; j<695; j=j+5){
			m=j/1.0;
			NH = pow((m-190),2)+0.02;
			//cout << NH/1000 << endl;
			for(int i=0;i<10000;i++){
				if(r3->Rndm()>NH/1000){
					histo->Fill(r3->Gaus(m,0.0236*m));
				}
				else{
					histo->Fill(r3->Exp(100));
				}
			}
			histo->Fit(ekspo,"Q","",m-10,m+10);
*/
void Analyzer::pval()
{
	TRandom3 *r3 = new TRandom3();
	
	TCanvas *c = new TCanvas("canvas", "canvas", 1400,800);
	
	TH1F *histo = new TH1F("histo","histogaus",200, 0, 700);
	/*
	TH1F *chisto = new TH1F("chisto","chi^2",250,0,25);
	chisto->GetXaxis()->SetTitle("chi^2");
	chisto->GetYaxis()->SetTitle("#");
	*/
	TF1 *ekspo = new TF1("ekspo", "[0]*exp(-x/[1])",0.0,300.0);
	ekspo->SetParName(0,"N");
	ekspo->SetParameter(0, 200);
	ekspo->SetParName(1,"zeta");
	ekspo->FixParameter(1, 100);
	
	TGraph *graf = new TGraph();
	graf->SetLineColor(2);
	graf->SetLineWidth(4);
	graf->SetMarkerColor(4);
	graf->SetMarkerSize(1.5);
	graf->SetMarkerStyle(21);
	graf->SetTitle("P-Value");
	graf->GetXaxis()->SetTitle("Masa");
	graf->GetYaxis()->SetTitle("Pval");
	TAxis *axis = graf->GetXaxis();
	axis->SetLimits(10.0,690.0);  
	
	double m, NH;
	int brojac=1;
	
	for(int j=10; j<695; j=j+5){
		m=j/1.0;
		NH = -pow((m-190),2)+0.02;
		for(int i=0;i<10000;i++){
			if(r3->Rndm()<NH){
				histo->Fill(r3->Gaus(m,0.0236*m));
			}
			else{
				histo->Fill(r3->Exp(100));
			}
		}
		histo->Fit(ekspo,"Q","",j-10,j+10);
			
		double chi = ekspo->GetChisquare();
		double p_val=chisto->Integral(chisto->GetXaxis()->FindBin(chi),700)/chisto->Integral();
		//cout<< p_val<<endl;
		graf->SetPoint(brojac,m,p_val);
		brojac++;
		}
	gStyle->SetOptStat(0);
	c->SetLogy();
	graf->Draw("AP");
	TLine *line = new TLine(0,1-0.9973,700,1-0.9973);
	line->Draw();
	c->SaveAs("zad2c.png");
};