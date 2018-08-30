#include <iostream>
#include <string>
#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TCut.h>
#include <TEventList.h>
#include <TStyle.h>

using namespace std ;

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

void FillandAdd( int b1 = 0, int b2 = 0, float tcos1 = 0, float tcos2 = 0, float bcos1 = 0, float bcos2 = 0, int& tpl, int& tmi = 0, int& bpl, int& bmi, double weight = 0, TH1F* top = 0, TH1F* bottom = 0){

		if( b1 < 0 ){  //Top1 = top, Top2 = antitop, Top1b = bottom, Top2b = antibottom
			top->Fill( tcos1, weight ) ;
			top->Fill( -tcos2, weight ) ;
			bottom->Fill( bcos1, weight ) ;
			bottom->Fill( -bcos2, weight ) ;
			AddAFBvalue( tcos1, tpl, tmi ) ;
			AddAFBvalue( -tcos2, tpl, tmi ) ;
			AddAFBvalue( bcos1, bpl, bmi ) ;
			AddAFBvalue( -bcos2, bpl, bmi ) ;
		}else if( b1 > 0 ){  //Top1 = antitop, Top2 = top, Top1b = antibottom, Top2b = bottom
			top->Fill( -tcos1, weight ) ;
			top->Fill( tcos2, weight ) ;
			bottom->Fill( -bcos1, weight ) ;
			bottom->Fill( bcos2, weight ) ;
			AddAFBvalue( -tcos1, tpl, tmi ) ;
			AddAFBvalue( tcos2, tpl, tmi ) ;
			AddAFBvalue( -bcos1, bpl, bmi ) ;
			AddAFBvalue( bcos2, bpl, bmi ) ;
		}else if( b2 > 0 ){  //Top1 = top, Top2 = antitop, Top1b = bottom, Top2b = antibottom
			top->Fill( tcos1, weight ) ;
			top->Fill( -tcos2, weight ) ;
			bottom->Fill( bcos1, weight ) ;
			bottom->Fill( -bcos2, weight ) ;
			AddAFBvalue( tcos1, tpl, tmi ) ;
			AddAFBvalue( -tcos2, tpl, tmi ) ;
			AddAFBvalue( bcos1, bpl, bmi ) ;
			AddAFBvalue( -bcos2, bpl, bmi ) ;
		}else{  //Top1 = antitop, Top2 = top, Top1b = antibottom, Top2b = bottom
			top->Fill( -tcos1, weight ) ;
			top->Fill( tcos2, weight ) ;
			bottom->Fill( -bcos1, weight ) ;
			bottom->Fill( bcos2, weight ) ;
			AddAFBvalue( -tcos1, tpl, tmi ) ;
			AddAFBvalue( tcos2, tpl, tmi ) ;
			AddAFBvalue( -bcos1, bpl, bmi ) ;
			AddAFBvalue( bcos2, bpl, bmi ) ;
		}

}


#ifdef __CINT__
int polar_angle_beforeafter(){
#else
int main( int argc, char **argv ){
	TApplication app( "app", &argc, argv ) ;
#endif

	// calling root files
	string rootfiledir = "../root_merge/" ;
	string beforefilename = "hadronic_eLpR_kekcc_500k.root" ;
	string afterfilename = "aftervertexrestore_" + beforefilename ;
	string rootfilename ;
	string treename = "Stats" ;

	rootfilename = rootfiledir + beforefilename ;
	TFile file1( rootfilename.c_str() ) ;
	if( file1.IsZombie() ){
		cout << "cannot open the file '" << rootfilename << "'." << endl ;
		return 1 ;
	}

	gStyle->SetOptStat(0) ;

	// declaring variables
	int Top1bcharge, Top2bcharge ;
	float Top1costheta, Top1bcostheta, Top2costheta, Top2bcostheta ;
	int Top1TotalKaonCharge, Top2TotalKaonCharge ;
	float Top1bmomentum, Top2bmomentum;
	float Top1btag, Top2btag;
	float Top1energy, Top1mass;
	float Top2mass, Top2energy;
	float MCTopcostheta, MCTopBarcostheta ;
	float qMCBcostheta[2] ;
	int topplus = 0, topminus = 0, bottomplus = 0, bottomminus = 0 ;
	float topAFB, bottomAFB, topAFBgen, bottomAFBgen ;

	// setting precuts
	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.30 ) " ;
	TCut chi2_1 = " chiTopMass1 + chiTopE1 + chiPbstar1 < 30 " ;
	TCut chi2_2 = " chiTopMass2 + chiTopE2 + chiPbstar2 < 30 " ;
	TCut chi2 = chi2_1 + chi2_2 ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) && ( Top2mass > 140 ) && ( Top2mass < 210 ) " ;
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
	int afterchi2 = tree1->GetEntries( btag && kinematic && chi2 ) ;
	cout << "after chi2 cut      = " << afterchi2 << " (" << (float)100*afterchi2/eventnum << "%)" << endl;

	// number of events after precuts
	int samesignnum = tree1->GetEntries( btag && kinematic && chi2 && samecharge ) ;
	//int samesignKaonbnum = tree1->GetEntries( btag && kinematic && chi2 && sameKaonbcharge ) ;
	int both0num = tree1->GetEntries( btag && kinematic && chi2 && both0charge ) ;
	//int usednum = afterchi2 - samesignnum - both0num ;
	int usednum = afterchi2 ;

	cout << endl ;
	cout << "used number = " << usednum << endl ; // number of events before cuts (not precuts!)

	TEventList *elist1 = new TEventList( "elist1", "Reconstructed Event List" ) ;
	//tree1->Draw( ">>elist1", btag && kinematic && chi2 && !samecharge  && !both0charge ) ;
	tree1->Draw( ">>elist1", btag && kinematic && chi2 ) ;
	//usednum = elist->GetN() ;
	//cout << "used number = " << usednum << endl ;

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
	tree1->SetBranchAddress( "Top2energy", &Top2energy ) ;

	tree1->SetBranchAddress( "Top1bmomentum", &Top1bmomentum ) ;
	tree1->SetBranchAddress( "Top2bmomentum", &Top2bmomentum ) ;

	// decleir canvas and histograms
	TCanvas* c1 = new TCanvas( "c1", "c1", 1280, 480 ) ;
	TCanvas* c2 = new TCanvas( "c2", "c2", 680, 480 ) ;
	TCanvas* c3 = new TCanvas( "c3", "c3", 1280, 480 ) ;
	TH1F* htop = new TH1F( "htop", "top polar angle (reconstructed)", 40, -1, 1 ) ;
	htop->SetMinimum(0) ;
	htop->SetLineColor(2) ;
	TH1F* hbottom = new TH1F( "hbottom", "bottom polar angle (reconstructed)", 40, -1, 1 ) ;
	hbottom->SetMinimum(0) ;
	hbottom->SetLineColor(2) ;
	TH1F* htopgen = new TH1F( "htopgen", "top polar angle (generated)", 40, -1, 1 ) ;
	htopgen->SetMinimum(0) ;
	htopgen->SetMaximum(0.11) ;
	htopgen->SetLineColor(4) ;
	TH1F* hbottomgen = new TH1F( "hbottomgen", "bottom polar angle (generated)", 40, -1, 1 ) ;
	hbottomgen->SetMinimum(0) ;
	hbottomgen->SetMaximum(0.11) ;
	hbottomgen->SetLineColor(4) ;
	TH1F* hLzFbf = new TH1F( "hLzFbf", "Lorentz factor #gamma", 100, 2, 4 ) ;
	hLzFbf->SetLineColor(2) ;
	TH1F* hLzFaf = new TH1F( "hLzFaf", "Lorentz factor #gamma", 100, 2, 4 ) ;
	hLzFaf->SetLineColor(3) ;
	TH2F* hCosMCRCbf = new TH2F( "hCosMCRCbf", "Top cos#theta MC vs RC (before vtx recovery)", 100, -1, 1, 100, -1, 1 ) ;
	TH2F* hCosMCRCaf = new TH2F( "hCosMCRCaf", "Top cos#theta MC vs RC (after vtx recovery)", 100, -1, 1, 100, -1, 1 ) ;

	// normalize histogram to have proper error
	htop->Sumw2();
	htopgen->Sumw2();
	hbottom->Sumw2();
	hbottomgen->Sumw2();

	//double fillweight = (double)1/usednum ;
	double fillweight = 1 ;
	
	// in-loop varibale declaration
	bool isbsign = false, iskaonsign = false;
	bool isb1k2sign = false;
	bool isb2k1sign = false;
	bool isbMomentum = false;
	
	int b1b2=0,k1k2=0,b1k2=0,k1b2=0;
	float G1=0,G2=0;

	// event loop (before vtx restore)
	for( int i=0 ; i<usednum ; i++ ){

		tree1->GetEntry( elist1->GetEntry(i) ) ;

		isbsign = false ;
		iskaonsign = false;
		isb1k2sign = false ;
		isb2k1sign = false ;
		isbMomentum = false ;

		G1=0;
		G2=0;

		if( Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80 ) isbsign = true;
		if( Top1TotalKaonCharge*Top2TotalKaonCharge < 0 ) iskaonsign = true;
		if( Top1bcharge*Top2TotalKaonCharge < 0 ) isb1k2sign = true;
		if( Top2bcharge*Top1TotalKaonCharge < 0 ) isb2k1sign = true;
		if( Top1bmomentum > 30 && Top2bmomentum > 30 ) isbMomentum = true;

		if( isbsign || iskaonsign || isb1k2sign || isb2k1sign ){
			G1 = LorentzF(Top1energy,Top1mass);
			G2 = LorentzF(Top2energy,Top2mass);
			hLzFbf->Fill(G1+G2);
		}

		//if(G1+G2>2.6 && isbMomentum){
			
			if( isbsign ){
					FillandAdd(Top1bcharge,Top2bcharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					FillMCRC(hCosMCRCbf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					b1b2++;
			}else if( iskaonsign ){
					FillandAdd(Top1TotalKaonCharge,Top2TotalKaonCharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					FillMCRC(hCosMCRCbf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					k1k2++;
			}else if( isb1k2sign ){
					FillandAdd(Top1bcharge,Top2TotalKaonCharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					FillMCRC(hCosMCRCbf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					b1k2++;
			}else if( isb2k1sign ){
					FillandAdd(Top1TotalKaonCharge,Top2bcharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					FillMCRC(hCosMCRCbf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					k1b2++;
			}
			
		//}

	}

	cout << "number after cuts = " << b1b2+k1k2+b1k2+k1b2 << endl;
	cout << "vtx1  + vtx2  : " << b1b2 << endl;
	cout << "kaon1 + kaon2 : " << k1k2 << endl;
	cout << "vtx1  + kaon2 : " << b1k2 << endl;
	cout << "kaon1 + vtx2  : " << k1b2 << endl;

	topAFB = getAFB( topplus, topminus ) ;
	bottomAFB = getAFB( bottomplus, bottomminus ) ;
	cout << "AFB(top) = " << topAFB << ", AFB(bottom) = " << bottomAFB << endl ;

	//tree1->SetBranchStatus( "Top*", 0 ) ;
	//tree1->SetBranchAddress( "MCTopcostheta", &MCTopcostheta ) ;
	//tree1->SetBranchAddress( "MCTopBarcostheta", &MCTopBarcostheta ) ;
	//tree1->SetBranchAddress( "qMCBcostheta", &qMCBcostheta ) ;

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
		return 1 ;
	}

	TTree* tree2 = (TTree*)file2.Get( treename.c_str() ) ;
	eventnum = tree2->GetEntries() ;
	cout << "eventnum            = " << eventnum << " (100%)" << endl ;
	afterbtag = tree2->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/eventnum << "%)" << endl ;
	afterkinematic = tree2->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/eventnum << "%)" << endl;
	afterchi2 = tree2->GetEntries( btag && kinematic && chi2 ) ;
	cout << "after chi2 cut      = " << afterchi2 << " (" << (float)100*afterchi2/eventnum << "%)" << endl;

	samesignnum = tree2->GetEntries( btag && kinematic && chi2 && samecharge ) ;
	//samesignKaonbnum = tree2->GetEntries( btag && kinematic && chi2 && sameKaonbcharge ) ;
	both0num = tree2->GetEntries( btag && kinematic && chi2 && both0charge ) ;
	//usednum = afterchi2 - samesignnum - both0num ;
	usednum = afterchi2 ;
	cout << endl ;
	cout << "used number = " << usednum << endl ;
	//cout << "same charge sign number = " << samesignnum << endl ;
	//cout << "same b/Kaon1 and bbar/Kaon2 charge sign number = " << samesignKaonbnum << endl ;
	//cout << "both charge 0 number = " << both0num << endl ;

	TEventList *elist2 = new TEventList( "elist2", "Reconstructed Event List" ) ;
	//tree2->Draw( ">>elist2", btag && kinematic && chi2 && !samecharge && !both0charge ) ;
	tree2->Draw( ">>elist2", btag && kinematic && chi2 ) ;
	//usednum = elist2->GetN() ;
	//cout << "used number = " << usednum << endl ;

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
	tree2->SetBranchAddress( "Top2energy", &Top2energy ) ;
	
	tree2->SetBranchAddress( "Top1bmomentum", &Top1bmomentum ) ;
	tree2->SetBranchAddress( "Top2bmomentum", &Top2bmomentum ) ;
	
	TH1F* htopafter = new TH1F( "htopafter", "top polar angle (after vertex restorer)", 40, -1, 1 ) ;
	htopafter->SetMinimum(0) ;
	htopafter->SetLineColor(3) ;
	TH1F* hbottomafter = new TH1F( "hbottomafter", "bottom polar angle (after vertex restorer)", 40, -1, 1 ) ;
	hbottomafter->SetMinimum(0) ;
	hbottomafter->SetLineColor(3) ;

	htopafter->Sumw2();
	hbottomafter->Sumw2();

	// we need to work on weight
	//fillweight = (double)1/usednum ;
	fillweight = 1 ;

	topplus = 0 ;
	topminus = 0;
	bottomplus = 0 ;
	bottomminus = 0 ;

	b1b2=0;
	k1k2=0;
	b1k2=0;
	k1b2=0;

	for( int i=0 ; i<usednum ; i++ ){

		tree2->GetEntry( elist2->GetEntry(i) ) ;

		isbsign = false ;
		iskaonsign = false;
		isb1k2sign = false ;
		isb2k1sign = false ;
		isbMomentum = false ;

		if( Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80 ) isbsign = true;
		if( Top1TotalKaonCharge*Top2TotalKaonCharge < 0 ) iskaonsign = true;
		if( Top1bcharge*Top2TotalKaonCharge < 0 ) isb1k2sign = true;
		if( Top2bcharge*Top1TotalKaonCharge < 0 ) isb2k1sign = true;
		if( Top1bmomentum > 30 && Top2bmomentum > 30 ) isbMomentum = true;

		G1=0;
		G2=0;
		
		if( isbsign || iskaonsign || isb1k2sign || isb2k1sign ){
			G1 = LorentzF(Top1energy,Top1mass);
			G2 = LorentzF(Top2energy,Top2mass);
			hLzFaf->Fill(G1+G2);
		}

		//if(G1+G2>2.6 && isbMomentum){
			if( isbsign ){
					FillandAdd(Top1bcharge,Top2bcharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
					FillMCRC(hCosMCRCaf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					b1b2++;
			}else if( iskaonsign ){
					FillandAdd(Top1TotalKaonCharge,Top2TotalKaonCharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
					FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					k1k2++;
			}else if( isb1k2sign ){
					FillandAdd(Top1bcharge,Top2TotalKaonCharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
					FillMCRC(hCosMCRCaf,Top1bcharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					b1k2++;
			}else if( isb2k1sign ){
					FillandAdd(Top1TotalKaonCharge,Top2bcharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htopafter,hbottomafter);
					FillMCRC(hCosMCRCaf,Top1TotalKaonCharge,Top1costheta,Top2costheta,MCTopcostheta,MCTopBarcostheta);
					k1b2++;
			}

		//}

	}

	cout << "number after cuts = " << b1b2+k1k2+b1k2+k1b2 << endl;
	cout << "vtx1  + vtx2  : " << b1b2 << endl;
	cout << "kaon1 + kaon2 : " << k1k2 << endl;
	cout << "vtx1  + kaon2 : " << b1k2 << endl;
	cout << "kaon1 + vtx2  : " << k1b2 << endl;

	topAFB = getAFB( topplus, topminus ) ;
	bottomAFB = getAFB( bottomplus, bottomminus ) ;
	cout << "AFB(top) = " << topAFB << ", AFB(bottom) = " << bottomAFB << endl ;

	cout << endl ;
	cout << endl ;
	cout << "-- generated data --" << endl ;
	cout << "used genarated number = " << usedgennum << endl ;
	cout << endl ;
	cout << "AFB(top) = " << topAFBgen << ", AFB(bottom) = " << bottomAFBgen << endl ;

	c1->Divide(2,1) ;
	c3->Divide(2,1) ;

	c1->cd(1) ;
	htopgen->SetTitle( "top polar angle (before:Red after:Green Gen:Blue)" ) ;

	cout << endl;

	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
	pad1->SetBottomMargin(3);
	//pad1->SetGridx();
	pad1->Draw();
	pad1->cd();
	
	double norm = htop->GetEntries()/2 ;

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
	TH1F *rpTopAF = (TH1F*)htopafter->Clone("rpTopAF");
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
	TH1F *rpBottomAF = (TH1F*)hbottomafter->Clone("rpBottomAF");
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

	c2->cd();
	norm = hLzFbf->GetEntries();
	hLzFbf->Scale(1/norm);
	norm = hLzFaf->GetEntries();
	hLzFaf->Scale(1/norm);

	hLzFbf->Draw();
	hLzFaf->Draw("same");

	c3->cd(1);
	hCosMCRCbf->GetYaxis()->SetTitle("MC cos #theta");
	hCosMCRCbf->GetXaxis()->SetTitle("RC cos #theta");
	hCosMCRCbf->Draw("colz");
	c3->cd(2);
	hCosMCRCaf->GetYaxis()->SetTitle("MC cos #theta");
	hCosMCRCaf->GetXaxis()->SetTitle("RC cos #theta");
	hCosMCRCaf->Draw("colz");
	
	c1->WaitPrimitive() ;

	c1->Print( "picture/newpicture.png" ) ;
	c1->Close() ;

	file1.Close() ;
	file2.Close() ;


	

	return 0;

}




