//
//  B_BH_Observables.c
//  
//
//  Created by Jose Arias on 6/8/23.
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

void B_BH_Observables() {
    
    TFile fread("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Bjets_BH_Variable_Tree_841656.root", "READ");
    TTree *Bjet_tree = (TTree *)fread.Get("Bjet");
    TFile f("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_BH_Observables.root", "RECREATE");
    int NumEvts = Bjet_tree->GetEntries();

    cout << "Total number of events = " << NumEvts << endl;

    double jet_pt, jet_eta,  jet_rap;
    double jet_px, jet_py, jet_pz, jet_e;

    double mum_px, mum_py, mum_pz, mum_e;
    double mup_px, mup_py, mup_pz, mup_e;
    double K_px, K_py, K_pz, K_e;

    double B_px, B_py, B_pz, B_e;
    double B_m, B_pt, B_eta, B_phi;

    double dphi;
    int nPV, Jet_Dtr_ndtr;

    double bPhi, bM;
    double jPhi, jP;
    double bz, bJt, bR;

    Bjet_tree->SetBranchAddress("jet_pt", &jet_pt);
    Bjet_tree->SetBranchAddress("jet_px", &jet_px);
    Bjet_tree->SetBranchAddress("jet_py", &jet_py);
    Bjet_tree->SetBranchAddress("jet_pz", &jet_pz);
    Bjet_tree->SetBranchAddress("jet_e", &jet_e);
    Bjet_tree->SetBranchAddress("jet_eta", &jet_eta);
   
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
    Bjet_tree->SetBranchAddress("nPV", &nPV);
    Bjet_tree->SetBranchAddress("Jet_Dtr_ndtr", &Jet_Dtr_ndtr);

 
    TH1F *zH = new TH1F("z", ";#it{z}; #frac{1}{N_{jet}} #frac{dN_{B}(z)}{dz}", 45, 0.0, 1.05); // 46 and 45 Bins BEST !!!
    TH1F *jtH = new TH1F("jt", ";j_{T} [GeV/c]; #frac{1}{N_{jet}} #frac{dN_{B}(j_{T})}{dj_{T}} [GeV^{-1}]", 80, 0., 10.);
    TH1F *rH = new TH1F("r", ";#it{r};", 80, 0., 0.505);
    TH2F *jtzH = new TH2F("Fzjt", ";#it{z}; j_{T} [GeV/c]", 70, 0.0, 1.05, 70, 0., 10.);
    TH2F *zRH = new TH2F("z_R", ";#it{z}; #it{r}", 70, 0.0, 1.05, 70, 0., 0.505);

    //Pt Binned Histograms
    //20<pt<30 GeV/c
    TH1F *zH_20_30 = new TH1F("z_20_30", "; #it{z}; #frac{1}{N_{jet}} #frac{dN_{B}(z)}{dz}", 38, 0.0, 1.05); //43 and 38 Bins: BEST !!!
    TH1F *jtH_20_30 = new TH1F("jt_20_30", ";j_{T} [GeV/c]; #frac{1}{N_{jet}} #frac{dN_{B}(j_{T})}{dj_{T}} [GeV^{-1}]", 75, 0., 10.);
    TH1F *rH_20_30 = new TH1F("r_20_30", ";#it{r}; #frac{1}{N_{jet}} #frac{dN_{B}(r)}{dr}", 75, 0., 0.505);
    TH2F *jtzH_20_30 = new TH2F(";Fzjt_20_30;", ";#it{z}; j_{T} [GeV/c]", 75, 0.0, 1.05, 75, 0., 10.);
    TH2F *zRH_20_30 = new TH2F(";z_R_20_30;", ";#it{z}; #it{r}", 75, 0.0, 1.05, 75, 0., 0.505);

    //30<pt<50 GeV/c
    TH1F *zH_30_50 = new TH1F("z_30_50", ";#it{z};#frac{1}{N_{jet}} #frac{dN_{B}(z)}{dz}", 25, 0.0, 1.05); //32 bins: Good, BEST: 25
    TH1F *jtH_30_50 = new TH1F("jt_30_50", ";j_{T} [GeV/c]; #frac{1}{N_{jet}} #frac{dN_{h}(j_{T})}{dj_{T}} [GeV^{-1}]", 60, 0., 10.);
    TH1F *rH_30_50 = new TH1F("r_30_50", ";#it{r}; #frac{1}{N_{jet}} #frac{dN_{B}(r)}{dr}", 60, 0., 0.505);
    TH2F *jtzH_30_50 = new TH2F(";Fzjt_30_50;", ";#it{z}; j_{T} [GeV/c]", 60, 0.0, 1.05, 60, 0., 10.);
    TH2F *zRH_30_50 = new TH2F(";z_R_30_50;", ";#it{z}; #it{r}", 60, 0.0, 1.05, 60, 0., 0.505);

    //50<pt<100 GeV/c
    TH1F *zH_50_100 = new TH1F("z_50_100", ";#it{z};#frac{1}{N_{jet}} #frac{dN_{B}(z)}{dz}", 13, 0.0, 1.05); // 15 Bins: Good, BEST: 13
    TH1F *jtH_50_100 = new TH1F("jt_50_100", ";j_{T} [GeV/c]; #frac{1}{N_{jet}} #frac{dN_{B}(j_{T})}{dj_{T}} [GeV^{-1}]", 26, 0., 10.);
    TH1F *rH_50_100 = new TH1F("r_50_100", ";#it{r}; #frac{1}{N_{jet}} #frac{dN_{B}(r)}{dr}", 30, 0., 0.505);
    TH2F *jtzH_50_100 = new TH2F(";Fzjt_50_100;", ";#it{z}; j_{T} [GeV/c]", 20, 0.0, 1.05, 26, 0., 10.);
    TH2F *zRH_50_100 = new TH2F(";z_R_50_100;", ";#it{z}; #it{r}", 20, 0.0, 1.05, 30, 0., 0.505);
    
    TH1F *zh = new TH1F("zh", ";z_{h} = #frac{p_{T, B}}{p_{T,jet}};#frac{1}{N_{jet}} #frac{dN_{B}(z_{h})}{dz_{h,B}}", 45, 0.0, 1.05);
    TH1F *zpt = new TH1F("zpt", ";z_{#perp} = #frac{ p_{T}^{h} #bullet p_{T}^{jet} }{|p_{T}^{jet}|^{2} };#frac{1}{N_{jet}} #frac{dN_{B}(z_{#perp})}{dz_{#perp}}", 45, 0.0, 1.05);
    TH1F *zE = new TH1F("zE", ";z_{E} = #frac{ E^{h} }{ E^{jet} }; #frac{1}{N_{jet}} #frac{dN_{B}(z_{E})}{dz_{E}}", 45, 0.0, 1.05);

    double mass_high = 5.7;
    double mass_low = 5.0;

    for (int ev = 0; ev < NumEvts; ev++) {
        Bjet_tree->GetEntry(ev);

        if (ev % 100000 == 0) {
            cout << "Executing event " << ev << endl;
        }

//        if (dphi < 0.4) continue;

        if (jet_pt < 20.0) {
            continue;
        }
        
        if (nPV >1) {continue;}

        if (B_m < mass_low || B_m > mass_high) {
            continue;
        }

        TLorentzVector b4vec(B_px, B_py, B_pz, B_e);
        TVector3 b3vec(B_px, B_py, B_pz);
        TVector2 b2vec(B_px, B_py);  // pt=(px, py)
        
        bPhi = b3vec.Phi();
        bM = (B_m);

        TLorentzVector j4vec(jet_px, jet_py, jet_pz, jet_e);
        TVector3 jet3vec(jet_px, jet_py, jet_pz);
        TVector2 jet2vec(jet_px, jet_py); // pt=(px, py)
        
        jPhi = jet3vec.Phi();
        jP =  jet3vec.Mag();

        // Observables: z, jt, dr

        bz = (b3vec.Dot(jet3vec) ) / (jet3vec.Mag2() );
        bJt = (jet3vec.Cross(b3vec).Mag()) / (jet3vec.Mag());
        bR = b4vec.DeltaR(j4vec);
        
        // Variations of F(z)
        
        double z_h = b4vec.Pt()/j4vec.Pt();
        double z_perp = (b2vec * jet2vec) / ( jet2vec.Mod2() );
        double z_E = ( b4vec.E() )/( j4vec.E() );

        // Roofit Signal Regions
        double m_int = 5.27892;
        double sigma_int = 0.0255; // 0.0176 // 0.0255
        double m_2030 = 5.2790;
        double sigma_2030 = 0.0221; //0.015 // 0.0221
        double m_3050 = 5.2789;
        double sigma_3050 = 0.028; //0.015 //0.028
        double m_50100 = 5.2792;
        double sigma_50100 = 0.026; // 0.01 //0.026
        
        if (bM >= m_int - 2*sigma_int && bM <= m_int + 2*sigma_int) {
            
            zH->Fill(bz);
        
            jtH->Fill(bJt);
            rH->Fill(bR);
            
            jtzH->Fill(bz, bJt);
            zRH->Fill(bz, bR);
            
            zh -> Fill(z_h);
            zh->GetXaxis()->SetTitleOffset(1.5);
            
            zpt -> Fill(z_perp);
            zpt->GetXaxis()->SetTitleOffset(1.5);
            
            zE-> Fill( z_E);
            zE-> GetXaxis()->SetTitleOffset(1.5);
    
        }

        if (bM >= m_2030 - 2.5*sigma_2030 && bM <= m_2030 + 2.5*sigma_2030) {
            if (jet_pt  > 20.0 && jet_pt  < 30.0) {
                zH_20_30->Fill(bz);
                jtH_20_30->Fill(bJt);
                rH_20_30->Fill(bR);
                jtzH_20_30->Fill(bz, bJt);
                zRH_20_30->Fill(bz, bR);
                
   
            }
        }

        if (bM >= m_3050 - 2*sigma_3050 && bM <= m_3050 + 2*sigma_3050) {
            if (jet_pt  > 30.0 && jet_pt  < 50.0) {
                zH_30_50->Fill(bz);
                jtH_30_50->Fill(bJt);
                rH_30_50->Fill(bR);
                jtzH_30_50->Fill(bz, bJt);
                zRH_30_50->Fill(bz, bR);
            }
        }

        if (bM >= m_50100 - 2.3*sigma_50100 && bM <= m_50100 + 2.3*sigma_50100) {
            if (jet_pt  > 50.0 && jet_pt  < 100.0) {
                zH_50_100->Fill(bz);
                jtH_50_100->Fill(bJt);
                rH_50_100->Fill(bR);
                jtzH_50_100->Fill(bz, bJt);
                zRH_50_100->Fill(bz, bR);
            }
        }
    }
    
    
    TCanvas* c=new TCanvas("c","c", 1100, 1000);
    gStyle->SetOptStat(0);
    c->Divide(1, 1);
    c->cd(1);
    
    TH1F *z_zh= (TH1F *)zH->Clone("z_zh");
    zH->SetLineColor(2);

    zH->SetFillColor(kRed);
    zH->SetMarkerStyle(20);
    zH->SetMarkerSize(0.76);
    zH->SetMarkerColor(kRed);
    zH->Draw("E1 E2 X0"); //"E1 X0 PLC PMC"
    
    zh->SetFillColor(kBlack);
    zh->SetMarkerStyle(20);
    zh->SetMarkerSize(0.76);
    zh->SetMarkerColor(kBlack);
    zh->Draw("Same  E1 E2 X0 ");
    
    zpt->SetFillColor(kBlue);
    zpt->SetMarkerStyle(20);
    zpt->SetMarkerSize(0.76);
    zpt->SetMarkerColor(kBlue);
    zpt->Draw("Same  E1 E2 X0 ");
    
    zE->SetFillColor(kGreen);
    zE->SetMarkerStyle(20);
    zE->SetMarkerSize(0.76);
    zE->SetMarkerColor(kGreen);
    zE->Draw("Same  E1 E2 X0 ");
//    zh->Draw(" E1 E2 X0 ");

    gPad->Modified();
    
    TLegend *leg = new TLegend(0.18, 0.54, 0.45, 0.86);
    gStyle->SetLegendTextSize(0.03);
    leg->SetHeader("LHCb Bhadron Stream: p_{T} > 20 GeV/c","C");
    leg->SetBorderSize(0);
    leg->AddEntry((TObject*)0, "#sqrt{s} = 13 TeV", "");
    leg->AddEntry((TObject*)0, "#it{pp} #rightarrow (B^{#pm}, jet)X", "");
    leg->AddEntry( zh, "z_{h} = p_{T}^{h} / p_{T}^{j}", "PE");
    leg->AddEntry(zH, " z = ( p_{h} #bullet p_{jet} ) / |p_{jet}|^{2} ", "PE");
    leg->AddEntry(zpt, " z_{T}  = ( p_{T}^{h} #bullet p_{T}^{jet} ) / |p_{T}^{jet}|^{2} ", "PE");
    leg->AddEntry(zE, " z_{E} = E^{h} / E^{jet}", "PE");
    leg->Draw("SAME");

    c->SaveAs("/Users/josearias18/Desktop/Bjets_BH_z_zh_zperp_zE.pdf");
    
    f.Write();
    f.Close();
}

