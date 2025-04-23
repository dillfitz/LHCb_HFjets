#include <TFile.h>
#include <TH2.h>
#include "Settings.h"
#include "../Helpers.h"

void SPlotCompare()
{


    gStyle->SetPaintTextFormat("3.3f");
    gStyle->SetOptStat(0);
    gROOT->ForceStyle();
    
    TFile infile = TFile("../../root_files/Bjets/data_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_91599.root");
    TFile outfile = TFile("../../root_files/Bjets/splot_compare.root", "RECREATE");
    

    TH2D *ptz = (TH2D*)infile.Get("ptz");
    NormalizeHist(ptz);
    TH2D *ptz_sweight = (TH2D*)infile.Get("ptz_sweight");
    NormalizeHist(ptz_sweight);
    TH2D *ptz_ratio = (TH2D*)ptz->Clone("ptz_ratio");
    ptz_ratio->Divide(ptz, ptz_sweight);
    ptz_ratio->SetOption("COLZ, text");
    ptz_ratio->Write();
    THStack *hs_ptz_ratio = new THStack("z_sweight_ratio", ";z;#frac{SB subtraction}{SPlot}");      
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
    hs_ptz_ratio->SetMaximum(2.0);
    hs_ptz_ratio->SetMinimum(0.);
    hs_ptz_ratio->Write();


    TH2D *ptjt = (TH2D*)infile.Get("ptjt");
    NormalizeHist(ptjt);
    TH2D *ptjt_sweight = (TH2D*)infile.Get("ptjt_sweight");
    NormalizeHist(ptjt_sweight);
    TH2D *ptjt_ratio = (TH2D*)ptjt->Clone("ptjt_ratio");
    ptjt_ratio->Divide(ptjt, ptjt_sweight);
    ptjt_ratio->SetOption("COLZ, text");
    ptjt_ratio->Write();
    THStack *hs_ptjt_ratio = new THStack("jt_sweight_ratio", ";j_{T} [GeV/c];#frac{SB subtraction}{SPlot}");
    for (int j = 1; j < ptbinsize; j++)
    {   
        
      TH1D *h1_ptjt_temp = (TH1D *)ptjt_ratio->ProjectionX(Form("z_ratio_pt%d", j), j + 1, j + 1); 
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
    hs_ptjt_ratio->SetMinimum(0.);
    hs_ptjt_ratio->Write();


    TH2D *ptr = (TH2D*)infile.Get("ptr");
    NormalizeHist(ptr);
    TH2D *ptr_sweight = (TH2D*)infile.Get("ptr_sweight");
    NormalizeHist(ptr_sweight);
    TH2D *ptr_ratio = (TH2D*)ptr->Clone("ptr_ratio");
    ptr_ratio->Divide(ptr, ptr_sweight);
    ptr_ratio->SetOption("COLZ, text");
    ptr_ratio->Write();
    THStack *hs_ptr_ratio = new THStack("r_sweight_ratio", ";r;#frac{SB subtraction}{SPlot}");      
    for (int j = 1; j < ptbinsize; j++)
    {   
      TH1D *h1_ptr_temp = (TH1D *)ptr_ratio->ProjectionX(Form("z_ratio_pt%d", j), j + 1, j + 1); 
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
    hs_ptr_ratio->SetMinimum(0.);
    hs_ptr_ratio->Write();

    outfile.Close();
}
