

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

void MCMakeVarTree(int NumEvts_user = 10000, int dataset = 1510,
                   bool chargedJetCut_user = false)
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
  TString str_tree;

  TString extension;
  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  BjetMCTree Tree(0, dataset, false);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  cout << "Executing CAJetAlgo" << endl;

  TString dir_deadcone("$LUND/Bjets/");

  TFile f(dir_deadcone + "hists/" + extension + ".root", "RECREATE");

  JetDefinition jet_def(cambridge_algorithm, jetradius);
  PseudoJet dtr1, dtr2;

  double jet_pt, jet_eta, meas_jet_pt, meas_jet_eta;
  double jet_px, jet_py, jet_pz, jet_e;
  double HF_px, HF_py, HF_pz, HF_e;
  double HF_pt;
  double jet_rap, meas_jet_rap;
  double K_px, K_py, K_pz, K_e;
  double mup_px, mup_py, mup_pz, mup_e;
  double mum_px, mum_py, mum_pz, mum_e;

  double meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e;
  double meas_mup_px, meas_mup_py, meas_mup_pz, meas_mup_e;
  double meas_mum_px, meas_mum_py, meas_mum_pz, meas_mum_e;
  double meas_K_px, meas_K_py, meas_K_pz, meas_K_e;
  double meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e;
  double meas_HF_pt;

  int nsplits, ndtrs;
  int meas_nsplits, meas_ndtrs;
  int GluonTag;
  int NumHFHads, eventNumber;

  bool hasRecoHF;

  vector<double> thetas, meas_thetas;
  vector<double> dRs, meas_dRs;
  vector<double> ktthetas, meas_ktthetas;
  vector<double> Erads, meas_Erads;
  vector<double> kts, meas_kts;
  vector<double> zs, meas_zs;
  vector<double> raps, meas_raps;
  vector<double> phis, meas_phis;
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

  LundTree->Branch("jet_pt", &jet_pt);
  LundTree->Branch("jet_eta", &jet_eta);
  LundTree->Branch("jet_rap", &jet_rap);

  LundTree->Branch("jet_px", &jet_px);
  LundTree->Branch("jet_py", &jet_py);
  LundTree->Branch("jet_pz", &jet_pz);
  LundTree->Branch("jet_e", &jet_e);

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

  LundTree->Branch("meas_thetas", &meas_thetas);
  LundTree->Branch("meas_ktthetas", &meas_ktthetas);
  LundTree->Branch("meas_Erads", &meas_Erads);
  LundTree->Branch("meas_dRs", &meas_dRs);
  LundTree->Branch("meas_kts", &meas_kts);
  LundTree->Branch("meas_zs", &meas_zs);
  LundTree->Branch("meas_raps", &meas_raps);
  LundTree->Branch("meas_phis", &meas_phis);

  LundTree->Branch("meas_jet_pt", &meas_jet_pt);
  LundTree->Branch("meas_jet_eta", &meas_jet_eta);
  LundTree->Branch("meas_jet_rap", &meas_jet_rap);

  LundTree->Branch("meas_HF_pt", &meas_HF_pt);

  LundTree->Branch("meas_jet_px", &meas_jet_px);
  LundTree->Branch("meas_jet_py", &meas_jet_py);
  LundTree->Branch("meas_jet_pz", &meas_jet_pz);
  LundTree->Branch("meas_jet_e", &meas_jet_e);

  LundTree->Branch("meas_mum_px", &meas_mum_px);
  LundTree->Branch("meas_mum_py", &meas_mum_py);
  LundTree->Branch("meas_mum_pz", &meas_mum_pz);
  LundTree->Branch("meas_mum_e", &meas_mum_e);

  LundTree->Branch("meas_mup_px", &meas_mup_px);
  LundTree->Branch("meas_mup_py", &meas_mup_py);
  LundTree->Branch("meas_mup_pz", &meas_mup_pz);
  LundTree->Branch("meas_mup_e", &meas_mup_e);

  LundTree->Branch("meas_HF_px", &meas_HF_px);
  LundTree->Branch("meas_HF_py", &meas_HF_py);
  LundTree->Branch("meas_HF_pz", &meas_HF_pz);
  LundTree->Branch("meas_HF_e", &meas_HF_e);

  LundTree->Branch("meas_K_px", &meas_K_px);
  LundTree->Branch("meas_K_py", &meas_K_py);
  LundTree->Branch("meas_K_pz", &meas_K_pz);
  LundTree->Branch("meas_K_e", &meas_K_e);

  LundTree->Branch("meas_ndtrs", &meas_ndtrs);
  LundTree->Branch("meas_nsplits", &meas_nsplits);

  LundTree->Branch("GluonTag", &GluonTag);
  LundTree->Branch("NumHFHads", &NumHFHads);
  LundTree->Branch("hasRecoHF", &hasRecoHF);

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

  for (int ev = 0; ev < NumEvts; ev++)
  {
    Tree.GetEntry(ev);
    // EventTree->GetEntry(ev);
    // cout<<recojet_e<<", ";
    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;
    // cout<<NumEvts<<endl;
    // cout<<"event="<<ev<<endl;
    // FIX DOUBLE COUNTING
    // if(eventNum!=eventNum1) continue;
    // cout<<"totalCands = "<<totalCands<<", ";

    if (ev != 0)
    {
      if (Tree.eventNumber != last_eventNum)
      {
        maxjetpT_found = false;
      }
    }

    // if(maxjetpT_found){
    //   continue;
    // }

    TLorentzVector HFjet, recojet, meas_HFjet, HFmeson, mup, mum, Kmeson, Jpsi;
    TLorentzVector meas_Zdtr3, meas_mup, meas_mum, meas_HFmeson, meas_Kmeson;

    vector<PseudoJet> jetdtrs, meas_jetdtrs;

    mup.SetPxPyPzE(Tree.MCJet_truth_mup_PX / 1000.,
                   Tree.MCJet_truth_mup_PY / 1000.,
                   Tree.MCJet_truth_mup_PZ / 1000.,
                   Tree.MCJet_truth_mup_PE / 1000.);
    mum.SetPxPyPzE(Tree.MCJet_truth_mum_PX / 1000.,
                   Tree.MCJet_truth_mum_PY / 1000.,
                   Tree.MCJet_truth_mum_PZ / 1000.,
                   Tree.MCJet_truth_mum_PE / 1000.);
    Kmeson.SetPxPyPzE(Tree.MCJet_truth_K_PX / 1000.,
                      Tree.MCJet_truth_K_PY / 1000.,
                      Tree.MCJet_truth_K_PZ / 1000.,
                      Tree.MCJet_truth_K_PE / 1000.);

    HFjet.SetPxPyPzE(Tree.MCJet_PX / 1000.,
                     Tree.MCJet_PY / 1000.,
                     Tree.MCJet_PZ / 1000.,
                     Tree.MCJet_PE / 1000.);

    HFmeson = mup + mum + Kmeson;
    Jpsi = mup + mum;
    // cout<<Jpsi.M()<<",";
    // cout<<matched_mum_PX<<",";
    meas_HFjet.SetPxPyPzE(Tree.MCJet_recojet_PX / 1000.,
                          Tree.MCJet_recojet_PY / 1000.,
                          Tree.MCJet_recojet_PZ / 1000.,
                          Tree.MCJet_recojet_PE / 1000.);

    meas_HFmeson = meas_mup + meas_mum + meas_Kmeson;

    double HF_jet_dR = HFmeson.DeltaR(HFjet);
    double HF_jet_truedR = meas_HFmeson.DeltaR(meas_HFjet);

    // if(HF_jet_dR > 0.5) continue;

    //  if(HFjet.Eta() < etaMin || HFjet.Eta() > etaMax) cout<<HFjet.Eta()<<",";

    if (Tree.nPVs > 1)
    {
      cut_npvs++;
      continue;
    }
    if (HFjet.Pt() < 15.)
    {
      cut_pt++;
      continue;
    }
    // if (HFjet.Eta() < etaMin || HFjet.Eta() > etaMax)
    // {
    //   cut_eta++;
    //   continue;
    // }
    //  if(Kmeson.Pt() < 0.25 || mup.Pt() < 0.25 || mum.Pt() < 0.25){
    //     continue;
    //  }

    //  if(HF_jet_dR > jetradius){
    //     cut_HFdR++;
    //     continue;
    //  }
    
      

    // cout<<Tree.eventNumber<<endl;
    // jet_Nmcdtrs = recojetNdtrs;
    bool hasHFhadron = false;
    bool hasJpsi = false;
    bool isGluonJet = false;
    bool hasbquark = false;
    bool hasbbar = false;
    GluonTag = false;
    NumHFHads = 0;
    // cout<<Tree.eventNumber<<endl; 
    // cout<<endl;
    // cout<<endl<<HFjet.Pt()<<endl; 
    // if(Tree.eventNumber == 673310) cout<<"before dtrs"<<endl;
    // if(Tree.eventNumber == 673310) cout<<HFmeson.Pt()<<", "<<meas_HFmeson.Pt()<<endl;
    // if(Tree.eventNumber == 673310) cout<<HFjet.Eta()<<", "<<HFjet.Pt()<<endl;
    // if(Tree.eventNumber == 673310) cout<<meas_HFjet.Eta()<<", "<<meas_HFjet.Pt()<<endl;

    for (int dtrs0 = 0; dtrs0 < Tree.MCJet_Dtr_nmcdtrs; dtrs0++)
    {

      double trchi2ndf = 0;
      TLorentzVector dtr(Tree.MCJet_Dtr_PX[dtrs0] / 1000.,
                         Tree.MCJet_Dtr_PY[dtrs0] / 1000.,
                         Tree.MCJet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.MCJet_Dtr_E[dtrs0] / 1000.);

      bool dtrpass = true;
      // cout<<dtr.E()<<","<<Tree.MCJet_Dtr_ID[dtrs0]<<",";

      dtrpass = DtrCuts(dtr, Tree.MCJet_Dtr_ThreeCharge[dtrs0], 0, 0, chargedJetCut);
      if (abs(Tree.MCJet_Dtr_ID[dtrs0]) == HF_pdgcode)
        dtrpass = true;
      if (!dtrpass)
        continue;
      if (dtr.DeltaR(HFjet) > jetradius)
        continue;
      if (abs(Tree.MCJet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        if(Tree.eventNumber == 673310) cout<<dtr.Pt()<<endl;
        if(fabs(dtr.Px() - HFmeson.Px()) < 2 && fabs(dtr.Py() - HFmeson.Py()) < 2){
          NumHFHads++;
          hasHFhadron = true;
        }        
      }

      jetdtrs.push_back(PseudoJet(Tree.MCJet_Dtr_PX[dtrs0] / 1000.,
                                  Tree.MCJet_Dtr_PY[dtrs0] / 1000.,
                                  Tree.MCJet_Dtr_PZ[dtrs0] / 1000.,
                                  Tree.MCJet_Dtr_E[dtrs0] / 1000.));
      jetdtrs.back().set_user_info(new MyInfo(Tree.MCJet_Dtr_ID[dtrs0]));
      // cout<<Tree.MCJet_Dtr_ID[dtrs0]<<",";

      if (Tree.MCJet_Dtr_TopMotherID[dtrs0] == 5)
        hasbquark = true;
      if (Tree.MCJet_Dtr_TopMotherID[dtrs0] == -5)
        hasbbar = true;
      // jet_Nmcdtrs++;
    }
    // if(Tree.eventNumber == 673310) cout<<"after dtrs"<<endl;
    // cout<<HFjet.Pt()<<endl;
    if (HFmeson.DeltaR(HFjet) > jetradius)
      continue;
    // if(Tree.eventNumber == 673310) cout<<"passed deltaR"<<endl;
    if (!hasHFhadron)
      continue;
    // if(Tree.eventNumber == 673310) cout<<"passed hasHFhadron"<<endl;
    // if(NumHFHads > 1) continue;
    if (hasbquark && hasbbar)
      GluonTag = true;
    // if(NumHFHads > 1) continue;
    hasRecoHF = false;

    for (int dtrs0 = 0; dtrs0 < Tree.MCJet_recojet_nrecodtrs; dtrs0++)
    {
      // if(Tree.eventNumber == 673310) cout<<Tree.MCJet_recojet_Dtr_ID[dtrs0]<<endl;

      double trchi2ndf = Tree.MCJet_recojet_Dtr_TrackChi2[dtrs0] / Tree.MCJet_recojet_Dtr_TrackNDF[dtrs0];
      TLorentzVector dtr(Tree.MCJet_recojet_Dtr_PX[dtrs0] / 1000.,
                         Tree.MCJet_recojet_Dtr_PY[dtrs0] / 1000.,
                         Tree.MCJet_recojet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.MCJet_recojet_Dtr_E[dtrs0] / 1000.);

      bool dtrpass = true;


      dtrpass = DtrCuts(dtr, Tree.MCJet_recojet_Dtr_ThreeCharge[dtrs0], Tree.MCJet_recojet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
      if (abs(Tree.MCJet_recojet_Dtr_ID[dtrs0]) == HF_pdgcode)
        dtrpass = true;

      if (dtr.E() < 0)
        continue;

      if (!dtrpass)
        continue;
      
      if (dtr.DeltaR(meas_HFjet) > jetradius)
        continue;
      // if(fabs(Tree.MCJet_recojet_Dtr_ThreeCharge[dtrs0]) == 0) cout<<Tree.MCJet_recojet_Dtr_P[dtrs0]<< ", "<<Tree.MCJet_recojet_matchedtruthdtr_P[dtrs0]<<endl;

      meas_jetdtrs.push_back(PseudoJet(Tree.MCJet_recojet_Dtr_PX[dtrs0] / 1000.,
                                       Tree.MCJet_recojet_Dtr_PY[dtrs0] / 1000.,
                                       Tree.MCJet_recojet_Dtr_PZ[dtrs0] / 1000.,
                                       Tree.MCJet_recojet_Dtr_E[dtrs0] / 1000.));
      meas_jetdtrs.back().set_user_info(new MyInfo(Tree.MCJet_recojet_Dtr_ID[dtrs0]));

      if (abs(Tree.MCJet_recojet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        meas_HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        // if(Tree.eventNumber == 673310) cout<<"rec "<<dtr.Pt()<<endl;
        hasRecoHF = true;
      }
    }
    if(meas_HFmeson.DeltaR(meas_HFjet) > jetradius) hasRecoHF = false;
    if(hasRecoHF) NumRecoHF++;

    // if(meas_HFjet.Pt() > 20.) cout<<hasRecoHF<<endl;
//     if(meas_HFjet.E() < 0.) cout<<meas_HFjet.Pt()<<endl;
    // cout<<Tree.eventNumber<<endl;

    jet_pt = HFjet.Pt();
    jet_eta = HFjet.Eta();
    meas_jet_pt = meas_HFjet.Pt();
    meas_jet_eta = meas_HFjet.Eta();

    // cout<<"Starting dijet loop";
    thetas.clear();
    ktthetas.clear();
    dRs.clear();
    Erads.clear();
    kts.clear();
    zs.clear();
    raps.clear();
    phis.clear();
    meas_thetas.clear();
    meas_ktthetas.clear();
    meas_dRs.clear();
    meas_Erads.clear();
    meas_kts.clear();
    meas_zs.clear();
    meas_raps.clear();
    meas_phis.clear();

    // if(jetdtrs.size() > 2) continue;
    ClusterSequence cs(jetdtrs, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    PseudoJet mom = jets[0];
    vector<PseudoJet> constit;
    vector<LundDeclustering> declusts;
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
        }
      }
    }

    vector<LundDeclustering> meas_declusts;
    if (meas_jetdtrs.size() > 1)
    {
      ClusterSequence cs_meas_(meas_jetdtrs, jet_def);
      vector<PseudoJet> meas_constit;
      vector<PseudoJet> meas_jets = sorted_by_pt(cs_meas_.inclusive_jets());
      PseudoJet meas_mom = meas_jets[0];

      meas_constit = meas_mom.constituents();
      int meas_had_loc = -99;
      for (int i = 0; i < meas_constit.size(); i++)
      {
        if (abs(meas_constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
        {
          meas_had_loc = i;
          break;
        }
      }
      // cout<<"Truth Declust!"<<endl;
      if (meas_had_loc > -1)
        meas_declusts = result(meas_mom, meas_constit[meas_had_loc]);
    };
    for (int idecl = 0; idecl < meas_declusts.size(); idecl++)
    {
      double kt = meas_declusts[idecl].kt();
      meas_kts.push_back(kt);
      double dR = meas_declusts[idecl].Delta();
      meas_dRs.push_back(dR);
      double z = meas_declusts[idecl].z();
      meas_zs.push_back(z);
      double theta = meas_declusts[idecl].theta();
      meas_thetas.push_back(theta);
      double kttheta = meas_declusts[idecl].kttheta();
      meas_ktthetas.push_back(kttheta);
      double erad = meas_declusts[idecl].erad();
      meas_Erads.push_back(erad);
      double rap = meas_declusts[idecl].rap();
      meas_raps.push_back(rap);
      double phi = meas_declusts[idecl].phi();
      meas_phis.push_back(phi);
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

    meas_jet_eta = meas_HFjet.Eta();
    meas_jet_rap = meas_HFjet.Rapidity();
    meas_jet_pt = meas_HFjet.Pt();
    meas_HF_pt = meas_HFmeson.Pt();

    meas_mum_px = meas_mum.Px();
    meas_mum_py = meas_mum.Py();
    meas_mum_pz = meas_mum.Pz();
    meas_mum_e = meas_mum.E();
    meas_mup_px = meas_mup.Px();
    meas_mup_py = meas_mup.Py();
    meas_mup_pz = meas_mup.Pz();
    meas_mup_e = meas_mup.E();
    meas_K_px = meas_Kmeson.Px();
    meas_K_py = meas_Kmeson.Py();
    meas_K_pz = meas_Kmeson.Pz();
    meas_K_e = meas_Kmeson.E();
    meas_HF_px = meas_HFmeson.Px();
    meas_HF_py = meas_HFmeson.Py();
    meas_HF_pz = meas_HFmeson.Pz();
    meas_HF_e = meas_HFmeson.E();
    meas_ndtrs = meas_jetdtrs.size();
    meas_nsplits = meas_kts.size();

    if (last_eventNum == Tree.eventNumber)
      continue;
    last_eventNum = Tree.eventNumber;
    eventNumber = Tree.eventNumber;

    events++;
    // if(declusts.size() > 0){
      // if(Tree.eventNumber == 673310) cout<<"filling"<<endl;
    LundTree->Fill();
    //  }
  }
  cout << "Total number of events processed = " << events << endl;
  cout << "NumRecoHF = " << NumRecoHF << endl;

  cout << "Events blocked: " << endl;
  cout << "npvs = " << cut_npvs << endl;
  cout << "jetpt = " << cut_pt << endl;
  cout << "jeteta = " << cut_eta << endl;
  cout << "Dinjet = " << cut_HFdR << endl;
  // cout<<"hasHF = "<< cut_hasHF<<endl;

  f.Write();
  f.Close();
}
//
