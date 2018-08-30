#include <iostream>
#include <string>
#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1.h>
#include <TCut.h>
#include <TEventList.h>
#include <TStyle.h>

using namespace std ;

#ifdef __CINT__
int polar_angle_main(){
#else
int main( int argc, char **argv ){
	TApplication app( "app", &argc, argv ) ;
#endif


	string rootfiledir = "../../root_merge/" ;
	string beforefilename = "hadronic_eLpR_kekcc_500k.root" ;
	string afterfilename = "aftervertexrestore_" + beforefilename ;
	string rootfilename ;

	rootfilename = rootfiledir + beforefilename ;
	
	gROOT->ProcessLine(".L polar_angle_before.cpp");
	//gROOT->ProcessLine(".L polar_angle_after.cpp");
	polar_angle_before(rootfilename);


	return 0;

}




