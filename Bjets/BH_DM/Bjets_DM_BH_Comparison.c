
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
//#include "omp.h"

using namespace std;

void Bjets_DM_BH_Comparison()
{
    TFile freadDM("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Bjets_DM_Variable_Tree_409283.root", "READ");
    TTree *Bjet_tree_DM = (TTree *)freadDM.Get("Bjet");
    TFile freadBH("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Bjets_BH_Variable_Tree_841656.root", "READ");
    TTree *Bjet_tree_BH = (TTree *)freadBH.Get("Bjet");
 
    int NumEvtsDM = Bjet_tree_DM->GetEntries();
    int NumEvtsBH = Bjet_tree_BH->GetEntries();
    
    TFile f("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_DM_BH_Comparison.root", "RECREATE");
    
    double jet_pt_DM, jet_eta_DM;
    double jet_px_DM, jet_py_DM, jet_pz_DM, jet_e_DM;
    
    double jet_pt_BH, jet_eta_BH;
    double jet_px_BH, jet_py_BH, jet_pz_BH, jet_e_BH;

    double mum_px_DM, mum_py_DM, mum_pz_DM, mum_e_DM;
    double mup_px_DM, mup_py_DM, mup_pz_DM, mup_e_DM;
    double K_px_DM, K_py_DM, K_pz_DM, K_e_DM;

    double mum_px_BH, mum_py_BH, mum_pz_BH, mum_e_BH;
    double mup_px_BH, mup_py_BH, mup_pz_BH, mup_e_BH;
    double K_px_BH, K_py_BH, K_pz_BH, K_e_BH;
    
    double B_px_DM, B_py_DM, B_pz_DM, B_e_DM;
    double B_m_DM, B_pt_DM, B_eta_DM, B_phi_DM;
    
    double B_px_BH, B_py_BH, B_pz_BH, B_e_BH;
    double B_m_BH, B_pt_BH, B_eta_BH, B_phi_BH;

    int nPV_BH, Jet_Dtr_ndtr_BH, Jet_Dtr_ndtr_DM ;

//    double bPhi, bM;
//    double jPhi, jP;
//    double bz, bJt, bR;

    Bjet_tree_DM->SetBranchAddress("jet_pt", &jet_pt_DM);
    Bjet_tree_DM->SetBranchAddress("jet_px", &jet_px_DM);
    Bjet_tree_DM->SetBranchAddress("jet_py", &jet_py_DM);
    Bjet_tree_DM->SetBranchAddress("jet_pz", &jet_pz_DM);
    Bjet_tree_DM->SetBranchAddress("jet_e", &jet_e_DM);
    Bjet_tree_DM->SetBranchAddress("jet_eta", &jet_eta_DM);
    
    Bjet_tree_BH->SetBranchAddress("jet_pt", &jet_pt_BH);
    Bjet_tree_BH->SetBranchAddress("jet_px", &jet_px_BH);
    Bjet_tree_BH->SetBranchAddress("jet_py", &jet_py_BH);
    Bjet_tree_BH->SetBranchAddress("jet_pz", &jet_pz_BH);
    Bjet_tree_BH->SetBranchAddress("jet_e", &jet_e_BH);
    Bjet_tree_BH->SetBranchAddress("jet_eta", &jet_eta_BH);
   
    Bjet_tree_DM->SetBranchAddress("mum_px", &mum_px_DM);
    Bjet_tree_DM->SetBranchAddress("mum_py", &mum_py_DM);
    Bjet_tree_DM->SetBranchAddress("mum_pz", &mum_pz_DM);
    Bjet_tree_DM->SetBranchAddress("mum_e", &mum_e_DM);
    
    Bjet_tree_BH->SetBranchAddress("mum_px", &mum_px_BH);
    Bjet_tree_BH->SetBranchAddress("mum_py", &mum_py_BH);
    Bjet_tree_BH->SetBranchAddress("mum_pz", &mum_pz_BH);
    Bjet_tree_BH->SetBranchAddress("mum_e", &mum_e_BH);

    Bjet_tree_DM->SetBranchAddress("mup_px", &mup_px_DM);
    Bjet_tree_DM->SetBranchAddress("mup_py", &mup_py_DM);
    Bjet_tree_DM->SetBranchAddress("mup_pz", &mup_pz_DM);
    Bjet_tree_DM->SetBranchAddress("mup_e", &mup_e_DM);
    
    Bjet_tree_BH->SetBranchAddress("mup_px", &mup_px_BH);
    Bjet_tree_BH->SetBranchAddress("mup_py", &mup_py_BH);
    Bjet_tree_BH->SetBranchAddress("mup_pz", &mup_pz_BH);
    Bjet_tree_BH->SetBranchAddress("mup_e", &mup_e_BH);

    Bjet_tree_DM->SetBranchAddress("K_px", &K_px_DM);
    Bjet_tree_DM->SetBranchAddress("K_py", &K_py_DM);
    Bjet_tree_DM->SetBranchAddress("K_pz", &K_pz_DM);
    Bjet_tree_DM->SetBranchAddress("K_e", &K_e_DM);
    
    Bjet_tree_BH->SetBranchAddress("K_px", &K_px_BH);
    Bjet_tree_BH->SetBranchAddress("K_py", &K_py_BH);
    Bjet_tree_BH->SetBranchAddress("K_pz", &K_pz_BH);
    Bjet_tree_BH->SetBranchAddress("K_e", &K_e_BH);

    Bjet_tree_DM->SetBranchAddress("B_px", &B_px_DM);
    Bjet_tree_DM->SetBranchAddress("B_py", &B_py_DM);
    Bjet_tree_DM->SetBranchAddress("B_pz", &B_pz_DM);
    Bjet_tree_DM->SetBranchAddress("B_e", &B_e_DM);
    Bjet_tree_DM->SetBranchAddress("B_pt", &B_pt_DM);
    Bjet_tree_DM->SetBranchAddress("B_m", &B_m_DM);
    Bjet_tree_DM->SetBranchAddress("B_eta", &B_eta_DM);
    Bjet_tree_DM->SetBranchAddress("B_phi", &B_phi_DM);
    
     Bjet_tree_BH->Branch("B_px", &B_px_BH);
     Bjet_tree_BH->Branch("B_py", &B_py_BH);
     Bjet_tree_BH->Branch("B_pz", &B_pz_BH);
     Bjet_tree_BH->Branch("B_e", &B_e_BH);
     Bjet_tree_BH->Branch("B_pt", &B_pt_BH);
     Bjet_tree_BH->Branch("B_m", &B_m_BH);
     Bjet_tree_BH->Branch("B_eta", &B_eta_BH);
     Bjet_tree_BH->Branch("B_phi", &B_phi_BH);
    
    Bjet_tree_DM->SetBranchAddress("Jet_Dtr_ndtr", &Jet_Dtr_ndtr_DM);
    Bjet_tree_BH->SetBranchAddress("Jet_Dtr_ndtr", &Jet_Dtr_ndtr_BH);
    
    long eventN_DM, eventN_BH;
    
    Bjet_tree_DM->SetBranchAddress("eventN", &eventN_DM);
    Bjet_tree_BH->SetBranchAddress("eventN", &eventN_BH);
    
    TH1F *mumptDMH = new TH1F("mumptDMH", ";#it{p_{T} (#mu^{-}) DiMuon ;", 150, 0.0, 200.0);
    TH1F *mupptDMH = new TH1F("mupptDMH", ";#it{p_{T} (#mu^{+}) DiMuon;", 150, 0.0, 200.0);
    
    TH1F *mumpDMH = new TH1F("mumpDMH", ";|#it{p}| (#mu^{-}) DiMuon;", 150, 0.0, 3000.0);
    TH1F *muppDMH = new TH1F("muppDMH", ";|#it{p}| (#mu^{+}) DiMuon;", 150, 0.0, 3000.0);
    
    TH1F *mumptBHH = new TH1F("mumptBHH", ";#it{p_{T} (#mu^{-}) BHadron;", 150, 0.0, 200.0);
    TH1F *mupptBHH = new TH1F("mupptBHH", ";#it{p_{T} (#mu^{+}) BHadron;", 150, 0.0, 200.0);
    
    TH1F *mumpBHH = new TH1F("mumpBHH", ";|#it{p}| (#mu^{-}) BHadron;", 150, 0.0, 3000.0);
    TH1F *muppBHH = new TH1F("muppBHH", ";|#it{p}| (#mu^{+}) BHadron;", 150, 0.0, 3000.0);
    
    TH1F *jetpDMH = new TH1F("jetpDMH", ";|#it{p}| (jet) DiMuon;", 150, 0.0, 3000.0);
    TH1F *jetpBHH = new TH1F("jetpBHH", ";|#it{p}| (jet) BHadron;", 150, 0.0, 3000.0);
    
    TH1F *KaonpBHH = new TH1F("KaonpBHH", ";|#it{p}| (#it{K}) BHadron;", 150, 0.0, 3000.0);
    TH1F *KaonptBHH = new TH1F("KaonptBHH", ";#it{p_T} (#it{K}) BHadron;", 150, 0.0, 200.0);
    
    TH1F *KaonpDMH = new TH1F("KaonpDMH", ";|#it{p}| (#it{K}) DiMuon;", 150, 0.0, 3000.0);
    TH1F *KaonptDMH = new TH1F("KaonptDMH", ";#it{p_T} (#it{K}) DiMuon;", 150, 0.0, 200.0);
    
    TH1F *HFpDMH = new TH1F("HFpDMH", ";|#it{p}| (#it{B^{#pm}}) DiMuon;", 150, 0.0, 3000.0);
    TH1F *HFptDMH = new TH1F("HFptDMH", ";#it{p_T} (#it{B^{#pm}}) DiMuon;", 150, 0.0, 200.0);
    
    TH1F *HFpBHH = new TH1F("HFpBHH", ";|#it{p}| (#it{B^{#pm}}) BHadron;", 150, 0.0, 3000.0);
    TH1F *HFptBHH = new TH1F("HFptBHH", ";#it{p_T} (#it{B^{#pm}}) BHadron;", 150, 0.0, 200.0);
    
//    TH2F *mum2D = new TH2F("")
    
    int Stream_same =0;
    
    cout << "Total number of DM events: " << NumEvtsDM << endl;
    cout << "Total number of BH events: " << NumEvtsBH << endl;
    
    int mu_p_diff = 0;
    
    for (int i = 0; i< NumEvtsDM ; ++i )
    {
        Bjet_tree_DM->GetEntry(i);
        
        
        for (int j = 0; j < NumEvtsBH; ++j )
        {
            Bjet_tree_BH->GetEntry(j);
            
            if ( eventN_DM == eventN_BH )
            {
               
                Stream_same++;
//
//                cout << " In Composite event " <<  i << " " << j << " same events found: " << Stream_same << endl;
                
                if (i % 100 == 0) {
                    cout << "processing DM entry : " <<  i << endl;
                }

                if (j % 100 == 0) {
                    cout << "processing BH entry : " << j  << endl;
                }
                

                TLorentzVector jet4P_BH, mup4P_BH, mum4P_BH, Kmeson4P_BH, HFmeson_BH;
                TLorentzVector jet4P_DM, mup4P_DM, mum4P_DM, Kmeson4P_DM, HFmeson_DM;
                
                jet4P_DM.SetPxPyPzE( jet_px_DM, jet_py_DM, jet_pz_DM, jet_e_DM);
                mup4P_DM.SetPxPyPzE(mup_px_DM, mup_py_DM, mup_pz_DM, mup_e_DM);
                mum4P_DM.SetPxPyPzE( mum_px_DM, mum_py_DM, mum_pz_DM, mum_e_DM);
                Kmeson4P_DM.SetPxPyPzE(K_px_DM, K_py_DM, K_pz_DM, K_e_DM);
                HFmeson_DM = mum4P_DM + mup4P_DM + Kmeson4P_DM;
                
                // BHadron Stream Particles 4-Vectors
                jet4P_BH.SetPxPyPzE(jet_px_BH, jet_py_BH, jet_pz_BH, jet_e_BH);
                mup4P_BH.SetPxPyPzE(mup_px_BH, mup_py_BH, mup_pz_BH, mup_e_BH);
                mum4P_BH.SetPxPyPzE(mum_px_BH, mum_py_BH, mum_pz_BH, mum_e_BH);
                Kmeson4P_BH.SetPxPyPzE(K_px_BH, K_py_BH, K_pz_BH, K_e_BH);
                HFmeson_BH = mum4P_BH + mup4P_BH + Kmeson4P_BH;
                
//                cout<< " BH B |P| " << " " << HFmeson_BH.P() << endl;
//                cout<< " DM B |P| " << " " << HFmeson_DM.P() << endl;
//
//                cout<< " BH muons Pt " << " " <<  mum4P_BH.Pt()<< endl;
//                cout<< " DM muons Pt " << " " <<  mum4P_DM.Pt() << endl;
                
                mumptDMH->Fill( mum4P_DM.Pt() );
                mupptDMH->Fill( mup4P_DM.Pt() );

                mumpDMH->Fill( mum4P_DM.P() );
                muppDMH->Fill( mup4P_DM.P() );

                mumptBHH->Fill( mum4P_BH.Pt() );
                mupptBHH->Fill( mup4P_BH.Pt() );

                mumpBHH->Fill( mum4P_BH.P() );
                muppBHH->Fill( mup4P_BH.P() );
                
                jetpDMH->Fill( jet4P_DM.P() );
                jetpBHH->Fill( jet4P_BH.P() );
                
                KaonpBHH->Fill( Kmeson4P_BH.P() );
                KaonptBHH->Fill( Kmeson4P_BH.Pt() ) ;
                
                KaonpDMH->Fill( Kmeson4P_DM.P() ) ;
                KaonptDMH->Fill( Kmeson4P_DM.Pt() ) ;
                
                HFpDMH->Fill( HFmeson_DM.P()  ) ;
                HFptDMH->Fill( HFmeson_DM.Pt() ) ;
                
                HFpBHH->Fill( HFmeson_BH.P() ) ;
                HFptBHH->Fill( HFmeson_BH.Pt() ) ;
                
                break;
            }
        }
        
    }
   
    f.Write();
    f.Close();

}
