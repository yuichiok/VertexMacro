#include "utils.h"
#include "histograms.h"

//pol=0 eLpR
//pol=1 eRpL
//pol=2 eLpR 80/30
//pol=3 eRpL 80/30

TH1F* FHistoBKG(int pol=0, int histo=1, int iquark=5,  float lum=900, float error=0.1){


  TH1F *h0[10];
  TH1F *hj[10];
  TH1F *hb0[10];
  TH1F *hbj[10];

  int ipdgquark=0;
  if(iquark==5) ipdgquark=0;
  if(iquark==4) ipdgquark=1;

  int ipdgquark2=0;
  if(iquark==5) ipdgquark2=1;
  if(iquark==4) ipdgquark2=0;

  double factor=1;
  if(histo==1) factor=2;
  
  //BKG--------------------------------
   //ZZ
  hb0[0]=GetHisto(0,TString::Format("h_N%i_0",0),pol,iquark,lum,factor);
  //hz
  hb0[1]=GetHisto(1,TString::Format("h_N%i_0",0),pol,iquark,lum,factor);
  //ww
  hb0[2]=GetHisto(2,TString::Format("h_N%i_0",0),pol,iquark,lum,factor);
  //rad return
  hb0[3]=GetHisto(3,TString::Format("h_N%i_3",0),pol,iquark,lum,factor);
  hb0[0]->Add(hb0[1]);
  hb0[0]->Add(hb0[2]);
  hb0[0]->Add(hb0[3]);

  //BKG2--------------------------------
  hbj[0]=GetHisto(0,TString::Format("h_N%i_0",histo),pol,iquark,lum,1);
  hbj[1]=GetHisto(1,TString::Format("h_N%i_0",histo),pol,iquark,lum,1);
  hbj[2]=GetHisto(2,TString::Format("h_N%i_0",histo),pol,iquark,lum,1);
  hbj[3]=GetHisto(3,TString::Format("h_N%i_3",histo),pol,iquark,lum,1);
  hbj[0]->Add(hbj[1]);
  hbj[0]->Add(hbj[2]);
  hbj[0]->Add(hbj[3]);

  //signal
  //bkg-uds
  h0[0]=GetHisto(4,TString::Format("h_N%i_%i",0,2),pol,iquark,lum,factor);
  //bkg-heavyquark
  h0[1]=GetHisto(4,TString::Format("h_N%i_%i",0,ipdgquark2),pol,iquark,lum,factor);
  //signal
  h0[2]=GetHisto(4,TString::Format("h_N%i_%i",0,ipdgquark),pol,iquark,lum,factor);

  //bkg-uds
  hj[0]=GetHisto(4,TString::Format("h_N%i_%i",histo,2),pol,iquark,lum,1);
  //bkg-heavyquark
  hj[1]=GetHisto(4,TString::Format("h_N%i_%i",histo,ipdgquark2),pol,iquark,lum,1);
  //signal
  hj[2]=GetHisto(4,TString::Format("h_N%i_%i",histo,ipdgquark),pol,iquark,lum,1);

  h0[0]->Add(h0[1]);
  h0[0]->Add(h0[2]);

  hj[0]->Add(hj[1]);
  hj[0]->Add(hj[2]);



  //add errors from bkg
  for(int i=0; i<h0[0]->GetNbinsX()+1; i++) {
    h0[0]->SetBinError(i,sqrt( pow(h0[0]->GetBinError(i),2)+ pow(hb0[0]->GetBinContent(i)*error,2)));
    hj[0]->SetBinError(i,sqrt( pow(hj[0]->GetBinError(i),2)+ pow(hbj[0]->GetBinContent(i)*error,2))); 
  }
      
  //result
  hj[0]->Divide(h0[0]);
  return hj[0];

}

TH1F* FHistoEffErr(int pol=0, int histo=1, int iquark=5,  float lum=900, float error_b=0, float error_uds=0){


  TH1F *h0[10];
  TH1F *h1[10];
  TH1F *h2[10];

  int ipdgquark=0;
  if(iquark==5) ipdgquark=0;
  if(iquark==4) ipdgquark=1;

  int ipdgquark2=0;
  if(iquark==5) ipdgquark2=1;
  if(iquark==4) ipdgquark2=0;

  double factor=1;
  if(histo==1) factor=2;
  //bkg-uds
  h0[0]=GetHisto(4,TString::Format("h_N%i_%i",0,2),pol,iquark,lum,factor);
  //bkg-heavyquark
  h0[1]=GetHisto(4,TString::Format("h_N%i_%i",0,ipdgquark2),pol,iquark,lum,factor);
  //signal
  h0[2]=GetHisto(4,TString::Format("h_N%i_%i",0,ipdgquark),pol,iquark,lum,factor);

  //bkg-uds
  h1[0]=GetHisto(4,TString::Format("h_N%i_%i",1,2),pol,iquark,lum,1);
  //bkg-heavyquark
  h1[1]=GetHisto(4,TString::Format("h_N%i_%i",1,ipdgquark2),pol,iquark,lum,1);
  //signal
  h1[2]=GetHisto(4,TString::Format("h_N%i_%i",1,ipdgquark),pol,iquark,lum,1);

  //bkg-uds
  h2[0]=GetHisto(4,TString::Format("h_N%i_%i",2,2),pol,iquark,lum,1);
  //bkg-heavyquark
  h2[1]=GetHisto(4,TString::Format("h_N%i_%i",2,ipdgquark2),pol,iquark,lum,1);
  //signal
  h2[2]=GetHisto(4,TString::Format("h_N%i_%i",2,ipdgquark),pol,iquark,lum,1);

 
  //add errors from bkg
  for(int i=0; i<h0[0]->GetNbinsX()+1; i++) {
    //error heeavy quark
    float effb=0;
    effb = h1[1]->GetBinContent(i)/h0[1]->GetBinContent(i);
    float epsilon_b=0;
    if(histo==1) epsilon_b = (effb+effb*error_b);
    if(histo==2) epsilon_b = (effb*effb+2.*effb*(effb*error_b));
    cout<<i<<" "<<histo<<" "<<effb<<" "<<error_b<<" "<<epsilon_b<<" "<<h1[1]->GetBinError(i)<<" "<<h2[1]->GetBinError(i)<<endl;
    h1[1]->SetBinError(i,sqrt( pow(h1[1]->GetBinError(i),2)+ pow(sqrt(h1[1]->GetBinContent(i) + h0[1]->GetBinContent(i)*epsilon_b),2)));
    h2[1]->SetBinError(i,sqrt( pow(h2[1]->GetBinError(i),2)+ pow(sqrt(h1[1]->GetBinContent(i) + h0[1]->GetBinContent(i)*epsilon_b),2)));
    cout<<h1[1]->GetBinError(i)<<" "<<h2[1]->GetBinError(i)<<endl;

    //error uds
    float effuds=0;
    effuds = h1[0]->GetBinContent(i)/h0[0]->GetBinContent(i);
    float epsilon_uds=0;
    if(histo==1) epsilon_uds = (effuds+effuds*error_uds);
    if(histo==2) epsilon_uds = (effuds*effuds+2.*effuds*(effuds*error_uds));
    h1[0]->SetBinError(i,sqrt( pow(h1[0]->GetBinError(i),2)+ pow(sqrt(h1[0]->GetBinContent(i) + h0[1]->GetBinContent(i)*epsilon_uds),2)));
    h2[0]->SetBinError(i,sqrt( pow(h2[0]->GetBinError(i),2)+ pow(sqrt(h1[0]->GetBinContent(i) + h0[1]->GetBinContent(i)*epsilon_uds),2)));
  }

  h0[0]->Add(h0[1]);
  h0[0]->Add(h0[2]);

  h1[0]->Add(h1[1]);
  h1[0]->Add(h1[2]);
  h1[0]->Divide(h0[0]);
  
  h2[0]->Add(h2[1]);
  h2[0]->Add(h2[2]);
  h2[0]->Divide(h0[0]);
  
  if(histo==1) return h1[0];
  if(histo==2) return h2[0];

}


TH1F* FHisto(int pol=0, int histo=1, int iquark=5,  float lum=900){


  TH1F *h0[10];
  TH1F *hj[10];

   double factor=1;
  if(histo==1) factor=2;
  h0[0]=GetHisto(4,TString::Format("h_N%i_%i",0,0),pol,iquark,lum,factor);
  h0[1]=GetHisto(4,TString::Format("h_N%i_%i",0,1),pol,iquark,lum,factor);
  h0[2]=GetHisto(4,TString::Format("h_N%i_%i",0,2),pol,iquark,lum,factor);

  hj[0]=GetHisto(4,TString::Format("h_N%i_%i",histo,0),pol,iquark,lum,1);
  hj[1]=GetHisto(4,TString::Format("h_N%i_%i",histo,1),pol,iquark,lum,1);
  hj[2]=GetHisto(4,TString::Format("h_N%i_%i",histo,2),pol,iquark,lum,1);

  h0[0]->Add(h0[1]);
  h0[0]->Add(h0[2]);

  hj[0]->Add(hj[1]);
  hj[0]->Add(hj[2]);
  
  hj[0]->Divide(h0[0]);
  
  return hj[0];

}

TH1F* Rhisto(TH1F *h0,TH1F *h1,TH1F *h2){
  h1->Add(h0);
  h1->Add(h2);
  h0->Divide(h1);
  return h0;
}

double RParton_value(int pol=0, int iquark=5,  float lum=900){

  TH1F *h0=GetHisto(4,TString::Format("h_Nparton_%i",0),pol,4,lum,1);
  TH1F *h1=GetHisto(4,TString::Format("h_Nparton_%i",1),pol,4,lum,1);
  TH1F *h2=GetHisto(4,TString::Format("h_Nparton_%i",2),pol,4,lum,1);

  TH1F *h;
  if(iquark==5) h=Rhisto(h0,h1,h2);
  if(iquark==4) h=Rhisto(h1,h0,h2);
  if(iquark==3) h=Rhisto(h2,h1,h0);
  TF1  *f1 = new TF1("f1","[0]",0,1.0);
  h->Fit("f1","QRME");
  return f1->GetParameter(0);
  
}


TH1F* RCheat(int pol, int iquark=5,  float lum=900){

int ipdg1=0, ipdg2=1;
if(iquark==4) {
  ipdg1=1;
  ipdg2=0;
 }
  TH1F *h0=GetHisto(4,TString::Format("h_N0_%i",ipdg1),pol,4,lum,1);
  TH1F *h1=GetHisto(4,TString::Format("h_N0_%i",ipdg2),pol,4,lum,1);
  TH1F *h2=GetHisto(4,TString::Format("h_N0_%i",2),pol,4,lum,1);

  return Rhisto(h0,h1,h2);
}

TH1F* RParton(int pol=0, int iquark=5,  float lum=900){

  TH1F *h0=GetHisto(4,TString::Format("h_Nparton_%i",0),pol,4,lum,1);
  TH1F *h1=GetHisto(4,TString::Format("h_Nparton_%i",1),pol,4,lum,1);
  TH1F *h2=GetHisto(4,TString::Format("h_Nparton_%i",2),pol,4,lum,1);

  if(iquark==5) return Rhisto(h0,h1,h2);
  if(iquark==4) return Rhisto(h1,h0,h2);
  if(iquark==3) return Rhisto(h2,h1,h0);
  return NULL;
}


TH1F *epsilon_mistag_truth(int pol=0, int iquark=4, int iquark2=5, float lum=-1, float error=0) {

  TH1F * other_quark=MCuneff(4, pol, iquark, iquark2, -1);
  
  for(int i=0; i<other_quark->GetNbinsX()+1; i++) {
    double value=other_quark->GetBinContent(i);
    other_quark->SetBinContent(i,value*(1+error));
  }
  return other_quark;


}

TH1F *epsilon_mistag(int pol=0, int iquark=4, int iquark2=5, float lum=-1, float error=0) {

  TH1F * other_quark=MCuneff(4, pol, iquark, iquark2, -1);
  TF1  *f1 = new TF1("f1","[0]+[1]*x",0,0.9);

  other_quark->Fit("f1","QRME");

  double a=f1->GetParameter(0);
  double b=f1->GetParameter(1);
  double ea=f1->GetParError(0);
  double eb=f1->GetParError(1);

  for(int i=0; i<other_quark->GetNbinsX()+1; i++) {
    double value=a+b*other_quark->GetBinCenter(i);
    other_quark->SetBinContent(i,value);
    other_quark->SetBinError(i,sqrt(ea*ea+eb*eb*other_quark->GetBinCenter(i)*other_quark->GetBinCenter(i)));
    
  }

  return other_quark;


}

TH1F *DT_R(TH1F* hf1=NULL, TH1F* hf2=NULL, TH1F* eff_quark=NULL, TH1F* rho_MC=NULL, double RQ=0, TH1F* mistag_heavy=NULL , TH1F* mistag_uds=NULL ) {

  TH1F *R = (TH1F*)hf2->Clone("R");

  for(int i=0; i<R->GetNbinsX()+1; i++) {

    double f1=hf1->GetBinContent(i);
    double f2=hf2->GetBinContent(i);
    double ef2=hf2->GetBinError(i);
    double ef1=hf1->GetBinError(i);
    double euds=mistag_uds->GetBinContent(i);
    double eQ=mistag_heavy->GetBinContent(i);
    double rho=rho_MC->GetBinContent(i);
    double eff=eff_quark->GetBinContent(i);
    double err_eff=eff_quark->GetBinError(i);

    double a1= (f1-RQ*(eQ-euds)-euds);
    double rq= a1/ (eff-euds);

    //rq=(f2)/(eff*eff*rho);
    R->SetBinContent(i, rq);
    double e1=ef2/(eff*eff*rho);
    double e2=2*f2*err_eff/(eff*eff*eff*rho);

    //double e1=ef1/(eff-euds);
    //double e2=a1*err_eff/pow(eff-euds,2);

    // e1=ef2*f2/(2*sqrt(f2/Rtheory)*Rtheory*Rtheory);
    // e2=(1-rho)*(1-rho)/(4.*Rtheory*f2*rho*rho);
    R->SetBinError(i,sqrt(e1*e1+e2*e2));
  }
  return R;

}

TH1F *epsilon_tag(double Rtheory=0.5, double RQ=0.5, TH1F* hf1=NULL, TH1F* hf2=NULL, TH1F* mstag_heavy=NULL, TH1F* mstag_light=NULL, TH1F * rho_MC=NULL, bool onlystats=false) {

  TH1F *heff = (TH1F*)hf2->Clone("heff");

  for(int i=0; i<heff->GetNbinsX()+1; i++) {
    double f1=hf1->GetBinContent(i);
    double f2=hf2->GetBinContent(i);
    double ef2=hf2->GetBinError(i);
    double ef1=hf1->GetBinError(i);
    double euds=mstag_light->GetBinContent(i);
    double eQ=mstag_heavy->GetBinContent(i);
    double rho=rho_MC->GetBinContent(i);
					   
    
    double a1= (f1-RQ*(eQ-euds)-euds);
    double a= a1*(rho);
    double a2=f2-RQ*(eQ*eQ-euds*euds)-euds*euds;
    double b= -a2;
    double c= -euds*euds +euds*a2;
    double epsilon1= (-b+sqrt(b*b-4*a*c))/(2*a);
    double epsilon2= (-b-sqrt(b*b-4*a*c))/(2*a);

    if(epsilon1>epsilon2 && epsilon1<1 && epsilon1>0) heff->SetBinContent(i,epsilon1);
    else if(epsilon2>epsilon1 && epsilon2<1 && epsilon2>0)  heff->SetBinContent(i,epsilon2);
    else heff->SetBinContent(i,0);
    // double e1=ef2*ef2/(4*Rtheory*rho*f2);
    double e1=ef2*f2/(2*sqrt(f2/Rtheory)*Rtheory*Rtheory);
    double e2=(1-rho)*(1-rho)/(4.*Rtheory*f2*rho*rho);
    if(onlystats==false)heff->SetBinError(i,sqrt(e1*e1+e2*e2));
    else heff->SetBinError(i,sqrt(e1*e1));
  }
  return heff;

}


void fit_Rq(TH1F* h, TString title, double xmax=1) {

  TF1  *f1 = new TF1("f1","[0]",0,xmax);
  h->Fit("f1","QRME");
  cout<<title<<" R:"<<f1->GetParameter(0)<<" Error:"<<f1->GetParError(0)<<" ("<<100.*f1->GetParError(0)/f1->GetParameter(0)<<"/%)"<<endl;
  
}


void fit_Rq(TH1F* h1, TH1F* h2, TString title, double xmax=1) {

  TF1  *f1 = new TF1("f1","[0]",0,xmax);
  h1->Fit("f1","QRME");
  TF1  *f2 = new TF1("f2","[0]",0,xmax);
  h2->Fit("f2","QRME");
  cout<<title<<" R:"<<(f1->GetParameter(0)+f2->GetParameter(0))/2.<<" Error:"<<fabs(f1->GetParameter(0)-f2->GetParameter(0))/2.<<" ("<<100.*fabs(f1->GetParameter(0)-f2->GetParameter(0))/(f1->GetParameter(0)+f2->GetParameter(0))<<"/%)"<<endl;

}


float fit_Rq_value(TH1F* h1, double xmax=1) {

  TF1  *f1 = new TF1("f1","[0]",0,xmax);
  h1->Fit("f1","QRME");
  //  cout<<f1->GetParameter(0)<<endl;
  return f1->GetParameter(0);
}

  



