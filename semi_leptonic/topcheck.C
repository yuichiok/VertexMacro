void topcheck(string filename = "/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR.root")
{
	TFile * file = TFile::Open(filename.c_str());
	int bin_e = 40;
	int max_e = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1500,500);
	c1->Divide(3,1);
	c1->cd(2);
	TH1F * cosRecoKaon = new TH1F("cosRecoKaon", "Kaon charge", bin_e,-1.0,max_e);
	TH1F * cosRecoLepton = new TH1F("cosRecoLepton", "Lepton charge", bin_e,-1.0,max_e);
	TH1F * cosRecoVtx = new TH1F("cosRecoVtx", "Vertex charge", bin_e,-1.0,max_e);
	cosRecoKaon->Sumw2();
	cosRecoVtx->Sumw2();
	cosRecoLepton->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{top};Entries (normalised to unity)", bin_e,-1.0,max_e);
	int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > -2 ");
	int w = 4;
	cosRecoKaon->SetLineWidth(w);
	cosRecoVtx->SetLineWidth(w);
	cosRecoKaon->SetLineColor(kBlue+1);
	cosRecoVtx->SetLineColor(kOrange);
	cosRecoLepton->SetLineWidth(w);
	cosRecoLepton->SetLineColor(kRed+1);
	cosGen->SetMinimum(0);
	cosGen->SetLineWidth(3);
	cosGen->SetLineStyle(2);
	cosGen->SetLineColor(kGreen+1);
	cosGen->SetFillColor(kGreen+1);
	cosGen->SetFillStyle(3004);
	cosGen->SetStats(0);
	string cuts = " hadMass > 180 && hadMass < 420 && Top1mass < 200 && W1mass < 110 && Top1mass > 150 && W1mass > 50 &&";
	Stats->Draw("-Sum$(Top1KaonCharges)*Top1costheta>>cosRecoKaon",(cuts + "abs(Sum$(Top1KaonCharges)) > 0 && Top1costheta < 1").c_str());
	Stats->Draw("-Top1bcharge*Top1costheta / abs(Top1bcharge)>>cosRecoVtx", (cuts + "abs(Top1bcharge) > 0 && Top1bmomentum > 0").c_str());
	int leptons = Stats->Draw("-Top2leptonCharge*Top1costheta >>cosRecoLepton", (cuts + "1").c_str());
	//int leptons = Stats->Draw("-Top2leptonCharge*Top1costheta >>cosRecoLepton", (cuts + "Top1gamma+Top2gamma > 2.5 &&Top2gamma < 1.8").c_str());
	//int leptons = Stats->Draw("-Top2leptonCharge*Top1costheta >>cosRecoLepton", (cuts + "chiGammaT+chiCosWb+chiPbstar < 15").c_str());
	gPad->SetLeftMargin(0.14);
	cosGen->GetYaxis()->SetTitleOffset(1.5);
	gPad->SetBottomMargin(0.14);
	cosGen->GetXaxis()->SetTitleOffset(0.85);
	cosGen->GetXaxis()->SetTitleSize(.07);
	cout << "Generated:\n";
	float afbgen = getAfb(cosGen);
	cout << "------------KAON------------\n";
	float afbkaon = getAfb(cosRecoKaon);
	cout << "Quality: " << afbkaon / afbgen * 100 << "%\n";
	cosGen->DrawNormalized("");
	cosRecoKaon->DrawNormalized("same");
	drawLegend(cosRecoKaon);
	c1->cd(1);
	gPad->SetLeftMargin(0.14);
	cosGen->GetYaxis()->SetTitleOffset(1.5);
	gPad->SetBottomMargin(0.14);
	cosGen->GetXaxis()->SetTitleOffset(0.85);
	cosGen->GetXaxis()->SetTitleSize(.07);
	cout << "-------------VTX------------\n";
	float afbvtx = getAfb(cosRecoVtx);
	cout << "Quality: " << afbvtx / afbgen * 100 << "%\n";
	cosGen->DrawNormalized("");
	cosRecoVtx->DrawNormalized("same");
	drawLegend(cosRecoVtx);
	c1->cd(3);
	gPad->SetLeftMargin(0.15);
	cosGen->GetYaxis()->SetTitleOffset(1.5);
	gPad->SetBottomMargin(0.14);
	cosGen->GetXaxis()->SetTitleOffset(0.85);
	cosGen->GetXaxis()->SetTitleSize(.07);
	cout << "-----------LEPTON-----------\n";
	float afblep = getAfb(cosRecoLepton);
	cout << "Quality: " << afblep / afbgen * 100 << "%\n";
	cout << "N: " << leptons << endl;
	cosGen->DrawNormalized("");
	cosRecoLepton->DrawNormalized("same");
	drawLegend(cosRecoLepton);
}
float getAfb(TH1F * h)
{
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	h->Fit("fgen","Q");
	float afbgenf = (fgen->Integral(0,1) - fgen->Integral(-1,0)) / (fgen->Integral(0,1) + fgen->Integral(-1,0));
	cout << "AFB: " << afbgenf << endl;
	return 	afbgenf;
}
float drawLegend(TH1F * h)
{
	TLegend *legendMean2 = new TLegend(0.20,0.7,0.8,0.85,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetFillStyle(0);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(cosGen,"Generated","f");
        legendMean2->AddEntry(h,h->GetTitle(),"fl");
	legendMean2->Draw();
}
