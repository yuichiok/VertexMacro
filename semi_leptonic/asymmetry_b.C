
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void asymmetry_b()
{
		//TFile * file = TFile::Open(filename.c_str());
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_inc.root");
		TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_iso_lep_lcut.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/root_merge/leptonic_yyxylv_eLeR_no_iso_lep.root");
		//TFile * file = TFile::Open("/home/ilc/yokugawa/run/rootfile/rv01-16-p05_500.sv01-14-01-p00.mILD_o1_v05.E500-TDR_ws.I108675.P6f_yyxylv.eL.pR_dst_5709_00001-DST.root");

		int bin_e = 30;
		int max_e = 1;
		//if (!c1) 
		//{
		TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
		//}
		//c1->Divide(2,1);
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

		//int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && abs(MCBcostheta) < 0.95");
		//int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && abs(MCBcostheta) < 0.95");
		int forward = normaltree->Draw("qMCBcostheta >> cosGen","qMCBcostheta > 0 && qMCBcostheta > -2 ");
		int backward = normaltree->Draw("qMCBcostheta >> +cosGen","qMCBcostheta < 0 && qMCBcostheta > -2");
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

		//cuts
		///////////////
		// BASE CUTS //
		///////////////

		TCut cuts = " hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.8 || Top2btag > 0.3)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";

		// **** Full cuts ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ((methodTaken == 1 && Top1btag > 0.8 && Top2btag > 0.8 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 1 )";

		// **** Test ****
		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((methodTaken == 1 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 2 )";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4)";

		//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ( methodTaken >= 1 )";



		//string fcuts = "qCostheta > 0" + cuts;
		//string bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;
		//int recoforward = normaltree->Draw("qCostheta >> cosReco", fcuts.c_str());
		//int recobackward = normaltree->Draw("qCostheta >> +cosReco", bcuts.c_str());


		//string fcuts = "qBCostheta > 0" + cuts;
		//string bcuts = "qBCostheta < 0 && qBCostheta > -1.0 " + cuts;

		//int recoforward = normaltree->Draw("qBCostheta >> cosReco", fcuts.c_str());
		//int recobackward = normaltree->Draw("qBCostheta >> +cosReco", bcuts.c_str());

		int entry = normaltree->GetEntries();
		float hadMass, Top1mass, W1mass, Top1btag, Top2btag, Top1gamma, Top2gamma, Top1bmomentum, Top2bmomentum;
		int methodTaken[12];

		int nevt, Top1bcharge;
		float Top1bcostheta;

		int recoforward=0, recobackward=0;


		normaltree->SetBranchAddress("hadMass", &hadMass) ;
		normaltree->SetBranchAddress("Top1mass", &Top1mass) ;
		normaltree->SetBranchAddress("W1mass", &W1mass) ;
		normaltree->SetBranchAddress("Top1btag", &Top1btag) ;
		normaltree->SetBranchAddress("Top2btag", &Top2btag) ;
		normaltree->SetBranchAddress("Top1gamma", &Top1gamma) ;
		normaltree->SetBranchAddress("Top2gamma", &Top2gamma) ;
		normaltree->SetBranchAddress("Top1bmomentum", &Top1bmomentum) ;
		normaltree->SetBranchAddress("Top2bmomentum", &Top2bmomentum) ;
		normaltree->SetBranchAddress("methodTaken", methodTaken) ;

		normaltree->SetBranchAddress("Top1bcharge", &Top1bcharge) ;
		normaltree->SetBranchAddress("Top1bcostheta", &Top1bcostheta) ;

		int testInt = 0;

		TEventList *elist1 = new TEventList( "elist1", "Reconstructed Event List" ) ;
		normaltree->Draw( ">>elist1", cuts ) ;

		for(int i=0; i<entry; i++){

				normaltree->GetEntry( elist1->GetEntry(i) ) ;

				testInt++;

				if(Top1bcharge < 0 && Top1bcostheta > 0){
						cosReco->Fill(Top1bcostheta);
						recoforward++;
				}else if(Top1bcharge > 0 && Top1bcostheta < 0 && Top1bcostheta > -1){
						cosReco->Fill(-Top1bcostheta);
						recobackward++;
				}

		}

		cout << "testInt = " << testInt << endl;

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

		cout << "afbgen = " << afbgen << endl;
		cout << "forward = " << forward << endl;
		cout << "backward = " << backward << endl;

		cout << "recoforward = " << recoforward << endl;
		cout << "recobackward = " << recobackward << endl;

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

