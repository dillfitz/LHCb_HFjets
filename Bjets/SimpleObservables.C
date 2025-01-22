#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <TF1.h>
#include <TLatex.h>
#include <THStack.h>
#include <TChain.h>
#include <TStyle.h>
#include "Settings.h"
#include "../Helpers.h"


using namespace std;

void SimpleObservables(int NumEvts = 10000, int dataset = 1510,
                bool isData = true,
                int DoTrackEff = 0,
                int DoTrigEff = 0,
                int DoPIDEff = 0,
                bool DoRecSelEff = false,
                int DoMassFit = 0,
                bool DoSignalSys = false,
                bool DoJetID = false,                                
                bool SubtractGS = false)
{

  bool MCflag = !isData;
  followHardest = false;


  int year = (dataset / 10000) % 10;
  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;

  int dataset_closure;
  if (Mag == 0)
    dataset_closure = dataset + 1;
  else if (Mag == 1)
    dataset_closure = dataset - 1;
  else
    dataset_closure = dataset;

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
  TString str_year = "2016";
  TString str_DTF = "";
  TString str_PID = "";
  TString str_GS = "";

  if (SubtractGS)
    str_GS = "_GSsub";

  if (year == 6)
    str_year = "2016";
  else if (year == 7)
    str_year = "2017";
  else if (year == 8)
    str_year = "2018";

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
  // TString str_trees[5];
  // str_trees[0] = "TaggedDijets/DecayTree";
  // str_trees[1] = "D0KPiJet/DecayTree";
  // str_trees[2] = "B0KPiJet/DecayTree";
  // str_trees[3] = "Jets/DecayTree";

  TString str_tree;
  TString  extension_RootFilesMC, extension_RootFiles;
  TString  extension_read, extension_wspace, extension_eff;
  TString eff_path;

  TString extension_unfold, extension_prefix, extension_trackeff;
  TString extension;

  extension = str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_GS + Form("_%d", dataset);

  // HFjetTree Tree(0, dataset, isData);

  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;
    
  extension_RootFilesMC = TString("../../root_files/BjetsMC/");
  extension_RootFiles = isData ?  TString("../../root_files/Bjets/") : extension_RootFilesMC;
    
  eff_path = TString( "../../Effs/");
    
  float minimum_dR = 0.1;

  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + Form("_%d", dataset);
  extension_unfold = TString("unfold_reco") + Form("_ev_%d", -1) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_GS + Form("_%d", dataset);
  extension_wspace = TString("workspace_massfit_") + str_level + Form("_ev_%d", -1) + Form("_ptj_%d%d", int(15), int(250)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_ghost + str_Mag + str_flavor + Form("_%d", dataset);

  if (DoJetID)
    extension_prefix = TString("jetid_");    
  if (DoRecSelEff)
    extension_prefix = TString("recselsys_");
  if (DoSignalSys)
    extension_prefix = TString("signalsys_");
    
  extension_unfold = extension_prefix + extension_unfold;

  if (DoTrackEff == 1)
    extension = TString("trackingsysup_") + extension;
  if (DoTrackEff == 2)
    extension = TString("trackingsysdown_") + extension;
  if (DoPIDEff == 1)
    extension = TString("pidsysup_") + extension;
  if (DoPIDEff == 2)
    extension = TString("pidsysdown_") + extension;
  if (DoTrigEff == 1)
    extension = TString("trigsysup_") + extension;
  if (DoTrigEff == 2)
    extension = TString("trigsysdown_") + extension;  
  if (DoMassFit == 1)
    extension_prefix = TString("massfitsysnear_");
  if (DoMassFit == 2)
    extension_prefix = TString("massfitsysfar_");
  


  //cout << extension_read << endl;
  cout << extension_unfold << endl;

  extension = extension_prefix + extension;
  extension_trackeff = "trackEff_" + str_year + "_Ratio_Full_Long_method";

  TFile *file_unfold = new TFile(extension_RootFilesMC + extension_unfold + TString(".root"), "READ");
  // TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
  // TFile fwspace(dir_deadcone + "hists/" + extension_wspace + ".root", "READ");
  // TFile file_reco_weights("hists/MC_DATA_WEIGHTS.root", "READ");
  TFile *file_decay = new TFile( extension_RootFilesMC + "HFeff_truth_ev_-1" + str_Mag + str_flavor + str_DTF + str_PID + Form("_%d.root", dataset), "READ");
    
  TFile *file_truth = new TFile( extension_RootFilesMC + "truth_ev_-1_ptj_20100_eta_2.54.0_HF_b_91599.root", "READ");
  
  TFile file_reco_weights("../../root_files/Bjets/MC_DATA_WEIGHTS.root", "READ");  

  //
  TH2D *h2_HFptrap_ratio;
  TH3D *h3_HFptjetptrap_ratio;
  TH3D *h3_dRztheta_ratio;
  // if (!isData)
  // {
  //   h2_HFptrap_ratio = (TH2D *)file_reco_weights.Get("h2_HFptrap_ratio");
  //   h3_HFptjetptrap_ratio = (TH3D *)file_reco_weights.Get("h3_HFptjetptrap_ratio");
  //   h3_dRztheta_ratio = (TH3D *)file_reco_weights.Get("h3_dRztheta_ratio");
  // }

  /////////////////// Efficiencies and Purities /////////////////////////////////

  TH1D *h1_efficiency_HFpt = (TH1D *)file_unfold->Get("efficiency_HFpt");
  TH1D *h1_purity_HFpt = (TH1D *)file_unfold->Get("purity_HFpt");
  TH1D *h1_purity_jetpt = (TH1D *)file_unfold->Get("purity_jetpt");
  TH2D *h2_purity_HFptjetpt = (TH2D *)file_unfold->Get("purity_HFptjetpt");

  TH2D *h2_efficiency_HFptjetpt = (TH2D *)file_unfold->Get("efficiency_HFptjetpt");
  TH3D *h3_efficiency_HFptetajetpt = (TH3D *)file_unfold->Get("efficiency_HFptetajetpt");
  TH3D *h3_purity_HFptetajetpt = (TH3D *)file_unfold->Get("purity_HFptetajetpt");
  TH2D *h2_response_jetpt = (TH2D *)file_unfold->Get("h2_response_jetpt");
    
    // Observables
  TH2D *h2_efficiency_ptz = (TH2D *)file_unfold->Get("efficiency_ptz");
  TH2D *h2_efficiency_ptjt = (TH2D *)file_unfold->Get("efficiency_ptjt");
  TH2D *h2_efficiency_ptr = (TH2D *)file_unfold->Get("efficiency_ptr");
  TH2D *h2_purity_ptz = (TH2D *)file_unfold->Get("purity_ptz");
  TH2D *h2_purity_ptjt = (TH2D *)file_unfold->Get("purity_ptjt");
  TH2D *h2_purity_ptr = (TH2D *)file_unfold->Get("purity_ptr");
  
  TH2D *h3_efficiency_ptzjt = (TH2D *)file_unfold->Get("efficiency_ptzjt");
  TH2D *h3_efficiency_ptzr = (TH2D *)file_unfold->Get("efficiency_ptzt");
  TH2D *h3_efficiency_ptjtr = (TH2D *)file_unfold->Get("efficiency_ptjtr");
  TH2D *h3_purity_ptzjt = (TH2D *)file_unfold->Get("purity_ptzjt");
  TH2D *h3_purity_ptzr = (TH2D *)file_unfold->Get("purity_ptzr");
  TH2D *h3_purity_ptjtr = (TH2D *)file_unfold->Get("purity_ptjtr");  
    
  RooUnfoldResponse *response_ptz = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptz");
  RooUnfoldResponse *response_ptjt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptjt");
  RooUnfoldResponse *response_ptr = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptr");

    // TH2D *h2_SVTag_eff = (TH2D *)file_unfold->Get("h2_SVTag_eff");
  TH2D *h2_SVTag_eff_z = (TH2D *)file_unfold->Get("h2_SVTag_eff_z");
  TH2D *h2_SVTag_pur_z = (TH2D *)file_unfold->Get("h2_SVTag_pur_z");
  TH2D *h2_SVTag_eff = (TH2D *)file_unfold->Get("h2_SVTag_eff");
  TH2D *h2_SVTag_pur = (TH2D *)file_unfold->Get("h2_SVTag_pur");

  TH1D *h1_HFeff_HFpt = (TH1D *)file_decay->Get("efficiency_HFpt");
  TH1D *h1_HFeff_jetpt = (TH1D *)file_decay->Get("efficiency_jetpt");
  TH2D *h2_HFeff_HFpteta = (TH2D *)file_decay->Get("efficiency_HFpteta");
  TH2D *h2_HFeff_HFptjetpt = (TH2D *)file_decay->Get("efficiency_HFptjetpt");
    
  TH2D *h2_ptz_truth = (TH2D *)file_truth->Get("ptz");
  TH2D *h2_ptjt_truth =(TH2D *)file_truth->Get("ptjt");
  TH2D *h2_ptr_truth = (TH2D *)file_truth->Get("ptr");

  // h2_SVTag_eff_z->Smooth();

  /////////////////// Mass Fit Parameters /////////////////////////////////
  // massfit_data_ev_-1_ptj_12250_eta_2.54.0_ghost_0.5_b_PID_91599.root
  TString massfit = TString("massfit_data_ev_-1_ptj_7250_eta_2.54.0_ghost_0.5") + str_Mag  + TString("_b_PID_") + Form("%d.root", dataset);
  //TString recostr = TString("massfit_reco_ev_-1_ptj_7250_eta_2.54.0_ghost_0.5") + str_Mag + TString("_b_PID_") + Form("%d.root", dataset);

    
  if (DoRecSelEff)
    massfit = "recselsys_" + massfit;
  if (DoSignalSys)
  {
    massfit = "sys_" + massfit;
  }
  
  TString extension_mass = "../../root_files/Bjets/" + massfit;  
  std::cout << "extension_mass : " << extension_mass << std::endl;   
  TFile f_massfit( extension_mass, "READ");
  TH1D *h1_MassMin = (TH1D *)f_massfit.Get("h1_MassMin");
  TH1D *h1_MassMax = (TH1D *)f_massfit.Get("h1_MassMax");
  TH1D *h1_Sideband1Min = (TH1D *)f_massfit.Get("h1_Sideband1Min");
  TH1D *h1_Sideband1Max = (TH1D *)f_massfit.Get("h1_Sideband1Max");
  TH1D *h1_Sideband2Min = (TH1D *)f_massfit.Get("h1_Sideband2Min");
  TH1D *h1_Sideband2Max = (TH1D *)f_massfit.Get("h1_Sideband2Max");
  TH1D *h1_BkgScale = (TH1D *)f_massfit.Get("h1_BkgScale");
  TH1D *h1_BkgScale_forSysNear = (TH1D *)f_massfit.Get("h1_BkgScale_forSysNear");
  TH1D *h1_BkgScale_forSysFar = (TH1D *)f_massfit.Get("h1_BkgScale_forSysFar");


  //////////////////////////////////////
  
  /////////////////// Trigger Ratio (TISTOS/MC True) /////////////////////////////////
  TString extension_trig("jpsieff_data_ev_-1_b" + TString("_91599.root"));
  // if (DoTrigEff)
  //   extension_trig = "recselsys_" + extension_trig;
  TFile f_trig("../../root_files/TrigEff/" + extension_trig, "READ");
  TH2D *h2_trig_ratio = (TH2D *)f_trig.Get("h2_eff_ratio");


  TF1 *f_eff = (TF1 *)file_unfold->Get("f_eff1");
  TF1 *f_pur = (TF1 *)file_unfold->Get("f_pur1");
  //
    TChain *BTree = new TChain("BTree", "B-jets Tree Variables");
    vector<int> vec_datasets;
  if (Mag == 0)
    vec_datasets = {61590, 71590, 81590};
  else if (Mag == 1)
    vec_datasets = {61591, 71591, 81591};
  else
    vec_datasets = {61590, 61591, 71590, 71591, 81590, 81591};

  if (year == 9 && JetMeth != 9)
  {
    for (int i = 0; i < vec_datasets.size(); i++)
    {
      Mag = (vec_datasets[i] / 1) % 10;
      if (Mag == 0)
        str_Mag = "_MD";
      else if (Mag == 1)
        str_Mag = "_MU";
      extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost  + str_Mag + str_flavor + Form("_%d", vec_datasets[i]);
      if (!DoRecSelEff && DoMassFit == 0 && DoSignalSys == 0)
      {
        extension_read = extension_prefix + extension_read;
        cout << "Loading Dataset(s) " << extension_read << endl;        
      }

     BTree->Add(extension_RootFiles + extension_read + ".root/BTree");
    }
  }
  else
  {
    extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + Form("_%d", dataset);
    if (!DoRecSelEff && DoMassFit == 0 && DoSignalSys == 0)
    {   
      extension_read = extension_prefix + extension_read;
      cout << "Loading Dataset(s) " << extension_read << endl;       
    }
      BTree->Add(extension_RootFiles + extension_read + ".root/BTree");
  }

  cout << BTree->GetTreeNumber() << endl;
  if (NumEvts > BTree->GetEntries())
    NumEvts = BTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = BTree->GetEntries();
  cout << BTree->GetEntries() << endl;

    TFile f(extension_RootFiles  + extension + ".root", "RECREATE");
    
    TH2D *h2_zjt = new TH2D("zjt", ";z; j_{T} ", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_zr = new TH2D("zr", ";z; r ", zbinsize, z_binedges, rbinsize, r_binedges);
    TH2D *h2_jtr = new TH2D("jtr", "; j_{T}; r ", jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    TH1D *h1_z = new TH1D("z", ";z", zbinsize, z_binedges);
    TH1D *h1_tr_z = new TH1D("tr_z", ";z", zbinsize, z_binedges);
    TH1D *h1_jt = new TH1D("jt", ";j_{T}", jtbinsize, jt_binedges);
    TH1D *h1_tr_jt = new TH1D("tr_jt", ";j_{T}", jtbinsize, jt_binedges);
    TH1D *h1_r = new TH1D("r", ";r", rbinsize, r_binedges);
    TH1D *h1_tr_r = new TH1D("tr_r", "r", rbinsize, r_binedges);
                                    
    TH1D *h1_jt_tot = new TH1D("jt_tot", "Total; j_{T}",  jtbinsize, jt_binedges);
    TH1D *h1_z_tot = new TH1D("z_tot", "Total; z", zbinsize, z_binedges);
    TH1D *h1_r_tot = new TH1D("r_tot", "Total; r ", rbinsize, r_binedges);

    TH2D *h2_ptz = new TH2D("ptz", ";z;", zbinsize, z_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptjt = new TH2D("ptjt", ";j_{T};", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptr = new TH2D("ptr", ";r;", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
    TH3D *h3_ptzjt = new TH3D("ptzjt", ";z ; j_{T};", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptzr = new TH3D("ptzr", ";z ; r;",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptjtr = new TH3D("ptjtr", ";j_{T}; r; ",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    
    TH2D *h2_ptz_50_100 = new TH2D("ptz_50_100", ";z;", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
    TH2D *h2_ptjt_50_100 = new TH2D("ptjt_50_100", ";j_{T};", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
    TH2D *h2_ptr_50_100 = new TH2D("ptr_50_100", ";r;", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
    
    TH3D *h3_ptzjt_50_100 = new TH3D("ptzjt_50_100", ";z ; j_{T};", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges );
    TH3D *h3_ptzr_50_100 = new TH3D("ptzr_50_100", ";z ; r;",  zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges );
    TH3D *h3_ptjtr_50_100 = new TH3D("ptjtr_50_100", ";j_{T}; r; ",  jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges );    
     
    TH3D *h3_ptzjt_unweight = new TH3D("ptzjt_unweight", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptzr_unweight = new TH3D("ptzr_unweight", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptjtr_unweight = new TH3D("ptjtr_unweight", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    
    TH3D *h3_ptHFzjt = new TH3D("ptHFzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_ptHFzr = new TH3D("ptHFzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    TH3D *h3_ptHFjtr = new TH3D("ptHFjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptHFbinsize, ptHF_binedges );
    
    TH2D *h2_ptHFz = new TH2D("HFptz", ";z;", zbinsize, z_binedges, ptHFbinsize, ptHF_binedges);
    TH2D *h2_ptHFjt = new TH2D("HFptjt", ";j_{T};", jtbinsize, jt_binedges, ptHFbinsize, ptHF_binedges);
    TH2D *h2_ptHFr = new TH2D("HFptr", ";r;", rbinsize, r_binedges, ptHFbinsize, ptHF_binedges);    

    TH1D *h1_z_ptHFcut_g5 = new TH1D("z_ptHFcut_g5", ";z;", zbinsize, z_binedges);
    TH1D *h1_z_ptHFcut_l5 = new TH1D("z_ptHFcut_l5", ";z;", zbinsize, z_binedges);    
    
    /// ------------------------------------------ COMBINATORIAL --------------------------------------------- ///
    
    TH1D *h1_z_comb = new TH1D("z_comb", "Combinatoric; z", zbinsize, z_binedges);
    TH1D *h1_jt_comb = new TH1D("jt_comb", "Combinatoric; j_{T}", jtbinsize, jt_binedges);
    TH1D *h1_r_comb = new TH1D("r_comb", "Combinatoric; r", rbinsize, r_binedges);
    
    TH2D *h2_zjt_comb = new TH2D("zjt_comb", "", zbinsize, z_binedges,  jtbinsize, jt_binedges);
    TH2D *h2_zr_comb = new TH2D("zr_comb", "", zbinsize, z_binedges,  rbinsize, r_binedges);
    TH2D *h2_jtr_comb = new TH2D("jtr_comb", "", jtbinsize, jt_binedges,  rbinsize, r_binedges);

    TH2D *h2_ptz_comb = new TH2D("ptz_comb", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptjt_comb = new TH2D("ptjt_comb", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptr_comb = new TH2D("ptr_comb", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
    TH3D *h3_ptzjt_comb = new TH3D("ptzjt_comb", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptzr_comb = new TH3D("ptzr_comb ", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptjtr_comb = new TH3D("ptjtr_comb", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    
    /// ------------------------------------------------- SV -------------------------------------------------------- ///
    
    TH1D *h1_z_SV = new TH1D("z_SV", "SV > 0 ; z", zbinsize, z_binedges);
    TH1D *h1_jt_SV = new TH1D("jt_SV", "SV > 0; j_{T}", jtbinsize, jt_binedges);
    TH1D *h1_r_SV = new TH1D("r_SV", "SV > 0; r", rbinsize, r_binedges);
    
    TH2D *h2_ptz_SV = new TH2D("ptz_SV", "SV > 0 ; z;", zbinsize, z_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptjt_SV = new TH2D("ptjt_SV", "SV > 0 ; z;", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptr_SV = new TH2D("ptr_SV", "SV > 0 ; z;", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
    TH3D *h3_ptzjt_SV = new TH3D("ptzjt_SV", "SV > 0 ; z; j_{T};", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptzr_SV = new TH3D("ptzr_SV", "SV > 0 ; z; r;",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_ptjtr_SV = new TH3D("ptjtr_SV", "SV > 0 ; j_{T}; r;",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
     
     TH2D *h2_zjt_SV  = new TH2D("zjt_SV ", "SV > 0 ;z; j_{T} ", zbinsize, z_binedges, jtbinsize, jt_binedges);
     TH2D *h2_zr_SV  = new TH2D("zr_SV ", "SV > 0 ;z; r ", zbinsize, z_binedges, rbinsize, r_binedges);
     TH2D *h2_jtr_SV  = new TH2D("jtr_SV ", "SV > 0; j_{T}; r ", jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    
    /// ---------------------------------------------- GLUONS ---------------------------------------------------- ///


    TH1D *h1_z_gluon = new TH1D("z_gluon", "Gluons; z", zbinsize, z_binedges);
    TH1D *h1_jt_gluon = new TH1D("jt_gluon", "Gluons; j_{T}", jtbinsize, jt_binedges);
    TH1D *h1_r_gluon = new TH1D("r_gluon", "Gluons; r", rbinsize, r_binedges);
    
    TH2D *h2_zjt_gluon = new TH2D("zjt_gluon", "Gluons ;z; j_{T} ", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_zr_gluon = new TH2D("zr_gluon", "Gluons;z; r ", zbinsize, z_binedges, rbinsize, r_binedges);
    TH2D *h2_jtr_gluon = new TH2D("jtr_gluon", "Gluons; j_{T}; r ", jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    TH2D *h2_ptz_gluon = new TH2D("ptz_gluon", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptjt_gluon = new TH2D("ptjt_gluon", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_ptr_gluon = new TH2D("ptr_gluon", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
    /// --------------------------------------------  B-FROM-JET  ------------------------------------------------ ///
    
    TH1D *h1_z_Bfromjet = new TH1D("z_Bfromjet", "", zbinsize, z_binedges);
    TH1D *h1_jt_Bfromjet = new TH1D("jt_Bfromjet", "", jtbinsize, jt_binedges);
    TH1D *h1_r_Bfromjet = new TH1D("r_Bfromjet", "", rbinsize, r_binedges);

    
    //// ----------------------------------------------------------------------------------------------------------- ////

  TH1D *h1_dphi = new TH1D("dphi", "", 60, 0, TMath::Pi() - 0.001);
  TH1D *h1_dphi_gluon = new TH1D("dphi_gluon", "", 60, 0, TMath::Pi() - 0.001);
  TH1D *h1_dphi_SV = new TH1D("dphi_SV", "", 60, 0, TMath::Pi() - 0.001);

  TH1D *h1_R = new TH1D("R_Observable", "R Observable", 20, 1.5, 6.5);

  TH2D *h2_jetpt_HFpt = new TH2D("jetpt_HFpt", "", 50, 0, 100, 50, 0, 100);

  TH1D *h1_jet_flav = new TH1D("Jet_Flav", "", 7, -0.5, 6.5);
  TH1D *h1_jet_pt = new TH1D("Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_jet_pt_fine = new TH1D("Jet_pT_fine", "", fineptbinsize, finept_binedges);
  TH1D *h1_jet_pt_comb = new TH1D("Jet_pT_comb", "", ptbinsize, pt_binedges);
  TH1D *h1_jet_pt_SV = new TH1D("Jet_pT_SV", "", 60, 15, 150);
  TH1D *h1_jet_eta = new TH1D("Jet_eta", "", 12, etaMin, etaMax);
  TH1D *h1_jet_rap = new TH1D("Jet_rap", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi = new TH1D("Jet_phi", "", 20, -3.14, 3.14);
  TH1D *h1_jet_ptbalance = new TH1D("jet_ptbalance", "", 60, -1, 1);

  TH2D *h2_jetpteta = new TH2D("h2_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);

  TH1D *h1_tr_jet_pt = new TH1D("tr_Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_jet_trueeta = new TH1D("Jet_trueeta", "", 12, etaMin, etaMax);
  TH1D *h1_jet_truephi = new TH1D("Jet_truephi", "", 20, -3.14, 3.14);

  TH1D *h1_jet_pt_noghost = new TH1D("Jet_pT_noghost", "", 50, ptMin, ptMax);
  TH1D *h1_jet_eta_noghost = new TH1D("Jet_eta_noghost", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi_noghost = new TH1D("Jet_phi_noghost", "", 20, -3.14, 3.14);

  TH1D *h1_Jpsi_rap = new TH1D("Jpsi_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_Jpsi_pt = new TH1D("Jpsi_pT", "", 50, 0, 100);
  TH1D *h1_Jpsi_phi = new TH1D("Jpsi_phi", "", 20, -3.14, 3.14);
  TH1D *h1_Jpsi_mass = new TH1D("Jpsi_mass", "", 30, 3.1 - 0.2, 3.1 + 0.2);
  TH1D *h1_Jpsi_ipchi2 = new TH1D("Jpsi_ipchi2", "", 80, -3, 5);

  TH1D *h1_HF_rap = new TH1D("HF_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_HF_pt = new TH1D("HF_pT", "", 50, 0, 100);
  TH1D *h1_HF_phi = new TH1D("HF_phi", "", 20, -3.14, 3.14);
  TH1D *h1_HF_mass = new TH1D("HF_mass", "", 80, 5.279 - 0.3, 5.279 + 0.3);
  TH1D *h1_HF_mass_dtfcut = new TH1D("HF_mass_dtfcut", "", 80, 5.279 - 0.3, 5.279 + 0.3);
  TH2D *h2_HF_mass_float = new TH2D("HF_mass_float", "", 12, 5.279 - 0.3, 5.279 + 0.3, 12, 5.279 - 0.3, 5.279 + 0.3);
  TH1D *h1_HFjet_ptbalance = new TH1D("HFjet_ptbalance", "", 20, 0, 2);

  TH1D *h1_HFpt = new TH1D("h1_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH2D *h2_HFptjetpt = new TH2D("h2_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_HFptrap = new TH2D("h2_HFptrap", "", ptHFbinsize, ptHF_binedges, etabinsize, eta_binedges);
  TH3D *h3_HFptjetptrap = new TH3D("h3_HFptjetptrap", "", ptHFbinsize, ptHF_binedges, fineptbinsize, finept_binedges, etabinsize, eta_binedges);

  TH1D *h1_HF_trueeta = new TH1D("HF_trueeta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_HF_truept = new TH1D("HF_truepT", "", 50, 0, 80);
  TH1D *h1_HF_truephi = new TH1D("HF_truephi", "", 20, -3.14, 3.14);

  TH1D *h1_Dtr_Eta = new TH1D("Dtr_Eta", "", 50, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_dtr_phi = new TH1D("Dtr_phi", "", 50, -3.14, 3.14);
  TH1D *h1_dtr_pT = new TH1D("Dtr_pT", "", 50, 0, 10);
  TH1D *h1_dtr_p = new TH1D("Dtr_p", "", 50, 0, 150);
  TH1D *h1_keys = new TH1D("Keys", "Keys", 100, 0, 100);
  TH1D *h1_hfdtrs_e_diff = new TH1D("HFDtrsEDiff", "HFDtrsEDiff", 40, -100, 100);
  TH1D *h1_HFHadronMass = new TH1D("HFHadronMass", "HFHadronMass", 100, 60, 120);
    
//  TH1D *h1_HF_jet_dR = new TH1D("HF_jet_dR", "", 24, 0, 4.);
//  TH1D *h1_HF_jet_truedR = new TH1D("HF_jet_truedR", "", 24, 0, 4.);
    
  TH1D *h1_HFdtr1_mass = new TH1D("HFdtr1mass", "", 100, 1, 7);
  TH1D *h1_recoHFHadronMass = new TH1D("recoHFHadronMass", "recoHFHadronMass", 40, 0, 15);
  TH1D *h1_nsplittings = new TH1D("nSplittings", "nSplittings", 15, -0.5, 14.5);
  TH1D *h1_ptHF = new TH1D("ptHF", "pT_{HF}", 30, 0, 25);
  TH1D *h1_probNNghost = new TH1D("probNNghost", "probNNghost", 20, 0, 1);

  TH1D *h1_nJetDtrs = new TH1D("nJetDtrs", "", 40, -0.5, 39.5);
  TH1D *h1_nJetDtrs_noghost = new TH1D("nJetDtrs_noghost", "nJetDtrs_noghost", 40, -0.5, 39.5);
  TH1D *h1_nJetDtrs_noghost_comb = new TH1D("nJetDtrs_noghost_comb", "", 40, -0.5, 39.5);
  TH1D *h1_nJetDtrs_noghost_SV = new TH1D("nJetDtrs_noghost_SV", "", 40, -0.5, 39.5);
  TH1F *h_nJetDaughters = new TH1F("h_nJetDaughters", "Number of jet daughters", 40, -0.5, 39.5);

  TH1D *h1_dtr_pt = new TH1D("h1_dtr_pt", "; p_{T}^{dtr};", 100, 0, 10);
  TH2D *h2_Ndtr_jetpt_neutral = new TH2D("h2_Ndtr_jetpt_neutral", "", 15, -0.5, 14.5, ptbinsize, pt_binedges);
  TH2D *h2_Ndtr_jetpt_charged = new TH2D("h2_Ndtr_jetpt_charged", "", 15, -0.5, 14.5, ptbinsize, pt_binedges);
  TH2D *h2_Ndtr_jetpt = new TH2D("h2_Ndtr_jetpt", "", 15, -0.5, 14.5, ptbinsize, pt_binedges);
  // TH1D* truedtrp_h = new TH1D("truedtrp_h",";p [GeV]",npbins,thispbins);
  // TH1D* truedtrpt_h = new TH1D("truedtrpt_h",";p_{T} [GeV]",npbins,thispbins);
  TH1D *truenconst_h = new TH1D("truenconst_h", ";N_{const}^{chg}", 40, -0.5, 39.5);

  TH1D *h1_Mcor_true = new TH1D("h1_Mcor_true", "", 30, 0, 15.);
  TH1D *h1_Mcor_false = new TH1D("h1_Mcor_false", "", 30, 0, 15.);

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
  
  TH2D *h2_ptz_weighted = new TH2D("ptz_weighted", ";z;p_{T} (GeV/c)", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt_weighted = new TH2D("ptjt_weighted", ";j_{T} (GeV/c); p_{T} (GeV/c)", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr_weighted = new TH2D("ptr_weighted", ";r;p_{T} (GeV/c)", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
  TH1D *h1_z_weighted = new TH1D("z_weighted", ";z;", zbinsize, z_binedges);
  TH1D *h1_jt_weighted = new TH1D("jt_weighted", ";j_{T} (GeV/c);", jtbinsize, jt_binedges);
  TH1D *h1_r_weighted = new TH1D("r_weighted", ";r;", rbinsize, r_binedges);  
  
  TH1D *h1_z_nobgsub, *h1_jt_nobgsub, *h1_r_nobgsub;
  TH2D *h2_ptz_nobgsub, *h2_ptjt_nobgsub, *h2_ptr_nobgsub;
  h1_z_nobgsub = (TH1D*)h1_z->Clone("z_nobgsub");
  h1_jt_nobgsub = (TH1D*)h1_jt->Clone("jt_nobgsub");
  h1_r_nobgsub = (TH1D*)h1_r->Clone("r_nobgsub");
  h2_ptz_nobgsub = (TH2D*)h2_ptz->Clone("ptz_nobgsub");    
  h2_ptjt_nobgsub = (TH2D*)h2_ptjt->Clone("ptjt_nobgsub");            
  h2_ptr_nobgsub = (TH2D*)h2_ptr->Clone("ptr_nobgsub");     
   
    
   TH3D *h3_ptzjt_ratio = (TH3D *)file_reco_weights.Get("ptzjt_ratio");   

  //
  // Event loop
  //
  unsigned long long last_eventNum = 0;
  float last_jetpT = 0.;
  int event_counter = 0;
    
  vector<float> *dtr_pt(0), *dtr_rap(0), *dtr_id(0), *dtr_3charge(0);
  vector<float> *sv_ipchi2(0), *sv_keys(0), *sv_pids(0);

  float jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  float jet_rap, tr_jet_rap;
  float jet_px, jet_py, jet_pz, jet_e, jet_charge;
  float HF_px, HF_py, HF_pz, HF_e, HF_pt;
  float Z_px, Z_py, Z_pz, Z_e;
  float mup_px, mup_py, mup_pz, mup_e;
  float mum_px, mum_py, mum_pz, mum_e;
  float K_px, K_py, K_pz, K_e;
  float mup_CHI2NDOF, mup_GHOSTPROB, mup_IPCHI2;
  float mum_CHI2NDOF, mum_GHOSTPROB, mum_IPCHI2;
  float K_CHI2NDOF, K_GHOSTPROB, K_IPCHI2;
  float Jpsi_CHI2NDOF, Jpsi_CHI2, Jpsi_FDCHI2, Jpsi_IPCHI2, Jpsi_BPVDLS;
  float Bu_CHI2NDOF, Bu_CHI2, Bu_IPCHI2;
  float Bfromjet_px, Bfromjet_py, Bfromjet_pz, Bfromjet_e;
  float K_PIDK;
  int nTracks;

  float tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  float tr_mup_px, tr_mup_py, tr_mup_pz, tr_mup_e;
  float tr_mum_px, tr_mum_py, tr_mum_pz, tr_mum_e;
  float tr_K_px, tr_K_py, tr_K_pz, tr_K_e;
    
  double z, jt, r;
  double tr_z, tr_jt, tr_r;
  double zg, jtg, rg;


  int nsplits, ndtrs, ndtrs_noghost, NumSubJets;
  int tr_nsplits, tr_ndtrs;
  bool isTrueBjet, isBacktoBack, HFHardest, Hasbbbar, TOS;
  float dphi, bmass_dtf, Bmass_1, Bmass_2;
  int nSV, nSV_test, NumBHads_tr;
  float jpsi_ipchi2;
  int eventNumber;
  float sv_mass, sv_chi2, sv_ntrks, sv_cosine, bdt_mCor;
  int SVTag;
  float chi2ndf_dtf, tau_dtf;
  int Ndtr_charged, Ndtr_neutral;
  // TLorentzVector
    
    float pideff_K(1.0), pideff_mup(1.0), pideff_mum(1.0);
    float pideff_K_err(1.0), pideff_mup_err(1.0), pideff_mum_err(1.0);
    float trkeff_K(1.0), trkeff_mup(1.0), trkeff_mum(1.0);
    float trkeff_K_errhi(1.0), trkeff_mup_errhi(1.0), trkeff_mum_errhi(1.0);
    float trkeff_K_errlo(1.0), trkeff_mup_errlo(1.0), trkeff_mum_errlo(1.0);
    float trigeff_Data(1.0), trigeff_MC(1.0), trigeff_ratio(1.0);
    
  BTree->SetBranchAddress("eventNumber", &eventNumber);

  BTree->SetBranchAddress("dtr_pt", &dtr_pt);
  BTree->SetBranchAddress("dtr_rap", &dtr_rap);
  BTree->SetBranchAddress("dtr_id", &dtr_id);
  BTree->SetBranchAddress("dtr_3charge", &dtr_3charge);
  BTree->SetBranchAddress("Ndtr_neutral", &Ndtr_neutral);
  BTree->SetBranchAddress("Ndtr_charged", &Ndtr_charged);

//  BTree->SetBranchAddress("thetas", &thetas);
//  BTree->SetBranchAddress("ktthetas", &ktthetas);
//  BTree->SetBranchAddress("Erads", &Erads);
//  BTree->SetBranchAddress("dRs", &dRs);
//  BTree->SetBranchAddress("kts", &kts);
//  BTree->SetBranchAddress("zs", &zs);
//  BTree->SetBranchAddress("raps", &raps);
//  BTree->SetBranchAddress("phis", &phis);

  BTree->SetBranchAddress("jet_pt", &jet_pt);
  BTree->SetBranchAddress("jet_eta", &jet_eta);
  BTree->SetBranchAddress("jet_rap", &jet_rap);

  BTree->SetBranchAddress("jet_px", &jet_px);
  BTree->SetBranchAddress("jet_py", &jet_py);
  BTree->SetBranchAddress("jet_pz", &jet_pz);
  BTree->SetBranchAddress("jet_e", &jet_e);

  // BTree->SetBranchAddress("jet_charge", &jet_charge);

  BTree->SetBranchAddress("HF_px", &HF_px);
  BTree->SetBranchAddress("HF_py", &HF_py);
  BTree->SetBranchAddress("HF_pz", &HF_pz);
  BTree->SetBranchAddress("HF_e", &HF_e);
  BTree->SetBranchAddress("HF_pt", &HF_pt);

  BTree->SetBranchAddress("Bu_IPCHI2", &Bu_IPCHI2);
  BTree->SetBranchAddress("Bu_CHI2", &Bu_CHI2);
  BTree->SetBranchAddress("Bu_CHI2NDOF", &Bu_CHI2NDOF);
    
  BTree->SetBranchAddress("ndtrs", &ndtrs);
  BTree->SetBranchAddress("ndtrs_noghost", &ndtrs_noghost);
  BTree->SetBranchAddress("nsplits", &nsplits);

  BTree->SetBranchAddress("mum_px", &mum_px);
  BTree->SetBranchAddress("mum_py", &mum_py);
  BTree->SetBranchAddress("mum_pz", &mum_pz);
  BTree->SetBranchAddress("mum_e", &mum_e);
  BTree->SetBranchAddress("mum_IPCHI2", &mum_IPCHI2);
  BTree->SetBranchAddress("mum_CHI2NDOF", &mum_CHI2NDOF);
  BTree->SetBranchAddress("mum_GHOSTPROB", &mum_GHOSTPROB);
    
  BTree->SetBranchAddress("mup_px", &mup_px);
  BTree->SetBranchAddress("mup_py", &mup_py);
  BTree->SetBranchAddress("mup_pz", &mup_pz);
  BTree->SetBranchAddress("mup_e", &mup_e);
  BTree->SetBranchAddress("mup_IPCHI2", &mup_IPCHI2);
  BTree->SetBranchAddress("mup_CHI2NDOF", &mup_CHI2NDOF);
  BTree->SetBranchAddress("mup_GHOSTPROB", &mup_GHOSTPROB);

  BTree->SetBranchAddress("K_px", &K_px);
  BTree->SetBranchAddress("K_py", &K_py);
  BTree->SetBranchAddress("K_pz", &K_pz);
  BTree->SetBranchAddress("K_e", &K_e);
  BTree->SetBranchAddress("K_IPCHI2", &K_IPCHI2);
  BTree->SetBranchAddress("K_CHI2NDOF", &K_CHI2NDOF);
  BTree->SetBranchAddress("K_GHOSTPROB", &K_GHOSTPROB);
    
  BTree->SetBranchAddress("nTracks", &nTracks);
    
  BTree->SetBranchAddress("Jpsi_FDCHI2", &Jpsi_FDCHI2);
  BTree->SetBranchAddress("Jpsi_CHI2", &Jpsi_CHI2);
  BTree->SetBranchAddress("Jpsi_CHI2NDOF", &Jpsi_CHI2NDOF);
  BTree->SetBranchAddress("Jpsi_BPVDLS", &Jpsi_BPVDLS);  
    
  BTree->SetBranchAddress("jpsi_ipchi2", &jpsi_ipchi2);

  BTree->SetBranchAddress("Bfromjet_px", &Bfromjet_px);
  BTree->SetBranchAddress("Bfromjet_py", &Bfromjet_py);
  BTree->SetBranchAddress("Bfromjet_pz", &Bfromjet_pz);
  BTree->SetBranchAddress("Bfromjet_e", &Bfromjet_e);

//  BTree->SetBranchAddress("tr_thetas", &tr_thetas);
//  BTree->SetBranchAddress("tr_ktthetas", &tr_ktthetas);
//  BTree->SetBranchAddress("tr_Erads", &tr_Erads);
//  BTree->SetBranchAddress("tr_dRs", &tr_dRs);
//  BTree->SetBranchAddress("tr_kts", &tr_kts);
//  BTree->SetBranchAddress("tr_zs", &tr_zs);
//  BTree->SetBranchAddress("tr_raps", &tr_raps);
//  BTree->SetBranchAddress("tr_phis", &tr_phis);

  BTree->SetBranchAddress("tr_jet_pt", &tr_jet_pt);
  BTree->SetBranchAddress("tr_jet_eta", &tr_jet_eta);
  BTree->SetBranchAddress("tr_jet_rap", &tr_jet_rap);

  BTree->SetBranchAddress("tr_jet_px", &tr_jet_px);
  BTree->SetBranchAddress("tr_jet_py", &tr_jet_py);
  BTree->SetBranchAddress("tr_jet_pz", &tr_jet_pz);
  BTree->SetBranchAddress("tr_jet_e", &tr_jet_e);

  BTree->SetBranchAddress("tr_mum_px", &tr_mum_px);
  BTree->SetBranchAddress("tr_mum_py", &tr_mum_py);
  BTree->SetBranchAddress("tr_mum_pz", &tr_mum_pz);
  BTree->SetBranchAddress("tr_mum_e", &tr_mum_e);

  BTree->SetBranchAddress("tr_mup_px", &tr_mup_px);
  BTree->SetBranchAddress("tr_mup_py", &tr_mup_py);
  BTree->SetBranchAddress("tr_mup_pz", &tr_mup_pz);
  BTree->SetBranchAddress("tr_mup_e", &tr_mup_e);

  BTree->SetBranchAddress("tr_K_px", &tr_K_px);
  BTree->SetBranchAddress("tr_K_py", &tr_K_py);
  BTree->SetBranchAddress("tr_K_pz", &tr_K_pz);
  BTree->SetBranchAddress("tr_K_e", &tr_K_e);

  BTree->SetBranchAddress("tr_ndtrs", &tr_ndtrs);
  BTree->SetBranchAddress("tr_nsplits", &tr_nsplits);
  BTree->SetBranchAddress("isTrueBjet", &isTrueBjet);

  BTree->SetBranchAddress("dphi", &dphi);
  // BTree->SetBranchAddress("Bmass_1", &Bmass_1);
  // BTree->SetBranchAddress("Bmass_2", &Bmass_2);
  BTree->SetBranchAddress("nSV", &nSV);
  BTree->SetBranchAddress("nSV_test", &nSV_test);
    BTree->SetBranchAddress("sv_mass", &sv_mass);
    BTree->SetBranchAddress("sv_chi2", &sv_chi2);
    BTree->SetBranchAddress("sv_cosine", &sv_cosine);
    BTree->SetBranchAddress("sv_ntrks", &sv_ntrks);
    BTree->SetBranchAddress("sv_ipchi2", &sv_ipchi2);
    BTree->SetBranchAddress("sv_keys", &sv_keys);
    BTree->SetBranchAddress("sv_pids", &sv_pids);
    BTree->SetBranchAddress("bdt_mCor", &bdt_mCor);
    
    BTree->SetBranchAddress("SVTag", &SVTag);
    
    BTree->SetBranchAddress("HFHardest", &HFHardest);
    BTree->SetBranchAddress("bmass_dtf", &bmass_dtf);
    BTree->SetBranchAddress("chi2ndf_dtf", &chi2ndf_dtf);
    BTree->SetBranchAddress("tau_dtf", &tau_dtf);
  // BTree->SetBranchAddress("NumSubJets", &NumSubJets);
    BTree->SetBranchAddress("NumBHads_tr", &NumBHads_tr);
  BTree->SetBranchAddress("Hasbbbar", &Hasbbbar);
  BTree->SetBranchAddress("K_PIDK", &K_PIDK);
  BTree->SetBranchAddress("pideff_K", &pideff_K);
  BTree->SetBranchAddress("pideff_mum", &pideff_mum);
  BTree->SetBranchAddress("pideff_mup", &pideff_mup);
  BTree->SetBranchAddress("pideff_K_err", &pideff_K_err);
  BTree->SetBranchAddress("pideff_mum_err", &pideff_mum_err);
  BTree->SetBranchAddress("pideff_mup_err", &pideff_mup_err);

  BTree->SetBranchAddress("trkeff_K", &trkeff_K);
  BTree->SetBranchAddress("trkeff_mup", &trkeff_mup);
  BTree->SetBranchAddress("trkeff_mum", &trkeff_mum);

  BTree->SetBranchAddress("trkeff_K_errhi", &trkeff_K_errhi);
  BTree->SetBranchAddress("trkeff_mup_errhi", &trkeff_mup_errhi);
  BTree->SetBranchAddress("trkeff_mum_errhi", &trkeff_mum_errhi);
  BTree->SetBranchAddress("trkeff_K_errlo", &trkeff_K_errlo);
  BTree->SetBranchAddress("trkeff_mup_errlo", &trkeff_mup_errlo);
  BTree->SetBranchAddress("trkeff_mum_errlo", &trkeff_mum_errlo);

  BTree->SetBranchAddress("trigeff_Data", &trigeff_Data);
  BTree->SetBranchAddress("trigeff_MC", &trigeff_MC);
  BTree->SetBranchAddress("trigeff_ratio", &trigeff_ratio);
  BTree->SetBranchAddress("TOS", &TOS);
    
    BTree->SetBranchAddress("z", &z);
    BTree->SetBranchAddress("jt", &jt);
    BTree->SetBranchAddress("r", &r);
    BTree->SetBranchAddress("zg", &zg);
    BTree->SetBranchAddress("jtg", &jtg);
    BTree->SetBranchAddress("rg", &rg);
    BTree->SetBranchAddress("tr_z", &tr_z);
    BTree->SetBranchAddress("tr_jt", &tr_jt);
    BTree->SetBranchAddress("tr_r", &tr_r);

  int eventNum;
  int NumJets_zdR_comb = 0;
  int NumJets_ktdR_comb = 0;

  int NumJets_zdR_gluon = 0;
  int NumJets_ktdR_gluon = 0;

  int NumJets_zdR = 0;
  int NumJets_ktdR = 0;

  int N_SV = 0;
  int N_BacktoBack = 0;
  int N_SV_and_BacktoBack = 0;

  int N_hardest = 0;
  int N_NotHardest = 0;

  int NumTwoHFInJet = 0;
  int NumTwoCand = 0;

  float MassMu = 5.27940;
  float MassSigma = 1.32479e-02;
  // if (dataset == 90599)
  // {
  //   MassMu = 5.27907e+00;
  //   MassSigma = 3.08492e-02;
  // }

  cout << "Requested # of events" << NumEvts << endl;
  // float MassHigh = MassMu + 3 * MassSigma;
  // float MassLow = MassMu - 3 * MassSigma;

  TRandom3 *randomGenerator = new TRandom3();

  for (int ev = 0; ev < NumEvts; ev++)
  {
    BTree->GetEntry(ev);

    if (ev % 100000 == 0)
      cout << "Executing event " << ev << endl;

    // if (jet_pt > 50. && jet_pt < 52.)
    // {
    //   cout << eventNumber << endl;
    //   cout << jet_pt << ", " << jet_rap << ", " << HF_pt << endl;
    // }
    TLorentzVector HFmeson, HFjet, mum, mup, Kmeson, Jpsi, Bfromjet;
    TLorentzVector tr_HFmeson, tr_HFjet, tr_mum, tr_mup, tr_Kmeson, tr_Jpsi;
    HFjet.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
    mup.SetPxPyPzE(mup_px, mup_py, mup_pz, mup_e);
    mum.SetPxPyPzE(mum_px, mum_py, mum_pz, mum_e);
    Kmeson.SetPxPyPzE(K_px, K_py, K_pz, K_e);
    Bfromjet.SetPxPyPzE(Bfromjet_px, Bfromjet_py, Bfromjet_pz, Bfromjet_e);

    bool pt_cond = (jet_pt > pTLow);
    bool rap_cond = (jet_rap > etaMin && jet_rap < etaMax);

    if (!TOS)
      continue;
    if (!pt_cond || !rap_cond)
      continue;

    bool StrippingCuts = false;
    if (StrippingCuts)
    {
      if (mup_CHI2NDOF > 4 || mum_CHI2NDOF > 4 || K_CHI2NDOF > 4)
        continue;
      if (mup_GHOSTPROB > 0.4 || mum_GHOSTPROB > 0.4 || K_GHOSTPROB > 0.4)
        continue;
      if (mup_IPCHI2 < 25 || mum_IPCHI2 < 25 || K_IPCHI2 < 25)
        continue;
    }

    tr_HFjet.SetPxPyPzE(tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e);
    tr_mup.SetPxPyPzE(tr_mup_px, tr_mup_py, tr_mup_pz, tr_mup_e);
    tr_mum.SetPxPyPzE(tr_mum_px, tr_mum_py, tr_mum_pz, tr_mum_e);
    tr_Kmeson.SetPxPyPzE(tr_K_px, tr_K_py, tr_K_pz, tr_K_e);
    tr_HFmeson = tr_mup + tr_mum + tr_Kmeson;
    tr_Jpsi = tr_mup + tr_mum;
    // HFmeson = mup + mum + Kmeson;
    HFmeson.SetPxPyPzE(HF_px, HF_py, HF_pz, HF_e);
    Jpsi = mup + mum;
    float HF_eta = HFmeson.Eta();
    
    float frag_z = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
    float frag_jt = HFmeson.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
    float frag_r = HFmeson.DeltaR(HFjet, true);
    

    float event_weight = 1.0;

    float reweight = 1.0;
    float emission_weight = 1.0;
    float event_eff = 1.0;
    float event_pur = 1.0;
    float event_eff_ptz = 1.0;
    float event_pur_ptz = 1.0;
    float sv_weight = 1.0;
    float sv_eff = 1.0;
    float sv_pur = 1.0;
    float bkg_weight = h1_BkgScale != NULL ? h1_BkgScale->GetBinContent(h1_BkgScale->FindBin(HFmeson.Pt())) : 1.0;
    float MassHigh = h1_MassMax != NULL ? h1_MassMax->GetBinContent(h1_MassMax->FindBin(HFmeson.Pt())) : 5.31;
    float MassLow = h1_MassMin != NULL ? h1_MassMin->GetBinContent(h1_MassMin->FindBin(HFmeson.Pt())) : 5.24;

    float Sideband1Min = h1_Sideband1Min != NULL ? h1_Sideband1Min->GetBinContent(h1_Sideband1Min->FindBin(HFmeson.Pt())) : 5.24;
    float Sideband1Max = h1_Sideband1Max != NULL ? h1_Sideband1Max->GetBinContent(h1_Sideband1Max->FindBin(HFmeson.Pt())) : 5.31;
    float Sideband2Min = h1_Sideband2Min != NULL ? h1_Sideband2Min->GetBinContent(h1_Sideband2Min->FindBin(HFmeson.Pt())) : 5.24;
    float Sideband2Max = h1_Sideband2Max != NULL ? h1_Sideband2Max->GetBinContent(h1_Sideband2Max->FindBin(HFmeson.Pt())) : 5.31;

    // cout << HFmeson.Pt() << ", " << MassLow << ", " << MassHigh << ", " << Sideband1Min << ", " << Sideband1Max << ", " << Sideband2Min << ", " << Sideband2Max << endl;
    if (DoMassFit == 1)
    {
      TH1D *h1_Sideband1Min_forSysNear = (TH1D *)f_massfit.Get("h1_Sideband1Min_forSysNear");
      TH1D *h1_Sideband1Max_forSysNear = (TH1D *)f_massfit.Get("h1_Sideband1Max_forSysNear");
      TH1D *h1_Sideband2Min_forSysNear = (TH1D *)f_massfit.Get("h1_Sideband2Min_forSysNear");
      TH1D *h1_Sideband2Max_forSysNear = (TH1D *)f_massfit.Get("h1_Sideband2Max_forSysNear");
      Sideband1Min = h1_Sideband1Min_forSysNear != NULL ? h1_Sideband1Min_forSysNear->GetBinContent(h1_Sideband1Min_forSysNear->FindBin(HFmeson.Pt())) : 5.24;
      Sideband1Max = h1_Sideband1Max_forSysNear != NULL ? h1_Sideband1Max_forSysNear->GetBinContent(h1_Sideband1Max_forSysNear->FindBin(HFmeson.Pt())) : 5.31;
      Sideband2Min = h1_Sideband2Min_forSysNear != NULL ? h1_Sideband2Min_forSysNear->GetBinContent(h1_Sideband2Min_forSysNear->FindBin(HFmeson.Pt())) : 5.24;
      Sideband2Max = h1_Sideband2Max_forSysNear != NULL ? h1_Sideband2Max_forSysNear->GetBinContent(h1_Sideband2Max_forSysNear->FindBin(HFmeson.Pt())) : 5.31;
      bkg_weight = h1_BkgScale_forSysNear != NULL ? h1_BkgScale_forSysNear->GetBinContent(h1_BkgScale_forSysNear->FindBin(HFmeson.Pt())) : 1.0;
    }
    if (DoMassFit == 2)
    {
      TH1D *h1_Sideband1Min_forSysFar = (TH1D *)f_massfit.Get("h1_Sideband1Min_forSysFar");
      TH1D *h1_Sideband1Max_forSysFar = (TH1D *)f_massfit.Get("h1_Sideband1Max_forSysFar");
      TH1D *h1_Sideband2Min_forSysFar = (TH1D *)f_massfit.Get("h1_Sideband2Min_forSysFar");
      TH1D *h1_Sideband2Max_forSysFar = (TH1D *)f_massfit.Get("h1_Sideband2Max_forSysFar");
      Sideband1Min = h1_Sideband1Min_forSysFar != NULL ? h1_Sideband1Min_forSysFar->GetBinContent(h1_Sideband1Min_forSysFar->FindBin(HFmeson.Pt())) : 5.24;
      Sideband1Max = h1_Sideband1Max_forSysFar != NULL ? h1_Sideband1Max_forSysFar->GetBinContent(h1_Sideband1Max_forSysFar->FindBin(HFmeson.Pt())) : 5.31;
      Sideband2Min = h1_Sideband2Min_forSysFar != NULL ? h1_Sideband2Min_forSysFar->GetBinContent(h1_Sideband2Min_forSysFar->FindBin(HFmeson.Pt())) : 5.24;
      Sideband2Max = h1_Sideband2Max_forSysFar != NULL ? h1_Sideband2Max_forSysFar->GetBinContent(h1_Sideband2Max_forSysFar->FindBin(HFmeson.Pt())) : 5.31;
      bkg_weight = h1_BkgScale_forSysFar != NULL ? h1_BkgScale_forSysFar->GetBinContent(h1_BkgScale_forSysFar->FindBin(HFmeson.Pt())) : 1.0;
    }
    
    
    // cout << "Mass Range = [" << MassLow << ", " << MassHigh << "]"
    //      << ", " << HFmeson.Pt() << endl;
    // cout << bkg_weight << ", " << MassLow << ", " << MassHigh << endl;

    bool PID_cond = (K_PIDK > 0);
    bool DTF_cond = (chi2ndf_dtf < 9) && (tau_dtf > 0.3);
    bool mass_cond = (bmass_dtf > MassLow && bmass_dtf < MassHigh);
    bool bkg_cond = (bmass_dtf > Sideband1Min && bmass_dtf < Sideband1Max) || (bmass_dtf > Sideband2Min && bmass_dtf < Sideband2Max);
    bool gluon_cond = mass_cond && Hasbbbar;
    bool SV_cond = (nSV > 0) && mass_cond && sv_mass > 0.4;
    bool signal_cond = mass_cond;
    if (DTF_cut)
    {
      signal_cond = signal_cond && DTF_cond;
      bkg_cond = bkg_cond && DTF_cond;
      SV_cond = SV_cond && DTF_cond;
    }
    if (PID_cut && isData)
    {
      signal_cond = signal_cond && PID_cond;
      bkg_cond = bkg_cond && PID_cond;
      SV_cond = SV_cond && PID_cond;
    }

    // if (h2_efficiency_HFptjetpt != NULL && h2_purity_HFptjetpt != NULL)
    // {
    //   event_eff = h2_efficiency_HFptjetpt->GetBinContent(h2_efficiency_HFptjetpt->GetXaxis()->FindBin(HFmeson.Pt()), h2_efficiency_HFptjetpt->GetYaxis()->FindBin(HFjet.Pt()));
    //   event_pur = h2_purity_HFptjetpt->GetBinContent(h2_purity_HFptjetpt->GetXaxis()->FindBin(HFmeson.Pt()), h2_purity_HFptjetpt->GetYaxis()->FindBin(HFjet.Pt()));
    // }

    if (h3_efficiency_HFptetajetpt != NULL && h3_purity_HFptetajetpt != NULL)
    {
      event_eff = h3_efficiency_HFptetajetpt->GetBinContent(h3_efficiency_HFptetajetpt->GetXaxis()->FindBin(HFmeson.Pt()), h3_efficiency_HFptetajetpt->GetYaxis()->FindBin(HFmeson.Rapidity()), h3_efficiency_HFptetajetpt->GetZaxis()->FindBin(HFjet.Pt()));
      event_pur = h3_purity_HFptetajetpt->GetBinContent(h3_purity_HFptetajetpt->GetXaxis()->FindBin(HFmeson.Pt()), h3_efficiency_HFptetajetpt->GetYaxis()->FindBin(HFmeson.Rapidity()), h3_purity_HFptetajetpt->GetZaxis()->FindBin(HFjet.Pt()));
    }
    
    if (h2_efficiency_ptz != NULL && h2_purity_ptz != NULL)
    {
      event_eff_ptz = h2_efficiency_ptz->GetBinContent(h2_efficiency_ptz->GetXaxis()->FindBin(z), h2_efficiency_ptz->GetYaxis()->FindBin(HFjet.Pt()));
      event_pur_ptz = h2_purity_ptz->GetBinContent(h2_purity_ptz->GetXaxis()->FindBin(z), h2_efficiency_ptz->GetYaxis()->FindBin(HFjet.Pt()));
    }
        
    //std::cout << " event_eff : " << event_eff << " event_pur : " << event_pur << std::endl;

    if (h2_SVTag_eff != NULL)
    {
      sv_eff = h2_SVTag_eff_z->GetBinContent(h2_SVTag_eff_z->GetXaxis()->FindBin(HFmeson.Pt() / HFjet.Pt()), h2_SVTag_eff_z->GetYaxis()->FindBin(HFjet.Pt()));
      sv_pur = h2_SVTag_pur_z->GetBinContent(h2_SVTag_pur_z->GetXaxis()->FindBin(HFmeson.Pt() / HFjet.Pt()), h2_SVTag_pur_z->GetYaxis()->FindBin(HFjet.Pt()));
    }

    sv_weight = sv_pur / sv_eff;
//      cout<< "SV Weight"<< sv_weight << endl;

    if (DoTrackEff == 1)
    {
      trkeff_K = trkeff_K + trkeff_K_errhi;
      trkeff_K = (1 + 0.0127) * trkeff_K; // Material Budget of 1.27% on Kaons
      trkeff_mum = trkeff_mum + trkeff_mum_errhi;
      trkeff_mup = trkeff_mup + trkeff_mup_errhi;
    }
    else if (DoTrackEff == 2)
    {
      trkeff_K = trkeff_K - trkeff_K_errlo;
      trkeff_K = (1 - 0.0127) * trkeff_K; // Material Budget of 1.27% on Kaons
      trkeff_mum = trkeff_mum - trkeff_mum_errlo;
      trkeff_mup = trkeff_mup - trkeff_mup_errlo;
      // cout << trkeff_K << ", " << trkeff_mum << ", " << trkeff_mup << endl;
      // if (trkeff_K_errhi > 0.02 || trkeff_mup_errhi > 0.02 || trkeff_mum_errhi > 0.02)
      //   cout << trkeff_mum_errhi << ", " << trkeff_mup_errhi << ", " << trkeff_K_errhi << endl;

      if (trkeff_K_errlo > 0.1 || trkeff_mup_errlo > 0.1 || trkeff_mum_errlo > 0.1)
      {
        cout << trkeff_K << endl;
        cout << trkeff_mum_errlo << ", " << trkeff_mup_errlo << ", " << trkeff_K_errlo << endl;
        cout << mup.Pt() << ", " << mup.Eta() << endl;
        cout << mum.Pt() << ", " << mum.Eta() << endl;
        cout << Kmeson.P() << ", " << Kmeson.Eta() << endl;
      }
    }
    if (DoPIDEff == 1)
    {
      pideff_K = pideff_K + pideff_K_err;
      pideff_mum = pideff_mum + pideff_mum_err;
      pideff_mup = pideff_mup + pideff_mup_err;
    }
    else if (DoPIDEff == 2)
    {
      pideff_K = pideff_K - pideff_K_err;
      pideff_mum = pideff_mum - pideff_mum_err;
      pideff_mup = pideff_mup - pideff_mup_err;
    }
    if (DoRecSelEff)
    {
      // cout << Bu_IPCHI2 << ", " << Bu_CHI2 << ", " << Jpsi_CHI2 << ", " << Jpsi_CHI2NDOF << ", " << sqrt(Jpsi_FDCHI2) << endl;
      if (Bu_IPCHI2 > 22)
        continue;
      if (Bu_CHI2 > 42)
        continue;
      if (Jpsi_CHI2 > 22)
        continue;
      if (Jpsi_CHI2NDOF > 18)
        continue;
      if (fabs(Jpsi_BPVDLS) < 2.8)
        continue;
    }

    if (DoTrigEff == 1)
    {
      double trig_var = h2_trig_ratio->GetBinContent(h2_trig_ratio->GetXaxis()->FindBin(HFmeson.Pt()), h2_trig_ratio->GetYaxis()->FindBin(HFmeson.Rapidity()));
      double trig_err = h2_trig_ratio->GetBinError(h2_trig_ratio->GetXaxis()->FindBin(HFmeson.Pt()), h2_trig_ratio->GetYaxis()->FindBin(HFmeson.Rapidity()));
      trig_var = fabs(1.0 - trig_var);
      trig_var = (trig_err > trig_var) ? trig_err : trig_var;
      trigeff_ratio = trigeff_ratio * (1 + trig_var);
    }
    if (DoTrigEff == 2)
    {
      double trig_var = h2_trig_ratio->GetBinContent(h2_trig_ratio->GetXaxis()->FindBin(HFmeson.Pt()), h2_trig_ratio->GetYaxis()->FindBin(HFmeson.Rapidity()));
      double trig_err = h2_trig_ratio->GetBinError(h2_trig_ratio->GetXaxis()->FindBin(HFmeson.Pt()), h2_trig_ratio->GetYaxis()->FindBin(HFmeson.Rapidity()));
      trig_var = fabs(1.0 - trig_var);
      trig_var = (trig_err > trig_var) ? trig_err : trig_var;
      trigeff_ratio = trigeff_ratio * (1 - trig_var);
    }

      
//    cout << " ------------------------------------------------ " << endl;
//     cout << "Evt Pur:"<< event_pur << ", Event Eff:" << event_eff << endl;
//     cout << "Trk Eff (K, mum, mup):" << trkeff_K << ", " << trkeff_mum << ", " << trkeff_mup << endl;
//     cout << "PID Eff (K, mum, mup):" << pideff_K << ", " << pideff_mum << ", " << pideff_mup << endl;
//     cout << "Trig Eff (K, mum, mup):" << trigeff_ratio << endl;
//      cout << " ------------------------------------------------ " << endl;
      
    //event_weight = event_pur / (event_eff * trkeff_K * trkeff_mum * trkeff_mup * pideff_mum * pideff_mup * trigeff_ratio);
    
    //event_weight = event_pur_ptz / (event_eff_ptz * trkeff_K * trkeff_mum * trkeff_mup * pideff_mum * pideff_mup * trigeff_ratio);    
      
    event_weight *= (1./ trkeff_K * trkeff_mum * trkeff_mup * pideff_mum * pideff_mup * trigeff_ratio);   
    
    //if (PID_cut)
    //  event_weight *= (1. / (pideff_K));
    
    // if (sv_weight == 0 && (nSV > 0))
    // cout << HFjet.Pt() << "," << HFmeson.Pt() << endl;
    if (std::isinf(event_weight) || std::isnan(event_weight))
      event_weight = 1.0;
    if (std::isnan(sv_weight) || std::isinf(sv_weight))
      sv_weight = 1.0;

    //std::cout << "event weight : " << event_weight << std::endl;
    //std::cout << "event purity : " << event_pur << std::endl;
    //std::cout << "event_efficiency : " << event_eff << std::endl;
    //std::cout << "PID_cut : " << PID_cut  << std::endl;

    h2_jetpteta->Fill(jet_pt, jet_eta);

    // if (!isData)
    // {
    //   if (NumBHads_tr > 1)
    //     continue;
    // }
    // if (!isData)
    // {

    // }

    // bool signal_cond = true;

    float dphi_HF_jet = checkphi(checkphi(HFmeson.Phi()) - checkphi(HFjet.Phi()));
    float dy_HF_jet = HFjet.Eta() - HFmeson.Rapidity();
    h2_jetpt_HFpt->Fill(HFmeson.Pt(), HFjet.Pt());
    // h1_HF_mass->Fill(HFmeson.M());
    h1_HF_mass->Fill(bmass_dtf);
    if (DTF_cond)
      h1_HF_mass_dtfcut->Fill(bmass_dtf);

    if (mass_cond)
    {
      if (jet_pt > ptMin)
        h1_z_tot->Fill(z);
        h1_jt_tot->Fill(jt);
        h1_r_tot->Fill(r);
    }
    if (bkg_cond)
    {
      // if (nSV > 0 && sv_mass > 0.4)
      //   cout << "bkg SV!";

      h1_z_comb->Fill(z, event_weight * bkg_weight);
      h1_jt_comb->Fill(jt, event_weight * bkg_weight);
      h1_r_comb->Fill(r, event_weight * bkg_weight);
        
      h2_zjt_comb->Fill(z, jt, event_weight * bkg_weight);
      h2_zr_comb->Fill(z, r, event_weight * bkg_weight);
      h2_jtr_comb->Fill(jt, r, event_weight * bkg_weight);

      h2_ptz_comb->Fill(z, jet_pt, event_weight * bkg_weight);
      h2_ptjt_comb->Fill(jt, jet_pt, event_weight * bkg_weight);
      h2_ptr_comb->Fill(r, jet_pt, event_weight * bkg_weight);
        
      h3_ptzjt_comb->Fill(z, jt, jet_pt, event_weight * bkg_weight);
      h3_ptzr_comb->Fill(z, jt, jet_pt, event_weight * bkg_weight);
      h3_ptjtr_comb->Fill(jt, r,  jet_pt, event_weight * bkg_weight);

      h1_nJetDtrs_noghost_comb->Fill(ndtrs);
      h1_jet_pt_comb->Fill(jet_pt, event_weight * bkg_weight);
        
    }
    if (SV_cond)
    {
      float frag_z_SV = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
      // float frag_z_SV = HFmeson.Pt() / HFjet.Pt();
      // if (jet_pt > ptMin)
//     h2_frag_z_jetpt_SV->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt(), event_weight * sv_weight)
      float frag_jt_SV = HFmeson.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
      float frag_r_SV = HFmeson.DeltaR(HFjet, true);
      
//      h1_z_SV->Fill(frag_z_SV, sv_weight);
//      h1_jt_SV->Fill(frag_jt_SV, sv_weight);
//      h1_r_SV->Fill(frag_r_SV, sv_weight);
//        
//      h2_zjt_SV->Fill(frag_z_SV, frag_jt_SV, sv_weight);
//      h2_zr_SV->Fill(frag_z_SV, frag_r_SV, sv_weight);
//      h2_jtr_SV->Fill(frag_jt_SV, frag_r_SV, sv_weight);
//        
//      h2_ptz_SV->Fill(frag_z_SV, HFjet.Pt(), event_weight * sv_weight);
//      h2_ptjt_SV->Fill(frag_jt_SV, HFjet.Pt(), event_weight * sv_weight);
//      h2_ptr_SV->Fill(frag_r_SV, HFjet.Pt(), event_weight * sv_weight);
        
        h1_z_SV->Fill(frag_z_SV);
        h1_jt_SV->Fill(frag_jt_SV);
        h1_r_SV->Fill(frag_r_SV);
          
        h2_zjt_SV->Fill(frag_z_SV, frag_jt_SV);
        h2_zr_SV->Fill(frag_z_SV, frag_r_SV);
        h2_jtr_SV->Fill(frag_jt_SV, frag_r_SV);
          
        h2_ptz_SV->Fill(frag_z_SV, HFjet.Pt());
        h2_ptjt_SV->Fill(frag_jt_SV, HFjet.Pt());
        h2_ptr_SV->Fill(frag_r_SV, HFjet.Pt());
    
        h1_dphi_SV->Fill(dphi);
        h1_nJetDtrs_noghost_SV->Fill(ndtrs);
        h1_jet_pt_SV->Fill(jet_pt);

        // h1_HF_ipchi2_SV->Fill(log10(ipchi2));
    }
    if (signal_cond)
    {
       
      h2_Ndtr_jetpt_neutral->Fill(Ndtr_neutral, HFjet.Pt(), event_weight);
      h2_Ndtr_jetpt_charged->Fill(Ndtr_charged, HFjet.Pt(), event_weight);
      h2_Ndtr_jetpt->Fill(Ndtr_neutral + Ndtr_charged, HFjet.Pt(), event_weight);
     
        for (int i = 0; i < dtr_pt->size(); i++)
        {
            if (dtr_3charge->at(i) == 0 && dtr_id->at(i) != 22)
                h1_dtr_pt->Fill(dtr_pt->at(i));
        }
      
        
      if (HFHardest)
        N_hardest++;
      else
        N_NotHardest++;
      h1_dphi->Fill(dphi);

      h1_nJetDtrs->Fill(ndtrs);
      h1_nJetDtrs_noghost->Fill(ndtrs_noghost);
      h1_jet_pt->Fill(jet_pt, event_weight);
      h1_jet_pt_fine->Fill(jet_pt);
      h1_jet_eta->Fill(jet_eta);
      h1_jet_rap->Fill(jet_rap);

      if (HFjet.Pt() > ptMin && HFjet.Pt() < ptMax)
        h1_HFpt->Fill(HFmeson.Pt());
      h2_HFptjetpt->Fill(HFmeson.Pt(), HFjet.Pt(), event_weight);
      h1_HFjet_ptbalance->Fill(jet_pt / HFmeson.Pt());

      h2_HFptrap->Fill(HFmeson.Pt(), HFmeson.Rapidity());
      h3_HFptjetptrap->Fill(HFmeson.Pt(), HFjet.Pt(), HFjet.Rapidity());

      h1_Jpsi_mass->Fill(Jpsi.M());
      h1_Jpsi_pt->Fill(Jpsi.Pt());
      h1_Jpsi_rap->Fill(Jpsi.Rapidity());
      h1_Jpsi_ipchi2->Fill(jpsi_ipchi2);

//      h1_nsplittings->Fill(kts->size());
      h1_HF_rap->Fill(HFmeson.Rapidity());
      h1_HF_pt->Fill(HFmeson.Pt());

      if (tr_jet_pt > 10.)
        h1_jet_ptbalance->Fill((jet_pt - tr_jet_pt) / tr_jet_pt);

      // h1_HF_ipchi2->Fill(log10(ipchi2));
    }
    if (gluon_cond)
    {
      float frag_z_gluon = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
      float frag_jt_gluon = HFmeson.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
      float frag_r_gluon = HFmeson.DeltaR(HFjet, true);
        
      if (jet_pt > ptMin)
        h1_z_gluon->Fill(frag_z_gluon);
  
      h1_jt_gluon->Fill(frag_jt_gluon);
      h1_r_gluon->Fill(frag_r_gluon);
        
      h2_zjt_gluon->Fill(frag_z_gluon, frag_jt_gluon);
      h2_zr_gluon->Fill(frag_z_gluon, frag_r_gluon);
      h2_jtr_gluon->Fill(frag_r_gluon, frag_jt_gluon);
  
      h2_ptz_gluon->Fill(frag_z_gluon, jet_pt) ;
      h2_ptjt_gluon->Fill(frag_jt_gluon, jet_pt) ;
      h2_ptr_gluon->Fill(frag_r_gluon, jet_pt);
        
      h1_dphi_gluon->Fill(dphi);

      NumTwoHFInJet++;
      // h1_HF_ipchi2_gluon->Fill(log10(ipchi2));
    }

    float frag_z_Bfromjet = Bfromjet.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
    float frag_jt_Bfromjet = Bfromjet.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
    float frag_r_Bfromjet = Bfromjet.DeltaR(HFjet, true);
    
    h1_z_Bfromjet->Fill(frag_z_Bfromjet);
    h1_jt_Bfromjet->Fill(frag_jt_Bfromjet);
    h1_r_Bfromjet->Fill(frag_r_Bfromjet);

    if (isTrueBjet)
    {
      h1_tr_z->Fill(tr_z);
      h1_tr_jt->Fill(tr_jt);
      h1_tr_r->Fill(tr_r);
      h1_tr_jet_pt->Fill(tr_jet_pt);
    }


    if (signal_cond)
    {
        h3_ptzjt->Fill(z, jt, jet_pt, event_weight);
        h3_ptzr->Fill(z, r, jet_pt, event_weight);
        h3_ptjtr->Fill(jt, r, jet_pt, event_weight);
        
        h3_ptzjt_unweight->Fill(z, jt, jet_pt, event_weight);
        h3_ptzr_unweight->Fill(z, r, jet_pt, event_weight);
        h3_ptjtr_unweight->Fill(jt, r, jet_pt,  event_weight);


        h2_ptz->Fill(z, jet_pt, event_weight);
        h2_ptjt->Fill(jt, jet_pt, event_weight);
        h2_ptr->Fill(r, jet_pt, event_weight);
        
        h3_ptzjt_50_100->Fill(z, jt, jet_pt, event_weight);
        h3_ptzr_50_100->Fill(z, r, jet_pt, event_weight);
        h3_ptjtr_50_100->Fill(jt, r, jet_pt, event_weight);


        h2_ptz_50_100->Fill(z, jet_pt, event_weight);
        h2_ptjt_50_100->Fill(jt, jet_pt, event_weight);
        h2_ptr_50_100->Fill(r, jet_pt, event_weight);    
             

        h2_ptHFz->Fill(z, HF_pt);
        h2_ptHFjt->Fill(jt, HF_pt);
        h2_ptHFr->Fill(r, HF_pt);      
        
        h1_z->Fill(z, event_weight);
        h1_jt->Fill(jt, event_weight);
        h1_r->Fill(r, event_weight);
        
        h2_zjt->Fill(z, jt, event_weight);
        h2_zr->Fill(z, r, event_weight);
        h2_jtr->Fill(jt, r, event_weight);
        
        h1_z_nobgsub->Fill(z, event_weight);
        h1_jt_nobgsub->Fill(jt, event_weight);
        h1_r_nobgsub->Fill(r, event_weight);
        
        h2_ptz_nobgsub->Fill(z, jet_pt, event_weight);
        h2_ptjt_nobgsub->Fill(jt, jet_pt, event_weight);
        h2_ptr_nobgsub->Fill(r, jet_pt, event_weight);
              

        double prior_weight = 1.0;
        if (!isData) 
        {
          prior_weight = h3_ptzjt_ratio->GetBinContent(h3_ptzjt_ratio->GetXaxis()->FindBin(z),
                                                       h3_ptzjt_ratio->GetYaxis()->FindBin(jt),
                                                       h3_ptzjt_ratio->GetZaxis()->FindBin(jet_pt));
        }
        // For a cross check on the unfold prior systematic
        h2_ptz_weighted->Fill(z, jet_pt, prior_weight);
        h2_ptjt_weighted->Fill(jt, jet_pt, prior_weight);
        h2_ptr_weighted->Fill(r, jet_pt, prior_weight);  
        h1_z_weighted->Fill(z, prior_weight);
        h1_jt_weighted->Fill(jt, prior_weight);
        h1_r_weighted->Fill(r, prior_weight);   
                
        if (HF_pt < 5.) { h1_z_ptHFcut_l5->Fill(z); }        
        else { h1_z_ptHFcut_g5->Fill(z); }

      }
  
    
    bool gluon_splitting;
    // if (isData)
    //   gluon_splitting = SV_cond;
    // else
    //   gluon_splitting = gluon_cond;


//    if (!isData)
//    {
//  
//    }
      
  }

  ///////////////// ////////////////
  // Background Subtraction
  ////////////// ////////////////
  cout << "Before sub: " << endl;
  cout << "Num Jet pt = " << h1_jet_pt->Integral() << endl;
  cout << "Int ptzjt = " << h3_ptzjt->Integral() << endl;
  cout << "Int ptzr = " << h3_ptzr->Integral() << endl;
  cout << "Int ptjtr = " << h3_ptjtr->Integral() << endl;


  if (isData)
  {
  
    // Why don't we call MakeHistPositive on the 1D distributions?
    h1_jet_pt->Add(h1_jet_pt_comb, -1);
 

                        
    h1_z->Add(h1_z_comb, -1);
    h1_jt->Add(h1_jt_comb, -1);
    h1_r->Add(h1_r_comb, -1);
    
    h2_zjt->Add(h2_zjt_comb, -1);
    MakeHistPositive(h2_zjt);
    h2_zr->Add(h2_zr_comb, -1);
    MakeHistPositive(h2_zr);
    h2_jtr->Add(h2_jtr_comb, -1);
    MakeHistPositive(h2_jtr);
 
    h2_ptz->Add(h2_ptz_comb, -1);
    MakeHistPositive(h2_ptz);    
    h2_ptjt->Add(h2_ptjt_comb, -1);
    MakeHistPositive(h2_ptjt);
    h2_ptr->Add(h2_ptr_comb, -1);
    MakeHistPositive(h2_ptr); 
      
    h3_ptzjt->Add(h3_ptzjt_comb, -1);
    MakeHistPositive(h3_ptzjt);    
    h3_ptzr->Add(h3_ptzr_comb, -1);
    MakeHistPositive(h3_ptzr);
    h3_ptjtr->Add(h3_ptjtr_comb, -1);
    MakeHistPositive(h3_ptjtr);
           
  }
 
  // SetFeldmanErr(h3_ptktdR);
  // SetFeldmanErr(h3_ptzdR);
  cout << "After sub: " << endl;
  cout << "Num Jet pt = " << h1_jet_pt->Integral() << endl;
  cout << "Int ptzjt = " << h3_ptzjt->Integral() << endl;
  cout << "Int ptzr = " << h3_ptzr->Integral() << endl;
  cout << "Int ptjtr = " << h3_ptjtr->Integral() << endl;

  cout << event_counter << " events processed" << endl;
  cout << "NumJets_zdR = " << NumJets_zdR << endl;
  cout << "NumJets_ktdR = " << NumJets_ktdR << endl;
  cout << "N_SV = " << N_SV << endl;
  cout << "N_BacktoBack = " << N_BacktoBack << endl;
  cout << "N_SV_and_BacktoBack = " << N_SV_and_BacktoBack << endl;

  cout << "N_hardest = " << N_hardest << endl;
  cout << "N_NotHardest = " << N_NotHardest << endl;

  cout << "Num TWO HF in Jet = " << NumTwoHFInJet << endl;
  cout << "Num More than 1 jet in event = " << NumTwoCand << endl;


    //////// Unfolding Attempt -- Observables ///// / /

    TH2D *h2_ptz_final = (TH2D *)h2_ptz->Clone("ptz_final");
    TH2D *h2_ptjt_final = (TH2D *)h2_ptjt->Clone("ptjt_final");
    TH2D *h2_ptr_final = (TH2D *)h2_ptr->Clone("ptr_final");
    
    cout << " ------------------------------------------------ " << endl;
    cout << "Integrals before ptz: " << h2_ptz_final->Integral() << endl;
    cout << "Integrals before ptjt: " << h2_ptjt_final->Integral()  << endl;
    cout << "Integrals before ptr: " << h2_ptr_final->Integral()  << endl;
    cout << " ------------------------------------------------ " << endl;
    
    // Correct for purities (if event weight is off)
    h2_ptz_final->Multiply(h2_ptz_final, h2_purity_ptz);
    h2_ptjt_final->Multiply(h2_ptjt_final, h2_purity_ptjt);
    h2_ptr_final->Multiply(h2_ptr_final, h2_purity_ptr);
    
    cout << " ------------------------------------------------ " << endl;
    cout << "Integrals After Pur ptz: " << h2_ptz_final->Integral() << endl;
    cout << "Integrals After Pur ptjt: " << h2_ptjt_final->Integral()  << endl;
    cout << "Integrals After Pur ptr: " << h2_ptr_final->Integral()  << endl;
    cout << " ------------------------------------------------ " << endl;
    
    int NumIters = 4;
    RooUnfoldBayes unfold_ptz(response_ptz, h2_ptz_final, NumIters);
    RooUnfoldBayes unfold_ptjt(response_ptjt, h2_ptjt_final, NumIters);
    RooUnfoldBayes unfold_ptr(response_ptr, h2_ptr_final, NumIters);
    
    cout << "Unfold successful" << endl;
    
    /////////////////////   Get Unfolded Distribution /////////////////////////////////

    h2_ptz_final = (TH2D *)unfold_ptz.Hreco();
    h2_ptjt_final = (TH2D *)unfold_ptjt.Hreco();
    h2_ptr_final = (TH2D *)unfold_ptr.Hreco();
    
    cout << " ------------------------------------------------ " << endl;
    cout << "Integrals after Unfold ptz: " << h2_ptz_final->Integral() << endl;
    cout << "Integrals after Unfold ptjt: " << h2_ptjt_final->Integral()  << endl;
    cout << "Integrals after Unfold ptr: " << h2_ptr_final->Integral()  << endl;
    cout << " ------------------------------------------------ " << endl;
    
    ///////////////////  Correct for efficiency if needed /////////////////////////////////
    h2_ptz_final->Divide(h2_ptz_final, h2_efficiency_ptz);
    h2_ptjt_final->Divide(h2_ptjt_final, h2_efficiency_ptjt);
    h2_ptr_final->Divide(h2_ptr_final, h2_efficiency_ptr);

    cout << " ------------------------------------------------ " << endl;
    cout << "Integrals after eff ptz: " << h2_ptz_final->Integral() << endl;
    cout << "Integrals after eff ptjt: " << h2_ptjt_final->Integral()  << endl;
    cout << "Integrals after eff ptr: " << h2_ptr_final->Integral()  << endl;
    cout << " ------------------------------------------------ " << endl;
    
  SetRecoStyle(h1_jet_eta);
  SetDataStyle(h1_jet_rap);
  SetRecoStyle(h1_jet_pt);
  SetRecoStyle(h1_HF_rap);
  SetRecoStyle(h1_HF_pt);
  SetRecoStyle(h1_HF_mass);
    
  SetRecoStyle(h1_z);
  SetRecoStyle(h1_jt);
  SetRecoStyle(h1_r);
    
  SetRecoStyle(h1_jet_ptbalance);

  SetRecoStyle(h1_Jpsi_rap);
  SetRecoStyle(h1_Jpsi_pt);
  SetRecoStyle(h1_Jpsi_mass);
  SetRecoStyle(h1_Jpsi_ipchi2);

  SetTruthStyle(h1_tr_jet_pt);
  SetTruthStyle(h1_tr_z);
  SetTruthStyle(h1_tr_jt);
  SetTruthStyle(h1_tr_r);

  SetRecoStyle(h1_z_comb);
  SetRecoStyle(h1_jt_comb);
  SetRecoStyle(h1_r_comb);

  SetRecoStyle(h1_z_gluon);
  SetRecoStyle(h1_jt_gluon);
  SetRecoStyle(h1_r_gluon);

  // for(int j = 0; j<NumHists; j++){
  //   cout<<"NumJets ["<<MinErad+StepErad*j<<","<<MinErad+StepErad*(j+1)<<"] = "<<NumJets_allcuts_Erad[j]<<endl;
  //   // for(int k = 0; k<NumRbins;k++){
  //   //   h1_Rratios_vec[j][k]->Scale(1./NumJets_allcuts_Erad[j]);
  //   // }
  //   h1_Rratios[j]->Scale(1./NumJets_allcuts_Erad[j]);
  //   h1_tr_Rratios[j]->Scale(1./tr_NumJets_allcuts_Erad[j]);
  // }
  // for(int k = 0; k < NumRbins; k++){
  //   THStack *stack_temp = new THStack(Form("hs_R%d", k), "");
  //   // for(int j = 0; j< NumHists; j++){
  //   //   h1_Rratios_vec[j][k]->SetStats(0);
  //   //   stack_temp->Add(h1_Rratios_vec[j][k], "HIST");
  //   // }
  //   stack_R_vec.push_back(stack_temp);
  // }

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
  // gStyle->SetOptStat(0);
  // gStyle->SetPaperSize(TStyle::kUSLetter);
  // gStyle->SetPadBottomMargin(0.08);
  // gStyle->SetPadTopMargin(0.005);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetLabelSize(0.05, "X");
  gStyle->SetLabelSize(0.05, "Y");
  gStyle->SetTitleXSize(0.055);
  gStyle->SetTitleYSize(0.055);
  gStyle->SetTitleOffset(0.85, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetStatW(0.2);
  gStyle->SetPalette(kBird);
  gStyle->SetNumberContours(100);
  // gStyle->SetErrorX(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetStatStyle(0);
  // gStyle->SetLineWidth(3);

  //---- paint...
  char buf[100];
  char bufb[100];
    TString rootfile;
    TString plotfile;
    TString plotfilePDF;
    TString plotfileO;
    TString plotfileC;
    // TString OutputFileBase    = outbase+outinfo;
    TString plotextension = isData ? TString("../../plots/Bjets/") : TString("../../plots/BjetsMC/");
    rootfile = extension_RootFilesMC + extension + TString(".root");
    plotfile = plotextension + extension + TString(".ps");
    
    plotfilePDF = plotextension + extension + TString(".pdf");
    plotfileO = plotfilePDF + TString("(");
    plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0.06);
    gPad->SetRightMargin(0.15);
    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);

      
    auto legend_zpt_final = new TLegend(0.2, 0.6, 0.45, 0.8);
    legend_zpt_final ->SetTextSize(0.03);
    legend_zpt_final ->SetBorderSize(0);
    legend_zpt_final ->SetFillStyle(0);
    legend_zpt_final ->SetFillColor(3);
    legend_zpt_final->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptz_final->ProjectionX(Form("z_pt%d_final", i), i + 1, i + 1);
        
      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      h1_temp->SetMarkerColor(i-1 + 1);
      h1_temp->SetLineColor(i-1 + 1);
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
      //h1_temp->SetMinimum(0.0);
//      h1_temp->SetMaximum(3.5);
 
      legend_zpt_final->AddEntry(h1_temp, Form(" %.1f < Unfolded p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_zpt_final -> Draw("SAME");

    ccan[ican]->cd(2);
    auto legend_zpt_raw= new TLegend(0.25, 0.6, 0.5, 0.8);
    legend_zpt_raw ->SetTextSize(0.03);
    legend_zpt_raw ->SetBorderSize(0);
    legend_zpt_raw ->SetFillStyle(0);
    legend_zpt_raw ->SetFillColor(3);
    legend_zpt_raw ->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptz->ProjectionX(Form("htemp%d_ptz_raw", i), i + 1, i + 1);

      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
        h1_temp->SetMarkerStyle(i + 20);
        h1_temp->SetMarkerColor(i-1 + 1);
        h1_temp->SetLineColor(i-1 + 1);
        
        h1_temp->Draw("P E SAME");
        h1_temp->Draw("HIST SAME");
        //h1_temp->SetMinimum(0.0);
        //h1_temp->SetMaximum(3.5);
  
      legend_zpt_raw->AddEntry(h1_temp, Form(" %.1f < p_{T}^{Raw jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_zpt_raw -> Draw("SAME");
    
    ccan[ican]->cd(3);
    auto legend_zpt_truth = new TLegend(0.25, 0.6, 0.5, 0.8);
    legend_zpt_truth ->SetTextSize(0.03);
    legend_zpt_truth ->SetBorderSize(0);
    legend_zpt_truth ->SetFillStyle(0);
    legend_zpt_truth ->SetFillColor(3);
    legend_zpt_truth ->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp_truth = (TH1D *)h2_ptz_truth->ProjectionX(Form("htemp%d_ptz_truth", i), i + 1, i + 1);

      h1_temp_truth->SetStats(0);
      NormalizeHist(h1_temp_truth);
        h1_temp_truth->SetMarkerStyle(i + 20);
        h1_temp_truth->SetMarkerColor(i-1 + 1);
        h1_temp_truth->SetLineColor(i-1 + 1);
        
        h1_temp_truth->Draw("P E SAME");
        h1_temp_truth->Draw("HIST SAME");
        //h1_temp_truth->SetMinimum(0.0);
        //h1_temp_truth->SetMaximum(3.5);
  
      legend_zpt_truth->AddEntry(h1_temp_truth, Form(" %.1f < p_{T}^{Truth jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_zpt_truth -> Draw("SAME");
  
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
    
    // jT pT   
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->cd();    
    ccan[ican]->SetFillColor(10);    
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);       
    gPad->SetLogy();    
    auto legend_jtpt_final = new TLegend(0.45, 0.7, 0.7, 0.9);
    legend_jtpt_final ->SetTextSize(0.03);
    legend_jtpt_final ->SetBorderSize(0);
    legend_jtpt_final ->SetFillStyle(0);
    legend_jtpt_final ->SetFillColor(3);
    legend_jtpt_final->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt_final->ProjectionX(Form("jt_pt%d_final", i), i + 1, i + 1);
        
      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
      //h1_temp->Scale(1./h1_temp->Integral("width"));
      h1_temp->SetMarkerStyle(i + 20);
      h1_temp->SetMarkerColor(i-1 + 1);
      h1_temp->SetLineColor(i-1 + 1);

        
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
      //h1_temp->SetMinimum(0.0);
//      h1_temp->SetMaximum(3.5);
 
      legend_jtpt_final->AddEntry(h1_temp, Form(" %.1f < Unfolded p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_jtpt_final -> Draw("SAME");

    ccan[ican]->cd(2);
    gPad->SetLogy();        
    auto legend_jtpt_raw= new TLegend(0.45, 0.7, 0.7, 0.9);
    legend_jtpt_raw ->SetTextSize(0.03);
    legend_jtpt_raw ->SetBorderSize(0);
    legend_jtpt_raw ->SetFillStyle(0);
    legend_jtpt_raw ->SetFillColor(3);
    legend_jtpt_raw ->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt->ProjectionX(Form("htemp%d_ptjt_raw", i), i + 1, i + 1);

      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
 
        h1_temp->SetMarkerStyle(i + 20);
        h1_temp->SetMarkerColor(i-1 + 1);
        h1_temp->SetLineColor(i-1 + 1);
        
        h1_temp->Draw("P E SAME");
        h1_temp->Draw("HIST SAME");
        //h1_temp->SetMinimum(0.0);
        //h1_temp->SetMaximum(3.5);
  
      legend_jtpt_raw->AddEntry(h1_temp, Form(" %.1f < p_{T}^{Raw jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_jtpt_raw -> Draw("SAME");
    
    
    ccan[ican]->cd(3);
    gPad->SetLogy();        
    auto legend_jtpt_truth = new TLegend(0.45, 0.7, 0.7, 0.9);
    legend_jtpt_truth ->SetTextSize(0.03);
    legend_jtpt_truth ->SetBorderSize(0);
    legend_jtpt_truth ->SetFillStyle(0);
    legend_jtpt_truth ->SetFillColor(3);
    legend_jtpt_truth ->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp_truth = (TH1D *)h2_ptjt_truth->ProjectionX(Form("htemp%d_ptjt_truth", i), i + 1, i + 1);

      h1_temp_truth->SetStats(0);
      NormalizeHist(h1_temp_truth);
 
        h1_temp_truth->SetMarkerStyle(i + 20);
        h1_temp_truth->SetMarkerColor(i-1 + 1);
        h1_temp_truth->SetLineColor(i-1 + 1);
        
        h1_temp_truth->Draw("P E SAME");
        h1_temp_truth->Draw("HIST SAME");
        //h1_temp_truth->SetMinimum(0.0);
        //h1_temp_truth->SetMaximum(3.5);
  
      legend_jtpt_truth->AddEntry(h1_temp_truth, Form(" %.1f < p_{T}^{Truth jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_jtpt_truth -> Draw("SAME");

 
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
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->cd();    
    ccan[ican]->SetFillColor(10);    
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);     
    gPad->SetLogy();    
        
    auto legend_rpt_final = new TLegend(0.45, 0.7, 0.7, 0.9);
    legend_rpt_final ->SetTextSize(0.03);
    legend_rpt_final ->SetBorderSize(0);
    legend_rpt_final ->SetFillStyle(0);
    legend_rpt_final ->SetFillColor(3);
    legend_rpt_final->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr_final->ProjectionX(Form("r_pt%d_final", i), i + 1, i + 1);
        
      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
      h1_temp->SetMarkerStyle(i + 20);
      h1_temp->SetMarkerColor(i-1 + 1);
      h1_temp->SetLineColor(i-1 + 1);
      
        
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
      //h1_temp->SetMinimum(0.0);
//      h1_temp->SetMaximum(3.5);
 
      legend_rpt_final->AddEntry(h1_temp, Form(" %.1f < Unfolded p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_rpt_final -> Draw("SAME");

    ccan[ican]->cd(2);
    gPad->SetLogy();        
    auto legend_rpt_raw= new TLegend(0.45, 0.7, 0.7, 0.9);
    legend_rpt_raw ->SetTextSize(0.03);
    legend_rpt_raw ->SetBorderSize(0);
    legend_rpt_raw ->SetFillStyle(0);
    legend_rpt_raw ->SetFillColor(3);
    legend_rpt_raw ->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr->ProjectionX(Form("htemp%d_ptr_raw", i), i + 1, i + 1);

      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
 
        h1_temp->SetMarkerStyle(i + 20);
        h1_temp->SetMarkerColor(i-1 + 1);
        h1_temp->SetLineColor(i-1 + 1);
        
        h1_temp->Draw("P E SAME");
        h1_temp->Draw("HIST SAME");
        //h1_temp->SetMinimum(0.0);
        //h1_temp->SetMaximum(3.5);
  
      legend_rpt_raw->AddEntry(h1_temp, Form(" %.1f < p_{T}^{Raw jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_rpt_raw -> Draw("SAME");
    
    ccan[ican]->cd(3);
    gPad->SetLogy();        
    auto legend_rpt_truth = new TLegend(0.45, 0.7, 0.7, 0.9);
    legend_rpt_truth ->SetTextSize(0.03);
    legend_rpt_truth ->SetBorderSize(0);
    legend_rpt_truth ->SetFillStyle(0);
    legend_rpt_truth ->SetFillColor(3);
    legend_rpt_truth ->SetHeader("LHCb Unofficial","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp_truth = (TH1D *)h2_ptr_truth->ProjectionX(Form("htemp%d_ptr_truth", i), i + 1, i + 1);

      h1_temp_truth->SetStats(0);
      NormalizeHist(h1_temp_truth);
 
        h1_temp_truth->SetMarkerStyle(i + 20);
        h1_temp_truth->SetMarkerColor(i-1 + 1);
        h1_temp_truth->SetLineColor(i-1 + 1);
        
        h1_temp_truth->Draw("P E SAME");
        h1_temp_truth->Draw("HIST SAME");
        //h1_temp_truth->SetMinimum(0.0);
        //h1_temp_truth->SetMaximum(3.5);
  
      legend_rpt_truth->AddEntry(h1_temp_truth, Form(" %.1f < p_{T}^{Truth jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_rpt_truth -> Draw("SAME");
  
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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);

  // h1_frag_z_tot->SetStats(0);
  // SetDataStyle(h1_frag_z_tot);
  // h1_frag_z_tot->Draw("P E SAME");

  h1_z->SetStats(0);
  h1_z->SetXTitle("z");
  h1_z->SetYTitle("#frac{dN}{ dz} ");
  h1_z->SetMinimum(0.0);
  h1_z->SetMaximum(8000);
  SetRecoStyle(h1_z);
  h1_z->SetMarkerSize(0.7);

  h1_z->Draw("P E SAME");
//
//  h1_z_SV->SetStats(0);
//  SetTruthStyle(h1_z_SV);
//  h1_z_SV->Draw("P E SAME");

//  h1_z_gluon->SetStats(0);
//  h1_z_gluon->SetMarkerColor(kRed);
//  // SetDataStyle(h1_frag_z_gluon);
//  h1_z_gluon->Draw("P E SAME");

//  h1_z_comb->SetStats(0);
//  h1_z_comb->SetLineColor(38);
//  h1_z_comb->SetMarkerColor(38);
//  h1_z_comb->Draw("P E SAME");
    
  auto legend_z = new TLegend(0.25, 0.6, 0.45, 0.9);
    legend_z->SetBorderSize(0);
    legend_z->SetFillStyle(0);
    legend_z->SetFillColor(3);
    legend_z->SetHeader("LHCb Unofficial","C");
    legend_z->AddEntry(h1_z , "p_{T}^{jet} > 20 GeV/c");
//    legend_z->AddEntry(h1_z_SV, "SV");
////    legend_z->AddEntry(h1_z_gluon, "Gluons");
//    legend_z->AddEntry(h1_z_comb, "Comb.");

   legend_z->Draw("SAME");

  ccan[ican]->cd(2);

  // SetRecoStyle(h1_SVTag_eff);
  // h1_SVTag_eff->Draw("PE SAME");
  // h1_SVTag_eff->Draw("HIST SAME");

  // h2_thetaErad->Scale(1./NumJets);
  gPad->SetLogy();
  h1_jt->SetStats(0);
  h1_jt->SetXTitle("j_{T}");
  h1_jt->SetYTitle("#frac{dN}{ dj_{T} }");
  h1_jt->SetMaximum(120000);
  SetRecoStyle(h1_jt);
  h1_jt->SetMarkerSize(0.7);

  h1_jt->Draw("P E SAME");

//  h1_jt_SV->SetStats(0);
//  SetTruthStyle(h1_jt_SV);
//  h1_jt_SV->Draw("P E SAME");

//  h1_jt_gluon->SetStats(0);
//  SetDataStyle(h1_jt_gluon);
//  h1_jt_gluon->Draw("P E SAME");
//
//  h1_jt_comb->SetStats(0);
//    h1_jt_comb->SetLineColor(38);
//    h1_jt_comb->SetMarkerColor(38);
//  h1_jt_comb->Draw("SAME");
    
    auto legend_jt = new TLegend(0.6, 0.6, 0.8, 0.8);
      legend_jt->SetBorderSize(0);
      legend_jt->SetFillStyle(0);
      legend_jt->SetFillColor(3);
      legend_jt->SetHeader("LHCb Unofficial","C");
      legend_jt->AddEntry(h1_jt , "p_{T}^{jet} > 20 GeV/c");
//      legend_jt->AddEntry(h1_jt_SV, "SV");
//      legend_jt->AddEntry(h1_jt_gluon, "Gluons");
//      legend_jt->AddEntry(h1_jt_comb, "Comb.");
    legend_jt->Draw("SAME");

  ccan[ican]->cd(3);
    
  gPad->SetLogy();
  SetRecoStyle(h1_r);
  h1_r->SetStats(0);
  h1_r->SetMarkerSize(0.7);
  h1_r->SetMaximum(120000);
    h1_r->SetYTitle("#frac{dN}{ dr }");
  h1_r->Draw("P E SAME");

//  h1_r_SV->SetStats(0);
//  SetTruthStyle(h1_r_SV);
//  h1_r_SV->Draw("P E SAME");

//  h1_r_gluon->SetStats(0);
//  SetDataStyle(h1_r_gluon);
//  h1_r_gluon->Draw("P E SAME");

//  h1_r_comb->SetStats(0);
//    h1_r_comb->SetLineColor(38);
//    h1_r_comb->SetMarkerColor(38);
//  h1_r_comb->Draw("SAME");
    
  auto legend_r = new TLegend(0.6, 0.6, 0.8, 0.8);
  legend_r->SetBorderSize(0);
  legend_r->SetFillStyle(0);
  legend_r->SetFillColor(3);
  legend_r->SetHeader("LHCb Unofficial","C");
  legend_r->AddEntry(h1_r , "p_{T}^{jet} > 20 GeV/c ");
//  legend_r->AddEntry(h1_r_SV, "SV");
////  legend_r->AddEntry(h1_r_gluon, "Gluons");
//  legend_r->AddEntry(h1_r_comb, "Comb.");
  legend_r->Draw("SAME");

  ccan[ican]->cd(4);
    
  auto legend_zpt = new TLegend(0.25, 0.6, 0.5, 0.8);
  legend_zpt ->SetTextSize(0.03);
  legend_zpt ->SetBorderSize(0);
  legend_zpt ->SetFillStyle(0);
  legend_zpt ->SetFillColor(3);
  legend_zpt->SetHeader("LHCb Unofficial","C");
//  for (int i = 0; i < ptbinsize; i++)
  for (int i = 2; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptz->ProjectionX(Form("htemp%d_ptz", i), i + 1, i + 1);
    h1_temp->SetStats(0);
    NormalizeHist(h1_temp);
      h1_temp->SetMarkerStyle(i + 20);
      h1_temp->SetMarkerColor(i-1 + 1);
      h1_temp->SetLineColor(i-1 + 1);
    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetMinimum(0.0);
    h1_temp->SetMaximum(3.5);
      
    legend_zpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
      
//      legend_zpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

  }
    legend_zpt -> Draw("SAME");

  // ccan[ican]->cd(4);
  // for (int i = 0; i < customptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_SVTag_eff_z->ProjectionX(Form("htemp%d_z", i), i + 1, i + 1);
  //   TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur_z->ProjectionX(Form("htemp_pur%d", i), i + 1, i + 1);

  //   h1_temp->SetMarkerStyle(i + 20);
  //   h1_temp->SetMarkerColor(i + 1);
  //   h1_temp->SetLineColor(i + 1);
  //   h1_temp->Draw("P E SAME");
  //   h1_temp->Draw("HIST SAME");
  //   h1_temp->SetMinimum(0.);
  //   h1_temp->SetMaximum(1.05);

  //   h1_temp_pur->SetMarkerStyle(i + 23);
  //   h1_temp_pur->SetMarkerColor(i + 4);
  //   h1_temp_pur->SetLineColor(i + 4);
  //   h1_temp_pur->Draw("P E SAME");
  //   h1_temp_pur->Draw("HIST SAME");
  //   h1_temp_pur->SetMinimum(0.);
  //   h1_temp_pur->SetMaximum(1.05);
  // }
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
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0.06);
    gPad->SetRightMargin(0.15);
    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

    ccan[ican]->cd(1);
    auto legend_jtpt = new TLegend(0.6, 0.65, 0.8, 0.8);
//    legend_jtpt ->SetTextSize(0.03);
    legend_jtpt ->SetBorderSize(0);
    legend_jtpt ->SetFillStyle(0);
    legend_jtpt ->SetFillColor(3);
    legend_jtpt->SetHeader("LHCb Unofficial","C");
    gPad->SetLogy();
  //  for (int i = 0; i < ptbinsize; i++)
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt->ProjectionX(Form("htemp%d_ptjt", i), i + 1, i + 1);
      h1_temp->SetStats(0);
//      NormalizeHist(h1_temp);
        h1_temp->SetMarkerStyle(i + 20);
        h1_temp->SetMarkerColor(i-1 + 1);
        h1_temp->SetLineColor(i-1 + 1);
      h1_temp->SetYTitle("#frac{1}{N} #frac{dN}{d j_{T}}");
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
//      h1_temp->SetMinimum(0.1);
//      h1_temp->SetMaximum(2.0);
        
      legend_jtpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
        
  //      legend_zpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
      legend_jtpt -> Draw("SAME");
    
    ccan[ican]->cd(2);
    auto legend_rpt = new TLegend(0.6, 0.65, 0.8, 0.85);
//    legend_jtpt ->SetTextSize(0.03);
    legend_rpt ->SetBorderSize(0);
    legend_rpt ->SetFillStyle(0);
    legend_rpt ->SetFillColor(3);
    legend_rpt->SetHeader("LHCb Unofficial","C");
    gPad->SetLogy();
  //  for (int i = 0; i < ptbinsize; i++)
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr->ProjectionX(Form("htemp%d_ptr", i), i + 1, i + 1);
      h1_temp->SetStats(0);
//      NormalizeHist(h1_temp);
        h1_temp->SetMarkerStyle(i + 20);
        h1_temp->SetMarkerColor(i-1 + 1);
        h1_temp->SetLineColor(i-1 + 1);
      h1_temp->SetYTitle("#frac{1}{N} #frac{dN}{d j_{r}}");
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
//      h1_temp->SetMinimum(0.7);
//      h1_temp->SetMaximum(30.0);
        
      legend_rpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
        
  //      legend_zpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
      legend_rpt -> Draw("SAME");
    
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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  NormalizeHist(h1_z);
  NormalizeHist(h1_z_SV);
  NormalizeHist(h1_z_gluon);
  NormalizeHist(h1_jt);
  NormalizeHist(h1_jt_SV);
  NormalizeHist(h1_jt_gluon);
  NormalizeHist(h1_r);
  NormalizeHist(h1_r_SV);
  NormalizeHist(h1_r_gluon);
  NormalizeHist(h1_z_comb);
  NormalizeHist(h1_jt_comb);
  NormalizeHist(h1_r_comb);

  ccan[ican]->cd(1);

  h1_z->SetStats(0);
  h1_z->SetXTitle("z");
  SetRecoStyle(h1_z);
    h1_z->SetMarkerSize(0.7);
    h1_z->SetMinimum(0.);
    h1_z->SetMaximum(3.5);

  h1_z->Draw("P E SAME");

  h1_z_SV->SetStats(0);
  SetTruthStyle(h1_z_SV);
  h1_z_SV->SetMarkerSize(0.7);
  h1_z_SV->Draw("P E SAME");


//  h1_z_gluon->SetStats(0);
//  h1_z_gluon->SetLineColor(kMagenta);
//  // SetDataStyle(h1_frag_z_gluon);
//  h1_z_gluon->Draw("P E SAME");

//  h1_z_comb->SetStats(0);
//  h1_z_comb->SetLineColor(kRed);
//  h1_z_comb->SetMarkerColor(kRed);
//  h1_z_comb->SetMarkerStyle(8);
//  h1_z_comb->SetMarkerSize(0.7);
//  h1_z_comb->Draw("SAME");
    
    auto legend_znorm = new TLegend(0.2, 0.6, 0.3, 0.8);
    legend_znorm->SetBorderSize(0);
    legend_znorm->SetFillStyle(0);
    legend_znorm->SetFillColor(3);
    legend_znorm->AddEntry(h1_z , "b-quark");
    legend_znorm->AddEntry(h1_z_SV, "SV");
//      legend_jt->AddEntry(h1_jt_gluon, "Gluons");
//    legend_znorm->AddEntry(h1_z_comb, "Comb. (SB)");
    legend_znorm->Draw("SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  gPad->SetLogy();

//  h1_jt_gluon->SetStats(0);
//  SetDataStyle(h1_jt_gluon);
//  h1_jt_gluon->Draw("P E SAME");
    
  h1_jt->SetStats(0);
  h1_jt->SetXTitle("j_{T}");
  SetRecoStyle(h1_jt);
  h1_jt->SetMarkerSize(0.7);
  h1_jt->Draw("P E SAME");

  h1_jt_SV->SetStats(0);
  SetTruthStyle(h1_jt_SV);
  h1_jt_SV->SetMarkerSize(0.7);
  h1_jt_SV->Draw("P E SAME");

//  h1_jt_comb->SetStats(0);
//  h1_jt_comb->SetLineColor(kRed);
//  h1_jt_comb->SetMarkerColor(kRed);
//  h1_jt_comb->SetMarkerStyle(8);
//  h1_jt_comb->SetMarkerSize(0.7);
//  h1_jt_comb->Draw("SAME");
    
    auto legend_jtnorm = new TLegend(0.65, 0.6, 0.85, 0.8);
    legend_jtnorm->SetBorderSize(0);
    legend_jtnorm->SetFillStyle(0);
    legend_jtnorm->SetFillColor(3);
    legend_jtnorm->AddEntry(h1_jt , "b-quark");
    legend_jtnorm->AddEntry(h1_jt_SV, "SV");
//      legend_jt->AddEntry(h1_jt_gluon, "Gluons");
//    legend_jtnorm->AddEntry(h1_jt_comb, "Comb. (SB)");
    legend_jtnorm->Draw("SAME");

  ccan[ican]->cd(3);

  gPad->SetLogy();
  SetRecoStyle(h1_r);
  h1_r->SetMarkerSize(0.7);
  h1_r->Draw("P E SAME");

  h1_r_SV->SetStats(0);
  SetTruthStyle(h1_r_SV);
  h1_r_SV->SetMarkerSize(0.7);
  h1_r_SV->Draw("P E SAME");
    
    //  h1_r_gluon->SetStats(0);
    //  SetDataStyle(h1_r_gluon);
    //  h1_r_gluon->Draw("P E SAME");

//  h1_r_comb->SetStats(0);
//  h1_r_comb->SetLineColor(kRed);
//  h1_r_comb->SetMarkerColor(kRed);
//  h1_r_comb->SetMarkerStyle(8);
//  h1_r_comb->SetMarkerSize(0.7);
//  h1_r_comb->Draw("SAME");
    
    
    auto legend_rnorm = new TLegend(0.65, 0.65, 0.85, 0.88);
    legend_rnorm->SetBorderSize(0);
    legend_rnorm->SetFillStyle(0);
    legend_rnorm->SetFillColor(3);
    legend_rnorm->AddEntry(h1_r , "b-quark");
    legend_rnorm->AddEntry(h1_r_SV, "SV");
//      legend_jt->AddEntry(h1_jt_gluon, "Gluons");
//    legend_rnorm->AddEntry(h1_r_comb, "Comb. (SB)");
    legend_rnorm->Draw("SAME");


  ccan[ican]->cd(4);
    auto legend_zptSV = new TLegend(0.55, 0.65, 0.9, 0.85);
    legend_zptSV ->SetTextSize(0.027);
    legend_zptSV ->SetBorderSize(0);
    legend_zptSV ->SetFillStyle(0);
    legend_zptSV ->SetFillColor(3);
    legend_zptSV->SetHeader("SV > 0","C");
  for (int i = 2; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptz_SV->ProjectionX(Form("htemp%d_ptz_SV", i), i + 1, i + 1);
    NormalizeHist(h1_temp);
      h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i-1 + 1);
    h1_temp->SetLineColor(i-1 + 1);
    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(3.5);
    // h1_temp->SetMinimum(0.);
    // h1_temp->SetMaximum(1.05);
      
      legend_zptSV->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
  }
    legend_zptSV -> Draw("SAME");

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
    
    ////
    ///
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0.06);
    gPad->SetRightMargin(0.15);
    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

    ccan[ican]->cd(1);
    gPad->SetLogy();
      auto legend_jtptSV = new TLegend(0.55, 0.65, 0.9, 0.85);
      legend_jtptSV ->SetTextSize(0.027);
      legend_jtptSV ->SetBorderSize(0);
      legend_jtptSV ->SetFillStyle(0);
      legend_jtptSV ->SetFillColor(3);
      legend_jtptSV->SetHeader("SV > 0","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt_SV->ProjectionX(Form("htemp%d_ptjt_SV", i), i + 1, i + 1);
//      NormalizeHist(h1_temp);
        h1_temp->SetStats(0);
      h1_temp->SetMarkerStyle(i + 20);
      h1_temp->SetMarkerColor(i-1 + 1);
      h1_temp->SetLineColor(i-1 + 1);
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
      h1_temp->SetXTitle("j_{T}");
//      h1_temp->SetMinimum(0.);
//      h1_temp->SetMaximum(3.5);
      // h1_temp->SetMinimum(0.);
      // h1_temp->SetMaximum(1.05);
        
        legend_jtptSV->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
    }
      legend_jtptSV -> Draw("SAME");
    
    ccan[ican]->cd(2);
    gPad->SetLogy();
      auto legend_rptSV = new TLegend(0.55, 0.65, 0.9, 0.85);
      legend_rptSV ->SetTextSize(0.027);
      legend_rptSV ->SetBorderSize(0);
      legend_rptSV ->SetFillStyle(0);
      legend_rptSV ->SetFillColor(3);
      legend_rptSV->SetHeader("SV > 0","C");
    for (int i = 2; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr_SV->ProjectionX(Form("htemp%d_ptr_SV", i), i + 1, i + 1);
//      NormalizeHist(h1_temp);
        h1_temp->SetStats(0);
      h1_temp->SetMarkerStyle(i + 20);
      h1_temp->SetMarkerColor(i-1 + 1);
      h1_temp->SetLineColor(i-1 + 1);
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
      h1_temp->SetXTitle("r");
////      h1_temp->SetMinimum(0.);
//      h1_temp->SetMaximum(30);
      // h1_temp->SetMinimum(0.);
      // h1_temp->SetMaximum(1.05);
        
        legend_rptSV->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
    }
      legend_rptSV -> Draw("SAME");

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
//  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 650);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
//  gPad->SetTopMargin(0.08);
  ccan[ican]->cd();
  ccan[ican]->Divide(3, 2, 0.0001, 0.0001);
  
  ccan[ican]->cd(1);
  gPad->SetLogz();
  //h2_zjt->SetStats(0);
  //h2_zjt->Draw("COLZ");
  h3_ptzjt->GetZaxis()->SetRange(20.,100.);
  TH2D *h2_temp_zjt = (TH2D*)h3_ptzjt->Project3D("yx");
  h2_temp_zjt->SetStats(0);
  h2_temp_zjt->Draw("COLZ");  
    
  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
   gPad->SetLogz();
  //h2_zr->SetStats(0);
  //h2_zr->Draw("COLZ");
  h3_ptzr->GetZaxis()->SetRange(20.,100.);
  TH2D *h2_temp_zr = (TH2D*)h3_ptzr->Project3D("yx");
  h2_temp_zr->SetStats(0);
  h2_temp_zr->Draw("COLZ");


  ccan[ican]->cd(3);
  gPad->SetLogz();
//    h2_jtr->SetStats(0);
//  h2_jtr->Draw("COLZ");
  h3_ptjtr->GetZaxis()->SetRange(20.,100.);
  TH2D *h2_temp_jtr = (TH2D*)h3_ptjtr->Project3D("yx");
  h2_temp_jtr->SetStats(0);
  h2_temp_jtr->Draw("COLZ");

 
  ccan[ican]->cd(4);
  gPad->SetLogz();
  h2_zjt_SV->SetStats(0);
  h2_zjt_SV->Draw("COLZ");
  
 ccan[ican]->cd(5);
 gPad->SetLogz();
 h2_zr_SV->SetStats(0);
  h2_zr_SV->Draw("COLZ");

  ccan[ican]->cd(6);
  gPad->SetLogz();
  h2_jtr_SV->SetStats(0);
  h2_jtr_SV->Draw("COLZ");
    
//    ccan[ican]->cd(7);
//    gPad->SetLogz();
//    h2_zjt_gluon->SetStats(0);
//    h2_zjt_gluon->Draw("COLZ");
//    
//    ccan[ican]->cd(8);
//    // h2_thetaErad->Scale(1./NumJets);
//    gPad->SetLogz();
//    h2_zr_gluon->Draw("COLZ");
//
//    ccan[ican]->cd(9);
//    gPad->SetLogz();
//    h2_jtr_gluon->SetStats(0);
//    h2_jtr_gluon->Draw("COLZ");


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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  SetDataStyle(h1_jet_pt_comb);
  SetTruthStyle(h1_jet_pt_SV);
  SetRecoStyle(h1_jet_pt);
  h1_jet_pt->SetStats(0);
  h1_jet_pt->SetXTitle("pT(jet)");
  h1_jet_pt->Draw("P E SAME");
  cout << h1_jet_pt->Integral() << endl;

  h1_jet_pt_comb->Draw(" P E SAME");
  h1_jet_pt_SV->Draw(" P E SAME");

  h1_tr_jet_pt->SetStats(0);
  // h1_tr_jet_pt->SetXTitle("pT(jet)");
  h1_tr_jet_pt->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_jet_eta->SetStats(0);
  h1_jet_eta->SetXTitle("#eta(jet)");
  h1_jet_eta->Draw("P E SAME");
  h1_jet_rap->Draw("P E SAME");

  ccan[ican]->cd(3);
  // PaintOverflow(h1_jet_ptbalance);
  h1_jet_ptbalance->SetTitle("; pT(Reco)/pT(Truth);");
  h1_jet_ptbalance->Draw("P E SAME");
  // gPad->SetLogy();

  ccan[ican]->cd(4);
  h2_jetpt_HFpt->Draw("COLZ");

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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  SetRecoStyle(h1_dtr_pt);
  h1_dtr_pt->Draw("PE SAME");

  ccan[ican]->cd(2);
  for (int i = 0; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_Ndtr_jetpt->ProjectionX(Form("htemp%d_dtrjetpt", i), i + 1, i + 1);

    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);
    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    // h1_temp->SetMinimum(0.);
    // h1_temp->SetMaximum(1.05);
  }
  ccan[ican]->cd(3);
  for (int i = 0; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_Ndtr_jetpt_charged->ProjectionX(Form("htemp%d_dtrjetptcharged", i), i + 1, i + 1);

    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);
    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    // h1_temp->SetMinimum(0.);
    // h1_temp->SetMaximum(1.05);
  }
  ccan[ican]->cd(4);
  for (int i = 0; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_Ndtr_jetpt_neutral->ProjectionX(Form("htemp%d_dtrjetptneutral", i), i + 1, i + 1);

    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);
    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    // h1_temp->SetMinimum(0.);
    // h1_temp->SetMaximum(1.05);
  }

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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  h1_HF_pt->SetStats(0);
  h1_HF_pt->SetXTitle("pT(HF)");
  h1_HF_pt->SetMarkerStyle(20);
  h1_HF_pt->SetMarkerColor(kBlue);
  h1_HF_pt->SetLineColor(kBlue);

  h1_HF_pt->Draw("P E SAME");
  // Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  // h1_tr_dR->SetStats(0);
  // h1_tr_dR->SetMarkerStyle(21);
  // h1_tr_dR->SetMarkerColor(kRed);
  // h1_tr_dR->SetLineColor(kRed);
  // h1_tr_dR->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_HF_rap->SetStats(0);
  h1_HF_rap->SetXTitle("y(HF)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_HF_rap->Draw("P E SAME");
  ccan[ican]->cd(3);
  // gPad->SetLogy();
  h1_HF_mass->SetStats(0);
  // h1_dphi_HF_jet->SetXTitle("#Delta#Phi");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_HF_mass->Draw("P E SAME");
  h1_HF_mass_dtfcut->Draw("SAME");
  // SetTruthStyle(h1_HF_mass_float);
  // h2_HF_mass_float->Draw("COLZ");

  ccan[ican]->cd(4);
  SetDataStyle(h1_nJetDtrs_noghost_comb);
  SetRecoStyle(h1_nJetDtrs_noghost);
  SetTruthStyle(h1_nJetDtrs_noghost_SV);
  h1_nJetDtrs_noghost->Draw("P E SAME");
  h1_nJetDtrs_noghost_SV->Draw("P E SAME");
  h1_nJetDtrs_noghost_comb->Draw("P E SAME");

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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  gPad->SetLogy();
  h1_Jpsi_pt->SetStats(0);
  h1_Jpsi_pt->SetXTitle("pT(J/#psi)");
  h1_Jpsi_pt->SetMarkerStyle(20);
  h1_Jpsi_pt->SetMarkerColor(kBlue);
  h1_Jpsi_pt->SetLineColor(kBlue);

  h1_Jpsi_pt->Draw("P E SAME");
  // Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  // h1_tr_dR->SetStats(0);
  // h1_tr_dR->SetMarkerStyle(21);
  // h1_tr_dR->SetMarkerColor(kRed);
  // h1_tr_dR->SetLineColor(kRed);
  // h1_tr_dR->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  h1_Jpsi_rap->SetStats(0);
  h1_Jpsi_rap->SetXTitle("y(J/#psi)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_Jpsi_rap->Draw("P E SAME");
  ccan[ican]->cd(3);
  h1_Jpsi_mass->SetStats(0);
  // h1_dphi_Jpsi_jet->SetXTitle("#Delta#Phi");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_Jpsi_mass->Draw("P E SAME");
  ccan[ican]->cd(4);
  h1_Jpsi_ipchi2->Draw("P E SAME");
  h1_Jpsi_ipchi2->SetStats(0);

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
//  ++ican;
//  sprintf(buf, "ccan%d", ican);
//  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
//  ccan[ican]->SetFillColor(10);
//  gPad->SetLeftMargin(0.16);
//  gPad->SetBottomMargin(0.06);
//  gPad->SetRightMargin(0.15);
//  ccan[ican]->cd();
//  ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
//  ccan[ican]->cd(1);
//  THStack *stack_theta = new THStack("stack_theta", "");
//  for (int i = 0; i < Eradbinsize; i++)
//  {
//    TH1D *hX_Y = (TH1D *)h2_thetaErad->ProjectionY(Form("hX_Y%d", i + 1), i + 1, i + 1);
//    stack_theta->Add(hX_Y);
//  }
//  stack_theta->Draw("PLC NOSTACK");

//  ccan[ican]->cd();
//  ccan[ican]->Update();
//  if (ican == 0)
//  {
//    ccan[ican]->Print(plotfileO.Data());
//  }
//  else
//  {
//    ccan[ican]->Print(plotfilePDF.Data());
//  }

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);

  h2_sv_mass_z_truepos->Draw("COLZ");

  ccan[ican]->cd(2);

  h2_bdt_z_truepos->Draw("COLZ");

  ccan[ican]->cd(3);

  h2_bdt_sv_mass_truepos->Draw("COLZ");

  ccan[ican]->cd(4);
  SetRecoStyle(h1_r_false);
  SetTruthStyle(h1_r_true);
  // NormalizeHist(h1_r_false);
  // NormalizeHist(h1_r_true);
  h1_r_true->Draw("P E SAME");
  h1_r_false->Draw("P E SAME");

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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);

  h2_sv_mass_z_falsepos->Draw("COLZ");

  ccan[ican]->cd(2);

  h2_bdt_z_falsepos->Draw("COLZ");

  ccan[ican]->cd(3);

  h2_bdt_sv_mass_falsepos->Draw("COLZ");

  ccan[ican]->cd(4);
  SetRecoStyle(h1_z_false);
  SetTruthStyle(h1_z_true);
  SetDataStyle(h1_z_truefalse);
  // NormalizeHist(h1_z_false);
  // NormalizeHist(h1_z_true);
  // NormalizeHist(h1_z_truefalse);
  h1_z_truefalse->Draw("PE SAME");
  h1_z_false->Draw("P E SAME");
  h1_z_true->Draw("P E SAME");

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
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);

  h2_sv_mass_ntrks_falsepos->Draw("COLZ");

  ccan[ican]->cd(2);

  h2_sv_mass_ntrks_truepos->Draw("COLZ");

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

//  //
//  ++ican;
//  sprintf(buf, "ccan%d", ican);
//  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
//  ccan[ican]->SetFillColor(10);
//  gPad->SetLeftMargin(0.16);
//  gPad->SetBottomMargin(0.06);
//  gPad->SetRightMargin(0.15);
//  ccan[ican]->cd();
//  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
//  ccan[ican]->cd(1);
//
//  h2_ktdR_truepos->Draw("COLZ");
//
//  ccan[ican]->cd(2);
//
//  h2_ktdR_falsepos->Draw("COLZ");
//
//  ccan[ican]->cd(3);
//
//  h2_zdR_truepos->Draw("COLZ");
//
//  ccan[ican]->cd(4);
//
//  h2_zdR_falsepos->Draw("COLZ");
//
//  ccan[ican]->cd();
//  ccan[ican]->Update();
//  if (ican == 0)
//  {
//    ccan[ican]->Print(plotfileO.Data());
//  }
//  else
//  {
//    ccan[ican]->Print(plotfilePDF.Data());
//  }
  //
 
  f.Write();
  f.Close();
  file_unfold->Close();

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }
}

int main(int argc, char *argv[])
{

  int NumEvts = -1;
  int dataset = 91599;
  bool isData = true;
  bool chargedJetCut = false;
  int DoTrackEff = 0;
  bool DoTrigEff = false;
  int DoPIDEff = 0;
  bool DoRecSelEff = false;
  bool DoMassFit = false;
  bool SubtractGS = false;

  // Parsing command line arguments
  for (int i = 1; i < argc; ++i)
  {
    // std::cout << "Parsing!" << std::endl;
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
      // std::cout << argv[i + 1] << std::endl;
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
      // std::cout << argv[i + 1] << std::endl;
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
    else if (arg == "-recsel")
    {
      if (i + 1 < argc)
      {
        DoRecSelEff = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-recsel option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-trig")
    {
      if (i + 1 < argc)
      {
        DoTrigEff = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-trig option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-massfit")
    {
      if (i + 1 < argc)
      {
        DoMassFit = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-massfit option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-subtractGS")
    {
      if (i + 1 < argc)
      {
        SubtractGS = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-subtractGS option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-trackeff")
    {
      if (i + 1 < argc)
      {
        DoTrackEff = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-trackeff option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-pideff")
    {
      if (i + 1 < argc)
      {
        DoPIDEff = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-pideff option requires one argument." << std::endl;
        return 1;
      }
    }
    else
    {
      std::cerr << "Unknown option: " << arg << std::endl;
      return 1;
    }
  }

  SimpleObservables(NumEvts,
             dataset,
             isData,
             chargedJetCut,
             DoTrackEff,
             DoTrigEff,
             DoPIDEff,
             DoRecSelEff,
             DoMassFit,
             SubtractGS);
  return 0;
}
