//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jan 15 12:33:43 2022 by ROOT version 6.24/06
// from TTree TrainTree/TrainTree
// found on file: TMVA.root
//////////////////////////////////////////////////////////

#ifndef analyzer_h
#define analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           classID;
   Char_t          className[11];
   Float_t         ele_pt;
   Float_t         scl_eta;
   Float_t         ele_fbrem;
   Float_t         ele_eelepout;
   Float_t         weight;
   Float_t         MLP;

   // List of branches
   TBranch        *b_classID;   //!
   TBranch        *b_className;   //!
   TBranch        *b_ele_pt;   //!
   TBranch        *b_scl_eta;   //!
   TBranch        *b_ele_fbrem;   //!
   TBranch        *b_ele_eelepout;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_MLP;   //!

   analyzer(TTree *tree=0);
   virtual ~analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analyzer_cxx
analyzer::analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TMVA.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("TMVA.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("TMVA.root:/dataset");
      dir->GetObject("TrainTree",tree);

   }
   Init(tree);
}

analyzer::~analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("classID", &classID, &b_classID);
   fChain->SetBranchAddress("className", className, &b_className);
   fChain->SetBranchAddress("ele_pt", &ele_pt, &b_ele_pt);
   fChain->SetBranchAddress("scl_eta", &scl_eta, &b_scl_eta);
   fChain->SetBranchAddress("ele_fbrem", &ele_fbrem, &b_ele_fbrem);
   fChain->SetBranchAddress("ele_eelepout", &ele_eelepout, &b_ele_eelepout);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("MLP", &MLP, &b_MLP);
   Notify();
}

Bool_t analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analyzer_cxx