#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <stdlib.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>

void Kstar0_fit(){

    gStyle->SetOptStat(0);

    TFile *f = TFile::Open("../rootfiles/double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_mass_correct.mergeFULL.root","READ");
    if (f == 0) {
        std::cout << "Error: File not found." << std::endl;
        return;
    }

    const int hsize = 11;
    TH1F * hs[hsize];
    int colors[hsize] = {1,633,810,418,434,601,617,907,804,800,875};

    hs[0] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass");
    hs[1] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat313");//
    hs[2] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheatMOD313");
    hs[3] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat315");//
    hs[4] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat323");
    hs[5] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat333");//
    hs[6] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat335");
    hs[7] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat113");
    hs[8] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat213");
    hs[9] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat92");
    hs[10] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat_other");


    TCanvas *c0 = new TCanvas("c0","c0",700,700);
    hs[1]->Rebin(4);
    hs[1]->Scale(1/hs[0]->GetEntries());

    float p0[3];
          p0[0] = hs[1]->GetMaximum();
          p0[1] = hs[1]->GetMean();
          p0[2] = hs[1]->GetRMS();

    TF1 *landau0 = new TF1("landau0","TMath::Landau(x,[0],[1],0)*[2]",0.7,2);
    landau0->SetLineColor(kGreen+2);
    landau0->SetParameters(p0[1],p0[2]/10.0,p0[0]);

    hs[1]->Fit(landau0,"SR");
    hs[1]->Draw("h");


    TCanvas *c1 = new TCanvas("c1","c1",700,700);
    hs[5]->Rebin(4);
    hs[5]->Scale(1/hs[0]->GetEntries());

    float p1[3];
          p1[0] = hs[5]->GetMaximum();
          p1[1] = hs[5]->GetMean();
          p1[2] = hs[5]->GetRMS();

    cout << p1[0] << "," << p1[1] << "," << p1[2] << endl;

    TF1 *gaus1 = new TF1("gaus1","[2]*TMath::Gaus(x,[0],[1])",0.7,2);
    gaus1->SetParameters(0.8,0.018,0.017);

    hs[5]->Fit(gaus1,"SR");
    hs[5]->Draw("hsame");

    TCanvas *c2 = new TCanvas("c2","c2",700,700);
    hs[3]->Rebin(4);
    hs[3]->Scale(1/hs[0]->GetEntries());

    float p2[3];
          p2[0] = hs[3]->GetMaximum();
          p2[1] = hs[3]->GetMean();
          p2[2] = hs[3]->GetRMS();
    
    TF1 *gaus2 = new TF1("gaus1","[2]*TMath::Gaus(x,[0],[1])",0.7,2);
    gaus2->SetLineColor(kBlue+1);
    gaus2->SetParameters(1.44,0.018,0.007);

    hs[3]->Fit(gaus2,"SR");
    hs[3]->Draw("hsame");

    TCanvas *c3 = new TCanvas("c3","c3",700,700);

    TH1F *h_bkg = (TH1F*) hs[2]->Clone();
    h_bkg->Add(hs[4]);
    for(int i=6;i<11;i++){
        h_bkg->Add(hs[i]);
    }
    h_bkg->Rebin(4);
    h_bkg->Scale(1/hs[0]->GetEntries());

    TF1 *landau1 = new TF1("landau1","TMath::Landau(x,[0],[1],0)*[2] + [5]*TMath::Landau(x,[3],[4])",0.7,2);
    landau1->SetLineColor(kGray+2);
    landau1->SetLineStyle(2);
    landau1->SetParameters(0.85,0.1,0.02,1.4,0.12,0.015);

    h_bkg->Fit(landau1,"SR");
    h_bkg->Draw("h");



    TCanvas *c4 = new TCanvas("c4","c4",700,700);
    hs[0]->Rebin(4);
    hs[0]->Scale(1/hs[0]->GetEntries());

    // TF1 *fsum = new TF1("fsum","[0]*TMath::Landau(x,[1],[2],0) + [3]*TMath::Landau(x,[4],[5],0) + [6]*TMath::Landau(x,[7],[8],0) + [9]*TMath::Landau(x,[10],[11],0)",0.7,2.0);
    TF1 *fsum = new TF1("fsum","[0]*TMath::Gaus(x,[1],[2]) + [3]*TMath::Landau(x,[4],[5],0) + [6]*TMath::Landau(x,[7],[8],0) + [9]*TMath::Gaus(x,[10],[11])",0.7,2.0);
    cout << "p0[1]=" << p0[1] << ", p0[2]=" << p0[2] << ", p1[1]=" << p1[1] << ", p1[2]=" << p1[2] << endl;
    fsum->SetLineColor(kBlack);
    fsum->SetParameters(0.035, p1[1]-0.1, p1[2]/10.0, 0.055, p0[1], p0[2]/10.0, 0.05, 1.19, 0.12);
    fsum->SetParameter(9,0.015);
    fsum->SetParameter(10,1.4);
    fsum->SetParameter(11,0.12);

    hs[0]->Fit(fsum,"SR");
    hs[0]->Draw("same");

    gaus1->Draw("same");
    gaus2->Draw("same");
    landau0->Draw("same");
    // landau1->Draw("same");

    TLegend *leg1 = new TLegend(0.65,0.85,0.9,0.65,"","brNDC");
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.025);
    leg1->AddEntry(hs[0],"All","le");
    leg1->AddEntry(gaus1,"#phi(1020)","l");
    leg1->AddEntry(landau0,"K*_{0}(892)^{0}","l");
    leg1->AddEntry(gaus2,"K*_{2}(1430)^{0}","l");
    // for (int ih = 0; ih < 10; ih++) leg1->AddEntry(hs[ih],labels[ih],"lf");
    leg1->Draw("same");


}