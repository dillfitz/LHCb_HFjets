#include <vector>
#include <string>
#include <iostream>

#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TH1D.h>
#include <TRandom3.h>
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
// #include "/afs/cern.ch/work/i/ichahrou/RooUnfold/src/RooUnfoldBayes.h"
// #include "/afs/cern.ch/work/i/ichahrou/RooUnfold2.0.1/build/RooUnfoldResponse.h"

// gSystem->AddIncludePath(" -I$HOME//fastjet-install/include");
//     gSystem->Load("$HOME//fastjet-install/lib/libfastjet.so");

//using namespace fastjet;

bool pt_cut = true;
bool Erad_cut = true;
bool kt_cut = true;
bool pt_track_cut = false;
bool removeHFDTRs = true;
bool followHardest = true;
bool fullReconstruction = false;
bool truthLevel = false;
bool ghostCut = true;
bool bdtCut = true;
bool softDrop = false;
bool chargedJetCut = false;
bool PrimaryVertexCut = true;

bool PID_cut = true;
bool DTF_cut = false;

const double zjetdphicut = 7. * TMath::Pi() / 8.;
float B_mass = 5.2;
float MassMin = 5.24;
float MassMax = 5.31;
float Sideband1_Min = 5.15;
float Sideband1_Max = 5.2;
float Sideband2_Min = 5.4;
float Sideband2_Max = 5.51;
float mass_num;
float BDTbc_cut = 0.1;
float BDTbcudsg_cut = 0.0;
float ghostProb = 0.5;
float jetradius = 0.5;
//float Erad_low = 110.; //GeV
//float Erad_high = 120.;
int maxPVs = 6;
float etaMin = 2.5;
float etaMax = 4.;
float LambdaQCD = 0.2;
float pTLow = 7.;
float ptMin = 20.;
//float ptMin = 15.0;
float ptMax = 100.;
float pMin = 0;
float pMax = 10;
float sd_z_cut = 0.10;
float sd_beta = 0.0;
float max_ipchi2 = 16;

TF1 *f1_theta_Erad = new TF1("f1_theta_Erad", "log(x/[0])", 1, 800);
TF1 *f1_kt_Erad = new TF1("f1_kt_Erad", "log(x/[0])", 1, 800);

const int NumHists = 5;
const int NumProj = 16;
const int EEC_bins = 100;
int MinErad = 100;
int MaxErad = 200;
int EradStep = 20;
int MinEradProj = 20;
int MaxEradProj = MinEradProj + EradStep * NumProj;
int StepErad = (MaxErad - MinErad) / NumHists;
int h2_theta_bins = 50;
int h2_theta_low = 1;
int h2_theta_high = 8;
int h2_erad_bins = 50;
int h2_erad_low = 0;
int h2_erad_high = 400;
int R_bins = 14;
const int NumRbins = 5;
int RbinsArr[NumRbins] = {5, 6, 7, 8, 9};
float R_min = 2.5;
float R_max = 6.;

// const int kT_bins = 14;
// const int z_bins = kT_bins;
float kT_min = -6.;
float kT_max = 3.;
float z_min = log(1. / 0.5);
// double z_min = 0.;
float z_max = 6.;
// int Erad_bins = 15;
float Erad_min = 0.;
float Erad_max = 1000.;
// int Erad_step = (Erad_max - Erad_min)/Erad_bins;
// const int dR_bins = 14;
float dR_min = 0.;
float dR_max = 5.;

// const int ktbinsize = 12;
// const int dRbinsize = 11;
// const int zbinsize = 13;
// const int thetabinsize = 11;
// const int Eradbinsize = 11;

// const int ptbinsize = 2;
// const int ptbinsize = 9; // more pt bins gives better unfolding for charged dist
// doesn't help Zjets to increase jet pt bins

//const int ptHFbinsize = 9;
const int ptbinsize = 5; //5
const int customptbinsize = 5; //10
const int fineptbinsize = 10;

const int ptHFbinsize = 10;
const int ptJpsibinsize = 14;

const int HFetabinsize = 5;
const int Jpsietabinsize = 5;
const int longptbinsize = 6;
const int ptbinsize_truth = 4;
const int etabinsize = 6;
const int pbinsize = 20;
const int neut_pbinsize = 9;
const int ptbinsize_JES = 4;
const int nTracksbinsize = 5;

const int zbinsize = 21; // N bins = len(binedges) - 1
const int jtbinsize = 20;
const int rbinsize = 25 ;
//const int rbinsize = 20 ;
const int zbinsize50100 = 11; // N bins = len(binedges) - 1
const int jtbinsize50100 = 16;
const int rbinsize50100 = 16 ;
//const int rbinsize = 20 ;

const int z0Bins = 27;  //PERFECT:45[55,53(Good),BETTER:52,51BEST: 50]
const int z1Bins = 43;  //  BEST: 43 , GOOD: 45
const int z2Bins = 25;  // BEST , BETTER: 25
const int z3Bins = 10;  // BEST: 10 GOOD: 13, Really good: 9
const int jt0Bins = 27;  // [BEST: 29! ] Good 30
const int jt1Bins = 45;  //PERFECT : GOOD 45
const int jt2Bins = 28;  // PERFECT: 28
const int jt3Bins = 17;  //PERFECT: GOOD: 17
const int r0Bins = 28;  //  and  GOOD 31 BEST: 28
const int r1Bins = 28;  //
const int r2Bins = 22;  /// GOOD: 22
const int r3Bins = 20;  // Good: 20


//const int etabinsize = 10;
//const int HFetabinsize = 10;

//double ptHF_binedges[ptHFbinsize + 1] = {2, 5, 10, 15, 20, 25, 35, 50, 80, 150};
double ptHF_binedges[ptHFbinsize + 1] = {0, 6, 10, 12, 14, 16, 18, 20, 25, 35, 100};
double ptJpsi_binedges[ptJpsibinsize + 1] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 20, 100};

// double ptres_binedges[ptbinsize+1] = {10, 20, 30, 70, ptMax};

//double pt_binedges[ptbinsize + 6] = {12.5, 15, 20, 30, 50, ptMax, 150};
double eta_binedges[etabinsize + 1] = { 2.2, 2.5, 2.65, 2.9, 3.3, 4.0, 4.5 };

double HFeta_binedges[HFetabinsize + 1] =  { 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };
double Jpsieta_binedges[Jpsietabinsize + 1] =  { 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };

double pt_binedges[ptbinsize + 1] = {pTLow, 15, 20, 30, 50, 100.};
double custompt_binedges[customptbinsize +1] = {pTLow, 15, 20, 30, 50, 100};
double finept_binedges[fineptbinsize +1] = {pTLow, 15, 20, 30, 40, 50, 60, 70, 80, 100, 200};

  // ptbinsize = 6
// double pt_binedges[ptbinsize+1] = {15, 20, 40, 60, 80, 100, 120, 140, ptMax, 200};
// double pt_binedges[ptbinsize+1] = {15, 20, ptMax};
double longpt_binedges[longptbinsize + 1] = {15, 17, 20, 30, 40, 50, ptMax};
double pt_binedges_truth[ptbinsize_truth + 1] = {15, 20, 30, 50, ptMax};
double p_binedges[pbinsize + 1] = {2, 3, 4, 5, 7.5, 10, 12.5, 15, 20, 25, 30, 40, 50, 75, 100, 150, 200, 250, 300, 500, 1000};
double neut_p_binedges[pbinsize + 1] = {2, 4, 10, 20, 40, 80, 160, 320, 640, 1280};
double nTrack_binedges[nTracksbinsize + 1] = {0, 100, 200, 300, 400, 500};

double z_binedges[zbinsize + 1] = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.1};
double jt_binedges[jtbinsize + 1 ] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
double r_binedges[rbinsize +1 ] = {0.0, 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3, 0.32, 0.34, 0.36,
                                    0.38, 0.4, 0.42, 0.44, 0.46, 0.48, 0.5 };

double z_50100binedges[zbinsize50100 + 1] = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};

float jt_Bwidth_50 = 0.625;
float r_Bwidth_50 = 0.03125;

double jt_50100binedges[jtbinsize50100 + 1 ] = {0.0, jt_Bwidth_50,  2*jt_Bwidth_50,  3.0*jt_Bwidth_50,  4.0*jt_Bwidth_50, 5.0*jt_Bwidth_50, 6.0*jt_Bwidth_50, 7.0*jt_Bwidth_50,  8.0*jt_Bwidth_50, 9.0*jt_Bwidth_50,  10.0*jt_Bwidth_50, 11*jt_Bwidth_50, 12*jt_Bwidth_50, 13*jt_Bwidth_50, 14*jt_Bwidth_50, 15*jt_Bwidth_50, 16*jt_Bwidth_50};

double r_50100binedges[rbinsize50100 +1 ] = {0.0, r_Bwidth_50, 2*r_Bwidth_50, 3*r_Bwidth_50, 4*r_Bwidth_50, 5*r_Bwidth_50, 6*r_Bwidth_50, 7*r_Bwidth_50, 8*r_Bwidth_50, 9*r_Bwidth_50, 10*r_Bwidth_50, 11*r_Bwidth_50, 12*r_Bwidth_50, 13*r_Bwidth_50, 14*r_Bwidth_50, 15*r_Bwidth_50, 16*r_Bwidth_50 };
//double r_binedges[rbinsize +1 ] = {0.0, 0.025, 0.050, 0.075, 0.1, 0.125, 0.150, 0.175, 0.2, 0.225, 0.250, 0.275, 0.3, 0.325, 0.350, 0.375, 0.4, 0.425,                                   0.450,0.475, 0.5};
 
