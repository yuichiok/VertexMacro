#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"

//#include "rootlogon.C"
//#include "bilo_sty.C"
#define MAXV 8

using namespace std;

void WTmass()
{

	// initialize variables
	int styl = 0;
	int cx   = 500;
	double Legx1 = 0.20;
	double Legx2 = 0.6;

	int token=0;

	int bin_e = 250;
	int max = 250;

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

	
	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record2.txt" );
	//std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/test.txt" );

	while( fs.input(in) ){
		rootfiles.push_back(fs);
	}

	int nrootfiles = 0;
	nrootfiles = rootfiles.size();

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

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);
	TH1F * h_W1mass = new TH1F("h_W1mass", ";Mass (GeV); Events / 1 GeV", bin_e,0,max);
	h_W1mass->Sumw2();
	TH1F * h_W2mass = new TH1F("h_W2mass", ";Mass (GeV); Events / 1 GeV", bin_e,0,max);
	h_W2mass->Sumw2();
	TH1F * h_T1mass = new TH1F("h_T1mass", ";Mass (GeV); Events / 1 GeV", bin_e,0,max);
	h_T1mass->Sumw2();
	TH1F * h_T2mass = new TH1F("h_T2mass", ";Mass (GeV); Events / 1 GeV", bin_e,0,max);
	h_T2mass->Sumw2();


	TGaxis::SetMaxDigits(3);

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

	h_W1mass->SetLineWidth(3);
	h_W2mass->SetLineWidth(3);
	h_T1mass->SetLineWidth(3);
	h_T2mass->SetLineWidth(3);

	h_W2mass->SetLineStyle(2);
	h_T2mass->SetLineStyle(2);

	h_W1mass->SetLineColor(kBlue+1);
	h_W2mass->SetLineColor(kBlue+1);
	h_T1mass->SetLineColor(kRed+1);
	h_T2mass->SetLineColor(kRed+1);


	// Selection lists
	TCut thru = "Thrust < 0.9";
	TCut hadM = "hadMass > 180 && hadMass < 420";
	TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";
	TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
	TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

	// full-hadronic
	TCut pcut2 = "Top1bmomentum > 30 && Top2bmomentum > 30";

	// Methods selection
	TCut methodAll = "methodTaken > 0";
	TCut method1 = "methodTaken == 1";
	TCut method2 = "methodTaken == 2";
	TCut method3 = "methodTaken == 3";
	TCut method4 = "methodTaken == 4";
	TCut method5 = "methodTaken == 5";
	TCut method6 = "methodTaken == 6";
	TCut method7 = "methodTaken == 7";

	// Total cut applied
	TCut cuts = rcTW + hadM + pcut + gcut + methodAll;
	//TCut cuts2 = rcTW + hadM + pcut2 + methodAll;


	int n_W1mass = normaltree->Draw("W1mass >> h_W1mass", cuts);
	int n_W2mass = normaltree->Draw("W2mass >> h_W2mass", cuts);

	int n_T1mass = normaltree->Draw("Top1mass >> h_T1mass", cuts);
	int n_T2mass = normaltree->Draw("Top2mass >> h_T2mass", cuts);


	// normalize
	h_W1mass->Scale(1 / h_W1mass->GetEntries());
	h_W2mass->Scale(1 / h_W2mass->GetEntries());
	h_T1mass->Scale(1 / h_T1mass->GetEntries());
	h_T2mass->Scale(1 / h_T2mass->GetEntries());

	// Draw
	h_W1mass->Draw("hist");
	h_W2mass->Draw("hsame");
	h_T1mass->Draw("hsame");
	h_T2mass->Draw("hsame");

	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	// semiLep
	/*
	leg->AddEntry(h_W1mass,"Hadronic W mass","l");
	leg->AddEntry(h_W2mass,"Leptonic W mass","l");
	leg->AddEntry(h_T1mass,"Hadronic top mass","l");
	leg->AddEntry(h_T2mass,"Leptonic top mass","l");
	*/
	// fullHad
	leg->AddEntry(h_W1mass,"W1 mass","l");
	leg->AddEntry(h_W2mass,"W2 mass","l");
	leg->AddEntry(h_T1mass,"Top1 mass","l");
	leg->AddEntry(h_T2mass,"Top2 mass","l");

	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();

	
}

