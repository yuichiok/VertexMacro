#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

// see math/mathcore/src/PdfFuncMathCore.cxx in ROOT 6.x
double crystalball_function(double x, double alpha, double n, double sigma, double mean) {
  // evaluate the crystal ball function
  if (sigma < 0.)     return 0.;
  double z = (x - mean)/sigma; 
  if (alpha < 0) z = -z; 
  double abs_alpha = std::abs(alpha);
  // double C = n/abs_alpha * 1./(n-1.) * std::exp(-alpha*alpha/2.);
  // double D = std::sqrt(M_PI/2.)*(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
  // double N = 1./(sigma*(C+D));
  if (z  > - abs_alpha)
    return std::exp(- 0.5 * z * z);
  else {
    //double A = std::pow(n/abs_alpha,n) * std::exp(-0.5*abs_alpha*abs_alpha);
    double nDivAlpha = n/abs_alpha;
    double AA =  std::exp(-0.5*abs_alpha*abs_alpha);
    double B = nDivAlpha -abs_alpha;
    double arg = nDivAlpha/(B-z);
    return AA * std::pow(arg,n);
  }
}

double crystalball_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}

double GaussExp_function(double x, double k, double sigma, double mean) {
	if (sigma < 0.)     return 0.;
	double z = (x - mean)/sigma;
	if (k < 0) z = -z;
	double abs_k = std::abs(k);
	if (z  >= - abs_k)
		return std::exp(- 0.5 * z * z);
	else{
		double abs_k2 = abs_k * abs_k;
		return std::exp(0.5 * abs_k2 + abs_k * z);
	}

}

double GaussExp_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * GaussExp_function(x[0], p[3], p[2], p[1]));
}

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
	TH1F * jetE1all			= new TH1F("jetE1all",";jetE_{B}; 1 / Entries",200,0,200);
	jetE1all->Sumw2();
	TH1F * jetE1			= new TH1F("jetE1",";jetE_{B}; 1 / Entries",200,0,200);
	jetE1->Sumw2();

	TH1F * jetE2all			= new TH1F("jetE2all",";jetE_{B}; 1 / Entries",200,0,200);
	jetE2all->Sumw2();
	TH1F * jetE2			= new TH1F("jetE2",";jetE_{B}; 1 / Entries",200,0,200);
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

	// Entry

	int bjet1all	= Stats->Draw("jet_E[0] >> jetE1all",MCcos2);
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + bmom1 + singleTopFlagON + method1);
	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + bmom1 + singleTopFlagON);
	//int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + MCcos09 + bmom1 + singleTopFlagON + (method1 || method2 || method3 || method4 || method7) );
	
	int bjet2all	= Stats->Draw("jet_E[1] >> jetE2all",MCcos2);
//	int bjet2 		= Stats->Draw("jet_E[1] >> jetE2", MCcos2 + bmom2 + singleTopFlagON + method1);
	int bjet2 		= Stats->Draw("jet_E[1] >> jetE2", MCcos2 + bmom2 + singleTopFlagON);
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


//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%  Fit Functions %%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	float xmin = 20., xmax = 180.;
	TF1 *crystalball = new TF1("crystalball", crystalball_function, xmin, xmax, 5);
	TF1 *fgaus       = new TF1("fgaus","gaus",xmin, xmax);
	TF1 *dgaus       = new TF1("dgaus","gaus(0)+gaus(3)",xmin, xmax);
	TF1 *tgaus       = new TF1("tgaus","gaus(0)+gaus(3)+gaus(6)",xmin, xmax);
	TF1 *fcheb       = new TF1("fcheb","cheb3",xmin, xmax);
	TF1 *fgaus_epx   = new TF1("fgaus_epx", GaussExp_function, xmin, xmax, 4);
	TF1 *fpol        = new TF1("fpol","pol6",xmin, xmax);

	TF1 *flogNormal = new TF1("flogNormal","[0]*ROOT::Math::lognormal_pdf(x,log([1]),log([2]))",xmin,xmax);

	crystalball->SetParNames("Constant", "Mean", "Sigma", "Alpha", "N");
	crystalball->SetTitle("crystalball"); // not strictly necessary

	fgaus_epx->SetParNames("Constant", "Mean", "Sigma", "k");

	float p0 = 9.0E-3;
	float p1 = 100.;
	float p2 = 100.;
	float p3 = 1.0;
	float p4 = 1.0;

	// Double Gaussian parameter
	float constant = 8E-3;
	float mean = 80.0;
	float wid = 30.0;

	float bgconstant = 5e-3;
	float bgmean = 80.0;
	float bgwid = 30.0;

	// GaussExp paramter
	float pconst = 9.5E-3;
	float pmean  = 80.0;
	float psigma = 40.0;
	float pk     = 0.5;

	// Function Colors
	crystalball->SetLineColor(kRed);
	dgaus->SetLineColor(kRed);	
	tgaus->SetLineColor(kRed);
	fcheb->SetLineColor(kRed);
	fgaus_epx->SetLineColor(kRed);
	flogNormal->SetLineColor(kRed);
	fpol->SetLineColor(kRed);


	// set parameters 
	crystalball->SetParameters(jetE1->GetMaximum(), jetE1->GetMean(), jetE1->GetRMS(), p3, p4);
	dgaus->SetParameters(jetE1->GetMaximum()*0.8, jetE1->GetMean(), jetE1->GetRMS(), jetE1->GetMaximum()*0.2, jetE1->GetMean(), jetE1->GetRMS());
	tgaus->SetParameters(jetE1->GetMaximum()*0.6, jetE1->GetMean(), jetE1->GetRMS(), jetE1->GetMaximum()*0.2, jetE1->GetMean(), jetE1->GetRMS(), jetE1->GetMaximum()*0.1, jetE1->GetMean(), jetE1->GetRMS());
	fgaus_epx->SetParameters(pconst, pmean, psigma, pk);

	fgaus->SetParameters(jetE1->GetMaximum(), jetE1->GetMean(), jetE1->GetRMS());
	flogNormal->SetParameters(jetE1->GetMaximum(), jetE1->GetMean(), jetE1->GetRMS());


//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//	今んとこtgausが最高

	jetE1->Fit("flogNormal","R");
	jetE1->Draw("he");
	flogNormal->Draw("same");
	jetE1all->Draw("hsame");


	TLegend *leg = new TLegend(0.7,0.85,0.9,0.95); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(jetE1all,"All Parton Level","l");
	leg->AddEntry(jetE1,"Single Top Tagged","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	c1->Update();

/*
// jetE2

	TCanvas * c2			= new TCanvas("c2", "jetE2",0,0,500,500);

	jetE2->Fit("crystalball");
	jetE2->Draw("he");
	jetE2all->Draw("hsame");
	crystalball->Draw("same");

	TLegend *leg2 = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(jetE2all,"All Parton Level","l");
	leg2->AddEntry(jetE2,"Single Top Tagged","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();

	c2->Update();
*/


}

