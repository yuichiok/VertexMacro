
#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"


void QQbarAnalysisClass::JetTag(int n_entries=-1, int selection_type=0, float Kvcut=2500)
{
  
  TFile *MyFile = new TFile(TString::Format("jettag_%s_250GeV.root",process.Data()),"RECREATE");
  MyFile->cd();

 
  TH1F * h_jet_btag[40];
  TH1F * h_jet_ctag[40];

  for(int i=0; i<40;i++) {
    h_jet_btag[i]= new TH1F(TString::Format("h_jet_btag_%i",i),TString::Format("h_jet_btag_%i",i),6,-0.5,5.5);
    h_jet_ctag[i]= new TH1F(TString::Format("h_jet_ctag_%i",i),TString::Format("h_jet_ctag_%i",i),6,-0.5,5.5);
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

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    float Kv=Kreco();
    //parte importante
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;
    if(gamma_e>Kvcut) continue;


    for(int ijet=0; ijet<2; ijet++) {
      for(int j=0; j<40;j++) {
	double tag=j*0.025;
	if(jet_btag[ijet]>tag) {
	  if(fabs(mc_quark_pdg[0])<4) h_jet_btag[j]->Fill(0);
	  h_jet_btag[j]->Fill(fabs(mc_quark_pdg[0]));
	}
	if(jet_ctag[ijet]>tag) {
	  if(fabs(mc_quark_pdg[0])<4) h_jet_ctag[j]->Fill(0);
	  h_jet_ctag[j]->Fill(fabs(mc_quark_pdg[0]));
	}
      }//for tag
    }//for ijet

  }//jentry
  
  for(int i=0; i<40;i++) {
    h_jet_btag[i]->Write();
    h_jet_ctag[i]->Write();
  }

}

void QQbarAnalysisClass::Selection(int n_entries=-1, int selection_type=0, float Kvcut=2500, int bkg=0)
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV.root",process.Data()),"RECREATE");
  MyFile->cd();

  
  float   bb_gen=0,  bb_radreturn_gen=0,  qq_gen=0,   qq_radreturn_gen=0,   cc_gen=0,   cc_radreturn_gen=0;
  float   bb_counter=0,  bb_radreturn_counter=0,  qq_counter=0,   qq_radreturn_counter=0,   cc_counter=0,   cc_radreturn_counter=0;

  //costheta_nocuts
  TH1F * h_costheta_nocuts = new TH1F("h_costheta_nocuts","h_costheta_nocuts",20,0,1);

  //costheta
  TH1F * h_costheta_th_vs_lab_bb = new TH1F("h_costheta_th_vs_lab_bb","h_costheta_th_vs_lab_bb",4000,-1,1);
  TH1F * h_costheta_th_vs_lab_qq = new TH1F("h_costheta_th_vs_lab_qq","h_costheta_th_vs_lab_qq",4000,-1,1);
  TH1F * h_costheta_th_vs_lab_cc = new TH1F("h_costheta_th_vs_lab_cc","h_costheta_th_vs_lab_cc",4000,-1,1);
  TH1F * h_costheta_th_vs_lab_radreturn = new TH1F("h_costheta_th_vs_lab_radreturn","h_costheta_th_vs_lab_radreturn",4000,-1,1);

//costheta
  TH1F * h_costheta_bb = new TH1F("h_costheta_bb","h_costheta_bb",20,0,1);
  TH1F * h_costheta_qq = new TH1F("h_costheta_qq","h_costheta_qq",20,0,1);
  TH1F * h_costheta_cc = new TH1F("h_costheta_cc","h_costheta_cc",20,0,1);
  TH1F * h_costheta_radreturn = new TH1F("h_costheta_radreturn","h_costheta_radreturn",20,0,1);

  //invariant mass
  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);
  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_mjj_cc = new TH1F("h_mjj_cc","h_mjj_cc",100,0,500);

  //K
  TH1F * h_K = new TH1F("h_K","h_K",2000,0,200);
  TH1F * h_K_bb = new TH1F("h_K_bb","h_K_bb",2000,0,200);
  TH1F * h_K_radreturn = new TH1F("h_K_radreturn","h_K_radreturn",2000,0,200);
  TH1F * h_K_qq = new TH1F("h_K_qq","h_K_qq",2000,0,200);
  TH1F * h_K_cc = new TH1F("h_K_cc","h_K_cc",2000,0,200);

  TH1F * h_K_parton_bb = new TH1F("h_K_parton_bb","h_K_parton_bb",2000,0,200);
  TH1F * h_K_parton_radreturn = new TH1F("h_K_parton_radreturn","h_K_parton_radreturn",2000,0,200);
  TH1F * h_K_parton_qq = new TH1F("h_K_parton_qq","h_K_parton_qq",2000,0,200);
  TH1F * h_K_parton_cc = new TH1F("h_K_parton_cc","h_K_parton_cc",2000,0,200);

  TH2F * h_K_parton_K_bb = new TH2F("h_K_parton_K_bb","h_K_parton_K_bb",200,0,200,200,0,200);
  TH2F * h_K_parton_K_radreturn = new TH2F("h_K_parton_K_radreturn","h_K_parton_K_radreturn",200,0,200,200,0,200);
  TH2F * h_K_parton_K_qq = new TH2F("h_K_parton_K_qq","h_K_parton_K_qq",200,0,200,200,0,200);
  TH2F * h_K_parton_K_cc = new TH2F("h_K_parton_K_cc","h_K_parton_K_cc",200,0,200,200,0,200);
  
  // NPFOs
  //------------------------
  TH2F * h_photon_npfos_qq = new TH2F("h_photon_npfos_qq","h_photon_npfos_qq",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_cc = new TH2F("h_photon_npfos_cc","h_photon_npfos_cc",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_bb = new TH2F("h_photon_npfos_bb","h_photon_npfos_bb",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_radreturn = new TH2F("h_photon_npfos_radreturn","h_photon_npfos_radreturn",51,-0.5,50.5,51,-0.5,50.5);

  TH2F * h_charge_npfos_qq = new TH2F("h_charge_npfos_qq","h_charge_npfos_qq",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_cc = new TH2F("h_charge_npfos_cc","h_charge_npfos_cc",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_bb = new TH2F("h_charge_npfos_bb","h_charge_npfos_bb",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_radreturn = new TH2F("h_charge_npfos_radreturn","h_charge_npfos_radreturn",51,-0.5,50.5,51,-0.5,50.5);

  TH2F * h_npfos_bb = new TH2F("h_npfos_bb","h_npfos_bb",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_radreturn = new TH2F("h_npfos_radreturn","h_npfos_radreturn",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_qq = new TH2F("h_npfos_qq","h_npfos_qq",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_cc = new TH2F("h_npfos_cc","h_npfos_cc",101,-0.5,100.5,101,-0.5,100.5);
  

  //jet algorithm variables
  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",4000,0,0.25);
  TH1F * h_y23_radreturn = new TH1F("h_y23_radreturn","h_y23_radreturn",4000,0,0.25);
  TH1F * h_y23_qq = new TH1F("h_y23_qq","h_y23_qq",4000,0,0.25);
  TH1F * h_y23_cc = new TH1F("h_y23_cc","h_y23_cc",4000,0,0.25);

  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",5000,-0.5,4999.5);
  TH1F * h_d23_radreturn = new TH1F("h_d23_radreturn","h_d23_radreturn",5000,-0.5,4999.5);
  TH1F * h_d23_qq = new TH1F("h_d23_qq","h_d23_qq",5000,-0.5,4999.5);
  TH1F * h_d23_cc = new TH1F("h_d23_cc","h_d23_cc",5000,-0.5,4999.5);

  TH1F * h_thrust_bb = new TH1F("h_thrust_bb","h_thrust_bb",400,0,1);
  TH1F * h_thrust_radreturn = new TH1F("h_thrust_radreturn","h_thrust_radreturn",400,0,1);
  TH1F * h_thrust_qq = new TH1F("h_thrust_qq","h_thrust_qq",400,0,1);
  TH1F * h_thrust_cc = new TH1F("h_thrust_cc","h_thrust_cc",400,0,1);

   //mass of two jets
  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",400,0,200);
  TH1F * h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",400,0,200);
  TH1F * h_mj1_mj2_qq = new TH1F("h_mj1_mj2_qq","h_mj1_mj2_qq",400,0,200);
  TH1F * h_mj1_mj2_cc = new TH1F("h_mj1_mj2_cc","h_mj1_mj2_cc",400,0,200);
 
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

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bb_gen++;
    }
    if(gamma_e>Kvcut ) {
      if(fabs(mc_quark_pdg[0])==5) bb_radreturn_gen++;
      if(fabs(mc_quark_pdg[0])==4) cc_radreturn_gen++;
      if(fabs(mc_quark_pdg[0])<4) qq_radreturn_gen++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_gen++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_gen++;
    }


    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco stuff
    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));

    float costheta_bbbar;
    std::vector<float> p_bbbar;
    p_bbbar.push_back(jet_px[0]-jet_px[1]);
    p_bbbar.push_back(jet_py[0]-jet_py[1]);
    p_bbbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta_bbbar=fabs(GetCostheta(p_bbbar));

    
    float costheta_thrust;
    std::vector<float> p_thrust;
    p_thrust.push_back(principle_thrust_axis[0]);
    p_thrust.push_back(principle_thrust_axis[1]);
    p_thrust.push_back(principle_thrust_axis[2]);
    costheta_thrust=fabs(GetCostheta(p_thrust));
    
    h_costheta_nocuts->Fill(costheta_bbbar);

    float Kv=Kreco();
    //parte importante
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;

    //pfos identificados como fotones o como cargados?
    //---------------------
    //Radiative return cuts, photon INSIDE the detector
    PFOphotonQuantities();
    // HASTA AQUI Las cosas de PFOs

    if(bkg==1)  {

      h_costheta_th_vs_lab_bb->Fill(costheta_bbbar-costheta_thrust);
      h_costheta_bb->Fill(costheta_bbbar);
      h_mjj_bb->Fill(reco_bbmass);

      h_photon_npfos_bb->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_bb->Fill(npfo[0],npfo[1]);
      h_charge_npfos_bb->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
     
      h_y23_bb->Fill(d23/pow(reco_bbmass,2));
      h_d23_bb->Fill(d23);
      h_thrust_bb->Fill(principle_thrust_value);

      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);

      h_K_bb->Fill(Kv);
      h_K_parton_bb->Fill(gamma_e);
      h_K_parton_K_bb->Fill(gamma_e,Kv);
    } else  {

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bb_counter++;
    }
    if(gamma_e>Kvcut ) {
      if(fabs(mc_quark_pdg[0])==5) bb_radreturn_counter++;
      if(fabs(mc_quark_pdg[0])==4) cc_radreturn_counter++;
      if(fabs(mc_quark_pdg[0])<4)qq_radreturn_counter++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_counter++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_counter++;
    }
    
    if(gamma_e>Kvcut) {
   
      h_costheta_th_vs_lab_radreturn->Fill(costheta_bbbar-costheta_thrust);
      h_costheta_radreturn->Fill(costheta_bbbar);
      h_mjj_radreturn->Fill(reco_bbmass);

      h_photon_npfos_radreturn->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_radreturn->Fill(npfo[0],npfo[1]);
      h_charge_npfos_radreturn->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
      h_y23_radreturn->Fill(d23/pow(reco_bbmass,2));
      h_d23_radreturn->Fill(d23);
      h_thrust_radreturn->Fill(principle_thrust_value);
      h_mj1_mj2_radreturn->Fill(reco_b1mass+reco_b2mass);

      h_K_radreturn->Fill(Kv);
      h_K_parton_radreturn->Fill(gamma_e);
      h_K_parton_K_radreturn->Fill(gamma_e,Kv);
    }


    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
   
      h_costheta_th_vs_lab_bb->Fill(costheta_bbbar-costheta_thrust);
      h_costheta_bb->Fill(costheta_bbbar);

      h_mjj_bb->Fill(reco_bbmass);

      h_photon_npfos_bb->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_bb->Fill(npfo[0],npfo[1]);
      h_charge_npfos_bb->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
     
      h_y23_bb->Fill(d23/pow(reco_bbmass,2));
      h_d23_bb->Fill(d23);
      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
      h_thrust_bb->Fill(principle_thrust_value);

      h_K_bb->Fill(Kv);
      h_K_parton_bb->Fill(gamma_e);
      h_K_parton_K_bb->Fill(gamma_e,Kv);
    }

    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) {
   
      h_costheta_th_vs_lab_cc->Fill(costheta_bbbar-costheta_thrust);
      h_costheta_cc->Fill(costheta_bbbar);
      h_mjj_cc->Fill(reco_bbmass);

      h_photon_npfos_cc->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_cc->Fill(npfo[0],npfo[1]);
      h_charge_npfos_cc->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
    
      h_y23_cc->Fill(d23/pow(reco_bbmass,2));
      h_d23_cc->Fill(d23);
      h_mj1_mj2_cc->Fill(reco_b1mass+reco_b2mass);
      h_thrust_cc->Fill(principle_thrust_value);

      h_K_cc->Fill(Kv);
      h_K_parton_cc->Fill(gamma_e);
      h_K_parton_K_cc->Fill(gamma_e,Kv);
    }

    if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) {
   
      h_costheta_th_vs_lab_qq->Fill(costheta_bbbar-costheta_thrust);
      h_costheta_qq->Fill(costheta_bbbar);
      h_mjj_qq->Fill(reco_bbmass);

      h_photon_npfos_qq->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_qq->Fill(npfo[0],npfo[1]);
      h_charge_npfos_qq->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
    
      h_y23_qq->Fill(d23/pow(reco_bbmass,2));
      h_d23_qq->Fill(d23);
      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_thrust_qq->Fill(principle_thrust_value);

      h_K_qq->Fill(Kv);
      h_K_parton_qq->Fill(gamma_e);
      h_K_parton_K_qq->Fill(gamma_e,Kv);
    }
    }
  }
  cout<<TString::Format("selection_%s_250GeV.root",process.Data())<<endl;
  cout<<" Total generated events: bb cc qq bb(rad) cc(rad) qq(rad)" <<endl;
  cout<<"                     "<<bb_gen<<" "<<cc_gen<<" "<<qq_gen<<" "<<bb_radreturn_gen<<" "<<cc_radreturn_gen<<" "<<qq_radreturn_gen<<endl;
  cout<<" aftercuts  "<<bb_counter<<" "<<cc_counter<<" "<<qq_counter<<" "<<bb_radreturn_counter<<" "<<cc_radreturn_counter<<" "<<qq_radreturn_counter<<endl;

  //  cout<<" Total generated Z-radreturn events: " <<radreturn_counter<<endl;
  //cout<<" Total generated qqbar events: " << qq_counter<<endl;
  //cout<<" Total generated ccbar events: " << cc_counter<<endl;

  // save histograms
  h_costheta_nocuts->Write();
      
  h_mjj_bb->Write();
  h_mjj_qq->Write();
  h_mjj_cc->Write();
  h_mjj_radreturn->Write();

  h_costheta_bb->Write();
  h_costheta_qq->Write();
  h_costheta_cc->Write();
  h_costheta_radreturn->Write();
 
  h_costheta_th_vs_lab_bb->Write();
  h_costheta_th_vs_lab_qq->Write();
  h_costheta_th_vs_lab_cc->Write();
  h_costheta_th_vs_lab_radreturn->Write();

  h_photon_npfos_bb->Write();
  h_photon_npfos_cc->Write();
  h_photon_npfos_qq->Write();
  h_photon_npfos_radreturn->Write();
  
  h_charge_npfos_bb->Write();
  h_charge_npfos_cc->Write();
  h_charge_npfos_qq->Write();
  h_charge_npfos_radreturn->Write();

  h_npfos_bb->Write();
  h_npfos_cc->Write();
  h_npfos_qq->Write();
  h_npfos_radreturn->Write();

  h_y23_bb->Write();
  h_y23_qq->Write();
  h_y23_cc->Write();
  h_y23_radreturn->Write();

  h_d23_bb->Write();
  h_d23_qq->Write();
  h_d23_cc->Write();
  h_d23_radreturn->Write();

  h_thrust_bb->Write();
  h_thrust_qq->Write();
  h_thrust_cc->Write();
  h_thrust_radreturn->Write();

  h_mj1_mj2_bb->Write();
  h_mj1_mj2_qq->Write();
  h_mj1_mj2_cc->Write();
  h_mj1_mj2_radreturn->Write();

  h_K->Write();
  h_K_bb->Write();
  h_K_qq->Write();
  h_K_cc->Write();
  h_K_radreturn->Write();
  
  h_K_parton_bb->Write();
  h_K_parton_qq->Write();
  h_K_parton_cc->Write();
  h_K_parton_radreturn->Write();

  h_K_parton_K_bb->Write();
  h_K_parton_K_qq->Write();
  h_K_parton_K_cc->Write();
  h_K_parton_K_radreturn->Write();

   
}


