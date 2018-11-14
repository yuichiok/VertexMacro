#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

Double_t BetheBlochGeant(Double_t *bg,
		Double_t *kp){

	const Double_t mK  = 0.307075e-3; // [GeV*cm^2/g]
	const Double_t me  = 0.511e-3;    // [GeV/c^2]
	const Double_t rho = kp[0];
	const Double_t x0  = kp[1]*2.303;
	const Double_t x1  = kp[2]*2.303;
	const Double_t mI  = kp[3];
	const Double_t mZA = kp[4];
	const Double_t bg2 = bg[0]*bg[0];
	const Double_t maxT= 2*me*bg2;    // neglecting the electron mass

	//*** Density effect
	Double_t d2=0.; 
	const Double_t x=TMath::Log(bg[0]);
	const Double_t lhwI=TMath::Log(28.816*1e-9*TMath::Sqrt(rho*mZA)/mI);
	if (x > x1) {
		d2 = lhwI + x - 0.5;
	} else if (x > x0) {
		const Double_t r=(x1-x)/(x1-x0);
		d2 = lhwI + x - 0.5 + (0.5 - lhwI - x0)*r*r*r;
	}

	return mK*mZA*(1+bg2)/bg2*
		(0.5*TMath::Log(2*me*bg2*maxT/(mI*mI)) - bg2/(1+bg2) - d2);
}

void dEdx()
{
	int token=0;
	string filename0 = "/home/ilc/yokugawa/run/root_merge/";
	string filename1;

	filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar_dEdx.root";

	string filename = filename0 + filename1;
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);

	float ymax = 0.22E-6;
	float ymin = 0.1E-6;

	TH2F * h_dEdx     = new TH2F("h_dEdx", "dEdx;p_{kaon} [GeV];dEdx", 100, 0, 20, 100, ymin, ymax) ;

	//TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
	//cosReco->Sumw2();

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

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

	TCut diag = " (Top1bntracks - Top1Genbntracks) == 0 " ;

	//TCut fcuts = "qCostheta > 0" + cuts;
	//TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;

	TF1 *fitfunc = new TF1("fitfunc", BetheBlochGeant, 1, 10, 5);

	float p0 = 1.07E-6;
	float p1 = -0.42;
	float p2 = 2.39;
	float p3 = 7.95E-6;
	float p4 = 2.19E-5;

	fitfunc->SetParameters(p0,p1,p2,p3,p4);

	// Fill histograms from tree
	normaltree->Draw("Top1KaondEdx:Top1KaonMomentum>>h_dEdx");

	h_dEdx->Fit("fitfunc","Q");
	h_dEdx->SetStats(0);
	h_dEdx->Draw("COLZ");
	fitfunc->Draw("same");
	c1->Update();

}

