#include <vector>
#include <string>
#include <iostream>

#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TH1D.h>
#include <TRandom3.h>

int colors[10] = {1, 2, 3, 4, 6, 7, 8, 9, 41, 42};

TString str_Mag = "";
TString str_pT = "";
TString str_level = "";
TString str_followHard = "";
TString str_flavor = "";
TString str_ghost = "";
TString str_year = "";
TString str_GS = "";
TString str_charged = "";
TString str_pt;
TString str_eta;
TString str_Nevts;
TString str_PID = "";

//const int n_smearing_iter = 25;
const int n_smearing_iter = 1;


bool followHardest = true;
bool truthLevel = false;
bool ghostCut = true;
bool chargedJetCut = false;
bool PID_cut = true;

float B_mass = 5.2;
float MassMin = 5.24;
float MassMax = 5.31;
float Sideband1_Min = 5.15;
float Sideband1_Max = 5.2;
float Sideband2_Min = 5.4;
float Sideband2_Max = 5.51;
float mass_num;
float ghostProb = 0.4;
float jetradius = 0.5;

float etaMin = 2.5;
float etaMax = 4.;
float pTLow = 5.;
float ptMin = 10.;
float ptMax = 100.;
float pMin = 0;
float pMax = 10;

//const int ptHFbinsize = 9;
const int ptbinsize = 7; //5
const int customptbinsize = 5; //10
const int fineptbinsize = 10;

const int ptHFbinsize = 15;
const int ptJpsibinsize = 14;

const int HFetabinsize = 5;
const int Jpsietabinsize = 3;
const int longptbinsize = 6;
const int etabinsize = 6;
const int pbinsize = 20;
const int nTracksbinsize = 5;

const int zbinsize = 15;
const int jtbinsize = 18;
const int rbinsize = 11;

const int zbinsize_50_100 = 7; // N bins = len(binedges) - 1
const int jtbinsize_50_100 = 10;
const int rbinsize_50_100 = 6 ;



//double ptHF_binedges[ptHFbinsize + 1] = {2, 5, 10, 15, 20, 25, 35, 50, 80, 150};
double ptHF_binedges[ptHFbinsize + 1] = {0, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 25, 35, 100};
double ptJpsi_binedges[ptJpsibinsize + 1] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 20, 100};

double eta_binedges[etabinsize + 1] = { 2.2, 2.5, 2.65, 2.9, 3.3, 4.0, 4.5 };

double HFeta_binedges[HFetabinsize + 1] =  { 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };
//double Jpsieta_binedges[Jpsietabinsize + 1] =  { 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };
double Jpsieta_binedges[Jpsietabinsize + 1] = {2.0, 3.0, 3.5, 4.5};

double pt_binedges[ptbinsize + 1] = {pTLow, 10, 12, 15, 20, 30, 50, ptMax};
double custompt_binedges[customptbinsize +1] = {pTLow, 15, 20, 30, 50, ptMax};
double finept_binedges[fineptbinsize +1] = {pTLow, 15, 20, 30, 40, 50, 60, 70, 80, 100, 200};
double longpt_binedges[longptbinsize + 1] = {15, 17, 20, 30, 40, 50, ptMax};

double p_binedges[pbinsize + 1] = {2, 3, 4, 5, 7.5, 10, 12.5, 15, 20, 25, 30, 40, 50, 75, 100, 150, 200, 250, 300, 500, 1000};
double nTrack_binedges[nTracksbinsize + 1] = {0, 100, 200, 300, 400, 500};

double z_binedges[zbinsize + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};
double jt_binedges[jtbinsize + 1 ] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.50, 1.75, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 10.0};
double r_binedges[rbinsize +1 ] = {0.0, 0.025, 0.05, 0.075, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.5};

double z_binedges_50_100[zbinsize_50_100 + 1] = {0.0, 0.1, 0.25, 0.4, 0.55, 0.7, 0.85, 1.0};
double jt_binedges_50_100[jtbinsize_50_100 + 1 ] = {0.0, 0.5, 1.0, 1.50, 2.0, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0};
double r_binedges_50_100[rbinsize_50_100 +1 ] = {0.0, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5};