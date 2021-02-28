#include "TROOT.h"
#include "TFile.h"
#include "Hit.cc"
#include "TApplication.h"

int run_process(){

  TString pol="eL";
  TString id="15162";
  int cuts=12;
  float Kv=35;
  float btag1=0.8;
  float btag2=0.8;

  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root";
  
  Hit Hit(file);

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );


  gSystem->Exit(0);

  return 0;
}
