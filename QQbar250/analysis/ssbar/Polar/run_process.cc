#include "TROOT.h"
#include "TFile.h"
#include "AnaPolar.cc"
#include "VecOP.cc"
#include "TApplication.h"

int run_process(){

  TString pol="eL";
  TString id="15162";
  // TString output="OppChg";

  TString output="uds";
  // TString output="uu";
  // TString output="ss";

  int cuts=12;
  float Kv=35;
  float btag1=0.8;
  float btag2=0.8;

  // TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";
  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";
  
  AnaPolar AnaPolar(file);
  AnaPolar.AnalyzeLeadK(-1,Kv,output);

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );


  gSystem->Exit(0);

  return 0;
}
