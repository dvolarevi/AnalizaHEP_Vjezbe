#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>

void analyzer::Loop(TString filename)
{
	 TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
      f->GetObject(filename,tree);
	
   Init(tree);
   
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
	  
	if(filename=="background"){
		hb_ele_pt->Fill(ele_pt);
		hb_scl_eta->Fill(scl_eta);
		hb_ele_hadronicOverEm->Fill(ele_hadronicOverEm);
		hb_ele_gsfchi2->Fill(ele_gsfchi2);
		hb_ele_fbrem->Fill(ele_fbrem);
		hb_ele_ep->Fill(ele_ep);
		hb_ele_eelepout->Fill(ele_eelepout);
		hb_ele_pfChargedHadIso->Fill(ele_pfChargedHadIso);
	}
	else{
		hs_ele_pt->Fill(ele_pt);
		hs_scl_eta->Fill(scl_eta);
		hs_ele_hadronicOverEm->Fill(ele_hadronicOverEm);
		hs_ele_gsfchi2->Fill(ele_gsfchi2);
		hs_ele_fbrem->Fill(ele_fbrem);
		hs_ele_ep->Fill(ele_ep);
		hs_ele_eelepout->Fill(ele_eelepout);
		hs_ele_pfChargedHadIso->Fill(ele_pfChargedHadIso);
	}
		
   }
}
void analyzer::draw()
{
	TCanvas *c = new TCanvas("canv","canv",2000,1000);
	c->Divide(4,2);
	//
	c->cd(1);
	hb_ele_pt->SetLineColor(kBlue);
	hs_ele_pt->SetLineColor(kRed);
	hb_ele_pt->Draw();
	hs_ele_pt->Draw("same");
	//
	c->cd(2);
	hb_scl_eta->SetLineColor(kBlue);
	hs_scl_eta->SetLineColor(kRed);
	hs_scl_eta->Draw();
	hb_scl_eta->Draw("same");
	//
	c->cd(3);
	hb_ele_hadronicOverEm->SetLineColor(kBlue);
	hs_ele_hadronicOverEm->SetLineColor(kRed);
	hs_ele_hadronicOverEm->Draw();
	hb_ele_hadronicOverEm->Draw("same");
	//
	c->cd(4);
	hb_ele_gsfchi2->SetLineColor(kBlue);
	hs_ele_gsfchi2->SetLineColor(kRed);
	hs_ele_gsfchi2->Draw();
	hb_ele_gsfchi2->Draw("same");
	//
	c->cd(5);
	hb_ele_fbrem->SetLineColor(kBlue);
	hs_ele_fbrem->SetLineColor(kRed);
	hb_ele_fbrem->Draw();
	hs_ele_fbrem->Draw("same");
	c->cd(6);
	hb_ele_ep->SetLineColor(kBlue);
	hs_ele_ep->SetLineColor(kRed);
	hs_ele_ep->Draw();
	hb_ele_ep->Draw("same");
	c->cd(7);
	hb_ele_eelepout->SetLineColor(kBlue);
	hs_ele_eelepout->SetLineColor(kRed);
	hs_ele_eelepout->Draw();
	hb_ele_eelepout->Draw("same");
	c->cd(8);
	hb_ele_pfChargedHadIso->SetLineColor(kBlue);
	hs_ele_pfChargedHadIso->SetLineColor(kRed);
	hs_ele_pfChargedHadIso->Draw();
	hb_ele_pfChargedHadIso->Draw("same");
	
	c->SaveAs("osam.png");
}


void analyzer::MVATraining(TString metoda)
{
	TMVA::Tools::Instance();
	
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
	TTree *signalTree;
	TTree *background; 

	f->GetObject("signal",signalTree);
	Init(signalTree);
   
	f->GetObject("background",background);
	Init(background);

	//output
	TFile* outputFile = TFile::Open("TMVA.root","RECREATE");
	//factory
	// The first argument is the base of the name of all the
	// weightfiles in the directory weight
	// The second argument is the output file for the training results
	// All TMVA output can be suppressed by removing the "!" (not) in
	// front of the "Silent" argument in the option string
	TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");
	
	TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
	
	dataloader->AddVariable("ele_pt","var_1", "", 'F');
	dataloader->AddVariable("scl_eta", "var_2", "", 'F');
	dataloader->AddVariable("ele_fbrem", "var_3", "", 'F');
	dataloader->AddVariable("ele_eelepout", "var_3", "", 'F');
	
	// You can add an arbitrary number of signal or background trees
	dataloader->AddSignalTree(signalTree, 1.);
	dataloader->AddBackgroundTree(background, 1.);
	
	dataloader->PrepareTrainingAndTestTree( "","","nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V");
	
	if (metoda=="MLP")
		factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP","H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator");

	if (metoda=="BDTG")
		factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2");
	
	factory->TrainAllMethods();
	factory->TestAllMethods();
	factory->EvaluateAllMethods();
	
	outputFile->Close();
	std::cout << "Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "TMVAClassification is done!" << std::endl;
	delete factory;
	delete dataloader;

}