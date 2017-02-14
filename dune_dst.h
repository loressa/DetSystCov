//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec  9 11:46:32 2016 by ROOT version 5.34/34
// from TChain dune_dst/
//////////////////////////////////////////////////////////

#ifndef dune_dst_h
#define dune_dst_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <vector>

// Header file for the classes stored in the TTree if any.
//#include "./NtpMCEventRecord.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxtrueFSParticles = 100;
   const Int_t kMaxrecoFSParticles = 100;

class dune_dst {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   //genie::NtpMCEventRecord *genie_mc_truth;
 //ndtf::TaskForceAna *ana;
   Int_t           Run;
   Int_t           SubRun;
   Int_t           Event;
   Int_t           Detector;
   Float_t         Ev;
   Double_t        POTWeight;
   Int_t           sample;
   Int_t           reactionmode;
   Float_t         trueVtxX;
   Float_t         trueVtxY;
   Float_t         trueVtxZ;
   Float_t         trueDistToEdge;
   Float_t         y_true;
   Int_t           target;
   Int_t           NuPDG;
   Bool_t          NuInput;
   Int_t           trueFSParticles;
   Int_t           trueFSParticles_pdg[kMaxtrueFSParticles];   //[trueFSParticles_]
   Int_t           trueFSParticles_id[kMaxtrueFSParticles];   //[trueFSParticles_]
   Float_t         trueFSParticles_energy[kMaxtrueFSParticles];   //[trueFSParticles_]
   Int_t           trueFSParticles_numHits[kMaxtrueFSParticles];   //[trueFSParticles_]
   float   trueFSParticles_dEdx[kMaxtrueFSParticles];
   Float_t         trueFSParticles_momentum[kMaxtrueFSParticles][3];   //[trueFSParticles_]
   Int_t           NuPDG_reco;
   Int_t           sample_reco;
   Int_t           reaction_reco;
   Float_t         Ev_reco;
   Float_t         y_reco;
   Float_t         recoVtxX;
   Float_t         recoVtxY;
   Float_t         recoVtxZ;
   Float_t         sharedE_reco;
   Int_t           recoFSParticles;
   Int_t           recoFSParticles_pdg[kMaxrecoFSParticles];   //[recoFSParticles_]
   Int_t           recoFSParticles_id[kMaxrecoFSParticles];   //[recoFSParticles_]
   Float_t         recoFSParticles_energy[kMaxrecoFSParticles];   //[recoFSParticles_]
   Int_t           recoFSParticles_numHits[kMaxrecoFSParticles];   //[recoFSParticles_]
   float   recoFSParticles_dEdx[kMaxrecoFSParticles];
   Float_t         recoFSParticles_momentum[kMaxrecoFSParticles][3];   //[recoFSParticles_]

   // List of branches
   //TBranch        *b_genie_mc_truth;   //!
   TBranch        *b_ana_Run;   //!
   TBranch        *b_ana_SubRun;   //!
   TBranch        *b_ana_Event;   //!
   TBranch        *b_ana_Detector;   //!
   TBranch        *b_ana_Ev;   //!
   TBranch        *b_ana_POTWeight;   //!
   TBranch        *b_ana_sample;   //!
   TBranch        *b_ana_reactionmode;   //!
   TBranch        *b_ana_trueVtxX;   //!
   TBranch        *b_ana_trueVtxY;   //!
   TBranch        *b_ana_trueVtxZ;   //!
   TBranch        *b_ana_trueDistToEdge;   //!
   TBranch        *b_ana_y_true;   //!
   TBranch        *b_ana_target;   //!
   TBranch        *b_ana_NuPDG;   //!
   TBranch        *b_ana_NuInput;   //!
   TBranch        *b_ana_trueFSParticles_;   //!
   TBranch        *b_trueFSParticles_pdg;   //!
   TBranch        *b_trueFSParticles_id;   //!
   TBranch        *b_trueFSParticles_energy;   //!
   TBranch        *b_trueFSParticles_numHits;   //!
   TBranch        *b_trueFSParticles_dEdx;   //!
   TBranch        *b_trueFSParticles_momentum;   //!
   TBranch        *b_ana_NuPDG_reco;   //!
   TBranch        *b_ana_sample_reco;   //!
   TBranch        *b_ana_reaction_reco;   //!
   TBranch        *b_ana_Ev_reco;   //!
   TBranch        *b_ana_y_reco;   //!
   TBranch        *b_ana_recoVtxX;   //!
   TBranch        *b_ana_recoVtxY;   //!
   TBranch        *b_ana_recoVtxZ;   //!
   TBranch        *b_ana_sharedE_reco;   //!
   TBranch        *b_ana_recoFSParticles_;   //!
   TBranch        *b_recoFSParticles_pdg;   //!
   TBranch        *b_recoFSParticles_id;   //!
   TBranch        *b_recoFSParticles_energy;   //!
   TBranch        *b_recoFSParticles_numHits;   //!
   TBranch        *b_recoFSParticles_dEdx;   //!
   TBranch        *b_recoFSParticles_momentum;   //!

   dune_dst(TTree *tree=0);
   virtual ~dune_dst();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int mySeed = 0);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   //   virtual Int_t    Index(Float_t Ev_reco, Float_t y_reco, Int_t sample_reco);
};

#endif

#ifdef dune_dst_cxx
dune_dst::dune_dst(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("dune_dst",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("dune_dst","");

      chain->Add("fgt_events_nu.root");
      chain->Add("fgt_events_nubar.root");
      
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

dune_dst::~dune_dst()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dune_dst::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t dune_dst::LoadTree(Long64_t entry)
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

void dune_dst::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   //genie_mc_truth = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   //LORENA
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("trueFSParticles", 1);
   fChain->SetBranchStatus("trueFSParticles.pdg", 1);
   fChain->SetBranchStatus("trueFSParticles.id", 1);
   fChain->SetBranchStatus("trueFSParticles.energy", 1);
   fChain->SetBranchStatus("sample_reco",1);
   fChain->SetBranchStatus("reaction_reco", 1);
   fChain->SetBranchStatus("Ev_reco", 1);
   fChain->SetBranchStatus("y_reco", 1);
   fChain->SetBranchStatus("recoFSParticles", 1);
   fChain->SetBranchStatus("recoFSParticles.pdg", 1);
   fChain->SetBranchStatus("recoFSParticles.id", 1);
   fChain->SetBranchStatus("recoFSParticles.energy", 1);

   //fChain->SetBranchAddress("genie_mc_truth", &genie_mc_truth, &b_genie_mc_truth);
   //   fChain->SetBranchAddress("sample", &sample, &b_ana_sample);
   //fChain->SetBranchAddress("reactionmode", &reactionmode, &b_ana_reactionmode);
   //fChain->SetBranchAddress("y_true", &y_true, &b_ana_y_true);
   fChain->SetBranchAddress("trueFSParticles", &trueFSParticles, &b_ana_trueFSParticles_);
   fChain->SetBranchAddress("trueFSParticles.pdg", trueFSParticles_pdg, &b_trueFSParticles_pdg);
   fChain->SetBranchAddress("trueFSParticles.id", trueFSParticles_id, &b_trueFSParticles_id);
   fChain->SetBranchAddress("trueFSParticles.energy", trueFSParticles_energy, &b_trueFSParticles_energy);
   fChain->SetBranchAddress("sample_reco", &sample_reco, &b_ana_sample_reco);
   fChain->SetBranchAddress("reaction_reco", &reaction_reco, &b_ana_reaction_reco);
   fChain->SetBranchAddress("Ev_reco", &Ev_reco, &b_ana_Ev_reco);
   fChain->SetBranchAddress("y_reco", &y_reco, &b_ana_y_reco);
   fChain->SetBranchAddress("recoFSParticles", &recoFSParticles, &b_ana_recoFSParticles_);
   fChain->SetBranchAddress("recoFSParticles.pdg", recoFSParticles_pdg, &b_recoFSParticles_pdg);
   fChain->SetBranchAddress("recoFSParticles.id", recoFSParticles_id, &b_recoFSParticles_id);
   fChain->SetBranchAddress("recoFSParticles.energy", recoFSParticles_energy, &b_recoFSParticles_energy);
   Notify();
}

Bool_t dune_dst::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dune_dst::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dune_dst::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef dune_dst_cxx
