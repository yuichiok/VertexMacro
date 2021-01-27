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


void plotmodel() {

  int nbins=40;
  TString pol = "eL";
  TString folder = "../output/";//output/kt_20190202";
  TString model = "l5_valencia2.0";
  
 // large model
  //---------------------------------
  TString filename = "/home/ilc/yokugawa/QQbarAnalysis/analysis/bbbar_Kgamma35_15161_cuts11_250GeV_eL_btag1_0.8_btag2_0.8_nbins40.root";
  TFile *f = new TFile(filename);

  TH1F *h_parton = (TH1F*)f->Get("parton");
  h_parton->Sumw2();

  TH1F *h_eff = (TH1F*)f->Get("parton_recocuts");
  h_eff->Sumw2();
  h_eff->Divide(h_parton);
  
  double max =0;
  for(int i=nbins/2; i<nbins-3; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);
  h_eff->Scale(1./max);
  
  double integtral_parton= h_parton->Integral(4,16);//nbins/2-nbins/3,nbins/2+nbins/3);//
  // h_parton->Scale(integtral_truth/integtral_parton);

  //-----------------------------------------------------
  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",500,500);
  canvas0->cd(1);
//  h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 500GeV, 46 fb^{-1}");
  h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 250GeV");
  h_parton->GetXaxis()->SetTitle("cos#theta_{b}");
  h_parton->GetXaxis()->SetTitleOffset(1.1);
  h_parton->GetXaxis()->SetTitleFont(42);
  h_parton->GetXaxis()->SetTitleSize(0.05);
  h_parton->GetXaxis()->SetLabelSize(0.05);
  h_parton->GetXaxis()->SetLabelOffset(0.015);

  h_parton->GetYaxis()->SetTitle("entries / 0.1");
  h_parton->GetYaxis()->SetTitleOffset(1.4);
  h_parton->GetYaxis()->SetTitleFont(42);
  h_parton->GetYaxis()->SetTitleSize(0.05);
  h_parton->GetYaxis()->SetLabelSize(0.05);
  h_parton->GetYaxis()->SetLabelOffset(0.015);
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(3);
  h_parton->SetLineWidth(3);
  h_parton->Draw("histo");
  
  QQBARLabel(0.8,0.2,"",1);

  TLegend *leg = new TLegend(0.2,0.65,0.55,0.8);
  leg->SetTextFont(42);
  leg->AddEntry(h_parton,"parton level","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  canvas0->Update();
//  canvas0->Print("../plots/result2models_v2.C");
//  canvas0->Print("../plots/result2models_v2.eps");

}