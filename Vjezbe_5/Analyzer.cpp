#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>

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
void Analyzer::PlotHistogram()
{
	TH1F *hist1 = new TH1F("h1", "pT", 100, 0, 120);
	TH1F *hist2 = new TH1F("h2", "pT", 100, 0, 120);
	TH1F *hist3 = new TH1F("h3", "pT", 100, 0, 120);
	TLorentzVector *cest1, *cest2, *rek;
	TLegend *leg = new TLegend(1,0.7,0.48,0.9);
	leg->SetHeader("novi naslov", "C");
	leg->AddEntry(hist1,"prva cestica","f");
	leg->AddEntry(hist2,"druga cestica","f");
	leg->AddEntry(hist3,"rekonstrukcija","f");
	if (fChain == 0) return;

	   Long64_t nentries = fChain->GetEntriesFast();

	   Long64_t nbytes = 0, nb = 0;
	   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	      Long64_t ientry = LoadTree(jentry);
	      if (ientry < 0) break;
	      nb = fChain->GetEntry(jentry);   nbytes += nb;
	      // if (Cut(ientry) < 0) continue;
		cest1 = new TLorentzVector(p1[0],p1[1],p1[2],mass);
		cest2 = new TLorentzVector(p2[0],p2[1],p2[2],mass);
		rek = new TLorentzVector();
		*rek = *cest1+*cest2;
		
		hist1->Fill(trans1);
		hist2->Fill(trans2);
		hist3->Fill(rek->Pt());
		//hist3->Fill(sqrt((p1[0]+p2[0])*(p1[0]+p2[0])+(p1[1]+p2[1])*(p1[1]+p2[1])));
	   }
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(2,1);
	gStyle->SetOptStat(0);
	//hist1->GetXaxis()->SetTitle("pT");
	//hist1->GetYaxis()->SetTitle("broj");
	hist2->GetXaxis()->SetTitle("pT");
	hist2->GetYaxis()->SetTitle("broj");
	hist3->GetXaxis()->SetTitle("pT");
	hist3->GetYaxis()->SetTitle("broj");
	hist1->SetFillStyle(3003);
	hist1->SetFillColor(kRed-4);

	hist2->SetFillStyle(3002);
	hist2->SetFillColor(kBlue-3);
	hist3->SetFillStyle(3005);
	hist3->SetFillColor(kYellow-3);
	canvas->cd(1);
	hist2->Draw();
	hist1->Draw("SAME");
	leg->Draw();
	canvas->cd(2);
	hist3->Draw();
	canvas->SaveAs("rekonstrukcija.png");
	
	
	


}
