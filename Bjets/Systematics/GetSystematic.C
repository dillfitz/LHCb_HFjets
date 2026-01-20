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
                   int NumIters = 4,
                   double rho = 0.,
                   //bool DoJER = false,
                   //bool DoJES = false,
                   bool DoJESJER = false,
                   bool DoJetID = false,                   
                   int DoTrackEff = 0,
                   int DoPIDEff = 0,
                   int DoTrigEff = 0,
                   bool DoRecSelEff = false,
                   bool DoSignalSys = false,
                   int DoMassFit = 0,
                   int DoIterSys = 0,
                   bool DoUnfoldPrior = false,
                   bool DoTrackEff_SysCrossCheck = false)
{

  gStyle->SetPaintTextFormat("3.3f");
  
  TString string_data_nominal, string_data_test, string_unfold, string_unfold_test, extension;
  TString str_followHard, str_ghost, str_Mag, str_flavor;
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

  //if (DoJES)
  //  string_systype = "JES_";
  //if (DoJER)
  //  string_systype = "JER_";
  if (DoJESJER)
    string_systype = "JESJER_";
  if (DoJetID)
    string_systype = "jetid_";
  if (DoTrackEff == 1)
    string_systype = "trackingsysup_";
  if (DoTrackEff == 2)
    string_systype = "trackingsysdown_";
  if (DoTrackEff_SysCrossCheck && DoTrackEff !=0)
    string_systype = "crosscheck_" + string_systype;
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
  if (DoMassFit == 3)
    string_systype = "massfitsyslower_";
  if (DoMassFit == 4)
    string_systype = "massfitsysupper_";
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

  TString str_PID("");

  if (PID_cut)
    str_PID = "_PID";

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


  //string_data_nominal = loc_rootfiles_data + TString("data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + str_Mag1 + str_flavor1 + str_PID + Form("_%d", dataset1);
  string_data_nominal = loc_rootfiles_data + TString("corrected_data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + str_Mag1 + str_flavor1 + str_PID + Form("_iters_%d", NumIters) + Form("_%d", dataset1);
  string_data_test = TString("data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + str_ghost2 + str_Mag2 + str_flavor2 + str_PID  + Form("_%d", dataset2);
  //string_unfold = loc_rootfiles_MC + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + str_flavor1 + str_PID + Form("_%d", dataset_unfold);
  if (DoTrackEff != 0 || DoPIDEff != 0 || DoTrigEff != 0 || DoMassFit != 0 || DoIterSys != 0)
  {
    string_unfold_test = loc_rootfiles_MC + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + Form("_ghost_%.1f", ghostProb_test) + str_flavor2 + str_PID + Form("_%d", dataset_test);
  }
  else
  {
    string_unfold_test = loc_rootfiles_MC + string_systype + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + Form("_ghost_%.1f", ghostProb_test) + str_flavor2 + str_PID + Form("_%d", dataset_test);
  }

  if (DoJetID || (DoTrackEff != 0) || (DoPIDEff != 0) || (DoTrigEff != 0) || (DoMassFit != 0) || (DoRecSelEff) || (DoSignalSys))
  {
    string_data_test = loc_rootfiles_data + string_systype + string_data_test;
  }
  else
  {
    string_data_test = loc_rootfiles_data + string_data_test;
  }
  cout << string_data_nominal << endl;
  cout << string_data_test << endl;
  //cout << string_unfold << endl;
  cout << string_unfold_test << endl;

  extension = string_systype + TString("sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + str_Mag1 + str_flavor1 + str_PID + Form("_iters_%d", NumIters) + Form("_%d", dataset1);

  if (dataset1 != dataset2)
    extension += Form("_%d", dataset2);
  /////////////////////   Get Files /////////////////////////////////

  TFile *file_data_nominal = new TFile(string_data_nominal + TString(".root"), "READ");
  TFile *file_data_test = new TFile(string_data_test + TString(".root"), "READ");
  //TFile *file_unfold = new TFile(string_unfold + TString(".root"), "READ");
  TFile *file_unfold_test = new TFile(string_unfold_test + TString(".root"), "READ");

  TFile *file_save = new TFile(loc_rootfiles_data + "Systematics/" + extension + ".root", "RECREATE");


  /////////////////////   Create observable histograms /////////////////////////////////

  TH3D *h3_ptzjt_final_nominal = (TH3D *)file_data_nominal->Get("ptzjt_final");
  TH3D *h3_ptzjt_test = (TH3D *)file_data_test->Get("ptzjt");
  //TH3D *h3_ptzjt_final_nominal = (TH3D *)h3_ptzjt_nominal->Clone("ptzjt_final_nominal");
  TH3D *h3_ptzjt_final_test = (TH3D *)h3_ptzjt_test->Clone("ptzjt_final_test");
  
  TH3D *h3_ptzr_final_nominal = (TH3D *)file_data_nominal->Get("ptzr_final");
  TH3D *h3_ptzr_test = (TH3D *)file_data_test->Get("ptzr");   
  //TH3D *h3_ptzr_final_nominal = (TH3D *)h3_ptzr_nominal->Clone("ptzr_final_nominal");
  TH3D *h3_ptzr_final_test = (TH3D *)h3_ptzr_test->Clone("ptzr_final_test");  
  
  TH3D *h3_ptjtr_final_nominal = (TH3D *)file_data_nominal->Get("ptjtr_final");
  TH3D *h3_ptjtr_test = (TH3D *)file_data_test->Get("ptjtr");
  //TH3D *h3_ptjtr_final_nominal = (TH3D *)h3_ptjtr_nominal->Clone("ptjtr_final_nominal");
  TH3D *h3_ptjtr_final_test = (TH3D *)h3_ptjtr_test->Clone("ptjtr_final_test");   
    
  
  TH2D *h2_ptz_final_nominal = (TH2D *)file_data_nominal->Get("ptz_final");
  TH2D *h2_ptz_test = (TH2D *)file_data_test->Get("ptz");
  //TH2D *h2_ptz_final_nominal = (TH2D *)h2_ptz_nominal->Clone("ptz_final_nominal");
  TH2D *h2_ptz_final_test = (TH2D *)h2_ptz_test->Clone("ptz_final_test");
  
  TH2D *h2_ptjt_final_nominal = (TH2D *)file_data_nominal->Get("ptjt_final");
  TH2D *h2_ptjt_test = (TH2D *)file_data_test->Get("ptjt");   
  //TH2D *h2_ptjt_final_nominal = (TH2D *)h2_ptjt_nominal->Clone("ptjt_final_nominal");
  TH2D *h2_ptjt_final_test = (TH2D *)h2_ptjt_test->Clone("ptjt_final_test");  
  
  TH2D *h2_ptr_final_nominal = (TH2D *)file_data_nominal->Get("ptr_final");
  TH2D *h2_ptr_test = (TH2D *)file_data_test->Get("ptr");
  //TH2D *h2_ptr_final_nominal = (TH2D *)h2_ptr_nominal->Clone("ptr_final_nominal");
  TH2D *h2_ptr_final_test = (TH2D *)h2_ptr_test->Clone("ptr_final_test");   


  /////////////////////   Get Efficiency Hists /////////////////////////////////

  //TH3D *h3_eff_ptzjt_nominal = (TH3D *)file_unfold->Get("efficiency_ptzjt");
  TH3D *h3_eff_ptzjt_test = (TH3D *)file_unfold_test->Get("efficiency_ptzjt");
  //TH3D *h3_purity_ptzjt_nominal = (TH3D *)file_unfold->Get("purity_ptzjt");
  TH3D *h3_purity_ptzjt_test = (TH3D *)file_unfold_test->Get("purity_ptzjt"); 
  
  //TH3D *h3_eff_ptzr_nominal = (TH3D *)file_unfold->Get("efficiency_ptzr");
  TH3D *h3_eff_ptzr_test = (TH3D *)file_unfold_test->Get("efficiency_ptzr");
  //TH3D *h3_purity_ptzr_nominal = (TH3D *)file_unfold->Get("purity_ptzr");
  TH3D *h3_purity_ptzr_test = (TH3D *)file_unfold_test->Get("purity_ptzr");      
  
  //TH3D *h3_eff_ptjtr_nominal = (TH3D *)file_unfold->Get("efficiency_ptjtr");
  TH3D *h3_eff_ptjtr_test = (TH3D *)file_unfold_test->Get("efficiency_ptjtr");
  //TH3D *h3_purity_ptjtr_nominal = (TH3D *)file_unfold->Get("purity_ptjtr");
  TH3D *h3_purity_ptjtr_test = (TH3D *)file_unfold_test->Get("purity_ptjtr");    

  //TH2D *h2_eff_ptz_nominal = (TH2D *)file_unfold->Get("efficiency_ptz");
  TH2D *h2_eff_ptz_test = (TH2D *)file_unfold_test->Get("efficiency_ptz");
  //TH2D *h2_purity_ptz_nominal = (TH2D *)file_unfold->Get("purity_ptz");
  TH2D *h2_purity_ptz_test = (TH2D *)file_unfold_test->Get("purity_ptz"); 
  
  //TH2D *h2_eff_ptjt_nominal = (TH2D *)file_unfold->Get("efficiency_ptjt");
  TH2D *h2_eff_ptjt_test = (TH2D *)file_unfold_test->Get("efficiency_ptjt");
  //TH2D *h2_purity_ptjt_nominal = (TH2D *)file_unfold->Get("purity_ptjt");
  TH2D *h2_purity_ptjt_test = (TH2D *)file_unfold_test->Get("purity_ptjt");      
  
  //TH2D *h2_eff_ptr_nominal = (TH2D *)file_unfold->Get("efficiency_ptr");
  TH2D *h2_eff_ptr_test = (TH2D *)file_unfold_test->Get("efficiency_ptr");
  //TH2D *h2_purity_ptr_nominal = (TH2D *)file_unfold->Get("purity_ptr");
  TH2D *h2_purity_ptr_test = (TH2D *)file_unfold_test->Get("purity_ptr");    


  /////////////////////   Get Response Matrices /////////////////////////////////

  //RooUnfoldResponse *response_ptzjt_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzjt");
  RooUnfoldResponse *response_ptzjt_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptzjt");
  
  //RooUnfoldResponse *response_ptzr_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzr");
  RooUnfoldResponse *response_ptzr_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptzr");
  
  //RooUnfoldResponse *response_ptjtr_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptjtr");
  RooUnfoldResponse *response_ptjtr_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptjtr");      
  
  //RooUnfoldResponse *response_ptz_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptz");
  RooUnfoldResponse *response_ptz_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptz");
  
  //RooUnfoldResponse *response_ptjt_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptjt");
  RooUnfoldResponse *response_ptjt_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptjt");
  
  //RooUnfoldResponse *response_ptr_nominal = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptr");
  RooUnfoldResponse *response_ptr_test = (RooUnfoldResponse *)file_unfold_test->Get("Roo_response_ptr");    
 

  /////////////////////  Correct Purities /////////////////////////////////

  //h3_ptzjt_final_nominal->Multiply(h3_ptzjt_final_nominal, h3_purity_ptzjt_nominal);
  h3_ptzjt_final_test->Multiply(h3_ptzjt_final_test, h3_purity_ptzjt_test);
  
  //h3_ptzr_final_nominal->Multiply(h3_ptzr_final_nominal, h3_purity_ptzr_nominal);
  h3_ptzr_final_test->Multiply(h3_ptzr_final_test, h3_purity_ptzr_test);
  
  //h3_ptjtr_final_nominal->Multiply(h3_ptjtr_final_nominal, h3_purity_ptjtr_nominal);
  h3_ptjtr_final_test->Multiply(h3_ptjtr_final_test, h3_purity_ptjtr_test);    

  //h2_ptz_final_nominal->Multiply(h2_ptz_final_nominal, h2_purity_ptz_nominal);
  h2_ptz_final_test->Multiply(h2_ptz_final_test, h2_purity_ptz_test);
  
  //h2_ptjt_final_nominal->Multiply(h2_ptjt_final_nominal, h2_purity_ptjt_nominal);
  h2_ptjt_final_test->Multiply(h2_ptjt_final_test, h2_purity_ptjt_test);
  
  //h2_ptr_final_nominal->Multiply(h2_ptr_final_nominal, h2_purity_ptr_nominal);
  h2_ptr_final_test->Multiply(h2_ptr_final_test, h2_purity_ptr_test);      
  

  cout << "About to Unfold" << endl;

  // RooUnfoldids    unfold1D(response_jetpt, h1_jetpt_reco_purity, NumIters);

  /////////////////////   Create Unfold Objects and unfold /////////////////////////////////

  //RooUnfoldBayes unfold_ptzjt_nominal(response_ptzjt_nominal, h3_ptzjt_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptzjt_test(response_ptzjt_test, h3_ptzjt_final_test, NumIters_test);
  
  //RooUnfoldBayes unfold_ptzr_nominal(response_ptzr_nominal, h3_ptzr_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptzr_test(response_ptzr_test, h3_ptzr_final_test, NumIters_test);  

  //RooUnfoldBayes unfold_ptjtr_nominal(response_ptjtr_nominal, h3_ptjtr_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptjtr_test(response_ptjtr_test, h3_ptjtr_final_test, NumIters_test);   
 
  //RooUnfoldBayes unfold_ptz_nominal(response_ptz_nominal, h2_ptz_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptz_test(response_ptz_test, h2_ptz_final_test, NumIters_test);
  
  //RooUnfoldBayes unfold_ptjt_nominal(response_ptjt_nominal, h2_ptjt_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptjt_test(response_ptjt_test, h2_ptjt_final_test, NumIters_test);  

  //RooUnfoldBayes unfold_ptr_nominal(response_ptr_nominal, h2_ptr_final_nominal, NumIters);
  RooUnfoldBayes unfold_ptr_test(response_ptr_test, h2_ptr_final_test, NumIters_test);  

  cout << "Unfold successful" << endl;
  /////////////////////   Get Unfolded Distribution /////////////////////////////////
  // h1_jetpt_reco_purity_unfold = (TH1D*) unfold1D.Hreco();

  //h3_ptzjt_final_nominal = (TH3D *)unfold_ptzjt_nominal.Hreco();
  h3_ptzjt_final_test = (TH3D *)unfold_ptzjt_test.Hreco();
  
  //h3_ptzr_final_nominal = (TH3D *)unfold_ptzr_nominal.Hreco();
  h3_ptzr_final_test = (TH3D *)unfold_ptzr_test.Hreco();
  
  //h3_ptjtr_final_nominal = (TH3D *)unfold_ptjtr_nominal.Hreco();
  h3_ptjtr_final_test = (TH3D *)unfold_ptjtr_test.Hreco();     
  
  //h2_ptz_final_nominal = (TH2D *)unfold_ptz_nominal.Hreco();
  h2_ptz_final_test = (TH2D *)unfold_ptz_test.Hreco();
  
  //h2_ptjt_final_nominal = (TH2D *)unfold_ptjt_nominal.Hreco();
  h2_ptjt_final_test = (TH2D *)unfold_ptjt_test.Hreco();
  
  //h2_ptr_final_nominal = (TH2D *)unfold_ptr_nominal.Hreco();
  h2_ptr_final_test = (TH2D *)unfold_ptr_test.Hreco();    
 

  cout << "Got Unfolded Dist" << endl;
  /////////////////////  Correct for efficiency if needed /////////////////////////////////

  //h3_ptzjt_final_nominal->Divide(h3_ptzjt_final_nominal, h3_eff_ptzjt_nominal);
  h3_ptzjt_final_test->Divide(h3_ptzjt_final_test, h3_eff_ptzjt_test);
  
  //h3_ptzr_final_nominal->Divide(h3_ptzr_final_nominal, h3_eff_ptzr_nominal);
  h3_ptzr_final_test->Divide(h3_ptzr_final_test, h3_eff_ptzr_test);
  
  //h3_ptjtr_final_nominal->Divide(h3_ptjtr_final_nominal, h3_eff_ptjtr_nominal);
  h3_ptjtr_final_test->Divide(h3_ptjtr_final_test, h3_eff_ptjtr_test); 

  //h2_ptz_final_nominal->Divide(h2_ptz_final_nominal, h2_eff_ptz_nominal);
  h2_ptz_final_test->Divide(h2_ptz_final_test, h2_eff_ptz_test);
  
  //h2_ptjt_final_nominal->Divide(h2_ptjt_final_nominal, h2_eff_ptjt_nominal);
  h2_ptjt_final_test->Divide(h2_ptjt_final_test, h2_eff_ptjt_test);
  
  //h2_ptr_final_nominal->Divide(h2_ptr_final_nominal, h2_eff_ptr_nominal);
  h2_ptr_final_test->Divide(h2_ptr_final_test, h2_eff_ptr_test);
  
  
  cout << "Corrected for Eff" << endl;


  /////////////////////  Combine last 2 z bins to include z=1.0 entries in the 0.95-1.0 bin /////////////////////////////////

  for (int iy = 1; iy <= h3_ptzjt_final_test->GetNbinsY(); iy++)
  {
    for (int iz = 1; iz <= h3_ptzjt_final_test->GetNbinsZ(); iz++)
    {
      h3_ptzjt_final_test->SetBinContent(zbinsize2D-1, iy, iz, h3_ptzjt_final_test->GetBinContent(zbinsize2D-1, iy, iz) + h3_ptzjt_final_test->GetBinContent(zbinsize2D, iy, iz));
      h3_ptzjt_final_test->SetBinError(zbinsize2D-1, iy, iz, sqrt(pow(h3_ptzjt_final_test->GetBinError(zbinsize2D-1, iy, iz),2) + pow(h3_ptzjt_final_test->GetBinError(zbinsize2D, iy, iz),2)));
      h3_ptzjt_final_test->SetBinContent(zbinsize2D, iy, iz, 0.);
      h3_ptzjt_final_test->SetBinError(zbinsize2D, iy, iz, 0.);
    }
  }
  
  for (int iy = 1; iy <= h3_ptzr_final_test->GetNbinsY(); iy++)
  {
    for (int iz = 1; iz <= h3_ptzr_final_test->GetNbinsZ(); iz++)
    {
      h3_ptzr_final_test->SetBinContent(zbinsize2D-1, iy, iz, h3_ptzr_final_test->GetBinContent(zbinsize2D-1, iy, iz) + h3_ptzr_final_test->GetBinContent(zbinsize2D, iy, iz));
      h3_ptzr_final_test->SetBinError(zbinsize2D-1, iy, iz, sqrt(pow(h3_ptzr_final_test->GetBinError(zbinsize2D-1, iy, iz),2) + pow(h3_ptzr_final_test->GetBinError(zbinsize2D, iy, iz),2)));
      h3_ptzr_final_test->SetBinContent(zbinsize2D, iy, iz, 0.);
      h3_ptzr_final_test->SetBinError(zbinsize2D, iy, iz, 0.);
    }
  }  
  
  for (int iy = 1; iy <= h2_ptz_final_test->GetNbinsY(); iy++)
  {
    h2_ptz_final_test->SetBinContent(zbinsize-1, iy, h2_ptz_final_test->GetBinContent(zbinsize-1, iy) + h2_ptz_final_test->GetBinContent(zbinsize, iy));
    h2_ptz_final_test->SetBinError(zbinsize-1, iy, sqrt(pow(h2_ptz_final_test->GetBinError(zbinsize-1, iy),2) + pow(h2_ptz_final_test->GetBinError(zbinsize, iy),2)));
    h2_ptz_final_test->SetBinContent(zbinsize, iy, 0.);
    h2_ptz_final_test->SetBinError(zbinsize, iy, 0.); 
  }
  /////////////////////   Normalize histograms /////////////////////////////////

  int binlow = h2_ptz_final_nominal->GetYaxis()->FindBin(ptMin + 0.1);
  int binhigh = h2_ptz_final_nominal->GetYaxis()->FindBin(ptMax - 0.1); 

  h3_ptzjt_final_nominal->GetZaxis()->SetRange(binlow, binhigh);
  h3_ptzjt_final_test->GetZaxis()->SetRange(binlow, binhigh);
  
  h3_ptzr_final_nominal->GetZaxis()->SetRange(binlow, binhigh);
  h3_ptzr_final_test->GetZaxis()->SetRange(binlow, binhigh);  
  
  h3_ptjtr_final_nominal->GetZaxis()->SetRange(binlow, binhigh);
  h3_ptjtr_final_test->GetZaxis()->SetRange(binlow, binhigh);  

  h2_ptz_final_nominal->GetYaxis()->SetRange(binlow, binhigh);
  h2_ptz_final_test->GetYaxis()->SetRange(binlow, binhigh);
  
  h2_ptjt_final_nominal->GetYaxis()->SetRange(binlow, binhigh);
  h2_ptjt_final_test->GetYaxis()->SetRange(binlow, binhigh);  
  
  h2_ptr_final_nominal->GetYaxis()->SetRange(binlow, binhigh);
  h2_ptr_final_test->GetYaxis()->SetRange(binlow, binhigh);  
  
  TH2D *h2_zjt_ptbinned_final_nominal[ptbinsize-1], *h2_zjt_ptbinned_final_test[ptbinsize-1];
  TH2D *h2_zjt_ptbinned_ratio[ptbinsize-1], *h2_zjt_ptbinned_diff[ptbinsize-1];
  
  TH2D *h2_zr_ptbinned_final_nominal[ptbinsize-1], *h2_zr_ptbinned_final_test[ptbinsize-1];
  TH2D *h2_zr_ptbinned_ratio[ptbinsize-1], *h2_zr_ptbinned_diff[ptbinsize-1];
  
  TH2D *h2_jtr_ptbinned_final_nominal[ptbinsize-1], *h2_jtr_ptbinned_final_test[ptbinsize-1];
  TH2D *h2_jtr_ptbinned_ratio[ptbinsize-1], *h2_jtr_ptbinned_diff[ptbinsize-1];     

  TH1D *h1_z_ptbinned_final_nominal[ptbinsize-1], *h1_z_ptbinned_final_test[ptbinsize-1];
  TH1D *h1_z_ptbinned_ratio[ptbinsize-1], *h1_z_ptbinned_diff[ptbinsize-1];
  
  TH1D *h1_jt_ptbinned_final_nominal[ptbinsize-1], *h1_jt_ptbinned_final_test[ptbinsize-1];
  TH1D *h1_jt_ptbinned_ratio[ptbinsize-1], *h1_jt_ptbinned_diff[ptbinsize-1];
  
  TH1D *h1_r_ptbinned_final_nominal[ptbinsize-1], *h1_r_ptbinned_final_test[ptbinsize-1];
  TH1D *h1_r_ptbinned_ratio[ptbinsize-1], *h1_r_ptbinned_diff[ptbinsize-1];    
    
  TString systype = string_systype.Remove(string_systype.Length() -1);  
  TString sys_title = "";
  for (int j=1; j < ptbinsize; ++j)
  {
    h3_ptzjt_final_nominal->GetZaxis()->SetRange(j+1, j+1);
    h3_ptzjt_final_test->GetZaxis()->SetRange(j+1, j+1); 

    h3_ptzr_final_nominal->GetZaxis()->SetRange(j+1, j+1);
    h3_ptzr_final_test->GetZaxis()->SetRange(j+1, j+1); 
    
    h3_ptjtr_final_nominal->GetZaxis()->SetRange(j+1, j+1);
    h3_ptjtr_final_test->GetZaxis()->SetRange(j+1, j+1); 
      
    h2_zjt_ptbinned_final_nominal[j-1] = (TH2D *)h3_ptzjt_final_nominal->Project3D(Form("zjt_n_pt%d_yx",j));
    h2_zjt_ptbinned_final_test[j-1] = (TH2D *)h3_ptzjt_final_test->Project3D(Form("zjt_t_pt%d_yx",j));      
    
    h2_zr_ptbinned_final_nominal[j-1] = (TH2D *)h3_ptzr_final_nominal->Project3D(Form("zr_n_pt%d_yx",j));
    h2_zr_ptbinned_final_test[j-1] = (TH2D *)h3_ptzr_final_test->Project3D(Form("zr_t_pt%d_yx",j));       
    
    h2_jtr_ptbinned_final_nominal[j-1] = (TH2D *)h3_ptjtr_final_nominal->Project3D(Form("jtr_n_pt%d_yx",j));
    h2_jtr_ptbinned_final_test[j-1] = (TH2D *)h3_ptjtr_final_test->Project3D(Form("jtr_t_pt%d_yx",j));    
    
    h1_z_ptbinned_final_nominal[j-1] = (TH1D *)h2_ptz_final_nominal->ProjectionX(Form("z_nominal_pt%d",j), j+1, j+1);
    h1_z_ptbinned_final_test[j-1] = (TH1D *)h2_ptz_final_test->ProjectionX(Form("z_test_pt%d",j), j+1, j+1);    
    
    h1_jt_ptbinned_final_nominal[j-1] = (TH1D *)h2_ptjt_final_nominal->ProjectionX(Form("jt_nominal_pt%d",j), j+1, j+1);
    h1_jt_ptbinned_final_test[j-1] = (TH1D *)h2_ptjt_final_test->ProjectionX(Form("jt_test_pt%d",j), j+1, j+1);       
    
    h1_r_ptbinned_final_nominal[j-1] = (TH1D *)h2_ptr_final_nominal->ProjectionX(Form("r_nominal_pt%d",j), j+1, j+1);
    h1_r_ptbinned_final_test[j-1] = (TH1D *)h2_ptr_final_test->ProjectionX(Form("r_test_pt%d",j), j+1, j+1);                  

    //h1_z_ptbinned_final_nominal[j-1]->GetXaxis()->SetRange(binlow, binhigh);
    //h1_z_ptbinned_final_test[j-1]->GetXaxis()->SetRange(binlow, binhigh);    

    NormalizeHist(h2_zjt_ptbinned_final_nominal[j-1]);    
    NormalizeHist(h2_zjt_ptbinned_final_test[j-1]);      
    
    NormalizeHist(h2_zr_ptbinned_final_nominal[j-1]);
    NormalizeHist(h2_zr_ptbinned_final_test[j-1]);    
    
    NormalizeHist(h2_jtr_ptbinned_final_nominal[j-1]);
    NormalizeHist(h2_jtr_ptbinned_final_test[j-1]);  
    
    NormalizeHist(h1_z_ptbinned_final_nominal[j-1]);    
    NormalizeHist(h1_z_ptbinned_final_test[j-1]);      
    
    NormalizeHist(h1_jt_ptbinned_final_nominal[j-1]);
    NormalizeHist(h1_jt_ptbinned_final_test[j-1]);    
    
    NormalizeHist(h1_r_ptbinned_final_nominal[j-1]);
    NormalizeHist(h1_r_ptbinned_final_test[j-1]);            
    
    h2_zjt_ptbinned_ratio[j-1] = (TH2D*)h2_zjt_ptbinned_final_nominal[j-1]->Clone(Form("zjt_pt%d_ratio", j));
    h2_zjt_ptbinned_diff[j-1] = (TH2D*)h2_zjt_ptbinned_final_nominal[j-1]->Clone(Form("zjt_pt%d_diff", j));    
    
    h2_zr_ptbinned_ratio[j-1] = (TH2D*)h2_zr_ptbinned_final_nominal[j-1]->Clone(Form("zr_pt%d_ratio", j));
    h2_zr_ptbinned_diff[j-1] = (TH2D*)h2_zr_ptbinned_final_nominal[j-1]->Clone(Form("zr_pt%d_diff", j));   
    
    h2_jtr_ptbinned_ratio[j-1] = (TH2D*)h2_jtr_ptbinned_final_nominal[j-1]->Clone(Form("jtr_pt%d_ratio", j));
    h2_jtr_ptbinned_diff[j-1] = (TH2D*)h2_jtr_ptbinned_final_nominal[j-1]->Clone(Form("jtr_pt%d_diff", j));    

    h1_z_ptbinned_ratio[j-1] = (TH1D*)h1_z_ptbinned_final_nominal[j-1]->Clone(Form("z_pt%d_ratio", j));
    h1_z_ptbinned_diff[j-1] = (TH1D*)h1_z_ptbinned_final_nominal[j-1]->Clone(Form("z_pt%d_diff", j)); 
    
    h1_jt_ptbinned_ratio[j-1] = (TH1D*)h1_jt_ptbinned_final_nominal[j-1]->Clone(Form("jt_pt%d_ratio", j));
    h1_jt_ptbinned_diff[j-1] = (TH1D*)h1_jt_ptbinned_final_nominal[j-1]->Clone(Form("jt_pt%d_diff", j));   
    
    h1_r_ptbinned_ratio[j-1] = (TH1D*)h1_r_ptbinned_final_nominal[j-1]->Clone(Form("r_pt%d_ratio", j));
    h1_r_ptbinned_diff[j-1] = (TH1D*)h1_r_ptbinned_final_nominal[j-1]->Clone(Form("r_pt%d_diff", j));           
    
    /////////////////////   Compute ratios and pulls /////////////////////////////////
  
    sys_title = systype + Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[j], pt_binedges[j + 1]);

    h2_zjt_ptbinned_ratio[j-1]->Divide(h2_zjt_ptbinned_final_test[j-1], h2_zjt_ptbinned_final_nominal[j-1]);
    cout << " zjt Averaged Rel. Unc. = " << GetWeightedAverage(h2_zjt_ptbinned_ratio[j-1]) << endl;
    SubtractUnity(h2_zjt_ptbinned_ratio[j-1]);
    h2_zjt_ptbinned_ratio[j-1]->SetOption("COLZ, text");
    h2_zjt_ptbinned_ratio[j-1]->GetXaxis()->SetTitle("z");
    h2_zjt_ptbinned_ratio[j-1]->GetYaxis()->SetTitle("j_{T} [GeV/c]");
    h2_zjt_ptbinned_ratio[j-1]->GetZaxis()->SetTitle("#sigma_{sys}");
    h2_zjt_ptbinned_ratio[j-1]->SetTitle(sys_title);   
    h2_zjt_ptbinned_ratio[j-1]->Write();

    h2_zjt_ptbinned_diff[j-1]->Add(h2_zjt_ptbinned_diff[j-1], h2_zjt_ptbinned_final_test[j-1], 1, -1);
    SetHistErrCorr(h2_zjt_ptbinned_diff[j-1], h2_zjt_ptbinned_final_nominal[j-1], h2_zjt_ptbinned_final_test[j-1], rho);
    h2_zjt_ptbinned_diff[j-1]->SetOption("COLZ, text");  
    h2_zjt_ptbinned_diff[j-1]->GetXaxis()->SetTitle("z");    
    h2_zjt_ptbinned_diff[j-1]->GetYaxis()->SetTitle("j_{T} [GeV/c]");
    h2_zjt_ptbinned_diff[j-1]->GetZaxis()->SetTitle("#sigma_{sys}");
    h2_zjt_ptbinned_diff[j-1]->SetTitle(sys_title); 
    h2_zjt_ptbinned_diff[j-1]->Write();
        
    h2_zr_ptbinned_ratio[j-1]->Divide(h2_zr_ptbinned_final_test[j-1], h2_zr_ptbinned_final_nominal[j-1]);
    cout << "zr Averaged Rel. Unc. = " << GetWeightedAverage(h2_zr_ptbinned_ratio[j-1]) << endl;
    SubtractUnity(h2_zr_ptbinned_ratio[j-1]);
    h2_zr_ptbinned_ratio[j-1]->SetOption("COLZ, text");  
    h2_zr_ptbinned_ratio[j-1]->GetXaxis()->SetTitle("z");  
    h2_zr_ptbinned_ratio[j-1]->GetYaxis()->SetTitle("r");
    h2_zr_ptbinned_ratio[j-1]->GetZaxis()->SetTitle("#sigma_{sys}");
    h2_zr_ptbinned_ratio[j-1]->SetTitle(sys_title);         
    h2_zr_ptbinned_ratio[j-1]->Write();
    
    h2_zr_ptbinned_diff[j-1]->Add(h2_zr_ptbinned_diff[j-1], h2_zr_ptbinned_final_test[j-1], 1, -1);
    SetHistErrCorr(h2_zr_ptbinned_diff[j-1], h2_zr_ptbinned_final_nominal[j-1], h2_zr_ptbinned_final_test[j-1], rho); 
    h2_zr_ptbinned_diff[j-1]->SetOption("COLZ, text");  
    h2_zr_ptbinned_diff[j-1]->GetXaxis()->SetTitle("z");        
    h2_zr_ptbinned_diff[j-1]->GetYaxis()->SetTitle("r");
    h2_zr_ptbinned_diff[j-1]->GetZaxis()->SetTitle("#sigma_{sys}");
    h2_zr_ptbinned_diff[j-1]->SetTitle(sys_title);          
    h2_zr_ptbinned_diff[j-1]->Write();
        
    h2_jtr_ptbinned_ratio[j-1]->Divide(h2_jtr_ptbinned_final_test[j-1], h2_jtr_ptbinned_final_nominal[j-1]);
    cout << "jtr Averaged Rel. Unc. = " << GetWeightedAverage(h2_jtr_ptbinned_ratio[j-1]) << endl;
    SubtractUnity(h2_jtr_ptbinned_ratio[j-1]);
    h2_jtr_ptbinned_ratio[j-1]->SetOption("COLZ, text");  
    h2_jtr_ptbinned_ratio[j-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h2_jtr_ptbinned_ratio[j-1]->GetYaxis()->SetTitle("r");
    h2_jtr_ptbinned_ratio[j-1]->GetZaxis()->SetTitle("#sigma_{sys}");
    h2_jtr_ptbinned_ratio[j-1]->SetTitle(sys_title);         
    h2_jtr_ptbinned_ratio[j-1]->Write();
    
    h2_jtr_ptbinned_diff[j-1]->Add(h2_jtr_ptbinned_diff[j-1], h2_jtr_ptbinned_final_test[j-1], 1, -1);
    SetHistErrCorr(h2_jtr_ptbinned_diff[j-1], h2_jtr_ptbinned_final_nominal[j-1], h2_jtr_ptbinned_final_test[j-1], rho);
    h2_jtr_ptbinned_diff[j-1]->SetOption("COLZ, text");  
    h2_jtr_ptbinned_diff[j-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h2_jtr_ptbinned_diff[j-1]->GetYaxis()->SetTitle("r");
    h2_jtr_ptbinned_diff[j-1]->GetZaxis()->SetTitle("#sigma_{sys}");
    h2_jtr_ptbinned_diff[j-1]->SetTitle(sys_title);   
    h2_jtr_ptbinned_diff[j-1]->Write();   

    h1_z_ptbinned_ratio[j-1]->Divide(h1_z_ptbinned_final_test[j-1], h1_z_ptbinned_final_nominal[j-1]);
    cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h1_z_ptbinned_ratio[j-1]) << endl;
    SubtractUnity(h1_z_ptbinned_ratio[j-1]);
    h1_z_ptbinned_ratio[j-1]->GetXaxis()->SetTitle("z");
    h1_z_ptbinned_ratio[j-1]->GetYaxis()->SetTitle("#sigma_{sys}");
    h1_z_ptbinned_ratio[j-1]->SetTitle(sys_title);   
    h1_z_ptbinned_ratio[j-1]->Write();

    h1_z_ptbinned_diff[j-1]->Add(h1_z_ptbinned_diff[j-1], h1_z_ptbinned_final_test[j-1], 1, -1);
    SetHistErrCorr(h1_z_ptbinned_diff[j-1], h1_z_ptbinned_final_nominal[j-1], h1_z_ptbinned_final_test[j-1], rho);
    h1_z_ptbinned_diff[j-1]->GetXaxis()->SetTitle("z");
    h1_z_ptbinned_diff[j-1]->GetYaxis()->SetTitle("#sigma_{sys}");
    h1_z_ptbinned_diff[j-1]->SetTitle(sys_title);           
    h1_z_ptbinned_diff[j-1]->Write();
        
    h1_jt_ptbinned_ratio[j-1]->Divide(h1_jt_ptbinned_final_test[j-1], h1_jt_ptbinned_final_nominal[j-1]);
    cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h1_jt_ptbinned_ratio[j-1]) << endl;
    SubtractUnity(h1_jt_ptbinned_ratio[j-1]);
    h1_jt_ptbinned_ratio[j-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h1_jt_ptbinned_ratio[j-1]->GetYaxis()->SetTitle("#sigma_{sys}");
    h1_jt_ptbinned_ratio[j-1]->SetTitle(sys_title);   
    h1_jt_ptbinned_ratio[j-1]->Write();
    
    h1_jt_ptbinned_diff[j-1]->Add(h1_jt_ptbinned_diff[j-1], h1_jt_ptbinned_final_test[j-1], 1, -1);
    SetHistErrCorr(h1_jt_ptbinned_diff[j-1], h1_jt_ptbinned_final_nominal[j-1], h1_jt_ptbinned_final_test[j-1], rho); 
    h1_jt_ptbinned_diff[j-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h1_jt_ptbinned_diff[j-1]->GetYaxis()->SetTitle("#sigma_{sys}");
    h1_jt_ptbinned_diff[j-1]->SetTitle(sys_title);   
    h1_jt_ptbinned_diff[j-1]->Write();
        
    h1_r_ptbinned_ratio[j-1]->Divide(h1_r_ptbinned_final_test[j-1], h1_r_ptbinned_final_nominal[j-1]);
    cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h1_r_ptbinned_ratio[j-1]) << endl;
    SubtractUnity(h1_r_ptbinned_ratio[j-1]);
    h1_r_ptbinned_ratio[j-1]->GetXaxis()->SetTitle("r");
    h1_r_ptbinned_ratio[j-1]->GetYaxis()->SetTitle("#sigma_{sys}");
    h1_r_ptbinned_ratio[j-1]->SetTitle(sys_title);             
    h1_r_ptbinned_ratio[j-1]->Write();
    
    h1_r_ptbinned_diff[j-1]->Add(h1_r_ptbinned_diff[j-1], h1_r_ptbinned_final_test[j-1], 1, -1);
    SetHistErrCorr(h1_r_ptbinned_diff[j-1], h1_r_ptbinned_final_nominal[j-1], h1_r_ptbinned_final_test[j-1], rho);   
    h1_r_ptbinned_diff[j-1]->GetXaxis()->SetTitle("r");    
    h1_r_ptbinned_diff[j-1]->GetYaxis()->SetTitle("#sigma_{sys}");
    h1_r_ptbinned_diff[j-1]->SetTitle(sys_title);     
    h1_r_ptbinned_diff[j-1]->Write();              
  }

  //file_save->Write();
  file_save->Close();
}
