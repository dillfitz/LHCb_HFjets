

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

// #include "ZjetLuC"

#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <fstream>
//#include "Settings.h"
//#include "../Helpers.h"
// #include "../LundGen.hh"
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Helpers.h"
#include <TF1.h>
#include <TLatex.h>
#include <THStack.h>
#include <TChain.h>
#include <TStyle.h>
////#include "RooUnfoldResponse.h"
//#include "RooUnfoldBayes.h"
#include <TLegend.h>
#include <TEfficiency.h>
//#include "/Users/josearias18/Desktop/QCDc2/root/RooUnfold/src/RooUnfold.h"
#include "/Users/josearias18/Desktop/QCDc2/root/RooUnfold/src/RooUnfoldBayes.h"

#include "/Users/josearias18/Desktop/QCDc2/root/RooUnfold/src/RooUnfoldResponse.h"


 using namespace std;

void SimpleUnfold(int NumEvts = -1,
                  int dataset = 91599,
                  bool chargedJetCut_user = false,
                  float minimum_dR = 0.1,
                  bool DoReverse = false,
                  int DoJES = 0,
                  bool DoJER = false,
                  bool DoFSPEff = false,
                  bool DoTrackPt = false,
                  bool DoGhostCut = false,
                  bool DoRecSelEff = false,
                  bool SubtractGS = false)
{
    
    // gROOT->ProcessLine(".L ZjetLuC");
    
    // TFile *input = new TFile("/home/chahrour/DeadCone/", "read");
    
    // int flavor = -99;
    // cout<<"Current Flavor = "<<flavor<<endl;
    //  while(flavor != 0 && flavor != 4 && flavor != 5){
    //    cout<<"Please choose flavor (0: light, 4: charm, 5: beauty): ";
    //    cin>>flavor;
    //  }
    // pt_cut = true;
    // Erad_cut = Erad_cut_user;
    // kt_cut = true;
    // pt_track_cut = false;
    // bool isData = false;
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
    TString str_DTF = "";
    TString str_PID = "";
    TString str_year = "2016";
    TString str_GS = "";
    
    TString str_charged = "";
    
    if (year == 6)
        str_year = "2016";
    else if (year == 7)
        str_year = "2017";
    else if (year == 8)
        str_year = "2018";
    
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
    
    if (DTF_cut)
        str_DTF = "_DTF";
    if (PID_cut)
        str_PID = "_PID";
    
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
    
    TString extension, extension_prefix;
    extension = TString("unfold_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_GS + Form("_%d", dataset);
    // if (isData)
    //   extension += "_forData";
    
    if (DoReverse)
        extension_prefix = "reverse_";
    if (DoJES == 1)
        extension_prefix = TString("JESPos_");
    else if (DoJES == 2)
        extension_prefix = TString("JESNeg_");
    if (DoJER)
        extension_prefix = TString("JER_");
    if (DoFSPEff)
        extension_prefix = TString("fspeff_");
    if (DoTrackPt)
        extension_prefix = TString("trackpt_");
    if (DoGhostCut)
        extension_prefix = TString("ghostcut_");
    if (DoRecSelEff)
        extension_prefix = TString("recselsys_");
    // int NumEvts = 0;
    // cout <<"Choose number of events (-1: All Events, or enter integer): ";
    // cin>> NumEvts;
    
    TString extension_read, extension_eff, extension_RootFilesMC;
    
    extension_RootFilesMC = TString("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/BjetsMC/");
    
    extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
    extension_eff = TString("efficiency_truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag + str_flavor + str_GS + Form("_%d", dataset);
    
    if (!DoReverse)
        extension_read = extension_prefix + extension_read;
    extension = extension_prefix + extension;
    
    // TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
    cout << "File:" << endl;
    cout << extension_read << endl;
    
    TFile *file_eff = new TFile(extension_RootFilesMC + extension_eff + TString(".root"), "READ");
    TFile *file_decay = new TFile(extension_RootFilesMC + "HFeff_truth_ev_-1" + str_Mag + str_flavor + str_DTF + str_PID + Form("_%d.root", dataset), "READ");
//    TFile *file_decay = new TFile("HFeff_truth_ev_-1_b_PID_91599.root" , "READ");
    
    TChain *BTree = new TChain("BTree", "");
    vector<int> vec_datasets;
    if (Mag == 0)
        vec_datasets = {61590, 71590, 81590};
    else if (Mag == 1)
        vec_datasets = {61591, 71591, 81591};
    else
        vec_datasets = {61590, 61591, 71590, 71591, 81590, 81591};
    
    cout << "Loading dataset(s): " << endl;
    if (year == 9 && JetMeth != 9)
    {
        for (int i = 0; i < vec_datasets.size(); i++)
        {
            Mag = (vec_datasets[i] / 1) % 10;
            if (Mag == 0)
                str_Mag = "_MD";
            else if (Mag == 1)
                str_Mag = "_MU";
            extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", vec_datasets[i]);
            if (!DoReverse && !DoRecSelEff)
                extension_read = extension_prefix + extension_read;
            cout << extension_read << endl;
            BTree->Add(extension_RootFilesMC  + extension_read + ".root/BTree");
        }
    }
    else
    {
        extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
        if (!DoReverse && !DoRecSelEff)
            extension_read = extension_prefix + extension_read;
        cout << extension_read << endl;
        BTree->Add(extension_RootFilesMC  + extension_read + ".root/BTree");
    }
    if (NumEvts > BTree->GetEntries())
        NumEvts = BTree->GetEntries();
    if (NumEvts == -1)
        NumEvts = BTree->GetEntries();
    
    TH1D *h1_denom_efficiency_HFpt = (TH1D *)file_eff->Get("denom_efficiency_HFpt");
    
    TH1D *h1_denom_efficiency_z = (TH1D *)file_eff->Get("denom_efficiency_z");
    
    TH1D *h1_denom_efficiency_jt = (TH1D *)file_eff->Get("denom_efficiency_jt");
    
    TH1D *h1_denom_efficiency_r = (TH1D *)file_eff->Get("denom_efficiency_r");
    
    TH2D *h2_denom_efficiency_HFptjetpt = (TH2D *)file_eff->Get("denom_efficiency_HFptjetpt");
//    TH2D *h2_denom_efficiency_fragzjetpt = (TH2D *)file_eff->Get("h2_denom_efficiency_fragzjetpt");
    TH2D *h2_denom_efficiency_HFpteta = (TH2D *)file_eff->Get("denom_efficiency_HFpteta");
    TH3D *h3_denom_efficiency_HFptetajetpt = (TH3D *)file_eff->Get("denom_efficiency_HFptetajetpt");
    TH2D *h2_denom_efficiency_jetpteta = (TH2D *)file_eff->Get("denom_efficiency_jetpteta");
    TH1D *h1_denom_efficiency_jetpt = (TH1D *)file_eff->Get("denom_efficiency_jetpt");
    TH1D *h1_denom_efficiency_jetrap = (TH1D *)file_eff->Get("denom_efficiency_jetrap");
    TH2D *h2_denom_efficiency_zjt = (TH2D*)file_eff->Get("denom_efficiency_zjt");
    TH2D *h2_denom_efficiency_zr = (TH2D*)file_eff->Get("denom_efficiency_zr");
    TH2D *h2_denom_efficiency_jtr = (TH2D*)file_eff->Get("denom_efficiency_zr");
    TH2D *h2_denom_efficiency_ptz=(TH2D*)file_eff->Get("denom_efficiency_ptz");
    TH2D *h2_denom_efficiency_ptjt=(TH2D*)file_eff->Get("denom_efficiency_ptjt");
    TH2D *h2_denom_efficiency_ptr=(TH2D*)file_eff->Get("denom_efficiency_ptr");
    
    TH3D *h3_denom_efficiency_ptzjt=(TH3D*)file_eff->Get("denom_efficiency_ptzjt");
    TH3D *h3_denom_efficiency_ptzr=(TH3D*)file_eff->Get("denom_efficiency_ptzr");
    TH3D *h3_denom_efficiency_ptjtr=(TH3D*)file_eff->Get("denom_efficiency_ptjtr");
    
     TH2D *h2_SVTag_eff_denom_z = (TH2D *)file_eff->Get("h2_SVTag_eff_denom_z");
    TH2D *h2_SVTag_eff_denom = (TH2D *)file_eff->Get("h2_SVTag_eff_denom");
    
    TH1D *h1_recoHF_HFpt = (TH1D *)file_decay->Get("num_efficiency_HFpt");
    TH1D *h1_recoHF_jetpt = (TH1D *)file_decay->Get("num_efficiency_jetpt");
    TH2D *h2_recoHF_HFpteta = (TH2D *)file_decay->Get("num_efficiency_HFpteta");
    TH3D *h3_recoHF_HFptetajetpt = (TH3D *)file_decay->Get("num_efficiency_HFptetajetpt");
    
    TH1D *h1_HFeff_HFpt = (TH1D *)file_decay->Get("efficiency_HFpt");
    TH1D *h1_HFeff_jetpt = (TH1D *)file_decay->Get("efficiency_jetpt");
    TH2D *h2_HFeff_HFpteta = (TH2D *)file_decay->Get("efficiency_HFpteta");
    TH3D *h3_HFeff_HFptetajetpt = (TH3D *)file_decay->Get("efficiency_HFptetajetpt");
    
    TH2D *h2_HFptrap_ratio;
    TH3D *h3_HFptjetptrap_ratio;
    TH3D *h3_dRztheta_ratio;
    
//    /////////////////// Mass Fit Parameters /////////////////////////////////
//    TString extension_mass("massfit_data_ev_-1_ptj_12250_eta_2.54.0_ghost_0.5_b" + str_PID + "_91599.root");
//    if (DoRecSelEff)
//        extension_mass = "recselsys_" + extension_mass;
//    TFile f_massfit(extension_RootFilesMC  + extension_mass, "READ");
//    TH1D *h1_MassMin = (TH1D *)f_massfit.Get("h1_MassMin");
//    TH1D *h1_MassMax = (TH1D *)f_massfit.Get("h1_MassMax");
//    TH1D *h1_BkgScale = (TH1D *)f_massfit.Get("h1_BkgScale");
    
    // h2_HFptrap_ratio = (TH2D *)file_reco_weights.Get("h2_HFptrap_ratio");
    // h3_HFptjetptrap_ratio = (TH3D *)file_reco_weights.Get("h3_HFptjetptrap_ratio");
    // h3_dRztheta_ratio = (TH3D *)file_reco_weights.Get("h3_dRztheta_ratio");
    
    TFile *f = TFile::Open(extension_RootFilesMC + extension + ".root", "RECREATE");
    
    //Reco 1D Observables
    TH1D *h1_z = new TH1D("z", "", zbinsize, z_binedges);
    TH1D *h1_jt = new TH1D("jt", "", jtbinsize, jt_binedges);
    TH1D *h1_r = new TH1D("r", "", rbinsize, r_binedges);
    
    //Truth 1D Observables
    TH1D *h1_z_truth = new TH1D("z_truth", "", zbinsize, z_binedges);
    TH1D *h1_jt_truth = new TH1D("jt_truth", "", jtbinsize, jt_binedges);
    TH1D *h1_r_truth = new TH1D("r_truth", "", rbinsize, r_binedges);
    
    //Reco 2D Observables (208 - 217)
    TH2D *h2_zjt = new TH2D("zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_zr = new TH2D("zr", "", zbinsize, z_binedges,  rbinsize, r_binedges);
    TH2D *h2_jtr = new TH2D("jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    //Truth 2D Observables
    TH2D *h2_zjt_truth = new TH2D("zjt_truth", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_zr_truth = new TH2D("zr_truth", "", zbinsize, z_binedges,  rbinsize, r_binedges);
    TH2D *h2_jtr_truth = new TH2D("jtr_truth", "", jtbinsize, jt_binedges,  rbinsize, r_binedges);
    
    // 2D Truth-Reco Correspondence (219 - 224)
    TH2D *h2_truthreco_z = new TH2D("truthreco_z", ";Reco z; Truth z", zbinsize, z_binedges, zbinsize, z_binedges);
    TH2D *h2_truthreco_jt = new TH2D("truthreco_jt", ";Reco jT; Truth jT", jtbinsize, jt_binedges, jtbinsize, jt_binedges);
    TH2D *h2_truthreco_r = new TH2D("truthreco_r", ";Reco r; Truth r", rbinsize, r_binedges, rbinsize, r_binedges);
    ////
    TH2D *h2_truthreco_jetpt = new TH2D("truthreco_jetpt", "", longptbinsize, longpt_binedges, longptbinsize, longpt_binedges);
    //////
    
    // 1D Num Efficiencies and Purities of Observables (226 - 235)
    TH1D *h1_num_purity_z = new TH1D("num_purity_z", "", zbinsize, z_binedges);
    TH1D *h1_num_purity_jt = new TH1D("num_purity_jt", "", jtbinsize, jt_binedges );
    TH1D *h1_num_purity_r = new TH1D("num_purity_r", "", rbinsize, r_binedges);
    TH1D *h1_num_efficiency_z = new TH1D("num_efficiency_z", "", zbinsize, z_binedges);
    TH1D *h1_num_efficiency_jt = new TH1D("num_efficiency_jt", "", jtbinsize, jt_binedges );
    TH1D *h1_num_efficiency_r = new TH1D("num_efficiency_r", "", rbinsize, r_binedges);
    
    // 1D Denom Efficiencies and Purities of Observables (237 - 246)
    TH1D *h1_denom_purity_z = new TH1D("denom_purity_z", "", zbinsize, z_binedges);
    TH1D *h1_denom_purity_jt = new TH1D("denom_purity_jt", "", jtbinsize, jt_binedges );
    TH1D *h1_denom_purity_r = new TH1D("denom_purity_r", "", rbinsize, r_binedges);
//    TH1D *h1_denom_efficiency_z = new TH1D("denom_efficiency_z", "", zbinsize, z_binedges);
//    TH1D *h1_denom_efficiency_jt = new TH1D("denom_efficiency_jt", "", jtbinsize, jt_binedges );
//    TH1D *h1_denom_efficiency_r = new TH1D("denom_efficiency_r", "", rbinsize, r_binedges);
    
    TH1D *h1_num_purity_jetpt = new TH1D("num_purity_jetpt", "", ptbinsize, pt_binedges);
    TH1D *h1_denom_purity_jetpt = new TH1D("denom_purity_jetpt", "", ptbinsize, pt_binedges);
    TH1D *h1_num_purity_HFpt = new TH1D("num_purity_HFpt", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_denom_purity_HFpt = new TH1D("denom_purity_HFpt", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_num_purity_rap = new TH1D("num_purity_rap", "", etabinsize, eta_binedges);
    TH1D *h1_denom_purity_rap = new TH1D("denom_purity_rap", "", etabinsize, eta_binedges);
    
    TH1D *h1_num_efficiency_HFpt = new TH1D("num_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_num_efficiency_jetpt = new TH1D("num_efficiency_jetpt", "", ptbinsize, pt_binedges);
    TH1D *h1_num_efficiency_jetrap = new TH1D("num_efficiency_jetrap", "", ptbinsize, pt_binedges);
    TH2D *h2_num_efficiency_HFptjetpt = new TH2D("num_efficiency_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_num_purity_HFptjetpt = new TH2D("num_purity_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_denom_purity_HFptjetpt = new TH2D("denom_purity_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    
    TH2D *h2_num_purity_HFpteta = new TH2D("num_purity_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
    TH2D *h2_denom_purity_HFpteta = new TH2D("denom_purity_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
    TH2D *h2_num_efficiency_HFpteta = new TH2D("num_efficiency_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
    
    TH3D *h3_num_purity_HFptetajetpt = new TH3D("num_purity_HFptetajetpt", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges, customptbinsize, custompt_binedges);
    TH3D *h3_denom_purity_HFptetajetpt = new TH3D("denom_purity_HFptetajetpt", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges, customptbinsize, custompt_binedges);
    TH3D *h3_num_efficiency_HFptetajetpt = new TH3D("num_efficiency_HFptetajetpt", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges, customptbinsize, custompt_binedges);
    
    TH2D *h2_denom_purity_jetpteta = new TH2D("denom_purity_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    TH2D *h2_num_purity_jetpteta = new TH2D("num_purity_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    
    TH2D *h2_num_efficiency_jetpteta = new TH2D("num_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    
    //  TEfficiency *t1_efficiency_dR = new TEfficiency("t1_efficiency_dR", "", dRbinsize, dR_binedges);
    
    // TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
    // TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize_truth, pt_binedges_truth);
    // TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);
    
    TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
    TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize, pt_binedges);
    TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);
    
    TH2D *h2_jetpteta = new TH2D("jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    
    RooUnfoldResponse *response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, "response_jetpt");
    RooUnfoldResponse *response_jeteta = new RooUnfoldResponse(h1_num_purity_rap, h1_num_purity_rap, "response_jeteta");
    RooUnfoldResponse *response_HFptjetpt = new RooUnfoldResponse(h2_denom_efficiency_HFptjetpt, h2_denom_efficiency_HFptjetpt, "response_HFptjetpt");
    RooUnfoldResponse *response_jetpteta = new RooUnfoldResponse(h2_jetpteta, h2_jetpteta, "response_jetpteta");
    
    // 2D Efficiencies and Purities Observables (257 - 273)
    TH2D *h2_num_purity_zjt = new TH2D("num_purity_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_denom_purity_zjt = new TH2D("denom_purity_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    
    TH2D *h2_num_purity_zr = new TH2D("num_purity_zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
    TH2D *h2_denom_purity_zr = new TH2D("denom_purity_zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
    
    TH2D *h2_num_purity_jtr = new TH2D("num_purity_jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);
    TH2D *h2_denom_purity_jtr = new TH2D("denom_purity_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    TH2D *h2_num_efficiency_zjt = new TH2D("num_efficiency_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
//    TH2D *h2_denom_efficiency_zjt = new TH2D("denom_efficiency_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    
    TH2D *h2_num_efficiency_zr = new TH2D("num_efficiency_zr", "",  zbinsize, z_binedges, rbinsize, r_binedges);
//    TH2D *h2_denom_efficiency_zr = new TH2D("denom_efficiency_zr", "",  zbinsize, z_binedges, rbinsize, r_binedges);
    
    TH2D *h2_num_efficiency_jtr = new TH2D("num_efficiency_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
//    TH2D *h2_denom_efficiency_jtr = new TH2D("denom_efficiency_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    // 2D and 4D Observables response Matrices (286 - 292)
    RooUnfoldResponse *response_zjt = new RooUnfoldResponse( h2_zjt, h2_zjt_truth, "response_zjt" );
    RooUnfoldResponse *response_zr = new RooUnfoldResponse( h2_zr, h2_zr_truth, "respose_zr");
    RooUnfoldResponse *response_jtr = new RooUnfoldResponse( h2_jtr , h2_jtr_truth, "respose_jtr");
    RooUnfoldResponse *response_z = new RooUnfoldResponse(h1_denom_purity_z, h1_denom_efficiency_z, "response_z");
    RooUnfoldResponse *response_jt = new RooUnfoldResponse(h1_denom_purity_jt, h1_denom_efficiency_jt, "response_jt");
    RooUnfoldResponse *response_r = new RooUnfoldResponse(h1_denom_purity_r, h1_denom_efficiency_r, "response_r");
    
    
    // 3D Efficiencies/Purities of 2D Observables vs jet_pt; 6D Response Matrices (324 - 357)
    /// Q: Is Ibrahim's "matched obsv." is my "truth obsv." ?
    
    TH3D *h3_ptzjt = new TH3D("ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptzjt = new TH3D("truthptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptzjt = new TH3D("num_efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
//    TH3D *h3_denom_efficiency_ptzjt = new TH3D("denom_efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_efficiency_ptzjt = new TH3D("efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptzjt = new TH3D("num_purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptzjt = new TH3D("denom_purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptzjt = new TH3D("purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptzjt = new RooUnfoldResponse(h3_ptzjt, h3_truthptzjt, "response_ptzjt");
    
    TH3D *h3_ptzr = new TH3D("ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptzr = new TH3D("truthptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptzr = new TH3D("num_efficiency_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
//    TH3D *h3_denom_efficiency_ptzr = new TH3D("denom_efficiency_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_efficiency_ptzr = new TH3D("efficiency_ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptzr = new TH3D("num_purity_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptzr = new TH3D("denom_purity_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptzr = new TH3D("purity_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptzr = new RooUnfoldResponse(h3_ptzr, h3_truthptzr, "response_ptzr");
    
    TH3D *h3_ptjtr = new TH3D("ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptjtr = new TH3D("truthptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptjtr = new TH3D("num_efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
//    TH3D *h3_denom_efficiency_ptjtr = new TH3D("denom_efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize,  pt_binedges );
    TH3D *h3_efficiency_ptjtr = new TH3D("efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptjtr = new TH3D("num_purity_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptjtr = new TH3D("denom_purity_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptjtr = new TH3D("purity_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptjtr = new RooUnfoldResponse(h3_ptjtr, h3_truthptjtr, "response_ptjtr");
    
    // 2D Jet_pt vs Observable histograms, Purities/Efficiencies, Responses (359 - 368)
    TH2D *h2_ptz = new TH2D("ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_truthptz = new TH2D("truthptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges );
    TH2D *h2_num_efficiency_ptz = new TH2D("num_efficiency_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
//    TH2D *h2_denom_efficiency_ptz = new TH2D("denom_efficiency_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges );
    TH2D *h2_efficiency_ptz = new TH2D("efficiency_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_num_purity_ptz = new TH2D("num_purity_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges );
    TH2D *h2_denom_purity_ptz = new TH2D("denom_purity_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_purity_ptz = new TH2D("purity_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptz = new RooUnfoldResponse(h2_ptz, h2_truthptz, "response_ptz");
    
    TH2D *h2_ptjt = new TH2D("ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_truthptjt = new TH2D("truthptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH2D *h2_num_efficiency_ptjt = new TH2D("num_efficiency_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
//    TH2D *h2_denom_efficiency_ptjt = new TH2D("denom_efficiency_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_efficiency_ptjt = new TH2D("efficiency_ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_num_purity_ptjt = new TH2D("num_purity_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH2D *h2_denom_purity_ptjt = new TH2D("denom_purity_ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_purity_ptjt = new TH2D("purity_ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptjt = new RooUnfoldResponse(h2_ptjt, h2_truthptjt, "response_ptjt");
    
    TH2D *h2_ptr = new TH2D("ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_truthptr = new TH2D("truthptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH2D *h2_num_efficiency_ptr = new TH2D("num_efficiency_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
//    TH2D *h2_denom_efficiency_ptr = new TH2D("denom_efficiency_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    TH2D *h2_efficiency_ptr = new TH2D("efficiency_ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_num_purity_ptr = new TH2D("num_purity_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH2D *h2_denom_purity_ptr = new TH2D("denom_purity_ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_purity_ptr = new TH2D("purity_ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptr = new RooUnfoldResponse(h2_ptr, h2_truthptr, "response_ptr");
    
    ////SV tagging
    TH3D *h3_ptzjt_SV = new TH3D("ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptzjt_SV = new TH3D("truthptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptzjt_SV = new TH3D("num_efficiency_ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_efficiency_ptzjt_SV = new TH3D("denom_efficiency_ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_efficiency_ptzjt_SV = new TH3D("efficiency_ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptzjt_SV = new TH3D("num_purity_ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptzjt_SV = new TH3D("denom_purity_ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptzjt_SV = new TH3D("purity_ptzjt_SV", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptzjt_SV = new RooUnfoldResponse(h3_ptzjt_SV, h3_truthptzjt_SV, "response_ptzjt_SV");
    
    TH3D *h3_ptzr_SV = new TH3D("ptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptzr_SV = new TH3D("truthptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptzr_SV = new TH3D("num_efficiency_ptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_efficiency_ptzr_SV = new TH3D("denom_efficiency_ptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_efficiency_ptzr_SV = new TH3D("efficiency_ptzr_SV", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptzr_SV = new TH3D("num_purity_ptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptzr_SV = new TH3D("denom_purity_ptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptzr_SV = new TH3D("purity_ptzr_SV", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptzr_SV = new RooUnfoldResponse(h3_ptzr_SV, h3_truthptzr_SV, "response_ptzr_SV");
    
    TH3D *h3_ptjtr_SV = new TH3D("ptjtr_SV", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptjtr_SV = new TH3D("truthptjtr_SV", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptjtr_SV = new TH3D("num_efficiency_ptjtr_SV", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_efficiency_ptjtr_SV = new TH3D("denom_efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize,  pt_binedges );
    TH3D *h3_efficiency_ptjtr_SV = new TH3D("efficiency_ptjtr_SV", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptjtr_SV = new TH3D("num_purity_ptjtr_SV", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptjtr_SV = new TH3D("denom_purity_ptjtr_SV", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptjtr_SV = new TH3D("purity_ptjtr_SV", "", jtbinsize, jt_binedges, rbinsize, r_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptjtr_SV = new RooUnfoldResponse(h3_ptjtr_SV, h3_truthptjtr_SV, "response_ptjtr_SV");
    
    //// HF pt
    
    TH3D *h3_ptHFzjt = new TH3D("ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges,  ptHFbinsize, ptHF_binedges );
    TH3D *h3_truthptHFzjt = new TH3D("truthptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptHFbinsize, ptHF_binedges);
    TH3D *h3_num_efficiency_ptHFzjt = new TH3D("num_efficiency_ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges,  ptHFbinsize, ptHF_binedges);
    TH3D *h3_denom_efficiency_ptHFzjt = new TH3D("denom_efficiency_ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_efficiency_ptHFzjt = new TH3D("efficiency_ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges,  ptHFbinsize, ptHF_binedges );
    TH3D *h3_num_purity_ptHFzjt = new TH3D("num_purity_ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges,  ptHFbinsize, ptHF_binedges );
    TH3D *h3_denom_purity_ptHFzjt = new TH3D("denom_purity_ptHFzjt", "", zbinsize, z_binedges,jtbinsize, jt_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_purity_ptHFzjt = new TH3D("purity_ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptHFbinsize, ptHF_binedges );
    
    RooUnfoldResponse *response_ptHFzjt = new RooUnfoldResponse(h3_ptHFzjt, h3_truthptHFzjt, "response_ptHFzjt");
    
    TH3D *h3_ptHFzr = new TH3D("ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges,  ptHFbinsize, ptHF_binedges );
    TH3D *h3_truthptHFzr = new TH3D("truthptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges);
    TH3D *h3_num_efficiency_ptHFzr = new TH3D("num_efficiency_ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges,  ptHFbinsize, ptHF_binedges);
    TH3D *h3_denom_efficiency_ptHFzr = new TH3D("denom_efficiency_ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_efficiency_ptHFzr = new TH3D("efficiency_ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges,  ptHFbinsize, ptHF_binedges );
    TH3D *h3_num_purity_ptHFzr = new TH3D("num_purity_ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges,  ptHFbinsize, ptHF_binedges );
    TH3D *h3_denom_purity_ptHFzr = new TH3D("denom_purity_ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_purity_ptHFzr = new TH3D("purity_ptHFzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    
    RooUnfoldResponse *response_ptHFzr = new RooUnfoldResponse(h3_ptHFzr, h3_truthptHFzr, "response_ptHFzr");
    
    TH3D *h3_ptHFjtr = new TH3D("ptHFjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges);
    TH3D *h3_truthptHFjtr = new TH3D("truthptHFjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges,ptHFbinsize, ptHF_binedges );
    TH3D *h3_num_efficiency_ptHFjtr = new TH3D("num_efficiency_ptHFjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_denom_efficiency_ptHFjtr = new TH3D("denom_efficiency_ptHFjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_efficiency_ptHFjtr = new TH3D("efficiency_ptHFjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_num_purity_ptHFjtr = new TH3D("num_purity_ptHFjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_denom_purity_ptHFjtr = new TH3D("denom_purity_ptHFjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_purity_ptjtHFr = new TH3D("purity_ptHFjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    
    RooUnfoldResponse *response_ptHFjtr = new RooUnfoldResponse(h3_ptHFjtr, h3_truthptHFjtr, "response_ptHFjtr");
    
    TH2D *h2_SVTag_eff_num_z = new TH2D("h2_SVTag_eff_num_z", "", zbinsize, z_binedges, customptbinsize, custompt_binedges);
//    TH2D *h2_SVTag_eff_denom_z = new TH2D("h2_SVTag_eff_denom_z", "", zbinsize, z_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_eff_z = new TH2D("h_SVTag_eff_z", "",zbinsize, z_binedges, customptbinsize, custompt_binedges);
    
    TH2D *h2_SVTag_pur_num_z = new TH2D("h2_SVTag_pur_num_z", "", zbinsize, z_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_pur_denom_z = new TH2D("h2_SVTag_pur_denom_z", "", zbinsize, z_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_pur_z = new TH2D("h_SVTag_pur_z", "", zbinsize, z_binedges, customptbinsize, custompt_binedges);
    
    RooUnfoldResponse *response_fragz = new RooUnfoldResponse(h2_SVTag_eff_num_z, h2_SVTag_eff_num_z, "response_fragz");
    
    TH2D *h2_SVTag_eff_num = new TH2D("h2_SVTag_eff_num", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
//    TH2D *h2_SVTag_eff_denom = new TH2D("h2_SVTag_eff_denom", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_eff = new TH2D("h2_SVTag_eff", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    
    TH2D *h2_SVTag_pur_num = new TH2D("h2_SVTag_pur_num", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_pur_denom = new TH2D("h2_SVTag_pur_denom", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_pur = new TH2D("h2_SVTag_pur", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    
    TH1D *h1_z_true = new TH1D("h1_z_true", "", 20, 0, 1.05);
    TH1D *h1_z_false = new TH1D("h1_z_false", "", 20, 0, 1.05);
    TH1D *h1_z_truefalse = new TH1D("h1_z_truefalse", "", 20, 0, 1.05);
    
    TH1D *h1_r_true = new TH1D("h1_r_true", "", 20, 0, 0.5);
    TH1D *h1_r_false = new TH1D("h1_r_false", "", 20, 0, 0.5);
    
    TH1D *h1_chi2_true = new TH1D("h1_chi2_true", "", 20, -4., 4.);
    TH1D *h1_chi2_false = new TH1D("h1_chi2_false", "", 20, -4., 4.);
    
    TH2D *h2_bdt_sv_mass_truepos = new TH2D("h2_bdt_sv_mass_truepos", "", 30, 0, 15., 30, 0, 4.);
    TH2D *h2_bdt_z_truepos = new TH2D("h2_bdt_z_truepos", "", 30, 0, 15., 20, 0, 1.05);
    TH2D *h2_sv_mass_z_truepos = new TH2D("h2_sv_mass_z_truepos", "", 30, 0, 4., 20, 0, 1.05);
    TH2D *h2_sv_mass_ntrks_truepos = new TH2D("h2_sv_mass_ntrks_truepos", "", 30, 0, 4., 10, -0.5, 9.5);
    
    TH2D *h2_bdt_sv_mass_falsepos = new TH2D("h2_bdt_sv_mass_falsepos", "", 30, 0, 15., 30, 0, 4.);
    TH2D *h2_bdt_z_falsepos = new TH2D("h2_bdt_z_falsepos", "", 30, 0, 15., 20, 0, 1.05);
    TH2D *h2_sv_mass_z_falsepos = new TH2D("h2_sv_mass_z_falsepos", "", 30, 0, 4., 20, 0, 1.05);
    TH2D *h2_sv_mass_ntrks_falsepos = new TH2D("h2_sv_mass_ntrks_falsepos", "", 30, 0, 4., 10, -0.5, 9.5);
    
    //  f1_theta_Erad->SetParameter(0, mass_num);
    //  f1_kt_Erad->SetParameter(0, 2 * LambdaQCD);
    
    vector<RooUnfoldResponse*> vec_response_ptzjt;
    vector<TH3D*> vec_h3_ptzjt, vec_h3_matchedptzjt, vec_h3_num_efficiency_ptzjt, vec_h3_denom_efficiency_ptzjt, vec_h3_efficiency_ptzjt, vec_h3_num_purity_ptzjt, vec_h3_denom_purity_ptzjt, vec_h3_purity_ptzjt;
    
    vector<RooUnfoldResponse *> vec_response_ptzr;
    vector<TH3D*> vec_h3_ptzr, vec_h3_matchedptzr, vec_h3_num_efficiency_ptzr, vec_h3_denom_efficiency_ptzr, vec_h3_efficiency_ptzr, vec_h3_num_purity_ptzr, vec_h3_denom_purity_ptzr, vec_h3_purity_ptzr;
    
    vector<RooUnfoldResponse *> vec_response_ptjtr;
    vector<TH3D*> vec_h3_ptjtr, vec_h3_matchedptjtr, vec_h3_num_efficiency_ptjtr, vec_h3_denom_efficiency_ptjtr, vec_h3_efficiency_ptjtr, vec_h3_num_purity_ptjtr, vec_h3_denom_purity_ptjtr, vec_h3_purity_ptjtr;
    
    for (int i = 0; i < ptHFbinsize; i++)
    {
        int loc = i;
        // for (int j = 0; j < HFetabinsize; j++)
        // {
        TH3D *h3_ptzjt_tmp = new TH3D(Form("ptzjt%d", loc), "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_matchedptzjt_tmp = new TH3D(Form("matchedptzjt%d", loc), "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_num_efficiency_ptzjt_tmp = new TH3D(Form("num_efficiency_ptzjt%d", loc), "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_denom_efficiency_ptzjt_tmp = new TH3D(Form("denom_efficiency_ptzjt%d", loc), "",zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_efficiency_ptzjt_tmp = new TH3D(Form("efficiency_ptzjt%d", loc), "",zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_num_purity_ptzjt_tmp = new TH3D(Form("num_purity_ptzjt%d", loc), "",zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_denom_purity_ptzjt_tmp = new TH3D(Form("denom_purity_ptzjt%d", loc), "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        TH3D *h3_purity_ptzjt_tmp = new TH3D(Form("purity_ptzjt%d", loc), "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
        
        vec_h3_ptzjt.push_back(h3_ptzjt_tmp);
        vec_h3_matchedptzjt.push_back(h3_matchedptzjt_tmp);
        vec_h3_num_efficiency_ptzjt.push_back(h3_num_efficiency_ptzjt_tmp);
        vec_h3_denom_efficiency_ptzjt.push_back(h3_denom_efficiency_ptzjt_tmp);
        vec_h3_efficiency_ptzjt.push_back(h3_efficiency_ptzjt_tmp);
        vec_h3_num_purity_ptzjt.push_back(h3_num_purity_ptzjt_tmp);
        vec_h3_denom_purity_ptzjt.push_back(h3_denom_purity_ptzjt_tmp);
        vec_h3_purity_ptzjt.push_back(h3_purity_ptzjt_tmp);
        
        RooUnfoldResponse *response_ptzjt_temp = new RooUnfoldResponse(h3_ptzjt_tmp, h3_matchedptzjt_tmp, Form("response_ptzjt%d", i));
        vec_response_ptzjt.push_back(response_ptzjt_temp);
        
        
        TH3D *h3_ptzr_tmp = new TH3D(Form("ptzr%d", loc), "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_matchedptzr_tmp = new TH3D(Form("matchedptzr%d", loc), "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_num_efficiency_ptzr_tmp = new TH3D(Form("num_efficiency_ptzr%d", loc), "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_denom_efficiency_ptzr_tmp = new TH3D(Form("denom_efficiency_ptzr%d", loc), "",zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_efficiency_ptzr_tmp = new TH3D(Form("efficiency_ptzr%d", loc), "",zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_num_purity_ptzr_tmp = new TH3D(Form("num_purity_ptzr%d", loc), "",zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_denom_purity_ptzr_tmp = new TH3D(Form("denom_purity_ptzr%d", loc), "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_purity_ptzr_tmp = new TH3D(Form("purity_ptzr%d", loc), "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        
        vec_h3_ptzr.push_back(h3_ptzr_tmp);
        vec_h3_matchedptzr.push_back(h3_matchedptzr_tmp);
        vec_h3_num_efficiency_ptzr.push_back(h3_num_efficiency_ptzr_tmp);
        vec_h3_denom_efficiency_ptzr.push_back(h3_denom_efficiency_ptzr_tmp);
        vec_h3_efficiency_ptzr.push_back(h3_efficiency_ptzr_tmp);
        vec_h3_num_purity_ptzr.push_back(h3_num_purity_ptzr_tmp);
        vec_h3_denom_purity_ptzr.push_back(h3_denom_purity_ptzr_tmp);
        vec_h3_purity_ptzr.push_back(h3_purity_ptzr_tmp);
        
        RooUnfoldResponse *response_ptzr_temp = new RooUnfoldResponse(h3_ptzr_tmp, h3_matchedptzr_tmp, Form("response_ptzr%d", i));
        vec_response_ptzr.push_back(response_ptzr_temp);
        
        
        
        TH3D *h3_ptjtr_tmp = new TH3D(Form("ptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_matchedptjtr_tmp = new TH3D(Form("matchedptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_num_efficiency_ptjtr_tmp = new TH3D(Form("num_efficiency_ptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_denom_efficiency_ptjtr_tmp = new TH3D(Form("denom_efficiency_ptjtr%d", loc), "",jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_efficiency_ptjtr_tmp = new TH3D(Form("efficiency_ptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_num_purity_ptjtr_tmp = new TH3D(Form("num_purity_ptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_denom_purity_ptjtr_tmp = new TH3D(Form("denom_purity_ptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        TH3D *h3_purity_ptjtr_tmp = new TH3D(Form("purity_ptjtr%d", loc), "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
        
        vec_h3_ptjtr.push_back(h3_ptjtr_tmp);
        vec_h3_matchedptjtr.push_back(h3_matchedptjtr_tmp);
        vec_h3_num_efficiency_ptjtr.push_back(h3_num_efficiency_ptjtr_tmp);
        vec_h3_denom_efficiency_ptjtr.push_back(h3_denom_efficiency_ptjtr_tmp);
        vec_h3_efficiency_ptjtr.push_back(h3_efficiency_ptjtr_tmp);
        vec_h3_num_purity_ptjtr.push_back(h3_num_purity_ptjtr_tmp);
        vec_h3_denom_purity_ptjtr.push_back(h3_denom_purity_ptjtr_tmp);
        vec_h3_purity_ptjtr.push_back(h3_purity_ptjtr_tmp);
        
        RooUnfoldResponse *response_ptjtr_temp = new RooUnfoldResponse(h3_ptjtr_tmp, h3_matchedptjtr_tmp, Form("response_ptjtr%d", i));
        vec_response_ptjtr.push_back(response_ptjtr_temp);
        
    }
    
    //
    // Event loop
    //
    unsigned long long last_eventNum = 0;
    float last_jetpT = 0.;
    int event_counter = 0;
    
    cout << BTree->GetEntries() << endl;
    
    //  vector<float> *thetas = 0;
    //  vector<float> *tr_thetas = 0;
    //  vector<float> *dRs(0), *tr_dRs(0);
    //  vector<float> *Erads(0), *tr_Erads(0);
    //  vector<float> *ktthetas(0), *tr_ktthetas(0);
    //  vector<float> *kts = 0;
    //  vector<float> *tr_kts = 0;
    //
    //  vector<float> *raps(0), *tr_raps(0);
    //  vector<float> *phis(0), *tr_phis(0);
    
    vector<float> *zs(0), *tr_zs(0);
    vector<float> *sv_ipchi2(0);
    
    float jet_pt, HF_pt, jet_rap, tr_jet_pt, tr_jet_rap, tr_HF_pt, bmass_dtf;
    float tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
    float jet_px, jet_py, jet_pz, jet_e;
    float HF_px, HF_py, HF_pz, HF_e;
    bool isTrueBjet;
    int NumBHads_tr;
    int eventNumber, nSV;
    bool Hasbbbar, TOS;
    float Jpsi_CHI2NDOF, Jpsi_CHI2, Jpsi_FDCHI2, Jpsi_IPCHI2;
    float Bu_CHI2NDOF, Bu_CHI2, Bu_IPCHI2;
    float sv_mass, sv_chi2, sv_ntrks, sv_cosine, bdt_mCor;
    int SVTag;
    float K_PIDK, chi2ndf_dtf, tau_dtf;
    
    double z, jt, r;
    double tr_z, tr_jt, tr_r;
    double zg, jtg, rg;
    
    //  BTree->SetBranchAddress("ktthetas", &ktthetas);
    //  BTree->SetBranchAddress("tr_ktthetas", &tr_ktthetas);
    
    //  BTree->SetBranchAddress("thetas", &thetas);
    //  BTree->SetBranchAddress("Erads", &Erads);
    //  BTree->SetBranchAddress("dRs", &dRs);
    //  BTree->SetBranchAddress("kts", &kts);
    //  BTree->SetBranchAddress("zs", &zs);
    //  BTree->SetBranchAddress("raps", &raps);
    //  BTree->SetBranchAddress("phis", &phis);
    
    BTree->SetBranchAddress("HF_px", &HF_px);
    BTree->SetBranchAddress("HF_py", &HF_py);
    BTree->SetBranchAddress("HF_pz", &HF_pz);
    BTree->SetBranchAddress("HF_e", &HF_e);
    BTree->SetBranchAddress("HF_pt", &HF_pt);
    
    BTree->SetBranchAddress("Bu_IPCHI2", &Bu_IPCHI2);
    BTree->SetBranchAddress("Bu_CHI2", &Bu_CHI2);
    BTree->SetBranchAddress("Bu_CHI2NDOF", &Bu_CHI2NDOF);
    
    BTree->SetBranchAddress("Jpsi_FDCHI2", &Jpsi_FDCHI2);
    BTree->SetBranchAddress("Jpsi_CHI2", &Jpsi_CHI2);
    BTree->SetBranchAddress("Jpsi_CHI2NDOF", &Jpsi_CHI2NDOF);
    
    //  BTree->SetBranchAddress("tr_thetas", &tr_thetas);
    //  BTree->SetBranchAddress("tr_Erads", &tr_Erads);
    //  BTree->SetBranchAddress("tr_dRs", &tr_dRs);
    //  BTree->SetBranchAddress("tr_kts", &tr_kts);
    //  BTree->SetBranchAddress("tr_zs", &tr_zs);
    //  BTree->SetBranchAddress("tr_raps", &tr_raps);
    //  BTree->SetBranchAddress("tr_phis", &tr_phis);
    
    BTree->SetBranchAddress("jet_pt", &jet_pt);
    BTree->SetBranchAddress("jet_rap", &jet_rap);
    BTree->SetBranchAddress("jet_px", &jet_px);
    BTree->SetBranchAddress("jet_py", &jet_py);
    BTree->SetBranchAddress("jet_pz", &jet_pz);
    BTree->SetBranchAddress("jet_e", &jet_e);
    
    BTree->SetBranchAddress("tr_jet_px", &tr_jet_px);
    BTree->SetBranchAddress("tr_jet_py", &tr_jet_py);
    BTree->SetBranchAddress("tr_jet_pz", &tr_jet_pz);
    BTree->SetBranchAddress("tr_jet_e", &tr_jet_e);
    
    BTree->SetBranchAddress("tr_jet_pt", &tr_jet_pt);
    BTree->SetBranchAddress("tr_HF_pt", &tr_HF_pt);
    BTree->SetBranchAddress("tr_jet_rap", &tr_jet_rap);
    BTree->SetBranchAddress("isTrueBjet", &isTrueBjet);
    BTree->SetBranchAddress("NumBHads_tr", &NumBHads_tr);
    BTree->SetBranchAddress("bmass_dtf", &bmass_dtf);
    BTree->SetBranchAddress("eventNumber", &eventNumber);
    BTree->SetBranchAddress("chi2ndf_dtf", &chi2ndf_dtf);
    BTree->SetBranchAddress("tau_dtf", &tau_dtf);
    
    BTree->SetBranchAddress("Hasbbbar", &Hasbbbar);
    BTree->SetBranchAddress("nSV", &nSV);
    BTree->SetBranchAddress("sv_mass", &sv_mass);
    BTree->SetBranchAddress("sv_chi2", &sv_chi2);
    BTree->SetBranchAddress("sv_cosine", &sv_cosine);
    BTree->SetBranchAddress("sv_ipchi2", &sv_ipchi2);
    BTree->SetBranchAddress("sv_ntrks", &sv_ntrks);
    BTree->SetBranchAddress("bdt_mCor", &bdt_mCor);
    BTree->SetBranchAddress("SVTag", &SVTag);
    BTree->SetBranchAddress("K_PIDK", &K_PIDK);
    
    BTree->SetBranchAddress("z", &z);
    BTree->SetBranchAddress("jt", &jt);
    BTree->SetBranchAddress("r", &r);
    BTree->SetBranchAddress("zg", &zg);
    BTree->SetBranchAddress("jtg", &jtg);
    BTree->SetBranchAddress("rg", &rg);
    BTree->SetBranchAddress("tr_z", &tr_z);
    BTree->SetBranchAddress("tr_jt", &tr_jt);
    BTree->SetBranchAddress("tr_r", &tr_r);
    
    BTree->SetBranchAddress("TOS", &TOS);
    
    int eventNum;
    cout << "Requested # of events" << NumEvts << endl;
    
    //  std::ofstream myfile;
    //  std::ofstream SVTag_file;
    //  myfile.open(Form("data/bjet_dataset_%d.csv", dataset));
    //  SVTag_file.open(Form("data/svtag_bjet_dataset_%d.csv", dataset));
    //
    //  myfile << "jet pt"
    //         << ",";
    //  myfile << "jet eta"
    //         << ",";
    //  // myfile << HF_pt << ",";
    //  // myfile << HF_rap << ",";
    //  myfile << "logdR"
    //         << ",";
    //  myfile << "logz"
    //         << ",";
    //  myfile << "logkt"
    //         << ",";
    //  myfile << "tr_jet_pt"
    //         << ",";
    //  myfile << "tr_jet_rap"
    //         << ",";
    //  // myfile << tr_HF_pt << ",";
    //  // myfile << tr_HF_rap << ",";
    //  myfile << "tr_logdR"
    //         << ",";
    //  myfile << "tr_logz"
    //         << ",";
    //  myfile << "tr_logkt"
    //         << "\n";
    //
    //  SVTag_file << "jet pt"
    //             << ",";
    //  SVTag_file << "jet eta"
    //             << ",";
    //  // SVTag_file << HF_pt << ",";
    //  // SVTag_file << HF_rap << ",";
    //  SVTag_file << "frag_z"
    //             << ",";
    //  SVTag_file << "frag_r"
    //             << ",";
    //  SVTag_file << "sv_mass"
    //             << ",";
    //  SVTag_file << "sv_chi2"
    //             << ",";
    //  SVTag_file << "sv_ntrks"
    //             << ",";
    //  SVTag_file << "Tag"
    //             << "\n";
    
    int NumBjets = 0;
    int NumTrueBjets = 0;
    
    for (int ev = 0; ev < NumEvts; ev++)
    {
        BTree->GetEntry(ev);
        
        if (ev % 10000 == 0)
            cout << "Executing event " << ev << endl;
        
        TLorentzVector HFmeson(HF_px, HF_py, HF_pz, HF_e);
        TLorentzVector HFjet(jet_px, jet_py, jet_pz, jet_e);
        TLorentzVector tr_HFjet(tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e);
        
        float reweight = 1.0;
        float MassMu = 5.27940;
        float MassSigma = 1.32479e-02;
        // float MassHigh = MassMu + 3 * MassSigma;
        // float MassLow = MassMu - 3 * MassSigma;
        // float MassLow = 5.24;
        // float MassHigh = 5.31;
        //        float bkg_weight = h1_BkgScale != NULL ? h1_BkgScale->GetBinContent(h1_BkgScale->FindBin(HFmeson.Pt())) : 1.0;
        //        float MassHigh = h1_MassMax != NULL ? h1_MassMax->GetBinContent(h1_MassMax->FindBin(HFmeson.Pt())) : 5.31;
        //        float MassLow = h1_MassMin != NULL ? h1_MassMin->GetBinContent(h1_MassMin->FindBin(HFmeson.Pt())) : 5.24;
        
        float bkg_weight = 1.0;
        float MassHigh = 5.31;
        float MassLow =  5.24;
        
        float frag_z = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
        float frag_r = HFmeson.DeltaR(HFjet, true);
        float frag_jt = (HFjet.Vect().Cross(HFmeson.Vect()).Mag()) / (HFjet.Vect().Mag());
        
        float frag_z_trjet = HFmeson.Vect().Dot(tr_HFjet.Vect()) / (HFjet.Vect().Mag2());
        float frag_r_trjet = HFmeson.DeltaR(tr_HFjet, true);
        float frag_jt_trjet = (HFjet.Vect().Cross(HFmeson.Vect()).Mag()) / (tr_HFjet.Mag());
        
        bool mass_cond = (bmass_dtf > MassLow && bmass_dtf < MassHigh);
        bool DTF_cond = (chi2ndf_dtf < 9) && (tau_dtf > 0.3);
        bool PID_cond = (K_PIDK > 0);
        bool rap_cond = (jet_rap > etaMin && jet_rap < etaMax);
        bool pt_cond = (jet_pt > 12.5);
        bool tr_rap_cond = (tr_jet_rap > etaMin && tr_jet_rap < etaMax);
        bool tr_pt_cond = (tr_jet_pt > 12.5);
        bool SV_cond = (nSV > 0) && mass_cond && sv_mass > 0.4;
        bool gluon_cond = mass_cond && Hasbbbar;
        
        if (DoRecSelEff)
        {
            // cout << Bu_IPCHI2 << ", " << Bu_CHI2 << ", " << Jpsi_CHI2 << ", " << Jpsi_CHI2NDOF << ", " << sqrt(Jpsi_FDCHI2) << endl;
            if (Bu_IPCHI2 > 20)
                continue;
            if (Bu_CHI2 > 40)
                continue;
            if (Jpsi_CHI2 > 22)
                continue;
            if (Jpsi_CHI2NDOF > 18)
                continue;
            // if (sqrt(Jpsi_FDCHI2) > 2.8)
            //   continue;
        }
        
        if (!TOS)
            continue;
        if (!mass_cond)
            continue;
        if (DTF_cut && !DTF_cond)
            continue;
        // if (PID_cut && !PID_cond)
        //   continue;
        
        
        if (gluon_cond && isTrueBjet && tr_rap_cond && tr_pt_cond && rap_cond)
        {
            h2_SVTag_eff_denom->Fill(HFmeson.Pt(), tr_jet_pt);
            h2_SVTag_eff_denom_z->Fill(HFmeson.Pt() / tr_HFjet.Pt(), tr_HFjet.Pt());
        }
        if (SV_cond && rap_cond && isTrueBjet && tr_rap_cond && tr_pt_cond)
        {
            if (SVTag == 1)
            {
                h2_SVTag_eff_num_z->Fill(HFmeson.Pt() / tr_HFjet.Pt(), tr_HFjet.Pt());
                h2_SVTag_pur_num_z->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt());
                h2_SVTag_eff_num->Fill(HFmeson.Pt(), tr_jet_pt);
                h2_SVTag_pur_num->Fill(HFmeson.Pt(), jet_pt);
                
                // cout << HFmeson.Pt() << ", " << tr_HF_pt << endl;
                // response_fragz->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt(), tr_HF_pt / tr_HFjet.Pt(), tr_HFjet.Pt());
                // cout << HFmeson.Pt() / HFjet.Pt() << ", " << HFjet.Pt() << endl;
                // cout << tr_HF_pt / tr_HFjet.Pt() << ", " << tr_HFjet.Pt() << endl;
                h1_z_true->Fill(frag_z);
                h1_r_true->Fill(frag_r);
                h2_sv_mass_z_truepos->Fill(sv_mass, frag_z);
                h2_bdt_z_truepos->Fill(bdt_mCor, frag_z);
                h2_bdt_sv_mass_truepos->Fill(bdt_mCor, sv_mass);
                h2_sv_mass_ntrks_truepos->Fill(sv_mass, sv_ntrks);
            }
            else if (SVTag == 2)
            {
                h1_z_false->Fill(frag_z);
                h1_r_false->Fill(frag_r);
                h2_sv_mass_z_falsepos->Fill(sv_mass, frag_z);
                h2_bdt_z_falsepos->Fill(bdt_mCor, frag_z);
                h2_bdt_sv_mass_falsepos->Fill(bdt_mCor, sv_mass);
                h2_sv_mass_ntrks_falsepos->Fill(sv_mass, sv_ntrks);
            }
            if (SVTag == 1 || SVTag == 2)
            {
                h2_SVTag_pur_denom_z->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt());
                h2_SVTag_pur_denom->Fill(HFmeson.Pt(), HFjet.Pt());
                
                h1_z_truefalse->Fill(frag_z);
            }
        }
        
        //    if (SVTag > 0)
        //    {
        //      SVTag_file << jet_pt << ",";
        //      SVTag_file << jet_rap << ",";
        //      SVTag_file << frag_z << ",";
        //      SVTag_file << frag_r << ",";
        //      SVTag_file << sv_mass << ",";
        //      SVTag_file << sv_chi2 << ",";
        //      SVTag_file << sv_ntrks << ",";
        //      SVTag_file << SVTag << "\n";
        //    }
        if (SubtractGS && Hasbbbar)
            continue;
        
        // if (Hasbbbar)
        //   continue;
        
        float HF_rap = HFmeson.Rapidity();
        
        if (tr_pt_cond && isTrueBjet && pt_cond && tr_rap_cond && rap_cond)
        {
            if (eventNumber == 6176925)
                cout << jet_pt << ", " << jet_rap << ", " << tr_jet_pt << ", " << tr_jet_rap << endl;
            // if (tr_jet_pt > 40)
            //   cout << eventNumber << ",";
            
            h2_num_efficiency_HFptjetpt->Fill(HFmeson.Pt(), tr_jet_pt, reweight);
            h2_num_efficiency_HFpteta->Fill(HFmeson.Pt(), HFmeson.Rapidity(), reweight);
            h3_num_efficiency_HFptetajetpt->Fill(HFmeson.Pt(), HFmeson.Rapidity(), tr_jet_pt, reweight);
            h1_num_efficiency_jetpt->Fill(tr_jet_pt, reweight);
            h1_num_efficiency_jetrap->Fill(tr_jet_rap, reweight);
            h1_num_efficiency_HFpt->Fill(HFmeson.Pt(), reweight);
            
            h1_num_efficiency_z->Fill(frag_z_trjet, reweight);
            h1_num_efficiency_jt->Fill(frag_jt_trjet, reweight);
            h1_num_efficiency_r->Fill(frag_r_trjet, reweight);
            
            h2_num_efficiency_ptz->Fill(frag_z_trjet, tr_HFjet.Pt(), reweight);
            h2_num_efficiency_ptjt->Fill(frag_jt_trjet, tr_HFjet.Pt(), reweight);
            h2_num_efficiency_ptr->Fill(frag_r_trjet, tr_HFjet.Pt(), reweight);
            
            h2_num_efficiency_zjt->Fill(frag_z, frag_jt, reweight);
            h2_num_efficiency_zr->Fill(frag_z, frag_r, reweight);
            h2_num_efficiency_jtr->Fill(frag_jt, frag_r, reweight);
            
            h3_num_efficiency_ptzjt->Fill(frag_z_trjet, frag_jt_trjet, tr_HFjet.Pt(), reweight);
            h3_num_efficiency_ptzr->Fill(frag_z_trjet, frag_r_trjet, tr_HFjet.Pt(), reweight);
            h3_num_efficiency_ptjtr->Fill( frag_jt_trjet, frag_r_trjet, tr_HFjet.Pt(), reweight);
            
            h1_num_purity_jetpt->Fill(jet_pt, reweight);
            h1_num_purity_rap->Fill(jet_rap, reweight);
            
        }
        
        if (tr_pt_cond && isTrueBjet && pt_cond)
        {
            h2_num_efficiency_jetpteta->Fill(tr_jet_pt, tr_jet_rap, reweight);
        }
        
        if (pt_cond && rap_cond)
        {
            h1_denom_purity_jetpt->Fill(jet_pt, reweight);
            h1_denom_purity_rap->Fill(jet_rap, reweight);
            h1_denom_purity_HFpt->Fill(HF_pt);
            h2_denom_purity_HFpteta->Fill(HF_pt, HF_rap, reweight);
            h3_denom_purity_HFptetajetpt->Fill(HF_pt, HF_rap, jet_pt, reweight);
            h2_denom_purity_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, reweight);
            //      h2_denom_purity_fragzjetpt->Fill(frag_z, jet_pt, reweight);
            
            h1_denom_purity_z->Fill(frag_z, reweight);
            h1_denom_purity_jt->Fill(frag_jt, reweight);
            h1_denom_purity_r->Fill(frag_r, reweight);
            
            h2_denom_purity_zjt->Fill(frag_z, frag_jt, reweight);
            h2_denom_purity_zr->Fill(frag_z, frag_r, reweight);
            h2_denom_purity_jtr->Fill(frag_jt, frag_r, reweight);
            
            h2_denom_purity_ptz->Fill(frag_z, jet_pt, reweight);
            h2_denom_purity_ptjt->Fill(frag_jt, jet_pt, reweight);
            h2_denom_purity_ptr->Fill(frag_r, jet_pt, reweight);
            
            h3_denom_purity_ptzjt->Fill(frag_z, frag_jt, jet_pt, reweight);
            h3_denom_purity_ptzr->Fill(frag_z, frag_r, jet_pt, reweight);
            h3_denom_purity_ptjtr->Fill(frag_jt, frag_r, jet_pt, reweight);
            
            
        }
        
        if (pt_cond)
        {
            h2_denom_purity_jetpteta->Fill(jet_pt, jet_rap, reweight);
        }
        if (isTrueBjet && tr_pt_cond && pt_cond)
        {
            h2_num_purity_jetpteta->Fill(jet_pt, jet_rap, reweight);
        }
        
        if (isTrueBjet && tr_pt_cond && pt_cond && rap_cond)
        {
            h1_num_purity_HFpt->Fill(HF_pt, reweight);
            // h1_num_purity_HFeta->Fill(HF_rap);
            h2_num_purity_HFpteta->Fill(HF_pt, HF_rap, reweight);
            h3_num_purity_HFptetajetpt->Fill(HF_pt, HF_rap, jet_pt, reweight);
            NumTrueBjets++;
        }
        if (isTrueBjet && tr_pt_cond && tr_rap_cond && pt_cond && rap_cond)
        {
            h2_num_purity_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, reweight);
            //      h2_num_purity_fragzjetpt->Fill(HFmeson.Pt() / jet_pt, jet_pt, reweight);
            
            h1_num_purity_z->Fill(frag_z, reweight);
            h1_num_purity_jt->Fill(frag_jt, reweight);
            h1_num_purity_r->Fill(frag_r, reweight);
            
            h2_num_purity_zjt->Fill(frag_z, frag_jt, reweight);
            h2_num_purity_zr->Fill(frag_z, frag_r, reweight);
            h2_num_purity_jtr->Fill(frag_jt, frag_r, reweight);
            
            h2_num_purity_ptz->Fill(frag_z, jet_pt, reweight);
            h2_num_purity_ptjt->Fill(frag_jt, jet_pt, reweight);
            h2_num_purity_ptr->Fill(frag_r, jet_pt, reweight);
            
            h3_num_purity_ptzjt->Fill(frag_z, frag_jt, jet_pt, reweight);
            h3_num_purity_ptzr->Fill(frag_z, frag_r, jet_pt, reweight);
            h3_num_purity_ptjtr->Fill(frag_jt, frag_r, jet_pt, reweight);
            
            
        }
        
        if (!pt_cond || !tr_pt_cond || !isTrueBjet)
            continue;
        
        response_jetpteta->Fill(jet_pt, jet_rap, tr_jet_pt, tr_jet_rap);
        
        if (!pt_cond || !tr_pt_cond || !isTrueBjet || !rap_cond || !tr_rap_cond || !mass_cond)
            continue;
        
        response_jetpt->Fill(jet_pt, tr_jet_pt, reweight);
        response_jeteta->Fill(jet_rap, tr_jet_rap, reweight);
        response_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, HFmeson.Pt(), tr_jet_pt, reweight);
        response_fragz->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt(), tr_HF_pt / tr_HFjet.Pt(), tr_HFjet.Pt());
        
        response_z->Fill(frag_z, tr_z);
        response_jt->Fill(frag_jt, tr_jt);
        response_r->Fill(frag_r, tr_r);
        
        response_zjt->Fill(frag_z, frag_jt, tr_z, tr_jt);
        response_zr->Fill(frag_z, frag_r, tr_z, tr_r);
        response_jtr->Fill(frag_jt, frag_r, tr_jt, tr_r);
        response_ptjt->Fill( frag_jt, jet_pt, tr_jt, tr_jet_pt);
        response_ptr->Fill( frag_r,  jet_pt, tr_r, tr_jet_pt);
        response_ptz->Fill( frag_z,  jet_pt, tr_z, tr_jet_pt);
        response_ptzjt->Fill( frag_z, frag_jt, jet_pt, tr_z, tr_jt, tr_jet_pt);
        response_ptzr->Fill( frag_z, frag_r, jet_pt, tr_z, tr_r, tr_jet_pt);
        response_ptjtr->Fill( frag_jt,  frag_r, jet_pt, tr_jt, tr_r, tr_jet_pt);
        
        
        // if(jet_pt > ptMax) continue;
        h2_truthreco_jetpt->Fill(jet_pt, tr_jet_pt, reweight);
        h2_truthreco_z->Fill(frag_z, tr_z);
        h2_truthreco_jt->Fill(frag_jt, tr_jt);
        h2_truthreco_r->Fill(frag_r, tr_r);
        
        
        event_counter++;
        
        if (!truthLevel)
        {
            
            for (int i = 0; i < ptHFbinsize; i++)
            {
                if (HF_pt > ptHF_binedges[i] && HF_pt < ptHF_binedges[i + 1])
                {
                    int loc = i;
                    // for (int j = 0; j < HFetabinsize; j++)
                    // {
                    //   int loc = i * HFetabinsize + j;
                    //   if (HF_rap > HFeta_binedges[j] && HF_rap < HFeta_binedges[j + 1])
                    //   {
                    
                    vec_response_ptzjt[loc]->Fill(frag_z, frag_jt, jet_pt, tr_z, tr_jt, tr_jet_pt);
                    vec_response_ptzr[loc]->Fill(frag_z, frag_r, jet_pt, tr_z, tr_r, tr_jet_pt);
                    vec_response_ptjtr[loc]->Fill(frag_jt, frag_r, jet_pt, tr_jt, tr_r, tr_jet_pt);
                    
                    // break;
                    //   }
                    // }
                    break;
                }
            }
            
            
        }
    }
        
        //  myfile.close();
        //  SVTag_file.close();
        
        //  cout << h1_denom_purity_dR->GetEntries() << endl;
        //  cout << h1_num_purity_dR->GetEntries() << endl;
        
        h2_SVTag_eff_z->Divide(h2_SVTag_eff_num_z, h2_SVTag_eff_denom_z, 1, 1, "B");
        h2_SVTag_eff->Divide(h2_SVTag_eff_num, h2_SVTag_eff_denom, 1, 1, "B");
        
        h2_SVTag_pur_z->Divide(h2_SVTag_pur_num_z, h2_SVTag_pur_denom_z, 1, 1, "B");
        h2_SVTag_pur->Divide(h2_SVTag_pur_num, h2_SVTag_pur_denom, 1, 1, "B");
        
        // RooUnfoldResponse * response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, h2_truthreco_jetpt, "response_jetpt");
        
        TH2 *h2_response_jetpt = response_jetpt->Hresponse();
        TH2 *h2_response_z = response_z->Hresponse();
        TH2 *h2_response_jt = response_jt->Hresponse();
        TH2 *h2_response_r = response_r->Hresponse();
        
        TH2 *h2_response_zjt = response_zjt->Hresponse() ;
        TH2 *h2_response_zr = response_zr->Hresponse();
        TH2 *h2_response_jtr = response_jtr->Hresponse();
        
        TH2 *h2_response_ptjt = response_ptjt->Hresponse();
        TH2 *h2_response_ptr = response_ptr->Hresponse();
        TH2 *h2_response_ptz =  response_ptz->Hresponse();
        
        TH2 *h2_response_ptzjt = response_ptzjt->Hresponse();
        TH2 *h2_response_ptzr = response_ptzr->Hresponse();
        TH2 *h2_response_ptjtr = response_ptjtr->Hresponse();
        
        TH2 *h2_response_fragz = response_fragz->Hresponse();
        
        h2_response_jetpt->Write("h2_response_jetpt");
        
        //  response_ptktdR->Write("Roo_response_ptktdR");
        //  response_ptzdR->Write("Roo_response_ptzdR");
        //  response_ptzdR_SV->Write("Roo_response_ptzdR_SV");
        //  response_ptktdR_SV->Write("Roo_response_ptktdR_SV");
        
        
        // response_ptdRptHF->Write("Roo_response_ptdRptHF");
        response_jetpt->Write("Roo_response_jetpt");
        response_HFptjetpt->Write("Roo_response_HFptjetpt");
        response_jetpteta->Write("Roo_response_jetpteta");
        response_fragz->Write("Roo_response_fragz");
        
        response_z->Write("Roo_response_z");
        response_jt->Write("Roo_response_jt");
        response_r->Write("Roo_response_r");
        response_zjt->Write("Roo_response_zjt") ;
        response_zr->Write("Roo_response_zr" );
        response_jtr->Write( "Roo_response_jtr");
        
        response_ptjt->Write("Roo_response_ptjt" );
        response_ptr->Write( "Roo_response_ptr");
        response_ptz->Write("Roo_response_ptz" );
        
        response_ptzjt->Write("Roo_response_ptzjt" );
        response_ptzr->Write( "Roo_response_ptzr");
        response_ptjtr->Write( "Roo_response_ptjtr") ;
        
        
//          TEfficiency *h1_purity_z = new TEfficiency(*h1_num_purity_z, *h1_denom_purity_z);
        
          TH1D *h1_purity_z = (TH1D *)h1_num_purity_z->Clone("h1_purity_z");
          h1_purity_z->Divide(h1_num_purity_z, h1_denom_purity_z, 1, 1, "B");
    
    TH1D *h1_purity_jt = (TH1D *)h1_num_purity_jt->Clone("h1_purity_jt");
    h1_purity_jt->Divide(h1_num_purity_jt, h1_denom_purity_jt, 1, 1, "B");
    
    TH1D *h1_purity_r = (TH1D *)h1_num_purity_r->Clone("h1_purity_r");
    h1_purity_r->Divide(h1_num_purity_r, h1_denom_purity_r, 1, 1, "B");
    
    TH1D *h1_efficiency_z = (TH1D *)h1_num_efficiency_z->Clone("h1_efficiency_z");
    h1_efficiency_z->Divide(h1_num_efficiency_z, h1_denom_efficiency_z, 1, 1, "B");

   TH1D *h1_efficiency_jt = (TH1D *)h1_num_efficiency_jt->Clone("h1_efficiency_jt");
   h1_efficiency_jt->Divide(h1_num_efficiency_jt, h1_denom_efficiency_jt, 1, 1, "B");

   TH1D *h1_efficiency_r = (TH1D *)h1_num_efficiency_r->Clone("h1_efficiency_r");
   h1_efficiency_r->Divide(h1_num_efficiency_r, h1_denom_efficiency_r, 1, 1, "B");
    
     
        TH1D *h1_purity_HFpt = (TH1D *)h1_num_purity_HFpt->Clone("h1_purity_HFpt");
        h1_purity_HFpt->Divide(h1_num_purity_HFpt, h1_denom_purity_HFpt, 1, 1, "B");
        
        TH1D *h1_purity_jetpt = (TH1D *)h1_num_purity_jetpt->Clone("h1_purity_jetpt");
        h1_purity_jetpt->Divide(h1_num_purity_jetpt, h1_denom_purity_jetpt, 1, 1, "B");
        
        TH2D *h2_purity_HFpteta = (TH2D *)h2_num_purity_HFpteta->Clone("h2_purity_HFpteta");
        h2_purity_HFpteta->Divide(h2_num_purity_HFpteta, h2_denom_purity_HFpteta, 1, 1, "B");
        
        TH3D *h3_purity_HFptetajetpt = (TH3D *)h3_num_purity_HFptetajetpt->Clone("h3_purity_HFptetajetpt");
        h3_purity_HFptetajetpt->Divide(h3_num_purity_HFptetajetpt, h3_denom_purity_HFptetajetpt, 1, 1, "B");
        
        TH1D *h1_efficiency_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("h1_efficiency_HFpt");
        h1_efficiency_HFpt->Divide(h1_num_efficiency_HFpt, h1_denom_efficiency_HFpt, 1, 1, "B");
        
        TH1D *h1_efficiency_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("h1_efficiency_jetpt");
        h1_efficiency_jetpt->Divide(h1_num_efficiency_jetpt, h1_denom_efficiency_jetpt, 1, 1, "B");
        
        TH2D *h2_efficiency_HFptjetpt = (TH2D *)h2_num_efficiency_HFptjetpt->Clone("h2_efficiency_HFptjetpt");
        h2_efficiency_HFptjetpt->Divide(h2_num_efficiency_HFptjetpt, h2_denom_efficiency_HFptjetpt, 1, 1, "B");
        
        TH2D *h2_purity_HFptjetpt = (TH2D *)h2_num_purity_HFptjetpt->Clone("h2_purity_HFptjetpt");
        h2_purity_HFptjetpt->Divide(h2_num_purity_HFptjetpt, h2_denom_purity_HFptjetpt, 1, 1, "B");
    
    
//    h2_num_efficiency_ptz->Fill(frag_z_trjet, tr_HFjet.Pt(), reweight);
//    h2_num_efficiency_ptjt->Fill(frag_jt_trjet, tr_HFjet.Pt(), reweight);
//    h2_num_efficiency_ptr->Fill(frag_r_trjet, tr_HFjet.Pt(), reweight);
//    
//    h2_num_efficiency_zjt->Fill(frag_z, frag_jt, reweight);
//    h2_num_efficiency_zr->Fill(frag_z, frag_r, reweight);
//    h2_num_efficiency_jtr->Fill(frag_jt, frag_r, reweight);
//    
//    h3_num_efficiency_ptzjt->Fill(frag_z_trjet, frag_jt_trjet, tr_HFjet.Pt(), reweight);
//    h3_num_efficiency_ptzr->Fill(frag_z_trjet, frag_r_trjet, tr_HFjet.Pt(), reweight);
//    h3_num_efficiency_ptjtr->Fill( frag_jt_trjet, frag_r_trjet, tr_HFjet.Pt(), reweight);
//    
//    h1_num_purity_jetpt->Fill(jet_pt, reweight);
//    h1_num_purity_rap->Fill(jet_rap, reweight);
    
    h1_efficiency_z->Divide(h1_num_efficiency_z, h1_denom_efficiency_z, 1, 1, "B");
     
     h1_efficiency_jt->Divide(h1_num_efficiency_jt, h1_denom_efficiency_jt, 1, 1, "B");
     
    h1_efficiency_r->Divide(h1_num_efficiency_r, h1_denom_efficiency_r, 1, 1, "B");
                               
    
   h2_efficiency_ptz->Divide(h2_num_efficiency_ptz, h2_denom_efficiency_ptz, 1, 1, "B");
    
    h2_efficiency_ptjt->Divide(h2_num_efficiency_ptjt, h2_denom_efficiency_ptjt, 1, 1, "B");
    
    h2_efficiency_ptr->Divide(h2_num_efficiency_ptr, h2_denom_efficiency_ptr, 1, 1, "B");
    
    h2_purity_ptz->Divide(h2_num_purity_ptz, h2_denom_purity_ptz, 1, 1, "B");
     
     h2_purity_ptjt->Divide(h2_num_purity_ptjt, h2_denom_purity_ptjt, 1, 1, "B");
     
     h2_purity_ptr->Divide(h2_num_purity_ptr, h2_denom_purity_ptr, 1, 1, "B");
    
 
    TH2D *h2_efficiency_HFpteta = (TH2D *)h2_num_efficiency_HFpteta->Clone("h2_efficiency_HFpteta");
    h2_efficiency_HFpteta->Divide(h2_num_efficiency_HFpteta, h2_denom_efficiency_HFpteta, 1, 1, "B");
        
    TH3D *h3_efficiency_HFptetajetpt = (TH3D *)h3_num_efficiency_HFptetajetpt->Clone("h3_efficiency_HFptetajetpt");
          h3_efficiency_HFptetajetpt->Divide(h3_num_efficiency_HFptetajetpt, h3_denom_efficiency_HFptetajetpt, 1, 1, "B");
        
    TH2D *h2_efficiency_jetpteta = (TH2D *)h2_num_efficiency_jetpteta->Clone("h2_efficiency_jetpteta");
    h2_efficiency_jetpteta->Divide(h2_num_efficiency_jetpteta, h2_denom_efficiency_jetpteta, 1, 1, "B");
        
    TH2D *h2_purity_jetpteta = (TH2D *)h2_num_purity_jetpteta->Clone("h2_purity_jetpteta");
   h2_purity_jetpteta->Divide(h2_num_purity_jetpteta, h2_denom_purity_jetpteta, 1, 1, "B");
    

   TH1D *h1_efficiency_recoJet_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("efficiency_recoJet_HFpt");
          h1_efficiency_recoJet_HFpt->Divide(h1_efficiency_recoJet_HFpt, h1_recoHF_HFpt, 1, 1, "B");
        
   TH2D *h2_efficiency_recoJet_HFpteta = (TH2D *)h2_num_efficiency_HFpteta->Clone("efficiency_recoJet_HFpteta");
   h2_efficiency_recoJet_HFpteta->Divide(h2_efficiency_recoJet_HFpteta, h2_recoHF_HFpteta, 1, 1, "B");
        
   TH3D *h3_efficiency_recoJet_HFptetajetpt = (TH3D *)h3_num_efficiency_HFptetajetpt->Clone("efficiency_recoJet_HFptetajetpt");
    h3_efficiency_recoJet_HFptetajetpt->Divide(h3_efficiency_recoJet_HFptetajetpt, h3_recoHF_HFptetajetpt, 1, 1, "B");
        
    TH1D *h1_efficiency_recoJet_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("efficiency_recoJet_jetpt");
    h1_efficiency_recoJet_jetpt->Divide(h1_efficiency_recoJet_jetpt, h1_recoHF_jetpt, 1, 1, "B");
        
        //  // TEfficiency * h1_purity_jetpt = new TEfficiency(*h1_num_purity_jetpt, *h1_denom_purity_jetpt);
          TEfficiency *h1_purity_rap = new TEfficiency(*h1_num_purity_rap, *h1_denom_purity_rap);
        //  TEfficiency *h2_purity_ktdR = new TEfficiency(*h2_num_purity_ktdR, *h2_denom_purity_ktdR);
        //  TEfficiency *h2_purity_zdR = new TEfficiency(*h2_num_purity_zdR, *h2_denom_purity_zdR);
        //  TEfficiency *h2_purity_thetaErad = new TEfficiency(*h2_num_purity_thetaErad, *h2_denom_purity_thetaErad);
        //  TEfficiency *h2_efficiency_ktdR = new TEfficiency(*h2_num_efficiency_ktdR, *h2_denom_efficiency_ktdR);
        //  TEfficiency *h2_efficiency_zdR = new TEfficiency(*h2_num_efficiency_zdR, *h2_denom_efficiency_zdR);
        //  TEfficiency *h2_efficiency_thetaErad = new TEfficiency(*h2_num_efficiency_thetaErad, *h2_denom_efficiency_thetaErad);
        //
    
      h3_efficiency_ptzjt->Divide(h3_num_efficiency_ptzjt, h3_denom_efficiency_ptzjt, 1, 1, "B");
      h3_purity_ptzjt->Divide(h3_num_purity_ptzjt, h3_denom_purity_ptzjt, 1, 1, "B");
    
      h3_efficiency_ptzr->Divide(h3_num_efficiency_ptzr, h3_denom_efficiency_ptzr, 1, 1, "B");
      h3_purity_ptzr->Divide(h3_num_purity_ptzr, h3_denom_purity_ptzr, 1, 1, "B");
    
      h3_efficiency_ptjtr->Divide(h3_num_efficiency_ptjtr, h3_denom_efficiency_ptjtr, 1, 1, "B");
      h3_purity_ptjtr->Divide(h3_num_purity_ptjtr, h3_denom_purity_ptjtr, 1, 1, "B");
        
 
        
          h3_efficiency_ptzjt_SV->Divide(h3_num_efficiency_ptzjt_SV, h3_denom_efficiency_ptzjt_SV, 1, 1, "B");
          h3_purity_ptzr_SV->Divide(h3_num_purity_ptzr_SV, h3_denom_purity_ptzr_SV, 1, 1, "B");
    
    h3_efficiency_ptjtr_SV->Divide(h3_num_efficiency_ptjtr_SV, h3_denom_efficiency_ptjtr_SV, 1, 1, "B");

        //
        //  h3_efficiency_ptktdR_SV->Divide(h3_num_efficiency_ptktdR_SV, h3_denom_efficiency_ptktdR_SV, 1, 1, "B");
        //  h3_purity_ptktdR_SV->Divide(h3_num_purity_ptktdR_SV, h3_denom_purity_ptktdR_SV, 1, 1, "B");
        //
        //  h3_efficiency_ptthetaErad->Divide(h3_num_efficiency_ptthetaErad, h3_denom_efficiency_ptthetaErad, 1, 1, "B");
        //  h3_purity_ptthetaErad->Divide(h3_num_purity_ptthetaErad, h3_denom_purity_ptthetaErad, 1, 1, "B");
        //
        //  h3_efficiency_ptdRErad->Divide(h3_num_efficiency_ptdRErad, h3_denom_efficiency_ptdRErad, 1, 1, "B");
        //  h3_purity_ptdRErad->Divide(h3_num_purity_ptdRErad, h3_denom_purity_ptdRErad, 1, 1, "B");
        //
        //  // h3_efficiency_ptdRptHF->Divide(h3_num_efficiency_ptdRptHF, h3_denom_efficiency_ptdRptHF, 1, 1, "B");
        //  // h3_purity_ptdRptHF->Divide(h3_num_purity_ptdRptHF, h3_denom_purity_ptdRptHF, 1, 1, "B");
        //
        //  h3_efficiency_ptHFktdR->Divide(h3_num_efficiency_ptHFktdR, h3_denom_efficiency_ptHFktdR, 1, 1, "B");
        //  h3_purity_ptHFktdR->Divide(h3_num_purity_ptHFktdR, h3_denom_purity_ptHFktdR, 1, 1, "B");
        //
        //  h3_efficiency_ptHFzdR->Divide(h3_num_efficiency_ptHFzdR, h3_denom_efficiency_ptHFzdR, 1, 1, "B");
        //  h3_purity_ptHFzdR->Divide(h3_num_purity_ptHFzdR, h3_denom_purity_ptHFzdR, 1, 1, "B");
        //
        //  h2_efficiency_ptkt->Divide(h2_num_efficiency_ptkt, h2_denom_efficiency_ptkt, 1, 1, "B");
        //  h2_purity_ptkt->Divide(h2_num_purity_ptkt, h2_denom_purity_ptkt, 1, 1, "B");
        //
          for (int i = 0; i < ptHFbinsize; i++)
          {
            int loc = i;
        
            // for (int j = 0; j < HFetabinsize; j++)
            // {
            // int loc = i * HFetabinsize + j;
            vec_h3_efficiency_ptzjt[loc]->Divide(vec_h3_num_efficiency_ptzjt[loc], vec_h3_denom_efficiency_ptzjt[loc], 1, 1, "B");
            vec_h3_purity_ptzjt[loc]->Divide(vec_h3_num_purity_ptzjt[loc], vec_h3_denom_purity_ptzjt[loc], 1, 1, "B");
              
            vec_h3_efficiency_ptzr[loc]->Divide(vec_h3_num_efficiency_ptzr[loc], vec_h3_denom_efficiency_ptzr[loc], 1, 1, "B");
            vec_h3_purity_ptzr[loc]->Divide(vec_h3_num_purity_ptzr[loc], vec_h3_denom_purity_ptzr[loc], 1, 1, "B");
              
            vec_h3_efficiency_ptjtr[loc]->Divide(vec_h3_num_efficiency_ptjtr[loc], vec_h3_denom_efficiency_ptjtr[loc], 1, 1, "B");
            vec_h3_purity_ptjtr[loc]->Divide(vec_h3_num_purity_ptjtr[loc], vec_h3_denom_purity_ptjtr[loc], 1, 1, "B");
            
              
            vec_h3_efficiency_ptzjt[loc]->Write(Form("h3_efficiency_ptzjt%d", loc));
            vec_h3_purity_ptzjt[loc]->Write(Form("h3_purity_ptzjt%d", loc));
            vec_response_ptzjt[loc]->Write(Form("h3_response_ptzjt%d", loc));
              
              vec_h3_efficiency_ptzr[loc]->Write(Form("h3_efficiency_ptzr%d", loc));
              vec_h3_purity_ptzr[loc]->Write(Form("h3_purity_ptzr%d", loc));
              vec_response_ptzr[loc]->Write(Form("h3_response_ptzr%d", loc));
              
              
              vec_h3_efficiency_ptjtr[loc]->Write(Form("h3_efficiency_ptjtr%d", loc));
              vec_h3_purity_ptjtr[loc]->Write(Form("h3_purity_ptjtr%d", loc));
              vec_response_ptjtr[loc]->Write(Form("h3_response_ptjtr%d", loc));

            // }
          }
    
        //
        //  TH1D *h1_factor_HFpt = (TH1D *)h1_purity_HFpt->Clone("factor_HFpt");
        //  h1_factor_HFpt->Divide(h1_efficiency_HFpt);
        //
           f->WriteObject(&vec_h3_efficiency_ptzjt, "vec_h3_efficiency_ptzjt");
           f->WriteObject(&vec_h3_purity_ptzr, "vec_h3_purity_ptzr");
           f->WriteObject(&vec_response_ptjtr, "vec_response_ptjtr");
        
//      h2_purity_zjt->Write("purity_zjt");
//      h2_purity_zr->Write("purity_zr");
//      h2_purity_jtr->Write("purity_jtr");
    
      h1_purity_z->Write("purity_z");
      h1_purity_jt->Write("purity_jt");
      h1_purity_r->Write("purity_r");

      h1_purity_jetpt->Write("purity_jetpt");
      h1_purity_HFpt->Write("purity_HFpt");
      h1_efficiency_HFpt->Write("efficiency_HFpt");
      h2_efficiency_HFptjetpt->Write("efficiency_HFptjetpt");
    
      h2_efficiency_ptz->Write("efficiency_ptz");
      h2_efficiency_ptjt->Write("efficiency_ptjt");
      h2_efficiency_ptr->Write("efficiency_ptr");
    
     h2_purity_ptz->Write("purity_ptz");
     h2_purity_ptjt->Write("purity_ptjt");
     h2_purity_ptr->Write("purity_ptr");
    
          h2_efficiency_HFpteta->Write("efficiency_HFpteta");
          h3_efficiency_HFptetajetpt->Write("efficiency_HFptetajetpt");
          h3_purity_HFptetajetpt->Write("purity_HFptetajetpt");
          h2_purity_HFptjetpt->Write("purity_HFptjetpt");

    
          h2_efficiency_jetpteta->Write("efficiency_jetpteta");
          h2_purity_jetpteta->Write("purity_jetpteta");
          h1_efficiency_jetpt->Write("efficiency_jetpt");
          h1_purity_rap->Write("purity_jeteta");
          h1_efficiency_recoJet_HFpt->Write("efficiency_recoJet_HFpt");
          h2_efficiency_recoJet_HFpteta->Write("efficiency_recoJet_HFpteta");
          h1_efficiency_recoJet_jetpt->Write("efficiency_recoJet_jetpt");
    
        //
        //  h2_purity_HFpteta->Write("purity_HFpteta");
        //
        //  h2_efficiency_ktdR->Write("efficiency_ktdR");
        //  h2_efficiency_zdR->Write("efficiency_zdR");
        //  h2_efficiency_thetaErad->Write("efficiency_thetaErad");
        //  h1_efficiency_dR->Write("efficiency_dR");
        //  h1_efficiency_z->Write("efficiency_z");
        //  h1_efficiency_theta->Write("efficiency_theta");
        //  h1_efficiency_kT->Write("efficiency_kt");
        //  h1_efficiency_Erad->Write("efficiency_Erad");
        //
        //  h2_purity_ptkt->Write("purity_ptkt");
        //  h2_efficiency_ptkt->Write("efficiency_ptkt");
        //
        //  h3_purity_ptktdR->Write("purity_ptktdR");
        //  h3_efficiency_ptktdR->Write("efficiency_ptktdR");
        //
        //  h3_purity_rapktdR->Write("purity_rapktdR");
        //  h3_efficiency_rapktdR->Write("efficiency_rapktdR");
        //
        //  h3_purity_ptzdR->Write("purity_ptzdR");
        //  h3_efficiency_ptzdR->Write("efficiency_ptzdR");
        //
          h3_purity_ptzjt_SV->Write("purity_ptzjt_SV");
          h3_efficiency_ptzjt_SV->Write("efficiency_ptzjt_SV");
        
          h3_purity_ptzr_SV->Write("purity_ptzr_SV");
          h3_efficiency_ptzr_SV->Write("efficiency_ptzr_SV");
    
    h3_purity_ptjtr_SV->Write("purity_ptjtr_SV");
    h3_efficiency_ptjtr_SV->Write("efficiency_ptjtr_SV");
        //
        //  h3_purity_ptthetaErad->Write("purity_ptthetaErad");
        //  h3_efficiency_ptthetaErad->Write("efficiency_ptthetaErad");
        //
        //  h3_purity_ptdRErad->Write("purity_ptdRErad");
        //  h3_efficiency_ptdRErad->Write("efficiency_ptdRErad");
        //
        //  // h3_purity_ptdRptHF->Write("purity_ptdRptHF");
        //  // h3_efficiency_ptdRptHF->Write("efficiency_ptdRptHF");
        //
        //  h3_purity_ptHFktdR->Write("purity_ptHFktdR");
        //  h3_efficiency_ptHFktdR->Write("efficiency_ptHFktdR");
        //
        //  h3_purity_ptHFzdR->Write("purity_ptHFzdR");
        //  h3_efficiency_ptHFzdR->Write("efficiency_ptHFzdR");
        //
          h2_SVTag_eff->Write("h2_SVTag_eff");
          h2_SVTag_eff_z->Write("h2_SVTag_eff_z");
        
          h2_SVTag_pur->Write("h2_SVTag_pur");
          h2_SVTag_pur_z->Write("h2_SVTag_pur_z");
        //
        //  /////////////////////////////////
        
          TF1 *f_eff1 = new TF1("f_eff1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
          TF1 *f_eff2 = new TF1("f_eff2", "[0]*tanh([1]*([3] - x))+[2]", 25, 100);
          f_eff1->SetParameters(0.2, 0.1, 0.2, 6.4);
          f_eff2->SetParameters(0.2, 0.1, 0.2, 100);
          f_eff2->SetParLimits(3, 80, 200);
//          h1_efficiency_HFpt->Fit("f_eff1", "E", "SAME", 2, 25);
//          h1_efficiency_HFpt->Fit("f_eff2", "E", "SAME", 25, 100);
//        
//          f_eff1->Write("f_eff1");
//          f_eff2->Write("f_eff2");
//        
//          TF1 *f_pur1 = new TF1("f_pur1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
//          f_pur1->SetParameters(0.05, 0.4, 0.95, 16);
//          f_pur1->SetParLimits(0, 0.01, 0.1);
//          f_pur1->SetParLimits(2, 0.9, 0.99);
//        
//          h1_purity_HFpt->Fit("f_pur1", "E", "SAME", 2, 100);
//          f_pur1->Write("f_pur");
        
        cout << event_counter << " events processed" << endl;
        
        /////////////////////////////////////////////////////
        TH1D *h1_jetpt_true = (TH1D *)h1_denom_efficiency_jetpt->Clone("h1_jetpt_true");
        TH1D *h1_jetpt_reco = (TH1D *)h1_denom_purity_jetpt->Clone("h1_jetpt_reco");
        h1_jetpt_reco->Multiply(h1_purity_jetpt);
        RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_reco, 4);
        h1_jetpt_reco = (TH1D *)unfold_jetpt.Hreco();
        h1_jetpt_reco->Divide(h1_efficiency_jetpt);
        // TH1D * h1_jetpt_corr = (TH1D *)h1_jetpt_reco->Clone("h1_jetpt_corr");
        // h1_jetpt_corr->Divide(h1_jetpt_true);
        // h1_jetpt_corr->Write("h1_jetpt_corr");
        
        TH2D *h2_HFptjetpt_true = (TH2D *)h2_denom_efficiency_HFptjetpt->Clone("h2_HFptjetpt_true");
        TH2D *h2_HFptjetpt_reco = (TH2D *)h2_denom_purity_HFptjetpt->Clone("h2_HFptjetpt_reco");
        h2_HFptjetpt_reco->Multiply(h2_purity_HFptjetpt);
        RooUnfoldBayes unfold_HFptjetpt(response_HFptjetpt, h2_HFptjetpt_reco, 4);
        h2_HFptjetpt_reco = (TH2D *)unfold_HFptjetpt.Hreco();
        h2_HFptjetpt_reco->Divide(h2_efficiency_HFptjetpt);
        TH2D *h2_HFptjetpt_corr = (TH2D *)h2_HFptjetpt_reco->Clone("h2_HFptjetpt_corr");
        h2_HFptjetpt_corr->Divide(h2_HFptjetpt_true);
        h2_HFptjetpt_corr->Write("h2_HFptjetpt_corr");
        ////////////////////////////////////////////////////
        
        // gROOT->ProcessLine(".L $LUND/lhcbStyle.C");
        // gROOT->ProcessLine(".x $LUND/lhcbStyle.C");
        // gROOT->ProcessLine(".x lhcbStyle2D.C");
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
        Int_t lhcbFont = 132; // Old LHCb style: 62;
        // Line thickness
        float_t lhcbWidth = 2.00; // Old LHCb style: 3.00;
        // Text size
        float_t lhcbTSize = 0.06;
        
        // gROOT->SetStyle("Plain");
        gStyle->SetCanvasDefH(1414);
        gStyle->SetCanvasDefW(1000);
        gStyle->SetPadBottomMargin(0.08);
        gStyle->SetPadTopMargin(0.08);
        gStyle->SetPadLeftMargin(0.12);
        gStyle->SetPadRightMargin(0.12);
        gStyle->SetTitleStyle(0);
        gStyle->SetStatStyle(0);
        // gStyle->SetLineWidth(3);
        gStyle->SetOptStat(0);
        //---- paint...
        char buf[100];
        char bufb[100];
        
        TString rootfile;
        TString plotfile;
        TString plotfilePDF;
        TString plotfileO;
        TString plotfileC;
        // TString OutputFileBase    = outbase+outinfo;
        TString plotextension = TString("/Users/josearias18/Desktop/QCDc2/pythia/Plots/BjetsMC/");
        rootfile = extension_RootFilesMC + extension + TString(".root");
        plotfile = plotextension + extension + TString(".ps");
        
        plotfilePDF = plotextension + extension + TString(".pdf");
        plotfileO = plotfilePDF + TString("(");
        plotfileC = plotfilePDF + TString("]");
        
        // c->SaveAs("plots/"+extension+".pdf");
        
        // c1->SaveAs(Form("plots_misc/Misc_%s"+extension+".pdf", file_name.c_str()));
        // cout<<"...outbase   = "<<outbase.Data()<<endl;
        // cout<<"...rootfile  = "<<rootfile.Data()<<endl;
        // cout<<"...plotfile  = "<<plotfile.Data()<<endl;
        
        // //
        //
          ++ican;
          sprintf(buf, "ccan%d", ican);
          ccan[ican] = new TCanvas(buf, buf, 1);
          ccan[ican]->SetFillColor(10);
          gPad->SetLeftMargin(0.16);
          gPad->SetBottomMargin(0.06);
          gPad->SetRightMargin(0.15);
          ccan[ican]->cd();
          ccan[ican]->Divide(2, 3);
          ccan[ican]->cd(1);
    
          h2_response_ptz->SetStats(0);
          gPad->SetLogz();
          h2_response_ptz->Draw("COLZ");
          h2_response_ptz->SetYTitle("Truth z / p_{T}^{Jet}");
          h2_response_ptz->SetXTitle("Reco z / p_{T}^{Jet}");
    
    
          // Tl.drawLatex(0.7, 0.8, "No cuts");
          ccan[ican]->cd(2);
          h2_response_ptjt->SetStats(0);
          gPad->SetLogz();
          h2_response_ptjt->Draw("COLZ");
          h2_response_ptjt->SetYTitle("Truth j_{T} / p_{T}^{Jet}");
          h2_response_ptjt->SetXTitle("Reco j_{T} / p_{T}^{Jet}");
    
    
          // Tl.drawLatex(0.7, 0.8, "No cuts");
          ccan[ican]->cd(3);
         h2_response_ptr->SetStats(0);
         gPad->SetLogz();
         h2_response_ptr->Draw("COLZ");
         h2_response_ptr->SetYTitle("Truth r / p_{T}^{Jet}");
         h2_response_ptr->SetXTitle("Reco r / p_{T}^{Jet}");
    
        ccan[ican]->cd(4);
        gPad->SetLogy();
        TRandom3 *randomGenerator = new TRandom3();
        for (int i = 0; i < ptbinsize; i++)
        {
            TH1D *h1_temp = (TH1D *)h2_response_jetpt->ProjectionX(Form("htemp_%djetpt", i), i + 1, i + 1);
            h1_temp->Scale(1. / h1_temp->Integral());
            h1_temp->SetMarkerStyle(i + 23);
            h1_temp->SetMarkerColor(i + 4);
            h1_temp->SetLineColor(i + 4);
            h1_temp->Draw("P E SAME");
            int selectbin = SampleTH1(h1_temp, randomGenerator);
            // h1_temp->SetMinimum(0.);
            // h1_temp->SetMaximum(1.05);
        }
        
        ccan[ican]->cd(5);
        gPad->SetLogz();
        
        h2_response_jetpt->SetStats(0);
        h2_response_jetpt->Draw("COLZ");
        
//         ccan[ican]->cd(4);
//         NormalizeHist(h1_jetpt);
//         h1_jetpt->Draw("same");
//        
//         NormalizeHist(h1_jetpt_truth);
//         h1_jetpt_truth->SetLineColor(kGreen);
//         h1_jetpt_truth->Draw("same");
        
        ccan[ican]->cd(6);
        // h2_response_ptktdR->GetZaxis()->SetRange(2,5);
        gPad->SetLogy();
        // h2_response_ptktdR->Draw("COLZ");
        h1_denom_efficiency_jetpt->SetXTitle("p_{T}^{jet}");
        h1_denom_efficiency_jetpt->Draw("SAME");
        h1_denom_purity_jetpt->Draw("SAME");
        
//        ccan[ican]->cd(6);
//        gPad->SetLogy();
//        //  stack_theta_resolution->Draw("nostack");
//        //  for (int i = 0; i < MaxEmissions; i++)
//        //  {
//        //    h1_theta_resolution_vec[i]->SetLineColor(1 + i);
//        //    // h1_theta_resolution_vec[i]->Fit()
//        //  }
//        
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
//        //
//        //
        ++ican;
        sprintf(buf, "ccan%d", ican);
        ccan[ican] = new TCanvas(buf, buf, 1);
        ccan[ican]->SetFillColor(10);
        gPad->SetLeftMargin(0.16);
        gPad->SetBottomMargin(0.06);
        gPad->SetRightMargin(0.15);
        
          ccan[ican]->cd();
          ccan[ican]->Divide(2, 3);
          ccan[ican]->cd(1);
          gPad->SetLogz();
          h2_truthreco_z->SetStats(0);
          h2_truthreco_z->SetXTitle("MCTrue z");
          h2_truthreco_z->SetYTitle("MCReco z");
          // h2_lundplane->Sethflocimum(.01);
          // h2_lundplane->SetMinimum(0.00001);
          h2_truthreco_z->Draw("COLZ");
          Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
          // Tl.drawLatex(0.7, 0.8, "No cuts");
//        //
          ccan[ican]->cd(2);
          gPad->SetLogz();
          h2_truthreco_jt->SetStats(0);
          h2_truthreco_jt->SetXTitle("MCTrue jt");
          h2_truthreco_jt->SetYTitle("MCReco jt");
//        //  // h2_lundplane->Sethflocimum(.01);
//        //  // h2_lundplane->SetMinimum(0.00001);
          h2_truthreco_jt->Draw("COLZ");
          ccan[ican]->cd(3);
          gPad->SetLogz();
          h2_truthreco_r->SetStats(0);
          h2_truthreco_r->SetXTitle("MCTrue r");
          h2_truthreco_r->SetYTitle("MCReco r");
//        //  // h2_lundplane->Sethflocimum(.01);
//        //  // h2_lundplane->SetMinimum(0.00001);
          h2_truthreco_r->Draw("COLZ");
//        //  ccan[ican]->cd(4);
//        //  gPad->SetLogz();
//        //  h2_truthreco_dR->SetStats(0);
//        //  h2_truthreco_dR->SetXTitle("MCTrue ln(#Delta R)");
//        //  h2_truthreco_dR->SetYTitle("MCReco ln(#Delta R)");
//        //  // h2_lundplane->Sethflocimum(.01);
//        //  // h2_lundplane->SetMinimum(0.00001);
//        //  h2_truthreco_dR->Draw("COLZ");
//        //
          ccan[ican]->cd(5);
        
          ccan[ican]->cd(6);
        
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

          ++ican;
          sprintf(buf, "ccan%d", ican);
          ccan[ican] = new TCanvas(buf, buf, 1);
          ccan[ican]->SetFillColor(10);
          gPad->SetLeftMargin(0.16);
          gPad->SetBottomMargin(0.06);
          gPad->SetRightMargin(0.15);
          ccan[ican]->cd();
          ccan[ican]->Divide(2, 3);
    
          ccan[ican]->cd(1);
          h1_purity_z->SetMarkerColor(kRed);
          h1_purity_z->SetMarkerStyle(20);
          h1_purity_z->Draw("P E same");
          h1_purity_z->SetTitle("; z; Purity or Efficiency");
//        //
          h1_efficiency_z->SetMarkerColor(kBlue);
          h1_efficiency_z->SetMarkerStyle(21);
          h1_efficiency_z->Draw("P E same");
        
          h1_purity_z->SetMinimum(0.);
          h1_purity_z->SetMaximum(1.08);

//        //  // h1_efficiency_kT->SetTitle("; ln(R/#Delta R); efficiency");
//        //  // h1_purity_Erad->SetXTitle("E_{radiator}");
//        //  // h1_purity_Erad->SetYTitle("Counts");
//        //  // gPad->Update();
//        //  // auto graph1 = h1_purity_kT->GetPaintedGraph();
//        //  // graph1->SetMinimum(0);
//        //  // graph1->SetMaximum(1);
//        //  // gPad->Update();
//        //
          auto legendeff = new TLegend(0.6, 0.4, 0.8, 0.6);
          legendeff->SetBorderSize(0);
          legendeff->SetFillStyle(0);
          legendeff->SetFillColor(3);
          legendeff->AddEntry(h1_efficiency_z, "Efficiency");
          legendeff->AddEntry(h1_purity_z, "Purity");
          legendeff->Draw("SAME");
//        //
//        //  // h1_purity_Erad->SetXTitle("E_{radiator}");
//        //  // h1_purity_Erad->SetYTitle("Counts");
          ccan[ican]->cd(2);
          h1_purity_jt->SetMarkerColor(kRed);
          h1_purity_jt->SetMarkerStyle(20);
          h1_purity_jt->Draw("P E same");
          h1_purity_jt->SetTitle("; j_{T}; Purity or Efficiency");
        
          h1_efficiency_jt->SetMarkerColor(kBlue);
          h1_efficiency_jt->SetMarkerStyle(21);
          h1_efficiency_jt->Draw("P E same");
        
          h1_purity_jt->SetMinimum(0.);
          h1_purity_jt->SetMaximum(1.08);
        
          h1_efficiency_jt->Draw("P SAME");
    
    auto legendeff_jt = new TLegend(0.6, 0.4, 0.8, 0.6);
    legendeff_jt->SetBorderSize(0);
    legendeff_jt->SetFillStyle(0);
    legendeff_jt->SetFillColor(3);
    legendeff_jt->AddEntry(h1_efficiency_jt, "Efficiency");
    legendeff_jt->AddEntry(h1_purity_jt, "Purity");
    legendeff_jt->Draw("SAME");
    
        ccan[ican]->cd(3);
        h1_purity_r->SetMarkerColor(kRed);
        h1_purity_r->SetMarkerStyle(20);
        h1_purity_r->Draw("P E same");
        h1_purity_r->SetTitle("; r; Purity or Efficiency");
  
        h1_efficiency_r->SetMarkerColor(kBlue);
        h1_efficiency_r->SetMarkerStyle(21);
        h1_efficiency_r->Draw("P E same");
  
        h1_purity_r->SetMinimum(0.);
        h1_purity_r->SetMaximum(1.08);
  
        h1_efficiency_r->Draw("P SAME");
    
    auto legendeff_r = new TLegend(0.6, 0.3, 0.8, 0.5);
    legendeff_r->SetBorderSize(0);
    legendeff_r->SetFillStyle(0);
    legendeff_r->SetFillColor(3);
    legendeff_r->AddEntry(h1_efficiency_r, "Efficiency");
    legendeff_r->AddEntry(h1_purity_r, "Purity");
    legendeff_r->Draw("SAME");
    

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
        ccan[ican] = new TCanvas(buf, buf, 1);
        ccan[ican]->SetFillColor(10);
        gPad->SetLeftMargin(0.16);
        gPad->SetBottomMargin(0.06);
        gPad->SetRightMargin(0.15);
        ccan[ican]->cd();
        ccan[ican]->Divide(2, 3);
        ccan[ican]->cd(1);
        
        h1_purity_jetpt->SetMarkerColor(kRed);
        h1_purity_jetpt->SetMarkerStyle(21);
        h1_purity_jetpt->SetMinimum(0.);
        h1_purity_jetpt->SetMaximum(1.05);
        h1_purity_jetpt->Draw("P E same");
        h1_purity_jetpt->SetTitle("; p_{T}^{Jet};  Purity or Efficiency");
 
        h1_efficiency_jetpt->SetMarkerColor(kBlue);
        h1_efficiency_jetpt->SetMarkerStyle(22);
        h1_efficiency_jetpt->SetMinimum(0.);
        h1_efficiency_jetpt->SetMaximum(1.05);
        h1_efficiency_jetpt->Draw("P E same");
    
    auto legendeff_jetpt = new TLegend(0.5, 0.4, 0.7, 0.7);
    legendeff_jetpt->SetTextSize(0.03);
    legendeff_jetpt->SetBorderSize(0);
    legendeff_jetpt->SetFillStyle(0);
    legendeff_jetpt->SetFillColor(3);
    legendeff_jetpt->AddEntry(h1_efficiency_jetpt, "HF Reco. Efficiency");
    legendeff_jetpt->AddEntry(h1_purity_jetpt, "HF Reco. Purity");
    legendeff_jetpt->Draw("SAME");
    
        // h1_purity_jetpt->SetXTitle("E_{radiator}");
        // h1_purity_jetpt->SetYTitle("Counts");
        // gPad->Update();
        // auto graphpt3 = h1_purity_jetpt->GetPaintedGraph();
        // graphpt3->SetMinimum(0);
        // graphpt3->SetMaximum(1);
        // gPad->Update();
        // h1_purity_jetpt->SetMinimum(0.0);
          ccan[ican]->cd(2);
        //
        //  // SetRecoStyle(h1_jetpt_reco);
        //  // SetTruthStyle(h1_jetpt_true);
        //  // h1_jetpt_reco->Draw("SAME");
        //  // h1_jetpt_true->Draw("SAME");
          h3_efficiency_HFptetajetpt->GetYaxis()->SetRange(1, 1);
          h3_purity_HFptetajetpt->GetYaxis()->SetRange(2, 2);
          TH2D *h2_temp = (TH2D *)(h3_efficiency_HFptetajetpt->Project3D("zx_eff"));
          TH2D *h2_temp_pur = (TH2D *)(h3_purity_HFptetajetpt->Project3D("zx_pur"));
          for (int i = 0; i < customptbinsize; i++)
          {
        
            TH1D *h1_temp = (TH1D *)(h2_temp->ProjectionX(Form("htemp%d_HFptetajetpt", i), i + 1, i + 1));
            TH1D *h1_temp_pur = (TH1D *)(h2_temp_pur->ProjectionX(Form("htemp_pur%d_HFptetajetpt", i), i + 1, i + 1));
        
            h1_temp_pur->SetMarkerStyle(i + 23);
            h1_temp_pur->SetMarkerColor(i + 4);
            h1_temp_pur->SetLineColor(i + 4);
            h1_temp_pur->Draw("P E SAME");
            h1_temp_pur->SetMinimum(0.);
            h1_temp_pur->SetMaximum(1.05);
        
            h1_temp->SetMarkerStyle(i + 20);
            h1_temp->SetMarkerColor(i + 1);
            h1_temp->SetLineColor(i + 1);
            h1_temp->Draw("P E SAME");
          }
//        
//        // h1_purity_rap->SetMarkerColor(kRed);
//        // h1_purity_rap->SetMarkerStyle(21);
//        // h1_purity_rap->Draw("AP same");
//        // h1_purity_rap->SetTitle("; Jet #eta; HF Jet Purity");
//        // // h1_purity_rap->SetXTitle("E_{radiator}");
//        // // h1_purity_rap->SetYTitle("Counts");
//        // gPad->Update();
//        // auto grapheta4 = h1_purity_rap->GetPaintedGraph();
//        // grapheta4->SetMinimum(0);
//        // grapheta4->SetMaximum(1);
//        // gPad->Update();
//        
        ccan[ican]->cd(3);
          SetRecoStyle(h1_efficiency_recoJet_jetpt);
          h1_efficiency_recoJet_jetpt->SetMinimum(0.);
          h1_efficiency_recoJet_jetpt->SetMaximum(1.05);
          h1_efficiency_recoJet_jetpt->Draw("P E SAME");
          h1_efficiency_recoJet_jetpt->SetTitle("; Jet pT; Efficiency");
        
        h1_efficiency_jetpt->SetMarkerColor(kRed);
        h1_efficiency_jetpt->SetMarkerStyle(22);
        h1_efficiency_jetpt->SetMinimum(0.);
        h1_efficiency_jetpt->SetMaximum(1.05);
        h1_efficiency_jetpt->Draw("P E same");
        
        SetTruthStyle(h1_HFeff_jetpt);
        h1_HFeff_jetpt->SetMinimum(0.);
        h1_HFeff_jetpt->SetMaximum(1.05);
        h1_HFeff_jetpt->Draw("PE SAME");

    
    auto legendeff_HFrecojet = new TLegend(0.5, 0.7, 0.8, 0.9);
    legendeff_HFrecojet->SetTextSize(0.03);
    legendeff_HFrecojet->SetBorderSize(0);
    legendeff_HFrecojet->SetFillStyle(0);
    legendeff_HFrecojet->SetFillColor(3);
    legendeff_HFrecojet->AddEntry(h1_HFeff_jetpt,"HF Reco. Efficiency");
    legendeff_HFrecojet->AddEntry(h1_efficiency_jetpt,"HF Jet Reco. Efficiency");
    legendeff_HFrecojet->AddEntry(h1_efficiency_recoJet_jetpt," Jet Reco. Efficiency");
    legendeff_HFrecojet->Draw("SAME");
//
//         for (int i = 0; i < customptbinsize; i++)
//         {
//           TH1D *h1_temp = (TH1D *)h2_SVTag_eff->ProjectionX(Form("htemp_sveff%d", i), i + 1, i + 1);
//           TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur->ProjectionX(Form("htemp_pur_sveff%d", i), i + 1, i + 1);
//        
//           h1_temp->SetMarkerStyle(i + 20);
//           h1_temp->SetMarkerColor(i + 1);
//           h1_temp->SetLineColor(i + 1);
//           h1_temp->Draw("P E SAME");
//           h1_temp->Draw("HIST SAME");
//           h1_temp->SetMinimum(0.);
//           h1_temp->SetMaximum(1.05);
//        
//           h1_temp_pur->SetMarkerStyle(i + 23);
//           h1_temp_pur->SetMarkerColor(i + 4);
//           h1_temp_pur->SetLineColor(i + 4);
//           h1_temp_pur->Draw("P E SAME");
//           h1_temp_pur->Draw("HIST SAME");
//           // h1_temp_pur->SetMinimum(0.);
//           // h1_temp_pur->SetMaximum(1.05);
//         }
//        
//         h1_purity_HFpt->SetMarkerColor(kRed);
//         h1_purity_HFpt->SetMarkerStyle(21);
//         h1_purity_HFpt->Draw("P E same");
//         h1_purity_HFpt->SetTitle("; HF pT; Purity or Efficiency");
//         h1_purity_HFpt->SetMinimum(0.);
//         h1_purity_HFpt->SetMaximum(1.05);
//        
//         h1_efficiency_HFpt->SetMarkerColor(kBlue);
//         h1_efficiency_HFpt->SetMarkerStyle(22);
//         h1_efficiency_HFpt->Draw("P E same");
//        
//         h1_efficiency_HFpt->SetTitle("; HF pT; Purity");
//        
//         f_pur1->Draw("SAME");
//         f_eff1->Draw("SAME");
//        
        ccan[ican]->cd(4);
//        // SetRecoStyle(h1_jetpt_reco);
//        // SetTruthStyle(h1_jetpt_true);
//        // h1_jetpt_reco->Draw("SAME");
//        // h1_jetpt_true->Draw("SAME");
//        
          for (int i = 0; i < HFetabinsize; i++)
          {
            TH1D *h1_temp = (TH1D *)h2_efficiency_HFpteta->ProjectionX(Form("htemp%d_HFpteta", i), i + 1, i + 1);
            TH1D *h1_temp_pur = (TH1D *)h2_purity_HFpteta->ProjectionX(Form("htemp_pur%d_HFpteta", i), i + 1, i + 1);
        
            h1_temp_pur->SetMarkerStyle(i + 23);
            h1_temp_pur->SetMarkerColor(i + 4);
            h1_temp_pur->SetLineColor(i + 4);
            h1_temp_pur->Draw("P E SAME");
            h1_temp_pur->SetMinimum(0.);
            h1_temp_pur->SetMaximum(1.05);
            h1_temp_pur->SetTitle("; p_{T}^{HF}; Purity or Efficiency");
        
            h1_temp->SetMarkerStyle(i + 20);
            h1_temp->SetMarkerColor(i + 1);
            h1_temp->SetLineColor(i + 1);
            h1_temp->Draw("P E SAME");
          }
//        
//        // for (int i = 0; i < customptbinsize; i++)
//        // {
//        //   TH1D *h1_temp = (TH1D *)h2_SVTag_eff_z->ProjectionX(Form("htemp%d_z", i), i + 1, i + 1);
//        //   TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur_z->ProjectionX(Form("htemppur%d_z", i), i + 1, i + 1);
//        
//        //   h1_temp->SetMarkerStyle(i + 20);
//        //   h1_temp->SetMarkerColor(i + 1);
//        //   h1_temp->SetLineColor(i + 1);
//        //   h1_temp->Draw("P E SAME");
//        //   h1_temp->Draw("HIST SAME");
//        //   h1_temp->SetMinimum(0.);
//        //   h1_temp->SetMaximum(1.05);
//        
//        //   h1_temp_pur->SetMarkerStyle(i + 23);
//        //   h1_temp_pur->SetMarkerColor(i + 4);
//        //   h1_temp_pur->SetLineColor(i + 4);
//        //   h1_temp_pur->Draw("P E SAME");
//        //   h1_temp_pur->Draw("HIST SAME");
//        //   h1_temp_pur->SetMinimum(0.);
//        //   h1_temp_pur->SetMaximum(1.05);
//        // }
//        
        ccan[ican]->cd(5);
          SetRecoStyle(h1_efficiency_recoJet_HFpt);
         h1_efficiency_recoJet_HFpt->SetTitle("; P_{T}^{HF}; Efficiency");
          h1_efficiency_recoJet_HFpt->Draw("P E SAME");
          h1_efficiency_recoJet_HFpt->SetMinimum(0.);
    h1_efficiency_recoJet_HFpt->SetMaximum(1.05);
    
        h1_efficiency_HFpt->SetMarkerColor(kRed);
        h1_efficiency_HFpt->SetMarkerStyle(22);
        h1_efficiency_HFpt->Draw("P E same");
       h1_efficiency_HFpt->SetTitle("; P_{T}^{HF}; Efficiency");
        
        SetTruthStyle(h1_HFeff_HFpt);
        h1_HFeff_HFpt->Draw("PE SAME");
    
        auto legend_diffeff = new TLegend(0.6, 0.7, 0.8, 0.9);
    legend_diffeff->SetBorderSize(0);
    legend_diffeff->SetFillStyle(0);
    legend_diffeff->SetFillColor(3);
    legend_diffeff->AddEntry(h1_efficiency_recoJet_HFpt, "Jet Reco. Efficiency");
    legend_diffeff->AddEntry(h1_HFeff_HFpt, "HF Reco. Efficiency");
    legend_diffeff->AddEntry(h1_efficiency_HFpt, "Reco. Efficiency");
    
    legend_diffeff->Draw("SAME");
        
        ccan[ican]->cd(6);
        
        auto legendeffpur = new TLegend(0.35, 0.45, 0.65, 0.75);
        legendeffpur->SetTextSize(0.03);
        legendeffpur->SetBorderSize(0);
        legendeffpur->SetFillStyle(0);
        legendeffpur->SetFillColor(3);
        
        for (int i = 0; i < customptbinsize; i++)
        {
            TH1D *h1_temp = (TH1D *)h2_efficiency_HFptjetpt->ProjectionX(Form("htemp%d_HFptjetpt", i), i + 1, i + 1);
            TH1D *h1_temp_pur = (TH1D *)h2_purity_HFptjetpt->ProjectionX(Form("htemp_pur%d_HFptjetpt", i), i + 1, i + 1);
            
            h1_temp_pur->SetMarkerStyle(i + 23);
            h1_temp_pur->SetMarkerColor(i + 4);
            h1_temp_pur->SetLineColor(i + 4);
            h1_temp_pur->Draw("P E SAME");
            h1_temp_pur->SetMinimum(0.);
            h1_temp_pur->SetMaximum(1.05);
            h1_temp_pur->SetTitle("; p_{T}^{HF}; Purity or Efficiency");
            
            h1_temp->SetMarkerStyle(i + 20);
            h1_temp->SetMarkerColor(i + 1);
            h1_temp->SetLineColor(i + 1);
            h1_temp->Draw("P E SAME");
            
            legendeffpur->AddEntry(h1_temp_pur, Form("Purity, %.1f < p_{T}^{jet} < %.1f GeV", custompt_binedges[i], custompt_binedges[i + 1]));
            legendeffpur->AddEntry(h1_temp, Form("Efficiency, %.1f < p_{T}^{jet} < %.1f GeV", custompt_binedges[i], custompt_binedges[i + 1]));
        }
        legendeffpur->Draw("SAME");
//        
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
//        //
        ++ican;
        sprintf(buf, "ccan%d", ican);
        ccan[ican] = new TCanvas(buf, buf, 1);
        ccan[ican]->SetFillColor(10);
        gPad->SetLeftMargin(0.16);
        gPad->SetBottomMargin(0.06);
        gPad->SetRightMargin(0.15);
        ccan[ican]->cd();
        ccan[ican]->Divide(2, 3);
        ccan[ican]->cd(1);
        for (int i = 0; i < customptbinsize; i++)
        {
            TH1D *h1_temp = (TH1D *)h2_SVTag_eff_z->ProjectionX(Form("htemp%d_z", i), i + 1, i + 1);
            TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur_z->ProjectionX(Form("htemppur%d_z", i), i + 1, i + 1);
            
            h1_temp->SetMarkerStyle(i + 20);
            h1_temp->SetMarkerColor(i + 1);
            h1_temp->SetLineColor(i + 1);
            h1_temp->Draw("P E SAME");
            h1_temp->Draw("HIST SAME");
            h1_temp->SetMinimum(0.);
            h1_temp->SetMaximum(1.05);
            
            h1_temp_pur->SetMarkerStyle(i + 23);
            h1_temp_pur->SetMarkerColor(i + 4);
            h1_temp_pur->SetLineColor(i + 4);
            h1_temp_pur->Draw("P E SAME");
            h1_temp_pur->Draw("HIST SAME");
            h1_temp_pur->SetMinimum(0.);
            h1_temp_pur->SetMaximum(1.05);
            

        }
//        
        ccan[ican]->cd(2);
    auto legendeff_sv = new TLegend(0.35, 0.45, 0.65, 0.75);
    legendeff_sv->SetTextSize(0.03);
    legendeff_sv->SetBorderSize(0);
    legendeff_sv->SetFillStyle(0);
    legendeff_sv->SetFillColor(3);
        for (int i = 0; i < customptbinsize; i++)
        {
            TH1D *h1_temp = (TH1D *)h2_SVTag_eff->ProjectionX(Form("htemp%d_svtag", i), i + 1, i + 1);
            TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur->ProjectionX(Form("htemppur%d_svtag", i), i + 1, i + 1);
            
            h1_temp->SetMarkerStyle(i + 20);
            h1_temp->SetMarkerColor(i + 1);
            h1_temp->SetLineColor(i + 1);
            h1_temp->Draw("P E SAME");
            h1_temp->Draw("HIST SAME");
            h1_temp->SetMinimum(0.);
            h1_temp->SetMaximum(1.05);
            
            h1_temp_pur->SetMarkerStyle(i + 23);
            h1_temp_pur->SetMarkerColor(i + 4);
            h1_temp_pur->SetLineColor(i + 4);
            h1_temp_pur->Draw("P E SAME");
            h1_temp_pur->Draw("HIST SAME");
            h1_temp_pur->SetMinimum(0.);
            h1_temp_pur->SetMaximum(1.05);
            
            legendeff_sv->AddEntry(h1_temp_pur, Form("SV Purity, %.1f < p_{T}^{jet} < %.1f GeV", custompt_binedges[i], custompt_binedges[i + 1]));
            legendeff_sv->AddEntry(h1_temp, Form("SV Efficiency, %.1f < p_{T}^{jet} < %.1f GeV", custompt_binedges[i], custompt_binedges[i + 1]));
        }
    legendeff_sv->Draw("SAME");
//
        if (ican == 0)
        {
            ccan[ican]->Print(plotfileO.Data());
        }
        else
        {
            ccan[ican]->Print(plotfilePDF.Data());
        }
        
//        //
//        //
          ++ican;
          sprintf(buf, "ccan%d", ican);
          ccan[ican] = new TCanvas(buf, buf, 1);
          ccan[ican]->SetFillColor(10);
          gPad->SetLeftMargin(0.16);
          gPad->SetBottomMargin(0.06);
          gPad->SetRightMargin(0.15);
          ccan[ican]->cd();
          ccan[ican]->Divide(2, 3);
          ccan[ican]->cd(1);
//        //  //  cout<<h2_response_dR->Integral()<<endl;
//        //  h2_response_dR->Draw("COLZ TEXT");
//        //
//        //  // h1_purity_Erad->SetXTitle("E_{radiator}");
//        //  // h1_purity_Erad->SetYTitle("Counts");
//        //  ccan[ican]->cd(2);
//        //  cout << h2_response_theta->Integral() << endl;
//        //  h2_response_theta->Draw("COLZ TEXT");
//        //  // h1_efficiency_theta->SetMinimum(0.0);
//        //
//        //  ccan[ican]->cd(3);
//        //  h2_response_Erad->Draw("COLZ TEXT");
//        //
//        //  ccan[ican]->cd(4);
//        //  h2_response_kt->Draw("COLZ TEXT");
//        //
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Update();
//        //  if (ican == 0)
//        //  {
//        //    ccan[ican]->Print(plotfileO.Data());
//        //  }
//        //  else
//        //  {
//        //    ccan[ican]->Print(plotfilePDF.Data());
//        //  }
//        //
//        //  //
//        //  ++ican;
//        //  sprintf(buf, "ccan%d", ican);
//        //  ccan[ican] = new TCanvas(buf, buf, 1);
//        //  ccan[ican]->SetFillColor(10);
//        //  gPad->SetLeftMargin(0.16);
//        //  gPad->SetBottomMargin(0.06);
//        //  gPad->SetRightMargin(0.15);
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Divide(2, 3);
//        //  ccan[ican]->cd(1);
//        //  // h2_purity_ktdR->SetMarkerColor(kBlue);
//        //  // h2_purity_ktdR->SetMarkerStyle(21);
//        //  h2_purity_ktdR->Draw("COLZ");
//        //  h2_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
//        //  // h2_purity_ktdR->SetMaximum(1.0);
//        //  // h2_purity_ktdR->SetMinimum(0.0);
//        //  // h1_purity_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(2);
//        //  // h2_purity_ktdR->SetMarkerColor(kBlue);
//        //  // h2_purity_ktdR->SetMarkerStyle(21);
//        //  h2_num_purity_ktdR->Draw("COLZ");
//        //  h2_num_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
//        //  // h1_purity_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(3);
//        //  // h2_purity_ktdR->SetMarkerColor(kBlue);
//        //  // h2_purity_ktdR->SetMarkerStyle(21);
//        //  h2_denom_purity_ktdR->Draw("COLZ");
//        //  h2_denom_purity_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
//        //  // h1_purity_rap->SetXTitle("E_{radiator}");
//        //  ccan[ican]->cd(4);
//        //  // h2_purity_ktdR->SetMarkerColor(kBlue);
//        //  // h2_purity_ktdR->SetMarkerStyle(21);
//        //  h2_purity_zdR->Draw("COLZ");
//        //  h2_purity_zdR->SetTitle("; ln(R/#Delta R); ln(1/z)");
//        //  // h2_purity_ktdR->SetMaximum(1.0);
//        //  // h2_purity_ktdR->SetMinimum(0.0);
//        //  // h1_purity_rap->SetXTitle("E_{radiator}");
//        //
//        //  //  ccan[ican]->cd(5);
//        //  //  auto legend00 = new TLegend(0.6,0.2,0.8,0.4);
//        //  // legend00->SetBorderSize(0);
//        //  // legend00->SetFillStyle(0);
//        //  // legend00->SetFillColor(3);
//        //  //  THStack * stack_pur = new THStack("stack_pur_kt", "stack");
//        //  //  for(int i = 0; i < ptbinsize; i++){
//        //  //   TH1D* h1 = (TH1D*) h2_purity_ptkt->ProjectionX(Form("pur%d_x", i), i+1, i+1);
//        //  //   h1->SetLineColor(i+1);
//        //  //   stack_pur->Add(h1);
//        //  //   legend00->AddEntry(h1, Form("[%.0f, %.0f]", pt_binedges[i], pt_binedges[i+1]));
//        //  //  }
//        //  //  stack_pur->Draw("PLC NOSTACK");
//        //  //  legend00->Draw("SAME");
//        //
//        //  //  ccan[ican]->cd(6);
//        //  //  THStack * stack_eff = new THStack("stack_eff_kt", "stack");
//        //  //  for(int i = 0; i < ptbinsize; i++){
//        //  //   TH1D* h1 = (TH1D*) h2_efficiency_ptkt->ProjectionX(Form("eff%d_x", i), i+1, i+1);
//        //  //   h1->SetLineColor(i+1);
//        //  //   stack_eff->Add(h1);
//        //  //  }
//        //  //  stack_eff->Draw("PLC NOSTACK");
//        //
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Update();
//        //  if (ican == 0)
//        //  {
//        //    ccan[ican]->Print(plotfileO.Data());
//        //  }
//        //  else
//        //  {
//        //    ccan[ican]->Print(plotfilePDF.Data());
//        //  }
//        //
//        //  //
//        //  ++ican;
//        //  sprintf(buf, "ccan%d", ican);
//        //  ccan[ican] = new TCanvas(buf, buf, 1);
//        //  ccan[ican]->SetFillColor(10);
//        //  gPad->SetLeftMargin(0.16);
//        //  gPad->SetBottomMargin(0.06);
//        //  gPad->SetRightMargin(0.15);
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Divide(2, 3);
//        //  ccan[ican]->cd(1);
//        //  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
//        //  // h2_efficiency_ktdR->SetMarkerStyle(21);
//        //  h2_efficiency_ktdR->Draw("COLZ");
//        //  h2_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
//        //  // h2_efficiency_ktdR->SetMaximum(1.0);
//        //  // h2_efficiency_ktdR->SetMinimum(0.0);
//        //  // h1_efficiency_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(2);
//        //  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
//        //  // h2_efficiency_ktdR->SetMarkerStyle(21);
//        //  h2_num_efficiency_ktdR->Draw("COLZ");
//        //  h2_num_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
//        //  // h1_efficiency_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(3);
//        //  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
//        //  // h2_efficiency_ktdR->SetMarkerStyle(21);
//        //  h2_denom_efficiency_ktdR->Draw("COLZ");
//        //  h2_denom_efficiency_ktdR->SetTitle("; ln(R/#Delta R); ln(kT)");
//        //  // h1_efficiency_rap->SetXTitle("E_{radiator}");
//        //  ccan[ican]->cd(4);
//        //  // h2_efficiency_ktdR->SetMarkerColor(kBlue);
//        //  // h2_efficiency_ktdR->SetMarkerStyle(21);
//        //  h2_efficiency_zdR->Draw("COLZ");
//        //  h2_efficiency_zdR->SetTitle("; ln(R/#Delta R); ln(1/z)");
//        //  // h2_efficiency_ktdR->SetMaximum(1.0);
//        //  // h2_efficiency_ktdR->SetMinimum(0.0);
//        //  // h1_purity_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(5);
//        //  //  THStack * stack_pur_z = new THStack("stack_pur_z", "stack_pur_z");
//        //  //  for(int i = 0; i < ptbinsize; i++){
//        //  //   TH1D* h1 = (TH1D*) h2_purity_ptz->ProjectionX(Form("pur_z%d_x", i), i+1, i+1);
//        //  //   h1->SetLineColor(i+1);
//        //  //   stack_pur_z->Add(h1);
//        //  //  }
//        //  //  stack_pur_z->Draw("PLC NOSTACK");
//        //  //  legend00->Draw("SAME");
//        //
//        //  //  ccan[ican]->cd(6);
//        //  //  THStack * stack_eff_z = new THStack("stack_eff_z", "stack_eff_z");
//        //  //  for(int i = 0; i < ptbinsize; i++){
//        //  //   TH1D* h1 = (TH1D*) h2_efficiency_ptz->ProjectionX(Form("eff_z%d_x", i), i+1, i+1);
//        //  //   h1->SetLineColor(i+1);
//        //  //   stack_eff_z->Add(h1);
//        //  //  }
//        //  //  stack_eff_z->Draw("PLC NOSTACK");
//        //
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Update();
//        //  if (ican == 0)
//        //  {
//        //    ccan[ican]->Print(plotfileO.Data());
//        //  }
//        //  else
//        //  {
//        //    ccan[ican]->Print(plotfilePDF.Data());
//        //  }
//        //
//        //  //
//        //  ++ican;
//        //  sprintf(buf, "ccan%d", ican);
//        //  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
//        //  ccan[ican]->SetFillColor(10);
//        //  gPad->SetLeftMargin(0.16);
//        //  gPad->SetBottomMargin(0.06);
//        //  gPad->SetRightMargin(0.15);
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
//        //  ccan[ican]->cd(1);
//        //  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
//        //  // h2_efficiency_thetaErad->SetMarkerStyle(21);
//        //  h2_efficiency_thetaErad->Draw("COLZ");
//        //  h2_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
//        //  // h2_efficiency_thetaErad->SetMaximum(1.0);
//        //  // h2_efficiency_thetaErad->SetMinimum(0.0);
//        //  // h1_efficiency_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(2);
//        //  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
//        //  // h2_efficiency_thetaErad->SetMarkerStyle(21);
//        //  h2_num_efficiency_thetaErad->Draw("COLZ");
//        //  h2_num_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
//        //  // h1_efficiency_rap->SetXTitle("E_{radiator}");
//        //
//        //  ccan[ican]->cd(3);
//        //  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
//        //  // h2_efficiency_thetaErad->SetMarkerStyle(21);
//        //  h2_denom_efficiency_thetaErad->Draw("COLZ");
//        //  h2_denom_efficiency_thetaErad->SetTitle("; ln(1/#theta); Erad");
//        //  // h1_efficiency_rap->SetXTitle("E_{radiator}");
//        //  ccan[ican]->cd(4);
//        //  // h2_efficiency_thetaErad->SetMarkerColor(kBlue);
//        //  // h2_efficiency_thetaErad->SetMarkerStyle(21);
//        //  h2_purity_thetaErad->Draw("COLZ");
//        //  h2_purity_thetaErad->SetTitle("; ln(1/#theta); Erad");
//        //  // h2_efficiency_thetaErad->SetMaximum(1.0);
//        //  // h2_efficiency_thetaErad->SetMinimum(0.0);
//        //  // h1_purity_rap->SetXTitle("E_{radiator}");
//        
//        ccan[ican]->cd();
//        ccan[ican]->Update();
//        if (ican == 0)
//        {
//            ccan[ican]->Print(plotfileO.Data());
//        }
//        else
//        {
//            ccan[ican]->Print(plotfilePDF.Data());
//        }
//        
//        //
//        ++ican;
//        sprintf(buf, "ccan%d", ican);
//        ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
//        ccan[ican]->SetFillColor(10);
//        gPad->SetLeftMargin(0.16);
//        gPad->SetBottomMargin(0.06);
//        gPad->SetRightMargin(0.15);
//        ccan[ican]->cd();
//        ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
//        ccan[ican]->cd(1);
//        
//        h2_sv_mass_z_truepos->Draw("COLZ");
//        
//        ccan[ican]->cd(2);
//        
//        h2_bdt_z_truepos->Draw("COLZ");
//        
//        ccan[ican]->cd(3);
//        
//        h2_bdt_sv_mass_truepos->Draw("COLZ");
//        
//        ccan[ican]->cd(4);
//        SetRecoStyle(h1_r_false);
//        SetTruthStyle(h1_r_true);
//        // NormalizeHist(h1_r_false);
//        // NormalizeHist(h1_r_true);
//        h1_r_true->Draw("P E SAME");
//        h1_r_false->Draw("P E SAME");
//        
//        ccan[ican]->cd();
//        ccan[ican]->Update();
//        if (ican == 0)
//        {
//            ccan[ican]->Print(plotfileO.Data());
//        }
//        else
//        {
//            ccan[ican]->Print(plotfilePDF.Data());
//        }
//        //
//        
//        //
//        ++ican;
//        sprintf(buf, "ccan%d", ican);
//        ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
//        ccan[ican]->SetFillColor(10);
//        gPad->SetLeftMargin(0.16);
//        gPad->SetBottomMargin(0.06);
//        gPad->SetRightMargin(0.15);
//        ccan[ican]->cd();
//        ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
//        ccan[ican]->cd(1);
//        
//        h2_sv_mass_z_falsepos->Draw("COLZ");
//        
//        ccan[ican]->cd(2);
//        
//        h2_bdt_z_falsepos->Draw("COLZ");
//        
//        ccan[ican]->cd(3);
//        
//        h2_bdt_sv_mass_falsepos->Draw("COLZ");
//        
//        ccan[ican]->cd(4);
//        SetRecoStyle(h1_z_false);
//        SetTruthStyle(h1_z_true);
//        SetDataStyle(h1_z_truefalse);
//        // NormalizeHist(h1_z_false);
//        // NormalizeHist(h1_z_true);
//        // NormalizeHist(h1_z_truefalse);
//        h1_z_truefalse->Draw("PE SAME");
//        h1_z_false->Draw("P E SAME");
//        h1_z_true->Draw("P E SAME");
//        
//        ccan[ican]->cd();
//        ccan[ican]->Update();
//        if (ican == 0)
//        {
//            ccan[ican]->Print(plotfileO.Data());
//        }
//        else
//        {
//            ccan[ican]->Print(plotfilePDF.Data());
//        }
//        //
//        //
//        
//        ++ican;
//        //  sprintf(buf, "ccan%d", ican);
//        //  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
//        //  ccan[ican]->SetFillColor(10);
//        //  // gPad->SetLeftMargin(0.16);
//        //  // gPad->SetBottomMargin(0.06);
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
//        //
//        //  ccan[ican]->cd(1);
//        //  h3_purity_ptzdR->GetZaxis()->SetRange(1, 1);
//        //  TH2D *h2_temp_purz = (TH2D *)(h3_purity_ptzdR->Project3D("yx_effz1"));
//        //  h2_temp_purz->Draw("COLZ");
//        //  ccan[ican]->cd(2);
//        //  h3_purity_ptzdR->GetZaxis()->SetRange(2, 2);
//        //  h2_temp_purz = (TH2D *)(h3_purity_ptzdR->Project3D("yx_effz2"));
//        //  h2_temp_purz->Draw("COLZ");
//        //  // h2_ptktdR_->SetTitle("Data+Purity+Unfold; ;");
//        //  ccan[ican]->cd(3);
//        //  h3_purity_ptzdR->GetZaxis()->SetRange(3, 3);
//        //  h2_temp_purz = (TH2D *)(h3_purity_ptzdR->Project3D("yx_effz3"));
//        //  h2_temp_purz->Draw("COLZ");
//        //
//        //  ccan[ican]->cd(4);
//        //  h3_purity_ptzdR->GetZaxis()->SetRange(4, 4);
//        //  h2_temp_purz = (TH2D *)(h3_purity_ptzdR->Project3D("yx_effz4"));
//        //  h2_temp_purz->Draw("COLZ");
//        //
//        //  ccan[ican]->cd();
//        //  ccan[ican]->Update();
//        //  if (ican == 0)
//        //  {
//        //    ccan[ican]->Print(plotfileO.Data());
//        //  }
//        //  else
//        //  {
//        //    ccan[ican]->Print(plotfilePDF.Data());
//        //  }
//        
        f->Write();
        f->Close();
//        
        if (ican > -1)
        {
            cout << " You plotted " << ican + 1 << " canvasses......." << endl;
            ccan[ican]->Print(plotfileC.Data());
//            //
//            // sprintf(buf,"/usr/bin/ps2pdf %s %s",plotfile.Data(),plotfilePDF.Data());
//            // cout<<" "<<buf<<endl;
//            // int iSuccess = gSystem->Exec(buf);
//            // if (iSuccess==0){
//            // 	sprintf(buf,"/bin/rm %s",plotfile.Data());
//            // 	gSystem->Exec(buf);
//            // 	cout<<" "<<buf<<endl;
//            // } else {
//            // 	cout<<" PDF creation failed ... "<<plotfile.Data()<<endl;
//            // }
//            //		sprintf(buf,"/usr/bin/scp %s wjllope@rhic22.physics.wayne.edu:/Library/WebServer/WebPages/files/",plotfilePDF.Data());
//            //		gSystem->Exec(buf);
//            //		cout<<" "<<buf<<endl;
        }
//        cout << "Num of Reco B jets = " << NumBjets << endl;
//        cout << "Num of True B jets = " << NumTrueBjets << endl;
//        
        // CAJetAlgo(std::string filename);
        
        // loop(ptMax, Nsubsets);
        // write(ptMax, Nsubsets);
    }
    //
    //int main(int argc, char *argv[])
    //{
    //
    //  int NumEvts = -1;
    //  int dataset = 91599;
    //  double minimum_dR = 0.1;
    //  int DoReverse = false;
    //  bool isData = true;
    //  bool chargedJetCut = false;
    //  bool DoJER = false;
    //  int DoJES = 0;
    //  bool DoTrackPt = false;
    //  bool DoGhostCut = false;
    //  bool DoFSPEff = false;
    //  bool DoTrigEff = false;
    //  int DoPIDEff = 0;
    //  bool DoRecSelEff = false;
    //  bool DoMassFit = false;
    //  bool SubtractGS = false;
    //
    //  // Parsing command line arguments
    //  for (int i = 1; i < argc; ++i)
    //  {
    //    // std::cout << "Parsing!" << std::endl;
    //    std::string arg = argv[i];
    //    if (arg == "-h")
    //    {
    //      // Print help message explaining the options
    //      std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
    //      std::cout << "Options:" << std::endl;
    //      std::cout << "  -n <NumEvts>       : Number of events" << std::endl;
    //      std::cout << "  -dataset <dataset> : Dataset number" << std::endl;
    //      std::cout << "  -isdata <isData>   : Whether the dataset is real data (0 or 1)" << std::endl;
    //      std::cout << "  -charge <chargedJetCut> : Whether to apply charged jet cut (0 or 1)" << std::endl;
    //      std::cout << "  -jer <DoJER>       : Whether to apply JER (0 or 1)" << std::endl;
    //      std::cout << "  -jes <DoJES>       : JES variation (integer)" << std::endl;
    //      std::cout << "  -trackpt <DoTrackPt>     : Whether to apply track pT cut (0 or 1)" << std::endl;
    //      std::cout << "  -ghost <DoGhostCut>       : Whether to apply ghost cut (0 or 1)" << std::endl;
    //      std::cout << "  -fspeff <DoFSPEff>       : Whether to apply full simulation efficiency (0 or 1)" << std::endl;
    //      std::cout << "  -trig <DoTrigEff>        : Whether to apply trigger efficiency (0 or 1)" << std::endl;
    //      std::cout << "  -pideff <DoPIDEff>       : PID efficiency variation (integer)" << std::endl;
    //      std::cout << "  -recsel <DoRecSelEff>    : Whether to apply reconstruction selection efficiency (0 or 1)" << std::endl;
    //      std::cout << "  -massfit <DoMassFit>     : Whether to perform mass fitting (0 or 1)" << std::endl;
    //      std::cout << "  -subtractGS <SubtractGS> : Whether to subtract ghost signals (0 or 1)" << std::endl;
    //      return 0;
    //    }
    //    else if (arg == "-n")
    //    {
    //      // std::cout << argv[i + 1] << std::endl;
    //      if (i + 1 < argc)
    //      {
    //        NumEvts = std::stoi(argv[i + 1]);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-n option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-dataset")
    //    {
    //      // std::cout << argv[i + 1] << std::endl;
    //      if (i + 1 < argc)
    //      {
    //        dataset = std::stoi(argv[i + 1]);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-dataset option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-isdata")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        isData = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-isdata option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-charge")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        chargedJetCut = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-charge option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-mindR")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        minimum_dR = stod(argv[i + 1]);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-mindR option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-jer")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoJER = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-jer option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-reverse")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoReverse = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-reverse option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-fspeff")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoFSPEff = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-fspeff option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-trackpt")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoTrackPt = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-trackpt option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-ghost")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoGhostCut = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-ghost option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-recsel")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoRecSelEff = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-recsel option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-trig")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoTrigEff = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-trig option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-massfit")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoMassFit = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-massfit option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-subtractGS")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        SubtractGS = (stoi(argv[i + 1]) != 0);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-subtractGS option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-jes")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoJES = std::stoi(argv[i + 1]);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-jes option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else if (arg == "-pideff")
    //    {
    //      if (i + 1 < argc)
    //      {
    //        DoPIDEff = std::stoi(argv[i + 1]);
    //        i++;
    //      }
    //      else
    //      {
    //        std::cerr << "-pideff option requires one argument." << std::endl;
    //        return 1;
    //      }
    //    }
    //    else
    //    {
    //      std::cerr << "Unknown option: " << arg << std::endl;
    //      return 1;
    //    }
    //  }
    //
    //  SimpleUnfold(NumEvts,
    //               dataset,
    //               chargedJetCut,
    //               minimum_dR,
    //               DoReverse,
    //               DoJES,
    //               DoJER,
    //               DoFSPEff,
    //               DoTrackPt,
    //               DoGhostCut,
    //               DoRecSelEff,
    //               SubtractGS);
    //  return 0;
    
//    }
//}
    
    
