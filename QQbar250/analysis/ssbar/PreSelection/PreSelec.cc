#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define PreSelec_cxx
#include "PreSelec.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>

void PreSelec::PreSelection(int n_entries=-1, float MINP_CUT=10.0, TString process="test", TString fileout="out")
{

	float MAXP_CUT=60.0;

	// Number Counting
	TH1I* cnt_nevents   = new TH1I("h_cnt_nevents",";nevents;Entries",10,0,10);
	TH1I* cnt_ISRevents = new TH1I("h_cnt_ISRevents",";isr events;Entries",10,0,10);

	_h0_counter.push_back(cnt_nevents);
	_h0_counter.push_back(cnt_ISRevents);

	// MC Histograms

	TString name_mc_stable = "h_mc_stable_";
	TString name_mc 	   = "h_mc_";

	// TH1F
	TH1F* h_mc_qq_TotE = new TH1F(name_mc+"qq_TotE", ";MC QQ Energy (GeV);", 260, 0, 260);
	TH1F* h_mc_qq_InvM = new TH1F(name_mc+"qq_InvM", ";MC Inv. Mass (GeV);", 260, 0, 260);

	TH1F* h_mc_ISR_TotE = new TH1F(name_mc+"ISR_TotE", ";MC ISR Energy (GeV);", 260, 0, 260);

	_h1_mc_stable.push_back( h_mc_qq_TotE );
	_h1_mc_stable.push_back( h_mc_qq_InvM );

	_h1_mc_stable.push_back( h_mc_ISR_TotE );

	// TH2F



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F
	TH1F* h_pfo_visE     = new TH1F(name_pfo+"visE", ";Total Visible Energy (GeV);", 260, 0, 260);
	TH1F* h_pfo_visE_all = new TH1F(name_pfo+"visE_all", ";Total Visible Energy (GeV);", 260, 0, 260);
	TH1F* h_pfo_gammaE   = new TH1F(name_pfo+"gammaE", ";Total Visible Energy (GeV);", 260, 0, 260);
	TH1F* h_pfo_sigE   = new TH1F(name_pfo+"sigE", ";Total Signal Energy (GeV);", 260, 0, 260);

	TH1F* h_pfo_jet_mult = new TH1F(name_pfo+"jet_mult", ";Jet Mult;", 60,0,60);
	TH1F* h_pfo_jet_ISR_mult = new TH1F(name_pfo+"jet_ISR_mult", ";Jet ISR Mult;", 60,0,60);
	TH1F* h_pfo_jet_NonISR_mult = new TH1F(name_pfo+"jet_NonISR_mult", ";Jet NonISR Mult;", 60,0,60);

	TH1F* h_pfo_phjet_E   = new TH1F(name_pfo+"phjet_E", ";Photon Jet Energy (GeV);", 260, 0, 260);
	TH1F* h_pfo_phjet_ISR_E   = new TH1F(name_pfo+"phjet_ISR_E", ";Photon Jet ISR Energy (GeV);", 260, 0, 260);
	TH1F* h_pfo_phjet_NonISR_E   = new TH1F(name_pfo+"phjet_NonISR_E", ";Photon Jet NonISR Energy (GeV);", 260, 0, 260);

	TH1F* h_pfo_phjet_cos   = new TH1F(name_pfo+"phjet_cos", ";Photon Jet |cos#theta|;", 50, 0, 1);
	TH1F* h_pfo_phjet_ISR_cos   = new TH1F(name_pfo+"phjet_ISR_cos", ";Photon Jet ISR |cos#theta|;", 50, 0, 1);
	TH1F* h_pfo_phjet_NonISR_cos   = new TH1F(name_pfo+"phjet_NonISR_cos", ";Photon Jet NonISR |cos#theta|;", 50, 0, 1);

	TH1F* h_pfo_jet_TotE = new TH1F(name_pfo+"jet_TotE", ";Di-jet Energy (GeV);", 260, 0, 260);
	TH1F* h_pfo_jet_InvM = new TH1F(name_pfo+"jet_InvM", ";Di-jet Inv. Mass (GeV);", 260, 0, 260);

	_h1_pfo.push_back( h_pfo_visE );
	_h1_pfo.push_back( h_pfo_visE_all );
	_h1_pfo.push_back( h_pfo_gammaE );

	_h1_pfo.push_back( h_pfo_jet_mult );
	_h1_pfo.push_back( h_pfo_jet_ISR_mult );
	_h1_pfo.push_back( h_pfo_jet_NonISR_mult );

	_h1_pfo.push_back( h_pfo_phjet_E );
	_h1_pfo.push_back( h_pfo_phjet_ISR_E );
	_h1_pfo.push_back( h_pfo_phjet_NonISR_E );

	_h1_pfo.push_back( h_pfo_phjet_cos );
	_h1_pfo.push_back( h_pfo_phjet_ISR_cos );
	_h1_pfo.push_back( h_pfo_phjet_NonISR_cos );

	_h1_pfo.push_back( h_pfo_jet_TotE );
	_h1_pfo.push_back( h_pfo_jet_InvM );


	// TH2F




	std::stringstream stream_min;
	std::stringstream stream_max;
	stream_min << std::fixed << std::setprecision(0) << MINP_CUT;
	stream_max << std::fixed << std::setprecision(0) << MAXP_CUT;
	TString minp_it = stream_min.str();
	TString maxp_it = stream_max.str();
	cout << "MINP = " << minp_it << endl;
	cout << "MAXP = " << maxp_it << endl;

	process = process;

	TString filename_out_root = fileout;
	TString filename_out = "test";

	// test mode
	bool debug = 0;
	if(debug) filename_out_root = "rootfiles/double_tag/test.root";



	TFile *MyFile = new TFile(filename_out_root,"RECREATE");

	MyFile->cd();

	TString tmp_str  = "data/" + filename_out + ".txt";
	TString tmp_str2 = "data/" + filename_out + ".true.txt";
	ofstream LeadKDataFile (tmp_str.Data());
	ofstream TrueDataFile  (tmp_str2.Data());

	if (fChain == 0) return;

	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////


	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		if(process=="uds" && (fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) ) continue; // ignore MC b/c quarks
		if(process=="uu"  && fabs(mc_quark_pdg[0])!=2) continue; // ignore MC other than uu
		if(process=="ss"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss
		if(process=="dd"  && fabs(mc_quark_pdg[0])!=1) continue; // ignore MC other than dd
		if(process=="default"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss


		////////////////////////////////
		//////   MC QQ ANALYSIS   //////
		////////////////////////////////

		std::vector<VecOP> qqVecs;
		float mc_InvM[2] = {-1,-1};

		for(int iqq=0; iqq < 2; iqq++){

			VecOP qqVec(mc_quark_px[iqq],mc_quark_py[iqq],mc_quark_pz[iqq]);
			qqVecs.push_back(qqVec);

		}

		VecOP qqAddVec = VecOP::AddVec(qqVecs.at(0),qqVecs.at(1));

		float mc_qq_E 	 = mc_quark_E[0] + mc_quark_E[1];
		float mc_qq_InvM = GetInvMass(mc_qq_E,qqAddVec.GetMomentum3());

		h_mc_qq_TotE->Fill(mc_qq_E);
		h_mc_qq_InvM->Fill(mc_qq_InvM);


		////////////////////////////////
		/////   MC ISR ANALYSIS   //////
		////////////////////////////////

		std::vector<VecOP> qqISRVecs;
		float mc_ISR_InvM[2] = {-1,-1};

		for(int isr=0; isr < 2; isr++){

			VecOP qqISRVec(mc_ISR_px[isr],mc_ISR_py[isr],mc_ISR_pz[isr]);
			qqISRVecs.push_back(qqISRVec);

		}

		VecOP qqISRAddVec = VecOP::AddVec(qqISRVecs.at(0),qqISRVecs.at(1));

		float gamma_E 	  = mc_ISR_E[0] + mc_ISR_E[1];
		h_mc_ISR_TotE->Fill(gamma_E);


		///////////////////////////////
		//////   Jet ANALYSIS   ///////
		///////////////////////////////
		
		std::vector<VecOP> jetVecs;
		float jet_InvM[2] = {-1,-1};
		bool  jet_E_check = (jet_E[0]<0.5 || jet_E[1]<0.5) ? false : true;

		for (int ijet = 0; ijet < 2; ++ijet){

			VecOP jetVec(jet_px[ijet],jet_py[ijet],jet_pz[ijet]);
			jetVecs.push_back(jetVec);

			jet_InvM[ijet] = GetInvMass(jet_E[ijet],jetVec.GetMomentum3());
		
		} // end of jet

		VecOP dijetVec   = VecOP::AddVec(jetVecs.at(0),jetVecs.at(1));

		float dijet_E 	 = jet_E[0] + jet_E[1];
		float dijet_InvM = GetInvMass(dijet_E,dijetVec.GetMomentum3());

		if(jet_E_check){
			h_pfo_jet_TotE->Fill(dijet_E);
			h_pfo_jet_InvM->Fill(dijet_InvM);
		}


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		float visE     = 0;
		float visE_all = 0;
		std::vector<VecOP> pfoVecs;
		VecOP LPFOVecs[2];

		int jet_mult[2] = {0};
		float phjet_E[2] = {0};

		// Leading PFO variables
		int   lead_ipfo[2]	= {-1,-1};
		float maxP[2]		= {0};

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			visE_all += pfo_E[ipfo];

			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float mom    = pfoVec.GetMomentum();

		    if(pfo_match[ipfo]<0) continue;
		    // if(pfo_E[ipfo]<1) continue;
		    if(pfo_match[ipfo]>1) continue;

			visE += pfo_E[ipfo];

			// Jet Analysis

			// jet multiplicity
			jet_mult[pfo_match[ipfo]]++;


			// photon jet
			if( pfo_type[ipfo]==22  || fabs(pfo_type[ipfo])==2112 ) {

				phjet_E[pfo_match[ipfo]] += pfo_E[ipfo];

			}

			// Leading PFO

			// ID leading particle
			if(mom > maxP[pfo_match[ipfo]]){

				maxP[pfo_match[ipfo]] = mom;
				lead_ipfo[pfo_match[ipfo]] = ipfo;
				LPFOVecs[pfo_match[ipfo]] = pfoVec;
			
			}


		} // end of pfo


		// LPFO parameters

		float LPFO_cos[2] = {-1,-1};

		for (int i = 0; i < 2; ++i)
		{
			LPFO_cos[i] = abs(cos(LPFOVecs[i].CalculateAngles().at(1)));
		}




		h_pfo_visE->Fill(visE);
		h_pfo_visE_all->Fill(visE_all);

		for (int i = 0; i < 2; ++i)
		{
			h_pfo_jet_mult->Fill(jet_mult[i]);
			h_pfo_phjet_E->Fill(phjet_E[i]);
			h_pfo_phjet_cos->Fill(LPFO_cos[i]);
		}

		// for true isr bothered event
		if(35 < gamma_E){ // ISR

			h_pfo_gammaE->Fill(visE);
		
			for (int i = 0; i < 2; ++i)
			{
				h_pfo_jet_ISR_mult->Fill(jet_mult[i]);
				h_pfo_phjet_ISR_E->Fill(phjet_E[i]);
				h_pfo_phjet_ISR_cos->Fill(LPFO_cos[i]);
			}

		}else{ // signal

			h_pfo_sigE->Fill(visE);

			for (int i = 0; i < 2; ++i)
			{
				h_pfo_jet_NonISR_mult->Fill(jet_mult[i]);
				h_pfo_phjet_NonISR_E->Fill(phjet_E[i]);
				h_pfo_phjet_NonISR_cos->Fill(LPFO_cos[i]);
			}

		}

		// printf("visE_all = %4.3f, visE = %4.3f\n", visE_all, visE);


		////////////////////////////////
		/////   FIND ISR PHOTONS   /////
		////////////////////////////////

		// for(int ipfo=0; ipfo<pfo_n; ipfo++) {


		// 	VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
		// 	float mom    = pfoVec.GetMomentum();






		// }

























	} // end of event loop

	// printResults();

	for(int h=0; h < _h0_counter.size(); h++) _h0_counter.at(h)->Write();

	for(int h=0; h < _h1_mc_stable.size(); h++) _h1_mc_stable.at(h)->Write();
	for(int h=0; h < _h2_mc_stable.size(); h++) _h2_mc_stable.at(h)->Write();

	for(int h=0; h < _h1_pfo.size(); h++) _h1_pfo.at(h)->Write();
	for(int h=0; h < _h2_pfo.size(); h++) _h2_pfo.at(h)->Write();

	LeadKDataFile.close();
	TrueDataFile.close();


}

float PreSelec::GetInvMass(float E=0, vector<float> p3 = {}){

	float p32 = 0;
	for (int i = 0; i < 3; ++i)
	{
		p32 += p3.at(i)*p3.at(i);
	}

	float InvM = sqrt( E*E - p32 );
	return InvM;

}

void PreSelec::printResults(){

	cout << "print event result" << endl;


}