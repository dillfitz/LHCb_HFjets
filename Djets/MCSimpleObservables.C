

// #include "AnalyzeDijetData_withsubsets.h"
// #include "LundPlaneData.h"

// #include "HFjetLuC"

#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"

using namespace std;

void MCSimpleObservables(int NumEvts = 10000, int dataset = 1510,
                         bool chargedJetCut_user = false,
                         bool WTA_cut = true,
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
  int HF_pdgcode = -999;

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

  extension_RootFilesMC = TString("../../root_files/DjetsMC/");

  extension = str_level + str_Nevts + str_pt + str_eta + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_GS + str_WTA + str_prompt + Form("_%d", dataset);

  extension_read = TString("tree_") + str_level + str_Nevts + str_eta + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);

  // TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");
  cout << "Loading ntuples: " << endl;
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
  //     // if (ptranges[k] == 1 || ptranges[k] == 5)
  //     //   continue;
  //     // Select pthat 20 and above
  //     // if (ptranges[k] < 4)
  //     //   continue;

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

  // vec_datasets = {60490, 60491, 70490, 70491, 80490, 80491};

  // vec_datasets = {62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};
  vec_datasets = {61400, 61401, 62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};

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
      DTree->Add(extension_RootFilesMC + extension_read + ".root/DTree");
    }
  }
  else
  {
    extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_prompt + Form("_%d", dataset);
    // extension_read = extension_prefix + extension_read;
    cout << extension_read << endl;
    DTree->Add(extension_RootFilesMC + extension_read + ".root/DTree");
  }
  if (NumEvts > DTree->GetEntries())
    NumEvts = DTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = DTree->GetEntries();
  cout << DTree->GetEntries() << endl;

  TFile f(extension_RootFilesMC + extension + ".root", "RECREATE");

  // TH2D *h2_lundplane_b = new TH2D("B_LundPlane", "B-meson Lund Plane", 50, 0, 8, 50, -8, 8);
  // TH2D *h2_lundplane_c = new TH2D("D_LundPlane", "D-meson Lund Plane", 50, 0, 8, 50, -8, 8);
  // TH2D *h2_lundplane_inc = new TH2D("L_LundPlane", "Light Lund Plane", 50, 0, 8, 50, -8, 8);

  // for(int i = 0; i < ktbinsize+1; i++){
  //   kt_binedges[i] = kT_min + i*(kT_max - kT_min)/ktbinsize;
  //   dR_binedges[i] = dR_min + i * (dR_max - dR_min)/dRbinsize;
  //   z_binedges[i] = z_min + i*(z_max - z_min)/ktbinsize;
  // }

  TH2D *h2_ptz = new TH2D("ptz", ";z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt = new TH2D("ptjt", ";j_{T} [GeV/c]; p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr = new TH2D("ptr", ";r; p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);

  TH2D *h2_ptz_charm = new TH2D("h2_ptz_charm", ";z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt_charm = new TH2D("h2_ptjt_charm", ";j_{T} [GeV/c]; p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr_charm = new TH2D("h2_ptr_charm", ";r; p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);

  TH2D *h2_ptz_gluon = new TH2D("h2_ptz_gluon", ";z;p_{T,jet} [GeV/c]", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptjt_gluon = new TH2D("h2_ptjt_gluon", ";j_{T} [GeV/c]; p_{T,jet} [GeV/c]", jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH2D *h2_ptr_gluon = new TH2D("h2_ptr_gluon", ";r; p_{T,jet} [GeV/c]", rbinsize, r_binedges, ptbinsize, pt_binedges);

  TH2D *h2_ptz_gluon_ratio = (TH2D *)h2_ptz_gluon->Clone("h2_ptz_gluon_ratio");
  TH2D *h2_ptjt_gluon_ratio = (TH2D *)h2_ptjt_gluon->Clone("h2_ptjt_gluon_ratio");
  TH2D *h2_ptr_gluon_ratio = (TH2D *)h2_ptr_gluon->Clone("h2_ptr_gluon_ratio");

  TH3D *h3_ptzjt = new TH3D("ptzjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_ptzr = new TH3D("ptzr", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_ptjtr = new TH3D("ptjtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);

  TH2D *h2_ptz_50_100 = new TH2D("ptz_50_100", ";z;", zbinsize_50_100, z_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_ptjt_50_100 = new TH2D("ptjt_50_100", ";j_{T};", jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH2D *h2_ptr_50_100 = new TH2D("ptr_50_100", ";r;", rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);

  TH3D *h3_ptzjt_50_100 = new TH3D("ptzjt_50_100", "", zbinsize_50_100, z_binedges_50_100, jtbinsize_50_100, jt_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_ptzr_50_100 = new TH3D("ptzr_50_100", "", zbinsize_50_100, z_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);
  TH3D *h3_ptjtr_50_100 = new TH3D("ptjtr_50_100", "", jtbinsize_50_100, jt_binedges_50_100, rbinsize_50_100, r_binedges_50_100, ptbinsize, pt_binedges);

  TH3D *h3_ptzjt_gluon = new TH3D("ptzjt_gluon", "", zbinsize, z_binedges, jtbinsize, jt_binedges, ptbinsize, pt_binedges);
  TH3D *h3_ptzr_gluon = new TH3D("ptzr_gluon", "", zbinsize, z_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);
  TH3D *h3_ptjtr_gluon = new TH3D("ptjtr_gluon", "", jtbinsize, jt_binedges, rbinsize, r_binedges, ptbinsize, pt_binedges);

  //    TH1D *h1_frag_jt = new TH1D("frag_jt", "", 30, 0, 12);
  //    TH1D *h1_frag_z = new TH1D("frag_z", "", zbinsize, z_binedges);
  //    TH1D *h1_frag_r = new TH1D("frag_r", "", 30, 0, 1);

  TH1D *h1_frag_jt_gluon = new TH1D("frag_jt_gluon", "", 30, 0, 12);
  TH1D *h1_frag_z_gluon = new TH1D("frag_z_gluon", "", zbinsize, z_binedges);
  TH1D *h1_frag_r_gluon = new TH1D("frag_r_gluon", "", 30, 0, 1);

  TH1D *h1_frag_jt_charm = new TH1D("frag_jt_charm", "", 30, 0, 12);
  TH1D *h1_frag_z_charm = new TH1D("frag_z_charm", "", zbinsize, z_binedges);
  TH1D *h1_frag_r_charm = new TH1D("frag_r_charm", "", 30, 0, 1);

  TH2D *h2_frag_z_jetpt = new TH2D("frag_z_jetpt", "", zbinsize, z_binedges, ptbinsize, pt_binedges);
  TH2D *h2_frag_z_jetpt_charm = new TH2D("frag_z_jetpt_charm", "", zbinsize, z_binedges, ptbinsize, pt_binedges);

  TH1D *h1_z = new TH1D("z", "", zbinsize, z_binedges);
  TH1D *h1_jt = new TH1D("jt", "", jtbinsize, jt_binedges);
  TH1D *h1_r = new TH1D("r", "", rbinsize, r_binedges);

  TH1D *h1_meas_z = new TH1D("meas_z", "", zbinsize, z_binedges);
  TH1D *h1_meas_jt = new TH1D("meas_jt", "", jtbinsize, jt_binedges);
  TH1D *h1_meas_r = new TH1D("meas_r", "", rbinsize, r_binedges);

  TH2D *h2_zjt = new TH2D("zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
  TH2D *h2_zr = new TH2D("zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
  TH2D *h2_jtr = new TH2D("jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);

  TH2D *h2_zjt_gluon = new TH2D("zjt_gluon", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
  TH2D *h2_zr_gluon = new TH2D("zr_gluon", "", zbinsize, z_binedges, rbinsize, r_binedges);
  TH2D *h2_jtr_gluon = new TH2D("jtr_gluon", "", jtbinsize, jt_binedges, rbinsize, r_binedges);

  TH2D *h2_meas_zjt = new TH2D("meas_zjt", "", zbinsize, z_binedges, jtbinsize, jt_binedges);
  TH2D *h2_meas_zr = new TH2D("meas_zr", "", zbinsize, z_binedges, rbinsize, r_binedges);
  TH2D *h2_meas_jtr = new TH2D("meas_jtr", "", jtbinsize, jt_binedges, rbinsize, r_binedges);

  // 2D Truth-Reco Correspondence (219 - 224)
  TH2D *h2_truthreco_z = new TH2D("truthreco_z", ";Reco z; Truth z", zbinsize, z_binedges, zbinsize, z_binedges);
  TH2D *h2_truthreco_jt = new TH2D("truthreco_jt", ";Reco jT; Truth jT", jtbinsize, jt_binedges, jtbinsize, jt_binedges);
  TH2D *h2_truthreco_r = new TH2D("truthreco_r", ";Reco r; Truth r", rbinsize, r_binedges, rbinsize, r_binedges);

  TH1D *h1_ratio_z0 = new TH1D("ratio_z0", ";truth z / reco z;", 30, 0.0, 2.0);
  TH1D *h1_ratio_jt0 = new TH1D("ratio_jt0", ";truth jt / reco jt;", 30, 0.0, 2.0);
  TH1D *h1_ratio_r0 = new TH1D("ratio_r0", ";truth r / reco r;", 30, 0.0, 2.0);
  TH1D *h1_ratio_z1 = new TH1D("ratio_z1", ";reco z / truth z;", 30, 0.0, 2.0);
  TH1D *h1_ratio_jt1 = new TH1D("ratio_jt1", ";reco jt / truth jt;", 30, 0.0, 2.0);
  TH1D *h1_ratio_r1 = new TH1D("ratio_r1", ";reco r / truth r;", 30, 0.0, 2.0);

  TH1D *h1_jet_flav = new TH1D("Jet_Flav", "", 7, -0.5, 6.5);
  TH1D *h1_jet_pt = new TH1D("Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_jet_eta = new TH1D("Jet_eta", "", 12, etaMin, etaMax);
  TH1D *h1_jet_rap = new TH1D("Jet_rap", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi = new TH1D("Jet_phi", "", 20, -3.14, 3.14);
  TH1D *h1_jet_ptbalance0 = new TH1D("jet_ptbalance0", "", 20, 0.0, 2.0);
  TH1D *h1_jet_ptbalance1 = new TH1D("jet_ptbalance1", "", 20, 0.0, 2.0);

  TH2D *h2_jetpteta = new TH2D("h2_jetpteta", ";p_{T,jet} [GeV/c]; #eta", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_jetpteta_gluon = new TH2D("h2_jetpteta_gluon", ";p_{T,jet} [GeV/c]; #eta", ptbinsize, pt_binedges, etabinsize, eta_binedges);
  TH2D *h2_jetpteta_gluon_ratio = (TH2D *)h2_jetpteta_gluon->Clone("h2_jetpteta_gluon_ratio");

  TH2D *h2_jetptp = new TH2D("h2_jetptp", ";p_{T,jet} [GeV/c]; p_{jet} [GeV/c]", ptbinsize, pt_binedges, pbinsize, p_binedges);
  TH2D *h2_jetptp_gluon = new TH2D("h2_jetptp_gluon", "p_{T,jet} [GeV/c]; p_{jet} [GeV/c]", ptbinsize, pt_binedges, pbinsize, p_binedges);
  TH2D *h2_jetptp_gluon_ratio = (TH2D *)h2_jetptp_gluon->Clone("h2_jetptp_gluon_ratio");

  TH1D *h1_meas_jet_pt = new TH1D("meas_Jet_pT", "", ptbinsize, pt_binedges);
  TH1D *h1_meas_jet_eta = new TH1D("meas_Jet_eta", "", 12, etaMin, etaMax);
  TH1D *h1_meas_jet_rap = new TH1D("meas_Jet_rap", "", 12, etaMin, etaMax);
  TH1D *h1_meas_jet_phi = new TH1D("meas_Jet_phi", "", 20, -3.14, 3.14);

  TH1D *h1_jet_pt_noghost = new TH1D("Jet_pT_noghost", "", 50, ptMin, ptMax);
  TH1D *h1_jet_eta_noghost = new TH1D("Jet_eta_noghost", "", 12, etaMin, etaMax);
  TH1D *h1_jet_phi_noghost = new TH1D("Jet_phi_noghost", "", 20, -3.14, 3.14);

  ///////////
  TH1D *h1_Phi_rap = new TH1D("Phi_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_Phi_pt = new TH1D("Phi_pT", "", 50, 0, 100);
  TH1D *h1_Phi_phi = new TH1D("Phi_phi", "", 20, -3.14, 3.14);
  TH1D *h1_Phi_mass = new TH1D("Phi_mass", "", 30, 3.1 - 0.1, 3.1 + 0.1);

  TH1D *h1_meas_Phi_rap = new TH1D("meas_Phi_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_meas_Phi_pt = new TH1D("meas_Phi_pT", "", 50, 0, 100);
  TH1D *h1_meas_Phi_phi = new TH1D("meas_Phi_phi", "", 20, -3.14, 3.14);
  TH1D *h1_meas_Phi_mass = new TH1D("meas_Phi_mass", "", 30, 3.1 - 0.1, 3.1 + 0.1);

  TH1D *h1_pi0_eta = new TH1D("pi0_eta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_pi0_pt = new TH1D("pi0_pt", "", 40, 0, 20);
  TH1D *h1_K_eta = new TH1D("K_eta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_K_pt = new TH1D("K_pt", "", 40, 0, 20);
  TH1D *h1_pi_eta = new TH1D("K_eta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_pi_pt = new TH1D("pi_pt", "", 40, 0, 20);

  TH1D *h1_meas_pi0_eta = new TH1D("meas_pi0_eta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_meas_pi0_pt = new TH1D("meas_pi0_pt", "", 40, 0, 20);
  TH1D *h1_meas_K_eta = new TH1D("meas_K_eta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_meas_K_pt = new TH1D("meas_K_pt", "", 40, 0, 20);
  TH1D *h1_meas_pi_eta = new TH1D("meas_pi_eta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_meas_pi_pt = new TH1D("meas_pi_pt", "", 40, 0, 20);
  ///////////

  TH1D *h1_HF_rap = new TH1D("HF_rap", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_HF_pt = new TH1D("HF_pT", "", 50, 0, 100);
  TH1D *h1_HF_phi = new TH1D("HF_phi", "", 20, -3.14, 3.14);
  TH1D *h1_HF_mass = new TH1D("HF_mass", "", 30, 1.865 - 0.15, 1.865 + 0.15);
  TH1D *h1_HFjet_ptbalance = new TH1D("HFjet_ptbalance", "", 20, 0, 2);

  TH1D *h1_HFpt_GS = new TH1D("HFpt_GS", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_HFpt_FC = new TH1D("HFpt_FC", "", ptHFbinsize, ptHF_binedges);
  TH1D *h1_HFpt_Total = new TH1D("HFpt_Total", "", ptHFbinsize, ptHF_binedges);

  TH1D *h1_jetpt_GS = new TH1D("jetpt_GS", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_FC = new TH1D("jetpt_FC", "", ptbinsize, pt_binedges);
  TH1D *h1_jetpt_Total = new TH1D("jetpt_Total", "", ptbinsize, pt_binedges);

  TH1D *h1_HFpt = new TH1D("h1_HFpt", "", ptHFbinsize, ptHF_binedges);
  TH2D *h2_HFptjetpt = new TH2D("h2_HFptjetpt", "", ptHFbinsize, ptHF_binedges, customptbinsize, custompt_binedges);

  TH1D *h1_HF_measeta = new TH1D("HF_measeta", "", 12, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_HF_measpt = new TH1D("HF_measpT", "", 50, 0, 80);
  TH1D *h1_HF_measphi = new TH1D("HF_measphi", "", 20, -3.14, 3.14);

  TH1D *h1_Dtr_Eta = new TH1D("Dtr_Eta", "Dtr #eta", 50, etaMin - jetradius, etaMax + jetradius);
  TH1D *h1_dtr_phi = new TH1D("Dtr_phi", "Dtr #phi", 50, -3.14, 3.14);
  TH1D *h1_dtr_pT = new TH1D("Dtr_pT", "Dtr pT", 50, 0, 10);
  TH1D *h1_dtr_p = new TH1D("Dtr_p", "Dtr p", 50, 0, 150);
  TH1D *h1_keys = new TH1D("Keys", "Keys", 100, 0, 100);

  TH1D *h1_hfdtrs_e_diff = new TH1D("HFDtrsEDiff", "HFDtrsEDiff", 40, -100, 100);
  TH1D *h1_HFHadronMass = new TH1D("HFHadronMass", "HFHadronMass", 100, 60, 120);
  TH1D *h1_HF_jet_dR = new TH1D("HF_jet_dR", "", 24, 0, 4.);
  TH1D *h1_HF_jet_truedR = new TH1D("HF_jet_truedR", "", 24, 0, 4.);
  TH1D *h1_HFdtr1_mass = new TH1D("HFdtr1mass", "", 100, 1, 7);
  TH1D *h1_recoHFHadronMass = new TH1D("recoHFHadronMass", "recoHFHadronMass", 40, 0, 15);
  TH1D *h1_nsplittings = new TH1D("nSplittings", "nSplittings", 15, -0.5, 14.5);
  TH1D *h1_ptHF = new TH1D("ptHF", "pT_{HF}", 30, 0, 25);
  TH1D *h1_probNNghost = new TH1D("probNNghost", "probNNghost", 20, 0, 1);
  TH1D *h1_nJetDtrs_noghost = new TH1D("nJetDtrs_noghost", "nJetDtrs_noghost", 40, -0.5, 39.5);
  TH1D *h1_nJetDtrs_noghost_gluon = new TH1D("nJetDtrs_noghost_gluon", "nJetDtrs_noghost", 40, -0.5, 39.5);
  TH1F *h_nJetDaughters = new TH1F("h_nJetDaughters", "Number of jet daughters", 40, -0.5, 39.5);

  TH2D *HFmesonyphi_h = new TH2D("HFmesonyphi_h", ";#phi [rad]; y",
                                 100, -1 * TMath::Pi(), TMath::Pi(), 50, 1, 5);
  TH2D *HFjetetaphi_h = new TH2D("truejetetaphi_h", ";#phi [rad]; #eta",
                                 100, -1 * TMath::Pi(), TMath::Pi(), 50, 1, 5);
  TH1D *HFjetpt_h = new TH1D("truejetpt_h", ";p_{T}^{jet,MC} [GeV]", 50, 0, 200);
  TH1D *zmass = new TH1D("zmass", ";M_{#mu#mu} [GeV]", 150, 0, 150);
  TH1D *truedphi_h = new TH1D("truedphi_h", ";#Delta#phi [rad]", 50, 0, 3.14159);
  TH1D *truexj_h = new TH1D("truexj_h", "x_{J}", 50, 0, 2);
  TH1D *Zpt_h = new TH1D("Zpt_h", "p_{T}^{Z} [GeV]", 50, 0, 200);
  TH1D *truedy_h = new TH1D("truedy_h", "#Deltay", 50, -3, 3);
  // TH1D* truedtrp_h = new TH1D("truedtrp_h",";p [GeV]",npbins,thispbins);
  // TH1D* truedtrpt_h = new TH1D("truedtrpt_h",";p_{T} [GeV]",npbins,thispbins);
  TH1D *truenconst_h = new TH1D("truenconst_h", ";N_{const}^{chg}", 40, -0.5, 39.5);

  // TClonesArray *arr = new TClonesArray("TLorentzVector");

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
  int NumJets = 0;
  int NumJets_zdR = 0;
  int NumJets_ktdR = 0;
  int NumD2KKPi = 0;

  cout << "Requested # of events" << NumEvts << endl;
  for (int ev = 0; ev < NumEvts; ev++)
  {
    DTree->GetEntry(ev);
    if (jet_pt < pTLow)
      continue;

    if (ev % 500000 == 0)
      cout << "Executing event " << ev << endl;

    TLorentzVector HFmeson, HFjet, K, pi0, pi, Phi;
    TLorentzVector meas_HFmeson, meas_HFjet, meas_pi, meas_pi0, meas_K, meas_Phi;

    HFjet.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
    pi0.SetPxPyPzE(pi0_px, pi0_py, pi0_pz, pi0_e);
    pi.SetPxPyPzE(pi_px, pi_py, pi_pz, pi_e);
    K.SetPxPyPzE(K_px, K_py, K_pz, K_e);
    HFmeson.SetPxPyPzE(HF_px, HF_py, HF_pz, HF_e);

    meas_HFjet.SetPxPyPzE(meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e);
    // meas_pi0.SetPxPyPzE(meas_pi0_px, meas_pi0_py, meas_pi0_pz, meas_pi0_e);
    // meas_K.SetPxPyPzE(meas_K_px, meas_K_py, meas_K_pz, meas_K_e);
    // meas_pi.SetPxPyPzE(meas_pi_px, meas_pi_py, meas_pi_pz, meas_pi_e);
    meas_HFmeson.SetPxPyPzE(meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e);

    if (jet_eta > etaMin && jet_eta < etaMax)
      h2_HFptjetpt->Fill(HFmeson.Pt(), HFjet.Pt());

    h2_jetpteta->Fill(HFjet.Pt(), HFjet.Eta());

    int treeNumber = DTree->GetTreeNumber();
    int treeEvts = DTree->GetTree()->GetEntries();
    // ptweight /= (ptweights[4] * signal_eff[4]);
    // cout<<ptweights[2]<<", "<<signal_eff[2]<<", "<<ptweight<<endl;

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
    double event_weight = 1.;
    event_weight *= ptweight;

    // bool pt_cond = jet_pt > pTLow;
    bool pt_cond = jet_pt > ptMin && jet_pt < ptMax;
    bool rap_cond = jet_rap > etaMin && jet_rap < etaMax;

    // if (jet_pt < 20)
    //   continue;
    if (!rap_cond)
      continue;
    if (!pt_cond)
      continue;
    // cout << WTA_dist << ", ";
    // if (WTA_cut && (WTA_dist > WTA_max))
    //   continue;
    if (SubtractGS && Hasccbar)
    {
      continue;
    }

    if (Hasccbar)
    {
      h1_HFpt_GS->Fill(HFmeson.Pt(), event_weight);
      h1_jetpt_GS->Fill(HFjet.Pt(), event_weight);
    }
    else
    {
      h1_HFpt_FC->Fill(HFmeson.Pt(), event_weight);
      h1_jetpt_FC->Fill(HFjet.Pt(), event_weight);
    }

    h1_HFpt_Total->Fill(HFmeson.Pt(), event_weight);
    h1_jetpt_Total->Fill(HFjet.Pt(), event_weight);

    event_counter++;
    // if (HFmeson.Pt() < 2)
    //   continue;

    // cout<<eventNumber<<": "<<jet_pt <<" -- "<< meas_jet_pt<<endl;
    // if(HFmeson.M() < 5.279) continue;
    // if(kts->size() < 1) cout<<"filled with 0 kts";
    NumD2KKPi++;

    h1_jet_pt->Fill(jet_pt, event_weight);
    h1_jet_eta->Fill(jet_eta, event_weight);
    h1_jet_rap->Fill(jet_rap, event_weight);

    h1_meas_jet_pt->Fill(meas_jet_pt);
    h1_meas_jet_eta->Fill(meas_jet_eta);
    h1_meas_jet_rap->Fill(meas_jet_rap);

    h1_HFpt->Fill(HFmeson.Pt());
    h1_HF_rap->Fill(HFmeson.Rapidity());
    h1_HF_pt->Fill(HFmeson.Pt());
    h1_HF_mass->Fill(HFmeson.M());

    // if (meas_HFjet.E() > 0 && hasRecoHF)
    // {
    //   double jet_dR = HFjet.DeltaR(meas_HFjet, true);
    //   h1_truthreco_jetdR->Fill(jet_dR);
    // }

    // h1_HFpt->Fill(HFmeson.Pt(), event_weight);
    // h1_HF_rap->Fill(HFmeson.Rapidity(), event_weight);
    // h1_HF_pt->Fill(HFmeson.Pt(), event_weight);
    // h1_HF_mass->Fill(HFmeson.M(), event_weight);

    h1_jet_ptbalance0->Fill(jet_pt / meas_jet_pt); //// Truth over Reco is the standard....
    h1_jet_ptbalance1->Fill(meas_jet_pt / jet_pt);

    h1_HFjet_ptbalance->Fill(jet_pt / HFmeson.Pt());

    TVector3 HF_jet = HFjet.Vect();
    TVector3 HF_meson = HFmeson.Vect();
    double frag_z = (HF_meson.Dot(HF_jet)) / (HF_jet.Mag2());
    double frag_jt = HF_meson.Cross(HF_jet).Mag() / HF_jet.Mag();
    float frag_r = HFmeson.DeltaR(HFjet, true);

    if (Hasccbar)
    {
      double frag_z_gluon = HFmeson.Vect().Dot(HFjet.Vect()) / (HFjet.Vect().Mag2());
      double frag_jt_gluon = HFmeson.Vect().Cross(HFjet.Vect()).Mag() / HFjet.Vect().Mag();
      double frag_r_gluon = HFmeson.DeltaR(HFjet, true);

      h1_frag_z_gluon->Fill(frag_z_gluon);
      h1_frag_jt_gluon->Fill(frag_jt_gluon);
      h1_frag_r_gluon->Fill(frag_r_gluon);

      h2_zjt_gluon->Fill(frag_z_gluon, frag_jt_gluon);
      h2_zr_gluon->Fill(frag_z_gluon, frag_r_gluon);
      h2_jtr_gluon->Fill(frag_jt_gluon, frag_r_gluon);

      h3_ptzjt_gluon->Fill(frag_z_gluon, frag_jt_gluon, jet_pt);
      h3_ptzr_gluon->Fill(frag_z_gluon, frag_r_gluon, jet_pt);
      h3_ptjtr_gluon->Fill(frag_jt_gluon, frag_r_gluon, jet_pt);
    }
    else
    {
      h1_frag_z_charm->Fill(frag_z);
      h1_frag_jt_charm->Fill(frag_jt);
      h1_frag_r_charm->Fill(frag_r);

      h2_frag_z_jetpt_charm->Fill(frag_z, HFjet.Pt());

      h2_ptz_charm->Fill(frag_z, HFjet.Pt());
      h2_ptjt_charm->Fill(frag_jt, HFjet.Pt());
      h2_ptr_charm->Fill(frag_r, HFjet.Pt());
    }

    // h1_z->Fill(truth_z);
    // h1_jt->Fill(truth_jt);
    // h1_r->Fill(truth_r);

    h1_z->Fill(frag_z);
    h1_jt->Fill(frag_jt);
    h1_r->Fill(frag_r);

    h1_meas_z->Fill(meas_z);
    h1_meas_jt->Fill(meas_jt);
    h1_meas_r->Fill(meas_r);

    h1_ratio_z0->Fill(truth_z / meas_z);
    h1_ratio_z1->Fill(meas_z / truth_z);
    h1_ratio_jt0->Fill(truth_jt / meas_jt);
    h1_ratio_jt1->Fill(meas_jt / truth_jt);
    h1_ratio_r0->Fill(truth_r / meas_r);
    h1_ratio_r1->Fill(meas_r / truth_r);

    // cout << frag_z << ", " << HFjet.Pt();
    h2_frag_z_jetpt->Fill(frag_z, HFjet.Pt());

    if (Hasccbar)
    {
      // h2_frag_z_jetpt_gluon->Fill(HFmeson.Pt() / HFjet.Pt(), HFjet.Pt());
      h2_jetpteta_gluon->Fill(HFjet.Pt(), HFjet.Eta());
      h2_jetptp_gluon->Fill(HFjet.Pt(), HFjet.P());

      h2_ptz_gluon->Fill(truth_z, jet_pt);
      h2_ptjt_gluon->Fill(truth_jt, jet_pt);
      h2_ptr_gluon->Fill(truth_r, jet_pt);
    }

    h2_jetpteta->Fill(HFjet.Pt(), HFjet.Eta());
    h2_jetptp->Fill(HFjet.Pt(), HFjet.P());

    // h2_ptz->Fill(truth_z, jet_pt);
    // h2_ptjt->Fill(truth_jt, jet_pt);
    // h2_ptr->Fill(truth_r, jet_pt);

    h2_ptz->Fill(frag_z, jet_pt);
    h2_ptjt->Fill(frag_jt, jet_pt);
    h2_ptr->Fill(frag_r, jet_pt);

    h3_ptzjt->Fill(truth_z, truth_jt, jet_pt);
    h3_ptzr->Fill(truth_z, truth_r, jet_pt);
    h3_ptjtr->Fill(truth_jt, truth_r, jet_pt);

    h2_ptz_50_100->Fill(truth_z, jet_pt);
    h2_ptjt_50_100->Fill(truth_jt, jet_pt);
    h2_ptr_50_100->Fill(truth_r, jet_pt);

    h3_ptzjt_50_100->Fill(truth_z, truth_jt, jet_pt);
    h3_ptzr_50_100->Fill(truth_z, truth_r, jet_pt);
    h3_ptjtr_50_100->Fill(truth_jt, truth_r, jet_pt);

    h2_zjt->Fill(truth_z, truth_jt);
    h2_zr->Fill(truth_z, truth_r);
    h2_jtr->Fill(truth_jt, truth_r);

    h2_meas_zjt->Fill(meas_z, meas_jt);
    h2_meas_zr->Fill(meas_z, meas_r);
    h2_meas_jtr->Fill(meas_jt, meas_r);
  }

  cout << event_counter << " events processed" << endl;

  TH1D *h1_GS_frac = (TH1D *)h1_HFpt_GS->Clone("h1_GS_frac");
  h1_GS_frac->Divide(h1_GS_frac, h1_HFpt_Total, 1, 1, "B");

  TH1D *h1_FC_frac = (TH1D *)h1_HFpt_FC->Clone("h1_FC_frac");
  h1_FC_frac->Divide(h1_FC_frac, h1_HFpt_Total, 1, 1, "B");

  SetRecoStyle(h1_GS_frac);  // Blue
  SetTruthStyle(h1_FC_frac); // Green

  TH1D *h1_jetpt_GS_frac = (TH1D *)h1_jetpt_GS->Clone("h1_jetpt_GS_frac");
  h1_jetpt_GS_frac->Divide(h1_jetpt_GS_frac, h1_jetpt_Total, 1, 1, "B");

  TH1D *h1_jetpt_FC_frac = (TH1D *)h1_jetpt_FC->Clone("h1_jetpt_FC_frac");
  h1_jetpt_FC_frac->Divide(h1_jetpt_FC_frac, h1_jetpt_Total, 1, 1, "B");

  SetRecoStyle(h1_jetpt_GS_frac);
  SetTruthStyle(h1_jetpt_FC_frac);

  h2_jetpteta_gluon_ratio->Divide(h2_jetpteta_gluon, h2_jetpteta);
  h2_jetptp_gluon_ratio->Divide(h2_jetptp_gluon, h2_jetptp);
  h2_ptz_gluon_ratio->Divide(h2_ptz_gluon, h2_ptz);
  h2_ptjt_gluon_ratio->Divide(h2_ptjt_gluon, h2_ptjt);
  h2_ptr_gluon_ratio->Divide(h2_ptr_gluon, h2_ptr);

  TH2D *h2_zjt_ptbinned[ptbinsize - 1];
  TH2D *h2_zr_ptbinned[ptbinsize - 1];
  TH2D *h2_jtr_ptbinned[ptbinsize - 1];
  for (int j = 1; j < ptbinsize; j++)
  {

    h3_ptzjt->GetZaxis()->SetRange(j + 1, j + 1);
    h2_zjt_ptbinned[j - 1] = (TH2D *)h3_ptzjt->Project3D("yx");
    h2_zjt_ptbinned[j - 1]->SetName(Form("zjt_truth_pt%d", j));
    NormalizeHist(h2_zjt_ptbinned[j - 1]);

    h3_ptzr->GetZaxis()->SetRange(j + 1, j + 1);
    h2_zr_ptbinned[j - 1] = (TH2D *)h3_ptzr->Project3D("yx");
    h2_zr_ptbinned[j - 1]->SetName(Form("zr_truth_pt%d", j));
    NormalizeHist(h2_zr_ptbinned[j - 1]);

    h3_ptjtr->GetZaxis()->SetRange(j + 1, j + 1);
    h2_jtr_ptbinned[j - 1] = (TH2D *)h3_ptjtr->Project3D("yx");
    h2_jtr_ptbinned[j - 1]->SetName(Form("jtr_truth_pt%d", j));
    NormalizeHist(h2_jtr_ptbinned[j - 1]);
  }
  h3_ptzjt->GetZaxis()->SetRange(1, ptbinsize + 1);
  h3_ptzr->GetZaxis()->SetRange(1, ptbinsize + 1);
  h3_ptjtr->GetZaxis()->SetRange(1, ptbinsize + 1);

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
  // TString OutputFileBase	= outbase+outinfo;
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

  h2_zjt->GetYaxis()->SetRangeUser(0, 12);
  h2_zjt->GetXaxis()->SetRangeUser(0, 1.05);
  h2_zjt->SetStats(0);
  h2_zjt->SetXTitle("z");
  h2_zjt->SetYTitle("j_{T}");
  h2_zjt->Draw("COLZ");

  // h2_lundplane->SetStats(0);
  // h2_lundplane->SetXTitle("ln(1/#theta)");
  // h2_lundplane->SetYTitle("ln(k_{T})");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  //  gPad->SetLogz();
  Tl.DrawLatex(.58, 0.8, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);

  h2_zr->GetYaxis()->SetRangeUser(0, 1.0);
  h2_zr->GetXaxis()->SetRangeUser(0, 1.05);
  h2_zr->SetStats(0);
  h2_zr->SetXTitle("z");
  h2_zr->SetYTitle("r");
  // h2_thetaErad->Setmaximum(.01);
  // h2_thetaErad->SetMinimum(0.00001);
  //  gPad->SetLogz();
  h2_zr->Draw("COLZ");
  h2_zr->SetLineColor(1);
  h2_zr->SetLineStyle(9);

  //  if (flavor != 0)
  //    f1_theta_Erad->Draw("SAME");
  //  f1_kt_Erad->Draw("SAME");

  Tl.DrawLatex(.5, 0.8, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  //  Tl.DrawLatex(.2, 0.72, Form("k_{T}>%.1f GeV", LambdaQCD));
  Tl.DrawLatex(.6, 0.64, Form("%.1f<#eta<%.1f", etaMin, etaMax));
  ccan[ican]->cd(3);

  h2_jtr->SetStats(0);
  h2_jtr->SetXTitle("j_{T}");
  h2_jtr->SetYTitle("r");
  // h2_ktdR->SetMaximum(.01);
  // h2_ktdR->SetMinimum(0.00001);
  //  gPad->SetLogz();
  h2_jtr->Draw("COLZ");

  //  ccan[ican]->cd(4);
  //  h2_zdR->SetStats(0);
  //  h2_zdR->SetXTitle("ln(R/#DeltaR)");
  //  h2_zdR->SetYTitle("ln(1/z)");
  //  // h2_zdR->SetMaximum(.01);
  //  // h2_zdR->SetMinimum(0.00001);
  //  //  gPad->SetLogz();
  //  h2_zdR->Draw("COLZ");

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

  NormalizeHist(h1_z);
  NormalizeHist(h1_jt);
  NormalizeHist(h1_r);

  NormalizeHist(h1_meas_z);
  NormalizeHist(h1_meas_jt);
  NormalizeHist(h1_meas_r);

  SetTruthStyle(h1_z);
  SetTruthStyle(h1_jt);
  SetTruthStyle(h1_r);

  SetDataStyle(h1_meas_z);
  SetDataStyle(h1_meas_jt);
  SetDataStyle(h1_meas_r);

  NormalizeHist(h1_frag_z_gluon);

  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  ccan[ican]->cd(1);
  h1_z->SetStats(0);
  h1_z->SetXTitle("z");

  h1_z->Draw("P E SAME");
  h1_z->SetMinimum(0.);
  h1_z->SetMaximum(2.5);
  // Tl.DrawLatex(.5, 0.75, Form("%.1f<p_{T,jet}<%.1f GeV", ptMin, ptMax));
  // Tl.DrawLatex(0.7, 0.8, "No cuts");
  h1_meas_z->SetStats(0);
  h1_meas_z->Draw("P E SAME");
  h1_meas_z->SetMaximum(2.5);

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  gPad->SetLogy();
  h1_jt->SetStats(0);
  h1_jt->SetXTitle("j_{T}");
  h1_jt->SetMinimum(0.1);
  h1_jt->SetMaximum(3);
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_jt->Draw("P E SAME");
  h1_meas_jt->Draw("P E SAME");
  ccan[ican]->cd(3);

  gPad->SetLogy();
  h1_r->SetStats(0);
  h1_r->SetXTitle("r");
  h1_r->Draw("P E SAME");
  h1_r->SetMinimum(0.9);
  h1_r->SetMaximum(10);

  h1_meas_r->Draw("P E SAME");

  //  ccan[ican]->cd(4);
  //  h1_theta->SetStats(0);
  //  h1_theta->SetXTitle("ln(1/#theta)");
  //  h1_theta->SetMinimum(0.);
  //  // h2_lundplane->Sethflocimum(.01);
  //  // h2_lundplane->SetMinimum(0.00001);
  //  h1_theta->Draw("P E SAME");
  //  h1_meas_theta->Draw("P E SAME");

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
  SetTruthStyle(h1_z);
  SetDataStyle(h1_frag_z_gluon);

  h1_z->SetStats(0);
  h1_z->SetXTitle("z");
  h1_z->Draw("PE SAME");
  h1_frag_z_gluon->Draw("PE SAME");
  h1_z->SetMaximum(3.5);

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  SetTruthStyle(h1_jt);
  gPad->SetLogy();
  h1_jt->SetStats(0);
  h1_jt->SetXTitle("jt");
  h1_jt->Draw("P E SAME");
  h1_jt->SetMaximum(3);

  // SetTruthStyle(h1_tr_frag_jt);
  // h1_tr_frag_jt->Draw("P E SAME");

  ccan[ican]->cd(3);
  gPad->SetLogy();
  SetTruthStyle(h1_r);
  h1_r->SetStats(0);
  h1_r->SetXTitle("r");
  h1_r->Draw("P E SAME");
  h1_r->SetMaximum(10);

  // SetTruthStyle(h1_tr_frag_r);
  // h1_tr_frag_r->Draw("P E SAME");

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
  //////////////////////////////////// I N C L U S I V E /////////////////////////////////////
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

  auto legend_zpt = new TLegend(0.52, 0.62, 0.9, 0.89);
  legend_zpt->SetTextSize(0.028);
  legend_zpt->SetBorderSize(0);
  legend_zpt->SetFillStyle(0);
  legend_zpt->SetFillColor(3);
  legend_zpt->SetHeader("PYTHIA LHCb Unofficial (inclusive)", "C");

  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptz->ProjectionX(Form("z_truth_pt%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("z");
    h1_temp->SetYTitle(" 1/N dN/dz ");

    legend_zpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(3.05);
  }

  legend_zpt->Draw("SAME");

  ccan[ican]->cd(2);
  gPad->SetLogy();

  auto legend_jtpt = new TLegend(0.52, 0.62, 0.9, 0.89);
  legend_jtpt->SetTextSize(0.028);
  legend_jtpt->SetBorderSize(0);
  legend_jtpt->SetFillStyle(0);
  legend_jtpt->SetFillColor(3);
  legend_jtpt->SetHeader("PYTHIA LHCb Unofficial (inclusive)", "C");
  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptjt->ProjectionX(Form("jt_truth_pt%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("j_{T}");
    h1_temp->SetYTitle(" 1/N dN / dj_{T} ");

    legend_jtpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(3.05);
  }

  legend_jtpt->Draw("SAME");

  ccan[ican]->cd(3);
  gPad->SetLogy();

  auto legend_rpt = new TLegend(0.52, 0.62, 0.9, 0.89);
  legend_rpt->SetTextSize(0.028);
  legend_rpt->SetBorderSize(0);
  legend_rpt->SetFillStyle(0);
  legend_rpt->SetFillColor(3);
  legend_rpt->SetHeader("PYTHIA LHCb Unofficial (inclusive)", "C");
  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptr->ProjectionX(Form("r_truth_pt%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("r");
    h1_temp->SetYTitle(" 1/N dN/dr ");

    legend_rpt->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(15.5);
  }

  legend_rpt->Draw("SAME");

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

  //////////////////////////////////// C H A R M ////////////////////////////////////

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

  auto legend_zpt_charm = new TLegend(0.5, 0.62, 0.89, 0.89);
  legend_zpt_charm->SetTextSize(0.028);
  legend_zpt_charm->SetBorderSize(0);
  legend_zpt_charm->SetFillStyle(0);
  legend_zpt_charm->SetFillColor(3);
  legend_zpt_charm->SetHeader("PYTHIA LHCb Unofficial (charm)", "C");

  // h2_ptz_charm
  // h2_ptz_charm

  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptz_charm->ProjectionX(Form("z_truth_pt_charm%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("z");
    h1_temp->SetYTitle(" 1/N dN/dz ");

    legend_zpt_charm->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(3.5);
  }

  legend_zpt_charm->Draw("SAME");

  ccan[ican]->cd(2);
  gPad->SetLogy();

  auto legend_jtpt_charm = new TLegend(0.50, 0.62, 0.89, 0.89);
  legend_jtpt_charm->SetTextSize(0.028);
  legend_jtpt_charm->SetBorderSize(0);
  legend_jtpt_charm->SetFillStyle(0);
  legend_jtpt_charm->SetFillColor(3);
  legend_jtpt_charm->SetHeader("PYTHIA LHCb Unofficial (charm)", "C");
  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptjt_charm->ProjectionX(Form("jt_truth_pt_charm%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("j_{T}");
    h1_temp->SetYTitle(" 1/N dN / dj_{T} ");

    legend_jtpt_charm->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(4.0);
  }

  legend_jtpt_charm->Draw("SAME");

  ccan[ican]->cd(3);
  gPad->SetLogy();

  auto legend_rpt_charm = new TLegend(0.5, 0.62, 0.89, 0.89);
  legend_rpt_charm->SetTextSize(0.028);
  legend_rpt_charm->SetBorderSize(0);
  legend_rpt_charm->SetFillStyle(0);
  legend_rpt_charm->SetFillColor(3);
  legend_rpt_charm->SetHeader("PYTHIA LHCb Unofficial (charm)", "C");
  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptr_charm->ProjectionX(Form("r_truth_pt_charm%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("r");
    h1_temp->SetYTitle(" 1/N dN/dr ");

    legend_rpt_charm->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(20.5);
  }

  legend_rpt_charm->Draw("SAME");

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

  //////////////////////////////////////// G L U O N S ////////////////////////////////////////
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

  auto legend_zpt_gluon = new TLegend(0.5, 0.62, 0.89, 0.89);
  legend_zpt_gluon->SetTextSize(0.028);
  legend_zpt_gluon->SetBorderSize(0);
  legend_zpt_gluon->SetFillStyle(0);
  legend_zpt_gluon->SetFillColor(3);
  legend_zpt_gluon->SetHeader("PYTHIA LHCb Unofficial (g-splitting)", "C");

  // h2_ptz_charm
  // h2_ptz_gluon

  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptz_gluon->ProjectionX(Form("z_truth_pt_gluon%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("z");
    h1_temp->SetYTitle(" 1/N dN/dz ");

    legend_zpt_gluon->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(3.5);
  }

  legend_zpt_gluon->Draw("SAME");

  ccan[ican]->cd(2);
  gPad->SetLogy();

  auto legend_jtpt_gluon = new TLegend(0.50, 0.62, 0.89, 0.89);
  legend_jtpt_gluon->SetTextSize(0.028);
  legend_jtpt_gluon->SetBorderSize(0);
  legend_jtpt_gluon->SetFillStyle(0);
  legend_jtpt_gluon->SetFillColor(3);
  legend_jtpt_gluon->SetHeader("PYTHIA LHCb Unofficial (g-splitting)", "C");
  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptjt_gluon->ProjectionX(Form("jt_truth_pt_gluon%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("j_{T}");
    h1_temp->SetYTitle(" 1/N dN / dj_{T} ");

    legend_jtpt_gluon->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(4.0);
  }

  legend_jtpt_gluon->Draw("SAME");

  ccan[ican]->cd(3);
  gPad->SetLogy();

  auto legend_rpt_gluon = new TLegend(0.5, 0.62, 0.89, 0.89);
  legend_rpt_gluon->SetTextSize(0.028);
  legend_rpt_gluon->SetBorderSize(0);
  legend_rpt_gluon->SetFillStyle(0);
  legend_rpt_gluon->SetFillColor(3);
  legend_rpt_gluon->SetHeader("PYTHIA LHCb Unofficial (g-splitting)", "C");
  for (int i = 1; i < ptbinsize; i++)
  {
    TH1D *h1_temp = (TH1D *)h2_ptr_gluon->ProjectionX(Form("r_truth_pt_gluon%d", i), i + 1, i + 1);

    NormalizeHist(h1_temp);
    h1_temp->SetStats(0);
    h1_temp->SetMarkerStyle(i + 20);
    h1_temp->SetMarkerColor(i + 1);
    h1_temp->SetLineColor(i + 1);

    h1_temp->Draw("P E SAME");
    h1_temp->Draw("HIST SAME");
    h1_temp->SetXTitle("r");
    h1_temp->SetYTitle(" 1/N dN/dr ");

    legend_rpt_gluon->AddEntry(h1_temp, Form(" %.1f < p_{T}^{jet} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));

    // h1_temp->SetMinimum(0.);
    h1_temp->SetMaximum(20.5);
  }

  legend_rpt_gluon->Draw("SAME");

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
  SetDataStyle(h1_jet_pt);
  h1_jet_pt->SetStats(0);
  h1_jet_pt->SetXTitle("pT(jet)");
  h1_jet_pt->Draw("P E SAME");
  h1_meas_jet_pt->Draw("P E SAME");

  ccan[ican]->cd(2);
  // h2_thetaErad->Scale(1./NumJets);
  SetDataStyle(h1_jet_eta);
  h1_jet_eta->SetStats(0);
  h1_jet_eta->SetXTitle("#eta(jet)");
  h1_jet_eta->Draw("P E SAME");
  h1_meas_jet_eta->Draw("P E SAME");

  ccan[ican]->cd(3);
  // h2_thetaErad->Scale(1./NumJets);
  SetDataStyle(h1_jet_rap);
  h1_jet_rap->SetStats(0);
  h1_jet_rap->SetXTitle("#eta(jet)");
  h1_jet_rap->Draw("P E SAME");
  h1_meas_jet_rap->Draw("P E SAME");

  //  ccan[ican]->cd(4);
  //  // h1_nsplittings->Draw("P E SAME");
  //  h1_nJetDtrs_noghost->SetStats(0);
  //  h1_nJetDtrs_noghost_gluon->SetStats(0);
  //  SetTruthStyle(h1_nJetDtrs_noghost);
  //  SetDataStyle(h1_nJetDtrs_noghost_gluon);
  //  NormalizeHist(h1_nJetDtrs_noghost);
  //  NormalizeHist(h1_nJetDtrs_noghost_gluon);
  //  h1_nJetDtrs_noghost_gluon->Draw("P E SAME");
  //  h1_nJetDtrs_noghost->Draw("P E SAME");

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

  SetDataStyle(h1_HF_pt);
  h1_HF_pt->SetStats(0);
  h1_HF_pt->SetXTitle("pT(HF)");
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
  SetDataStyle(h1_HF_rap);
  h1_HF_rap->SetStats(0);
  h1_HF_rap->SetXTitle("y(HF)");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_HF_rap->Draw("P E SAME");

  ccan[ican]->cd(3);
  SetDataStyle(h1_HF_mass);
  h1_HF_mass->SetStats(0);
  // h1_dphi_HF_jet->SetXTitle("#Delta#Phi");
  // h2_lundplane->Sethflocimum(.01);
  // h2_lundplane->SetMinimum(0.00001);
  h1_HF_mass->Draw("P E SAME");

  // ccan[ican]->cd(4);
  // h1_FC_frac->Draw("PE1SAME");
  // h1_GS_frac->Draw("PE1SAME");

  // h1_FC_frac->SetMinimum(0.);
  // h1_FC_frac->SetMaximum(1.05);

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
  //  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.06);
  //  gPad->SetRightMargin(0.15);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h1_FC_frac->SetStats(0);
  h1_GS_frac->SetStats(0);
  h1_FC_frac->SetMarkerSize(0.8);
  h1_GS_frac->SetMarkerSize(0.5);
  h1_FC_frac->Draw("PE1SAME");
  h1_GS_frac->Draw("PE1SAME");

  h1_FC_frac->SetMinimum(0.);
  h1_FC_frac->SetMaximum(1.05);
  h1_FC_frac->SetYTitle("Fraction");
  h1_FC_frac->SetXTitle("p_{T}^{HF}");

  auto legend_fc = new TLegend(0.45, 0.35, 0.75, 0.65);
  legend_fc->SetTextSize(0.04);
  legend_fc->SetBorderSize(0);
  legend_fc->SetFillStyle(0);
  legend_fc->SetFillColor(3);
  legend_fc->SetHeader("PYTHIA LHCb Unofficial", "C");
  legend_fc->AddEntry(h1_FC_frac, "charm fragmentation");
  legend_fc->AddEntry(h1_GS_frac, "gluon splitting");
  legend_fc->Draw("SAME");

  ccan[ican]->cd(2);
  h1_jetpt_FC_frac->SetStats(0);
  h1_jetpt_GS_frac->SetStats(0);
  h1_jetpt_GS_frac->SetMarkerSize(0.5);
  //  h1_jetpt_FC_frac->Draw("PE1SAME");
  h1_jetpt_GS_frac->Draw("PE1SAME");

  //  h1_jetpt_FC_frac->SetMinimum(0.);
  h1_jetpt_GS_frac->SetMaximum(1.05);
  h1_jetpt_GS_frac->SetXTitle("p_{T}^{Jet}");
  h1_jetpt_GS_frac->SetYTitle("Fraction of gluon splitting");
  h1_jetpt_GS_frac->GetXaxis()->SetLabelSize(0.03);
  h1_jetpt_GS_frac->GetYaxis()->SetLabelSize(0.03);

  auto legend_gs = new TLegend(0.45, 0.6, 0.75, 0.9);
  legend_gs->SetTextSize(0.05);
  legend_gs->SetBorderSize(0);
  legend_gs->SetFillStyle(0);
  legend_gs->SetFillColor(3);
  legend_gs->SetHeader("PYTHIA LHCb Unofficial", "C");
  legend_gs->Draw("SAME");

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
  /// "crystalball" parameters: [alpha], [N], [Sigma], [mean]
  TF1 *fitFunc = new TF1("fitFunc", "crystalball", 0.0, 2.0);
  fitFunc->SetParameters(1.0, 1.0, 0.5, 1.5, 2.0);

  SetTruthStyle(h1_ratio_z0);
  SetRecoStyle(h1_ratio_z1);

  h1_ratio_z0->Fit(fitFunc, "RQ");

  h1_ratio_z0->SetStats(0);
  h1_ratio_z0->SetXTitle("z balance");
  h1_ratio_z0->Draw("P E SAME");
  fitFunc->Draw("P E SAME");
  h1_ratio_z1->SetStats(0);
  h1_ratio_z1->SetXTitle("z balance");
  h1_ratio_z1->Draw("P E SAME");

  auto legend_zbalance = new TLegend(0.2, 0.6, 0.4, 0.9);
  legend_zbalance->SetTextSize(0.04);
  legend_zbalance->SetBorderSize(0);
  legend_zbalance->SetFillStyle(0);
  legend_zbalance->SetFillColor(3);
  legend_zbalance->AddEntry(h1_ratio_z0, "z_{True}/z_{Reco}");
  legend_zbalance->AddEntry(h1_ratio_z1, "z_{Reco}/z_{Truth}");
  legend_zbalance->Draw("SAME");

  ccan[ican]->cd(2);
  SetTruthStyle(h1_ratio_jt0);
  SetRecoStyle(h1_ratio_jt1);
  // h1_ratio_jt0->SetStats(0);
  // h1_ratio_jt0->SetXTitle("jt balance");
  // h1_ratio_jt0->Draw("P E SAME");
  h1_ratio_jt1->SetStats(0);
  h1_ratio_jt1->SetXTitle(" jt balance");
  h1_ratio_jt1->Draw("P E SAME");

  auto legend_jtbalance = new TLegend(0.6, 0.6, 0.9, 0.9);
  legend_jtbalance->SetTextSize(0.04);
  legend_jtbalance->SetBorderSize(0);
  legend_jtbalance->SetFillStyle(0);
  legend_jtbalance->SetFillColor(3);
  // legend_jtbalance->AddEntry(h1_ratio_jt0, "j_{T; Truth}/j_{T; Reco}");
  legend_jtbalance->AddEntry(h1_ratio_jt1, "j_{T; Reco}/j_{T; Truth}");
  legend_jtbalance->Draw("SAME");

  ccan[ican]->cd(3);
  SetTruthStyle(h1_ratio_r0);
  SetRecoStyle(h1_ratio_r1);
  h1_ratio_r0->SetStats(0);
  h1_ratio_r0->SetXTitle(" r balance");
  h1_ratio_r0->Draw("P E SAME");
  h1_ratio_r1->SetStats(0);
  h1_ratio_r1->SetXTitle(" r balance");
  h1_ratio_r1->Draw("P E SAME");

  auto legend_rbalance = new TLegend(0.7, 0.6, 0.9, 0.9);
  legend_rbalance->SetTextSize(0.04);
  legend_rbalance->SetBorderSize(0);
  legend_rbalance->SetFillStyle(0);
  legend_rbalance->SetFillColor(3);
  legend_rbalance->AddEntry(h1_ratio_r0, "r_{Truth}/r_{Reco}");
  legend_rbalance->AddEntry(h1_ratio_r1, "r_{Reco}/r_{Truth}");
  legend_rbalance->Draw("SAME");

  ccan[ican]->cd(4);
  SetTruthStyle(h1_jet_ptbalance0);
  SetRecoStyle(h1_jet_ptbalance1);
  h1_jet_ptbalance0->SetStats(0);
  h1_jet_ptbalance0->SetXTitle(" pt balance");
  h1_jet_ptbalance0->Draw("P E SAME");
  h1_jet_ptbalance1->SetStats(0);
  h1_jet_ptbalance1->SetXTitle(" pt balance");
  h1_jet_ptbalance1->Draw("P E SAME");

  auto legend_ptbalance = new TLegend(0.6, 0.6, 0.9, 0.9);
  legend_ptbalance->SetTextSize(0.04);
  legend_ptbalance->SetBorderSize(0);
  legend_ptbalance->SetFillStyle(0);
  legend_ptbalance->SetFillColor(3);
  legend_ptbalance->AddEntry(h1_jet_ptbalance0, "p_{T; Truth}/p_{T; Reco}");
  legend_ptbalance->AddEntry(h1_jet_ptbalance1, "p_{T; Reco}/p_{T; Truth}");
  legend_ptbalance->Draw("SAME");

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
  // ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  // ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  // gPad->SetRightMargin(0.15);
  // ccan[ican]->cd();
  // ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
  // ccan[ican]->cd(1);
  // gPad->SetLogy();
  // h1_pi_pt->SetStats(0);
  // h1_pi_pt->SetXTitle("p_{T} [GeV]");

  // SetRecoStyle(h1_pi_pt);
  // SetTruthStyle(h1_pi0_pt);
  // SetDataStyle(h1_K_pt);
  // h1_pi_pt->Draw("P E SAME");
  // h1_pi0_pt->Draw("P E SAME");
  // h1_K_pt->Draw("P E SAME");

  // ccan[ican]->cd(2);
  // // gPad->SetLogy();
  // h1_pi_eta->SetStats(0);
  // h1_pi_eta->SetXTitle("p_{T} [GeV]");

  // SetRecoStyle(h1_pi_eta);
  // SetTruthStyle(h1_pi0_eta);
  // SetDataStyle(h1_K_eta);
  // h1_pi_eta->Draw("P E SAME");
  // h1_pi0_eta->Draw("P E SAME");
  // h1_K_eta->Draw("P E SAME");

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

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }
  //
  f.Write();
  f.Close();

  cout << "Num of True B jets = " << NumD2KKPi << endl;
}
