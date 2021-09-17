#include "Rq.C"


void RPartonPlots( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  TH1F *h_Rhisto[3];
  h_Rhisto[0]=RParton(pol, 5, lum);
  h_Rhisto[1]=RParton(pol, 4, lum);
  h_Rhisto[2]=RParton(pol, 3, lum);

  TCanvas* c_f1_MC = new TCanvas("c_f1_MC","c_f1_MC",800,800);
  c_f1_MC->cd(1);
  c_f1_MC->SetGrid();
  h_Rhisto[0]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
  h_Rhisto[0]->GetYaxis()->SetTitle("R_{q}");
  h_Rhisto[0]->GetYaxis()->SetRangeUser(0,1);

  h_Rhisto[0]->SetLineColor(2);
  h_Rhisto[0]->SetLineWidth(2);

  h_Rhisto[1]->SetLineColor(4);
  h_Rhisto[1]->SetLineWidth(2);

  h_Rhisto[2]->SetLineColor(kMagenta+2);
  h_Rhisto[2]->SetLineWidth(2);
  
  h_Rhisto[0]->Draw("histoe");
  h_Rhisto[1]->Draw("histoesame");
  h_Rhisto[2]->Draw("histoesame");

  c_f1_MC->Update();

  Labels(pol,0,lum);

  TLegend *leg = new TLegend(0.2,0.7,0.55,0.9);
  TString signal="c#bar{c}";
  TString qbkg="b#bar{b}";
  leg->AddEntry(h_Rhisto[0],"b-quark","l");
  leg->AddEntry(h_Rhisto[1],"c-quark","l");
  leg->AddEntry(h_Rhisto[2],"uds-quarks","l");
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetShadowColor(0);
  leg->Draw();
  c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));

  
}

void PreSelection( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  TH1F* h0[3];
  h0[0]=GetHisto(3,TString::Format("h_Nparton_%i",0),pol,4,lum,1);
  h0[1]=GetHisto(3,TString::Format("h_Nparton_%i",1),pol,4,lum,1);
  h0[2]=GetHisto(3,TString::Format("h_Nparton_%i",2),pol,4,lum,1);
  
  TH1F* h1[3];
  h1[0]=GetHisto(3,"h_N0_0",pol,4,lum,1);
  h1[1]=GetHisto(3,"h_N0_1",pol,4,lum,1);
  h1[2]=GetHisto(3,"h_N0_2",pol,4,lum,1);
  
  for(int i=0; i<3; i++) h1[i]->Divide(h0[i]);

  TCanvas* c_F_MC = new TCanvas("c_F_MC","c_F_MC",800,800);
  c_F_MC->cd(1);
  c_F_MC->SetGrid();
  h1[0]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
  h1[0]->GetYaxis()->SetTitle("[no units]");
  h1[0]->GetYaxis()->SetRangeUser(0,0.95);

  h1[0]->SetLineColor(2);
  h1[0]->SetLineWidth(2);

  h1[1]->SetLineColor(4);
  h1[1]->SetLineWidth(2);
 
  h1[0]->Draw("histoe");
  h1[1]->Draw("histoesame");
  h1[2]->Draw("histoesame");

  c_F_MC->Update();

  Labels(pol,0,lum);

  TLegend *leg = new TLegend(0.2,0.8,0.55,0.9);
  TString signal="c#bar{c}";
  TString qbkg="b#bar{b}";
  leg->AddEntry(h1[0],"b","l");
  leg->AddEntry(h1[1],"c","l");
  leg->AddEntry(h1[2],"uds","l");

  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetShadowColor(0);
  leg->Draw();

}

void RPlots_c( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);


  
  //R theory
  double d_Rparton[3];
  d_Rparton[0]=RParton_value(pol, 5, -1);
  d_Rparton[1]=RParton_value(pol, 4, -1);
  d_Rparton[2]=RParton_value(pol, 3, -1);
  
  //F fractions
  TH1F *h_Fhisto[2];
  h_Fhisto[0]=FHisto(pol, 1, 4, lum);
  h_Fhisto[1]=FHisto(pol, 2, 4, lum);

  
  //MC mistagging efficiencies
  TH1F *h_mistag_b= epsilon_mistag(pol, 4, 5,-1);
  TH1F *h_mistag_uds= epsilon_mistag(pol, 4, 3,-1);

      
  //MC eff quark calculation
  TH1F *eff_MC;
  eff_MC=DTeff_cheat(4,pol,4,-1).first;
  TH1F *rho_MC;
  rho_MC=DTeff_cheat(4,pol,4,-1).second;
  
  //double tag eff quark estimation
  TH1F* h_eff_quark = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC,true);

  cout<<" C-quark, Lum:"<<lum<<"fb-1, pol="<<pol<<" ()=left, 1=right, 2=80/30 left, 3=80/30 right)"<<endl;
  //RParton
  TH1F *h_Rhisto=RCheat(pol, 4, -1);
  TH1F *Rmeasured=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);

  //*************************************************************
  // Plots Fs
  h_eff_quark->Scale(100);
  eff_MC->Scale(100.);

  TCanvas* c_F_MC = new TCanvas("c_F_MC","c_F_MC",800,800);
  c_F_MC->cd(1);
  c_F_MC->SetGrid();
  h_Fhisto[0]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
  h_Fhisto[0]->GetYaxis()->SetTitle("[no units]");
  h_Fhisto[0]->GetYaxis()->SetRangeUser(0,0.15);

  h_Fhisto[0]->SetLineColor(2);
  h_Fhisto[0]->SetLineWidth(2);

  h_Fhisto[1]->SetLineColor(4);
  h_Fhisto[1]->SetLineWidth(2);
 
  h_Fhisto[0]->Draw("histoe");
  h_Fhisto[1]->Draw("histoesame");

  c_F_MC->Update();

  Labels(pol,0,lum);

  TLegend *leg = new TLegend(0.2,0.8,0.55,0.9);
  TString signal="c#bar{c}";
  TString qbkg="b#bar{b}";
  leg->AddEntry(h_Fhisto[0],"F1_{c}","l");
  leg->AddEntry(h_Fhisto[1],"F2_{c}","l");
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c_F_MC->Print(TString::Format("summaryplots/F_pdg_%i_pol_%i.eps",4,pol));

  //*************************************************************
  // Plots efficiencies
  TCanvas* c_eff_MC = new TCanvas("c_eff_MC","c_eff_MC",800,800);
  c_eff_MC->cd(1);
  c_eff_MC->SetGrid();
  h_eff_quark->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
  h_eff_quark->GetYaxis()->SetTitle("[no units]");
  h_eff_quark->GetYaxis()->SetRangeUser(0,50);

  h_eff_quark->SetLineColor(2);
  h_eff_quark->SetLineWidth(2);

  eff_MC->SetLineColor(4);
  eff_MC->SetLineWidth(2);
 
  h_eff_quark->Draw("histoe");
  eff_MC->Draw("histoesame");
  rho_MC->Draw("histoesame");

  c_eff_MC->Update();

  Labels(pol,0,lum);

  TLegend *leg2 = new TLegend(0.2,0.8,0.55,0.9);
  leg2->AddEntry(eff_MC,"Cheat","l");
  leg2->AddEntry(h_eff_quark,"Data Method","l");
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

  c_eff_MC->Print(TString::Format("summaryplots/eff_MC_vs_DT_pdg_%i_pol_%i.eps",4,pol));

  //*************************************************************
  // Plots R
  TCanvas* c_R_MC = new TCanvas("c_R_MC","c_R_MC",800,800);
  c_R_MC->cd(1);
  c_R_MC->SetGrid();
  Rmeasured->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
  Rmeasured->GetYaxis()->SetTitle("R_{c}");
  Rmeasured->GetYaxis()->SetRangeUser(0,1);

  Rmeasured->SetLineColor(2);
  Rmeasured->SetLineWidth(2);

  h_Rhisto->SetLineColor(4);
  h_Rhisto->SetLineWidth(2);
 
  Rmeasured->Draw("histoe");
  h_Rhisto->Draw("histoesame");

  c_R_MC->Update();

  Labels(pol,0,lum);

  TLegend *leg3 = new TLegend(0.2,0.8,0.55,0.9);
  leg3->AddEntry(h_Rhisto,"Cheat","l");
  leg3->AddEntry(Rmeasured,"Data Method","l");
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetShadowColor(0);
  leg3->Draw();
  c_R_MC->Print(TString::Format("summaryplots/Rmeasured_pdg_%i_pol_%i.eps",4,pol));
  
}




void R_c( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  //R theory
  double d_Rparton[3];
  d_Rparton[0]=RParton_value(pol, 5, -1);
  d_Rparton[1]=RParton_value(pol, 4, -1);
  d_Rparton[2]=RParton_value(pol, 3, -1);

  //F fractions
  TH1F *h_Fhisto[2];
  h_Fhisto[0]=FHisto(pol, 1, 4, lum);
  h_Fhisto[1]=FHisto(pol, 2, 4, lum);

  
  //MC mistagging efficiencies
  TH1F *h_mistag_b= epsilon_mistag(pol, 4, 5,-1);
  TH1F *h_mistag_b_truth= epsilon_mistag_truth(pol, 4, 5,-1);
  TH1F *h_mistag_uds= epsilon_mistag(pol, 4, 3,-1);
  TH1F *h_mistag_uds_truth= epsilon_mistag_truth(pol, 4, 3,-1);

  TH1F *h_Fhisto_effb10[2];
  h_Fhisto_effb10[0]=FHistoEffErr(pol, 1, 4, lum,0.1);
  h_Fhisto_effb10[1]=FHistoEffErr(pol, 2, 4, lum,0.1);

  TH1F *h_Fhisto_effuds10[2];
  h_Fhisto_effuds10[0]=FHistoEffErr(pol, 1, 4, lum,0.,0.1);
  h_Fhisto_effuds10[1]=FHistoEffErr(pol, 2, 4, lum,0.,0.1);
  
  //MC eff quark calculation
  TH1F *eff_MC;
  eff_MC=DTeff_cheat(4,pol,4,-1).first;
  TH1F *rho_MC;
  rho_MC=DTeff_cheat(4,pol,4,-1).second;
  
  //double tag eff quark estimation
  TH1F* h_eff_quark_onlystats = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b_truth,h_mistag_uds, rho_MC,true);
  TH1F* h_eff_quark = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
  TH1F* h_eff_quark_Rbup1 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1+0.01), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
  TH1F* h_eff_quark_Rbdown1 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1-0.01), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
  TH1F* h_eff_quark_Rbup5 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1+0.05), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
  TH1F* h_eff_quark_Rbdown5 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1-0.05), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
  TH1F* h_eff_quark_eb10= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effb10[0] , h_Fhisto_effb10[1] , h_mistag_b_truth,h_mistag_uds, rho_MC,true);
  TH1F* h_eff_quark_euds10= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effb10[0] , h_Fhisto_effb10[1] , h_mistag_b_truth,h_mistag_uds, rho_MC,true);

  cout<<" C-quark, Lum:"<<lum<<"fb-1, pol="<<pol<<" ()=left, 1=right, 2=80/30 left, 3=80/30 right)"<<endl;
  //RParton
  TH1F *h_Rhisto=RCheat(pol, 4, -1);
  fit_Rq(h_Rhisto," Parton LeveL: ");
  //Rmeasurement only stats
  TH1F *Rmeasured_onlystats=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark_onlystats, rho_MC, d_Rparton[0], h_mistag_b_truth, h_mistag_uds_truth);

  fit_Rq(Rmeasured_onlystats," Reco, only stats: ");
  //including rho and effc
  TH1F *Rmeasured=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  fit_Rq(Rmeasured," Reco, stats+rho ");

  //bmistagg
  TH1F *Rmeasured_effb_10=DT_R(h_Fhisto_effb10[0], h_Fhisto_effb10[1], h_eff_quark_eb10, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  fit_Rq(Rmeasured_effb_10," Reco, Delta_effb=10% ");

  //uds-mistagg
  TH1F *Rmeasured_effuds_10=DT_R(h_Fhisto_effuds10[0], h_Fhisto_effuds10[1], h_eff_quark_euds10, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  fit_Rq(Rmeasured_effuds_10," Reco, Delta_effuds=10% ");

 
  TH1F *Rmeasured_Rbup1=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark_Rbup1, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  TH1F *Rmeasured_Rbdown1=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark_Rbdown1, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  fit_Rq(Rmeasured_Rbup1,Rmeasured_Rbdown1," DeltaRb=1% ");

  TH1F *Rmeasured_Rbup5=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark_Rbup5, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  TH1F *Rmeasured_Rbdown5=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark_Rbdown5, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
  fit_Rq(Rmeasured_Rbup5,Rmeasured_Rbdown5," DeltaRb=5% ");
 
  
}


void R_cpol( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  cout<<" C-quark, Lum:"<<lum<<"fb-1, pol="<<pol<<" ()=left, 1=right, 2=80/30 left, 3=80/30 right)"<<endl;
    
  //R theory
  double d_Rparton[3];
  d_Rparton[0]=RParton_value(pol, 5, -1);
  d_Rparton[1]=RParton_value(pol, 4, -1);
  d_Rparton[2]=RParton_value(pol, 3, -1);


  float value=0;
  float value_array[]={0};

  float k=0;
  float eel=0;
  float epos=0;

  if(pol==2) {
    eel=0.001;
    epos=0.001;
  }
  if(pol==3) {
    eel=0.001;
    epos=0.0014;
  }
    
  for(int i=-1; i<2; i+=2) {
    for(int j=-1; j<2; j+=2) {
      p1error=eel*i;
      p2error=epos*j;
      //F fractions
      TH1F *h_Fhisto[2];
      h_Fhisto[0]=FHisto(pol, 1, 4, lum);
      h_Fhisto[1]=FHisto(pol, 2, 4, lum);
      
      //MC mistagging efficiencies
      TH1F *h_mistag_b= epsilon_mistag(pol, 4, 5,-1);
      TH1F *h_mistag_uds= epsilon_mistag(pol, 4, 3,-1);

      //MC eff quark calculation
      TH1F *eff_MC;
      eff_MC=DTeff_cheat(4,pol,4,-1).first;
      TH1F *rho_MC;
      rho_MC=DTeff_cheat(4,pol,4,-1).second;
      
      //double tag eff quark estimation
      TH1F* h_eff_quark = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
      
      TH1F *Rmeasured=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
      value_array[int(k)]=fit_Rq_value(Rmeasured);
      value+=fit_Rq_value(Rmeasured);
      k++;
    }
  }
  cout<<"  "<<endl;
 
  value/=k;
  float var = 0;
  for( int i = 0; i < k; i++ ) {
    var += (value_array[i] - value) * (value_array[i] - value);
    
  }
  var = var / k;
  float sd = sqrt(var);

  cout<<"Polarization unc: "<<100.*sd/value<<"%"<<endl;
  // cout<<sd<<" "<<value<<endl;

}

void R_cbkg( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  cout<<" C-quark, Lum:"<<lum<<"fb-1, pol="<<pol<<" ()=left, 1=right, 2=80/30 left, 3=80/30 right)"<<endl;
    
  //R theory
  double d_Rparton[3];
  d_Rparton[0]=RParton_value(pol, 5, -1);
  d_Rparton[1]=RParton_value(pol, 4, -1);
  d_Rparton[2]=RParton_value(pol, 3, -1);

  float k=0;

  for(int i=0; i<5; i++) {
    float error_bkg=0.0;
    if(i==1) error_bkg=0.01;
    if(i==2) error_bkg=0.05;
    if(i==3) error_bkg=0.1;
    if(i==4) error_bkg=1;

    //F fractions
    TH1F *h_Fhisto[2];
    h_Fhisto[0]=FHistoBKG(pol, 1, 4, lum,error_bkg);
    h_Fhisto[1]=FHistoBKG(pol, 2, 4, lum,error_bkg);
      
    //MC mistagging efficiencies
    TH1F *h_mistag_b= epsilon_mistag(pol, 4, 5,-1);
    TH1F *h_mistag_uds= epsilon_mistag(pol, 4, 3,-1);
    
    //MC eff quark calculation
    TH1F *eff_MC;
    eff_MC=DTeff_cheat(4,pol,4,-1).first;
    TH1F *rho_MC;
    rho_MC=DTeff_cheat(4,pol,4,-1).second;
    
    //double tag eff quark estimation
    TH1F* h_eff_quark = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC,true);
      
    TH1F *Rmeasured=DT_R(h_Fhisto[0], h_Fhisto[1], h_eff_quark, rho_MC, d_Rparton[0], h_mistag_b, h_mistag_uds);
    fit_Rq(Rmeasured,TString::Format("BKG unc: %.1f",error_bkg*100.));

  }

}

void R_theory_vs_reco( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  cout<<" C-quark, Lum:"<<lum<<"fb-1, pol="<<pol<<" ()=left, 1=right, 2=80/30 left, 3=80/30 right)"<<endl;
    
 
  float k=0;

  for(int i=0; i<5; i++) {
    float error_bkg=0.0;
    if(i==1) error_bkg=0.01;
    if(i==2) error_bkg=0.05;
    if(i==3) error_bkg=0.1;
    if(i==4) error_bkg=0.5;

    TH1F *h_RCheat=RCheat(pol, 4, -1);
    TH1F *h_RParton=RParton(pol, 4, -1);

    float rq_reco=fit_Rq_value(h_RCheat);
    float rq_parton=fit_Rq_value(h_RParton);
    cout<<" Correction size: "<<100.*(1-rq_parton/rq_reco)<<" %, uncert."<<error_bkg*100<<"%,  correction error:"<<error_bkg/((rq_parton/rq_reco))*rq_reco<<" %"<<endl;
  }

}



void Rc_calculations() {


  for(int pol=2; pol<3; pol++) {
    cout<<" Plots "<<endl;
    cout<<"  ------------------------------------------ "<<endl;
    //   RPartonPlots(pol,900);
    //PreSelection(pol,900);
     RPlots_c(pol,900);
    // cout<<"  ------------------------------------------ "<<endl;
     R_c(pol,900);
    // cout<<" polarization "<<endl;
    // cout<<"  ------------------------------------------ "<<endl;
     R_cpol(pol,900);
    // cout<<" bkg "<<endl;
    // cout<<"  ------------------------------------------ "<<endl;
    R_cbkg(pol,900);
    R_theory_vs_reco(pol,900);
  }
}
