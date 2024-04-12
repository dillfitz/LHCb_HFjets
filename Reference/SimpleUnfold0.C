

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

// #include "ZjetLuC"

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

void SimpleUnfold(int NumEvts = -1,
                  int dataset = 91599,
                  bool chargedJetCut_user = false,
                  double minimum_dR = 0.1,
                  bool DoReverse = false,
                  int DoJES = 0,
                  bool DoJER = false,
                  bool DoTrackEff = false,
                  bool DoTrackPt = false,
                  bool DoGhostCut = false)
{

  // gROOT->ProcessLine(".L ZjetLuC");

  // TFile *input = new TFile("/home/chahrour/DeadCone/", "read");

  // int flavor = -99;
  // cout<<"Current Flavor = "<<flavor<<endl;
  //  while(flavor != 0 && flavor != 4 && flavor != 5){
  //    cout<<"Please choose flavor (0: light, 4: charm, 5: beauty): ";
  //    cin>>flavor;
  //  }
  // pt_cut = true;
  // Erad_cut = Erad_cut_user;
  // kt_cut = true;
  // pt_track_cut = false;
  // isData = fa;
  bool isData = false;
  followHardest = false;
  truthLevel = false;
  chargedJetCut = chargedJetCut_user;
  if (truthLevel)
  {
    ghostCut = false;
  }

  if (DoGhostCut)
    ghostProb = 0.3;

  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;

  if (flavor == 5)
  {
    mass_num = 4.2;
    HF_pdgcode = 521;
  }
  else if (flavor == 4)
  {
    mass_num = 1.25;
    HF_pdgcode = 421;
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

  if (isData)
    str_level = "data";
  else
  {
    if (truthLevel)
      str_level = "truth";
    else
      str_level = "reco";
  }

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
  extension = TString("unfold_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  if (DoReverse)
    extension = "reverse_" + extension;
  if (DoJES == 1)
    extension = TString("JESPos_") + extension;
  else if (DoJES == 2)
    extension = TString("JESNeg_") + extension;
  if (DoJER)
    extension = TString("JER_") + extension;
  if (DoTrackEff)
    extension = TString("trackeff_") + extension;
  if (DoTrackPt)
    extension = TString("trackpt_") + extension;
  if (DoGhostCut)
    extension = TString("ghostcut_") + extension;
  // ZjetTree Tree(0, dataset, isData);

  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  TString extension_read, extension_eff;

  TString dir_deadcone("$LUND/Bjets/");

  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
  extension_eff = TString("hists/efficiency_truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged+ str_Mag + str_flavor + Form("_%d", dataset);

  if (DoJES == 1)
    extension_read = TString("JESPos_") + extension_read;
  else if (DoJES == 2)
    extension_read = TString("JESNeg_") + extension_read;

  if (DoJER)
    extension_read = TString("JER_") + extension_read;
  if (DoTrackEff)
    extension_read = TString("trackeff_") + extension_read;
  if (DoTrackPt)
    extension_read = TString("trackpt_") + extension_read;
  if (DoGhostCut)
    extension_read = TString("ghostcut_") + extension_read;

  TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
  cout << "File:" << endl;
  cout << extension_read << endl;
  TTree *LundTree = (TTree *)fread.Get("LundTree");
  if (NumEvts > LundTree->GetEntries())
    NumEvts = LundTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = LundTree->GetEntries();

  TFile *file_eff = new TFile(extension_eff + TString(".root"), "READ");

  TH1D* h1_denom_efficiency_HFpt = (TH1D*) file_eff->Get("h1_denom_efficiency_HFpt");
  TH1D* h1_denom_efficiency_HFpt15 = (TH1D*) file_eff->Get("h1_denom_efficiency_HFpt15");
  TH2D* h2_denom_efficiency_HFptjetpt = (TH2D*) file_eff->Get("h2_denom_efficiency_HFptjetpt");
  TH2D* h2_denom_efficiency_jetpteta = (TH2D*) file_eff->Get("denom_efficiency_jetpteta");
  TH1D* h1_denom_efficiency_jetpt = (TH1D*) file_eff->Get("h1_denom_efficiency_jetpt");

  TFile *f = TFile::Open(dir_deadcone + "hists/" + extension + ".root", "RECREATE");

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
  TH1D *h1_num_efficiency_theta = new TH1D("num_efficiency_theta", "", tr_thetabinsize, tr_theta_binedges);
  TH1D *h1_num_efficiency_Erad = new TH1D("num_efficiency_Erad", "", tr_Eradbinsize, tr_Erad_binedges);
  TH1D *h1_num_efficiency_kT = new TH1D("num_efficiency_kT", "", tr_ktbinsize, tr_kt_binedges);
  TH1D *h1_num_efficiency_dR = new TH1D("num_efficiency_dR", "", tr_dRbinsize, tr_dR_binedges);
  TH1D *h1_num_efficiency_z = new TH1D("num_efficiency_z", "", tr_zbinsize, tr_z_binedges);

  TH1D *h1_denom_purity_theta = new TH1D("denom_purity_theta", "", thetabinsize, theta_binedges);
  TH1D *h1_denom_purity_Erad = new TH1D("denom_purity_Erad", "", Eradbinsize, Erad_binedges);
  TH1D *h1_denom_purity_kT = new TH1D("denom_purity_kT", "", ktbinsize, kt_binedges);
  TH1D *h1_denom_purity_dR = new TH1D("denom_purity_dR", "", dRbinsize, dR_binedges);
  TH1D *h1_denom_purity_z = new TH1D("denom_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_denom_efficiency_theta = new TH1D("denom_efficiency_theta", "", tr_thetabinsize, tr_theta_binedges);
  TH1D *h1_denom_efficiency_Erad = new TH1D("denom_efficiency_Erad", "", tr_Eradbinsize, tr_Erad_binedges);
  TH1D *h1_denom_efficiency_kT = new TH1D("denom_efficiency_kT", "", tr_ktbinsize, tr_kt_binedges);
  TH1D *h1_denom_efficiency_dR = new TH1D("denom_efficiency_dR", "", tr_dRbinsize, tr_dR_binedges);
  TH1D *h1_denom_efficiency_z = new TH1D("denom_efficiency_z", "", tr_zbinsize, tr_z_binedges);

  TH1D *h1_num_purity_jetpt = new TH1D("num_purity_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_denom_purity_jetpt = new TH1D("denom_purity_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_num_purity_HFpt = new TH1D("num_purity_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_denom_purity_HFpt = new TH1D("denom_purity_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_purity_HFpt15 = new TH1D("num_purity_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_denom_purity_HFpt15 = new TH1D("denom_purity_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_purity_eta = new TH1D("num_purity_eta", "", etabinsize, eta_binedges);
  TH1D *h1_denom_purity_eta = new TH1D("denom_purity_eta", "", etabinsize, eta_binedges);

  TH1D *h1_num_efficiency_HFpt = new TH1D("num_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_efficiency_HFpt15 = new TH1D("num_efficiency_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_efficiency_jetpt = new TH1D("num_efficiency_jetpt", "", ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_HFptjetpt = new TH2D("num_efficiency_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_num_purity_HFptjetpt = new TH2D("num_purity_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_denom_purity_HFptjetpt = new TH2D("denom_purity_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);

  TH2D *h2_num_purity_HFpteta = new TH2D("num_purity_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
  TH2D *h2_denom_purity_HFpteta = new TH2D("denom_purity_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);

  TH2D *h2_denom_purity_jetpteta = new TH2D("denom_purity_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_num_purity_jetpteta = new TH2D("num_purity_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);

  TH2D *h2_num_efficiency_jetpteta = new TH2D("num_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);

  TEfficiency *t1_efficiency_dR = new TEfficiency("t1_efficiency_dR", "", dRbinsize, dR_binedges);

  // TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
  // TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize_truth, pt_binedges_truth);
  // TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);

  TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);

  TH2D *h2_jetpteta = new TH2D("jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);

  RooUnfoldResponse *response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, "response_jetpt");
  RooUnfoldResponse *response_jeteta = new RooUnfoldResponse(h1_num_purity_eta, h1_num_purity_eta, "response_jeteta");
  RooUnfoldResponse *response_HFptjetpt = new RooUnfoldResponse(h2_denom_efficiency_HFptjetpt, h2_denom_efficiency_HFptjetpt, "response_HFptjetpt");
  RooUnfoldResponse *response_jetpteta = new RooUnfoldResponse(h2_jetpteta, h2_jetpteta, "response_jetpteta");

  TH2D *h2_num_purity_ktdR = new TH2D("num_purity_ktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);
  TH2D *h2_denom_purity_ktdR = new TH2D("denom_purity_ktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges);

  TH2D *h2_num_purity_zdR = new TH2D("num_purity_zdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);
  TH2D *h2_denom_purity_zdR = new TH2D("denom_purity_zdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges);

  TH2D *h2_num_purity_thetaErad = new TH2D("num_purity_thetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges);
  TH2D *h2_denom_purity_thetaErad = new TH2D("denom_purity_thetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges);

  TH2D *h2_num_efficiency_ktdR = new TH2D("num_efficiency_ktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges);
  TH2D *h2_denom_efficiency_ktdR = new TH2D("denom_efficiency_ktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges);

  TH2D *h2_num_efficiency_zdR = new TH2D("num_efficiency_zdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges);
  TH2D *h2_denom_efficiency_zdR = new TH2D("denom_efficiency_zdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges);

  TH2D *h2_num_efficiency_thetaErad = new TH2D("num_efficiency_thetaErad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges);
  TH2D *h2_denom_efficiency_thetaErad = new TH2D("denom_efficiency_thetaErad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges);

  RooUnfoldResponse *response_theta = new RooUnfoldResponse(h1_denom_purity_theta, h1_denom_efficiency_theta, "response_theta");

  RooUnfoldResponse *response_ktdR = new RooUnfoldResponse(h2_ktdR, h2_matchedktdR, "response_ktdR");
  RooUnfoldResponse *response_zdR = new RooUnfoldResponse(h2_zdR, h2_matchedzdR, "response_zdR");
  RooUnfoldResponse *response_dR = new RooUnfoldResponse(h1_denom_purity_dR, h1_denom_efficiency_dR, "response_dR");
  RooUnfoldResponse *response_kt = new RooUnfoldResponse(h1_denom_purity_kT, h1_denom_efficiency_kT, "response_kT");
  RooUnfoldResponse *response_Erad = new RooUnfoldResponse(h1_denom_purity_Erad, h1_denom_efficiency_Erad, "response_Erad");

  TH3D *h3_etaktdR = new TH3D("etaktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_matchedetaktdR = new TH3D("matchedetaktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_num_efficiency_etaktdR = new TH3D("num_efficiency_etaktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_denom_efficiency_etaktdR = new TH3D("denom_efficiency_etaktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_efficiency_etaktdR = new TH3D("efficiency_etaktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_num_purity_etaktdR = new TH3D("num_purity_etaktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_denom_purity_etaktdR = new TH3D("denom_purity_etaktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, etabinsize, eta_binedges);
  TH3D *h3_purity_etaktdR = new TH3D("purity_etaktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, etabinsize, eta_binedges);

  RooUnfoldResponse *response_etaktdR = new RooUnfoldResponse(h3_etaktdR, h3_matchedetaktdR, "response_etaktdR");

  TH3D *h3_ptktdR = new TH3D("ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_matchedptktdR = new TH3D("matchedptktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptktdR = new TH3D("num_efficiency_ptktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_efficiency_ptktdR = new TH3D("denom_efficiency_ptktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptktdR = new TH3D("efficiency_ptktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptktdR = new TH3D("num_purity_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptktdR = new TH3D("denom_purity_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptktdR = new TH3D("purity_ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptktdR = new RooUnfoldResponse(h3_ptktdR, h3_matchedptktdR, "response_ptktdR");

  TH3D *h3_ptzdR = new TH3D("ptzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_matchedptzdR = new TH3D("matchedptzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptzdR = new TH3D("num_efficiency_ptzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_efficiency_ptzdR = new TH3D("denom_efficiency_ptzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptzdR = new TH3D("efficiency_ptzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptzdR = new TH3D("num_purity_ptzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptzdR = new TH3D("denom_purity_ptzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptzdR = new TH3D("purity_ptzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptzdR = new RooUnfoldResponse(h3_ptzdR, h3_matchedptzdR, "response_ptzdR");

  TH3D *h3_ptthetaErad = new TH3D("ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_matchedptthetaErad = new TH3D("matchedptthetaErad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptthetaErad = new TH3D("num_efficiency_ptthetaErad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_efficiency_ptthetaErad = new TH3D("denom_efficiency_ptthetaErad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptthetaErad = new TH3D("efficiency_ptthetaErad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptthetaErad = new TH3D("num_purity_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptthetaErad = new TH3D("denom_purity_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptthetaErad = new TH3D("purity_ptthetaErad", "", Eradbinsize, Erad_binedges, thetabinsize, theta_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptthetaErad = new RooUnfoldResponse(h3_ptthetaErad, h3_matchedptthetaErad, "response_ptthetaErad");

  TH3D *h3_ptHFktdR = new TH3D("ptHFktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_matchedptHFktdR = new TH3D("matchedptHFktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_num_efficiency_ptHFktdR = new TH3D("num_efficiency_ptHFktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_denom_efficiency_ptHFktdR = new TH3D("denom_efficiency_ptHFktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_efficiency_ptHFktdR = new TH3D("efficiency_ptHFktdR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_num_purity_ptHFktdR = new TH3D("num_purity_ptHFktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_denom_purity_ptHFktdR = new TH3D("denom_purity_ptHFktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_purity_ptHFktdR = new TH3D("purity_ptHFktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptHFbinsize, ptHF_binedges);

  RooUnfoldResponse *response_ptHFktdR = new RooUnfoldResponse(h3_ptHFktdR, h3_matchedptHFktdR, "response_ptHFktdR");

  TH3D *h3_ptHFzdR = new TH3D("ptHFzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_matchedptHFzdR = new TH3D("matchedptHFzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_num_efficiency_ptHFzdR = new TH3D("num_efficiency_ptHFzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_denom_efficiency_ptHFzdR = new TH3D("denom_efficiency_ptHFzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_efficiency_ptHFzdR = new TH3D("efficiency_ptHFzdR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_num_purity_ptHFzdR = new TH3D("num_purity_ptHFzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_denom_purity_ptHFzdR = new TH3D("denom_purity_ptHFzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptHFbinsize, ptHF_binedges);
  TH3D *h3_purity_ptHFzdR = new TH3D("purity_ptHFzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptHFbinsize, ptHF_binedges);

  RooUnfoldResponse *response_ptHFzdR = new RooUnfoldResponse(h3_ptHFzdR, h3_matchedptHFzdR, "response_ptHFzdR");

  TH2D *h2_ptkt = new TH2D("ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_matchedptkt = new TH2D("matchedptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptkt = new TH2D("num_efficiency_ptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_efficiency_ptkt = new TH2D("denom_efficiency_ptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptkt = new TH2D("efficiency_ptkt", "", tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptkt = new TH2D("num_purity_ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptkt = new TH2D("denom_purity_ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptkt = new TH2D("purity_ptkt", "", ktbinsize, kt_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptkt = new RooUnfoldResponse(h2_ptkt, h2_matchedptkt, "response_ptkt");

  f1_theta_Erad->SetParameter(0, mass_num);
  f1_kt_Erad->SetParameter(0, 2 * LambdaQCD);

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
  vector<RooUnfoldResponse *> vec_response_ptktdR;
  vector<TH3D *> vec_h3_ptktdR,
      vec_h3_matchedptktdR,
      vec_h3_num_efficiency_ptktdR,
      vec_h3_denom_efficiency_ptktdR,
      vec_h3_efficiency_ptktdR,
      vec_h3_num_purity_ptktdR,
      vec_h3_denom_purity_ptktdR,
      vec_h3_purity_ptktdR;

  vector<RooUnfoldResponse *> vec_response_ptzdR;
  vector<TH3D *> vec_h3_ptzdR,
      vec_h3_matchedptzdR,
      vec_h3_num_efficiency_ptzdR,
      vec_h3_denom_efficiency_ptzdR,
      vec_h3_efficiency_ptzdR,
      vec_h3_num_purity_ptzdR,
      vec_h3_denom_purity_ptzdR,
      vec_h3_purity_ptzdR;
  for (int i = 0; i < ptHFbinsize; i++)
  {
    for (int j = 0; j < HFetabinsize; j++)
    {
      TH3D *h3_ptktdR_tmp = new TH3D(Form("ptktdR%d%d", i, j), "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_matchedptktdR_tmp = new TH3D(Form("matchedptktdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_num_efficiency_ptktdR_tmp = new TH3D(Form("num_efficiency_ptktdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_denom_efficiency_ptktdR_tmp = new TH3D(Form("denom_efficiency_ptktdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_efficiency_ptktdR_tmp = new TH3D(Form("efficiency_ptktdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_num_purity_ptktdR_tmp = new TH3D(Form("num_purity_ptktdR%d%d", i, j), "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_denom_purity_ptktdR_tmp = new TH3D(Form("denom_purity_ptktdR%d%d", i, j), "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
      TH3D *h3_purity_ptktdR_tmp = new TH3D(Form("purity_ptktdR%d%d", i, j), "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
      vec_h3_ptktdR.push_back(h3_ptktdR_tmp);
      vec_h3_matchedptktdR.push_back(h3_matchedptktdR_tmp);
      vec_h3_num_efficiency_ptktdR.push_back(h3_num_efficiency_ptktdR_tmp);
      vec_h3_denom_efficiency_ptktdR.push_back(h3_denom_efficiency_ptktdR_tmp);
      vec_h3_efficiency_ptktdR.push_back(h3_efficiency_ptktdR_tmp);
      vec_h3_num_purity_ptktdR.push_back(h3_num_purity_ptktdR_tmp);
      vec_h3_denom_purity_ptktdR.push_back(h3_denom_purity_ptktdR_tmp);
      vec_h3_purity_ptktdR.push_back(h3_purity_ptktdR_tmp);

      RooUnfoldResponse *response_ptktdR_temp = new RooUnfoldResponse(h3_ptktdR_tmp, h3_matchedptktdR_tmp, Form("response_ptktdR%d", i));
      vec_response_ptktdR.push_back(response_ptktdR_temp);

      TH3D *h3_ptzdR_tmp = new TH3D(Form("ptzdR%d%d", i, j), "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_matchedptzdR_tmp = new TH3D(Form("matchedptzdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_num_efficiency_ptzdR_tmp = new TH3D(Form("num_efficiency_ptzdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_denom_efficiency_ptzdR_tmp = new TH3D(Form("denom_efficiency_ptzdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_efficiency_ptzdR_tmp = new TH3D(Form("efficiency_ptzdR%d%d", i, j), "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_num_purity_ptzdR_tmp = new TH3D(Form("num_purity_ptzdR%d%d", i, j), "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_denom_purity_ptzdR_tmp = new TH3D(Form("denom_purity_ptzdR%d%d", i, j), "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
      TH3D *h3_purity_ptzdR_tmp = new TH3D(Form("purity_ptzdR%d%d", i, j), "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
      vec_h3_ptzdR.push_back(h3_ptzdR_tmp);
      vec_h3_matchedptzdR.push_back(h3_matchedptzdR_tmp);
      vec_h3_num_efficiency_ptzdR.push_back(h3_num_efficiency_ptzdR_tmp);
      vec_h3_denom_efficiency_ptzdR.push_back(h3_denom_efficiency_ptzdR_tmp);
      vec_h3_efficiency_ptzdR.push_back(h3_efficiency_ptzdR_tmp);
      vec_h3_num_purity_ptzdR.push_back(h3_num_purity_ptzdR_tmp);
      vec_h3_denom_purity_ptzdR.push_back(h3_denom_purity_ptzdR_tmp);
      vec_h3_purity_ptzdR.push_back(h3_purity_ptzdR_tmp);

      RooUnfoldResponse *response_ptzdR_temp = new RooUnfoldResponse(h3_ptzdR_tmp, h3_matchedptzdR_tmp, Form("response_ptzdR%d", i));
      vec_response_ptzdR.push_back(response_ptzdR_temp);
    }
  }

  JetDefinition jet_def(cambridge_algorithm, jetradius);
  PseudoJet dtr1, dtr2;

  //
  // Event loop
  //
  unsigned long long last_eventNum = 0;
  double last_jetpT = 0.;
  int event_counter = 0;

  cout << LundTree->GetEntries() << endl;
  vector<double> *thetas = 0;
  vector<double> *tr_thetas = 0;
  vector<double> *dRs(0), *tr_dRs(0);
  vector<double> *Erads(0), *tr_Erads(0);
  vector<double> *kts = 0;
  vector<double> *tr_kts = 0;
  vector<double> *raps(0), *tr_raps(0);
  vector<double> *phis(0), *tr_phis(0);
  vector<double> *zs(0), *tr_zs(0);

  double jet_pt, HF_pt, jet_eta, tr_jet_pt, tr_jet_eta, tr_HF_pt, bmass_dtf;
  double HF_px, HF_py, HF_pz, HF_e;
  bool isTrueBjet;
  int NumBHads_tr;
  int eventNumber;

  LundTree->SetBranchAddress("thetas", &thetas);
  LundTree->SetBranchAddress("Erads", &Erads);
  LundTree->SetBranchAddress("dRs", &dRs);
  LundTree->SetBranchAddress("kts", &kts);
  LundTree->SetBranchAddress("zs", &zs);
  LundTree->SetBranchAddress("raps", &raps);
  LundTree->SetBranchAddress("phis", &phis);

  LundTree->SetBranchAddress("HF_px", &HF_px);
  LundTree->SetBranchAddress("HF_py", &HF_py);
  LundTree->SetBranchAddress("HF_pz", &HF_pz);
  LundTree->SetBranchAddress("HF_e", &HF_e);
  LundTree->SetBranchAddress("HF_pt", &HF_pt);

  LundTree->SetBranchAddress("tr_thetas", &tr_thetas);
  LundTree->SetBranchAddress("tr_Erads", &tr_Erads);
  LundTree->SetBranchAddress("tr_dRs", &tr_dRs);
  LundTree->SetBranchAddress("tr_kts", &tr_kts);
  LundTree->SetBranchAddress("tr_zs", &tr_zs);
  LundTree->SetBranchAddress("tr_raps", &tr_raps);
  LundTree->SetBranchAddress("tr_phis", &tr_phis);

  LundTree->SetBranchAddress("jet_pt", &jet_pt);
  LundTree->SetBranchAddress("jet_eta", &jet_eta);

  LundTree->SetBranchAddress("tr_jet_pt", &tr_jet_pt);
  LundTree->SetBranchAddress("tr_HF_pt", &tr_HF_pt);
  LundTree->SetBranchAddress("tr_jet_eta", &tr_jet_eta);
  LundTree->SetBranchAddress("isTrueBjet", &isTrueBjet);
  LundTree->SetBranchAddress("NumBHads_tr", &NumBHads_tr);
  LundTree->SetBranchAddress("bmass_dtf", &bmass_dtf);
  LundTree->SetBranchAddress("eventNumber", &eventNumber);

  int eventNum;
  cout << "Requested # of events" << NumEvts << endl;

  std::ofstream myfile;
  myfile.open(Form("data/bjet_dataset_%d.csv", dataset));

  myfile << "jet pt"
         << ",";
  myfile << "jet eta"
         << ",";
  // myfile << HF_pt << ",";
  // myfile << HF_eta << ",";
  myfile << "logdR"
         << ",";
  myfile << "logz"
         << ",";
  myfile << "logkt"
         << ",";
  myfile << "tr_jet_pt"
         << ",";
  myfile << "tr_jet_eta"
         << ",";
  // myfile << tr_HF_pt << ",";
  // myfile << tr_HF_eta << ",";
  myfile << "tr_logdR"
         << ",";
  myfile << "tr_logz"
         << ",";
  myfile << "tr_logkt"
         << "\n";

  int NumBjets = 0;
  int NumTrueBjets = 0;

  for (int ev = 0; ev < NumEvts; ev++)
  {
    LundTree->GetEntry(ev);

    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;
    double MassMu = 5.27940;
    double MassSigma = 1.32479e-02;
    // double MassHigh = MassMu + 3 * MassSigma;
    // double MassLow = MassMu - 3 * MassSigma;
    double MassHigh = 5.31;
    double MassLow = 5.24;
    bool mass_cond = (bmass_dtf > MassLow && bmass_dtf < MassHigh);
    if (!mass_cond){
      continue;
    }
      
    TLorentzVector HFmeson(HF_px, HF_py, HF_pz, HF_e);
    double HF_eta = HFmeson.Eta();
    // if(NumBHads_tr > 1) continue; // does not change much
    if(tr_jet_pt > 15. && isTrueBjet && jet_pt > 15. && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta < etaMax && jet_eta > etaMin)
      {
        h2_num_efficiency_HFptjetpt->Fill(HFmeson.Pt(), tr_jet_pt);
      } 
    if(tr_jet_pt > 15. && tr_jet_pt < 20. && isTrueBjet && jet_pt > 15. && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta > etaMin && jet_eta < etaMax)
      {
        h1_num_efficiency_HFpt15->Fill(HFmeson.Pt());
      } 

    if(tr_jet_pt > 15. && isTrueBjet && jet_pt > 15. && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta < etaMax && jet_eta > etaMin)
      {
        h1_num_efficiency_jetpt->Fill(tr_jet_pt);
      } 
    if(tr_jet_pt > 15. && isTrueBjet && jet_pt > 15.)
      {
        h2_num_efficiency_jetpteta->Fill(tr_jet_pt, tr_jet_eta);
      } 

    if(tr_jet_pt > ptMin && tr_jet_pt < ptMax && isTrueBjet && jet_pt > 15. && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta > etaMin && jet_eta < etaMax)
      {
        h1_num_efficiency_HFpt->Fill(HFmeson.Pt());
        // h1_num_efficiency_jetpt->Fill(tr_jet_pt);
      } 

    if (jet_pt > 15. && jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_denom_purity_jetpt->Fill(jet_pt); 
      h1_denom_purity_eta->Fill(jet_eta);
    }
    if (isTrueBjet && tr_jet_pt > 15. &&
        jet_pt > 15. &&
        jet_eta < etaMax && jet_eta > etaMin &&
        tr_jet_eta < etaMax && tr_jet_eta > etaMin)
    {
      h1_num_purity_jetpt->Fill(jet_pt);
      h1_num_purity_eta->Fill(jet_eta);
    }
    if(jet_pt > 15.){
      h2_denom_purity_jetpteta->Fill(jet_pt, jet_eta);
    }
    if (isTrueBjet && tr_jet_pt > 15. &&
        jet_pt > 15.)
    {
      h2_num_purity_jetpteta->Fill(jet_pt, jet_eta);
    }

    if (jet_pt > 15. && jet_pt < 20. && jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_denom_purity_HFpt15->Fill(HF_pt);
    }
    if (jet_pt > ptMin && jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_denom_purity_HFpt->Fill(HF_pt);
      h2_denom_purity_HFpteta->Fill(HF_pt, HF_eta);
      NumBjets++;
    }
    if (jet_pt > 15. && jet_eta < etaMax && jet_eta > etaMin)
    {
      h2_denom_purity_HFptjetpt->Fill(HFmeson.Pt(), jet_pt);
    }

     if (isTrueBjet && tr_jet_pt > 15. &&
        jet_pt > 15. && jet_pt < ptMin &&
        jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_num_purity_HFpt15->Fill(HF_pt);
    }
    if (isTrueBjet && tr_jet_pt > 15. &&
        jet_pt > ptMin &&
        jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_num_purity_HFpt->Fill(HF_pt);
      // h1_num_purity_HFeta->Fill(HF_eta);
      h2_num_purity_HFpteta->Fill(HF_pt, HF_eta);
      NumTrueBjets++;
    }
    if (isTrueBjet && tr_jet_pt > 15. &&
        jet_pt > 15. &&
        jet_eta < etaMax && jet_eta > etaMin &&
        tr_jet_eta < etaMax && tr_jet_eta > etaMin)
    {
      h2_num_purity_HFptjetpt->Fill(HFmeson.Pt(), jet_pt);
    }

    if (jet_pt < 15.)
      continue;
    if (tr_jet_pt < 15.)
      continue;
    if (!isTrueBjet)
      continue;

    response_jetpteta->Fill(jet_pt, jet_eta, tr_jet_pt, tr_jet_eta);
    

    if (jet_eta < etaMin || jet_eta > etaMax)
      continue;
    if (tr_jet_eta > etaMax || tr_jet_eta < etaMin)
      continue;

    response_jetpt->Fill(jet_pt, tr_jet_pt);
    response_jeteta->Fill(jet_eta, tr_jet_eta);
    response_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, HFmeson.Pt(), tr_jet_pt);

    // if(kts->size()<1) continue;
    // if(tr_kts->size()<1) continue;
    // if(jet_pt > ptMax) continue;
    h2_truthreco_jetpt->Fill(jet_pt, tr_jet_pt);
    event_counter++;

    // cout<<"New Event: "<<endl;

    // cout<<"New Event:"<<endl;
    //   cout<<"Num emissions = "<<kts->size()<<endl;
    //   cout<<"Num true emissions = "<<tr_kts->size()<<endl;
    //   cout<<tr_jet_pt<<", "<<tr_jet_eta<<", "<<tr_kts->size()<<endl;
    // cout<<jet_pt<<", "<<jet_eta<<", "<<kts->size()<<endl;

    int match_loc = -99;
    int rev_match_loc = -99;
    if (DoReverse)
    {
      reverse(kts->begin(), kts->end());
      reverse(dRs->begin(), dRs->end());
      reverse(zs->begin(), zs->end());
      reverse(Erads->begin(), Erads->end());
      reverse(thetas->begin(), thetas->end());
      reverse(raps->begin(), raps->end());
      reverse(phis->begin(), phis->end());

      // reverse(tr_kts->begin(), tr_kts->end());
      // reverse(tr_dRs->begin(), tr_dRs->end());
      // reverse(tr_zs->begin(), tr_zs->end());
      // reverse(tr_Erads->begin(), tr_Erads->end());
      // reverse(tr_thetas->begin(), tr_thetas->end());
      // reverse(tr_raps->begin(), tr_raps->end());
      // reverse(tr_phis->begin(), tr_phis->end());
    }
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
      if (logkt < -3.)
        continue;

      bool found_match = false;
      double min_dr = minimum_dR;
      for (int j = 0; j < tr_kts->size(); j++)
      {
        double tr_logkt = log(tr_kts->at(j));
        double tr_rap = tr_raps->at(j);
        double tr_phi = tr_phis->at(j);

        if (tr_logkt < -3.)
          continue;

        bool banned = false;
        for (int k = 0; k < matchedbans.size(); k++)
        {
          if (j == matchedbans[k])
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
      temp.push_back(match_loc);
      if (match_loc > -1)
        matchedbans.push_back(match_loc);
    }

    for (int i = 0; i < tr_kts->size(); i++)
    {
      match_loc = -99;
      double logkt = log(tr_kts->at(i));
      double logdR = log(jetradius / tr_dRs->at(i));
      double logz = log(1. / tr_zs->at(i));
      double logtheta = log(1. / tr_thetas->at(i));
      // double kttheta = ktthetas->at(i);
      double erad = tr_Erads->at(i);
      double rap = tr_raps->at(i);
      double phi = tr_phis->at(i);
      double dR_final = -99;
      if (logkt < -3.)
        continue;

      bool found_match = false;
      double min_dr = minimum_dR;
      for (int j = 0; j < kts->size(); j++)
      {
        double meas_logkt = log(kts->at(j));
        double meas_rap = raps->at(j);
        double meas_phi = phis->at(j);

        if (meas_logkt < -3.)
          continue;

        bool banned = false;
        for (int k = 0; k < bans.size(); k++)
        {
          if (j == bans[k])
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
      double tr_logkt = log(tr_kts->at(matchedbans[i]));
      double tr_logdR = log(jetradius / tr_dRs->at(matchedbans[i]));
      double tr_logz = log(1. / tr_zs->at(matchedbans[i]));
      double tr_logtheta = log(1. / tr_thetas->at(matchedbans[i]));
      double tr_erad = tr_Erads->at(matchedbans[i]);
      // cout<<"quants defined"<<endl;
      // cout<<"Match: ("<<rev_match_loc<<","<<match_loc<<")"<<endl;
      // cout<<"E: ("<<logkt<<","<<tr_logkt<<")"<<endl;
      // matchedbans.push_back(match_loc);
      // bans.push_back(rev_match_loc);
      if (!truthLevel)
      {
        if (jet_pt > ptMin && jet_pt < ptMax)
        {
          response_zdR->Fill(logdR, logz, tr_logdR, tr_logz);
          response_ktdR->Fill(logdR, logkt, tr_logdR, tr_logkt);
          response_dR->Fill(logdR, tr_logdR);
          response_kt->Fill(logkt, tr_logkt);
          response_theta->Fill(logtheta, tr_logtheta);
          response_Erad->Fill(erad, tr_erad);
          response_ptHFktdR->Fill(logdR, logkt, HF_pt, tr_logdR, tr_logkt, HFmeson.Pt());
          response_ptHFzdR->Fill(logdR, logz, HF_pt, tr_logdR, tr_logz, HFmeson.Pt());

          // response_zdR_nocorr->Fill(logdR, logz, tr_logdR, tr_logz);
          // response_ktdR_nocorr->Fill(logdR, logkt, tr_logdR, tr_logkt);
          // response_dR_nocorr->Fill(logdR, tr_logdR);
        }
        for (int i = 0; i < ptHFbinsize; i++)
        {
          if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
          {
            for (int j = 0; j < HFetabinsize; j++)
            {
              int loc = i * HFetabinsize + j;
              if (HF_eta > HFeta_binedges[j] && HF_eta < HFeta_binedges[j + 1])
              {
                vec_response_ptktdR[loc]->Fill(logdR, logkt, jet_pt, tr_logdR, tr_logkt, tr_jet_pt);
                vec_response_ptzdR[loc]->Fill(logdR, logz, jet_pt, tr_logdR, tr_logz, tr_jet_pt);
                break;
              }
            }
            break;
          }
        }
        myfile << jet_pt << ",";
        myfile << jet_eta << ",";
        // myfile << HF_pt << ",";
        // myfile << HF_eta << ",";
        myfile << logdR << ",";
        myfile << logz << ",";
        myfile << logkt << ",";
        myfile << tr_jet_pt << ",";
        myfile << tr_jet_eta << ",";
        // myfile << tr_HF_pt << ",";
        // myfile << tr_HF_eta << ",";
        myfile << tr_logdR << ",";
        myfile << tr_logz << ",";
        myfile << tr_logkt << "\n";

        // myfile << "\n";
        response_ptktdR->Fill(logdR, logkt, jet_pt, tr_logdR, tr_logkt, tr_jet_pt);
        response_ptzdR->Fill(logdR, logz, jet_pt, tr_logdR, tr_logz, tr_jet_pt);

        response_ptkt->Fill(logkt, jet_pt, tr_logkt, tr_jet_pt);

        // if(kttheta > LambdaQCD){
        response_ptthetaErad->Fill(erad, logtheta, jet_pt, tr_erad, tr_logtheta, tr_jet_pt);
        // }

        // response_ptHFktdR->Fill(logdR, logkt, HF_pt, tr_logdR, tr_logkt, tr_HF_pt);
        // response_ptHFzdR->Fill(logdR, logz, HF_pt, tr_logdR, tr_logz, tr_HF_pt);
      }
      h2_truthreco_Erad->Fill(tr_erad, erad);
      h2_truthreco_theta->Fill(tr_logtheta, logtheta);
      h2_truthreco_dR->Fill(tr_logdR, logdR);
      h2_truthreco_kT->Fill(tr_logkt, logkt);
      h2_truthreco_z->Fill(tr_logz, logz);

      for (int jj = 0; jj < dRbinsize; jj++)
      {
        if (tr_logdR > dR_binedges[jj] && tr_logdR < dR_binedges[jj + 1])
        {
          h1_dR_resolution_vec[jj]->Fill(dRs->at(bans[i]) - tr_dRs->at(matchedbans[i]));
        }
      }
      for (int jj = 0; jj < thetabinsize; jj++)
      {
        if (tr_logtheta > theta_binedges[jj] && tr_logtheta < theta_binedges[jj + 1])
        {
          h1_theta_resolution_vec[jj]->Fill(thetas->at(bans[i]) - tr_thetas->at(matchedbans[i]));
        }
      }
      // for(int jj = 0; jj < Eradbinsize; jj++){
      //   if(tr_erad > Erad_binedges[jj] && tr_erad < Erad_binedges[jj+1]){
      //     h1_Erad_resolution_vec[jj]->Fill(Erads->at(rev_match_loc) - tr_Erads->at(match_loc));
      //   }
      // }
    }

    // if(match_loc < 0){
    //   continue;;
    // }

    // for(int k = 0; k < kts->size(); k++){
    //    rap = raps->at(k);
    //    phi = phis->at(k);
    //    bool banned = false;
    //   for(int l = 0; l < bans.size(); l++){
    //     if(k == bans[l]) banned = true;
    //   }
    //   if(banned) continue;
    //    double tr_rap = tr_raps->at(match_loc);
    //    double tr_phi = tr_phis->at(match_loc);
    //    double drap = rap - tr_rap;
    //    double dphi = checkphi(checkphi(phi) - checkphi(tr_phi));
    //    double delta_R = sqrt(drap*drap + dphi*dphi);
    //    if(delta_R < min_dr)
    //   {
    //     // found_match = true;
    //     min_dr = delta_R;
    //     rev_match_loc = k;
    //     dR_final = delta_R;
    //   }
    // }
    // if(rev_match_loc == i) found_match = true;
    // // if(!matchedbans.empty()){
    // //   if(match_loc < matchedbans.back()){
    // //     continue;
    // //   }
    // // }

    // if(found_match){

    //   logkt = log(kts->at(rev_match_loc));
    //   logdR = log(jetradius/dRs->at(rev_match_loc));
    //   logz = log(1./zs->at(rev_match_loc));
    //   logtheta = log(1./thetas->at(rev_match_loc));
    //   erad = Erads->at(rev_match_loc);
    //   rap = raps->at(rev_match_loc);
    //   phi = phis->at(rev_match_loc);
    //   double tr_logkt = log(tr_kts->at(match_loc));
    //   double tr_logdR = log(jetradius/tr_dRs->at(match_loc));
    //   double tr_logz = log(1./tr_zs->at(match_loc));
    //   double tr_logtheta = log(1./tr_thetas->at(match_loc));
    //   double tr_erad = tr_Erads->at(match_loc);
    //   cout<<"Match: ("<<rev_match_loc<<","<<match_loc<<")"<<endl;
    //   cout<<"E: ("<<logkt<<","<<tr_logkt<<")"<<endl;
    //   matchedbans.push_back(match_loc);
    //   bans.push_back(rev_match_loc);
    //   if(!truthLevel){
    //     if(jet_pt > ptMin && jet_pt < ptMax){
    //       response_zdR->Fill(logdR, logz, tr_logdR, tr_logz);
    //       response_ktdR->Fill(logdR, logkt, tr_logdR, tr_logkt);
    //       response_dR->Fill(logdR, tr_logdR);
    //       response_kt->Fill(logkt, tr_logkt);
    //       response_theta->Fill(logtheta, tr_logtheta);
    //       response_Erad->Fill(erad, tr_erad);
    //       response_ptHFktdR->Fill(logdR, logkt, HF_pt, tr_logdR, tr_logkt, tr_HF_pt);
    //     response_ptHFzdR->Fill(logdR, logz, HF_pt, tr_logdR, tr_logz, tr_HF_pt);

    //       // response_zdR_nocorr->Fill(logdR, logz, tr_logdR, tr_logz);
    //       // response_ktdR_nocorr->Fill(logdR, logkt, tr_logdR, tr_logkt);
    //       // response_dR_nocorr->Fill(logdR, tr_logdR);
    //     }
    //     response_ptktdR->Fill(logdR, logkt, jet_pt, tr_logdR, tr_logkt, tr_jet_pt);
    //     response_ptzdR->Fill(logdR, logz, jet_pt, tr_logdR, tr_logz, tr_jet_pt);

    //     response_ptkt->Fill(logkt, jet_pt, tr_logkt, tr_jet_pt);

    //     // if(kttheta > LambdaQCD){
    //        response_ptthetaErad->Fill(erad, logtheta, jet_pt, tr_erad, tr_logtheta, tr_jet_pt);
    //     // }

    //     // response_ptHFktdR->Fill(logdR, logkt, HF_pt, tr_logdR, tr_logkt, tr_HF_pt);
    //     // response_ptHFzdR->Fill(logdR, logz, HF_pt, tr_logdR, tr_logz, tr_HF_pt);
    //   }
    //   h2_truthreco_Erad->Fill(tr_erad,erad);
    //   h2_truthreco_theta->Fill(tr_logtheta, logtheta);
    //   h2_truthreco_dR->Fill(tr_logdR, logdR);
    //   h2_truthreco_kT->Fill(tr_logkt, logkt);
    //   h2_truthreco_z->Fill(tr_logz, logz);

    //   for(int jj = 0; jj < dRbinsize; jj++){
    //     if(tr_logdR > dR_binedges[jj] && tr_logdR < dR_binedges[jj+1]){
    //       h1_dR_resolution_vec[jj]->Fill(dRs->at(rev_match_loc) - tr_dRs->at(match_loc));
    //     }
    //   }
    //   for(int jj = 0; jj < thetabinsize; jj++){
    //     if(tr_logtheta > theta_binedges[jj] && tr_logtheta < theta_binedges[jj+1]){
    //       h1_theta_resolution_vec[jj]->Fill(thetas->at(rev_match_loc) - tr_thetas->at(match_loc));
    //     }
    //   }
    //   // for(int jj = 0; jj < Eradbinsize; jj++){
    //   //   if(tr_erad > Erad_binedges[jj] && tr_erad < Erad_binedges[jj+1]){
    //   //     h1_Erad_resolution_vec[jj]->Fill(Erads->at(rev_match_loc) - tr_Erads->at(match_loc));
    //   //   }
    //   // }

    // }

    // cout<<"Filling purity"<<endl;
    for (int i = 0; i < kts->size(); i++)
    {
      double logkt = log(kts->at(i));
      double logdR = log(jetradius / dRs->at(i));
      double logz = log(1. / zs->at(i));
      double logtheta = log(1. / thetas->at(i));
      double erad = Erads->at(i);

      if (logkt < -3.)
        continue;
      // double kttheta = ktthetas->at(i);
      if (jet_pt > ptMin && jet_pt < ptMax)
      {
        h1_denom_purity_theta->Fill(logtheta);
        h1_denom_purity_Erad->Fill(erad);
        h1_denom_purity_kT->Fill(logkt);
        h1_denom_purity_dR->Fill(logdR);
        h1_denom_purity_z->Fill(logz);
        h2_denom_purity_ktdR->Fill(logdR, logkt);
        h2_denom_purity_zdR->Fill(logdR, logz);
        h2_denom_purity_thetaErad->Fill(erad, logtheta);
        h3_denom_purity_ptHFktdR->Fill(logdR, logkt, HF_pt);
        h3_denom_purity_ptHFzdR->Fill(logdR, logz, HF_pt);
      }

      // for (int i = 0; i < ptHFbinsize; i++)
      // {
      //   if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
      //   {
      //     vec_h3_denom_purity_ptktdR[i]->Fill(logdR, logkt, jet_pt);
      //     vec_h3_denom_purity_ptzdR[i]->Fill(logdR, logz, jet_pt);
      //     break;
      //   }
      // }

      for (int i = 0; i < ptHFbinsize; i++)
      {
        if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
        {
          for (int j = 0; j < HFetabinsize; j++)
          {
            int loc = i * HFetabinsize + j;
            if (HF_eta > HFeta_binedges[j] && HF_eta < HFeta_binedges[j + 1])
            {
              vec_h3_denom_purity_ptktdR[loc]->Fill(logdR, logkt, jet_pt);
              vec_h3_denom_purity_ptzdR[loc]->Fill(logdR, logz, jet_pt);
              break;
            }
          }
          break;
        }
      }
      h3_denom_purity_ptktdR->Fill(logdR, logkt, jet_pt);
      h3_denom_purity_etaktdR->Fill(logdR, logkt, jet_eta);
      h3_denom_purity_ptzdR->Fill(logdR, logz, jet_pt);

      h2_denom_purity_ptkt->Fill(logkt, jet_pt);

      // if(kttheta > LambdaQCD){
      h3_denom_purity_ptthetaErad->Fill(erad, logtheta, jet_pt);
      // }

      bool isFake = true;
      for (int j = 0; j < bans.size(); j++)
      {
        if (i == bans[j])
        {
          isFake = false;
        }
      }
      if (isFake)
      {
        // cout<<i <<" is fake"<<endl;
        // if(jet_pt > ptMin && jet_pt < ptMax){
        // response_ktdR->Fake(logdR, logkt);
        // response_zdR->Fake(logdR, logz);
        // response_dR->Fake(logdR);
        // response_kt->Fake(logkt);
        // response_theta->Fake(logtheta);
        // }

        // response_ptktdR->Fake(logdR, logkt, jet_pt);
        // response_ptzdR->Fake(logdR, logz, jet_pt);
        // // if(kttheta > LambdaQCD){
        //   response_ptthetaErad->Fake(erad, logtheta, jet_pt);
        // // }
      }
      else
      {
        if (jet_pt > ptMin && jet_pt < ptMax)
        {
          h1_num_purity_theta->Fill(logtheta);
          h1_num_purity_Erad->Fill(erad);
          h1_num_purity_kT->Fill(logkt);
          h1_num_purity_dR->Fill(logdR);
          h1_num_purity_z->Fill(logz);
          h2_num_purity_ktdR->Fill(logdR, logkt);
          h2_num_purity_zdR->Fill(logdR, logz);
          h2_num_purity_thetaErad->Fill(erad, logtheta);
          h3_num_purity_ptHFktdR->Fill(logdR, logkt, HF_pt);
          h3_num_purity_ptHFzdR->Fill(logdR, logz, HF_pt);
        }
        // for(int i = 0; i < ptHFbinsize; i++){
        //   if(HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i+1]){
        //     vec_h3_num_purity_ptktdR[i]->Fill(logdR, logkt, jet_pt);
        //     vec_h3_num_purity_ptzdR[i]->Fill(logdR, logz, jet_pt);
        //     break;
        //   }
        // }
        for (int i = 0; i < ptHFbinsize; i++)
        {
          if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
          {
            for (int j = 0; j < HFetabinsize; j++)
            {
              int loc = i * HFetabinsize + j;
              if (HF_eta > HFeta_binedges[j] && HF_eta < HFeta_binedges[j + 1])
              {
                vec_h3_num_purity_ptktdR[loc]->Fill(logdR, logkt, jet_pt);
                vec_h3_num_purity_ptzdR[loc]->Fill(logdR, logz, jet_pt);
                break;
              }
            }
            break;
          }
        }
        h3_num_purity_ptktdR->Fill(logdR, logkt, jet_pt);
        h3_num_purity_ptzdR->Fill(logdR, logz, jet_pt);
        h3_num_purity_etaktdR->Fill(logdR, logkt, jet_eta);

        h2_num_purity_ptkt->Fill(logkt, jet_pt);

        // if(kttheta > LambdaQCD){
        h3_num_purity_ptthetaErad->Fill(erad, logtheta, jet_pt);
        // }
      }
    }

    // cout<<"Filling eff"<<endl;
    for (int i = 0; i < tr_kts->size(); i++)
    {
      double logkt = log(tr_kts->at(i));
      double logdR = log(jetradius / tr_dRs->at(i));
      double logz = log(1. / tr_zs->at(i));
      double logtheta = log(1. / tr_thetas->at(i));
      double erad = tr_Erads->at(i);

      if (logkt < -3.)
        continue;
      // double kttheta = tr_ktthetas->at(i);
      if (tr_jet_pt > ptMin && tr_jet_pt < ptMax)
      {
        h1_denom_efficiency_theta->Fill(logtheta);
        h1_denom_efficiency_Erad->Fill(erad);
        h1_denom_efficiency_kT->Fill(logkt);
        h1_denom_efficiency_dR->Fill(logdR);
        h1_denom_efficiency_z->Fill(logz);
        h2_denom_efficiency_ktdR->Fill(logdR, logkt);
        h2_denom_efficiency_zdR->Fill(logdR, logz);
        h2_denom_efficiency_thetaErad->Fill(erad, logtheta);
        h3_denom_efficiency_ptHFktdR->Fill(logdR, logkt, HFmeson.Pt());
        h3_denom_efficiency_ptHFzdR->Fill(logdR, logz, HFmeson.Pt());
      }
      // for(int i = 0; i < ptHFbinsize; i++){
      //     if(HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i+1]){
      //       vec_h3_denom_efficiency_ptktdR[i]->Fill(logdR, logkt, tr_jet_pt);
      //       vec_h3_denom_efficiency_ptzdR[i]->Fill(logdR, logz, tr_jet_pt);
      //       break;
      //     }
      //   }
      for (int i = 0; i < ptHFbinsize; i++)
      {
        if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
        {
          for (int j = 0; j < HFetabinsize; j++)
          {
            int loc = i * HFetabinsize + j;
            if (HF_eta > HFeta_binedges[j] && HF_eta < HFeta_binedges[j + 1])
            {
              vec_h3_denom_efficiency_ptktdR[loc]->Fill(logdR, logkt, tr_jet_pt);
              vec_h3_denom_efficiency_ptzdR[loc]->Fill(logdR, logz, tr_jet_pt);
              break;
            }
          }
          break;
        }
      }
      h3_denom_efficiency_ptktdR->Fill(logdR, logkt, tr_jet_pt);
      h3_denom_efficiency_ptzdR->Fill(logdR, logz, tr_jet_pt);

      h2_denom_efficiency_ptkt->Fill(logkt, tr_jet_pt);

      h3_denom_efficiency_etaktdR->Fill(logdR, logkt, tr_jet_eta);
      // if(kttheta > LambdaQCD){
      h3_denom_efficiency_ptthetaErad->Fill(erad, logtheta, tr_jet_pt);
      // }

      bool isMiss = true;
      for (int j = 0; j < matchedbans.size(); j++)
      {
        if (i == matchedbans[j])
        {
          isMiss = false;
        }
      }

      if (isMiss)
      {

        // cout<<i <<" is Miss"<<endl;
        // if(tr_jet_pt > ptMin && tr_jet_pt < ptMax){
        //   t1_efficiency_dR->Fill(false, logdR);

        // response_ktdR->Miss(logdR, logkt);
        // response_zdR->Miss(logdR, logz);
        // response_dR->Miss(logdR);
        // response_kt->Miss(logkt);
        // response_theta->Miss(logtheta);
        // }

        // response_ptktdR->Miss(logdR, logkt, tr_jet_pt);
        // response_ptzdR->Miss(logdR, logz, tr_jet_pt);
        // // if(kttheta > LambdaQCD){
        // response_ptthetaErad->Miss(erad, logtheta, tr_jet_pt);
        // // }
      }
      else
      {

        if (tr_jet_pt > ptMin && tr_jet_pt < ptMax)
        {
          t1_efficiency_dR->Fill(true, logdR);
          h1_num_efficiency_theta->Fill(logtheta);
          h1_num_efficiency_Erad->Fill(erad);
          h1_num_efficiency_kT->Fill(logkt);
          h1_num_efficiency_dR->Fill(logdR);
          h1_num_efficiency_z->Fill(logz);
          h2_num_efficiency_ktdR->Fill(logdR, logkt);
          h2_num_efficiency_zdR->Fill(logdR, logz);
          h2_num_efficiency_thetaErad->Fill(erad, logtheta);
          h3_num_efficiency_ptHFktdR->Fill(logdR, logkt, HFmeson.Pt());
          h3_num_efficiency_ptHFzdR->Fill(logdR, logz, HFmeson.Pt());
        }

        // for(int i = 0; i < ptHFbinsize; i++){
        //   if(HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i+1]){
        //     vec_h3_num_efficiency_ptktdR[i]->Fill(logdR, logkt, tr_jet_pt);
        //     vec_h3_num_efficiency_ptzdR[i]->Fill(logdR, logz, tr_jet_pt);
        //     break;
        //   }
        // }
        for (int i = 0; i < ptHFbinsize; i++)
        {
          if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
          {
            for (int j = 0; j < HFetabinsize; j++)
            {
              int loc = i * HFetabinsize + j;
              if (HF_eta > HFeta_binedges[j] && HF_eta < HFeta_binedges[j + 1])
              {
                vec_h3_num_efficiency_ptktdR[loc]->Fill(logdR, logkt, tr_jet_pt);
                vec_h3_num_efficiency_ptzdR[loc]->Fill(logdR, logz, tr_jet_pt);
                break;
              }
            }
            break;
          }
        }

        h3_num_efficiency_ptktdR->Fill(logdR, logkt, tr_jet_pt);
        h3_num_efficiency_ptzdR->Fill(logdR, logz, tr_jet_pt);

        h2_num_efficiency_ptkt->Fill(logkt, tr_jet_pt);

        h3_num_efficiency_etaktdR->Fill(logdR, logkt, tr_jet_eta);
        // if(kttheta > LambdaQCD){
        h3_num_efficiency_ptthetaErad->Fill(erad, logtheta, tr_jet_pt);
        // }
      }
    }
  }

  myfile.close();

  cout << h1_denom_purity_dR->GetEntries() << endl;
  cout << h1_num_purity_dR->GetEntries() << endl;

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

  // TH1* h1_fakes_dR = response_dR->Hfakes();
  // TH1* h1_truth_dR = response_dR->Htruth();
  // TH1* h1_meas_dR = response_dR->Hmeasured();
  h2_response->SetName("h2_response");
  response_ptktdR->Write("Roo_response_ptktdR");
  response_ptzdR->Write("Roo_response_ptzdR");
  response_ptHFktdR->Write("Roo_response_ptHFktdR");
  response_ptHFzdR->Write("Roo_response_ptHFzdR");
  response_ptthetaErad->Write("Roo_response_ptthetaErad");
  response_jetpt->Write("Roo_response_jetpt");
  response_HFptjetpt->Write("Roo_response_HFptjetpt");
  response_jetpteta->Write("Roo_response_jetpteta");
  response_ptkt->Write("Roo_response_ptkt");
  response_ktdR->Write("Roo_response_ktdR");
  response_zdR->Write("Roo_response_zdR");
  response_dR->Write("Roo_response_dR");
  response_kt->Write("Roo_response_kt");
  response_theta->Write("Roo_response_theta");
  response_Erad->Write("Roo_response_Erad");

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

  TH1D *h1_purity_HFpt = (TH1D *)h1_num_purity_HFpt->Clone("h1_purity_HFpt");
  h1_purity_HFpt->Divide(h1_num_purity_HFpt, h1_denom_purity_HFpt, 1, 1, "B");

  TH1D *h1_purity_HFpt15 = (TH1D *)h1_num_purity_HFpt15->Clone("h1_purity_HFpt15");
  h1_purity_HFpt15->Divide(h1_num_purity_HFpt15, h1_denom_purity_HFpt15, 1, 1, "B");

  TH1D *h1_purity_jetpt = (TH1D *)h1_num_purity_jetpt->Clone("h1_purity_jetpt");
  h1_purity_jetpt->Divide(h1_num_purity_jetpt, h1_denom_purity_jetpt, 1, 1, "B");

  TH2D *h2_purity_HFpteta = (TH2D *)h2_num_purity_HFpteta->Clone("h2_purity_HFpteta");
  h2_purity_HFpteta->Divide(h2_num_purity_HFpteta, h2_denom_purity_HFpteta, 1, 1, "B");

  TH1D *h1_efficiency_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("h1_efficiency_HFpt");
  h1_efficiency_HFpt->Divide(h1_num_efficiency_HFpt, h1_denom_efficiency_HFpt, 1, 1, "B");

  TH1D *h1_efficiency_HFpt15 = (TH1D *)h1_num_efficiency_HFpt15->Clone("h1_efficiency_HFpt15");
  h1_efficiency_HFpt15->Divide(h1_num_efficiency_HFpt15, h1_denom_efficiency_HFpt15, 1, 1, "B");

  TH1D *h1_efficiency_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("h1_efficiency_jetpt");
  h1_efficiency_jetpt->Divide(h1_num_efficiency_jetpt, h1_denom_efficiency_jetpt, 1, 1, "B");

  TH2D *h2_efficiency_HFptjetpt = (TH2D *)h2_num_efficiency_HFptjetpt->Clone("h2_efficiency_HFptjetpt");
  h2_efficiency_HFptjetpt->Divide(h2_num_efficiency_HFptjetpt, h2_denom_efficiency_HFptjetpt, 1, 1, "B");

  TH2D *h2_purity_HFptjetpt = (TH2D *)h2_num_purity_HFptjetpt->Clone("h2_purity_HFptjetpt");
  h2_purity_HFptjetpt->Divide(h2_num_purity_HFptjetpt, h2_denom_purity_HFptjetpt, 1, 1, "B");

  TH2D *h2_efficiency_jetpteta = (TH2D *)h2_num_efficiency_jetpteta->Clone("h2_efficiency_jetpteta");
  h2_efficiency_jetpteta->Divide(h2_num_efficiency_jetpteta, h2_denom_efficiency_jetpteta, 1, 1, "B");

  TH2D *h2_purity_jetpteta = (TH2D *)h2_num_purity_jetpteta->Clone("h2_purity_jetpteta");
  h2_purity_jetpteta->Divide(h2_num_purity_jetpteta, h2_denom_purity_jetpteta, 1, 1, "B");

  // TEfficiency * h1_purity_jetpt = new TEfficiency(*h1_num_purity_jetpt, *h1_denom_purity_jetpt);
  TEfficiency *h1_purity_eta = new TEfficiency(*h1_num_purity_eta, *h1_denom_purity_eta);
  TEfficiency *h2_purity_ktdR = new TEfficiency(*h2_num_purity_ktdR, *h2_denom_purity_ktdR);
  TEfficiency *h2_purity_zdR = new TEfficiency(*h2_num_purity_zdR, *h2_denom_purity_zdR);
  TEfficiency *h2_purity_thetaErad = new TEfficiency(*h2_num_purity_thetaErad, *h2_denom_purity_thetaErad);
  TEfficiency *h2_efficiency_ktdR = new TEfficiency(*h2_num_efficiency_ktdR, *h2_denom_efficiency_ktdR);
  TEfficiency *h2_efficiency_zdR = new TEfficiency(*h2_num_efficiency_zdR, *h2_denom_efficiency_zdR);
  TEfficiency *h2_efficiency_thetaErad = new TEfficiency(*h2_num_efficiency_thetaErad, *h2_denom_efficiency_thetaErad);

  h3_efficiency_ptktdR->Divide(h3_num_efficiency_ptktdR, h3_denom_efficiency_ptktdR, 1, 1, "B");
  h3_purity_ptktdR->Divide(h3_num_purity_ptktdR, h3_denom_purity_ptktdR, 1, 1, "B");

  h3_efficiency_etaktdR->Divide(h3_num_efficiency_etaktdR, h3_denom_efficiency_etaktdR, 1, 1, "B");
  h3_purity_etaktdR->Divide(h3_num_purity_etaktdR, h3_denom_purity_etaktdR, 1, 1, "B");

  h3_efficiency_ptzdR->Divide(h3_num_efficiency_ptzdR, h3_denom_efficiency_ptzdR, 1, 1, "B");
  h3_purity_ptzdR->Divide(h3_num_purity_ptzdR, h3_denom_purity_ptzdR, 1, 1, "B");

  h3_efficiency_ptthetaErad->Divide(h3_num_efficiency_ptthetaErad, h3_denom_efficiency_ptthetaErad, 1, 1, "B");
  h3_purity_ptthetaErad->Divide(h3_num_purity_ptthetaErad, h3_denom_purity_ptthetaErad, 1, 1, "B");

  h3_efficiency_ptHFktdR->Divide(h3_num_efficiency_ptHFktdR, h3_denom_efficiency_ptHFktdR, 1, 1, "B");
  h3_purity_ptHFktdR->Divide(h3_num_purity_ptHFktdR, h3_denom_purity_ptHFktdR, 1, 1, "B");

  h3_efficiency_ptHFzdR->Divide(h3_num_efficiency_ptHFzdR, h3_denom_efficiency_ptHFzdR, 1, 1, "B");
  h3_purity_ptHFzdR->Divide(h3_num_purity_ptHFzdR, h3_denom_purity_ptHFzdR, 1, 1, "B");

  h2_efficiency_ptkt->Divide(h2_num_efficiency_ptkt, h2_denom_efficiency_ptkt, 1, 1, "B");
  h2_purity_ptkt->Divide(h2_num_purity_ptkt, h2_denom_purity_ptkt, 1, 1, "B");

  for (int i = 0; i < ptHFbinsize; i++)
  {
    for (int j = 0; j < HFetabinsize; j++)
    {
      int loc = i * HFetabinsize + j;
      vec_h3_efficiency_ptktdR[loc]->Divide(vec_h3_num_efficiency_ptktdR[loc], vec_h3_denom_efficiency_ptktdR[loc], 1, 1, "B");
      vec_h3_purity_ptktdR[loc]->Divide(vec_h3_num_purity_ptktdR[loc], vec_h3_denom_purity_ptktdR[loc], 1, 1, "B");
      vec_h3_efficiency_ptktdR[loc]->Write(Form("h3_efficiency_ptktdR%d%d", i, j));
      vec_h3_purity_ptktdR[loc]->Write(Form("h3_purity_ptktdR%d%d", i, j));
      vec_response_ptktdR[loc]->Write(Form("h3_response_ptktdR%d%d", i, j));

      cout << vec_h3_purity_ptktdR[loc]->Integral() << endl;

      vec_h3_efficiency_ptzdR[loc]->Divide(vec_h3_num_efficiency_ptzdR[loc], vec_h3_denom_efficiency_ptzdR[loc], 1, 1, "B");
      vec_h3_purity_ptzdR[loc]->Divide(vec_h3_num_purity_ptzdR[loc], vec_h3_denom_purity_ptzdR[loc], 1, 1, "B");
      vec_h3_efficiency_ptzdR[loc]->Write(Form("h3_efficiency_ptzdR%d%d", i, j));
      vec_h3_purity_ptzdR[loc]->Write(Form("h3_purity_ptzdR%d%d", i, j));
      vec_response_ptzdR[loc]->Write(Form("h3_response_ptzdR%d%d", i, j));
    }
  }
  // f->WriteObject(&vec_h3_efficiency_ptktdR, "vec_h3_efficiency_ptktdR");
  // f->WriteObject(&vec_h3_purity_ptktdR, "vec_h3_purity_ptktdR");
  // f->WriteObject(&vec_response_ptktdR, "vec_response_ptktdR");

  h2_purity_ktdR->Write("purity_ktdR");
  h2_purity_zdR->Write("purity_zdR");
  h2_purity_thetaErad->Write("purity_thetaErad");
  h1_purity_dR->Write("purity_dR");
  h1_purity_kT->Write("purity_kt");
  h1_purity_theta->Write("purity_theta");
  h1_purity_Erad->Write("purity_Erad");
  h1_purity_z->Write("purity_z");
  h1_purity_jetpt->Write("purity_jetpt");
  h1_purity_HFpt->Write("purity_HFpt");
  h1_purity_HFpt15->Write("purity_HFpt15");
  h1_efficiency_HFpt->Write("efficiency_HFpt");
  h1_efficiency_HFpt15->Write("efficiency_HFpt15");
  h2_efficiency_HFptjetpt->Write("efficiency_HFptjetpt");
  h2_purity_HFptjetpt->Write("purity_HFptjetpt");
  h2_efficiency_jetpteta->Write("efficiency_jetpteta");
  h2_purity_jetpteta->Write("purity_jetpteta");
  h1_efficiency_jetpt->Write("efficiency_jetpt");
  h1_purity_eta->Write("purity_jeteta");

  h2_purity_HFpteta->Write("purity_HFpteta");

  h2_efficiency_ktdR->Write("efficiency_ktdR");
  h2_efficiency_zdR->Write("efficiency_zdR");
  h2_efficiency_thetaErad->Write("efficiency_thetaErad");
  h1_efficiency_dR->Write("efficiency_dR");
  h1_efficiency_z->Write("efficiency_z");
  h1_efficiency_theta->Write("efficiency_theta");
  h1_efficiency_kT->Write("efficiency_kt");
  h1_efficiency_Erad->Write("efficiency_Erad");

  h2_purity_ptkt->Write("purity_ptkt");
  h2_efficiency_ptkt->Write("efficiency_ptkt");

  h3_purity_ptktdR->Write("purity_ptktdR");
  h3_efficiency_ptktdR->Write("efficiency_ptktdR");

  h3_purity_etaktdR->Write("purity_etaktdR");
  h3_efficiency_etaktdR->Write("efficiency_etaktdR");

  h3_purity_ptzdR->Write("purity_ptzdR");
  h3_efficiency_ptzdR->Write("efficiency_ptzdR");

  h3_purity_ptthetaErad->Write("purity_ptthetaErad");
  h3_efficiency_ptthetaErad->Write("efficiency_ptthetaErad");

  h3_purity_ptHFktdR->Write("purity_ptHFktdR");
  h3_efficiency_ptHFktdR->Write("efficiency_ptHFktdR");

  h3_purity_ptHFzdR->Write("purity_ptHFzdR");
  h3_efficiency_ptHFzdR->Write("efficiency_ptHFzdR");

  /////////////////////////////////

  TF1 *f_eff1 = new TF1("f_eff1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
  TF1 *f_eff2 = new TF1("f_eff2", "[0]*tanh([1]*([3] - x))+[2]", 25, 100);
  TF1 *f_eff15 = new TF1("f_eff15", "[0]*tanh([1]*([3] - x))+[2]", 2, 20);
  f_eff1->SetParameters(0.2, 0.1, 0.2, 6.4);
  f_eff15->SetParameters(0.2, 0.1, 0.2, 6.4);
  f_eff2->SetParameters(0.2, 0.1, 0.2, 100);
  f_eff2->SetParLimits(3, 80, 200);
  h1_efficiency_HFpt->Fit("f_eff1", "E", "SAME", 2, 25);
  h1_efficiency_HFpt15->Fit("f_eff15", "E", "SAME", 2, 25);
  h1_efficiency_HFpt->Fit("f_eff2", "E", "SAME", 25, 100);

  f_eff1->Write("f_eff1");
  f_eff15->Write("f_eff15");
  f_eff2->Write("f_eff2");

  TF1 *f_pur1 = new TF1("f_pur1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
  TF1 *f_pur15 = new TF1("f_pur15", "[0]*tanh([1]*(x-[3]))+[2]", 2, 20);
  f_pur1->SetParameters(0.05, 0.4, 0.95, 16);
  f_pur1->SetParLimits(0, 0.01, 0.1);
  f_pur1->SetParLimits(2, 0.9, 0.99);

  f_pur15->SetParameters(0.3, 0.4, 0.70, 16);
  f_pur15->SetParLimits(0, 0.25, 0.35);
  f_pur15->SetParLimits(2, 0.65, 0.75);

  h1_purity_HFpt->Fit("f_pur1", "E", "SAME", 2, 100);
  f_pur1->Write("f_pur");

  h1_purity_HFpt15->Fit("f_pur15", "E", "SAME", 2, 20);
  f_pur15->Write("f_pur15");
  cout << event_counter << " events processed" << endl;


  /////////////////////////////////////////////////////

  TH2D* h2_HFptjetpt_true = (TH2D*) h2_denom_efficiency_HFptjetpt->Clone("h2_HFptjetpt_true");
  TH2D* h2_HFptjetpt_reco = (TH2D*) h2_denom_purity_HFptjetpt->Clone("h2_HFptjetpt_reco");
  h2_HFptjetpt_reco->Multiply(h2_purity_HFptjetpt);
  RooUnfoldBayes unfold_HFptjetpt(response_HFptjetpt, h2_HFptjetpt_reco, 4);
  h2_HFptjetpt_reco = (TH2D *)unfold_HFptjetpt.Hreco();
  h2_HFptjetpt_reco->Divide(h2_efficiency_HFptjetpt);
  TH2D* h2_HFptjetpt_corr = (TH2D*) h2_HFptjetpt_reco->Clone("h2_HFptjetpt_corr");
  h2_HFptjetpt_corr->Divide(h2_HFptjetpt_true);
  h2_HFptjetpt_corr->Write("h2_HFptjetpt_corr");
  ////////////////////////////////////////////////////

  // gROOT->ProcessLine(".L $LUND/lhcbStyle.C");
  // gROOT->ProcessLine(".x $LUND/lhcbStyle.C");
  // gROOT->ProcessLine(".x lhcbStyle2D.C");
  //---- paint setup...
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

  ccan[ican]->cd(5);
  // h2_response_ptktdR->GetZaxis()->SetRange(2,5);
  gPad->SetLogz();
  h2_response_ptktdR->Draw("COLZ");
  ccan[ican]->cd(6);
  gPad->SetLogy();
  stack_theta_resolution->Draw("nostack");
  for (int i = 0; i < MaxEmissions; i++)
  {
    h1_theta_resolution_vec[i]->SetLineColor(1 + i);
    // h1_theta_resolution_vec[i]->Fit()
  }

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
  gPad->SetLogz();
  h2_truthreco_theta->SetStats(0);
  h2_truthreco_theta->SetXTitle("MCTrue ln(1/#theta)");
  h2_truthreco_theta->SetYTitle("MCReco ln(1/#theta)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_theta->Draw("COLZ");
  Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.drawLatex(0.7, 0.8, "No cuts");

  ccan[ican]->cd(2);
  gPad->SetLogz();
  h2_truthreco_kT->SetStats(0);
  h2_truthreco_kT->SetXTitle("MCTrue ln(kT)");
  h2_truthreco_kT->SetYTitle("MCReco ln(kT)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_kT->Draw("COLZ");
  ccan[ican]->cd(3);
  gPad->SetLogz();
  h2_truthreco_z->SetStats(0);
  h2_truthreco_z->SetXTitle("MCTrue ln(1/z)");
  h2_truthreco_z->SetYTitle("MCReco ln(1/z)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_z->Draw("COLZ");
  ccan[ican]->cd(4);
  gPad->SetLogz();
  h2_truthreco_dR->SetStats(0);
  h2_truthreco_dR->SetXTitle("MCTrue ln(#Delta R)");
  h2_truthreco_dR->SetYTitle("MCReco ln(#Delta R)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h2_truthreco_dR->Draw("COLZ");

  ccan[ican]->cd(5);

  ccan[ican]->cd(6);

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

  t1_efficiency_dR->Draw("P SAME");

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

  h1_purity_jetpt->SetMarkerColor(kRed);
  h1_purity_jetpt->SetMarkerStyle(21);
  h1_purity_jetpt->Draw("P E same");
  h1_purity_jetpt->SetTitle("; Jet pT; HF Jet Purity");
  h1_purity_jetpt->SetMinimum(0.);
  h1_purity_jetpt->SetMaximum(1.05);

  h1_efficiency_jetpt->SetMarkerColor(kBlue);
  h1_efficiency_jetpt->SetMarkerStyle(22);
  h1_efficiency_jetpt->Draw("P E same");
  // h1_purity_jetpt->SetXTitle("E_{radiator}");
  // h1_purity_jetpt->SetYTitle("Counts");
  // gPad->Update();
  // auto graphpt3 = h1_purity_jetpt->GetPaintedGraph();
  // graphpt3->SetMinimum(0);
  // graphpt3->SetMaximum(1);
  // gPad->Update();
  // h1_purity_jetpt->SetMinimum(0.0);
  ccan[ican]->cd(2);
  h1_purity_eta->SetMarkerColor(kRed);
  h1_purity_eta->SetMarkerStyle(21);
  h1_purity_eta->Draw("AP same");
  h1_purity_eta->SetTitle("; Jet #eta; HF Jet Purity");
  // h1_purity_eta->SetXTitle("E_{radiator}");
  // h1_purity_eta->SetYTitle("Counts");
  gPad->Update();
  auto grapheta4 = h1_purity_eta->GetPaintedGraph();
  grapheta4->SetMinimum(0);
  grapheta4->SetMaximum(1);
  gPad->Update();

  ccan[ican]->cd(3);

  h1_purity_HFpt->SetMarkerColor(kRed);
  h1_purity_HFpt->SetMarkerStyle(21);
  h1_purity_HFpt->Draw("P E same");
  h1_purity_HFpt->SetTitle("; HF pT; Purity or Efficiency");
  h1_purity_HFpt->SetMinimum(0.);
  h1_purity_HFpt->SetMaximum(1.05);

  h1_purity_HFpt15->SetMarkerColor(kGreen);
  h1_purity_HFpt15->SetMarkerStyle(21);
  h1_purity_HFpt15->Draw("P E same");

  h1_efficiency_HFpt->SetMarkerColor(kBlue);
  h1_efficiency_HFpt->SetMarkerStyle(22);
  h1_efficiency_HFpt->Draw("P E same");

  h1_efficiency_HFpt15->SetMarkerColor(kMagenta);
  h1_efficiency_HFpt15->SetMarkerStyle(22);
  h1_efficiency_HFpt15->Draw("P E same");
  // h1_efficiency_HFpt->SetTitle("; HF pT; Purity");

  f_pur1->Draw("SAME");
  f_pur15->Draw("SAME");
  f_eff1->Draw("SAME");
  f_eff15->Draw("SAME");

  ccan[ican]->cd(4);

  h2_efficiency_HFptjetpt->Draw("COLZ TEXT");
  // h2_efficiency_HFptjetpt->SetMinimum(0.);
  // h2_efficiency_HFptjetpt->SetMaximum(1.0);

  ccan[ican]->cd(5);

  h2_HFptjetpt_corr->Draw("COLZ TEXT");

  // h2_purity_HFpteta->Draw("COLZ");
  // h2_purity_HFpteta->SetTitle("; HF p_{T}; HF #eta; HF Jet Purity");
  // h2_purity_HFpteta->SetMinimum(0.);
  // h2_efficiency_HFpteta->SetMaximum(1.);

  ccan[ican]->cd(6);
  for(int i = 0; i < customptbinsize; i++){
    TH1D* h1_temp = (TH1D*) h2_efficiency_HFptjetpt->ProjectionX(Form("htemp%d", i), i+1, i+1);
    TH1D* h1_temp_pur = (TH1D*) h2_purity_HFptjetpt->ProjectionX(Form("htemp_pur%d", i), i+1, i+1);

    h1_temp_pur->SetMarkerStyle(i+20);
    h1_temp_pur->SetMarkerColor(i+1);
    h1_temp_pur->SetLineColor(i+1);
    h1_temp_pur->Draw("P E SAME");
    h1_temp_pur->SetMinimum(0.);
    h1_temp_pur->SetMaximum(1.05);

    h1_temp->SetMarkerStyle(i+20);
    h1_temp->SetMarkerColor(i+1);
    h1_temp->SetLineColor(i+1);
    h1_temp->Draw("P E SAME");
  }
  

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
  // h1_purity_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(2);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_num_purity_ktdR->Draw("COLZ");
  h2_num_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_purity_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(3);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_denom_purity_ktdR->Draw("COLZ");
  h2_denom_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_purity_eta->SetXTitle("E_{radiator}");
  ccan[ican]->cd(4);
  // h2_purity_ktdR->SetMarkerColor(kBlue);
  // h2_purity_ktdR->SetMarkerStyle(21);
  h2_purity_zdR->Draw("COLZ");
  h2_purity_zdR->SetTitle("; ln(R/#Delta R); ln(1/z)");
  // h2_purity_ktdR->SetMaximum(1.0);
  // h2_purity_ktdR->SetMinimum(0.0);
  // h1_purity_eta->SetXTitle("E_{radiator}");

  //  ccan[ican]->cd(5);
  //  auto legend00 = new TLegend(0.6,0.2,0.8,0.4);
  // legend00->SetBorderSize(0);
  // legend00->SetFillStyle(0);
  // legend00->SetFillColor(3);
  //  THStack * stack_pur = new THStack("stack_pur_kt", "stack");
  //  for(int i = 0; i < ptbinsize; i++){
  //   TH1D* h1 = (TH1D*) h2_purity_ptkt->ProjectionX(Form("pur%d_x", i), i+1, i+1);
  //   h1->SetLineColor(i+1);
  //   stack_pur->Add(h1);
  //   legend00->AddEntry(h1, Form("[%.0f, %.0f]", pt_binedges[i], pt_binedges[i+1]));
  //  }
  //  stack_pur->Draw("PLC NOSTACK");
  //  legend00->Draw("SAME");

  //  ccan[ican]->cd(6);
  //  THStack * stack_eff = new THStack("stack_eff_kt", "stack");
  //  for(int i = 0; i < ptbinsize; i++){
  //   TH1D* h1 = (TH1D*) h2_efficiency_ptkt->ProjectionX(Form("eff%d_x", i), i+1, i+1);
  //   h1->SetLineColor(i+1);
  //   stack_eff->Add(h1);
  //  }
  //  stack_eff->Draw("PLC NOSTACK");

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
  // h1_efficiency_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(2);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_num_efficiency_ktdR->Draw("COLZ");
  h2_num_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_efficiency_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(3);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_denom_efficiency_ktdR->Draw("COLZ");
  h2_denom_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
  // h1_efficiency_eta->SetXTitle("E_{radiator}");
  ccan[ican]->cd(4);
  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
  // h2_efficiency_ktdR->SetMarkerStyle(21);
  h2_efficiency_zdR->Draw("COLZ");
  h2_efficiency_zdR->SetTitle("; ln(R/#Delta R); ln(1/z)");
  // h2_efficiency_ktdR->SetMaximum(1.0);
  // h2_efficiency_ktdR->SetMinimum(0.0);
  // h1_purity_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(5);
  //  THStack * stack_pur_z = new THStack("stack_pur_z", "stack_pur_z");
  //  for(int i = 0; i < ptbinsize; i++){
  //   TH1D* h1 = (TH1D*) h2_purity_ptz->ProjectionX(Form("pur_z%d_x", i), i+1, i+1);
  //   h1->SetLineColor(i+1);
  //   stack_pur_z->Add(h1);
  //  }
  //  stack_pur_z->Draw("PLC NOSTACK");
  //  legend00->Draw("SAME");

  //  ccan[ican]->cd(6);
  //  THStack * stack_eff_z = new THStack("stack_eff_z", "stack_eff_z");
  //  for(int i = 0; i < ptbinsize; i++){
  //   TH1D* h1 = (TH1D*) h2_efficiency_ptz->ProjectionX(Form("eff_z%d_x", i), i+1, i+1);
  //   h1->SetLineColor(i+1);
  //   stack_eff_z->Add(h1);
  //  }
  //  stack_eff_z->Draw("PLC NOSTACK");

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
  // h1_efficiency_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(2);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_num_efficiency_thetaErad->Draw("COLZ");
  h2_num_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h1_efficiency_eta->SetXTitle("E_{radiator}");

  ccan[ican]->cd(3);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_denom_efficiency_thetaErad->Draw("COLZ");
  h2_denom_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h1_efficiency_eta->SetXTitle("E_{radiator}");
  ccan[ican]->cd(4);
  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
  // h2_efficiency_thetaErad->SetMarkerStyle(21);
  h2_purity_thetaErad->Draw("COLZ");
  h2_purity_thetaErad->SetTitle("; ln(1/#theta); Erad");
  // h2_efficiency_thetaErad->SetMaximum(1.0);
  // h2_efficiency_thetaErad->SetMinimum(0.0);
  // h1_purity_eta->SetXTitle("E_{radiator}");

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

  f->Write();
  f->Close();

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
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
  cout << "Num of Reco B jets = " << NumBjets << endl;
  cout << "Num of True B jets = " << NumTrueBjets << endl;

  // CAJetAlgo(std::string filename);

  // loop(ptMax, Nsubsets);
  // write(ptMax, Nsubsets);
}
//
