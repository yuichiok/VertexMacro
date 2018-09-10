#define myclass_cxx
#include "myclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

void myclass::Loop()
{
		//   In a ROOT session, you can do:
		//      Root > .L myclass.C
		//      Root > myclass t
		//      Root > t.GetEntry(12); // Fill t data members with entry number 12
		//      Root > t.Show();       // Show values of entry 12
		//      Root > t.Show(16);     // Read and show values of entry 16
		//      Root > t.Loop();       // Loop on all entries
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


		//TH1F *chi2hist = new TH1F("chi2hist", "chi2 dist.",100,0,200);

		if (fChain == 0) return;

		Long64_t nentries = fChain->GetEntriesFast();

		Long64_t nbytes = 0, nb = 0;
		int numTest=0;
		
		for (Long64_t jentry=0; jentry<nentries;jentry++) {
				Long64_t ientry = LoadTree(jentry);
				if (ientry < 0) break;
				nb = fChain->GetEntry(jentry);   nbytes += nb;

				//bool hadM = (hadMass > 180 && hadMass < 420)? true: false;
				//bool rcTW = (Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50)? true: false;

				//if(hadM && rcTW) numTest++;

				if (Cut(ientry) < 0) continue;
		
				numTest++;

		}

		std::cout << "test number = " << numTest << std::endl;

}
