//
//  BJetMCNoJetID.c
//  
//
//  Created by Jose Arias on 1/20/23.
//

#include <stdio.h>
#define BJetMCNoJetIDTree_cxx
#include "BJetMCNoJetIDTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TH1.h"
#include "TFile.h"

void BJetMCNoJetIDTree::Loop()
{

double bPx, bPy, bPz, bE;
double bz, bJt, bR, bM, jP;
const int nPt_bins = 3;

TString outfileName = "BJets_MC_NoJetID_MassCut.root";
TFile *outfile = new TFile(outfileName, "RECREATE");

TH1F *bMH = new TH1F("m", ";m_{B^{#pm}} (MeV/c^{2});", 175, 5000., 5700.);
TH1F *zH = new TH1F("z",";z;", 175, 0., 1.2);
TH1F *jtH = new TH1F("jt",";j_{T} (GeV/c);", 175, 0., 10.);                     //good shapes with 200 bins for 1 M for z and jt
TH1F *rH = new TH1F("r",";r;", 175, 0., 7.);
TH1F *bJetPtH = new TH1F("pt", ";p_{T} (GeV/c);", 175, 0., 200.);
TH2F *jPH = new TH2F("Pvspt", ";p_{T};|P_{jet}|", 175, 15., 200., 175, 0., 3000.);
TH2F *jtzH = new TH2F("Fzjt", ";#it{z}; j_{T}" , 175, 0., 1.2, 175, 0., 10.);

TH1F *bMH_bins[nPt_bins], *zH_bins[nPt_bins], *jtH_bins[nPt_bins], *rH_bins[nPt_bins];
TH2F *jPH_bins[nPt_bins], *jtzH_bins[nPt_bins];

const float Pt_bins[nPt_bins+1] = {20.0, 30.0, 50., 100.};

//   In a ROOT session, you can do:
//      root> .L BJetTree.C
//      root> BJetTree t
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

TString hist_name = "";

for (int i = 0; i < nPt_bins; ++i)
    { hist_name = "bm_";
      hist_name += Pt_bins[i];
      hist_name += "_";
      hist_name += Pt_bins[i+1];
      bMH_bins[i] = new TH1F(hist_name, ";m_{J/#Psi K} (MeV/c^{2});" ,175, 5000., 5700.);
      //e_dcat_binned[i]->Sumw2();
      
      hist_name = "z_";
      hist_name += Pt_bins[i];
      hist_name += "_";
      hist_name += Pt_bins[i+1];
      zH_bins[i] = new TH1F(hist_name,";z;", 175, 0., 1.2);

      hist_name = "jt_";
      hist_name += Pt_bins[i];
      hist_name += "_";
      hist_name += Pt_bins[i+1];
      jtH_bins[i] = new TH1F(hist_name,";j_{T} (GeV/c);", 175, 0., 10.);
      
      hist_name = "r_";
      hist_name += Pt_bins[i];
      hist_name += "_";
      hist_name += Pt_bins[i+1];
      rH_bins[i] = new TH1F(hist_name,";r;", 175, 0., 7.);
      
      hist_name = "Pvspt_";
      hist_name += Pt_bins[i];
      hist_name += "_";
      hist_name += Pt_bins[i+1];
      jPH_bins[i] = new TH2F(hist_name,";p_{T};|P_{jet}|", 175, 15., 200., 175, 0., 3000.);
      
      hist_name = "Fzjt_";
      hist_name += Pt_bins[i];
      hist_name += "_";
      hist_name += Pt_bins[i+1];
      jtzH_bins[i] = new TH2F(hist_name,";#it{z}; j_{T}", 175, 0., 1.2, 175, 0., 10.);
    }


  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();  //to process everything
  //Long64_t nentries = 200000;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    if (jentry%100000==0)
      cout << "processing entry : " << jentry << endl;
      
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Jet pt cut, 20 GeV < pt < 150 GeV as in LHCb literature for heavy flavor//
    if ((Jet_PT/1000) < (20) ) {continue;}
    
    if ( Jet_Dtr_nrecodtr<(2) )  {continue;}
    //if ( Jet_Dtr_nrecodtr<(2) || Jet_Dtr_nrecodtr>(5) )  {continue;}

    /*if (Jet_Dtr_nrecodtr==2)
      {
        if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) ) continue;
      } */
    
    // if (Cut(ientry) < 0) continue;
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
        
        bM = Jet_Dtr_M[j];
        //bM  = b4vec.M();
        //cout << bM << endl;
        //TLorentzVector jet4vec(Jet_Px, Jet_Py, Jet_Pz, Jet_PE);
        TVector3 jet3vec(Jet_PX/1000., Jet_PY/1000., Jet_PZ/1000.);
                
        bz = ( b3vec.Dot(jet3vec) ) / ( jet3vec.Mag2() );
        bJt = (jet3vec.Cross(b3vec).Mag())/(jet3vec.Mag());
        bR = sqrt( pow( jet3vec.Phi() - b3vec.Phi() , 2) + pow(jet3vec.Eta() - b3vec.Eta(), 2));
        jP =  jet3vec.Mag();
        
        if (bM >= 5000 && bM <= 5700) {
        bMH->Fill(bM);
        bJetPtH->Fill(Jet_PT/1000.);
        zH->Fill(bz);
        jtH->Fill(bJt);
        rH->Fill(bR);
        jPH->Fill(Jet_PT/1000.,jP);
        jtzH->Fill(bz, bJt);
      
     for (int i = 0; i < nPt_bins; ++i){
        if(Jet_PT/1000. > Pt_bins[i] && Jet_PT/1000. < Pt_bins[i+1])
          { bMH_bins[i]->Fill(bM);
            zH_bins[i]->Fill(bz);
            jtH_bins[i]->Fill(bJt);
            rH_bins[i]->Fill(bR);
            jPH_bins[i]->Fill(Jet_PT/1000.,jP);
            jtzH_bins[i]->Fill(bz, bJt);
          }
        }
       }
      }
      //cout << Jet_Dtr_ID[j] << " " << Jet_Dtr_M[j] << endl;
    }
  }
  
  //bJetPtH->Draw();
  //zH->Draw();
  //jtH->Draw();
  //rH->Draw();
  //bMH->Draw();
  //jPH->Draw("COLZ1");
  
  outfile->Write();
  outfile->Close();
  
}
