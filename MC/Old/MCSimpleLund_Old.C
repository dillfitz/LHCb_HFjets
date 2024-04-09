

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

// #include "HFjetLuC"

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

void MCSimpleLund(int NumEvts = 10000, int dataset = 1510,
                  bool chargedJetCut_user = false,
                  bool SubtractGS = false)
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
  int HF_pdgcode = -999;

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
  TString str_GS = "";

  TString str_charged = "";

  if (SubtractGS)
    str_GS = "_GSsub";

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
  extension = str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_GS + str_Mag + str_flavor + Form("_%d", dataset);

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

  // TH2D *h2_lundplane_b = new TH2D("B_LundPlane", "B-meson Lund Plane", 50, 0, 8, 50, -8, 8);
  // TH2D *h2_lundplane_c = new TH2D("D_LundPlane", "D-meson Lund Plane", 50, 0, 8, 50, -8, 8);
  // TH2D *h2_lundplane_inc = new TH2D("L_LundPlane", "Light Lund Plane", 50, 0, 8, 50, -8, 8);

  // for(int i = 0; i < ktbinsize+1; i++){
  //   kt_binedges[i] = kT_min + i*(kT_max - kT_min)/ktbinsize;
  //   dR_binedges[i] = dR_min + i * (dR_max - dR_min)/dRbinsize;
  //   z_binedges[i] = z_min + i*(z_max - z_min)/ktbinsize;
  // }

  vector<TH3D *> vec_h3_ptktdR, vec_h3_ptzdR;
  for (int i = 0; i < ptHFbinsize; i++)
  {
    for (int j = 0; j < HFetabinsize; j++)
    {
      TH3D *h3_ptktdR_tmp = new TH3D(Form("ptktdR%d%d", i, j), "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
      vec_h3_ptktdR.push_back(h3_ptktdR_tmp);

      TH3D *h3_ptzdR_tmp = new TH3D(Form("ptzdR%d%d", i, j), "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);
      vec_h3_ptzdR.push_back(h3_ptzdR_tmp);
    }
  }

  TH3D *h3_ptktdR = new TH3D("ptktdR", "", dRbinsize, dR_binedges, ktbinsize, kt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_ptzdR = new TH3D("ptzdR", "", dRbinsize, dR_binedges, zbinsize, z_binedges, ptbinsize, pt_binedges);

  TH2D *h2_lundplane = new TH2D("Lund_Plane", "Lund Jet Plane", 80, 2, 8, 80, -8, 4);
  TH2D *h2_thetaErad = new TH2D("Theta_Erad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges);
  TH2D *h2_dRErad = new TH2D("dR_Erad", "", h2_erad_bins, h2_erad_low, h2_erad_high, tr_dRbinsize, tr_dR_binedges);
  TH2D *h2_ktdR = new TH2D("kT_dR", "", tr_dRbinsize, tr_dR_binedges, tr_ktbinsize, tr_kt_binedges);
  TH2D *h2_zdR = new TH2D("z_dR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges);

  TH2D *h2_meas_lundplane = new TH2D("meas_Lund_Plane", "Lund Jet Plane", 80, 2, 8, 80, -8, 4);
  TH2D *h2_meas_thetaErad = new TH2D("meas_Theta_Erad", "", tr_Eradbinsize, tr_Erad_binedges, tr_thetabinsize, tr_theta_binedges);
  TH2D *h2_meas_dRErad = new TH2D("meas_dR_Erad", "", h2_erad_bins, h2_erad_low, h2_erad_high, 80, 0.5, 6);
  TH2D *h2_meas_ktdR = new TH2D("meas_kT_dR", "", 80, 0.5, 6, 80, -8, 4);
  TH2D *h2_meas_zdR = new TH2D("meas_z_dR", "", tr_dRbinsize, tr_dR_binedges, tr_zbinsize, tr_z_binedges);

  TH2D *h2_truthreco_theta = new TH2D("truthreco_theta", "", tr_thetabinsize, tr_theta_binedges, tr_thetabinsize, tr_theta_binedges);
  TH2D *h2_truthreco_kT = new TH2D("truthreco_kT", "", tr_ktbinsize, tr_kt_binedges, tr_ktbinsize, tr_kt_binedges);
  TH2D *h2_truthreco_Erad = new TH2D("truthreco_Erad", "", tr_Eradbinsize, tr_Erad_binedges, tr_Eradbinsize, tr_Erad_binedges);
  TH2D *h2_truthreco_dR = new TH2D("truthreco_dR", "", tr_dRbinsize, tr_dR_binedges, tr_dRbinsize, tr_dR_binedges);

  // TH1D *h1_R_b = new TH1D("B_R_Observable", "Beauty R Observable", 20, 1, 8);
  // TH1D *h1_R_inc = new TH1D("L_R_Observable", "Light R Observable", 20, 1, 8);
  TH1D *h1_dR = new TH1D("dR", "", tr_dRbinsize, tr_dR_binedges);
  TH1D *h1_meas_dR = new TH1D("meas_dR", "", tr_dRbinsize, tr_dR_binedges);
  TH1D *h1_erad = new TH1D("E_rad", "E Radiator", h2_erad_bins, h2_erad_low, h2_erad_high);
  TH1D *h1_meas_erad = new TH1D("meas_E_rad", "E Radiator", h2_erad_bins, h2_erad_low, h2_erad_high);
  TH1D *h1_z = new TH1D("z", "", tr_zbinsize, tr_z_binedges);
  TH1D *h1_meas_z = new TH1D("meas_z", "", tr_zbinsize, tr_z_binedges);
  TH1D *h1_kt = new TH1D("kt", "", tr_ktbinsize, tr_kt_binedges);
  TH1D *h1_meas_kt = new TH1D("meas_kt", "", tr_ktbinsize, tr_kt_binedges);
  TH1D *h1_theta = new TH1D("theta", "", tr_thetabinsize, tr_theta_binedges);
  TH1D *h1_meas_theta = new TH1D("meas_theta", "", tr_thetabinsize, tr_theta_binedges);

  TH1D *h1_frag_jt = new TH1D("frag_jt", "", 30, 0, 12);
  TH1D *h1_frag_z = new TH1D("frag_z", "", 60, 0, 1.05);
  TH1D *h1_frag_r = new TH1D("frag_r", "", 30, 0, 1);

  TH1D *h1_frag_jt_gluon = new TH1D("frag_jt_gluon", "", 30, 0, 12);
  TH1D *h1_frag_z_gluon = new TH1D("frag_z_gluon", "", 60, 0, 1.05);
  TH1D *h1_frag_r_gluon = new TH1D("frag_r_gluon", "", 30, 0, 1);

  TH1D *h1_jet_flav = new TH1D("Jet_Flav", "", 7, -0.5, 6.5);
  TH1D *h1_jet_pt = new TH1D("Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_jet_eta = new TH1D("Jet_eta", "", 12, etaMin, etaMax);
  TH1D *h1_jet_rap = new TH1D("Jet_rap", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi = new TH1D("Jet_phi", "", 20, -3.14, 3.14);
  TH1D *h1_jet_ptbalance = new TH1D("jet_ptbalance", "", 20, 0, 2);

  TH2D *h2_jetpteta = new TH2D("h2_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);

  TH1D *h1_meas_jet_pt = new TH1D("meas_Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_meas_jet_eta = new TH1D("meas_Jet_eta", "", 12, etaMin, etaMax);
  TH1D *h1_meas_jet_rap = new TH1D("meas_Jet_rap", "", 12, etaMin, etaMax);
  TH1D *h1_meas_jet_phi = new TH1D("meas_Jet_phi", "", 20, -3.14, 3.14);

  TH1D *h1_jet_pt_noghost = new TH1D("Jet_pT_noghost", "", 50, ptMin, ptMax);
  TH1D *h1_jet_eta_noghost = new TH1D("Jet_eta_noghost", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi_noghost = new TH1D("Jet_phi_noghost", "", 20, -3.14, 3.14);

  TH1D *h1_Jpsi_rap = new TH1D("Jpsi_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_Jpsi_pt = new TH1D("Jpsi_pT", "", 50, 0, 100);
  TH1D *h1_Jpsi_phi = new TH1D("Jpsi_phi", "", 20, -3.14, 3.14);
  TH1D *h1_Jpsi_mass = new TH1D("Jpsi_mass", "", 30, 3.1 - 0.1, 3.1 + 0.1);

  TH1D *h1_meas_Jpsi_rap = new TH1D("meas_Jpsi_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_meas_Jpsi_pt = new TH1D("meas_Jpsi_pT", "", 50, 0, 100);
  TH1D *h1_meas_Jpsi_phi = new TH1D("meas_Jpsi_phi", "", 20, -3.14, 3.14);
  TH1D *h1_meas_Jpsi_mass = new TH1D("meas_Jpsi_mass", "", 30, 3.1 - 0.1, 3.1 + 0.1);

  TH1D *h1_HF_rap = new TH1D("HF_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_HF_pt = new TH1D("HF_pT", "", 50, 0, 100);
  TH1D *h1_HF_phi = new TH1D("HF_phi", "", 20, -3.14, 3.14);
  TH1D *h1_HF_mass = new TH1D("HF_mass", "", 30, 5.279 - 0.3, 5.279 + 0.3);
  TH1D *h1_HFjet_ptbalance = new TH1D("HFjet_ptbalance", "", 20, 0, 2);

  TH1D *h1_HFpt = new TH1D("h1_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH2D *h2_HFptjetpt = new TH2D("h2_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);

  TH1D *h1_HF_measeta = new TH1D("HF_measeta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_HF_measpt = new TH1D("HF_measpT", "", 50, 0, 80);
  TH1D *h1_HF_measphi = new TH1D("HF_measphi", "", 20, -3.14, 3.14);

  TH1D *h1_Dtr_Eta = new TH1D("Dtr_Eta", "Dtr #eta", 50, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_dtr_phi = new TH1D("Dtr_phi", "Dtr #phi", 50, -3.14, 3.14);
  TH1D *h1_dtr_pT = new TH1D("Dtr_pT", "Dtr pT", 50, 0, 10);
  TH1D *h1_dtr_p = new TH1D("Dtr_p", "Dtr p", 50, 0, 150);
  TH1D *h1_keys = new TH1D("Keys", "Keys", 100, 0, 100);
  TH1D *h1_hfdtrs_e_diff = new TH1D("HFDtrsEDiff", "HFDtrsEDiff", 40, -100, 100);
  TH1D *h1_HFHadronMass = new TH1D("HFHadronMass", "HFHadronMass", 100, 60, 120);
  TH1D *h1_HF_jet_dR = new TH1D("HF_jet_dR", "", 24, 0, 4.);
  TH1D *h1_HF_jet_truedR = new TH1D("HF_jet_truedR", "", 24, 0, 4.);
  TH1D *h1_HFdtr1_mass = new TH1D("HFdtr1mass", "", 100, 1, 7);
  TH1D *h1_recoHFHadronMass = new TH1D("recoHFHadronMass", "recoHFHadronMass", 40, 0, 15);
  TH1D *h1_nsplittings = new TH1D("nSplittings", "nSplittings", 15, -0.5, 14.5);
  TH1D *h1_ptHF = new TH1D("ptHF", "pT_{HF}", 30, 0, 25);
  TH1D *h1_probNNghost = new TH1D("probNNghost", "probNNghost", 20, 0, 1);
  TH1D *h1_nJetDtrs_noghost = new TH1D("nJetDtrs_noghost", "nJetDtrs_noghost", 40, -0.5, 39.5);
  TH1D *h1_nJetDtrs_noghost_gluon = new TH1D("nJetDtrs_noghost_gluon", "nJetDtrs_noghost", 40, -0.5, 39.5);
  TH1F *h_nJetDaughters = new TH1F("h_nJetDaughters", "Number of jet daughters", 40, -0.5, 39.5);

  TH2D *HFmesonyphi_h = new TH2D("HFmesonyphi_h", ";#phi [rad]; y",
                                 100, -1 * TMath::Pi(), TMath::Pi(), 50, 1, 5);
  TH2D *HFjetetaphi_h = new TH2D("truejetetaphi_h", ";#phi [rad]; #eta",
                                 100, -1 * TMath::Pi(), TMath::Pi(), 50, 1, 5);
  TH1D *HFjetpt_h = new TH1D("truejetpt_h", ";p_{T}^{jet,MC} [GeV]", 50, 0, 200);
  TH1D *zmass = new TH1D("zmass", ";M_{#mu#mu} [GeV]", 150, 0, 150);
  TH1D *truedphi_h = new TH1D("truedphi_h", ";#Delta#phi [rad]", 50, 0, 3.14159);
  TH1D *truexj_h = new TH1D("truexj_h", "x_{J}", 50, 0, 2);
  TH1D *Zpt_h = new TH1D("Zpt_h", "p_{T}^{Z} [GeV]", 50, 0, 200);
  TH1D *truedy_h = new TH1D("truedy_h", "#Deltay", 50, -3, 3);
  // TH1D* truedtrp_h = new TH1D("truedtrp_h",";p [GeV]",npbins,thispbins);
  // TH1D* truedtrpt_h = new TH1D("truedtrpt_h",";p_{T} [GeV]",npbins,thispbins);
  TH1D *truenconst_h = new TH1D("truenconst_h", ";N_{const}^{chg}", 40, -0.5, 39.5);

  for (int i = 0; i < NumHists; i++)
  {
    TH1D *h = new TH1D(Form("Theta%d", i), "Theta Distribution", 20, 0, 0.15);
    TH1D *h_meas_ = new TH1D(Form("meas_Theta%d", i), "Theta Distribution", 20, 0, 0.15);
    TH1D *h1 = new TH1D(Form("R%d", i), "R Observable", R_bins, R_min, R_max);
    TH1D *h1_meas_ = new TH1D(Form("meas_R%d", i), "R Observable", R_bins, R_min, R_max);
    std::vector<TH1D *> vec1;
    // for(int j = 0; j < NumRbins; j++){
    //   TH1D *h1_vec = new TH1D(Form("R%d%d",i,j),"R Observable",RbinsArr[j],R_min,R_max);
    //   vec1.push_back(h1_vec);
    // }
    // h1_Rratios_vec.push_back(vec1);

    // TH2D *h2 = new TH2D(Form("truthVsreco_theta%d", i), "truthVsreco Theta", 50, 0, 8);
    h1_thetas.push_back(h);
    h1_meas_thetas.push_back(h_meas_);
    h1_Rratios.push_back(h1);
    h1_meas_Rratios.push_back(h1_meas_);
    // h2_recomatch_theta.push_back(h2);
  }
  THStack *stack = new THStack("hs", "");
  THStack *stack_R = new THStack("hs_R", "");
  std::vector<THStack *> stack_R_vec;

  f1_theta_Erad->SetParameter(0, mass_num);
  f1_kt_Erad->SetParameter(0, 2 * LambdaQCD);

  JetDefinition jet_def(cambridge_algorithm, jetradius);
  PseudoJet dtr1, dtr2;

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //
  unsigned long long last_eventNum = 0;
  double last_jetpT = 0.;
  int event_counter = 0;

  vector<double> *thetas = 0;
  vector<double> *meas_thetas = 0;
  vector<double> *ktthetas(0), *meas_ktthetas(0);
  vector<double> *dRs(0), *meas_dRs(0);
  vector<double> *Erads(0), *meas_Erads(0);
  vector<double> *kts = 0;
  vector<double> *meas_kts = 0;
  vector<double> *raps(0), *meas_raps(0);
  vector<double> *phis(0), *meas_phis(0);
  vector<double> *zs(0), *meas_zs(0);

  double jet_pt, jet_eta, meas_jet_pt, meas_jet_eta;
  double jet_rap, meas_jet_rap;
  double jet_px, jet_py, jet_pz, jet_e;
  double Z_px, Z_py, Z_pz, Z_e;
  double mup_px, mup_py, mup_pz, mup_e;
  double mum_px, mum_py, mum_pz, mum_e;
  double K_px, K_py, K_pz, K_e;
  double HF_px, HF_py, HF_pz, HF_e, HF_pt;

  double meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e;
  double meas_mup_px, meas_mup_py, meas_mup_pz, meas_mup_e;
  double meas_mum_px, meas_mum_py, meas_mum_pz, meas_mum_e;
  double meas_K_px, meas_K_py, meas_K_pz, meas_K_e;

  int nsplits, ndtrs;
  int meas_nsplits, meas_ndtrs;
  int GluonTag, NumHFHads;
  int eventNumber;
  bool Hasbbbar;
  // TLorentzVector
  LundTree->SetBranchAddress("eventNumber", &eventNumber);
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
  LundTree->SetBranchAddress("jet_rap", &jet_rap);

  LundTree->SetBranchAddress("jet_px", &jet_px);
  LundTree->SetBranchAddress("jet_py", &jet_py);
  LundTree->SetBranchAddress("jet_pz", &jet_pz);
  LundTree->SetBranchAddress("jet_e", &jet_e);

  LundTree->SetBranchAddress("ndtrs", &ndtrs);
  LundTree->SetBranchAddress("nsplits", &nsplits);

  LundTree->SetBranchAddress("mum_px", &mum_px);
  LundTree->SetBranchAddress("mum_py", &mum_py);
  LundTree->SetBranchAddress("mum_pz", &mum_pz);
  LundTree->SetBranchAddress("mum_e", &mum_e);

  LundTree->SetBranchAddress("mup_px", &mup_px);
  LundTree->SetBranchAddress("mup_py", &mup_py);
  LundTree->SetBranchAddress("mup_pz", &mup_pz);
  LundTree->SetBranchAddress("mup_e", &mup_e);

  LundTree->SetBranchAddress("K_px", &K_px);
  LundTree->SetBranchAddress("K_py", &K_py);
  LundTree->SetBranchAddress("K_pz", &K_pz);
  LundTree->SetBranchAddress("K_e", &K_e);

  LundTree->SetBranchAddress("HF_px", &HF_px);
  LundTree->SetBranchAddress("HF_py", &HF_py);
  LundTree->SetBranchAddress("HF_pz", &HF_pz);
  LundTree->SetBranchAddress("HF_e", &HF_e);
  LundTree->SetBranchAddress("HF_pt", &HF_pt);

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
  LundTree->SetBranchAddress("meas_jet_rap", &meas_jet_rap);

  LundTree->SetBranchAddress("meas_jet_px", &meas_jet_px);
  LundTree->SetBranchAddress("meas_jet_py", &meas_jet_py);
  LundTree->SetBranchAddress("meas_jet_pz", &meas_jet_pz);
  LundTree->SetBranchAddress("meas_jet_e", &meas_jet_e);

  LundTree->SetBranchAddress("meas_mum_px", &meas_mum_px);
  LundTree->SetBranchAddress("meas_mum_py", &meas_mum_py);
  LundTree->SetBranchAddress("meas_mum_pz", &meas_mum_pz);
  LundTree->SetBranchAddress("meas_mum_e", &meas_mum_e);

  LundTree->SetBranchAddress("meas_mup_px", &meas_mup_px);
  LundTree->SetBranchAddress("meas_mup_py", &meas_mup_py);
  LundTree->SetBranchAddress("meas_mup_pz", &meas_mup_pz);
  LundTree->SetBranchAddress("meas_mup_e", &meas_mup_e);

  LundTree->SetBranchAddress("meas_K_px", &meas_K_px);
  LundTree->SetBranchAddress("meas_K_py", &meas_K_py);
  LundTree->SetBranchAddress("meas_K_pz", &meas_K_pz);
  LundTree->SetBranchAddress("meas_K_e", &meas_K_e);

  LundTree->SetBranchAddress("meas_ndtrs", &meas_ndtrs);
  LundTree->SetBranchAddress("meas_nsplits", &meas_nsplits);
  LundTree->SetBranchAddress("GluonTag", &GluonTag);
  LundTree->SetBranchAddress("NumHFHads", &NumHFHads);
  LundTree->SetBranchAddress("Hasbbbar", &Hasbbbar);

  int eventNum;
  int NumJets = 0;
  int NumJets_zdR = 0;
  int NumJets_ktdR = 0;
  int NumBJets = 0;

  cout << "Requested # of events" << NumEvts << endl;
  for (int ev = 0; ev < NumEvts; ev++)
  {
    LundTree->GetEntry(ev);

    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;

    TLorentzVector HFmeson, HFjet, mum, mup, Kmeson, Jpsi;
    HFjet.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
    mup.SetPxPyPzE(mup_px, mup_py, mup_pz, mup_e);
    mum.SetPxPyPzE(mum_px, mum_py, mum_pz, mum_e);
    Kmeson.SetPxPyPzE(K_px, K_py, K_pz, K_e);
    HFmeson.SetPxPyPzE(HF_px, HF_py, HF_pz, HF_e);
    Jpsi = mup + mum;
    double HF_eta = HFmeson.Eta();
    double HF_pt = HFmeson.Pt();

    if (jet_eta > etaMin && jet_eta < etaMax)
      h2_HFptjetpt->Fill(HFmeson.Pt(), HFjet.Pt());
    h2_jetpteta->Fill(HFjet.Pt(), HFjet.Eta());

    if (jet_pt < ptMin)
      continue;
    if (jet_pt > ptMax)
      continue;
    if (jet_eta < etaMin || jet_eta > etaMax)
      continue;

    if (NumHFHads > 1)
      continue;
    if (SubtractGS && Hasbbbar)
    {
      continue;
    }

    event_counter++;
    // if(HFmeson.Pt() < 2) cout<<HFmeson.Pt()<<endl;

    // cout<<eventNumber<<": "<<jet_pt <<" -- "<< meas_jet_pt<<endl;
    // if(HFmeson.M() < 5.279) continue;
    // if(kts->size() < 1) cout<<"filled with 0 kts";
    NumBJets++;

    h1_jet_pt->Fill(jet_pt);
    h1_jet_eta->Fill(jet_eta);
    h1_jet_rap->Fill(jet_rap);

    h1_meas_jet_pt->Fill(meas_jet_pt);
    h1_meas_jet_eta->Fill(meas_jet_eta);
    h1_meas_jet_rap->Fill(meas_jet_rap);

    h1_nsplittings->Fill(kts->size());
    h1_HFpt->Fill(HFmeson.Pt());
    h1_HF_rap->Fill(HFmeson.Rapidity());
    h1_HF_pt->Fill(HFmeson.Pt());
    h1_HF_mass->Fill(HFmeson.M());

    h1_jet_ptbalance->Fill(jet_pt / meas_jet_pt);
    h1_HFjet_ptbalance->Fill(jet_pt / HFmeson.Pt());

    h1_Jpsi_mass->Fill(Jpsi.M());
    h1_Jpsi_pt->Fill(Jpsi.Pt());
    h1_Jpsi_rap->Fill(Jpsi.Rapidity());

    h1_nJetDtrs_noghost->Fill(ndtrs);

    if (Hasbbbar)
    {
      double frag_z_gluon = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
      h1_frag_z_gluon->Fill(frag_z_gluon);
      double frag_jt_gluon = HFmeson.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
      h1_frag_jt_gluon->Fill(frag_jt_gluon);
      double frag_r_gluon = HFmeson.DeltaR(HFjet, true);
      h1_frag_r_gluon->Fill(frag_r_gluon);
      h1_nJetDtrs_noghost_gluon->Fill(ndtrs);
    }
    double frag_z = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
    h1_frag_z->Fill(frag_z);
    double frag_jt = HFmeson.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
    h1_frag_jt->Fill(frag_jt);
    double frag_r = HFmeson.DeltaR(HFjet, true);
    h1_frag_r->Fill(frag_r);
    h1_nJetDtrs_noghost->Fill(ndtrs);

    // if(fabs(frag_z-0.3) < 0.02 ){
    //   cout<<"("<<HFmeson.Px()<<", "<<HFmeson.Py()<<","<<HFmeson.Pz()<<")"<<endl;
    //   cout<<"("<<HFjet.Px()<<", "<<HFjet.Py()<<","<<HFjet.Pz()<<")"<<endl;
    //   cout<<ndtrs<<endl;
    // }

    bool hasEmission_ktdR = false;
    bool hasEmission_zdR = false;

    for (int idecl = 0; idecl < kts->size(); idecl++)
    {
      double logkt = log(kts->at(idecl));
      double logdR = log(jetradius / dRs->at(idecl));
      double logz = log(1. / zs->at(idecl));
      double logtheta = log(1. / thetas->at(idecl));
      double erad = Erads->at(idecl);
      double kttheta = ktthetas->at(idecl);

      ////// Fill histograms //////
      if (logkt < -3)
        continue;
      if (logdR > dR_min && logdR < dR_max && logz > z_min && logz < z_max)
        hasEmission_zdR = true;
      if (logdR > dR_min && logdR < dR_max && logkt > kT_min && logkt < kT_max)
        hasEmission_ktdR = true;
      h1_dR->Fill(logdR);
      h2_lundplane->Fill(logtheta, logkt);
      h2_ktdR->Fill(logdR, logkt);
      h2_zdR->Fill(logdR, logz);

      for (int i = 0; i < ptHFbinsize; i++)
      {
        if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
        {
          for (int j = 0; j < HFetabinsize; j++)
          {
            int loc = i * HFetabinsize + j;
            if (HF_eta > HFeta_binedges[j] && HF_eta < HFeta_binedges[j + 1])
            {
              vec_h3_ptktdR[loc]->Fill(logdR, logkt, jet_pt);
              vec_h3_ptzdR[loc]->Fill(logdR, logz, jet_pt);
              break;
            }
          }
          break;
        }
      }

      h1_dR->Fill(logdR);
      h1_z->Fill(logz);
      h1_theta->Fill(logtheta);
      h1_kt->Fill(logkt);

      h3_ptktdR->Fill(logdR, logkt, jet_pt);
      h3_ptzdR->Fill(logdR, logz, jet_pt);

      ////// Non-perturbative cut //////

      if (kttheta > LambdaQCD)
      {
        h2_thetaErad->Fill(erad, logtheta);
        h2_dRErad->Fill(erad, logdR);
        for (int j = 0; j < NumHists; j++)
        {
          if (erad > MinErad + StepErad * j && erad < MinErad + StepErad * (j + 1))
          {
            h1_thetas[j]->Fill(exp(-1 * logtheta));
            h1_Rratios[j]->Fill(logtheta);
            break;
          }
        }
      }
    }

    for (int idecl = 0; idecl < meas_kts->size(); idecl++)
    {
      double logkt = log(meas_kts->at(idecl));
      double logdR = log(jetradius / meas_dRs->at(idecl));
      double logz = log(1. / meas_zs->at(idecl));
      double logtheta = log(1. / meas_thetas->at(idecl));
      double erad = meas_Erads->at(idecl);
      double kttheta = meas_ktthetas->at(idecl);

      ////// Fill histograms //////
      h1_meas_dR->Fill(logdR);
      h2_meas_lundplane->Fill(logtheta, logkt);
      h2_meas_ktdR->Fill(logdR, logkt);
      h2_meas_zdR->Fill(logdR, logz);

      h1_meas_dR->Fill(logdR);
      h1_meas_z->Fill(logz);
      h1_meas_theta->Fill(logtheta);
      h1_meas_kt->Fill(logkt);
    }
    if (hasEmission_zdR)
      NumJets_zdR++;
    if (hasEmission_ktdR)
      NumJets_ktdR++;
  }
  cout << event_counter << " events processed" << endl;
  cout << "NumJets_zdR = " << NumJets_zdR << endl;
  cout << "NumJets_ktdR = " << NumJets_ktdR << endl;

  for (int i = 0; i < ptHFbinsize; i++)
  {
    for (int j = 0; j < HFetabinsize; j++)
    {
      int loc = i * HFetabinsize + j;
      vec_h3_ptktdR[loc]->Write(Form("h3_ptktdR%d%d", i, j));
      vec_h3_ptzdR[loc]->Write(Form("h3_ptzdR%d%d", i, j));
    }
  }
  // h2_ktdR->Scale(1./ NumJets_ktdR);
  // h2_zdR->Scale(1./ NumJets_zdR);

  SetTruthStyle(h1_jet_eta);
  SetDataStyle(h1_jet_rap);
  SetTruthStyle(h1_jet_pt);

  SetRecoStyle(h1_meas_jet_eta);
  SetDataStyle(h1_meas_jet_rap);
  SetRecoStyle(h1_meas_jet_pt);

  SetTruthStyle(h1_HF_rap);
  SetTruthStyle(h1_HF_pt);
  SetTruthStyle(h1_HF_mass);

  SetTruthStyle(h1_kt);
  SetTruthStyle(h1_z);
  SetTruthStyle(h1_dR);
  SetTruthStyle(h1_theta);

  SetRecoStyle(h1_meas_kt);
  SetRecoStyle(h1_meas_z);
  SetRecoStyle(h1_meas_dR);
  SetRecoStyle(h1_meas_theta);

  SetTruthStyle(h1_Jpsi_rap);
  SetTruthStyle(h1_Jpsi_pt);
  SetTruthStyle(h1_Jpsi_mass);

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
  // gStyle->SetOptStat(0);
  // gStyle->SetPaperSize(TStyle::kUSLetter);
  // gStyle->SetPadBottomMargin(0.08);
  // gStyle->SetPadTopMargin(0.005);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetLabelSize(0.05, "X");
  gStyle->SetLabelSize(0.05, "Y");
  gStyle->SetTitleXSize(0.055);
  gStyle->SetTitleYSize(0.055);
  gStyle->SetTitleOffset(0.85, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetStatW(0.2);
  gStyle->SetPalette(kBird);
  gStyle->SetNumberContours(100);
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
  h2_lundplane->SetStats(0);
  h2_lundplane->SetXTitle("ln(1/#theta)");
  h2_lundplane->SetYTitle("ln(k_{T})");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  //  gPad->SetLogz();
  h2_lundplane->Draw("COLZ");
  Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h2_thetaErad->SetStats(0);
  h2_thetaErad->SetXTitle("E_{radiator}");
  h2_thetaErad->SetYTitle("ln(1/#theta)");
  // h2_thetaErad->Setmaximum(.01);
  // h2_thetaErad->SetMinimum(0.00001);
  //  gPad->SetLogz();
  h2_thetaErad->Draw("COLZ");
  f1_kt_Erad->SetLineColor(1);
  f1_kt_Erad->SetLineStyle(9);
  if (flavor != 0)
    f1_theta_Erad->Draw("SAME");
  f1_kt_Erad->Draw("SAME");

  Tl.DrawLatex(.2, 0.8, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  Tl.DrawLatex(.2, 0.72, Form("k_{T}>%.1f GeV", LambdaQCD));
  Tl.DrawLatex(.2, 0.64, Form("%.1f<#eta<%.1f", etaMin, etaMax));
  ccan[ican]->cd(3);
  h2_ktdR->SetStats(0);
  h2_ktdR->SetXTitle("ln(R/#DeltaR)");
  h2_ktdR->SetYTitle("ln(k_{T})");
  // h2_ktdR->SetMaximum(.01);
  // h2_ktdR->SetMinimum(0.00001);
  //  gPad->SetLogz();
  h2_ktdR->Draw("COLZ");

  ccan[ican]->cd(4);
  h2_zdR->SetStats(0);
  h2_zdR->SetXTitle("ln(R/#DeltaR)");
  h2_zdR->SetYTitle("ln(1/z)");
  // h2_zdR->SetMaximum(.01);
  // h2_zdR->SetMinimum(0.00001);
  //  gPad->SetLogz();
  h2_zdR->Draw("COLZ");

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
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  h1_dR->SetStats(0);
  h1_dR->SetXTitle("ln(R/#DeltaR)");

  h1_dR->Draw("P E SAME");
  h1_dR->SetMinimum(0.);
  // Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  h1_meas_dR->SetStats(0);
  h1_meas_dR->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_kt->SetStats(0);
  h1_kt->SetXTitle("ln(kt)");
  h1_kt->SetMinimum(0.);
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_kt->Draw("P E SAME");
  h1_meas_kt->Draw("P E SAME");
  ccan[ican]->cd(3);
  h1_z->SetStats(0);
  h1_z->SetXTitle("ln(1/z)");
  h1_z->Draw("P E SAME");
  h1_z->SetMinimum(0.);

  h1_meas_z->Draw("P E SAME");

  ccan[ican]->cd(4);
  h1_theta->SetStats(0);
  h1_theta->SetXTitle("ln(1/#theta)");
  h1_theta->SetMinimum(0.);
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_theta->Draw("P E SAME");
  h1_meas_theta->Draw("P E SAME");

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
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  h1_frag_z->SetStats(0);
  h1_frag_z->SetXTitle("Frag z");

  THStack *stack_frag = new THStack("stack_frag", "");
  stack_frag->Add(h1_frag_z);
  stack_frag->Add(h1_frag_z_gluon);

  SetTruthStyle(h1_frag_z);
  SetDataStyle(h1_frag_z_gluon);
  stack_frag->Draw("P NOSTACK ");
  // h1_frag_z->Draw("P E SAME");

  // h1_frag_z_gluon->Draw("P E SAME");

  // SetTruthStyle(h1_tr_frag_z);
  // h1_tr_frag_z->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  gPad->SetLogy();
  h1_frag_jt->SetStats(0);
  h1_frag_jt->SetXTitle("Frag jt");
  SetTruthStyle(h1_frag_jt);
  h1_frag_jt->Draw("P E SAME");

  // SetTruthStyle(h1_tr_frag_jt);
  // h1_tr_frag_jt->Draw("P E SAME");

  ccan[ican]->cd(3);
  gPad->SetLogy();
  SetTruthStyle(h1_frag_r);
  h1_frag_r->SetStats(0);
  h1_frag_r->SetXTitle("Frag r");
  h1_frag_r->Draw("P E SAME");

  // SetTruthStyle(h1_tr_frag_r);
  // h1_tr_frag_r->Draw("P E SAME");

  ccan[ican]->cd(4);

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
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  h1_jet_pt->SetStats(0);
  h1_jet_pt->SetXTitle("pT(jet)");
  h1_jet_pt->Draw("P E SAME");
  h1_meas_jet_pt->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_jet_eta->SetStats(0);
  h1_jet_eta->SetXTitle("#eta(jet)");
  h1_jet_eta->Draw("P E SAME");
  h1_meas_jet_eta->Draw("P E SAME");

  ccan[ican]->cd(3);
  // h2_thetaErad->Scale(1./NumJets);
  h1_jet_rap->SetStats(0);
  h1_jet_rap->SetXTitle("#eta(jet)");
  h1_jet_rap->Draw("P E SAME");
  h1_meas_jet_rap->Draw("P E SAME");

  ccan[ican]->cd(4);
  // h1_nsplittings->Draw("P E SAME");
  h1_nJetDtrs_noghost->SetStats(0);
  h1_nJetDtrs_noghost_gluon->SetStats(0);
  SetTruthStyle(h1_nJetDtrs_noghost);
  SetDataStyle(h1_nJetDtrs_noghost_gluon);
  NormalizeHist(h1_nJetDtrs_noghost);
  NormalizeHist(h1_nJetDtrs_noghost_gluon);
  h1_nJetDtrs_noghost_gluon->Draw("P E SAME");
  h1_nJetDtrs_noghost->Draw("P E SAME");

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
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  h1_HF_pt->SetStats(0);
  h1_HF_pt->SetXTitle("pT(HF)");

  h1_HF_pt->Draw("P E SAME");
  // Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  // h1_tr_dR->SetStats(0);
  // h1_tr_dR->SetMarkerStyle(21);
  // h1_tr_dR->SetMarkerColor(kRed);
  // h1_tr_dR->SetLineColor(kRed);
  // h1_tr_dR->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_HF_rap->SetStats(0);
  h1_HF_rap->SetXTitle("y(HF)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_HF_rap->Draw("P E SAME");
  ccan[ican]->cd(3);
  h1_HF_mass->SetStats(0);
  // h1_dphi_HF_jet->SetXTitle("#Delta#Phi");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_HF_mass->Draw("P E SAME");

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
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  h1_Jpsi_pt->SetStats(0);
  h1_Jpsi_pt->SetXTitle("pT(J/#psi)");

  h1_Jpsi_pt->Draw("P E SAME");
  // Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  // h1_tr_dR->SetStats(0);
  // h1_tr_dR->SetMarkerStyle(21);
  // h1_tr_dR->SetMarkerColor(kRed);
  // h1_tr_dR->SetLineColor(kRed);
  // h1_tr_dR->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_Jpsi_rap->SetStats(0);
  h1_Jpsi_rap->SetXTitle("y(J/#psi)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_Jpsi_rap->Draw("P E SAME");
  ccan[ican]->cd(3);
  h1_Jpsi_mass->SetStats(0);
  // h1_dphi_Jpsi_jet->SetXTitle("#Delta#Phi");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_Jpsi_mass->Draw("P E SAME");

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
  f.Write();
  f.Close();

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }

  cout << "Num of True B jets = " << NumBJets << endl;
}
