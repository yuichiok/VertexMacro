#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;

void sethist(Color_t clr, TH1F* h = 0);

void asymmetry_fullHad_EvE()
{
	// set plot style
	SetQQbarStyle();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

	// set file path
	std::string filename = "/hsm/ilc/users/yokugawa/preset_N_run/l5/fullHad/eLpR/QQbarProcessor_out/root_merge/fullHad.eL.pR_QQbar.root";
	//std::string filename = "/hsm/ilc/users/yokugawa/preset_N_run/l5/electron_muon/QQbarProcessor_out/IsoLepTagged.eL.pR_electron_muon_QQbar_MethodAll_110119.root";

	TFile * file = TFile::Open(filename.c_str());

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;

	// Histograms
	
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * cosbjets_all = new TH1F("cosbjets_all", ";cos#theta_{bjets};Entries", 200,-1.0,1.0);
	TH1F * cosbjets_acc = new TH1F("cosbjets_acc", ";cos#theta_{bjets};Entries", 200,-1.0,1.0);
	TH1F * cosbjets_rej = new TH1F("cosbjets_rej", ";cos#theta_{bjets};Entries", 200,-1.0,1.0);

	TH1F * bjetE_all = new TH1F("bjetE_all", ";E_{bjet} (GeV);Entries", 200,0.,200.);
	TH1F * bjetE_acc = new TH1F("bjetE_acc", ";E_{bjet} (GeV);Entries", 200,0.,200.);
	TH1F * bjetE_rej = new TH1F("bjetE_rej", ";E_{bjet} (GeV);Entries", 200,0.,200.);

	TGaxis::SetMaxDigits(3);

	sethist(kGray+1, cosbjets_all);
	cosbjets_all->SetLineStyle(1);
	sethist(kGreen+1, cosbjets_acc);
	sethist(kRed+1, cosbjets_rej);

	sethist(kGray+1, bjetE_all);
	bjetE_all->SetLineStyle(1);
	sethist(kGreen+1, bjetE_acc);
	sethist(kRed+1, bjetE_rej);

	
	// Variables
	int Top1bcharge = 0,
			Top2bcharge = 0;

	float Top1btag = 0,
				Top2btag = 0;


	// Cuts
	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.30 ) " ;
	TCut chi2_1 = " chiTopMass1 + chiTopE1 + chiPbstar1 < 30 " ;
	TCut chi2_2 = " chiTopMass2 + chiTopE2 + chiPbstar2 < 30 " ;
	TCut chi2 = chi2_1 + chi2_2 ;
	//TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) && ( Top2mass > 140 ) && ( Top2mass < 210 ) " ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) " ;
	TCut samecharge = "  Top1bcharge * Top2bcharge > 0 " ;
	TCut both0charge = " ( Top1bcharge == 0 ) || ( Top2bcharge == 0 ) " ;

	int entryStat = normaltree->GetEntries();	
	cout << "eventnum            = " << entryStat << " (100%)" << endl ;
	int afterbtag = normaltree->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/entryStat << "%)" << endl ;
	int afterkinematic = normaltree->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/entryStat << "%)" << endl;

	int samesignnum = normaltree->GetEntries( btag && kinematic && samecharge ) ;
	int both0num = normaltree->GetEntries( btag && kinematic && both0charge ) ;

	int usednum = afterkinematic;

	cout << endl ;
	cout << "used number = " << usednum << endl ; // number of events before cuts (not precuts!)

	TEventList *elist1 = new TEventList( "elist1", "Reconstructed Event List" ) ;
	//normaltree->Draw( ">>elist1", btag && kinematic && chi2 ) ;
	normaltree->Draw( ">>elist1", btag && kinematic ) ;


	normaltree->SetBranchAddress("Top1bcharge", &Top1bcharge);
	normaltree->SetBranchAddress("Top2bcharge", &Top2bcharge);
	normaltree->SetBranchAddress("Top1btag", &Top1btag);
	normaltree->SetBranchAddress("Top2btag", &Top2btag);


	bool isbsign = false;
	int  b1b2 = 0;

  for(int iStatEntry=0; iStatEntry<usednum; iStatEntry++){

		normaltree->GetEntry( elist1->GetEntry(iStatEntry) );

		isbsign = false ;

		if( (Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80) && (fabs(Top1bcharge) < 5 && fabs(Top2bcharge) < 5) ) isbsign = true;

		if(isbsign) b1b2++;

	}

	cout << "b1b2 = " << b1b2 << endl;

/*
	// Plot




	// Legends
	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosbjets_all,"All","l");
	leg->AddEntry(cosbjets_acc,"Accepted","l");
	leg->AddEntry(cosbjets_rej,"Rejected","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();
*/

}

void sethist(Color_t clr, TH1F* h = 0){

	h->SetLineWidth(3);
	h->SetLineStyle(2);
	h->SetLineColor(clr);
	h->SetFillColor(clr);
	h->SetFillStyle(3004);

}








