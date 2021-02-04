#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(){

//  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15161/000/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.MERGED.root";
  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/000/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root";
  TString output = "bbbar_Kgamma35_15162_cuts12_250GeV_eL_btag1_0.8_btag2_0.8_nbins40";

  cout<< " "<<endl;
  cout<< file << endl;
  observable ss3(file);
  ss3.process=output;
  ss3.dEdx(-1);

  
  gSystem->Exit(0);

  return 0;
}
