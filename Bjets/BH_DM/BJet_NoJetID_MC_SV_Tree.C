#define BJet_NoJetID_MC_SV_Tree_cxx
#include "BJet_NoJetID_MC_SV_Tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TH1.h"
#include "TFile.h"
#include <vector>
#include <cmath>
#include <TMath.h>
#include <THStack.h>

void BJet_NoJetID_MC_SV_Tree::Loop()
{
    double bPx, bPy, bPz, bE, bPhi;
    double bz, bJt, bR, bM, jP, jPhi, DiffR;

    TLorentzVector jet4P;
    TLorentzVector mup4P;
    TLorentzVector mum4P;
    TLorentzVector Kmeson4P;
    TLorentzVector HFmeson;

    int nentries = fChain->GetEntries();
    //int nentries = 100000;
    TString outfileName = Form("BJet_NoJetID_MC_SV_%d.root", nentries);
    TFile *outfile = new TFile(outfileName, "RECREATE");

    //Integrated Histograms
    TH1F *bMH = new TH1F("m", ";m_{#mu#mu K^{#pm} (GeV/c^{2});", 175, 5.0, 5.7);
    TH1F *zH = new TH1F("z",";z;", 175, 0.0, 1.1);
    TH1F *jtH = new TH1F("jt",";j_{T} (GeV/c);", 175, 0., 10.);   //good shapes with 200 bins for 1 M for z and jt
    TH1F *rH = new TH1F("r",";r;", 150, 0., 7.);
    TH1F *bJetPtH = new TH1F("pt", ";p_{T} (GeV/c);", 175, 20., 200.);
    TH2F *jPH = new TH2F("Pvspt", ";p_{T};|P_{jet}|", 175, 15., 200., 175, 0., 3000.);
    TH2F *jtzH = new TH2F("Fzjt", ";#it{z}; j_{T}" , 175, 0.0, 1.1, 175, 0., 10.);
    TH2F *zRH = new TH2F("z_R", ";#it{z}; r" , 175, 0.0, 1.1, 175, 0., 7.);


    //Pt Binned Histograms
    //20<pt<30 GeV/c
    TH1F *bMH_20_30 = new TH1F("m_20_30", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,175, 5.0, 5.7);
    TH1F *zH_20_30 = new TH1F("z_20_30", ";D_{p}^{B^{#pm}} (z);" , 120, 0.0, 1.1);
    TH1F *zH_0_500p = new TH1F("z_0_500p", ";D_{p}^{B^{#pm}} (z);" , 120, 0.0, 1.1);
    TH1F *jtH_20_30 = new TH1F("jt_20_30", ";D_{p}^{B^{#pm}} (j_T);", 150, 0., 10.);
    TH1F *rH_20_30 = new TH1F("r_20_30", ";r;", 150, 0., 7.);
    TH2F *jtzH_20_30 = new TH2F("jt_z_20_30", ";#it{z}; j_{T}", 120, 0.0, 1.1, 120, 0., 10.);
    TH2F *zRH_20_30 = new TH2F("z_r_20_30", ";#it{z}; r", 120, 0.0, 1.1, 120, 0., 7.);

    //30<pt<50 GeV/c
    TH1F *bMH_30_50 = new TH1F("m_30_50", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,175, 5.0, 5.7);
    TH1F *zH_30_50 = new TH1F("z_30_50", ";D_{p}^{B^{#pm}} (z);" , 100, 0.0, 1.1);
    TH1F *zH_500_1000p = new TH1F("z_500_1000p", ";D_{p}^{B^{#pm}} (z);" , 100, 0.0, 1.1);
    TH1F *jtH_30_50 = new TH1F("jt_30_50", ";D_{p}^{B^{#pm}} (j_T);", 100, 0., 10.);
    TH1F *rH_30_50 = new TH1F("r_30_50", ";r;", 100, 0., 7.);
    TH2F *jtzH_30_50 = new TH2F("jt_z_30_50", ";#it{z}; j_{T}", 100, 0.0, 1.1, 100, 0., 10.);
    TH2F *zRH_30_50 = new TH2F("z_r_30_50", ";#it{z}; r", 120, 0.0, 1.1, 120, 0., 7.);

    //50<pt<100 GeV/c
    TH1F *bMH_50_100 = new TH1F("m_50_100", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,175, 5.0, 5.7);
    TH1F *zH_50_100 = new TH1F("z_50_100", ";D_{p}^{B^{#pm}} (z);" , 50, 0.0, 1.1);
    TH1F *zH_1000_1500p = new TH1F("z_1000_1500p", ";D_{p}^{B^{#pm}} (z);" , 50, 0.0, 1.1);
    TH1F *jtH_50_100 = new TH1F("jt_50_100", ";D_{p}^{B^{#pm}} (j_T);", 50, 0., 10.);
    TH1F *rH_50_100 = new TH1F("r_50_100", ";r;", 80, 0., 7.);
    TH2F *jtzH_50_100 = new TH2F("jt_z_50_100", ";#it{z}; j_{T}", 50, 0.0, 1.1, 50, 0., 10.);
    TH2F *zRH_50_100 = new TH2F("z_r_50_100", ";#it{z}; r", 120, 0.0, 1.1, 120, 0., 7.);

    TH1F *zH_1500p = new TH1F("z_1500p", ";D_{p}^{B^{#pm}} (z);" , 30, 0.0, 1.1);
//   In a ROOT session, you can do:
//      root> .L BJet_NoJetID_MC_SV_Tree.C
//      root> BJet_NoJetID_MC_SV_Tree t
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
    
   //Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
    
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
       if (jentry%100000==0)
           cout << "processing entry : " << jentry << endl;
       
       //      Long64_t ientry = LoadTree(jentry);
       //      if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       //      if (Cut(ientry) < 0) continue;
    
       
       //Jet pt cut, 20 GeV < pt < 150 GeV as in LHCb literature for heavy flavor//
       if ((Jet_PT/1000.) < (20.) ) {continue;}
       if ((Jet_Eta)<2.5 || Jet_Eta>4.0) {continue;}
       
       //Only Jets with 2 constituents or more
       if ( Jet_Dtr_nrecodtr<(2) )  {continue;}
       //if ( Jet_Dtr_nrecodtr<(2) || Jet_Dtr_nrecodtr>(5) )  {continue;}
       
       //Discarding 2-constituents jets with one of them being a photon
       if (Jet_Dtr_nrecodtr==2)
       { if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) ) continue;}
       
       //SV Cut
//       if ( (Jet_SVTag_Nvertices) == (1) )  //{continue;}
//       {
           for (int j=0; j<Jet_Dtr_nrecodtr; ++j)
           {
               if ( abs( Jet_Dtr_ID[j] ) == 521 )
               {
                   //cout << Jet_PT << endl;
                   bPx = Jet_Dtr_PX[j]/1000.;
                   bPy = Jet_Dtr_PY[j]/1000.;
                   bPz = Jet_Dtr_PZ[j]/1000.;
                   bE  = Jet_Dtr_E[j]/1000.;
                   
                   TLorentzVector b4vec(bPx, bPy, bPz, bE);
                   TVector3 b3vec(bPx, bPy, bPz);
                   TVector3 jet3vec(Jet_PX/1000., Jet_PY/1000., Jet_PZ/1000.);
                   
                   bPhi = b3vec.Phi();
                   jPhi = jet3vec.Phi();
                   
                   bM = (Jet_Dtr_M[j]/1000.);
                   //bM  = b4vec.M();
                   //cout << bM << endl;
                   //TLorentzVector jet4vec(Jet_Px, Jet_Py, Jet_Pz, Jet_PE);
                   
                   bz = ( b3vec.Dot(jet3vec) ) / ( jet3vec.Mag2() );
                   bJt = (jet3vec.Cross(b3vec).Mag())/(jet3vec.Mag());
                   double ucPhi = bPhi + 6.28;
                   double lcPhi = bPhi - 6.28;
                   std::vector<double> phiDiffSqVec{pow(ucPhi-jPhi,2), pow(bPhi-jPhi,2), pow(lcPhi-jPhi,2)};
                   std::vector<double>::iterator rPhiDiffSq = std::min_element(phiDiffSqVec.begin(), phiDiffSqVec.end());
                   bR = sqrt(pow(jet3vec.Eta() - b3vec.Eta(), 2) + phiDiffSqVec.at(std::distance(phiDiffSqVec.begin(), rPhiDiffSq)));
                   //bR = sqrt( pow( jet3vec.Phi() - b3vec.Phi() , 2) + pow(jet3vec.Eta() - b3vec.Eta(), 2));
                   jP =  jet3vec.Mag();
                   
                   if (bM >= 5.0 && bM <= 5.7)
                   {
                       bMH->Fill(bM);
                       bJetPtH->Fill(Jet_PT/1000.);
                       zH->Fill(bz);
                       jtH->Fill(bJt);
                       rH->Fill(bR);
                       jPH->Fill(Jet_PT/1000.,jP);
                       jtzH->Fill(bz, bJt);
                       zRH->Fill(bz,bR);
                       
                       if (Jet_PT/1000. > 20.0 && Jet_PT/1000. < 30.0)
                       {
                           bMH_20_30->Fill(bM);
                           zH_20_30->Fill(bz);
                           jtH_20_30->Fill(bJt);
                           rH_20_30->Fill(bR);
                           jtzH_20_30->Fill(bz, bJt);
                           zRH_20_30->Fill(bz,bR);
                       }
                       
                       if (jP < 500.)
                       {
                           zH_0_500p->Fill(bz);
                       }
                       
                       if (jP > 500. && jP < 1000.)
                       {
                           zH_500_1000p->Fill(bz);
                       }
                       
                       if (jP > 1000. && jP < 1500.)
                       {
                           zH_1000_1500p->Fill(bz);
                       }
                       
                       if (jP > 1500.)
                       {
                           zH_1500p->Fill(bz);
                       }
                       
                       
                       if (Jet_PT/1000. > 30.0 && Jet_PT/1000. < 50.0)
                       { bMH_30_50->Fill(bM);
                           zH_30_50->Fill(bz);
                           jtH_30_50->Fill(bJt);
                           rH_30_50->Fill(bR);
                           jtzH_30_50->Fill(bz, bJt);
                           zRH_30_50->Fill(bz,bR);
                       }
                       
                       if (Jet_PT/1000. > 50.0 && Jet_PT/1000. < 100.0)
                       { bMH_50_100->Fill(bM);
                           zH_50_100->Fill(bz);
                           jtH_50_100->Fill(bJt);
                           rH_50_100->Fill(bR);
                           jtzH_50_100->Fill(bz, bJt);
                           zRH_50_100->Fill(bz,bR);
                       }
                       
                   } //mass cut
               } //B(+-) hadron requirements "if loop"
               
               //cout << Jet_Dtr_ID[j] << " " << Jet_Dtr_M[j] << endl;
               
           } //Reconstructed Jet Daughters "For i Loop"
       
     } //jet entry loop
       
   //}
    outfile->Write();
    outfile->Close();
}
