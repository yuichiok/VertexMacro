#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void asymmetry()
{
		int token=0;
		string filename0 = "/home/ilc/yokugawa/run/root_merge/";
		//string filename0 = "rootfile/"; 
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
			case 0 : filename1 = "leptonic_yyxyev_eLeR_new_small.root";
					 break;
			case 1 : filename1 = "leptonic_yyxyev_eLeR_new_large.root";
					 break;
			case 2 : filename1 = "leptonic_yyxyev_eLeR_new_large_QQbar.root";
					 break;
			case 3 : filename1 = "leptonic_yyxyev_eLeR_old_lcut.root" ;
					 break;
			case 4 : filename1 = "leptonic_yyxylv_eLeR_iso_lep_lcut.root" ;
					 break;
		}

		string filename = filename0 + filename1;
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());

		int bin_e = 30;
		int max_e = 1;
		
		TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
		
		TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
		cosReco->Sumw2();
		TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{top};Entries", bin_e,-1.0,max_e);
		cosGen->Sumw2();

		//TTree * normaltree = Stats;
		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
		TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
		//cosReco->SetLineColor(kBlue);
		cosReco->SetLineWidth(3);
		cosGen->SetLineWidth(3);
		cosGen->SetLineStyle(2);
		cosGen->SetLineColor(kGreen+1);
		cosGen->SetFillColor(kGreen+1);
		cosGen->SetFillStyle(3004);

		//int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && abs(MCBcostheta) < 0.95");
		//int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && abs(MCBcostheta) < 0.95");
		int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
		int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");
		//int forward = normaltree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 && methodUsed");
		//int backward = normaltree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2 && methodUsed");
		//int forward = normaltree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 &&  qCostheta > -1.0");
		//int backward = normaltree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2 &&  qCostheta > -1.0");

		//float chi2 = chiTopMass + chiTopE + chiPbstar + chiCosWb;
		//string cuts = "";
		//string cuts = "&& B1momentum > 10 && B2momentum > 10";
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && Top1gamma + Top2gamma > 2.4 && Top2gamma < 2"; //BEST!!!!!
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && Top1gamma + Top2gamma > 2.4 && Top2gamma < 2.5"; //


		//Basic selection cuts **** The one we are using for Base cut ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";


		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50&& (  Top1gamma + Top2gamma > 2.1 && Top2gamma < 1.8 )"; 
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50&& abs(MCLeptonPDG) ==15"; 
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && (Top1bmomentum > 30 || Top2bmomentum > 30)";
		//CRP 16/7/18
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && (Top1bmomentum > 35 || Top2bmomentum > 35) && ((Top1gamma + Top2gamma) > 2.4 && Top2gamma < 2.5)";
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && (Top1bmomentum > 35 || Top2bmomentum > 35) && ((Top1gamma + Top2gamma) > 2.4 && ( Top1btag > 0.8 && Top2btag > 0.3) )";
		//CRP 17/7/18 Cut which brings distribution clostest to the one of Sviatoslav 

		///////////////
		// BASE CUTS //
		///////////////

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.0 || Top2btag > 0.0)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";

		// **** Full cuts (old) ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ((methodTaken == 1 && Top1btag > 0.8 && Top2btag > 0.8 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 1 )";

		// **** Test ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((methodTaken == 1 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 2 )";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4)";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ( methodTaken >= 1 )";

		//TCut cuts = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2.0 && Top1btag > 0.8 && Top2btag > 0.3 && methodTaken > 0";

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
		TCut cuts = rcTW + hadM + pcut + gcut + methodAll;

		TCut fcuts = "qCostheta > 0" + cuts;
		TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;
		int recoforward = normaltree->Draw("qCostheta >> cosReco", fcuts);
		int recobackward = normaltree->Draw("qCostheta >> +cosReco", bcuts);
		//int recoforward = normaltree->Draw("-Top1costheta*UsedBTVCM >> +cosReco", "(qCostheta > 0 && W1mass > 0 && UsedBTVCM !=0 && (MCBOscillation > -1 && MCBBarOscillation > -1 ))"); //UsedBTVCM
		//int recobackward = normaltree->Draw("-Top1costheta*UsedBTVCM >> +cosReco", "(qCostheta < 0 && qCostheta > -1.0 && W1mass > 0 && UsedBTVCM !=0 && (MCBOscillation > -1 && MCBBarOscillation > -1 ))");
		cosGen->SetStats(0);
		TF1 * fgen = new TF1("fgen","pol2",-1,1);
		TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
		fgen->SetLineColor(kGreen);
		fgen->SetLineStyle(3);
		freco->SetLineStyle(3);
		//cosGen->SetTitle("e_{L}p_{R} minivector original");
		cosGen->Scale(cosReco->GetEntries()/ cosGen->GetEntries());
		//cosReco->Scale(1./ cosReco->GetEntries());
		cosGen->Fit("fgen","Q");
		cosReco->Fit("freco", "QR");
		cosGen->SetMinimum(0);
		cosGen->Draw("he");
		fgen->Draw("same");
		//cosGen->Draw();
		cosGen->SetMinimum(0);
		cosReco->Draw("samee");
		TLegend *legendMean2 = new TLegend(0.20,0.75,0.6,0.85,NULL,"brNDC");
		legendMean2->SetFillColor(kWhite);
		legendMean2->SetBorderSize(0);
		legendMean2->AddEntry(cosGen,"Generated","f");
		legendMean2->AddEntry(cosReco,"Reconstructed","f");
		legendMean2->Draw();
		float afbgen = (float)(forward - backward) / (float) (forward + backward);
		float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);
		cout << "--------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------\n";
		//cout << "Integral: " << ( cosReco->Integral(11,20) - cosReco->Integral(1,10) ) / cosReco->Integral()<< endl;
		std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
		std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
		std::cout << "Chi2: " << cosReco->Chi2Test(cosGen,"UUNORMCHI2/NDF") << "\n";
		cout << "--------------------------------------------------------------\n";
		//cout << "Integral: " << fgen->Integral(-1,0) << " " << fgen->Integral(0,1) << endl;
		float afbgenf = (fgen->Integral(0,1) - fgen->Integral(-1,0)) / (fgen->Integral(0,1) + fgen->Integral(-1,0));
		float afbrecof = (freco->Integral(0,1) - freco->Integral(-1,0)) / (freco->Integral(0,1) + freco->Integral(-1,0));
		gPad->SetLeftMargin(0.14);
		cosGen->GetYaxis()->SetTitleOffset(1.3);
		cout << "Afb gen functional: " << afbgenf << endl;
		cout << "Afb reco functional: " << afbrecof << "(" << afbrecof / afbgenf *100 << "%)"   << endl;
		float nominal = 30.8;
		float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
		cout << "Final efficiency: " << efficiency << "% (+" << efficiency / nominal *100 -100 << "%)\n" ;
		cout << "--------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------\n";
		//file->Close();
}

