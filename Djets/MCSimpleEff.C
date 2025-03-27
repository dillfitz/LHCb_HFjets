

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"

using namespace std;

void MCSimpleEff(int NumEvts = 10000, int dataset = 1510,
                 bool chargedJetCut_user = false,
                 bool WTA_cut = true,
                 double minimum_dR = 0.1,
                 bool SubtractGS = false,
                 int PromptCut = 0)
{

  bool MCflag = true;
  followHardest = false;
  truthLevel = true;
  chargedJetCut = chargedJetCut_user;
  if (truthLevel)
  {
    ghostCut = false;
  }

  int year = (dataset / 10000) % 10;
  int ptrange = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int prompt_int = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;

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

    followHardest = true;
  }

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
  str_prompt = (PromptCut == 1) ? "_prompt" : (PromptCut == 2) ? "_nonprompt"
                                                               : "";
  TString str_tree;

  TString extension_read, extension_RootFilesMC, extension;

  extension = TString("efficiency_") + str_level + str_Nevts + str_pt + str_eta + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_GS + str_WTA + str_prompt + Form("_%d", dataset);

  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;

  // TString dir_deadcone("$LUND/D2KKPi/");

  extension_RootFilesMC = TString("../../root_files/DjetsMC/");

  extension_read = TString("tree_") + str_level + str_Nevts + str_eta + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);

  // TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
  TChain *DTree = new TChain("DTree", "");
  vector<int> vec_datasets;
  int Mags[2] = {0, 1};
  int years[3] = {6, 7, 8};
  int prompts[2] = {0, 1};
  int ptranges[6] = {1, 2, 3, 4, 5, 6};

  // vec_datasets = {62400, 62401, 72400, 72401, 82400, 82401, 63400, 63401, 73400, 73401, 83400, 83401, 67400, 67401, 77400, 77401, 87400, 87401};

  // for (int j = 0; j < 2; j++)
  // {
  //   if (prompt_int == 0 && prompts[j] != 0)
  //     continue;
  //   if (prompt_int == 1 && prompts[j] != 1)
  //     continue;
  //   for (int k = 0; k < 6; k++)
  //   {
  //     if (ptranges[k] == 1 || ptranges[k] == 5)
  //       continue;

  //     if (ptrange != 9)
  //     {
  //       if (ptranges[k] != ptrange)
  //         continue;
  //     }
  //     // if (ptrange == 1 && ptranges[k] != 1)
  //     //   continue;
  //     // if (ptrange == 2 && ptranges[k] != 2)
  //     //   continue;
  //     // if (ptrange == 3 && ptranges[k] != 3)
  //     //   continue;
  //     // if (ptrange == 4 && ptranges[k] != 4)
  //     //   continue;
  //     // if (ptrange == 5 && ptranges[k] != 5)
  //     //   continue;
  //     // if (ptrange == 6 && ptranges[k] != 6)
  //     //   continue;
  //     for (int l = 0; l < 3; l++)
  //     {
  //       if (year == 6 && years[l] != 6)
  //         continue;
  //       if (year == 7 && years[l] != 7)
  //         continue;
  //       if (year == 8 && years[l] != 8)
  //         continue;
  //       for (int i = 0; i < 2; i++)
  //       {
  //         if (Mag == 0 && Mags[i] != 0)
  //           continue;
  //         if (Mag == 1 && Mags[i] != 1)
  //           continue;
  //         int num = 10000 * years[l] + 1000 * ptranges[k] + 400 + 10 * prompts[j] + Mags[i];
  //         cout << num << endl;
  //         cout << years[l] << ", " << ptranges[k] << ", " << prompts[j] << ", " << Mags[i] << endl;
  //         vec_datasets.push_back(num);
  //       }
  //     }
  //   }
  // }
  // if (Mag == 0)
  //   vec_datasets = {60490, 70490, 80490};
  // else if (Mag == 1)
  //   vec_datasets = {60491, 70491, 80491};
  // else
  //   vec_datasets = {60490, 60491, 70490, 70491, 80490, 80491};

  // vec_datasets = {62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};
  vec_datasets = {61400, 61401, 62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};
  if (dataset == 99499)
    vec_datasets = {99499};
  if (year == 9)
  {
    for (int i = 0; i < vec_datasets.size(); i++)
    {
      Mag = (vec_datasets[i] / 1) % 10;
      if (Mag == 0)
        str_Mag = "_MD";
      else if (Mag == 1)
        str_Mag = "_MU";
      extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", vec_datasets[i]);
      // extension_read = extension_prefix + extension_read;
      cout << extension_read << endl;
      DTree->Add(extension_RootFilesMC  + extension_read + ".root/DTree");
    }
  }
  else
  {
    extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);
    // extension_read = extension_prefix + extension_read;
    cout << extension_read << endl;
    DTree->Add(extension_RootFilesMC  + extension_read + ".root/DTree");
  }
  if (NumEvts > DTree->GetEntries())
    NumEvts = DTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = DTree->GetEntries();
  cout << DTree->GetEntries() << endl;

  TFile f(extension_RootFilesMC + extension + ".root", "RECREATE");


    /// Integrated Observables
    
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

    // 1D jet_pt-Binned observables
    
    TH1D *h1_z_truth_b = new TH1D("z_truth_c", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_g = new TH1D("z_truth_g", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_12515 = new TH1D("z_truth_12515", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_1520 = new TH1D("z_truth_1520", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_2030 = new TH1D("z_truth_2030", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_3050 = new TH1D("z_truth_3050", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_50100 = new TH1D("z_truth_50100", "", zbinsize, z_binedges);
    TH1D *h1_z_truth_100150 = new TH1D("z_truth_100150", "", zbinsize, z_binedges);
    TH1D *h1_jt_truth_12515 = new TH1D("jt_truth_12515", "", jtbinsize, jt_binedges);
    TH1D *h1_jt_truth_1520 = new TH1D("jt_truth_1520", "", jtbinsize, jt_binedges);
    TH1D *h1_jt_truth_2030 = new TH1D("jt_truth_2030", "", jtbinsize, jt_binedges);
    TH1D *h1_jt_truth_3050 = new TH1D("jt_truth_3050", "", jtbinsize, jt_binedges);
    TH1D *h1_jt_truth_50100 = new TH1D("jt_truth_50100", "", jtbinsize, jt_binedges);
    TH1D *h1_jt_truth_100150 = new TH1D("jt_truth_100150", "", jtbinsize, jt_binedges);
    TH1D *h1_r_truth_12515 = new TH1D("r_truth_12515", "", rbinsize, r_binedges);
    TH1D *h1_r_truth_1520 = new TH1D("r_truth_1520", "", rbinsize, r_binedges);
    TH1D *h1_r_truth_2030 = new TH1D("r_truth_2030", "", rbinsize, r_binedges);
    TH1D *h1_r_truth_3050 = new TH1D("r_truth_3050", "", rbinsize, r_binedges);
    TH1D *h1_r_truth_50100 = new TH1D("r_truth_50100", "", rbinsize, r_binedges);
    TH1D *h1_r_truth_100150 = new TH1D("r_truth_100150", "", rbinsize, r_binedges);
    
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
    TH1D *h1_denom_efficiency_z = new TH1D("denom_efficiency_z", "", zbinsize, z_binedges);
    TH1D *h1_denom_efficiency_jt = new TH1D("denom_efficiency_jt", "", jtbinsize, jt_binedges );
    TH1D *h1_denom_efficiency_r = new TH1D("denom_efficiency_r", "", rbinsize, r_binedges);

    // 1D Kinematic Efficiencies and Purities (248-251)
    TH1D *h1_num_purity_jetpt = new TH1D("num_purity_jetpt", "", longptbinsize, longpt_binedges);
    TH1D *h1_denom_purity_jetpt = new TH1D("denom_purity_jetpt", "", longptbinsize, longpt_binedges);
    TH1D *h1_num_purity_rap = new TH1D("num_purity_rap", "", etabinsize, eta_binedges);       /// Jet Rap or HF rap?
    TH1D *h1_denom_purity_rap = new TH1D("denom_purity_rap", "", etabinsize, eta_binedges);  /// Jet Rap or HF rap?
    
    // 2D Efficiencies and Purities Observables (257 - 273)
    TH2D *h2_num_purity_zjt = new TH2D("num_purity_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_denom_purity_zjt = new TH2D("denom_purity_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    
    TH2D *h2_num_purity_zr = new TH2D("num_purity_zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
    TH2D *h2_denom_purity_zr = new TH2D("denom_purity_zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
    
    TH2D *h2_num_purity_jtr = new TH2D("num_purity_jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);
    TH2D *h2_denom_purity_jtr = new TH2D("denom_purity_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    TH2D *h2_num_efficiency_zjt = new TH2D("num_efficiency_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    TH2D *h2_denom_efficiency_zjt = new TH2D("denom_efficiency_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
    
    TH2D *h2_num_efficiency_zr = new TH2D("num_efficiency_zr", "",  zbinsize, z_binedges, rbinsize, r_binedges);
    TH2D *h2_denom_efficiency_zr = new TH2D("denom_efficiency_zr", "",  zbinsize, z_binedges, rbinsize, r_binedges);
    
    TH2D *h2_num_efficiency_jtr = new TH2D("num_efficiency_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
    TH2D *h2_denom_efficiency_jtr = new TH2D("denom_efficiency_jtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges);
    
    // 2D and 4D Observables response Matrices (286 - 292)
    RooUnfoldResponse *response_zjt = new RooUnfoldResponse( h2_zjt, h2_zjt_truth, "response_zjt" );
    RooUnfoldResponse *response_zr = new RooUnfoldResponse( h2_zr, h2_zr_truth, "respose_zr");
    RooUnfoldResponse *response_jtr = new RooUnfoldResponse( h2_jtr , h2_jtr_truth, "respose_jtr");
    RooUnfoldResponse *response_z = new RooUnfoldResponse(h1_denom_purity_z, h1_denom_efficiency_z, "response_z");
    RooUnfoldResponse *response_jt = new RooUnfoldResponse(h1_denom_purity_jt, h1_denom_efficiency_jt, "response_jt");
    RooUnfoldResponse *response_r = new RooUnfoldResponse(h1_denom_purity_r, h1_denom_efficiency_r, "response_r");
    
    // 1D Kinematic Efficiencies and Purities (299 - 306)
//    TH1D *h1_num_efficiency_jetpt = new TH1D("num_efficiency_jetpt", "", longptbinsize, longpt_binedges);
    TH1D *h1_num_efficiency_jetpt = new TH1D("num_efficiency_jetpt", "", ptbinsize, pt_binedges);
    
    TH1D *h1_denom_efficiency_jetpt = new TH1D("denom_efficiency_jetpt", "", ptbinsize, pt_binedges);
//    TH1D *h1_denom_efficiency_jetpt = new TH1D("denom_efficiency_jetpt", "", longptbinsize, longpt_binedges);
    
    TH1D *h1_num_efficiency_HFpt = new TH1D("num_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_denom_efficiency_HFpt = new TH1D("denom_efficiency_HFpt", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_num_efficiency_HFeta = new TH1D("num_efficiency_HFeta", "", etabinsize, eta_binedges);
    TH1D *h1_denom_efficiency_HFeta = new TH1D("denom_efficiency_HFeta", "", etabinsize, eta_binedges);
    TH1D *h1_num_efficiency_jetrap = new TH1D("num_efficiency_rap", "", etabinsize, eta_binedges);
    TH1D *h1_denom_efficiency_jetrap = new TH1D("denom_efficiency_rap", "", etabinsize, eta_binedges);
    
    // 2D jet_pt Efficiencies (308 - 309)
    TH2D *h2_num_efficiency_jetpteta = new TH2D("num_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    TH2D *h2_denom_efficiency_jetpteta = new TH2D("denom_efficiency_jetpteta", "", ptbinsize, pt_binedges, etabinsize, eta_binedges);
    
    // 2D HFpt-eta Efficiencies; 3D HFpt-eta-jet_pt Efficiencies (311 - 318)
    TH2D *h2_num_efficiency_HFpteta = new TH2D("num_efficiency_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
    TH2D *h2_denom_efficiency_HFpteta = new TH2D("denom_efficiency_HFpteta", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges);
    TH3D *h3_denom_efficiency_HFptetajetpt = new TH3D("denom_efficiency_HFptetajetpt", "", ptHFbinsize, ptHF_binedges, HFetabinsize, HFeta_binedges, customptbinsize, custompt_binedges);

    TH2D *h2_denom_efficiency_HFptjetpt = new TH2D("denom_efficiency_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_denom_efficiency_HFptnTracks = new TH2D("denom_efficiency_HFptnTracks","",ptHFbinsize, ptHF_binedges, nTracksbinsize, nTrack_binedges);
    
    // Reco/Truth Jet pt 1D Hists; Jet Pt Response Matrix (320 - 324)
    TH1D *h1_jetpt = new TH1D("jetpt", "", ptbinsize, pt_binedges);
    TH1D *h1_jetpt_truth = new TH1D("jetpt_truth", "", ptbinsize, pt_binedges);
    TH1D *h1_jetpt_test = new TH1D("jetpt_test", "", ptbinsize, pt_binedges);
    
    RooUnfoldResponse *response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, "response_jetpt", ";Reco Jet pT; Truth Jet pT");
    
    TH2D *h2_truthreco_jetpt = new TH2D("truthreco_jetpt", ";Reco Jet pT; Truth Jet pT", longptbinsize, longpt_binedges, longptbinsize, longpt_binedges);
    
    // 3D Efficiencies/Purities of 2D Observables vs jet_pt; 6D Response Matrices (324 - 357)
    /// Q: Is Ibrahim's "matched obsv." is my "truth obsv." ?

    TH3D *h3_ptzjt = new TH3D("ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptzjt = new TH3D("truthptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptzjt = new TH3D("num_efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_efficiency_ptzjt = new TH3D("denom_efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_efficiency_ptzjt = new TH3D("efficiency_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptzjt = new TH3D("num_purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptzjt = new TH3D("denom_purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptzjt = new TH3D("purity_ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptzjt = new RooUnfoldResponse(h3_ptzjt, h3_truthptzjt, "response_ptzjt");
    
    TH3D *h3_ptzr = new TH3D("ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptzr = new TH3D("truthptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptzr = new TH3D("num_efficiency_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_efficiency_ptzr = new TH3D("denom_efficiency_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_efficiency_ptzr = new TH3D("efficiency_ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptzr = new TH3D("num_purity_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptzr = new TH3D("denom_purity_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptzr = new TH3D("purity_ptzr", "",  zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );

    RooUnfoldResponse *response_ptzr = new RooUnfoldResponse(h3_ptzr, h3_truthptzr, "response_ptzr");
    
    TH3D *h3_ptjtr = new TH3D("ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_truthptjtr = new TH3D("truthptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_efficiency_ptjtr = new TH3D("num_efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_efficiency_ptjtr = new TH3D("denom_efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize,  pt_binedges );
    TH3D *h3_efficiency_ptjtr = new TH3D("efficiency_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_num_purity_ptjtr = new TH3D("num_purity_ptjtr", "",  jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_denom_purity_ptjtr = new TH3D("denom_purity_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH3D *h3_purity_ptjtr = new TH3D("purity_ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges,  ptbinsize, pt_binedges );

    RooUnfoldResponse *response_ptjtr = new RooUnfoldResponse(h3_ptjtr, h3_truthptjtr, "response_ptjtr");
    
    // 2D Jet_pt vs Observable histograms, Purities/Efficiencies, Responses (359 - 368)
    TH2D *h2_ptz = new TH2D("ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_truthptz = new TH2D("truthptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges );
    TH2D *h2_num_efficiency_ptz = new TH2D("num_efficiency_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_denom_efficiency_ptz = new TH2D("denom_efficiency_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges );
    TH2D *h2_efficiency_ptz = new TH2D("efficiency_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_num_purity_ptz = new TH2D("num_purity_ptz", "", zbinsize, z_binedges, ptbinsize, pt_binedges );
    TH2D *h2_denom_purity_ptz = new TH2D("denom_purity_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_purity_ptz = new TH2D("purity_ptz", "", zbinsize, z_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptz = new RooUnfoldResponse(h2_ptz, h2_truthptz, "response_ptz");
    
    TH2D *h2_ptjt = new TH2D("ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_truthptjt = new TH2D("truthptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH2D *h2_num_efficiency_ptjt = new TH2D("num_efficiency_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_denom_efficiency_ptjt = new TH2D("denom_efficiency_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
    TH2D *h2_efficiency_ptjt = new TH2D("efficiency_ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_num_purity_ptjt = new TH2D("num_purity_ptjt", "", jtbinsize, jt_binedges, ptbinsize, pt_binedges );
    TH2D *h2_denom_purity_ptjt = new TH2D("denom_purity_ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_purity_ptjt = new TH2D("purity_ptjt", "", jtbinsize, jt_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptjt = new RooUnfoldResponse(h2_ptjt, h2_truthptjt, "response_ptjt");
   
    TH2D *h2_ptr = new TH2D("ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_truthptr = new TH2D("truthptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH2D *h2_num_efficiency_ptr = new TH2D("num_efficiency_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    TH2D *h2_denom_efficiency_ptr = new TH2D("denom_efficiency_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges);
    TH2D *h2_efficiency_ptr = new TH2D("efficiency_ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_num_purity_ptr = new TH2D("num_purity_ptr", "", rbinsize, r_binedges, ptbinsize, pt_binedges );
    TH2D *h2_denom_purity_ptr = new TH2D("denom_purity_ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    TH2D *h2_purity_ptr = new TH2D("purity_ptr", "", rbinsize, r_binedges,  ptbinsize, pt_binedges );
    
    RooUnfoldResponse *response_ptr = new RooUnfoldResponse(h2_ptr, h2_truthptr, "response_ptr");
    
    TH3D *h3_denom_efficiency_ptzjt_50_100 = new TH3D("denom_efficiency_ptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges );   
    TH3D *h3_denom_efficiency_ptzr_50_100 = new TH3D("denom_efficiency_ptzr_50_100", "",  zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges );    
    TH3D *h3_denom_efficiency_ptjtr_50_100 = new TH3D("denom_efficiency_ptjtr_50_100", "",  jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize,  pt_binedges );    
    TH2D *h2_denom_efficiency_ptz_50_100 = new TH2D("denom_efficiency_ptz_50_100", "", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges );   
    TH2D *h2_denom_efficiency_ptjt_50_100 = new TH2D("denom_efficiency_ptjt_50_100", "", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);     
    TH2D *h2_denom_efficiency_ptr_50_100 = new TH2D("denom_efficiency_ptr_50_100", "", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);    
    
    TH2D *h2_SVTag_eff_denom = new TH2D("h2_SVTag_eff_denom","", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);
    TH2D *h2_SVTag_eff_denom_z = new TH2D("h2_SVTag_eff_denom_z","", zbinsize, z_binedges, customptbinsize, custompt_binedges);
    
    //// Other Stuff
    TH1D *h1_jetpt_reco_ext = new TH1D("jetpt_reco_ext", "", 20, 0.0, 100.);
    TH1D *h1_jetpt_truth_ext = new TH1D("jetpt_truth_ext", "", 20, 0.0, 100.);
   
    TH1D *h1_HFpt_reco_ext = new TH1D("HFpt_reco_ext", "", 20, 0.0, 100.);
    TH1D *h1_HFpt_truth_ext = new TH1D("HFpt_truth_ext", "", 20, 0.0, 100.);

  //
  // Event loop
  //
    unsigned long long last_eventNum = 0;
    double last_jetpT = 0.;
    int event_counter = 0;

    // Truth Variables (from Truth Tree)
    double jet_pt, jet_eta, meas_jet_pt, meas_jet_eta;
    double jet_px, jet_py, jet_pz, jet_e;
    double HF_px, HF_py, HF_pz, HF_e;
    double HF_pt;
    double jet_rap, meas_jet_rap;
    double pi_px, pi_py, pi_pz, pi_e;
    double pi0_px, pi0_py, pi0_pz, pi0_e;
    double K_px, K_py, K_pz, K_e;
  
    // Reco Variables (from Truth Tree)
    double meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e;
    double meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e;
    double meas_HF_pt;

    double WTA_dist(999);
    bool hasGamma;

    double truth_z, truth_jt, truth_r;
    double truth_z_c, truth_jt_c, truth_r_c;
    double truth_zg, truth_jtg, truth_rg;
    double meas_z, meas_jt, meas_r;
    double meas_inJet_z, meas_inJet_jt, meas_inJet_r;
    double jet_pt_recotruthratio, HF_pt_recotruthratio;

    int nsplits, ndtrs;
    int meas_nsplits, meas_ndtrs;
    int nTracks;
    int NumHFHads, eventNumber;

    bool hasRecoHF, Hasccbar;
    double ptweight(1.);

  DTree->SetBranchAddress("eventNumber", &eventNumber);

  DTree->SetBranchAddress("jet_pt", &jet_pt);
  DTree->SetBranchAddress("jet_eta", &jet_eta);
  DTree->SetBranchAddress("jet_rap", &jet_rap);

  DTree->SetBranchAddress("jet_px", &jet_px);
  DTree->SetBranchAddress("jet_py", &jet_py);
  DTree->SetBranchAddress("jet_pz", &jet_pz);
  DTree->SetBranchAddress("jet_e", &jet_e);

  DTree->SetBranchAddress("HF_px", &HF_px);
  DTree->SetBranchAddress("HF_py", &HF_py);
  DTree->SetBranchAddress("HF_pz", &HF_pz);
  DTree->SetBranchAddress("HF_e", &HF_e);
  DTree->SetBranchAddress("HF_pt", &HF_pt);

  DTree->SetBranchAddress("ndtrs", &ndtrs);
  DTree->SetBranchAddress("nsplits", &nsplits);

  DTree->SetBranchAddress("K_px", &K_px);
  DTree->SetBranchAddress("K_py", &K_py);
  DTree->SetBranchAddress("K_pz", &K_pz);
  DTree->SetBranchAddress("K_e", &K_e);

  DTree->SetBranchAddress("pi0_px", &pi0_px);
  DTree->SetBranchAddress("pi0_py", &pi0_py);
  DTree->SetBranchAddress("pi0_pz", &pi0_pz);
  DTree->SetBranchAddress("pi0_e", &pi0_e);

  DTree->SetBranchAddress("pi_px", &pi_px);
  DTree->SetBranchAddress("pi_py", &pi_py);
  DTree->SetBranchAddress("pi_pz", &pi_pz);
  DTree->SetBranchAddress("pi_e", &pi_e);

  DTree->SetBranchAddress("meas_jet_pt", &meas_jet_pt);
  DTree->SetBranchAddress("meas_jet_eta", &meas_jet_eta);
  DTree->SetBranchAddress("meas_jet_rap", &meas_jet_rap);

  DTree->SetBranchAddress("meas_HF_pt", &meas_HF_pt);

  DTree->SetBranchAddress("meas_jet_px", &meas_jet_px);
  DTree->SetBranchAddress("meas_jet_py", &meas_jet_py);
  DTree->SetBranchAddress("meas_jet_pz", &meas_jet_pz);
  DTree->SetBranchAddress("meas_jet_e", &meas_jet_e);

  DTree->SetBranchAddress("meas_HF_px", &meas_HF_px);
  DTree->SetBranchAddress("meas_HF_py", &meas_HF_py);
  DTree->SetBranchAddress("meas_HF_pz", &meas_HF_pz);
  DTree->SetBranchAddress("meas_HF_e", &meas_HF_e);

  DTree->SetBranchAddress("meas_ndtrs", &meas_ndtrs);
  DTree->SetBranchAddress("meas_nsplits", &meas_nsplits);

  DTree->SetBranchAddress("NumHFHads", &NumHFHads);
  DTree->SetBranchAddress("hasRecoHF", &hasRecoHF);
  DTree->SetBranchAddress("Hasccbar", &Hasccbar);
  DTree->SetBranchAddress("nTracks", &nTracks);

  DTree->SetBranchAddress("WTA_dist", &WTA_dist);
  DTree->SetBranchAddress("ptweight", &ptweight);

  DTree->SetBranchAddress("hasGamma", &hasGamma);

  DTree->SetBranchAddress("truth_z", &truth_z);
  DTree->SetBranchAddress("truth_jt", &truth_jt);
  DTree->SetBranchAddress("truth_r", &truth_r);
  DTree->SetBranchAddress("truth_z_c", &truth_z_c);
  DTree->SetBranchAddress("truth_jt_c", &truth_jt_c);
  DTree->SetBranchAddress("truth_r_c", &truth_r_c);
  DTree->SetBranchAddress("truth_zg", &truth_zg);
  DTree->SetBranchAddress("truth_jtg", &truth_jtg);
  DTree->SetBranchAddress("truth_rg", &truth_rg);

  DTree->SetBranchAddress("meas_z", &meas_z);
  DTree->SetBranchAddress("meas_jt", &meas_jt);
  DTree->SetBranchAddress("meas_r", &meas_r);

  DTree->SetBranchAddress("meas_inJet_z", &meas_inJet_z);
  DTree->SetBranchAddress("meas_inJet_jt", &meas_inJet_jt);
  DTree->SetBranchAddress("meas_inJet_r", &meas_inJet_r);

  int eventNum;
  int NumJets_zdR = 0;
  int NumJets_ktdR = 0;
  int NumD2KKPi = 0;
  int NumRecoD2KKPi = 0;

  cout << "Requested # of events" << NumEvts << endl;
  for (int ev = 0; ev < NumEvts; ev++)
  {
    // cout << jet_pt << ", ";

    DTree->GetEntry(ev);
    // if (jet_pt < pTLow)
    //   continue;

    if (ev % 500000 == 0)
      cout << "Executing event " << ev << endl;

    TLorentzVector HFmeson(HF_px, HF_py, HF_pz, HF_e);
    TLorentzVector meas_HFmeson(meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e);

    double event_weight = 1.0;

    bool rap_cond = (jet_rap > etaMin && jet_rap < etaMax);
    bool pt_cond = (jet_pt > pTLow);
    bool meas_rap_cond = (meas_jet_rap > etaMin && meas_jet_rap < etaMax);
    bool meas_pt_cond = (meas_jet_pt > pTLow);
    bool WTA_cond = (WTA_dist < WTA_max);

    if (SubtractGS && Hasccbar)
      continue;

    // if (WTA_cut && !WTA_cond)
    //   continue;

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
    int treeNumber = DTree->GetTreeNumber();

    // // cout << ptweight << ", ";
    ptweight = 1.0;
    event_weight *= ptweight;

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

    ///////////////////////////////////////////////////
    // Fill the denominator of the efficiency
    // Denominator = all truth B jets in fiducial region
    ///////////////////////////////////////////////////

    h1_jetpt_reco_ext->Fill(meas_jet_pt);
    h1_jetpt_truth_ext->Fill(jet_pt);

    h1_HFpt_reco_ext->Fill(meas_HFmeson.Pt());
    h1_HFpt_truth_ext->Fill(HFmeson.Pt());

        if (hasRecoHF && meas_pt_cond && meas_rap_cond)
        {
            response_jetpt->Fill(meas_jet_pt, jet_pt);
            
            response_z->Fill(meas_z, truth_z);
            response_jt->Fill(meas_jt, truth_jt);
            response_r->Fill(meas_r, truth_r);
            
            response_zjt->Fill(meas_z, meas_jt, truth_z, truth_jt);
            response_zr->Fill(meas_z, meas_r, truth_z, truth_r);
            response_jtr->Fill(meas_jt, meas_r, truth_jt, truth_r);
            
            response_ptjt->Fill( meas_jt,  meas_jet_pt, truth_jt, jet_pt);
            response_ptr->Fill( meas_r,  meas_jet_pt, truth_r, jet_pt);
            response_ptz->Fill( meas_z,  meas_jet_pt, truth_z, jet_pt);
            
            response_ptzjt->Fill( meas_z, meas_jt, meas_jet_pt, truth_z, truth_jt, jet_pt);
            response_ptzr->Fill( meas_z, meas_r, meas_jet_pt, truth_z, truth_r, jet_pt);
            response_ptjtr->Fill( meas_jt,  meas_r, meas_jet_pt, truth_jt, truth_r, jet_pt);
            
        }

    if (pt_cond && rap_cond)
    {
      NumD2KKPi++;

            h1_denom_efficiency_HFpt->Fill(HF_pt, event_weight);
            h1_denom_efficiency_HFeta->Fill(HFmeson.Eta(), event_weight);
            h1_denom_efficiency_jetrap->Fill(jet_rap, event_weight);
            
            h2_denom_efficiency_HFpteta->Fill(HFmeson.Pt(), HFmeson.Rapidity(), event_weight);
            h3_denom_efficiency_HFptetajetpt->Fill(HFmeson.Pt(), HFmeson.Rapidity(), jet_pt, event_weight);
            h1_denom_efficiency_jetpt->Fill(jet_pt, event_weight);
            h2_denom_efficiency_HFptjetpt->Fill(HFmeson.Pt(), jet_pt, event_weight);
            
//            h2_denom_efficiency_fragzjetpt->Fill(HFmeson.Pt() / jet_pt, jet_pt);
            h2_denom_efficiency_HFptnTracks->Fill(HFmeson.Pt(), nTracks, event_weight);
            
            h2_denom_efficiency_ptz->Fill(truth_z, jet_pt, event_weight);
            h2_denom_efficiency_ptjt->Fill(truth_jt, jet_pt, event_weight);
            h2_denom_efficiency_ptr->Fill(truth_r, jet_pt, event_weight);
    
            h3_denom_efficiency_ptzjt->Fill(truth_z, truth_jt, jet_pt, event_weight);
            h3_denom_efficiency_ptzr->Fill(truth_z, truth_r, jet_pt, event_weight);
            h3_denom_efficiency_ptjtr->Fill(truth_jt, truth_r, jet_pt, event_weight);
            
            h2_denom_efficiency_ptz_50_100->Fill(truth_z, jet_pt, event_weight);
            h2_denom_efficiency_ptjt_50_100->Fill(truth_jt, jet_pt, event_weight);
            h2_denom_efficiency_ptr_50_100->Fill(truth_r, jet_pt, event_weight);
    
            h3_denom_efficiency_ptzjt_50_100->Fill(truth_z, truth_jt, jet_pt, event_weight);
            h3_denom_efficiency_ptzr_50_100->Fill(truth_z, truth_r, jet_pt, event_weight);
            h3_denom_efficiency_ptjtr_50_100->Fill(truth_jt, truth_r, jet_pt, event_weight);            
            
            h1_denom_efficiency_z->Fill(truth_z, event_weight);
            h1_denom_efficiency_jt->Fill(truth_jt, event_weight);
            h1_denom_efficiency_r->Fill(truth_r, event_weight);
  
            h2_denom_efficiency_zjt->Fill(truth_z, truth_jt, event_weight);
            h2_denom_efficiency_zr->Fill(truth_z, truth_r, event_weight);
            h2_denom_efficiency_jtr->Fill(truth_jt, truth_r, event_weight);

      if (Hasccbar)
      {
        h2_SVTag_eff_denom_z->Fill(truth_z, jet_pt, event_weight);
      }
    }

    ///////////////////////////////////////////////////
    // Fill the numerator of the efficiency & response matrix
    // Numerator = all reco B jets in fiducial region
    ////////////////////////////////////////////////////
    // cout << jet_pt << ", " << meas_jet_pt << endl;
    // if (jet_pt > ptMin && jet_pt < ptMax && rap_cond && meas_pt_cond && hasRecoHF)
    if (pt_cond && rap_cond && meas_pt_cond && hasRecoHF)
      {
          
          h1_num_efficiency_HFpt->Fill(HF_pt, event_weight);
          h1_num_efficiency_HFeta->Fill(HFmeson.Eta(), event_weight);
          h1_num_efficiency_jetrap->Fill(jet_rap, event_weight);
          
          h2_num_efficiency_HFpteta->Fill(HFmeson.Pt(), HFmeson.Rapidity(), event_weight);
          h1_num_efficiency_jetpt->Fill(jet_pt, event_weight);
          h2_num_efficiency_jetpteta->Fill(jet_pt, jet_rap, event_weight);
          
          h1_num_efficiency_z->Fill(truth_z, event_weight);
          h1_num_efficiency_jt->Fill(truth_jt, event_weight);
          h1_num_efficiency_r->Fill(truth_r, event_weight);

          h2_num_efficiency_zjt->Fill(truth_z, truth_jt, event_weight);
          h2_num_efficiency_zr->Fill(truth_z, truth_r, event_weight);
          h2_num_efficiency_jtr->Fill(truth_jt, truth_r, event_weight);
          
          h2_num_efficiency_ptz->Fill(truth_z, jet_pt, event_weight);
          h2_num_efficiency_ptjt->Fill(truth_jt, jet_pt, event_weight);
          h2_num_efficiency_ptr->Fill(truth_r, jet_pt, event_weight);
  
          h3_num_efficiency_ptzjt->Fill(truth_z, truth_jt, jet_pt, event_weight);
          h3_num_efficiency_ptzr->Fill(truth_z, truth_r, jet_pt, event_weight);
          h3_num_efficiency_ptjtr->Fill( truth_jt, truth_r, jet_pt, event_weight);
          
      }

            if (meas_pt_cond)
        {
            h1_num_purity_jetpt->Fill(jet_pt, event_weight);
            h1_num_purity_rap->Fill(jet_rap, event_weight);
            
//            h1_num_purity_z->Fill(meas_z);
//            h1_num_purity_jt->Fill(meas_jt);
//            h1_num_purity_r->Fill(meas_r);
// 
//            h2_num_purity_zjt->Fill(meas_z, meas_jt);
//            h2_num_purity_zr->Fill(meas_z, meas_r);
//            h2_num_purity_jtr->Fill(meas_jt, meas_r);
//
//            h2_num_purity_ptz->Fill(meas_z, meas_jet_pt);
//            h2_num_purity_ptjt->Fill(meas_jt, meas_jet_pt);
//            h2_num_purity_ptr->Fill(meas_r, meas_jet_pt);
//            
//            h3_num_purity_ptzjt->Fill(meas_z, meas_jt, meas_jet_pt );
//            h3_num_purity_ptzr->Fill(meas_z, meas_r, meas_jet_pt);
//            h3_num_purity_ptjtr->Fill(meas_jt, meas_r, meas_jet_pt);
//  
            
        }

    ////////////////////////////////////////////////////////////////////////////
    // Only keep events where both truth and reco jets are in the fiducial region
    ////////////////////////////////////////////////////////////////////////////

    if (!pt_cond || !rap_cond)
      continue;

        h1_jetpt_truth->Fill(jet_pt);
        h1_z_truth->Fill(truth_z);
        h1_jt_truth->Fill(truth_jt);
        h1_r_truth->Fill(truth_r);
        
        h2_zjt_truth->Fill(truth_z, truth_jt);
        h2_zr_truth->Fill(truth_z, truth_r);
        h2_jtr_truth->Fill( truth_jt, truth_r);

        h3_truthptzjt->Fill(truth_z, truth_jt, jet_pt);
        h3_truthptzr->Fill(truth_z, truth_r, jet_pt);
        h3_truthptjtr->Fill( truth_jt, truth_r, jet_pt );
        
    
        if (jet_pt > 12.5 && jet_pt < 15.0 ) {
            
            h1_z_truth_12515->Fill(truth_z);
            h1_jt_truth_12515->Fill(truth_jt);
            h1_r_truth_12515->Fill(truth_r);
          
        }
        if (jet_pt > 15.0 && jet_pt < 20.0 ) {
          
            h1_z_truth_1520->Fill(truth_z);
            h1_jt_truth_1520->Fill(truth_jt);
            h1_r_truth_1520->Fill(truth_r);
            
        }
        if (jet_pt > 20.0 && jet_pt < 30.0 ) {
          
            h1_z_truth_2030->Fill(truth_z);
            h1_jt_truth_2030->Fill(truth_jt);
            h1_r_truth_2030->Fill(truth_r);
        }
        if (jet_pt > 30.0 && jet_pt < 50.0 ) {
            h1_z_truth_3050->Fill(truth_z);
            h1_jt_truth_3050->Fill(truth_jt);
            h1_r_truth_3050->Fill(truth_r);
        }
        if (jet_pt > 50.0 && jet_pt < 100.0 ) {
            h1_z_truth_50100->Fill(truth_z);
            h1_jt_truth_50100->Fill(truth_jt);
            h1_r_truth_50100->Fill(truth_r);
        }
        if (jet_pt > 100.0 && jet_pt < 150.0 ) {
            h1_z_truth_100150->Fill(truth_z);
            h1_jt_truth_100150->Fill(truth_jt);
            h1_r_truth_100150->Fill(truth_r);
        }

    if (!meas_pt_cond || !meas_rap_cond || !hasRecoHF)
      continue;

    h1_z->Fill(meas_z);
    h1_jt->Fill(meas_jt);
    h1_r->Fill(meas_r);

    h2_truthreco_jetpt->Fill(meas_jet_pt, jet_pt);
    h2_truthreco_z->Fill(meas_z, truth_z);
    h2_truthreco_jt->Fill(meas_jt, truth_jt);
    h2_truthreco_r->Fill(meas_r, truth_r);
        
    h2_zjt->Fill(meas_z, meas_jt);
    h2_zr->Fill(meas_z, meas_r);
    h2_jtr->Fill( meas_jt, meas_r);
        
    h3_ptzjt->Fill(meas_z, meas_jt, meas_jet_pt);
    h3_ptzr->Fill(meas_z, meas_r, meas_jet_pt);
    h3_ptjtr->Fill( meas_jt,meas_r, meas_jet_pt);
        
//        if (jet_pt > ptMin && jet_pt < ptMax)
//        {
//            response_zjt->Fill(meas_z, meas_jt, truth_z, truth_jt);
//            response_zr->Fill(meas_z, meas_r, truth_z, truth_r);
//        }

    // cout << "num:" << meas_jet_pt << endl;

    // Matching Procedure:
    // Loop over truth emissions and find matches (dR < 0.1) at reco level
    // Loop over reco emissions and find matches (dR < 0.1) at truth level
    // If an emission is matched both ways, it is declared a match
    // Fill response matrix with matches
    // Fill eff. histograms with unmatched truth emissions
    // Fill purity histograms with unmatched reco emissions

    event_counter++;
  }

  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
  // Save and Draw
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////

//  RooUnfoldResponse * response_jetpt = new RooUnfoldResponse(h1_jetpt, h1_jetpt_truth, h2_truthreco_jetpt, "response_jetpt");
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
    

    response_jetpt->Write("response_jetpt");
    response_z->Write("response_z");
    response_jt->Write("response_jt");
    response_r->Write("response_r");
    response_zjt->Write("response_zjt") ;
    response_zr->Write("response_zr" );
    response_jtr->Write( "response_jtr");
    
    response_ptjt->Write("response_ptjt" );
    response_ptr->Write( "response_ptr");
    response_ptz->Write("response_ptz" );
    
    response_ptzjt->Write("response_ptzjt" );
    response_ptzr->Write( "response_ptzr");
    response_ptjtr->Write( "response_ptjtr") ;
    
    

    TH1D *h1_efficiency_jetpt = (TH1D *)h1_num_efficiency_jetpt->Clone("h1_efficiency_jetpt");
    h1_efficiency_jetpt->Divide(h1_num_efficiency_jetpt, h1_denom_efficiency_jetpt, 1, 1, "B");

    TH1D *h1_efficiency_jetrap = (TH1D *)h1_num_efficiency_jetrap->Clone("h1_efficiency_jetrap");
    h1_efficiency_jetrap->Divide(h1_num_efficiency_jetrap, h1_denom_efficiency_jetrap, 1, 1, "B");

    TH1D *h1_efficiency_HFpt = (TH1D *)h1_num_efficiency_HFpt->Clone("h1_efficiency_HFpt");
    h1_efficiency_HFpt->Divide(h1_num_efficiency_HFpt, h1_denom_efficiency_HFpt, 1, 1, "B");

    TH1D *h1_efficiency_HFeta = (TH1D *)h1_num_efficiency_HFeta->Clone("h1_efficiency_HFeta");
    h1_efficiency_HFeta->Divide(h1_num_efficiency_HFeta, h1_denom_efficiency_HFeta, 1, 1, "B");
    
    TH1D *h1_efficiency_z = (TH1D *)h1_num_efficiency_z->Clone("h1_efficiency_z");
    h1_efficiency_z->Divide(h1_num_efficiency_z, h1_denom_efficiency_z, 1, 1, "B");
    
    TH1D *h1_efficiency_jt = (TH1D *)h1_num_efficiency_jt->Clone("h1_efficiency_jt");
    h1_efficiency_jt->Divide(h1_num_efficiency_jt, h1_denom_efficiency_jt, 1, 1, "B");
    
    TH1D *h1_efficiency_r = (TH1D *)h1_num_efficiency_r->Clone("h1_efficiency_r");
    h1_efficiency_r->Divide(h1_num_efficiency_r, h1_denom_efficiency_r, 1, 1, "B");

    TH2D *h2_efficiency_jetpteta = (TH2D *)h2_num_efficiency_jetpteta->Clone("h2_efficiency_jetpteta");
    h2_efficiency_jetpteta->Divide(h2_num_efficiency_jetpteta, h2_denom_efficiency_jetpteta, 1, 1, "B");

    TH2D *h2_efficiency_HFpteta = (TH2D *)h2_num_efficiency_HFpteta->Clone("h2_efficiency_HFpteta");
    h2_efficiency_HFpteta->Divide(h2_num_efficiency_HFpteta, h2_denom_efficiency_HFpteta, 1, 1, "B");


    // TEfficiency * h1_efficiency_jetpt = new TEfficiency(*h1_num_efficiency_jetpt, *h1_denom_efficiency_jetpt);
    // TEfficiency * h1_efficiency_jeteta = new TEfficiency(*h1_num_efficiency_jeteta, *h1_denom_efficiency_jeteta);

    /////////////////////////////////

    TSpline3 sp(h1_efficiency_HFpt);
    TF1 *f_eff1 = new TF1("f_eff1", "[0]*tanh([1]*(x-[3]))+[2]", 2, 25);
    TF1 *f_eff2 = new TF1("f_eff2", "[0]*tanh([1]*([3] - x))+[2]", 25, 100);
    f_eff1->SetParameters(0.2, 0.1, 0.2, 6.4);
    f_eff2->SetParameters(0.2, 0.1, 0.2, 100);
    f_eff2->SetParLimits(3, 80, 200);
//  h1_efficiency_HFpt->Fit("f_eff1", "E", "SAME", 2, 25);
//  h1_efficiency_HFpt->Fit("f_eff2", "E", "SAME", 25, 100);

//  f_eff1->Write("f_eff1");
//  f_eff2->Write("f_eff2");
// TF1 *f_eff = new TF1(
//     "f_eff", [=](double *x, double *p)
//     { return (sp.Eval(x[0])); },
//     sp.GetXmin(), sp.GetXmax(), 2);

    /////////////////////////////////
    
    h1_efficiency_jetpt->Write("efficiency_jetpt");
    h1_denom_efficiency_HFpt->Write("h1_denom_efficiency_HFpt");
    h1_denom_efficiency_jetpt->Write("h1_denom_efficiency_jetpt");
    h1_efficiency_HFpt->Write("efficiency_HFpt");
    h1_efficiency_HFeta->Write("efficiency_HFeta");
    h1_efficiency_jetrap->Write("efficiency_jetrap");
    h1_efficiency_z->Write("efficiency_z");
    h1_efficiency_jt->Write("efficiency_jt");
    h1_efficiency_r->Write("efficiency_r");
    
    h2_denom_efficiency_HFptjetpt->Write("h2_denom_efficiency_HFptjetpt");
    h2_efficiency_jetpteta->Write("efficiency_jetpteta");
    h2_efficiency_HFpteta->Write("efficiency_HFpteta");

    cout << event_counter << " events processed" << endl;

    //
    int ican = -1, iframe = -1, itext = -1;
    TCanvas *ccan[1000];
    TH1F *frame[1000];
    TLatex *text[1000];

    for (int i = 0; i < 1000; i++) {
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
    // TString OutputFileBase	= outbase+outinfo;
    TString plotextension = TString("../../plots/DjetsMC/");
    rootfile = extension_RootFilesMC + extension + TString(".root");
    plotfile = plotextension + extension + TString(".ps");

    plotfilePDF = plotextension + extension + TString(".pdf");
    plotfileO = plotfilePDF + TString("(");
    plotfileC = plotfilePDF + TString("]");

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

    gPad->SetLogz();
    // Tl.drawLatex(0.7, 0.8, "No cuts");
    ccan[ican]->cd(2);
    // Tl.drawLatex(0.7, 0.8, "No cuts");
//  ccan[ican]->cd(3);
    h2_response_jetpt->SetStats(0);
    gPad->SetLogz();
    h2_response_jetpt->Draw("COLZ");
    h2_response_jetpt->SetTitle("; Reco Jet pT; Truth Jet pT");

    ccan[ican]->cd(3);
    NormalizeHist(h1_jetpt);
    h1_jetpt->Draw("same");

//    NormalizeHist(h1_jetpt_truth);
    h1_jetpt_truth->SetLineColor(kGreen);
    h1_jetpt_truth->Draw("same");

    ccan[ican]->cd();
    ccan[ican]->Update();

    if (ican == 0) {
        ccan[ican]->Print(plotfileO.Data());
    } else {
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

    h1_efficiency_jetpt->SetMarkerColor(kBlue);
    h1_efficiency_jetpt->SetMarkerStyle(21);
    h1_efficiency_jetpt->Draw("P E SAME");
    h1_efficiency_jetpt->SetTitle("; Jet pT; HF Jet Reco. Efficiency");
    h1_efficiency_jetpt->SetMinimum(0.);
    // h1_efficiency_jetpt->SetMaximum(1.);
    h1_efficiency_jetpt->SetMaximum(0.1);
    // h1_efficiency_jetpt->SetXTitle("E_{radiator}");
    // h1_efficiency_jetpt->SetYTitle("Counts");
    // gPad->Update();
    // auto graphpt3 = h1_efficiency_jetpt->GetPaintedGraph();
    // graphpt3->SetMinimum(0);
    // graphpt3->SetMaximum(1);
    // gPad->Update();
    // h1_efficiency_jetpt->SetMinimum(0.0);
    ccan[ican]->cd(2);
    h1_efficiency_jetrap->SetMarkerColor(kBlue);
    h1_efficiency_jetrap->SetMarkerStyle(21);
    h1_efficiency_jetrap->Draw("P E same");
    h1_efficiency_jetrap->SetTitle("; Jet #eta; HF Jet Reco. Efficiency");
    h1_efficiency_jetrap->SetMinimum(0.);
    // h1_efficiency_jetrap->SetMaximum(1.);
    h1_efficiency_jetrap->SetMaximum(0.1);
    // h1_efficiency_jeteta->SetXTitle("E_{radiator}");
    // h1_efficiency_jeteta->SetYTitle("Counts");

    ccan[ican]->cd(3);

    h1_efficiency_HFpt->SetMarkerColor(kBlue);
    h1_efficiency_HFpt->SetMarkerStyle(21);
    h1_efficiency_HFpt->Draw("P E SAME");
    h1_efficiency_HFpt->SetTitle("; HF pT; HF Jet Reco. Efficiency");
    h1_efficiency_HFpt->SetMinimum(0.);
    // h1_efficiency_HFpt->SetMaximum(1.05);
    h1_efficiency_HFpt->SetMaximum(0.1);
//
//  f_eff1->Draw("SAME");
//  f_eff2->Draw("SAME");

    ccan[ican]->cd(4);

    h1_efficiency_HFeta->SetMarkerColor(kBlue);
    h1_efficiency_HFeta->SetMarkerStyle(21);
    h1_efficiency_HFeta->Draw("P E SAME");
    h1_efficiency_HFeta->SetTitle("; HF #eta; HF Jet Reco. Efficiency");
    h1_efficiency_HFeta->SetMinimum(0.);
    h1_efficiency_HFeta->SetMaximum(0.1);

    ccan[ican]->cd(5);

    h2_efficiency_HFpteta->Draw("COLZ TEXT");
    h2_efficiency_HFpteta->SetTitle("; HF p_{T}; HF #eta; Jet Reco Efficiency");
    h2_efficiency_HFpteta->SetMinimum(0.);
    // h2_efficiency_HFpteta->SetMaximum(1.);

    ccan[ican]->cd(6);

    h2_efficiency_jetpteta->Draw("COLZ TEXT");
    h2_efficiency_jetpteta->SetTitle("; jet p_{T}; jet #eta; Jet Reco Efficiency");
    h2_efficiency_jetpteta->SetMinimum(0.);
    // h2_efficiency_jetpteta->SetMaximum(1.);
    
    ccan[ican]->cd(7);

    h1_efficiency_z->SetMarkerColor(kBlue);
    h1_efficiency_z->SetMarkerStyle(21);
    h1_efficiency_z->Draw("P E SAME");
    h1_efficiency_z->SetTitle("; z ; HF Jet Reco. Efficiency");
    h1_efficiency_z->SetMinimum(0.);
    h1_efficiency_z->SetMaximum(1.);
    
    ccan[ican]->cd(8);

    h1_efficiency_jt->SetMarkerColor(kBlue);
    h1_efficiency_jt->SetMarkerStyle(21);
    h1_efficiency_jt->Draw("P E SAME");
    h1_efficiency_jt->SetTitle("; j_{T} [GeV] ; HF Jet Reco. Efficiency");
    h1_efficiency_jt->SetMinimum(0.);
    h1_efficiency_jt->SetMaximum(1.);
    
    ccan[ican]->cd(9);

    h1_efficiency_r->SetMarkerColor(kBlue);
    h1_efficiency_r->SetMarkerStyle(21);
    h1_efficiency_r->Draw("P E SAME");
    h1_efficiency_r->SetTitle("; r ; HF Jet Reco. Efficiency");
    h1_efficiency_r->SetMinimum(0.);
    h1_efficiency_r->SetMaximum(1.);

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

  f.Write();
  f.Close();

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());

    cout << "Num of True B jets = " << NumD2KKPi << endl;
    cout << "Num of Reco B jets = " << NumRecoD2KKPi << endl;
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

  // CAJetAlgo(std::string filename);

  // loop(ptMax, Nsubsets);
  // write(ptMax, Nsubsets);
}
