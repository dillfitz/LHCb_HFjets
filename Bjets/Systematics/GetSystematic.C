#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "../Settings.h"
#include <TF1.h>
#include <TLatex.h>
#include <THStack.h>
#include <TChain.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TEfficiency.h>
#include <TRatioPlot.h>
#include "../../Helpers.h"
using namespace std;

void GetSystematic(int NumEvts = -1, int dataset1 = 91599, int dataset2 = 91599,
                   bool chargedJetCut = false,
                   bool WTA_cut = false,
                   double minimum_dR = 0.1,
                   int NumIters = 4,
                   double rho = 0.,
                   bool DoJER = false,
                   int DoJES = 0,
                   bool DoFSPEff = false,
                   bool DoFSPPT = false,
                   bool DoGhostCut = false,
                   int DoTrackEff = 0,
                   int DoPIDEff = 0,
                   int DoTrigEff = 0,
                   bool DoRecSelEff = 0,
                   bool DoSignalSys = 0,
                   int DoMassFit = 0,
                   int DoIterSys = 0,
                   bool DoUnfoldPrior = 0,
                   bool DoReverse = false,
                   bool DoJetID = false)
{

  TString string_data_nominal, string_data_test,
      string_unfold, string_unfold_test, extension;
  TString str_followHard, str_ghost, str_charged, str_Mag, str_flavor;
  TString string_systype;
  TString loc_rootfiles_data("../../../root_files/Bjets/");
  TString loc_rootfiles_MC("../../../root_files/BjetsMC/");
  TString loc_plots("../../../plots/Bjets/");

  bool ghostCut1(true), ghostCut2(true);
  int chargedJetCut1 = chargedJetCut;
  int chargedJetCut2 = chargedJetCut;
  bool followHardest1 = false;
  bool followHardest2 = false;

  int JetMeth1 = (dataset1 / 1000) % 10;
  int flavor1 = (dataset1 / 100) % 10;
  int ptRange1 = (dataset1 / 10) % 10;
  int Mag1 = (dataset1 / 1) % 10;

  int JetMeth2 = (dataset2 / 1000) % 10;
  int flavor2 = (dataset2 / 100) % 10;
  int ptRange2 = (dataset2 / 10) % 10;
  int Mag2 = (dataset2 / 1) % 10;

  int dataset_test = 91599;
  int dataset_unfold = 91599;
  double ghostProb_test = ghostProb;
  int NumIters_test = NumIters;

  if (DoReverse)
    string_systype = "reverse_";
  if (DoJES == 1)
    string_systype = "JESPos_";
  if (DoJES == 2)
    string_systype = "JESNeg_";
  if (DoJER)
    string_systype = "JER_";
  if (DoFSPEff)
    string_systype = "fspeff_";
  if (DoFSPPT)
    string_systype = "fsppt_";
  if (DoGhostCut)
    string_systype = "ghostcut_";
  if (DoGhostCut)
    ghostProb_test = 0.3;

  if (DoJetID)
    string_systype = "jetid_";
  if (DoTrackEff == 1)
    string_systype = "trackingsysup_";
  if (DoTrackEff == 2)
    string_systype = "trackingsysdown_";
  if (DoPIDEff == 1)
    string_systype = "pidsysup_";
  if (DoPIDEff == 2)
    string_systype = "pidsysdown_";
  if (DoTrigEff == 1)
    string_systype = "trigsysup_";
  if (DoTrigEff == 2)
    string_systype = "trigsysdown_";
  if (DoMassFit == 1)
    string_systype = "massfitsysnear_";
  if (DoMassFit == 2)
    string_systype = "massfitsysfar_";
  if (DoRecSelEff)
    string_systype = "recselsys_";
  if (DoSignalSys)
    string_systype = "signalsys_";
  if (DoUnfoldPrior)
    string_systype = "priorsys_";
  if (DoIterSys == 1)
  {
    string_systype = "itersysup_";
    NumIters_test++;
  }
  if (DoIterSys == 2)
  {
    string_systype = "itersysdown_";
    NumIters_test--;
  }

  TString str_Mag1 = "";
  TString str_pT1 = "";
  TString str_level1 = "";
  TString str_followHard1 = "";
  TString str_flavor1 = "";
  TString str_ghost1 = "";

  TString str_Mag2 = "";
  TString str_pT2 = "";
  TString str_level2 = "";
  TString str_followHard2 = "";
  TString str_flavor2 = "";
  TString str_ghost2 = "";

  TString str_charged1 = "";
  TString str_charged2 = "";
  TString str_DTF(""), str_PID("");
  TString str_WTA("");

  if (DTF_cut)
    str_DTF = "_DTF";
  if (PID_cut)
    str_PID = "_PID";
  if (WTA_cut)
    str_WTA = "_WTA";

  if (Mag1 == 0)
    str_Mag1 = "_MD";
  else if (Mag1 == 1)
    str_Mag1 = "_MU";

  if (flavor1 == 1)
    str_flavor1 = "_udsg";
  else if (flavor1 == 4)
    str_flavor1 = "_c";
  else if (flavor1 == 5)
    str_flavor1 = "_b";

  if (followHardest1)
    str_followHard1 = "_hard";
  else
    str_followHard1 = "_HF";

  if (ghostCut1)
    str_ghost1 = Form("_ghost_%.1f", ghostProb);

  if (chargedJetCut1)
    str_charged1 = "_charge";

  if (Mag2 == 0)
    str_Mag2 = "_MD";
  else if (Mag2 == 1)
    str_Mag2 = "_MU";

  if (flavor2 == 1)
    str_flavor2 = "_udsg";
  else if (flavor2 == 4)
    str_flavor2 = "_c";
  else if (flavor2 == 5)
    str_flavor2 = "_b";

  if (followHardest2)
    str_followHard2 = "_hard";
  else
    str_followHard2 = "_HF";

  if (ghostCut2)
    str_ghost2 = Form("_ghost_%.1f", ghostProb);
  if (DoGhostCut)
    str_ghost2 = Form("_ghost_%.1f", 0.3);
  if (chargedJetCut2)
    str_charged2 = "_charge";

  string_data_nominal = loc_rootfiles_data + TString("data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + str_charged1 + str_Mag1 + str_flavor1 + str_DTF + str_PID + str_WTA + Form("_%d", dataset1);
  string_data_test = TString("data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + str_ghost2 + str_charged2 + str_Mag2 + str_flavor2 + str_DTF + str_PID + str_WTA + Form("_%d", dataset2);
  string_unfold = loc_rootfiles_MC + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + Form("_dR_%.2f", minimum_dR) + str_charged1 + str_flavor1 + str_DTF + str_PID + str_WTA + Form("_%d", dataset_unfold);
  if (DoTrackEff != 0 || DoPIDEff != 0 || DoTrigEff != 0 || DoMassFit != 0 || DoIterSys != 0)
  {
    string_unfold_test = loc_rootfiles_MC + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + Form("_ghost_%.1f", ghostProb_test) + Form("_dR_%.2f", minimum_dR) + str_charged2 + str_flavor2 + str_DTF + str_PID + str_WTA + Form("_%d", dataset_test);
  }
  else
  {
    string_unfold_test = loc_rootfiles_MC + string_systype + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + Form("_ghost_%.1f", ghostProb_test) + Form("_dR_%.2f", minimum_dR) + str_charged2 + str_flavor2 + str_DTF + str_PID + str_WTA + Form("_%d", dataset_test);
  }
  // string_data = loc + "hists/data_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  // string_unfold = loc + "hists/unfold_reco_ev_-1_ptj_20150_eta_2.54.0_hard_ghost_0.5_udsg_93139.root";
  if (DoGhostCut || DoJetID || (DoTrackEff != 0) || (DoPIDEff != 0) || (DoTrigEff != 0) || (DoMassFit != 0) || (DoRecSelEff) || (DoSignalSys))
  {
    string_data_test = loc_rootfiles_data + string_systype + string_data_test;
  }
  else
  {
    string_data_test = loc_rootfiles_data + string_data_test;
  }
  cout << string_data_nominal << endl;
  cout << string_data_test << endl;
  cout << string_unfold << endl;
  cout << string_unfold_test << endl;

  extension = string_systype + TString("sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + Form("_dR_%.2f", minimum_dR) + str_charged1 + str_Mag1 + str_flavor1 + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset1);

  if (dataset1 != dataset2)
    extension += Form("_%d", dataset2);
  /////////////////////   Get Files /////////////////////////////////

  TFile *file_data_nominal = new TFile(string_data_nominal + TString(".root"), "READ");
  TFile *file_data_test = new TFile(string_data_test + TString(".root"), "READ");
  TFile *file_unfold = new TFile(string_unfold + TString(".root"), "READ");
  TFile *file_unfold_test = new TFile(string_unfold_test + TString(".root"), "READ");

  TFile *file_save = new TFile(loc_rootfiles_data + "Systematics/" + extension + ".root", "RECREATE");


  /////////////////////   Create z histograms /////////////////////////////////

  TH2D *h2_ptz_nominal = (TH2D *)file_data_nominal->Get("ptz");
  TH2D *h2_ptz_test = (TH2D *)file_data_test->Get("ptz");

  TH2D *h2_ptz_final_nominal = (TH2D *)h2_ptz_nominal->Clone("ptz_final_nominal");
  TH2D *h2_ptz_final_test = (TH2D *)h2_ptz_test->Clone("ptz_final_test");

  /////////////////////   Get jet pT Hists for Normalization /////////////////////////////////

  TH1D *h1_jetpt = (TH1D *)file_data_nominal->Get("Jet_pT");
  TH1D *h1_jetpt_test = (TH1D *)file_data_test->Get("Jet_pT");

  TH1D *h1_jetpt_final_nominal = (TH1D *)h1_jetpt->Clone("jetpt_final_nominal");
  TH1D *h1_jetpt_final_test = (TH1D *)h1_jetpt_test->Clone("jetpt_final_test");

  /////////////////////   Get Efficiency Hists /////////////////////////////////

  TH2D *h2_eff_ptz_nominal = (TH2D *)file_unfold->Get("efficiency_ptz");
  TH2D *h2_eff_ptz_test = (TH2D *)file_unfold_test->Get("efficiency_ptz");
  TH2D *h2_purity_ptz_nominal = (TH2D *)file_unfold->Get("purity_ptz");
  TH2D *h2_purity_ptz_test = (TH2D *)file_unfold_test->Get("purity_ptz");  

  TH1D *h1_eff_jetpt_nominal = (TH1D *)file_unfold->Get("efficiency_jetpt");
  TH1D *h1_eff_jetpt_test = (TH1D *)file_unfold_test->Get("efficiency_jetpt");
  TH1D *h1_purity_jetpt_nominal = (TH1D *)file_unfold->Get("purity_jetpt");
  TH1D *h1_purity_jetpt_test = (TH1D *)file_unfold_test->Get("purity_jetpt");

  /////////////////////   Get Response Matrices /////////////////////////////////

  RooUnfoldResponse *response_ptz_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptz");
  RooUnfoldResponse *response_ptz_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptz");
  
  RooUnfoldResponse *response_jetpt_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_jetpt");
  RooUnfoldResponse *response_jetpt_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_jetpt");

  /////////////////////  Correct Purities /////////////////////////////////

  h2_ptz_final_nominal->Multiply(h2_ptz_final_nominal, h2_purity_ptz_nominal);
  h2_ptz_final_test->Multiply(h2_ptz_final_test, h2_purity_ptz_test);
  
  h1_jetpt_final_nominal->Multiply(h1_jetpt_final_nominal, h1_purity_jetpt_nominal);
  h1_jetpt_final_test->Multiply(h1_jetpt_final_test, h1_purity_jetpt_test);  

  cout << "About to Unfold" << endl;

  // RooUnfoldids    unfold1D(response_jetpt, h1_jetpt_reco_purity, NumIters);

  /////////////////////   Create Unfold Objects and unfold /////////////////////////////////

  RooUnfoldBayes unfold_ptz_nominal(response_ptz_nominal, h2_ptz_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptz_test(response_ptz_test, h2_ptz_final_test, NumIters_test);

  RooUnfoldBayes unfold_jetpt_nominal(response_jetpt_nominal, h1_jetpt_final_nominal, NumIters);
  RooUnfoldBayes unfold_jetpt_test(response_jetpt_test, h1_jetpt_final_test, NumIters_test);

  cout << "Unfold successful" << endl;
  /////////////////////   Get Unfolded Distribution /////////////////////////////////
  // h1_jetpt_reco_purity_unfold = (TH1D*) unfold1D.Hreco();

  h2_ptz_final_nominal = (TH2D *)unfold_ptz_nominal.Hreco();
  h2_ptz_final_test = (TH2D *)unfold_ptz_test.Hreco();

  h1_jetpt_final_nominal = (TH1D *)unfold_jetpt_nominal.Hreco();
  h1_jetpt_final_test = (TH1D *)unfold_jetpt_test.Hreco();

  cout << "Got Unfolded Dist" << endl;
  /////////////////////  Correct for efficiency if needed /////////////////////////////////
  h2_ptz_final_nominal->Divide(h2_ptz_final_nominal, h2_eff_ptz_nominal);
  h2_ptz_final_test->Divide(h2_ptz_final_test, h2_eff_ptz_test);
  
  h1_jetpt_final_nominal->Divide(h1_jetpt_final_nominal, h1_eff_jetpt_nominal);
  h1_jetpt_final_test->Divide(h1_jetpt_final_test, h1_eff_jetpt_test);  
  

  cout << "Corrected for Eff" << endl;
  /////////////////////   Normalize histograms /////////////////////////////////

  int binlow_jet = h1_jetpt_final_nominal->FindBin(ptMin);
  int binhigh_jet = h1_jetpt_final_nominal->FindBin(ptMax);

  double Njets_nominal = h1_jetpt_final_nominal->Integral(binlow_jet, binhigh_jet);
  double Njets_test = h1_jetpt_final_test->Integral(binlow_jet, binhigh_jet);

  int binlow = h2_ptz_nominal->GetYaxis()->FindBin(ptMin + 0.1);
  int binhigh = h2_ptz_nominal->GetYaxis()->FindBin(ptMax - 0.1);

  h2_ptz_final_nominal->GetYaxis()->SetRange(binlow, binhigh);
  h2_ptz_final_test->GetYaxis()->SetRange(binlow, binhigh);

  TH1D *h1_z_ptbinned_final_nominal[ptbinsize-2], *h1_z_ptbinned_final_test[ptbinsize-2];
  TH1D *h1_z_ptbinned_ratio[ptbinsize-2], *h1_z_ptbinned_diff[ptbinsize-2];
  for (int j=2; j < ptbinsize; ++j)
  {

    h1_z_ptbinned_final_nominal[j-2] = (TH1D *)h2_ptz_final_nominal->ProjectionX(Form("z_nominal_pt%d",j), j+1, j+1);
    h1_z_ptbinned_final_test[j-2] = (TH1D *)h2_ptz_final_test->ProjectionX(Form("z_test_pt%d",j), j+1, j+1);       

    //h1_z_ptbinned_final_nominal[j-2]->GetXaxis()->SetRange(binlow, binhigh);
    //h1_z_ptbinned_final_test[j-2]->GetXaxis()->SetRange(binlow, binhigh);    

    //NormalizeHist(h1_z_ptbinned[j-2]_final_nominal);
    //NormalizeHist(h1_z_ptbinned[j-2]_final_test);
    
    h1_z_ptbinned_final_nominal[j-2]->Scale(1./h1_jetpt_final_nominal->GetBinContent(j+1));
    h1_z_ptbinned_final_test[j-2]->Scale(1./h1_jetpt_final_test->GetBinContent(j+1));    
    
    h1_z_ptbinned_ratio[j-2] = (TH1D*)h1_z_ptbinned_final_nominal[j-2]->Clone(Form("z_pt%d_ratio", j));
    h1_z_ptbinned_diff[j-2] = (TH1D*)h1_z_ptbinned_final_nominal[j-2]->Clone(Form("z_pt%d_diff", j));    
    
    /////////////////////   Compute ratios and pulls /////////////////////////////////
    h1_z_ptbinned_ratio[j-2]->Divide(h1_z_ptbinned_ratio[j-2], h1_z_ptbinned_final_test[j-2]);
    cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h1_z_ptbinned_ratio[j-2]) << endl;
    SubtractUnity(h1_z_ptbinned_ratio[j-2]);

    h1_z_ptbinned_diff[j-2]->Add(h1_z_ptbinned_diff[j-2], h1_z_ptbinned_final_test[j-2], 1, -1);
    SetHistErrCorr(h1_z_ptbinned_diff[j-2], h1_z_ptbinned_final_nominal[j-2], h1_z_ptbinned_final_test[j-2], rho);    
  }
/*
  /////////////////////   Create pull hists /////////////////////////////////

  TH2D *h2_ptktdR_pull = (TH2D *)h2_ptktdR_final_nominal->Clone("ptktdR_pull");
  TH1D *h1_ptktdR_pulldist = new TH1D("ptktdR_pulldist", "", 16, -4.5, 4.5);

  TH2D *h2_ptzdR_pull = (TH2D *)h2_ptzdR_final_nominal->Clone("ptzdR_pull");
  TH1D *h1_ptzdR_pulldist = new TH1D("ptzdR_pulldist", "", 16, -4.5, 4.5);

  TH2D *h2_ptthetaErad_pull = (TH2D *)h2_ptthetaErad_final_nominal->Clone("ptthetaErad_pull");
  TH1D *h1_ptthetaErad_pulldist = new TH1D("ptthetaErad_pulldist", "", 16, -4.5, 4.5);
*/


  //GetPulls(h2_ptktdR_diff, h2_ptktdR_pull, h1_ptktdR_pulldist);
/*
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
  gStyle->SetPaintTextFormat("4.5g");
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
  h2_ptktdR_final_test->Draw("COL0Z");

  ccan[ican]->cd(2);
  h1_ptktdR_pulldist->Draw("E SAME");
  h1_ptktdR_pulldist->Draw("HIST SAME");
  ccan[ican]->cd(3);
  // h2_ktdR_diff->Set
  h2_ptktdR_ratio->Draw("COL0Z TEXTE MIN0");
  h2_ptktdR_ratio->SetMinimum(-0.1);
  h2_ptktdR_ratio->SetMaximum(0.1);

  ccan[ican]->cd(4);
  h2_ptktdR_pull->Draw("COL0Z TEXT MIN0");
  h2_ptktdR_pull->SetMaximum(4.);
  h2_ptktdR_pull->SetMinimum(-4.);

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
  h2_ptzdR_final_test->Draw("COL0Z");

  ccan[ican]->cd(2);
  h1_ptzdR_pulldist->Draw("E SAME");
  h1_ptzdR_pulldist->Draw("HIST SAME");
  // h2_ktdR_->SetTitle("Data+Purity+Unfold; ;");
  ccan[ican]->cd(3);
  // h2_ktdR_diff->Set
  h2_ptzdR_ratio->Draw("COL0Z TEXTE MIN0");
  h2_ptzdR_ratio->SetMinimum(-0.1);
  h2_ptzdR_ratio->SetMaximum(0.1);

  ccan[ican]->cd(4);
  h2_ptzdR_pull->Draw("COL0Z TEXT MIN0");
  h2_ptzdR_pull->SetMaximum(4.);
  h2_ptzdR_pull->SetMinimum(-4.);

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
  //
*/
  file_save->Write();
  file_save->Close();
}
/*
int main(int argc, char *argv[])
{
  int NumIters = 3;
  int NumEvts = -1;
  int dataset1 = 91599;
  int dataset2 = 91599;
  bool isData = true;
  bool chargedJetCut = false;
  double rho = 0.;
  bool DoJER = false;
  int DoJES = 0;
  bool DoFSPPT = false;
  bool DoGhostCut = false;
  bool DoFSPEff = false;
  int DoTrackEff = 0;
  int DoTrigEff = false;
  int DoPIDEff = 0;
  bool DoRecSelEff = false;
  bool DoSignalSys = false;
  int DoMassFit = 0;
  bool SubtractGS = false;
  bool DoReverse = false;
  bool WTA_cut = true;
  int DoIterSys = 0;
  bool DoUnfoldPrior = false;
  double minimum_dR = 0.1;
  bool DoJetID = false;
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
    else if (arg == "-dataset1")
    {
      // std::cout << argv[i + 1] << std::endl;
      if (i + 1 < argc)
      {
        dataset1 = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-dataset1 option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-dataset2")
    {
      // std::cout << argv[i + 1] << std::endl;
      if (i + 1 < argc)
      {
        dataset2 = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-dataset2 option requires one argument." << std::endl;
        return 1;
      }
    }
    else if (arg == "-mindR")
    {
      // std::cout << argv[i + 1] << std::endl;
      if (i + 1 < argc)
      {
        minimum_dR = std::stod(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-mindR option requires one argument." << std::endl;
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
        DoTrigEff = std::stoi(argv[i + 1]);
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
        DoMassFit = stoi(argv[i + 1]);
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
    else if (arg == "-itersys")
    {
      if (i + 1 < argc)
      {
        DoIterSys = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-itersys option requires one argument." << std::endl;
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
    else if (arg == "-iters")
    {
      if (i + 1 < argc)
      {
        NumIters = std::stoi(argv[i + 1]);
        i++;
      }
      else
      {
        std::cerr << "-iters option requires one argument." << std::endl;
        return 1;
      }
    }
    else
    {
      std::cerr << "Unknown option: " << arg << std::endl;
      return 1;
    }
  }

  GetSystematic(NumEvts,
                dataset1,
                dataset2,
                chargedJetCut,
                WTA_cut,
                minimum_dR,
                NumIters,
                rho,
                DoJER,
                DoJES,
                DoFSPEff,
                DoFSPPT,
                DoGhostCut,
                DoTrackEff,
                DoPIDEff,
                DoTrigEff,
                DoRecSelEff,
                DoSignalSys,
                DoMassFit,
                DoIterSys,
                DoUnfoldPrior,
                DoReverse,
                DoJetID);
  return 0;
}
*/

