#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

void singleTop_jet()
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
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record2.txt" );

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

	TTree * Stats = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary = (TTree*) file->Get( "Summary" );

	// Histograms
	
	TCanvas * c1			= new TCanvas("c1", "jetE1",0,0,500,500);
	TH1F * jetE1all			= new TH1F("jetE1all",";jetE_{B}; / Entries",200,0,200);
	jetE1all->Sumw2();
	TH1F * jetE1			= new TH1F("jetE1",";jetE_{B}; / Entries",200,0,200);
	jetE1->Sumw2();

	TH1F * jetE2all			= new TH1F("jetE2all",";jetE_{B}; / Entries",200,0,200);
	jetE2all->Sumw2();
	TH1F * jetE2			= new TH1F("jetE2",";jetE_{B}; / Entries",200,0,200);
	jetE2->Sumw2();


	////////////// Cuts //////////////

	// Methods selection
	TCut methodAll = "methodTaken > 0";
	TCut method1 = "methodTaken == 1";
	TCut method2 = "methodTaken == 2";
	TCut method3 = "methodTaken == 3";
	TCut method4 = "methodTaken == 4";
	TCut method5 = "methodTaken == 5";
	TCut method6 = "methodTaken == 6";
	TCut method7 = "methodTaken == 7";

	TCut MCcos2  = "qMCcostheta > -2";
	TCut MCcos09 = "qMCcostheta < -0.9"; 
	TCut bmom1	 = "Top1bmomentum > 0";
	TCut bmom2	 = "Top2bmomentum > 0";
	TCut singleTopFlagON = "singletopFlag == 1";

	TGaxis::SetMaxDigits(3);

	jetE1all->SetLineWidth(3);
	jetE1all->SetLineStyle(1);
	jetE1all->SetLineColor(kGray+1);

	jetE1->SetLineWidth(3);
	jetE1->SetLineStyle(1);

	jetE2all->SetLineWidth(3);
	jetE2all->SetLineStyle(1);
	jetE2all->SetLineColor(kGray+1);

	jetE2->SetLineWidth(3);
	jetE2->SetLineStyle(1);

	int bjet1all	= Stats->Draw("jet_E[0] >> jetE1all",MCcos2);
	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + bmom1 + singleTopFlagON + method1);
	//int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + MCcos09 + bmom1 + singleTopFlagON + (method1 || method2 || method3 || method4 || method7) );
	int bjet2all	= Stats->Draw("jet_E[1] >> jetE2all",MCcos2);
	int bjet2 		= Stats->Draw("jet_E[1] >> jetE2", MCcos2 + bmom2 + singleTopFlagON + method1);
	//int bjet2 		= Stats->Draw("jet_E[1] >> jetE2", MCcos2 + MCcos09 + bmom2 + singleTopFlagON + (method1 || method2 || method3 || method4 || method7) );


	cout << jetE1all->GetEntries() << "\n";
	cout << jetE1->GetEntries() << "\n";
	cout << jetE2all->GetEntries() << "\n";
	cout << jetE2->GetEntries() << "\n";


	jetE1all->Scale( 1 / jetE1all->GetEntries() );
	jetE1->Scale( 1 / jetE1->GetEntries() );
	jetE2all->Scale( 1 / jetE2all->GetEntries() );
	jetE2->Scale( 1 / jetE2->GetEntries() );


	jetE1all->SetMinimum(0);
	jetE1->SetMinimum(0);
	jetE2all->SetMinimum(0);
	jetE2->SetMinimum(0);


	jetE1->Draw("he");
	jetE1all->Draw("hsame");

	TLegend *leg = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(jetE1all,"All Parton Level","l");
	leg->AddEntry(jetE1,"Single Top Tagged","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	c1->Update();

// jetE2

	TCanvas * c2			= new TCanvas("c2", "jetE2",0,0,500,500);

	jetE2->Draw("he");
	jetE2all->Draw("hsame");

	TLegend *leg2 = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(jetE2all,"All Parton Level","l");
	leg2->AddEntry(jetE2,"Single Top Tagged","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();

	c2->Update();










}

