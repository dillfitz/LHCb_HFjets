#include <TCanvas.h>
#include <vector>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include <iostream>
#include "../Settings.h"
#include "../../Helpers.h"
using namespace std;

void GetTotalSys(int NumEvts = -1,
                 int dataset = 91599,
                 bool chargedJetCut = false,
                 bool WTA_cut = true,
                 double minimum_dR = 0.1,
                 int NumIters = 3)
{

  TString string_matching, string_JESPos, string_JESNeg, string_JER, string_fspeff, string_fsppt,
      string_closure, string_unfold, string_unfold_rev, extension, string_ghost, string_jetid;
  TString string_trackingsysup, string_trackingsysdown, string_pidsysup, string_pidsysdown;
  TString string_trigsysup, string_trigsysdown, string_recselsys;
  TString string_itersysup, string_itersysdown;
  TString string_massfitsysnear, string_massfitsysfar;
  TString string_unfold_upONdown, string_unfold_downONup, string_unfold_smeartest, string_priorsys;
  TString str_followHard, str_ghost, str_charged, str_Mag, str_flavor, str_DTF(""), str_PID("");
  TString loc_hists("$LUND/Bjets/hists/");
  TString loc_plots("$LUND/Bjets/plots/");

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

  string_matching = loc_hists + TString("reverse_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_JER = loc_hists + TString("JER_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_JESNeg = loc_hists + TString("JESNeg_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_JESPos = loc_hists + TString("JESPos_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_fspeff = loc_hists + TString("fspeff_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_fsppt = loc_hists + TString("fsppt_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_ghost = loc_hists + TString("ghostcut_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_jetid = loc_hists + TString("jetid_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trackingsysup = loc_hists + TString("trackingsysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trackingsysdown = loc_hists + TString("trackingsysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_pidsysup = loc_hists + TString("pidsysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_pidsysdown = loc_hists + TString("pidsysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trigsysup = loc_hists + TString("trigsysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_trigsysdown = loc_hists + TString("trigsysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_itersysup = loc_hists + TString("itersysup_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_itersysdown = loc_hists + TString("itersysdown_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_massfitsysnear = loc_hists + TString("massfitsysnear_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_massfitsysfar = loc_hists + TString("massfitsysfar_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_recselsys = loc_hists + TString("recselsys_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  string_unfold_upONdown = loc_hists + TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + "_MU" + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d_%d", NumIters, NumIters) + Form("_%d", 91591) + Form("_%d", 91590);
  string_unfold_downONup = loc_hists + TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + "_MD" + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d_%d", NumIters, NumIters) + Form("_%d", 91590) + Form("_%d", 91591);
  string_unfold_smeartest = loc_hists + TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d_%d", NumIters, NumIters) + Form("_%d", 91599) + Form("_%d", 91599);
  string_priorsys = loc_hists + TString("priorsys_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);

  // string_closure = loc_hists + TString("closure") + Form("_ev_%d", NumEvts)
  //           + Form("_ptj_%d%d", int(ptMin), int(ptMax))
  //           + Form("_eta_%.1f%.1f", etaMin, etaMax)
  //           +  str_followHard
  //           +  str_ghost
  //           +  Form("_dR_%.2f", minimum_dR)
  //           + str_charged + "MD"
  //           + str_flavor +  Form("_%d", 1) + Form("_%d", 1)
  //           + Form("_%d", 93190) +  Form("_%d", 93191);

  // string_reco = loc + "hists/reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_data = loc + "hists/data_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_truth = loc + "hists/truth_ev_-1_ptj_20150_eta_2.54.0_hard_udsg_93139.root";
  // string_eff = loc + "hists/eff_truth_ev_-1_ptj_20150_eta_2.54.0_hard_udsg_93139.root";
  // string_unfold = loc + "hists/unfold_reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";

  extension = TString("total_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);

  cout << string_matching << endl;
  cout << string_closure << endl;
  cout << string_JER << endl;
  cout << string_JESPos << endl;
  cout << string_fspeff << endl;
  cout << string_fsppt << endl;
  /////////////////////   Get Files /////////////////////////////////

  TFile *file_matching = new TFile(string_matching + TString(".root"), "READ");
  TFile *file_fspeff = new TFile(string_fspeff + TString(".root"), "READ");
  TFile *file_fsppt = new TFile(string_fsppt + TString(".root"), "READ");
  TFile *file_jetid = new TFile(string_jetid + TString(".root"), "READ");
  TFile *file_JER = new TFile(string_JER + TString(".root"), "READ");
  TFile *file_JESNeg = new TFile(string_JESNeg + TString(".root"), "READ");
  TFile *file_JESPos = new TFile(string_JESPos + TString(".root"), "READ");
  TFile *file_ghost = new TFile(string_JESPos + TString(".root"), "READ");

  TFile *file_trackingsysup = new TFile(string_trackingsysup + TString(".root"), "READ");
  TFile *file_trackingsysdown = new TFile(string_trackingsysdown + TString(".root"), "READ");
  TFile *file_trigsysup = new TFile(string_trigsysup + TString(".root"), "READ");
  TFile *file_trigsysdown = new TFile(string_trigsysdown + TString(".root"), "READ");
  TFile *file_itersysup = new TFile(string_itersysup + TString(".root"), "READ");
  TFile *file_itersysdown = new TFile(string_itersysdown + TString(".root"), "READ");

  TFile *file_massfitsysnear = new TFile(string_massfitsysnear + TString(".root"), "READ");
  TFile *file_massfitsysfar = new TFile(string_massfitsysfar + TString(".root"), "READ");

  TFile *file_pidsysup = new TFile(string_pidsysup + TString(".root"), "READ");
  TFile *file_pidsysdown = new TFile(string_pidsysdown + TString(".root"), "READ");
  TFile *file_recselsys = new TFile(string_recselsys + TString(".root"), "READ");

  TFile *file_unfold_upONdown = new TFile(string_unfold_upONdown + TString(".root"), "READ");
  TFile *file_unfold_downONup = new TFile(string_unfold_downONup + TString(".root"), "READ");

  TFile *file_unfold_smeartest = new TFile(string_unfold_smeartest + TString(".root"), "READ");
  TFile *file_priorsys = new TFile(string_priorsys + TString(".root"), "READ");

  TFile *file_save = new TFile(loc_hists + extension + ".root", "RECREATE");

  /////////////////////   Get Systematic histograms /////////////////////////////////
  vector<TH2D *> vec_sys_ptktdR;
  vector<int> vec_markers = {21, 22, 23, 34, 33, 45, 47, 48, 49, 24, 25, 26, 27, 28, 29, 30, 31, 32, 43};
  vector<TString> vec_string = {"Matching Proc.",
                                "FSP Eff.",
                                "FSP p_{T}",
                                "Jet ID",
                                "JER",
                                "JES +1 #sigma",
                                "JES -1 #sigma",
                                "Track Eff. +1 #sigma",
                                "Track Eff. -1 #sigma",
                                "PID Eff. +1 #sigma",
                                "PID Eff. -1 #sigma",
                                "Trig. Eff. +1 #sigma",
                                "Trig. Eff. -1 #sigma",
                                "Sideband Var. 1",
                                "Sideband Var. 2",
                                "Rec. & Sel. Eff.",
                                "Unfolding",
                                "Total"};

  TH2D *h2_ptktdR_sys_matching = (TH2D *)file_matching->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_fspeff = (TH2D *)file_fspeff->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_fsppt = (TH2D *)file_fsppt->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_jetid = (TH2D *)file_jetid->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_jer = (TH2D *)file_JER->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_jesneg = (TH2D *)file_JESNeg->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_jespos = (TH2D *)file_JESPos->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_trackingsysup = (TH2D *)file_trackingsysup->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_trackingsysdown = (TH2D *)file_trackingsysdown->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_trigsysup = (TH2D *)file_trigsysup->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_trigsysdown = (TH2D *)file_trigsysdown->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_itersysup = (TH2D *)file_itersysup->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_itersysdown = (TH2D *)file_itersysdown->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_massfitsysnear = (TH2D *)file_massfitsysnear->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_massfitsysfar = (TH2D *)file_massfitsysfar->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_pidsysup = (TH2D *)file_pidsysup->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_pidsysdown = (TH2D *)file_pidsysdown->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_recselsys = (TH2D *)file_recselsys->Get("ptktdR_ratio");
  // TH2D *h2_ptktdR_sys_ghost = (TH2D *)file_ghost->Get("ptktdR_ratio");
  TH2D *h2_ptktdR_sys_priorsys = (TH2D *)file_priorsys->Get("ptktdR_ratio");

  cout << "Handling Closure" << endl;
  TH2D *h2_ptktdR_sys_closure_up = (TH2D *)file_unfold_upONdown->Get("h2_ptktdR_ratio_final");
  TH2D *h2_ptktdR_sys_closure_down = (TH2D *)file_unfold_downONup->Get("h2_ptktdR_ratio_final");
  TH2D *h2_ptktdR_sys_closure_smeartest = (TH2D *)file_unfold_smeartest->Get("h2_ptktdR_closure_error");
  // SubtractUnity(h2_ptktdR_sys_closure_up);
  // SubtractUnity(h2_ptktdR_sys_closure_down);
  // SetAbsHist(h2_ptktdR_sys_closure_up);
  // SetAbsHist(h2_ptktdR_sys_closure_down);
  // TH2D *h2_ptktdR_sys_closure = (TH2D *)h2_ptktdR_sys_closure_up->Clone("h2_ptktdR_sys_closure");
  // h2_ptktdR_sys_closure->Add(h2_ptktdR_sys_closure_down);
  // h2_ptktdR_sys_closure->Scale(0.5);

  TH2D *h2_ptktdR_sys_closure = (TH2D *)h2_ptktdR_sys_closure_smeartest->Clone("h2_ptktdR_sys_closure");

  cout << "Creating new histograms" << endl;

  TH2D *h2_ptktdR_sys_matching_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_matching_sq");
  TH2D *h2_ptktdR_sys_fspeff_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_fspeff_sq");
  TH2D *h2_ptktdR_sys_fsppt_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_fsppt_sq");
  TH2D *h2_ptktdR_sys_jer_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_jer_sq");
  TH2D *h2_ptktdR_sys_jetid_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_jetid_sq");
  TH2D *h2_ptktdR_sys_jesneg_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_jesneg_sq");
  TH2D *h2_ptktdR_sys_jespos_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_jespos_sq");
  TH2D *h2_ptktdR_sys_trackingsysup_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_trackingsysup_sq");
  TH2D *h2_ptktdR_sys_trackingsysdown_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_trackingsysdown_sq");
  TH2D *h2_ptktdR_sys_trigsysup_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_trigsysup_sq");
  TH2D *h2_ptktdR_sys_trigsysdown_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_trigsysdown_sq");
  TH2D *h2_ptktdR_sys_massfitsysnear_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_massfitsysnear_sq");
  TH2D *h2_ptktdR_sys_massfitsysfar_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_massfitsysfar_sq");
  TH2D *h2_ptktdR_sys_pidsysup_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_pidsysup_sq");
  TH2D *h2_ptktdR_sys_pidsysdown_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_pidsysdown_sq");
  TH2D *h2_ptktdR_sys_recselsys_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_recselsys_sq");
  // TH2D *h2_ptktdR_sys_ghost_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_ghost_sq");
  TH2D *h2_ptktdR_sys_priorsys_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_priorsys_sq");
  TH2D *h2_ptktdR_sys_itersysup_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_itersysup_sq");
  TH2D *h2_ptktdR_sys_itersysdown_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_itersysdown_sq");

  TH2D *h2_ptktdR_sys_closure_sq = (TH2D *)h2_ptktdR_sys_matching->Clone("h2_ptktdR_sys_closure_sq");

  cout << "Creating new histograms" << endl;

  vec_sys_ptktdR.push_back(h2_ptktdR_sys_matching);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_fspeff);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_fsppt);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_jetid);

  vec_sys_ptktdR.push_back(h2_ptktdR_sys_jer);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_jespos);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_jesneg);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_trackingsysup);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_trackingsysdown);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_pidsysup);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_pidsysdown);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_trigsysup);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_trigsysdown);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_massfitsysnear);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_massfitsysfar);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_recselsys);
  // vec_sys_ptktdR.push_back(h2_ptktdR_sys_ghost);
  vec_sys_ptktdR.push_back(h2_ptktdR_sys_closure);

  cout << "After push back" << endl;

  TH2D *h2_ptktdR_sys_total = (TH2D *)h2_ptktdR_sys_matching->Clone("ptktdR_total_sys");

  // SetHistConst(h2_ptktdR_sys_closure, 0.04);
  SetHistConst(h2_ptktdR_sys_total, 0.);
  h2_ptktdR_sys_matching_sq->Multiply(h2_ptktdR_sys_matching, h2_ptktdR_sys_matching);
  h2_ptktdR_sys_fspeff_sq->Multiply(h2_ptktdR_sys_fspeff, h2_ptktdR_sys_fspeff);
  h2_ptktdR_sys_fsppt_sq->Multiply(h2_ptktdR_sys_fsppt, h2_ptktdR_sys_fsppt);
  h2_ptktdR_sys_jer_sq->Multiply(h2_ptktdR_sys_jer, h2_ptktdR_sys_jer);
  h2_ptktdR_sys_jetid_sq->Multiply(h2_ptktdR_sys_jetid, h2_ptktdR_sys_jetid);
  h2_ptktdR_sys_jesneg_sq->Multiply(h2_ptktdR_sys_jesneg, h2_ptktdR_sys_jesneg);
  h2_ptktdR_sys_jespos_sq->Multiply(h2_ptktdR_sys_jespos, h2_ptktdR_sys_jespos);
  h2_ptktdR_sys_trackingsysup_sq->Multiply(h2_ptktdR_sys_trackingsysup, h2_ptktdR_sys_trackingsysup);
  h2_ptktdR_sys_trackingsysdown_sq->Multiply(h2_ptktdR_sys_trackingsysdown, h2_ptktdR_sys_trackingsysdown);
  h2_ptktdR_sys_trigsysup_sq->Multiply(h2_ptktdR_sys_trigsysup, h2_ptktdR_sys_trigsysup);
  h2_ptktdR_sys_trigsysdown_sq->Multiply(h2_ptktdR_sys_trigsysdown, h2_ptktdR_sys_trigsysdown);
  h2_ptktdR_sys_massfitsysnear_sq->Multiply(h2_ptktdR_sys_massfitsysnear, h2_ptktdR_sys_massfitsysnear);
  h2_ptktdR_sys_massfitsysfar_sq->Multiply(h2_ptktdR_sys_massfitsysfar, h2_ptktdR_sys_massfitsysfar);
  h2_ptktdR_sys_pidsysup_sq->Multiply(h2_ptktdR_sys_pidsysup, h2_ptktdR_sys_pidsysup);
  h2_ptktdR_sys_pidsysdown_sq->Multiply(h2_ptktdR_sys_pidsysdown, h2_ptktdR_sys_pidsysdown);
  h2_ptktdR_sys_recselsys_sq->Multiply(h2_ptktdR_sys_recselsys, h2_ptktdR_sys_recselsys);
  // h2_ptktdR_sys_ghost_sq->Multiply(h2_ptktdR_sys_ghost, h2_ptktdR_sys_ghost);
  h2_ptktdR_sys_priorsys_sq->Multiply(h2_ptktdR_sys_priorsys, h2_ptktdR_sys_priorsys);
  h2_ptktdR_sys_itersysup_sq->Multiply(h2_ptktdR_sys_itersysup, h2_ptktdR_sys_itersysup);
  h2_ptktdR_sys_itersysdown_sq->Multiply(h2_ptktdR_sys_itersysdown, h2_ptktdR_sys_itersysdown);

  cout << "After squaring" << endl;

  h2_ptktdR_sys_closure_sq->Multiply(h2_ptktdR_sys_closure, h2_ptktdR_sys_closure);
  h2_ptktdR_sys_closure_sq->Add(h2_ptktdR_sys_priorsys_sq);
  h2_ptktdR_sys_closure_sq->Add(h2_ptktdR_sys_itersysup_sq);
  h2_ptktdR_sys_closure_sq->Add(h2_ptktdR_sys_itersysdown_sq);

  cout << "After closure " << endl;

  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_matching_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_fspeff_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_fsppt_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_jetid_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_jer_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_jesneg_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_jespos_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_trackingsysup_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_trackingsysdown_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_trigsysup_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_trigsysdown_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_massfitsysnear_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_massfitsysfar_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_pidsysup_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_pidsysdown_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_recselsys_sq);
  h2_ptktdR_sys_total->Add(h2_ptktdR_sys_closure_sq);
  // h2_ptktdR_sys_total->Add(h2_ptktdR_sys_ghost_sq);
  GetSqrtHist(h2_ptktdR_sys_total);

  vec_sys_ptktdR.push_back(h2_ptktdR_sys_total);

  /////////////////////   Get Systematic histograms /////////////////////////////////
  vector<TH2D *> vec_sys_ptzdR;
  TH2D *h2_ptzdR_sys_matching = (TH2D *)file_matching->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_fspeff = (TH2D *)file_fspeff->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_fsppt = (TH2D *)file_fsppt->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_jetid = (TH2D *)file_jetid->Get("ptzdR_ratio");

  TH2D *h2_ptzdR_sys_jer = (TH2D *)file_JER->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_jesneg = (TH2D *)file_JESNeg->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_jespos = (TH2D *)file_JESPos->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_trackingsysup = (TH2D *)file_trackingsysup->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_trackingsysdown = (TH2D *)file_trackingsysdown->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_trigsysup = (TH2D *)file_trigsysup->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_trigsysdown = (TH2D *)file_trigsysdown->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_itersysup = (TH2D *)file_itersysup->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_itersysdown = (TH2D *)file_itersysdown->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_massfitsysnear = (TH2D *)file_massfitsysnear->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_massfitsysfar = (TH2D *)file_massfitsysfar->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_pidsysup = (TH2D *)file_pidsysup->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_pidsysdown = (TH2D *)file_pidsysdown->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_recselsys = (TH2D *)file_recselsys->Get("ptzdR_ratio");
  // TH2D *h2_ptzdR_sys_ghost = (TH2D *)file_ghost->Get("ptzdR_ratio");
  TH2D *h2_ptzdR_sys_priorsys = (TH2D *)file_priorsys->Get("ptzdR_ratio");

  cout << "Handling Closure" << endl;
  TH2D *h2_ptzdR_sys_closure_up = (TH2D *)file_unfold_upONdown->Get("h2_ptzdR_ratio_final");
  TH2D *h2_ptzdR_sys_closure_down = (TH2D *)file_unfold_downONup->Get("h2_ptzdR_ratio_final");
  TH2D *h2_ptzdR_sys_closure_smeartest = (TH2D *)file_unfold_smeartest->Get("h2_ptzdR_closure_error");
  // SubtractUnity(h2_ptzdR_sys_closure_up);
  // SubtractUnity(h2_ptzdR_sys_closure_down);
  // SetAbsHist(h2_ptzdR_sys_closure_up);
  // SetAbsHist(h2_ptzdR_sys_closure_down);
  // TH2D *h2_ptzdR_sys_closure = (TH2D *)h2_ptzdR_sys_closure_up->Clone("h2_ptzdR_sys_closure");
  // h2_ptzdR_sys_closure->Add(h2_ptzdR_sys_closure_down);
  // h2_ptzdR_sys_closure->Scale(0.5);

  TH2D *h2_ptzdR_sys_closure = (TH2D *)h2_ptzdR_sys_closure_smeartest->Clone("h2_ptzdR_sys_closure");

  cout << "Creating new histograms" << endl;

  TH2D *h2_ptzdR_sys_matching_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_matching_sq");
  TH2D *h2_ptzdR_sys_fspeff_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_fspeff_sq");
  TH2D *h2_ptzdR_sys_fsppt_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_fsppt_sq");
  TH2D *h2_ptzdR_sys_jetid_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_jetid_sq");

  TH2D *h2_ptzdR_sys_jer_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_jer_sq");
  TH2D *h2_ptzdR_sys_jesneg_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_jesneg_sq");
  TH2D *h2_ptzdR_sys_jespos_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_jespos_sq");
  TH2D *h2_ptzdR_sys_trackingsysup_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_trackingsysup_sq");
  TH2D *h2_ptzdR_sys_trackingsysdown_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_trackingsysdown_sq");
  TH2D *h2_ptzdR_sys_trigsysup_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_trigsysup_sq");
  TH2D *h2_ptzdR_sys_trigsysdown_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_trigsysdown_sq");
  TH2D *h2_ptzdR_sys_itersysup_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_itersysup_sq");
  TH2D *h2_ptzdR_sys_itersysdown_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_itersysdown_sq");
  TH2D *h2_ptzdR_sys_massfitsysnear_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_massfitsysnear_sq");
  TH2D *h2_ptzdR_sys_massfitsysfar_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_massfitsysfar_sq");
  TH2D *h2_ptzdR_sys_pidsysup_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_pidsysup_sq");
  TH2D *h2_ptzdR_sys_pidsysdown_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_pidsysdown_sq");
  TH2D *h2_ptzdR_sys_recselsys_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_recselsys_sq");
  // TH2D *h2_ptzdR_sys_ghost_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_ghost_sq");
  TH2D *h2_ptzdR_sys_priorsys_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_priorsys_sq");

  TH2D *h2_ptzdR_sys_closure_sq = (TH2D *)h2_ptzdR_sys_matching->Clone("h2_ptzdR_sys_closure_sq");

  cout << "Creating new histograms" << endl;

  vec_sys_ptzdR.push_back(h2_ptzdR_sys_matching);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_fspeff);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_fsppt);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_jetid);

  vec_sys_ptzdR.push_back(h2_ptzdR_sys_jer);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_jespos);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_jesneg);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_trackingsysup);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_trackingsysdown);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_pidsysup);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_pidsysdown);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_trigsysup);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_trigsysdown);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_massfitsysnear);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_massfitsysfar);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_recselsys);
  // vec_sys_ptzdR.push_back(h2_ptzdR_sys_ghost);
  vec_sys_ptzdR.push_back(h2_ptzdR_sys_closure);

  cout << "After push back" << endl;

  TH2D *h2_ptzdR_sys_total = (TH2D *)h2_ptzdR_sys_matching->Clone("ptzdR_total_sys");

  // SetHistConst(h2_ptzdR_sys_closure, 0.04);
  SetHistConst(h2_ptzdR_sys_total, 0.);
  h2_ptzdR_sys_matching_sq->Multiply(h2_ptzdR_sys_matching, h2_ptzdR_sys_matching);
  h2_ptzdR_sys_fspeff_sq->Multiply(h2_ptzdR_sys_fspeff, h2_ptzdR_sys_fspeff);
  h2_ptzdR_sys_fsppt_sq->Multiply(h2_ptzdR_sys_fsppt, h2_ptzdR_sys_fsppt);
  h2_ptzdR_sys_jetid_sq->Multiply(h2_ptzdR_sys_jetid, h2_ptzdR_sys_jetid);

  h2_ptzdR_sys_jer_sq->Multiply(h2_ptzdR_sys_jer, h2_ptzdR_sys_jer);
  h2_ptzdR_sys_jesneg_sq->Multiply(h2_ptzdR_sys_jesneg, h2_ptzdR_sys_jesneg);
  h2_ptzdR_sys_jespos_sq->Multiply(h2_ptzdR_sys_jespos, h2_ptzdR_sys_jespos);
  h2_ptzdR_sys_trackingsysup_sq->Multiply(h2_ptzdR_sys_trackingsysup, h2_ptzdR_sys_trackingsysup);
  h2_ptzdR_sys_trackingsysdown_sq->Multiply(h2_ptzdR_sys_trackingsysdown, h2_ptzdR_sys_trackingsysdown);
  h2_ptzdR_sys_trigsysup_sq->Multiply(h2_ptzdR_sys_trigsysup, h2_ptzdR_sys_trigsysup);
  h2_ptzdR_sys_trigsysdown_sq->Multiply(h2_ptzdR_sys_trigsysdown, h2_ptzdR_sys_trigsysdown);
  h2_ptzdR_sys_itersysup_sq->Multiply(h2_ptzdR_sys_itersysup, h2_ptzdR_sys_itersysup);
  h2_ptzdR_sys_itersysdown_sq->Multiply(h2_ptzdR_sys_itersysdown, h2_ptzdR_sys_itersysdown);
  h2_ptzdR_sys_massfitsysnear_sq->Multiply(h2_ptzdR_sys_massfitsysnear, h2_ptzdR_sys_massfitsysnear);
  h2_ptzdR_sys_massfitsysfar_sq->Multiply(h2_ptzdR_sys_massfitsysfar, h2_ptzdR_sys_massfitsysfar);
  h2_ptzdR_sys_pidsysup_sq->Multiply(h2_ptzdR_sys_pidsysup, h2_ptzdR_sys_pidsysup);
  h2_ptzdR_sys_pidsysdown_sq->Multiply(h2_ptzdR_sys_pidsysdown, h2_ptzdR_sys_pidsysdown);
  h2_ptzdR_sys_recselsys_sq->Multiply(h2_ptzdR_sys_recselsys, h2_ptzdR_sys_recselsys);
  // h2_ptzdR_sys_ghost_sq->Multiply(h2_ptzdR_sys_ghost, h2_ptzdR_sys_ghost);
  h2_ptzdR_sys_priorsys_sq->Multiply(h2_ptzdR_sys_priorsys, h2_ptzdR_sys_priorsys);
  h2_ptzdR_sys_itersysup_sq->Multiply(h2_ptzdR_sys_itersysup, h2_ptzdR_sys_itersysup);
  h2_ptzdR_sys_itersysdown_sq->Multiply(h2_ptzdR_sys_itersysdown, h2_ptzdR_sys_itersysdown);

  cout << "After squaring" << endl;

  h2_ptzdR_sys_closure_sq->Multiply(h2_ptzdR_sys_closure, h2_ptzdR_sys_closure);
  h2_ptzdR_sys_closure_sq->Add(h2_ptzdR_sys_priorsys_sq);
  h2_ptzdR_sys_closure_sq->Add(h2_ptzdR_sys_itersysup_sq);
  h2_ptzdR_sys_closure_sq->Add(h2_ptzdR_sys_itersysdown_sq);

  cout << "After closure " << endl;

  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_matching_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_fspeff_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_fsppt_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_jetid_sq);

  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_jer_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_jesneg_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_jespos_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_trackingsysup_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_trackingsysdown_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_trigsysup_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_trigsysdown_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_massfitsysnear_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_massfitsysfar_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_pidsysup_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_pidsysdown_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_recselsys_sq);
  h2_ptzdR_sys_total->Add(h2_ptzdR_sys_closure_sq);
  // h2_ptzdR_sys_total->Add(h2_ptzdR_sys_ghost_sq);
  GetSqrtHist(h2_ptzdR_sys_total);

  vec_sys_ptzdR.push_back(h2_ptzdR_sys_total);

  /////////////////////   Get Systematic histograms /////////////////////////////////
  vector<TH2D *> vec_sys_ptthetaErad;
  TH2D *h2_ptthetaErad_sys_matching = (TH2D *)file_matching->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_fspeff = (TH2D *)file_fspeff->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_fsppt = (TH2D *)file_fsppt->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_jetid = (TH2D *)file_jetid->Get("ptthetaErad_ratio");

  TH2D *h2_ptthetaErad_sys_jer = (TH2D *)file_JER->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_jesneg = (TH2D *)file_JESNeg->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_jespos = (TH2D *)file_JESPos->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_trackingsysup = (TH2D *)file_trackingsysup->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_trackingsysdown = (TH2D *)file_trackingsysdown->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_trigsysup = (TH2D *)file_trigsysup->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_trigsysdown = (TH2D *)file_trigsysdown->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_massfitsysnear = (TH2D *)file_massfitsysnear->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_massfitsysfar = (TH2D *)file_massfitsysfar->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_pidsysup = (TH2D *)file_pidsysup->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_pidsysdown = (TH2D *)file_pidsysdown->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_recselsys = (TH2D *)file_recselsys->Get("ptthetaErad_ratio");
  // TH2D *h2_ptthetaErad_sys_ghost = (TH2D *)file_ghost->Get("ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_sys_closure_up = (TH2D *)file_unfold_upONdown->Get("h2_ptthetaErad_ratio_final");
  TH2D *h2_ptthetaErad_sys_closure_down = (TH2D *)file_unfold_downONup->Get("h2_ptthetaErad_ratio_final");
  TH2D *h2_ptthetaErad_sys_closure_smeartest = (TH2D *)file_unfold_smeartest->Get("h2_ptthetaErad_closure_error");
  // SubtractUnity(h2_ptthetaErad_sys_closure_up);
  // SubtractUnity(h2_ptthetaErad_sys_closure_down);
  // SetAbsHist(h2_ptthetaErad_sys_closure_up);
  // SetAbsHist(h2_ptthetaErad_sys_closure_down);
  // TH2D *h2_ptthetaErad_sys_closure = (TH2D *)h2_ptthetaErad_sys_closure_up->Clone("h2_ptthetaErad_sys_closure");
  // h2_ptthetaErad_sys_closure->Add(h2_ptthetaErad_sys_closure_down);
  // h2_ptthetaErad_sys_closure->Scale(0.5);

  TH2D *h2_ptthetaErad_sys_closure = (TH2D *)h2_ptthetaErad_sys_closure_smeartest->Clone("h2_ptthetaErad_sys_closure");

  TH2D *h2_ptthetaErad_sys_matching_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_matching_sq");
  TH2D *h2_ptthetaErad_sys_fspeff_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_fspeff_sq");
  TH2D *h2_ptthetaErad_sys_fsppt_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_fsppt_sq");
  TH2D *h2_ptthetaErad_sys_jetid_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_jetid_sq");

  TH2D *h2_ptthetaErad_sys_jer_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_jer_sq");
  TH2D *h2_ptthetaErad_sys_jesneg_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_jesneg_sq");
  TH2D *h2_ptthetaErad_sys_jespos_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_jespos_sq");
  TH2D *h2_ptthetaErad_sys_trackingsysup_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_trackingsysup_sq");
  TH2D *h2_ptthetaErad_sys_trackingsysdown_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_trackingsysdown_sq");
  TH2D *h2_ptthetaErad_sys_trigsysup_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_trigsysup_sq");
  TH2D *h2_ptthetaErad_sys_trigsysdown_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_trigsysdown_sq");
  TH2D *h2_ptthetaErad_sys_massfitsysnear_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_massfitsysnear_sq");
  TH2D *h2_ptthetaErad_sys_massfitsysfar_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_massfitsysfar_sq");
  TH2D *h2_ptthetaErad_sys_pidsysup_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_pidsysup_sq");
  TH2D *h2_ptthetaErad_sys_pidsysdown_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_pidsysdown_sq");
  TH2D *h2_ptthetaErad_sys_recselsys_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_recselsys_sq");
  // TH2D *h2_ptthetaErad_sys_ghost_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_ghost_sq");
  TH2D *h2_ptthetaErad_sys_closure_sq = (TH2D *)h2_ptthetaErad_sys_matching->Clone("h2_ptthetaErad_sys_closure_sq");

  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_matching);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_fspeff);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_fsppt);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_jetid);

  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_jer);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_jespos);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_jesneg);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_trackingsysup);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_trackingsysdown);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_pidsysup);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_pidsysdown);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_trigsysup);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_trigsysdown);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_massfitsysnear);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_massfitsysfar);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_recselsys);
  // vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_ghost);
  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_closure);

  TH2D *h2_ptthetaErad_sys_total = (TH2D *)h2_ptthetaErad_sys_matching->Clone("ptthetaErad_total_sys");

  // SetHistConst(h2_ptthetaErad_sys_closure, 0.04);
  SetHistConst(h2_ptthetaErad_sys_total, 0.);
  h2_ptthetaErad_sys_matching_sq->Multiply(h2_ptthetaErad_sys_matching, h2_ptthetaErad_sys_matching);
  h2_ptthetaErad_sys_fspeff_sq->Multiply(h2_ptthetaErad_sys_fspeff, h2_ptthetaErad_sys_fspeff);
  h2_ptthetaErad_sys_fsppt_sq->Multiply(h2_ptthetaErad_sys_fsppt, h2_ptthetaErad_sys_fsppt);
  h2_ptthetaErad_sys_jetid_sq->Multiply(h2_ptthetaErad_sys_jetid, h2_ptthetaErad_sys_jetid);

  h2_ptthetaErad_sys_jer_sq->Multiply(h2_ptthetaErad_sys_jer, h2_ptthetaErad_sys_jer);
  h2_ptthetaErad_sys_jesneg_sq->Multiply(h2_ptthetaErad_sys_jesneg, h2_ptthetaErad_sys_jesneg);
  h2_ptthetaErad_sys_jespos_sq->Multiply(h2_ptthetaErad_sys_jespos, h2_ptthetaErad_sys_jespos);
  h2_ptthetaErad_sys_trackingsysup_sq->Multiply(h2_ptthetaErad_sys_trackingsysup, h2_ptthetaErad_sys_trackingsysup);
  h2_ptthetaErad_sys_trackingsysdown_sq->Multiply(h2_ptthetaErad_sys_trackingsysdown, h2_ptthetaErad_sys_trackingsysdown);
  h2_ptthetaErad_sys_trigsysup_sq->Multiply(h2_ptthetaErad_sys_trigsysup, h2_ptthetaErad_sys_trigsysup);
  h2_ptthetaErad_sys_trigsysdown_sq->Multiply(h2_ptthetaErad_sys_trigsysdown, h2_ptthetaErad_sys_trigsysdown);
  h2_ptthetaErad_sys_massfitsysnear_sq->Multiply(h2_ptthetaErad_sys_massfitsysnear, h2_ptthetaErad_sys_massfitsysnear);
  h2_ptthetaErad_sys_massfitsysfar_sq->Multiply(h2_ptthetaErad_sys_massfitsysfar, h2_ptthetaErad_sys_massfitsysfar);
  h2_ptthetaErad_sys_pidsysup_sq->Multiply(h2_ptthetaErad_sys_pidsysup, h2_ptthetaErad_sys_pidsysup);
  h2_ptthetaErad_sys_pidsysdown_sq->Multiply(h2_ptthetaErad_sys_pidsysdown, h2_ptthetaErad_sys_pidsysdown);
  h2_ptthetaErad_sys_recselsys_sq->Multiply(h2_ptthetaErad_sys_recselsys, h2_ptthetaErad_sys_recselsys);
  // h2_ptthetaErad_sys_ghost_sq->Multiply(h2_ptthetaErad_sys_ghost, h2_ptthetaErad_sys_ghost);
  h2_ptthetaErad_sys_closure_sq->Multiply(h2_ptthetaErad_sys_closure, h2_ptthetaErad_sys_closure);

  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_matching_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_fspeff_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_fsppt_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_jetid_sq);

  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_jer_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_jesneg_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_jespos_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_trackingsysup_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_trackingsysdown_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_trigsysup_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_trigsysdown_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_massfitsysnear_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_massfitsysfar_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_pidsysup_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_pidsysdown_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_recselsys_sq);
  // h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_ghost_sq);
  h2_ptthetaErad_sys_total->Add(h2_ptthetaErad_sys_closure_sq);
  GetSqrtHist(h2_ptthetaErad_sys_total);

  vec_sys_ptthetaErad.push_back(h2_ptthetaErad_sys_total);
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
  h2_ptktdR_sys_total->Draw("COLZ TEXTE");
  h2_ptktdR_sys_total->SetMaximum(0.3);
  h2_ptktdR_sys_total->SetMinimum(0.);
  h2_ptktdR_sys_total->SetTitle("Total Systematic");

  ccan[ican]->cd(2);
  h2_ptktdR_sys_jetid->Draw("COLZ TEXTE");
  h2_ptktdR_sys_jetid->SetMaximum(0.3);
  h2_ptktdR_sys_jetid->SetMinimum(-0.3);
  h2_ptktdR_sys_jetid->SetTitle("JetID efficiency");
  ccan[ican]->cd(3);
  h2_ptktdR_sys_closure->Draw("COLZ TEXTE");
  // h2_ptktdR_sys_closure->SetMaximum(0.3);
  // h2_ptktdR_sys_closure->SetMinimum(0.);
  h2_ptktdR_sys_closure->SetTitle("Non-Closure");

  ccan[ican]->cd(4);

  h2_ptktdR_sys_fspeff->Draw("COLZ TEXTE");
  h2_ptktdR_sys_fspeff->SetMaximum(0.3);
  h2_ptktdR_sys_fspeff->SetMinimum(-0.3);
  h2_ptktdR_sys_fspeff->SetTitle("FSP efficiency");

  // h2_ptktdR_->SetTitle("Data+Purity+Unfold; ;");

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
  h2_ptktdR_sys_fsppt->Draw("COLZ TEXTE");
  h2_ptktdR_sys_fsppt->SetMinimum(-0.3);
  h2_ptktdR_sys_fsppt->SetMaximum(0.3);
  h2_ptktdR_sys_fsppt->SetTitle("FSP p_{T}");
  ccan[ican]->cd(2);

  h2_ptktdR_sys_jesneg->Draw("COLZ TEXTE");
  h2_ptktdR_sys_jesneg->SetMinimum(-0.3);
  h2_ptktdR_sys_jesneg->SetMaximum(0.3);
  h2_ptktdR_sys_jesneg->SetTitle("JES -1#sigma");

  ccan[ican]->cd(3);
  h2_ptktdR_sys_jespos->Draw("COLZ TEXTE");
  h2_ptktdR_sys_jespos->SetMinimum(-0.3);
  h2_ptktdR_sys_jespos->SetMaximum(0.3);
  h2_ptktdR_sys_jespos->SetTitle("JES 1#sigma");

  ccan[ican]->cd(4);

  h2_ptktdR_sys_jer->Draw("COLZ TEXTE");
  h2_ptktdR_sys_jer->SetMinimum(-0.3);
  h2_ptktdR_sys_jer->SetMaximum(0.3);
  h2_ptktdR_sys_jer->SetTitle("JER");

  // h2_ptktdR_->SetTitle("Data+Purity+Unfold; ;");

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
  h2_ptktdR_sys_trigsysup->Draw("COLZ TEXTE");
  h2_ptktdR_sys_trigsysup->SetMinimum(-0.3);
  h2_ptktdR_sys_trigsysup->SetMaximum(0.3);
  h2_ptktdR_sys_trigsysup->SetTitle("Trig. +1#sigma");
  ccan[ican]->cd(2);

  h2_ptktdR_sys_trigsysdown->Draw("COLZ TEXTE");
  h2_ptktdR_sys_trigsysdown->SetMinimum(-0.3);
  h2_ptktdR_sys_trigsysdown->SetMaximum(0.3);
  h2_ptktdR_sys_trigsysdown->SetTitle("Trig. -1#sigma");

  ccan[ican]->cd(3);
  h2_ptktdR_sys_trackingsysup->Draw("COLZ TEXTE");
  h2_ptktdR_sys_trackingsysup->SetMinimum(-0.3);
  h2_ptktdR_sys_trackingsysup->SetMaximum(0.3);
  h2_ptktdR_sys_trackingsysup->SetTitle("Tracking +1#sigma");

  ccan[ican]->cd(4);

  h2_ptktdR_sys_trackingsysdown->Draw("COLZ TEXTE");
  h2_ptktdR_sys_trackingsysdown->SetMinimum(-0.3);
  h2_ptktdR_sys_trackingsysdown->SetMaximum(0.3);
  h2_ptktdR_sys_trackingsysdown->SetTitle("Tracking -1#sigma");

  // h2_ptktdR_->SetTitle("Data+Purity+Unfold; ;");

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
  h2_ptktdR_sys_massfitsysnear->Draw("COLZ TEXTE");
  h2_ptktdR_sys_massfitsysnear->SetMinimum(-0.3);
  h2_ptktdR_sys_massfitsysnear->SetMaximum(0.3);
  h2_ptktdR_sys_massfitsysnear->SetTitle("Sideband Var 1");
  ccan[ican]->cd(2);

  // h2_ptktdR_sys_ghost->Draw("COLZ TEXTE");
  // h2_ptktdR_sys_ghost->SetMinimum(-0.3);
  // h2_ptktdR_sys_ghost->SetMaximum(0.3);
  // h2_ptktdR_sys_ghost->SetTitle("ProbNNGhost Cut");

  ccan[ican]->cd(3);
  h2_ptktdR_sys_massfitsysfar->Draw("COLZ TEXTE");
  h2_ptktdR_sys_massfitsysfar->SetMinimum(-0.3);
  h2_ptktdR_sys_massfitsysfar->SetMaximum(0.3);
  h2_ptktdR_sys_massfitsysfar->SetTitle("Sideband Var 2");

  ccan[ican]->cd(4);
  h2_ptktdR_sys_recselsys->Draw("COLZ TEXTE");
  h2_ptktdR_sys_recselsys->SetMinimum(-0.3);
  h2_ptktdR_sys_recselsys->SetMaximum(0.3);
  h2_ptktdR_sys_recselsys->SetTitle("Rec. and Sel.");

  // h2_ptktdR_->SetTitle("Data+Purity+Unfold; ;");

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

  auto legend_ktdR = new TLegend(0.5, 0.5, 0.9, 0.85);
  legend_ktdR->SetBorderSize(0);
  legend_ktdR->SetFillStyle(0);
  legend_ktdR->SetFillColor(3);
  auto legend_stack_ktdR = new TLegend(0.6, 0.67, 0.8, 0.87);
  auto legend_stack_zdR = new TLegend(0.6, 0.67, 0.8, 0.87);
  // int n_slice[4] = {2, 3, 5, 8};
  const int slice_size = 7;
  int n_slice[slice_size] = {2, 3, 4, 5, 6, 7, 8};
  int n_slice_z[slice_size] = {3, 4, 5, 6, 7, 8, 9};
  for (int sl = 0; sl < slice_size; sl++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptktdR_sys("stack_ptktdR_sys%d", "");

    for (int i = 0; i < vec_sys_ptktdR.size(); i++)
    {
      SetHistErrorZero(vec_sys_ptktdR[i]);
      TH1D *h1_ptktdR_sys = (TH1D *)vec_sys_ptktdR[i]->ProjectionY(Form("h1_ptktdR_sys%d%d%d", n_slice[sl], i, sl), n_slice[sl], n_slice[sl]);
      TH1D *h1_ptktdR_sys_sym = (TH1D *)h1_ptktdR_sys->Clone(Form("h1_ptktdR_sys_sym%d%d%d", n_slice[sl], i, sl));
      h1_ptktdR_sys_sym->Scale(-1);

      if (i == vec_sys_ptktdR.size() - 1)
      {
        h1_ptktdR_sys->SetTitle("; ln(k_{T}/GeV);Relative Uncertainty");
        h1_ptktdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_ptktdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->SetFillColorAlpha(16, 0.3);
        h1_ptktdR_sys->SetLineColorAlpha(16, 0.3);
        h1_ptktdR_sys->Draw("HIST SAME");

        h1_ptktdR_sys_sym->SetTitle("; ln(k_{T}/GeV);Relative Uncertainty");
        h1_ptktdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptktdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_ptktdR_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_ptktdR_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = i + 22;
        if (i + 1 == 10)
          color = 15;

        h1_ptktdR_sys->SetTitle("; ln(k_{T}/GeV);Relative Uncertainty");
        h1_ptktdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys->GetXaxis()->SetTitleOffset(1.);

        h1_ptktdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->SetMarkerStyle(vec_markers[i]);
        h1_ptktdR_sys->SetMarkerColor(color);
        h1_ptktdR_sys->SetLineColor(color);
        h1_ptktdR_sys->Draw("P SAME");

        h1_ptktdR_sys_sym->SetTitle("; ln(k_{T}/GeV);Relative Uncertainty");
        h1_ptktdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptktdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->SetMarkerStyle(vec_markers[i]);
        h1_ptktdR_sys_sym->SetMarkerColor(color);
        h1_ptktdR_sys_sym->SetLineColor(color);
        h1_ptktdR_sys_sym->Draw("P SAME");
      }
      if (sl == 0)
        legend_ktdR->AddEntry(h1_ptktdR_sys, vec_string[i]);
      h1_ptktdR_sys->SetMaximum(0.50);
      h1_ptktdR_sys->SetMinimum(-0.30);
    }
    legend_ktdR->Draw("SAME");

    //  Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);
    double top = 0.85;
    double step = 0.06;
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - step, Form("p_{T,jet} > 20 GeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));
    Tl.DrawLatex(0.2, top - 3 * step, Form("%.2f<ln(R/#DeltaR)<%.2f", h2_ptktdR_sys_total->GetXaxis()->GetBinLowEdge(n_slice[sl]), h2_ptktdR_sys_total->GetXaxis()->GetBinLowEdge(n_slice[sl] + 1)));

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

  for (int sl = 0; sl < slice_size; sl++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptktdR_sys("stack_ptktdR_sys%d", "");

    for (int i = 0; i < vec_sys_ptktdR.size(); i++)
    {
      SetHistErrorZero(vec_sys_ptktdR[i]);
      TH1D *h1_ptktdR_sys = (TH1D *)vec_sys_ptktdR[i]->ProjectionX(Form("h1_ptktdRx_sys%d%d%d", n_slice[sl], i, sl), n_slice[sl], n_slice[sl]);
      TH1D *h1_ptktdR_sys_sym = (TH1D *)h1_ptktdR_sys->Clone(Form("h1_ptktdRx_sys_sym%d%d%d", n_slice[sl], i, sl));
      h1_ptktdR_sys_sym->Scale(-1);

      if (i == vec_sys_ptktdR.size() - 1)
      {
        h1_ptktdR_sys->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptktdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_ptktdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->SetFillColorAlpha(16, 0.3);
        h1_ptktdR_sys->SetLineColorAlpha(16, 0.3);
        h1_ptktdR_sys->Draw("HIST SAME");

        h1_ptktdR_sys_sym->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptktdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptktdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_ptktdR_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_ptktdR_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = i + 22;
        if (i + 1 == 10)
          color = 15;

        h1_ptktdR_sys->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptktdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys->GetXaxis()->SetTitleOffset(1.);

        h1_ptktdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys->SetMarkerStyle(vec_markers[i]);
        h1_ptktdR_sys->SetMarkerColor(color);
        h1_ptktdR_sys->SetLineColor(color);
        h1_ptktdR_sys->Draw("P SAME");

        h1_ptktdR_sys_sym->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptktdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptktdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptktdR_sys_sym->SetMarkerStyle(vec_markers[i]);
        h1_ptktdR_sys_sym->SetMarkerColor(color);
        h1_ptktdR_sys_sym->SetLineColor(color);
        h1_ptktdR_sys_sym->Draw("P SAME");
      }
      // if (sl == 0)
      //   legend_ktdR->AddEntry(h1_ptktdR_sys, vec_string[i]);
      h1_ptktdR_sys->SetMaximum(0.50);
      h1_ptktdR_sys->SetMinimum(-0.30);
    }
    legend_ktdR->Draw("SAME");

    //  Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);
    double top = 0.85;
    double step = 0.06;
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - step, Form("p_{T,jet} > 20 GeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));
    Tl.DrawLatex(0.2, top - 3 * step, Form("%.2f<ln(k_{T}/GeV)<%.2f", h2_ptktdR_sys_total->GetYaxis()->GetBinLowEdge(n_slice[sl]), h2_ptktdR_sys_total->GetYaxis()->GetBinLowEdge(n_slice[sl] + 1)));

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

  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
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
  h2_ptzdR_sys_total->Draw("COLZ TEXTE");
  h2_ptzdR_sys_total->SetMaximum(0.3);
  h2_ptzdR_sys_total->SetMinimum(0.);
  h2_ptzdR_sys_total->SetTitle("Total Systematic");

  ccan[ican]->cd(2);
  h2_ptzdR_sys_recselsys->Draw("COLZ TEXTE");
  ccan[ican]->cd(3);
  h2_ptzdR_sys_closure->Draw("COLZ TEXTE");
  // h2_ptzdR_sys_closure->SetMaximum(0.3);
  // h2_ptzdR_sys_closure->SetMinimum(0.);
  h2_ptzdR_sys_closure->SetTitle("Non-Closure");

  ccan[ican]->cd(4);

  h2_ptzdR_sys_fspeff->Draw("COLZ TEXTE");
  h2_ptzdR_sys_fspeff->SetMaximum(0.3);
  h2_ptzdR_sys_fspeff->SetMinimum(-0.3);
  h2_ptzdR_sys_fspeff->SetTitle("FSP efficiency");

  // h2_ptzdR_->SetTitle("Data+Purity+Unfold; ;");

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
  h2_ptzdR_sys_fsppt->Draw("COLZ TEXTE");
  h2_ptzdR_sys_fsppt->SetMinimum(-0.3);
  h2_ptzdR_sys_fsppt->SetMaximum(0.3);
  h2_ptzdR_sys_fsppt->SetTitle("FSP p_{T}");
  ccan[ican]->cd(2);

  h2_ptzdR_sys_jesneg->Draw("COLZ TEXTE");
  h2_ptzdR_sys_jesneg->SetMinimum(-0.3);
  h2_ptzdR_sys_jesneg->SetMaximum(0.3);
  h2_ptzdR_sys_jesneg->SetTitle("JES -1#sigma");

  ccan[ican]->cd(3);
  h2_ptzdR_sys_jespos->Draw("COLZ TEXTE");
  h2_ptzdR_sys_jespos->SetMinimum(-0.3);
  h2_ptzdR_sys_jespos->SetMaximum(0.3);
  h2_ptzdR_sys_jespos->SetTitle("JES 1#sigma");

  ccan[ican]->cd(4);

  h2_ptzdR_sys_jer->Draw("COLZ TEXTE");
  h2_ptzdR_sys_jer->SetMinimum(-0.3);
  h2_ptzdR_sys_jer->SetMaximum(0.3);
  h2_ptzdR_sys_jer->SetTitle("JER");

  // h2_ptzdR_->SetTitle("Data+Purity+Unfold; ;");

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
  h2_ptzdR_sys_matching->Draw("COLZ TEXTE");
  h2_ptzdR_sys_matching->SetMinimum(-0.3);
  h2_ptzdR_sys_matching->SetMaximum(0.3);
  h2_ptzdR_sys_matching->SetTitle("Matching");
  ccan[ican]->cd(2);

  h2_ptzdR_sys_trackingsysup->Draw("COLZ TEXTE");
  h2_ptzdR_sys_trackingsysup->SetMinimum(-0.3);
  h2_ptzdR_sys_trackingsysup->SetMaximum(0.3);
  h2_ptzdR_sys_trackingsysup->SetTitle("Track Sys. +1#sigma");

  ccan[ican]->cd(3);
  h2_ptzdR_sys_trackingsysdown->Draw("COLZ TEXTE");
  h2_ptzdR_sys_trackingsysdown->SetMinimum(-0.3);
  h2_ptzdR_sys_trackingsysdown->SetMaximum(0.3);
  h2_ptzdR_sys_trackingsysdown->SetTitle("JES -1#sigma");

  ccan[ican]->cd(4);

  h2_ptzdR_sys_pidsysup->Draw("COLZ TEXTE");
  h2_ptzdR_sys_pidsysup->SetMinimum(-0.3);
  h2_ptzdR_sys_pidsysup->SetMaximum(0.3);
  h2_ptzdR_sys_pidsysup->SetTitle("PID +1#sigma");

  // h2_ptzdR_->SetTitle("Data+Purity+Unfold; ;");

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
  h2_ptzdR_sys_pidsysdown->Draw("COLZ TEXTE");
  h2_ptzdR_sys_pidsysdown->SetMinimum(-0.3);
  h2_ptzdR_sys_pidsysdown->SetMaximum(0.3);
  h2_ptzdR_sys_pidsysdown->SetTitle("pidsysdown");
  ccan[ican]->cd(2);

  h2_ptzdR_sys_trigsysup->Draw("COLZ TEXTE");
  h2_ptzdR_sys_trigsysup->SetMinimum(-0.3);
  h2_ptzdR_sys_trigsysup->SetMaximum(0.3);
  h2_ptzdR_sys_trigsysup->SetTitle("Track Sys. +1#sigma");

  ccan[ican]->cd(3);
  h2_ptzdR_sys_trigsysdown->Draw("COLZ TEXTE");
  h2_ptzdR_sys_trigsysdown->SetMinimum(-0.3);
  h2_ptzdR_sys_trigsysdown->SetMaximum(0.3);
  h2_ptzdR_sys_trigsysdown->SetTitle("JES -1#sigma");

  ccan[ican]->cd(4);

  h2_ptzdR_sys_massfitsysnear->Draw("COLZ TEXTE");
  h2_ptzdR_sys_massfitsysnear->SetMinimum(-0.3);
  h2_ptzdR_sys_massfitsysnear->SetMaximum(0.3);
  h2_ptzdR_sys_massfitsysnear->SetTitle("PID +1#sigma");

  // h2_ptzdR_->SetTitle("Data+Purity+Unfold; ;");

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

  auto legend_zdR = new TLegend(0.5, 0.5, 0.9, 0.85);
  legend_zdR->SetBorderSize(0);
  legend_zdR->SetFillStyle(0);
  legend_zdR->SetFillColor(3);

  for (int sl = 0; sl < slice_size; sl++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptzdR_sys("stack_ptzdR_sys%d", "");

    for (int i = 0; i < vec_sys_ptzdR.size(); i++)
    {
      SetHistErrorZero(vec_sys_ptzdR[i]);
      TH1D *h1_ptzdR_sys = (TH1D *)vec_sys_ptzdR[i]->ProjectionY(Form("h1_ptzdR_sys%d%d%d", n_slice_z[sl], i, sl), n_slice_z[sl], n_slice_z[sl]);
      TH1D *h1_ptzdR_sys_sym = (TH1D *)h1_ptzdR_sys->Clone(Form("h1_ptzdR_sys_sym%d%d%d", n_slice_z[sl], i, sl));
      h1_ptzdR_sys_sym->Scale(-1);

      if (i == vec_sys_ptzdR.size() - 1)
      {
        h1_ptzdR_sys->SetTitle("; ln(1/z);Relative Uncertainty");
        h1_ptzdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_ptzdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->SetFillColorAlpha(16, 0.3);
        h1_ptzdR_sys->SetLineColorAlpha(16, 0.3);
        h1_ptzdR_sys->Draw("HIST SAME");

        h1_ptzdR_sys_sym->SetTitle("; ln(1/z);Relative Uncertainty");
        h1_ptzdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptzdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_ptzdR_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_ptzdR_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = i + 22;
        if (i + 1 == 10)
          color = 15;

        h1_ptzdR_sys->SetTitle("; ln(1/z);Relative Uncertainty");
        h1_ptzdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys->GetXaxis()->SetTitleOffset(1.);

        h1_ptzdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->SetMarkerStyle(vec_markers[i]);
        h1_ptzdR_sys->SetMarkerColor(color);
        h1_ptzdR_sys->SetLineColor(color);
        h1_ptzdR_sys->Draw("P SAME");

        h1_ptzdR_sys_sym->SetTitle("; ln(1/z);Relative Uncertainty");
        h1_ptzdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptzdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->SetMarkerStyle(vec_markers[i]);
        h1_ptzdR_sys_sym->SetMarkerColor(color);
        h1_ptzdR_sys_sym->SetLineColor(color);
        h1_ptzdR_sys_sym->Draw("P SAME");
      }
      if (sl == 0)
        legend_zdR->AddEntry(h1_ptzdR_sys, vec_string[i]);
      h1_ptzdR_sys->SetMaximum(0.50);
      h1_ptzdR_sys->SetMinimum(-0.30);
    }
    legend_zdR->Draw("SAME");

    //  Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);
    double top = 0.85;
    double step = 0.06;
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - step, Form("p_{T,jet} > 20 GeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));
    Tl.DrawLatex(0.2, top - 3 * step, Form("%.2f<ln(R/#DeltaR)<%.2f", h2_ptzdR_sys_total->GetXaxis()->GetBinLowEdge(n_slice_z[sl]), h2_ptzdR_sys_total->GetXaxis()->GetBinLowEdge(n_slice_z[sl] + 1)));

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

  for (int sl = 0; sl < slice_size; sl++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);

    THStack stack_ptzdR_sys("stack_ptzdR_sys%d", "");

    for (int i = 0; i < vec_sys_ptzdR.size(); i++)
    {
      SetHistErrorZero(vec_sys_ptzdR[i]);
      TH1D *h1_ptzdR_sys = (TH1D *)vec_sys_ptzdR[i]->ProjectionX(Form("h1_ptzdRx_sys%d%d%d", n_slice_z[sl], i, sl), n_slice_z[sl], n_slice_z[sl]);
      TH1D *h1_ptzdR_sys_sym = (TH1D *)h1_ptzdR_sys->Clone(Form("h1_ptzdRx_sys_sym%d%d%d", n_slice_z[sl], i, sl));
      h1_ptzdR_sys_sym->Scale(-1);

      if (i == vec_sys_ptzdR.size() - 1)
      {
        h1_ptzdR_sys->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptzdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys->GetXaxis()->SetTitleOffset(1.3);

        h1_ptzdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->SetFillColorAlpha(16, 0.3);
        h1_ptzdR_sys->SetLineColorAlpha(16, 0.3);
        h1_ptzdR_sys->Draw("HIST SAME");

        h1_ptzdR_sys_sym->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptzdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptzdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->SetFillColorAlpha(16, 0.3);
        h1_ptzdR_sys_sym->SetLineColorAlpha(kBlack, 0.3);
        h1_ptzdR_sys_sym->Draw("HIST SAME");
      }
      else
      {
        int color = i + 22;
        if (i + 1 == 10)
          color = 15;

        h1_ptzdR_sys->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptzdR_sys->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys->GetXaxis()->SetTitleOffset(1.);

        h1_ptzdR_sys->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys->SetMarkerStyle(vec_markers[i]);
        h1_ptzdR_sys->SetMarkerColor(color);
        h1_ptzdR_sys->SetLineColor(color);
        h1_ptzdR_sys->Draw("P SAME");

        h1_ptzdR_sys_sym->SetTitle("; ln(R/#Delta R);Relative Uncertainty");
        h1_ptzdR_sys_sym->GetYaxis()->SetTitleOffset(1.);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleOffset(1.3);

        h1_ptzdR_sys_sym->GetYaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->GetXaxis()->SetTitleSize(0.05);
        h1_ptzdR_sys_sym->SetMarkerStyle(vec_markers[i]);
        h1_ptzdR_sys_sym->SetMarkerColor(color);
        h1_ptzdR_sys_sym->SetLineColor(color);
        h1_ptzdR_sys_sym->Draw("P SAME");
      }
      // if (sl == 0)
      //   legend_ktdR->AddEntry(h1_ptzdR_sys, vec_string[i]);
      h1_ptzdR_sys->SetMaximum(0.50);
      h1_ptzdR_sys->SetMinimum(-0.30);
    }
    legend_ktdR->Draw("SAME");

    //  Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);
    double top = 0.85;
    double step = 0.06;
    Tl.DrawLatex(0.2, top, Form("pp #sqrt{s} = 13 TeV"));
    Tl.DrawLatex(0.2, top - step, Form("p_{T,jet} > 20 GeV"));
    Tl.DrawLatex(0.2, top - 2 * step, Form("2.5 < #eta_{jet} < 4"));
    Tl.DrawLatex(0.2, top - 3 * step, Form("%.2f<ln(1/z)<%.2f", h2_ptzdR_sys_total->GetYaxis()->GetBinLowEdge(n_slice_z[sl]), h2_ptzdR_sys_total->GetYaxis()->GetBinLowEdge(n_slice_z[sl] + 1)));

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

  //
  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }
  //
  h2_ptktdR_sys_total->Write();
  h2_ptzdR_sys_total->Write();
  h2_ptthetaErad_sys_total->Write();
  file_save->Write();
  file_save->Close();
}

