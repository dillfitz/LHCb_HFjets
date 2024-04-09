#define Bjet_BH_Variable_Tree_cxx
#include "Bjet_BH_Variable_Tree.h"
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Header.h"
#include <stdio.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include "TH1.h"
#include "TFile.h"
#include <vector>
#include <cmath>
#include <TMath.h>

using namespace std;

void Bjet_BH_Variable_Tree::Loop()
{
    int nentries = fChain->GetEntries();
//    int nentries = 500000;
    TString outfileName = Form("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Bjets_BH_Variable_Tree_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");

    cout << "Total number of events (before cuts): " << nentries << endl;

    double jet_pt, jet_eta, jet_phi, jet_m;
    double jet_px, jet_py, jet_pz, jet_e;
    
    double mum_px, mum_py, mum_pz, mum_e;
    double mup_px, mup_py, mup_pz, mup_e;
    double K_px, K_py, K_pz, K_e;
    
    double B_px, B_py, B_pz, B_e;
    double B_m, B_pt, B_eta, B_phi;

    double dphi;
    int nPV, Jet_Dtr_ndtr;
    long eventN;
    
    TTree *Bjet_tree = new TTree("Bjet", "A tree with B hadrons in jets from BHadron Stream");

    Bjet_tree->Branch("jet_pt", &jet_pt);
    Bjet_tree->Branch("jet_eta", &jet_eta);
    Bjet_tree->Branch("jet_phi", &jet_phi);
    Bjet_tree->Branch("jet_m", &jet_m);
    
    Bjet_tree->Branch("jet_px", &jet_px);
    Bjet_tree->Branch("jet_py", &jet_py);
    Bjet_tree->Branch("jet_pz", &jet_pz);
    Bjet_tree->Branch("jet_e", &jet_e);

    Bjet_tree->Branch("mum_px", &mum_px);
    Bjet_tree->Branch("mum_py", &mum_py);
    Bjet_tree->Branch("mum_pz", &mum_pz);
    Bjet_tree->Branch("mum_e", &mum_e);
    
    Bjet_tree->Branch("mup_px", &mup_px);
    Bjet_tree->Branch("mup_py", &mup_py);
    Bjet_tree->Branch("mup_pz", &mup_pz);
    Bjet_tree->Branch("mup_e", &mup_e);

    Bjet_tree->Branch("K_px", &K_px);
    Bjet_tree->Branch("K_py", &K_py);
    Bjet_tree->Branch("K_pz", &K_pz);
    Bjet_tree->Branch("K_e", &K_e);
    
    Bjet_tree->Branch("B_px", &B_px);
    Bjet_tree->Branch("B_py", &B_py);
    Bjet_tree->Branch("B_pz", &B_pz);
    Bjet_tree->Branch("B_e", &B_e);
    Bjet_tree->Branch("B_m", &B_m);
    Bjet_tree->Branch("B_pt", &B_pt);
    Bjet_tree->Branch("B_eta", &B_eta);
    Bjet_tree->Branch("B_phi", &B_phi);

    Bjet_tree->Branch("dphi", &dphi);
    Bjet_tree->Branch("nPV", &nPV);
    Bjet_tree->Branch("Jet_Dtr_ndtr", &Jet_Dtr_ndtr);
    Bjet_tree->Branch("eventN", &eventN);

    if (fChain == 0) {
        return;
    }

    Long64_t nbytes = 0, nb = 0;

    int events = 0;
    int cut_npvs = 0;
    int cut_jetpt = 0;
    int cut_jeteta = 0;
    int cut_Dinjet = 0;
    int n_Bphoton = 0;
    int HF_counter = 0;

    for (int jentry = 0; jentry < nentries; jentry++) { //Long64_t
        if (jentry % 100000 == 0) {
            cout << "processing entry : " << jentry << endl;
        }

        //      Long64_t ientry = LoadTree(jentry);
        //      if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        TLorentzVector jet4P, mup4P, mum4P, Kmeson4P, HFmeson;

        jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
        mup4P.SetPxPyPzE(mup_PX/1000., mup_PY/1000., mup_PZ/1000., mup_PE/1000.);
        mum4P.SetPxPyPzE( mum_PX/1000., mum_PY/1000., mum_PZ/1000., mum_PE/1000.);
        Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
        HFmeson = mum4P + mup4P + Kmeson4P;

        double HF_jet_dR = HFmeson.DeltaR(jet4P);

        if (nPVs > 1) {
            cut_npvs++;
            continue;
        }

        if (jet4P.Pt() < 15.0) {
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
        
        // Dicardit one constituet jets
        if ( Jet_Dtr_nrecodtr<(2) )  {continue;}

        //Discarding 2-constituents jets with one of them being a photon
        if (Jet_Dtr_nrecodtr==2)
        {
            if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) )
            {
                n_Bphoton++;
                continue;
                
            }
        }
        
//        Discarding artificially reconstructed B-s (i.e., two B's in a jets with shared daughters)
        int HF_artificial = 0;
        for (int i =0; i<Jet_Dtr_nrecodtr; i++)
        {
            if( abs(Jet_Dtr_ID[i])==521 )
            {
                HF_artificial ++;
            }
        }
        
        if (HF_artificial > 1) {continue;}
        
        nPV = nPVs;
        Jet_Dtr_ndtr = Jet_Dtr_nrecodtr;
        eventN = eventNumber;
        
//        cout<< "Event: " << jentry << endl;
//        cout<< "B meson |p| = " << HFmeson.P() << endl;
//        cout<< "Jet |p| = " << jet4P.P() << endl;
        /////// B a c k   to    B a c k   C u t  ///// one of the goals: to try and decrease contribution to Heavy flavor from gluon splits g->cc(bar) etc.
        double cand_jetpt;

        dphi = 3.1415;
        vector < double > jetpts;
        bool JetFound = false;
        double jetradius =0.5;
        
        double leading_pT = 0;
        int n_maxpT_cand = -999;
        int n_maxpT_entry = -999;
        int n_HFpt_entry = -999;
//        int HF_counter = 0;
        double last_HFjet = 0;
        double last_HFpt = 0;
        double testjet_phi, testjet_px, testjet_py, testjet_pz, testjet_e;
        int ncand = nCandidate;
        
        if (totCandidates > 1) {
            for (int icand = 0; icand < totCandidates; icand++) {
                GetEntry(jentry + icand - ncand);
                
                jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
                mup4P.SetPxPyPzE(mup_PX/1000., mup_PY/1000., mup_PZ/1000., mup_PE/1000.);
                mum4P.SetPxPyPzE( mum_PX/1000., mum_PY/1000., mum_PZ/1000., mum_PE/1000.);
                Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
                HFmeson = mum4P + mup4P + Kmeson4P;
                
                bool hasHF = HFmeson.DeltaR(jet4P) < jetradius;
                
                double cand_jetpt = jet4P.Pt();
                // cout<<"Has HF"<<endl;
                if(!hasHF){
                    if(cand_jetpt > leading_pT){
                        // cout<<leading_pT<<", "<<cand_jetpt<<endl;
                        leading_pT = cand_jetpt;
                        n_maxpT_cand = nCandidate;
                        n_maxpT_entry = jentry+icand-ncand;
                        // cout<<n_maxpT_entry<<endl;
                    }
                }
                else{
                    HF_counter++;
                    if(HFmeson.Pt() > last_HFpt) n_HFpt_entry = jentry+icand-ncand;
                    
                    // cout<<"n_HFpt_entry = "<<n_HFpt_entry<<endl;
                    // cout<<HF_counter<<endl;
                    last_HFjet = jet4P.Pt();
                    last_HFpt = HFmeson.Pt();
                }
            }
            GetEntry(n_maxpT_entry);
            jet4P.SetPxPyPzE(Jet_PX/1000.,
                             Jet_PY/1000.,
                             Jet_PZ/1000.,
                             Jet_PE/1000.);
            testjet_phi = jet4P.Phi();
        }

        GetEntry(jentry);

        jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
        mup4P.SetPxPyPzE(mup_PX/1000., mup_PY/1000., mup_PZ/1000., mup_PE/1000.);
        mum4P.SetPxPyPzE( mum_PX/1000., mum_PY/1000., mum_PZ/1000., mum_PE/1000.);
        Kmeson4P.SetPxPyPzE(K_PX / 1000., K_PY / 1000., K_PZ / 1000., K_PE / 1000.);
        HFmeson = mum4P + mup4P + Kmeson4P;

        if (totCandidates > 1) {
            dphi = checkphi(fabs(checkphi((HFmeson.Phi()) - checkphi(testjet_phi))));
        }
       
        
        jet_pt = jet4P.Pt();
        jet_eta = jet4P.Eta();
        jet_phi = jet4P.Phi();
        jet_m = jet4P.M();
        
        jet_px = jet4P.Px();
        jet_py = jet4P.Py();
        jet_pz = jet4P.Pz();
        jet_e = jet4P.E();
        
        mum_px = mum4P.Px();
        mum_py = mum4P.Py();
        mum_pz = mum4P.Pz();
        mum_e = mum4P.E();
    
        mup_px = mup4P.Px();
        mup_py = mup4P.Py();
        mup_pz = mup4P.Pz();
        mup_e = mup4P.E();

        K_px = Kmeson4P.Px();
        K_py = Kmeson4P.Py();
        K_pz = Kmeson4P.Pz();
        K_e = Kmeson4P.E();

        B_px = HFmeson.Px();
        B_py = HFmeson.Py();
        B_pz = HFmeson.Pz();
        B_e = HFmeson.E();
        B_pt = HFmeson.Pt();
        B_m = HFmeson.M();
        B_eta = HFmeson.Eta();
        B_phi = HFmeson.Phi();
    
        events++;
        Bjet_tree->Fill();
    }

    cout << "Total number of events processed (after cuts): " << events << endl;
//    cout << "npvs = " << cut_npvs << endl;
//    cout << "Jets with pt < 15 GeV/c: " << cut_jetpt << endl;
    cout << "Jets outside LHCb eta acceptance: " << cut_jeteta << endl;
    cout << "HFs not in jet: " << cut_Dinjet << endl;
//    cout<< "More than 1 HF in jet: " << HF_artificial << endl;
//    cout << "Number of HF within R=0.5: " << HF_counter << endl;
    cout << "B-photon jets: " << n_Bphoton << endl;

    outfile->Write();
    outfile->Close();
}

