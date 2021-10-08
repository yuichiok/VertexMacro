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


bool cquark;

const TString filename = "../rootfiles/dEdx_d_pcut_5.root";
// const TString filename = "../rootfiles/dEdx_uds_pcut_20.root";

void Labels(TString pol){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(cquark==false) {
    if(pol=="eL")
      QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow b#bar{b} mc-2020",kGray+2);
    else 
      if(pol=="eR")
	QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow b#bar{b} mc-2020",kGray+2);
      else 
	QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow b#bar{b} mc-2020",kGray+2);
    
    QQBARLabel2(0.2,0.22, "Secondary Tracks in b-jets",kGray+4);
  } else {
    if(pol=="eL")
      QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
    else 
      if(pol=="eR")
	QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
      else 
	QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
    
    QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);
  }
      

}


void EffPurity_default() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  //*-------------  
  // TString filename = "../results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_2GeV.root";
  // TString filename = "../rootfiles/dEdx_test.root";
  TFile *f = new TFile(filename);

  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  
  TH1F*  prob_pi_kaon = (TH1F*)f->Get("pi_prob_kaon_method2");
  TH1F*  prob_pi_pion = (TH1F*)f->Get("pi_prob_pion_method2");
  TH1F*  prob_pi_proton = (TH1F*)f->Get("pi_prob_proton_method2");
  TH1F*  prob_pi_muon = (TH1F*)f->Get("pi_prob_muon_method2");
  TH1F*  prob_pi_electron = (TH1F*)f->Get("pi_prob_electron_method2");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=1;i<100; i++) {
    float n_kaons=  prob_pi_kaon->Integral(0,i);
    float n_pions=  prob_pi_pion->Integral(0,i);
    float n_protons=  prob_pi_proton->Integral(0,i);
    float n_muons=  prob_pi_muon->Integral(0,i);
    float n_electrons=  prob_pi_electron->Integral(0,i);
    // cout<<n_kaons<<endl;

    x[i-1]=i*1.0/100.;
    //    eff[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-1]=100.*(n_kaons)/nkaons;
    pur[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);


  cquark=false;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  efficiency->GetXaxis()->SetTitle("Prob-#pi < x");
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

  
  // Labels("");
  
  TLegend *leg0 = new TLegend(0.6,0.8,0.8,0.9);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_mom2 = new TCanvas("c_mom2","c_mom2",800,800);
  c_mom2->cd(1);
  c_mom2->SetGrid();
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");

  // Labels("");
  QQBARLabel2(0.3,0.2, "Method dEdxPID",kBlack);

  TLegend *leg1 = new TLegend(0.6,0.8,0.8,0.9);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(efficiency_purity,"Left Polarisation","lp");
  // leg1->AddEntry(efficiency_purity2,"Right Polarisation","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   
}


void EffPurity_dedxdist() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  // TString filename = "../results/histos_bquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_2GeV.root";
  // TString filename = "../rootfiles/dEdx_test.root";
  TFile *f = new TFile(filename);
  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  kdEdxdist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon = (TH1F*)f->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron = (TH1F*)f->Get("kdEdx_dist_electron");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(16,i);
    float n_pions=  kdEdxdist_pion->Integral(16,i);
    float n_protons=  kdEdxdist_proton->Integral(16,i);
    float n_muons=  kdEdxdist_muon->Integral(16,i);
    float n_electrons=  kdEdxdist_electron->Integral(16,i);
    x[i-16]=i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-16]=100.*(n_kaons)/nkaons;                    
    pur[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);


  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  efficiency->GetXaxis()->SetTitle("i");
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

  
  // Labels("");
  
  TLegend *leg0 = new TLegend(0.2,0.2,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_mom3 = new TCanvas("c_mom3","c_mom3",800,800);
  c_mom3->cd(1);
  c_mom3->SetGrid();
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");


  Labels("");
  QQBARLabel2(0.3,0.2, "Method dEdx-distance",kBlack);

  TLegend *leg1 = new TLegend(0.2,0.8,0.5,0.9);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(efficiency_purity,"Left Polarisation","lp");
  // leg1->AddEntry(efficiency_purity2,"Right Polarisation","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   
}


void EffPurity_dedxdist3() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  // TString filename = "../results/histos_bquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  // TString filename = "../rootfiles/dEdx_test.root";
  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=2;i<60; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,22);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,22);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,22);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,22);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,22);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,40);
    x[i-2]=i-1.5;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-2]=100.*(n_kaons)/nkaons;                    
    pur[i-2]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
  
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  efficiency->GetXaxis()->SetTitle(" momentum [GeV]");
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

  
  // Labels("");
  
  TLegend *leg0 = new TLegend(0.2,0.3,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  
  // Labels("");
  
  TLegend *leg2 = new TLegend(0.2,0.3,0.5,0.4);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(efficiency,"Efficiency","lp");
  leg2->AddEntry(purity,"Purity","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();
 
}



void EffPurity_dedxdist4() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  // TString filename = "../results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_2GeV.root";
  // TString filename = "../rootfiles/dEdx_test.root";

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("costheta_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("costheta_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("costheta_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("costheta_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("costheta_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=1;i<21; i++) {
    int ipion=22;
    if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i);

    if(nkaons==0) nkaons=10000000;
    x[i-1]=i*1./20;
    eff[i-1]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

  // cout << eff[0] << ", " << pur[0] << endl;

 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
  
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  efficiency->GetXaxis()->SetTitle("cos #theta");
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



void EffPurity_dedxdist5() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  // TString filename = "../results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_2GeV.root";
  // TString filename = "../rootfiles/dEdx_out.root";
  // TString filename = "../rootfiles/dEdx_test.root";

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=0;i<80; i++) {
    int iproton=16;
    int ipion=22;
    // int iproton=16;
    // int ipion=21;
    // if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,iproton,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,iproton,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,iproton,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,iproton,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,iproton,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i);
    if(nkaons==0) nkaons=10000000;
    x[i]=i;
    eff[i]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
  cquark=false;

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  efficiency->GetXaxis()->SetTitle("p [GeV]");
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

  
  // Labels("");
  
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


void EffPurity_dedxdist2() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  // TString filename = "../results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  // TString filename = "../rootfiles/dEdx_test.root";

  TFile *f = new TFile(filename);
  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  kdEdxdist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon = (TH1F*)f->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron = (TH1F*)f->Get("kdEdx_dist_electron");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(16,i);
    float n_pions=  kdEdxdist_pion->Integral(16,i);
    float n_protons=  kdEdxdist_proton->Integral(16,i);
    float n_muons=  kdEdxdist_muon->Integral(16,i);
    float n_electrons=  kdEdxdist_electron->Integral(16,i);
    x[i-16]=16+i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-16]=100.*(n_kaons)/nkaons;                    
    pur[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);


  cquark=false;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  efficiency->GetXaxis()->SetTitle("i");
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

  
  // Labels("");
  
  TLegend *leg0 = new TLegend(0.6,0.25,0.8,0.35);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_mom3 = new TCanvas("c_mom3","c_mom3",800,800);
  c_mom3->cd(1);
  c_mom3->SetGrid();
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");

  // Labels("eL");
  // QQBARLabel2(0.3,0.2, "Method dEdx-distance",kBlack);

  TLegend *leg1 = new TLegend(0.6,0.25,0.8,0.35);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(efficiency_purity,"|p_{track}|> 0 GeV","lp");
  // leg1->AddEntry(efficiency_purity2,"|p_{track}|> 2 GeV","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   
}

void Mom() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  // TString filename = "../results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  // TString filename = "../rootfiles/dEdx_pcut_2.root";
  TFile *f = new TFile(filename);

  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  p_pion = (TH1F*)f->Get("p_pion");
  TH1F*  p_proton = (TH1F*)f->Get("p_proton");

  cquark=false;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  p_pion->GetXaxis()->SetTitle("momentum [GeV]");
  p_pion->GetYaxis()->SetTitle("a.u.");
  //p_pion->GetYaxis()->SetTitleOffset(1.25);
  //p_pion->GetXaxis()->SetTitleOffset(1.);

  p_pion->SetLineColor(4);
  p_pion->SetLineWidth(3);
  p_pion->SetLineStyle(1);
  p_pion->Draw("histo");

  p_kaon->SetLineColor(2);
  p_kaon->SetLineWidth(3);
  p_kaon->SetLineStyle(1);
  p_kaon->Draw("histosame");

  p_proton->SetLineColor(1);
  p_proton->SetLineWidth(3);
  p_proton->SetLineStyle(1);
  p_proton->Draw("histosame");
    
  TLegend *leg = new TLegend(0.6,0.25,0.8,0.35);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(p_pion,"pions","l");
  leg->AddEntry(p_kaon,"kaons","lp");
  leg->AddEntry(p_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

}

void dEdxdist() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);
  
  
  // TString filename = "../results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_2GeV.root";
  // TString filename = "../rootfiles/dEdx_pcut_2.root";
  TFile *f = new TFile(filename);

  TH1F*  kdEdx_dist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton = (TH1F*)f->Get("kdEdx_dist_proton");

  // cquark=true;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  kdEdx_dist_pion->GetXaxis()->SetTitle("signed [(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}]^{2}");
  kdEdx_dist_pion->GetYaxis()->SetTitle("a.u.");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);

  kdEdx_dist_pion->SetLineColor(4);
  kdEdx_dist_pion->SetLineWidth(3);
  kdEdx_dist_pion->SetLineStyle(1);
  kdEdx_dist_pion->Draw("histo");

  kdEdx_dist_kaon->SetLineColor(2);
  kdEdx_dist_kaon->SetLineWidth(3);
  kdEdx_dist_kaon->SetLineStyle(1);
  kdEdx_dist_kaon->Draw("histosame");

  kdEdx_dist_proton->SetLineColor(1);
  kdEdx_dist_proton->SetLineWidth(3);
  kdEdx_dist_proton->SetLineStyle(1);
  kdEdx_dist_proton->Draw("histosame");
  

  TF1 *f_k= new TF1("f_k","gaus",-4,4);
  kdEdx_dist_kaon->Fit(f_k,"SR");
  f_k->Draw("lsame");
  f_k->SetLineColor(2);
  f_k->SetLineWidth(2);
  f_k->SetLineStyle(2);
  f_k->Draw("lsame");

  TF1 *f_pi= new TF1("f_pi","gaus",-1,7);
  kdEdx_dist_pion->Fit(f_pi,"SR");
  f_pi->Draw("lsame");
  f_pi->SetLineColor(4);
  f_pi->SetLineWidth(2);
  f_pi->SetLineStyle(2);
  f_pi->Draw("lsame");

  
 
  // Labels("eL");
  
  TLegend *leg = new TLegend(0.2,0.7,0.5,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(kdEdx_dist_pion,"pions","l");
  leg->AddEntry(kdEdx_dist_kaon,"kaons","lp");
  leg->AddEntry(kdEdx_dist_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


}


void plots_dEdx_ss() {
  // Mom();
  // EffPurity_default();
  // EffPurity_dedxdist();
  // EffPurity_dedxdist2();
  // EffPurity_dedxdist3();
  // EffPurity_dedxdist4();
  // EffPurity_dedxdist5();
  dEdxdist();
}
