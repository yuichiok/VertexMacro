//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb 28 17:10:29 2021 by ROOT version 6.18/04
// from TTree Stats/tree
// found on file: /group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root
//////////////////////////////////////////////////////////

#ifndef AnaPolar_hh
#define AnaPolar_hh

#include "include/VecOP.hh"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>


// Header file for the classes stored in the TTree if any.

class AnaPolar {
public :
   float btag1=0.8;
   float btag2=0.8;

   float ctag1=0.225;
   float ctag2=0.225;

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         mc_quark_E[2];
   Float_t         mc_quark_px[2];
   Float_t         mc_quark_py[2];
   Float_t         mc_quark_pz[2];
   Float_t         mc_quark_m[2];
   Float_t         mc_quark_pdg[2];
   Float_t         mc_quark_charge[2];
   Float_t         mc_ISR_E[2];
   Float_t         mc_ISR_px[2];
   Float_t         mc_ISR_py[2];
   Float_t         mc_ISR_pz[2];
   Float_t         mc_ISR_m[2];
   Float_t         mc_ISR_pdg[2];
   Float_t         mc_ISR_charge[2];
   Int_t           mc_quark_ps_n;
   Float_t         mc_quark_ps_E[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_px[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_py[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_pz[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_m[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_pdg[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_charge[25];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_y12;
   Float_t         mc_quark_ps_y23;
   Float_t         mc_quark_ps_d12;
   Float_t         mc_quark_ps_d23;
   Float_t         mc_quark_ps_jet_E[2];
   Float_t         mc_quark_ps_jet_px[2];
   Float_t         mc_quark_ps_jet_py[2];
   Float_t         mc_quark_ps_jet_pz[2];
   Int_t           mc_stable_n;
   Float_t         mc_stable_E[746];   //[mc_stable_n]
   Float_t         mc_stable_px[746];   //[mc_stable_n]
   Float_t         mc_stable_py[746];   //[mc_stable_n]
   Float_t         mc_stable_pz[746];   //[mc_stable_n]
   Float_t         mc_stable_m[746];   //[mc_stable_n]
   Int_t           mc_stable_pdg[746];   //[mc_stable_n]
   Float_t         mc_stable_charge[746];   //[mc_stable_n]
   Int_t           mc_stable_isoverlay[746];   //[mc_stable_n]
   Int_t           mc_stable_isisr[746];   //[mc_stable_n]
   Float_t         mc_stable_y12;
   Float_t         mc_stable_y23;
   Float_t         mc_stable_d12;
   Float_t         mc_stable_d23;
   Float_t         mc_stable_jet_E[2];
   Float_t         mc_stable_jet_px[2];
   Float_t         mc_stable_jet_py[2];
   Float_t         mc_stable_jet_pz[2];
   Float_t         jet_E[2];
   Float_t         jet_px[2];
   Float_t         jet_py[2];
   Float_t         jet_pz[2];
   Float_t         jet_btag[2];
   Float_t         jet_ctag[2];
   Float_t         y23;
   Float_t         y12;
   Float_t         d23;
   Float_t         d12;
   Float_t         oblateness;
   Float_t         aplanarity;
   Float_t         major_thrust_value;
   Float_t         major_thrust_axis[3];
   Float_t         minor_thrust_value;
   Float_t         minor_thrust_axis[3];
   Float_t         principle_thrust_value;
   Float_t         principle_thrust_axis[3];
   Float_t         sphericity;
   Float_t         sphericity_tensor[3];
   Int_t           pfo_n;
   Int_t           jet_nvtx;
   Int_t           pfo_n_j1;
   Int_t           jet_nvtx_j1;
   Int_t           pfo_n_j2;
   Int_t           jet_nvtx_j2;
   Int_t           pfo_match[188];   //[pfo_n]
   Int_t           pfo_pdgcheat[188];   //[pfo_n]
   Int_t           pfo_pdgcheat_parent[188];   //[pfo_n]
   Float_t         pfo_E[188];   //[pfo_n]
   Float_t         pfo_px[188];   //[pfo_n]
   Float_t         pfo_py[188];   //[pfo_n]
   Float_t         pfo_pz[188];   //[pfo_n]
   Float_t         pfo_m[188];   //[pfo_n]
   Int_t           pfo_type[188];   //[pfo_n]
   Int_t           pfo_isoverlay[188];   //[pfo_n]
   Int_t           pfo_isisr[188];   //[pfo_n]
   Int_t           pfo_vtx[188];   //[pfo_n]
   Int_t           pfo_charge[188];   //[pfo_n]
   Int_t           pfo_ntracks[188];   //[pfo_n]
   Int_t           pfo_tpc_hits[188];   //[pfo_n]
   Float_t         pfo_dedx[188];   //[pfo_n]
   Float_t         pfo_dedxerror[188];   //[pfo_n]
   Float_t         pfo_d0[188];   //[pfo_n]
   Float_t         pfo_d0error[188];   //[pfo_n]
   Float_t         pfo_z0[188];   //[pfo_n]
   Float_t         pfo_z0error[188];   //[pfo_n]
   Float_t         pfo_phi[188];   //[pfo_n]
   Float_t         pfo_phierror[188];   //[pfo_n]
   Float_t         pfo_omega[188];   //[pfo_n]
   Float_t         pfo_omegaerror[188];   //[pfo_n]
   Float_t         pfo_tanlambda[188];   //[pfo_n]
   Float_t         pfo_tanlambdaerror[188];   //[pfo_n]
   Float_t         pfo_chi2[188];   //[pfo_n]
   Float_t         pfo_ndf[188];   //[pfo_n]
   Int_t           pfo_pid[188];   //[pfo_n]
   Float_t         pfo_pid_likelihood[188];   //[pfo_n]
   Float_t         pfo_pid_eprob[188];   //[pfo_n]
   Float_t         pfo_pid_muprob[188];   //[pfo_n]
   Float_t         pfo_pid_piprob[188];   //[pfo_n]
   Float_t         pfo_pid_kprob[188];   //[pfo_n]
   Float_t         pfo_pid_pprob[188];   //[pfo_n]
   Float_t         pfo_pid_hprob[188];   //[pfo_n]
   Int_t           pfo_piddedx[188];   //[pfo_n]
   Float_t         pfo_piddedx_likelihood[188];   //[pfo_n]
   Float_t         pfo_piddedx_eprob[188];   //[pfo_n]
   Float_t         pfo_piddedx_muprob[188];   //[pfo_n]
   Float_t         pfo_piddedx_piprob[188];   //[pfo_n]
   Float_t         pfo_piddedx_kprob[188];   //[pfo_n]
   Float_t         pfo_piddedx_pprob[188];   //[pfo_n]
   Float_t         pfo_piddedx_hprob[188];   //[pfo_n]

   // List of branches
   TBranch        *b_mc_quark_E;   //!
   TBranch        *b_mc_quark_px;   //!
   TBranch        *b_mc_quark_py;   //!
   TBranch        *b_mc_quark_pz;   //!
   TBranch        *b_mc_quark_m;   //!
   TBranch        *b_mc_quark_pdg;   //!
   TBranch        *b_mc_quark_charge;   //!
   TBranch        *b_mc_ISR_E;   //!
   TBranch        *b_mc_ISR_px;   //!
   TBranch        *b_mc_ISR_py;   //!
   TBranch        *b_mc_ISR_pz;   //!
   TBranch        *b_mc_ISR_m;   //!
   TBranch        *b_mc_ISR_pdg;   //!
   TBranch        *b_mc_ISR_charge;   //!
   TBranch        *b_mc_quark_ps_n;   //!
   TBranch        *b_mc_quark_ps_E;   //!
   TBranch        *b_mc_quark_ps_px;   //!
   TBranch        *b_mc_quark_ps_py;   //!
   TBranch        *b_mc_quark_ps_pz;   //!
   TBranch        *b_mc_quark_ps_m;   //!
   TBranch        *b_mc_quark_ps_pdg;   //!
   TBranch        *b_mc_quark_ps_charge;   //!
   TBranch        *b_mc_quark_ps_y12;   //!
   TBranch        *b_mc_quark_ps_y23;   //!
   TBranch        *b_mc_quark_ps_d12;   //!
   TBranch        *b_mc_quark_ps_d23;   //!
   TBranch        *b_mc_quark_ps_jet_E;   //!
   TBranch        *b_mc_quark_ps_jet_px;   //!
   TBranch        *b_mc_quark_ps_jet_py;   //!
   TBranch        *b_mc_quark_ps_jet_pz;   //!
   TBranch        *b_mc_stable_n;   //!
   TBranch        *b_mc_stable_E;   //!
   TBranch        *b_mc_stable_px;   //!
   TBranch        *b_mc_stable_py;   //!
   TBranch        *b_mc_stable_pz;   //!
   TBranch        *b_mc_stable_m;   //!
   TBranch        *b_mc_stable_pdg;   //!
   TBranch        *b_mc_stable_charge;   //!
   TBranch        *b_mc_stable_isoverlay;   //!
   TBranch        *b_mc_stable_isisr;   //!
   TBranch        *b_mc_stable_y12;   //!
   TBranch        *b_mc_stable_y23;   //!
   TBranch        *b_mc_stable_d12;   //!
   TBranch        *b_mc_stable_d23;   //!
   TBranch        *b_mc_stable_jet_E;   //!
   TBranch        *b_mc_stable_jet_px;   //!
   TBranch        *b_mc_stable_jet_py;   //!
   TBranch        *b_mc_stable_jet_pz;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_px;   //!
   TBranch        *b_jet_py;   //!
   TBranch        *b_jet_pz;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_ctag;   //!
   TBranch        *b_y23;   //!
   TBranch        *b_y12;   //!
   TBranch        *b_d23;   //!
   TBranch        *b_d12;   //!
   TBranch        *b_oblateness;   //!
   TBranch        *b_aplanarity;   //!
   TBranch        *b_major_thrust_value;   //!
   TBranch        *b_major_thrust_axis;   //!
   TBranch        *b_minor_thrust_value;   //!
   TBranch        *b_minor_thrust_axis;   //!
   TBranch        *b_principle_thrust_value;   //!
   TBranch        *b_principle_thrust_axis;   //!
   TBranch        *b_sphericity;   //!
   TBranch        *b_sphericity_tensor;   //!
   TBranch        *b_pfo_n;   //!
   TBranch        *b_jet_nvtx;   //!
   TBranch        *b_pfo_n_j1;   //!
   TBranch        *b_jet_nvtx_j1;   //!
   TBranch        *b_pfo_n_j2;   //!
   TBranch        *b_jet_nvtx_j2;   //!
   TBranch        *b_pfo_match;   //!
   TBranch        *b_pfo_pdgcheat;   //!
   TBranch        *b_pfo_pdgcheat_parent;   //!
   TBranch        *b_pfo_E;   //!
   TBranch        *b_pfo_px;   //!
   TBranch        *b_pfo_py;   //!
   TBranch        *b_pfo_pz;   //!
   TBranch        *b_pfo_m;   //!
   TBranch        *b_pfo_type;   //!
   TBranch        *b_pfo_isoverlay;   //!
   TBranch        *b_pfo_isisr;   //!
   TBranch        *b_pfo_vtx;   //!
   TBranch        *b_pfo_charge;   //!
   TBranch        *b_pfo_ntracks;   //!
   TBranch        *b_pfo_tpc_hits;   //!
   TBranch        *b_pfo_dedx;   //!
   TBranch        *b_pfo_dedxerror;   //!
   TBranch        *b_pfo_d0;   //!
   TBranch        *b_pfo_d0error;   //!
   TBranch        *b_pfo_z0;   //!
   TBranch        *b_pfo_z0error;   //!
   TBranch        *b_pfo_phi;   //!
   TBranch        *b_pfo_phierror;   //!
   TBranch        *b_pfo_omega;   //!
   TBranch        *b_pfo_omegaerror;   //!
   TBranch        *b_pfo_tanlambda;   //!
   TBranch        *b_pfo_tanlambdaerror;   //!
   TBranch        *b_pfo_chi2;   //!
   TBranch        *b_pfo_ndf;   //!
   TBranch        *b_pfo_pid;   //!
   TBranch        *b_pfo_pid_likelihood;   //!
   TBranch        *b_pfo_pid_eprob;   //!
   TBranch        *b_pfo_pid_muprob;   //!
   TBranch        *b_pfo_pid_piprob;   //!
   TBranch        *b_pfo_pid_kprob;   //!
   TBranch        *b_pfo_pid_pprob;   //!
   TBranch        *b_pfo_pid_hprob;   //!
   TBranch        *b_pfo_piddedx;   //!
   TBranch        *b_pfo_piddedx_likelihood;   //!
   TBranch        *b_pfo_piddedx_eprob;   //!
   TBranch        *b_pfo_piddedx_muprob;   //!
   TBranch        *b_pfo_piddedx_piprob;   //!
   TBranch        *b_pfo_piddedx_kprob;   //!
   TBranch        *b_pfo_piddedx_pprob;   //!
   TBranch        *b_pfo_piddedx_hprob;   //!
   
   AnaPolar(TString tree_s);
   AnaPolar(TList *f=0);
   virtual ~AnaPolar();

   virtual void     printResults();
   virtual void     printProgress(double percentage);
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual bool     PreSelection(int type, float egamma);
   virtual void     LeadingMom(TH1F* h1p, TH1F* h1m, TH2F* h2, int subject, int iPFO0, int iPFO1, float P0, float P1);

   virtual void     AnalyzePolar(int, float, float, TString);

   float getAngle2Vec(float px1, float py1, float pz1, float E1, float px2, float py2, float pz2, float E2) {

      TLorentzVector v1(px1,py1,pz1,E1);
      TLorentzVector v2(px2,py2,pz2,E2);

      Double_t a = v1.Angle(v2.Vect());  // get angle between v1 and v2
      return a;
   }

private:

   TString process="default";

   int nevents = 0;
   int nevents_after_preselec = 0;
   int nevents_kaon_match = 0;

   int n_kk   = 0;
   int n_kpkm = 0;
   int n_kpkp = 0;
   int n_kmkm = 0;

   int nLeadK_pass  = 0;
   int nLeadK_match = 0;

   // TH1F* h1_mc_stable[10];
   // TH1F* h1_pfo[10];

   // TH2F* h2_mc_stable[10];
   // TH2F* h2_pfo[10];

   std::vector<TH1F*> h1_mc_stable;
   std::vector<TH1F*> h1_pfo;

   std::vector<TH2F*> h2_mc_stable;
   std::vector<TH2F*> h2_pfo;

};

#endif

#ifdef AnaPolar_cxx
AnaPolar::AnaPolar(TString tree_s) : fChain(0) 
{
   TFile *f = new TFile(tree_s);
   TTree *tree = (TTree*)f->Get("Stats");
   //  tree->Print();
   Init(tree);
}

AnaPolar::AnaPolar(TList *f) : fChain(0) 
{
   // if parameter tree is not specified (or zero), use a list of of files provided as input

   TIter next(f);
   TSystemFile *file;
   TString fname;
   while((file = (TSystemFile*)next())){
      fname = file->GetName();
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fname);
      TTree *tree=0;
      f->GetObject("Stats",tree);
      Init(tree);
   }
}

AnaPolar::~AnaPolar()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnaPolar::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnaPolar::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnaPolar::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mc_quark_E", mc_quark_E, &b_mc_quark_E);
   fChain->SetBranchAddress("mc_quark_px", mc_quark_px, &b_mc_quark_px);
   fChain->SetBranchAddress("mc_quark_py", mc_quark_py, &b_mc_quark_py);
   fChain->SetBranchAddress("mc_quark_pz", mc_quark_pz, &b_mc_quark_pz);
   fChain->SetBranchAddress("mc_quark_m", mc_quark_m, &b_mc_quark_m);
   fChain->SetBranchAddress("mc_quark_pdg", mc_quark_pdg, &b_mc_quark_pdg);
   fChain->SetBranchAddress("mc_quark_charge", mc_quark_charge, &b_mc_quark_charge);
   fChain->SetBranchAddress("mc_ISR_E", mc_ISR_E, &b_mc_ISR_E);
   fChain->SetBranchAddress("mc_ISR_px", mc_ISR_px, &b_mc_ISR_px);
   fChain->SetBranchAddress("mc_ISR_py", mc_ISR_py, &b_mc_ISR_py);
   fChain->SetBranchAddress("mc_ISR_pz", mc_ISR_pz, &b_mc_ISR_pz);
   fChain->SetBranchAddress("mc_ISR_m", mc_ISR_m, &b_mc_ISR_m);
   fChain->SetBranchAddress("mc_ISR_pdg", mc_ISR_pdg, &b_mc_ISR_pdg);
   fChain->SetBranchAddress("mc_ISR_charge", mc_ISR_charge, &b_mc_ISR_charge);
   fChain->SetBranchAddress("mc_quark_ps_n", &mc_quark_ps_n, &b_mc_quark_ps_n);
   fChain->SetBranchAddress("mc_quark_ps_E", mc_quark_ps_E, &b_mc_quark_ps_E);
   fChain->SetBranchAddress("mc_quark_ps_px", mc_quark_ps_px, &b_mc_quark_ps_px);
   fChain->SetBranchAddress("mc_quark_ps_py", mc_quark_ps_py, &b_mc_quark_ps_py);
   fChain->SetBranchAddress("mc_quark_ps_pz", mc_quark_ps_pz, &b_mc_quark_ps_pz);
   fChain->SetBranchAddress("mc_quark_ps_m", mc_quark_ps_m, &b_mc_quark_ps_m);
   fChain->SetBranchAddress("mc_quark_ps_pdg", mc_quark_ps_pdg, &b_mc_quark_ps_pdg);
   fChain->SetBranchAddress("mc_quark_ps_charge", mc_quark_ps_charge, &b_mc_quark_ps_charge);
   fChain->SetBranchAddress("mc_quark_ps_y12", &mc_quark_ps_y12, &b_mc_quark_ps_y12);
   fChain->SetBranchAddress("mc_quark_ps_y23", &mc_quark_ps_y23, &b_mc_quark_ps_y23);
   fChain->SetBranchAddress("mc_quark_ps_d12", &mc_quark_ps_d12, &b_mc_quark_ps_d12);
   fChain->SetBranchAddress("mc_quark_ps_d23", &mc_quark_ps_d23, &b_mc_quark_ps_d23);
   fChain->SetBranchAddress("mc_quark_ps_jet_E", mc_quark_ps_jet_E, &b_mc_quark_ps_jet_E);
   fChain->SetBranchAddress("mc_quark_ps_jet_px", mc_quark_ps_jet_px, &b_mc_quark_ps_jet_px);
   fChain->SetBranchAddress("mc_quark_ps_jet_py", mc_quark_ps_jet_py, &b_mc_quark_ps_jet_py);
   fChain->SetBranchAddress("mc_quark_ps_jet_pz", mc_quark_ps_jet_pz, &b_mc_quark_ps_jet_pz);
   fChain->SetBranchAddress("mc_stable_n", &mc_stable_n, &b_mc_stable_n);
   fChain->SetBranchAddress("mc_stable_E", mc_stable_E, &b_mc_stable_E);
   fChain->SetBranchAddress("mc_stable_px", mc_stable_px, &b_mc_stable_px);
   fChain->SetBranchAddress("mc_stable_py", mc_stable_py, &b_mc_stable_py);
   fChain->SetBranchAddress("mc_stable_pz", mc_stable_pz, &b_mc_stable_pz);
   fChain->SetBranchAddress("mc_stable_m", mc_stable_m, &b_mc_stable_m);
   fChain->SetBranchAddress("mc_stable_pdg", mc_stable_pdg, &b_mc_stable_pdg);
   fChain->SetBranchAddress("mc_stable_charge", mc_stable_charge, &b_mc_stable_charge);
   fChain->SetBranchAddress("mc_stable_isoverlay", mc_stable_isoverlay, &b_mc_stable_isoverlay);
   fChain->SetBranchAddress("mc_stable_isisr", mc_stable_isisr, &b_mc_stable_isisr);
   fChain->SetBranchAddress("mc_stable_y12", &mc_stable_y12, &b_mc_stable_y12);
   fChain->SetBranchAddress("mc_stable_y23", &mc_stable_y23, &b_mc_stable_y23);
   fChain->SetBranchAddress("mc_stable_d12", &mc_stable_d12, &b_mc_stable_d12);
   fChain->SetBranchAddress("mc_stable_d23", &mc_stable_d23, &b_mc_stable_d23);
   fChain->SetBranchAddress("mc_stable_jet_E", mc_stable_jet_E, &b_mc_stable_jet_E);
   fChain->SetBranchAddress("mc_stable_jet_px", mc_stable_jet_px, &b_mc_stable_jet_px);
   fChain->SetBranchAddress("mc_stable_jet_py", mc_stable_jet_py, &b_mc_stable_jet_py);
   fChain->SetBranchAddress("mc_stable_jet_pz", mc_stable_jet_pz, &b_mc_stable_jet_pz);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_px", jet_px, &b_jet_px);
   fChain->SetBranchAddress("jet_py", jet_py, &b_jet_py);
   fChain->SetBranchAddress("jet_pz", jet_pz, &b_jet_pz);
   fChain->SetBranchAddress("jet_btag", jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("jet_ctag", jet_ctag, &b_jet_ctag);
   fChain->SetBranchAddress("y23", &y23, &b_y23);
   fChain->SetBranchAddress("y12", &y12, &b_y12);
   fChain->SetBranchAddress("d23", &d23, &b_d23);
   fChain->SetBranchAddress("d12", &d12, &b_d12);
   fChain->SetBranchAddress("oblateness", &oblateness, &b_oblateness);
   fChain->SetBranchAddress("aplanarity", &aplanarity, &b_aplanarity);
   fChain->SetBranchAddress("major_thrust_value", &major_thrust_value, &b_major_thrust_value);
   fChain->SetBranchAddress("major_thrust_axis", major_thrust_axis, &b_major_thrust_axis);
   fChain->SetBranchAddress("minor_thrust_value", &minor_thrust_value, &b_minor_thrust_value);
   fChain->SetBranchAddress("minor_thrust_axis", minor_thrust_axis, &b_minor_thrust_axis);
   fChain->SetBranchAddress("principle_thrust_value", &principle_thrust_value, &b_principle_thrust_value);
   fChain->SetBranchAddress("principle_thrust_axis", principle_thrust_axis, &b_principle_thrust_axis);
   fChain->SetBranchAddress("sphericity", &sphericity, &b_sphericity);
   fChain->SetBranchAddress("sphericity_tensor", sphericity_tensor, &b_sphericity_tensor);
   fChain->SetBranchAddress("pfo_n", &pfo_n, &b_pfo_n);
   fChain->SetBranchAddress("jet_nvtx", &jet_nvtx, &b_jet_nvtx);
   fChain->SetBranchAddress("pfo_n_j1", &pfo_n_j1, &b_pfo_n_j1);
   fChain->SetBranchAddress("jet_nvtx_j1", &jet_nvtx_j1, &b_jet_nvtx_j1);
   fChain->SetBranchAddress("pfo_n_j2", &pfo_n_j2, &b_pfo_n_j2);
   fChain->SetBranchAddress("jet_nvtx_j2", &jet_nvtx_j2, &b_jet_nvtx_j2);
   fChain->SetBranchAddress("pfo_match", pfo_match, &b_pfo_match);
   fChain->SetBranchAddress("pfo_pdgcheat", pfo_pdgcheat, &b_pfo_pdgcheat);
   fChain->SetBranchAddress("pfo_pdgcheat_parent", pfo_pdgcheat_parent, &b_pfo_pdgcheat_parent);
   fChain->SetBranchAddress("pfo_E", pfo_E, &b_pfo_E);
   fChain->SetBranchAddress("pfo_px", pfo_px, &b_pfo_px);
   fChain->SetBranchAddress("pfo_py", pfo_py, &b_pfo_py);
   fChain->SetBranchAddress("pfo_pz", pfo_pz, &b_pfo_pz);
   fChain->SetBranchAddress("pfo_m", pfo_m, &b_pfo_m);
   fChain->SetBranchAddress("pfo_type", pfo_type, &b_pfo_type);
   fChain->SetBranchAddress("pfo_isoverlay", pfo_isoverlay, &b_pfo_isoverlay);
   fChain->SetBranchAddress("pfo_isisr", pfo_isisr, &b_pfo_isisr);
   fChain->SetBranchAddress("pfo_vtx", pfo_vtx, &b_pfo_vtx);
   fChain->SetBranchAddress("pfo_charge", pfo_charge, &b_pfo_charge);
   fChain->SetBranchAddress("pfo_ntracks", pfo_ntracks, &b_pfo_ntracks);
   fChain->SetBranchAddress("pfo_tpc_hits", pfo_tpc_hits, &b_pfo_tpc_hits);
   fChain->SetBranchAddress("pfo_dedx", pfo_dedx, &b_pfo_dedx);
   fChain->SetBranchAddress("pfo_dedxerror", pfo_dedxerror, &b_pfo_dedxerror);
   fChain->SetBranchAddress("pfo_d0", pfo_d0, &b_pfo_d0);
   fChain->SetBranchAddress("pfo_d0error", pfo_d0error, &b_pfo_d0error);
   fChain->SetBranchAddress("pfo_z0", pfo_z0, &b_pfo_z0);
   fChain->SetBranchAddress("pfo_z0error", pfo_z0error, &b_pfo_z0error);
   fChain->SetBranchAddress("pfo_phi", pfo_phi, &b_pfo_phi);
   fChain->SetBranchAddress("pfo_phierror", pfo_phierror, &b_pfo_phierror);
   fChain->SetBranchAddress("pfo_omega", pfo_omega, &b_pfo_omega);
   fChain->SetBranchAddress("pfo_omegaerror", pfo_omegaerror, &b_pfo_omegaerror);
   fChain->SetBranchAddress("pfo_tanlambda", pfo_tanlambda, &b_pfo_tanlambda);
   fChain->SetBranchAddress("pfo_tanlambdaerror", pfo_tanlambdaerror, &b_pfo_tanlambdaerror);
   fChain->SetBranchAddress("pfo_chi2", pfo_chi2, &b_pfo_chi2);
   fChain->SetBranchAddress("pfo_ndf", pfo_ndf, &b_pfo_ndf);
   fChain->SetBranchAddress("pfo_pid", pfo_pid, &b_pfo_pid);
   fChain->SetBranchAddress("pfo_pid_likelihood", pfo_pid_likelihood, &b_pfo_pid_likelihood);
   fChain->SetBranchAddress("pfo_pid_eprob", pfo_pid_eprob, &b_pfo_pid_eprob);
   fChain->SetBranchAddress("pfo_pid_muprob", pfo_pid_muprob, &b_pfo_pid_muprob);
   fChain->SetBranchAddress("pfo_pid_piprob", pfo_pid_piprob, &b_pfo_pid_piprob);
   fChain->SetBranchAddress("pfo_pid_kprob", pfo_pid_kprob, &b_pfo_pid_kprob);
   fChain->SetBranchAddress("pfo_pid_pprob", pfo_pid_pprob, &b_pfo_pid_pprob);
   fChain->SetBranchAddress("pfo_pid_hprob", pfo_pid_hprob, &b_pfo_pid_hprob);
   fChain->SetBranchAddress("pfo_piddedx", pfo_piddedx, &b_pfo_piddedx);
   fChain->SetBranchAddress("pfo_piddedx_likelihood", pfo_piddedx_likelihood, &b_pfo_piddedx_likelihood);
   fChain->SetBranchAddress("pfo_piddedx_eprob", pfo_piddedx_eprob, &b_pfo_piddedx_eprob);
   fChain->SetBranchAddress("pfo_piddedx_muprob", pfo_piddedx_muprob, &b_pfo_piddedx_muprob);
   fChain->SetBranchAddress("pfo_piddedx_piprob", pfo_piddedx_piprob, &b_pfo_piddedx_piprob);
   fChain->SetBranchAddress("pfo_piddedx_kprob", pfo_piddedx_kprob, &b_pfo_piddedx_kprob);
   fChain->SetBranchAddress("pfo_piddedx_pprob", pfo_piddedx_pprob, &b_pfo_piddedx_pprob);
   fChain->SetBranchAddress("pfo_piddedx_hprob", pfo_piddedx_hprob, &b_pfo_piddedx_hprob);
   Notify();
}

Bool_t AnaPolar::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnaPolar::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnaPolar::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Hit_cxx
