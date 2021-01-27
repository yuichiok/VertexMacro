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
#include "TLine.h"
#include "/home/ilc/yokugawa/macros/semi_leptonic/style/Style.C"
#include "/home/ilc/yokugawa/macros/semi_leptonic/style/Labels.C"


int nbins=40;
TString pol = "eL";
TString folder = "../output/";//output/kt_20190202";

void acceptance_factor_plot(bool DBD=false) {

  //----------------------------------
  // --- large model
 
//  TString filename = TString::Format("%s/bbbar_l5_valencia2.0_cuts3_500GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  TString filename = "/home/ilc/yokugawa/QQbarAnalysis/analysis/bbbar_Kgamma35_15161_cuts11_250GeV_eL_btag1_0.8_btag2_0.8_nbins40.root";

  TFile *f = new TFile(filename);
  TH1F *h_parton = (TH1F*)f->Get("parton");
  h_parton->Sumw2();

  TH1F *h_eff = (TH1F*)f->Get("parton_recocuts");
  h_eff->Sumw2();

  h_eff->Divide(h_parton);
  double max =0;
  for(int i=nbins/2; i<nbins; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);
    
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  gStyle->SetLegendFont(42);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.0);
  
  TCanvas * canvas = new TCanvas ("canvas","canvas",500,500);
  canvas->cd(1);
  h_eff->GetXaxis()->SetTitle("|cos#theta_{b}|");
  h_eff->GetXaxis()->SetRangeUser(0,1);
  h_eff->GetYaxis()->SetTitle("N_{reco cuts}^{parton level} / N^{parton level}");
  h_eff->GetYaxis()->SetRangeUser(0,h_eff->GetMaximum()*1.1);

  h_eff->GetXaxis()->SetTitleOffset(1.1);
  h_eff->GetXaxis()->SetTitleFont(42);
  h_eff->GetXaxis()->SetTitleSize(0.05);
  h_eff->GetXaxis()->SetLabelSize(0.05);
  h_eff->GetXaxis()->SetLabelOffset(0.015);

  h_eff->GetYaxis()->SetTitleOffset(1.4);
  h_eff->GetYaxis()->SetTitleFont(42);
  h_eff->GetYaxis()->SetTitleSize(0.05);
  h_eff->GetYaxis()->SetLabelSize(0.05);
  h_eff->GetYaxis()->SetLabelOffset(0.015);
  
  h_eff->Draw("p");
  h_eff->SetLineStyle(1);
  h_eff->SetMarkerStyle(21);
  h_eff->SetMarkerColor(4);
  h_eff->SetLineColor(4);
  h_eff->SetLineWidth(2);

  QQBARLabel(0.2,0.2,"",1);
  
  TLegend *leg = new TLegend(0.2,0.5,0.65,0.65);
  leg->SetTextFont(42);
  leg->AddEntry(h_eff,"IDR-L, 500 GeV","lep");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);

  leg->Draw();


  canvas->Update();
  /*
  if(DBD==false) {
    canvas->Print("../plots/acceptance_2models_v2.C");
    canvas->Print("../plots/acceptance_2models_v2.eps");
  }
  else  {
    canvas->Print("../plots/acceptance_2models_DBD_v2.C");
    canvas->Print("../plots/acceptance_2models_DBD_v2.eps");
  }
  */
  
}