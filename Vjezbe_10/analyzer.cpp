#include "analyzer.h"
#include <TH1F.h>
#include <TH2F.h>
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
using namespace std;


Analyzer::Analyzer(){

};

void Analyzer::plothisto()
{	
	TCanvas *canvas = new TCanvas("canvas", "error graf",200,10,700,500);
	canvas->SetGrid();

	gStyle->SetOptFit();
	const Int_t n=5;
	double akcel[n]={9.8,21.2,34.5,39.9,48.5};
	double a_gres[n]={1.0,1.9,3.1,3.9,5.1};
	double sile[n]={1,2,3,4,5};
	double s_gres[n]={0,0,0,0,0};
	TGraphErrors *gr = new TGraphErrors(n, sile, akcel, s_gres, a_gres);
	gr->SetTitle("akceleracija/sila");
	gr->SetMarkerColor(5);
	gr->SetMarkerStyle(21);
	gr->GetXaxis()->SetTitle("sila");
	gr->GetYaxis()->SetTitle("akceleracija");
	gr->Draw("AP");
	TF1 *funkcija = new TF1("f1", "x/[0]",0,6);
	funkcija->SetParameter(0,1.);
	funkcija->SetParNames("m");
	gr->Fit(funkcija);
	
	canvas->SaveAs("test.png");

	

};


void Analyzer::hisq()
{	
	TCanvas *canvas = new TCanvas("canvas", "error graf",200,10,700,500);
	canvas->SetGrid();
	
	gStyle->SetOptFit();
	const Int_t n=5;
	double akcel[n]={9.8,21.2,34.5,39.9,48.5};
	double a_gres[n]={1.,1.9,3.1,3.9,5.1};
	double sile[n]={1,2,3,4,5};
	double s_gres[n]={0,0,0,0,0};
	TF1 *hi = new TF1("hi","(9.8-1*x)*(9.8-1*x)/((1.0)*(1.0))+(21.2-2*x)*(21.2-2*x)/((1.9)*(1.9))+(34.5-3*x)*(34.5-3*x)/((3.1)*(3.1))+(39.9-4*x)*(39.9-4*x)/((3.9)*(3.9))+(48.5-5*x)*(48.5-5*x)/((5.1)*(5.1))",9,11.5);
	hi->SetTitle("chi");
	hi->SetParNames("theta");
	hi->GetYaxis()->SetRangeUser(0,12);
	hi->Draw();
//racun




	double ymin = hi->GetMinimum();
	double xmin = hi->GetMinimumX();
	double x1 = hi->GetX(ymin + 1.0, 1.0, hi->GetMinimumX() - 0.0001);
	double x2 = hi->GetX(ymin + 1.0, hi->GetMinimumX() + 0.0001, 15);
	double sigma1 = xmin - x1;
	double sigma2 = x2 - xmin;
	
    	cout << "min= " << xmin << endl;
	cout << "Sigma1= " << sigma1 << endl;
	cout << "Sigma2= " << sigma2 << endl;
	
	double greskaprop=sigma1/(xmin*xmin);
	
	cout << "Sigma_m= " << greskaprop << endl;

//linije	
	

	TLine *l1 = new TLine(xmin,ymin, xmin, 0);
	TLine *l2 = new TLine(xmin-sigma1,0, xmin-sigma1, ymin+1);
	TLine *l3 = new TLine(xmin+sigma2,0, xmin+sigma2, ymin+1);
	TLine *l4 = new TLine(xmin-sigma1, ymin+1, xmin+sigma2, ymin+1);
	l1->Draw();
	l2->Draw("same");
	l3->Draw("same");
	l4->Draw("same");

	canvas->SaveAs("hisq.png");


	
};

















