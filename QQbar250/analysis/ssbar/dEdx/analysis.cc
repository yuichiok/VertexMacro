#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString output, bool ignoreoverlay, bool angularcorrection){

  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.PID.root";

  observable ss3(file);
  ss3.dEdx(-1,output,true,ignoreoverlay,angularcorrection);
  ss3.dEdx(-1,output,false,ignoreoverlay,angularcorrection);
  
  gSystem->Exit(0);

  return 0;
}
