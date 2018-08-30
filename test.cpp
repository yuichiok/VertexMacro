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

using namespace std ;


//#ifdef __CINT__
void test(){
		
		//opening the root files
		string rootfiledir = "/home/ilc/yokugawa/run/root_merge/";
		string beforefilename = "leptonic_yyxylv_eLeR.root";
		string rootfilename ;
		string treename = "Summary" ;

		rootfilename = rootfiledir + beforefilename ;
		cout << "filename '" << rootfilename << "'." << endl ;
		TFile file1( rootfilename.c_str() ) ;
		if( file1.IsZombie() ){
				cout << "cannot open the file '" << rootfilename << "'." << endl ;
				return 1 ;
		}

		// getting tree informations
		TTree* tree1 = (TTree*)file1.Get( treename.c_str() ) ;
		int eventnum = tree1->GetEntries() ;
		cout << "eventnum            = " << eventnum << " (100%)" << endl ;

		tree1->Scan("nEvents");

		file1.Close() ;

}




