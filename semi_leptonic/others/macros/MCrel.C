#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void MCrel()
{
	int token=0;
	string filename0 = "/home/ilc/yokugawa/run/root_merge/";
	string filename1;

	filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar_VR.root";

	string filename = filename0 + filename1;
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	int bin_e = 30;
	int max_e = 1;

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);

	TH1F * h_MCTopmomentum = new TH1F("h_MCTopmomentum", "MC top momentum;MC p_{top}; NEvents", 100, 0, 200) ;

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

	TCut diag1 = " (Top1bntracks - Top1Genbntracks) != 0 " ;
	TCut diag2 = " (Top2bntracks - Top2Genbntracks) != 0 " ;
	TCut diag  = diag1 || diag2;

	normaltree->Draw("MCTopmomentum >> h_MCTopmomentum", diag);
	//normaltree->Draw("MCTopmomentum >> h_MCTopmomentum");

	c1->cd();
	h_MCTopmomentum->SetStats(0);
	h_MCTopmomentum->Draw();

}

