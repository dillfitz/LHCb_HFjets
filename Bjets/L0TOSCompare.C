#include <TFile.h>
#include <TH2.h>
#include "Settings.h"
#include "../Helpers.h"

void L0TOSCompare()
{

  gStyle->SetPaintTextFormat("3.3f");
  gROOT->ForceStyle();
  gStyle->SetOptStat(0);
  
  TFile infile_all = TFile("../../root_files/Bjets/data_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_91599.root");
  TFile infile_L0DiMuon = TFile("../../root_files/Bjets/data_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_L0DiMuon_91599.root");
  TFile infile_reco_all = TFile("../../root_files/BjetsMC/reco_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_91599.root");
  TFile infile_reco_L0DiMuon = TFile("../../root_files/BjetsMC/reco_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_L0DiMuon_91599.root");
  TFile infile_corrected_all = TFile("../../root_files/Bjets/corrected_data_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_iters_4_91599.root");
  TFile infile_corrected_L0DiMuon = TFile("../../root_files/Bjets/corrected_data_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_iters_4_L0DiMuon_91599.root");
  TFile outfile = TFile("../../root_files/Bjets/L0_TOS_compare.root", "RECREATE");
  

  TH2D *ptz_all = (TH2D*)infile_corrected_all.Get("ptz_final");
  NormalizeHist(ptz_all);
  TH2D *ptz_L0DiMuon = (TH2D*)infile_corrected_L0DiMuon.Get("ptz_final");
  NormalizeHist(ptz_L0DiMuon);
  TH2D *ptz_ratio = (TH2D*)ptz_all->Clone("ptz_ratio");
  ptz_ratio->Divide(ptz_all, ptz_L0DiMuon);
  ptz_ratio->SetOption("COLZ, text");
  ptz_ratio->SetTitle("#frac{L0Muon || L0DiMuon}{L0DiMuon}");
  ptz_ratio->Write();
  THStack *hs_ptz_ratio = new THStack("z_L0_TOS_ratio", ";z;#frac{L0Muon || L0DiMuon}{L0DiMuon}");      
  for (int j = ptbinsize; j > 0; j--)
  {   
    TH1D *h1_ptz_temp = (TH1D *)ptz_ratio->ProjectionX(Form("z_ratio_pt%d", j), j + 1, j + 1); 
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
    hs_ptz_ratio->Add(h1_ptz_temp);
  }
  hs_ptz_ratio->SetMaximum(2.0);
  hs_ptz_ratio->SetMinimum(0.0);
  hs_ptz_ratio->Write();


  TH2D *ptjt_all = (TH2D*)infile_corrected_all.Get("ptjt_final");
  NormalizeHist(ptjt_all);
  TH2D *ptjt_L0DiMuon = (TH2D*)infile_corrected_L0DiMuon.Get("ptjt_final");
  NormalizeHist(ptjt_L0DiMuon);
  TH2D *ptjt_ratio = (TH2D*)ptjt_all->Clone("ptjt_ratio");
  ptjt_ratio->Divide(ptjt_all, ptjt_L0DiMuon);
  ptjt_ratio->SetOption("COLZ, text");
  ptjt_ratio->SetTitle("#frac{L0Muon || L0DiMuon}{L0DiMuon}");
  ptjt_ratio->Write();
  THStack *hs_ptjt_ratio = new THStack("jt_L0_TOS_ratio", ";j_{T} [GeV/c];#frac{L0Muon || L0DiMuon}{L0DiMuon}");
  for (int j = ptbinsize; j > 0; j--)
  {   
      
    TH1D *h1_ptjt_temp = (TH1D *)ptjt_ratio->ProjectionX(Form("jt_ratio_pt%d", j), j + 1, j + 1); 
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
    //h1_ptjt_temp->SetOption("PE HIST");
    hs_ptjt_ratio->Add(h1_ptjt_temp);
  }
  hs_ptjt_ratio->SetMaximum(2.0);
  hs_ptjt_ratio->SetMinimum(0.0);
  hs_ptjt_ratio->Write();


  TH2D *ptr_all = (TH2D*)infile_corrected_all.Get("ptr_final");
  NormalizeHist(ptr_all);
  TH2D *ptr_L0DiMuon = (TH2D*)infile_corrected_L0DiMuon.Get("ptr_final");
  NormalizeHist(ptr_L0DiMuon);
  TH2D *ptr_ratio = (TH2D*)ptr_all->Clone("ptr_ratio");
  ptr_ratio->Divide(ptr_all, ptr_L0DiMuon);
  ptr_ratio->SetOption("COLZ, text");
  ptr_ratio->SetTitle("#frac{L0Muon || L0DiMuon}{L0DiMuon}");
  ptr_ratio->Write();
  THStack *hs_ptr_ratio = new THStack("r_L0_TOS_ratio", ";r;#frac{L0Muon || L0DiMuon}{L0DiMuon}");      
  for (int j = ptbinsize; j > 0; j--)
  {   
      
    TH1D *h1_ptr_temp = (TH1D *)ptr_ratio->ProjectionX(Form("r_ratio_pt%d", j), j + 1, j + 1); 
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
    //h1_ptr_temp->SetOption("PE HIST");
    hs_ptr_ratio->Add(h1_ptr_temp);
  }
  hs_ptr_ratio->SetMaximum(2.0);
  hs_ptr_ratio->SetMinimum(0.0);
  hs_ptr_ratio->Write();

  TH1D *h1_nSPDHits_all = (TH1D*)infile_all.Get("nSPDHits");
  TH1D *h1_nSPDHits_reco_all = (TH1D*)infile_reco_all.Get("nSPDHits");
  TH1D *h1_nSPDHits_L0DiMuon = (TH1D*)infile_L0DiMuon.Get("nSPDHits");
  TH1D *h1_nSPDHits_reco_L0DiMuon = (TH1D*)infile_reco_L0DiMuon.Get("nSPDHits");

  THStack *hs_nSPDHits_all = new THStack("nSPDHits_all", "( L0Muon || L0DiMuon );N_{SPD};A.U.");
  h1_nSPDHits_all->Scale(1./h1_nSPDHits_all->Integral());     
  h1_nSPDHits_all->SetTitle("data");
  h1_nSPDHits_reco_all->Scale(1./h1_nSPDHits_reco_all->Integral());       
  h1_nSPDHits_reco_all->SetLineColor(kRed);
  h1_nSPDHits_reco_all->SetTitle("reco");
  hs_nSPDHits_all->Add(h1_nSPDHits_all);
  hs_nSPDHits_all->Add(h1_nSPDHits_reco_all);
  hs_nSPDHits_all->Write();

  THStack *hs_nSPDHits_L0DiMuon = new THStack("nSPDHits_L0DiMuon", "L0DiMuon;N_{SPD};A.U.");
  h1_nSPDHits_L0DiMuon->Scale(1./h1_nSPDHits_L0DiMuon->Integral()); 
  h1_nSPDHits_L0DiMuon->SetTitle("data");    
  h1_nSPDHits_reco_L0DiMuon->Scale(1./h1_nSPDHits_reco_L0DiMuon->Integral());       
  h1_nSPDHits_reco_L0DiMuon->SetLineColor(kRed);
  h1_nSPDHits_reco_L0DiMuon->SetTitle("reco");    
  hs_nSPDHits_L0DiMuon->Add(h1_nSPDHits_L0DiMuon);
  hs_nSPDHits_L0DiMuon->Add(h1_nSPDHits_reco_L0DiMuon);
  hs_nSPDHits_L0DiMuon->Write();


  

  outfile.Close();


}
