#include <iostream>
#include <string>
#include <sstream>
//#include <vector>
#include <TFile.h>
#include <TApplication.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1.h>
#include <TCut.h>

using namespace std ;



#ifdef __CINT__
int cut(){
#else
int main( int argc, char **argv ){
	TApplication app( "app", &argc, argv ) ;
#endif

	string rootfilename = "rootfile/aftervertexrestore_hadronic_eLpR_iso_lep_lcut.root" ;
	string treename = "Stats" ;
	string branchname1 = "Top1mass" ;
	string branchname2 = "qMCBcostheta[0]" ;
	string histtitle = "topmass" ;

	bool singlehist = true ;

	bool setframe = true ;
	int div = 80 ;
	double xmin = 135 ;
	double xmax = 215 ;

	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.30 ) " ;
	TCut chi2_1 = " chiTopMass1 + chiTopE1 + chiPbstar1 < 30 " ;
	TCut chi2_2 = " chiTopMass2 + chiTopE2 + chiPbstar2 < 30 " ;
	TCut chi2 = chi2_1 + chi2_2 ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) && ( Top2mass > 140 ) && ( Top2mass < 210 ) " ;
	TCut samecharge = " Top1bcharge * Top2bcharge > 0 " ;
	TCut zerocharge = " ( Top1bcharge == 0 ) || ( Top2bcharge == 0 ) " ;


	TFile file( rootfilename.c_str() ) ;
	if( file.IsZombie() ){
		cout << "cannot open the file" << endl ;
		return 1 ;
	}

	TTree* tree = (TTree*)file.Get( treename.c_str() ) ;
	int eventnum = tree->GetEntries() ;
	cout << "eventnum            = " << eventnum << " (100%)" << endl ;
	int afterbtag = tree->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/eventnum << "%)" << endl ;
	int afterkinematic = tree->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/eventnum << "%)" << endl;
	int afterchi2 = tree->GetEntries( btag && kinematic && chi2 ) ;
	cout << "after chi2 cut      = " << afterchi2 << " (" << (float)100*afterchi2/eventnum << "%)" << endl;
	int samechargenum = tree->GetEntries( btag && kinematic && chi2 && samecharge ) ;
	cout << "same charge num     = " << samechargenum << " (" << (float)100*samechargenum/afterchi2 << "%)" << endl;
	int zerochargenum = tree->GetEntries( btag && kinematic && chi2 && zerocharge ) ;
	cout << "zero charge num     = " << zerochargenum << " (" << (float)100*zerochargenum/afterchi2 << "%)" << endl;
	cout << "used num            = " << afterchi2 - samechargenum - zerochargenum << " (" << (float)100*(afterchi2-samechargenum-zerochargenum)/afterchi2 << "%)" << endl;


	TCanvas* c1 = new TCanvas( "c1", "c1" ) ;

	stringstream ssdrawoption1 ;
	ssdrawoption1 << branchname1 << " >> h1" ;
	if( setframe ){
		ssdrawoption1 << "( " << div << ", " << xmin << ", " << xmax << " )" ;
	}
	string drawoption1 = ssdrawoption1.str() ;
	//tree->Draw( drawoption1.c_str(), btag && chi2 && kinematic ) ;
	tree->Draw( drawoption1.c_str(), btag && kinematic && chi2 && !samecharge && !zerocharge ) ;

	TH1F* h1 = (TH1F*)gDirectory->Get( "h1" ) ;

	h1->SetTitle( histtitle.c_str() ) ;
	h1->SetTitle(0) ;
	h1->SetMinimum(0) ;
	h1->SetMaximum(6000) ;
	h1->SetLineColor(2) ;

	cout << "h1 is ready..." << endl;

	if( !singlehist ){

		string drawoption2 = branchname2 + " >> h2" ;
		tree->Draw( drawoption2.c_str(), "", "SAME" ) ;

		TH1F* h2 = (TH1F*)gDirectory->Get( "h2" ) ;

		h2->SetLineColor(4) ;

		cout << "h2 is ready..." << endl;

	}

	c1->WaitPrimitive() ;

	c1->Print( "picture/newpicture.png" ) ;
	c1->Close() ;

	return 0;

}



