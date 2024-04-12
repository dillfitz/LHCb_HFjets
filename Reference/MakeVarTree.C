

//#include "AnalyzeDijetData_withsubsets.h"
//#include "LundPlaneData.h"



#include "DjetTree.C"
#include "DjetMCTree.C"
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "../Settings.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
// #include "../RooHelpers.h"
#include "../LundGen.hh"

using namespace fastjet;
using namespace std;



void MakeVarTree(int NumEvts_user = 10000, int dataset = 1510,bool isData = true,
              bool isPrompt = false,
              bool chargedJetCut_user = false){


  int NumEvts = NumEvts_user;
  int NumEvtsTruth = NumEvts_user;
  bool MCflag = !isData;
  followHardest = false;
  truthLevel = false;
  chargedJetCut = chargedJetCut_user;
  if(truthLevel){
    ghostCut = false;

  }


  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;

  if (flavor == 5) {
    mass_num = 4.2;
    HF_pdgcode = 521;
  }
  else if (flavor == 4) {
    mass_num = 1.25;
    HF_pdgcode = 421;
  }
  else if (flavor == 1) {
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
  TString str_prompt = "";

  TString str_charged = "";

  if(Mag == 0) str_Mag = "_MD";
  else if (Mag == 1) str_Mag = "_MU";

  if(flavor == 1) str_flavor = "_udsg";
  else if(flavor == 4) str_flavor = "_c";
  else if(flavor == 5) str_flavor = "_b";

  // if(ptRange == 0) str_pT = "pt15pt20";
  // else if(ptRange == 1) str_pT = "pt20pt50";
  // else if(ptRange == 2) str_pT = "pt50";

  if(isData) str_level = "data";
  else{
    if(truthLevel) str_level = "truth";
    else str_level = "reco";
  }


  if(flavor == 1) str_followHard = "_hard";
  else{
    if(followHardest) str_followHard = "_hard";
    else str_followHard = "_HF";
  }



  if(ghostCut) str_ghost = Form("_ghost_%.1f", ghostProb);
  if(isPrompt) str_prompt = "_prompt";

  if(chargedJetCut) str_charged = "_charge";
  // TString str_trees[5];
  // str_trees[0] = "TaggedDijets/DecayTree";
  // str_trees[1] = "D0KPiJet/DecayTree";
  // str_trees[2] = "B0KPiJet/DecayTree";
  // str_trees[3] = "Jets/DecayTree";
  TString str_tree;



  TString extension;
  extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts)
            + Form("_eta_%.1f%.1f", etaMin, etaMax)
            +  str_followHard
            +  str_ghost +str_charged + str_Mag
            + str_flavor + str_prompt+  Form("_%d", dataset);



  DjetTree Tree(0, dataset, isData);
  // HFjetTree TreeAnti(0, dataset, !isData);

  cout<<"Total number of events = "<<Tree.fChain->GetEntries()<<endl;
  if (NumEvts == -1) NumEvts = Tree.fChain->GetEntries();
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;



  cout<<"Executing CAJetAlgo"<<endl;
  double dtr_rap;
  double dtr_phi;
  double delta_rap;
  double delta_phi;

  TString dir_deadcone("$LUND/Djets/");

  TFile f(dir_deadcone+"hists/"+ extension+".root", "RECREATE");


  JetDefinition jet_def(cambridge_algorithm, jetradius);
  PseudoJet dtr1, dtr2;

  bool isTrueHFjet;

  double jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  double jet_rap, tr_jet_rap;
  double jet_px, jet_py, jet_pz, jet_e;
  double pi_px, pi_py, pi_pz, pi_e;
  double K_px, K_py, K_pz, K_e;

  double tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  double tr_pi_px, tr_pi_py, tr_pi_pz, tr_pi_e;
  double tr_K_px, tr_K_py, tr_K_pz, tr_K_e;

  int nsplits, ndtrs;
  int tr_nsplits, tr_ndtrs;
  int nSV, flav, parton_id;
  double D0_ipchi2;
  double dphi;

  vector<double> thetas, tr_thetas;
  vector<double> dRs, tr_dRs;
  vector<double> Erads, tr_Erads;
  vector<double> kts, tr_kts;
  vector<double> zs, tr_zs;
  vector<double> raps, tr_raps;
  vector<double> phis, tr_phis;
  // TLorentzVector
  TTree *LundTree = new TTree("LundTree","Lund Tree Variables");
  LundTree->Branch("thetas",&thetas);
  LundTree->Branch("Erads",&Erads);
  LundTree->Branch("dRs",&dRs);
  LundTree->Branch("kts",&kts);
  LundTree->Branch("zs",&zs);
  LundTree->Branch("raps",&raps);
  LundTree->Branch("phis",&phis);

  LundTree->Branch("jet_pt",&jet_pt);
  LundTree->Branch("jet_eta",&jet_eta);
  LundTree->Branch("jet_rap",&jet_rap);

  LundTree->Branch("jet_px",&jet_px);
  LundTree->Branch("jet_py",&jet_py);
  LundTree->Branch("jet_pz",&jet_pz);
  LundTree->Branch("jet_e",&jet_e);

  LundTree->Branch("ndtrs", &ndtrs);
  LundTree->Branch("nsplits", &nsplits);

  LundTree->Branch("pi_px",&pi_px);
  LundTree->Branch("pi_py",&pi_py);
  LundTree->Branch("pi_pz",&pi_pz);
  LundTree->Branch("pi_e",&pi_e);

  LundTree->Branch("K_px",&K_px);
  LundTree->Branch("K_py",&K_py);
  LundTree->Branch("K_pz",&K_pz);
  LundTree->Branch("K_e",&K_e);

  LundTree->Branch("D0_ipchi2", &D0_ipchi2);

  LundTree->Branch("tr_thetas",&tr_thetas);
  LundTree->Branch("tr_Erads",&tr_Erads);
  LundTree->Branch("tr_dRs",&tr_dRs);
  LundTree->Branch("tr_kts",&tr_kts);
  LundTree->Branch("tr_zs",&tr_zs);
  LundTree->Branch("tr_raps",&tr_raps);
  LundTree->Branch("tr_phis",&tr_phis);

  LundTree->Branch("tr_jet_pt",&tr_jet_pt);
  LundTree->Branch("tr_jet_eta",&tr_jet_eta);
  LundTree->Branch("tr_jet_rap",&tr_jet_rap);

  LundTree->Branch("tr_jet_px",&tr_jet_px);
  LundTree->Branch("tr_jet_py",&tr_jet_py);
  LundTree->Branch("tr_jet_pz",&tr_jet_pz);
  LundTree->Branch("tr_jet_e",&tr_jet_e);


  LundTree->Branch("tr_pi_px",&tr_pi_px);
  LundTree->Branch("tr_pi_py",&tr_pi_py);
  LundTree->Branch("tr_pi_pz",&tr_pi_pz);
  LundTree->Branch("tr_pi_e",&tr_pi_e);

  LundTree->Branch("tr_K_px",&tr_K_px);
  LundTree->Branch("tr_K_py",&tr_K_py);
  LundTree->Branch("tr_K_pz",&tr_K_pz);
  LundTree->Branch("tr_K_e",&tr_K_e);

  LundTree->Branch("tr_ndtrs", &tr_ndtrs);
  LundTree->Branch("tr_nsplits", &tr_nsplits);
  LundTree->Branch("isTrueHFjet", &isTrueHFjet);

  LundTree->Branch("dphi", &dphi);
  LundTree->Branch("nSV", &nSV);
  LundTree->Branch("flav", &flav);
  LundTree->Branch("parton_id", &parton_id);




  //TClonesArray *arr = new TClonesArray("TLorentzVector");

  //
  // Event loop
  //

  int eventNum;
  unsigned long long last_eventNum = 0;
  int events = 0;

  bool maxjetpT_found = false;


  double mean_sec = 1.8045e+00;
  double sigma_sec = 8.3712e-01;

  int cut_npvs = 0;
  int cut_jetpt = 0;
  int cut_jeteta = 0;
  int cut_Dinjet = 0;
  int cut_prompt = 0;
  int cut_hasHF = 0;

  for(int ev = 0; ev < NumEvts; ev++)
  {
    Tree.GetEntry(ev);

    if (ev%10000==0) cout<<"Executing event "<<ev<<endl;

    if(ev!=0){
            if(Tree.eventNumber != last_eventNum){
              maxjetpT_found = false;
            }
        }

    last_eventNum = Tree.eventNumber;
    double min_dr = 999;
    int n_mindr_cand = -999;
    int n_mindr_entry = -999;
    TLorentzVector HFjet, recojet, tr_truthjet, HFmeson,  pi, Kmeson;
    TLorentzVector tr_HFjet, tr_Kmeson, tr_pi, tr_HFmeson;


    vector<PseudoJet> jetdtrs, tr_jetdtrs;

    //TLorentzVector recojet, tr_Zjet, zjet;
    pi.SetPxPyPzE(Tree.pi_PX/1000., Tree.pi_PY/1000., Tree.pi_PZ/1000., Tree.pi_PE/1000.);
    Kmeson.SetPxPyPzE(Tree.K_PX/1000., Tree.K_PY/1000., Tree.K_PZ/1000., Tree.K_PE/1000.);

    HFjet.SetPxPyPzE(Tree.Jet_PX/1000.,
         Tree.Jet_PY/1000.,
         Tree.Jet_PZ/1000.,
         Tree.Jet_PE/1000.);


    //cout<<tr_truemumpx<<",";
   tr_HFjet.SetPxPyPzE(Tree.Jet_mcjet_PX/1000.,
          Tree.Jet_mcjet_PY/1000.,
          Tree.Jet_mcjet_PZ/1000.,
          Tree.Jet_mcjet_PE/1000.);


    tr_pi.SetPxPyPzE(Tree.pi_TRUEP_X/1000., Tree.pi_TRUEP_Y/1000.,
                      Tree.pi_TRUEP_Z/1000., Tree.pi_TRUEP_E/1000.);
    tr_Kmeson.SetPxPyPzE(Tree.K_TRUEP_X/1000., Tree.K_TRUEP_Y/1000.,
                      Tree.K_TRUEP_Z/1000., Tree.K_TRUEP_E/1000.);



    HFmeson = pi + Kmeson;
    tr_HFmeson = tr_pi + tr_Kmeson;
    //cout<<tr_HFmeson.M()<<",";

    double HF_jet_dR = HFmeson.DeltaR(HFjet);
    double HF_jet_truedR = tr_HFmeson.DeltaR(tr_HFjet);

    // if(Tree.totCandidates > 1){
    //   cout<<HFjet.Pt()<< ", "<< HFmeson.Pt() << endl;
    // }

    if(Tree.nPVs>1){
      cut_npvs++;
      continue;
    }
    if(HFjet.Pt() < 15.){
      cut_jetpt++;
      continue;
    }
    if(HFjet.Eta() < etaMin || HFjet.Eta() > etaMax){
      cut_jeteta++;
      continue;
    }
    if(HF_jet_dR > jetradius){
      cut_Dinjet++;
      continue;
    }
    if(isPrompt){
      if(log10(Tree.D0_IPCHI2_OWNPV) > (mean_sec - 2*sigma_sec) ){
        cut_prompt++;
        continue;
      }
    }

    // if(dataset == 99499){
    //   if(Tree.Jet_SVTag_Nvertices > 0) continue;
    // }
    nSV = Tree.Jet_SVTag_Nvertices;
    flav = Tree.Jet_mcjet_FLAV;

    double leading_pT = 0;
    int n_maxpT_cand = -999;
    int n_maxpT_entry = -999;
    double testjet_phi;
    int ncand = Tree.nCandidate;

    dphi = 3.1415;
    // cout<<"Event = "<<ev<<endl;
    // cout<<"tot Cands = "<<Tree.totCandidates<<endl;
    vector<double> jetpts; 
    bool JetFound = false;
    if(Tree.totCandidates > 1){
      for(int icand = 0; icand < Tree.totCandidates; icand++){
          Tree.GetEntry(ev+icand-ncand);
          // cout<<"entry = "<<ev+icand-ncand<<endl;
          // Tree.GetEntry(ev+icand);

          pi.SetPxPyPzE(Tree.pi_PX/1000., Tree.pi_PY/1000., Tree.pi_PZ/1000., Tree.pi_PE/1000.);
          Kmeson.SetPxPyPzE(Tree.K_PX/1000., Tree.K_PY/1000., Tree.K_PZ/1000., Tree.K_PE/1000.);

          HFjet.SetPxPyPzE(Tree.Jet_PX/1000.,
               Tree.Jet_PY/1000.,
               Tree.Jet_PZ/1000.,
               Tree.Jet_PE/1000.);
         HFmeson = pi + Kmeson;
         for(int j = 0; j < jetpts.size(); j++){
            if(fabs(HFjet.Pt() - jetpts[j]) < 1e-3) JetFound = true;
         }
         if(JetFound) continue;
         else jetpts.push_back(HFjet.Pt());

         
        //  cout<<"Jet pt = "<<HFjet.Pt()<<", HF pt = "<<HFmeson.Pt()<<endl;
         if(HFmeson.DeltaR(HFjet) < jetradius){
          // cout<<"Has hf!"<<endl;
          continue;
         }

          double cand_jetpt = HFjet.Pt();
          if(cand_jetpt > leading_pT){
            leading_pT = cand_jetpt;
            n_maxpT_cand = Tree.nCandidate;
            n_maxpT_entry = ev+icand-ncand;
            // cout<<"nmax = "<<n_maxpT_entry<<endl;
          }

        }
        Tree.GetEntry(n_maxpT_entry);
        // cout<<"nmax = "<<n_maxpT_entry<<endl;
        HFjet.SetPxPyPzE(Tree.Jet_PX/1000.,
             Tree.Jet_PY/1000.,
             Tree.Jet_PZ/1000.,
             Tree.Jet_PE/1000.);
        testjet_phi = HFjet.Phi();
    }
    Tree.GetEntry(ev);

    pi.SetPxPyPzE(Tree.pi_PX/1000., Tree.pi_PY/1000., Tree.pi_PZ/1000., Tree.pi_PE/1000.);
    Kmeson.SetPxPyPzE(Tree.K_PX/1000., Tree.K_PY/1000., Tree.K_PZ/1000., Tree.K_PE/1000.);

    HFjet.SetPxPyPzE(Tree.Jet_PX/1000.,
         Tree.Jet_PY/1000.,
         Tree.Jet_PZ/1000.,
         Tree.Jet_PE/1000.);


    //cout<<tr_truemumpx<<",";
   tr_HFjet.SetPxPyPzE(Tree.Jet_mcjet_PX/1000.,
          Tree.Jet_mcjet_PY/1000.,
          Tree.Jet_mcjet_PZ/1000.,
          Tree.Jet_mcjet_PE/1000.);


    tr_pi.SetPxPyPzE(Tree.pi_TRUEP_X/1000., Tree.pi_TRUEP_Y/1000.,
                      Tree.pi_TRUEP_Z/1000., Tree.pi_TRUEP_E/1000.);
    tr_Kmeson.SetPxPyPzE(Tree.K_TRUEP_X/1000., Tree.K_TRUEP_Y/1000.,
                      Tree.K_TRUEP_Z/1000., Tree.K_TRUEP_E/1000.);



    HFmeson = pi + Kmeson;
    tr_HFmeson = tr_pi + tr_Kmeson;

    if(Tree.totCandidates > 1){
        dphi = checkphi(fabs(checkphi((HFmeson.Phi()) - checkphi(testjet_phi))));
    }
    // if(HFmeson.M() < 5.2) continue;

    bool hasHFhadron = false;
    for(int dtrs0=0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
    {
      // cout<<(Tree.Jet_Dtr_PT[dtrs0]/HFjet.Pt()/1000.)<<",";
      double trchi2ndf = Tree.Jet_Dtr_TrackChi2[dtrs0]/Tree.Jet_Dtr_TrackNDF[dtrs0];
      TLorentzVector dtr(Tree.Jet_Dtr_PX[dtrs0]/1000.,
                              Tree.Jet_Dtr_PY[dtrs0]/1000.,
                              Tree.Jet_Dtr_PZ[dtrs0]/1000.,
                              Tree.Jet_Dtr_E[dtrs0]/1000.);

      bool dtrpass = true;

      dtrpass = DtrCuts(dtr, Tree.Jet_Dtr_ThreeCharge[dtrs0], Tree.Jet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
      if(abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode) dtrpass = true;
      if(!dtrpass) continue;
      if(dtr.DeltaR(HFjet) > jetradius) continue;
      jetdtrs.push_back( PseudoJet(Tree.Jet_Dtr_PX[dtrs0]/1000.,
                              Tree.Jet_Dtr_PY[dtrs0]/1000.,
                              Tree.Jet_Dtr_PZ[dtrs0]/1000.,
                              Tree.Jet_Dtr_E[dtrs0]/1000.) );
      jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_Dtr_ID[dtrs0]));
      if(abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode) hasHFhadron = true;
      //jet_Nmcdtrs++;
    }
    // cout<<endl;
    if(!hasHFhadron){
      cut_hasHF++;
      continue;
    }
//    parton_id = -99;
//    bool hasHFhadron_matched = false;
//    for(int dtrs0=0; dtrs0 < Tree.Jet_mcjet_nmcdtrs; dtrs0++)
//    {
//      double trchi2ndf = 0;
//      TLorentzVector dtr(Tree.Jet_mcjet_dtrPX[dtrs0]/1000.,
//                              Tree.Jet_mcjet_dtrPY[dtrs0]/1000.,
//                              Tree.Jet_mcjet_dtrPZ[dtrs0]/1000.,
//                              Tree.Jet_mcjet_dtrE[dtrs0]/1000.) ;
//
//      bool dtrpass = true;
//
//      dtrpass = DtrCuts(dtr, Tree.Jet_mcjet_dtrThreeCharge[dtrs0], 0, 0, chargedJetCut);
//      if(abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode) dtrpass = true;
//      if(!dtrpass) continue;
//      if(dtr.DeltaR(tr_HFjet) > jetradius) continue;
//      tr_jetdtrs.push_back( PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0]/1000.,
//                              Tree.Jet_mcjet_dtrPY[dtrs0]/1000.,
//                              Tree.Jet_mcjet_dtrPZ[dtrs0]/1000.,
//                              Tree.Jet_mcjet_dtrE[dtrs0]/1000.) );
//      tr_jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_mcjet_dtrID[dtrs0]));
//      if(abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode){
//        hasHFhadron_matched = true;
//        parton_id = abs(Tree.Jet_mcjet_TopMotherID[dtrs0]);
//        // tr_HFmeson = dtr;
//      }
//      //jet_Nmcdtrs++;
//    }
    // if(hasHFhadron_matched && fabs(HFmeson.E() - tr_HFmeson.E()) > 5){
    //   cout<<"("<< HFmeson.Px()<<", "<< tr_HFmeson.Px()<< ")"<<endl;
    //   cout<<"("<< HFmeson.Py()<<", "<< tr_HFmeson.Py()<< ")"<<endl;
    //   cout<<"("<< HFmeson.Pz()<<", "<< tr_HFmeson.Pz()<< ")"<<endl;
    //   cout<<"("<< HFmeson.E()<<", "<< tr_HFmeson.E()<< ")"<<endl;
    // }


//    //cout<<"Starting dijet loop";
//    thetas.clear();
//    dRs.clear();
//    Erads.clear();
//    kts.clear();
//    zs.clear();
//    raps.clear();
//    phis.clear();
//    tr_thetas.clear();
//    tr_dRs.clear();
//    tr_Erads.clear();
//    tr_kts.clear();
//    tr_zs.clear();
//    tr_raps.clear();
//    tr_phis.clear();

//    vector<LundDeclustering> declusts;
//
//    if(jetdtrs.size() > 1){
//      ClusterSequence cs(jetdtrs, jet_def);
//      vector<PseudoJet> constit;
//      vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
//      PseudoJet mom = jets[0];
//      constit = mom.constituents();
//      int had_loc = -99;
//      for(int i = 0; i < constit.size();i++){
//        if(abs(constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
//        {
//          had_loc = i;
//          break;
//        }
//      }
//      if (had_loc > -1)  declusts = result(mom, constit[had_loc]);
//      // Decluster jet by following either hardest prong or HF prong
//      // Store info such as kt, Eradiator, theta, delta R
//      // cout<<"Reco Declust!"<<endl;
//      for (int idecl = 0; idecl < declusts.size(); idecl++) {
//        double kt = declusts[idecl].kt(); kts.push_back(kt);
//        double dR = declusts[idecl].Delta(); dRs.push_back(dR);
//        double z = declusts[idecl].z(); zs.push_back(z);
//        double theta = declusts[idecl].theta(); thetas.push_back(theta);
//        double erad = declusts[idecl].erad(); Erads.push_back(erad);
//        double rap = declusts[idecl].rap(); raps.push_back(rap);
//        double phi = declusts[idecl].phi(); phis.push_back(phi);
//      }
//    }
//
//
//    vector<LundDeclustering> tr_declusts;
//    if(!isData){
//      if(tr_jetdtrs.size() > 1){
//        ClusterSequence cs_tr_(tr_jetdtrs, jet_def);
//        vector<PseudoJet> tr_constit;
//        vector<PseudoJet> tr_jets = sorted_by_pt(cs_tr_.inclusive_jets());
//        PseudoJet tr_mom = tr_jets[0];
//
//        tr_constit = tr_mom.constituents();
//        int tr_had_loc = -99;
//        for(int i = 0; i < tr_constit.size();i++){
//          if(abs(tr_constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
//          {
//            tr_had_loc = i;
//            break;
//          }
//        }
//        // cout<<"Truth Declust!"<<endl;
//        if(tr_had_loc > -1) tr_declusts = result(tr_mom, tr_constit[tr_had_loc]);
//      };
//      for (int idecl = 0; idecl < tr_declusts.size(); idecl++) {
//        double kt = tr_declusts[idecl].kt(); tr_kts.push_back(kt);
//        double dR = tr_declusts[idecl].Delta(); tr_dRs.push_back(dR);
//        double z = tr_declusts[idecl].z(); tr_zs.push_back(z);
//        double theta = tr_declusts[idecl].theta(); tr_thetas.push_back(theta);
//        double erad = tr_declusts[idecl].erad(); tr_Erads.push_back(erad);
//        double rap = tr_declusts[idecl].rap(); tr_raps.push_back(rap);
//        double phi = tr_declusts[idecl].phi(); tr_phis.push_back(phi);
//      }
//    }

    jet_pt = HFjet.Pt();
    jet_eta = HFjet.Eta();
    jet_rap = HFjet.Rapidity();
    jet_px = HFjet.Px();
    jet_py = HFjet.Py();
    jet_pz= HFjet.Pz();
    jet_e = HFjet.E();
    pi_px = pi.Px();
    pi_py = pi.Py();
    pi_pz = pi.Pz();
    pi_e = pi.E();
    K_px = Kmeson.Px();
    K_py = Kmeson.Py();
    K_pz= Kmeson.Pz();
    K_e = Kmeson.E();
    ndtrs = jetdtrs.size();
    nsplits = kts.size();
    D0_ipchi2 = Tree.D0_IPCHI2_OWNPV;

    tr_jet_eta = tr_HFjet.Eta();
    tr_jet_rap = tr_HFjet.Rapidity();
    tr_jet_pt = tr_HFjet.Pt();
    tr_jet_px = tr_HFjet.Px();
    tr_jet_py = tr_HFjet.Py();
    tr_jet_pz= tr_HFjet.Pz();
    tr_jet_e = tr_HFjet.E();

    tr_pi_px = tr_pi.Px();
    tr_pi_py = tr_pi.Py();
    tr_pi_pz = tr_pi.Pz();
    tr_pi_e = tr_pi.E();
    tr_K_px = tr_Kmeson.Px();
    tr_K_py = tr_Kmeson.Py();
    tr_K_pz= tr_Kmeson.Pz();
    tr_K_e = tr_Kmeson.E();
    tr_ndtrs = tr_jetdtrs.size();
    tr_nsplits = tr_kts.size();

    if(hasHFhadron_matched) isTrueHFjet = true;
    else isTrueHFjet = false;

    events++;
    LundTree->Fill();

  }
  cout<<"Total number of events processed = "<<events<<endl;
  cout<<"Events blocked: "<<endl;
  cout<<"npvs = "<< cut_npvs<<endl;
  cout<<"jetpt = "<< cut_jetpt<<endl;
  cout<<"jeteta = "<< cut_jeteta<<endl;
  cout<<"prompt = "<< cut_prompt<<endl;
  cout<<"Dinjet = "<< cut_Dinjet<<endl;
  cout<<"hasHF = "<< cut_hasHF<<endl;

  f.Write();
  f.Close();
}
//
