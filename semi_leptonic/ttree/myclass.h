//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep  7 18:00:15 2018 by ROOT version 5.34/30
// from TTree Stats/tree
// found on file: leptonic_yyxylv_eLeR_iso_lep_lcut_090418.root
//////////////////////////////////////////////////////////

#ifndef myclass_h
#define myclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class myclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           mctag;
   Float_t         MCTopmass;
   Float_t         MCquarkAngle;
   Float_t         MCTopmomentum;
   Float_t         MCTopcostheta;
   Float_t         MCTopBarmass;
   Float_t         MCTopBarmomentum;
   Float_t         MCTopBarcostheta;
   Float_t         MCTopBangle;
   Float_t         MCTopcosWb;
   Float_t         MCNeutrinoEnergy;
   Int_t           MCLeptonPDG;
   Float_t         MCLeptonMomentum;
   Float_t         MCLeptonCostheta;
   Int_t           MCBOscillation;
   Int_t           MCBBarOscillation;
   Int_t           MCBWcorrect;
   Float_t         qMCBcostheta[2];
   Float_t         qMCcostheta[2];
   Float_t         totalEnergy;
   Float_t         bProduct;
   Float_t         hadMass;
   Float_t         missedEnergy;
   Float_t         W1mass;
   Float_t         W1gamma;
   Float_t         W1momentum;
   Float_t         W1costheta;
   Float_t         W2mass;
   Float_t         W2momentum;
   Float_t         W2costheta;
   Float_t         Top1mass;
   Float_t         Top1gamma;
   Float_t         Top1btag;
   Float_t         Top1energy;
   Int_t           Top1bcharge;
   Float_t         Top1bmomentum;
   Float_t         Top1bdistance;
   Float_t         Top1costheta;
   Float_t         Top1bcostheta;
   Float_t         Top1truthAngle;
   Int_t           Top1bntracks;
   Int_t           Top1bTVCM;
   Float_t         Top1cosWb;
   Float_t         Top1pstarb;
   Int_t           Top1Vtx;
   Int_t           Top1Kaon;
   Int_t           Top1KaonNumber;
   Int_t           Top1KaonCharges[6];   //[Top1KaonNumber]
   Float_t         Top1KaonMomentum[6];   //[Top1KaonNumber]
   Float_t         Top2mass;
   Float_t         Top2energy;
   Float_t         Top2gamma;
   Float_t         Top2btag;
   Float_t         Top2bmomentum;
   Float_t         Top2bdistance;
   Int_t           Top2bcharge;
   Float_t         Top2bcostheta;
   Int_t           Top2bTVCM;
   Int_t           Top2bntracks;
   Int_t           Top2leptonCharge;
   Float_t         Top2leptonE;
   Float_t         Top2leptonCos;
   Int_t           Top2leptonCorrect;
   Int_t           Top2Vtx;
   Int_t           Top2Kaon;
   Int_t           Top2KaonNumber;
   Int_t           Top2KaonCharges[6];   //[Top2KaonNumber]
   Float_t         Top2KaonMomentum[6];   //[Top2KaonNumber]
   Int_t           UsedBTVCM;
   Int_t           methodUsed;
   Int_t           methodRefused;
   Int_t           methodCorrect;
   Int_t           methodSameCharge[6];   //[methodRefused]
   Int_t           methodTaken[11];   //[methodUsed]
   Float_t         qBCostheta[2];
   Float_t         qCostheta[2];
   Float_t         chiHad;
   Float_t         chiTopMass;
   Float_t         chiTopE;
   Float_t         chiPbstar;
   Float_t         chiCosWb;
   Float_t         chiGammaT;
   Float_t         gammaT;
   Float_t         chiTop2Mass;
   Float_t         chiTop2E;
   Float_t         chiGammaT2;
   Float_t         Thrust;

   // List of branches
   TBranch        *b_mctag;   //!
   TBranch        *b_MCTopmass;   //!
   TBranch        *b_MCquarkAngle;   //!
   TBranch        *b_MCTopmomentum;   //!
   TBranch        *b_MCTopcostheta;   //!
   TBranch        *b_MCTopBarmass;   //!
   TBranch        *b_MCTopBarmomentum;   //!
   TBranch        *b_MCTopBarcostheta;   //!
   TBranch        *b_MCTopBangle;   //!
   TBranch        *b_MCTopcosWb;   //!
   TBranch        *b_MCNeutrinoEnergy;   //!
   TBranch        *b_MCLeptonPDG;   //!
   TBranch        *b_MCLeptonMomentum;   //!
   TBranch        *b_MCLeptonCostheta;   //!
   TBranch        *b_MCBOscillation;   //!
   TBranch        *b_MCBBarOscillation;   //!
   TBranch        *b_MCBWcorrect;   //!
   TBranch        *b_qMCBcostheta;   //!
   TBranch        *b_qMCcostheta;   //!
   TBranch        *b_totalEnergy;   //!
   TBranch        *b_bProduct;   //!
   TBranch        *b_hadMass;   //!
   TBranch        *b_missedEnergy;   //!
   TBranch        *b_W1mass;   //!
   TBranch        *b_W1gamma;   //!
   TBranch        *b_W1momentum;   //!
   TBranch        *b_W1costheta;   //!
   TBranch        *b_W2mass;   //!
   TBranch        *b_W2momentum;   //!
   TBranch        *b_W2costheta;   //!
   TBranch        *b_Top1mass;   //!
   TBranch        *b_Top1gamma;   //!
   TBranch        *b_Top1btag;   //!
   TBranch        *b_Top1energy;   //!
   TBranch        *b_Top1bcharge;   //!
   TBranch        *b_Top1bmomentum;   //!
   TBranch        *b_Top1bdistance;   //!
   TBranch        *b_Top1costheta;   //!
   TBranch        *b_Top1bcostheta;   //!
   TBranch        *b_Top1truthAngle;   //!
   TBranch        *b_Top1bntracks;   //!
   TBranch        *b_Top1bTVCM;   //!
   TBranch        *b_Top1cosWb;   //!
   TBranch        *b_Top1pstarb;   //!
   TBranch        *b_Top1Vtx;   //!
   TBranch        *b_Top1Kaon;   //!
   TBranch        *b_Top1KaonNumber;   //!
   TBranch        *b_Top1KaonCharges;   //!
   TBranch        *b_Top1KaonMomentum;   //!
   TBranch        *b_Top2mass;   //!
   TBranch        *b_Top2energy;   //!
   TBranch        *b_Top2gamma;   //!
   TBranch        *b_Top2btag;   //!
   TBranch        *b_Top2bmomentum;   //!
   TBranch        *b_Top2bdistance;   //!
   TBranch        *b_Top2bcharge;   //!
   TBranch        *b_Top2bcostheta;   //!
   TBranch        *b_Top2bTVCM;   //!
   TBranch        *b_Top2bntracks;   //!
   TBranch        *b_Top2leptonCharge;   //!
   TBranch        *b_Top2leptonE;   //!
   TBranch        *b_Top2leptonCos;   //!
   TBranch        *b_Top2leptonCorrect;   //!
   TBranch        *b_Top2Vtx;   //!
   TBranch        *b_Top2Kaon;   //!
   TBranch        *b_Top2KaonNumber;   //!
   TBranch        *b_Top2KaonCharges;   //!
   TBranch        *b_Top2KaonMomentum;   //!
   TBranch        *b_UsedBTVCM;   //!
   TBranch        *b_methodUsed;   //!
   TBranch        *b_methodRefused;   //!
   TBranch        *b_methodCorrect;   //!
   TBranch        *b_methodSameCharge;   //!
   TBranch        *b_methodTaken;   //!
   TBranch        *b_qBCostheta;   //!
   TBranch        *b_qCostheta;   //!
   TBranch        *b_chiHad;   //!
   TBranch        *b_chiTopMass;   //!
   TBranch        *b_chiTopE;   //!
   TBranch        *b_chiPbstar;   //!
   TBranch        *b_chiCosWb;   //!
   TBranch        *b_chiGammaT;   //!
   TBranch        *b_gammaT;   //!
   TBranch        *b_chiTop2Mass;   //!
   TBranch        *b_chiTop2E;   //!
   TBranch        *b_chiGammaT2;   //!
   TBranch        *b_Thrust;   //!

   myclass(TTree *tree=0);
   virtual ~myclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef myclass_cxx
myclass::myclass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/users/ilc/okugawa/macros/leptonic_yyxylv_eLeR_iso_lep_lcut_090418.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/users/ilc/okugawa/macros/leptonic_yyxylv_eLeR_iso_lep_lcut_090418.root");
      }
      f->GetObject("Stats",tree);

   }
   Init(tree);
}

myclass::~myclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t myclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t myclass::LoadTree(Long64_t entry)
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

void myclass::Init(TTree *tree)
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

   fChain->SetBranchAddress("mctag", &mctag, &b_mctag);
   fChain->SetBranchAddress("MCTopmass", &MCTopmass, &b_MCTopmass);
   fChain->SetBranchAddress("MCquarkAngle", &MCquarkAngle, &b_MCquarkAngle);
   fChain->SetBranchAddress("MCTopmomentum", &MCTopmomentum, &b_MCTopmomentum);
   fChain->SetBranchAddress("MCTopcostheta", &MCTopcostheta, &b_MCTopcostheta);
   fChain->SetBranchAddress("MCTopBarmass", &MCTopBarmass, &b_MCTopBarmass);
   fChain->SetBranchAddress("MCTopBarmomentum", &MCTopBarmomentum, &b_MCTopBarmomentum);
   fChain->SetBranchAddress("MCTopBarcostheta", &MCTopBarcostheta, &b_MCTopBarcostheta);
   fChain->SetBranchAddress("MCTopBangle", &MCTopBangle, &b_MCTopBangle);
   fChain->SetBranchAddress("MCTopcosWb", &MCTopcosWb, &b_MCTopcosWb);
   fChain->SetBranchAddress("MCNeutrinoEnergy", &MCNeutrinoEnergy, &b_MCNeutrinoEnergy);
   fChain->SetBranchAddress("MCLeptonPDG", &MCLeptonPDG, &b_MCLeptonPDG);
   fChain->SetBranchAddress("MCLeptonMomentum", &MCLeptonMomentum, &b_MCLeptonMomentum);
   fChain->SetBranchAddress("MCLeptonCostheta", &MCLeptonCostheta, &b_MCLeptonCostheta);
   fChain->SetBranchAddress("MCBOscillation", &MCBOscillation, &b_MCBOscillation);
   fChain->SetBranchAddress("MCBBarOscillation", &MCBBarOscillation, &b_MCBBarOscillation);
   fChain->SetBranchAddress("MCBWcorrect", &MCBWcorrect, &b_MCBWcorrect);
   fChain->SetBranchAddress("qMCBcostheta", qMCBcostheta, &b_qMCBcostheta);
   fChain->SetBranchAddress("qMCcostheta", qMCcostheta, &b_qMCcostheta);
   fChain->SetBranchAddress("totalEnergy", &totalEnergy, &b_totalEnergy);
   fChain->SetBranchAddress("bProduct", &bProduct, &b_bProduct);
   fChain->SetBranchAddress("hadMass", &hadMass, &b_hadMass);
   fChain->SetBranchAddress("missedEnergy", &missedEnergy, &b_missedEnergy);
   fChain->SetBranchAddress("W1mass", &W1mass, &b_W1mass);
   fChain->SetBranchAddress("W1gamma", &W1gamma, &b_W1gamma);
   fChain->SetBranchAddress("W1momentum", &W1momentum, &b_W1momentum);
   fChain->SetBranchAddress("W1costheta", &W1costheta, &b_W1costheta);
   fChain->SetBranchAddress("W2mass", &W2mass, &b_W2mass);
   fChain->SetBranchAddress("W2momentum", &W2momentum, &b_W2momentum);
   fChain->SetBranchAddress("W2costheta", &W2costheta, &b_W2costheta);
   fChain->SetBranchAddress("Top1mass", &Top1mass, &b_Top1mass);
   fChain->SetBranchAddress("Top1gamma", &Top1gamma, &b_Top1gamma);
   fChain->SetBranchAddress("Top1btag", &Top1btag, &b_Top1btag);
   fChain->SetBranchAddress("Top1energy", &Top1energy, &b_Top1energy);
   fChain->SetBranchAddress("Top1bcharge", &Top1bcharge, &b_Top1bcharge);
   fChain->SetBranchAddress("Top1bmomentum", &Top1bmomentum, &b_Top1bmomentum);
   fChain->SetBranchAddress("Top1bdistance", &Top1bdistance, &b_Top1bdistance);
   fChain->SetBranchAddress("Top1costheta", &Top1costheta, &b_Top1costheta);
   fChain->SetBranchAddress("Top1bcostheta", &Top1bcostheta, &b_Top1bcostheta);
   fChain->SetBranchAddress("Top1truthAngle", &Top1truthAngle, &b_Top1truthAngle);
   fChain->SetBranchAddress("Top1bntracks", &Top1bntracks, &b_Top1bntracks);
   fChain->SetBranchAddress("Top1bTVCM", &Top1bTVCM, &b_Top1bTVCM);
   fChain->SetBranchAddress("Top1cosWb", &Top1cosWb, &b_Top1cosWb);
   fChain->SetBranchAddress("Top1pstarb", &Top1pstarb, &b_Top1pstarb);
   fChain->SetBranchAddress("Top1Vtx", &Top1Vtx, &b_Top1Vtx);
   fChain->SetBranchAddress("Top1Kaon", &Top1Kaon, &b_Top1Kaon);
   fChain->SetBranchAddress("Top1KaonNumber", &Top1KaonNumber, &b_Top1KaonNumber);
   fChain->SetBranchAddress("Top1KaonCharges", Top1KaonCharges, &b_Top1KaonCharges);
   fChain->SetBranchAddress("Top1KaonMomentum", Top1KaonMomentum, &b_Top1KaonMomentum);
   fChain->SetBranchAddress("Top2mass", &Top2mass, &b_Top2mass);
   fChain->SetBranchAddress("Top2energy", &Top2energy, &b_Top2energy);
   fChain->SetBranchAddress("Top2gamma", &Top2gamma, &b_Top2gamma);
   fChain->SetBranchAddress("Top2btag", &Top2btag, &b_Top2btag);
   fChain->SetBranchAddress("Top2bmomentum", &Top2bmomentum, &b_Top2bmomentum);
   fChain->SetBranchAddress("Top2bdistance", &Top2bdistance, &b_Top2bdistance);
   fChain->SetBranchAddress("Top2bcharge", &Top2bcharge, &b_Top2bcharge);
   fChain->SetBranchAddress("Top2bcostheta", &Top2bcostheta, &b_Top2bcostheta);
   fChain->SetBranchAddress("Top2bTVCM", &Top2bTVCM, &b_Top2bTVCM);
   fChain->SetBranchAddress("Top2bntracks", &Top2bntracks, &b_Top2bntracks);
   fChain->SetBranchAddress("Top2leptonCharge", &Top2leptonCharge, &b_Top2leptonCharge);
   fChain->SetBranchAddress("Top2leptonE", &Top2leptonE, &b_Top2leptonE);
   fChain->SetBranchAddress("Top2leptonCos", &Top2leptonCos, &b_Top2leptonCos);
   fChain->SetBranchAddress("Top2leptonCorrect", &Top2leptonCorrect, &b_Top2leptonCorrect);
   fChain->SetBranchAddress("Top2Vtx", &Top2Vtx, &b_Top2Vtx);
   fChain->SetBranchAddress("Top2Kaon", &Top2Kaon, &b_Top2Kaon);
   fChain->SetBranchAddress("Top2KaonNumber", &Top2KaonNumber, &b_Top2KaonNumber);
   fChain->SetBranchAddress("Top2KaonCharges", Top2KaonCharges, &b_Top2KaonCharges);
   fChain->SetBranchAddress("Top2KaonMomentum", Top2KaonMomentum, &b_Top2KaonMomentum);
   fChain->SetBranchAddress("UsedBTVCM", &UsedBTVCM, &b_UsedBTVCM);
   fChain->SetBranchAddress("methodUsed", &methodUsed, &b_methodUsed);
   fChain->SetBranchAddress("methodRefused", &methodRefused, &b_methodRefused);
   fChain->SetBranchAddress("methodCorrect", &methodCorrect, &b_methodCorrect);
   fChain->SetBranchAddress("methodSameCharge", methodSameCharge, &b_methodSameCharge);
   fChain->SetBranchAddress("methodTaken", methodTaken, &b_methodTaken);
   fChain->SetBranchAddress("qBCostheta", qBCostheta, &b_qBCostheta);
   fChain->SetBranchAddress("qCostheta", qCostheta, &b_qCostheta);
   fChain->SetBranchAddress("chiHad", &chiHad, &b_chiHad);
   fChain->SetBranchAddress("chiTopMass", &chiTopMass, &b_chiTopMass);
   fChain->SetBranchAddress("chiTopE", &chiTopE, &b_chiTopE);
   fChain->SetBranchAddress("chiPbstar", &chiPbstar, &b_chiPbstar);
   fChain->SetBranchAddress("chiCosWb", &chiCosWb, &b_chiCosWb);
   fChain->SetBranchAddress("chiGammaT", &chiGammaT, &b_chiGammaT);
   fChain->SetBranchAddress("gammaT", &gammaT, &b_gammaT);
   fChain->SetBranchAddress("chiTop2Mass", &chiTop2Mass, &b_chiTop2Mass);
   fChain->SetBranchAddress("chiTop2E", &chiTop2E, &b_chiTop2E);
   fChain->SetBranchAddress("chiGammaT2", &chiGammaT2, &b_chiGammaT2);
   fChain->SetBranchAddress("Thrust", &Thrust, &b_Thrust);
   Notify();
}

Bool_t myclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void myclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t myclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   
   bool hadM = (hadMass > 180 && hadMass < 420)? true: false;
   bool rcTW = (Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50)? true: false;

   if(hadM && rcTW) return 1;
   
   return -1;

}
#endif // #ifdef myclass_cxx
