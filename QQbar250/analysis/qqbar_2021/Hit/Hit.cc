#define Hit_cxx
#include "Hit.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Hit::AnalyzeHit(int n_entries=-1, float Kvcut=35, TString output="test")
{

	// DO NOT CHANGE THE ORDER OF HISTOGRAMS!!!


	// Reco Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	h1_mc_stable.push_back( new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20) );
	h1_mc_stable.push_back( new TH1F(name_mc_stable+"Kaon_cos",";|cos#theta|; Events",100,0,1.0) );

	// TH2F
	h2_mc_stable.push_back( new TH2F(name_mc_stable+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );
	h2_mc_stable.push_back( new TH2F(name_mc_stable+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );




	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F
	h1_pfo.push_back( new TH1F(name_pfo+"nKaons_evt",";nKaons/Evt; Events",20,0,20) );
	h1_pfo.push_back( new TH1F(name_pfo+"nKaons_jet",";nKaons/Jet; Events",20,0,20) );
	h1_pfo.push_back( new TH1F(name_pfo+"Kaons_cos",";|cos#theta|; Events",100,0,1.0) );
	h1_pfo.push_back( new TH1F(name_pfo+"LeadPFO_pid",";Leading PFO; Events",400,0,400) );
	h1_pfo.push_back( new TH1F(name_pfo+"nKaons_sec_evt",";nKaons/Evt; Events",20,0,20) );

	// TH2F
	h2_pfo.push_back( new TH2F(name_pfo+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );
	h2_pfo.push_back( new TH2F(name_pfo+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );
	h2_pfo.push_back( new TH2F(name_pfo+"LeadPFO_p_pid",";Leading PFO; p [GeV]",4,0,4,200,0,200) );
	h2_pfo.push_back( new TH2F(name_pfo+"LeadKaon_p","; p_{K^{-}} [GeV]; p_{K^{+}} [GeV]",120,0,120,120,0,120) );



	TFile *MyFile = new TFile(TString::Format("DQ_250GeV_%s.root",output.Data()),"RECREATE");
	MyFile->cd();


	if (fChain == 0) return;



	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////

	int Kpm=0;
	int Ksame=0;	

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		if ( jentry > 10000 && jentry % 10000 == 0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

		if(PreSelection(0,Kvcut)==false) continue;


		///////////////////////////////
		///////   MC ANALYSIS   ///////
		///////////////////////////////

		int nMCkaons = 0;

		for (int istable = 0; istable < mc_stable_n; istable++)
		{

			if(sqrt(pow(mc_stable_px[istable],2)+pow(mc_stable_py[istable],2))<2) continue;

			VecOP mcVec(mc_stable_px[istable],mc_stable_py[istable],mc_stable_pz[istable]);
			float abscos = abs( mcVec.GetCostheta() );

			if(fabs(mc_stable_pdg[istable])==321 && mc_stable_isoverlay[istable]==0){
				
				nMCkaons++;
				h1_mc_stable.at(1)->Fill(abscos);
			
			} // kaon?


		} // end of mc_stable

		h1_mc_stable.at(0)->Fill(nMCkaons);


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		int nPFOkaons     = 0;
		int nPFOkaons_sec = 0;

		int nJETkaons1 = 0;
		int nJETkaons2 = 0;

		float maxP0 = 0;
		float maxP1 = 0;
		int LeadiPFO0 = -1;
		int LeadiPFO1 = -1;

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			if(pfo_match[ipfo]<0) continue;
			if(sqrt(pow(pfo_px[ipfo],2)+pow(pfo_py[ipfo],2))<2) continue;


			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float abscos = abs( pfoVec.GetCostheta() );
			float mom    = pfoVec.GetMomentum();

			h2_pfo.at(0)->Fill(abscos, pfo_tpc_hits[ipfo]);


			if( pfo_vtx[ipfo]>0 && fabs(pfo_pdgcheat[ipfo])==321 && pfo_isoverlay[ipfo]==0) nPFOkaons_sec++;

			// PFO kaon?
			if( fabs(pfo_pdgcheat[ipfo])==321 && pfo_isoverlay[ipfo]==0 ){
			
				nPFOkaons++;

				h1_pfo.at(2)->Fill(abscos);

				h2_pfo.at(1)->Fill(abscos, pfo_tpc_hits[ipfo]);
			
			} // end PFO kaon?

			
			// Jet1 Analysis
			if(pfo_match[ipfo]==0){

				if(mom > maxP0){
					maxP0 = mom;
					LeadiPFO0 = ipfo;
				}

				// kaon in jet1?
				if( fabs(pfo_pdgcheat[ipfo])==321 && pfo_isoverlay[ipfo]==0 ){
				
					nJETkaons1++;
				
				} // end kaon in jet1?

			} // end jet1


			// Jet2 Analysis
			if(pfo_match[ipfo]==1){

				if(mom > maxP1){
					maxP1 = mom;
					LeadiPFO1 = ipfo;
				}

				// kaon in jet2?
				if( fabs(pfo_pdgcheat[ipfo])==321 && pfo_isoverlay[ipfo]==0 ){
				
					nJETkaons2++;
				
				} // end kaon in jet2?


			} // end jet1
		

		} // end of pfo


		h1_pfo.at(0)->Fill(nPFOkaons);
		h1_pfo.at(4)->Fill(nPFOkaons_sec);

		h1_pfo.at(1)->Fill(nJETkaons1);
		h1_pfo.at(1)->Fill(nJETkaons2);

		h1_pfo.at(3)->Fill(pfo_pdgcheat[LeadiPFO0]);
		h1_pfo.at(3)->Fill(pfo_pdgcheat[LeadiPFO1]);

		SwitchEGPK(h2_pfo.at(2),pfo_pdgcheat[LeadiPFO0],maxP0);
		SwitchEGPK(h2_pfo.at(2),pfo_pdgcheat[LeadiPFO1],maxP1);


		////////////////////////////////////////
		//////   Leading PFOs ANALYSIS   ///////
		////////////////////////////////////////

		if( pfo_isoverlay[LeadiPFO0]==0 && pfo_isoverlay[LeadiPFO1]==0){

			// are leading PFOs Kaons?
			if( fabs(pfo_pdgcheat[LeadiPFO0]) == 321 && fabs(pfo_pdgcheat[LeadiPFO1]) == 321 ){

				float multchg = pfo_charge[LeadiPFO0] * pfo_charge[LeadiPFO1];
				bool signPM = (multchg < 0) ? true : false;

				if(signPM){

					Kpm++;

					if(pfo_charge[LeadiPFO0] > 0){

						h2_pfo.at(3)->Fill(maxP1,maxP0);

					}else if(pfo_charge[LeadiPFO0] < 0){

						h2_pfo.at(3)->Fill(maxP0,maxP1);

					}


				}else{

					Ksame++;

				} // end if sign check

			} // end Leading Kaon check

		} // end PFO isoverlay



		// int nJETkaons = 0;

		// for(int ijet=0; ijet<2; ijet++){

		// 	VecOP jetVec(jet_px[ijet],jet_py[ijet],jet_pz[ijet]);
		// 	float abscos = abs( jetVec.GetCostheta() );



		// }






		// trial
		if(jentry==1000) break;

	} // end of event loop


	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();


}

// bool Hit::PreSelection(int type=0,float Kvcut=25) {
  
//   if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
//   if(type == 0 ) return true;

//   return false;
  
// }

void Hit::SwitchEGPK(TH2F* h2 = 0, int pdgcheat = 0, float maxP = -2) {

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


bool Hit::PreSelection(int type=0,float Kvcut=25) {
  
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
