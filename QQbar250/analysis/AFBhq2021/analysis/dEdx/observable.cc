// A. Irles
// irles @ lal.in2p3.fr
// 30 March 2020

#define observable_cxx
#include "observable.h"
#include "TPad.h"


void observable::dEdx(int n_entries=-1, TString process="",bool secondary=false, bool ignoreoverlay=true,float momentum_min=0, int pdg=4) {

  //  1.,1.33,1.667
  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.5,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,32,36,40,44,48,52,56,60,64,68,72,80,90,100};
  //13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t bins_cos[50]={};
  bins_cos[0]=0;
  for(int i=1;i<50;i++) bins_cos[i]=bins_cos[i-1]+1./50.;
  //13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_cos=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  TH2F* kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* electron_dEdx_truth = new TH2F("electron_dEdx_truth","electron_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* muon_dEdx_truth = new TH2F("muon_dEdx_truth","muon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  TH2F* kaon_dEdx_cos = new TH2F("kaon_dEdx_cos","kaon_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* proton_dEdx_cos = new TH2F("proton_dEdx_cos","proton_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* pion_dEdx_cos = new TH2F("pion_dEdx_cos","pion_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* electron_dEdx_cos = new TH2F("electron_dEdx_cos","electron_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* muon_dEdx_cos = new TH2F("muon_dEdx_cos","muon_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);

  TH2F* kaon_dEdx_pid = new TH2F("kaon_dEdx_pid","kaon_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* proton_dEdx_pid = new TH2F("proton_dEdx_pid","proton_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pion_dEdx_pid = new TH2F("pion_dEdx_pid","pion_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* electron_dEdx_pid = new TH2F("electron_dEdx_pid","electron_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* muon_dEdx_pid = new TH2F("muon_dEdx_pid","muon_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);

  TH1F* n_kaon_jet = new TH1F("n_kaon_jet","n_kaon_jet",15,-0.5,14.5);
  TH1F* n_kaon_vtx = new TH1F("n_kaon_vtx","n_kaon_vtx",15,-0.5,14.5);
  TH1F* p_kaon = new TH1F("p_kaon","p_kaon",125,-0.5,124.5);
  TH1F* p_proton = new TH1F("p_proton","p_proton",125,-0.5,124.5);
  TH1F* p_pion = new TH1F("p_pion","p_pion",125,-0.5,124.5);
  TH1F* p_electron = new TH1F("p_electron","p_electron",125,-0.5,124.5);
  TH1F* p_muon = new TH1F("p_muon","p_muon",125,-0.5,124.5);
  TH1F* p_others = new TH1F("p_others","p_others",125,-0.5,124.5);
  TH1F* costheta_kaon = new TH1F("costheta_kaon","costheta_kaon",40,-1,1);
  TH1F* costheta_proton = new TH1F("costheta_proton","costheta_proton",40,-1,1);
  TH1F* costheta_pion = new TH1F("costheta_pion","costheta_pion",40,-1,1);
  TH1F* costheta_electron = new TH1F("costheta_electron","costheta_electron",40,-1,1);
  TH1F* costheta_muon = new TH1F("costheta_muon","costheta_muon",40,-1,1);
  TH1F* costheta_others = new TH1F("costheta_others","costheta_others",40,-1,1);
  TH2F* p_costheta_kaon = new TH2F("p_costheta_kaon","p_costheta_kaon",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_proton = new TH2F("p_costheta_proton","p_costheta_proton",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_pion = new TH2F("p_costheta_pion","p_costheta_pion",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_electron = new TH2F("p_costheta_electron","p_costheta_electron",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_muon = new TH2F("p_costheta_muon","p_costheta_muon",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_others = new TH2F("p_costheta_others","p_costheta_others",125,-0.5,124.5,40,-1,1);

  TH2F* n_costheta_kaon = new TH2F("n_costheta_kaon","n_costheta_kaon",40,-1,1,25,0,250);


  //
  TH1F* p_kaon_method1 = new TH1F("p_kaon_method1","p_kaon_method1",125,-0.5,124.5);
  TH1F* p_proton_method1 = new TH1F("p_proton_method1","p_proton_method1",125,-0.5,124.5);
  TH1F* p_pion_method1 = new TH1F("p_pion_method1","p_pion_method1",125,-0.5,124.5);
  TH1F* p_electron_method1 = new TH1F("p_electron_method1","p_electron_method1",125,-0.5,124.5);
  TH1F* p_muon_method1 = new TH1F("p_muon_method1","p_muon_method1",125,-0.5,124.5);
  TH1F* p_others_method1 = new TH1F("p_others_method1","p_others_method1",125,-0.5,124.5);

  TH1F* p_kaon_method2 = new TH1F("p_kaon_method2","p_kaon_method2",125,-0.5,124.5);
  TH1F* p_proton_method2 = new TH1F("p_proton_method2","p_proton_method2",125,-0.5,124.5);
  TH1F* p_pion_method2 = new TH1F("p_pion_method2","p_pion_method2",125,-0.5,124.5);
  TH1F* p_electron_method2 = new TH1F("p_electron_method2","p_electron_method2",125,-0.5,124.5);
  TH1F* p_muon_method2 = new TH1F("p_muon_method2","p_muon_method2",125,-0.5,124.5);
  TH1F* p_others_method2 = new TH1F("p_others_method2","p_others_method2",125,-0.5,124.5);

  //
  TH1F* costheta_kaon_method1 = new TH1F("costheta_kaon_method1","costheta_kaon_method1",40,-1,1);
  TH1F* costheta_proton_method1 = new TH1F("costheta_proton_method1","costheta_proton_method1",40,-1,1);
  TH1F* costheta_pion_method1 = new TH1F("costheta_pion_method1","costheta_pion_method1",40,-1,1);
  TH1F* costheta_electron_method1 = new TH1F("costheta_electron_method1","costheta_electron_method1",40,-1,1);
  TH1F* costheta_muon_method1 = new TH1F("costheta_muon_method1","costheta_muon_method1",40,-1,1);
  TH1F* costheta_others_method1 = new TH1F("costheta_others_method1","costheta_others_method1",40,-1,1);

  TH1F* costheta_kaon_method2 = new TH1F("costheta_kaon_method2","costheta_kaon_method2",40,-1,1);
  TH1F* costheta_proton_method2 = new TH1F("costheta_proton_method2","costheta_proton_method2",40,-1,1);
  TH1F* costheta_pion_method2 = new TH1F("costheta_pion_method2","costheta_pion_method2",40,-1,1);
  TH1F* costheta_electron_method2 = new TH1F("costheta_electron_method2","costheta_electron_method2",40,-1,1);
  TH1F* costheta_muon_method2 = new TH1F("costheta_muon_method2","costheta_muon_method2",40,-1,1);
  TH1F* costheta_others_method2 = new TH1F("costheta_others_method2","costheta_others_method2",40,-1,1);

  //
  TH2F* p_costheta_kaon_method1 = new TH2F("p_costheta_kaon_method1","p_costheta_kaon_method1",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_proton_method1 = new TH2F("p_costheta_proton_method1","p_costheta_proton_method1",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_pion_method1 = new TH2F("p_costheta_pion_method1","p_costheta_pion_method1",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_electron_method1 = new TH2F("p_costheta_electron_method1","p_costheta_electron_method1",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_muon_method1 = new TH2F("p_costheta_muon_method1","p_costheta_muon_method1",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_others_method1 = new TH2F("p_costheta_others_method1","p_costheta_others_method1",125,-0.5,124.5,40,-1,1);

  TH2F* p_costheta_kaon_method2 = new TH2F("p_costheta_kaon_method2","p_costheta_kaon_method2",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_proton_method2 = new TH2F("p_costheta_proton_method2","p_costheta_proton_method2",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_pion_method2 = new TH2F("p_costheta_pion_method2","p_costheta_pion_method2",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_electron_method2 = new TH2F("p_costheta_electron_method2","p_costheta_electron_method2",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_muon_method2 = new TH2F("p_costheta_muon_method2","p_costheta_muon_method2",125,-0.5,124.5,40,-1,1);
  TH2F* p_costheta_others_method2 = new TH2F("p_costheta_others_method2","p_costheta_others_method2",125,-0.5,124.5,40,-1,1);

  //
  TH1F* likelihood_kaon_method1 = new TH1F("likelihood_kaon_method1","likelihood_kaon_method1",6010,-598.05,2.95);
  TH1F* likelihood_proton_method1 = new TH1F("likelihood_proton_method1","likelihood_proton_method1",6010,-598.05,2.95);
  TH1F* likelihood_pion_method1 = new TH1F("likelihood_pion_method1","likelihood_pion_method1",6010,-598.05,2.95);
  TH1F* likelihood_electron_method1 = new TH1F("likelihood_electron_method1","likelihood_electron_method1",6010,-598.05,2.95);
  TH1F* likelihood_muon_method1 = new TH1F("likelihood_muon_method1","likelihood_muon_method1",6010,-598.05,2.95);
  TH1F* likelihood_others_method1 = new TH1F("likelihood_others_method1","likelihood_others_method1",6010,-598.05,2.95);

  TH1F* likelihood_kaon_method2 = new TH1F("likelihood_kaon_method2","likelihood_kaon_method2",6010,-598.05,2.95);
  TH1F* likelihood_proton_method2 = new TH1F("likelihood_proton_method2","likelihood_proton_method2",6010,-598.05,2.95);
  TH1F* likelihood_pion_method2 = new TH1F("likelihood_pion_method2","likelihood_pion_method2",6010,-598.05,2.95);
  TH1F* likelihood_electron_method2 = new TH1F("likelihood_electron_method2","likelihood_electron_method2",6010,-598.05,2.95);
  TH1F* likelihood_muon_method2 = new TH1F("likelihood_muon_method2","likelihood_muon_method2",6010,-598.05,2.95);
  TH1F* likelihood_others_method2 = new TH1F("likelihood_others_method2","likelihood_others_method2",6010,-598.05,2.95);

  //
  TH1F* k_prob_kaon_method1 = new TH1F("k_prob_kaon_method1","k_prob_kaon_method1",100,0,1);
  TH1F* k_prob_proton_method1 = new TH1F("k_prob_proton_method1","k_prob_proton_method1",100,0,1);
  TH1F* k_prob_pion_method1 = new TH1F("k_prob_pion_method1","k_prob_pion_method1",100,0,1);
  TH1F* k_prob_electron_method1 = new TH1F("k_prob_electron_method1","k_prob_electron_method1",100,0,1);
  TH1F* k_prob_muon_method1 = new TH1F("k_prob_muon_method1","k_prob_muon_method1",100,0,1);
  TH1F* k_prob_others_method1 = new TH1F("k_prob_others_method1","k_prob_others_method1",100,0,1);

  TH1F* k_prob_kaon_method2 = new TH1F("k_prob_kaon_method2","k_prob_kaon_method2",100,0,1);
  TH1F* k_prob_proton_method2 = new TH1F("k_prob_proton_method2","k_prob_proton_method2",100,0,1);
  TH1F* k_prob_pion_method2 = new TH1F("k_prob_pion_method2","k_prob_pion_method2",100,0,1);
  TH1F* k_prob_electron_method2 = new TH1F("k_prob_electron_method2","k_prob_electron_method2",100,0,1);
  TH1F* k_prob_muon_method2 = new TH1F("k_prob_muon_method2","k_prob_muon_method2",100,0,1);
  TH1F* k_prob_others_method2 = new TH1F("k_prob_others_method2","k_prob_others_method2",100,0,1);

  //
  TH1F* pi_prob_kaon_method1 = new TH1F("pi_prob_kaon_method1","pi_prob_kaon_method1",100,0,1);
  TH1F* pi_prob_proton_method1 = new TH1F("pi_prob_proton_method1","pi_prob_proton_method1",100,0,1);
  TH1F* pi_prob_pion_method1 = new TH1F("pi_prob_pion_method1","pi_prob_pion_method1",100,0,1);
  TH1F* pi_prob_electron_method1 = new TH1F("pi_prob_electron_method1","pi_prob_electron_method1",100,0,1);
  TH1F* pi_prob_muon_method1 = new TH1F("pi_prob_muon_method1","pi_prob_muon_method1",100,0,1);
  TH1F* pi_prob_others_method1 = new TH1F("pi_prob_others_method1","pi_prob_others_method1",100,0,1);

  TH1F* pi_prob_kaon_method2 = new TH1F("pi_prob_kaon_method2","pi_prob_kaon_method2",100,0,1);
  TH1F* pi_prob_proton_method2 = new TH1F("pi_prob_proton_method2","pi_prob_proton_method2",100,0,1);
  TH1F* pi_prob_pion_method2 = new TH1F("pi_prob_pion_method2","pi_prob_pion_method2",100,0,1);
  TH1F* pi_prob_electron_method2 = new TH1F("pi_prob_electron_method2","pi_prob_electron_method2",100,0,1);
  TH1F* pi_prob_muon_method2 = new TH1F("pi_prob_muon_method2","pi_prob_muon_method2",100,0,1);
  TH1F* pi_prob_others_method2 = new TH1F("pi_prob_others_method2","pi_prob_others_method2",100,0,1);

  //
  TH2F* k_pi_prob_kaon_method1 = new TH2F("k_pi_prob_kaon_method1","k_pi_prob_kaon_method1",100,0,1,100,0,1);
  TH2F* k_pi_prob_proton_method1 = new TH2F("k_pi_prob_proton_method1","k_pi_prob_proton_method1",100,0,1,100,0,1);
  TH2F* k_pi_prob_pion_method1 = new TH2F("k_pi_prob_pion_method1","k_pi_prob_pion_method1",100,0,1,100,0,1);
  TH2F* k_pi_prob_electron_method1 = new TH2F("k_pi_prob_electron_method1","k_pi_prob_electron_method1",100,0,1,100,0,1);
  TH2F* k_pi_prob_muon_method1 = new TH2F("k_pi_prob_muon_method1","k_pi_prob_muon_method1",100,0,1,100,0,1);
  TH2F* k_pi_prob_others_method1 = new TH2F("k_pi_prob_others_method1","k_pi_prob_others_method1",100,0,1,100,0,1);

  TH2F* k_pi_prob_kaon_method2 = new TH2F("k_pi_prob_kaon_method2","k_pi_prob_kaon_method2",100,0,1,100,0,1);
  TH2F* k_pi_prob_proton_method2 = new TH2F("k_pi_prob_proton_method2","k_pi_prob_proton_method2",100,0,1,100,0,1);
  TH2F* k_pi_prob_pion_method2 = new TH2F("k_pi_prob_pion_method2","k_pi_prob_pion_method2",100,0,1,100,0,1);
  TH2F* k_pi_prob_electron_method2 = new TH2F("k_pi_prob_electron_method2","k_pi_prob_electron_method2",100,0,1,100,0,1);
  TH2F* k_pi_prob_muon_method2 = new TH2F("k_pi_prob_muon_method2","k_pi_prob_muon_method2",100,0,1,100,0,1);
  TH2F* k_pi_prob_others_method2 = new TH2F("k_pi_prob_others_method2","k_pi_prob_others_method2",100,0,1,100,0,1);

  //
  TH1F* kdEdx_dist_kaon = new TH1F("kdEdx_dist_kaon","kdEdx_dist_kaon",40,-10,10);
  TH1F* kdEdx_dist_proton = new TH1F("kdEdx_dist_proton","kdEdx_dist_proton",40,-10,10);
  TH1F* kdEdx_dist_pion = new TH1F("kdEdx_dist_pion","kdEdx_dist_pion",40,-10,10);
  TH1F* kdEdx_dist_electron = new TH1F("kdEdx_dist_electron","kdEdx_dist_electron",40,-10,10);
  TH1F* kdEdx_dist_muon = new TH1F("kdEdx_dist_muon","kdEdx_dist_muon",40,-10,10);
  TH1F* kdEdx_dist_others = new TH1F("kdEdx_dist_others","kdEdx_dist_others",40,-10,10);

  //
  TH2F* p_kdEdx_dist_kaon = new TH2F("p_kdEdx_dist_kaon","p_kdEdx_dist_kaon",100,0.5,100.5,40,-10,10);
  TH2F* p_kdEdx_dist_proton = new TH2F("p_kdEdx_dist_proton","p_kdEdx_dist_proton",100,0.5,100.5,40,-10,10);
  TH2F* p_kdEdx_dist_pion = new TH2F("p_kdEdx_dist_pion","p_kdEdx_dist_pion",100,0.5,100.5,40,-10,10);
  TH2F* p_kdEdx_dist_electron = new TH2F("p_kdEdx_dist_electron","p_kdEdx_dist_electron",100,0.5,100.5,40,-10,10);
  TH2F* p_kdEdx_dist_muon = new TH2F("p_kdEdx_dist_muon","p_kdEdx_dist_muon",100,0.5,100.5,40,-10,10);
  TH2F* p_kdEdx_dist_others = new TH2F("p_kdEdx_dist_others","p_kdEdx_dist_others",100,0.5,100.5,40,-10,10);

  //
  TH2F* costheta_kdEdx_dist_kaon = new TH2F("costheta_kdEdx_dist_kaon","costheta_kdEdx_dist_kaon",20,0,1,40,-10,10);
  TH2F* costheta_kdEdx_dist_proton = new TH2F("costheta_kdEdx_dist_proton","costheta_kdEdx_dist_proton",20,0,1,40,-10,10);
  TH2F* costheta_kdEdx_dist_pion = new TH2F("costheta_kdEdx_dist_pion","costheta_kdEdx_dist_pion",20,0,1,40,-10,10);
  TH2F* costheta_kdEdx_dist_electron = new TH2F("costheta_kdEdx_dist_electron","costheta_kdEdx_dist_electron",20,0,1,40,-10,10);
  TH2F* costheta_kdEdx_dist_muon = new TH2F("costheta_kdEdx_dist_muon","costheta_kdEdx_dist_muon",20,0,1,40,-10,10);
  TH2F* costheta_kdEdx_dist_others = new TH2F("costheta_kdEdx_dist_others","costheta_kdEdx_dist_others",20,0,1,40,-10,10);


  // counters
  Int_t isrcut  = 0;

  Int_t all_pfo = 0;
  Int_t nmomcut_pfo = 0;
  Int_t ncoscut_pfo = 0;


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  std::cout<<nentries<<std::endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // if( jentry>10000 ) break;
    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


    double gamma_e=mc_ISR_E[0]+mc_ISR_E[1];

    // bool selection=false;
    // if(pdg==3) selection = PreSelection(1,35);
    // if(pdg==5) selection = PreSelection(7,35);
    // if(pdg==4) selection = PreSelection(8,35);

    // if(selection==false) continue;

    //for the moment, we restrict the analysis to the bb events without radaitive return
    if(fabs(mc_quark_pdg[0])==pdg && gamma_e<35) {

      isrcut++;

      for(int ijet=0; ijet<2; ijet++){
       int nkaonjet=0;
       double nt=0;
	//	if(jet_btag[ijet]>0.8) {
       int nkaonvtx=0;

       all_pfo += pfo_n;

       for(int ipfo=0; ipfo<pfo_n; ipfo++) {

         float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
         if(momentum < momentum_min) continue;
         nmomcut_pfo++;
         if(secondary==true &&  pfo_vtx[ipfo]<1) continue;
	  // if(secondary==false &&  pfo_vtx[ipfo]>0) continue;
         if(ignoreoverlay==false && pfo_isoverlay[ipfo]==1) continue;

         float costheta;
         std::vector<float> p_track;
         p_track.push_back(pfo_px[ipfo]);
         p_track.push_back(pfo_py[ipfo]);
         p_track.push_back(pfo_pz[ipfo]);
         costheta=GetCostheta(p_track);

         if(fabs(costheta)<0.8) continue;
         ncoscut_pfo++;
         float dedx=pfo_dedx[ipfo];

         bool nhits_bool=false;
         if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
         if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
         if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

         if( pfo_ntracks[ipfo]==1 && nhits_bool==true) {

           if( fabs(pfo_pdgcheat[ipfo])==321 ){
             nkaonjet++;
             nkaonvtx++;
             p_kaon->Fill(momentum);
             costheta_kaon->Fill(costheta);
             p_costheta_kaon->Fill(momentum,costheta);
             kdEdx_dist_kaon->Fill(pfo_piddedx_k_dedxdist[ipfo]);
             p_kdEdx_dist_kaon->Fill(momentum,pfo_piddedx_k_dedxdist[ipfo]);
             costheta_kdEdx_dist_kaon->Fill(fabs(costheta),pfo_piddedx_k_dedxdist[ipfo]);

             n_costheta_kaon->Fill(costheta,pfo_tpc_hits[ipfo]);

             if(fabs(pfo_pid[ipfo])==321) {
              p_kaon_method1->Fill(momentum);
              costheta_kaon_method1->Fill(costheta);
              p_costheta_kaon_method1->Fill(momentum,costheta);
              likelihood_kaon_method1->Fill(pfo_pid_likelihood[ipfo]);
              k_prob_kaon_method1->Fill(pfo_pid_kprob[ipfo]);
              pi_prob_kaon_method1->Fill(pfo_pid_piprob[ipfo]);
              k_pi_prob_kaon_method1->Fill(pfo_pid_kprob[ipfo],pfo_pid_piprob[ipfo]);
            }

            if(fabs(pfo_piddedx[ipfo])==321) {
              p_kaon_method2->Fill(momentum);
              costheta_kaon_method2->Fill(costheta);
              p_costheta_kaon_method2->Fill(momentum,costheta);
              likelihood_kaon_method2->Fill(pfo_piddedx_likelihood[ipfo]);
              k_prob_kaon_method2->Fill(pfo_piddedx_kprob[ipfo]);
              pi_prob_kaon_method2->Fill(pfo_piddedx_piprob[ipfo]);
              k_pi_prob_kaon_method2->Fill(pfo_piddedx_kprob[ipfo],pfo_pid_piprob[ipfo]);
            }

          } else {
           if( fabs(pfo_pdgcheat[ipfo])==211 ) {
            p_pion->Fill(momentum);
            costheta_pion->Fill(costheta);
            p_costheta_pion->Fill(momentum,costheta);
            kdEdx_dist_pion->Fill(pfo_piddedx_k_dedxdist[ipfo]);
            p_kdEdx_dist_pion->Fill(momentum,pfo_piddedx_k_dedxdist[ipfo]);
            costheta_kdEdx_dist_pion->Fill(fabs(costheta),pfo_piddedx_k_dedxdist[ipfo]);

            if(fabs(pfo_pid[ipfo])==321) {
              p_pion_method1->Fill(momentum);
              costheta_pion_method1->Fill(costheta);
              p_costheta_pion_method1->Fill(momentum,costheta);
              likelihood_pion_method1->Fill(pfo_pid_likelihood[ipfo]);
              k_prob_pion_method1->Fill(pfo_pid_kprob[ipfo]);
              pi_prob_pion_method1->Fill(pfo_pid_piprob[ipfo]);
              k_pi_prob_pion_method1->Fill(pfo_pid_kprob[ipfo],pfo_pid_piprob[ipfo]);
            }

            if(fabs(pfo_piddedx[ipfo])==321) {
              p_pion_method2->Fill(momentum);
              costheta_pion_method2->Fill(costheta);
              p_costheta_pion_method2->Fill(momentum,costheta);
              likelihood_pion_method2->Fill(pfo_piddedx_likelihood[ipfo]);
              k_prob_pion_method2->Fill(pfo_piddedx_kprob[ipfo]);
              pi_prob_pion_method2->Fill(pfo_piddedx_piprob[ipfo]);
              k_pi_prob_pion_method2->Fill(pfo_piddedx_kprob[ipfo],pfo_pid_piprob[ipfo]);
            }

          } else {
            if( fabs(pfo_pdgcheat[ipfo])==2212 ) {
              p_proton->Fill(momentum);
              costheta_proton->Fill(costheta);
              p_costheta_proton->Fill(momentum,costheta);
              kdEdx_dist_proton->Fill(pfo_piddedx_k_dedxdist[ipfo]);
              p_kdEdx_dist_proton->Fill(momentum,pfo_piddedx_k_dedxdist[ipfo]);
              costheta_kdEdx_dist_proton->Fill(fabs(costheta),pfo_piddedx_k_dedxdist[ipfo]);

              if(fabs(pfo_pid[ipfo])==321) {
                p_proton_method1->Fill(momentum);
                costheta_proton_method1->Fill(costheta);
                p_costheta_proton_method1->Fill(momentum,costheta);
                likelihood_proton_method1->Fill(pfo_pid_likelihood[ipfo]);
                k_prob_proton_method1->Fill(pfo_pid_kprob[ipfo]);
                pi_prob_proton_method1->Fill(pfo_pid_piprob[ipfo]);
                k_pi_prob_proton_method1->Fill(pfo_pid_kprob[ipfo],pfo_pid_piprob[ipfo]);
              }

              if(fabs(pfo_piddedx[ipfo])==321) {
                p_proton_method2->Fill(momentum);
                costheta_proton_method2->Fill(costheta);
                p_costheta_proton_method2->Fill(momentum,costheta);
                likelihood_proton_method2->Fill(pfo_piddedx_likelihood[ipfo]);
                k_prob_proton_method2->Fill(pfo_piddedx_kprob[ipfo]);
                pi_prob_proton_method2->Fill(pfo_piddedx_piprob[ipfo]);
                k_pi_prob_proton_method2->Fill(pfo_piddedx_kprob[ipfo],pfo_pid_piprob[ipfo]);
              }
            } else {
              if( fabs(pfo_pdgcheat[ipfo])==11 ) {
                p_electron->Fill(momentum);
                costheta_electron->Fill(costheta);
                p_costheta_electron->Fill(momentum,costheta);
                kdEdx_dist_electron->Fill(pfo_piddedx_k_dedxdist[ipfo]);
                p_kdEdx_dist_electron->Fill(momentum,pfo_piddedx_k_dedxdist[ipfo]);
                costheta_kdEdx_dist_electron->Fill(fabs(costheta),pfo_piddedx_k_dedxdist[ipfo]);

                if(fabs(pfo_pid[ipfo])==321) {
                  p_electron_method1->Fill(momentum);
                  costheta_electron_method1->Fill(costheta);
                  p_costheta_electron_method1->Fill(momentum,costheta);
                  likelihood_electron_method1->Fill(pfo_pid_likelihood[ipfo]);
                  k_prob_electron_method1->Fill(pfo_pid_kprob[ipfo]);
                  pi_prob_electron_method1->Fill(pfo_pid_piprob[ipfo]);
                  k_pi_prob_electron_method1->Fill(pfo_pid_kprob[ipfo],pfo_pid_piprob[ipfo]);
                }

                if(fabs(pfo_piddedx[ipfo])==321) {
                  p_electron_method2->Fill(momentum);
                  costheta_electron_method2->Fill(costheta);
                  p_costheta_electron_method2->Fill(momentum,costheta);
                  likelihood_electron_method2->Fill(pfo_piddedx_likelihood[ipfo]);
                  k_prob_electron_method2->Fill(pfo_piddedx_kprob[ipfo]);
                  pi_prob_electron_method2->Fill(pfo_piddedx_piprob[ipfo]);
                  k_pi_prob_electron_method2->Fill(pfo_piddedx_kprob[ipfo],pfo_pid_piprob[ipfo]);
                }
              } else {
                if( fabs(pfo_pdgcheat[ipfo])==13 ) {
                  p_muon->Fill(momentum);
                  costheta_muon->Fill(costheta);
                  p_costheta_muon->Fill(momentum,costheta);
                  kdEdx_dist_muon->Fill(pfo_piddedx_k_dedxdist[ipfo]);
                  p_kdEdx_dist_muon->Fill(momentum,pfo_piddedx_k_dedxdist[ipfo]);
                  costheta_kdEdx_dist_muon->Fill(fabs(costheta),pfo_piddedx_k_dedxdist[ipfo]);

                  if(fabs(pfo_pid[ipfo])==321) {
                   p_muon_method1->Fill(momentum);
                   costheta_muon_method1->Fill(costheta);
                   p_costheta_muon_method1->Fill(momentum,costheta);
                   likelihood_muon_method1->Fill(pfo_pid_likelihood[ipfo]);
                   k_prob_muon_method1->Fill(pfo_pid_kprob[ipfo]);
                   pi_prob_muon_method1->Fill(pfo_pid_piprob[ipfo]);
                   k_pi_prob_muon_method1->Fill(pfo_pid_kprob[ipfo],pfo_pid_piprob[ipfo]);
                 }

                 if(fabs(pfo_piddedx[ipfo])==321) {
                   p_muon_method2->Fill(momentum);
                   costheta_muon_method2->Fill(costheta);
                   p_costheta_muon_method2->Fill(momentum,costheta);
                   likelihood_muon_method2->Fill(pfo_piddedx_likelihood[ipfo]);
                   k_prob_muon_method2->Fill(pfo_piddedx_kprob[ipfo]);
                   pi_prob_muon_method2->Fill(pfo_piddedx_piprob[ipfo]);
                   k_pi_prob_muon_method2->Fill(pfo_piddedx_kprob[ipfo],pfo_pid_piprob[ipfo]);
                 }

               } else {
                p_others->Fill(momentum);
                costheta_others->Fill(costheta);
                p_costheta_others->Fill(momentum,costheta);
                kdEdx_dist_others->Fill(pfo_piddedx_k_dedxdist[ipfo]);
                p_kdEdx_dist_others->Fill(momentum,pfo_piddedx_k_dedxdist[ipfo]);
                costheta_kdEdx_dist_others->Fill(fabs(costheta),pfo_piddedx_k_dedxdist[ipfo]);

                if(fabs(pfo_pid[ipfo])==321) {
                 p_others_method1->Fill(momentum);
                 costheta_others_method1->Fill(costheta);
                 p_costheta_others_method1->Fill(momentum,costheta);
                 likelihood_others_method1->Fill(pfo_pid_likelihood[ipfo]);
                 k_prob_others_method1->Fill(pfo_pid_kprob[ipfo]);
                 pi_prob_others_method1->Fill(pfo_pid_piprob[ipfo]);
                 k_pi_prob_others_method1->Fill(pfo_pid_kprob[ipfo],pfo_pid_piprob[ipfo]);
               }

               if(fabs(pfo_piddedx[ipfo])==321) {
                 p_others_method2->Fill(momentum);
                 costheta_others_method2->Fill(costheta);
                 p_costheta_others_method2->Fill(momentum,costheta);
                 likelihood_others_method2->Fill(pfo_piddedx_likelihood[ipfo]);
                 k_prob_others_method2->Fill(pfo_piddedx_kprob[ipfo]);
                 pi_prob_others_method2->Fill(pfo_piddedx_piprob[ipfo]);
                 k_pi_prob_others_method2->Fill(pfo_piddedx_kprob[ipfo],pfo_pid_piprob[ipfo]);
               }
             }
           }
         }
       }
     }

	    //for(int ijet=0; ijet<2; ijet++) {
     if(dedx>0) {
       if(fabs(pfo_pdgcheat[ipfo])==211) pion_dEdx_truth->Fill(momentum,dedx);
       if(fabs(pfo_pdgcheat[ipfo])==321) kaon_dEdx_truth->Fill(momentum,dedx);
       if(fabs(pfo_pdgcheat[ipfo])==2212) proton_dEdx_truth->Fill(momentum,dedx);
       if(fabs(pfo_pdgcheat[ipfo])==11) electron_dEdx_truth->Fill(momentum,dedx);
       if(fabs(pfo_pdgcheat[ipfo])==13) muon_dEdx_truth->Fill(momentum,dedx);

       if(fabs(pfo_pdgcheat[ipfo])==211) pion_dEdx_cos->Fill(fabs(costheta),dedx);
       if(fabs(pfo_pdgcheat[ipfo])==321) kaon_dEdx_cos->Fill(fabs(costheta),dedx);
       if(fabs(pfo_pdgcheat[ipfo])==2212) proton_dEdx_cos->Fill(fabs(costheta),dedx);
       if(fabs(pfo_pdgcheat[ipfo])==11) electron_dEdx_cos->Fill(fabs(costheta),dedx);
       if(fabs(pfo_pdgcheat[ipfo])==13) muon_dEdx_cos->Fill(fabs(costheta),dedx);


       if(fabs(pfo_piddedx[ipfo])==211) pion_dEdx_pid->Fill(momentum,dedx);
       if(fabs(pfo_piddedx[ipfo])==321) kaon_dEdx_pid->Fill(momentum,dedx);
       if(fabs(pfo_piddedx[ipfo])==2212) proton_dEdx_pid->Fill(momentum,dedx);
       if(fabs(pfo_piddedx[ipfo])==11) electron_dEdx_pid->Fill(momentum,dedx);
       if(fabs(pfo_piddedx[ipfo])==13) muon_dEdx_pid->Fill(momentum,dedx);
     }
   }
 }
 n_kaon_vtx->Fill(nkaonvtx);
	//	}//btag
      }//ijet
    }//ff
  }//for

  cout << "========= Result =========" << endl;
  cout << "nEvents (after ISR cut) = " << isrcut << "\n";
  cout << "========= PFO Result =========" << "\n";
  cout << "All PFOs = " << all_pfo << "\n";
  cout << "PFOs (after mom cut) = " << nmomcut_pfo << "\n";
  cout << "PFOs (after cos cut) = " << ncoscut_pfo << "\n";  



  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);

  TCanvas* c_dEdx_truth_0 = new TCanvas("c_dEdx","c_dEdx",800,800);
  c_dEdx_truth_0->cd(1);
  gPad->SetLogx();
  pion_dEdx_truth->GetXaxis()->SetTitle("p [GeV]");
  pion_dEdx_truth->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  pion_dEdx_truth->GetYaxis()->SetTitleOffset(1.7);
  
  pion_dEdx_truth->SetMarkerColor(4);
  pion_dEdx_truth->SetMarkerStyle(1);
  pion_dEdx_truth->SetLineColor(4);
  pion_dEdx_truth->SetTitle("");
  pion_dEdx_truth->SetContour(5);
  pion_dEdx_truth->Draw("p");

  proton_dEdx_truth->SetMarkerColor(kGreen+1);
  proton_dEdx_truth->SetMarkerStyle(1);
  proton_dEdx_truth->SetLineColor(kGreen+1);
  proton_dEdx_truth->SetContour(5);
  proton_dEdx_truth->Draw("psame");

  kaon_dEdx_truth->SetMarkerColor(2);
  kaon_dEdx_truth->SetMarkerStyle(1);
  kaon_dEdx_truth->SetLineColor(2);
  kaon_dEdx_truth->SetContour(5);
  kaon_dEdx_truth->Draw("psame");


  electron_dEdx_truth->SetMarkerColor(kBlack);
  electron_dEdx_truth->SetMarkerStyle(1);
  electron_dEdx_truth->SetLineColor(kBlack);
  electron_dEdx_truth->SetContour(5);
  electron_dEdx_truth->Draw("psame");

  muon_dEdx_truth->SetMarkerColor(kGray);
  muon_dEdx_truth->SetMarkerStyle(1);
  muon_dEdx_truth->SetLineColor(kGray);
  muon_dEdx_truth->SetContour(5);
  muon_dEdx_truth->Draw("psame");

  TCanvas* c_dEdx_pid_0 = new TCanvas("c_dEdx_pid","c_dEdx_pid",800,800);
  c_dEdx_pid_0->cd(1);
  gPad->SetLogx();
  pion_dEdx_pid->GetXaxis()->SetTitle("p [GeV]");
  pion_dEdx_pid->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  pion_dEdx_pid->GetYaxis()->SetTitleOffset(1.7);
  
  pion_dEdx_pid->SetMarkerColor(4);
  pion_dEdx_pid->SetMarkerStyle(1);
  pion_dEdx_pid->SetLineColor(4);
  pion_dEdx_pid->SetTitle("");
  pion_dEdx_pid->SetContour(5);
  pion_dEdx_pid->Draw("p");

  proton_dEdx_pid->SetMarkerColor(kGreen+1);
  proton_dEdx_pid->SetMarkerStyle(1);
  proton_dEdx_pid->SetLineColor(kGreen+1);
  proton_dEdx_pid->SetContour(5);
  proton_dEdx_pid->Draw("psame");

  kaon_dEdx_pid->SetMarkerColor(2);
  kaon_dEdx_pid->SetMarkerStyle(1);
  kaon_dEdx_pid->SetLineColor(2);
  kaon_dEdx_pid->SetContour(5);
  kaon_dEdx_pid->Draw("psame");


  electron_dEdx_pid->SetMarkerColor(kBlack);
  electron_dEdx_pid->SetMarkerStyle(1);
  electron_dEdx_pid->SetLineColor(kBlack);
  electron_dEdx_pid->SetContour(5);
  electron_dEdx_pid->Draw("psame");

  muon_dEdx_pid->SetMarkerColor(kGray);
  muon_dEdx_pid->SetMarkerStyle(1);
  muon_dEdx_pid->SetLineColor(kGray);
  muon_dEdx_pid->SetContour(5);
  muon_dEdx_pid->Draw("psame");

  

  QQBARLabel(0.25,0.85,"",1);
  
  TLegend *leg1 = new TLegend(0.7,0.8,0.8,0.9);
  leg1->AddEntry(pion_dEdx_pid,"PID-dEdx #pi","lp");
  leg1->AddEntry(kaon_dEdx_pid,"PID-dEdx K","lp");
  leg1->AddEntry(proton_dEdx_pid,"PID-dEdx p","lp");
  leg1->AddEntry(muon_dEdx_pid,"PID-dEdx #mu","lp");
  leg1->AddEntry(electron_dEdx_pid,"PID-dEdx e","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
  



  TString fname="all_tracks";
  if(secondary==true) fname = "secondary_tracks";
  if(ignoreoverlay==true) fname += "_ignoreoverlay";
  if(pdg==3) fname = process;
  if(pdg==4) fname = TString::Format("output_250_%s_%s_cquark_costheta_lt08.root",fname.Data(),process.Data());
  if(pdg==5) fname = TString::Format("output_250_%s_%s_bquark_costheta_lt08.root",fname.Data(),process.Data());

  
  TFile *MyFile = new TFile(fname,"RECREATE");
  MyFile->cd();
  pion_dEdx_truth->SetName("pion");
  kaon_dEdx_truth->SetName("kaon");
  proton_dEdx_truth->SetName("proton");
  electron_dEdx_truth->SetName("electron");
  muon_dEdx_truth->SetName("muon");
  pion_dEdx_truth->Write();
  kaon_dEdx_truth->Write();
  proton_dEdx_truth->Write();
  electron_dEdx_truth->Write();
  muon_dEdx_truth->Write();
  c_dEdx_truth_0->Write();
  n_kaon_jet->Write();

  pion_dEdx_cos->SetName("pion_cos");
  kaon_dEdx_cos->SetName("kaon_cos");
  proton_dEdx_cos->SetName("proton_cos");
  electron_dEdx_cos->SetName("electron_cos");
  muon_dEdx_cos->SetName("muon_cos");
  pion_dEdx_cos->Write();
  kaon_dEdx_cos->Write();
  proton_dEdx_cos->Write();
  electron_dEdx_cos->Write();
  muon_dEdx_cos->Write();
  
  pion_dEdx_pid->SetName("pid_pion");
  kaon_dEdx_pid->SetName("pid_kaon");
  proton_dEdx_pid->SetName("pid_proton");
  electron_dEdx_pid->SetName("pid_electron");
  muon_dEdx_pid->SetName("pid_muon");
  pion_dEdx_pid->Write();
  kaon_dEdx_pid->Write();
  proton_dEdx_pid->Write();
  electron_dEdx_pid->Write();
  muon_dEdx_pid->Write();
  c_dEdx_pid_0->Write();
  
  n_kaon_vtx->Write();
  p_kaon->Write();
  p_proton->Write();
  p_pion->Write();
  p_electron->Write();
  p_muon->Write();
  p_others->Write();

  costheta_kaon->Write();
  costheta_proton->Write();
  costheta_pion->Write();
  costheta_electron->Write();
  costheta_muon->Write();
  costheta_others->Write();

  //
  p_kaon_method1->Write();
  p_proton_method1->Write();
  p_pion_method1->Write();
  p_electron_method1->Write();
  p_muon_method1->Write();
  p_others_method1->Write();

  p_kaon_method2->Write();
  p_proton_method2->Write();
  p_pion_method2->Write();
  p_electron_method2->Write();
  p_muon_method2->Write();
  p_others_method2->Write();

  //
  costheta_kaon_method1->Write();
  costheta_proton_method1->Write();
  costheta_pion_method1->Write();
  costheta_electron_method1->Write();
  costheta_muon_method1->Write();
  costheta_others_method1->Write();

  costheta_kaon_method2->Write();
  costheta_proton_method2->Write();
  costheta_pion_method2->Write();
  costheta_electron_method2->Write();
  costheta_muon_method2->Write();
  costheta_others_method2->Write();

  //
  p_costheta_kaon_method1->Write();
  p_costheta_proton_method1->Write();
  p_costheta_pion_method1->Write();
  p_costheta_electron_method1->Write();
  p_costheta_muon_method1->Write();
  p_costheta_others_method1->Write();

  p_costheta_kaon_method2->Write();
  p_costheta_proton_method2->Write();
  p_costheta_pion_method2->Write();
  p_costheta_electron_method2->Write();
  p_costheta_muon_method2->Write();
  p_costheta_others_method2->Write();

  //
  likelihood_kaon_method1->Write();
  likelihood_proton_method1->Write();
  likelihood_pion_method1->Write();
  likelihood_electron_method1->Write();
  likelihood_muon_method1->Write();
  likelihood_others_method1->Write();

  likelihood_kaon_method2->Write();
  likelihood_proton_method2->Write();
  likelihood_pion_method2->Write();
  likelihood_electron_method2->Write();
  likelihood_muon_method2->Write();
  likelihood_others_method2->Write();

  //
  k_prob_kaon_method1->Write();
  k_prob_proton_method1->Write();
  k_prob_pion_method1->Write();
  k_prob_electron_method1->Write();
  k_prob_muon_method1->Write();
  k_prob_others_method1->Write();

  k_prob_kaon_method2->Write();
  k_prob_proton_method2->Write();
  k_prob_pion_method2->Write();
  k_prob_electron_method2->Write();
  k_prob_muon_method2->Write();
  k_prob_others_method2->Write();

  //
  pi_prob_kaon_method1->Write();
  pi_prob_proton_method1->Write();
  pi_prob_pion_method1->Write();
  pi_prob_electron_method1->Write();
  pi_prob_muon_method1->Write();
  pi_prob_others_method1->Write();

  pi_prob_kaon_method2->Write();
  pi_prob_proton_method2->Write();
  pi_prob_pion_method2->Write(); ;
  pi_prob_electron_method2->Write(); 
  pi_prob_muon_method2->Write(); ;
  pi_prob_others_method2->Write(); 

  //
  k_pi_prob_kaon_method1->Write(); 
  k_pi_prob_proton_method1->Write(); 
  k_pi_prob_pion_method1->Write(); 
  k_pi_prob_electron_method1->Write(); 
  k_pi_prob_muon_method1->Write(); 
  k_pi_prob_others_method1->Write(); 

  k_pi_prob_kaon_method2->Write();
  k_pi_prob_proton_method2->Write(); 
  k_pi_prob_pion_method2->Write(); 
  k_pi_prob_electron_method2->Write(); 
  k_pi_prob_muon_method2->Write(); 
  k_pi_prob_others_method2->Write(); 

  
  kdEdx_dist_kaon->Write();
  kdEdx_dist_proton->Write();
  kdEdx_dist_pion->Write();
  kdEdx_dist_electron->Write();
  kdEdx_dist_muon->Write();
  kdEdx_dist_others->Write();

  p_kdEdx_dist_kaon->Write();
  p_kdEdx_dist_proton->Write();
  p_kdEdx_dist_pion->Write();
  p_kdEdx_dist_electron->Write();
  p_kdEdx_dist_muon->Write();
  p_kdEdx_dist_others->Write();

  costheta_kdEdx_dist_kaon->Write();
  costheta_kdEdx_dist_proton->Write();
  costheta_kdEdx_dist_pion->Write();
  costheta_kdEdx_dist_electron->Write();
  costheta_kdEdx_dist_muon->Write();
  costheta_kdEdx_dist_others->Write();

  n_costheta_kaon->Write();

  MyFile->Close();
  
  
}







