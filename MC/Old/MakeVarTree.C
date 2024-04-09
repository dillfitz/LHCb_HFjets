

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

//#include "./MC_10192023/BjetTree.C"  //Reco
//#include "./MC_08152023/BjetTree.C"  //Reco
//#include "./MC_10162023/BjetTree.C"  //Reco
#include "./MC_03032024/BjetTree.C"  //Reco

#include <TCanvas.h>
#include <vector>
#include <iostream>
//#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Settings.h"
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Helpers.h"
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
// #include "../RooHelpers.h"
//#include "../LundGen.hh"

//using namespace fastjet;
using namespace std;

// , int NumEvts = 6022748

void MakeVarTree(int NumEvts_user = -1,
                 int dataset = 91599,
                 bool isData = false,
                 bool chargedJetCut_user = false,
                 bool DoJER = false,
                 int DoJES = 0,
                 bool DoFSPEff = false,
                 bool DoTrackPt = false,
                 bool DoGhostCut = false){
    
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

    TString str_year = "2016";

    TString str_charged = "";

    if (year == 6)
        str_year = "2016";
    else if (year == 7)
        str_year = "2017";
    else if (year == 8)
        str_year = "2018";

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

    if (Mag == 0)
        str_Mag = "_MD";
    else if (Mag == 1)
        str_Mag = "_MU";
    else if (Mag == 9)
        str_Mag = "_MU&MD";

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

//  BjetTree Tree(0, isMagUp, isMagDown);
//  
//  int NumEvts;
//  if (NumEvts_user ==-1)
//    {
//        NumEvts_user = Tree.fChain->GetEntries();
//        NumEvts = NumEvts_user;
//    }
//  else
//    {
//        NumEvts = NumEvts_user;
//    }
//
////    if (truthLevel)
////    {
////      ghostCut = false;
////    }
//    
//    int HF_pdgcode = -99;
//    
//    if (flavor == 5)
//    {
//      mass_num = 4.2;
//      HF_pdgcode = 521;
//    }
//    else if (flavor == 4)
//    {
//      mass_num = 1.25;
//      HF_pdgcode = 421;
//    }
//    else if (flavor == 1)
//    {
//      mass_num = 0.001;
//  //    followHardest = true;
//    }
//    
//  //  Naming Convention:
//  //  {$1}{$2}{$3}{$4}{$5}
//  //  $1: Year: 2016 = 6, 2017 = 7, 2018 = 8, All = 9
//  //  $2: jets or dijets: TaggedDijets = 1, else = 2
//  //  $3: flavor: b = 5, c = 4, udsg = 1
//  //  $4: pT: pt15pt20 = 0, pt20pt50 = 1, pt50 = 2, else = 3
//  //  $5: Magnet: MD = 0, MU = 1, Both = 9
//    TString str_pT = "";
//      
//    TString str_level = "";
//    TString str_flavor = "";
//
//    TString str_charged = "";
//    TString str_mag = "";
//
//    if (flavor == 1)
//      str_flavor = "_udsg";
//    else if (flavor == 4)
//      str_flavor = "_c";
//    else if (flavor == 5)
//      str_flavor = "_b";
//
//  // if(ptRange == 0) str_pT = "pt15pt20";
//  // else if(ptRange == 1) str_pT = "pt20pt50";
//  // else if(ptRange == 2) str_pT = "pt50";
//
//    if (truthLevel)
//      str_level = "truth";
//    else
//      str_level = "reco";
//    
//    if (isMagUp) {
//        str_mag = "MU";
//    } else if (isMagDown) {
//        str_mag = "MD";
//    } else {
//        str_mag = "";
//    }
//
//  // TString str_trees[5];
//  // str_trees[0] = "TaggedDijets/DecayTree";
//  // str_trees[1] = "D0KPiJet/DecayTree";
//  // str_trees[2] = "B0KPiJet/DecayTree";
//  // str_trees[3] = "Jets/DecayTree";
//  TString str_tree;

  TString extension, extension_RootFilesMC;
  // This should be the file from MCMakeVarTree
      
  extension_RootFilesMC = TString("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/BjetsMC/");

//  extension = TString("tree_") + str_level + str_mag + Form("_ev_%d", NumEvts) + str_flavor;
    
    TString extension, extension_eff;
    extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

//  BjetTree Tree_DiMuon(0, 11511, isData);
  // HFjetTree TreeAnti(0, dataset, !isData);

  cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
  if (NumEvts == -1)
    NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;
    
        TH1D *h1_z_12515 = new TH1D("z_12515", "", zbinsize, z_binedges);
        TH1D *h1_jt_12515 = new TH1D("jt_12515", "", jtbinsize, jt_binedges);
        TH1D *h1_r_12515 = new TH1D("r_12515", "", rbinsize, r_binedges);
    
        TH1D *h1_z_1520 = new TH1D("z_1520", "", zbinsize, z_binedges);
        TH1D *h1_jt_1520 = new TH1D("jt_1520", "", jtbinsize, jt_binedges);
        TH1D *h1_r_1520 = new TH1D("r_1520", "", rbinsize, r_binedges);
    
        TH1D *h1_z_2030 = new TH1D("z_2030", "", zbinsize, z_binedges);
        TH1D *h1_jt_2030 = new TH1D("jt_2030", "", jtbinsize, jt_binedges);
        TH1D *h1_r_2030 = new TH1D("r_2030", "", rbinsize, r_binedges);
    
        TH1D *h1_z_3050 = new TH1D("z_3050", "", zbinsize, z_binedges);
        TH1D *h1_jt_3050 = new TH1D("jt_3050", "", jtbinsize, jt_binedges);
        TH1D *h1_r_3050 = new TH1D("r_3050", "", rbinsize, r_binedges);
    
        TH1D *h1_z_50100 = new TH1D("z_50100", "", zbinsize, z_binedges);
        TH1D *h1_jt_50100 = new TH1D("jt_50100", "", jtbinsize, jt_binedges);
        TH1D *h1_r_50100 = new TH1D("r_50100", "", rbinsize, r_binedges);
    
        TH1D *h1_z_100150 = new TH1D("z_100150 ", "", zbinsize, z_binedges);
        TH1D *h1_jt_100150  = new TH1D("jt_100150 ", "", jtbinsize, jt_binedges);
        TH1D *h1_r_100150  = new TH1D("r_100150 ", "", rbinsize, r_binedges);

    TH2D *h2_denom_purity_ptr_MD = new TH2D("denom_purity_jetptr_MD", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    TH2D *h2_denom_purity_ptjt_MD = new TH2D("denom_purity_jetptjt_MD", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_denom_purity_ptz_MD = new TH2D("denom_purity_jetptz_MD", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
    
    
  double dtr_rap;
  double dtr_phi;
  double delta_rap;
  double delta_phi;

  TFile f(extension_RootFilesMC + extension + ".root", "RECREATE");

  double jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  double jet_rap, tr_jet_rap;
  double jet_px, jet_py, jet_pz, jet_e;
  double HF_px, HF_py, HF_pz, HF_e, HF_pt;
  double mup_px, mup_py, mup_pz, mup_e;
  double mum_px, mum_py, mum_pz, mum_e;
  double K_px, K_py, K_pz, K_e;
  double jpsi_ipchi2;
    
  double tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  double tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e, tr_HF_pt;
  double tr_mup_px, tr_mup_py, tr_mup_pz, tr_mup_e;
  double tr_mum_px, tr_mum_py, tr_mum_pz, tr_mum_e;
  double tr_K_px, tr_K_py, tr_K_pz, tr_K_e;
    
  double z, jt, r;
  double tr_z, tr_jt, tr_r;
    double zg, jtg, rg;

  int nSV, nSV_test;
  bool isTrueBjet, Hasbbbar;
  double dphi, Bmass_1, Bmass_2;
  double bmass_dtf;
  int NumBHads_tr, eventNumber;

  // TLorentzVector
  TTree *BTree = new TTree("BTree", "B Tree Variables");

  BTree->Branch("eventNumber", &eventNumber);

  BTree->Branch("jet_pt", &jet_pt);
  BTree->Branch("jet_eta", &jet_eta);
  BTree->Branch("jet_rap", &jet_rap);

  BTree->Branch("jet_px", &jet_px);
  BTree->Branch("jet_py", &jet_py);
  BTree->Branch("jet_pz", &jet_pz);
  BTree->Branch("jet_e", &jet_e);

  BTree->Branch("HF_px", &HF_px);
  BTree->Branch("HF_py", &HF_py);
  BTree->Branch("HF_pz", &HF_pz);
  BTree->Branch("HF_e", &HF_e);
  BTree->Branch("HF_pt", &HF_pt);

  BTree->Branch("mum_px", &mum_px);
  BTree->Branch("mum_py", &mum_py);
  BTree->Branch("mum_pz", &mum_pz);
  BTree->Branch("mum_e", &mum_e);

  BTree->Branch("mup_px", &mup_px);
  BTree->Branch("mup_py", &mup_py);
  BTree->Branch("mup_pz", &mup_pz);
  BTree->Branch("mup_e", &mup_e);

  BTree->Branch("K_px", &K_px);
  BTree->Branch("K_py", &K_py);
  BTree->Branch("K_pz", &K_pz);
  BTree->Branch("K_e", &K_e);

  BTree->Branch("jpsi_ipchi2", &jpsi_ipchi2);

  BTree->Branch("tr_jet_pt", &tr_jet_pt);
  BTree->Branch("tr_jet_eta", &tr_jet_eta);
  BTree->Branch("tr_jet_rap", &tr_jet_rap);

  BTree->Branch("tr_jet_px", &tr_jet_px);
  BTree->Branch("tr_jet_py", &tr_jet_py);
  BTree->Branch("tr_jet_pz", &tr_jet_pz);
  BTree->Branch("tr_jet_e", &tr_jet_e);

  BTree->Branch("tr_HF_px", &tr_HF_px);
  BTree->Branch("tr_HF_py", &tr_HF_py);
  BTree->Branch("tr_HF_pz", &tr_HF_pz);
  BTree->Branch("tr_HF_e", &tr_HF_e);
  BTree->Branch("tr_HF_pt", &tr_HF_pt);

  BTree->Branch("tr_mum_px", &tr_mum_px);
  BTree->Branch("tr_mum_py", &tr_mum_py);
  BTree->Branch("tr_mum_pz", &tr_mum_pz);
  BTree->Branch("tr_mum_e", &tr_mum_e);

  BTree->Branch("tr_mup_px", &tr_mup_px);
  BTree->Branch("tr_mup_py", &tr_mup_py);
  BTree->Branch("tr_mup_pz", &tr_mup_pz);
  BTree->Branch("tr_mup_e", &tr_mup_e);

  BTree->Branch("tr_K_px", &tr_K_px);
  BTree->Branch("tr_K_py", &tr_K_py);
  BTree->Branch("tr_K_pz", &tr_K_pz);
  BTree->Branch("tr_K_e", &tr_K_e);
    
  BTree->Branch("z", &z);
  BTree->Branch("jt", &jt);
  BTree->Branch("r", &r);
  BTree->Branch("zg", &zg);
  BTree->Branch("jtg", &jtg);
  BTree->Branch("rg", &rg);
  BTree->Branch("tr_z", &tr_z);
  BTree->Branch("tr_jt", &tr_jt);
  BTree->Branch("tr_r", &tr_r);

  BTree->Branch("isTrueBjet", &isTrueBjet);

  BTree->Branch("dphi", &dphi);
  BTree->Branch("Bmass_1", &Bmass_1);
  BTree->Branch("Bmass_2", &Bmass_2);
  BTree->Branch("nSV", &nSV);
    
  BTree->Branch("nSV_test", &nSV_test);
    
  BTree->Branch("bmass_dtf", &bmass_dtf);

  BTree->Branch("NumBHads_tr", &NumBHads_tr);
  BTree->Branch("Hasbbbar", &Hasbbbar);

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

    // cout<<tr_HFmeson.M()<<",";

    double HF_jet_dR = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
    double HF_jet_truedR = static_cast < TLorentzVector > (tr_HFmeson).DeltaR(tr_HFjet, kTRUE);
    bmass_dtf = Tree.Bu_ConsBu_M[0] / 1000.;
    // cout<<bmass_dtf<<endl;

    // bool mum_HLT1 = Tree.mum_Hlt1DiMuonHighMassDecision_TOS;
    // bool mum_HLT2 = Tree.mum_Hlt2DiMuonJpsi2MuMuDecision_TOS;

    // if(mup.Pt() < 0.25 || mum.Pt() < 0.25) continue;

    // if(Tree.eventNumber == 673310) cout<<"found event 673310"<<endl;

    if (Tree.nPVs > 1)
    {
      cut_npvs++;
      continue;
    }
    if (HFjet.Pt() < 12.5)
    {
      cut_jetpt++;
      continue;
    }
//    // cout<<Tree.Jet_SVTag_Tag<< ", "<< Tree.Jet_SVTag_Nvertices<<endl;
//    if (HFjet.Eta() < 2.2 || HFjet.Eta() > 4.2 )
//    {
//      cut_jeteta++;
//      continue;
//    }

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

    bool hasHFhadron = false;

    int NumBHads = 0;
    Bmass_1 = 0;
    Bmass_2 = 0;
    double B_energy = -99;
    // cout<<Tree.eventNumber<<endl;
    // cout<<HFjet.E()<<", "<<tr_HFjet.E()<<endl;
    // cout<<HFmeson.E()<<endl;

    double tot_e = 0;
    for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    {
      // if(Tree.eventNumber == 673310) cout<<Tree.Jet_Dtr_ID[dtrs0]<<endl;
      // cout<<(Tree.Jet_Dtr_PT[dtrs0]/HFjet.Pt()/1000.)<<",";
      // cout<<Tree.Jet_Dtr_ID[dtrs0]<<",";

      TLorentzVector dtr(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PY[dtrs0] / 1000.,
                         Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
                         Tree.Jet_Dtr_E[dtrs0] / 1000.);
        
      if (static_cast < TLorentzVector > (dtr).DeltaR(HFjet, kTRUE) > jetradius)
        continue;

      if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
      {
        HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
        hasHFhadron = true;
        NumBHads++;
        // cout<<dtr.Pt()<<endl;
      }
      
      // jet_Nmcdtrs++;
    }
    // cout<<endl;

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
      // cout<<Tree.Jet_mcjet_dtrID[dtrs0]<<",";
      TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
                         Tree.Jet_mcjet_dtrE[dtrs0] / 1000.);
        
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

      if (static_cast < TLorentzVector > (dtr).DeltaR(tr_HFjet, kTRUE) > jetradius)
        continue;

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
    if(static_cast < TLorentzVector > (tr_HFmeson).DeltaR(tr_HFjet, kTRUE) > jetradius) hasHFhadron_matched = false;
    // cout<<endl<<tr_HFmeson.Pt()<<endl;
 
    if (!hasHFhadron)
    {
      continue;
    }
   
    Hasbbbar = false;
      
    // SV tagging Efficiency
    if (Tree.hasb && Tree.hasbbar && Tree.Jet_SVTag_Tag)
      N_num++;
    if (Tree.hasb && Tree.hasbbar)
    {
      // cout<<Tree.hasb<<","<<Tree.hasbbar<<endl;
      Hasbbbar = true;
      N_denom++;
    }
    
      TVector3 HF_meson = HFmeson.Vect();
      TVector3 HF_jet = HFjet.Vect();
      TVector3 tr_HF_meson = tr_HFmeson.Vect();
      TVector3 tr_HF_jet = tr_HFjet.Vect();

      z = (HF_meson.Dot(HF_jet) ) / (HF_jet.Mag2() );
      jt = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
      r = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);

//                tr_z = (tr_HF_meson.Dot(tr_HF_jet) ) / (tr_HF_jet.Mag2() );
//                tr_jt = (tr_HF_jet.Cross(tr_HF_meson).Mag()) / (tr_HF_jet.Mag());
//                tr_r =  static_cast < TLorentzVector > (tr_HFmeson).DeltaR(tr_HFjet, kTRUE);
      
      if(hasHFhadron_matched ){
          tr_z = (tr_HF_meson.Dot(tr_HF_jet) ) / (tr_HF_jet.Mag2() );
          tr_jt = (tr_HF_jet.Cross(tr_HF_meson).Mag()) / (tr_HF_jet.Mag());
          tr_r =  static_cast < TLorentzVector > (tr_HFmeson).DeltaR(tr_HFjet, kTRUE);

          if(Hasbbbar){
              zg = (tr_HF_meson.Dot(tr_HF_jet) ) / (tr_HF_jet.Mag2() );
              jtg = (tr_HF_jet.Cross(tr_HF_meson).Mag()) / (tr_HF_jet.Mag());
              rg = static_cast < TLorentzVector > (tr_HFmeson).DeltaR(tr_HFjet, kTRUE);
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
      
      ///////////
      double MassMu = 5.27940;
      double MassSigma = 1.32479e-02;
      // double MassHigh = MassMu + 3 * MassSigma;
      // double MassLow = MassMu - 3 * MassSigma;
      double MassHigh = 5.31;
      double MassLow = 5.24;
      bool mass_cond = (bmass_dtf > MassLow && bmass_dtf < MassHigh);
        
  
      if (mass_cond && jet_pt > 12.5 && jet_eta < etaMax && jet_eta > etaMin)
          {
              
              h2_denom_purity_ptz_MD->Fill(z, jet_pt);
              h2_denom_purity_ptjt_MD->Fill(jt, jet_pt);
              h2_denom_purity_ptr_MD->Fill(r, jet_pt);
          }
      //////////////////
      
    if (hasHFhadron_matched)
    {
      isTrueBjet = true;
    }
    else
    {
      isTrueBjet = false;
      // cout<<jet_pt<<", "<<tr_jet_pt<<endl;
    }
      
    if (mass_cond && isTrueBjet && tr_jet_pt > 12.5 &&
          jet_pt > 12.5 &&
          jet_eta < etaMax && jet_eta > etaMin &&
          tr_jet_eta < etaMax && tr_jet_eta > etaMin)
    {
        if (jet_pt > 12.5 && jet_pt < 15.0 ) {
        
                  h1_z_12515->Fill(z);
                  h1_jt_12515->Fill(jt);
                  h1_r_12515->Fill(r);
              }
        
              if (jet_pt > 15.0 && jet_pt < 20.0 ) {
        
                  h1_z_1520->Fill(z);
                  h1_jt_1520->Fill(jt);
                  h1_r_1520->Fill(r);
              }
        
              if (jet_pt > 20.0 && jet_pt < 30.0 ) {
        
                  h1_z_2030->Fill(z);
                  h1_jt_2030->Fill(jt);
                  h1_r_2030->Fill(r);
              }
        
              if (jet_pt > 30.0 && jet_pt < 50.0 ) {
        
                  h1_z_3050->Fill(z);
                  h1_jt_3050->Fill(jt);
                  h1_r_3050->Fill(r);
              }
        
              if (jet_pt > 50.0 && jet_pt < 100.0 ) {
                  h1_z_50100->Fill(z);
                  h1_jt_50100->Fill(jt);
                  h1_r_50100->Fill(r);
              }
        
              if (jet_pt > 100.0 && jet_pt < 150.0 ) {
                  h1_z_100150->Fill(z);
                  h1_jt_100150->Fill(jt);
                  h1_r_100150->Fill(r);
              }
    }
          
    if (last_eventNum == Tree.eventNumber)
      NumSame++;
    last_eventNum = Tree.eventNumber;
    eventNumber = Tree.eventNumber;

    events++;
    // if(declusts.size()>0) {
    // cout<<"Filling";
    // if(Tree.eventNumber == 673310) cout<<"filling"<<endl;
    BTree->Fill();
    // }
  }
    
    h2_denom_purity_ptz_MD->Write("h2_denom_purity_ptz_MD");
    h2_denom_purity_ptjt_MD->Write("h2_denom_purity_ptjt_MD");
    h2_denom_purity_ptr_MD->Write("h2_denom_purity_ptr_MD");
    
    h1_z_12515->Write("h1_z_12515");
    h1_jt_12515->Write("h1_jt_12515");
    h1_r_12515->Write("h1_r_12515");

    h1_z_1520->Write("h1_z_1520");
    h1_jt_1520->Write("h1_jt_1520");
    h1_r_1520->Write("h1_r_1520");

    h1_z_2030->Write("h1_z_2030");
    h1_jt_2030->Write("h1_jt_2030");
    h1_r_2030->Write("h1_r_2030");

    h1_z_3050->Write("h1_z_3050");
    h1_jt_3050->Write("h1_jt_3050");
    h1_r_3050->Write("h1_r_3050");

    h1_z_50100->Write("h1_z_50100");
    h1_jt_50100->Write("h1_jt_50100");
    h1_r_50100->Write("h1_r_50100");

    h1_z_100150->Write("h1_z_100150");
    h1_jt_100150->Write("h1_jt_100150");
    h1_r_100150->Write("h1_r_100150");
    
    
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
