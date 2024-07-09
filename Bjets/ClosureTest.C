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

  TRandom3 *myRNG = new TRandom3();
  const int nRuns = 3;

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
  cout << string_data + TString(".root") << endl;
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
  //TH1D *h1_kt_truth = (TH1D *)file_truth->Get("kt");
  //TH1D *h1_dR_truth = (TH1D *)file_truth->Get("dR");
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
  // Multiply by purity
  h1_jetpt_final->Multiply(h1_purity_jetpt);
  RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters_z);
  // RooUnfoldIds unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters_kt);
  h1_jetpt_final = (TH1D *)unfold_jetpt.Hreco();
  
  cout << "Unfold successful" << endl;  

  // Divide by efficiency
  h1_jetpt_final->Divide(h1_efficiency_jetpt);

  TH1D *h1_jetpt_final_ratio = (TH1D *)h1_jetpt_final->Clone("h1_jetpt_final_ratio");
  // TH1D * h1_correct_jetpt = (TH1D*) h1_jetpt_reco->Clone("h1_correct_jetpt");
  h1_jetpt_final_ratio->Divide(h1_jetpt_truth);

  // h1_jetpt_final->Divide(h1_correct_jetpt);
  // h1_efficiency_recoJet_jetpt->Multiply(h1_correct_jetpt);
  
  
  /////////////////////   Normalize histograms /////////////////////////////////
  
  std::cout << "Normalizing hists..." << std::endl;

  int binlow_jet = h1_jetpt_truth->FindBin(ptMin);
  int binhigh_jet = h1_jetpt_truth->FindBin(ptMax);

  double Njets_reco = h1_jetpt_reco->Integral(binlow_jet, binhigh_jet);
  double Njets_truth = h1_jetpt_truth->Integral(binlow_jet, binhigh_jet);
  double Njets_final = h1_jetpt_final->Integral(binlow_jet, binhigh_jet);
  
  std::cout << "Njets_reco : " << Njets_reco << " Njets_truth : " << Njets_truth << " Njets_final : " << Njets_final << std::endl;

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create zjt histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  TH2D *h2_zjt_truth = (TH2D *)file_truth->Get("zjt");
  TH3D *h3_ptzjt_truth = (TH3D *)file_truth->Get("ptzjt");
  TH3D *h3_ptzjt = (TH3D *)file_reco->Get("ptzjt");
  TH3D *h3_ptzjt_data = (TH3D *)file_data->Get("ptzjt");  
  TH3D *h3_ptzjt_final = (TH3D *)h3_ptzjt->Clone("ptzjt_final");
  TH3D *h3_eff_ptzjt = (TH3D *)file_unfold->Get("efficiency_ptzjt");
  TH3D *h3_purity_ptzjt = (TH3D *)file_unfold->Get("purity_ptzjt");
  RooUnfoldResponse *response_ptzjt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzjt");
  
  // Multiply by purity  
  h3_ptzjt_final->Multiply(h3_ptzjt_final, h3_purity_ptzjt);
  RooUnfoldBayes unfold_ptzjt(response_ptzjt, h3_ptzjt_final, NumIters_kt);
  // RooUnfoldIds unfold_ptzjt(response_ptzjt, h3_ptzjt_final, NumIters_kt);
  h3_ptzjt_final = (TH3D *)unfold_ptzjt.Hreco();
  // Divide by efficiency  
  h3_ptzjt_final->Divide(h3_ptzjt_final, h3_eff_ptzjt);
  //
  int binlow = h3_ptzjt->GetZaxis()->FindBin(ptMin + 0.1);
  int binhigh = h3_ptzjt->GetZaxis()->FindBin(ptMax - 0.1);
  int binlowz = h3_ptzjt->GetXaxis()->FindBin(0.0);
  int binhighz = h3_ptzjt->GetXaxis()->FindBin(1.1);
  int binlowjt = h3_ptzjt->GetYaxis()->FindBin(0.0);
  int binhighjt = h3_ptzjt->GetYaxis()->FindBin(10.0);
  //

  h3_ptzjt_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzjt_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);
  //h3_ptzjt_vecfinal->GetZaxis()->SetRangeUser(ptMin, ptMax);

  h3_ptzjt->GetZaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH2D *h2_ptzjt_final = (TH2D *)h3_ptzjt_final->Project3D("zjt_final_yx");
  //TH2D *h2_ptzjt_vecfinal = (TH2D *)h3_ptzjt_vecfinal->Project3D("zjt_vecfinal_yx");
  TH2D *h2_ptzjt = (TH2D *)h3_ptzjt->Project3D("zjt_yx");
  TH2D *h2_ptzjt_truth = (TH2D *)h3_ptzjt_truth->Project3D("zjt_truth_yx");
  //
  h2_ptzjt_final->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_ptzjt_final->GetXaxis()->SetRange(binlowz, binhighz);
  //h2_ptzjt_vecfinal->GetYaxis()->SetRange(binlowjt, binhighjt);
  //h2_ptzjt_vecfinal->GetXaxis()->SetRange(binlowz, binhighz);
  h2_ptzjt_truth->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_ptzjt_truth->GetXaxis()->SetRange(binlowz, binhighz);
  
  
  // This will depend on results of 1D jet unfolding
  h2_ptzjt_final->Scale(1. / Njets_final, "width");
  //h2_ptzjt_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h2_ptzjt_truth->Scale(1. / Njets_truth, "width");

  // h2_ptzjt_vecfinal->Scale(1. / Njets_vecfinal, "width");
  // h2_ptzjt_final->Scale(1. / 0.98);

  TH2D *h2_ptzjt_ratio = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_ratio");
  TH2D *h2_ptzjt_ratio_final = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_ratio_final");
  TH2D *h2_ptzjt_pull_final = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_pull_final");

  TH2D *h2_ptzjt_ratio_vecfinal = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_ratio_vecfinal");
  //TH2D *h2_ptzjt_pull_vecfinal = (TH2D *)h2_ptzjt->Clone("h2_ptzjt_pull_vecfinal");

  TH2D *h2_ptzjt_pull = (TH2D *)h2_zjt_truth->Clone("ptzjt_pull");

  TH1D *h1_ptzjt_pulldist = new TH1D("ptzjt_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_ptzjt_pulldist_final = new TH1D("ptzjt_pulldist_final", "", 20, -4.5, 4.5);
  //TH1D *h1_ptzjt_pulldist_vecfinal = new TH1D("ptzjt_pulldist_vecfinal", "", 20, -4.5, 4.5);

  h2_ptzjt_ratio->Divide(h2_ptzjt, h2_ptzjt_truth);
  h2_ptzjt_ratio_final->Divide(h2_ptzjt_final, h2_ptzjt_truth);
  //h2_ptzjt_ratio_vecfinal->Divide(h2_ptzjt_vecfinal, h2_ptzjt_truth);

  h2_ptzjt_ratio_final->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_ptzjt_ratio_final->GetXaxis()->SetRange(binlowz, binhighz);

  h2_ptzjt_pull_final->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_ptzjt_pull_final->GetXaxis()->SetRange(binlowz, binhighz);

  //h2_ptzjt_ratio_vecfinal->GetYaxis()->SetRange(binlowjt, binhighjt);
  //h2_ptzjt_ratio_vecfinal->GetXaxis()->SetRange(binlowz, binhighz);

  //h2_ptzjt_pull_vecfinal->GetYaxis()->SetRange(binlowjt, binhighjt);
  //h2_ptzjt_pull_vecfinal->GetXaxis()->SetRange(binlowz, binhighz);

  GetPullsRatio(h2_ptzjt_ratio, h2_ptzjt_pull, h1_ptzjt_pulldist);
  GetPullsRatio(h2_ptzjt_ratio_final, h2_ptzjt_pull_final, h1_ptzjt_pulldist_final);
  //GetPullsRatio(h2_ptzjt_ratio_vecfinal, h2_ptzjt_pull_vecfinal, h1_ptzjt_pulldist_vecfinal);

  double ptzjt_pullperf1 = GetPullPerformance(h2_ptzjt_pull, 1);
  double ptzjt_pullperf2 = GetPullPerformance(h2_ptzjt_pull, 2);

  double ptzjt_pullperf1_final = GetPullPerformance(h2_ptzjt_pull_final, 1);
  double ptzjt_pullperf2_final = GetPullPerformance(h2_ptzjt_pull_final, 2);
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH2D *h2_ptzjt_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH3D *h3_ptzjt_clone = (TH3D *)h3_ptzjt->Clone(Form("ptzjt_clone%d", i));
    myRNG->SetSeed(time(0));
    SmearObservables(h3_ptzjt_clone, h3_ptzjt_data, myRNG);
    // Multiply by purity
    h3_ptzjt_clone->Multiply(h3_ptzjt_clone, h3_purity_ptzjt);
    RooUnfoldBayes unfold_ptzjt_clone(response_ptzjt, h3_ptzjt_clone, NumIters_kt);
    // RooUnfoldIds unfold_ptzjt(response_ptzjt, h3_ptzjt_clone, NumIters_kt);
    // unfold_ptzjt_clone.SetMeasuredCov((*covMatrix_ptzjt));

    h3_ptzjt_clone = (TH3D *)unfold_ptzjt_clone.Hreco();
    // Divide by efficiency
    h3_ptzjt_clone->Divide(h3_ptzjt_clone, h3_eff_ptzjt);
    h3_ptzjt_clone->GetZaxis()->SetRangeUser(ptMin, ptMax);

    TH2D *h2_ptzjt_clone = (TH2D *)h3_ptzjt_clone->Project3D(Form("zjt_clone%d_yx", i));

    h2_ptzjt_clone->GetYaxis()->SetRange(binlowjt, binhighjt);
    h2_ptzjt_clone->GetXaxis()->SetRange(binlowz, binhighz);
    h2_ptzjt_clone->Scale(1. / Njets_final, "width");
    TH2D *h2_ptzjt_ratio_clone = (TH2D *)h2_ptzjt_clone->Clone(Form("h2_ptzjt_ratio_clone%d", i));
    TH2D *h2_ptzjt_pull_clone = (TH2D *)h2_ptzjt_clone->Clone(Form("h2_ptzjt_pull_clone%d", i));
    h2_ptzjt_ratio_clone->Divide(h2_ptzjt_clone, h2_ptzjt_truth);

    h2_ptzjt_ratio_clone->GetYaxis()->SetRange(binlowjt, binhighjt);
    h2_ptzjt_ratio_clone->GetXaxis()->SetRange(binlowz, binhighz);

    h2_ptzjt_pull_clone->GetYaxis()->SetRange(binlowjt, binhighjt);
    h2_ptzjt_pull_clone->GetXaxis()->SetRange(binlowz, binhighz);

    if (i == 0)
    {
      h2_ptzjt_closure_error = (TH2D *)h2_ptzjt_ratio_clone->Clone("h2_ptzjt_closure_error");
      h2_ptzjt_closure_error->Reset(); // Reset the histogram to zero
    }
    // h2_ptzjt_closure_error->Add(h2_ptzjt_ratio_clone);
    // Loop over all bins and add in quadrature
    for (int x = 1; x <= h2_ptzjt_ratio_clone->GetNbinsX(); ++x)
    {
      for (int y = 1; y <= h2_ptzjt_ratio_clone->GetNbinsY(); ++y)
      {
        for (int z = 1; z <= h2_ptzjt_ratio_clone->GetNbinsZ(); ++z)
        {
          double binContent = 1. - h2_ptzjt_ratio_clone->GetBinContent(x, y, z);
          double sumContent = h2_ptzjt_closure_error->GetBinContent(x, y, z);
          h2_ptzjt_closure_error->SetBinContent(x, y, z, sumContent + binContent * binContent);

          double binError = 1. - h2_ptzjt_ratio_clone->GetBinError(x, y, z);
          double sumError = h2_ptzjt_closure_error->GetBinError(x, y, z);
          h2_ptzjt_closure_error->SetBinError(x, y, z, sumError + binError * binError);
        }
      }
    }
  }

  // h2_ptzjt_closure_error->Scale(1.0 / nRuns);
  // Take the square root of the final sum histogram to get the quadrature sum
  for (int x = 1; x <= h2_ptzjt_closure_error->GetNbinsX(); ++x)
  {
    for (int y = 1; y <= h2_ptzjt_closure_error->GetNbinsY(); ++y)
    {
      for (int z = 1; z <= h2_ptzjt_closure_error->GetNbinsZ(); ++z)
      {
        double sumContent = h2_ptzjt_closure_error->GetBinContent(x, y, z);
        h2_ptzjt_closure_error->SetBinContent(x, y, z, TMath::Sqrt(sumContent) / TMath::Sqrt(nRuns - 1));

        double sumError = h2_ptzjt_closure_error->GetBinError(x, y, z);
        h2_ptzjt_closure_error->SetBinError(x, y, z, TMath::Sqrt(sumError) / TMath::Sqrt(nRuns - 1));
      }
    }
  }
  GetPullsRatio(h2_ptzjt_closure_error, h2_ptzjt_pull_final, h1_ptzjt_pulldist_final);


  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create z histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH1D *h1_z_truth = (TH1D *)file_truth->Get("z");
  TH2D *h2_ptz_truth = (TH2D *)file_truth->Get("ptz");
  TH2D *h2_ptz = (TH2D *)file_reco->Get("ptz");
  TH2D *h2_ptz_data = (TH2D *)file_data->Get("ptz");  
  TH2D *h2_ptz_final = (TH2D *)h2_ptz->Clone("ptz_final");
  TH2D *h2_eff_ptz = (TH2D *)file_unfold->Get("efficiency_ptz");
  TH2D *h2_purity_ptz = (TH2D *)file_unfold->Get("purity_ptz");
  RooUnfoldResponse *response_ptz = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptz");
  
  // Multiply by purity  
  h2_ptz_final->Multiply(h2_ptz_final, h2_purity_ptz);
  h2_purity_ptz->Write();
  h2_eff_ptz->Write();
  RooUnfoldBayes unfold_ptz(response_ptz, h2_ptz_final, NumIters_kt);

  h2_ptz_final = (TH2D *)unfold_ptz.Hreco();
  // Divide by efficiency  
  h2_ptz_final->Divide(h2_ptz_final, h2_eff_ptz);

  h2_ptz_final->GetYaxis()->SetRangeUser(ptMin, ptMax);
  h2_ptz_truth->GetYaxis()->SetRangeUser(ptMin, ptMax);

  h2_ptz->GetYaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH1D *h1_z_final = (TH1D *)h2_ptz_final->ProjectionX("z_final");
  TH1D *h1_z = (TH1D *)h2_ptz->ProjectionX("z");
  TH1D *h1_z_truth = (TH1D *)h2_ptz_truth->ProjectionX("z_truth");
  //
  
  h1_z_final->GetXaxis()->SetRange(binlowz, binhighz);
  h1_z_truth->GetXaxis()->SetRange(binlowz, binhighz);
  
  // This will depend on results of 1D jet pt unfolding
  h1_z_final->Scale(1. / Njets_final, "width");
  //h2_ptz_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h1_z_truth->Scale(1. / Njets_truth, "width");
  h1_z->Scale(1. / Njets_reco, "width");  
  

  TH1D *h1_z_ratio = (TH1D *)h1_z->Clone("h1_z_ratio");
  TH1D *h1_z_ratio_final = (TH1D *)h1_z_final->Clone("h1_z_ratio_final"); 


  h1_z_ratio->Divide(h1_z, h1_z_truth);
  h1_z_ratio_final->Divide(h1_z_final, h1_z_truth);

  h1_z_ratio_final->GetXaxis()->SetRange(binlowz, binhighz);
 
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH1D *h1_z_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH2D *h2_ptz_clone = (TH2D *)h2_ptz->Clone(Form("ptz_clone%d", i));
    myRNG->SetSeed(time(0));
    SmearObservables(h2_ptz_clone, h2_ptz_data, myRNG);
    
    //std::cout << endl;
    //std::cout << "h2ptz before corrections : " << h2_ptz_clone->GetEntries() << std::endl;
    //std::cout << endl;    

    // Multiply by purity
    h2_ptz_clone->Multiply(h2_ptz_clone, h2_purity_ptz);
    
    RooUnfoldBayes unfold_ptz_clone(response_ptz, h2_ptz_clone, NumIters_kt);
    h2_ptz_clone = (TH2D *)unfold_ptz_clone.Hreco();
    
    // Divide by efficiency    
    h2_ptz_clone->Divide(h2_ptz_clone, h2_eff_ptz);
    
    //std::cout << endl;    
    //std::cout << "h2ptz after corrections : " << h2_ptz_clone->GetEntries() << std::endl;
    //std::cout << endl;
            
    h2_ptz_clone->GetYaxis()->SetRangeUser(ptMin, ptMax);
    
       
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]
    TH1D *h1_z_clone = (TH1D *)h2_ptz_clone->ProjectionX(Form("z_clone%d", i));
    //TH1D *h1_z_clone_20_100 = (TH1D *)h2_ptz_clone->ProjectionX(Form("z_clone_20_100_%d", i), 3, 5);  


    h1_z_clone->GetXaxis()->SetRange(binlowz, binhighz);
    h1_z_clone->GetXaxis()->SetTitle("z");
    
    //h1_z_clone_20_100->GetXaxis()->SetRange(binlowz, binhighz);  
    //h1_z_clone_20_100->GetYaxis()->SetTitle("z");    
    
    //h1_z_truth_20_100->GetXaxis()->SetRange(binlowz, binhighz);
    //h1_z_truth_20_100->GetYaxis()->SetTitle("z");   
    
             
    h1_z_clone->Scale(1. / Njets_final, "width");

    std::cout << endl;    
    std::cout << "h1_z after norm : " << h1_z_clone->GetEntries() << std::endl;
    std::cout << endl;    
    
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]    
    //h1_z_clone_20_100->Scale(1./h1_jetpt_final->Integral(3,5), "width");     
    //h1_z_truth_20_100->Scale(1./h1_jetpt_truth->Integral(3,5), "width");         
    
    
    TRatioPlot *z_ratio_clone = new TRatioPlot(h1_z_clone, h1_z_truth);

    TLegend *leg_z = new TLegend(0.8, 0.8, 1.0, 1.0);
    leg_z->AddEntry(h1_z_clone, "l");
    leg_z->AddEntry(h1_z_truth,"l");
    //z_ratio_clone->Draw();
    TPad *p = z_ratio_clone->GetUpperPad();    
    TLegend *leg = p->BuildLegend();
    leg_z->Draw();
    p->Modified(); p->Update();      
    
    z_ratio_clone->Write(Form("z_ratio_clone_%d", i));    

 
    

    //TRatioPlot *z_ratio_clone_20_100 = new TRatioPlot(h1_z_clone_20_100, h1_z_truth_20_100);       
    //z_ratio_clone_20_100->Write(Form("z_ratio_clone_%d_20_100", i));    
  
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]        
    TH1D *h1_z_ptbinned[ptbinsize-2], *h1_z_truth_ptbinned[ptbinsize-2];
    TRatioPlot *h1_z_ptbinned_ratio[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h1_z_ptbinned[i] = (TH1D *)h2_ptz_clone->ProjectionX(Form("z_run%d_pt%d", i,j), j+1, j+1);    
        h1_z_truth_ptbinned[i] = (TH1D *)h2_ptz_truth->ProjectionX(Form("z_truth_run%d_pt%d", i,j), j+1, j+1);
        h1_z_ptbinned[i]->GetXaxis()->SetRange(binlowz, binhighz);
        h1_z_truth_ptbinned[i]->GetXaxis()->SetRange(binlowz, binhighz);
        h1_z_ptbinned[i]->GetXaxis()->SetTitle("z");
        h1_z_truth_ptbinned[i]->GetXaxis()->SetTitle("z");
        
        h1_z_ptbinned[i]->Scale(1./h1_jetpt_final->Integral(j+1, j+1));
        h1_z_truth_ptbinned[i]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1));
        h1_z_ptbinned_ratio[i] = new TRatioPlot(h1_z_ptbinned[i], h1_z_truth_ptbinned[i]);
        h1_z_ptbinned_ratio[i]->Write(Form("z_ratio_%d_pt%d", i,j));                 
    }
/*
    TH1D *h1_ptz_ratio_clone = (TH1D *)h1_ptz_clone->Clone(Form("z_ratio_clone%d", i));
    TH1D *h1_ptz_ratio_clone_20_100 = (TH1D *)h1_ptz_clone_20_100->Clone(Form("z_ratio_clone%d_20_100", i));   
    TH1D *h1_ptz_ratio_clone_20_30 = (TH1D *)h1_ptz_clone_20_30->Clone(Form("z_ratio_clone%d_20_30", i));  
    TH1D *h1_ptz_ratio_clone_30_50 = (TH1D *)h1_ptz_clone_30_50->Clone(Form("z_ratio_clone%d_30_50", i));  
    TH1D *h1_ptz_ratio_clone_50_100 = (TH1D *)h1_ptz_clone_50_100->Clone(Form("z_ratio_clone%d_50_100", i));                 
    TH1D *h1_ptz_pull_clone = (TH1D *)h1_ptz_clone->Clone(Form("z_pull_clone%d", i));
    
    
    h1_ptz_ratio_clone->Divide(h1_ptz_clone, h1_ptz_truth);
    h1_ptz_ratio_clone_20_100->Divide(h1_ptz_clone_20_100, h1_ptz_truth_20_100);   
    h1_ptz_ratio_clone_20_100->Divide(h1_ptz_clone_20_30, h1_ptz_truth_20_30); 
    h1_ptz_ratio_clone_20_100->Divide(h1_ptz_clone_30_50, h1_ptz_truth_30_50); 
    h1_ptz_ratio_clone_20_100->Divide(h1_ptz_clone_50_100, h1_ptz_truth_50_100);              

    h1_ptz_ratio_clone->GetXaxis()->SetRange(binlowz, binhighz);
    h1_ptz_ratio_clone_20_100->GetXaxis()->SetRange(binlowz, binhighz);
    h1_ptz_ratio_clone_20_30->GetXaxis()->SetRange(binlowz, binhighz);
    h1_ptz_ratio_clone_30_50->GetXaxis()->SetRange(binlowz, binhighz);
    h1_ptz_ratio_clone_50_100->GetXaxis()->SetRange(binlowz, binhighz);            
*/
  }
  
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create jt histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH1D *h1_jt_truth = (TH1D *)file_truth->Get("jt");
  TH2D *h2_ptjt_truth = (TH2D *)file_truth->Get("ptjt");
  TH2D *h2_ptjt = (TH2D *)file_reco->Get("ptjt");
  TH2D *h2_ptjt_data = (TH2D *)file_data->Get("ptjt");  
  TH2D *h2_ptjt_final = (TH2D *)h2_ptjt->Clone("ptjt_final");
  TH2D *h2_eff_ptjt = (TH2D *)file_unfold->Get("efficiency_ptjt");
  TH2D *h2_purity_ptjt = (TH2D *)file_unfold->Get("purity_ptjt");
  RooUnfoldResponse *response_ptjt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptjt");
  
  // Multiply by purity  
  h2_ptjt_final->Multiply(h2_ptjt_final, h2_purity_ptjt);
  RooUnfoldBayes unfold_ptjt(response_ptjt, h2_ptjt_final, NumIters_kt);

  h2_ptjt_final = (TH2D *)unfold_ptjt.Hreco();
  // Divide by efficiency  
  h2_ptjt_final->Divide(h2_ptjt_final, h2_eff_ptjt);

  h2_ptjt_final->GetYaxis()->SetRangeUser(ptMin, ptMax);
  h2_ptjt_truth->GetYaxis()->SetRangeUser(ptMin, ptMax);

  h2_ptjt->GetYaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH1D *h1_jt_final = (TH1D *)h2_ptjt_final->ProjectionX("jt_final");
  TH1D *h1_jt = (TH1D *)h2_ptjt->ProjectionX("jt");
  TH1D *h1_jt_truth = (TH1D *)h2_ptjt_truth->ProjectionX("jt_truth");
  //
  
  h1_jt_final->GetXaxis()->SetRange(binlowjt, binhighjt);
  h1_jt_truth->GetXaxis()->SetRange(binlowjt, binhighjt);
  
  // This will depend on results of 1D jet pt unfolding
  h1_jt_final->Scale(1. / Njets_final, "width");
  //h2_ptjt_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h1_jt_truth->Scale(1. / Njets_truth, "width");
  h1_jt->Scale(1. / Njets_reco, "width");  
  

  TH1D *h1_jt_ratio = (TH1D *)h1_jt->Clone("h1_jt_ratio");
  TH1D *h1_jt_ratio_final = (TH1D *)h1_jt_final->Clone("h1_jt_ratio_final"); 


  h1_jt_ratio->Divide(h1_jt, h1_jt_truth);
  h1_jt_ratio_final->Divide(h1_jt_final, h1_jt_truth);

  h1_jt_ratio_final->GetXaxis()->SetRange(binlowjt, binhighjt);
 
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH1D *h1_jt_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH2D *h2_ptjt_clone = (TH2D *)h2_ptjt->Clone(Form("ptjt_clone%d", i));
    myRNG->SetSeed(time(0));
    SmearObservables(h2_ptjt_clone, h2_ptjt_data, myRNG);  

    // Multiply by purity
    h2_ptjt_clone->Multiply(h2_ptjt_clone, h2_purity_ptjt);
    RooUnfoldBayes unfold_ptjt_clone(response_ptjt, h2_ptjt_clone, NumIters_kt);
    h2_ptjt_clone = (TH2D *)unfold_ptjt_clone.Hreco();
    // Divide by efficiency    
    h2_ptjt_clone->Divide(h2_ptjt_clone, h2_eff_ptjt);
    h2_ptjt_clone->GetYaxis()->SetRangeUser(ptMin, ptMax);  
       
    TH1D *h1_jt_clone = (TH1D *)h2_ptjt_clone->ProjectionX(Form("jt_clone%d", i));                        
    h1_jt_clone->GetXaxis()->SetRange(binlowjt, binhighjt);   
    h1_jt_clone->GetXaxis()->SetTitle("j_{T} (GeV/c)");
    h1_jt_clone->Scale(1. / Njets_final, "width");     
   
    TRatioPlot *jt_ratio_clone = new TRatioPlot(h1_jt_clone, h1_jt_truth);          
    jt_ratio_clone->Write(Form("jt_ratio_clone_%d", i));

    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]        
    TH1D *h1_jt_ptbinned[ptbinsize-2], *h1_jt_truth_ptbinned[ptbinsize-2];
    TRatioPlot *h1_jt_ptbinned_ratio[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h1_jt_ptbinned[i] = (TH1D *)h2_ptjt_clone->ProjectionX(Form("jt_run%d_pt%d", i,j), j+1, j+1);    
        h1_jt_truth_ptbinned[i] = (TH1D *)h2_ptjt_truth->ProjectionX(Form("jt_truth_run%d_pt%d", i,j), j+1, j+1);
        h1_jt_ptbinned[i]->GetXaxis()->SetRange(binlowjt, binhighjt);
        h1_jt_truth_ptbinned[i]->GetXaxis()->SetRange(binlowjt, binhighjt);
        h1_jt_ptbinned[i]->GetXaxis()->SetTitle("j_{T} (GeV/c)");
        h1_jt_truth_ptbinned[i]->GetXaxis()->SetTitle("j_{T} (GeV/c)");
        
        h1_jt_ptbinned[i]->Scale(1./h1_jetpt_final->Integral(j+1, j+1));
        h1_jt_truth_ptbinned[i]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1));
        h1_jt_ptbinned_ratio[i] = new TRatioPlot(h1_jt_ptbinned[i], h1_jt_truth_ptbinned[i]);
        h1_jt_ptbinned_ratio[i]->Write(Form("jt_ratio_%d_pt%d", i,j));                 
    }      
    
  }  
  
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create r histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH1D *h1_r_truth = (TH1D *)file_truth->Get("r");
  TH2D *h2_ptr_truth = (TH2D *)file_truth->Get("ptr");
  TH2D *h2_ptr = (TH2D *)file_reco->Get("ptr");
  TH2D *h2_ptr_data = (TH2D *)file_data->Get("ptr");  
  TH2D *h2_ptr_final = (TH2D *)h2_ptr->Clone("ptr_final");
  TH2D *h2_eff_ptr = (TH2D *)file_unfold->Get("efficiency_ptr");
  TH2D *h2_purity_ptr = (TH2D *)file_unfold->Get("purity_ptr");
  RooUnfoldResponse *response_ptr = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptr");
  
  // Multiply by purity  
  h2_ptr_final->Multiply(h2_ptr_final, h2_purity_ptr);
  RooUnfoldBayes unfold_ptr(response_ptr, h2_ptr_final, NumIters_kt);

  h2_ptr_final = (TH2D *)unfold_ptr.Hreco();
  // Divide by efficiency  
  h2_ptr_final->Divide(h2_ptr_final, h2_eff_ptr);
  
  int binlowr = h2_ptr->GetXaxis()->FindBin(0.0);
  int binhighr = h2_ptr->GetXaxis()->FindBin(0.5);  

  h2_ptr_final->GetYaxis()->SetRangeUser(ptMin, ptMax);
  h2_ptr_truth->GetYaxis()->SetRangeUser(ptMin, ptMax);

  h2_ptr->GetYaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH1D *h1_r_final = (TH1D *)h2_ptr_final->ProjectionX("r_final");
  TH1D *h1_r = (TH1D *)h2_ptr->ProjectionX("r");
  TH1D *h1_r_truth = (TH1D *)h2_ptr_truth->ProjectionX("r_truth");
  //
  
  h1_r_final->GetXaxis()->SetRange(binlowr, binhighr);
  h1_r_truth->GetXaxis()->SetRange(binlowr, binhighr);
  
  // This will depend on results of 1D jet pt unfolding
  h1_r_final->Scale(1. / Njets_final, "width");
  //h2_ptr_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h1_r_truth->Scale(1. / Njets_truth, "width");
  h1_r->Scale(1. / Njets_reco, "width");  
  

  TH1D *h1_r_ratio = (TH1D *)h1_r->Clone("h1_r_ratio");
  TH1D *h1_r_ratio_final = (TH1D *)h1_r_final->Clone("h1_r_ratio_final"); 


  h1_r_ratio->Divide(h1_r, h1_r_truth);
  h1_r_ratio_final->Divide(h1_r_final, h1_r_truth);

  h1_r_ratio_final->GetXaxis()->SetRange(binlowr, binhighr);
 
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH1D *h1_r_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH2D *h2_ptr_clone = (TH2D *)h2_ptr->Clone(Form("ptr_clone%d", i));
    myRNG->SetSeed(time(0));
    SmearObservables(h2_ptr_clone, h2_ptr_data, myRNG);

    // Multiply by purity
    h2_ptr_clone->Multiply(h2_ptr_clone, h2_purity_ptr);
    
    RooUnfoldBayes unfold_ptr_clone(response_ptr, h2_ptr_clone, NumIters_kt);
    h2_ptr_clone = (TH2D *)unfold_ptr_clone.Hreco();
    
    // Divide by efficiency    
    h2_ptr_clone->Divide(h2_ptr_clone, h2_eff_ptr);
    
    h2_ptr_clone->GetYaxis()->SetRangeUser(ptMin, ptMax);
         
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]
    TH1D *h1_r_clone = (TH1D *)h2_ptr_clone->ProjectionX(Form("r_clone%d", i));                     
    h1_r_clone->GetXaxis()->SetRange(binlowr, binhighr);    
    h1_r_clone->GetXaxis()->SetTitle("r");    
    h1_r_clone->Scale(1. / Njets_final, "width");   
    TRatioPlot *r_ratio_clone = new TRatioPlot(h1_r_clone, h1_r_truth);     
    r_ratio_clone->Write(Form("r_ratio_clone_%d", i));
    
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]        
    TH1D *h1_r_ptbinned[ptbinsize-2], *h1_r_truth_ptbinned[ptbinsize-2];
    TRatioPlot *h1_r_ptbinned_ratio[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h1_r_ptbinned[i] = (TH1D *)h2_ptr_clone->ProjectionX(Form("r_run%d_pt%d", i,j), j+1, j+1);    
        h1_r_truth_ptbinned[i] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_run%d_pt%d", i,j), j+1, j+1);
        h1_r_ptbinned[i]->GetXaxis()->SetRange(binlowr, binhighr);
        h1_r_truth_ptbinned[i]->GetXaxis()->SetRange(binlowr, binhighr);
        h1_r_ptbinned[i]->GetXaxis()->SetTitle("r");
        h1_r_truth_ptbinned[i]->GetXaxis()->SetTitle("r");
        
        h1_r_ptbinned[i]->Scale(1./h1_jetpt_final->Integral(j+1, j+1));
        h1_r_truth_ptbinned[i]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1));
        h1_r_ptbinned_ratio[i] = new TRatioPlot(h1_r_ptbinned[i], h1_r_truth_ptbinned[i]);
        h1_r_ptbinned_ratio[i]->Write(Form("r_ratio_%d_pt%d", i,j));                 
    }         
  }
    
  /*

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================jt Pull Performance====================================" << endl;
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
  TRatioPlot *jetpt_ratio = new TRatioPlot(h1_jetpt_final, h1_jetpt_truth);
  jetpt_ratio->Write("jetpt_ratio");
  h2_ptzjt_ratio->Write();
  h2_ptzjt_ratio_final->Write();  
  h2_ptzjt_pull->Write();  
  h2_ptzjt_pull_final->Write();
  h1_ptzjt_pulldist->Write();
  h1_ptzjt_pulldist_final->Write();
  //z_ratio_clone->Write("z_ratio_clone");      


  //file_write->Write();
  file_write->Close();
  //
}
