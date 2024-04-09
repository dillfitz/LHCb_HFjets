
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "TSystem.h"
//#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Settings.h"
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Helpers.h"
//#include "/Users/josearias18/Desktop/QCDc2/root/RooUnfold/src/RooUnfoldResponse.h"

// MC(08152023): 616424
// MC(10192023): 1146186
// MC(10192023 MU): 572852

using namespace std;


void SimpleUnfold(int flavor = 5,
                  bool truthLevel = false,
                  bool isMagUp = true,
                  bool isMagDown = false)
{
    
    int NumEvts;
    
    if (isMagUp){
        NumEvts = 572852;
    }else if (isMagDown){
        NumEvts = 573334;
    } else {
        NumEvts = 1146186;
    }
        
        
    if (flavor == 5)
    {
      mass_num = 4.2;
    }
    else if (flavor == 4)
    {
      mass_num = 1.25;
    }
    else if (flavor == 1)
    {
        mass_num = 0.001;
    }

  //
  //  Naming Convention:
  //  {$1}{$2}{$3}{$4}{$5}
  //  $1: Year: 2016 = 6, 2017 = 7, 2018 = 8, All = 9
  //  $2: jets or dijets: TaggedDijets = 1, else = 2
  //  $3: flavor: b = 5, c = 4, udsg = 1
  //  $4: pT: pt15pt20 = 0, pt20pt50 = 1, pt50 = 2, else = 3
  //  $5: Magnet: MD = 0, MU = 1, Both = 9

    TString str_pT = "";
    TString str_level = "";
    TString str_flavor = "";
    TString str_charged = "";
    TString str_mag = "";

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

  if (isMagUp) {
        str_mag = "MU";
  } else if (isMagDown) {
        str_mag = "MD";
  } else {
        str_mag = "";
  }
    

  TString str_tree;

  TString extension;
//  extension = TString("unfold_") + str_level + Form("_ev_%d", NumEvts) + str_flavor;
  extension = TString("unfold_") + str_level + str_mag + Form("_ev_%d", NumEvts) + str_flavor;
    

  TString extension_read, extension_eff, extension_eff2, extension_RootFilesMC, extension_reco_MD;
        
      // This should be the file from MCMakeVarTree
//  extension_read = TString("tree_") + str_level + str_mag + Form("_ev_%d", NumEvts)  + str_flavor;
//  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts)  + str_flavor;
    extension_read = TString("tree_") + str_level + str_mag + Form("_ev_%d", NumEvts) + str_flavor;
    
  extension_RootFilesMC = TString("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/BjetsMC/");
        
  int  NumEvts_eff0 = 6022748; // MC(08152023)
  int  NumEvts_eff1 = 2189893; // MC(10192023) Both MU & MD
  int  NumEvts_eff2 = 1096343; // MC(10192023) MU
  int  NumEvts_eff3 = 1093550; // MC(10192023) MD
    int NumEvts_reco_MD = 573334; // MC(10192023) MD reco
    
//  extension_eff = TString("efficiency_truth") + Form("_ev_%d", NumEvts_eff1)  + str_flavor;
//  extension_eff = TString("efficiency_truth") +  Form("_ev_%d", NumEvts_eff1)  + str_flavor;
    extension_eff = TString("efficiency_truth") +  str_mag + Form("_ev_%d", NumEvts_eff2)  + str_flavor; //MU
    extension_eff2 = TString("efficiency_truth") +  TString("MD") + Form("_ev_%d", NumEvts_eff3)  + str_flavor; //MD
    
    extension_reco_MD = TString("tree_") + str_level + TString("MD") + Form("_ev_%d", NumEvts_reco_MD) + str_flavor; // MD Jet Decay Tree

  TFile fread( extension_RootFilesMC + extension_read + ".root", "READ");
        
  cout << "File:" << endl;
  cout << extension_read << endl;
  TTree *BTree = (TTree *)fread.Get("BTree");
  if (NumEvts > BTree->GetEntries())
    NumEvts = BTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = BTree->GetEntries();

  TFile *file_eff = new TFile(extension_RootFilesMC + extension_eff + TString(".root"), "READ");

  TH1D* h1_denom_efficiency_HFpt = (TH1D*) file_eff->Get("h1_denom_efficiency_HFpt");
  TH1D* h1_denom_efficiency_HFpt15 = (TH1D*) file_eff->Get("h1_denom_efficiency_HFpt15");
  TH2D* h2_denom_efficiency_HFptjetpt = (TH2D*) file_eff->Get("h2_denom_efficiency_HFptjetpt");
  TH2D* h2_denom_efficiency_jetpteta = (TH2D*) file_eff->Get("denom_efficiency_jetpteta");
  TH1D* h1_denom_efficiency_jetpt = (TH1D*) file_eff->Get("h1_denom_efficiency_jetpt");
    TH1D* h1_denom_efficiency_z = (TH1D*) file_eff->Get("denom_efficiency_z");
    TH1D* h1_denom_efficiency_jt = (TH1D*) file_eff->Get("denom_efficiency_jt");
    TH1D* h1_denom_efficiency_r = (TH1D*) file_eff->Get("denom_efficiency_r");
    TH2D* h2_denom_efficiency_ptz = (TH2D*) file_eff->Get("denom_efficiency_ptz");
    TH2D* h2_denom_efficiency_ptjt = (TH2D*) file_eff->Get("denom_efficiency_ptjt");
    TH2D* h2_denom_efficiency_ptr = (TH2D*) file_eff->Get("denom_efficiency_ptr");
    
  TH1D* h1_jetpt_MCtruth = (TH1D*) file_eff->Get("jetpt_truth");
  TH1D* h1_z_MCtruth = (TH1D*) file_eff->Get("z_truth");
  TH1D* h1_jt_MCtruth = (TH1D*) file_eff->Get("jt_truth");
  TH1D* h1_r_MCtruth = (TH1D*) file_eff->Get("r_truth");

    TFile *file_eff1 = new TFile(extension_RootFilesMC + extension_eff2 + TString(".root"), "READ");
    
    TH1D* h1_z_MCtruth_12515 = (TH1D*) file_eff1->Get("z_truth_12515");
    TH1D* h1_jt_MCtruth_12515 = (TH1D*) file_eff1->Get("jt_truth_12515");
    TH1D* h1_r_MCtruth_12515 = (TH1D*) file_eff1->Get("r_truth_12515");
    
    TH1D* h1_z_MCtruth_1520 = (TH1D*) file_eff1->Get("z_truth_1520");
    TH1D* h1_jt_MCtruth_1520 = (TH1D*) file_eff1->Get("jt_truth_1520");
    TH1D* h1_r_MCtruth_1520 = (TH1D*) file_eff1->Get("r_truth_1520");
    
    TH1D* h1_z_MCtruth_2030 = (TH1D*) file_eff1->Get("z_truth_2030");
    TH1D* h1_jt_MCtruth_2030 = (TH1D*) file_eff1->Get("jt_truth_2030");
    TH1D* h1_r_MCtruth_2030 = (TH1D*) file_eff1->Get("r_truth_2030");
    
    TH1D* h1_z_MCtruth_3050 = (TH1D*) file_eff1->Get("z_truth_3050");
    TH1D* h1_jt_MCtruth_3050 = (TH1D*) file_eff1->Get("jt_truth_3050");
    TH1D* h1_r_MCtruth_3050 = (TH1D*) file_eff1->Get("r_truth_3050");
    
    TH1D* h1_z_MCtruth_50100 = (TH1D*) file_eff1->Get("z_truth_50100");
    TH1D* h1_jt_MCtruth_50100 = (TH1D*) file_eff1->Get("jt_truth_50100");
    TH1D* h1_r_MCtruth_50100 = (TH1D*) file_eff1->Get("r_truth_50100");
    
    TH1D* h1_z_MCtruth_100150 = (TH1D*) file_eff1->Get("z_truth_100150");
    TH1D* h1_jt_MCtruth_100150 = (TH1D*) file_eff1->Get("jt_truth_100150");
    TH1D* h1_r_MCtruth_100150 = (TH1D*) file_eff1->Get("r_truth_100150");
    
    TFile *file_reco_MD = new TFile(extension_RootFilesMC + extension_reco_MD + TString(".root"), "READ");

    TH1D* h1_z_12515 = (TH1D*) file_reco_MD->Get("h1_z_12515");
    TH1D* h1_jt_12515 = (TH1D*) file_reco_MD->Get("h1_jt_12515");
    TH1D* h1_r_12515 = (TH1D*) file_reco_MD->Get("h1_r_12515");
    
    TH1D* h1_z_1520 = (TH1D*) file_reco_MD->Get("h1_z_1520");
    TH1D* h1_jt_1520 = (TH1D*) file_reco_MD->Get("h1_jt_1520");
    TH1D* h1_r_1520 = (TH1D*) file_reco_MD->Get("h1_r_1520");
    
    TH1D* h1_z_2030 = (TH1D*) file_reco_MD->Get("h1_z_2030");
    TH1D* h1_jt_2030 = (TH1D*) file_reco_MD->Get("h1_jt_2030");
    TH1D* h1_r_2030 = (TH1D*) file_reco_MD->Get("h1_r_2030");
    
    TH1D* h1_z_3050 = (TH1D*) file_reco_MD->Get("h1_z_3050");
    TH1D* h1_jt_3050 = (TH1D*) file_reco_MD->Get("h1_jt_3050");
    TH1D* h1_r_3050 = (TH1D*) file_reco_MD->Get("h1_r_3050");
    
    TH1D* h1_z_50100 = (TH1D*) file_reco_MD->Get("h1_z_50100");
    TH1D* h1_jt_50100 = (TH1D*) file_reco_MD->Get("h1_jt_50100");
    TH1D* h1_r_50100 = (TH1D*) file_reco_MD->Get("h1_r_50100");
    
    TH1D* h1_z_100150 = (TH1D*) file_reco_MD->Get("h1_z_100150");
    TH1D* h1_jt_100150 = (TH1D*) file_reco_MD->Get("h1_jt_100150");
    TH1D* h1_r_100150 = (TH1D*) file_reco_MD->Get("h1_r_100150");
    
    
    TH2D* h2_denom_purity_ptz_MD = (TH2D*) file_reco_MD->Get("h2_denom_purity_ptz_MD");
    TH2D* h2_denom_purity_ptjt_MD  = (TH2D*) file_reco_MD->Get("h2_denom_purity_ptjt_MD");
    TH2D* h2_denom_purity_ptr_MD  = (TH2D*) file_reco_MD->Get("h2_denom_purity_ptr_MD");
    
  TFile *f = TFile::Open(extension_RootFilesMC + extension + ".root", "RECREATE");

  TH2D *h2_truthreco_jetpt = new TH2D("truthreco_jetpt", "", longptbinsize, longpt_binedges, longptbinsize, longpt_binedges);
  TH2D *h2_truthreco_z = new TH2D("truthreco_z", ";Reco z; Truth z", zbinsize, z_binedges, zbinsize, z_binedges);
  TH2D *h2_truthreco_jt = new TH2D("truthreco_jt", ";Reco jT; Truth jT", jtbinsize, jt_binedges, jtbinsize, jt_binedges);
  TH2D *h2_truthreco_r = new TH2D("truthreco_r", ";Reco r; Truth r", rbinsize, r_binedges, rbinsize, r_binedges);

  TH1D *h1_num_purity_jetpt = new TH1D("num_purity_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_denom_purity_jetpt = new TH1D("denom_purity_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_num_purity_HFpt = new TH1D("num_purity_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_denom_purity_HFpt = new TH1D("denom_purity_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_purity_HFpt15 = new TH1D("num_purity_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_denom_purity_HFpt15 = new TH1D("denom_purity_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_purity_eta = new TH1D("num_purity_eta", "", etabinsize, eta_binedges);
  TH1D *h1_denom_purity_eta = new TH1D("denom_purity_eta", "", etabinsize, eta_binedges);
    
  TH1D *h1_num_purity_z = new TH1D("num_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_denom_purity_z = new TH1D("denom_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_num_purity_jt = new TH1D("num_purity_jt", "", jtbinsize, jt_binedges);
  TH1D *h1_denom_purity_jt = new TH1D("denom_purity_jt", "", jtbinsize, jt_binedges);
  TH1D *h1_num_purity_r = new TH1D("num_purity_r", "", rbinsize, r_binedges);
  TH1D *h1_denom_purity_r = new TH1D("denom_purity_r", "", rbinsize, r_binedges);

  TH1D *h1_num_efficiency_HFpt = new TH1D("num_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_efficiency_HFpt15 = new TH1D("num_efficiency_HFpt15", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_num_efficiency_jetpt = new TH1D("num_efficiency_jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_num_efficiency_z = new TH1D("num_efficiency_z", "", zbinsize, z_binedges);
  TH1D *h1_num_efficiency_jt = new TH1D("num_efficiency_jt", "", jtbinsize, jt_binedges);
  TH1D *h1_num_efficiency_r = new TH1D("num_efficiency_r", "", rbinsize, r_binedges);
    
  TH2D *h2_num_efficiency_HFptjetpt = new TH2D("num_efficiency_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_num_purity_HFptjetpt = new TH2D("num_purity_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_denom_purity_HFptjetpt = new TH2D("denom_purity_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_num_purity_HFpteta = new TH2D("num_purity_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
  TH2D *h2_denom_purity_HFpteta = new TH2D("denom_purity_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
  TH2D *h2_denom_purity_jetpteta = new TH2D("denom_purity_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_num_purity_jetpteta = new TH2D("num_purity_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_num_efficiency_jetpteta = new TH2D("num_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    
  TH2D *h2_num_efficiency_ptz = new TH2D("num_efficiency_jetptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
    TH2D *h2_num_efficiency_ptjt = new TH2D("num_efficiency_jetptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_num_efficiency_ptr = new TH2D("num_efficiency_jetptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
  TH2D *h2_num_purity_ptz = new TH2D("num_purity_jetptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptz = new TH2D("denom_purity_jetptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  
    TH2D *h2_num_purity_ptjt = new TH2D("num_purity_jetptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_denom_purity_ptjt = new TH2D("denom_purity_jetptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);

    TH2D *h2_num_purity_ptr = new TH2D("num_purity_jetptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    TH2D *h2_denom_purity_ptr = new TH2D("denom_purity_jetptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    

  // TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
  // TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize_truth, pt_binedges_truth);
  // TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);

  TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize, pt_binedges);
    
    TH1D *h1_z = new TH1D("z", "", zbinsize, z_binedges);
    TH1D *h1_z_truth = new TH1D("z_truth", "", zbinsize, z_binedges);
    TH1D *h1_jt = new TH1D("jt", "", jtbinsize, jt_binedges);
    TH1D *h1_jt_truth = new TH1D("jt_truth", "", jtbinsize, jt_binedges);
    TH1D *h1_r = new TH1D("r", "", rbinsize, r_binedges);
    TH1D *h1_r_truth = new TH1D("r_truth", "", rbinsize, r_binedges);
   
//// Uncoment for Same or Both Polarities
    
//    TH1D *h1_z_12515 = new TH1D("z_12515", "", zbinsize, z_binedges);
//    TH1D *h1_jt_12515 = new TH1D("jt_12515", "", jtbinsize, jt_binedges);
//    TH1D *h1_r_12515 = new TH1D("r_12515", "", rbinsize, r_binedges);
//    
//    TH1D *h1_z_1520 = new TH1D("z_1520", "", zbinsize, z_binedges);
//    TH1D *h1_jt_1520 = new TH1D("jt_1520", "", jtbinsize, jt_binedges);
//    TH1D *h1_r_1520 = new TH1D("r_1520", "", rbinsize, r_binedges);
//    
//    TH1D *h1_z_2030 = new TH1D("z_2030", "", zbinsize, z_binedges);
//    TH1D *h1_jt_2030 = new TH1D("jt_2030", "", jtbinsize, jt_binedges);
//    TH1D *h1_r_2030 = new TH1D("r_2030", "", rbinsize, r_binedges);
//    
//    TH1D *h1_z_3050 = new TH1D("z_3050", "", zbinsize, z_binedges);
//    TH1D *h1_jt_3050 = new TH1D("jt_3050", "", jtbinsize, jt_binedges);
//    TH1D *h1_r_3050 = new TH1D("r_3050", "", rbinsize, r_binedges);
//    
//    TH1D *h1_z_50100 = new TH1D("z_50100", "", zbinsize, z_binedges);
//    TH1D *h1_jt_50100 = new TH1D("jt_50100", "", jtbinsize, jt_binedges);
//    TH1D *h1_r_50100 = new TH1D("r_50100", "", rbinsize, r_binedges);
//   
//    TH1D *h1_z_100150 = new TH1D("z_100150 ", "", zbinsize, z_binedges);
//    TH1D *h1_jt_100150  = new TH1D("jt_100150 ", "", jtbinsize, jt_binedges);
//    TH1D *h1_r_100150  = new TH1D("r_100150 ", "", rbinsize, r_binedges);
    
    
  TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);
  TH2D *h2_jetpteta = new TH2D("jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    
  TH2D *h2_ptz = new TH2D("ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_matchedptz = new TH2D("matchedptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptjt = new TH2D("ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_matchedptjt = new TH2D("matchedptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptr = new TH2D("ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    TH2D *h2_matchedptr = new TH2D("matchedptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, "response_jetpt");
  RooUnfoldResponse *response_z = new RooUnfoldResponse(h1_z, h1_z_truth, "response_z", ";Reco z; Truth z");
  RooUnfoldResponse *response_jt = new RooUnfoldResponse(h1_jt, h1_jt_truth, "response_jt", ";Reco jT; Truth jT");
  RooUnfoldResponse *response_r = new RooUnfoldResponse(h1_r, h1_r_truth, "response_r", ";Reco r; Truth r");
    
  RooUnfoldResponse *response_jeteta = new RooUnfoldResponse(h1_num_purity_eta, h1_num_purity_eta, "response_jeteta");
  RooUnfoldResponse *response_HFptjetpt = new RooUnfoldResponse(h2_denom_efficiency_HFptjetpt, h2_denom_efficiency_HFptjetpt, "response_HFptjetpt");
  RooUnfoldResponse *response_jetpteta = new RooUnfoldResponse(h2_jetpteta, h2_jetpteta, "response_jetpteta");
    
  RooUnfoldResponse *response_ptz = new RooUnfoldResponse(h2_ptz, h2_matchedptz, "response_ptz");
  RooUnfoldResponse *response_ptjt = new RooUnfoldResponse(h2_ptjt, h2_matchedptjt, "response_ptjt");
  RooUnfoldResponse *response_ptr = new RooUnfoldResponse(h2_ptr, h2_matchedptr, "response_ptr");

  //
  // Event loop
  //
  unsigned long long last_eventNum = 0;
  double last_jetpT = 0.;
  int event_counter = 0;

  cout << BTree->GetEntries() << endl;

  double jet_pt, HF_pt, jet_eta, tr_jet_pt, tr_jet_eta, tr_HF_pt, bmass_dtf;
  double HF_px, HF_py, HF_pz, HF_e;
  double z, jt, r;
  double tr_z, tr_jt, tr_r;
  double zg, jtg, rg;
    
  bool isTrueBjet, Hasbbbar;
  int NumBHads_tr;
  int eventNumber;

  BTree->SetBranchAddress("HF_px", &HF_px);
  BTree->SetBranchAddress("HF_py", &HF_py);
  BTree->SetBranchAddress("HF_pz", &HF_pz);
  BTree->SetBranchAddress("HF_e", &HF_e);
  BTree->SetBranchAddress("HF_pt", &HF_pt);

  BTree->SetBranchAddress("jet_pt", &jet_pt);
  BTree->SetBranchAddress("jet_eta", &jet_eta);
  BTree->SetBranchAddress("z", &z);
  BTree->SetBranchAddress("jt", &jt);
  BTree->SetBranchAddress("r", &r);

  BTree->SetBranchAddress("tr_jet_pt", &tr_jet_pt);
  BTree->SetBranchAddress("tr_HF_pt", &tr_HF_pt);
  BTree->SetBranchAddress("tr_jet_eta", &tr_jet_eta);

  BTree->SetBranchAddress("tr_z", &tr_z);
  BTree->SetBranchAddress("tr_jt", &tr_jt);
  BTree->SetBranchAddress("tr_r", &tr_r);
    
  BTree->SetBranchAddress("zg", &zg);
  BTree->SetBranchAddress("jtg", &jtg);
  BTree->SetBranchAddress("rg", &rg);
    
  BTree->SetBranchAddress("isTrueBjet", &isTrueBjet);
  BTree->SetBranchAddress("NumBHads_tr", &NumBHads_tr);
  BTree->SetBranchAddress("bmass_dtf", &bmass_dtf);
  BTree->SetBranchAddress("eventNumber", &eventNumber);
  BTree->SetBranchAddress("Hasbbbar", &Hasbbbar);

  int eventNum;
  cout << "Requested # of events: " << NumEvts << endl;

//  std::ofstream myfile;
//  myfile.open(Form("data/bjet_dataset_%d.csv", dataset));
//
//  myfile << "jet pt"
//         << ",";
//  myfile << "jet eta"
//         << ",";
//  // myfile << HF_pt << ",";
//  // myfile << HF_eta << ",";
//
//  myfile << "tr_jet_pt"
//         << ",";
//  myfile << "tr_jet_eta"
//         << "\n";
//  // myfile << tr_HF_pt << ",";
//  // myfile << tr_HF_eta << ",";
        
  int NumBjets = 0;
  int NumTrueBjets = 0;

  for (int ev = 0; ev < NumEvts; ev++)
  {
    BTree->GetEntry(ev);

    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;
    double MassMu = 5.27940;
    double MassSigma = 1.32479e-02;
    // double MassHigh = MassMu + 3 * MassSigma;
    // double MassLow = MassMu - 3 * MassSigma;
    double MassHigh = 5.31;
    double MassLow = 5.24;
    bool mass_cond = (bmass_dtf > MassLow && bmass_dtf < MassHigh);
      
    if (!mass_cond){
      continue;
    }
    
//    if (Hasbbbar){continue;}
      
    TLorentzVector HFmeson(HF_px, HF_py, HF_pz, HF_e);
    double HF_eta = HFmeson.Eta();
    // if(NumBHads_tr > 1) continue; // does not change much
    if(tr_jet_pt > 12.5 && isTrueBjet && jet_pt > 12.5 && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta < etaMax && jet_eta > etaMin)
      {
        h2_num_efficiency_HFptjetpt->Fill(HFmeson.Pt(), tr_jet_pt);
      } 
    if(tr_jet_pt > 12.5 && tr_jet_pt < 20. && isTrueBjet && jet_pt > 12.5 && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta > etaMin && jet_eta < etaMax)
      {
        h1_num_efficiency_HFpt15->Fill(HFmeson.Pt());
      } 

    if(tr_jet_pt > 12.5 && isTrueBjet && jet_pt > 12.5 && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta < etaMax && jet_eta > etaMin)
      {
        h1_num_efficiency_jetpt->Fill(tr_jet_pt);
        h1_num_efficiency_z->Fill(tr_z);
        h1_num_efficiency_jt->Fill(tr_jt);
        h1_num_efficiency_r->Fill(tr_r);
          
        h2_num_efficiency_ptz->Fill(tr_z, tr_jet_pt);
        h2_num_efficiency_ptjt->Fill(tr_jt, tr_jet_pt);
        h2_num_efficiency_ptr->Fill(tr_r, tr_jet_pt);
          
      }
      
    if(tr_jet_pt > 12.5 && isTrueBjet && jet_pt > 12.5)
      {
        h2_num_efficiency_jetpteta->Fill(tr_jet_pt, tr_jet_eta);
      } 

      //ptMin // ptMax
    if(tr_jet_pt > 12.5 && tr_jet_pt < 150. && isTrueBjet && jet_pt > 12.5 && tr_jet_eta < etaMax && tr_jet_eta > etaMin && jet_eta > etaMin && jet_eta < etaMax)
      {
        h1_num_efficiency_HFpt->Fill(HFmeson.Pt());
        // h1_num_efficiency_jetpt->Fill(tr_jet_pt);
      } 

    if (jet_pt > 12.5 && jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_denom_purity_jetpt->Fill(jet_pt); 
      h1_denom_purity_eta->Fill(jet_eta);
        h1_denom_purity_z->Fill(z);
        h1_denom_purity_jt->Fill(jt);
        h1_denom_purity_r->Fill(r);
        
        h2_denom_purity_ptz->Fill(z, jet_pt);
        h2_denom_purity_ptjt->Fill(jt, jet_pt);
        h2_denom_purity_ptr->Fill(r, jet_pt);
    }
      
    if (isTrueBjet && tr_jet_pt > 12.5 &&
        jet_pt > 12.5 &&
        jet_eta < etaMax && jet_eta > etaMin &&
        tr_jet_eta < etaMax && tr_jet_eta > etaMin)
    {
      h1_num_purity_jetpt->Fill(jet_pt);
      h1_num_purity_eta->Fill(jet_eta);
        h1_num_purity_z->Fill(z);
        h1_num_purity_jt->Fill(jt);
        h1_num_purity_r->Fill(r);
        
        h2_num_purity_ptz->Fill(z, jet_pt);
        h2_num_purity_ptjt->Fill(jt, jet_pt);
        h2_num_purity_ptr->Fill(r, jet_pt);
    }
    if(jet_pt > 12.5){
      h2_denom_purity_jetpteta->Fill(jet_pt, jet_eta);
    }
    if (isTrueBjet && tr_jet_pt > 12.5 &&
        jet_pt > 12.5)
    {
      h2_num_purity_jetpteta->Fill(jet_pt, jet_eta);
    }

    if (jet_pt > 12.5 && jet_pt < 20. && jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_denom_purity_HFpt15->Fill(HF_pt);
    }
    if (jet_pt > 12.5 && jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_denom_purity_HFpt->Fill(HF_pt);
      h2_denom_purity_HFpteta->Fill(HF_pt, HF_eta);
      NumBjets++;
    }
    if (jet_pt > 12.5 && jet_eta < etaMax && jet_eta > etaMin)
    {
      h2_denom_purity_HFptjetpt->Fill(HFmeson.Pt(), jet_pt);
    }

     if (isTrueBjet && tr_jet_pt > 12.5 &&
        jet_pt > 12.5 && jet_pt < 20.0 &&
        jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_num_purity_HFpt15->Fill(HF_pt);
    }
    if (isTrueBjet && tr_jet_pt > 12.5 &&
        jet_pt > 12.5 &&
        jet_eta < etaMax && jet_eta > etaMin)
    {
      h1_num_purity_HFpt->Fill(HF_pt);
      // h1_num_purity_HFeta->Fill(HF_eta);
      h2_num_purity_HFpteta->Fill(HF_pt, HF_eta);
      NumTrueBjets++;
    }
    if (isTrueBjet && tr_jet_pt > 12.5 &&
        jet_pt > 12.5 &&
        jet_eta < etaMax && jet_eta > etaMin &&
        tr_jet_eta < etaMax && tr_jet_eta > etaMin)
    {
      h2_num_purity_HFptjetpt->Fill(HFmeson.Pt(), jet_pt);
    }

    if (jet_pt < 12.5)
      continue;
    if (tr_jet_pt < 12.5)
      continue;
    if (!isTrueBjet)
      continue;

    response_jetpteta->Fill(jet_pt, jet_eta, tr_jet_pt, tr_jet_eta);

    if (jet_eta < etaMin || jet_eta > etaMax)
      continue;

    if (tr_jet_eta > etaMax || tr_jet_eta < etaMin)
      continue;

    response_jetpt->Fill(jet_pt, tr_jet_pt);
    response_jeteta->Fill(jet_eta, tr_jet_eta);
    response_z->Fill(z, tr_z);
    response_jt->Fill(jt, tr_jt);
    response_r->Fill(r, tr_r);
      
      
    response_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, HFmeson.Pt(), tr_jet_pt);
    
    response_ptz->Fill(z, jet_pt, tr_z, tr_jet_pt);
    response_ptjt->Fill(jt, jet_pt, tr_jt, tr_jet_pt);
    response_ptr->Fill(r, jet_pt, tr_r, tr_jet_pt);

    h1_jetpt->Fill(jet_pt);
      h1_z->Fill(z);
      h1_jt->Fill(jt);
      h1_r->Fill(r);
      
//////////////////// Below: Uncomment for same or both polarities
      
//      if (jet_pt > 12.5 && jet_pt < 15.0 ) {
//
//          h1_z_12515->Fill(z);
//          h1_jt_12515->Fill(jt);
//          h1_r_12515->Fill(r);
//      }
//
//      if (jet_pt > 15.0 && jet_pt < 20.0 ) {
//        
//          h1_z_1520->Fill(z);
//          h1_jt_1520->Fill(jt);
//          h1_r_1520->Fill(r);
//      }
//      
//      if (jet_pt > 20.0 && jet_pt < 30.0 ) {
//        
//          h1_z_2030->Fill(z);
//          h1_jt_2030->Fill(jt);
//          h1_r_2030->Fill(r);
//      }
//      
//      if (jet_pt > 30.0 && jet_pt < 50.0 ) {
//          
//          h1_z_3050->Fill(z);
//          h1_jt_3050->Fill(jt);
//          h1_r_3050->Fill(r);
//      }
//      
//      if (jet_pt > 50.0 && jet_pt < 100.0 ) {
//          h1_z_50100->Fill(z);
//          h1_jt_50100->Fill(jt);
//          h1_r_50100->Fill(r);
//      }
//      
//      if (jet_pt > 100.0 && jet_pt < 150.0 ) {
//          h1_z_100150->Fill(z);
//          h1_jt_100150->Fill(jt);
//          h1_r_100150->Fill(r);
//      }
      
    h1_jetpt_truth->Fill(tr_jet_pt);
    h2_truthreco_jetpt->Fill(jet_pt, tr_jet_pt);
    event_counter++;

    // cout<<"New Event: "<<endl;
    // cout<<"Filling eff"<<endl;

  }


  // RooUnfoldResponse * response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, h2_truthreco_jetpt, "response_jetpt");
  TH2 *h2_response_jetpt = response_jetpt->Hresponse();
    TH2 *h2_response_z = response_z->Hresponse();
    TH2 *h2_response_jt = response_jt->Hresponse();
    TH2 *h2_response_r = response_r->Hresponse();
    
    TH2 *h2_response_ptz= response_ptz->Hresponse();
    TH2 *h2_response_ptjt= response_ptjt->Hresponse();
    TH2 *h2_response_ptr= response_ptr->Hresponse();
 
  response_jetpt->Write("Roo_response_jetpt");
    response_z->Write("response_z");
    response_jt->Write("response_jt");
    response_r->Write("response_r");
    
  response_HFptjetpt->Write("Roo_response_HFptjetpt");
  response_jetpteta->Write("Roo_response_jetpteta");

  response_ptz->Write("Roo_response_ptz");
  response_ptjt->Write("Roo_response_ptjt");
  response_ptr->Write("Roo_response_ptr");
    
  TH1D *h1_purity_HFpt = (TH1D *)h1_num_purity_HFpt->Clone("h1_purity_HFpt");
  h1_purity_HFpt->Divide(h1_num_purity_HFpt, h1_denom_purity_HFpt, 1, 1, "B");

  TH1D *h1_purity_HFpt15 = (TH1D *)h1_num_purity_HFpt15->Clone("h1_purity_HFpt15");
  h1_purity_HFpt15->Divide(h1_num_purity_HFpt15, h1_denom_purity_HFpt15, 1, 1, "B");

  TH1D *h1_purity_jetpt = (TH1D *)h1_num_purity_jetpt->Clone("h1_purity_jetpt");
  h1_purity_jetpt->Divide(h1_num_purity_jetpt, h1_denom_purity_jetpt, 1, 1, "B");
    
  TH1D *h1_purity_jeteta = (TH1D *)h1_num_purity_eta->Clone("h1_purity_jeteta");
  h1_purity_jeteta->Divide(h1_num_purity_eta, h1_denom_purity_eta, 1, 1, "B");
    
    TH1D *h1_purity_z = (TH1D *)h1_num_purity_z->Clone("h1_purity_z");
    h1_purity_z->Divide(h1_num_purity_z, h1_denom_purity_z, 1, 1, "B");
    
    TH1D *h1_purity_jt = (TH1D *)h1_num_purity_jt->Clone("h1_purity_jt");
    h1_purity_jt->Divide(h1_num_purity_jt, h1_denom_purity_jt, 1, 1, "B");
    
    TH1D *h1_purity_r = (TH1D *)h1_num_purity_r->Clone("h1_purity_r");
    h1_purity_r->Divide(h1_num_purity_r, h1_denom_purity_r, 1, 1, "B");
    
  TH2D *h2_purity_HFpteta = (TH2D *)h2_num_purity_HFpteta->Clone("h2_purity_HFpteta");
  h2_purity_HFpteta->Divide(h2_num_purity_HFpteta, h2_denom_purity_HFpteta, 1, 1, "B");

  TH1D *h1_efficiency_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("h1_efficiency_HFpt");
  h1_efficiency_HFpt->Divide(h1_num_efficiency_HFpt, h1_denom_efficiency_HFpt, 1, 1, "B");

  TH1D *h1_efficiency_HFpt15 = (TH1D *)h1_num_efficiency_HFpt15->Clone("h1_efficiency_HFpt15");
  h1_efficiency_HFpt15->Divide(h1_num_efficiency_HFpt15, h1_denom_efficiency_HFpt15, 1, 1, "B");

  TH1D *h1_efficiency_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("h1_efficiency_jetpt");
  h1_efficiency_jetpt->Divide(h1_num_efficiency_jetpt, h1_denom_efficiency_jetpt, 1, 1, "B");
    
  TH1D *h1_efficiency_z = (TH1D *)h1_num_efficiency_z->Clone("h1_efficiency_z");
  h1_efficiency_z->Divide(h1_num_efficiency_z, h1_denom_efficiency_z, 1, 1, "B");
    
  TH1D *h1_efficiency_jt = (TH1D *)h1_num_efficiency_jt->Clone("h1_efficiency_jt");
  h1_efficiency_jt->Divide(h1_num_efficiency_jt, h1_denom_efficiency_jt, 1, 1, "B");
    
  TH1D *h1_efficiency_r = (TH1D *)h1_num_efficiency_r->Clone("h1_efficiency_r");
  h1_efficiency_r->Divide(h1_num_efficiency_r, h1_denom_efficiency_r, 1, 1, "B");

  TH2D *h2_efficiency_HFptjetpt = (TH2D *)h2_num_efficiency_HFptjetpt->Clone("h2_efficiency_HFptjetpt");
  h2_efficiency_HFptjetpt->Divide(h2_num_efficiency_HFptjetpt, h2_denom_efficiency_HFptjetpt, 1, 1, "B");

  TH2D *h2_purity_HFptjetpt = (TH2D *)h2_num_purity_HFptjetpt->Clone("h2_purity_HFptjetpt");
  h2_purity_HFptjetpt->Divide(h2_num_purity_HFptjetpt, h2_denom_purity_HFptjetpt, 1, 1, "B");

  TH2D *h2_efficiency_jetpteta = (TH2D *)h2_num_efficiency_jetpteta->Clone("h2_efficiency_jetpteta");
  h2_efficiency_jetpteta->Divide(h2_num_efficiency_jetpteta, h2_denom_efficiency_jetpteta, 1, 1, "B");

  TH2D *h2_purity_jetpteta = (TH2D *)h2_num_purity_jetpteta->Clone("h2_purity_jetpteta");
  h2_purity_jetpteta->Divide(h2_num_purity_jetpteta, h2_denom_purity_jetpteta, 1, 1, "B");
    
  //// Efficiencies and Purities for z, jt, r
  TH2D *h2_efficiency_ptz = (TH2D *)h2_num_efficiency_ptz->Clone("h2_efficiency_ptz");
  h2_efficiency_ptz->Divide(h2_num_efficiency_ptz, h2_denom_efficiency_ptz, 1, 1, "B");
    TH2D *h2_efficiency_ptjt = (TH2D *)h2_num_efficiency_ptjt->Clone("h2_efficiency_ptjt");
    h2_efficiency_ptjt->Divide(h2_num_efficiency_ptjt, h2_denom_efficiency_ptjt, 1, 1, "B");
    TH2D *h2_efficiency_ptr = (TH2D *)h2_num_efficiency_ptr->Clone("h2_efficiency_ptr");
    h2_efficiency_ptr->Divide(h2_num_efficiency_ptr, h2_denom_efficiency_ptr, 1, 1, "B");
    
  TH2D *h2_purity_ptz = (TH2D *)h2_num_purity_ptz->Clone("h2_purity_ptz");
  h2_purity_ptz->Divide(h2_num_purity_ptz, h2_denom_purity_ptz, 1, 1, "B");
    TH2D *h2_purity_ptjt = (TH2D *)h2_num_purity_ptjt->Clone("h2_purity_ptjt");
    h2_purity_ptjt->Divide(h2_num_purity_ptjt, h2_denom_purity_ptjt, 1, 1, "B");
    TH2D *h2_purity_ptr = (TH2D *)h2_num_purity_ptr->Clone("h2_purity_ptr");
    h2_purity_ptr->Divide(h2_num_purity_ptr, h2_denom_purity_ptr, 1, 1, "B");
    

  // TEfficiency * h1_purity_jetpt = new TEfficiency(*h1_num_purity_jetpt, *h1_denom_purity_jetpt);
  TEfficiency *h1_purity_eta = new TEfficiency(*h1_num_purity_eta, *h1_denom_purity_eta);
        
  h1_purity_jetpt->Write("purity_jetpt");
  h1_purity_HFpt->Write("purity_HFpt");
  h1_purity_HFpt15->Write("purity_HFpt15");
  h1_purity_eta->Write("purity_jeteta1");
  h1_purity_jeteta->Write("purity_jeteta2");
  h1_purity_z->Write("purity_z");
  h1_purity_jt->Write("purity_jt");
  h1_purity_r->Write("purity_r");
  h2_purity_HFpteta->Write("purity_HFpteta");
  h2_purity_HFptjetpt->Write("purity_HFptjetpt");
  h2_efficiency_jetpteta->Write("efficiency_jetpteta");
  h2_purity_jetpteta->Write("purity_jetpteta");

  h1_efficiency_jetpt->Write("efficiency_jetpt");
  h1_efficiency_z->Write("efficiency_z");
  h1_efficiency_jt->Write("efficiency_jt");
  h1_efficiency_r->Write("efficiency_r");
  h1_efficiency_HFpt->Write("efficiency_HFpt");
  h1_efficiency_HFpt15->Write("efficiency_HFpt15");
  h2_efficiency_HFptjetpt->Write("efficiency_HFptjetpt");
    
  h2_efficiency_ptz->Write("efficiency_ptz");
  h2_purity_ptz->Write("purity_ptz");
    h2_efficiency_ptjt->Write("efficiency_ptjt");
    h2_purity_ptjt->Write("purity_ptjt");
    h2_efficiency_ptr->Write("efficiency_ptr");
    h2_purity_ptr->Write("purity_ptr");

  /////////////////////////////////

//  TF1 *f_eff1 = new TF1("f_eff1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
//  TF1 *f_eff2 = new TF1("f_eff2", "[0]*tanh([1]*([3] - x))+[2]", 25, 100);
//  TF1 *f_eff15 = new TF1("f_eff15", "[0]*tanh([1]*([3] - x))+[2]", 2, 20);
//  f_eff1->SetParameters(0.2, 0.1, 0.2, 6.4);
//  f_eff15->SetParameters(0.2, 0.1, 0.2, 6.4);
//  f_eff2->SetParameters(0.2, 0.1, 0.2, 100);
//  f_eff2->SetParLimits(3, 80, 200);
////  h1_efficiency_HFpt->Fit("f_eff1", "E", "SAME", 2, 25);
////  h1_efficiency_HFpt15->Fit("f_eff15", "E", "SAME", 2, 25);
////  h1_efficiency_HFpt->Fit("f_eff2", "E", "SAME", 25, 100);
//
//  f_eff1->Write("f_eff1");
//  f_eff15->Write("f_eff15");
//  f_eff2->Write("f_eff2");
//
//  TF1 *f_pur1 = new TF1("f_pur1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
//  TF1 *f_pur15 = new TF1("f_pur15", "[0]*tanh([1]*(x-[3]))+[2]", 2, 20);
//  f_pur1->SetParameters(0.05, 0.4, 0.95, 16);
//  f_pur1->SetParLimits(0, 0.01, 0.1);
//  f_pur1->SetParLimits(2, 0.9, 0.99);
//
//  f_pur15->SetParameters(0.3, 0.4, 0.70, 16);
//  f_pur15->SetParLimits(0, 0.25, 0.35);
//  f_pur15->SetParLimits(2, 0.65, 0.75);

//  h1_purity_HFpt->Fit("f_pur1", "E", "SAME", 2, 100);
//  f_pur1->Write("f_pur");
//
//  h1_purity_HFpt15->Fit("f_pur15", "E", "SAME", 2, 20);
//  f_pur15->Write("f_pur15");
  cout << event_counter << " events processed: " << endl;


  /////////////////////////////////////////////////////

  TH2D* h2_HFptjetpt_true = (TH2D*) h2_denom_efficiency_HFptjetpt->Clone("h2_HFptjetpt_true");
  TH2D* h2_HFptjetpt_reco = (TH2D*) h2_denom_purity_HFptjetpt->Clone("h2_HFptjetpt_reco");
  h2_HFptjetpt_reco->Multiply(h2_purity_HFptjetpt);
  RooUnfoldBayes unfold_HFptjetpt(response_HFptjetpt, h2_HFptjetpt_reco, 4);
  h2_HFptjetpt_reco = (TH2D *)unfold_HFptjetpt.Hreco();
  h2_HFptjetpt_reco->Divide(h2_efficiency_HFptjetpt);
  TH2D* h2_HFptjetpt_corr = (TH2D*) h2_HFptjetpt_reco->Clone("h2_HFptjetpt_corr");
  h2_HFptjetpt_corr->Divide(h2_HFptjetpt_true);
  h2_HFptjetpt_corr->Write("h2_HFptjetpt_corr");
    
    cout<< "-----------------------------"<<endl;
    cout<< "| 2D Unfolding z with jet_pt |"<<endl;
    cout<< "-----------------------------"<<endl;
    
//////////// 2D unfolding z  and jet_pt
  TH2D* h2_zjetpt_true = (TH2D*) h2_denom_efficiency_ptz->Clone("h2_zjetpt_true"); // MU/MD
//  TH2D* h2_zjetpt_reco = (TH2D*) h2_denom_purity_ptz->Clone("h2_zjetpt_reco"); //MU/MD
    TH2D* h2_zjetpt_reco = (TH2D*) h2_denom_purity_ptz_MD->Clone("h2_zjetpt_reco"); //MU/MD
    h2_zjetpt_reco->Multiply(h2_purity_ptz);
    RooUnfoldBayes unfold_ptz(response_ptz, h2_zjetpt_reco, 4);
    h2_zjetpt_reco = (TH2D *)unfold_ptz.Hreco();
    h2_zjetpt_reco->Divide(h2_efficiency_ptz);
  TH2D* h2_zjetpt_corr = (TH2D*) h2_zjetpt_reco->Clone("h2_zjetpt_corr");
  h2_zjetpt_corr->Divide(h2_zjetpt_true );
  h2_zjetpt_corr->Write("h2_zjetpt_corr");
    
    cout<< "-----------------------------"<<endl;
    cout<< "| 2D Unfolding jt with jet_pt |"<<endl;
    cout<< "-----------------------------"<<endl;

    
    //////////// 2D unfolding jt  and jet_pt
    TH2D* h2_jtjetpt_true = (TH2D*) h2_denom_efficiency_ptjt->Clone("h2_jtjetpt_true");
//    TH2D* h2_jtjetpt_reco = (TH2D*) h2_denom_purity_ptjt->Clone("h2_jtjetpt_reco");
    TH2D* h2_jtjetpt_reco = (TH2D*) h2_denom_purity_ptjt_MD->Clone("h2_jtjetpt_reco_MD");
    h2_jtjetpt_reco->Multiply(h2_purity_ptjt);
    RooUnfoldBayes unfold_ptjt(response_ptjt, h2_jtjetpt_reco, 4);
    h2_jtjetpt_reco = (TH2D *)unfold_ptjt.Hreco();
    h2_jtjetpt_reco->Divide(h2_efficiency_ptjt);
    TH2D* h2_jtjetpt_corr = (TH2D*) h2_jtjetpt_reco->Clone("h2_jtjetpt_corr");
    h2_jtjetpt_corr->Divide(h2_jtjetpt_true );
    h2_jtjetpt_corr->Write("h2_jtjetpt_corr");
    
    cout<< "-----------------------------"<<endl;
    cout<< "| 2D Unfolding r with jet_pt |"<<endl;
    cout<< "-----------------------------"<<endl;

    //////////// 2D unfolding  r  and jet_pt
    TH2D* h2_rjetpt_true = (TH2D*) h2_denom_efficiency_ptr->Clone("h2_rjetpt_true");
//    TH2D* h2_rjetpt_reco = (TH2D*) h2_denom_purity_ptr->Clone("h2_rjetpt_reco");
    TH2D* h2_rjetpt_reco = (TH2D*) h2_denom_purity_ptr_MD->Clone("h2_rjetpt_reco)MD");
    h2_rjetpt_reco->Multiply(h2_purity_ptr);
    RooUnfoldBayes unfold_ptr(response_ptr, h2_rjetpt_reco, 4);
    h2_rjetpt_reco = (TH2D *)unfold_ptr.Hreco();
    h2_rjetpt_reco->Divide(h2_efficiency_ptr);
    TH2D* h2_rjetpt_corr = (TH2D*) h2_rjetpt_reco->Clone("h2_rjetpt_corr");
    h2_rjetpt_corr->Divide(h2_rjetpt_true );
    h2_rjetpt_corr->Write("h2_rjetpt_corr");
    
    
  
  ////////////////////////////////////////////////////
    // Jet Unfolding
    cout<< "-----------------------------"<<endl;
    cout<< "   | 1D Unfolding jet_pt |   "<<endl;
    cout<< "-----------------------------"<<endl;
   
    TH1D* h1_jetpt_reco = (TH1D*) h1_jetpt->Clone("h1_jetpt_reco");

    h1_jetpt_reco->Multiply(h1_purity_jetpt);
    RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_reco, 4);
    h1_jetpt_reco = (TH1D *)unfold_jetpt.Hreco();
    h1_jetpt_reco->Divide(h1_efficiency_jetpt);
    TH1D* h1_jetpt_corr = (TH1D*) h1_jetpt_reco->Clone("h1_jetpt_corr");

    // z Unfolding
   
    TH1D* h1_z_reco = (TH1D*) h1_z->Clone("h1_z_reco");

    h1_z_reco->Multiply(h1_purity_z);
    RooUnfoldBayes unfold_z(response_z, h1_z_reco, 4);
    h1_z_reco = (TH1D *)unfold_z.Hreco();
    h1_z_reco->Divide(h1_efficiency_z);
    TH1D* h1_z_corr = (TH1D*) h1_z_reco->Clone("h1_z_corr");
    
    // Jt Unfolding
   
    TH1D* h1_jt_reco = (TH1D*) h1_jt->Clone("h1_jt_reco");

    h1_jt_reco->Multiply(h1_purity_jt);
    RooUnfoldBayes unfold_jt(response_jt, h1_jt_reco, 4);
    h1_jt_reco = (TH1D *)unfold_jt.Hreco();
    h1_jt_reco->Divide(h1_efficiency_jt);
    TH1D* h1_jt_corr = (TH1D*) h1_jt_reco->Clone("h1_jt_corr");
    
    // r Unfolding
   
    TH1D* h1_r_reco = (TH1D*) h1_r->Clone("h1_r_reco");

    h1_r_reco->Multiply(h1_purity_r);
    RooUnfoldBayes unfold_r(response_r, h1_r_reco, 4);
    h1_r_reco = (TH1D *)unfold_r.Hreco();
    h1_r_reco->Divide(h1_efficiency_r);
    TH1D* h1_r_corr = (TH1D*) h1_r_reco->Clone("h1_r_corr");

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
  Double_t lhcbWidth = 2.00; // Old LHCb style: 3.00;
  // Text size
  Double_t lhcbTSize = 0.06;
    Double_t lhcbTSize1    = 0.02;
    Double_t lhcbTSize2    = 0.04;
    /// The one that I use [integrated observables] ///
   TLatex *lhcbLatex = new TLatex();
   lhcbLatex->SetTextFont(lhcbFont);
   lhcbLatex->SetTextColor(1);
   lhcbLatex->SetTextSize(lhcbTSize);
   lhcbLatex->SetTextAlign(12);
    
   TLatex *lhcbLatex1 = new TLatex();
    lhcbLatex1->SetTextFont(lhcbFont);
    lhcbLatex1->SetTextColor(1);
    lhcbLatex1->SetTextSize(lhcbTSize1);
    lhcbLatex1->SetTextAlign(12);
    
    TLatex *lhcbLatex2 = new TLatex();
    lhcbLatex2->SetTextFont(lhcbFont);
    lhcbLatex2->SetTextColor(1);
    lhcbLatex2->SetTextSize(lhcbTSize1);
    lhcbLatex2->SetTextAlign(12);
    lhcbLatex2->SetTextAngle(90);

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
        
  TString plotextension = TString("/Users/josearias18/Desktop/QCDc2/pythia/Plots/BjetsMC/");
  rootfile = extension_RootFilesMC + extension + TString(".root");
  plotfile = plotextension + extension + TString(".ps");
  // TString OutputFileBase	= outbase+outinfo;
        
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
  
  ccan[ican]->Divide(2, 2);
  ccan[ican]->cd(1);
  h2_response_jetpt->SetStats(0);
  gPad->SetLogz();
  h2_response_jetpt->Draw("COLZ");

//  ccan[ican]->cd(2);
//  NormalizeHist(h1_jetpt);
//  h1_jetpt->Draw("same");
//
//  NormalizeHist(h1_jetpt_truth);
//  h1_jetpt_truth->SetLineColor(kGreen);
//  h1_jetpt_truth->Draw("same");
//
//  ccan[ican]->cd();
//  ccan[ican]->Update();
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
  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 1);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 4);
  ccan[ican]->cd(1);

  h1_purity_jetpt->SetMarkerColor(kRed);
  h1_purity_jetpt->SetMarkerStyle(21);
  h1_purity_jetpt->Draw("P E same");
  h1_purity_jetpt->SetTitle("; Jet pT; HF Jet Purity");
  h1_purity_jetpt->SetMinimum(0.);
  h1_purity_jetpt->SetMaximum(1.05);

  h1_efficiency_jetpt->SetMarkerColor(kBlue);
  h1_efficiency_jetpt->SetMarkerStyle(22);
  h1_efficiency_jetpt->Draw("P E same");
  h1_efficiency_jetpt->SetTitle("; Jet pT; HF Jet Efficiency");
  h1_efficiency_jetpt->SetMinimum(0.);
  h1_efficiency_jetpt->SetMaximum(1.0);
  // h1_purity_jetpt->SetXTitle("E_{radiator}");
  // h1_purity_jetpt->SetYTitle("Counts");
  // gPad->Update();
  // auto graphpt3 = h1_purity_jetpt->GetPaintedGraph();
  // graphpt3->SetMinimum(0);
  // graphpt3->SetMaximum(1);
  // gPad->Update();
  // h1_purity_jetpt->SetMinimum(0.0);
  ccan[ican]->cd(2);
    h1_purity_jeteta->SetMarkerColor(kRed);
    h1_purity_jeteta->SetMarkerStyle(21);
    h1_purity_jeteta->Draw("P E same");
    h1_purity_jeteta->SetTitle("; Jet #eta; HF Jet Purity");
    h1_purity_jeteta->SetMinimum(0.);
    h1_purity_jeteta->SetMaximum(1.05);

  ccan[ican]->cd(3);

  h1_purity_HFpt->SetMarkerColor(kRed);
  h1_purity_HFpt->SetMarkerStyle(21);
  h1_purity_HFpt->Draw("P E same");
//  h1_purity_HFpt->SetTitle("; HF pT; Purity or Efficiency");
  h1_purity_HFpt->SetTitle("; HF pT; Purity");
  h1_purity_HFpt->SetMinimum(0.);
  h1_purity_HFpt->SetMaximum(1.05);

  h1_purity_HFpt15->SetMarkerColor(kGreen);
  h1_purity_HFpt15->SetMarkerStyle(21);
  h1_purity_HFpt15->Draw("P E same");
  h1_purity_HFpt15->SetTitle("; HF pT (pT < 15 GeV/c); Purity ");

  h1_efficiency_HFpt->SetMarkerColor(kBlue);
  h1_efficiency_HFpt->SetMarkerStyle(22);
  h1_efficiency_HFpt->Draw("P E same");
  h1_efficiency_HFpt->SetTitle("; HF pT; Efficiency");
  h1_efficiency_HFpt->SetMinimum(0.);
  h1_efficiency_HFpt->SetMaximum(1.05);
  
  h1_efficiency_HFpt15->SetMarkerColor(kMagenta);
  h1_efficiency_HFpt15->SetMarkerStyle(22);
  h1_efficiency_HFpt15->Draw("P E same");
  h1_efficiency_HFpt15->SetTitle("; HF pT (pT < 15 GeV/c); Efficiency");
  h1_efficiency_HFpt15->SetMinimum(0.0);
  h1_efficiency_HFpt15->SetMaximum(1.05);

//  f_pur1->Draw("SAME");
//  f_pur15->Draw("SAME");
//  f_eff1->Draw("SAME");
//  f_eff15->Draw("SAME");

  ccan[ican]->cd(4);

  h2_efficiency_HFptjetpt->Draw("COLZ TEXT");
  // h2_efficiency_HFptjetpt->SetMinimum(0.);
  // h2_efficiency_HFptjetpt->SetMaximum(1.0);

  ccan[ican]->cd(5);

  h2_HFptjetpt_corr->Draw("COLZ TEXT");

  // h2_purity_HFpteta->Draw("COLZ");
  // h2_purity_HFpteta->SetTitle("; HF p_{T}; HF #eta; HF Jet Purity");
  // h2_purity_HFpteta->SetMinimum(0.);
  // h2_efficiency_HFpteta->SetMaximum(1.);

  ccan[ican]->cd(6);
  for(int i = 0; i < customptbinsize; i++){
    TH1D* h1_temp = (TH1D*) h2_efficiency_HFptjetpt->ProjectionX(Form("htemp%d", i), i+1, i+1);
    TH1D* h1_temp_pur = (TH1D*) h2_purity_HFptjetpt->ProjectionX(Form("htemp_pur%d", i), i+1, i+1);

    h1_temp_pur->SetMarkerStyle(i+20);
    h1_temp_pur->SetMarkerColor(i+1);
    h1_temp_pur->SetLineColor(i+1);
    h1_temp_pur->Draw("P E SAME");
    h1_temp_pur->SetMinimum(0.);
    h1_temp_pur->SetMaximum(1.05);
    h1_temp_pur->SetTitle("; HF pT; Purity (X Projection)");

    h1_temp->SetMarkerStyle(i+20);
    h1_temp->SetMarkerColor(i+1);
    h1_temp->SetLineColor(i+1);
    h1_temp->Draw("P E SAME");
    h1_temp->SetTitle("; HF pT; Efficiency (X Projection)");
      
  }
    ccan[ican]->cd(7);
    h1_purity_eta->SetMarkerColor(kRed);
    h1_purity_eta->SetMarkerStyle(21);
    h1_purity_eta->Draw("AP same");
    h1_purity_eta->SetTitle("; Jet #eta; HF Jet Purity");
    // h1_purity_eta->SetXTitle("E_{radiator}");
    // h1_purity_eta->SetYTitle("Counts");
    
    gPad->Update();
    auto grapheta4 = h1_purity_eta->GetPaintedGraph();
    grapheta4->SetMinimum(0);
    grapheta4->SetMaximum(1);
    grapheta4->SetTitle("; Jet #eta; HF Jet Purity");
    gPad->Update();

    ccan[ican]->cd(8);
    h1_purity_z->SetMarkerColor(kRed);
    h1_purity_z->SetMarkerStyle(21);
    h1_purity_z->Draw("P E same");
    h1_purity_z->SetTitle("; z ; HF Jet Purity");
    h1_purity_z->SetMinimum(0.);
    h1_purity_z->SetMaximum(1.05);

    ccan[ican]->cd(9);
    h1_purity_jt->SetMarkerColor(kRed);
    h1_purity_jt->SetMarkerStyle(21);
    h1_purity_jt->Draw("P E same");
    h1_purity_jt->SetTitle("; j_{T} [GeV] ; HF Jet Purity");
    h1_purity_jt->SetMinimum(0.);
    h1_purity_jt->SetMaximum(1.05);
    
    ccan[ican]->cd(10);
    h1_purity_r->SetMarkerColor(kRed);
    h1_purity_r->SetMarkerStyle(21);
    h1_purity_r->Draw("P E same");
    h1_purity_r->SetTitle("; r ; HF Jet Purity");
    h1_purity_r->SetMinimum(0.);
    h1_purity_r->SetMaximum(1.05);
    
    ccan[ican]->cd(11);
    h1_efficiency_z->SetMarkerColor(kBlue);
    h1_efficiency_z->SetMarkerStyle(21);
    h1_efficiency_z->Draw("P E same");
    h1_efficiency_z->SetTitle("; z ; HF Jet Reco. Efficiency");
    h1_efficiency_z->SetMinimum(0.);
    h1_efficiency_z->SetMaximum(1.05);
    
    ccan[ican]->cd(12);
    h1_efficiency_jt->SetMarkerColor(kBlue);
    h1_efficiency_jt->SetMarkerStyle(21);
    h1_efficiency_jt->Draw("P E same");
    h1_efficiency_jt->SetTitle("; j_{T} [GeV] ; HF Jet Reco. Efficiency");
    h1_efficiency_jt->SetMinimum(0.);
    h1_efficiency_jt->SetMaximum(1.05);
    
    ccan[ican]->cd(13);
    h1_efficiency_r->SetMarkerColor(kBlue);
    h1_efficiency_r->SetMarkerStyle(21);
    h1_efficiency_r->Draw("P E same");
    h1_efficiency_r->SetTitle("; r ; HF Jet Reco. Efficiency");
    h1_efficiency_r->SetMinimum(0.);
    h1_efficiency_r->SetMaximum(1.05);
    
    
  ccan[ican]->cd();
  ccan[ican]->Update();
    
    auto* c6 = new TCanvas();
    
//        NormalizeHist(h1_jetpt_MCtruth);
        h1_jetpt_MCtruth->SetLineColor(kGreen);
    //    h1_jetpt_truth->SetLineColor(kGreen);
        gPad->SetLogy();
        h1_jetpt_MCtruth->Draw("P E same");
    //    h1_jetpt_truth->GetXaxis()->SetRangeUser(10.0, 150.);
    
//    NormalizeHist(h1_jetpt);
    h1_jetpt->SetLineColor(kBlue);
    gPad->SetLogy();
    h1_jetpt->Draw("P E same");
//    h1_jetpt->GetXaxis()->SetRangeUser(10.0, 150.);

//    NormalizeHist(h1_jetpt_corr);
    h1_jetpt_corr->SetLineColor(kRed);
    gPad->SetLogy();
    h1_jetpt_corr->Draw("P E same");
    h1_jetpt_corr->GetXaxis()->SetRangeUser(5.0, 150.);
    gPad->Update();
    
    auto* leg6 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg6->SetTextFont(lhcbFont);
    leg6->SetBorderSize(0);
//    leg6->AddEntry(h1_jetpt_truth, "True ","LPE");
    leg6->AddEntry(h1_jetpt_MCtruth, "True ","LPE");
    leg6->AddEntry(h1_jetpt, "Measured ", "LPE");
    leg6->AddEntry(h1_jetpt_corr, "Unfolded ");
    leg6->Draw("same");
    c6->Draw();
    
    c6->SaveAs(plotextension + str_mag + "jetpt_unfold_log.pdf");
    
    
    auto* c10 = new TCanvas();
    
//    NormalizeHist(h1_r_MCtruth);
    TH1D *h1_2Dunfolded_z_12515 = (TH1D *)h2_zjetpt_reco->ProjectionX("hprojection", 1, 1);
    
    NormalizeHist(h1_z_MCtruth_12515);
    h1_z_MCtruth_12515->SetLineColor(kGreen);
    h1_z_MCtruth_12515->SetMarkerColor(kGreen);
    h1_z_MCtruth_12515->SetMarkerStyle(21);
    h1_z_MCtruth_12515->Draw("P E same");
    h1_z_MCtruth_12515->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_MCtruth_12515->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_MCtruth_12515->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_z_12515);
    h1_z_12515->SetLineColor(kBlue);
    h1_z_12515->SetMarkerColor(kBlue);
    h1_z_12515->SetMarkerStyle(21);
    h1_z_12515->Draw("P E same");
    h1_z_12515->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_12515->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_12515->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_2Dunfolded_z_12515);
    h1_2Dunfolded_z_12515->SetLineColor(kRed);
    h1_2Dunfolded_z_12515->SetMarkerColor(kRed);
    h1_2Dunfolded_z_12515->SetMarkerStyle(21);
    h1_2Dunfolded_z_12515->Draw("P E same");
    h1_2Dunfolded_z_12515->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_2Dunfolded_z_12515->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_2Dunfolded_z_12515->GetXaxis()->SetTitle("z");

    gPad->Update();
    lhcbLatex1->SetNDC();
 
    auto* leg10 = new TLegend(0.25, 0.6, 0.35, 0.75);
    leg10->SetTextFont(lhcbFont);
    leg10->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.25, 0.78, "12.5 < p_{T jet} < 15");
    
    if (isMagUp){
        leg10->AddEntry(h1_z_MCtruth_12515, "True MD ","LPE");
        leg10->AddEntry(h1_z_12515, "Measured MD ", "LPE");
        leg10->AddEntry(h1_2Dunfolded_z_12515, "Unfolded MD");
    }else{
        leg10->AddEntry(h1_z_MCtruth_12515, "True ","LPE");
        leg10->AddEntry(h1_z_12515, "Measured ", "LPE");
        leg10->AddEntry(h1_2Dunfolded_z_12515, "Unfolded ");
    }

    leg10->Draw("same");
    c10->Draw();
    c10->SaveAs(plotextension + str_mag + "z12515_2Dunfold.pdf");
    

    TCanvas* c11 =new TCanvas("c11","c11", 800, 800);
//    TPad *ptzpad = new TPad("ptzpad", "", 0.07, 0.07, 0.83, 0.83);
    TPad *ptzpad = new TPad("ptzpad", "", 0.0, 0.0, 1.0, 1.0);
    ptzpad->SetTopMargin(0.2); // Increase top margin if the text at the top is cut off
    ptzpad->SetBottomMargin(0.2); // Increase bottom margin for text at the bottom
    ptzpad->SetLeftMargin(0.2); // Adjust left margin
    ptzpad->SetRightMargin(0.25);
    
    ptzpad->Draw();
    ptzpad->cd();
    ptzpad->SetLogz();
    
    gStyle->SetPalette(kBird);
    gStyle->SetLabelSize(0.025, "Z");
    gStyle->SetLabelFont(lhcbFont, "Z");
    h2_response_ptz->GetXaxis()->SetLabelSize(0.025);
    h2_response_ptz->GetXaxis()->SetLabelFont(lhcbFont);
    h2_response_ptz->GetYaxis()->SetLabelSize(0.025);
    h2_response_ptz->GetYaxis()->SetLabelFont(lhcbFont);
    h2_response_ptz->SetTitle("");
    h2_response_ptz->Draw("COLZ");
    
    lhcbLatex2->SetNDC();
    lhcbLatex1->SetNDC();
    
    double y_ndc = 0.12;
    double x_ndc = 0.12;
    
    /// Y-axis
    lhcbLatex2->DrawLatex(0.15, 0.68, "z_{true} Bin Number");
    lhcbLatex2->DrawLatex(0.08, 0.45, "p_{T}^{jet, true} [GeV]");
    lhcbLatex2->DrawLatex(x_ndc, 0.22, "12.5 - 15");
    lhcbLatex2->DrawLatex(x_ndc, 0.33, "15 - 20");
    lhcbLatex2->DrawLatex(x_ndc, 0.41, "20 - 30");
    lhcbLatex2->DrawLatex(x_ndc, 0.52, "30 - 50");
    lhcbLatex2->DrawLatex(x_ndc, 0.63, "50 - 100");
    lhcbLatex2->DrawLatex(x_ndc, 0.73, "100 - 150");
    /// X-Axis
    lhcbLatex1->DrawLatex(0.65, 0.15, "z_{reco} Bin Number");
    lhcbLatex1->DrawLatex(0.40, 0.08, "p_{T}^{jet, reco} [GeV]");
    lhcbLatex1->DrawLatex(0.22, y_ndc, "12.5 - 15");
    lhcbLatex1->DrawLatex(0.33, y_ndc, "15 - 20");
    lhcbLatex1->DrawLatex(0.41, y_ndc, "20 - 30");
    lhcbLatex1->DrawLatex(0.49, y_ndc, "30 - 50");
    lhcbLatex1->DrawLatex(0.58, y_ndc, "50 - 100");
    lhcbLatex1->DrawLatex(0.68, y_ndc, "100 - 150");
    
    ptzpad->Modified();
    ptzpad->Update(); // Update the pad
    c11->Modified();
    c11->Update();
    c11->SaveAs(plotextension + str_mag + "ptz_ResponseMtx.pdf");
    
    TCanvas* c12 =new TCanvas("c12","c12", 800, 800);
//    TPad *ptzpad = new TPad("ptzpad", "", 0.07, 0.07, 0.83, 0.83);
    TPad *ptjtpad = new TPad("ptjtpad", "", 0.0, 0.0, 1.0, 1.0);
    ptjtpad->SetTopMargin(0.2); // Increase top margin if the text at the top is cut off
    ptjtpad->SetBottomMargin(0.2); // Increase bottom margin for text at the bottom
    ptjtpad->SetLeftMargin(0.2); // Adjust left margin
    ptjtpad->SetRightMargin(0.25);
    ptjtpad->Draw();
    ptjtpad->cd();
    ptjtpad->SetLogz();
    gStyle->SetPalette(kBird);
    gStyle->SetLabelSize(0.025, "Z");
    gStyle->SetLabelFont(lhcbFont, "Z");
    h2_response_ptjt->GetXaxis()->SetLabelSize(0.025);
    h2_response_ptjt->GetXaxis()->SetLabelFont(lhcbFont);
    h2_response_ptjt->GetYaxis()->SetLabelSize(0.025);
    h2_response_ptjt->GetYaxis()->SetLabelFont(lhcbFont);
    h2_response_ptjt->SetTitle("");
    h2_response_ptjt->Draw("COLZ");

    lhcbLatex2->SetNDC();
    lhcbLatex1->SetNDC();
    /// Y-axis
    lhcbLatex2->DrawLatex(0.15, 0.68, "j_{T true} Bin Number");
    lhcbLatex2->DrawLatex(0.08, 0.45, "p_{T}^{jet, true} [GeV]");
    lhcbLatex2->DrawLatex(x_ndc, 0.22, "12.5 - 15");
    lhcbLatex2->DrawLatex(x_ndc, 0.33, "15 - 20");
    lhcbLatex2->DrawLatex(x_ndc, 0.41, "20 - 30");
    lhcbLatex2->DrawLatex(x_ndc, 0.52, "30 - 50");
    lhcbLatex2->DrawLatex(x_ndc, 0.63, "50 - 100");
    lhcbLatex2->DrawLatex(x_ndc, 0.73, "100 - 150");
    /// X-Axis
    lhcbLatex1->DrawLatex(0.65, 0.15, "j_{T reco} Bin Number");
    lhcbLatex1->DrawLatex(0.40, 0.08, "p_{T}^{jet, reco} [GeV]");
    lhcbLatex1->DrawLatex(0.22, y_ndc, "12.5 - 15");
    lhcbLatex1->DrawLatex(0.33, y_ndc, "15 - 20");
    lhcbLatex1->DrawLatex(0.41, y_ndc, "20 - 30");
    lhcbLatex1->DrawLatex(0.49, y_ndc, "30 - 50");
    lhcbLatex1->DrawLatex(0.58, y_ndc, "50 - 100");
    lhcbLatex1->DrawLatex(0.68, y_ndc, "100 - 150");

    ptjtpad->Modified();
    ptjtpad->Update(); // Update the pad
    c12->Modified();
    c12->Update();
    c12->SaveAs(plotextension + str_mag + "ptj_ResponseMtx.pdf");

    TCanvas* c13 =new TCanvas("c13","c13", 800, 800);
//    TPad *ptzpad = new TPad("ptzpad", "", 0.07, 0.07, 0.83, 0.83);
    TPad *ptrpad = new TPad("ptrpad", "", 0.0, 0.0, 1.0, 1.0);
    ptrpad->SetTopMargin(0.2); // Increase top margin if the text at the top is cut off
    ptrpad->SetBottomMargin(0.2); // Increase bottom margin for text at the bottom
    ptrpad->SetLeftMargin(0.2); // Adjust left margin
    ptrpad->SetRightMargin(0.25);
    ptrpad->Draw();
    ptrpad->cd();
    ptrpad->SetLogz();
    
    gStyle->SetPalette(kBird);
    gStyle->SetLabelSize(0.025, "Z");
    gStyle->SetLabelFont(lhcbFont, "Z");
    h2_response_ptr->GetXaxis()->SetLabelSize(0.025);
    h2_response_ptr->GetXaxis()->SetLabelFont(lhcbFont);
    h2_response_ptr->GetYaxis()->SetLabelSize(0.025);
    h2_response_ptr->GetYaxis()->SetLabelFont(lhcbFont);
    h2_response_ptr->SetTitle("");
    h2_response_ptr->Draw("COLZ");
    lhcbLatex2->SetNDC();
    lhcbLatex1->SetNDC();
    
    /// Y-axis
    lhcbLatex2->DrawLatex(0.15, 0.68, "r_{true} Bin Number");
    lhcbLatex2->DrawLatex(0.08, 0.45, "p_{T}^{jet, true} [GeV]");
    lhcbLatex2->DrawLatex(x_ndc, 0.22, "12.5 - 15");
    lhcbLatex2->DrawLatex(x_ndc, 0.33, "15 - 20");
    lhcbLatex2->DrawLatex(x_ndc, 0.41, "20 - 30");
    lhcbLatex2->DrawLatex(x_ndc, 0.52, "30 - 50");
    lhcbLatex2->DrawLatex(x_ndc, 0.63, "50 - 100");
    lhcbLatex2->DrawLatex(x_ndc, 0.73, "100 - 150");
    /// X-Axis
    lhcbLatex1->DrawLatex(0.65, 0.15, "r_{reco} Bin Number");
    lhcbLatex1->DrawLatex(0.40, 0.08, "p_{T}^{jet, reco} [GeV]");
    lhcbLatex1->DrawLatex(0.22, y_ndc, "12.5 - 15");
    lhcbLatex1->DrawLatex(0.33, y_ndc, "15 - 20");
    lhcbLatex1->DrawLatex(0.41, y_ndc, "20 - 30");
    lhcbLatex1->DrawLatex(0.49, y_ndc, "30 - 50");
    lhcbLatex1->DrawLatex(0.58, y_ndc, "50 - 100");
    lhcbLatex1->DrawLatex(0.68, y_ndc, "100 - 150");

    ptrpad->Modified();
    ptrpad->Update(); // Update the pad
    c13->Modified();
    c13->Update();

    c13->SaveAs(plotextension + str_mag + "ptr_ResponseMtx.pdf");
    
    auto* c14 = new TCanvas();
    TH1D *h1_2Dunfolded_z_1520 = (TH1D *)h2_zjetpt_reco->ProjectionX("hprojection", 2, 2);
    
    NormalizeHist(h1_z_MCtruth_1520);
    h1_z_MCtruth_1520->SetLineColor(kGreen);
    h1_z_MCtruth_1520->SetMarkerColor(kGreen);
    h1_z_MCtruth_1520->SetMarkerStyle(21);
    h1_z_MCtruth_1520->Draw("P E same");
    h1_z_MCtruth_1520->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_MCtruth_1520->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_MCtruth_1520->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_z_1520);
    h1_z_1520->SetLineColor(kBlue);
    h1_z_1520->SetMarkerColor(kBlue);
    h1_z_1520->SetMarkerStyle(21);
    h1_z_1520->Draw("P E same");
    h1_z_1520->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_1520->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_1520->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_2Dunfolded_z_1520);
    h1_2Dunfolded_z_1520->SetLineColor(kRed);
    h1_2Dunfolded_z_1520->SetMarkerColor(kRed);
    h1_2Dunfolded_z_1520->SetMarkerStyle(21);
    h1_2Dunfolded_z_1520->Draw("P E same");
    h1_2Dunfolded_z_1520->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_2Dunfolded_z_1520->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_2Dunfolded_z_1520->GetXaxis()->SetTitle("z");

    gPad->Update();
    lhcbLatex1->SetNDC();
 
    auto* leg11 = new TLegend(0.25, 0.6, 0.35, 0.75);
    leg11->SetTextFont(lhcbFont);
    leg11->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.25, 0.78, "15 < p_{T jet} < 20");
    if (isMagUp){
        leg11->AddEntry(h1_z_MCtruth_1520, "True MD ","LPE");
        leg11->AddEntry(h1_z_1520, "Measured MD", "LPE");
        leg11->AddEntry(h1_2Dunfolded_z_1520, "Unfolded MD");
    }else{
        leg11->AddEntry(h1_z_MCtruth_1520, "True ","LPE");
        leg11->AddEntry(h1_z_1520, "Measured ", "LPE");
        leg11->AddEntry(h1_2Dunfolded_z_1520, "Unfolded ");
    }

    leg11->Draw("same");
    c14->Draw();
    c14->SaveAs(plotextension + str_mag + "z1520_2Dunfold.pdf");
    
    auto* c15 = new TCanvas();
    TH1D *h1_2Dunfolded_z_2030 = (TH1D *)h2_zjetpt_reco->ProjectionX("hprojection", 3, 3);
    
    NormalizeHist(h1_z_MCtruth_2030);
    h1_z_MCtruth_2030->SetLineColor(kGreen);
    h1_z_MCtruth_2030->SetMarkerColor(kGreen);
    h1_z_MCtruth_2030->SetMarkerStyle(21);
    h1_z_MCtruth_2030->Draw("P E same");
    h1_z_MCtruth_2030->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_MCtruth_2030->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_MCtruth_2030->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_z_2030);
    h1_z_2030->SetLineColor(kBlue);
    h1_z_2030->SetMarkerColor(kBlue);
    h1_z_2030->SetMarkerStyle(21);
    h1_z_2030->Draw("P E same");
    h1_z_2030->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_2030->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_2030->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_2Dunfolded_z_2030);
    h1_2Dunfolded_z_2030->SetLineColor(kRed);
    h1_2Dunfolded_z_2030->SetMarkerColor(kRed);
    h1_2Dunfolded_z_2030->SetMarkerStyle(21);
    h1_2Dunfolded_z_2030->Draw("P E same");
    h1_2Dunfolded_z_2030->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_2Dunfolded_z_2030->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_2Dunfolded_z_2030->GetXaxis()->SetTitle("z");

    gPad->Update();
    lhcbLatex1->SetNDC();
 
    auto* leg12 = new TLegend(0.25, 0.6, 0.35, 0.75);
    leg12->SetTextFont(lhcbFont);
    leg12->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.25, 0.78, "20 < p_{T jet} < 30");
    if (isMagUp){
        leg12->AddEntry(h1_z_MCtruth_2030, "True MD","LPE");
        leg12->AddEntry(h1_z_2030, "Measured MD", "LPE");
        leg12->AddEntry(h1_2Dunfolded_z_2030, "Unfolded MD");
    }else{
        leg12->AddEntry(h1_z_MCtruth_2030, "True ","LPE");
        leg12->AddEntry(h1_z_2030, "Measured ", "LPE");
        leg12->AddEntry(h1_2Dunfolded_z_2030, "Unfolded ");
    }


    leg12->Draw("same");
    c15->Draw();
    c15->SaveAs(plotextension + str_mag + "z2030_2Dunfold.pdf");
    
    auto* c16 = new TCanvas();
    TH1D *h1_2Dunfolded_z_3050 = (TH1D *)h2_zjetpt_reco->ProjectionX("hprojection", 4, 4);
    
    NormalizeHist(h1_z_MCtruth_3050);
    h1_z_MCtruth_3050->SetLineColor(kGreen);
    h1_z_MCtruth_3050->SetMarkerColor(kGreen);
    h1_z_MCtruth_3050->SetMarkerStyle(21);
    h1_z_MCtruth_3050->Draw("P E same");
    h1_z_MCtruth_3050->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_MCtruth_3050->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_MCtruth_3050->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_z_3050);
    h1_z_3050->SetLineColor(kBlue);
    h1_z_3050->SetMarkerColor(kBlue);
    h1_z_3050->SetMarkerStyle(21);
    h1_z_3050->Draw("P E same");
    h1_z_3050->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_3050->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_3050->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_2Dunfolded_z_3050);
    h1_2Dunfolded_z_3050->SetLineColor(kRed);
    h1_2Dunfolded_z_3050->SetMarkerColor(kRed);
    h1_2Dunfolded_z_3050->SetMarkerStyle(21);
    h1_2Dunfolded_z_3050->Draw("P E same");
    h1_2Dunfolded_z_3050->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_2Dunfolded_z_3050->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_2Dunfolded_z_3050->GetXaxis()->SetTitle("z");

    gPad->Update();
    lhcbLatex1->SetNDC();
 
    auto* leg13 = new TLegend(0.25, 0.6, 0.35, 0.75);
    leg13->SetTextFont(lhcbFont);
    leg13->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.25, 0.78, "30 < p_{T jet} < 50");
    if (isMagUp){
        leg13->AddEntry(h1_z_MCtruth_3050, "True MD","LPE");
        leg13->AddEntry(h1_z_3050, "Measured MD", "LPE");
        leg13->AddEntry(h1_2Dunfolded_z_3050, "Unfolded MD");
    }else{
        leg13->AddEntry(h1_z_MCtruth_3050, "True ","LPE");
        leg13->AddEntry(h1_z_3050, "Measured ", "LPE");
        leg13->AddEntry(h1_2Dunfolded_z_3050, "Unfolded ");
    }


    leg13->Draw("same");
    c16->Draw();
    c16->SaveAs(plotextension + str_mag + "z3050_2Dunfold.pdf");
    
    auto* c17 = new TCanvas();
    TH1D *h1_2Dunfolded_z_50100 = (TH1D *)h2_zjetpt_reco->ProjectionX("hprojection", 5, 5);
    
    NormalizeHist(h1_z_MCtruth_50100);
    h1_z_MCtruth_50100->SetLineColor(kGreen);
    h1_z_MCtruth_50100->SetMarkerColor(kGreen);
    h1_z_MCtruth_50100->SetMarkerStyle(21);
    h1_z_MCtruth_50100->Draw("P E same");
    h1_z_MCtruth_50100->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_MCtruth_50100->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_MCtruth_50100->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_z_50100);
    h1_z_50100->SetLineColor(kBlue);
    h1_z_50100->SetMarkerColor(kBlue);
    h1_z_50100->SetMarkerStyle(21);
    h1_z_50100->Draw("P E same");
    h1_z_50100->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_50100->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_50100->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_2Dunfolded_z_50100);
    h1_2Dunfolded_z_50100->SetLineColor(kRed);
    h1_2Dunfolded_z_50100->SetMarkerColor(kRed);
    h1_2Dunfolded_z_50100->SetMarkerStyle(21);
    h1_2Dunfolded_z_50100->Draw("P E same");
    h1_2Dunfolded_z_50100->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_2Dunfolded_z_50100->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_2Dunfolded_z_50100->GetXaxis()->SetTitle("z");

    gPad->Update();
    lhcbLatex1->SetNDC();
 
    auto* leg14 = new TLegend(0.25, 0.6, 0.35, 0.75);
    leg14->SetTextFont(lhcbFont);
    leg14->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.25, 0.78, "50 < p_{T jet} < 100");
    
    if (isMagUp){
        leg14->AddEntry(h1_z_MCtruth_50100, "True MD ","LPE");
        leg14->AddEntry(h1_z_50100, "Measured MD", "LPE");
        leg14->AddEntry(h1_2Dunfolded_z_50100, "Unfolded MD");
    }else{
        leg14->AddEntry(h1_z_MCtruth_50100, "True ","LPE");
        leg14->AddEntry(h1_z_50100, "Measured ", "LPE");
        leg14->AddEntry(h1_2Dunfolded_z_50100, "Unfolded ");
    }

    leg14->Draw("same");
    c17->Draw();
    
    c17->SaveAs(plotextension + str_mag + "z50100_2Dunfold.pdf");
    
    auto* c18 = new TCanvas();
    TH1D *h1_2Dunfolded_z_100150 = (TH1D *)h2_zjetpt_reco->ProjectionX("hprojection", 6, 6);
    
    NormalizeHist(h1_z_MCtruth_100150);
    h1_z_MCtruth_100150->SetLineColor(kGreen);
    h1_z_MCtruth_100150->SetMarkerColor(kGreen);
    h1_z_MCtruth_100150->SetMarkerStyle(21);
    h1_z_MCtruth_100150->Draw("P E same");
    h1_z_MCtruth_100150->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_MCtruth_100150->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_MCtruth_100150->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_z_100150);
    h1_z_100150->SetLineColor(kBlue);
    h1_z_100150->SetMarkerColor(kBlue);
    h1_z_100150->SetMarkerStyle(21);
    h1_z_100150->Draw("P E same");
    h1_z_100150->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_100150->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_100150->GetXaxis()->SetTitle("z");

    NormalizeHist(h1_2Dunfolded_z_100150);
    h1_2Dunfolded_z_100150->SetLineColor(kRed);
    h1_2Dunfolded_z_100150->SetMarkerColor(kRed);
    h1_2Dunfolded_z_100150->SetMarkerStyle(21);
    h1_2Dunfolded_z_100150->Draw("P E same");
    h1_2Dunfolded_z_100150->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_2Dunfolded_z_100150->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_2Dunfolded_z_100150->GetXaxis()->SetTitle("z");

    gPad->Update();
    lhcbLatex1->SetNDC();
 
    auto* leg15 = new TLegend(0.25, 0.6, 0.35, 0.75);
    leg15->SetTextFont(lhcbFont);
    leg15->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.25, 0.78, "100 < p_{T jet} < 150");
    
    if (isMagUp){
        leg15->AddEntry(h1_z_MCtruth_100150, "True MD","LPE");
        leg15->AddEntry(h1_z_100150, "Measured MD", "LPE");
        leg15->AddEntry(h1_2Dunfolded_z_100150, "Unfolded MD");
    }else{
        leg15->AddEntry(h1_z_MCtruth_100150, "True ","LPE");
        leg15->AddEntry(h1_z_100150, "Measured ", "LPE");
        leg15->AddEntry(h1_2Dunfolded_z_100150, "Unfolded ");
    }

    leg15->Draw("same");
    c18->Draw();
    c18->SaveAs(plotextension + str_mag + "z100150_2Dunfold.pdf");

    auto* c19 = new TCanvas();
    TH1D *h1_2Dunfolded_jt_1520 = (TH1D *)h2_jtjetpt_reco->ProjectionX("hprojection", 2, 2);
    
    c19->cd();
//
//    NormalizeHist(h1_jt_1520);
    h1_jt_1520->SetLineColor(kBlue);
    h1_jt_1520->SetMarkerColor(kBlue);
    h1_jt_1520->SetMarkerStyle(21);
//    gPad->SetLogy();
    h1_jt_1520->Draw("P E same");
    h1_jt_1520->GetXaxis()->SetRangeUser(0.0, 10);
//    h1_jt_1520->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_jt_1520->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    
    //        NormalizeHistScale(h1_jt_MCtruth_1520);
    h1_jt_MCtruth_1520->SetLineColor(kGreen);
    h1_jt_MCtruth_1520->SetMarkerColor(kGreen);
    h1_jt_MCtruth_1520->SetMarkerStyle(41);
    h1_jt_MCtruth_1520->SetMarkerSize(3);
//    gPad->SetLogy();
    h1_jt_MCtruth_1520->Draw("P E same");
    h1_jt_MCtruth_1520->GetXaxis()->SetRangeUser(0.0, 10);
//    h1_jt_MCtruth_1520->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_jt_MCtruth_1520->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();


//    NormalizeHist(h1_2Dunfolded_jt_1520);
    h1_2Dunfolded_jt_1520->SetLineColor(kRed);
    h1_2Dunfolded_jt_1520->SetMarkerColor(kRed);
    h1_2Dunfolded_jt_1520->SetMarkerStyle(21);
//    gPad->SetLogy();
    h1_2Dunfolded_jt_1520->Draw("P E same");
    h1_2Dunfolded_jt_1520->GetXaxis()->SetRangeUser(0.0, 10);
//    h1_2Dunfolded_jt_1520->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_2Dunfolded_jt_1520->GetXaxis()->SetTitle("j_{T} [GeV]");
    
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg16 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg16->SetTextFont(lhcbFont);
    leg16->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "15 < p_{T jet} < 20");
    if (isMagUp){
        leg16->AddEntry(h1_jt_MCtruth_1520, "True MD","LPE");
        leg16->AddEntry(h1_jt_1520, "Measured MD ", "LPE");
        leg16->AddEntry(h1_2Dunfolded_jt_1520, "Unfolded MD", "LPE");
    }else{
        leg16->AddEntry(h1_jt_MCtruth_1520, "True ","LPE");
        leg16->AddEntry(h1_jt_1520, "Measured ", "LPE");
        leg16->AddEntry(h1_2Dunfolded_jt_1520, "Unfolded ", "LPE");
    }

    leg16->Draw("same");
    gPad->Update();
    c19->Update();
    c19->Modified();
    c19->Draw();
    c19->SaveAs(plotextension + str_mag + "jt1520_2Dunfold_test.pdf");
    
    auto* c20 = new TCanvas();
    TH1D *h1_2Dunfolded_jt_12515 = (TH1D *)h2_jtjetpt_reco->ProjectionX("hprojection", 1, 1);
//    NormalizeHist(h1_jt_1520);
    h1_jt_12515->SetLineColor(kBlue);
    h1_jt_12515->SetMarkerColor(kBlue);
    h1_jt_12515->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_jt_12515->Draw("P E same");
    h1_jt_12515->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_12515->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_jt_12515->GetXaxis()->SetTitle("j_{T} [GeV]");
    
    //        NormalizeHistScale(h1_jt_MCtruth_1520);
    h1_jt_MCtruth_12515->SetLineColor(kGreen);
    h1_jt_MCtruth_12515->SetMarkerColor(kGreen);
    h1_jt_MCtruth_12515->SetMarkerStyle(41);
    h1_jt_MCtruth_12515->SetMarkerSize(3);
    gPad->SetLogy();
    h1_jt_MCtruth_12515->Draw("P E same");
    h1_jt_MCtruth_12515->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_MCtruth_12515->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_jt_MCtruth_12515->GetXaxis()->SetTitle("j_{T} [GeV]");

//    NormalizeHist(h1_2Dunfolded_jt_1520);
    h1_2Dunfolded_jt_12515->SetLineColor(kRed);
    h1_2Dunfolded_jt_12515->SetMarkerColor(kRed);
    h1_2Dunfolded_jt_12515->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_jt_12515->Draw("P E same");
    h1_2Dunfolded_jt_12515->GetXaxis()->SetRangeUser(0.0, 10);
    h1_2Dunfolded_jt_12515->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_2Dunfolded_jt_12515->GetXaxis()->SetTitle("j_{T} [GeV]");
    
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg17 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg17->SetTextFont(lhcbFont);
    leg17->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "12.5 < p_{T jet} < 15");
    
    if (isMagUp){
        leg17->AddEntry(h1_jt_MCtruth_12515, "True MD","LPE");
        leg17->AddEntry(h1_jt_12515, "Measured MD", "LPE");
        leg17->AddEntry(h1_2Dunfolded_jt_12515, "Unfolded MD ", "LPE");
    }else{
        leg17->AddEntry(h1_jt_MCtruth_12515, "True ","LPE");
        leg17->AddEntry(h1_jt_12515, "Measured ", "LPE");
        leg17->AddEntry(h1_2Dunfolded_jt_12515, "Unfolded ", "LPE");
    }

    leg17->Draw("same");
    c20->Draw();
    c20->SaveAs(plotextension + str_mag + "jt12515_2Dunfold.pdf");
    
    auto* c21 = new TCanvas();
    TH1D *h1_2Dunfolded_jt_2030 = (TH1D *)h2_jtjetpt_reco->ProjectionX("hprojection", 3, 3);
//    NormalizeHist(h1_jt_1520);
    h1_jt_2030->SetLineColor(kBlue);
    h1_jt_2030->SetMarkerColor(kBlue);
    h1_jt_2030->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_jt_2030->Draw("P E same");
    h1_jt_2030->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_2030->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_jt_2030->GetXaxis()->SetTitle("j_{T} [GeV]");
    
    //        NormalizeHistScale(h1_jt_MCtruth_1520);
    h1_jt_MCtruth_2030->SetLineColor(kGreen);
    h1_jt_MCtruth_2030->SetMarkerColor(kGreen);
    h1_jt_MCtruth_2030->SetMarkerStyle(41);
    h1_jt_MCtruth_2030->SetMarkerSize(3);
    gPad->SetLogy();
    h1_jt_MCtruth_2030->Draw("P E same");
    h1_jt_MCtruth_2030->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_MCtruth_2030->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_jt_MCtruth_2030->GetXaxis()->SetTitle("j_{T} [GeV]");

//    NormalizeHist(h1_2Dunfolded_jt_1520);
    h1_2Dunfolded_jt_2030->SetLineColor(kRed);
    h1_2Dunfolded_jt_2030->SetMarkerColor(kRed);
    h1_2Dunfolded_jt_2030->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_jt_2030->Draw("P E same");
    h1_2Dunfolded_jt_2030->GetXaxis()->SetRangeUser(0.0, 10);
    h1_2Dunfolded_jt_2030->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_2Dunfolded_jt_2030->GetXaxis()->SetTitle("j_{T} [GeV]");
    
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg18 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg18->SetTextFont(lhcbFont);
    leg18->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "20 < p_{T jet} < 30");
    if (isMagUp){
        leg18->AddEntry(h1_jt_MCtruth_2030, "True MD ","LPE");
        leg18->AddEntry(h1_jt_2030, "Measured MD", "LPE");
        leg18->AddEntry(h1_2Dunfolded_jt_2030, "Unfolded MD", "LPE");
    }else{
        leg18->AddEntry(h1_jt_MCtruth_2030, "True ","LPE");
        leg18->AddEntry(h1_jt_2030, "Measured ", "LPE");
        leg18->AddEntry(h1_2Dunfolded_jt_2030, "Unfolded ", "LPE");
    }
 
    leg18->Draw("same");
    c21->Draw();
    c21->SaveAs(plotextension + str_mag + "jt2030_2Dunfold.pdf");
    
    auto* c22 = new TCanvas();
    TH1D *h1_2Dunfolded_jt_3050 = (TH1D *)h2_jtjetpt_reco->ProjectionX("hprojection", 4, 4);
    c22->cd();
//    NormalizeHist(h1_jt_1520);
    h1_jt_3050->SetLineColor(kBlue);
    h1_jt_3050->SetMarkerColor(kBlue);
    h1_jt_3050->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_jt_3050->Draw("P E same");
    h1_jt_3050->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_3050->GetYaxis()->SetRangeUser(0.3, 100000);
    h1_jt_3050->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    //        NormalizeHistScale(h1_jt_MCtruth_3050);
    h1_jt_MCtruth_3050->SetLineColor(kGreen);
    h1_jt_MCtruth_3050->SetMarkerColor(kGreen);
    h1_jt_MCtruth_3050->SetMarkerStyle(41);
    h1_jt_MCtruth_3050->SetMarkerSize(3);
    gPad->SetLogy();
    h1_jt_MCtruth_3050->Draw("P E same");
    h1_jt_MCtruth_3050->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_MCtruth_3050->GetYaxis()->SetRangeUser(0.3, 100000);
    h1_jt_MCtruth_3050->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
//    NormalizeHist(h1_2Dunfolded_jt_3050);
    h1_2Dunfolded_jt_3050->SetLineColor(kRed);
    h1_2Dunfolded_jt_3050->SetMarkerColor(kRed);
    h1_2Dunfolded_jt_3050->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_jt_3050->Draw("P E same");
    h1_2Dunfolded_jt_3050->GetXaxis()->SetRangeUser(0.0, 10);
    h1_2Dunfolded_jt_3050->GetYaxis()->SetRangeUser(0.3, 100000);
    h1_2Dunfolded_jt_3050->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg19 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg19->SetTextFont(lhcbFont);
    leg19->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "30 < p_{T jet} < 50");
    if (isMagUp){
        leg19->AddEntry(h1_jt_MCtruth_3050, "True MD","LPE");
        leg19->AddEntry(h1_jt_3050, "Measured MD", "LPE");
        leg19->AddEntry(h1_2Dunfolded_jt_3050, "Unfolded MD", "LPE");
    }else{
        leg19->AddEntry(h1_jt_MCtruth_3050, "True ","LPE");
        leg19->AddEntry(h1_jt_3050, "Measured ", "LPE");
        leg19->AddEntry(h1_2Dunfolded_jt_3050, "Unfolded ", "LPE");
    }

    leg19->Draw("same");
    gPad->Update();
    c22->Update();
    c22->Modified();
    c22->Draw();
    c22->SaveAs(plotextension + str_mag + "jt3050_2Dunfold.pdf");
    
    auto* c23 = new TCanvas();
    TH1D *h1_2Dunfolded_jt_50100 = (TH1D *)h2_jtjetpt_reco->ProjectionX("hprojection", 5, 5);
    c23->cd();
//    NormalizeHist(h1_jt_1520);
    h1_jt_50100->SetLineColor(kBlue);
    h1_jt_50100->SetMarkerColor(kBlue);
    h1_jt_50100->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_jt_50100->Draw("P E same");
    h1_jt_50100->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_50100->GetYaxis()->SetRangeUser(0.001, 10000);
    h1_jt_50100->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    //        NormalizeHistScale(h1_jt_MCtruth_50100);
    h1_jt_MCtruth_50100->SetLineColor(kGreen);
    h1_jt_MCtruth_50100->SetMarkerColor(kGreen);
    h1_jt_MCtruth_50100->SetMarkerStyle(41);
    h1_jt_MCtruth_50100->SetMarkerSize(3);
    gPad->SetLogy();
    h1_jt_MCtruth_50100->Draw("P E same");
    h1_jt_MCtruth_50100->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_MCtruth_50100->GetYaxis()->SetRangeUser(0.001, 10000);
    h1_jt_MCtruth_50100->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
//    NormalizeHist(h1_2Dunfolded_jt_50100);
    h1_2Dunfolded_jt_50100->SetLineColor(kRed);
    h1_2Dunfolded_jt_50100->SetMarkerColor(kRed);
    h1_2Dunfolded_jt_50100->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_jt_50100->Draw("P E same");
    h1_2Dunfolded_jt_50100->GetXaxis()->SetRangeUser(0.0, 10);
    h1_2Dunfolded_jt_50100->GetYaxis()->SetRangeUser(0.001, 10000);
    h1_2Dunfolded_jt_50100->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg20 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg20->SetTextFont(lhcbFont);
    leg20->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "50 < p_{T jet} < 100");
    
    if (isMagUp){
        leg20->AddEntry(h1_jt_MCtruth_50100, "True MD ","LPE");
        leg20->AddEntry(h1_jt_50100, "Measured MD ", "LPE");
        leg20->AddEntry(h1_2Dunfolded_jt_50100, "Unfolded MD", "LPE");
    }else{
        leg20->AddEntry(h1_jt_MCtruth_50100, "True ","LPE");
        leg20->AddEntry(h1_jt_50100, "Measured ", "LPE");
        leg20->AddEntry(h1_2Dunfolded_jt_50100, "Unfolded ", "LPE");
    }
 
    leg20->Draw("same");
    gPad->Update();
    c23->Update();
    c23->Modified();
    c23->Draw();
    c23->SaveAs(plotextension + str_mag + "jt50100_2Dunfold.pdf");
    
    auto* c24 = new TCanvas();
    TH1D *h1_2Dunfolded_jt_100150 = (TH1D *)h2_jtjetpt_reco->ProjectionX("hprojection", 6, 6);
    c24->cd();
//    NormalizeHist(h1_jt_1520);
    h1_jt_100150->SetLineColor(kBlue);
    h1_jt_100150->SetMarkerColor(kBlue);
    h1_jt_100150->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_jt_100150->Draw("P E same");
    h1_jt_100150->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_100150->GetYaxis()->SetRangeUser(0.3, 100);
    h1_jt_100150->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    //        NormalizeHistScale(h1_jt_MCtruth_100150);
    h1_jt_MCtruth_100150->SetLineColor(kGreen);
    h1_jt_MCtruth_100150->SetMarkerColor(kGreen);
    h1_jt_MCtruth_100150->SetMarkerStyle(41);
    h1_jt_MCtruth_100150->SetMarkerSize(3);
    gPad->SetLogy();
    h1_jt_MCtruth_100150->Draw("P E same");
    h1_jt_MCtruth_100150->GetXaxis()->SetRangeUser(0.0, 10);
    h1_jt_MCtruth_100150->GetYaxis()->SetRangeUser(0.3, 100);
    h1_jt_MCtruth_100150->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
//    NormalizeHist(h1_2Dunfolded_jt_100150);
    h1_2Dunfolded_jt_100150->SetLineColor(kRed);
    h1_2Dunfolded_jt_100150->SetMarkerColor(kRed);
    h1_2Dunfolded_jt_100150->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_jt_100150->Draw("P E same");
    h1_2Dunfolded_jt_100150->GetXaxis()->SetRangeUser(0.0, 10);
    h1_2Dunfolded_jt_100150->GetYaxis()->SetRangeUser(0.3, 100);
    h1_2Dunfolded_jt_100150->GetXaxis()->SetTitle("j_{T} [GeV]");
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg21 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg21->SetTextFont(lhcbFont);
    leg21->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "100 < p_{T jet} < 150");
    if (isMagUp){
        leg21->AddEntry(h1_jt_MCtruth_100150, "True MD","LPE");
        leg21->AddEntry(h1_jt_100150, "Measured MD", "LPE");
        leg21->AddEntry(h1_2Dunfolded_jt_100150, "Unfolded MD", "LPE");
    }else{
        leg21->AddEntry(h1_jt_MCtruth_100150, "True ","LPE");
        leg21->AddEntry(h1_jt_100150, "Measured ", "LPE");
        leg21->AddEntry(h1_2Dunfolded_jt_100150, "Unfolded ", "LPE");
    }

    leg21->Draw("same");
    gPad->Update();
    c24->Update();
    c24->Modified();
    c24->Draw();
    c24->SaveAs(plotextension + str_mag + "jt100150_2Dunfold.pdf");
    
    auto* c25 = new TCanvas();
    TH1D *h1_2Dunfolded_r_2030 = (TH1D *)h2_rjetpt_reco->ProjectionX("hprojection", 3, 3);
    c25->cd();
//    NormalizeHist(h1_jt_1520);
    h1_r_2030->SetLineColor(kBlue);
    h1_r_2030->SetMarkerColor(kBlue);
    h1_r_2030->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_r_2030->Draw("P E same");
    h1_r_2030->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_r_2030->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_r_2030->GetXaxis()->SetTitle("r");
    gPad->Update();
    //        NormalizeHistScale(h1_jt_MCtruth_100150);
    h1_r_MCtruth_2030->SetLineColor(kGreen);
    h1_r_MCtruth_2030->SetMarkerColor(kGreen);
    h1_r_MCtruth_2030->SetMarkerStyle(41);
    h1_r_MCtruth_2030->SetMarkerSize(3);
    gPad->SetLogy();
    h1_r_MCtruth_2030->Draw("P E same");
    h1_r_MCtruth_2030->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_r_MCtruth_2030->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_r_MCtruth_2030->GetXaxis()->SetTitle("r");
    gPad->Update();
//    NormalizeHist(h1_2Dunfolded_r_2030);
    h1_2Dunfolded_r_2030->SetLineColor(kRed);
    h1_2Dunfolded_r_2030->SetMarkerColor(kRed);
    h1_2Dunfolded_r_2030->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_r_2030->Draw("P E same");
    h1_2Dunfolded_r_2030->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_2Dunfolded_r_2030->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_2Dunfolded_r_2030->GetXaxis()->SetTitle("r");
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg22 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg22->SetTextFont(lhcbFont);
    leg22->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "20 < p_{T jet} < 30");
    if (isMagUp){
        leg22->AddEntry(h1_r_MCtruth_2030, "True MD","LPE");
        leg22->AddEntry(h1_r_2030, "Measured MD", "LPE");
        leg22->AddEntry(h1_2Dunfolded_r_2030, "Unfolded MD", "LPE");
    }else{
        leg22->AddEntry(h1_r_MCtruth_2030, "True ","LPE");
        leg22->AddEntry(h1_r_2030, "Measured ", "LPE");
        leg22->AddEntry(h1_2Dunfolded_r_2030, "Unfolded ", "LPE");
    }

    leg22->Draw("same");
    gPad->Update();
    c25->Update();
    c25->Modified();
    c25->Draw();
    c25->SaveAs(plotextension + str_mag + "r2030_2Dunfold.pdf");

    auto* c26 = new TCanvas();
    TH1D *h1_2Dunfolded_r_3050 = (TH1D *)h2_rjetpt_reco->ProjectionX("hprojection", 4, 4);
    c26->cd();
//    NormalizeHist(h1_jt_1520);
    h1_r_3050->SetLineColor(kBlue);
    h1_r_3050->SetMarkerColor(kBlue);
    h1_r_3050->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_r_3050->Draw("P E same");
    h1_r_3050->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_r_3050->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_r_3050->GetXaxis()->SetTitle("r");
    gPad->Update();
    //        NormalizeHistScale(h1_jt_MCtruth_100150);
    h1_r_MCtruth_3050->SetLineColor(kGreen);
    h1_r_MCtruth_3050->SetMarkerColor(kGreen);
    h1_r_MCtruth_3050->SetMarkerStyle(41);
    h1_r_MCtruth_3050->SetMarkerSize(3);
    gPad->SetLogy();
    h1_r_MCtruth_3050->Draw("P E same");
    h1_r_MCtruth_3050->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_r_MCtruth_3050->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_r_MCtruth_3050->GetXaxis()->SetTitle("r");
    gPad->Update();
//    NormalizeHist(h1_2Dunfolded_r_3050);
    h1_2Dunfolded_r_3050->SetLineColor(kRed);
    h1_2Dunfolded_r_3050->SetMarkerColor(kRed);
    h1_2Dunfolded_r_3050->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_r_3050->Draw("P E same");
    h1_2Dunfolded_r_3050->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_2Dunfolded_r_3050->GetYaxis()->SetRangeUser(0.3, 1000000);
    h1_2Dunfolded_r_3050->GetXaxis()->SetTitle("r");
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg23 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg23->SetTextFont(lhcbFont);
    leg23->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "30 < p_{T jet} < 50");
    if (isMagUp){
        leg23->AddEntry(h1_r_MCtruth_3050, "True MD","LPE");
        leg23->AddEntry(h1_r_3050, "Measured MD", "LPE");
        leg23->AddEntry(h1_2Dunfolded_r_3050, "Unfolded MD", "LPE");
    }else{
        leg23->AddEntry(h1_r_MCtruth_3050, "True ","LPE");
        leg23->AddEntry(h1_r_3050, "Measured ", "LPE");
        leg23->AddEntry(h1_2Dunfolded_r_3050, "Unfolded ", "LPE");
    }

    leg23->Draw("same");
    gPad->Update();
    c26->Update();
    c26->Modified();
    c26->Draw();
    c26->SaveAs(plotextension + str_mag + "r3050_2Dunfold.pdf");

    auto* c27 = new TCanvas();
    TH1D *h1_2Dunfolded_r_50100 = (TH1D *)h2_rjetpt_reco->ProjectionX("hprojection", 5, 5);
    c27->cd();
//    NormalizeHist(h1_jt_1520);
    h1_r_50100->SetLineColor(kBlue);
    h1_r_50100->SetMarkerColor(kBlue);
    h1_r_50100->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_r_50100->Draw("P E same");
    h1_r_50100->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_r_50100->GetYaxis()->SetRangeUser(0.3, 100000);
    h1_r_50100->GetXaxis()->SetTitle("r");
    gPad->Update();
    //        NormalizeHistScale(h1_jt_MCtruth_100150);
    h1_r_MCtruth_50100->SetLineColor(kGreen);
    h1_r_MCtruth_50100->SetMarkerColor(kGreen);
    h1_r_MCtruth_50100->SetMarkerStyle(41);
    h1_r_MCtruth_50100->SetMarkerSize(3);
    gPad->SetLogy();
    h1_r_MCtruth_50100->Draw("P E same");
    h1_r_MCtruth_50100->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_r_MCtruth_50100->GetYaxis()->SetRangeUser(0.3, 100000);
    h1_r_MCtruth_50100->GetXaxis()->SetTitle("r");
    gPad->Update();
//    NormalizeHist(h1_2Dunfolded_r_3050);
    h1_2Dunfolded_r_50100->SetLineColor(kRed);
    h1_2Dunfolded_r_50100->SetMarkerColor(kRed);
    h1_2Dunfolded_r_50100->SetMarkerStyle(21);
    gPad->SetLogy();
    h1_2Dunfolded_r_50100->Draw("P E same");
    h1_2Dunfolded_r_50100->GetXaxis()->SetRangeUser(0.0, 0.6);
    h1_2Dunfolded_r_50100->GetYaxis()->SetRangeUser(0.3, 100000);
    h1_2Dunfolded_r_50100->GetXaxis()->SetTitle("r");
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg24 = new TLegend(0.65, 0.6, 0.85, 0.75);
    leg24->SetTextFont(lhcbFont);
    leg24->SetBorderSize(0);
    lhcbLatex1->DrawLatex(0.65, 0.78, "50 < p_{T jet} < 100");
    if (isMagUp){
        leg24->AddEntry(h1_r_MCtruth_50100, "True MD","LPE");
        leg24->AddEntry(h1_r_50100, "Measured MD", "LPE");
        leg24->AddEntry(h1_2Dunfolded_r_50100, "Unfolded MD", "LPE");
    }else{
        leg24->AddEntry(h1_r_MCtruth_50100, "True ","LPE");
        leg24->AddEntry(h1_r_50100, "Measured ", "LPE");
        leg24->AddEntry(h1_2Dunfolded_r_50100, "Unfolded ", "LPE");
    }

    leg24->Draw("same");
    gPad->Update();
    c27->Update();
    c27->Modified();
    c27->Draw();
    c27->SaveAs(plotextension + str_mag + "r50100_2Dunfold.pdf");



  f->Write();
  f->Close();

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
    //
    // sprintf(buf,"/usr/bin/ps2pdf %s %s",plotfile.Data(),plotfilePDF.Data());
    // cout<<" "<<buf<<endl;
    // int iSuccess = gSystem->Exec(buf);
    // if (iSuccess==0){
    // 	sprintf(buf,"/bin/rm %s",plotfile.Data());
    // 	gSystem->Exec(buf);
    // 	cout<<" "<<buf<<endl;
    // } else {
    // 	cout<<" PDF creation failed ... "<<plotfile.Data()<<endl;
    // }
    //		sprintf(buf,"/usr/bin/scp %s wjllope@rhic22.physics.wayne.edu:/Library/WebServer/WebPages/files/",plotfilePDF.Data());
    //		gSystem->Exec(buf);
    //		cout<<" "<<buf<<endl;
  }
  cout << "Num of Reco B jets = " << NumBjets << endl;
  cout << "Num of True B jets = " << NumTrueBjets << endl;

  // CAJetAlgo(std::string filename);

  // loop(ptMax, Nsubsets);
  // write(ptMax, Nsubsets);
}
//
