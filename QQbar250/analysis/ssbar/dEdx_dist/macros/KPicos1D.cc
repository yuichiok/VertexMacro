#include <vector>

void DrawCosHist(TCanvas* c=0, int i = 0, TH1F* h_k = 0, TH1F* h_lk = 0){

	h_k->Scale(1/h_k->GetEntries());
	h_k->SetLineColor(kBlue);

	h_lk->Scale(1/h_lk->GetEntries());
	h_lk->SetLineColor(kRed);

	TString mom_case = "";

	switch(i){

		case 0:
			mom_case = "cos#theta for all momenta";
			break;
		case 1:
			mom_case = "cos#theta for 2 < p_{K} < 10 GeV";
			break;
		case 2:
			mom_case = "cos#theta for 10 < p_{K} < 30 GeV";
			break;
		case 3:
			mom_case = "cos#theta for p_{K} > 30 GeV";
			break;

		default:
			break;

	}


	h_lk->SetTitle(mom_case);
	h_lk->GetYaxis()->SetTitle("Entries/bin");

	h_lk->Draw("h");
	h_k->Draw("hsame");

	TLegend* leg = new TLegend(0.2,0.85,0.4,0.75,"","brNDC");
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);
	leg->AddEntry(h_k,"All Kaons","l");
	leg->AddEntry(h_lk,"Leading Kaon","l");
	leg->Draw();

	stringstream fname;
	fname << "$HOME/macros/QQbar250/analysis/qqbar_2021/Hit/plot/k_mom_" << i << ".pdf" << ends;
	c->Print(fname.str().data());

}

void KPicos1D()
{
	gStyle->SetOptStat(0);

	TFile* _file0 = TFile::Open("/home/ilc/yokugawa/macros/QQbar250/analysis/qqbar_2021/Hit/DQ_250GeV_test.root");

	TH1F *h_kaon[4];
	TH1F *h_leadK[4];

	_file0->GetObject("h_pfo_Kaon_cos",h_kaon[0]);
	_file0->GetObject("h_pfo_LeadKaons_cos",h_leadK[0]);
	
	_file0->GetObject("h_pfo_k_2_10_cos",h_kaon[1]);
	_file0->GetObject("h_pfo_k_10_30_cos",h_kaon[2]);
	_file0->GetObject("h_pfo_k_30_cos",h_kaon[3]);

	_file0->GetObject("h_pfo_LeadK_2_10_cos",h_leadK[1]);
	_file0->GetObject("h_pfo_LeadK_10_30_cos",h_leadK[2]);
	_file0->GetObject("h_pfo_LeadK_30_cos",h_leadK[3]);

	TCanvas* c1	= new TCanvas("c1","canvas1",500,500);
	c1->SetLeftMargin(0.15);

	for (int i = 0; i < 4; ++i)
	{
		DrawCosHist(c1, i, h_kaon[i],h_leadK[i]);
	}

	

	// h_pfo_Kaon_cos->Scale(1/h_pfo_LeadKp_p->GetEntries());
	// h_pfo_LeadKp_p->SetLineColor(kRed);

	// h_pfo_LeadPip_p->Scale(1/h_pfo_LeadPip_p->GetEntries());
	// h_pfo_LeadPip_p->SetLineColor(kBlue);

	// h_pfo_LeadPip_p->Draw("h");
	// h_pfo_LeadKp_p->Draw("hsame");




}