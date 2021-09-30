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
const float momentum_min=0.95;
const TString particles[5] = {"kaon","proton","pion","electron","muon"};
const Color_t colors[5]    = {kRed,kGreen,kBlue,kBlack,kGray};


void eff_purity_dEdx() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);


  // TString filename0 = "../rootfiles/dEdx_out.root";
  TString filename0 = "../rootfiles/dEdx_test.root";
  TString filename1 = "plots/proj_dEdx.root";

  TFile *file0  = new TFile(filename0);
  TFile *file1  = new TFile(filename1);

  TH2F* dEdx_truths[NPAR];
  TGraphErrors* GEprojs[NPAR];

  for (int i = 0; i < NPAR; ++i)
  {
    dEdx_truths[i] = (TH2F*)file0->Get(particles[i]);
    GEprojs[i]     = (TGraphErrors*)file1->Get(TString::Format("GE_proj_%s",particles[i].Data()));
  }




//////////// dE/dx PID ////////////

  TF1 *f1= new TF1("f1","[0]+[1]*std::log(x)",3,100);
  f1->SetLineColor(2);
  GEprojs[0]->Fit(f1,"REM");


  double x[100], y[100];

  for(int ieff=0; ieff<11; ieff++) {
    float eff=0.45+0.05*ieff;
    
    double a=f1->GetParameter(0);
    double b=f1->GetParameter(1);
    
    double a_up=0;
    double a_down=0;
    float max_purity=0;
    float max_eff=0;
    
    for(int j=0; j<50; j++) {
      for(int k=0; k<50; k++) {

        double ea=(0.1+0.1*j)*f1->GetParError(0);
        double ea2=-(0.1+0.1*k)*f1->GetParError(0);

        double int_pion=0;
        double int_kaon=0;
        double int_proton=0;
        double int_kaon_total=0;

        for(int i=0; i<dEdx_truths[0]->GetNbinsX(); i++) {

          TH1D * proj_kaon =dEdx_truths[0]->ProjectionY("proj_kaon",i,i+1);
          int_kaon_total+=proj_kaon->GetEntries();
          
          if( dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1) > momentum_min ) {
          
            TH1D * proj_pion   = dEdx_truths[2]->ProjectionY("proj_pion",i,i+1);
            TH1D * proj_proton = dEdx_truths[1]->ProjectionY("proj_proton",i,i+1);

            for(int j1=0; j1<proj_pion->GetNbinsX(); j1++) {
          
              double yplus  = a+ea  + b* std::log(dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1));
              double yminus = a+ea2 + b* std::log(dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1));
              if(proj_pion->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_pion->GetXaxis()->GetBinCenter(j1)> yminus) int_pion+=proj_pion->GetBinContent(j1);
          
            }

            for(int j1=0; j1<proj_kaon->GetNbinsX(); j1++) {

              double yplus  = a+ea  + b* std::log(dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1));
              double yminus = a+ea2 + b* std::log(dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1));
              if(proj_kaon->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_kaon->GetXaxis()->GetBinCenter(j1)> yminus) int_kaon+=proj_kaon->GetBinContent(j1);
            
            }

            for(int j1=0; j1<proj_proton->GetNbinsX(); j1++) {
            
              double yplus  = a+ea  + b* std::log(dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1));
              double yminus = a+ea2 + b* std::log(dEdx_truths[0]->GetXaxis()->GetBinCenter(i+1));
              if(proj_proton->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_proton->GetXaxis()->GetBinCenter(j1)> yminus) int_proton+=proj_proton->GetBinContent(j1);
            
            } 
          }
        }

        if((int_proton+int_pion+int_kaon)/int_kaon_total>eff ) {
         
          // cout<<j<<" "<<k<< "  ->  eff: "<< int_kaon/int_kaon_total<<" purity: "<<1.-(int_proton+int_pion)/int_kaon<<" (pion:"<<1.-(int_pion)/int_kaon<<") (proton:"<<1.-(int_proton)/int_kaon<<")"<<endl;
         
          if( int_kaon/(int_proton+int_pion+int_kaon)  > max_purity) {
         
            max_purity = int_kaon/(int_proton+int_pion+int_kaon);
            max_eff= (int_proton+int_pion+int_kaon)/int_kaon_total;
            a_up=a+ea;
            a_down=a+ea2;
            // cout<<" purity="<<max_purity<<" eff="<<(int_proton+int_pion+int_kaon)/int_kaon_total<<";    slope="<<b<<" upper="<<a+ea<<" lower="<<a+ea2<<endl;
         
          }
        }
      }
    }
    cout<<"eff_input>"<<eff<<":\t purity="<<max_purity<<" eff="<<max_eff<<";\t slope="<<b<<" upper="<<a_up<<" lower="<<a_down<<endl;
    x[ieff]=eff;
    y[ieff]=max_purity;
    a_up=0;
    a_down=0;
    max_purity=0;
    max_eff= 0;
  }


  TCanvas *c1 = new TCanvas("c1","c1",500,500);
  TGraph *eff_purity = new TGraph(11,x,y);
  eff_purity->SetTitle(";Efficiency;Purity");
  eff_purity->SetMarkerColor(colors[0]);
  eff_purity->SetMarkerSize(1.0);
  eff_purity->Draw("APL");

  TFile *MyFile = new TFile("plots/eff_purity_dEdx.root","RECREATE");
  MyFile->cd();

  eff_purity->Write();


  std::cout << "DONE" << std::endl;
  
  
}
