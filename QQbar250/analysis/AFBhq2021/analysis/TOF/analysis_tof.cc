#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis_tof(TString file, TString output, bool ignoreoverlay){

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  cout<<file<<endl;
  observable ss3(file);
  
  for(int i=0; i<5; i++) {
    int j=i;
    
    //cut2 GeV, 1= standard cut 
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),true,ignoreoverlay,j,2,1);
    //cut2GeV, include soft tracks
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),true,ignoreoverlay,j,2,0);
    //cut5 GeV, 1= standard cut                             
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),true,ignoreoverlay,j,5,1);
    //cut5GeV, include soft tracks             
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),true,ignoreoverlay,j,5,0);
    //cut5 250eV, 1= standard cut
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),true,ignoreoverlay,j,250,1);
    //cut250GeV, include soft tracks 
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),true,ignoreoverlay,j,250,0);
    
    
    //cut2 GeV, 1= standard cut
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),false,ignoreoverlay,j,2,1);
    //cut2GeV, include soft tracks    
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),false,ignoreoverlay,j,2,0);
    //cut5 GeV, 1= standard cut       
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),false,ignoreoverlay,j,5,1);
    //cut5GeV, include soft tracks    
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),false,ignoreoverlay,j,5,0);
    //cut5 250eV, 1= standard cut     
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),false,ignoreoverlay,j,250,1);
    //cut250GeV, include soft tracks  
    ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),j),false,ignoreoverlay,j,250,0);

  }
    
  
  //ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),2),true,ignoreoverlay,2.);
  //  ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),0),true,ignoreoverlay,0.);
  //  ss3.dEdx(-1,output,false,ignoreoverlay);
  
  gSystem->Exit(0);

  return 0;
}
