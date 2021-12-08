#define Analyzer_cxx
#include "analyzer.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <THStack.h>
#include <TF1.h>
#include <iostream>
#include <TPave.h>
using namespace std;

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
void Analyzer::plothisto()
{	
	double sumt, tau_kap;
	double sigma_m, sigma_p;
	double tau_log;
	//zad1
	TH1F *histo1 = new TH1F("histogram 1", "Podaci + Fit", 150, 0, 12);
	TH1F *histo2 = new TH1F("histogram 2", "Podaci + -2lnL", 150, 0, 12);
	TF1 *funkc = new TF1("funkcija", "[1]*(1/[0])*exp(-x/[0]) ",0,12);
	funkc->SetParNames("#tau","C");
	funkc->SetParameters(1,100);
	//zad2
	TF1 *lh1 = new TF1("lh1", "[0]*(1/x)*exp(-1/x)",0,12);
	lh1->SetParNames("N");
	lh1->SetParameters(1,1);


	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	
	sumt+=t;
	histo1->Fill(t);
	histo2->Fill(t);
   }
	//zad3
	tau_kap=sumt/1000;
	//zad4
	TF1 *mhln = new TF1("mhln","2*([0]*log(x)+([1]/x))",1,1.6);
	mhln->SetParNames("N","t_i");
	mhln->SetParameters(1000,sumt);

//racun

	tau_log=mhln->GetMinimumX();
	sigma_m=tau_log-mhln->GetX(mhln->GetMinimum(+1.0,1.0,tau_log-0.01));
	sigma_p=mhln->GetX(mhln->GetMinimum()+1.0,tau_log,10.0)-tau_log;
	

//crtanje

	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	
	canvas->Divide(3);
	gStyle->SetOptFit();
	canvas->cd(1);
	TLegend *leg1 = new TLegend(.7, .15, .89, .25);
	leg1->AddEntry(histo1,"podaci","l");
	leg1->AddEntry(funkc,"teorija","l");

	gPad->SetLeftMargin(0.15);
	histo1->GetXaxis()->SetTitle("vrijeme");
	histo1->GetYaxis()->SetTitle("broj");
	histo1->SetLineColor(kRed-2);
	histo1->Draw("hist");
	histo1->Fit(funkc);
	funkc->SetLineColor(kBlue-2);
	funkc->Draw("same");

	leg1->Draw();

	canvas->cd(2);
	TLegend *leg2 = new TLegend(.6, .1, .89, .25);
	leg2->AddEntry(lh1,"t=1s","l");
	leg2->AddEntry((TObject*)0, "#tau = 1.23506", "");
	lh1->SetLineColor(kGreen);
	lh1->SetTitle("Likelihood t=1s");
	lh1->Draw();
	leg2->Draw();
	cout<<tau_kap<<endl;
	
	canvas->cd(3);
	
	
	gStyle->SetOptFit();
	mhln->SetTitle("-2lnL");
	mhln->SetLineColor(kRed);
	mhln->Draw();
	cout<<mhln->GetMinimumX()<<endl;
	cout<<"greska "<<sigma_m<<endl;
	cout<<"greska "<<sigma_p<<endl;
	canvas->Draw();
	canvas->SaveAs("histo.png");

}
