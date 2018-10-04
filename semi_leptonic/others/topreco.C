void topreco(string filename = "/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR.root")
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1200,400);
	TFile *_file0 = TFile::Open(filename.c_str());
	int bin_e = 50;
	int minn = 1;
	int maxn = 8;
	TH1F * gammaTotal = new TH1F("gammaTotal", "E(Ntracks)", bin_e,1, 1.7);
	TH1F * gammaWrong = new TH1F("gammaWrong", "E(Ntracks)", bin_e,1, 1.7);
	TH1F * cosTotal = new TH1F("cosTotal", "E(Ntracks)", bin_e,-1, 1);
	TH1F * cosWrong = new TH1F("cosWrong", "E(Ntracks)", bin_e,-1, 1);
	TH1F * pTotal = new TH1F("pTotal", "E(Ntracks)", bin_e,30, 100);
	TH1F * pWrong = new TH1F("pWrong", "E(Ntracks)", bin_e,30, 100);
	
	// **** Base cut ****
	string cuts = " hadMass > 180 && hadMass < 420 && Top1mass < 200 && W1mass < 110 && Top1mass > 150 && W1mass > 50 &&";
	
	// **** Full cut ****
	//string cuts = "hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ((methodTaken == 1 && Top1btag > 0.8 && Top2btag > 0.8 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 2 ) && ";
	
	c1->Divide(3,1);
	c1->cd(1);
	Stats->Draw("Top1gamma >> gammaTotal",(cuts+"MCBWcorrect == 1").c_str());
	Stats->Draw("Top1gamma >> gammaWrong",(cuts+"MCBWcorrect == 0").c_str());
	makePretty(gammaTotal, kGreen);
	makePretty(gammaWrong, kRed);
	THStack * stack1 = new THStack("stack1",";#gamma_{t};Entries");
	stack1->Add(gammaWrong);
	stack1->Add(gammaTotal);
	stack1->Draw();
	gPad->SetLeftMargin(0.14);
	stack1->GetYaxis()->SetTitleOffset(1.5);
	gPad->SetBottomMargin(0.14);
	gPad->SetTopMargin(0.04);
	gPad->SetRightMargin(0.04);
	stack1->GetXaxis()->SetTitleOffset(0.85);
	stack1->GetXaxis()->SetTitleSize(.07);
	//gPad->SetBottomMargin(0.14);
	drawLegend();
	c1->cd(2);
	Stats->Draw("Top1pstarb >> pTotal",(cuts+"MCBWcorrect == 1").c_str());
	Stats->Draw("Top1pstarb >> pWrong",(cuts+"MCBWcorrect == 0").c_str());
	makePretty(pTotal, kGreen);
	makePretty(pWrong, kRed);
	THStack * stack2 = new THStack("stack2",";p^{*}_{b} [GeV];Entries");
	stack2->Add(pWrong);
	stack2->Add(pTotal);
	stack2->SetMaximum(stack2->GetMaximum()*1.1);
	stack2->Draw();
	gPad->SetLeftMargin(0.14);
	stack2->GetYaxis()->SetTitleOffset(1.5);
	gPad->SetBottomMargin(0.14);
	gPad->SetTopMargin(0.04);
	gPad->SetRightMargin(0.04);
	stack2->GetXaxis()->SetTitleOffset(0.75);
	stack2->GetXaxis()->SetTitleSize(.07);
	drawLegend();
	c1->cd(3);
	Stats->Draw("Top1cosWb >> cosTotal",(cuts+"MCBWcorrect == 1").c_str());
	Stats->Draw("Top1cosWb >> cosWrong",(cuts+"MCBWcorrect == 0").c_str());
	makePretty(cosTotal, kGreen);
	makePretty(cosWrong, kRed);
	THStack * stack3 = new THStack("stack3",";cos#theta_{bW};Entries");
	stack3->Add(cosWrong);
	stack3->Add(cosTotal);
	stack3->Draw();
	gPad->SetLeftMargin(0.14);
	stack3->GetYaxis()->SetTitleOffset(1.5);
	gPad->SetBottomMargin(0.14);
	gPad->SetTopMargin(0.04);
	gPad->SetRightMargin(0.04);
	stack3->GetXaxis()->SetTitleOffset(0.85);
	stack3->GetXaxis()->SetTitleSize(.07);
	drawLegend();
	//gammaTotal->Draw();
	//gammaWrong->Draw("same");
}
void makePretty(TH1* hist, int color)
{
	hist->SetStats(0);
	hist->SetLineWidth(3);
	hist->SetLineColor(color);
	hist->SetFillColor(color);
	hist->SetFillStyle(3004);
	if (color == kRed) 
	{
		hist->SetFillStyle(3005);
	}
}
float drawLegend(bool right = false)
{
	
	TLegend *legendMean2 = new TLegend(0.17,0.75,0.57,0.9,NULL,"brNDC");
	if (right) 
	{
		legendMean2 = new TLegend(0.50,0.75,0.8,0.85,NULL,"brNDC");
		
	}
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetFillStyle(0);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(gammaTotal,"All events","f");
        legendMean2->AddEntry(gammaWrong,"Lepton migrated","f");
	legendMean2->Draw();
}
