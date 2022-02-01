#include "TROOT.h"
#include "TFile.h"
#include "dEdx_dist.cc"
#include "src/VecOP.cc"
#include "TApplication.h"

int run_process(TString output="default"){

  TString pol="eL";
  TString id="15162";

  float minp = 10.;

  // TString output="uds";
  // TString output="uu";
  // TString output=Form("uu_wk%g",wk);

  // TString output="ss";
  // TString output="dd";




  // float wk = 0.5;

  // TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";
  // TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";
  // TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.400.root";
  TString file = "/afs/cern.ch/work/y/yuokugaw/DataSets/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.400.root";
  
  dEdx_dist dEdx_dist(file);
  dEdx_dist.Analyze_dEdxdist(-1,minp,output);

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );


  gSystem->Exit(0);

  return 0;
}
