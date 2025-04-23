#include <TFile.h>
#include <TH2.h>
#include "Settings.h"
#include "../Helpers.h"

void SimVersionCompare()
{

    gStyle->SetPaintTextFormat("3.3f");
    gROOT->ForceStyle();
    gStyle->SetOptStat(0);
    
    TFile infile_all = TFile("../../root_files/BjetsMC/truth_ev_-1_ptj_5100_eta_2.54.0_HF_b_91599.root");
    TFile infile_sim9 = TFile("../../root_files/BjetsMC/truth_ev_-1_ptj_5100_eta_2.54.0_HF_b_sim9_91599.root");
    TFile outfile = TFile("../../root_files/BjetsMC/sim_versions_compare.root", "RECREATE");
    

    TH2D *ptz_all = (TH2D*)infile_all.Get("ptz");
    NormalizeHist(ptz_all);
    TH2D *ptz_sim9 = (TH2D*)infile_sim9.Get("ptz");
    NormalizeHist(ptz_sim9);
    TH2D *ptz_ratio = (TH2D*)ptz_all->Clone("ptz_ratio");
    ptz_ratio->Divide(ptz_all, ptz_sim9);
    ptz_ratio->SetOption("COLZ, text");
    ptz_ratio->SetTitle("#frac{Sim09+Sim10}{Sim09}");
    ptz_ratio->Write();
    THStack *hs_ptz_ratio = new THStack("z_sim_ratio", ";z;#frac{Sim09+Sim10}{Sim09}");      
    for (int j = 1; j < ptbinsize; j++)
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
    hs_ptz_ratio->SetMaximum(1.3);
    hs_ptz_ratio->SetMinimum(0.7);
    hs_ptz_ratio->Write();


    TH2D *ptjt_all = (TH2D*)infile_all.Get("ptjt");
    NormalizeHist(ptjt_all);
    TH2D *ptjt_sim9 = (TH2D*)infile_sim9.Get("ptjt");
    NormalizeHist(ptjt_sim9);
    TH2D *ptjt_ratio = (TH2D*)ptjt_all->Clone("ptjt_ratio");
    ptjt_ratio->Divide(ptjt_all, ptjt_sim9);
    ptjt_ratio->SetOption("COLZ, text");
    ptjt_ratio->SetTitle("#frac{Sim09+Sim10}{Sim09}");
    ptjt_ratio->Write();
    THStack *hs_ptjt_ratio = new THStack("jt_sim_ratio", ";j_{T} [GeV/c];#frac{Sim09+Sim10}{Sim09}");
    for (int j = 1; j < ptbinsize; j++)
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
    hs_ptjt_ratio->SetMaximum(1.3);
    hs_ptjt_ratio->SetMinimum(0.7);
    hs_ptjt_ratio->Write();


    TH2D *ptr_all = (TH2D*)infile_all.Get("ptr");
    NormalizeHist(ptr_all);
    TH2D *ptr_sim9 = (TH2D*)infile_sim9.Get("ptr");
    NormalizeHist(ptr_sim9);
    TH2D *ptr_ratio = (TH2D*)ptr_all->Clone("ptr_ratio");
    ptr_ratio->Divide(ptr_all, ptr_sim9);
    ptr_ratio->SetOption("COLZ, text");
    ptr_ratio->SetTitle("#frac{Sim09+Sim10}{Sim09}");
    ptr_ratio->Write();
    THStack *hs_ptr_ratio = new THStack("r_sim_ratio", ";r;#frac{Sim09+Sim10}{Sim09}");      
    for (int j = 1; j < ptbinsize; j++)
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
    hs_ptr_ratio->SetMaximum(1.3);
    hs_ptr_ratio->SetMinimum(0.7);
    hs_ptr_ratio->Write();

    outfile.Close();


}
