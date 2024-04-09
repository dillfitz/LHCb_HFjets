//
//  BH_DM_Obsv_Plots.c
//  
//
//  Created by Jose Arias on 6/18/23.
//

#include "TAxis.h"
#include "TCanvas.h"
#include "TH1.h"
#include <cmath>
#include <TCanvas.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TStyle.h>
#include <vector>
#include "TFile.h"
#include "TH1.h"

using namespace std;

void BH_DM_Obsv_Plots(){
    
    double p_j_DM, p_j_BH, p_h_DM, p_h_BH;
    
    TFile fread("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_DM_BH_Comparison.root", "READ");
    
    // Jets Kinematics
    TH1F *DMpj = (TH1F*)fread.Get("jetpDMH");
    TH1F *BHpj = (TH1F*)fread.Get("jetpBHH");
    
    // HF Kinematics
    TH1F *DMpb = (TH1F*)fread.Get("HFpDMH");
    TH1F *BHpb = (TH1F*)fread.Get("HFpBHH");
    
    // Kaons Kinematics
    TH1F *DMpK = (TH1F*)fread.Get("KaonpDMH");
    TH1F *BHpK = (TH1F*)fread.Get("KaonpBHH");
    
    // mu(-+) |p|
    TH1F *DMpmum = (TH1F*)fread.Get("mumpDMH");
    TH1F *BHpmum = (TH1F*)fread.Get("mumpBHH");

    TH1F *DMpmup = (TH1F*)fread.Get("muppDMH");
    TH1F *BHpmup = (TH1F*)fread.Get("muppBHH");
    
    // mu(-+) pt
    TH1F *DMptmup = (TH1F*)fread.Get("mupptDMH");
    TH1F *BHptmup = (TH1F*)fread.Get("mupptBHH");
    
    TH1F *DMptmum = (TH1F*)fread.Get("mumptDMH");
    TH1F *BHptmum = (TH1F*)fread.Get("mumptBHH");

//    TH1F *Jetp = new TH1F("Jetp", "Jetp; |p| ",DMnbinsJ ,0.0, 3000.0);
//    TH1F *HFp = new TH1F("HFp", "HFp; |p|", DMnbinsB, 0.0, 10.0);
//
    const Int_t DMpjBins = DMpj->GetNbinsX();
    const Int_t BHpjBins = BHpj->GetNbinsX();

    double xmin = DMpj->GetXaxis()->GetXmin();
    double xmax = DMpj->GetXaxis()->GetXmax();
    
    double ymin = BHpj->GetXaxis()->GetXmin();
    double ymax = BHpj->GetXaxis()->GetXmax();
    
    const Double_t* xDMpjBinEdges = DMpj->GetXaxis()->GetXbins()->GetArray();
    const Double_t* xBHpjBinEdges = BHpj->GetXaxis()->GetXbins()->GetArray();

    TH2D* Jetp = new TH2D("Jetp", ";|p|_{DM} [GeV/c]; |p|_{BH} [GeV/c] ", DMpjBins,
                          xmin, xmax,
                          BHpjBins,ymin, ymax);

 // Plotting Jet's |p|
    TCanvas* c=new TCanvas("c","c", 700, 900);
    c->Divide(1, 1);
    c->cd(1);
    
    DMpj->Sumw2();
    TH1F *DM_pnorm = (TH1F *)DMpj->Clone("DM_pnorm");
    DM_pnorm->SetTitle(" Jet |p|");
//    DM_pnorm->Scale((1)/(DM_pnorm->Integral()), "width");
    DM_pnorm->SetLineColor(2);
    DM_pnorm->SetStats(0);
    DM_pnorm->Draw("Hist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();

    BHpj->Sumw2();
    TH1F *BH_pnorm= (TH1F *)BHpj->Clone("BH_pnorm");
//    BH_pnorm->Scale((1)/(BHpj->Integral()), "width");
    BH_pnorm->SetLineColor(4);
    BH_pnorm->SetStats(0);
    BH_pnorm->Draw("SameHist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();
    
    TLegend *leg1 = new TLegend(0.68, 0.68, 0.85, 0.8);
    leg1->SetBorderSize(0);
    leg1->AddEntry(BH_pnorm, "Bhadron Stream", "PE");
    leg1->AddEntry(DM_pnorm, "Dimuon Stream", "L");
    leg1->Draw("SAME");
 
///////   Ploting HF |p|
    TCanvas* c1=new TCanvas("c1","c1", 700, 900);
    c1->Divide(1, 1);
    c1->cd(1);
    
    DMpb->Sumw2();
    TH1F *DM_pnormb = (TH1F *)DMpb->Clone("DM_pnormb");
    DM_pnormb->SetTitle("B^{#pm} |p|");
//    DM_pnorm->Scale((1)/(DM_pnorm->Integral()), "width");
    DM_pnormb ->SetLineColor(2);
    DM_pnormb->SetStats(0);
    DM_pnormb->Draw("Hist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();

    BHpb->Sumw2();
    TH1F *BH_pnormb= (TH1F *)BHpb->Clone("BH_pnormb");
//    BH_pnorm->Scale((1)/(BHpj->Integral()), "width");
    BH_pnormb->SetLineColor(4);
    BH_pnormb->SetStats(0);
    BH_pnormb->Draw("SameHist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();
    
    TLegend *leg2 = new TLegend(0.68, 0.68, 0.85, 0.8);
    leg2->SetBorderSize(0);
    leg2->AddEntry(BH_pnormb, "Bhadron Stream", "PE");
    leg2->AddEntry(DM_pnormb, "Dimuon Stream", "L");
    leg2->Draw("SAME");

    ///////   Ploting mu(-)  |p|
    TCanvas* c2=new TCanvas("c2","c2", 700, 900);
    c2->Divide(1, 1);
    c2->cd(1);
    
    DMpmum->Sumw2();
    TH1F *DM_pmum = (TH1F *)DMpmum->Clone("DM_pmum");
    DM_pmum->SetTitle("#mu^{-} |p|");
//    DM_pnorm->Scale((1)/(DM_pnorm->Integral()), "width");
    DM_pmum ->SetLineColor(2);
    DM_pmum->SetStats(0);
    DM_pmum->Draw("Hist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();

    BHpmum->Sumw2();
    TH1F *BH_pmum= (TH1F *)BHpmum->Clone("BH_pmum");
//    BH_pnorm->Scale((1)/(BHpj->Integral()), "width");
    BH_pmum->SetLineColor(4);
    BH_pmum->SetStats(0);
    BH_pmum->Draw("SameHist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();
    
    TLegend *leg3 = new TLegend(0.68, 0.68, 0.85, 0.8);
    leg3->SetBorderSize(0);
    leg3->AddEntry(BH_pmum, "Bhadron Stream", "PE");
    leg3->AddEntry(DM_pmum, "Dimuon Stream", "L");
    leg3->Draw("SAME");

    ///////   Ploting mu(-)  |p|
    TCanvas* c3=new TCanvas("c3","c3", 700, 900);
    c3->Divide(1, 1);
    c3->cd(1);
    
    DMpmup->Sumw2();
    TH1F *DM_pmup = (TH1F *)DMpmup->Clone("DM_pmup");
    DM_pmup->SetTitle("#mu^{+} |p|");
//    DM_pnorm->Scale((1)/(DM_pnorm->Integral()), "width");
    DM_pmup ->SetLineColor(2);
    DM_pmup->SetStats(0);
    DM_pmup->Draw("Hist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();

    BHpmup->Sumw2();
    TH1F *BH_pmup= (TH1F *)BHpmup->Clone("BH_pmup");
//    BH_pnorm->Scale((1)/(BHpj->Integral()), "width");
    BH_pmup->SetLineColor(4);
    BH_pmup->SetStats(0);
    BH_pmup->Draw("SameHist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();
    
    TLegend *leg4 = new TLegend(0.68, 0.68, 0.85, 0.8);
    leg4->SetBorderSize(0);
    leg4->AddEntry(BH_pmup, "BHadron Stream", "PE");
    leg4->AddEntry(DM_pmup, "DiMuon Stream", "L");
    leg4->Draw("SAME");
    
    ///////   P l o t i n g   mu(+)  pt
    TCanvas* c4=new TCanvas("c4","c4", 700, 900);
    c4->Divide(1, 1);
    c4->cd(1);
    
    DMptmup->Sumw2();
    TH1F *DM_ptmup = (TH1F *)DMptmup->Clone("DM_ptmup");
    DM_ptmup->SetTitle("#mu^{+} p_{T}");
//    DM_pnorm->Scale((1)/(DM_pnorm->Integral()), "width");
    DM_ptmup ->SetLineColor(2);
    DM_ptmup->SetStats(0);
    DM_ptmup->Draw("Hist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();

    BHptmup->Sumw2();
    TH1F *BH_ptmup= (TH1F *)BHptmup->Clone("BH_ptmup");
//    BH_pnorm->Scale((1)/(BHpj->Integral()), "width");
    BH_ptmup->SetLineColor(4);
    BH_ptmup->SetStats(0);
    BH_ptmup->Draw("SameHist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();
    
    TLegend *leg5 = new TLegend(0.68, 0.68, 0.85, 0.8);
    leg5->SetBorderSize(0);
    leg5->AddEntry(BH_ptmup, "BHadron Stream", "PE");
    leg5->AddEntry(DM_ptmup, "DiMuon Stream", "L");
    leg5->Draw("SAME");
    
    ///////   P l o t i n g   mu(-)  pt
    TCanvas* c5=new TCanvas("c5","c5", 700, 900);
    c5->Divide(1, 1);
    c5->cd(1);
    
    DMptmum->Sumw2();
    TH1F *DM_ptmum = (TH1F *)DMptmum->Clone("DM_ptmum");
    DM_ptmum->SetTitle("#mu^{-} p_{T}");
//    DM_pnorm->Scale((1)/(DM_pnorm->Integral()), "width");
    DM_ptmum ->SetLineColor(2);
    DM_ptmum->SetStats(0);
    DM_ptmum->Draw("Hist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();

    BHptmum->Sumw2();
    TH1F *BH_ptmum= (TH1F *)BHptmum->Clone("BH_ptmum");
//    BH_pnorm->Scale((1)/(BHpj->Integral()), "width");
    BH_ptmum->SetLineColor(4);
    BH_ptmum->SetStats(0);
    BH_ptmum->Draw("SameHist");
    gPad->SetLogy();
//    gPad->SetLogx();
    gPad->Update();
    
    TLegend *leg6 = new TLegend(0.68, 0.69, 0.85, 0.8);
    leg6->SetBorderSize(0);
    leg6->AddEntry(BH_ptmum, "BHadron Stream", "PE");
    leg6->AddEntry(DM_ptmum, "DiMuon Stream", "L");
    leg6->Draw("SAME");
    
    c->SaveAs("/Users/josearias18/Desktop/BH_DM_Comp_Plots/BHDM_Jetp.pdf");
    c1->SaveAs("/Users/josearias18/Desktop/BH_DM_Comp_Plots/BHDM_HFp.pdf");
    c2->SaveAs("/Users/josearias18/Desktop/BH_DM_Comp_Plots/BHDM_mum_p.pdf");
    c3->SaveAs("/Users/josearias18/Desktop/BH_DM_Comp_Plots/BHDM_mup_p.pdf");
    c4->SaveAs("/Users/josearias18/Desktop/BH_DM_Comp_Plots/BHDM_mup_pt.pdf");
    c5->SaveAs("/Users/josearias18/Desktop/BH_DM_Comp_Plots/BHDM_mum_pt.pdf");
    
}
