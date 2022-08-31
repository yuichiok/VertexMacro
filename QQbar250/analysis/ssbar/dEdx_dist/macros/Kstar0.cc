#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <stdlib.h>

void Kstar0(){

    gStyle->SetOptStat(0);

    TFile *f = TFile::Open("../rootfiles/double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_cos.AllEvents.root","READ");
    if (f == 0) {
        std::cout << "Error: File not found." << std::endl;
        return;
    }

    const int hsize = 11;
    TH1F * hs[hsize];
    int colors[hsize] = {1,633,810,418,434,601,617,907,804,800,875};

    hs[0] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass");
    hs[1] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat313");
    hs[2] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheatMOD313");
    hs[3] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat315");
    hs[4] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat323");
    hs[5] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat333");
    hs[6] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat335");
    hs[7] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat113");
    hs[8] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat213");
    hs[9] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat92");
    hs[10] = (TH1F*)f->Get("h_pfo_LeadPi_K_mass_cheat_other");

    
    TLegend *leg0 = new TLegend(0.65,0.85,0.9,0.5,"","brNDC");
    TString labels[hsize] = {"All","K*_{0}(892)^{0}","K*(other)^{0}","K*_{2}(1430)^{0}","K*(892)^{#pm}","#phi(1020)","f'_{2}(1525)","#rho(770)^{0}","#rho(770)^{#pm}","MC hadron","others"};
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.025);
    for (int ih = 0; ih < hsize; ih++) leg0->AddEntry(hs[ih],labels[ih],"lf");

    TLegend *leg1 = new TLegend(0.65,0.85,0.9,0.5,"","brNDC");
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.025);
    for (int ih = 0; ih < 10; ih++) leg1->AddEntry(hs[ih],labels[ih],"lf");


    TCanvas *c0 = new TCanvas("c0","c0",700,700);
    THStack *h_KstarStack  = new THStack("h_KstarStack","h_KstarStack");
    hs[0]->SetLineWidth(3);
    for (int ih = 0; ih < hsize; ih++)
    {
        hs[ih]->SetLineColor(colors[ih]);
        hs[ih]->SetFillColor(colors[ih]);
        hs[ih]->SetFillStyle(3004);
        hs[ih]->Rebin(4);
        hs[ih]->GetXaxis()->SetRangeUser(0.7,2);
        if(0<ih && ih<10) h_KstarStack->Add(hs[ih]);
    }
    hs[0]->Draw("h");
    h_KstarStack->Draw("nostack same");
    hs[10]->Draw("hsame");
    leg0->Draw("same");


    TCanvas *c1 = new TCanvas("c1","c1",700,700);
    hs[0]->Draw("h");
    h_KstarStack->Draw("same");
    leg1->Draw("same");

}