#include "TROOT.h"
#include "TFile.h"
#include "kaon_info.cc"
#include "TApplication.h"

int run_process(){

  TString pol="eL";
  TString id="15161";
  int cuts=12;
  float Kv=35;
  float btag1=0.8;
  float btag2=0.8;

  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/adrian_sample/bbbar15162_radret_250GeV_mc2020_eL_ValenciaVertexBeam_R1.17_short2.root";
  
  kaon_info ki(file);
  ki.process=TString::Format("bbbar_Kgamma%i_%s_cuts%i",int(Kv),id.Data(),cuts);
  ki.btag1=btag1;
  ki.btag2=btag2;

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );


  // for(int po=2; po<5;po++){

  //   float power = 0.02 + 0.01*po;

  //   std::cout << "//////// power = " << power << "////////" << std::endl;

  //   ki.Analysis(-1,pol,power,Kv);
  
  // }


  ki.Analysis(-1,pol,0.05,Kv);

  gSystem->Exit(0);

  return 0;
}
