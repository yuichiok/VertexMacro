
#include <unistd.h>
#include <iostream>
#include "../style/Style.C"
#include "../style/Labels.C"

#define MAXV 8
void makePretty(TH1F * cosAll, int color, int reconumber)
{
	cosAll->Scale(1./reconumber);
	cosAll->SetLineColor(color);
	//cosAll->SetFillColor(color-1);
	cosAll->SetLineWidth(3);

}
void LostTracksClassification(string filename = "/home/irles/WorkArea/BBbar_tests/ntuples/trackrestoring/IDR_vertex_reprocessed/OUTPUT3_eL_l5_valencia2.0_may2019_merged.root", TString topology="bbbar")
{

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0);

  gStyle->SetTitleX(0.19); 
  gStyle->SetTitleY(0.85); 

  TString title;
  if(topology=="bbbar")  title="e_{L}^{-}e_{R}^{+}#rightarrowb#bar{b} @500 GeV, IDR-L";
  else if (topology=="ttbar")  title="e_{L}^{-}e_{R}^{+}#rightarrow t#bar{t} (l#nu+jets) @500 GeV, IDR-L";
  
  
	TFile * file = TFile::Open(filename.c_str());
	int bin_e = 50;
	int max_e = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,800);

	TTree *Stats = (TTree*)file->Get("Stats");
        int vtxnumber = Stats->GetEntries();
        TTree *TaggedVertices = (TTree*)file->Get("TaggedVertices");
        int reconumber = TaggedVertices->Draw("abs(costhetaOfParticles)","momentumOfParticles > 0");

	
	c1->cd(1);
	TTree * tree = (TTree*)file->Get("MissedTracks");

	TH1F * cosLowtr = new TH1F("cosLowtr", "tracks", bin_e,.0,max_e);
	TH1F * cosGoodTracks = new TH1F("cosGoodTracks", "tracks", bin_e,.0,max_e);
	TH1F * cosNoPFO = new TH1F("cosNoPFO", "tracks", bin_e,.0,max_e);
	TH1F * cosNoVTX = new TH1F("cosNoVTX", "tracks", bin_e,.0,max_e);
	TH1F * cosNoFTD = new TH1F("cosNoFTD", "tracks", bin_e,.0,max_e);
	TH1F * cosNoTrack = new TH1F("cosNoTrack", "tracks", bin_e,.0,max_e);
	TH1F * cosBtag = new TH1F("cosBtag", "tracks", bin_e,.0,max_e);
	TH1F * cosAll = new TH1F("cosAll", "tracks", bin_e,.0,max_e);
	//tree->Draw("costhetaMissed >> cosGoodTracks","momentumMissed > 1.0 && offsetMissed > 3*sqrt(0.005*0.005+0.01*0.01/momentumMissed/momentumMissed)");
	//tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (btagMissed > 0.8)");
	tree->Draw("abs(costhetaMissed) >> cosAll","");
	tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && momentumMissed > 1.0 && offsetMissed > 0.015");
	tree->Draw("abs(costhetaMissed) >> cosLowtr","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (deviationMissed < 25*sqrt(vertexAngleMissed)+2 || vertexAngleMissed > 0.08)");
	tree->Draw("abs(costhetaMissed) >> cosNoPFO","isrecoMissed == 0 && hastrackMissed == 1");
	tree->Draw("abs(costhetaMissed) >> cosNoTrack","hastrackMissed == 0");
	tree->Draw("abs(costhetaMissed) >> cosNoVTX"," ftdHitsMissed == 0 && vtxHitsMissed == 0 && isrecoMissed == 1");
	//tree->Draw("abs(costhetaMissed) >> cosNoFTD"," (ftdHitsMissed == 0 || vtxHitsMissed == 0) && (ftdHitsMissed == 1 || vtxHitsMissed == 1) && isrecoMissed == 1");
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
	makePretty(cosNoFTD, kYellow, reconumber);
	makePretty(cosNoTrack, kBlack, reconumber);
	makePretty(cosLowtr, kMagenta, reconumber);
	makePretty(cosNoPFO, kGreen, reconumber);

	THStack * stack2 = new THStack("stack2",";|cos#theta|; Entries (normalised to N_{rec})");
	cosNoTrack->SetFillColor(1);
	cosNoTrack->SetFillStyle(3003);
	stack2->Add(cosNoTrack);

	cosNoVTX->SetFillColor(4);
	cosNoVTX->SetFillStyle(3004);
	stack2->Add(cosNoVTX);
	
	//	stack2->Add(cosNoFTD);
	cosNoPFO->SetFillColor(3);
	cosNoPFO->SetFillStyle(1001);
	stack2->Add(cosNoPFO);
	
	//stack2->Add(cosBtag);
	cosLowtr->SetFillColor(6);
	cosLowtr->SetFillStyle(3005);
	stack2->Add(cosLowtr);
	//stack2->Add(cosAll, "nostack2");
	//stack2->Add(cosGoodTracks);


	cosAll->SetTitle(title);
	cosAll->GetXaxis()->SetTitle("|cos#theta|");
	cosAll->GetYaxis()->SetTitle("Entries (normalised to N_{rec})");
	cosAll->GetYaxis()->SetTitleOffset(1.5);

	cosAll->GetYaxis()->SetRangeUser(0,0.01);
	cosAll->Draw("histo");
	stack2->Draw("histosame");

	//	stack2->GetYaxis()->SetTitleOffset(1.7);
	TLegend *legendMean2 = new TLegend(0.2,0.5,0.63,0.75,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(cosAll,"Other reasons","f");
        legendMean2->AddEntry(cosLowtr,"Low offset significance","f");
        legendMean2->AddEntry(cosNoPFO,"Nonreconstructed PFO","f");
        legendMean2->AddEntry(cosNoVTX,"No hits in VXD&FTD","f");
	//	legendMean2->AddEntry(cosNoFTD,"No hits in FTD","f");
        legendMean2->AddEntry(cosNoTrack,"No tracking information","f");
	legendMean2->Draw();
	//	cosAll->GetXaxis()->SetTitle("|cos#theta|");

	c1->Update();
	QQBARLabel(0.2,0.85,"",1);


}

