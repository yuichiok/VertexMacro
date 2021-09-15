#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define AnaPolar_cxx
#include "AnaPolar.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

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

void AnaPolar::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void AnaPolar::AnalyzePolar(int n_entries=-1, float wk=1.0, float MAXP_CUT=10.0, TString output="test")
{

	// MC Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	TH1F* mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* mc_k_cos 	 = new TH1F(name_mc_stable+"Kaon_cos",";|cos#theta|; Events",100,0,1.0);
	
	TH1F* mc_qq_cos  = new TH1F("h_mc_quark_cos",";cos#theta; Entries",100,-1.0,1.0);
	TH1F* mc_qq_sep  = new TH1F("h_mc_quark_sep",";#theta (rad); Events",100,0.,TMath::Pi());

	TH1F* mc_qq_m     = new TH1F("h_mc_quark_m",";Mass (GeV); Entries",100,0,0.003);
	TH1F* mc_qq_pp = new TH1F("h_mc_quark_pp",";p0+p1; Entries",300,0,300);
	TH1F* mc_qq_pz = new TH1F("h_mc_quark_pz",";pz (beam direction); Entries",125,0,125);


	h1_mc_stable.push_back( mc_nk_evt );
	h1_mc_stable.push_back( mc_k_cos );

	h1_mc_stable.push_back( mc_qq_cos );
	h1_mc_stable.push_back( mc_qq_sep );

	h1_mc_stable.push_back( mc_qq_m );
	h1_mc_stable.push_back( mc_qq_pp );
	h1_mc_stable.push_back( mc_qq_pz );


	// TH2F
	TH2F* mc_qq_E	   = new TH2F("h_mc_quark_E",";qbar energy (GeV); q energy (GeV)",200,0,130,200,0,130);
	TH2F* mc_qq_p	   = new TH2F("h_mc_quark_p",";qbar momentum (GeV); q momentum (GeV)",200,120,127,200,120,127);
	TH2F* mc_isr_p	 = new TH2F(name_mc_stable+"isr_p",";qbar momentum (GeV); q momentum (GeV)",200,0,130,200,0,130);

	h2_mc_stable.push_back( mc_qq_E );
	h2_mc_stable.push_back( mc_qq_p );
	h2_mc_stable.push_back( mc_isr_p );
	// h2_mc_stable.push_back( mc_HitCos_k );



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F

	TH1F* pfo_k_cos  				  = new TH1F(name_pfo+"Kaon_cos",";|cos#theta|; Events",100,0,1.0);
	TH1F* pfo_LeadK_abscos 	  = new TH1F(name_pfo+"LeadKaons_abscos",";|cos#theta|; Events",100,0,1.0);
	TH1F* pfo_LeadK_qcos			= new TH1F(name_pfo+"LeadKaons_cos",";cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_cosAdd		= new TH1F(name_pfo+"LeadKaons_cosAdd",";cos#theta_{0}+cos#theta_{1}; Events",100,-2.0,2.0);
	TH1F* pfo_LeadK_phiDiff		= new TH1F(name_pfo+"LeadK_phiDiff",";#delta#phi_{LeadK}; Events",100,-TMath::Pi(),TMath::Pi());
	TH1F* pfo_k_mult_jet 		  = new TH1F(name_pfo+"k_mult_jet","; # kaons/jet ; Entry",10,0,10);

	TH1F* pfo_jet_angdiff  		= new TH1F(name_pfo+"jet_angdiff","; sep. ang qq - jet; Entry",100,0.0,TMath::Pi());

	TH1F* pfo_jet_mult			  = new TH1F(name_pfo+"jet_mult",";Jet multiplicity; Entry",10,0,10);
	TH1F* pfo_jet_mult_uu			= new TH1F(name_pfo+"jet_mult_uu",";Jet multiplicity (u#bar{u}); Entry",10,0,10);
	TH1F* pfo_jet_mult_dd			= new TH1F(name_pfo+"jet_mult_dd",";Jet multiplicity (d#bar{d}); Entry",10,0,10);
	TH1F* pfo_jet_mult_ss			= new TH1F(name_pfo+"jet_mult_ss",";Jet multiplicity (s#bar{s}); Entry",10,0,10);

	TH1F* pfo_jet_LeadK_cos   = new TH1F(name_pfo+"jet_LeadK_cos",";|#theta_{Jet} - #theta_{LeadK}|; Entries",100,0,1.0);

	TH1F* pfo_jet_charge		  = new TH1F(name_pfo+"jet_charge",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_u		= new TH1F(name_pfo+"jet_charge_u",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_ubar	= new TH1F(name_pfo+"jet_charge_ubar",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_d		= new TH1F(name_pfo+"jet_charge_d",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_dbar	= new TH1F(name_pfo+"jet_charge_dbar",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_s		= new TH1F(name_pfo+"jet_charge_s",";Jet charge; Events",100,-1.0,1.0);
	TH1F* pfo_jet_charge_sbar	= new TH1F(name_pfo+"jet_charge_sbar",";Jet charge; Events",100,-1.0,1.0);

	TH1F* pfo_q_match_charge	  = new TH1F(name_pfo+"q_match_charge",";Q match charge; Events",100,-1.0,1.0);
	TH1F* pfo_qbar_match_charge	= new TH1F(name_pfo+"qbar_match_charge",";Qbar match charge; Events",100,-1.0,1.0);

	TH1F* pfo_LeadK_q_match_charge	  = new TH1F(name_pfo+"LeadK_q_match_charge",";Q match charge (LeadK cond.); Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qbar_match_charge	= new TH1F(name_pfo+"LeadK_qbar_match_charge",";Qbar match charge (LeadK cond.); Events",100,-1.0,1.0);

	TH1F* pfo_LeadK_p  					= new TH1F(name_pfo+"LeadK_p",";p[GeV]; Events",120,0,120);
	TH1F* pfo_LeadK_p_10  			= new TH1F(name_pfo+"LeadK_p_10",";p[GeV]; Events",120,0,120);


	h1_pfo.push_back( pfo_k_cos );
	h1_pfo.push_back( pfo_LeadK_abscos );
	h1_pfo.push_back( pfo_LeadK_qcos );
	h1_pfo.push_back( pfo_LeadK_cosAdd );
	h1_pfo.push_back( pfo_LeadK_phiDiff );
	h1_pfo.push_back( pfo_k_mult_jet );

	h1_pfo.push_back( pfo_jet_angdiff );

	h1_pfo.push_back( pfo_jet_mult );
	h1_pfo.push_back( pfo_jet_mult_uu );
	h1_pfo.push_back( pfo_jet_mult_dd );
	h1_pfo.push_back( pfo_jet_mult_ss );

	h1_pfo.push_back( pfo_jet_LeadK_cos );
	
	h1_pfo.push_back( pfo_jet_charge);
	h1_pfo.push_back( pfo_jet_charge_u);
	h1_pfo.push_back( pfo_jet_charge_ubar);
	h1_pfo.push_back( pfo_jet_charge_d);
	h1_pfo.push_back( pfo_jet_charge_dbar);
	h1_pfo.push_back( pfo_jet_charge_s);
	h1_pfo.push_back( pfo_jet_charge_sbar);

	h1_pfo.push_back( pfo_q_match_charge);
	h1_pfo.push_back( pfo_qbar_match_charge);

	h1_pfo.push_back( pfo_LeadK_q_match_charge);
	h1_pfo.push_back( pfo_LeadK_qbar_match_charge);	

	h1_pfo.push_back( pfo_LeadK_p);
	h1_pfo.push_back( pfo_LeadK_p_10);

	// TH2F
	// TH2F* pfo_LeadPFO_p_pid 	= new TH2F(name_pfo+"LeadPFO_p_pid",";Leading PFO; p [GeV]",200,0,200,200,0,200);

	// h2_pfo.push_back( pfo_LeadPFO_p_pid );


	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << MAXP_CUT;
	TString maxp_it = stream.str();
	cout << "MAXP = " << MAXP_CUT << endl;
	process = output;

	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.root",output.Data()),"RECREATE");
	// TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.400.pISR.root",output.Data()),"RECREATE");
	TFile *MyFile = new TFile(TString::Format("rootfiles/DQ_250GeV_%s.400.maxp%s.root",output.Data(),maxp_it.Data()),"RECREATE");
	MyFile->cd();


	if (fChain == 0) return;



	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////

	// const float MAXP_CUT = 10.;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// trial
		// if(jentry>100000) break;
		if(jentry>1000) break;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		// Progress bar
		if ( jentry > 10000 && jentry % 10000 == 0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
		printProgress( static_cast<double>(jentry) / (double)(1.0 * nentries) );


		if(output=="uds" && (fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) ) continue; // ignore MC b/c quarks
		if(output=="uu"  && fabs(mc_quark_pdg[0])!=2) continue; // ignore MC other than uu
		if(output=="ss"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss
		if(output=="dd"  && fabs(mc_quark_pdg[0])!=1) continue; // ignore MC other than dd

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

		mc_qq_E->Fill(mc_quark_E[0],mc_quark_E[1]);

		mc_qq_pz->Fill(mc_quark_pz[0]);
		mc_qq_pz->Fill(mc_quark_pz[1]);

		// if(abs(mc_quark_pz[0]) < 60 && abs(mc_quark_pz[1]) < 60) mc_qq_p->Fill(qqVecs.at(0).GetMomentum(),qqVecs.at(1).GetMomentum());
		mc_qq_p->Fill(qqVecs.at(0).GetMomentum(),qqVecs.at(1).GetMomentum());
		mc_qq_pp->Fill(qqVecs.at(0).GetMomentum()+qqVecs.at(1).GetMomentum());



		mc_qq_m->Fill(mc_quark_m[0]);
		mc_qq_m->Fill(mc_quark_m[1]);


		// Cut qq with qq separation
		float qqsep = VecOP::getAngleBtw(qqVecs.at(0).GetMomentum3(),qqVecs.at(1).GetMomentum3());
		mc_qq_sep->Fill(qqsep);


		// ISR protection
		if(abs(cos(qqsep)) < 0.95) continue;

		if( qqVecs.at(0).GetMomentum() < 120 || qqVecs.at(0).GetMomentum() > 127 ) continue;
		if( qqVecs.at(1).GetMomentum() < 120 || qqVecs.at(1).GetMomentum() > 127 ) continue;

		nevents_after_preselec++;



		for(int iqq=0; iqq < 2; iqq++){

			VecOP qq2Vec(mc_quark_px[iqq],mc_quark_py[iqq],mc_quark_pz[iqq]);

			float cos 	 = qq2Vec.GetCostheta();
			float charge = mc_quark_charge[iqq];
			float QQqCos = (charge < 0)? cos: -cos;

			mc_qq_cos->Fill(QQqCos);

		}


		/////////////////////////////////
		//////   MC ISR ANALYSIS   //////
		/////////////////////////////////

		std::vector<VecOP> isrVecs;

		for(int isr=0; isr < 2; isr++){

			VecOP isrVec(mc_ISR_px[isr],mc_ISR_py[isr],mc_ISR_pz[isr]);
			isrVecs.push_back(isrVec);

		}

		mc_isr_p->Fill(isrVecs.at(0).GetMomentum(),isrVecs.at(1).GetMomentum());


		/////////////////////////////////////
		///////   MC STABLE ANALYSIS   //////
		/////////////////////////////////////

		int nMCkaons = 0;

		for (int istable = 0; istable < mc_stable_n; istable++)
		{

			// if( sqrt(pow(mc_stable_px[istable],2)+pow(mc_stable_py[istable],2))<2 ) continue;

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

		// Compare qqbar
		int qq_match = -1;
		int qq_match_count[2] = {0};

		float qq_match_qp[2] = {0};
		float qq_match_ThrustPz[2] = {0};
		float qq_match_charge[2] = {-100};

		// float wk = 0.3;

		// Jet variables
		float jet_pt[2]       = {0};
		float jet_ThrustPz[2] = {0};
		float jet_qp[2]       = {0};
		float jet_charge[2]   = {-100};
		int   jet_mult[2]     = {0};
		int   jet_k_mult[2]   = {0};

		// Leading PFO variables
		float maxP[2] 			 = {0};
		float lead_abscos[2] = {-2,-2};
		float lead_cos[2] 	 = {-2,-2};
		float lead_phi[2] 	 = {-2,-2};
		float lead_qcos[2] 	 = {-2,-2};
		int   lead_ipfo[2] 	 = {-1,-1};

		VecOP thrustVec(principle_thrust_axis[0],principle_thrust_axis[1],principle_thrust_axis[2]);

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			// if(pfo_match[ipfo]<0) continue;

			// if(sqrt(pow(pfo_px[ipfo],2)+pow(pfo_py[ipfo],2))<2) continue;
			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;


			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float abscos = abs( pfoVec.GetCostheta() );
			float cos    = pfoVec.GetCostheta();
			float phi    = pfoVec.GetPhi();
			float mom    = pfoVec.GetMomentum();
			std::vector<float> mom3   = pfoVec.GetMomentum3();
			float ThrustPz     = pfoVec.GetThrustPz(thrustVec.GetMomentum3());
			// float pt     = pfoVec.GetPT();
			float charge = pfo_charge[ipfo];

			float q_pfo_sep    = VecOP::getAngleBtw(pfoVec.GetMomentum3(),qqVecs.at(0).GetMomentum3());
			float qbar_pfo_sep = VecOP::getAngleBtw(pfoVec.GetMomentum3(),qqVecs.at(1).GetMomentum3());

			qq_match = (q_pfo_sep < qbar_pfo_sep) ? 0 : 1;

			qq_match_count[qq_match]++;

			float ThrustPz_match = pfoVec.GetThrustPz(qqVecs.at(qq_match).GetMomentum3());


			// CHANGE HERE FOR SELECTION

			// if(charge!=0 &&  mom > 5.0){
			if(charge!=0){
				float qp = charge * pow(ThrustPz_match,wk);
				qq_match_qp[qq_match] += qp;
				qq_match_ThrustPz[qq_match] += pow(ThrustPz_match,wk);
			}


			// PFO kaon?
			// if( fabs(pfo_pdgcheat[ipfo])==321 && mom > 2.0 ){
			if( fabs(pfo_piddedx[ipfo])==321 && mom > 2.0 ){
			
				pfo_k_cos->Fill(abscos);
			
			} // end PFO kaon?


			// Jet Analysis
			
			for (int imatch = 0; imatch < 2; ++imatch)
			{
				if(pfo_match[ipfo]==imatch){

					jet_mult[imatch]++;
					// if(fabs(pfo_pdgcheat[ipfo])==321) jet_k_mult[imatch]++;
					if(fabs(pfo_piddedx[ipfo])==321) jet_k_mult[imatch]++;

					jet_qp[imatch] += charge * sqrt(ThrustPz);
					jet_ThrustPz[imatch] += ThrustPz;


					if(mom > maxP[imatch]){
						maxP[imatch] = mom;
						lead_abscos[imatch] = abscos;
						lead_cos[imatch] = cos;
						lead_phi[imatch] = phi;
						lead_ipfo[imatch] = ipfo;
					}

				} // end jet imatch
			} // end imatch


		} // end of pfo



		for(int qmatch=0;qmatch<2;qmatch++){

			qq_match_charge[qmatch] = qq_match_qp[qmatch] / qq_match_ThrustPz[qq_match];

		}

		if(qq_match_count[0]>0) pfo_q_match_charge->Fill(qq_match_charge[0]);
		if(qq_match_count[1]>0) pfo_qbar_match_charge->Fill(qq_match_charge[1]);


		///////////////////////////////
		//////   Jet ANALYSIS   ///////
		///////////////////////////////
		
		std::vector<VecOP> jetVecs;

		for (int ijet = 0; ijet < 2; ++ijet){
		
			VecOP jetVec(jet_px[ijet],jet_py[ijet],jet_pz[ijet]);
			jetVecs.push_back(jetVec);

			jet_charge[ijet] = jet_qp[ijet] / sqrt(jet_ThrustPz[ijet]);

			pfo_k_mult_jet->Fill(jet_k_mult[ijet]);
		
		}


		// Compare jet and qqbar
		float min_angbtw = 1000;
		int min_iqq = -1;
		int min_ijet= -1;

		for (int iqq = 0; iqq < 2; ++iqq)
		{
			for (int ijet = 0; ijet < 2; ++ijet)
			{
				float angbtw = VecOP::getAngleBtw(qqVecs.at(iqq).GetMomentum3(),jetVecs.at(ijet).GetMomentum3());
				pfo_jet_angdiff->Fill(angbtw);

				if(angbtw < min_angbtw){
				
					min_angbtw = angbtw;
					min_iqq    = iqq;
					min_ijet   = ijet;
				
				} // min angbtw
			
			} // jet loop

		} // qq loop

		

		if(jet_charge[0] * jet_charge[1] < 0){

			float jetchg_q = 0;
			float jetchg_qbar = 0;

			pfo_jet_charge->Fill(jet_charge[0]);
			pfo_jet_charge->Fill(jet_charge[1]);


			if(min_iqq == 0){ // if it is q
				jetchg_q = jet_charge[min_iqq];
				jetchg_qbar = jet_charge[1-min_iqq];
			}else{ // if it is qbar
				jetchg_q = jet_charge[1-min_iqq];
				jetchg_qbar = jet_charge[min_iqq];
			}

			int mcqq = fabs(mc_quark_pdg[0]);

			for(int i=0;i<2;i++) pfo_jet_mult->Fill(jet_mult[i]);

			switch(mcqq){

				case 1: // ddbar case
					for(int i=0;i<2;i++) pfo_jet_mult_dd->Fill(jet_mult[i]);
					pfo_jet_charge_d->Fill(jetchg_q);
					pfo_jet_charge_dbar->Fill(jetchg_qbar);
					break;

				case 2: // uubar case
					for(int i=0;i<2;i++) pfo_jet_mult_uu->Fill(jet_mult[i]);
					pfo_jet_charge_u->Fill(jetchg_q);
					pfo_jet_charge_ubar->Fill(jetchg_qbar);
					break;

				case 3: // ssbar case
					for(int i=0;i<2;i++) pfo_jet_mult_ss->Fill(jet_mult[i]);
					pfo_jet_charge_s->Fill(jetchg_q);
					pfo_jet_charge_sbar->Fill(jetchg_qbar);
				break;

				default:
					break;

			} // end switch qqbar			

		} // jet charge opposite


		///////////////////////////////////////
		//////   Leading PFOs ANALYSIS   //////
		///////////////////////////////////////

		float chg[2] = {0};
		chg[0] = pfo_charge[lead_ipfo[0]];
		chg[1] = pfo_charge[lead_ipfo[1]];

		bool kchg_configs[4] = {0};
		kchg_configs[0] = ( (chg[0]<0) && (chg[1]>0) ) ? true : false;
		kchg_configs[1] = ( (chg[0]>0) && (chg[1]<0) ) ? true : false;
		kchg_configs[2] = ( (chg[0]>0) && (chg[1]>0) ) ? true : false;
		kchg_configs[3] = ( (chg[0]<0) && (chg[1]<0) ) ? true : false;

		bool ktags[2] = {0};
		// ktags[0] = (fabs(pfo_pdgcheat[lead_ipfo[0]])==321) ? true : false;
		// ktags[1] = (fabs(pfo_pdgcheat[lead_ipfo[1]])==321) ? true : false;
		ktags[0] = (fabs(pfo_piddedx[lead_ipfo[0]])==321) ? true : false;
		ktags[1] = (fabs(pfo_piddedx[lead_ipfo[1]])==321) ? true : false;

		bool maxP_check = ( maxP[0]>MAXP_CUT && maxP[1]>MAXP_CUT ) ? true : false;

		if(ktags[0] && ktags[1] && maxP_check){

			n_kk++;

			if(kchg_configs[0] || kchg_configs[1]){

				n_kpkm++;

				if(qq_match_count[0]>0) pfo_LeadK_q_match_charge->Fill(qq_match_charge[0]);
				if(qq_match_count[1]>0) pfo_LeadK_qbar_match_charge->Fill(qq_match_charge[1]);

				pfo_LeadK_cosAdd->Fill(lead_cos[0]+lead_cos[1]);
				pfo_LeadK_phiDiff->Fill(lead_phi[0]-lead_phi[1]);

				for (int i = 0; i < 2; ++i){

					VecOP LeadKVec(pfo_px[lead_ipfo[i]],pfo_py[lead_ipfo[i]],pfo_pz[lead_ipfo[i]]);
					float q_LeadK_sep    = VecOP::getAngleBtw(LeadKVec.GetMomentum3(),qqVecs.at(0).GetMomentum3());
					float qbar_LeadK_sep = VecOP::getAngleBtw(LeadKVec.GetMomentum3(),qqVecs.at(1).GetMomentum3());
					int   qq_LeadK_match = (q_LeadK_sep < qbar_LeadK_sep) ? 0 : 1;
					// int   LeadKchg_match = (pfo_pdgcheat[lead_ipfo[i]] < 0) ? 0 : 1;  // s,d (<): 0 = K-, 1 = K+ | u(>): 0 = K+, 1 = K-
					int   LeadKchg_match = (pfo_piddedx[lead_ipfo[i]] < 0) ? 0 : 1;  // s,d (<): 0 = K-, 1 = K+ | u(>): 0 = K+, 1 = K-

					nLeadK_pass++;
					if(LeadKchg_match == qq_LeadK_match) nLeadK_match++;

					lead_qcos[i] = (chg[i] < 0)? lead_cos[i]: -lead_cos[i];
					
					pfo_LeadK_qcos->Fill(lead_qcos[i]);
					pfo_LeadK_abscos->Fill(lead_abscos[i]);
					pfo_LeadK_p_10->Fill(maxP[i]); // with 10GeV cut

					float jet_LeadK_sep  = fabs( VecOP::getAngleBtw(LeadKVec.GetMomentum3(),jetVecs.at(i).GetMomentum3()) );
					pfo_jet_LeadK_cos->Fill(jet_LeadK_sep);


				}  // loop 2 leading kaons 

			}else if( kchg_configs[2] ){ 
				
				n_kpkp++;

			}else if( kchg_configs[3] ){

				n_kmkm++;
			
			}

		} // k double tag / MAXP check



	} // end of event loop

	printProgress( 1.0 );
	std::cout << std::endl;

	printResults();

	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();


}

void AnaPolar::printResults(){

	std::cout << "========= Event Results =========" << "\n";
	std::cout << "Process: " << process << "\n";
	std::cout << "# Events: " << nevents << "\n";
	std::cout << "# Events after preselection: " << nevents_after_preselec << "\n";
	// std::cout << "# Events Kaon: " << nevents_kaon_match << "\n";
	std::cout << "LeadK_match: " << nLeadK_match << " LeadK_pass: " << nLeadK_pass << "\n";
	std::cout << "Kaon purity: " << (float)nLeadK_match / (float)nLeadK_pass << "\n";
	std::cout << "n_kk: " << n_kk << " n_kpkm: " << n_kpkm << " n_kpkp:" << n_kpkp << " n_kmkm:" << n_kmkm << "\n";

}



void AnaPolar::LeadingMom(TH1F* h1p = 0, TH1F* h1m = 0, TH2F* h2 = 0, int subject = 0, int iPFO0 = 0, int iPFO1 = 0, float P0 = -2, float P1 = -2) {

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