//
//  B_DM_SV_Observables.c
//
//
//  Created by Jose Arias on 6/6/23.
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
#include "LHCbStyle.C"

using namespace std;

void B_DM_SV_Observables() {
    TFile fread("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Bjets_DM_Variable_Tree_409283.root", "READ");
    TTree *Bjet_tree = (TTree *)fread.Get("Bjet");
    TFile f("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_DM_SV_0_Observables.root", "RECREATE");
    int NumEvts = Bjet_tree->GetEntries();

    cout << "Total number of events = " << NumEvts << endl;

    double jet_pt, jet_eta,  jet_rap;
    double jet_px, jet_py, jet_pz, jet_e;

    double mum_px, mum_py, mum_pz, mum_e;
    double mup_px, mup_py, mup_pz, mup_e;
    double K_px, K_py, K_pz, K_e;

    double B_px, B_py, B_pz, B_e;
    double B_m, B_pt, B_eta, B_phi;
    double bm_constrained;

    double dphi;
    int nSV, Jet_Dtr_ndtr;

    double bPhi, bM;
    double jPhi, jP;
    double bz, bJt, bR;

    Bjet_tree->SetBranchAddress("jet_pt", &jet_pt);
    Bjet_tree->SetBranchAddress("jet_px", &jet_px);
    Bjet_tree->SetBranchAddress("jet_py", &jet_py);
    Bjet_tree->SetBranchAddress("jet_pz", &jet_pz);
    Bjet_tree->SetBranchAddress("jet_e", &jet_e);
    Bjet_tree->SetBranchAddress("jet_eta", &jet_eta);
    Bjet_tree->SetBranchAddress("jet_rap", &jet_rap);
    Bjet_tree->SetBranchAddress("mum_px", &mum_px);
    Bjet_tree->SetBranchAddress("mum_py", &mum_py);
    Bjet_tree->SetBranchAddress("mum_pz", &mum_pz);
    Bjet_tree->SetBranchAddress("mum_e", &mum_e);
    Bjet_tree->SetBranchAddress("mup_px", &mup_px);
    Bjet_tree->SetBranchAddress("mup_py", &mup_py);
    Bjet_tree->SetBranchAddress("mup_pz", &mup_pz);
    Bjet_tree->SetBranchAddress("mup_e", &mup_e);
    Bjet_tree->SetBranchAddress("K_px", &K_px);
    Bjet_tree->SetBranchAddress("K_py", &K_py);
    Bjet_tree->SetBranchAddress("K_pz", &K_pz);
    Bjet_tree->SetBranchAddress("K_e", &K_e);
    Bjet_tree->SetBranchAddress("B_px", &B_px);
    Bjet_tree->SetBranchAddress("B_py", &B_py);
    Bjet_tree->SetBranchAddress("B_pz", &B_pz);
    Bjet_tree->SetBranchAddress("B_e", &B_e);
    Bjet_tree->SetBranchAddress("B_pt", &B_pt);
    Bjet_tree->SetBranchAddress("B_m", &B_m);
    Bjet_tree->SetBranchAddress("B_eta", &B_eta);
    Bjet_tree->SetBranchAddress("B_phi", &B_phi);
    Bjet_tree->SetBranchAddress("dphi", &dphi);
    Bjet_tree->SetBranchAddress("nSV", &nSV);
    Bjet_tree->SetBranchAddress("Jet_Dtr_ndtr", &Jet_Dtr_ndtr);
    Bjet_tree->SetBranchAddress("bm_constrained", &bm_constrained);
    
    int z0Bins, z1Bins, z2Bins, z3Bins;
    int jt0Bins, jt1Bins, jt2Bins, jt3Bins;
    int r0Bins, r1Bins, r2Bins, r3Bins;
    
    //SV = 0
    // Colz : 27 Good
    z0Bins = 27;  //  PERFECT: 45  [  55, 53 (Good) , BETTER: 52, 51  BEST: 50 ]
    z1Bins = 43;  //  BEST: 43 , GOOD: 45
    z2Bins = 25;  // BEST , BETTER: 25
    
    z3Bins = 10;  // BEST: 10 GOOD: 13, Really good: 9
    
    jt0Bins = 27;  // [BEST: 29! ] Good 30
    jt1Bins = 45;  //PERFECT : GOOD 45
    jt2Bins = 28;  // PERFECT: 28
    jt3Bins = 17;  //PERFECT: GOOD: 17

    r0Bins = 28;  //  and  GOOD 31 BEST: 28
    
    r1Bins = 28;  //
    r2Bins = 22;  /// GOOD: 22
    r3Bins = 20;  // Good: 20

    TH1F *zH = new TH1F("z", ";#it{z};  #frac{dN_{h}(z)}{dz}", z0Bins, 0.0, 1.0); //Good ; 69 (noSV) 70(SV0)
    TH1F *jtH = new TH1F("jt", ";j_{T} (GeV/c);  #frac{dN_{h}(j_{T})}{dj_{T}}", jt0Bins, 0., 10.);
    TH1F *rH = new TH1F("r", ";#it{r}; #frac{dN_{h}(r)}{dr}", r0Bins, 0., 0.5);
    TH2F *jtzH = new TH2F("Fzjt", ";#it{z}; j_{T} (GeV/c)", z0Bins, 0.0, 1.0, jt0Bins, 0., 10.);
    TH2F *zRH = new TH2F("z_R", ";#it{z}; #it{r}", z0Bins, 0.0, 1.0, r0Bins, 0., 0.5);
    
    TH2F *jtrH = new TH2F("jt_r", ";j_{T} (GeV/c); #it{r}", jt0Bins, 0.0, 10.0, r0Bins, 0., 0.5);

    //Pt Binned Histograms
    //20<pt<30 GeV/c
    TH1F *zH_20_30 = new TH1F("z_20_30", "; #it{z};   #frac{dN_{h}(z)}{dz}",z1Bins, 0.0, 1.0); //GOOD: 53 (noSV) 46(SV0) 18 (SV2)
    TH1F *jtH_20_30 = new TH1F("jt_20_30", ";j_{T} (GeV/c);   #frac{dN_{h}(j_{T})}{dj_{T}}", jt1Bins, 0., 10.);
    TH1F *rH_20_30 = new TH1F("r_20_30", ";#it{r};  #frac{dN_{h}(r)}{dr}", r1Bins, 0., 0.50);
    TH2F *jtzH_20_30 = new TH2F(";Fzjt_20_30;", ";#it{z}; j_{T} (GeV/c)", z1Bins, 0.0, 1.0, jt1Bins, 0., 10.);
    TH2F *zRH_20_30 = new TH2F(";z_R_20_30;", ";#it{z}; #it{r}", z1Bins, 0.0, 1.0, r1Bins, 0., 0.50);
    
    TH2F *jtrH_20_30 = new TH2F("jt_r_20_30", ";j_{T} (GeV/c); #it{r} ", jt1Bins, 0.0, 10.0, r1Bins, 0., 0.50);

    //30<pt<50 GeV/c
    TH1F *zH_30_50 = new TH1F("z_30_50", ";#it{z};   #frac{dN_{h}(z)}{dz}", z2Bins, 0.0, 1.0); //GOOD 30 (noSV/SV0) 15 (SV2)
    TH1F *jtH_30_50 = new TH1F("jt_30_50", ";j_{T} (GeV/c); #frac{dN_{h}(j_{T})}{dj_{T}}", jt2Bins, 0., 10.); //GOOD: 60 (noSV)
    TH1F *rH_30_50 = new TH1F("r_30_50", ";#it{r}; #frac{dN_{h}(r)}{dr}", r2Bins, 0., 0.50); // GOOD: 60 (noSV)
    TH2F *jtzH_30_50 = new TH2F(";Fzjt_30_50;", ";#it{z}; j_{T} (GeV/c)", z2Bins, 0.0, 1.0, jt2Bins, 0., 10.);
    TH2F *zRH_30_50 = new TH2F(";z_R_30_50;", ";#it{z}; #it{r}", z2Bins, 0.0, 1.0, r2Bins, 0., 0.50);
    
    TH2F *jtrH_30_50 = new TH2F("jt_r_30_50", ";j_{T} (GeV/c); #it{r} ", jt2Bins, 0.0, 10., r2Bins, 0., 0.50);

    //50<pt<100 GeV/c
    TH1F *zH_50_100 = new TH1F("z_50_100", ";#it{z};   #frac{dN_{h}(z)}{dz}", z3Bins, 0.0, 1.0); //GOOD; 13 (noSV) 10 (SV2)
    TH1F *jtH_50_100 = new TH1F("jt_50_100", ";j_{T} (GeV/c);  #frac{dN_{h}(j_{T})}{dj_{T}} ", jt3Bins, 0., 10.); //GOOD: 22 (noSV)
    TH1F *rH_50_100 = new TH1F("r_50_100", ";#it{r}; #frac{dN_{h}(r)}{dr}", r3Bins, 0., 0.50);
    TH2F *jtzH_50_100 = new TH2F(";Fzjt_50_100;", ";#it{z}; j_{T} (GeV/c)", z3Bins, 0.0, 1.0, jt3Bins, 0., 10.);
    TH2F *zRH_50_100 = new TH2F(";z_R_50_100;", ";#it{z}; #it{r}", z3Bins, 0.0, 1.0, r3Bins, 0., 0.50);
    
    TH2F *jtrH_50_100 = new TH2F("jt_r_50_100", ";j_{T} (GeV/c); #it{r} ", jt3Bins, 0.0, 10., r3Bins, 0., 0.50);

    double mass_high = 5.550;
    double mass_low = 5.150;

    for (int ev = 0; ev < NumEvts; ev++) {
        Bjet_tree->GetEntry(ev);

        if (ev % 100000 == 0) {
            cout << "Executing event " << ev << endl;
        }

//        if (dphi < 0.4) continue;

        if (jet_pt < 20.0) {
            continue;
        }
        
        if (nSV > 0) {continue;}

        if (bm_constrained / 1000. < mass_low || bm_constrained / 1000. > mass_high) {
            continue;
        }

        TLorentzVector b4vec(B_px, B_py, B_pz, B_e);
        TVector3 b3vec(B_px, B_py, B_pz);
        bPhi = b3vec.Phi();
        bM = (bm_constrained / 1000.);

        TLorentzVector j4vec(jet_px, jet_py, jet_pz, jet_e);
        TVector3 jet3vec(jet_px, jet_py, jet_pz);
        jPhi = jet3vec.Phi();
        jP =  jet3vec.Mag();

        // Observables: z, jt, dr

        bz = (b3vec.Dot(jet3vec) ) / (jet3vec.Mag2() );
        bJt = (jet3vec.Cross(b3vec).Mag()) / (jet3vec.Mag());
        bR = b4vec.DeltaR(j4vec);

        // Roofit Signal Regions
        double m_int = 5.27963;
        double sigma_int =  0.0138 ; // 0.0138 // 0.0079
        double m_2030 = 5.27959;
        double sigma_2030 = 0.0144 ; // 0.0144 // 0.0084
        double m_3050 = 5.2797;
        double sigma_3050 = 0.0155 ; //0.0155 // 0.0086
        double m_50100 = 5.2793;
        double sigma_50100 = 0.0175; // 0.011
        
        if (bM >= m_int - 2*sigma_int && bM <= m_int + 2*sigma_int) {
            zH->Fill(bz);
            jtH->Fill(bJt);
            rH->Fill(bR);
            jtzH->Fill(bz, bJt);
            zRH->Fill(bz, bR);
            
            jtrH->Fill(bJt, bR);
        }

        if (bM >= m_2030 - 2*sigma_2030 && bM <= m_2030 + 2*sigma_2030) { /// m_u 
            if (jet_pt  > 20.0 && jet_pt  < 30.0) {
                zH_20_30->Fill(bz);
                jtH_20_30->Fill(bJt);
                rH_20_30->Fill(bR);
                jtzH_20_30->Fill(bz, bJt);
                zRH_20_30->Fill(bz, bR);
                
                jtrH_20_30->Fill( bJt, bR);
                
            }
        }

        if (bM >= m_3050 - 2*sigma_3050 && bM <= m_3050 + 2*sigma_3050) {
            if (jet_pt  > 30.0 && jet_pt  < 50.0) {
                zH_30_50->Fill(bz);
                jtH_30_50->Fill(bJt);
                rH_30_50->Fill(bR);
                jtzH_30_50->Fill(bz, bJt);
                zRH_30_50->Fill(bz, bR);
                
                jtrH_30_50->Fill( bJt, bR);
            }
        }

        if (bM >= m_50100 - 2*sigma_50100 && bM <= m_50100 + 2*sigma_50100) {
            if (jet_pt  > 50.0 && jet_pt  < 100.0) {
                zH_50_100->Fill(bz);
                jtH_50_100->Fill(bJt);
                rH_50_100->Fill(bR);
                jtzH_50_100->Fill(bz, bJt);
                zRH_50_100->Fill(bz, bR);
                
                jtrH_50_100->Fill( bJt, bR);
            }
        }
    }
    
    Int_t lhcbFont        = 132;  // Old LHCb style: 62; // Line thickness
    Double_t lhcbWidth    = 2.00; // Old LHCb style: 3.00; // Text size
    Double_t lhcbTSize    = 0.06;
    Double_t lhcbTSize1    = 0.05;
    Double_t lhcbTSize2    = 0.04;
    
    /// The one that I use [integrated observables] ///
   TLatex *lhcbLatex = new TLatex();
   lhcbLatex->SetTextFont(lhcbFont);
   lhcbLatex->SetTextColor(1);
   lhcbLatex->SetTextSize(lhcbTSize);
   lhcbLatex->SetTextAlign(12);
    
    TLatex *lhcbLatex1 = new TLatex();
    lhcbLatex1->SetTextFont(lhcbFont);
    lhcbLatex1->SetTextColor(1);
    lhcbLatex1->SetTextSize(lhcbTSize1);
    lhcbLatex1->SetTextAlign(12);
    
    TLatex *lhcbLatex2 = new TLatex();
    lhcbLatex2->SetTextFont(lhcbFont);
    lhcbLatex2->SetTextColor(1);
    lhcbLatex2->SetTextSize(lhcbTSize2);
    lhcbLatex2->SetTextAlign(12);
    
    zH->GetYaxis()->SetTitleOffset(1.1);
    jtH->GetYaxis()->SetTitleOffset(1.1);
    rH->GetYaxis()->SetTitleOffset(1.1);
    zH_20_30->GetYaxis()->SetTitleOffset(1.1);
    zH_30_50->GetYaxis()->SetTitleOffset(1.1);
    zH_50_100->GetYaxis()->SetTitleOffset(1.1);
    jtH_20_30->GetYaxis()->SetTitleOffset(1.1);
    rH_20_30->GetYaxis()->SetTitleOffset(1.1);
    jtzH->GetYaxis()->SetTitleOffset(0.6);
    
    // Z
//    zH_20_30->SetMarkerStyle(kFullCircle);
    zH_20_30->SetMarkerSize(0.7);
//    zH_20_30->SetLineColor(kRed);
//    zH_20_30->SetMarkerColor(kRed+1);
    
//    zH_30_50->SetMarkerStyle(kFullSquare); //20
    zH_30_50->SetMarkerSize(0.7);
//    zH_30_50->SetLineColor(kGreen);
//    zH_30_50->SetMarkerColor(kGreen+1);
    
//    zH_50_100->SetMarkerStyle(kFullTriangleUp); //20
    zH_50_100->SetMarkerSize(0.7);
//    zH_50_100->SetLineColor(kBlue);
//    zH_50_100->SetMarkerColor(kBlue);
    zH_50_100->SetLineWidth(1);
    
    // JT
    jtH_20_30->SetMarkerStyle(kFullCircle);
    jtH_20_30->SetMarkerSize(0.84);
    jtH_20_30->SetLineColor(kRed);
    jtH_20_30->SetMarkerColor(kRed);
//    jtH_20_30->SetLineWidth(2);
    jtH_30_50->SetMarkerStyle(kFullSquare); //20
    jtH_30_50->SetMarkerSize(0.84);
    jtH_30_50->SetLineColor(kGreen);
    jtH_30_50->SetMarkerColor(kGreen);
//    jtH_30_50->SetLineWidth(2);
    jtH_50_100->SetMarkerStyle(kFullTriangleUp); //20
    jtH_50_100->SetMarkerSize(0.84);
    jtH_50_100->SetLineColor(kBlue);
    jtH_50_100->SetMarkerColor(kBlue);
//    jtH_50_100->SetLineWidth(2);
    
    // R
    rH_20_30->SetMarkerStyle(kFullCircle);
    rH_20_30->SetMarkerSize(0.84);
    rH_20_30->SetLineColor(kRed);
    rH_20_30->SetMarkerColor(kRed);
//    jtH_20_30->SetLineWidth(2);
    rH_30_50->SetMarkerStyle(kFullSquare); //20
    rH_30_50->SetMarkerSize(0.84);
    rH_30_50->SetLineColor(kGreen);
    rH_30_50->SetMarkerColor(kGreen);
//    jtH_30_50->SetLineWidth(2);
    rH_50_100->SetMarkerStyle(kFullTriangleUp); //20
    rH_50_100->SetMarkerSize(0.84);
    rH_50_100->SetLineColor(kBlue);
    rH_50_100->SetMarkerColor(kBlue);

    
    lhcbStyle();
    TCanvas* c=new TCanvas("c","c", 600, 400);
    TPad *zPad = new TPad("z", "", 0.04, 0.03, 0.98, 0.89);
    zPad->Draw();
    zPad->cd();
    
//    zH->Draw("E1 E2 X0"); //"E1 X0 PLC PMC"
//    lhcbName->Draw();
    zH->Draw("E1");
    lhcbLatex->DrawLatex( 0.1, 4200, "LHCb unofficial");
    lhcbLatex->DrawLatex(0.1, 3800, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    lhcbLatex->DrawLatex(0.1, 3400, "p_{T}^{ jet} > 20 GeV/c");
    
    TCanvas* c1=new TCanvas("c1","c1", 600, 400);
    TPad *jtPad = new TPad("jt", "", 0.04, 0.03, 0.98, 0.89);
    jtPad->Draw();
    jtPad->SetLogy();
    jtPad->cd();
    
    jtH->Draw("E1");
    lhcbLatex->DrawLatex( 5.5, 10000, "LHCb unofficial");
    lhcbLatex->DrawLatex(5.5, 3500, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    lhcbLatex->DrawLatex(5.5, 1200, "p_{T}^{ jet} > 20 GeV/c");
 
    TCanvas* c2=new TCanvas("c2","c2", 600, 400);
    TPad *rPad = new TPad("r", "", 0.04, 0.03, 0.98, 0.89);
    rPad->Draw();
    rPad->SetLogy();
    rPad->cd();
    
    rH->Draw("E1");
    lhcbLatex->DrawLatex( 0.25, 9000, "LHCb unofficial");
    lhcbLatex->DrawLatex(0.25, 5000, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    lhcbLatex->DrawLatex(0.25, 2700, "p_{T}^{ jet} > 20 GeV/c");
    
    TCanvas* c3=new TCanvas("c3","c3", 600, 400);
    TPad *z2030Pad = new TPad("z2030", "", 0.04, 0.03, 0.98, 0.89);
    z2030Pad->Draw();
    z2030Pad->cd();
    
    zH_20_30->Draw("E");
    lhcbLatex1->DrawLatex( 0.1, 3300, "LHCb unofficial");
    lhcbLatex1->DrawLatex(0.1, 3000, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    lhcbLatex1->DrawLatex(0.1, 2700, " 20 GeV/c < p_{T}^{ jet} < 30 GeV/c");
    
    TCanvas* c4=new TCanvas("c4","c4", 600, 400);
    TPad *z3050Pad = new TPad("z3020", "", 0.04, 0.03, 0.98, 0.89);
    z3050Pad->Draw();
    z3050Pad->cd();
    
    zH_30_50->Draw("E");
    lhcbLatex1->DrawLatex( 0.1, 1500, "LHCb unofficial");
    lhcbLatex1->DrawLatex(0.1, 1350, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    lhcbLatex1->DrawLatex(0.1, 1200, " 30 GeV/c < p_{T}^{ jet} < 50 GeV/c");
    
    TCanvas* c5=new TCanvas("c5","c5", 600, 400);
    TPad *z50100Pad = new TPad("z50100", "", 0.04, 0.03, 0.98, 0.89);
    z50100Pad->Draw();
    z50100Pad->cd();
    
    zH_50_100->Draw("HIST E");
    lhcbLatex1->DrawLatex( 0.1, 350, "LHCb unofficial");
    lhcbLatex1->DrawLatex(0.1, 300, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    lhcbLatex1->DrawLatex(0.1, 250, " 50 GeV/c < p_{T}^{ jet} < 100 GeV/c");
    
    TCanvas* c6=new TCanvas("c6","c6", 600, 400);
    TPad *jtAllPad = new TPad("jtAll", "", 0.04, 0.03, 0.98, 0.89);
    jtAllPad->Draw();
    jtAllPad->cd();
    jtAllPad->SetLogy();
    
    jtH_20_30->Draw("E  ");
    jtH_30_50->Draw(" E   Same");
    jtH_50_100->Draw(" E  Same");
    
    TLegend *leg3 = new TLegend(0.54, 0.60, 0.64, 0.80);
    gStyle->SetLegendTextSize(0.04);
    leg3->SetTextFont(lhcbFont);
    leg3->SetBorderSize(0);
    leg3->AddEntry(jtH_20_30, " 20 GeV/c < p_{T}^{ jet} < 30 GeV/c", "LPE");
    leg3->AddEntry(jtH_30_50, " 30 GeV/c < p_{T}^{ jet} < 50 GeV/c", "LPE");
    leg3->AddEntry(jtH_50_100, " 50 GeV/c < p_{T}^{ jet} < 100 GeV/c", "LPE");
    leg3->Draw("SAME");
    
    lhcbLatex2->DrawLatex(6.2, 9500, "LHCb unofficial");
    lhcbLatex2->DrawLatex(6.0, 4600, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    
    TCanvas* c7=new TCanvas("c7","c7", 600, 400);
    TPad *rAllPad = new TPad("rAll", "", 0.04, 0.03, 0.98, 0.89);
    rAllPad->Draw();
    rAllPad->cd();
    rAllPad->SetLogy();
    
    rH_20_30->Draw("E  ");
    rH_30_50->Draw(" E   Same");
    rH_50_100->Draw(" E  Same");
    
    TLegend *leg4 = new TLegend(0.55, 0.57, 0.65, 0.77);
    gStyle->SetLegendTextSize(0.04);
    leg4->SetTextFont(lhcbFont);
    leg4->SetBorderSize(0);
    leg4->AddEntry(rH_20_30, " 20 GeV/c < p_{T}^{ jet} < 30 GeV/c", "LPE");
    leg4->AddEntry(rH_30_50, " 30 GeV/c < p_{T}^{ jet} < 50 GeV/c", "LPE");
    leg4->AddEntry(rH_50_100, " 50 GeV/c < p_{T}^{ jet} < 100 GeV/c", "LPE");
    leg4->Draw("SAME");
    
    lhcbLatex2->DrawLatex(0.31, 9500, "LHCb unofficial");
    lhcbLatex2->DrawLatex(0.30, 6000, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
    
    TCanvas* c8=new TCanvas("c8","c8", 600, 400);
    TPad *jtzPad = new TPad("jtz", "", 0.02, 0.03, 0.92, 0.89);
    jtzPad->Draw();
    jtzPad->cd();
    jtzPad->SetLogz();
//    jtzPad->SetLogy();
    
    jtzH->Draw("Colz");
    
    TLegend *leg5 = new TLegend(0.64, 0.57, 0.74, 0.77);
    gStyle->SetLegendTextSize(0.04);
    leg5->SetTextFont(lhcbFont);
    leg5->SetBorderSize(0);
    leg5->Draw("SAME");
    
//    lhcbLatex2->DrawLatex(0.3, 9000, "LHCb unofficial");
//    lhcbLatex2->DrawLatex(0.3, 5600, "#sqrt{s} = 13 TeV, 5.4 fb^{-1}");
//    lhcbLatex2->DrawLatex(0.3, 3500, "Prompt D^{0}");
    
    c->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_zH_Final.pdf");
    c1->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_jtH_Final.pdf");
    c2->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_rH_Final.pdf");
    c3->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_zH2030_Final.pdf");
    c4->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_zH3050_Final.pdf");
    c5->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_zH50100_Final.pdf");
    c6->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_jtAll_Final.pdf");
    c7->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_rAll_Final.pdf");
    c8->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/2023_REU_Presentation/LHCb_B_jtz_Final.pdf");
    
    
    f.Write();
    f.Close();
}
