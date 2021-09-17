#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_jettag( TString file="", TString process="2f_hadronic", TString pol="eL", int file_n=0, int type=4, float Kv=35){

  TString s_type=TString::Format("cuts%i_",type);
  cout<< " "<<endl;
  cout<< file << endl;
  QQbarAnalysisClass ss3(file);
  if(file_n<10) ss3.process=s_type+process+"_"+pol+TString::Format("_file_00%i",file_n);
  else if(file_n<100) ss3.process=s_type+process+"_"+pol+TString::Format("_file_0%i",file_n);
  else ss3.process=s_type+process+"_"+pol+TString::Format("_file_%i",file_n);

  ss3.JetTag(-1,type,Kv);
  gSystem->Exit(0);

  return 0;
}
