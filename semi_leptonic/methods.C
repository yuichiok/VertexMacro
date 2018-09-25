#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;

void methods()
{
		TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);

		int token=0;
		string filename0 = "/home/ilc/yokugawa/run/root_merge/";
		//string filename0 = "rootfile/"; 
		string filename1;

		cout << "0 = New/Small" 	  << endl;
		cout << "1 = New/Large" 	  << endl;
		cout << "2 = New/Large/QQbar" << endl;
		cout << "3 = Old      " 	  << endl;
		cout << "Choose from 0-3: ";
		cin  >> token;
		cout << endl;

		switch(token){
				case 0 : filename1 = "leptonic_yyxyev_eLeR_new_small.root";
						 break;
				case 1 : filename1 = "leptonic_yyxyev_eLeR_new_large.root";
						 break;
				case 2 : filename1 = "leptonic_yyxyev_eLeR_new_large_QQbar.root";
						 break;
				case 3 : filename1 = "leptonic_yyxyev_eLeR_old_lcut.root" ;
						 break;
		}

		string filename = filename0 + filename1;
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());

		int nbins = 7;
		int minn = 1;
		int maxn = minn + nbins;
		TH1F * all = new TH1F("all", ";Methods;Entries", nbins,minn,maxn);
		all->Sumw2();
		TH1F * good = new TH1F("good", ";methods", nbins,minn,maxn);
		TH1F * refused = new TH1F("refused", ";methods", nbins,minn,maxn);
		TH1F * zero = new TH1F("zero", ";methods", nbins,minn,maxn);
		TH1F * division1 = new TH1F("division1", ";methods", nbins,minn,maxn);
		TH1F * division2 = new TH1F("division2", ";methods", nbins,minn,maxn);
		TH1F * division3 = new TH1F("division3", ";methods", nbins,minn,maxn);
		string bcuts   = " MCMass > 200 && MCPDG == 5 && methodUsed";
		//string topcuts = " hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.0 || Top2btag > 0.0)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";
		//string topcuts = "hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 ";

		//current
		//string topcuts = "hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && Top1gamma + Top2gamma > 2.4 && Top2gamma < 2.";

		//!string topcuts = "hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && Top1gamma + Top2gamma > 2.4 && Top2gamma < 2. && methodTaken==7";

		//string topcuts = " hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.0 || Top2btag > 0.0)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";

		//string topcuts = "hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && Top1gamma + Top2gamma > 2.4 && Top2gamma < 2. && methodTaken == 7";

		//string topcuts = " InvMass > 180 && maxPhotonEnergy < 40 && B1mass + B2mass < 120 && Sphericity < 0.2 && methodRefused == 0 && methodUsed > 0";
		
		
		// Selection lists
		TCut thru = "Thrust < 0.9";
		TCut hadM = "hadMass > 180 && hadMass < 420";
		TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";
		TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
		TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";
		
		// Methods selection
		TCut methodAll = "methodTaken > 0";
		TCut method1 = "methodTaken == 1";
		TCut method2 = "methodTaken == 2";
		TCut method3 = "methodTaken == 3";
		TCut method4 = "methodTaken == 4";
		TCut method5 = "methodTaken == 5";
		TCut method6 = "methodTaken == 6";
		TCut method7 = "methodTaken == 7";

		// Total cut applied
		TCut topcuts = rcTW + hadM + pcut + gcut + methodAll;
		TCut methodCorrectCut = "methodCorrect";
		
		all->SetMinimum(0);
		refused->Sumw2();
		//setLabels(all);
		good->Sumw2();
		zero->Sumw2();
		//Stats->Draw("methodUsed>> all","methodUsed > 0 && Top1mass < 200 && W1mass < 110","");
		//Stats->Draw("methodUsed>> good","methodUsed > 0 && methodCorrect && Top1mass < 200 && W1mass < 110","same");
		//Stats->Draw("methodTaken >> all"," MCMass > 200 && MCPDG == 5","e");
		Stats->Draw("methodTaken >> all",topcuts,"e");
		//	Stats->Draw("methodZeroCharge >> +all",topcuts.c_str(),"e");
		//Stats->Draw("methodSameCharge >> +all",topcuts.c_str(),"e");
		Stats->Draw("methodSameCharge >> refused",topcuts,"e");
		//	Stats->Draw("methodZeroCharge >> zero",topcuts.c_str(),"e");
		Stats->Draw("methodTaken >> good", methodCorrectCut + topcuts,"samee");

		division1->Divide(good, all);
		//division2->Divide(refused, all);
		//division3->Divide(zero, all);
		setLabels(division1);
		setLabels(all);
		makePretty(division1, kBlue);
		makePretty(division2, kRed);
		makePretty(division3, kBlack);
		makePretty(all, kBlue);
		all->Draw("he");
		division1->SetMinimum(0);
		division1->SetMaximum(1);
		division2->SetLineWidth(2);
		//division1->Draw("e");
		gPad->SetLeftMargin(0.15);
		gPad->SetBottomMargin(0.15);
		division1->GetXaxis()->SetTitleOffset(1.7);
		all->GetXaxis()->SetTitleOffset(1.7);
		all->GetYaxis()->SetTitleOffset(1.6);
		//division2->Draw("samee");
		//division3->Draw("samee");
		//good->Draw("same");
}
void setLabels(TH1F * good)
{

		good->GetXaxis()->SetLabelSize(0.06);
		good->GetXaxis()->SetBinLabel(1,"VTX+VTX");
		good->GetXaxis()->SetBinLabel(2,"KAON+KAON");
		good->GetXaxis()->SetBinLabel(3,"VTX+KAON");
		good->GetXaxis()->SetBinLabel(4,"VTX+KAON'");
		good->GetXaxis()->SetBinLabel(5,"VTX+L");
		good->GetXaxis()->SetBinLabel(6,"KAON+L");
		good->GetXaxis()->SetBinLabel(7,"L cut");

		/*good->GetXaxis()->SetBinLabel(7,"V_{1}+L");
		  good->GetXaxis()->SetBinLabel(8,"V_{2}+L");
		  good->GetXaxis()->SetBinLabel(9,"K_{1}+L");
		  good->GetXaxis()->SetBinLabel(10,"K_{2}+L");
		  good->GetXaxis()->SetBinLabel(11,"#chi^2");

		  good->GetXaxis()->SetBinLabel(1,"V_{1}+V_{2}");
		  good->GetXaxis()->SetBinLabel(2,"K_{1}+K_{2}");
		  good->GetXaxis()->SetBinLabel(3,"K_{1}+V_{1}");
		  good->GetXaxis()->SetBinLabel(4,"K_{2}+V_{2}");
		  good->GetXaxis()->SetBinLabel(5,"K_{2}+V_{1}");
		  good->GetXaxis()->SetBinLabel(6,"K_{1}+V_{2}");*/
		good->SetStats(0);
}
void makePretty(TH1F * good, int color)
{
		good->SetLineWidth(3);
		good->SetLineColor(color);
		good->SetFillColor(color);
		good->SetFillStyle(3004);
}
