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

// const TString filename = "../rootfiles/maxp10/DQ_250GeV_ss.kpkm.pvcut.maxp10.root";
// const TString filename = "../rootfiles/maxp10/DQ_250GeV_uu.kpkm.pvcut.maxp10.root";
// const TString filename = "../rootfiles/maxp10/DQ_250GeV_dd.kpkm.pvcut.maxp10.root";
// const TString filename = "../rootfiles/maxp10/DQ_250GeV_uds.kpkm.pvcut.maxp10.root";

// const TString filename = "../rootfiles/maxp10/DQ_250GeV_ss.kpkm.maxp10.root";
// const TString filename = "../rootfiles/maxp10/DQ_250GeV_dd.kpkm.maxp10.root";
// const TString filename = "../rootfiles/maxp10/DQ_250GeV_uu.kpkm.maxp10.root";
// const TString filename = "../rootfiles/maxp10/DQ_250GeV_uds.kpkm.maxp10.root";

// const TString filename = "../rootfiles/DQ_250GeV_ss.minp10.test2.root";
// const TString filename = "../rootfiles/DQ_250GeV_dd.minp10.test.root";
// const TString filename = "../rootfiles/DQ_250GeV_uu.minp10.test.root";
const TString filename = "../rootfiles/DQ_250GeV_uds.minp10.test2.root";

// const TString filename = "../rootfiles/DQ_250GeV_uds.minp60.test2.root";

void normalize(TH1F* h = 0){

  h->Scale(1/h->GetEntries());

}

void EffPurity_dedxdist5() {
  
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("h_pfo_p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("h_pfo_p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("h_pfo_p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("h_pfo_p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("h_pfo_p_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;

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

void dEdxdist_k() {
  
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);
  
  TFile *f = new TFile(filename);

  TH1F*  kdEdx_dist_kaon = (TH1F*)f->Get("h_pfo_kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion = (TH1F*)f->Get("h_pfo_kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton = (TH1F*)f->Get("h_pfo_kdEdx_dist_proton");

  // cquark=true;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  kdEdx_dist_pion->GetXaxis()->SetTitle("signed [(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}]^{2}");
  kdEdx_dist_pion->GetYaxis()->SetTitle("a.u.");

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

void dEdxdist_p() {
  
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);
  
  TFile *f = new TFile(filename);

  TH1F*  pdEdx_dist_kaon = (TH1F*)f->Get("h_pfo_pdEdx_dist_kaon");
  TH1F*  pdEdx_dist_pion = (TH1F*)f->Get("h_pfo_pdEdx_dist_pion");
  TH1F*  pdEdx_dist_proton = (TH1F*)f->Get("h_pfo_pdEdx_dist_proton");

  // cquark=true;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  pdEdx_dist_pion->GetXaxis()->SetTitle("signed [(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}]^{2}");
  pdEdx_dist_pion->GetYaxis()->SetTitle("a.u.");

  pdEdx_dist_pion->SetLineColor(4);
  pdEdx_dist_pion->SetLineWidth(3);
  pdEdx_dist_pion->SetLineStyle(1);
  pdEdx_dist_pion->Draw("histo");

  pdEdx_dist_kaon->SetLineColor(2);
  pdEdx_dist_kaon->SetLineWidth(3);
  pdEdx_dist_kaon->SetLineStyle(1);
  pdEdx_dist_kaon->Draw("histosame");

  pdEdx_dist_proton->SetLineColor(1);
  pdEdx_dist_proton->SetLineWidth(3);
  pdEdx_dist_proton->SetLineStyle(1);
  pdEdx_dist_proton->Draw("histosame");
  

  TF1 *f_k= new TF1("f_k","gaus",-4,4);
  pdEdx_dist_kaon->Fit(f_k,"SR");
  f_k->Draw("lsame");
  f_k->SetLineColor(2);
  f_k->SetLineWidth(2);
  f_k->SetLineStyle(2);
  f_k->Draw("lsame");

  TF1 *f_pi= new TF1("f_pi","gaus",-1,7);
  pdEdx_dist_pion->Fit(f_pi,"SR");
  f_pi->Draw("lsame");
  f_pi->SetLineColor(4);
  f_pi->SetLineWidth(2);
  f_pi->SetLineStyle(2);
  f_pi->Draw("lsame");
  
  TLegend *leg = new TLegend(0.2,0.7,0.5,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(pdEdx_dist_pion,"pions","l");
  leg->AddEntry(pdEdx_dist_kaon,"kaons","lp");
  leg->AddEntry(pdEdx_dist_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

}

void pv() {

  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);
  
  TFile *f = new TFile(filename);

  TH1F*  pfo_pv_kaon   = (TH1F*)f->Get("h_pfo_pv_kaon");
  TH1F*  pfo_pv_pion   = (TH1F*)f->Get("h_pfo_pv_pion");
  TH1F*  pfo_pv_proton = (TH1F*)f->Get("h_pfo_pv_proton");


  normalize(pfo_pv_kaon);
  normalize(pfo_pv_pion);
  normalize(pfo_pv_proton);


  // cquark=true;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  pfo_pv_pion->GetXaxis()->SetTitle("sqrt(d0^2 + z0^2)");
  pfo_pv_pion->GetYaxis()->SetTitle("a.u.");

  pfo_pv_pion->SetLineColor(4);
  pfo_pv_pion->SetLineWidth(3);
  pfo_pv_pion->SetLineStyle(1);
  pfo_pv_pion->Draw("histo");

  pfo_pv_kaon->SetLineColor(2);
  pfo_pv_kaon->SetLineWidth(3);
  pfo_pv_kaon->SetLineStyle(1);
  pfo_pv_kaon->Draw("histosame");

  pfo_pv_proton->SetLineColor(1);
  pfo_pv_proton->SetLineWidth(3);
  pfo_pv_proton->SetLineStyle(1);
  pfo_pv_proton->Draw("histosame");
  

  // TF1 *f_k= new TF1("f_k","gaus",-4,4);
  // kdEdx_dist_kaon->Fit(f_k,"SR");
  // f_k->Draw("lsame");
  // f_k->SetLineColor(2);
  // f_k->SetLineWidth(2);
  // f_k->SetLineStyle(2);
  // f_k->Draw("lsame");

  // TF1 *f_pi= new TF1("f_pi","gaus",-1,7);
  // kdEdx_dist_pion->Fit(f_pi,"SR");
  // f_pi->Draw("lsame");
  // f_pi->SetLineColor(4);
  // f_pi->SetLineWidth(2);
  // f_pi->SetLineStyle(2);
  // f_pi->Draw("lsame");
  
  TLegend *leg = new TLegend(0.2,0.7,0.5,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(pfo_pv_pion,"pions","l");
  leg->AddEntry(pfo_pv_kaon,"kaons","lp");
  leg->AddEntry(pfo_pv_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

}


void plots_dEdx_dist() {

  EffPurity_dedxdist5();
  // dEdxdist_k();
  // dEdxdist_p();
  // pv();
}
