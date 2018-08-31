
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void efficiency()
{
		//TFile * file = TFile::Open(filename.c_str());
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_inc.root");
		TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_lcut.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_no_iso_lep.root");

		//TTree * normaltree = Stats;
		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
		TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

		int forward = GenTree->Draw("qMCcostheta","qMCcostheta > 0 && qMCcostheta > -2 ");
		int backward = GenTree->Draw("qMCcostheta","qMCcostheta < 0 && qMCcostheta > -2");

		
		///////////////
		// BASE CUTS //
		///////////////

		string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.0 || Top2btag > 0.0)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";

		// **** Full cuts ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ((methodTaken == 1 && Top1btag > 0.8 && Top2btag > 0.8 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 1 )";

		// **** Test ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((methodTaken == 1 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 2 )";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4)";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ( methodTaken >= 1 )";



		string fcuts = "qCostheta > 0" + cuts;
		string bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;
		int recoforward = normaltree->Draw("qCostheta", fcuts.c_str());
		int recobackward = normaltree->Draw("qCostheta", bcuts.c_str());
		
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

