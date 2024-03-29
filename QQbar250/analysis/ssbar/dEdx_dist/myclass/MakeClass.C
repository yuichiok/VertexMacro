#include "TROOT.h"
#include "TFile.h"

int MakeClass(){

  TString filename = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.n002.d_dstm_15162_002.root";
  TFile *file = new TFile(filename);

  TString treename = "Stats";
  TTree* tree = (TTree*)file->Get( treename ) ;

  file->ls();

  tree->MakeClass("dEdx_dist");

  std::cout << "processed..." << std::endl;

  return 0;


}