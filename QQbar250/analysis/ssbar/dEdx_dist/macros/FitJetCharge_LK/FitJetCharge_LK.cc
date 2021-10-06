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
#include <TLegend.h>
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

void FitJetCharge_LK() {

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);

  TCanvas* c1 = new TCanvas("c1","c1",500,500);


  TString filename = "/home/ilc/yokugawa/macros/QQbar250/analysis/ssbar/Polar/rootfiles/DQ_250GeV_uu.400.root";
  TFile *f = new TFile(filename);
  TH1F* h_pfo_LeadK_q_match_charge = (TH1F*)f->Get("h_pfo_LeadK_q_match_charge");
  TH1F* h_pfo_LeadK_qbar_match_charge = (TH1F*)f->Get("h_pfo_LeadK_qbar_match_charge");
  Normal(h_pfo_LeadK_q_match_charge);
  Normal(h_pfo_LeadK_qbar_match_charge);
  std::cout << filename << std::endl;

  makePretty(h_pfo_LeadK_q_match_charge,2);
  makePretty(h_pfo_LeadK_qbar_match_charge,4);

  // h_pfo_LeadK_q_match_charge->GetYaxis()->SetRangeUser(0,0.055);

  h_pfo_LeadK_q_match_charge->Draw("h");
  h_pfo_LeadK_qbar_match_charge->Draw("hsame");

  TLegend* leg = new TLegend(0.65,0.85,0.9,0.65,"","brNDC");
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(h_pfo_LeadK_q_match_charge,"uu matched PFO","fp");
  leg->AddEntry(h_pfo_LeadK_qbar_match_charge,"#bar{uu} matched PFO","fp");
  leg->Draw();


  TF1* crystalball = new TF1("crystalball", crystalball_function, -1., 1., 5) ;
  crystalball->SetParNames("Constant", "Mean", "Sigma", "Alpha", "N");
  crystalball->SetTitle("crystalball");
  crystalball->SetLineColor(2);
  
  float p0 = h_pfo_LeadK_q_match_charge->GetMaximum();
  float p1 = h_pfo_LeadK_q_match_charge->GetMean();
  float p2 = h_pfo_LeadK_q_match_charge->GetRMS();
  float p3 = 10.0;
  float p4 = 1.0;
  crystalball->SetParameters(p0,p1,p2,p3,p4);
  
  h_pfo_LeadK_q_match_charge->Fit(crystalball,"SR");

  p0 = h_pfo_LeadK_qbar_match_charge->GetMaximum();
  p1 = h_pfo_LeadK_qbar_match_charge->GetMean();
  p2 = h_pfo_LeadK_qbar_match_charge->GetRMS();
  crystalball->SetLineColor(4);
  crystalball->SetParameters(p0,p1,p2,p3,p4);
  
  h_pfo_LeadK_qbar_match_charge->Fit(crystalball,"SR");





  
   

}
