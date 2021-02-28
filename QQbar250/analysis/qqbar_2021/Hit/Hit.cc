#define Hit_cxx
#include "Hit.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Hit::AnalyzeHit(int n_entries=-1, float Kvcut=35, TString output="test")
{

	TH2F* h_HitCos_all  = new TH2F("h_HitCos_all",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);
	TH2F* h_HitCos_k 	= new TH2F("h_HitCos_k",";|cos#theta|; # of Track Hits",100,0,1,230,0,230);

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

		if ( jentry > 10000 && jentry % 10000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

		if(PreSelection(0,Kvcut)==false) continue;

		for(int i=0; i<pfo_n; i++) {

			VecOP pfoVec(pfo_px[i],pfo_py[i],pfo_pz[i]);
			float abscos = abs( pfoVec.GetCostheta() );

			h_HitCos_all->Fill(abscos, pfo_tpc_hits[i]);
			if(fabs(pfo_pdgcheat[i])==321) h_HitCos_k->Fill(abscos, pfo_tpc_hits[i]);
		
			// std::cout << "pfo" << i << std::endl;
			//std::vector< float > angles = CalculateAngles(pfo_px[i],pfo_py[i],pfo_pz[i]);

		}

		// trial
		// if(jentry==1000) break;

	} // end of event loop

	h_HitCos_all->Write();
	h_HitCos_k->Write();

}

bool Hit::PreSelection(int type=0,float Kvcut=25) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  if(type == 0 ) return true;

  return false;
  
}