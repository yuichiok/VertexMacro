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
#include "../../common/cross_sections.h"


TString folder="../results/Rq_";
float p1error=0;
float p2error=0;
//pol=0 eLpR
//pol=1 eRpL
//pol=2 eLpR 80/30
//pol=3 eRpL 80/30

TString process[5]={"4f_ZZ_hadronic","qqH","4f_WW_hadronic","2f_hadronic_sample","2f_hadronic"};



TH1F * ScaleHisto(TH1F *h, float luminosity, float lum_goal, float norm=1) {

  TH1F *hnew = (TH1F*)h->Clone("hnew");
  if(lum_goal<0) lum_goal=luminosity;
  for(int i=0; i<hnew->GetNbinsX()+1; i++) {
    float sigma=h->GetBinContent(i)*norm/luminosity;
    float nprime=sigma*lum_goal;
    hnew->SetBinError(i,sqrt(nprime));
    hnew->SetBinContent(i,nprime);
    //    cout<<luminosity<<" "<<lum_goal<<" "<<norm<<" "<<h->GetBinContent(i)<<" "<<hnew->GetBinContent(i)<<endl;

  }

  return hnew;

}

TH1F * PolHisto(TH1F *h1, TH1F* h2, int pol, float luminosity[], float lum_goal, float norm=1) {

  TH1F *hnew = (TH1F*)h1->Clone("hnew");
  float global=0, a=0., b=0.;
  float p1=-0.8, p2=0.3;

  if(pol==3) {
    p1=0.8;
    p2=-0.3;
  }
  p1+=p1error;
  p2+=p2error;

  global= 0.25* (1-p1*p2);
  float peff = (p1-p2)/(1-p1*p2);

  a=global*(1-peff);
  b=global*(1+peff);

  for(int i=0; i<hnew->GetNbinsX()+1; i++) {
    float sigma1=h1->GetBinContent(i)*norm/luminosity[0];
    float nprime1=a*sigma1*lum_goal;
    float sigma2=h2->GetBinContent(i)*norm/luminosity[1];
    float nprime2=b*sigma2*lum_goal;

    if(lum_goal<1) {
      sigma1=norm*h1->GetBinContent(i);
      nprime1=a*sigma1;
      sigma2=norm*h2->GetBinContent(i);
      nprime2=b*sigma2;
    }
    double lum_max=TMath::Max(luminosity[0],luminosity[1]);
    if(lum_goal<1 && pol>1) {
      sigma1=norm*h1->GetBinContent(i)*lum_max/luminosity[0];
      nprime1=a*sigma1;
      sigma2=norm*h2->GetBinContent(i)*lum_max/luminosity[1];
      nprime2=b*sigma2;
    }
    hnew->SetBinError(i,sqrt(nprime1+nprime2));
    hnew->SetBinContent(i, nprime1 + nprime2 );
  }

  /*  for(int i=hnew->GetNbinsX(); i>hnew->GetNbinsX()-8; i--) {
    hnew->SetBinContent(i,0);
    }*/
  
  return hnew;

}

float MCLum(int iprocess, int pol, int iquark) {

  TString filename = TString::Format("%spdg%i_%s_eL_pR_250GeV.root",folder.Data(),iquark,process[iprocess].Data());
  TFile *f = new TFile(filename);
  TH1F *hstats[2];
  hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");

  filename = TString::Format("%spdg%i_%s_eR_pL_250GeV.root",folder.Data(),iquark,process[iprocess].Data());
  TFile *f2 = new TFile(filename);
  hstats[1]=(TH1F*)f2->Get("h_Ntotal_nocuts");


  float luminosity[2];
  luminosity[0]=hstats[0]->GetEntries()/cross_section[0][iprocess];
  luminosity[1]=hstats[1]->GetEntries()/cross_section[1][iprocess];

  // cout<<luminosity[0]<<" "<<cross_section[0][iprocess]<<endl;
  return luminosity[pol];

}

TH1F* GetHisto(int iprocess, TString histo, int pol, int iquark, float lum, float norm=1) {

  TString filename = TString::Format("%spdg%i_%s_eL_pR_250GeV.root",folder.Data(),iquark,process[iprocess].Data());
  //  cout<<filename<<endl;
  TFile *f = new TFile(filename);
  TH1F *hstats[2];
  hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");
  TH1F *h[2];
  h[0]= (TH1F*)f->Get(histo);

  filename = TString::Format("%spdg%i_%s_eR_pL_250GeV.root",folder.Data(),iquark,process[iprocess].Data());
  TFile *f2 = new TFile(filename);
  hstats[1]=(TH1F*)f2->Get("h_Ntotal_nocuts");
  h[1]= (TH1F*)f2->Get(histo);

  float luminosity[2];
  luminosity[0]=hstats[0]->GetEntries()/cross_section[0][iprocess];
  luminosity[1]=hstats[1]->GetEntries()/cross_section[1][iprocess];

  
  if(pol==0 || pol==1) {
    //    cout<<"Scale pol:"<<pol<<endl;
    h[pol]=ScaleHisto(h[pol],luminosity[pol],lum,norm);
    //    h[pol]->Sumw2();
    return h[pol];
  }

  if(pol>1) {
    
    TH1F* hpol=PolHisto(h[0],h[1],pol,luminosity,lum,norm);
    //hpol->Sumw2();
    //hpol->Rebin(40);
    delete f;
    return hpol;
  }


  return NULL;

}




TH1F* MCuneff(int sample=0, int pol=0, int iquark=5, int iquark2=4, float lum=900){

  int ipdgquark=0;
  if(iquark2==5) ipdgquark=0;
  if(iquark2==4) ipdgquark=1;
  if(iquark2==3) ipdgquark=2;


  TH1F *htags=GetHisto(sample,TString::Format("h_N1_%i",ipdgquark),pol,iquark,lum,1);
  TH1F *hnjets=GetHisto(sample,TString::Format("h_N0_%i",ipdgquark),pol,iquark,lum,2);

  htags->Divide(hnjets);
  return htags;

}


TH1F* MCeff(int sample=0, int pol=0, int iquark=5, float lum=900){

  int ipdgquark=0;
  if(iquark==4) ipdgquark=1;

  TH1F *htags=GetHisto(sample,TString::Format("h_N1_%i",ipdgquark),pol,iquark,lum,1);
  TH1F *hnjets=GetHisto(sample,TString::Format("h_N0_%i",ipdgquark),pol,iquark,lum,2);

  htags->Divide(hnjets);
  return htags;

}

std::pair<TH1F*, TH1F* > DTeff_cheat(int sample=0, int pol=0, int iquark=5, float lum=900){

  int ipdgquark=0;
  if(iquark==4) ipdgquark=1;

  TH1F *h0_2=GetHisto(sample,TString::Format("h_N0_%i",ipdgquark),pol,iquark,lum,2);
  TH1F *h0=GetHisto(sample,TString::Format("h_N0_%i",ipdgquark),pol,iquark,lum,1);
  TH1F *h1=GetHisto(sample,TString::Format("h_N1_%i",ipdgquark),pol,iquark,lum,1);
  TH1F *h2=GetHisto(sample,TString::Format("h_N2_%i",ipdgquark),pol,iquark,lum,1);

  h1->Divide(h0_2);
  
  h2->Divide(h0);
  h2->Divide(h1);
  h2->Divide(h1);

  std::pair<TH1F*, TH1F* > result{h1,h2};
  return result;

}


