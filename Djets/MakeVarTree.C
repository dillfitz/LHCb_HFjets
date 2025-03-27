

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include "JetTree.C"
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"

using namespace std;

void MakeVarTree(int NumEvts_user = -1,
                 int dataset = 90499,
                 bool isData = true,
                 bool chargedJetCut_user = false,
                 bool DoJER = false,
                 int DoJES = 0,
                 bool DoJetID = false,
                 bool DoFSPEff = false,
                 bool DoFSPPT = false,
                 bool DoGhostCut = false,
                 int PromptCut = 0)
{

  int NumEvts = NumEvts_user;
  int NumEvtsTruth = NumEvts_user;
  bool MCflag = !isData;
  followHardest = false;
  truthLevel = false;
  chargedJetCut = chargedJetCut_user;
  if (truthLevel)
  {
    ghostCut = false;
  }
  if (DoGhostCut)
    ghostProb = 0.3;

  int year = (dataset / 10000) % 10;
  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;
  int tr_HF_pdgcode = -999;

  if (flavor == 5)
  {
    mass_num = 4.2;
    HF_pdgcode = 521;
  }
  else if (flavor == 4)
  {
    mass_num = 1.25;
    HF_pdgcode = 421;
    tr_HF_pdgcode = 421;
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

  str_year = (year == 6) ? "2016" : (year == 7) ? "2017"
                                : (year == 8)   ? "2018"
                                                : "";

  str_Mag = Mag == 0 ? "_MD" : Mag == 1 ? "_MU"
                                        : "";
  str_flavor = flavor == 1 ? "_udsg" : flavor == 4 ? "_c"
                                   : flavor == 5   ? "_b"
                                                   : "";
  str_level = truthLevel ? "truth" : isData ? "data"
                                            : "reco";
  str_followHard = flavor == 1 ? "_hard" : "_HF";
  str_followHard = followHardest ? "_hard" : "_HF";
  str_ghost = ghostCut ? Form("_ghost_%.1f", ghostProb) : "";
  str_charged = chargedJetCut ? "_charge" : "";
  str_eta = Form("_eta_%.1f%.1f", etaMin, etaMax);
  str_pt = Form("_ptj_%d%d", int(ptMin), int(ptMax));
  str_Nevts = Form("_ev_%d", NumEvts);
  str_prompt = (PromptCut == 1) ? "_prompt" : (PromptCut == 2) ? "_nonprompt"
                                          : (PromptCut == 3)   ? "_Dsst"
                                          : (PromptCut == 4)   ? "_GammaMiss"
                                                               : "";
  TString str_tree;

  TString extension_read, extension_RootFilesMC, extension_RootFilesData, extension_RootFiles;
  TString extension, extension_eff;

  extension_RootFilesMC = TString("../../root_files/DjetsMC/");
  extension_RootFilesData = TString("../../root_files/Djets/");
  extension_RootFiles = isData ? "../../root_files/Djets/" : "../../root_files/DjetsMC/";

  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);
  extension_eff = TString("fspeff_") + "truth" + Form("_ev_%d", -1) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_flavor + Form("_%d", 90499);

  if (DoJES == 1)
    extension = TString("JESPos_") + extension;
  else if (DoJES == 2)
    extension = TString("JESNeg_") + extension;
  if (DoJER)
    extension = TString("JER_") + extension;
  if (DoFSPEff)
    extension = TString("fspeff_") + extension;
  if (DoFSPPT)
    extension = TString("fsppt_") + extension;
  if (DoGhostCut)
    extension = TString("ghostcut_") + extension;

  // extension_pideff = "effhists-Turbo" + str_year + str_Mag + "-K-DLLK>0-P.ETA.nTracks";

  JetTree Tree(0, dataset, isData);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();

  TH2D *h2_HFpt_RM = new TH2D("h2_HFpt_RM", "", 30, 0, 100, 30, 0, 100);

  TFile f(extension_RootFiles + extension + ".root", "RECREATE");

  TH1F *h1_TIS = new TH1F("h1_TIS", "", ptHFbinsize, ptHF_binedges);
  TH1F *h1_TISTOS = new TH1F("h1_TISTOS", "", ptHFbinsize, ptHF_binedges);

  TH2F *h2_TIS_ptrap = new TH2F("h2_TIS_ptrap", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
  TH2F *h2_TISTOS_ptrap = new TH2F("h2_TISTOS_ptrap", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);

  TH1D *h1_mass_Dsgamma = new TH1D("h1_mass_Dsgamma", "", 80, 2.00, 2.55);
  TH1D *h1_mass_Dsgamma_prompt = new TH1D("h1_mass_Dsgamma_prompt", "", 80, 2.00, 2.55);
  TH1D *h1_mass_Dsgamma_nonprompt = new TH1D("h1_mass_Dsgamma_nonprompt", "", 80, 2.00, 2.55);

  TH1D *h1_pt_gamma_nonprompt = new TH1D("h1_pt_gamma_nonprompt", "", 50, 0, 10);
  TH1D *h1_pt_gamma_all = new TH1D("h1_pt_gamma_all", "", 50, 0, 10);

  TH1D *h1_HFMass = new TH1D("h1_HFMass", "", 50, 1.864 - 0.06, 1.864 + 0.06);
  TH1D *h1_HFMass_dtf = new TH1D("h1_HFMass_dtf", "", 50, 1.864 - 0.06, 1.864 + 0.06);
  TH1D *h1_ipchi2 = new TH1D("h1_ipchi2", "", 80, -4, 4);

  float jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  float jet_rap, tr_jet_rap;
  float jet_px, jet_py, jet_pz, jet_e, jet_charge;

  float HF_px, HF_py, HF_pz, HF_e, HF_pt, HF_m;

  float K_px, K_py, K_pz, K_e;
  float pi0_px, pi0_py, pi0_pz, pi0_e;
  float pi_px, pi_py, pi_pz, pi_e, pi_p, pi_eta;
  float Phi_px, Phi_py, Phi_pz, Phi_e;

  float K_CHI2NDOF, K_GHOSTPROB, K_IPCHI2;
  float pi0_CHI2NDOF, pi0_GHOSTPROB, pi0_IPCHI2;
  float pi_CHI2NDOF, pi_GHOSTPROB, pi_IPCHI2;
  float Phi_CHI2NDOF, Phi_CHI2, Phi_FDCHI2, Phi_BPVDLS, Phi_IPCHI2;
  float D0_CHI2NDOF, D0_CHI2, D0_IPCHI2;

  int nTracks, nSPDHits;
  float Phi_ipchi2, pi_ipchi2;
  float Bfromjet_px, Bfromjet_py, Bfromjet_pz, Bfromjet_e;
  float pi_PIDK, K_PIDK;
  float K_realET;

  float tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  float tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e, tr_HF_pt;
  float tr_K_px, tr_K_py, tr_K_pz, tr_K_e;
  float tr_pi0_px, tr_pi0_py, tr_pi0_pz, tr_pi0_e;
  float tr_pi_px, tr_pi_py, tr_pi_pz, tr_pi_e;

  double z, jt, r;
  double tr_z, tr_jt, tr_r;
  double zg, jtg, rg;

  int nsplits, ndtrs, ndtrs_noghost, NumSubJets;
  int tr_nsplits, tr_ndtrs;
  int nSV, nSV_test;
  bool isTrueDjet, isBacktoBack, HFHardest, Hasccbar;
  float dphi, Bmass_1, Bmass_2;
  float D0_mass, chi2ndf_dtf, tau_dtf;
  float dtf_mass;
  int NumBHaD0_tr, eventNumber;

  float pideff_pi(1.0), pideff_Kaon(1.0), pideff_pi0(1.0);
  float pideff_pi_err(1.0), pideff_K_err(1.0), pideff_pi0_err(1.0);
  float trkeff_pi(1.0), trkeff_Kaon(1.0), trkeff_pi0(1.0);
  float trkeff_pi_errhi(1.0), trkeff_K_errhi(1.0), trkeff_pi0_errhi(1.0);
  float trkeff_pi_errlo(1.0), trkeff_K_errlo(1.0), trkeff_pi0_errlo(1.0);
  float trigeff_Data(1.0), trigeff_MC(1.0), trigeff_ratio(1.0);
  float trigeff_L0table_Data(1.0), trigeff_L0table_Data_err(1.0);
  float trigeff_Kaon(1.0);
  double ptweight(1.);
  double NearestMass = -99;
  bool FromDsst;

  int Ndtr_neutral, Ndtr_charged;
  vector<float> dtr_pt, dtr_rap, dtr_id, dtr_3charge;

  // vector<float> thetas, tr_thetas;
  // vector<float> ktthetas, tr_ktthetas;
  // vector<float> dRs, tr_dRs;
  // vector<float> Erads, tr_Erads;
  // vector<float> kts, tr_kts;
  // vector<float> zs, tr_zs;
  // vector<float> raps, tr_raps;
  // vector<float> phis, tr_phis;

  vector<bool> hardest, tr_hardest;
  vector<float> sv_ipchi2, sv_keys, sv_pids;

  float sv_mass, sv_chi2, sv_cosine, sv_ntrks, SVIPCHI2;
  float SVIPCHI2_1, SVIPCHI2_2;
  int SVTag;

  bool K_L0, pi0_L0;
  bool L0Dec, Hlt1Dec, Hlt2Dec;
  bool L0TIS, Hlt1TIS, Hlt2TIS;

  float WTA_dist;
  float tr_WTA_dist;
  bool Trig, TIS, TOS;

  // TLorentzVector
  TTree *DTree = new TTree("DTree", "DTree Variables");

  DTree->Branch("eventNumber", &eventNumber);

  DTree->Branch("dtr_pt", &dtr_pt);
  DTree->Branch("dtr_rap", &dtr_rap);
  DTree->Branch("dtr_id", &dtr_id);
  DTree->Branch("dtr_3charge", &dtr_3charge);
  DTree->Branch("Ndtr_neutral", &Ndtr_neutral);
  DTree->Branch("Ndtr_charged", &Ndtr_charged);

  // DTree->Branch("thetas", &thetas);
  // DTree->Branch("ktthetas", &ktthetas);
  // DTree->Branch("Erads", &Erads);
  // DTree->Branch("dRs", &dRs);
  // DTree->Branch("kts", &kts);
  // DTree->Branch("zs", &zs);
  // DTree->Branch("raps", &raps);
  // DTree->Branch("phis", &phis);

  DTree->Branch("hardest", &hardest);

  DTree->Branch("jet_pt", &jet_pt);
  DTree->Branch("jet_eta", &jet_eta);
  DTree->Branch("jet_rap", &jet_rap);

  DTree->Branch("jet_px", &jet_px);
  DTree->Branch("jet_py", &jet_py);
  DTree->Branch("jet_pz", &jet_pz);
  DTree->Branch("jet_e", &jet_e);

  DTree->Branch("HF_px", &HF_px);
  DTree->Branch("HF_py", &HF_py);
  DTree->Branch("HF_pz", &HF_pz);
  DTree->Branch("HF_e", &HF_e);
  DTree->Branch("HF_pt", &HF_pt);
  DTree->Branch("HF_m", &HF_m);

  DTree->Branch("D0_IPCHI2", &D0_IPCHI2);
  DTree->Branch("D0_CHI2", &D0_CHI2);
  DTree->Branch("D0_CHI2NDOF", &D0_CHI2NDOF);

  DTree->Branch("ndtrs", &ndtrs);
  DTree->Branch("ndtrs_noghost", &ndtrs_noghost);
  DTree->Branch("nsplits", &nsplits);

  DTree->Branch("pi0_px", &pi0_px);
  DTree->Branch("pi0_py", &pi0_py);
  DTree->Branch("pi0_pz", &pi0_pz);
  DTree->Branch("pi0_e", &pi0_e);
  DTree->Branch("pi0_IPCHI2", &pi0_IPCHI2);
  DTree->Branch("pi0_CHI2NDOF", &pi0_CHI2NDOF);
  DTree->Branch("pi0_GHOSTPROB", &pi0_GHOSTPROB);

  DTree->Branch("K_px", &K_px);
  DTree->Branch("K_py", &K_py);
  DTree->Branch("K_pz", &K_pz);
  DTree->Branch("K_e", &K_e);
  DTree->Branch("K_IPCHI2", &K_IPCHI2);
  DTree->Branch("K_CHI2NDOF", &K_CHI2NDOF);
  DTree->Branch("K_GHOSTPROB", &K_GHOSTPROB);

  DTree->Branch("pi_px", &pi_px);
  DTree->Branch("pi_py", &pi_py);
  DTree->Branch("pi_pz", &pi_pz);
  DTree->Branch("pi_e", &pi_e);
  DTree->Branch("pi_p", &pi_p);
  DTree->Branch("pi_eta", &pi_eta);
  DTree->Branch("pi_IPCHI2", &pi_IPCHI2);
  DTree->Branch("pi_CHI2NDOF", &pi_CHI2NDOF);
  DTree->Branch("pi_GHOSTPROB", &pi_GHOSTPROB);

  DTree->Branch("nTracks", &nTracks);
  DTree->Branch("nSPDHits", &nSPDHits);

  DTree->Branch("Phi_px", &Phi_px);
  DTree->Branch("Phi_py", &Phi_py);
  DTree->Branch("Phi_pz", &Phi_pz);
  DTree->Branch("Phi_e", &Phi_e);
  DTree->Branch("Phi_FDCHI2", &Phi_FDCHI2);
  DTree->Branch("Phi_BPVDLS", &Phi_BPVDLS);
  DTree->Branch("Phi_CHI2", &Phi_CHI2);
  DTree->Branch("Phi_CHI2NDOF", &Phi_CHI2NDOF);

  DTree->Branch("Phi_ipchi2", &Phi_ipchi2);
  DTree->Branch("pi_ipchi2", &pi_ipchi2);

  DTree->Branch("Bfromjet_px", &Bfromjet_px);
  DTree->Branch("Bfromjet_py", &Bfromjet_py);
  DTree->Branch("Bfromjet_pz", &Bfromjet_pz);
  DTree->Branch("Bfromjet_e", &Bfromjet_e);

  // DTree->Branch("tr_thetas", &tr_thetas);
  // DTree->Branch("tr_ktthetas", &tr_ktthetas);
  // DTree->Branch("tr_Erads", &tr_Erads);
  // DTree->Branch("tr_dRs", &tr_dRs);
  // DTree->Branch("tr_kts", &tr_kts);
  // DTree->Branch("tr_zs", &tr_zs);
  // DTree->Branch("tr_raps", &tr_raps);
  // DTree->Branch("tr_phis", &tr_phis);

  DTree->Branch("tr_hardest", &tr_hardest);

  DTree->Branch("tr_jet_pt", &tr_jet_pt);
  DTree->Branch("tr_jet_eta", &tr_jet_eta);
  DTree->Branch("tr_jet_rap", &tr_jet_rap);

  DTree->Branch("tr_jet_px", &tr_jet_px);
  DTree->Branch("tr_jet_py", &tr_jet_py);
  DTree->Branch("tr_jet_pz", &tr_jet_pz);
  DTree->Branch("tr_jet_e", &tr_jet_e);

  DTree->Branch("tr_HF_px", &tr_HF_px);
  DTree->Branch("tr_HF_py", &tr_HF_py);
  DTree->Branch("tr_HF_pz", &tr_HF_pz);
  DTree->Branch("tr_HF_e", &tr_HF_e);
  DTree->Branch("tr_HF_pt", &tr_HF_pt);

  DTree->Branch("tr_pi0_px", &tr_pi0_px);
  DTree->Branch("tr_pi0_py", &tr_pi0_py);
  DTree->Branch("tr_pi0_pz", &tr_pi0_pz);
  DTree->Branch("tr_pi0_e", &tr_pi0_e);

  DTree->Branch("tr_K_px", &tr_K_px);
  DTree->Branch("tr_K_py", &tr_K_py);
  DTree->Branch("tr_K_pz", &tr_K_pz);
  DTree->Branch("tr_K_e", &tr_K_e);

  DTree->Branch("tr_pi_px", &tr_pi_px);
  DTree->Branch("tr_pi_py", &tr_pi_py);
  DTree->Branch("tr_pi_pz", &tr_pi_pz);
  DTree->Branch("tr_pi_e", &tr_pi_e);

  DTree->Branch("tr_ndtrs", &tr_ndtrs);
  DTree->Branch("tr_nsplits", &tr_nsplits);
  DTree->Branch("isTrueDjet", &isTrueDjet);

  DTree->Branch("dphi", &dphi);
  DTree->Branch("nSV", &nSV);
  DTree->Branch("nSV_test", &nSV_test);
  DTree->Branch("sv_mass", &sv_mass);
  DTree->Branch("sv_chi2", &sv_chi2);
  DTree->Branch("sv_ntrks", &sv_ntrks);
  DTree->Branch("sv_cosine", &sv_cosine);
  DTree->Branch("sv_ipchi2", &sv_ipchi2);
  DTree->Branch("sv_keys", &sv_keys);
  DTree->Branch("sv_pids", &sv_pids);

  DTree->Branch("SVTag", &SVTag);

  DTree->Branch("HFHardest", &HFHardest);
  DTree->Branch("D0_mass", &D0_mass);
  DTree->Branch("dtf_mass", &dtf_mass);

  DTree->Branch("chi2ndf_dtf", &chi2ndf_dtf);
  DTree->Branch("tau_dtf", &tau_dtf);
  // DTree->Branch("NumSubJets", &NumSubJets);
  DTree->Branch("NumBHaD0_tr", &NumBHaD0_tr);
  DTree->Branch("Hasccbar", &Hasccbar);
  DTree->Branch("pi_PIDK", &pi_PIDK);
  DTree->Branch("pideff_pi", &pideff_pi);
  DTree->Branch("pideff_pi0", &pideff_pi0);

  DTree->Branch("K_PIDK", &K_PIDK);
  DTree->Branch("pideff_Kaon", &pideff_Kaon);
  DTree->Branch("pideff_pi_err", &pideff_pi_err);
  DTree->Branch("pideff_pi0_err", &pideff_pi0_err);
  DTree->Branch("pideff_K_err", &pideff_K_err);

  DTree->Branch("trkeff_pi", &trkeff_pi);
  DTree->Branch("trkeff_Kaon", &trkeff_Kaon);
  DTree->Branch("trkeff_pi0", &trkeff_pi0);

  DTree->Branch("trkeff_pi_errhi", &trkeff_pi_errhi);
  DTree->Branch("trkeff_K_errhi", &trkeff_K_errhi);
  DTree->Branch("trkeff_pi0_errhi", &trkeff_pi0_errhi);
  DTree->Branch("trkeff_pi_errlo", &trkeff_pi_errlo);
  DTree->Branch("trkeff_K_errlo", &trkeff_K_errlo);
  DTree->Branch("trkeff_pi0_errlo", &trkeff_pi0_errlo);

  DTree->Branch("trigeff_L0table_Data", &trigeff_L0table_Data);
  DTree->Branch("trigeff_L0table_Data_err", &trigeff_L0table_Data_err);

  DTree->Branch("trigeff_Data", &trigeff_Data);
  DTree->Branch("trigeff_MC", &trigeff_MC);
  DTree->Branch("trigeff_ratio", &trigeff_ratio);

  DTree->Branch("trigeff_Kaon", &trigeff_Kaon);

  DTree->Branch("K_L0", &K_L0);
  DTree->Branch("pi0_L0", &pi0_L0);
  DTree->Branch("L0Dec", &L0Dec);
  DTree->Branch("Hlt1Dec", &Hlt1Dec);
  DTree->Branch("Hlt2Dec", &Hlt2Dec);
  DTree->Branch("L0TIS", &L0TIS);
  DTree->Branch("Hlt1TIS", &Hlt1TIS);
  DTree->Branch("Hlt2TIS", &Hlt2TIS);
  DTree->Branch("Trig", &Trig);
  DTree->Branch("TIS", &TIS);
  DTree->Branch("TOS", &TOS);

  DTree->Branch("SVIPCHI2", &SVIPCHI2);
  DTree->Branch("SVIPCHI2_1", &SVIPCHI2_1);
  DTree->Branch("SVIPCHI2_2", &SVIPCHI2_2);

  DTree->Branch("WTA_dist", &WTA_dist);
  DTree->Branch("tr_WTA_dist", &tr_WTA_dist);
  DTree->Branch("K_realET", &K_realET);
  DTree->Branch("NearestMass", &NearestMass);
  DTree->Branch("ptweight", &ptweight);

  DTree->Branch("z", &z);
  DTree->Branch("jt", &jt);
  DTree->Branch("r", &r);
  DTree->Branch("zg", &zg);
  DTree->Branch("jtg", &jtg);
  DTree->Branch("rg", &rg);
  DTree->Branch("tr_z", &tr_z);
  DTree->Branch("tr_jt", &tr_jt);
  DTree->Branch("tr_r", &tr_r);

  DTree->Branch("FromDsst", &FromDsst);

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //

  int eventNum;
  unsigned long long last_eventNum = 0;
  int events = 0;

  bool maxjetpT_found = false;
  bool maxHFpT_found = false;

  int Num_Bmatched = 0;
  int NumTwoHFInJet = 0;
  int NumTwoCand = 0;
  int N_num = 0;
  int N_denom = 0;
  int N_purity_num(0), N_purity_denom(0);
  float last_HFpt = 0;
  float last_HFjet = 0;
  int ev_min = 0;
  int NumSame = 0;
  int NumHFReco = 0;
  int NumHFReco_tr = 0;
  int NumHFjet = 0;
  int NumHFjet_tr = 0;
  int ev_notrig(0), ev_L0(0), ev_Hlt1(0), ev_Hlt2(0);
  TRandom3 *myUniform = new TRandom3();
  TRandom3 *myRNG = new TRandom3();

  int NumD0_star = 0;
  int NumD0_all = 0;

  int NumDsst = 0;
  int NumDetected = 0;

  for (int ev = ev_min; ev < NumEvts + ev_min; ev++)
  {
    Tree.GetEntry(ev);
    if (ev % 100000 == 0)
      cout << "Executing event " << ev << endl;

    if (ev != 0)
    {
      if (Tree.eventNumber == last_eventNum)
      {
        continue;
      }
    }

    if (Tree.nPVs > 1)
      continue;

    bool WrongB = false;

    // if (!isData)
    // {
    //   if (Tree.totCandidates > 1)
    //   {
    //     for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    //     {
    //       if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
    //       {
    //         if (fabs(Tree.Jet_Dtr_E[dtrs0] - Tree.D0_PE) / (Tree.D0_PE) > 0.001)
    //         {
    //           cout << "Wrong D0!, ";
    //           WrongB = true;
    //         }

    //         break;
    //       }
    //     }
    //     if (WrongB)
    //       continue;
    //   }
    // }

    for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    {
      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        if (fabs(Tree.Jet_Dtr_E[dtrs0] - Tree.D0_PE) / (Tree.D0_PE) > 0.001)
        {
          // cout << "Wrong D0!, ";
          WrongB = true;
        }
        break;
      }
    }
    if (WrongB)
      continue;

    L0Dec = Tree.D0_L0HadronDecision_TOS;
    Hlt1Dec = Tree.D0_Hlt1TrackMVADecision_TOS || Tree.D0_Hlt1TwoTrackMVADecision_TOS;
    Hlt2Dec = Tree.D0_Hlt2Phys_TOS;
    L0TIS = Tree.D0_L0HadronDecision_TIS || Tree.D0_L0PhotonDecision_TIS || Tree.D0_L0ElectronDecision_TIS || Tree.D0_L0MuonDecision_TIS;
    Hlt1TIS = Tree.D0_Hlt1Global_TIS;
    Hlt2TIS = Tree.D0_Hlt2Global_TIS;

    // cout << Tree.D0_Hlt2Global_TOS << ", " << Tree.D0_Hlt2Phys_TOS << ", " << Tree.D0_Hlt2Topo2BodyDecision_TOS << ", " << Tree.D0_Hlt2Topo3BodyDecision_TOS << ", " << Tree.D0_Hlt2Topo4BodyDecision_TOS << endl;

    ptweight = ptweights[JetMeth];
    // if (!L0Dec)
    //   continue;
    // if (!Hlt1Dec)
    //   continue;
    // if (!Hlt2Dec)
    //   continue;

    TIS = (Tree.D0_L0Global_TIS && Tree.D0_Hlt1Global_TIS && Tree.D0_Hlt2Global_TIS);
    TOS = L0Dec && Hlt1Dec && Hlt2Dec;

    dtr_pt.clear();
    dtr_id.clear();
    dtr_rap.clear();
    dtr_3charge.clear();

    float min_dr = 999;
    int n_mindr_cand = -999;
    int n_mindr_entry = -999;

    TLorentzVector HFjet, recojet, tr_truthjet, HFmeson, Kaon, pi0, Phi, pion;
    TLorentzVector tr_HFjet, tr_pion, tr_pi0, tr_Kaon, tr_HFmeson, tr_HFmeson_injet;

    // vector<PseudoJet> jetdtrs, tr_jetdtrs;
    // TLorentzVector recojet, tr_HFjet, HFjet;
    Kaon.SetPxPyPzE(Tree.K_PX / 1000., Tree.K_PY / 1000., Tree.K_PZ / 1000., Tree.K_PE / 1000.);
    pi0.SetPxPyPzE(Tree.pi0_PX / 1000., Tree.pi0_PY / 1000., Tree.pi0_PZ / 1000., Tree.pi0_PE / 1000.);
    pion.SetPxPyPzE(Tree.pi_PX / 1000., Tree.pi_PY / 1000., Tree.pi_PZ / 1000., Tree.pi_PE / 1000.);
    HFmeson = Kaon + pi0 + pion;

    double pi0_mass = 0.1349770;
    double pi0_energy = sqrt(pi0_mass * pi0_mass + (pi0.Px() * pi0.Px() + pi0.Py() * pi0.Py() + pi0.Pz() * pi0.Pz()));
    TLorentzVector pi0_DTF(pi0.Px(), pi0.Py(), pi0.Pz(), pi0_energy);
    TLorentzVector HF_DTF = pion + Kaon + pi0_DTF;
    // cout << pion.M() << ", " << Kaon.M() << ", " << pi0.M() << ", " << pi0_DTF.M() << endl;

    // if (Kaon.M() == 0.493677 || pi0.M() == 0.493677)
    //     cout << Kaon.M() << ", " << pi0.M() << endl;
    HFjet.SetPxPyPzE(Tree.Jet_PX / 1000.,
                     Tree.Jet_PY / 1000.,
                     Tree.Jet_PZ / 1000.,
                     Tree.Jet_PE / 1000.);

    // cout<<tr_truepi0px<<",";
    tr_HFjet.SetPxPyPzE(Tree.Jet_mcjet_PX / 1000.,
                        Tree.Jet_mcjet_PY / 1000.,
                        Tree.Jet_mcjet_PZ / 1000.,
                        Tree.Jet_mcjet_PE / 1000.);

    tr_Kaon.SetPxPyPzE(Tree.K_TRUEP_X / 1000., Tree.K_TRUEP_Y / 1000.,
                       Tree.K_TRUEP_Z / 1000., Tree.K_TRUEP_E / 1000.);
    tr_pi0.SetPxPyPzE(Tree.pi0_TRUEP_X / 1000., Tree.pi0_TRUEP_Y / 1000.,
                      Tree.pi0_TRUEP_Z / 1000., Tree.pi0_TRUEP_E / 1000.);
    tr_pion.SetPxPyPzE(Tree.pi_TRUEP_X / 1000., Tree.pi_TRUEP_Y / 1000.,
                       Tree.pi_TRUEP_Z / 1000., Tree.pi_TRUEP_E / 1000.);

    HFmeson = Kaon + pi0 + pion;
    Phi = Kaon + pi0;
    // Phi.SetPxPyPzE(Tree.Phi_PX / 1000., Tree.Phi_PY / 1000., Tree.Phi_PZ / 1000., Tree.Phi_PE / 1000.);
    tr_HFmeson = tr_Kaon + tr_pi0 + tr_pion;

    // cout << HFmeson.Pt() << ", ";

    // if (HFjet.Pt() < 20)
    //   continue;

    // if (Tree.eventNumber == 1668999)
    //   cout << HFjet.Pt() << ", " << tr_HFjet.Pt() << endl;

    if (DoJES == 1)
    {
      float rand = 1.026;
      HFjet -= HFmeson;
      HFjet.SetPx(HFjet.Px() * rand);
      HFjet.SetPy(HFjet.Py() * rand);
      HFjet.SetPz(HFjet.Pz() * rand);
      HFjet.SetE(HFjet.E() * rand);
      HFjet += HFmeson;
    }
    else if (DoJES == 2)
    {
      float rand = 0.974;
      HFjet -= HFmeson;
      HFjet.SetPx(HFjet.Px() * rand);
      HFjet.SetPy(HFjet.Py() * rand);
      HFjet.SetPz(HFjet.Pz() * rand);
      HFjet.SetE(HFjet.E() * rand);
      HFjet += HFmeson;
    }

    if (DoJER)
    {
      float rand = myRNG->Gaus(1, 0.114);
      HFjet -= HFmeson;
      HFjet.SetPx(HFjet.Px() * rand);
      HFjet.SetPy(HFjet.Py() * rand);
      HFjet.SetPz(HFjet.Pz() * rand);
      HFjet.SetE(HFjet.E() * rand);
      HFjet += HFmeson;
    }

    if (DoJetID)
    {
      double mpt = 0;
      int num_trk = 0;
      int num_neut = 0;
      int num_part = 0;
      double mtf = 0;
      for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
      {

        if (fabs(Tree.Jet_Dtr_ThreeCharge[dtrs0]) == 0)
        {
          num_neut++;
        }
        else
        {
          num_trk++;
        }
      }
      // double cpf = (double)num_trk / (double)num_part;
      // mtf /= Zjet.E();
      // std::cout << "cpf = " << cpf << std::endl;
      // std::cout << "mtf = " << mtf << std::endl;
      // std::cout << "mpt = " << mpt << std::endl;

      if (num_trk < 2)
        continue;
    }

    // cout << tr_HFmeson.M() << ",";

    dtf_mass = Tree.D0_ConsD0_M[0] / 1000.;
    chi2ndf_dtf = Tree.D0_ConsD0_chi2[0] / Tree.D0_ConsD0_nDOF[0];
    tau_dtf = Tree.D0_ConsD0_pi0_ctau[0];

    nSV = Tree.Jet_SVTag_Nvertices;
    nSV_test = 0;
    HFHardest = true;
    // Phi_ipchi2 = log10(Tree.Phi_IPCHI2_OWNPV);
    pi_ipchi2 = (Tree.pi_IPCHI2_OWNPV);

    // if(fabs(HFjet.Pt() - 18.8631) < 1e-4) cout<<HFjet.Eta()<<", "<<HFjet.Pt()<<endl;

    float leading_pT = 0;
    int n_maxpT_cand = -999;
    int n_maxpT_entry = -999;
    int n_HFpt_entry = -999;
    int HF_counter = 0;

    float testjet_phi, testjet_px, testjet_py, testjet_pz, testjet_e;
    int ncand = Tree.nCandidate;

    // FromDsst = false;
    // bool hasHFhadron_matched = false;
    // TLorentzVector tr_Gamma;
    // int gamma_key = -99;
    // NumBHaD0_tr = 0;
    // if (!isData)
    // {
    //   int HFmatchloc = -99;
    //   double ptdiff = 99;
    //   for (int dtrs0 = 0; dtrs0 < Tree.Jet_mcjet_nmcdtrs; dtrs0++)
    //   {
    //     TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
    //                        Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
    //                        Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
    //                        Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);
    //     if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
    //     {
    //       double diff = fabs(dtr.Pt() - HFmeson.Pt());
    //       if (diff < ptdiff)
    //       {
    //         HFmatchloc = dtrs0;
    //         ptdiff = diff;
    //       }
    //       if ((ptdiff / dtr.Pt()) > 0.4)
    //         HFmatchloc = 99;
    //     }
    //   }
    //   // cout << "New event" << endl;
    //   // float ptdiff = 1e3;
    //   TLorentzVector D0_gamma;
    //   int D0_motherid = -999;
    //   for (int dtrs0 = 0; dtrs0 < Tree.Jet_mcjet_nmcdtrs; dtrs0++)
    //   {
    //     bool dtrpass = true;
    //     TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
    //                        Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
    //                        Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
    //                        Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);

    //     if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) != tr_HF_pdgcode)
    //       dtrpass = DtrCuts(dtr, Tree.Jet_mcjet_dtrThreeCharge[dtrs0], 0, 0, chargedJetCut);
    //     if (!dtrpass)
    //       continue;

    //     if (dtrs0 == HFmatchloc)
    //     {
    //       // h2_HFpt_RM->Fill(dtr.Pt(), HFmeson.Pt());
    //       h2_HFpt_RM->Fill(dtr.Pt(), HF_DTF.Pt());
    //       hasHFhadron_matched = true;
    //       tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
    //                                      Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
    //                                      Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
    //                                      Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
    //       tr_HFmeson_injet.SetPxPyPzE(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
    //                                   Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
    //                                   Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
    //                                   Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);
    //       tr_jetdtrs.back().set_user_info(new MyInfo(tr_HF_pdgcode));
    //       // cout << "HF!";
    //     }
    //     else
    //     {
    //       tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
    //                                      Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
    //                                      Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
    //                                      Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
    //       tr_jetdtrs.back().set_user_info(new MyInfo(-999));
    //     }

    //     // if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == tr_HF_pdgcode)
    //     // {

    //     //   NumBHaD0_tr++;
    //     //   NumHFReco_tr++;

    //     //   if (fabs(dtr.Pt() - Tree.D0_TRUEPT / 1000.) < 0.01)
    //     //   {
    //     //     cout << "match: " << HFmeson.Pt() << ", " << Tree.D0_TRUEPT / 1000. << ", " << dtr.Pt() << endl;

    //     //
    //     //     hasHFhadron_matched = true;
    //     //     D0_motherid = Tree.Jet_mcjet_MotherID[dtrs0];
    //     //   }
    //     //   else
    //     //   {
    //     //     cout << "no match: " << HFmeson.Pt() << ", " << Tree.D0_TRUEPT / 1000. << ", " << dtr.Pt() << endl;

    //     //     tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
    //     //                                    Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
    //     //                                    Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
    //     //                                    Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
    //     //     tr_jetdtrs.back().set_user_info(new MyInfo(-999));
    //     //   }
    //     //   // if (fabs(dtr.E() - HFmeson.E()) < ptdiff)
    //     //   // {
    //     //   //   tr_HFmeson_injet.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
    //     //   //   ptdiff = fabs(dtr.E() - HFmeson.E());
    //     //   // }
    //     // }

    //     // jet_Nmcdtrs++;
    //   }
    //   // cout << tr_HFmeson_injet.DeltaR(tr_HFjet, true) << ", " << tr_HFmeson.DeltaR(tr_HFjet, true) << endl;
    //   // if (tr_HFmeson_injet.DeltaR(tr_HFjet, true) > jetradius)
    //   //   hasHFhadron_matched = false;

    //   // if (hasHFhadron_matched)
    //   // {
    //   //   tr_jetdtrs.push_back(PseudoJet(tr_HFmeson_injet.Px(),
    //   //                                  tr_HFmeson_injet.Py(),
    //   //                                  tr_HFmeson_injet.Pz(),
    //   //                                  tr_HFmeson_injet.E()));
    //   //   tr_jetdtrs.back().set_user_info(new MyInfo(tr_HF_pdgcode));
    //   // }
    // }

    bool hasHFhadron = false;

    int NumBHads = 0;

    Ndtr_neutral = 0;
    Ndtr_charged = 0;
    TLorentzVector HFmatch;
    for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    {
      // cout << "(" << Tree.Jet_Dtr_ID[dtrs0] << ", " << Tree.Jet_Dtr_PT[dtrs0] << "), ";

      float trchi2ndf = Tree.Jet_Dtr_TrackChi2[dtrs0] / Tree.Jet_Dtr_TrackNDF[dtrs0];
      float dtr_charge = Tree.Jet_Dtr_ThreeCharge[dtrs0] / 3.;

      TLorentzVector dtr(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.Jet_Dtr_E[dtrs0] / 1000.);
      TLorentzVector tr_dtr(Tree.Jet_Dtr_TRUE_PX[dtrs0] / 1000.,
                            Tree.Jet_Dtr_TRUE_PY[dtrs0] / 1000.,
                            Tree.Jet_Dtr_TRUE_PZ[dtrs0] / 1000.,
                            Tree.Jet_Dtr_TRUE_E[dtrs0] / 1000.);

      bool dtrpass = true;

      // if (Tree.Jet_Dtr_ID[dtrs0] == 22)
      //   cout << dtr.P() << ", " << dtr.Pt() << endl;

      // if (DoFSPPT && (abs(Tree.Jet_Dtr_ID[dtrs0]) != HF_pdgcode))
      // {
      //   SmearDtrPt(dtr, Tree.Jet_Dtr_ThreeCharge[dtrs0], Tree.Jet_Dtr_ID[dtrs0], myRNG);
      // }

      // if (abs(Tree.Jet_Dtr_ID[dtrs0]) != HF_pdgcode)
      //   dtrpass = DtrCuts(dtr, dtr_charge, Tree.Jet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
      // if (!dtrpass)
      //   continue;

      // if (DoFSPEff && (abs(Tree.Jet_Dtr_ID[dtrs0]) != HF_pdgcode))
      // {
      //   float track_sys = 0.0155;
      //   float neutral_sys = 0.04;
      //   bool drop = false;
      //   if (fabs(Tree.Jet_Dtr_ThreeCharge[dtrs0]) > 0)
      //   {
      //     drop = DropFSP(track_sys, myUniform);
      //   }
      //   else
      //   {
      //     drop = DropFSP(neutral_sys, myUniform);
      //   }
      //   if (drop)
      //     continue;
      // }

      // jetdtrs.push_back(PseudoJet(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
      //                             Tree.Jet_Dtr_PY[dtrs0] / 1000.,
      //                             Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
      //                             Tree.Jet_Dtr_E[dtrs0] / 1000.));
      // jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_Dtr_ID[dtrs0]));

      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        HFmatch.SetPxPyPzE(Tree.Jet_Dtr_TRUE_PX[dtrs0] / 1000.,
                           Tree.Jet_Dtr_TRUE_PY[dtrs0] / 1000.,
                           Tree.Jet_Dtr_TRUE_PZ[dtrs0] / 1000.,
                           Tree.Jet_Dtr_TRUE_E[dtrs0] / 1000.);

        // cout << Tree.Jet_Dtr_TRUE_ID[dtrs0] << endl;
        hasHFhadron = true;
        NumBHads++;
        NumHFReco++;
      }
      if (Tree.Jet_Dtr_ThreeCharge[dtrs0] == 0)
        Ndtr_neutral++;
      else if (abs(Tree.Jet_Dtr_ID[dtrs0]) != HF_pdgcode)
        Ndtr_charged++;
      dtr_id.push_back(Tree.Jet_Dtr_ID[dtrs0]);
      dtr_pt.push_back(dtr.Pt());
      dtr_rap.push_back(dtr.Rapidity());
      dtr_3charge.push_back(Tree.Jet_Dtr_ThreeCharge[dtrs0]);
    }

    if (!hasHFhadron)
    {
      continue;
    }

    bool hasHFhadron_matched = false;
    NumBHaD0_tr = 0;
    bool hasb = false;
    bool hasbbar = false;

    if (!isData)
    {
      float ptdiff = 1e3;

      for (int dtrs0 = 0; dtrs0 < Tree.Jet_mcjet_nmcdtrs; dtrs0++)
      {
        float trchi2ndf = 0;
        // cout<<Tree.Jet_mcjet_dtrID[dtrs0]<<",";
        TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
                           Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
                           Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
                           Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);

        bool dtrpass = true;

        // if (dtr.DeltaR(tr_HFjet, true) > jetradius)
        //     continue;

        //                tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
        //                                               Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
        //                                               Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
        //                                               Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
        //                tr_jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_mcjet_dtrID[dtrs0]));

        if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
        {
          // cout << "true = " << dtr.Px() << ", " << dtr.Py() << ", " << dtr.Pz() << ", " << dtr.E() << ", " << dtr.Pt() << endl;
          NumBHaD0_tr++;
          // if (fabs(dtr.Px() - HFmeson.Px()) < 2 && fabs(dtr.Py() - HFmeson.Py()) < 2)
          // {
          if (fabs(dtr.Pt() - tr_HFmeson.Pt()) < 0.01)
          {
            tr_HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
            hasHFhadron_matched = true;
            // ptdiff = fabs(dtr.E() - HFmeson.E());
          }
          // }
        }

        // jet_Nmcdtrs++;
      }
      // if (tr_HFmeson.DeltaR(tr_HFjet, true) > jetradius)

      // cout<<endl<<tr_HFmeson.Pt()<<endl;
      // if (fabs(HFmeson.Pt() - tr_HFmeson.Pt()) / tr_HFmeson.Pt() > 0.03 && hasHFhadron_matched)
      // {
      //     hasHFhadron_matched = false;
      // }
      // if (fabs(HFmeson.Pt() - tr_HFmeson.Pt()) / tr_HFmeson.Pt() > 0.03)
      //   continue;
    }

    SVTag = 0;
    Hasccbar = false;

    if (Tree.hasc && Tree.hascbar)
    {
      Hasccbar = true;
      if (Tree.Jet_SVTag_Tag)
      {
        SVTag = 1;
      }
    }
    // }

    if (Tree.Jet_SVTag_Tag && !(Tree.hasc && Tree.hascbar))
    {
      SVTag = 2;
    }

    // cout<<"Starting dijet loop";

    // cout << WTA_dist << ", " << tr_WTA_dist << endl;

    // cout << endl
    //      << "New event: " << endl;

    TVector3 HF_meson = HFmeson.Vect();
    TVector3 HF_jet = HFjet.Vect();
    TVector3 tr_HF_meson = tr_HFmeson.Vect();
    TVector3 tr_HF_jet = tr_HFjet.Vect();

    z = (HF_meson.Dot(HF_jet)) / (HF_jet.Mag2());
    jt = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
    r = static_cast<TLorentzVector>(HFmeson).DeltaR(HFjet, kTRUE);

    if (hasHFhadron_matched)
    {
      tr_z = (tr_HF_meson.Dot(tr_HF_jet)) / (tr_HF_jet.Mag2());
      tr_jt = (tr_HF_jet.Cross(tr_HF_meson).Mag()) / (tr_HF_jet.Mag());
      tr_r = static_cast<TLorentzVector>(tr_HFmeson).DeltaR(tr_HFjet, kTRUE);

      if (Hasccbar)
      {
        zg = (tr_HF_meson.Dot(tr_HF_jet)) / (tr_HF_jet.Mag2());
        jtg = (tr_HF_jet.Cross(tr_HF_meson).Mag()) / (tr_HF_jet.Mag());
        rg = static_cast<TLorentzVector>(tr_HFmeson).DeltaR(tr_HFjet, kTRUE);
      }
    }

    jet_pt = HFjet.Pt();
    jet_eta = HFjet.Eta();
    jet_rap = HFjet.Rapidity();
    jet_px = HFjet.Px();
    jet_py = HFjet.Py();
    jet_pz = HFjet.Pz();
    jet_e = HFjet.E();
    HF_px = HFmeson.Px();
    HF_py = HFmeson.Py();
    HF_pz = HFmeson.Pz();
    HF_e = HFmeson.E();
    HF_pt = HFmeson.Pt();
    HF_m = HFmeson.M();

    D0_CHI2NDOF = Tree.D0_ENDVERTEX_CHI2 / Tree.D0_ENDVERTEX_NDOF;
    D0_IPCHI2 = Tree.D0_IPCHI2_OWNPV;
    // D0_CHI2 = Tree.D0_OWNPV_CHI2;
    D0_CHI2 = Tree.D0_ENDVERTEX_CHI2;
    D0_mass = HFmeson.M();

    pi0_px = pi0.Px();
    pi0_py = pi0.Py();
    pi0_pz = pi0.Pz();
    pi0_e = pi0.E();

    K_px = Kaon.Px();
    K_py = Kaon.Py();
    K_pz = Kaon.Pz();
    K_e = Kaon.E();
    K_PIDK = Tree.K_PIDK;
    K_CHI2NDOF = Tree.K_TRACK_CHI2NDOF;
    K_GHOSTPROB = Tree.K_TRACK_GhostProb;
    K_IPCHI2 = Tree.K_IPCHI2_OWNPV;

    pi_px = pion.Px();
    pi_py = pion.Py();
    pi_pz = pion.Pz();
    pi_e = pion.E();
    pi_p = pion.P() * 1000;
    pi_eta = pion.Eta();
    pi_CHI2NDOF = Tree.pi_TRACK_CHI2NDOF;
    pi_GHOSTPROB = Tree.pi_TRACK_GhostProb;
    pi_IPCHI2 = Tree.pi_IPCHI2_OWNPV;
    pi_PIDK = Tree.pi_PIDK;

    // Phi_px = Phi.Px();
    // Phi_py = Phi.Py();
    // Phi_pz = Phi.Pz();
    // Phi_e = Phi.E();
    // Phi_CHI2NDOF = Tree.Phi_ENDVERTEX_CHI2 / Tree.Phi_ENDVERTEX_NDOF;
    // Phi_IPCHI2 = Tree.Phi_IPCHI2_OWNPV;
    // Phi_CHI2 = Tree.Phi_ENDVERTEX_CHI2;
    // Phi_FDCHI2 = Tree.Phi_FDCHI2_OWNPV;
    // Phi_BPVDLS = Tree.Phi_BPVDLS;

    nTracks = Tree.nTracks;
    nSPDHits = Tree.nSPDHits;
    ndtrs_noghost = Tree.Jet_Dtr_nrecodtr;

    // ndtrs = jetdtrs.size();
    // nsplits = kts.size();

    tr_jet_eta = tr_HFjet.Eta();
    tr_jet_rap = tr_HFjet.Rapidity();
    tr_jet_pt = tr_HFjet.Pt();
    tr_jet_px = tr_HFjet.Px();
    tr_jet_py = tr_HFjet.Py();
    tr_jet_pz = tr_HFjet.Pz();
    tr_jet_e = tr_HFjet.E();

    tr_HF_pt = tr_HFmeson.Pt();
    tr_HF_px = tr_HFmeson.Px();
    tr_HF_py = tr_HFmeson.Py();
    tr_HF_pz = tr_HFmeson.Pz();
    tr_HF_e = tr_HFmeson.E();

    tr_pi0_px = tr_pi0.Px();
    tr_pi0_py = tr_pi0.Py();
    tr_pi0_pz = tr_pi0.Pz();
    tr_pi0_e = tr_pi0.E();
    tr_K_px = tr_Kaon.Px();
    tr_K_py = tr_Kaon.Py();
    tr_K_pz = tr_Kaon.Pz();
    tr_K_e = tr_Kaon.E();
    tr_pi_px = tr_pion.Px();
    tr_pi_py = tr_pion.Py();
    tr_pi_pz = tr_pion.Pz();
    tr_pi_e = tr_pion.E();

    // tr_ndtrs = tr_jetdtrs.size();
    // tr_nsplits = tr_kts.size();

    K_realET = Tree.K_L0Calo_HCAL_realET;

    if (hasHFhadron_matched)
      isTrueDjet = true;
    else
      isTrueDjet = false;

    if (last_eventNum == Tree.eventNumber)
      NumSame++;
    last_eventNum = Tree.eventNumber;
    eventNumber = Tree.eventNumber;

    // cout << endl;

    // if (fabs(HFmeson.Pt() - tr_HFmeson_injet.Pt()) / tr_HFmeson_injet.Pt() > 0.03)
    // if (tr_HFjet.DeltaR(HFjet, kTRUE) > 0.15 && hasHFhadron_matched)
    // {
    //     if (tr_HFmeson_injet.Pt() > 0)
    //     {
    //         cout << "------------------------------------------" << endl;
    //         cout << "Kaon :" << Kaon.Pt() << ", " << tr_Kaon.Pt() << endl;
    //         cout << "pi0 :" << pi0.Pt() << ", " << tr_pi0.Pt() << endl;
    //         cout << "pi :" << pion.Pt() << ", " << tr_pion.Pt() << endl;
    //         cout << "HFmeson :" << HFmeson.Pt() << ", " << tr_HFmeson.Pt() << endl;
    //         cout << "HFmeson :" << HFmeson.Pt() << ", " << tr_HFmeson_injet.Pt() << endl;
    //         cout << "DElta R = " << HFjet.DeltaR(tr_HFjet, kTRUE) << endl;
    //         cout << "NumBHaD0_tr = " << NumBHaD0_tr << endl;
    //     }
    // }

    // if (L0Dec)
    // {
    //   cout << Tree.D0_L0HadronDecision_TOS << ", " << Tree.K_L0HadronDecision_TOS << ", " << Tree.pi0_L0HadronDecision_TOS << ", " << Tree.pi_L0HadronDecision_TOS << endl;
    //   cout << Tree.K_L0Calo_HCAL_realET << ", " << Tree.pi0_L0Calo_HCAL_realET << ", " << Tree.pi_L0Calo_HCAL_realET << ", " << trigeff_Kaon << ", " << trigeff_Data << endl;
    // }

    events++;
    if (HFjet.Pt() > 0)
      NumHFjet++;
    if (tr_HFjet.Pt() > 7)
      NumHFjet_tr++;

    // cout << tr_HFjet.Pt() << ", " << HFjet.Pt() << ", ";

    h1_HFMass->Fill(HFmeson.M());
    h1_HFMass_dtf->Fill(Tree.D0_ConsD0_M[0] / 1000.);
    h1_ipchi2->Fill(log10(Tree.D0_IPCHI2_OWNPV));
    DTree->Fill();
    // }
  }

  // gROOT->ProcessLine(".L $LUND/lhcbStyle.C");
  // gROOT->ProcessLine(".x $LUND/lhcbStyle.C");
  // gROOT->ProcessLine(".x lhcbStyle2D.C");
  // -- --paint setup...

  // int ican = -1,
  //     iframe = -1, itext = -1;
  // TCanvas *ccan[1000];
  // TH1F *frame[1000];

  // //
  // Int_t lhcbFont = 132; // Old LHCb style: 62;
  // // Line thickness
  // float_t lhcbWidth = 2.00; // Old LHCb style: 3.00;
  // // Text size
  // float_t lhcbTSize = 0.06;

  // // gROOT->SetStyle("Plain");
  // // gStyle->SetCanvasDefH(1414);
  // // gStyle->SetCanvasDefW(1000);
  // gStyle->SetPadBottomMargin(0.08);
  // gStyle->SetPadTopMargin(0.08);
  // gStyle->SetPadLeftMargin(0.12);
  // gStyle->SetPadRightMargin(0.12);
  // gStyle->SetTitleStyle(0);
  // gStyle->SetStatStyle(0);
  // // gStyle->SetLineWidth(3);
  // // gStyle->SetOptStat(0);
  // //---- paint...
  // char buf[100];
  // char bufb[100];
  // TString rootfile;
  // TString plotfile;
  // TString plotfilePDF;
  // TString plotfileO;
  // TString plotfileC;
  // // TString OutputFileBase	= outbase+outinfo;
  // rootfile = TString(dir_deadcone + "hists/") + extension + TString(".root");
  // plotfile = TString(dir_deadcone + "plots/") + extension + TString(".ps");
  // plotfilePDF = TString(dir_deadcone + "plots/") + extension + TString(".pdf");
  // plotfileO = plotfilePDF + TString("(");
  // plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

  // c1->SaveAs(Form("plots_misc/Misc_%s"+extension+".pdf", file_name.c_str()));
  // cout<<"...outbase   = "<<outbase.Data()<<endl;
  // cout<<"...rootfile  = "<<rootfile.Data()<<endl;
  // cout<<"...plotfile  = "<<plotfile.Data()<<endl;

  // //
  //
  // ++ican;
  // sprintf(buf, "ccan%d", ican);
  // ccan[ican] = new TCanvas(buf, buf, 1);
  // ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  // gPad->SetRightMargin(0.15);
  // ccan[ican]->cd();
  // ccan[ican]->Divide(2, 2);

  // ccan[ican]->cd(1);
  // h2_HFpt_RM->Draw("COLZ");
  // gPad->SetLogz();

  // ccan[ican]->cd(2);
  // SetTruthStyle(h1_HFMass);
  // SetRecoStyle(h1_HFMass_dtf);
  // h1_HFMass_dtf->Draw("SAME");
  // h1_HFMass->Draw("SAME");

  // ccan[ican]->cd(2);
  // TFile f_trig(dir_deadcone + "hists/" + "D0_trigData_fits" + ".root", "RECREATE");
  // f_trig.cd();
  // for (int i = 0; i < HFetabinsize; i++)
  // {
  //   cout << "i = " << i << endl;
  //   TF1 *fit = new TF1(Form("trigeffMCfit%d", i), "[0]*tanh([1]*(x-[3]))+[2]", 0., 100);
  //   TF1 *fit_pur = new TF1(Form("fit_pur%d", i), "[0]*tanh([1]*(x-[3]))+[2]", 0., 100);
  //   fit->SetParameters(0.767461, 0.0590819, -0.121837, -7.07847);
  //   fit->SetParLimits(0, 0, 2.0);

  //   // fit_pur->SetParameters(0.967461, 0.0590819, -0.121837, -7.07847);
  //   // fit_pur->SetParLimits(0, 0, 0.4);
  //   TH1D *h1_temp = (TH1D *)h2_trigeff_Data->ProjectionX(Form("htemp%d_trigeffMC", i), i + 1, i + 1);
  //   // TH1D *h1_temp_pur = (TH1D *)h2_purity_HFpteta->ProjectionX(Form("htemp_pur%d_HFpteta", i), i + 1, i + 1);

  //   h1_temp->SetMarkerStyle(i + 23);
  //   h1_temp->SetMarkerColor(i + 4);
  //   h1_temp->SetLineColor(i + 4);
  //   h1_temp->Draw("P E SAME");
  //   h1_temp->SetMinimum(0.);
  //   h1_temp->SetMaximum(1.05);
  //   fit->SetLineColor(i + 4);

  //   h1_temp->Fit(Form("trigeffMCfit%d", i), "E", "", 2., 100);
  //   fit->Write(Form("trigeffMCfit%d", i));

  //   // h1_temp_pur->Fit(Form("fit_pur%d", i), "E", "", 0, 100);
  //   // fit_pur->Write(Form("fit_pur%d", i));
  // }
  // f_trig.Write();
  // f_trig.Close();

  // ccan[ican]->cd(4);
  // h1_ipchi2->Draw("SAME");

  // ccan[ican]->cd();
  // ccan[ican]->Update();
  // if (ican == 0)
  // {
  //   ccan[ican]->Print(plotfileO.Data());
  // }
  // else
  // {
  //   ccan[ican]->Print(plotfilePDF.Data());
  // }

  // if (ican > -1)
  // {
  //   cout << " You plotted " << ican + 1 << " canvasses......." << endl;
  //   ccan[ican]->Print(plotfileC.Data());
  // }

  f.Write();
  f.Close();

  // cout << "No Trigger = " << ev_notrig << endl;
  // cout << "L0 Trigger = " << ev_L0 << endl;
  // cout << "L0 + Hlt1 Trigger = " << ev_Hlt1 << endl;
  // cout << "L0 + Hlt1 + Hlt2 Trigger = " << ev_Hlt2 << endl;
  cout << "Num TWO HF in Jet = " << NumTwoHFInJet << endl;
  cout << "Num More than 1 jet in event = " << NumTwoCand << endl;
  cout << "Num Djets from same event = " << NumSame << endl;

  cout << "NumHFReco = " << NumHFReco << endl;
  cout << "NumBhads = " << NumHFReco << ", Num B hads tr = " << NumHFReco_tr << endl;
  cout << "Num jets = " << NumHFjet << ", Num jets tr = " << NumHFjet_tr << endl;

  cout << "Number of saved events = " << events << endl;

  cout << "Percentage of excited Ds decays in truth = " << (double)NumD0_star / (double)NumD0_all << endl;
  cout << "Percentage of excited Ds decays eliminated = " << (double)NumDetected / (double)NumDsst << endl;
  cout << "Percentage of excited Ds decays in reco = " << (double)NumDsst / (double)events << endl;
}

int main(int argc, char *argv[])
{

  int NumEvts = -1;
  int dataset = 90499;
  bool isData = true;
  bool chargedJetCut = false;
  bool DoJER = false;
  int DoJES = 0;
  bool DoFSPEff = false;
  bool DoFSPPT = false;
  bool DoGhostCut = false;
  int PromptCut = false;

  // Parsing command line arguments
  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg == "-h")
    {
      // Print help message explaining the options
      std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
      std::cout << "Options:" << std::endl;
      std::cout << "  -n <NumEvts>       : Number of events" << std::endl;
      std::cout << "  -dataset <dataset> : Dataset number" << std::endl;
      std::cout << "  -isdata <isData>   : Whether the dataset is real data (0 or 1)" << std::endl;
      std::cout << "  -charge <chargedJetCut> : Whether to apply charged jet cut (0 or 1)" << std::endl;
      std::cout << "  -jer <DoJER>       : Whether to apply JER (0 or 1)" << std::endl;
      std::cout << "  -jes <DoJES>       : JES variation (integer)" << std::endl;
      std::cout << "  -fsppt <DoFSPPT>     : Whether to apply track pT cut (0 or 1)" << std::endl;
      std::cout << "  -ghost <DoGhostCut>       : Whether to apply ghost cut (0 or 1)" << std::endl;
      std::cout << "  -fspeff <DoFSPEff>       : Whether to apply full simulation efficiency (0 or 1)" << std::endl;
      std::cout << "  -trackeff <DoTrackEff>   : Track efficiency variation (integer)" << std::endl;
      std::cout << "  -trig <DoTrigEff>        : Whether to apply trigger efficiency (0 or 1)" << std::endl;
      std::cout << "  -pideff <DoPIDEff>       : PID efficiency variation (integer)" << std::endl;
      std::cout << "  -recsel <DoRecSelEff>    : Whether to apply reconstruction selection efficiency (0 or 1)" << std::endl;
      std::cout << "  -massfit <DoMassFit>     : Whether to perform mass fitting (0 or 1)" << std::endl;
      std::cout << "  -subtractGS <SubtractGS> : Whether to subtract ghost signals (0 or 1)" << std::endl;
      return 0;
    }
    else if (arg == "-n")
    {
      if (i + 1 < argc)
      {
        NumEvts = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-n option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-dataset")
    {
      if (i + 1 < argc)
      {
        dataset = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-dataset option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-isdata")
    {
      std::cout << argv[i + 1] << std::endl;
      if (i + 1 < argc)
      {
        isData = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-isdata option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-charge")
    {
      if (i + 1 < argc)
      {
        chargedJetCut = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-charge option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-prompt")
    {
      if (i + 1 < argc)
      {
        PromptCut = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-prompt option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-jer")
    {
      if (i + 1 < argc)
      {
        DoJER = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-jer option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-fspeff")
    {
      if (i + 1 < argc)
      {
        DoFSPEff = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-fspeff option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-fsppt")
    {
      if (i + 1 < argc)
      {
        DoFSPPT = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-fsppt option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-ghost")
    {
      if (i + 1 < argc)
      {
        DoGhostCut = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-ghost option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-jes")
    {
      if (i + 1 < argc)
      {
        DoJES = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-jes option requires one argument." << std::endl;
        return 1;
      }
    }
    else
    {
      std::cerr << "Unknown option: " << arg << std::endl;
      return 1;
    }
  }

  MakeVarTree(NumEvts,
              dataset,
              isData,
              chargedJetCut,
              DoJER,
              DoJES,
              DoFSPEff,
              DoFSPPT,
              DoGhostCut,
              PromptCut);
  return 0;
}
//
