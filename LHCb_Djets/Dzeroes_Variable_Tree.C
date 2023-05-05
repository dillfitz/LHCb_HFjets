#define Dzeroes_Variable_Tree_cxx
#include "Dzeroes_Variable_Tree.h"
//#include "DjetTree.C"
#include <iostream>
#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>
#include <vector>

using namespace std;

void Dzeroes_Variable_Tree::Loop() {
    int nentries = fChain->GetEntries();
//    int nentries = 500000;
    TString outfileName = Form("Dzeroes_Variable_Tree_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");

    cout << "Total number of events = " << nentries << endl;

    double jet_pt, jet_eta,  jet_rap;
    double jet_px, jet_py, jet_pz, jet_e;
    double pi_px, pi_py, pi_pz, pi_e;
    double K_px, K_py, K_pz, K_e;

    double dphi;
    double D0_ipchi2;

//    double dPx, dPy, dPz, dE, dPt, dM, dPhi, jPhi;

    TTree *Djet_tree = new TTree("Djet", "A tree with Dzeroes hadrons in jets");

    Djet_tree->Branch("jet_pt", &jet_pt);
    Djet_tree->Branch("jet_px", &jet_px);
    Djet_tree->Branch("jet_py", &jet_py);
    Djet_tree->Branch("jet_pz", &jet_pz);
    Djet_tree->Branch("jet_e", &jet_e);
    Djet_tree->Branch("jet_eta", &jet_eta);
    Djet_tree->Branch("jet_rap", &jet_rap);

//    Djet_tree->Branch("dPx", &dPx);
//    Djet_tree->Branch("dPy", &dPy);
//    Djet_tree->Branch("dPz", &dPz);
//    Djet_tree->Branch("dE", &dE);
//    Djet_tree->Branch("dPt", &dPt);
//    Djet_tree->Branch("dM", &dM);
//    Djet_tree->Branch("dPhi", &dPhi);
//    Djet_tree->Branch("jPhi", &jPhi);

    Djet_tree->Branch("pi_px", &pi_px);
    Djet_tree->Branch("pi_py", &pi_py);
    Djet_tree->Branch("pi_pz", &pi_pz);
    Djet_tree->Branch("pi_e", &pi_e);

    Djet_tree->Branch("K_px", &K_px);
    Djet_tree->Branch("K_py", &K_py);
    Djet_tree->Branch("K_pz", &K_pz);
    Djet_tree->Branch("K_e", &K_e);

    Djet_tree->Branch("dphi", &dphi);
    Djet_tree->Branch("D0_ipchi2", &D0_ipchi2);

    if (fChain == 0) {
        return;
    }

//    cout<<nentries<<endl;
    Long64_t nbytes = 0, nb = 0;

    int events = 0;
    int cut_npvs = 0;
    int cut_jetpt = 0;
    int cut_jeteta = 0;
    int cut_Dinjet = 0;

    for (int jentry = 0; jentry < nentries; jentry++) { //Long64_t
        if (jentry % 100000 == 0) {
            cout << "processing entry : " << jentry << endl;
        }

        //      Long64_t ientry = LoadTree(jentry);
        //      if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        TLorentzVector jet4P, pi4P, Kmeson4P, HFmeson;

        jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
        pi4P.SetPxPyPzE(pi_PX / 1000., pi_PY / 1000., pi_PZ / 1000., pi_PE / 1000.);
        Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
        HFmeson = pi4P + Kmeson4P;

        double HF_jet_dR = HFmeson.DeltaR(jet4P);

        if (nPVs > 1) {
            cut_npvs++;
            continue;
        }

        if (jet4P.Pt() < 20.) {
            cut_jetpt++;
            continue;
        }

        if (jet4P.Eta() < 2.5 || jet4P.Eta() > 4.0) {
            cut_jeteta++;
            continue;
        }

        if (HF_jet_dR > 0.5) {
            cut_Dinjet++;
            continue;
        }

//        if ((Jet_PT/1000.) < (20.) ) {continue;}
//        if ((Jet_Eta)<2.5 || Jet_Eta>4.0) {continue;}

        //Only Jets with 2 constituents or more
//        if ( Jet_Dtr_nrecodtr<(2) )  {continue;}
//        //if ( Jet_Dtr_nrecodtr<(2) || Jet_Dtr_nrecodtr>(5) )  {continue;}
//
//        //Discarding 2-constituents jets with one of them being a photon
//        if (Jet_Dtr_nrecodtr==2)
//        { if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) ) continue;}

        double leading_pT = 0;
        double cand_jetpt, testjet_phi;
        int n_maxpT_cand, n_maxpT_entry;

        dphi = 3.1415;
        vector < double > jetpts;
        bool JetFound = false;

        if (totCandidates > 1) {
            for (int icand = 0; icand < totCandidates; icand++) {
                GetEntry(jentry + icand - nCandidate);

                jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
                pi4P.SetPxPyPzE(pi_PX / 1000., pi_PY / 1000., pi_PZ / 1000., pi_PE / 1000.);

                Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
                HFmeson = pi4P + Kmeson4P;

                for (int j = 0; j < jetpts.size(); j++) {
                    if (fabs(jet4P.Pt() - jetpts[j]) < 1e-3) {
                        JetFound = true;
                    }
                }

                if (JetFound) {
                    continue;
                } else {
                    jetpts.push_back(jet4P.Pt());
                }

                if (HFmeson.DeltaR(jet4P) < 0.5) {
                    continue;
                }                                            //<0.5 for b-jets

//                if ((Jet_PT/1000.) < (15.) ) {continue;}
//
//                if ((Jet_Eta)<2.5 || Jet_Eta>4.0) {continue;}

                cand_jetpt = jet4P.Pt();

                if (cand_jetpt > leading_pT) {
                    leading_pT = cand_jetpt;
                    n_maxpT_cand = nCandidate;
                    n_maxpT_entry = jentry + icand - nCandidate;
                }
            }

            GetEntry(n_maxpT_entry);

            jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);

            testjet_phi = jet4P.Phi();
        }

        GetEntry(jentry);

        jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
        pi4P.SetPxPyPzE(pi_PX / 1000., pi_PY / 1000., pi_PZ / 1000., pi_PE / 1000.);
        Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
        HFmeson = pi4P + Kmeson4P;

        if (totCandidates > 1) {
            dphi = checkphi(fabs(checkphi((HFmeson.Phi()) - checkphi(testjet_phi))));
        }

//        for (int j=0; j<Jet_Dtr_nrecodtr; ++j)
//        {
//            if ( abs( Jet_Dtr_ID[j] ) == 421)  //here
//            {
//                //cout << Jet_PT << endl;
//                TLorentzVector d4vec(Jet_Dtr_PX[j]/1000.,
//                                     Jet_Dtr_PY[j]/1000.,
//                                     Jet_Dtr_PZ[j]/1000.,
//                                     Jet_Dtr_E[j]/1000.);
//
//                TVector3 d3vec(dPx, dPy, dPz);
//                TVector3 jet3vec(Jet_PX/1000., Jet_PY/1000., Jet_PZ/1000.);
//
//                dPhi = d3vec.Phi();
//                dPt = Jet_Dtr_PT[j]/1000.;
//
//                dPx = d4vec.Px();
//                dPy = d4vec.Py();
//                dPz = d4vec.Pz();
//                dE = d4vec.E();
//                dM = d4vec.M();
//
//                jPhi = jet3vec.Phi();
//
//            } // if PDG = 421 Loop
//
//        } // Jet Daugthers Loops

        jet_pt = jet4P.Pt();
        jet_eta = jet4P.Eta();
        jet_px = jet4P.Px();
        jet_py = jet4P.Py();
        jet_pz = jet4P.Pz();
        jet_e = jet4P.E();
        jet_rap = jet4P.Rapidity();

        pi_px = pi4P.Px();
        pi_py = pi4P.Py();
        pi_pz = pi4P.Pz();
        pi_e = pi4P.E();

        K_px = Kmeson4P.Px();
        K_py = Kmeson4P.Py();
        K_pz = Kmeson4P.Pz();
        K_e = Kmeson4P.E();

        D0_ipchi2 = D0_IPCHI2_OWNPV;

        events++;
        Djet_tree->Fill();
    }

    cout << "Total number of events processed = " << events << endl;
    cout << "npvs = " << cut_npvs << endl;
    cout << "jetpt = " << cut_jetpt << endl;
    cout << "jeteta = " << cut_jeteta << endl;
    cout << "Dinjet = " << cut_Dinjet << endl;

    outfile->Write();
    outfile->Close();
}
