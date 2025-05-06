#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "../Settings.h"
#include "../../Helpers.h"
using namespace std;

void GetTotalSys(int NumEvts = -1,
                 int dataset = 91599,
                 bool WTA_cut = false,
                 int NumIters = 4)
{

  const int sigfigs = 4;
  gROOT->ForceStyle();
  gStyle->SetPaintTextFormat("3.3f");
  gStyle->SetOptStat(0);

  TString string_matching, string_JES, string_JER;
  TString string_closure, string_shapeclosure, string_unfold, string_unfold_rev, extension, string_ghost, string_jetid;
  TString string_trackingsysup, string_trackingsysdown, string_pidsysup, string_pidsysdown;
  TString string_trigsysup, string_trigsysdown, string_recselsys;
  TString string_itersysup, string_itersysdown;
  TString string_massfitsysnear, string_massfitsysfar, string_fitmodel;
  TString string_priorsys;
  TString str_followHard, str_ghost, str_Mag, str_flavor, str_DTF(""), str_PID(""), str_WTA("");
  TString loc_hists("../../../root_files/Bjets/Systematics/");
  TString loc_plots("../../../plots/Bjets/Systematics/");

  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;

  // int NumIters = 2;

  if (Mag == 0)
    str_Mag = "_MD";
  else if (Mag == 1)
    str_Mag = "_MU";
  if (flavor == 1)
    str_flavor = "_udsg";
  else if (flavor == 4)
    str_flavor = "_c";
  else if (flavor == 5)
    str_flavor = "_b";

  if (DTF_cut)
    str_DTF = "_DTF";
  if (PID_cut)
    str_PID = "_PID";

  if (flavor == 1)
    str_followHard = "_hard";
  else
  {
    // if(followHardest) str_followHard = "_hard";
    // else str_followHard = "_HF";
    str_followHard = "_HF";
  }
  if (ghostCut)
    str_ghost = Form("_ghost_%.1f", ghostProb);
  if (chargedJetCut)
    str_charged = "_charge";
  if (WTA_cut)
    str_WTA = "_WTA";

  string_JER = loc_hists + TString("JER_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_JES = loc_hists + TString("JES_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_jetid = loc_hists + TString("jetid_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trackingsysup = loc_hists + TString("trackingsysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trackingsysdown = loc_hists + TString("trackingsysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_pidsysup = loc_hists + TString("pidsysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_pidsysdown = loc_hists + TString("pidsysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trigsysup = loc_hists + TString("trigsysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trigsysdown = loc_hists + TString("trigsysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_itersysup = loc_hists + TString("itersysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_itersysdown = loc_hists + TString("itersysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_massfitsysnear = loc_hists + TString("massfitsysnear_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_massfitsysfar = loc_hists + TString("massfitsysfar_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_fitmodel = loc_hists + TString("signalsys_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);  
  string_recselsys = loc_hists + TString("recselsys_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_closure = "../../../root_files/BjetsMC/" + TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", 91599) + Form("_%d", 91599);
  string_shapeclosure = "../../../root_files/BjetsMC/" + TString("shapeclosure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", 91599) + Form("_%d", 91599);
  string_priorsys = loc_hists + TString("priorsys_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);

  // string_closure = loc_hists + TString("closure") + Form("_ev_%d", NumEvts)
  //           + Form("_ptj_%d%d", int(ptMin), int(ptMax))
  //           + Form("_eta_%.1f%.1f", etaMin, etaMax)
  //           +  str_followHard
  //           +  str_ghost
  //           +  Form("_dR_%.2f", minimum_dR)
  //           + "MD"
  //           + str_flavor +  Form("_%d", 1) + Form("_%d", 1)
  //           + Form("_%d", 93190) +  Form("_%d", 93191);

  // string_reco = loc + "hists/reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_data = loc + "hists/data_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_truth = loc + "hists/truth_ev_-1_ptj_20150_eta_2.54.0_hard_udsg_93139.root";
  // string_eff = loc + "hists/eff_truth_ev_-1_ptj_20150_eta_2.54.0_hard_udsg_93139.root";
  // string_unfold = loc + "hists/unfold_reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";

  extension = TString("total_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost  + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);

  cout << string_closure << endl;
  cout << string_JER << endl;
  cout << string_JES << endl;
  /////////////////////   Get Files /////////////////////////////////

  TFile *file_jetid = new TFile(string_jetid + TString(".root"), "READ");
  TFile *file_JER = new TFile(string_JER + TString(".root"), "READ");
  TFile *file_JES = new TFile(string_JES + TString(".root"), "READ");

  TFile *file_trackingsysup = new TFile(string_trackingsysup + TString(".root"), "READ");
  TFile *file_trackingsysdown = new TFile(string_trackingsysdown + TString(".root"), "READ");
  TFile *file_trigsysup = new TFile(string_trigsysup + TString(".root"), "READ");
  TFile *file_trigsysdown = new TFile(string_trigsysdown + TString(".root"), "READ");
  TFile *file_itersysup = new TFile(string_itersysup + TString(".root"), "READ");
  TFile *file_itersysdown = new TFile(string_itersysdown + TString(".root"), "READ");

  TFile *file_massfitsysnear = new TFile(string_massfitsysnear + TString(".root"), "READ");
  TFile *file_massfitsysfar = new TFile(string_massfitsysfar + TString(".root"), "READ");
  TFile *file_fitmodel = new TFile(string_fitmodel + TString(".root"), "READ");  

  TFile *file_pidsysup = new TFile(string_pidsysup + TString(".root"), "READ");
  TFile *file_pidsysdown = new TFile(string_pidsysdown + TString(".root"), "READ");
  TFile *file_recselsys = new TFile(string_recselsys + TString(".root"), "READ");

  TFile *file_closure = new TFile(string_closure + TString(".root"), "READ");
  TFile *file_shapeclosure = new TFile(string_shapeclosure + TString(".root"), "READ");  
  TFile *file_priorsys = new TFile(string_priorsys + TString(".root"), "READ");

  TFile *file_save = new TFile(loc_hists + extension + ".root", "RECREATE");

  /////////////////////   Get Systematic histograms /////////////////////////////////
  vector<TH1D *> vec_sys_z_ptbinned[ptbinsize-1], vec_sys_jt_ptbinned[ptbinsize-1], vec_sys_r_ptbinned[ptbinsize-1];
  vector<TH2D *> vec_sys_zjt_ptbinned[ptbinsize-1], vec_sys_zr_ptbinned[ptbinsize-1], vec_sys_jtr_ptbinned[ptbinsize-1];  
  vector<int> vec_markers = {21, 22, 23, 34, 33, 45, 47, 48, 49, 24, 25, 26, 27, 28, 29, 30, 31, 32, 43};
  vector<TString> vec_string = {"Jet ID",
                                "JER",
                                "JES",
                                "Track Eff.",
                                "PID Eff.",
                                "Trig. Eff.",
                                "Sideband Var.",
                                "Fit Model",
                                "Rec. Sel. Eff.",
                                "nonclosure",
                                "shapeclosure",
                                "iter",
                                "prior",
                                "Total"};
                                
  TH1D *h1_z_ptbinned_sys_jetid[ptbinsize-1], *h1_z_ptbinned_sys_jer[ptbinsize-1], *h1_z_ptbinned_sys_jes[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_trackingup[ptbinsize-1], *h1_z_ptbinned_sys_trackingdown[ptbinsize-1], *h1_z_ptbinned_sys_tracking[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_pidup[ptbinsize-1], *h1_z_ptbinned_sys_piddown[ptbinsize-1], *h1_z_ptbinned_sys_pid[ptbinsize-1];  
  TH1D *h1_z_ptbinned_sys_trigup[ptbinsize-1], *h1_z_ptbinned_sys_trigdown[ptbinsize-1], *h1_z_ptbinned_sys_trig[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_recsel[ptbinsize-1], *h1_z_ptbinned_sys_fitmodel[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_sbsubnear[ptbinsize-1], *h1_z_ptbinned_sys_sbsubfar[ptbinsize-1], *h1_z_ptbinned_sys_sbsub[ptbinsize-1];         
  TH1D *h1_z_ptbinned_sys_iterhigh[ptbinsize-1], *h1_z_ptbinned_sys_iterlow[ptbinsize-1], *h1_z_ptbinned_sys_iter[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_closure[ptbinsize-1], *h1_z_ptbinned_sys_prior[ptbinsize-1], *h1_z_ptbinned_sys_unfold[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_shapeclosure[ptbinsize-1];

  TH1D *h1_z_ptbinned_sys_jetid_sq[ptbinsize-1], *h1_z_ptbinned_sys_jer_sq[ptbinsize-1], *h1_z_ptbinned_sys_jes_sq[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_trackingup_sq[ptbinsize-1], *h1_z_ptbinned_sys_trackingdown_sq[ptbinsize-1], *h1_z_ptbinned_sys_tracking_sq[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_pidup_sq[ptbinsize-1], *h1_z_ptbinned_sys_piddown_sq[ptbinsize-1], *h1_z_ptbinned_sys_pid_sq[ptbinsize-1];  
  TH1D *h1_z_ptbinned_sys_trigup_sq[ptbinsize-1], *h1_z_ptbinned_sys_trigdown_sq[ptbinsize-1], *h1_z_ptbinned_sys_trig_sq[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_recsel_sq[ptbinsize-1], *h1_z_ptbinned_sys_fitmodel_sq[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_sbsubnear_sq[ptbinsize-1], *h1_z_ptbinned_sys_sbsubfar_sq[ptbinsize-1], *h1_z_ptbinned_sys_sbsub_sq[ptbinsize-1];         
  TH1D *h1_z_ptbinned_sys_iterhigh_sq[ptbinsize-1], *h1_z_ptbinned_sys_iterlow_sq[ptbinsize-1], *h1_z_ptbinned_sys_iter_sq[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_closure_sq[ptbinsize-1], *h1_z_ptbinned_sys_prior_sq[ptbinsize-1], *h1_z_ptbinned_sys_unfold_sq[ptbinsize-1];
  TH1D *h1_z_ptbinned_sys_shapeclosure_sq[ptbinsize-1];

  TH1D *h1_jt_ptbinned_sys_jetid[ptbinsize-1], *h1_jt_ptbinned_sys_jer[ptbinsize-1], *h1_jt_ptbinned_sys_jes[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_trackingup[ptbinsize-1], *h1_jt_ptbinned_sys_trackingdown[ptbinsize-1], *h1_jt_ptbinned_sys_tracking[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_pidup[ptbinsize-1], *h1_jt_ptbinned_sys_piddown[ptbinsize-1], *h1_jt_ptbinned_sys_pid[ptbinsize-1];  
  TH1D *h1_jt_ptbinned_sys_trigup[ptbinsize-1], *h1_jt_ptbinned_sys_trigdown[ptbinsize-1], *h1_jt_ptbinned_sys_trig[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_recsel[ptbinsize-1], *h1_jt_ptbinned_sys_fitmodel[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_sbsubnear[ptbinsize-1], *h1_jt_ptbinned_sys_sbsubfar[ptbinsize-1], *h1_jt_ptbinned_sys_sbsub[ptbinsize-1];         
  TH1D *h1_jt_ptbinned_sys_iterhigh[ptbinsize-1], *h1_jt_ptbinned_sys_iterlow[ptbinsize-1], *h1_jt_ptbinned_sys_iter[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_closure[ptbinsize-1], *h1_jt_ptbinned_sys_prior[ptbinsize-1], *h1_jt_ptbinned_sys_unfold[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_shapeclosure[ptbinsize-1];


  TH1D *h1_jt_ptbinned_sys_jetid_sq[ptbinsize-1], *h1_jt_ptbinned_sys_jer_sq[ptbinsize-1], *h1_jt_ptbinned_sys_jes_sq[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_trackingup_sq[ptbinsize-1], *h1_jt_ptbinned_sys_trackingdown_sq[ptbinsize-1], *h1_jt_ptbinned_sys_tracking_sq[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_pidup_sq[ptbinsize-1], *h1_jt_ptbinned_sys_piddown_sq[ptbinsize-1], *h1_jt_ptbinned_sys_pid_sq[ptbinsize-1];  
  TH1D *h1_jt_ptbinned_sys_trigup_sq[ptbinsize-1], *h1_jt_ptbinned_sys_trigdown_sq[ptbinsize-1], *h1_jt_ptbinned_sys_trig_sq[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_recsel_sq[ptbinsize-1], *h1_jt_ptbinned_sys_fitmodel_sq[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_sbsubnear_sq[ptbinsize-1], *h1_jt_ptbinned_sys_sbsubfar_sq[ptbinsize-1], *h1_jt_ptbinned_sys_sbsub_sq[ptbinsize-1];         
  TH1D *h1_jt_ptbinned_sys_iterhigh_sq[ptbinsize-1], *h1_jt_ptbinned_sys_iterlow_sq[ptbinsize-1], *h1_jt_ptbinned_sys_iter_sq[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_closure_sq[ptbinsize-1], *h1_jt_ptbinned_sys_prior_sq[ptbinsize-1], *h1_jt_ptbinned_sys_unfold_sq[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_shapeclosure_sq[ptbinsize-1];

  TH1D *h1_r_ptbinned_sys_jetid[ptbinsize-1], *h1_r_ptbinned_sys_jer[ptbinsize-1], *h1_r_ptbinned_sys_jes[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_trackingup[ptbinsize-1], *h1_r_ptbinned_sys_trackingdown[ptbinsize-1], *h1_r_ptbinned_sys_tracking[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_pidup[ptbinsize-1], *h1_r_ptbinned_sys_piddown[ptbinsize-1], *h1_r_ptbinned_sys_pid[ptbinsize-1];  
  TH1D *h1_r_ptbinned_sys_trigup[ptbinsize-1], *h1_r_ptbinned_sys_trigdown[ptbinsize-1], *h1_r_ptbinned_sys_trig[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_recsel[ptbinsize-1], *h1_r_ptbinned_sys_fitmodel[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_sbsubnear[ptbinsize-1], *h1_r_ptbinned_sys_sbsubfar[ptbinsize-1], *h1_r_ptbinned_sys_sbsub[ptbinsize-1];         
  TH1D *h1_r_ptbinned_sys_iterhigh[ptbinsize-1], *h1_r_ptbinned_sys_iterlow[ptbinsize-1], *h1_r_ptbinned_sys_iter[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_closure[ptbinsize-1], *h1_r_ptbinned_sys_prior[ptbinsize-1], *h1_r_ptbinned_sys_unfold[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_shapeclosure[ptbinsize-1];
 
  TH1D *h1_r_ptbinned_sys_jetid_sq[ptbinsize-1], *h1_r_ptbinned_sys_jer_sq[ptbinsize-1], *h1_r_ptbinned_sys_jes_sq[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_trackingup_sq[ptbinsize-1], *h1_r_ptbinned_sys_trackingdown_sq[ptbinsize-1], *h1_r_ptbinned_sys_tracking_sq[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_pidup_sq[ptbinsize-1], *h1_r_ptbinned_sys_piddown_sq[ptbinsize-1], *h1_r_ptbinned_sys_pid_sq[ptbinsize-1];  
  TH1D *h1_r_ptbinned_sys_trigup_sq[ptbinsize-1], *h1_r_ptbinned_sys_trigdown_sq[ptbinsize-1], *h1_r_ptbinned_sys_trig_sq[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_recsel_sq[ptbinsize-1], *h1_r_ptbinned_sys_fitmodel_sq[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_sbsubnear_sq[ptbinsize-1], *h1_r_ptbinned_sys_sbsubfar_sq[ptbinsize-1], *h1_r_ptbinned_sys_sbsub_sq[ptbinsize-1];         
  TH1D *h1_r_ptbinned_sys_iterhigh_sq[ptbinsize-1], *h1_r_ptbinned_sys_iterlow_sq[ptbinsize-1], *h1_r_ptbinned_sys_iter_sq[ptbinsize-1];
  TH1D *h1_r_ptbinned_sys_closure_sq[ptbinsize-1], *h1_r_ptbinned_sys_prior_sq[ptbinsize-1], *h1_r_ptbinned_sys_unfold_sq[ptbinsize-1]; 
  TH1D *h1_r_ptbinned_sys_shapeclosure_sq[ptbinsize-1];
 
  
  TH2D *h2_zjt_ptbinned_sys_jetid[ptbinsize-1], *h2_zjt_ptbinned_sys_jer[ptbinsize-1], *h2_zjt_ptbinned_sys_jes[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_trackingup[ptbinsize-1], *h2_zjt_ptbinned_sys_trackingdown[ptbinsize-1], *h2_zjt_ptbinned_sys_tracking[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_pidup[ptbinsize-1], *h2_zjt_ptbinned_sys_piddown[ptbinsize-1], *h2_zjt_ptbinned_sys_pid[ptbinsize-1];  
  TH2D *h2_zjt_ptbinned_sys_trigup[ptbinsize-1], *h2_zjt_ptbinned_sys_trigdown[ptbinsize-1], *h2_zjt_ptbinned_sys_trig[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_recsel[ptbinsize-1], *h2_zjt_ptbinned_sys_fitmodel[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_sbsubnear[ptbinsize-1], *h2_zjt_ptbinned_sys_sbsubfar[ptbinsize-1], *h2_zjt_ptbinned_sys_sbsub[ptbinsize-1];         
  TH2D *h2_zjt_ptbinned_sys_iterhigh[ptbinsize-1], *h2_zjt_ptbinned_sys_iterlow[ptbinsize-1], *h2_zjt_ptbinned_sys_iter[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_closure[ptbinsize-1], *h2_zjt_ptbinned_sys_prior[ptbinsize-1], *h2_zjt_ptbinned_sys_unfold[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_shapeclosure[ptbinsize-1];

  TH2D *h2_zjt_ptbinned_sys_jetid_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_jer_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_jes_sq[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_trackingup_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_trackingdown_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_tracking_sq[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_pidup_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_piddown_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_pid_sq[ptbinsize-1];  
  TH2D *h2_zjt_ptbinned_sys_trigup_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_trigdown_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_trig_sq[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_recsel_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_fitmodel_sq[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_sbsubnear_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_sbsubfar_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_sbsub_sq[ptbinsize-1];         
  TH2D *h2_zjt_ptbinned_sys_iterhigh_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_iterlow_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_iter_sq[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_closure_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_prior_sq[ptbinsize-1], *h2_zjt_ptbinned_sys_unfold_sq[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_sys_shapeclosure_sq[ptbinsize-1];

  TH2D *h2_zr_ptbinned_sys_jetid[ptbinsize-1], *h2_zr_ptbinned_sys_jer[ptbinsize-1], *h2_zr_ptbinned_sys_jes[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_trackingup[ptbinsize-1], *h2_zr_ptbinned_sys_trackingdown[ptbinsize-1], *h2_zr_ptbinned_sys_tracking[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_pidup[ptbinsize-1], *h2_zr_ptbinned_sys_piddown[ptbinsize-1], *h2_zr_ptbinned_sys_pid[ptbinsize-1];  
  TH2D *h2_zr_ptbinned_sys_trigup[ptbinsize-1], *h2_zr_ptbinned_sys_trigdown[ptbinsize-1], *h2_zr_ptbinned_sys_trig[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_recsel[ptbinsize-1], *h2_zr_ptbinned_sys_fitmodel[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_sbsubnear[ptbinsize-1], *h2_zr_ptbinned_sys_sbsubfar[ptbinsize-1], *h2_zr_ptbinned_sys_sbsub[ptbinsize-1];         
  TH2D *h2_zr_ptbinned_sys_iterhigh[ptbinsize-1], *h2_zr_ptbinned_sys_iterlow[ptbinsize-1], *h2_zr_ptbinned_sys_iter[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_closure[ptbinsize-1], *h2_zr_ptbinned_sys_prior[ptbinsize-1], *h2_zr_ptbinned_sys_unfold[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_shapeclosure[ptbinsize-1];

  TH2D *h2_zr_ptbinned_sys_jetid_sq[ptbinsize-1], *h2_zr_ptbinned_sys_jer_sq[ptbinsize-1], *h2_zr_ptbinned_sys_jes_sq[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_trackingup_sq[ptbinsize-1], *h2_zr_ptbinned_sys_trackingdown_sq[ptbinsize-1], *h2_zr_ptbinned_sys_tracking_sq[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_pidup_sq[ptbinsize-1], *h2_zr_ptbinned_sys_piddown_sq[ptbinsize-1], *h2_zr_ptbinned_sys_pid_sq[ptbinsize-1];  
  TH2D *h2_zr_ptbinned_sys_trigup_sq[ptbinsize-1], *h2_zr_ptbinned_sys_trigdown_sq[ptbinsize-1], *h2_zr_ptbinned_sys_trig_sq[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_recsel_sq[ptbinsize-1], *h2_zr_ptbinned_sys_fitmodel_sq[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_sbsubnear_sq[ptbinsize-1], *h2_zr_ptbinned_sys_sbsubfar_sq[ptbinsize-1], *h2_zr_ptbinned_sys_sbsub_sq[ptbinsize-1];         
  TH2D *h2_zr_ptbinned_sys_iterhigh_sq[ptbinsize-1], *h2_zr_ptbinned_sys_iterlow_sq[ptbinsize-1], *h2_zr_ptbinned_sys_iter_sq[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_closure_sq[ptbinsize-1], *h2_zr_ptbinned_sys_prior_sq[ptbinsize-1], *h2_zr_ptbinned_sys_unfold_sq[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_shapeclosure_sq[ptbinsize-1];

  TH2D *h2_jtr_ptbinned_sys_jetid[ptbinsize-1], *h2_jtr_ptbinned_sys_jer[ptbinsize-1], *h2_jtr_ptbinned_sys_jes[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_trackingup[ptbinsize-1], *h2_jtr_ptbinned_sys_trackingdown[ptbinsize-1], *h2_jtr_ptbinned_sys_tracking[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_pidup[ptbinsize-1], *h2_jtr_ptbinned_sys_piddown[ptbinsize-1], *h2_jtr_ptbinned_sys_pid[ptbinsize-1];  
  TH2D *h2_jtr_ptbinned_sys_trigup[ptbinsize-1], *h2_jtr_ptbinned_sys_trigdown[ptbinsize-1], *h2_jtr_ptbinned_sys_trig[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_recsel[ptbinsize-1], *h2_jtr_ptbinned_sys_fitmodel[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_sbsubnear[ptbinsize-1], *h2_jtr_ptbinned_sys_sbsubfar[ptbinsize-1], *h2_jtr_ptbinned_sys_sbsub[ptbinsize-1];         
  TH2D *h2_jtr_ptbinned_sys_iterhigh[ptbinsize-1], *h2_jtr_ptbinned_sys_iterlow[ptbinsize-1], *h2_jtr_ptbinned_sys_iter[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_closure[ptbinsize-1], *h2_jtr_ptbinned_sys_prior[ptbinsize-1], *h2_jtr_ptbinned_sys_unfold[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_shapeclosure[ptbinsize-1];

  TH2D *h2_jtr_ptbinned_sys_jetid_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_jer_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_jes_sq[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_trackingup_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_trackingdown_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_tracking_sq[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_pidup_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_piddown_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_pid_sq[ptbinsize-1];  
  TH2D *h2_jtr_ptbinned_sys_trigup_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_trigdown_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_trig_sq[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_recsel_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_fitmodel_sq[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_sbsubnear_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_sbsubfar_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_sbsub_sq[ptbinsize-1];         
  TH2D *h2_jtr_ptbinned_sys_iterhigh_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_iterlow_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_iter_sq[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_sys_closure_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_prior_sq[ptbinsize-1], *h2_jtr_ptbinned_sys_unfold_sq[ptbinsize-1];   
  TH2D *h2_jtr_ptbinned_sys_shapeclosure_sq[ptbinsize-1];

  TH1D *h1_z_ptbinned_sys_total[ptbinsize-1];
  TH1D *h1_jt_ptbinned_sys_total[ptbinsize-1]; 
  TH1D *h1_r_ptbinned_sys_total[ptbinsize-1];   
  TH2D *h2_zjt_ptbinned_sys_total[ptbinsize-1];
  TH2D *h2_zr_ptbinned_sys_total[ptbinsize-1]; 
  TH2D *h2_jtr_ptbinned_sys_total[ptbinsize-1];    
  
  for (int i = 1; i< ptbinsize; ++i)
  {                                

  h1_z_ptbinned_sys_jetid[i-1] = (TH1D *)file_jetid->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_jer[i-1] = (TH1D *)file_JER->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_jes[i-1] = (TH1D *)file_JES->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_trackingup[i-1] = (TH1D *)file_trackingsysup->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_trackingdown[i-1] = (TH1D *)file_trackingsysdown->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_trigup[i-1] = (TH1D *)file_trigsysup->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_trigdown[i-1] = (TH1D *)file_trigsysdown->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_iterhigh[i-1] = (TH1D *)file_itersysup->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_iterlow[i-1] = (TH1D *)file_itersysdown->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_sbsubnear[i-1] = (TH1D *)file_massfitsysnear->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_sbsubfar[i-1] = (TH1D *)file_massfitsysfar->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_fitmodel[i-1] = (TH1D *)file_fitmodel->Get(Form("z_pt%d_ratio", i));  
  h1_z_ptbinned_sys_pidup[i-1] = (TH1D *)file_pidsysup->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_piddown[i-1] = (TH1D *)file_pidsysdown->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_recsel[i-1] = (TH1D *)file_recselsys->Get(Form("z_pt%d_ratio", i));
  h1_z_ptbinned_sys_prior[i-1] = (TH1D *)file_priorsys->Get(Form("z_pt%d_ratio", i));
  
  h1_jt_ptbinned_sys_jetid[i-1] = (TH1D *)file_jetid->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_jer[i-1] = (TH1D *)file_JER->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_jes[i-1] = (TH1D *)file_JES->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_trackingup[i-1] = (TH1D *)file_trackingsysup->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_trackingdown[i-1] = (TH1D *)file_trackingsysdown->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_trigup[i-1] = (TH1D *)file_trigsysup->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_trigdown[i-1] = (TH1D *)file_trigsysdown->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_iterhigh[i-1] = (TH1D *)file_itersysup->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_iterlow[i-1] = (TH1D *)file_itersysdown->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_sbsubnear[i-1] = (TH1D *)file_massfitsysnear->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_sbsubfar[i-1] = (TH1D *)file_massfitsysfar->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_fitmodel[i-1] = (TH1D *)file_fitmodel->Get(Form("jt_pt%d_ratio", i));  
  h1_jt_ptbinned_sys_pidup[i-1] = (TH1D *)file_pidsysup->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_piddown[i-1] = (TH1D *)file_pidsysdown->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_recsel[i-1] = (TH1D *)file_recselsys->Get(Form("jt_pt%d_ratio", i));
  h1_jt_ptbinned_sys_prior[i-1] = (TH1D *)file_priorsys->Get(Form("jt_pt%d_ratio", i));
  
  h1_r_ptbinned_sys_jetid[i-1] = (TH1D *)file_jetid->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_jer[i-1] = (TH1D *)file_JER->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_jes[i-1] = (TH1D *)file_JES->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_trackingup[i-1] = (TH1D *)file_trackingsysup->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_trackingdown[i-1] = (TH1D *)file_trackingsysdown->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_trigup[i-1] = (TH1D *)file_trigsysup->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_trigdown[i-1] = (TH1D *)file_trigsysdown->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_iterhigh[i-1] = (TH1D *)file_itersysup->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_iterlow[i-1] = (TH1D *)file_itersysdown->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_sbsubnear[i-1] = (TH1D *)file_massfitsysnear->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_sbsubfar[i-1] = (TH1D *)file_massfitsysfar->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_fitmodel[i-1] = (TH1D *)file_fitmodel->Get(Form("r_pt%d_ratio", i));  
  h1_r_ptbinned_sys_pidup[i-1] = (TH1D *)file_pidsysup->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_piddown[i-1] = (TH1D *)file_pidsysdown->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_recsel[i-1] = (TH1D *)file_recselsys->Get(Form("r_pt%d_ratio", i));
  h1_r_ptbinned_sys_prior[i-1] = (TH1D *)file_priorsys->Get(Form("r_pt%d_ratio", i));    
  

  h2_zjt_ptbinned_sys_jetid[i-1] = (TH2D *)file_jetid->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_jer[i-1] = (TH2D *)file_JER->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_jes[i-1] = (TH2D *)file_JES->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_trackingup[i-1] = (TH2D *)file_trackingsysup->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_trackingdown[i-1] = (TH2D *)file_trackingsysdown->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_trigup[i-1] = (TH2D *)file_trigsysup->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_trigdown[i-1] = (TH2D *)file_trigsysdown->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_iterhigh[i-1] = (TH2D *)file_itersysup->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_iterlow[i-1] = (TH2D *)file_itersysdown->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_sbsubnear[i-1] = (TH2D *)file_massfitsysnear->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_sbsubfar[i-1] = (TH2D *)file_massfitsysfar->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_fitmodel[i-1] = (TH2D *)file_fitmodel->Get(Form("zjt_pt%d_ratio", i));  
  h2_zjt_ptbinned_sys_pidup[i-1] = (TH2D *)file_pidsysup->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_piddown[i-1] = (TH2D *)file_pidsysdown->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_recsel[i-1] = (TH2D *)file_recselsys->Get(Form("zjt_pt%d_ratio", i));
  h2_zjt_ptbinned_sys_prior[i-1] = (TH2D *)file_priorsys->Get(Form("zjt_pt%d_ratio", i));
  
  h2_zr_ptbinned_sys_jetid[i-1] = (TH2D *)file_jetid->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_jer[i-1] = (TH2D *)file_JER->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_jes[i-1] = (TH2D *)file_JES->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_trackingup[i-1] = (TH2D *)file_trackingsysup->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_trackingdown[i-1] = (TH2D *)file_trackingsysdown->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_trigup[i-1] = (TH2D *)file_trigsysup->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_trigdown[i-1] = (TH2D *)file_trigsysdown->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_iterhigh[i-1] = (TH2D *)file_itersysup->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_iterlow[i-1] = (TH2D *)file_itersysdown->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_sbsubnear[i-1] = (TH2D *)file_massfitsysnear->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_sbsubfar[i-1] = (TH2D *)file_massfitsysfar->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_fitmodel[i-1] = (TH2D *)file_fitmodel->Get(Form("zr_pt%d_ratio", i));  
  h2_zr_ptbinned_sys_pidup[i-1] = (TH2D *)file_pidsysup->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_piddown[i-1] = (TH2D *)file_pidsysdown->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_recsel[i-1] = (TH2D *)file_recselsys->Get(Form("zr_pt%d_ratio", i));
  h2_zr_ptbinned_sys_prior[i-1] = (TH2D *)file_priorsys->Get(Form("zr_pt%d_ratio", i));
  
  h2_jtr_ptbinned_sys_jetid[i-1] = (TH2D *)file_jetid->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_jer[i-1] = (TH2D *)file_JER->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_jes[i-1] = (TH2D *)file_JES->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_trackingup[i-1] = (TH2D *)file_trackingsysup->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_trackingdown[i-1] = (TH2D *)file_trackingsysdown->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_trigup[i-1] = (TH2D *)file_trigsysup->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_trigdown[i-1] = (TH2D *)file_trigsysdown->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_iterhigh[i-1] = (TH2D *)file_itersysup->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_iterlow[i-1] = (TH2D *)file_itersysdown->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_sbsubnear[i-1] = (TH2D *)file_massfitsysnear->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_sbsubfar[i-1] = (TH2D *)file_massfitsysfar->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_fitmodel[i-1] = (TH2D *)file_fitmodel->Get(Form("jtr_pt%d_ratio", i));  
  h2_jtr_ptbinned_sys_pidup[i-1] = (TH2D *)file_pidsysup->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_piddown[i-1] = (TH2D *)file_pidsysdown->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_recsel[i-1] = (TH2D *)file_recselsys->Get(Form("jtr_pt%d_ratio", i));
  h2_jtr_ptbinned_sys_prior[i-1] = (TH2D *)file_priorsys->Get(Form("jtr_pt%d_ratio", i));    

  cout << "Handling Closure" << endl;
  h1_z_ptbinned_sys_closure[i-1] = (TH1D *)file_closure->Get(Form("z_pt%d_closure_error", i));
  h1_jt_ptbinned_sys_closure[i-1] = (TH1D *)file_closure->Get(Form("jt_pt%d_closure_error", i));  
  h1_r_ptbinned_sys_closure[i-1] = (TH1D *)file_closure->Get(Form("r_pt%d_closure_error", i));  
  h2_zjt_ptbinned_sys_closure[i-1] = (TH2D *)file_closure->Get(Form("zjt_pt%d_closure_error", i));
  h2_zr_ptbinned_sys_closure[i-1] = (TH2D *)file_closure->Get(Form("zr_pt%d_closure_error", i));  
  h2_jtr_ptbinned_sys_closure[i-1] = (TH2D *)file_closure->Get(Form("jtr_pt%d_closure_error", i));    

  h1_z_ptbinned_sys_shapeclosure[i-1] = (TH1D *)file_shapeclosure->Get(Form("z_pt%d_closure_error", i));
  h1_jt_ptbinned_sys_shapeclosure[i-1] = (TH1D *)file_shapeclosure->Get(Form("jt_pt%d_closure_error", i));  
  h1_r_ptbinned_sys_shapeclosure[i-1] = (TH1D *)file_shapeclosure->Get(Form("r_pt%d_closure_error", i));  
  h2_zjt_ptbinned_sys_shapeclosure[i-1] = (TH2D *)file_shapeclosure->Get(Form("zjt_pt%d_closure_error", i));
  h2_zr_ptbinned_sys_shapeclosure[i-1] = (TH2D *)file_shapeclosure->Get(Form("zr_pt%d_closure_error", i));  
  h2_jtr_ptbinned_sys_shapeclosure[i-1] = (TH2D *)file_shapeclosure->Get(Form("jtr_pt%d_closure_error", i));  

  // TH2D *h2_ptktdR_sys_closure = (TH2D *)h2_ptktdR_sys_closure_up->Clone("h2_ptktdR_sys_closure");
  // h2_ptktdR_sys_closure->Add(h2_ptktdR_sys_closure_down);
  // h2_ptktdR_sys_closure->Scale(0.5);

  //TH2D *h1_z_ptbinned_sys_closure = (TH2D *)h2_ptktdR_sys_closure_smeartest->Clone("h2_ptktdR_sys_closure");

  cout << "Creating new histograms" << endl;

  h1_z_ptbinned_sys_jer_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_jer[i-1]->Clone(Form("z_pt%d_sys_jer_sq", i));
  h1_z_ptbinned_sys_jetid_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_jetid[i-1]->Clone(Form("z_pt%d_sys_jetid_sq", i));
  h1_z_ptbinned_sys_jes_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_jes[i-1]->Clone(Form("z_pt%d_sys_jes_sq",i));
  h1_z_ptbinned_sys_trackingup_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_trackingup[i-1]->Clone(Form("z_pt%d_sys_trackingup_sq",i));
  h1_z_ptbinned_sys_trackingdown_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_trackingdown[i-1]->Clone(Form("z_pt%d_sys_trackingdown_sq",i));
  h1_z_ptbinned_sys_trigup_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_trigup[i-1]->Clone(Form("z_pt%d_sys_trigup_sq", i));
  h1_z_ptbinned_sys_trigdown_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_trigdown[i-1]->Clone(Form("z_pt%d_sys_trigdown_sq", i));
  h1_z_ptbinned_sys_sbsubnear_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_sbsubnear[i-1]->Clone(Form("z_pt%d_sys_sbsubnear_sq", i));
  h1_z_ptbinned_sys_sbsubfar_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_sbsubfar[i-1]->Clone(Form("z_pt%d_sys_sbsubfar_sq", i));
  h1_z_ptbinned_sys_fitmodel_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_fitmodel[i-1]->Clone(Form("z_pt%d_sys_fitmodel_sq", i));
  h1_z_ptbinned_sys_pidup_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_pidup[i-1]->Clone(Form("z_pt%d_sys_pidup_sq", i));
  h1_z_ptbinned_sys_piddown_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_piddown[i-1]->Clone(Form("z_pt%d_sys_piddown_sq", i));
  h1_z_ptbinned_sys_recsel_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_recsel[i-1]->Clone(Form("z_pt%d_sys_recsel_sq", i));
  h1_z_ptbinned_sys_iterhigh_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_iterhigh[i-1]->Clone(Form("z_pt%d_sys_iterhigh_sq", i));
  h1_z_ptbinned_sys_iterlow_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_iterlow[i-1]->Clone(Form("z_pt%d_sys_iterlow_sq", i));
  h1_z_ptbinned_sys_prior_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_prior[i-1]->Clone(Form("z_pt%d_sys_prior_sq", i));  
  h1_z_ptbinned_sys_closure_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_closure[i-1]->Clone(Form("z_pt%d_sys_closure_sq", i));
  h1_z_ptbinned_sys_shapeclosure_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_shapeclosure[i-1]->Clone(Form("z_pt%d_sys_shapeclosure_sq", i));  

  
  h1_jt_ptbinned_sys_jer_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_jer[i-1]->Clone(Form("jt_pt%d_sys_jer_sq", i));
  h1_jt_ptbinned_sys_jetid_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_jetid[i-1]->Clone(Form("jt_pt%d_sys_jetid_sq", i));
  h1_jt_ptbinned_sys_jes_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_jes[i-1]->Clone(Form("jt_pt%d_sys_jes_sq",i));
  h1_jt_ptbinned_sys_trackingup_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_trackingup[i-1]->Clone(Form("jt_pt%d_sys_trackingup_sq",i));
  h1_jt_ptbinned_sys_trackingdown_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_trackingdown[i-1]->Clone(Form("jt_pt%d_sys_trackingdown_sq",i));
  h1_jt_ptbinned_sys_trigup_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_trigup[i-1]->Clone(Form("jt_pt%d_sys_trigup_sq", i));
  h1_jt_ptbinned_sys_trigdown_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_trigdown[i-1]->Clone(Form("jt_pt%d_sys_trigdown_sq", i));
  h1_jt_ptbinned_sys_sbsubnear_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_sbsubnear[i-1]->Clone(Form("jt_pt%d_sys_sbsubnear_sq", i));
  h1_jt_ptbinned_sys_sbsubfar_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_sbsubfar[i-1]->Clone(Form("jt_pt%d_sys_sbsubfar_sq", i));
  h1_jt_ptbinned_sys_fitmodel_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_fitmodel[i-1]->Clone(Form("jt_pt%d_sys_fitmodel_sq", i));
  h1_jt_ptbinned_sys_pidup_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_pidup[i-1]->Clone(Form("jt_pt%d_sys_pidup_sq", i));
  h1_jt_ptbinned_sys_piddown_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_piddown[i-1]->Clone(Form("jt_pt%d_sys_piddown_sq", i));
  h1_jt_ptbinned_sys_recsel_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_recsel[i-1]->Clone(Form("jt_pt%d_sys_recsel_sq", i));
  h1_jt_ptbinned_sys_iterhigh_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_iterhigh[i-1]->Clone(Form("jt_pt%d_sys_iterhigh_sq", i));
  h1_jt_ptbinned_sys_iterlow_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_iterlow[i-1]->Clone(Form("jt_pt%d_sys_iterlow_sq", i));
  h1_jt_ptbinned_sys_prior_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_prior[i-1]->Clone(Form("jt_pt%d_sys_prior_sq", i));  
  h1_jt_ptbinned_sys_closure_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_closure[i-1]->Clone(Form("jt_pt%d_sys_closure_sq", i));    
  h1_jt_ptbinned_sys_shapeclosure_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_shapeclosure[i-1]->Clone(Form("jt_pt%d_sys_shapeclosure_sq", i));  

  h1_r_ptbinned_sys_jer_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_jer[i-1]->Clone(Form("r_pt%d_sys_jer_sq", i));
  h1_r_ptbinned_sys_jetid_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_jetid[i-1]->Clone(Form("r_pt%d_sys_jetid_sq", i));
  h1_r_ptbinned_sys_jes_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_jes[i-1]->Clone(Form("r_pt%d_sys_jes_sq",i));
  h1_r_ptbinned_sys_trackingup_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_trackingup[i-1]->Clone(Form("r_pt%d_sys_trackingup_sq",i));
  h1_r_ptbinned_sys_trackingdown_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_trackingdown[i-1]->Clone(Form("r_pt%d_sys_trackingdown_sq",i));
  h1_r_ptbinned_sys_trigup_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_trigup[i-1]->Clone(Form("r_pt%d_sys_trigup_sq", i));
  h1_r_ptbinned_sys_trigdown_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_trigdown[i-1]->Clone(Form("r_pt%d_sys_trigdown_sq", i));
  h1_r_ptbinned_sys_sbsubnear_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_sbsubnear[i-1]->Clone(Form("r_pt%d_sys_sbsubnear_sq", i));
  h1_r_ptbinned_sys_sbsubfar_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_sbsubfar[i-1]->Clone(Form("r_pt%d_sys_sbsubfar_sq", i));
  h1_r_ptbinned_sys_fitmodel_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_fitmodel[i-1]->Clone(Form("r_pt%d_sys_fitmodel_sq", i));
  h1_r_ptbinned_sys_pidup_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_pidup[i-1]->Clone(Form("r_pt%d_sys_pidup_sq", i));
  h1_r_ptbinned_sys_piddown_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_piddown[i-1]->Clone(Form("r_pt%d_sys_piddown_sq", i));
  h1_r_ptbinned_sys_recsel_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_recsel[i-1]->Clone(Form("r_pt%d_sys_recsel_sq", i));
  h1_r_ptbinned_sys_iterhigh_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_iterhigh[i-1]->Clone(Form("r_pt%d_sys_iterhigh_sq", i));
  h1_r_ptbinned_sys_iterlow_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_iterlow[i-1]->Clone(Form("r_pt%d_sys_iterlow_sq", i));
  h1_r_ptbinned_sys_prior_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_prior[i-1]->Clone(Form("r_pt%d_sys_prior_sq", i));  
  h1_r_ptbinned_sys_closure_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_closure[i-1]->Clone(Form("r_pt%d_sys_closure_sq", i));      
  h1_r_ptbinned_sys_shapeclosure_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_shapeclosure[i-1]->Clone(Form("r_pt%d_sys_shapeclosure_sq", i));  
 

  h2_zjt_ptbinned_sys_jer_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_jer[i-1]->Clone(Form("zjt_pt%d_sys_jer_sq", i));
  h2_zjt_ptbinned_sys_jetid_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_jetid[i-1]->Clone(Form("zjt_pt%d_sys_jetid_sq", i));
  h2_zjt_ptbinned_sys_jes_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_jes[i-1]->Clone(Form("zjt_pt%d_sys_jes_sq",i));
  h2_zjt_ptbinned_sys_trackingup_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_trackingup[i-1]->Clone(Form("zjt_pt%d_sys_trackingup_sq",i));
  h2_zjt_ptbinned_sys_trackingdown_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_trackingdown[i-1]->Clone(Form("zjt_pt%d_sys_trackingdown_sq",i));
  h2_zjt_ptbinned_sys_trigup_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_trigup[i-1]->Clone(Form("zjt_pt%d_sys_trigup_sq", i));
  h2_zjt_ptbinned_sys_trigdown_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_trigdown[i-1]->Clone(Form("zjt_pt%d_sys_trigdown_sq", i));
  h2_zjt_ptbinned_sys_sbsubnear_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_sbsubnear[i-1]->Clone(Form("zjt_pt%d_sys_sbsubnear_sq", i));
  h2_zjt_ptbinned_sys_sbsubfar_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_sbsubfar[i-1]->Clone(Form("zjt_pt%d_sys_sbsubfar_sq", i));
  h2_zjt_ptbinned_sys_fitmodel_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_fitmodel[i-1]->Clone(Form("zjt_pt%d_sys_fitmodel_sq", i));
  h2_zjt_ptbinned_sys_pidup_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_pidup[i-1]->Clone(Form("zjt_pt%d_sys_pidup_sq", i));
  h2_zjt_ptbinned_sys_piddown_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_piddown[i-1]->Clone(Form("zjt_pt%d_sys_piddown_sq", i));
  h2_zjt_ptbinned_sys_recsel_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_recsel[i-1]->Clone(Form("zjt_pt%d_sys_recsel_sq", i));
  h2_zjt_ptbinned_sys_iterhigh_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_iterhigh[i-1]->Clone(Form("zjt_pt%d_sys_iterhigh_sq", i));
  h2_zjt_ptbinned_sys_iterlow_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_iterlow[i-1]->Clone(Form("zjt_pt%d_sys_iterlow_sq", i));
  h2_zjt_ptbinned_sys_prior_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_prior[i-1]->Clone(Form("zjt_pt%d_sys_prior_sq", i));  
  h2_zjt_ptbinned_sys_closure_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_closure[i-1]->Clone(Form("zjt_pt%d_sys_closure_sq", i));  
  h2_zjt_ptbinned_sys_shapeclosure_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_shapeclosure[i-1]->Clone(Form("zjt_pt%d_sys_shapeclosure_sq", i));  

  h2_zr_ptbinned_sys_jer_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_jer[i-1]->Clone(Form("zr_pt%d_sys_jer_sq", i));
  h2_zr_ptbinned_sys_jetid_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_jetid[i-1]->Clone(Form("zr_pt%d_sys_jetid_sq", i));
  h2_zr_ptbinned_sys_jes_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_jes[i-1]->Clone(Form("zr_pt%d_sys_jes_sq",i));
  h2_zr_ptbinned_sys_trackingup_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_trackingup[i-1]->Clone(Form("zr_pt%d_sys_trackingup_sq",i));
  h2_zr_ptbinned_sys_trackingdown_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_trackingdown[i-1]->Clone(Form("zr_pt%d_sys_trackingdown_sq",i));
  h2_zr_ptbinned_sys_trigup_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_trigup[i-1]->Clone(Form("zr_pt%d_sys_trigup_sq", i));
  h2_zr_ptbinned_sys_trigdown_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_trigdown[i-1]->Clone(Form("zr_pt%d_sys_trigdown_sq", i));
  h2_zr_ptbinned_sys_sbsubnear_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_sbsubnear[i-1]->Clone(Form("zr_pt%d_sys_sbsubnear_sq", i));
  h2_zr_ptbinned_sys_sbsubfar_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_sbsubfar[i-1]->Clone(Form("zr_pt%d_sys_sbsubfar_sq", i));
  h2_zr_ptbinned_sys_fitmodel_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_fitmodel[i-1]->Clone(Form("zr_pt%d_sys_fitmodel_sq", i));
  h2_zr_ptbinned_sys_pidup_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_pidup[i-1]->Clone(Form("zr_pt%d_sys_pidup_sq", i));
  h2_zr_ptbinned_sys_piddown_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_piddown[i-1]->Clone(Form("zr_pt%d_sys_piddown_sq", i));
  h2_zr_ptbinned_sys_recsel_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_recsel[i-1]->Clone(Form("zr_pt%d_sys_recsel_sq", i));
  h2_zr_ptbinned_sys_iterhigh_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_iterhigh[i-1]->Clone(Form("zr_pt%d_sys_iterhigh_sq", i));
  h2_zr_ptbinned_sys_iterlow_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_iterlow[i-1]->Clone(Form("zr_pt%d_sys_iterlow_sq", i));
  h2_zr_ptbinned_sys_prior_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_prior[i-1]->Clone(Form("zr_pt%d_sys_prior_sq", i));  
  h2_zr_ptbinned_sys_closure_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_closure[i-1]->Clone(Form("zr_pt%d_sys_closure_sq", i));    
  h2_zr_ptbinned_sys_shapeclosure_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_shapeclosure[i-1]->Clone(Form("zr_pt%d_sys_shapeclosure_sq", i));    

  h2_jtr_ptbinned_sys_jer_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_jer[i-1]->Clone(Form("jtr_pt%d_sys_jer_sq", i));
  h2_jtr_ptbinned_sys_jetid_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_jetid[i-1]->Clone(Form("jtr_pt%d_sys_jetid_sq", i));
  h2_jtr_ptbinned_sys_jes_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_jes[i-1]->Clone(Form("jtr_pt%d_sys_jes_sq",i));
  h2_jtr_ptbinned_sys_trackingup_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_trackingup[i-1]->Clone(Form("jtr_pt%d_sys_trackingup_sq",i));
  h2_jtr_ptbinned_sys_trackingdown_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_trackingdown[i-1]->Clone(Form("jtr_pt%d_sys_trackingdown_sq",i));
  h2_jtr_ptbinned_sys_trigup_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_trigup[i-1]->Clone(Form("jtr_pt%d_sys_trigup_sq", i));
  h2_jtr_ptbinned_sys_trigdown_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_trigdown[i-1]->Clone(Form("jtr_pt%d_sys_trigdown_sq", i));
  h2_jtr_ptbinned_sys_sbsubnear_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_sbsubnear[i-1]->Clone(Form("jtr_pt%d_sys_sbsubnear_sq", i));
  h2_jtr_ptbinned_sys_sbsubfar_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_sbsubfar[i-1]->Clone(Form("jtr_pt%d_sys_sbsubfar_sq", i));
  h2_jtr_ptbinned_sys_fitmodel_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_fitmodel[i-1]->Clone(Form("jtr_pt%d_sys_fitmodel_sq", i));
  h2_jtr_ptbinned_sys_pidup_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_pidup[i-1]->Clone(Form("jtr_pt%d_sys_pidup_sq", i));
  h2_jtr_ptbinned_sys_piddown_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_piddown[i-1]->Clone(Form("jtr_pt%d_sys_piddown_sq", i));
  h2_jtr_ptbinned_sys_recsel_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_recsel[i-1]->Clone(Form("jtr_pt%d_sys_recsel_sq", i));
  h2_jtr_ptbinned_sys_iterhigh_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_iterhigh[i-1]->Clone(Form("jtr_pt%d_sys_iterhigh_sq", i));
  h2_jtr_ptbinned_sys_iterlow_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_iterlow[i-1]->Clone(Form("jtr_pt%d_sys_iterlow_sq", i));
  h2_jtr_ptbinned_sys_prior_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_prior[i-1]->Clone(Form("jtr_pt%d_sys_prior_sq", i));  
  h2_jtr_ptbinned_sys_closure_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_closure[i-1]->Clone(Form("jtr_pt%d_sys_closure_sq", i));  
  h2_jtr_ptbinned_sys_shapeclosure_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_shapeclosure[i-1]->Clone(Form("jtr_pt%d_sys_shapeclosure_sq", i));      
  
  
  h1_z_ptbinned_sys_total[i-1] = (TH1D *)h1_z_ptbinned_sys_jer[i-1]->Clone(Form("z_pt%d_total_sys",i));
  h1_jt_ptbinned_sys_total[i-1] = (TH1D *)h1_jt_ptbinned_sys_jer[i-1]->Clone(Form("jt_pt%d_total_sys",i));
  h1_r_ptbinned_sys_total[i-1] = (TH1D *)h1_r_ptbinned_sys_jer[i-1]->Clone(Form("r_pt%d_total_sys",i));    
  h2_zjt_ptbinned_sys_total[i-1] = (TH2D *)h2_zjt_ptbinned_sys_jer[i-1]->Clone(Form("zjt_pt%d_total_sys",i));
  h2_zr_ptbinned_sys_total[i-1] = (TH2D *)h2_zr_ptbinned_sys_jer[i-1]->Clone(Form("zr_pt%d_total_sys",i));
  h2_jtr_ptbinned_sys_total[i-1] = (TH2D *)h2_jtr_ptbinned_sys_jer[i-1]->Clone(Form("jtr_pt%d_total_sys",i));


  // Square (and combine where applicable)
  SetHistConst(h1_z_ptbinned_sys_total[i-1], 0.);
  h1_z_ptbinned_sys_jer_sq[i-1]->Multiply(h1_z_ptbinned_sys_jer[i-1], h1_z_ptbinned_sys_jer[i-1]);
  h1_z_ptbinned_sys_jetid_sq[i-1]->Multiply(h1_z_ptbinned_sys_jetid[i-1], h1_z_ptbinned_sys_jetid[i-1]);
  h1_z_ptbinned_sys_jes_sq[i-1]->Multiply(h1_z_ptbinned_sys_jes[i-1], h1_z_ptbinned_sys_jes[i-1]);
  h1_z_ptbinned_sys_trackingup_sq[i-1]->Multiply(h1_z_ptbinned_sys_trackingup[i-1], h1_z_ptbinned_sys_trackingup[i-1]);
  h1_z_ptbinned_sys_trackingdown_sq[i-1]->Multiply(h1_z_ptbinned_sys_trackingdown[i-1], h1_z_ptbinned_sys_trackingdown[i-1]);
  h1_z_ptbinned_sys_tracking_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_trackingup_sq[i-1]->Clone(Form("z_pt%d_sys_tracking_sq",i));  
  h1_z_ptbinned_sys_tracking_sq[i-1]->Add(h1_z_ptbinned_sys_trackingup_sq[i-1], h1_z_ptbinned_sys_trackingdown_sq[i-1]);
  h1_z_ptbinned_sys_tracking_sq[i-1]->Scale(1./2.);   
  h1_z_ptbinned_sys_tracking[i-1] = (TH1D*)h1_z_ptbinned_sys_tracking_sq[i-1]->Clone(Form("z_pt%d_ratio",i));
  GetSqrtHist(h1_z_ptbinned_sys_tracking[i-1]);  
  h1_z_ptbinned_sys_trigup_sq[i-1]->Multiply(h1_z_ptbinned_sys_trigup[i-1], h1_z_ptbinned_sys_trigup[i-1]);
  h1_z_ptbinned_sys_trigdown_sq[i-1]->Multiply(h1_z_ptbinned_sys_trigdown[i-1], h1_z_ptbinned_sys_trigdown[i-1]);
  h1_z_ptbinned_sys_trig_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_trigup_sq[i-1]->Clone(Form("z_pt%d_sys_trig_sq",i));  
  h1_z_ptbinned_sys_trig_sq[i-1]->Add(h1_z_ptbinned_sys_trigup_sq[i-1], h1_z_ptbinned_sys_trigdown_sq[i-1]);
  h1_z_ptbinned_sys_trig_sq[i-1]->Scale(1./2.);   
  h1_z_ptbinned_sys_trig[i-1] = (TH1D*)h1_z_ptbinned_sys_trig_sq[i-1]->Clone(Form("z_pt%d_ratio",i));
  GetSqrtHist(h1_z_ptbinned_sys_trig[i-1]);    
  h1_z_ptbinned_sys_sbsubnear_sq[i-1]->Multiply(h1_z_ptbinned_sys_sbsubnear[i-1], h1_z_ptbinned_sys_sbsubnear[i-1]);
  h1_z_ptbinned_sys_sbsubfar_sq[i-1]->Multiply(h1_z_ptbinned_sys_sbsubfar[i-1], h1_z_ptbinned_sys_sbsubfar[i-1]);
  h1_z_ptbinned_sys_sbsub_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_sbsubnear_sq[i-1]->Clone(Form("z_pt%d_sys_sbsub_sq",i));  
  h1_z_ptbinned_sys_sbsub_sq[i-1]->Add(h1_z_ptbinned_sys_sbsubnear_sq[i-1], h1_z_ptbinned_sys_sbsubfar_sq[i-1]);
  h1_z_ptbinned_sys_sbsub_sq[i-1]->Scale(1./2.);   
  h1_z_ptbinned_sys_sbsub[i-1] = (TH1D*)h1_z_ptbinned_sys_sbsub_sq[i-1]->Clone(Form("z_pt%d_ratio",i));  
  GetSqrtHist(h1_z_ptbinned_sys_sbsub[i-1]);    
  h1_z_ptbinned_sys_fitmodel_sq[i-1]->Multiply(h1_z_ptbinned_sys_fitmodel[i-1], h1_z_ptbinned_sys_fitmodel[i-1]);
  h1_z_ptbinned_sys_pidup_sq[i-1]->Multiply(h1_z_ptbinned_sys_pidup[i-1], h1_z_ptbinned_sys_pidup[i-1]);
  h1_z_ptbinned_sys_piddown_sq[i-1]->Multiply(h1_z_ptbinned_sys_piddown[i-1], h1_z_ptbinned_sys_piddown[i-1]);
  h1_z_ptbinned_sys_pid_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_pidup_sq[i-1]->Clone(Form("z_pt%d_sys_pid_sq",i));  
  h1_z_ptbinned_sys_pid_sq[i-1]->Add(h1_z_ptbinned_sys_pidup_sq[i-1], h1_z_ptbinned_sys_piddown_sq[i-1]);
  h1_z_ptbinned_sys_pid_sq[i-1]->Scale(1./2.);   
  h1_z_ptbinned_sys_pid[i-1] = (TH1D*)h1_z_ptbinned_sys_pid_sq[i-1]->Clone(Form("z_pt%d_ratio",i));
  GetSqrtHist(h1_z_ptbinned_sys_pid[i-1]);     
  h1_z_ptbinned_sys_recsel_sq[i-1]->Multiply(h1_z_ptbinned_sys_recsel[i-1], h1_z_ptbinned_sys_recsel[i-1]);
  h1_z_ptbinned_sys_prior_sq[i-1]->Multiply(h1_z_ptbinned_sys_prior[i-1], h1_z_ptbinned_sys_prior[i-1]);
  h1_z_ptbinned_sys_iterhigh_sq[i-1]->Multiply(h1_z_ptbinned_sys_iterhigh[i-1], h1_z_ptbinned_sys_iterhigh[i-1]);
  h1_z_ptbinned_sys_iterlow_sq[i-1]->Multiply(h1_z_ptbinned_sys_iterlow[i-1], h1_z_ptbinned_sys_iterlow[i-1]);
  h1_z_ptbinned_sys_iter_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_iterhigh_sq[i-1]->Clone(Form("z_pt%d_sys_iter_sq",i));  
  h1_z_ptbinned_sys_iter_sq[i-1]->Add(h1_z_ptbinned_sys_iterhigh_sq[i-1], h1_z_ptbinned_sys_iterlow_sq[i-1]);
  h1_z_ptbinned_sys_iter_sq[i-1]->Scale(1./2.);
  h1_z_ptbinned_sys_iter[i-1] = (TH1D*)h1_z_ptbinned_sys_iter_sq[i-1]->Clone(Form("z_pt%d_ratio",i));
  GetSqrtHist(h1_z_ptbinned_sys_iter[i-1]);   

  h1_z_ptbinned_sys_closure_sq[i-1]->Multiply(h1_z_ptbinned_sys_closure[i-1], h1_z_ptbinned_sys_closure[i-1]);
  h1_z_ptbinned_sys_shapeclosure_sq[i-1]->Multiply(h1_z_ptbinned_sys_shapeclosure[i-1], h1_z_ptbinned_sys_shapeclosure[i-1]);
  h1_z_ptbinned_sys_unfold_sq[i-1] = (TH1D *)h1_z_ptbinned_sys_closure_sq[i-1]->Clone(Form("z_pt%d_sys_unfold_sq", i));  
  h1_z_ptbinned_sys_unfold_sq[i-1]->Add(h1_z_ptbinned_sys_shapeclosure_sq[i-1]);
  h1_z_ptbinned_sys_unfold_sq[i-1]->Add(h1_z_ptbinned_sys_prior_sq[i-1]);
  h1_z_ptbinned_sys_unfold_sq[i-1]->Add(h1_z_ptbinned_sys_iter_sq[i-1]);
  
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_jetid_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_jer_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_jes_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_tracking_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_trig_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_sbsub_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_fitmodel_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_pid_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_recsel_sq[i-1]);
  h1_z_ptbinned_sys_total[i-1]->Add(h1_z_ptbinned_sys_unfold_sq[i-1]);
  GetSqrtHist(h1_z_ptbinned_sys_total[i-1]);
  
  
  SetHistConst(h1_jt_ptbinned_sys_total[i-1], 0.);
  h1_jt_ptbinned_sys_jer_sq[i-1]->Multiply(h1_jt_ptbinned_sys_jer[i-1], h1_jt_ptbinned_sys_jer[i-1]);
  h1_jt_ptbinned_sys_jetid_sq[i-1]->Multiply(h1_jt_ptbinned_sys_jetid[i-1], h1_jt_ptbinned_sys_jetid[i-1]);
  h1_jt_ptbinned_sys_jes_sq[i-1]->Multiply(h1_jt_ptbinned_sys_jes[i-1], h1_jt_ptbinned_sys_jes[i-1]);
  h1_jt_ptbinned_sys_trackingup_sq[i-1]->Multiply(h1_jt_ptbinned_sys_trackingup[i-1], h1_jt_ptbinned_sys_trackingup[i-1]);
  h1_jt_ptbinned_sys_trackingdown_sq[i-1]->Multiply(h1_jt_ptbinned_sys_trackingdown[i-1], h1_jt_ptbinned_sys_trackingdown[i-1]);
  h1_jt_ptbinned_sys_tracking_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_trackingup_sq[i-1]->Clone(Form("jt_pt%d_sys_tracking_sq",i));  
  h1_jt_ptbinned_sys_tracking_sq[i-1]->Add(h1_jt_ptbinned_sys_trackingup_sq[i-1], h1_jt_ptbinned_sys_trackingdown_sq[i-1]);
  h1_jt_ptbinned_sys_tracking_sq[i-1]->Scale(1./2.);   
  h1_jt_ptbinned_sys_tracking[i-1] = (TH1D*)h1_jt_ptbinned_sys_tracking_sq[i-1]->Clone(Form("jt_pt%d_ratio",i));
  GetSqrtHist(h1_jt_ptbinned_sys_tracking[i-1]);  
  h1_jt_ptbinned_sys_trigup_sq[i-1]->Multiply(h1_jt_ptbinned_sys_trigup[i-1], h1_jt_ptbinned_sys_trigup[i-1]);
  h1_jt_ptbinned_sys_trigdown_sq[i-1]->Multiply(h1_jt_ptbinned_sys_trigdown[i-1], h1_jt_ptbinned_sys_trigdown[i-1]);
  h1_jt_ptbinned_sys_trig_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_trigup_sq[i-1]->Clone(Form("jt_pt%d_sys_trig_sq",i));  
  h1_jt_ptbinned_sys_trig_sq[i-1]->Add(h1_jt_ptbinned_sys_trigup_sq[i-1], h1_jt_ptbinned_sys_trigdown_sq[i-1]);
  h1_jt_ptbinned_sys_trig_sq[i-1]->Scale(1./2.);   
  h1_jt_ptbinned_sys_trig[i-1] = (TH1D*)h1_jt_ptbinned_sys_trig_sq[i-1]->Clone(Form("jt_pt%d_ratio",i));
  GetSqrtHist(h1_jt_ptbinned_sys_trig[i-1]);    
  h1_jt_ptbinned_sys_sbsubnear_sq[i-1]->Multiply(h1_jt_ptbinned_sys_sbsubnear[i-1], h1_jt_ptbinned_sys_sbsubnear[i-1]);
  h1_jt_ptbinned_sys_sbsubfar_sq[i-1]->Multiply(h1_jt_ptbinned_sys_sbsubfar[i-1], h1_jt_ptbinned_sys_sbsubfar[i-1]);
  h1_jt_ptbinned_sys_sbsub_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_sbsubnear_sq[i-1]->Clone(Form("jt_pt%d_sys_sbsub_sq",i));  
  h1_jt_ptbinned_sys_sbsub_sq[i-1]->Add(h1_jt_ptbinned_sys_sbsubnear_sq[i-1], h1_jt_ptbinned_sys_sbsubfar_sq[i-1]);
  h1_jt_ptbinned_sys_sbsub_sq[i-1]->Scale(1./2.);   
  h1_jt_ptbinned_sys_sbsub[i-1] = (TH1D*)h1_jt_ptbinned_sys_sbsub_sq[i-1]->Clone(Form("jt_pt%d_ratio",i));
  GetSqrtHist(h1_jt_ptbinned_sys_sbsub[i-1]);    
  h1_jt_ptbinned_sys_fitmodel_sq[i-1]->Multiply(h1_jt_ptbinned_sys_fitmodel[i-1], h1_jt_ptbinned_sys_fitmodel[i-1]);
  h1_jt_ptbinned_sys_pidup_sq[i-1]->Multiply(h1_jt_ptbinned_sys_pidup[i-1], h1_jt_ptbinned_sys_pidup[i-1]);
  h1_jt_ptbinned_sys_piddown_sq[i-1]->Multiply(h1_jt_ptbinned_sys_piddown[i-1], h1_jt_ptbinned_sys_piddown[i-1]);
  h1_jt_ptbinned_sys_pid_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_pidup_sq[i-1]->Clone(Form("jt_pt%d_sys_pid_sq",i));  
  h1_jt_ptbinned_sys_pid_sq[i-1]->Add(h1_jt_ptbinned_sys_pidup_sq[i-1], h1_jt_ptbinned_sys_piddown_sq[i-1]);
  h1_jt_ptbinned_sys_pid_sq[i-1]->Scale(1./2.);   
  h1_jt_ptbinned_sys_pid[i-1] = (TH1D*)h1_jt_ptbinned_sys_pid_sq[i-1]->Clone(Form("jt_pt%d_ratio",i));
  GetSqrtHist(h1_jt_ptbinned_sys_pid[i-1]);     
  h1_jt_ptbinned_sys_recsel_sq[i-1]->Multiply(h1_jt_ptbinned_sys_recsel[i-1], h1_jt_ptbinned_sys_recsel[i-1]);
  h1_jt_ptbinned_sys_prior_sq[i-1]->Multiply(h1_jt_ptbinned_sys_prior[i-1], h1_jt_ptbinned_sys_prior[i-1]);
  h1_jt_ptbinned_sys_iterhigh_sq[i-1]->Multiply(h1_jt_ptbinned_sys_iterhigh[i-1], h1_jt_ptbinned_sys_iterhigh[i-1]);
  h1_jt_ptbinned_sys_iterlow_sq[i-1]->Multiply(h1_jt_ptbinned_sys_iterlow[i-1], h1_jt_ptbinned_sys_iterlow[i-1]);
  h1_jt_ptbinned_sys_iter_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_iterhigh_sq[i-1]->Clone(Form("jt_pt%d_sys_iter_sq",i));  
  h1_jt_ptbinned_sys_iter_sq[i-1]->Add(h1_jt_ptbinned_sys_iterhigh_sq[i-1], h1_jt_ptbinned_sys_iterlow_sq[i-1]);
  h1_jt_ptbinned_sys_iter_sq[i-1]->Scale(1./2.);
  h1_jt_ptbinned_sys_iter[i-1] = (TH1D*)h1_jt_ptbinned_sys_iter_sq[i-1]->Clone(Form("jt_pt%d_ratio",i));
  GetSqrtHist(h1_jt_ptbinned_sys_iter[i-1]);  

  h1_jt_ptbinned_sys_closure_sq[i-1]->Multiply(h1_jt_ptbinned_sys_closure[i-1], h1_jt_ptbinned_sys_closure[i-1]);
  h1_jt_ptbinned_sys_shapeclosure_sq[i-1]->Multiply(h1_jt_ptbinned_sys_shapeclosure[i-1], h1_jt_ptbinned_sys_shapeclosure[i-1]);
  h1_jt_ptbinned_sys_unfold_sq[i-1] = (TH1D *)h1_jt_ptbinned_sys_closure_sq[i-1]->Clone(Form("jt_pt%d_sys_unfold_sq", i)); 
  h1_jt_ptbinned_sys_unfold_sq[i-1]->Add(h1_jt_ptbinned_sys_shapeclosure_sq[i-1]);
  h1_jt_ptbinned_sys_unfold_sq[i-1]->Add(h1_jt_ptbinned_sys_prior_sq[i-1]);
  h1_jt_ptbinned_sys_unfold_sq[i-1]->Add(h1_jt_ptbinned_sys_iter_sq[i-1]);
  
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_jetid_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_jer_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_jes_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_tracking_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_trig_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_sbsub_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_fitmodel_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_pid_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_recsel_sq[i-1]);
  h1_jt_ptbinned_sys_total[i-1]->Add(h1_jt_ptbinned_sys_unfold_sq[i-1]);
  GetSqrtHist(h1_jt_ptbinned_sys_total[i-1]);

  
  SetHistConst(h1_r_ptbinned_sys_total[i-1], 0.);
  h1_r_ptbinned_sys_jer_sq[i-1]->Multiply(h1_r_ptbinned_sys_jer[i-1], h1_r_ptbinned_sys_jer[i-1]);
  h1_r_ptbinned_sys_jetid_sq[i-1]->Multiply(h1_r_ptbinned_sys_jetid[i-1], h1_r_ptbinned_sys_jetid[i-1]);
  h1_r_ptbinned_sys_jes_sq[i-1]->Multiply(h1_r_ptbinned_sys_jes[i-1], h1_r_ptbinned_sys_jes[i-1]);
  h1_r_ptbinned_sys_trackingup_sq[i-1]->Multiply(h1_r_ptbinned_sys_trackingup[i-1], h1_r_ptbinned_sys_trackingup[i-1]);
  h1_r_ptbinned_sys_trackingdown_sq[i-1]->Multiply(h1_r_ptbinned_sys_trackingdown[i-1], h1_r_ptbinned_sys_trackingdown[i-1]);
  h1_r_ptbinned_sys_tracking_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_trackingup_sq[i-1]->Clone(Form("r_pt%d_sys_tracking_sq",i));  
  h1_r_ptbinned_sys_tracking_sq[i-1]->Add(h1_r_ptbinned_sys_trackingup_sq[i-1], h1_r_ptbinned_sys_trackingdown_sq[i-1]);
  h1_r_ptbinned_sys_tracking_sq[i-1]->Scale(1./2.);   
  h1_r_ptbinned_sys_tracking[i-1] = (TH1D*)h1_r_ptbinned_sys_tracking_sq[i-1]->Clone(Form("r_pt%d_ratio",i));
  GetSqrtHist(h1_r_ptbinned_sys_tracking[i-1]);  
  h1_r_ptbinned_sys_trigup_sq[i-1]->Multiply(h1_r_ptbinned_sys_trigup[i-1], h1_r_ptbinned_sys_trigup[i-1]);
  h1_r_ptbinned_sys_trigdown_sq[i-1]->Multiply(h1_r_ptbinned_sys_trigdown[i-1], h1_r_ptbinned_sys_trigdown[i-1]);
  h1_r_ptbinned_sys_trig_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_trigup_sq[i-1]->Clone(Form("r_pt%d_sys_trig_sq",i));  
  h1_r_ptbinned_sys_trig_sq[i-1]->Add(h1_r_ptbinned_sys_trigup_sq[i-1], h1_r_ptbinned_sys_trigdown_sq[i-1]);
  h1_r_ptbinned_sys_trig_sq[i-1]->Scale(1./2.);   
  h1_r_ptbinned_sys_trig[i-1] = (TH1D*)h1_r_ptbinned_sys_trig_sq[i-1]->Clone(Form("r_pt%d_ratio",i));
  GetSqrtHist(h1_r_ptbinned_sys_trig[i-1]);    
  h1_r_ptbinned_sys_sbsubnear_sq[i-1]->Multiply(h1_r_ptbinned_sys_sbsubnear[i-1], h1_r_ptbinned_sys_sbsubnear[i-1]);
  h1_r_ptbinned_sys_sbsubfar_sq[i-1]->Multiply(h1_r_ptbinned_sys_sbsubfar[i-1], h1_r_ptbinned_sys_sbsubfar[i-1]);
  h1_r_ptbinned_sys_sbsub_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_sbsubnear_sq[i-1]->Clone(Form("r_pt%d_sys_sbsub_sq",i));  
  h1_r_ptbinned_sys_sbsub_sq[i-1]->Add(h1_r_ptbinned_sys_sbsubnear_sq[i-1], h1_r_ptbinned_sys_sbsubfar_sq[i-1]);
  h1_r_ptbinned_sys_sbsub_sq[i-1]->Scale(1./2.);   
  h1_r_ptbinned_sys_sbsub[i-1] = (TH1D*)h1_r_ptbinned_sys_sbsub_sq[i-1]->Clone(Form("r_pt%d_ratio",i));
  GetSqrtHist(h1_r_ptbinned_sys_sbsub[i-1]);    
  h1_r_ptbinned_sys_fitmodel_sq[i-1]->Multiply(h1_r_ptbinned_sys_fitmodel[i-1], h1_r_ptbinned_sys_fitmodel[i-1]);
  h1_r_ptbinned_sys_pidup_sq[i-1]->Multiply(h1_r_ptbinned_sys_pidup[i-1], h1_r_ptbinned_sys_pidup[i-1]);
  h1_r_ptbinned_sys_piddown_sq[i-1]->Multiply(h1_r_ptbinned_sys_piddown[i-1], h1_r_ptbinned_sys_piddown[i-1]);
  h1_r_ptbinned_sys_pid_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_pidup_sq[i-1]->Clone(Form("r_pt%d_sys_pid_sq",i));  
  h1_r_ptbinned_sys_pid_sq[i-1]->Add(h1_r_ptbinned_sys_pidup_sq[i-1], h1_r_ptbinned_sys_piddown_sq[i-1]);
  h1_r_ptbinned_sys_pid_sq[i-1]->Scale(1./2.);   
  h1_r_ptbinned_sys_pid[i-1] = (TH1D*)h1_r_ptbinned_sys_pid_sq[i-1]->Clone(Form("r_pt%d_ratio",i));
  GetSqrtHist(h1_r_ptbinned_sys_pid[i-1]);     
  h1_r_ptbinned_sys_recsel_sq[i-1]->Multiply(h1_r_ptbinned_sys_recsel[i-1], h1_r_ptbinned_sys_recsel[i-1]);
  h1_r_ptbinned_sys_prior_sq[i-1]->Multiply(h1_r_ptbinned_sys_prior[i-1], h1_r_ptbinned_sys_prior[i-1]);
  h1_r_ptbinned_sys_iterhigh_sq[i-1]->Multiply(h1_r_ptbinned_sys_iterhigh[i-1], h1_r_ptbinned_sys_iterhigh[i-1]);
  h1_r_ptbinned_sys_iterlow_sq[i-1]->Multiply(h1_r_ptbinned_sys_iterlow[i-1], h1_r_ptbinned_sys_iterlow[i-1]);
  h1_r_ptbinned_sys_iter_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_iterhigh_sq[i-1]->Clone(Form("r_pt%d_sys_iter_sq",i));  
  h1_r_ptbinned_sys_iter_sq[i-1]->Add(h1_r_ptbinned_sys_iterhigh_sq[i-1], h1_r_ptbinned_sys_iterlow_sq[i-1]);
  h1_r_ptbinned_sys_iter_sq[i-1]->Scale(1./2.);
  h1_r_ptbinned_sys_iter[i-1] = (TH1D*)h1_r_ptbinned_sys_iter_sq[i-1]->Clone(Form("r_pt%d_ratio",i));
  GetSqrtHist(h1_r_ptbinned_sys_iter[i-1]);    

  h1_r_ptbinned_sys_closure_sq[i-1]->Multiply(h1_r_ptbinned_sys_closure[i-1], h1_r_ptbinned_sys_closure[i-1]);
  h1_r_ptbinned_sys_shapeclosure_sq[i-1]->Multiply(h1_r_ptbinned_sys_shapeclosure[i-1], h1_r_ptbinned_sys_shapeclosure[i-1]);
  h1_r_ptbinned_sys_unfold_sq[i-1] = (TH1D *)h1_r_ptbinned_sys_closure_sq[i-1]->Clone(Form("r_pt%d_sys_unfold_sq", i));  
  h1_r_ptbinned_sys_unfold_sq[i-1]->Add(h1_r_ptbinned_sys_shapeclosure_sq[i-1]);
  h1_r_ptbinned_sys_unfold_sq[i-1]->Add(h1_r_ptbinned_sys_prior_sq[i-1]);
  h1_r_ptbinned_sys_unfold_sq[i-1]->Add(h1_r_ptbinned_sys_iter_sq[i-1]);
  
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_jetid_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_jer_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_jes_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_tracking_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_trig_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_sbsub_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_fitmodel_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_pid_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_recsel_sq[i-1]);
  h1_r_ptbinned_sys_total[i-1]->Add(h1_r_ptbinned_sys_unfold_sq[i-1]);
  GetSqrtHist(h1_r_ptbinned_sys_total[i-1]);
  
  
  SetHistConst(h2_zjt_ptbinned_sys_total[i-1], 0.);
  h2_zjt_ptbinned_sys_jer_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_jer[i-1], h2_zjt_ptbinned_sys_jer[i-1]);
  h2_zjt_ptbinned_sys_jetid_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_jetid[i-1], h2_zjt_ptbinned_sys_jetid[i-1]);
  h2_zjt_ptbinned_sys_jes_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_jes[i-1], h2_zjt_ptbinned_sys_jes[i-1]);
  h2_zjt_ptbinned_sys_trackingup_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_trackingup[i-1], h2_zjt_ptbinned_sys_trackingup[i-1]);
  h2_zjt_ptbinned_sys_trackingdown_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_trackingdown[i-1], h2_zjt_ptbinned_sys_trackingdown[i-1]);
  h2_zjt_ptbinned_sys_tracking_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_trackingup_sq[i-1]->Clone(Form("zjt_pt%d_sys_tracking_sq",i));  
  h2_zjt_ptbinned_sys_tracking_sq[i-1]->Add(h2_zjt_ptbinned_sys_trackingup_sq[i-1], h2_zjt_ptbinned_sys_trackingdown_sq[i-1]);
  h2_zjt_ptbinned_sys_tracking_sq[i-1]->Scale(1./2.);   
  h2_zjt_ptbinned_sys_tracking[i-1] = (TH2D*)h2_zjt_ptbinned_sys_tracking_sq[i-1]->Clone(Form("zjt_pt%d_ratio",i));
  GetSqrtHist(h2_zjt_ptbinned_sys_tracking[i-1]);  
  h2_zjt_ptbinned_sys_trigup_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_trigup[i-1], h2_zjt_ptbinned_sys_trigup[i-1]);
  h2_zjt_ptbinned_sys_trigdown_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_trigdown[i-1], h2_zjt_ptbinned_sys_trigdown[i-1]);
  h2_zjt_ptbinned_sys_trig_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_trigup_sq[i-1]->Clone(Form("zjt_pt%d_sys_trig_sq",i));  
  h2_zjt_ptbinned_sys_trig_sq[i-1]->Add(h2_zjt_ptbinned_sys_trigup_sq[i-1], h2_zjt_ptbinned_sys_trigdown_sq[i-1]);
  h2_zjt_ptbinned_sys_trig_sq[i-1]->Scale(1./2.);   
  h2_zjt_ptbinned_sys_trig[i-1] = (TH2D*)h2_zjt_ptbinned_sys_trig_sq[i-1]->Clone(Form("zjt_pt%d_ratio",i));
  GetSqrtHist(h2_zjt_ptbinned_sys_trig[i-1]);    
  h2_zjt_ptbinned_sys_sbsubnear_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_sbsubnear[i-1], h2_zjt_ptbinned_sys_sbsubnear[i-1]);
  h2_zjt_ptbinned_sys_sbsubfar_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_sbsubfar[i-1], h2_zjt_ptbinned_sys_sbsubfar[i-1]);
  h2_zjt_ptbinned_sys_sbsub_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_sbsubnear_sq[i-1]->Clone(Form("zjt_pt%d_sys_sbsub_sq",i));  
  h2_zjt_ptbinned_sys_sbsub_sq[i-1]->Add(h2_zjt_ptbinned_sys_sbsubnear_sq[i-1], h2_zjt_ptbinned_sys_sbsubfar_sq[i-1]);
  h2_zjt_ptbinned_sys_sbsub_sq[i-1]->Scale(1./2.);   
  h2_zjt_ptbinned_sys_sbsub[i-1] = (TH2D*)h2_zjt_ptbinned_sys_sbsub_sq[i-1]->Clone(Form("zjt_pt%d_ratio",i));
  GetSqrtHist(h2_zjt_ptbinned_sys_sbsub[i-1]);    
  h2_zjt_ptbinned_sys_fitmodel_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_fitmodel[i-1], h2_zjt_ptbinned_sys_fitmodel[i-1]);
  h2_zjt_ptbinned_sys_pidup_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_pidup[i-1], h2_zjt_ptbinned_sys_pidup[i-1]);
  h2_zjt_ptbinned_sys_piddown_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_piddown[i-1], h2_zjt_ptbinned_sys_piddown[i-1]);
  h2_zjt_ptbinned_sys_pid_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_pidup_sq[i-1]->Clone(Form("zjt_pt%d_sys_pid_sq",i));  
  h2_zjt_ptbinned_sys_pid_sq[i-1]->Add(h2_zjt_ptbinned_sys_pidup_sq[i-1], h2_zjt_ptbinned_sys_piddown_sq[i-1]);
  h2_zjt_ptbinned_sys_pid_sq[i-1]->Scale(1./2.);   
  h2_zjt_ptbinned_sys_pid[i-1] = (TH2D*)h2_zjt_ptbinned_sys_pid_sq[i-1]->Clone(Form("zjt_pt%d_ratio",i));
  GetSqrtHist(h2_zjt_ptbinned_sys_pid[i-1]);     
  h2_zjt_ptbinned_sys_recsel_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_recsel[i-1], h2_zjt_ptbinned_sys_recsel[i-1]);
  h2_zjt_ptbinned_sys_prior_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_prior[i-1], h2_zjt_ptbinned_sys_prior[i-1]);
  h2_zjt_ptbinned_sys_iterhigh_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_iterhigh[i-1], h2_zjt_ptbinned_sys_iterhigh[i-1]);
  h2_zjt_ptbinned_sys_iterlow_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_iterlow[i-1], h2_zjt_ptbinned_sys_iterlow[i-1]);
  h2_zjt_ptbinned_sys_iter_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_iterhigh_sq[i-1]->Clone(Form("zjt_pt%d_sys_iter_sq",i));  
  h2_zjt_ptbinned_sys_iter_sq[i-1]->Add(h2_zjt_ptbinned_sys_iterhigh_sq[i-1], h2_zjt_ptbinned_sys_iterlow_sq[i-1]);
  h2_zjt_ptbinned_sys_iter_sq[i-1]->Scale(1./2.);
  h2_zjt_ptbinned_sys_iter[i-1] = (TH2D*)h2_zjt_ptbinned_sys_iter_sq[i-1]->Clone(Form("zjt_pt%d_ratio",i));
  GetSqrtHist(h2_zjt_ptbinned_sys_iter[i-1]);      

  h2_zjt_ptbinned_sys_closure_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_closure[i-1], h2_zjt_ptbinned_sys_closure[i-1]);
  h2_zjt_ptbinned_sys_shapeclosure_sq[i-1]->Multiply(h2_zjt_ptbinned_sys_shapeclosure[i-1], h2_zjt_ptbinned_sys_shapeclosure[i-1]);
  h2_zjt_ptbinned_sys_unfold_sq[i-1] = (TH2D *)h2_zjt_ptbinned_sys_closure_sq[i-1]->Clone(Form("zjt_pt%d_sys_unfold_sq", i));  
  h2_zjt_ptbinned_sys_unfold_sq[i-1]->Add(h2_zjt_ptbinned_sys_shapeclosure_sq[i-1]);
  h2_zjt_ptbinned_sys_unfold_sq[i-1]->Add(h2_zjt_ptbinned_sys_prior_sq[i-1]);
  h2_zjt_ptbinned_sys_unfold_sq[i-1]->Add(h2_zjt_ptbinned_sys_iter_sq[i-1]);
  
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_jetid_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_jer_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_jes_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_tracking_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_trig_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_sbsub_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_fitmodel_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_pid_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_recsel_sq[i-1]);
  h2_zjt_ptbinned_sys_total[i-1]->Add(h2_zjt_ptbinned_sys_unfold_sq[i-1]);
  GetSqrtHist(h2_zjt_ptbinned_sys_total[i-1]);
  
  
  SetHistConst(h2_zr_ptbinned_sys_total[i-1], 0.);
  h2_zr_ptbinned_sys_jer_sq[i-1]->Multiply(h2_zr_ptbinned_sys_jer[i-1], h2_zr_ptbinned_sys_jer[i-1]);
  h2_zr_ptbinned_sys_jetid_sq[i-1]->Multiply(h2_zr_ptbinned_sys_jetid[i-1], h2_zr_ptbinned_sys_jetid[i-1]);
  h2_zr_ptbinned_sys_jes_sq[i-1]->Multiply(h2_zr_ptbinned_sys_jes[i-1], h2_zr_ptbinned_sys_jes[i-1]);
  h2_zr_ptbinned_sys_trackingup_sq[i-1]->Multiply(h2_zr_ptbinned_sys_trackingup[i-1], h2_zr_ptbinned_sys_trackingup[i-1]);
  h2_zr_ptbinned_sys_trackingdown_sq[i-1]->Multiply(h2_zr_ptbinned_sys_trackingdown[i-1], h2_zr_ptbinned_sys_trackingdown[i-1]);
  h2_zr_ptbinned_sys_tracking_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_trackingup_sq[i-1]->Clone(Form("zr_pt%d_sys_tracking_sq",i));  
  h2_zr_ptbinned_sys_tracking_sq[i-1]->Add(h2_zr_ptbinned_sys_trackingup_sq[i-1], h2_zr_ptbinned_sys_trackingdown_sq[i-1]);
  h2_zr_ptbinned_sys_tracking_sq[i-1]->Scale(1./2.);   
  h2_zr_ptbinned_sys_tracking[i-1] = (TH2D*)h2_zr_ptbinned_sys_tracking_sq[i-1]->Clone(Form("zr_pt%d_ratio",i));
  GetSqrtHist(h2_zr_ptbinned_sys_tracking[i-1]);  
  h2_zr_ptbinned_sys_trigup_sq[i-1]->Multiply(h2_zr_ptbinned_sys_trigup[i-1], h2_zr_ptbinned_sys_trigup[i-1]);
  h2_zr_ptbinned_sys_trigdown_sq[i-1]->Multiply(h2_zr_ptbinned_sys_trigdown[i-1], h2_zr_ptbinned_sys_trigdown[i-1]);
  h2_zr_ptbinned_sys_trig_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_trigup_sq[i-1]->Clone(Form("zr_pt%d_sys_trig_sq",i));  
  h2_zr_ptbinned_sys_trig_sq[i-1]->Add(h2_zr_ptbinned_sys_trigup_sq[i-1], h2_zr_ptbinned_sys_trigdown_sq[i-1]);
  h2_zr_ptbinned_sys_trig_sq[i-1]->Scale(1./2.);   
  h2_zr_ptbinned_sys_trig[i-1] = (TH2D*)h2_zr_ptbinned_sys_trig_sq[i-1]->Clone(Form("zr_pt%d_ratio",i));
  GetSqrtHist(h2_zr_ptbinned_sys_trig[i-1]);    
  h2_zr_ptbinned_sys_sbsubnear_sq[i-1]->Multiply(h2_zr_ptbinned_sys_sbsubnear[i-1], h2_zr_ptbinned_sys_sbsubnear[i-1]);
  h2_zr_ptbinned_sys_sbsubfar_sq[i-1]->Multiply(h2_zr_ptbinned_sys_sbsubfar[i-1], h2_zr_ptbinned_sys_sbsubfar[i-1]);
  h2_zr_ptbinned_sys_sbsub_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_sbsubnear_sq[i-1]->Clone(Form("zr_pt%d_sys_sbsub_sq",i));  
  h2_zr_ptbinned_sys_sbsub_sq[i-1]->Add(h2_zr_ptbinned_sys_sbsubnear_sq[i-1], h2_zr_ptbinned_sys_sbsubfar_sq[i-1]);
  h2_zr_ptbinned_sys_sbsub_sq[i-1]->Scale(1./2.);   
  h2_zr_ptbinned_sys_sbsub[i-1] = (TH2D*)h2_zr_ptbinned_sys_sbsub_sq[i-1]->Clone(Form("zr_pt%d_ratio",i));
  GetSqrtHist(h2_zr_ptbinned_sys_sbsub[i-1]);    
  h2_zr_ptbinned_sys_fitmodel_sq[i-1]->Multiply(h2_zr_ptbinned_sys_fitmodel[i-1], h2_zr_ptbinned_sys_fitmodel[i-1]);
  h2_zr_ptbinned_sys_pidup_sq[i-1]->Multiply(h2_zr_ptbinned_sys_pidup[i-1], h2_zr_ptbinned_sys_pidup[i-1]);
  h2_zr_ptbinned_sys_piddown_sq[i-1]->Multiply(h2_zr_ptbinned_sys_piddown[i-1], h2_zr_ptbinned_sys_piddown[i-1]);
  h2_zr_ptbinned_sys_pid_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_pidup_sq[i-1]->Clone(Form("zr_pt%d_sys_pid_sq",i));  
  h2_zr_ptbinned_sys_pid_sq[i-1]->Add(h2_zr_ptbinned_sys_pidup_sq[i-1], h2_zr_ptbinned_sys_piddown_sq[i-1]);
  h2_zr_ptbinned_sys_pid_sq[i-1]->Scale(1./2.);   
  h2_zr_ptbinned_sys_pid[i-1] = (TH2D*)h2_zr_ptbinned_sys_pid_sq[i-1]->Clone(Form("zr_pt%d_ratio",i));
  GetSqrtHist(h2_zr_ptbinned_sys_pid[i-1]);     
  h2_zr_ptbinned_sys_recsel_sq[i-1]->Multiply(h2_zr_ptbinned_sys_recsel[i-1], h2_zr_ptbinned_sys_recsel[i-1]);
  h2_zr_ptbinned_sys_prior_sq[i-1]->Multiply(h2_zr_ptbinned_sys_prior[i-1], h2_zr_ptbinned_sys_prior[i-1]);
  h2_zr_ptbinned_sys_iterhigh_sq[i-1]->Multiply(h2_zr_ptbinned_sys_iterhigh[i-1], h2_zr_ptbinned_sys_iterhigh[i-1]);
  h2_zr_ptbinned_sys_iterlow_sq[i-1]->Multiply(h2_zr_ptbinned_sys_iterlow[i-1], h2_zr_ptbinned_sys_iterlow[i-1]);
  h2_zr_ptbinned_sys_iter_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_iterhigh_sq[i-1]->Clone(Form("zr_pt%d_sys_iter_sq",i));  
  h2_zr_ptbinned_sys_iter_sq[i-1]->Add(h2_zr_ptbinned_sys_iterhigh_sq[i-1], h2_zr_ptbinned_sys_iterlow_sq[i-1]);
  h2_zr_ptbinned_sys_iter_sq[i-1]->Scale(1./2.);
  h2_zr_ptbinned_sys_iter[i-1] = (TH2D*)h2_zr_ptbinned_sys_iter_sq[i-1]->Clone(Form("zr_pt%d_ratio",i));
  GetSqrtHist(h2_zr_ptbinned_sys_iter[i-1]);    

  h2_zr_ptbinned_sys_closure_sq[i-1]->Multiply(h2_zr_ptbinned_sys_closure[i-1], h2_zr_ptbinned_sys_closure[i-1]);
  h2_zr_ptbinned_sys_shapeclosure_sq[i-1]->Multiply(h2_zr_ptbinned_sys_shapeclosure[i-1], h2_zr_ptbinned_sys_shapeclosure[i-1]);
  h2_zr_ptbinned_sys_unfold_sq[i-1] = (TH2D *)h2_zr_ptbinned_sys_closure_sq[i-1]->Clone(Form("zr_pt%d_sys_unfold_sq", i)); 
  h2_zr_ptbinned_sys_unfold_sq[i-1]->Add(h2_zr_ptbinned_sys_shapeclosure_sq[i-1]); 
  h2_zr_ptbinned_sys_unfold_sq[i-1]->Add(h2_zr_ptbinned_sys_prior_sq[i-1]);
  h2_zr_ptbinned_sys_unfold_sq[i-1]->Add(h2_zr_ptbinned_sys_iter_sq[i-1]);
  
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_jetid_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_jer_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_jes_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_tracking_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_trig_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_sbsub_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_fitmodel_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_pid_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_recsel_sq[i-1]);
  h2_zr_ptbinned_sys_total[i-1]->Add(h2_zr_ptbinned_sys_unfold_sq[i-1]);
  GetSqrtHist(h2_zr_ptbinned_sys_total[i-1]);

  
  SetHistConst(h2_jtr_ptbinned_sys_total[i-1], 0.);
  h2_jtr_ptbinned_sys_jer_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_jer[i-1], h2_jtr_ptbinned_sys_jer[i-1]);
  h2_jtr_ptbinned_sys_jetid_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_jetid[i-1], h2_jtr_ptbinned_sys_jetid[i-1]);
  h2_jtr_ptbinned_sys_jes_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_jes[i-1], h2_jtr_ptbinned_sys_jes[i-1]);
  h2_jtr_ptbinned_sys_trackingup_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_trackingup[i-1], h2_jtr_ptbinned_sys_trackingup[i-1]);
  h2_jtr_ptbinned_sys_trackingdown_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_trackingdown[i-1], h2_jtr_ptbinned_sys_trackingdown[i-1]);
  h2_jtr_ptbinned_sys_tracking_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_trackingup_sq[i-1]->Clone(Form("jtr_pt%d_sys_tracking_sq",i));  
  h2_jtr_ptbinned_sys_tracking_sq[i-1]->Add(h2_jtr_ptbinned_sys_trackingup_sq[i-1], h2_jtr_ptbinned_sys_trackingdown_sq[i-1]);
  h2_jtr_ptbinned_sys_tracking_sq[i-1]->Scale(1./2.);   
  h2_jtr_ptbinned_sys_tracking[i-1] = (TH2D*)h2_jtr_ptbinned_sys_tracking_sq[i-1]->Clone(Form("jtr_pt%d_ratio",i));
  GetSqrtHist(h2_jtr_ptbinned_sys_tracking[i-1]);  
  h2_jtr_ptbinned_sys_trigup_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_trigup[i-1], h2_jtr_ptbinned_sys_trigup[i-1]);
  h2_jtr_ptbinned_sys_trigdown_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_trigdown[i-1], h2_jtr_ptbinned_sys_trigdown[i-1]);
  h2_jtr_ptbinned_sys_trig_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_trigup_sq[i-1]->Clone(Form("jtr_pt%d_sys_trig_sq",i));  
  h2_jtr_ptbinned_sys_trig_sq[i-1]->Add(h2_jtr_ptbinned_sys_trigup_sq[i-1], h2_jtr_ptbinned_sys_trigdown_sq[i-1]);
  h2_jtr_ptbinned_sys_trig_sq[i-1]->Scale(1./2.);   
  h2_jtr_ptbinned_sys_trig[i-1] = (TH2D*)h2_jtr_ptbinned_sys_trig_sq[i-1]->Clone(Form("jtr_pt%d_ratio",i));
  GetSqrtHist(h2_jtr_ptbinned_sys_trig[i-1]);    
  h2_jtr_ptbinned_sys_sbsubnear_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_sbsubnear[i-1], h2_jtr_ptbinned_sys_sbsubnear[i-1]);
  h2_jtr_ptbinned_sys_sbsubfar_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_sbsubfar[i-1], h2_jtr_ptbinned_sys_sbsubfar[i-1]);
  h2_jtr_ptbinned_sys_sbsub_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_sbsubnear_sq[i-1]->Clone(Form("jtr_pt%d_sys_sbsub_sq",i));  
  h2_jtr_ptbinned_sys_sbsub_sq[i-1]->Add(h2_jtr_ptbinned_sys_sbsubnear_sq[i-1], h2_jtr_ptbinned_sys_sbsubfar_sq[i-1]);
  h2_jtr_ptbinned_sys_sbsub_sq[i-1]->Scale(1./2.);   
  h2_jtr_ptbinned_sys_sbsub[i-1] = (TH2D*)h2_jtr_ptbinned_sys_sbsub_sq[i-1]->Clone(Form("jtr_pt%d_ratio",i));
  GetSqrtHist(h2_jtr_ptbinned_sys_sbsub[i-1]);
  h2_jtr_ptbinned_sys_fitmodel_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_fitmodel[i-1], h2_jtr_ptbinned_sys_fitmodel[i-1]);
  h2_jtr_ptbinned_sys_pidup_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_pidup[i-1], h2_jtr_ptbinned_sys_pidup[i-1]);
  h2_jtr_ptbinned_sys_piddown_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_piddown[i-1], h2_jtr_ptbinned_sys_piddown[i-1]);
  h2_jtr_ptbinned_sys_pid_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_pidup_sq[i-1]->Clone(Form("jtr_pt%d_sys_pid_sq",i));  
  h2_jtr_ptbinned_sys_pid_sq[i-1]->Add(h2_jtr_ptbinned_sys_pidup_sq[i-1], h2_jtr_ptbinned_sys_piddown_sq[i-1]);
  h2_jtr_ptbinned_sys_pid_sq[i-1]->Scale(1./2.);   
  h2_jtr_ptbinned_sys_pid[i-1] = (TH2D*)h2_jtr_ptbinned_sys_pid_sq[i-1]->Clone(Form("jtr_pt%d_ratio",i));
  GetSqrtHist(h2_jtr_ptbinned_sys_pid[i-1]);     
  h2_jtr_ptbinned_sys_recsel_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_recsel[i-1], h2_jtr_ptbinned_sys_recsel[i-1]);
  h2_jtr_ptbinned_sys_prior_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_prior[i-1], h2_jtr_ptbinned_sys_prior[i-1]);
  h2_jtr_ptbinned_sys_iterhigh_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_iterhigh[i-1], h2_jtr_ptbinned_sys_iterhigh[i-1]);
  h2_jtr_ptbinned_sys_iterlow_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_iterlow[i-1], h2_jtr_ptbinned_sys_iterlow[i-1]);
  h2_jtr_ptbinned_sys_iter_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_iterhigh_sq[i-1]->Clone(Form("jtr_pt%d_sys_iter_sq",i));  
  h2_jtr_ptbinned_sys_iter_sq[i-1]->Add(h2_jtr_ptbinned_sys_iterhigh_sq[i-1], h2_jtr_ptbinned_sys_iterlow_sq[i-1]);
  h2_jtr_ptbinned_sys_iter_sq[i-1]->Scale(1./2.);
  h2_jtr_ptbinned_sys_iter[i-1] = (TH2D*)h2_jtr_ptbinned_sys_iter_sq[i-1]->Clone(Form("jtr_pt%d_ratio",i));
  GetSqrtHist(h2_jtr_ptbinned_sys_iter[i-1]);    

  h2_jtr_ptbinned_sys_closure_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_closure[i-1], h2_jtr_ptbinned_sys_closure[i-1]);
  h2_jtr_ptbinned_sys_shapeclosure_sq[i-1]->Multiply(h2_jtr_ptbinned_sys_shapeclosure[i-1], h2_jtr_ptbinned_sys_shapeclosure[i-1]);
  h2_jtr_ptbinned_sys_unfold_sq[i-1] = (TH2D *)h2_jtr_ptbinned_sys_closure_sq[i-1]->Clone(Form("jtr_pt%d_sys_unfold_sq", i)); 
  h2_jtr_ptbinned_sys_unfold_sq[i-1]->Add(h2_jtr_ptbinned_sys_shapeclosure_sq[i-1]); 
  h2_jtr_ptbinned_sys_unfold_sq[i-1]->Add(h2_jtr_ptbinned_sys_prior_sq[i-1]);
  h2_jtr_ptbinned_sys_unfold_sq[i-1]->Add(h2_jtr_ptbinned_sys_iter_sq[i-1]);
  
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_jetid_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_jer_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_jes_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_tracking_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_trig_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_sbsub_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_fitmodel_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_pid_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_recsel_sq[i-1]);
  h2_jtr_ptbinned_sys_total[i-1]->Add(h2_jtr_ptbinned_sys_unfold_sq[i-1]);
  GetSqrtHist(h2_jtr_ptbinned_sys_total[i-1]);  
  
  // Add systematic histograms to vectors, must correspond to the ordering of vec_string

  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_jetid[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_jer[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_jes[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_tracking[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_pid[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_trig[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_sbsub[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_fitmodel[i-1]);  
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_recsel[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_closure[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_shapeclosure[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_iter[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_prior[i-1]);
  vec_sys_z_ptbinned[i-1].push_back(h1_z_ptbinned_sys_total[i-1]);  
  
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_jetid[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_jer[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_jes[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_tracking[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_pid[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_trig[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_sbsub[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_fitmodel[i-1]);  
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_recsel[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_closure[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_shapeclosure[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_iter[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_prior[i-1]);
  vec_sys_jt_ptbinned[i-1].push_back(h1_jt_ptbinned_sys_total[i-1]);     
  
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_jetid[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_jer[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_jes[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_tracking[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_pid[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_trig[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_sbsub[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_fitmodel[i-1]);  
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_recsel[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_closure[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_shapeclosure[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_iter[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_prior[i-1]);
  vec_sys_r_ptbinned[i-1].push_back(h1_r_ptbinned_sys_total[i-1]);  
  

  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_jetid[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_jer[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_jes[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_tracking[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_pid[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_trig[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_sbsub[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_fitmodel[i-1]);  
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_recsel[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_closure[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_shapeclosure[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_iter[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_prior[i-1]);
  vec_sys_zjt_ptbinned[i-1].push_back(h2_zjt_ptbinned_sys_total[i-1]);  
  
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_jetid[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_jer[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_jes[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_tracking[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_pid[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_trig[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_sbsub[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_fitmodel[i-1]);  
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_recsel[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_closure[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_shapeclosure[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_iter[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_prior[i-1]);
  vec_sys_zr_ptbinned[i-1].push_back(h2_zr_ptbinned_sys_total[i-1]);     
  
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_jetid[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_jer[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_jes[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_tracking[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_pid[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_trig[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_sbsub[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_fitmodel[i-1]);  
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_recsel[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_closure[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_shapeclosure[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_iter[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_prior[i-1]);
  vec_sys_jtr_ptbinned[i-1].push_back(h2_jtr_ptbinned_sys_total[i-1]);    
  
  h1_z_ptbinned_sys_jetid[i-1]->SetName(Form("z_sys_jetid_pt%d", i));   
  h1_z_ptbinned_sys_jer[i-1]->SetName(Form("z_sys_jer_pt%d", i));   
  h1_z_ptbinned_sys_jes[i-1]->SetName(Form("z_sys_jes_pt%d", i));   
  h1_z_ptbinned_sys_tracking[i-1]->SetName(Form("z_sys_tracking_pt%d", i));   
  h1_z_ptbinned_sys_pid[i-1]->SetName(Form("z_sys_pid_pt%d", i));  
  h1_z_ptbinned_sys_sbsub[i-1]->SetName(Form("z_sys_sbsub_pt%d", i));   
  h1_z_ptbinned_sys_fitmodel[i-1]->SetName(Form("z_sys_fitmodel_pt%d", i));  
  h1_z_ptbinned_sys_recsel[i-1]->SetName(Form("z_sys_recsel_pt%d", i));       
  h1_z_ptbinned_sys_closure[i-1]->SetName(Form("z_sys_closure_pt%d", i)); 
  h1_z_ptbinned_sys_shapeclosure[i-1]->SetName(Form("z_sys_shapeclosure_pt%d", i)); 
  h1_z_ptbinned_sys_iter[i-1]->SetName(Form("z_sys_iter_pt%d", i));    
  h1_z_ptbinned_sys_prior[i-1]->SetName(Form("z_sys_prior_pt%d", i));    
  h1_z_ptbinned_sys_total[i-1]->SetName(Form("z_sys_total_pt%d", i));    
  
  h1_jt_ptbinned_sys_jetid[i-1]->SetName(Form("jt_sys_jetid_pt%d", i));   
  h1_jt_ptbinned_sys_jer[i-1]->SetName(Form("jt_sys_jer_pt%d", i));   
  h1_jt_ptbinned_sys_jes[i-1]->SetName(Form("jt_sys_jes_pt%d", i));   
  h1_jt_ptbinned_sys_tracking[i-1]->SetName(Form("jt_sys_tracking_pt%d", i));   
  h1_jt_ptbinned_sys_pid[i-1]->SetName(Form("jt_sys_pid_pt%d", i));  
  h1_jt_ptbinned_sys_sbsub[i-1]->SetName(Form("jt_sys_sbsub_pt%d", i));   
  h1_jt_ptbinned_sys_fitmodel[i-1]->SetName(Form("jt_sys_fitmodel_pt%d", i));  
  h1_jt_ptbinned_sys_recsel[i-1]->SetName(Form("jt_sys_recsel_pt%d", i));       
  h1_jt_ptbinned_sys_closure[i-1]->SetName(Form("jt_sys_closure_pt%d", i)); 
  h1_jt_ptbinned_sys_shapeclosure[i-1]->SetName(Form("jt_sys_shapeclosure_pt%d", i)); 
  h1_jt_ptbinned_sys_iter[i-1]->SetName(Form("jt_sys_iter_pt%d", i));    
  h1_jt_ptbinned_sys_prior[i-1]->SetName(Form("jt_sys_prior_pt%d", i));    
  h1_jt_ptbinned_sys_total[i-1]->SetName(Form("jt_sys_total_pt%d", i));    
  
  h1_r_ptbinned_sys_jetid[i-1]->SetName(Form("r_sys_jetid_pt%d", i));   
  h1_r_ptbinned_sys_jer[i-1]->SetName(Form("r_sys_jer_pt%d", i));   
  h1_r_ptbinned_sys_jes[i-1]->SetName(Form("r_sys_jes_pt%d", i));   
  h1_r_ptbinned_sys_tracking[i-1]->SetName(Form("r_sys_tracking_pt%d", i));   
  h1_r_ptbinned_sys_pid[i-1]->SetName(Form("r_sys_pid_pt%d", i));  
  h1_r_ptbinned_sys_sbsub[i-1]->SetName(Form("r_sys_sbsub_pt%d", i));   
  h1_r_ptbinned_sys_fitmodel[i-1]->SetName(Form("r_sys_fitmodel_pt%d", i));  
  h1_r_ptbinned_sys_recsel[i-1]->SetName(Form("r_sys_recsel_pt%d", i));       
  h1_r_ptbinned_sys_closure[i-1]->SetName(Form("r_sys_closure_pt%d", i)); 
  h1_r_ptbinned_sys_shapeclosure[i-1]->SetName(Form("r_sys_shapeclosure_pt%d", i)); 
  h1_r_ptbinned_sys_iter[i-1]->SetName(Form("r_sys_iter_pt%d", i));    
  h1_r_ptbinned_sys_prior[i-1]->SetName(Form("r_sys_prior_pt%d", i));    
  h1_r_ptbinned_sys_total[i-1]->SetName(Form("r_sys_total_pt%d", i));    
  

  h2_zjt_ptbinned_sys_jetid[i-1]->SetName(Form("zjt_sys_jetid_pt%d", i));   
  h2_zjt_ptbinned_sys_jer[i-1]->SetName(Form("zjt_sys_jer_pt%d", i));   
  h2_zjt_ptbinned_sys_jes[i-1]->SetName(Form("zjt_sys_jes_pt%d", i));   
  h2_zjt_ptbinned_sys_tracking[i-1]->SetName(Form("zjt_sys_tracking_pt%d", i));   
  h2_zjt_ptbinned_sys_pid[i-1]->SetName(Form("zjt_sys_pid_pt%d", i));  
  h2_zjt_ptbinned_sys_sbsub[i-1]->SetName(Form("zjt_sys_sbsub_pt%d", i));   
  h2_zjt_ptbinned_sys_fitmodel[i-1]->SetName(Form("zjt_sys_fitmodel_pt%d", i));  
  h2_zjt_ptbinned_sys_recsel[i-1]->SetName(Form("zjt_sys_recsel_pt%d", i));       
  h2_zjt_ptbinned_sys_closure[i-1]->SetName(Form("zjt_sys_closure_pt%d", i)); 
  h2_zjt_ptbinned_sys_shapeclosure[i-1]->SetName(Form("zjt_sys_shapeclosure_pt%d", i)); 
  h2_zjt_ptbinned_sys_iter[i-1]->SetName(Form("zjt_sys_iter_pt%d", i));    
  h2_zjt_ptbinned_sys_prior[i-1]->SetName(Form("zjt_sys_prior_pt%d", i));    
  h2_zjt_ptbinned_sys_total[i-1]->SetName(Form("zjt_sys_total_pt%d", i));    
  
  h2_zr_ptbinned_sys_jetid[i-1]->SetName(Form("zr_sys_jetid_pt%d", i));   
  h2_zr_ptbinned_sys_jer[i-1]->SetName(Form("zr_sys_jer_pt%d", i));   
  h2_zr_ptbinned_sys_jes[i-1]->SetName(Form("zr_sys_jes_pt%d", i));   
  h2_zr_ptbinned_sys_tracking[i-1]->SetName(Form("zr_sys_tracking_pt%d", i));   
  h2_zr_ptbinned_sys_pid[i-1]->SetName(Form("zr_sys_pid_pt%d", i));  
  h2_zr_ptbinned_sys_sbsub[i-1]->SetName(Form("zr_sys_sbsub_pt%d", i));   
  h2_zr_ptbinned_sys_fitmodel[i-1]->SetName(Form("zr_sys_fitmodel_pt%d", i));  
  h2_zr_ptbinned_sys_recsel[i-1]->SetName(Form("zr_sys_recsel_pt%d", i));       
  h2_zr_ptbinned_sys_closure[i-1]->SetName(Form("zr_sys_closure_pt%d", i)); 
  h2_zr_ptbinned_sys_shapeclosure[i-1]->SetName(Form("zr_sys_shapeclosure_pt%d", i)); 
  h2_zr_ptbinned_sys_iter[i-1]->SetName(Form("zr_sys_iter_pt%d", i));    
  h2_zr_ptbinned_sys_prior[i-1]->SetName(Form("zr_sys_prior_pt%d", i));    
  h2_zr_ptbinned_sys_total[i-1]->SetName(Form("zr_sys_total_pt%d", i));    
  
  h2_jtr_ptbinned_sys_jetid[i-1]->SetName(Form("jtr_sys_jetid_pt%d", i));   
  h2_jtr_ptbinned_sys_jer[i-1]->SetName(Form("jtr_sys_jer_pt%d", i));   
  h2_jtr_ptbinned_sys_jes[i-1]->SetName(Form("jtr_sys_jes_pt%d", i));   
  h2_jtr_ptbinned_sys_tracking[i-1]->SetName(Form("jtr_sys_tracking_pt%d", i));   
  h2_jtr_ptbinned_sys_pid[i-1]->SetName(Form("jtr_sys_pid_pt%d", i));  
  h2_jtr_ptbinned_sys_sbsub[i-1]->SetName(Form("jtr_sys_sbsub_pt%d", i));   
  h2_jtr_ptbinned_sys_fitmodel[i-1]->SetName(Form("jtr_sys_fitmodel_pt%d", i));  
  h2_jtr_ptbinned_sys_recsel[i-1]->SetName(Form("jtr_sys_recsel_pt%d", i));       
  h2_jtr_ptbinned_sys_closure[i-1]->SetName(Form("jtr_sys_closure_pt%d", i)); 
  h2_jtr_ptbinned_sys_shapeclosure[i-1]->SetName(Form("jtr_sys_shapeclosure_pt%d", i)); 
  h2_jtr_ptbinned_sys_iter[i-1]->SetName(Form("jtr_sys_iter_pt%d", i));    
  h2_jtr_ptbinned_sys_prior[i-1]->SetName(Form("jtr_sys_prior_pt%d", i));    
  h2_jtr_ptbinned_sys_total[i-1]->SetName(Form("jtr_sys_total_pt%d", i));        
  /*
  if (i==3)
  {
    for (int ibin = 0; ibin < h1_jt_ptbinned_sys_total[i-1]->GetNbinsX(); ++ibin)
    {
      cout << " total sys jT pt " << ibin << " : " << h1_jt_ptbinned_sys_total[i-1]->GetBinContent(ibin+1) << endl;
      cout << " nonclosure sys jT pt " << ibin << " : " << h1_jt_ptbinned_sys_closure[i-1]->GetBinContent(ibin+1) << endl;      
    }
  }
  */
  // Write relevant histograms to output file
  h1_z_ptbinned_sys_jetid[i-1]->Write();   
  h1_z_ptbinned_sys_jer[i-1]->Write();   
  h1_z_ptbinned_sys_jes[i-1]->Write();   
  h1_z_ptbinned_sys_tracking[i-1]->Write();   
  h1_z_ptbinned_sys_pid[i-1]->Write();  
  h1_z_ptbinned_sys_sbsub[i-1]->Write();   
  h1_z_ptbinned_sys_fitmodel[i-1]->Write();  
  h1_z_ptbinned_sys_recsel[i-1]->Write();       
  h1_z_ptbinned_sys_closure[i-1]->Write(); 
  h1_z_ptbinned_sys_shapeclosure[i-1]->Write(); 
  h1_z_ptbinned_sys_iter[i-1]->Write();    
  h1_z_ptbinned_sys_prior[i-1]->Write(); 
  h1_z_ptbinned_sys_total[i-1]->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  h1_z_ptbinned_sys_total[i-1]->Write();    
  
  h1_jt_ptbinned_sys_jetid[i-1]->Write();   
  h1_jt_ptbinned_sys_jer[i-1]->Write();   
  h1_jt_ptbinned_sys_jes[i-1]->Write();   
  h1_jt_ptbinned_sys_tracking[i-1]->Write();   
  h1_jt_ptbinned_sys_pid[i-1]->Write();  
  h1_jt_ptbinned_sys_sbsub[i-1]->Write();   
  h1_jt_ptbinned_sys_fitmodel[i-1]->Write();  
  h1_jt_ptbinned_sys_recsel[i-1]->Write();       
  h1_jt_ptbinned_sys_closure[i-1]->Write(); 
  h1_jt_ptbinned_sys_shapeclosure[i-1]->Write(); 
  h1_jt_ptbinned_sys_iter[i-1]->Write();    
  h1_jt_ptbinned_sys_prior[i-1]->Write();
  h1_jt_ptbinned_sys_total[i-1]->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  h1_jt_ptbinned_sys_total[i-1]->Write();    
  
  h1_r_ptbinned_sys_jetid[i-1]->Write();   
  h1_r_ptbinned_sys_jer[i-1]->Write();   
  h1_r_ptbinned_sys_jes[i-1]->Write();   
  h1_r_ptbinned_sys_tracking[i-1]->Write();   
  h1_r_ptbinned_sys_pid[i-1]->Write();  
  h1_r_ptbinned_sys_sbsub[i-1]->Write();   
  h1_r_ptbinned_sys_fitmodel[i-1]->Write();  
  h1_r_ptbinned_sys_recsel[i-1]->Write();       
  h1_r_ptbinned_sys_closure[i-1]->Write(); 
  h1_r_ptbinned_sys_shapeclosure[i-1]->Write(); 
  h1_r_ptbinned_sys_iter[i-1]->Write();    
  h1_r_ptbinned_sys_prior[i-1]->Write();
  h1_r_ptbinned_sys_total[i-1]->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  h1_r_ptbinned_sys_total[i-1]->Write();    
  

  h2_zjt_ptbinned_sys_jetid[i-1]->Write();   
  h2_zjt_ptbinned_sys_jer[i-1]->Write();   
  h2_zjt_ptbinned_sys_jes[i-1]->Write();   
  h2_zjt_ptbinned_sys_tracking[i-1]->Write();   
  h2_zjt_ptbinned_sys_pid[i-1]->Write();  
  h2_zjt_ptbinned_sys_sbsub[i-1]->Write();   
  h2_zjt_ptbinned_sys_fitmodel[i-1]->Write();  
  h2_zjt_ptbinned_sys_recsel[i-1]->Write();       
  h2_zjt_ptbinned_sys_closure[i-1]->Write(); 
  h2_zjt_ptbinned_sys_shapeclosure[i-1]->Write(); 
  h2_zjt_ptbinned_sys_iter[i-1]->Write();    
  h2_zjt_ptbinned_sys_prior[i-1]->Write();    
  h2_zjt_ptbinned_sys_total[i-1]->SetTitle(Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  h2_zjt_ptbinned_sys_total[i-1]->SetOption("COLZ, text");
  h2_zjt_ptbinned_sys_total[i-1]->Write();    
  
  h2_zr_ptbinned_sys_jetid[i-1]->Write();   
  h2_zr_ptbinned_sys_jer[i-1]->Write();   
  h2_zr_ptbinned_sys_jes[i-1]->Write();   
  h2_zr_ptbinned_sys_tracking[i-1]->Write();   
  h2_zr_ptbinned_sys_pid[i-1]->Write();  
  h2_zr_ptbinned_sys_sbsub[i-1]->Write();   
  h2_zr_ptbinned_sys_fitmodel[i-1]->Write();  
  h2_zr_ptbinned_sys_recsel[i-1]->Write();       
  h2_zr_ptbinned_sys_closure[i-1]->Write(); 
  h2_zr_ptbinned_sys_shapeclosure[i-1]->Write(); 
  h2_zr_ptbinned_sys_iter[i-1]->Write();    
  h2_zr_ptbinned_sys_prior[i-1]->Write();   
  h2_zr_ptbinned_sys_total[i-1]->SetTitle(Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  h2_zr_ptbinned_sys_total[i-1]->SetOption("COLZ, text");
  h2_zr_ptbinned_sys_total[i-1]->Write();    
  
  h2_jtr_ptbinned_sys_jetid[i-1]->Write();   
  h2_jtr_ptbinned_sys_jer[i-1]->Write();   
  h2_jtr_ptbinned_sys_jes[i-1]->Write();   
  h2_jtr_ptbinned_sys_tracking[i-1]->Write();   
  h2_jtr_ptbinned_sys_pid[i-1]->Write();  
  h2_jtr_ptbinned_sys_sbsub[i-1]->Write();   
  h2_jtr_ptbinned_sys_fitmodel[i-1]->Write();  
  h2_jtr_ptbinned_sys_recsel[i-1]->Write();       
  h2_jtr_ptbinned_sys_closure[i-1]->Write();
  h2_jtr_ptbinned_sys_shapeclosure[i-1]->Write();  
  h2_jtr_ptbinned_sys_iter[i-1]->Write();    
  h2_jtr_ptbinned_sys_prior[i-1]->Write();
  h2_jtr_ptbinned_sys_total[i-1]->SetTitle(Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  h2_jtr_ptbinned_sys_total[i-1]->SetOption("COLZ, text");
  h2_jtr_ptbinned_sys_total[i-1]->Write();   
  
  }


  //---- paint setup...
  //
  int ican = -1, iframe = -1, itext = -1;
  TCanvas *ccan[1000];
  TH1F *frame[1000];
  TLatex *text[1000];
  TRatioPlot *rp[1000];
  for (int i = 0; i < 1000; i++)
  {
    text[i] = new TLatex();
    text[i]->SetNDC(kTRUE);
    text[i]->SetTextSize(0.06);
  }
  TLatex Tl;
  Tl.SetNDC(kTRUE);
  Tl.SetTextSize(0.04);
  //
  gStyle->SetOptStat(0);
  // gStyle->SetPaperSize(TStyle::kUSLetter);
  gStyle->SetPadBottomMargin(0.13);
  // gStyle->SetPadTopMargin(0.005);
  gStyle->SetPadLeftMargin(0.17);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetLabelSize(0.05, "X");
  gStyle->SetLabelSize(0.05, "Y");
  gStyle->SetTitleXSize(0.055);
  gStyle->SetTitleYSize(0.055);
  gStyle->SetTitleOffset(0.55, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetStatW(0.2);
  // gStyle->SetPalette(kBird);
  gStyle->SetPalette(kBird);
  gStyle->SetNumberContours(100);
  gStyle->SetPaintTextFormat("4.3g");
  // gStyle->SetErrorX(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetStatStyle(0);
  // gStyle->SetLineWidth(3);

  //---- paint...
  char buf[100];
  char bufb[100];
  TString rootfile;
  TString plotfile;
  TString plotfilePDF;
  TString plotfileO;
  TString plotfileC;
  // TString OutputFileBase	= outbase+outinfo;
  rootfile = loc_hists + extension + TString(".root");
  plotfile = loc_plots + extension + TString(".ps");
  plotfilePDF = loc_plots + extension + TString(".pdf");
  plotfileO = plotfilePDF + TString("(");
  plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

  double top = 0.85;
  double step = 0.06;

  ofstream textables;
  textables.open("textables.txt");
  textables << "\\begin{longtable}{ccc}\n";
  textables << "    \\caption{Systematic uncertainties for $\\frac{1}{N_{j}}\\frac{dN}{dz}$ from Figure~\\ref{fig:z_total_sys_pt1}-\\ref{fig:z_total_sys_pt6}} \\\\\n";
  textables << "    \\label{tab:z_sys_all}\n";
  textables << "    \\ptj & sys type & min - max (relative sys) \\\\\n";
  textables << "    \\hline\n";
  for (int i=1; i<ptbinsize; ++i)
  {
    if (i!=1)
    {
      textables << "    \\hline\n";
    }
    textables << Form("    $%.1f<\\ptj<%.1f$", pt_binedges[i], pt_binedges[i+1]) << " & ";
  // Begin plotting
  //
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_z_ptbinned_sys_total[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_total[i-1]->SetMaximum(1.);
  //h1_z_ptbinned_sys_total[i-1]->SetMinimum(0.);
  h1_z_ptbinned_sys_total[i-1]->SetTitle("Total Systematic");
  
  ccan[ican]->cd(3);
  h1_z_ptbinned_sys_pidup[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_pidup[i-1]->SetMinimum(-0.1);
  //h1_z_ptbinned_sys_pidup[i-1]->SetMaximum(0.1);
  h1_z_ptbinned_sys_pidup[i-1]->SetTitle("PID +1#sigma");

  ccan[ican]->cd(4);
  h1_z_ptbinned_sys_piddown[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_piddown[i-1]->SetMinimum(-0.1);
  //h1_z_ptbinned_sys_piddown[i-1]->SetMaximum(0.1);
  h1_z_ptbinned_sys_piddown[i-1]->SetTitle("PID -1#sigma");  

  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
  
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_z_ptbinned_sys_trigup[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_trigup[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_trigup[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_trigup[i-1]->SetTitle("Trig. +1#sigma");
  ccan[ican]->cd(2);

  h1_z_ptbinned_sys_trigdown[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_trigdown[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_trigdown[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_trigdown[i-1]->SetTitle("Trig. -1#sigma");

  ccan[ican]->cd(3);
  h1_z_ptbinned_sys_trackingup[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_trackingup[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_trackingup[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_trackingup[i-1]->SetTitle("Tracking +1#sigma");

  ccan[ican]->cd(4);

  h1_z_ptbinned_sys_trackingdown[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_trackingdown[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_trackingdown[i-1]->SetMaximum(0.3);
  h1_z_ptbinned_sys_trackingdown[i-1]->SetTitle("Tracking -1#sigma");

  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }  
  
  
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_z_ptbinned_sys_closure[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_closure[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_closure[i-1]->SetMaximum(0.3);
  h1_z_ptbinned_sys_closure[i-1]->SetTitle("non closure");

  ccan[ican]->cd(2);
  h1_z_ptbinned_sys_iterhigh[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_iterhigh[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_iterhigh[i-1]->SetMaximum(0.3);
  h1_z_ptbinned_sys_iterhigh[i-1]->SetTitle("iter +1");

  ccan[ican]->cd(3);
  h1_z_ptbinned_sys_iterlow[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_iterlow[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_iterlow[i-1]->SetMaximum(0.3);
  h1_z_ptbinned_sys_iterlow[i-1]->SetTitle("iter -1");  
  
  ccan[ican]->cd(4);
  h1_z_ptbinned_sys_prior[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_prior[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_prior[i-1]->SetMaximum(0.3);
  h1_z_ptbinned_sys_prior[i-1]->SetTitle("prior");   
  
  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
 

  //

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_z_ptbinned_sys_jes[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_jes[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_jes[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_jes[i-1]->SetTitle("JES");

  ccan[ican]->cd(2);
  h1_z_ptbinned_sys_jer[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_jer[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_jer[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_jer[i-1]->SetTitle("JER");
  
  ccan[ican]->cd(3);
  h1_z_ptbinned_sys_jetid[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_jetid[i-1]->SetMaximum(0.5);
  //h1_z_ptbinned_sys_jetid[i-1]->SetMinimum(-0.5);
  h1_z_ptbinned_sys_jetid[i-1]->SetTitle("JetID efficiency");  

  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }

  //
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_z_ptbinned_sys_sbsubnear[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_sbsubnear[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_sbsubnear[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_sbsubnear[i-1]->SetTitle("Sideband Var 1");
 
  ccan[ican]->cd(2);
  h1_z_ptbinned_sys_sbsubfar[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_sbsubfar[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_sbsubfar[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_sbsubfar[i-1]->SetTitle("Sideband Var 2");
   
  ccan[ican]->cd(3);
  h1_z_ptbinned_sys_fitmodel[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_fitmodel[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_fitmodel[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_fitmodel[i-1]->SetTitle("MassFit Model Var");
  
  ccan[ican]->cd(4);
  h1_z_ptbinned_sys_recsel[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_recsel[i-1]->SetMinimum(-0.5);
  //h1_z_ptbinned_sys_recsel[i-1]->SetMaximum(0.5);
  h1_z_ptbinned_sys_recsel[i-1]->SetTitle("Rec. and Sel.");    


  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }

  //

  //

  TLegend *legend_z_ptbinned = new TLegend(0.6, 0.6, 0.9, 0.9);
  legend_z_ptbinned->SetBorderSize(0);
  legend_z_ptbinned->SetFillStyle(0);
  legend_z_ptbinned->SetFillColor(3);
  //auto legend_stack_z_ptbinned = new TLegend(0.6, 0.67, 0.8, 0.87);
  
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptz_ptbinned_sys("stack_ptz_ptbinned_sys%d", "");



    for (int j = 0; j < vec_sys_z_ptbinned[i-1].size(); j++)
    {
      SetHistErrorZero(vec_sys_z_ptbinned[i-1][j]);
      TH1D *h1_z_ptbinned_sys = (TH1D *)vec_sys_z_ptbinned[i-1][j];
      TH1D *h1_z_ptbinned_sys_fortable = (TH1D*)h1_z_ptbinned_sys->Clone(Form("h1_z_pt%d_sys_fortable_%d",i,j));
      for (int ibin = 0; ibin < h1_z_ptbinned_sys_fortable->GetNbinsX(); ++ibin )
      {
        if (ibin == 0) { h1_z_ptbinned_sys_fortable->SetBinContent(ibin+1, 0.); }
        if (h1_z_ptbinned_sys_fortable->GetBinContent(ibin+1) < 0)
        {
          h1_z_ptbinned_sys_fortable->SetBinContent(ibin+1, fabs(h1_z_ptbinned_sys_fortable->GetBinContent(ibin+1)));
        }


      }
      if (j==0)
      {
        textables << std::fixed << std::setprecision(sigfigs) << vec_string[j] << " & " << h1_z_ptbinned_sys_fortable->GetMinimum(0.) << " - " << h1_z_ptbinned_sys_fortable->GetMaximum() << "\\\\\n";
      }
      else
      {
        textables << std::fixed << std::setprecision(sigfigs) << "                     & " << vec_string[j] << " & " << h1_z_ptbinned_sys_fortable->GetMinimum(0.) << " - " << h1_z_ptbinned_sys_fortable->GetMaximum() << "\\\\\n";
      }
      TH1D *h1_z_ptbinned_sys_sym = (TH1D *)h1_z_ptbinned_sys->Clone(Form("h1_z_pt%d_sys_sym%d",i,j));
      h1_z_ptbinned_sys_sym->Scale(-1);

      if (j == vec_sys_z_ptbinned[i-1].size() - 1)
      {
        h1_z_ptbinned_sys->SetTitle("; z;Relative Uncertainty");
        h1_z_ptbinned_sys->GetYaxis()->SetTitleOffset(1.);
        h1_z_ptbinned_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_z_ptbinned_sys->GetYaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys->GetXaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys->SetFillColorAlpha(16, 0.3);
        h1_z_ptbinned_sys->SetLineColorAlpha(16, 0.3);
        h1_z_ptbinned_sys->Draw("HIST SAME");

        h1_z_ptbinned_sys_sym->SetTitle("; z;Relative Uncertainty");
        h1_z_ptbinned_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_z_ptbinned_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_z_ptbinned_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_z_ptbinned_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_z_ptbinned_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = j + 22;
        if (j + 1 == 10)
          color = 15;

        h1_z_ptbinned_sys->SetTitle("; z;Relative Uncertainty");
        h1_z_ptbinned_sys->GetYaxis()->SetTitleOffset(1.);
        h1_z_ptbinned_sys->GetXaxis()->SetTitleOffset(1.);

        h1_z_ptbinned_sys->GetYaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys->GetXaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys->SetMarkerStyle(vec_markers[j]);
        h1_z_ptbinned_sys->SetMarkerColor(color);
        h1_z_ptbinned_sys->SetLineColor(color);
        h1_z_ptbinned_sys->Draw("P SAME");

        h1_z_ptbinned_sys_sym->SetTitle("; z;Relative Uncertainty");
        h1_z_ptbinned_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_z_ptbinned_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_z_ptbinned_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_z_ptbinned_sys_sym->SetMarkerStyle(vec_markers[j]);
        h1_z_ptbinned_sys_sym->SetMarkerColor(color);
        h1_z_ptbinned_sys_sym->SetLineColor(color);
        h1_z_ptbinned_sys_sym->Draw("P SAME");
      }
      legend_z_ptbinned->AddEntry(h1_z_ptbinned_sys, vec_string[j]);
      
      h1_z_ptbinned_sys->SetMaximum(1.0);
      h1_z_ptbinned_sys->SetMinimum(-1.0);
    }
    
    legend_z_ptbinned->Draw("SAME");   
    
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));    
    Tl.DrawLatex(0.2, top - step, Form("%.1f < p_{T,jet} < %.1f", pt_binedges[i], pt_binedges[i+1]));  
    
    ccan[ican]->SaveAs(loc_plots + Form("z_total_sys_contributions_pt%d.png", i));      
    
    ccan[ican]->cd();
    ccan[ican]->Update();
    if (ican == 0)
    {
      ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
      ccan[ican]->Print(plotfilePDF.Data());
    }

  }
  textables << "\\end{longtable}\n";

  textables << "\\begin{longtable}{ccc}\n";
  textables << "    \\caption{Systematic uncertainties for $\\frac{1}{N_{j}}\\frac{dN}{d\\jt}$ from Figure~\\ref{fig:jt_total_sys_pt1}-\\ref{fig:jt_total_sys_pt6}} \\\\\n";
  textables << "    \\label{tab:jt_sys_all}\n";
  textables << "    \\ptj & sys type & min - max (relative sys) \\\\\n";
  textables << "    \\hline\n";
  for (int i=1; i<ptbinsize; ++i)
  {

    if (i!=1)
    {
      textables << "    \\hline\n";
    }
    textables << Form("    $%.1f<\\ptj<%.1f$", pt_binedges[i], pt_binedges[i+1]) << " & ";

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);  

  h1_jt_ptbinned_sys_total[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_total[i-1]->SetMaximum(1.);
  //h1_jt_ptbinned_sys_total[i-1]->SetMinimum(0.);
  h1_jt_ptbinned_sys_total[i-1]->SetTitle("Total Systematic");
  
  ccan[ican]->cd(3);
  h1_jt_ptbinned_sys_pidup[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_pidup[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_pidup[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_pidup[i-1]->SetTitle("PID +1#sigma");

  ccan[ican]->cd(4);
  h1_jt_ptbinned_sys_piddown[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_piddown[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_piddown[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_piddown[i-1]->SetTitle("PID -1#sigma");    


  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
  
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_jt_ptbinned_sys_trigup[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_trigup[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_trigup[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_trigup[i-1]->SetTitle("Trig. +1#sigma");
  ccan[ican]->cd(2);

  h1_jt_ptbinned_sys_trigdown[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_trigdown[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_trigdown[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_trigdown[i-1]->SetTitle("Trig. -1#sigma");

  ccan[ican]->cd(3);
  h1_jt_ptbinned_sys_trackingup[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_trackingup[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_trackingup[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_trackingup[i-1]->SetTitle("Tracking +1#sigma");

  ccan[ican]->cd(4);

  h1_jt_ptbinned_sys_trackingdown[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_trackingdown[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_trackingdown[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_trackingdown[i-1]->SetTitle("Tracking -1#sigma");

  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
  
  //  
  //
  
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_jt_ptbinned_sys_closure[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_closure[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_closure[i-1]->SetMaximum(0.3);
  h1_jt_ptbinned_sys_closure[i-1]->SetTitle("non closure");

  ccan[ican]->cd(2);
  h1_jt_ptbinned_sys_iterhigh[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_iterhigh[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_iterhigh[i-1]->SetMaximum(0.3);
  h1_jt_ptbinned_sys_iterhigh[i-1]->SetTitle("iter +1");

  ccan[ican]->cd(3);
  h1_jt_ptbinned_sys_iterlow[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_iterlow[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_iterlow[i-1]->SetMaximum(0.3);
  h1_jt_ptbinned_sys_iterlow[i-1]->SetTitle("iter -1");  
  
  ccan[ican]->cd(4);
  h1_jt_ptbinned_sys_prior[i-1]->Draw("COLZ TEXTE");
  //h1_z_ptbinned_sys_prior[i-1]->SetMinimum(-0.3);
  //h1_z_ptbinned_sys_prior[i-1]->SetMaximum(0.3);
  h1_jt_ptbinned_sys_prior[i-1]->SetTitle("prior");   
  
  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
 

  //

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_jt_ptbinned_sys_jes[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_jes[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_jer[i-1]->SetMaximum(0.5);
  //h1_jt_ptbinned_sys_jes[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_jes[i-1]->SetTitle("JES");


  ccan[ican]->cd(2);
  h1_jt_ptbinned_sys_jer[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_jer[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_jer[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_jer[i-1]->SetTitle("JER");
  
  ccan[ican]->cd(3);
  h1_jt_ptbinned_sys_jetid[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_jetid[i-1]->SetMaximum(0.5);
  //h1_jt_ptbinned_sys_jetid[i-1]->SetMinimum(-0.5);
  h1_jt_ptbinned_sys_jetid[i-1]->SetTitle("JetID");  

  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }

  //


  //
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_jt_ptbinned_sys_sbsubnear[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_sbsubnear[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_sbsubnear[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_sbsubnear[i-1]->SetTitle("Sideband Var 1");
 
  ccan[ican]->cd(2);
  h1_jt_ptbinned_sys_sbsubfar[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_sbsubfar[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_sbsubfar[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_sbsubfar[i-1]->SetTitle("Sideband Var 2");
   
  ccan[ican]->cd(3);
  h1_jt_ptbinned_sys_fitmodel[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_fitmodel[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_fitmodel[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_fitmodel[i-1]->SetTitle("MassFit Model Var");
  
  ccan[ican]->cd(4);
  h1_jt_ptbinned_sys_recsel[i-1]->Draw("COLZ TEXTE");
  //h1_jt_ptbinned_sys_recsel[i-1]->SetMinimum(-0.5);
  //h1_jt_ptbinned_sys_recsel[i-1]->SetMaximum(0.5);
  h1_jt_ptbinned_sys_recsel[i-1]->SetTitle("Rec. and Sel.");    


  // h1_z_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }

  //

  //

  TLegend *legend_jt_ptbinned = new TLegend(0.6, 0.6, 0.9, 0.9);
  legend_jt_ptbinned->SetBorderSize(0);
  legend_jt_ptbinned->SetFillStyle(0);
  legend_jt_ptbinned->SetFillColor(3);
  //auto legend_stack_z_ptbinned = new TLegend(0.6, 0.67, 0.8, 0.87);
  
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptjt_ptbinned_sys("stack_ptjt_ptbinned_sys%d", "");

    for (int j = 0; j < vec_sys_jt_ptbinned[i-1].size(); j++)
    {
      SetHistErrorZero(vec_sys_jt_ptbinned[i-1][j]);
      TH1D *h1_jt_ptbinned_sys = (TH1D *)vec_sys_jt_ptbinned[i-1][j];
      TH1D *h1_jt_ptbinned_sys_fortable = (TH1D*)h1_jt_ptbinned_sys->Clone(Form("h1_jt_pt%d_sys_fortable_%d",i,j));
      for (int ibin = 0; ibin < h1_jt_ptbinned_sys_fortable->GetNbinsX(); ++ibin )
      {
        if (h1_jt_ptbinned_sys_fortable->GetBinContent(ibin+1) < 0)
        {
          h1_jt_ptbinned_sys_fortable->SetBinContent(ibin+1, fabs(h1_jt_ptbinned_sys_fortable->GetBinContent(ibin+1)));
        }
      }
      if (j==0)
      {
        textables << std::fixed << std::setprecision(sigfigs) << vec_string[j] << " & " << h1_jt_ptbinned_sys_fortable->GetMinimum(0.) << " - " << h1_jt_ptbinned_sys_fortable->GetMaximum() << "\\\\\n";
      }
      else
      {
        textables << std::fixed << std::setprecision(sigfigs) << "                     & " << vec_string[j] << " & " << h1_jt_ptbinned_sys_fortable->GetMinimum(0.) << " - " << h1_jt_ptbinned_sys_fortable->GetMaximum() << "\\\\\n";
      }
      TH1D *h1_jt_ptbinned_sys_sym = (TH1D *)h1_jt_ptbinned_sys->Clone(Form("h1_jt_pt%d_sys_sym%d",i,j));
      h1_jt_ptbinned_sys_sym->Scale(-1);

      if (j == vec_sys_jt_ptbinned[i-1].size() - 1)
      {
        h1_jt_ptbinned_sys->SetTitle("; j_{T} (GeV/Cc);Relative Uncertainty");
        h1_jt_ptbinned_sys->GetYaxis()->SetTitleOffset(1.);
        h1_jt_ptbinned_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_jt_ptbinned_sys->GetYaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys->GetXaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys->SetFillColorAlpha(16, 0.3);
        h1_jt_ptbinned_sys->SetLineColorAlpha(16, 0.3);
        h1_jt_ptbinned_sys->Draw("HIST SAME");

        h1_jt_ptbinned_sys_sym->SetTitle("; j_{T} (GeV/c);Relative Uncertainty");
        h1_jt_ptbinned_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_jt_ptbinned_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_jt_ptbinned_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_jt_ptbinned_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_jt_ptbinned_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = j + 22;
        if (j + 1 == 10)
          color = 15;

        h1_jt_ptbinned_sys->SetTitle("; j_{T} (GeV/c);Relative Uncertainty");
        h1_jt_ptbinned_sys->GetYaxis()->SetTitleOffset(1.);
        h1_jt_ptbinned_sys->GetXaxis()->SetTitleOffset(1.);

        h1_jt_ptbinned_sys->GetYaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys->GetXaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys->SetMarkerStyle(vec_markers[j]);
        h1_jt_ptbinned_sys->SetMarkerColor(color);
        h1_jt_ptbinned_sys->SetLineColor(color);
        h1_jt_ptbinned_sys->Draw("P SAME");

        h1_jt_ptbinned_sys_sym->SetTitle("; j_{T} (GeV/c);Relative Uncertainty");
        h1_jt_ptbinned_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_jt_ptbinned_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_jt_ptbinned_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_jt_ptbinned_sys_sym->SetMarkerStyle(vec_markers[j]);
        h1_jt_ptbinned_sys_sym->SetMarkerColor(color);
        h1_jt_ptbinned_sys_sym->SetLineColor(color);
        h1_jt_ptbinned_sys_sym->Draw("P SAME");
      }
      legend_jt_ptbinned->AddEntry(h1_jt_ptbinned_sys, vec_string[j]);
      
      h1_jt_ptbinned_sys->SetMaximum(1.0);
      h1_jt_ptbinned_sys->SetMinimum(-1.0);
    }
    
    legend_jt_ptbinned->Draw("SAME");    
    
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));    
    Tl.DrawLatex(0.2, top - step, Form("%.1f < p_{T,jet} < %.1f", pt_binedges[i], pt_binedges[i+1]));   
    
    ccan[ican]->SaveAs(loc_plots + Form("jt_total_sys_contributions_pt%d.png", i));     
    
    ccan[ican]->cd();
    ccan[ican]->Update();
    if (ican == 0)
    {
      ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
      ccan[ican]->Print(plotfilePDF.Data());
    }   
    
  }
  textables << "\\end{longtable}\n";

  textables << "\\begin{longtable}{ccc}\n";
  textables << "    \\caption{Systematic uncertainties for $\\frac{1}{N_{j}}\\frac{dN}{dr}$ from Figure~\\ref{fig:r_total_sys_pt1}-\\ref{fig:r_total_sys_pt6}} \\\\\n";
  textables << "    \\label{tab:r_sys_all}\n";
  textables << "    \\ptj & sys type & min - max (relative sys) \\\\\n";
  textables << "    \\hline\n";
  for (int i=1; i<ptbinsize; ++i)
  {

  if (i!=1)
  {
    textables << "    \\hline\n";
  }
  textables << Form("    $%.1f<\\ptj<%.1f$", pt_binedges[i], pt_binedges[i+1]) << " & ";    
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_r_ptbinned_sys_total[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_total[i-1]->SetMaximum(1.);
  //h1_r_ptbinned_sys_total[i-1]->SetMinimum(0.);
  h1_r_ptbinned_sys_total[i-1]->SetTitle("Total Systematic");
  
  ccan[ican]->cd(3);
  h1_r_ptbinned_sys_pidup[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_pidup[i-1]->SetMinimum(-0.5);
  //h1_r_ptbinned_sys_pidup[i-1]->SetMaximum(0.5);
  h1_r_ptbinned_sys_pidup[i-1]->SetTitle("PID +1#sigma");

  ccan[ican]->cd(4);
  h1_r_ptbinned_sys_piddown[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_piddown[i-1]->SetMinimum(-0.5);
  //h1_r_ptbinned_sys_piddown[i-1]->SetMaximum(0.5);
  h1_r_ptbinned_sys_piddown[i-1]->SetTitle("PID -1#sigma");     


  // h1_r_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
  
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_r_ptbinned_sys_trigup[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_trigup[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_trigup[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_trigup[i-1]->SetTitle("Trig. +1#sigma");
  ccan[ican]->cd(2);

  h1_r_ptbinned_sys_trigdown[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_trigdown[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_trigdown[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_trigdown[i-1]->SetTitle("Trig. -1#sigma");

  ccan[ican]->cd(3);
  h1_r_ptbinned_sys_trackingup[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_trackingup[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_trackingup[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_trackingup[i-1]->SetTitle("Tracking +1#sigma");

  ccan[ican]->cd(4);

  h1_r_ptbinned_sys_trackingdown[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_trackingdown[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_trackingdown[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_trackingdown[i-1]->SetTitle("Tracking -1#sigma");

  // h1_r_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }  
  
  
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_r_ptbinned_sys_closure[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_closure[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_closure[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_closure[i-1]->SetTitle("non closure");

  ccan[ican]->cd(2);
  h1_r_ptbinned_sys_iterhigh[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_iterhigh[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_iterhigh[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_iterhigh[i-1]->SetTitle("iter +1");

  ccan[ican]->cd(3);
  h1_r_ptbinned_sys_iterlow[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_iterlow[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_iterlow[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_iterlow[i-1]->SetTitle("iter -1");  
  
  ccan[ican]->cd(4);
  h1_r_ptbinned_sys_prior[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_prior[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_prior[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_prior[i-1]->SetTitle("prior");   
  
  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }
 

  //

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_r_ptbinned_sys_jes[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_jes[i-1]->SetMinimum(-0.5);
  //h1_r_ptbinned_sys_jes[i-1]->SetMaximum(0.5);
  h1_r_ptbinned_sys_jes[i-1]->SetTitle("JES");


  ccan[ican]->cd(2);
  h1_r_ptbinned_sys_jer[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_jer[i-1]->SetMinimum(-0.5);
  //h1_r_ptbinned_sys_jer[i-1]->SetMaximum(0.5);
  h1_r_ptbinned_sys_jer[i-1]->SetTitle("JER");
  
  ccan[ican]->cd(3);
  h1_r_ptbinned_sys_jetid[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_jetid[i-1]->SetMaximum(0.5);
  //h1_r_ptbinned_sys_jetid[i-1]->SetMinimum(-0.5);
  h1_r_ptbinned_sys_jetid[i-1]->SetTitle("JetID");  

  // h1_r_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }

  //


  //
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_r_ptbinned_sys_sbsubnear[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_sbsubnear[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_sbsubnear[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_sbsubnear[i-1]->SetTitle("Sideband Var 1");
 
  ccan[ican]->cd(2);
  h1_r_ptbinned_sys_sbsubfar[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_sbsubfar[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_sbsubfar[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_sbsubfar[i-1]->SetTitle("Sideband Var 2");
   
  ccan[ican]->cd(3);
  h1_r_ptbinned_sys_fitmodel[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_fitmodel[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_fitmodel[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_fitmodel[i-1]->SetTitle("MassFit Model Var");
  
  ccan[ican]->cd(4);
  h1_r_ptbinned_sys_recsel[i-1]->Draw("COLZ TEXTE");
  //h1_r_ptbinned_sys_recsel[i-1]->SetMinimum(-0.3);
  //h1_r_ptbinned_sys_recsel[i-1]->SetMaximum(0.3);
  h1_r_ptbinned_sys_recsel[i-1]->SetTitle("Rec. and Sel.");    


  // h1_r_ptbinned_->SetTitle("Data+Purity+Unfold; ;");

  ccan[ican]->cd();
  ccan[ican]->Update();
  if (ican == 0)
  {
    ccan[ican]->Print(plotfileO.Data());
  }
  else
  {
    ccan[ican]->Print(plotfilePDF.Data());
  }

  //

  //

  TLegend *legend_r_ptbinned = new TLegend(0.6, 0.6, 0.9, 0.9);
  legend_r_ptbinned->SetBorderSize(0);
  legend_r_ptbinned->SetFillStyle(0);
  legend_r_ptbinned->SetFillColor(3);
  //auto legend_stack_r_ptbinned = new TLegend(0.6, 0.67, 0.8, 0.87);
  
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptr_ptbinned_sys("stack_ptr_ptbinned_sys%d", "");

    for (int j = 0; j < vec_sys_r_ptbinned[i-1].size(); j++)
    {
      SetHistErrorZero(vec_sys_r_ptbinned[i-1][j]);
      TH1D *h1_r_ptbinned_sys = (TH1D *)vec_sys_r_ptbinned[i-1][j];
      TH1D *h1_r_ptbinned_sys_fortable = (TH1D*)h1_r_ptbinned_sys->Clone(Form("h1_r_pt%d_sys_fortable_%d",i,j));
      for (int ibin = 0; ibin < h1_r_ptbinned_sys_fortable->GetNbinsX(); ++ibin )
      {
        if (ibin+1 == rbinsize) { h1_r_ptbinned_sys_fortable->SetBinContent(ibin+1, 0.); }
        if (h1_r_ptbinned_sys_fortable->GetBinContent(ibin+1) < 0)
        {
          h1_r_ptbinned_sys_fortable->SetBinContent(ibin+1, fabs(h1_r_ptbinned_sys_fortable->GetBinContent(ibin+1)));
        }
      }
      if (j==0)
      {
        textables << std::fixed << std::setprecision(sigfigs) << vec_string[j] << " & " << h1_r_ptbinned_sys_fortable->GetMinimum(0.) << " - " << h1_r_ptbinned_sys_fortable->GetMaximum() << "\\\\\n";
      }
      else
      {
        textables << std::fixed << std::setprecision(sigfigs) << "                     & " << vec_string[j] << " & " << h1_r_ptbinned_sys_fortable->GetMinimum(0.) << " - " << h1_r_ptbinned_sys_fortable->GetMaximum() << "\\\\\n";
      }
      TH1D *h1_r_ptbinned_sys_sym = (TH1D *)h1_r_ptbinned_sys->Clone(Form("h1_r_pt%d_sys_sym%d",i,j));
      h1_r_ptbinned_sys_sym->Scale(-1);

      if (j == vec_sys_r_ptbinned[i-1].size() - 1)
      {
        h1_r_ptbinned_sys->SetTitle("; r;Relative Uncertainty");
        h1_r_ptbinned_sys->GetYaxis()->SetTitleOffset(1.);
        h1_r_ptbinned_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_r_ptbinned_sys->GetYaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys->GetXaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys->SetFillColorAlpha(16, 0.3);
        h1_r_ptbinned_sys->SetLineColorAlpha(16, 0.3);
        h1_r_ptbinned_sys->Draw("HIST SAME");

        h1_r_ptbinned_sys_sym->SetTitle("; r;Relative Uncertainty");
        h1_r_ptbinned_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_r_ptbinned_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_r_ptbinned_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_r_ptbinned_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_r_ptbinned_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = j + 22;
        if (j + 1 == 10)
          color = 15;

        h1_r_ptbinned_sys->SetTitle("; r;Relative Uncertainty");
        h1_r_ptbinned_sys->GetYaxis()->SetTitleOffset(1.);
        h1_r_ptbinned_sys->GetXaxis()->SetTitleOffset(1.);

        h1_r_ptbinned_sys->GetYaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys->GetXaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys->SetMarkerStyle(vec_markers[j]);
        h1_r_ptbinned_sys->SetMarkerColor(color);
        h1_r_ptbinned_sys->SetLineColor(color);
        h1_r_ptbinned_sys->Draw("P SAME");

        h1_r_ptbinned_sys_sym->SetTitle("; r;Relative Uncertainty");
        h1_r_ptbinned_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_r_ptbinned_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_r_ptbinned_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_r_ptbinned_sys_sym->SetMarkerStyle(vec_markers[j]);
        h1_r_ptbinned_sys_sym->SetMarkerColor(color);
        h1_r_ptbinned_sys_sym->SetLineColor(color);
        h1_r_ptbinned_sys_sym->Draw("P SAME");
      }
      legend_r_ptbinned->AddEntry(h1_r_ptbinned_sys, vec_string[j]);
      
      h1_r_ptbinned_sys->SetMaximum(1.0);
      h1_r_ptbinned_sys->SetMinimum(-1.0);
    }
    
    legend_r_ptbinned->Draw("SAME");    
    
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));    
    Tl.DrawLatex(0.2, top - step, Form("%.1f < p_{T,jet} < %.1f", pt_binedges[i], pt_binedges[i+1]));    
    
    ccan[ican]->SaveAs(loc_plots + Form("r_total_sys_contributions_pt%d.png", i));    
    
    ccan[ican]->cd();
    ccan[ican]->Update();
    if (ican == 0)
    {
      ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
      ccan[ican]->Print(plotfilePDF.Data());
    }         

  //
  cout << "pt bin " << i << endl;
  //
  //h1_z_ptbinned_sys_total[i-1]->Write();
  //h1_jt_ptbinned_sys_total[i-1]->Write();
  //h1_r_ptbinned_sys_total[i-1]->Write();    
  } // end pt bin loop

  textables << "\\end{longtable}\n";

  
  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }                    
  //file_save->Write();
  file_save->Close();
}

