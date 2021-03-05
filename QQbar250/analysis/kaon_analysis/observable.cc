// A. Irles
// irles @ lal.in2p3.fr
// 30 March 2020

#define observable_cxx
#include "observable.h"
#include "TPad.h"

void observable::dEdx(int n_entries=-1) {

  float momentum_min=0.95;
  
  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.33,1.667,2,2.5,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,32,36,40,44,48,52,56,60,64,68,72,80,90,100};
		    //13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  TH2F* kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* electron_dEdx_truth = new TH2F("electron_dEdx_truth","electron_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* muon_dEdx_truth = new TH2F("muon_dEdx_truth","muon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  TH2F* kaon_dEdx_reco = new TH2F("kaon_dEdx_reco","kaon_dEdx_reco",nbinnum_p,bins_p,nbinnumy,binsy);


  TH1F* n_kaon_jet = new TH1F("n_kaon_jet","n_kaon_jet",15,-0.5,14.5);
  TH1F* n_kaon_vtx = new TH1F("n_kaon_vtx","n_kaon_vtx",15,-0.5,14.5);
  TH1F* p_kaon = new TH1F("p_kaon","p_kaon",125,-0.5,124.5);
  TH1F* p_proton = new TH1F("p_proton","p_proton",125,-0.5,124.5);
  TH1F* p_pion = new TH1F("p_pion","p_pion",125,-0.5,124.5);
  TH1F* p_electron = new TH1F("p_electron","p_electron",125,-0.5,124.5);
  TH1F* p_muon = new TH1F("p_muon","p_muon",125,-0.5,124.5);

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //  double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));
    double gamma_e=mc_ISR_E[0]+mc_ISR_E[1];

    //for the moment, we restrict the analysis to the bb events without radaitive return
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<35) {
      //  if(gamma_e<35 && fabs(mc_quark_pdg[0])==5) { 
      //    if(bbmass<120) {

        for(int ijet=0; ijet<2; ijet++){
         int nkaonjet=0;
         double nt=0;

         /*
         double mom_x=0, mom_y=0, mom_z=0;
         double e=0;
         double nt=0;
         float momvertex;
         for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
           for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
             nt++;
             e+=jet_track_E[ijet][ivtx][itrack];
             mom_x+=jet_track_px[ijet][ivtx][itrack];
             mom_y+=jet_track_py[ijet][ivtx][itrack];
             mom_z+=jet_track_pz[ijet][ivtx][itrack];
           }
         }
         momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );
         */

         if(jet_btag[ijet]>0.8) {

           for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {

            int nkaonvtx=0;

            for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {

             nt++;

             if( fabs(jet_track_pdg[ijet][ivtx][itrack])==321 ){

              nkaonjet++;
              nkaonvtx++;
              p_kaon->Fill(jet_track_p[ijet][ivtx][itrack]);

            }

            if( fabs(jet_track_pdg[ijet][ivtx][itrack])==211 ) p_pion->Fill(jet_track_p[ijet][ivtx][itrack]);
            if( fabs(jet_track_pdg[ijet][ivtx][itrack])==2212 ) p_proton->Fill(jet_track_p[ijet][ivtx][itrack]);
            if( fabs(jet_track_pdg[ijet][ivtx][itrack])==11 ) p_electron->Fill(jet_track_p[ijet][ivtx][itrack]);
            if( fabs(jet_track_pdg[ijet][ivtx][itrack])==13 ) p_muon->Fill(jet_track_p[ijet][ivtx][itrack]);
            
            } // end track

            n_kaon_vtx->Fill(nkaonvtx);

          } // end vtx

          n_kaon_jet->Fill(nkaonjet);

        } // end if jet 0.8

  	//      }

  	//for(int ijet=0; ijet<2; ijet++) {
        for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
          for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {

             if(jet_track_dedx[ijet][ivtx][itrack]>0) {

                std::vector<float> track_p_vec;
                track_p_vec.push_back(jet_track_px[ijet][ivtx][itrack]);
                track_p_vec.push_back(jet_track_py[ijet][ivtx][itrack]);
                track_p_vec.push_back(jet_track_pz[ijet][ivtx][itrack]);
                // float abs_rad_track = fabs(GetTheta(track_p_vec));
                float abs_cos_track = fabs(GetCostheta(track_p_vec));
                float abs_rad_track = acos(abs_cos_track);

                float track_dedx = jet_track_dedx[ijet][ivtx][itrack];
                float dedx_corr  = track_dedx * pow(abs_rad_track,0.05);

                if(abs_cos_track<0.8){

                  if(jet_track_pdg[ijet][ivtx][itrack]==211){
                    // pion_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],jet_track_dedx[ijet][ivtx][itrack]);
                    pion_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],dedx_corr);
                  }

                  if(jet_track_pdg[ijet][ivtx][itrack]==321){
                    // kaon_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],jet_track_dedx[ijet][ivtx][itrack]);
                    kaon_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],dedx_corr);
                  }

                  if(jet_track_pdg[ijet][ivtx][itrack]==2212){
                    // proton_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],jet_track_dedx[ijet][ivtx][itrack]);
                    proton_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],dedx_corr);
                  }

                  if(jet_track_pdg[ijet][ivtx][itrack]==11){
                    // electron_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],jet_track_dedx[ijet][ivtx][itrack]);
                    electron_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],dedx_corr);
                  }

                  if(jet_track_pdg[ijet][ivtx][itrack]==13){
                    // muon_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],jet_track_dedx[ijet][ivtx][itrack]);
                    muon_dEdx_truth->Fill(jet_track_p[ijet][ivtx][itrack],dedx_corr);
                  }

                }

            } // end if dEdx track > 0

          } // end itrack
        } // end ivtx
      } // end ijet

    }//bb
  }//for

   //SetQQbarStyle();
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);

   gStyle->SetTitleBorderSize(0);
   gStyle->SetTitleStyle(0);
   gStyle->SetTitleX(0.3);
   gStyle->SetMarkerSize(0.2);
   gStyle->SetPadLeftMargin(0.2);

   TCanvas* c_dEdx_truth_0 = new TCanvas("c_dEdx","c_dEdx",500,500);
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

  

   QQBARLabel(0.25,0.85,"",1);
  
   TLegend *leg0 = new TLegend(0.7,0.8,0.8,0.9);
   leg0->AddEntry(pion_dEdx_truth,"#pi","lp");
   leg0->AddEntry(kaon_dEdx_truth,"K","lp");
   leg0->AddEntry(proton_dEdx_truth,"p","lp");
   leg0->AddEntry(muon_dEdx_truth,"#mu","lp");
   leg0->AddEntry(electron_dEdx_truth,"e","lp");
   leg0->SetFillColor(0);
   leg0->SetLineColor(0);
   leg0->SetShadowColor(0);
   leg0->Draw();
  

   //kaon
   float x_kaon[200], y_kaon[200], ey_kaon[200], ey_kaon2[200];
   float ex[200];
   int n_kaon=0;
   for(int i=0; i<kaon_dEdx_truth->GetNbinsX(); i++) {
     if( kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
       TH1D * proj_kaon =kaon_dEdx_truth->ProjectionY("proj_kaon",i,i+1);
       
       x_kaon[n_kaon]=kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
       y_kaon[n_kaon]=proj_kaon->GetMean();
       ey_kaon[n_kaon]=proj_kaon->GetRMS();
       ey_kaon2[n_kaon]=proj_kaon->GetMean()/sqrt(proj_kaon->GetEntries());
       ex[n_kaon]=0.;//kaon_dEdx_truth->GetXaxis()->GetBinWidth(i+1)/2.;
       n_kaon++;
     }
   }
   TGraphErrors *kaonproj= new TGraphErrors(n_kaon,x_kaon,y_kaon,ex,ey_kaon);
   TGraphErrors *kaonproj2= new TGraphErrors(n_kaon,x_kaon,y_kaon,ex,ey_kaon2);

   //pion
   float x_pion[200], y_pion[200], ey_pion[200], ey_pion2[200];
   int n_pion=0;
   for(int i=0; i<pion_dEdx_truth->GetNbinsX(); i++) {
     if( pion_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
       TH1D * proj_pion =pion_dEdx_truth->ProjectionY("proj_pion",i,i+1);

       x_pion[n_pion]=pion_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
       y_pion[n_pion]=proj_pion->GetMean();
       ey_pion[n_pion]=proj_pion->GetRMS();
       ey_pion2[n_pion]=proj_pion->GetMean()/sqrt(proj_pion->GetEntries());
       ex[n_pion]=pion_dEdx_truth->GetXaxis()->GetBinWidth(i+1);
       n_pion++;
     }
   }
   TGraphErrors *pionproj= new TGraphErrors(n_pion,x_pion,y_pion,ex,ey_pion);
   TGraphErrors *pionproj2= new TGraphErrors(n_pion,x_pion,y_pion,ex,ey_pion2);
   
   //proton
   float x_proton[200], y_proton[200], ey_proton[200], ey_proton2[200];
   int n_proton=0;
   for(int i=0; i<proton_dEdx_truth->GetNbinsX(); i++) {
     if( proton_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
       TH1D * proj_proton =proton_dEdx_truth->ProjectionY("proj_proton",i,i+1);

       x_proton[n_proton]=proton_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
       y_proton[n_proton]=proj_proton->GetMean();
       ey_proton[n_proton]=proj_proton->GetRMS();
       ey_proton2[n_proton]=proj_proton->GetMean()/sqrt(proj_proton->GetEntries());
       ex[n_proton]=proton_dEdx_truth->GetXaxis()->GetBinWidth(i+1);
       n_proton++;
     }
   }
   TGraphErrors *protonproj= new TGraphErrors(n_proton,x_proton,y_proton,ex,ey_proton);
   TGraphErrors *protonproj2= new TGraphErrors(n_proton,x_proton,y_proton,ex,ey_proton2);
   

  //----------------------------------------------------------------------------------------
  // TCanvas* c_calculateparam = new TCanvas("c_calculateparam","c_calculateparam",1000,800);
  // pionproj->SetMarkerColor(4);
  // pionproj->SetLineColor(4);
  // pionproj->SetTitle("dE/dx projection");
  // pionproj->GetYaxis()->SetTitle("dE/dx#times10^{-6}");
  // pionproj->GetXaxis()->SetTitle("p");
  // pionproj->Draw("ap");

  // kaonproj->SetMarkerColor(2);
  // kaonproj->SetLineColor(2);
  // kaonproj->Draw("p");

  // protonproj->SetMarkerColor(3);
  // protonproj->SetLineColor(3);
  // protonproj->Draw("p"); 

  TF1 *f1= new TF1("f1","[0]+[1]*std::log(x)",3,100);
  f1->SetLineColor(2);
  // f1->SetParameter(0,0.15);
  // f1->SetParameter(1,0.02);

  kaonproj->Fit(f1,"REM");

  double x[100], y[100];
  

  for(int ieff=0; ieff<11; ieff++) {
    float eff=0.45+0.05*ieff;
    
    double a=f1->GetParameter(0);
    double b=f1->GetParameter(1);
    
    double a_up=0;
    double a_down=0;
    float max_purity=0;
    float max_eff=0;
    
    for(int j=0; j<50; j++) {

      for(int k=0; k<50; k++) {

       double ea=(0.1+0.1*j)*f1->GetParError(0);
       double ea2=-(0.1+0.1*k)*f1->GetParError(0);

       double int_pion=0;
       double int_kaon=0;
       double int_proton=0;
       double int_kaon_total=0;

       for(int i=0; i<kaon_dEdx_truth->GetNbinsX(); i++) {

         TH1D * proj_kaon =kaon_dEdx_truth->ProjectionY("proj_kaon",i,i+1);
         int_kaon_total+=proj_kaon->GetEntries();

         if( kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1) > momentum_min ) {

           TH1D * proj_pion =pion_dEdx_truth->ProjectionY("proj_pion",i,i+1);
           TH1D * proj_proton =proton_dEdx_truth->ProjectionY("proj_proton",i,i+1);

           for(int j1=0; j1<proj_pion->GetNbinsX(); j1++) {

             double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
             double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));

             if(proj_pion->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_pion->GetXaxis()->GetBinCenter(j1)> yminus) int_pion+=proj_pion->GetBinContent(j1);

           }

           for(int j1=0; j1<proj_kaon->GetNbinsX(); j1++) {

             double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
             double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
             if(proj_kaon->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_kaon->GetXaxis()->GetBinCenter(j1)> yminus) int_kaon+=proj_kaon->GetBinContent(j1);

           }

           for(int j1=0; j1<proj_proton->GetNbinsX(); j1++) {

             double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
             double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));

             if(proj_proton->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_proton->GetXaxis()->GetBinCenter(j1)> yminus) int_proton+=proj_proton->GetBinContent(j1);

           }	
         }
       }

       if((int_proton+int_pion+int_kaon)/int_kaon_total>eff ) {
       // cout<<j<<" "<<k<< "  ->  eff: "<< int_kaon/int_kaon_total<<" purity: "<<1.-(int_proton+int_pion)/int_kaon<<" (pion:"<<1.-(int_pion)/int_kaon<<") (proton:"<<1.-(int_proton)/int_kaon<<")"<<endl;
         if( int_kaon/(int_proton+int_pion+int_kaon)  > max_purity) {
           max_purity = int_kaon/(int_proton+int_pion+int_kaon);
           max_eff= (int_proton+int_pion+int_kaon)/int_kaon_total;
           a_up=a+ea;
           a_down=a+ea2;
	    //	cout<<" purity="<<max_purity<<" eff="<<(int_proton+int_pion+int_kaon)/int_kaon_total<<";    slope="<<b<<" upper="<<a+ea<<" lower="<<a+ea2<<endl;
         }
       }

     } // end k loop
   } // end j loop

    cout<<"eff_input>"<<eff<<":     purity="<<max_purity<<" eff="<<max_eff<<";    slope="<<b<<" upper="<<a_up<<" lower="<<a_down<<endl;
    x[ieff]=eff;
    y[ieff]=max_purity;
    a_up=0;
    a_down=0;
    max_purity=0;
    max_eff= 0;
  }
  
  TGraph *eff_purity = new TGraph(11,x,y);
  
  TFile *MyFile = new TFile(TString::Format("output_250_all_%s_corr.root",process.Data()),"RECREATE");
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
  n_kaon_vtx->Write();
  p_kaon->Write();
  p_proton->Write();
  p_pion->Write();
  p_electron->Write();
  p_muon->Write();

  protonproj->SetName("proton_proj");
  protonproj->Write();
  pionproj->SetName("pion_proj");
  pionproj->Write();
  kaonproj->SetName("kaon_proj");
  kaonproj->Write();

  protonproj2->SetName("proton_proj2");
  protonproj2->Write();
  pionproj2->SetName("pion_proj2");
  pionproj2->Write();
  kaonproj2->SetName("kaon_proj2");
  kaonproj2->Write();
  
  
  eff_purity->SetName("eff_purity");
  eff_purity->Write();
  
  
  MyFile->Close();
  
  
}

bool observable::iskaon_dEdx(float p, float dedx){

  bool iskaon=false;

  float a  = 0.0183421;
  float b1 = 0.10207;
  float b2 = 0.0862359;

  iskaon =  dedx > 0 && 
  dedx < a*std::log(p) + b1 &&
  dedx > a*std::log(p) + b2;

  return iskaon;


}  
   


bool observable::PreSelection(int type=0,float Kvcut=25) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  if(type == 0 ) return true;

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
  if(photonness[0]<0.85 && photonness[1]<0.85) ISR_1=false;

  bool ISR_2=true;
  if(npfo[0]>4 && npfo[1]>4) ISR_2=false;

  bool ISR_3=true;
  if(energy<100) ISR_3=false;

  bool ISR_4=true;
  if(energy<70 || fabs(costheta)<0.95) ISR_4=false;

  //   bool ISR_3=false;
  //   if( (fabs(costheta_neutral0)>0.99 && neutralPFO_total[0]>Kvcut) || (fabs(costheta_neutral1)>0.99 && neutralPFO_total[1]>Kvcut) ) ISR_3=true;

  if(type == 3 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false)  return true;
  if(type == 4 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false && ISR_2==false)  return true;
  if(type == 5 )  if( Kv < Kvcut && bbmass>130 && ISR_3==false)  return true;
  if(type == 6 )  if( Kv < Kvcut && bbmass>130 && ISR_3==false && ISR_4==false)  return true;
  if(type == 7 )  if( Kv < Kvcut && bbmass>130 && ISR_3==false && ISR_4==false && ISR_2==false)  return true;
  if(type == 8 )  if( Kv < Kvcut && bbmass>130 && ISR_3==false && ISR_4==false && ISR_2==false && jet_btag[0]>btag1 && jet_btag[1]>btag2)   return true;
  // //    float thrust=principle_thrust_value;
     
  //   double  neutralPFO_max[2];
  //   double  neutralPFO_total[2];
  //   double  neutralPFO_ratio[2];

  //   double  neutraljet_E[2];
  //   double  neutraljet_costheta[2];

  //   float costheta_neutral0;
  //   float costheta_neutral1;

    
  //   float neut[2][3];

  //   double npfo[2];
  //   for(int ijet=0; ijet<2; ijet++) {
  //     neutralPFO_max[ijet]=0;
  //     neutralPFO_total[ijet]=0;
  //     neutralPFO_ratio[ijet]=0;
  //     npfo[ijet]=0;
  //     double jetenergy=0;

  //     neut[ijet][0]=0;
  //     neut[ijet][1]=0;
  //     neut[ijet][2]=0;

  //     for(int ipfo=0; ipfo<100; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
  // 	if(jet_pfo_E[ijet][ipfo]<0.1) continue;
	
  // 	npfo[ijet]++;
  // 	jetenergy+=jet_pfo_E[ijet][ipfo];
  // 	if( (jet_pfo_type[ijet][ipfo]==22 || jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
  // 	  neutralPFO_max[ijet]=jet_pfo_E[ijet][ipfo]; 
  // 	}
  // 	if( jet_pfo_type[ijet][ipfo]==22 ||  jet_pfo_charge[ijet][ipfo]==0 ) {

  // 	  neut[ijet][0]+=jet_pfo_px[ijet][ipfo];
  // 	  neut[ijet][1]+=jet_pfo_py[ijet][ipfo];
  // 	  neut[ijet][2]+=jet_pfo_pz[ijet][ipfo];

  // 	  neutralPFO_total[ijet]+=jet_pfo_E[ijet][ipfo]; 
  // 	  neutralPFO_ratio[ijet]+=jet_pfo_E[ijet][ipfo]; 
  // 	}
  //     }
  //     neutralPFO_ratio[ijet]/=jetenergy;
  //   }

  //   for(int ijet=0; ijet<2; ijet++) {
  //     neutraljet_E[ijet]=-1;
  //     neutraljet_costheta[ijet]=-1; 
  //     if(neutralPFO_ratio[ijet]>0.85) {
  // 	neutraljet_E[ijet]=jet_E[ijet];
  // 	if(ijet==0) neutraljet_costheta[ijet]=costheta_j0;
  // 	if(ijet==1) neutraljet_costheta[ijet]=costheta_j1;
  //     }
  //   }

        
  //   std::vector<float> neutral0;
  //   neutral0.push_back(neut[0][0]);
  //   neutral0.push_back(neut[0][1]);
  //   neutral0.push_back(neut[0][2]);

  //   std::vector<float> neutral1;
  //   neutral1.push_back(neut[1][0]);
  //   neutral1.push_back(neut[1][1]);
  //   neutral1.push_back(neut[1][2]);
    
  //   costheta_neutral0=GetCostheta(neutral0);
  //   costheta_neutral1=GetCostheta(neutral1);


  //   bool ISR_1=true;
  //   if(neutralPFO_ratio[0]<0.85 && neutralPFO_ratio[1]<0.85) ISR_1=false;

  //   bool ISR_2=true;
  //   if(npfo[0]>5 && npfo[1]>5) ISR_2=false;

  //   bool ISR_3=false;
  //   if( (fabs(costheta_neutral0)>0.99 && neutralPFO_total[0]>Kvcut) || (fabs(costheta_neutral1)>0.99 && neutralPFO_total[1]>Kvcut) ) ISR_3=true;

  //   if(type == 0 ) return true;

  //   if(type == -1 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false ) return true;
  //   if(type == -2 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false && ISR_2==false ) return true;
    

  //   if(type == 3 )  if( ISR_1==false && ISR_2==false && ISR_3==false && bbmass>130 && Kv < Kvcut)  return true;
    
  //   if(type == 4 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 )  return true;
  //   if(type == 5 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 && (b1mass+b2mass)<100)  return true;
    
  
  //   if(type > 10) {
  //     if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 && (b1mass+b2mass)<100  ) {
  // 	//btagging
  // 	if(type == 11 )  if( jet_btag[0]>btag1) return true;
  // 	if(type == 12 )  if( jet_btag[0]>btag1 && jet_btag[1]>btag2) return true;
  // 	if(type == 13 )  if( JetBtag(0)==true || JetBtag(1)==true ) return true;
  // 	if(type == 14 )  if( JetBtag(0)==true && JetBtag(1)==true ) return true;
	
  // 	//ctagging
  // 	if(type == 15 )  if( jet_ctag[0]>ctag1 || jet_ctag[1]>ctag2 ) return true;
  // 	if(type == 16 )  if( jet_ctag[0]>ctag1 && jet_ctag[1]>ctag2 ) return true;
  //     }
  //   }

  return false;
}

