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

const int NPAR = 5;
const TString particles[5] = {"kaon","proton","pion","electron","muon"};
const Color_t colors[5]    = {kRed,kGreen,kBlue,kBlack,kGray};

void drawTH1D(TCanvas* c, TH1D* hists[]){

  c->cd();

  float valMAX = 0;
  for (int i = 0; i < NPAR; ++i){

    hists[i]->SetLineColor(colors[i]);

    if(i==0){
      hists[i]->Draw();
    }else{
      hists[i]->Draw("same");
    }

    float MAX = hists[i]->GetBinContent(hists[i]->GetMaximumBin());
    if (MAX>valMAX)
    {
      valMAX = MAX;
    }

  }

  hists[0]->GetYaxis()->SetRangeUser(0,valMAX+100);
  c->Update();
  // c->Write();

}

void drawTGEs(TGraphErrors* TGEs[]){

  for (int i = 0; i < NPAR; ++i){

    TGEs[i]->SetLineColor(colors[i]);
    TGEs[i]->SetMarkerColor(colors[i]);
    TGEs[i]->SetMarkerSize(1.0);
    
    if(i==0){
      TGEs[i]->Draw("AP");
    }else{
      TGEs[i]->Draw("Psame");
    }

  } // for NPAR

}

void proj_dEdx() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);


  // TString filename = "../rootfiles/dEdx_out.root";
  TString filename = "../rootfiles/dEdx_test.root";

  TFile *f = new TFile(filename);

  TH2F* dEdx_truths[5];

  for (int i = 0; i < 5; ++i)
  {
    dEdx_truths[i] = (TH2F*)f->Get(particles[i]);
  }


  TFile *MyFile = new TFile("plots/proj_dEdx.root","RECREATE");
  MyFile->cd();

  //////////// Projection Momentum dE/dx ////////////

  float rLow[5]  = {1.0,2.0,5.0,10.0,30.0};
  float rHigh[5] = {1.5,2.5,6.0,11.5,40.0};
  
  for (int i = 0; i < 5; ++i)
  {
    TAxis* xaxis = dEdx_truths[i]->GetXaxis();

    TCanvas *cs_proj = new TCanvas(TString::Format("mom_%.1f_%.1f",rLow[i],rHigh[i]),TString::Format("mom_%.1f_%.1f",rLow[i],rHigh[i]),500,500);
    TH1D* projs[5];

    for (int j = 0; j < NPAR; ++j)
    {
      projs[j] = dEdx_truths[j]->ProjectionY(TString::Format("proj_%s",particles[j].Data()),xaxis->FindBin(rLow[i]),xaxis->FindBin(rHigh[i]));
    }

    drawTH1D(cs_proj,projs);
    cs_proj->Write();

  }


  //////////// Projection Individual dE/dx ////////////

  float momentum_min=0.95;

  TH1D *ind_projs[NPAR];
  TGraphErrors *GEprojs[NPAR];
  TGraphErrors *GEproj2s[NPAR];


  for (int i = 0; i < NPAR; ++i)
  {
    float x[200], y[200], ey[200], ey2[200];
    float ex[200];
    int npt=0;

    for(int j=0; j<dEdx_truths[i]->GetNbinsX(); j++) {

      ind_projs[i] =dEdx_truths[i]->ProjectionY(TString::Format("ind_proj_%s",particles[i].Data()),j,j+1);

      x[npt]=dEdx_truths[i]->GetXaxis()->GetBinCenter(j+1);
      y[npt]=ind_projs[i]->GetMean();
      ey[npt]=ind_projs[i]->GetRMS();
      ey2[npt]=ind_projs[i]->GetMean()/sqrt(ind_projs[i]->GetEntries());
      ex[npt]=0;//dEdx_truths[0]->GetXaxis()->GetBinWidth(i+1)/2.;
      npt++;

    }

    GEprojs[i] = new TGraphErrors(npt,x,y,ex,ey);
    GEprojs[i]->SetName(TString::Format("GE_proj_%s",particles[i].Data()));
    GEprojs[i]->SetTitle(TString::Format("%s;p [GeV];#frac{dE}{dx} [MeV]",particles[i].Data()));

    GEproj2s[i] = new TGraphErrors(npt,x,y,ex,ey2);
    GEproj2s[i]->SetName(TString::Format("GE_proj2_%s",particles[i].Data()));
    GEproj2s[i]->SetTitle(TString::Format("%s_2;p [GeV];#frac{dE}{dx} [MeV]",particles[i].Data()));

  }

  TCanvas* c_ind_proj = new TCanvas("c_ind_proj","c_ind_proj",500,500);
  c_ind_proj->cd();
  c_ind_proj->SetLogx();

  drawTGEs(GEprojs);

  TCanvas* c_ind_proj2 = new TCanvas("c_ind_proj2","c_ind_proj2",500,500);
  c_ind_proj2->cd();
  c_ind_proj2->SetLogx();

  drawTGEs(GEproj2s);


  //////////// Save Plots ////////////

  for (int i = 0; i < NPAR; ++i)
  {
    GEprojs[i]->Write();
    GEproj2s[i]->Write();
  }

  c_ind_proj->Write();
  c_ind_proj2->Write();


 std::cout << "DONE" << std::endl;
  
  
}
