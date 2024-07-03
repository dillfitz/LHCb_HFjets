#include <TCanvas.h>
#include <vector>
#include <iostream>
//#include "../Reference/Settings.h"
#include "../Reference/Helpers.h"
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

  TString string_reco, string_data, string_truth, string_eff, string_unfold, extension, str_eta, str_pt, str_Nevts;
  TString str_followHard, str_ghost, str_charged, str_Mag1, str_Mag2, str_flavor, str_GS(""), str_WTA;
  TString loc_hists("../../root_files/");
  TString loc_plots("../../plots/");  
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

  string_reco = loc_hists + "BjetsMC/" + TString("reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset1);
  string_truth = loc_hists + "BjetsMC/" + TString("truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag1 + str_flavor + str_GS + str_WTA + Form("_%d", dataset1);  
  string_eff = loc_hists + "BjetsMC/" + TString("efficiency_truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag2 + str_flavor + str_GS + str_WTA + Form("_%d", dataset2);
  string_unfold = loc_hists + "BjetsMC/" + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag2 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset2); 
  string_data = loc_hists + "Bjets/" + TString("data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset1);
  
  extension = loc_hists + "BjetsMC/" + TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_iters_%d_%d", NumIters_kt, NumIters_z) + Form("_%d", dataset1) + Form("_%d", dataset2);


  cout << string_reco + TString(".root") << endl;
  cout << string_truth + TString(".root") << endl;
  cout << string_eff + TString(".root") << endl;
  cout << string_unfold + TString(".root") << endl;
  cout << extension + TString(".root") << endl;
  
  /////////////////////   Get Files /////////////////////////////////

  TFile *file_reco = new TFile(string_reco + TString(".root"), "READ"); 
  TFile *file_data = new TFile(string_data + TString(".root"), "READ");
  TFile *file_truth = new TFile(string_truth + TString(".root"), "READ"); 
  TFile *file_eff = new TFile(string_eff + TString(".root"), "READ"); 
  TFile *file_unfold = new TFile(string_unfold + TString(".root"), "READ"); 

  TFile *file_write = new TFile(extension + TString(".root"), "RECREATE");

  /////////////////////   Get histograms /////////////////////////////////

  TH1D *h1_jetpt_ref = (TH1D *)file_unfold->Get("jetpt");
  h1_jetpt_ref->Draw();
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
  TH1D *h1_efficiency_vecHFpt = (TH1D *)file_unfold->Get("efficiency_HFpt");
  TH1D *h1_purity_vecHFpt = (TH1D *)file_unfold->Get("purity_HFpt");
  // TH3D * h3_purity_ptzjt = (TH3D*) file_unfold->Get("purity_ptHFzjt");
  // TH3D * h3_purity_ptzdR = (TH3D*) file_unfold->Get("purity_ptHFzdR");

  /////////////////////   Get Response Matrices /////////////////////////////////

  // RooUnfoldResponse * response_jetpt = (RooUnfoldResponse*)file_eff->Get("response_jetpt");
  RooUnfoldResponse *response_jetpt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_jetpt");
  TH2 *h2_response_jetpt = (TH2 *)response_jetpt->Hresponse();

  response_jetpt->UseOverflow();

  int ntoys = 5;

  // unfold_zjt_bayes.SetVerbose (1);
  // unfold_zjt_bayes.SetNToys(ntoys);
  // unfold_zjt_bayes.IncludeSystematics(0);
  //
  // unfold_dR_bayes.SetNToys(ntoys);
  // unfold_dR_bayes.IncludeSystematics(0);

  // RooUnfoldErrors* errors= new RooUnfoldErrors(ntoys,&unfold_zjt_bayes,h2_zjt_truth);
  // auto hToyErr=errors->RMSResiduals();
  // auto hUnfErr=errors->UnfoldingError();

  // RooUnfoldErrors* errors= new RooUnfoldErrors(ntoys,&unfold_dR_bayes,h1_dR_truth);
  // auto hToyErr=errors->RMSResiduals();
  // auto hUnfErr=errors->UnfoldingError();

  // h1_jetpt_final->Multiply(h1_purity_jetpt);
  RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters_z);
  // RooUnfoldIds unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters_kt);
  h1_jetpt_final = (TH1D *)unfold_jetpt.Hreco();
  // h1_jetpt_final->Divide(h1_efficiency_recoJet_jetpt);
  
  cout << "Unfold successful" << endl;  

  // h1_jetpt_final->Divide(h1_efficiency_jetpt);

  TH1D *h1_correct_jetpt = (TH1D *)h1_jetpt_final->Clone("h1_correct_jetpt");
  // TH1D * h1_correct_jetpt = (TH1D*) h1_jetpt_reco->Clone("h1_correct_jetpt");
  h1_correct_jetpt->Divide(h1_jetpt_truth);

  // h1_jetpt_final->Divide(h1_correct_jetpt);
  // h1_efficiency_recoJet_jetpt->Multiply(h1_correct_jetpt);

  vector<TH1D *> vec_jetpt, vec_efficiency_jetpt, vec_purity_jetpt;
  vector<RooUnfoldResponse *> vec_response_jetpt;
  for (int i = 0; i < ptHFbinsize; i++)
  {
    int loc = i;
    cout << "Reading histograms: " << endl;
    std::cout << Form("jetpt%d", loc) << std::endl;
    TH1D *h1_jetpt_tmp = (TH1D *)file_reco->Get(Form("jetpt%d", loc));
    TH1D *h1_efficiency_jetpt_tmp = (TH1D *)file_unfold->Get(Form("efficiency_jetpt%d", loc));
    TH1D *h1_purity_jetpt_tmp = (TH1D *)file_unfold->Get(Form("purity_jetpt%d", loc));
    RooUnfoldResponse *response_jetpt_tmp = (RooUnfoldResponse *)file_unfold->Get(Form("response_jetpt%d", loc));
    cout << "Pushback: " << endl;
    if (response_jetpt_tmp != NULL)
      cout << "found response" << endl;

    cout << "h1_jetpt_tmp->Integral() : " <<  h1_jetpt_tmp->Integral() << endl;
    cout << "h1_purity_jetpt_tmp->Integral() : " << h1_purity_jetpt_tmp->Integral() << endl;
    cout << "h1_efficiency_jetpt_tmp->Integral() : " << h1_efficiency_jetpt_tmp->Integral() << endl;
    vec_jetpt.push_back(h1_jetpt_tmp);
    vec_efficiency_jetpt.push_back(h1_efficiency_jetpt_tmp);
    vec_purity_jetpt.push_back(h1_purity_jetpt_tmp);
    vec_response_jetpt.push_back(response_jetpt_tmp);
  }

  TH1D *h1_jetpt_vecfinal;
  for (int i = 0; i < ptHFbinsize; i++)
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
  
  std::cout << "Normalizing hists..." << std::endl;

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

  /////////////////////   Create zjt histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  vector<RooUnfoldResponse *> vec_response_ptzjt;
  vector<TH3D *> vec_h3_ptzjt, vec_h3_efficiency_ptzjt, vec_h3_purity_ptzjt;
  for (int i = 0; i < ptHFbinsize; i++)
  {
    int loc = i;
    TH3D *h3_ptzjt_tmp = (TH3D *)file_reco->Get(Form("h3_ptzjt%d", loc));
    std::cout << " made it here.. " << std::endl;
    vec_h3_ptzjt.push_back(h3_ptzjt_tmp);

    RooUnfoldResponse *response_ptzjt_temp = (RooUnfoldResponse *)file_unfold->Get(Form("h3_response_ptzjt%d", loc));
    vec_response_ptzjt.push_back(response_ptzjt_temp);

    TH3D *h3_efficiency_ptzjt_tmp = (TH3D *)file_unfold->Get(Form("h3_efficiency_ptzjt%d", loc));
    TH3D *h3_purity_ptzjt_tmp = (TH3D *)file_unfold->Get(Form("h3_purity_ptzjt%d", loc));

    vec_h3_efficiency_ptzjt.push_back(h3_efficiency_ptzjt_tmp);
    vec_h3_purity_ptzjt.push_back(h3_purity_ptzjt_tmp);
  }

  TH2D *h2_zjt_truth = (TH2D *)file_truth->Get("zjt");
  TH3D *h3_ptzjt_truth = (TH3D *)file_truth->Get("ptzjt");
  TH3D *h3_ptzjt = (TH3D *)file_reco->Get("ptzjt");
  TH3D *h3_ptzjt_final = (TH3D *)h3_ptzjt->Clone("ptzjt_final");
  TH3D *h3_eff_ptzjt = (TH3D *)file_unfold->Get("efficiency_ptzjt");
  TH3D *h3_purity_ptzjt = (TH3D *)file_unfold->Get("purity_ptzjt");
  RooUnfoldResponse *response_ptzjt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzjt");
  //
  TH3D *h3_ptzjt_vecfinal;
  for (int i = 0; i < ptHFbinsize; i++)
  {
    int loc = i;

    double HF_eff = h1_efficiency_vecHFpt->GetBinContent(loc + 1);
    double HF_pur = h1_purity_vecHFpt->GetBinContent(loc + 1);
    vec_h3_ptzjt[loc]->Scale(HF_pur);
    cout << ptHF_binedges[i] << ", " << ptHF_binedges[i + 1] << endl;
    vec_h3_ptzjt[loc]->Multiply(vec_h3_purity_ptzjt[loc]);
    ///// Update NumIters_kt to something more general /////
    RooUnfoldBayes unfold_ptzjt(vec_response_ptzjt[loc], vec_h3_ptzjt[loc], NumIters_kt);
    // vec_h3_ptzjt[loc] = (TH3D *)unfold_ptzjt.Hreco();
    vec_h3_ptzjt[loc]->Divide(vec_h3_efficiency_ptzjt[loc]);

    cout << HF_eff << ", " << HF_pur << endl;

    vec_h3_ptzjt[loc]->Scale(1. / HF_eff);
    if (i == 0)
      h3_ptzjt_vecfinal = vec_h3_ptzjt[loc];
    else
      h3_ptzjt_vecfinal->Add(vec_h3_ptzjt[loc]);
  }
  h3_ptzjt_final->Multiply(h3_ptzjt_final, h3_purity_ptzjt);
  RooUnfoldBayes unfold_ptzjt(response_ptzjt, h3_ptzjt_final, NumIters_kt);
  // RooUnfoldIds unfold_ptzjt(response_ptzjt, h3_ptzjt_final, NumIters_kt);
  h3_ptzjt_final = (TH3D *)unfold_ptzjt.Hreco();
  h3_ptzjt_final->Divide(h3_ptzjt_final, h3_eff_ptzjt);
  //
  int binlow = h3_ptzjt->GetZaxis()->FindBin(ptMin + 0.1);
  int binhigh = h3_ptzjt->GetZaxis()->FindBin(ptMax - 0.1);
  int binlowdR = h3_ptzjt->GetXaxis()->FindBin(0.);
  int binhighdR = h3_ptzjt->GetXaxis()->FindBin(2.1);
  int binlowkt = h3_ptzjt->GetYaxis()->FindBin(-1.9);
  int binhighkt = h3_ptzjt->GetYaxis()->FindBin(1.49);
  //

  h3_ptzjt_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzjt_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzjt_vecfinal->GetZaxis()->SetRangeUser(ptMin, ptMax);

  h3_ptzjt->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptzjt_final = (TH2D *)h3_ptzjt_final->Project3D("kt_final_yx");
  TH2D *h2_ptzjt_vecfinal = (TH2D *)h3_ptzjt_vecfinal->Project3D("kt_vecfinal_yx");
  TH2D *h2_ptzjt = (TH2D *)h3_ptzjt->Project3D("kt_yx");
  TH2D *h2_ptzjt_truth = (TH2D *)h3_ptzjt_truth->Project3D("kt_truth_yx");
  //
  h2_ptzjt_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_final->GetXaxis()->SetRange(binlowdR, binhighdR);
  h2_ptzjt_vecfinal->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_vecfinal->GetXaxis()->SetRange(binlowdR, binhighdR);
  h2_ptzjt_truth->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_truth->GetXaxis()->SetRange(binlowdR, binhighdR);

  TH2D *h2_final_ptzjt = GetJetPtCorrectedHist(h3_ptzjt_final, h1_efficiency_recoJet_jetpt);
  h2_final_ptzjt->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_final_ptzjt->GetXaxis()->SetRange(binlowdR, binhighdR);
  //
  // NormalizeHist(h2_ptzjt_final);
  // NormalizeHist(h2_ptzjt_vecfinal);
  // NormalizeHist(h2_ptzjt_truth);
  h2_final_ptzjt->Scale(1. / Njets_final, "width");
  h2_ptzjt_final->Scale(1. / Njets_final, "width");
  h2_ptzjt_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h2_ptzjt_truth->Scale(1. / Njets_truth, "width");

  // h2_ptzjt_vecfinal->Scale(1. / Njets_vecfinal, "width");
  // h2_ptzjt_final->Scale(1. / 0.98);

  TH2D *h2_ptzjt_ratio = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_ratio");
  TH2D *h2_ptzjt_ratio_final = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_ratio_final");
  TH2D *h2_ptzjt_pull_final = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_pull_final");

  TH2D *h2_ptzjt_ratio_vecfinal = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_ratio_vecfinal");
  TH2D *h2_ptzjt_pull_vecfinal = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_pull_vecfinal");

  // TH2D *h2_ptzjt_ratio_final = new TH2D("h2_ptzjt_ratio_final", "", dRbinsizefinal, dR_binedgesfinal, ktbinsizefinal, kt_binedgesfinal);
  // TH2D *h2_ptzjt_pull_final = new TH2D("h2_ptzjt_pull_final", "", dRbinsizefinal, dR_binedgesfinal, ktbinsizefinal, kt_binedgesfinal);

  TH2D *h2_ptzjt_pull = (TH2D *)h2_zjt_truth->Clone("ptzjt_pull");

  TH1D *h1_ptzjt_pulldist = new TH1D("ptzjt_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptzjt_pulldist_final = new TH1D("ptzjt_pulldist_final", "", 20, -4.5, 4.5);
  TH1D *h1_ptzjt_pulldist_vecfinal = new TH1D("ptzjt_pulldist_vecfinal", "", 20, -4.5, 4.5);

  // h2_ptzjt_ratio->Divide(h2_ptzjt, h2_zjt_truth);
  // h2_ptzjt_ratio_final->Divide(h2_ptzjt_final, h2_zjt_truth);

  h2_ptzjt_ratio->Divide(h2_ptzjt, h2_ptzjt_truth);
  h2_ptzjt_ratio_final->Divide(h2_ptzjt_final, h2_ptzjt_truth);
  h2_ptzjt_ratio_vecfinal->Divide(h2_ptzjt_vecfinal, h2_ptzjt_truth);

  h2_ptzjt_ratio_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_ratio_final->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptzjt_pull_final->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_pull_final->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptzjt_ratio_vecfinal->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_ratio_vecfinal->GetXaxis()->SetRange(binlowdR, binhighdR);

  h2_ptzjt_pull_vecfinal->GetYaxis()->SetRange(binlowkt, binhighkt);
  h2_ptzjt_pull_vecfinal->GetXaxis()->SetRange(binlowdR, binhighdR);

  // for (int i = 0; i < dRbinsizefinal; i++)
  // {
  //   for (int j = 1; j < ktbinsizefinal + 1; j++)
  //   {
  //     double num = h2_ptzjt_final->GetBinContent(i + 2, j + 1);
  //     // double num = h2_final_ptzjt->GetBinContent(i + 2, j + 1);
  //     double denom = h2_ptzjt_truth->GetBinContent(i + 2, j + 1);
  //     double num_err = h2_ptzjt_final->GetBinError(i + 2, j + 1);
  //     // double num_err = h2_final_ptzjt->GetBinError(i + 2, j + 1);
  //     double denom_err = h2_ptzjt_truth->GetBinError(i + 2, j + 1);
  //     double tot = num / denom;
  //     double tot_err = tot * sqrt(pow(num_err / num, 2) + pow(denom_err / denom, 2));
  //     if (denom <= 0)
  //       continue;
  //     h2_ptzjt_ratio_final->SetBinContent(i + 1, j + 1 - 1, tot);
  //     h2_ptzjt_ratio_final->SetBinError(i + 1, j + 1 - 1, tot_err);
  //   }
  // }

  GetPullsRatio(h2_ptzjt_ratio, h2_ptzjt_pull, h1_ptzjt_pulldist);
  GetPullsRatio(h2_ptzjt_ratio_final, h2_ptzjt_pull_final, h1_ptzjt_pulldist_final);
  GetPullsRatio(h2_ptzjt_ratio_vecfinal, h2_ptzjt_pull_vecfinal, h1_ptzjt_pulldist_vecfinal);

  double ptzjt_pullperf1 = GetPullPerformance(h2_ptzjt_pull, 1);
  double ptzjt_pullperf2 = GetPullPerformance(h2_ptzjt_pull, 2);

  double ptzjt_pullperf1_final = GetPullPerformance(h2_ptzjt_pull_final, 1);
  double ptzjt_pullperf2_final = GetPullPerformance(h2_ptzjt_pull_final, 2);
  
  /*

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
  

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================zjt Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzjt_pullperf1 << " %"
       << " --- " << ptzjt_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzjt_pullperf1_final << " %"
       << " --- " << ptzjt_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_z << " iterations:" << endl;
  cout << "=======================zdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzdR_pullperf1 << " %"
       << " --- " << ptzdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzdR_pullperf1_final << " %"
       << " --- " << ptzdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;

  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzjt_ratio_final) << endl;
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

 

  cout << (Njets_truth - Njets_final) / Njets_truth * 100 << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================zjt Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzjt_pullperf1 << " %"
       << " --- " << ptzjt_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzjt_pullperf1_final << " %"
       << " --- " << ptzjt_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_z << " iterations:" << endl;
  cout << "=======================zdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzdR_pullperf1 << " %"
       << " --- " << ptzdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzdR_pullperf1_final << " %"
       << " --- " << ptzdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;

  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzjt_ratio_final) << endl;
  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzdR_ratio_final) << endl;

  // TFile *file_save = new TFile("hists/HFpt_Correction.root", "RECREATE");
  // h2_correct_HFptjetpt->Write("h2_correct_HFptjetpt");
  // file_save->Close();

  h2_ptzjt_ratio_final->Write("ptzjt_ratio_final");
  h2_ptzdR_ratio_final->Write("ptzdR_ratio_final");
*/
  
  h1_jetpt_final->Write("h1_jetpt_final");
  h1_jetpt_reco->Write("h1_jetpt_reco");
  h1_jetpt_truth->Write("h1_jetpt_truth");
  h1_correct_jetpt->Write("h1_jetpt_unfolded_truth_ratio");
  h2_ptzjt_ratio->Write();
  h2_ptzjt_ratio_final->Write();  
  h2_ptzjt_ratio_vecfinal->Write();
  h2_ptzjt_pull->Write();  
  h2_ptzjt_pull_final->Write();
  h2_ptzjt_pull_vecfinal->Write();
  h1_ptzjt_pulldist->Write();
  h1_ptzjt_pulldist_final->Write();
  h1_ptzjt_pulldist_vecfinal->Write();
    
  //file_write->Write();
  file_write->Close();
  //
}
