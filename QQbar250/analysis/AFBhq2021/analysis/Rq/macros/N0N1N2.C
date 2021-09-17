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

std::vector<TH1F*> Histograms(int histo=0, int pol=0, int iquark=5,  float lum=900){

  //TString process[5]={"4f_ZZ_hadronic","qqH","4f_WW_hadronic","2f_hadronic_sample","2f_hadronic"};

  TH1F *h0[10];

  int ipdgquark=0;
  if(iquark==5) ipdgquark=0;
  if(iquark==4) ipdgquark=1;

  int ipdgquark2=0;
  if(iquark==5) ipdgquark2=1;
  if(iquark==4) ipdgquark2=0;

  //ZZ
  h0[0]=GetHisto(0,TString::Format("h_N%i_0",histo),pol,iquark,lum,1);
  //hz
  h0[1]=GetHisto(1,TString::Format("h_N%i_0",histo),pol,iquark,lum,1);
  //ww
  h0[2]=GetHisto(2,TString::Format("h_N%i_0",histo),pol,iquark,lum,1);
  //rad return
  h0[3]=GetHisto(3,TString::Format("h_N%i_3",histo),pol,iquark,lum,1);
  //bkg-uds
  h0[4]=GetHisto(4,TString::Format("h_N%i_%i",histo,2),pol,iquark,lum,1);
  //bkg-heavyquark
  h0[5]=GetHisto(4,TString::Format("h_N%i_%i",histo,ipdgquark2),pol,iquark,lum,1);
  //signal
  h0[6]=GetHisto(4,TString::Format("h_N%i_%i",histo,ipdgquark),pol,iquark,lum,1);

  /* h0[0]->Add(h0[1]);
  h0[0]->Add(h0[2]);
  h0[0]->Add(h0[3]);
  h0[0]->Add(h0[4]);
  h0[0]->Add(h0[5]);
  h0[0]->Add(h0[6]);*/

  std::vector<TH1F*> result;
  for(int i=0; i<7; i++) {
    result.push_back(h0[i]);
  }
  return result;

}


void NPlots(int iquark=5, float lum=-1, int pol=0) {


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  for(int ihisto=0; ihisto<3; ihisto++) {
    
    TH1F *Nhisto[15];
    std::vector<TH1F*> result=Histograms(ihisto,pol,iquark,lum);
    for(int i=0; i<7; i++) {
      Nhisto[i]=result.at(i);
    }
    
    if(iquark==4) {
      //signal
      Nhisto[6]->SetLineColor(2);
      Nhisto[6]->SetLineWidth(2);
      Nhisto[6]->SetFillColor(2);
      
      //heavy quark bkg
      Nhisto[5]->SetLineColor(4);
      Nhisto[5]->SetLineWidth(2);
      Nhisto[5]->SetFillColor(4);
    }

    if(iquark==5) {
      //c-quark bkg
      Nhisto[5]->SetLineColor(2);
      Nhisto[5]->SetLineWidth(2);
      Nhisto[5]->SetFillColor(2);
      
      //signakl
      Nhisto[6]->SetLineColor(4);
      Nhisto[6]->SetLineWidth(2);
      Nhisto[6]->SetFillColor(4);
    }
    //uds quark bkg
    Nhisto[4]->SetLineColor(kMagenta+2);
    Nhisto[4]->SetLineWidth(2);
    Nhisto[4]->SetFillColor(kMagenta+2);
    //radreturn
    Nhisto[3]->SetLineColor(kGreen+1);
    Nhisto[3]->SetLineWidth(2);
    Nhisto[3]->SetFillColor(kGreen+1);
    Nhisto[3]->SetFillStyle(3001);

    for(int i=0; i<3; i++) {
      Nhisto[i]->SetFillColor(kGray+i);
      Nhisto[i]->SetLineColor(kGray+i);
      Nhisto[i]->SetFillStyle(3002+i);
    }
    
    THStack *f1stack = new THStack("f1stack","");
    for(int i=0; i<7; i++) f1stack->Add(Nhisto[i]);
    
    
    TCanvas* c_f1_MC = new TCanvas(TString::Format("c_f1_MC_%i",ihisto),TString::Format("c_f1_MC_%i",ihisto),800,800);
    c_f1_MC->cd(1);
    c_f1_MC->SetGrid();
    f1stack->Draw("histoe");
    f1stack->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
    f1stack->GetYaxis()->SetTitle("entries");
    c_f1_MC->Update();

    Labels(pol,iquark,900);

    TLegend *leg = new TLegend(0.2,0.7,0.55,0.9);
    leg->SetHeader(TString::Format("N_{%i} distribution",ihisto));
    TString signal="c#bar{c}";
    TString qbkg="b#bar{b}";

    if(iquark==5) {
      signal="b#bar{b}";
      qbkg="c#bar{c}";
    }

    leg->AddEntry(Nhisto[6],signal,"lf");
    leg->AddEntry(Nhisto[5],qbkg,"lf");
    leg->AddEntry(Nhisto[4],"q#bar{q}, q=uds","lf");
    leg->AddEntry(Nhisto[3],"Z#gamma","lf");
    leg->AddEntry(Nhisto[2],"WW","lf");
    leg->AddEntry(Nhisto[1],"HZ","lf");
    leg->AddEntry(Nhisto[0],"ZZ","lf");


    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->Draw();

    c_f1_MC->Print(TString::Format("summaryplots/N%i_pdg_%i_pol_%i.eps",ihisto,iquark,pol));
  }
  
}



void N0N1N2() {

  NPlots(4,900,0);
  NPlots(5,900,0);
  NPlots(4,900,1);
  NPlots(5,900,1);
  NPlots(4,900,2);
  NPlots(5,900,2);
  NPlots(4,900,3);
  NPlots(5,900,3);

}
