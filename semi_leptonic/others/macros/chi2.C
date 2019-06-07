
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void chi2()
{
		int token=0;
		string filename0 = "/home/ilc/yokugawa/run/root_merge/";
		//string filename0 = "rootfile/"; 
		string filename1;

		cout << "0 = New/Small" 	  << endl;
		cout << "1 = New/Large" 	  << endl;
		cout << "2 = New/Large/QQbar" << endl;
		cout << "3 = Old      " 	  << endl;
		cout << "4 = Old/yyxylv      "       << endl;
		cout << "Choose from 0-4: ";
		cin  >> token;
		cout << endl;

		switch(token){
				case 0 : filename1 = "new/small/leptonic_yyxyev_eLeR_new_small.root";
						 break;
				case 1 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large.root";
						 break;
				case 2 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar.root";
						 break;
				case 3 : filename1 = "old/leptonic_yyxyev_eLeR_old_lcut.root" ;
						 break;
				case 4 : filename1 = "old/leptonic_yyxylv_eLeR_iso_lep_lcut.root" ;
						 break;
		}

		string filename = filename0 + filename1;
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());

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

