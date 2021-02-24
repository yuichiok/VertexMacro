#define kaon_info_cxx
#include "kaon_info.h"
#include <math.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void kaon_info::Analysis(int n_entries=-1, TString polarization="eL", float pwr=0.1, float Kvcut=35)
{

  preselection = 0;

////
  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.33,1.667,2,2.5,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,32,36,40,44,48,52,56,60,64,68,72,80,90,100};
        //13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
    Int_t nbinnumy=199;

  TH1F* cosKaon_truth = new TH1F("cosKaon_truth","cosKaon_truth",nbins,0.,1.0);
  TH1F* cosKaon_reco  = new TH1F("cosKaon_reco","cosKaon_reco",nbins,0.,1.0);
  TH1F* p_Kaon_truth = new TH1F("p_Kaon_truth","p_Kaon_truth",nbins,0.,100.0);
  TH1F* p_Kaon_reco  = new TH1F("p_Kaon_reco","p_Kaon_reco",nbins,0.,100.0);
  cosKaon_truth->Sumw2();
  cosKaon_reco->Sumw2();
  p_Kaon_truth->Sumw2();
  p_Kaon_reco->Sumw2();

  TH2F* kaon_dEdx_truth     = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* proton_dEdx_truth   = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pion_dEdx_truth     = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* electron_dEdx_truth = new TH2F("electron_dEdx_truth","electron_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* muon_dEdx_truth     = new TH2F("muon_dEdx_truth","muon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  TH2F* kaon_dEdx_cos_truth     = new TH2F("kaon_dEdx_cos_truth","kaon_dEdx_cos_truth",nbins,0.,1.0,200,0.1,0.3);
  TH2F* proton_dEdx_cos_truth   = new TH2F("proton_dEdx_cos_truth","proton_dEdx_cos_truth",nbins,0.,1.0,200,0.1,0.3);
  TH2F* pion_dEdx_cos_truth     = new TH2F("pion_dEdx_cos_truth","pion_dEdx_cos_truth",nbins,0.,1.0,200,0.1,0.3);
  TH2F* electron_dEdx_cos_truth = new TH2F("electron_dEdx_cos_truth","electron_dEdx_cos_truth",nbins,0.,1.0,200,0.1,0.3);
  TH2F* muon_dEdx_cos_truth     = new TH2F("muon_dEdx_cos_truth","muon_dEdx_cos_truth",nbins,0.,1.0,200,0.1,0.3);

  TH2F* kaon_dEdx_cos_corr      = new TH2F("kaon_dEdx_cos_corr",";|cos#theta|;#frac{dE}{dx} [MeV]",nbins,0.,1.0,200,0.1,0.3);

  TH2F* kaon_dEdx_rad_truth     = new TH2F("kaon_dEdx_rad_truth",";rad;#frac{dE}{dx} [MeV]",nbins,0.,M_PI/2.0,200,0.1,0.3);
  TH2F* proton_dEdx_rad_truth   = new TH2F("proton_dEdx_rad_truth",";rad;#frac{dE}{dx} [MeV]",nbins,0.,M_PI/2.0,200,0.1,0.3);
  TH2F* pion_dEdx_rad_truth     = new TH2F("pion_dEdx_rad_truth",";rad;#frac{dE}{dx} [MeV]",nbins,0.,M_PI/2.0,200,0.1,0.3);
  TH2F* electron_dEdx_rad_truth = new TH2F("electron_dEdx_rad_truth",";rad;#frac{dE}{dx} [MeV]",nbins,0.,M_PI/2.0,200,0.1,0.3);
  TH2F* muon_dEdx_rad_truth     = new TH2F("muon_dEdx_rad_truth",";rad;#frac{dE}{dx} [MeV]",nbins,0.,M_PI/2.0,200,0.1,0.3);

  TH2F* kaon_dEdx_rad_corr      = new TH2F("kaon_dEdx_rad_corr",";rad;#frac{dE}{dx} [MeV]",nbins,0.,M_PI/2.0,200,0.1,0.3);

  TH2I* pdg_selec = new TH2I("pdg_selec","pdg_selec",3,0,3,3,0,3);
  pdg_selec->SetCanExtend(TH1::kAllAxes);

  TH1F* cosKaon_eff = new TH1F("cosKaon_eff","cosKaon_eff",nbins,0.,1.0);
  TH1F* p_Kaon_eff  = new TH1F("p_Kaon_eff","p_Kaon_eff",nbins,0.,100.0);
  cosKaon_eff->Sumw2();
  p_Kaon_eff->Sumw2();


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e + gamma1_e;//_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));// gamma0_e+gamma1_e;
    float Kv_p=gamma_e;

    // //costheta parton
    // float costheta_bbbar;
    // std::vector<float> p_bbar;
    // p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    // p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    // p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    // costheta_bbbar=GetCostheta(p_bbar);
    
    
    // // gen info
    // if(fabs(mc_quark_pdg[0])==5 && Kv_p<Kvcut) {
    //   bbbar_gen++;
    //   h_cos_parton->Fill(costheta_bbbar);
    //   h_cos_parton->Fill(-costheta_bbbar);
      
    //   costheta_bbbar=  (mc_quark_charge[0] < 0) ? costheta_bbbar: -costheta_bbbar;
    //   h_bbbar->Fill( costheta_bbbar );
    // }


    // angle for jets reconstructed only with secondary vertex tracks
   //  float ptrack_x=0;
   //  float ptrack_y=0;
   //  float ptrack_z=0;

   //  for(int ivtx=0; ivtx<jet_nvtx[0]; ivtx++) {
   //    for(int itrack=0; itrack<jet_vtx_ntrack[0][ivtx]; itrack++) {
   //      ptrack_x+=jet_track_px[0][ivtx][itrack];
   //      ptrack_y+=jet_track_py[0][ivtx][itrack];
   //      ptrack_z+=jet_track_pz[0][ivtx][itrack];
   //    }
   //  }

   // for(int ivtx=0; ivtx<jet_nvtx[1]; ivtx++) {
   //    for(int itrack=0; itrack<jet_vtx_ntrack[1][ivtx]; itrack++) {
   //      ptrack_x-=jet_track_px[1][ivtx][itrack];
   //      ptrack_y-=jet_track_py[1][ivtx][itrack];
   //      ptrack_z-=jet_track_pz[1][ivtx][itrack];
   //    }
   //  }

   //  std::vector<float> ptracks;
   //  ptracks.push_back(ptrack_x);
   //  ptracks.push_back(ptrack_y);
   //  ptracks.push_back(ptrack_z);
   //  float costheta_tracks=GetCostheta(ptracks);

    if(PreSelection(5,Kvcut)==false) continue;

    preselection++;

    for(int ijet=0; ijet<2; ijet++) {

      for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {

        for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {

          std::vector<float> track_p_vec;
          track_p_vec.push_back(jet_track_px[ijet][ivtx][itrack]);
          track_p_vec.push_back(jet_track_py[ijet][ivtx][itrack]);
          track_p_vec.push_back(jet_track_pz[ijet][ivtx][itrack]);
          // float abs_rad_track = fabs(GetTheta(track_p_vec));
          float abs_cos_track = fabs(GetCostheta(track_p_vec));
          float abs_rad_track = acos(abs_cos_track);

          float track_p    = jet_track_p[ijet][ivtx][itrack];
          float track_dedx = jet_track_dedx[ijet][ivtx][itrack];
          float dedx_corr  = track_dedx * pow(abs_rad_track,pwr);

          bool iskaon_reco = checkParticle(track_p,track_dedx, 321);
          bool ispion_reco = checkParticle(track_p,track_dedx, 211);
          bool isproton_reco = checkParticle(track_p,track_dedx, 2212);

          int particleGen  = -1;
          int particleReco = -1;

          if(iskaon_reco==true){

            particleReco = 1;

            cosKaon_reco->Fill(abs_cos_track);
            p_Kaon_reco->Fill(track_p);

            cosKaon_eff->Fill(abs_cos_track);
            p_Kaon_eff->Fill(track_p);
          }

          if(ispion_reco==true) particleReco = 0;
          if(isproton_reco==true) particleReco = 2;


          if(jet_track_pdg[ijet][ivtx][itrack]==321){

            particleGen = 1;

            cosKaon_truth->Fill(abs_cos_track);
            p_Kaon_truth->Fill(track_p);
            kaon_dEdx_truth->Fill(track_p,track_dedx);
            
            kaon_dEdx_cos_truth->Fill(abs_cos_track,track_dedx);
            kaon_dEdx_cos_corr->Fill(abs_cos_track,dedx_corr);

            kaon_dEdx_rad_truth->Fill(abs_rad_track,track_dedx);
            kaon_dEdx_rad_corr->Fill(abs_rad_track,dedx_corr);
          }

          if(jet_track_pdg[ijet][ivtx][itrack]==211){

            particleGen = 0;

            pion_dEdx_truth->Fill(track_p,track_dedx);
            pion_dEdx_cos_truth->Fill(abs_cos_track,track_dedx);
            pion_dEdx_rad_truth->Fill(abs_rad_track,track_dedx);
          }

          if(jet_track_pdg[ijet][ivtx][itrack]==2212){

            particleGen = 2;

            proton_dEdx_truth->Fill(track_p,track_dedx);
            proton_dEdx_cos_truth->Fill(abs_cos_track,track_dedx);
            proton_dEdx_rad_truth->Fill(abs_rad_track,track_dedx);
          }

          if(jet_track_pdg[ijet][ivtx][itrack]==11){
            electron_dEdx_truth->Fill(track_p,track_dedx);
            electron_dEdx_cos_truth->Fill(abs_cos_track,track_dedx);
            electron_dEdx_rad_truth->Fill(abs_rad_track,track_dedx);
          }

          if(jet_track_pdg[ijet][ivtx][itrack]==13){
            muon_dEdx_truth->Fill(track_p,track_dedx);
            muon_dEdx_cos_truth->Fill(abs_cos_track,track_dedx);
            muon_dEdx_rad_truth->Fill(abs_rad_track,track_dedx);
          }

          if(particleGen!=-1 && particleReco!=-1) pdg_selec->Fill(particleReco,particleGen);

        } // end track

      } // end vtx

    } // end jet

    // check run
    // if(preselection == 50000) break;

  } // end event


  TH2MeanGraph(kaon_dEdx_rad_corr);



  std::vector<TH2F*> result;
  result.push_back(kaon_dEdx_truth);
  result.push_back(proton_dEdx_truth);
  result.push_back(pion_dEdx_truth);
  result.push_back(electron_dEdx_truth);
  result.push_back(muon_dEdx_truth);

  result.push_back(kaon_dEdx_cos_truth);
  result.push_back(proton_dEdx_cos_truth);
  result.push_back(pion_dEdx_cos_truth);
  result.push_back(electron_dEdx_cos_truth);
  result.push_back(muon_dEdx_cos_truth);

  result.push_back(kaon_dEdx_rad_truth);
  result.push_back(proton_dEdx_rad_truth);
  result.push_back(pion_dEdx_rad_truth);
  result.push_back(electron_dEdx_rad_truth);
  result.push_back(muon_dEdx_rad_truth);

  result.push_back(kaon_dEdx_cos_corr);
  result.push_back(kaon_dEdx_rad_corr);


  cosKaon_eff->Divide(cosKaon_truth);
  p_Kaon_eff->Divide(p_Kaon_truth);

  std::vector<TH1F*> result2;
  result2.push_back(cosKaon_truth);
  result2.push_back(cosKaon_reco);
  result2.push_back(p_Kaon_truth);
  result2.push_back(p_Kaon_reco);
  result2.push_back(cosKaon_eff);
  result2.push_back(p_Kaon_eff);

  std::vector<TH2I*> result3;
  result3.push_back(pdg_selec);

  //DeleteHistograms(result,result2,result3);
  SaveRootFile(result,result2,result3,polarization);


}

void kaon_info::TH2MeanGraph(TH2F* hist){

  float x_kaon[200], y_kaon[200], ey_kaon[200], ey_kaon2[200];
  float ex[200];
  int nXbins = hist->GetNbinsX();

  for(int i = 0; i < nXbins; i++){

      TH1D * proj_kaon = hist->ProjectionY("proj_kaon",i,i+1);
       
      x_kaon[i]   = hist->GetXaxis()->GetBinCenter(i+1);
      y_kaon[i]   = proj_kaon->GetMean();
      // ey_kaon[i]  = proj_kaon->GetRMS();
      ey_kaon2[i] = proj_kaon->GetMean()/sqrt(proj_kaon->GetEntries());
      ex[i]       = hist->GetXaxis()->GetBinWidth(i+1)/2.;

  }

  TGraphErrors *kaonproj= new TGraphErrors(nXbins,x_kaon,y_kaon,ex,ey_kaon2);

  TF1 *f1= new TF1("f1","[0]+[1]*TMath::Power(x+[2],[3])",0.199,M_PI/2.0);
  f1->SetParameters(0.072,0.072,0.002,0.139);
  kaonproj->Fit(f1,"REM");

  // TCanvas* c1 = new TCanvas("c1","canvas",500,500);
  // kaonproj->Draw("ALP");
  // f1->Draw("same");

}

void kaon_info::DeleteHistograms(std::vector<TH2F*> th2f, std::vector<TH1F*> th1f, std::vector<TH2I*> th2i){

  for(unsigned i=0; i<th2f.size(); i++) delete th2f[i];

  for (unsigned i = 0; i < th1f.size(); ++i) delete th1f[i];
    
  for (unsigned i = 0; i < th2i.size(); ++i) delete th2i[i];

}

void kaon_info::SaveRootFile(std::vector<TH2F*> th2f, std::vector<TH1F*> th1f, std::vector<TH2I*> th2i, TString polarization="eL"){

  TFile *MyFile = new TFile(TString::Format("%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f_nbins%i_noCheat_adrian.root",process.Data(),polarization.Data(),btag1,btag2,nbins),"RECREATE");
  MyFile->cd();

  for(unsigned i=0; i<th2f.size(); i++) th2f[i]->Write();

  for (unsigned i = 0; i < th1f.size(); ++i) th1f[i]->Write();
    
  for (unsigned i = 0; i < th2i.size(); ++i) th2i[i]->Write();

  MyFile->Close();
  

}

bool kaon_info::JetBtag(int ijet) {

  double btagv=0;
  if(ijet==0) btagv=btag1;
  if(ijet==1) btagv=btag2;
  
  if(jet_btag[ijet]<btagv) return false;


  double momvertex=0;

  double mom_x=0, mom_y=0, mom_z=0;
  double e=0;
  double nt=0;
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      nt++;
      e+=jet_track_E[ijet][ivtx][itrack];
      mom_x+=jet_track_px[ijet][ivtx][itrack];
      mom_y+=jet_track_py[ijet][ivtx][itrack];
      mom_z+=jet_track_pz[ijet][ivtx][itrack];
    }
  }

  double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
  momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );

  if(momvertex<25) return false;  

  
  //  if(ChargeKcJet(ijet)!=0) return true;
  //if(ChargeBcJet(ijet)!=0) return true;

  return true;

}

bool kaon_info::PreSelection(int type=0,float Kvcut=25) {

  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
  TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
  float acol=GetSinacol(v1,v2);
  
  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

  float costheta_j0;
  std::vector<float> p_j0;
  p_j0.push_back(jet_px[0]);
  p_j0.push_back(jet_py[0]);
  p_j0.push_back(jet_pz[0]);
  costheta_j0=fabs(GetCostheta(p_j0));

  float costheta_j1;
  std::vector<float> p_j1;
  p_j1.push_back(jet_px[1]);
  p_j1.push_back(jet_py[1]);
  p_j1.push_back(jet_pz[1]);
  costheta_j1=fabs(GetCostheta(p_j1));
  
  float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
  float K1=jet0_p*acol/sqrt(1-costheta_j1*costheta_j1);
  float K2=jet1_p*acol/sqrt(1-costheta_j0*costheta_j0);

  if(type == 1 )  if( Kv < Kvcut ) return true;
  if(type == 2 )  if( Kv < Kvcut && bbmass>130 )  return true;


  //************************************************
  float photonness[2]={-1};
  float photon_energy=0;
  double npfo[2]={0};
  float costheta=0;
  float energy=0;


  for(int ijet=0; ijet<2; ijet++) {
    float energy_neut=0;
    npfo[ijet]=jet_pfo_n[ijet];
    float costheta_jet=0;
    for(int ipfo=0; ipfo<jet_pfo_n[ijet]; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      if(jet_pfo_E[ijet][ipfo]<0.1) continue;
      if( jet_pfo_type[ijet][ipfo]==22  || fabs(jet_pfo_type[ijet][ipfo])==2112 ) {
        std::vector<float> p_pfo;
        p_pfo.push_back(jet_pfo_px[ijet][ipfo]);
        p_pfo.push_back(jet_pfo_py[ijet][ipfo]);
        p_pfo.push_back(jet_pfo_pz[ijet][ipfo]);

        float costheta_pfo=GetCostheta(p_pfo);
        energy_neut += jet_pfo_E[ijet][ipfo];
        costheta_jet+= jet_pfo_E[ijet][ipfo] * costheta_pfo;
      }
    }//ipfo
    photonness[ijet]=energy_neut/jet_E[ijet];
    if(energy_neut>energy) {
      energy=energy_neut;
      costheta=costheta_jet;
    }
  }
  if(energy>0) costheta/=energy;
  
  ///***********************************************
  bool ISR_1=true;
  if(photonness[0]<0.85 && photonness[1]<0.85) ISR_1=false; //outdated!

  bool ISR_2=true;
  if(npfo[0]>4 && npfo[1]>4) ISR_2=false; //cut to remove the photon conversion events

  bool ISR_3=true;
  if(energy<100) ISR_3=false;

  bool ISR_4=true;
  if(energy<70 || fabs(costheta)<0.95) ISR_4=false;

  
  if(type == 0 ) return true;
  
  if(type == -1 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false ) return true;
  if(type == -2 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false && ISR_2==false ) return true;
  
  if(type == 1 )  if( Kv < Kvcut ) return true;
  if(type == 2 )  if( Kv < Kvcut && bbmass>130 )  return true;
  if(type == 3 )  if(  ISR_2==false && ISR_3==false && ISR_4==false && bbmass>130 && Kv < Kvcut)  return true;
  
  // if(type == 4 )  if( bbmass>130 && Kv < Kvcut &&  ISR_2==false && ISR_3==false && ISR_4==false && y23<0.015 )  return true;
  //  if(type == 5 )  if( bbmass>130 && Kv < Kvcut &&  ISR_2==false && ISR_3==false && ISR_4==false && y23<0.015 && (b1mass+b2mass)<100)  return true;
  if(type == 4 )  if( bbmass>130 && Kv < Kvcut &&  ISR_2==false && ISR_3==false && ISR_4==false )  return true;
  if(type == 5 )  if( bbmass>130 && Kv < Kvcut &&  ISR_2==false && ISR_3==false && ISR_4==false )  return true;
  
  
  if(type > 10) {
    // if( bbmass>130 && Kv < Kvcut &&  ISR_2==false && ISR_3==false && ISR_4==false && y23<0.015 && (b1mass+b2mass)<100  ) {
    if( bbmass>130 && Kv < Kvcut &&  ISR_2==false && ISR_3==false && ISR_4==false ) {
      //btagging   
      if(type == 11 )  if( jet_btag[0]>btag1) return true;
      if(type == 12 )  if( jet_btag[0]>btag1 && jet_btag[1]>btag2) return true;
      if(type == 13 )  if( JetBtag(0)==true || JetBtag(1)==true ) return true;
      if(type == 14 )  if( JetBtag(0)==true && JetBtag(1)==true ) return true;
      
      //ctagging
      if(type == 15 )  if( jet_ctag[0]>ctag1 || jet_ctag[1]>ctag2 ) return true;
      if(type == 16 )  if( jet_ctag[0]>ctag1 && jet_ctag[1]>ctag2 ) return true;
    }
  }
  
  return false;
}

bool kaon_info::checkParticle(float p, float dedx, int pdg){

  float a  = 0.0185204;
  float b1 = 0.101048;
  float b2 = 0.083887;

  // pion
  if(pdg == 211){
    return  dedx > 0 && 
            dedx > a*std::log(p) + b1;
  }

  // kaon
  if(pdg == 321){
    return  dedx > 0 && 
            dedx < a*std::log(p) + b1 &&
            dedx > a*std::log(p) + b2;
  }

  // proton
  if(pdg == 2212){
    return  dedx > 0 && 
            dedx < a*std::log(p) + b2;
  }

  return false;

}