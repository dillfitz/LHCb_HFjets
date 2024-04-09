#include <cmath>
#include <iostream>
#include <stdio.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TStyle.h>
#include <vector>
#include "Header.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"

using namespace std;

void BH_DM_Comparison(){
    
    TFile freadDM("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/DM_Stream_Var_Tree_1979178.root", "READ");
    TFile freadBH("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/BH_Stream_Var_Tree_841656.root", "READ");
    TTree *DiMuon_Tree = (TTree *)freadDM.Get("DM_Stream");
    int DMNumEvts = DiMuon_Tree->GetEntries();
    TTree *B_hadron_Tree = (TTree *)freadBH.Get("BH_Stream");
    int BHNumEvts = B_hadron_Tree->GetEntries();
//
//    int NumEvts = Djet_tree->GetEntries();
////  cout<<Djet_tree->GetEntries()<<endl;
//    cout << NumEvts << endl;

    TFile *outfile = new TFile("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/BH_DM_Comparison.root", "RECREATE");
    
    double DM_jet_pt, DM_jet_eta, DM_jet_phi;
    double DM_jet_px, DM_jet_py, DM_jet_pz, DM_jet_e;
    double DM_K_pt, DM_mup_pt, DM_mum_pt;
    double DM_K_px, DM_K_py, DM_K_pz, DM_K_e;
    double DM_mup_px, DM_mup_py, DM_mup_pz, DM_mup_e;
    double DM_mum_px, DM_mum_py, DM_mum_pz, DM_mum_e;
    double DM_JPsi_pt, DM_JPsi_m;
    double DM_JPsi_px, DM_JPsi_py, DM_JPsi_pz, DM_JPsi_e;
    double DM_HFmeson_phi, DM_HFmeson_eta, DM_HFmeson_pt;
    double jet_pt, jet_eta, jet_phi;
    double jet_px, jet_py, jet_pz, jet_e;
    double K_pt, mup_pt, mum_pt;
    double K_px, K_py, K_pz, K_e;
    double mup_px, mup_py, mup_pz, mup_e;
    double mum_px, mum_py, mum_pz, mum_e;
    double JPsi_pt, JPsi_m;
    double JPsi_px, JPsi_py, JPsi_pz, JPsi_e;
    double HFmeson_phi, HFmeson_eta, HFmeson_pt;
    
    DiMuon_Tree->SetBranchAddress("DM_jet_pt", &DM_jet_pt);
    DiMuon_Tree->SetBranchAddress("DM_jet_eta", &DM_jet_eta);
    DiMuon_Tree->SetBranchAddress("DM_jet_phi", &DM_jet_phi);
    DiMuon_Tree->SetBranchAddress("DM_jet_px", &DM_jet_px);
    DiMuon_Tree->SetBranchAddress("DM_jet_py", &DM_jet_py);
    DiMuon_Tree->SetBranchAddress("DM_jet_pz", &DM_jet_pz);
    DiMuon_Tree->SetBranchAddress("DM_jet_e", &DM_jet_e);
    DiMuon_Tree->SetBranchAddress("DM_mup_pt", &DM_mup_pt);
    DiMuon_Tree->SetBranchAddress("DM_mup_px", &DM_mup_px);
    DiMuon_Tree->SetBranchAddress("DM_mup_py", &DM_mup_py);
    DiMuon_Tree->SetBranchAddress("DM_mup_pz", &DM_mup_pz);
    DiMuon_Tree->SetBranchAddress("DM_mup_e", &DM_mup_e);
    DiMuon_Tree->SetBranchAddress("DM_mum_pt", &DM_mum_pt);
    DiMuon_Tree->SetBranchAddress("DM_mum_px", &DM_mum_px);
    DiMuon_Tree->SetBranchAddress("DM_mum_py", &DM_mum_py);
    DiMuon_Tree->SetBranchAddress("DM_mum_pz", &DM_mum_pz);
    DiMuon_Tree->SetBranchAddress("DM_mum_e", &DM_mum_e);
    DiMuon_Tree->SetBranchAddress("DM_K_pt", &DM_K_pt);
    DiMuon_Tree->SetBranchAddress("DM_K_px", &DM_K_px);
    DiMuon_Tree->SetBranchAddress("DM_K_py", &DM_K_py);
    DiMuon_Tree->SetBranchAddress("DM_K_pz", &DM_K_pz);
    DiMuon_Tree->SetBranchAddress("DM_K_e", &DM_K_e);
    DiMuon_Tree->SetBranchAddress("DM_JPsi_pt", &DM_JPsi_pt);
    DiMuon_Tree->SetBranchAddress("DM_JPsi_m", &DM_JPsi_m);
    DiMuon_Tree->SetBranchAddress("DM_JPsi_px", &DM_JPsi_px);
    DiMuon_Tree->SetBranchAddress("DM_JPsi_py", &DM_JPsi_py);
    DiMuon_Tree->SetBranchAddress("DM_JPsi_pz", &DM_JPsi_pz);
    DiMuon_Tree->SetBranchAddress("DM_JPsi_e", &DM_JPsi_e);
    DiMuon_Tree->SetBranchAddress("DM_HFmeson_phi", &DM_HFmeson_phi);
    DiMuon_Tree->SetBranchAddress("DM_HFmeson_eta", &DM_HFmeson_eta);
    DiMuon_Tree->SetBranchAddress("DM_HFmeson_pt", &DM_HFmeson_pt);
    B_hadron_Tree->SetBranchAddress("jet_pt", &jet_pt);
    B_hadron_Tree->SetBranchAddress("jet_eta", &jet_eta);
    B_hadron_Tree->SetBranchAddress("jet_phi", &jet_phi);
    B_hadron_Tree->SetBranchAddress("jet_px", &jet_px);
    B_hadron_Tree->SetBranchAddress("jet_py", &jet_py);
    B_hadron_Tree->SetBranchAddress("jet_pz", &jet_pz);
    B_hadron_Tree->SetBranchAddress("jet_e", &jet_e);
    B_hadron_Tree->SetBranchAddress("mup_pt", &mup_pt);
    B_hadron_Tree->SetBranchAddress("mup_px", &mup_px);
    B_hadron_Tree->SetBranchAddress("mup_py", &mup_py);
    B_hadron_Tree->SetBranchAddress("mup_pz", &mup_pz);
    B_hadron_Tree->SetBranchAddress("mup_e", &mup_e);
    B_hadron_Tree->SetBranchAddress("mum_pt", &mum_pt);
    B_hadron_Tree->SetBranchAddress("mum_px", &mum_px);
    B_hadron_Tree->SetBranchAddress("mum_py", &mum_py);
    B_hadron_Tree->SetBranchAddress("mum_pz", &mum_pz);
    B_hadron_Tree->SetBranchAddress("mum_e", &mum_e);
    B_hadron_Tree->SetBranchAddress("K_pt", &K_pt);
    B_hadron_Tree->SetBranchAddress("K_px", &K_px);
    B_hadron_Tree->SetBranchAddress("K_py", &K_py);
    B_hadron_Tree->SetBranchAddress("K_pz", &K_pz);
    B_hadron_Tree->SetBranchAddress("K_e", &K_e);
    B_hadron_Tree->SetBranchAddress("JPsi_pt", &JPsi_pt);
    B_hadron_Tree->SetBranchAddress("JPsi_m", &JPsi_m);
    B_hadron_Tree->SetBranchAddress("JPsi_px", &JPsi_px);
    B_hadron_Tree->SetBranchAddress("JPsi_py", &JPsi_py);
    B_hadron_Tree->SetBranchAddress("JPsi_pz", &JPsi_pz);
    B_hadron_Tree->SetBranchAddress("JPsi_e", &JPsi_e);
    B_hadron_Tree->SetBranchAddress("HFmeson_phi", &HFmeson_phi);
    B_hadron_Tree->SetBranchAddress("HFmeson_eta", &HFmeson_eta);
    B_hadron_Tree->SetBranchAddress("HFmeson_pt", &HFmeson_pt);
    
    TH1F *DM_JPsiM = new TH1F("DM_JPsiM", ";m_{#mu#mu} (GeV/c^{2});", 200, 3.0, 3.2);
    TH1F *BH_JPsiM = new TH1F("BH_JPsiM", ";m_{#mu#mu} (GeV/c^{2});", 200, 3.0, 3.2);
    TH1F *DM_JPsip = new TH1F("DM_JPsip", ";|p| (GeV/c);", 200, 0.0, 3000.);
    TH1F *BH_JPsip = new TH1F("BH_JPsip", ";|p| (GeV/c);", 200, 0.0, 3000.);
    TH1F *DM_JPsipt = new TH1F("DM_JPsipt", ";p_{T} (GeV/c);", 200, 0.0, 200.);
    TH1F *BH_JPsipt = new TH1F("BH_JPsipt", ";p_{T} (GeV/c);", 200, 0.0, 200.);
    
    //////// Jet ///// / / /
    TH1F *DM_Jetpt = new TH1F("DM_Jetpt", ";p_{T} (GeV/c);", 200, 0.0, 200.);
    TH1F *BH_Jetpt = new TH1F("BH_Jetpt", ";p_{T} (GeV/c);", 200, 0.0, 200.);
    TH1F *DM_Jetp = new TH1F("DM_Jetp", ";|p| (GeV/c);", 200, 0.0, 3000.);
    TH1F *BH_Jetp = new TH1F("BH_Jetp", ";|p| (GeV/c);", 200, 0.0, 3000.);
    TH1F *DM_Jetpz = new TH1F("DM_Jetpz", ";p_{z} (GeV/c);", 200, 0.0, 1000.);
    TH1F *BH_Jetpz = new TH1F("BH_Jetpz", ";p_{z} (GeV/c);", 200, 0.0, 1000.);
    TH1F *DM_Jeteta = new TH1F("DM_Jeteta", ";#eta;", 200, 2.4, 5.0);
    TH1F *BH_Jeteta = new TH1F("BH_Jeteta", ";#eta;", 200, 2.4, 5.0);
    TH1F *DM_Jetphi = new TH1F("DM_Jetphi", ";#phi;", 200, -3.7, 3.7);
    TH1F *BH_Jetphi = new TH1F("BH_Jetphi", ";#phi;", 200, -3.7, 3.7);
    
    //////// B meson ///// / / /
    TH1F *DM_Bpt = new TH1F("DM_Bpt", ";p_{T} (GeV/c);", 200, 0.0, 200.);
    TH1F *BH_Bpt = new TH1F("BH_Bpt", ";p_{T} (GeV/c);", 200, 0.0, 200.);
    TH1F *DM_Bp = new TH1F("DM_Bp", ";|p| (GeV/c);", 200, 0.0, 3000.);
    TH1F *BH_Bp = new TH1F("BH_Bp", ";|p| (GeV/c);", 200, 0.0, 3000.);
    TH1F *DM_Bpz = new TH1F("DM_Bpz", ";p_{z} (GeV/c);", 200, 0.0, 1000.);
    TH1F *BH_Bpz = new TH1F("BH_Bpz", ";p_{z} (GeV/c);", 200, 0.0, 1000.);
    TH1F *DM_Beta = new TH1F("DM_Beta", ";#eta;", 200, 2.4, 5.0);
    TH1F *BH_Beta = new TH1F("BH_Beta", ";#eta;", 200, 2.4, 5.0);
    TH1F *DM_Bphi = new TH1F("DM_Bphi", ";#phi;", 200, -3.7, 3.7);
    TH1F *BH_Bphi = new TH1F("BH_Bphi", ";#phi;", 200, -3.7, 3.7);
    
    TH2F *JPsi2_pt = new TH2F("JPsi2_pt", ";BH p_{T, J/Psi}; DM p_{T, J/Psi}" , 175, 0.0, 250., 175, 0., 250.);
    
    for (int ev = 0; ev < DMNumEvts; ev++) {
        DiMuon_Tree->GetEntry(ev);

        if (ev % 100000 == 0) {
            cout << "Executing DM event " << ev << endl;
        }

        TLorentzVector DM_jet4P, DM_mum4P, DM_mup4P, DM_JPsi, DM_Kmeson4P, DM_HFmeson; //DiMuon
        

        //Dimuon
        DM_jet4P.SetPxPyPzE(DM_jet_px, DM_jet_py, DM_jet_pz, DM_jet_e);
        DM_mum4P.SetPxPyPzE(DM_mum_px, DM_mum_py, DM_mum_pz, DM_mum_e);
        DM_mup4P.SetPxPyPzE(DM_mup_px, DM_mup_py, DM_mup_pz, DM_mup_e);
        DM_Kmeson4P.SetPxPyPzE(DM_K_px, DM_K_py, DM_K_pz, DM_K_e);
        DM_HFmeson = DM_mum4P + DM_mup4P + DM_Kmeson4P;
        DM_JPsi = DM_mum4P + DM_mup4P;
        
        DM_jet_pt = DM_jet4P.Pt();
        DM_jet_eta = DM_jet4P.Eta();
        DM_jet_pz = DM_jet4P.Pz();
        DM_jet_e = DM_jet4P.E();
        double DM_jet_p = DM_jet4P.P();
        DM_jet_phi = DM_jet4P.Phi();

        DM_JPsi_pt = DM_JPsi.Pt();
        DM_JPsi_m = DM_JPsi.M();
        DM_JPsi_pz = DM_JPsi.Pz();
        double DM_JPsi_p = DM_JPsi.P();
        DM_JPsi_e = DM_JPsi.E();

        DM_HFmeson_phi = DM_HFmeson.Phi();
        DM_HFmeson_eta = DM_HFmeson.Eta();
        DM_HFmeson_pt = DM_HFmeson.Pt();
        double DM_HFmeson_p =  DM_HFmeson.P();

        DM_JPsiM->Fill(DM_JPsi_m);
        DM_JPsip->Fill(DM_JPsi_p);
        DM_JPsipt->Fill(DM_JPsi_pt);
        DM_Jetpt->Fill(DM_jet_pt);
        DM_Jetp->Fill(DM_jet_p);
        DM_Jetpz->Fill(DM_jet_pz);
        DM_Bp->Fill(DM_HFmeson_p);
        DM_Bpz->Fill(DM_HFmeson.Pz());
        DM_Bpt->Fill(DM_HFmeson_pt);
        JPsi2_pt->Fill();
    }

    for (int j = 0; j < BHNumEvts; j++) {
        B_hadron_Tree->GetEntry(j);
        
        if (j % 100000 == 0) {
            cout << "Executing BH event " << j << endl;
        }
        TLorentzVector jet4P, mum4P, mup4P, JPsi, Kmeson4P, HFmeson; //BHadron
        //Bhadron
        jet4P.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
        mum4P.SetPxPyPzE(mum_px, mum_py, mum_pz, mum_e);
        mup4P.SetPxPyPzE(mup_px, mup_py, mup_pz, mup_e);
        Kmeson4P.SetPxPyPzE(K_px, K_py, K_pz, K_e);
        HFmeson = mum4P + mup4P + Kmeson4P;
        JPsi = mum4P + mup4P;
        
        //Bahdron Variables
        jet_pt = jet4P.Pt();
        jet_eta = jet4P.Eta();
        jet_pz = jet4P.Pz();
        double jet_p = jet4P.P();
        jet_e = jet4P.E();
        jet_phi = jet4P.Phi();
        
        JPsi_pt = JPsi.Pt();
        JPsi_m = JPsi.M();
        JPsi_pz = JPsi.Pz();
        double JPsi_p = JPsi.P();
        JPsi_e = JPsi.E();
        
        HFmeson_phi = HFmeson.Phi();
        HFmeson_eta = HFmeson.Eta();
        HFmeson_pt = HFmeson.Pt();
        double HFmeson_p =  HFmeson.P();
        
        BH_JPsiM->Fill(JPsi_m);
        BH_JPsip->Fill(JPsi_p);
        BH_JPsipt->Fill(JPsi_pt);
        BH_Jetpt->Fill(jet_pt);
        BH_Jetp->Fill(jet_p);
        BH_Jetpz->Fill(jet_pz);
        BH_Bpt->Fill(HFmeson_pt);
        BH_Bp->Fill(HFmeson_p);
        BH_Bpz->Fill(HFmeson.Pz());
    }
    
    TCanvas *c1 = new TCanvas("c1", "c", 700, 900);
    c1->Divide(1, 1);
    c1->cd(1);
    
    BH_Bpt->Sumw2();
    TH1F *BH_Bptnorm = (TH1F *)BH_Bpt->Clone("BH_Bptnorm");
    BH_Bptnorm->SetTitle("Normalized B meson p_{T}");
    BH_Bptnorm->Scale((100./7.5)/(BH_Bpt->Integral()), "width");
    BH_Bptnorm->SetLineColor(2);
    BH_Bptnorm->SetStats(0);
    BH_Bptnorm->Draw("Hist");
    gPad->SetLogy();
    gPad->Update();

    DM_Bpt->Sumw2();
    TH1F *DM_Bptnorm = (TH1F *)DM_Bpt->Clone("DM_Bptnorm");
    DM_Bptnorm->Scale((200./14)/(DM_Bpt->Integral()), "width");
    DM_Bptnorm->SetLineColor(4);
    DM_Bptnorm->SetStats(0);
    DM_Bptnorm->Draw("SameHist");
    gPad->SetLogy();
    gPad->Update();
    
    TLegend *leg1 = new TLegend(0.5, 0.55, 0.75, 0.8);
    leg1->SetBorderSize(0);
    leg1->AddEntry(BH_Bptnorm, "BHadron Stream", "PE");
    leg1->AddEntry(DM_Bptnorm, "DiMuon Stream", "L");
    leg1->Draw("SAME");
     
    //
    TCanvas *c2 = new TCanvas("c2", "c", 700, 900);
    c2->Divide(1, 1);
    c2->cd(1);
    
    BH_Bp->Sumw2();
    TH1F *BH_Bpnorm = (TH1F *)BH_Bp->Clone("BH_Bpnorm");
    BH_Bpnorm->SetTitle("Normalized B meson |p|");
    BH_Bpnorm->Scale((200./1.18)/(BH_Bp->Integral()), "width");
    BH_Bpnorm->SetLineColor(2);
    BH_Bpnorm->SetStats(0);
    BH_Bpnorm->Draw("Hist");
    gPad->SetLogy();
    gPad->Update();

    DM_Bp->Sumw2();
    TH1F *DM_Bpnorm = (TH1F *)DM_Bp->Clone("DM_Bpnorm");
    DM_Bpnorm->Scale((200./1.225)/(DM_Bp->Integral()), "width");
    DM_Bpnorm->SetLineColor(4);
    DM_Bpnorm->SetStats(0);
    DM_Bpnorm->Draw("SameHist");
    gPad->SetLogy();
    gPad->Update();
    
    TLegend *leg2 = new TLegend(0.5, 0.55, 0.75, 0.8);
    leg2->SetBorderSize(0);
    leg2->AddEntry(BH_Bpnorm, "BHadron Stream", "PE");
    leg2->AddEntry(DM_Bpnorm, "DiMuon Stream", "L");
    leg2->Draw("SAME");
    
    TCanvas *c3 = new TCanvas("c3", "c", 700, 900);
    c3->Divide(1, 1);
    c3->cd(1);
    
    BH_Jetpt->Sumw2();
    TH1F *BH_Jetptnorm = (TH1F *)BH_Jetpt->Clone("BH_Jetptnorm");
    BH_Jetptnorm->SetTitle("Normalized Jet p_{T}");
    BH_Jetptnorm->Scale((100./16)/(BH_Jetpt->Integral()), "width");
    BH_Jetptnorm->SetLineColor(2);
    BH_Jetptnorm->SetStats(0);
    BH_Jetptnorm->Draw("Hist");
    gPad->SetLogy();
    gPad->Update();

    DM_Jetpt->Sumw2();
    TH1F *DM_Jetptnorm = (TH1F *)DM_Jetpt->Clone("DM_Jetptnorm");
    DM_Jetptnorm->Scale((100./17)/(DM_Jetpt->Integral()), "width");
    DM_Jetptnorm->SetLineColor(4);
    DM_Jetptnorm->SetStats(0);
    DM_Jetptnorm->Draw("SameHist");
    gPad->SetLogy();
    gPad->Update();
    
    TLegend *leg3 = new TLegend(0.5, 0.55, 0.75, 0.8);
    leg3->SetBorderSize(0);
    leg3->AddEntry(BH_Jetptnorm, "BHadron Stream", "PE");
    leg3->AddEntry(DM_Jetptnorm, "DiMuon Stream", "L");
    leg3->Draw("SAME");
    ////////////
    TCanvas *c4 = new TCanvas("c4", "c", 700, 900);
    c4->Divide(1, 1);
    c4->cd(1);
    
    BH_Jetp->Sumw2();
    TH1F *BH_Jetpnorm = (TH1F *)BH_Jetp->Clone("BH_Jetpnorm");
    BH_Jetpnorm->SetTitle("Normalized Jet |p|");
    BH_Jetpnorm->Scale((220.)/(BH_Jetp->Integral()), "width");
    BH_Jetpnorm->SetLineColor(2);
    BH_Jetpnorm->SetStats(0);
    BH_Jetpnorm->Draw("Hist");
    gPad->SetLogy();
    gPad->Update();

    DM_Jetp->Sumw2();
    TH1F *DM_Jetpnorm = (TH1F *)DM_Jetp->Clone("DM_Jetpnorm");
    DM_Jetpnorm->Scale((208.)/(DM_Jetp->Integral()), "width");
    DM_Jetpnorm->SetLineColor(4);
    DM_Jetpnorm->SetStats(0);
    DM_Jetpnorm->Draw("SameHist");
    gPad->SetLogy();
    gPad->Update();
    
    TLegend *leg4 = new TLegend(0.5, 0.55, 0.75, 0.8);
    leg4->SetBorderSize(0);
    leg4->AddEntry(BH_Jetpnorm, "BHadron Stream", "PE");
    leg4->AddEntry(DM_Jetpnorm, "DiMuon Stream", "L");
    leg4->Draw("SAME");
    
    //////////////////////////////////////////////////////
    
    TCanvas *c5 = new TCanvas("c5", "c", 700, 900);
    c5->Divide(1, 1);
    c5->cd(1);
    
    BH_JPsiM->Sumw2();
    TH1F *BH_JPsiMnorm = (TH1F *)BH_JPsiM->Clone("BH_JPsiMnorm");
    BH_JPsiMnorm->SetTitle("Normalized J/#Psi mass");
    BH_JPsiMnorm->Scale((1./(1.205*21))/(BH_JPsiM->Integral()), "width");
    BH_JPsiMnorm->SetLineColor(2);
    BH_JPsiMnorm->SetStats(0);
    BH_JPsiMnorm->Draw("Hist");
//    gPad->SetLogy();
//    gPad->Update();

    DM_JPsiM->Sumw2();
    TH1F *DM_JPsiMnorm = (TH1F *)DM_JPsiM->Clone("DM_JPsiMnorm");
    DM_JPsiMnorm->Scale((1./(1.205*21.5))/(DM_JPsiM->Integral()), "width");
    DM_JPsiMnorm->SetLineColor(4);
    DM_JPsiMnorm->SetStats(0);
    DM_JPsiMnorm->Draw("SameHist");
//    gPad->SetLogy();
//    gPad->Update();
//
    TLegend *leg5 = new TLegend(0.8, 0.85, 0.7, 0.72);
    leg5->SetBorderSize(0);
    leg5->AddEntry(BH_JPsiMnorm, "BHadron Stream", "PE");
    leg5->AddEntry(DM_JPsiMnorm, "DiMuon Stream", "L");
    leg5->Draw("SAME");
    
    c1->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/Bpt_var_norm.pdf");
    c2->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/Bp_var_norm.pdf");
    c3->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/Jetpt_var_norm.pdf");
    c4->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/Jetp_var_norm.pdf");
    c5->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/JPsiM_var_norm.pdf");
    
    outfile->Write();
    outfile->Close();
}
