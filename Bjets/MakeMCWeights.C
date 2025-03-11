#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
using namespace std;

void MakeMCWeights(int NumEvts1 = -1, int NumEvts2 = -1,
                   int dataset1 = 91599, int dataset2 = 91599,
                   int datatype1 = 0, int datatype2 = 1,
                   bool followHardest1 = false, bool followHardest2 = false,
                   bool chargedJetCut1 = false, bool chargedJetCut2 = false)
{

  // TString datafile1, datafile2, datafile3, extension;
  bool ghostCut1, ghostCut2;
  if (datatype1 == 0 || datatype1 == 1)
    ghostCut1 = true;
  else
    ghostCut1 = false;
  if (datatype2 == 0 || datatype2 == 1)
    ghostCut2 = true;
  else
    ghostCut2 = false;

  int JetMeth1 = (dataset1 / 1000) % 10;
  int flavor1 = (dataset1 / 100) % 10;
  int ptRange1 = (dataset1 / 10) % 10;
  int Mag1 = (dataset1 / 1) % 10;

  int JetMeth2 = (dataset2 / 1000) % 10;
  int flavor2 = (dataset2 / 100) % 10;
  int ptRange2 = (dataset2 / 10) % 10;
  int Mag2 = (dataset2 / 1) % 10;

  if (flavor1 == 1)
  {
    followHardest1 = true;
  }
  if (flavor2 == 1)
  {
    followHardest2 = true;
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

  if (datatype1 == 0)
    str_level1 = "data";
  else if (datatype1 == 1)
    str_level1 = "reco";
  else if (datatype1 == 2)
    str_level1 = "truth";

  if (followHardest1)
    str_followHard1 = "_hard";
  else
    str_followHard1 = "_HF";

  if (ghostCut1)
    str_ghost1 = Form("_ghost_%.1f", ghostProb);

  if (chargedJetCut1)
    str_charged1 = "_charge";
    
  str_PID = PID_cut ? "_PID" : "";    

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

  if (datatype2 == 0)
    str_level2 = "data";
  else if (datatype2 == 1)
    str_level2 = "reco";
  else if (datatype2 == 2)
    str_level2 = "truth";

  if (followHardest2)
    str_followHard2 = "_hard";
  else
    str_followHard2 = "_HF";

  if (ghostCut2)
    str_ghost2 = Form("_ghost_%.1f", ghostProb);

  if (chargedJetCut2)
    str_charged2 = "_charge";

  TString extension1, extension2, extension;
  extension = TString("compare_") + str_level1 + str_level2 + Form("_ev_%d", NumEvts1) + Form("_ev_%d", NumEvts2) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_followHard2 + str_ghost1 + str_ghost2 + str_charged1 + str_charged2 + str_Mag1 + +str_Mag2 + str_flavor1 + str_flavor2 + Form("_%d", dataset1) + Form("_%d", dataset2);
  extension1 = str_level1 + Form("_ev_%d", NumEvts1) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard1 + str_ghost1 + str_charged1 + str_Mag1 + str_flavor1 + str_PID + Form("_%d", dataset1);
  extension2 = str_level2 + Form("_ev_%d", NumEvts2) + Form("_ptj_%d%d", int(pTLow), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard2 + str_ghost2 + str_charged2 + str_Mag2 + str_flavor2 + str_PID + Form("_%d", dataset2);
  //extension1 = "data_ev_-1_ptj_20100_eta_2.54.0_HF_ghost_0.5_b_PID_WTA_91599";
  //extension2 = "reco_ev_-1_ptj_20100_eta_2.54.0_HF_ghost_0.5_b_PID_WTA_91599";

  //TString loc("$LUND/Bjets/");

  TFile fread1("../../root_files/Bjets/" + extension1 + ".root", "READ");
  TFile fread2("../../root_files/BjetsMC/" + extension2 + ".root", "READ");

  TFile file_weight("../../root_files/Bjets/MC_DATA_WEIGHTS.root", "RECREATE");

  TH3D *h3_ptzjt_data = (TH3D *)fread1.Get("ptzjt");
  TH3D *h3_ptzjt_reco = (TH3D *)fread2.Get("ptzjt");

  //TH3D *h3_HFptjetptrap_reco = (TH3D *)fread1.Get("h3_HFptjetptrap");
  //TH3D *h3_HFptjetptrap_data = (TH3D *)fread2.Get("h3_HFptjetptrap");

  //TH3D *h3_dRzkt_reco = (TH3D *)fread1.Get("h3_dRzkt");
  //TH3D *h3_dRzkt_data = (TH3D *)fread2.Get("h3_dRzkt");

  //NormalizeHist(h3_HFptjetptrap_reco);
  //NormalizeHist(h3_HFptjetptrap_data);
  //NormalizeHist(h3_dRzkt_reco);
  //NormalizeHist(h3_dRzkt_data);
  NormalizeHist(h3_ptzjt_data);
  NormalizeHist(h3_ptzjt_reco);
  
  

  TH3D *h3_ptzjt_ratio = (TH3D *)h3_ptzjt_data->Clone("ptzjt_ratio");
  h3_ptzjt_ratio->Divide(h3_ptzjt_reco);


  h3_ptzjt_ratio->Write();

  fread1.Close();
  fread2.Close();

  //
}

