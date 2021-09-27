#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

// int analysis(TString file, TString output, bool ignoreoverlay, int cut, int quark){
int analysis(){

  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.400.root";
  TString output = "/home/ilc/yokugawa/macros/QQbar250/analysis/AFBhq2021/analysis/dEdx/rootfiles/dEdx_out.root";

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  observable ss3(file);
  
  // ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),cut),true,ignoreoverlay,float(cut),quark); 
  ss3.dEdx(-1,output,false,true,0,3); 

  //  ss3.dEdx(-1,output,false,ignoreoverlay);
  
  gSystem->Exit(0);

  return 0;
}
