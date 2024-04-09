//#define Bjet_Variable_Tree_SameEvnts_cxx
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/BjetTree.h"
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/BjetTree.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <limits>
#include "/Users/josearias18/Desktop/QCDc2/pythia/Scripts/Reference/Header.h"

#include <stdio.h>

using namespace std;

void Bjet_Variable_Tree_SameEvnts(){
    
BjetTree DMTree(0, 1);
BjetTree BHTree(0, 2);
int prevEvent = -1;
    
    TFile *outfile = new TFile("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Bjets_SameEvents.root", "RECREATE");
    
    TH1F *DM_JetDtr_PX = new TH1F("DM_JetDtr_PX ", ";DiMuon Jet Dtr PX [GeV/c];", 120, 0.0, 400. );
    TH1F *DM_JetDtr_PY = new TH1F("DM_JetDtr_PY ", ";DiMuon Jet Dtr PY [GeV/c];", 120, 0.0, 400. );
    TH1F *DM_JetDtr_PZ = new TH1F("DM_JetDtr_PZ ", ";DiMuon Jet Dtr PZ [GeV/c];", 120, 0.0, 400. );
    TH1F *DM_JetDtr_PE = new TH1F("DM_JetDtr_PE ", ";DiMuon Jet Dtr PE [GeV/c];", 120, 0.0, 400. );
    
    TH1F *DM_Jet_PX = new TH1F("DM_Jet_PX ", ";DiMuon Jet PX [GeV/c];", 120, 0.0, 400. );
    TH1F *DM_Jet_PY = new TH1F("DM_Jet_PY ", ";DiMuon Jet PY [GeV/c];", 120, 0.0, 400. );
    TH1F *DM_Jet_PZ = new TH1F("DM_Jet_PZ ", ";DiMuon Jet PZ [GeV/c];", 120, 0.0, 400. );
    TH1F *DM_Jet_PE = new TH1F("DM_Jet_PE ", ";DiMuon Jet PE [GeV/c];", 120, 0.0, 400. );
    
for (int i = 0; i < 500 ; i++){ //DMTree.fChain->GetEntries()
    
    DMTree.GetEntry(i);
    
//    if (DMTree.eventNumber != prevEvent) {
//        cout << "New event: " << DMTree.eventNumber << endl;
//        prevEvent = DMTree.eventNumber;
//    }
    
    for (int j = 0; j < 500 ;j++){ //BHTree.fChain->GetEntries()
        
        BHTree.GetEntry(j);
            
        if( DMTree.eventNumber == BHTree.eventNumber)
        {
//            cout<< "=========================================== " << endl;
//            cout<< "|| DM entry: " << i << " | BH entry: "<< j << " ||" <<endl;
//            cout<< "- - - - - - - - - - - - - - - - - - - - - - " << endl;
            
            for (int k=0; k < DMTree.Jet_Dtr_nrecodtr; k++){
//                cout<< "DM PID JetDtrs: " << DMTree.Jet_Dtr_ID[k] << endl;
                TLorentzVector DM_JetDtr, DM_Jet;
                
                DM_JetDtr.SetPxPyPzE(DMTree.Jet_Dtr_PX[k]/1000., DMTree.Jet_Dtr_PY[k]/1000.,
                                  DMTree.Jet_Dtr_PZ[k]/1000.,  DMTree.Jet_Dtr_E[k]/1000.);
                DM_Jet.SetPxPyPzE(DMTree.Jet_PX/1000., DMTree.Jet_PY/1000., DMTree.Jet_PZ/1000., DMTree.Jet_PE/1000.);
                
                DM_JetDtr_PX->Fill(DMTree.Jet_Dtr_PX[k]/1000.);
                DM_JetDtr_PY->Fill(DMTree.Jet_Dtr_PY[k]/1000.);
                DM_JetDtr_PZ->Fill(DMTree.Jet_Dtr_PZ[k]/1000.);
                DM_JetDtr_PE->Fill(DMTree.Jet_Dtr_PE[k]/1000.);
                
                DM_Jet_PX->Fill(DMTree.Jet_PX/1000.);
//                cout<<"DM JetDtr 4-Vec: " << DM_JetDtr << endl;
//                cout<<"DM Jet 4-Vec: " << DM_Jet << endl;
        
            }
            
            cout<< "  " << endl;
            
            for (int l=0; l < BHTree.Jet_Dtr_nrecodtr; l++){
                   
//                    cout<< "BH PID JetDtrs: " << BHTree.Jet_Dtr_ID[l] << endl;
                
                }
            
            break;
            
            }
        
        }
    }
    outfile->Write();
    outfile->Close();
}

