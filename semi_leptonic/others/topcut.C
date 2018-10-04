
void topcut(string filename = "/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR.root")
{
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	gPad->SetBottomMargin(0.12);
	TFile * bSignal = TFile::Open(filename.c_str());
	
	TH1F * b1 = new TH1F("b1","; #gamma_{t}^{had} + #gamma_{t}^{lep};Entries",100,2,4);
	Stats->Draw("Top1gamma+Top2gamma>> b1","Top1gamma+Top2gamma < 4.5 && hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 &&MCBWcorrect == 1");
	TH1F * b2 = new TH1F("b2","; #gamma_{t}^{had} + #gamma_{t}^{lep};Entries",100,2,4);
	Stats->Draw("Top1gamma+Top2gamma>> b2","Top1gamma+Top2gamma < 4.5 &&hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 &&MCBWcorrect == 0");
	makePretty(b2,kRed);
	makePretty(b1,kBlue);
	THStack * stack = new THStack("h",";#gamma_{t}^{had} + #gamma_{t}^{lep};Entries");
	stack->Add(b2);
	stack->Add(b1);
	stack->Draw();
	TLegend *legendMean2 = new TLegend(0.55,0.7,0.9,0.85,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
        //legendMean2->AddEntry(b1,"Reconstructed","f");
        //legendMean2->AddEntry(b2,"Missing","f");
        legendMean2->AddEntry(b1,"Correct combination","f");
        legendMean2->AddEntry(b2,"Wrong combination","f");
	legendMean2->Draw()	;
	stack->GetYaxis()->SetTitleOffset(1.5);
}
	
void makePretty(TH1 * vtxTotal, int color, int line = 0)
{
	vtxTotal->GetYaxis()->SetTitleOffset(1.5);
	vtxTotal->SetLineWidth(3);
	vtxTotal->SetLineStyle(line);
	vtxTotal->SetLineColor(color);
	vtxTotal->SetMinimum(0);
	vtxTotal->SetStats(0);
	vtxTotal->SetFillStyle(3004);
	vtxTotal->SetFillColor(color);
	if (color == kBlue) 
	{
		vtxTotal->SetFillStyle(3005);
	}
}
