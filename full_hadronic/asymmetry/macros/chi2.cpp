#include <iostream>
#include <string>
#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TH1F.h>
#include <TCut.h>
#include <TEventList.h>
#include <TStyle.h>
#include "../../style/Style.C"
#include "../../style/Labels.C"

using namespace std ;

void chi2(){

	// set plot style
	SetQQbarStyle();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(1);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

	//TH1F* h_Chi2Sum = new TH1F( "h_Chi2Sum", "h_Chi2Sum", 1000, 0, 1000 ) ;


	// declare canvas for later usage


	//opening the root files
	// IDR
	/*
	string rootfiledir = "/hsm/ilc/users/yokugawa/preset_N_run/l5/fullHad/eLpR/QQbarProcessor_out/root_merge/" ;
	string beforefilename = "fullHad.eL.pR_QQbar.root" ;
	
	// DBD
	string rootfiledir = "/home/ilc/yokugawa/TTBarAnalysis/root_merge/" ;
	string beforefilename = "hadronic_eLpR_kekcc_500k.root" ;
	*/

	// Semi-leptonic
	string rootfiledir = "/hsm/ilc/users/yokugawa/preset_N_run/l5/electron_muon/QQbarProcessor_out/" ;
	string beforefilename = "IsoLepTagged.eL.pR_electron_muon_QQbar_MethodAll_110119.root" ;


	string rootfilename ;
	string treename = "Stats" ;

	rootfilename = rootfiledir + beforefilename ;
	cout << "filename '" << rootfilename << "'." << endl ;
	TFile * file1 = TFile::Open(rootfilename.c_str());
	if( file1->IsZombie() ){
		cout << "cannot open the file '" << rootfilename << "'." << endl ;
		return ;
	}

	gStyle->SetOptStat(0) ;


	TCanvas* c2 = new TCanvas( "c2", "c2", 500, 500 ) ;

	TH1F* h_chiSum = new TH1F( "h_chiSum", "h_chiSum", 1000, 0, 300 ) ;

	TH1F* h_chiTopMass1 = new TH1F( "h_chiTopMass1", "h_chiTopMass1", 1000, 0, 300 ) ;
	TH1F* h_chiTopE1    = new TH1F( "h_chiTopE1", "h_chiTopE1", 1000, 0, 300 ) ;
	TH1F* h_chiPbstar1  = new TH1F( "h_chiPbstar1", "h_chiPbstar1", 1000, 0, 100 ) ;

	TH1F* h_chiTopMass2 = new TH1F( "h_chiTopMass2", "h_chiTopMass2", 1000, 0, 300 ) ;
	TH1F* h_chiTopE2    = new TH1F( "h_chiTopE2", "h_chiTopE2", 1000, 0, 300 ) ;
	TH1F* h_chiPbstar2  = new TH1F( "h_chiPbstar2", "h_chiPbstar2", 1000, 0, 100 ) ;

	TGaxis::SetMaxDigits(3);

	// setting precuts
	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.30 ) " ;

	TCut chi2_1 = "chiTopMass1 + chiTopE1 + chiPbstar1 < 30 " ;
	TCut chi2_2 = "chiTopMass2 + chiTopE2 + chiPbstar2 < 30 " ;
	//TCut chi2_1 = "chiTopMass1 + chiTopE1 < 30 " ;
	//TCut chi2_2 = "chiTopMass2 + chiTopE2 < 30 " ;

	TCut chi2 = chi2_1 + chi2_2 ;
	//TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) && ( Top2mass > 140 ) && ( Top2mass < 210 ) " ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) " ;
	TCut samecharge = "  Top1bcharge * Top2bcharge > 0 " ;
	TCut both0charge = " ( Top1bcharge == 0 ) || ( Top2bcharge == 0 ) " ;


	// getting tree informations
	TTree* tree1 = (TTree*) file1->Get( treename.c_str() ) ;
	int eventnum = tree1->GetEntries() ;
	cout << "eventnum            = " << eventnum << " (100%)" << endl ;
	int afterbtag = tree1->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/eventnum << "%)" << endl ;
	int afterkinematic = tree1->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/eventnum << "%)" << endl;


	int val_chiSum = tree1->Draw("chiTopMass1 + chiTopE1 + chiPbstar1 >> h_chiSum", btag && kinematic);
	//int val_chiSum = tree1->Draw("chiTopMass1 + chiTopE1 >> h_chiSum", btag && kinematic);

	int val_chiTopMass1 = tree1->Draw("chiTopMass1 >> h_chiTopMass1", btag && kinematic);
	int val_chiTopE1    = tree1->Draw("chiTopE1 >> h_chiTopE1", btag && kinematic);
	int val_chiPbstar1  = tree1->Draw("chiPbstar1 >> h_chiPbstar1", btag && kinematic);

	int val_chiTopMass2 = tree1->Draw("chiTopMass2 >> h_chiTopMass2", btag && kinematic);
	int val_chiTopE2    = tree1->Draw("chiTopE2 >> h_chiTopE2", btag && kinematic);
	int val_chiPbstar2  = tree1->Draw("chiPbstar2 >> h_chiPbstar2", btag && kinematic);

	//c2->Update();

	TCanvas* c1 = new TCanvas( "c1", "c1", 1500, 1000 ) ;

	c1->Divide(3,2);

	c1->cd(1);
	h_chiTopMass1->Draw();
	c1->cd(2);
	h_chiTopE1->Draw();
	c1->cd(3);
	h_chiPbstar1->Draw();
	
	c1->cd(4);
	h_chiTopMass2->Draw();
	c1->cd(5);
	h_chiTopE2->Draw();
	c1->cd(6);
	h_chiPbstar2->Draw();

	c1->Update();


	TCanvas* c3 = new TCanvas( "c3", "c3", 500, 500 ) ;

	h_chiSum->Draw();

	c3->Update();



/*
	int afterchi2 = tree1->GetEntries( btag && kinematic && chi2 ) ;
	//int afterchi2 = tree1->GetEntries( btag && kinematic ) ;
	
	cout << "after chi2 cut      = " << afterchi2 << " (" << (float)100*afterchi2/eventnum << "%)" << endl;

	// number of events after precuts
	//int samesignnum = tree1->GetEntries( btag && kinematic && chi2 && samecharge ) ;
	//int samesignKaonbnum = tree1->GetEntries( btag && kinematic && chi2 && sameKaonbcharge ) ;
	//int both0num = tree1->GetEntries( btag && kinematic && chi2 && both0charge ) ;
	//int usednum = afterchi2 - samesignnum - both0num ;
	
	int samesignnum = tree1->GetEntries( btag && kinematic && samecharge ) ;
	//int samesignKaonbnum = tree1->GetEntries( btag && kinematic && chi2 && sameKaonbcharge ) ;
	int both0num = tree1->GetEntries( btag && kinematic && both0charge ) ;
	*/

}




