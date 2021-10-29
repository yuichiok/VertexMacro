#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define dEdx_dist_cxx
#include "dEdx_dist.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>

// see math/mathcore/src/PdfFuncMathCore.cxx in ROOT 6.x
double crystalball_function(double x, double alpha, double n, double sigma, double mean) {
  // evaluate the crystal ball function
  if (sigma < 0.)     return 0.;
  double z = (x - mean)/sigma; 
  if (alpha < 0) z = -z; 
  double abs_alpha = std::abs(alpha);
  // double C = n/abs_alpha * 1./(n-1.) * std::exp(-alpha*alpha/2.);
  // double D = std::sqrt(M_PI/2.)*(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
  // double N = 1./(sigma*(C+D));
  if (z  > - abs_alpha)
    return std::exp(- 0.5 * z * z);
  else {
    //double A = std::pow(n/abs_alpha,n) * std::exp(-0.5*abs_alpha*abs_alpha);
    double nDivAlpha = n/abs_alpha;
    double AA =  std::exp(-0.5*abs_alpha*abs_alpha);
    double B = nDivAlpha -abs_alpha;
    double arg = nDivAlpha/(B-z);
    return AA * std::pow(arg,n);
  }
}

double crystalball_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}

void dEdx_dist::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void dEdx_dist::Analyze_dEdxdist(int n_entries=-1, float MINP_CUT=10.0, TString output="test")
{

	float MAXP_CUT=60.0;

	// MC Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	TH1F* mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* mc_qq_cos  = new TH1F("h_mc_quark_cos",";cos#theta; Entries",100,-1.0,1.0);

	h1_mc_stable.push_back( mc_nk_evt );
	h1_mc_stable.push_back( mc_qq_cos );

	// TH2F



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F

	// vertex position
  TH1F * pfo_pv_kaon     = new TH1F(name_pfo+"pv_kaon", "pv_kaon", 40, 0, 4.0);
  TH1F * pfo_pv_pion     = new TH1F(name_pfo+"pv_pion", "pv_pion", 40, 0, 4.0);
  TH1F * pfo_pv_proton   = new TH1F(name_pfo+"pv_proton", "pv_proton", 40, 0, 4.0);

  // dEdx distance from kaon bethe-bloch
  TH1F * pfo_kdEdx_dist_kaon     = new TH1F(name_pfo+"kdEdx_dist_kaon", "kdEdx_dist_kaon", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_proton   = new TH1F(name_pfo+"kdEdx_dist_proton", "kdEdx_dist_proton", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_pion     = new TH1F(name_pfo+"kdEdx_dist_pion", "kdEdx_dist_pion", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_electron = new TH1F(name_pfo+"kdEdx_dist_electron", "kdEdx_dist_electron", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_muon     = new TH1F(name_pfo+"kdEdx_dist_muon", "kdEdx_dist_muon", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_others   = new TH1F(name_pfo+"kdEdx_dist_others", "kdEdx_dist_others", 40, -10, 10);

  // dEdx distance from pion bethe-bloch
  TH1F * pfo_pidEdx_dist_kaon     = new TH1F(name_pfo+"pidEdx_dist_kaon", "pidEdx_dist_kaon", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_proton   = new TH1F(name_pfo+"pidEdx_dist_proton", "pidEdx_dist_proton", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_pion     = new TH1F(name_pfo+"pidEdx_dist_pion", "pidEdx_dist_pion", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_electron = new TH1F(name_pfo+"pidEdx_dist_electron", "pidEdx_dist_electron", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_muon     = new TH1F(name_pfo+"pidEdx_dist_muon", "pidEdx_dist_muon", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_others   = new TH1F(name_pfo+"pidEdx_dist_others", "pidEdx_dist_others", 40, -10, 10);

  // dEdx distance from proton bethe-bloch
  TH1F * pfo_pdEdx_dist_kaon     = new TH1F(name_pfo+"pdEdx_dist_kaon", "pdEdx_dist_kaon", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_proton   = new TH1F(name_pfo+"pdEdx_dist_proton", "pdEdx_dist_proton", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_pion     = new TH1F(name_pfo+"pdEdx_dist_pion", "pdEdx_dist_pion", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_electron = new TH1F(name_pfo+"pdEdx_dist_electron", "pdEdx_dist_electron", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_muon     = new TH1F(name_pfo+"pdEdx_dist_muon", "pdEdx_dist_muon", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_others   = new TH1F(name_pfo+"pdEdx_dist_others", "pdEdx_dist_others", 40, -10, 10);

  // Kaon polar angle
	TH1F* pfo_LeadK_qcos			= new TH1F(name_pfo+"LeadKaons_cos",";cos#theta; Events",100,-1.0,1.0);


  // push_back hists
  h1_pfo.push_back( pfo_pv_kaon );
  h1_pfo.push_back( pfo_pv_pion );
  h1_pfo.push_back( pfo_pv_proton );

	h1_pfo.push_back( pfo_kdEdx_dist_kaon );
	h1_pfo.push_back( pfo_kdEdx_dist_proton );
	h1_pfo.push_back( pfo_kdEdx_dist_pion );
	h1_pfo.push_back( pfo_kdEdx_dist_electron );
	h1_pfo.push_back( pfo_kdEdx_dist_muon );
	h1_pfo.push_back( pfo_kdEdx_dist_others );

	h1_pfo.push_back( pfo_pidEdx_dist_kaon );
	h1_pfo.push_back( pfo_pidEdx_dist_proton );
	h1_pfo.push_back( pfo_pidEdx_dist_pion );
	h1_pfo.push_back( pfo_pidEdx_dist_electron );
	h1_pfo.push_back( pfo_pidEdx_dist_muon );
	h1_pfo.push_back( pfo_pidEdx_dist_others );

	h1_pfo.push_back( pfo_pdEdx_dist_kaon );
	h1_pfo.push_back( pfo_pdEdx_dist_proton );
	h1_pfo.push_back( pfo_pdEdx_dist_pion );
	h1_pfo.push_back( pfo_pdEdx_dist_electron );
	h1_pfo.push_back( pfo_pdEdx_dist_muon );
	h1_pfo.push_back( pfo_pdEdx_dist_others );

	h1_pfo.push_back( pfo_LeadK_qcos );

	// TH2F
  TH2F * pfo_p_kdEdx_dist_kaon 			= new TH2F(name_pfo+"p_kdEdx_dist_kaon", "p_kdEdx_dist_kaon", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_proton 		= new TH2F(name_pfo+"p_kdEdx_dist_proton", "p_kdEdx_dist_proton", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_pion 			= new TH2F(name_pfo+"p_kdEdx_dist_pion", "p_kdEdx_dist_pion", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_electron  = new TH2F(name_pfo+"p_kdEdx_dist_electron", "p_kdEdx_dist_electron", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_muon 			= new TH2F(name_pfo+"p_kdEdx_dist_muon", "p_kdEdx_dist_muon", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_others 		= new TH2F(name_pfo+"p_kdEdx_dist_others", "p_kdEdx_dist_others", 100, 0.5, 100.5, 40, -10, 10);

  // push_back hists
  h2_pfo.push_back( pfo_p_kdEdx_dist_kaon );
  h2_pfo.push_back( pfo_p_kdEdx_dist_proton );
  h2_pfo.push_back( pfo_p_kdEdx_dist_pion );
  h2_pfo.push_back( pfo_p_kdEdx_dist_electron );
  h2_pfo.push_back( pfo_p_kdEdx_dist_muon );
  h2_pfo.push_back( pfo_p_kdEdx_dist_others );


	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << MINP_CUT;
	TString minp_it = stream.str();
	cout << "MINP = " << MINP_CUT << endl;
	process = output;

	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.root",output.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.400.pISR.root",output.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.400.minp%s.root",output.Data(),minp_it.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.kpkm.400.minp%s.root",output.Data(),minp_it.Data()),"RECREATE");

	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.kpkm.pvcut.minp%s.root",output.Data(),minp_it.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.kpkm.minp%s.root",output.Data(),minp_it.Data()),"RECREATE");

	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.minp%s.distcut.root",output.Data(),minp_it.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.minp%s.distcut.kid.root",output.Data(),minp_it.Data()),"RECREATE");
	TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.minp%s.distcut.polar.root",output.Data(),minp_it.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.minp%s.maxp60.distcut.polar.root",output.Data(),minp_it.Data()),"RECREATE");

	// TFile *MyFile = new TFile("test.root","RECREATE");

	MyFile->cd();


	TString tmp_str  = TString::Format("data/DQ_250GeV_%s.minp%s.distcut.polar.data",output.Data(),minp_it.Data());
	TString tmp_str2 = TString::Format("data/DQ_250GeV_%s.minp%s.distcut.polar.true.data",output.Data(),minp_it.Data());
	ofstream LeadKDataFile (tmp_str.Data());
	ofstream TrueDataFile  (tmp_str2.Data());

	if (fChain == 0) return;



	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////

	// const float MINP_CUT = 10.;

	// pdg ratio
	int kaon_dEdx_cheat_same0 = 0;
	int kaon_dEdx_cheat_same1 = 0;
	int kaon_dEdx_cheat_all  = 0;


	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// trial
		// if(jentry>100000) break;
		// if(jentry>1000) break;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		// Progress bar
		// if ( jentry > 10000 && jentry % 10000 == 0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

		// Comment on batch mode
		// printProgress( static_cast<double>(jentry) / (double)(1.0 * nentries) );


		if(output=="uds" && (fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) ) continue; // ignore MC b/c quarks
		if(output=="uu"  && fabs(mc_quark_pdg[0])!=2) continue; // ignore MC other than uu
		if(output=="ss"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss
		if(output=="dd"  && fabs(mc_quark_pdg[0])!=1) continue; // ignore MC other than dd
		if(output=="default"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss

		// if(mc_ISR_E[0] + mc_ISR_E[1]>35) continue; 


		nevents++;


		////////////////////////////////
		//////   MC QQ ANALYSIS   //////
		////////////////////////////////

		std::vector<VecOP> qqVecs;

		for(int iqq=0; iqq < 2; iqq++){

			VecOP qqVec(mc_quark_px[iqq],mc_quark_py[iqq],mc_quark_pz[iqq]);
			qqVecs.push_back(qqVec);

		}

		// Cut qq with qq separation
		float qqsep = VecOP::getAngleBtw(qqVecs.at(0).GetMomentum3(),qqVecs.at(1).GetMomentum3());


		// ISR protection
		if(abs(cos(qqsep)) < 0.95) continue;

		if( qqVecs.at(0).GetMomentum() < 120 || qqVecs.at(0).GetMomentum() > 127 ) continue;
		if( qqVecs.at(1).GetMomentum() < 120 || qqVecs.at(1).GetMomentum() > 127 ) continue;

		nevents_after_preselec++;

		for(int iqq=0; iqq < 2; iqq++){

			float cos 	 = qqVecs.at(iqq).GetCostheta();
			float charge = mc_quark_charge[iqq];
			float QQqCos = (charge < 0)? cos: -cos;

			mc_qq_cos->Fill(QQqCos);

		}


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		// Compare qqbar
		int qq_match = -1;
		int qq_match_count[2] = {0};

		// Jet variables
		float jet_pt[2]       = {0};
		float jet_ThrustPz[2] = {0};
		float jet_qp[2]       = {0};
		float jet_charge[2]   = {-100};
		int   jet_mult[2]     = {0};
		int   jet_k_mult[2]   = {0};

		// Leading PFO variables
		float maxP[2] 			     = {0};
		int   lead_ipfo[2] 	     = {-1};

		VecOP thrustVec(principle_thrust_axis[0],principle_thrust_axis[1],principle_thrust_axis[2]);

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float abscos = abs( pfoVec.GetCostheta() );
			float cos    = pfoVec.GetCostheta();
			float mom    = pfoVec.GetMomentum();
			std::vector<float> mom3   = pfoVec.GetMomentum3();
			float ThrustPz     = pfoVec.GetThrustPz(thrustVec.GetMomentum3());
			// float pt     = pfoVec.GetPT();
			float charge = pfo_charge[ipfo];


			// if(pfo_match[ipfo]<0) continue;
			// if(mom < MINP_CUT) continue;
			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;


			// This compares pfo angle with MC angle -> giving which this pfo are from. 
			// 0: PFO is from q
			// 1: PFO is from qbar

			float q_pfo_sep    = VecOP::getAngleBtw(pfoVec.GetMomentum3(),qqVecs.at(0).GetMomentum3());
			float qbar_pfo_sep = VecOP::getAngleBtw(pfoVec.GetMomentum3(),qqVecs.at(1).GetMomentum3());

			qq_match = (q_pfo_sep < qbar_pfo_sep) ? 0 : 1;

			qq_match_count[qq_match]++;

			// Jet Analysis
			
			for (int imatch = 0; imatch < 2; ++imatch)
			{
				if(pfo_match[ipfo]==imatch){

					if(mom > maxP[imatch]){
						maxP[imatch] = mom;
						lead_ipfo[imatch] = ipfo;
					}

				} // end jet imatch
			} // end imatch


		} // end of pfo


		///////////////////////////////
		//////   Jet ANALYSIS   ///////
		///////////////////////////////
		
		std::vector<VecOP> jetVecs;

		for (int ijet = 0; ijet < 2; ++ijet){
		
			VecOP jetVec(jet_px[ijet],jet_py[ijet],jet_pz[ijet]);
			jetVecs.push_back(jetVec);
		
		}


		///////////////////////////////////////
		//////   Leading PFOs ANALYSIS   //////
		///////////////////////////////////////

		float lead_dedx[2]			  = {0};
		float lead_kdEdx_dist[2]  = {0};
		float lead_pdEdx_dist[2]  = {0};
		float lead_pidEdx_dist[2] = {0};

		float lead_mom[2]				 = {0};
		float lead_cos[2] 	     = {-2};
		float lead_qcos[2] 	     = {-2};
		float lead_chg[2]  			 = {0};
		float lead_pv[2]				 = {0};
		lead_chg[0] = pfo_charge[lead_ipfo[0]];
		lead_chg[1] = pfo_charge[lead_ipfo[1]];

		bool kchg_configs[4] = {0};
		kchg_configs[0] = ( (lead_chg[0]<0) && (lead_chg[1]>0) ) ? true : false;
		kchg_configs[1] = ( (lead_chg[0]>0) && (lead_chg[1]<0) ) ? true : false;
		kchg_configs[2] = ( (lead_chg[0]>0) && (lead_chg[1]>0) ) ? true : false;
		kchg_configs[3] = ( (lead_chg[0]<0) && (lead_chg[1]<0) ) ? true : false;

		int   lead_pdg_cheat[2]	 = {0};


		if(kchg_configs[0] || kchg_configs[1]){

			for (int i = 0; i < 2; ++i){

				if(lead_ipfo[i]==-1) continue;

				VecOP lead_pfoVec(pfo_px[lead_ipfo[i]],pfo_py[lead_ipfo[i]],pfo_pz[lead_ipfo[i]]);

				lead_dedx[i]				= pfo_dedx[lead_ipfo[i]];
				lead_kdEdx_dist[i]  = pfo_piddedx_k_dedxdist[lead_ipfo[i]];
				lead_pdEdx_dist[i]  = pfo_piddedx_p_dedxdist[lead_ipfo[i]];
				lead_pidEdx_dist[i] = pfo_piddedx_pi_dedxdist[lead_ipfo[i]];

				lead_mom[i] = lead_pfoVec.GetMomentum();
				lead_cos[i]	= lead_pfoVec.GetCostheta();
				lead_qcos[i] = (lead_chg[i] < 0)? lead_cos[i]: -lead_cos[i];
				lead_pv[i]  = sqrt(pfo_d0[lead_ipfo[i]]*pfo_d0[lead_ipfo[i]] + pfo_z0[lead_ipfo[i]]*pfo_z0[lead_ipfo[i]]);
				// lead_chg[i] = pfo_charge[lead_ipfo[i]];

				lead_pdg_cheat[i] = pfo_pdgcheat[lead_ipfo[i]];


	      bool nhits_bool = false;
	      if (fabs(lead_cos[i]) < 0.75 && pfo_tpc_hits[lead_ipfo[i]] > 210) nhits_bool = true;
	      if (fabs(lead_cos[i]) > 0.75 && fabs(lead_cos[i]) < 0.9 && pfo_tpc_hits[lead_ipfo[i]] > (210 + (210 - 50) * (fabs(lead_cos[i]) - 0.75) / (0.75 - 0.9))) nhits_bool = true;
	      if (fabs(lead_cos[i]) > 0.9  && pfo_tpc_hits[lead_ipfo[i]] > 50) nhits_bool = true;


	      if(lead_mom[i] < MINP_CUT) continue;

	      if(!nhits_bool) continue;
	      if(lead_pv[i]>1.0) continue;
	      if(abs(lead_kdEdx_dist[i]) > abs(lead_pdEdx_dist[i])) continue;
	      if(abs(lead_kdEdx_dist[i]) > abs(lead_pidEdx_dist[i])) continue;

	      float min_dist=-1.5;
	      float max_dist=0.5;

	      if(lead_kdEdx_dist[i]<min_dist||lead_kdEdx_dist[i]>max_dist) continue;


	      pfo_LeadK_qcos->Fill(lead_qcos[i]);
	      LeadKDataFile << lead_qcos[i] << '\t' << lead_mom[i] << '\t' << lead_chg[i] << '\t' << lead_dedx[i] << '\t' << lead_kdEdx_dist[i] << '\n';


				switch(lead_pdg_cheat[i]){

					case 321:		// kaon

						TrueDataFile << lead_qcos[i] << '\t' << lead_mom[i] << '\t' << lead_chg[i] << '\t' << lead_dedx[i] << '\t' << lead_kdEdx_dist[i] << '\n';

						pfo_kdEdx_dist_kaon->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_kaon->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_kaon->Fill(lead_pidEdx_dist[i]);

						pfo_p_kdEdx_dist_kaon->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						pfo_pv_kaon->Fill(lead_pv[i]);
						break;

					case 211:		// pion
						pfo_kdEdx_dist_pion->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_pion->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_pion->Fill(lead_pidEdx_dist[i]);

						pfo_p_kdEdx_dist_pion->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						pfo_pv_pion->Fill(lead_pv[i]);
						break;

					case 2212:	// proton
						pfo_kdEdx_dist_proton->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_proton->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_proton->Fill(lead_pidEdx_dist[i]);

						pfo_p_kdEdx_dist_proton->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						pfo_pv_proton->Fill(lead_pv[i]);
						break;

					case 11:		// electron
						pfo_kdEdx_dist_electron->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_electron->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_electron->Fill(lead_pidEdx_dist[i]);

						pfo_p_kdEdx_dist_electron->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						break;

					case 13:		// muon
						pfo_kdEdx_dist_muon->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_muon->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_muon->Fill(lead_pidEdx_dist[i]);

						pfo_p_kdEdx_dist_muon->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						break;

					default:
						pfo_kdEdx_dist_others->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_others->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_others->Fill(lead_pidEdx_dist[i]);

						pfo_p_kdEdx_dist_others->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						break;

				}

			} // loop 2 LEADING PFOs


		} // kpkm


	} // end of event loop

	// printProgress( 1.0 );
	// std::cout << std::endl;


	// printResults();

	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();

	LeadKDataFile.close();
	TrueDataFile.close();


}

void dEdx_dist::printResults(){

	std::cout << "========= Event Results =========" << "\n";
	std::cout << "Process: " << process << "\n";
	std::cout << "# Events: " << nevents << "\n";
	std::cout << "# Events after preselection: " << nevents_after_preselec << "\n";
	// std::cout << "# Events Kaon: " << nevents_kaon_match << "\n";
	std::cout << "LeadK_match: " << nLeadK_match << " LeadK_pass: " << nLeadK_pass << "\n";
 	std::cout << "Kaon purity: " << (float)nLeadK_match / (float)nLeadK_pass << "\n";
 	std::cout << "n_kk: " << n_kk << " n_kpkm: " << n_kpkm << " n_kpkp:" << n_kpkp << " n_kmkm:" << n_kmkm << "\n";

 }



 void dEdx_dist::LeadingMom(TH1F* h1p = 0, TH1F* h1m = 0, TH2F* h2 = 0, int subject = 0, int iPFO0 = 0, int iPFO1 = 0, float P0 = -2, float P1 = -2) {

 	// are leading PFOs Kaons?
 	// if( fabs(pfo_pdgcheat[iPFO0]) == subject && fabs(pfo_pdgcheat[iPFO1]) == subject ){
 	if( fabs(pfo_piddedx[iPFO0]) == subject && fabs(pfo_piddedx[iPFO1]) == subject ){

 		float multchg = pfo_charge[iPFO0] * pfo_charge[iPFO1];
 		bool signPM = (multchg < 0) ? true : false;

 		if(signPM){

 			if(pfo_charge[iPFO0] > 0){

 				h1p->Fill(P0);
 				h1m->Fill(P1);

 				h2->Fill(P1,P0);

 			}else if(pfo_charge[iPFO0] < 0){

 				h1p->Fill(P1);
 				h1m->Fill(P0);

 				h2->Fill(P0,P1);

 			}

 		} // end sign check

 	} // end Leading Kaon check

 }


 bool dEdx_dist::PreSelection(int type=0,float Kvcut=25) {

   if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;

   if(type == 0 ) return true;

   //---------------------
   //Radiative return cuts, photon not in the detector

   double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

   TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
   TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
   VecOP vop;
   float acol=vop.GetSinacol(v1,v2);

   double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
   double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

   float costheta_j0;
   VecOP p_j0(jet_px[0],jet_py[0],jet_pz[0]);
   costheta_j0 = fabs(p_j0.GetCostheta());

   float costheta_j1;
   VecOP p_j1(jet_px[1],jet_py[1],jet_pz[1]);
   costheta_j1 = fabs(p_j1.GetCostheta());

   float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
   float K1=jet0_p*acol/sqrt(1-costheta_j1*costheta_j1);
   float K2=jet1_p*acol/sqrt(1-costheta_j0*costheta_j0);

   if(type == 1 )  if( Kv < Kvcut ) return true;
   if(type == 2 )  if( Kv < Kvcut && bbmass>130 )  return true;



   return false;
 } 