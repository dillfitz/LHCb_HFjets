//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun  8 15:34:13 2023 by ROOT version 6.24/08
// from TChain Jets/DecayTree/
//////////////////////////////////////////////////////////

#ifndef Bjet_BH_Variable_Tree_h
#define Bjet_BH_Variable_Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Bjet_BH_Variable_Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxmup_OWNPV_COV = 1;
   static constexpr Int_t kMaxmup_ORIVX_COV = 1;
   static constexpr Int_t kMaxmum_OWNPV_COV = 1;
   static constexpr Int_t kMaxmum_ORIVX_COV = 1;
   static constexpr Int_t kMaxK_OWNPV_COV = 1;
   static constexpr Int_t kMaxK_ORIVX_COV = 1;

   // Declaration of leaf types
   Double_t        system_P;
   Double_t        system_PT;
   Double_t        system_PE;
   Double_t        system_PX;
   Double_t        system_PY;
   Double_t        system_PZ;
   Double_t        system_MM;
   Double_t        system_MMERR;
   Double_t        system_M;
   Int_t           system_ID;
   Bool_t          system_L0Global_Dec;
   Bool_t          system_L0Global_TIS;
   Bool_t          system_L0Global_TOS;
   Bool_t          system_Hlt1Global_Dec;
   Bool_t          system_Hlt1Global_TIS;
   Bool_t          system_Hlt1Global_TOS;
   Bool_t          system_Hlt1Phys_Dec;
   Bool_t          system_Hlt1Phys_TIS;
   Bool_t          system_Hlt1Phys_TOS;
   Bool_t          system_Hlt2Global_Dec;
   Bool_t          system_Hlt2Global_TIS;
   Bool_t          system_Hlt2Global_TOS;
   Bool_t          system_Hlt2Phys_Dec;
   Bool_t          system_Hlt2Phys_TIS;
   Bool_t          system_Hlt2Phys_TOS;
   Bool_t          system_L0MuonDecision_Dec;
   Bool_t          system_L0MuonDecision_TIS;
   Bool_t          system_L0MuonDecision_TOS;
   Bool_t          system_L0DimuonDecision_Dec;
   Bool_t          system_L0DimuonDecision_TIS;
   Bool_t          system_L0DimuonDecision_TOS;
   Bool_t          system_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          system_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          system_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          system_Hlt2SingleMuonDecision_Dec;
   Bool_t          system_Hlt2SingleMuonDecision_TIS;
   Bool_t          system_Hlt2SingleMuonDecision_TOS;
   Bool_t          system_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          system_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          system_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          system_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          system_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          system_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          system_Hlt2DiMuonDecision_Dec;
   Bool_t          system_Hlt2DiMuonDecision_TIS;
   Bool_t          system_Hlt2DiMuonDecision_TOS;
   Bool_t          system_Hlt2DiMuonHighMassDecision_Dec;
   Bool_t          system_Hlt2DiMuonHighMassDecision_TIS;
   Bool_t          system_Hlt2DiMuonHighMassDecision_TOS;
   Bool_t          system_Hlt2DiMuonJpsi2MuMuDecision_Dec;
   Bool_t          system_Hlt2DiMuonJpsi2MuMuDecision_TIS;
   Bool_t          system_Hlt2DiMuonJpsi2MuMuDecision_TOS;
   Double_t        Jpsi_P;
   Double_t        Jpsi_PT;
   Double_t        Jpsi_PE;
   Double_t        Jpsi_PX;
   Double_t        Jpsi_PY;
   Double_t        Jpsi_PZ;
   Double_t        Jpsi_MM;
   Double_t        Jpsi_MMERR;
   Double_t        Jpsi_M;
   Int_t           Jpsi_ID;
   Bool_t          Jpsi_L0Global_Dec;
   Bool_t          Jpsi_L0Global_TIS;
   Bool_t          Jpsi_L0Global_TOS;
   Bool_t          Jpsi_Hlt1Global_Dec;
   Bool_t          Jpsi_Hlt1Global_TIS;
   Bool_t          Jpsi_Hlt1Global_TOS;
   Bool_t          Jpsi_Hlt1Phys_Dec;
   Bool_t          Jpsi_Hlt1Phys_TIS;
   Bool_t          Jpsi_Hlt1Phys_TOS;
   Bool_t          Jpsi_Hlt2Global_Dec;
   Bool_t          Jpsi_Hlt2Global_TIS;
   Bool_t          Jpsi_Hlt2Global_TOS;
   Bool_t          Jpsi_Hlt2Phys_Dec;
   Bool_t          Jpsi_Hlt2Phys_TIS;
   Bool_t          Jpsi_Hlt2Phys_TOS;
   Bool_t          Jpsi_L0MuonDecision_Dec;
   Bool_t          Jpsi_L0MuonDecision_TIS;
   Bool_t          Jpsi_L0MuonDecision_TOS;
   Bool_t          Jpsi_L0DimuonDecision_Dec;
   Bool_t          Jpsi_L0DimuonDecision_TIS;
   Bool_t          Jpsi_L0DimuonDecision_TOS;
   Bool_t          Jpsi_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          Jpsi_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          Jpsi_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          Jpsi_Hlt2SingleMuonDecision_Dec;
   Bool_t          Jpsi_Hlt2SingleMuonDecision_TIS;
   Bool_t          Jpsi_Hlt2SingleMuonDecision_TOS;
   Bool_t          Jpsi_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          Jpsi_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          Jpsi_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          Jpsi_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          Jpsi_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          Jpsi_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          Jpsi_Hlt2DiMuonDecision_Dec;
   Bool_t          Jpsi_Hlt2DiMuonDecision_TIS;
   Bool_t          Jpsi_Hlt2DiMuonDecision_TOS;
   Bool_t          Jpsi_Hlt2DiMuonHighMassDecision_Dec;
   Bool_t          Jpsi_Hlt2DiMuonHighMassDecision_TIS;
   Bool_t          Jpsi_Hlt2DiMuonHighMassDecision_TOS;
   Bool_t          Jpsi_Hlt2DiMuonJpsi2MuMuDecision_Dec;
   Bool_t          Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TIS;
   Bool_t          Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TOS;
   Double_t        mup_MC12TuneV2_ProbNNe;
   Double_t        mup_MC12TuneV2_ProbNNmu;
   Double_t        mup_MC12TuneV2_ProbNNpi;
   Double_t        mup_MC12TuneV2_ProbNNk;
   Double_t        mup_MC12TuneV2_ProbNNp;
   Double_t        mup_MC12TuneV2_ProbNNghost;
   Double_t        mup_MC12TuneV3_ProbNNe;
   Double_t        mup_MC12TuneV3_ProbNNmu;
   Double_t        mup_MC12TuneV3_ProbNNpi;
   Double_t        mup_MC12TuneV3_ProbNNk;
   Double_t        mup_MC12TuneV3_ProbNNp;
   Double_t        mup_MC12TuneV3_ProbNNghost;
   Double_t        mup_MC12TuneV4_ProbNNe;
   Double_t        mup_MC12TuneV4_ProbNNmu;
   Double_t        mup_MC12TuneV4_ProbNNpi;
   Double_t        mup_MC12TuneV4_ProbNNk;
   Double_t        mup_MC12TuneV4_ProbNNp;
   Double_t        mup_MC12TuneV4_ProbNNghost;
   Double_t        mup_MC15TuneV1_ProbNNe;
   Double_t        mup_MC15TuneV1_ProbNNmu;
   Double_t        mup_MC15TuneV1_ProbNNpi;
   Double_t        mup_MC15TuneV1_ProbNNk;
   Double_t        mup_MC15TuneV1_ProbNNp;
   Double_t        mup_MC15TuneV1_ProbNNghost;
   Double_t        mup_P;
   Double_t        mup_PT;
   Double_t        mup_PE;
   Double_t        mup_PX;
   Double_t        mup_PY;
   Double_t        mup_PZ;
   Double_t        mup_M;
   Int_t           mup_ID;
   Double_t        mup_PIDe;
   Double_t        mup_PIDmu;
   Double_t        mup_PIDK;
   Double_t        mup_PIDp;
   Double_t        mup_PIDd;
   Double_t        mup_ProbNNe;
   Double_t        mup_ProbNNk;
   Double_t        mup_ProbNNp;
   Double_t        mup_ProbNNpi;
   Double_t        mup_ProbNNmu;
   Double_t        mup_ProbNNd;
   Double_t        mup_ProbNNghost;
   Bool_t          mup_hasMuon;
   Bool_t          mup_isMuon;
   Bool_t          mup_hasRich;
   Bool_t          mup_UsedRichAerogel;
   Bool_t          mup_UsedRich1Gas;
   Bool_t          mup_UsedRich2Gas;
   Bool_t          mup_RichAboveElThres;
   Bool_t          mup_RichAboveMuThres;
   Bool_t          mup_RichAbovePiThres;
   Bool_t          mup_RichAboveKaThres;
   Bool_t          mup_RichAbovePrThres;
   Bool_t          mup_hasCalo;
   Bool_t          mup_L0Global_Dec;
   Bool_t          mup_L0Global_TIS;
   Bool_t          mup_L0Global_TOS;
   Bool_t          mup_Hlt1Global_Dec;
   Bool_t          mup_Hlt1Global_TIS;
   Bool_t          mup_Hlt1Global_TOS;
   Bool_t          mup_Hlt1Phys_Dec;
   Bool_t          mup_Hlt1Phys_TIS;
   Bool_t          mup_Hlt1Phys_TOS;
   Bool_t          mup_Hlt2Global_Dec;
   Bool_t          mup_Hlt2Global_TIS;
   Bool_t          mup_Hlt2Global_TOS;
   Bool_t          mup_Hlt2Phys_Dec;
   Bool_t          mup_Hlt2Phys_TIS;
   Bool_t          mup_Hlt2Phys_TOS;
   Bool_t          mup_L0MuonDecision_Dec;
   Bool_t          mup_L0MuonDecision_TIS;
   Bool_t          mup_L0MuonDecision_TOS;
   Bool_t          mup_L0DimuonDecision_Dec;
   Bool_t          mup_L0DimuonDecision_TIS;
   Bool_t          mup_L0DimuonDecision_TOS;
   Bool_t          mup_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          mup_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          mup_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          mup_Hlt2SingleMuonDecision_Dec;
   Bool_t          mup_Hlt2SingleMuonDecision_TIS;
   Bool_t          mup_Hlt2SingleMuonDecision_TOS;
   Bool_t          mup_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          mup_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          mup_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          mup_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          mup_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          mup_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          mup_Hlt2DiMuonDecision_Dec;
   Bool_t          mup_Hlt2DiMuonDecision_TIS;
   Bool_t          mup_Hlt2DiMuonDecision_TOS;
   Bool_t          mup_Hlt2DiMuonHighMassDecision_Dec;
   Bool_t          mup_Hlt2DiMuonHighMassDecision_TIS;
   Bool_t          mup_Hlt2DiMuonHighMassDecision_TOS;
   Bool_t          mup_Hlt2DiMuonJpsi2MuMuDecision_Dec;
   Bool_t          mup_Hlt2DiMuonJpsi2MuMuDecision_TIS;
   Bool_t          mup_Hlt2DiMuonJpsi2MuMuDecision_TOS;
   Double_t        mup_OWNPV_X;
   Double_t        mup_OWNPV_Y;
   Double_t        mup_OWNPV_Z;
   Double_t        mup_OWNPV_XERR;
   Double_t        mup_OWNPV_YERR;
   Double_t        mup_OWNPV_ZERR;
   Double_t        mup_OWNPV_CHI2;
   Int_t           mup_OWNPV_NDOF;
   Float_t         mup_OWNPV_COV_[3][3];
   Double_t        mup_IP_OWNPV;
   Double_t        mup_IPCHI2_OWNPV;
   Double_t        mup_ORIVX_X;
   Double_t        mup_ORIVX_Y;
   Double_t        mup_ORIVX_Z;
   Double_t        mup_ORIVX_XERR;
   Double_t        mup_ORIVX_YERR;
   Double_t        mup_ORIVX_ZERR;
   Double_t        mup_ORIVX_CHI2;
   Int_t           mup_ORIVX_NDOF;
   Float_t         mup_ORIVX_COV_[3][3];
   Int_t           mup_TRUEID;
   Double_t        mup_TRUEP_E;
   Double_t        mup_TRUEP_X;
   Double_t        mup_TRUEP_Y;
   Double_t        mup_TRUEP_Z;
   Double_t        mup_TRUEPT;
   Double_t        mup_TRUEORIGINVERTEX_X;
   Double_t        mup_TRUEORIGINVERTEX_Y;
   Double_t        mup_TRUEORIGINVERTEX_Z;
   Double_t        mup_TRUEENDVERTEX_X;
   Double_t        mup_TRUEENDVERTEX_Y;
   Double_t        mup_TRUEENDVERTEX_Z;
   Bool_t          mup_TRUEISSTABLE;
   Double_t        mup_TRUETAU;
   Int_t           mup_TRACK_Type;
   Int_t           mup_TRACK_Key;
   Double_t        mup_TRACK_CHI2NDOF;
   Double_t        mup_TRACK_PCHI2;
   Double_t        mup_TRACK_MatchCHI2;
   Double_t        mup_TRACK_GhostProb;
   Double_t        mup_TRACK_CloneDist;
   Double_t        mup_TRACK_Likelihood;
   Double_t        mum_MC12TuneV2_ProbNNe;
   Double_t        mum_MC12TuneV2_ProbNNmu;
   Double_t        mum_MC12TuneV2_ProbNNpi;
   Double_t        mum_MC12TuneV2_ProbNNk;
   Double_t        mum_MC12TuneV2_ProbNNp;
   Double_t        mum_MC12TuneV2_ProbNNghost;
   Double_t        mum_MC12TuneV3_ProbNNe;
   Double_t        mum_MC12TuneV3_ProbNNmu;
   Double_t        mum_MC12TuneV3_ProbNNpi;
   Double_t        mum_MC12TuneV3_ProbNNk;
   Double_t        mum_MC12TuneV3_ProbNNp;
   Double_t        mum_MC12TuneV3_ProbNNghost;
   Double_t        mum_MC12TuneV4_ProbNNe;
   Double_t        mum_MC12TuneV4_ProbNNmu;
   Double_t        mum_MC12TuneV4_ProbNNpi;
   Double_t        mum_MC12TuneV4_ProbNNk;
   Double_t        mum_MC12TuneV4_ProbNNp;
   Double_t        mum_MC12TuneV4_ProbNNghost;
   Double_t        mum_MC15TuneV1_ProbNNe;
   Double_t        mum_MC15TuneV1_ProbNNmu;
   Double_t        mum_MC15TuneV1_ProbNNpi;
   Double_t        mum_MC15TuneV1_ProbNNk;
   Double_t        mum_MC15TuneV1_ProbNNp;
   Double_t        mum_MC15TuneV1_ProbNNghost;
   Double_t        mum_P;
   Double_t        mum_PT;
   Double_t        mum_PE;
   Double_t        mum_PX;
   Double_t        mum_PY;
   Double_t        mum_PZ;
   Double_t        mum_M;
   Int_t           mum_ID;
   Double_t        mum_PIDe;
   Double_t        mum_PIDmu;
   Double_t        mum_PIDK;
   Double_t        mum_PIDp;
   Double_t        mum_PIDd;
   Double_t        mum_ProbNNe;
   Double_t        mum_ProbNNk;
   Double_t        mum_ProbNNp;
   Double_t        mum_ProbNNpi;
   Double_t        mum_ProbNNmu;
   Double_t        mum_ProbNNd;
   Double_t        mum_ProbNNghost;
   Bool_t          mum_hasMuon;
   Bool_t          mum_isMuon;
   Bool_t          mum_hasRich;
   Bool_t          mum_UsedRichAerogel;
   Bool_t          mum_UsedRich1Gas;
   Bool_t          mum_UsedRich2Gas;
   Bool_t          mum_RichAboveElThres;
   Bool_t          mum_RichAboveMuThres;
   Bool_t          mum_RichAbovePiThres;
   Bool_t          mum_RichAboveKaThres;
   Bool_t          mum_RichAbovePrThres;
   Bool_t          mum_hasCalo;
   Bool_t          mum_L0Global_Dec;
   Bool_t          mum_L0Global_TIS;
   Bool_t          mum_L0Global_TOS;
   Bool_t          mum_Hlt1Global_Dec;
   Bool_t          mum_Hlt1Global_TIS;
   Bool_t          mum_Hlt1Global_TOS;
   Bool_t          mum_Hlt1Phys_Dec;
   Bool_t          mum_Hlt1Phys_TIS;
   Bool_t          mum_Hlt1Phys_TOS;
   Bool_t          mum_Hlt2Global_Dec;
   Bool_t          mum_Hlt2Global_TIS;
   Bool_t          mum_Hlt2Global_TOS;
   Bool_t          mum_Hlt2Phys_Dec;
   Bool_t          mum_Hlt2Phys_TIS;
   Bool_t          mum_Hlt2Phys_TOS;
   Bool_t          mum_L0MuonDecision_Dec;
   Bool_t          mum_L0MuonDecision_TIS;
   Bool_t          mum_L0MuonDecision_TOS;
   Bool_t          mum_L0DimuonDecision_Dec;
   Bool_t          mum_L0DimuonDecision_TIS;
   Bool_t          mum_L0DimuonDecision_TOS;
   Bool_t          mum_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          mum_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          mum_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          mum_Hlt2SingleMuonDecision_Dec;
   Bool_t          mum_Hlt2SingleMuonDecision_TIS;
   Bool_t          mum_Hlt2SingleMuonDecision_TOS;
   Bool_t          mum_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          mum_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          mum_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          mum_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          mum_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          mum_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          mum_Hlt2DiMuonDecision_Dec;
   Bool_t          mum_Hlt2DiMuonDecision_TIS;
   Bool_t          mum_Hlt2DiMuonDecision_TOS;
   Bool_t          mum_Hlt2DiMuonHighMassDecision_Dec;
   Bool_t          mum_Hlt2DiMuonHighMassDecision_TIS;
   Bool_t          mum_Hlt2DiMuonHighMassDecision_TOS;
   Bool_t          mum_Hlt2DiMuonJpsi2MuMuDecision_Dec;
   Bool_t          mum_Hlt2DiMuonJpsi2MuMuDecision_TIS;
   Bool_t          mum_Hlt2DiMuonJpsi2MuMuDecision_TOS;
   Double_t        mum_OWNPV_X;
   Double_t        mum_OWNPV_Y;
   Double_t        mum_OWNPV_Z;
   Double_t        mum_OWNPV_XERR;
   Double_t        mum_OWNPV_YERR;
   Double_t        mum_OWNPV_ZERR;
   Double_t        mum_OWNPV_CHI2;
   Int_t           mum_OWNPV_NDOF;
   Float_t         mum_OWNPV_COV_[3][3];
   Double_t        mum_IP_OWNPV;
   Double_t        mum_IPCHI2_OWNPV;
   Double_t        mum_ORIVX_X;
   Double_t        mum_ORIVX_Y;
   Double_t        mum_ORIVX_Z;
   Double_t        mum_ORIVX_XERR;
   Double_t        mum_ORIVX_YERR;
   Double_t        mum_ORIVX_ZERR;
   Double_t        mum_ORIVX_CHI2;
   Int_t           mum_ORIVX_NDOF;
   Float_t         mum_ORIVX_COV_[3][3];
   Int_t           mum_TRUEID;
   Double_t        mum_TRUEP_E;
   Double_t        mum_TRUEP_X;
   Double_t        mum_TRUEP_Y;
   Double_t        mum_TRUEP_Z;
   Double_t        mum_TRUEPT;
   Double_t        mum_TRUEORIGINVERTEX_X;
   Double_t        mum_TRUEORIGINVERTEX_Y;
   Double_t        mum_TRUEORIGINVERTEX_Z;
   Double_t        mum_TRUEENDVERTEX_X;
   Double_t        mum_TRUEENDVERTEX_Y;
   Double_t        mum_TRUEENDVERTEX_Z;
   Bool_t          mum_TRUEISSTABLE;
   Double_t        mum_TRUETAU;
   Int_t           mum_TRACK_Type;
   Int_t           mum_TRACK_Key;
   Double_t        mum_TRACK_CHI2NDOF;
   Double_t        mum_TRACK_PCHI2;
   Double_t        mum_TRACK_MatchCHI2;
   Double_t        mum_TRACK_GhostProb;
   Double_t        mum_TRACK_CloneDist;
   Double_t        mum_TRACK_Likelihood;
   Double_t        K_MC12TuneV2_ProbNNe;
   Double_t        K_MC12TuneV2_ProbNNmu;
   Double_t        K_MC12TuneV2_ProbNNpi;
   Double_t        K_MC12TuneV2_ProbNNk;
   Double_t        K_MC12TuneV2_ProbNNp;
   Double_t        K_MC12TuneV2_ProbNNghost;
   Double_t        K_MC12TuneV3_ProbNNe;
   Double_t        K_MC12TuneV3_ProbNNmu;
   Double_t        K_MC12TuneV3_ProbNNpi;
   Double_t        K_MC12TuneV3_ProbNNk;
   Double_t        K_MC12TuneV3_ProbNNp;
   Double_t        K_MC12TuneV3_ProbNNghost;
   Double_t        K_MC12TuneV4_ProbNNe;
   Double_t        K_MC12TuneV4_ProbNNmu;
   Double_t        K_MC12TuneV4_ProbNNpi;
   Double_t        K_MC12TuneV4_ProbNNk;
   Double_t        K_MC12TuneV4_ProbNNp;
   Double_t        K_MC12TuneV4_ProbNNghost;
   Double_t        K_MC15TuneV1_ProbNNe;
   Double_t        K_MC15TuneV1_ProbNNmu;
   Double_t        K_MC15TuneV1_ProbNNpi;
   Double_t        K_MC15TuneV1_ProbNNk;
   Double_t        K_MC15TuneV1_ProbNNp;
   Double_t        K_MC15TuneV1_ProbNNghost;
   Double_t        K_P;
   Double_t        K_PT;
   Double_t        K_PE;
   Double_t        K_PX;
   Double_t        K_PY;
   Double_t        K_PZ;
   Double_t        K_M;
   Int_t           K_ID;
   Double_t        K_PIDe;
   Double_t        K_PIDmu;
   Double_t        K_PIDK;
   Double_t        K_PIDp;
   Double_t        K_PIDd;
   Double_t        K_ProbNNe;
   Double_t        K_ProbNNk;
   Double_t        K_ProbNNp;
   Double_t        K_ProbNNpi;
   Double_t        K_ProbNNmu;
   Double_t        K_ProbNNd;
   Double_t        K_ProbNNghost;
   Bool_t          K_hasMuon;
   Bool_t          K_isMuon;
   Bool_t          K_hasRich;
   Bool_t          K_UsedRichAerogel;
   Bool_t          K_UsedRich1Gas;
   Bool_t          K_UsedRich2Gas;
   Bool_t          K_RichAboveElThres;
   Bool_t          K_RichAboveMuThres;
   Bool_t          K_RichAbovePiThres;
   Bool_t          K_RichAboveKaThres;
   Bool_t          K_RichAbovePrThres;
   Bool_t          K_hasCalo;
   Bool_t          K_L0Global_Dec;
   Bool_t          K_L0Global_TIS;
   Bool_t          K_L0Global_TOS;
   Bool_t          K_Hlt1Global_Dec;
   Bool_t          K_Hlt1Global_TIS;
   Bool_t          K_Hlt1Global_TOS;
   Bool_t          K_Hlt1Phys_Dec;
   Bool_t          K_Hlt1Phys_TIS;
   Bool_t          K_Hlt1Phys_TOS;
   Bool_t          K_Hlt2Global_Dec;
   Bool_t          K_Hlt2Global_TIS;
   Bool_t          K_Hlt2Global_TOS;
   Bool_t          K_Hlt2Phys_Dec;
   Bool_t          K_Hlt2Phys_TIS;
   Bool_t          K_Hlt2Phys_TOS;
   Bool_t          K_L0MuonDecision_Dec;
   Bool_t          K_L0MuonDecision_TIS;
   Bool_t          K_L0MuonDecision_TOS;
   Bool_t          K_L0DimuonDecision_Dec;
   Bool_t          K_L0DimuonDecision_TIS;
   Bool_t          K_L0DimuonDecision_TOS;
   Bool_t          K_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          K_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          K_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          K_Hlt2SingleMuonDecision_Dec;
   Bool_t          K_Hlt2SingleMuonDecision_TIS;
   Bool_t          K_Hlt2SingleMuonDecision_TOS;
   Bool_t          K_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          K_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          K_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          K_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          K_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          K_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          K_Hlt2DiMuonDecision_Dec;
   Bool_t          K_Hlt2DiMuonDecision_TIS;
   Bool_t          K_Hlt2DiMuonDecision_TOS;
   Bool_t          K_Hlt2DiMuonHighMassDecision_Dec;
   Bool_t          K_Hlt2DiMuonHighMassDecision_TIS;
   Bool_t          K_Hlt2DiMuonHighMassDecision_TOS;
   Bool_t          K_Hlt2DiMuonJpsi2MuMuDecision_Dec;
   Bool_t          K_Hlt2DiMuonJpsi2MuMuDecision_TIS;
   Bool_t          K_Hlt2DiMuonJpsi2MuMuDecision_TOS;
   Double_t        K_OWNPV_X;
   Double_t        K_OWNPV_Y;
   Double_t        K_OWNPV_Z;
   Double_t        K_OWNPV_XERR;
   Double_t        K_OWNPV_YERR;
   Double_t        K_OWNPV_ZERR;
   Double_t        K_OWNPV_CHI2;
   Int_t           K_OWNPV_NDOF;
   Float_t         K_OWNPV_COV_[3][3];
   Double_t        K_IP_OWNPV;
   Double_t        K_IPCHI2_OWNPV;
   Double_t        K_ORIVX_X;
   Double_t        K_ORIVX_Y;
   Double_t        K_ORIVX_Z;
   Double_t        K_ORIVX_XERR;
   Double_t        K_ORIVX_YERR;
   Double_t        K_ORIVX_ZERR;
   Double_t        K_ORIVX_CHI2;
   Int_t           K_ORIVX_NDOF;
   Float_t         K_ORIVX_COV_[3][3];
   Int_t           K_TRUEID;
   Double_t        K_TRUEP_E;
   Double_t        K_TRUEP_X;
   Double_t        K_TRUEP_Y;
   Double_t        K_TRUEP_Z;
   Double_t        K_TRUEPT;
   Double_t        K_TRUEORIGINVERTEX_X;
   Double_t        K_TRUEORIGINVERTEX_Y;
   Double_t        K_TRUEORIGINVERTEX_Z;
   Double_t        K_TRUEENDVERTEX_X;
   Double_t        K_TRUEENDVERTEX_Y;
   Double_t        K_TRUEENDVERTEX_Z;
   Bool_t          K_TRUEISSTABLE;
   Double_t        K_TRUETAU;
   Int_t           K_TRACK_Type;
   Int_t           K_TRACK_Key;
   Double_t        K_TRACK_CHI2NDOF;
   Double_t        K_TRACK_PCHI2;
   Double_t        K_TRACK_MatchCHI2;
   Double_t        K_TRACK_GhostProb;
   Double_t        K_TRACK_CloneDist;
   Double_t        K_TRACK_Likelihood;
   Double_t        Jet_P;
   Double_t        Jet_PT;
   Double_t        Jet_PE;
   Double_t        Jet_PX;
   Double_t        Jet_PY;
   Double_t        Jet_PZ;
   Double_t        Jet_MM;
   Double_t        Jet_MMERR;
   Double_t        Jet_M;
   Int_t           Jet_ID;
   Bool_t          Jet_L0Global_Dec;
   Bool_t          Jet_L0Global_TIS;
   Bool_t          Jet_L0Global_TOS;
   Bool_t          Jet_Hlt1Global_Dec;
   Bool_t          Jet_Hlt1Global_TIS;
   Bool_t          Jet_Hlt1Global_TOS;
   Bool_t          Jet_Hlt1Phys_Dec;
   Bool_t          Jet_Hlt1Phys_TIS;
   Bool_t          Jet_Hlt1Phys_TOS;
   Bool_t          Jet_Hlt2Global_Dec;
   Bool_t          Jet_Hlt2Global_TIS;
   Bool_t          Jet_Hlt2Global_TOS;
   Bool_t          Jet_Hlt2Phys_Dec;
   Bool_t          Jet_Hlt2Phys_TIS;
   Bool_t          Jet_Hlt2Phys_TOS;
   Bool_t          Jet_L0MuonDecision_Dec;
   Bool_t          Jet_L0MuonDecision_TIS;
   Bool_t          Jet_L0MuonDecision_TOS;
   Bool_t          Jet_L0DimuonDecision_Dec;
   Bool_t          Jet_L0DimuonDecision_TIS;
   Bool_t          Jet_L0DimuonDecision_TOS;
   Bool_t          Jet_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          Jet_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          Jet_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          Jet_Hlt2SingleMuonDecision_Dec;
   Bool_t          Jet_Hlt2SingleMuonDecision_TIS;
   Bool_t          Jet_Hlt2SingleMuonDecision_TOS;
   Bool_t          Jet_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          Jet_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          Jet_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          Jet_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          Jet_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          Jet_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          Jet_Hlt2DiMuonDecision_Dec;
   Bool_t          Jet_Hlt2DiMuonDecision_TIS;
   Bool_t          Jet_Hlt2DiMuonDecision_TOS;
   Bool_t          Jet_Hlt2DiMuonHighMassDecision_Dec;
   Bool_t          Jet_Hlt2DiMuonHighMassDecision_TIS;
   Bool_t          Jet_Hlt2DiMuonHighMassDecision_TOS;
   Bool_t          Jet_Hlt2DiMuonJpsi2MuMuDecision_Dec;
   Bool_t          Jet_Hlt2DiMuonJpsi2MuMuDecision_TIS;
   Bool_t          Jet_Hlt2DiMuonJpsi2MuMuDecision_TOS;
   Int_t           Jet_Dtr_nrecodtr;
   Double_t        jet_XVTX;
   Double_t        jet_YVTX;
   Double_t        jet_ZVTX;
   Int_t           Jet_NDtr;
   Float_t         Jet_Dtr_ID[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ThreeCharge[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_IsMeson[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_IsBaryon[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_IsStrange[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PIDe[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PIDmu[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PIDk[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PIDp[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PIDpi[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ProbNNe[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ProbNNmu[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ProbNNk[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ProbNNp[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ProbNNpi[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ProbNNghost[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PY[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PZ[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_E[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_P[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PT[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_M[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PHI[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ETA[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_XVTX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_YVTX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_ZVTX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_R[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_JT[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_Z[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TrackType[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TrackKey[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TrackChi2[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TrackNDF[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TrackPCHI2[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PFType[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PFDaughterType[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PFclustype[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_PFclusE[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_ID[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_ThreeCharge[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_IsMeson[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_IsBaryon[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_IsStrange[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_PX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_PY[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_PZ[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_E[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_P[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_PT[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_M[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_PHI[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_ETA[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_XVTX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_YVTX[1024];   //[Jet_NDtr]
   Float_t         Jet_Dtr_TRUE_ZVTX[1024];   //[Jet_NDtr]
   Double_t        Jet_Eta;
   Double_t        Jet_Phi;
   Double_t        Jet_MLoKi;
   Double_t        Jet_MMLoKi;
   Double_t        Jet_NTrk;
   Double_t        Jet_N90;
   Double_t        Jet_MTF;
   Double_t        Jet_NSatCells;
   Double_t        Jet_NHasPVInfo;
   Double_t        Jet_JEC_Cor;
   Double_t        Jet_JEC_PV;
   Double_t        Jet_JEC_Error;
   Int_t           Jet_TagKey;
   Double_t        Jet_w;
   Double_t        Jet_CPF;
   Double_t        Jet_JetWidth;
   Double_t        Jet_NSatECAL;
   Double_t        Jet_NSatHCAL;
   Double_t        Jet_NIPChi2Inf4;
   Double_t        Jet_EfCharged;
   Double_t        Jet_EfChargedHadron;
   Double_t        Jet_EfMuon;
   Double_t        Jet_EfElectron;
   Double_t        Jet_EfNeutral;
   Double_t        Jet_EfPhoton;
   Double_t        Jet_EfPi0;
   Double_t        Jet_EfMPi0;
   Double_t        Jet_EfRPi0;
   Double_t        Jet_EfNHad;
   Double_t        Jet_EfNReco;
   Double_t        Jet_EfCompo;
   Double_t        Jet_EfV0;
   Double_t        Jet_EfD;
   Double_t        Jet_EfB;
   Double_t        Jet_EfBadParticle;
   Double_t        Jet_EfCharged0Momentum;
   Double_t        Jet_EfChargedInfMomentum;
   Double_t        Jet_EfBadPhotonMatchingT;
   Double_t        Jet_EfBadPhoton;
   Double_t        Jet_EfIsolatedPhoton;
   Double_t        Jet_NLongTrk;
   Double_t        Jet_EfLongTrk;
   Double_t        Jet_NDownTrk;
   Double_t        Jet_EfDownTrk;
   Double_t        Jet_NUpTrk;
   Double_t        Jet_EfUpTrk;
   Double_t        Jet_PU_NPVs;
   Double_t        Jet_PU_Cone06_SumPTLongTrk;
   Double_t        Jet_PU_Cone06_SumELongTrk;
   Double_t        Jet_PU_Cone06_NLongTrk;
   Double_t        Jet_PU_Cone06_NUpVeloTrk;
   Double_t        Jet_PU_Cone10_SumPTLongTrk;
   Double_t        Jet_PU_Cone10_SumELongTrk;
   Double_t        Jet_PU_Cone10_NLongTrk;
   Double_t        Jet_PU_Cone10_NUpVeloTrk;
   Double_t        Jet_PU_Cone15_SumPTLongTrk;
   Double_t        Jet_PU_Cone15_SumELongTrk;
   Double_t        Jet_PU_Cone15_NLongTrk;
   Double_t        Jet_PU_Cone15_NUpVeloTrk;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLT1TCK;
   UInt_t          HLT2TCK;
   ULong64_t       GpsTime;
   Short_t         Polarity;
   Int_t           nPVs;
   Int_t           nTracks;
   Int_t           nLongTracks;
   Int_t           nDownstreamTracks;
   Int_t           nUpstreamTracks;
   Int_t           nVeloTracks;
   Int_t           nTTracks;
   Int_t           nBackTracks;
   Int_t           nRich1Hits;
   Int_t           nRich2Hits;
   Int_t           nVeloClusters;
   Int_t           nITClusters;
   Int_t           nTTClusters;
   Int_t           nOTClusters;
   Int_t           nSPDHits;
   Int_t           nMuonCoordsS0;
   Int_t           nMuonCoordsS1;
   Int_t           nMuonCoordsS2;
   Int_t           nMuonCoordsS3;
   Int_t           nMuonCoordsS4;
   Int_t           nMuonTracks;

   // List of branches
   TBranch        *b_system_P;   //!
   TBranch        *b_system_PT;   //!
   TBranch        *b_system_PE;   //!
   TBranch        *b_system_PX;   //!
   TBranch        *b_system_PY;   //!
   TBranch        *b_system_PZ;   //!
   TBranch        *b_system_MM;   //!
   TBranch        *b_system_MMERR;   //!
   TBranch        *b_system_M;   //!
   TBranch        *b_system_ID;   //!
   TBranch        *b_system_L0Global_Dec;   //!
   TBranch        *b_system_L0Global_TIS;   //!
   TBranch        *b_system_L0Global_TOS;   //!
   TBranch        *b_system_Hlt1Global_Dec;   //!
   TBranch        *b_system_Hlt1Global_TIS;   //!
   TBranch        *b_system_Hlt1Global_TOS;   //!
   TBranch        *b_system_Hlt1Phys_Dec;   //!
   TBranch        *b_system_Hlt1Phys_TIS;   //!
   TBranch        *b_system_Hlt1Phys_TOS;   //!
   TBranch        *b_system_Hlt2Global_Dec;   //!
   TBranch        *b_system_Hlt2Global_TIS;   //!
   TBranch        *b_system_Hlt2Global_TOS;   //!
   TBranch        *b_system_Hlt2Phys_Dec;   //!
   TBranch        *b_system_Hlt2Phys_TIS;   //!
   TBranch        *b_system_Hlt2Phys_TOS;   //!
   TBranch        *b_system_L0MuonDecision_Dec;   //!
   TBranch        *b_system_L0MuonDecision_TIS;   //!
   TBranch        *b_system_L0MuonDecision_TOS;   //!
   TBranch        *b_system_L0DimuonDecision_Dec;   //!
   TBranch        *b_system_L0DimuonDecision_TIS;   //!
   TBranch        *b_system_L0DimuonDecision_TOS;   //!
   TBranch        *b_system_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_system_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_system_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_system_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_system_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_system_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_system_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_system_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_system_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_system_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_system_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_system_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_system_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_system_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_system_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_system_Hlt2DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_system_Hlt2DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_system_Hlt2DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_system_Hlt2DiMuonJpsi2MuMuDecision_Dec;   //!
   TBranch        *b_system_Hlt2DiMuonJpsi2MuMuDecision_TIS;   //!
   TBranch        *b_system_Hlt2DiMuonJpsi2MuMuDecision_TOS;   //!
   TBranch        *b_Jpsi_P;   //!
   TBranch        *b_Jpsi_PT;   //!
   TBranch        *b_Jpsi_PE;   //!
   TBranch        *b_Jpsi_PX;   //!
   TBranch        *b_Jpsi_PY;   //!
   TBranch        *b_Jpsi_PZ;   //!
   TBranch        *b_Jpsi_MM;   //!
   TBranch        *b_Jpsi_MMERR;   //!
   TBranch        *b_Jpsi_M;   //!
   TBranch        *b_Jpsi_ID;   //!
   TBranch        *b_Jpsi_L0Global_Dec;   //!
   TBranch        *b_Jpsi_L0Global_TIS;   //!
   TBranch        *b_Jpsi_L0Global_TOS;   //!
   TBranch        *b_Jpsi_Hlt1Global_Dec;   //!
   TBranch        *b_Jpsi_Hlt1Global_TIS;   //!
   TBranch        *b_Jpsi_Hlt1Global_TOS;   //!
   TBranch        *b_Jpsi_Hlt1Phys_Dec;   //!
   TBranch        *b_Jpsi_Hlt1Phys_TIS;   //!
   TBranch        *b_Jpsi_Hlt1Phys_TOS;   //!
   TBranch        *b_Jpsi_Hlt2Global_Dec;   //!
   TBranch        *b_Jpsi_Hlt2Global_TIS;   //!
   TBranch        *b_Jpsi_Hlt2Global_TOS;   //!
   TBranch        *b_Jpsi_Hlt2Phys_Dec;   //!
   TBranch        *b_Jpsi_Hlt2Phys_TIS;   //!
   TBranch        *b_Jpsi_Hlt2Phys_TOS;   //!
   TBranch        *b_Jpsi_L0MuonDecision_Dec;   //!
   TBranch        *b_Jpsi_L0MuonDecision_TIS;   //!
   TBranch        *b_Jpsi_L0MuonDecision_TOS;   //!
   TBranch        *b_Jpsi_L0DimuonDecision_Dec;   //!
   TBranch        *b_Jpsi_L0DimuonDecision_TIS;   //!
   TBranch        *b_Jpsi_L0DimuonDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonJpsi2MuMuDecision_Dec;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TIS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TOS;   //!
   TBranch        *b_mup_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_mup_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_mup_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_mup_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_mup_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_mup_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_mup_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_mup_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_mup_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_mup_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_mup_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_mup_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_mup_MC12TuneV4_ProbNNe;   //!
   TBranch        *b_mup_MC12TuneV4_ProbNNmu;   //!
   TBranch        *b_mup_MC12TuneV4_ProbNNpi;   //!
   TBranch        *b_mup_MC12TuneV4_ProbNNk;   //!
   TBranch        *b_mup_MC12TuneV4_ProbNNp;   //!
   TBranch        *b_mup_MC12TuneV4_ProbNNghost;   //!
   TBranch        *b_mup_MC15TuneV1_ProbNNe;   //!
   TBranch        *b_mup_MC15TuneV1_ProbNNmu;   //!
   TBranch        *b_mup_MC15TuneV1_ProbNNpi;   //!
   TBranch        *b_mup_MC15TuneV1_ProbNNk;   //!
   TBranch        *b_mup_MC15TuneV1_ProbNNp;   //!
   TBranch        *b_mup_MC15TuneV1_ProbNNghost;   //!
   TBranch        *b_mup_P;   //!
   TBranch        *b_mup_PT;   //!
   TBranch        *b_mup_PE;   //!
   TBranch        *b_mup_PX;   //!
   TBranch        *b_mup_PY;   //!
   TBranch        *b_mup_PZ;   //!
   TBranch        *b_mup_M;   //!
   TBranch        *b_mup_ID;   //!
   TBranch        *b_mup_PIDe;   //!
   TBranch        *b_mup_PIDmu;   //!
   TBranch        *b_mup_PIDK;   //!
   TBranch        *b_mup_PIDp;   //!
   TBranch        *b_mup_PIDd;   //!
   TBranch        *b_mup_ProbNNe;   //!
   TBranch        *b_mup_ProbNNk;   //!
   TBranch        *b_mup_ProbNNp;   //!
   TBranch        *b_mup_ProbNNpi;   //!
   TBranch        *b_mup_ProbNNmu;   //!
   TBranch        *b_mup_ProbNNd;   //!
   TBranch        *b_mup_ProbNNghost;   //!
   TBranch        *b_mup_hasMuon;   //!
   TBranch        *b_mup_isMuon;   //!
   TBranch        *b_mup_hasRich;   //!
   TBranch        *b_mup_UsedRichAerogel;   //!
   TBranch        *b_mup_UsedRich1Gas;   //!
   TBranch        *b_mup_UsedRich2Gas;   //!
   TBranch        *b_mup_RichAboveElThres;   //!
   TBranch        *b_mup_RichAboveMuThres;   //!
   TBranch        *b_mup_RichAbovePiThres;   //!
   TBranch        *b_mup_RichAboveKaThres;   //!
   TBranch        *b_mup_RichAbovePrThres;   //!
   TBranch        *b_mup_hasCalo;   //!
   TBranch        *b_mup_L0Global_Dec;   //!
   TBranch        *b_mup_L0Global_TIS;   //!
   TBranch        *b_mup_L0Global_TOS;   //!
   TBranch        *b_mup_Hlt1Global_Dec;   //!
   TBranch        *b_mup_Hlt1Global_TIS;   //!
   TBranch        *b_mup_Hlt1Global_TOS;   //!
   TBranch        *b_mup_Hlt1Phys_Dec;   //!
   TBranch        *b_mup_Hlt1Phys_TIS;   //!
   TBranch        *b_mup_Hlt1Phys_TOS;   //!
   TBranch        *b_mup_Hlt2Global_Dec;   //!
   TBranch        *b_mup_Hlt2Global_TIS;   //!
   TBranch        *b_mup_Hlt2Global_TOS;   //!
   TBranch        *b_mup_Hlt2Phys_Dec;   //!
   TBranch        *b_mup_Hlt2Phys_TIS;   //!
   TBranch        *b_mup_Hlt2Phys_TOS;   //!
   TBranch        *b_mup_L0MuonDecision_Dec;   //!
   TBranch        *b_mup_L0MuonDecision_TIS;   //!
   TBranch        *b_mup_L0MuonDecision_TOS;   //!
   TBranch        *b_mup_L0DimuonDecision_Dec;   //!
   TBranch        *b_mup_L0DimuonDecision_TIS;   //!
   TBranch        *b_mup_L0DimuonDecision_TOS;   //!
   TBranch        *b_mup_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_mup_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_mup_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_mup_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_mup_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_mup_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_mup_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_mup_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_mup_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_mup_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_mup_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_mup_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_mup_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_mup_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_mup_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_mup_Hlt2DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_mup_Hlt2DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_mup_Hlt2DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_mup_Hlt2DiMuonJpsi2MuMuDecision_Dec;   //!
   TBranch        *b_mup_Hlt2DiMuonJpsi2MuMuDecision_TIS;   //!
   TBranch        *b_mup_Hlt2DiMuonJpsi2MuMuDecision_TOS;   //!
   TBranch        *b_mup_OWNPV_X;   //!
   TBranch        *b_mup_OWNPV_Y;   //!
   TBranch        *b_mup_OWNPV_Z;   //!
   TBranch        *b_mup_OWNPV_XERR;   //!
   TBranch        *b_mup_OWNPV_YERR;   //!
   TBranch        *b_mup_OWNPV_ZERR;   //!
   TBranch        *b_mup_OWNPV_CHI2;   //!
   TBranch        *b_mup_OWNPV_NDOF;   //!
   TBranch        *b_mup_OWNPV_COV_;   //!
   TBranch        *b_mup_IP_OWNPV;   //!
   TBranch        *b_mup_IPCHI2_OWNPV;   //!
   TBranch        *b_mup_ORIVX_X;   //!
   TBranch        *b_mup_ORIVX_Y;   //!
   TBranch        *b_mup_ORIVX_Z;   //!
   TBranch        *b_mup_ORIVX_XERR;   //!
   TBranch        *b_mup_ORIVX_YERR;   //!
   TBranch        *b_mup_ORIVX_ZERR;   //!
   TBranch        *b_mup_ORIVX_CHI2;   //!
   TBranch        *b_mup_ORIVX_NDOF;   //!
   TBranch        *b_mup_ORIVX_COV_;   //!
   TBranch        *b_mup_TRUEID;   //!
   TBranch        *b_mup_TRUEP_E;   //!
   TBranch        *b_mup_TRUEP_X;   //!
   TBranch        *b_mup_TRUEP_Y;   //!
   TBranch        *b_mup_TRUEP_Z;   //!
   TBranch        *b_mup_TRUEPT;   //!
   TBranch        *b_mup_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_mup_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_mup_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_mup_TRUEENDVERTEX_X;   //!
   TBranch        *b_mup_TRUEENDVERTEX_Y;   //!
   TBranch        *b_mup_TRUEENDVERTEX_Z;   //!
   TBranch        *b_mup_TRUEISSTABLE;   //!
   TBranch        *b_mup_TRUETAU;   //!
   TBranch        *b_mup_TRACK_Type;   //!
   TBranch        *b_mup_TRACK_Key;   //!
   TBranch        *b_mup_TRACK_CHI2NDOF;   //!
   TBranch        *b_mup_TRACK_PCHI2;   //!
   TBranch        *b_mup_TRACK_MatchCHI2;   //!
   TBranch        *b_mup_TRACK_GhostProb;   //!
   TBranch        *b_mup_TRACK_CloneDist;   //!
   TBranch        *b_mup_TRACK_Likelihood;   //!
   TBranch        *b_mum_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_mum_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_mum_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_mum_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_mum_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_mum_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_mum_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_mum_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_mum_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_mum_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_mum_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_mum_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_mum_MC12TuneV4_ProbNNe;   //!
   TBranch        *b_mum_MC12TuneV4_ProbNNmu;   //!
   TBranch        *b_mum_MC12TuneV4_ProbNNpi;   //!
   TBranch        *b_mum_MC12TuneV4_ProbNNk;   //!
   TBranch        *b_mum_MC12TuneV4_ProbNNp;   //!
   TBranch        *b_mum_MC12TuneV4_ProbNNghost;   //!
   TBranch        *b_mum_MC15TuneV1_ProbNNe;   //!
   TBranch        *b_mum_MC15TuneV1_ProbNNmu;   //!
   TBranch        *b_mum_MC15TuneV1_ProbNNpi;   //!
   TBranch        *b_mum_MC15TuneV1_ProbNNk;   //!
   TBranch        *b_mum_MC15TuneV1_ProbNNp;   //!
   TBranch        *b_mum_MC15TuneV1_ProbNNghost;   //!
   TBranch        *b_mum_P;   //!
   TBranch        *b_mum_PT;   //!
   TBranch        *b_mum_PE;   //!
   TBranch        *b_mum_PX;   //!
   TBranch        *b_mum_PY;   //!
   TBranch        *b_mum_PZ;   //!
   TBranch        *b_mum_M;   //!
   TBranch        *b_mum_ID;   //!
   TBranch        *b_mum_PIDe;   //!
   TBranch        *b_mum_PIDmu;   //!
   TBranch        *b_mum_PIDK;   //!
   TBranch        *b_mum_PIDp;   //!
   TBranch        *b_mum_PIDd;   //!
   TBranch        *b_mum_ProbNNe;   //!
   TBranch        *b_mum_ProbNNk;   //!
   TBranch        *b_mum_ProbNNp;   //!
   TBranch        *b_mum_ProbNNpi;   //!
   TBranch        *b_mum_ProbNNmu;   //!
   TBranch        *b_mum_ProbNNd;   //!
   TBranch        *b_mum_ProbNNghost;   //!
   TBranch        *b_mum_hasMuon;   //!
   TBranch        *b_mum_isMuon;   //!
   TBranch        *b_mum_hasRich;   //!
   TBranch        *b_mum_UsedRichAerogel;   //!
   TBranch        *b_mum_UsedRich1Gas;   //!
   TBranch        *b_mum_UsedRich2Gas;   //!
   TBranch        *b_mum_RichAboveElThres;   //!
   TBranch        *b_mum_RichAboveMuThres;   //!
   TBranch        *b_mum_RichAbovePiThres;   //!
   TBranch        *b_mum_RichAboveKaThres;   //!
   TBranch        *b_mum_RichAbovePrThres;   //!
   TBranch        *b_mum_hasCalo;   //!
   TBranch        *b_mum_L0Global_Dec;   //!
   TBranch        *b_mum_L0Global_TIS;   //!
   TBranch        *b_mum_L0Global_TOS;   //!
   TBranch        *b_mum_Hlt1Global_Dec;   //!
   TBranch        *b_mum_Hlt1Global_TIS;   //!
   TBranch        *b_mum_Hlt1Global_TOS;   //!
   TBranch        *b_mum_Hlt1Phys_Dec;   //!
   TBranch        *b_mum_Hlt1Phys_TIS;   //!
   TBranch        *b_mum_Hlt1Phys_TOS;   //!
   TBranch        *b_mum_Hlt2Global_Dec;   //!
   TBranch        *b_mum_Hlt2Global_TIS;   //!
   TBranch        *b_mum_Hlt2Global_TOS;   //!
   TBranch        *b_mum_Hlt2Phys_Dec;   //!
   TBranch        *b_mum_Hlt2Phys_TIS;   //!
   TBranch        *b_mum_Hlt2Phys_TOS;   //!
   TBranch        *b_mum_L0MuonDecision_Dec;   //!
   TBranch        *b_mum_L0MuonDecision_TIS;   //!
   TBranch        *b_mum_L0MuonDecision_TOS;   //!
   TBranch        *b_mum_L0DimuonDecision_Dec;   //!
   TBranch        *b_mum_L0DimuonDecision_TIS;   //!
   TBranch        *b_mum_L0DimuonDecision_TOS;   //!
   TBranch        *b_mum_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_mum_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_mum_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_mum_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_mum_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_mum_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_mum_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_mum_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_mum_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_mum_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_mum_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_mum_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_mum_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_mum_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_mum_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_mum_Hlt2DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_mum_Hlt2DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_mum_Hlt2DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_mum_Hlt2DiMuonJpsi2MuMuDecision_Dec;   //!
   TBranch        *b_mum_Hlt2DiMuonJpsi2MuMuDecision_TIS;   //!
   TBranch        *b_mum_Hlt2DiMuonJpsi2MuMuDecision_TOS;   //!
   TBranch        *b_mum_OWNPV_X;   //!
   TBranch        *b_mum_OWNPV_Y;   //!
   TBranch        *b_mum_OWNPV_Z;   //!
   TBranch        *b_mum_OWNPV_XERR;   //!
   TBranch        *b_mum_OWNPV_YERR;   //!
   TBranch        *b_mum_OWNPV_ZERR;   //!
   TBranch        *b_mum_OWNPV_CHI2;   //!
   TBranch        *b_mum_OWNPV_NDOF;   //!
   TBranch        *b_mum_OWNPV_COV_;   //!
   TBranch        *b_mum_IP_OWNPV;   //!
   TBranch        *b_mum_IPCHI2_OWNPV;   //!
   TBranch        *b_mum_ORIVX_X;   //!
   TBranch        *b_mum_ORIVX_Y;   //!
   TBranch        *b_mum_ORIVX_Z;   //!
   TBranch        *b_mum_ORIVX_XERR;   //!
   TBranch        *b_mum_ORIVX_YERR;   //!
   TBranch        *b_mum_ORIVX_ZERR;   //!
   TBranch        *b_mum_ORIVX_CHI2;   //!
   TBranch        *b_mum_ORIVX_NDOF;   //!
   TBranch        *b_mum_ORIVX_COV_;   //!
   TBranch        *b_mum_TRUEID;   //!
   TBranch        *b_mum_TRUEP_E;   //!
   TBranch        *b_mum_TRUEP_X;   //!
   TBranch        *b_mum_TRUEP_Y;   //!
   TBranch        *b_mum_TRUEP_Z;   //!
   TBranch        *b_mum_TRUEPT;   //!
   TBranch        *b_mum_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_mum_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_mum_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_mum_TRUEENDVERTEX_X;   //!
   TBranch        *b_mum_TRUEENDVERTEX_Y;   //!
   TBranch        *b_mum_TRUEENDVERTEX_Z;   //!
   TBranch        *b_mum_TRUEISSTABLE;   //!
   TBranch        *b_mum_TRUETAU;   //!
   TBranch        *b_mum_TRACK_Type;   //!
   TBranch        *b_mum_TRACK_Key;   //!
   TBranch        *b_mum_TRACK_CHI2NDOF;   //!
   TBranch        *b_mum_TRACK_PCHI2;   //!
   TBranch        *b_mum_TRACK_MatchCHI2;   //!
   TBranch        *b_mum_TRACK_GhostProb;   //!
   TBranch        *b_mum_TRACK_CloneDist;   //!
   TBranch        *b_mum_TRACK_Likelihood;   //!
   TBranch        *b_K_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_K_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_K_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_K_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_K_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_K_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_K_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_K_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_K_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_K_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_K_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_K_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_K_MC12TuneV4_ProbNNe;   //!
   TBranch        *b_K_MC12TuneV4_ProbNNmu;   //!
   TBranch        *b_K_MC12TuneV4_ProbNNpi;   //!
   TBranch        *b_K_MC12TuneV4_ProbNNk;   //!
   TBranch        *b_K_MC12TuneV4_ProbNNp;   //!
   TBranch        *b_K_MC12TuneV4_ProbNNghost;   //!
   TBranch        *b_K_MC15TuneV1_ProbNNe;   //!
   TBranch        *b_K_MC15TuneV1_ProbNNmu;   //!
   TBranch        *b_K_MC15TuneV1_ProbNNpi;   //!
   TBranch        *b_K_MC15TuneV1_ProbNNk;   //!
   TBranch        *b_K_MC15TuneV1_ProbNNp;   //!
   TBranch        *b_K_MC15TuneV1_ProbNNghost;   //!
   TBranch        *b_K_P;   //!
   TBranch        *b_K_PT;   //!
   TBranch        *b_K_PE;   //!
   TBranch        *b_K_PX;   //!
   TBranch        *b_K_PY;   //!
   TBranch        *b_K_PZ;   //!
   TBranch        *b_K_M;   //!
   TBranch        *b_K_ID;   //!
   TBranch        *b_K_PIDe;   //!
   TBranch        *b_K_PIDmu;   //!
   TBranch        *b_K_PIDK;   //!
   TBranch        *b_K_PIDp;   //!
   TBranch        *b_K_PIDd;   //!
   TBranch        *b_K_ProbNNe;   //!
   TBranch        *b_K_ProbNNk;   //!
   TBranch        *b_K_ProbNNp;   //!
   TBranch        *b_K_ProbNNpi;   //!
   TBranch        *b_K_ProbNNmu;   //!
   TBranch        *b_K_ProbNNd;   //!
   TBranch        *b_K_ProbNNghost;   //!
   TBranch        *b_K_hasMuon;   //!
   TBranch        *b_K_isMuon;   //!
   TBranch        *b_K_hasRich;   //!
   TBranch        *b_K_UsedRichAerogel;   //!
   TBranch        *b_K_UsedRich1Gas;   //!
   TBranch        *b_K_UsedRich2Gas;   //!
   TBranch        *b_K_RichAboveElThres;   //!
   TBranch        *b_K_RichAboveMuThres;   //!
   TBranch        *b_K_RichAbovePiThres;   //!
   TBranch        *b_K_RichAboveKaThres;   //!
   TBranch        *b_K_RichAbovePrThres;   //!
   TBranch        *b_K_hasCalo;   //!
   TBranch        *b_K_L0Global_Dec;   //!
   TBranch        *b_K_L0Global_TIS;   //!
   TBranch        *b_K_L0Global_TOS;   //!
   TBranch        *b_K_Hlt1Global_Dec;   //!
   TBranch        *b_K_Hlt1Global_TIS;   //!
   TBranch        *b_K_Hlt1Global_TOS;   //!
   TBranch        *b_K_Hlt1Phys_Dec;   //!
   TBranch        *b_K_Hlt1Phys_TIS;   //!
   TBranch        *b_K_Hlt1Phys_TOS;   //!
   TBranch        *b_K_Hlt2Global_Dec;   //!
   TBranch        *b_K_Hlt2Global_TIS;   //!
   TBranch        *b_K_Hlt2Global_TOS;   //!
   TBranch        *b_K_Hlt2Phys_Dec;   //!
   TBranch        *b_K_Hlt2Phys_TIS;   //!
   TBranch        *b_K_Hlt2Phys_TOS;   //!
   TBranch        *b_K_L0MuonDecision_Dec;   //!
   TBranch        *b_K_L0MuonDecision_TIS;   //!
   TBranch        *b_K_L0MuonDecision_TOS;   //!
   TBranch        *b_K_L0DimuonDecision_Dec;   //!
   TBranch        *b_K_L0DimuonDecision_TIS;   //!
   TBranch        *b_K_L0DimuonDecision_TOS;   //!
   TBranch        *b_K_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_K_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_K_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_K_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_K_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_K_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_K_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_K_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_K_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_K_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_K_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_K_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_K_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_K_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_K_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_K_Hlt2DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_K_Hlt2DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_K_Hlt2DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_K_Hlt2DiMuonJpsi2MuMuDecision_Dec;   //!
   TBranch        *b_K_Hlt2DiMuonJpsi2MuMuDecision_TIS;   //!
   TBranch        *b_K_Hlt2DiMuonJpsi2MuMuDecision_TOS;   //!
   TBranch        *b_K_OWNPV_X;   //!
   TBranch        *b_K_OWNPV_Y;   //!
   TBranch        *b_K_OWNPV_Z;   //!
   TBranch        *b_K_OWNPV_XERR;   //!
   TBranch        *b_K_OWNPV_YERR;   //!
   TBranch        *b_K_OWNPV_ZERR;   //!
   TBranch        *b_K_OWNPV_CHI2;   //!
   TBranch        *b_K_OWNPV_NDOF;   //!
   TBranch        *b_K_OWNPV_COV_;   //!
   TBranch        *b_K_IP_OWNPV;   //!
   TBranch        *b_K_IPCHI2_OWNPV;   //!
   TBranch        *b_K_ORIVX_X;   //!
   TBranch        *b_K_ORIVX_Y;   //!
   TBranch        *b_K_ORIVX_Z;   //!
   TBranch        *b_K_ORIVX_XERR;   //!
   TBranch        *b_K_ORIVX_YERR;   //!
   TBranch        *b_K_ORIVX_ZERR;   //!
   TBranch        *b_K_ORIVX_CHI2;   //!
   TBranch        *b_K_ORIVX_NDOF;   //!
   TBranch        *b_K_ORIVX_COV_;   //!
   TBranch        *b_K_TRUEID;   //!
   TBranch        *b_K_TRUEP_E;   //!
   TBranch        *b_K_TRUEP_X;   //!
   TBranch        *b_K_TRUEP_Y;   //!
   TBranch        *b_K_TRUEP_Z;   //!
   TBranch        *b_K_TRUEPT;   //!
   TBranch        *b_K_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_K_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_K_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_K_TRUEENDVERTEX_X;   //!
   TBranch        *b_K_TRUEENDVERTEX_Y;   //!
   TBranch        *b_K_TRUEENDVERTEX_Z;   //!
   TBranch        *b_K_TRUEISSTABLE;   //!
   TBranch        *b_K_TRUETAU;   //!
   TBranch        *b_K_TRACK_Type;   //!
   TBranch        *b_K_TRACK_Key;   //!
   TBranch        *b_K_TRACK_CHI2NDOF;   //!
   TBranch        *b_K_TRACK_PCHI2;   //!
   TBranch        *b_K_TRACK_MatchCHI2;   //!
   TBranch        *b_K_TRACK_GhostProb;   //!
   TBranch        *b_K_TRACK_CloneDist;   //!
   TBranch        *b_K_TRACK_Likelihood;   //!
   TBranch        *b_Jet_P;   //!
   TBranch        *b_Jet_PT;   //!
   TBranch        *b_Jet_PE;   //!
   TBranch        *b_Jet_PX;   //!
   TBranch        *b_Jet_PY;   //!
   TBranch        *b_Jet_PZ;   //!
   TBranch        *b_Jet_MM;   //!
   TBranch        *b_Jet_MMERR;   //!
   TBranch        *b_Jet_M;   //!
   TBranch        *b_Jet_ID;   //!
   TBranch        *b_Jet_L0Global_Dec;   //!
   TBranch        *b_Jet_L0Global_TIS;   //!
   TBranch        *b_Jet_L0Global_TOS;   //!
   TBranch        *b_Jet_Hlt1Global_Dec;   //!
   TBranch        *b_Jet_Hlt1Global_TIS;   //!
   TBranch        *b_Jet_Hlt1Global_TOS;   //!
   TBranch        *b_Jet_Hlt1Phys_Dec;   //!
   TBranch        *b_Jet_Hlt1Phys_TIS;   //!
   TBranch        *b_Jet_Hlt1Phys_TOS;   //!
   TBranch        *b_Jet_Hlt2Global_Dec;   //!
   TBranch        *b_Jet_Hlt2Global_TIS;   //!
   TBranch        *b_Jet_Hlt2Global_TOS;   //!
   TBranch        *b_Jet_Hlt2Phys_Dec;   //!
   TBranch        *b_Jet_Hlt2Phys_TIS;   //!
   TBranch        *b_Jet_Hlt2Phys_TOS;   //!
   TBranch        *b_Jet_L0MuonDecision_Dec;   //!
   TBranch        *b_Jet_L0MuonDecision_TIS;   //!
   TBranch        *b_Jet_L0MuonDecision_TOS;   //!
   TBranch        *b_Jet_L0DimuonDecision_Dec;   //!
   TBranch        *b_Jet_L0DimuonDecision_TIS;   //!
   TBranch        *b_Jet_L0DimuonDecision_TOS;   //!
   TBranch        *b_Jet_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_Jet_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_Jet_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Jet_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_Jet_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_Jet_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_Jet_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_Jet_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_Jet_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_Jet_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Jet_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Jet_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Jet_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_Jet_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_Jet_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_Jet_Hlt2DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_Jet_Hlt2DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_Jet_Hlt2DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Jet_Hlt2DiMuonJpsi2MuMuDecision_Dec;   //!
   TBranch        *b_Jet_Hlt2DiMuonJpsi2MuMuDecision_TIS;   //!
   TBranch        *b_Jet_Hlt2DiMuonJpsi2MuMuDecision_TOS;   //!
   TBranch        *b_Jet_Dtr_nrecodtr;   //!
   TBranch        *b_jet_XVTX;   //!
   TBranch        *b_jet_YVTX;   //!
   TBranch        *b_jet_ZVTX;   //!
   TBranch        *b_Jet_NDtr;   //!
   TBranch        *b_Jet_Dtr_ID;   //!
   TBranch        *b_Jet_Dtr_ThreeCharge;   //!
   TBranch        *b_Jet_Dtr_IsMeson;   //!
   TBranch        *b_Jet_Dtr_IsBaryon;   //!
   TBranch        *b_Jet_Dtr_IsStrange;   //!
   TBranch        *b_Jet_Dtr_PIDe;   //!
   TBranch        *b_Jet_Dtr_PIDmu;   //!
   TBranch        *b_Jet_Dtr_PIDk;   //!
   TBranch        *b_Jet_Dtr_PIDp;   //!
   TBranch        *b_Jet_Dtr_PIDpi;   //!
   TBranch        *b_Jet_Dtr_ProbNNe;   //!
   TBranch        *b_Jet_Dtr_ProbNNmu;   //!
   TBranch        *b_Jet_Dtr_ProbNNk;   //!
   TBranch        *b_Jet_Dtr_ProbNNp;   //!
   TBranch        *b_Jet_Dtr_ProbNNpi;   //!
   TBranch        *b_Jet_Dtr_ProbNNghost;   //!
   TBranch        *b_Jet_Dtr_PX;   //!
   TBranch        *b_Jet_Dtr_PY;   //!
   TBranch        *b_Jet_Dtr_PZ;   //!
   TBranch        *b_Jet_Dtr_E;   //!
   TBranch        *b_Jet_Dtr_P;   //!
   TBranch        *b_Jet_Dtr_PT;   //!
   TBranch        *b_Jet_Dtr_M;   //!
   TBranch        *b_Jet_Dtr_PHI;   //!
   TBranch        *b_Jet_Dtr_ETA;   //!
   TBranch        *b_Jet_Dtr_XVTX;   //!
   TBranch        *b_Jet_Dtr_YVTX;   //!
   TBranch        *b_Jet_Dtr_ZVTX;   //!
   TBranch        *b_Jet_Dtr_R;   //!
   TBranch        *b_Jet_Dtr_JT;   //!
   TBranch        *b_Jet_Dtr_Z;   //!
   TBranch        *b_Jet_Dtr_TrackType;   //!
   TBranch        *b_Jet_Dtr_TrackKey;   //!
   TBranch        *b_Jet_Dtr_TrackChi2;   //!
   TBranch        *b_Jet_Dtr_TrackNDF;   //!
   TBranch        *b_Jet_Dtr_TrackPCHI2;   //!
   TBranch        *b_Jet_Dtr_PFType;   //!
   TBranch        *b_Jet_Dtr_PFDaughterType;   //!
   TBranch        *b_Jet_Dtr_PFclustype;   //!
   TBranch        *b_Jet_Dtr_PFclusE;   //!
   TBranch        *b_Jet_Dtr_TRUE_ID;   //!
   TBranch        *b_Jet_Dtr_TRUE_ThreeCharge;   //!
   TBranch        *b_Jet_Dtr_TRUE_IsMeson;   //!
   TBranch        *b_Jet_Dtr_TRUE_IsBaryon;   //!
   TBranch        *b_Jet_Dtr_TRUE_IsStrange;   //!
   TBranch        *b_Jet_Dtr_TRUE_PX;   //!
   TBranch        *b_Jet_Dtr_TRUE_PY;   //!
   TBranch        *b_Jet_Dtr_TRUE_PZ;   //!
   TBranch        *b_Jet_Dtr_TRUE_E;   //!
   TBranch        *b_Jet_Dtr_TRUE_P;   //!
   TBranch        *b_Jet_Dtr_TRUE_PT;   //!
   TBranch        *b_Jet_Dtr_TRUE_M;   //!
   TBranch        *b_Jet_Dtr_TRUE_PHI;   //!
   TBranch        *b_Jet_Dtr_TRUE_ETA;   //!
   TBranch        *b_Jet_Dtr_TRUE_XVTX;   //!
   TBranch        *b_Jet_Dtr_TRUE_YVTX;   //!
   TBranch        *b_Jet_Dtr_TRUE_ZVTX;   //!
   TBranch        *b_Jet_Eta;   //!
   TBranch        *b_Jet_Phi;   //!
   TBranch        *b_Jet_MLoKi;   //!
   TBranch        *b_Jet_MMLoKi;   //!
   TBranch        *b_Jet_NTrk;   //!
   TBranch        *b_Jet_N90;   //!
   TBranch        *b_Jet_MTF;   //!
   TBranch        *b_Jet_NSatCells;   //!
   TBranch        *b_Jet_NHasPVInfo;   //!
   TBranch        *b_Jet_JEC_Cor;   //!
   TBranch        *b_Jet_JEC_PV;   //!
   TBranch        *b_Jet_JEC_Error;   //!
   TBranch        *b_Jet_TagKey;   //!
   TBranch        *b_Jet_w;   //!
   TBranch        *b_Jet_CPF;   //!
   TBranch        *b_Jet_JetWidth;   //!
   TBranch        *b_Jet_NSatECAL;   //!
   TBranch        *b_Jet_NSatHCAL;   //!
   TBranch        *b_Jet_NIPChi2Inf4;   //!
   TBranch        *b_Jet_EfCharged;   //!
   TBranch        *b_Jet_EfChargedHadron;   //!
   TBranch        *b_Jet_EfMuon;   //!
   TBranch        *b_Jet_EfElectron;   //!
   TBranch        *b_Jet_EfNeutral;   //!
   TBranch        *b_Jet_EfPhoton;   //!
   TBranch        *b_Jet_EfPi0;   //!
   TBranch        *b_Jet_EfMPi0;   //!
   TBranch        *b_Jet_EfRPi0;   //!
   TBranch        *b_Jet_EfNHad;   //!
   TBranch        *b_Jet_EfNReco;   //!
   TBranch        *b_Jet_EfCompo;   //!
   TBranch        *b_Jet_EfV0;   //!
   TBranch        *b_Jet_EfD;   //!
   TBranch        *b_Jet_EfB;   //!
   TBranch        *b_Jet_EfBadParticle;   //!
   TBranch        *b_Jet_EfCharged0Momentum;   //!
   TBranch        *b_Jet_EfChargedInfMomentum;   //!
   TBranch        *b_Jet_EfBadPhotonMatchingT;   //!
   TBranch        *b_Jet_EfBadPhoton;   //!
   TBranch        *b_Jet_EfIsolatedPhoton;   //!
   TBranch        *b_Jet_NLongTrk;   //!
   TBranch        *b_Jet_EfLongTrk;   //!
   TBranch        *b_Jet_NDownTrk;   //!
   TBranch        *b_Jet_EfDownTrk;   //!
   TBranch        *b_Jet_NUpTrk;   //!
   TBranch        *b_Jet_EfUpTrk;   //!
   TBranch        *b_Jet_PU_NPVs;   //!
   TBranch        *b_Jet_PU_Cone06_SumPTLongTrk;   //!
   TBranch        *b_Jet_PU_Cone06_SumELongTrk;   //!
   TBranch        *b_Jet_PU_Cone06_NLongTrk;   //!
   TBranch        *b_Jet_PU_Cone06_NUpVeloTrk;   //!
   TBranch        *b_Jet_PU_Cone10_SumPTLongTrk;   //!
   TBranch        *b_Jet_PU_Cone10_SumELongTrk;   //!
   TBranch        *b_Jet_PU_Cone10_NLongTrk;   //!
   TBranch        *b_Jet_PU_Cone10_NUpVeloTrk;   //!
   TBranch        *b_Jet_PU_Cone15_SumPTLongTrk;   //!
   TBranch        *b_Jet_PU_Cone15_SumELongTrk;   //!
   TBranch        *b_Jet_PU_Cone15_NLongTrk;   //!
   TBranch        *b_Jet_PU_Cone15_NUpVeloTrk;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLT1TCK;   //!
   TBranch        *b_HLT2TCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_Polarity;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_nLongTracks;   //!
   TBranch        *b_nDownstreamTracks;   //!
   TBranch        *b_nUpstreamTracks;   //!
   TBranch        *b_nVeloTracks;   //!
   TBranch        *b_nTTracks;   //!
   TBranch        *b_nBackTracks;   //!
   TBranch        *b_nRich1Hits;   //!
   TBranch        *b_nRich2Hits;   //!
   TBranch        *b_nVeloClusters;   //!
   TBranch        *b_nITClusters;   //!
   TBranch        *b_nTTClusters;   //!
   TBranch        *b_nOTClusters;   //!
   TBranch        *b_nSPDHits;   //!
   TBranch        *b_nMuonCoordsS0;   //!
   TBranch        *b_nMuonCoordsS1;   //!
   TBranch        *b_nMuonCoordsS2;   //!
   TBranch        *b_nMuonCoordsS3;   //!
   TBranch        *b_nMuonCoordsS4;   //!
   TBranch        *b_nMuonTracks;   //!

   Bjet_BH_Variable_Tree(TTree *tree=0);
   virtual ~Bjet_BH_Variable_Tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Bjet_BH_Variable_Tree_cxx
Bjet_BH_Variable_Tree::Bjet_BH_Variable_Tree(TTree *tree) : fChain(0) 
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
      f->GetObject("Jets/DecayTree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Jets/DecayTree","");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MD_11252022_url423_0_800.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MD_11252022_url423_800_1426.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MU_11252022_url424_0_800.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MU_11252022_url424_800_1315.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MD_11252022_url425_0_800.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MD_11252022_url425_800_877.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MU_11252022_url426_0_800.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MU_11252022_url426_800_847.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MD_11252022_url427_0_800.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MD_11252022_url427_800_989.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MU_11252022_url428_0_800.root/Jets/DecayTree");
      chain->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MU_11252022_url428_800_1040.root/Jets/DecayTree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Bjet_BH_Variable_Tree::~Bjet_BH_Variable_Tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Bjet_BH_Variable_Tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Bjet_BH_Variable_Tree::LoadTree(Long64_t entry)
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

void Bjet_BH_Variable_Tree::Init(TTree *tree)
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

   fChain->SetBranchAddress("system_P", &system_P, &b_system_P);
   fChain->SetBranchAddress("system_PT", &system_PT, &b_system_PT);
   fChain->SetBranchAddress("system_PE", &system_PE, &b_system_PE);
   fChain->SetBranchAddress("system_PX", &system_PX, &b_system_PX);
   fChain->SetBranchAddress("system_PY", &system_PY, &b_system_PY);
   fChain->SetBranchAddress("system_PZ", &system_PZ, &b_system_PZ);
   fChain->SetBranchAddress("system_MM", &system_MM, &b_system_MM);
   fChain->SetBranchAddress("system_MMERR", &system_MMERR, &b_system_MMERR);
   fChain->SetBranchAddress("system_M", &system_M, &b_system_M);
   fChain->SetBranchAddress("system_ID", &system_ID, &b_system_ID);
   fChain->SetBranchAddress("system_L0Global_Dec", &system_L0Global_Dec, &b_system_L0Global_Dec);
   fChain->SetBranchAddress("system_L0Global_TIS", &system_L0Global_TIS, &b_system_L0Global_TIS);
   fChain->SetBranchAddress("system_L0Global_TOS", &system_L0Global_TOS, &b_system_L0Global_TOS);
   fChain->SetBranchAddress("system_Hlt1Global_Dec", &system_Hlt1Global_Dec, &b_system_Hlt1Global_Dec);
   fChain->SetBranchAddress("system_Hlt1Global_TIS", &system_Hlt1Global_TIS, &b_system_Hlt1Global_TIS);
   fChain->SetBranchAddress("system_Hlt1Global_TOS", &system_Hlt1Global_TOS, &b_system_Hlt1Global_TOS);
   fChain->SetBranchAddress("system_Hlt1Phys_Dec", &system_Hlt1Phys_Dec, &b_system_Hlt1Phys_Dec);
   fChain->SetBranchAddress("system_Hlt1Phys_TIS", &system_Hlt1Phys_TIS, &b_system_Hlt1Phys_TIS);
   fChain->SetBranchAddress("system_Hlt1Phys_TOS", &system_Hlt1Phys_TOS, &b_system_Hlt1Phys_TOS);
   fChain->SetBranchAddress("system_Hlt2Global_Dec", &system_Hlt2Global_Dec, &b_system_Hlt2Global_Dec);
   fChain->SetBranchAddress("system_Hlt2Global_TIS", &system_Hlt2Global_TIS, &b_system_Hlt2Global_TIS);
   fChain->SetBranchAddress("system_Hlt2Global_TOS", &system_Hlt2Global_TOS, &b_system_Hlt2Global_TOS);
   fChain->SetBranchAddress("system_Hlt2Phys_Dec", &system_Hlt2Phys_Dec, &b_system_Hlt2Phys_Dec);
   fChain->SetBranchAddress("system_Hlt2Phys_TIS", &system_Hlt2Phys_TIS, &b_system_Hlt2Phys_TIS);
   fChain->SetBranchAddress("system_Hlt2Phys_TOS", &system_Hlt2Phys_TOS, &b_system_Hlt2Phys_TOS);
   fChain->SetBranchAddress("system_L0MuonDecision_Dec", &system_L0MuonDecision_Dec, &b_system_L0MuonDecision_Dec);
   fChain->SetBranchAddress("system_L0MuonDecision_TIS", &system_L0MuonDecision_TIS, &b_system_L0MuonDecision_TIS);
   fChain->SetBranchAddress("system_L0MuonDecision_TOS", &system_L0MuonDecision_TOS, &b_system_L0MuonDecision_TOS);
   fChain->SetBranchAddress("system_L0DimuonDecision_Dec", &system_L0DimuonDecision_Dec, &b_system_L0DimuonDecision_Dec);
   fChain->SetBranchAddress("system_L0DimuonDecision_TIS", &system_L0DimuonDecision_TIS, &b_system_L0DimuonDecision_TIS);
   fChain->SetBranchAddress("system_L0DimuonDecision_TOS", &system_L0DimuonDecision_TOS, &b_system_L0DimuonDecision_TOS);
   fChain->SetBranchAddress("system_Hlt1DiMuonHighMassDecision_Dec", &system_Hlt1DiMuonHighMassDecision_Dec, &b_system_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("system_Hlt1DiMuonHighMassDecision_TIS", &system_Hlt1DiMuonHighMassDecision_TIS, &b_system_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("system_Hlt1DiMuonHighMassDecision_TOS", &system_Hlt1DiMuonHighMassDecision_TOS, &b_system_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("system_Hlt2SingleMuonDecision_Dec", &system_Hlt2SingleMuonDecision_Dec, &b_system_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("system_Hlt2SingleMuonDecision_TIS", &system_Hlt2SingleMuonDecision_TIS, &b_system_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("system_Hlt2SingleMuonDecision_TOS", &system_Hlt2SingleMuonDecision_TOS, &b_system_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("system_Hlt2SingleMuonLowPTDecision_Dec", &system_Hlt2SingleMuonLowPTDecision_Dec, &b_system_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("system_Hlt2SingleMuonLowPTDecision_TIS", &system_Hlt2SingleMuonLowPTDecision_TIS, &b_system_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("system_Hlt2SingleMuonLowPTDecision_TOS", &system_Hlt2SingleMuonLowPTDecision_TOS, &b_system_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("system_Hlt2SingleMuonHighPTDecision_Dec", &system_Hlt2SingleMuonHighPTDecision_Dec, &b_system_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("system_Hlt2SingleMuonHighPTDecision_TIS", &system_Hlt2SingleMuonHighPTDecision_TIS, &b_system_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("system_Hlt2SingleMuonHighPTDecision_TOS", &system_Hlt2SingleMuonHighPTDecision_TOS, &b_system_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("system_Hlt2DiMuonDecision_Dec", &system_Hlt2DiMuonDecision_Dec, &b_system_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("system_Hlt2DiMuonDecision_TIS", &system_Hlt2DiMuonDecision_TIS, &b_system_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("system_Hlt2DiMuonDecision_TOS", &system_Hlt2DiMuonDecision_TOS, &b_system_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("system_Hlt2DiMuonHighMassDecision_Dec", &system_Hlt2DiMuonHighMassDecision_Dec, &b_system_Hlt2DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("system_Hlt2DiMuonHighMassDecision_TIS", &system_Hlt2DiMuonHighMassDecision_TIS, &b_system_Hlt2DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("system_Hlt2DiMuonHighMassDecision_TOS", &system_Hlt2DiMuonHighMassDecision_TOS, &b_system_Hlt2DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("system_Hlt2DiMuonJpsi2MuMuDecision_Dec", &system_Hlt2DiMuonJpsi2MuMuDecision_Dec, &b_system_Hlt2DiMuonJpsi2MuMuDecision_Dec);
   fChain->SetBranchAddress("system_Hlt2DiMuonJpsi2MuMuDecision_TIS", &system_Hlt2DiMuonJpsi2MuMuDecision_TIS, &b_system_Hlt2DiMuonJpsi2MuMuDecision_TIS);
   fChain->SetBranchAddress("system_Hlt2DiMuonJpsi2MuMuDecision_TOS", &system_Hlt2DiMuonJpsi2MuMuDecision_TOS, &b_system_Hlt2DiMuonJpsi2MuMuDecision_TOS);
   fChain->SetBranchAddress("Jpsi_P", &Jpsi_P, &b_Jpsi_P);
   fChain->SetBranchAddress("Jpsi_PT", &Jpsi_PT, &b_Jpsi_PT);
   fChain->SetBranchAddress("Jpsi_PE", &Jpsi_PE, &b_Jpsi_PE);
   fChain->SetBranchAddress("Jpsi_PX", &Jpsi_PX, &b_Jpsi_PX);
   fChain->SetBranchAddress("Jpsi_PY", &Jpsi_PY, &b_Jpsi_PY);
   fChain->SetBranchAddress("Jpsi_PZ", &Jpsi_PZ, &b_Jpsi_PZ);
   fChain->SetBranchAddress("Jpsi_MM", &Jpsi_MM, &b_Jpsi_MM);
   fChain->SetBranchAddress("Jpsi_MMERR", &Jpsi_MMERR, &b_Jpsi_MMERR);
   fChain->SetBranchAddress("Jpsi_M", &Jpsi_M, &b_Jpsi_M);
   fChain->SetBranchAddress("Jpsi_ID", &Jpsi_ID, &b_Jpsi_ID);
   fChain->SetBranchAddress("Jpsi_L0Global_Dec", &Jpsi_L0Global_Dec, &b_Jpsi_L0Global_Dec);
   fChain->SetBranchAddress("Jpsi_L0Global_TIS", &Jpsi_L0Global_TIS, &b_Jpsi_L0Global_TIS);
   fChain->SetBranchAddress("Jpsi_L0Global_TOS", &Jpsi_L0Global_TOS, &b_Jpsi_L0Global_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt1Global_Dec", &Jpsi_Hlt1Global_Dec, &b_Jpsi_Hlt1Global_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt1Global_TIS", &Jpsi_Hlt1Global_TIS, &b_Jpsi_Hlt1Global_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt1Global_TOS", &Jpsi_Hlt1Global_TOS, &b_Jpsi_Hlt1Global_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt1Phys_Dec", &Jpsi_Hlt1Phys_Dec, &b_Jpsi_Hlt1Phys_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt1Phys_TIS", &Jpsi_Hlt1Phys_TIS, &b_Jpsi_Hlt1Phys_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt1Phys_TOS", &Jpsi_Hlt1Phys_TOS, &b_Jpsi_Hlt1Phys_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2Global_Dec", &Jpsi_Hlt2Global_Dec, &b_Jpsi_Hlt2Global_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2Global_TIS", &Jpsi_Hlt2Global_TIS, &b_Jpsi_Hlt2Global_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2Global_TOS", &Jpsi_Hlt2Global_TOS, &b_Jpsi_Hlt2Global_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2Phys_Dec", &Jpsi_Hlt2Phys_Dec, &b_Jpsi_Hlt2Phys_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2Phys_TIS", &Jpsi_Hlt2Phys_TIS, &b_Jpsi_Hlt2Phys_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2Phys_TOS", &Jpsi_Hlt2Phys_TOS, &b_Jpsi_Hlt2Phys_TOS);
   fChain->SetBranchAddress("Jpsi_L0MuonDecision_Dec", &Jpsi_L0MuonDecision_Dec, &b_Jpsi_L0MuonDecision_Dec);
   fChain->SetBranchAddress("Jpsi_L0MuonDecision_TIS", &Jpsi_L0MuonDecision_TIS, &b_Jpsi_L0MuonDecision_TIS);
   fChain->SetBranchAddress("Jpsi_L0MuonDecision_TOS", &Jpsi_L0MuonDecision_TOS, &b_Jpsi_L0MuonDecision_TOS);
   fChain->SetBranchAddress("Jpsi_L0DimuonDecision_Dec", &Jpsi_L0DimuonDecision_Dec, &b_Jpsi_L0DimuonDecision_Dec);
   fChain->SetBranchAddress("Jpsi_L0DimuonDecision_TIS", &Jpsi_L0DimuonDecision_TIS, &b_Jpsi_L0DimuonDecision_TIS);
   fChain->SetBranchAddress("Jpsi_L0DimuonDecision_TOS", &Jpsi_L0DimuonDecision_TOS, &b_Jpsi_L0DimuonDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_Dec", &Jpsi_Hlt1DiMuonHighMassDecision_Dec, &b_Jpsi_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TIS", &Jpsi_Hlt1DiMuonHighMassDecision_TIS, &b_Jpsi_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &Jpsi_Hlt1DiMuonHighMassDecision_TOS, &b_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonDecision_Dec", &Jpsi_Hlt2SingleMuonDecision_Dec, &b_Jpsi_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonDecision_TIS", &Jpsi_Hlt2SingleMuonDecision_TIS, &b_Jpsi_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonDecision_TOS", &Jpsi_Hlt2SingleMuonDecision_TOS, &b_Jpsi_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonLowPTDecision_Dec", &Jpsi_Hlt2SingleMuonLowPTDecision_Dec, &b_Jpsi_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonLowPTDecision_TIS", &Jpsi_Hlt2SingleMuonLowPTDecision_TIS, &b_Jpsi_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonLowPTDecision_TOS", &Jpsi_Hlt2SingleMuonLowPTDecision_TOS, &b_Jpsi_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonHighPTDecision_Dec", &Jpsi_Hlt2SingleMuonHighPTDecision_Dec, &b_Jpsi_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonHighPTDecision_TIS", &Jpsi_Hlt2SingleMuonHighPTDecision_TIS, &b_Jpsi_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2SingleMuonHighPTDecision_TOS", &Jpsi_Hlt2SingleMuonHighPTDecision_TOS, &b_Jpsi_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonDecision_Dec", &Jpsi_Hlt2DiMuonDecision_Dec, &b_Jpsi_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonDecision_TIS", &Jpsi_Hlt2DiMuonDecision_TIS, &b_Jpsi_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonDecision_TOS", &Jpsi_Hlt2DiMuonDecision_TOS, &b_Jpsi_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonHighMassDecision_Dec", &Jpsi_Hlt2DiMuonHighMassDecision_Dec, &b_Jpsi_Hlt2DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonHighMassDecision_TIS", &Jpsi_Hlt2DiMuonHighMassDecision_TIS, &b_Jpsi_Hlt2DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonHighMassDecision_TOS", &Jpsi_Hlt2DiMuonHighMassDecision_TOS, &b_Jpsi_Hlt2DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonJpsi2MuMuDecision_Dec", &Jpsi_Hlt2DiMuonJpsi2MuMuDecision_Dec, &b_Jpsi_Hlt2DiMuonJpsi2MuMuDecision_Dec);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TIS", &Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TIS, &b_Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TIS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TOS", &Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TOS, &b_Jpsi_Hlt2DiMuonJpsi2MuMuDecision_TOS);
   fChain->SetBranchAddress("mup_MC12TuneV2_ProbNNe", &mup_MC12TuneV2_ProbNNe, &b_mup_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("mup_MC12TuneV2_ProbNNmu", &mup_MC12TuneV2_ProbNNmu, &b_mup_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("mup_MC12TuneV2_ProbNNpi", &mup_MC12TuneV2_ProbNNpi, &b_mup_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("mup_MC12TuneV2_ProbNNk", &mup_MC12TuneV2_ProbNNk, &b_mup_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("mup_MC12TuneV2_ProbNNp", &mup_MC12TuneV2_ProbNNp, &b_mup_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("mup_MC12TuneV2_ProbNNghost", &mup_MC12TuneV2_ProbNNghost, &b_mup_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("mup_MC12TuneV3_ProbNNe", &mup_MC12TuneV3_ProbNNe, &b_mup_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("mup_MC12TuneV3_ProbNNmu", &mup_MC12TuneV3_ProbNNmu, &b_mup_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("mup_MC12TuneV3_ProbNNpi", &mup_MC12TuneV3_ProbNNpi, &b_mup_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("mup_MC12TuneV3_ProbNNk", &mup_MC12TuneV3_ProbNNk, &b_mup_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("mup_MC12TuneV3_ProbNNp", &mup_MC12TuneV3_ProbNNp, &b_mup_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("mup_MC12TuneV3_ProbNNghost", &mup_MC12TuneV3_ProbNNghost, &b_mup_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("mup_MC12TuneV4_ProbNNe", &mup_MC12TuneV4_ProbNNe, &b_mup_MC12TuneV4_ProbNNe);
   fChain->SetBranchAddress("mup_MC12TuneV4_ProbNNmu", &mup_MC12TuneV4_ProbNNmu, &b_mup_MC12TuneV4_ProbNNmu);
   fChain->SetBranchAddress("mup_MC12TuneV4_ProbNNpi", &mup_MC12TuneV4_ProbNNpi, &b_mup_MC12TuneV4_ProbNNpi);
   fChain->SetBranchAddress("mup_MC12TuneV4_ProbNNk", &mup_MC12TuneV4_ProbNNk, &b_mup_MC12TuneV4_ProbNNk);
   fChain->SetBranchAddress("mup_MC12TuneV4_ProbNNp", &mup_MC12TuneV4_ProbNNp, &b_mup_MC12TuneV4_ProbNNp);
   fChain->SetBranchAddress("mup_MC12TuneV4_ProbNNghost", &mup_MC12TuneV4_ProbNNghost, &b_mup_MC12TuneV4_ProbNNghost);
   fChain->SetBranchAddress("mup_MC15TuneV1_ProbNNe", &mup_MC15TuneV1_ProbNNe, &b_mup_MC15TuneV1_ProbNNe);
   fChain->SetBranchAddress("mup_MC15TuneV1_ProbNNmu", &mup_MC15TuneV1_ProbNNmu, &b_mup_MC15TuneV1_ProbNNmu);
   fChain->SetBranchAddress("mup_MC15TuneV1_ProbNNpi", &mup_MC15TuneV1_ProbNNpi, &b_mup_MC15TuneV1_ProbNNpi);
   fChain->SetBranchAddress("mup_MC15TuneV1_ProbNNk", &mup_MC15TuneV1_ProbNNk, &b_mup_MC15TuneV1_ProbNNk);
   fChain->SetBranchAddress("mup_MC15TuneV1_ProbNNp", &mup_MC15TuneV1_ProbNNp, &b_mup_MC15TuneV1_ProbNNp);
   fChain->SetBranchAddress("mup_MC15TuneV1_ProbNNghost", &mup_MC15TuneV1_ProbNNghost, &b_mup_MC15TuneV1_ProbNNghost);
   fChain->SetBranchAddress("mup_P", &mup_P, &b_mup_P);
   fChain->SetBranchAddress("mup_PT", &mup_PT, &b_mup_PT);
   fChain->SetBranchAddress("mup_PE", &mup_PE, &b_mup_PE);
   fChain->SetBranchAddress("mup_PX", &mup_PX, &b_mup_PX);
   fChain->SetBranchAddress("mup_PY", &mup_PY, &b_mup_PY);
   fChain->SetBranchAddress("mup_PZ", &mup_PZ, &b_mup_PZ);
   fChain->SetBranchAddress("mup_M", &mup_M, &b_mup_M);
   fChain->SetBranchAddress("mup_ID", &mup_ID, &b_mup_ID);
   fChain->SetBranchAddress("mup_PIDe", &mup_PIDe, &b_mup_PIDe);
   fChain->SetBranchAddress("mup_PIDmu", &mup_PIDmu, &b_mup_PIDmu);
   fChain->SetBranchAddress("mup_PIDK", &mup_PIDK, &b_mup_PIDK);
   fChain->SetBranchAddress("mup_PIDp", &mup_PIDp, &b_mup_PIDp);
   fChain->SetBranchAddress("mup_PIDd", &mup_PIDd, &b_mup_PIDd);
   fChain->SetBranchAddress("mup_ProbNNe", &mup_ProbNNe, &b_mup_ProbNNe);
   fChain->SetBranchAddress("mup_ProbNNk", &mup_ProbNNk, &b_mup_ProbNNk);
   fChain->SetBranchAddress("mup_ProbNNp", &mup_ProbNNp, &b_mup_ProbNNp);
   fChain->SetBranchAddress("mup_ProbNNpi", &mup_ProbNNpi, &b_mup_ProbNNpi);
   fChain->SetBranchAddress("mup_ProbNNmu", &mup_ProbNNmu, &b_mup_ProbNNmu);
   fChain->SetBranchAddress("mup_ProbNNd", &mup_ProbNNd, &b_mup_ProbNNd);
   fChain->SetBranchAddress("mup_ProbNNghost", &mup_ProbNNghost, &b_mup_ProbNNghost);
   fChain->SetBranchAddress("mup_hasMuon", &mup_hasMuon, &b_mup_hasMuon);
   fChain->SetBranchAddress("mup_isMuon", &mup_isMuon, &b_mup_isMuon);
   fChain->SetBranchAddress("mup_hasRich", &mup_hasRich, &b_mup_hasRich);
   fChain->SetBranchAddress("mup_UsedRichAerogel", &mup_UsedRichAerogel, &b_mup_UsedRichAerogel);
   fChain->SetBranchAddress("mup_UsedRich1Gas", &mup_UsedRich1Gas, &b_mup_UsedRich1Gas);
   fChain->SetBranchAddress("mup_UsedRich2Gas", &mup_UsedRich2Gas, &b_mup_UsedRich2Gas);
   fChain->SetBranchAddress("mup_RichAboveElThres", &mup_RichAboveElThres, &b_mup_RichAboveElThres);
   fChain->SetBranchAddress("mup_RichAboveMuThres", &mup_RichAboveMuThres, &b_mup_RichAboveMuThres);
   fChain->SetBranchAddress("mup_RichAbovePiThres", &mup_RichAbovePiThres, &b_mup_RichAbovePiThres);
   fChain->SetBranchAddress("mup_RichAboveKaThres", &mup_RichAboveKaThres, &b_mup_RichAboveKaThres);
   fChain->SetBranchAddress("mup_RichAbovePrThres", &mup_RichAbovePrThres, &b_mup_RichAbovePrThres);
   fChain->SetBranchAddress("mup_hasCalo", &mup_hasCalo, &b_mup_hasCalo);
   fChain->SetBranchAddress("mup_L0Global_Dec", &mup_L0Global_Dec, &b_mup_L0Global_Dec);
   fChain->SetBranchAddress("mup_L0Global_TIS", &mup_L0Global_TIS, &b_mup_L0Global_TIS);
   fChain->SetBranchAddress("mup_L0Global_TOS", &mup_L0Global_TOS, &b_mup_L0Global_TOS);
   fChain->SetBranchAddress("mup_Hlt1Global_Dec", &mup_Hlt1Global_Dec, &b_mup_Hlt1Global_Dec);
   fChain->SetBranchAddress("mup_Hlt1Global_TIS", &mup_Hlt1Global_TIS, &b_mup_Hlt1Global_TIS);
   fChain->SetBranchAddress("mup_Hlt1Global_TOS", &mup_Hlt1Global_TOS, &b_mup_Hlt1Global_TOS);
   fChain->SetBranchAddress("mup_Hlt1Phys_Dec", &mup_Hlt1Phys_Dec, &b_mup_Hlt1Phys_Dec);
   fChain->SetBranchAddress("mup_Hlt1Phys_TIS", &mup_Hlt1Phys_TIS, &b_mup_Hlt1Phys_TIS);
   fChain->SetBranchAddress("mup_Hlt1Phys_TOS", &mup_Hlt1Phys_TOS, &b_mup_Hlt1Phys_TOS);
   fChain->SetBranchAddress("mup_Hlt2Global_Dec", &mup_Hlt2Global_Dec, &b_mup_Hlt2Global_Dec);
   fChain->SetBranchAddress("mup_Hlt2Global_TIS", &mup_Hlt2Global_TIS, &b_mup_Hlt2Global_TIS);
   fChain->SetBranchAddress("mup_Hlt2Global_TOS", &mup_Hlt2Global_TOS, &b_mup_Hlt2Global_TOS);
   fChain->SetBranchAddress("mup_Hlt2Phys_Dec", &mup_Hlt2Phys_Dec, &b_mup_Hlt2Phys_Dec);
   fChain->SetBranchAddress("mup_Hlt2Phys_TIS", &mup_Hlt2Phys_TIS, &b_mup_Hlt2Phys_TIS);
   fChain->SetBranchAddress("mup_Hlt2Phys_TOS", &mup_Hlt2Phys_TOS, &b_mup_Hlt2Phys_TOS);
   fChain->SetBranchAddress("mup_L0MuonDecision_Dec", &mup_L0MuonDecision_Dec, &b_mup_L0MuonDecision_Dec);
   fChain->SetBranchAddress("mup_L0MuonDecision_TIS", &mup_L0MuonDecision_TIS, &b_mup_L0MuonDecision_TIS);
   fChain->SetBranchAddress("mup_L0MuonDecision_TOS", &mup_L0MuonDecision_TOS, &b_mup_L0MuonDecision_TOS);
   fChain->SetBranchAddress("mup_L0DimuonDecision_Dec", &mup_L0DimuonDecision_Dec, &b_mup_L0DimuonDecision_Dec);
   fChain->SetBranchAddress("mup_L0DimuonDecision_TIS", &mup_L0DimuonDecision_TIS, &b_mup_L0DimuonDecision_TIS);
   fChain->SetBranchAddress("mup_L0DimuonDecision_TOS", &mup_L0DimuonDecision_TOS, &b_mup_L0DimuonDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt1DiMuonHighMassDecision_Dec", &mup_Hlt1DiMuonHighMassDecision_Dec, &b_mup_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt1DiMuonHighMassDecision_TIS", &mup_Hlt1DiMuonHighMassDecision_TIS, &b_mup_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt1DiMuonHighMassDecision_TOS", &mup_Hlt1DiMuonHighMassDecision_TOS, &b_mup_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonDecision_Dec", &mup_Hlt2SingleMuonDecision_Dec, &b_mup_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonDecision_TIS", &mup_Hlt2SingleMuonDecision_TIS, &b_mup_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonDecision_TOS", &mup_Hlt2SingleMuonDecision_TOS, &b_mup_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonLowPTDecision_Dec", &mup_Hlt2SingleMuonLowPTDecision_Dec, &b_mup_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonLowPTDecision_TIS", &mup_Hlt2SingleMuonLowPTDecision_TIS, &b_mup_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonLowPTDecision_TOS", &mup_Hlt2SingleMuonLowPTDecision_TOS, &b_mup_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonHighPTDecision_Dec", &mup_Hlt2SingleMuonHighPTDecision_Dec, &b_mup_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonHighPTDecision_TIS", &mup_Hlt2SingleMuonHighPTDecision_TIS, &b_mup_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt2SingleMuonHighPTDecision_TOS", &mup_Hlt2SingleMuonHighPTDecision_TOS, &b_mup_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt2DiMuonDecision_Dec", &mup_Hlt2DiMuonDecision_Dec, &b_mup_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt2DiMuonDecision_TIS", &mup_Hlt2DiMuonDecision_TIS, &b_mup_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt2DiMuonDecision_TOS", &mup_Hlt2DiMuonDecision_TOS, &b_mup_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt2DiMuonHighMassDecision_Dec", &mup_Hlt2DiMuonHighMassDecision_Dec, &b_mup_Hlt2DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt2DiMuonHighMassDecision_TIS", &mup_Hlt2DiMuonHighMassDecision_TIS, &b_mup_Hlt2DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt2DiMuonHighMassDecision_TOS", &mup_Hlt2DiMuonHighMassDecision_TOS, &b_mup_Hlt2DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("mup_Hlt2DiMuonJpsi2MuMuDecision_Dec", &mup_Hlt2DiMuonJpsi2MuMuDecision_Dec, &b_mup_Hlt2DiMuonJpsi2MuMuDecision_Dec);
   fChain->SetBranchAddress("mup_Hlt2DiMuonJpsi2MuMuDecision_TIS", &mup_Hlt2DiMuonJpsi2MuMuDecision_TIS, &b_mup_Hlt2DiMuonJpsi2MuMuDecision_TIS);
   fChain->SetBranchAddress("mup_Hlt2DiMuonJpsi2MuMuDecision_TOS", &mup_Hlt2DiMuonJpsi2MuMuDecision_TOS, &b_mup_Hlt2DiMuonJpsi2MuMuDecision_TOS);
   fChain->SetBranchAddress("mup_OWNPV_X", &mup_OWNPV_X, &b_mup_OWNPV_X);
   fChain->SetBranchAddress("mup_OWNPV_Y", &mup_OWNPV_Y, &b_mup_OWNPV_Y);
   fChain->SetBranchAddress("mup_OWNPV_Z", &mup_OWNPV_Z, &b_mup_OWNPV_Z);
   fChain->SetBranchAddress("mup_OWNPV_XERR", &mup_OWNPV_XERR, &b_mup_OWNPV_XERR);
   fChain->SetBranchAddress("mup_OWNPV_YERR", &mup_OWNPV_YERR, &b_mup_OWNPV_YERR);
   fChain->SetBranchAddress("mup_OWNPV_ZERR", &mup_OWNPV_ZERR, &b_mup_OWNPV_ZERR);
   fChain->SetBranchAddress("mup_OWNPV_CHI2", &mup_OWNPV_CHI2, &b_mup_OWNPV_CHI2);
   fChain->SetBranchAddress("mup_OWNPV_NDOF", &mup_OWNPV_NDOF, &b_mup_OWNPV_NDOF);
   fChain->SetBranchAddress("mup_OWNPV_COV_", mup_OWNPV_COV_, &b_mup_OWNPV_COV_);
   fChain->SetBranchAddress("mup_IP_OWNPV", &mup_IP_OWNPV, &b_mup_IP_OWNPV);
   fChain->SetBranchAddress("mup_IPCHI2_OWNPV", &mup_IPCHI2_OWNPV, &b_mup_IPCHI2_OWNPV);
   fChain->SetBranchAddress("mup_ORIVX_X", &mup_ORIVX_X, &b_mup_ORIVX_X);
   fChain->SetBranchAddress("mup_ORIVX_Y", &mup_ORIVX_Y, &b_mup_ORIVX_Y);
   fChain->SetBranchAddress("mup_ORIVX_Z", &mup_ORIVX_Z, &b_mup_ORIVX_Z);
   fChain->SetBranchAddress("mup_ORIVX_XERR", &mup_ORIVX_XERR, &b_mup_ORIVX_XERR);
   fChain->SetBranchAddress("mup_ORIVX_YERR", &mup_ORIVX_YERR, &b_mup_ORIVX_YERR);
   fChain->SetBranchAddress("mup_ORIVX_ZERR", &mup_ORIVX_ZERR, &b_mup_ORIVX_ZERR);
   fChain->SetBranchAddress("mup_ORIVX_CHI2", &mup_ORIVX_CHI2, &b_mup_ORIVX_CHI2);
   fChain->SetBranchAddress("mup_ORIVX_NDOF", &mup_ORIVX_NDOF, &b_mup_ORIVX_NDOF);
   fChain->SetBranchAddress("mup_ORIVX_COV_", mup_ORIVX_COV_, &b_mup_ORIVX_COV_);
   fChain->SetBranchAddress("mup_TRUEID", &mup_TRUEID, &b_mup_TRUEID);
   fChain->SetBranchAddress("mup_TRUEP_E", &mup_TRUEP_E, &b_mup_TRUEP_E);
   fChain->SetBranchAddress("mup_TRUEP_X", &mup_TRUEP_X, &b_mup_TRUEP_X);
   fChain->SetBranchAddress("mup_TRUEP_Y", &mup_TRUEP_Y, &b_mup_TRUEP_Y);
   fChain->SetBranchAddress("mup_TRUEP_Z", &mup_TRUEP_Z, &b_mup_TRUEP_Z);
   fChain->SetBranchAddress("mup_TRUEPT", &mup_TRUEPT, &b_mup_TRUEPT);
   fChain->SetBranchAddress("mup_TRUEORIGINVERTEX_X", &mup_TRUEORIGINVERTEX_X, &b_mup_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("mup_TRUEORIGINVERTEX_Y", &mup_TRUEORIGINVERTEX_Y, &b_mup_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("mup_TRUEORIGINVERTEX_Z", &mup_TRUEORIGINVERTEX_Z, &b_mup_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("mup_TRUEENDVERTEX_X", &mup_TRUEENDVERTEX_X, &b_mup_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("mup_TRUEENDVERTEX_Y", &mup_TRUEENDVERTEX_Y, &b_mup_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("mup_TRUEENDVERTEX_Z", &mup_TRUEENDVERTEX_Z, &b_mup_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("mup_TRUEISSTABLE", &mup_TRUEISSTABLE, &b_mup_TRUEISSTABLE);
   fChain->SetBranchAddress("mup_TRUETAU", &mup_TRUETAU, &b_mup_TRUETAU);
   fChain->SetBranchAddress("mup_TRACK_Type", &mup_TRACK_Type, &b_mup_TRACK_Type);
   fChain->SetBranchAddress("mup_TRACK_Key", &mup_TRACK_Key, &b_mup_TRACK_Key);
   fChain->SetBranchAddress("mup_TRACK_CHI2NDOF", &mup_TRACK_CHI2NDOF, &b_mup_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("mup_TRACK_PCHI2", &mup_TRACK_PCHI2, &b_mup_TRACK_PCHI2);
   fChain->SetBranchAddress("mup_TRACK_MatchCHI2", &mup_TRACK_MatchCHI2, &b_mup_TRACK_MatchCHI2);
   fChain->SetBranchAddress("mup_TRACK_GhostProb", &mup_TRACK_GhostProb, &b_mup_TRACK_GhostProb);
   fChain->SetBranchAddress("mup_TRACK_CloneDist", &mup_TRACK_CloneDist, &b_mup_TRACK_CloneDist);
   fChain->SetBranchAddress("mup_TRACK_Likelihood", &mup_TRACK_Likelihood, &b_mup_TRACK_Likelihood);
   fChain->SetBranchAddress("mum_MC12TuneV2_ProbNNe", &mum_MC12TuneV2_ProbNNe, &b_mum_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("mum_MC12TuneV2_ProbNNmu", &mum_MC12TuneV2_ProbNNmu, &b_mum_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("mum_MC12TuneV2_ProbNNpi", &mum_MC12TuneV2_ProbNNpi, &b_mum_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("mum_MC12TuneV2_ProbNNk", &mum_MC12TuneV2_ProbNNk, &b_mum_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("mum_MC12TuneV2_ProbNNp", &mum_MC12TuneV2_ProbNNp, &b_mum_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("mum_MC12TuneV2_ProbNNghost", &mum_MC12TuneV2_ProbNNghost, &b_mum_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("mum_MC12TuneV3_ProbNNe", &mum_MC12TuneV3_ProbNNe, &b_mum_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("mum_MC12TuneV3_ProbNNmu", &mum_MC12TuneV3_ProbNNmu, &b_mum_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("mum_MC12TuneV3_ProbNNpi", &mum_MC12TuneV3_ProbNNpi, &b_mum_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("mum_MC12TuneV3_ProbNNk", &mum_MC12TuneV3_ProbNNk, &b_mum_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("mum_MC12TuneV3_ProbNNp", &mum_MC12TuneV3_ProbNNp, &b_mum_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("mum_MC12TuneV3_ProbNNghost", &mum_MC12TuneV3_ProbNNghost, &b_mum_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("mum_MC12TuneV4_ProbNNe", &mum_MC12TuneV4_ProbNNe, &b_mum_MC12TuneV4_ProbNNe);
   fChain->SetBranchAddress("mum_MC12TuneV4_ProbNNmu", &mum_MC12TuneV4_ProbNNmu, &b_mum_MC12TuneV4_ProbNNmu);
   fChain->SetBranchAddress("mum_MC12TuneV4_ProbNNpi", &mum_MC12TuneV4_ProbNNpi, &b_mum_MC12TuneV4_ProbNNpi);
   fChain->SetBranchAddress("mum_MC12TuneV4_ProbNNk", &mum_MC12TuneV4_ProbNNk, &b_mum_MC12TuneV4_ProbNNk);
   fChain->SetBranchAddress("mum_MC12TuneV4_ProbNNp", &mum_MC12TuneV4_ProbNNp, &b_mum_MC12TuneV4_ProbNNp);
   fChain->SetBranchAddress("mum_MC12TuneV4_ProbNNghost", &mum_MC12TuneV4_ProbNNghost, &b_mum_MC12TuneV4_ProbNNghost);
   fChain->SetBranchAddress("mum_MC15TuneV1_ProbNNe", &mum_MC15TuneV1_ProbNNe, &b_mum_MC15TuneV1_ProbNNe);
   fChain->SetBranchAddress("mum_MC15TuneV1_ProbNNmu", &mum_MC15TuneV1_ProbNNmu, &b_mum_MC15TuneV1_ProbNNmu);
   fChain->SetBranchAddress("mum_MC15TuneV1_ProbNNpi", &mum_MC15TuneV1_ProbNNpi, &b_mum_MC15TuneV1_ProbNNpi);
   fChain->SetBranchAddress("mum_MC15TuneV1_ProbNNk", &mum_MC15TuneV1_ProbNNk, &b_mum_MC15TuneV1_ProbNNk);
   fChain->SetBranchAddress("mum_MC15TuneV1_ProbNNp", &mum_MC15TuneV1_ProbNNp, &b_mum_MC15TuneV1_ProbNNp);
   fChain->SetBranchAddress("mum_MC15TuneV1_ProbNNghost", &mum_MC15TuneV1_ProbNNghost, &b_mum_MC15TuneV1_ProbNNghost);
   fChain->SetBranchAddress("mum_P", &mum_P, &b_mum_P);
   fChain->SetBranchAddress("mum_PT", &mum_PT, &b_mum_PT);
   fChain->SetBranchAddress("mum_PE", &mum_PE, &b_mum_PE);
   fChain->SetBranchAddress("mum_PX", &mum_PX, &b_mum_PX);
   fChain->SetBranchAddress("mum_PY", &mum_PY, &b_mum_PY);
   fChain->SetBranchAddress("mum_PZ", &mum_PZ, &b_mum_PZ);
   fChain->SetBranchAddress("mum_M", &mum_M, &b_mum_M);
   fChain->SetBranchAddress("mum_ID", &mum_ID, &b_mum_ID);
   fChain->SetBranchAddress("mum_PIDe", &mum_PIDe, &b_mum_PIDe);
   fChain->SetBranchAddress("mum_PIDmu", &mum_PIDmu, &b_mum_PIDmu);
   fChain->SetBranchAddress("mum_PIDK", &mum_PIDK, &b_mum_PIDK);
   fChain->SetBranchAddress("mum_PIDp", &mum_PIDp, &b_mum_PIDp);
   fChain->SetBranchAddress("mum_PIDd", &mum_PIDd, &b_mum_PIDd);
   fChain->SetBranchAddress("mum_ProbNNe", &mum_ProbNNe, &b_mum_ProbNNe);
   fChain->SetBranchAddress("mum_ProbNNk", &mum_ProbNNk, &b_mum_ProbNNk);
   fChain->SetBranchAddress("mum_ProbNNp", &mum_ProbNNp, &b_mum_ProbNNp);
   fChain->SetBranchAddress("mum_ProbNNpi", &mum_ProbNNpi, &b_mum_ProbNNpi);
   fChain->SetBranchAddress("mum_ProbNNmu", &mum_ProbNNmu, &b_mum_ProbNNmu);
   fChain->SetBranchAddress("mum_ProbNNd", &mum_ProbNNd, &b_mum_ProbNNd);
   fChain->SetBranchAddress("mum_ProbNNghost", &mum_ProbNNghost, &b_mum_ProbNNghost);
   fChain->SetBranchAddress("mum_hasMuon", &mum_hasMuon, &b_mum_hasMuon);
   fChain->SetBranchAddress("mum_isMuon", &mum_isMuon, &b_mum_isMuon);
   fChain->SetBranchAddress("mum_hasRich", &mum_hasRich, &b_mum_hasRich);
   fChain->SetBranchAddress("mum_UsedRichAerogel", &mum_UsedRichAerogel, &b_mum_UsedRichAerogel);
   fChain->SetBranchAddress("mum_UsedRich1Gas", &mum_UsedRich1Gas, &b_mum_UsedRich1Gas);
   fChain->SetBranchAddress("mum_UsedRich2Gas", &mum_UsedRich2Gas, &b_mum_UsedRich2Gas);
   fChain->SetBranchAddress("mum_RichAboveElThres", &mum_RichAboveElThres, &b_mum_RichAboveElThres);
   fChain->SetBranchAddress("mum_RichAboveMuThres", &mum_RichAboveMuThres, &b_mum_RichAboveMuThres);
   fChain->SetBranchAddress("mum_RichAbovePiThres", &mum_RichAbovePiThres, &b_mum_RichAbovePiThres);
   fChain->SetBranchAddress("mum_RichAboveKaThres", &mum_RichAboveKaThres, &b_mum_RichAboveKaThres);
   fChain->SetBranchAddress("mum_RichAbovePrThres", &mum_RichAbovePrThres, &b_mum_RichAbovePrThres);
   fChain->SetBranchAddress("mum_hasCalo", &mum_hasCalo, &b_mum_hasCalo);
   fChain->SetBranchAddress("mum_L0Global_Dec", &mum_L0Global_Dec, &b_mum_L0Global_Dec);
   fChain->SetBranchAddress("mum_L0Global_TIS", &mum_L0Global_TIS, &b_mum_L0Global_TIS);
   fChain->SetBranchAddress("mum_L0Global_TOS", &mum_L0Global_TOS, &b_mum_L0Global_TOS);
   fChain->SetBranchAddress("mum_Hlt1Global_Dec", &mum_Hlt1Global_Dec, &b_mum_Hlt1Global_Dec);
   fChain->SetBranchAddress("mum_Hlt1Global_TIS", &mum_Hlt1Global_TIS, &b_mum_Hlt1Global_TIS);
   fChain->SetBranchAddress("mum_Hlt1Global_TOS", &mum_Hlt1Global_TOS, &b_mum_Hlt1Global_TOS);
   fChain->SetBranchAddress("mum_Hlt1Phys_Dec", &mum_Hlt1Phys_Dec, &b_mum_Hlt1Phys_Dec);
   fChain->SetBranchAddress("mum_Hlt1Phys_TIS", &mum_Hlt1Phys_TIS, &b_mum_Hlt1Phys_TIS);
   fChain->SetBranchAddress("mum_Hlt1Phys_TOS", &mum_Hlt1Phys_TOS, &b_mum_Hlt1Phys_TOS);
   fChain->SetBranchAddress("mum_Hlt2Global_Dec", &mum_Hlt2Global_Dec, &b_mum_Hlt2Global_Dec);
   fChain->SetBranchAddress("mum_Hlt2Global_TIS", &mum_Hlt2Global_TIS, &b_mum_Hlt2Global_TIS);
   fChain->SetBranchAddress("mum_Hlt2Global_TOS", &mum_Hlt2Global_TOS, &b_mum_Hlt2Global_TOS);
   fChain->SetBranchAddress("mum_Hlt2Phys_Dec", &mum_Hlt2Phys_Dec, &b_mum_Hlt2Phys_Dec);
   fChain->SetBranchAddress("mum_Hlt2Phys_TIS", &mum_Hlt2Phys_TIS, &b_mum_Hlt2Phys_TIS);
   fChain->SetBranchAddress("mum_Hlt2Phys_TOS", &mum_Hlt2Phys_TOS, &b_mum_Hlt2Phys_TOS);
   fChain->SetBranchAddress("mum_L0MuonDecision_Dec", &mum_L0MuonDecision_Dec, &b_mum_L0MuonDecision_Dec);
   fChain->SetBranchAddress("mum_L0MuonDecision_TIS", &mum_L0MuonDecision_TIS, &b_mum_L0MuonDecision_TIS);
   fChain->SetBranchAddress("mum_L0MuonDecision_TOS", &mum_L0MuonDecision_TOS, &b_mum_L0MuonDecision_TOS);
   fChain->SetBranchAddress("mum_L0DimuonDecision_Dec", &mum_L0DimuonDecision_Dec, &b_mum_L0DimuonDecision_Dec);
   fChain->SetBranchAddress("mum_L0DimuonDecision_TIS", &mum_L0DimuonDecision_TIS, &b_mum_L0DimuonDecision_TIS);
   fChain->SetBranchAddress("mum_L0DimuonDecision_TOS", &mum_L0DimuonDecision_TOS, &b_mum_L0DimuonDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt1DiMuonHighMassDecision_Dec", &mum_Hlt1DiMuonHighMassDecision_Dec, &b_mum_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt1DiMuonHighMassDecision_TIS", &mum_Hlt1DiMuonHighMassDecision_TIS, &b_mum_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt1DiMuonHighMassDecision_TOS", &mum_Hlt1DiMuonHighMassDecision_TOS, &b_mum_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonDecision_Dec", &mum_Hlt2SingleMuonDecision_Dec, &b_mum_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonDecision_TIS", &mum_Hlt2SingleMuonDecision_TIS, &b_mum_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonDecision_TOS", &mum_Hlt2SingleMuonDecision_TOS, &b_mum_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonLowPTDecision_Dec", &mum_Hlt2SingleMuonLowPTDecision_Dec, &b_mum_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonLowPTDecision_TIS", &mum_Hlt2SingleMuonLowPTDecision_TIS, &b_mum_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonLowPTDecision_TOS", &mum_Hlt2SingleMuonLowPTDecision_TOS, &b_mum_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonHighPTDecision_Dec", &mum_Hlt2SingleMuonHighPTDecision_Dec, &b_mum_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonHighPTDecision_TIS", &mum_Hlt2SingleMuonHighPTDecision_TIS, &b_mum_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt2SingleMuonHighPTDecision_TOS", &mum_Hlt2SingleMuonHighPTDecision_TOS, &b_mum_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt2DiMuonDecision_Dec", &mum_Hlt2DiMuonDecision_Dec, &b_mum_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt2DiMuonDecision_TIS", &mum_Hlt2DiMuonDecision_TIS, &b_mum_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt2DiMuonDecision_TOS", &mum_Hlt2DiMuonDecision_TOS, &b_mum_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt2DiMuonHighMassDecision_Dec", &mum_Hlt2DiMuonHighMassDecision_Dec, &b_mum_Hlt2DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt2DiMuonHighMassDecision_TIS", &mum_Hlt2DiMuonHighMassDecision_TIS, &b_mum_Hlt2DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt2DiMuonHighMassDecision_TOS", &mum_Hlt2DiMuonHighMassDecision_TOS, &b_mum_Hlt2DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("mum_Hlt2DiMuonJpsi2MuMuDecision_Dec", &mum_Hlt2DiMuonJpsi2MuMuDecision_Dec, &b_mum_Hlt2DiMuonJpsi2MuMuDecision_Dec);
   fChain->SetBranchAddress("mum_Hlt2DiMuonJpsi2MuMuDecision_TIS", &mum_Hlt2DiMuonJpsi2MuMuDecision_TIS, &b_mum_Hlt2DiMuonJpsi2MuMuDecision_TIS);
   fChain->SetBranchAddress("mum_Hlt2DiMuonJpsi2MuMuDecision_TOS", &mum_Hlt2DiMuonJpsi2MuMuDecision_TOS, &b_mum_Hlt2DiMuonJpsi2MuMuDecision_TOS);
   fChain->SetBranchAddress("mum_OWNPV_X", &mum_OWNPV_X, &b_mum_OWNPV_X);
   fChain->SetBranchAddress("mum_OWNPV_Y", &mum_OWNPV_Y, &b_mum_OWNPV_Y);
   fChain->SetBranchAddress("mum_OWNPV_Z", &mum_OWNPV_Z, &b_mum_OWNPV_Z);
   fChain->SetBranchAddress("mum_OWNPV_XERR", &mum_OWNPV_XERR, &b_mum_OWNPV_XERR);
   fChain->SetBranchAddress("mum_OWNPV_YERR", &mum_OWNPV_YERR, &b_mum_OWNPV_YERR);
   fChain->SetBranchAddress("mum_OWNPV_ZERR", &mum_OWNPV_ZERR, &b_mum_OWNPV_ZERR);
   fChain->SetBranchAddress("mum_OWNPV_CHI2", &mum_OWNPV_CHI2, &b_mum_OWNPV_CHI2);
   fChain->SetBranchAddress("mum_OWNPV_NDOF", &mum_OWNPV_NDOF, &b_mum_OWNPV_NDOF);
   fChain->SetBranchAddress("mum_OWNPV_COV_", mum_OWNPV_COV_, &b_mum_OWNPV_COV_);
   fChain->SetBranchAddress("mum_IP_OWNPV", &mum_IP_OWNPV, &b_mum_IP_OWNPV);
   fChain->SetBranchAddress("mum_IPCHI2_OWNPV", &mum_IPCHI2_OWNPV, &b_mum_IPCHI2_OWNPV);
   fChain->SetBranchAddress("mum_ORIVX_X", &mum_ORIVX_X, &b_mum_ORIVX_X);
   fChain->SetBranchAddress("mum_ORIVX_Y", &mum_ORIVX_Y, &b_mum_ORIVX_Y);
   fChain->SetBranchAddress("mum_ORIVX_Z", &mum_ORIVX_Z, &b_mum_ORIVX_Z);
   fChain->SetBranchAddress("mum_ORIVX_XERR", &mum_ORIVX_XERR, &b_mum_ORIVX_XERR);
   fChain->SetBranchAddress("mum_ORIVX_YERR", &mum_ORIVX_YERR, &b_mum_ORIVX_YERR);
   fChain->SetBranchAddress("mum_ORIVX_ZERR", &mum_ORIVX_ZERR, &b_mum_ORIVX_ZERR);
   fChain->SetBranchAddress("mum_ORIVX_CHI2", &mum_ORIVX_CHI2, &b_mum_ORIVX_CHI2);
   fChain->SetBranchAddress("mum_ORIVX_NDOF", &mum_ORIVX_NDOF, &b_mum_ORIVX_NDOF);
   fChain->SetBranchAddress("mum_ORIVX_COV_", mum_ORIVX_COV_, &b_mum_ORIVX_COV_);
   fChain->SetBranchAddress("mum_TRUEID", &mum_TRUEID, &b_mum_TRUEID);
   fChain->SetBranchAddress("mum_TRUEP_E", &mum_TRUEP_E, &b_mum_TRUEP_E);
   fChain->SetBranchAddress("mum_TRUEP_X", &mum_TRUEP_X, &b_mum_TRUEP_X);
   fChain->SetBranchAddress("mum_TRUEP_Y", &mum_TRUEP_Y, &b_mum_TRUEP_Y);
   fChain->SetBranchAddress("mum_TRUEP_Z", &mum_TRUEP_Z, &b_mum_TRUEP_Z);
   fChain->SetBranchAddress("mum_TRUEPT", &mum_TRUEPT, &b_mum_TRUEPT);
   fChain->SetBranchAddress("mum_TRUEORIGINVERTEX_X", &mum_TRUEORIGINVERTEX_X, &b_mum_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("mum_TRUEORIGINVERTEX_Y", &mum_TRUEORIGINVERTEX_Y, &b_mum_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("mum_TRUEORIGINVERTEX_Z", &mum_TRUEORIGINVERTEX_Z, &b_mum_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("mum_TRUEENDVERTEX_X", &mum_TRUEENDVERTEX_X, &b_mum_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("mum_TRUEENDVERTEX_Y", &mum_TRUEENDVERTEX_Y, &b_mum_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("mum_TRUEENDVERTEX_Z", &mum_TRUEENDVERTEX_Z, &b_mum_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("mum_TRUEISSTABLE", &mum_TRUEISSTABLE, &b_mum_TRUEISSTABLE);
   fChain->SetBranchAddress("mum_TRUETAU", &mum_TRUETAU, &b_mum_TRUETAU);
   fChain->SetBranchAddress("mum_TRACK_Type", &mum_TRACK_Type, &b_mum_TRACK_Type);
   fChain->SetBranchAddress("mum_TRACK_Key", &mum_TRACK_Key, &b_mum_TRACK_Key);
   fChain->SetBranchAddress("mum_TRACK_CHI2NDOF", &mum_TRACK_CHI2NDOF, &b_mum_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("mum_TRACK_PCHI2", &mum_TRACK_PCHI2, &b_mum_TRACK_PCHI2);
   fChain->SetBranchAddress("mum_TRACK_MatchCHI2", &mum_TRACK_MatchCHI2, &b_mum_TRACK_MatchCHI2);
   fChain->SetBranchAddress("mum_TRACK_GhostProb", &mum_TRACK_GhostProb, &b_mum_TRACK_GhostProb);
   fChain->SetBranchAddress("mum_TRACK_CloneDist", &mum_TRACK_CloneDist, &b_mum_TRACK_CloneDist);
   fChain->SetBranchAddress("mum_TRACK_Likelihood", &mum_TRACK_Likelihood, &b_mum_TRACK_Likelihood);
   fChain->SetBranchAddress("K_MC12TuneV2_ProbNNe", &K_MC12TuneV2_ProbNNe, &b_K_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("K_MC12TuneV2_ProbNNmu", &K_MC12TuneV2_ProbNNmu, &b_K_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("K_MC12TuneV2_ProbNNpi", &K_MC12TuneV2_ProbNNpi, &b_K_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("K_MC12TuneV2_ProbNNk", &K_MC12TuneV2_ProbNNk, &b_K_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("K_MC12TuneV2_ProbNNp", &K_MC12TuneV2_ProbNNp, &b_K_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("K_MC12TuneV2_ProbNNghost", &K_MC12TuneV2_ProbNNghost, &b_K_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("K_MC12TuneV3_ProbNNe", &K_MC12TuneV3_ProbNNe, &b_K_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("K_MC12TuneV3_ProbNNmu", &K_MC12TuneV3_ProbNNmu, &b_K_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("K_MC12TuneV3_ProbNNpi", &K_MC12TuneV3_ProbNNpi, &b_K_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("K_MC12TuneV3_ProbNNk", &K_MC12TuneV3_ProbNNk, &b_K_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("K_MC12TuneV3_ProbNNp", &K_MC12TuneV3_ProbNNp, &b_K_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("K_MC12TuneV3_ProbNNghost", &K_MC12TuneV3_ProbNNghost, &b_K_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("K_MC12TuneV4_ProbNNe", &K_MC12TuneV4_ProbNNe, &b_K_MC12TuneV4_ProbNNe);
   fChain->SetBranchAddress("K_MC12TuneV4_ProbNNmu", &K_MC12TuneV4_ProbNNmu, &b_K_MC12TuneV4_ProbNNmu);
   fChain->SetBranchAddress("K_MC12TuneV4_ProbNNpi", &K_MC12TuneV4_ProbNNpi, &b_K_MC12TuneV4_ProbNNpi);
   fChain->SetBranchAddress("K_MC12TuneV4_ProbNNk", &K_MC12TuneV4_ProbNNk, &b_K_MC12TuneV4_ProbNNk);
   fChain->SetBranchAddress("K_MC12TuneV4_ProbNNp", &K_MC12TuneV4_ProbNNp, &b_K_MC12TuneV4_ProbNNp);
   fChain->SetBranchAddress("K_MC12TuneV4_ProbNNghost", &K_MC12TuneV4_ProbNNghost, &b_K_MC12TuneV4_ProbNNghost);
   fChain->SetBranchAddress("K_MC15TuneV1_ProbNNe", &K_MC15TuneV1_ProbNNe, &b_K_MC15TuneV1_ProbNNe);
   fChain->SetBranchAddress("K_MC15TuneV1_ProbNNmu", &K_MC15TuneV1_ProbNNmu, &b_K_MC15TuneV1_ProbNNmu);
   fChain->SetBranchAddress("K_MC15TuneV1_ProbNNpi", &K_MC15TuneV1_ProbNNpi, &b_K_MC15TuneV1_ProbNNpi);
   fChain->SetBranchAddress("K_MC15TuneV1_ProbNNk", &K_MC15TuneV1_ProbNNk, &b_K_MC15TuneV1_ProbNNk);
   fChain->SetBranchAddress("K_MC15TuneV1_ProbNNp", &K_MC15TuneV1_ProbNNp, &b_K_MC15TuneV1_ProbNNp);
   fChain->SetBranchAddress("K_MC15TuneV1_ProbNNghost", &K_MC15TuneV1_ProbNNghost, &b_K_MC15TuneV1_ProbNNghost);
   fChain->SetBranchAddress("K_P", &K_P, &b_K_P);
   fChain->SetBranchAddress("K_PT", &K_PT, &b_K_PT);
   fChain->SetBranchAddress("K_PE", &K_PE, &b_K_PE);
   fChain->SetBranchAddress("K_PX", &K_PX, &b_K_PX);
   fChain->SetBranchAddress("K_PY", &K_PY, &b_K_PY);
   fChain->SetBranchAddress("K_PZ", &K_PZ, &b_K_PZ);
   fChain->SetBranchAddress("K_M", &K_M, &b_K_M);
   fChain->SetBranchAddress("K_ID", &K_ID, &b_K_ID);
   fChain->SetBranchAddress("K_PIDe", &K_PIDe, &b_K_PIDe);
   fChain->SetBranchAddress("K_PIDmu", &K_PIDmu, &b_K_PIDmu);
   fChain->SetBranchAddress("K_PIDK", &K_PIDK, &b_K_PIDK);
   fChain->SetBranchAddress("K_PIDp", &K_PIDp, &b_K_PIDp);
   fChain->SetBranchAddress("K_PIDd", &K_PIDd, &b_K_PIDd);
   fChain->SetBranchAddress("K_ProbNNe", &K_ProbNNe, &b_K_ProbNNe);
   fChain->SetBranchAddress("K_ProbNNk", &K_ProbNNk, &b_K_ProbNNk);
   fChain->SetBranchAddress("K_ProbNNp", &K_ProbNNp, &b_K_ProbNNp);
   fChain->SetBranchAddress("K_ProbNNpi", &K_ProbNNpi, &b_K_ProbNNpi);
   fChain->SetBranchAddress("K_ProbNNmu", &K_ProbNNmu, &b_K_ProbNNmu);
   fChain->SetBranchAddress("K_ProbNNd", &K_ProbNNd, &b_K_ProbNNd);
   fChain->SetBranchAddress("K_ProbNNghost", &K_ProbNNghost, &b_K_ProbNNghost);
   fChain->SetBranchAddress("K_hasMuon", &K_hasMuon, &b_K_hasMuon);
   fChain->SetBranchAddress("K_isMuon", &K_isMuon, &b_K_isMuon);
   fChain->SetBranchAddress("K_hasRich", &K_hasRich, &b_K_hasRich);
   fChain->SetBranchAddress("K_UsedRichAerogel", &K_UsedRichAerogel, &b_K_UsedRichAerogel);
   fChain->SetBranchAddress("K_UsedRich1Gas", &K_UsedRich1Gas, &b_K_UsedRich1Gas);
   fChain->SetBranchAddress("K_UsedRich2Gas", &K_UsedRich2Gas, &b_K_UsedRich2Gas);
   fChain->SetBranchAddress("K_RichAboveElThres", &K_RichAboveElThres, &b_K_RichAboveElThres);
   fChain->SetBranchAddress("K_RichAboveMuThres", &K_RichAboveMuThres, &b_K_RichAboveMuThres);
   fChain->SetBranchAddress("K_RichAbovePiThres", &K_RichAbovePiThres, &b_K_RichAbovePiThres);
   fChain->SetBranchAddress("K_RichAboveKaThres", &K_RichAboveKaThres, &b_K_RichAboveKaThres);
   fChain->SetBranchAddress("K_RichAbovePrThres", &K_RichAbovePrThres, &b_K_RichAbovePrThres);
   fChain->SetBranchAddress("K_hasCalo", &K_hasCalo, &b_K_hasCalo);
   fChain->SetBranchAddress("K_L0Global_Dec", &K_L0Global_Dec, &b_K_L0Global_Dec);
   fChain->SetBranchAddress("K_L0Global_TIS", &K_L0Global_TIS, &b_K_L0Global_TIS);
   fChain->SetBranchAddress("K_L0Global_TOS", &K_L0Global_TOS, &b_K_L0Global_TOS);
   fChain->SetBranchAddress("K_Hlt1Global_Dec", &K_Hlt1Global_Dec, &b_K_Hlt1Global_Dec);
   fChain->SetBranchAddress("K_Hlt1Global_TIS", &K_Hlt1Global_TIS, &b_K_Hlt1Global_TIS);
   fChain->SetBranchAddress("K_Hlt1Global_TOS", &K_Hlt1Global_TOS, &b_K_Hlt1Global_TOS);
   fChain->SetBranchAddress("K_Hlt1Phys_Dec", &K_Hlt1Phys_Dec, &b_K_Hlt1Phys_Dec);
   fChain->SetBranchAddress("K_Hlt1Phys_TIS", &K_Hlt1Phys_TIS, &b_K_Hlt1Phys_TIS);
   fChain->SetBranchAddress("K_Hlt1Phys_TOS", &K_Hlt1Phys_TOS, &b_K_Hlt1Phys_TOS);
   fChain->SetBranchAddress("K_Hlt2Global_Dec", &K_Hlt2Global_Dec, &b_K_Hlt2Global_Dec);
   fChain->SetBranchAddress("K_Hlt2Global_TIS", &K_Hlt2Global_TIS, &b_K_Hlt2Global_TIS);
   fChain->SetBranchAddress("K_Hlt2Global_TOS", &K_Hlt2Global_TOS, &b_K_Hlt2Global_TOS);
   fChain->SetBranchAddress("K_Hlt2Phys_Dec", &K_Hlt2Phys_Dec, &b_K_Hlt2Phys_Dec);
   fChain->SetBranchAddress("K_Hlt2Phys_TIS", &K_Hlt2Phys_TIS, &b_K_Hlt2Phys_TIS);
   fChain->SetBranchAddress("K_Hlt2Phys_TOS", &K_Hlt2Phys_TOS, &b_K_Hlt2Phys_TOS);
   fChain->SetBranchAddress("K_L0MuonDecision_Dec", &K_L0MuonDecision_Dec, &b_K_L0MuonDecision_Dec);
   fChain->SetBranchAddress("K_L0MuonDecision_TIS", &K_L0MuonDecision_TIS, &b_K_L0MuonDecision_TIS);
   fChain->SetBranchAddress("K_L0MuonDecision_TOS", &K_L0MuonDecision_TOS, &b_K_L0MuonDecision_TOS);
   fChain->SetBranchAddress("K_L0DimuonDecision_Dec", &K_L0DimuonDecision_Dec, &b_K_L0DimuonDecision_Dec);
   fChain->SetBranchAddress("K_L0DimuonDecision_TIS", &K_L0DimuonDecision_TIS, &b_K_L0DimuonDecision_TIS);
   fChain->SetBranchAddress("K_L0DimuonDecision_TOS", &K_L0DimuonDecision_TOS, &b_K_L0DimuonDecision_TOS);
   fChain->SetBranchAddress("K_Hlt1DiMuonHighMassDecision_Dec", &K_Hlt1DiMuonHighMassDecision_Dec, &b_K_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("K_Hlt1DiMuonHighMassDecision_TIS", &K_Hlt1DiMuonHighMassDecision_TIS, &b_K_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("K_Hlt1DiMuonHighMassDecision_TOS", &K_Hlt1DiMuonHighMassDecision_TOS, &b_K_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("K_Hlt2SingleMuonDecision_Dec", &K_Hlt2SingleMuonDecision_Dec, &b_K_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("K_Hlt2SingleMuonDecision_TIS", &K_Hlt2SingleMuonDecision_TIS, &b_K_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("K_Hlt2SingleMuonDecision_TOS", &K_Hlt2SingleMuonDecision_TOS, &b_K_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("K_Hlt2SingleMuonLowPTDecision_Dec", &K_Hlt2SingleMuonLowPTDecision_Dec, &b_K_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("K_Hlt2SingleMuonLowPTDecision_TIS", &K_Hlt2SingleMuonLowPTDecision_TIS, &b_K_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("K_Hlt2SingleMuonLowPTDecision_TOS", &K_Hlt2SingleMuonLowPTDecision_TOS, &b_K_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("K_Hlt2SingleMuonHighPTDecision_Dec", &K_Hlt2SingleMuonHighPTDecision_Dec, &b_K_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("K_Hlt2SingleMuonHighPTDecision_TIS", &K_Hlt2SingleMuonHighPTDecision_TIS, &b_K_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("K_Hlt2SingleMuonHighPTDecision_TOS", &K_Hlt2SingleMuonHighPTDecision_TOS, &b_K_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("K_Hlt2DiMuonDecision_Dec", &K_Hlt2DiMuonDecision_Dec, &b_K_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("K_Hlt2DiMuonDecision_TIS", &K_Hlt2DiMuonDecision_TIS, &b_K_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("K_Hlt2DiMuonDecision_TOS", &K_Hlt2DiMuonDecision_TOS, &b_K_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("K_Hlt2DiMuonHighMassDecision_Dec", &K_Hlt2DiMuonHighMassDecision_Dec, &b_K_Hlt2DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("K_Hlt2DiMuonHighMassDecision_TIS", &K_Hlt2DiMuonHighMassDecision_TIS, &b_K_Hlt2DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("K_Hlt2DiMuonHighMassDecision_TOS", &K_Hlt2DiMuonHighMassDecision_TOS, &b_K_Hlt2DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("K_Hlt2DiMuonJpsi2MuMuDecision_Dec", &K_Hlt2DiMuonJpsi2MuMuDecision_Dec, &b_K_Hlt2DiMuonJpsi2MuMuDecision_Dec);
   fChain->SetBranchAddress("K_Hlt2DiMuonJpsi2MuMuDecision_TIS", &K_Hlt2DiMuonJpsi2MuMuDecision_TIS, &b_K_Hlt2DiMuonJpsi2MuMuDecision_TIS);
   fChain->SetBranchAddress("K_Hlt2DiMuonJpsi2MuMuDecision_TOS", &K_Hlt2DiMuonJpsi2MuMuDecision_TOS, &b_K_Hlt2DiMuonJpsi2MuMuDecision_TOS);
   fChain->SetBranchAddress("K_OWNPV_X", &K_OWNPV_X, &b_K_OWNPV_X);
   fChain->SetBranchAddress("K_OWNPV_Y", &K_OWNPV_Y, &b_K_OWNPV_Y);
   fChain->SetBranchAddress("K_OWNPV_Z", &K_OWNPV_Z, &b_K_OWNPV_Z);
   fChain->SetBranchAddress("K_OWNPV_XERR", &K_OWNPV_XERR, &b_K_OWNPV_XERR);
   fChain->SetBranchAddress("K_OWNPV_YERR", &K_OWNPV_YERR, &b_K_OWNPV_YERR);
   fChain->SetBranchAddress("K_OWNPV_ZERR", &K_OWNPV_ZERR, &b_K_OWNPV_ZERR);
   fChain->SetBranchAddress("K_OWNPV_CHI2", &K_OWNPV_CHI2, &b_K_OWNPV_CHI2);
   fChain->SetBranchAddress("K_OWNPV_NDOF", &K_OWNPV_NDOF, &b_K_OWNPV_NDOF);
   fChain->SetBranchAddress("K_OWNPV_COV_", K_OWNPV_COV_, &b_K_OWNPV_COV_);
   fChain->SetBranchAddress("K_IP_OWNPV", &K_IP_OWNPV, &b_K_IP_OWNPV);
   fChain->SetBranchAddress("K_IPCHI2_OWNPV", &K_IPCHI2_OWNPV, &b_K_IPCHI2_OWNPV);
   fChain->SetBranchAddress("K_ORIVX_X", &K_ORIVX_X, &b_K_ORIVX_X);
   fChain->SetBranchAddress("K_ORIVX_Y", &K_ORIVX_Y, &b_K_ORIVX_Y);
   fChain->SetBranchAddress("K_ORIVX_Z", &K_ORIVX_Z, &b_K_ORIVX_Z);
   fChain->SetBranchAddress("K_ORIVX_XERR", &K_ORIVX_XERR, &b_K_ORIVX_XERR);
   fChain->SetBranchAddress("K_ORIVX_YERR", &K_ORIVX_YERR, &b_K_ORIVX_YERR);
   fChain->SetBranchAddress("K_ORIVX_ZERR", &K_ORIVX_ZERR, &b_K_ORIVX_ZERR);
   fChain->SetBranchAddress("K_ORIVX_CHI2", &K_ORIVX_CHI2, &b_K_ORIVX_CHI2);
   fChain->SetBranchAddress("K_ORIVX_NDOF", &K_ORIVX_NDOF, &b_K_ORIVX_NDOF);
   fChain->SetBranchAddress("K_ORIVX_COV_", K_ORIVX_COV_, &b_K_ORIVX_COV_);
   fChain->SetBranchAddress("K_TRUEID", &K_TRUEID, &b_K_TRUEID);
   fChain->SetBranchAddress("K_TRUEP_E", &K_TRUEP_E, &b_K_TRUEP_E);
   fChain->SetBranchAddress("K_TRUEP_X", &K_TRUEP_X, &b_K_TRUEP_X);
   fChain->SetBranchAddress("K_TRUEP_Y", &K_TRUEP_Y, &b_K_TRUEP_Y);
   fChain->SetBranchAddress("K_TRUEP_Z", &K_TRUEP_Z, &b_K_TRUEP_Z);
   fChain->SetBranchAddress("K_TRUEPT", &K_TRUEPT, &b_K_TRUEPT);
   fChain->SetBranchAddress("K_TRUEORIGINVERTEX_X", &K_TRUEORIGINVERTEX_X, &b_K_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("K_TRUEORIGINVERTEX_Y", &K_TRUEORIGINVERTEX_Y, &b_K_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("K_TRUEORIGINVERTEX_Z", &K_TRUEORIGINVERTEX_Z, &b_K_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("K_TRUEENDVERTEX_X", &K_TRUEENDVERTEX_X, &b_K_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("K_TRUEENDVERTEX_Y", &K_TRUEENDVERTEX_Y, &b_K_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("K_TRUEENDVERTEX_Z", &K_TRUEENDVERTEX_Z, &b_K_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("K_TRUEISSTABLE", &K_TRUEISSTABLE, &b_K_TRUEISSTABLE);
   fChain->SetBranchAddress("K_TRUETAU", &K_TRUETAU, &b_K_TRUETAU);
   fChain->SetBranchAddress("K_TRACK_Type", &K_TRACK_Type, &b_K_TRACK_Type);
   fChain->SetBranchAddress("K_TRACK_Key", &K_TRACK_Key, &b_K_TRACK_Key);
   fChain->SetBranchAddress("K_TRACK_CHI2NDOF", &K_TRACK_CHI2NDOF, &b_K_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("K_TRACK_PCHI2", &K_TRACK_PCHI2, &b_K_TRACK_PCHI2);
   fChain->SetBranchAddress("K_TRACK_MatchCHI2", &K_TRACK_MatchCHI2, &b_K_TRACK_MatchCHI2);
   fChain->SetBranchAddress("K_TRACK_GhostProb", &K_TRACK_GhostProb, &b_K_TRACK_GhostProb);
   fChain->SetBranchAddress("K_TRACK_CloneDist", &K_TRACK_CloneDist, &b_K_TRACK_CloneDist);
   fChain->SetBranchAddress("K_TRACK_Likelihood", &K_TRACK_Likelihood, &b_K_TRACK_Likelihood);
   fChain->SetBranchAddress("Jet_P", &Jet_P, &b_Jet_P);
   fChain->SetBranchAddress("Jet_PT", &Jet_PT, &b_Jet_PT);
   fChain->SetBranchAddress("Jet_PE", &Jet_PE, &b_Jet_PE);
   fChain->SetBranchAddress("Jet_PX", &Jet_PX, &b_Jet_PX);
   fChain->SetBranchAddress("Jet_PY", &Jet_PY, &b_Jet_PY);
   fChain->SetBranchAddress("Jet_PZ", &Jet_PZ, &b_Jet_PZ);
   fChain->SetBranchAddress("Jet_MM", &Jet_MM, &b_Jet_MM);
   fChain->SetBranchAddress("Jet_MMERR", &Jet_MMERR, &b_Jet_MMERR);
   fChain->SetBranchAddress("Jet_M", &Jet_M, &b_Jet_M);
   fChain->SetBranchAddress("Jet_ID", &Jet_ID, &b_Jet_ID);
   fChain->SetBranchAddress("Jet_L0Global_Dec", &Jet_L0Global_Dec, &b_Jet_L0Global_Dec);
   fChain->SetBranchAddress("Jet_L0Global_TIS", &Jet_L0Global_TIS, &b_Jet_L0Global_TIS);
   fChain->SetBranchAddress("Jet_L0Global_TOS", &Jet_L0Global_TOS, &b_Jet_L0Global_TOS);
   fChain->SetBranchAddress("Jet_Hlt1Global_Dec", &Jet_Hlt1Global_Dec, &b_Jet_Hlt1Global_Dec);
   fChain->SetBranchAddress("Jet_Hlt1Global_TIS", &Jet_Hlt1Global_TIS, &b_Jet_Hlt1Global_TIS);
   fChain->SetBranchAddress("Jet_Hlt1Global_TOS", &Jet_Hlt1Global_TOS, &b_Jet_Hlt1Global_TOS);
   fChain->SetBranchAddress("Jet_Hlt1Phys_Dec", &Jet_Hlt1Phys_Dec, &b_Jet_Hlt1Phys_Dec);
   fChain->SetBranchAddress("Jet_Hlt1Phys_TIS", &Jet_Hlt1Phys_TIS, &b_Jet_Hlt1Phys_TIS);
   fChain->SetBranchAddress("Jet_Hlt1Phys_TOS", &Jet_Hlt1Phys_TOS, &b_Jet_Hlt1Phys_TOS);
   fChain->SetBranchAddress("Jet_Hlt2Global_Dec", &Jet_Hlt2Global_Dec, &b_Jet_Hlt2Global_Dec);
   fChain->SetBranchAddress("Jet_Hlt2Global_TIS", &Jet_Hlt2Global_TIS, &b_Jet_Hlt2Global_TIS);
   fChain->SetBranchAddress("Jet_Hlt2Global_TOS", &Jet_Hlt2Global_TOS, &b_Jet_Hlt2Global_TOS);
   fChain->SetBranchAddress("Jet_Hlt2Phys_Dec", &Jet_Hlt2Phys_Dec, &b_Jet_Hlt2Phys_Dec);
   fChain->SetBranchAddress("Jet_Hlt2Phys_TIS", &Jet_Hlt2Phys_TIS, &b_Jet_Hlt2Phys_TIS);
   fChain->SetBranchAddress("Jet_Hlt2Phys_TOS", &Jet_Hlt2Phys_TOS, &b_Jet_Hlt2Phys_TOS);
   fChain->SetBranchAddress("Jet_L0MuonDecision_Dec", &Jet_L0MuonDecision_Dec, &b_Jet_L0MuonDecision_Dec);
   fChain->SetBranchAddress("Jet_L0MuonDecision_TIS", &Jet_L0MuonDecision_TIS, &b_Jet_L0MuonDecision_TIS);
   fChain->SetBranchAddress("Jet_L0MuonDecision_TOS", &Jet_L0MuonDecision_TOS, &b_Jet_L0MuonDecision_TOS);
   fChain->SetBranchAddress("Jet_L0DimuonDecision_Dec", &Jet_L0DimuonDecision_Dec, &b_Jet_L0DimuonDecision_Dec);
   fChain->SetBranchAddress("Jet_L0DimuonDecision_TIS", &Jet_L0DimuonDecision_TIS, &b_Jet_L0DimuonDecision_TIS);
   fChain->SetBranchAddress("Jet_L0DimuonDecision_TOS", &Jet_L0DimuonDecision_TOS, &b_Jet_L0DimuonDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt1DiMuonHighMassDecision_Dec", &Jet_Hlt1DiMuonHighMassDecision_Dec, &b_Jet_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt1DiMuonHighMassDecision_TIS", &Jet_Hlt1DiMuonHighMassDecision_TIS, &b_Jet_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt1DiMuonHighMassDecision_TOS", &Jet_Hlt1DiMuonHighMassDecision_TOS, &b_Jet_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonDecision_Dec", &Jet_Hlt2SingleMuonDecision_Dec, &b_Jet_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonDecision_TIS", &Jet_Hlt2SingleMuonDecision_TIS, &b_Jet_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonDecision_TOS", &Jet_Hlt2SingleMuonDecision_TOS, &b_Jet_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonLowPTDecision_Dec", &Jet_Hlt2SingleMuonLowPTDecision_Dec, &b_Jet_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonLowPTDecision_TIS", &Jet_Hlt2SingleMuonLowPTDecision_TIS, &b_Jet_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonLowPTDecision_TOS", &Jet_Hlt2SingleMuonLowPTDecision_TOS, &b_Jet_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonHighPTDecision_Dec", &Jet_Hlt2SingleMuonHighPTDecision_Dec, &b_Jet_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonHighPTDecision_TIS", &Jet_Hlt2SingleMuonHighPTDecision_TIS, &b_Jet_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt2SingleMuonHighPTDecision_TOS", &Jet_Hlt2SingleMuonHighPTDecision_TOS, &b_Jet_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonDecision_Dec", &Jet_Hlt2DiMuonDecision_Dec, &b_Jet_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonDecision_TIS", &Jet_Hlt2DiMuonDecision_TIS, &b_Jet_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonDecision_TOS", &Jet_Hlt2DiMuonDecision_TOS, &b_Jet_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonHighMassDecision_Dec", &Jet_Hlt2DiMuonHighMassDecision_Dec, &b_Jet_Hlt2DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonHighMassDecision_TIS", &Jet_Hlt2DiMuonHighMassDecision_TIS, &b_Jet_Hlt2DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonHighMassDecision_TOS", &Jet_Hlt2DiMuonHighMassDecision_TOS, &b_Jet_Hlt2DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonJpsi2MuMuDecision_Dec", &Jet_Hlt2DiMuonJpsi2MuMuDecision_Dec, &b_Jet_Hlt2DiMuonJpsi2MuMuDecision_Dec);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonJpsi2MuMuDecision_TIS", &Jet_Hlt2DiMuonJpsi2MuMuDecision_TIS, &b_Jet_Hlt2DiMuonJpsi2MuMuDecision_TIS);
   fChain->SetBranchAddress("Jet_Hlt2DiMuonJpsi2MuMuDecision_TOS", &Jet_Hlt2DiMuonJpsi2MuMuDecision_TOS, &b_Jet_Hlt2DiMuonJpsi2MuMuDecision_TOS);
   fChain->SetBranchAddress("Jet_Dtr_nrecodtr", &Jet_Dtr_nrecodtr, &b_Jet_Dtr_nrecodtr);
   fChain->SetBranchAddress("jet_XVTX", &jet_XVTX, &b_jet_XVTX);
   fChain->SetBranchAddress("jet_YVTX", &jet_YVTX, &b_jet_YVTX);
   fChain->SetBranchAddress("jet_ZVTX", &jet_ZVTX, &b_jet_ZVTX);
   fChain->SetBranchAddress("Jet_NDtr", &Jet_NDtr, &b_Jet_NDtr);
   fChain->SetBranchAddress("Jet_Dtr_ID", Jet_Dtr_ID, &b_Jet_Dtr_ID);
   fChain->SetBranchAddress("Jet_Dtr_ThreeCharge", Jet_Dtr_ThreeCharge, &b_Jet_Dtr_ThreeCharge);
   fChain->SetBranchAddress("Jet_Dtr_IsMeson", Jet_Dtr_IsMeson, &b_Jet_Dtr_IsMeson);
   fChain->SetBranchAddress("Jet_Dtr_IsBaryon", Jet_Dtr_IsBaryon, &b_Jet_Dtr_IsBaryon);
   fChain->SetBranchAddress("Jet_Dtr_IsStrange", Jet_Dtr_IsStrange, &b_Jet_Dtr_IsStrange);
   fChain->SetBranchAddress("Jet_Dtr_PIDe", Jet_Dtr_PIDe, &b_Jet_Dtr_PIDe);
   fChain->SetBranchAddress("Jet_Dtr_PIDmu", Jet_Dtr_PIDmu, &b_Jet_Dtr_PIDmu);
   fChain->SetBranchAddress("Jet_Dtr_PIDk", Jet_Dtr_PIDk, &b_Jet_Dtr_PIDk);
   fChain->SetBranchAddress("Jet_Dtr_PIDp", Jet_Dtr_PIDp, &b_Jet_Dtr_PIDp);
   fChain->SetBranchAddress("Jet_Dtr_PIDpi", Jet_Dtr_PIDpi, &b_Jet_Dtr_PIDpi);
   fChain->SetBranchAddress("Jet_Dtr_ProbNNe", Jet_Dtr_ProbNNe, &b_Jet_Dtr_ProbNNe);
   fChain->SetBranchAddress("Jet_Dtr_ProbNNmu", Jet_Dtr_ProbNNmu, &b_Jet_Dtr_ProbNNmu);
   fChain->SetBranchAddress("Jet_Dtr_ProbNNk", Jet_Dtr_ProbNNk, &b_Jet_Dtr_ProbNNk);
   fChain->SetBranchAddress("Jet_Dtr_ProbNNp", Jet_Dtr_ProbNNp, &b_Jet_Dtr_ProbNNp);
   fChain->SetBranchAddress("Jet_Dtr_ProbNNpi", Jet_Dtr_ProbNNpi, &b_Jet_Dtr_ProbNNpi);
   fChain->SetBranchAddress("Jet_Dtr_ProbNNghost", Jet_Dtr_ProbNNghost, &b_Jet_Dtr_ProbNNghost);
   fChain->SetBranchAddress("Jet_Dtr_PX", Jet_Dtr_PX, &b_Jet_Dtr_PX);
   fChain->SetBranchAddress("Jet_Dtr_PY", Jet_Dtr_PY, &b_Jet_Dtr_PY);
   fChain->SetBranchAddress("Jet_Dtr_PZ", Jet_Dtr_PZ, &b_Jet_Dtr_PZ);
   fChain->SetBranchAddress("Jet_Dtr_E", Jet_Dtr_E, &b_Jet_Dtr_E);
   fChain->SetBranchAddress("Jet_Dtr_P", Jet_Dtr_P, &b_Jet_Dtr_P);
   fChain->SetBranchAddress("Jet_Dtr_PT", Jet_Dtr_PT, &b_Jet_Dtr_PT);
   fChain->SetBranchAddress("Jet_Dtr_M", Jet_Dtr_M, &b_Jet_Dtr_M);
   fChain->SetBranchAddress("Jet_Dtr_PHI", Jet_Dtr_PHI, &b_Jet_Dtr_PHI);
   fChain->SetBranchAddress("Jet_Dtr_ETA", Jet_Dtr_ETA, &b_Jet_Dtr_ETA);
   fChain->SetBranchAddress("Jet_Dtr_XVTX", Jet_Dtr_XVTX, &b_Jet_Dtr_XVTX);
   fChain->SetBranchAddress("Jet_Dtr_YVTX", Jet_Dtr_YVTX, &b_Jet_Dtr_YVTX);
   fChain->SetBranchAddress("Jet_Dtr_ZVTX", Jet_Dtr_ZVTX, &b_Jet_Dtr_ZVTX);
   fChain->SetBranchAddress("Jet_Dtr_R", Jet_Dtr_R, &b_Jet_Dtr_R);
   fChain->SetBranchAddress("Jet_Dtr_JT", Jet_Dtr_JT, &b_Jet_Dtr_JT);
   fChain->SetBranchAddress("Jet_Dtr_Z", Jet_Dtr_Z, &b_Jet_Dtr_Z);
   fChain->SetBranchAddress("Jet_Dtr_TrackType", Jet_Dtr_TrackType, &b_Jet_Dtr_TrackType);
   fChain->SetBranchAddress("Jet_Dtr_TrackKey", Jet_Dtr_TrackKey, &b_Jet_Dtr_TrackKey);
   fChain->SetBranchAddress("Jet_Dtr_TrackChi2", Jet_Dtr_TrackChi2, &b_Jet_Dtr_TrackChi2);
   fChain->SetBranchAddress("Jet_Dtr_TrackNDF", Jet_Dtr_TrackNDF, &b_Jet_Dtr_TrackNDF);
   fChain->SetBranchAddress("Jet_Dtr_TrackPCHI2", Jet_Dtr_TrackPCHI2, &b_Jet_Dtr_TrackPCHI2);
   fChain->SetBranchAddress("Jet_Dtr_PFType", Jet_Dtr_PFType, &b_Jet_Dtr_PFType);
   fChain->SetBranchAddress("Jet_Dtr_PFDaughterType", Jet_Dtr_PFDaughterType, &b_Jet_Dtr_PFDaughterType);
   fChain->SetBranchAddress("Jet_Dtr_PFclustype", Jet_Dtr_PFclustype, &b_Jet_Dtr_PFclustype);
   fChain->SetBranchAddress("Jet_Dtr_PFclusE", Jet_Dtr_PFclusE, &b_Jet_Dtr_PFclusE);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_ID", Jet_Dtr_TRUE_ID, &b_Jet_Dtr_TRUE_ID);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_ThreeCharge", Jet_Dtr_TRUE_ThreeCharge, &b_Jet_Dtr_TRUE_ThreeCharge);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_IsMeson", Jet_Dtr_TRUE_IsMeson, &b_Jet_Dtr_TRUE_IsMeson);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_IsBaryon", Jet_Dtr_TRUE_IsBaryon, &b_Jet_Dtr_TRUE_IsBaryon);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_IsStrange", Jet_Dtr_TRUE_IsStrange, &b_Jet_Dtr_TRUE_IsStrange);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_PX", Jet_Dtr_TRUE_PX, &b_Jet_Dtr_TRUE_PX);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_PY", Jet_Dtr_TRUE_PY, &b_Jet_Dtr_TRUE_PY);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_PZ", Jet_Dtr_TRUE_PZ, &b_Jet_Dtr_TRUE_PZ);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_E", Jet_Dtr_TRUE_E, &b_Jet_Dtr_TRUE_E);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_P", Jet_Dtr_TRUE_P, &b_Jet_Dtr_TRUE_P);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_PT", Jet_Dtr_TRUE_PT, &b_Jet_Dtr_TRUE_PT);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_M", Jet_Dtr_TRUE_M, &b_Jet_Dtr_TRUE_M);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_PHI", Jet_Dtr_TRUE_PHI, &b_Jet_Dtr_TRUE_PHI);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_ETA", Jet_Dtr_TRUE_ETA, &b_Jet_Dtr_TRUE_ETA);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_XVTX", Jet_Dtr_TRUE_XVTX, &b_Jet_Dtr_TRUE_XVTX);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_YVTX", Jet_Dtr_TRUE_YVTX, &b_Jet_Dtr_TRUE_YVTX);
   fChain->SetBranchAddress("Jet_Dtr_TRUE_ZVTX", Jet_Dtr_TRUE_ZVTX, &b_Jet_Dtr_TRUE_ZVTX);
   fChain->SetBranchAddress("Jet_Eta", &Jet_Eta, &b_Jet_Eta);
   fChain->SetBranchAddress("Jet_Phi", &Jet_Phi, &b_Jet_Phi);
   fChain->SetBranchAddress("Jet_MLoKi", &Jet_MLoKi, &b_Jet_MLoKi);
   fChain->SetBranchAddress("Jet_MMLoKi", &Jet_MMLoKi, &b_Jet_MMLoKi);
   fChain->SetBranchAddress("Jet_NTrk", &Jet_NTrk, &b_Jet_NTrk);
   fChain->SetBranchAddress("Jet_N90", &Jet_N90, &b_Jet_N90);
   fChain->SetBranchAddress("Jet_MTF", &Jet_MTF, &b_Jet_MTF);
   fChain->SetBranchAddress("Jet_NSatCells", &Jet_NSatCells, &b_Jet_NSatCells);
   fChain->SetBranchAddress("Jet_NHasPVInfo", &Jet_NHasPVInfo, &b_Jet_NHasPVInfo);
   fChain->SetBranchAddress("Jet_JEC_Cor", &Jet_JEC_Cor, &b_Jet_JEC_Cor);
   fChain->SetBranchAddress("Jet_JEC_PV", &Jet_JEC_PV, &b_Jet_JEC_PV);
   fChain->SetBranchAddress("Jet_JEC_Error", &Jet_JEC_Error, &b_Jet_JEC_Error);
   fChain->SetBranchAddress("Jet_TagKey", &Jet_TagKey, &b_Jet_TagKey);
   fChain->SetBranchAddress("Jet_w", &Jet_w, &b_Jet_w);
   fChain->SetBranchAddress("Jet_CPF", &Jet_CPF, &b_Jet_CPF);
   fChain->SetBranchAddress("Jet_JetWidth", &Jet_JetWidth, &b_Jet_JetWidth);
   fChain->SetBranchAddress("Jet_NSatECAL", &Jet_NSatECAL, &b_Jet_NSatECAL);
   fChain->SetBranchAddress("Jet_NSatHCAL", &Jet_NSatHCAL, &b_Jet_NSatHCAL);
   fChain->SetBranchAddress("Jet_NIPChi2Inf4", &Jet_NIPChi2Inf4, &b_Jet_NIPChi2Inf4);
   fChain->SetBranchAddress("Jet_EfCharged", &Jet_EfCharged, &b_Jet_EfCharged);
   fChain->SetBranchAddress("Jet_EfChargedHadron", &Jet_EfChargedHadron, &b_Jet_EfChargedHadron);
   fChain->SetBranchAddress("Jet_EfMuon", &Jet_EfMuon, &b_Jet_EfMuon);
   fChain->SetBranchAddress("Jet_EfElectron", &Jet_EfElectron, &b_Jet_EfElectron);
   fChain->SetBranchAddress("Jet_EfNeutral", &Jet_EfNeutral, &b_Jet_EfNeutral);
   fChain->SetBranchAddress("Jet_EfPhoton", &Jet_EfPhoton, &b_Jet_EfPhoton);
   fChain->SetBranchAddress("Jet_EfPi0", &Jet_EfPi0, &b_Jet_EfPi0);
   fChain->SetBranchAddress("Jet_EfMPi0", &Jet_EfMPi0, &b_Jet_EfMPi0);
   fChain->SetBranchAddress("Jet_EfRPi0", &Jet_EfRPi0, &b_Jet_EfRPi0);
   fChain->SetBranchAddress("Jet_EfNHad", &Jet_EfNHad, &b_Jet_EfNHad);
   fChain->SetBranchAddress("Jet_EfNReco", &Jet_EfNReco, &b_Jet_EfNReco);
   fChain->SetBranchAddress("Jet_EfCompo", &Jet_EfCompo, &b_Jet_EfCompo);
   fChain->SetBranchAddress("Jet_EfV0", &Jet_EfV0, &b_Jet_EfV0);
   fChain->SetBranchAddress("Jet_EfD", &Jet_EfD, &b_Jet_EfD);
   fChain->SetBranchAddress("Jet_EfB", &Jet_EfB, &b_Jet_EfB);
   fChain->SetBranchAddress("Jet_EfBadParticle", &Jet_EfBadParticle, &b_Jet_EfBadParticle);
   fChain->SetBranchAddress("Jet_EfCharged0Momentum", &Jet_EfCharged0Momentum, &b_Jet_EfCharged0Momentum);
   fChain->SetBranchAddress("Jet_EfChargedInfMomentum", &Jet_EfChargedInfMomentum, &b_Jet_EfChargedInfMomentum);
   fChain->SetBranchAddress("Jet_EfBadPhotonMatchingT", &Jet_EfBadPhotonMatchingT, &b_Jet_EfBadPhotonMatchingT);
   fChain->SetBranchAddress("Jet_EfBadPhoton", &Jet_EfBadPhoton, &b_Jet_EfBadPhoton);
   fChain->SetBranchAddress("Jet_EfIsolatedPhoton", &Jet_EfIsolatedPhoton, &b_Jet_EfIsolatedPhoton);
   fChain->SetBranchAddress("Jet_NLongTrk", &Jet_NLongTrk, &b_Jet_NLongTrk);
   fChain->SetBranchAddress("Jet_EfLongTrk", &Jet_EfLongTrk, &b_Jet_EfLongTrk);
   fChain->SetBranchAddress("Jet_NDownTrk", &Jet_NDownTrk, &b_Jet_NDownTrk);
   fChain->SetBranchAddress("Jet_EfDownTrk", &Jet_EfDownTrk, &b_Jet_EfDownTrk);
   fChain->SetBranchAddress("Jet_NUpTrk", &Jet_NUpTrk, &b_Jet_NUpTrk);
   fChain->SetBranchAddress("Jet_EfUpTrk", &Jet_EfUpTrk, &b_Jet_EfUpTrk);
   fChain->SetBranchAddress("Jet_PU_NPVs", &Jet_PU_NPVs, &b_Jet_PU_NPVs);
   fChain->SetBranchAddress("Jet_PU_Cone06_SumPTLongTrk", &Jet_PU_Cone06_SumPTLongTrk, &b_Jet_PU_Cone06_SumPTLongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone06_SumELongTrk", &Jet_PU_Cone06_SumELongTrk, &b_Jet_PU_Cone06_SumELongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone06_NLongTrk", &Jet_PU_Cone06_NLongTrk, &b_Jet_PU_Cone06_NLongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone06_NUpVeloTrk", &Jet_PU_Cone06_NUpVeloTrk, &b_Jet_PU_Cone06_NUpVeloTrk);
   fChain->SetBranchAddress("Jet_PU_Cone10_SumPTLongTrk", &Jet_PU_Cone10_SumPTLongTrk, &b_Jet_PU_Cone10_SumPTLongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone10_SumELongTrk", &Jet_PU_Cone10_SumELongTrk, &b_Jet_PU_Cone10_SumELongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone10_NLongTrk", &Jet_PU_Cone10_NLongTrk, &b_Jet_PU_Cone10_NLongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone10_NUpVeloTrk", &Jet_PU_Cone10_NUpVeloTrk, &b_Jet_PU_Cone10_NUpVeloTrk);
   fChain->SetBranchAddress("Jet_PU_Cone15_SumPTLongTrk", &Jet_PU_Cone15_SumPTLongTrk, &b_Jet_PU_Cone15_SumPTLongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone15_SumELongTrk", &Jet_PU_Cone15_SumELongTrk, &b_Jet_PU_Cone15_SumELongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone15_NLongTrk", &Jet_PU_Cone15_NLongTrk, &b_Jet_PU_Cone15_NLongTrk);
   fChain->SetBranchAddress("Jet_PU_Cone15_NUpVeloTrk", &Jet_PU_Cone15_NUpVeloTrk, &b_Jet_PU_Cone15_NUpVeloTrk);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLT1TCK", &HLT1TCK, &b_HLT1TCK);
   fChain->SetBranchAddress("HLT2TCK", &HLT2TCK, &b_HLT2TCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
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

Bool_t Bjet_BH_Variable_Tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Bjet_BH_Variable_Tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Bjet_BH_Variable_Tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Bjet_BH_Variable_Tree_cxx
