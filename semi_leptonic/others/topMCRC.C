#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void topMCRC()
{
	int token=0;
	string filename0 = "/home/ilc/yokugawa/run/root_merge/";
	string filename1;

	cout << "0 = New/Small" 	  << endl;
	cout << "1 = New/Large" 	  << endl;
	cout << "2 = New/Large/QQbar" << endl;
	cout << "3 = New/Large/QQbar_newTest" << endl;
	//cout << "3 = Old      " 	  << endl;
	//cout << "4 = Old/yyxylv      "       << endl;
	cout << "Choose from 0-3: ";
	cin  >> token;
	cout << endl;

	switch(token){
		case 0 : filename1 = "new/small/leptonic_yyxyev_eLeR_new_small.root";
						 break;
		case 1 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large.root";
						 break;
		case 2 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar.root";
						 break;
		case 3 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar_NewIsoLep_121318.root";
						 break;
		//case 3 : filename1 = "old/leptonic_yyxyev_eLeR_old_lcut.root" ;
		//				 break;
		//case 4 : filename1 = "old/leptonic_yyxylv_eLeR_iso_lep_lcut.root" ;
		//				 break;
	}

	string filename = filename0 + filename1;
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	int bin_e = 30;
	int max_e = 1;

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1500,1000);
	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);
	c1->Divide(3,2,0,0);

	TH2F * h_TopPolar     = new TH2F("h_TopPolar", "Top Polar Angle;RC;MC", 30, -1, 1, 30, -1, 1) ;
	TH1F * h_Top1mass			= new TH1F("h_Top1mass", "Top1 mass;mass_{top1};events", 100, 0, 400);
	TH1F * h_W1mass				= new TH1F("h_W1mass", "W1 mass;mass_{W1};events", 100, 0, 300);
	TH1F * h_LeptonCos		= new TH1F("h_LeptonCos", "Lepton Polar Angle;|Top2leptonCos|;events", 100, 0, 1.2);
	TH1F * h_B1mass				= new TH1F("h_B1mass", "B1 mass;mass_{B1};events", 100, 0, 100);
	//TH2F * h_Top2bntracks     = new TH2F("h_Top2bntracks", "Top2 b-quark ntracks;Reco b ntracks;MC b ntracks", 20, 0, 20, 20, 0, 20) ;
	//TH1F * h_BHadtracks				= new TH1F("h_BHadtracks", "B Hadron ntracks;Reco b ntracks; NEvents", 20, 0, 20) ;

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
	TCut RCcuts = rcTW + hadM + pcut + gcut + methodAll + "qCostheta > -1.0";
	TCut MCcuts = "qMCcostheta > -2";

	TCut diag = " (Top1bntracks - Top1Genbntracks) == 0 " ;

	//TCut fcuts = "qCostheta > 0" + cuts;
	//TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;

	// Fill histograms from tree
	normaltree->Draw("qMCcostheta:qCostheta >> h_TopPolar",RCcuts+MCcuts);
	normaltree->Draw("Top1mass >> h_Top1mass");
	normaltree->Draw("W1mass >> h_W1mass");
	normaltree->Draw("Top2leptonCos >> h_LeptonCos");
	normaltree->Draw("jet_M >> h_B1mass");
	

/*
	c1->cd(1);
	normaltree->Draw("qMCcostheta:qCostheta >> h_TopPolar",RCcuts+MCcuts);
	h_TopPolar->SetStats(0);
	h_TopPolar->Draw("COLZ");

	c1->cd(2);
	normaltree->Draw("Top1mass >> h_Top1mass","W1mass < 50");
	h_Top1mass->Draw();

	c1->cd(3);
	normaltree->Draw("W1mass >> h_W1mass");
	h_W1mass->Draw();

	c1->cd(4);
	normaltree->Draw("Top2leptonCos >> h_LeptonCos");
	h_LeptonCos->Draw();

	c1->cd(5);
	normaltree->Draw("jet_M >> h_B1mass");
	h_B1mass->Draw();
	*/

	c2->cd();
	//h_B1mass->Draw();
	normaltree->Draw("Top2leptonCos >> h_LeptonCos");
	h_LeptonCos->Draw();

}

