#include <iostream>
#include <string>
#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>

using namespace std ;


#ifdef __CINT__
int distribution(){
#else
int main( int argc, char **argv ){
	TApplication app( "app", &argc, argv ) ;
#endif


	string rootfilename = "~/run/root_merge/leptonic_yyxylv_eLeR.root" ;
	string treename = "Stats" ;

	TFile file( rootfilename.c_str() ) ;
	if( file.IsZombie() ){
		cout << "cannot open the file" << endl ;
		return 1 ;
	}

	TTree* tree = (TTree*)file.Get( treename.c_str() ) ;
	int eventnum = tree->GetEntries() ;

	float Top1mass, Top2mass, chiHad ;
	tree->SetBranchAddress( "Top1mass", &Top1mass ) ;
	tree->SetBranchAddress( "Top2mass", &Top2mass ) ;
	tree->SetBranchAddress( "chiHad", &chiHad ) ;
	//tree->SetBranchAddress( "chiHad2", &chiHad2 ) ;

	TCanvas* c1 = new TCanvas( "c1", "c1", 1280, 480 ) ;
	TH2F* h1 = new TH2F( "h1", "mass vs chi2 (top1)", 50, 125, 225, 30, 0, 60 ) ;
	TH2F* h2 = new TH2F( "h2", "mass vs chi2 (top2)", 50, 125, 225, 30, 0, 60 ) ;
	h1->SetTitle(0) ;
	h2->SetTitle(0) ;

	for( int i=0 ; i<eventnum ; i++ ){

		tree->GetEntry(i) ;

		h1->Fill( Top1mass, chiHad );
		h2->Fill( Top2mass, chiHad );

	}

	c1->Divide(2,1) ;
	c1->cd(1) ;
	h1->Draw( "COLZ" ) ;
	c1->cd(2) ;
	h2->Draw( "COLZ" ) ;

	c1->WaitPrimitive() ;

	c1->Print( "picture/newpicture.png" ) ;
	c1->Close() ;

	return 0 ;

}
