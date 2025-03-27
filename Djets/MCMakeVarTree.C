

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include "./MCJetTree.C"
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
// #include "fastjet/ClusterSequence.hh"
// #include "fastjet/contrib/SoftDrop.hh"
// #include "../RooHelpers.h"
// #include "../LundGen.hh"

using namespace std;

void MCMakeVarTree(int NumEvts_user = 10000, int dataset = 1510,
                   bool chargedJetCut_user = false,
                   int PromptCut = 0)
{

  int NumEvts = NumEvts_user;
  int NumEvtsTruth = NumEvts_user;
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

  int tr_HF_pdgcode = -999;
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
  str_prompt = (PromptCut == 1) ? "_prompt" : (PromptCut == 2) ? "_nonprompt"
                                                               : "";
  TString str_tree;
  TString extension_read, extension_RootFilesMC;
  TString extension;

  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);

  MCJetTree Tree(0, dataset, false);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  cout << "Executing CAJetAlgo" << endl;

  extension_RootFilesMC = TString("../../root_files/DjetsMC/");

  TFile f(extension_RootFilesMC + extension + ".root", "RECREATE");

  double jet_pt, jet_eta, meas_jet_pt, meas_jet_eta;
  double jet_px, jet_py, jet_pz, jet_e;
  double HF_px, HF_py, HF_pz, HF_e;
  double HF_pt;
  double jet_rap, meas_jet_rap;
  double pi_px, pi_py, pi_pz, pi_e;
  double pi0_px, pi0_py, pi0_pz, pi0_e;
  double K_px, K_py, K_pz, K_e;

  double meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e;
  double meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e;
  double meas_HF_pt;

  double WTA_dist(999);
  bool hasGamma = false;

  double truth_z, truth_jt, truth_r;
  double truth_z_c, truth_jt_c, truth_r_c;
  double truth_zg, truth_jtg, truth_rg;
  double meas_z, meas_jt, meas_r;
  double meas_inJet_z, meas_inJet_jt, meas_inJet_r;
  double jet_pt_recotruthratio, HF_pt_recotruthratio;

  int nsplits, ndtrs;
  int meas_nsplits, meas_ndtrs;
  int nTracks;
  int NumHFHads, eventNumber;

  bool hasRecoHF, Hasccbar;
  double ptweight(1.);

  // TLorentzVector
  TTree *DTree = new TTree("DTree", "D-jets Tree Variables");

  DTree->Branch("eventNumber", &eventNumber);

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

  DTree->Branch("ndtrs", &ndtrs);
  DTree->Branch("nsplits", &nsplits);

  DTree->Branch("K_px", &K_px);
  DTree->Branch("K_py", &K_py);
  DTree->Branch("K_pz", &K_pz);
  DTree->Branch("K_e", &K_e);

  DTree->Branch("pi0_px", &pi0_px);
  DTree->Branch("pi0_py", &pi0_py);
  DTree->Branch("pi0_pz", &pi0_pz);
  DTree->Branch("pi0_e", &pi0_e);

  DTree->Branch("pi_px", &pi_px);
  DTree->Branch("pi_py", &pi_py);
  DTree->Branch("pi_pz", &pi_pz);
  DTree->Branch("pi_e", &pi_e);

  DTree->Branch("meas_jet_pt", &meas_jet_pt);
  DTree->Branch("meas_jet_eta", &meas_jet_eta);
  DTree->Branch("meas_jet_rap", &meas_jet_rap);

  DTree->Branch("meas_HF_pt", &meas_HF_pt);

  DTree->Branch("meas_jet_px", &meas_jet_px);
  DTree->Branch("meas_jet_py", &meas_jet_py);
  DTree->Branch("meas_jet_pz", &meas_jet_pz);
  DTree->Branch("meas_jet_e", &meas_jet_e);

  DTree->Branch("meas_HF_px", &meas_HF_px);
  DTree->Branch("meas_HF_py", &meas_HF_py);
  DTree->Branch("meas_HF_pz", &meas_HF_pz);
  DTree->Branch("meas_HF_e", &meas_HF_e);

  DTree->Branch("meas_ndtrs", &meas_ndtrs);
  DTree->Branch("meas_nsplits", &meas_nsplits);

  DTree->Branch("NumHFHads", &NumHFHads);
  DTree->Branch("hasRecoHF", &hasRecoHF);
  DTree->Branch("Hasccbar", &Hasccbar);
  DTree->Branch("nTracks", &nTracks);

  DTree->Branch("WTA_dist", &WTA_dist);
  DTree->Branch("ptweight", &ptweight);

  DTree->Branch("hasGamma", &hasGamma);

  DTree->Branch("truth_z", &truth_z);
  DTree->Branch("truth_jt", &truth_jt);
  DTree->Branch("truth_r", &truth_r);
  DTree->Branch("truth_z_c", &truth_z_c);
  DTree->Branch("truth_jt_c", &truth_jt_c);
  DTree->Branch("truth_r_c", &truth_r_c);
  DTree->Branch("truth_zg", &truth_zg);
  DTree->Branch("truth_jtg", &truth_jtg);
  DTree->Branch("truth_rg", &truth_rg);

  DTree->Branch("meas_z", &meas_z);
  DTree->Branch("meas_jt", &meas_jt);
  DTree->Branch("meas_r", &meas_r);

  DTree->Branch("meas_inJet_z", &meas_inJet_z);
  DTree->Branch("meas_inJet_jt", &meas_inJet_jt);
  DTree->Branch("meas_inJet_r", &meas_inJet_r);

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //

  int eventNum;
  unsigned long long last_eventNum = 0;
  int events = 0;

  bool maxjetpT_found = false;
  int NumRecoHF = 0;

  int cut_npvs = 0;
  int cut_eta = 0;
  int cut_pt = 0;
  int cut_HFdR = 0;

  int Num_nonprompt = 0;
  int Num_prompt = 0;

  // Loop over all B + jet pairs
  // Not all jets have a B meson
  for (int ev = 0; ev < NumEvts; ev++)
  {
    Tree.GetEntry(ev);

    if (ev % 100000 == 0)
      cout << "Executing event " << ev << endl;

    // if (Tree.nPVs > 1)
    //   continue;
    // if (Tree.MCJet_PT / 1000. < pTLow)
    //   continue;

    // If DTree has been filled, skip all other B + jet combinations in the event
    if (ev != 0)
    {
      if (Tree.eventNumber == last_eventNum)
      {
        continue;
      }
    }

    // bool skipevent = true;
    // for (int dtrs0 = 0; dtrs0 < Tree.MCJet_Dtr_nmcdtrs; dtrs0++)
    // {
    //   if (abs(Tree.MCJet_Dtr_ID[dtrs0]) == tr_HF_pdgcode)
    //     skipevent = false;
    // }
    // if (skipevent)
    //   continue;

    ptweight = ptweights[JetMeth];

    // Define all 4-momenta
    TLorentzVector HFjet, HFmeson, K, pi0, pi, Phi;
    TLorentzVector meas_HFjet, meas_HFmeson;
    TLorentzVector meas_K, meas_pi0, meas_pi, meas_Phi;

    // Store the jet daughters in a vector of PseudoJets for FASTJET
    // vector<PseudoJet> jetdtrs, meas_jetdtrs;

    // Set all 4-momenta
    pi0.SetPxPyPzE(Tree.MCJet_truth_Pi0_PX / 1000., 
                   Tree.MCJet_truth_Pi0_PY / 1000., 
                   Tree.MCJet_truth_Pi0_PZ / 1000., 
                   Tree.MCJet_truth_Pi0_PE / 1000.);
    K.SetPxPyPzE(Tree.MCJet_truth_K_PX / 1000., 
                 Tree.MCJet_truth_K_PY / 1000., 
                 Tree.MCJet_truth_K_PZ / 1000., 
                 Tree.MCJet_truth_K_PE / 1000.);
    pi.SetPxPyPzE(Tree.MCJet_truth_pi_PX / 1000., 
                  Tree.MCJet_truth_pi_PY / 1000., 
                  Tree.MCJet_truth_pi_PZ / 1000., 
                  Tree.MCJet_truth_pi_PE / 1000.);

    HFjet.SetPxPyPzE(Tree.MCJet_PX / 1000., 
                     Tree.MCJet_PY / 1000., 
                     Tree.MCJet_PZ / 1000., 
                     Tree.MCJet_PE / 1000.);

    HFmeson = pi0 + K + pi;
    // HFmeson.SetPxPyPzE(Tree.MCJet_truth_D0_PX / 1000., 
    //                    Tree.MCJet_truth_D0_PY / 1000., 
    //                    Tree.MCJet_truth_D0_PZ / 1000., 
    //                    Tree.MCJet_truth_D0_PE / 1000.);
    
    meas_HFjet.SetPxPyPzE(Tree.MCJet_recojet_PX / 1000., 
                          Tree.MCJet_recojet_PY / 1000., 
                          Tree.MCJet_recojet_PZ / 1000., 
                          Tree.MCJet_recojet_PE / 1000.);
    
    meas_pi0.SetPxPyPzE(Tree.MCJet_truth_Pi0_PX / 1000., 
                   Tree.MCJet_truth_Pi0_PY / 1000., 
                   Tree.MCJet_truth_Pi0_PZ / 1000., 
                   Tree.MCJet_truth_Pi0_PE / 1000.);

    meas_K.SetPxPyPzE(Tree.MCJet_truth_K_PX / 1000., 
                 Tree.MCJet_truth_K_PY / 1000., 
                 Tree.MCJet_truth_K_PZ / 1000., 
                 Tree.MCJet_truth_K_PE / 1000.);

    meas_pi.SetPxPyPzE(Tree.MCJet_truth_pi_PX / 1000., 
                  Tree.MCJet_truth_pi_PY / 1000., 
                  Tree.MCJet_truth_pi_PZ / 1000., 
                  Tree.MCJet_truth_pi_PE / 1000.);

    meas_HFmeson = meas_pi0 + meas_K + meas_pi;

    double HF_jet_dR = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
//   double HF_jet_dR = HFmeson.DeltaR(HFjet);
    // Uncommented
    double HF_jet_truedR = static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE);

  if (Tree.nPVs > 1)
      continue;

    // Check if jet had two B hadrons with dR < 0.5
    Hasccbar = false;
    if (Tree.hasc && Tree.hascbar)
      Hasccbar = true;

    // Boolean to store if jet has a HF hadron
    bool hasHFhadron = false;
    NumHFHads = 0;
    hasGamma = false;
  
    // if (HFjet.Pt() < pTLow)
    //   continue;

    //////////////////////////////////////////////
    // Loop over truth jet daughters
    // store good daughters in vector of PseudoJet
    //////////////////////////////////////////////
    // cout << endl
    //      << "New jet" << endl;
    TLorentzVector D0_gamma;
    for (int dtrs0 = 0; dtrs0 < Tree.MCJet_Dtr_nmcdtrs; dtrs0++)
    {
      // cout << Tree.MCJet_Dtr_ID[dtrs0] << ", ";
      bool dtrpass = true;
      TLorentzVector dtr(Tree.MCJet_Dtr_PX[dtrs0] / 1000.,
                         Tree.MCJet_Dtr_PY[dtrs0] / 1000.,
                         Tree.MCJet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.MCJet_Dtr_E[dtrs0] / 1000.);

      // if (dtr.E() < dtr.P())
      // cout << dtr.E() << ", " << dtr.P() << endl;
      // Check if daughter passes quality cuts
      // if (abs(Tree.MCJet_Dtr_ID[dtrs0]) != tr_HF_pdgcode)
      //   dtrpass = DtrCuts(dtr, Tree.MCJet_Dtr_ThreeCharge[dtrs0], 0, 0, chargedJetCut);
      // if (!dtrpass)
      //   continue;

      if (abs(Tree.MCJet_Dtr_ID[dtrs0]) == tr_HF_pdgcode)
      {
        // This is to ensure that the "421" in the jet is the signal B meson
        // There could be B mesons that don't decay to Phi K,
        // they will still be clustered as "421" in the jet
        // HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        // cout << HFmeson.Pt() << ", " << HFmeson.Rapidity() << ", " << dtr.Pt() << ", " << HFjet.Pt() << ", " << HFjet.Eta() << endl;
        if (fabs(dtr.Px() - HFmeson.Px()) < 1e-2 && fabs(dtr.Py() - HFmeson.Py()) < 1e-2)
        {
          hasHFhadron = true;

        }

        NumHFHads++;
      }

    }

    // Veto events that don't have a B meson
    if (!hasHFhadron)
      continue;
    // Veto events with dR(B, jet) > 0.5
    // if (HFmeson.DeltaR(HFjet, true) > jetradius)
    //   continue;
    // jetdtrs.push_back(PseudoJet(HFmeson.Px(),
    //                             HFmeson.Py(),
    //                             HFmeson.Pz(),
    //                             HFmeson.E()));
    // jetdtrs.back().set_user_info(new MyInfo(tr_HF_pdgcode));

    // cout << HFmeson.E() << ", " << HFmeson.M() << endl;

    // Boolean to store if reco jet has a HF hadron
    hasRecoHF = false;

    //////////////////////////////////////////////
    // Loop over reco jet daughters
    // store good daughters in vector of PseudoJet
    //////////////////////////////////////////////
    for (int dtrs0 = 0; dtrs0 < Tree.MCJet_recojet_nrecodtrs; dtrs0++)
    {
      // cout << Tree.MCJet_recojet_Dtr_ID[dtrs0] << ", ";
      double trchi2ndf = Tree.MCJet_recojet_Dtr_TrackChi2[dtrs0] / Tree.MCJet_recojet_Dtr_TrackNDF[dtrs0];
      bool dtrpass = true;

      TLorentzVector dtr(Tree.MCJet_recojet_Dtr_PX[dtrs0] / 1000.,
                         Tree.MCJet_recojet_Dtr_PY[dtrs0] / 1000.,
                         Tree.MCJet_recojet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.MCJet_recojet_Dtr_E[dtrs0] / 1000.);
      if (dtr.E() < 0) {
          continue;
      }
      // if (abs(Tree.MCJet_recojet_Dtr_ID[dtrs0]) != HF_pdgcode)
      //   dtrpass = DtrCuts(dtr, Tree.MCJet_recojet_Dtr_ThreeCharge[dtrs0], Tree.MCJet_recojet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);

      // if (!dtrpass)
      //   continue;

 
      if (abs(Tree.MCJet_recojet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        meas_HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        hasRecoHF = true;
        NumRecoHF++;
        // }
      }
    }

    if (static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE) > jetradius) hasRecoHF = false;

    // If reco HF falls outside jet cone, then treat is as not reconstructed
    // if (meas_HFmeson.DeltaR(meas_HFjet, true) > jetradius)
    //   hasRecoHF = false;


    TVector3 HF_meson = HFmeson.Vect();
    TVector3 HF_jet = HFjet.Vect();
    TVector3 meas_HF_meson = meas_HFmeson.Vect();
    TVector3 meas_HF_jet = meas_HFjet.Vect();
             
    if(!Hasccbar) {
      truth_z_c = (HF_meson.Dot(HF_jet) ) / (HF_jet.Mag2() );
      truth_jt_c = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
      truth_r_c = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);

      // h1_z_truth_c->Fill(truth_z_c);
  
    }

    meas_z = (meas_HF_meson.Dot(meas_HF_jet) ) / (meas_HF_jet.Mag2() );
    meas_jt = (meas_HF_jet.Cross(meas_HF_meson).Mag()) / (meas_HF_jet.Mag());
    meas_r =  static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE);

        // Below: Not Needed --- Just for curiosity //
    if (hasRecoHF) {
      meas_inJet_z = (meas_HF_meson.Dot(meas_HF_jet) ) / (meas_HF_jet.Mag2() );
      meas_inJet_jt = (meas_HF_jet.Cross(meas_HF_meson).Mag()) / (meas_HF_jet.Mag());
      meas_inJet_r = static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE);
    }

    if(Hasccbar){
      truth_zg = (HF_meson.Dot(HF_jet) ) / (HF_jet.Mag2() );
      truth_jtg = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
      truth_rg = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
            
      // h1_z_truth_g->Fill(truth_zg);
    }

    // Update all variables to be stored in the DTree
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

    K_px = K.Px();
    K_py = K.Py();
    K_pz = K.Pz();
    K_e = K.E();

    pi0_px = pi0.Px();
    pi0_py = pi0.Py();
    pi0_pz = pi0.Pz();
    pi0_e = pi0.E();

    pi_px = pi.Px();
    pi_py = pi.Py();
    pi_pz = pi.Pz();
    pi_e = pi.E();

    truth_z = HF_meson.Dot(HF_jet) / (HF_jet.Mag2());
    truth_jt = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
    truth_r = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);  

    // ndtrs = jetdtrs.size();
    // nsplits = kts.size();

    meas_jet_eta = meas_HFjet.Eta();
    meas_jet_rap = meas_HFjet.Rapidity();
    meas_jet_pt = meas_HFjet.Pt();
    meas_jet_px = meas_HFjet.Px();
    meas_jet_py = meas_HFjet.Py();
    meas_jet_pz = meas_HFjet.Pz();
    meas_jet_e = meas_HFjet.E();
    meas_HF_pt = meas_HFmeson.Pt();

    meas_HF_px = meas_HFmeson.Px();
    meas_HF_py = meas_HFmeson.Py();
    meas_HF_pz = meas_HFmeson.Pz();
    meas_HF_e = meas_HFmeson.E();

    // meas_ndtrs = meas_jetdtrs.size();
    // meas_nsplits = meas_kts.size();

    nTracks = Tree.nTracks;

    last_eventNum = Tree.eventNumber;
    eventNumber = Tree.eventNumber;

    // if (HFjet.DeltaR(meas_HFjet, kTRUE) > 0.15)
    // {
    //   if (meas_HFmeson.Pt() > 0)
    //   {
    //     cout << "------------------------------------------" << endl;
    //     // cout << "Kp :" << pi0.Pt() << ", " << meas_pi0.Pt() << endl;
    //     // cout << "Km :" << K.Pt() << ", " << meas_K.Pt() << endl;
    //     // cout << "pi :" << pi.Pt() << ", " << meas_pi.Pt() << endl;
    //     cout << "HFmeson :" << HFmeson.Pt() << ", " << meas_HFmeson.Pt() << endl;
    //     cout << "DElta R = " << HFjet.DeltaR(meas_HFjet, kTRUE) << endl;
    //     // cout << "NumRecoHF = " << NumRecoHF << endl;
    //   }
    // }

    // cout << Tree.parton1_ID << ", " << Tree.parton2_ID << endl;

    if (hasGamma)
      Num_nonprompt++;
    else
      Num_prompt++;
    // Fill the Tree
    events++;
    DTree->Fill();
  }
  cout << "Total number of events processed = " << events << endl;
  cout << "NumRecoHF = " << NumRecoHF << endl;

  cout << "Events blocked: " << endl;
  cout << "npvs = " << cut_npvs << endl;
  cout << "jetpt = " << cut_pt << endl;
  cout << "jeteta = " << cut_eta << endl;
  cout << "Dinjet = " << cut_HFdR << endl;

  cout << "Percentage of excited Ds = " << (double)Num_nonprompt / (double)(Num_nonprompt + Num_prompt) << endl;
  // cout<<"hasHF = "<< cut_hasHF<<endl;

  f.Write();
  f.Close();
}
//
