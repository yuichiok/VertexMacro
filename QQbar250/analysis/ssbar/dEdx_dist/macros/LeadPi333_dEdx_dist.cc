#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <stdlib.h>

void LeadPi333_dEdx_dist(){

    gStyle->SetOptStat(0);

    TFile *f = TFile::Open("../rootfiles/double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_cos.AllEvents.root","READ");
    if (f == 0) {
        std::cout << "Error: File not found." << std::endl;
        return;
    }

    const int hsize = 3;
    // TH1F * hs[hsize];
    struct Hists {
        TH1F * hist;
        int color;
        TString label;
    };

    Hists hs[hsize] = {
        {(TH1F*)f->Get("h_pfo_LeadPi333_kdEdx_dist"), kRed, "K^{#pm}"},
        {(TH1F*)f->Get("h_pfo_LeadPi333_pdEdx_dist"), kBlack, "p"},
        {(TH1F*)f->Get("h_pfo_LeadPi333_pidEdx_dist"), kBlue, "#pi^{#pm}"}
    };


    TCanvas *c0 = new TCanvas("c0","c0",700,700);
    for (int ih = 0; ih < hsize; ih++)
    {
        hs[ih].hist->SetLineColor(hs[ih].color);
        hs[ih].hist->SetLineWidth(3);
        hs[ih].hist->Scale(1/hs[ih].hist->GetEntries());
        hs[ih].hist->GetYaxis()->SetRangeUser(0,0.3);
        hs[ih].hist->Draw("hsame");
    }
    
    TLegend *leg0 = new TLegend(0.65,0.85,0.9,0.5,"","brNDC");
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.03);
    for (int ih = 0; ih < hsize; ih++) leg0->AddEntry(hs[ih].hist,hs[ih].label,"lf");
    leg0->Draw("same");


/*

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
*/

}