
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void efficiency()
{
		int token=0;
		string filename0 = "/home/ilc/yokugawa/run/root_merge/";
		string filename1;

		cout << "0 = New/Small" << endl;
		cout << "1 = New/Large" << endl;
		cout << "2 = Old      " << endl;
		cout << "Choose from 0-2: ";
		cin  >> token;
		cout << endl;
		
		switch(token){
			case 0 : filename1 = "leptonic_yyxyev_eLeR_new_small.root";
					 break;
			case 1 : filename1 = "leptonic_yyxyev_eLeR_new_large.root";
					 break;
			case 2 : filename1 = "leptonic_yyxyev_eLeR_old_lcut.root" ;
					 break;
		}

		string filename = filename0 + filename1;
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_inc.root");
		//!TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_lcut.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_no_iso_lep.root");

		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
		TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
		TTree * Summary = (TTree*) file->Get( "Summary" );

		int forward  = GenTree->Draw("qMCcostheta","qMCcostheta > 0 && qMCcostheta > -2 ");
		int backward = GenTree->Draw("qMCcostheta","qMCcostheta < 0 && qMCcostheta > -2");

		///////////////
		// BASE CUTS //
		///////////////

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.8 || Top2btag > 0.3)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";

		// **** Full cuts ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ((methodTaken == 1 && Top1btag > 0.8 && Top2btag > 0.8 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 1 )";

		// **** Test ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((methodTaken == 1 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 2 )";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4)";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ( methodTaken >= 1 )";


		// Begin efficiency calculation
		
		int entrySum = Summary->GetEntries();
		int nEvents, nAfterLeptonCuts, nAfterBtagCuts;
		int nevt, nlcut, nbcut;

		Summary->SetBranchAddress( "nEvents", &nEvents ) ;
		Summary->SetBranchAddress( "nAfterLeptonCuts", &nAfterLeptonCuts ) ;
		Summary->SetBranchAddress( "nAfterBtagCuts", &nAfterBtagCuts ) ;

		for(int i=0; i<entrySum; i++){

				Summary->GetEntry(i);

				nevt  += nEvents;
				nlcut += nAfterLeptonCuts;
				nbcut += nAfterBtagCuts;

		}

		cout << "nEvents                      = " << nevt << " (100%)" << endl;
		cout << "after lepton cuts            = " << nlcut << " (" << (float)(nlcut)/(float)(nevt) *100 << "%)" << endl;
		cout << "after btag cuts (0.8 & 0.3)  = " << nbcut << " (" << (float)(nbcut)/(float)(nevt) *100 << "%)" << endl;
		

		TCut thru = "Thrust < 0.9";
		TCut hadM = "hadMass > 180 && hadMass < 420";
		TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";

		TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
		TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

		TCut method = "methodTaken > 0";

		TCut cuts = thru && hadM && rcTW && pcut && gcut && method;

		int afterbcut    = normaltree->GetEntries();
		int afterthrucut = normaltree->GetEntries( thru );
		int afterhadMcut = normaltree->GetEntries( thru && hadM );
		int afterrcTWcut = normaltree->GetEntries( thru && hadM && rcTW );

		cout << "after thrust cut             = " << afterthrucut << " (" << (float)(afterthrucut)/(float)(nevt) *100 << "%)" << endl;
		cout << "after hadronic mass cut      = " << afterhadMcut << " (" << (float)(afterhadMcut)/(float)(nevt) *100 << "%)" << endl;
		cout << "after reco T & W mass cut    = " << afterrcTWcut << " (" << (float)(afterrcTWcut)/(float)(nevt) *100 << "%)" << endl;
		
		TCut fcoscut = "qCostheta > 0";
		TCut bcoscut = "qCostheta < 0 && qCostheta > -1.0";
	
		TCut fcuts = fcoscut && cuts;
		TCut bcuts = bcoscut && cuts;

		int recoforward = normaltree->GetEntries(fcuts);
		int recobackward = normaltree->GetEntries(bcuts);
		
		float afbgen = (float)(forward - backward) / (float) (forward + backward);
		float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);
		
		cout << "--------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------\n";
		std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
		std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
		cout << "--------------------------------------------------------------\n";
		float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
		cout << "Final efficiency: " << efficiency << "%\n" ;
		cout << "--------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------\n";
		//file->Close();
}

