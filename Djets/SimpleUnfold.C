

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

// #include "ZjetLuC"

#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <TH3.h>
#include <TF1.h>
#include <TLatex.h>
#include <THStack.h>
#include <TChain.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TEfficiency.h>
#include "Settings.h"
#include "../Helpers.h"

// using namespace std;

void SimpleUnfold(int NumEvts = -1,
                  int dataset = 90499,
                  bool chargedJetCut_user = false,
                  bool WTA_cut = false,
                  float minimum_dR = 0.1,
                  bool DoReverse = false,
                  int DoJES = 0,
                  bool DoJER = false,
                  bool DoFSPEff = false,
                  bool DoFSPPT = false,
                  bool DoGhostCut = false,
                  bool DoRecSelEff = false,
                  bool DoSignalSys = false,
                  bool DoUnfoldPrior = false,
                  bool DoJetID = false,
                  bool SubtractGS = false,
                  int PromptCut = 0)
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
  int ptrange = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int prompt_int = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;
  int tr_HF_pdgcode = -99;

  if (flavor == 5)
  {
    mass_num = 4.2;
    HF_pdgcode = 521;
  }
  else if (flavor == 4)
  {
    mass_num = 1.25;
    HF_pdgcode = 411;
    tr_HF_pdgcode = 431;
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

  str_year = (year == 6) ? "2016" : (year == 7) ? "2017"
                                : (year == 8)   ? "2018"
                                                : "";

  str_Mag = Mag == 0 ? "_MD" : Mag == 1 ? "_MU"
                                        : "";
  str_flavor = flavor == 1 ? "_udsg" : flavor == 4 ? "_c"
                                   : flavor == 5   ? "_b"
                                                   : "";
  str_GS = SubtractGS ? "_GSsub" : "";
  str_level = truthLevel ? "truth" : "reco";
  str_followHard = flavor == 1 ? "_hard" : "_HF";
  str_followHard = followHardest ? "_hard" : "_HF";
  str_ghost = ghostCut ? Form("_ghost_%.1f", ghostProb) : "";
  str_charged = chargedJetCut ? "_charge" : "";
  str_eta = Form("_eta_%.1f%.1f", etaMin, etaMax);
  str_pt = Form("_ptj_%d%d", int(ptMin), int(ptMax));
  str_Nevts = Form("_ev_%d", NumEvts);
  str_WTA = WTA_cut ? "_WTA" : "";
  str_DTF = DTF_cut ? "_DTF" : "";
  str_PID = PID_cut ? "_PID" : "";
  str_prompt = (PromptCut == 1) ? "_prompt" : (PromptCut == 2) ? "_nonprompt"
                                                               : "";
  TString str_tree;
  TString extension, extension_prefix;
  extension = TString("unfold_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag + str_flavor + str_GS + str_WTA + str_prompt + Form("_%d", dataset);
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
  if (DoFSPPT)
    extension_prefix = TString("fsppt_");
  if (DoGhostCut)
    extension_prefix = TString("ghostcut_");
  if (DoRecSelEff)
    extension_prefix = TString("recselsys_");
  if (DoSignalSys)
    extension_prefix = TString("signalsys_");
  if (DoUnfoldPrior)
    extension_prefix = TString("priorsys_");
  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  TString extension_read, extension_eff, extension_RootFilesMC, extension_RootFilesData;

  extension_RootFilesMC = TString("../../root_files/DjetsMC/");
  extension_RootFilesData = TString("../../root_files/Djets/");

  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);
  // extension_eff = TString("efficiency_truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag + str_flavor + str_GS + str_WTA + str_prompt + Form("_%d", dataset);
  extension_eff = TString("efficiency_truth_ev_3500000_ptj_20100_eta_2.54.0_HF_c_WTA_90499");

  if (!DoReverse)
    extension_read = extension_prefix + extension_read;
  extension = extension_prefix + extension;

  // TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
  cout << "File:" << endl;
  cout << extension_read << endl;

  TFile *file_eff = new TFile(extension_RootFilesMC + extension_eff + TString(".root"), "READ");
  TFile *file_decay = new TFile(extension_RootFilesMC + "HFeff_truth_ev_-1" + str_Mag + str_flavor + str_WTA + Form("_%d.root", dataset), "READ");

  TChain *DTree = new TChain("DTree", "");
  vector<int> vec_datasets;
  int Mags[2] = {0, 1};
  int years[3] = {6, 7, 8};
  int prompts[2] = {0, 1};
  int ptranges[6] = {1, 2, 3, 4, 5, 6};
  std::map<int, vector<int>> my_map;

  // vec_datasets = {62400, 62401, 72400, 72401, 82400, 82401, 63400, 63401, 73400, 73401, 83400, 83401, 67400, 67401, 77400, 77401, 87400, 87401};

  // for (int i = 0; i < 2; i++)
  // {
  //   if (Mag == 0 && Mags[i] != 0)
  //     continue;
  //   if (Mag == 1 && Mags[i] != 1)
  //     continue;

  //   for (int j = 0; j < 2; j++)
  //   {
  //     if (prompt_int == 0 && prompts[j] != 0)
  //       continue;
  //     if (prompt_int == 1 && prompts[j] != 1)
  //       continue;
  //     for (int k = 0; k < 6; k++)
  //     {
  //       if (ptranges[k] == 1 || ptranges[k] == 5)
  //         continue;

  //       if (ptrange == 1 && ptranges[k] != 1)
  //         continue;
  //       if (ptrange == 2 && ptranges[k] != 2)
  //         continue;
  //       if (ptrange == 3 && ptranges[k] != 3)
  //         continue;
  //       if (ptrange == 4 && ptranges[k] != 4)
  //         continue;
  //       if (ptrange == 5 && ptranges[k] != 5)
  //         continue;
  //       if (ptrange == 6 && ptranges[k] != 6)
  //         continue;
  //       for (int l = 0; l < 3; l++)
  //       {
  //         if (year == 6 && years[l] != 6)
  //           continue;
  //         if (year == 7 && years[l] != 7)
  //           continue;
  //         if (year == 8 && years[l] != 8)
  //           continue;
  //         int num = 10000 * years[l] + 1000 * ptranges[k] + 400 + 10 * prompts[j] + Mags[i];
  //         cout << num << endl;
  //         cout << years[l] << ", " << ptranges[k] << ", " << prompts[j] << ", " << Mags[i] << endl;
  //         vec_datasets.push_back(num);
  //       }
  //     }
  //   }
  // }

  // my_map = {
  //     {60490, {60490}},
  //     {60491, {60491}},
  //     {60499, {60490, 60491}},
  //     {70490, {70490}},
  //     {70491, {70491}},
  //     {70499, {70490, 70491}},
  //     {80490, {80490}},
  //     {80491, {80491}},
  //     {80499, {80490, 80491}},
  //     {90490, {60490, 70490, 80490}},
  //     {90491, {60491, 70491, 80491}},
  //     {90499, {60490, 60491, 70490, 70491, 80490, 80491}}};
  // if (Mag == 0)
  //   vec_datasets = {60490, 70490, 80490};
  // else if (Mag == 1)
  //   vec_datasets = {60491, 70491, 80491};
  // else
  //   vec_datasets = {60490, 60491, 70490, 70491, 80490, 80491};

  // if (year == 9 && JetMeth != 9)
  // {
  // for (int i = 0; i < my_map[dataset].size(); i++)
  // {
  //   Mag = (my_map[dataset][i] / 1) % 10;
  //   if (Mag == 0)
  //     str_Mag = "_MD";
  //   else if (Mag == 1)
  //     str_Mag = "_MU";
  //   extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", my_map[dataset][i]);
  //   if (!DoRecSelEff && DoMassFit == 0 && DoSignalSys == 0)
  //     extension_read = extension_prefix + extension_read;

  //   DTree->Add(dir_deadcone+"hists/" + extension_read + ".root/DTree");
  // }

  // vec_datasets = {62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};
  vec_datasets = {61400, 61401, 62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};
  if (dataset == 99499)
    vec_datasets = {99499};
  if (year == 9)
  {
    for (int i = 0; i < vec_datasets.size(); i++)
    {
      cout << vec_datasets[i] << ", ";
      Mag = (vec_datasets[i] / 1) % 10;
      if (Mag == 0)
        str_Mag = "_MD";
      else if (Mag == 1)
        str_Mag = "_MU";
      extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", vec_datasets[i]);
      if (!(DoReverse || DoRecSelEff || DoSignalSys || DoUnfoldPrior))
        extension_read = extension_prefix + extension_read;
      cout << extension_read << endl;
      DTree->Add(extension_RootFilesMC + extension_read + ".root/DTree");
    }
  }

  else
  {
    extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);
    if (!(DoReverse || DoRecSelEff || DoSignalSys || DoUnfoldPrior))
      extension_read = extension_prefix + extension_read;
    DTree->Add(extension_RootFilesMC + extension_read + ".root/DTree");
  }
  if (NumEvts > DTree->GetEntries())
    NumEvts = DTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = DTree->GetEntries();

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
  TH2D *h2_denom_efficiency_zjt = (TH2D *)file_eff->Get("denom_efficiency_zjt");
  TH2D *h2_denom_efficiency_zr = (TH2D *)file_eff->Get("denom_efficiency_zr");
  TH2D *h2_denom_efficiency_jtr = (TH2D *)file_eff->Get("denom_efficiency_jtr");

  TH2D *h2_denom_efficiency_ptz = (TH2D *)file_eff->Get("denom_efficiency_ptz");
  TH2D *h2_denom_efficiency_ptjt = (TH2D *)file_eff->Get("denom_efficiency_ptjt");
  TH2D *h2_denom_efficiency_ptr = (TH2D *)file_eff->Get("denom_efficiency_ptr");

  TH3D *h3_denom_efficiency_ptzjt = (TH3D *)file_eff->Get("denom_efficiency_ptzjt");
  TH3D *h3_denom_efficiency_ptzr = (TH3D *)file_eff->Get("denom_efficiency_ptzr");
  TH3D *h3_denom_efficiency_ptjtr = (TH3D *)file_eff->Get("denom_efficiency_ptjtr");

  TH2D *h2_denom_efficiency_ptz_50_100 = (TH2D *)file_eff->Get("denom_efficiency_ptz_50_100");
  TH2D *h2_denom_efficiency_ptjt_50_100 = (TH2D *)file_eff->Get("denom_efficiency_ptjt_50_100");
  TH2D *h2_denom_efficiency_ptr_50_100 = (TH2D *)file_eff->Get("denom_efficiency_ptr_50_100");

  TH3D *h3_denom_efficiency_ptzjt_50_100 = (TH3D *)file_eff->Get("denom_efficiency_ptzjt_50_100");
  TH3D *h3_denom_efficiency_ptzr_50_100 = (TH3D *)file_eff->Get("denom_efficiency_ptzr_50_100");
  TH3D *h3_denom_efficiency_ptjtr_50_100 = (TH3D *)file_eff->Get("denom_efficiency_ptjtr_50_100");

  // TH2D *h2_SVTag_eff_denom_z = (TH2D *)file_eff->Get("h2_SVTag_eff_denom_z");
  // TH2D *h2_SVTag_eff_denom = (TH2D *)file_eff->Get("h2_SVTag_eff_denom");

  TH1D *h1_recoHF_HFpt = (TH1D *)file_decay->Get("num_efficiency_HFpt");
  TH1D *h1_recoHF_jetpt = (TH1D *)file_decay->Get("num_efficiency_jetpt");
  TH2D *h2_recoHF_HFpteta = (TH2D *)file_decay->Get("num_efficiency_HFpteta");
  TH3D *h3_recoHF_HFptetajetpt = (TH3D *)file_decay->Get("num_efficiency_HFptetajetpt");

  TH1D *h1_HFeff_HFpt = (TH1D *)file_decay->Get("efficiency_HFpt");
  TH1D *h1_HFeff_jetpt = (TH1D *)file_decay->Get("efficiency_jetpt");
  TH2D *h2_HFeff_HFpteta = (TH2D *)file_decay->Get("efficiency_HFpteta");
  TH3D *h3_HFeff_HFptetajetpt = (TH3D *)file_decay->Get("efficiency_HFptetajetpt");

  /////////////////// Mass Fit Parameters /////////////////////////////////
  TString extension_mass(TString("massfit_data_ev_-1") + Form("_ptj_%d%d", int(pTLow), int(250.)) + "_eta_2.54.0_ghost_0.5_c" + str_WTA + "_90499.root");
  if (DoRecSelEff)
    extension_mass = "recselsys_" + extension_mass;
  if (DoSignalSys)
    extension_mass = "sys_" + extension_mass;
  extension_mass = extension_RootFilesData + extension_mass;
  TFile f_massfit(extension_mass, "READ");
  TH1D *h1_MassMin = (TH1D *)f_massfit.Get("h1_MassMin");
  TH1D *h1_MassMax = (TH1D *)f_massfit.Get("h1_MassMax");
  TH1D *h1_BkgScale = (TH1D *)f_massfit.Get("h1_BkgScale");
  TH1D *h1_BkgScaleNear = (TH1D *)f_massfit.Get("h1_BkgScale_forSysNear");
  TH1D *h1_BkgScaleFar = (TH1D *)f_massfit.Get("h1_BkgScale_forSysFar");

  if (h1_BkgScaleNear == NULL)
    cout << "NULL NEAR!" << endl;
  if (h1_BkgScaleFar == NULL)
    cout << "NULL FAR!" << endl;

  // TFile file_reco_weights("../../root_files/Djets/MC_DATA_WEIGHTS.root", "READ");
  // //
  // TH2D *h2_HFptrap_ratio;
  // TH3D *h3_HFptjetptrap_ratio;
  // TH3D *h3_dRzkt_ratio;
  // h2_HFptrap_ratio = (TH2D *)file_reco_weights.Get("h2_HFptrap_ratio");
  // h3_HFptjetptrap_ratio = (TH3D *)file_reco_weights.Get("h3_HFptjetptrap_ratio");

  TFile *f = TFile::Open(extension_RootFilesMC + extension + ".root", "RECREATE");

  // Reco 1D Observables
  TH1D *h1_z = new TH1D("z", "", zbinsize, z_binedges);
  TH1D *h1_jt = new TH1D("jt", "", jtbinsize, jt_binedges);
  TH1D *h1_r = new TH1D("r", "", rbinsize, r_binedges);

  // Truth 1D Observables
  TH1D *h1_z_truth = new TH1D("z_truth", "", zbinsize, z_binedges);
  TH1D *h1_jt_truth = new TH1D("jt_truth", "", jtbinsize, jt_binedges);
  TH1D *h1_r_truth = new TH1D("r_truth", "", rbinsize, r_binedges);

  // Reco 2D Observables (208 - 217)
  TH2D *h2_zjt = new TH2D("zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
  TH2D *h2_zr = new TH2D("zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
  TH2D *h2_jtr = new TH2D("jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);

  // Truth 2D Observables
  TH2D *h2_zjt_truth = new TH2D("zjt_truth", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
  TH2D *h2_zr_truth = new TH2D("zr_truth", "", zbinsize, z_binedges, rbinsize, r_binedges);
  TH2D *h2_jtr_truth = new TH2D("jtr_truth", "", jtbinsize, jt_binedges, rbinsize, r_binedges);

  // 2D Truth-Reco Correspondence (219 - 224)
  TH2D *h2_truthreco_z = new TH2D("truthreco_z", ";Reco z; Truth z", zbinsize, z_binedges, zbinsize, z_binedges);
  TH2D *h2_truthreco_jt = new TH2D("truthreco_jt", ";Reco jT; Truth jT", jtbinsize, jt_binedges, jtbinsize, jt_binedges);
  TH2D *h2_truthreco_r = new TH2D("truthreco_r", ";Reco r; Truth r", rbinsize, r_binedges, rbinsize, r_binedges);
  ////
  TH2D *h2_truthreco_jetpt = new TH2D("truthreco_jetpt", "", longptbinsize, longpt_binedges, longptbinsize, longpt_binedges);
  //////

  // 1D Num Efficiencies and Purities of Observables (226 - 235)
  TH1D *h1_num_purity_z = new TH1D("num_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_num_purity_jt = new TH1D("num_purity_jt", "", jtbinsize, jt_binedges);
  TH1D *h1_num_purity_r = new TH1D("num_purity_r", "", rbinsize, r_binedges);
  TH1D *h1_num_efficiency_z = new TH1D("num_efficiency_z", "", zbinsize, z_binedges);
  TH1D *h1_num_efficiency_jt = new TH1D("num_efficiency_jt", "", jtbinsize, jt_binedges);
  TH1D *h1_num_efficiency_r = new TH1D("num_efficiency_r", "", rbinsize, r_binedges);

  // 1D Denom Efficiencies and Purities of Observables (237 - 246)
  TH1D *h1_denom_purity_z = new TH1D("denom_purity_z", "", zbinsize, z_binedges);
  TH1D *h1_denom_purity_jt = new TH1D("denom_purity_jt", "", jtbinsize, jt_binedges);
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

  // TEfficiency *t1_efficiency_dR = new TEfficiency("t1_efficiency_dR", "", dRbinsize, dR_binedges);

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
  TH2D *h2_denom_purity_jtr = new TH2D("denom_purity_jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);

  TH2D *h2_num_efficiency_zjt = new TH2D("num_efficiency_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
  //    TH2D *h2_denom_efficiency_zjt = new TH2D("denom_efficiency_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);

  TH2D *h2_num_efficiency_zr = new TH2D("num_efficiency_zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
  //    TH2D *h2_denom_efficiency_zr = new TH2D("denom_efficiency_zr", "",  zbinsize, z_binedges, rbinsize, r_binedges);

  TH2D *h2_num_efficiency_jtr = new TH2D("num_efficiency_jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);
  //    TH2D *h2_denom_efficiency_jtr = new TH2D("denom_efficiency_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);

  // 2D and 4D Observables response Matrices (286 - 292)
  RooUnfoldResponse *response_zjt = new RooUnfoldResponse(h2_zjt, h2_zjt_truth, "response_zjt");
  RooUnfoldResponse *response_zr = new RooUnfoldResponse(h2_zr, h2_zr_truth, "respose_zr");
  RooUnfoldResponse *response_jtr = new RooUnfoldResponse(h2_jtr, h2_jtr_truth, "respose_jtr");
  RooUnfoldResponse *response_z = new RooUnfoldResponse(h1_denom_purity_z, h1_denom_efficiency_z, "response_z");
  RooUnfoldResponse *response_jt = new RooUnfoldResponse(h1_denom_purity_jt, h1_denom_efficiency_jt, "response_jt");
  RooUnfoldResponse *response_r = new RooUnfoldResponse(h1_denom_purity_r, h1_denom_efficiency_r, "response_r");

  ////////////////////// Here /////
  // 3D Efficiencies/Purities of 2D Observables vs jet_pt; 6D Response Matrices (324 - 357)
  /// Q: Is Ibrahim's "matched obsv." is my "truth obsv." ?

  TH3D *h3_ptzjt = new TH3D("ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_truthptzjt = new TH3D("truthptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptzjt = new TH3D("num_efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptzjt = new TH3D("efficiency_ptzjt", "efficiency;z; j_{T} [GeV/c];p_{T,jet} [GeV/c];", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptzjt = new TH3D("num_purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptzjt = new TH3D("denom_purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptzjt = new TH3D("purity_ptzjt", "purity;z; j_{T} [GeV/c];p_{T,jet} [GeV/c]", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptzjt = new RooUnfoldResponse(h3_ptzjt, h3_truthptzjt, "response_ptzjt");

  TH3D *h3_ptzjt_50_100 = new TH3D("ptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_truthptzjt_50_100 = new TH3D("truthptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptzjt_50_100 = new TH3D("num_efficiency_ptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptzjt_50_100 = new TH3D("efficiency_ptzjt_50_100", "efficiency;z; j_{T} [GeV/c];p_{T,jet} [GeV/c]", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptzjt_50_100 = new TH3D("num_purity_ptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptzjt_50_100 = new TH3D("denom_purity_ptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptzjt_50_100 = new TH3D("purity_ptzjt_50_100", "purity;z; j_{T} [GeV/c];p_{T,jet} [GeV/c]", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptzjt_50_100 = new RooUnfoldResponse(h3_ptzjt_50_100, h3_truthptzjt_50_100, "response_ptzjt_50_100");

  TH3D *h3_ptzr = new TH3D("ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_truthptzr = new TH3D("truthptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptzr = new TH3D("num_efficiency_ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptzr = new TH3D("efficiency_ptzr", "efficiency;z;r;p_{T,jet} [GeV/c]", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptzr = new TH3D("num_purity_ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptzr = new TH3D("denom_purity_ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptzr = new TH3D("purity_ptzr", "purity;z;r;p_{T,jet} [GeV/c]", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptzr = new RooUnfoldResponse(h3_ptzr, h3_truthptzr, "response_ptzr");

  TH3D *h3_ptzr_50_100 = new TH3D("ptzr_50_100", "", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_truthptzr_50_100 = new TH3D("truthptzr_50_100", "", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptzr_50_100 = new TH3D("num_efficiency_ptzr_50_100", "", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptzr_50_100 = new TH3D("efficiency_ptzr_50_100", "efficiency;z;r;p_{T,jet} [GeV/c]", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptzr_50_100 = new TH3D("num_purity_ptzr_50_100", "", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptzr_50_100 = new TH3D("denom_purity_ptzr_50_100", "", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptzr_50_100 = new TH3D("purity_ptzr_50_100", "purity;z;r;p_{T,jet} [GeV/c]", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptzr_50_100 = new RooUnfoldResponse(h3_ptzr_50_100, h3_truthptzr_50_100, "response_ptzr_50_100");

  TH3D *h3_ptjtr = new TH3D("ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_truthptjtr = new TH3D("truthptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptjtr = new TH3D("num_efficiency_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptjtr = new TH3D("efficiency_ptjtr", "efficiency;j_{T} [GeV/c];r;p_{T,jet} [GeV/c];", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptjtr = new TH3D("num_purity_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptjtr = new TH3D("denom_purity_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptjtr = new TH3D("purity_ptjtr", "purity;j_{T} [GeV/c];r;p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptjtr = new RooUnfoldResponse(h3_ptjtr, h3_truthptjtr, "response_ptjtr");

  TH3D *h3_ptjtr_50_100 = new TH3D("ptjtr_50_100", "", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_truthptjtr_50_100 = new TH3D("truthptjtr_50_100", "", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_num_efficiency_ptjtr_50_100 = new TH3D("num_efficiency_ptjtr_50_100", "", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_efficiency_ptjtr_50_100 = new TH3D("efficiency_ptjtr_50_100", "efficiency;j_{T} [GeV/c];r;p_{T,jet} [GeV/c]", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_num_purity_ptjtr_50_100 = new TH3D("num_purity_ptjtr_50_100", "", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_denom_purity_ptjtr_50_100 = new TH3D("denom_purity_ptjtr_50_100", "", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_purity_ptjtr_50_100 = new TH3D("purity_ptjtr_50_100", "purity;j_{T} [GeV/c];r;p_{T,jet} [GeV/c]", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptjtr_50_100 = new RooUnfoldResponse(h3_ptjtr_50_100, h3_truthptjtr_50_100, "response_ptjtr_50_100");

  // 2D Jet_pt vs Observable histograms, Purities/Efficiencies, Responses
  TH2D *h2_ptz = new TH2D("ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_truthptz = new TH2D("truthptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptz = new TH2D("num_efficiency_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptz = new TH2D("efficiency_ptz", "efficiency;z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptz = new TH2D("num_purity_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptz = new TH2D("denom_purity_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptz = new TH2D("purity_ptz", "purity;z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptz = new RooUnfoldResponse(h2_ptz, h2_truthptz, "response_ptz");

  TH2D *h2_ptz_50_100 = new TH2D("ptz_50_100", "", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_truthptz_50_100 = new TH2D("truthptz_50_100", "", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptz_50_100 = new TH2D("num_efficiency_ptz_50_100", "", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptz_50_100 = new TH2D("efficiency_ptz_50_100", "efficiency;z;p_{T,jet} [GeV/c]", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptz_50_100 = new TH2D("num_purity_ptz_50_100", "", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptz_50_100 = new TH2D("denom_purity_ptz_50_100", "", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptz_50_100 = new TH2D("purity_ptz_50_100", "purity;z;p_{T,jet} [GeV/c]", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptz_50_100 = new RooUnfoldResponse(h2_ptz_50_100, h2_truthptz_50_100, "response_ptz_50_100");

  TH2D *h2_ptjt = new TH2D("ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_truthptjt = new TH2D("truthptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptjt = new TH2D("num_efficiency_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptjt = new TH2D("efficiency_ptjt", "efficiency;j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptjt = new TH2D("num_purity_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptjt = new TH2D("denom_purity_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptjt = new TH2D("purity_ptjt", "purity;j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptjt = new RooUnfoldResponse(h2_ptjt, h2_truthptjt, "response_ptjt");

  TH2D *h2_ptjt_50_100 = new TH2D("ptjt_50_100", "", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_truthptjt_50_100 = new TH2D("truthptjt_50_100", "", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptjt_50_100 = new TH2D("num_efficiency_ptjt_50_100", "", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptjt_50_100 = new TH2D("efficiency_ptjt_50_100", "efficiency;j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptjt_50_100 = new TH2D("num_purity_ptjt_50_100", "", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptjt_50_100 = new TH2D("denom_purity_ptjt_50_100", "", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptjt_50_100 = new TH2D("purity_ptjt_50_100", "purity;j_{T} [GeV/c];p_{T,jet} [GeV/c]", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptjt_50_100 = new RooUnfoldResponse(h2_ptjt_50_100, h2_truthptjt_50_100, "response_ptjt_50_100");

  TH2D *h2_ptr = new TH2D("ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_truthptr = new TH2D("truthptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptr = new TH2D("num_efficiency_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptr = new TH2D("efficiency_ptr", "efficiency;r;p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptr = new TH2D("num_purity_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptr = new TH2D("denom_purity_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptr = new TH2D("purity_ptr", "purity;r;p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptr = new RooUnfoldResponse(h2_ptr, h2_truthptr, "response_ptr");

  TH2D *h2_ptr_50_100 = new TH2D("ptr_50_100", "", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_truthptr_50_100 = new TH2D("truthptr_50_100", "", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_num_efficiency_ptr_50_100 = new TH2D("num_efficiency_ptr_50_100", "", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_efficiency_ptr_50_100 = new TH2D("efficiency_ptr_50_100", "efficiency;r;p_{T,jet} [GeV/c]", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_num_purity_ptr_50_100 = new TH2D("num_purity_ptr_50_100", "", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_denom_purity_ptr_50_100 = new TH2D("denom_purity_ptr_50_100", "", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_purity_ptr_50_100 = new TH2D("purity_ptr_50_100", "purity;r;p_{T,jet} [GeV/c]", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);

  RooUnfoldResponse *response_ptr_50_100 = new RooUnfoldResponse(h2_ptr_50_100, h2_truthptr_50_100, "response_ptr_50_100");

  /////////// Analogous Not in Bjets SimpleUnfold.C ////////////
  TH2D *h2_SVTag_eff_num_z = new TH2D("h2_SVTag_eff_num_z", "", fragzbinsize, fragz_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_eff_denom_z = new TH2D("h2_SVTag_eff_denom_z", "", fragzbinsize, fragz_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_eff_z = new TH2D("h_SVTag_eff_z", "", fragzbinsize, fragz_binedges, customptbinsize, custompt_binedges);

  TH2D *h2_SVTag_pur_num_z = new TH2D("h2_SVTag_pur_num_z", "", fragzbinsize, fragz_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_pur_denom_z = new TH2D("h2_SVTag_pur_denom_z", "", fragzbinsize, fragz_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_pur_z = new TH2D("h_SVTag_pur_z", "", fragzbinsize, fragz_binedges, customptbinsize, custompt_binedges);

  TH2D *h2_SVTag_eff_num = new TH2D("h2_SVTag_eff_num", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_eff_denom = new TH2D("h2_SVTag_eff_denom", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_eff = new TH2D("h2_SVTag_eff", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);

  TH2D *h2_SVTag_pur_num = new TH2D("h2_SVTag_pur_num", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_pur_denom = new TH2D("h2_SVTag_pur_denom", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  TH2D *h2_SVTag_pur = new TH2D("h2_SVTag_pur", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
  ///////////--------------------------------------- ////////////

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

  /////////// Analogous Not in Bjets SimpleUnfold.C ////////////
  TH1D *h1_svipchi2_true = new TH1D("h1_svipchi2_true", "", 50, 0, 10);
  TH1D *h1_svipchi2_fake = new TH1D("h1_svipchi2_fake", "", 50, 0, 10);

  TH2D *h2_svipchi2_true = new TH2D("h2_svipchi2_true", "", 50, 0, 10, 50, 0, 10);
  TH2D *h2_svipchi2_fake = new TH2D("h2_svipchi2_fake", "", 50, 0, 10, 50, 0, 10);
  TH2D *h2_svipchi2 = new TH2D("h2_svipchi2", "", 50, 0, 10, 50, 0, 10);
  ///////////--------------------------------------- ////////////

  vector<RooUnfoldResponse *> vec_response_jetpt;
  vector<TH1D *> vec_num_efficiency_jetpt, vec_denom_efficiency_jetpt;
  vector<TH1D *> vec_num_purity_jetpt, vec_denom_purity_jetpt;
  vector<TH1D *> vec_efficiency_jetpt, vec_purity_jetpt;

  for (int i = 0; i < vecptHFbinsize; i++)
  {
    int loc = i;

    TH1D *h1_jetpt_tmp = new TH1D(Form("h1_jetpt%d", loc), "", ptbinsize, pt_binedges);
    TH1D *h1_num_efficiency_jetpt_tmp = new TH1D(Form("h1_num_efficiency_jetpt%d", loc), "", ptbinsize, pt_binedges);
    TH1D *h1_denom_efficiency_jetpt_tmp = (TH1D *)file_eff->Get(Form("denom_efficiency_jetpt%d", loc));
    TH1D *h1_num_purity_jetpt_tmp = new TH1D(Form("h1_num_purity_jetpt%d", loc), "", ptbinsize, pt_binedges);
    TH1D *h1_denom_purity_jetpt_tmp = new TH1D(Form("h1_denom_purity_jetpt%d", loc), "", ptbinsize, pt_binedges);
    TH1D *h1_efficiency_jetpt_tmp = new TH1D(Form("h1_efficiency_jetpt%d", loc), "", ptbinsize, pt_binedges);
    TH1D *h1_purity_jetpt_tmp = new TH1D(Form("h1_purity_jetpt%d", loc), "", ptbinsize, pt_binedges);

    RooUnfoldResponse *response_jetpt_temp = new RooUnfoldResponse(h1_jetpt_tmp, h1_jetpt_tmp, Form("response_jetpt%d", i));

    vec_response_jetpt.push_back(response_jetpt_temp);
    vec_num_efficiency_jetpt.push_back(h1_num_efficiency_jetpt_tmp);
    vec_denom_efficiency_jetpt.push_back(h1_denom_efficiency_jetpt_tmp);
    vec_num_purity_jetpt.push_back(h1_num_purity_jetpt_tmp);
    vec_denom_purity_jetpt.push_back(h1_denom_purity_jetpt_tmp);
    vec_efficiency_jetpt.push_back(h1_efficiency_jetpt_tmp);
    vec_purity_jetpt.push_back(h1_purity_jetpt_tmp);

    // }
  }

  //
  // Event loop
  //
  unsigned long long last_eventNum = 0;
  float last_jetpT = 0.;
  int event_counter = 0;

  cout << "Entries: " << DTree->GetEntries() << endl;

  vector<float> *zs(0), *tr_zs(0);
  vector<float> *sv_ipchi2(0);

  float jet_pt, HF_pt, jet_rap, tr_jet_pt, tr_jet_rap, tr_HF_pt, HF_m;
  float tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  float jet_px, jet_py, jet_pz, jet_e;
  float HF_px, HF_py, HF_pz, HF_e;

  bool isTrueDjet;
  int NumBHaD0_tr;
  int eventNumber, nSV;
  bool Hasccbar, TOS;
  float Jpsi_CHI2NDOF, Jpsi_CHI2, Jpsi_FDCHI2, Jpsi_IPCHI2, Jpsi_BPVDLS;
  float D0_CHI2NDOF, D0_CHI2, D0_IPCHI2;
  float sv_mass, sv_chi2, sv_ntrks, sv_cosine, bdt_mCor, SVIPCHI2;
  float SVIPCHI2_1, SVIPCHI2_2;
  int SVTag;
  float K_PIDK, chi2ndf_dtf, tau_dtf;
  float dtf_mass;
  bool L0Dec, Hlt1Dec, Hlt2Dec, L0TIS, FromDsst;
  double NearestMass;
  double ptweight(1.);

  double z, jt, r;
  double tr_z, tr_jt, tr_r;
  double zg, jtg, rg;

  DTree->SetBranchAddress("eventNumber", &eventNumber);

  DTree->SetBranchAddress("HF_px", &HF_px);
  DTree->SetBranchAddress("HF_py", &HF_py);
  DTree->SetBranchAddress("HF_pz", &HF_pz);
  DTree->SetBranchAddress("HF_e", &HF_e);
  DTree->SetBranchAddress("HF_pt", &HF_pt);
  DTree->SetBranchAddress("HF_m", &HF_m);

  DTree->SetBranchAddress("D0_IPCHI2", &D0_IPCHI2);
  DTree->SetBranchAddress("D0_CHI2", &D0_CHI2);
  DTree->SetBranchAddress("D0_CHI2NDOF", &D0_CHI2NDOF);

  DTree->SetBranchAddress("Jpsi_FDCHI2", &Jpsi_FDCHI2);
  DTree->SetBranchAddress("Jpsi_CHI2", &Jpsi_CHI2);
  DTree->SetBranchAddress("Jpsi_CHI2NDOF", &Jpsi_CHI2NDOF);
  DTree->SetBranchAddress("Jpsi_BPVDLS", &Jpsi_BPVDLS);

  DTree->SetBranchAddress("jet_pt", &jet_pt);
  DTree->SetBranchAddress("jet_rap", &jet_rap);
  DTree->SetBranchAddress("jet_px", &jet_px);
  DTree->SetBranchAddress("jet_py", &jet_py);
  DTree->SetBranchAddress("jet_pz", &jet_pz);
  DTree->SetBranchAddress("jet_e", &jet_e);

  DTree->SetBranchAddress("tr_jet_px", &tr_jet_px);
  DTree->SetBranchAddress("tr_jet_py", &tr_jet_py);
  DTree->SetBranchAddress("tr_jet_pz", &tr_jet_pz);
  DTree->SetBranchAddress("tr_jet_e", &tr_jet_e);
  DTree->SetBranchAddress("tr_jet_pt", &tr_jet_pt);
  DTree->SetBranchAddress("tr_HF_pt", &tr_HF_pt);
  DTree->SetBranchAddress("tr_jet_rap", &tr_jet_rap);

  DTree->SetBranchAddress("isTrueDjet", &isTrueDjet);

  DTree->SetBranchAddress("nSV", &nSV);
  DTree->SetBranchAddress("sv_mass", &sv_mass);
  DTree->SetBranchAddress("sv_chi2", &sv_chi2);
  DTree->SetBranchAddress("sv_cosine", &sv_cosine);
  DTree->SetBranchAddress("sv_ipchi2", &sv_ipchi2);
  DTree->SetBranchAddress("sv_ntrks", &sv_ntrks);
  DTree->SetBranchAddress("SVIPCHI2", &SVIPCHI2);
  DTree->SetBranchAddress("SVIPCHI2_1", &SVIPCHI2_1);
  DTree->SetBranchAddress("SVIPCHI2_2", &SVIPCHI2_2);
  DTree->SetBranchAddress("bdt_mCor", &bdt_mCor);

  DTree->SetBranchAddress("SVTag", &SVTag);

  DTree->SetBranchAddress("dtf_mass", &dtf_mass);

  DTree->SetBranchAddress("chi2ndf_dtf", &chi2ndf_dtf);
  DTree->SetBranchAddress("tau_dtf", &tau_dtf);
  DTree->SetBranchAddress("NumBHaD0_tr", &NumBHaD0_tr);
  DTree->SetBranchAddress("Hasccbar", &Hasccbar);

  DTree->SetBranchAddress("K_PIDK", &K_PIDK);
  DTree->SetBranchAddress("L0Dec", &L0Dec);
  DTree->SetBranchAddress("Hlt1Dec", &Hlt1Dec);
  DTree->SetBranchAddress("Hlt2Dec", &Hlt2Dec);
  DTree->SetBranchAddress("L0TIS", &L0TIS);
  DTree->SetBranchAddress("TOS", &TOS);

  DTree->SetBranchAddress("NearestMass", &NearestMass);
  DTree->SetBranchAddress("ptweight", &ptweight);

  DTree->Branch("z", &z);
  DTree->Branch("jt", &jt);
  DTree->Branch("r", &r);
  DTree->Branch("zg", &zg);
  DTree->Branch("jtg", &jtg);
  DTree->Branch("rg", &rg);
  DTree->Branch("tr_z", &tr_z);
  DTree->Branch("tr_jt", &tr_jt);
  DTree->Branch("tr_r", &tr_r);

  DTree->SetBranchAddress("FromDsst", &FromDsst);

  int eventNum;
  cout << "Requested # of events" << NumEvts << endl;

  // std::ofstream myfile, file_events;
  // std::ofstream SVTag_file;
  // myfile.open(Form("data/bjet_dataset_%d.csv", dataset));
  // SVTag_file.open(Form("data/svtag_bjet_dataset_%d.csv", dataset));
  // file_events.open(Form("csv/bjet_%d_events.txt", dataset));

  int NumD2KKPi = 0;
  int NumTrueD2KKPi = 0;

  for (int ev = 0; ev < NumEvts; ev++)
  {
    DTree->GetEntry(ev);

    if (ev % 100000 == 0)
      cout << "Executing event " << ev << endl;

    TLorentzVector HFmeson(HF_px, HF_py, HF_pz, HF_e);
    TLorentzVector HFjet(jet_px, jet_py, jet_pz, jet_e);
    TLorentzVector tr_HFjet(tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e);

    // ptweight = 1.0;
    // ptweight /= treeEvts;
    // if (treeNumber < 12)
    //   continue;

    if (ptweight == ptweights[1])
      ptweight = ptweights[1] * signal_eff[1];
    if (ptweight == ptweights[2])
      ptweight = ptweights[2] * signal_eff[2];
    if (ptweight == ptweights[3])
      ptweight = ptweights[3] * signal_eff[3];
    if (ptweight == ptweights[4])
      ptweight = ptweights[4] * signal_eff[4];
    if (ptweight == ptweights[5])
      ptweight = ptweights[5] * signal_eff[5];

    ptweight /= (ptweights[2] * signal_eff[2]);

    ptweight = 1.0;
    float reweight = 1.0;
    float emission_weight = 1.0;
    float eff_weight = 1.0;
    eff_weight *= ptweight;
    emission_weight *= ptweight;
    // if (DoUnfoldPrior)
    // {
    //   reweight = h3_HFptjetptrap_ratio->GetBinContent(h3_HFptjetptrap_ratio->GetXaxis()->FindBin(HFmeson.Pt()),
    //                                                   h3_HFptjetptrap_ratio->GetYaxis()->FindBin(HFjet.Pt()),
    //                                                   h3_HFptjetptrap_ratio->GetZaxis()->FindBin(HFjet.Rapidity()));
    //   // eff_weight = reweight;
    // }
    float MassMu = 1.864;
    float MassSigma = 0.04;
    float bkg_weight = h1_BkgScale != NULL ? h1_BkgScale->GetBinContent(h1_BkgScale->FindBin(HFmeson.Pt())) : 1.0;
    float MassHigh = h1_MassMax != NULL ? h1_MassMax->GetBinContent(h1_MassMax->FindBin(HFmeson.Pt())) : 1.985;
    float MassLow = h1_MassMin != NULL ? h1_MassMin->GetBinContent(h1_MassMin->FindBin(HFmeson.Pt())) : 1.688;

    // bool mass_cond = (HFmeson.M() > MassLow && HFmeson.M() < MassHigh);
    bool mass_cond = (dtf_mass > MassLow && dtf_mass < MassHigh);
    // bool mass_cond = true;
    // bool bkg_cond = (dtf_mass > Sideband1Min && dtf_mass < Sideband1Max) || (dtf_mass > Sideband2Min && dtf_mass < Sideband2Max);
    bool signal_cond = mass_cond;
    bool rap_cond = (jet_rap > etaMin && jet_rap < etaMax);
    bool pt_cond = (jet_pt > pTLow);
    bool tr_rap_cond = (tr_jet_rap > etaMin && tr_jet_rap < etaMax);
    bool tr_pt_cond = (tr_jet_pt > pTLow);
    bool SV_cond = (nSV > 0) && mass_cond && sv_mass > 0.4;
    bool gluon_cond = mass_cond && Hasccbar;
    // bool tr_WTA_cond = (tr_WTA_dist < WTA_max);
    // bool WTA_cond = (WTA_dist < WTA_max);

    float frag_z = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
    float frag_r = HFmeson.DeltaR(HFjet, true);

    if (DoRecSelEff)
    {
      // cout << D0_IPCHI2 << ", " << D0_CHI2 << ", " << Jpsi_CHI2 << ", " << Jpsi_CHI2NDOF << ", " << sqrt(Jpsi_FDCHI2) << endl;
      // if (D0_IPCHI2 > 22)
      //   continue;
      // if (D0_CHI2 > 42)
      //   continue;
      // if (Jpsi_CHI2 > 22)
      //   continue;
      // if (Jpsi_CHI2NDOF > 18)
      //   continue;
      // if (fabs(Jpsi_BPVDLS) < 2.8)
      //   continue;
    }

    if (!mass_cond)
      continue;
    // if (log10(D0_IPCHI2) > ipmax)
    //   continue;
    if (HFmeson.Pt() < 2)
      continue;
    // if (!L0TIS)
    //   continue;
    // if (!L0Dec || !Hlt1Dec || !Hlt2Dec)
    //   continue;

    // cout << WTA_dist << ", " << tr_WTA_dist << endl;

    // Not implement in MC since PIDCalib has no MC/Data tables
    // if (PID_cut && !PID_cond)
    //   continue;

    ///////////////////////////////////////////////////////////////////
    // Calculate SV-tag efficiency
    /////////////////////////////////////////////////////////////////////

    // if (SVIPCHI2 < 3)
    //   SVTag = 0;
    if (gluon_cond && isTrueDjet && tr_rap_cond && tr_pt_cond && rap_cond)
    {
      h2_SVTag_eff_denom->Fill(HFmeson.Pt(), tr_jet_pt);
      h2_SVTag_eff_denom_z->Fill(HFmeson.Pt() / tr_HFjet.Pt(), tr_HFjet.Pt());
    }
    if (SV_cond && rap_cond && isTrueDjet && tr_rap_cond && tr_pt_cond)
    {
      if (SVTag == 1)
      {
        h1_svipchi2_true->Fill((SVIPCHI2));
        h2_svipchi2_true->Fill(SVIPCHI2_1, SVIPCHI2_2);

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
        h1_svipchi2_fake->Fill((SVIPCHI2));
        h2_svipchi2_fake->Fill(SVIPCHI2_1, SVIPCHI2_2);

        h1_z_false->Fill(frag_z);
        h1_r_false->Fill(frag_r);
        h2_sv_mass_z_falsepos->Fill(sv_mass, frag_z);
        h2_bdt_z_falsepos->Fill(bdt_mCor, frag_z);
        h2_bdt_sv_mass_falsepos->Fill(bdt_mCor, sv_mass);
        h2_sv_mass_ntrks_falsepos->Fill(sv_mass, sv_ntrks);
      }
      if (SVTag == 1 || SVTag == 2)
      {
        h2_svipchi2->Fill(SVIPCHI2_1, SVIPCHI2_2);

        h2_SVTag_pur_denom_z->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt());
        h2_SVTag_pur_denom->Fill(HFmeson.Pt(), HFjet.Pt());

        h1_z_truefalse->Fill(frag_z);
      }
    }

    if (SubtractGS && Hasccbar)
      continue;

    // if (Hasccbar)
    //   continue;

    float HF_rap = HFmeson.Rapidity();

    ////////////////////////////////////////////////////////////////////
    // Two methods to compute efficiency:
    ///////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    // Method 1:
    // Fill denominator with all truth B jets in fiducial region in MCSimpleEff
    // Fill numerator with all reconstructed B jets in fiducial region in MCSimpleEff
    // Take the ratio as the efficiency
    // Problem: This efficiency is limited, cannot apply trigger in the MCTruth Tree
    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////
    // Method 2:
    // Fill denominator with all truth B jets in fiducial region in MCSimpleEff
    // Fill numerator with all reconstructed B jets in fiducial region in SimpleUnfold
    // Advantage: more freedom with variables (like trigger) in MCReco Tree
    /////////////////////////////////////////////////////////////////////
    // bool RemoveDsst = (NearestMass < 2.09 || NearestMass > 2.14);
    // bool RemoveDsst = true;
    bool num_cond_eff = tr_pt_cond && tr_rap_cond && isTrueDjet && pt_cond && rap_cond;
    bool num_cond_pur = tr_pt_cond && tr_rap_cond && isTrueDjet && pt_cond && rap_cond;
    bool denom_cond = pt_cond && rap_cond;

    // cout << pt_cond << ", " << rap_cond << ", " << tr_pt_cond << ", " << tr_rap_cond << ", " << isTrueDjet << endl;

    // if (WTA_cut)
    // {
    //   num_cond_eff = num_cond_eff && tr_WTA_cond && WTA_cond;
    //   num_cond_pur = num_cond_pur && tr_WTA_cond && WTA_cond;
    //   denom_cond = denom_cond && WTA_cond;
    // }

    // add rap_cond
    // calculate bin by bin corrections

    if (num_cond_eff)
    {

      h1_num_efficiency_jetpt->Fill(tr_jet_pt, eff_weight);
      h1_num_efficiency_HFpt->Fill(HFmeson.Pt(), eff_weight);

      h2_num_efficiency_ptz->Fill(tr_z, tr_HFjet.Pt(), eff_weight);
      h2_num_efficiency_ptjt->Fill(tr_jt, tr_HFjet.Pt(), eff_weight);
      h2_num_efficiency_ptr->Fill(tr_r, tr_HFjet.Pt(), eff_weight);

      h3_num_efficiency_ptzjt->Fill(tr_z, tr_jt, tr_HFjet.Pt(), eff_weight);
      h3_num_efficiency_ptzr->Fill(tr_z, tr_r, tr_HFjet.Pt(), eff_weight);
      h3_num_efficiency_ptjtr->Fill(tr_jt, tr_r, tr_HFjet.Pt(), eff_weight);

      h2_num_efficiency_ptz_50_100->Fill(tr_z, tr_HFjet.Pt(), eff_weight);
      h2_num_efficiency_ptjt_50_100->Fill(tr_jt, tr_HFjet.Pt(), eff_weight);
      h2_num_efficiency_ptr_50_100->Fill(tr_r, tr_HFjet.Pt(), eff_weight);

      h3_num_efficiency_ptzjt_50_100->Fill(tr_z, tr_jt, tr_HFjet.Pt(), eff_weight);
      h3_num_efficiency_ptzr_50_100->Fill(tr_z, tr_r, tr_HFjet.Pt(), eff_weight);
      h3_num_efficiency_ptjtr_50_100->Fill(tr_jt, tr_r, tr_HFjet.Pt(), eff_weight);

      for (int i = 0; i < vecptHFbinsize; i++)
      {
        if (HF_pt > vecptHF_binedges[i] && HF_pt < vecptHF_binedges[i + 1])
        {
          int loc = i;
          vec_num_efficiency_jetpt[loc]->Fill(tr_jet_pt);
          break;
        }
      }
    }

    if (denom_cond)
    {

      NumD2KKPi++;

      h1_denom_purity_jetpt->Fill(jet_pt, eff_weight);
      h1_denom_purity_HFpt->Fill(HF_pt, eff_weight);

      h2_denom_purity_ptz->Fill(z, jet_pt, eff_weight);
      h2_denom_purity_ptjt->Fill(jt, jet_pt, eff_weight);
      h2_denom_purity_ptr->Fill(r, jet_pt, eff_weight);

      h3_denom_purity_ptzjt->Fill(z, jt, jet_pt, eff_weight);
      h3_denom_purity_ptzr->Fill(z, r, jet_pt, eff_weight);
      h3_denom_purity_ptjtr->Fill(jt, r, jet_pt, eff_weight);

      h2_denom_purity_ptz_50_100->Fill(z, jet_pt, eff_weight);
      h2_denom_purity_ptjt_50_100->Fill(jt, jet_pt, eff_weight);
      h2_denom_purity_ptr_50_100->Fill(r, jet_pt, eff_weight);

      h3_denom_purity_ptzjt_50_100->Fill(z, jt, jet_pt, eff_weight);
      h3_denom_purity_ptzr_50_100->Fill(z, r, jet_pt, eff_weight);
      h3_denom_purity_ptjtr_50_100->Fill(jt, r, jet_pt, eff_weight);

      for (int i = 0; i < vecptHFbinsize; i++)
      {
        if (HF_pt > vecptHF_binedges[i] && HF_pt < vecptHF_binedges[i + 1])
        {
          int loc = i;
          vec_denom_purity_jetpt[loc]->Fill(jet_pt);
          break;
        }
      }
    }

    // adding tr_rap_cond makes this worse
    if (num_cond_pur)
    {
      h1_num_purity_jetpt->Fill(jet_pt, eff_weight);

      h2_num_purity_ptz->Fill(z, jet_pt, eff_weight);
      h2_num_purity_ptjt->Fill(jt, jet_pt, eff_weight);
      h2_num_purity_ptr->Fill(r, jet_pt, eff_weight);

      h3_num_purity_ptzjt->Fill(z, jt, jet_pt, eff_weight);
      h3_num_purity_ptzr->Fill(z, r, jet_pt, eff_weight);
      h3_num_purity_ptjtr->Fill(jt, r, jet_pt, eff_weight);

      h2_num_purity_ptz_50_100->Fill(z, jet_pt, eff_weight);
      h2_num_purity_ptjt_50_100->Fill(jt, jet_pt, eff_weight);
      h2_num_purity_ptr_50_100->Fill(r, jet_pt, eff_weight);

      h3_num_purity_ptzjt_50_100->Fill(z, jt, jet_pt, eff_weight);
      h3_num_purity_ptzr_50_100->Fill(z, r, jet_pt, eff_weight);
      h3_num_purity_ptjtr_50_100->Fill(jt, r, jet_pt, eff_weight);

      for (int i = 0; i < vecptHFbinsize; i++)
      {
        if (HF_pt > vecptHF_binedges[i] && HF_pt < vecptHF_binedges[i + 1])
        {
          int loc = i;
          vec_num_purity_jetpt[loc]->Fill(jet_pt);
          break;
        }
      }

      NumTrueD2KKPi++;
    }

    if (!pt_cond || !tr_pt_cond || !isTrueDjet)
      continue;

    response_jetpteta->Fill(jet_pt, jet_rap, tr_jet_pt, tr_jet_rap);

    if (!pt_cond || !tr_pt_cond || !isTrueDjet || !rap_cond || !tr_rap_cond)
      continue;

    // if (WTA_cut && !tr_WTA_cond)
    //   continue;
    // if (WTA_cut && !WTA_cond)
    //   continue;

    // cout << pt_cond << ", " << tr_pt_cond << endl;
    // cout << rap_cond << ", " << tr_rap_cond << endl;
    // cout << isTrueDjet << endl;

    response_jetpt->Fill(jet_pt, tr_jet_pt, reweight * ptweight);
    response_jeteta->Fill(jet_rap, tr_jet_rap, reweight * ptweight);
    response_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, HFmeson.Pt(), tr_jet_pt, reweight * ptweight);

    response_ptz->Fill(z, jet_pt, tr_z, tr_jet_pt, reweight * ptweight);
    response_ptjt->Fill(jt, jet_pt, tr_jt, tr_jet_pt, reweight * ptweight);
    response_ptr->Fill(r, jet_pt, tr_r, tr_jet_pt, reweight * ptweight);

    response_ptzjt->Fill(z, jt, jet_pt, tr_z, tr_jt, tr_jet_pt, reweight * ptweight);
    response_ptzr->Fill(z, r, jet_pt, tr_z, tr_r, tr_jet_pt, reweight * ptweight);
    response_ptjtr->Fill(jt, r, jet_pt, tr_jt, tr_r, tr_jet_pt, reweight * ptweight);

    response_ptz_50_100->Fill(z, jet_pt, tr_z, tr_jet_pt, reweight * ptweight);
    response_ptjt_50_100->Fill(jt, jet_pt, tr_jt, tr_jet_pt, reweight * ptweight);
    response_ptr_50_100->Fill(r, jet_pt, tr_r, tr_jet_pt, reweight * ptweight);

    response_ptzjt_50_100->Fill(z, jt, jet_pt, tr_z, tr_jt, tr_jet_pt, reweight * ptweight);
    response_ptzr_50_100->Fill(z, r, jet_pt, tr_z, tr_r, tr_jet_pt, reweight * ptweight);
    response_ptjtr_50_100->Fill(jt, r, jet_pt, tr_jt, tr_r, tr_jet_pt, reweight * ptweight);

    // if(jet_pt > ptMax) continue;
    h2_truthreco_jetpt->Fill(jet_pt, tr_jet_pt, reweight * ptweight);
    h2_truthreco_z->Fill(z, tr_z, reweight * ptweight);
    h2_truthreco_jt->Fill(jt, tr_jt, reweight * ptweight);
    h2_truthreco_r->Fill(r, tr_r, reweight * ptweight);

    // For a cross check on the unfold prior systematic
    h2_ptz_weighted->Fill(z, jet_pt, reweight * ptweight);
    h2_ptjt_weighted->Fill(jt, jet_pt, reweight * ptweight);
    h2_ptr_weighted->Fill(r, jet_pt, reweight * ptweight);
    h1_z_weighted->Fill(z, reweight * ptweight);
    h1_jt_weighted->Fill(jt, reweight * ptweight);
    h1_r_weighted->Fill(r, reweight * ptweight);

    h2_ptz->Fill(z, jet_pt);
    h2_ptjt->Fill(jt, jet_pt);
    h2_ptr->Fill(r, jet_pt);
    h1_z->Fill(z);
    h1_jt->Fill(jt);
    h1_r->Fill(r);

    for (int i = 0; i < vecptHFbinsize; i++)
    {
      if (HF_pt > vecptHF_binedges[i] && HF_pt < vecptHF_binedges[i + 1])
      {
        int loc = i;
        vec_response_jetpt[loc]->Fill(jet_pt, tr_jet_pt, reweight * ptweight);
        break;
      }
    }

    event_counter++;
  }

  h2_SVTag_eff_z->Divide(h2_SVTag_eff_num_z, h2_SVTag_eff_denom_z, 1, 1, "B");
  h2_SVTag_eff->Divide(h2_SVTag_eff_num, h2_SVTag_eff_denom, 1, 1, "B");

  h2_SVTag_pur_z->Divide(h2_SVTag_pur_num_z, h2_SVTag_pur_denom_z, 1, 1, "B");
  h2_SVTag_pur->Divide(h2_SVTag_pur_num, h2_SVTag_pur_denom, 1, 1, "B");

  // RooUnfoldResponse * response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, h2_truthreco_jetpt, "response_jetpt");
  TH2 *h2_response_jetpt = response_jetpt->Hresponse();

  TH2 *h2_response_ptz = response_ptz->Hresponse();
  TH2 *h2_response_ptjt = response_ptjt->Hresponse();
  TH2 *h2_response_ptr = response_ptr->Hresponse();

  TH2 *h2_response_ptzjt = response_ptzjt->Hresponse();
  TH2 *h2_response_ptzr = response_ptzr->Hresponse();
  TH2 *h2_response_ptjtr = response_ptjtr->Hresponse();

  h2_response_jetpt->Write("response_jetpt");

  h2_response_ptz->Write("response_ptz");
  h2_response_ptjt->Write("response_ptjt");
  h2_response_ptr->Write("response_ptr");

  h2_response_ptzjt->Write("response_ptzjt");
  h2_response_ptzr->Write("response_ptzr");
  h2_response_ptjtr->Write("response_ptjtr");

  response_jetpt->Write("Roo_response_jetpt");

  response_ptz->Write("Roo_response_ptz");
  response_ptjt->Write("Roo_response_ptjt");
  response_ptr->Write("Roo_response_ptr");

  response_ptzjt->Write("Roo_response_ptzjt");
  response_ptzr->Write("Roo_response_ptzr");
  response_ptjtr->Write("Roo_response_ptjtr");

  response_ptz_50_100->Write("Roo_response_ptz_50_100");
  response_ptjt_50_100->Write("Roo_response_ptjt_50_100");
  response_ptr_50_100->Write("Roo_response_ptr_50_100");

  response_ptzjt_50_100->Write("Roo_response_ptzjt_50_100");
  response_ptzr_50_100->Write("Roo_response_ptzr_50_100");
  response_ptjtr_50_100->Write("Roo_response_ptjtr_50_100");

  TH1D *h1_purity_jetpt = (TH1D *)h1_num_purity_jetpt->Clone("h1_purity_jetpt");
  h1_purity_jetpt->Divide(h1_num_purity_jetpt, h1_denom_purity_jetpt, 1, 1, "B");

  TH1D *h1_efficiency_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("h1_efficiency_jetpt");
  h1_efficiency_jetpt->Divide(h1_num_efficiency_jetpt, h1_denom_efficiency_jetpt, 1, 1, "B");

  TH1D *h1_efficiency_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("h1_efficiency_HFpt");
  h1_efficiency_HFpt->Divide(h1_num_efficiency_HFpt, h1_denom_efficiency_HFpt, 1, 1, "B");

  h2_efficiency_ptz->Divide(h2_num_efficiency_ptz, h2_denom_efficiency_ptz, 1, 1, "B");
  h2_efficiency_ptjt->Divide(h2_num_efficiency_ptjt, h2_denom_efficiency_ptjt, 1, 1, "B");
  h2_efficiency_ptr->Divide(h2_num_efficiency_ptr, h2_denom_efficiency_ptr, 1, 1, "B");

  h2_purity_ptz->Divide(h2_num_purity_ptz, h2_denom_purity_ptz, 1, 1, "B");
  h2_purity_ptjt->Divide(h2_num_purity_ptjt, h2_denom_purity_ptjt, 1, 1, "B");
  h2_purity_ptr->Divide(h2_num_purity_ptr, h2_denom_purity_ptr, 1, 1, "B");

  h3_efficiency_ptzjt->Divide(h3_num_efficiency_ptzjt, h3_denom_efficiency_ptzjt, 1, 1, "B");
  h3_efficiency_ptzr->Divide(h3_num_efficiency_ptzr, h3_denom_efficiency_ptzr, 1, 1, "B");
  h3_efficiency_ptjtr->Divide(h3_num_efficiency_ptjtr, h3_denom_efficiency_ptjtr, 1, 1, "B");

  h3_purity_ptzjt->Divide(h3_num_purity_ptzjt, h3_denom_purity_ptzjt, 1, 1, "B");
  h3_purity_ptzr->Divide(h3_num_purity_ptzr, h3_denom_purity_ptzr, 1, 1, "B");
  h3_purity_ptjtr->Divide(h3_num_purity_ptjtr, h3_denom_purity_ptjtr, 1, 1, "B");

  h2_efficiency_ptz_50_100->Divide(h2_num_efficiency_ptz_50_100, h2_denom_efficiency_ptz_50_100, 1, 1, "B");
  h2_efficiency_ptjt_50_100->Divide(h2_num_efficiency_ptjt_50_100, h2_denom_efficiency_ptjt_50_100, 1, 1, "B");
  h2_efficiency_ptr_50_100->Divide(h2_num_efficiency_ptr_50_100, h2_denom_efficiency_ptr_50_100, 1, 1, "B");

  h2_purity_ptz_50_100->Divide(h2_num_purity_ptz_50_100, h2_denom_purity_ptz_50_100, 1, 1, "B");
  h2_purity_ptjt_50_100->Divide(h2_num_purity_ptjt_50_100, h2_denom_purity_ptjt_50_100, 1, 1, "B");
  h2_purity_ptr_50_100->Divide(h2_num_purity_ptr_50_100, h2_denom_purity_ptr_50_100, 1, 1, "B");

  h3_efficiency_ptzjt_50_100->Divide(h3_num_efficiency_ptzjt_50_100, h3_denom_efficiency_ptzjt_50_100, 1, 1, "B");
  h3_efficiency_ptzr_50_100->Divide(h3_num_efficiency_ptzr_50_100, h3_denom_efficiency_ptzr_50_100, 1, 1, "B");
  h3_efficiency_ptjtr_50_100->Divide(h3_num_efficiency_ptjtr_50_100, h3_denom_efficiency_ptjtr_50_100, 1, 1, "B");

  h3_purity_ptzjt_50_100->Divide(h3_num_purity_ptzjt_50_100, h3_denom_purity_ptzjt_50_100, 1, 1, "B");
  h3_purity_ptzr_50_100->Divide(h3_num_purity_ptzr_50_100, h3_denom_purity_ptzr_50_100, 1, 1, "B");
  h3_purity_ptjtr_50_100->Divide(h3_num_purity_ptjtr_50_100, h3_denom_purity_ptjtr_50_100, 1, 1, "B");

  h1_efficiency_jetpt->Write("efficiency_jetpt");

  h1_purity_jetpt->Write("purity_jetpt");

  h2_efficiency_ptz->Write("efficiency_ptz");
  h2_efficiency_ptjt->Write("efficiency_ptjt");
  h2_efficiency_ptr->Write("efficiency_ptr");

  h2_purity_ptz->Write("purity_ptz");
  h2_purity_ptjt->Write("purity_ptjt");
  h2_purity_ptr->Write("purity_ptr");

  h3_efficiency_ptzjt->Write("efficiency_ptzjt");
  h3_efficiency_ptzr->Write("efficiency_ptzr");
  h3_efficiency_ptjtr->Write("efficiency_ptjtr");

  h3_purity_ptzjt->Write("purity_ptzjt");
  h3_purity_ptzr->Write("purity_ptzr");
  h3_purity_ptjtr->Write("purity_ptjtr");

  h2_efficiency_ptz_50_100->Write("efficiency_ptz_50_100");
  h2_efficiency_ptjt_50_100->Write("efficiency_ptjt_50_100");
  h2_efficiency_ptr_50_100->Write("efficiency_ptr_50_100");

  h2_purity_ptz_50_100->Write("purity_ptz_50_100");
  h2_purity_ptjt_50_100->Write("purity_ptjt_50_100");
  h2_purity_ptr_50_100->Write("purity_ptr_50_100");

  h3_efficiency_ptzjt_50_100->Write("efficiency_ptzjt_50_100");
  h3_efficiency_ptzr_50_100->Write("efficiency_ptzr_50_100");
  h3_efficiency_ptjtr_50_100->Write("efficiency_ptjtr_50_100");

  h3_purity_ptzjt_50_100->Write("purity_ptzjt_50_100");
  h3_purity_ptzr_50_100->Write("purity_ptzr_50_100");
  h3_purity_ptjtr_50_100->Write("purity_ptjtr_50_100");

  for (int i = 0; i < vecptHFbinsize; i++)
  {
    int loc = i;

    vec_efficiency_jetpt[loc]->Divide(vec_num_efficiency_jetpt[loc], vec_denom_efficiency_jetpt[loc], 1, 1, "B");
    vec_purity_jetpt[loc]->Divide(vec_num_purity_jetpt[loc], vec_denom_purity_jetpt[loc], 1, 1, "B");
    vec_efficiency_jetpt[loc]->Write(Form("efficiency_jetpt%d", loc));
    vec_purity_jetpt[loc]->Write(Form("purity_jetpt%d", loc));
    vec_response_jetpt[loc]->Write(Form("response_jetpt%d", loc));
  }

  h2_SVTag_eff->Write("h2_SVTag_eff");
  h2_SVTag_eff_z->Write("h2_SVTag_eff_z");

  h2_SVTag_pur->Write("h2_SVTag_pur");
  h2_SVTag_pur_z->Write("h2_SVTag_pur_z");

  NormalizeHist(h2_ptz_weighted);
  NormalizeHist(h2_ptjt_weighted);
  NormalizeHist(h2_ptr_weighted);

  NormalizeHist(h1_z_weighted);
  NormalizeHist(h1_jt_weighted);
  NormalizeHist(h1_r_weighted);

  NormalizeHist(h2_ptz);
  NormalizeHist(h2_ptjt);
  NormalizeHist(h2_ptr);

  NormalizeHist(h1_z);
  NormalizeHist(h1_jt);
  NormalizeHist(h1_r);

  h2_ptz_weighted->Write();
  h2_ptjt_weighted->Write();
  h2_ptr_weighted->Write();
  h1_z_weighted->Write();
  h1_jt_weighted->Write();
  h1_r_weighted->Write();

  h2_ptz->Write();
  h2_ptjt->Write();
  h2_ptr->Write();
  h1_z->Write();
  h1_jt->Write();
  h1_r->Write();

  /////////////////////////////////

  cout << event_counter << " events processed" << endl;

  /////////////////////////////////////////////////////
  TH1D *h1_jetpt_true = (TH1D *)h1_denom_efficiency_jetpt->Clone("h1_jetpt_true");
  TH1D *h1_jetpt_reco = (TH1D *)h1_denom_purity_jetpt->Clone("h1_jetpt_reco");
  h1_jetpt_reco->Multiply(h1_purity_jetpt);
  RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_reco, 4);
  h1_jetpt_reco = (TH1D *)unfold_jetpt.Hreco();
  h1_jetpt_reco->Divide(h1_efficiency_jetpt);

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
  TString plotextension = TString("../../plots/DjetsMC/");
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

  // ccan[ican]->cd(4);
  // NormalizeHist(h1_jetpt);
  // h1_jetpt->Draw("same");

  // NormalizeHist(h1_jetpt_truth);
  // h1_jetpt_truth->SetLineColor(kGreen);
  // h1_jetpt_truth->Draw("same");

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
  h2_truthreco_r->Draw("COLZ");

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
  h1_purity_jetpt->Draw("P E same");
  h1_purity_jetpt->SetTitle("; Jet pT; HF Jet Purity");
  h1_purity_jetpt->SetMinimum(0.);
  h1_purity_jetpt->SetMaximum(1.05);

  ccan[ican]->cd(2);
  h1_efficiency_jetpt->SetMarkerColor(kBlue);
  h1_efficiency_jetpt->SetMarkerStyle(22);
  h1_efficiency_jetpt->Draw("P E same");
  h1_efficiency_jetpt->SetTitle("; Jet pT; HF Jet Efficiency");
  h1_efficiency_jetpt->SetMinimum(0.);
  // h1_efficiency_jetpt->SetMaximum(1.);
  h1_efficiency_jetpt->SetMaximum(0.1);

  if (h1_HFeff_jetpt != NULL)
  {
    SetTruthStyle(h1_HFeff_jetpt);
    h1_HFeff_jetpt->Draw("PE SAME");
  }

  ccan[ican]->cd(3);
  h1_efficiency_HFpt->SetMarkerColor(kRed);
  h1_efficiency_HFpt->SetMarkerStyle(21);
  h1_efficiency_HFpt->Draw("PE same");
  h1_efficiency_HFpt->SetTitle("; HF pT; HF Jet Efficiency");
  h1_efficiency_HFpt->SetMinimum(0.);
  // h1_efficiency_HFpt->SetMaximum(1.);
  h1_efficiency_HFpt->SetMaximum(0.1);
  gPad->Update();

  ccan[ican]->cd(4);
  SetRecoStyle(h1_jetpt_reco);
  SetTruthStyle(h1_jetpt_true);
  h1_jetpt_reco->Draw("SAME");
  h1_jetpt_true->Draw("SAME");

  // h3_efficiency_HFptjetptrap->GetYaxis()->SetRange(1, 1);
  // h3_purity_HFptjetptrap->GetYaxis()->SetRange(2, 2);
  // TH2D *h2_temp = (TH2D *)(h3_efficiency_HFptjetptrap->Project3D("zx_eff"));
  // TH2D *h2_temp_pur = (TH2D *)(h3_purity_HFptjetptrap->Project3D("zx_pur"));
  // for (int i = 0; i < customptbinsize; i++)
  // {

  //   TH1D *h1_temp = (TH1D *)(h2_temp->ProjectionX(Form("htemp%d_HFptjetptrap", i), i + 1, i + 1));
  //   TH1D *h1_temp_pur = (TH1D *)(h2_temp_pur->ProjectionX(Form("htemp_pur%d_HFptjetptrap", i), i + 1, i + 1));

  //   h1_temp_pur->SetMarkerStyle(i + 23);
  //   h1_temp_pur->SetMarkerColor(i + 4);
  //   h1_temp_pur->SetLineColor(i + 4);
  //   h1_temp_pur->Draw("P E SAME");
  //   h1_temp_pur->SetMinimum(0.);
  //   h1_temp_pur->SetMaximum(1.05);

  //   h1_temp->SetMarkerStyle(i + 20);
  //   h1_temp->SetMarkerColor(i + 1);
  //   h1_temp->SetLineColor(i + 1);
  //   h1_temp->Draw("P E SAME");
  // }

  // auto grapheta4 = h1_purity_rap->GetPaintedGraph();
  // grapheta4->SetMinimum(0);
  // grapheta4->SetMaximum(1);
  // gPad->Update();

  // for (int i = 0; i < customptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_SVTag_eff->ProjectionX(Form("htemp_sveff%d", i), i + 1, i + 1);
  //   TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur->ProjectionX(Form("htemp_pur_sveff%d", i), i + 1, i + 1);

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
  //   // h1_temp_pur->SetMinimum(0.);
  //   // h1_temp_pur->SetMaximum(1.05);
  // }

  // h1_purity_HFpt->SetMarkerColor(kRed);
  // h1_purity_HFpt->SetMarkerStyle(21);
  // h1_purity_HFpt->Draw("P E same");
  // h1_purity_HFpt->SetTitle("; HF pT; Purity or Efficiency");
  // h1_purity_HFpt->SetMinimum(0.);
  // h1_purity_HFpt->SetMaximum(1.05);

  // h1_efficiency_HFpt->SetMarkerColor(kBlue);
  // h1_efficiency_HFpt->SetMarkerStyle(22);
  // h1_efficiency_HFpt->Draw("P E same");

  // h1_efficiency_HFpt->SetTitle("; HF pT; Purity");

  // f_pur1->Draw("SAME");
  // f_eff1->Draw("SAME");

  // for (int i = 0; i < customptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_SVTag_eff_z->ProjectionX(Form("htemp%d_z", i), i + 1, i + 1);
  //   TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur_z->ProjectionX(Form("htemppur%d_z", i), i + 1, i + 1);

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

  // ccan[ican]->cd(4);

  // h1_efficiency_HFpt->SetMarkerColor(kRed);
  // h1_efficiency_HFpt->SetMarkerStyle(22);
  // h1_efficiency_HFpt->Draw("P E same");

  // if (h1_HFeff_HFpt != NULL)
  // {
  //   SetTruthStyle(h1_HFeff_HFpt);
  //   h1_HFeff_HFpt->Draw("PE SAME");
  // }
  // ccan[ican]->cd(4);

  // auto legendeffpur = new TLegend(0.35, 0.45, 0.65, 0.75);
  // legendeffpur->SetTextSize(0.03);
  // legendeffpur->SetBorderSize(0);
  // legendeffpur->SetFillStyle(0);
  // legendeffpur->SetFillColor(3);

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

  // //
  // ++ican;
  // sprintf(buf, "ccan%d", ican);
  // ccan[ican] = new TCanvas(buf, buf, 1);
  // ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  // gPad->SetRightMargin(0.15);
  // ccan[ican]->cd();
  // ccan[ican]->Divide(2, 3);

  // ccan[ican]->cd(1);
  // for (int i = 0; i < customptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_SVTag_eff->ProjectionX(Form("htemp%d_svtag", i), i + 1, i + 1);
  //   TH1D *h1_temp_pur = (TH1D *)h2_SVTag_pur->ProjectionX(Form("htemppur%d_svtag", i), i + 1, i + 1);

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

  // ccan[ican]->cd(2);
  // SetRecoStyle(h1_svipchi2_true);
  // SetTruthStyle(h1_svipchi2_fake);
  // h1_svipchi2_true->Draw("PESAME");
  // h1_svipchi2_fake->Draw("PESAME");

  // ccan[ican]->cd(3);
  // h2_svipchi2->Draw("COLZ");
  // ccan[ican]->cd(4);
  // h2_svipchi2_true->Draw("COLZ");
  // ccan[ican]->cd(5);
  // h2_svipchi2_fake->Draw("COLZ");

  // if (ican == 0)
  // {
  //   ccan[ican]->Print(plotfileO.Data());
  // }
  // else
  // {
  //   ccan[ican]->Print(plotfilePDF.Data());
  // }

  //
  //

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
  cout << "Num of Reco B jets = " << NumD2KKPi << endl;
  cout << "Num of True B jets = " << NumTrueD2KKPi << endl;

  // CAJetAlgo(std::string filename);

  // loop(ptMax, Nsubsets);
  // write(ptMax, Nsubsets);
}
//
int main(int argc, char *argv[])
{

  int NumEvts = -1;
  int dataset = 90499;
  double minimum_dR = 0.1;
  int DoReverse = false;
  bool isData = true;
  bool chargedJetCut = false;
  bool WTA_cut = true;
  bool DoJER = false;
  int DoJES = 0;
  bool DoFSPPT = false;
  bool DoGhostCut = false;
  bool DoFSPEff = false;
  bool DoTrigEff = false;
  int DoPIDEff = 0;
  bool DoRecSelEff = false;
  bool DoSignalSys = false;
  bool SubtractGS = false;
  bool DoUnfoldPrior = false;
  bool DoJetID = false;
  int PromptCut = 0;

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
      std::cout << "  -jer <DoJER>       : Whether to apply JER (0 or 1)" << std::endl;
      std::cout << "  -jes <DoJES>       : JES variation (integer)" << std::endl;
      std::cout << "  -fsppt <DoFSPPT>     : Whether to apply track pT cut (0 or 1)" << std::endl;
      std::cout << "  -ghost <DoGhostCut>       : Whether to apply ghost cut (0 or 1)" << std::endl;
      std::cout << "  -fspeff <DoFSPEff>       : Whether to apply full simulation efficiency (0 or 1)" << std::endl;
      std::cout << "  -trig <DoTrigEff>        : Whether to apply trigger efficiency (0 or 1)" << std::endl;
      std::cout << "  -pideff <DoPIDEff>       : PID efficiency variation (integer)" << std::endl;
      std::cout << "  -recsel <DoRecSelEff>    : Whether to apply reconstruction selection efficiency (0 or 1)" << std::endl;
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
    else if (arg == "-mindR")
    {
      if (i + 1 < argc)
      {
        minimum_dR = stod(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-mindR option requires one argument." << std::endl;
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
    else if (arg == "-reverse")
    {
      if (i + 1 < argc)
      {
        DoReverse = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-reverse option requires one argument." << std::endl;
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
    else if (arg == "-jetid")
    {
      if (i + 1 < argc)
      {
        DoJetID = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-jetid option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-fsppt")
    {
      if (i + 1 < argc)
      {
        DoFSPPT = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-fsppt option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-priorsys")
    {
      if (i + 1 < argc)
      {
        DoUnfoldPrior = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-priorsys option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-prompt")
    {
      if (i + 1 < argc)
      {
        PromptCut = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-prompt option requires one argument." << std::endl;
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
    else if (arg == "-dosignal")
    {
      if (i + 1 < argc)
      {
        DoSignalSys = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-dosignal option requires one argument." << std::endl;
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
    else if (arg == "-wta")
    {
      if (i + 1 < argc)
      {
        WTA_cut = (stoi(argv[i + 1]) != 0);
        i++;
      }
      else
      {
        std::cerr << "-wta option requires one argument." << std::endl;
        return 1;
      }
    }
    else
    {
      std::cerr << "Unknown option: " << arg << std::endl;
      return 1;
    }
  }

  SimpleUnfold(NumEvts,
               dataset,
               chargedJetCut,
               WTA_cut,
               minimum_dR,
               DoReverse,
               DoJES,
               DoJER,
               DoFSPEff,
               DoFSPPT,
               DoGhostCut,
               DoRecSelEff,
               DoSignalSys,
               DoUnfoldPrior,
               DoJetID,
               SubtractGS,
               PromptCut);
  return 0;
}
