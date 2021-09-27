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

void draw1(TH1D* hists[]){

  float valMAX = 0;
  for (int i = 0; i < NPAR; ++i){
    if(i==0){
      hists[i]->Draw();
    }else{
      hists[i]->Draw("same");
    }

    float MAX = hists[i]->GetMaximum();
    if (MAX>valMAX)
    {
      valMAX = MAX;
    }

  }

  color1(hists);
  hists[0]->GetYaxis()->SetRangeUser(0,valMAX+100);

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


  std::cout << dEdx_truths[0]->GetXaxis()->FindBin(1.0) << ", " << dEdx_truths[0]->GetXaxis()->FindBin(1.5) << std::endl;
  std::cout << dEdx_truths[0]->GetXaxis()->FindBin(2.0) << ", " << dEdx_truths[0]->GetXaxis()->FindBin(2.5) << std::endl;
  std::cout << dEdx_truths[0]->GetXaxis()->FindBin(5.0) << ", " << dEdx_truths[0]->GetXaxis()->FindBin(6.0) << std::endl;
  std::cout << dEdx_truths[0]->GetXaxis()->FindBin(10.0) << ", " << dEdx_truths[0]->GetXaxis()->FindBin(11.5) << std::endl;
  std::cout << dEdx_truths[0]->GetXaxis()->FindBin(30.0) << ", " << dEdx_truths[0]->GetXaxis()->FindBin(40.0) << std::endl;

  // Projection dE/dx
  
  TCanvas *c1 = new TCanvas("c1","c1",500,500);

  TH1D* projs[5];

  for (int i = 0; i < NPAR; ++i)
  {
    projs[i] = dEdx_truths[i]->ProjectionY(TString::Format("proj_%s",particles[i].Data()),22,22);
  }

  draw1(projs);

  std::cout << "DONE" << std::endl;
  
  
}
