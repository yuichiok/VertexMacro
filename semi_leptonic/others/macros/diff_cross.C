#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"

#define MAXV 8

using namespace std;

void diff_cross()
{
	// set plot style
	SetQQbarStyle();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

	TCanvas * c1 		= new TCanvas("c1", "Data-MC",0,0,500,500);
	TF1 		*f_LLR	=	new TF1("f_LLR","0.155*(1+x)^2",-1,1);
	TF1 		*f_LRL	=	new TF1("f_LRL","0.0425*(1-x)^2",-1,1);
	TF1 		*f_LLRR	=	new TF1("f_LLRR","-0.14*x^2+0.14",-1,1);
	TF1 		*f_SUM	=	new TF1("f_SUM","0.155*(1+x)^2 + 0.0425*(1-x)^2 + -0.14*x^2+0.14",-1,1);


	f_LLR->SetTitle("");
	f_LLR->GetXaxis()->SetTitle("cos#theta");
	f_LLR->GetYaxis()->SetTitle("d #sigma / d cos#theta");
	f_LLR->SetMaximum(0.8);

	//f_LLR->SetLineWidth(2);
	f_LLR->SetLineColor(kBlue);
	f_LLR->SetLineStyle(2);
	
	//f_LRL->SetLineWidth(2);
	f_LRL->SetLineColor(kRed);
	f_LRL->SetLineStyle(2);

	//f_LLRR->SetLineWidth(2);
	f_LLRR->SetLineColor(kGreen);
	f_LLRR->SetLineStyle(2);

	//f_SUM->SetLineWidth(3);

	f_LLR->Draw();
	f_LRL->Draw("same");
	f_LLRR->Draw("same");
	f_SUM->Draw("same");

	TLegend *leg = new TLegend(0.2,0.65,0.65,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(f_SUM,"sum","l");
	leg->AddEntry(f_LLR,"t_{L}#bar{t}_{R}","l");
	leg->AddEntry(f_LRL,"t_{R}#bar{t}_{L}","l");
	leg->AddEntry(f_LLRR,"t_{L}#bar{t}_{L} + t_{R}#bar{t}_{R}","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	c1->Update();

}

