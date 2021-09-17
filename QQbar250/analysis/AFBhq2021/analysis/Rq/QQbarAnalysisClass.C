
#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"


void QQbarAnalysisClass::Rq(int n_entries=-1, int test_quark=5, float Kvcut=2500, int bkg=0)
{
  
  TString filename=TString::Format("Rq_pdg%i_%s_250GeV.root",test_quark,process.Data());
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  //Ntotal_nocuts
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",40,0,1);

  TH1F * h_Nparton[4];
  TH1F * h_N0[4];//events after preselection
  TH1F * h_N1[4];//events 1 tag
  TH1F * h_N2[4];//events 2 tags

  for(int i=0;i<4;i++) {
    h_Nparton[i] = new TH1F(TString::Format("h_Nparton_%i",i),TString::Format("h_Nparton_%i",i),40,0,1);
    h_N0[i] = new TH1F(TString::Format("h_N0_%i",i),TString::Format("h_N0_%i",i),40,0,1);
    h_N1[i] = new TH1F(TString::Format("h_N1_%i",i),TString::Format("h_N1_%i",i),40,0,1);
    h_N2[i] = new TH1F(TString::Format("h_N2_%i",i),TString::Format("h_N2_%i",i),40,0,1);
    // 0=b (or signal), 1=c, 2=uds, 3=rad return
  }


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

   
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

    int iquark=-1;
    if(bkg==0) {
      if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) iquark=0;
      if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) iquark=1;
      if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) iquark=2;
      if(gamma_e>Kvcut ) iquark=3;
    }

    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    float costheta_thrust;
    std::vector<float> p_thrust;
    p_thrust.push_back(principle_thrust_axis[0]);
    p_thrust.push_back(principle_thrust_axis[1]);
    p_thrust.push_back(principle_thrust_axis[2]);
    costheta_thrust=fabs(GetCostheta(p_thrust));
    h_Ntotal_nocuts->Fill(costheta_thrust);

    float costheta_qqbar;
    std::vector<float> p_qqbar;
    p_qqbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_qqbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_qqbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_qqbar=fabs(GetCostheta(p_qqbar));

    if(iquark<0 && bkg==0) continue;
    
    //parton level distributions
    if(bkg==1) h_Nparton[0]->Fill(costheta_thrust);
    else h_Nparton[iquark]->Fill(costheta_thrust);


    //reco level distributions
    float Kv=Kreco();
    bool selection=PreSelection(6,Kvcut);
    if(selection==false) continue;

    //jet flavour
    bool jettag[2]={false,false};
    if(test_quark==5 && jet_btag[0]>btag1) jettag[0]=true;
    if(test_quark==5 && jet_btag[1]>btag2) jettag[1]=true;

    if(test_quark==4 && jet_ctag[0]>ctag1) jettag[0]=true;
    if(test_quark==4 && jet_ctag[1]>ctag2) jettag[1]=true;


    if(bkg==1)  {
      h_N0[0]->Fill(costheta_thrust);
      for(int i=0; i<2; i++) {
	if(jettag[i]==true) h_N1[0]->Fill(costheta_thrust);
      }
      if(jettag[0]==true && jettag[1]==true) h_N2[0]->Fill(costheta_thrust);
    } else {
      h_N0[iquark]->Fill(costheta_thrust);
      for(int i=0; i<2; i++) {
	if(jettag[i]==true) h_N1[iquark]->Fill(costheta_thrust);
      }
      if(jettag[0]==true && jettag[1]==true) h_N2[iquark]->Fill(costheta_thrust);
    }

     
  }
  cout<<filename<<endl;
  
  h_Ntotal_nocuts ->Write();
  for(int i=0; i<4; i++) {
    h_Nparton[i]->Write();
    h_N0[i]->Write();
    h_N1[i]->Write();
    h_N2[i]->Write();
  }
}


