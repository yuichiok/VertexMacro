#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
// #include "../../../style/Style.C"
// #include "../../../style/Labels.C"

double crystalball_function(double x, double alpha, double n, double sigma, double mean) {
  // evaluate the crystal ball function
  if (sigma < 0.)     return 0.;
  double z = (x - mean)/sigma; 
  if (alpha < 0) z = -z; 
  double abs_alpha = std::abs(alpha);
  if (z  > - abs_alpha)
    return std::exp(- 0.5 * z * z);
  else {
    double nDivAlpha = n/abs_alpha;
    double AA =  std::exp(-0.5*abs_alpha*abs_alpha);
    double B = nDivAlpha -abs_alpha;
    double arg = nDivAlpha/(B-z);
    return AA * std::pow(arg,n);
  }
}

double crystalball_function(const double *x, const double *p) {
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}


void makePretty(TH1F* h1, int color){
  h1->SetStats(0);
  h1->SetMarkerColor(color);
  h1->SetLineColor(color);
  h1->SetFillColor(color);
  h1->SetFillStyle(3003);
  h1->SetMarkerStyle(1);
  h1->SetMarkerSize(0.2);
  h1->SetTitle("");
}

void Normal(TH1F* h1){
  h1->Scale(1.0/h1->GetEntries());
}

void FitJetCharge() {

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);

  TCanvas* c1 = new TCanvas("c1","c1",500,500);

  for (int i = 1; i < 10; ++i)
  {

    if(i%2==1) continue;

    float index = i * 0.1;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << index;
    TString filename = "/home/ilc/yokugawa/macros/QQbar250/analysis/ssbar/Polar/rootfiles/DQ_250GeV_uu_wk" + ss.str() + ".root";
    TFile *f = new TFile(filename);
    TH1F* h_pfo_q_match_charge = (TH1F*)f->Get("h_pfo_q_match_charge");
    Normal(h_pfo_q_match_charge);
    std::cout << filename << std::endl;

    makePretty(h_pfo_q_match_charge,i);

    if(i == 1){
      h_pfo_q_match_charge->Draw("h");
    }else{
      h_pfo_q_match_charge->Draw("hsame");
    }


    TF1* crystalball = new TF1("crystalball", crystalball_function, -1., 1., 5) ;
    crystalball->SetParNames("Constant", "Mean", "Sigma", "Alpha", "N");
    crystalball->SetTitle("crystalball");
    crystalball->SetLineColor(i);
    
    float p0 = h_pfo_q_match_charge->GetMaximum();
    float p1 = h_pfo_q_match_charge->GetMean();
    float p2 = h_pfo_q_match_charge->GetRMS();
    float p3 = 10.0;
    float p4 = 1.0;
    crystalball->SetParameters(p0,p1,p2,p3,p4);
    
    h_pfo_q_match_charge->Fit(crystalball,"SR");

  }




  
   

}
