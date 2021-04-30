void KPimom1D()
{
	gStyle->SetOptStat(0);

	TFile* _file0 = TFile::Open("/home/ilc/yokugawa/macros/QQbar250/analysis/qqbar_2021/Hit/DQ_250GeV_test.root");

	TH1F* h_pfo_LeadKp_p;
	TH1F* h_pfo_LeadKm_p;
	TH1F* h_pfo_LeadPip_p;
	TH1F* h_pfo_LeadPim_p;

	_file0->GetObject("h_pfo_LeadKp_p",h_pfo_LeadKp_p);
	_file0->GetObject("h_pfo_LeadKm_p",h_pfo_LeadKm_p);
	_file0->GetObject("h_pfo_LeadPip_p",h_pfo_LeadPip_p);
	_file0->GetObject("h_pfo_LeadPim_p",h_pfo_LeadPim_p);
	
	TCanvas* c1	= new TCanvas("c1","canvas1",500,500);
	c1->SetLeftMargin(0.15);

	h_pfo_LeadKp_p->Scale(1/h_pfo_LeadKp_p->GetEntries());
	h_pfo_LeadKp_p->SetLineColor(kRed);

	h_pfo_LeadPip_p->Scale(1/h_pfo_LeadPip_p->GetEntries());
	h_pfo_LeadPip_p->SetLineColor(kBlue);

	h_pfo_LeadPip_p->Draw("h");
	h_pfo_LeadKp_p->Draw("hsame");

	TLegend* leg = new TLegend(0.65,0.85,0.9,0.65,"","brNDC");
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);
	leg->AddEntry(h_pfo_LeadKp_p,"K^{+}","l");
	leg->AddEntry(h_pfo_LeadPip_p,"#pi^{+}","l");
	leg->Draw();



	TCanvas* c2	= new TCanvas("c2","canvas2",500,500);
	c2->SetLeftMargin(0.15);

	h_pfo_LeadKm_p->Scale(1/h_pfo_LeadKm_p->GetEntries());
	h_pfo_LeadKm_p->SetLineColor(kRed);

	h_pfo_LeadPim_p->Scale(1/h_pfo_LeadPim_p->GetEntries());
	h_pfo_LeadPim_p->SetLineColor(kBlue);

	h_pfo_LeadPim_p->Draw("h");
	h_pfo_LeadKm_p->Draw("hsame");

	TLegend* leg2 = new TLegend(0.65,0.85,0.9,0.65,"","brNDC");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->SetTextSize(0.03);
	leg2->AddEntry(h_pfo_LeadKm_p,"K^{-}","l");
	leg2->AddEntry(h_pfo_LeadPim_p,"#pi^{-}","l");
	leg2->Draw();


}