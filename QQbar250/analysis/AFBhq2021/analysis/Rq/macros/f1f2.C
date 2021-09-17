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
#include "utils.h"
#include "histograms.h"

//pol=0 eLpR
//pol=1 eRpL
//pol=2 eLpR 80/30
//pol=3 eRpL 80/30



TH1F* f1sample(int sample=0, int pol=0, int iquark=5,  float lum=900){

  int ipdgquark=0;
  if(iquark==5) ipdgquark=0;
  if(iquark==4) ipdgquark=1;


  TH1F *h0=GetHisto(sample,TString::Format("h_N0_%i",ipdgquark),pol,iquark,lum,2);
  TH1F *h1=GetHisto(sample,TString::Format("h_N1_%i",ipdgquark),pol,iquark,lum,1);

  h1->Divide(h0);
  return h1;

}

std::vector<TH1F*> f1(int pol=0, int iquark=5,  float lum=900){

  //TString process[5]={"4f_ZZ_hadronic","qqH","4f_WW_hadronic","2f_hadronic_sample","2f_hadronic"};

  TH1F *h0[10];
  TH1F *h1[10];

  int ipdgquark=0;
  if(iquark==5) ipdgquark=0;
  if(iquark==4) ipdgquark=1;

  int ipdgquark2=0;
  if(iquark==5) ipdgquark2=1;
  if(iquark==4) ipdgquark2=0;

  //ZZ
  h0[0]=GetHisto(0,"h_N0_0",pol,iquark,lum,2);
  h1[0]=GetHisto(0,"h_N1_0",pol,iquark,lum,1);
  //hz
  h0[1]=GetHisto(1,"h_N0_0",pol,iquark,lum,2);
  h1[1]=GetHisto(1,"h_N1_0",pol,iquark,lum,1);
  //ww
  h0[2]=GetHisto(2,"h_N0_0",pol,iquark,lum,2);
  h1[2]=GetHisto(2,"h_N1_0",pol,iquark,lum,1);
  //rad return
  h0[3]=GetHisto(3,"h_N0_3",pol,iquark,lum,2);
  h1[3]=GetHisto(3,"h_N1_3",pol,iquark,lum,1);
  //bkg-uds
  h0[4]=GetHisto(3,TString::Format("h_N0_%i",2),pol,iquark,lum,2);
  h1[4]=GetHisto(3,TString::Format("h_N1_%i",2),pol,iquark,lum,1);
  //bkg-heavyquark
  h0[5]=GetHisto(3,TString::Format("h_N0_%i",ipdgquark2),pol,iquark,lum,2);
  h1[5]=GetHisto(3,TString::Format("h_N1_%i",ipdgquark2),pol,iquark,lum,1);
  //signal
  h0[6]=GetHisto(4,TString::Format("h_N0_%i",ipdgquark),pol,iquark,lum,2);
  h1[6]=GetHisto(4,TString::Format("h_N1_%i",ipdgquark),pol,iquark,lum,1);

  h0[0]->Add(h0[1]);
  h0[0]->Add(h0[2]);
  h0[0]->Add(h0[3]);
  h0[0]->Add(h0[4]);
  h0[0]->Add(h0[5]);
  h0[0]->Add(h0[6]);

  std::vector<TH1F*> result;
  for(int i=0; i<7; i++) {
    h1[i]->Divide(h0[0]);
    result.push_back(h1[i]);
  }
  return result;

}

void f1PlotsSample(int sample=0, int iquark=5, float lum=-1) {


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  
  TH1F *hf1[2];
  TGraphErrors * g_f1[2];
  for(int i=0; i<2; i++) {
    hf1[i]=f1sample(sample,2,iquark,lum);
    g_f1[i]= new TGraphErrors(hf1[i]);
  }

  


  TCanvas* c_f1_MC = new TCanvas("c_f1_MC","c_f1_MC",800,800);
  c_f1_MC->cd(1);
  c_f1_MC->SetGrid();
  g_f1[0]->GetXaxis()->SetTitle("cos #theta_{thrust}");
  g_f1[0]->GetYaxis()->SetTitle("Mis-ID [%]");
  g_f1[0]->GetYaxis()->SetTitleOffset(1.25);
  g_f1[0]->GetXaxis()->SetTitleOffset(1.);
  g_f1[0]->GetYaxis()->SetRangeUser(0,2);
  g_f1[0]->GetXaxis()->SetRangeUser(0,1);
  g_f1[0]->SetLineColor(4);
  g_f1[0]->SetLineWidth(1);
  g_f1[0]->SetMarkerStyle(0);
  g_f1[0]->Draw("alp");

  g_f1[1]->SetLineColor(4);
  g_f1[1]->SetLineWidth(2);
  g_f1[1]->SetLineStyle(2);
  g_f1[1]->SetMarkerStyle(0);
  g_f1[1]->Draw("lp");


  Labels(2,iquark,3000);

  c_f1_MC->Print(TString::Format("summaryplots/F1_sample_%i_pdg_%i_twopols.png",sample,iquark));
  c_f1_MC->Update();
}


void f1Plots(int iquark=5, float lum=-1) {


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  
  TH1F *hf1[15];
  TGraphErrors * g_f1[15];
  std::vector<TH1F*> result=f1(2,iquark,lum);
  for(int i=0; i<7; i++) {
    hf1[i]=result.at(i);
    g_f1[i]= new TGraphErrors(hf1[i]);
  }

  
  //signal
  hf1[6]->SetLineColor(1);
  hf1[6]->SetLineWidth(2);
  //heavy quark bkg
  hf1[5]->SetLineColor(4);
  hf1[5]->SetLineWidth(2);
  hf1[5]->SetFillColor(4);
  //uds quark bkg
  hf1[4]->SetLineColor(kMagenta+2);
  hf1[4]->SetLineWidth(2);
  hf1[4]->SetFillColor(kMagenta+2);
  //radreturn
  hf1[3]->SetLineColor(kGreen+1);
  hf1[3]->SetLineWidth(2);
  hf1[3]->SetFillColor(kGreen+1);

  for(int i=0; i<3; i++) {
    hf1[i]->SetFillColor(kGray+i);
    hf1[i]->SetLineColor(kGray+i);
  }

  THStack *f1stack = new THStack("f1stack","");
  for(int i=0; i<7; i++) f1stack->Add(hf1[i]);


  TCanvas* c_f1_MC = new TCanvas("c_f1_MC","c_f1_MC",800,800);
  c_f1_MC->cd(1);
  c_f1_MC->SetGrid();
  f1stack->Draw("histoe");


  Labels(2,iquark,900);

  c_f1_MC->Print(TString::Format("summaryplots/F1_pdg_%i_twopols.png",iquark));
  c_f1_MC->Update();
}



void f1f2() {

  int sample=3; //3= signal, no cuts in rad return; 4= signa+radreturncut, 0=zz, 1=hz, 2=ww

  f1Plots(4,900);


}
