#include "TROOT.h"
#include "TFile.h"
#include "PreSelec.cc"
#include "src/VecOP.cc"
#include "TApplication.h"

int run_process(TString process="default",TString file="default",TString fileout="default"){

  TString pol="eL";
  TString id="15162";

  float minp = 20.;
  
  PreSelec PreSelec(file);
  PreSelec.PreSelection(-1,minp,process,fileout);

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 200 );


  gSystem->Exit(0);

  return 0;
}
