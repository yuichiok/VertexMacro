#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <stdlib.h>

void Kstar0(){

    TFile *f = TFile::Open("../downloads/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_mass_correct.mergeFULL.root","UPDATE");
    if (f == 0) {
        std::cout << "Error: File not found." << std::endl;
        return;
    }

    TH1F * hs[11];

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

    hs[0]->SetLineColor(kBlack);
    hs

    THStack *h_KstarStack  = new THStack("h_KstarStack","h_KstarStack");

    TCanvas *c = new TCanvas("c","c",700,700);




}