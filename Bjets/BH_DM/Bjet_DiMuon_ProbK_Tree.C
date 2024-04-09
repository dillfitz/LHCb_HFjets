#define Bjet_DiMuon_ProbK_Tree_cxx
#include "Bjet_DiMuon_ProbK_Tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Bjet_DiMuon_ProbK_Tree::Loop()
{
    
    TLorentzVector jet4P;
    TLorentzVector mup4P;
    TLorentzVector mum4P;
    TLorentzVector Kmeson4P;
    TLorentzVector HFmeson;
    
    int nentries = fChain->GetEntries();
    //int nentries = 100000;
    TString outfileName = Form("BJet_DiMuon_ProbK_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");
    
    TH1F *ProbIDKasK = new TH1F("ProbIDKasK ", "Probability (ID K as K)", 200, 0.0, 1.01);
    TH1F *ProbIDKaspi = new TH1F("ProbIDKaspi ", "Probability(ID K as #pi)", 200, 0.0, 1.01);
    
    TH1F *ProbIDKasK2030 = new TH1F("ProbIDKasK2030 ", "Probability (ID K as K) in pt: 20-30", 175, 0.0, 1.01);
    TH1F *ProbIDKaspi2030 = new TH1F("ProbIDKaspi2030 ", "Probability(ID K as #pi) in pt: 20-30", 175, 0.0, 1.01);
    
    TH1F *ProbIDKasK3050 = new TH1F("ProbIDKasK3050 ", "Probability (ID K as K) in pt: 30-35", 175, 0.0, 1.01);
    TH1F *ProbIDKaspi3050 = new TH1F("ProbIDKaspi3050 ", "Probability(ID K as #pi) in pt: 30-50", 175, 0.0, 1.01);
    
    TH1F *ProbIDKasK50100 = new TH1F("ProbIDKasK50100 ", "Probability (ID K as K) in pt: 50-100", 175, 0.0, 1.01);
    TH1F *ProbIDKaspi50100 = new TH1F("ProbIDKaspi50100 ", "Probability(ID K as #pi) in pt: 50-100", 175, 0.0, 1.01);
    
    
//   In a ROOT session, you can do:
//      root> .L Bjet_DiMuon_ProbK_Tree.C
//      root> Bjet_DiMuon_ProbK_Tree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

    if (fChain == 0) return;
     
     cout<<nentries<<endl;
     
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        if (jentry%100000==0)
            cout << "processing entry : " << jentry << endl;
        
        nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;
        
        if ((Jet_PT/1000.) < (20.) ) {continue;}
        if ((Jet_Eta)<2.5 || Jet_Eta>4.0) {continue;}
        
        //Only Jets with 2 constituents or more
        if ( Jet_Dtr_nrecodtr<(2) )  {continue;}
        //if ( Jet_Dtr_nrecodtr<(2) || Jet_Dtr_nrecodtr>(5) )  {continue;}
        
        //Discarding 2-constituents jets with one of them being a photon
        if (Jet_Dtr_nrecodtr==2)
        { if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) ) continue;}
        
//        double leading_pT=0;
//        double cand_jetpt, testjet_phi;
//        int n_maxpT_cand, n_maxpT_entry;
//
//        if( totCandidates > 1)
//        {
//            for(int icand = 0; icand < totCandidates; icand++)
//            {
//                GetEntry(jentry+icand-nCandidate);
//
//                jet4P.SetPxPyPzE(Jet_PX/1000., Jet_PY/1000., Jet_PZ/1000., Jet_PE/1000.);
//                mup4P.SetPxPyPzE(mup_PX/1000., mup_PY/1000., mup_PZ/1000., mup_PE/1000.);
//                mum4P.SetPxPyPzE( mum_PX/1000., mum_PY/1000., mum_PZ/1000., mum_PE/1000.);
//                Kmeson4P.SetPxPyPzE(K_PX/1000., K_PY/1000., K_PZ/1000., K_PE/1000.);
//                HFmeson = mup4P + mum4P + Kmeson4P;
//
//                if(HFmeson.DeltaR(jet4P) < 0.5) continue;  //<0.5 for b-jets
//
//                if ((Jet_PT/1000.) < (15.) ) {continue;}
//
//                if ((Jet_Eta)<2.5 || Jet_Eta>4.0) {continue;}
//
//                cand_jetpt = jet4P.Pt();
//                if(cand_jetpt > leading_pT)
//                {
//                    leading_pT = cand_jetpt;
//                    n_maxpT_cand = nCandidate;
//                    n_maxpT_entry = jentry+icand-nCandidate;
//                }
//            }
//            GetEntry(n_maxpT_entry);
//            testjet_phi = jet4P.Phi();
//        }
//        GetEntry(jentry);
//
//        jet4P.SetPxPyPzE(Jet_PX/1000., Jet_PY/1000., Jet_PZ/1000., Jet_PE/1000.);
//        mup4P.SetPxPyPzE(mup_PX/1000., mup_PY/1000., mup_PZ/1000., mup_PE/1000.);
//        mum4P.SetPxPyPzE( mum_PX/1000., mum_PY/1000., mum_PZ/1000., mum_PE/1000.);
//        Kmeson4P.SetPxPyPzE(K_PX/1000., K_PY/1000., K_PZ/1000., K_PE/1000.);
//        HFmeson = mup4P + mum4P + Kmeson4P;
//
//        if(totCandidates > 1)
//        {
//            if(checkphi(fabs(checkphi(HFmeson.Phi()) - checkphi(testjet_phi))) < 0.95 * TMath::Pi() ) continue; //<0.95*pi for b-jets
//
//        }
        
        if ((Jet_PT/1000) > (20))
        {
            ProbIDKasK->Fill(K_ProbNNk);
            ProbIDKaspi->Fill(K_ProbNNpi);
        }
        if ( (Jet_PT/1000) > (20) && (Jet_PT/1000) < (30))
        {
            ProbIDKasK2030->Fill(K_ProbNNk);
            ProbIDKaspi2030->Fill(K_ProbNNpi);
        }
        
        if ( (Jet_PT/1000) > (30) && (Jet_PT/1000) < (50))
        {
            ProbIDKasK3050->Fill(K_ProbNNk);
            ProbIDKaspi3050->Fill(K_ProbNNpi);
        }
        
        if ( (Jet_PT/1000) > (50) && (Jet_PT/1000) < (100))
        {
            ProbIDKasK50100->Fill(K_ProbNNk);
            ProbIDKaspi50100->Fill(K_ProbNNpi);
        }
    }
    
outfile->Write();
outfile->Close();
    
}
