
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

void RatioPlotsObs()
{
    
    TFile *f1 = TFile::Open("BJetsNoJetID_MassCut_All_841656.root");
    TFile *f2 = TFile::Open("BJetsNoJetID_MassCut_OnlyB_841656.root");
    TFile *f3 = TFile::Open("BJetsNoJetID_MsCut_All_DiMuon_1979178.root");
    TFile *f4 = TFile::Open("BJetsNoJetID_MsCut_OnlyB_DiMuon_1979178.root");

    TFile *outfile = new TFile("RatioPlotsObs.root", "RECREATE");
    
    TH2F *zjtAllBh = (TH2F*)f1->Get("Fzjt");
    TH2F *zrAllBh = (TH2F*)f1->Get("z_R");
    
    TH2F *zjtOnlyBBh = (TH2F*)f2->Get("Fzjt");
    TH2F *zrOnlyBBh = (TH2F*)f2->Get("z_R");
    
    TH2F *zjtAllDiMu = (TH2F*)f3->Get("Fzjt");
    TH2F *zrAllDiMu = (TH2F*)f3->Get("z_R");
    
    TH2F *zjtOnlyBDiMu = (TH2F*)f4->Get("Fzjt");
    TH2F *zrOnlyBDiMu = (TH2F*)f4->Get("z_R");
    
    zjtAllDiMu->Divide(zjtAllBh);
    zjtAllDiMu->Draw();
    zjtAllDiMu->Write();
    
    zrAllDiMu->Divide(zrAllBh);
    zrAllDiMu->Draw();
    zrAllDiMu->Write();
    
    zjtOnlyBDiMu->Divide(zjtOnlyBBh);
    zjtOnlyBDiMu->Draw();
    zjtOnlyBDiMu->Write();
    
    zrOnlyBDiMu->Divide(zrOnlyBBh);
    zrOnlyBDiMu->Draw();
    zrOnlyBDiMu->Write();

    outfile->Write();
    outfile->Close();
}
