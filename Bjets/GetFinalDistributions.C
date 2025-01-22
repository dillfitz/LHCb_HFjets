#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
using namespace std;

void GetFinalDistributions(int NumEvts = -1,
                           int dataset = 91599,
                           bool WTA_cut = false,
                           int NumIters = 4)
{

  TString string_final, string_truth, string_eff, string_unfold, string_sys, extension;
  TString str_followHard, str_ghost, str_charged, str_Mag, str_flavor, str_DTF(""), str_PID("");
  TString loc_rootfiles_data("../../root_files/Bjets/");
  TString loc_rootfiles_MC("../../root_files/BjetsMC/");
  TString loc_plots("../../plots/Bjets/");

  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;

  // int NumIters = 2;
  //int NumIters_z = 1;
  //int NumIters_kt = 1;

  if (Mag == 0)
    str_Mag = "_MD";
  else if (Mag == 1)
    str_Mag = "_MU";
  if (flavor == 1)
    str_flavor = "_udsg";
  else if (flavor == 4)
    str_flavor = "_c";
  else if (flavor == 5)
    str_flavor = "_b";

  if (DTF_cut)
    str_DTF = "_DTF";
  if (PID_cut)
    str_PID = "_PID";
  if (flavor == 1)
    str_followHard = "_hard";
  else
  {
    //   if(followHardest) str_followHard = "_hard";
    // else
    str_followHard = "_HF";
  }
  if (ghostCut)
    str_ghost = Form("_ghost_%.1f", ghostProb);

  if (WTA_cut)
    str_WTA = "_WTA";
  string_truth = TString("truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_Mag + str_flavor + str_WTA + Form("_%d", dataset);

  string_final = TString("corrected_data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);

  string_sys = TString("total_sys") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost  + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);  
  
  extension = TString("publish") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_Mag + str_flavor + str_DTF + str_PID + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset);
  

  cout << string_final << endl;
  cout << string_truth << endl;
  


  //////////////////////////////////////////////////////////////////

  // TH1D* h1_dR_empty = new TH1D("h1_ptktdR_empty", "", dR_bins, jetradius/exp(dR_min), jetradius/exp(dR_max));

  /////////////////////   Get Files /////////////////////////////////

  TFile *file_final = new TFile(loc_rootfiles_data + string_final + TString(".root"), "READ");
  TFile *file_truth = new TFile(loc_rootfiles_MC + string_truth + TString(".root"), "READ");
  TFile *file_sys = new TFile(loc_rootfiles_data + "Systematics/" + string_sys + TString(".root"), "READ");
  //TFile *file_write = new TFile(loc_hists + extension + TString(".root"), "RECREATE");
  //TFile *file_write = TFile::Open(loc_rootfiles_data + extension + TString(".root"), "RECREATE");    

  TH2D *h2_ptz_data = (TH2D *)file_final->Get("ptz_final");
  TH2D *h2_ptz_truth = (TH2D *)file_truth->Get("ptz");
  
  TH2D *h2_ptjt_data = (TH2D *)file_final->Get("ptjt_final");
  TH2D *h2_ptjt_truth = (TH2D *)file_truth->Get("ptjt");
  
  TH2D *h2_ptr_data = (TH2D *)file_final->Get("ptr_final");
  TH2D *h2_ptr_truth = (TH2D *)file_truth->Get("ptr");    

  TH3D *h3_ptzjt_data = (TH3D *)file_final->Get("ptzjt_final");
  TH3D *h3_ptzjt_truth = (TH3D *)file_truth->Get("ptzjt");
  
  TH3D *h3_ptzr_data = (TH3D *)file_final->Get("ptzr_final");
  TH3D *h3_ptzr_truth = (TH3D *)file_truth->Get("ptzr");
  
  TH3D *h3_ptjtr_data = (TH3D *)file_final->Get("ptjtr_final");
  TH3D *h3_ptjtr_truth = (TH3D *)file_truth->Get("ptjtr");    
       
  TH1D *h1_z_data[ptbinsize-1], *h1_z_truth[ptbinsize-1];
  TH1D *h1_jt_data[ptbinsize-1], *h1_jt_truth[ptbinsize-1];
  TH1D *h1_r_data[ptbinsize-1], *h1_r_truth[ptbinsize-1]; 
  TH1D *h1_z_ratio_MCData[ptbinsize-1], *h1_jt_ratio_MCData[ptbinsize-1], *h1_r_ratio_MCData[ptbinsize-1];     
  TH1D *h1_z_sys[ptbinsize-1], *h1_jt_sys[ptbinsize-1], *h1_r_sys[ptbinsize-1];  
  
  TH2D *h2_zjt_data[ptbinsize-1], *h2_zjt_truth[ptbinsize-1];
  TH2D *h2_zr_data[ptbinsize-1], *h2_zr_truth[ptbinsize-1];
  TH2D *h2_jtr_data[ptbinsize-1], *h2_jtr_truth[ptbinsize-1];  
  TH2D *h2_zjt_ratio_MCData[ptbinsize-1], *h2_zr_ratio_MCData[ptbinsize-1], *h2_jtr_ratio_MCData[ptbinsize-1];     
  TH2D *h2_zjt_sys[ptbinsize-1], *h2_zr_sys[ptbinsize-1], *h2_jtr_sys[ptbinsize-1];    
  TH2D *h2_zjt_tot_unc[ptbinsize-1], *h2_zr_tot_unc[ptbinsize-1], *h2_jtr_tot_unc[ptbinsize-1];     

  TRatioPlot *rp[1000];
  // h2_ptktdR_truth->GetYaxis()->SetRange(1, ktbinsize);

  // NormalizeHist(h2_ptktdR_truth);
  // NormalizeHist(h2_ptzdR_truth);
  ////

  //---- paint setup...
  //
  int ican = -1, iframe = -1, itext = -1;
  int irp = 0;
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
  Tl.SetTextSize(0.06);
  Tl.SetTextFont(1);
  Int_t lhcbFont = 132;
  Double_t lhcbTSize = 0.05;
  Double_t lhcbWidth = 2.00;

  Tl.SetTextFont(lhcbFont);
  Tl.SetTextColor(1);
  Tl.SetTextSize(lhcbTSize);
  Tl.SetTextAlign(12);
  //

  // add LHCb label
  auto lhcbName = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                                1.01 - gStyle->GetPadTopMargin(),
                                gStyle->GetPadLeftMargin() + 0.30,
                                1.07 - gStyle->GetPadTopMargin(),
                                "BRNDC");
  lhcbName->AddText("LHCb");
  lhcbName->SetFillColor(0);
  lhcbName->SetTextAlign(12);
  lhcbName->SetBorderSize(0);
  // lhcbName->SetTextFont(lhcbFont);

  gStyle->SetOptStat(0);
  // gROOT->SetStyle("Plain");
  // gStyle->SetCanvasDefH(1414); gStyle->SetCanvasDefW(1000);
  // set the paper & margin sizes
  gStyle->SetFillColor(1);
  gStyle->SetFillStyle(1001); // solid
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPaperSize(20, 26);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetTitleStyle(0);
  gStyle->SetStatStyle(0);
  // use large fonts
  gStyle->SetTextFont(lhcbFont);
  gStyle->SetTextSize(lhcbTSize);
  gStyle->SetLabelFont(lhcbFont, "x");
  gStyle->SetLabelFont(lhcbFont, "y");
  gStyle->SetLabelFont(lhcbFont, "z");
  gStyle->SetLabelSize(lhcbTSize, "x");
  gStyle->SetLabelSize(lhcbTSize, "y");
  gStyle->SetLabelSize(lhcbTSize, "z");
  gStyle->SetTitleFont(lhcbFont);
  gStyle->SetTitleFont(lhcbFont, "x");
  gStyle->SetTitleFont(lhcbFont, "y");
  gStyle->SetTitleFont(lhcbFont, "z");
  gStyle->SetTitleSize(1.2 * lhcbTSize, "x");
  gStyle->SetTitleSize(1.2 * lhcbTSize, "y");
  gStyle->SetTitleSize(1.2 * lhcbTSize, "z");

  // use medium bold lines and thick markers
  // gStyle->SetLineWidth(lhcbWidth);
  // gStyle->SetFrameLineWidth(lhcbWidth);
  // gStyle->SetHistLineWidth(lhcbWidth);
  // gStyle->SetFuncWidth(lhcbWidth);
  // gStyle->SetGridWidth(lhcbWidth);
  // gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  // gStyle->SetMarkerStyle(20);
  // gStyle->SetMarkerSize(1.0);

  // label offsets
  gStyle->SetLabelOffset(0.010, "X");
  gStyle->SetLabelOffset(0.010, "Y");

  // by default, do not display histogram decorations:
  // gStyle->SetOptStat(0);
  gStyle->SetOptStat("emr"); // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  gStyle->SetStatFormat("6.3g");      // specified as c printf options
  gStyle->SetPaintTextFormat("6.3g"); // specified as c printf options

  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  // gStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  // titles
  gStyle->SetTitleOffset(0.95, "X");
  gStyle->SetTitleOffset(0.95, "Y");
  gStyle->SetTitleOffset(1.2, "Z");
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFont(lhcbFont, "title");
  gStyle->SetTitleX(0.0);
  gStyle->SetTitleY(1.0);
  gStyle->SetTitleW(1.0);
  gStyle->SetTitleH(0.05);

  // look of the statistics box:
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatFont(lhcbFont);
  gStyle->SetStatFontSize(0.05);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.15);

  // put tick marks on top and RHS of plots
  // gStyle->SetPadTickX(1);
  // gStyle->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  gStyle->SetNdivisions(505, "x");
  gStyle->SetNdivisions(510, "y");

  // gStyle->SetLineWidth(3);
  gStyle->SetOptStat(0);

  //---- paint...
  char buf[100];
  char bufb[100];
  TString rootfile;
  TString plotfile;
  TString plotfilePDF;
  TString plotfileO;
  TString plotfileC;
  // TString OutputFileBase	= outbase+outinfo;
  rootfile = loc_rootfiles_data + extension + TString(".root");
  plotfile = loc_plots + extension + TString(".ps");
  plotfilePDF = loc_plots + extension + TString(".pdf");
  plotfileO = plotfilePDF + TString("(");
  plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

  // Begin plotting
  //
  auto legend_stack_z = new TLegend(0.6, 0.67, 0.8, 0.87);
  legend_stack_z->SetTextSize(0.07);
  
  auto legend_stack_jt = new TLegend(0.6, 0.67, 0.8, 0.87);
  legend_stack_jt->SetTextSize(0.07);
  
  auto legend_stack_r = new TLegend(0.6, 0.67, 0.8, 0.87);
  legend_stack_r->SetTextSize(0.07);  
  
  double left = 0.2;
  double step = 0.1;
  double top = 0.8 - step;
  double top2 = 0.5 - step;
  double top2d = 0.9 - step;
  double step2d = 0.06;

  for (int i = 1; i < ptbinsize; i++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);
    
    h1_z_data[i-1] = (TH1D *)h2_ptz_data->ProjectionX(Form("z_data_pt%d",i), i+1, i+1);
    h1_z_truth[i-1] = (TH1D *)h2_ptz_truth->ProjectionX(Form("z_truth_pt%d",i), i+1, i+1);
    
    NormalizeHist(h1_z_data[i-1]);
    NormalizeHist(h1_z_truth[i-1]); 
        
    h1_z_sys[i-1] = (TH1D*)file_sys->Get(Form("z_sys_total_pt%d",i));   
    TH1D *h1_z_data_w_sys = (TH1D*)h1_z_data[i-1]->Clone("h1_z_data_w_sys");
    h1_z_sys[i-1]->Multiply(h1_z_sys[i-1], h1_z_data[i-1]);
    for (int ibin=0; ibin<h1_z_data_w_sys->GetNbinsX(); ++ibin)
    { 
      h1_z_data_w_sys->SetBinError(ibin+1, h1_z_sys[i-1]->GetBinContent(ibin+1));
      std::cout << "stat error pt: " << i << " : " << h1_z_data[i-1]->GetBinError(ibin+1) << std::endl;
      std::cout << "sys error pt: " << i << " : " << h1_z_data_w_sys->GetBinError(ibin+1) << std::endl;      
      
    } 
    
   
/*    
    h1_jt_data[i-1] = (TH1D *)h2_ptjt_data->ProjectionX(Form("jt_data_pt%d",i), i+1, i+1);
    h1_jt_truth[i-1] = (TH1D *)h2_ptjt_truth->ProjectionX(Form("jt_truth_pt%d",i), i+1, i+1);
    h1_jt_ratio_MCData[i-1] = (TH1D *)h2_ptjt_ratio_MCData->ProjectionX(Form("jt_ratio_MCData_pt%d",i), i+1, i+1);     
        
    h1_r_data[i-1] = (TH1D *)h2_ptr_data->ProjectionX(Form("r_data_pt%d",i), i+1, i+1);
    h1_r_truth[i-1] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_pt%d",i), i+1, i+1);
    h1_r_ratio_MCData[i-1] = (TH1D *)h2_ptr_ratio_MCData->ProjectionX(Form("r_ratio_MCData_pt%d",i), i+1, i+1);    
*/
    SetTruthStyle(h1_z_truth[i-1]);
    SetDataStyle(h1_z_data[i-1], 0.7);
    //h1_z_data_w_sys->
    h1_z_data_w_sys->SetFillColorAlpha(16, 0.5);
    h1_z_data_w_sys->SetLineColorAlpha(0, 0.5);
    //h1_z_truth[i-1]->GetXaxis()->SetRange(1, h1_z_truth[i-1]->GetNbinsX() - 1);
    rp[irp] = new TRatioPlot(h1_z_truth[i-1], h1_z_data[i-1]);

    rp[irp]->SetH1DrawOpt("HIST P");
    rp[irp]->SetH2DrawOpt("HIST P");
    // rp[irp]->SetLineColor(kRed);
    rp[irp]->Draw();
    // ccan[ican]->Update();

    rp[irp]->GetLowerRefGraph()->SetMinimum(0.0);
    rp[irp]->GetLowerRefGraph()->SetMaximum(2.0);
    rp[irp]->GetLowerRefYaxis()->SetLabelSize(0.03);
    //SetTruthStyle(rp[irp]->GetLowerRefGraph());

    rp[irp]->GetLowerRefYaxis()->SetTitle("MC/Data");
    // rp[irp]->GetLowerRefGraph()->Draw("PAC");
    // TGaxis::SetMaxDigits(3);
    rp[irp]->GetUpperRefYaxis()->SetMaxDigits(2);
    rp[irp]->GetUpperRefYaxis()->SetTitle("#frac{1}{N_{jets}}#frac{dN}{dz}");
    rp[irp]->GetUpperRefYaxis()->SetTitleOffset(1.1);
    rp[irp]->GetUpperRefYaxis()->SetRangeUser(0, h1_z_truth[i-1]->GetMaximum() * 2.3);
    rp[irp]->GetUpperRefXaxis()->SetTickLength(0.);

    rp[irp]->SetLeftMargin(0.16);
    rp[irp]->SetLowBottomMargin(0.45);

    gPad->Modified();
    gPad->Update();
    rp[irp]->GetUpperPad()->cd();
    h1_z_truth[i-1]->Draw("HIST SAME");
    h1_z_truth[i-1]->Draw("PE SAME");
    //h1_ptktdR_data_stat->Draw("HIST SAME");
    h1_z_data_w_sys->Draw("PE2 SAME");
    h1_z_data[i-1]->Draw("PE SAME");    
    // TGaxis *axis_dR = new TGaxis(gPad->GetUxmax(),gPad->GetUymax(),gPad->GetUxmin(),gPad->GetUymax(),jetradius/exp(dR_max), jetradius/exp(dR_min),510,"+L");
    // TGaxis *axis_dR = new TGaxis(gPad->GetUxmax(),gPad->GetUymax(),gPad->GetUxmin(),gPad->GetUymax(),jetradius/exp(dR_max), jetradius/exp(dR_min) - 0.0001,510,"+L");
    // axis_dR->SetLabelOffset(-0.01);
    // Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);
    // Tl.DrawLatex(left, top + step, "#scale[1.4]{LHCb Unofficial}");
    lhcbName->Draw("SAME");
    Tl.DrawLatex(left, top + step, "#scale[1.2]{AK5 B^{#pm}-tagged jets}");

    Tl.DrawLatex(left, top, "#scale[1.2]{pp #sqrt{s} = 13 TeV}");
    Tl.DrawLatex(left, top - step, Form("#scale[1.2]{%.1f<p_{T,jet}<%.1f GeV/c}", pt_binedges[i], pt_binedges[i+1]));
    Tl.DrawLatex(left, top - 2 * step, "#scale[1.2]{2.5 < #eta_{jet} < 4}");

    if (i == 1)
    {
      legend_stack_z->SetBorderSize(0);
      legend_stack_z->SetFillStyle(0);
      legend_stack_z->SetFillColor(3);
      legend_stack_z->AddEntry(h1_z_data[i-1], "Data");
      legend_stack_z->AddEntry(h1_z_truth[i-1], "PYTHIA8");
      legend_stack_z->Draw("SAME");
    }
    else
    {
      legend_stack_z->Draw("SAME");
    }

    rp[irp]->GetUpperPad()->Update();

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
    ++irp;
}     
    // jT historgrams //
  for (int i = 1; i < ptbinsize; i++)
  {    
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);
   
    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);
    
    h1_jt_data[i-1] = (TH1D *)h2_ptjt_data->ProjectionX(Form("jt_data_pt%d",i), i+1, i+1);
    h1_jt_truth[i-1] = (TH1D *)h2_ptjt_truth->ProjectionX(Form("jt_truth_pt%d",i), i+1, i+1);
    
    NormalizeHist(h1_jt_data[i-1]);
    NormalizeHist(h1_jt_truth[i-1]); 
        
    h1_jt_sys[i-1] = (TH1D*)file_sys->Get(Form("jt_sys_total_pt%d",i));   
    TH1D *h1_jt_data_w_sys = (TH1D*)h1_jt_data[i-1]->Clone("h1_jt_data_w_sys");
    h1_jt_sys[i-1]->Multiply(h1_jt_sys[i-1], h1_jt_data[i-1]);
    for (int ibin=0; ibin<h1_jt_data_w_sys->GetNbinsX(); ++ibin)
    { 
      h1_jt_data_w_sys->SetBinError(ibin+1, h1_jt_sys[i-1]->GetBinContent(ibin+1));
      std::cout << "stat error pt: " << i << " : " << h1_jt_data[i-1]->GetBinError(ibin+1) << std::endl;
      std::cout << "sys error pt: " << i << " : " << h1_jt_data_w_sys->GetBinError(ibin+1) << std::endl;      
      
    } 
    
   
/*    
    h1_jt_data[i-1] = (TH1D *)h2_ptjt_data->ProjectionX(Form("jt_data_pt%d",i), i+1, i+1);
    h1_jt_truth[i-1] = (TH1D *)h2_ptjt_truth->ProjectionX(Form("jt_truth_pt%d",i), i+1, i+1);
    h1_jt_ratio_MCData[i-1] = (TH1D *)h2_ptjt_ratio_MCData->ProjectionX(Form("jt_ratio_MCData_pt%d",i), i+1, i+1);     
        
    h1_r_data[i-1] = (TH1D *)h2_ptr_data->ProjectionX(Form("r_data_pt%d",i), i+1, i+1);
    h1_r_truth[i-1] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_pt%d",i), i+1, i+1);
    h1_r_ratio_MCData[i-1] = (TH1D *)h2_ptr_ratio_MCData->ProjectionX(Form("r_ratio_MCData_pt%d",i), i+1, i+1);    
*/
    SetTruthStyle(h1_jt_truth[i-1]);
    SetDataStyle(h1_jt_data[i-1], 0.7);
    //h1_jt_data_w_sys->
    h1_jt_data_w_sys->SetFillColorAlpha(16, 0.5);
    h1_jt_data_w_sys->SetLineColorAlpha(0, 0.5);
    //h1_jt_truth[i-1]->GetXaxis()->SetRange(1, h1_jt_truth[i-1]->GetNbinsX() - 1);
    rp[irp] = new TRatioPlot(h1_jt_truth[i-1], h1_jt_data[i-1]);

    rp[irp]->SetH1DrawOpt("HIST P");
    rp[irp]->SetH2DrawOpt("HIST P");
    //rp[irp]->GetUpperPad()->SetLogy();
    // rp[irp]->SetLineColor(kRed);
    rp[irp]->Draw();

    rp[irp]->GetLowerRefGraph()->SetMinimum(0.0);
    rp[irp]->GetLowerRefGraph()->SetMaximum(2.0);
    rp[irp]->GetLowerRefYaxis()->SetLabelSize(0.03);
    //rp[irp]->GetUpperRefYaxis()->SetRangeUser(0.001, 5);
    //SetTruthStyle(rp[irp]->GetLowerRefGraph());

    rp[irp]->GetLowerRefYaxis()->SetTitle("MC/Data");
    // rp[irp]->GetLowerRefGraph()->Draw("PAC");
    // TGaxis::SetMaxDigits(3);
    rp[irp]->GetUpperRefYaxis()->SetMaxDigits(2);
    rp[irp]->GetUpperRefYaxis()->SetTitle("#frac{1}{N_{jets}}#frac{dN}{dj_{T}}");
    rp[irp]->GetUpperRefYaxis()->SetTitleOffset(1.1);
    rp[irp]->GetUpperRefYaxis()->SetRangeUser(0, h1_jt_truth[i-1]->GetMaximum() * 2.3);
    rp[irp]->GetUpperRefXaxis()->SetTickLength(0.);

    rp[irp]->SetLeftMargin(0.16);
    rp[irp]->SetLowBottomMargin(0.45);

    gPad->Modified();
    gPad->Update();
    rp[irp]->GetUpperPad()->cd();
    gPad->SetLogy();

    h1_jt_truth[i-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h1_jt_truth[i-1]->SetMinimum(0.00000001);
    h1_jt_truth[i-1]->Draw("HIST SAME");
    h1_jt_truth[i-1]->Draw("PE SAME");
    //h1_ptktdR_data_stat->Draw("HIST SAME");
    h1_jt_data_w_sys->SetMinimum(0.00000001);    
    h1_jt_data[i-1]->SetMinimum(0.00000001);
    h1_jt_data_w_sys->Draw("PE2 SAME");    
    h1_jt_data[i-1]->Draw("PE SAME");

    //gPad->SetLogy();
    // TGaxis *axis_dR = new TGaxis(gPad->GetUxmax(),gPad->GetUymax(),gPad->GetUxmin(),gPad->GetUymax(),jetradius/exp(dR_max), jetradius/exp(dR_min),510,"+L");
    // TGaxis *axis_dR = new TGaxis(gPad->GetUxmax(),gPad->GetUymax(),gPad->GetUxmin(),gPad->GetUymax(),jetradius/exp(dR_max), jetradius/exp(dR_min) - 0.0001,510,"+L");
    // axis_dR->SetLabelOffset(-0.01);
    // Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);
      

    // Tl.DrawLatex(left, top + step, "#scale[1.4]{LHCb Unofficial}");
    lhcbName->Draw("SAME");
    Tl.DrawLatex(left, top2 + step, "#scale[1.2]{AK5 B^{#pm}-tagged jets}");

    Tl.DrawLatex(left, top2, "#scale[1.2]{pp #sqrt{s} = 13 TeV}");
    Tl.DrawLatex(left, top2 - step, Form("#scale[1.2]{%.1f<p_{T,jet}<%.1f GeV/c}", pt_binedges[i], pt_binedges[i+1]));
    Tl.DrawLatex(left, top2 - 2 * step, "#scale[1.2]{2.5 < #eta_{jet} < 4}");

    if (i == 1)
    {
      legend_stack_jt->SetBorderSize(0);
      legend_stack_jt->SetFillStyle(0);
      legend_stack_jt->SetFillColor(3);
      legend_stack_jt->AddEntry(h1_jt_data[i-1], "Data");
      legend_stack_jt->AddEntry(h1_jt_truth[i-1], "PYTHIA8");
      legend_stack_jt->Draw("SAME");
    }
    else
    {
      legend_stack_jt->Draw("SAME");
    }

    rp[irp]->GetUpperPad()->Update();

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
    ++irp;  
  }
  // r histograms! // 
  for (int i = 1; i < ptbinsize; i++)
  {    
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(1, 1, 0.0001, 0.0001);
    ccan[ican]->cd(1);
    
    h1_r_data[i-1] = (TH1D *)h2_ptr_data->ProjectionX(Form("r_data_pt%d",i), i+1, i+1);
    h1_r_truth[i-1] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_pt%d",i), i+1, i+1);
    
    NormalizeHist(h1_r_data[i-1]);
    NormalizeHist(h1_r_truth[i-1]); 
        
    h1_r_sys[i-1] = (TH1D*)file_sys->Get(Form("r_sys_total_pt%d",i));   
    TH1D *h1_r_data_w_sys = (TH1D*)h1_r_data[i-1]->Clone("h1_r_data_w_sys");
    h1_r_sys[i-1]->Multiply(h1_r_sys[i-1], h1_r_data[i-1]);
    for (int ibin=0; ibin<h1_r_data_w_sys->GetNbinsX(); ++ibin)
    { 
      h1_r_data_w_sys->SetBinError(ibin+1, h1_r_sys[i-1]->GetBinContent(ibin+1));
      std::cout << "stat error pt: " << i << " : " << h1_r_data[i-1]->GetBinError(ibin+1) << std::endl;
      std::cout << "sys error pt: " << i << " : " << h1_r_data_w_sys->GetBinError(ibin+1) << std::endl;      
      
    } 
    
   
/*    
    h1_r_data[i-1] = (TH1D *)h2_ptr_data->ProjectionX(Form("r_data_pt%d",i), i+1, i+1);
    h1_r_truth[i-1] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_pt%d",i), i+1, i+1);
    h1_r_ratio_MCData[i-1] = (TH1D *)h2_ptr_ratio_MCData->ProjectionX(Form("r_ratio_MCData_pt%d",i), i+1, i+1);     
        
    h1_r_data[i-1] = (TH1D *)h2_ptr_data->ProjectionX(Form("r_data_pt%d",i), i+1, i+1);
    h1_r_truth[i-1] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_pt%d",i), i+1, i+1);
    h1_r_ratio_MCData[i-1] = (TH1D *)h2_ptr_ratio_MCData->ProjectionX(Form("r_ratio_MCData_pt%d",i), i+1, i+1);    
*/
    SetTruthStyle(h1_r_truth[i-1]);
    SetDataStyle(h1_r_data[i-1], 0.7);
    //h1_r_data_w_sys->
    h1_r_data_w_sys->SetFillColorAlpha(16, 0.5);
    h1_r_data_w_sys->SetLineColorAlpha(0, 0.5);
    //h1_r_truth[i-1]->GetXaxis()->SetRange(1, h1_r_truth[i-1]->GetNbinsX() - 1);
    rp[irp] = new TRatioPlot(h1_r_truth[i-1], h1_r_data[i-1]);

    rp[irp]->SetH1DrawOpt("HIST P");
    rp[irp]->SetH2DrawOpt("HIST P");
    // rp[irp]->SetLineColor(kRed);
    rp[irp]->Draw();
    // ccan[ican]->Update();

    rp[irp]->GetLowerRefGraph()->SetMinimum(0.0);
    rp[irp]->GetLowerRefGraph()->SetMaximum(2.0);
    rp[irp]->GetLowerRefYaxis()->SetLabelSize(0.03);
    //SetTruthStyle(rp[irp]->GetLowerRefGraph());

    rp[irp]->GetLowerRefYaxis()->SetTitle("MC/Data");
    // rp[irp]->GetLowerRefGraph()->Draw("PAC");
    // TGaxis::SetMaxDigits(3);
    rp[irp]->GetUpperRefYaxis()->SetMaxDigits(2);
    rp[irp]->GetUpperRefYaxis()->SetTitle("#frac{1}{N_{jets}}#frac{dN}{dr}");
    rp[irp]->GetUpperRefYaxis()->SetTitleOffset(1.1);
    rp[irp]->GetUpperRefYaxis()->SetRangeUser(0, h1_r_truth[i-1]->GetMaximum() * 2.3);
    rp[irp]->GetUpperRefXaxis()->SetTickLength(0.);

    rp[irp]->SetLeftMargin(0.16);
    rp[irp]->SetLowBottomMargin(0.45);

    gPad->Modified();
    gPad->Update();
    rp[irp]->GetUpperPad()->cd();
    gPad->SetLogy();
    h1_r_truth[i-1]->SetMinimum(0.00001);
    h1_r_truth[i-1]->Draw("HIST SAME");
    h1_r_truth[i-1]->Draw("PE SAME");
    //h1_ptktdR_data_stat->Draw("HIST SAME");
    h1_r_data_w_sys->SetMinimum(0.00001);
    h1_r_data[i-1]->SetMinimum(0.00001);
    h1_r_data_w_sys->Draw("PE2 SAME");    
    h1_r_data[i-1]->Draw("PE SAME");
    // TGaxis *axis_dR = new TGaxis(gPad->GetUxmax(),gPad->GetUymax(),gPad->GetUxmin(),gPad->GetUymax(),jetradius/exp(dR_max), jetradius/exp(dR_min),510,"+L");
    // TGaxis *axis_dR = new TGaxis(gPad->GetUxmax(),gPad->GetUymax(),gPad->GetUxmin(),gPad->GetUymax(),jetradius/exp(dR_max), jetradius/exp(dR_min) - 0.0001,510,"+L");
    // axis_dR->SetLabelOffset(-0.01);
    // Tl.DrawLatex(0.85, 0.95, Form("#DeltaR"));
    // axis_dR->Draw("SAME");
    // axis_dR->SetNdivisions(-510);

    // Tl.DrawLatex(left, top + step, "#scale[1.4]{LHCb Unofficial}");
    lhcbName->Draw("SAME");
    Tl.DrawLatex(left, top2 + step, "#scale[1.2]{AK5 B^{#pm}-tagged jets}");

    Tl.DrawLatex(left, top2, "#scale[1.2]{pp #sqrt{s} = 13 TeV}");
    Tl.DrawLatex(left, top2 - step, Form("#scale[1.2]{%.1f<p_{T,jet}<%.1f GeV/c}", pt_binedges[i], pt_binedges[i+1]));
    Tl.DrawLatex(left, top2 - 2 * step, "#scale[1.2]{2.5 < #eta_{jet} < 4}");

    if (i == 1)
    {
      legend_stack_r->SetBorderSize(0);
      legend_stack_r->SetFillStyle(0);
      legend_stack_r->SetFillColor(3);
      legend_stack_r->AddEntry(h1_r_data[i-1], "Data");
      legend_stack_r->AddEntry(h1_r_truth[i-1], "PYTHIA8");
      legend_stack_r->Draw("SAME");
    }
    else
    {
      legend_stack_r->Draw("SAME");
    }

    rp[irp]->GetUpperPad()->Update();

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
    ++irp;
  }  
  
  for (int i = 1; i < ptbinsize; i++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);
    
    h3_ptzjt_data->GetZaxis()->SetRange(i+1, i+1);
    h3_ptzjt_truth->GetZaxis()->SetRange(i+1, i+1);   
    
    h2_zjt_data[i-1] = (TH2D *)h3_ptzjt_data->Project3D("yx");
    h2_zjt_truth[i-1] = (TH2D *)h3_ptzjt_truth->Project3D("yx");     
    h2_zjt_data[i-1]->SetName(Form("zjt_pt%d",i));     
    h2_zjt_truth[i-1]->SetName(Form("zjt_truth_pt%d",i));     
    
    NormalizeHist(h2_zjt_data[i-1]);
    NormalizeHist(h2_zjt_truth[i-1]); 
        
    h2_zjt_sys[i-1] = (TH2D*)file_sys->Get(Form("zjt_sys_total_pt%d",i));   
    h2_zjt_sys[i-1]->Multiply(h2_zjt_sys[i-1], h2_zjt_data[i-1]);
    
    h2_zjt_tot_unc[i-1] = (TH2D*)h2_zjt_data[i-1]->Clone(Form("zjt_tot_unc_pt%d", i));
    for (int xbin=0; xbin<h2_zjt_data[i-1]->GetNbinsX(); ++xbin)
    { 
      for (int ybin=0; ybin<h2_zjt_data[i-1]->GetNbinsY(); ++ybin)
      {
        h2_zjt_tot_unc[i-1]->SetBinContent( xbin+1, ybin+1,  std::sqrt(std::pow(h2_zjt_data[i-1]->GetBinError(xbin+1, ybin+1),2) + std::pow(h2_zjt_sys[i-1]->GetBinContent(xbin+1, ybin+1), 2) ) );
        //std::cout << "stat error pt: " << i << " : " << h1_r_data[i-1]->GetBinError(xbin+1) << std::endl;
        //std::cout << "sys error pt: " << i << " : " << h1_r_data_w_sys->GetBinError(xbin+1) << std::endl; 
      }     
      
    } 
        
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zjt_data[i-1]->GetXaxis()->SetTitle("z");
    h2_zjt_data[i-1]->GetYaxis()->SetTitle("j_{T} [GeV/c]");
    //h2_zjt_data[i-1]->GetYaxis()->SetLimits(0.0, 20.0);
    h2_zjt_data[i-1]->Draw("COLZ");

    lhcbName->Draw("SAME");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{AK5 B^{#pm}-tagged jets              pp #sqrt{s} = 13 TeV}");    
    //Tl.DrawLatex(left, top2d, "#scale[0.8]{}");
    Tl.DrawLatex(left, top2d, Form("#scale[0.8]{%.1f<p_{T,jet}<%.1f GeV/c        2.5 < #eta_{jet} < 4}", pt_binedges[i], pt_binedges[i+1]));
    //Tl.DrawLatex(left, top2d - 2 * step2d, "#scale[0.8]{}");    
    
    ccan[ican]->cd(2); 
    h2_zjt_tot_unc[i-1]->SetMinimum(0.0001);          
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zjt_tot_unc[i-1]->GetXaxis()->SetTitle("z");
    h2_zjt_tot_unc[i-1]->GetYaxis()->SetTitle("j_{T} [GeV/c]");      
    h2_zjt_tot_unc[i-1]->Draw("COLZ");  
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{Total uncertainty (statistical + systematic)}");     
    
    ccan[ican]->cd(3);              
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zjt_truth[i-1]->GetXaxis()->SetTitle("z");
    h2_zjt_truth[i-1]->GetYaxis()->SetTitle("j_{T} [GeV/c]");        
    h2_zjt_truth[i-1]->Draw("COLZ");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{PYTHIA8}"); 
    
    ccan[ican]->cd(4);
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zjt_ratio_MCData[i-1] = (TH2D*)h2_zjt_truth[i-1]->Clone(Form("h2_zjt_ratio_pt%d",i));
    h2_zjt_ratio_MCData[i-1]->Divide(h2_zjt_truth[i-1], h2_zjt_data[i-1]);    
    h2_zjt_ratio_MCData[i-1]->SetMinimum(0.0001);        
    h2_zjt_ratio_MCData[i-1]->GetXaxis()->SetTitle("z");
    h2_zjt_ratio_MCData[i-1]->GetYaxis()->SetTitle("j_{T} [GeV/c]");    
    h2_zjt_ratio_MCData[i-1]->Draw("COLZ");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{MC/Data Ratio}");     
    
    ccan[ican]->cd();
    //gPad->SetLogz();
    ccan[ican]->Update();
    if (ican == 0)
    {
      ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
      ccan[ican]->Print(plotfilePDF.Data());
    } 
  }     
  // zr plots //
  for (int i = 1; i < ptbinsize; i++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);
    
    h3_ptzr_data->GetZaxis()->SetRange(i+1, i+1);
    h3_ptzr_truth->GetZaxis()->SetRange(i+1, i+1);   
    
    h2_zr_data[i-1] = (TH2D *)h3_ptzr_data->Project3D("yx");
    h2_zr_truth[i-1] = (TH2D *)h3_ptzr_truth->Project3D("yx");     
    h2_zr_data[i-1]->SetName(Form("zr_pt%d",i));     
    h2_zr_truth[i-1]->SetName(Form("zr_truth_pt%d",i));     
    
    NormalizeHist(h2_zr_data[i-1]);
    NormalizeHist(h2_zr_truth[i-1]); 
        
    h2_zr_sys[i-1] = (TH2D*)file_sys->Get(Form("zr_sys_total_pt%d",i));   
    h2_zr_sys[i-1]->Multiply(h2_zr_sys[i-1], h2_zr_data[i-1]);
    
    h2_zr_tot_unc[i-1] = (TH2D*)h2_zr_data[i-1]->Clone(Form("zr_tot_unc_pt%d", i));
    for (int xbin=0; xbin<h2_zr_data[i-1]->GetNbinsX(); ++xbin)
    { 
      for (int ybin=0; ybin<h2_zr_data[i-1]->GetNbinsY(); ++ybin)
      {
        h2_zr_tot_unc[i-1]->SetBinContent( xbin+1, ybin+1,  std::sqrt(std::pow(h2_zr_data[i-1]->GetBinError(xbin+1, ybin+1),2) + std::pow(h2_zr_sys[i-1]->GetBinContent(xbin+1, ybin+1), 2) ) );
        //std::cout << "stat error pt: " << i << " : " << h1_r_data[i-1]->GetBinError(xbin+1) << std::endl;
        //std::cout << "sys error pt: " << i << " : " << h1_r_data_w_sys->GetBinError(xbin+1) << std::endl; 
      }     
      
    } 
        
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zr_data[i-1]->GetXaxis()->SetTitle("z");
    h2_zr_data[i-1]->GetYaxis()->SetTitle("r");
    h2_zr_data[i-1]->Draw("COLZ");

    lhcbName->Draw("SAME");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{AK5 B^{#pm}-tagged jets              pp #sqrt{s} = 13 TeV}");    
    //Tl.DrawLatex(left, top2d, "#scale[0.8]{}");
    Tl.DrawLatex(left, top2d, Form("#scale[0.8]{%.1f<p_{T,jet}<%.1f GeV/c        2.5 < #eta_{jet} < 4}", pt_binedges[i], pt_binedges[i+1]));
    //Tl.DrawLatex(left, top2d - 2 * step2d, "#scale[0.8]{}");  
    
    ccan[ican]->cd(2); 
    h2_zr_tot_unc[i-1]->SetMinimum(0.0001);          
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zr_tot_unc[i-1]->GetXaxis()->SetTitle("z");
    h2_zr_tot_unc[i-1]->GetYaxis()->SetTitle("r");      
    h2_zr_tot_unc[i-1]->Draw("COLZ");  
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{Total uncertainty (statistical + systematic)}");     
    
    ccan[ican]->cd(3);              
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zr_truth[i-1]->GetXaxis()->SetTitle("z");
    h2_zr_truth[i-1]->GetYaxis()->SetTitle("r");        
    h2_zr_truth[i-1]->Draw("COLZ");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{PYTHIA8}"); 
    
    ccan[ican]->cd(4);
    gPad->SetLogz();
    gPad->SetLogy();
    h2_zr_ratio_MCData[i-1] = (TH2D*)h2_zr_truth[i-1]->Clone(Form("h2_zr_ratio_pt%d",i));
    h2_zr_ratio_MCData[i-1]->Divide(h2_zr_truth[i-1], h2_zr_data[i-1]);    
    h2_zr_ratio_MCData[i-1]->SetMinimum(0.0001);        
    h2_zr_ratio_MCData[i-1]->GetXaxis()->SetTitle("z");
    h2_zr_ratio_MCData[i-1]->GetYaxis()->SetTitle("r");    
    h2_zr_ratio_MCData[i-1]->Draw("COLZ");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{MC/Data Ratio}");     
    
    ccan[ican]->cd();
    //gPad->SetLogz();
    ccan[ican]->Update();
    if (ican == 0)
    {
      ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
      ccan[ican]->Print(plotfilePDF.Data());
    } 
  }      
  
  // jtr plots //
  for (int i = 1; i < ptbinsize; i++)
  {
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    ccan[ican]->SetFillColor(10);

    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2, 0.0001, 0.0001);
    ccan[ican]->cd(1);
    
    h3_ptjtr_data->GetZaxis()->SetRange(i+1, i+1);
    h3_ptjtr_truth->GetZaxis()->SetRange(i+1, i+1);   
    
    h2_jtr_data[i-1] = (TH2D *)h3_ptjtr_data->Project3D("yx");
    h2_jtr_truth[i-1] = (TH2D *)h3_ptjtr_truth->Project3D("yx");     
    h2_jtr_data[i-1]->SetName(Form("jtr_pt%d",i));     
    h2_jtr_truth[i-1]->SetName(Form("jtr_truth_pt%d",i));     
    
    NormalizeHist(h2_jtr_data[i-1]);
    NormalizeHist(h2_jtr_truth[i-1]); 
        
    h2_jtr_sys[i-1] = (TH2D*)file_sys->Get(Form("jtr_sys_total_pt%d",i));   
    h2_jtr_sys[i-1]->Multiply(h2_jtr_sys[i-1], h2_jtr_data[i-1]);
    
    h2_jtr_tot_unc[i-1] = (TH2D*)h2_jtr_data[i-1]->Clone(Form("jtr_tot_unc_pt%d", i));
    for (int xbin=0; xbin<h2_jtr_data[i-1]->GetNbinsX(); ++xbin)
    { 
      for (int ybin=0; ybin<h2_jtr_data[i-1]->GetNbinsY(); ++ybin)
      {
        h2_jtr_tot_unc[i-1]->SetBinContent( xbin+1, ybin+1,  std::sqrt(std::pow(h2_jtr_data[i-1]->GetBinError(xbin+1, ybin+1),2) + std::pow(h2_jtr_sys[i-1]->GetBinContent(xbin+1, ybin+1), 2) ) );
        //std::cout << "stat error pt: " << i << " : " << h1_r_data[i-1]->GetBinError(xbin+1) << std::endl;
        //std::cout << "sys error pt: " << i << " : " << h1_r_data_w_sys->GetBinError(xbin+1) << std::endl; 
      }     
      
    } 
        
    gPad->SetLogz();
    gPad->SetLogy();
    gPad->SetLogx();
    h2_jtr_data[i-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h2_jtr_data[i-1]->GetYaxis()->SetTitle("r");
    h2_jtr_data[i-1]->Draw("COLZ");

    lhcbName->Draw("SAME");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{AK5 B^{#pm}-tagged jets              pp #sqrt{s} = 13 TeV}");    
    //Tl.DrawLatex(left, top2d, "#scale[0.8]{}");
    Tl.DrawLatex(left, top2d, Form("#scale[0.8]{%.1f<p_{T,jet}<%.1f GeV/c        2.5 < #eta_{jet} < 4}", pt_binedges[i], pt_binedges[i+1]));
    //Tl.DrawLatex(left, top2d - 2 * step2d, "#scale[0.8]{}");  
    
    ccan[ican]->cd(2); 
    h2_jtr_tot_unc[i-1]->SetMinimum(0.0001);          
    gPad->SetLogz();
    gPad->SetLogy();
    gPad->SetLogx();
    h2_jtr_tot_unc[i-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h2_jtr_tot_unc[i-1]->GetYaxis()->SetTitle("r");      
    h2_jtr_tot_unc[i-1]->Draw("COLZ");  
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{Total uncertainty (statistical + systematic)}");     
    
    ccan[ican]->cd(3);              
    gPad->SetLogz();
    gPad->SetLogy();
    gPad->SetLogx();
    h2_jtr_truth[i-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h2_jtr_truth[i-1]->GetYaxis()->SetTitle("r");        
    h2_jtr_truth[i-1]->Draw("COLZ");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{PYTHIA8}"); 
    
    ccan[ican]->cd(4);
    gPad->SetLogz();
    gPad->SetLogy();
    gPad->SetLogx();
    h2_jtr_ratio_MCData[i-1] = (TH2D*)h2_jtr_truth[i-1]->Clone(Form("h2_jtr_ratio_pt%d",i));
    h2_jtr_ratio_MCData[i-1]->Divide(h2_jtr_truth[i-1], h2_jtr_data[i-1]);    
    h2_jtr_ratio_MCData[i-1]->SetMinimum(0.0001);        
    h2_jtr_ratio_MCData[i-1]->GetXaxis()->SetTitle("j_{T} [GeV/c]");
    h2_jtr_ratio_MCData[i-1]->GetYaxis()->SetTitle("r");    
    h2_jtr_ratio_MCData[i-1]->Draw("COLZ");
    Tl.DrawLatex(left, top2d + step2d, "#scale[0.8]{MC/Data Ratio}");     
    
    ccan[ican]->cd();
    //gPad->SetLogz();
    ccan[ican]->Update();
    if (ican == 0)
    {
      ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
      ccan[ican]->Print(plotfilePDF.Data());
    } 
  }    
  
  if (ican > -1)
  {
    cout << " You plotted " << ican + 1 << " canvasses......." << endl;
    ccan[ican]->Print(plotfileC.Data());
  }



  //file_write->Write();
  //file_write->Close();
  //delete file_write;
  //
}


