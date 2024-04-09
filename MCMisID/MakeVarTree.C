

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include "MisIDTree.C"
#include "MisIDMCTree.C"
#include <TCanvas.h>
#include <vector>
#include <iostream>
//#include "Settings.h"
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
// #include "../RooHelpers.h"
//#include "../LundGen.hh"
#include "Helpers.h"

//using namespace fastjet;
using namespace std;

void MakeVarTree(int NumEvts_user = -1, int dataset = 1510, bool isData = true,
                 bool chargedJetCut_user = false)
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
    
 TString extension_read, extension_RootFilesMC, extension;
    extension_RootFilesMC = TString("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/BjetsMC/");

  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  MisIDTree Tree(0, dataset, isData);
  // HFjetTree TreeAnti(0, dataset, !isData);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

//  cout << "Executing CAJetAlgo" << endl;
  float dtr_rap;
  float dtr_phi;
  float delta_rap;
  float delta_phi;

  TFile f(extension_RootFilesMC + extension + ".root", "RECREATE");

  float jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  float jet_rap, tr_jet_rap;
  float jet_px, jet_py, jet_pz, jet_e;
  float HF_px, HF_py, HF_pz, HF_e;
  float tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e;
  float mup_px, mup_py, mup_pz, mup_e;
  float mum_px, mum_py, mum_pz, mum_e;
  float pi_px, pi_py, pi_pz, pi_e;
  float pi_PIDK;
  float Bfromjet_px, Bfromjet_py, Bfromjet_pz, Bfromjet_e;

  float tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  float tr_mup_px, tr_mup_py, tr_mup_pz, tr_mup_e;
  float tr_mum_px, tr_mum_py, tr_mum_pz, tr_mum_e;
  float tr_pi_px, tr_pi_py, tr_pi_pz, tr_pi_e;

  int nsplits, ndtrs;
  int tr_nsplits, tr_ndtrs;
  float bmass_dtf, dtf_chi2ndf;

  bool isTrueBjet;

//  vector<float> thetas, tr_thetas;
//  vector<float> dRs, tr_dRs;
//  vector<float> Erads, tr_Erads;
//  vector<float> kts, tr_kts;
//  vector<float> zs, tr_zs;
//  vector<float> raps, tr_raps;
//  vector<float> phis, tr_phis;
  // TLorentzVector
  TTree *BTree = new TTree("BTree", "B-jets Tree Variables");
//  LundTree->Branch("thetas", &thetas);
//  LundTree->Branch("Erads", &Erads);
//  LundTree->Branch("dRs", &dRs);
//  LundTree->Branch("kts", &kts);
//  LundTree->Branch("zs", &zs);
//  LundTree->Branch("raps", &raps);
//  LundTree->Branch("phis", &phis);

    BTree->Branch("jet_pt", &jet_pt);
    BTree->Branch("jet_eta", &jet_eta);
    BTree->Branch("jet_rap", &jet_rap);

    BTree->Branch("jet_px", &jet_px);
  BTree->Branch("jet_py", &jet_py);
  BTree->Branch("jet_pz", &jet_pz);
  BTree->Branch("jet_e", &jet_e);

  BTree->Branch("ndtrs", &ndtrs);
  BTree->Branch("nsplits", &nsplits);

  BTree->Branch("mum_px", &mum_px);
  BTree->Branch("mum_py", &mum_py);
  BTree->Branch("mum_pz", &mum_pz);
  BTree->Branch("mum_e", &mum_e);

  BTree->Branch("mup_px", &mup_px);
  BTree->Branch("mup_py", &mup_py);
  BTree->Branch("mup_pz", &mup_pz);
  BTree->Branch("mup_e", &mup_e);

  BTree->Branch("pi_px", &pi_px);
  BTree->Branch("pi_py", &pi_py);
  BTree->Branch("pi_pz", &pi_pz);
  BTree->Branch("pi_e", &pi_e);

  BTree->Branch("pi_PIDK", &pi_PIDK);

  BTree->Branch("HF_px", &HF_px);
  BTree->Branch("HF_py", &HF_py);
  BTree->Branch("HF_pz", &HF_pz);
  BTree->Branch("HF_e", &HF_e);

  BTree->Branch("tr_HF_px", &tr_HF_px);
  BTree->Branch("tr_HF_py", &tr_HF_py);
  BTree->Branch("tr_HF_pz", &tr_HF_pz);
  BTree->Branch("tr_HF_e", &tr_HF_e);

  BTree->Branch("Bfromjet_px", &Bfromjet_px);
  BTree->Branch("Bfromjet_py", &Bfromjet_py);
  BTree->Branch("Bfromjet_pz", &Bfromjet_pz);
  BTree->Branch("Bfromjet_e", &Bfromjet_e);

//  LundTree->Branch("tr_thetas", &tr_thetas);
//  LundTree->Branch("tr_Erads", &tr_Erads);
//  LundTree->Branch("tr_dRs", &tr_dRs);
//  LundTree->Branch("tr_kts", &tr_kts);
//  LundTree->Branch("tr_zs", &tr_zs);
//  LundTree->Branch("tr_raps", &tr_raps);
//  LundTree->Branch("tr_phis", &tr_phis);

  BTree->Branch("tr_jet_pt", &tr_jet_pt);
  BTree->Branch("tr_jet_eta", &tr_jet_eta);
  BTree->Branch("tr_jet_rap", &tr_jet_rap);

  BTree->Branch("tr_jet_px", &tr_jet_px);
  BTree->Branch("tr_jet_py", &tr_jet_py);
  BTree->Branch("tr_jet_pz", &tr_jet_pz);
  BTree->Branch("tr_jet_e", &tr_jet_e);

  BTree->Branch("tr_mum_px", &tr_mum_px);
  BTree->Branch("tr_mum_py", &tr_mum_py);
  BTree->Branch("tr_mum_pz", &tr_mum_pz);
  BTree->Branch("tr_mum_e", &tr_mum_e);

  BTree->Branch("tr_mup_px", &tr_mup_px);
  BTree->Branch("tr_mup_py", &tr_mup_py);
  BTree->Branch("tr_mup_pz", &tr_mup_pz);
  BTree->Branch("tr_mup_e", &tr_mup_e);

  BTree->Branch("tr_pi_px", &tr_pi_px);
  BTree->Branch("tr_pi_py", &tr_pi_py);
  BTree->Branch("tr_pi_pz", &tr_pi_pz);
  BTree->Branch("tr_pi_e", &tr_pi_e);

  BTree->Branch("tr_ndtrs", &tr_ndtrs);
  BTree->Branch("tr_nsplits", &tr_nsplits);
  BTree->Branch("isTrueBjet", &isTrueBjet);

  BTree->Branch("bmass_dtf", &bmass_dtf);
  BTree->Branch("dtf_chi2ndf", &dtf_chi2ndf);

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //

  int eventNum;
  unsigned long long last_eventNum = 0;
  int events = 0;

  bool maxjetpT_found = false;
  int cut_npvs = 0;
  int cut_jetpt = 0;
  int cut_jeteta = 0;
  int cut_Dinjet = 0;
  int cut_prompt = 0;
  int cut_hasHF = 0;

  float pionMass = 0.139570;
  float kaonMass = 0.493677;
  float jpsiMass = 3.096916;

  for (int ev = 0; ev < NumEvts; ev++)
  {
    Tree.GetEntry(ev);
    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;

    if (ev != 0)
    {
      if (Tree.eventNumber != last_eventNum)
      {
        maxjetpT_found = false;
      }
    }

    last_eventNum = Tree.eventNumber;
    float min_dr = 999;
    int n_mindr_cand = -999;
    int n_mindr_entry = -999;

    TLorentzVector HFjet, recojet, tr_truthjet, HFmeson, mup, mum, pion, jpsi;
    TLorentzVector tr_HFjet, tr_pion, tr_mum, tr_mup, tr_HFmeson;

//    vector<PseudoJet> jetdtrs, tr_jetdtrs;
    // TLorentzVector recojet, tr_Zjet, zjet;
    mup.SetPxPyPzE(Tree.mup_PX / 1000., Tree.mup_PY / 1000., Tree.mup_PZ / 1000., Tree.mup_PE / 1000.);
    mum.SetPxPyPzE(Tree.mum_PX / 1000., Tree.mum_PY / 1000., Tree.mum_PZ / 1000., Tree.mum_PE / 1000.);
    jpsi = mup + mum;
    // jpsi.SetE(sqrt(jpsi.E() * jpsi.E() - jpsi.M() * jpsi.M() + jpsiMass * jpsiMass));
    // cout<<jpsi.M()<<",";
    // jpsi.SetM(jpsiMass);
    pion.SetPxPyPzE(Tree.pi_PX / 1000., Tree.pi_PY / 1000., Tree.pi_PZ / 1000., Tree.pi_PE / 1000.);
    // cout << pion.M() << ", " << jpsi.M() << endl;

    pion.SetPxPyPzE(Tree.pi_PX / 1000., Tree.pi_PY / 1000., Tree.pi_PZ / 1000.,
                    sqrt(Tree.pi_PE / 1000. * Tree.pi_PE / 1000. - pionMass * pionMass + kaonMass * kaonMass));

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
    tr_pion.SetPxPyPzE(Tree.pi_TRUEP_X / 1000., Tree.pi_TRUEP_Y / 1000.,
                       Tree.pi_TRUEP_Z / 1000., Tree.pi_TRUEP_E / 1000.);

    HFmeson.SetPxPyPzE(Tree.Bu_PX / 1000.,
                       Tree.Bu_PY / 1000.,
                       Tree.Bu_PZ / 1000.,
                       Tree.Bu_PE / 1000.);
    tr_HFmeson = tr_mup + tr_mum + tr_pion;
    // cout<<tr_HFmeson.M()<<",";

    float HF_jet_dR = HFmeson.DeltaR(HFjet);
    float HF_jet_truedR = tr_HFmeson.DeltaR(tr_HFjet);
    bmass_dtf = Tree.Bu_ConsBu_M[0] / 1000.;
    dtf_chi2ndf = Tree.Bu_ConsBu_chi2[0] / Tree.Bu_ConsBu_nDOF[0];

    if (Tree.nPVs > 1)
    {
      cut_npvs++;
      continue;
    }

    if (HF_jet_dR > jetradius)
    {
      cut_Dinjet++;
      continue;
    }

    // cout<<HFmeson.M()<<endl;

    bool hasHFhadron = false;
    int NumHF = 0;
    for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    {
      // cout<<(Tree.Jet_Dtr_PT[dtrs0]/HFjet.Pt()/1000.)<<",";
      // cout<<Tree.Jet_Dtr_ID[dtrs0]<<",";
      float trchi2ndf = Tree.Jet_Dtr_TrackChi2[dtrs0] / Tree.Jet_Dtr_TrackNDF[dtrs0];
      TLorentzVector dtr(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.Jet_Dtr_E[dtrs0] / 1000.);

//      bool dtrpass = true;
//
//      dtrpass = DtrCuts(dtr, Tree.Jet_Dtr_ThreeCharge[dtrs0], Tree.Jet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
//      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
//        dtrpass = true;
//      if (!dtrpass)
//        continue;
//      jetdtrs.push_back(PseudoJet(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
//                                  Tree.Jet_Dtr_PY[dtrs0] / 1000.,
//                                  Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
//                                  Tree.Jet_Dtr_E[dtrs0] / 1000.));
//      jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_Dtr_ID[dtrs0]));
        
      // cout<<Tree.Jet_Dtr_ID[dtrs0]<<" -- ";
      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        hasHFhadron = true;
        NumHF++;
        Bfromjet_px = Tree.Jet_Dtr_PX[dtrs0] / 1000.;
        Bfromjet_py = Tree.Jet_Dtr_PY[dtrs0] / 1000.;
        Bfromjet_pz = Tree.Jet_Dtr_PZ[dtrs0] / 1000.;
        Bfromjet_e = Tree.Jet_Dtr_E[dtrs0] / 1000.;
      }
      // jet_Nmcdtrs++;
    }
    // cout<<endl;
    if (!hasHFhadron)
      continue;
    if (NumHF > 1)
      continue;

    bool hasHFhadron_matched = false;
    for (int dtrs0 = 0; dtrs0 < Tree.Jet_mcjet_nmcdtrs; dtrs0++)
    {
      float trchi2ndf = 0;
      TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);

//      bool dtrpass = true;
//
//      dtrpass = DtrCuts(dtr, Tree.Jet_mcjet_dtrThreeCharge[dtrs0], 0, 0, chargedJetCut);
//      if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
//        dtrpass = true;
//      if (!dtrpass)
//        continue;

//      tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
//                                     Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
//                                     Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
//                                     Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
//      tr_jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_mcjet_dtrID[dtrs0]));
      if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
      {
        tr_HFmeson.SetPxPyPzE(dtr.Px(),
                              dtr.Py(),
                              dtr.Pz(),
                              dtr.E());
        hasHFhadron_matched = true;
      }

      // jet_Nmcdtrs++;
    }



    jet_pt = HFjet.Pt();
    jet_eta = HFjet.Eta();
    jet_rap = HFjet.Rapidity();
    jet_px = HFjet.Px();
    jet_py = HFjet.Py();
    jet_pz = HFjet.Pz();
    jet_e = HFjet.E();
    mum_px = mum.Px();
    mum_py = mum.Py();
    mum_pz = mum.Pz();
    mum_e = mum.E();
    mup_px = mup.Px();
    mup_py = mup.Py();
    mup_pz = mup.Pz();
    mup_e = mup.E();
    pi_px = pion.Px();
    pi_py = pion.Py();
    pi_pz = pion.Pz();
    pi_e = pion.E();

    HF_px = HFmeson.Px();
    HF_py = HFmeson.Py();
    HF_pz = HFmeson.Pz();
    HF_e = HFmeson.E();

    tr_HF_px = tr_HFmeson.Px();
    tr_HF_py = tr_HFmeson.Py();
    tr_HF_pz = tr_HFmeson.Pz();
    tr_HF_e = tr_HFmeson.E();

//    ndtrs = jetdtrs.size();
//    nsplits = kts.size();

    tr_jet_eta = tr_HFjet.Eta();
    tr_jet_rap = tr_HFjet.Rapidity();
    tr_jet_pt = tr_HFjet.Pt();
    tr_jet_px = tr_HFjet.Px();
    tr_jet_py = tr_HFjet.Py();
    tr_jet_pz = tr_HFjet.Pz();
    tr_jet_e = tr_HFjet.E();

    tr_mum_px = tr_mum.Px();
    tr_mum_py = tr_mum.Py();
    tr_mum_pz = tr_mum.Pz();
    tr_mum_e = tr_mum.E();
    tr_mup_px = tr_mup.Px();
    tr_mup_py = tr_mup.Py();
    tr_mup_pz = tr_mup.Pz();
    tr_mup_e = tr_mup.E();
    tr_pi_px = tr_pion.Px();
    tr_pi_py = tr_pion.Py();
    tr_pi_pz = tr_pion.Pz();
    tr_pi_e = tr_pion.E();
//    tr_ndtrs = tr_jetdtrs.size();
//    tr_nsplits = tr_kts.size();

    pi_PIDK = Tree.pi_PIDK;

    if (hasHFhadron_matched)
      isTrueBjet = true;
    else
      isTrueBjet = false;

    events++;
    BTree->Fill();
  }
  cout << "Total number of events processed = " << events << endl;

  cout << "Events blocked: " << endl;
  cout << "npvs = " << cut_npvs << endl;
  cout << "jetpt = " << cut_jetpt << endl;
  cout << "jeteta = " << cut_jeteta << endl;
  cout << "Dinjet = " << cut_Dinjet << endl;
  cout << "hasHF = " << cut_hasHF << endl;

  f.Write();
  f.Close();
}
//
