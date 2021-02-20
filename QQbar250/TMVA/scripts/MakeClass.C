#include "TROOT.h"
#include "TFile.h"

int MakeClass(){

  TString filename = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/adrian_sample/bbbar15162_radret_250GeV_mc2020_eL_ValenciaVertexBeam_R1.17_short2.root";
  TFile *file = new TFile(filename);

  TString treename = "Stats";
  TTree* tree = (TTree*)file->Get( treename ) ;

  file->ls();

  tree->MakeClass("sig_bg");

  std::cout << "processed..." << std::endl;

  return 0;


}