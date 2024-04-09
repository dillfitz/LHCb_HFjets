//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 14 20:07:40 2024 by ROOT version 6.24/08
// from TChain MCDecay/MCDecayTree/
//////////////////////////////////////////////////////////

#ifndef JpsiMCTree_h
#define JpsiMCTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class JpsiMCTree
{
public:
   TTree *fChain;  //! pointer to the analyzed TTree or TChain
   Int_t fCurrent; //! current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t J_psi_1S_TRUEP_E;
   Double_t J_psi_1S_TRUEP_X;
   Double_t J_psi_1S_TRUEP_Y;
   Double_t J_psi_1S_TRUEP_Z;
   Double_t J_psi_1S_TRUEPT;
   Double_t J_psi_1S_TRUEORIGINVERTEX_X;
   Double_t J_psi_1S_TRUEORIGINVERTEX_Y;
   Double_t J_psi_1S_TRUEORIGINVERTEX_Z;
   Double_t J_psi_1S_TRUEENDVERTEX_X;
   Double_t J_psi_1S_TRUEENDVERTEX_Y;
   Double_t J_psi_1S_TRUEENDVERTEX_Z;
   Bool_t J_psi_1S_TRUEISSTABLE;
   Double_t J_psi_1S_TRUETAU;
   Int_t J_psi_1S_Reconstructible;
   Int_t J_psi_1S_Reconstructed;
   Int_t J_psi_1S_ProtoParticles;
   Float_t J_psi_1S_PP_PX[20];       //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_PY[20];       //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_PZ[20];       //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_Weight[20];   //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_tr_pchi2[20]; //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_DLLe[20];     //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_DLLk[20];     //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_DLLp[20];     //[J_psi_1S_ProtoParticles]
   Float_t J_psi_1S_PP_DLLmu[20];    //[J_psi_1S_ProtoParticles]
   Double_t J_psi_1S0_TRUEP_E;
   Double_t J_psi_1S0_TRUEP_X;
   Double_t J_psi_1S0_TRUEP_Y;
   Double_t J_psi_1S0_TRUEP_Z;
   Double_t J_psi_1S0_TRUEPT;
   Double_t J_psi_1S0_TRUEORIGINVERTEX_X;
   Double_t J_psi_1S0_TRUEORIGINVERTEX_Y;
   Double_t J_psi_1S0_TRUEORIGINVERTEX_Z;
   Double_t J_psi_1S0_TRUEENDVERTEX_X;
   Double_t J_psi_1S0_TRUEENDVERTEX_Y;
   Double_t J_psi_1S0_TRUEENDVERTEX_Z;
   Bool_t J_psi_1S0_TRUEISSTABLE;
   Double_t J_psi_1S0_TRUETAU;
   Int_t J_psi_1S0_Reconstructible;
   Int_t J_psi_1S0_Reconstructed;
   Int_t J_psi_1S0_ProtoParticles;
   Float_t J_psi_1S0_PP_PX[20];       //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_PY[20];       //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_PZ[20];       //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_Weight[20];   //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_tr_pchi2[20]; //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_DLLe[20];     //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_DLLk[20];     //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_DLLp[20];     //[J_psi_1S0_ProtoParticles]
   Float_t J_psi_1S0_PP_DLLmu[20];    //[J_psi_1S0_ProtoParticles]
   Double_t muplus_TRUEP_E;
   Double_t muplus_TRUEP_X;
   Double_t muplus_TRUEP_Y;
   Double_t muplus_TRUEP_Z;
   Double_t muplus_TRUEPT;
   Double_t muplus_TRUEORIGINVERTEX_X;
   Double_t muplus_TRUEORIGINVERTEX_Y;
   Double_t muplus_TRUEORIGINVERTEX_Z;
   Double_t muplus_TRUEENDVERTEX_X;
   Double_t muplus_TRUEENDVERTEX_Y;
   Double_t muplus_TRUEENDVERTEX_Z;
   Bool_t muplus_TRUEISSTABLE;
   Double_t muplus_TRUETAU;
   Int_t muplus_Reconstructible;
   Int_t muplus_Reconstructed;
   Int_t muplus_ProtoParticles;
   Float_t muplus_PP_PX[20];       //[muplus_ProtoParticles]
   Float_t muplus_PP_PY[20];       //[muplus_ProtoParticles]
   Float_t muplus_PP_PZ[20];       //[muplus_ProtoParticles]
   Float_t muplus_PP_Weight[20];   //[muplus_ProtoParticles]
   Float_t muplus_PP_tr_pchi2[20]; //[muplus_ProtoParticles]
   Float_t muplus_PP_DLLe[20];     //[muplus_ProtoParticles]
   Float_t muplus_PP_DLLk[20];     //[muplus_ProtoParticles]
   Float_t muplus_PP_DLLp[20];     //[muplus_ProtoParticles]
   Float_t muplus_PP_DLLmu[20];    //[muplus_ProtoParticles]
   Double_t muminus_TRUEP_E;
   Double_t muminus_TRUEP_X;
   Double_t muminus_TRUEP_Y;
   Double_t muminus_TRUEP_Z;
   Double_t muminus_TRUEPT;
   Double_t muminus_TRUEORIGINVERTEX_X;
   Double_t muminus_TRUEORIGINVERTEX_Y;
   Double_t muminus_TRUEORIGINVERTEX_Z;
   Double_t muminus_TRUEENDVERTEX_X;
   Double_t muminus_TRUEENDVERTEX_Y;
   Double_t muminus_TRUEENDVERTEX_Z;
   Bool_t muminus_TRUEISSTABLE;
   Double_t muminus_TRUETAU;
   Int_t muminus_Reconstructible;
   Int_t muminus_Reconstructed;
   Int_t muminus_ProtoParticles;
   Float_t muminus_PP_PX[20];       //[muminus_ProtoParticles]
   Float_t muminus_PP_PY[20];       //[muminus_ProtoParticles]
   Float_t muminus_PP_PZ[20];       //[muminus_ProtoParticles]
   Float_t muminus_PP_Weight[20];   //[muminus_ProtoParticles]
   Float_t muminus_PP_tr_pchi2[20]; //[muminus_ProtoParticles]
   Float_t muminus_PP_DLLe[20];     //[muminus_ProtoParticles]
   Float_t muminus_PP_DLLk[20];     //[muminus_ProtoParticles]
   Float_t muminus_PP_DLLp[20];     //[muminus_ProtoParticles]
   Float_t muminus_PP_DLLmu[20];    //[muminus_ProtoParticles]
   UInt_t nCandidate;
   ULong64_t totCandidates;
   ULong64_t EventInSequence;
   Int_t nPVs;
   Int_t nTracks;
   Int_t nLongTracks;
   Int_t nDownstreamTracks;
   Int_t nUpstreamTracks;
   Int_t nVeloTracks;
   Int_t nTTracks;
   Int_t nBackTracks;
   Int_t nRich1Hits;
   Int_t nRich2Hits;
   Int_t nVeloClusters;
   Int_t nITClusters;
   Int_t nTTClusters;
   Int_t nOTClusters;
   Int_t nSPDHits;
   Int_t nMuonCoordsS0;
   Int_t nMuonCoordsS1;
   Int_t nMuonCoordsS2;
   Int_t nMuonCoordsS3;
   Int_t nMuonCoordsS4;
   Int_t nMuonTracks;

   // List of branches
   TBranch *b_J_psi_1S_TRUEP_E;             //!
   TBranch *b_J_psi_1S_TRUEP_X;             //!
   TBranch *b_J_psi_1S_TRUEP_Y;             //!
   TBranch *b_J_psi_1S_TRUEP_Z;             //!
   TBranch *b_J_psi_1S_TRUEPT;              //!
   TBranch *b_J_psi_1S_TRUEORIGINVERTEX_X;  //!
   TBranch *b_J_psi_1S_TRUEORIGINVERTEX_Y;  //!
   TBranch *b_J_psi_1S_TRUEORIGINVERTEX_Z;  //!
   TBranch *b_J_psi_1S_TRUEENDVERTEX_X;     //!
   TBranch *b_J_psi_1S_TRUEENDVERTEX_Y;     //!
   TBranch *b_J_psi_1S_TRUEENDVERTEX_Z;     //!
   TBranch *b_J_psi_1S_TRUEISSTABLE;        //!
   TBranch *b_J_psi_1S_TRUETAU;             //!
   TBranch *b_J_psi_1S_Reconstructible;     //!
   TBranch *b_J_psi_1S_Reconstructed;       //!
   TBranch *b_J_psi_1S_ProtoParticles;      //!
   TBranch *b_J_psi_1S_PP_PX;               //!
   TBranch *b_J_psi_1S_PP_PY;               //!
   TBranch *b_J_psi_1S_PP_PZ;               //!
   TBranch *b_J_psi_1S_PP_Weight;           //!
   TBranch *b_J_psi_1S_PP_tr_pchi2;         //!
   TBranch *b_J_psi_1S_PP_DLLe;             //!
   TBranch *b_J_psi_1S_PP_DLLk;             //!
   TBranch *b_J_psi_1S_PP_DLLp;             //!
   TBranch *b_J_psi_1S_PP_DLLmu;            //!
   TBranch *b_J_psi_1S0_TRUEP_E;            //!
   TBranch *b_J_psi_1S0_TRUEP_X;            //!
   TBranch *b_J_psi_1S0_TRUEP_Y;            //!
   TBranch *b_J_psi_1S0_TRUEP_Z;            //!
   TBranch *b_J_psi_1S0_TRUEPT;             //!
   TBranch *b_J_psi_1S0_TRUEORIGINVERTEX_X; //!
   TBranch *b_J_psi_1S0_TRUEORIGINVERTEX_Y; //!
   TBranch *b_J_psi_1S0_TRUEORIGINVERTEX_Z; //!
   TBranch *b_J_psi_1S0_TRUEENDVERTEX_X;    //!
   TBranch *b_J_psi_1S0_TRUEENDVERTEX_Y;    //!
   TBranch *b_J_psi_1S0_TRUEENDVERTEX_Z;    //!
   TBranch *b_J_psi_1S0_TRUEISSTABLE;       //!
   TBranch *b_J_psi_1S0_TRUETAU;            //!
   TBranch *b_J_psi_1S0_Reconstructible;    //!
   TBranch *b_J_psi_1S0_Reconstructed;      //!
   TBranch *b_J_psi_1S0_ProtoParticles;     //!
   TBranch *b_J_psi_1S0_PP_PX;              //!
   TBranch *b_J_psi_1S0_PP_PY;              //!
   TBranch *b_J_psi_1S0_PP_PZ;              //!
   TBranch *b_J_psi_1S0_PP_Weight;          //!
   TBranch *b_J_psi_1S0_PP_tr_pchi2;        //!
   TBranch *b_J_psi_1S0_PP_DLLe;            //!
   TBranch *b_J_psi_1S0_PP_DLLk;            //!
   TBranch *b_J_psi_1S0_PP_DLLp;            //!
   TBranch *b_J_psi_1S0_PP_DLLmu;           //!
   TBranch *b_muplus_TRUEP_E;               //!
   TBranch *b_muplus_TRUEP_X;               //!
   TBranch *b_muplus_TRUEP_Y;               //!
   TBranch *b_muplus_TRUEP_Z;               //!
   TBranch *b_muplus_TRUEPT;                //!
   TBranch *b_muplus_TRUEORIGINVERTEX_X;    //!
   TBranch *b_muplus_TRUEORIGINVERTEX_Y;    //!
   TBranch *b_muplus_TRUEORIGINVERTEX_Z;    //!
   TBranch *b_muplus_TRUEENDVERTEX_X;       //!
   TBranch *b_muplus_TRUEENDVERTEX_Y;       //!
   TBranch *b_muplus_TRUEENDVERTEX_Z;       //!
   TBranch *b_muplus_TRUEISSTABLE;          //!
   TBranch *b_muplus_TRUETAU;               //!
   TBranch *b_muplus_Reconstructible;       //!
   TBranch *b_muplus_Reconstructed;         //!
   TBranch *b_muplus_ProtoParticles;        //!
   TBranch *b_muplus_PP_PX;                 //!
   TBranch *b_muplus_PP_PY;                 //!
   TBranch *b_muplus_PP_PZ;                 //!
   TBranch *b_muplus_PP_Weight;             //!
   TBranch *b_muplus_PP_tr_pchi2;           //!
   TBranch *b_muplus_PP_DLLe;               //!
   TBranch *b_muplus_PP_DLLk;               //!
   TBranch *b_muplus_PP_DLLp;               //!
   TBranch *b_muplus_PP_DLLmu;              //!
   TBranch *b_muminus_TRUEP_E;              //!
   TBranch *b_muminus_TRUEP_X;              //!
   TBranch *b_muminus_TRUEP_Y;              //!
   TBranch *b_muminus_TRUEP_Z;              //!
   TBranch *b_muminus_TRUEPT;               //!
   TBranch *b_muminus_TRUEORIGINVERTEX_X;   //!
   TBranch *b_muminus_TRUEORIGINVERTEX_Y;   //!
   TBranch *b_muminus_TRUEORIGINVERTEX_Z;   //!
   TBranch *b_muminus_TRUEENDVERTEX_X;      //!
   TBranch *b_muminus_TRUEENDVERTEX_Y;      //!
   TBranch *b_muminus_TRUEENDVERTEX_Z;      //!
   TBranch *b_muminus_TRUEISSTABLE;         //!
   TBranch *b_muminus_TRUETAU;              //!
   TBranch *b_muminus_Reconstructible;      //!
   TBranch *b_muminus_Reconstructed;        //!
   TBranch *b_muminus_ProtoParticles;       //!
   TBranch *b_muminus_PP_PX;                //!
   TBranch *b_muminus_PP_PY;                //!
   TBranch *b_muminus_PP_PZ;                //!
   TBranch *b_muminus_PP_Weight;            //!
   TBranch *b_muminus_PP_tr_pchi2;          //!
   TBranch *b_muminus_PP_DLLe;              //!
   TBranch *b_muminus_PP_DLLk;              //!
   TBranch *b_muminus_PP_DLLp;              //!
   TBranch *b_muminus_PP_DLLmu;             //!
   TBranch *b_nCandidate;                   //!
   TBranch *b_totCandidates;                //!
   TBranch *b_EventInSequence;              //!
   TBranch *b_nPVs;                         //!
   TBranch *b_nTracks;                      //!
   TBranch *b_nLongTracks;                  //!
   TBranch *b_nDownstreamTracks;            //!
   TBranch *b_nUpstreamTracks;              //!
   TBranch *b_nVeloTracks;                  //!
   TBranch *b_nTTracks;                     //!
   TBranch *b_nBackTracks;                  //!
   TBranch *b_nRich1Hits;                   //!
   TBranch *b_nRich2Hits;                   //!
   TBranch *b_nVeloClusters;                //!
   TBranch *b_nITClusters;                  //!
   TBranch *b_nTTClusters;                  //!
   TBranch *b_nOTClusters;                  //!
   TBranch *b_nSPDHits;                     //!
   TBranch *b_nMuonCoordsS0;                //!
   TBranch *b_nMuonCoordsS1;                //!
   TBranch *b_nMuonCoordsS2;                //!
   TBranch *b_nMuonCoordsS3;                //!
   TBranch *b_nMuonCoordsS4;                //!
   TBranch *b_nMuonTracks;                  //!

   JpsiMCTree(TTree *tree = 0, int dataset = 93539, bool isData = false);
   virtual ~JpsiMCTree();
   virtual Int_t Cut(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void Init(TTree *tree);
   virtual void Loop();
   virtual Bool_t Notify();
   virtual void Show(Long64_t entry = -1);
};

#endif

#ifdef JpsiMCTree_cxx
JpsiMCTree::JpsiMCTree(TTree *tree = 0, int dataset = 93539, bool isData = false) : fChain(0)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0)
   {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile *)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen())
      {
         f = new TFile("Memory Directory");
      }
      f->GetObject("MCDecay/MCDecayTree", tree);

#else  // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain *chain = new TChain("MCDecay/MCDecayTree", "");
      TString data_dir = "/Users/josearias18/Desktop/QCDc2/pythia/Data/";

      if (dataset == 61599)
      {
         if (isData)
         {
         }
         else
         {

            chain->Add(data_dir + "Jpsi2MuMu_MC_2016_Sim09k_MD_02142024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 61590)
      {
         if (isData)
         {
         }
         else
         {
            // data_dir = "/afs/cern.ch/work/i/ichahrou/DeadCone/DaVinci/Run2_BuJpsiK/";
            chain->Add(data_dir + "Jpsi2MuMu_MC_2016_Sim09k_MD_02142024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 61591)
      {
         if (isData)
         {
         }
         else
         {
            // data_dir = "/afs/cern.ch/work/i/ichahrou/DeadCone/DaVinci/Run2_BuJpsiK/";
            // chain->Add(data_dir + "truth_BuPsiK_in_jet_13TeV_nojetid.root/MCDecay/MCDecayTree");

            chain->Add(data_dir + "Jpsi2MuMu_MC_2016_Sim09k_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2016_Sim09l_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2016_Sim10a_MU_02122024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 71599)
      {
         if (isData)
         {
         }
         else
         {

            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09k_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09k_MU_02122024_full.root/MCDecay/MCDecayTree");

            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09l_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09l_MU_02122024_full.root/MCDecay/MCDecayTree");

            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim10a_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim10a_MU_02122024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 71590)
      {
         if (isData)
         {
         }
         else
         {
            // data_dir = "/afs/cern.ch/work/i/ichahrou/DeadCone/DaVinci/Run2_BuJpsiK/";
            // chain->Add(data_dir + "truth_BuPsiK_in_jet_13TeV_nojetid.root/MCDecay/MCDecayTree");

            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09k_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09l_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim10a_MD_02122024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 71591)
      {
         if (isData)
         {
         }
         else
         {
            // data_dir = "/afs/cern.ch/work/i/ichahrou/DeadCone/DaVinci/Run2_BuJpsiK/";
            // chain->Add(data_dir + "truth_BuPsiK_in_jet_13TeV_nojetid.root/MCDecay/MCDecayTree");

            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09k_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim09l_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2017_Sim10a_MU_02122024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 81599)
      {
         if (isData)
         {
         }
         else
         {
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09k_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09k_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09l_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09l_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim10a_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim10a_MU_02122024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 81590)
      {
         if (isData)
         {
         }
         else
         {
            // data_dir = "/afs/cern.ch/work/i/ichahrou/DeadCone/DaVinci/Run2_BuJpsiK/";
            // chain->Add(data_dir + "truth_BuPsiK_in_jet_13TeV_nojetid.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09k_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09l_MD_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim10a_MD_02122024_full.root/MCDecay/MCDecayTree");
         }
      }
      else if (dataset == 81591)
      {
         if (isData)
         {
         }
         else
         {
            // data_dir = "/afs/cern.ch/work/i/ichahrou/DeadCone/DaVinci/Run2_BuJpsiK/";
            // chain->Add(data_dir + "truth_BuPsiK_in_jet_13TeV_nojetid.root/MCDecay/MCDecayTree");

            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09k_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim09l_MU_02122024_full.root/MCDecay/MCDecayTree");
            chain->Add(data_dir + "Jpsi2MuMu_MC_2018_Sim10a_MU_02122024_full.root/MCDecay/MCDecayTree");
         }
      }

      tree = chain;
#endif // SINGLE_TREE
   }
   Init(tree);
}

JpsiMCTree::~JpsiMCTree()
{
   if (!fChain)
      return;
   delete fChain->GetCurrentFile();
}

Int_t JpsiMCTree::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain)
      return 0;
   return fChain->GetEntry(entry);
}
Long64_t JpsiMCTree::LoadTree(Long64_t entry)
{
   // Set the environment to read one entry
   if (!fChain)
      return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0)
      return centry;
   if (fChain->GetTreeNumber() != fCurrent)
   {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void JpsiMCTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree)
      return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("J_psi_1S_TRUEP_E", &J_psi_1S_TRUEP_E, &b_J_psi_1S_TRUEP_E);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_X", &J_psi_1S_TRUEP_X, &b_J_psi_1S_TRUEP_X);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_Y", &J_psi_1S_TRUEP_Y, &b_J_psi_1S_TRUEP_Y);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_Z", &J_psi_1S_TRUEP_Z, &b_J_psi_1S_TRUEP_Z);
   fChain->SetBranchAddress("J_psi_1S_TRUEPT", &J_psi_1S_TRUEPT, &b_J_psi_1S_TRUEPT);
   fChain->SetBranchAddress("J_psi_1S_TRUEORIGINVERTEX_X", &J_psi_1S_TRUEORIGINVERTEX_X, &b_J_psi_1S_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("J_psi_1S_TRUEORIGINVERTEX_Y", &J_psi_1S_TRUEORIGINVERTEX_Y, &b_J_psi_1S_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("J_psi_1S_TRUEORIGINVERTEX_Z", &J_psi_1S_TRUEORIGINVERTEX_Z, &b_J_psi_1S_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("J_psi_1S_TRUEENDVERTEX_X", &J_psi_1S_TRUEENDVERTEX_X, &b_J_psi_1S_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("J_psi_1S_TRUEENDVERTEX_Y", &J_psi_1S_TRUEENDVERTEX_Y, &b_J_psi_1S_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("J_psi_1S_TRUEENDVERTEX_Z", &J_psi_1S_TRUEENDVERTEX_Z, &b_J_psi_1S_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("J_psi_1S_TRUEISSTABLE", &J_psi_1S_TRUEISSTABLE, &b_J_psi_1S_TRUEISSTABLE);
   fChain->SetBranchAddress("J_psi_1S_TRUETAU", &J_psi_1S_TRUETAU, &b_J_psi_1S_TRUETAU);
   fChain->SetBranchAddress("J_psi_1S_Reconstructible", &J_psi_1S_Reconstructible, &b_J_psi_1S_Reconstructible);
   fChain->SetBranchAddress("J_psi_1S_Reconstructed", &J_psi_1S_Reconstructed, &b_J_psi_1S_Reconstructed);
   fChain->SetBranchAddress("J_psi_1S_ProtoParticles", &J_psi_1S_ProtoParticles, &b_J_psi_1S_ProtoParticles);
   fChain->SetBranchAddress("J_psi_1S_PP_PX", J_psi_1S_PP_PX, &b_J_psi_1S_PP_PX);
   fChain->SetBranchAddress("J_psi_1S_PP_PY", J_psi_1S_PP_PY, &b_J_psi_1S_PP_PY);
   fChain->SetBranchAddress("J_psi_1S_PP_PZ", J_psi_1S_PP_PZ, &b_J_psi_1S_PP_PZ);
   fChain->SetBranchAddress("J_psi_1S_PP_Weight", J_psi_1S_PP_Weight, &b_J_psi_1S_PP_Weight);
   fChain->SetBranchAddress("J_psi_1S_PP_tr_pchi2", J_psi_1S_PP_tr_pchi2, &b_J_psi_1S_PP_tr_pchi2);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLe", J_psi_1S_PP_DLLe, &b_J_psi_1S_PP_DLLe);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLk", J_psi_1S_PP_DLLk, &b_J_psi_1S_PP_DLLk);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLp", J_psi_1S_PP_DLLp, &b_J_psi_1S_PP_DLLp);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLmu", J_psi_1S_PP_DLLmu, &b_J_psi_1S_PP_DLLmu);
   fChain->SetBranchAddress("J_psi_1S0_TRUEP_E", &J_psi_1S0_TRUEP_E, &b_J_psi_1S0_TRUEP_E);
   fChain->SetBranchAddress("J_psi_1S0_TRUEP_X", &J_psi_1S0_TRUEP_X, &b_J_psi_1S0_TRUEP_X);
   fChain->SetBranchAddress("J_psi_1S0_TRUEP_Y", &J_psi_1S0_TRUEP_Y, &b_J_psi_1S0_TRUEP_Y);
   fChain->SetBranchAddress("J_psi_1S0_TRUEP_Z", &J_psi_1S0_TRUEP_Z, &b_J_psi_1S0_TRUEP_Z);
   fChain->SetBranchAddress("J_psi_1S0_TRUEPT", &J_psi_1S0_TRUEPT, &b_J_psi_1S0_TRUEPT);
   fChain->SetBranchAddress("J_psi_1S0_TRUEORIGINVERTEX_X", &J_psi_1S0_TRUEORIGINVERTEX_X, &b_J_psi_1S0_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("J_psi_1S0_TRUEORIGINVERTEX_Y", &J_psi_1S0_TRUEORIGINVERTEX_Y, &b_J_psi_1S0_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("J_psi_1S0_TRUEORIGINVERTEX_Z", &J_psi_1S0_TRUEORIGINVERTEX_Z, &b_J_psi_1S0_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("J_psi_1S0_TRUEENDVERTEX_X", &J_psi_1S0_TRUEENDVERTEX_X, &b_J_psi_1S0_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("J_psi_1S0_TRUEENDVERTEX_Y", &J_psi_1S0_TRUEENDVERTEX_Y, &b_J_psi_1S0_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("J_psi_1S0_TRUEENDVERTEX_Z", &J_psi_1S0_TRUEENDVERTEX_Z, &b_J_psi_1S0_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("J_psi_1S0_TRUEISSTABLE", &J_psi_1S0_TRUEISSTABLE, &b_J_psi_1S0_TRUEISSTABLE);
   fChain->SetBranchAddress("J_psi_1S0_TRUETAU", &J_psi_1S0_TRUETAU, &b_J_psi_1S0_TRUETAU);
   fChain->SetBranchAddress("J_psi_1S0_Reconstructible", &J_psi_1S0_Reconstructible, &b_J_psi_1S0_Reconstructible);
   fChain->SetBranchAddress("J_psi_1S0_Reconstructed", &J_psi_1S0_Reconstructed, &b_J_psi_1S0_Reconstructed);
   fChain->SetBranchAddress("J_psi_1S0_ProtoParticles", &J_psi_1S0_ProtoParticles, &b_J_psi_1S0_ProtoParticles);
   fChain->SetBranchAddress("J_psi_1S0_PP_PX", J_psi_1S0_PP_PX, &b_J_psi_1S0_PP_PX);
   fChain->SetBranchAddress("J_psi_1S0_PP_PY", J_psi_1S0_PP_PY, &b_J_psi_1S0_PP_PY);
   fChain->SetBranchAddress("J_psi_1S0_PP_PZ", J_psi_1S0_PP_PZ, &b_J_psi_1S0_PP_PZ);
   fChain->SetBranchAddress("J_psi_1S0_PP_Weight", J_psi_1S0_PP_Weight, &b_J_psi_1S0_PP_Weight);
   fChain->SetBranchAddress("J_psi_1S0_PP_tr_pchi2", J_psi_1S0_PP_tr_pchi2, &b_J_psi_1S0_PP_tr_pchi2);
   fChain->SetBranchAddress("J_psi_1S0_PP_DLLe", J_psi_1S0_PP_DLLe, &b_J_psi_1S0_PP_DLLe);
   fChain->SetBranchAddress("J_psi_1S0_PP_DLLk", J_psi_1S0_PP_DLLk, &b_J_psi_1S0_PP_DLLk);
   fChain->SetBranchAddress("J_psi_1S0_PP_DLLp", J_psi_1S0_PP_DLLp, &b_J_psi_1S0_PP_DLLp);
   fChain->SetBranchAddress("J_psi_1S0_PP_DLLmu", J_psi_1S0_PP_DLLmu, &b_J_psi_1S0_PP_DLLmu);
   fChain->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E, &b_muplus_TRUEP_E);
   fChain->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X, &b_muplus_TRUEP_X);
   fChain->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y, &b_muplus_TRUEP_Y);
   fChain->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z, &b_muplus_TRUEP_Z);
   fChain->SetBranchAddress("muplus_TRUEPT", &muplus_TRUEPT, &b_muplus_TRUEPT);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_X", &muplus_TRUEORIGINVERTEX_X, &b_muplus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_Y", &muplus_TRUEORIGINVERTEX_Y, &b_muplus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_Z", &muplus_TRUEORIGINVERTEX_Z, &b_muplus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_X", &muplus_TRUEENDVERTEX_X, &b_muplus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_Y", &muplus_TRUEENDVERTEX_Y, &b_muplus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_Z", &muplus_TRUEENDVERTEX_Z, &b_muplus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("muplus_TRUEISSTABLE", &muplus_TRUEISSTABLE, &b_muplus_TRUEISSTABLE);
   fChain->SetBranchAddress("muplus_TRUETAU", &muplus_TRUETAU, &b_muplus_TRUETAU);
   fChain->SetBranchAddress("muplus_Reconstructible", &muplus_Reconstructible, &b_muplus_Reconstructible);
   fChain->SetBranchAddress("muplus_Reconstructed", &muplus_Reconstructed, &b_muplus_Reconstructed);
   fChain->SetBranchAddress("muplus_ProtoParticles", &muplus_ProtoParticles, &b_muplus_ProtoParticles);
   fChain->SetBranchAddress("muplus_PP_PX", muplus_PP_PX, &b_muplus_PP_PX);
   fChain->SetBranchAddress("muplus_PP_PY", muplus_PP_PY, &b_muplus_PP_PY);
   fChain->SetBranchAddress("muplus_PP_PZ", muplus_PP_PZ, &b_muplus_PP_PZ);
   fChain->SetBranchAddress("muplus_PP_Weight", muplus_PP_Weight, &b_muplus_PP_Weight);
   fChain->SetBranchAddress("muplus_PP_tr_pchi2", muplus_PP_tr_pchi2, &b_muplus_PP_tr_pchi2);
   fChain->SetBranchAddress("muplus_PP_DLLe", muplus_PP_DLLe, &b_muplus_PP_DLLe);
   fChain->SetBranchAddress("muplus_PP_DLLk", muplus_PP_DLLk, &b_muplus_PP_DLLk);
   fChain->SetBranchAddress("muplus_PP_DLLp", muplus_PP_DLLp, &b_muplus_PP_DLLp);
   fChain->SetBranchAddress("muplus_PP_DLLmu", muplus_PP_DLLmu, &b_muplus_PP_DLLmu);
   fChain->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E, &b_muminus_TRUEP_E);
   fChain->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X, &b_muminus_TRUEP_X);
   fChain->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y, &b_muminus_TRUEP_Y);
   fChain->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z, &b_muminus_TRUEP_Z);
   fChain->SetBranchAddress("muminus_TRUEPT", &muminus_TRUEPT, &b_muminus_TRUEPT);
   fChain->SetBranchAddress("muminus_TRUEORIGINVERTEX_X", &muminus_TRUEORIGINVERTEX_X, &b_muminus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("muminus_TRUEORIGINVERTEX_Y", &muminus_TRUEORIGINVERTEX_Y, &b_muminus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("muminus_TRUEORIGINVERTEX_Z", &muminus_TRUEORIGINVERTEX_Z, &b_muminus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("muminus_TRUEENDVERTEX_X", &muminus_TRUEENDVERTEX_X, &b_muminus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("muminus_TRUEENDVERTEX_Y", &muminus_TRUEENDVERTEX_Y, &b_muminus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("muminus_TRUEENDVERTEX_Z", &muminus_TRUEENDVERTEX_Z, &b_muminus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("muminus_TRUEISSTABLE", &muminus_TRUEISSTABLE, &b_muminus_TRUEISSTABLE);
   fChain->SetBranchAddress("muminus_TRUETAU", &muminus_TRUETAU, &b_muminus_TRUETAU);
   fChain->SetBranchAddress("muminus_Reconstructible", &muminus_Reconstructible, &b_muminus_Reconstructible);
   fChain->SetBranchAddress("muminus_Reconstructed", &muminus_Reconstructed, &b_muminus_Reconstructed);
   fChain->SetBranchAddress("muminus_ProtoParticles", &muminus_ProtoParticles, &b_muminus_ProtoParticles);
   fChain->SetBranchAddress("muminus_PP_PX", muminus_PP_PX, &b_muminus_PP_PX);
   fChain->SetBranchAddress("muminus_PP_PY", muminus_PP_PY, &b_muminus_PP_PY);
   fChain->SetBranchAddress("muminus_PP_PZ", muminus_PP_PZ, &b_muminus_PP_PZ);
   fChain->SetBranchAddress("muminus_PP_Weight", muminus_PP_Weight, &b_muminus_PP_Weight);
   fChain->SetBranchAddress("muminus_PP_tr_pchi2", muminus_PP_tr_pchi2, &b_muminus_PP_tr_pchi2);
   fChain->SetBranchAddress("muminus_PP_DLLe", muminus_PP_DLLe, &b_muminus_PP_DLLe);
   fChain->SetBranchAddress("muminus_PP_DLLk", muminus_PP_DLLk, &b_muminus_PP_DLLk);
   fChain->SetBranchAddress("muminus_PP_DLLp", muminus_PP_DLLp, &b_muminus_PP_DLLp);
   fChain->SetBranchAddress("muminus_PP_DLLmu", muminus_PP_DLLmu, &b_muminus_PP_DLLmu);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("nLongTracks", &nLongTracks, &b_nLongTracks);
   fChain->SetBranchAddress("nDownstreamTracks", &nDownstreamTracks, &b_nDownstreamTracks);
   fChain->SetBranchAddress("nUpstreamTracks", &nUpstreamTracks, &b_nUpstreamTracks);
   fChain->SetBranchAddress("nVeloTracks", &nVeloTracks, &b_nVeloTracks);
   fChain->SetBranchAddress("nTTracks", &nTTracks, &b_nTTracks);
   fChain->SetBranchAddress("nBackTracks", &nBackTracks, &b_nBackTracks);
   fChain->SetBranchAddress("nRich1Hits", &nRich1Hits, &b_nRich1Hits);
   fChain->SetBranchAddress("nRich2Hits", &nRich2Hits, &b_nRich2Hits);
   fChain->SetBranchAddress("nVeloClusters", &nVeloClusters, &b_nVeloClusters);
   fChain->SetBranchAddress("nITClusters", &nITClusters, &b_nITClusters);
   fChain->SetBranchAddress("nTTClusters", &nTTClusters, &b_nTTClusters);
   fChain->SetBranchAddress("nOTClusters", &nOTClusters, &b_nOTClusters);
   fChain->SetBranchAddress("nSPDHits", &nSPDHits, &b_nSPDHits);
   fChain->SetBranchAddress("nMuonCoordsS0", &nMuonCoordsS0, &b_nMuonCoordsS0);
   fChain->SetBranchAddress("nMuonCoordsS1", &nMuonCoordsS1, &b_nMuonCoordsS1);
   fChain->SetBranchAddress("nMuonCoordsS2", &nMuonCoordsS2, &b_nMuonCoordsS2);
   fChain->SetBranchAddress("nMuonCoordsS3", &nMuonCoordsS3, &b_nMuonCoordsS3);
   fChain->SetBranchAddress("nMuonCoordsS4", &nMuonCoordsS4, &b_nMuonCoordsS4);
   fChain->SetBranchAddress("nMuonTracks", &nMuonTracks, &b_nMuonTracks);
   Notify();
}

Bool_t JpsiMCTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void JpsiMCTree::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain)
      return;
   fChain->Show(entry);
}
Int_t JpsiMCTree::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}
#endif // #ifdef JpsiMCTree_cxx
