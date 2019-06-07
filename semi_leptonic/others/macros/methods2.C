#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;

void setLabels(TH1F * good);
void makePretty(TH1F * good, int color);
float calculate(int accepted, int rejected);

void methods2()
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);

	int token=0;
	string filename0 = "/home/ilc/yokugawa/run/root_merge/";
	//string filename0 = "rootfile/"; 
	string filename1;

	cout << "0 = yyxylv/small" 	  << endl;
	cout << "1 = yyxylv/large" 	  << endl;
	cout << "2 = yyxyev/small" << endl;
	cout << "3 = yyxyev/large" << endl;
	cout << "Choose from 0-3: ";
	cin  >> token;
	cout << endl;

	switch(token){
		case 0 : filename1 = "new/small/QQbar_s5_yyxylv_eLeR.root";
						 break;
		case 1 : filename1 = "new/large/QQbar_l5_yyxylv_eLeR.root";
						 break;
		case 2 : filename1 = "new/small/QQbar_s5_yyxyev_eLeR.root";
						 break;
		case 3 : filename1 = "new/large/QQbar_l5_yyxyev_eLeR.root";
						 break;
	}

	string filename = filename0 + filename1;
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	TTree * Stats = (TTree*) file->Get( "Stats" ) ;

	int nbins = 7;
	int minn = 1;
	int maxn = minn + nbins;
	TH1F * all = new TH1F("all", ";Methods;Entries", nbins,minn,maxn);
	TH1F * good = new TH1F("good", ";methods", nbins,minn,maxn);
	TH1F * refused = new TH1F("refused", ";methods", nbins,minn,maxn);
	TH1F * zero = new TH1F("zero", ";methods", nbins,minn,maxn);
	TH1F * division1 = new TH1F("division1", ";methods", nbins,minn,maxn);
	TH1F * division2 = new TH1F("division2", ";methods", nbins,minn,maxn);
	TH1F * division3 = new TH1F("division3", ";methods", nbins,minn,maxn);
	string bcuts   = " MCMass > 200 && MCPDG == 5 && methodUsed";

	all->Sumw2();

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
	//TCut topcuts = rcTW + hadM + pcut + gcut + methodAll;
	TCut topcuts = rcTW + hadM + pcut + gcut;
	TCut methodCorrectCut = "methodCorrect";

	all->SetMinimum(0);
	refused->Sumw2();
	//setLabels(all);
	good->Sumw2();
	zero->Sumw2();

	// plotting the histogram of purity
	Stats->Draw("methodTaken >> all","","e");
	Stats->Draw("methodSameCharge >> refused",topcuts,"e");
	Stats->Draw("methodTaken >> good", methodCorrectCut + topcuts + methodAll,"samee");

	// get numbers
	int mT1 = Stats->Draw("methodTaken", methodCorrectCut + topcuts + method1,"");
	int mR1 = Stats->Draw("methodSameCharge", topcuts + method1, "");

	int mT2 = Stats->Draw("methodTaken", methodCorrectCut + topcuts + method2,"");
	int mR2 = Stats->Draw("methodSameCharge", topcuts + method2, "");

	int mT3 = Stats->Draw("methodTaken", methodCorrectCut + topcuts + method3,"");
	int mR3 = Stats->Draw("methodSameCharge", topcuts + method3, "");

	int mT4 = Stats->Draw("methodTaken", methodCorrectCut + topcuts + method4,"");
	int mR4 = Stats->Draw("methodSameCharge", topcuts + method4, "");

  float p1 = calculate(mT1,mR1);
  float p2 = calculate(mT2,mR2);
  float p3 = calculate(mT3,mR3);
  float p4 = calculate(mT4,mR4);

  cout << "acc1 = " << mT1 << ", rej1 = " << mR1 << endl;
	cout << p1 << endl;

  cout << "acc2 = " << mT2 << ", rej2 = " << mR2 << endl;
	cout << p2 << endl;

  cout << "acc3 = " << mT3 << ", rej3 = " << mR3 << endl;
	cout << p3 << endl;

  cout << "acc4 = " << mT4 << ", rej4 = " << mR4 << endl;
	cout << p4 << endl;

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
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	all->GetXaxis()->SetTitleOffset(1.7);
	all->GetYaxis()->SetTitleOffset(1.6);

	TCanvas * c2 = new TCanvas("c2", "The 3d view",0,0,500,500);

	division1->SetMinimum(0);
	division1->SetMaximum(1);
	division2->SetLineWidth(2);
	division1->GetXaxis()->SetTitleOffset(1.7);
	division1->Draw("e");

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

float calculate(int accepted, int rejected)
{
	float a=1;
	float b=-1;
	float c= (float)(rejected)/ (2* (float(accepted+rejected)));
	float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
	float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
	if(p>0.99) p=0;
	if(p2>0.99) p2=0;
	if(p<0) p=0;
	if(p2<0) p2=0;
	if(p >0 || p2>0 ) p=max(p,p2);

	return p;

}






