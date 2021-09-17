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




void Labels(TString pol){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(pol=="eL")
    QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q} mc-2020",kGray+2);
  else 
    if(pol=="eR")
      QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} mc-2020",kGray+2);
    else 
      QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q} mc-2020",kGray+2);

  QQBARLabel2(0.2,0.82, "Secondary Tracks in q-jets",kGray+4);

}



void EffPurity_TOF() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  TString filename = "../results/tof_all_primary_tracks_ignoreoverlay_2f_hadronic_and_rad_eL_pR_cut_0_1track_plt2.root";

  TGraph* efficiency[4];
  TGraph* purity[4];

  TFile *f = new TFile(filename);

  for(int j=0; j<4; j++) {
    TH2F*  p_mass_kaon = (TH2F*)f->Get(TString::Format("p_mass_kaon_%i",j));
    TH2F*  p_mass_pion = (TH2F*)f->Get(TString::Format("p_mass_pion_%i",j));
    TH2F*  p_mass_proton = (TH2F*)f->Get(TString::Format("p_mass_proton_%i",j));
    TH2F*  p_mass_muon = (TH2F*)f->Get(TString::Format("p_mass_muon_%i",j));
    TH2F*  p_mass_electron = (TH2F*)f->Get(TString::Format("p_mass_electron_%i",j));
    
    float x[100], eff[100], pur[100];
    int n=0;
    //  option 1, 80eff, 92 pur = 16,21
    //  option 1, 87eff, 87 pur = 16,23
    
    for(int i=4;i<20; i+=2) {
      float n_kaons=  p_mass_kaon->Integral(i, i,40,60)+p_mass_kaon->Integral(i+1, i+1,40,60);
      float n_pions=  p_mass_pion->Integral(i, i,40,60)+p_mass_pion->Integral(i+1, i+1,40,60);
      float n_protons=  p_mass_proton->Integral(i, i,40,60)+p_mass_proton->Integral(i+1, i+1,40,60);
      float n_muons=  p_mass_muon->Integral(i, i,40,60)+p_mass_muon->Integral(i+1, i+1,40,60);
      float n_electrons=  p_mass_electron->Integral(i, i,40,60)+p_mass_electron->Integral(i+1, i+1,40,60);
      float nkaons=  p_mass_kaon->Integral(i, i)+p_mass_kaon->Integral(i+1, i+1,40,60);
      x[n]=i*100./400.;
      //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
      eff[n]=100.*(n_kaons)/nkaons;                    
      pur[n]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
      n++;
    }
 
    efficiency[j] = new TGraph(n,x,eff);
    purity[j] = new TGraph(n,x,pur);
  }

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",1600,800);
  
  c_mom->Divide(2,1);
  c_mom->cd(1);
  c_mom->SetGrid();
  
   TString method[4];
  method[0]="Closest";
  method[1]="Fastest";
  method[2]="CylFit";
  method[3]="ClosestFit";

  c_mom->cd(1);
  TLegend *leg0 = new TLegend(0.2,0.3,0.5,0.5);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->SetHeader("Efficiency");

  for(int j=0; j<4; j++) {

    if(j==0) {
      efficiency[j]->GetXaxis()->SetTitle("momentum [GeV]");
      efficiency[j]->GetYaxis()->SetTitle("[%]");
      efficiency[j]->GetYaxis()->SetTitleOffset(1.25);
      efficiency[j]->GetXaxis()->SetTitleOffset(1.);
      efficiency[j]->GetYaxis()->SetRangeUser(0,100);
    }
    efficiency[j]->SetLineColor(j+1);
    efficiency[j]->SetLineWidth(3);
    efficiency[j]->SetLineStyle(2);
    if(j==0) efficiency[j]->Draw("alp");
    else efficiency[j]->Draw("lp");

    leg0->AddEntry(efficiency[j],method[j],"lp");

  }
  
  Labels("");
  
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  c_mom->cd(2);
  TLegend *leg1 = new TLegend(0.2,0.3,0.5,0.5);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->SetHeader("Purity");

  for(int j=0; j<4; j++) {

    if(j==0) {
      purity[j]->GetXaxis()->SetTitle("momentum [GeV]");
      purity[j]->GetYaxis()->SetTitle("[%]");
      purity[j]->GetYaxis()->SetTitleOffset(1.25);
      purity[j]->GetXaxis()->SetTitleOffset(1.);
      purity[j]->GetYaxis()->SetRangeUser(0,100);
    }
    purity[j]->SetLineColor(j+1);
    purity[j]->SetLineWidth(3);
    purity[j]->SetLineStyle(1);
    if(j==0) purity[j]->Draw("alp");
    else purity[j]->Draw("lp");

 
    leg1->AddEntry(purity[j],method[j],"lp");

  }
  
  Labels("");
  
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();

}

void EffPurity_TOF2() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  TString filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_0_1track_plt2.root";

  TFile *f = new TFile(filename);
  TH2F*  costheta_mass_kaon = (TH2F*)f->Get("costheta_mass_kaon_1");
  TH2F*  costheta_mass_pion = (TH2F*)f->Get("costheta_mass_pion_1");
  TH2F*  costheta_mass_proton = (TH2F*)f->Get("costheta_mass_proton_1");
  TH2F*  costheta_mass_muon = (TH2F*)f->Get("costheta_mass_muon_1");
  TH2F*  costheta_mass_electron = (TH2F*)f->Get("costheta_mass_electron_1");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=1;i<21; i++) {
    float n_kaons=  costheta_mass_kaon->Integral(i, i,40,60);
    float n_pions=  costheta_mass_pion->Integral(i, i,40,60);
    float n_protons=  costheta_mass_proton->Integral(i, i,40,60);
    float n_muons=  costheta_mass_muon->Integral(i, i,40,60);
    float n_electrons=  costheta_mass_electron->Integral(i, i,40,60);
    float nkaons=  costheta_mass_kaon->Integral(i, i);
    x[i-1]=i*1./20.;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-1]=100.*(n_kaons)/nkaons;                    
    pur[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
 
  TCanvas* c_cos = new TCanvas("c_cos","c_cos",800,800);
  c_cos->cd(1);
  c_cos->SetGrid();
  efficiency->GetXaxis()->SetTitle(" cos #theta");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");

  
  Labels("");
  
  TLegend *leg0 = new TLegend(0.2,0.3,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

}


void Mass() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  TString filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_2_1track_plt2.root";
  TFile *f = new TFile(filename);

  TH1F*  mass_fit_kaon = (TH1F*)f->Get("mass_kaon_1");
  TH1F*  mass_fit_pion = (TH1F*)f->Get("mass_pion_1");
  TH1F*  mass_fit_proton = (TH1F*)f->Get("mass_proton_1");

  TH1F*  mass_closest_kaon = (TH1F*)f->Get("mass_kaon_0");
  TH1F*  mass_closest_pion = (TH1F*)f->Get("mass_pion_0");
  TH1F*  mass_closest_proton = (TH1F*)f->Get("mass_proton_0");

  TCanvas* c_mom = new TCanvas("c_mass","c_mass",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  gPad->SetLogy();
  mass_closest_pion->GetXaxis()->SetTitle("mass [GeV]");
  mass_closest_pion->GetYaxis()->SetTitle("a.u.");
  //mass_fit_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_closest_pion->GetXaxis()->SetRangeUser(-0.02,3.02);

  mass_closest_pion->SetLineColor(4);
  mass_closest_pion->SetLineWidth(1);
  mass_closest_pion->SetLineStyle(1);
  mass_closest_pion->Draw("histo");

  mass_closest_kaon->SetLineColor(2);
  mass_closest_kaon->SetLineWidth(1);
  mass_closest_kaon->SetLineStyle(1);
  mass_closest_kaon->Draw("histosame");

  mass_closest_proton->SetLineColor(1);
  mass_closest_proton->SetLineWidth(1);
  mass_closest_proton->SetLineStyle(1);
  mass_closest_proton->Draw("histosame");

  mass_fit_pion->SetLineColor(4);
  mass_fit_pion->SetLineWidth(3);
  mass_fit_pion->SetLineStyle(2);
  mass_fit_pion->Draw("histosame");

  mass_fit_kaon->SetLineColor(2);
  mass_fit_kaon->SetLineWidth(3);
  mass_fit_kaon->SetLineStyle(2);
  mass_fit_kaon->Draw("histosame");

  mass_fit_proton->SetLineColor(1);
  mass_fit_proton->SetLineWidth(2);
  mass_fit_proton->SetLineStyle(2);
  mass_fit_proton->Draw("histosame");
  
 
  Labels("eL");
  
  TLegend *leg = new TLegend(0.6,0.25,0.8,0.55);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(mass_fit_pion,"pions","l");
  leg->AddEntry(mass_fit_kaon,"kaons","lp");
  leg->AddEntry(mass_fit_proton,"protons","lp");
  leg->AddEntry(mass_fit_proton,"Fastest","lp");
  leg->AddEntry(mass_closest_proton,"Closest","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();



}


void Mass2() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  TString filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_2_1track_plt2_softtrack.root";
  TFile *f = new TFile(filename);

  TH1F*  mass_soft_kaon = (TH1F*)f->Get("mass_kaon_1");
  TH1F*  mass_soft_pion = (TH1F*)f->Get("mass_pion_1");
  TH1F*  mass_soft_proton = (TH1F*)f->Get("mass_proton_1");

  filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_2_1track_plt2.root";
  f = new TFile(filename);

  TH1F*  mass_kaon = (TH1F*)f->Get("mass_kaon_1");
  TH1F*  mass_pion = (TH1F*)f->Get("mass_pion_1");
  TH1F*  mass_proton = (TH1F*)f->Get("mass_proton_1");

  TCanvas* c_mom = new TCanvas("c_mass2","c_mass2",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  gPad->SetLogy();
  mass_pion->GetXaxis()->SetTitle("mass [GeV]");
  mass_pion->GetYaxis()->SetTitle("a.u.");
  //mass_soft_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_pion->GetXaxis()->SetRangeUser(-0.02,3.02);

  mass_pion->SetLineColor(4);
  mass_pion->SetLineWidth(1);
  mass_pion->SetLineStyle(1);
  mass_pion->Draw("histo");

  mass_kaon->SetLineColor(2);
  mass_kaon->SetLineWidth(1);
  mass_kaon->SetLineStyle(1);
  mass_kaon->Draw("histosame");

  mass_proton->SetLineColor(1);
  mass_proton->SetLineWidth(1);
  mass_proton->SetLineStyle(1);
  mass_proton->Draw("histosame");

  mass_soft_pion->SetLineColor(4);
  mass_soft_pion->SetLineWidth(3);
  mass_soft_pion->SetLineStyle(2);
  mass_soft_pion->Draw("histosame");

  mass_soft_kaon->SetLineColor(2);
  mass_soft_kaon->SetLineWidth(3);
  mass_soft_kaon->SetLineStyle(2);
  mass_soft_kaon->Draw("histosame");

  mass_soft_proton->SetLineColor(1);
  mass_soft_proton->SetLineWidth(2);
  mass_soft_proton->SetLineStyle(2);
  mass_soft_proton->Draw("histosame");
  
 
  Labels("eL");
  
  TLegend *leg = new TLegend(0.4,0.55,0.6,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(mass_soft_pion,"pions","l");
  leg->AddEntry(mass_soft_kaon,"kaons","lp");
  leg->AddEntry(mass_soft_proton,"protons","lp");
  leg->AddEntry(mass_soft_proton,"Fastest - Including pT<1GeV  Tracks","lp");
  leg->AddEntry(mass_proton,"Fastest","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();



}

void Mass3() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  TString filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_mitaroff2_eL_pR_cut_0_1track_plt2.root";
  TFile *f = new TFile(filename);

  TH1F*  mass_hitbyhit_kaon = (TH1F*)f->Get("mass_kaon_1");
  TH1F*  mass_hitbyhit_pion = (TH1F*)f->Get("mass_pion_1");
  TH1F*  mass_hitbyhit_proton = (TH1F*)f->Get("mass_proton_1");

  filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_0_1track_plt2.root";
  f = new TFile(filename);

  TH1F*  mass_kaon = (TH1F*)f->Get("mass_kaon_1");
  TH1F*  mass_pion = (TH1F*)f->Get("mass_pion_1");
  TH1F*  mass_proton = (TH1F*)f->Get("mass_proton_1");

  TCanvas* c_mom = new TCanvas("c_mass3","c_mass3",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  gPad->SetLogy();
  mass_pion->GetXaxis()->SetTitle("mass [GeV]");
  mass_pion->GetYaxis()->SetTitle("a.u.");
  //mass_hitbyhit_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_pion->GetXaxis()->SetRangeUser(-0.02,3.02);

  mass_pion->SetLineColor(4);
  mass_pion->SetLineWidth(1);
  mass_pion->SetLineStyle(1);
  mass_pion->Draw("histo");

  mass_kaon->SetLineColor(2);
  mass_kaon->SetLineWidth(1);
  mass_kaon->SetLineStyle(1);
  mass_kaon->Draw("histosame");

  mass_proton->SetLineColor(1);
  mass_proton->SetLineWidth(1);
  mass_proton->SetLineStyle(1);
  mass_proton->Draw("histosame");

  mass_hitbyhit_pion->SetLineColor(4);
  mass_hitbyhit_pion->SetLineWidth(3);
  mass_hitbyhit_pion->SetLineStyle(2);
  mass_hitbyhit_pion->Draw("histosame");

  mass_hitbyhit_kaon->SetLineColor(2);
  mass_hitbyhit_kaon->SetLineWidth(3);
  mass_hitbyhit_kaon->SetLineStyle(2);
  mass_hitbyhit_kaon->Draw("histosame");

  mass_hitbyhit_proton->SetLineColor(1);
  mass_hitbyhit_proton->SetLineWidth(2);
  mass_hitbyhit_proton->SetLineStyle(2);
  mass_hitbyhit_proton->Draw("histosame");
  
 
  Labels("eL");
  
  TLegend *leg = new TLegend(0.4,0.55,0.6,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(mass_hitbyhit_pion,"pions","l");
  leg->AddEntry(mass_hitbyhit_kaon,"kaons","lp");
  leg->AddEntry(mass_hitbyhit_proton,"protons","lp");
  leg->AddEntry(mass_hitbyhit_proton,"Fastest - HitBy Hit Length","lp");
  leg->AddEntry(mass_proton,"Fastest - simple length","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();



}


void MassMom() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  //  TString filename = "../results/tof_all_primary_tracks_ignoreoverlay_2f_hadronic_and_rad_eL_pR_cut_0_1track_plt2.root";
  TString filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_hitbyhitlength_eL_pR_cut_2_1track_plt2_softtrack.root";

  TFile *f = new TFile(filename);
  TH2F*  mass_kaon = (TH2F*)f->Get("p_mass_kaon_1");
  TH2F*  mass_pion = (TH2F*)f->Get("p_mass_pion_1");
  TH2F*  mass_proton = (TH2F*)f->Get("p_mass_proton_1");


  TCanvas* c_mom = new TCanvas("c_mass_mom","c_mass_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  mass_pion->GetXaxis()->SetTitle("momentum [GeV]");
  mass_pion->GetYaxis()->SetTitle("mass [GeV]");
  //mass_fit_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_pion->GetXaxis()->SetRangeUser(0,6);
  mass_pion->GetYaxis()->SetRangeUser(0.01,2);

  mass_pion->SetMarkerColor(4);
  mass_pion->SetLineColor(4);
  mass_pion->SetLineWidth(3);
  mass_pion->SetLineStyle(1);
  mass_pion->Draw("p");

  mass_kaon->SetMarkerColor(2);
  mass_kaon->SetLineColor(2);
  mass_kaon->SetLineWidth(3);
  mass_kaon->SetLineStyle(1);
  mass_kaon->Draw("psame");

  mass_proton->SetMarkerColor(1);
  mass_proton->SetLineColor(1);
  mass_proton->SetLineWidth(3);
  mass_proton->SetLineStyle(1);
  mass_proton->Draw("psame");
 
 
  Labels("eL");
  
  TLegend *leg = new TLegend(0.6,0.65,0.8,0.75);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->SetHeader("Closest");
  leg->AddEntry(mass_pion,"pions","lp");
  leg->AddEntry(mass_kaon,"kaons","lp");
  leg->AddEntry(mass_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();





}

void MassMom2() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  TString filename = "../results/tof_250_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_0_trackmom.root";
  TFile *f = new TFile(filename);

  TH2F*  mass_closest_kaon = (TH2F*)f->Get("p_mass_closest_kaon");
  TH2F*  mass_closest_pion = (TH2F*)f->Get("p_mass_closest_pion");
  TH2F*  mass_closest_proton = (TH2F*)f->Get("p_mass_closest_proton");

  filename = "../results/tof_250_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_0.root";
  TFile *f2 = new TFile(filename);

  TH2F*  mass_closest2_kaon = (TH2F*)f2->Get("p_mass_closest_kaon");
  TH2F*  mass_closest2_pion = (TH2F*)f2->Get("p_mass_closest_pion");
  TH2F*  mass_closest2_proton = (TH2F*)f2->Get("p_mass_closest_proton");

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  mass_closest_pion->GetXaxis()->SetTitle("momentum [GeV]");
  mass_closest_pion->GetYaxis()->SetTitle("mass [GeV]");
  //mass_fit_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_closest_pion->GetXaxis()->SetRangeUser(0,6);
  mass_closest_pion->GetYaxis()->SetRangeUser(0.01,2);

  mass_closest_pion->SetMarkerColor(4);
  mass_closest_pion->SetLineColor(4);
  mass_closest_pion->SetLineWidth(3);
  mass_closest_pion->SetLineStyle(1);
  mass_closest_pion->Draw("p");

  mass_closest_kaon->SetMarkerColor(2);
  mass_closest_kaon->SetLineColor(2);
  mass_closest_kaon->SetLineWidth(3);
  mass_closest_kaon->SetLineStyle(1);
  mass_closest_kaon->Draw("psame");

  mass_closest_proton->SetMarkerColor(1);
  mass_closest_proton->SetLineColor(1);
  mass_closest_proton->SetLineWidth(3);
  mass_closest_proton->SetLineStyle(1);
  mass_closest_proton->Draw("psame");
 
 
  Labels("eL");
  
  TLegend *leg = new TLegend(0.6,0.65,0.8,0.75);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->SetHeader("Closest, track mom from IP");
  leg->AddEntry(mass_closest_pion,"pions","lp");
  leg->AddEntry(mass_closest_kaon,"kaons","lp");
  leg->AddEntry(mass_closest_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

 TCanvas* c_mom2 = new TCanvas("c_mom2","c_mom2",800,800);
  c_mom2->cd(1);
  c_mom2->SetGrid();
  mass_closest2_pion->GetXaxis()->SetTitle("momentum [GeV]");
  mass_closest2_pion->GetYaxis()->SetTitle("mass [GeV]");
  //mass_closest2_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_closest2_pion->GetXaxis()->SetRangeUser(0,6);
  mass_closest2_pion->GetYaxis()->SetRangeUser(0.01,2);

  mass_closest2_pion->SetMarkerColor(4);
  mass_closest2_pion->SetLineColor(4);
  mass_closest2_pion->SetLineWidth(3);
  mass_closest2_pion->SetLineStyle(1);
  mass_closest2_pion->Draw("p");

  mass_closest2_kaon->SetMarkerColor(2);
  mass_closest2_kaon->SetLineColor(2);
  mass_closest2_kaon->SetLineWidth(3);
  mass_closest2_kaon->SetLineStyle(1);
  mass_closest2_kaon->Draw("psame");

  mass_closest2_proton->SetMarkerColor(1);
  mass_closest2_proton->SetLineColor(1);
  mass_closest2_proton->SetLineWidth(3);
  mass_closest2_proton->SetLineStyle(1);
  mass_closest2_proton->Draw("psame");
 
 
  Labels("eL");
  
  TLegend *leg2 = new TLegend(0.6,0.65,0.8,0.75);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->SetHeader("Closest, track mom from calo");
  leg2->AddEntry(mass_closest2_pion,"pions","lp");
  leg2->AddEntry(mass_closest2_kaon,"kaons","lp");
  leg2->AddEntry(mass_closest2_proton,"protons","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();



}

void MassMom3() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  TString filename = "../tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_0_1track.root";
  TFile *f = new TFile(filename);

  TH2F*  mass_closest_kaon = (TH2F*)f->Get("p_mass_kaon_0");
  TH2F*  mass_closest_pion = (TH2F*)f->Get("p_mass_pion_0");
  TH2F*  mass_closest_proton = (TH2F*)f->Get("p_mass_proton_0");

  filename = "../results/tof_all_secondary_tracks_ignoreoverlay_2f_hadronic_eL_pR_cut_0_1track.root";
  TFile *f2 = new TFile(filename);

  TH2F*  mass_closest2_kaon = (TH2F*)f2->Get("p_mass_kaon_0");
  TH2F*  mass_closest2_pion = (TH2F*)f2->Get("p_mass_pion_0");
  TH2F*  mass_closest2_proton = (TH2F*)f2->Get("p_mass_proton_0");

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  mass_closest_pion->GetXaxis()->SetTitle("momentum [GeV]");
  mass_closest_pion->GetYaxis()->SetTitle("mass [GeV]");
  //mass_fit_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_closest_pion->GetXaxis()->SetRangeUser(0,6);
  mass_closest_pion->GetYaxis()->SetRangeUser(0.01,2);

  mass_closest_pion->SetMarkerColor(4);
  mass_closest_pion->SetLineColor(4);
  mass_closest_pion->SetLineWidth(3);
  mass_closest_pion->SetLineStyle(1);
  mass_closest_pion->Draw("p");

  mass_closest_kaon->SetMarkerColor(2);
  mass_closest_kaon->SetLineColor(2);
  mass_closest_kaon->SetLineWidth(3);
  mass_closest_kaon->SetLineStyle(1);
  mass_closest_kaon->Draw("psame");

  mass_closest_proton->SetMarkerColor(1);
  mass_closest_proton->SetLineColor(1);
  mass_closest_proton->SetLineWidth(3);
  mass_closest_proton->SetLineStyle(1);
  mass_closest_proton->Draw("psame");
 
 
  Labels("eL");
  
  TLegend *leg = new TLegend(0.6,0.65,0.8,0.75);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->SetHeader("Closest, 0ps");
  leg->AddEntry(mass_closest_pion,"pions","lp");
  leg->AddEntry(mass_closest_kaon,"kaons","lp");
  leg->AddEntry(mass_closest_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

 TCanvas* c_mom2 = new TCanvas("c_mom2","c_mom2",800,800);
  c_mom2->cd(1);
  c_mom2->SetGrid();
  mass_closest2_pion->GetXaxis()->SetTitle("momentum [GeV]");
  mass_closest2_pion->GetYaxis()->SetTitle("mass [GeV]");
  //mass_closest2_pion->GetYaxis()->SetTitleOffset(1.25);
  mass_closest2_pion->GetXaxis()->SetRangeUser(0,6);
  mass_closest2_pion->GetYaxis()->SetRangeUser(0.01,2);

  mass_closest2_pion->SetMarkerColor(4);
  mass_closest2_pion->SetLineColor(4);
  mass_closest2_pion->SetLineWidth(3);
  mass_closest2_pion->SetLineStyle(1);
  mass_closest2_pion->Draw("p");

  mass_closest2_kaon->SetMarkerColor(2);
  mass_closest2_kaon->SetLineColor(2);
  mass_closest2_kaon->SetLineWidth(3);
  mass_closest2_kaon->SetLineStyle(1);
  mass_closest2_kaon->Draw("psame");

  mass_closest2_proton->SetMarkerColor(1);
  mass_closest2_proton->SetLineColor(1);
  mass_closest2_proton->SetLineWidth(3);
  mass_closest2_proton->SetLineStyle(1);
  mass_closest2_proton->Draw("psame");
 
 
  Labels("eL");
  
  TLegend *leg2 = new TLegend(0.6,0.65,0.8,0.75);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->SetHeader("Closest, 50ps");
  leg2->AddEntry(mass_closest2_pion,"pions","lp");
  leg2->AddEntry(mass_closest2_kaon,"kaons","lp");
  leg2->AddEntry(mass_closest2_proton,"protons","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();



}


void Plots_TOF() {
  //Mass();
  Mass3();
  //MassMom();
  // EffPurity_TOF();
  // EffPurity_TOF();

  //  dEdxdist();
}
