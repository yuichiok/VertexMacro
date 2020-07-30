#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;
void Topmass()
{
	int token=0;

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

	// File Selector

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/full_hadronic/input/record.txt" );

	while( fs.input(in) ){
		rootfiles.push_back(fs);
	}

	int nrootfiles = 0;
	nrootfiles = rootfiles.size();
  
	cout << "nfiles = " << nrootfiles << endl;

	std::cout << "Choose a file from below:" << std::endl;
	for( int i=0; i < nrootfiles; i++){
		std::cout << i << ": " << rootfiles[i].info() << endl;
	}

	std::cout << "Enter code: ";
	std::cin >> token;
	std::cout << std::endl;

	std::string filename = rootfiles[token].filename();
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	TTree * Stats      = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree    = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary    = (TTree*) file->Get( "Summary" );

	// Histograms
	
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * h_Topmass = new TH1F("h_Topmass", ";Mass (GeV);Events / 1 GeV", 250, 0., 250.);
	TH1F * h_Wmass = new TH1F("h_Wmass", ";Mass (GeV);Events / 1 GeV", 250, 0., 250.);

	// Histogram style

	//TGaxis::SetMaxDigits(3);

	h_Topmass->SetLineWidth(3);
	h_Topmass->SetLineStyle(1);
	h_Topmass->SetLineColor(kRed+1);

	h_Wmass->SetLineWidth(3);
	h_Wmass->SetLineStyle(1);
	h_Wmass->SetLineColor(kBlue+1);

	int n_Tentry = Stats->Draw("MCTopmass >> h_Topmass", "");
	int n_Wentry = Stats->Draw("MCWplusmass >> h_Wmass", "");

  ////////////// Fitting //////////////
	TF1 * f_Topmass = new TF1("f_Topmass","gaus",0,150);

	f_Topmass->SetLineColor(kRed);
	f_Topmass->SetLineStyle(3);
	h_Topmass->Fit("f_Topmass","Q");

	h_Topmass->SetMinimum(0);
	h_Topmass->Draw("");
	f_Topmass->Draw("same");

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();
	
}

