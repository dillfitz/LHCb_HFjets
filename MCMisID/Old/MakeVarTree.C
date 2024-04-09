

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include "MisIDTree.C"
#include "MisIDMCTree.C"
#include <TCanvas.h>
#include <vector>
#include <iostream>
//#include "../Settings.h"

//#include "Helpers.h"
//#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Helpers.h"
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
// #include "../RooHelpers.h"
//#include "../LundGen.hh"
//using namespace fastjet;

using namespace std;

void MakeVarTree(int NumEvts_user = -1, int dataset = 91599, bool isData = false,
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
  TString extension_read, extension_RootFilesMC;

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
  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  MisIDTree Tree(0, dataset, isData);
  // HFjetTree TreeAnti(0, dataset, !isData);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  cout << "Executing CAJetAlgo" << endl;
  float dtr_rap;
  float dtr_phi;
  float delta_rap;
  float delta_phi;

  TString dir_deadcone("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/BjetsMC/");
//  extension_RootFilesMC = TString("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/BjetsMC/");

  TFile f(dir_deadcone + extension + ".root", "RECREATE");

//  JetDefinition jet_def(cambridge_algorithm, jetradius);
//  PseudoJet dtr1, dtr2;

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
  TTree *LundTree = new TTree("LundTree", "Lund Tree Variables");
    
//  LundTree->Branch("thetas", &thetas);
//  LundTree->Branch("Erads", &Erads);
//  LundTree->Branch("dRs", &dRs);
//  LundTree->Branch("kts", &kts);
//  LundTree->Branch("zs", &zs);
//  LundTree->Branch("raps", &raps);
//  LundTree->Branch("phis", &phis);

  LundTree->Branch("jet_pt", &jet_pt);
  LundTree->Branch("jet_eta", &jet_eta);
  LundTree->Branch("jet_rap", &jet_rap);

  LundTree->Branch("jet_px", &jet_px);
  LundTree->Branch("jet_py", &jet_py);
  LundTree->Branch("jet_pz", &jet_pz);
  LundTree->Branch("jet_e", &jet_e);

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

  LundTree->Branch("pi_px", &pi_px);
  LundTree->Branch("pi_py", &pi_py);
  LundTree->Branch("pi_pz", &pi_pz);
  LundTree->Branch("pi_e", &pi_e);

  LundTree->Branch("pi_PIDK", &pi_PIDK);

  LundTree->Branch("HF_px", &HF_px);
  LundTree->Branch("HF_py", &HF_py);
  LundTree->Branch("HF_pz", &HF_pz);
  LundTree->Branch("HF_e", &HF_e);

  LundTree->Branch("tr_HF_px", &tr_HF_px);
  LundTree->Branch("tr_HF_py", &tr_HF_py);
  LundTree->Branch("tr_HF_pz", &tr_HF_pz);
  LundTree->Branch("tr_HF_e", &tr_HF_e);

  LundTree->Branch("Bfromjet_px", &Bfromjet_px);
  LundTree->Branch("Bfromjet_py", &Bfromjet_py);
  LundTree->Branch("Bfromjet_pz", &Bfromjet_pz);
  LundTree->Branch("Bfromjet_e", &Bfromjet_e);

//  LundTree->Branch("tr_thetas", &tr_thetas);
//  LundTree->Branch("tr_Erads", &tr_Erads);
//  LundTree->Branch("tr_dRs", &tr_dRs);
//  LundTree->Branch("tr_kts", &tr_kts);
//  LundTree->Branch("tr_zs", &tr_zs);
//  LundTree->Branch("tr_raps", &tr_raps);
//  LundTree->Branch("tr_phis", &tr_phis);

  LundTree->Branch("tr_jet_pt", &tr_jet_pt);
  LundTree->Branch("tr_jet_eta", &tr_jet_eta);
  LundTree->Branch("tr_jet_rap", &tr_jet_rap);

  LundTree->Branch("tr_jet_px", &tr_jet_px);
  LundTree->Branch("tr_jet_py", &tr_jet_py);
  LundTree->Branch("tr_jet_pz", &tr_jet_pz);
  LundTree->Branch("tr_jet_e", &tr_jet_e);

  LundTree->Branch("tr_mum_px", &tr_mum_px);
  LundTree->Branch("tr_mum_py", &tr_mum_py);
  LundTree->Branch("tr_mum_pz", &tr_mum_pz);
  LundTree->Branch("tr_mum_e", &tr_mum_e);

  LundTree->Branch("tr_mup_px", &tr_mup_px);
  LundTree->Branch("tr_mup_py", &tr_mup_py);
  LundTree->Branch("tr_mup_pz", &tr_mup_pz);
  LundTree->Branch("tr_mup_e", &tr_mup_e);

  LundTree->Branch("tr_pi_px", &tr_pi_px);
  LundTree->Branch("tr_pi_py", &tr_pi_py);
  LundTree->Branch("tr_pi_pz", &tr_pi_pz);
  LundTree->Branch("tr_pi_e", &tr_pi_e);

//  LundTree->Branch("tr_ndtrs", &tr_ndtrs);
//  LundTree->Branch("tr_nsplits", &tr_nsplits);
    
  LundTree->Branch("isTrueBjet", &isTrueBjet);

  LundTree->Branch("bmass_dtf", &bmass_dtf);
  LundTree->Branch("dtf_chi2ndf", &dtf_chi2ndf);

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

    vector<PseudoJet> jetdtrs, tr_jetdtrs;
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
//      float trchi2ndf = Tree.Jet_Dtr_TrackChi2[dtrs0] / Tree.Jet_Dtr_TrackNDF[dtrs0];
      TLorentzVector dtr(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.Jet_Dtr_E[dtrs0] / 1000.);

      bool dtrpass = true;

      dtrpass = DtrCuts(dtr, Tree.Jet_Dtr_ThreeCharge[dtrs0], Tree.Jet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
        dtrpass = true;
      if (!dtrpass)
        continue;
      jetdtrs.push_back(PseudoJet(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                                  Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                                  Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                                  Tree.Jet_Dtr_E[dtrs0] / 1000.));
      jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_Dtr_ID[dtrs0]));
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

      bool dtrpass = true;

      dtrpass = DtrCuts(dtr, Tree.Jet_mcjet_dtrThreeCharge[dtrs0], 0, 0, chargedJetCut);
      if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
        dtrpass = true;
      if (!dtrpass)
        continue;

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

    // cout<<"Starting dijet loop";
    thetas.clear();
    dRs.clear();
    Erads.clear();
    kts.clear();
    zs.clear();
    raps.clear();
    phis.clear();
    tr_thetas.clear();
    tr_dRs.clear();
    tr_Erads.clear();
    tr_kts.clear();
    tr_zs.clear();
    tr_raps.clear();
    tr_phis.clear();

    // cout<<jetdtrs.size()<<endl;
//    vector<LundDeclustering> declusts;
//    if (jetdtrs.size() < 1)
//    {
//      ClusterSequence cs(jetdtrs, jet_def);
//      vector<PseudoJet> constit;
//      vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
//      PseudoJet mom = jets[0];
//
//      constit = mom.constituents();
//      int had_loc = -99;
//      for (int i = 0; i < constit.size(); i++)
//      {
//        if (abs(constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
//        {
//          had_loc = i;
//          break;
//        }
//      }
//      if (had_loc > -1)
//        declusts = result(mom, constit[had_loc]);
//      // Decluster jet by following either hardest prong or HF prong
//      // Store info such as kt, Eradiator, theta, delta R
//      // cout<<"Reco Declust!"<<endl;
//
//      for (int idecl = 0; idecl < declusts.size(); idecl++)
//      {
//        float kt = declusts[idecl].kt();
//        kts.push_back(kt);
//        float dR = declusts[idecl].Delta();
//        dRs.push_back(dR);
//        float z = declusts[idecl].z();
//        zs.push_back(z);
//        float theta = declusts[idecl].theta();
//        thetas.push_back(theta);
//        float erad = declusts[idecl].erad();
//        Erads.push_back(erad);
//        float rap = declusts[idecl].rap();
//        raps.push_back(rap);
//        float phi = declusts[idecl].phi();
//        phis.push_back(phi);
//      }
//    }

//    vector<LundDeclustering> tr_declusts;
//    if (!isData)
//    {
//      if (tr_jetdtrs.size() > 2)
//      {
//        ClusterSequence cs_tr_(tr_jetdtrs, jet_def);
//        vector<PseudoJet> tr_constit;
//        vector<PseudoJet> tr_jets = sorted_by_pt(cs_tr_.inclusive_jets());
//        PseudoJet tr_mom = tr_jets[0];
//
//        tr_constit = tr_mom.constituents();
//        int tr_had_loc = -99;
//        for (int i = 0; i < tr_constit.size(); i++)
//        {
//          if (abs(tr_constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
//          {
//            tr_had_loc = i;
//            break;
//          }
//        }
//        // cout<<"Truth Declust!"<<endl;
//        if (tr_had_loc > -1)
//          tr_declusts = result(tr_mom, tr_constit[tr_had_loc]);
//      };
//      for (int idecl = 0; idecl < tr_declusts.size(); idecl++)
//      {
//        float kt = tr_declusts[idecl].kt();
//        tr_kts.push_back(kt);
//        float dR = tr_declusts[idecl].Delta();
//        tr_dRs.push_back(dR);
//        float z = tr_declusts[idecl].z();
//        tr_zs.push_back(z);
//        float theta = tr_declusts[idecl].theta();
//        tr_thetas.push_back(theta);
//        float erad = tr_declusts[idecl].erad();
//        tr_Erads.push_back(erad);
//        float rap = tr_declusts[idecl].rap();
//        tr_raps.push_back(rap);
//        float phi = tr_declusts[idecl].phi();
//        tr_phis.push_back(phi);
//      }
//    }

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

    ndtrs = jetdtrs.size();
    nsplits = kts.size();

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
      
    tr_ndtrs = tr_jetdtrs.size();
    tr_nsplits = tr_kts.size();

    pi_PIDK = Tree.pi_PIDK;

    if (hasHFhadron_matched)
      isTrueBjet = true;
    else
      isTrueBjet = false;

    events++;
    LundTree->Fill();
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
