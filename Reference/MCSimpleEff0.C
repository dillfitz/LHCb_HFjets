

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "../LundGen.hh"
using namespace fastjet;
using namespace std;

void MCSimpleEff(int NumEvts = 10000, int dataset = 1510,
                 bool chargedJetCut_user = false, double minimum_dR = 0.1)
{

  bool MCflag = true;
  followHardest = false;
  truthLevel = true;
  chargedJetCut = chargedJetCut_user;
  if (truthLevel)
  {
    ghostCut = false;
  }

  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;

  if (flavor == 5)
  {
    mass_num = 4.2;
  }
  else if (flavor == 4)
  {
    mass_num = 1.25;
  }
  else if (flavor == 1)
  {
    mass_num = 0.001;

    followHardest = true;
  }

  //
  //  Naming Convention:
  //  {$1}{$2}{$3}{$4}{$5}
  //  $1: Year: 2016 = 6, 2017 = 7, 2018 = 8, All = 9
  //  $2: jets or dijets: TaggedDijets = 1, else = 2
  //  $3: flavor: b = 5, c = 4, udsg = 1
  //  $4: pT: pt15pt20 = 0, pt20pt50 = 1, pt50 = 2, else = 3
  //  $5: Magnet: MD = 0, MU = 1, Both = 9

  TString str_Mag = "";
  TString str_pT = "";
  TString str_level = "";
  TString str_followHard = "";
  TString str_flavor = "";
  TString str_ghost = "";

  TString str_charged = "";

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

  // if(ptRange == 0) str_pT = "pt15pt20";
  // else if(ptRange == 1) str_pT = "pt20pt50";
  // else if(ptRange == 2) str_pT = "pt50";

  if (truthLevel)
    str_level = "truth";
  else
    str_level = "reco";

  if (flavor == 1)
    str_followHard = "_hard";
  else
  {
    if (followHardest)
      str_followHard = "_hard";
    else
      str_followHard = "_HF";
  }

  if (ghostCut)
    str_ghost = Form("_ghost_%.1f", ghostProb);

  if (chargedJetCut)
    str_charged = "_charge";
  // TString str_trees[5];
  // str_trees[0] = "TaggedDijets/DecayTree";
  // str_trees[1] = "D0KPiJet/DecayTree";
  // str_trees[2] = "B0KPiJet/DecayTree";
  // str_trees[3] = "Jets/DecayTree";
  TString str_tree;

  TString extension;
  extension = TString("efficiency_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  TString dir_deadcone("$LUND/Bjets/");
  TString extension_read;
  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
  TTree *LundTree = (TTree *)fread.Get("LundTree");
  if (NumEvts > LundTree->GetEntries())
    NumEvts = LundTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = LundTree->GetEntries();
  cout << LundTree->GetEntries() << endl;

  TFile f(dir_deadcone + "hists/" + extension + ".root", "RECREATE");

  // for(int i = 0; i < ktbinsize+1; i++){
  //   kt_binedges[i] = kT_min + i*(kT_max - kT_min)/ktbinsize;
  // }
  // for(int i = 0; i < zbinsize+1; i++){
  //   z_binedges[i] = z_min + i*(z_max - z_min)/zbinsize;
  // }
  // for(int i = 0; i < thetabinsize+1; i++){
  //   theta_binedges[i] = R_min + i*(R_max - R_min)/thetabinsize;
  // }
  // for(int i = 0; i < dRbinsize+1; i++){
  //   dR_binedges[i] = dR_min + i*(dR_max - dR_min)/dRbinsize;
  // }
  // for(int i = 0; i < Eradbinsize+1; i++){
  //   Erad_binedges[i] = Erad_min + i*(Erad_max - Erad_min)/Eradbinsize;
  // }

  // for(int i = 0; i < tr_ktbinsize+1; i++){
  //   tr_kt_binedges[i] = kT_min + i*(kT_max - kT_min)/tr_ktbinsize;
  // }
  // for(int i = 0; i < tr_zbinsize+1; i++){
  //   tr_z_binedges[i] = z_min + i*(z_max - z_min)/tr_zbinsize;
  // }
  // for(int i = 0; i < tr_thetabinsize+1; i++){
  //   tr_theta_binedges[i] = R_min + i*(R_max - R_min)/tr_thetabinsize;
  // }
  // for(int i = 0; i < tr_dRbinsize+1; i++){
  //   tr_dR_binedges[i] = dR_min + i*(dR_max - dR_min)/tr_dRbinsize;
  // }
  // for(int i = 0; i < tr_Eradbinsize+1; i++){
  //   tr_Erad_binedges[i] = Erad_min + i*(Erad_max - Erad_min)/tr_Eradbinsize;
  // }

  TH2D *h2_thetaErad = new TH2D("Theta_Erad", "", h2_erad_bins, h2_erad_low, h2_erad_high, 80, 1, 8);
  TH2D *h2_dRErad = new TH2D("dR_Erad", "", h2_erad_bins, h2_erad_low, h2_erad_high, 80, 0.5, 6);
  TH2D *h2_ktdR = new TH2D("kT_dR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);
  TH2D *h2_zdR = new TH2D("z_dR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);

  TH2D *h2_matchedlundplane = new TH2D("matchedLund_Plane", "Lund Jet Plane", 80, 2, 8, 80, -8, 4);
  TH2D *h2_matchedthetaErad = new TH2D("matchedTheta_Erad", "", h2_erad_bins, h2_erad_low, h2_erad_high, 80, 1, 8);
  TH2D *h2_matcheddRErad = new TH2D("matcheddR_Erad", "", h2_erad_bins, h2_erad_low, h2_erad_high, 80, 0.5, 6);
  TH2D *h2_matchedktdR = new TH2D("matchedkT_dR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);
  TH2D *h2_matchedzdR = new TH2D("matchedz_dR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);

  TH2D *h2_truthreco_theta = new TH2D("truthreco_theta", "", thetabinsize, theta_binedges, thetabinsize, theta_binedges);
  TH2D *h2_truthreco_kT = new TH2D("truthreco_kT", "", ktbinsize, kt_binedges, ktbinsize, kt_binedges);
  TH2D *h2_truthreco_Erad = new TH2D("truthreco_Erad", "", Eradbinsize, Erad_binedges, Eradbinsize, Erad_binedges);
  TH2D *h2_truthreco_dR = new TH2D("truthreco_dR", "", dRbinsize, dR_binedges, dRbinsize, dR_binedges);
  TH2D *h2_truthreco_z = new TH2D("truthreco_z", "", zbinsize, z_binedges, zbinsize, z_binedges);
  TH2D *h2_truthreco_jetpt = new TH2D("truthreco_jetpt", "", longptbinsize, longpt_binedges, longptbinsize, longpt_binedges);

  TH1D *h1_num_purity_theta = new TH1D("num_purity_theta", "", thetabinsize, theta_binedges);
  TH1D *h1_num_purity_Erad = new TH1D("num_purity_Erad", "", Eradbinsize, Erad_binedges);
  TH1D *h1_num_purity_kT = new TH1D("num_purity_kT", "", ktbinsize, kt_binedges);
  TH1D *h1_num_purity_dR = new TH1D("num_purity_dR", "", dRbinsize, dR_binedges);
  TH1D *h1_num_purity_z = new TH1D("num_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_num_efficiency_theta = new TH1D("num_efficiency_theta", "", thetabinsize, theta_binedges);
  TH1D *h1_num_efficiency_Erad = new TH1D("num_efficiency_Erad", "", Eradbinsize, Erad_binedges);
  TH1D *h1_num_efficiency_kT = new TH1D("num_efficiency_kT", "", ktbinsize, kt_binedges);
  TH1D *h1_num_efficiency_dR = new TH1D("num_efficiency_dR", "", dRbinsize, dR_binedges);
  TH1D *h1_num_efficiency_z = new TH1D("num_efficiency_z", "", zbinsize, z_binedges);

  TH1D *h1_denom_purity_theta = new TH1D("denom_purity_theta", "", thetabinsize, theta_binedges);
  TH1D *h1_denom_purity_Erad = new TH1D("denom_purity_Erad", "", Eradbinsize, Erad_binedges);
  TH1D *h1_denom_purity_kT = new TH1D("denom_purity_kT", "", ktbinsize, kt_binedges);
  TH1D *h1_denom_purity_dR = new TH1D("denom_purity_dR", "", dRbinsize, dR_binedges);
  TH1D *h1_denom_purity_z = new TH1D("denom_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_denom_efficiency_theta = new TH1D("denom_efficiency_theta", "", thetabinsize, theta_binedges);
  TH1D *h1_denom_efficiency_Erad = new TH1D("denom_efficiency_Erad", "", Eradbinsize, Erad_binedges);
  TH1D *h1_denom_efficiency_kT = new TH1D("denom_efficiency_kT", "", ktbinsize, kt_binedges);
  TH1D *h1_denom_efficiency_dR = new TH1D("denom_efficiency_dR", "", dRbinsize, dR_binedges);
  TH1D *h1_denom_efficiency_z = new TH1D("denom_efficiency_z", "", zbinsize, z_binedges);

  TH1D *h1_num_purity_jetpt = new TH1D("num_purity_jetpt", "", longptbinsize, longpt_binedges);
  TH1D *h1_denom_purity_jetpt = new TH1D("denom_purity_jetpt", "", longptbinsize, longpt_binedges);
  TH1D *h1_num_purity_eta = new TH1D("num_purity_eta", "", etabinsize, eta_binedges);
  TH1D *h1_denom_purity_eta = new TH1D("denom_purity_eta", "", etabinsize, eta_binedges);

  // TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
  // TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize_truth, pt_binedges_truth);
  // TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);

  TH2D *h2_num_purity_ktdR = new TH2D("num_purity_ktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);
  TH2D *h2_denom_purity_ktdR = new TH2D("denom_purity_ktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);

  TH2D *h2_num_purity_zdR = new TH2D("num_purity_zdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);
  TH2D *h2_denom_purity_zdR = new TH2D("denom_purity_zdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);

  TH2D *h2_num_purity_thetaErad = new TH2D("num_purity_thetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges);
  TH2D *h2_denom_purity_thetaErad = new TH2D("denom_purity_thetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges);

  TH2D *h2_num_efficiency_ktdR = new TH2D("num_efficiency_ktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);
  TH2D *h2_denom_efficiency_ktdR = new TH2D("denom_efficiency_ktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);

  TH2D *h2_num_efficiency_zdR = new TH2D("num_efficiency_zdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);
  TH2D *h2_denom_efficiency_zdR = new TH2D("denom_efficiency_zdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);

  TH2D *h2_num_efficiency_thetaErad = new TH2D("num_efficiency_thetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges);
  TH2D *h2_denom_efficiency_thetaErad = new TH2D("denom_efficiency_thetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges);

  RooUnfoldResponse *response_theta = new RooUnfoldResponse(h1_denom_purity_theta, h1_denom_efficiency_theta, "response_theta");

  RooUnfoldResponse *response_ktdR = new RooUnfoldResponse(h2_ktdR, h2_matchedktdR, "response_ktdR");
  RooUnfoldResponse *response_zdR = new RooUnfoldResponse(h2_zdR, h2_matchedzdR, "response_zdR");
  RooUnfoldResponse *response_dR = new RooUnfoldResponse(h1_denom_purity_dR, h1_denom_efficiency_dR, "response_dR");
  RooUnfoldResponse *response_kt = new RooUnfoldResponse(h1_denom_purity_kT, h1_denom_efficiency_kT, "response_kT");
  RooUnfoldResponse *response_Erad = new RooUnfoldResponse(h1_denom_purity_Erad, h1_denom_efficiency_Erad, "response_Erad");

  // RooUnfoldResponse * response_ktdR_nocorr = new RooUnfoldResponse(h2_ktdR, h2_matchedktdR, "response_ktdR_nocorr");
  // RooUnfoldResponse * response_zdR_nocorr = new RooUnfoldResponse(h2_zdR, h2_matchedzdR, "response_zdR_nocorr");
  // RooUnfoldResponse * response_dR_nocorr = new RooUnfoldResponse(dRbinsize, dR_binedges, dRbinsize, dR_binedges, "response_dR_nocorr");
  // RooUnfoldResponse * response_kt_nocorr = new RooUnfoldResponse(ktbinsize, kt_binedges, ktbinsize, kt_binedges, "response_kt_nocorr");

  TH1D *h1_num_efficiency_jetpt = new TH1D("num_efficiency_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_denom_efficiency_jetpt = new TH1D("denom_efficiency_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_num_efficiency_HFpt = new TH1D("num_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_denom_efficiency_HFpt = new TH1D("denom_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_denom_efficiency_HFpt15 = new TH1D("denom_efficiency_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_efficiency_HFeta = new TH1D("num_efficiency_HFeta", "", etabinsize, eta_binedges);
  TH1D *h1_denom_efficiency_HFeta = new TH1D("denom_efficiency_HFeta", "", etabinsize, eta_binedges);
  TH1D *h1_num_efficiency_jeteta = new TH1D("num_efficiency_eta", "", etabinsize, eta_binedges);
  TH1D *h1_denom_efficiency_jeteta = new TH1D("denom_efficiency_eta", "", etabinsize, eta_binedges);

  TH2D *h2_num_efficiency_jetpteta = new TH2D("num_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_denom_efficiency_jetpteta = new TH2D("denom_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);

  TH2D *h2_num_efficiency_HFpteta = new TH2D("num_efficiency_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
  TH2D *h2_denom_efficiency_HFpteta = new TH2D("denom_efficiency_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);

  TH2D *h2_denom_efficiency_HFptjetpt = new TH2D("denom_efficiency_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);

  TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);

  RooUnfoldResponse *response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, "response_jetpt");

  TH3D *h3_ptktdR = new TH3D("ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_matchedptktdR = new TH3D("matchedptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptktdR = new TH3D("num_efficiency_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_efficiency_ptktdR = new TH3D("denom_efficiency_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptktdR = new TH3D("efficiency_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptktdR = new TH3D("num_purity_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptktdR = new TH3D("denom_purity_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptktdR = new TH3D("purity_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptktdR = new RooUnfoldResponse(h3_ptktdR, h3_matchedptktdR, "response_ptktdR");

  TH3D *h3_ptzdR = new TH3D("ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_matchedptzdR = new TH3D("matchedptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptzdR = new TH3D("num_efficiency_ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_efficiency_ptzdR = new TH3D("denom_efficiency_ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptzdR = new TH3D("efficiency_ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptzdR = new TH3D("num_purity_ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptzdR = new TH3D("denom_purity_ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptzdR = new TH3D("purity_ptzdR", "", dRbinsize, dR_binedges, ktbinsize, z_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptzdR = new RooUnfoldResponse(h3_ptzdR, h3_matchedptzdR, "response_ptzdR");

  TH3D *h3_ptthetaErad = new TH3D("ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_matchedptthetaErad = new TH3D("matchedptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptthetaErad = new TH3D("num_efficiency_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_efficiency_ptthetaErad = new TH3D("denom_efficiency_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptthetaErad = new TH3D("efficiency_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptthetaErad = new TH3D("num_purity_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptthetaErad = new TH3D("denom_purity_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptthetaErad = new TH3D("purity_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptthetaErad = new RooUnfoldResponse(h3_ptthetaErad, h3_matchedptthetaErad, "response_ptthetaErad");

  TH2D *h2_ptkt = new TH2D("ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_matchedptkt = new TH2D("matchedptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptkt = new TH2D("num_efficiency_ptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_efficiency_ptkt = new TH2D("denom_efficiency_ptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptkt = new TH2D("efficiency_ptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptkt = new TH2D("num_purity_ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptkt = new TH2D("denom_purity_ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptkt = new TH2D("purity_ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptkt = new RooUnfoldResponse(h2_ptkt, h2_matchedptkt, "response_ptkt");

  THStack *stack_theta_resolution = new THStack("stack_theta_resolution", "");
  vector<TH1D *> h1_theta_resolution_vec;
  int MaxEmissions = 20;
  for (int i = 0; i < MaxEmissions; i++)
  {
    TH1D *h1res = new TH1D(Form("theta_resolution%d", i), "", 80, -5e-2, 5e-2);
    h1_theta_resolution_vec.push_back(h1res);
    stack_theta_resolution->Add(h1_theta_resolution_vec[i]);
  }

  THStack *stack_dR_resolution = new THStack("stack_dR_resolution", "");
  vector<TH1D *> h1_dR_resolution_vec;
  for (int i = 0; i < MaxEmissions; i++)
  {
    TH1D *h1res = new TH1D(Form("dR_resolution%d", i), "", 80, -5e-2, 5e-2);
    h1_dR_resolution_vec.push_back(h1res);
    stack_dR_resolution->Add(h1_dR_resolution_vec[i]);
  }

  // TH1D* h1_dR_resolution = new TH1D("dR_resolution", "", 40, 0, .3);
  // THStack *stack_dR_resolution = new THStack("stack_dR_resolution", "");
  // vector<TH1D*> h1_dR_resolution_vec;
  // for(int i = 0; i < 15; i++){
  //   TH1D* h1res = new TH1D(Form("dR_resolution%d", i), "", 40, 0, .3);
  //   h1_dR_resolution_vec.push_back(h1res);
  //   stack_dR_resolution->Add(h1_dR_resolution_vec[i]);
  // }
  // TH1D* h1_dR_neutral_resolution = new TH1D("dR_neutral_resolution", "", 40, 0, .3);
  // TH1D* h1_dR_track_resolution = new TH1D("dR_track_resolution", "", 40, 0, .3);

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //
  unsigned long long last_eventNum = 0;
  double last_jetpT = 0.;
  int event_counter = 0;

  vector<double> *thetas = 0;
  vector<double> *meas_thetas = 0;
  vector<double> *dRs(0), *meas_dRs(0);
  vector<double> *ktthetas(0), *meas_ktthetas(0);
  vector<double> *Erads(0), *meas_Erads(0);
  vector<double> *kts = 0;
  vector<double> *meas_kts = 0;
  vector<double> *raps(0), *meas_raps(0);
  vector<double> *phis(0), *meas_phis(0);
  vector<double> *zs(0), *meas_zs(0);

  double jet_pt, jet_eta, meas_jet_pt, meas_jet_eta;
  double jet_px, jet_py, jet_pz, jet_e;
  double HF_px, HF_py, HF_pz, HF_e;
  double HF_pt;
  double mup_px, mup_py, mup_pz, mup_e;
  double mum_px, mum_py, mum_pz, mum_e;

  double meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e;
  double meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e;
  double meas_mup_px, meas_mup_py, meas_mup_pz, meas_mup_e;
  double meas_mum_px, meas_mum_py, meas_mum_pz, meas_mum_e;

  int n_splits, ndtrs, NumHFHads;
  int meas_n_splits, meas_ndtrs;
  int eventNumber;

  bool hasRecoHF;

  LundTree->SetBranchAddress("thetas", &thetas);
  LundTree->SetBranchAddress("ktthetas", &ktthetas);
  LundTree->SetBranchAddress("Erads", &Erads);
  LundTree->SetBranchAddress("dRs", &dRs);
  LundTree->SetBranchAddress("kts", &kts);
  LundTree->SetBranchAddress("zs", &zs);
  LundTree->SetBranchAddress("raps", &raps);
  LundTree->SetBranchAddress("phis", &phis);

  LundTree->SetBranchAddress("jet_pt", &jet_pt);
  LundTree->SetBranchAddress("jet_eta", &jet_eta);

  LundTree->SetBranchAddress("jet_px", &jet_px);
  LundTree->SetBranchAddress("jet_py", &jet_py);
  LundTree->SetBranchAddress("jet_pz", &jet_pz);
  LundTree->SetBranchAddress("jet_e", &jet_e);

  LundTree->SetBranchAddress("mum_px", &mum_px);
  LundTree->SetBranchAddress("mum_py", &mum_py);
  LundTree->SetBranchAddress("mum_pz", &mum_pz);
  LundTree->SetBranchAddress("mum_e", &mum_e);

  LundTree->SetBranchAddress("mup_px", &mup_px);
  LundTree->SetBranchAddress("mup_py", &mup_py);
  LundTree->SetBranchAddress("mup_pz", &mup_pz);
  LundTree->SetBranchAddress("mup_e", &mup_e);

  LundTree->SetBranchAddress("meas_thetas", &meas_thetas);
  LundTree->SetBranchAddress("meas_ktthetas", &meas_ktthetas);
  LundTree->SetBranchAddress("meas_Erads", &meas_Erads);
  LundTree->SetBranchAddress("meas_dRs", &meas_dRs);
  LundTree->SetBranchAddress("meas_kts", &meas_kts);
  LundTree->SetBranchAddress("meas_zs", &meas_zs);
  LundTree->SetBranchAddress("meas_raps", &meas_raps);
  LundTree->SetBranchAddress("meas_phis", &meas_phis);

  LundTree->SetBranchAddress("meas_jet_pt", &meas_jet_pt);
  LundTree->SetBranchAddress("meas_jet_eta", &meas_jet_eta);

  LundTree->SetBranchAddress("meas_jet_px", &meas_jet_px);
  LundTree->SetBranchAddress("meas_jet_py", &meas_jet_py);
  LundTree->SetBranchAddress("meas_jet_pz", &meas_jet_pz);
  LundTree->SetBranchAddress("meas_jet_e", &meas_jet_e);

  LundTree->SetBranchAddress("meas_HF_px", &meas_HF_px);
  LundTree->SetBranchAddress("meas_HF_py", &meas_HF_py);
  LundTree->SetBranchAddress("meas_HF_pz", &meas_HF_pz);
  LundTree->SetBranchAddress("meas_HF_e", &meas_HF_e);

  LundTree->SetBranchAddress("ndtrs", &ndtrs);
  LundTree->SetBranchAddress("NumHFHads", &NumHFHads);
  LundTree->SetBranchAddress("hasRecoHF", &hasRecoHF);

  LundTree->SetBranchAddress("HF_px", &HF_px);
  LundTree->SetBranchAddress("HF_py", &HF_py);
  LundTree->SetBranchAddress("HF_pz", &HF_pz);
  LundTree->SetBranchAddress("HF_e", &HF_e);
  LundTree->SetBranchAddress("HF_pt", &HF_pt);

  LundTree->SetBranchAddress("eventNumber", &eventNumber);

  int eventNum;
  int NumJets_zdR = 0;
  int NumJets_ktdR = 0;
  int NumBjets = 0;
  int NumRecoBjets = 0;

  cout << "Requested # of events" << NumEvts << endl;
  for (int ev = 0; ev < NumEvts; ev++)
  {
    LundTree->GetEntry(ev);

    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;
    TLorentzVector HFmeson(HF_px, HF_py, HF_pz, HF_e);
    TLorentzVector meas_HFmeson(meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e);
    TLorentzVector mup(mup_px, mup_py, mup_pz, mup_e);
    TLorentzVector mum(mum_px, mum_py, mum_pz, mum_e);

    // if(NumHFHads > 1) continue;

    if (hasRecoHF && meas_jet_pt > 15. && meas_jet_eta > etaMin && meas_jet_eta < etaMax)
    {
      response_jetpt->Fill(meas_jet_pt, jet_pt);
    }

    // if (jet_pt < ptMin)
    //   continue;
    // if (jet_pt > ptMax)
    //   continue;
    // if (jet_eta < etaMin || jet_eta > etaMax)
    //   continue;
    NumBjets++;
    if(jet_pt > 15. && jet_pt < 20. && jet_eta > etaMin & jet_eta < etaMax){
      h1_denom_efficiency_HFpt15->Fill(HFmeson.Pt());
    }
    if(jet_pt > 15. && jet_eta > etaMin & jet_eta < etaMax){
      h2_denom_efficiency_HFptjetpt->Fill(HFmeson.Pt(), jet_pt);
    }
    if(jet_pt > 15. && jet_eta > etaMin & jet_eta < etaMax){
      h1_denom_efficiency_jetpt->Fill(jet_pt);
    }
    if(jet_pt > 15.){
      h2_denom_efficiency_jetpteta->Fill(jet_pt, jet_eta);
    }
    if(jet_pt > ptMin && jet_pt < ptMax && jet_eta > etaMin & jet_eta < etaMax){
      h1_denom_efficiency_HFpt->Fill(HF_pt);
      h1_denom_efficiency_HFeta->Fill(HFmeson.Eta());
      h1_denom_efficiency_jeteta->Fill(jet_eta);
      h2_denom_efficiency_HFpteta->Fill(HFmeson.Pt(), HFmeson.Eta());
    }
    if(jet_pt > ptMin && jet_pt < ptMax && jet_eta > etaMin & jet_eta < etaMax && meas_jet_pt > 15. && hasRecoHF){
      h1_num_efficiency_jetpt->Fill(jet_pt);
      h1_num_efficiency_HFpt->Fill(HF_pt);
      h1_num_efficiency_HFeta->Fill(HFmeson.Eta());
      h1_num_efficiency_jeteta->Fill(jet_eta);
      h2_num_efficiency_jetpteta->Fill(jet_pt, jet_eta);
      h2_num_efficiency_HFpteta->Fill(HFmeson.Pt(), HFmeson.Eta());
    }

    if (meas_jet_pt > 15.)
    {
      h1_num_purity_jetpt->Fill(jet_pt);
      h1_num_purity_eta->Fill(jet_eta);
      // cout<<meas_jet_eta<<endl;
    }

    if(jet_pt < 15. || jet_eta < etaMin || jet_eta > etaMax) continue;
    if(meas_jet_pt < 15. || meas_jet_eta < etaMin || meas_jet_eta > etaMax || !hasRecoHF) continue;
    // if(meas_kts->size() < 1) continue;


    h2_truthreco_jetpt->Fill(meas_jet_pt, jet_pt);

    int match_loc = -99;
    int rev_match_loc = -99;

    vector<double> bans, matchedbans;
    vector<double> temp, temp_tr;
    for (int i = 0; i < kts->size(); i++)
    {
      match_loc = -99;
      double logkt = log(kts->at(i));
      double logdR = log(jetradius / dRs->at(i));
      double logz = log(1. / zs->at(i));
      double logtheta = log(1. / thetas->at(i));
      // double kttheta = ktthetas->at(i);
      double erad = Erads->at(i);
      double rap = raps->at(i);
      double phi = phis->at(i);
      double dR_final = -99;
      // if (logkt < -3.0)
      //   continue;

      bool found_match = false;
      double min_dr = minimum_dR;
      for (int j = 0; j < meas_kts->size(); j++)
      {
        double meas_rap = meas_raps->at(j);
        double meas_phi = meas_phis->at(j);

        bool banned = false;
        for (int k = 0; k < matchedbans.size(); k++)
        {
          if (j == matchedbans[k])
            banned = true;
        }
        if (banned)
          continue;
        double drap = rap - meas_rap;
        double dphi = checkphi(checkphi(phi) - checkphi(meas_phi));
        double delta_R = sqrt(drap * drap + dphi * dphi);
        // if(delta_R > jetradius) cout<<delta_R<<endl;
        // cout<<"contrib = "<<delta_R<<endl;
        // cout<<"contrib = "<<declusts[i].harder().eta()<<","<<declusts[i].harder().phi()<<endl;
        // cout<<"contrib = "<<matcheddeclusts[j].harder().eta()<<","<<matcheddeclusts[j].harder().phi()<<endl;

        if (delta_R < min_dr)
        {
          // found_match = true;
          min_dr = delta_R;
          match_loc = j;
          dR_final = delta_R;
        }
      }

      min_dr = minimum_dR;
      temp.push_back(match_loc);
      if (match_loc > -1)
        matchedbans.push_back(match_loc);
    }

    for (int i = 0; i < meas_kts->size(); i++)
    {
      match_loc = -99;
      double logkt = log(meas_kts->at(i));
      double logdR = log(jetradius / meas_dRs->at(i));
      double logz = log(1. / meas_zs->at(i));
      double logtheta = log(1. / meas_thetas->at(i));
      // double kttheta = ktthetas->at(i);
      double erad = meas_Erads->at(i);
      double rap = meas_raps->at(i);
      double phi = meas_phis->at(i);
      double dR_final = -99;
      // cout << logkt << ",";
      // if (logkt < -3.0)
      //   continue;

      bool found_match = false;
      double min_dr = minimum_dR;
      for (int j = 0; j < kts->size(); j++)
      {
        double tr_rap = raps->at(j);
        double tr_phi = phis->at(j);

        bool banned = false;
        for (int k = 0; k < bans.size(); k++)
        {
          if (j == bans[k])
            banned = true;
        }
        if (banned)
          continue;
        double drap = rap - tr_rap;
        double dphi = checkphi(checkphi(phi) - checkphi(tr_phi));
        double delta_R = sqrt(drap * drap + dphi * dphi);
        // if(delta_R > jetradius) cout<<delta_R<<endl;
        // cout<<"contrib = "<<delta_R<<endl;
        // cout<<"contrib = "<<declusts[i].harder().eta()<<","<<declusts[i].harder().phi()<<endl;
        // cout<<"contrib = "<<matcheddeclusts[j].harder().eta()<<","<<matcheddeclusts[j].harder().phi()<<endl;

        if (delta_R < min_dr)
        {
          // found_match = true;
          min_dr = delta_R;
          match_loc = j;
          dR_final = delta_R;
        }
      }

      min_dr = minimum_dR;
      temp_tr.push_back(match_loc);
      if (match_loc > -1)
        bans.push_back(match_loc);
    }

    bans.clear();
    matchedbans.clear();
    // cout<<endl<<temp.size()<<", "<<temp_tr.size()<<endl;

    // cout<<endl<<"temps"<<endl;
    // for(int i = 0; i < temp.size(); i++){
    //   cout<<temp[i]<<",";
    // }
    // cout<<endl<<"temp_tr"<<endl;
    // for(int i = 0; i < temp_tr.size(); i++){
    //   cout<<temp_tr[i]<<",";
    // }

    for (int i = 0; i < temp.size(); i++)
    {
      if (temp[i] < 0)
        continue;
      // cout<<i<<", "<<temp[i]<<", "<<temp_tr[temp[i]]<<endl;
      if (temp_tr[temp[i]] == i)
      {
        bans.push_back(i);
        matchedbans.push_back(temp[i]);
      }
    }
    // cout<<endl<<"bans"<<endl;
    // for(int i = 0; i < bans.size(); i++){
    //   cout<<bans[i]<<",";
    // }
    // cout<<endl<<"matchbans"<<endl;
    // for(int i = 0; i < matchedbans.size(); i++){
    //   cout<<matchedbans[i]<<",";
    // }

    for (int i = 0; i < bans.size(); i++)
    {
      // cout<<bans[i]<<", ";
      // cout<<matchedbans[i]<<",";
      double logkt = log(kts->at(bans[i]));
      double logdR = log(jetradius / dRs->at(bans[i]));
      double logz = log(1. / zs->at(bans[i]));
      double logtheta = log(1. / thetas->at(bans[i]));
      double erad = Erads->at(bans[i]);
      double rap = raps->at(bans[i]);
      double phi = phis->at(bans[i]);
      double meas_logkt = log(meas_kts->at(matchedbans[i]));
      double meas_logdR = log(jetradius / meas_dRs->at(matchedbans[i]));
      double meas_logz = log(1. / meas_zs->at(matchedbans[i]));
      double meas_logtheta = log(1. / meas_thetas->at(matchedbans[i]));
      double meas_erad = meas_Erads->at(matchedbans[i]);
      // cout<<"quants defined"<<endl;
      // cout<<"Match: ("<<rev_match_loc<<","<<match_loc<<")"<<endl;
      // cout<<"E: ("<<logkt<<","<<meas_logkt<<")"<<endl;
      // matchedbans.push_back(match_loc);
      // bans.push_back(rev_match_loc);
      if (jet_pt > ptMin && jet_pt < ptMax)
      {
        response_zdR->Fill(meas_logdR, meas_logz, logdR, logz);
        response_ktdR->Fill(meas_logdR, meas_logkt, logdR, logkt);
        response_dR->Fill(meas_logdR, logdR);
        response_kt->Fill(meas_logkt, logkt);
        response_theta->Fill(meas_logtheta, logtheta);
        response_Erad->Fill(meas_erad, erad);
        //   response_ptHFktdR->Fill(meas_logdR, meas_logkt, meas_HF_pt, logdR, logkt, HF_pt);
        // response_ptHFzdR->Fill(logdR, logz, HF_pt, meas_logdR, meas_logz, tr_HF_pt);

        // response_zdR_nocorr->Fill(logdR, logz, tr_logdR, tr_logz);
        // response_ktdR_nocorr->Fill(logdR, logkt, tr_logdR, tr_logkt);
        // response_dR_nocorr->Fill(logdR, tr_logdR);
      }
      response_ptktdR->Fill(meas_logdR, meas_logkt, meas_jet_pt, logdR, logkt, jet_pt);
      response_ptzdR->Fill(meas_logdR, meas_logz, meas_jet_pt, logdR, logz, jet_pt);

      response_ptkt->Fill(meas_logkt, meas_jet_pt, logkt, jet_pt);

      // if(kttheta > LambdaQCD){
      response_ptthetaErad->Fill(meas_erad, meas_logtheta, meas_jet_pt, erad, logtheta, jet_pt);
      // }

      // response_ptHFktdR->Fill(logdR, logkt, HF_pt, tr_logdR, tr_logkt, tr_HF_pt);
      // response_ptHFzdR->Fill(logdR, logz, HF_pt, tr_logdR, tr_logz, tr_HF_pt);

      h2_truthreco_Erad->Fill(meas_erad, erad);
      h2_truthreco_theta->Fill(meas_logtheta, logtheta);
      h2_truthreco_dR->Fill(meas_logdR, logdR);
      h2_truthreco_kT->Fill(meas_logkt, logkt);
      h2_truthreco_z->Fill(meas_logz, logz);

      for (int jj = 0; jj < dRbinsize; jj++)
      {
        if (logdR > dR_binedges[jj] && logdR < dR_binedges[jj + 1])
        {
          h1_dR_resolution_vec[jj]->Fill(dRs->at(bans[i]) - meas_dRs->at(matchedbans[i]));
        }
      }
      for (int jj = 0; jj < thetabinsize; jj++)
      {
        if (logtheta > theta_binedges[jj] && logtheta < theta_binedges[jj + 1])
        {
          h1_theta_resolution_vec[jj]->Fill(thetas->at(bans[i]) - meas_thetas->at(matchedbans[i]));
        }
      }
      // for(int jj = 0; jj < Eradbinsize; jj++){
      //   if(tr_erad > Erad_binedges[jj] && tr_erad < Erad_binedges[jj+1]){
      //     h1_Erad_resolution_vec[jj]->Fill(Erads->at(rev_match_loc) - meas_Erads->at(match_loc));
      //   }
      // }
    }
    for (int i = 0; i < kts->size(); i++)
    {
      double logkt = log(kts->at(i));
      double logdR = log(jetradius / dRs->at(i));
      double logz = log(1. / zs->at(i));
      double logtheta = log(1. / thetas->at(i));
      double erad = Erads->at(i);
      double kttheta = ktthetas->at(i);
      if (jet_pt > ptMin && jet_pt < ptMax)
      {
        h1_denom_efficiency_theta->Fill(logtheta);
        h1_denom_efficiency_Erad->Fill(erad);
        h1_denom_efficiency_kT->Fill(logkt);
        h1_denom_efficiency_dR->Fill(logdR);
        h1_denom_efficiency_z->Fill(logz);
        h2_denom_efficiency_ktdR->Fill(logdR, logkt);
        h2_denom_efficiency_zdR->Fill(logdR, logz);
        h2_denom_efficiency_thetaErad->Fill(erad, logtheta);
      }
      h3_denom_efficiency_ptktdR->Fill(logdR, logkt, jet_pt);
      h3_denom_efficiency_ptzdR->Fill(logdR, logz, jet_pt);
      if (kttheta > LambdaQCD)
      {
        h3_denom_efficiency_ptthetaErad->Fill(erad, logtheta, jet_pt);
      }
      bool isMiss = true;
      for (int j = 0; j < bans.size(); j++)
      {
        if (i == bans[j])
        {
          isMiss = false;
        }
      }
      if (isMiss)
      {
        // if(jet_pt > ptMin && jet_pt < ptMax){
        // response_ktdR->Miss(logdR, logkt);
        // response_zdR->Miss(logdR, logz);
        // // response_dR->Miss(logdR);
        // // response_kt->Miss(logkt);
        // response_theta->Miss(logtheta);
        // }
        // response_ptktdR->Miss(logdR, logkt, jet_pt);
        // response_ptzdR->Miss(logdR, logz, jet_pt);
        // if(kttheta > LambdaQCD){
        // response_ptthetaErad->Miss(erad, logtheta, jet_pt);
        // }
      }
      else
      {
        if (jet_pt > ptMin && jet_pt < ptMax)
        {
          h1_num_efficiency_theta->Fill(logtheta);
          h1_num_efficiency_Erad->Fill(erad);
          h1_num_efficiency_kT->Fill(logkt);
          h1_num_efficiency_dR->Fill(logdR);
          h1_num_efficiency_z->Fill(logz);
          h2_num_efficiency_ktdR->Fill(logdR, logkt);
          h2_num_efficiency_zdR->Fill(logdR, logz);
          h2_num_efficiency_thetaErad->Fill(erad, logtheta);
        }

        h3_num_efficiency_ptktdR->Fill(logdR, logkt, jet_pt);
        h3_num_efficiency_ptzdR->Fill(logdR, logz, jet_pt);
        if (kttheta > LambdaQCD)
        {
          h3_num_efficiency_ptthetaErad->Fill(erad, logtheta, jet_pt);
        }
      }
    }
    for (int i = 0; i < meas_kts->size(); i++)
    {
      double logkt = log(meas_kts->at(i));
      double logdR = log(jetradius / meas_dRs->at(i));
      double logz = log(1. / meas_zs->at(i));
      double logtheta = log(1. / meas_thetas->at(i));
      double erad = meas_Erads->at(i);
      double kttheta = meas_ktthetas->at(i);
      if (meas_jet_pt > ptMin && meas_jet_pt < ptMax)
      {
        h1_denom_purity_theta->Fill(logtheta);
        h1_denom_purity_Erad->Fill(erad);
        h1_denom_purity_kT->Fill(logkt);
        h1_denom_purity_dR->Fill(logdR);
        h1_denom_purity_z->Fill(logz);
        h2_denom_purity_ktdR->Fill(logdR, logkt);
        h2_denom_purity_zdR->Fill(logdR, logz);
        h2_denom_purity_thetaErad->Fill(erad, logtheta);
      }
      h3_denom_purity_ptktdR->Fill(logdR, logkt, meas_jet_pt);
      h3_denom_purity_ptzdR->Fill(logdR, logz, meas_jet_pt);
      if (kttheta > LambdaQCD)
      {
        h3_denom_purity_ptthetaErad->Fill(erad, logtheta, meas_jet_pt);
      }
      bool isFake = true;
      for (int j = 0; j < matchedbans.size(); j++)
      {
        if (i == matchedbans[j])
        {
          isFake = false;
        }
      }
      if (isFake)
      {
        // if(meas_jet_pt > ptMin && meas_jet_pt < ptMax){
        // response_ktdR->Fake(logdR, logkt);
        // response_zdR->Fake(logdR, logz);
        // // response_dR->Fake(logdR);
        // // response_kt->Fake(logkt);
        // response_theta->Fake(logtheta);
        // }
        // response_ptktdR->Fake(logdR, logkt, meas_jet_pt);
        // response_ptzdR->Fake(logdR, logz, meas_jet_pt);
        // if(kttheta > LambdaQCD){
        //   response_ptthetaErad->Fake(erad, logtheta, meas_jet_pt);
        // }
      }
      else
      {
        if (meas_jet_pt > ptMin && meas_jet_pt < ptMax)
        {
          h1_num_purity_theta->Fill(logtheta);
          h1_num_purity_Erad->Fill(erad);
          h1_num_purity_kT->Fill(logkt);
          h1_num_purity_dR->Fill(logdR);
          h1_num_purity_z->Fill(logz);
          h2_num_purity_ktdR->Fill(logdR, logkt);
          h2_num_purity_zdR->Fill(logdR, logz);
          h2_num_purity_thetaErad->Fill(erad, logtheta);
        }

        h3_num_purity_ptktdR->Fill(logdR, logkt, meas_jet_pt);
        h3_num_purity_ptzdR->Fill(logdR, logz, meas_jet_pt);
        if (kttheta > LambdaQCD)
        {
          h3_num_purity_ptthetaErad->Fill(erad, logtheta, meas_jet_pt);
        }
      }
    }
    event_counter++;
  }

  // h2_ktdR->Scale(1./NumJets_ktdR);
  // h2_zdR->Scale(1./NumJets_zdR);

  // RooUnfoldResponse * response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, h2_truthreco_jetpt, "response_jetpt");
  TH2 *h2_response_jetpt = response_jetpt->Hresponse();
  TH2 *h2_response = response_ktdR->Hresponse();
  TH2 *h2_response_zdR = response_zdR->Hresponse();
  cout << response_theta->GetNbinsTruth() << endl;
  TH2 *h2_response_theta = response_theta->Hresponse();
  TH2 *h2_response_dR = response_dR->Hresponse();
  TH2 *h2_response_kt = response_kt->Hresponse();
  cout << h2_response_kt->Integral() << endl;
  cout << h2_response_theta->Integral() << endl;
  TH2 *h2_response_Erad = response_Erad->Hresponse();
  TH2 *h2_response_ptktdR = response_ptktdR->Hresponse();
  TH2 *h2_response_ptzdR = response_ptzdR->Hresponse();
  TH2 *h2_response_ptthetaErad = response_ptthetaErad->Hresponse();

  TH1 *h1_fakes_dR = response_dR->Hfakes();
  TH1 *h1_truth_dR = response_dR->Htruth();
  TH1 *h1_meas_dR = response_dR->Hmeasured();
  h2_response->SetName("h2_response");

  response_ptktdR->Write("response_ptktdR");
  response_ptzdR->Write("response_ptzdR");
  response_ptthetaErad->Write("response_ptthetaErad");

  response_jetpt->Write("response_jetpt");
  response_ktdR->Write("response_ktdR");
  response_zdR->Write("response_zdR");
  response_dR->Write("response_dR");
  response_kt->Write("response_kt");

  // response_ktdR_nocorr->Write("response_ktdR_nocorr");
  // response_zdR_nocorr->Write("response_zdR_nocorr");
  // response_dR_nocorr->Write("response_dR_nocorr");
  // response_kt_nocorr->Write("response_kt_nocorr");

  TEfficiency *h1_purity_Erad = new TEfficiency(*h1_num_purity_Erad, *h1_denom_purity_Erad);

  TH1D *h1_purity_theta = (TH1D *)h1_num_purity_theta->Clone("h1_purity_theta");
  h1_purity_theta->Divide(h1_num_purity_theta, h1_denom_purity_theta, 1, 1, "B");

  TH1D *h1_efficiency_theta = (TH1D *)h1_num_efficiency_theta->Clone("h1_efficiency_theta");
  h1_efficiency_theta->Divide(h1_num_efficiency_theta, h1_denom_efficiency_theta, 1, 1, "B");

  TH1D *h1_purity_kT = (TH1D *)h1_num_purity_kT->Clone("h1_purity_kT");
  h1_purity_kT->Divide(h1_num_purity_kT, h1_denom_purity_kT, 1, 1, "B");

  TH1D *h1_efficiency_kT = (TH1D *)h1_num_efficiency_kT->Clone("h1_efficiency_kT");
  h1_efficiency_kT->Divide(h1_num_efficiency_kT, h1_denom_efficiency_kT, 1, 1, "B");

  TH1D *h1_purity_z = (TH1D *)h1_num_purity_z->Clone("h1_purity_z");
  h1_purity_z->Divide(h1_num_purity_z, h1_denom_purity_z, 1, 1, "B");

  TH1D *h1_efficiency_z = (TH1D *)h1_num_efficiency_z->Clone("h1_efficiency_z");
  h1_efficiency_z->Divide(h1_num_efficiency_z, h1_denom_efficiency_z, 1, 1, "B");

  TH1D *h1_purity_dR = (TH1D *)h1_num_purity_dR->Clone("h1_purity_dR");
  h1_purity_dR->Divide(h1_num_purity_dR, h1_denom_purity_dR, 1, 1, "B");

  TH1D *h1_efficiency_dR = (TH1D *)h1_num_efficiency_dR->Clone("h1_efficiency_dR");
  h1_efficiency_dR->Divide(h1_num_efficiency_dR, h1_denom_efficiency_dR, 1, 1, "B");

  TEfficiency *h1_efficiency_Erad = new TEfficiency(*h1_num_efficiency_Erad, *h1_denom_efficiency_Erad);

  TH1D *h1_efficiency_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("h1_efficiency_jetpt");
  h1_efficiency_jetpt->Divide(h1_num_efficiency_jetpt, h1_denom_efficiency_jetpt, 1, 1, "B");

  TH1D *h1_efficiency_jeteta = (TH1D *)h1_num_efficiency_jeteta->Clone("h1_efficiency_jeteta");
  h1_efficiency_jeteta->Divide(h1_num_efficiency_jeteta, h1_denom_efficiency_jeteta, 1, 1, "B");

  TH1D *h1_efficiency_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("h1_efficiency_HFpt");
  h1_efficiency_HFpt->Divide(h1_num_efficiency_HFpt, h1_denom_efficiency_HFpt, 1, 1, "B");

  TH1D *h1_efficiency_HFeta = (TH1D *)h1_num_efficiency_HFeta->Clone("h1_efficiency_HFeta");
  h1_efficiency_HFeta->Divide(h1_num_efficiency_HFeta, h1_denom_efficiency_HFeta, 1, 1, "B");

  TH2D *h2_efficiency_jetpteta = (TH2D *)h2_num_efficiency_jetpteta->Clone("h2_efficiency_jetpteta");
  h2_efficiency_jetpteta->Divide(h2_num_efficiency_jetpteta, h2_denom_efficiency_jetpteta, 1, 1, "B");

  TH2D *h2_efficiency_HFpteta = (TH2D *)h2_num_efficiency_HFpteta->Clone("h2_efficiency_HFpteta");
  h2_efficiency_HFpteta->Divide(h2_num_efficiency_HFpteta, h2_denom_efficiency_HFpteta, 1, 1, "B");

  // TEfficiency * h1_efficiency_jetpt = new TEfficiency(*h1_num_efficiency_jetpt, *h1_denom_efficiency_jetpt);
  // TEfficiency * h1_efficiency_jeteta = new TEfficiency(*h1_num_efficiency_jeteta, *h1_denom_efficiency_jeteta);
  TEfficiency *h2_purity_ktdR = new TEfficiency(*h2_num_purity_ktdR, *h2_denom_purity_ktdR);
  TEfficiency *h2_purity_zdR = new TEfficiency(*h2_num_purity_zdR, *h2_denom_purity_zdR);
  TEfficiency *h2_purity_thetaErad = new TEfficiency(*h2_num_purity_thetaErad, *h2_denom_purity_thetaErad);
  TEfficiency *h2_efficiency_ktdR = new TEfficiency(*h2_num_efficiency_ktdR, *h2_denom_efficiency_ktdR);
  TEfficiency *h2_efficiency_zdR = new TEfficiency(*h2_num_efficiency_zdR, *h2_denom_efficiency_zdR);
  TEfficiency *h2_efficiency_thetaErad = new TEfficiency(*h2_num_efficiency_thetaErad, *h2_denom_efficiency_thetaErad);

  h3_efficiency_ptktdR->Divide(h3_num_efficiency_ptktdR, h3_denom_efficiency_ptktdR, 1, 1, "B");
  h3_purity_ptktdR->Divide(h3_num_purity_ptktdR, h3_denom_purity_ptktdR, 1, 1, "B");

  h3_efficiency_ptzdR->Divide(h3_num_efficiency_ptzdR, h3_denom_efficiency_ptzdR, 1, 1, "B");
  h3_purity_ptzdR->Divide(h3_num_purity_ptzdR, h3_denom_purity_ptzdR, 1, 1, "B");

  h3_efficiency_ptthetaErad->Divide(h3_num_efficiency_ptthetaErad, h3_denom_efficiency_ptthetaErad, 1, 1, "B");
  h3_purity_ptthetaErad->Divide(h3_num_purity_ptthetaErad, h3_denom_purity_ptthetaErad, 1, 1, "B");

  /////////////////////////////////
  // auto g = new TGraph();
  // for(int i = 1; i <= h1_efficiency_HFpt->GetNbinsX(); i++ ) g->SetPoint(i-1, h1_efficiency_HFpt->GetBinCenter(i), h1_efficiency_HFpt->GetBinContent(i));
  TSpline3 sp(h1_efficiency_HFpt);
  TF1 *f_eff1 = new TF1("f_eff1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
  TF1 *f_eff2 = new TF1("f_eff2", "[0]*tanh([1]*([3] - x))+[2]", 25, 100);
  f_eff1->SetParameters(0.2, 0.1, 0.2, 6.4);
  f_eff2->SetParameters(0.2, 0.1, 0.2, 100);
  f_eff2->SetParLimits(3, 80, 200);
  h1_efficiency_HFpt->Fit("f_eff1", "E", "SAME", 2, 25);
  h1_efficiency_HFpt->Fit("f_eff2", "E", "SAME", 25, 100);

  f_eff1->Write("f_eff1");
  f_eff2->Write("f_eff2");
  // TF1 *f_eff = new TF1(
  //     "f_eff", [=](double *x, double *p)
  //     { return (sp.Eval(x[0])); },
  //     sp.GetXmin(), sp.GetXmax(), 2);

  /////////////////////////////////

  h2_purity_ktdR->Write("purity_ktdR");
  h2_purity_zdR->Write("purity_zdR");
  h2_purity_thetaErad->Write("purity_thetaErad");
  h1_purity_dR->Write("purity_dR");
  h1_purity_kT->Write("purity_kt");
  h1_purity_Erad->Write("purity_Erad");
  h1_purity_z->Write("purity_z");
  h1_efficiency_jetpt->Write("efficiency_jetpt");
  h1_denom_efficiency_HFpt->Write("h1_denom_efficiency_HFpt");
  h1_denom_efficiency_HFpt15->Write("h1_denom_efficiency_HFpt15");
  h1_denom_efficiency_jetpt->Write("h1_denom_efficiency_jetpt");
  h2_denom_efficiency_HFptjetpt->Write("h2_denom_efficiency_HFptjetpt");
  h1_efficiency_HFpt->Write("efficiency_HFpt");
  h1_efficiency_HFeta->Write("efficiency_HFeta");
  h1_efficiency_jeteta->Write("efficiency_jeteta");

  h2_efficiency_jetpteta->Write("efficiency_jetpteta");
  h2_efficiency_HFpteta->Write("efficiency_HFpteta");

  h2_efficiency_ktdR->Write("efficiency_ktdR");
  h2_efficiency_zdR->Write("efficiency_zdR");
  h2_efficiency_thetaErad->Write("efficiency_thetaErad");
  h1_efficiency_dR->Write("efficiency_dR");
  h1_efficiency_z->Write("efficiency_z");
  h1_efficiency_theta->Write("efficiency_theta");
  h1_efficiency_kT->Write("efficiency_kt");
  h1_efficiency_Erad->Write("efficiency_Erad");

  h3_purity_ptktdR->Write("purity_ptktdR");
  h3_efficiency_ptktdR->Write("efficiency_ptktdR");

  h3_purity_ptzdR->Write("purity_ptzdR");
  h3_efficiency_ptzdR->Write("efficiency_ptzdR");

  h3_purity_ptthetaErad->Write("purity_ptthetaErad");
  h3_efficiency_ptthetaErad->Write("efficiency_ptthetaErad");

  cout << event_counter << " events processed" << endl;

  //
  int ican = -1, iframe = -1, itext = -1;
  TCanvas *ccan[1000];
  TH1F *frame[1000];
  TLatex *text[1000];
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
  Int_t lhcbFont = 132; // Old LHCb style: 62;
  // Line thickness
  Double_t lhcbWidth = 2.00; // Old LHCb style: 3.00;
  // Text size
  Double_t lhcbTSize = 0.06;

  // gROOT->SetStyle("Plain");
  gStyle->SetCanvasDefH(1414);
  gStyle->SetCanvasDefW(1000);
  gStyle->SetPadBottomMargin(0.08);
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.12);
  gStyle->SetTitleStyle(0);
  gStyle->SetStatStyle(0);
  // gStyle->SetLineWidth(3);
  gStyle->SetOptStat(0);
  //---- paint...
  char buf[100];
  char bufb[100];
  TString rootfile;
  TString plotfile;
  TString plotfilePDF;
  TString plotfileO;
  TString plotfileC;
  // TString OutputFileBase	= outbase+outinfo;
  rootfile = TString(dir_deadcone + "hists/") + extension + TString(".root");
  plotfile = TString(dir_deadcone + "plots/") + extension + TString(".ps");
  plotfilePDF = TString(dir_deadcone + "plots/") + extension + TString(".pdf");
  plotfileO = plotfilePDF + TString("(");
  plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

  // c1->SaveAs(Form("plots_misc/Misc_%s"+extension+".pdf", file_name.c_str()));
  // cout<<"...outbase   = "<<outbase.Data()<<endl;
  // cout<<"...rootfile  = "<<rootfile.Data()<<endl;
  // cout<<"...plotfile  = "<<plotfile.Data()<<endl;

  // //
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  h2_response->SetStats(0);
  gPad->SetLogz();
  h2_response->Draw("COLZ");
  // Tl.drawLatex(0.7, 0.8, "No cuts");
  ccan[ican]->cd(2);
  h2_response_zdR->SetStats(0);
  gPad->SetLogz();
  h2_response_zdR->Draw("COLZ");
  // Tl.drawLatex(0.7, 0.8, "No cuts");
  ccan[ican]->cd(3);
  h2_response_jetpt->SetStats(0);
  gPad->SetLogz();
  h2_response_jetpt->Draw("COLZ");

  ccan[ican]->cd(4);
  NormalizeHist(h1_jetpt);
  h1_jetpt->Draw("same");

  NormalizeHist(h1_jetpt_truth);
  h1_jetpt_truth->SetLineColor(kGreen);
  h1_jetpt_truth->Draw("same");

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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  // gPad->SetLogz();
  h2_truthreco_theta->SetStats(0);
  h2_truthreco_theta->SetXTitle("MCTrue ln(1/#theta)");
  h2_truthreco_theta->SetYTitle("MCReco ln(1/#theta)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_theta->Draw("COLZ");
  Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.drawLatex(0.7, 0.8, "No cuts");

  ccan[ican]->cd(2);
  // gPad->SetLogz();
  h2_truthreco_kT->SetStats(0);
  h2_truthreco_kT->SetXTitle("MCTrue ln(kT)");
  h2_truthreco_kT->SetYTitle("MCReco ln(kT)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_kT->Draw("COLZ");
  ccan[ican]->cd(3);
  // gPad->SetLogz();
  h2_truthreco_z->SetStats(0);
  h2_truthreco_z->SetXTitle("MCTrue ln(1/z)");
  h2_truthreco_z->SetYTitle("MCReco ln(1/z)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_z->Draw("COLZ");
  ccan[ican]->cd(4);
  // gPad->SetLogz();
  h2_truthreco_dR->SetStats(0);
  h2_truthreco_dR->SetXTitle("MCTrue ln(#Delta R)");
  h2_truthreco_dR->SetYTitle("MCReco ln(#Delta R)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_dR->Draw("COLZ");

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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  h1_purity_kT->SetMarkerColor(kRed);
  h1_purity_kT->SetMarkerStyle(20);
  h1_purity_kT->Draw("P E same");
  h1_purity_kT->SetTitle("; ln(kT); Purity or Efficiency");

  h1_efficiency_kT->SetMarkerColor(kBlue);
  h1_efficiency_kT->SetMarkerStyle(21);
  h1_efficiency_kT->Draw("P E same");

  h1_purity_kT->SetMinimum(0.);
  h1_purity_kT->SetMaximum(1.);

  // h1_efficiency_kT->SetTitle("; ln(R/#Delta R); efficiency");
  // h1_purity_Erad->SetXTitle("E_{radiator}");
  // h1_purity_Erad->SetYTitle("Counts");
  // gPad->Update();
  // auto graph1 = h1_purity_kT->GetPaintedGraph();
  // graph1->SetMinimum(0);
  // graph1->SetMaximum(1);
  // gPad->Update();

  auto legendeff = new TLegend(0.6, 0.2, 0.8, 0.4);
  legendeff->SetBorderSize(0);
  legendeff->SetFillStyle(0);
  legendeff->SetFillColor(3);
  legendeff->AddEntry(h1_efficiency_kT, "Efficiency");
  legendeff->AddEntry(h1_purity_kT, "Purity");
  legendeff->Draw("SAME");

  // h1_purity_Erad->SetXTitle("E_{radiator}");
  // h1_purity_Erad->SetYTitle("Counts");
  ccan[ican]->cd(2);
  h1_purity_dR->SetMarkerColor(kRed);
  h1_purity_dR->SetMarkerStyle(20);
  h1_purity_dR->Draw("P E same");
  h1_purity_dR->SetTitle("; ln(R/#DeltaR); Purity or Efficiency");

  h1_efficiency_dR->SetMarkerColor(kBlue);
  h1_efficiency_dR->SetMarkerStyle(21);
  h1_efficiency_dR->Draw("P E same");

  h1_purity_dR->SetMinimum(0.);
  h1_purity_dR->SetMaximum(1.);

  // h1_efficiency_theta->SetMinimum(0.0);
  ccan[ican]->cd(3);
  h1_purity_z->SetMarkerColor(kRed);
  h1_purity_z->SetMarkerStyle(20);
  h1_purity_z->Draw("P E same");
  h1_purity_z->SetTitle("; ln(1/z); Purity or Efficiency");

  h1_efficiency_z->SetMarkerColor(kBlue);
  h1_efficiency_z->SetMarkerStyle(21);
  h1_efficiency_z->Draw("P E same");

  h1_purity_z->SetMinimum(0.);
  h1_purity_z->SetMaximum(1.);
  // gPad->Update();
  // auto graph3 = h1_purity_z->GetPaintedGraph();
  // graph3->SetMinimum(0);
  // graph3->SetMaximum(1);
  // gPad->Update();
  ccan[ican]->cd(4);
  h1_purity_theta->SetMarkerColor(kRed);
  h1_purity_theta->SetMarkerStyle(20);
  h1_purity_theta->Draw("P E same");
  h1_purity_theta->SetTitle("; ln(1/#theta); Purity or Efficiency");

  h1_efficiency_theta->SetMarkerColor(kBlue);
  h1_efficiency_theta->SetMarkerStyle(21);
  h1_efficiency_theta->Draw("P E same");

  h1_purity_theta->SetMinimum(0.);
  h1_purity_theta->SetMaximum(1.);
  // h1_efficiency_dR->SetTitle("; ln(R/#Delta R); efficiency");
  // h1_purity_theta->SetXTitle("E_{radiator}");
  // h1_purity_theta->SetYTitle("Counts");
  // gPad->Update();
  // auto graphtheta3 = h1_purity_theta->GetPaintedGraph();
  // graphtheta3->SetMinimum(0);
  // graphtheta3->SetMaximum(1);
  // gPad->Update();
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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);

  h1_efficiency_jetpt->SetMarkerColor(kBlue);
  h1_efficiency_jetpt->SetMarkerStyle(21);
  h1_efficiency_jetpt->Draw("P E SAME");
  h1_efficiency_jetpt->SetTitle("; Jet pT; HF Jet Reco. Efficiency");
  h1_efficiency_jetpt->SetMinimum(0.);
  h1_efficiency_jetpt->SetMaximum(1.);
  // h1_efficiency_jetpt->SetXTitle("E_{radiator}");
  // h1_efficiency_jetpt->SetYTitle("Counts");
  // gPad->Update();
  // auto graphpt3 = h1_efficiency_jetpt->GetPaintedGraph();
  // graphpt3->SetMinimum(0);
  // graphpt3->SetMaximum(1);
  // gPad->Update();
  // h1_efficiency_jetpt->SetMinimum(0.0);
  ccan[ican]->cd(2);
  h1_efficiency_jeteta->SetMarkerColor(kBlue);
  h1_efficiency_jeteta->SetMarkerStyle(21);
  h1_efficiency_jeteta->Draw("P E same");
  h1_efficiency_jeteta->SetTitle("; Jet #eta; HF Jet Reco. Efficiency");
  h1_efficiency_jeteta->SetMinimum(0.);
  h1_efficiency_jeteta->SetMaximum(1.);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");
  // h1_efficiency_jeteta->SetYTitle("Counts");

  ccan[ican]->cd(3);

  h1_efficiency_HFpt->SetMarkerColor(kBlue);
  h1_efficiency_HFpt->SetMarkerStyle(21);
  h1_efficiency_HFpt->Draw("P E SAME");
  h1_efficiency_HFpt->SetTitle("; HF pT; HF Jet Reco. Efficiency");
  h1_efficiency_HFpt->SetMinimum(0.);
  h1_efficiency_HFpt->SetMaximum(1.05);

  f_eff1->Draw("SAME");
  f_eff2->Draw("SAME");

  ccan[ican]->cd(4);

  h1_efficiency_HFeta->SetMarkerColor(kBlue);
  h1_efficiency_HFeta->SetMarkerStyle(21);
  h1_efficiency_HFeta->Draw("P E SAME");
  h1_efficiency_HFeta->SetTitle("; HF #eta; HF Jet Reco. Efficiency");
  h1_efficiency_HFeta->SetMinimum(0.);
  h1_efficiency_HFeta->SetMaximum(1.);

  ccan[ican]->cd(5);

  h2_efficiency_HFpteta->Draw("COLZ TEXT");
  h2_efficiency_HFpteta->SetTitle("; HF p_{T}; HF #eta; Jet Reco Efficiency");
  h2_efficiency_HFpteta->SetMinimum(0.);
  // h2_efficiency_HFpteta->SetMaximum(1.);

  ccan[ican]->cd(6);

  h2_efficiency_jetpteta->Draw("COLZ TEXT");
  h2_efficiency_jetpteta->SetTitle("; jet p_{T}; jet #eta; Jet Reco Efficiency");
  h2_efficiency_jetpteta->SetMinimum(0.);
  // h2_efficiency_jetpteta->SetMaximum(1.);

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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  //  cout<<h2_response_dR->Integral()<<endl;
  h2_response_dR->Draw("COLZ TEXT");

  // h1_purity_Erad->SetXTitle("E_{radiator}");
  // h1_purity_Erad->SetYTitle("Counts");
  ccan[ican]->cd(2);
  cout << h2_response_theta->Integral() << endl;
  h2_response_theta->Draw("COLZ TEXT");
  // h1_efficiency_theta->SetMinimum(0.0);

  ccan[ican]->cd(3);
  h2_response_Erad->Draw("COLZ TEXT");

  ccan[ican]->cd(4);
  h2_response_kt->Draw("COLZ TEXT");

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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  h2_response_dR->Draw("COLZ");

  // h1_purity_Erad->SetXTitle("E_{radiator}");
  // h1_purity_Erad->SetYTitle("Counts");
  ccan[ican]->cd(2);
  h1_truth_dR->Draw("P E");
  // h1_efficiency_theta->SetMinimum(0.0);

  ccan[ican]->cd(3);
  h1_fakes_dR->Draw("P E");

  ccan[ican]->cd(4);
  h1_meas_dR->Draw("P E");

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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_purity_ktdR->Draw("COLZ");
  h2_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h2_purity_ktdR->SetMaximum(1.0);
  // h2_purity_ktdR->SetMinimum(0.0);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(2);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_num_purity_ktdR->Draw("COLZ");
  h2_num_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(3);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_denom_purity_ktdR->Draw("COLZ");
  h2_denom_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");
  ccan[ican]->cd(4);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_purity_zdR->Draw("COLZ");
  h2_purity_zdR->SetTitle("; ln(R/#Delta R); ln(1/z)");
  // h2_purity_ktdR->SetMaximum(1.0);
  // h2_purity_ktdR->SetMinimum(0.0);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

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
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 3);
  ccan[ican]->cd(1);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_efficiency_ktdR->Draw("COLZ");
  h2_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h2_efficiency_ktdR->SetMaximum(1.0);
  // h2_efficiency_ktdR->SetMinimum(0.0);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(2);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_num_efficiency_ktdR->Draw("COLZ");
  h2_num_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(3);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_denom_efficiency_ktdR->Draw("COLZ");
  h2_denom_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");
  ccan[ican]->cd(4);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_efficiency_zdR->Draw("COLZ");
  h2_efficiency_zdR->SetTitle("; ln(R/#Delta R); ln(1/z)");
  // h2_efficiency_ktdR->SetMaximum(1.0);
  // h2_efficiency_ktdR->SetMinimum(0.0);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

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
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_efficiency_thetaErad->Draw("COLZ");
  h2_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h2_efficiency_thetaErad->SetMaximum(1.0);
  // h2_efficiency_thetaErad->SetMinimum(0.0);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(2);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_num_efficiency_thetaErad->Draw("COLZ");
  h2_num_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(3);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_denom_efficiency_thetaErad->Draw("COLZ");
  h2_denom_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");
  ccan[ican]->cd(4);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_purity_thetaErad->Draw("COLZ");
  h2_purity_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h2_efficiency_thetaErad->SetMaximum(1.0);
  // h2_efficiency_thetaErad->SetMinimum(0.0);
  // h1_efficiency_jeteta->SetXTitle("E_{radiator}");

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

  f.Write();
  f.Close();

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());

    cout << "Num of True B jets = " << NumBjets << endl;
    cout << "Num of Reco B jets = " << NumRecoBjets << endl;
    //
    // sprintf(buf,"/usr/bin/ps2pdf %s %s",plotfile.Data(),plotfilePDF.Data());
    // cout<<" "<<buf<<endl;
    // int iSuccess = gSystem->Exec(buf);
    // if (iSuccess==0){
    // 	sprintf(buf,"/bin/rm %s",plotfile.Data());
    // 	gSystem->Exec(buf);
    // 	cout<<" "<<buf<<endl;
    // } else {
    // 	cout<<" PDF creation failed ... "<<plotfile.Data()<<endl;
    // }
    //		sprintf(buf,"/usr/bin/scp %s wjllope@rhic22.physics.wayne.edu:/Library/WebServer/WebPages/files/",plotfilePDF.Data());
    //		gSystem->Exec(buf);
    //		cout<<" "<<buf<<endl;
  }

  // CAJetAlgo(std::string filename);

  // loop(ptMax, Nsubsets);
  // write(ptMax, Nsubsets);
}
