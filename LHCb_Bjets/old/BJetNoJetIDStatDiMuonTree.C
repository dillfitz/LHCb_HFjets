#define BJetNoJetIDStatDiMuonTree_cxx
#include "BJetNoJetIDStatDiMuonTree.h"
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

using namespace std;

void BJetNoJetIDStatDiMuonTree::Loop()
{

double bPx, bPy, bPz, bE, bPhi;
double bz, bJt, bR, bM, jP, jPhi;

int nentries = fChain->GetEntries();
//int nentries = 50000;
TString outfileName = Form("BJetsNoJetID_MsCut_All_DiMuon_%d.root", nentries);
TFile *outfile = new TFile(outfileName, "RECREATE");

//Integrated Histograms
TH1F *bMH = new TH1F("m", ";m_{#mu#mu K^{#pm} (GeV/c^{2});", 175, 5.0, 5.7);
TH1F *zH = new TH1F("z",";z;", 150, 0.0, 1.1);
TH1F *jtH = new TH1F("jt",";j_{T} (GeV/c);", 175, 0., 8.);   //good shapes with 200 bins for 1 M for z and jt
TH1F *rH = new TH1F("r",";r;", 175, 0., 7.);
TH1F *bJetPtH = new TH1F("pt", ";p_{T} (GeV/c);", 175, 20., 200.);
TH2F *jPH = new TH2F("Pvspt", ";p_{T};|P_{jet}|", 175, 15., 200., 175, 0., 3000.);
TH2F *jtzH = new TH2F("Fzjt", ";#it{z}; j_{T}" , 175, 0.0, 1.1, 175, 0., 8.);
TH2F *zRH = new TH2F("z_R", ";#it{z}; r" , 175, 0.0, 1.1, 175, 0., 7.);

//Pt Binned Histograms
TH1F *bMH_20_30 = new TH1F("m_20_30", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,175, 5.0, 5.7);
TH1F *zH_20_30 = new TH1F("z_20_30", ";D_{p}^{B^{#pm}} (z);" , 120, 0.0, 1.1);
TH1F *zH_0_500p = new TH1F("z_0_500p", ";D_{p}^{B^{#pm}} (z);" , 120, 0.0, 1.1);
TH1F *jtH_20_30 = new TH1F("jt_20_30", ";D_{p}^{B^{#pm}} (j_T);", 150, 0., 8.);
TH1F *rH_20_30 = new TH1F("r (20 Gev/c < p_T < 30 GeV/c)", ";r;", 150, 0., 7.);
TH2F *jtzH_20_30 = new TH2F(";D(z,j_T) (20 Gev/c < p_T < 30 GeV/c);", ";#it{z}; j_{T}", 120, 0.0, 1.1, 120, 0., 8.);
TH2F *zRH_20_30 = new TH2F(";z vs. r) (20 Gev/c < p_T < 30 GeV/c);", ";#it{z}; r", 120, 0.0, 1.1, 120, 0., 7.);

TH1F *bMH_30_50 = new TH1F("m_30_50", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,175, 5.0, 5.7);
TH1F *zH_30_50 = new TH1F("z_30_50", ";D_{p}^{B^{#pm}} (z);" , 100, 0.0, 1.1);
TH1F *zH_500_1000p = new TH1F("z_500_1000p", ";D_{p}^{B^{#pm}} (z);" , 100, 0.0, 1.1);
TH1F *jtH_30_50 = new TH1F("jt_30_50", ";D_{p}^{B^{#pm}} (j_T);", 125, 0., 8.);
TH1F *rH_30_50 = new TH1F("r (30 Gev/c < p_T < 50 GeV/c)", ";r;", 125, 0., 7.);
TH2F *jtzH_30_50 = new TH2F(";D (z,j_T) (30 Gev/c < p_T < 50 GeV/c);", ";#it{z}; j_{T}", 120, 0.0, 1.1, 120, 0., 8.);
TH2F *zRH_30_50 = new TH2F(";z vs. r (30 Gev/c < p_T < 50 GeV/c);", ";#it{z}; r", 120, 0.0, 1.1, 120, 0., 7.);


TH1F *bMH_50_100 = new TH1F("m_50_100", ";m_{#mu#mu K^{#pm}} (GeV/c^{2});" ,175, 5.0, 5.7);
TH1F *zH_50_100 = new TH1F("z_50_100", ";D_{p}^{B^{#pm}} (z);" , 50, 0.0, 1.1);
TH1F *zH_1000_1500p = new TH1F("z_1000_1500p", ";D_{p}^{B^{#pm}} (z);" , 50, 0.0, 1.1);
TH1F *jtH_50_100 = new TH1F("jt_50_100", ";D_{p}^{B^{#pm}} (j_T);", 60, 0., 8.);
TH1F *rH_50_100 = new TH1F("r (50 Gev/c < p_T < 100 GeV/c)", ";r;", 80, 0., 7.);
TH2F *jtzH_50_100 = new TH2F(";D(z,j_T) (50 Gev/c < p_T < 100 GeV/c);", ";#it{z}; j_{T}", 50, 0.0, 1.1, 60, 0., 8.);
TH2F *zRH_50_100 = new TH2F(";z vs. r) (50 Gev/c < p_T < 100 GeV/c);", ";#it{z}; r", 120, 0.0, 1.1, 120, 0., 7.);

TH1F *zH_1500p = new TH1F("z_1500p", ";D_{p}^{B^{#pm}} (z);" , 30, 0.0, 1.1);

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

  if (fChain == 0) return;

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
      if ((Jet_Eta)<2.5 || Jet_Eta>4.0) {continue;}
      
      if ( Jet_Dtr_nrecodtr<(2) )  {continue;}
      //if ( Jet_Dtr_nrecodtr<(2) || Jet_Dtr_nrecodtr>(5) )  {continue;}
      
      if (Jet_Dtr_nrecodtr==2)
      {
          if ( ( Jet_Dtr_ID[0] == 22) || ( Jet_Dtr_ID[1] == 22) ) continue;
      }
      
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
              
              if (bM >= 5.27911-0.0337 && bM <= 5.27911+0.0337)
              {
                  bMH->Fill(bM);
                  bJetPtH->Fill(Jet_PT/1000.);
                  zH->Fill(bz);
                  jtH->Fill(bJt);
                  rH->Fill(bR);
                  jPH->Fill(Jet_PT/1000.,jP);
                  jtzH->Fill(bz, bJt);
                  zRH->Fill(bz,bR);
              }
              if (bM >= 5.27908-0.0324 && bM <= 5.27908+0.0324)
              {
                  if (Jet_PT/1000. > 20.0 && Jet_PT/1000. < 30.0)
                  {
                      bMH_20_30->Fill(bM);
                      zH_20_30->Fill(bz);
                      jtH_20_30->Fill(bJt);
                      rH_20_30->Fill(bR);
                      jtzH_20_30->Fill(bz, bJt);
                      zRH_20_30->Fill(bz,bR);
                  }
              }
              
              //            if (jP < 500.)
              //            {
              //                zH_0_500p->Fill(bz);
              //            }
              //
              //            if (jP > 500. && jP < 1000.)
              //            {
              //                zH_500_1000p->Fill(bz);
              //            }
              //
              //            if (jP > 1000. && jP < 1500.)
              //            {
              //                zH_1000_1500p->Fill(bz);
              //            }
              //
              //            if (jP > 1500.)
              //            {
              //                zH_1500p->Fill(bz);
              //            }
              //
              if (bM >= 5.2792-0.036 && bM <= 5.2792+0.036)
              {
                  if (Jet_PT/1000. > 30.0 && Jet_PT/1000. < 50.0)
                  { bMH_30_50->Fill(bM);
                      zH_30_50->Fill(bz);
                      jtH_30_50->Fill(bJt);
                      rH_30_50->Fill(bR);
                      jtzH_30_50->Fill(bz, bJt);
                      zRH_30_50->Fill(bz,bR);
                  }
              }
              if (bM >= 5.2785-0.05 && bM <= 5.2785+0.05)
              {
                  if (Jet_PT/1000. > 50.0 && Jet_PT/1000. < 100.0)
                  { bMH_50_100->Fill(bM);
                      zH_50_100->Fill(bz);
                      jtH_50_100->Fill(bJt);
                      rH_50_100->Fill(bR);
                      jtzH_50_100->Fill(bz, bJt);
                      zRH_50_100->Fill(bz,bR);
                  }
              }
              
          }
          
      }
      //cout << Jet_Dtr_ID[j] << " " << Jet_Dtr_M[j] << endl;
      
  }


///THIS WORKS!!! ///
auto hs = new THStack("hs","Jt");
jtH_20_30->SetLineColor(2);
hs->Add(jtH_20_30);
jtH_30_50->SetLineColor(3);
hs->Add(jtH_30_50);
jtH_50_100->SetLineColor(4);
hs->Add(jtH_50_100);

auto hs1 = new THStack("hs1","R");
rH_20_30->SetLineColor(2);
hs1->Add(rH_20_30);
rH_30_50->SetLineColor(3);
hs1->Add(rH_30_50);
rH_50_100->SetLineColor(4);
hs1->Add(rH_50_100);

auto hs2 = new THStack("hs2","R");
rH_20_30->SetLineColor(2);
hs2->Add(rH_20_30);
rH_30_50->SetLineColor(3);
hs2->Add(rH_30_50);
rH_50_100->SetLineColor(4);
hs2->Add(rH_50_100);

TCanvas* c1 = new TCanvas("c1","Jt and R",1400,800);
TCanvas* c2 = new TCanvas("c2","Jt and R",1400,800);
    
c1->Divide(2,1);

c1->cd(1);
hs->Draw("nostack");
gPad->SetLogy();
gPad->Update();

TLegend *legend1 = new TLegend(0.55,0.65,0.76,0.82);
legend1->AddEntry(jtH_20_30,"20 Gev/c < p_{T}^{jet} < 30 GeV/c","l");
legend1->AddEntry(jtH_30_50,"30 Gev/c < p_{T}^{jet} < 50 GeV/c","l");
legend1->AddEntry(jtH_50_100,"50 Gev/c < p_{T}^{jet} < 100 GeV/c","l");
legend1->Draw();
gPad->Update();

c1->cd(2);
hs1->Draw("nostack");
//hs1->GetXaxis()->SetRangeUser(0.0, 7.0);
gPad->SetLogy();
gPad->Update();

TLegend *legend2 = new TLegend(0.55,0.65,0.76,0.82);
legend2->AddEntry(rH_20_30,"20 Gev/c < p_{T}^{jet} < 30 GeV/c","l");
legend2->AddEntry(rH_30_50,"30 Gev/c < p_{T}^{jet} < 50 GeV/c","l");
legend2->AddEntry(rH_50_100,"50 Gev/c < p_{T}^{jet} < 100 GeV/c","l");
legend2->Draw();
gPad->Update();

c2->Divide(2,1);
    
c2->cd(1);
hs->Draw("nostack");
gPad->SetLogy();
gPad->Update();

TLegend *legend3 = new TLegend(0.55,0.65,0.76,0.82);
legend3->AddEntry(jtH_20_30,"20 Gev/c < p_{T}^{jet} < 30 GeV/c","l");
legend3->AddEntry(jtH_30_50,"30 Gev/c < p_{T}^{jet} < 50 GeV/c","l");
legend3->AddEntry(jtH_50_100,"50 Gev/c < p_{T}^{jet} < 100 GeV/c","l");
legend3->Draw();
gPad->Update();

c2->cd(2);
hs2->Draw("nostack");
hs2->GetXaxis()->SetRangeUser(0.0, 4.0);
gPad->SetLogy();
gPad->Update();

TLegend *legend4 = new TLegend(0.55,0.65,0.76,0.82);
legend4->AddEntry(rH_20_30,"20 Gev/c < p_{T}^{jet} < 30 GeV/c","l");
legend4->AddEntry(rH_30_50,"30 Gev/c < p_{T}^{jet} < 50 GeV/c","l");
legend4->AddEntry(rH_50_100,"50 Gev/c < p_{T}^{jet} < 100 GeV/c","l");
legend4->Draw();
gPad->Update();
    
c1->SaveAs("jt_r_All_DiMuon.pdf");
c2->SaveAs("jt_r_0_3_All_DiMuon.pdf");


//  jtH_20_30->SetLineColor(2);
//  jtH_20_30->Draw("Hist");
//  jtH_30_50->SetLineColor(3);
//  jtH_30_50->Draw("same Hist");
//  jtH_50_100->SetLineColor(4);
//  jtH_50_100->Draw("same Hist");
//  c1->Modified();

//  c1->cd(2);
//  rH_20_30->SetLineColor(2);
//  rH_30_50->SetLineColor(3);
//  rH_50_100->SetLineColor(4);
//  rH_20_30->Draw();
//  rH_30_50->Draw("same");
//  rH_30_50->Draw("same");
//  gPad->Update();
    
  outfile->Write();
  outfile->Close();
  
}
