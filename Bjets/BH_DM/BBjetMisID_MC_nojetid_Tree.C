#define BBjetMisID_MC_nojetid_Tree_cxx
#include "BBjetMisID_MC_nojetid_Tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include "TH1.h"
#include "TFile.h"
#include <vector>
#include <cmath>
#include <TMath.h>

void BBjetMisID_MC_nojetid_Tree::Loop()
{
    double bM;
    double pionMass = 0.13957039;
    double kaonMass = 0.493677;
    
    TLorentzVector HFmeson, HFjet, mum, mup, pion, Jpsi, Bfromjet;
    
    int nentries = fChain->GetEntries();
    
    TString outfileName = Form("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/BBjetMisID_MC_BH_nojetid_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");
    
    TH1F *bMH = new TH1F("m", ";m_{#mu#mu K^{#pm} (GeV/c^{2});", 150, 5.0, 5.7);
    TH1F *bJetPtH = new TH1F("pt", ";p_{T} (GeV/c);", 150, 20., 200.);
    TH1F *bMH_20_30 = new TH1F("m_20_30", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,120, 5.0, 5.7);
    TH1F *bMH_30_50 = new TH1F("m_30_50", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,110, 5.0, 5.7);
    TH1F *bMH_50_100 = new TH1F("m_50_100", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,20, 5.0, 5.7);
    
    
   if (fChain == 0) return;

   cout<<nentries<<endl;
    
   //Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
    
//   int Jpsi_constraint = 0;
    
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
       if (jentry%100000==0)
           cout << "processing entry : " << jentry << endl;
       
       //    Long64_t ientry = LoadTree(jentry);
       //    if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       //    if (Cut(ientry) < 0) continue;
       
       TLorentzVector HFmeson, HFjet, mum, mup, pion, Jpsi, jet4P, Bfromjet;
       
       jet4P.SetPxPyPzE(Jet_PX / 1000., Jet_PY / 1000., Jet_PZ / 1000., Jet_PE / 1000.);
       mup.SetPxPyPzE(mup_PX/1000., mup_PY/1000., mup_PZ/1000., mup_PE/1000.);
       mum.SetPxPyPzE(mum_PX/1000., mum_PY/1000., mum_PZ/1000., mum_PE/1000.);
       pion.SetPxPyPzE(pi_PX/1000., pi_PY/1000., pi_PZ/1000., sqrt(pi_PE/1000.*pi_PE/1000. - pionMass*pionMass + kaonMass*kaonMass));
       
       ///////  For DiMuon Data with J/Psi Constraint mass
       double JpsiMass = 3096.916/1000. ;
       double Jpsipx2 = (mup_PX/1000. + mum_PX/1000.)*(mup_PX/1000. + mum_PX/1000.);
       double Jpsipy2 = (mup_PY/1000. + mum_PY/1000.)*(mup_PY/1000. + mum_PY/1000.);
       double Jpsipz2 = (mup_PZ/1000. + mum_PZ/1000.)*(mup_PZ/1000. + mum_PZ/1000.);
       
       Jpsi.SetPxPyPzE( mup_PX/1000. + mum_PX/1000. , mup_PY/1000. + mum_PY/1000. , mup_PZ/1000. + mum_PZ/1000. , sqrt( JpsiMass*JpsiMass + ( Jpsipx2 + Jpsipy2 + Jpsipz2 ) ) ) ;
       
//       HFmeson = Jpsi + pion;

       HFmeson = mup + mum + pion;
       
       TVector3 jet3vec(Jet_PX/1000., Jet_PY/1000., Jet_PZ/1000.);
       
       double HF_jet_dR = HFmeson.DeltaR(jet4P);
       
       /////// Jet pt cut, 20 GeV < pt < 150 GeV as in LHCb literature for heavy flavor//
       if ( nPVs > 1 ) {continue;}
       
       if ( (Jet_PT/1000.) < (20.) ) {continue;}
       
       // Pseudorapidity cut
       if ( (Jet_Eta)<2.5 || Jet_Eta>4.0 ) {continue;}
       
       ///////  Getting Rid of HF mesons outide of the Jet
       if (HF_jet_dR > 0.5) {
           continue;
       }
       
       /////// Only Jets with 2 constituents or more
       if ( Jet_Dtr_nrecodtr<(2) )  {continue;}
       
       ////// Discarding 2-constituents jets when one of them is a photon
       if (Jet_Dtr_nrecodtr==2)
       {
           if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) )
           {
               continue;
               
           }
       }
       
       //////  Discarding artificially reconstructed HF's
       int HF_artificial = 0;
       for (int i =0; i<Jet_Dtr_nrecodtr; i++)
       {
           if( abs(Jet_Dtr_ID[i])==521 )
           {
               HF_artificial ++;
           }
       }

       
       if (HF_artificial > 1)
       {
           continue;
       }
       

       //////  Filling Variables
       bM = HFmeson.M();
               
       if (bM >= 5.0 && bM <= 5.7)
       {
           bMH->Fill(bM);
           bJetPtH->Fill(Jet_PT/1000.);
           
           if (Jet_PT/1000. > 20.0 && Jet_PT/1000. < 30.0)
           {
               bMH_20_30->Fill(bM);
               
           }
           
           if (Jet_PT/1000. > 30.0 && Jet_PT/1000. < 50.0)
           {
               bMH_30_50->Fill(bM);
               
           }
           
           if (Jet_PT/1000. > 50.0 && Jet_PT/1000. < 100.0)
           {
               bMH_50_100->Fill(bM);
           }
           
       }
       
   }
//    cout<< "Not in Jpsi narrow M:  " << Jpsi_constraint << endl;
    
outfile->Write();
outfile->Close();
    
}
