#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <stdlib.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>

// see math/mathcore/src/PdfFuncMathCore.cxx in ROOT 6.x
double crystalball_function(double x, double alpha, double n, double sigma, double mean)
{
	// evaluate the crystal ball function
	if (sigma < 0.)
		return 0.;
	double z = (x - mean) / sigma;
	if (alpha < 0)
		z = -z;
	double abs_alpha = std::abs(alpha);
	// double C = n/abs_alpha * 1./(n-1.) * std::exp(-alpha*alpha/2.);
	// double D = std::sqrt(M_PI/2.)*(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
	// double N = 1./(sigma*(C+D));
	if (z > -abs_alpha)
		return std::exp(-0.5 * z * z);
	else
	{
		// double A = std::pow(n/abs_alpha,n) * std::exp(-0.5*abs_alpha*abs_alpha);
		double nDivAlpha = n / abs_alpha;
		double AA = std::exp(-0.5 * abs_alpha * abs_alpha);
		double B = nDivAlpha - abs_alpha;
		double arg = nDivAlpha / (B - z);
		return AA * std::pow(arg, n);
	}
}

double crystalball_function(const double *x, const double *p)
{
	// if ((!x) || (!p)) return 0.; // just a precaution
	// [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
	return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}

double f_mult(const double *x, const double *p)
{
	return (p[0]*TMath::Landau(x[0],p[1],p[2],0) + p[3]*TMath::Landau(x[0],p[4],p[5],0) + p[6]*TMath::Landau(x[0],p[7],p[8],0) + p[9]*TMath::Landau(x[0],p[10],p[11],0));
}

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

    Double_t par_Ks[12];
    fsum->GetParameters(&par_Ks[0]);

    TF1 *bk = new TF1("bk","TMath::Landau(x,[0],[1],0)*[2]",0.7,2);
    bk->SetParameters(par_Ks[7],par_Ks[8],par_Ks[6]);
    bk->SetLineColor(kGray+2);
    bk->SetLineStyle(2);
    // bk->Draw("same");

}