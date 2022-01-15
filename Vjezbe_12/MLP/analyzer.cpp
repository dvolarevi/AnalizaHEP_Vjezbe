#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void analyzer::Loop()
{
	TCanvas *c = new TCanvas("canv","canv",2000,1000);
	c->Divide(4);
	
	TH1F *h_ele_pt = new TH1F("ele_pt","",100,0,100);
	TH1F *h_scl_eta = new TH1F("ele_eta","",100,-5,5);
	TH1F *h_ele_fbrem = new TH1F("ele_fbrem","",100,-2,2);
	TH1F *h_ele_eelepout = new TH1F("ele_eelepout","",100,-1,15);
	
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
	  
	  h_ele_pt->Fill(ele_pt);
	  h_scl_eta->Fill(scl_eta);
	  h_ele_fbrem->Fill(ele_fbrem);
	  h_ele_eelepout->Fill(ele_eelepout);
   }
	//
	c->cd(1);
	h_ele_pt->Draw();
	//
	c->cd(2);
	h_scl_eta->Draw();
   
	//
	c->cd(3);
	h_ele_fbrem->Draw();
   
	//
	c->cd(4);
	h_ele_eelepout->Draw();
   
   c->SaveAs("mlp.png");
}
