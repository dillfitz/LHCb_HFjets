

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include "./BjetTree.C"  //Truth
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
//// #include "../RooHelpers.h"

using namespace std;

void MakeVarTree(int NumEvts_user = -1,
                 int dataset = 91599,
                 bool isData = true,
                 bool chargedJetCut_user = false,
                 bool DoJER = false,
                 bool DoJES = true,
                 bool DoJetID = false,
                 bool DoFSPEff = false,
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
    TString extension_read, extension_RootFilesMC, extension_RootFilesData, extension_RootFiles;
    TString extension, extension_eff;
    
    extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
    
    extension_eff = TString("fspeff_") + "truth" + Form("_ev_%d", -1) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_flavor + Form("_%d", 91599);

    if (DoJES)
        extension = TString("JES_") + extension;
    if (DoJER)
        extension = TString("JER_") + extension;
    if (DoFSPEff)
        extension = TString("fspeff_") + extension;
    if (DoTrackPt)
        extension = TString("trackpt_") + extension;
    if (DoGhostCut)
        extension = TString("ghostcut_") + extension;
    if (DoJetID)
        extension = TString("jetid_") + extension;
        

    // extension_pideff = "effhists-Turbo" + str_year + str_Mag + "-K-DLLK>0-P.ETA.nTracks";
    ////////////////////////////////////////////////////
    ///              Tracking and PID
    //////////////////////////////////////////////////
    TString extension_pideffMu, extension_pideffK, extension_trackeff, extension_trackeff_Data, extension_trackeff_MC;
    TString extension_trackeff_Muon;
    TString eff_path;
    eff_path = TString( "../../Effs/");
   

    TH3D *h3_pideff_K_P_ETA_nTracks;
    TH3D *h3_pideff_Mu_P_ETA_nTracks;
    TH2D *h2_ratio_trkeff_P_ETA, *h2_ratio_trkeff_P_ETA_ERRHI, *h2_ratio_trkeff_P_ETA_ERRLO;
    TH2D *h2_ratio_trkeff_P_ETA_Muon, *h2_ratio_trkeff_P_ETA_Muon_ERRHI, *h2_ratio_trkeff_P_ETA_Muon_ERRLO;
    TH2D *h2_ratio_trkeff_P_ETA_DATA, *h2_ratio_trkeff_P_ETA_MC;

    extension_pideffK = "effhists-Turbo" + str_year + str_Mag + "-K-Brunel_DLLK>0-P.ETA.nTracks_Brunel";
    extension_pideffMu = "effhists-Turbo" + str_year + str_Mag + "-Mu-IsMuon&Brunel_DLLmu>0-P.ETA.nTracks_Brunel";
    extension_trackeff = "trackEff_" + str_year + "_Ratio_Full_Long_method";
    extension_trackeff_Muon = "trackEff_Muon_" + str_year + "_Ratio_Full_Long_method";
    extension_trackeff_Data = "trackEff_" + str_year + "_Data_Full_Long_method";
    extension_trackeff_MC = "trackEff_" + str_year + "_MC_Full_Long_method";
    
    TFile file_trackeff(eff_path+ "TrackEff/" + extension_trackeff + ".root", "READ");
    TFile file_trackeff_Muon(eff_path+ "TrackEff/" + extension_trackeff_Muon + ".root", "READ");
    TFile file_trackeff_Data(eff_path+ "TrackEff/" + extension_trackeff_Data + ".root", "READ");
    TFile file_trackeff_MC(eff_path+ "TrackEff/" + extension_trackeff_MC + ".root", "READ");
    TFile file_pideffK(eff_path + "PIDEff/" + extension_pideffK + ".root", "READ");
    TFile file_pideffMu(eff_path + "PIDEff/" + extension_pideffMu + ".root", "READ");

    cout << extension_pideffK << endl;
    cout << extension_pideffMu << endl;
    cout << extension_trackeff << endl;

    h2_ratio_trkeff_P_ETA_Muon = (TH2D *)file_trackeff_Muon.Get("hP_ETA");
    h2_ratio_trkeff_P_ETA_Muon_ERRHI = (TH2D *)file_trackeff_Muon.Get("hP_ETA_errhi");
    h2_ratio_trkeff_P_ETA_Muon_ERRLO = (TH2D *)file_trackeff_Muon.Get("hP_ETA_errlo");

    h2_ratio_trkeff_P_ETA = (TH2D *)file_trackeff.Get("hP_ETA");
    h2_ratio_trkeff_P_ETA_DATA = (TH2D *)file_trackeff_Data.Get("hP_ETA");
    h2_ratio_trkeff_P_ETA_MC = (TH2D *)file_trackeff_MC.Get("hP_ETA");
    h2_ratio_trkeff_P_ETA_ERRHI = (TH2D *)file_trackeff.Get("hP_ETA_errhi");
    h2_ratio_trkeff_P_ETA_ERRLO = (TH2D *)file_trackeff.Get("hP_ETA_errlo");
    h3_pideff_K_P_ETA_nTracks = (TH3D *)file_pideffK.Get("eff_Brunel_DLLK>0");
    h3_pideff_Mu_P_ETA_nTracks = (TH3D *)file_pideffMu.Get("eff_IsMuon&Brunel_DLLmu>0");

    //////////////////////////////////////////////////
    ///              Trigger
    ////////////////////////////////////////////////
    TString extension_trig_MC, extension_trig_Data, extension_RootFilesTrig;
    extension_RootFilesTrig = TString("../../root_files/TrigEff/");
    
    TH2D *h2_trigeff_Data;
    TH2D *h2_trigeff_MC;

    extension_trig_MC = "jpsieff_reco_ev_-1_b_91599";
    extension_trig_Data = "jpsieff_data_ev_-1_b_91599";

    TFile file_trigeffMC(extension_RootFilesTrig+ extension_trig_MC + ".root", "READ");
    TFile file_trigeffData(extension_RootFilesTrig + extension_trig_Data + ".root", "READ");

    h2_trigeff_Data = (TH2D *)file_trigeffData.Get("efficiency_Jpsiptrap");
    h2_trigeff_MC = (TH2D *)file_trigeffMC.Get("efficiency_Jpsiptrap");
    TH2D *h2_trigeff_ratio = (TH2D *)h2_trigeff_Data->Clone("h2_trigeff_ratio");
    h2_trigeff_ratio->Divide(h2_trigeff_MC);

    BjetTree Tree(0, dataset, isData);
//    BjetTree Tree_DiMuon(0, 11511, isData);
    // HFjetTree TreeAnti(0, dataset, !isData);

    cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
    if (NumEvts == -1)
        NumEvts = Tree.fChain->GetEntries();
    // int NumEvts = 0;
    // cout <<"Choose number of events (-1: All Events, or enter integer): ";
    // cin>> NumEvts;

    cout << "Executing CAJetAlgo" << endl;

    extension_RootFilesMC = TString("../../root_files/BjetsMC/");
    extension_RootFilesData = TString("../../root_files/Bjets/");
    extension_RootFiles = isData ? "../../root_files/Bjets/" : "../../root_files/BjetsMC/"; 

    TFile *file_eff;
    TH2D *h2_trk_eff;
    TH2D *h2_neut_eff;
    // if (DoFSPEff)
    // {
    //   file_eff = new TFile(dir_deadcone + "hists/" + extension_eff + ".root", "READ");
    //   h2_trk_eff = (TH2D *)file_eff->Get("trk_eff_sys");
    //   h2_neut_eff = (TH2D *)file_eff->Get("neut_eff_sys");
    // }

    //if (isData)
    //  TFile f( extension_RootFilesData +  extension + ".root", "RECREATE");
    //else
    //   TFile f( extension_RootFilesMC +  extension + ".root", "RECREATE");   

    TFile f(extension_RootFiles + extension + ".root", "RECREATE");
    
    TH1F *h1_TIS = new TH1F("h1_TIS", "", ptJpsibinsize, ptJpsi_binedges);
    TH1F *h1_TISTOS = new TH1F("h1_TISTOS", "", ptJpsibinsize, ptJpsi_binedges);

    TH2F *h2_TIS_ptrap = new TH2F("h2_TIS_ptrap", "", ptJpsibinsize, ptJpsi_binedges, HFetabinsize, HFeta_binedges);
    TH2F *h2_TISTOS_ptrap = new TH2F("h2_TISTOS_ptrap", "", ptJpsibinsize, ptJpsi_binedges, HFetabinsize, HFeta_binedges);

    // TH1D *h1_Mcor_true = new TH1D("h1_Mcor_true", "", 30, 0, 15.);
    // TH1D *h1_Mcor_false = new TH1D("h1_Mcor_false", "", 30, 0, 15.);

    // TH1D *h1_svmass_true = new TH1D("h1_svmass_true", "", 30, 0, 6.);
    // TH1D *h1_svmass_false = new TH1D("h1_svmass_false", "", 30, 0, 6.);

    // TH1D *h1_z_true = new TH1D("h1_z_true", "", 20, 0, 1.05);
    // TH1D *h1_z_false = new TH1D("h1_z_false", "", 20, 0, 1.05);
    // TH1D *h1_z = new TH1D("h1_z", "", 20, 0, 1.05);

    // TH1D *h1_chi2_true = new TH1D("h1_chi2_true", "", 20, -4., 4.);
    // TH1D *h1_chi2_false = new TH1D("h1_chi2_false", "", 20, -4., 4.);

//    float small_radius = 0.2;
//    // JetDefinition jet_def(cambridge_algorithm, jetradius);
//    JetDefinition jet_def(cambridge_algorithm, JetDefinition::max_allowable_R);
//    JetDefinition small_jets(antikt_algorithm, small_radius);
//    PseudoJet dtr1, dtr2;

    float jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
    float jet_rap, tr_jet_rap;
    float jet_px, jet_py, jet_pz, jet_e, jet_charge;
    float HF_px, HF_py, HF_pz, HF_e, HF_pt;
    float Jpsi_px, Jpsi_py, Jpsi_pz, Jpsi_e;
    float mup_px, mup_py, mup_pz, mup_e;
    float mum_px, mum_py, mum_pz, mum_e;
    float K_px, K_py, K_pz, K_e, K_p, K_eta;
    float mup_CHI2NDOF, mup_GHOSTPROB, mup_IPCHI2;
    float mum_CHI2NDOF, mum_GHOSTPROB, mum_IPCHI2;
    float K_CHI2NDOF, K_GHOSTPROB, K_IPCHI2;
    float Jpsi_CHI2NDOF, Jpsi_CHI2, Jpsi_FDCHI2, Jpsi_BPVDLS, Jpsi_IPCHI2;
    float Bu_CHI2NDOF, Bu_CHI2, Bu_IPCHI2;
    int nTracks, nSPDHits;
    float jpsi_ipchi2, k_ipchi2;
    float Bfromjet_px, Bfromjet_py, Bfromjet_pz, Bfromjet_e;
    float K_PIDK;

    float tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
    float tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e, tr_HF_pt;
    float tr_mup_px, tr_mup_py, tr_mup_pz, tr_mup_e;
    float tr_mum_px, tr_mum_py, tr_mum_pz, tr_mum_e;
    float tr_K_px, tr_K_py, tr_K_pz, tr_K_e;
    
    double z, jt, r;
    double tr_z, tr_jt, tr_r;
    double zg, jtg, rg;

    int nsplits, ndtrs, ndtrs_noghost, NumSubJets;
    int tr_nsplits, tr_ndtrs;
    int nSV, nSV_test;
    bool isTrueBjet, isBacktoBack, HFHardest, Hasbbbar;
    float dphi, Bmass_1, Bmass_2;
    float bmass_dtf, chi2ndf_dtf, tau_dtf;
    int NumBHads_tr, eventNumber;
    
    float pideff_K(1.0), pideff_mup(1.0), pideff_mum(1.0);
    float pideff_K_err(1.0), pideff_mup_err(1.0), pideff_mum_err(1.0);
    float trkeff_K(1.0), trkeff_mup(1.0), trkeff_mum(1.0);
    float trkeff_K_errhi(1.0), trkeff_mup_errhi(1.0), trkeff_mum_errhi(1.0);
    float trkeff_K_errlo(1.0), trkeff_mup_errlo(1.0), trkeff_mum_errlo(1.0);
    float trigeff_Data(1.0), trigeff_MC(1.0), trigeff_ratio(1.0);
    int Ndtr_neutral, Ndtr_charged;
    
    vector<float> dtr_pt, dtr_rap, dtr_id, dtr_3charge;
    
//    vector<float> thetas, tr_thetas;
//    vector<float> ktthetas, tr_ktthetas;
//    vector<float> dRs, tr_dRs;
//    vector<float> Erads, tr_Erads;
//    vector<float> kts, tr_kts;
//    vector<float> zs, tr_zs;
//    vector<float> raps, tr_raps;
//    vector<float> phis, tr_phis;
    
    vector<bool> hardest, tr_hardest;
    vector<float> sv_ipchi2, sv_keys, sv_pids;

    float sv_mass, sv_chi2, sv_cosine, sv_ntrks;
    float bdt_mCor, bdt_0, bdt_1, bdt_pt, bdt_z;
    float bdt_px, bdt_py, bdt_pz, bdt_e;
    int SVTag;

    bool mup_L0, mum_L0;
    bool jpsi_L0, jpsi_Hlt1, jpsi_Hlt2;
    bool Trig, TIS, TOS;
    // TLorentzVector
    TTree *BTree = new TTree("BTree", "B-jets Tree Variables");

    BTree->Branch("eventNumber", &eventNumber);

    BTree->Branch("dtr_pt", &dtr_pt);
    BTree->Branch("dtr_rap", &dtr_rap);
    BTree->Branch("dtr_id", &dtr_id);
    BTree->Branch("dtr_3charge", &dtr_3charge);
    BTree->Branch("Ndtr_neutral", &Ndtr_neutral);
    BTree->Branch("Ndtr_charged", &Ndtr_charged);

//    BTree->Branch("thetas", &thetas);
//    BTree->Branch("ktthetas", &ktthetas);
//    BTree->Branch("Erads", &Erads);
//    BTree->Branch("dRs", &dRs);
//    BTree->Branch("kts", &kts);
//    BTree->Branch("zs", &zs);
//    BTree->Branch("raps", &raps);
//    BTree->Branch("phis", &phis);
    
    BTree->Branch("hardest", &hardest);

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

    BTree->Branch("Bu_IPCHI2", &Bu_IPCHI2);
    BTree->Branch("Bu_CHI2", &Bu_CHI2);
    BTree->Branch("Bu_CHI2NDOF", &Bu_CHI2NDOF);

    BTree->Branch("ndtrs", &ndtrs);
    BTree->Branch("ndtrs_noghost", &ndtrs_noghost);
    BTree->Branch("nsplits", &nsplits);

    BTree->Branch("mum_px", &mum_px);
    BTree->Branch("mum_py", &mum_py);
    BTree->Branch("mum_pz", &mum_pz);
    BTree->Branch("mum_e", &mum_e);
    BTree->Branch("mum_IPCHI2", &mum_IPCHI2);
    BTree->Branch("mum_CHI2NDOF", &mum_CHI2NDOF);
    BTree->Branch("mum_GHOSTPROB", &mum_GHOSTPROB);

    BTree->Branch("mup_px", &mup_px);
    BTree->Branch("mup_py", &mup_py);
    BTree->Branch("mup_pz", &mup_pz);
    BTree->Branch("mup_e", &mup_e);
    BTree->Branch("mup_IPCHI2", &mup_IPCHI2);
    BTree->Branch("mup_CHI2NDOF", &mup_CHI2NDOF);
    BTree->Branch("mup_GHOSTPROB", &mup_GHOSTPROB);

    BTree->Branch("K_px", &K_px);
    BTree->Branch("K_py", &K_py);
    BTree->Branch("K_pz", &K_pz);
    BTree->Branch("K_e", &K_e);
    BTree->Branch("K_p", &K_p);
    BTree->Branch("K_eta", &K_eta);
    BTree->Branch("K_IPCHI2", &K_IPCHI2);
    BTree->Branch("K_CHI2NDOF", &K_CHI2NDOF);
    BTree->Branch("K_GHOSTPROB", &K_GHOSTPROB);

    BTree->Branch("nTracks", &nTracks);
    BTree->Branch("nSPDHits", &nSPDHits);

    BTree->Branch("Jpsi_px", &Jpsi_px);
    BTree->Branch("Jpsi_py", &Jpsi_py);
    BTree->Branch("Jpsi_pz", &Jpsi_pz);
    BTree->Branch("Jpsi_e", &Jpsi_e);
    BTree->Branch("Jpsi_FDCHI2", &Jpsi_FDCHI2);
    BTree->Branch("Jpsi_BPVDLS", &Jpsi_BPVDLS);    
    BTree->Branch("Jpsi_CHI2", &Jpsi_CHI2);
    BTree->Branch("Jpsi_CHI2NDOF", &Jpsi_CHI2NDOF);

    BTree->Branch("jpsi_ipchi2", &jpsi_ipchi2);
    BTree->Branch("k_ipchi2", &k_ipchi2);

    BTree->Branch("Bfromjet_px", &Bfromjet_px);
    BTree->Branch("Bfromjet_py", &Bfromjet_py);
    BTree->Branch("Bfromjet_pz", &Bfromjet_pz);
    BTree->Branch("Bfromjet_e", &Bfromjet_e);

//    BTree->Branch("tr_thetas", &tr_thetas);
//    BTree->Branch("tr_ktthetas", &tr_ktthetas);
//    BTree->Branch("tr_Erads", &tr_Erads);
//    BTree->Branch("tr_dRs", &tr_dRs);
//    BTree->Branch("tr_kts", &tr_kts);
//    BTree->Branch("tr_zs", &tr_zs);
//    BTree->Branch("tr_raps", &tr_raps);
//    BTree->Branch("tr_phis", &tr_phis);
//
    BTree->Branch("tr_hardest", &tr_hardest);

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

    BTree->Branch("tr_ndtrs", &tr_ndtrs);
    BTree->Branch("tr_nsplits", &tr_nsplits);
    BTree->Branch("isTrueBjet", &isTrueBjet);

    BTree->Branch("dphi", &dphi);
    BTree->Branch("nSV", &nSV);
    BTree->Branch("nSV_test", &nSV_test);
    BTree->Branch("sv_mass", &sv_mass);
    BTree->Branch("sv_chi2", &sv_chi2);
    BTree->Branch("sv_ntrks", &sv_ntrks);
    BTree->Branch("sv_cosine", &sv_cosine);
    BTree->Branch("sv_ipchi2", &sv_ipchi2);
    BTree->Branch("sv_keys", &sv_keys);
    BTree->Branch("sv_pids", &sv_pids);
    BTree->Branch("bdt_mCor", &bdt_mCor);
    BTree->Branch("bdt_0", &bdt_0);
    BTree->Branch("bdt_1", &bdt_1);
    BTree->Branch("bdt_pt", &bdt_pt);
    BTree->Branch("bdt_z", &bdt_z);

    BTree->Branch("bdt_px", &bdt_px);
    BTree->Branch("bdt_py", &bdt_py);
    BTree->Branch("bdt_pz", &bdt_pz);
    BTree->Branch("bdt_e", &bdt_e);

    BTree->Branch("SVTag", &SVTag);

    BTree->Branch("HFHardest", &HFHardest);
    BTree->Branch("bmass_dtf", &bmass_dtf);
    BTree->Branch("chi2ndf_dtf", &chi2ndf_dtf);
    BTree->Branch("tau_dtf", &tau_dtf);
    // BTree->Branch("NumSubJets", &NumSubJets);
    BTree->Branch("NumBHads_tr", &NumBHads_tr);
    BTree->Branch("Hasbbbar", &Hasbbbar);
    BTree->Branch("K_PIDK", &K_PIDK);
    BTree->Branch("pideff_K", &pideff_K);
    BTree->Branch("pideff_mum", &pideff_mum);
    BTree->Branch("pideff_mup", &pideff_mup);
    BTree->Branch("pideff_K_err", &pideff_K_err);
    BTree->Branch("pideff_mum_err", &pideff_mum_err);
    BTree->Branch("pideff_mup_err", &pideff_mup_err);

    BTree->Branch("trkeff_K", &trkeff_K);
    BTree->Branch("trkeff_mup", &trkeff_mup);
    BTree->Branch("trkeff_mum", &trkeff_mum);

    BTree->Branch("trkeff_K_errhi", &trkeff_K_errhi);
    BTree->Branch("trkeff_mup_errhi", &trkeff_mup_errhi);
    BTree->Branch("trkeff_mum_errhi", &trkeff_mum_errhi);
    BTree->Branch("trkeff_K_errlo", &trkeff_K_errlo);
    BTree->Branch("trkeff_mup_errlo", &trkeff_mup_errlo);
    BTree->Branch("trkeff_mum_errlo", &trkeff_mum_errlo);

    BTree->Branch("trigeff_Data", &trigeff_Data);
    BTree->Branch("trigeff_MC", &trigeff_MC);
    BTree->Branch("trigeff_ratio", &trigeff_ratio);

    BTree->Branch("mup_L0", &mup_L0);
    BTree->Branch("mum_L0", &mum_L0);
    BTree->Branch("jpsi_L0", &jpsi_L0);
    BTree->Branch("jpsi_Hlt1", &jpsi_Hlt1);
    BTree->Branch("jpsi_Hlt2", &jpsi_Hlt2);
    BTree->Branch("Trig", &Trig);
    BTree->Branch("TIS", &TIS);
    BTree->Branch("TOS", &TOS);

    BTree->Branch("z", &z);
    BTree->Branch("jt", &jt);
    BTree->Branch("r", &r);
    BTree->Branch("zg", &zg);
    BTree->Branch("jtg", &jtg);
    BTree->Branch("rg", &rg);
    BTree->Branch("tr_z", &tr_z);
    BTree->Branch("tr_jt", &tr_jt);
    BTree->Branch("tr_r", &tr_r);
    
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
    int N_purity_num(0), N_purity_denom(0);
    float last_HFpt = 0;
    float last_HFjet = 0;
    int ev_min = 0;
    int NumSame = 0;
    int ev_notrig(0), ev_L0(0), ev_Hlt1(0), ev_Hlt2(0);
    TRandom3 *myUniform = new TRandom3();
    TRandom3 *myRNG = new TRandom3();

    for (int ev = ev_min; ev < NumEvts + ev_min; ev++)
    {
        Tree.GetEntry(ev);
        if (ev % 10000 == 0)
            cout << "Executing event " << ev << endl;

        // TLorentzVector hfmeson(Tree.Bu_PX / 1000., Tree.Bu_PY / 1000., Tree.Bu_PZ / 1000., Tree.Bu_PE / 1000.);
        // TLorentzVector muptest(Tree.mup_PX / 1000., Tree.mup_PY / 1000., Tree.mup_PZ / 1000., Tree.mup_PE / 1000.);
        // TLorentzVector mumtest(Tree.mum_PX / 1000., Tree.mum_PY / 1000., Tree.mum_PZ / 1000., Tree.mum_PE / 1000.);
        // TLorentzVector Kmesontest(Tree.K_PX / 1000., Tree.K_PY / 1000., Tree.K_PZ / 1000., Tree.K_PE / 1000.);
        // TLorentzVector Jpsitest;
        // Jpsitest = mumtest + muptest;
        // if (Tree.totCandidates > 1)
        // {
        //     // if (fabs(muptest.Py() - Kmesontest.Py()) < 1e-3 && Tree.K_PIDK > -5 && TOS)
        //     // {
        //     cout << "-----------------------------------------------------" << endl;
        //     cout << Tree.eventNumber << endl;
        //     cout << muptest.Px() << ", " << mumtest.Px() << ", " << Kmesontest.Px() << endl;
        //     cout << muptest.Py() << ", " << mumtest.Py() << ", " << Kmesontest.Py() << endl;
        //     cout << muptest.Pz() << ", " << mumtest.Pz() << ", " << Kmesontest.Pz() << endl;
        //     cout << muptest.E() << ", " << mumtest.E() << ", " << Kmesontest.E() << endl;
        //     cout << Tree.K_PIDK << endl;
        //     cout << Jpsitest.M() << ", " << hfmeson.M() << ", " << hfmeson.Pt() << endl;
        //     cout << Tree.Bu_ConsBu_M[0] << endl;
        //     // }
        // }
        //   cout << Tree.eventNumber << ", " << hfmeson.Pt() << ", " << hfmeson.M() << ", " << (Tree.Bu_ConsBu_M[0] / 1000.) << endl;
        // cout << Tree.eventNumber << ", " << hfmeson.Px() << ", " << hfmeson.Py() << ", " << hfmeson.Pz() << ", " << hfmeson.E() << endl;

        if (ev != 0)
        {
            if (Tree.eventNumber == last_eventNum)
            {
                continue;
            }
        }
        
        // Not in Ibrahim's current code -- removing for now
        /*
        if (!isData)
        {
            if (Tree.Jet_mcjet_nmcdtrs < 2 )
            {
                continue;
            }
            
            if (Tree.Jet_mcjet_nmcdtrs == 2 )
            {
                if (Tree.Jet_mcjet_dtrID[0] == 22 || Tree.Jet_mcjet_dtrID[1] == 22)
                {
                    continue;
                }
            }
        }
        */
        if (Tree.nPVs > 1)
            continue;
        
        
        bool WrongB = false;
        // if (Tree.totCandidates > 1)
        // {
        for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
        {
            if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
            {
                if (fabs(Tree.Jet_Dtr_E[dtrs0] - Tree.Bu_PE) / (Tree.Bu_PE) > 0.001)
                    WrongB = true;
                break;
            }
        }
        if (WrongB)
            continue;
        // }

        jpsi_L0 = Tree.Jpsi_L0MuonDecision_TOS || Tree.Jpsi_L0DiMuonDecision_TOS;
        mup_L0 = Tree.mup_L0MuonDecision_TOS || Tree.mup_L0DiMuonDecision_TOS;
        mum_L0 = Tree.mum_L0MuonDecision_TOS || Tree.mum_L0DiMuonDecision_TOS;
        jpsi_Hlt1 = Tree.Jpsi_Hlt1DiMuonHighMassDecision_TOS;
        jpsi_Hlt2 = Tree.Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS;

        TIS = (Tree.Jpsi_L0Global_TIS && Tree.Jpsi_Hlt1Global_TIS && Tree.Jpsi_Hlt2Global_TIS);
        TOS = jpsi_L0 && jpsi_Hlt1 && jpsi_Hlt2;

        dtr_pt.clear();
        dtr_id.clear();
        dtr_rap.clear();
        dtr_3charge.clear();
        // if(maxjetpT_found) continue;
        // if(maxHFpT_found) continue;
        float min_dr = 999;
        int n_mindr_cand = -999;
        int n_mindr_entry = -999;

        TLorentzVector HFjet, recojet, tr_truthjet, HFmeson, mup, mum, Jpsi, Kmeson;
        TLorentzVector tr_HFjet, tr_Kmeson, tr_mum, tr_mup, tr_HFmeson;

//        vector<PseudoJet> jetdtrs, tr_jetdtrs;
        // TLorentzVector recojet, tr_HFjet, HFjet;
        mup.SetPxPyPzE(Tree.mup_PX / 1000., Tree.mup_PY / 1000., Tree.mup_PZ / 1000., Tree.mup_PE / 1000.);
        mum.SetPxPyPzE(Tree.mum_PX / 1000., Tree.mum_PY / 1000., Tree.mum_PZ / 1000., Tree.mum_PE / 1000.);
        Kmeson.SetPxPyPzE(Tree.K_PX / 1000., Tree.K_PY / 1000., Tree.K_PZ / 1000., Tree.K_PE / 1000.);
        Jpsi = mup + mum;
        HFmeson = mup + mum + Kmeson;
        // if (fabs(mup.Py() - Kmeson.Py()) < 1e-3 && Tree.K_PIDK > -5 && TOS)
        // {
        //     cout << "-----------------------------------------------------" << endl;
        //     cout << Tree.eventNumber << endl;
        //     cout << mup.Px() << ", " << mum.Px() << ", " << Kmeson.Px() << endl;
        //     cout << mup.Py() << ", " << mum.Py() << ", " << Kmeson.Py() << endl;
        //     cout << mup.Pz() << ", " << mum.Pz() << ", " << Kmeson.Pz() << endl;
        //     cout << mup.E() << ", " << mum.E() << ", " << Kmeson.E() << endl;
        //     cout << Tree.K_PIDK << endl;
        //     cout << Jpsi.M() << ", " << HFmeson.M() << ", " << Tree.Bu_ConsBu_M[0] << endl;
        // }

        // if (mup.M() == 0.493677 || mum.M() == 0.493677)
        //     cout << mup.M() << ", " << mum.M() << endl;
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
        // Jpsi = mup + mum;
        Jpsi.SetPxPyPzE(Tree.Jpsi_PX / 1000., Tree.Jpsi_PY / 1000., Tree.Jpsi_PZ / 1000., Tree.Jpsi_PE / 1000.);
        tr_HFmeson = tr_mup + tr_mum + tr_Kmeson;

        if (DoJES)
        {
            float rand = 0.976;
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

        // cout<<tr_HFmeson.M()<<",";

        bmass_dtf = Tree.Bu_ConsBu_M[0] / 1000.;
        chi2ndf_dtf = Tree.Bu_ConsBu_chi2[0] / Tree.Bu_ConsBu_nDOF[0];
        tau_dtf = Tree.Bu_ConsBu_ctau[0];


        dphi = 3.1415;

        if (Tree.totCandidates > 1)
            ManyJets++;
        else
            OneJet++;

        nSV = Tree.Jet_SVTag_Nvertices;
        nSV_test = 0;
        HFHardest = true;
        jpsi_ipchi2 = log10(Tree.Jpsi_IPCHI2_OWNPV);
        k_ipchi2 = (Tree.K_IPCHI2_OWNPV);

        // if(fabs(HFjet.Pt() - 18.8631) < 1e-4) cout<<HFjet.Eta()<<", "<<HFjet.Pt()<<endl;

        float leading_pT = 0;
        int n_maxpT_cand = -999;
        int n_maxpT_entry = -999;
        int n_HFpt_entry = -999;
        int HF_counter = 0;

        float testjet_phi, testjet_px, testjet_py, testjet_pz, testjet_e;
        int ncand = Tree.nCandidate;

        // if (Tree.totCandidates > 1 && fabs(last_HFjet - HFjet.Pt()) > 1e-1)
        // {
        //   cout << Tree.eventNumber << ", " << HFjet.Pt() << ", " << HFmeson.Pt() << ", " << HFjet.DeltaR(HFmeson, true) << endl;
        //   cout << Tree.hasb << ", " << Tree.hasbbar << endl;
        // }
        // last_HFjet = HFjet.Pt();

        // if (Tree.K_PIDK < 2)
        //   continue;

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
        //     bool hasHF = HFmeson.DeltaR(HFjet, true) < jetradius;

        //     float cand_jetpt = HFjet.Pt();
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
        // // if(HF_counter > 1){
        // //   maxHFpT_found = true;
        // //   Tree.GetEntry(n_HFpt_entry);
        // // }
        // // else Tree.GetEntry(ev);
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

        // cout<<Tree.Jet_SVTag_Tag<< ", "<< Tree.Jet_SVTag_Nvertices<<endl;
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
        // if (dphi < 2.5)
        //   continue;

        bool hasHFhadron = false;

        int NumBHads = 0;
        long customevnum = 740681719;
        // if (HFjet.Pt() > 40)
        // {
        //   cout << endl
        //        << Tree.eventNumber << endl;

        //   cout << HFjet.Pt() << ", " << HFmeson.Pt() << endl;
        // }
        // if (Tree.eventNumber == customevnum)
        // {
        //   cout << HFjet.Pt() << ", " << HFmeson.Pt() << endl;
        // }
        // cout << "Event: " << Tree.eventNumber << endl;
        // cout << "reco = " << HFmeson.Px() << ", " << HFmeson.Py() << ", " << HFmeson.Pz() << ", " << HFmeson.E() << ", " << HFmeson.Pt() << endl;
        // cout << "true = " << tr_HFmeson.Px() << ", " << tr_HFmeson.Py() << ", " << tr_HFmeson.Pz() << ", " << tr_HFmeson.E() << ", " << tr_HFmeson.Pt() << endl;

        Ndtr_neutral = 0;
        Ndtr_charged = 0;
        TLorentzVector HFmatch;
        for (int dtrs0 = 0; dtrs0 < Tree.Jet_Dtr_nrecodtr; dtrs0++)
        {

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

            if (DoTrackPt && !(abs(Tree.Jet_Dtr_ID[dtrs0]) != HF_pdgcode))
            {
                SmearDtrPt(dtr, Tree.Jet_Dtr_ThreeCharge[dtrs0], Tree.Jet_Dtr_ID[dtrs0], myRNG);
            }

//            dtrpass = DtrCuts(dtr, dtr_charge, Tree.Jet_Dtr_ProbNNghost[dtrs0], trchi2ndf, chargedJetCut);
//            if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
//                dtrpass = true;
//            if (!dtrpass)
//                continue;
            
            if (dtr.DeltaR(HFjet, true) > jetradius)
                continue;

            if (DoFSPEff && !(abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode))
            {
                float track_sys = 0.03;
                float neutral_sys = 0.04;
                bool drop = false;
                if (fabs(Tree.Jet_Dtr_ThreeCharge[dtrs0]) > 0)
                {
                    drop = DropFSP(track_sys, myUniform);
                }
                else
                {
                    drop = DropFSP(neutral_sys, myUniform);
                }
                if (drop)
                    continue;
            }

//            jetdtrs.push_back(PseudoJet(Tree.Jet_Dtr_PX[dtrs0] / 1000.,
//                                        Tree.Jet_Dtr_PY[dtrs0] / 1000.,
//                                        Tree.Jet_Dtr_PZ[dtrs0] / 1000.,
//                                        Tree.Jet_Dtr_E[dtrs0] / 1000.));
//            jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_Dtr_ID[dtrs0]));
            
            if (abs(Tree.Jet_Dtr_ID[dtrs0]) == HF_pdgcode)
            {
                // cout << "meas: " << dtr.Px() << ", " << dtr.Py() << ", " << dtr.Pz() << ", " << dtr.E() << endl;
                // cout << "match: " << Tree.Jet_Dtr_TRUE_PX[dtrs0] / 1000. << ", " << Tree.Jet_Dtr_TRUE_PY[dtrs0] / 1000. << ", " << Tree.Jet_Dtr_TRUE_PZ[dtrs0] / 1000. << ", " << Tree.Jet_Dtr_TRUE_E[dtrs0] / 1000. << endl;
                // cout << HFmeson.Px() << ", " << HFmeson.Py() << ", " << HFmeson.Pz() << ", " << HFmeson.E() << endl;
                HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
                HFmatch.SetPxPyPzE(Tree.Jet_Dtr_TRUE_PX[dtrs0] / 1000.,
                                   Tree.Jet_Dtr_TRUE_PY[dtrs0] / 1000.,
                                   Tree.Jet_Dtr_TRUE_PZ[dtrs0] / 1000.,
                                   Tree.Jet_Dtr_TRUE_E[dtrs0] / 1000.);
                // cout << "reco = " << dtr.Px() << ", " << dtr.Py() << ", " << dtr.Pz() << ", " << dtr.E() << ", " << dtr.Pt() << endl;
                // cout << "tr_reco = " << tr_dtr.Px() << ", " << tr_dtr.Py() << ", " << tr_dtr.Pz() << ", " << tr_dtr.E() << ", " << tr_dtr.Pt() << endl;

                hasHFhadron = true;
                NumBHads++;
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

        // This cut is not applied in Ibrahim's current code, it also seems dubioous
        /*
        if (NumBHads > 1)
        {
            continue;
        }
        */
        bool hasHFhadron_matched = false;
        NumBHads_tr = 0;
        bool hasb = false;
        bool hasbbar = false;

        // if(nSV > 0) cout<<"new ev"<<endl;
        // cout<<"reco "<<HFmeson.Px()<<", "<<HFmeson.Py()<<endl;
        // cout<<"true "<<tr_HFmeson.Px()<<", "<<tr_HFmeson.Py()<<endl;

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

//                dtrpass = DtrCuts(dtr, Tree.Jet_mcjet_dtrThreeCharge[dtrs0], 0, 0, chargedJetCut);
//                if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
//                    dtrpass = true;
//                if (!dtrpass)
//                    continue;
                if (dtr.DeltaR(tr_HFjet, true) > jetradius)
                    continue;

//                tr_jetdtrs.push_back(PseudoJet(Tree.Jet_mcjet_dtrPX[dtrs0] / 1000.,
//                                               Tree.Jet_mcjet_dtrPY[dtrs0] / 1000.,
//                                               Tree.Jet_mcjet_dtrPZ[dtrs0] / 1000.,
//                                               Tree.Jet_mcjet_dtrE[dtrs0] / 1000.));
//                tr_jetdtrs.back().set_user_info(new MyInfo(Tree.Jet_mcjet_dtrID[dtrs0]));

                if (abs(Tree.Jet_mcjet_dtrID[dtrs0]) == HF_pdgcode)
                {
                    // cout << "true = " << dtr.Px() << ", " << dtr.Py() << ", " << dtr.Pz() << ", " << dtr.E() << ", " << dtr.Pt() << endl;
                    NumBHads_tr++;
                    // if (fabs(dtr.Px() - HFmeson.Px()) < 2 && fabs(dtr.Py() - HFmeson.Py()) < 2)
                    // {
                    hasHFhadron_matched = true;
                    if (fabs(dtr.E() - HFmeson.E()) < ptdiff)
                    {
                        tr_HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
                        ptdiff = fabs(dtr.E() - HFmeson.E());
                    }
                    // }
                }

                // jet_Nmcdtrs++;
            }
            if (tr_HFmeson.DeltaR(tr_HFjet, true) > jetradius)
                hasHFhadron_matched = false;
            // cout<<endl<<tr_HFmeson.Pt()<<endl;
            // if (fabs(HFmeson.Pt() - tr_HFmeson.Pt()) / tr_HFmeson.Pt() > 0.03 && hasHFhadron_matched)
            // {
            //     hasHFhadron_matched = false;
            // }
            // if (fabs(HFmeson.Pt() - tr_HFmeson.Pt()) / tr_HFmeson.Pt() > 0.03)
            //   continue;
        }

        SVTag = 0;
        Hasbbbar = false;

        if (Tree.hasb && Tree.hasbbar)
        {
            Hasbbbar = true;
            if (Tree.Jet_SVTag_Tag)
            {
                SVTag = 1;
            }
        }
        // }

        if (Tree.Jet_SVTag_Tag && !(Tree.hasb && Tree.hasbbar)) // && !(Tree.tr_hasb && Tree.tr_hasbbar))
        {
            SVTag = 2;
        }

        // cout<<"Starting dijet loop";

//        thetas.clear();
//        ktthetas.clear();
//        dRs.clear();
//        Erads.clear();
//        kts.clear();
//        zs.clear();
//        raps.clear();
//        phis.clear();
//        hardest.clear();
//        tr_thetas.clear();
//        tr_ktthetas.clear();
//        tr_dRs.clear();
//        tr_Erads.clear();
//        tr_kts.clear();
//        tr_zs.clear();
//        tr_raps.clear();
//        tr_phis.clear();
//        tr_hardest.clear();

        // if(jetdtrs.size() < 2) continue;

//        ClusterSequence cs(jetdtrs, jet_def);
//        vector<PseudoJet> constit;
//        vector<LundDeclustering> declusts;
//        vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
//        PseudoJet mom = jets[0];

//        if (mom.has_constituents())
//        {
//            constit = mom.constituents();
//            int had_loc = -99;
//            for (int i = 0; i < constit.size(); i++)
//            {
//                if (abs(constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
//                {
//                    had_loc = i;
//                    break;
//                }
//            }
//            if (had_loc > -1)
//            {
//                // Decluster jet by following either hardest prong or HF prong
//                // Store info such as kt, Eradiator, theta, delta R
//                // cout<<"Reco Declust!"<<endl;
//                declusts = result(mom, constit[had_loc]);
//                for (int idecl = 0; idecl < declusts.size(); idecl++)
//                {
//                    float kt = declusts[idecl].kt();
//                    kts.push_back(kt);
//                    float dR = declusts[idecl].Delta();
//                    dRs.push_back(dR);
//                    float z = declusts[idecl].z();
//                    zs.push_back(z);
//                    float theta = declusts[idecl].theta();
//                    thetas.push_back(theta);
//                    float kttheta = declusts[idecl].kttheta();
//                    ktthetas.push_back(kttheta);
//                    float erad = declusts[idecl].erad();
//                    Erads.push_back(erad);
//                    float rap = declusts[idecl].rap();
//                    raps.push_back(rap);
//                    float phi = declusts[idecl].phi();
//                    phis.push_back(phi);
//                    bool isHard = declusts[idecl].hardest();
//                    hardest.push_back(isHard);
//                    if (!isHard)
//                        HFHardest = false;
//                }
//            }
//        }

//        vector<LundDeclustering> tr_declusts;
//        if (!isData)
//        {
//            if (tr_jetdtrs.size() > 1)
//            {
//                ClusterSequence cs_tr_(tr_jetdtrs, jet_def);
//                vector<PseudoJet> tr_constit;
//                vector<PseudoJet> tr_jets = sorted_by_pt(cs_tr_.inclusive_jets());
//                PseudoJet tr_mom = tr_jets[0];
//
//                tr_constit = tr_mom.constituents();
//                int tr_had_loc = -99;
//                for (int i = 0; i < tr_constit.size(); i++)
//                {
//                    if (abs(tr_constit.at(i).user_info<MyInfo>().pdg_id()) == HF_pdgcode)
//                    {
//                        tr_had_loc = i;
//                        break;
//                    }
//                }
//                // cout<<"Truth Declust!"<<endl;
//                if (tr_had_loc > -1)
//                    tr_declusts = result(tr_mom, tr_constit[tr_had_loc]);
//            };
//            for (int idecl = 0; idecl < tr_declusts.size(); idecl++)
//            {
//                float kt = tr_declusts[idecl].kt();
//                tr_kts.push_back(kt);
//                float dR = tr_declusts[idecl].Delta();
//                tr_dRs.push_back(dR);
//                float z = tr_declusts[idecl].z();
//                tr_zs.push_back(z);
//                float theta = tr_declusts[idecl].theta();
//                tr_thetas.push_back(theta);
//                float kttheta = tr_declusts[idecl].kttheta();
//                tr_ktthetas.push_back(kttheta);
//                float erad = tr_declusts[idecl].erad();
//                tr_Erads.push_back(erad);
//                float rap = tr_declusts[idecl].rap();
//                tr_raps.push_back(rap);
//                float phi = tr_declusts[idecl].phi();
//                tr_phis.push_back(phi);
//                bool isHard = tr_declusts[idecl].hardest();
//                tr_hardest.push_back(isHard);
//            }
//        }

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

        Bu_CHI2NDOF = Tree.Bu_ENDVERTEX_CHI2 / Tree.Bu_ENDVERTEX_NDOF;
        Bu_IPCHI2 = Tree.Bu_IPCHI2_OWNPV;
        // Bu_CHI2 = Tree.Bu_OWNPV_CHI2;
        Bu_CHI2 = Tree.Bu_ENDVERTEX_CHI2;

        mum_px = mum.Px();
        mum_py = mum.Py();
        mum_pz = mum.Pz();
        mum_e = mum.E();
        mum_CHI2NDOF = Tree.mum_TRACK_CHI2NDOF;
        mum_GHOSTPROB = Tree.mum_TRACK_GhostProb;
        mum_IPCHI2 = Tree.mum_IPCHI2_OWNPV;

        mup_px = mup.Px();
        mup_py = mup.Py();
        mup_pz = mup.Pz();
        mup_e = mup.E();
        mup_CHI2NDOF = Tree.mup_TRACK_CHI2NDOF;
        mup_GHOSTPROB = Tree.mup_TRACK_GhostProb;
        mup_IPCHI2 = Tree.mup_IPCHI2_OWNPV;

        K_px = Kmeson.Px();
        K_py = Kmeson.Py();
        K_pz = Kmeson.Pz();
        K_e = Kmeson.E();
        K_p = Kmeson.P() * 1000;
        K_eta = Kmeson.Eta();
        K_CHI2NDOF = Tree.K_TRACK_CHI2NDOF;
        K_GHOSTPROB = Tree.K_TRACK_GhostProb;
        K_IPCHI2 = Tree.K_IPCHI2_OWNPV;
        K_PIDK = Tree.K_PIDK;

        Jpsi_px = Jpsi.Px();
        Jpsi_py = Jpsi.Py();
        Jpsi_pz = Jpsi.Pz();
        Jpsi_e = Jpsi.E();
        Jpsi_CHI2NDOF = Tree.Jpsi_ENDVERTEX_CHI2 / Tree.Jpsi_ENDVERTEX_NDOF;
        Jpsi_IPCHI2 = Tree.Jpsi_IPCHI2_OWNPV;
        Jpsi_CHI2 = Tree.Jpsi_ENDVERTEX_CHI2;
        Jpsi_FDCHI2 = Tree.Jpsi_FDCHI2_OWNPV;
        Jpsi_BPVDLS = Tree.Jpsi_BPVDLS;
        
        nTracks = Tree.nTracks;
        nSPDHits = Tree.nSPDHits;
        ndtrs_noghost = Tree.Jet_Dtr_nrecodtr;
        
//        ndtrs = jetdtrs.size();
//        nsplits = kts.size();

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
//
//        tr_ndtrs = tr_jetdtrs.size();
//        tr_nsplits = tr_kts.size();

        sv_mass = Tree.Jet_SVTag_SigMaxMass / 1000.;
        sv_chi2 = log10(Tree.Jet_SVTag_SigMaxVtxChi2NDF);
        sv_ntrks = Tree.Jet_SVTag_SigMaxNtracks;
        sv_cosine = Tree.Jet_SVTag_SigMaxDirAngleS2S;
        bdt_mCor = Tree.Jet_BDTTag_mCor[0] / 1000.;
        bdt_0 = Tree.Jet_BDTTag_bdt0[0];
        bdt_1 = Tree.Jet_BDTTag_bdt1[0];
        bdt_pt = Tree.Jet_BDTTag_pt[0] / 1000.;
        bdt_z = Tree.Jet_BDTTag_z[0];

        if (isData && h2_trigeff_Data != NULL)
        {
            trigeff_Data = h2_trigeff_Data->GetBinContent(h2_trigeff_Data->GetXaxis()->FindBin(Jpsi.Pt()), h2_trigeff_Data->GetYaxis()->FindBin(Jpsi.Rapidity()));
            trigeff_MC = h2_trigeff_MC->GetBinContent(h2_trigeff_MC->GetXaxis()->FindBin(Jpsi.Pt()), h2_trigeff_MC->GetYaxis()->FindBin(Jpsi.Rapidity()));
            trigeff_ratio = trigeff_Data / trigeff_MC;
            if (std::isnan(trigeff_ratio) || std::isinf(trigeff_ratio))
                trigeff_ratio = trigeff_Data = trigeff_MC = 1.0;
        }
        else
        {
            trigeff_Data = trigeff_MC = trigeff_ratio = 1.0;
        }

        if (isData && h3_pideff_K_P_ETA_nTracks != NULL && h2_ratio_trkeff_P_ETA != NULL)
        {
            float p_K = (Kmeson.P() >= 400) ? 399 * 1e3 : Kmeson.P() * 1e3;
            float p_mum = (mum.P() >= 400) ? 399 * 1e3 : mum.P() * 1e3;
            float p_mup = (mup.P() >= 400) ? 399 * 1e3 : mup.P() * 1e3;
            p_K = (p_K <= 4000.) ? 4000.1 : p_K;
            p_mum = (p_mum <= 4000.) ? 4000.1 : p_mum;
            p_mup = (p_mup <= 4000.) ? 4000.1 : p_mup;

            float eta_K = (Kmeson.Eta() >= 4.5) ? 4.4 : Kmeson.Eta();
            float eta_mum = (mum.Eta() >= 4.5) ? 4.4 : mum.Eta();
            float eta_mup = (mup.Eta() >= 4.5) ? 4.4 : mup.Eta();
            eta_K = (eta_K <= 2.) ? 2.1 : eta_K;
            eta_mum = (eta_mum <= 2.) ? 2.1 : eta_mum;
            eta_mup = (eta_mup <= 2.) ? 2.1 : eta_mup;

            int nTracks_new = (nTracks >= 500) ? 400 : nTracks;

            pideff_K = h3_pideff_K_P_ETA_nTracks->GetBinContent(h3_pideff_K_P_ETA_nTracks->GetXaxis()->FindBin(p_K), h3_pideff_K_P_ETA_nTracks->GetYaxis()->FindBin(eta_K), h3_pideff_K_P_ETA_nTracks->GetZaxis()->FindBin(nTracks_new));
            pideff_mup = h3_pideff_Mu_P_ETA_nTracks->GetBinContent(h3_pideff_Mu_P_ETA_nTracks->GetXaxis()->FindBin(p_mup), h3_pideff_Mu_P_ETA_nTracks->GetYaxis()->FindBin(eta_mup), h3_pideff_Mu_P_ETA_nTracks->GetZaxis()->FindBin(nTracks_new));
            pideff_mum = h3_pideff_Mu_P_ETA_nTracks->GetBinContent(h3_pideff_Mu_P_ETA_nTracks->GetXaxis()->FindBin(p_mum), h3_pideff_Mu_P_ETA_nTracks->GetYaxis()->FindBin(eta_mum), h3_pideff_Mu_P_ETA_nTracks->GetZaxis()->FindBin(nTracks_new));

            pideff_K_err = h3_pideff_K_P_ETA_nTracks->GetBinError(h3_pideff_K_P_ETA_nTracks->GetXaxis()->FindBin(p_K), h3_pideff_K_P_ETA_nTracks->GetYaxis()->FindBin(eta_K), h3_pideff_K_P_ETA_nTracks->GetZaxis()->FindBin(nTracks_new));
            pideff_mup_err = h3_pideff_Mu_P_ETA_nTracks->GetBinError(h3_pideff_Mu_P_ETA_nTracks->GetXaxis()->FindBin(p_mup), h3_pideff_Mu_P_ETA_nTracks->GetYaxis()->FindBin(eta_mup), h3_pideff_Mu_P_ETA_nTracks->GetZaxis()->FindBin(nTracks_new));
            pideff_mum_err = h3_pideff_Mu_P_ETA_nTracks->GetBinError(h3_pideff_Mu_P_ETA_nTracks->GetXaxis()->FindBin(p_mum), h3_pideff_Mu_P_ETA_nTracks->GetYaxis()->FindBin(eta_mum), h3_pideff_Mu_P_ETA_nTracks->GetZaxis()->FindBin(nTracks_new));

            // cout << pideff_mum << ", " << pideff_mup << ", " << pideff_mum_err << ", " << pideff_mup_err << endl;
            // if (pideff_mum == 0)
            //     cout << p_mum << ", " << eta_mum << ", " << nTracks_new << endl;
            trkeff_K = h2_ratio_trkeff_P_ETA->GetBinContent(h2_ratio_trkeff_P_ETA->GetXaxis()->FindBin(p_K), h2_ratio_trkeff_P_ETA->GetYaxis()->FindBin(eta_K));
            trkeff_mup = h2_ratio_trkeff_P_ETA_Muon->GetBinContent(h2_ratio_trkeff_P_ETA_Muon->GetXaxis()->FindBin(p_mup), h2_ratio_trkeff_P_ETA_Muon->GetYaxis()->FindBin(eta_mup));
            trkeff_mum = h2_ratio_trkeff_P_ETA_Muon->GetBinContent(h2_ratio_trkeff_P_ETA_Muon->GetXaxis()->FindBin(p_mum), h2_ratio_trkeff_P_ETA_Muon->GetYaxis()->FindBin(eta_mum));
            // double trkeff_K_DATA = h2_ratio_trkeff_P_ETA_DATA->GetBinContent(h2_ratio_trkeff_P_ETA_DATA->GetXaxis()->FindBin(p_K), h2_ratio_trkeff_P_ETA_DATA->GetYaxis()->FindBin(eta_K));
            // double trkeff_K_MC = h2_ratio_trkeff_P_ETA_MC->GetBinContent(h2_ratio_trkeff_P_ETA_MC->GetXaxis()->FindBin(p_K), h2_ratio_trkeff_P_ETA_MC->GetYaxis()->FindBin(eta_K));
            // cout << trkeff_K << ", " << trkeff_K_DATA / trkeff_K_MC << ", " << trkeff_K_MC / trkeff_K_DATA << endl;

            trkeff_K_errhi = h2_ratio_trkeff_P_ETA_ERRHI->GetBinContent(h2_ratio_trkeff_P_ETA_ERRHI->GetXaxis()->FindBin(p_K), h2_ratio_trkeff_P_ETA_ERRHI->GetYaxis()->FindBin(eta_K));
            trkeff_mup_errhi = h2_ratio_trkeff_P_ETA_Muon_ERRHI->GetBinContent(h2_ratio_trkeff_P_ETA_Muon_ERRHI->GetXaxis()->FindBin(p_mup), h2_ratio_trkeff_P_ETA_Muon_ERRHI->GetYaxis()->FindBin(eta_mup));
            trkeff_mum_errhi = h2_ratio_trkeff_P_ETA_Muon_ERRHI->GetBinContent(h2_ratio_trkeff_P_ETA_Muon_ERRHI->GetXaxis()->FindBin(p_mum), h2_ratio_trkeff_P_ETA_Muon_ERRHI->GetYaxis()->FindBin(eta_mum));

            trkeff_K_errlo = h2_ratio_trkeff_P_ETA_ERRLO->GetBinContent(h2_ratio_trkeff_P_ETA_ERRLO->GetXaxis()->FindBin(p_K), h2_ratio_trkeff_P_ETA_ERRLO->GetYaxis()->FindBin(eta_K));
            trkeff_mup_errlo = h2_ratio_trkeff_P_ETA_Muon_ERRLO->GetBinContent(h2_ratio_trkeff_P_ETA_Muon_ERRLO->GetXaxis()->FindBin(p_mup), h2_ratio_trkeff_P_ETA_Muon_ERRLO->GetYaxis()->FindBin(eta_mup));
            trkeff_mum_errlo = h2_ratio_trkeff_P_ETA_Muon_ERRLO->GetBinContent(h2_ratio_trkeff_P_ETA_Muon_ERRLO->GetXaxis()->FindBin(p_mum), h2_ratio_trkeff_P_ETA_Muon_ERRLO->GetYaxis()->FindBin(eta_mum));

            if (Kmeson.P() > 100 && Kmeson.P() < 200 && Kmeson.Eta() < 2.5)
            {
                trkeff_K_errhi = trkeff_K_errlo = 0.04;
            }
            if (Kmeson.P() < 10 && Kmeson.Eta() > 3.6)
            {
                trkeff_K_errhi = trkeff_K_errlo = 0.06;
            }

            if (pideff_K == 0 || trkeff_K == 0 || trkeff_mup == 0 || trkeff_mum == 0)
            {
                cout << pideff_K << ", " << trkeff_K << ", " << trkeff_mup << ", " << trkeff_mum << endl;
                cout << p_K << ", " << eta_K << endl;
                cout << p_mup << ", " << eta_mup << endl;
                cout << p_mum << ", " << eta_mum << endl;
                cout << nTracks << endl;
            }
        }
        else
        {
            pideff_K = pideff_mum = pideff_mup = trkeff_K = trkeff_mup = trkeff_mum = 1.0;
        }
        
//        cout << " ------------------------------------------------ " << endl;
//         cout << "Trk Eff (K, mum, mup):" << trkeff_K << ", " << trkeff_mum << ", " << trkeff_mup << endl;
//         cout << "PID Eff (K, mum, mup):" << pideff_K << ", " << pideff_mum << ", " << pideff_mup << endl;
//         cout << "Trig Eff (K, mum, mup):" << trigeff_ratio << endl;
//          cout << " ------------------------------------------------ " << endl;


        if (hasHFhadron_matched)
            isTrueBjet = true;
        else
            isTrueBjet = false;

        if (last_eventNum == Tree.eventNumber)
            NumSame++;
        last_eventNum = Tree.eventNumber;
        eventNumber = Tree.eventNumber;

        // cout << endl;

        events++;
        BTree->Fill();
        // }
    }
    // cout << "No Trigger = " << ev_notrig << endl;
    // cout << "L0 Trigger = " << ev_L0 << endl;
    // cout << "L0 + Hlt1 Trigger = " << ev_Hlt1 << endl;
    // cout << "L0 + Hlt1 + Hlt2 Trigger = " << ev_Hlt2 << endl;
    cout << "Num TWO HF in Jet = " << NumTwoHFInJet << endl;
    cout << "Num More than 1 jet in event = " << NumTwoCand << endl;
    cout << "Num Bjets from same event = " << NumSame << endl;

    cout << "Number of saved events = " << events << endl;
    // gROOT->ProcessLine(".L $LUND/lhcbStyle.C");
    // gROOT->ProcessLine(".x $LUND/lhcbStyle.C");
    // gROOT->ProcessLine(".x lhcbStyle2D.C");
    //---- paint setup...
    //
    // int ican = -1, iframe = -1, itext = -1;
    // TCanvas *ccan[1000];
    // TH1F *frame[1000];
    // TLatex *text[1000];
    // for (int i = 0; i < 1000; i++)
    // {
    //   text[i] = new TLatex();
    //   text[i]->SetNDC(kTRUE);
    //   text[i]->SetTextSize(0.06);
    // }
    // TLatex Tl;
    // Tl.SetNDC(kTRUE);
    // Tl.SetTextSize(0.04);
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
    // gStyle->SetOptStat(0);
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
    // // c->SaveAs("plots/"+extension+".pdf");

    // // c1->SaveAs(Form("plots_misc/Misc_%s"+extension+".pdf", file_name.c_str()));
    // // cout<<"...outbase   = "<<outbase.Data()<<endl;
    // // cout<<"...rootfile  = "<<rootfile.Data()<<endl;
    // // cout<<"...plotfile  = "<<plotfile.Data()<<endl;

    // // //
    // //
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
    // SetTruthStyle(h1_trig_eff);
    // h1_trig_eff->Draw("P E SAME");
    // h1_trig_eff->SetMinimum(0.);
    // h1_trig_eff->SetMaximum(1.2);

    // ccan[ican]->cd(2);
    // for (int i = 0; i < HFetabinsize; i++)
    // {
    //   // ccan[ican]->cd(i + 1);

    //   TH1D *h1_temp = (TH1D *)h2_efficiency_Jpsiptrap->ProjectionX(Form("htempeff%d_jpsiptrap", i), i + 1, i + 1);
    //   h1_temp->SetMarkerStyle(i + 20);
    //   h1_temp->SetMarkerColor(i + 1);
    //   h1_temp->SetMarkerSize(0.6);
    //   h1_temp->SetLineColor(i + 1);
    //   h1_temp->Draw("PE1SAME");
    //   h1_temp->SetMaximum(1.05);
    //   h1_temp->SetMinimum(0.);
    //   h1_temp->SetTitle("; p_{T}^{HF} [GeV]; Efficiency");
    //   h1_temp->SetTitleOffset(1.2);
    //   h1_temp->GetXaxis()->CenterTitle(false);

    //   // legendptmass->AddEntry(h1_temp, Form("%.1f < #eta < %.1f GeV", HFeta_binedges[i], HFeta_binedges[i + 1]));
    // }

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
}

int main(int argc, char *argv[])
{

    int NumEvts = -1;
    int dataset = 91599;
    bool isData = true;
    bool chargedJetCut = false;
    bool DoJER = false;
    bool DoJES = false;
    bool DoFSPEff = false;
    bool DoTrackPt = false;
    bool DoGhostCut = false;

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
            std::cout << "  -jes <DoJES>       : JES variation (0 or 1)" << std::endl;
            std::cout << "  -trackpt <DoTrackPt>     : Whether to apply track pT cut (0 or 1)" << std::endl;
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
        else if (arg == "-trackpt")
        {
            if (i + 1 < argc)
            {
                DoTrackPt = (stoi(argv[i + 1]) != 0);
                i++;
            }
            else
            {
                std::cerr << "-trackpt option requires one argument." << std::endl;
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
                DoTrackPt,
                DoGhostCut);
    return 0;
}
//
