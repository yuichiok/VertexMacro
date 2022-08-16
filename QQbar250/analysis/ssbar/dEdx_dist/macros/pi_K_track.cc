#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <stdlib.h>

void pi_K_track(){

    gStyle->SetOptStat(0);

    TFile *f = TFile::Open("../rootfiles/double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_cos.mergeFULL.root","READ");
    if (f == 0) {
        std::cout << "Error: File not found." << std::endl;
        return;
    }

    const int hsize = 2;
    // TH1F * hs[hsize];
    struct Hists {
        TH1F * hist;
        int color;
        TString label;
    };

    Hists hs[hsize] = {
        {(TH1F*)f->Get("h_pfo_LeadPi_trk_length"), kBlue+1, "Lead #pi"},
        {(TH1F*)f->Get("h_pfo_SPFOK_trk_length"), kRed+1, "SPFO K"},
    };

    Hists hs_diff[hsize] = {
        {(TH1F*)f->Get("h_pfo_LeadPi_SPFOK_trk_diff"), kBlack, "Track Length Difference"},
        {(TH1F*)f->Get("h_pfo_LeadPi333_SPFOK_trk_diff"), kRed+1, "From #phi"},
    };

    TCanvas *c0 = new TCanvas("c0","c0",700,700);
    for (int ih = 0; ih < hsize; ih++)
    {
        hs[ih].hist->SetLineColor(hs[ih].color);
        hs[ih].hist->SetLineWidth(3);
        hs[ih].hist->Scale(1/hs[ih].hist->GetEntries());
        hs[ih].hist->Rebin(4);
        // hs[ih].hist->GetYaxis()->SetRangeUser(0,0.3);
        hs[ih].hist->Draw("hsame");
    }
    
    TLegend *leg0 = new TLegend(0.65,0.85,0.9,0.5,"","brNDC");
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.03);
    for (int ih = 0; ih < hsize; ih++) leg0->AddEntry(hs[ih].hist,hs[ih].label,"lf");
    leg0->Draw("same");


    TCanvas *c1 = new TCanvas("c1","c1",700,700);

    for (int ih = 0; ih < hsize; ih++)
    {
        hs_diff[ih].hist->SetLineColor(hs[ih].color);
        hs_diff[ih].hist->SetLineWidth(3);
        hs_diff[ih].hist->Scale(1/hs[ih].hist->GetEntries());
        hs_diff[ih].hist->Rebin(4);
        hs_diff[ih].hist->GetYaxis()->SetRangeUser(0,0.05);
        hs_diff[ih].hist->Draw("hsame");
    }

    TLegend *leg1 = new TLegend(0.65,0.85,0.9,0.5,"","brNDC");
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.03);
    for (int ih = 0; ih < hsize; ih++) leg1->AddEntry(hs_diff[ih].hist,hs_diff[ih].label,"lf");
    leg1->Draw("same");

}