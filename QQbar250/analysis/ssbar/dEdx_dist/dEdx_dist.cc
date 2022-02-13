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
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}

void dEdx_dist::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void dEdx_dist::Analyze_dEdxdist(int n_entries=-1, float MINP_CUT=10.0, TString process="test", TString fileout="out")
{

	float MAXP_CUT=60.0;


	// Number Counting
	TH1I* cnt_nevents = new TH1I("h_cnt_nevents",";nevents;Entries",10,0,10);

	_h0_counter.push_back(cnt_nevents);

	// MC Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	TH1F* mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* mc_qq_cos  = new TH1F("h_mc_quark_cos",";cos#theta; Entries",100,-1.0,1.0);

	_h1_mc_stable.push_back( mc_nk_evt );
	_h1_mc_stable.push_back( mc_qq_cos );

	// TH2F



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F
	TH1F* h_pfo_visibleE = new TH1F(name_pfo+"visibleE", ";Visible Energy (GeV);", 300, 0, 300);
	TH1F* h_pfo_LPFOsep  = new TH1F(name_pfo+"LPFOsep", ";LPFO sep;", 30, 0, M_PI);

	TH1F* h_pfo_ISR_eff  = new TH1F(name_pfo+"ISR cheat", ";Cheat (0: non-ISR, 1: ISR);", 2, 0, 2);


  // push_back hists
  _h1_pfo.push_back( h_pfo_visibleE );
  _h1_pfo.push_back( h_pfo_LPFOsep );
  _h1_pfo.push_back( h_pfo_ISR_eff );



	// TH2F

	// dEdx dist
  // TH2F * h_pfo_p_kdEdx_dist_kaon 			= new TH2F(name_pfo+"p_kdEdx_dist_kaon", "p_kdEdx_dist_kaon", 100, 0.5, 100.5, 40, -10, 10);


  // push_back hists
  // h2_pfo.push_back( h_pfo_p_kdEdx_dist_kaon );

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

	// pdg ratio
	int kaon_dEdx_cheat_same0 = 0;
	int kaon_dEdx_cheat_same1 = 0;
	int kaon_dEdx_cheat_all  = 0;


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

		cnt_nevents->Fill(0);

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
		bool cheat_isr = false;

		bool cheat_isr_sep = false;
		if(abs(cos(qqsep)) < 0.95) cheat_isr_sep = true;

		bool cheat_isr_E   = false;
		bool cheat_isr_E0  = false;
		bool cheat_isr_E1  = false;
		if( qqVecs.at(0).GetMomentum() < 120 || qqVecs.at(0).GetMomentum() > 127 ) cheat_isr_E0  = true;
		if( qqVecs.at(1).GetMomentum() < 120 || qqVecs.at(1).GetMomentum() > 127 ) cheat_isr_E1  = true;
		if( cheat_isr_E0 && cheat_isr_E1 ) cheat_isr_E = true;

		if( cheat_isr_sep && cheat_isr_E ) cheat_isr = true;


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		// ISR
		float visibleE = -1;

		// Compare qqbar
		int qq_match = -1;
		int qq_match_count[2] = {0};

		// Leading PFO variables
		int   lead_ipfo[2]	= {-1,-1};
		float maxP[2]				= {0};

		// Count N Kaons
		int n_reco_kaon_all     = 0;
		int n_reco_signK_jet[2][2] = {0};
		vector <float> signKopp_p_jet[2][2];

		vector<_PFOParam> NeuPFOs;
		_JetParam SPFOs[2];

		bool gagag=false;

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			// Add visible energy
			visibleE += pfo_E[ipfo];

			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;

	    // DEDX DISTANCE MINIMUM
	    bool k_dist_min_check  = false;
	    bool p_dist_min_check  = false;
	    bool pi_dist_min_check = false;
	    if( abs(pfo_piddedx_k_dedxdist[ipfo]) < abs(pfo_piddedx_p_dedxdist[ipfo])  ) p_dist_min_check  = true;
	    if( abs(pfo_piddedx_k_dedxdist[ipfo]) < abs(pfo_piddedx_pi_dedxdist[ipfo]) ) pi_dist_min_check = true;
	    if( p_dist_min_check && pi_dist_min_check ) k_dist_min_check = true;

	    if(!k_dist_min_check) continue;


			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float mom    = pfoVec.GetMomentum();

			// Jet Analysis
			
			for (int imatch = 0; imatch < 2; ++imatch)
			{
				if(pfo_match[ipfo]==imatch){

					// Classify PFOs in 2 Jets
					SPFOs[imatch]._id.push_back(ipfo);
					SPFOs[imatch]._mom.push_back(mom);
					SPFOs[imatch]._chg.push_back(pfo_charge[ipfo]);
					SPFOs[imatch]._kdEdx_dist.push_back(pfo_piddedx_k_dedxdist[ipfo]);
					SPFOs[imatch]._pdEdx_dist.push_back(pfo_piddedx_p_dedxdist[ipfo]);
					SPFOs[imatch]._pidEdx_dist.push_back(pfo_piddedx_pi_dedxdist[ipfo]);

					// ID leading particle
					if(mom > maxP[imatch]){
						maxP[imatch] = mom;
						lead_ipfo[imatch] = ipfo;
					}

				} // end jet imatch
			} // end imatch

		} // end of pfo

		// LPFO not found
		if(lead_ipfo[0]==-1 || lead_ipfo[1]==-1) continue;
		cnt_nevents->Fill(2);


		///////////////////////////////
		//////   Jet ANALYSIS   ///////
		///////////////////////////////
		
		_JetParam K_SPFOs[2];

		for (int ijet = 0; ijet < 2; ++ijet){
		
			std::vector<int>::iterator it;
			it = std::search_n (SPFOs[ijet]._id.begin(), SPFOs[ijet]._id.end(), 1, lead_ipfo[ijet]);
			int n = (it-SPFOs[ijet]._id.begin());

			SPFOs[ijet]._id.erase( SPFOs[ijet]._id.begin() + n );
			SPFOs[ijet]._mom.erase( SPFOs[ijet]._mom.begin() + n );
			SPFOs[ijet]._chg.erase( SPFOs[ijet]._chg.begin() + n );
			SPFOs[ijet]._kdEdx_dist.erase( SPFOs[ijet]._kdEdx_dist.begin() + n );
			SPFOs[ijet]._pdEdx_dist.erase( SPFOs[ijet]._pdEdx_dist.begin() + n );
			SPFOs[ijet]._pidEdx_dist.erase( SPFOs[ijet]._pidEdx_dist.begin() + n );

			for (int i = 0; i < SPFOs[ijet]._id.size(); ++i)
			{
				bool kmin=false;
				bool pmin=false;
				bool pimin=false;

				if( abs(SPFOs[ijet]._kdEdx_dist.at(i)) < abs(SPFOs[ijet]._pdEdx_dist.at(i)) )  pmin  = true;
				if( abs(SPFOs[ijet]._kdEdx_dist.at(i)) < abs(SPFOs[ijet]._pidEdx_dist.at(i)) ) pimin = true;
				if( pmin && pimin ) kmin = true;

				if(kmin){
					K_SPFOs[ijet]._id.push_back(SPFOs[ijet]._id.at(i));
					K_SPFOs[ijet]._mom.push_back(SPFOs[ijet]._mom.at(i));
					K_SPFOs[ijet]._chg.push_back(SPFOs[ijet]._chg.at(i));
					K_SPFOs[ijet]._kdEdx_dist.push_back(SPFOs[ijet]._kdEdx_dist.at(i));
					K_SPFOs[ijet]._pdEdx_dist.push_back(SPFOs[ijet]._pdEdx_dist.at(i));
					K_SPFOs[ijet]._pidEdx_dist.push_back(SPFOs[ijet]._pidEdx_dist.at(i));
				}

			}

		}



		///////////////////////////////////////
		//////   Leading PFOs ANALYSIS   //////
		///////////////////////////////////////

		std::vector<VecOP> LeadPFOVecs;

		_PFOParam LPFO[2] = {
			{0, 0, 0, 0, -2, -2, -1, -1, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, -2, -2, -1, -1, 0, 0, 0, 0, 0, 0}
		};

		int nOppK_SPFO[2] = {0};
		_JetParam OppK_SPFO[2];

		for (int i = 0; i < 2; ++i){

			int lpfo = lead_ipfo[i];
		
			VecOP LeadPFOVec(pfo_px[lpfo],pfo_py[lpfo],pfo_pz[lpfo]);
		
			LPFO[i]._dEdx				 = pfo_dedx[lpfo];
			LPFO[i]._kdEdx_dist  = pfo_piddedx_k_dedxdist[lpfo];
			LPFO[i]._pdEdx_dist  = pfo_piddedx_p_dedxdist[lpfo];
			LPFO[i]._pidEdx_dist = pfo_piddedx_pi_dedxdist[lpfo];

			LPFO[i]._chg				 = pfo_charge[lpfo];
			LPFO[i]._pv  				 = sqrt( pfo_d0[lpfo]*pfo_d0[lpfo] + pfo_z0[lpfo]*pfo_z0[lpfo] );
			LPFO[i]._tpc_hits		 = pfo_tpc_hits[lpfo];
			LPFO[i]._pdg_cheat 	 = pfo_pdgcheat[lpfo];

			LPFO[i]._mom 				 = LeadPFOVec.GetMomentum();
			LPFO[i]._cos				 = LeadPFOVec.GetCostheta();
			LPFO[i]._qcos 			 = (LPFO[i]._chg < 0)? LPFO[i]._cos: -LPFO[i]._cos;

			for (int j = 0; j < K_SPFOs[i]._id.size(); ++j)
			{
				// SPFO opposite charge to LPFO and above 10 GeV
				if( (K_SPFOs[i]._chg.at(j) * LPFO[i]._chg < 0) && (K_SPFOs[i]._mom.at(j) > 10))
				{
					OppK_SPFO[i]._mom.push_back(K_SPFOs[i]._mom.at(j));
					nOppK_SPFO[i]++;
				}

			}

			// This compares pfo angle with MC angle -> giving which this pfo are from. 
			// 0: PFO is from q
			// 1: PFO is from qbar

			LPFO[i]._q_sep    = VecOP::getAngleBtw(LeadPFOVec.GetMomentum3(),qqVecs.at(0).GetMomentum3());
			LPFO[i]._qbar_sep = VecOP::getAngleBtw(LeadPFOVec.GetMomentum3(),qqVecs.at(1).GetMomentum3());

			LeadPFOVecs.push_back(LeadPFOVec);

		}


		// ISR REMOVAL

		// LPFO MOM CHECK

		bool ISR_MOM_CHK = false;
		
		if(LPFO[0]._mom > 10 && LPFO[1]._mom > 10){

			ISR_MOM_CHK = true;

		}

		// BACK-TO-BACK

		float LPFO_sep = VecOP::getAngleBtw(LeadPFOVecs.at(0).GetMomentum3(),LeadPFOVecs.at(1).GetMomentum3());
		if(ISR_MOM_CHK) h_pfo_LPFOsep->Fill(LPFO_sep);

		bool ISR_LPFO_SEP_CHK = false;

		if( 3.0 < LPFO_sep ){

			ISR_LPFO_SEP_CHK = true;

		}

		// Visible Energy CHECK

		if(ISR_MOM_CHK) h_pfo_visibleE->Fill(visibleE);

		bool ISR_VIS_CHK = false;

		if( 200 < visibleE ){

			ISR_VIS_CHK = true;

		}


		if( ISR_MOM_CHK && ISR_LPFO_SEP_CHK && ISR_VIS_CHK ){

			if(cheat_isr){

				h_pfo_ISR_eff->Fill(1);
			
			}else{

				h_pfo_ISR_eff->Fill(0);

			}

		}else{

			continue;
		
		}





		// CHARGE CHECK
    bool chg_check = false;
		bool kchg_configs[4] = {0};
		kchg_configs[0] = ( (LPFO[0]._chg<0) && (LPFO[1]._chg>0) ) ? true : false;
		kchg_configs[1] = ( (LPFO[0]._chg>0) && (LPFO[1]._chg<0) ) ? true : false;
		kchg_configs[2] = ( (LPFO[0]._chg>0) && (LPFO[1]._chg>0) ) ? true : false;
		kchg_configs[3] = ( (LPFO[0]._chg<0) && (LPFO[1]._chg<0) ) ? true : false;

    if(kchg_configs[0] || kchg_configs[1]) chg_check = true;













/*		
		// MOMENTUM CHECK
		bool mom_check = ( maxP[0]>MINP_CUT && maxP[1]>MINP_CUT
										&& maxP[0]<MAXP_CUT && maxP[1]<MAXP_CUT ) ? true : false;

		// TPC HIT CHECK
		bool nhits_check = false;
    if (LPFO[0]._tpc_hits > 210 && LPFO[1]._tpc_hits > 210) nhits_check = true;

    // OFFSET CHECK
    bool offset_check = false;
    if( LPFO[0]._pv<1.0 && LPFO[1]._pv<1.0 ) offset_check = true;

    // DEDX DISTANCE MINIMUM
    bool dEdx_dist_min_check   = false;
    bool pdEdx_dist_min_check  = false;
    bool pidEdx_dist_min_check = false;
    if( (abs(LPFO[0]._kdEdx_dist) < abs(LPFO[0]._pdEdx_dist))  && (abs(LPFO[1]._kdEdx_dist) < abs(LPFO[1]._pdEdx_dist))  ) pdEdx_dist_min_check  = true;
    if( (abs(LPFO[0]._kdEdx_dist) < abs(LPFO[0]._pidEdx_dist)) && (abs(LPFO[1]._kdEdx_dist) < abs(LPFO[1]._pidEdx_dist)) ) pidEdx_dist_min_check = true;
    if( pdEdx_dist_min_check && pidEdx_dist_min_check ) dEdx_dist_min_check = true;

    // OPP KAON MULTIPLICITY
    bool OppKMult_check = false;
    if(nOppK_SPFO[0]==0 && nOppK_SPFO[1]==0) OppKMult_check = true;


    bool check_all = false;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check ) check_all = true;
		// if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check && OppKMult_check ) check_all = true;
		// if( 1 ) check_all = true;

		// Stats
		if( chg_check ) {cnt_nevents->Fill(3);}
		if( chg_check && mom_check ) {cnt_nevents->Fill(4);}
		if( chg_check && mom_check && nhits_check ) {cnt_nevents->Fill(5);}
		if( chg_check && mom_check && nhits_check && offset_check ) {cnt_nevents->Fill(6);}
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check ) {cnt_nevents->Fill(7);}
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check && OppKMult_check ) {cnt_nevents->Fill(8);}


		if (check_all)
		{

			// MIGRATION ANLYSIS

			// count number of when the reco is WRONG (source of migration)
			bool flag0=false;
			bool flag1=false;
			if( (LPFO[0]._q_sep<LPFO[0]._qbar_sep) && (LPFO[0]._chg>0) ) flag0=true;
			if( (LPFO[0]._q_sep>LPFO[0]._qbar_sep) && (LPFO[0]._chg<0) ) flag0=true;
			if( (LPFO[1]._q_sep<LPFO[1]._qbar_sep) && (LPFO[1]._chg>0) ) flag1=true;
			if( (LPFO[1]._q_sep>LPFO[1]._qbar_sep) && (LPFO[1]._chg<0) ) flag1=true;


			// MIGRATED EVENTS

			if(flag0||flag1){

				cnt_nevents->Fill(9);

			}else{


			}


			// ANALYZE RECO KAON ID EVENTS

			for (int i = 0; i < 2; ++i)
			{

				// h_pfo_LeadK_qcos->Fill(LPFO[i]._qcos);

			} // Loop Lead PFO

		}// check all
*/


	} // end of event loop

	printResults();

	for(int h=0; h < _h0_counter.size(); h++) _h0_counter.at(h)->Write();

	for(int h=0; h < _h1_mc_stable.size(); h++) _h1_mc_stable.at(h)->Write();
	for(int h=0; h < _h2_mc_stable.size(); h++) _h2_mc_stable.at(h)->Write();

	for(int h=0; h < _h1_pfo.size(); h++) _h1_pfo.at(h)->Write();
	for(int h=0; h < _h2_pfo.size(); h++) _h2_pfo.at(h)->Write();

	LeadKDataFile.close();
	TrueDataFile.close();


}

void dEdx_dist::printResults(){

	cout << "========= Event Results =========" << "\n";

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

 float dEdx_dist::enumerate_pdg(const int pdg=0){

 	switch(abs(pdg)){
		
		case 211:		// pion
			return 0;
			break;
		case 321:		// kaon
			return 1;
			break;
		case 2212:	// proton
			return 2;
			break;
		default:
			return 3;
			break;
 	}

 }
