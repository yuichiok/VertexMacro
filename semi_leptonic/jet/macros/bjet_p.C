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
void bjet_p()
{

	// initialize variables
	int styl = 0;
	int cx   = 500;
	double Legx1 = 0.20;
	double Legx2 = 0.6;

	int token_l5=0;
  int token_s5=0;

	int bin_e = 200;
	int max_e = 200;

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
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record.txt" );
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

	std::cout << "Enter code (l5): ";
	std::cin >> token_l5;
	std::cout << "Enter code (s5): ";
	std::cin >> token_s5;

	std::cout << std::endl;


	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);

  ////////////// Cuts //////////////

	// Selection lists
	TCut thru = "Thrust < 0.9";
	TCut hadM = "hadMass > 180 && hadMass < 420";
	TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";
	TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
	TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

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

	TCut fcuts = "qCostheta > 0" + cuts;
	TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;


	////////////// Detector Model LARGE //////////////

	std::string filename_l5 = rootfiles[token_l5].filename();
	cout << "Processing : " << filename_l5 << " ..." << endl;

	TFile * file_l5 = TFile::Open(filename_l5.c_str());

	TH1F * bjet_p_l5 = new TH1F("bjet_p_l5", ";p_{b};Entries", bin_e,0,max_e);
	TGaxis::SetMaxDigits(3);

	TTree * normaltree_l5 = (TTree*) file_l5->Get( "Stats" ) ;

	int bjet1_l5  = normaltree_l5->Draw("Top1bmomentum >> bjet_p_l5", fcuts||bcuts);
	int bjet2_l5  = normaltree_l5->Draw("Top2bmomentum >> +bjet_p_l5", fcuts||bcuts);


	////////////// Detector Model SMALL //////////////

	std::string filename_s5 = rootfiles[token_s5].filename();
	cout << "Processing : " << filename_s5 << " ..." << endl;

	TFile * file_s5 = TFile::Open(filename_s5.c_str());

	TH1F * bjet_p_s5 = new TH1F("bjet_p_s5", ";p_{b};Entries", bin_e,0,max_e);

	TTree * normaltree_s5 = (TTree*) file_s5->Get( "Stats" ) ;

	int bjet1_s5  = normaltree_s5->Draw("Top1bmomentum >> bjet_p_s5", fcuts||bcuts);
	int bjet2_s5  = normaltree_s5->Draw("Top2bmomentum >> +bjet_p_s5", fcuts||bcuts);


  ////////////// Style Setting //////////////

	bjet_p_l5->SetLineWidth(2);
	bjet_p_l5->SetLineStyle(1);
	bjet_p_l5->SetLineColor(kBlue);
	bjet_p_l5->SetStats(0);
	bjet_p_l5->SetMinimum(0);
	bjet_p_l5->GetYaxis()->SetTitleOffset(1);

	bjet_p_s5->SetLineWidth(2);
	bjet_p_s5->SetLineStyle(1);
	bjet_p_s5->SetLineColor(kRed);
	bjet_p_s5->SetStats(0);
	bjet_p_s5->SetMinimum(0);
	bjet_p_s5->GetYaxis()->SetTitleOffset(1);

	gPad->SetLeftMargin(0.14);

	bjet_p_l5->Draw("he");
	bjet_p_s5->Draw("same");


	// Legends
	TLegend *leg = new TLegend(0.4,0.75,0.8,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(bjet_p_l5,"IDR-L","l");
	leg->AddEntry(bjet_p_s5,"IDR-S","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();
	std::cout << "N: " << bjet1_l5 + bjet2_l5 << "\n";


	TFile *SaveFile = new TFile("ttbar_bjet_info.root","NEW");

	bjet_p_l5->Write();
	bjet_p_s5->Write();
	SaveFile->Close();

	delete SaveFile;















	
}

