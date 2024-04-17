
/*
   This macro creates a tree from a MC ROOT file that stores "TRUTH" Monte Carlo variables
 */

//#include "./MC_10192023/BjetMCTree.C"  //Truth
//#include "./MC_08152023/BjetMCTree.C"  //Truth
//#include "./MC_10162023/BjetMCTree.C"  //Truth
//#include "./MC_03032024/BjetMCTree.C"  //Truth
#include "./MC_04102024/BjetMCTree.C"  //Truth

#include <iostream>
#include <TCanvas.h>
#include <vector>
//#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Header.h"
#include "../Reference/Helpers.h"
//#include "/Users/josearias18/Desktop/QCDc2/root/RooUnfold/src/RooUnfoldResponse.h"
//#include "/Users/josearias18/Desktop/QCDc2/root/RooUnfold/src/RooUnfoldBayes.h"
//#include "../Helpers.h"
//#include "../RooHelpers.h"

using namespace std;

// All events: -1
void MCMakeVarTree(int NumEvts_user = -1, int dataset = 91599, bool chargedJetCut_user = false) {
    
//    BjetMCTree Tree(0, isMagUp, isMagDown);

    int NumEvts = NumEvts_user;
    int NumEvtsTruth = NumEvts_user;
    followHardest = false;
    truthLevel = true;
    chargedJetCut = chargedJetCut_user;
    
    if (truthLevel)
    {
        ghostCut = false;
    }
    
    int JetMeth = (dataset / 1000) % 10;
    int flavor = (dataset / 100) % 10;
    int ptRange = (dataset / 10) % 10;
    int Mag = (dataset / 1) % 10;

    int HF_pdgcode = -999;

//    double mass_num;

    if (flavor == 5) 
    {
        mass_num = 4.2;
        HF_pdgcode = 521;
    } 
    else if (flavor == 4)
    {
        mass_num = 1.25;
        HF_pdgcode = 421;
    }
    else if (flavor ==1)
    {
        mass_num = 0.001;
        followHardest = true; 
    }
    
//    if (NumEvts_user == -1) {
//        NumEvts_user = Tree.fChain->GetEntries();
//        NumEvts = NumEvts_user;
//    } else {
//        NumEvts = NumEvts_user;
//    }

// int NumEvts = NumEvts_user;
//
// int NumEvtsTruth = NumEvts_user;
//
// int NumEvts = Tree.fChain->GetEntries();

    TString extension_read, extension_RootFilesMC;

    //  Naming Convention:
    //  {$1}{$2}{$3}{$4}{$5}
    //  $1: Year: 2016 = 6, 2017 = 7, 2018 = 8, All = 9
    //  $2: jets or dijets: TaggedDijets = 1, else = 2
    //  $3: flavor: b = 5, c = 4, udsg = 1
    //  $4: pT: pt15pt20 = 0, pt20pt50 = 1, pt50 = 2, else = 3
    //  $5: Magnet: MD = 0, MU = 1, Both = 9

    TString str_Mag = "";
    TString str_pT = "";
    TString str_level = "";
    TString str_followHard = "";
    TString str_flavor = "";
    TString str_ghost = "";
    
    TString str_charged = "";
    
//    TString str_mag = "";
    
    if (Mag == 0)
        str_Mag = "_MD";
    else if (Mag == 1)
        str_Mag = "_MU";

    if (flavor == 1) {
        str_flavor = "_udsg";
    } else if (flavor == 4) {
        str_flavor = "_c";
    } else if (flavor == 5) {
        str_flavor = "_b";
    }

    // if(ptRange == 0) str_pT = "pt15pt20";
    // else if(ptRange == 1) str_pT = "pt20pt50";
    // else if(ptRange == 2) str_pT = "pt50";

    if (truthLevel) {
        str_level = "truth";
    } else {
        str_level = "reco";
    }
    
    if (flavor == 1)
        str_followHard = "_hard";
      else
      {
        if (followHardest)
          str_followHard = "_hard";
        else
          str_followHard = "_HF";
      }

      if (ghostCut)
        str_ghost = Form("_ghost_%.1f", ghostProb);
      if (chargedJetCut)
        str_charged = "_charge";
      TString str_tree;

    TString RecoHF = "OnlyOneRecoHF";

    TString extension;
    extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
    
//    extension = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_Mag + str_flavor;
//    extension = TString("MCtree_") + str_level + str_mag + Form("_ev_%d", NumEvts)  + str_flavor;
//    extension = TString("MCtree_") + str_level + Form("_ev_%d", NumEvts)  + str_flavor + RecoHF;

    BjetMCTree Tree(0, dataset, false);
    
    cout << "Total number of events = " << Tree.fChain->GetEntries() << endl;
    if (NumEvts == -1) {
        NumEvts = Tree.fChain->GetEntries();
    }

    // int NumEvts = 0;
    // cout <<"Choose number of events (-1: All Events, or enter integer): ";
    // cin>> NumEvts;

    extension_RootFilesMC = TString("");

    TFile f(extension_RootFilesMC + extension + ".root", "RECREATE");
    
    // FF(z) Histograms 
    TH1D *h1_z_truth = new TH1D("z_truth", "", 80, 0.0, 1.01);
    TH1D *h1_z_truth_b = new TH1D("z_truth_b", "",  80, 0.0, 1.01);
    TH1D *h1_z_truth_g = new TH1D("z_truth_g", "", 80, 0.0, 1.01);

    // Truth Variables (from Truth Tree)
    double jet_pt, jet_eta, meas_jet_pt, meas_jet_eta;
    double jet_px, jet_py, jet_pz, jet_e;
    double HF_px, HF_py, HF_pz, HF_e;
    double HF_pt;
    double jet_rap, meas_jet_rap;
    double K_px, K_py, K_pz, K_e;
    double mup_px, mup_py, mup_pz, mup_e;
    double mum_px, mum_py, mum_pz, mum_e;

    // Reco Variables (from Truth Tree)
    double meas_jet_px, meas_jet_py, meas_jet_pz, meas_jet_e;
    double meas_mup_px, meas_mup_py, meas_mup_pz, meas_mup_e;
    double meas_mum_px, meas_mum_py, meas_mum_pz, meas_mum_e;
    double meas_K_px, meas_K_py, meas_K_pz, meas_K_e;
    double meas_HF_px, meas_HF_py, meas_HF_pz, meas_HF_e;
    double meas_HF_pt;

    double truth_z, truth_jt, truth_r;
    double truth_z_b, truth_jt_b, truth_r_b;
    double truth_zg, truth_jtg, truth_rg;
    double meas_z, meas_jt, meas_r;
    double meas_inJet_z, meas_inJet_jt, meas_inJet_r;
    double jet_pt_recotruthratio, HF_pt_recotruthratio;

    int nsplits, ndtrs;
    int meas_nsplits, meas_ndtrs;
    int GluonTag, nTracks;
    int NumHFHads, eventNumber;
    int NumDtrRecoHF;

    bool hasRecoHF;
    bool Hasbbbar;
    bool isSingle_tr_Bjet;
    bool isPhoton_tr_Bjet;

    // TLorentzVector
    TTree *BTree = new TTree("BTree", "B-jets Tree Variables");

    BTree->Branch("eventNumber", &eventNumber);

    BTree->Branch("jet_pt", &jet_pt);
    BTree->Branch("jet_eta", &jet_eta);
    BTree->Branch("jet_rap", &jet_rap);
    BTree->Branch("jet_px", &jet_px);
    BTree->Branch("jet_py", &jet_py);
    BTree->Branch("jet_pz", &jet_pz);
    BTree->Branch("jet_e", &jet_e);

    BTree->Branch("HF_px", &HF_px);
    BTree->Branch("HF_py", &HF_py);
    BTree->Branch("HF_pz", &HF_pz);
    BTree->Branch("HF_e", &HF_e);
    BTree->Branch("HF_pt", &HF_pt);

    BTree->Branch("mum_px", &mum_px);
    BTree->Branch("mum_py", &mum_py);
    BTree->Branch("mum_pz", &mum_pz);
    BTree->Branch("mum_e", &mum_e);
    BTree->Branch("mup_px", &mup_px);
    BTree->Branch("mup_py", &mup_py);
    BTree->Branch("mup_pz", &mup_pz);
    BTree->Branch("mup_e", &mup_e);
    BTree->Branch("K_px", &K_px);
    BTree->Branch("K_py", &K_py);
    BTree->Branch("K_pz", &K_pz);
    BTree->Branch("K_e", &K_e);


    BTree->Branch("meas_jet_pt", &meas_jet_pt);
    BTree->Branch("meas_jet_eta", &meas_jet_eta);
    BTree->Branch("meas_jet_rap", &meas_jet_rap);
    BTree->Branch("meas_jet_px", &meas_jet_px);
    BTree->Branch("meas_jet_py", &meas_jet_py);
    BTree->Branch("meas_jet_pz", &meas_jet_pz);
    BTree->Branch("meas_jet_e", &meas_jet_e);

    BTree->Branch("meas_HF_px", &meas_HF_px);
    BTree->Branch("meas_HF_py", &meas_HF_py);
    BTree->Branch("meas_HF_pz", &meas_HF_pz);
    BTree->Branch("meas_HF_e", &meas_HF_e);
    BTree->Branch("meas_HF_pt", &meas_HF_pt);

      BTree->Branch("meas_mum_px", &meas_mum_px);
      BTree->Branch("meas_mum_py", &meas_mum_py);
      BTree->Branch("meas_mum_pz", &meas_mum_pz);
      BTree->Branch("meas_mum_e", &meas_mum_e);
      BTree->Branch("meas_mup_px", &meas_mup_px);
      BTree->Branch("meas_mup_py", &meas_mup_py);
      BTree->Branch("meas_mup_pz", &meas_mup_pz);
      BTree->Branch("meas_mup_e", &meas_mup_e);
      BTree->Branch("meas_K_px", &meas_K_px);
      BTree->Branch("meas_K_py", &meas_K_py);
      BTree->Branch("meas_K_pz", &meas_K_pz);
      BTree->Branch("meas_K_e", &meas_K_e);

    BTree->Branch("GluonTag", &GluonTag);
    BTree->Branch("nTracks", &nTracks);
    BTree->Branch("Hasbbbar", &Hasbbbar);
    BTree->Branch("NumHFHads", &NumHFHads);
    BTree->Branch("NumDtrRecoHF", &NumDtrRecoHF);
    BTree->Branch("hasRecoHF", &hasRecoHF);
    BTree->Branch("isSingle_tr_Bjet", &isSingle_tr_Bjet);
    BTree->Branch("isPhoton_tr_Bjet", &isPhoton_tr_Bjet);

    BTree->Branch("truth_z", &truth_z);
    BTree->Branch("truth_jt", &truth_jt);
    BTree->Branch("truth_r", &truth_r);
    BTree->Branch("truth_z_b", &truth_z_b);
    BTree->Branch("truth_jt_b", &truth_jt_b);
    BTree->Branch("truth_r_b", &truth_r_b);
    BTree->Branch("truth_zg", &truth_zg);
    BTree->Branch("truth_jtg", &truth_jtg);
    BTree->Branch("truth_rg", &truth_rg);

    BTree->Branch("meas_z", &meas_z);
    BTree->Branch("meas_jt", &meas_jt);
    BTree->Branch("meas_r", &meas_r);

    BTree->Branch("meas_inJet_z", &meas_inJet_z);
    BTree->Branch("meas_inJet_jt", &meas_inJet_jt);
    BTree->Branch("meas_inJet_r", &meas_inJet_r);
    
    BTree->Branch("jet_pt_recotruthratio", &jet_pt_recotruthratio);
    BTree->Branch("HF_pt_recotruthratio", &HF_pt_recotruthratio);

//
// Event loop
//

    int eventNum;
    unsigned long long last_eventNum = 0;
    int events = 0;

    bool maxjetpT_found = false;
    int NumRecoHF = 0;

    int cut_npvs = 0;
    int cut_eta = 0;
    int cut_pt = 0;
    int cut_HFdR = 0;
    int Num_Single_tr_Bjet = 0;
    int Num_Photon_tr_Bjet = 0;

//    double jetradius = 0.5;

    for (int ev = 0; ev < NumEvts; ev++) {
        Tree.GetEntry(ev);

        // EventTree->GetEntry(ev);
        // cout<<recojet_e<<", ";
        if (ev % 10000 == 0) {
            cout << "Executing event " << ev << endl;
        }


        if (ev != 0) {
            
            
            if (last_eventNum == Tree.eventNumber) {
                continue;
            }
        }
        events++;

        
        TLorentzVector HFjet, recojet, meas_HFjet, HFmeson, mup, mum, Kmeson, Jpsi;
        TLorentzVector meas_Zdtr3, meas_mup, meas_mum, meas_HFmeson, meas_Kmeson;

        mup.SetPxPyPzE(Tree.MCJet_truth_mup_PX / 1000.,
                       Tree.MCJet_truth_mup_PY / 1000.,
                       Tree.MCJet_truth_mup_PZ / 1000.,
                       Tree.MCJet_truth_mup_PE / 1000.);
        mum.SetPxPyPzE(Tree.MCJet_truth_mum_PX / 1000.,
                       Tree.MCJet_truth_mum_PY / 1000.,
                       Tree.MCJet_truth_mum_PZ / 1000.,
                       Tree.MCJet_truth_mum_PE / 1000.);
        Kmeson.SetPxPyPzE(Tree.MCJet_truth_K_PX / 1000.,
                          Tree.MCJet_truth_K_PY / 1000.,
                          Tree.MCJet_truth_K_PZ / 1000.,
                          Tree.MCJet_truth_K_PE / 1000.);

        HFjet.SetPxPyPzE(Tree.MCJet_PX / 1000.,
                         Tree.MCJet_PY / 1000.,
                         Tree.MCJet_PZ / 1000.,
                         Tree.MCJet_PE / 1000.);

        HFmeson = mup + mum + Kmeson;
        Jpsi = mup + mum;
   
        meas_HFjet.SetPxPyPzE(Tree.MCJet_recojet_PX / 1000.,
                              Tree.MCJet_recojet_PY / 1000.,
                              Tree.MCJet_recojet_PZ / 1000.,
                              Tree.MCJet_recojet_PE / 1000.);
        
        meas_mup.SetPxPyPzE(Tree.MCJet_truth_mup_PX / 1000.,
                       Tree.MCJet_truth_mup_PY / 1000.,
                       Tree.MCJet_truth_mup_PZ / 1000.,
                       Tree.MCJet_truth_mup_PE / 1000.);
        
        meas_mum.SetPxPyPzE(Tree.MCJet_truth_mum_PX / 1000.,
                       Tree.MCJet_truth_mum_PY / 1000.,
                       Tree.MCJet_truth_mum_PZ / 1000.,
                       Tree.MCJet_truth_mum_PE / 1000.);
        
        meas_Kmeson.SetPxPyPzE(Tree.MCJet_truth_K_PX / 1000.,
                          Tree.MCJet_truth_K_PY / 1000.,
                          Tree.MCJet_truth_K_PZ / 1000.,
                          Tree.MCJet_truth_K_PE / 1000.);
        
        meas_HFmeson = meas_mup + meas_mum + meas_Kmeson;

        double HF_jet_dR = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
//        double HF_jet_dR = HFmeson.DeltaR(HFjet);
        // Uncommented
        double HF_jet_truedR = static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE);
//        double HF_jet_truedR = meas_HFmeson.DeltaR(meas_HFjet);

        // if(HF_jet_dR > 0.5) continue;

        //  if(HFjet.Eta() < etaMin || HFjet.Eta() > etaMax) cout<<HFjet.Eta()<<",";
        
        isSingle_tr_Bjet = false;
        if (Tree.MCJet_Dtr_nmcdtrs < 2 )
        {
            isSingle_tr_Bjet = true;
            Num_Single_tr_Bjet++;
        }
            
        isPhoton_tr_Bjet = false;
        if (Tree.MCJet_Dtr_nmcdtrs == 2 )
        {
            if (Tree.MCJet_Dtr_ID[0] == 22 || Tree.MCJet_Dtr_ID[1] == 22)
            {
                isPhoton_tr_Bjet = true;
                Num_Photon_tr_Bjet++;
            }
        }
        
        
        if (Tree.nPVs > 1) {
            cut_npvs++;
            continue;
        }

        if (HFjet.Pt() < 12.5) {
            cut_pt++;
            continue;
        }
       
        Hasbbbar = false;
//        GluonTag = false;
        if (Tree.hasb && Tree.hasbbar) {
            Hasbbbar = true; //
//            GluonTag = true;
        }
//
        
        ///// Experimenting with Stripping Line cuts //// //
//      if ( meas_HFjet.Pt() < 5.) continue;

        // if (HFjet.Eta() < etaMin || HFjet.Eta() > etaMax)
        // {
        //   cut_eta++;
        //   continue;
        // }
        //  if(Kmeson.Pt() < 0.25 || mup.Pt() < 0.25 || mum.Pt() < 0.25){
        //     continue;
        //  }

        //  if(HF_jet_dR > jetradius){
        //     cut_HFdR++;
        //     continue;
        //  }

        // jet_Nmcdtrs = recojetNdtrs;
        
        bool hasHFhadron = false;
        bool hasJpsi = false;
        bool isGluonJet = false;
        bool hasbquark = false;
        bool hasbbar = false;
        GluonTag = false;
        NumHFHads = 0;
        NumDtrRecoHF = 0;
        
        int quark_pdg = -999;

//    cout<< "||Event  " << ev  << " ||" <<endl;

        for (int dtrs0 = 0; dtrs0 < Tree.MCJet_Dtr_nmcdtrs; dtrs0++)
        {
          
            TLorentzVector dtr(Tree.MCJet_Dtr_PX[dtrs0] / 1000.,
                               Tree.MCJet_Dtr_PY[dtrs0] / 1000.,
                               Tree.MCJet_Dtr_PZ[dtrs0] / 1000.,
                               Tree.MCJet_Dtr_E[dtrs0] / 1000.);
              
            
//            if ( dtr.DeltaR(HFjet) > jetradius) continue;
            
            if (static_cast < TLorentzVector > (dtr).DeltaR(HFjet, kTRUE) > jetradius) {continue;}
            
            if (abs(Tree.MCJet_Dtr_ID[dtrs0]) == HF_pdgcode)
            {
//                if (Tree.eventNumber == 673310)
//                {
//                    cout << dtr.Pt() << endl;
//                }
                
                if (fabs(dtr.Px() - HFmeson.Px()) < 1e-2 && fabs(dtr.Py() - HFmeson.Py()) < 1e-2)
                {
                    NumHFHads++;
                    hasHFhadron = true;
                }
            }

            // cout<<Tree.MCJet_Dtr_ID[dtrs0]<<",";

            if (Tree.MCJet_Dtr_TopMotherID[dtrs0] == 5)
            {
                hasbquark = true;
            }
            if (Tree.MCJet_Dtr_TopMotherID[dtrs0] == -5)
            {
                hasbbar = true;
            }
            // jet_Nmcdtrs++;
      
        }

        // if(Tree.eventNumber == 673310) cout<<"after dtrs"<<endl;
        // cout<<HFjet.Pt()<<endl;
        
        /////       If Truth HF meson is not is not inside a truth HF jet, I dont care about such event... /// /
        if (static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE) > jetradius)
            continue;
//        if ( HFmeson.DeltaR(HFjet) > jetradius)
//            continue;
    
        /////    If the HF meson (from branch) is not the same as the truth Jet daughter, I dont care about such event ... ////
        if (!hasHFhadron)
            continue;
        
        // if(NumHFHads > 1) continue;

        if(hasbquark && hasbbar)
        {
            GluonTag = true;
        }
    
    /// Experimenting Gluon Jet Daughters ///
//      for (int i = 0; i <  Tree.MCJet_Dtr_nmcdtrs; i++)
//      {
//          if (GluonTag){
//              cout << "Gluon jet Dtrs: " <<  endl;
//              cout << Tree.MCJet_Dtr_ID[i] <<endl;
//          }
//      }
        
        hasRecoHF = false;
        
        int NumHFinRecoJet = 0;
        
        for (int dtrs0 = 0; dtrs0 < Tree.MCJet_recojet_nrecodtrs; dtrs0++)
        {
//            cout<< Tree.MCJet_recojet_Dtr_ID[dtrs0] << endl;
            
            TLorentzVector dtr(Tree.MCJet_recojet_Dtr_PX[dtrs0] / 1000.,
                               Tree.MCJet_recojet_Dtr_PY[dtrs0] / 1000.,
                               Tree.MCJet_recojet_Dtr_PZ[dtrs0] / 1000.,
                               Tree.MCJet_recojet_Dtr_E[dtrs0] / 1000.);

            if (dtr.E() < 0) {
                continue;
            }

            if (static_cast < TLorentzVector > (dtr).DeltaR(meas_HFjet, kTRUE) > jetradius) continue;
//            if ( dtr.DeltaR(meas_HFjet) > jetradius) continue;

            if (abs(Tree.MCJet_recojet_Dtr_ID[dtrs0]) == HF_pdgcode)
            {
                meas_HFmeson.SetPxPyPzE(dtr.Px(), dtr.Py(), dtr.Pz(), dtr.E());
                
                NumDtrRecoHF++;
                NumHFinRecoJet++;
                
                hasRecoHF = true;
                
                if (NumHFinRecoJet == 2){
                    cout<< "Found two +-521 in reco jet: " << Tree.MCJet_recojet_Dtr_ID[dtrs0] << endl;
                }
            }
           
        }

        //// If reconstructed HF meson (from reco Daughters) is not inside the reco jet, then the Reco HF jet end up without the HF meson inside //// 
        if (static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE) > jetradius) hasRecoHF = false;
//        if ( meas_HFmeson.DeltaR(meas_HFjet) > jetradius) hasRecoHF = false;

        if (hasRecoHF) {
            NumRecoHF++;
        }

        TVector3 HF_meson = HFmeson.Vect();
        TVector3 HF_jet = HFjet.Vect();
        TVector3 meas_HF_meson = meas_HFmeson.Vect();
        TVector3 meas_HF_jet = meas_HFjet.Vect();

        truth_z = (HF_meson.Dot(HF_jet) ) / (HF_jet.Mag2() );
        truth_jt = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
        truth_r = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
        
        h1_z_truth->Fill(truth_z);
        
        if(!Hasbbbar) {
            truth_z_b = (HF_meson.Dot(HF_jet) ) / (HF_jet.Mag2() );
            truth_jt_b = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
            truth_r_b = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
            
            h1_z_truth_b->Fill(truth_z_b);

        }

        meas_z = (meas_HF_meson.Dot(meas_HF_jet) ) / (meas_HF_jet.Mag2() );
        meas_jt = (meas_HF_jet.Cross(meas_HF_meson).Mag()) / (meas_HF_jet.Mag());
        meas_r =  static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE);

        // Below: Not Needed --- Just for curiosity //
        if (hasRecoHF) {
            meas_inJet_z = (meas_HF_meson.Dot(meas_HF_jet) ) / (meas_HF_jet.Mag2() );
            meas_inJet_jt = (meas_HF_jet.Cross(meas_HF_meson).Mag()) / (meas_HF_jet.Mag());
            meas_inJet_r = static_cast < TLorentzVector > (meas_HFmeson).DeltaR(meas_HFjet, kTRUE);
        }
        
        if(Hasbbbar){
            truth_zg = (HF_meson.Dot(HF_jet) ) / (HF_jet.Mag2() );
            truth_jtg = (HF_jet.Cross(HF_meson).Mag()) / (HF_jet.Mag());
            truth_rg = static_cast < TLorentzVector > (HFmeson).DeltaR(HFjet, kTRUE);
            
            h1_z_truth_g->Fill(truth_zg);
        }
        
        jet_pt_recotruthratio = meas_HFjet.Pt()/HFjet.Pt();
        HF_pt_recotruthratio = meas_HFmeson.Pt()/HFmeson.Pt();

        jet_pt = HFjet.Pt();
        jet_eta = HFjet.Eta();
        jet_rap = HFjet.Rapidity();
        meas_jet_pt = meas_HFjet.Pt();
        meas_jet_eta = meas_HFjet.Eta();
        meas_jet_rap = meas_HFjet.Rapidity();

        jet_px = HFjet.Px();
        jet_py = HFjet.Py();
        jet_pz = HFjet.Pz();
        jet_e = HFjet.E();

        meas_jet_px = meas_HFjet.Px();
        meas_jet_py = meas_HFjet.Py();
        meas_jet_pz = meas_HFjet.Pz();
        meas_jet_e = meas_HFjet.E();

        mum_px = mum.Px();
        mum_py = mum.Py();
        mum_pz = mum.Pz();
        mum_e = mum.E();
        mup_px = mup.Px();
        mup_py = mup.Py();
        mup_pz = mup.Pz();
        mup_e = mup.E();
        K_px = Kmeson.Px();
        K_py = Kmeson.Py();
        K_pz = Kmeson.Pz();
        K_e = Kmeson.E();

        HF_px = HFmeson.Px();
        HF_py = HFmeson.Py();
        HF_pz = HFmeson.Pz();
        HF_e = HFmeson.E();
        HF_pt = HFmeson.Pt();

        meas_HF_pt = meas_HFmeson.Pt();
        meas_HF_px = meas_HFmeson.Px();
        meas_HF_py = meas_HFmeson.Py();
        meas_HF_pz = meas_HFmeson.Pz();
        meas_HF_e = meas_HFmeson.E();

    meas_mum_px = meas_mum.Px();
    meas_mum_py = meas_mum.Py();
    meas_mum_pz = meas_mum.Pz();
    meas_mum_e = meas_mum.E();
    meas_mup_px = meas_mup.Px();
    meas_mup_py = meas_mup.Py();
    meas_mup_pz = meas_mup.Pz();
    meas_mup_e = meas_mup.E();
    meas_K_px = meas_Kmeson.Px();
    meas_K_py = meas_Kmeson.Py();
    meas_K_pz = meas_Kmeson.Pz();
    meas_K_e = meas_Kmeson.E();
        
        nTracks = Tree.nTracks; 

//        if (last_eventNum == Tree.eventNumber) {
//            continue;
//        }

        last_eventNum = Tree.eventNumber;
        eventNumber = Tree.eventNumber;

//        events++;

        BTree->Fill();
    }
    
    TLatex *text[1000];
    for (int i = 0; i < 1000; i++)
    {
      text[i] = new TLatex();
      text[i]->SetNDC(kTRUE);
      text[i]->SetTextSize(0.06);
    }
    
    TLatex Tl;
    Tl.SetNDC(kTRUE);
    Tl.SetTextSize(0.04);
    //
    Int_t lhcbFont = 132; // Old LHCb style: 62;
    // Line thickness
    Double_t lhcbWidth = 2.00; // Old LHCb style: 3.00;
    // Text size
    Double_t lhcbTSize = 0.06;
      Double_t lhcbTSize1    = 0.02;
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
      lhcbLatex2->SetTextSize(lhcbTSize1);
      lhcbLatex2->SetTextAlign(12);
      lhcbLatex2->SetTextAngle(90);

    // gROOT->SetStyle("Plain");
    gStyle->SetCanvasDefH(1414);
    gStyle->SetCanvasDefW(1000);
    gStyle->SetPadBottomMargin(0.08);
    gStyle->SetPadTopMargin(0.08);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.12);
    gStyle->SetTitleStyle(0);
    gStyle->SetStatStyle(0);
    // gStyle->SetLineWidth(3);
    gStyle->SetOptStat(0);
    
    TString plotextension = TString("../../plots/BjetsMC/");
    auto* c1 = new TCanvas();
    
    NormalizeHist(h1_z_truth);
    h1_z_truth->SetMarkerColor(kBlack);
    h1_z_truth->SetMarkerStyle(21);
    h1_z_truth->Draw("A P same");
    h1_z_truth->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_truth->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_truth->GetXaxis()->SetTitle("z");
    
    c1->Modified();
    c1->Update();
    gPad->Update();

    NormalizeHist(h1_z_truth_b);
    h1_z_truth_b->SetMarkerColor(kRed);
    h1_z_truth_b->SetMarkerStyle(21);
    h1_z_truth_b->SetMarkerSize(0.7);
    h1_z_truth_b->Draw("A P same");
    h1_z_truth_b->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_truth_b->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_truth_b->GetXaxis()->SetTitle("z");
    
    c1->Modified();
    c1->Update();
    gPad->Update();
    
//    NormalizeHist(h1_z_truth_g);
    h1_z_truth_g->Scale(0.23*1.0 /( h1_z_truth_g->Integral() ), "width");
    h1_z_truth_g->SetMarkerColor(kBlue);
    h1_z_truth_g->SetMarkerStyle(21);
    h1_z_truth_g->Draw("AP same");
    h1_z_truth_g->GetXaxis()->SetRangeUser(0.0, 1.1);
    h1_z_truth_g->GetYaxis()->SetRangeUser(0.0, 3.5);
    h1_z_truth_g->GetXaxis()->SetTitle("z");

    c1->Modified();
    c1->Update();
    gPad->Update();
    lhcbLatex1->SetNDC();
    
    auto* leg3 = new TLegend(0.25, 0.6, 0.35, 0.75);
    gStyle->SetLegendTextSize(0.04);
    leg3->SetTextFont(lhcbFont);
    leg3->SetBorderSize(0);
    leg3->AddEntry(h1_z_truth, " Inclusive ", "LPE");
    leg3->AddEntry(h1_z_truth_b, " b-quark ", "LPE");
    leg3->AddEntry(h1_z_truth_g, " gluons ", "LPE");
    leg3->Draw("same");

    gPad->Modified();
    gPad->Update(); // Update the pad
    c1->Modified();
    c1->Update();
    c1->Draw();
    c1->SaveAs(plotextension + str_Mag + "_zb_zg_z.pdf");
    

    cout << "Total number of events processed = " << events << endl;
    cout << "NumRecoHF = " << NumRecoHF << endl;
    cout << "NumHFHads = " << NumHFHads << endl;
    cout << "Num Single Bjets = " << Num_Single_tr_Bjet << endl;
    cout << "Num Photon + B jets = " << Num_Photon_tr_Bjet << endl;

    cout << "Events blocked: " << endl;
    cout << "npvs = " << cut_npvs << endl;
    cout << "jetpt = " << cut_pt << endl;
    cout << "jeteta = " << cut_eta << endl;
    cout << "Dinjet = " << cut_HFdR << endl;
    // cout<<"hasHF = "<< cut_hasHF<<endl;

    f.Write();
    f.Close();
}

//
