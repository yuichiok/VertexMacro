// A. Irles
// adrian.irles _AT_ ific.uv.es
// August 2021

#define observable_cxx
#include "observable.h"
#include "TPad.h"

void observable::TOF(int n_entries=-1, TString process="",bool secondary=false, bool ignoreoverlay=true, int resolution=0, float ptcut=10000, int typecut=0) {

  //--------------------------------------------------
  TH1F* mass_kaon[4];
  TH1F* mass_proton[4];
  TH1F* mass_pion[4];
  TH1F* mass_electron[4];
  TH1F* mass_muon[4];

  //
  TH2F* p_mass_kaon[4];
  TH2F* p_mass_proton[4];
  TH2F* p_mass_pion[4];
  TH2F* p_mass_electron[4];
  TH2F* p_mass_muon[4];
  //
  TH2F* costheta_mass_kaon[4];
  TH2F* costheta_mass_proton[4];
  TH2F* costheta_mass_pion[4];
  TH2F* costheta_mass_electron[4];
  TH2F* costheta_mass_muon[4];

  for(int i=0;i<4; i++) {
    //--------------------------------------------------
    mass_kaon[i] = new TH1F(TString::Format("mass_kaon_%i",i),TString::Format("mass_kaon_%i",i),1000,0.005,10.005);
    mass_proton[i] = new TH1F(TString::Format("mass_proton_%i",i),TString::Format("mass_proton_%i",i),1000,0.005,10.005);
    mass_pion[i] = new TH1F(TString::Format("mass_pion_%i",i),TString::Format("mass_pion_%i",i),1000,0.005,10.005);
    mass_electron[i] = new TH1F(TString::Format("mass_electron_%i",i),TString::Format("mass_electron_%i",i),1000,0.005,10.005);
    mass_muon[i] = new TH1F(TString::Format("mass_muon_%i",i),TString::Format("mass_muon_%i",i),1000,0.005,10.005);

  //
    p_mass_kaon[i] = new TH2F(TString::Format("p_mass_kaon_%i",i),TString::Format("p_mass_kaon_%i",i),400,0.125,100.125,1000,0.005,10.005);
    p_mass_proton[i] = new TH2F(TString::Format("p_mass_proton_%i",i),TString::Format("p_mass_proton_%i",i),400,0.125,100.125,1000,0.005,10.005);
    p_mass_pion[i] = new TH2F(TString::Format("p_mass_pion_%i",i),TString::Format("p_mass_pion_%i",i),400,0.125,100.125,1000,0.005,10.005);
    p_mass_electron[i] = new TH2F(TString::Format("p_mass_electron_%i",i),TString::Format("p_mass_electron_%i",i),400,0.125,100.125,1000,0.005,10.005);
    p_mass_muon[i] = new TH2F(TString::Format("p_mass_muon_%i",i),TString::Format("p_mass_muon_%i",i),400,0.125,100.125,1000,0.005,10.005);
    
    //
    costheta_mass_kaon[i] = new TH2F(TString::Format("costheta_mass_kaon_%i",i),TString::Format("costheta_mass_kaon_%i",i),20,0,1,1000,0.005,10.005);
    costheta_mass_proton[i] = new TH2F(TString::Format("costheta_mass_proton_%i",i),TString::Format("costheta_mass_proton_%i",i),20,0,1,1000,0.005,10.005);
    costheta_mass_pion[i] = new TH2F(TString::Format("costheta_mass_pion_%i",i),TString::Format("costheta_mass_pion_%i",i),20,0,1,1000,0.005,10.005);
    costheta_mass_electron[i] = new TH2F(TString::Format("costheta_mass_electron_%i",i),TString::Format("costheta_mass_electron_%i",i),20,0,1,1000,0.005,10.005);
    costheta_mass_muon[i] = new TH2F(TString::Format("costheta_mass_muon_%i",i),TString::Format("costheta_mass_muon_%i",i),20,0,1,1000,0.005,10.005);
  }

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  std::cout<<nentries<<std::endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


    double gamma_e=mc_ISR_E[0]+mc_ISR_E[1];
 
    // bool selection=PreSelection(8,35);
    //if(selection==false) continue;

    //for the moment, we restrict the analysis to the bb events without radaitive return
    if(gamma_e<35) {
      //if(PreSelection(8,35)==true) {
      for(int ijet=0; ijet<2; ijet++){
	int nkaonjet=0;
	double nt=0;
	int nkaonvtx=0;
	for(int ipfo=0; ipfo<pfo_n; ipfo++) {

	  float costheta;
	  std::vector<float> p_track;
          p_track.push_back(pfo_px[ipfo]);
          p_track.push_back(pfo_py[ipfo]);
          p_track.push_back(pfo_pz[ipfo]);
          costheta=GetCostheta(p_track);

	  bool nhits_bool=false;
	  if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
	  if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
	  if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

	  float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
	  //float momentum = pfo_pidtof_p_at_calo[ipfo];

	  if(momentum>ptcut) continue;
	  if(secondary==true &&  pfo_vtx[ipfo]<1) continue;
	  if(secondary==false &&  pfo_vtx[ipfo]!=1) continue;
	  if(ignoreoverlay==false && pfo_isoverlay[ipfo]==1) continue;
	  if( pfo_ntracks[ipfo]!=1) continue;
	  if(typecut==0) {
	    if(sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2))<1) continue;      
	    if(pfo_tpc_hits[ipfo]<200) continue; 
	  } else {
	    if(nhits_bool==false) continue;
	  }
	  float beta[4]={0};
	  if(resolution==0) {
	    beta[0]=pfo_pidtof_closest_beta_0ps[ipfo];
	    beta[1]=pfo_pidtof_fastest_beta_0ps[ipfo];
	    beta[2]=pfo_pidtof_cylfit_beta_0ps[ipfo];
	    beta[3]=pfo_pidtof_closestfit_beta_0ps[ipfo];
	  }
	  if(resolution==1) {
	    beta[0]=pfo_pidtof_closest_beta_10ps[ipfo];
	    beta[1]=pfo_pidtof_fastest_beta_10ps[ipfo];
	    beta[2]=pfo_pidtof_cylfit_beta_10ps[ipfo];
	    beta[3]=pfo_pidtof_closestfit_beta_10ps[ipfo];
	  }
	  if(resolution==2) {
	    beta[0]=pfo_pidtof_closest_beta_50ps[ipfo];
	    beta[1]=pfo_pidtof_fastest_beta_50ps[ipfo];
	    beta[2]=pfo_pidtof_cylfit_beta_50ps[ipfo];
	    beta[3]=pfo_pidtof_closestfit_beta_50ps[ipfo];
	  }
	  if(resolution==3) {
	    beta[0]=pfo_pidtof_closest_beta_100ps[ipfo];
	    beta[1]=pfo_pidtof_fastest_beta_100ps[ipfo];
	    beta[2]=pfo_pidtof_cylfit_beta_100ps[ipfo];
	    beta[3]=pfo_pidtof_closestfit_beta_100ps[ipfo];
	  }


	  float mass[4]={0.};
	  for(int i=0; i<4; i++) {
	    mass[i] =(momentum/beta[i])* pow((1.- beta[i]*beta[i]),0.5);
	    //if(fabs(pfo_pdgcheat[ipfo])==211 && mass[i]>0.3 && mass[i]<0.8) std::cout<<"i: "<<i<<" mass:"<<mass[i]<<" beta:"<<beta[i]<<" costheta:"<<costheta<<" momentum:"<<momentum<<std::endl;
	  }
	  
	  if( pfo_ntracks[ipfo]==1 ) {
	      
	    for(int i=0; i<4; i++)  {
	      //  cout<<momentum<<" "<<beta_fit<<" "<<mass_fit<<endl;
	      if( fabs(pfo_pdgcheat[ipfo])==321 ){
		mass_kaon[i]->Fill(mass[i]);
		p_mass_kaon[i]->Fill(momentum,mass[i]);
		costheta_mass_kaon[i]->Fill(fabs(costheta),mass[i]);
	      } 
	      
	      if( fabs(pfo_pdgcheat[ipfo])==211 ) {
		mass_pion[i]->Fill(mass[i]);
		p_mass_pion[i]->Fill(momentum,mass[i]);
		costheta_mass_pion[i]->Fill(fabs(costheta),mass[i]);
	      } 
	      if( fabs(pfo_pdgcheat[ipfo])==2212 ) {
		mass_proton[i]->Fill(mass[i]);
		p_mass_proton[i]->Fill(momentum,mass[i]);
		costheta_mass_proton[i]->Fill(fabs(costheta),mass[i]);
	      }
	      if( fabs(pfo_pdgcheat[ipfo])==11 ) {
		mass_electron[i]->Fill(mass[i]);
		p_mass_electron[i]->Fill(momentum,mass[i]);
		costheta_mass_electron[i]->Fill(fabs(costheta),mass[i]);
	      }
	      if( fabs(pfo_pdgcheat[ipfo])==13 ) {
		mass_muon[i]->Fill(mass[i]);
		p_mass_muon[i]->Fill(momentum,mass[i]);
		costheta_mass_muon[i]->Fill(fabs(costheta),mass[i]);
	      }
	    }//loop over i
	  }//ntracks==1
	}//ipfo
      }//ijet
    }//bb
  }//for

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);
 

  TString fname="primary_tracks";
  if(secondary==true) fname = "secondary_tracks";
  if(ignoreoverlay==true) fname += "_ignoreoverlay";
  if(typecut==1) fname = TString::Format("tof_all_%s_%s_1track_plt%i_softtrack.root",fname.Data(),process.Data(),int(ptcut));
  else fname = TString::Format("tof_all_%s_%s_1track_plt%i.root",fname.Data(),process.Data(),int(ptcut));

  
  TFile *MyFile = new TFile(fname,"RECREATE");
  MyFile->cd();
  for(int i=0; i<4; i++)  {
    
    mass_kaon[i]->Write();
    mass_proton[i]->Write();
    mass_pion[i]->Write();
    mass_electron[i]->Write();
    mass_muon[i]->Write();
    
    p_mass_kaon[i]->Write();
    p_mass_proton[i]->Write();
    p_mass_pion[i]->Write();
    p_mass_electron[i]->Write();
    p_mass_muon[i]->Write();
    
    costheta_mass_kaon[i]->Write();
    costheta_mass_proton[i]->Write();
    costheta_mass_pion[i]->Write();
    costheta_mass_electron[i]->Write();
    costheta_mass_muon[i]->Write();
  }
  MyFile->Close();
  
  
}

  
   

