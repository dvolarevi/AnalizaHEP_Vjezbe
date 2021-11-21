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

//zadatak 2+3+4
void analyzer::PlotHistogram()
{
	TH1F *hist11 = new TH1F("h11", "pT", 100, 0, 120);
	TH1F *hist12 = new TH1F("h12", "pseudorapiditet", 100, -3, 3);
	TH1F *hist13 = new TH1F("h13", "azimutalni kut", 100, -4, 4);
	TH1F *hist14 = new TH1F("h14", "BDT", 40, 0, 10);

	TH1F *hist21 = new TH1F("h21", "pT", 100, 0, 120);
	TH1F *hist22 = new TH1F("h22", "pseudorapiditet", 100, -3, 3);
	TH1F *hist23 = new TH1F("h23", "azimutalni kut", 100, -4, 4);
	TH1F *hist24 = new TH1F("h24", "BDT", 40, 0, 10);

	TH1F *hist31 = new TH1F("h31", "pT", 100, 0, 120);
	TH1F *hist32 = new TH1F("h32", "pseudorapiditet", 100, -3, 3);
	TH1F *hist33 = new TH1F("h33", "azimutalni kut", 100, -4, 4);
	TH1F *hist34 = new TH1F("h34", "BDT", 40, 0, 10);
	
	TH1F *hist41 = new TH1F("h41", "pT", 100, 0, 120);
	TH1F *hist42 = new TH1F("h42", "pseudorapiditet", 100, -3, 3);
	TH1F *hist43 = new TH1F("h43", "azimutalni kut", 100, -4, 4);
	TH1F *hist44 = new TH1F("h44", "BDT", 40, 0, 10);
	
	
	TH1F *higzov = new TH1F("higzov", "Higgs", 40, 90, 140);

	TLorentzVector *zz1 = new TLorentzVector();
	TLorentzVector *zz2 = new TLorentzVector();
	TLorentzVector *higgy = new TLorentzVector();
	TLorentzVector *cest1 = new TLorentzVector();
	TLorentzVector *cest2 = new TLorentzVector();
	TLorentzVector *cest3 = new TLorentzVector();
	TLorentzVector *cest4 = new TLorentzVector();
	
	
	
	//za dobit bin
	TFile f("/home/public/data/ggH125/ZZ4lAnalysis.root"); 
    TH1F* histoCounter = (TH1F*)f.Get("ZZTree/Counters");
			
	if (fChain == 0) return;

	   Long64_t nentries = fChain->GetEntriesFast();

	   Long64_t nbytes = 0, nb = 0;
	   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	      Long64_t ientry = LoadTree(jentry);
	      if (ientry < 0) break;
	      nb = fChain->GetEntry(jentry);   nbytes += nb;
		  
		float binContent = histoCounter->GetBinContent(40);
		float w = (137.0 * 1000 * xsec * overallEventWeight)/binContent;	

		hist11->Fill(LepPt->at(0),w);
		hist12->Fill(LepEta->at(0),w);
		hist13->Fill(LepPhi->at(0),w);
		hist14->Fill(LepBDT->at(0),w);

		hist21->Fill(LepPt->at(1),w);
		hist22->Fill(LepEta->at(1),w);
		hist23->Fill(LepPhi->at(1),w);
		hist24->Fill(LepBDT->at(1),w);

		hist31->Fill(LepPt->at(2),w);
		hist32->Fill(LepEta->at(2),w);
		hist33->Fill(LepPhi->at(2),w);
		hist34->Fill(LepBDT->at(2),w);

		hist41->Fill(LepPt->at(3),w);
		hist42->Fill(LepEta->at(3),w);
		hist43->Fill(LepPhi->at(3),w);
		hist44->Fill(LepBDT->at(3),w);
		
		cest1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0);
		cest2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0);
		cest3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0);
		cest4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0);
		
		*zz1=*cest1+*cest2;
		*zz2=*cest3+*cest4;
		*higgy=*zz1+*zz2;
		
		higzov->Fill(higgy->M(),w);
		//M() je magnituda
	   }
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(2,2);
	gStyle->SetOptStat(0);
	
	TLegend *leg1 = new TLegend(.7, .75, .89, .89);
	TLegend *leg2 = new TLegend(.7, .75, .89, .89);
	TLegend *leg3 = new TLegend(.7, .75, .89, .89);
	TLegend *leg4 = new TLegend(.7, .75, .89, .89);
	//leg->SetHeader("legenda", "C");
	leg1->AddEntry(hist11,"Lep1","l");
	leg1->AddEntry(hist21,"Lep2","l");
	leg1->AddEntry(hist31,"Lep3","l");
	leg1->AddEntry(hist41,"Lep4","l");
	
	leg2->AddEntry(hist12,"Lep1","l");
	leg2->AddEntry(hist22,"Lep2","l");
	leg2->AddEntry(hist32,"Lep3","l");
	leg2->AddEntry(hist42,"Lep4","l");
	
	leg3->AddEntry(hist13,"Lep1","l");
	leg3->AddEntry(hist23,"Lep2","l");
	leg3->AddEntry(hist33,"Lep3","l");
	leg3->AddEntry(hist43,"Lep4","l");
	
	leg4->AddEntry(hist14,"Lep1","l");
	leg4->AddEntry(hist24,"Lep2","l");
	leg4->AddEntry(hist34,"Lep3","l");
	leg4->AddEntry(hist44,"Lep4","l");
	
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
	hist11->SetLineColor(kRed-4);
	hist21->SetLineColor(kBlue-3);
	hist31->SetLineColor(kYellow-3);
	hist41->SetLineColor(kGreen-6);
	//col hist 2x
	hist12->SetLineColor(kRed-4);
	hist22->SetLineColor(kBlue-3);
	hist32->SetLineColor(kYellow-3);
	hist42->SetLineColor(kGreen-6);
	//col hist 3x
	hist13->SetLineColor(kRed-4);
	hist23->SetLineColor(kBlue-3);
	hist33->SetLineColor(kYellow-3);
	hist43->SetLineColor(kGreen-6);
	//col hist 4x
	hist14->SetLineColor(kRed-4);
	hist24->SetLineColor(kBlue-3);
	hist34->SetLineColor(kYellow-3);
	hist44->SetLineColor(kGreen-6);
	//ost
	canvas->cd(1);
	hist41->Draw("hist");
	hist21->Draw("hist same");
	hist31->Draw("hist same");
	hist11->Draw("hist same");
	leg1->Draw();
	canvas->cd(2);
	hist12->Draw("hist");
	hist22->Draw("hist same");
	hist32->Draw("histo same");
	hist42->Draw("histo same");
	leg2->Draw();
	canvas->cd(3);
	hist13->Draw("hist");
	hist23->Draw("histo same");
	hist33->Draw("histo same");
	hist43->Draw("histo same");
	leg3->Draw();
	canvas->cd(4);
	hist14->Draw("hist");
	hist24->Draw("histo same");
	hist34->Draw("histo same");
	hist44->Draw("histo same");
	leg4->Draw();
	canvas->SaveAs("stuff2.png");
	
	TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 1400,600);
	gStyle->SetOptStat(0);
	higzov->GetXaxis()->SetTitle("masa GeV");
	higzov->GetYaxis()->SetTitle("broj");
	higzov->SetFillStyle(3020);
	higzov->SetFillColor(kRed-4);
	higzov->Draw("hist");
	
	TLegend *leg1232 = new TLegend(.7, .75, .89, .89);
	leg1232->AddEntry(higzov,"Higgs","l");
	leg1232->Draw();
	
	canvas2->Draw();
	canvas2->SaveAs("higgy.png");


}
/*
void analyzer::PlotHistogram()
{
	TH1F *hist1 = new TH1F("h1", "mass", 100, 90, 140);
	TLorentzVector *cest1, *cest2, *cest3, *cest4, *zz1, *zz2, *higgy;
	TLegend *leg = new TLegend(1,0.7,0.48,0.9);
	leg->SetHeader("legend", "C");
	leg->AddEntry(hist1,"rekonstruirana masa","f");
	
	
	if (fChain == 0) return;

	   Long64_t nentries = fChain->GetEntriesFast();

	   Long64_t nbytes = 0, nb = 0;
	   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	      Long64_t ientry = LoadTree(jentry);
	      if (ientry < 0) break;
	      nb = fChain->GetEntry(jentry);   nbytes += nb;
	    
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
	
	
	


}*/

