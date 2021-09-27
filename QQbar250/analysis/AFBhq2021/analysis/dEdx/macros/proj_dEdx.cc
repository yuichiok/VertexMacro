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

void color1(TH1D* hists[]){
  for (int i = 0; i < NPAR; ++i) hists[i]->SetLineColor(colors[i]);
}

void draw1(TCanvas* c, TH1D* hists[]){

  c->cd();

  float valMAX = 0;
  for (int i = 0; i < NPAR; ++i){
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

  color1(hists);
  hists[0]->GetYaxis()->SetRangeUser(0,valMAX+100);
  c->Update();

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


  TString filename = "../rootfiles/dEdx_out.root";

  TFile *f = new TFile(filename);

  TH2F* dEdx_truths[5];

  for (int i = 0; i < 5; ++i)
  {
    dEdx_truths[i] = (TH2F*)f->Get(particles[i]);
  }

  // Projection dE/dx

  TCanvas* cs[5];
  float rLow[5]  = {1.0,2.0,5.0,10.0,30.0};
  float rHigh[5] = {1.5,2.5,6.0,11.5,40.0};
  
  for (int i = 0; i < 5; ++i)
  {
    TAxis* xaxis = dEdx_truths[i]->GetXaxis();

    cs[i] = new TCanvas(TString::Format("mom_%.1f_%.1f",rLow[i],rHigh[i]),TString::Format("mom_%.1f_%.1f",rLow[i],rHigh[i]),500,500);
    TH1D* projs[5];

    for (int j = 0; j < NPAR; ++j)
    {
      projs[j] = dEdx_truths[j]->ProjectionY(TString::Format("proj_%s",particles[j].Data()),xaxis->FindBin(rLow[i]),xaxis->FindBin(rHigh[i]));
    }

    draw1(cs[i],projs);

  }


  TFile *MyFile = new TFile("proj_dEdx.root","RECREATE");
  MyFile->cd();
  for (int i = 0; i < 5; ++i)
  {
    cs[i]->Write();
  }

  std::cout << "DONE" << std::endl;
  
  
}
