//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 25 12:58:00 2023 by ROOT version 6.24/08
// from TChain Jets/DecayTree/
//////////////////////////////////////////////////////////

#ifndef Dzeroes_Variable_Tree_h
#define Dzeroes_Variable_Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Dzeroes_Variable_Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxD0_ENDVERTEX_COV = 1;
   static constexpr Int_t kMaxD0_OWNPV_COV = 1;
   static constexpr Int_t kMaxD0_ORIVX_COV = 1;
   static constexpr Int_t kMaxK_OWNPV_COV = 1;
   static constexpr Int_t kMaxK_ORIVX_COV = 1;
   static constexpr Int_t kMaxpi_OWNPV_COV = 1;
   static constexpr Int_t kMaxpi_ORIVX_COV = 1;

   // Declaration of leaf types
   Double_t        H_10_P;
   Double_t        H_10_PT;
   Double_t        H_10_PE;
   Double_t        H_10_PX;
   Double_t        H_10_PY;
   Double_t        H_10_PZ;
   Double_t        H_10_MM;
   Double_t        H_10_MMERR;
   Double_t        H_10_M;
   Int_t           H_10_ID;
   Double_t        D0_P;
   Double_t        D0_PT;
   Double_t        D0_PE;
   Double_t        D0_PX;
   Double_t        D0_PY;
   Double_t        D0_PZ;
   Double_t        D0_MM;
   Double_t        D0_MMERR;
   Double_t        D0_M;
   Int_t           D0_ID;
   Double_t        D0_ENDVERTEX_X;
   Double_t        D0_ENDVERTEX_Y;
   Double_t        D0_ENDVERTEX_Z;
   Double_t        D0_ENDVERTEX_XERR;
   Double_t        D0_ENDVERTEX_YERR;
   Double_t        D0_ENDVERTEX_ZERR;
   Double_t        D0_ENDVERTEX_CHI2;
   Int_t           D0_ENDVERTEX_NDOF;
   Float_t         D0_ENDVERTEX_COV_[3][3];
   Double_t        D0_OWNPV_X;
   Double_t        D0_OWNPV_Y;
   Double_t        D0_OWNPV_Z;
   Double_t        D0_OWNPV_XERR;
   Double_t        D0_OWNPV_YERR;
   Double_t        D0_OWNPV_ZERR;
   Double_t        D0_OWNPV_CHI2;
   Int_t           D0_OWNPV_NDOF;
   Float_t         D0_OWNPV_COV_[3][3];
   Double_t        D0_IP_OWNPV;
   Double_t        D0_IPCHI2_OWNPV;
   Double_t        D0_FD_OWNPV;
   Double_t        D0_FDCHI2_OWNPV;
   Double_t        D0_DIRA_OWNPV;
   Double_t        D0_ORIVX_X;
   Double_t        D0_ORIVX_Y;
   Double_t        D0_ORIVX_Z;
   Double_t        D0_ORIVX_XERR;
   Double_t        D0_ORIVX_YERR;
   Double_t        D0_ORIVX_ZERR;
   Double_t        D0_ORIVX_CHI2;
   Int_t           D0_ORIVX_NDOF;
   Float_t         D0_ORIVX_COV_[3][3];
   Double_t        D0_FD_ORIVX;
   Double_t        D0_FDCHI2_ORIVX;
   Double_t        D0_DIRA_ORIVX;
   Int_t           D0_TRUEID;
   Double_t        D0_TRUEP_E;
   Double_t        D0_TRUEP_X;
   Double_t        D0_TRUEP_Y;
   Double_t        D0_TRUEP_Z;
   Double_t        D0_TRUEPT;
   Double_t        D0_TRUEORIGINVERTEX_X;
   Double_t        D0_TRUEORIGINVERTEX_Y;
   Double_t        D0_TRUEORIGINVERTEX_Z;
   Double_t        D0_TRUEENDVERTEX_X;
   Double_t        D0_TRUEENDVERTEX_Y;
   Double_t        D0_TRUEENDVERTEX_Z;
   Bool_t          D0_TRUEISSTABLE;
   Double_t        D0_TRUETAU;
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
   Double_t        pi_MC12TuneV2_ProbNNe;
   Double_t        pi_MC12TuneV2_ProbNNmu;
   Double_t        pi_MC12TuneV2_ProbNNpi;
   Double_t        pi_MC12TuneV2_ProbNNk;
   Double_t        pi_MC12TuneV2_ProbNNp;
   Double_t        pi_MC12TuneV2_ProbNNghost;
   Double_t        pi_MC12TuneV3_ProbNNe;
   Double_t        pi_MC12TuneV3_ProbNNmu;
   Double_t        pi_MC12TuneV3_ProbNNpi;
   Double_t        pi_MC12TuneV3_ProbNNk;
   Double_t        pi_MC12TuneV3_ProbNNp;
   Double_t        pi_MC12TuneV3_ProbNNghost;
   Double_t        pi_MC12TuneV4_ProbNNe;
   Double_t        pi_MC12TuneV4_ProbNNmu;
   Double_t        pi_MC12TuneV4_ProbNNpi;
   Double_t        pi_MC12TuneV4_ProbNNk;
   Double_t        pi_MC12TuneV4_ProbNNp;
   Double_t        pi_MC12TuneV4_ProbNNghost;
   Double_t        pi_MC15TuneV1_ProbNNe;
   Double_t        pi_MC15TuneV1_ProbNNmu;
   Double_t        pi_MC15TuneV1_ProbNNpi;
   Double_t        pi_MC15TuneV1_ProbNNk;
   Double_t        pi_MC15TuneV1_ProbNNp;
   Double_t        pi_MC15TuneV1_ProbNNghost;
   Double_t        pi_P;
   Double_t        pi_PT;
   Double_t        pi_PE;
   Double_t        pi_PX;
   Double_t        pi_PY;
   Double_t        pi_PZ;
   Double_t        pi_M;
   Int_t           pi_ID;
   Double_t        pi_PIDe;
   Double_t        pi_PIDmu;
   Double_t        pi_PIDK;
   Double_t        pi_PIDp;
   Double_t        pi_PIDd;
   Double_t        pi_ProbNNe;
   Double_t        pi_ProbNNk;
   Double_t        pi_ProbNNp;
   Double_t        pi_ProbNNpi;
   Double_t        pi_ProbNNmu;
   Double_t        pi_ProbNNd;
   Double_t        pi_ProbNNghost;
   Bool_t          pi_hasMuon;
   Bool_t          pi_isMuon;
   Bool_t          pi_hasRich;
   Bool_t          pi_UsedRichAerogel;
   Bool_t          pi_UsedRich1Gas;
   Bool_t          pi_UsedRich2Gas;
   Bool_t          pi_RichAboveElThres;
   Bool_t          pi_RichAboveMuThres;
   Bool_t          pi_RichAbovePiThres;
   Bool_t          pi_RichAboveKaThres;
   Bool_t          pi_RichAbovePrThres;
   Bool_t          pi_hasCalo;
   Double_t        pi_OWNPV_X;
   Double_t        pi_OWNPV_Y;
   Double_t        pi_OWNPV_Z;
   Double_t        pi_OWNPV_XERR;
   Double_t        pi_OWNPV_YERR;
   Double_t        pi_OWNPV_ZERR;
   Double_t        pi_OWNPV_CHI2;
   Int_t           pi_OWNPV_NDOF;
   Float_t         pi_OWNPV_COV_[3][3];
   Double_t        pi_IP_OWNPV;
   Double_t        pi_IPCHI2_OWNPV;
   Double_t        pi_ORIVX_X;
   Double_t        pi_ORIVX_Y;
   Double_t        pi_ORIVX_Z;
   Double_t        pi_ORIVX_XERR;
   Double_t        pi_ORIVX_YERR;
   Double_t        pi_ORIVX_ZERR;
   Double_t        pi_ORIVX_CHI2;
   Int_t           pi_ORIVX_NDOF;
   Float_t         pi_ORIVX_COV_[3][3];
   Int_t           pi_TRUEID;
   Double_t        pi_TRUEP_E;
   Double_t        pi_TRUEP_X;
   Double_t        pi_TRUEP_Y;
   Double_t        pi_TRUEP_Z;
   Double_t        pi_TRUEPT;
   Double_t        pi_TRUEORIGINVERTEX_X;
   Double_t        pi_TRUEORIGINVERTEX_Y;
   Double_t        pi_TRUEORIGINVERTEX_Z;
   Double_t        pi_TRUEENDVERTEX_X;
   Double_t        pi_TRUEENDVERTEX_Y;
   Double_t        pi_TRUEENDVERTEX_Z;
   Bool_t          pi_TRUEISSTABLE;
   Double_t        pi_TRUETAU;
   Bool_t          pi_L0Global_Dec;
   Bool_t          pi_L0Global_TIS;
   Bool_t          pi_L0Global_TOS;
   Bool_t          pi_Hlt1Global_Dec;
   Bool_t          pi_Hlt1Global_TIS;
   Bool_t          pi_Hlt1Global_TOS;
   Bool_t          pi_Hlt1Phys_Dec;
   Bool_t          pi_Hlt1Phys_TIS;
   Bool_t          pi_Hlt1Phys_TOS;
   Bool_t          pi_Hlt2Global_Dec;
   Bool_t          pi_Hlt2Global_TIS;
   Bool_t          pi_Hlt2Global_TOS;
   Bool_t          pi_Hlt2Phys_Dec;
   Bool_t          pi_Hlt2Phys_TIS;
   Bool_t          pi_Hlt2Phys_TOS;
   Bool_t          pi_L0HadronDecision_Dec;
   Bool_t          pi_L0HadronDecision_TIS;
   Bool_t          pi_L0HadronDecision_TOS;
   Bool_t          pi_Hlt1TrackMVADecision_Dec;
   Bool_t          pi_Hlt1TrackMVADecision_TIS;
   Bool_t          pi_Hlt1TrackMVADecision_TOS;
   Bool_t          pi_Hlt1TwoTrackMVADecision_Dec;
   Bool_t          pi_Hlt1TwoTrackMVADecision_TIS;
   Bool_t          pi_Hlt1TwoTrackMVADecision_TOS;
   Bool_t          pi_Hlt1TrackMVATightDecision_Dec;
   Bool_t          pi_Hlt1TrackMVATightDecision_TIS;
   Bool_t          pi_Hlt1TrackMVATightDecision_TOS;
   Bool_t          pi_Hlt1TwoTrackMVATightDecision_Dec;
   Bool_t          pi_Hlt1TwoTrackMVATightDecision_TIS;
   Bool_t          pi_Hlt1TwoTrackMVATightDecision_TOS;
   Bool_t          pi_Hlt2Topo2BodyDecision_Dec;
   Bool_t          pi_Hlt2Topo2BodyDecision_TIS;
   Bool_t          pi_Hlt2Topo2BodyDecision_TOS;
   Bool_t          pi_Hlt2Topo3BodyDecision_Dec;
   Bool_t          pi_Hlt2Topo3BodyDecision_TIS;
   Bool_t          pi_Hlt2Topo3BodyDecision_TOS;
   Bool_t          pi_Hlt2Topo4BodyDecision_Dec;
   Bool_t          pi_Hlt2Topo4BodyDecision_TIS;
   Bool_t          pi_Hlt2Topo4BodyDecision_TOS;
   Int_t           pi_TRACK_Type;
   Int_t           pi_TRACK_Key;
   Double_t        pi_TRACK_CHI2NDOF;
   Double_t        pi_TRACK_PCHI2;
   Double_t        pi_TRACK_MatchCHI2;
   Double_t        pi_TRACK_GhostProb;
   Double_t        pi_TRACK_CloneDist;
   Double_t        pi_TRACK_Likelihood;
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
   TBranch        *b_H_10_P;   //!
   TBranch        *b_H_10_PT;   //!
   TBranch        *b_H_10_PE;   //!
   TBranch        *b_H_10_PX;   //!
   TBranch        *b_H_10_PY;   //!
   TBranch        *b_H_10_PZ;   //!
   TBranch        *b_H_10_MM;   //!
   TBranch        *b_H_10_MMERR;   //!
   TBranch        *b_H_10_M;   //!
   TBranch        *b_H_10_ID;   //!
   TBranch        *b_D0_P;   //!
   TBranch        *b_D0_PT;   //!
   TBranch        *b_D0_PE;   //!
   TBranch        *b_D0_PX;   //!
   TBranch        *b_D0_PY;   //!
   TBranch        *b_D0_PZ;   //!
   TBranch        *b_D0_MM;   //!
   TBranch        *b_D0_MMERR;   //!
   TBranch        *b_D0_M;   //!
   TBranch        *b_D0_ID;   //!
   TBranch        *b_D0_ENDVERTEX_X;   //!
   TBranch        *b_D0_ENDVERTEX_Y;   //!
   TBranch        *b_D0_ENDVERTEX_Z;   //!
   TBranch        *b_D0_ENDVERTEX_XERR;   //!
   TBranch        *b_D0_ENDVERTEX_YERR;   //!
   TBranch        *b_D0_ENDVERTEX_ZERR;   //!
   TBranch        *b_D0_ENDVERTEX_CHI2;   //!
   TBranch        *b_D0_ENDVERTEX_NDOF;   //!
   TBranch        *b_D0_ENDVERTEX_COV_;   //!
   TBranch        *b_D0_OWNPV_X;   //!
   TBranch        *b_D0_OWNPV_Y;   //!
   TBranch        *b_D0_OWNPV_Z;   //!
   TBranch        *b_D0_OWNPV_XERR;   //!
   TBranch        *b_D0_OWNPV_YERR;   //!
   TBranch        *b_D0_OWNPV_ZERR;   //!
   TBranch        *b_D0_OWNPV_CHI2;   //!
   TBranch        *b_D0_OWNPV_NDOF;   //!
   TBranch        *b_D0_OWNPV_COV_;   //!
   TBranch        *b_D0_IP_OWNPV;   //!
   TBranch        *b_D0_IPCHI2_OWNPV;   //!
   TBranch        *b_D0_FD_OWNPV;   //!
   TBranch        *b_D0_FDCHI2_OWNPV;   //!
   TBranch        *b_D0_DIRA_OWNPV;   //!
   TBranch        *b_D0_ORIVX_X;   //!
   TBranch        *b_D0_ORIVX_Y;   //!
   TBranch        *b_D0_ORIVX_Z;   //!
   TBranch        *b_D0_ORIVX_XERR;   //!
   TBranch        *b_D0_ORIVX_YERR;   //!
   TBranch        *b_D0_ORIVX_ZERR;   //!
   TBranch        *b_D0_ORIVX_CHI2;   //!
   TBranch        *b_D0_ORIVX_NDOF;   //!
   TBranch        *b_D0_ORIVX_COV_;   //!
   TBranch        *b_D0_FD_ORIVX;   //!
   TBranch        *b_D0_FDCHI2_ORIVX;   //!
   TBranch        *b_D0_DIRA_ORIVX;   //!
   TBranch        *b_D0_TRUEID;   //!
   TBranch        *b_D0_TRUEP_E;   //!
   TBranch        *b_D0_TRUEP_X;   //!
   TBranch        *b_D0_TRUEP_Y;   //!
   TBranch        *b_D0_TRUEP_Z;   //!
   TBranch        *b_D0_TRUEPT;   //!
   TBranch        *b_D0_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_D0_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_D0_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_D0_TRUEENDVERTEX_X;   //!
   TBranch        *b_D0_TRUEENDVERTEX_Y;   //!
   TBranch        *b_D0_TRUEENDVERTEX_Z;   //!
   TBranch        *b_D0_TRUEISSTABLE;   //!
   TBranch        *b_D0_TRUETAU;   //!
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
   TBranch        *b_pi_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_pi_MC12TuneV4_ProbNNe;   //!
   TBranch        *b_pi_MC12TuneV4_ProbNNmu;   //!
   TBranch        *b_pi_MC12TuneV4_ProbNNpi;   //!
   TBranch        *b_pi_MC12TuneV4_ProbNNk;   //!
   TBranch        *b_pi_MC12TuneV4_ProbNNp;   //!
   TBranch        *b_pi_MC12TuneV4_ProbNNghost;   //!
   TBranch        *b_pi_MC15TuneV1_ProbNNe;   //!
   TBranch        *b_pi_MC15TuneV1_ProbNNmu;   //!
   TBranch        *b_pi_MC15TuneV1_ProbNNpi;   //!
   TBranch        *b_pi_MC15TuneV1_ProbNNk;   //!
   TBranch        *b_pi_MC15TuneV1_ProbNNp;   //!
   TBranch        *b_pi_MC15TuneV1_ProbNNghost;   //!
   TBranch        *b_pi_P;   //!
   TBranch        *b_pi_PT;   //!
   TBranch        *b_pi_PE;   //!
   TBranch        *b_pi_PX;   //!
   TBranch        *b_pi_PY;   //!
   TBranch        *b_pi_PZ;   //!
   TBranch        *b_pi_M;   //!
   TBranch        *b_pi_ID;   //!
   TBranch        *b_pi_PIDe;   //!
   TBranch        *b_pi_PIDmu;   //!
   TBranch        *b_pi_PIDK;   //!
   TBranch        *b_pi_PIDp;   //!
   TBranch        *b_pi_PIDd;   //!
   TBranch        *b_pi_ProbNNe;   //!
   TBranch        *b_pi_ProbNNk;   //!
   TBranch        *b_pi_ProbNNp;   //!
   TBranch        *b_pi_ProbNNpi;   //!
   TBranch        *b_pi_ProbNNmu;   //!
   TBranch        *b_pi_ProbNNd;   //!
   TBranch        *b_pi_ProbNNghost;   //!
   TBranch        *b_pi_hasMuon;   //!
   TBranch        *b_pi_isMuon;   //!
   TBranch        *b_pi_hasRich;   //!
   TBranch        *b_pi_UsedRichAerogel;   //!
   TBranch        *b_pi_UsedRich1Gas;   //!
   TBranch        *b_pi_UsedRich2Gas;   //!
   TBranch        *b_pi_RichAboveElThres;   //!
   TBranch        *b_pi_RichAboveMuThres;   //!
   TBranch        *b_pi_RichAbovePiThres;   //!
   TBranch        *b_pi_RichAboveKaThres;   //!
   TBranch        *b_pi_RichAbovePrThres;   //!
   TBranch        *b_pi_hasCalo;   //!
   TBranch        *b_pi_OWNPV_X;   //!
   TBranch        *b_pi_OWNPV_Y;   //!
   TBranch        *b_pi_OWNPV_Z;   //!
   TBranch        *b_pi_OWNPV_XERR;   //!
   TBranch        *b_pi_OWNPV_YERR;   //!
   TBranch        *b_pi_OWNPV_ZERR;   //!
   TBranch        *b_pi_OWNPV_CHI2;   //!
   TBranch        *b_pi_OWNPV_NDOF;   //!
   TBranch        *b_pi_OWNPV_COV_;   //!
   TBranch        *b_pi_IP_OWNPV;   //!
   TBranch        *b_pi_IPCHI2_OWNPV;   //!
   TBranch        *b_pi_ORIVX_X;   //!
   TBranch        *b_pi_ORIVX_Y;   //!
   TBranch        *b_pi_ORIVX_Z;   //!
   TBranch        *b_pi_ORIVX_XERR;   //!
   TBranch        *b_pi_ORIVX_YERR;   //!
   TBranch        *b_pi_ORIVX_ZERR;   //!
   TBranch        *b_pi_ORIVX_CHI2;   //!
   TBranch        *b_pi_ORIVX_NDOF;   //!
   TBranch        *b_pi_ORIVX_COV_;   //!
   TBranch        *b_pi_TRUEID;   //!
   TBranch        *b_pi_TRUEP_E;   //!
   TBranch        *b_pi_TRUEP_X;   //!
   TBranch        *b_pi_TRUEP_Y;   //!
   TBranch        *b_pi_TRUEP_Z;   //!
   TBranch        *b_pi_TRUEPT;   //!
   TBranch        *b_pi_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_pi_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_pi_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_pi_TRUEENDVERTEX_X;   //!
   TBranch        *b_pi_TRUEENDVERTEX_Y;   //!
   TBranch        *b_pi_TRUEENDVERTEX_Z;   //!
   TBranch        *b_pi_TRUEISSTABLE;   //!
   TBranch        *b_pi_TRUETAU;   //!
   TBranch        *b_pi_L0Global_Dec;   //!
   TBranch        *b_pi_L0Global_TIS;   //!
   TBranch        *b_pi_L0Global_TOS;   //!
   TBranch        *b_pi_Hlt1Global_Dec;   //!
   TBranch        *b_pi_Hlt1Global_TIS;   //!
   TBranch        *b_pi_Hlt1Global_TOS;   //!
   TBranch        *b_pi_Hlt1Phys_Dec;   //!
   TBranch        *b_pi_Hlt1Phys_TIS;   //!
   TBranch        *b_pi_Hlt1Phys_TOS;   //!
   TBranch        *b_pi_Hlt2Global_Dec;   //!
   TBranch        *b_pi_Hlt2Global_TIS;   //!
   TBranch        *b_pi_Hlt2Global_TOS;   //!
   TBranch        *b_pi_Hlt2Phys_Dec;   //!
   TBranch        *b_pi_Hlt2Phys_TIS;   //!
   TBranch        *b_pi_Hlt2Phys_TOS;   //!
   TBranch        *b_pi_L0HadronDecision_Dec;   //!
   TBranch        *b_pi_L0HadronDecision_TIS;   //!
   TBranch        *b_pi_L0HadronDecision_TOS;   //!
   TBranch        *b_pi_Hlt1TrackMVADecision_Dec;   //!
   TBranch        *b_pi_Hlt1TrackMVADecision_TIS;   //!
   TBranch        *b_pi_Hlt1TrackMVADecision_TOS;   //!
   TBranch        *b_pi_Hlt1TwoTrackMVADecision_Dec;   //!
   TBranch        *b_pi_Hlt1TwoTrackMVADecision_TIS;   //!
   TBranch        *b_pi_Hlt1TwoTrackMVADecision_TOS;   //!
   TBranch        *b_pi_Hlt1TrackMVATightDecision_Dec;   //!
   TBranch        *b_pi_Hlt1TrackMVATightDecision_TIS;   //!
   TBranch        *b_pi_Hlt1TrackMVATightDecision_TOS;   //!
   TBranch        *b_pi_Hlt1TwoTrackMVATightDecision_Dec;   //!
   TBranch        *b_pi_Hlt1TwoTrackMVATightDecision_TIS;   //!
   TBranch        *b_pi_Hlt1TwoTrackMVATightDecision_TOS;   //!
   TBranch        *b_pi_Hlt2Topo2BodyDecision_Dec;   //!
   TBranch        *b_pi_Hlt2Topo2BodyDecision_TIS;   //!
   TBranch        *b_pi_Hlt2Topo2BodyDecision_TOS;   //!
   TBranch        *b_pi_Hlt2Topo3BodyDecision_Dec;   //!
   TBranch        *b_pi_Hlt2Topo3BodyDecision_TIS;   //!
   TBranch        *b_pi_Hlt2Topo3BodyDecision_TOS;   //!
   TBranch        *b_pi_Hlt2Topo4BodyDecision_Dec;   //!
   TBranch        *b_pi_Hlt2Topo4BodyDecision_TIS;   //!
   TBranch        *b_pi_Hlt2Topo4BodyDecision_TOS;   //!
   TBranch        *b_pi_TRACK_Type;   //!
   TBranch        *b_pi_TRACK_Key;   //!
   TBranch        *b_pi_TRACK_CHI2NDOF;   //!
   TBranch        *b_pi_TRACK_PCHI2;   //!
   TBranch        *b_pi_TRACK_MatchCHI2;   //!
   TBranch        *b_pi_TRACK_GhostProb;   //!
   TBranch        *b_pi_TRACK_CloneDist;   //!
   TBranch        *b_pi_TRACK_Likelihood;   //!
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

   Dzeroes_Variable_Tree(TTree *tree=0);
   virtual ~Dzeroes_Variable_Tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Dzeroes_Variable_Tree_cxx
Dzeroes_Variable_Tree::Dzeroes_Variable_Tree(TTree *tree) : fChain(0) 
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
      chain->Add("Djet_2016_MD_09082022_url327_0_535.root/Jets/DecayTree");
      chain->Add("Djet_2016_MU_09082022_url328_0_452.root/Jets/DecayTree");
      chain->Add("Djet_2017_MD_09082022_url329_0_345.root/Jets/DecayTree");
      chain->Add("Djet_2017_MU_09082022_url330_0_327.root/Jets/DecayTree");
      chain->Add("Djet_2018_MD_09082022_url331_0_372.root/Jets/DecayTree");
      chain->Add("Djet_2018_MU_09082022_url332_0_392.root/Jets/DecayTree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Dzeroes_Variable_Tree::~Dzeroes_Variable_Tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Dzeroes_Variable_Tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Dzeroes_Variable_Tree::LoadTree(Long64_t entry)
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

void Dzeroes_Variable_Tree::Init(TTree *tree)
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

   fChain->SetBranchAddress("H_10_P", &H_10_P, &b_H_10_P);
   fChain->SetBranchAddress("H_10_PT", &H_10_PT, &b_H_10_PT);
   fChain->SetBranchAddress("H_10_PE", &H_10_PE, &b_H_10_PE);
   fChain->SetBranchAddress("H_10_PX", &H_10_PX, &b_H_10_PX);
   fChain->SetBranchAddress("H_10_PY", &H_10_PY, &b_H_10_PY);
   fChain->SetBranchAddress("H_10_PZ", &H_10_PZ, &b_H_10_PZ);
   fChain->SetBranchAddress("H_10_MM", &H_10_MM, &b_H_10_MM);
   fChain->SetBranchAddress("H_10_MMERR", &H_10_MMERR, &b_H_10_MMERR);
   fChain->SetBranchAddress("H_10_M", &H_10_M, &b_H_10_M);
   fChain->SetBranchAddress("H_10_ID", &H_10_ID, &b_H_10_ID);
   fChain->SetBranchAddress("D0_P", &D0_P, &b_D0_P);
   fChain->SetBranchAddress("D0_PT", &D0_PT, &b_D0_PT);
   fChain->SetBranchAddress("D0_PE", &D0_PE, &b_D0_PE);
   fChain->SetBranchAddress("D0_PX", &D0_PX, &b_D0_PX);
   fChain->SetBranchAddress("D0_PY", &D0_PY, &b_D0_PY);
   fChain->SetBranchAddress("D0_PZ", &D0_PZ, &b_D0_PZ);
   fChain->SetBranchAddress("D0_MM", &D0_MM, &b_D0_MM);
   fChain->SetBranchAddress("D0_MMERR", &D0_MMERR, &b_D0_MMERR);
   fChain->SetBranchAddress("D0_M", &D0_M, &b_D0_M);
   fChain->SetBranchAddress("D0_ID", &D0_ID, &b_D0_ID);
   fChain->SetBranchAddress("D0_ENDVERTEX_X", &D0_ENDVERTEX_X, &b_D0_ENDVERTEX_X);
   fChain->SetBranchAddress("D0_ENDVERTEX_Y", &D0_ENDVERTEX_Y, &b_D0_ENDVERTEX_Y);
   fChain->SetBranchAddress("D0_ENDVERTEX_Z", &D0_ENDVERTEX_Z, &b_D0_ENDVERTEX_Z);
   fChain->SetBranchAddress("D0_ENDVERTEX_XERR", &D0_ENDVERTEX_XERR, &b_D0_ENDVERTEX_XERR);
   fChain->SetBranchAddress("D0_ENDVERTEX_YERR", &D0_ENDVERTEX_YERR, &b_D0_ENDVERTEX_YERR);
   fChain->SetBranchAddress("D0_ENDVERTEX_ZERR", &D0_ENDVERTEX_ZERR, &b_D0_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("D0_ENDVERTEX_CHI2", &D0_ENDVERTEX_CHI2, &b_D0_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("D0_ENDVERTEX_NDOF", &D0_ENDVERTEX_NDOF, &b_D0_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("D0_ENDVERTEX_COV_", D0_ENDVERTEX_COV_, &b_D0_ENDVERTEX_COV_);
   fChain->SetBranchAddress("D0_OWNPV_X", &D0_OWNPV_X, &b_D0_OWNPV_X);
   fChain->SetBranchAddress("D0_OWNPV_Y", &D0_OWNPV_Y, &b_D0_OWNPV_Y);
   fChain->SetBranchAddress("D0_OWNPV_Z", &D0_OWNPV_Z, &b_D0_OWNPV_Z);
   fChain->SetBranchAddress("D0_OWNPV_XERR", &D0_OWNPV_XERR, &b_D0_OWNPV_XERR);
   fChain->SetBranchAddress("D0_OWNPV_YERR", &D0_OWNPV_YERR, &b_D0_OWNPV_YERR);
   fChain->SetBranchAddress("D0_OWNPV_ZERR", &D0_OWNPV_ZERR, &b_D0_OWNPV_ZERR);
   fChain->SetBranchAddress("D0_OWNPV_CHI2", &D0_OWNPV_CHI2, &b_D0_OWNPV_CHI2);
   fChain->SetBranchAddress("D0_OWNPV_NDOF", &D0_OWNPV_NDOF, &b_D0_OWNPV_NDOF);
   fChain->SetBranchAddress("D0_OWNPV_COV_", D0_OWNPV_COV_, &b_D0_OWNPV_COV_);
   fChain->SetBranchAddress("D0_IP_OWNPV", &D0_IP_OWNPV, &b_D0_IP_OWNPV);
   fChain->SetBranchAddress("D0_IPCHI2_OWNPV", &D0_IPCHI2_OWNPV, &b_D0_IPCHI2_OWNPV);
   fChain->SetBranchAddress("D0_FD_OWNPV", &D0_FD_OWNPV, &b_D0_FD_OWNPV);
   fChain->SetBranchAddress("D0_FDCHI2_OWNPV", &D0_FDCHI2_OWNPV, &b_D0_FDCHI2_OWNPV);
   fChain->SetBranchAddress("D0_DIRA_OWNPV", &D0_DIRA_OWNPV, &b_D0_DIRA_OWNPV);
   fChain->SetBranchAddress("D0_ORIVX_X", &D0_ORIVX_X, &b_D0_ORIVX_X);
   fChain->SetBranchAddress("D0_ORIVX_Y", &D0_ORIVX_Y, &b_D0_ORIVX_Y);
   fChain->SetBranchAddress("D0_ORIVX_Z", &D0_ORIVX_Z, &b_D0_ORIVX_Z);
   fChain->SetBranchAddress("D0_ORIVX_XERR", &D0_ORIVX_XERR, &b_D0_ORIVX_XERR);
   fChain->SetBranchAddress("D0_ORIVX_YERR", &D0_ORIVX_YERR, &b_D0_ORIVX_YERR);
   fChain->SetBranchAddress("D0_ORIVX_ZERR", &D0_ORIVX_ZERR, &b_D0_ORIVX_ZERR);
   fChain->SetBranchAddress("D0_ORIVX_CHI2", &D0_ORIVX_CHI2, &b_D0_ORIVX_CHI2);
   fChain->SetBranchAddress("D0_ORIVX_NDOF", &D0_ORIVX_NDOF, &b_D0_ORIVX_NDOF);
   fChain->SetBranchAddress("D0_ORIVX_COV_", D0_ORIVX_COV_, &b_D0_ORIVX_COV_);
   fChain->SetBranchAddress("D0_FD_ORIVX", &D0_FD_ORIVX, &b_D0_FD_ORIVX);
   fChain->SetBranchAddress("D0_FDCHI2_ORIVX", &D0_FDCHI2_ORIVX, &b_D0_FDCHI2_ORIVX);
   fChain->SetBranchAddress("D0_DIRA_ORIVX", &D0_DIRA_ORIVX, &b_D0_DIRA_ORIVX);
   fChain->SetBranchAddress("D0_TRUEID", &D0_TRUEID, &b_D0_TRUEID);
   fChain->SetBranchAddress("D0_TRUEP_E", &D0_TRUEP_E, &b_D0_TRUEP_E);
   fChain->SetBranchAddress("D0_TRUEP_X", &D0_TRUEP_X, &b_D0_TRUEP_X);
   fChain->SetBranchAddress("D0_TRUEP_Y", &D0_TRUEP_Y, &b_D0_TRUEP_Y);
   fChain->SetBranchAddress("D0_TRUEP_Z", &D0_TRUEP_Z, &b_D0_TRUEP_Z);
   fChain->SetBranchAddress("D0_TRUEPT", &D0_TRUEPT, &b_D0_TRUEPT);
   fChain->SetBranchAddress("D0_TRUEORIGINVERTEX_X", &D0_TRUEORIGINVERTEX_X, &b_D0_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("D0_TRUEORIGINVERTEX_Y", &D0_TRUEORIGINVERTEX_Y, &b_D0_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("D0_TRUEORIGINVERTEX_Z", &D0_TRUEORIGINVERTEX_Z, &b_D0_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("D0_TRUEENDVERTEX_X", &D0_TRUEENDVERTEX_X, &b_D0_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("D0_TRUEENDVERTEX_Y", &D0_TRUEENDVERTEX_Y, &b_D0_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("D0_TRUEENDVERTEX_Z", &D0_TRUEENDVERTEX_Z, &b_D0_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("D0_TRUEISSTABLE", &D0_TRUEISSTABLE, &b_D0_TRUEISSTABLE);
   fChain->SetBranchAddress("D0_TRUETAU", &D0_TRUETAU, &b_D0_TRUETAU);
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
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNe", &pi_MC12TuneV2_ProbNNe, &b_pi_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNmu", &pi_MC12TuneV2_ProbNNmu, &b_pi_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNpi", &pi_MC12TuneV2_ProbNNpi, &b_pi_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNk", &pi_MC12TuneV2_ProbNNk, &b_pi_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNp", &pi_MC12TuneV2_ProbNNp, &b_pi_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNghost", &pi_MC12TuneV2_ProbNNghost, &b_pi_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNe", &pi_MC12TuneV3_ProbNNe, &b_pi_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNmu", &pi_MC12TuneV3_ProbNNmu, &b_pi_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNpi", &pi_MC12TuneV3_ProbNNpi, &b_pi_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNk", &pi_MC12TuneV3_ProbNNk, &b_pi_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNp", &pi_MC12TuneV3_ProbNNp, &b_pi_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNghost", &pi_MC12TuneV3_ProbNNghost, &b_pi_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("pi_MC12TuneV4_ProbNNe", &pi_MC12TuneV4_ProbNNe, &b_pi_MC12TuneV4_ProbNNe);
   fChain->SetBranchAddress("pi_MC12TuneV4_ProbNNmu", &pi_MC12TuneV4_ProbNNmu, &b_pi_MC12TuneV4_ProbNNmu);
   fChain->SetBranchAddress("pi_MC12TuneV4_ProbNNpi", &pi_MC12TuneV4_ProbNNpi, &b_pi_MC12TuneV4_ProbNNpi);
   fChain->SetBranchAddress("pi_MC12TuneV4_ProbNNk", &pi_MC12TuneV4_ProbNNk, &b_pi_MC12TuneV4_ProbNNk);
   fChain->SetBranchAddress("pi_MC12TuneV4_ProbNNp", &pi_MC12TuneV4_ProbNNp, &b_pi_MC12TuneV4_ProbNNp);
   fChain->SetBranchAddress("pi_MC12TuneV4_ProbNNghost", &pi_MC12TuneV4_ProbNNghost, &b_pi_MC12TuneV4_ProbNNghost);
   fChain->SetBranchAddress("pi_MC15TuneV1_ProbNNe", &pi_MC15TuneV1_ProbNNe, &b_pi_MC15TuneV1_ProbNNe);
   fChain->SetBranchAddress("pi_MC15TuneV1_ProbNNmu", &pi_MC15TuneV1_ProbNNmu, &b_pi_MC15TuneV1_ProbNNmu);
   fChain->SetBranchAddress("pi_MC15TuneV1_ProbNNpi", &pi_MC15TuneV1_ProbNNpi, &b_pi_MC15TuneV1_ProbNNpi);
   fChain->SetBranchAddress("pi_MC15TuneV1_ProbNNk", &pi_MC15TuneV1_ProbNNk, &b_pi_MC15TuneV1_ProbNNk);
   fChain->SetBranchAddress("pi_MC15TuneV1_ProbNNp", &pi_MC15TuneV1_ProbNNp, &b_pi_MC15TuneV1_ProbNNp);
   fChain->SetBranchAddress("pi_MC15TuneV1_ProbNNghost", &pi_MC15TuneV1_ProbNNghost, &b_pi_MC15TuneV1_ProbNNghost);
   fChain->SetBranchAddress("pi_P", &pi_P, &b_pi_P);
   fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
   fChain->SetBranchAddress("pi_PE", &pi_PE, &b_pi_PE);
   fChain->SetBranchAddress("pi_PX", &pi_PX, &b_pi_PX);
   fChain->SetBranchAddress("pi_PY", &pi_PY, &b_pi_PY);
   fChain->SetBranchAddress("pi_PZ", &pi_PZ, &b_pi_PZ);
   fChain->SetBranchAddress("pi_M", &pi_M, &b_pi_M);
   fChain->SetBranchAddress("pi_ID", &pi_ID, &b_pi_ID);
   fChain->SetBranchAddress("pi_PIDe", &pi_PIDe, &b_pi_PIDe);
   fChain->SetBranchAddress("pi_PIDmu", &pi_PIDmu, &b_pi_PIDmu);
   fChain->SetBranchAddress("pi_PIDK", &pi_PIDK, &b_pi_PIDK);
   fChain->SetBranchAddress("pi_PIDp", &pi_PIDp, &b_pi_PIDp);
   fChain->SetBranchAddress("pi_PIDd", &pi_PIDd, &b_pi_PIDd);
   fChain->SetBranchAddress("pi_ProbNNe", &pi_ProbNNe, &b_pi_ProbNNe);
   fChain->SetBranchAddress("pi_ProbNNk", &pi_ProbNNk, &b_pi_ProbNNk);
   fChain->SetBranchAddress("pi_ProbNNp", &pi_ProbNNp, &b_pi_ProbNNp);
   fChain->SetBranchAddress("pi_ProbNNpi", &pi_ProbNNpi, &b_pi_ProbNNpi);
   fChain->SetBranchAddress("pi_ProbNNmu", &pi_ProbNNmu, &b_pi_ProbNNmu);
   fChain->SetBranchAddress("pi_ProbNNd", &pi_ProbNNd, &b_pi_ProbNNd);
   fChain->SetBranchAddress("pi_ProbNNghost", &pi_ProbNNghost, &b_pi_ProbNNghost);
   fChain->SetBranchAddress("pi_hasMuon", &pi_hasMuon, &b_pi_hasMuon);
   fChain->SetBranchAddress("pi_isMuon", &pi_isMuon, &b_pi_isMuon);
   fChain->SetBranchAddress("pi_hasRich", &pi_hasRich, &b_pi_hasRich);
   fChain->SetBranchAddress("pi_UsedRichAerogel", &pi_UsedRichAerogel, &b_pi_UsedRichAerogel);
   fChain->SetBranchAddress("pi_UsedRich1Gas", &pi_UsedRich1Gas, &b_pi_UsedRich1Gas);
   fChain->SetBranchAddress("pi_UsedRich2Gas", &pi_UsedRich2Gas, &b_pi_UsedRich2Gas);
   fChain->SetBranchAddress("pi_RichAboveElThres", &pi_RichAboveElThres, &b_pi_RichAboveElThres);
   fChain->SetBranchAddress("pi_RichAboveMuThres", &pi_RichAboveMuThres, &b_pi_RichAboveMuThres);
   fChain->SetBranchAddress("pi_RichAbovePiThres", &pi_RichAbovePiThres, &b_pi_RichAbovePiThres);
   fChain->SetBranchAddress("pi_RichAboveKaThres", &pi_RichAboveKaThres, &b_pi_RichAboveKaThres);
   fChain->SetBranchAddress("pi_RichAbovePrThres", &pi_RichAbovePrThres, &b_pi_RichAbovePrThres);
   fChain->SetBranchAddress("pi_hasCalo", &pi_hasCalo, &b_pi_hasCalo);
   fChain->SetBranchAddress("pi_OWNPV_X", &pi_OWNPV_X, &b_pi_OWNPV_X);
   fChain->SetBranchAddress("pi_OWNPV_Y", &pi_OWNPV_Y, &b_pi_OWNPV_Y);
   fChain->SetBranchAddress("pi_OWNPV_Z", &pi_OWNPV_Z, &b_pi_OWNPV_Z);
   fChain->SetBranchAddress("pi_OWNPV_XERR", &pi_OWNPV_XERR, &b_pi_OWNPV_XERR);
   fChain->SetBranchAddress("pi_OWNPV_YERR", &pi_OWNPV_YERR, &b_pi_OWNPV_YERR);
   fChain->SetBranchAddress("pi_OWNPV_ZERR", &pi_OWNPV_ZERR, &b_pi_OWNPV_ZERR);
   fChain->SetBranchAddress("pi_OWNPV_CHI2", &pi_OWNPV_CHI2, &b_pi_OWNPV_CHI2);
   fChain->SetBranchAddress("pi_OWNPV_NDOF", &pi_OWNPV_NDOF, &b_pi_OWNPV_NDOF);
   fChain->SetBranchAddress("pi_OWNPV_COV_", pi_OWNPV_COV_, &b_pi_OWNPV_COV_);
   fChain->SetBranchAddress("pi_IP_OWNPV", &pi_IP_OWNPV, &b_pi_IP_OWNPV);
   fChain->SetBranchAddress("pi_IPCHI2_OWNPV", &pi_IPCHI2_OWNPV, &b_pi_IPCHI2_OWNPV);
   fChain->SetBranchAddress("pi_ORIVX_X", &pi_ORIVX_X, &b_pi_ORIVX_X);
   fChain->SetBranchAddress("pi_ORIVX_Y", &pi_ORIVX_Y, &b_pi_ORIVX_Y);
   fChain->SetBranchAddress("pi_ORIVX_Z", &pi_ORIVX_Z, &b_pi_ORIVX_Z);
   fChain->SetBranchAddress("pi_ORIVX_XERR", &pi_ORIVX_XERR, &b_pi_ORIVX_XERR);
   fChain->SetBranchAddress("pi_ORIVX_YERR", &pi_ORIVX_YERR, &b_pi_ORIVX_YERR);
   fChain->SetBranchAddress("pi_ORIVX_ZERR", &pi_ORIVX_ZERR, &b_pi_ORIVX_ZERR);
   fChain->SetBranchAddress("pi_ORIVX_CHI2", &pi_ORIVX_CHI2, &b_pi_ORIVX_CHI2);
   fChain->SetBranchAddress("pi_ORIVX_NDOF", &pi_ORIVX_NDOF, &b_pi_ORIVX_NDOF);
   fChain->SetBranchAddress("pi_ORIVX_COV_", pi_ORIVX_COV_, &b_pi_ORIVX_COV_);
   fChain->SetBranchAddress("pi_TRUEID", &pi_TRUEID, &b_pi_TRUEID);
   fChain->SetBranchAddress("pi_TRUEP_E", &pi_TRUEP_E, &b_pi_TRUEP_E);
   fChain->SetBranchAddress("pi_TRUEP_X", &pi_TRUEP_X, &b_pi_TRUEP_X);
   fChain->SetBranchAddress("pi_TRUEP_Y", &pi_TRUEP_Y, &b_pi_TRUEP_Y);
   fChain->SetBranchAddress("pi_TRUEP_Z", &pi_TRUEP_Z, &b_pi_TRUEP_Z);
   fChain->SetBranchAddress("pi_TRUEPT", &pi_TRUEPT, &b_pi_TRUEPT);
   fChain->SetBranchAddress("pi_TRUEORIGINVERTEX_X", &pi_TRUEORIGINVERTEX_X, &b_pi_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("pi_TRUEORIGINVERTEX_Y", &pi_TRUEORIGINVERTEX_Y, &b_pi_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("pi_TRUEORIGINVERTEX_Z", &pi_TRUEORIGINVERTEX_Z, &b_pi_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("pi_TRUEENDVERTEX_X", &pi_TRUEENDVERTEX_X, &b_pi_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("pi_TRUEENDVERTEX_Y", &pi_TRUEENDVERTEX_Y, &b_pi_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("pi_TRUEENDVERTEX_Z", &pi_TRUEENDVERTEX_Z, &b_pi_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("pi_TRUEISSTABLE", &pi_TRUEISSTABLE, &b_pi_TRUEISSTABLE);
   fChain->SetBranchAddress("pi_TRUETAU", &pi_TRUETAU, &b_pi_TRUETAU);
   fChain->SetBranchAddress("pi_L0Global_Dec", &pi_L0Global_Dec, &b_pi_L0Global_Dec);
   fChain->SetBranchAddress("pi_L0Global_TIS", &pi_L0Global_TIS, &b_pi_L0Global_TIS);
   fChain->SetBranchAddress("pi_L0Global_TOS", &pi_L0Global_TOS, &b_pi_L0Global_TOS);
   fChain->SetBranchAddress("pi_Hlt1Global_Dec", &pi_Hlt1Global_Dec, &b_pi_Hlt1Global_Dec);
   fChain->SetBranchAddress("pi_Hlt1Global_TIS", &pi_Hlt1Global_TIS, &b_pi_Hlt1Global_TIS);
   fChain->SetBranchAddress("pi_Hlt1Global_TOS", &pi_Hlt1Global_TOS, &b_pi_Hlt1Global_TOS);
   fChain->SetBranchAddress("pi_Hlt1Phys_Dec", &pi_Hlt1Phys_Dec, &b_pi_Hlt1Phys_Dec);
   fChain->SetBranchAddress("pi_Hlt1Phys_TIS", &pi_Hlt1Phys_TIS, &b_pi_Hlt1Phys_TIS);
   fChain->SetBranchAddress("pi_Hlt1Phys_TOS", &pi_Hlt1Phys_TOS, &b_pi_Hlt1Phys_TOS);
   fChain->SetBranchAddress("pi_Hlt2Global_Dec", &pi_Hlt2Global_Dec, &b_pi_Hlt2Global_Dec);
   fChain->SetBranchAddress("pi_Hlt2Global_TIS", &pi_Hlt2Global_TIS, &b_pi_Hlt2Global_TIS);
   fChain->SetBranchAddress("pi_Hlt2Global_TOS", &pi_Hlt2Global_TOS, &b_pi_Hlt2Global_TOS);
   fChain->SetBranchAddress("pi_Hlt2Phys_Dec", &pi_Hlt2Phys_Dec, &b_pi_Hlt2Phys_Dec);
   fChain->SetBranchAddress("pi_Hlt2Phys_TIS", &pi_Hlt2Phys_TIS, &b_pi_Hlt2Phys_TIS);
   fChain->SetBranchAddress("pi_Hlt2Phys_TOS", &pi_Hlt2Phys_TOS, &b_pi_Hlt2Phys_TOS);
   fChain->SetBranchAddress("pi_L0HadronDecision_Dec", &pi_L0HadronDecision_Dec, &b_pi_L0HadronDecision_Dec);
   fChain->SetBranchAddress("pi_L0HadronDecision_TIS", &pi_L0HadronDecision_TIS, &b_pi_L0HadronDecision_TIS);
   fChain->SetBranchAddress("pi_L0HadronDecision_TOS", &pi_L0HadronDecision_TOS, &b_pi_L0HadronDecision_TOS);
   fChain->SetBranchAddress("pi_Hlt1TrackMVADecision_Dec", &pi_Hlt1TrackMVADecision_Dec, &b_pi_Hlt1TrackMVADecision_Dec);
   fChain->SetBranchAddress("pi_Hlt1TrackMVADecision_TIS", &pi_Hlt1TrackMVADecision_TIS, &b_pi_Hlt1TrackMVADecision_TIS);
   fChain->SetBranchAddress("pi_Hlt1TrackMVADecision_TOS", &pi_Hlt1TrackMVADecision_TOS, &b_pi_Hlt1TrackMVADecision_TOS);
   fChain->SetBranchAddress("pi_Hlt1TwoTrackMVADecision_Dec", &pi_Hlt1TwoTrackMVADecision_Dec, &b_pi_Hlt1TwoTrackMVADecision_Dec);
   fChain->SetBranchAddress("pi_Hlt1TwoTrackMVADecision_TIS", &pi_Hlt1TwoTrackMVADecision_TIS, &b_pi_Hlt1TwoTrackMVADecision_TIS);
   fChain->SetBranchAddress("pi_Hlt1TwoTrackMVADecision_TOS", &pi_Hlt1TwoTrackMVADecision_TOS, &b_pi_Hlt1TwoTrackMVADecision_TOS);
   fChain->SetBranchAddress("pi_Hlt1TrackMVATightDecision_Dec", &pi_Hlt1TrackMVATightDecision_Dec, &b_pi_Hlt1TrackMVATightDecision_Dec);
   fChain->SetBranchAddress("pi_Hlt1TrackMVATightDecision_TIS", &pi_Hlt1TrackMVATightDecision_TIS, &b_pi_Hlt1TrackMVATightDecision_TIS);
   fChain->SetBranchAddress("pi_Hlt1TrackMVATightDecision_TOS", &pi_Hlt1TrackMVATightDecision_TOS, &b_pi_Hlt1TrackMVATightDecision_TOS);
   fChain->SetBranchAddress("pi_Hlt1TwoTrackMVATightDecision_Dec", &pi_Hlt1TwoTrackMVATightDecision_Dec, &b_pi_Hlt1TwoTrackMVATightDecision_Dec);
   fChain->SetBranchAddress("pi_Hlt1TwoTrackMVATightDecision_TIS", &pi_Hlt1TwoTrackMVATightDecision_TIS, &b_pi_Hlt1TwoTrackMVATightDecision_TIS);
   fChain->SetBranchAddress("pi_Hlt1TwoTrackMVATightDecision_TOS", &pi_Hlt1TwoTrackMVATightDecision_TOS, &b_pi_Hlt1TwoTrackMVATightDecision_TOS);
   fChain->SetBranchAddress("pi_Hlt2Topo2BodyDecision_Dec", &pi_Hlt2Topo2BodyDecision_Dec, &b_pi_Hlt2Topo2BodyDecision_Dec);
   fChain->SetBranchAddress("pi_Hlt2Topo2BodyDecision_TIS", &pi_Hlt2Topo2BodyDecision_TIS, &b_pi_Hlt2Topo2BodyDecision_TIS);
   fChain->SetBranchAddress("pi_Hlt2Topo2BodyDecision_TOS", &pi_Hlt2Topo2BodyDecision_TOS, &b_pi_Hlt2Topo2BodyDecision_TOS);
   fChain->SetBranchAddress("pi_Hlt2Topo3BodyDecision_Dec", &pi_Hlt2Topo3BodyDecision_Dec, &b_pi_Hlt2Topo3BodyDecision_Dec);
   fChain->SetBranchAddress("pi_Hlt2Topo3BodyDecision_TIS", &pi_Hlt2Topo3BodyDecision_TIS, &b_pi_Hlt2Topo3BodyDecision_TIS);
   fChain->SetBranchAddress("pi_Hlt2Topo3BodyDecision_TOS", &pi_Hlt2Topo3BodyDecision_TOS, &b_pi_Hlt2Topo3BodyDecision_TOS);
   fChain->SetBranchAddress("pi_Hlt2Topo4BodyDecision_Dec", &pi_Hlt2Topo4BodyDecision_Dec, &b_pi_Hlt2Topo4BodyDecision_Dec);
   fChain->SetBranchAddress("pi_Hlt2Topo4BodyDecision_TIS", &pi_Hlt2Topo4BodyDecision_TIS, &b_pi_Hlt2Topo4BodyDecision_TIS);
   fChain->SetBranchAddress("pi_Hlt2Topo4BodyDecision_TOS", &pi_Hlt2Topo4BodyDecision_TOS, &b_pi_Hlt2Topo4BodyDecision_TOS);
   fChain->SetBranchAddress("pi_TRACK_Type", &pi_TRACK_Type, &b_pi_TRACK_Type);
   fChain->SetBranchAddress("pi_TRACK_Key", &pi_TRACK_Key, &b_pi_TRACK_Key);
   fChain->SetBranchAddress("pi_TRACK_CHI2NDOF", &pi_TRACK_CHI2NDOF, &b_pi_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("pi_TRACK_PCHI2", &pi_TRACK_PCHI2, &b_pi_TRACK_PCHI2);
   fChain->SetBranchAddress("pi_TRACK_MatchCHI2", &pi_TRACK_MatchCHI2, &b_pi_TRACK_MatchCHI2);
   fChain->SetBranchAddress("pi_TRACK_GhostProb", &pi_TRACK_GhostProb, &b_pi_TRACK_GhostProb);
   fChain->SetBranchAddress("pi_TRACK_CloneDist", &pi_TRACK_CloneDist, &b_pi_TRACK_CloneDist);
   fChain->SetBranchAddress("pi_TRACK_Likelihood", &pi_TRACK_Likelihood, &b_pi_TRACK_Likelihood);
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

Bool_t Dzeroes_Variable_Tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Dzeroes_Variable_Tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Dzeroes_Variable_Tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
double checkphi(double phi)
{
  double returnphi = phi;
  if(phi > 1. * TMath::Pi())
    returnphi -= 2 * TMath::Pi();
  else if(phi < -1 * TMath::Pi() )
    returnphi += 2 * TMath::Pi();
  return returnphi;
}
#endif // #ifdef Dzeroes_Variable_Tree_cxx
