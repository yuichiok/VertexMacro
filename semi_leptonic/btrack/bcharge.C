#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void bcharge()
{
		int token=0;
		string filename0 = "/home/ilc/yokugawa/run/root_merge/";
		//string filename0 = "rootfile/"; 
		string filename1;

		filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar_withBtrack2.root";

		string filename = filename0 + filename1;
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());

		int bin_e = 30;
		int max_e = 1;

		TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
		//TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);
		
		TH1F * hist = new TH1F("hist", "test;ncharge;nevents", 12, 0, 1);

		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;

		normaltree->Draw("Top1Genbcharge >> hist");

		hist->Draw();

		/*
		TH2F * h_Top1bntracks     = new TH2F("h_Top1bntracks", "Top1 b-quark ntracks;Reco b ntracks;MC b ntracks", 20, 0, 20, 20, 0, 20) ;
		TH2F * h_Top2bntracks     = new TH2F("h_Top2bntracks", "Top2 b-quark ntracks;Reco b ntracks;MC b ntracks", 20, 0, 20, 20, 0, 20) ;

		//TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
		//cosReco->Sumw2();

		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
		TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

		// Selection lists
		TCut thru = "Thrust < 0.9";
		TCut hadM = "hadMass > 180 && hadMass < 420";
		TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";
		TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
		TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

		// Methods selection
		TCut methodAll = "methodTaken > 0";
		TCut method1 = "methodTaken == 1";
		TCut method2 = "methodTaken == 2";
		TCut method3 = "methodTaken == 3";
		TCut method4 = "methodTaken == 4";
		TCut method5 = "methodTaken == 5";
		TCut method6 = "methodTaken == 6";
		TCut method7 = "methodTaken == 7";

		// Total cut applied
		TCut cuts = rcTW + hadM + pcut + gcut + methodAll;

		TCut diag = " (Top1bntracks - Top1Genbntracks) == 0 " ;

		//TCut fcuts = "qCostheta > 0" + cuts;
		//TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;
		
		// Fill histograms from tree
		normaltree->Draw("Top1bntracks:Top1Genbntracks >> h_Top1bntracks");
		int Top1_accepted          = normaltree->Draw("Top1bntracks:Top1Genbntracks",  diag);
		int Top1_rejected          = normaltree->Draw("Top1bntracks:Top1Genbntracks", !diag);
		int Top1_total = Top1_accepted + Top1_rejected ;

		normaltree->Draw("Top2bntracks:Top2Genbntracks >> h_Top2bntracks");
		int Top2_accepted          = normaltree->Draw("Top2bntracks:Top2Genbntracks",  diag);
		int Top2_rejected          = normaltree->Draw("Top2bntracks:Top2Genbntracks", !diag);
		int Top2_total 			   = Top2_accepted + Top2_rejected ;
		
		// output
		cout << "====================" << endl;
		cout << "accepted = " << Top1_accepted << "\n";
		cout << "rejected = " << Top1_rejected << "\n";
		cout << "Total    = " << Top1_total    << "\n";
		cout << "\n";
		cout << "Track reco eff = " << (float)(Top1_accepted) / (float)(Top1_total) << endl;
		cout << "====================" << endl;

		c1->cd();
		h_Top1bntracks->SetStats(0);
		h_Top1bntracks->Draw("COLZ");
		c1->Update();
		
		c2->cd();
		h_Top2bntracks->SetStats(0);
		h_Top2bntracks->Draw("COLZ");
		c2->Update();
		*/

}

