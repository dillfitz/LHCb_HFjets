#include <vector>
#include <string>
#include <iostream>

#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TH1D.h>
#include <TRandom3.h>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
// #include "/afs/cern.ch/work/i/ichahrou/RooUnfold/src/RooUnfoldBayes.h"
// #include "/afs/cern.ch/work/i/ichahrou/RooUnfold2.0.1/build/RooUnfoldResponse.h"

// gSystem->AddIncludePath(" -I$HOME//fastjet-install/include");
//     gSystem->Load("$HOME//fastjet-install/lib/libfastjet.so");

using namespace fastjet;

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

const double zjetdphicut = 7. * TMath::Pi() / 8.;
double B_mass = 5.2;
double mass_num;
double BDTbc_cut = 0.1;
double BDTbcudsg_cut = 0.0;
double ghostProb = 0.5;
double jetradius = 0.5;
// double Erad_low = 110.; //GeV
// double Erad_high = 120.;
int maxPVs = 6;
double etaMin = 2.5;
double etaMax = 4.;
double LambdaQCD = 0.2;
double ptMin = 20.;
double ptMax = 100.;
double pMin = 0;
double pMax = 10;
double sd_z_cut = 0.10;
double sd_beta = 0.0;

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
double R_min = 2.5;
double R_max = 6.;

// const int kT_bins = 14;
// const int z_bins = kT_bins;
double kT_min = -6.;
double kT_max = 3.;
double z_min = log(1. / 0.5);
// double z_min = 0.;
double z_max = 6.;
// int Erad_bins = 15;
double Erad_min = 0.;
double Erad_max = 1000.;
// int Erad_step = (Erad_max - Erad_min)/Erad_bins;
// const int dR_bins = 14;
double dR_min = 0.;
double dR_max = 5.;

// const int ktbinsize = 16;
// const int dRbinsize = 16;
// const int zbinsize = 16;
// const int thetabinsize = 16;
// const int Eradbinsize = 16;

const int ktbinsize = 12;
const int dRbinsize = 10;
const int zbinsize = 11;
const int thetabinsize = 10;
const int Eradbinsize = 12;

const int tr_ktbinsize = 12;
const int tr_dRbinsize = 10;
const int tr_zbinsize = 11;
const int tr_thetabinsize = 10;
const int tr_Eradbinsize = 12;

const int ptbinsize = 6;
// const int ptbinsize = 2;
// const int ptbinsize = 9; // more pt bins gives better unfolding for charged dist
// doesn't help Zjets to increase jet pt bins

const int ptHFbinsize = 9;
const int longptbinsize = 6;
const int ptbinsize_truth = 4;

const int etabinsize = 10;

const int pbinsize = 20;
const int neut_pbinsize = 9;
const int ptbinsize_JES = 4;

// double kt_binedges[ktbinsize+1];
// double dR_binedges[dRbinsize+1];

// double z_binedges[zbinsize+1];
// double theta_binedges[thetabinsize+1];
// double Erad_binedges[Eradbinsize+1];

// double tr_kt_binedges[tr_ktbinsize+1];
// double tr_dR_binedges[tr_dRbinsize+1];

// double tr_z_binedges[tr_zbinsize+1];
// double tr_theta_binedges[tr_thetabinsize+1];
// double tr_Erad_binedges[tr_Eradbinsize+1];

const double kt_factor = 0.35;
const double z_factor = 0.33;
double kt_binedges[ktbinsize + 1] = {-5., -2., -2 + kt_factor, -2 + 2 * kt_factor, -2 + 3 * kt_factor, -2 + 4 * kt_factor, -2 + 5 * kt_factor, -2 + 6 * kt_factor, -2 + 7 * kt_factor, -2 + 8 * kt_factor, -2 + 9 * kt_factor, -2 + 10 * kt_factor, 3.};
double z_binedges[zbinsize + 1] = {log(2.), log(2.) + z_factor, log(2.) + 2 * z_factor, log(2.) + 3 * z_factor, log(2.) + 4 * z_factor, log(2.) + 5 * z_factor, log(2.) + 6 * z_factor, log(2.) + 7 * z_factor, log(2.) + 8 * z_factor, log(2.) + 9 * z_factor, log(2.) + 10 * z_factor, 6.};
// double dR_binedges[dRbinsize+1] = {0, 0.25, 0.5, 0.75, 1., 1.25, 1.5, 1.75, 2., 2.25, 3., 5.};
double dR_binedges[dRbinsize + 1] = {0., 0.15, 0.37, 0.67, 0.97, 1.27, 1.56, 2.0, 2.6, 4., 6.};
double theta_binedges[thetabinsize + 1] = {2., 2.5, 2.83, 3.16, 3.49, 3.82, 4.15, 4.48, 4.81, 5.758, 9.};
double Erad_binedges[Eradbinsize + 1] = {0., 30., 60., 90., 130., 170., 210., 260., 310., 360., 410., 1000., 2000.};

double tr_kt_binedges[ktbinsize + 1] = {-5., -2., -2 + kt_factor, -2 + 2 * kt_factor, -2 + 3 * kt_factor, -2 + 4 * kt_factor, -2 + 5 * kt_factor, -2 + 6 * kt_factor, -2 + 7 * kt_factor, -2 + 8 * kt_factor, -2 + 9 * kt_factor, -2 + 10 * kt_factor, 3.};
double tr_z_binedges[tr_zbinsize + 1] = {log(2.), log(2.) + z_factor, log(2.) + 2 * z_factor, log(2.) + 3 * z_factor, log(2.) + 4 * z_factor, log(2.) + 5 * z_factor, log(2.) + 6 * z_factor, log(2.) + 7 * z_factor, log(2.) + 8 * z_factor, log(2.) + 9 * z_factor, log(2.) + 10 * z_factor, 6.};
// double tr_dR_binedges[dRbinsize+1] = {0, 0.25, 0.5, 0.75, 1., 1.25, 1.5, 1.75, 2., 2.25, 3., 5.};
double tr_dR_binedges[dRbinsize + 1] = {0., 0.15, 0.37, 0.67, 0.97, 1.27, 1.56, 2.0, 2.6, 4., 6.};
double tr_theta_binedges[thetabinsize + 1] = {2., 2.5, 2.83, 3.16, 3.49, 3.82, 4.15, 4.48, 4.81, 5.758, 9.};
double tr_Erad_binedges[Eradbinsize + 1] = {0., 30., 60., 90., 130., 170., 210., 260., 310., 360., 410., 1000., 2000.};

double ptHF_binedges[ptHFbinsize + 1] = {2, 5, 10, 15, 20, 25, 35, 50, 80, 150};
// double ptres_binedges[ptbinsize+1] = {10, 20, 30, 70, ptMax};
double pt_binedges[ptbinsize + 1] = {12.5, 15, 20, 30, 50, ptMax, 250};
double eta_binedges[ptbinsize + 1];
// double pt_binedges[ptbinsize+1] = {15, 20, 30, 50, 60, ptMax};   // ptbinsize = 6
// double pt_binedges[ptbinsize+1] = {15, 20, 40, 60, 80, 100, 120, 140, ptMax, 200};
// double pt_binedges[ptbinsize+1] = {15, 20, ptMax};
double longpt_binedges[longptbinsize + 1] = {15, 17, 20, 30, 40, 50, ptMax};
double pt_binedges_truth[ptbinsize_truth + 1] = {15, 20, 30, 50, ptMax};
double p_binedges[pbinsize + 1] = {2, 3, 4, 5, 7.5, 10, 12.5, 15, 20, 25, 30, 40, 50, 75, 100, 150, 200, 250, 300, 500, 1000};
double neut_p_binedges[pbinsize + 1] = {2, 4, 10, 20, 40, 80, 160, 320, 640, 1280};
