

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include "BjetTree.C"
#include "BjetMCTree.C"
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
// #include "../RooHelpers.h"
#include "../LundGen.hh"

using namespace fastjet;
using namespace std;

void MakeVarTree(int NumEvts_user = 10000, 
                 int dataset = 1510, 
                 bool isData = true,
                 bool chargedJetCut_user = false,
                 bool DoJER = false,
                 int DoJES = 0,
                 bool DoTrackEff = false,
                 bool DoTrackPt = false,
                 bool DoGhostCut = false)
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

  TString extension, extension_eff;
  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
  extension_eff = TString("fspeff_") + "truth" + Form("_ev_%d", -1) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_flavor + Form("_%d", 91599);

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

  BjetTree Tree(0, dataset, isData);
  BjetTree Tree_DiMuon(0, 11511, isData);
  // HFjetTree TreeAnti(0, dataset, !isData);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  cout << "Executing CAJetAlgo" << endl;
  double dtr_rap;
  double dtr_phi;
  double delta_rap;
  double delta_phi;

  TString dir_deadcone("$LUND/Bjets/");

  TFile file_eff(dir_deadcone + "hists/" + extension_eff + ".root", "READ");
  TH2D *h2_trk_eff;
  TH2D *h2_neut_eff;
  h2_trk_eff = (TH2D *)file_eff.Get("trk_eff_sys");
  h2_neut_eff = (TH2D *)file_eff.Get("neut_eff_sys");

  TFile f(dir_deadcone + "hists/" + extension + ".root", "RECREATE");

  double small_radius = 0.2;
  JetDefinition jet_def(cambridge_algorithm, jetradius);
  JetDefinition small_jets(antikt_algorithm, small_radius);
  PseudoJet dtr1, dtr2;

  double jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  double jet_rap, tr_jet_rap;
  double jet_px, jet_py, jet_pz, jet_e, jet_charge;
  double HF_px, HF_py, HF_pz, HF_e, HF_pt;
  double Z_px, Z_py, Z_pz, Z_e;
  double mup_px, mup_py, mup_pz, mup_e;
  double mum_px, mum_py, mum_pz, mum_e;
  double K_px, K_py, K_pz, K_e;
  double jpsi_ipchi2;
  double Bfromjet_px, Bfromjet_py, Bfromjet_pz, Bfromjet_e;

  double tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  double tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e, tr_HF_pt;
  double tr_mup_px, tr_mup_py, tr_mup_pz, tr_mup_e;
  double tr_mum_px, tr_mum_py, tr_mum_pz, tr_mum_e;
  double tr_K_px, tr_K_py, tr_K_pz, tr_K_e;

  int nsplits, ndtrs, NumSubJets;
  int tr_nsplits, tr_ndtrs;
  int nSV, nSV_test;
  bool isTrueBjet, isBacktoBack, HFHardest, Hasbbbar;
  double dphi, Bmass_1, Bmass_2;
  double bmass_dtf, dtf_chi2ndf;
  int NumBHads_tr, eventNumber;

  vector<double> thetas, tr_thetas;
  vector<double> ktthetas, tr_ktthetas;
  vector<double> dRs, tr_dRs;
  vector<double> Erads, tr_Erads;
  vector<double> kts, tr_kts;
  vector<double> zs, tr_zs;
  vector<double> raps, tr_raps;
  vector<double> phis, tr_phis;
  vector<bool> hardest, tr_hardest;
  // TLorentzVector
  TTree *LundTree = new TTree("LundTree", "Lund Tree Variables");

  LundTree->Branch("eventNumber", &eventNumber);
  LundTree->Branch("thetas", &thetas);
  LundTree->Branch("ktthetas", &ktthetas);
  LundTree->Branch("Erads", &Erads);
  LundTree->Branch("dRs", &dRs);
  LundTree->Branch("kts", &kts);
  LundTree->Branch("zs", &zs);
  LundTree->Branch("raps", &raps);
  LundTree->Branch("phis", &phis);
  LundTree->Branch("hardest", &hardest);

  LundTree->Branch("jet_pt", &jet_pt);
  LundTree->Branch("jet_eta", &jet_eta);
  LundTree->Branch("jet_rap", &jet_rap);

  LundTree->Branch("jet_px", &jet_px);
  LundTree->Branch("jet_py", &jet_py);
  LundTree->Branch("jet_pz", &jet_pz);
  LundTree->Branch("jet_e", &jet_e);

  LundTree->Branch("jet_charge", &jet_charge);

  LundTree->Branch("HF_px", &HF_px);
  LundTree->Branch("HF_py", &HF_py);
  LundTree->Branch("HF_pz", &HF_pz);
  LundTree->Branch("HF_e", &HF_e);
  LundTree->Branch("HF_pt", &HF_pt);

  LundTree->Branch("ndtrs", &ndtrs);
  LundTree->Branch("nsplits", &nsplits);

  LundTree->Branch("mum_px", &mum_px);
  LundTree->Branch("mum_py", &mum_py);
  LundTree->Branch("mum_pz", &mum_pz);
  LundTree->Branch("mum_e", &mum_e);

  LundTree->Branch("mup_px", &mup_px);
  LundTree->Branch("mup_py", &mup_py);
  LundTree->Branch("mup_pz", &mup_pz);
  LundTree->Branch("mup_e", &mup_e);

  LundTree->Branch("K_px", &K_px);
  LundTree->Branch("K_py", &K_py);
  LundTree->Branch("K_pz", &K_pz);
  LundTree->Branch("K_e", &K_e);

  LundTree->Branch("jpsi_ipchi2", &jpsi_ipchi2);

  LundTree->Branch("Bfromjet_px", &Bfromjet_px);
  LundTree->Branch("Bfromjet_py", &Bfromjet_py);
  LundTree->Branch("Bfromjet_pz", &Bfromjet_pz);
  LundTree->Branch("Bfromjet_e", &Bfromjet_e);

  LundTree->Branch("tr_thetas", &tr_thetas);
  LundTree->Branch("tr_ktthetas", &tr_ktthetas);
  LundTree->Branch("tr_Erads", &tr_Erads);
  LundTree->Branch("tr_dRs", &tr_dRs);
  LundTree->Branch("tr_kts", &tr_kts);
  LundTree->Branch("tr_zs", &tr_zs);
  LundTree->Branch("tr_raps", &tr_raps);
  LundTree->Branch("tr_phis", &tr_phis);
  LundTree->Branch("tr_hardest", &tr_hardest);

  LundTree->Branch("tr_jet_pt", &tr_jet_pt);
  LundTree->Branch("tr_jet_eta", &tr_jet_eta);
  LundTree->Branch("tr_jet_rap", &tr_jet_rap);

  LundTree->Branch("tr_jet_px", &tr_jet_px);
  LundTree->Branch("tr_jet_py", &tr_jet_py);
  LundTree->Branch("tr_jet_pz", &tr_jet_pz);
  LundTree->Branch("tr_jet_e", &tr_jet_e);

  LundTree->Branch("tr_HF_px", &tr_HF_px);
  LundTree->Branch("tr_HF_py", &tr_HF_py);
  LundTree->Branch("tr_HF_pz", &tr_HF_pz);
  LundTree->Branch("tr_HF_e", &tr_HF_e);
  LundTree->Branch("tr_HF_pt", &tr_HF_pt);

  LundTree->Branch("tr_mum_px", &tr_mum_px);
  LundTree->Branch("tr_mum_py", &tr_mum_py);
  LundTree->Branch("tr_mum_pz", &tr_mum_pz);
  LundTree->Branch("tr_mum_e", &tr_mum_e);

  LundTree->Branch("tr_mup_px", &tr_mup_px);
  LundTree->Branch("tr_mup_py", &tr_mup_py);
  LundTree->Branch("tr_mup_pz", &tr_mup_pz);
  LundTree->Branch("tr_mup_e", &tr_mup_e);

  LundTree->Branch("tr_K_px", &tr_K_px);
  LundTree->Branch("tr_K_py", &tr_K_py);
  LundTree->Branch("tr_K_pz", &tr_K_pz);
  LundTree->Branch("tr_K_e", &tr_K_e);

  LundTree->Branch("tr_ndtrs", &tr_ndtrs);
  LundTree->Branch("tr_nsplits", &tr_nsplits);
  LundTree->Branch("isTrueBjet", &isTrueBjet);

  LundTree->Branch("dphi", &dphi);
  LundTree->Branch("Bmass_1", &Bmass_1);
  LundTree->Branch("Bmass_2", &Bmass_2);
  LundTree->Branch("nSV", &nSV);
  LundTree->Branch("nSV_test", &nSV_test);
  LundTree->Branch("HFHardest", &HFHardest);
  LundTree->Branch("bmass_dtf", &bmass_dtf);
  LundTree->Branch("dtf_chi2ndf", &dtf_chi2ndf);
  LundTree->Branch("NumSubJets", &NumSubJets);
  LundTree->Branch("NumBHads_tr", &NumBHads_tr);
  LundTree->Branch("Hasbbbar", &Hasbbbar);

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //

  int eventNum;
  unsigned long long last_eventNum = 0;
  int events = 0;

  bool maxjetpT_found = false;
  bool maxHFpT_found = false;
  int cut_npvs = 0;
  int cut_jetpt = 0;
  int cut_jeteta = 0;
  int cut_Dinjet = 0;
  int cut_prompt = 0;
  int cut_hasHF = 0;
  int Num_Bmatched = 0;
  int OneJet = 0;
  int ManyJets = 0;
  int NumTwoHFInJet = 0;
  int NumTwoCand = 0;
  int N_num = 0;
  int N_denom = 0;
  double last_HFpt = 0;
  double last_HFjet = 0;
  int ev_min = 0;
  int NumSame = 0;

  TRandom3 *myUniform = new TRandom3();
  TRandom3 *myRNG = new TRandom3();

  for (int ev = ev_min; ev < NumEvts + ev_min; ev++)
  {
    Tree.GetEntry(ev);
    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;

    if (ev != 0)
    {
      if (Tree.eventNumber == last_eventNum)
      {
        continue;
      }
    }
    // if(maxjetpT_found) continue;
    // if(maxHFpT_found) continue;
    double min_dr = 999;
    int n_mindr_cand = -999;
    int n_mindr_entry = -999;

    TLorentzVector HFjet, recojet, tr_truthjet, HFmeson, mup, mum, Kmeson;
    TLorentzVector tr_HFjet, tr_Kmeson, tr_mum, tr_mup, tr_HFmeson;

    vector<PseudoJet> jetdtrs, tr_jetdtrs;
    // TLorentzVector recojet, tr_HFjet, HFjet;
    mup.SetPxPyPzE(Tree.mup_PX / 1000., Tree.mup_PY / 1000., Tree.mup_PZ / 1000., Tree.mup_PE / 1000.);
    mum.SetPxPyPzE(Tree.mum_PX / 1000., Tree.mum_PY / 1000., Tree.mum_PZ / 1000., Tree.mum_PE / 1000.);
    Kmeson.SetPxPyPzE(Tree.K_PX / 1000., Tree.K_PY / 1000., Tree.K_PZ / 1000., Tree.K_PE / 1000.);

    HFjet.SetPxPyPzE(Tree.Jet_PX / 1000.,
                     Tree.Jet_PY / 1000.,
                     Tree.Jet_PZ / 1000.,
                     Tree.Jet_PE / 1000.);

    // cout<<tr_truemumpx<<",";
    tr_HFjet.SetPxPyPzE(Tree.Jet_mcjet_PX / 1000.,
                        Tree.Jet_mcjet_PY / 1000.,
                        Tree.Jet_mcjet_PZ / 1000.,
                        Tree.Jet_mcjet_PE / 1000.);

    tr_mup.SetPxPyPzE(Tree.mup_TRUEP_X / 1000., Tree.mup_TRUEP_Y / 1000.,
                      Tree.mup_TRUEP_Z / 1000., Tree.mup_TRUEP_E / 1000.);
    tr_mum.SetPxPyPzE(Tree.mum_TRUEP_X / 1000., Tree.mum_TRUEP_Y / 1000.,
                      Tree.mum_TRUEP_Z / 1000., Tree.mum_TRUEP_E / 1000.);
    tr_Kmeson.SetPxPyPzE(Tree.K_TRUEP_X / 1000., Tree.K_TRUEP_Y / 1000.,
                         Tree.K_TRUEP_Z / 1000., Tree.K_TRUEP_E / 1000.);

    HFmeson = mup + mum + Kmeson;
    tr_HFmeson = tr_mup + tr_mum + tr_Kmeson;

    if (DoJES == 1)
    {
      double rand = 1.026;
      HFjet -= HFmeson;
      HFjet.SetPx(HFjet.Px() * rand);
      HFjet.SetPy(HFjet.Py() * rand);
      HFjet.SetPz(HFjet.Pz() * rand);
      HFjet.SetE(HFjet.E() * rand);
      HFjet += HFmeson;
    }
    else if (DoJES == 2)
    {
      double rand = 0.974;
      HFjet -= HFmeson;
      HFjet.SetPx(HFjet.Px() * rand);
      HFjet.SetPy(HFjet.Py() * rand);
      HFjet.SetPz(HFjet.Pz() * rand);
      HFjet.SetE(HFjet.E() * rand);
      HFjet += HFmeson;
    }

    if (DoJER)
    {
      double rand = myRNG->Gaus(1, 0.103);
      HFjet -= HFmeson;
      HFjet.SetPx(HFjet.Px() * rand);
      HFjet.SetPy(HFjet.Py() * rand);
      HFjet.SetPz(HFjet.Pz() * rand);
      HFjet.SetE(HFjet.E() * rand);
      HFjet += HFmeson;
    }
    // cout<<tr_HFmeson.M()<<",";

    double HF_jet_dR = HFmeson.DeltaR(HFjet);
    double HF_jet_truedR = tr_HFmeson.DeltaR(tr_HFjet);
    bmass_dtf = Tree.Bu_ConsBu_M[0] / 1000.;
    dtf_chi2ndf = Tree.Bu_ConsBu_chi2[0] / Tree.Bu_ConsBu_nDOF[0];
    // cout<<bmass_dtf<<endl;

    bool mup_L0 = Tree.mup_L0MuonDecision_TOS || Tree.mup_L0DimuonDecision_TOS;
    // bool mup_HLT1 = Tree.mup_Hlt1DiMuonHighMassDecision_TOS;
    // bool mup_HLT2 = Tree.mup_Hlt2DiMuonJpsi2MuMuDecision_TOS;

    bool mum_L0 = Tree.mum_L0MuonDecision_TOS || Tree.mum_L0DimuonDecision_TOS;
    // bool mum_HLT1 = Tree.mum_Hlt1DiMuonHighMassDecision_TOS;
    // bool mum_HLT2 = Tree.mum_Hlt2DiMuonJpsi2MuMuDecision_TOS;

    // if(mup.Pt() < 0.25 || mum.Pt() < 0.25) continue;

    // if(Tree.eventNumber == 673310) cout<<"found event 673310"<<endl;

    if (Tree.nPVs > 1)
    {
      cut_npvs++;
      continue;
    }
    if (HFjet.Pt() < 15.)
    {
      cut_jetpt++;
      continue;
    }
    // cout<<Tree.Jet_SVTag_Tag<< ", "<< Tree.Jet_SVTag_Nvertices<<endl;
    if (HFjet.Eta() < 2.2 || HFjet.Eta() > 4.2)
    {
      cut_jeteta++;
      continue;
    }

    // if(Tree.eventNumber == 673310) cout<<"initial cuts"<<endl;
    // if (HF_jet_dR > jetradius)
    // {
    //   cut_Dinjet++;
    //   continue;
    // }
    // bool match = false;

    dphi = 3.1415;

    if (Tree.totCandidates > 1)
      ManyJets++;
    else
      OneJet++;

    nSV = Tree.Jet_SVTag_Nvertices;
    nSV_test = 0;
    HFHardest = true;
    jpsi_ipchi2 = log10(Tree.Jpsi_IPCHI2_OWNPV);
    // if(fabs(HFjet.Pt() - 18.8631) < 1e-4) cout<<HFjet.Eta()<<", "<<HFjet.Pt()<<endl;

    double leading_pT = 0;
    int n_maxpT_cand = -999;
    int n_maxpT_entry = -999;
    int n_HFpt_entry = -999;
    int HF_counter = 0;
    last_HFjet = 0;
    last_HFpt = 0;
    double testjet_phi, testjet_px, testjet_py, testjet_pz, testjet_e;
    int ncand = Tree.nCandidate;

    // cout<<"new ev"<<endl;
    // cout<<"totcand = "<<Tree.totCandidates<<endl;
    // if (Tree.totCandidates > 1)
    // {
    //   for (int icand = 0; icand < Tree.totCandidates; icand++)
    //   {
    //     Tree.GetEntry(ev + icand - ncand);
    //     // cout<<ev+icand-ncand<<endl;
    //     HFjet.SetPxPyPzE(Tree.Jet_PX / 1000.,
    //                      Tree.Jet_PY / 1000.,
    //                      Tree.Jet_PZ / 1000.,
    //                      Tree.Jet_PE / 1000.);
    //     mup.SetPxPyPzE(Tree.mup_PX / 1000., Tree.mup_PY / 1000., Tree.mup_PZ / 1000., Tree.mup_PE / 1000.);
    //     mum.SetPxPyPzE(Tree.mum_PX / 1000., Tree.mum_PY / 1000., Tree.mum_PZ / 1000., Tree.mum_PE / 1000.);
    //     Kmeson.SetPxPyPzE(Tree.K_PX / 1000., Tree.K_PY / 1000., Tree.K_PZ / 1000., Tree.K_PE / 1000.);
    //     HFmeson = mup + mum + Kmeson;
    //     //  HFjet = HFjet - mup - mum - Kmeson;

    //     //  cout<<HFjet.Pt()<<", "<<HFmeson.Pt()<<endl;
    //     bool hasHF = HFmeson.DeltaR(HFjet) < jetradius;

    //     double cand_jetpt = HFjet.Pt();
    //     // cout<<"Has HF"<<endl;
    //     if (!hasHF)
    //     {
    //       if (cand_jetpt > leading_pT)
    //       {
    //         // cout<<leading_pT<<", "<<cand_jetpt<<endl;
    //         leading_pT = cand_jetpt;
    //         n_maxpT_cand = Tree.nCandidate;
    //         n_maxpT_entry = ev + icand - ncand;
    //         // cout<<n_maxpT_entry<<endl;
    //       }
    //     }
    //     else
    //     {
    //       HF_counter++;
    //       if (HFmeson.Pt() > last_HFpt)
    //         n_HFpt_entry = ev + icand - ncand;

    //       // cout<<"n_HFpt_entry = "<<n_HFpt_entry<<endl;
    //       // cout<<HF_counter<<endl;
    //       last_HFjet = HFjet.Pt();
    //       last_HFpt = HFmeson.Pt();
    //     }
    //   }
    //   Tree.GetEntry(n_maxpT_entry);
    //   HFjet.SetPxPyPzE(Tree.Jet_PX / 1000.,
    //                    Tree.Jet_PY / 1000.,
    //                    Tree.Jet_PZ / 1000.,
    //                    Tree.Jet_PE / 1000.);
    //   // HFjet = HFjet - mup - mum - Kmeson;
    //   testjet_phi = HFjet.Phi();
    //   testjet_px = HFjet.Px();
    //   testjet_py = HFjet.Py();
    //   testjet_pz = HFjet.Pz();
    //   testjet_e = HFjet.E();
    //   if (Tree.Jet_BDTTag_bdt0[0] > 0. && Tree.Jet_BDTTag_bdt1[0] > 0.2)
    //     nSV_test = 1;
    //   else
    //     nSV_test = 0;
    // }
    // if(HF_counter > 1){
    //   maxHFpT_found = true;
    //   Tree.GetEntry(n_HFpt_entry);
    // }
    // else Tree.GetEntry(ev);
    // Tree.GetEntry(ev);
    // HFjet.SetPxPyPzE(Tree.Jet_PX / 1000.,
    //                  Tree.Jet_PY / 1000.,
    //                  Tree.Jet_PZ / 1000.,
    //                  Tree.Jet_PE / 1000.);
    // mup.SetPxPyPzE(Tree.mup_PX / 1000., Tree.mup_PY / 1000., Tree.mup_PZ / 1000., Tree.mup_PE / 1000.);
    // mum.SetPxPyPzE(Tree.mum_PX / 1000., Tree.mum_PY / 1000., Tree.mum_PZ / 1000., Tree.mum_PE / 1000.);
    // Kmeson.SetPxPyPzE(Tree.K_PX / 1000., Tree.K_PY / 1000., Tree.K_PZ / 1000., Tree.K_PE / 1000.);
    // HFmeson = mup + mum + Kmeson;
    // tr_HFjet.SetPxPyPzE(Tree.Jet_mcjet_PX / 1000.,
    //                     Tree.Jet_mcjet_PY / 1000.,
    //                     Tree.Jet_mcjet_PZ / 1000.,
    //                     Tree.Jet_mcjet_PE / 1000.);
    // tr_mup.SetPxPyPzE(Tree.mup_TRUEP_X / 1000., Tree.mup_TRUEP_Y / 1000.,
    //                   Tree.mup_TRUEP_Z / 1000., Tree.mup_TRUEP_E / 1000.);
    // tr_mum.SetPxPyPzE(Tree.mum_TRUEP_X / 1000., Tree.mum_TRUEP_Y / 1000.,
    //                   Tree.mum_TRUEP_Z / 1000., Tree.mum_TRUEP_E / 1000.);
    // tr_Kmeson.SetPxPyPzE(Tree.K_TRUEP_X / 1000., Tree.K_TRUEP_Y / 1000.,
    //                      Tree.K_TRUEP_Z / 1000., Tree.K_TRUEP_E / 1000.);
    // tr_HFmeson = tr_mup + tr_mum + tr_Kmeson;

    // // cout<<Tree.Jet_SVTag_Tag<< ", "<< Tree.Jet_SVTag_Nvertices<<endl;
    // if (HFjet.Eta() < etaMin || HFjet.Eta() > etaMax)
    // {
    //   cut_jeteta++;
    //   continue;
    // }
    // if (HF_jet_dR > jetradius)
    // {
    //   cut_Dinjet++;
    //   continue;
    // }

    // if (Tree.totCandidates > 1)
    // {
    //   dphi = fabs(checkphi(checkphi(HFmeson.Phi()) - checkphi(testjet_phi)));
    //   if (fabs(HFjet.Px() - testjet_px) < 0.01 &&
    //       fabs(HFjet.E() - testjet_e) < 0.01)
    //     dphi = 3.14159;
    //   // cout<<nSV_test<<endl;
    //   NumTwoCand++;
    //   if (fabs(HFjet.E() - testjet_e) < 0.0001)
    //   {
    //     NumTwoHFInJet++;
    //   }
    // }

    bool hasHFhadron = false;

    int NumBHads = 0;
    Bmass_1 = 0;
    Bmass_2 = 0;
    double B_energy = -99;
    // cout<<Tree.eventNumber<<endl;
    // cout<<HFjet.E()<<", "<<tr_HFjet.E()<<endl;
    // cout<<HFmeson.E()<<endl;

    jet_charge = 0;
    double kappa = 1.;
    bool skip_charge = true;

    double tot_e = 0;
    for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    {
      // if(Tree.eventNumber == 673310) cout<<Tree.Jet_Dtr_ID[dtrs0]<<endl;
      // cout<<(Tree.Jet_Dtr_PT[dtrs0]/HFjet.Pt()/1000.)<<",";
      // cout<<Tree.Jet_Dtr_ID[dtrs0]<<",";

      double trchi2ndf = Tree.Jet_Dtr_TrackChi2[dtrs0] / Tree.Jet_Dtr_TrackNDF[dtrs0];
      double dtr_charge = Tree.Jet_Dtr_ThreeCharge[dtrs0] / 3.;
      TLorentzVector dtr(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.Jet_Dtr_E[dtrs0] / 1000.);

      bool dtrpass = true;

      if (DoTrackPt)
      {

        if (fabs(Tree.Jet_Dtr_ThreeCharge[dtrs0]) > 0)
        {
          double rand = myRNG->Gaus(1, 0.03);
          dtr.SetPxPyPzE(dtr.Px() * rand,
                         dtr.Py() * rand,
                         dtr.Pz() * rand,
                         dtr.E() * rand);
        }
        else
        {
          // dE/E = a/sqrt(E) + b + c/E
          // a = 10%
          // b = 1%
          // c is small
          double b = 0.01;
          double a = 0.1;
          double e = dtr.E();
          double sigma = sqrt(b * b + a / sqrt(e) * a / sqrt(e));
          double rand = myRNG->Gaus(1, sigma);
          dtr.SetPxPyPzE(dtr.Px() * rand,
                         dtr.Py() * rand,
                         dtr.Pz() * rand,
                         dtr.E() * rand);
        }
      }

      jet_charge += dtr_charge * pow(dtr.Pt() / HFjet.Pt(), kappa);

      dtrpass = DtrCuts(dtr, dtr_charge, Tree.Jet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
        dtrpass = true;
      if (!dtrpass)
        continue;
      if (dtr.DeltaR(HFjet) > jetradius)
        continue;

      if (DoTrackEff)
      {
        if (abs(Tree.Jet_Dtr_ID[dtrs0]) != HF_pdgcode){
            // double prob_trk = 0.03;
          // double prob_neut = 0.08;
          double rand = myUniform->Uniform(1.);
          // cout<<rand;
          if (fabs(Tree.Jet_Dtr_ThreeCharge[dtrs0]) > 0)
          {
            int pbin = h2_trk_eff->GetXaxis()->FindBin(dtr.P());
            int etabin = h2_trk_eff->GetYaxis()->FindBin(dtr.Eta());
            double ratio = h2_trk_eff->GetBinContent(pbin, etabin);
            // int bin_eta = h2_trk_eff->GetBin(dtr.Eta());
            double prob_trk = fabs(ratio - 1.);
            // cout<<dtr.P()<<","<<dtr.Eta()<<", "<<ratio<<" | ";
            if (rand < prob_trk)
              continue;
          }
          else
          {
            int pbin = h2_neut_eff->GetXaxis()->FindBin(dtr.P());
            int etabin = h2_neut_eff->GetYaxis()->FindBin(dtr.Eta());
            double ratio = h2_neut_eff->GetBinContent(pbin, etabin);
            // int bin_eta = h2_trk_eff->GetBin(dtr.Eta());
            double prob_neut = fabs(ratio - 1.);
            // cout<<dtr.P()<<","<<dtr.Eta()<<", "<<ratio<<" | ";
            if (rand < prob_neut)
              continue;
          }
        }
      }

      jetdtrs.push_back(PseudoJet(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                                  Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                                  Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                                  Tree.Jet_Dtr_E[dtrs0] / 1000.));
      jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_Dtr_ID[dtrs0]));

      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        hasHFhadron = true;
        NumBHads++;
        // cout<<dtr.Pt()<<endl;
      }
      skip_charge = false;
      // jet_Nmcdtrs++;
    }
    // cout<<endl;
    if (skip_charge)
      jet_charge = -99;

    // if(Tree.eventNumber == 673310) cout<<"passed jet dtrs"<<endl;

    if (NumBHads > 1)
    {
      continue;
    }
    // if(Tree.eventNumber == 673310) cout<<"passed NumBHads > 1"<<endl;

    bool hasHFhadron_matched = false;
    NumBHads_tr = 0;
    bool hasb = false;
    bool hasbbar = false;

    // if(nSV > 0) cout<<"new ev"<<endl;
    // cout<<"reco "<<HFmeson.Px()<<", "<<HFmeson.Py()<<endl;
    // cout<<"true "<<tr_HFmeson.Px()<<", "<<tr_HFmeson.Py()<<endl;
    for (int dtrs0 = 0; dtrs0 < Tree.Jet_mcjet_nmcdtrs; dtrs0++)
    {
      double trchi2ndf = 0;
      // cout<<Tree.Jet_mcjet_dtrID[dtrs0]<<",";
      TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);

      bool dtrpass = true;
      // cout<<dtr.E()<<",";
      int motherid, id, topid;
      if (fabs(Tree.Jet_mcjet_MotherID[dtrs0]) < 6)
        id = (int)Tree.Jet_mcjet_MotherID[dtrs0];
      else
        id = -1 * ((int)Tree.Jet_mcjet_MotherID[dtrs0] / 100) % 10;
      topid = Tree.Jet_mcjet_TopMotherID[dtrs0];
      motherid = Tree.Jet_mcjet_MotherID[dtrs0];
      // if(nSV > 0) cout<<"M ID = "<<motherid<<", TopID = "<<topid<<endl;
      if (topid == 5)
        hasb = true;
      if (topid == -5)
        hasbbar = true;

      dtrpass = DtrCuts(dtr, Tree.Jet_mcjet_dtrThreeCharge[dtrs0], 0, 0, chargedJetCut);
      if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
        dtrpass = true;
      if (!dtrpass)
        continue;
      if (dtr.DeltaR(tr_HFjet) > jetradius)
        continue;

      tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
                                     Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
                                     Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
                                     Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
      tr_jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_mcjet_dtrID[dtrs0]));
      if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
      {
        // if(Tree.eventNumber == 673310) cout<<"in"<<dtr.Pt()<<endl;
        //  cout<<"in "<<dtr.Px()<<", "<<dtr.Py()<<endl;
        if(fabs(dtr.Px() - HFmeson.Px()) < 2 && fabs(dtr.Py() - HFmeson.Py()) < 2){
          hasHFhadron_matched = true;
          NumBHads_tr++;
          tr_HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        }
        
      }

      // jet_Nmcdtrs++;
    }
    if(tr_HFmeson.DeltaR(tr_HFjet) > jetradius) hasHFhadron_matched = false;
    // cout<<endl<<tr_HFmeson.Pt()<<endl;
 
    if (!hasHFhadron)
    {
      continue;
    }
    // if(Tree.eventNumber == 673310) cout<<"passed hasHFhadron"<<endl;
    // if(Tree.eventNumber == 673310) cout<<HFmeson.Pt() << ", "<<tr_HFmeson.Pt()<<endl;
    // if(Tree.eventNumber == 673310) cout<<HFmeson.Px() << ", "<<tr_HFmeson.Px()<<endl;
    // if(Tree.eventNumber == 673310) cout<<HFjet.Eta() << ", "<<HFjet.Pt()<<endl;
    // if(Tree.eventNumber == 673310) cout<<tr_HFjet.Eta() << ", "<<tr_HFjet.Pt()<<endl;
    Hasbbbar = false;
    if (Tree.hasb && Tree.hasbbar && Tree.Jet_SVTag_Tag)
      N_num++;
    if (Tree.hasb && Tree.hasbbar)
    {
      // cout<<Tree.hasb<<","<<Tree.hasbbar<<endl;
      Hasbbbar = true;
      N_denom++;
    }

    ClusterSequence subjet_cs(jetdtrs, small_jets);
    vector<PseudoJet> subjets = sorted_by_pt(subjet_cs.inclusive_jets());
    NumSubJets = 0;
    for (int i = 0; i < subjets.size(); i++)
    {
      if (subjets[i].pt() > 2 /* GeV */)
        NumSubJets++;
    }

    // cout<<"Starting dijet loop";
    thetas.clear();
    ktthetas.clear();
    dRs.clear();
    Erads.clear();
    kts.clear();
    zs.clear();
    raps.clear();
    phis.clear();
    hardest.clear();
    tr_thetas.clear();
    tr_ktthetas.clear();
    tr_dRs.clear();
    tr_Erads.clear();
    tr_kts.clear();
    tr_zs.clear();
    tr_raps.clear();
    tr_phis.clear();
    tr_hardest.clear();

    // if(jetdtrs.size() < 2) continue;

    ClusterSequence cs(jetdtrs, jet_def);
    vector<PseudoJet> constit;
    vector<LundDeclustering> declusts;
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
    PseudoJet mom = jets[0];

    if (mom.has_constituents())
    {
      constit = mom.constituents();
      int had_loc = -99;
      for (int i = 0; i < constit.size(); i++)
      {
        if (abs(constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
        {
          had_loc = i;
          break;
        }
      }
      if (had_loc > -1)
      {
        // Decluster jet by following either hardest prong or HF prong
        // Store info such as kt, Eradiator, theta, delta R
        // cout<<"Reco Declust!"<<endl;
        declusts = result(mom, constit[had_loc]);
        for (int idecl = 0; idecl < declusts.size(); idecl++)
        {
          double kt = declusts[idecl].kt();
          kts.push_back(kt);
          double dR = declusts[idecl].Delta();
          dRs.push_back(dR);
          double z = declusts[idecl].z();
          zs.push_back(z);
          double theta = declusts[idecl].theta();
          thetas.push_back(theta);
          double kttheta = declusts[idecl].kttheta();
          ktthetas.push_back(kttheta);
          double erad = declusts[idecl].erad();
          Erads.push_back(erad);
          double rap = declusts[idecl].rap();
          raps.push_back(rap);
          double phi = declusts[idecl].phi();
          phis.push_back(phi);
          bool isHard = declusts[idecl].hardest();
          hardest.push_back(isHard);
          if (!isHard)
            HFHardest = false;
        }
      }
    }

    vector<LundDeclustering> tr_declusts;
    if (!isData)
    {
      if (tr_jetdtrs.size() > 1)
      {
        ClusterSequence cs_tr_(tr_jetdtrs, jet_def);
        vector<PseudoJet> tr_constit;
        vector<PseudoJet> tr_jets = sorted_by_pt(cs_tr_.inclusive_jets());
        PseudoJet tr_mom = tr_jets[0];

        tr_constit = tr_mom.constituents();
        int tr_had_loc = -99;
        for (int i = 0; i < tr_constit.size(); i++)
        {
          if (abs(tr_constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
          {
            tr_had_loc = i;
            break;
          }
        }
        // cout<<"Truth Declust!"<<endl;
        if (tr_had_loc > -1)
          tr_declusts = result(tr_mom, tr_constit[tr_had_loc]);
      };
      for (int idecl = 0; idecl < tr_declusts.size(); idecl++)
      {
        double kt = tr_declusts[idecl].kt();
        tr_kts.push_back(kt);
        double dR = tr_declusts[idecl].Delta();
        tr_dRs.push_back(dR);
        double z = tr_declusts[idecl].z();
        tr_zs.push_back(z);
        double theta = tr_declusts[idecl].theta();
        tr_thetas.push_back(theta);
        double kttheta = tr_declusts[idecl].kttheta();
        tr_ktthetas.push_back(kttheta);
        double erad = tr_declusts[idecl].erad();
        tr_Erads.push_back(erad);
        double rap = tr_declusts[idecl].rap();
        tr_raps.push_back(rap);
        double phi = tr_declusts[idecl].phi();
        tr_phis.push_back(phi);
        bool isHard = tr_declusts[idecl].hardest();
        tr_hardest.push_back(isHard);
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
    mum_px = mum.Px();
    mum_py = mum.Py();
    mum_pz = mum.Pz();
    mum_e = mum.E();
    mup_px = mup.Px();
    mup_py = mup.Py();
    mup_pz = mup.Pz();
    mup_e = mup.E();
    K_px = Kmeson.Px();
    K_py = Kmeson.Py();
    K_pz = Kmeson.Pz();
    K_e = Kmeson.E();
    ndtrs = jetdtrs.size();
    nsplits = kts.size();

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

    tr_mum_px = tr_mum.Px();
    tr_mum_py = tr_mum.Py();
    tr_mum_pz = tr_mum.Pz();
    tr_mum_e = tr_mum.E();
    tr_mup_px = tr_mup.Px();
    tr_mup_py = tr_mup.Py();
    tr_mup_pz = tr_mup.Pz();
    tr_mup_e = tr_mup.E();
    tr_K_px = tr_Kmeson.Px();
    tr_K_py = tr_Kmeson.Py();
    tr_K_pz = tr_Kmeson.Pz();
    tr_K_e = tr_Kmeson.E();
    tr_ndtrs = tr_jetdtrs.size();
    tr_nsplits = tr_kts.size();

    if (hasHFhadron_matched)
    {
      isTrueBjet = true;
    }
    else
    {
      isTrueBjet = false;
      // cout<<jet_pt<<", "<<tr_jet_pt<<endl;
    }
    if (last_eventNum == Tree.eventNumber)
      NumSame++;
    last_eventNum = Tree.eventNumber;
    eventNumber = Tree.eventNumber;

    events++;
    // if(declusts.size()>0) {
    // cout<<"Filling";
    // if(Tree.eventNumber == 673310) cout<<"filling"<<endl;
    LundTree->Fill();
    // }
  }
  cout << "N_num = " << N_num << endl;
  cout << "N_denom = " << N_denom << endl;
  cout << "SV Tag Eff from MC = " << (double)N_num / (double)N_denom * 100 << "%" << endl;
  cout << "Total number of events processed = " << events << endl;
  cout << "Many Jets = " << ManyJets << endl;
  cout << "One Jets = " << OneJet << endl;

  cout << "Events blocked: " << endl;
  cout << "npvs = " << cut_npvs << endl;
  cout << "jetpt = " << cut_jetpt << endl;
  cout << "jeteta = " << cut_jeteta << endl;
  cout << "Dinjet = " << cut_Dinjet << endl;
  cout << "hasHF = " << cut_hasHF << endl;
  cout << "NumBmatched = " << Num_Bmatched << endl;

  cout << "Num TWO HF in Jet = " << NumTwoHFInJet << endl;
  cout << "Num More than 1 jet in event = " << NumTwoCand << endl;
  cout << "Num Bjets from same event = " << NumSame << endl;

  f.Write();
  f.Close();
}
//
