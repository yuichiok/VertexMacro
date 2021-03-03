#define Hit_cxx
#include "Hit.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Hit::AnalyzeHit(int n_entries=-1, float Kvcut=35, TString output="test")
{

	// Reco Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	// h1_mc_stable[0] = new TH1F(name_mc_stable+"nKaons_evt",";nKaons; Events",20,0,20);

	h1_mc_stable.push_back( new TH1F(name_mc_stable+"nKaons_evt",";nKaons; Events",20,0,20) );

	// TH2F
	// h2_mc_stable[0] = new TH2F(name_mc_stable+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);
	// h2_mc_stable[1] = new TH2F(name_mc_stable+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);

	h2_mc_stable.push_back( new TH2F(name_mc_stable+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );
	h2_mc_stable.push_back( new TH2F(name_mc_stable+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );


	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F
	// h1_pfo[0] = new TH1F(name_pfo+"nKaons_evt",";nKaons; Events",20,0,20);
	h1_pfo.push_back( new TH1F(name_pfo+"nKaons_evt",";nKaons; Events",20,0,20) );

	// TH2F
	// h2_pfo[0] = new TH2F(name_pfo+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);
	// h2_pfo[1] = new TH2F(name_pfo+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);

	h2_pfo.push_back( new TH2F(name_pfo+"HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );
	h2_pfo.push_back( new TH2F(name_pfo+"HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230) );



	TFile *MyFile = new TFile(TString::Format("DQ_250GeV_%s.root",output.Data()),"RECREATE");
	MyFile->cd();


	if (fChain == 0) return;

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
		///////   MC ANALYSiS   ///////
		///////////////////////////////

		int nMCkaons = 0;

		for (int imc = 0; imc < mc_stable_n; imc++)
		{
			VecOP mcVec(mc_stable_px[imc],mc_stable_py[imc],mc_stable_pz[imc]);
			float abscos = abs( mcVec.GetCostheta() );



			if(fabs(mc_stable_pdg[imc])==321){
				
				nMCkaons++;

			
			} // kaon?


		} // end of mc_stable

		h1_mc_stable.at(0)->Fill(nMCkaons);



		////////////////////////////////
		///////   PFO ANALYSiS   ///////
		////////////////////////////////

		int nPFOkaons = 0;

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float abscos = abs( pfoVec.GetCostheta() );

			h2_pfo.at(0)->Fill(abscos, pfo_tpc_hits[ipfo]);

			if(fabs(pfo_pdgcheat[ipfo])==321){
			
				nPFOkaons++;
				h2_pfo.at(1)->Fill(abscos, pfo_tpc_hits[ipfo]);
			
			} // kaon?
		

		} // end of pfo

		h1_pfo.at(0)->Fill(nPFOkaons);

		// trial
		// if(jentry==100) break;

	} // end of event loop


	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();


}

bool Hit::PreSelection(int type=0,float Kvcut=25) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  if(type == 0 ) return true;

  return false;
  
}