
#include <unistd.h>
#include <iostream>
#define MAXV 8

void makePretty(TH1F * cosAll, int color, int reconumber);

void OneTrack2()
{
	string recofilepath_before = "/home/ilc/yokugawa/run_preset/root_merge/TrashRecoProcessor_out/before_vtx_recovery/";
	string recofilename_before = "RecoTest_before.root";
	string recofile_before = recofilepath_before + recofilename_before;

	TFile * file = TFile::Open(recofile_before.c_str());
	int bin_e = 50;
	int max_e = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,500);
	c1->Divide(2,1);
	TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,.0,max_e);
	TH1F * cosOne = new TH1F("cosOne", "E(Ntracks)", bin_e,.0,max_e);
	TH1F * cosOtherLow = new TH1F("cosOtherLow", "tracks", bin_e,.0,max_e);
	TH1F * cosOtherHigh = new TH1F("cosOtherHigh", "tracks", bin_e,.0,max_e);
	TH1F * cosOtherLowDist = new TH1F("cosOtherLowDist", "tracks", bin_e,.0,max_e);
	TH1F * cosAll = new TH1F("cosAll", "E(Ntracks)", bin_e,.0,max_e);

	c1->cd(2);
	TTree * normaltree = (TTree*) file->Get( "MissedVertex" ) ;
	TTree * TaggedVertices = (TTree*) file->Get( "TaggedVertices" ) ;
	TTree * Stats = (TTree*) file->Get( "Stats" ) ;
	cosOne->SetLineColor(kBlue);
	cosOne->SetLineWidth(3);
	//cosOtherLow->SetLineColor(kMagenta);
	//cosOtherLow->SetLineWidth(3);
	cosOtherHigh->SetLineColor(kRed);
	cosOtherHigh->SetLineWidth(3);
	cosOtherLowDist->SetLineColor(kGreen);
	cosOtherLowDist->SetLineWidth(3);
	//cosOne->SetFillColor(kBlue);
	//cosOtherLow->SetFillColor(kMagenta);
	//cosOtherHigh->SetFillColor(kRed);
	//cosOtherLowDist->SetFillColor(kGreen);
	cosOtherLowDist->SetTitle("|cos#theta_{vertex}|");
	int vtxnumber = Stats->GetEntries();
	int reconumber = TaggedVertices->Draw("abs(costhetaOfParticles) >> cosReco","momentumOfParticles > 0");
	normaltree->Draw("abs(costhetaMissedVtx) >> cosOne","numberOfTracksMissedVtx < 2");
	//normaltree->Draw("costhetaMissedVtx >> cosOtherLow","numberOfTracksMissedVtx > 1 && momentumMissedVtx < 15.0 && distanceMissedVtx > 0.8");
	//normaltree->Draw("abs(costhetaMissedVtx) >> cosOtherHigh","numberOfTracksMissedVtx > 1 && momentumMissedVtx > 15.0 && distanceMissedVtx > .30");
	normaltree->Draw("abs(costhetaMissedVtx) >> cosOtherHigh","numberOfTracksMissedVtx > 1 && averagepMissedVtx > 4.0 && averagesMissedVtx > .1");
	//normaltree->Draw("abs(costhetaMissedVtx) >> cosOtherLowDist","numberOfTracksMissedVtx > 1 && ( momentumMissedVtx < 15.0 || distanceMissedVtx < .30)");
	normaltree->Draw("abs(costhetaMissedVtx) >> cosOtherLowDist","numberOfTracksMissedVtx > 1 && ( averagepMissedVtx < 4.0 || averagesMissedVtx < .5)");
	THStack * stack = new THStack("stack",";|cos#theta_{vtx}|; Entries (normalised to N_{rec})");
	//stack->Add(cosOtherLow);
	cosOtherLowDist->Scale(1./vtxnumber);
	cosOne->Scale(1./vtxnumber);
	cosOtherHigh->Scale(1./vtxnumber);
	stack->Add(cosOtherLowDist);
	stack->Add(cosOne);
	stack->Add(cosOtherHigh);
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	stack->Draw();
	stack->GetYaxis()->SetTitleOffset(1.7);
	TLegend *legendMean = new TLegend(0.2,0.7,0.63,0.85,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(cosOtherHigh,"Other vertices","f");
        legendMean->AddEntry(cosOne,"0-1 prong decay","f");
        legendMean->AddEntry(cosOtherLowDist,"Low momentum or low offset","f");
        //legendMean->AddEntry(cosOtherLow,"|p|_{B} < 15 GeV","fp");
	legendMean->Draw();
	stack->GetXaxis()->SetTitle("|cos#theta|");
	gPad->Modified();
	c1->cd(1);
	TTree * tree = (TTree*) file->Get( "MissedTracks" ) ;
	TH1F * cosLowtr = new TH1F("cosLowtr", "tracks", bin_e,.0,max_e);
	TH1F * cosGoodTracks = new TH1F("cosGoodTracks", "tracks", bin_e,.0,max_e);
	TH1F * cosNoPFO = new TH1F("cosNoPFO", "tracks", bin_e,.0,max_e);
	TH1F * cosNoVTX = new TH1F("cosNoVTX", "tracks", bin_e,.0,max_e);
	TH1F * cosNoTrack = new TH1F("cosNoTrack", "tracks", bin_e,.0,max_e);
	TH1F * cosBtag = new TH1F("cosBtag", "tracks", bin_e,.0,max_e);
	//tree->Draw("costhetaMissed >> cosGoodTracks","momentumMissed > 1.0 && offsetMissed > 3*sqrt(0.005*0.005+0.01*0.01/momentumMissed/momentumMissed)");
	//tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (btagMissed > 0.8)");
	tree->Draw("abs(costhetaMissed) >> cosAll","");
	tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && momentumMissed > 1.0 && offsetMissed > 0.015");
	tree->Draw("abs(costhetaMissed) >> cosLowtr","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (deviationMissed < 25*sqrt(vertexAngleMissed)+2 || vertexAngleMissed > 0.08)");
	tree->Draw("abs(costhetaMissed) >> cosNoPFO","isrecoMissed == 0 && hastrackMissed == 1");
	tree->Draw("abs(costhetaMissed) >> cosNoTrack","hastrackMissed == 0");
	tree->Draw("abs(costhetaMissed) >> cosNoVTX"," vtxHitsMissed == 0 && ftdHitsMissed == 0 && isrecoMissed == 1");
	//tree->Draw("abs(costhetaMissed) >> cosBtag"," (vtxHitsMissed > 0 || ftdHitsMissed > 0) && isrecoMissed == 1 && btagMissed < 0.8");
	tree->Draw("abs(costhetaMissed) >> cosBtag"," (vtxHitsMissed > 0 || ftdHitsMissed > 0) && isrecoMissed == 1 && (btagMissed < 0.8)");
	std::cout << "Vertex total: " << cosAll->Integral()
		  << " no track: " << cosNoTrack->Integral()
		  << " no vxd hits: " << cosNoVTX->Integral()
		  << " no PFO: " << cosNoPFO->Integral()
		  << " recoverable: " <<  cosGoodTracks->Integral()// +cosNoPFO->Integral()
		  << " \n";
	makePretty(cosAll, kRed, reconumber);
	makePretty(cosNoVTX, kBlue, reconumber);
	makePretty(cosNoTrack, kBlack, reconumber);
	makePretty(cosLowtr, kMagenta, reconumber);
	makePretty(cosNoPFO, kGreen, reconumber);
	THStack * stack2 = new THStack("stack2",";|cos#theta|; Entries (normalised to N_{rec})");
	stack->Add(cosNoTrack);
	stack->Add(cosNoVTX);
	stack->Add(cosNoPFO);
	//stack->Add(cosBtag);
	stack->Add(cosLowtr);
	//stack->Add(cosAll, "nostack");
	//stack->Add(cosGoodTracks);
	cosAll->SetMinimum(0);
	stack->SetMinimum(0);
	stack->SetMaximum(cosAll->GetMaximum());
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	stack->Draw();
	cosAll->Draw("same");
	stack->GetYaxis()->SetTitleOffset(1.7);
	TLegend *legendMean2 = new TLegend(0.2,0.6,0.63,0.85,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(cosAll,"Other reasons","f");
        legendMean2->AddEntry(cosLowtr,"Low offset significance","f");
        legendMean2->AddEntry(cosNoPFO,"Nonreconstructed PFO","f");
        legendMean2->AddEntry(cosNoVTX,"No hits in VXD and FTD","f");
        legendMean2->AddEntry(cosNoTrack,"No tracking information","f");
	legendMean2->Draw();
	cosAll->GetXaxis()->SetTitle("|cos#theta|");
	gPad->Modified();
	std::cout << "Novertex total: " << cosOne->Integral()+cosOtherLowDist->Integral()+cosOtherHigh->Integral()
		  << " one track: " << cosOne->Integral()
		  << " lowdist vtx: " << cosOtherLowDist->Integral()
		  << " others: " << cosOtherHigh->Integral()
		  << " \n";
	//tree->Draw("costhetaMissed >> cosAll","","same");
	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,1000,500);
	c2->cd();
	c2->Divide(2,1);
	c2->cd(1);
	float max_p = 10;
	TH1F * pLowtr = new TH1F("pLowtr", "tracks", bin_e,.0,max_p);
	TH1F * pGoodTracks = new TH1F("pGoodTracks", "tracks", bin_e,.0,max_p);
	TH1F * pNoPFO = new TH1F("pNoPFO", "tracks", bin_e,.0,max_p);
	TH1F * pNoVTX = new TH1F("pNoVTX", "tracks", bin_e,.0,max_p);
	TH1F * pNoTrack = new TH1F("pNoTrack", "tracks", bin_e,.0,max_p);
	TH1F * pBtag = new TH1F("pBtag", "tracks", bin_e,.0,max_p);
	TH1F * pAll = new TH1F("pAll", "tracks", bin_e,.0,max_p);
	//tree->Draw("costhetaMissed >> cosGoodTracks","momentumMissed > 1.0 && offsetMissed > 3*sqrt(0.005*0.005+0.01*0.01/momentumMissed/momentumMissed)");
	//tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (btagMissed > 0.8)");
	tree->Draw("abs(momentumMissed) >> pAll","");
	tree->Draw("abs(momentumMissed) >> pGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && momentumMissed > 1.0 && offsetMissed > 0.015");
	tree->Draw("abs(momentumMissed) >> pLowtr","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (deviationMissed < 25*sqrt(vertexAngleMissed)+2 || vertexAngleMissed > 0.08)");
	tree->Draw("abs(momentumMissed) >> pNoPFO","isrecoMissed == 0 && hastrackMissed == 1");
	tree->Draw("abs(momentumMissed) >> pNoTrack","hastrackMissed == 0");
	tree->Draw("abs(momentumMissed) >> pNoVTX"," vtxHitsMissed == 0 && ftdHitsMissed == 0 && isrecoMissed == 1");
	makePretty(pAll, kRed, reconumber);
	makePretty(pNoVTX, kBlue, reconumber);
	makePretty(pNoTrack, kBlack, reconumber);
	makePretty(pLowtr, kMagenta, reconumber);
	makePretty(pNoPFO, kGreen, reconumber);
	THStack * pstack = new THStack("stack3",";|p| [GeV]; Entries (normalised to N_{rec})");
	pstack->Add(pNoTrack);
	pstack->Add(pNoVTX);
	pstack->Add(pNoPFO);
	//stack->Add(cosBtag);
	pstack->Add(pLowtr);
	//stack->Add(cosAll, "nostack");
	//stack->Add(cosGoodTracks);
	pAll->SetMinimum(0);
	pstack->SetMinimum(0);
	pstack->SetMaximum(pAll->GetMaximum());
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	pstack->Draw();
	pAll->Draw("same");
	gPad->Modified();
	pstack->GetYaxis()->SetTitleOffset(1.7);
	TLegend *legendMean3 = new TLegend(0.5,0.6,0.93,0.85,NULL,"brNDC");
        legendMean3->SetFillColor(kWhite);
        legendMean3->SetBorderSize(0);
        legendMean3->AddEntry(pAll,"Other reasons","f");
        legendMean3->AddEntry(pLowtr,"Low offset significance","f");
        legendMean3->AddEntry(pNoPFO,"Nonreconstructed PFO","f");
        legendMean3->AddEntry(pNoVTX,"No hits in VXD and FTD","f");
        legendMean3->AddEntry(pNoTrack,"No tracking information","f");
	legendMean3->Draw();
}
void makePretty(TH1F * cosAll, int color, int reconumber)
{
	cosAll->Scale(1./reconumber);
	cosAll->SetLineColor(color);
	//cosAll->SetFillColor(color-1);
	cosAll->SetLineWidth(3);

}
