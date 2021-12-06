#define analyzer_cxx
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
#include <RooBreitWigner.h>
#include <TF1.h>

void analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analyzer.C
//      root> analyzer t
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

//zadatak 8.1
void analyzer::PlotHistogram(TString putanja)
{
	TTree *tree = 0;
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(putanja);
	if (!f || !f->IsOpen()) {
	   f = new TFile(putanja);
	}
	TDirectory * dir = (TDirectory*)f->Get(putanja+":/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);

	TLorentzVector *zz1 = new TLorentzVector();
	TLorentzVector *zz2 = new TLorentzVector();
	TLorentzVector *higgy = new TLorentzVector();
	TLorentzVector *cest1 = new TLorentzVector();
	TLorentzVector *cest2 = new TLorentzVector();
	TLorentzVector *cest3 = new TLorentzVector();
	TLorentzVector *cest4 = new TLorentzVector();


	

	//za dobit bin
	TFile fajl("/home/public/data/ggH125/ZZ4lAnalysis.root"); 
    	TH1F* histoCounter = (TH1F*)fajl.Get("ZZTree/Counters");
	float binContent = histoCounter->GetBinContent(40);
	//skupljanje
		if (fChain == 0) return;

		   Long64_t nentries = fChain->GetEntriesFast();

		   Long64_t nbytes = 0, nb = 0;
		   for (Long64_t jentry=0; jentry<nentries;jentry++) {
		      Long64_t ientry = LoadTree(jentry);
		      if (ientry < 0) break;
		      nb = fChain->GetEntry(jentry);   nbytes += nb;

		float w = (137.0 * 1000.0 * xsec * overallEventWeight)/binContent;		
		
		
		cest1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.000511);
		cest2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.105658);
		*zz1 = *cest1 + *cest2; 
		cest3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.000511);
		cest4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.105658);
		*zz2 = *cest3 + *cest4; 
		
		*higgy= *zz1 + *zz2;

		if(putanja.Contains("ggH125")){
			histo1->Fill(higgy->M(),w);
			histo3->Fill(higgy->M(),w);
		}
		else{	
			histo2->Fill(higgy->M(), w);
			histo4->Fill(higgy->M(), w);
		}
	}
}
//zad1
void analyzer::FillCanvass()
{
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1000,600);
	canvas->Divide(2);
	
	gStyle->SetOptFit();
	gPad->SetLeftMargin(0.15);
	canvas->cd(1);
	
	zbroj->SetTitle("zbroj");
	zbroj->SetLineColor(kRed-4); 
	zbroj->Draw(); 
	kvadratna->SetLineColor(kYellow-4);
	kvadratna->Draw("same");
	bw->SetLineColor(kBlue-4);
	bw->Draw("same");	
	TLegend* leg1 = new TLegend(0.1,0.2,0.2,0.1);
	leg1->AddEntry(kvadratna,"pozadina","l");
	leg1->AddEntry(bw,"signal","l");
	leg1->AddEntry(zbroj,"zbroj","l");
	leg1->Draw();
	
	
	canvas->cd(2);	
	histo1->SetLineColor(kGreen);
	histo2->SetLineColor(kBlue);
	histo2->Add(histo1);
	
	histo2->Draw("p E1 X0");
	histo2->SetTitle("masa");
	histo2->Fit(zbroj);
	canvas->SaveAs("zad1.png");
	

}
//zad2
void analyzer::Fullpod()
{
	
	TCanvas *canvas1 = new TCanvas("canvas", "canvas", 1000,600);
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	
	mh->SetLineColor(kBlue);
	mh->Draw();

	histo3->SetLineColor(kRed-2);
	histo3->Add(histo4);
	
	histo3->SetTitle("masa");
	histo3->Draw("p E1 X0");
	histo3->Fit(mh);
	
	
	
	canvas1->SaveAs("zad2.png");
	
}