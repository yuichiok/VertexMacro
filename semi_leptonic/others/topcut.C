#include <unistd.h>
#include <iostream>
#define MAXV 8

void makePretty(TH1 * vtxTotal, int color, int line = 0);

void topcut()
{
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	int token=0;
	string filename0 = "/home/ilc/yokugawa/run/root_merge/";
	string filename1;

	cout << "0 = New/Small" 	  << endl;
	cout << "1 = New/Large" 	  << endl;
	cout << "2 = New/Large/QQbar" << endl;
	cout << "3 = Old      " 	  << endl;
	cout << "4 = Old/yyxylv      "       << endl;
	cout << "Choose from 0-4: ";
	cin  >> token;
	cout << endl;

	switch(token){
		case 0 : filename1 = "new/small/leptonic_yyxyev_eLeR_new_small.root";
						 break;
		case 1 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large.root";
						 break;
		case 2 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar.root";
						 break;
		case 3 : filename1 = "old/leptonic_yyxyev_eLeR_old_lcut.root" ;
						 break;
		case 4 : filename1 = "old/leptonic_yyxylv_eLeR_iso_lep_lcut.root" ;
						 break;
	}

	string filename = filename0 + filename1;
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	gPad->SetBottomMargin(0.12);
	TFile * bSignal = TFile::Open(filename.c_str());
	
	TH1F * b1 = new TH1F("b1","; #gamma_{t}^{had} + #gamma_{t}^{lep};Entries",100,2,4);
	normaltree->Draw("Top1gamma+Top2gamma>> b1","Top1gamma+Top2gamma < 4.5 && hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 &&MCBWcorrect == 1");
	TH1F * b2 = new TH1F("b2","; #gamma_{t}^{had} + #gamma_{t}^{lep};Entries",100,2,4);
	normaltree->Draw("Top1gamma+Top2gamma>> b2","Top1gamma+Top2gamma < 4.5 &&hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 &&MCBWcorrect == 0");
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
