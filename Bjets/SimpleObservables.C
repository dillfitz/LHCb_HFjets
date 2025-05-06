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
void SimpleObservables(int NumEvts = -1, int dataset = 91599,
                bool isData = true,
                int DoTrackEff = 0,
                int DoTrigEff = 0,
                int DoPIDEff = 0,
                bool DoRecSelEff = false,
                int DoMassFit = 0,
                bool DoSignalSys = false,
                bool DoJetID = false,                                
                bool SubtractGS = false,
                bool onlyL0DiMuon = false)
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
  TString str_year = "";
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

  TString str_L0 = "";
  if (onlyL0DiMuon)
    str_L0 = "_L0DiMuon";


  TString str_tree;
  TString extension_RootFilesMC, extension_RootFiles;
  TString extension_read, extension_wspace, extension_eff;
  TString eff_path;

  TString extension_prefix, extension_trackeff;
  TString extension;

  extension = str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_GS + str_L0 + Form("_%d", dataset);

  // HFjetTree Tree(0, dataset, isData);

  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;
    
  extension_RootFilesMC = TString("../../root_files/BjetsMC/");
  extension_RootFiles = isData ?  TString("../../root_files/Bjets/") : extension_RootFilesMC;
    
  eff_path = TString( "../../Effs/");
    
  float minimum_dR = 0.1;

  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_L0 + Form("_%d", dataset);
  //extension_wspace = TString("workspace_massfit_") + str_level + Form("_ev_%d", -1) + Form("_ptj_%d%d",pTLow, int(250)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_ghost + str_Mag + str_flavor + Form("_%d", dataset);

  if (DoJetID)
    extension_prefix = TString("jetid_");    
  if (DoRecSelEff)
    extension_prefix = TString("recselsys_");
  if (DoSignalSys)
    extension_prefix = TString("signalsys_");
    
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

  extension = extension_prefix + extension;
  extension_trackeff = "trackEff_" + str_year + "_Ratio_Full_Long_method";

  /////////////////// Mass Fit Parameters /////////////////////////////////
  // massfit_data_ev_-1_ptj_12250_eta_2.54.0_ghost_0.5_b_PID_91599.root
  //TString massfit( TString("massfit_data_ev_-1") + Form("_ptj_%d%d", int(pTLow), int(250.)) + "_eta_2.54.0_ghost_0.4_b" + str_PID + "_91599.root"); 
  TString massfit( TString("splotfit_data_ev_-1") + Form("_ptj_%d%d", int(pTLow), int(250.)) + "_eta_2.54.0_ghost_0.4_b" + str_PID + str_L0 + "_91599.root"); 
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

  TTree *sWeightTree = (TTree *)f_massfit.Get("sWeightTree");

    
  /////////////////// Trigger Ratio (TISTOS/MC True) /////////////////////////////////
  ////////////////////////////////////////////////////
  ///              Trigger
  //////////////////////////////////////////////////
  TString extension_trig_MC, extension_trig_Data;
  TH2D *h2_trigeff_Data;
  TH2D *h2_trigeff_MC;

  //extension_trig_MC = "PhotonHadronElectronTIS_jpsieff_reco_ev_-1_b_PID_91599";
  //extension_trig_Data = "PhotonHadronElectronTIS_jpsieff_data_ev_-1_b_PID_91599";
  extension_trig_MC = "jpsieff_reco_ev_-1_b_PID" + str_L0 + "_91599.root";
  extension_trig_Data = "jpsieff_data_ev_-1_b_PID" + str_L0 + "_91599.root";

  TFile file_trigeffMC("../../Effs/TrigEff/MC/" + extension_trig_MC, "READ");
  TFile file_trigeffData("../../Effs/TrigEff/data/" + extension_trig_Data, "READ");

  h2_trigeff_Data = (TH2D *)file_trigeffData.Get("efficiency_Jpsiptrap");
  h2_trigeff_MC = (TH2D *)file_trigeffMC.Get("efficiency_Jpsiptrap");
  TH2D *h2_trigeff_ratio = (TH2D *)h2_trigeff_Data->Clone("h2_trigeff_ratio");
  h2_trigeff_ratio->Divide(h2_trigeff_MC);

  TH2D *h2_trig_ratio = (TH2D *)file_trigeffMC.Get("h2_eff_ratio");

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
      extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost  + str_Mag + str_flavor + str_L0 + Form("_%d", vec_datasets[i]);
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

  TH2D *h2_zjt = new TH2D("zjt", ";z; j_{T} [GeV/c]", zbinsize, z_binedges, jtbinsize, jt_binedges);
  TH2D *h2_zr = new TH2D("zr", ";z; r", zbinsize, z_binedges, rbinsize, r_binedges);
  TH2D *h2_jtr = new TH2D("jtr", "; j_{T} [GeV/c]; r", jtbinsize, jt_binedges, rbinsize, r_binedges);
    
  TH1D *h1_z = new TH1D("z", ";z", zbinsize, z_binedges);
  TH1D *h1_jt = new TH1D("jt", ";j_{T} [GeV/c]", jtbinsize, jt_binedges);
  TH1D *h1_r = new TH1D("r", ";r", rbinsize, r_binedges);

  TH2D *h2_ptz = new TH2D("ptz", ";z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt = new TH2D("ptjt", ";j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr = new TH2D("ptr", ";r;p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptz_sweight = new TH2D("ptz_sweight", ";z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt_sweight = new TH2D("ptjt_sweight", ";j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr_sweight = new TH2D("ptr_sweight", ";r;p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
  TH3D *h3_ptzjt = new TH3D("ptzjt", ";z;j_{T} [GeV/c];p_{T,jet} [GeV/c]", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptzr = new TH3D("ptzr", ";z;r;p_{T} [GeV/c]",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptjtr = new TH3D("ptjtr", ";j_{T} [GeV/c];r;p_{T} [GeV/c]",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptzjt_sweight = new TH3D("ptzjt_sweight", ";z;j_{T} [GeV/c];p_{T,jet} [GeV/c]", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptzr_sweight = new TH3D("ptzr_sweight", ";z;r;p_{T} [GeV/c]",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptjtr_sweight = new TH3D("ptjtr_sweight", ";j_{T} [GeV/c];r;p_{T} [GeV/c]",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    
  TH2D *h2_ptz_uncorrected = new TH2D("ptz_uncorrected", ";z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt_uncorrected = new TH2D("ptjt_uncorrected", ";j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr_uncorrected = new TH2D("ptr_uncorrected", ";r;p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);
    
  TH3D *h3_ptzjt_uncorrected = new TH3D("ptzjt_uncorrected", ";z;j_{T} [GeV/c];p_{T,jet} [GeV/c]", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptzr_uncorrected = new TH3D("ptzr_uncorrected", ";z;r;p_{T} [GeV/c]",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
  TH3D *h3_ptjtr_uncorrected = new TH3D("ptjtr_uncorrected", ";j_{T} [GeV/c];r;p_{T} [GeV/c]",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );    
     
  TH1D *h1_z_ptHFcut_g5 = new TH1D("z_ptHFcut_g5", ";z;", zbinsize, z_binedges);
  TH1D *h1_z_ptHFcut_l5 = new TH1D("z_ptHFcut_l5", ";z;", zbinsize, z_binedges);    
    
  /// ------------------------------------------ COMBINATORIAL --------------------------------------------- ///
    
  TH1D *h1_jet_pt_comb = new TH1D("Jet_pT_comb", "", ptbinsize, pt_binedges); 
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

  /// ------------------------------------------ END COMBINATORIAL --------------------------------------------- ///

  /// ------------------------------------------ QA --------------------------------------------- ///


  TH2D *h2_jetpteta = new TH2D("h2_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_jetpt_HFpt = new TH2D("jetpt_HFpt", "", 50, 0, 100, 50, 0, 100);

  TH1D *h1_jet_pt = new TH1D("Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_jet_eta = new TH1D("Jet_eta", "", 12, etaMin, etaMax);
  TH1D *h1_jet_rap = new TH1D("Jet_rap", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi = new TH1D("Jet_phi", "", 20, -3.14, 3.14);

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

  TH1D *h1_HFpt = new TH1D("h1_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH2D *h2_HFptjetpt = new TH2D("h2_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_HFptrap = new TH2D("h2_HFptrap", "", ptHFbinsize, ptHF_binedges, etabinsize, eta_binedges);
  TH3D *h3_HFptjetptrap = new TH3D("h3_HFptjetptrap", "", ptHFbinsize, ptHF_binedges, fineptbinsize, finept_binedges, etabinsize, eta_binedges);

  TH2D *h2_mB_mJpsi = new TH2D("mB_mJpsi", ";m_{#mu #mu K}; m_{#mu #mu}", 40, 5.15, 5.55, 40, 2.997, 3.197);
  TH1D *h1_nJetDtrs = new TH1D("nJetDtrs", "", 40, -0.5, 39.5);

  TH1D *h1_nSPDHits = new TH1D("nSPDHits", ";N_{SPD};", 100, 0., 1000.);
  
  TH1D *h1_z_nobgsub, *h1_jt_nobgsub, *h1_r_nobgsub;
  TH2D *h2_ptz_nobgsub, *h2_ptjt_nobgsub, *h2_ptr_nobgsub;
  h1_z_nobgsub = (TH1D*)h1_z->Clone("z_nobgsub");
  h1_jt_nobgsub = (TH1D*)h1_jt->Clone("jt_nobgsub");
  h1_r_nobgsub = (TH1D*)h1_r->Clone("r_nobgsub");
  h2_ptz_nobgsub = (TH2D*)h2_ptz->Clone("ptz_nobgsub");    
  h2_ptjt_nobgsub = (TH2D*)h2_ptjt->Clone("ptjt_nobgsub");            
  h2_ptr_nobgsub = (TH2D*)h2_ptr->Clone("ptr_nobgsub");     
   
    
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
  int nSPDHits;
  // TLorentzVector
    
  float pideff_K(1.0), pideff_mup(1.0), pideff_mum(1.0);
  float pideff_K_err(1.0), pideff_mup_err(1.0), pideff_mum_err(1.0);
  float trkeff_ratio_K(1.0), trkeff_ratio_mup(1.0), trkeff_ratio_mum(1.0);
  float trkeff_ratio_K_errhi(1.0), trkeff_ratio_mup_errhi(1.0), trkeff_ratio_mum_errhi(1.0);
  float trkeff_ratio_K_errlo(1.0), trkeff_ratio_mup_errlo(1.0), trkeff_ratio_mum_errlo(1.0);
  float trigeff_Data(1.0), trigeff_MC(1.0), trigeff_ratio(1.0);
    
  BTree->SetBranchAddress("eventNumber", &eventNumber);

  BTree->SetBranchAddress("dtr_pt", &dtr_pt);
  BTree->SetBranchAddress("dtr_rap", &dtr_rap);
  BTree->SetBranchAddress("dtr_id", &dtr_id);
  BTree->SetBranchAddress("dtr_3charge", &dtr_3charge);
  BTree->SetBranchAddress("Ndtr_neutral", &Ndtr_neutral);
  BTree->SetBranchAddress("Ndtr_charged", &Ndtr_charged);

  BTree->SetBranchAddress("jet_pt", &jet_pt);
  BTree->SetBranchAddress("jet_eta", &jet_eta);
  BTree->SetBranchAddress("jet_rap", &jet_rap);

  BTree->SetBranchAddress("jet_px", &jet_px);
  BTree->SetBranchAddress("jet_py", &jet_py);
  BTree->SetBranchAddress("jet_pz", &jet_pz);
  BTree->SetBranchAddress("jet_e", &jet_e);

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

  BTree->SetBranchAddress("trkeff_ratio_K", &trkeff_ratio_K);
  BTree->SetBranchAddress("trkeff_ratio_mup", &trkeff_ratio_mup);
  BTree->SetBranchAddress("trkeff_ratio_mum", &trkeff_ratio_mum);

  BTree->SetBranchAddress("trkeff_ratio_K_errhi", &trkeff_ratio_K_errhi);
  BTree->SetBranchAddress("trkeff_ratio_mup_errhi", &trkeff_ratio_mup_errhi);
  BTree->SetBranchAddress("trkeff_ratio_mum_errhi", &trkeff_ratio_mum_errhi);
  BTree->SetBranchAddress("trkeff_ratio_K_errlo", &trkeff_ratio_K_errlo);
  BTree->SetBranchAddress("trkeff_ratio_mup_errlo", &trkeff_ratio_mup_errlo);
  BTree->SetBranchAddress("trkeff_ratio_mum_errlo", &trkeff_ratio_mum_errlo);

  BTree->SetBranchAddress("trigeff_Data", &trigeff_Data);
  BTree->SetBranchAddress("trigeff_MC", &trigeff_MC);
  //BTree->SetBranchAddress("trigeff_ratio", &trigeff_ratio);
  BTree->SetBranchAddress("TOS", &TOS);
  BTree->SetBranchAddress("nSPDHits", &nSPDHits);

    
  BTree->SetBranchAddress("z", &z);
  BTree->SetBranchAddress("jt", &jt);
  BTree->SetBranchAddress("r", &r);
  BTree->SetBranchAddress("zg", &zg);
  BTree->SetBranchAddress("jtg", &jtg);
  BTree->SetBranchAddress("rg", &rg);
  BTree->SetBranchAddress("tr_z", &tr_z);
  BTree->SetBranchAddress("tr_jt", &tr_jt);
  BTree->SetBranchAddress("tr_r", &tr_r);

  float sweight;
  sWeightTree->SetBranchAddress("sweight", &sweight);
  

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

  cout << "Requested # of events : " << NumEvts << endl;
  cout << "NumEvents in the sweight tree : " << sWeightTree->GetEntries() << std::endl; 
  if (isData && NumEvts != sWeightTree->GetEntries())
  {
    std::cout << "Different number of entries in sWeightTree vs. Data tree is different!" << std::endl;
    return;
  }

  TRandom3 *randomGenerator = new TRandom3();

  //
  // Event loop
  //
  for (int ev = 0; ev < NumEvts; ev++)
  {
    BTree->GetEntry(ev);
    if (isData)
    {
      sWeightTree->GetEntry(ev);
    }
    else
    {
      sweight = 1.0;
    }
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


    float mass_low = 5.15;
    float mass_high = 5.55;
    if (bmass_dtf < mass_low || bmass_dtf > mass_high)
      continue; 

    //std:cout << "sweight : " << sweight << std::endl;


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
    float bkg_weight = h1_BkgScale != NULL ? h1_BkgScale->GetBinContent(h1_BkgScale->FindBin(HFmeson.Pt())) : 1.0;
    float MassHigh = h1_MassMax != NULL ? h1_MassMax->GetBinContent(h1_MassMax->FindBin(HFmeson.Pt())) : 5.31;
    float MassLow = h1_MassMin != NULL ? h1_MassMin->GetBinContent(h1_MassMin->FindBin(HFmeson.Pt())) : 5.24;

    float Sideband1Min = h1_Sideband1Min != NULL ? h1_Sideband1Min->GetBinContent(h1_Sideband1Min->FindBin(HFmeson.Pt())) : 5.24;
    float Sideband1Max = h1_Sideband1Max != NULL ? h1_Sideband1Max->GetBinContent(h1_Sideband1Max->FindBin(HFmeson.Pt())) : 5.31;
    float Sideband2Min = h1_Sideband2Min != NULL ? h1_Sideband2Min->GetBinContent(h1_Sideband2Min->FindBin(HFmeson.Pt())) : 5.24;
    float Sideband2Max = h1_Sideband2Max != NULL ? h1_Sideband2Max->GetBinContent(h1_Sideband2Max->FindBin(HFmeson.Pt())) : 5.31;
    
    //  Set Trigger Correction Weight
    if (isData && h2_trigeff_Data != NULL)
    {
      double rap = (Jpsi.Rapidity() > 2.00) ? Jpsi.Rapidity() : 2.1;
      double pt = (Jpsi.Pt() > 2.00) ? Jpsi.Pt() : 2.1;
      trigeff_ratio = h2_trigeff_ratio->GetBinContent(h2_trigeff_ratio->GetXaxis()->FindBin(pt), h2_trigeff_ratio->GetYaxis()->FindBin(rap));
      // trigeff_Data = h2_trigeff_Data->GetBinContent(h2_trigeff_Data->GetXaxis()->FindBin(Jpsi.Pt()), h2_trigeff_Data->GetYaxis()->FindBin(rap));
      // trigeff_MC = h2_trigeff_MC->GetBinContent(h2_trigeff_MC->GetXaxis()->FindBin(Jpsi.Pt()), h2_trigeff_MC->GetYaxis()->FindBin(rap));
      // trigeff_ratio = trigeff_Data / trigeff_MC;
      // cout << trigeff_ratio << ", ";
      if (std::isnan(trigeff_ratio) || std::isinf(trigeff_ratio) || trigeff_ratio == 0)
        trigeff_ratio = trigeff_Data = trigeff_MC = 1.0;
    }
    else
    {
      trigeff_ratio = 1.0;
    }
    

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

    if (DoTrackEff == 1)
    {
      trkeff_ratio_K = trkeff_ratio_K + trkeff_ratio_K_errhi;
      trkeff_ratio_K = (1 + 0.0127) * trkeff_ratio_K; // Material Budget of 1.27% on Kaons
      trkeff_ratio_mum = trkeff_ratio_mum + trkeff_ratio_mum_errhi;
      trkeff_ratio_mup = trkeff_ratio_mup + trkeff_ratio_mup_errhi;
    }
    else if (DoTrackEff == 2)
    {
      trkeff_ratio_K = trkeff_ratio_K - trkeff_ratio_K_errlo;
      trkeff_ratio_K = (1 - 0.0127) * trkeff_ratio_K; // Material Budget of 1.27% on Kaons
      trkeff_ratio_mum = trkeff_ratio_mum - trkeff_ratio_mum_errlo;
      trkeff_ratio_mup = trkeff_ratio_mup - trkeff_ratio_mup_errlo;

      if (trkeff_ratio_K_errlo > 0.1 || trkeff_ratio_mup_errlo > 0.1 || trkeff_ratio_mum_errlo > 0.1)
      {
        cout << trkeff_ratio_K << endl;
        cout << trkeff_ratio_mum_errlo << ", " << trkeff_ratio_mup_errlo << ", " << trkeff_ratio_K_errlo << endl;
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
      if (fabs(Jpsi_BPVDLS) < 3.2)
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

      
    //     cout << " ------------------------------------------------ " << endl;
    //     cout << "Evt Pur:"<< event_pur << ", Event Eff:" << event_eff << endl;
    //     cout << "Trk Eff (K, mum, mup):" << trkeff_ratio_K << ", " << trkeff_ratio_mum << ", " << trkeff_ratio_mup << endl;
    //     cout << "PID Eff (K, mum, mup):" << pideff_K << ", " << pideff_mum << ", " << pideff_mup << endl;
    //     cout << "Trig Eff (K, mum, mup):" << trigeff_ratio << endl;
    //     cout << " ------------------------------------------------ " << endl;
      
         
    event_weight = (1./ (trkeff_ratio_K * trkeff_ratio_mum * trkeff_ratio_mup * pideff_mum * pideff_mup * trigeff_ratio));       
    
    //if (PID_cut)
    //  event_weight *= (1. / (pideff_K));
    
    if (std::isinf(event_weight) || std::isnan(event_weight))
      event_weight = 1.0;

    float dphi_HF_jet = checkphi(checkphi(HFmeson.Phi()) - checkphi(HFjet.Phi()));
    float dy_HF_jet = HFjet.Eta() - HFmeson.Rapidity();
    // h1_HF_mass->Fill(HFmeson.M());
    if (DTF_cond)
      h1_HF_mass_dtfcut->Fill(bmass_dtf);


    if (bkg_cond)
    {

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

      h1_jet_pt_comb->Fill(jet_pt, event_weight * bkg_weight);
        
    }

    if (signal_cond)
    {

      // QA HISTS -- note there is no event weight applied here... //
      h2_jetpt_HFpt->Fill(HFmeson.Pt(), HFjet.Pt());
      h2_jetpteta->Fill(jet_pt, jet_eta);

      h1_Jpsi_mass->Fill(Jpsi.M());
      h1_Jpsi_pt->Fill(Jpsi.Pt());
      h1_Jpsi_rap->Fill(Jpsi.Rapidity());
      h1_Jpsi_phi->Fill(Jpsi.Phi());
      h1_Jpsi_ipchi2->Fill(jpsi_ipchi2);

      h1_HF_rap->Fill(HFmeson.Rapidity());
      h1_HF_pt->Fill(HFmeson.Pt());
      h1_HF_phi->Fill(HFmeson.Phi());
      h1_HF_mass->Fill(bmass_dtf);

      h1_nJetDtrs->Fill(ndtrs);
      h1_jet_eta->Fill(jet_eta);
      h1_jet_rap->Fill(jet_rap);
      h1_jet_phi->Fill(HFjet.Phi());


      // HISTS FOR ANALYSIS //
      h1_jet_pt->Fill(jet_pt, event_weight);

      h3_ptzjt->Fill(z, jt, jet_pt, event_weight);
      h3_ptzr->Fill(z, r, jet_pt, event_weight);
      h3_ptjtr->Fill(jt, r, jet_pt, event_weight);
      
      h2_ptz->Fill(z, jet_pt, event_weight);
      h2_ptjt->Fill(jt, jet_pt, event_weight);
      h2_ptr->Fill(r, jet_pt, event_weight); 
      
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
      
      h3_ptzjt_uncorrected->Fill(z, jt, jet_pt);
      h3_ptzr_uncorrected->Fill(z, r, jet_pt);
      h3_ptjtr_uncorrected->Fill(jt, r, jet_pt);
      
      h2_ptz_uncorrected->Fill(z, jet_pt);
      h2_ptjt_uncorrected->Fill(jt, jet_pt);
      h2_ptr_uncorrected->Fill(r, jet_pt);     
              
      if (HF_pt < 5.) { h1_z_ptHFcut_l5->Fill(z); }        
      else { h1_z_ptHFcut_g5->Fill(z); }

      h1_nSPDHits->Fill(nSPDHits);

    } // end signal cond 
    
    if (PID_cut && PID_cond)
    {
      h3_ptzjt_sweight->Fill(z, jt, jet_pt, event_weight*sweight);
      h3_ptzr_sweight->Fill(z, r, jet_pt, event_weight*sweight);
      h3_ptjtr_sweight->Fill(jt, r, jet_pt, event_weight*sweight);

      h2_ptz_sweight->Fill(z, jet_pt, event_weight*sweight);
      h2_ptjt_sweight->Fill(jt, jet_pt, event_weight*sweight);
      h2_ptr_sweight->Fill(r, jet_pt, event_weight*sweight);   

      h2_mB_mJpsi->Fill(bmass_dtf, Jpsi.M()); 
    }
    
  } // end event loop

  ///////////////// ////////////////
  // Background Subtraction
  ////////////// ////////////////

  // NOTE!! Integrals do not yield the exact same numbers in all cases before sideband subtraction unless underflow and overflow bins are supplied as bounds (e.g. ptz->Integral(0, zbinsize+1, 0, ptbinsize+1))
  cout << "Before sub: " << endl;
  cout << "Num Jet pt = " << h1_jet_pt->Integral() << endl;
  cout << "In ptz = " << h2_ptz->Integral() << endl;
  cout << "In ptjt = " << h2_ptjt->Integral() << endl;
  cout << "In ptr = " << h2_ptr->Integral() << endl;
  cout << "In ptzjt = " << h3_ptzjt->Integral() << endl;
  cout << "In ptzr = " << h3_ptzr->Integral() << endl;
  cout << "In ptjtr = " << h3_ptjtr->Integral() << endl;
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
  cout << "After sub: " << endl;
  cout << "Num Jet pt = " << h1_jet_pt->Integral() << endl;
  cout << "In ptz = " << h2_ptz->Integral() << endl;
  cout << "In ptjt = " << h2_ptjt->Integral() << endl;
  cout << "In ptr = " << h2_ptr->Integral() << endl;
  cout << "In ptzjt = " << h3_ptzjt->Integral() << endl;
  cout << "In ptzr = " << h3_ptzr->Integral() << endl;
  cout << "In ptjtr = " << h3_ptjtr->Integral() << endl;

  THStack *hs_ptz = new THStack("hs_ptz", ";z;#frac{1}{N_{jets}}#frac{dN}{dz}");
  THStack *hs_ptjt = new THStack("hs_ptjt", ";j_{T} [GeV/c];#frac{1}{N_{jets}}#frac{dN}{dj_{T}}");
  THStack *hs_ptr = new THStack("hs_ptr", ";r;#frac{1}{N_{jets}}#frac{dN}{dr}");    
  THStack *hs_ptz_sweight = new THStack("hs_ptz_sweight", ";z;#frac{1}{N_{jets}}#frac{dN}{dz}");
  THStack *hs_ptjt_sweight = new THStack("hs_ptjt_sweight", ";j_{T} [GeV/c];#frac{1}{N_{jets}}#frac{dN}{dj_{T}}");
  THStack *hs_ptr_sweight = new THStack("hs_ptr_sweight", ";r;#frac{1}{N_{jets}}#frac{dN}{dr}");        
  THStack *hs_ptz_uncorrected = new THStack("z_uncorrected_data_all", ";z;#frac{1}{N_{jets}}#frac{dN}{dz}");
  THStack *hs_ptjt_uncorrected = new THStack("jt_uncorrected_data_all", ";j_{T} [GeV/c];#frac{1}{N_{jets}}#frac{dN}{dj_{T}}");
  THStack *hs_ptr_uncorrected = new THStack("r_uncorrected_data_all", ";r;#frac{1}{N_{jets}}#frac{dN}{dr}");
  THStack *hs_ptz_nobgsub = new THStack("z_evtweights_nosbsub_data_all", ";z;#frac{1}{N_{jets}}#frac{dN}{dz}");
  THStack *hs_ptjt_nobgsub = new THStack("jt_evtweights_nosbsub_data_all", ";j_{T} [GeV/c];#frac{1}{N_{jets}}#frac{dN}{dj_{T}}");
  THStack *hs_ptr_nobgsub = new THStack("r_evtweights_nosbsub_data_all", ";r;#frac{1}{N_{jets}}#frac{dN}{dr}");  
  
  TH2D *h2_zjt_ptbinned_uncorrected[ptbinsize-1], *h2_zjt_ptbinned[ptbinsize-1];
  TH2D *h2_zr_ptbinned_uncorrected[ptbinsize-1], *h2_zr_ptbinned[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_uncorrected[ptbinsize-1], *h2_jtr_ptbinned[ptbinsize-1];       
  for (int j = 1; j < ptbinsize; j++)
  {   
    
    TH1D *h1_ptz_temp = (TH1D *)h2_ptz->ProjectionX(Form("z_pt%d", j), j + 1, j + 1); 
    NormalizeHist(h1_ptz_temp);
    h1_ptz_temp->SetStats(0);
    h1_ptz_temp->SetMarkerStyle(j + 20);
    if (j!=5) 
    {
      h1_ptz_temp->SetMarkerColor(j);
      h1_ptz_temp->SetLineColor(j);
    }
    else
    {
      h1_ptz_temp->SetMarkerColor(j*j+3);
      h1_ptz_temp->SetLineColor(j*j+3);
    }
    h1_ptz_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));
    //h1_ptz_temp->SetOption("PE HIST");
    hs_ptz->Add(h1_ptz_temp);

    TH1D *h1_ptjt_temp = (TH1D *)h2_ptjt->ProjectionX(Form("jt_pt%d", j), j + 1, j + 1); 
    NormalizeHist(h1_ptjt_temp);        
    h1_ptjt_temp->SetStats(0);
    h1_ptjt_temp->SetMarkerStyle(j + 20);
    if (j!=5) 
    {
      h1_ptjt_temp->SetMarkerColor(j);
      h1_ptjt_temp->SetLineColor(j);
    }
    else
    {
      h1_ptjt_temp->SetMarkerColor(j*j+3);
      h1_ptjt_temp->SetLineColor(j*j+3);
    }
    h1_ptjt_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));        
    hs_ptjt->Add(h1_ptjt_temp);
    
    TH1D *h1_ptr_temp = (TH1D *)h2_ptr->ProjectionX(Form("r_pt%d", j), j + 1, j + 1); 
    NormalizeHist(h1_ptr_temp);        
    h1_ptr_temp->SetStats(0);
    h1_ptr_temp->SetMarkerStyle(j + 20);
    if (j!=5) 
    {
      h1_ptr_temp->SetMarkerColor(j);
      h1_ptr_temp->SetLineColor(j);
    }
    else
    {
      h1_ptr_temp->SetMarkerColor(j*j+3);
      h1_ptr_temp->SetLineColor(j*j+3);
    }
    h1_ptr_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));        
    hs_ptr->Add(h1_ptr_temp);   
    

    // Sweighted distributions
    h1_ptz_temp = (TH1D *)h2_ptz_sweight->ProjectionX(Form("z_sweight_pt%d", j), j + 1, j + 1); 
    NormalizeHist(h1_ptz_temp);
    h1_ptz_temp->SetStats(0);
    h1_ptz_temp->SetMarkerStyle(j + 20);
    if (j!=5) 
    {
      h1_ptz_temp->SetMarkerColor(j);
      h1_ptz_temp->SetLineColor(j);
    }
    else
    {
      h1_ptz_temp->SetMarkerColor(j*j+3);
      h1_ptz_temp->SetLineColor(j*j+3);
    }
    h1_ptz_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));
    //h1_ptz_temp->SetOption("PE HIST");
    hs_ptz_sweight->Add(h1_ptz_temp);

    h1_ptjt_temp = (TH1D *)h2_ptjt_sweight->ProjectionX(Form("jt_sweight_pt%d", j), j + 1, j + 1); 
    NormalizeHist(h1_ptjt_temp);        
    h1_ptjt_temp->SetStats(0);
    h1_ptjt_temp->SetMarkerStyle(j + 20);
    if (j!=5) 
    {
      h1_ptjt_temp->SetMarkerColor(j);
      h1_ptjt_temp->SetLineColor(j);
    }
    else
    {
      h1_ptjt_temp->SetMarkerColor(j*j+3);
      h1_ptjt_temp->SetLineColor(j*j+3);
    }
    h1_ptjt_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));        
    hs_ptjt_sweight->Add(h1_ptjt_temp);
    
    h1_ptr_temp = (TH1D *)h2_ptr_sweight->ProjectionX(Form("r_sweight_pt%d", j), j + 1, j + 1); 
    NormalizeHist(h1_ptr_temp);        
    h1_ptr_temp->SetStats(0);
    h1_ptr_temp->SetMarkerStyle(j + 20);
    if (j!=5) 
    {
      h1_ptr_temp->SetMarkerColor(j);
      h1_ptr_temp->SetLineColor(j);
    }
    else
    {
      h1_ptr_temp->SetMarkerColor(j*j+3);
      h1_ptr_temp->SetLineColor(j*j+3);
    }
    h1_ptr_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));        
    hs_ptr_sweight->Add(h1_ptr_temp);  

    if (isData)
    {
      // Add uncorrected z histos (pt binned) to THStack
      h1_ptz_temp = (TH1D *)h2_ptz_uncorrected->ProjectionX(Form("z_pt%d_raw", j), j + 1, j + 1); 
      h1_ptz_temp->SetStats(0);
      NormalizeHist(h1_ptz_temp);
      h1_ptz_temp->SetMarkerStyle(j + 20);
      if (j!=5) 
      {
        h1_ptz_temp->SetMarkerColor(j);
        h1_ptz_temp->SetLineColor(j);
      }
      else
      {
        h1_ptz_temp->SetMarkerColor(j*j+3);
        h1_ptz_temp->SetLineColor(j*j+3);
      }
      h1_ptz_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));                
      hs_ptz_uncorrected->Add(h1_ptz_temp);
      
      // Add uncorrected jt histos (pt binned) to THStack        
      h1_ptjt_temp = (TH1D *)h2_ptjt_uncorrected->ProjectionX(Form("jt_pt%d_raw", j), j + 1, j + 1); 
      h1_ptjt_temp->SetStats(0);
      NormalizeHist(h1_ptjt_temp);
      h1_ptjt_temp->SetMarkerStyle(j + 20);
      if (j!=5) 
      {
        h1_ptjt_temp->SetMarkerColor(j);
        h1_ptjt_temp->SetLineColor(j);
      }
      else
      {
        h1_ptjt_temp->SetMarkerColor(j*j+3);
        h1_ptjt_temp->SetLineColor(j*j+3);
      }
      h1_ptjt_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));                
      hs_ptjt_uncorrected->Add(h1_ptjt_temp);  
      
      // Add uncorrected r histos (pt binned) to THStack
      h1_ptr_temp = (TH1D *)h2_ptr_uncorrected->ProjectionX(Form("r_pt%d_raw", j), j + 1, j + 1); 
      h1_ptr_temp->SetStats(0);
      NormalizeHist(h1_ptr_temp);
      h1_ptr_temp->SetMarkerStyle(j + 20);
      if (j!=5) 
      {
        h1_ptr_temp->SetMarkerColor(j);
        h1_ptr_temp->SetLineColor(j);
      }
      else
      {
        h1_ptr_temp->SetMarkerColor(j*j+3);
        h1_ptr_temp->SetLineColor(j*j+3);
      }
      h1_ptr_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));                
      hs_ptr_uncorrected->Add(h1_ptr_temp);
      
      // Add no bg sub z histos (pt binned) to THStack
      h1_ptz_temp = (TH1D *)h2_ptz_nobgsub->ProjectionX(Form("z_pt%d_nobgsub", j), j + 1, j + 1); 
      h1_ptz_temp->SetStats(0);
      NormalizeHist(h1_ptz_temp);
      h1_ptz_temp->SetMarkerStyle(j + 20);
      if (j!=5) 
      {
        h1_ptz_temp->SetMarkerColor(j);
        h1_ptz_temp->SetLineColor(j);
      }
      else
      {
        h1_ptz_temp->SetMarkerColor(j*j+3);
        h1_ptz_temp->SetLineColor(j*j+3);
      }
      h1_ptz_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));                
      hs_ptz_nobgsub->Add(h1_ptz_temp);
      
      // Add no bg sub jt histos (pt binned) to THStack        
      h1_ptjt_temp = (TH1D *)h2_ptjt_nobgsub->ProjectionX(Form("jt_pt%d_nobgsub", j), j + 1, j + 1); 
      h1_ptjt_temp->SetStats(0);
      NormalizeHist(h1_ptjt_temp);
      h1_ptjt_temp->SetMarkerStyle(j + 20);
      if (j!=5) 
      {
        h1_ptjt_temp->SetMarkerColor(j);
        h1_ptjt_temp->SetLineColor(j);
      }
      else
      {
        h1_ptjt_temp->SetMarkerColor(j*j+3);
        h1_ptjt_temp->SetLineColor(j*j+3);
      }
      h1_ptjt_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));                
      hs_ptjt_nobgsub->Add(h1_ptjt_temp);  
      
      // Add no bg sub r histos (pt binned) to THStack
      h1_ptr_temp = (TH1D *)h2_ptr_nobgsub->ProjectionX(Form("r_pt%d_nobgsub", j), j + 1, j + 1); 
      h1_ptr_temp->SetStats(0);
      NormalizeHist(h1_ptr_temp);
      h1_ptr_temp->SetMarkerStyle(j + 20);
      if (j!=5) 
      {
        h1_ptr_temp->SetMarkerColor(j);
        h1_ptr_temp->SetLineColor(j);
      }
      else
      {
        h1_ptr_temp->SetMarkerColor(j*j+3);
        h1_ptr_temp->SetLineColor(j*j+3);
      }
      h1_ptr_temp->SetTitle(Form("%.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]));                
      hs_ptr_nobgsub->Add(h1_ptr_temp);                                    
      
        
    
      h3_ptzjt_uncorrected->GetZaxis()->SetRange(j+1, j+1);      
      h2_zjt_ptbinned_uncorrected[j-1] = (TH2D *)h3_ptzjt_uncorrected->Project3D("yx");
      h2_zjt_ptbinned_uncorrected[j-1]->SetName(Form("zjt_uncorrected_pt%d",j)); 
      NormalizeHist(h2_zjt_ptbinned_uncorrected[j-1]);	

      h3_ptzr_uncorrected->GetZaxis()->SetRange(j+1, j+1);        
      h2_zr_ptbinned_uncorrected[j-1] = (TH2D *)h3_ptzr_uncorrected->Project3D("yx");
      h2_zr_ptbinned_uncorrected[j-1]->SetName(Form("zr_uncorrected_pt%d",j));
      NormalizeHist(h2_zr_ptbinned_uncorrected[j-1]);	
      
      h3_ptjtr_uncorrected->GetZaxis()->SetRange(j+1, j+1);        
      h2_jtr_ptbinned_uncorrected[j-1] = (TH2D *)h3_ptjtr_uncorrected->Project3D("yx");
      h2_jtr_ptbinned_uncorrected[j-1]->SetName(Form("jtr_uncorrected_pt%d",j));
      NormalizeHist(h2_jtr_ptbinned_uncorrected[j-1]);	
    }  
    
    h3_ptzjt->GetZaxis()->SetRange(j+1, j+1);             
    h2_zjt_ptbinned[j-1] = (TH2D *)h3_ptzjt->Project3D("yx");
    if (isData)
      h2_zjt_ptbinned[j-1]->SetName(Form("zjt_pt%d",j));
    else
      h2_zjt_ptbinned[j-1]->SetName(Form("zjt_reco_pt%d",j));                              
    NormalizeHist(h2_zjt_ptbinned[j-1]);

    h3_ptzr->GetZaxis()->SetRange(j+1, j+1);  
    h2_zr_ptbinned[j-1] = (TH2D *)h3_ptzr->Project3D("yx");     
    if (isData)
      h2_zr_ptbinned[j-1]->SetName(Form("zr_pt%d",j));
    else
      h2_zr_ptbinned[j-1]->SetName(Form("zr_reco_pt%d",j));                    
    NormalizeHist(h2_zr_ptbinned[j-1]);

    h3_ptjtr->GetZaxis()->SetRange(j+1, j+1);
    h2_jtr_ptbinned[j-1] = (TH2D *)h3_ptjtr->Project3D("yx");    
    if (isData)
      h2_jtr_ptbinned[j-1]->SetName(Form("jtr_pt%d",j));
    else
      h2_jtr_ptbinned[j-1]->SetName(Form("jtr_reco_pt%d",j));             
    NormalizeHist(h2_jtr_ptbinned[j-1]);        
  }  

  h1_nSPDHits->Write();
  if (isData)
  {
      hs_ptz->SetName("z_evtweights_sbsub_data_all");
      hs_ptjt->SetName("jt_evtweights_sbsub_data_all");
      hs_ptr->SetName("r_evtweights_sbsub_data_all");    
      //hs_ptz_sweight->SetName("z_evtweights_sbsub_data_sweight_all");
      //hs_ptjt_sweight->SetName("jt_evtweights_sbsub_data_sweight_all");
      //hs_ptr_sweight->SetName("r_evtweights_sbsub_data_sweight_all");   
      hs_ptz_uncorrected->Write();
      hs_ptjt_uncorrected->Write();   
      hs_ptr_uncorrected->Write();      
      hs_ptz_nobgsub->Write();
      hs_ptjt_nobgsub->Write();
      hs_ptr_nobgsub->Write();
  }
  else
  {
      hs_ptz->SetName("z_reco_all");
      hs_ptjt->SetName("jt_reco_all");
      hs_ptr->SetName("r_reco_all");
  }

  hs_ptz->Write();
  hs_ptjt->Write();
  hs_ptr->Write();
  hs_ptz_sweight->Write();
  hs_ptjt_sweight->Write();
  hs_ptr_sweight->Write();

  h3_ptzjt->GetZaxis()->SetRange(1, ptbinsize+1);
  h3_ptzr->GetZaxis()->SetRange(1, ptbinsize+1);
  h3_ptjtr->GetZaxis()->SetRange(1, ptbinsize+1);
  h3_ptzjt_uncorrected->GetZaxis()->SetRange(1, ptbinsize+1);
  h3_ptzr_uncorrected->GetZaxis()->SetRange(1, ptbinsize+1);
  h3_ptjtr_uncorrected->GetZaxis()->SetRange(1, ptbinsize+1);    
        
  SetRecoStyle(h1_jet_eta);
  SetDataStyle(h1_jet_rap);
  SetRecoStyle(h1_jet_pt);
  SetRecoStyle(h1_jet_phi);

  SetRecoStyle(h1_HF_rap);
  SetRecoStyle(h1_HF_pt);
  SetRecoStyle(h1_HF_mass);
  SetRecoStyle(h1_HF_phi);
    
  SetRecoStyle(h1_z);
  SetRecoStyle(h1_jt);
  SetRecoStyle(h1_r);
    
  SetRecoStyle(h1_Jpsi_rap);
  SetRecoStyle(h1_Jpsi_pt);
  SetRecoStyle(h1_Jpsi_mass);
  SetRecoStyle(h1_Jpsi_ipchi2);

  SetRecoStyle(h1_z_comb);
  SetRecoStyle(h1_jt_comb);
  SetRecoStyle(h1_r_comb);


/*
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
    
    cout <<" start of z plots " << endl;
    ccan[ican]->cd(1);
    auto legend_zpt_raw= new TLegend(0.15, 0.5, 0.5, 0.85);
    legend_zpt_raw ->SetTextSize(0.03);
    legend_zpt_raw ->SetBorderSize(0);
    legend_zpt_raw ->SetFillStyle(0);
    legend_zpt_raw ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptz_uncorrected->ProjectionX(Form("z_pt%d_raw", i), i + 1, i + 1); 
      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->GetYaxis()->SetRangeUser(0.0, 4.0);        
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
  
      legend_zpt_raw->AddEntry(h1_temp, Form(" %.1f < uncorrected p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_zpt_raw -> Draw("SAME");  
     
    ccan[ican]->cd(2);  
    if (isData)
    { 
      auto legend_zpt_nobgsub= new TLegend(0.15, 0.5, 0.5, 0.85);
      legend_zpt_nobgsub ->SetTextSize(0.03);
      legend_zpt_nobgsub ->SetBorderSize(0);
      legend_zpt_nobgsub ->SetFillStyle(0);
      legend_zpt_nobgsub ->SetFillColor(3);
      for (int i = 1; i < ptbinsize; i++)
      {
        TH1D *h1_temp = (TH1D *)h2_ptz_nobgsub->ProjectionX(Form("z_pt%d_nobgsub", i), i + 1, i + 1); 
        h1_temp->SetStats(0);
        NormalizeHist(h1_temp);
        h1_temp->SetMarkerStyle(i + 20);
        if (i!=5) 
        {
          h1_temp->SetMarkerColor(i);
          h1_temp->SetLineColor(i);
        }
        else
        {
          h1_temp->SetMarkerColor(i*i+3);
          h1_temp->SetLineColor(i*i+3);
        }
        h1_temp->GetYaxis()->SetRangeUser(0.0, 4.0);        
        h1_temp->Draw("P E SAME");
        h1_temp->Draw("HIST SAME");
  
        legend_zpt_nobgsub->AddEntry(h1_temp, Form(" %.1f < no sb sub p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
      }
      
      legend_zpt_nobgsub -> Draw("SAME");       
    }   

    ccan[ican]->cd(3);
    auto legend_zpt = new TLegend(0.15, 0.5, 0.5, 0.85);
    legend_zpt ->SetTextSize(0.03);
    legend_zpt ->SetBorderSize(0);
    legend_zpt ->SetFillStyle(0);
    legend_zpt ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptz->ProjectionX(Form("z_pt%d", i), i + 1, i + 1);
      h1_temp->SetStats(0);   
      h1_temp->GetXaxis()->SetTitle("z");   
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->GetYaxis()->SetRangeUser(0.0, 4.0);
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");

      
      legend_zpt->AddEntry(h1_temp, Form(" %.1f < p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_zpt -> Draw("SAME");        

    ccan[ican]->cd(4);
    auto legend_zpt_final = new TLegend(0.15, 0.5, 0.5, 0.85);
    legend_zpt_final ->SetTextSize(0.03);
    legend_zpt_final ->SetBorderSize(0);
    legend_zpt_final ->SetFillStyle(0);
    legend_zpt_final ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptz_final->ProjectionX(Form("z_pt%d_final", i), i + 1, i + 1);
      h1_temp->SetStats(0);   
      h1_temp->GetXaxis()->SetTitle("z");   
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->GetYaxis()->SetRangeUser(0.0, 4.0);
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");

      
      legend_zpt_final->AddEntry(h1_temp, Form(" %.1f < Unfolded p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_zpt_final -> Draw("SAME");    
  
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
    
 
     // jT pT   
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
    auto legend_jtpt_raw= new TLegend(0.45, 0.6, 0.75, 0.9);
    legend_jtpt_raw ->SetTextSize(0.03);
    legend_jtpt_raw ->SetBorderSize(0);
    legend_jtpt_raw ->SetFillStyle(0);
    legend_jtpt_raw ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt_uncorrected->ProjectionX(Form("jt_pt%d_raw", i), i + 1, i + 1); 
      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->SetMaximum(20.0);            
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
  
      legend_jtpt_raw->AddEntry(h1_temp, Form(" %.1f < uncorrected p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_jtpt_raw -> Draw("SAME");
     
    ccan[ican]->cd(2); 
    gPad->SetLogy();         
    if (isData)
    {
      auto legend_jtpt_nobgsub= new TLegend(0.45, 0.6, 0.75, 0.9);
      legend_jtpt_nobgsub ->SetTextSize(0.03);
      legend_jtpt_nobgsub ->SetBorderSize(0);
      legend_jtpt_nobgsub ->SetFillStyle(0);
      legend_jtpt_nobgsub ->SetFillColor(3);  
      for (int i = 1; i < ptbinsize; i++)
      {
        TH1D *h1_temp = (TH1D *)h2_ptjt_nobgsub->ProjectionX(Form("jt_pt%d_nobgsub", i), i + 1, i + 1); 
        h1_temp->SetStats(0);
        NormalizeHist(h1_temp);
        h1_temp->SetMarkerStyle(i + 20);
        if (i!=5) 
        {
          h1_temp->SetMarkerColor(i);
          h1_temp->SetLineColor(i);
        }
        else
        {
          h1_temp->SetMarkerColor(i*i+3);
          h1_temp->SetLineColor(i*i+3);
        }  
        h1_temp->SetMaximum(20.0);             
        h1_temp->Draw("P E SAME");
        h1_temp->Draw("HIST SAME");
  
        legend_jtpt_nobgsub->AddEntry(h1_temp, Form(" %.1f < no sb sub p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
      }
      
      legend_jtpt_nobgsub -> Draw("SAME");
    }      

    ccan[ican]->cd(3);
    gPad->SetLogy();        
    auto legend_jtpt = new TLegend(0.45, 0.6, 0.75, 0.9);
    legend_jtpt ->SetTextSize(0.03);
    legend_jtpt ->SetBorderSize(0);
    legend_jtpt ->SetFillStyle(0);
    legend_jtpt ->SetFillColor(3); 
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt->ProjectionX(Form("jt_pt%d", i), i + 1, i + 1);
      h1_temp->SetStats(0);   
      h1_temp->GetXaxis()->SetTitle("j_{T} [GeV/c]");   
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->SetMaximum(20.0);       
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");

      
      legend_jtpt->AddEntry(h1_temp, Form(" %.1f < p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_jtpt -> Draw("SAME");        

    ccan[ican]->cd(4);
    gPad->SetLogy();        
    auto legend_jtpt_final = new TLegend(0.45, 0.6, 0.75, 0.9);
    legend_jtpt_final ->SetTextSize(0.03);
    legend_jtpt_final ->SetBorderSize(0);
    legend_jtpt_final ->SetFillStyle(0);
    legend_jtpt_final ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptjt_final->ProjectionX(Form("jt_pt%d_final", i), i + 1, i + 1);
      h1_temp->SetStats(0);   
      h1_temp->GetXaxis()->SetTitle("j_{T} [GeV/c]");   
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->SetMaximum(20.0);       
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");

      
      legend_jtpt_final->AddEntry(h1_temp, Form(" %.1f < Unfolded p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_jtpt_final -> Draw("SAME");   

 
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
    
    // r histograms //
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->cd();    
    ccan[ican]->SetFillColor(10);    
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);     
    gPad->SetLogy();    
            
    ccan[ican]->cd(1);
    auto legend_rpt_raw= new TLegend(0.45, 0.6, 0.75, 0.9);
    legend_rpt_raw ->SetTextSize(0.03);
    legend_rpt_raw ->SetBorderSize(0);
    legend_rpt_raw ->SetFillStyle(0);
    legend_rpt_raw ->SetFillColor(3); 
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr_uncorrected->ProjectionX(Form("r_pt%d_raw", i), i + 1, i + 1); 
      h1_temp->SetStats(0);
      NormalizeHist(h1_temp);
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }    
      h1_temp->SetMaximum(800.0);               
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");
  
      legend_rpt_raw->AddEntry(h1_temp, Form(" %.1f < uncorrected p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_rpt_raw -> Draw("SAME");
     
    ccan[ican]->cd(2);
    gPad->SetLogy();            
    if (isData)
    {
      auto legend_rpt_nobgsub= new TLegend(0.45, 0.6, 0.75, 0.9);
      legend_rpt_nobgsub ->SetTextSize(0.03);
      legend_rpt_nobgsub ->SetBorderSize(0);
      legend_rpt_nobgsub ->SetFillStyle(0);
      legend_rpt_nobgsub ->SetFillColor(3);
      for (int i = 1; i < ptbinsize; i++)
      {
        TH1D *h1_temp = (TH1D *)h2_ptr_nobgsub->ProjectionX(Form("r_pt%d_nobgsub", i), i + 1, i + 1); 
        h1_temp->SetStats(0);
        NormalizeHist(h1_temp);
        h1_temp->SetMarkerStyle(i + 20);
        if (i!=5) 
        {
          h1_temp->SetMarkerColor(i);
          h1_temp->SetLineColor(i);
        }
        else
        {
          h1_temp->SetMarkerColor(i*i+3);
          h1_temp->SetLineColor(i*i+3);
        }        
        h1_temp->SetMaximum(800.0);
        h1_temp->Draw("P E SAME");
        h1_temp->Draw("HIST SAME");
  
        legend_rpt_nobgsub->AddEntry(h1_temp, Form(" %.1f < no sb sub p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
      }
      
      legend_rpt_nobgsub -> Draw("SAME");
    }   
      
    ccan[ican]->cd(3);
    gPad->SetLogy();       
    auto legend_rpt = new TLegend(0.45, 0.6, 0.75, 0.9);
    legend_rpt ->SetTextSize(0.03);
    legend_rpt ->SetBorderSize(0);
    legend_rpt ->SetFillStyle(0);
    legend_rpt ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr->ProjectionX(Form("r_pt%d", i), i + 1, i + 1);
      h1_temp->SetStats(0);   
      h1_temp->GetXaxis()->SetTitle("r");   
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->SetMaximum(800.0);       
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");

      
      legend_rpt->AddEntry(h1_temp, Form(" %.1f < p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_rpt -> Draw("SAME");        

    ccan[ican]->cd(4);
    gPad->SetLogy();       
    auto legend_rpt_final = new TLegend(0.45, 0.6, 0.75, 0.9);
    legend_rpt_final ->SetTextSize(0.03);
    legend_rpt_final ->SetBorderSize(0);
    legend_rpt_final ->SetFillStyle(0);
    legend_rpt_final ->SetFillColor(3);
    for (int i = 1; i < ptbinsize; i++)
    {
      TH1D *h1_temp = (TH1D *)h2_ptr_final->ProjectionX(Form("r_pt%d_final", i), i + 1, i + 1);
      h1_temp->SetStats(0);   
      h1_temp->GetXaxis()->SetTitle("r");   
      NormalizeHist(h1_temp);    
      h1_temp->SetMarkerStyle(i + 20);
      if (i!=5) 
      {
        h1_temp->SetMarkerColor(i);
        h1_temp->SetLineColor(i);
      }
      else
      {
        h1_temp->SetMarkerColor(i*i+3);
        h1_temp->SetLineColor(i*i+3);
      }
      h1_temp->SetMaximum(800.0);       
      h1_temp->Draw("P E SAME");
      h1_temp->Draw("HIST SAME");

      
      legend_rpt_final->AddEntry(h1_temp, Form(" %.1f < Unfolded p_{T, jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    }
    legend_rpt_final -> Draw("SAME");  
      
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
    
*/
  f.Write();
  f.Close();
  /*
  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }
  */
}
