
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void chi2()
{
		//TFile * file = TFile::Open(filename.c_str());
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_inc.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_lcut.root");
		TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_lcut_090418.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_no_iso_lep.root");

		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
		TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
		TTree * Summary = (TTree*) file->Get( "Summary" );

		///////////////
		// BASE CUTS //
		///////////////

		// Begin efficiency calculation
		
		TCut thru = "Thrust < 0.9";
		TCut hadM = "hadMass > 180 && hadMass < 420";
		TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";

		TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
		TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

		TCut method = "methodTaken > 0";

		TCut cuts = thru && hadM && rcTW;

		TH1F *chi2hist = new TH1F("chi2hist", "chi2 dist.",100,0,200);

		int chi2 = normaltree->Draw("chiGammaT+chiCosWb+chiPbstar >> chi2hist", cuts);

		chi2hist->Draw();

		//file->Close();
}

