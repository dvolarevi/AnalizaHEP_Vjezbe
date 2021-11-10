#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>

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
/*
//zadatak 2
void analyzer::PlotHistogram()
{
	TH1F *hist11 = new TH1F("h11", "pT", 100, 0, 120);
	TH1F *hist12 = new TH1F("h12", "pseudorapiditet", 100, -3, 3);
	TH1F *hist13 = new TH1F("h13", "azimutalni kut", 100, -4, 4);
	TH1F *hist14 = new TH1F("h14", "BDT", 100, 10, 14);

	TH1F *hist21 = new TH1F("h21", "pT", 100, 0, 120);
	TH1F *hist22 = new TH1F("h22", "pseudorapiditet", 100, -3, 3);
	TH1F *hist23 = new TH1F("h23", "azimutalni kut", 100, -4, 4);
	TH1F *hist24 = new TH1F("h24", "BDT", 100, 10, 14);

	TH1F *hist31 = new TH1F("h31", "pT", 100, 0, 120);
	TH1F *hist32 = new TH1F("h32", "pseudorapiditet", 100, -3, 3);
	TH1F *hist33 = new TH1F("h33", "azimutalni kut", 100, -4, 4);
	TH1F *hist34 = new TH1F("h34", "BDT", 100, 10, 14);
	
	TH1F *hist41 = new TH1F("h41", "pT", 100, 0, 120);
	TH1F *hist42 = new TH1F("h42", "pseudorapiditet", 100, -3, 3);
	TH1F *hist43 = new TH1F("h43", "azimutalni kut", 100, -4, 4);
	TH1F *hist44 = new TH1F("h44", "BDT", 100, 10, 14);

	//TLorentzVector *cest1, *cest2, *cest3, *cest4;
	TLegend *leg = new TLegend(1,0.7,0.48,0.9);
	leg->SetHeader("legenda", "C");
	leg->AddEntry(hist11,"Lep1","f");
	leg->AddEntry(hist21,"Lep2","f");
	leg->AddEntry(hist31,"Lep3","f");
	leg->AddEntry(hist41,"Lep4","f");
	if (fChain == 0) return;

	   Long64_t nentries = fChain->GetEntriesFast();

	   Long64_t nbytes = 0, nb = 0;
	   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	      Long64_t ientry = LoadTree(jentry);
	      if (ientry < 0) break;
	      nb = fChain->GetEntry(jentry);   nbytes += nb;
	      // if (Cut(ientry) < 0) continue;
		//cest1 = new TLorentzVector(*LepPt);
		//cest2 = new TLorentzVector(*LepEta);
		//cest3 = new TLorentzVector(*LepPhi);
		//cest4 = new TLorentzVector(*LepBDT);		

		hist11->Fill(GenLep1Pt);
		hist12->Fill(GenLep1Eta);
		hist13->Fill(GenLep1Phi);
		hist14->Fill(GenLep1Id);

		hist21->Fill(GenLep2Pt);
		hist22->Fill(GenLep2Eta);
		hist23->Fill(GenLep2Phi);
		hist24->Fill(GenLep2Id);

		hist31->Fill(GenLep3Pt);
		hist32->Fill(GenLep3Eta);
		hist33->Fill(GenLep3Phi);
		hist34->Fill(GenLep3Id);

		hist41->Fill(GenLep4Pt);
		hist42->Fill(GenLep4Eta);
		hist43->Fill(GenLep4Phi);
		hist44->Fill(GenLep4Id);
		//hist2->Fill(cest2);
	   }
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(2,2);
	gStyle->SetOptStat(0);
	//axis histos
	hist41->GetXaxis()->SetTitle("pT");
	hist41->GetYaxis()->SetTitle("broj");
	hist42->GetXaxis()->SetTitle("pseudorapiditet");
	hist42->GetYaxis()->SetTitle("broj");
	hist43->GetXaxis()->SetTitle("azimutalni kut");
	hist43->GetYaxis()->SetTitle("broj");
	hist44->GetXaxis()->SetTitle("BDT");
	hist44->GetYaxis()->SetTitle("broj");
	//col hist 1x
	hist11->SetFillStyle(3020);
	hist11->SetFillColor(kRed-4);
	hist21->SetFillStyle(3001);
	hist21->SetFillColor(kBlue-3);
	hist31->SetFillStyle(3005);
	hist31->SetFillColor(kYellow-3);
	hist41->SetFillStyle(3007);
	hist41->SetFillColor(kGreen-6);
	//col hist 2x
	hist12->SetFillStyle(3020);
	hist12->SetFillColor(kRed-4);
	hist22->SetFillStyle(3001);
	hist22->SetFillColor(kBlue-3);
	hist32->SetFillStyle(3005);
	hist32->SetFillColor(kYellow-3);
	hist42->SetFillStyle(3007);
	hist42->SetFillColor(kGreen-6);
	//col hist 3x
	hist13->SetFillStyle(3020);
	hist13->SetFillColor(kRed-4);
	hist23->SetFillStyle(3001);
	hist23->SetFillColor(kBlue-3);
	hist33->SetFillStyle(3005);
	hist33->SetFillColor(kYellow-3);
	hist43->SetFillStyle(3007);
	hist43->SetFillColor(kGreen-6);
	//col hist 4x
	hist14->SetFillStyle(3020);
	hist14->SetFillColor(kRed-4);
	hist24->SetFillStyle(3001);
	hist24->SetFillColor(kBlue-3);
	hist34->SetFillStyle(3005);
	hist34->SetFillColor(kYellow-3);
	hist44->SetFillStyle(3007);
	hist44->SetFillColor(kGreen-6);
	//ost
	canvas->cd(1);
	hist41->Draw();
	hist21->Draw("SAME");
	hist31->Draw("SAME");
	hist11->Draw("SAME");
	canvas->cd(2);
	hist12->Draw();
	hist22->Draw("SAME");
	hist32->Draw("SAME");
	hist42->Draw("SAME");
	canvas->cd(3);
	hist13->Draw();
	hist23->Draw("SAME");
	hist33->Draw("SAME");
	hist43->Draw("SAME");
	canvas->cd(4);
	hist14->Draw();
	hist24->Draw("SAME");
	hist34->Draw("SAME");
	hist44->Draw("SAME");
	leg->Draw();
	canvas->SaveAs("stuff2.png");
	
	
	


}*/
void analyzer::PlotHistogram()
{
	TH1F *hist1 = new TH1F("h1", "mass", 100, 90, 140);
	//TH1F *hist2 = new TH1F("h2", "pT", 100, 0, 120);
	//TH1F *hist3 = new TH1F("h3", "pT", 100, 0, 120);
	TLorentzVector *cest1, *cest2, *cest3, *cest4, *zz1, *zz2, *higgy;
	TLegend *leg = new TLegend(1,0.7,0.48,0.9);
	leg->SetHeader("legend", "C");
	leg->AddEntry(hist1,"rekonstruirana masa","f");
	//leg->AddEntry(hist2,"druga cestica","f");
	//leg->AddEntry(hist3,"rekonstrukcija","f");
	if (fChain == 0) return;

	   Long64_t nentries = fChain->GetEntriesFast();

	   Long64_t nbytes = 0, nb = 0;
	   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	      Long64_t ientry = LoadTree(jentry);
	      if (ientry < 0) break;
	      nb = fChain->GetEntry(jentry);   nbytes += nb;
	      // if (Cut(ientry) < 0) continue;
		zz1 = new TLorentzVector();
		zz2 = new TLorentzVector();
		higgy = new TLorentzVector();
		cest1 = new TLorentzVector();
		cest1->SetPtEtaPhiM(GenLep1Pt, GenLep1Eta, GenLep1Phi, 0.000511);
		cest2 = new TLorentzVector();
		cest2->SetPtEtaPhiM(GenLep2Pt, GenLep2Eta, GenLep2Phi, 0.105658);
		*zz1 = *cest1 + *cest2; 
		cest3 = new TLorentzVector();
		cest3->SetPtEtaPhiM(GenLep3Pt, GenLep3Eta, GenLep3Phi, 0.000511);
		cest4 = new TLorentzVector();
		cest4->SetPtEtaPhiM(GenLep4Pt, GenLep4Eta, GenLep4Phi, 0.105658);
		*zz2 = *cest3 + *cest4; 
		*higgy= *zz1 + *zz2;
		hist1->Fill(higgy->Mag());
		//hist3->Fill(sqrt((p1[0]+p2[0])*(p1[0]+p2[0])+(p1[1]+p2[1])*(p1[1]+p2[1])));
	   }
	TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 1400,600);
	gStyle->SetOptStat(0);
	hist1->GetXaxis()->SetTitle("mass (GeV)");
	hist1->GetYaxis()->SetTitle("broj");
	hist1->SetFillStyle(3003);
	hist1->SetFillColor(kRed-4);

	hist1->Draw();
	canvas2->SaveAs("higs.png");
	
	
	


}

