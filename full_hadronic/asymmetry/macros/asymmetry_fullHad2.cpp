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
#define MAXV 8

using namespace std ;


void sethist(Color_t clr, TH1F* h = 0){

	h->SetLineWidth(3);
	h->SetLineStyle(1);
	h->SetLineColor(clr);
	h->SetFillColor(clr);
	h->SetFillStyle(3004);

}

float LorentzF( float energy, float mass){
	return energy/mass ;
}

void AddAFBvalue( float input, int& plus , int& minus ){
	if( input > 0 ){
		plus++ ;
	}else{
		minus++ ;
	}
}

float getAFB( int plus, int minus ){
	return 1.0*(plus-minus)/(plus+minus) ;
}

void FillMCRC( TH2F* hist = 0, float chg1 = 0, float t1cos = 0, float t2cos = 0, float mctcos = 0, float mctbarcos = 0 ){	
	if( chg1 < 0 ){
		hist->Fill(t1cos,mctcos);
		hist->Fill(-t2cos,-mctbarcos);
	}else if( chg1 > 0 ){
		hist->Fill(t2cos,mctcos);
		hist->Fill(-t1cos,-mctbarcos);
	}
}

void FillandAdd( int b1, float tcos1, float bcos1, int& tpl, int& tmi, int& bpl, int& bmi, double weight = 0, TH1F* top = 0, TH1F* bottom = 0){
	if( b1 < 0 ){  //Top1 = top, Top2 = antitop, Top1b = bottom, Top2b = antibottom
		top->Fill( tcos1, weight ) ;
		bottom->Fill( bcos1, weight ) ;
		AddAFBvalue( tcos1, tpl, tmi ) ;
		AddAFBvalue( bcos1, bpl, bmi ) ;
	}else {  //Top1 = antitop, Top2 = top, Top1b = antibottom, Top2b = bottom
		top->Fill( -tcos1, weight ) ;
		bottom->Fill( -bcos1, weight ) ;
		AddAFBvalue( -tcos1, tpl, tmi ) ;
		AddAFBvalue( -bcos1, bpl, bmi ) ;
	}

}

void asymmetry_fullHad2(){

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

	TGaxis::SetMaxDigits(3);

	TH1F* htop = new TH1F( "htop", ";cos #theta;Entries", 40, -1, 1 ) ;
	sethist(kRed+1, htop);
	//htop->SetMinimum(0) ;
	//htop->SetLineColor(2) ;

	TH1F* hbottom = new TH1F( "hbottom", ";cos #theta;Entries", 40, -1, 1 ) ;
	sethist(kRed+1, hbottom);
	//hbottom->SetMinimum(0) ;
	//hbottom->SetLineColor(2) ;

	TH1F* htopgen = new TH1F( "htopgen", ";cos #theta;Entries", 40, -1, 1 ) ;
	sethist(kGray+1, htopgen);
	//htopgen->SetMinimum(0) ;
	//htopgen->SetMaximum(0.11) ;
	//htopgen->SetLineColor(4) ;

	TH1F* hbottomgen = new TH1F( "hbottomgen", ";cos #theta;Entries", 40, -1, 1 ) ;
	sethist(kGray+1, hbottomgen);
	//hbottomgen->SetMinimum(0) ;
	//hbottomgen->SetMaximum(0.11) ;
	//hbottomgen->SetLineColor(4) ;

	TH2F* hCosMCRCbf = new TH2F( "hCosMCRCbf", "Top cos#theta MC vs RC (before vtx recovery)", 100, -1, 1, 100, -1, 1 ) ;
	TH2F* hCosMCRCaf = new TH2F( "hCosMCRCaf", "Top cos#theta MC vs RC (after vtx recovery)", 100, -1, 1, 100, -1, 1 ) ;

	// normalize histogram to have proper error
	htop->Sumw2();
	htopgen->Sumw2();
	hbottom->Sumw2();
	hbottomgen->Sumw2();

	TH1F* htopafter = new TH1F( "htopafter", ";cos #theta;Entries", 40, -1, 1 ) ;
	sethist(kGreen+1, htopafter);
	//htopafter->SetMinimum(0) ;
	//htopafter->SetLineColor(3) ;
	TH1F* hbottomafter = new TH1F( "hbottomafter", ";cos #theta;Entries", 40, -1, 1 ) ;
	sethist(kGreen+1, hbottomafter);
	//hbottomafter->SetMinimum(0) ;
	//hbottomafter->SetLineColor(3) ;

	htopafter->Sumw2();
	hbottomafter->Sumw2();
	//End of histogram definition

	// declare canvas for later usage
	//TCanvas* c1 = new TCanvas( "c1", "c1", 1280, 480 ) ;
	//TCanvas* c2 = new TCanvas( "c2", "c2", 1280, 480 ) ;
	TCanvas* c1 = new TCanvas( "c1", "c1", 500, 500 ) ;
	TCanvas* c2 = new TCanvas( "c2", "c2", 500, 500 ) ;
	//

	//opening the root files
	string rootfiledir = "/hsm/ilc/users/yokugawa/preset_N_run/l5/fullHad/eLpR/QQbarProcessor_out/root_merge/" ;

	string beforefilename = "fullHad.eL.pR_QQbar.root" ;
	string afterfilename = "fullHad.eL.pR_QQbar_noVR.root" ;
	string rootfilename ;
	string treename = "Stats" ;

	rootfilename = rootfiledir + beforefilename ;
	cout << "filename '" << rootfilename << "'." << endl ;
	TFile file1( rootfilename.c_str() ) ;
	if( file1.IsZombie() ){
		cout << "cannot open the file '" << rootfilename << "'." << endl ;
		return ;
	}

	gStyle->SetOptStat(0) ;

	// declaring variables
	int Top1bcharge, Top2bcharge ;
	float Top1costheta, Top1bcostheta, Top2costheta, Top2bcostheta ;
	//int Top1KaonCharges[100], Top2KaonCharges[100];
	int Top1TotalKaonCharge, Top2TotalKaonCharge ;
	float Top1bmomentum, Top2bmomentum;
	float Top1btag, Top2btag;
	float Top1energy, Top1mass;
	float Top2mass;
	float MCTopcostheta, MCTopBarcostheta ;
	float qMCBcostheta[2] ;
	int topplus = 0, topminus = 0, bottomplus = 0, bottomminus = 0 ;
	float topAFB, bottomAFB, topAFBgen, bottomAFBgen ;


	// setting precuts
	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.80 ) " ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) " ;
	TCut samecharge = "  Top1bcharge * Top2bcharge > 0 " ;
	TCut both0charge = " ( Top1bcharge == 0 ) || ( Top2bcharge == 0 ) " ;

	// before vertex recovery
	cout << endl ;
	cout << "-- before vertex recovery --" << endl ;

	// getting tree informations
	TTree* tree1 = (TTree*)file1.Get( treename.c_str() ) ;
	int eventnum = tree1->GetEntries() ;
	cout << "eventnum            = " << eventnum << " (100%)" << endl ;
	int afterbtag = tree1->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/eventnum << "%)" << endl ;
	int afterkinematic = tree1->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/eventnum << "%)" << endl;
	
	int samesignnum = tree1->GetEntries( btag && kinematic && samecharge ) ;
	int both0num = tree1->GetEntries( btag && kinematic && both0charge ) ;
	
	int usednum = afterkinematic ;

	cout << endl ;
	cout << "used number = " << usednum << endl ; // number of events before cuts (not precuts!)

	TEventList *elist1 = new TEventList( "elist1", "Reconstructed Event List" ) ;

	tree1->Draw( ">>elist1", btag && kinematic) ;

	// setting tree branch address
	tree1->SetBranchAddress( "MCTopcostheta", &MCTopcostheta ) ;
	tree1->SetBranchAddress( "MCTopBarcostheta", &MCTopBarcostheta ) ;
	tree1->SetBranchAddress( "qMCBcostheta", &qMCBcostheta ) ;

	tree1->SetBranchAddress( "Top1bcharge", &Top1bcharge ) ;
	tree1->SetBranchAddress( "Top1costheta", &Top1costheta ) ;
	tree1->SetBranchAddress( "Top1bcostheta", &Top1bcostheta ) ;
	tree1->SetBranchAddress( "Top2bcharge", &Top2bcharge ) ;
	tree1->SetBranchAddress( "Top2costheta", &Top2costheta ) ;
	tree1->SetBranchAddress( "Top2bcostheta", &Top2bcostheta ) ;

	tree1->SetBranchAddress( "Top1TotalKaonCharge", &Top1TotalKaonCharge ) ;
	tree1->SetBranchAddress( "Top2TotalKaonCharge", &Top2TotalKaonCharge ) ;
	tree1->SetBranchAddress( "Top1btag", &Top1btag ) ;
	tree1->SetBranchAddress( "Top2btag", &Top2btag ) ;

	tree1->SetBranchAddress( "Top1mass", &Top1mass ) ;
	tree1->SetBranchAddress( "Top1energy", &Top1energy ) ;
	tree1->SetBranchAddress( "Top2mass", &Top2mass ) ;

	tree1->SetBranchAddress( "Top1bmomentum", &Top1bmomentum ) ;
	tree1->SetBranchAddress( "Top2bmomentum", &Top2bmomentum ) ;

	//double fillweight = (double)1/usednum ;
	double fillweight = 1 ;

	// in-loop varibale declaration
	bool isbsign = false, iskaonsign = false;
	bool isb1k2sign = false;
	bool isb2k1sign = false;
	bool isbMomentum = false;

	//CRP 03/06/18 Add same side charges
	bool isb1k1sign = false;
	bool isb2k2sign = false;

	int bmomentum_pass=0;

  int oneZero=0;

	int b1b2=0,k1k2=0,b1k2=0,k1b2=0;
	//CRP 03/06/18 Add same side charges
	int k1b1=0;
	int k2b2=0;
	float G1=0,G2=0;

	// event loop (before vtx restore)
	for( int i=0 ; i<usednum ; i++ ){

		tree1->GetEntry( elist1->GetEntry(i) ) ;

		isbsign = false ;
		iskaonsign = false;
		isb1k2sign = false ;
		isb2k1sign = false ;
		//CRP 03/06/18 Add same side charges
		isb1k1sign = false ;
		isb2k2sign = false ;
		isbMomentum = false ;

		G1=0;
		G2=0;

		//if( Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80 ) isbsign = true;
		//CRP 23/05/18 Avoid cases on which abs(b2) = 5
		if( (Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80) && (fabs(Top1bcharge) < 5 && fabs(Top2bcharge) < 5) ) isbsign = true;
		if( (Top1TotalKaonCharge*Top2TotalKaonCharge < 0) &&  ( fabs(Top1TotalKaonCharge)<5 &&  fabs(Top2TotalKaonCharge)<5)) iskaonsign = true;
		if( (Top1bcharge*Top2TotalKaonCharge < 0) && ( fabs(Top1bcharge)<5 &&  fabs(Top2TotalKaonCharge)<5) )  isb1k2sign = true;
		if( (Top2bcharge*Top1TotalKaonCharge < 0) && ( fabs(Top2bcharge)<5 &&  fabs(Top1TotalKaonCharge)<5) )  isb2k1sign = true;
		if( (Top1bcharge*Top1TotalKaonCharge > 0) && ( fabs(Top1bcharge)<5 &&  fabs(Top1TotalKaonCharge)<5) )  isb1k1sign = true;
		if( (Top2bcharge*Top2TotalKaonCharge > 0) && ( fabs(Top2bcharge)<5 &&  fabs(Top2TotalKaonCharge)<5) )  isb2k2sign = true;

		if( Top1bmomentum > 20 && Top2bmomentum > 20 ) isbMomentum = true;

		if( isbMomentum) {
		
			bmomentum_pass++;

			//if( Top1bcharge==0 || Top2bcharge==0) oneZero++;
			if( Top1bcharge==0) oneZero++;

			if( isbsign ){
				FillandAdd(Top1bcharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
				FillMCRC(hCosMCRCbf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				b1b2++;
			}else if( iskaonsign ){
				FillandAdd(Top1TotalKaonCharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
				FillMCRC(hCosMCRCbf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				k1k2++;
			}else if( isb1k2sign ){
				FillandAdd(Top1bcharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
				FillMCRC(hCosMCRCbf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				b1k2++;
			}else if( isb2k1sign ){
				FillandAdd(Top1TotalKaonCharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
				FillMCRC(hCosMCRCbf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				k1b2++;
				//}
				//CRP 03/06/18 Add same side events
			}else if( isb1k1sign ){
				FillandAdd(Top1TotalKaonCharge, Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
				FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				k1b1++;
			}else if( isb2k2sign ){
				FillandAdd(Top2TotalKaonCharge,Top2costheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
				FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				k2b2++;
			}
			//

		}

	}

	cout << "pass b mom cut = " << bmomentum_pass << endl;
	cout << "oneZero = " << oneZero << endl;

	cout << "number after cuts = " << b1b2+k1k2+b1k2+k1b2+k1b1+k2b2 << endl;
	cout << "vtx1  + vtx2  : " << b1b2 << endl;
	cout << "kaon1 + kaon2 : " << k1k2 << endl;
	cout << "vtx1  + kaon2 : " << b1k2 << endl;
	cout << "kaon1 + vtx2  : " << k1b2 << endl;
	//CRP 03/06/18 Add same side charges
	cout << "kaon1 + vtx1  : " << k1b1 << endl;
	cout << "kaon2 + vtx2  : " << k2b2 << endl;

	topAFB = getAFB( topplus, topminus ) ;
	bottomAFB = getAFB( bottomplus, bottomminus ) ;
	cout << "AFB(top) = " << topAFB << ", AFB(bottom) = " << bottomAFB << endl ;

	TEventList* elistgen = new TEventList( "elistgen", "Generated Event List" ) ;
	tree1->Draw( ">>elistgen", " ( MCTopcostheta != -2 ) && ( MCTopBarcostheta != -2 ) && ( qMCBcostheta[0] != -2 ) && ( qMCBcostheta[1] != -2 ) " ) ;
	int usedgennum = elistgen->GetN() ;
	cout << endl ;

	//work on weight
	fillweight = (double)1/usedgennum ;
	//fillweight = 1 ;

	topplus = 0 ;
	topminus = 0;
	bottomplus = 0 ;
	bottomminus = 0 ;

	for( int i=0 ; i<usedgennum ; i++ ){

		tree1->GetEntry( elistgen->GetEntry(i) ) ;

		htopgen->Fill( MCTopcostheta, fillweight ) ;
		htopgen->Fill( -MCTopBarcostheta, fillweight ) ;
		hbottomgen->Fill( qMCBcostheta[0], fillweight ) ;
		hbottomgen->Fill( -qMCBcostheta[1], fillweight ) ;
		AddAFBvalue( MCTopcostheta, topplus, topminus ) ;
		AddAFBvalue( -MCTopBarcostheta, topplus, topminus ) ;
		AddAFBvalue( qMCBcostheta[0], bottomplus, bottomminus ) ;
		AddAFBvalue( -qMCBcostheta[1], bottomplus, bottomminus ) ;

	}

	topAFBgen = getAFB( topplus, topminus ) ;
	bottomAFBgen = getAFB( bottomplus, bottomminus ) ;


	cout << endl ;
	cout << "-- after vertex recovery --" << endl ;

	rootfilename = rootfiledir + afterfilename ;

	TFile file2( rootfilename.c_str() ) ;
	if( file2.IsZombie() ){
		cout << "cannot open the file '" << rootfilename << "'." << endl ;
		//return 1 ;
		return ;
	}

	TTree* tree2 = (TTree*)file2.Get( treename.c_str() ) ;
	eventnum = tree2->GetEntries() ;
	cout << "eventnum            = " << eventnum << " (100%)" << endl ;
	afterbtag = tree2->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/eventnum << "%)" << endl ;
	afterkinematic = tree2->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/eventnum << "%)" << endl;

	//samesignnum = tree2->GetEntries( btag && kinematic && chi2 && samecharge ) ;
	//samesignKaonbnum = tree2->GetEntries( btag && kinematic && chi2 && sameKaonbcharge ) ;
	//both0num = tree2->GetEntries( btag && kinematic && chi2 && both0charge ) ;

	samesignnum = tree2->GetEntries( btag && kinematic && samecharge ) ;
	//samesignKaonbnum = tree2->GetEntries( btag && kinematic && chi2 && sameKaonbcharge ) ;
	both0num = tree2->GetEntries( btag && kinematic && both0charge ) ;


	//usednum = afterchi2 - samesignnum - both0num ;
	usednum = afterkinematic ;
	cout << endl ;
	cout << "used number = " << usednum << endl ;
	//cout << "same charge sign number = " << samesignnum << endl ;
	//cout << "same b/Kaon1 and bbar/Kaon2 charge sign number = " << samesignKaonbnum << endl ;
	//cout << "both charge 0 number = " << both0num << endl ;

	TEventList *elist2 = new TEventList( "elist2", "Reconstructed Event List" ) ;
	//tree2->Draw( ">>elist2", btag && kinematic && chi2 && !samecharge && !both0charge ) ;
	tree2->Draw( ">>elist2", btag && kinematic ) ;

	tree2->SetBranchAddress( "MCTopcostheta", &MCTopcostheta ) ;
	tree2->SetBranchAddress( "MCTopBarcostheta", &MCTopBarcostheta ) ;
	tree2->SetBranchAddress( "qMCBcostheta", &qMCBcostheta ) ;

	tree2->SetBranchAddress( "Top1bcharge", &Top1bcharge ) ;
	tree2->SetBranchAddress( "Top1costheta", &Top1costheta ) ;
	tree2->SetBranchAddress( "Top1bcostheta", &Top1bcostheta ) ;
	tree2->SetBranchAddress( "Top2bcharge", &Top2bcharge ) ;
	tree2->SetBranchAddress( "Top2costheta", &Top2costheta ) ;
	tree2->SetBranchAddress( "Top2bcostheta", &Top2bcostheta ) ;

	tree2->SetBranchAddress( "Top1TotalKaonCharge", &Top1TotalKaonCharge ) ;
	tree2->SetBranchAddress( "Top2TotalKaonCharge", &Top2TotalKaonCharge ) ;
	tree2->SetBranchAddress( "Top1btag", &Top1btag ) ;
	tree2->SetBranchAddress( "Top2btag", &Top2btag ) ;

	tree2->SetBranchAddress( "Top1mass", &Top1mass ) ;
	tree2->SetBranchAddress( "Top1energy", &Top1energy ) ;
	tree2->SetBranchAddress( "Top2mass", &Top2mass ) ;

	tree2->SetBranchAddress( "Top1bmomentum", &Top1bmomentum ) ;
	tree2->SetBranchAddress( "Top2bmomentum", &Top2bmomentum ) ;

	// we need to work on weight
	//fillweight = (double)1/usednum ;
	fillweight = 1 ;

	topplus = 0 ;
	topminus = 0;
	bottomplus = 0 ;
	bottomminus = 0 ;

	bmomentum_pass = 0;

	b1b2=0;
	k1k2=0;
	b1k2=0;
	k1b2=0;
	//CRP 03/06/18 Add same side charges
	k1b1=0;
	k2b2=0;

	for( int i=0 ; i<usednum ; i++ ){

		tree2->GetEntry( elist2->GetEntry(i) ) ;

		isbsign = false ;
		iskaonsign = false;
		isb1k2sign = false ;
		isb2k1sign = false ;
		//CRP 03/06/18 Add same side charges
		isb1k1sign = false ;
		isb2k2sign = false ;
		isbMomentum = false ;

		if( (Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80) && (fabs(Top1bcharge) < 5 && fabs(Top2bcharge) < 5) ) isbsign = true;
		if( (Top1TotalKaonCharge*Top2TotalKaonCharge < 0) &&  ( fabs(Top1TotalKaonCharge)<5 &&  fabs(Top2TotalKaonCharge)<5)) iskaonsign = true;
		if( (Top1bcharge*Top2TotalKaonCharge < 0) && ( fabs(Top1bcharge)<5 &&  fabs(Top2TotalKaonCharge)<5) )  isb1k2sign = true;
		if( (Top2bcharge*Top1TotalKaonCharge < 0) && ( fabs(Top2bcharge)<5 &&  fabs(Top1TotalKaonCharge)<5) )  isb2k1sign = true;
		if( (Top1bcharge*Top1TotalKaonCharge > 0) && ( fabs(Top1bcharge)<5 &&  fabs(Top1TotalKaonCharge)<5) )  isb1k1sign = true;
		if( (Top2bcharge*Top2TotalKaonCharge > 0) && ( fabs(Top2bcharge)<5 &&  fabs(Top2TotalKaonCharge)<5) )  isb2k2sign = true;
		if( Top1bmomentum > 20 && Top2bmomentum > 20 ) isbMomentum = true;

		G1=0;
		G2=0;

		if(isbMomentum){

			bmomentum_pass++;

			if( isbsign ){
				FillandAdd(Top1bcharge,Top1costheta, Top1bcostheta, topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
				FillMCRC(hCosMCRCaf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				b1b2++;
			}else if( iskaonsign ){
				FillandAdd(Top1TotalKaonCharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
				FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				k1k2++;
			}else if( isb1k2sign ){
				FillandAdd(Top1bcharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
				FillMCRC(hCosMCRCaf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				b1k2++;
			}else if( isb2k1sign ){
				FillandAdd(Top1TotalKaonCharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
				FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
				k1b2++;
				//}
				//CRP 03/06/18 Add same side events
		}else if( isb1k1sign ){
			FillandAdd(Top1TotalKaonCharge,Top1costheta,Top1bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
			FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
			k1b1++;
			//std::cout << "b1k1 cond reached" << std::endl;
		} else if( isb2k2sign ){
			FillandAdd(Top2TotalKaonCharge,Top2costheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
			FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
			//std::cout << "b1k1 cond reached" << std::endl;
			k2b2++;
		}
		//
	}

	}

	cout << "pass b mom cut = " << bmomentum_pass << endl;

	cout << "number after cuts = " << b1b2+k1k2+b1k2+k1b2+k1b1+k2b2 << endl;
	cout << "vtx1  + vtx2  : " << b1b2 << endl;
	cout << "kaon1 + kaon2 : " << k1k2 << endl;
	cout << "vtx1  + kaon2 : " << b1k2 << endl;
	cout << "kaon1 + vtx2  : " << k1b2 << endl;
	//CRP 03/06/18 Add same side charges
	cout << "kaon1 + vtx1  : " << k1b1 << endl;
	cout << "kaon2 + vtx2  : " << k2b2 << endl;

	topAFB = getAFB( topplus, topminus ) ;
	bottomAFB = getAFB( bottomplus, bottomminus ) ;
	cout << "AFB(top) = " << topAFB << ", AFB(bottom) = " << bottomAFB << endl ;

	cout << endl ;
	cout << endl ;
	cout << "-- generated data --" << endl ;
	cout << "used genarated number = " << usedgennum << endl ;
	cout << endl ;
	cout << "AFB(top) = " << topAFBgen << ", AFB(bottom) = " << bottomAFBgen << endl ;


	//Variable to normalise histos
	double norm(0.0);

	c1->cd();

	norm = htop->GetEntries()/2 ;
	htop->Scale(1/norm);
	norm = htopafter->GetEntries()/2 ;
	htopafter->Scale(1/norm);

	htopgen->SetTitle( "bottom polar angle (before:Red after:Green Gen:Blue)" ) ;
	htopgen->GetXaxis()->SetTitleOffset(1.1);
  htopgen->GetXaxis()->SetTitleFont(42);
  htopgen->GetXaxis()->SetTitleSize(0.05);
  htopgen->GetXaxis()->SetLabelSize(0.05);
  htopgen->GetXaxis()->SetLabelOffset(0.015);
	
	htopgen->Draw() ;
	htop->Draw( "SAME" ) ;
	htopafter->Draw( "SAME" ) ;



/*
	c2->cd();
	c2->Divide(2,1) ;
	c2->cd(1);
	hCosMCRCbf->GetYaxis()->SetTitle("MC cos #theta");
	hCosMCRCbf->GetXaxis()->SetTitle("RC cos #theta");
	hCosMCRCbf->Draw("colz");
	c2->cd(2);
	hCosMCRCaf->GetYaxis()->SetTitle("MC cos #theta");
	hCosMCRCaf->GetXaxis()->SetTitle("RC cos #theta");
	hCosMCRCaf->Draw("colz");


	c1->cd();
	c1->Divide(2,1) ;
	c1->cd(1) ;
	htopgen->SetTitle( "top polar angle (before:Red after:Green Gen:Blue)" ) ;
	cout << endl;
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
	pad1->SetBottomMargin(3);
	//pad1->SetGridx();
	pad1->Draw();
	pad1->cd();
	norm = htop->GetEntries()/2 ;

	htop->Scale(1/norm);
	norm = htopafter->GetEntries()/2 ;
	htopafter->Scale(1/norm);

	htopgen->Draw() ;
	htop->Draw( "SAME" ) ;
	htopafter->Draw( "SAME" ) ;


	c1->cd(1);
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.2);
	pad2->SetGridx();
	pad2->SetGridy();
	pad2->Draw();
	pad2->cd();

	TH1F *rpTopBF = (TH1F*)htop->Clone("rpTopBF");
	rpTopBF->SetDirectory(0);
	TH1F *rpTopAF = (TH1F*)htopafter->Clone("rpTopAF");
	rpTopAF->SetDirectory(0);
	//
	rpTopBF->SetMinimum(0.7);
	rpTopBF->SetMaximum(1.3);
	rpTopBF->SetStats(0);
	rpTopBF->Divide(htopgen);
	rpTopBF->SetMarkerColor(2);
	rpTopBF->SetMarkerStyle(20);
	rpTopBF->SetMarkerSize(0.8);
	rpTopBF->Draw("ep");
	rpTopBF->SetTitle("");

	rpTopBF->GetYaxis()->SetTitleSize(20);

	rpTopAF->SetMinimum(0.7);
	rpTopAF->SetMaximum(1.3);
	rpTopAF->SetStats(0);
	rpTopAF->Divide(htopgen);
	rpTopAF->SetMarkerColor(3);
	rpTopAF->SetMarkerStyle(20);
	rpTopAF->SetMarkerSize(0.8);
	rpTopAF->Draw("ep same");
	rpTopAF->SetTitle("");

	rpTopAF->GetYaxis()->SetTitleSize(20);


	c1->cd(2) ;
	hbottomgen->SetTitle( "bottom polar angle (before:Red after:Green Gen:Blue)" ) ;

	TPad *pad3 = new TPad("pad3", "pad3", 0, 0.3, 1, 1.0);
	pad3->SetBottomMargin(3);
	pad3->Draw();
	pad3->cd();

	norm = hbottom->GetEntries()/2 ;
	hbottom->Scale(1/norm);
	norm = hbottomafter->GetEntries()/2 ;
	hbottomafter->Scale(1/norm);

	hbottomgen->Draw() ;
	hbottom->Draw( "SAME" ) ;
	hbottomafter->Draw( "SAME" ) ;

	c1->cd(2);
	TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.3);
	pad4->SetTopMargin(0);
	pad4->SetBottomMargin(0.2);
	pad4->SetGridx();
	pad4->SetGridy();
	pad4->Draw();
	pad4->cd();

	TH1F *rpBottomBF = (TH1F*)hbottom->Clone("rpBottomBF");
	rpBottomBF->SetDirectory(0);
	TH1F *rpBottomAF = (TH1F*)hbottomafter->Clone("rpBottomAF");
	rpBottomAF->SetDirectory(0);
	//
	rpBottomBF->SetMinimum(0.7);
	rpBottomBF->SetMaximum(1.3);
	rpBottomBF->SetStats(0);
	rpBottomBF->Divide(htopgen);
	rpBottomBF->SetMarkerColor(2);
	rpBottomBF->SetMarkerStyle(20);
	rpBottomBF->SetMarkerSize(0.8);
	rpBottomBF->Draw("ep");
	rpBottomBF->SetTitle("");

	rpBottomBF->GetYaxis()->SetTitleSize(100);

	rpBottomAF->SetMinimum(0.7);
	rpBottomAF->SetMaximum(1.3);
	rpBottomAF->SetStats(0);
	rpBottomAF->Divide(htopgen);
	rpBottomAF->SetMarkerColor(3);
	rpBottomAF->SetMarkerStyle(20);
	rpBottomAF->SetMarkerSize(0.8);
	rpBottomAF->Draw("ep same");
	rpBottomAF->SetTitle("");

	rpBottomAF->GetYaxis()->SetTitleSize(100);

	c1->Print( "picture/newpicture.png" ) ;


	file1.Close() ;
	file2.Close() ;
*/


	//return 0;

}




