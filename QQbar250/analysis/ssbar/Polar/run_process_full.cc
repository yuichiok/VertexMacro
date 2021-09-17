#include "TROOT.h"
#include "TFile.h"
#include "AnaPolar.cc"
#include "VecOP.cc"
#include "TApplication.h"

int run_process_full(float wk=10){

  TString pol="eL";
  TString id="15162";

  wk = wk * 0.1;

  TString uds="uds";
  TString uu ="uu";
  TString ss ="ss";
  TString dd ="dd";

  // float wk = 0.5;

  // TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";
  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";
  
  AnaPolar AnaPolar(file);
  AnaPolar.AnalyzePolar(-1,wk,uds);
  AnaPolar.AnalyzePolar(-1,wk,uu);
  AnaPolar.AnalyzePolar(-1,wk,dd);
  AnaPolar.AnalyzePolar(-1,wk,ss);

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );


  gSystem->Exit(0);

  return 0;
}
