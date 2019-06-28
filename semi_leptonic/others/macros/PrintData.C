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

void style(TH1F* hist,Color_t color);

void PrintData()
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

	int bin_cos = 100;

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
	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,cx,500);
	TCanvas * c3 = new TCanvas("c3", "Data-MC",0,0,cx,500);
	TCanvas * c4 = new TCanvas("c4", "Data-MC",0,0,cx,500);

  c1->cd();

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

	TH1F * IsoLep_E_l5   = new TH1F("IsoLep_E_l5", ";E_{l} GeV;Entries", bin_e,0,max_e);
	TH1F * IsoLep_cos_l5 = new TH1F("IsoLep_cos_l5", ";cos#theta_{l};Entries", bin_cos,0,1.0);
	TH1F * TopMass_l5 = new TH1F("TopMass_l5", ";M_{t} GeV;Entries", 100,0,300);
	TH1F * WMass_l5 = new TH1F("WMass_l5", ";M_{W} GeV;Entries", 100,0,200);

	TGaxis::SetMaxDigits(3);

	TTree * normaltree_l5 = (TTree*) file_l5->Get( "Stats" ) ;

	int NIsoLep_E_l5    = normaltree_l5->Draw("Top2leptonE >> IsoLep_E_l5", fcuts||bcuts);
	int NIsoLep_cos_l5  = normaltree_l5->Draw("Top2leptonCos >> IsoLep_cos_l5", fcuts||bcuts);
	int NTop1Mass_l5     = normaltree_l5->Draw("Top1mass >> TopMass_l5", fcuts||bcuts);
	int NTop2Mass_l5     = normaltree_l5->Draw("Top2mass >> +TopMass_l5", fcuts||bcuts);
	int NW1Mass_l5     = normaltree_l5->Draw("W1mass >> WMass_l5", fcuts||bcuts);
	int NW2Mass_l5     = normaltree_l5->Draw("W2mass >> +WMass_l5", fcuts||bcuts);


	////////////// Detector Model SMALL //////////////

	std::string filename_s5 = rootfiles[token_s5].filename();
	cout << "Processing : " << filename_s5 << " ..." << endl;

	TFile * file_s5 = TFile::Open(filename_s5.c_str());

	TH1F * IsoLep_E_s5   = new TH1F("IsoLep_E_s5", ";E_{l} GeV;Entries", bin_e,0,max_e);
	TH1F * IsoLep_cos_s5 = new TH1F("IsoLep_cos_s5", ";cos#theta_{l};Entries", bin_cos,0,1.0);
	TH1F * TopMass_s5 = new TH1F("TopMass_s5", ";M_{t} GeV;Entries", 100,0,300);
	TH1F * WMass_s5 = new TH1F("WMass_s5", ";M_{W} GeV;Entries", 100,0,200);

	TTree * normaltree_s5 = (TTree*) file_s5->Get( "Stats" ) ;

	int NIsoLep_E_s5    = normaltree_s5->Draw("Top2leptonE >> IsoLep_E_s5", fcuts||bcuts);
	int NIsoLep_cos_s5  = normaltree_s5->Draw("Top2leptonCos >> IsoLep_cos_s5", fcuts||bcuts);
	int NTop1Mass_s5     = normaltree_s5->Draw("Top1mass >> TopMass_s5", fcuts||bcuts);
	int NTop2Mass_s5     = normaltree_s5->Draw("Top2mass >> +TopMass_s5", fcuts||bcuts);
	int NW1Mass_s5     = normaltree_s5->Draw("W1mass >> WMass_s5", fcuts||bcuts);
	int NW2Mass_s5     = normaltree_s5->Draw("W2mass >> +WMass_s5", fcuts||bcuts);


  ////////////// Style Setting //////////////

	Color_t red = kRed;
	Color_t blue = kBlue;

	style(IsoLep_E_l5,blue);
	style(IsoLep_E_s5,red);

	style(IsoLep_cos_l5,blue);
	style(IsoLep_cos_s5,red);

	style(TopMass_l5,blue);
	style(TopMass_s5,red);

	style(WMass_l5,blue);
	style(WMass_s5,red);

	gPad->SetLeftMargin(0.14);

	IsoLep_E_l5->Draw("he");
	IsoLep_E_s5->Draw("same");


	// Legends
	TLegend *leg = new TLegend(0.4,0.75,0.8,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(IsoLep_E_l5,"IDR-L","l");
	leg->AddEntry(IsoLep_E_s5,"IDR-S","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();

  //second pad
  c2->cd();

	IsoLep_cos_l5->Draw("he");
	IsoLep_cos_s5->Draw("same");

	TLegend *leg2 = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(IsoLep_cos_l5,"IDR-L","l");
	leg2->AddEntry(IsoLep_cos_s5,"IDR-S","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();
  
	QQBARLabel(0.8,0.2,"",1);

	c2->Update();

	// third pad
	c3->cd();

	TopMass_l5->Draw("he");
	TopMass_s5->Draw("same");

	TLegend *leg3 = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg3->SetTextFont(42);
	leg3->AddEntry(TopMass_l5,"IDR-L","l");
	leg3->AddEntry(TopMass_s5,"IDR-S","l");
	leg3->SetFillColor(0);
	leg3->SetLineColor(0);
	leg3->SetShadowColor(0);
	leg3->Draw();
  
	QQBARLabel(0.8,0.2,"",1);

	c3->Update();

	// forth pad
	c4->cd();

	WMass_l5->Draw("he");
	WMass_s5->Draw("same");

	TLegend *leg4 = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg4->SetTextFont(42);
	leg4->AddEntry(WMass_l5,"IDR-L","l");
	leg4->AddEntry(WMass_s5,"IDR-S","l");
	leg4->SetFillColor(0);
	leg4->SetLineColor(0);
	leg4->SetShadowColor(0);
	leg4->Draw();
  
	QQBARLabel(0.8,0.2,"",1);

	c4->Update();


	std::cout << "N: " << NIsoLep_E_l5 + NIsoLep_E_s5 << "\n";


	TFile *SaveFile = new TFile("ttbar_PrintData.root","NEW");

	IsoLep_E_l5->Write();
	IsoLep_E_s5->Write();
	IsoLep_cos_l5->Write();
	IsoLep_cos_s5->Write();
	TopMass_l5->Write();
	TopMass_s5->Write();
	WMass_l5->Write();
	WMass_s5->Write();

	SaveFile->Close();

	delete SaveFile;

}

void style(TH1F* hist,Color_t color)
{
	
	hist->SetLineWidth(2);
	hist->SetLineStyle(1);
	hist->SetLineColor(color);
	hist->SetStats(0);
	hist->SetMinimum(0);
	hist->GetYaxis()->SetTitleOffset(1);

}

