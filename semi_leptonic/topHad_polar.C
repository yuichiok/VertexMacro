
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void topHad_polar()
{
		//TFile * file = TFile::Open(filename.c_str());
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_inc.root");
		//!TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_lcut.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_no_iso_lep.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/rootfile/rv01-16-p05_500.sv01-14-01-p00.mILD_o1_v05.E500-TDR_ws.I108675.P6f_yyxylv.eL.pR_dst_5709_00001-DST.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxyev_eLeR_new_lcut.root");
		TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxyev_eLeR_old_lcut.root");

		int bin_e = 30;
		int max_e = 1;
		
		TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
		
		TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
		cosReco->Sumw2();
		TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{b};Entries", bin_e,-1.0,max_e);
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

		int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
		int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");
		//int forward = GenTree->Draw("MCBcostheta >> cosGen","MCBcostheta > 0 && MCBcostheta > -2 ");
		//int backward = GenTree->Draw("MCBcostheta >> +cosGen","MCBcostheta < 0 && MCBcostheta > -2");
		
		
		///////////////
		// BASE CUTS //
		///////////////

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
		TCut cuts = rcTW + hadM + method7;

		TCut fcuts = "Top1costheta > 0" + cuts;
		TCut bcuts = "Top1costheta < 0" + cuts;

		// Top hadronic angle
		int recoforward = normaltree->Draw("-Top1costheta*Top2leptonCharge >> cosReco", fcuts);
		int recobackward = normaltree->Draw("-Top1costheta*Top2leptonCharge >> +cosReco", bcuts);

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

		cout << "rcf: " << recoforward << "rcb: " << recobackward << endl;


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

