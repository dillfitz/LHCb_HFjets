#define B_Tree_BH_Comp_cxx
#include <iostream>
#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>
#include <vector>
#include "B_Tree_BH_Comp.h"

void B_Tree_BH_Comp::Loop() {
    int nentries = fChain->GetEntries();
//    int nentries = 500000;
    TString outfileName = Form("BH_Stream_Var_Tree_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");

    cout << "Total number of events = " << nentries << endl;

    double jet_pt, jet_eta, jet_phi;
    double jet_px, jet_py, jet_pz, jet_e;

    double K_pt, mup_pt, mum_pt;
    double K_px, K_py, K_pz, K_e;
    double mup_px, mup_py, mup_pz, mup_e;
    double mum_px, mum_py, mum_pz, mum_e;

    double JPsi_pt, JPsi_m;
    double JPsi_px, JPsi_py, JPsi_pz, JPsi_e;

    double HFmeson_phi, HFmeson_eta, HFmeson_pt;

    TTree *B_hadron_Tree = new TTree("BH_Stream", "A tree with B mesons in jets from BHadreon Stream");

    B_hadron_Tree->Branch("jet_pt", &jet_pt);
    B_hadron_Tree->Branch("jet_eta", &jet_eta);
    B_hadron_Tree->Branch("jet_phi", &jet_phi);
    B_hadron_Tree->Branch("jet_px", &jet_px);
    B_hadron_Tree->Branch("jet_py", &jet_py);
    B_hadron_Tree->Branch("jet_pz", &jet_pz);
    B_hadron_Tree->Branch("jet_e", &jet_e);

    B_hadron_Tree->Branch("mup_pt", &mup_pt);
    B_hadron_Tree->Branch("mup_px", &mup_px);
    B_hadron_Tree->Branch("mup_py", &mup_py);
    B_hadron_Tree->Branch("mup_pz", &mup_pz);
    B_hadron_Tree->Branch("mup_e", &mup_e);

    B_hadron_Tree->Branch("mum_pt", &mum_pt);
    B_hadron_Tree->Branch("mum_px", &mum_px);
    B_hadron_Tree->Branch("mum_py", &mum_py);
    B_hadron_Tree->Branch("mum_pz", &mum_pz);
    B_hadron_Tree->Branch("mum_e", &mum_e);

    B_hadron_Tree->Branch("K_pt", &K_pt);
    B_hadron_Tree->Branch("K_px", &K_px);
    B_hadron_Tree->Branch("K_py", &K_py);
    B_hadron_Tree->Branch("K_pz", &K_pz);
    B_hadron_Tree->Branch("K_e", &K_e);

    B_hadron_Tree->Branch("JPsi_pt", &JPsi_pt);
    B_hadron_Tree->Branch("JPsi_m", &JPsi_m);
    B_hadron_Tree->Branch("JPsi_px", &JPsi_px);
    B_hadron_Tree->Branch("JPsi_py", &JPsi_py);
    B_hadron_Tree->Branch("JPsi_pz", &JPsi_pz);
    B_hadron_Tree->Branch("JPsi_e", &JPsi_e);

    B_hadron_Tree->Branch("HFmeson_phi", &HFmeson_phi);
    B_hadron_Tree->Branch("HFmeson_eta", &HFmeson_eta);
    B_hadron_Tree->Branch("HFmeson_pt", &HFmeson_pt);

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

        jet_pt = jet4P.Pt();
        jet_eta = jet4P.Eta();
        jet_px = jet4P.Px();
        jet_py = jet4P.Py();
        jet_pz = jet4P.Pz();
        jet_e = jet4P.E();
        jet_phi = jet4P.Phi();

        K_pt = Kmeson4P.Pt();
        mup_pt = mup4P.Pt();
        mum_pt = mum4P.Pt();

        K_px = Kmeson4P.Px();
        K_py = Kmeson4P.Py();
        K_pz = Kmeson4P.Pz();
        K_e = Kmeson4P.E();

        mup_px = mup4P.Px();
        mup_py = mup4P.Py(),
        mup_pz = mup4P.Pz(),
        mup_e = mup4P.E();

        mum_px = mum4P.Px();
        mum_py = mum4P.Py();
        mum_pz = mum4P.Pz();
        mum_e = mum4P.E();

        JPsi_pt = JPsi.Pt();
        JPsi_m = JPsi.M();
        JPsi_px = JPsi.Px();
        JPsi_py = JPsi.Py();
        JPsi_pz = JPsi.Pz();
        JPsi_e = JPsi.E();

        HFmeson_phi = HFmeson.Phi();
        HFmeson_eta = HFmeson.Eta();
        HFmeson_pt = HFmeson.Pt();

        B_hadron_Tree->Fill();
    }

    outfile->Write();
    outfile->Close();
}
