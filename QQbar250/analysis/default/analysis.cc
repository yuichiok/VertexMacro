#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(){

  TString pol="eL";
  TString id="15161";
  int cuts=12;
  float Kv=35;
  float btag1=0.8;
  float btag2=0.8;

//  TString file = "/home/airqui/nextcloud_cernbox/QQbar/processor_output_2020/bbbar"+id+"_radret_250GeV_mc2020_"+pol+"_ValenciaVertexBeam_R1.17_short.root";
//  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15161/000/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.MERGED.root";
  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/000/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root";
  
  cout<< " ######################################################################### "<<endl; 
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<<" --------------------  btag1="<<btag1<<", btag2="<<btag2<<"  ---------------------------- "<<endl;

  observable ss_0(file);
  ss_0.process=TString::Format("bbbar_Kgamma%i_%s_cuts%i",int(Kv),id.Data(),cuts);
  ss_0.btag1=btag1;
  ss_0.btag2=btag2;
  ss_0.Analysis(-1,pol,40,cuts,Kv);

  gSystem->Exit(0);
  
  // file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_250fb_"+id+".root";
  // if(pol=="eL") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_72fb_"+ id+".root";
  // cout<< " "<<endl;
  // cout<< file << endl;
  // observable ss_4(file);
  // ss_4.process=TString::Format("bkg_Kgamma%i_WW_%s_cuts%i",int(Kv),id.Data(),cuts);
  // ss_4.btag1=btag1;
  // ss_4.btag2=btag2;
  // ss_4.AnalysisBKG(-1,pol,40,cuts,Kv);


  //  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_ZZ_250GeV_DBD_"+pol+"_250fb_"+id+".root";
  // cout<< " "<<endl;
  // cout<< file << endl;
  // observable ss_6(file);
  // ss_6.process=TString::Format("bkg_Kgamma%i_ZZ_%s_cuts%i",int(Kv),id.Data(),cuts);
  // ss_6.btag1=btag1;
  // ss_6.btag2=btag2;
  // ss_6.AnalysisBKG(-1,pol,40,cuts,Kv);

  // if(pol=="eL") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_353fb_"+id+".root";
  // if(pol=="eR") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_550fb_"+id+".root";
  // cout<< " "<<endl;
  // cout<< file << endl;
  // observable ss_8(file);
  // ss_8.process=TString::Format("bkg_Kgamma%i_HZ_%s_cuts%i",int(Kv),id.Data(),cuts);
  // ss_8.btag1=btag1;
  // ss_8.btag2=btag2;
  // ss_8.AnalysisBKG(-1,pol,40,cuts,Kv);
  

  
  gSystem->Exit(0);

  return 0;
}
