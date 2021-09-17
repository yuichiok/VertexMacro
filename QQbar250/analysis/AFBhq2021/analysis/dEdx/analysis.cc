#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, TString output, bool ignoreoverlay, int cut, int quark){

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  cout<<file<<endl;
  observable ss3(file);
  
  ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),cut),true,ignoreoverlay,float(cut),quark); 

  //  ss3.dEdx(-1,output,false,ignoreoverlay);
  
  gSystem->Exit(0);

  return 0;
}
