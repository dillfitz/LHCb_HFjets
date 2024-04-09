#define B_Tree_DM_Comp_cxx
#include "B_Tree_DM_Comp.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>

void B_Tree_DM_Comp::Loop()
{
    int nentries = fChain->GetEntries();
//    int nentries = 500000;
    TString outfileName = Form("DM_Stream_Var_Tree_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");

    cout << "Total number of events = " << nentries << endl;

    double DM_jet_pt, DM_jet_eta, DM_jet_phi;
    double DM_jet_px, DM_jet_py, DM_jet_pz,DM_jet_e;

    double DM_K_pt, DM_mup_pt, DM_mum_pt;
    double DM_K_px, DM_K_py, DM_K_pz, DM_K_e;
    double DM_mup_px, DM_mup_py, DM_mup_pz, DM_mup_e;
    double DM_mum_px, DM_mum_py, DM_mum_pz, DM_mum_e;

    double DM_JPsi_pt, DM_JPsi_m;
    double DM_JPsi_px, DM_JPsi_py, DM_JPsi_pz, DM_JPsi_e;

    double DM_HFmeson_phi, DM_HFmeson_eta, DM_HFmeson_pt;

    TTree *DiMuon_Tree = new TTree("DM_Stream", "A tree with B mesons in jets from DiMuon Stream");

    DiMuon_Tree->Branch("DM_jet_pt", &DM_jet_pt);
    DiMuon_Tree->Branch("DM_jet_eta", &DM_jet_eta);
    DiMuon_Tree->Branch("DM_jet_phi", &DM_jet_phi);
    DiMuon_Tree->Branch("DM_jet_px", &DM_jet_px);
    DiMuon_Tree->Branch("DM_jet_py", &DM_jet_py);
    DiMuon_Tree->Branch("DM_jet_pz", &DM_jet_pz);
    DiMuon_Tree->Branch("DM_jet_e", &DM_jet_e);

    DiMuon_Tree->Branch("DM_mup_pt", &DM_mup_pt);
    DiMuon_Tree->Branch("DM_mup_px", &DM_mup_px);
    DiMuon_Tree->Branch("DM_mup_py", &DM_mup_py);
    DiMuon_Tree->Branch("DM_mup_pz", &DM_mup_pz);
    DiMuon_Tree->Branch("DM_mup_e", &DM_mup_e);

    DiMuon_Tree->Branch("DM_mum_pt", &DM_mum_pt);
    DiMuon_Tree->Branch("DM_mum_px", &DM_mum_px);
    DiMuon_Tree->Branch("DM_mum_py", &DM_mum_py);
    DiMuon_Tree->Branch("DM_mum_pz", &DM_mum_pz);
    DiMuon_Tree->Branch("DM_mum_e", &DM_mum_e);

    DiMuon_Tree->Branch("DM_K_pt", &DM_K_pt);
    DiMuon_Tree->Branch("DM_K_px", &DM_K_px);
    DiMuon_Tree->Branch("DM_K_py", &DM_K_py);
    DiMuon_Tree->Branch("DM_K_pz", &DM_K_pz);
    DiMuon_Tree->Branch("DM_K_e", &DM_K_e);

    DiMuon_Tree->Branch("DM_JPsi_pt", &DM_JPsi_pt);
    DiMuon_Tree->Branch("DM_JPsi_m", &DM_JPsi_m);
    DiMuon_Tree->Branch("DM_JPsi_px", &DM_JPsi_px);
    DiMuon_Tree->Branch("DM_JPsi_py", &DM_JPsi_py);
    DiMuon_Tree->Branch("DM_JPsi_pz", &DM_JPsi_pz);
    DiMuon_Tree->Branch("DM_JPsi_e", &DM_JPsi_e);

    DiMuon_Tree->Branch("DM_HFmeson_phi", &DM_HFmeson_phi);
    DiMuon_Tree->Branch("DM_HFmeson_eta", &DM_HFmeson_eta);
    DiMuon_Tree->Branch("DM_HFmeson_pt", &DM_HFmeson_pt);

    if (fChain == 0) {
        return;
    }

//   Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;

    for (int jentry = 0; jentry < nentries; jentry++) {
        if (jentry % 100000 == 0) {
            cout << "processing entry : " << jentry << endl;
        }

        //      Long64_t ientry = LoadTree(jentry);
        //      if (ientry < 0) break;

        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        if ((Jet_Eta) < 2.5 || Jet_Eta > 4.0) {
            continue;
        }

        //Only Jets with 2 constituents or more
        if (Jet_Dtr_nrecodtr < (2) ) {
            continue;
        }

        //if ( Jet_Dtr_nrecodtr<(2) || Jet_Dtr_nrecodtr>(5) )  {continue;}

        //Discarding 2-constituents jets with one of them being a photon
        if (Jet_Dtr_nrecodtr == 2) {
            if ( (Jet_Dtr_ID[0] == 22) || (Jet_Dtr_ID[1] == 22) ) {
                continue;
            }
        }

        TLorentzVector jet4P, mum4P, mup4P, JPsi, Kmeson4P, HFmeson;

        jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
        mum4P.SetPxPyPzE(mum_PX / 1000., mum_PY / 1000., mum_PZ / 1000., mum_PE / 1000.);
        mup4P.SetPxPyPzE(mup_PX / 1000., mup_PY / 1000., mup_PZ / 1000., mup_PE / 1000.);
        Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
        HFmeson = mum4P + mup4P + Kmeson4P;
        JPsi = mum4P + mup4P;

        DM_jet_pt = jet4P.Pt();
        DM_jet_eta = jet4P.Eta();
        DM_jet_px = jet4P.Px();
        DM_jet_py = jet4P.Py();
        DM_jet_pz = jet4P.Pz();
        DM_jet_e = jet4P.E();
        DM_jet_phi = jet4P.Phi();

        DM_K_pt = Kmeson4P.Pt();
        DM_mup_pt = mup4P.Pt();
        DM_mum_pt = mum4P.Pt();

        DM_K_px = Kmeson4P.Px();
        DM_K_py = Kmeson4P.Py();
        DM_K_pz = Kmeson4P.Pz();
        DM_K_e = Kmeson4P.E();

        DM_mup_px = mup4P.Px();
        DM_mup_py = mup4P.Py(),
        DM_mup_pz = mup4P.Pz(),
        DM_mup_e = mup4P.E();

        DM_mum_px = mum4P.Px();
        DM_mum_py = mum4P.Py();
        DM_mum_pz = mum4P.Pz();
        DM_mum_e = mum4P.E();

        DM_JPsi_pt = JPsi.Pt();
        DM_JPsi_m = JPsi.M();
        DM_JPsi_px = JPsi.Px();
        DM_JPsi_py = JPsi.Py();
        DM_JPsi_pz = JPsi.Pz();
        DM_JPsi_e = JPsi.E();

        DM_HFmeson_phi = HFmeson.Phi();
        DM_HFmeson_eta = HFmeson.Eta();
        DM_HFmeson_pt = HFmeson.Pt();

        DiMuon_Tree->Fill();
    }

    outfile->Write();
    outfile->Close();
}

