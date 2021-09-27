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

// void getProj(TH2F dEdx_truths[]){

//   TH1D * proj_kaon = kaon_dEdx_truth->ProjectionY("proj_kaon",22,22);

// }


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

  TString particles[5] = {"kaon","proton","pion","electron","muon"};
  Color_t colors[5]    = {kRed,kGreen,kBlue,kBlack,kGray};
  TH2F* dEdx_truths[5];

  for (int i = 0; i < 5; ++i)
  {
    dEdx_truths[i] = (TH2F*)f->Get(particles[i]);
  }



  // Projection dE/dx
  
  TCanvas *c1 = new TCanvas("c1","c1",500,500);

  TH1D* projs[5];
  float valMAX = 0;
  for (int i = 0; i < 5; ++i)
  {
    projs[i] = dEdx_truths[i]->ProjectionY(TString::Format("proj_%s",particles[i].Data()),22,22);
    projs[i]->SetLineColor(colors[i]);

    float MAX = projs[i]->GetMaximum();
    if (MAX>valMAX)
    {
      valMAX = MAX;
    }

    // if(i==0){
    //   projs[i]->Draw();
    // }else{
    //   projs[i]->Draw("same");
    // }
  }

  // projs[0]->GetYaxis()->SetRangeUser(0,valMAX+100);





  // TH2F* kaon_dEdx_truth     = (TH2F*)f->Get("kaon");
  // TH2F* proton_dEdx_truth   = (TH2F*)f->Get("proton");
  // TH2F* pion_dEdx_truth     = (TH2F*)f->Get("pion");
  // TH2F* electron_dEdx_truth = (TH2F*)f->Get("electron");
  // TH2F* muon_dEdx_truth     = (TH2F*)f->Get("muon");

  // TCanvas *c1 = new TCanvas("c1","c1",500,500);

  // TH1D * proj_kaon = kaon_dEdx_truth->ProjectionY("proj_kaon",22,22);
  // TH1D * proj_proton = proton_dEdx_truth->ProjectionY("proj_proton",22,22);
  // TH1D * proj_pion = pion_dEdx_truth->ProjectionY("proj_pion",22,22);
  // TH1D * proj_electron = electron_dEdx_truth->ProjectionY("proj_electron",22,22);
  // TH1D * proj_muon = muon_dEdx_truth->ProjectionY("proj_muon",22,22);

  // proj_kaon->Draw();
  // proj_proton->Draw();
  // proj_pion->Draw();
  // proj_electron->Draw();
  // proj_muon->Draw();

  std::cout << "DONE" << std::endl;
  
  
}
