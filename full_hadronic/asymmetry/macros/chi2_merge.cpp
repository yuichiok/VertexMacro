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

void chi2_merge(){

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


	//opening the root files
	// IDR
	string rootfilename_fullHad = "/hsm/ilc/users/yokugawa/preset_N_run/l5/fullHad/eLpR/QQbarProcessor_out/root_merge/fullHad.eL.pR_QQbar_temp.root" ;
	string rootfilename_semiLep = "/hsm/ilc/users/yokugawa/preset_N_run/l5/semiLep/eLpR/electron_muon/QQbarProcessor_out/IsoLepTagged.eLpR_electron_muon_QQbar_MethodAll_temp.root" ;
	
	string treename = "Stats" ;

	cout << "filename '" << rootfilename_fullHad << "'." << endl ;
	TFile * file1 = TFile::Open(rootfilename_fullHad.c_str());
	if( file1->IsZombie() ){
		cout << "cannot open the file '" << rootfilename_fullHad << "'." << endl ;
		return ;
	}

	gStyle->SetOptStat(0) ;

	TCanvas* c2 = new TCanvas( "c2", "c2", 500, 500 ) ;
	TH1F* h_chiSum = new TH1F( "h_chiSum", ";#chi^{2}_{top};Events", 1000, 0, 300 ) ;
	//h_chiSum->SetDirectory(0);

	TGaxis::SetMaxDigits(3);

	// setting precuts
	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.30 ) " ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) " ;
	TCut samecharge = "  Top1bcharge * Top2bcharge > 0 " ;
	TCut both0charge = " ( Top1bcharge == 0 ) || ( Top2bcharge == 0 ) " ;

	// getting tree informations
	TTree* tree1 = (TTree*) file1->Get( treename.c_str() ) ;
	//int val_chiSum = tree1->Draw("chiTopMass1 + chiTopE1 + chiPbstar1 + chiCosWb1 + chiGammaT1 >> h_chiSum", btag && kinematic);
	int val_chiSum = tree1->Draw("chiTopMass1 + chiTopE1 + chiPbstar1 + chiCosWb1 + chiGammaT1 >> h_chiSum", "");


	TFile * file2 = TFile::Open(rootfilename_semiLep.c_str());
	if( file2->IsZombie() ){
		cout << "cannot open the file '" << rootfilename_semiLep << "'." << endl ;
		return ;
	}

	TH1F* h_chiSum2 = new TH1F( "h_chiSum2", ";#chi^{2}_{top};Events", 1000, 0, 300 ) ;

	// getting tree informations
	TTree* tree2 = (TTree*) file2->Get( treename.c_str() ) ;
	//int val_chiSum2 = tree2->Draw("chiTopMass + chiTopE + chiPbstar + chiCosWb + chiGammaT >> h_chiSum2", btag && kinematic);
	int val_chiSum2 = tree2->Draw("chiTopMass + chiTopE + chiPbstar + chiCosWb + chiGammaT >> h_chiSum2", "");

	h_chiSum->SetLineWidth(3); 
	h_chiSum2->SetLineWidth(3);
	 
	h_chiSum->SetLineColor(kBlue+1); 
	h_chiSum2->SetLineColor(kRed+1);

 //足し合わせるヒストグラムをTListに格納
	TList *l = new TList;
	l->Add(h_chiSum);
	l->Add(h_chiSum2);


	TCanvas* c1 = new TCanvas( "c1", "c1", 500, 500 ) ;

	l->At(0)->Draw();
	l->At(1)->Draw("same");

	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(l->At(0),"Full Hadronic","l");
	leg->AddEntry(l->At(1),"Semi Leptonic","l");

	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();

	//c3->Update();


}




