#include <unistd.h>
#include <iostream>
#define MAXV 8
void masses()
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
	int bin_e = 100;
	int max_e = 250;
	int min_e = 0;
	TH1F * topmass = new TH1F("topmass", "E(Ntracks)", bin_e,min_e,max_e);
	TH1F * top2mass = new TH1F("top2mass", "E(Ntracks)", bin_e,min_e,max_e);
	TH1F * wmass = new TH1F("wmass", ";m_{W|t} [GeV];Events / 2.5 GeV", bin_e,min_e,max_e);
	TH1F * w2mass = new TH1F("w2mass", ";m_{W|t} [GeV];Events / 2.5 GeV", bin_e,min_e,max_e);

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

