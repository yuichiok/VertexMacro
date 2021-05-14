#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define AnaLeadK_cxx
#include "AnaLeadK.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void AnaLeadK::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void AnaLeadK::AnalyzeLeadK(int n_entries=-1, float Kvcut=35, TString output="test")
{

	// Reco Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	TH1F* mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* mc_k_cos 	 = new TH1F(name_mc_stable+"Kaon_cos",";|cos#theta|; Events",100,0,1.0);

	h1_mc_stable.push_back( mc_nk_evt );
	h1_mc_stable.push_back( mc_k_cos );

	// TH2F
	TH2F* mc_HitCos_all	 = new TH2F(name_mc_stable+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);
	TH2F* mc_HitCos_k	 = new TH2F(name_mc_stable+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);

	h2_mc_stable.push_back( mc_HitCos_all );
	h2_mc_stable.push_back( mc_HitCos_k );



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F
	TH1F* pfo_nk_evt  				= new TH1F(name_pfo+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* pfo_nk_evt_ss  			= new TH1F(name_pfo+"nKaons_evt_ss",";nKaons/Evt; Events",20,0,20);
	TH1F* pfo_nk_evt_uu  			= new TH1F(name_pfo+"nKaons_evt_uu",";nKaons/Evt; Events",20,0,20);
	TH1F* pfo_nk_jet	  			= new TH1F(name_pfo+"nKaons_jet",";nKaons/Jet; Events",20,0,20);
	TH1F* pfo_nk_jet_ss	  			= new TH1F(name_pfo+"nKaons_jet_ss",";nKaons/Jet; Events",20,0,20);
	TH1F* pfo_nk_jet_uu	  			= new TH1F(name_pfo+"nKaons_jet_uu",";nKaons/Jet; Events",20,0,20);

	TH1F* pfo_k_cos  				= new TH1F(name_pfo+"Kaon_cos",";|cos#theta|; Events",100,0,1.0);
	TH1F* pfo_LeadK_cos  			= new TH1F(name_pfo+"LeadKaons_cos",";|cos#theta|; Events",100,0,1.0);

	TH1F* pfo_LeadPFO_pid			= new TH1F(name_pfo+"LeadPFO_pid",";Leading PFO; Events",400,0,400);
	TH1F* pfo_LeadPFO_pid_parent	= new TH1F(name_pfo+"LeadPFO_pid_parent",";Leading PFO parent; Events",7,0,7);
	TH1F* pfo_nk_sec_evt  			= new TH1F(name_pfo+"nKaons_sec_evt",";nKaons/Evt; Events",20,0,20);

	TH1F* pfo_LeadKp_p  			= new TH1F(name_pfo+"LeadKp_p",";p[GeV]; Events",120,0,120);
	TH1F* pfo_LeadKm_p  			= new TH1F(name_pfo+"LeadKm_p",";p[GeV]; Events",120,0,120);
	TH1F* pfo_LeadPip_p  			= new TH1F(name_pfo+"LeadPip_p",";p[GeV]; Events",120,0,120);
	TH1F* pfo_LeadPim_p  			= new TH1F(name_pfo+"LeadPim_p",";p[GeV]; Events",120,0,120);

	TH1F* pfo_LeadK_p_ss  			= new TH1F(name_pfo+"LeadK_p_ss",";p[GeV]; Events",120,0,120);
	TH1F* pfo_LeadK_p_uu  			= new TH1F(name_pfo+"LeadK_p_uu",";p[GeV]; Events",120,0,120);

	h1_pfo.push_back( pfo_nk_evt );
	h1_pfo.push_back( pfo_nk_evt_ss );
	h1_pfo.push_back( pfo_nk_evt_uu );
	h1_pfo.push_back( pfo_nk_jet );
	h1_pfo.push_back( pfo_nk_jet_ss );
	h1_pfo.push_back( pfo_nk_jet_uu );

	h1_pfo.push_back( pfo_k_cos );
	h1_pfo.push_back( pfo_LeadK_cos );

	h1_pfo.push_back( pfo_LeadPFO_pid );
	h1_pfo.push_back( pfo_LeadPFO_pid_parent );
	h1_pfo.push_back( pfo_nk_sec_evt );

	h1_pfo.push_back( pfo_LeadKp_p );
	h1_pfo.push_back( pfo_LeadKm_p );
	h1_pfo.push_back( pfo_LeadPip_p );
	h1_pfo.push_back( pfo_LeadPim_p );

	h1_pfo.push_back( pfo_LeadK_p_ss );
	h1_pfo.push_back( pfo_LeadK_p_uu );

	// TH2F
	TH2F* pfo_LeadPFO_p_pid 	= new TH2F(name_pfo+"LeadPFO_p_pid",";Leading PFO; p [GeV]",4,0,4,200,0,200);
	TH2F* pfo_LeadK_p 			= new TH2F(name_pfo+"LeadKaon_p","; p_{K^{-}} [GeV]; p_{K^{+}} [GeV]",120,0,120,120,0,120);
	TH2F* pfo_LeadPi_p			= new TH2F(name_pfo+"LeadPi_p","; p_{#pi^{-}} [GeV]; p_{#pi^{+}} [GeV]",120,0,120,120,0,120);

	h2_pfo.push_back( pfo_LeadPFO_p_pid );
	h2_pfo.push_back( pfo_LeadK_p );
	h2_pfo.push_back( pfo_LeadPi_p );



	TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.root",output.Data()),"RECREATE");
	MyFile->cd();


	if (fChain == 0) return;



	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////

	int Kpm=0;
	int Ksame=0;

	float Kedge = 0;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {


		// trial
		// if(jentry>1000) break;


		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		// Progress bar
		// if ( jentry > 10000 && jentry % 10000 == 0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
		printProgress( static_cast<double>(jentry) / (double)(1.0 * nentries) );


		if(fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) continue; // ignore MC b/c quarks
		if(mc_ISR_E[0] + mc_ISR_E[1]>35) continue; 



		///////////////////////////////
		///////   MC ANALYSIS   ///////
		///////////////////////////////

		int nMCkaons = 0;

		for (int istable = 0; istable < mc_stable_n; istable++)
		{

			if( sqrt(pow(mc_stable_px[istable],2)+pow(mc_stable_py[istable],2))<2 ) continue;

			VecOP mcVec(mc_stable_px[istable],mc_stable_py[istable],mc_stable_pz[istable]);
			float abscos = abs( mcVec.GetCostheta() );

			if( fabs(mc_stable_pdg[istable])==321 ){
				
				nMCkaons++;
				mc_k_cos->Fill(abscos);
			
			} // kaon?


		} // end of mc_stable

		mc_nk_evt->Fill(nMCkaons);


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		int nPFOkaons     = 0;
		int nPFOkaons_sec = 0;

		int nJetkaons0 = 0;
		int nJetkaons1 = 0;

		float maxP0 = 0;
		float maxP1 = 0;

		float LeadCos0 = -2;
		float LeadCos1 = -2;

		int LeadiPFO0 = -1;
		int LeadiPFO1 = -1;

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			// if(pfo_match[ipfo]<0) continue;

			if(sqrt(pow(pfo_px[ipfo],2)+pow(pfo_py[ipfo],2))<2) continue;
			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;


			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float abscos = abs( pfoVec.GetCostheta() );
			float mom    = pfoVec.GetMomentum();
			float charge = pfo_charge[ipfo];

			if( pfo_vtx[ipfo]>0 && fabs(pfo_pdgcheat[ipfo])==321 ) nPFOkaons_sec++;


			// PFO kaon?
			if( fabs(pfo_pdgcheat[ipfo])==321 && mom > 2.0 ){
			
				nPFOkaons++;
				pfo_k_cos->Fill(abscos);

				float tpcedge = -1.11849e3*abscos + 1.115e3;

				if( (abscos<0.8 && pfo_tpc_hits[ipfo]>210) || (abscos>=0.8 && pfo_tpc_hits[ipfo]>tpcedge) ){
					Kedge++;
				}
			
			} // end PFO kaon?

			
			// Jet1 Analysis
			if(pfo_match[ipfo]==0){

				if(mom > maxP0){
					maxP0 = mom;
					LeadCos0 = abscos;
					LeadiPFO0 = ipfo;
				}

				// kaon in jet1?
				if( fabs(pfo_pdgcheat[ipfo])==321 && mom > 2.0 ){
				
					nJetkaons0++;
				
				} // end kaon in jet1?

			} // end jet1


			// Jet2 Analysis
			if(pfo_match[ipfo]==1){

				if(mom > maxP1){
					maxP1 = mom;
					LeadCos1 = abscos;
					LeadiPFO1 = ipfo;
				}

				// kaon in jet2?
				if( fabs(pfo_pdgcheat[ipfo])==321 && mom > 2.0 ){
				
					nJetkaons1++;
				
				} // end kaon in jet2?

			} // end jet1

		} // end of pfo


		pfo_nk_evt->Fill(nPFOkaons);

		if(fabs(mc_quark_pdg[0])==2){
			pfo_nk_evt_uu->Fill(nPFOkaons);
		}
		if(fabs(mc_quark_pdg[0])==3){
			pfo_nk_evt_ss->Fill(nPFOkaons);
		}

		pfo_nk_sec_evt->Fill(nPFOkaons_sec);

		pfo_nk_jet->Fill(nJetkaons0);
		pfo_nk_jet->Fill(nJetkaons1);

		pfo_LeadPFO_pid->Fill(pfo_pdgcheat[LeadiPFO0]);
		pfo_LeadPFO_pid->Fill(pfo_pdgcheat[LeadiPFO1]);

		pfo_LeadK_cos->Fill(LeadCos0);
		pfo_LeadK_cos->Fill(LeadCos1);

		SwitchEGPK(pfo_LeadPFO_p_pid,pfo_pdgcheat[LeadiPFO0],maxP0);
		SwitchEGPK(pfo_LeadPFO_p_pid,pfo_pdgcheat[LeadiPFO1],maxP1);


		///////////////////////////////////////
		//////   Leading PFOs ANALYSIS   //////
		///////////////////////////////////////


		if(maxP0 > 2 && maxP1 > 2) LeadingMom(pfo_LeadKp_p, pfo_LeadKm_p, pfo_LeadK_p, 321, LeadiPFO0, LeadiPFO1, maxP0, maxP1);

		LeadingMom(pfo_LeadPip_p, pfo_LeadPim_p, pfo_LeadPi_p, 211, LeadiPFO0, LeadiPFO1, maxP0, maxP1);


		float chg0 = pfo_charge[LeadiPFO0];
		float chg1 = pfo_charge[LeadiPFO1];

		int ffbar_pdg = fabs(mc_quark_pdg[0]);

		if(chg0*chg1 < 0){

			if(maxP0 > 10){

				if(fabs(pfo_pdgcheat[LeadiPFO0])==321){

					pfo_LeadPFO_pid_parent->Fill(ffbar_pdg);
					
					switch( ffbar_pdg ){

						case 3:
							pfo_nk_jet_ss->Fill(nJetkaons0);
							pfo_LeadK_p_ss->Fill(maxP0);
							break;

						case 2:
							pfo_nk_jet_uu->Fill(nJetkaons0);
							pfo_LeadK_p_uu->Fill(maxP0);
							break;

						default:
							break;

					} // switch

				} // Lead PFO = Kaon

			} // maxP0 > 10

			if(maxP1 > 10){

				if(fabs(pfo_pdgcheat[LeadiPFO1])==321){

					pfo_LeadPFO_pid_parent->Fill(ffbar_pdg);
				
					switch( ffbar_pdg ){

						case 3:
							pfo_nk_jet_ss->Fill(nJetkaons1);
							pfo_LeadK_p_ss->Fill(maxP1);
							break;
						
						case 2:
							pfo_nk_jet_uu->Fill(nJetkaons1);
							pfo_LeadK_p_uu->Fill(maxP1);
							break;

						default:
							break;

					} // switch
			
				} // Lead PFO = Kaon

			} // maxP1 > 10

		} // if charge +/-








	} // end of event loop

	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();

	printProgress( 1.0 );
	std::cout << std::endl;

}

// bool AnaLeadK::PreSelection(int type=0,float Kvcut=25) {
  
//   if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
//   if(type == 0 ) return true;

//   return false;
  
// }

void AnaLeadK::LeadingMom(TH1F* h1p = 0, TH1F* h1m = 0, TH2F* h2 = 0, int subject = 0, int iPFO0 = 0, int iPFO1 = 0, float P0 = -2, float P1 = -2) {

	// are leading PFOs Kaons?
	if( fabs(pfo_pdgcheat[iPFO0]) == subject && fabs(pfo_pdgcheat[iPFO1]) == subject ){

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


void AnaLeadK::SwitchEGPK(TH2F* h2 = 0, int pdgcheat = 0, float maxP = -2) {

	switch ( pdgcheat ) {

	case 11:
		h2->Fill(0.,maxP);
		break;

	case 22:
		h2->Fill(1.,maxP);
		break;

	case 211:
		h2->Fill(2.,maxP);
		break;

	case 321:
		h2->Fill(3.,maxP);
		break;

	default:
		break;

	} // end switch

}


bool AnaLeadK::PreSelection(int type=0,float Kvcut=25) {
  
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
