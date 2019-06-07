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

#include "../style/Style.C"
#include "../style/Labels.C"

std::vector<float> CalculateP(int n_accepted,  int n_rejected)
{

  float pvaluemax=0;
  float pvaluemin=1;

  for(int j1=-1;j1<2; j1++) {
    for(int j2=-1;j2<2; j2++) {

        float accepted_total=0;
        float rejected_total=0;
	rejected_total += n_rejected+float(j1)*sqrt(float(n_rejected));
	accepted_total += n_accepted+float(j2)*sqrt(float(n_accepted));
	
        float a=1;
        float b=-1;
        float c= rejected_total/ (2* (accepted_total+rejected_total));
        float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
        float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
        if(p>0.99) p=0;
        if(p2>0.99) p2=0;
        if(p<0) p=0;
        if(p2<0) p2=0;
        if(p >0 || p2>0 ) p=max(p,p2);
        if(p<pvaluemin && p>0 && p<1) pvaluemin=p;
        if(p>pvaluemax && p>0 && p<1) pvaluemax=p;
	//cout<<j1<<" "<<j2<<" "<<" "<<p<<" "<<pvaluemin<<" "<<pvaluemax<<endl;  

    }
  }

  float pmean  = (pvaluemax+pvaluemin)/2.;
  float perror = (pvaluemax-pvaluemin)/2.;
  std::vector<float> resultaverage;
  resultaverage.push_back(pmean);
  resultaverage.push_back(perror);
  return resultaverage;

}

void purity_ttbar() {

	TString largeModel="/hsm/ilc/users/yokugawa/preset_N_run/l5/electron_muon/QQbarProcessor_out/IsoLepTagged.eL.pR_electron_muon_QQbar2.root";
	TString smallModel="/hsm/ilc/users/yokugawa/preset_N_run/s5/electron_muon/QQbarProcessor_out/IsoLepTagged.eL.pR_electron_muon_QQbar2.root";

	// set plot style
	SetQQbarStyle();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

  TCut cut_0="methodUsed>-1";
  
  double n_l5_accepted[10];  for(int i=0; i<8; i++) n_l5_accepted[i] = 0;
  double n_l5_rejected[10];  for(int i=0; i<8; i++) n_l5_rejected[i] = 0;

  TH1F *l5_accepted = new TH1F("l5_accepted","l5_accepted",8,0,8);
  TH1F *l5_rejected = new TH1F("l5_rejected","l5_rejected",8,0,8);
  TH1F *l5_ratio = new TH1F("l5_ratio","l5_ratio",8,0,8);
  TH1F *l5_purity = new TH1F("l5_purity","l5_purity",8,0,8);

    
  double n_s5_accepted[10];  for(int i=0; i<8; i++) n_s5_accepted[i] = 0;
  double n_s5_rejected[10];  for(int i=0; i<8; i++) n_s5_rejected[i] = 0;

  TH1F *s5_accepted = new TH1F("s5_accepted","s5_accepted",8,0,8);
  TH1F *s5_rejected = new TH1F("s5_rejected","s5_rejected",8,0,8);
  TH1F *s5_ratio = new TH1F("s5_ratio","s5_ratio",8,0,8);
  TH1F *s5_purity = new TH1F("s5_purity","s5_purity",8,0,8);

  // --------------------------------------------
  //   large model
  TFile *f_l5 = new TFile( largeModel );
  TTree *Stats_l5 = (TTree*)f_l5->Get("Stats");

  TH1F *h_l5_accepted = new TH1F("h_l5_accepted","h_l5_accepted",12,0,12);
  Stats_l5->Draw("methodTaken>>h_l5_accepted",cut_0);

  TH1F *h_l5_rejected = new TH1F("h_l5_rejected","h_l5_rejected",12,0,12);
  Stats_l5->Draw("methodSameCharge>>h_l5_rejected",cut_0);

  for(int i=0; i<8; i++) {
    n_l5_accepted[i]=h_l5_accepted->GetBinContent(i+1);
    n_l5_rejected[i]=h_l5_rejected->GetBinContent(i+1);

    // cout <<n_l5_accepted[i] << "  " << n_l5_rejected[i] <<"  " <<n_l5_accepted[i]/( n_l5_accepted[i]+ n_l5_rejected[i])<< endl;
    l5_accepted->SetBinContent(i+1,n_l5_accepted[i]);
    l5_rejected->SetBinContent(i+1,n_l5_rejected[i]);
    if(n_l5_accepted[i]+n_l5_rejected[i]>0) {
      l5_ratio->SetBinContent(i+1,n_l5_accepted[i]/(n_l5_accepted[i]+n_l5_rejected[i]));
      double error = pow(sqrt(n_l5_accepted[i])/(n_l5_accepted[i]+n_l5_rejected[i]),2);// + pow(0.5*n_l5_accepted[i]*sqrt(n_l5_accepted[i]+n_l5_rejected[i])/pow(n_l5_accepted[i]+n_l5_rejected[i],2),2);
      error=sqrt(error);
      l5_ratio->SetBinError(i+1,error);

      std::vector<float> purity_temp = CalculateP(n_l5_accepted[i],  n_l5_rejected[i]);
      l5_purity->SetBinContent(i+1,purity_temp[0]);
      l5_purity->SetBinError(i+1,purity_temp[1]);
    }
  }


  
  // --------------------------------------------
  //   small model
  TFile *f_s5 = new TFile( smallModel );
  TTree *Stats_s5 = (TTree*)f_s5->Get("Stats");

  TH1F *h_s5_accepted = new TH1F("h_s5_accepted","h_s5_accepted",12,0,12);
  Stats_s5->Draw("methodTaken>>h_s5_accepted",cut_0);

  TH1F *h_s5_rejected = new TH1F("h_s5_rejected","h_s5_rejected",12,0,12);
  Stats_s5->Draw("methodSameCharge>>h_s5_rejected",cut_0);

  for(int i=0; i<8; i++) {
    n_s5_accepted[i]=h_s5_accepted->GetBinContent(i+1);
    n_s5_rejected[i]=h_s5_rejected->GetBinContent(i+1);

    s5_accepted->SetBinContent(i+1,n_s5_accepted[i]);
    s5_rejected->SetBinContent(i+1,n_s5_rejected[i]);
    if(n_s5_accepted[i]+n_s5_rejected[i]>0) {
      s5_ratio->SetBinContent(i+1,n_s5_accepted[i]/(n_s5_accepted[i]+n_s5_rejected[i]));
      double error = pow(sqrt(n_s5_accepted[i])/(n_s5_accepted[i]+n_s5_rejected[i]),2);// + pow(0.5*n_s5_accepted[i]*sqrt(n_s5_accepted[i]+n_s5_rejected[i])/pow(n_s5_accepted[i]+n_s5_rejected[i],2),2);
      error=sqrt(error);
      s5_ratio->SetBinError(i+1,error);
      
      std::vector<float> purity_temp = CalculateP(n_s5_accepted[i],  n_s5_rejected[i]);
      s5_purity->SetBinContent(i+1,purity_temp[0]);
      s5_purity->SetBinError(i+1,purity_temp[1]);
    }

  }
 
  TCanvas * canvas = new TCanvas("canvas","canvas",1500,400);
  canvas->Divide(3,1);
  
  canvas->cd(1);
  gPad->SetGridy();
  gPad->SetGridx();
  l5_accepted->SetTitle("compatible charge events");
  l5_accepted->GetXaxis()->SetTitle("method");
  l5_accepted->SetLineColor(4);
  l5_accepted->SetLineStyle(1);
  l5_accepted->SetLineWidth(2);
  l5_accepted->Draw("histoe");

  s5_accepted->SetLineColor(2);
  s5_accepted->SetLineStyle(2);
  s5_accepted->SetLineWidth(2);
  s5_accepted->Draw("histoesame");
  
  TLegend *leg = new TLegend(0.2,0.75,0.4,0.85);
  leg->AddEntry(l5_accepted,"IDR-L","l");
  leg->AddEntry(s5_accepted,"IDR-S","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

  canvas->cd(2);
  gPad->SetGridy();
  gPad->SetGridx();
  l5_rejected->SetTitle("uncompatible charge events");
  l5_rejected->GetXaxis()->SetTitle("method");
  l5_rejected->SetLineColor(4);
  l5_rejected->SetLineStyle(1);
  l5_rejected->SetLineWidth(2);
  l5_rejected->Draw("histo");

  s5_rejected->SetLineColor(2);
  s5_rejected->SetLineStyle(2);
  s5_rejected->SetLineWidth(2);
  s5_rejected->Draw("histosame");

	QQBARLabel(0.8,0.2,"",1);
  leg->Draw();

  canvas->cd(3);
  gPad->SetGridy();
  gPad->SetGridx();
  l5_ratio->SetTitle("comp/ (comp+uncomp) charges");
  l5_ratio->GetXaxis()->SetTitle("method");
  l5_ratio->GetYaxis()->SetRangeUser(0.4,0.9);
  l5_ratio->SetLineColor(4);
  l5_ratio->SetLineStyle(1);
  l5_ratio->SetLineWidth(2);
  l5_ratio->Draw("histo");

  s5_ratio->SetLineColor(2);
  s5_ratio->SetLineStyle(2);
  s5_ratio->SetLineWidth(2);
  s5_ratio->Draw("histosame");

	QQBARLabel(0.8,0.2,"",1);
  leg->Draw();


  // p value plots
	
  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",500,500);
  //canvas2->Divide(2,1);

  //canvas2->cd(1);

  gPad->SetGridy();
  gPad->SetGridx();

  l5_ratio->GetXaxis()->SetBinLabel(2, "Vtx+Vtx");
  l5_ratio->GetXaxis()->SetBinLabel(3, "K+K");
  l5_ratio->GetXaxis()->SetBinLabel(4, "Vtx+K");
  l5_ratio->GetXaxis()->SetBinLabel(5, "Vtx+K'");
  l5_ratio->GetXaxis()->SetBinLabel(6, "Vtx+L_{cut}");
  l5_ratio->GetXaxis()->SetBinLabel(7, "K+L_{cut}");
  l5_ratio->GetXaxis()->SetBinLabel(8, "L_{cut}");
  
  l5_ratio->GetYaxis()->SetTitle("N_{acc.} / (N_{acc.}+N_{rej.})");
  l5_ratio->SetTitle("");
  l5_ratio->GetXaxis()->SetTitle("");
  l5_ratio->GetYaxis()->SetRangeUser(0.505,1.05);
  l5_ratio->SetLineColor(4);
  l5_ratio->SetLineStyle(1);
  l5_ratio->SetLineWidth(2);
  l5_ratio->Draw("histoe");

  s5_ratio->SetLineColor(2);
  s5_ratio->SetLineStyle(2);
  s5_ratio->SetLineWidth(2);
  s5_ratio->Draw("histoesame");

	QQBARLabel(0.8,0.2,"",1);
  leg->Draw();
  
  TCanvas * canvas3 = new TCanvas("canvas3","canvas3",500,500);

  //canvas2->cd(2);
  gPad->SetGridy();
  gPad->SetGridx();

  l5_purity->GetXaxis()->SetBinLabel(2, "Vtx+Vtx");
  l5_purity->GetXaxis()->SetBinLabel(3, "K+K");
  l5_purity->GetXaxis()->SetBinLabel(4, "Vtx+K");
  l5_purity->GetXaxis()->SetBinLabel(5, "Vtx+K'");
  l5_purity->GetXaxis()->SetBinLabel(6, "Vtx+L_{cut}");
  l5_purity->GetXaxis()->SetBinLabel(7, "K+L_{cut}");
  l5_purity->GetXaxis()->SetBinLabel(8, "L_{cut}");

  l5_purity->SetTitle("");
  l5_purity->GetXaxis()->SetTitle("");
  l5_purity->GetYaxis()->SetTitle("p");
  l5_purity->GetYaxis()->SetRangeUser(0.6,0.9);
  l5_purity->GetYaxis()->SetTitleOffset(1.5);
  l5_purity->SetLineColor(4);
  l5_purity->SetLineStyle(1);
  l5_purity->SetLineWidth(2);
  l5_purity->Draw("histoe");

  s5_purity->SetLineColor(2);
  s5_purity->SetLineStyle(2);
  s5_purity->SetLineWidth(2);
  s5_purity->Draw("histoesame");
  
	QQBARLabel(0.8,0.2,"",1);
  leg->Draw();

  
}

