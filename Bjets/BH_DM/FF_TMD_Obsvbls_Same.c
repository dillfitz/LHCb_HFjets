//
//  FF_TMD_Obsvbls_Same.c
//
//
//  Created by Jose Arias on 6/19/23.
//

#include <cmath>
#include <stdio.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TStyle.h>
#include <vector>
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1.h"

using namespace std;

void FF_TMD_Obsvbls_Same() {
    
    TFile f_BH("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_BH_Observables.root", "READ");
    TFile f_DMsV2("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_DM_SVonly3_Observables.root", "READ");
    TFile f_DMsV0("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_DM_SV0_Observables.root", "READ");
    TFile f_DMnoSV("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_DM_noSV_Observables.root", "READ");

    ////// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BHadron Stream Observables
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1F *z_BH = (TH1F *)f_BH.Get("z");
    TH1F *jt_BH = (TH1F *)f_BH.Get("jt");
    TH1F *r_BH = (TH1F *)f_BH.Get("r");

    TH1F *z2030_BH = (TH1F *)f_BH.Get("z_20_30");
    TH1F *z3050_BH = (TH1F *)f_BH.Get("z_30_50");
    TH1F *z50100_BH = (TH1F *)f_BH.Get("z_50_100");

    TH1F *jt2030_BH = (TH1F *)f_BH.Get("jt_20_30");
    TH1F *jt3050_BH = (TH1F *)f_BH.Get("jt_30_50");
    TH1F *jt50100_BH = (TH1F *)f_BH.Get("jt_50_100");

    TH1F *r2030_BH = (TH1F *)f_BH.Get("r_20_30");
    TH1F *r3050_BH = (TH1F *)f_BH.Get("r_30_50");
    TH1F *r50100_BH = (TH1F *)f_BH.Get("r_50_100");

    ////// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Dimuon Stream Observables (SV2)
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1F *z_DMsV2 = (TH1F *)f_DMsV2.Get("z");
    TH1F *jt_DMsV2 = (TH1F *)f_DMsV2.Get("jt");
    TH1F *r_DMsV2 = (TH1F *)f_DMsV2.Get("r");

    TH1F *z2030_DMsV2 = (TH1F *)f_DMsV2.Get("z_20_30");
    TH1F *jt2030_DMsV2 = (TH1F *)f_DMsV2.Get("jt_20_30");
    TH1F *r2030_DMsV2 = (TH1F *)f_DMsV2.Get("r_20_30");

    TH1F *z3050_DMsV2 = (TH1F *)f_DMsV2.Get("z_30_50");
    TH1F *jt3050_DMsV2 = (TH1F *)f_DMsV2.Get("jt_30_50");
    TH1F *r3050_DMsV2 = (TH1F *)f_DMsV2.Get("r_30_50");

    TH1F *z50100_DMsV2 = (TH1F *)f_DMsV2.Get("z_50_100");
    TH1F *jt50100_DMsV2 = (TH1F *)f_DMsV2.Get("jt_50_100");
    TH1F *r50100_DMsV2 = (TH1F *)f_DMsV2.Get("r_50_100");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Dimuon Stream Observables (SV0)
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1F *z_DMsV0 = (TH1F *)f_DMsV0.Get("z");
    TH1F *jt_DMsV0 = (TH1F *)f_DMsV0.Get("jt");
    TH1F *r_DMsV0 = (TH1F *)f_DMsV0.Get("r");

    TH1F *z2030_DMsV0 = (TH1F *)f_DMsV0.Get("z_20_30");
    TH1F *jt2030_DMsV0 = (TH1F *)f_DMsV0.Get("jt_20_30");
    TH1F *r2030_DMsV0 = (TH1F *)f_DMsV0.Get("r_20_30");

    TH1F *z3050_DMsV0 = (TH1F *)f_DMsV0.Get("z_30_50");
    TH1F *jt3050_DMsV0 = (TH1F *)f_DMsV0.Get("jt_30_50");
    TH1F *r3050_DMsV0 = (TH1F *)f_DMsV0.Get("r_30_50");

    TH1F *z50100_DMsV0 = (TH1F *)f_DMsV0.Get("z_50_100");
    TH1F *jt50100_DMsV0 = (TH1F *)f_DMsV0.Get("jt_50_100");
    TH1F *r50100_DMsV0 = (TH1F *)f_DMsV0.Get("r_50_100");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Dimuon Stream Observables (noSV)
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1F *z_DMnoSV = (TH1F *)f_DMnoSV.Get("z");
    TH1F *jt_DMnoSV = (TH1F *)f_DMnoSV.Get("jt");
    TH1F *r_DMnoSV = (TH1F *)f_DMnoSV.Get("r");

    TH1F *z2030_DMnoSV = (TH1F *)f_DMnoSV.Get("z_20_30");
    TH1F *jt2030_DMnoSV = (TH1F *)f_DMnoSV.Get("jt_20_30");
    TH1F *r2030_DMnoSV = (TH1F *)f_DMnoSV.Get("r_20_30");

    TH1F *z3050_DMnoSV = (TH1F *)f_DMnoSV.Get("z_30_50");
    TH1F *jt3050_DMnoSV = (TH1F *)f_DMnoSV.Get("jt_30_50");
    TH1F *r3050_DMnoSV = (TH1F *)f_DMnoSV.Get("r_30_50");

    TH1F *z50100_DMnoSV = (TH1F *)f_DMnoSV.Get("z_50_100");
    TH1F *jt50100_DMnoSV = (TH1F *)f_DMnoSV.Get("jt_50_100");
    TH1F *r50100_DMnoSV = (TH1F *)f_DMnoSV.Get("r_50_100");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Canvas 0 (DM: z_DM_sV0, z_DM_noSV, z_DM_SV2)
//    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
//    TCanvas *c = new TCanvas("c", "c", 1100, 1200);
//    gStyle->SetOptStat(0);
//    c->Divide(1, 1);
//    c->cd(1);
//
////        TH1F *z_zh= (TH1F *)zH->Clone("z_zh");
////        zH->SetLineColor(2);
//
////        zH->SetFillColor(kRed);
//    z_DMsV0->SetFillColor(kRed);
//    z_DMsV0->SetMarkerStyle(20);
//    z_DMsV0->SetMarkerSize(0.78);
//    z_DMsV0->SetMarkerColor(kRed);
//    z_DMsV0->Draw("E1 E2 X0"); //"E1 X0 PLC PMC"
//
////        zh->SetFillColor(kBlack);
//    z_DMnoSV->SetFillColor(kBlack);
//    z_DMnoSV->SetMarkerStyle(20);
//    z_DMnoSV->SetMarkerSize(0.78);
//    z_DMnoSV->SetMarkerColor(kBlack);
//    //    zh->Draw("Same  E1 E2 X0 ");
//    z_DMnoSV->Draw(" Same E1 E2 X0 ");
//
//    z_DMsV2->SetFillColor(kBlue);
//    z_DMsV2->SetMarkerStyle(20);
//    z_DMsV2->SetMarkerSize(0.78);
//    z_DMsV2->SetMarkerColor(kBlue);
//    z_DMsV2->Draw("Same E1 E2 X0");
//
//    gPad->Modified();
//
//    TLegend *leg = new TLegend(0.18, 0.68, 0.45, 0.88);
//    gStyle->SetLegendTextSize(0.03);
//    leg->SetHeader("Dimuon Stream: p_{T} > 20 GeV/c", "C");
//    leg->SetBorderSize(0);
//    leg->AddEntry(z_DMsV0, " S.V. = 0", "PE");
//    leg->AddEntry(z_DMnoSV, " S.V. #geq 0 ", "PE");
//    leg->AddEntry(z_DMsV2, " S.V. #geq 1 ", "PE");
//    leg->Draw("SAME");
//
//    c->SaveAs("/Users/josearias18/Desktop/DM_BH_Observables_SamePlots/Bjets_DM_z_SV0_SV2_noSV.pdf");
//
//    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    /// Canvas 1 (z_DMnoSV and z_DM_SV2)
//    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
//    TCanvas *c1 = new TCanvas("c1", "c1", 1100, 1000);
//    gStyle->SetOptStat(0);
//    c1->Divide(1, 1);
//    c1->cd(1);
//
//    z_DMnoSV->SetFillColor(kBlack);
//    z_DMnoSV->SetMarkerStyle(20);
//    z_DMnoSV->SetMarkerSize(0.78);
//    z_DMnoSV->SetMarkerColor(kBlack);
////    zh->Draw("Same  E1 E2 X0 ");
//    z_DMnoSV->Draw(" E1 E2 X0 ");
//
////        zH->SetFillColor(kRed);
//    z_DMsV2->SetFillColor(kBlue);
//    z_DMsV2->SetMarkerStyle(20);
//    z_DMsV2->SetMarkerSize(0.78);
//    z_DMsV2->SetMarkerColor(kBlue);
//    z_DMsV2->Draw("Same E1 E2 X0"); //"E1 X0 PLC PMC"
//
////        zh->SetFillColor(kBlack);
//    gPad->Modified();
//
//    TLegend *leg1 = new TLegend(0.18, 0.68, 0.45, 0.88);
//    gStyle->SetLegendTextSize(0.03);
//    leg1->SetHeader("Dimuon Stream: p_{T} > 20 GeV/c", "C");
//    leg1->SetBorderSize(0);
//    leg1->AddEntry(z_DMsV2, "S.V. #geq 1 ", "PE");
//    leg1->AddEntry(z_DMnoSV, " S.V. #geq 0  ", "PE");
//    leg1->Draw("SAME");
//
//    c1->SaveAs("/Users/josearias18/Desktop/DM_BH_Observables_SamePlots/Bjets_DM_z_SV2_noSV.pdf");
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Canvas 2 (z_BH and z_DMnoSV)
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TCanvas *c2 = new TCanvas("c2", "c2", 1100, 1000);
    gStyle->SetOptStat(0);
    c2->Divide(1, 1);
    c2->cd(1);

    z_BH->SetFillColor(kRed);
    z_BH->SetMarkerStyle(20);
    z_BH->SetMarkerSize(0.78);
    z_BH->SetMarkerColor(kRed);
//    zh->Draw("Same  E1 E2 X0 ");
    z_BH->Draw(" E1 E2 X0");

//        zH->SetFillColor(kRed);
    z_DMnoSV->SetFillColor(kBlack);
    z_DMnoSV->SetMarkerStyle(20);
    z_DMnoSV->SetMarkerSize(0.78);
    z_DMnoSV->SetMarkerColor(kBlack);
    z_DMnoSV->Draw("Same E1 E2 X0"); //"E1 X0 PLC PMC"

//        zh->SetFillColor(kBlack);
    gPad->Modified();

    TLegend *leg2 = new TLegend(0.18, 0.68, 0.45, 0.88);
    gStyle->SetLegendTextSize(0.03);
    leg2->SetHeader("Dimuon and Bhadron Streams: p_{T} > 20 GeV/c", "C");
    leg2->SetBorderSize(0);
    leg2->AddEntry(z_BH, "BHadron Stream ", "PE");
    leg2->AddEntry(z_DMnoSV, " Dimuon Stream: S.V. #geq 0  ", "PE");
    leg2->Draw("SAME");
    
    c2->SaveAs("/Users/josearias18/Desktop/DM_BH_Observables_SamePlots/Bjets_DM_BH_z_noSV.pdf");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Canvas 3 ( BH: jt(20-30), jt (30-50), jt (50-100)
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TCanvas *c3 = new TCanvas("c3", "c3", 1100, 1200);
    gStyle->SetOptStat(0);
    c3->Divide(1, 1);
    c3->cd(1);

//    jt2030_BH->SetFillColor(kRed);
    jt2030_BH->SetMarkerStyle(20);
    jt2030_BH->SetMarkerSize(0.84);
    jt2030_BH->SetMarkerColor(kRed+2);
    jt2030_BH->SetLineColor(kPink-4);
    jt2030_BH->SetLineWidth(1);
    jt2030_BH->Draw("EHIST");  //"E1 X0 PLC PMC"

//        zh->SetFillColor(kBlack);
//    jt3050_BH->SetFillColor(kBlue);
    jt3050_BH->SetMarkerStyle(20);
    jt3050_BH->SetMarkerSize(0.84);
    jt3050_BH->SetMarkerColor(kBlue+3);
    jt3050_BH->SetLineColor(kAzure+10);
    jt3050_BH->SetLineWidth(1);
    //    zh->Draw("Same  E1 E2 X0 ");
    jt3050_BH->Draw(" Same EHIST ");

//    jt50100_BH->SetFillColor(kGreen + 2);
    jt50100_BH->SetMarkerStyle(20);
    jt50100_BH->SetMarkerSize(0.84);
    jt50100_BH->SetMarkerColor(kGreen + 3);
    jt50100_BH->SetLineColor(kGreen);
    jt50100_BH->SetLineWidth(1);
    jt50100_BH->Draw("Same EHIST");

    gPad->SetLogy();
    gPad->Modified();

    TLegend *leg3 = new TLegend(0.65, 0.68, 0.75, 0.88);
    gStyle->SetLegendTextSize(0.03);
    leg3->SetHeader("Bhadron Stream: j_{T}", "C");
    leg3->SetBorderSize(0);
    leg3->AddEntry(jt2030_BH, " 20 GeV/c < p_{T} < 30 GeV/c", "PE");
    leg3->AddEntry(jt3050_BH, " 30 GeV/c < p_{T} < 50 GeV/c", "PE");
    leg3->AddEntry(jt50100_BH, " 50 GeV/c < p_{T} < 100 GeV/c", "PE");
    leg3->Draw("SAME");
    
    c3->SaveAs("/Users/josearias18/Desktop/DM_BH_Observables_SamePlots/Bjets_BH_jt.pdf");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Canvas 4 ( BH: r(20-30), r(30-50), r(50-100)
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    TCanvas *c4 = new TCanvas("c4", "c4", 1100, 1200);
    gStyle->SetOptStat(0);
    c4->Divide(1, 1);
    c4->cd(1);

//    r2030_BH->SetFillColor(kRed);
    r2030_BH->SetMarkerStyle(20);
    r2030_BH->SetMarkerSize(0.84);
    r2030_BH->SetMarkerColor(kRed+2);
    r2030_BH->SetLineColor(kPink-4);
    r2030_BH->SetLineWidth(1);
    r2030_BH->Draw("EHIST");  //"E1 X0 PLC PMC"

//        zh->SetFillColor(kBlack);
//    r3050_BH->SetFillColor(kBlue);
    r3050_BH->SetMarkerStyle(20);
    r3050_BH->SetMarkerSize(0.84);
    r3050_BH->SetMarkerColor(kBlue+3);
    r3050_BH->SetLineColor(kAzure+10);
    r3050_BH->SetLineWidth(1);
    //    zh->Draw("Same  E1 E2 X0 ");
    r3050_BH->Draw("Same  EHIST ");

//    r50100_BH->SetFillColor(kGreen + 2);
    r50100_BH->SetMarkerStyle(20);
    r50100_BH->SetMarkerSize(0.84);
    r50100_BH->SetMarkerColor(kGreen + 3);
    r50100_BH->SetLineColor(kGreen);
    r50100_BH->SetLineWidth(1);
    r50100_BH->Draw("Same EHIST");

    gPad->SetLogy();
    gPad->Modified();

    TLegend *leg4 = new TLegend(0.65, 0.68, 0.75, 0.88);
    gStyle->SetLegendTextSize(0.03);
    leg4->SetHeader("Bhadron Stream: r", "C");
    leg4->SetBorderSize(0);
    leg4->AddEntry(r2030_BH, " 20 GeV/c < p_{T} < 30 GeV/c", "PE");
    leg4->AddEntry(r3050_BH, " 30 GeV/c < p_{T} < 50 GeV/c", "PE");
    leg4->AddEntry(r50100_BH, " 50 GeV/c < p_{T} < 100 GeV/c", "PE");
    leg4->Draw("SAME");
    
    c4->SaveAs("/Users/josearias18/Desktop/DM_BH_Observables_SamePlots/Bjets_BH_r.pdf");
    
    ////// /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///Canvas 5 (DM : z (20-30) , z(30-50), z(50-100) SV>0
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TCanvas *c5 = new TCanvas("c5", "c5", 1100, 1200);
    gStyle->SetOptStat(0);
    c5->Divide(1, 1);
    c5->cd(1);
    c5->SetFillColor(0);

    //        zh->SetFillColor(kBlack);
    //    z3050_DMsV2->SetFillColor(0);
        jt3050_DMsV2->SetMarkerStyle(20);
        jt3050_DMsV2->SetMarkerSize(0.93);
        jt3050_DMsV2->SetMarkerColor(kBlue+2);
        jt3050_DMsV2->SetLineColor(kAzure+10);
        //    zh->Draw("Same  E1 E2 X0 ");
        jt3050_DMsV2->Draw(" EHIST"); // Draw(" Same BAR E1 E2 X0 ");
    
    jt50100_DMsV2->SetMarkerStyle(20);
    jt50100_DMsV2->SetMarkerSize(0.93);
    jt50100_DMsV2->SetMarkerColor(kGreen + 2);
    jt50100_DMsV2->SetLineColor(kGreen);
    jt50100_DMsV2->Draw(" Same EHIST");

//    z2030_DMsV2->SetFillColor(0);
    jt2030_DMsV2->SetMarkerStyle(20);
    jt2030_DMsV2->SetMarkerSize(0.93);
    jt2030_DMsV2->SetMarkerColor(kRed+1); //+3
    jt2030_DMsV2->SetLineColor(kPink+6); //-4
//    z2030_DMsV2->Draw("E1 BAR E2 X0");  //"E1 X0 PLC PMC"
    jt2030_DMsV2->Draw(" Same EHIST");


//    gPad->SetLogy();
    gPad->Modified();


    TLegend *leg5 = new TLegend(0.65, 0.68, 0.75, 0.88);
    gStyle->SetLegendTextSize(0.03);
    leg5->SetHeader("Dimuon Stream: j_{T} for S.V. #geq 2 ", "C"); //F(j_{T}) for S.V. #geq 1
    leg5->SetBorderSize(0);
    leg5->AddEntry(jt2030_DMsV2, " 20 GeV/c < p_{T} < 30 GeV/c", "PE");
    leg5->AddEntry(jt3050_DMsV2, " 30 GeV/c < p_{T} < 50 GeV/c", "PE");
    leg5->AddEntry(jt50100_DMsV2, " 50 GeV/c < p_{T} < 100 GeV/c", "PE");
    leg5->Draw("SAME");

    c5->SaveAs("/Users/josearias18/Desktop/DM_BH_Observables_SamePlots/Bjets_DM_jt_SVonly3.pdf");
    
   
    
}
