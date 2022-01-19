#define analyzer_cxx
#include "analyzer.h"
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TMath.h>
#include <TRandom3.h>
#include <iostream>
#include <TString.h>
using namespace std;

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

	double sum=0;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  sum=sum+height;
   }
   prosjek=sum/100;
   //cout << nentries << endl;
}

void analyzer::generacija()
{
	double p_value;
	TRandom *r = new TRandom3();
	TH1F *hist = new TH1F("hist","",200,160,170);
	double suma=0;
	for(int i=0;i<10e5;i++)
		{
		for(int j=0;j<100;j++)
			{
				suma=suma + r->Gaus(164.7,7.1);
			}
		suma=suma/100;
		hist->Fill(suma);
		suma=0;
		}	
		
	p_value = hist->Integral(hist->GetXaxis()->FindBin(prosjek),100)/hist->Integral();
	double z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value);	
	cout<<"p-value = "<< p_value <<" \n signifikantnost = "<< z_score << endl;
	
	TCanvas *c = new TCanvas("canv","canv",600,400);
	hist->Draw();
	c->SaveAs("hist.png");
	
	delete hist;
	delete c;
}
void analyzer::testiranje(double a, double b, TString c)
{
	double p_value0=0, p_value1=0;
	double z0=0, z1=0;
	TCanvas *canv = new TCanvas("canv","canv",600,400);
	TRandom *r = new TRandom3();
	TH1F *shist = new TH1F("spanija","",200,160,174);
	shist->SetLineColor(kRed);
	TH1F *hist = new TH1F(c,"",200,160,174);
	double suma0=0, suma1=0;
	for(int i=0;i<10e5;i++)
		{
		for(int j=0;j<100;j++)
			{
				suma0+=r->Gaus(168.0,7.0);
				suma1+=r->Gaus(a,b);
			}
		suma0/=100;
		suma1/=100;
		shist->Fill(suma0);
		hist->Fill(suma1);
		suma0=0;
		suma1=0;
		}	
	p_value0 = shist->Integral(shist->GetXaxis()->FindBin(prosjek),100)/shist->Integral();
	z0 = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value0);	
	cout<<"p-value0 = "<< p_value0 <<" \n signifikantnost0 = "<< z0 << endl;
	
	p_value1 = hist->Integral(hist->GetXaxis()->FindBin(prosjek),100)/hist->Integral();
	z1 = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value1);	
	cout<<"p-value1 = "<< p_value1 <<" \n signifikantnost1 = "<< z1 << endl;
	double CL = 100 - TMath::Abs(z1);
	cout << "CL odbacivanja H1 = "<< CL << endl;
	shist->SetTitle("CL je isprintan u cout, ne mogu nac nacin za printat variablu u hist title ");
	shist->Draw();
	hist->Draw("same");
	
	TLegend *legend = new TLegend(0.1,0.8,0.3,0.9);

	legend->AddEntry(shist,"spanjolska","l");
	legend->AddEntry(hist,c,"l");
	legend->Draw();
	
	//cout << "test \t" << shist->GetBinContent(shist->FindFixBin(prosjek)) << endl;
	TLine *line = new TLine(prosjek,0,prosjek,shist->GetBinContent(shist->FindFixBin(prosjek)));
	line->Draw();

	canv->SaveAs(c+".png");
	
	delete canv;
	delete shist;
}
	