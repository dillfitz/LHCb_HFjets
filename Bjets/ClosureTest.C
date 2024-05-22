#include <TCanvas.h>
#include <vector>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
using namespace std;

void ClosureTest(int NumEvts = -1,
                 int dataset1 = 91590,
                 int dataset2 = 91591,
                 bool chargedJetCut = false,
                 bool WTA_cut = false,
                 double minimum_dR = 0.1,
                 int NumIters_kt = 1,
                 int NumIters_z = 1,
                 bool SubtractGS = false)
{

  TString string_reco, string_data, string_truth, string_eff, string_unfold, extension;
  TString str_followHard, str_ghost, str_charged, str_Mag1, str_Mag2, str_flavor, str_GS("");
  TString loc_hists("$LUND/Bjets/hists/");
  TString loc_plots("$LUND/Bjets/plots/");
  TString str_DTF = "";
  TString str_PID = "";
  int JetMeth = (dataset1 / 1000) % 10;
  int flavor = (dataset1 / 100) % 10;
  int ptRange = (dataset1 / 10) % 10;
  int Mag1 = (dataset1 / 1) % 10;
  int Mag2 = (dataset2 / 1) % 10;

  // int NumIters = 1;
  // int RegIDS = 5;
  str_GS = SubtractGS ? "_GSsub" : "";
  str_DTF = DTF_cut ? "_DTF" : "";
  str_PID = PID_cut ? "_PID" : "";
  str_WTA = WTA_cut ? "_WTA" : "";

  str_Mag1 = Mag1 == 0 ? "_MD" : Mag1 == 1 ? "_MU"
                                           : "";
  str_Mag2 = Mag2 == 0 ? "_MD" : Mag2 == 1 ? "_MU"
                                           : "";
  str_flavor = flavor == 1 ? "_udsg" : flavor == 4 ? "_c"
                                   : flavor == 5   ? "_b"
                                                   : "";

  if (flavor == 1)
    str_followHard = "_hard";
  else
    str_followHard = "_HF";

  str_ghost = ghostCut ? Form("_ghost_%.1f", ghostProb) : "";
  str_charged = chargedJetCut ? "_charge" : "";
  str_eta = Form("_eta_%.1f%.1f", etaMin, etaMax);
  str_pt = Form("_ptj_%d%d", int(ptMin), int(ptMax));
  str_Nevts = Form("_ev_%d", NumEvts);

  string_reco = loc_hists + TString("reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset1);
  string_truth = loc_hists + TString("truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag1 + str_flavor + str_GS + str_WTA + Form("_%d", dataset1);
  string_eff = loc_hists + TString("efficiency_truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag2 + str_flavor + str_GS + str_WTA + Form("_%d", dataset2);
  string_unfold = loc_hists + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag2 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset2);
  // string_reco = loc + "hists/reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_data = loc + "hists/data_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_truth = loc + "hists/truth_ev_-1_ptj_20150_eta_2.54.0_hard_udsg_93139.root";
  // string_eff = loc + "hists/eff_truth_ev_-1_ptj_20150_eta_2.54.0_hard_udsg_93139.root";
  // string_unfold = loc + "hists/unfold_reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";

  extension = TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_iters_%d_%d", NumIters_kt, NumIters_z) + Form("_%d", dataset1) + Form("_%d", dataset2);

  /////////////////////   Get Files /////////////////////////////////

  TFile *file_reco = new TFile(string_reco + TString(".root"), "READ");
  // TFile *file_data = new TFile(string_data+ TString(".root"));
  TFile *file_truth = new TFile(string_truth + TString(".root"), "READ");
  TFile *file_eff = new TFile(string_eff + TString(".root"), "READ");
  TFile *file_unfold = new TFile(string_unfold + TString(".root"), "READ");

  TFile *file_write = new TFile(loc_hists + extension + ".root", "RECREATE");

  cout << string_reco + TString(".root") << endl;
  cout << string_truth + TString(".root") << endl;
  cout << string_eff + TString(".root") << endl;
  cout << string_unfold + TString(".root") << endl;

  /////////////////////   Get histograms /////////////////////////////////

  TH1D *h1_jetpt_ref = (TH1D *)file_unfold->Get("jetpt");
  TH1D *h1_jetpt_truth_ref = (TH1D *)file_unfold->Get("jetpt_truth;1");

  TH1D *h1_jetpt_reco = (TH1D *)file_reco->Get("Jet_pT");
  TH1D *h1_HFpt_reco = (TH1D *)file_reco->Get("h1_HFpt");
  TH2D *h2_HFptjetpt_reco = (TH2D *)file_reco->Get("h2_HFptjetpt");
  TH2D *h2_jetpteta_reco = (TH2D *)file_reco->Get("h2_jetpteta");
  TH1D *hNumJets = (TH1D *)file_reco->Get("hNumJets");
  TH1D *h1_jetpt_final = (TH1D *)h1_jetpt_reco->Clone("jetpt_final");
  TH1D *h1_HFpt_final = (TH1D *)h1_HFpt_reco->Clone("HFpt_final");
  TH2D *h2_HFptjetpt_final = (TH2D *)h2_HFptjetpt_reco->Clone("HFptjetpt_final");
  TH2D *h2_jetpteta_final = (TH2D *)h2_jetpteta_reco->Clone("jetpteta_final");

  /////////////////////   Get Truth histograms /////////////////////////////////
  TH1D *h1_jetpt_truth = (TH1D *)file_truth->Get("Jet_pT");
  TH1D *h1_HFpt_truth = (TH1D *)file_truth->Get("h1_HFpt");
  TH2D *h2_HFptjetpt_truth = (TH2D *)file_truth->Get("h2_HFptjetpt");
  TH2D *h2_jetpteta_truth = (TH2D *)file_truth->Get("h2_jetpteta");
  TH1D *h1_kt_truth = (TH1D *)file_truth->Get("kt");
  TH1D *h1_dR_truth = (TH1D *)file_truth->Get("dR");
  TVectorD *NumJets_truth = (TVectorD *)file_truth->Get("NumJets");

  /////////////////////   Get Purity Hists /////////////////////////////////

  TH1D *h1_purity_jetpt = (TH1D *)file_unfold->Get("purity_jetpt");
  TH1D *h1_efficiency_jetpt = (TH1D *)file_unfold->Get("efficiency_jetpt");
  TH1D *h1_efficiency_recoJet_jetpt = (TH1D *)file_unfold->Get("efficiency_recoJet_jetpt");
  TH1D *h1_efficiency_vecHFpt = (TH1D *)file_unfold->Get("efficiency_vecHFpt");
  TH1D *h1_purity_vecHFpt = (TH1D *)file_unfold->Get("purity_vecHFpt");
  // TH3D * h3_purity_ptktdR = (TH3D*) file_unfold->Get("purity_ptHFktdR");
  // TH3D * h3_purity_ptzdR = (TH3D*) file_unfold->Get("purity_ptHFzdR");

  /////////////////////   Get Response Matrices /////////////////////////////////

  // RooUnfoldResponse * response_jetpt = (RooUnfoldResponse*)file_eff->Get("response_jetpt");
  RooUnfoldResponse *response_jetpt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_jetpt");
  TH2 *h2_response_jetpt = (TH2 *)response_jetpt->Hresponse();

  response_jetpt->UseOverflow();

  int ntoys = 5;

  // unfold_ktdR_bayes.SetVerbose (1);
  // unfold_ktdR_bayes.SetNToys(ntoys);
  // unfold_ktdR_bayes.IncludeSystematics(0);
  //
  // unfold_dR_bayes.SetNToys(ntoys);
  // unfold_dR_bayes.IncludeSystematics(0);

  // RooUnfoldErrors* errors= new RooUnfoldErrors(ntoys,&unfold_ktdR_bayes,h2_ktdR_truth);
  // auto hToyErr=errors->RMSResiduals();
  // auto hUnfErr=errors->UnfoldingError();

  // RooUnfoldErrors* errors= new RooUnfoldErrors(ntoys,&unfold_dR_bayes,h1_dR_truth);
  // auto hToyErr=errors->RMSResiduals();
  // auto hUnfErr=errors->UnfoldingError();

  cout << "Unfold successful" << endl;

  // h1_jetpt_final->Multiply(h1_purity_jetpt);
  RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters_z);
  // RooUnfoldIds unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters_kt);
  h1_jetpt_final = (TH1D *)unfold_jetpt.Hreco();
  // h1_jetpt_final->Divide(h1_efficiency_recoJet_jetpt);

  // h1_jetpt_final->Divide(h1_efficiency_jetpt);

  TH1D *h1_correct_jetpt = (TH1D *)h1_jetpt_final->Clone("h1_correct_jetpt");
  // TH1D * h1_correct_jetpt = (TH1D*) h1_jetpt_reco->Clone("h1_correct_jetpt");
  h1_correct_jetpt->Divide(h1_jetpt_truth);

  // h1_jetpt_final->Divide(h1_correct_jetpt);
  // h1_efficiency_recoJet_jetpt->Multiply(h1_correct_jetpt);

  vector<TH1D *> vec_jetpt, vec_efficiency_jetpt, vec_purity_jetpt;
  vector<RooUnfoldResponse *> vec_response_jetpt;
  for (int i = 0; i < vecptHFbinsize; i++)
  {
    int loc = i;
    cout << "Reading histograms: " << endl;
    TH1D *h1_jetpt_tmp = (TH1D *)file_reco->Get(Form("jetpt%d", loc));
    TH1D *h1_efficiency_jetpt_tmp = (TH1D *)file_unfold->Get(Form("efficiency_jetpt%d", loc));
    TH1D *h1_purity_jetpt_tmp = (TH1D *)file_unfold->Get(Form("purity_jetpt%d", loc));
    RooUnfoldResponse *response_jetpt_tmp = (RooUnfoldResponse *)file_unfold->Get(Form("response_jetpt%d", loc));
    cout << "Pushback: " << endl;
    if (response_jetpt_tmp != NULL)
      cout << "found response" << endl;

    cout << h1_jetpt_tmp->Integral() << endl;
    cout << h1_purity_jetpt_tmp->Integral() << endl;
    cout << h1_efficiency_jetpt_tmp->Integral() << endl;
    vec_jetpt.push_back(h1_jetpt_tmp);
    vec_efficiency_jetpt.push_back(h1_efficiency_jetpt_tmp);
    vec_purity_jetpt.push_back(h1_purity_jetpt_tmp);
    vec_response_jetpt.push_back(response_jetpt_tmp);
  }

  TH1D *h1_jetpt_vecfinal;
  for (int i = 0; i < vecptHFbinsize; i++)
  {
    int loc = i;
    double HF_eff = h1_efficiency_vecHFpt->GetBinContent(loc + 1);
    double HF_pur = h1_purity_vecHFpt->GetBinContent(loc + 1);
    // vec_jetpt[loc]->Multiply(vec_purity_jetpt[loc]);
    cout << "Scaling by pur" << endl;
    vec_jetpt[loc]->Scale(HF_pur);
    cout << "Unfolding:" << endl;

    RooUnfoldBayes vec_unfold_jetpt(vec_response_jetpt[loc], vec_jetpt[loc], NumIters_z);

    vec_jetpt[loc] = (TH1D *)vec_unfold_jetpt.Hreco();
    vec_jetpt[loc]->Scale(1. / HF_eff);
    // vec_jetpt[loc]->Divide(vec_efficiency_jetpt[loc]);
    if (i == 0)
      h1_jetpt_vecfinal = vec_jetpt[loc];
    else
      h1_jetpt_vecfinal->Add(vec_jetpt[loc]);
  }
  /////////////////////   Normalize histograms /////////////////////////////////

  int binlow_jet = h1_jetpt_truth->FindBin(ptMin);
  int binhigh_jet = h1_jetpt_truth->FindBin(ptMax);

  double Njets_truth = h1_jetpt_truth->Integral(binlow_jet, binhigh_jet);
  double Njets_final = h1_jetpt_final->Integral(binlow_jet, binhigh_jet);
  double Njets_vecfinal = h1_jetpt_vecfinal->Integral(binlow_jet, binhigh_jet);

  cout << "Njets vecfinal = " << Njets_vecfinal << endl;
  // NormalizeHist(h2_ptthetaErad_final);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create ktdR histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  vector<RooUnfoldResponse *> vec_response_ptktdR;
  vector<TH3D *> vec_h3_ptktdR, vec_h3_efficiency_ptktdR, vec_h3_purity_ptktdR;
  for (int i = 0; i < vecptHFbinsize; i++)
  {
    int loc = i;
    TH3D *h3_ptktdR_tmp = (TH3D *)file_reco->Get(Form("h3_ptktdR%d", loc));
    vec_h3_ptktdR.push_back(h3_ptktdR_tmp);

    RooUnfoldResponse *response_ptktdR_temp = (RooUnfoldResponse *)file_unfold->Get(Form("h3_response_ptktdR%d", loc));
    vec_response_ptktdR.push_back(response_ptktdR_temp);

    TH3D *h3_efficiency_ptktdR_tmp = (TH3D *)file_unfold->Get(Form("h3_efficiency_ptktdR%d", loc));
    TH3D *h3_purity_ptktdR_tmp = (TH3D *)file_unfold->Get(Form("h3_purity_ptktdR%d", loc));

    vec_h3_efficiency_ptktdR.push_back(h3_efficiency_ptktdR_tmp);
    vec_h3_purity_ptktdR.push_back(h3_purity_ptktdR_tmp);
  }

  TH2D *h2_ktdR_truth = (TH2D *)file_truth->Get("kT_dR");
  TH3D *h3_ptktdR_truth = (TH3D *)file_truth->Get("ptktdR");
  TH3D *h3_ptktdR = (TH3D *)file_reco->Get("ptktdR");
  TH3D *h3_ptktdR_final = (TH3D *)h3_ptktdR->Clone("ptktdR_final");
  TH3D *h3_eff_ptktdR = (TH3D *)file_unfold->Get("efficiency_ptktdR");
  TH3D *h3_purity_ptktdR = (TH3D *)file_unfold->Get("purity_ptktdR");
  RooUnfoldResponse *response_ptktdR = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptktdR");
  //
  TH3D *h3_ptktdR_vecfinal;
  for (int i = 0; i < vecptHFbinsize; i++)
  {
    int loc = i;

    double HF_eff = h1_efficiency_vecHFpt->GetBinContent(loc + 1);
    double HF_pur = h1_purity_vecHFpt->GetBinContent(loc + 1);
    vec_h3_ptktdR[loc]->Scale(HF_pur);
    cout << vecptHF_binedges[i] << ", " << vecptHF_binedges[i + 1] << endl;
    vec_h3_ptktdR[loc]->Multiply(vec_h3_purity_ptktdR[loc]);
    RooUnfoldBayes unfold_ptktdR(vec_response_ptktdR[loc], vec_h3_ptktdR[loc], NumIters_kt);
    // vec_h3_ptktdR[loc] = (TH3D *)unfold_ptktdR.Hreco();
    vec_h3_ptktdR[loc]->Divide(vec_h3_efficiency_ptktdR[loc]);

    cout << HF_eff << ", " << HF_pur << endl;

    vec_h3_ptktdR[loc]->Scale(1. / HF_eff);
    if (i == 0)
      h3_ptktdR_vecfinal = vec_h3_ptktdR[loc];
    else
      h3_ptktdR_vecfinal->Add(vec_h3_ptktdR[loc]);
  }
  h3_ptktdR_final->Multiply(h3_ptktdR_final, h3_purity_ptktdR);
  RooUnfoldBayes unfold_ptktdR(response_ptktdR, h3_ptktdR_final, NumIters_kt);
  // RooUnfoldIds unfold_ptktdR(response_ptktdR, h3_ptktdR_final, NumIters_kt);
  h3_ptktdR_final = (TH3D *)unfold_ptktdR.Hreco();
  h3_ptktdR_final->Divide(h3_ptktdR_final, h3_eff_ptktdR);
  //
  int binlow = h3_ptktdR->GetZaxis()->FindBin(ptMin + 0.1);
  int binhigh = h3_ptktdR->GetZaxis()->FindBin(ptMax - 0.1);
  int binlowdR = h3_ptktdR->GetXaxis()->FindBin(0.);
  int binhighdR = h3_ptktdR->GetXaxis()->FindBin(2.1);
  int binlowkt = h3_ptktdR->GetYaxis()->FindBin(-1.9);
  int binhighkt = h3_ptktdR->GetYaxis()->FindBin(1.49);
  //

  h3_ptktdR_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptktdR_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptktdR_vecfinal->GetZaxis()->SetRangeUser(ptMin, ptMax);

  h3_ptktdR->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptktdR_final = (TH2D *)h3_ptktdR_final->Project3D("kt_final_yx");
  TH2D *h2_ptktdR_vecfinal = (TH2D *)h3_ptktdR_vecfinal->Project3D("kt_vecfinal_yx");
  TH2D *h2_ptktdR = (TH2D *)h3_ptktdR->Project3D("kt_yx");
  TH2D *h2_ptktdR_truth = (TH2D *)h3_ptktdR_truth->Project3D("kt_truth_yx");
  //
  h2_ptktdR_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_final->GetXaxis()->SetRange(binlowdR, binhighdR);
  h2_ptktdR_vecfinal->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_vecfinal->GetXaxis()->SetRange(binlowdR, binhighdR);
  h2_ptktdR_truth->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_truth->GetXaxis()->SetRange(binlowdR, binhighdR);

  TH2D *h2_final_ptktdR = GetJetPtCorrectedHist(h3_ptktdR_final, h1_efficiency_recoJet_jetpt);
  h2_final_ptktdR->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_final_ptktdR->GetXaxis()->SetRange(binlowdR, binhighdR);
  //
  // NormalizeHist(h2_ptktdR_final);
  // NormalizeHist(h2_ptktdR_vecfinal);
  // NormalizeHist(h2_ptktdR_truth);
  h2_final_ptktdR->Scale(1. / Njets_final, "width");
  h2_ptktdR_final->Scale(1. / Njets_final, "width");
  h2_ptktdR_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h2_ptktdR_truth->Scale(1. / Njets_truth, "width");

  // h2_ptktdR_vecfinal->Scale(1. / Njets_vecfinal, "width");
  // h2_ptktdR_final->Scale(1. / 0.98);

  TH2D *h2_ptktdR_ratio = (TH2D *)h2_ptktdR->Clone("h2_ptktdR_ratio");
  TH2D *h2_ptktdR_ratio_final = (TH2D *)h2_ptktdR->Clone("h2_ptktdR_ratio_final");
  TH2D *h2_ptktdR_pull_final = (TH2D *)h2_ptktdR->Clone("h2_ptktdR_pull_final");

  TH2D *h2_ptktdR_ratio_vecfinal = (TH2D *)h2_ptktdR->Clone("h2_ptktdR_ratio_vecfinal");
  TH2D *h2_ptktdR_pull_vecfinal = (TH2D *)h2_ptktdR->Clone("h2_ptktdR_pull_vecfinal");

  // TH2D *h2_ptktdR_ratio_final = new TH2D("h2_ptktdR_ratio_final", "", dRbinsizefinal, dR_binedgesfinal, ktbinsizefinal, kt_binedgesfinal);
  // TH2D *h2_ptktdR_pull_final = new TH2D("h2_ptktdR_pull_final", "", dRbinsizefinal, dR_binedgesfinal, ktbinsizefinal, kt_binedgesfinal);

  TH2D *h2_ptktdR_pull = (TH2D *)h2_ktdR_truth->Clone("ptktdR_pull");

  TH1D *h1_ptktdR_pulldist = new TH1D("ptktdR_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptktdR_pulldist_final = new TH1D("ptktdR_pulldist_final", "", 20, -4.5, 4.5);
  TH1D *h1_ptktdR_pulldist_vecfinal = new TH1D("ptktdR_pulldist_vecfinal", "", 20, -4.5, 4.5);

  // h2_ptktdR_ratio->Divide(h2_ptktdR, h2_ktdR_truth);
  // h2_ptktdR_ratio_final->Divide(h2_ptktdR_final, h2_ktdR_truth);

  h2_ptktdR_ratio->Divide(h2_ptktdR, h2_ptktdR_truth);
  h2_ptktdR_ratio_final->Divide(h2_ptktdR_final, h2_ptktdR_truth);
  h2_ptktdR_ratio_vecfinal->Divide(h2_ptktdR_vecfinal, h2_ptktdR_truth);

  h2_ptktdR_ratio_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_ratio_final->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptktdR_pull_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_pull_final->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptktdR_ratio_vecfinal->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_ratio_vecfinal->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptktdR_pull_vecfinal->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_pull_vecfinal->GetXaxis()->SetRange(binlowdR, binhighdR);

  // for (int i = 0; i < dRbinsizefinal; i++)
  // {
  //   for (int j = 1; j < ktbinsizefinal + 1; j++)
  //   {
  //     double num = h2_ptktdR_final->GetBinContent(i + 2, j + 1);
  //     // double num = h2_final_ptktdR->GetBinContent(i + 2, j + 1);
  //     double denom = h2_ptktdR_truth->GetBinContent(i + 2, j + 1);
  //     double num_err = h2_ptktdR_final->GetBinError(i + 2, j + 1);
  //     // double num_err = h2_final_ptktdR->GetBinError(i + 2, j + 1);
  //     double denom_err = h2_ptktdR_truth->GetBinError(i + 2, j + 1);
  //     double tot = num / denom;
  //     double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
  //     if (denom <= 0)
  //       continue;
  //     h2_ptktdR_ratio_final->SetBinContent(i + 1, j + 1 - 1, tot);
  //     h2_ptktdR_ratio_final->SetBinError(i + 1, j + 1 - 1, tot_err);
  //   }
  // }

  GetPullsRatio(h2_ptktdR_ratio, h2_ptktdR_pull, h1_ptktdR_pulldist);
  GetPullsRatio(h2_ptktdR_ratio_final, h2_ptktdR_pull_final, h1_ptktdR_pulldist_final);
  GetPullsRatio(h2_ptktdR_ratio_vecfinal, h2_ptktdR_pull_vecfinal, h1_ptktdR_pulldist_vecfinal);

  double ptktdR_pullperf1 = GetPullPerformance(h2_ptktdR_pull, 1);
  double ptktdR_pullperf2 = GetPullPerformance(h2_ptktdR_pull, 2);

  double ptktdR_pullperf1_final = GetPullPerformance(h2_ptktdR_pull_final, 1);
  double ptktdR_pullperf2_final = GetPullPerformance(h2_ptktdR_pull_final, 2);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create zdR histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  TH2D *h2_zdR = (TH2D *)file_reco->Get("z_dR");
  TH2D *h2_ptz = (TH2D *)file_reco->Get("ptz");

  TH2D *h2_zdR_truth = (TH2D *)file_truth->Get("z_dR");
  TH3D *h3_ptzdR_truth = (TH3D *)file_truth->Get("ptzdR");
  TH3D *h3_ptzdR = (TH3D *)file_reco->Get("ptzdR");
  TH3D *h3_ptzdR_final = (TH3D *)h3_ptzdR->Clone("ptzdR_final");
  TH3D *h3_eff_ptzdR = (TH3D *)file_unfold->Get("efficiency_ptzdR");
  TH3D *h3_purity_ptzdR = (TH3D *)file_unfold->Get("purity_ptzdR");
  RooUnfoldResponse *response_ptzdR = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzdR");
  //
  h3_ptzdR_final->Multiply(h3_ptzdR_final, h3_purity_ptzdR);
  RooUnfoldBayes unfold_ptzdR(response_ptzdR, h3_ptzdR_final, NumIters_z);
  h3_ptzdR_final = (TH3D *)unfold_ptzdR.Hreco();
  h3_ptzdR_final->Divide(h3_ptzdR_final, h3_eff_ptzdR);
  //
  int binlowz = h3_ptzdR->GetYaxis()->FindBin(0.8);
  int binhighz = h3_ptzdR->GetYaxis()->FindBin(3.9);
  //
  h3_ptzdR_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzdR_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzdR_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzdR->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptzdR_final = (TH2D *)h3_ptzdR_final->Project3D("z_final_yx");
  TH2D *h2_ptzdR_truth = (TH2D *)h3_ptzdR_truth->Project3D("z_truth_yx");
  TH2D *h2_ptzdR = (TH2D *)h3_ptzdR->Project3D("z_yx");
  //
  h2_ptzdR_final->GetYaxis()->SetRange(binlowz, binhighz);
  h2_ptzdR_final->GetXaxis()->SetRange(binlowdR, binhighdR);
  h2_ptzdR_truth->GetYaxis()->SetRange(binlowz, binhighz);
  h2_ptzdR_truth->GetXaxis()->SetRange(binlowdR, binhighdR);
  //
  TH2D *h2_final_ptzdR = GetJetPtCorrectedHist(h3_ptzdR_final, h1_efficiency_recoJet_jetpt);
  h2_final_ptzdR->GetYaxis()->SetRange(binlowz, binhighz);
  h2_final_ptzdR->GetXaxis()->SetRange(binlowdR, binhighdR);

  // NormalizeHist(h2_ptzdR_final);
  // NormalizeHist(h2_final_ptzdR);
  // NormalizeHist(h2_ptzdR_truth);

  h2_final_ptzdR->Scale(1. / Njets_final, "width");
  h2_ptzdR_final->Scale(1. / Njets_final, "width");
  h2_ptzdR_truth->Scale(1. / Njets_truth, "width");

  //
  TH2D *h2_ptzdR_ratio = (TH2D *)h2_ptzdR->Clone("h2_ptzdR_ratio");
  TH2D *h2_ptzdR_ratio_final = (TH2D *)h2_ptzdR->Clone("h2_ptzdR_ratio_final");
  TH2D *h2_ptzdR_pull_final = (TH2D *)h2_ptzdR->Clone("h2_ptzdR_pull_final");

  // TH2D *h2_ptzdR_ratio_final = new TH2D("h2_ptzdR_ratio_final", "", dRbinsizefinal, dR_binedgesfinal, zbinsizefinal, z_binedgesfinal);
  // TH2D *h2_ptzdR_pull_final = new TH2D("h2_ptzdR_pull_final", "", dRbinsizefinal, dR_binedgesfinal, zbinsizefinal, z_binedgesfinal);

  TH2D *h2_ptzdR_pull = (TH2D *)h2_zdR_truth->Clone("ptzdR_pull");

  TH1D *h1_ptzdR_pulldist = new TH1D("ptzdR_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptzdR_pulldist_final = new TH1D("ptzdR_pulldist_final", "", 20, -4.5, 4.5);

  // h2_ptzdR_ratio->Divide(h2_ptzdR, h2_zdR_truth);
  // h2_ptzdR_ratio_final->Divide(h2_ptzdR_final, h2_zdR_truth);

  h2_ptzdR_ratio->Divide(h2_ptzdR, h2_ptzdR_truth);
  h2_ptzdR_ratio_final->Divide(h2_ptzdR_final, h2_ptzdR_truth);

  h2_ptzdR_ratio_final->GetYaxis()->SetRange(binlowz, binhighz);
  h2_ptzdR_ratio_final->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptzdR_pull_final->GetYaxis()->SetRange(binlowz, binhighz);
  h2_ptzdR_pull_final->GetXaxis()->SetRange(binlowdR, binhighdR);

  // for (int i = 0; i < dRbinsizefinal; i++)
  // {
  //   for (int j = 2; j < zbinsizefinal + 2; j++)
  //   {
  //     double num = h2_ptzdR_final->GetBinContent(i + 2, j + 1);
  //     // double num = h2_final_ptzdR->GetBinContent(i + 2, j + 1);
  //     double denom = h2_ptzdR_truth->GetBinContent(i + 2, j + 1);
  //     double num_err = h2_ptzdR_final->GetBinError(i + 2, j + 1);
  //     // double num_err = h2_final_ptzdR->GetBinError(i + 2, j + 1);
  //     double denom_err = h2_ptzdR_truth->GetBinError(i + 2, j + 1);
  //     double tot = num / denom;
  //     double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
  //     if (denom <= 0)
  //       continue;
  //     h2_ptzdR_ratio_final->SetBinContent(i + 1, j + 1 - 2, tot);
  //     h2_ptzdR_ratio_final->SetBinError(i + 1, j + 1 - 2, tot_err);
  //   }
  // }

  GetPullsRatio(h2_ptzdR_ratio, h2_ptzdR_pull, h1_ptzdR_pulldist);
  GetPullsRatio(h2_ptzdR_ratio_final, h2_ptzdR_pull_final, h1_ptzdR_pulldist_final);

  double ptzdR_pullperf1 = GetPullPerformance(h2_ptzdR_pull, 1);
  double ptzdR_pullperf2 = GetPullPerformance(h2_ptzdR_pull, 2);

  double ptzdR_pullperf1_final = GetPullPerformance(h2_ptzdR_pull_final, 1);
  double ptzdR_pullperf2_final = GetPullPerformance(h2_ptzdR_pull_final, 2);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create thetaErad histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  TH2D *h2_thetaErad = (TH2D *)file_reco->Get("Theta_Erad");

  TH3D *h3_ptthetaErad_truth = (TH3D *)file_truth->Get("ptthetaErad");
  TH3D *h3_ptthetaErad = (TH3D *)file_reco->Get("ptthetaErad");
  TH3D *h3_ptthetaErad_final = (TH3D *)h3_ptthetaErad->Clone("ptthetaErad_final");
  TH3D *h3_eff_ptthetaErad = (TH3D *)file_unfold->Get("efficiency_ptthetaErad");
  TH3D *h3_purity_ptthetaErad = (TH3D *)file_unfold->Get("purity_ptthetaErad");
  RooUnfoldResponse *response_ptthetaErad = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptthetaErad");
  //
  h3_ptthetaErad_final->Multiply(h3_ptthetaErad_final, h3_purity_ptthetaErad);
  RooUnfoldBayes unfold_ptthetaErad(response_ptthetaErad, h3_ptthetaErad_final, NumIters_z);
  h3_ptthetaErad_final = (TH3D *)unfold_ptthetaErad.Hreco();
  h3_ptthetaErad_final->Divide(h3_ptthetaErad_final, h3_eff_ptthetaErad);
  //
  int binlowerad = 2;
  int binhigherad = Eradbinsize - 1;

  int binlowtheta = h3_ptthetaErad->GetYaxis()->FindBin(2.51);
  int binhightheta = h3_ptthetaErad->GetYaxis()->FindBin(5.);

  //
  h3_ptthetaErad_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptthetaErad->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptthetaErad_final = (TH2D *)h3_ptthetaErad_final->Project3D("Erad_final_yx");
  TH2D *h2_ptthetaErad_truth = (TH2D *)h3_ptthetaErad_truth->Project3D("Erad_truth_yx");
  TH2D *h2_ptthetaErad = (TH2D *)h3_ptthetaErad->Project3D("Erad_yx");
  //
  h2_ptthetaErad_final->GetYaxis()->SetRange(binlowtheta, binhightheta);
  h2_ptthetaErad_final->GetXaxis()->SetRange(binlowerad, binhigherad);
  h2_ptthetaErad_truth->GetYaxis()->SetRange(binlowtheta, binhightheta);
  h2_ptthetaErad_truth->GetXaxis()->SetRange(binlowerad, binhigherad);

  //
  h2_ptthetaErad_final->Scale(1. / Njets_final, "width");
  h2_ptthetaErad_truth->Scale(1. / Njets_truth, "width");
  // NormalizeHist(h2_ptthetaErad_final);
  // NormalizeHist(h2_ptthetaErad_truth);
  //
  TH2D *h2_ptthetaErad_ratio = (TH2D *)h2_ptthetaErad->Clone("h2_ptthetaErad_ratio");
  TH2D *h2_ptthetaErad_ratio_final = (TH2D *)h2_ptthetaErad->Clone("h2_ptthetaErad_ratio_final");
  TH2D *h2_ptthetaErad_pull_final = (TH2D *)h2_ptthetaErad->Clone("h2_ptthetaErad_pull_final");

  // TH2D *h2_ptthetaErad_ratio_final = new TH2D("h2_ptthetaErad_ratio_final", "", Eradbinsizefinal, Erad_binedgesfinal, zbinsizefinal, z_binedgesfinal);
  // TH2D *h2_ptthetaErad_pull_final = new TH2D("h2_ptthetaErad_pull_final", "", Eradbinsizefinal, Erad_binedgesfinal, zbinsizefinal, z_binedgesfinal);

  TH2D *h2_ptthetaErad_pull = (TH2D *)h2_ptthetaErad_truth->Clone("ptthetaErad_pull");

  TH1D *h1_ptthetaErad_pulldist = new TH1D("ptthetaErad_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptthetaErad_pulldist_final = new TH1D("ptthetaErad_pulldist_final", "", 20, -4.5, 4.5);

  // h2_ptthetaErad_ratio->Divide(h2_ptthetaErad, h2_ptthetaErad_truth);
  // h2_ptthetaErad_ratio_final->Divide(h2_ptthetaErad_final, h2_ptthetaErad_truth);

  h2_ptthetaErad_ratio->Divide(h2_ptthetaErad, h2_ptthetaErad_truth);
  h2_ptthetaErad_ratio_final->Divide(h2_ptthetaErad_final, h2_ptthetaErad_truth);

  h2_ptthetaErad_ratio_final->GetYaxis()->SetRange(binlowtheta, binhightheta);
  h2_ptthetaErad_ratio_final->GetXaxis()->SetRange(binlowerad, binhigherad);

  h2_ptthetaErad_pull_final->GetYaxis()->SetRange(binlowtheta, binhightheta);
  h2_ptthetaErad_pull_final->GetXaxis()->SetRange(binlowerad, binhigherad);

  // for (int i = 1; i < Eradbinsizefinal + 1; i++)
  // {
  //   for (int j = 1; j < thetabinsizefinal + 1; j++)
  //   {
  //     double num = h2_ptthetaErad_final->GetBinContent(i + 1, j + 1);
  //     double denom = h2_ptthetaErad_truth->GetBinContent(i + 1, j + 1);
  //     double num_err = h2_ptthetaErad_final->GetBinError(i + 1, j + 1);
  //     double denom_err = h2_ptthetaErad_truth->GetBinError(i + 1, j + 1);
  //     double tot = num / denom;
  //     double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
  //     if (denom <= 0)
  //       continue;
  //     h2_ptthetaErad_ratio_final->SetBinContent(i + 1 - 1, j + 1 - 1, tot);
  //     h2_ptthetaErad_ratio_final->SetBinError(i + 1 - 1, j + 1 - 1, tot_err);
  //   }
  // }

  GetPullsRatio(h2_ptthetaErad_ratio, h2_ptthetaErad_pull, h1_ptthetaErad_pulldist);
  GetPullsRatio(h2_ptthetaErad_ratio_final, h2_ptthetaErad_pull_final, h1_ptthetaErad_pulldist_final);

  double ptthetaErad_pullperf1 = GetPullPerformance(h2_ptthetaErad_pull, 1);
  double ptthetaErad_pullperf2 = GetPullPerformance(h2_ptthetaErad_pull, 2);

  double ptthetaErad_pullperf1_final = GetPullPerformance(h2_ptthetaErad_pull_final, 1);
  double ptthetaErad_pullperf2_final = GetPullPerformance(h2_ptthetaErad_pull_final, 2);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create ptHFdR histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  TH3D *h3_ptdRptrad_truth = (TH3D *)file_truth->Get("ptdRptrad");
  TH3D *h3_ptdRptrad = (TH3D *)file_reco->Get("ptdRptrad");
  TH3D *h3_ptdRptrad_final = (TH3D *)h3_ptdRptrad->Clone("ptdRptrad_final");
  TH3D *h3_eff_ptdRptrad = (TH3D *)file_unfold->Get("efficiency_ptdRptrad");
  TH3D *h3_purity_ptdRptrad = (TH3D *)file_unfold->Get("purity_ptdRptrad");
  RooUnfoldResponse *response_ptdRptrad = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptdRptrad");
  //
  h3_ptdRptrad_final->Multiply(h3_ptdRptrad_final, h3_purity_ptdRptrad);
  RooUnfoldBayes unfold_ptdRptrad(response_ptdRptrad, h3_ptdRptrad_final, NumIters_z);
  h3_ptdRptrad_final = (TH3D *)unfold_ptdRptrad.Hreco();
  h3_ptdRptrad_final->Divide(h3_ptdRptrad_final, h3_eff_ptdRptrad);
  //
  int binlowpt = 3;
  int binhighpt = ptradbinsize - 1;

  // int binlowtheta = h3_ptdRptrad->GetYaxis()->FindBin(2.51);
  // int binhightheta = h3_ptdRptrad->GetYaxis()->FindBin(5.);

  //
  h3_ptdRptrad_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptdRptrad->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptdRptrad_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptdRptrad_final = (TH2D *)h3_ptdRptrad_final->Project3D("ptrad_final_yx");
  TH2D *h2_ptdRptrad_truth = (TH2D *)h3_ptdRptrad_truth->Project3D("ptrad_truth_yx");
  TH2D *h2_ptdRptrad = (TH2D *)h3_ptdRptrad->Project3D("ptrad_yx");
  //
  h2_ptdRptrad_final->GetYaxis()->SetRange(binlowdR, binhighdR);
  h2_ptdRptrad_final->GetXaxis()->SetRange(binlowpt, binhighpt);
  h2_ptdRptrad_truth->GetYaxis()->SetRange(binlowdR, binhighdR);
  h2_ptdRptrad_truth->GetXaxis()->SetRange(binlowpt, binhighpt);

  //
  h2_ptdRptrad_final->Scale(1. / Njets_final, "width");
  h2_ptdRptrad_truth->Scale(1. / Njets_truth, "width");
  // NormalizeHist(h2_ptdRptrad_final);
  // NormalizeHist(h2_ptdRptrad_truth);
  //
  TH2D *h2_ptdRptrad_ratio = (TH2D *)h2_ptdRptrad_truth->Clone("h2_ptdRptrad_ratio");
  TH2D *h2_ptdRptrad_ratio_final = (TH2D *)h2_ptdRptrad_truth->Clone("h2_ptdRptrad_ratio_final");
  TH2D *h2_ptdRptrad_pull_final = (TH2D *)h2_ptdRptrad_truth->Clone("h2_ptdRptrad_pull_final");

  // TH2D *h2_ptdRptrad_ratio_final = new TH2D("h2_ptdRptrad_ratio_final", "", ptradbinsizefinal, ptrad_binedgesfinal, dRbinsizefinal, dR_binedgesfinal);
  // TH2D *h2_ptdRptrad_pull_final = new TH2D("h2_ptdRptrad_pull_final", "", ptradbinsizefinal, ptrad_binedgesfinal, dRbinsizefinal, dR_binedgesfinal);

  TH2D *h2_ptdRptrad_pull = (TH2D *)h2_ptdRptrad_truth->Clone("ptdRptrad_pull");

  TH1D *h1_ptdRptrad_pulldist = new TH1D("ptdRptrad_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptdRptrad_pulldist_final = new TH1D("ptdRptrad_pulldist_final", "", 20, -4.5, 4.5);

  // h2_ptdRptrad_ratio->Divide(h2_ptdRptrad, h2_ptdRptrad_truth);
  // h2_ptdRptrad_ratio_final->Divide(h2_ptdRptrad_final, h2_ptdRptrad_truth);

  h2_ptdRptrad_ratio->Divide(h2_ptdRptrad, h2_ptdRptrad_truth);
  h2_ptdRptrad_ratio_final->Divide(h2_ptdRptrad_final, h2_ptdRptrad_truth);

  h2_ptdRptrad_ratio_final->GetYaxis()->SetRange(binlowdR, binhighdR);
  h2_ptdRptrad_ratio_final->GetXaxis()->SetRange(binlowpt, binhighpt);

  h2_ptdRptrad_pull_final->GetYaxis()->SetRange(binlowdR, binhighdR);
  h2_ptdRptrad_pull_final->GetXaxis()->SetRange(binlowpt, binhighpt);

  // for (int i = 1; i < Eradbinsizefinal + 1; i++)
  // {
  //   for (int j = 1; j < thetabinsizefinal + 1; j++)
  //   {
  //     double num = h2_ptdRptrad_final->GetBinContent(i + 1, j + 1);
  //     double denom = h2_ptdRptrad_truth->GetBinContent(i + 1, j + 1);
  //     double num_err = h2_ptdRptrad_final->GetBinError(i + 1, j + 1);
  //     double denom_err = h2_ptdRptrad_truth->GetBinError(i + 1, j + 1);
  //     double tot = num / denom;
  //     double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
  //     if (denom <= 0)
  //       continue;
  //     h2_ptdRptrad_ratio_final->SetBinContent(i + 1 - 1, j + 1 - 1, tot);
  //     h2_ptdRptrad_ratio_final->SetBinError(i + 1 - 1, j + 1 - 1, tot_err);
  //   }
  // }

  GetPullsRatio(h2_ptdRptrad_ratio, h2_ptdRptrad_pull, h1_ptdRptrad_pulldist);
  GetPullsRatio(h2_ptdRptrad_ratio_final, h2_ptdRptrad_pull_final, h1_ptdRptrad_pulldist_final);

  double ptdRptrad_pullperf1 = GetPullPerformance(h2_ptdRptrad_pull, 1);
  double ptdRptrad_pullperf2 = GetPullPerformance(h2_ptdRptrad_pull, 2);

  double ptdRptrad_pullperf1_final = GetPullPerformance(h2_ptdRptrad_pull_final, 1);
  double ptdRptrad_pullperf2_final = GetPullPerformance(h2_ptdRptrad_pull_final, 2);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create dRErad histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  TH2D *h2_dRErad = (TH2D *)file_reco->Get("dR_Erad");

  TH2D *h2_dRErad_truth = (TH2D *)file_truth->Get("dR_Erad");
  TH3D *h3_ptdRErad = (TH3D *)file_reco->Get("ptdRErad");
  TH3D *h3_ptdRErad_final = (TH3D *)h3_ptdRErad->Clone("ptdRErad_final");
  TH3D *h3_eff_ptdRErad = (TH3D *)file_unfold->Get("efficiency_ptdRErad");
  TH3D *h3_purity_ptdRErad = (TH3D *)file_unfold->Get("purity_ptdRErad");
  RooUnfoldResponse *response_ptdRErad = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptdRErad");
  //
  h3_ptdRErad_final->Multiply(h3_ptdRErad_final, h3_purity_ptdRErad);
  RooUnfoldBayes unfold_ptdRErad(response_ptdRErad, h3_ptdRErad_final, NumIters_z);
  h3_ptdRErad_final = (TH3D *)unfold_ptdRErad.Hreco();
  h3_ptdRErad_final->Divide(h3_ptdRErad_final, h3_eff_ptdRErad);

  //
  h3_ptdRErad_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptdRErad->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptdRErad_final = (TH2D *)h3_ptdRErad_final->Project3D("Erad_final_yx");
  TH2D *h2_ptdRErad = (TH2D *)h3_ptdRErad->Project3D("Erad_yx");
  //
  h2_ptdRErad_final->GetYaxis()->SetRange(binlowtheta, binhightheta);
  h2_ptdRErad_final->GetXaxis()->SetRange(binlowerad, binhigherad);
  h2_dRErad_truth->GetYaxis()->SetRange(binlowtheta, binhightheta);
  h2_dRErad_truth->GetXaxis()->SetRange(binlowerad, binhigherad);

  //

  NormalizeHist(h2_ptdRErad_final);
  NormalizeHist(h2_dRErad_truth);
  //
  TH2D *h2_ptdRErad_ratio = (TH2D *)h2_dRErad->Clone("ptdRErad_ratio");
  TH2D *h2_ptdRErad_ratio_final = new TH2D("h2_ptdRErad_ratio_final", "", dRbinsizefinal, dR_binedgesfinal, zbinsizefinal, z_binedgesfinal);

  TH2D *h2_ptdRErad_pull = (TH2D *)h2_dRErad->Clone("ptdRErad_pull");
  TH2D *h2_ptdRErad_pull_final = (TH2D *)h2_ptdRErad_ratio_final->Clone("ptdRErad_pull_final");

  TH1D *h1_ptdRErad_pulldist = new TH1D("ptdRErad_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptdRErad_pulldist_final = new TH1D("ptdRErad_pulldist_final", "", 20, -4.5, 4.5);

  for (int i = 1; i < Eradbinsizefinal + 1; i++)
  {
    for (int j = 0; j < dRbinsizefinal + 1; j++)
    {
      double num = h2_ptdRErad_final->GetBinContent(i + 1, j + 1);
      double denom = h2_dRErad_truth->GetBinContent(i + 1, j + 1);
      double num_err = h2_ptdRErad_final->GetBinError(i + 1, j + 1);
      double denom_err = h2_dRErad_truth->GetBinError(i + 1, j + 1);
      double tot = num / denom;
      double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
      if (denom <= 0)
        continue;
      h2_ptdRErad_ratio_final->SetBinContent(i + 1, j + 1 - 1, tot);
      h2_ptdRErad_ratio_final->SetBinError(i + 1, j + 1 - 1, tot_err);
    }
  }

  GetPullsRatio(h2_ptdRErad_ratio, h2_ptdRErad_pull, h1_ptdRErad_pulldist);
  GetPullsRatio(h2_ptdRErad_ratio_final, h2_ptdRErad_pull_final, h1_ptdRErad_pulldist_final);

  double ptdRErad_pullperf1 = GetPullPerformance(h2_ptdRErad_pull, 1);
  double ptdRErad_pullperf2 = GetPullPerformance(h2_ptdRErad_pull, 2);

  double ptdRErad_pullperf1_final = GetPullPerformance(h2_ptdRErad_pull_final, 1);
  double ptdRErad_pullperf2_final = GetPullPerformance(h2_ptdRErad_pull_final, 2);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create ktdR_SV histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  TH2D *h2_ktdR_SV_truth = (TH2D *)file_truth->Get("kT_dR_gluon");
  TH3D *h3_ptktdR_SV_truth = (TH3D *)file_truth->Get("ptktdR_gluon");
  TH3D *h3_ptktdR_SV = (TH3D *)file_reco->Get("ptktdR_SV");
  TH3D *h3_ptktdR_SV_final = (TH3D *)h3_ptktdR_SV->Clone("ptktdR_SV_final");
  TH3D *h3_eff_ptktdR_SV = (TH3D *)file_unfold->Get("efficiency_ptktdR_SV");
  TH3D *h3_purity_ptktdR_SV = (TH3D *)file_unfold->Get("purity_ptktdR_SV");
  RooUnfoldResponse *response_ptktdR_SV = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptktdR_SV");

  //
  h3_ptktdR_SV_final->Multiply(h3_ptktdR_SV_final, h3_purity_ptktdR_SV);
  RooUnfoldBayes unfold_ptktdR_SV(response_ptktdR_SV, h3_ptktdR_SV_final, NumIters_kt);
  // RooUnfoldBayes unfold_ptktdR_SV(response_ptktdR, h3_ptktdR_SV_final, NumIters_kt); // Does not work!

  h3_ptktdR_SV_final = (TH3D *)unfold_ptktdR_SV.Hreco();
  h3_ptktdR_SV_final->Divide(h3_ptktdR_SV_final, h3_eff_ptktdR_SV);
  //

  //

  h3_ptktdR_SV_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptktdR_SV_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptktdR_SV->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptktdR_SV_final = (TH2D *)h3_ptktdR_SV_final->Project3D("kt_final_yx");
  TH2D *h2_ptktdR_SV = (TH2D *)h3_ptktdR_SV->Project3D("kt_yx");
  //
  h2_ptktdR_SV_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptktdR_SV_final->GetXaxis()->SetRange(binlowdR, binhighdR);
  h2_ktdR_SV_truth->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ktdR_SV_truth->GetXaxis()->SetRange(binlowdR, binhighdR);
  //
  NormalizeHist(h2_ptktdR_SV_final);
  NormalizeHist(h2_ktdR_SV_truth);
  //
  // TH2D *h2_ptktdR_SV_ratio = (TH2D *)h2_ktdR_SV->Clone("ptktdR_SV_ratio");
  TH2D *h2_ptktdR_SV_ratio = new TH2D("h2_ptktdR_SV_ratio", "", dRbinsizefinal, dR_binedgesfinal, ktbinsizefinal, kt_binedgesfinal);
  TH2D *h2_ptktdR_SV_ratio_final = new TH2D("h2_ptktdR_SV_ratio_final", "", dRbinsizefinal, dR_binedgesfinal, ktbinsizefinal, kt_binedgesfinal);

  TH2D *h2_ptktdR_SV_pull = (TH2D *)h2_ktdR_SV_truth->Clone("ptktdR_SV_pull");
  TH2D *h2_ptktdR_SV_pull_final = (TH2D *)h2_ptktdR_SV_ratio_final->Clone("ptktdR_SV_pull_final");

  TH1D *h1_ptktdR_SV_pulldist = new TH1D("ptktdR_SV_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptktdR_SV_pulldist_final = new TH1D("ptktdR_SV_pulldist_final", "", 20, -4.5, 4.5);

  h2_ptktdR_SV_ratio->Divide(h2_ptktdR_SV, h2_ktdR_SV_truth);

  for (int i = 0; i < dRbinsizefinal; i++)
  {
    for (int j = 1; j < ktbinsizefinal + 1; j++)
    {
      double num = h2_ptktdR_SV_final->GetBinContent(i + 1, j + 1);
      double denom = h2_ktdR_SV_truth->GetBinContent(i + 1, j + 1);
      double num_err = h2_ptktdR_SV_final->GetBinError(i + 1, j + 1);
      double denom_err = h2_ktdR_SV_truth->GetBinError(i + 1, j + 1);
      double tot = num / denom;
      double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
      if (denom <= 0)
        continue;
      h2_ptktdR_SV_ratio_final->SetBinContent(i + 1, j + 1 - 1, tot);
      h2_ptktdR_SV_ratio_final->SetBinError(i + 1, j + 1 - 1, tot_err);
    }
  }

  GetPullsRatio(h2_ptktdR_SV_ratio, h2_ptktdR_SV_pull, h1_ptktdR_SV_pulldist);
  GetPullsRatio(h2_ptktdR_SV_ratio_final, h2_ptktdR_SV_pull_final, h1_ptktdR_SV_pulldist_final);

  double ptktdR_SV_pullperf1 = GetPullPerformance(h2_ptktdR_SV_pull, 1);
  double ptktdR_SV_pullperf2 = GetPullPerformance(h2_ptktdR_SV_pull, 2);

  double ptktdR_SV_pullperf1_final = GetPullPerformance(h2_ptktdR_SV_pull_final, 1);
  double ptktdR_SV_pullperf2_final = GetPullPerformance(h2_ptktdR_SV_pull_final, 2);

  /////////////////////   Create zdR histograms /////////////////////////////////

  /////////////////////////////////////////////////////////////////

  // TH3D* h3_thetaErad =(TH3D*) file_reco->Get("ptHFzdR");

  /////////////////////   Get Frag z /////////////////////////////////

  TH2D *h2_frag_z_jetpt_SV_truth = (TH2D *)file_truth->Get("frag_z_jetpt_gluon");
  TH2D *h2_frag_z_jetpt_SV_reco = (TH2D *)file_reco->Get("frag_z_jetpt_SV");
  TH2D *h2_frag_z_jetpt_SV_final = (TH2D *)h2_frag_z_jetpt_SV_reco->Clone("h2_frag_z_jetpt_SV_final");
  TH2D *h2_eff_frag_z_jetpt_SV = (TH2D *)file_unfold->Get("h2_SVTag_eff_z");
  TH2D *h2_pur_frag_z_jetpt_SV = (TH2D *)file_unfold->Get("h2_SVTag_pur_z");
  RooUnfoldResponse *response_fragz = (RooUnfoldResponse *)file_unfold->Get("Roo_response_fragz");

  // h2_frag_z_jetpt_SV_final->Multiply(h2_pur_frag_z_jetpt_SV);
  RooUnfoldBayes unfold_fragz(response_fragz, h2_frag_z_jetpt_SV_final, 3);
  h2_frag_z_jetpt_SV_final = (TH2D *)unfold_fragz.Hreco();
  // h2_frag_z_jetpt_SV_final->Divide(h2_eff_frag_z_jetpt_SV);
  /////////////////////   Get Efficiency Hists /////////////////////////////////

  // TH3D * h3_eff_ptktdR = (TH3D*) file_unfold->Get("efficiency_ptHFktdR");
  // TH3D * h3_eff_ptzdR = (TH3D*) file_unfold->Get("efficiency_ptHFzdR");

  /////////////////////   Create ratio hists /////////////////////////////////

  TH2D *h2_zdR_ratio = (TH2D *)h2_zdR->Clone("zdR_ratio");
  TH2D *h2_zdR_ratio_final = (TH2D *)h2_zdR->Clone("zdR_ratio_final");

  /////////////////////   Compute ratios and pulls /////////////////////////////////

  cout << h2_ptktdR_ratio_final->GetNbinsX() << " -- " << h2_ptktdR_ratio_final->GetNbinsY() << endl;

  GetPullsRatio(h2_ptdRErad_ratio_final, h2_ptdRErad_pull_final, h1_ptdRErad_pulldist_final);
  // h1_ktdR_pulldist->Fit("gaus");
  // h1_ktdR_purity_eff_pulldist->Fit("gaus");
  // h1_ktdR_ids_unfold_pulldist->Fit("gaus");
  // h1_ktdR_bayes_unfold_pulldist->Fit("gaus");
  // h1_ktdR_pulldist->Fit("gaus");
  // h1_ktdR_pull_finaldist->Fit("gaus");

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================ktdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptktdR_pullperf1 << " %"
       << " --- " << ptktdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptktdR_pullperf1_final << " %"
       << " --- " << ptktdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_z << " iterations:" << endl;
  cout << "=======================zdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzdR_pullperf1 << " %"
       << " --- " << ptzdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzdR_pullperf1_final << " %"
       << " --- " << ptzdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;

  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptktdR_ratio_final) << endl;
  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzdR_ratio_final) << endl;

  //---- paint setup...
  //
  int ican = -1, iframe = -1, itext = -1;
  TCanvas *ccan[1000];
  TH1F *frame[1000];
  TLatex *text[1000];
  TRatioPlot *rp[1000];
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
  gStyle->SetOptStat(0);
  // gStyle->SetPaperSize(TStyle::kUSLetter);
  // gStyle->SetPadBottomMargin(0.08);
  // gStyle->SetPadTopMargin(0.005);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetLabelSize(0.05, "X");
  gStyle->SetLabelSize(0.05, "Y");
  gStyle->SetTitleXSize(0.055);
  gStyle->SetTitleYSize(0.055);
  gStyle->SetTitleOffset(0.55, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetStatW(0.2);
  // gStyle->SetPalette(kBird);
  gStyle->SetPalette(kBird);
  gStyle->SetNumberContours(100);
  gStyle->SetPaintTextFormat("4.3g");
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
  rootfile = loc_hists + extension + TString(".root");
  plotfile = loc_plots + extension + TString(".ps");
  plotfilePDF = loc_plots + extension + TString(".pdf");
  plotfileO = plotfilePDF + TString("(");
  plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

  // Begin plotting

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // gPad->SetLogy();
  SetTruthStyle(h1_jetpt_truth);
  SetRecoStyle(h1_jetpt_reco);
  SetDataStyle(h1_jetpt_final);
  h1_jetpt_truth->Draw("P E SAME");
  h1_jetpt_final->Draw("P E SAME");
  h1_jetpt_reco->Draw("P E SAME");

  h1_jetpt_vecfinal->SetMarkerColor(kGreen);
  h1_jetpt_vecfinal->SetMarkerStyle(33);
  h1_jetpt_vecfinal->Draw("P E SAME");

  h1_jetpt_truth->SetMinimum(h1_jetpt_truth->GetMinimum() * 0.7);
  h1_jetpt_truth->SetMaximum(h1_jetpt_truth->GetMaximum() * 1.3);

  ccan[ican]->cd(2);
  // gPad->SetLogy();
  SetTruthStyle(h1_HFpt_truth);
  SetRecoStyle(h1_HFpt_reco);
  SetDataStyle(h1_HFpt_final);
  h1_HFpt_truth->Draw("P E SAME");
  h1_HFpt_final->Draw("P E SAME");
  h1_HFpt_reco->Draw("P E SAME");

  h1_HFpt_truth->SetMinimum(h1_HFpt_truth->GetMinimum() * 0.7);
  h1_HFpt_truth->SetMaximum(h1_HFpt_truth->GetMaximum() * 1.3);

  ccan[ican]->cd(3);
  SetRecoStyle(h1_efficiency_jetpt);
  h1_purity_jetpt->SetLineColor(kRed);
  h1_purity_jetpt->SetMarkerColor(kRed);
  h1_purity_jetpt->SetMarkerStyle(kFullSquare);
  h1_efficiency_jetpt->Draw("P E SAME");
  h1_purity_jetpt->Draw("P E SAME");

  h1_efficiency_jetpt->SetMinimum(0.);
  h1_efficiency_jetpt->SetMaximum(1.);

  ccan[ican]->cd(4);
  h1_correct_jetpt->Draw();
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
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h2_jetpteta_final->Draw("COLZ");
  ccan[ican]->cd(2);
  h2_jetpteta_truth->Draw("COLZ");

  ccan[ican]->cd(3);
  TH2D *h2_ratio_jetpteta = (TH2D *)h2_jetpteta_final->Clone("h2_ratio_jetpteta");
  h2_ratio_jetpteta->Divide(h2_jetpteta_truth);
  h2_ratio_jetpteta->Draw("COLZ");

  ccan[ican]->cd(4);

  // TH1D* jetx_final15 = (TH1D*) h2_jetpteta_final->ProjectionX("jet_x_reco15", 1, 1);
  // TH1D* jetx_truth15 = (TH1D*) h2_jetpteta_truth->ProjectionX("jet_x_tr15", 1, 1);
  // jetx_final15->SetLineColor(kBlue);
  // jetx_truth15->SetLineColor(kGreen);
  // jetx_final15->Draw("HIST SAME");
  // jetx_truth15->Draw("HIST SAME");

  TH1D *jetx_final = (TH1D *)h2_jetpteta_final->ProjectionX("jet_x_reco", 2, 5);
  TH1D *jetx_truth = (TH1D *)h2_jetpteta_truth->ProjectionX("jet_x_tr", 2, 5);
  jetx_final->SetLineColor(kBlue);
  jetx_truth->SetLineColor(kGreen);
  jetx_final->Draw("HIST SAME");
  jetx_truth->Draw("HIST SAME");

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
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);

  h2_ptktdR_final->Draw("COLZ ");
  // h2_ptktdR_final->SetMinimum(0.7);
  // h2_ptktdR_final->SetMaximum(1.3);
  // h1_jetpt_data->Draw("COL0Z same");
  ccan[ican]->cd(2);
  h2_ptktdR_ratio_final->Draw("COLZ TEXTE");
  h2_ptktdR_ratio_final->SetMinimum(0.7);
  h2_ptktdR_ratio_final->SetMaximum(1.3);
  ccan[ican]->cd(3);
  h2_ptktdR_truth->Draw("COLZ ");
  ccan[ican]->cd(4);

  h2_ptktdR_vecfinal->Draw("COLZ ");
  // h2_final_ptktdR->SetMinimum(0.7);
  // h2_final_ptktdR->SetMaximum(1.3);
  // h1_jetpt_data->Draw("COL0Z same");

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

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  ccan[ican]->cd(2);
  //
  h1_ptktdR_pulldist_vecfinal->SetLineColor(kMagenta);
  h1_ptktdR_pulldist_final->SetTitle(";Pull;");

  h1_ptktdR_pulldist_final->Draw("SAME");
  h1_ptktdR_pulldist_vecfinal->Draw("SAME");
  // h1_ptktdR_pulldist->SetLineColor(kMagenta);
  // h1_ptktdR_pulldist->Draw("SAME");

  ccan[ican]->cd(3);

  h2_ptktdR_pull_final->Draw("COL0Z TEXT MIN0");
  h2_ptktdR_pull_final->SetMinimum(-4.);
  h2_ptktdR_pull_final->SetMaximum(4.);

  ccan[ican]->cd(4);

  // h2_ktdR_->SetTitle("MCReco+Purity+Unfold; ;");

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
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h2_zdR->Draw("COL0Z");
  // h2_zdR->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  h2_ptzdR_final->Draw("COLZ ");
  h2_ptzdR_final->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  // h1_jetpt_data->Draw("COL0Z same");
  ccan[ican]->cd(2);
  h2_ptzdR_ratio_final->Draw("COLZ TEXTE");
  h2_ptzdR_ratio_final->SetMinimum(0.7);
  h2_ptzdR_ratio_final->SetMaximum(1.3);
  ccan[ican]->cd(3);
  h2_ptzdR_truth->Draw("COLZ ");
  ccan[ican]->cd(4);

  // h2_zdR_bayes_purity_unfold_eff->Draw("COL0Z SAME");
  // h2_zdR_bayes_purity_unfold_eff->SetTitle("Data+Purity+Bayes+eff; ;");

  // h1_jetpt_reco->SetLineColor(kBlack);
  // h1_jetpt_reco->Draw("P E SAME");

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

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);

  ccan[ican]->cd(2);
  //

  h1_ptzdR_pulldist_final->Draw("SAME");

  h1_ptzdR_pulldist->SetLineColor(kMagenta);
  h1_ptzdR_pulldist->Draw("SAME");
  h1_ptzdR_pulldist->SetTitle(";Pull;");

  ccan[ican]->cd(3);

  h2_ptzdR_pull_final->Draw("COL0Z TEXT MIN0");
  h2_ptzdR_pull_final->SetMinimum(-4.);
  h2_ptzdR_pull_final->SetMaximum(4.);

  // auto legend_pulldist_zdR = new TLegend(0.2,0.7,0.5,0.9);
  // legend_pulldist_zdR->SetBorderSize(0);
  // legend_pulldist_zdR->SetFillStyle(0);
  // legend_pulldist_zdR->SetFillColor(3);
  //
  // // legend_pulldist_zdR->AddEntry(h1_dR_purity, "Data+Purity");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Uncorrected");
  // legend_pulldist_zdR->AddEntry(h1_zdR_purity_eff_pulldist, "Pur+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_ids_unfold_pulldist, "IDS");
  // legend_pulldist_zdR->AddEntry(h1_zdR_bayes_unfold_pulldist, "Bayes (Pur+Eff in Res. Mat.)");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Pur+IDS+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_pull_finaldist, "Pur+Bayes+Eff");
  // legend_pulldist_zdR->Draw("SAME");
  // legend_pulldist_zdR->SetFillStyle(0);

  // h2_zdR_->SetTitle("MCReco+Purity+Unfold; ;");

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

  //
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h2_zdR->Draw("COL0Z");
  // h2_zdR->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  h2_ptdRptrad_final->Draw("COLZ ");
  h2_ptdRptrad_final->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  // h1_jetpt_data->Draw("COL0Z same");
  ccan[ican]->cd(2);
  h2_ptdRptrad_ratio_final->Draw("COLZ TEXTE");
  h2_ptdRptrad_ratio_final->SetMinimum(0.7);
  h2_ptdRptrad_ratio_final->SetMaximum(1.3);
  ccan[ican]->cd(3);
  h2_ptdRptrad_truth->Draw("COLZ ");
  ccan[ican]->cd(4);

  // h2_zdR_bayes_purity_unfold_eff->Draw("COL0Z SAME");
  // h2_zdR_bayes_purity_unfold_eff->SetTitle("Data+Purity+Bayes+eff; ;");

  // h1_jetpt_reco->SetLineColor(kBlack);
  // h1_jetpt_reco->Draw("P E SAME");

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

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);

  ccan[ican]->cd(2);
  //

  h1_ptdRptrad_pulldist_final->Draw("SAME");

  h1_ptdRptrad_pulldist->SetLineColor(kMagenta);
  h1_ptdRptrad_pulldist->Draw("SAME");
  h1_ptdRptrad_pulldist->SetTitle(";Pull;");

  ccan[ican]->cd(3);

  h2_ptdRptrad_pull_final->Draw("COL0Z TEXT MIN0");
  h2_ptdRptrad_pull_final->SetMinimum(-4.);
  h2_ptdRptrad_pull_final->SetMaximum(4.);

  // auto legend_pulldist_zdR = new TLegend(0.2,0.7,0.5,0.9);
  // legend_pulldist_zdR->SetBorderSize(0);
  // legend_pulldist_zdR->SetFillStyle(0);
  // legend_pulldist_zdR->SetFillColor(3);
  //
  // // legend_pulldist_zdR->AddEntry(h1_dR_purity, "Data+Purity");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Uncorrected");
  // legend_pulldist_zdR->AddEntry(h1_zdR_purity_eff_pulldist, "Pur+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_ids_unfold_pulldist, "IDS");
  // legend_pulldist_zdR->AddEntry(h1_zdR_bayes_unfold_pulldist, "Bayes (Pur+Eff in Res. Mat.)");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Pur+IDS+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_pull_finaldist, "Pur+Bayes+Eff");
  // legend_pulldist_zdR->Draw("SAME");
  // legend_pulldist_zdR->SetFillStyle(0);

  // h2_zdR_->SetTitle("MCReco+Purity+Unfold; ;");

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

  //
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================

  //
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h2_zdR->Draw("COL0Z");
  // h2_zdR->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  h2_ptthetaErad_final->Draw("COLZ ");
  h2_ptthetaErad_final->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  // h1_jetpt_data->Draw("COL0Z same");
  ccan[ican]->cd(2);
  h2_ptthetaErad_ratio_final->Draw("COLZ TEXTE");
  h2_ptthetaErad_ratio_final->SetMinimum(0.7);
  h2_ptthetaErad_ratio_final->SetMaximum(1.3);
  ccan[ican]->cd(3);
  h2_ptthetaErad_truth->Draw("COLZ ");
  ccan[ican]->cd(4);

  // h2_thetaErad_bayes_purity_unfold_eff->Draw("COL0Z SAME");
  // h2_thetaErad_bayes_purity_unfold_eff->SetTitle("Data+Purity+Bayes+eff; ;");

  // h1_jetpt_reco->SetLineColor(kBlack);
  // h1_jetpt_reco->Draw("P E SAME");

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

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h1_thetaErad_pulldist->Draw("SAME");
  // h1_thetaErad_pulldist->SetLineColor(kBlack);

  ccan[ican]->cd(2);
  //

  h1_ptthetaErad_pulldist_final->Draw("SAME");

  // h1_ptthetaErad_pulldist->SetLineColor(kMagenta);
  // h1_ptthetaErad_pulldist->Draw("SAME");
  // h1_ptthetaErad_pulldist->SetTitle(";Pull;");

  ccan[ican]->cd(3);

  h2_ptthetaErad_pull_final->Draw("COL0Z TEXT MIN0");
  h2_ptthetaErad_pull_final->SetMinimum(-4.);
  h2_ptthetaErad_pull_final->SetMaximum(4.);

  // auto legend_pulldist_zdR = new TLegend(0.2,0.7,0.5,0.9);
  // legend_pulldist_zdR->SetBorderSize(0);
  // legend_pulldist_zdR->SetFillStyle(0);
  // legend_pulldist_zdR->SetFillColor(3);
  //
  // // legend_pulldist_zdR->AddEntry(h1_dR_purity, "Data+Purity");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Uncorrected");
  // legend_pulldist_zdR->AddEntry(h1_zdR_purity_eff_pulldist, "Pur+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_ids_unfold_pulldist, "IDS");
  // legend_pulldist_zdR->AddEntry(h1_zdR_bayes_unfold_pulldist, "Bayes (Pur+Eff in Res. Mat.)");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Pur+IDS+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_pull_finaldist, "Pur+Bayes+Eff");
  // legend_pulldist_zdR->Draw("SAME");
  // legend_pulldist_zdR->SetFillStyle(0);

  // h2_zdR_->SetTitle("MCReco+Purity+Unfold; ;");

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
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h2_zdR->Draw("COL0Z");
  // h2_zdR->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  h2_ptdRErad_final->Draw("COLZ ");
  h2_ptdRErad_final->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  // h1_jetpt_data->Draw("COL0Z same");
  ccan[ican]->cd(2);
  h2_ptdRErad_ratio_final->Draw("COLZ TEXTE");
  h2_ptdRErad_ratio_final->SetMinimum(0.7);
  h2_ptdRErad_ratio_final->SetMaximum(1.3);
  ccan[ican]->cd(3);
  h2_dRErad_truth->Draw("COLZ ");
  ccan[ican]->cd(4);

  // h2_dRErad_bayes_purity_unfold_eff->Draw("COL0Z SAME");
  // h2_dRErad_bayes_purity_unfold_eff->SetTitle("Data+Purity+Bayes+eff; ;");

  // h1_jetpt_reco->SetLineColor(kBlack);
  // h1_jetpt_reco->Draw("P E SAME");

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

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h1_dRErad_pulldist->Draw("SAME");
  // h1_dRErad_pulldist->SetLineColor(kBlack);

  ccan[ican]->cd(2);
  //

  h1_ptdRErad_pulldist_final->Draw("SAME");

  // h1_ptdRErad_pulldist->SetLineColor(kMagenta);
  // h1_ptdRErad_pulldist->Draw("SAME");
  // h1_ptdRErad_pulldist->SetTitle(";Pull;");

  ccan[ican]->cd(3);

  h2_ptdRErad_pull_final->Draw("COL0Z TEXT MIN0");
  h2_ptdRErad_pull_final->SetMinimum(-4.);
  h2_ptdRErad_pull_final->SetMaximum(4.);

  // auto legend_pulldist_zdR = new TLegend(0.2,0.7,0.5,0.9);
  // legend_pulldist_zdR->SetBorderSize(0);
  // legend_pulldist_zdR->SetFillStyle(0);
  // legend_pulldist_zdR->SetFillColor(3);
  //
  // // legend_pulldist_zdR->AddEntry(h1_dR_purity, "Data+Purity");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Uncorrected");
  // legend_pulldist_zdR->AddEntry(h1_zdR_purity_eff_pulldist, "Pur+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_ids_unfold_pulldist, "IDS");
  // legend_pulldist_zdR->AddEntry(h1_zdR_bayes_unfold_pulldist, "Bayes (Pur+Eff in Res. Mat.)");
  // legend_pulldist_zdR->AddEntry(h1_zdR_pulldist, "Pur+IDS+Eff");
  // // legend_pulldist_zdR->AddEntry(h1_zdR_pull_finaldist, "Pur+Bayes+Eff");
  // legend_pulldist_zdR->Draw("SAME");
  // legend_pulldist_zdR->SetFillStyle(0);

  // h2_zdR_->SetTitle("MCReco+Purity+Unfold; ;");

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
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  // h2_zdR->Draw("COL0Z");
  // h2_zdR->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  h2_ptktdR_SV_final->Draw("COLZ ");
  h2_ptktdR_SV_final->SetTitle("Data;ln(R/#DeltaR);ln(1/z)");
  // h1_jetpt_data->Draw("COL0Z same");
  ccan[ican]->cd(2);
  h2_ptktdR_SV_ratio_final->Draw("COLZ TEXTE");
  h2_ptktdR_SV_ratio_final->SetMinimum(0.7);
  h2_ptktdR_SV_ratio_final->SetMaximum(1.3);
  ccan[ican]->cd(3);
  h2_ktdR_SV_truth->Draw("COLZ ");
  ccan[ican]->cd(4);

  // h2_ktdR_SV_bayes_purity_unfold_eff->Draw("COL0Z SAME");
  // h2_ktdR_SV_bayes_purity_unfold_eff->SetTitle("Data+Purity+Bayes+eff; ;");

  // h1_jetpt_reco->SetLineColor(kBlack);
  // h1_jetpt_reco->Draw("P E SAME");

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
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  ccan[ican]->cd(2);
  //

  h1_ptktdR_SV_pulldist_final->Draw("SAME");

  h1_ptktdR_SV_pulldist->SetLineColor(kMagenta);
  h1_ptktdR_SV_pulldist->Draw("SAME");
  h1_ptktdR_SV_pulldist->SetTitle(";Pull;");

  ccan[ican]->cd(3);

  h2_ptktdR_SV_pull_final->Draw("COL0Z TEXT MIN0");
  h2_ptktdR_SV_pull_final->SetMinimum(-4.);
  h2_ptktdR_SV_pull_final->SetMaximum(4.);

  ccan[ican]->cd(4);

  // h2_ktdR_SV_->SetTitle("MCReco+Purity+Unfold; ;");

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

  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h3_eff_ptktdR->GetZaxis()->SetRange(1, 1);
  auto h1_proj_eff1 = h3_eff_ptktdR->Project3D("yx_1");
  h1_proj_eff1->SetMaximum(1.0);
  h1_proj_eff1->SetMinimum(0.0);
  h1_proj_eff1->Draw("COLZ");
  // gPad->SetLogz();

  ccan[ican]->cd(2);
  // gPad->SetLogz();
  h3_eff_ptktdR->GetZaxis()->SetRange(2, 2);
  auto h1_proj_eff2 = (TH2D *)h3_eff_ptktdR->Project3D("yx_2");
  h1_proj_eff2->SetMaximum(1.0);
  h1_proj_eff2->SetMinimum(0.0);
  h1_proj_eff2->Draw("COLZ");

  ccan[ican]->cd(3);
  // gPad->SetLogz();
  h3_eff_ptktdR->GetZaxis()->SetRange(3, 3);
  auto h1_proj_eff3 = (TH2D *)h3_eff_ptktdR->Project3D("yx_3");
  h1_proj_eff3->SetMaximum(1.0);
  h1_proj_eff3->SetMinimum(0.0);
  h1_proj_eff3->Draw("COLZ");
  ccan[ican]->cd(4);
  // gPad->SetLogz();
  h3_eff_ptktdR->GetZaxis()->SetRange(4, 4);
  auto h1_proj_eff4 = (TH2D *)h3_eff_ptktdR->Project3D("yx_4");
  h1_proj_eff4->SetMaximum(1.0);
  h1_proj_eff4->SetMinimum(0.0);
  h1_proj_eff4->Draw("COLZ");

  // h2_ktdR_->SetTitle("Data+Purity+Unfold; ;");

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
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  h3_purity_ptktdR->GetZaxis()->SetRange(1, 1);
  auto h1_proj_pur1 = h3_purity_ptktdR->Project3D("yx_1");
  h1_proj_pur1->SetMaximum(1.0);
  h1_proj_pur1->SetMinimum(0.0);
  h1_proj_pur1->Draw("COLZ");
  // gPad->SetLogz();

  ccan[ican]->cd(2);
  // gPad->SetLogz();
  h3_purity_ptktdR->GetZaxis()->SetRange(2, 2);
  auto h1_proj_pur2 = (TH2D *)h3_purity_ptktdR->Project3D("yx_2");
  h1_proj_pur2->SetMaximum(1.0);
  h1_proj_pur2->SetMinimum(0.0);
  h1_proj_pur2->Draw("COLZ");

  ccan[ican]->cd(3);
  // gPad->SetLogz();
  h3_purity_ptktdR->GetZaxis()->SetRange(3, 3);
  auto h1_proj_pur3 = (TH2D *)h3_purity_ptktdR->Project3D("yx_3");
  h1_proj_pur3->SetMaximum(1.0);
  h1_proj_pur3->SetMinimum(0.0);
  h1_proj_pur3->Draw("COLZ");
  ccan[ican]->cd(4);
  // gPad->SetLogz();
  h3_purity_ptktdR->GetZaxis()->SetRange(4, 4);
  auto h1_proj_pur4 = (TH2D *)h3_purity_ptktdR->Project3D("yx_4");
  h1_proj_pur4->SetMaximum(1.0);
  h1_proj_pur4->SetMinimum(0.0);
  h1_proj_pur4->Draw("COLZ");

  // h2_ktdR_->SetTitle("Data+Purity+Unfold; ;");

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
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================
  //===================================================================================================

  //
  ++ican;
  sprintf(buf, "ccan%d", ican);
  ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
  ccan[ican]->SetFillColor(10);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetBottomMargin(0.06);
  ccan[ican]->cd();
  ccan[ican]->Divide(2, 2, 0.0001, 0.0001);

  ccan[ican]->cd(1);
  TH1D *h1_temp_final_3 = (TH1D *)h2_frag_z_jetpt_SV_final->ProjectionX(Form("htemp%d_fragzjetpt_SV_final", 3), 3, 3);
  TH1D *h1_temp_truth_3 = (TH1D *)h2_frag_z_jetpt_SV_truth->ProjectionX(Form("htemp%d_fragzjetpt_SV_truth", 3), 3, 3);
  TH1D *h1_temp_reco_3 = (TH1D *)h2_frag_z_jetpt_SV_reco->ProjectionX(Form("htemp%d_fragzjetpt_SV_reco", 3), 3, 3);

  NormalizeHist(h1_temp_final_3);
  NormalizeHist(h1_temp_truth_3);
  NormalizeHist(h1_temp_reco_3);
  h1_temp_final_3->SetMarkerStyle(1 + 20);
  h1_temp_final_3->SetMarkerColor(1 + 1);
  h1_temp_final_3->SetLineColor(1 + 1);
  h1_temp_final_3->Draw("P E SAME");
  h1_temp_final_3->Draw("HIST SAME");

  h1_temp_final_3->SetMaximum(h1_temp_final_3->GetMaximum() * 1.2);
  h1_temp_final_3->SetMinimum(0.);

  h1_temp_truth_3->SetMarkerStyle(2 + 20);
  h1_temp_truth_3->SetMarkerColor(2 + 1);
  h1_temp_truth_3->SetLineColor(2 + 1);
  h1_temp_truth_3->Draw("P E SAME");
  h1_temp_truth_3->Draw("HIST SAME");

  h1_temp_reco_3->SetMarkerStyle(3 + 20);
  h1_temp_reco_3->SetMarkerColor(3 + 1);
  h1_temp_reco_3->SetLineColor(3 + 1);
  h1_temp_reco_3->Draw("P E SAME");
  h1_temp_reco_3->Draw("HIST SAME");

  ccan[ican]->cd(2);

  TH1D *h1_temp_final_4 = (TH1D *)h2_frag_z_jetpt_SV_final->ProjectionX(Form("htemp%d_fragzjetpt_SV_final", 4), 4, 4);
  TH1D *h1_temp_truth_4 = (TH1D *)h2_frag_z_jetpt_SV_truth->ProjectionX(Form("htemp%d_fragzjetpt_SV_truth", 4), 4, 4);
  TH1D *h1_temp_reco_4 = (TH1D *)h2_frag_z_jetpt_SV_reco->ProjectionX(Form("htemp%d_fragzjetpt_SV_reco", 4), 4, 4);

  NormalizeHist(h1_temp_final_4);
  NormalizeHist(h1_temp_truth_4);
  NormalizeHist(h1_temp_reco_4);
  h1_temp_final_4->SetMarkerStyle(1 + 20);
  h1_temp_final_4->SetMarkerColor(1 + 1);
  h1_temp_final_4->SetLineColor(1 + 1);
  h1_temp_final_4->Draw("P E SAME");
  h1_temp_final_4->Draw("HIST SAME");

  h1_temp_final_4->SetMaximum(h1_temp_final_4->GetMaximum() * 1.2);
  h1_temp_final_4->SetMinimum(0.);

  h1_temp_truth_4->SetMarkerStyle(2 + 20);
  h1_temp_truth_4->SetMarkerColor(2 + 1);
  h1_temp_truth_4->SetLineColor(2 + 1);
  h1_temp_truth_4->Draw("P E SAME");
  h1_temp_truth_4->Draw("HIST SAME");

  h1_temp_reco_4->SetMarkerStyle(3 + 20);
  h1_temp_reco_4->SetMarkerColor(3 + 1);
  h1_temp_reco_4->SetLineColor(3 + 1);
  h1_temp_reco_4->Draw("P E SAME");
  h1_temp_reco_4->Draw("HIST SAME");

  ccan[ican]->cd(3);

  TH1D *h1_temp_final_5 = (TH1D *)h2_frag_z_jetpt_SV_final->ProjectionX(Form("htemp%d_fragzjetpt_SV_final", 5), 5, 5);
  TH1D *h1_temp_truth_5 = (TH1D *)h2_frag_z_jetpt_SV_truth->ProjectionX(Form("htemp%d_fragzjetpt_SV_truth", 5), 5, 5);
  TH1D *h1_temp_reco_5 = (TH1D *)h2_frag_z_jetpt_SV_reco->ProjectionX(Form("htemp%d_fragzjetpt_SV_reco", 5), 5, 5);

  NormalizeHist(h1_temp_final_5);
  NormalizeHist(h1_temp_truth_5);
  NormalizeHist(h1_temp_reco_5);
  h1_temp_final_5->SetMarkerStyle(1 + 20);
  h1_temp_final_5->SetMarkerColor(1 + 1);
  h1_temp_final_5->SetLineColor(1 + 1);
  h1_temp_final_5->Draw("P E SAME");
  h1_temp_final_5->Draw("HIST SAME");

  h1_temp_final_5->SetMaximum(h1_temp_final_5->GetMaximum() * 1.2);
  h1_temp_final_5->SetMinimum(0.);

  h1_temp_truth_5->SetMarkerStyle(2 + 20);
  h1_temp_truth_5->SetMarkerColor(2 + 1);
  h1_temp_truth_5->SetLineColor(2 + 1);
  h1_temp_truth_5->Draw("P E SAME");
  h1_temp_truth_5->Draw("HIST SAME");

  h1_temp_reco_5->SetMarkerStyle(3 + 20);
  h1_temp_reco_5->SetMarkerColor(3 + 1);
  h1_temp_reco_5->SetLineColor(3 + 1);
  h1_temp_reco_5->Draw("P E SAME");
  h1_temp_reco_5->Draw("HIST SAME");
  // for (int i = 2; i < ptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_frag_z_jetpt_SV_final->ProjectionX(Form("htemp%d_fragzjetpt_SV_final", i), i + 1, i + 1);
  //   NormalizeHist(h1_temp);
  //   h1_temp->SetMarkerStyle(i + 20);
  //   h1_temp->SetMarkerColor(i + 1);
  //   h1_temp->SetLineColor(i + 1);
  //   h1_temp->Draw("P E SAME");
  //   h1_temp->Draw("HIST SAME");
  //   // h1_temp->SetMinimum(0.);
  //   // h1_temp->SetMaximum(1.05);
  // }

  // ccan[ican]->cd(2);
  // for (int i = 2; i < ptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_frag_z_jetpt_SV_truth->ProjectionX(Form("htemp%d_fragzjetpt_SV_truth", i), i + 1, i + 1);
  //   NormalizeHist(h1_temp);
  //   h1_temp->SetMarkerStyle(i + 20);
  //   h1_temp->SetMarkerColor(i + 1);
  //   h1_temp->SetLineColor(i + 1);
  //   h1_temp->Draw("P E SAME");
  //   h1_temp->Draw("HIST SAME");
  //   // h1_temp->SetMinimum(0.);
  //   // h1_temp->SetMaximum(1.05);
  // }

  // ccan[ican]->cd(3);
  // for (int i = 2; i < ptbinsize; i++)
  // {
  //   TH1D *h1_temp = (TH1D *)h2_frag_z_jetpt_SV_reco->ProjectionX(Form("htemp%d_fragzjetpt_SV_reco", i), i + 1, i + 1);
  //   NormalizeHist(h1_temp);
  //   h1_temp->SetMarkerStyle(i + 20);
  //   h1_temp->SetMarkerColor(i + 1);
  //   h1_temp->SetLineColor(i + 1);
  //   h1_temp->Draw("P E SAME");
  //   h1_temp->Draw("HIST SAME");
  //   // h1_temp->SetMinimum(0.);
  //   // h1_temp->SetMaximum(1.05);
  // }

  // h2_dRErad_bayes_purity_unfold_eff->Draw("COL0Z SAME");
  // h2_dRErad_bayes_purity_unfold_eff->SetTitle("Data+Purity+Bayes+eff; ;");

  // h1_jetpt_reco->SetLineColor(kBlack);
  // h1_jetpt_reco->Draw("P E SAME");

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

  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }

  cout << (Njets_truth - Njets_final) / Njets_truth * 100 << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================ktdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptktdR_pullperf1 << " %"
       << " --- " << ptktdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptktdR_pullperf1_final << " %"
       << " --- " << ptktdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_z << " iterations:" << endl;
  cout << "=======================zdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzdR_pullperf1 << " %"
       << " --- " << ptzdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzdR_pullperf1_final << " %"
       << " --- " << ptzdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;

  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptktdR_ratio_final) << endl;
  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzdR_ratio_final) << endl;

  // TFile *file_save = new TFile("hists/HFpt_Correction.root", "RECREATE");
  // h2_correct_HFptjetpt->Write("h2_correct_HFptjetpt");
  // file_save->Close();

  h2_ptktdR_ratio_final->Write("ptktdR_ratio_final");
  h2_ptzdR_ratio_final->Write("ptzdR_ratio_final");
  h1_jetpt_final->Write("h1_jetpt_final");
  h1_jetpt_reco->Write("h1_jetpt_reco");
  h1_jetpt_truth->Write("h1_jetpt_truth");
  file_write->Write();
  file_write->Close();
  //
}
