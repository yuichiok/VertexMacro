#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define AnaPolar_cxx
#include "AnaPolar.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void AnaPolar::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void AnaPolar::AnalyzePolar(int n_entries=-1, float Kvcut=35, TString output="test")
{

	// Reco Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	TH1F* mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* mc_k_cos 	 = new TH1F(name_mc_stable+"Kaon_cos",";|cos#theta|; Events",100,0,1.0);
	TH1F* mc_qq_cos  = new TH1F("mc_quark_cos",";cos#theta; Events",100,-1.0,1.0);

	h1_mc_stable.push_back( mc_nk_evt );
	h1_mc_stable.push_back( mc_k_cos );

	h1_mc_stable.push_back( mc_qq_cos );

	// TH2F
	// TH2F* mc_HitCos_all	 = new TH2F(name_mc_stable+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);
	// TH2F* mc_HitCos_k	 = new TH2F(name_mc_stable+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);

	// h2_mc_stable.push_back( mc_HitCos_all );
	// h2_mc_stable.push_back( mc_HitCos_k );



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F

	TH1F* pfo_k_cos  				= new TH1F(name_pfo+"Kaon_cos",";|cos#theta|; Events",100,0,1.0);
	TH1F* pfo_LeadK_abscos 	= new TH1F(name_pfo+"LeadKaons_abscos",";|cos#theta|; Events",100,0,1.0);
	TH1F* pfo_LeadK_cos			= new TH1F(name_pfo+"LeadKaons_cos",";cos#theta; Events",100,-1.0,1.0);

	TH1F* pfo_jet_charge_u		= new TH1F(name_pfo+"jet_charge_u",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_ubar	= new TH1F(name_pfo+"jet_charge_ubar",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_d		= new TH1F(name_pfo+"jet_charge_d",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_dbar	= new TH1F(name_pfo+"jet_charge_dbar",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_s		= new TH1F(name_pfo+"jet_charge_s",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_sbar	= new TH1F(name_pfo+"jet_charge_sbar",";Jet charge; Events",100,-1.0,1.0);

	h1_pfo.push_back( pfo_k_cos );
	h1_pfo.push_back( pfo_LeadK_abscos );
	h1_pfo.push_back( pfo_LeadK_cos );
	
	h1_pfo.push_back( pfo_jet_charge_u);
	h1_pfo.push_back( pfo_jet_charge_ubar);
	h1_pfo.push_back( pfo_jet_charge_d);
	h1_pfo.push_back( pfo_jet_charge_dbar);
	h1_pfo.push_back( pfo_jet_charge_s);
	h1_pfo.push_back( pfo_jet_charge_sbar);

	// TH2F
	// TH2F* pfo_LeadPFO_p_pid 	= new TH2F(name_pfo+"LeadPFO_p_pid",";Leading PFO; p [GeV]",4,0,4,200,0,200);

	// h2_pfo.push_back( pfo_LeadPFO_p_pid );

	TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.root",output.Data()),"RECREATE");
	MyFile->cd();


	if (fChain == 0) return;



	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// trial
		if(jentry>10) break;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		// Progress bar
		// if ( jentry > 10000 && jentry % 10000 == 0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
		printProgress( static_cast<double>(jentry) / (double)(1.0 * nentries) );


		if(fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) continue; // ignore MC b/c quarks
		// if(fabs(mc_quark_pdg[0])!=2) continue; // ignore MC other than uu
		// if(fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss

		if(mc_ISR_E[0] + mc_ISR_E[1]>35) continue; 


		////////////////////////////////
		//////   MC QQ ANALYSIS   //////
		////////////////////////////////

		std::vector<VecOP> qqVecs;

		for(int iqq=0; iqq < 2; iqq++){

			VecOP qqVec(mc_quark_px[iqq],mc_quark_py[iqq],mc_quark_pz[iqq]);
			qqVecs.push_back(qqVec);

			float cos 	 = qqVec.GetCostheta();
			float charge = mc_quark_charge[iqq];
			float QQqCos = (charge < 0)? cos: -cos;

			mc_qq_cos->Fill(QQqCos);

		}


		/////////////////////////////////////
		///////   MC STABLE ANALYSIS   //////
		/////////////////////////////////////

		int nMCkaons = 0;

		for (int istable = 0; istable < mc_stable_n; istable++)
		{

			if( sqrt(pow(mc_stable_px[istable],2)+pow(mc_stable_py[istable],2))<2 ) continue;

			VecOP mcVec(mc_stable_px[istable],mc_stable_py[istable],mc_stable_pz[istable]);
			float abscos = abs( mcVec.GetCostheta() );
			float cos 	 = mcVec.GetCostheta();

			if( fabs(mc_stable_pdg[istable])==321 ){
				
				nMCkaons++;
				mc_k_cos->Fill(abscos);
			
			} // kaon?


		} // end of mc_stable

		mc_nk_evt->Fill(nMCkaons);


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		// Jet variables
		float jet_pt[2] = {0};
		float jet_qp[2] = {0};
		float jet_charge[2] = {0};

		// Leading PFO variables
		float maxP[2] 			= {0};
		float lead_abscos[2] = {-2,-2};
		float lead_cos[2] 		= {-2,-2};
		float lead_qcos[2] 	= {-2,-2};
		int   lead_ipfo[2] 	= {-1,-1};


		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			// if(pfo_match[ipfo]<0) continue;

			if(sqrt(pow(pfo_px[ipfo],2)+pow(pfo_py[ipfo],2))<2) continue;
			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;


			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float abscos = abs( pfoVec.GetCostheta() );
			float cos    = pfoVec.GetCostheta();
			float mom    = pfoVec.GetMomentum();
			float pt     = pfoVec.GetPT();
			float charge = pfo_charge[ipfo];

			// PFO kaon?
			if( fabs(pfo_pdgcheat[ipfo])==321 && mom > 2.0 ){
			
				pfo_k_cos->Fill(abscos);
			
			} // end PFO kaon?


			// Jet Analysis
			
			for (int imatch = 0; imatch < 2; ++imatch)
			{
				if(pfo_match[ipfo]==imatch){

					// jet_charge[imatch] += charge * sqrt(pt / 125.0);
					jet_qp[imatch] += charge * sqrt(pt);
					jet_pt[imatch] += pt;

					if(mom > maxP[imatch]){
						maxP[imatch] = mom;
						lead_abscos[imatch] = abscos;
						lead_cos[imatch] = cos;
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

			jet_charge[ijet] = jet_qp[ijet] / sqrt(jet_pt[ijet]);
		
		}


		// Compare jet and qqbar
		for (int iqq = 0; iqq < 2; ++iqq)
		{
			for (int ijet = 0; ijet < 2; ++ijet)
			{
				VecOP angVec;
				float angbtw = angVec.getAngleBtw(qqVecs.at(iqq).GetMomentum3(),jetVecs.at(ijet).GetMomentum3());
				std::cout << "angbtw q" << iqq << ", jet" << ijet << " = " << angbtw << std::endl;
			}

		}

		

		if(jet_charge[0] * jet_charge[1] < 0){

			// float pchg = 0;
			// float mchg = 0;

			// if(jet_charge[0] > 0){
			// 	pchg = jet_charge[0];
			// 	mchg = jet_charge[1];
			// }else{
			// 	pchg = jet_charge[1];
			// 	mchg = jet_charge[0];				
			// }

			int mcqq = fabs(mc_quark_pdg[0]);

			switch(mcqq){

				case 1: // ddbar case
					pfo_jet_charge_d->Fill(jet_charge[0]);
					pfo_jet_charge_dbar->Fill(jet_charge[1]);
					break;

				case 2: // uubar case
					pfo_jet_charge_u->Fill(jet_charge[0]);
					pfo_jet_charge_ubar->Fill(jet_charge[1]);
					break;

				case 3: // ssbar case
					pfo_jet_charge_s->Fill(jet_charge[0]);
					pfo_jet_charge_sbar->Fill(jet_charge[1]);
				break;

				default:
					break;

			} // end switch qqbar			

		}


		///////////////////////////////////////
		//////   Leading PFOs ANALYSIS   //////
		///////////////////////////////////////

		float chg[2] = {0};
		chg[0] = pfo_charge[lead_ipfo[0]];
		chg[1] = pfo_charge[lead_ipfo[1]];
		

		if (fabs(pfo_pdgcheat[lead_ipfo[0]])==321){

			for (int i = 0; i < 2; ++i){

				if(maxP[i]>10){

					if(chg[0]*chg[1]<0){
						lead_qcos[i] = (chg[i] < 0)? lead_cos[i]: -lead_cos[i];
					}

					pfo_LeadK_cos->Fill(lead_qcos[i]);
					pfo_LeadK_abscos->Fill(lead_abscos[i]);

				} // momentum cut (p > 10)
			
			} // Lead PFO loop

		} // if Lead K




	} // end of event loop

	printProgress( 1.0 );
	std::cout << std::endl;

	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();


}



void AnaPolar::LeadingMom(TH1F* h1p = 0, TH1F* h1m = 0, TH2F* h2 = 0, int subject = 0, int iPFO0 = 0, int iPFO1 = 0, float P0 = -2, float P1 = -2) {

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


bool AnaPolar::PreSelection(int type=0,float Kvcut=25) {
  
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