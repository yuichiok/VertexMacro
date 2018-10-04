

#include <unistd.h>
#include <iostream>
#define MAXV 8
void masses(string filename = "/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR.root")
{
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TFile * file = TFile::Open(filename.c_str(),"READ");
	int bin_e = 100;
	int max_e = 250;
	int min_e = 0;
	TH1F * topmass = new TH1F("topmass", "E(Ntracks)", bin_e,min_e,max_e);
	TH1F * top2mass = new TH1F("top2mass", "E(Ntracks)", bin_e,min_e,max_e);
	TH1F * wmass = new TH1F("wmass", ";m_{W|t} [GeV];Events / 2.5 GeV", bin_e,min_e,max_e);
	TH1F * w2mass = new TH1F("w2mass", ";m_{W|t} [GeV];Events / 2.5 GeV", bin_e,min_e,max_e);
	
	TTree * normaltree = Stats;
	topmass->SetLineWidth(3);
	wmass->SetLineWidth(3);
	wmass->SetLineColor(kGreen);
	wmass->SetFillColor(kGreen);
	wmass->SetFillStyle(3004);
	w2mass->SetLineWidth(3);
	w2mass->SetLineStyle(2);
	w2mass->SetLineColor(kGreen+1);
	w2mass->SetFillColor(kGreen+1);
	w2mass->SetFillStyle(3005);
	topmass->SetLineColor(kBlue+1);
	topmass->SetFillColor(kBlue+1);
	topmass->SetFillStyle(3004);
	top2mass->SetLineStyle(2);
	top2mass->SetLineWidth(3);
	top2mass->SetLineColor(kBlue);
	top2mass->SetFillColor(kBlue);
	top2mass->SetFillStyle(3005);
	wmass->SetStats(0);	
	int t = normaltree->Draw("Top1mass >> topmass","Top1mass > 0");
	int t2 = normaltree->Draw("Top2mass >> top2mass","Top1mass > 0");
	int w = normaltree->Draw("W1mass >> wmass","Top1mass > 0");
	int w2 = normaltree->Draw("W2mass >> w2mass","Top1mass > 0");
	wmass->Draw("");
	w2mass->Draw("same");
	topmass->Draw("same");
	top2mass->Draw("same");
	TLegend *legendMean2 = new TLegend(0.45,0.7,0.85,0.85,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(wmass,"W hadronic mass","f");
        legendMean2->AddEntry(w2mass,"W leptonic mass","f");
        legendMean2->AddEntry(topmass,"Top hadronic mass","f");
        legendMean2->AddEntry(top2mass,"Top leptonic mass","f");
	legendMean2->Draw();
	gPad->SetLeftMargin(0.14);
	//gPad->SetBottomMargin(0.14);
	wmass->GetYaxis()->SetTitleOffset(1.4);
}

