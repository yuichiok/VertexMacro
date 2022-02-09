#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "../../../style/Style.C"
#include "../../../style/Labels.C"

double BetheBloch(const double *x, const double *pars){
  double mass=pars[5];
  double bg=x[0]/mass;
  double b=sqrt(bg*bg/(1.0+bg*bg));
  double tmax=pars[2]*TMath::Power(bg,2.0);   ///(1.0+pars[3]*g+pars[4]);

  return 1.350e-1*(0.5*pars[0]*TMath::Log(pars[1]*TMath::Power(bg,2.0)*tmax)-pars[3]*b*b-pars[4]*bg/2.0)/(b*b);
}

void Labels(){

  QQBARLabel(0.1,0.952,"Work In Progress");
  QQBARLabel2(0.6,0.965, "e^{-}e^{+} #rightarrow s#bar{s}",kGray+2);

}

void dEdxplots() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);

 
  TString filename = "../rootfiles/double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.root";
  // TString filename = "../rootfiles/double_tag/DQ_250GeV_ss.nocut.root";
  TFile *f = new TFile(filename);

  TH1F*  pion_dEdx_truth = (TH1F*)f->Get("h_pfo_p_dEdx_pion");
  TH1F*  proton_dEdx_truth = (TH1F*)f->Get("h_pfo_p_dEdx_proton");
  TH1F*  kaon_dEdx_truth = (TH1F*)f->Get("h_pfo_p_dEdx_kaon");
  TH1F*  muon_dEdx_truth = (TH1F*)f->Get("h_pfo_p_dEdx_muon");
  TH1F*  electron_dEdx_truth = (TH1F*)f->Get("h_pfo_p_dEdx_electron");

  
  std::vector< double > parskaon;
  parskaon.push_back(0.0792784);
  parskaon.push_back(3798.12);
  parskaon.push_back(4.06952e+07);
  parskaon.push_back(0.450671);
  parskaon.push_back(0.00050169);
  parskaon.push_back(0.493677); // mass


  TCanvas* c_dEdx_truth_0 = new TCanvas("c_dEdx","c_dEdx",800,800);
  gPad->SetLogx();
  pion_dEdx_truth->GetXaxis()->SetRangeUser(1,100);
  pion_dEdx_truth->GetXaxis()->SetTitle("p [GeV]");
  pion_dEdx_truth->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV/cm]");
  pion_dEdx_truth->GetYaxis()->SetTitleOffset(1.9);
  
  pion_dEdx_truth->SetMarkerColor(4);
  pion_dEdx_truth->SetMarkerStyle(1);
  pion_dEdx_truth->SetLineColor(4);
  pion_dEdx_truth->SetFillColor(4);
  pion_dEdx_truth->SetFillStyle(1001);
  pion_dEdx_truth->SetTitle("");
  pion_dEdx_truth->SetContour(5);
  pion_dEdx_truth->Draw("p");
  
  proton_dEdx_truth->SetMarkerColor(kGreen+1);
  proton_dEdx_truth->SetMarkerStyle(1);
  proton_dEdx_truth->SetLineColor(kGreen+1);
  proton_dEdx_truth->SetFillColor(kGreen+1);
  proton_dEdx_truth->SetFillStyle(1001);
  proton_dEdx_truth->SetContour(5);
  proton_dEdx_truth->Draw("psame");
  
  kaon_dEdx_truth->SetMarkerColor(2);
  kaon_dEdx_truth->SetMarkerStyle(1);
  kaon_dEdx_truth->SetLineColor(2);
  kaon_dEdx_truth->SetFillColor(2);
  kaon_dEdx_truth->SetFillStyle(1001);
  kaon_dEdx_truth->SetContour(5);
  kaon_dEdx_truth->Draw("psame");

  electron_dEdx_truth->SetMarkerColor(kViolet);
  electron_dEdx_truth->SetMarkerStyle(1);
  electron_dEdx_truth->SetLineColor(kViolet);
  electron_dEdx_truth->SetFillColor(kViolet);
  electron_dEdx_truth->SetFillStyle(1001);
  electron_dEdx_truth->SetContour(5);
  electron_dEdx_truth->Draw("psame");

  muon_dEdx_truth->SetMarkerColor(kGray);
  muon_dEdx_truth->SetMarkerStyle(1);
  muon_dEdx_truth->SetLineColor(kGray);
  muon_dEdx_truth->SetFillColor(kGray);
  muon_dEdx_truth->SetFillStyle(1001);
  muon_dEdx_truth->SetContour(5);
  muon_dEdx_truth->Draw("psame");


  TF1 *func = new TF1("func",BetheBloch,1,100,6) ;
  for (int i = 0; i < 6; ++i) func->SetParameter(i,parskaon[i]);
  func->SetLineColor(kBlack);
  func->Draw("same");
  
  TLegend *leg0 = new TLegend(0.25,0.7,0.5,0.85);
  leg0->SetTextSize(0.03);
  leg0->SetTextFont(42);
  leg0->AddEntry(kaon_dEdx_truth,"Charged Kaons","fp");
  leg0->AddEntry(func,"Bethe-Bloch (Kaon)","l");
  leg0->AddEntry(pion_dEdx_truth,"Charged Pions","fp");
  leg0->AddEntry(proton_dEdx_truth,"Protons","fp");
  leg0->AddEntry(muon_dEdx_truth,"Muons","fp");
  leg0->AddEntry(electron_dEdx_truth,"Electrons","fp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

}
