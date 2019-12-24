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
void asymmetry_merge()
{

	// initialize variables
	int styl = 0;
	int cx   = 500;
	double Legx1 = 0.20;
	double Legx2 = 0.6;

	int tokenL=0;
	int tokenR=0;

	int bin_e = 30;
	int max_e = 1;

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
	//TCut cuts = rcTW + hadM + pcut + gcut + (method1|| method2|| method3|| method4);


	
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

	std::cout << "Enter code for eLpR: ";
	std::cin >> tokenL;
	std::cout << "Enter code for eRpL: ";
	std::cin >> tokenR;
	std::cout << std::endl;



	// eLpR sample
	
	std::string filenameL = rootfiles[tokenL].filename();
	cout << "Processing : " << filenameL << " ..." << endl;

	TFile * fileL = TFile::Open(filenameL.c_str());

	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,cx,500);
	TH1F * cosRecoL = new TH1F("cosRecoL", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosRecoL->Sumw2();
	TH1F * cosGenL = new TH1F("cosGenL", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGenL->Sumw2();

	TGaxis::SetMaxDigits(3);

	TTree * normaltreeL = (TTree*) fileL->Get( "Stats" ) ;
	TTree * GenTreeL = (TTree*) fileL->Get( "GenTree" ) ;

	int forwardL = GenTreeL->Draw("qMCcostheta >> cosGenL","qMCcostheta > 0 && qMCcostheta > -2 && singletopFlag == 0");
	int backwardL = GenTreeL->Draw("qMCcostheta >> +cosGenL","qMCcostheta < 0 && qMCcostheta > -2 && singletopFlag == 0");

	TCut fcuts = "qCostheta > 0" + cuts;
	TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;
	int recoforwardL = normaltreeL->Draw("qCostheta >> cosRecoL", fcuts);
	int recobackwardL = normaltreeL->Draw("qCostheta >> +cosRecoL", bcuts);

	cosGenL->Scale(0.315);
	cosRecoL->Scale(0.315);


	// eRpL sample
	
	std::string filenameR = rootfiles[tokenR].filename();
	cout << "Processing : " << filenameR << " ..." << endl;

	TFile * fileR = TFile::Open(filenameR.c_str());

	//TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);
	TH1F * cosRecoR = new TH1F("cosRecoR", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosRecoR->Sumw2();
	TH1F * cosGenR = new TH1F("cosGenR", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGenR->Sumw2();

	TTree * normaltreeR = (TTree*) fileR->Get( "Stats" ) ;
	TTree * GenTreeR = (TTree*) fileR->Get( "GenTree" ) ;

	int forwardR = GenTreeR->Draw("qMCcostheta >> cosGenR","qMCcostheta > 0 && qMCcostheta > -2 && singletopFlag == 0");
	int backwardR = GenTreeR->Draw("qMCcostheta >> +cosGenR","qMCcostheta < 0 && qMCcostheta > -2 && singletopFlag == 0");

	int recoforwardR = normaltreeR->Draw("qCostheta >> cosRecoR", fcuts);
	int recobackwardR = normaltreeR->Draw("qCostheta >> +cosRecoR", bcuts);

	cosGenR->Scale(0.065);
	cosRecoR->Scale(0.065);


	// merge two histograms
	
	TList *l_Reco = new TList;
	l_Reco->Add(cosRecoL);
	l_Reco->Add(cosRecoR);

	TList *l_Gen = new TList;
	l_Gen->Add(cosGenL);
	l_Gen->Add(cosGenR);


	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);
	TH1F * cosReco = new TH1F("cosReco", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosReco->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGen->Sumw2();

	cosReco->Merge(l_Reco);
	cosGen->Merge(l_Gen);

	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
	fgen->SetLineColor(kBlue+1);
	fgen->SetLineStyle(3);
	freco->SetLineStyle(3);

	double intCosReco = cosReco->Integral(2,29);
	double intCosGen  = cosGen->Integral(2,29);
	cosReco->Scale(1/intCosReco);
	cosGen->Scale(1/intCosGen);

	cosReco->SetLineWidth(3);
	cosGen->SetLineWidth(3);
	cosGen->SetLineStyle(2);

	cosGen->SetLineColor(kBlue+1);
	cosReco->SetLineColor(kBlue+1);

	cosGen->Fit("fgen","Q0");
	cosReco->Fit("freco", "0QR");

	cosGen->SetMinimum(0);
	cosGen->Draw("he");
	cosReco->Draw("same");


	// computation result

	int forward = forwardL + forwardR;
	int backward = backwardL + backwardR;

	int recoforward = recoforwardL + recoforwardR;
	int recobackward = recobackwardL + recobackwardR;

	float afbgen = (float)(forward - backward) / (float) (forward + backward);
	float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);


	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	std::cout << "Chi2: " << cosReco->Chi2Test(cosGen,"UUNORMCHI2/NDF") << "\n";
	cout << "--------------------------------------------------------------\n";
	float afbgenf = (fgen->Integral(0,1) - fgen->Integral(-1,0)) / (fgen->Integral(0,1) + fgen->Integral(-1,0));
	float afbrecof = (freco->Integral(0,1) - freco->Integral(-1,0)) / (freco->Integral(0,1) + freco->Integral(-1,0));

	gPad->SetLeftMargin(0.14);
	cosGen->GetYaxis()->SetTitleOffset(1);

	cout << "Afb gen functional: " << afbgenf << endl;
	cout << "Afb reco functional: " << afbrecof << "(" << afbrecof / afbgenf *100 << "%)"   << endl;
	float nominal = 30.8;

	float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "% (+" << efficiency / nominal *100 -100 << "%)\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";



	
}

