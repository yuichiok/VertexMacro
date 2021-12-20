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
	TH1F* pfo_LeadK_qcos			     = new TH1F(name_pfo+"LeadKaons_cos",";cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_kaon	     = new TH1F(name_pfo+"LeadKaons_cos_kaon","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_proton	   = new TH1F(name_pfo+"LeadKaons_cos_proton","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_pion	     = new TH1F(name_pfo+"LeadKaons_cos_pion","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_electron	 = new TH1F(name_pfo+"LeadKaons_cos_electron","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_muon	     = new TH1F(name_pfo+"LeadKaons_cos_muon","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_others	   = new TH1F(name_pfo+"LeadKaons_cos_others","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);

	TH1F* pfo_LeadK_psum					 = new TH1F(name_pfo+"LeadKaons_psum",";cos#theta; Events",100,-1.0,1.0);

	TH1F* pfo_qq_qcos_wrong 		   = new TH1F(name_pfo+"QQ_cos_wrong",";cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_wrong 		 = new TH1F(name_pfo+"LeadKaons_cos_wrong",";cos#theta; Events",100,-1.0,1.0);


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
	h1_pfo.push_back( pfo_LeadK_qcos_kaon );
	h1_pfo.push_back( pfo_LeadK_qcos_proton );
	h1_pfo.push_back( pfo_LeadK_qcos_pion );
	h1_pfo.push_back( pfo_LeadK_qcos_electron );
	h1_pfo.push_back( pfo_LeadK_qcos_muon );
	h1_pfo.push_back( pfo_LeadK_qcos_others );

	h1_pfo.push_back( pfo_qq_qcos_wrong );
	h1_pfo.push_back( pfo_LeadK_qcos_wrong );


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


	std::stringstream stream_min;
	std::stringstream stream_max;
	stream_min << std::fixed << std::setprecision(0) << MINP_CUT;
	stream_max << std::fixed << std::setprecision(0) << MAXP_CUT;
	TString minp_it = stream_min.str();
	TString maxp_it = stream_max.str();
	cout << "MINP = " << minp_it << endl;
	cout << "MAXP = " << maxp_it << endl;

	process = output;


	// Double Tag
	// TString filename_out = TString::Format("rootfiles/double_tag/DQ_250GeV_%s.minp%smaxp%s.hit210.offset.dEdxMin",output.Data(),minp_it.Data(),maxp_it.Data());
	TString filename_out = TString::Format("rootfiles/double_tag/DQ_250GeV_%s.minp%smaxp%s.hit210.offset.dEdxMin.cheat",output.Data(),minp_it.Data(),maxp_it.Data());


	// test mode
	bool debug = 1;
	if(debug) filename_out = "rootfiles/test";




	TString filename_out_root = filename_out + ".root";
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

	// const float MINP_CUT = 10.;

	// pdg ratio
	int kaon_dEdx_cheat_same0 = 0;
	int kaon_dEdx_cheat_same1 = 0;
	int kaon_dEdx_cheat_all  = 0;


	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {


		if (debug)
		{
			// if(jentry>100000) break;
			if(jentry>50000) break;
		}

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

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
		float qqqcos[2]={-2};


		// ISR protection
		if(abs(cos(qqsep)) < 0.95) continue;

		if( qqVecs.at(0).GetMomentum() < 120 || qqVecs.at(0).GetMomentum() > 127 ) continue;
		if( qqVecs.at(1).GetMomentum() < 120 || qqVecs.at(1).GetMomentum() > 127 ) continue;

		nevents_after_GENselec++;

		for(int iqq=0; iqq < 2; iqq++){

			float cos 	 			= qqVecs.at(iqq).GetCostheta();
			float charge 			= mc_quark_charge[iqq];
			qqqcos[iqq] 			= (charge < 0)? cos: -cos;

			mc_qq_cos->Fill(qqqcos[iqq]);

		}


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		// Compare qqbar
		int qq_match = -1;
		int qq_match_count[2] = {0};

		// Leading PFO variables
		int   lead_ipfo[2]	= {-1};
		float maxP[2]				= {0};


		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;


			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float mom    = pfoVec.GetMomentum();

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

		if(lead_ipfo[0]==-1 || lead_ipfo[1]==-1) continue;
		nevents_after_PFOselec++;


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

		float lead_chg[2]  			   = {0};
		float lead_pv[2]				   = {-1};
		float lead_pfo_tpc_hits[2] = {-1};
		int   lead_pdg_cheat[2]	   = {0};

		float lead_mom[2]				 = {0};
		float lead_cos[2] 	     = {-2};
		float lead_qcos[2] 	     = {-2};

		float lead_q_sep[2]			= {0};
		float lead_qbar_sep[2]	= {0};


		for (int i = 0; i < 2; ++i){

			int lpfo = lead_ipfo[i];
		
			VecOP LeadPFOVec(pfo_px[lpfo],pfo_py[lpfo],pfo_pz[lpfo]);
		
			lead_dedx[i]				= pfo_dedx[lpfo];
			lead_kdEdx_dist[i]  = pfo_piddedx_k_dedxdist[lpfo];
			lead_pdEdx_dist[i]  = pfo_piddedx_p_dedxdist[lpfo];
			lead_pidEdx_dist[i] = pfo_piddedx_pi_dedxdist[lpfo];

			lead_chg[i]					= pfo_charge[lpfo];
			lead_pv[i]  				= sqrt( pfo_d0[lpfo]*pfo_d0[lpfo] + pfo_z0[lpfo]*pfo_z0[lpfo] );
			lead_pfo_tpc_hits[i]= pfo_tpc_hits[lpfo];
			lead_pdg_cheat[i] 	= pfo_pdgcheat[lpfo];

			lead_mom[i] 				= LeadPFOVec.GetMomentum();
			lead_cos[i]					= LeadPFOVec.GetCostheta();
			lead_qcos[i] 				= (lead_chg[i] < 0)? lead_cos[i]: -lead_cos[i];

			// This compares pfo angle with MC angle -> giving which this pfo are from. 
			// 0: PFO is from q
			// 1: PFO is from qbar

			lead_q_sep[i]    = VecOP::getAngleBtw(LeadPFOVec.GetMomentum3(),qqVecs.at(0).GetMomentum3());
			lead_qbar_sep[i] = VecOP::getAngleBtw(LeadPFOVec.GetMomentum3(),qqVecs.at(1).GetMomentum3());


		}

		
		// CHARGE CHECK
    bool chg_check = false;
		bool kchg_configs[4] = {0};
		kchg_configs[0] = ( (lead_chg[0]<0) && (lead_chg[1]>0) ) ? true : false;
		kchg_configs[1] = ( (lead_chg[0]>0) && (lead_chg[1]<0) ) ? true : false;
		kchg_configs[2] = ( (lead_chg[0]>0) && (lead_chg[1]>0) ) ? true : false;
		kchg_configs[3] = ( (lead_chg[0]<0) && (lead_chg[1]<0) ) ? true : false;

    if(kchg_configs[0] || kchg_configs[1]) chg_check = true;

		// MOMENTUM CHECK
		// bool mom_check = ( maxP[0]>MINP_CUT && maxP[1]>MINP_CUT ) ? true : false;
		bool mom_check = ( maxP[0]>MINP_CUT && maxP[1]>MINP_CUT
										 && maxP[0]<MAXP_CUT && maxP[1]<MAXP_CUT ) ? true : false;

		// TPC HIT CHECK
		bool nhits_check = false;
    if (lead_pfo_tpc_hits[0] > 210 && lead_pfo_tpc_hits[1] > 210) nhits_check = true;

    // OFFSET CHECK
    bool offset_check = false;
    if( lead_pv[0]<1.0 && lead_pv[1]<1.0 ) offset_check = true;

    // DEDX DISTANCE MINIMUM
    bool dEdx_dist_min_check   = false;
    bool pdEdx_dist_min_check  = false;
    bool pidEdx_dist_min_check = false;
    if( (abs(lead_kdEdx_dist[0]) < abs(lead_pdEdx_dist[0]))  && (abs(lead_kdEdx_dist[1]) < abs(lead_pdEdx_dist[1]))  ) pdEdx_dist_min_check  = true;
    if( (abs(lead_kdEdx_dist[0]) < abs(lead_pidEdx_dist[0])) && (abs(lead_kdEdx_dist[1]) < abs(lead_pidEdx_dist[1])) ) pidEdx_dist_min_check = true;
    if( pdEdx_dist_min_check && pidEdx_dist_min_check ) dEdx_dist_min_check = true;

    // DEDX DISTANCE WINDOW
    bool dEdx_dist_win_check = false;
		float min_dist=-1.5;
		// float max_dist=0.5;
		float max_dist=2.0;
    if( (lead_kdEdx_dist[0]>min_dist&&lead_kdEdx_dist[0]<max_dist)
    	&&(lead_kdEdx_dist[1]>min_dist&&lead_kdEdx_dist[1]<max_dist) ) dEdx_dist_win_check = true;


    bool check_all = false;
		// if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check && dEdx_dist_win_check ) check_all = true;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check ) check_all = true;

		// Stats
		if( chg_check ) n_chg_check++;
		if( chg_check && mom_check ) n_chg_mom_check++;
		if( chg_check && mom_check && nhits_check ) n_chg_mom_nhits_check++;
		if( chg_check && mom_check && nhits_check && offset_check ) n_chg_mom_nhits_offset_check++;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check ) n_chg_mom_nhits_offset_DistMin_check++;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check && dEdx_dist_win_check ) n_chg_mom_nhits_offset_DistMin_DistWin_check++;



		if (check_all)
		{

			// count number of when the reco is WRONG (source of migration)
			bool flag0=false;
			bool flag1=false;
			if( (lead_q_sep[0]<lead_qbar_sep[0]) && (lead_chg[0]>0) ) flag0=true;
			if( (lead_q_sep[0]>lead_qbar_sep[0]) && (lead_chg[0]<0) ) flag0=true;
			if( (lead_q_sep[1]<lead_qbar_sep[1]) && (lead_chg[1]>0) ) flag1=true;
			if( (lead_q_sep[1]>lead_qbar_sep[1]) && (lead_chg[1]<0) ) flag1=true;
			if(flag0||flag1){
				n_cos_nonconsis++;
				continue;
				pfo_qq_qcos_wrong->Fill(qqqcos[0]);
				pfo_qq_qcos_wrong->Fill(qqqcos[1]);
				pfo_LeadK_qcos_wrong->Fill(lead_qcos[0]);
				pfo_LeadK_qcos_wrong->Fill(lead_qcos[1]);
				cout << "Non consistent: qcos=" << qqqcos[0] << "\tqbarcos=" << qqqcos[1] << "\tcos0=" << lead_qcos[0] << "\tcos1=" << lead_qcos[1] << endl;
				if(debug) cout << "not consistent! -> " << flag0 << ", " << flag1 << endl;

			}//else{cout << "consistent: qcos=" << qqqcos[0] << "\tqbarcos=" << qqqcos[1] << "\tcos0=" << lead_qcos[0] << "\tcos1=" << lead_qcos[1] << endl;}

			for (int i = 0; i < 2; ++i)
			{
	      if (debug)
	      {
	      	cout << "Lead PFO " << i << ": q sep=" << lead_q_sep[i] << "\t qqbar sep=" << lead_qbar_sep[i] << "\t lead chg=" << lead_chg[i] << endl;
	      }

				pfo_LeadK_qcos->Fill(lead_qcos[i]);

				switch(lead_pdg_cheat[i]){

					case 321:		// kaon

						TrueDataFile << lead_qcos[i] << ',' << lead_mom[i] << ',' << lead_chg[i] << ',' << lead_dedx[i] << ',' << lead_kdEdx_dist[i] << '\n';

			      // pfo_LeadK_qcos->Fill(lead_qcos[i]);

						pfo_kdEdx_dist_kaon->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_kaon->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_kaon->Fill(lead_pidEdx_dist[i]);

						pfo_LeadK_qcos_kaon->Fill(lead_qcos[i]);
						pfo_p_kdEdx_dist_kaon->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						pfo_pv_kaon->Fill(lead_pv[i]);
						break;

					case 211:		// pion
						pfo_kdEdx_dist_pion->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_pion->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_pion->Fill(lead_pidEdx_dist[i]);

						pfo_LeadK_qcos_pion->Fill(lead_qcos[i]);
						pfo_p_kdEdx_dist_pion->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						pfo_pv_pion->Fill(lead_pv[i]);
						break;

					case 2212:	// proton
						pfo_kdEdx_dist_proton->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_proton->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_proton->Fill(lead_pidEdx_dist[i]);

						pfo_LeadK_qcos_proton->Fill(lead_qcos[i]);
						pfo_p_kdEdx_dist_proton->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						pfo_pv_proton->Fill(lead_pv[i]);
						break;

					case 11:		// electron
						pfo_kdEdx_dist_electron->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_electron->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_electron->Fill(lead_pidEdx_dist[i]);

						pfo_LeadK_qcos_electron->Fill(lead_qcos[i]);
						pfo_p_kdEdx_dist_electron->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						break;

					case 13:		// muon
						pfo_kdEdx_dist_muon->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_muon->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_muon->Fill(lead_pidEdx_dist[i]);

						pfo_LeadK_qcos_muon->Fill(lead_qcos[i]);
						pfo_p_kdEdx_dist_muon->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						break;

					default:
						pfo_kdEdx_dist_others->Fill(lead_kdEdx_dist[i]);
						pfo_pdEdx_dist_others->Fill(lead_pdEdx_dist[i]);
						pfo_pidEdx_dist_others->Fill(lead_pidEdx_dist[i]);

						pfo_LeadK_qcos_others->Fill(lead_qcos[i]);
						pfo_p_kdEdx_dist_others->Fill(lead_mom[i],lead_kdEdx_dist[i]);
						break;

				} // switch

			} // Loop Lead PFO

		}// check all


	} // end of event loop

	// printProgress( 1.0 );
	// std::cout << std::endl;


	printResults();

	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();

	LeadKDataFile.close();
	TrueDataFile.close();


}

void dEdx_dist::printResults(){

	cout << "========= Event Results =========" << "\n";
	cout << "Process: " << process << "\n";
	cout << "# Events:                     " << nevents << "\n";
	cout << "# Events after GEN selection: " << nevents_after_GENselec << "\n";
	cout << "# Events after PFO selection: " << nevents_after_PFOselec << "\n";
	
	cout << "# Events after LeadK selection (Both LeadPFO should satisfy):" << "\n";
	cout << " - Charge check:              " << n_chg_check << "\n";
	cout << " - Momentum check:            " << n_chg_mom_check << "\n";
	cout << " - TPC hit check:             " << n_chg_mom_nhits_check << "\n";
	cout << " - Offset check:              " << n_chg_mom_nhits_offset_check << "\n";
	cout << " - dEdx dist min check:       " << n_chg_mom_nhits_offset_DistMin_check << "\n";
	cout << " - dEdx dist win check:       " << n_chg_mom_nhits_offset_DistMin_DistWin_check << "\n";

	cout << endl;
	cout << "migration: " << n_cos_nonconsis << "\n";

	// // std::cout << "# Events Kaon: " << nevents_kaon_match << "\n";
	// std::cout << "LeadK_match: " << nLeadK_match << " LeadK_pass: " << nLeadK_pass << "\n";
	// std::cout << "Kaon purity: " << (float)nLeadK_match / (float)nLeadK_pass << "\n";
	// std::cout << "n_kk: " << n_kk << " n_kpkm: " << n_kpkm << " n_kpkp:" << n_kpkp << " n_kmkm:" << n_kmkm << "\n";

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