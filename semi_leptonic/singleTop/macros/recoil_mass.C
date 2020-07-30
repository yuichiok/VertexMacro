#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

void recoil_mass()
{
	int token=0;

	bool twoDmode = 1;

	// set plot style

	if(!twoDmode) SetQQbarStyle();

	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 


	// File Selector

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record2.txt" );

	while( fs.input(in) ){
		rootfiles.push_back(fs);
	}

	int nrootfiles = 0;
	nrootfiles = rootfiles.size();
  
	cout << "nfiles = " << nrootfiles << endl;

	std::cout << "Choose a file from below:" << std::endl;
	for( int i=0; i < nrootfiles; i++){
		std::cout << i << ": " << rootfiles[i].info() << endl;
	}

	std::cout << "Enter code: ";
	std::cin >> token;
	std::cout << std::endl;

	std::string filename = rootfiles[token].filename();
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	TTree * Stats = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary = (TTree*) file->Get( "Summary" );

	// Histograms
	
	TH1F * histMCTopHadMass	= new TH1F("histMCTopHadMass",";Gen Top_{Had} Mass (GeV); Entries",200,100,300);
	histMCTopHadMass->Sumw2();
	TH1F * histMCTopLepMass	= new TH1F("histMCTopLepMass",";Gen Top_{Lep} Mass (GeV); Entries",200,100,300);
	histMCTopLepMass->Sumw2();

	TH1F * histRecoTopHadMass	= new TH1F("histRecoTopHadMass",";Reco Top_{Had} Mass (GeV); Entries",200,100,300);
	histRecoTopHadMass->Sumw2();
	TH1F * histRecoTopLepMass	= new TH1F("histRecoTopLepMass",";Reco Top_{Lep} Mass (GeV); Entries",200,100,300);
	histRecoTopLepMass->Sumw2();

	TH1F * histRecoMCHadMassDiff	= new TH1F("histRecoMCHadMassDiff",";Reco-Gen Top_{Had} Mass (GeV); Entries",200,-100,100);
	TH1F * histRecoMCLepMassDiff	= new TH1F("histRecoMCLepMassDiff",";Reco-Gen Top_{Lep} Mass (GeV); Entries",200,-100,100);


	TH2F * histTopHadMass	= new TH2F("histTopHadMass",";MC Top_{Had} Mass (GeV);Reco Top_{Had} Mass (GeV)",200,0,400,200,0,400);
	TH2F * histTopLepMass	= new TH2F("histTopLepMass",";MC Top_{Lep} Mass (GeV);Reco Top_{Lep} Mass (GeV)",200,0,400,200,0,400);

	TGaxis::SetMaxDigits(3);

	// Set variables

	int MCLeptonPDG=0;
	int singletopFlag=0;
	int methodUsed=0;
	int methodTaken[100];
	float MCTopmass=0, MCTopBarmass=0;
	float qMCcostheta[2];

	float 	Thrust=0,
	hadMass=0,
	Top1mass=0,
	Top2mass=0,
	W1mass=0,
	Top1bmomentum=0,
	Top2bmomentum=0,
	Top1gamma=0,
	Top2gamma=0;


	// Set Branch Adress

	// Generator Info

	Stats->SetBranchAddress("MCLeptonPDG", &MCLeptonPDG);
	Stats->SetBranchAddress("qMCcostheta", qMCcostheta);
	Stats->SetBranchAddress("MCTopmass", &MCTopmass);
	Stats->SetBranchAddress("MCTopBarmass", &MCTopBarmass);
	Stats->SetBranchAddress("singletopFlag", &singletopFlag);
	Stats->SetBranchAddress("methodTaken", methodTaken);
	Stats->SetBranchAddress("methodUsed", &methodUsed);

	//　Reconstructed Info

	Stats->SetBranchAddress("Thrust", &Thrust);
	Stats->SetBranchAddress("hadMass", &hadMass);
	Stats->SetBranchAddress("Top1mass", &Top1mass);
	Stats->SetBranchAddress("Top2mass", &Top2mass);
	Stats->SetBranchAddress("W1mass", &W1mass);
	Stats->SetBranchAddress("Top1bmomentum", &Top1bmomentum);
	Stats->SetBranchAddress("Top2bmomentum", &Top2bmomentum);
	Stats->SetBranchAddress("Top1gamma", &Top1gamma);
	Stats->SetBranchAddress("Top2gamma", &Top2gamma);


	// Event Loop

	int entryStat = Stats->GetEntries();

	for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		Stats->GetEntry(iStatEntry);



		bool qMCCheck1 = false;
		bool qMCCheck2 = false;

		if(qMCcostheta[0] > -2 && qMCcostheta[0] < -0.9) qMCCheck1=true;
		if(qMCcostheta[1] > -2 && qMCcostheta[1] < -0.9) qMCCheck2=true;

		//if(qMCCheck1 && qMCCheck2){

			for (int i = 0; i < methodUsed; ++i)
			{

				if(methodTaken[i]==1){

					// Generated Level

					float MCTopHadMass = -1;
					float MCTopLepMass = -1;

					if(MCLeptonPDG < 0){
						MCTopHadMass = MCTopmass;
						MCTopLepMass = MCTopBarmass;
					}
					if(MCLeptonPDG > 0){
						MCTopHadMass = MCTopBarmass;
						MCTopLepMass = MCTopmass;
					}

					if(MCTopHadMass != -1) histMCTopHadMass->Fill(MCTopHadMass);
					if(MCTopLepMass != -1) histMCTopLepMass->Fill(MCTopLepMass);


					// Reconstructed Level

					histRecoTopHadMass->Fill(Top1mass);
					histRecoTopLepMass->Fill(Top2mass);

					histTopHadMass->Fill(MCTopHadMass,Top1mass);
					histTopLepMass->Fill(MCTopLepMass,Top2mass);

					// Reco MC Difference

					float HadDiff = Top1mass - MCTopHadMass;
					float LepDiff = Top2mass - MCTopLepMass;

					histRecoMCHadMassDiff->Fill(HadDiff);
					histRecoMCLepMassDiff->Fill(LepDiff);

				}

			}

		//}


/*

		if(Thrust<0.9){

			if(hadMass > 180 && hadMass < 420){

				if(Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50){

					if( (Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ){

						if(Top1bmomentum > 15 && Top2bmomentum > 15){

							for (int i = 0; i < methodUsed; ++i)
							{

								if(methodTaken[i]==1){

									bool qMCCheck1 = false;
									bool qMCCheck2 = false;

									if(qMCcostheta[0] > -2 && qMCcostheta[0] < -0.9) qMCCheck1=true;
									if(qMCcostheta[1] > -2 && qMCcostheta[1] < -0.9) qMCCheck2=true;

									//if(qMCCheck1 && qMCCheck2){

										// Generated Level

										float MCTopHadMass = -1;
										float MCTopLepMass = -1;

										if(MCLeptonPDG < 0){
											MCTopHadMass = MCTopmass;
											MCTopLepMass = MCTopBarmass;
										}
										if(MCLeptonPDG > 0){
											MCTopHadMass = MCTopBarmass;
											MCTopLepMass = MCTopmass;
										}

										if(MCTopHadMass != -1) histMCTopHadMass->Fill(MCTopHadMass);
										if(MCTopLepMass != -1) histMCTopLepMass->Fill(MCTopLepMass);


										// Reconstructed Level

										histRecoTopHadMass->Fill(Top1mass);
										histRecoTopLepMass->Fill(Top2mass);

										histTopHadMass->Fill(MCTopHadMass,Top1mass);
										histTopLepMass->Fill(MCTopLepMass,Top2mass);

										// Reco MC Difference

										float HadDiff = Top1mass - MCTopHadMass;
										float LepDiff = Top2mass - MCTopLepMass;

										histRecoMCHadMassDiff->Fill(HadDiff);
										histRecoMCLepMassDiff->Fill(LepDiff);

									//}

								}

							}


						}//pcut
					}//gcut
				}//rcTW cut
			}//hadM cut
		}//thrust cut

*/


	}// End of Event Loop

	
	// set margin sizes
	if (twoDmode){
		gStyle->SetPadTopMargin(0.1);
		gStyle->SetPadRightMargin(0.13);
		gStyle->SetPadBottomMargin(0.15);
		gStyle->SetPadLeftMargin(0.15);
	}


	// hist normalization

	histMCTopHadMass->Scale( 1 / histMCTopHadMass->GetEntries() );
	histMCTopLepMass->Scale( 1 / histMCTopLepMass->GetEntries() );
	histRecoTopHadMass->Scale( 1 / histRecoTopHadMass->GetEntries() );
	histRecoTopLepMass->Scale( 1 / histRecoTopLepMass->GetEntries() );


	// hist setting

	histMCTopHadMass->SetLineWidth(3);
	histMCTopHadMass->SetLineStyle(1);
	histMCTopHadMass->SetLineColor(kGray+1);

	histRecoTopHadMass->SetLineWidth(3);
	histRecoTopHadMass->SetLineStyle(1);

	histMCTopLepMass->SetLineWidth(3);
	histMCTopLepMass->SetLineStyle(1);
	histMCTopLepMass->SetLineColor(kGray+1);

	histRecoTopLepMass->SetLineWidth(3);
	histRecoTopLepMass->SetLineStyle(1);

	TCanvas * c1	= new TCanvas("c1", "DataMC",0,0,1000,500);
	c1->Divide(2,1);

	c1->cd(1);
	histMCTopHadMass->Draw("he");
	histRecoTopHadMass->Draw("hsame");

	c1->cd(2);
	histMCTopLepMass->Draw("he");
	histRecoTopLepMass->Draw("hsame");


	/*
	c1->Divide(2,2);

	c1->cd(1);
	histMCTopHadMass->Draw("he");

	c1->cd(2);
	histMCTopLepMass->Draw("he");

	c1->cd(3);
	histRecoTopHadMass->Draw("he");

	c1->cd(4);
	histRecoTopLepMass->Draw("he");
	*/


	TCanvas * c2	= new TCanvas("c2", "DataMC2",0,0,1000,500);
	c2->Divide(2,1);

	histTopHadMass->GetXaxis()->SetTitleOffset(1.7);
	histTopHadMass->GetYaxis()->SetTitleOffset(1.7);

	histTopLepMass->GetXaxis()->SetTitleOffset(1.7);
	histTopLepMass->GetYaxis()->SetTitleOffset(1.7);


	c2->cd(1);
	histTopHadMass->Draw("COLZ");

	c2->cd(2);
	histTopLepMass->Draw("COLZ");
	

	TCanvas * c3	= new TCanvas("c3", "DataMC3",0,0,1000,500);
	c3->Divide(2,1);

	c3->cd(1);
	histRecoMCHadMassDiff->Draw("he");

	c3->cd(2);
	histRecoMCLepMassDiff->Draw("he");






















}

