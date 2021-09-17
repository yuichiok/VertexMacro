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






void DTeffPlotPols(int sample=0, int iquark=5, float lum=-1) {


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  
  TH1F *eff[2];
  TH1F *rho[2];
  float MCluminosity[2];
  TGraphErrors * g_eff[2];
  TGraphErrors * g_rho[2];
  for(int i=0; i<2; i++) {
    eff[i]=DTeff_cheat(sample,i,iquark,lum).first;
    eff[i]->Scale(100.);
    rho[i]=DTeff_cheat(sample,i,iquark,lum).second;
    // rho[i]->Scale(100.);
    MCluminosity[i]=MCLum(sample,i,iquark);
    g_eff[i]= new TGraphErrors(eff[i]);
    g_rho[i]= new TGraphErrors(rho[i]);

  }

  
  
  TCanvas* c_eff_DT = new TCanvas("c_eff_DT","c_eff_DT",800,800);
  c_eff_DT->cd(1);
  c_eff_DT->SetGrid();
  g_eff[0]->GetXaxis()->SetTitle("cos #theta_{thrust}");
  g_eff[0]->GetYaxis()->SetTitle("Eff [%]");
  g_eff[0]->GetYaxis()->SetTitleOffset(1.25);
  g_eff[0]->GetXaxis()->SetTitleOffset(1.);
  g_eff[0]->GetYaxis()->SetRangeUser(0,100);
  g_eff[0]->GetXaxis()->SetRangeUser(0,1);
  g_eff[0]->SetLineColor(4);
  g_eff[0]->SetLineWidth(2);
  g_eff[0]->SetMarkerStyle(0);
  g_eff[0]->Draw("alp");

  g_eff[1]->SetLineColor(2);
  g_eff[1]->SetLineWidth(2);
  g_eff[1]->SetMarkerStyle(0);
  g_eff[1]->Draw("lp");

  Labels(4,iquark,3000);

  TLegend *leg = new TLegend(0.57,0.76,0.85,0.9);//(0.4,0.3,0.5,0.6);
  leg->SetTextSize(0.035);
  leg->AddEntry(g_eff[0],"eL_pR(100%)","l");
  leg->AddEntry(g_eff[1],"eR_pL(100%)","l");
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

  c_eff_DT->Print(TString::Format("summaryplots/EffDT_sample_%i_pdg_%i_twopols.eps",sample,iquark));
  c_eff_DT->Update();

  TCanvas* c_rho_DT = new TCanvas("c_rho_DT","c_rho_DT",800,800);
  c_rho_DT->cd(1);
  c_rho_DT->SetGrid();
  g_rho[0]->GetXaxis()->SetTitle("cos #theta_{thrust}");
  g_rho[0]->GetYaxis()->SetTitle("(1+#rho)");
  g_rho[0]->GetYaxis()->SetTitleOffset(1.25);
  g_rho[0]->GetXaxis()->SetTitleOffset(1.);
  g_rho[0]->GetYaxis()->SetRangeUser(0,1.5);
  g_rho[0]->GetXaxis()->SetRangeUser(9,1);
  g_rho[0]->SetLineColor(4);
  g_rho[0]->SetLineWidth(2);
  g_rho[0]->SetMarkerStyle(0);
  g_rho[0]->Draw("alp");

  g_rho[1]->SetLineColor(2);
  g_rho[1]->SetLineWidth(2);
  g_rho[1]->SetMarkerStyle(0);
  g_rho[1]->Draw("lp");

  Labels(4,iquark,3000);

  TLegend *leg2 = new TLegend(0.57,0.76,0.85,0.9);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(g_rho[0],"eL_pR(100%)","l");
  leg2->AddEntry(g_rho[1],"eR_pL(100%)","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  c_rho_DT->Print(TString::Format("summaryplots/RhoDT_sample_%i_pdg_%i_twopols.eps",sample,iquark));
  c_rho_DT->Update();

}


void MCeffPlotPols(int sample=0, int iquark=5, float lum=-1) {


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  
  TH1F *eff[2];
  float MCluminosity[2];
  TGraphErrors * g_eff[2];
  for(int i=0; i<2; i++) {
    eff[i]=MCeff(sample,i,iquark,lum);
    eff[i]->Scale(100.);
    MCluminosity[i]=MCLum(sample,i,iquark);
    g_eff[i]= new TGraphErrors(eff[i]);
  }

  


  TCanvas* c_eff_MC = new TCanvas("c_eff_MC","c_eff_MC",800,800);
  c_eff_MC->cd(1);
  c_eff_MC->SetGrid();
  g_eff[0]->GetXaxis()->SetTitle("cos #theta_{thrust}");
  g_eff[0]->GetYaxis()->SetTitle("Eff [%]");
  g_eff[0]->GetYaxis()->SetTitleOffset(1.25);
  g_eff[0]->GetXaxis()->SetTitleOffset(1.);
  g_eff[0]->GetYaxis()->SetRangeUser(0,100);
  g_eff[0]->GetXaxis()->SetRangeUser(0,1);
  g_eff[0]->SetLineColor(4);
  g_eff[0]->SetLineWidth(2);
  g_eff[0]->SetMarkerStyle(0);
  g_eff[0]->Draw("alp");

  g_eff[1]->SetLineColor(2);
  g_eff[1]->SetLineWidth(2);
  g_eff[1]->SetMarkerStyle(0);
  g_eff[1]->Draw("lp");

  Labels(0,iquark,3000);

  TLegend *leg2 = new TLegend(0.57,0.76,0.85,0.9);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(g_eff[0],"eL_pR(100%)","l");
  leg2->AddEntry(g_eff[1],"eR_pL(100%)","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  c_eff_MC->Print(TString::Format("summaryplots/Eff_sample_%i_pdg_%i_twopols.eps",sample,iquark));
  c_eff_MC->Update();

}

void MCuneffPlotPols(int sample=0, int iquark=5, float lum=-1) {


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  
  TH1F *eff[2];
  TH1F *eff2[2];
  TGraphErrors * g_eff[2];
  TGraphErrors * g_eff2[2];
  for(int i=0; i<2; i++) {
    eff[i]=MCuneff(sample,i,iquark,3,lum);
    eff[i]->Scale(100.);
    g_eff[i]= new TGraphErrors(eff[i]);

    int quark2=4;
    if(iquark==4) quark2=5;
    eff2[i]=MCuneff(sample,i,iquark,quark2,lum);
    eff2[i]->Scale(100.);
    g_eff2[i]= new TGraphErrors(eff2[i]);
  }

  


  TCanvas* c_eff_MC = new TCanvas("c_eff_MC","c_eff_MC",800,800);
  c_eff_MC->cd(1);
  c_eff_MC->SetGrid();
  g_eff[0]->GetXaxis()->SetTitle("cos #theta_{thrust}");
  g_eff[0]->GetYaxis()->SetTitle("Mis-ID [%]");
  g_eff[0]->GetYaxis()->SetTitleOffset(1.25);
  g_eff[0]->GetXaxis()->SetTitleOffset(1.);
  g_eff[0]->GetYaxis()->SetRangeUser(0,2);
  g_eff[0]->GetXaxis()->SetRangeUser(0,1);
  g_eff[0]->SetLineColor(4);
  g_eff[0]->SetLineWidth(1);
  g_eff[0]->SetMarkerStyle(0);
  g_eff[0]->Draw("alp");

  g_eff[1]->SetLineColor(4);
  g_eff[1]->SetLineWidth(2);
  g_eff[1]->SetLineStyle(2);
  g_eff[1]->SetMarkerStyle(0);
  g_eff[1]->Draw("lp");

  g_eff2[0]->SetLineColor(2);
  g_eff2[0]->SetLineWidth(1);
  g_eff2[0]->SetMarkerStyle(0);
  g_eff2[0]->Draw("lp");

  g_eff2[1]->SetLineColor(2);
  g_eff2[1]->SetLineWidth(2);
  g_eff2[1]->SetLineStyle(2);
  g_eff2[1]->SetMarkerStyle(0);
  g_eff2[1]->Draw("lp");

  Labels(4,iquark,3000);

  TLegend *leg2 = new TLegend(0.57,0.76,0.85,0.9);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(g_eff[0],"uds-eL_pR(100%)","l");
  leg2->AddEntry(g_eff[1],"uds-eR_pL(100%)","l");
  if(iquark==5) {
    leg2->AddEntry(g_eff2[0],"c-eL_pR(100%)","l");
    leg2->AddEntry(g_eff2[1],"c-eR_pL(100%)","l");
  } else {
    leg2->AddEntry(g_eff2[0],"b-eL_pR(100%)","l");
    leg2->AddEntry(g_eff2[1],"b-eR_pL(100%)","l");
  }
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();


  c_eff_MC->Print(TString::Format("summaryplots/UnEff_sample_%i_pdg_%i_twopols.eps",sample,iquark));
  c_eff_MC->Update();
}



void JetTag() {

  int sample=4; //3= signal, no cuts in rad return; 4= signa+radreturncut, 0=zz, 1=hz, 2=ww

  DTeffPlotPols(sample,4,900);
  MCeffPlotPols(sample,4,900);
  MCuneffPlotPols(sample,4,900);

}
