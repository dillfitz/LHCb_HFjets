#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"

using namespace std;

void ClosureTest(int NumEvts = -1,
                 int dataset1 = 91590,
                 int dataset2 = 91591,
                 int NumIters = 2,                 
                 bool chargedJetCut = false,
                 bool WTA_cut = false,
                 double minimum_dR = 0.1,
                 bool SubtractGS = false)
{

  TRandom3 *myRNG = new TRandom3();
  const int nRuns = 1;

  TString string_reco, string_data, string_truth, string_eff, string_unfold, extension, str_eta, str_pt, str_Nevts;
  TString str_followHard, str_ghost, str_charged, str_Mag1, str_Mag2, str_flavor, str_GS(""), str_WTA;
  TString loc_hists("../../root_files/");
  TString loc_plots("../../plots/");  
  TString str_DTF = "";
  TString str_PID = "";
  int JetMeth = (dataset1 / 1000) % 10;
  int flavor = (dataset1 / 100) % 10;
  int ptRange = (dataset1 / 10) % 10;
  int Mag1 = (dataset1 / 1) % 10;
  int Mag2 = (dataset2 / 1) % 10;
  
  const int fixSmear = 42;

  // int NumIters = 1;
  // int RegIDS = 5;
  str_GS = SubtractGS ? "_GSsub" : "";
  str_DTF = DTF_cut ? "_DTF" : "";
  str_PID = PID_cut ? "_PID" : "";
  str_WTA = WTA_cut ? "_WTA" : "";

  str_Mag1 = Mag1 == 0 ? "_MD" : Mag1 == 1 ? "_MU"
                                           : "";
  str_Mag2 = Mag2 == 0 ? "_MD" : Mag2 == 1 ? "_MU"
                                           : "";
  str_flavor = flavor == 1 ? "_udsg" : flavor == 4 ? "_c"
                                   : flavor == 5   ? "_b"
                                                   : "";

  if (flavor == 1)
    str_followHard = "_hard";
  else
    str_followHard = "_HF";

  str_ghost = ghostCut ? Form("_ghost_%.1f", ghostProb) : "";
  str_charged = chargedJetCut ? "_charge" : "";
  str_eta = Form("_eta_%.1f%.1f", etaMin, etaMax);
  str_pt = Form("_ptj_%d%d", int(ptMin), int(ptMax));
  str_Nevts = Form("_ev_%d", NumEvts);

  string_reco = loc_hists + "BjetsMC/" + TString("reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset1);
  string_truth = loc_hists + "BjetsMC/" + TString("truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag1 + str_flavor + str_GS + str_WTA + Form("_%d", dataset1);  
  string_eff = loc_hists + "BjetsMC/" + TString("efficiency_truth") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_charged + str_Mag2 + str_flavor + str_GS + str_WTA + Form("_%d", dataset2);
  string_unfold = loc_hists + "BjetsMC/" + TString("unfold_reco") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag2 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset2); 
  string_data = loc_hists + "Bjets/" + TString("data") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_%d", dataset1);
  
  extension = loc_hists + "BjetsMC/" + TString("closure") + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + Form("_dR_%.2f", minimum_dR) + str_charged + str_Mag1 + str_flavor + str_DTF + str_PID + str_GS + str_WTA + Form("_iters_%d", NumIters) + Form("_%d", dataset1) + Form("_%d", dataset2);


  cout << string_reco + TString(".root") << endl;
  cout << string_truth + TString(".root") << endl;
  cout << string_eff + TString(".root") << endl;
  cout << string_unfold + TString(".root") << endl;
  cout << string_data + TString(".root") << endl;
  cout << extension + TString(".root") << endl;
  
  
  /////////////////////   Get Files /////////////////////////////////

  TFile *file_reco = new TFile(string_reco + TString(".root"), "READ"); 
  TFile *file_data = new TFile(string_data + TString(".root"), "READ");
  TFile *file_truth = new TFile(string_truth + TString(".root"), "READ"); 
  TFile *file_eff = new TFile(string_eff + TString(".root"), "READ"); 
  TFile *file_unfold = new TFile(string_unfold + TString(".root"), "READ"); 

  TFile *file_write = new TFile(extension + TString(".root"), "RECREATE");

  /////////////////////   Get histograms /////////////////////////////////

  TH1D *h1_jetpt_ref = (TH1D *)file_unfold->Get("jetpt");
  h1_jetpt_ref->Draw();
  TH1D *h1_jetpt_truth_ref = (TH1D *)file_unfold->Get("jetpt_truth;1");

  TH1D *h1_jetpt_reco = (TH1D *)file_reco->Get("Jet_pT");
  TH1D *h1_jetpt_data = (TH1D *)file_data->Get("Jet_pT");  
  TH1D *h1_HFpt_reco = (TH1D *)file_reco->Get("h1_HFpt");
  TH2D *h2_HFptjetpt_reco = (TH2D *)file_reco->Get("h2_HFptjetpt");
  TH2D *h2_jetpteta_reco = (TH2D *)file_reco->Get("h2_jetpteta");
  TH1D *hNumJets = (TH1D *)file_reco->Get("hNumJets");
  TH1D *h1_jetpt_final = (TH1D *)h1_jetpt_reco->Clone("jetpt_final");
  TH1D *h1_HFpt_final = (TH1D *)h1_HFpt_reco->Clone("HFpt_final");
  TH2D *h2_HFptjetpt_final = (TH2D *)h2_HFptjetpt_reco->Clone("HFptjetpt_final");
  TH2D *h2_jetpteta_final = (TH2D *)h2_jetpteta_reco->Clone("jetpteta_final");

  /////////////////////   Get Truth histograms /////////////////////////////////
  TH1D *h1_jetpt_truth = (TH1D *)file_truth->Get("Jet_pT");
  TH1D *h1_HFpt_truth = (TH1D *)file_truth->Get("h1_HFpt");
  TH2D *h2_HFptjetpt_truth = (TH2D *)file_truth->Get("h2_HFptjetpt");
  TH2D *h2_jetpteta_truth = (TH2D *)file_truth->Get("h2_jetpteta");
  //TH1D *h1_kt_truth = (TH1D *)file_truth->Get("kt");
  //TH1D *h1_dR_truth = (TH1D *)file_truth->Get("dR");
  TVectorD *NumJets_truth = (TVectorD *)file_truth->Get("NumJets");

  /////////////////////   Get Purity Hists /////////////////////////////////

  TH1D *h1_purity_jetpt = (TH1D *)file_unfold->Get("purity_jetpt");
  TH1D *h1_efficiency_jetpt = (TH1D *)file_unfold->Get("efficiency_jetpt");
  TH1D *h1_efficiency_recoJet_jetpt = (TH1D *)file_unfold->Get("efficiency_recoJet_jetpt");
  TH1D *h1_efficiency_vecHFpt = (TH1D *)file_unfold->Get("efficiency_HFpt");
  TH1D *h1_purity_vecHFpt = (TH1D *)file_unfold->Get("purity_HFpt");
  // TH3D * h3_purity_ptzjt = (TH3D*) file_unfold->Get("purity_ptHFzjt");
  // TH3D * h3_purity_ptzdR = (TH3D*) file_unfold->Get("purity_ptHFzdR");

  /////////////////////   Get Response Matrices /////////////////////////////////

  // RooUnfoldResponse * response_jetpt = (RooUnfoldResponse*)file_eff->Get("response_jetpt");
  RooUnfoldResponse *response_jetpt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_jetpt");
  TH2 *h2_response_jetpt = (TH2 *)response_jetpt->Hresponse();

  response_jetpt->UseOverflow();

  int ntoys = 5;
  // Multiply by purity
  h1_jetpt_final->Multiply(h1_purity_jetpt);
  RooUnfoldBayes unfold_jetpt(response_jetpt, h1_jetpt_final, NumIters);
  h1_jetpt_final = (TH1D *)unfold_jetpt.Hreco();
  
  cout << "Unfold successful" << endl;  

  // Divide by efficiency
  h1_jetpt_final->Divide(h1_efficiency_jetpt);

  TH1D *h1_jetpt_final_ratio = (TH1D *)h1_jetpt_final->Clone("h1_jetpt_final_ratio");
  h1_jetpt_final_ratio->Divide(h1_jetpt_truth);

  h1_jetpt_final->Write("h1_jetpt_final");
  h1_jetpt_reco->Write("h1_jetpt_reco");
  h1_jetpt_truth->Write("h1_jetpt_truth");
  h1_jetpt_final_ratio->Write();
  TRatioPlot *jetpt_ratio = new TRatioPlot(h1_jetpt_final, h1_jetpt_truth);
  jetpt_ratio->Write("jetpt_ratio");
  
  
  /////////////////////   Get normalization values for 20 < pT < 100 histograms /////////////////////////////////
  

  int binlow_jet = h1_jetpt_truth->FindBin(ptMin);
  int binhigh_jet = h1_jetpt_truth->FindBin(ptMax);

  double Njets_reco = h1_jetpt_reco->Integral(binlow_jet, binhigh_jet);
  double Njets_truth = h1_jetpt_truth->Integral(binlow_jet, binhigh_jet);
  double Njets_final = h1_jetpt_final->Integral(binlow_jet, binhigh_jet);
  
  std::cout << "Njets_reco : " << Njets_reco << " Njets_truth : " << Njets_truth << " Njets_final : " << Njets_final << std::endl;
  
  ////////////////////////////////////
  // Smearing the jet pt distribution
  ///////////////////////////////////
  TH1D *h1_jetpt_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH1D *h1_jetpt_smear = (TH1D *)h1_jetpt_reco->Clone(Form("jetpt_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h1_jetpt_smear, h1_jetpt_data, myRNG);
    
    // Multiply by purity
    h1_jetpt_smear->Multiply(h1_purity_jetpt);
      
    RooUnfoldBayes unfold_jetpt_smear(response_jetpt, h1_jetpt_smear, NumIters);      
    h1_jetpt_smear = (TH1D *)unfold_jetpt_smear.Hreco();

    // Divide by efficiency
    h1_jetpt_smear->Divide(h1_efficiency_jetpt);
  
    TH1D *h1_jetpt_ratio_smear = (TH1D *)h1_jetpt_reco->Clone(Form("h1_jetpt_ratio_smear%d", i));
    //TH1D *h1_jetpt_pull_smear = (TH1D *)h1_jetpt_reco->Clone(Form("h1_jetpt_pull_smear%d", i));
    h1_jetpt_ratio_smear->Divide(h1_jetpt_smear, h1_jetpt_truth);
    h1_jetpt_ratio_smear->Write();
    //h1_jetpt_pull_smear->Write();
/*    
    if (i == 0)
    {
      h1_jetpt_closure_error = (TH1D *)h1_jetpt_ratio_smear->Clone("h1_jetpt_closure_error");
      h1_jetpt_closure_error->Reset(); // Reset the histogram to zero
    }
    
  
    // h1_jetpt_closure_error->Add(h1_jetpt_ratio_smear);
    // Loop over all bins and add in quadrature
    for (int x = 1; x <= h1_jetpt_ratio_smear->GetNbinsX(); ++x)
    {

      double binContent = 1. - h1_jetpt_ratio_smear->GetBinContent(x);
      double sumContent = h1_jetpt_closure_error->GetBinContent(x);
      h1_jetpt_closure_error->SetBinContent(x, sumContent + binContent * binContent);

      double binError = 1. - h1_jetpt_ratio_smear->GetBinError(x);
      double sumError = h1_jetpt_closure_error->GetBinError(x);
      h1_jetpt_closure_error->SetBinError(x, sumError + binError * binError);
    }
*/    
  }
/*
  // h1_jetpt_closure_error->Scale(1.0 / nRuns);
  // Take the square root of the final sum histogram to get the quadrature sum
  for (int x = 1; x <= h1_jetpt_closure_error->GetNbinsX(); ++x)
  {
    double sumContent = h1_jetpt_closure_error->GetBinContent(x);
    h1_jetpt_closure_error->SetBinContent(x, TMath::Sqrt(sumContent) / TMath::Sqrt(nRuns - 1));

    double sumError = h1_jetpt_closure_error->GetBinError(x);
    h1_jetpt_closure_error->SetBinError(x, TMath::Sqrt(sumError) / TMath::Sqrt(nRuns - 1));
  }

  h1_jetpt_closure_error->Write();
*/ 
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create z histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH1D *h1_z_truth = (TH1D *)file_truth->Get("z");
  TH2D *h2_ptz_truth = (TH2D *)file_truth->Get("ptz");
  TH2D *h2_ptz = (TH2D *)file_reco->Get("ptz");
  TH2D *h2_ptz_data = (TH2D *)file_data->Get("ptz");  
  TH2D *h2_ptz_final = (TH2D *)h2_ptz->Clone("ptz_final");
  TH2D *h2_eff_ptz = (TH2D *)file_unfold->Get("efficiency_ptz");
  TH2D *h2_purity_ptz = (TH2D *)file_unfold->Get("purity_ptz");
  RooUnfoldResponse *response_ptz = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptz");
  
  // Multiply by purity  
  h2_ptz_final->Multiply(h2_ptz_final, h2_purity_ptz);
  RooUnfoldBayes unfold_ptz(response_ptz, h2_ptz_final, NumIters);

  h2_ptz_final = (TH2D *)unfold_ptz.Hreco();
  // Divide by efficiency  
  h2_ptz_final->Divide(h2_ptz_final, h2_eff_ptz);
  
  int binlow = h2_ptz->GetYaxis()->FindBin(ptMin + 0.1);
  int binhigh = h2_ptz->GetYaxis()->FindBin(ptMax - 0.1);
  int binlowz = h2_ptz->GetXaxis()->FindBin(0.0);
  int binhighz = h2_ptz->GetXaxis()->FindBin(1.1);

  h2_ptz_final->GetYaxis()->SetRangeUser(ptMin, ptMax);
  h2_ptz_truth->GetYaxis()->SetRangeUser(ptMin, ptMax);

  h2_ptz->GetYaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH1D *h1_z_final = (TH1D *)h2_ptz_final->ProjectionX("z_final");
  TH1D *h1_z = (TH1D *)h2_ptz->ProjectionX("z");
  TH1D *h1_z_truth = (TH1D *)h2_ptz_truth->ProjectionX("z_truth");
  //
  
  h1_z_final->GetXaxis()->SetRange(binlowz, binhighz);
  h1_z_truth->GetXaxis()->SetRange(binlowz, binhighz);
  
  // This will depend on results of 1D jet pt unfolding
  h1_z_final->Scale(1. / Njets_final, "width");
  //h2_ptz_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h1_z_truth->Scale(1. / Njets_truth, "width");
  h1_z->Scale(1. / Njets_reco, "width");  
  

  TH1D *h1_z_ratio = (TH1D *)h1_z->Clone("h1_z_ratio");
  TH1D *h1_z_ratio_final = (TH1D *)h1_z_final->Clone("h1_z_ratio_final"); 


  h1_z_ratio->Divide(h1_z, h1_z_truth);
  h1_z_ratio_final->Divide(h1_z_final, h1_z_truth);

  h1_z_ratio_final->GetXaxis()->SetRange(binlowz, binhighz);
 
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH1D *h1_z_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH2D *h2_ptz_smear = (TH2D *)h2_ptz->Clone(Form("ptz_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h2_ptz_smear, h2_ptz_data, myRNG);
    
    // Multiply by purity
    h2_ptz_smear->Multiply(h2_ptz_smear, h2_purity_ptz);
    
    RooUnfoldBayes unfold_ptz_smear(response_ptz, h2_ptz_smear, NumIters);
    h2_ptz_smear = (TH2D *)unfold_ptz_smear.Hreco();
    
    // Divide by efficiency    
    h2_ptz_smear->Divide(h2_ptz_smear, h2_eff_ptz);
    
    h2_ptz_smear->GetYaxis()->SetRangeUser(ptMin, ptMax);
    
       
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]
    TH1D *h1_z_smear = (TH1D *)h2_ptz_smear->ProjectionX(Form("z_smear%d", i));
    //TH1D *h1_z_smear_20_100 = (TH1D *)h2_ptz_smear->ProjectionX(Form("z_smear_20_100_%d", i), 3, 5);  


    h1_z_smear->GetXaxis()->SetRange(binlowz, binhighz);
    h1_z_smear->GetXaxis()->SetTitle("z");
    
             
    h1_z_smear->Scale(1. / Njets_final, "width");

    std::cout << endl;    
    std::cout << "h1_z after norm : " << h1_z_smear->GetEntries() << std::endl;
    std::cout << endl;    
    
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]    
    //h1_z_smear_20_100->Scale(1./h1_jetpt_final->Integral(3,5), "width");     
    //h1_z_truth_20_100->Scale(1./h1_jetpt_truth->Integral(3,5), "width");         
    
    TRatioPlot *z_ratio_smear = new TRatioPlot(h1_z_smear, h1_z_truth);

    z_ratio_smear->SetH1DrawOpt("E");
    z_ratio_smear->SetH2DrawOpt("E"); 
    h1_z_truth->SetLineColor(kRed);       
    
    z_ratio_smear->Write(Form("z_ratio_smear%d", i));    
    z_ratio_smear->GetUpperPad()->cd();
    TLegend *leg_z = new TLegend(0.8, 0.8, 1.0, 1.0);
    leg_z->AddEntry(h1_z_smear, "l");
    leg_z->AddEntry(h1_z_truth,"l");
    leg_z->Draw();
    
    //TRatioPlot *z_ratio_smear_20_100 = new TRatioPlot(h1_z_smear_20_100, h1_z_truth_20_100);       
    //z_ratio_smear_20_100->Write(Form("z_ratio_smear_%d_20_100", i));    
  
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]        
    TH1D *h1_z_ptbinned[ptbinsize-2], *h1_z_truth_ptbinned[ptbinsize-2];
    TRatioPlot *h1_z_ptbinned_ratio[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h1_z_ptbinned[j-2] = (TH1D *)h2_ptz_smear->ProjectionX(Form("z_smear%d_pt%d", i,j), j+1, j+1);    
        h1_z_truth_ptbinned[j-2] = (TH1D *)h2_ptz_truth->ProjectionX(Form("z_truth_smear%d_pt%d", i,j), j+1, j+1);
        h1_z_ptbinned[j-2]->GetXaxis()->SetRange(binlowz, binhighz);
        h1_z_truth_ptbinned[j-2]->GetXaxis()->SetRange(binlowz, binhighz);
        h1_z_ptbinned[j-2]->GetXaxis()->SetTitle("z");
        h1_z_truth_ptbinned[j-2]->GetXaxis()->SetTitle("z");
        
        //if (j==4)
       // {
       //   h1_z_ptbinned[j-2]->Rebin(2);  
       //   h1_z_truth_ptbinned[j-2]->Rebin(2);
       // }      
        h1_z_ptbinned[j-2]->Scale(1./h1_jetpt_final->Integral(j+1, j+1), "width");
        h1_z_truth_ptbinned[j-2]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1), "width");
        h1_z_ptbinned_ratio[j-2] = new TRatioPlot(h1_z_ptbinned[j-2], h1_z_truth_ptbinned[j-2]);
        h1_z_ptbinned_ratio[j-2]->SetH1DrawOpt("E");
        h1_z_ptbinned_ratio[j-2]->SetH2DrawOpt("E");
        h1_z_truth_ptbinned[j-2]->SetLineColor(kRed);
        h1_z_ptbinned_ratio[j-2]->Write(Form("z_ratio_smear%d_pt%d", i,j));                 
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create jt histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH1D *h1_jt_truth = (TH1D *)file_truth->Get("jt");
  TH2D *h2_ptjt_truth = (TH2D *)file_truth->Get("ptjt");
  TH2D *h2_ptjt = (TH2D *)file_reco->Get("ptjt");
  TH2D *h2_ptjt_data = (TH2D *)file_data->Get("ptjt");  
  TH2D *h2_ptjt_final = (TH2D *)h2_ptjt->Clone("ptjt_final");
  TH2D *h2_eff_ptjt = (TH2D *)file_unfold->Get("efficiency_ptjt");
  TH2D *h2_purity_ptjt = (TH2D *)file_unfold->Get("purity_ptjt");
  RooUnfoldResponse *response_ptjt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptjt");
  
  // Multiply by purity  
  h2_ptjt_final->Multiply(h2_ptjt_final, h2_purity_ptjt);
  RooUnfoldBayes unfold_ptjt(response_ptjt, h2_ptjt_final, NumIters);

  h2_ptjt_final = (TH2D *)unfold_ptjt.Hreco();
  // Divide by efficiency  
  h2_ptjt_final->Divide(h2_ptjt_final, h2_eff_ptjt);
  
  int binlowjt = h2_ptjt->GetXaxis()->FindBin(0.0);
  int binhighjt = h2_ptjt->GetXaxis()->FindBin(10.0);   

  h2_ptjt_final->GetYaxis()->SetRangeUser(ptMin, ptMax);
  h2_ptjt_truth->GetYaxis()->SetRangeUser(ptMin, ptMax);

  h2_ptjt->GetYaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH1D *h1_jt_final = (TH1D *)h2_ptjt_final->ProjectionX("jt_final");
  TH1D *h1_jt = (TH1D *)h2_ptjt->ProjectionX("jt");
  TH1D *h1_jt_truth = (TH1D *)h2_ptjt_truth->ProjectionX("jt_truth");
  //
  
  h1_jt_final->GetXaxis()->SetRange(binlowjt, binhighjt);
  h1_jt_truth->GetXaxis()->SetRange(binlowjt, binhighjt);
  
  // This will depend on results of 1D jet pt unfolding
  h1_jt_final->Scale(1. / Njets_final, "width");
  //h2_ptjt_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h1_jt_truth->Scale(1. / Njets_truth, "width");
  h1_jt->Scale(1. / Njets_reco, "width");  
  

  TH1D *h1_jt_ratio = (TH1D *)h1_jt->Clone("h1_jt_ratio");
  TH1D *h1_jt_ratio_final = (TH1D *)h1_jt_final->Clone("h1_jt_ratio_final"); 


  h1_jt_ratio->Divide(h1_jt, h1_jt_truth);
  h1_jt_ratio_final->Divide(h1_jt_final, h1_jt_truth);

  h1_jt_ratio_final->GetXaxis()->SetRange(binlowjt, binhighjt);
 
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH1D *h1_jt_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH2D *h2_ptjt_smear = (TH2D *)h2_ptjt->Clone(Form("ptjt_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h2_ptjt_smear, h2_ptjt_data, myRNG);  

    // Multiply by purity
    h2_ptjt_smear->Multiply(h2_ptjt_smear, h2_purity_ptjt);
    RooUnfoldBayes unfold_ptjt_smear(response_ptjt, h2_ptjt_smear, NumIters);
    h2_ptjt_smear = (TH2D *)unfold_ptjt_smear.Hreco();
    // Divide by efficiency    
    h2_ptjt_smear->Divide(h2_ptjt_smear, h2_eff_ptjt);
    h2_ptjt_smear->GetYaxis()->SetRangeUser(ptMin, ptMax);  
       
    TH1D *h1_jt_smear = (TH1D *)h2_ptjt_smear->ProjectionX(Form("jt_smear%d", i));                        
    h1_jt_smear->GetXaxis()->SetRange(binlowjt, binhighjt);   
    h1_jt_smear->GetXaxis()->SetTitle("j_{T} (GeV/c)");
    h1_jt_smear->Scale(1. / Njets_final, "width");     
   
    TRatioPlot *jt_ratio_smear = new TRatioPlot(h1_jt_smear, h1_jt_truth);          
    jt_ratio_smear->SetH1DrawOpt("E");
    jt_ratio_smear->SetH2DrawOpt("E"); 
    h1_jt_truth->SetLineColor(kRed);         
    jt_ratio_smear->Write(Form("jt_ratio_smear%d", i));

    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]        
    TH1D *h1_jt_ptbinned[ptbinsize-2], *h1_jt_truth_ptbinned[ptbinsize-2];
    TRatioPlot *h1_jt_ptbinned_ratio[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h1_jt_ptbinned[j-2] = (TH1D *)h2_ptjt_smear->ProjectionX(Form("jt_smear%d_pt%d", i,j), j+1, j+1);    
        h1_jt_truth_ptbinned[j-2] = (TH1D *)h2_ptjt_truth->ProjectionX(Form("jt_truth_smear%d_pt%d", i,j), j+1, j+1);
        h1_jt_ptbinned[j-2]->GetXaxis()->SetRange(binlowjt, binhighjt);
        h1_jt_truth_ptbinned[j-2]->GetXaxis()->SetRange(binlowjt, binhighjt);
        h1_jt_ptbinned[j-2]->GetXaxis()->SetTitle("j_{T} (GeV/c)");
        h1_jt_truth_ptbinned[j-2]->GetXaxis()->SetTitle("j_{T} (GeV/c)");
        
        h1_jt_ptbinned[j-2]->Scale(1./h1_jetpt_final->Integral(j+1, j+1), "width");
        h1_jt_truth_ptbinned[j-2]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1), "width");
        h1_jt_ptbinned_ratio[j-2] = new TRatioPlot(h1_jt_ptbinned[j-2], h1_jt_truth_ptbinned[j-2]);
        h1_jt_ptbinned_ratio[j-2]->SetH1DrawOpt("E");
        h1_jt_ptbinned_ratio[j-2]->SetH2DrawOpt("E");
        h1_jt_truth_ptbinned[j-2]->SetLineColor(kRed);        
        h1_jt_ptbinned_ratio[j-2]->Write(Form("jt_ratio_smear%d_pt%d", i,j));                 
    }      
    
  }  
  
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create r histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH1D *h1_r_truth = (TH1D *)file_truth->Get("r");
  TH2D *h2_ptr_truth = (TH2D *)file_truth->Get("ptr");
  TH2D *h2_ptr = (TH2D *)file_reco->Get("ptr");
  TH2D *h2_ptr_data = (TH2D *)file_data->Get("ptr");  
  TH2D *h2_ptr_final = (TH2D *)h2_ptr->Clone("ptr_final");
  TH2D *h2_eff_ptr = (TH2D *)file_unfold->Get("efficiency_ptr");
  TH2D *h2_purity_ptr = (TH2D *)file_unfold->Get("purity_ptr");
  RooUnfoldResponse *response_ptr = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptr");
  
  // Multiply by purity  
  h2_ptr_final->Multiply(h2_ptr_final, h2_purity_ptr);
  RooUnfoldBayes unfold_ptr(response_ptr, h2_ptr_final, NumIters);

  h2_ptr_final = (TH2D *)unfold_ptr.Hreco();
  // Divide by efficiency  
  h2_ptr_final->Divide(h2_ptr_final, h2_eff_ptr);
  
  int binlowr = h2_ptr->GetXaxis()->FindBin(0.0);
  int binhighr = h2_ptr->GetXaxis()->FindBin(0.5);  

  h2_ptr_final->GetYaxis()->SetRangeUser(ptMin, ptMax);
  h2_ptr_truth->GetYaxis()->SetRangeUser(ptMin, ptMax);

  h2_ptr->GetYaxis()->SetRangeUser(ptMin, ptMax);

  //
  TH1D *h1_r_final = (TH1D *)h2_ptr_final->ProjectionX("r_final");
  TH1D *h1_r = (TH1D *)h2_ptr->ProjectionX("r");
  TH1D *h1_r_truth = (TH1D *)h2_ptr_truth->ProjectionX("r_truth");
  //
  
  h1_r_final->GetXaxis()->SetRange(binlowr, binhighr);
  h1_r_truth->GetXaxis()->SetRange(binlowr, binhighr);
  
  // This will depend on results of 1D jet pt unfolding
  h1_r_final->Scale(1. / Njets_final, "width");
  //h2_ptr_vecfinal->Scale(1. / Njets_vecfinal, "width");
  h1_r_truth->Scale(1. / Njets_truth, "width");
  h1_r->Scale(1. / Njets_reco, "width");  
  

  TH1D *h1_r_ratio = (TH1D *)h1_r->Clone("h1_r_ratio");
  TH1D *h1_r_ratio_final = (TH1D *)h1_r_final->Clone("h1_r_ratio_final"); 


  h1_r_ratio->Divide(h1_r, h1_r_truth);
  h1_r_ratio_final->Divide(h1_r_final, h1_r_truth);

  h1_r_ratio_final->GetXaxis()->SetRange(binlowr, binhighr);
 
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH1D *h1_r_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH2D *h2_ptr_smear = (TH2D *)h2_ptr->Clone(Form("ptr_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h2_ptr_smear, h2_ptr_data, myRNG);

    // Multiply by purity
    h2_ptr_smear->Multiply(h2_ptr_smear, h2_purity_ptr);
    
    RooUnfoldBayes unfold_ptr_smear(response_ptr, h2_ptr_smear, NumIters);
    h2_ptr_smear = (TH2D *)unfold_ptr_smear.Hreco();
    
    // Divide by efficiency    
    h2_ptr_smear->Divide(h2_ptr_smear, h2_eff_ptr);
    
    h2_ptr_smear->GetYaxis()->SetRangeUser(ptMin, ptMax);
         
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]
    TH1D *h1_r_smear = (TH1D *)h2_ptr_smear->ProjectionX(Form("r_smear%d", i));                     
    h1_r_smear->GetXaxis()->SetRange(binlowr, binhighr);    
    h1_r_smear->GetXaxis()->SetTitle("r");    
    h1_r_smear->Scale(1. / Njets_final, "width");   
    TRatioPlot *r_ratio_smear = new TRatioPlot(h1_r_smear, h1_r_truth);     
    r_ratio_smear->SetH1DrawOpt("E");
    r_ratio_smear->SetH2DrawOpt("E"); 
    h1_r_truth->SetLineColor(kRed);         
    r_ratio_smear->Write(Form("r_ratio_smear%d", i));
    
    // pT bins [7-15, 15-20, 20-30, 30-50, 50-100, 100-?]        
    TH1D *h1_r_ptbinned[ptbinsize-2], *h1_r_truth_ptbinned[ptbinsize-2];
    TRatioPlot *h1_r_ptbinned_ratio[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h1_r_ptbinned[j-2] = (TH1D *)h2_ptr_smear->ProjectionX(Form("r_smear%d_pt%d", i,j), j+1, j+1);    
        h1_r_truth_ptbinned[j-2] = (TH1D *)h2_ptr_truth->ProjectionX(Form("r_truth_smear%d_pt%d", i,j), j+1, j+1);
        h1_r_ptbinned[j-2]->GetXaxis()->SetRange(binlowr, binhighr);
        h1_r_truth_ptbinned[j-2]->GetXaxis()->SetRange(binlowr, binhighr);
        h1_r_ptbinned[j-2]->GetXaxis()->SetTitle("r");
        h1_r_truth_ptbinned[j-2]->GetXaxis()->SetTitle("r");
        
        h1_r_ptbinned[j-2]->Scale(1./h1_jetpt_final->Integral(j+1, j+1), "width");
        h1_r_truth_ptbinned[j-2]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1), "width");
        h1_r_ptbinned_ratio[j-2] = new TRatioPlot(h1_r_ptbinned[j-2], h1_r_truth_ptbinned[j-2]);
        h1_r_ptbinned_ratio[j-2]->SetH1DrawOpt("E");
        h1_r_ptbinned_ratio[j-2]->SetH2DrawOpt("E");
        h1_r_truth_ptbinned[j-2]->SetLineColor(kRed);        
        h1_r_ptbinned_ratio[j-2]->Write(Form("r_ratio_smear%d_pt%d", i,j));                 
    }         
  }  

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create zjt histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH2D *h2_zjt_truth = (TH2D *)file_truth->Get("zjt");
  TH3D *h3_ptzjt_truth = (TH3D *)file_truth->Get("ptzjt");
  TH3D *h3_ptzjt = (TH3D *)file_reco->Get("ptzjt");
  TH3D *h3_ptzjt_data = (TH3D *)file_data->Get("ptzjt");  
  TH3D *h3_ptzjt_final = (TH3D *)h3_ptzjt->Clone("ptzjt_final");
  TH3D *h3_eff_ptzjt = (TH3D *)file_unfold->Get("efficiency_ptzjt");
  TH3D *h3_purity_ptzjt = (TH3D *)file_unfold->Get("purity_ptzjt");
  RooUnfoldResponse *response_ptzjt = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzjt");
  
  // Multiply by purity  
  h3_ptzjt_final->Multiply(h3_ptzjt_final, h3_purity_ptzjt);
  RooUnfoldBayes unfold_ptzjt(response_ptzjt, h3_ptzjt_final, NumIters);
  h3_ptzjt_final = (TH3D *)unfold_ptzjt.Hreco();
  // Divide by efficiency  
  h3_ptzjt_final->Divide(h3_ptzjt_final, h3_eff_ptzjt);
  //
  //

  h3_ptzjt_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzjt_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);

  h3_ptzjt->GetZaxis()->SetRangeUser(ptMin, ptMax);

  TH2D *h2_zjt_final = (TH2D *)h3_ptzjt_final->Project3D("zjt_final_yx");
  TH2D *h2_zjt = (TH2D *)h3_ptzjt->Project3D("zjt_yx");
  TH2D *h2_zjt_truth = (TH2D *)h3_ptzjt_truth->Project3D("zjt_truth_yx");
  //
  h2_zjt_final->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_zjt_final->GetXaxis()->SetRange(binlowz, binhighz);
  h2_zjt_truth->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_zjt_truth->GetXaxis()->SetRange(binlowz, binhighz);
  
  
  // This will depend on results of 1D jet unfolding
  h2_zjt_final->Scale(1. / Njets_final, "width");
  h2_zjt_truth->Scale(1. / Njets_truth, "width");

  TH2D *h2_zjt_ratio = (TH2D *)h2_zjt->Clone("h2_zjt_ratio");
  TH2D *h2_zjt_ratio_final = (TH2D *)h2_zjt->Clone("h2_zjt_ratio_final");
  //TH2D *h2_zjt_pull_final = (TH2D *)h2_zjt->Clone("h2_zjt_pull_final");

  //TH2D *h2_zjt_pull = (TH2D *)h2_zjt_truth->Clone("zjt_pull");

  //TH1D *h1_zjt_pulldist = new TH1D("zjt_pulldist", "", 20, -4.5, 4.5);
  //TH1D *h1_zjt_pulldist_final = new TH1D("zjt_pulldist_final", "", 20, -4.5, 4.5);
  //TH1D *h1_ptzjt_pulldist_vecfinal = new TH1D("ptzjt_pulldist_vecfinal", "", 20, -4.5, 4.5);

  h2_zjt_ratio->Divide(h2_zjt, h2_zjt_truth);
  h2_zjt_ratio_final->Divide(h2_zjt_final, h2_zjt_truth);

  h2_zjt_ratio_final->GetYaxis()->SetRange(binlowjt, binhighjt);
  h2_zjt_ratio_final->GetXaxis()->SetRange(binlowz, binhighz);

  //h2_zjt_pull_final->GetYaxis()->SetRange(binlowjt, binhighjt);        h2_zjt_truth_ptbinned[j-2]->Draw();
  //h2_zjt_pull_final->GetXaxis()->SetRange(binlowz, binhighz);

  //GetPullsRatio(h2_zjt_ratio, h2_zjt_pull, h1_zjt_pulldist);
  //GetPullsRatio(h2_zjt_ratio_final, h2_zjt_pull_final, h1_zjt_pulldist_final);

  //double zjt_pullperf1 = GetPullPerformance(h2_zjt_pull, 1);
  //double zjt_pullperf2 = GetPullPerformance(h2_zjt_pull, 2);

  //double zjt_pullperf1_final = GetPullPerformance(h2_zjt_pull_final, 1);
  //double zjt_pullperf2_final = GetPullPerformance(h2_zjt_pull_final, 2);
  
  h2_zjt_ratio_final->SetOption("COLZ");  
  h2_zjt_ratio_final->Write();
  /*  
  h2_zjt_pull->Write();  
  h2_zjt_pull_final->Write();
  h1_zjt_pulldist->Write();
  h1_zjt_pulldist_final->Write();  
  */
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH2D *h2_zjt_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH3D *h3_ptzjt_smear = (TH3D *)h3_ptzjt->Clone(Form("ptzjt_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h3_ptzjt_smear, h3_ptzjt_data, myRNG);
    // Multiply by purity
    h3_ptzjt_smear->Multiply(h3_ptzjt_smear, h3_purity_ptzjt);
    RooUnfoldBayes unfold_ptzjt_smear(response_ptzjt, h3_ptzjt_smear, NumIters);

    h3_ptzjt_smear = (TH3D *)unfold_ptzjt_smear.Hreco();
    // Divide by efficiency
    h3_ptzjt_smear->Divide(h3_ptzjt_smear, h3_eff_ptzjt);
    h3_ptzjt_smear->GetZaxis()->SetRangeUser(ptMin, ptMax);

    TH2D *h2_zjt_smear = (TH2D *)h3_ptzjt_smear->Project3D(Form("zjt_smear%d_yx", i));

    h2_zjt_smear->GetYaxis()->SetRange(binlowjt, binhighjt);
    h2_zjt_smear->GetXaxis()->SetRange(binlowz, binhighz);
    h2_zjt_smear->Scale(1. / Njets_final, "width");
    TH2D *h2_zjt_ratio_smear = (TH2D *)h2_zjt_smear->Clone(Form("zjt_ratio_smear%d", i));
    //TH2D *h2_zjt_pull_smear = (TH2D *)h2_zjt_smear->Clone(Form("h2_zjt_pull_smear%d", i));
    h2_zjt_ratio_smear->Divide(h2_zjt_smear, h2_zjt_truth); 

    h2_zjt_ratio_smear->GetYaxis()->SetRange(binlowjt, binhighjt);
    h2_zjt_ratio_smear->GetXaxis()->SetRange(binlowz, binhighz);

    //h2_zjt_pull_smear->GetYaxis()->SetRange(binlowjt, binhighjt);
    //h2_zjt_pull_smear->GetXaxis()->SetRange(binlowz, binhighz);
    h2_zjt_ratio_smear->SetOption("COLZ");    
    h2_zjt_ratio_smear->Write();      
    //h2_zjt_pull_smear->Write(); 
    
    TH2D *h2_zjt_ptbinned[ptbinsize-2], *h2_zjt_truth_ptbinned[ptbinsize-2], *h2_zjt_ratio_ptbinned[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h3_ptzjt_smear->GetZaxis()->SetRange(j+1, j+1);
        h3_ptzjt_truth->GetZaxis()->SetRange(j+1, j+1);        
        h2_zjt_ptbinned[j-2] = (TH2D *)h3_ptzjt_smear->Project3D(Form("zjt_smear%d_pt%d_yx", i,j));    
        h2_zjt_truth_ptbinned[j-2] = (TH2D *)h3_ptzjt_truth->Project3D(Form("zjt_truth_smear%d_pt%d_yx", i,j));
        h2_zjt_ptbinned[j-2]->GetXaxis()->SetRange(binlowz, binhighz);
        h2_zjt_truth_ptbinned[j-2]->GetXaxis()->SetRange(binlowz, binhighz);
        h2_zjt_ptbinned[j-2]->GetXaxis()->SetTitle("z");
        h2_zjt_truth_ptbinned[j-2]->GetXaxis()->SetTitle("z");
        h2_zjt_ptbinned[j-2]->GetYaxis()->SetRange(binlowjt, binhighjt);
        h2_zjt_truth_ptbinned[j-2]->GetYaxis()->SetRange(binlowjt, binhighjt);
        h2_zjt_ptbinned[j-2]->GetYaxis()->SetTitle("j_{T}");
        h2_zjt_truth_ptbinned[j-2]->GetYaxis()->SetTitle("j_{T}");        
        
        h2_zjt_ptbinned[j-2]->Scale(1./h1_jetpt_final->Integral(j+1, j+1));
        h2_zjt_truth_ptbinned[j-2]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1));
        h2_zjt_ratio_ptbinned[j-2] = (TH2D *)h2_zjt_ptbinned[j-2]->Clone(Form("zjt_ratio_smear%d_pt%d", i,j));
        h2_zjt_ratio_ptbinned[j-2]->Divide(h2_zjt_ptbinned[j-2], h2_zjt_truth_ptbinned[j-2]);     
        h2_zjt_ratio_ptbinned[j-2]->SetOption("COLZ");         
        h2_zjt_ratio_ptbinned[j-2]->Write();                 
    }                      
    
/*    
    if (i == 0)
    {
      h2_zjt_closure_error = (TH2D *)h2_zjt_ratio_smear->Clone("h2_ptzjt_closure_error");
      h2_zjt_closure_error->Reset(); // Reset the histogram to zero
    }
    // h2_ptzjt_closure_error->Add(h2_ptzjt_ratio_smear);
    // Loop over all bins and add in quadrature
    for (int x = 1; x <= h2_zjt_ratio_smear->GetNbinsX(); ++x)
    {
      for (int y = 1; y <= h2_zjt_ratio_smear->GetNbinsY(); ++y)
      {
        for (int z = 1; z <= h2_zjt_ratio_smear->GetNbinsZ(); ++z)
        {
          double binContent = 1. - h2_zjt_ratio_smear->GetBinContent(x, y, z);
          double sumContent = h2_zjt_closure_error->GetBinContent(x, y, z);
          h2_zjt_closure_error->SetBinContent(x, y, z, sumContent + binContent * binContent);

          double binError = 1. - h2_zjt_ratio_smear->GetBinError(x, y, z);
          double sumError = h2_zjt_closure_error->GetBinError(x, y, z);
          h2_zjt_closure_error->SetBinError(x, y, z, sumError + binError * binError);
        }
      }
    }
*/    
  }

/*
  // h2_ptzjt_closure_error->Scale(1.0 / nRuns);
  // Take the square root of the final sum histogram to get the quadrature sum
  for (int x = 1; x <= h2_zjt_closure_error->GetNbinsX(); ++x)
  {
    for (int y = 1; y <= h2_zjt_closure_error->GetNbinsY(); ++y)
    {
      for (int z = 1; z <= h2_zjt_closure_error->GetNbinsZ(); ++z)
      {
        double sumContent = h2_zjt_closure_error->GetBinContent(x, y, z);
        h2_zjt_closure_error->SetBinContent(x, y, z, TMath::Sqrt(sumContent) / TMath::Sqrt(nRuns - 1));

        double sumError = h2_zjt_closure_error->GetBinError(x, y, z);
        h2_zjt_closure_error->SetBinError(x, y, z, TMath::Sqrt(sumError) / TMath::Sqrt(nRuns - 1));
      }
    }
  }
  //GetPullsRatio(h2_zjt_closure_error, h2_zjt_pull_final, h1_zjt_pulldist_final);
  h2_zjt_closure_error->Write();
  //h2_zjt_pull_final->Write();
  //h1_zjt_pulldist_final->Write();  
*/
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create zr histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH2D *h2_zr_truth = (TH2D *)file_truth->Get("zr");
  TH3D *h3_ptzr_truth = (TH3D *)file_truth->Get("ptzr");
  TH3D *h3_ptzr = (TH3D *)file_reco->Get("ptzr");
  TH3D *h3_ptzr_data = (TH3D *)file_data->Get("ptzr");  
  TH3D *h3_ptzr_final = (TH3D *)h3_ptzr->Clone("ptzr_final");
  TH3D *h3_eff_ptzr = (TH3D *)file_unfold->Get("efficiency_ptzr");
  TH3D *h3_purity_ptzr = (TH3D *)file_unfold->Get("purity_ptzr");
  RooUnfoldResponse *response_ptzr = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptzr");
  
  // Multiply by purity  
  h3_ptzr_final->Multiply(h3_ptzr_final, h3_purity_ptzr);
  RooUnfoldBayes unfold_ptzr(response_ptzr, h3_ptzr_final, NumIters);
  h3_ptzr_final = (TH3D *)unfold_ptzr.Hreco();
  // Divide by efficiency  
  h3_ptzr_final->Divide(h3_ptzr_final, h3_eff_ptzr);

  h3_ptzr_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptzr_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);

  h3_ptzr->GetZaxis()->SetRangeUser(ptMin, ptMax);

  TH2D *h2_zr_final = (TH2D *)h3_ptzr_final->Project3D("zr_final_yx");
  TH2D *h2_zr = (TH2D *)h3_ptzr->Project3D("zr_yx");
  TH2D *h2_zr_truth = (TH2D *)h3_ptzr_truth->Project3D("zr_truth_yx");
  //
  h2_zr_final->GetYaxis()->SetRange(binlowr, binhighr);
  h2_zr_final->GetXaxis()->SetRange(binlowz, binhighz);
  h2_zr_truth->GetYaxis()->SetRange(binlowr, binhighr);
  h2_zr_truth->GetXaxis()->SetRange(binlowz, binhighz);
  
  
  // This will depend on results of 1D jet unfolding
  h2_zr_final->Scale(1. / Njets_final, "width");  
  h2_zr_truth->Scale(1. / Njets_truth, "width");

  TH2D *h2_zr_ratio = (TH2D *)h2_zr->Clone("h2_zr_ratio");
  TH2D *h2_zr_ratio_final = (TH2D *)h2_zr->Clone("h2_zr_ratio_final");
  //TH2D *h2_zr_pull_final = (TH2D *)h2_zr->Clone("h2_zr_pull_final");

  //TH2D *h2_zr_pull = (TH2D *)h2_zr_truth->Clone("zr_pull");

  //TH1D *h1_zr_pulldist = new TH1D("zr_pulldist", "", 20, -4.5, 4.5);
  //TH1D *h1_zr_pulldist_final = new TH1D("zr_pulldist_final", "", 20, -4.5, 4.5);
  //TH1D *h1_ptzr_pulldist_vecfinal = new TH1D("ptzr_pulldist_vecfinal", "", 20, -4.5, 4.5);

  h2_zr_ratio->Divide(h2_zr, h2_zr_truth);
  h2_zr_ratio_final->Divide(h2_zr_final, h2_zr_truth);

  h2_zr_ratio_final->GetYaxis()->SetRange(binlowr, binhighr);
  h2_zr_ratio_final->GetXaxis()->SetRange(binlowz, binhighz);

  //h2_zr_pull_final->GetYaxis()->SetRange(binlowr, binhighr);
  //h2_zr_pull_final->GetXaxis()->SetRange(binlowz, binhighz);

  //GetPullsRatio(h2_zr_ratio, h2_zr_pull, h1_zr_pulldist);
  //GetPullsRatio(h2_zr_ratio_final, h2_zr_pull_final, h1_zr_pulldist_final);

  //double zr_pullperf1 = GetPullPerformance(h2_zr_pull, 1);
  //double zr_pullperf2 = GetPullPerformance(h2_zr_pull, 2);

  //double zr_pullperf1_final = GetPullPerformance(h2_zr_pull_final, 1);
  //double zr_pullperf2_final = GetPullPerformance(h2_zr_pull_final, 2);
  h2_zr_ratio_final->SetOption("COLZ");  
  h2_zr_ratio_final->Write();

  /*  
  h2_zr_pull->Write();  
  h2_zr_pull_final->Write();
  h1_zr_pulldist->Write();
  h1_zr_pulldist_final->Write();  
  */
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH2D *h2_zr_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH3D *h3_ptzr_smear = (TH3D *)h3_ptzr->Clone(Form("ptzr_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h3_ptzr_smear, h3_ptzr_data, myRNG);
    // Multiply by purity
    h3_ptzr_smear->Multiply(h3_ptzr_smear, h3_purity_ptzr);
    RooUnfoldBayes unfold_ptzr_smear(response_ptzr, h3_ptzr_smear, NumIters);

    h3_ptzr_smear = (TH3D *)unfold_ptzr_smear.Hreco();
    // Divide by efficiency
    h3_ptzr_smear->Divide(h3_ptzr_smear, h3_eff_ptzr);
    h3_ptzr_smear->GetZaxis()->SetRangeUser(ptMin, ptMax);

    TH2D *h2_zr_smear = (TH2D *)h3_ptzr_smear->Project3D(Form("zr_smear%d_yx", i));

    h2_zr_smear->GetYaxis()->SetRange(binlowr, binhighr);
    h2_zr_smear->GetXaxis()->SetRange(binlowz, binhighz);
    h2_zr_smear->Scale(1. / Njets_final, "width");
    TH2D *h2_zr_ratio_smear = (TH2D *)h2_zr_smear->Clone(Form("zr_ratio_smear%d", i));
    //TH2D *h2_zr_pull_smear = (TH2D *)h2_zr_smear->Clone(Form("h2_zr_pull_smear%d", i));
    h2_zr_ratio_smear->Divide(h2_zr_smear, h2_zr_truth); 

    h2_zr_ratio_smear->GetYaxis()->SetRange(binlowr, binhighr);
    h2_zr_ratio_smear->GetXaxis()->SetRange(binlowz, binhighz);

    //h2_zr_pull_smear->GetYaxis()->SetRange(binlowr, binhighr);
    //h2_zr_pull_smear->GetXaxis()->SetRange(binlowz, binhighz);
    h2_zr_ratio_smear->SetOption("COLZ");
    h2_zr_ratio_smear->Write();      
    //h2_zr_pull_smear->Write();   
    
    TH2D *h2_zr_ptbinned[ptbinsize-2], *h2_zr_truth_ptbinned[ptbinsize-2], *h2_zr_ratio_ptbinned[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h3_ptzr_smear->GetZaxis()->SetRange(j+1, j+1);
        h3_ptzr_truth->GetZaxis()->SetRange(j+1, j+1);        
        h2_zr_ptbinned[j-2] = (TH2D *)h3_ptzr_smear->Project3D(Form("zr_smear%d_pt%d_yx", i,j));    
        h2_zr_truth_ptbinned[j-2] = (TH2D *)h3_ptzr_truth->Project3D(Form("zr_truth_smear%d_pt%d_yx", i,j));
        h2_zr_ptbinned[j-2]->GetXaxis()->SetRange(binlowz, binhighz);
        h2_zr_truth_ptbinned[j-2]->GetXaxis()->SetRange(binlowz, binhighz);
        h2_zr_ptbinned[j-2]->GetXaxis()->SetTitle("z");
        h2_zr_truth_ptbinned[j-2]->GetXaxis()->SetTitle("z");
        h2_zr_ptbinned[j-2]->GetYaxis()->SetRange(binlowr, binhighr);
        h2_zr_truth_ptbinned[j-2]->GetYaxis()->SetRange(binlowr, binhighr);
        h2_zr_ptbinned[j-2]->GetYaxis()->SetTitle("r");
        h2_zr_truth_ptbinned[j-2]->GetYaxis()->SetTitle("r");        
        
        h2_zr_ptbinned[j-2]->Scale(1./h1_jetpt_final->Integral(j+1, j+1));
        h2_zr_truth_ptbinned[j-2]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1));
        h2_zr_ratio_ptbinned[j-2] = (TH2D *)h2_zr_ptbinned[j-2]->Clone(Form("zr_ratio_smear%d_pt%d", i,j));
        h2_zr_ratio_ptbinned[j-2]->Divide(h2_zr_ptbinned[j-2], h2_zr_truth_ptbinned[j-2]);     
        h2_zr_ratio_ptbinned[j-2]->SetOption("COLZ");         
        h2_zr_ratio_ptbinned[j-2]->Write();                 
    }         
                     
/*
    if (i == 0)
    {
      h2_zr_closure_error = (TH2D *)h2_zr_ratio_smear->Clone("h2_ptzr_closure_error");
      h2_zr_closure_error->Reset(); // Reset the histogram to zero
    }
    // h2_ptzr_closure_error->Add(h2_ptzr_ratio_smear);
    // Loop over all bins and add in quadrature
    for (int x = 1; x <= h2_zr_ratio_smear->GetNbinsX(); ++x)
    {
      for (int y = 1; y <= h2_zr_ratio_smear->GetNbinsY(); ++y)
      {
        for (int z = 1; z <= h2_zr_ratio_smear->GetNbinsZ(); ++z)
        {
          double binContent = 1. - h2_zr_ratio_smear->GetBinContent(x, y, z);
          double sumContent = h2_zr_closure_error->GetBinContent(x, y, z);
          h2_zr_closure_error->SetBinContent(x, y, z, sumContent + binContent * binContent);

          double binError = 1. - h2_zr_ratio_smear->GetBinError(x, y, z);
          double sumError = h2_zr_closure_error->GetBinError(x, y, z);
          h2_zr_closure_error->SetBinError(x, y, z, sumError + binError * binError);
        }
      }
    }
*/    
  }
/*
  // h2_ptzr_closure_error->Scale(1.0 / nRuns);
  // Take the square root of the final sum histogram to get the quadrature sum
  for (int x = 1; x <= h2_zr_closure_error->GetNbinsX(); ++x)
  {
    for (int y = 1; y <= h2_zr_closure_error->GetNbinsY(); ++y)
    {
      for (int z = 1; z <= h2_zr_closure_error->GetNbinsZ(); ++z)
      {
        double sumContent = h2_zr_closure_error->GetBinContent(x, y, z);
        h2_zr_closure_error->SetBinContent(x, y, z, TMath::Sqrt(sumContent) / TMath::Sqrt(nRuns - 1));

        double sumError = h2_zr_closure_error->GetBinError(x, y, z);
        h2_zr_closure_error->SetBinError(x, y, z, TMath::Sqrt(sumError) / TMath::Sqrt(nRuns - 1));
      }
    }
  }
  //GetPullsRatio(h2_zr_closure_error, h2_zr_pull_final, h1_zr_pulldist_final);
  h2_zr_closure_error->Write();
  //h2_zr_pull_final->Write();
  //h1_zr_pulldist_final->Write();  
*/  
  
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////   Create jtr histograms /////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////

  //TH2D *h2_jtr_truth = (TH2D *)file_truth->Get("jtr");
  TH3D *h3_ptjtr_truth = (TH3D *)file_truth->Get("ptjtr");
  TH3D *h3_ptjtr = (TH3D *)file_reco->Get("ptjtr");
  TH3D *h3_ptjtr_data = (TH3D *)file_data->Get("ptjtr");  
  TH3D *h3_ptjtr_final = (TH3D *)h3_ptjtr->Clone("ptjtr_final");
  TH3D *h3_eff_ptjtr = (TH3D *)file_unfold->Get("efficiency_ptjtr");
  TH3D *h3_purity_ptjtr = (TH3D *)file_unfold->Get("purity_ptjtr");
  RooUnfoldResponse *response_ptjtr = (RooUnfoldResponse *)file_unfold->Get("Roo_response_ptjtr");
  
  // Multiply by purity  
  h3_ptjtr_final->Multiply(h3_ptjtr_final, h3_purity_ptjtr);
  RooUnfoldBayes unfold_ptjtr(response_ptjtr, h3_ptjtr_final, NumIters);

  h3_ptjtr_final = (TH3D *)unfold_ptjtr.Hreco();
  // Divide by efficiency  
  h3_ptjtr_final->Divide(h3_ptjtr_final, h3_eff_ptjtr);

  h3_ptjtr_final->GetZaxis()->SetRangeUser(ptMin, ptMax);
  h3_ptjtr_truth->GetZaxis()->SetRangeUser(ptMin, ptMax);

  h3_ptjtr->GetZaxis()->SetRangeUser(ptMin, ptMax);

  TH2D *h2_jtr_final = (TH2D *)h3_ptjtr_final->Project3D("jtr_final_yx");
  TH2D *h2_jtr = (TH2D *)h3_ptjtr->Project3D("jtr_yx");
  TH2D *h2_jtr_truth = (TH2D *)h3_ptjtr_truth->Project3D("jtr_truth_yx");
  //
  h2_jtr_final->GetYaxis()->SetRange(binlowr, binhighr);
  h2_jtr_final->GetXaxis()->SetRange(binlowjt, binhighjt);
  h2_jtr_truth->GetYaxis()->SetRange(binlowr, binhighr);
  h2_jtr_truth->GetXaxis()->SetRange(binlowjt, binhighjt);
  
  
  // This will depend on results of 1D jet unfolding
  h2_jtr_final->Scale(1. / Njets_final, "width");
  h2_jtr_truth->Scale(1. / Njets_truth, "width");

  TH2D *h2_jtr_ratio = (TH2D *)h2_jtr->Clone("h2_jtr_ratio");
  TH2D *h2_jtr_ratio_final = (TH2D *)h2_jtr->Clone("h2_jtr_ratio_final");
  /*
  TH2D *h2_jtr_pull_final = (TH2D *)h2_jtr->Clone("h2_jtr_pull_final");

  TH2D *h2_jtr_pull = (TH2D *)h2_jtr_truth->Clone("jtr_pull");

  TH1D *h1_jtr_pulldist = new TH1D("jtr_pulldist", "", 20, -4.5, 4.5);
  TH1D *h1_jtr_pulldist_final = new TH1D("jtr_pulldist_final", "", 20, -4.5, 4.5);
  //TH1D *h1_ptjtr_pulldist_vecfinal = new TH1D("ptjtr_pulldist_vecfinal", "", 20, -4.5, 4.5);
  */
  h2_jtr_ratio->Divide(h2_jtr, h2_jtr_truth);
  h2_jtr_ratio_final->Divide(h2_jtr_final, h2_jtr_truth);

  h2_jtr_ratio_final->GetYaxis()->SetRange(binlowr, binhighr);
  h2_jtr_ratio_final->GetXaxis()->SetRange(binlowjt, binhighjt);
  /*
  h2_jtr_pull_final->GetYaxis()->SetRange(binlowr, binhighr);
  h2_jtr_pull_final->GetXaxis()->SetRange(binlowjt, binhighjt);

  GetPullsRatio(h2_jtr_ratio, h2_jtr_pull, h1_jtr_pulldist);
  GetPullsRatio(h2_jtr_ratio_final, h2_jtr_pull_final, h1_jtr_pulldist_final);

  double jtr_pullperf1 = GetPullPerformance(h2_jtr_pull, 1);
  double jtr_pullperf2 = GetPullPerformance(h2_jtr_pull, 2);

  double jtr_pullperf1_final = GetPullPerformance(h2_jtr_pull_final, 1);
  double jtr_pullperf2_final = GetPullPerformance(h2_jtr_pull_final, 2);
  */
  h2_jtr_ratio_final->SetOption("COLZ");  
  h2_jtr_ratio_final->Write();
  /*  
  h2_jtr_pull->Write();  
  h2_jtr_pull_final->Write();
  h1_jtr_pulldist->Write();
  h1_jtr_pulldist_final->Write();  
  */
  
  ////////////////////////////////////
  // Smearing the Observables
  ///////////////////////////////////
  TH2D *h2_jtr_closure_error;
  for (int i = 0; i < nRuns; i++)
  {
    TH3D *h3_ptjtr_smear = (TH3D *)h3_ptjtr->Clone(Form("ptjtr_smear%d", i));
    //myRNG->SetSeed(time(0));
    myRNG->SetSeed(fixSmear);
    SmearObservables(h3_ptjtr_smear, h3_ptjtr_data, myRNG);
    // Multiply by purity
    h3_ptjtr_smear->Multiply(h3_ptjtr_smear, h3_purity_ptjtr);
    RooUnfoldBayes unfold_ptjtr_smear(response_ptjtr, h3_ptjtr_smear, NumIters);

    h3_ptjtr_smear = (TH3D *)unfold_ptjtr_smear.Hreco();
    // Divide by efficiency
    h3_ptjtr_smear->Divide(h3_ptjtr_smear, h3_eff_ptjtr);
    h3_ptjtr_smear->GetZaxis()->SetRangeUser(ptMin, ptMax);

    TH2D *h2_jtr_smear = (TH2D *)h3_ptjtr_smear->Project3D(Form("jtr_smear%d_yx", i));

    h2_jtr_smear->GetYaxis()->SetRange(binlowr, binhighr);
    h2_jtr_smear->GetXaxis()->SetRange(binlowjt, binhighjt);
    h2_jtr_smear->Scale(1. / Njets_final, "width");
    TH2D *h2_jtr_ratio_smear = (TH2D *)h2_jtr_smear->Clone(Form("jtr_ratio_smear%d", i));
    //TH2D *h2_jtr_pull_smear = (TH2D *)h2_jtr_smear->Clone(Form("h2_jtr_pull_smear%d", i));
    h2_jtr_ratio_smear->Divide(h2_jtr_smear, h2_jtr_truth); 

    h2_jtr_ratio_smear->GetYaxis()->SetRange(binlowr, binhighr);
    h2_jtr_ratio_smear->GetXaxis()->SetRange(binlowjt, binhighjt);

    //h2_jtr_pull_smear->GetYaxis()->SetRange(binlowr, binhighr);
    //h2_jtr_pull_smear->GetXaxis()->SetRange(binlowjt, binhighjt);
    h2_jtr_ratio_smear->SetOption("COLZ");
    h2_jtr_ratio_smear->Write();      
    //h2_jtr_pull_smear->Write();     
    
    TH2D *h2_jtr_ptbinned[ptbinsize-2], *h2_jtr_truth_ptbinned[ptbinsize-2], *h2_jtr_ratio_ptbinned[ptbinsize-2];
    for (int j=2; j < ptbinsize; ++j)
    {
        h3_ptjtr_smear->GetZaxis()->SetRange(j+1, j+1);
        h3_ptjtr_truth->GetZaxis()->SetRange(j+1, j+1);        
        h2_jtr_ptbinned[j-2] = (TH2D *)h3_ptjtr_smear->Project3D(Form("jtr_smear%d_pt%d_yx", i,j));    
        h2_jtr_truth_ptbinned[j-2] = (TH2D *)h3_ptjtr_truth->Project3D(Form("jtr_truth_smear%d_pt%d_yx", i,j));
        h2_jtr_ptbinned[j-2]->GetXaxis()->SetRange(binlowjt, binhighjt);
        h2_jtr_truth_ptbinned[j-2]->GetXaxis()->SetRange(binlowjt, binhighjt);
        h2_jtr_ptbinned[j-2]->GetXaxis()->SetTitle("j_{T}");
        h2_jtr_truth_ptbinned[j-2]->GetXaxis()->SetTitle("j_{T}");
        h2_jtr_ptbinned[j-2]->GetYaxis()->SetRange(binlowr, binhighr);
        h2_jtr_truth_ptbinned[j-2]->GetYaxis()->SetRange(binlowr, binhighr);
        h2_jtr_ptbinned[j-2]->GetYaxis()->SetTitle("r");
        h2_jtr_truth_ptbinned[j-2]->GetYaxis()->SetTitle("r");        
        
        h2_jtr_ptbinned[j-2]->Scale(1./h1_jetpt_final->Integral(j+1, j+1));
        h2_jtr_truth_ptbinned[j-2]->Scale(1./h1_jetpt_truth->Integral(j+1, j+1));
        h2_jtr_ratio_ptbinned[j-2] = (TH2D *)h2_jtr_ptbinned[j-2]->Clone(Form("jtr_ratio_smear%d_pt%d", i,j));
        h2_jtr_ratio_ptbinned[j-2]->Divide(h2_jtr_ptbinned[j-2], h2_jtr_truth_ptbinned[j-2]);     
        h2_jtr_ratio_ptbinned[j-2]->SetOption("COLZ");         
        //h2_jtr_ratio_ptbinned[j-2]->Write(Form("zjt_ratio_smear%d_pt%d", i,j));
        h2_jtr_ratio_ptbinned[j-2]->Write();                 
    }                        
/*
    if (i == 0)
    {
      h2_jtr_closure_error = (TH2D *)h2_jtr_ratio_smear->Clone("h2_ptjtr_closure_error");
      h2_jtr_closure_error->Reset(); // Reset the histogram to zero
    }
    // h2_ptjtr_closure_error->Add(h2_ptjtr_ratio_smear);
    // Loop over all bins and add in quadrature
    for (int x = 1; x <= h2_jtr_ratio_smear->GetNbinsX(); ++x)
    {
      for (int y = 1; y <= h2_jtr_ratio_smear->GetNbinsY(); ++y)
      {
        for (int z = 1; z <= h2_jtr_ratio_smear->GetNbinsZ(); ++z)
        {
          double binContent = 1. - h2_jtr_ratio_smear->GetBinContent(x, y, z);
          double sumContent = h2_jtr_closure_error->GetBinContent(x, y, z);
          h2_jtr_closure_error->SetBinContent(x, y, z, sumContent + binContent * binContent);

          double binError = 1. - h2_jtr_ratio_smear->GetBinError(x, y, z);
          double sumError = h2_jtr_closure_error->GetBinError(x, y, z);
          h2_jtr_closure_error->SetBinError(x, y, z, sumError + binError * binError);
        }
      }
    }
*/    
  }
/*
  // h2_ptjtr_closure_error->Scale(1.0 / nRuns);
  // Take the square root of the final sum histogram to get the quadrature sum
  for (int x = 1; x <= h2_jtr_closure_error->GetNbinsX(); ++x)
  {
    for (int y = 1; y <= h2_jtr_closure_error->GetNbinsY(); ++y)
    {
      for (int z = 1; z <= h2_jtr_closure_error->GetNbinsZ(); ++z)
      {
        double sumContent = h2_jtr_closure_error->GetBinContent(x, y, z);
        h2_jtr_closure_error->SetBinContent(x, y, z, TMath::Sqrt(sumContent) / TMath::Sqrt(nRuns - 1));

        double sumError = h2_jtr_closure_error->GetBinError(x, y, z);
        h2_jtr_closure_error->SetBinError(x, y, z, TMath::Sqrt(sumError) / TMath::Sqrt(nRuns - 1));
      }
    }
  }
  //GetPullsRatio(h2_jtr_closure_error, h2_jtr_pull_final, h1_jtr_pulldist_final);
  h2_jtr_closure_error->Write();
  //h2_jtr_pull_final->Write();
  //h1_jtr_pulldist_final->Write();   
  
  */
  
  /*

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================jt Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzjt_pullperf1 << " %"
       << " --- " << ptzjt_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzjt_pullperf1_final << " %"
       << " --- " << ptzjt_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_z << " iterations:" << endl;
  cout << "=======================zdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzdR_pullperf1 << " %"
       << " --- " << ptzdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzdR_pullperf1_final << " %"
       << " --- " << ptzdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;

  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzjt_ratio_final) << endl;
  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzdR_ratio_final) << endl;

  //---- paint setup...
  //
  int ican = -1, iframe = -1, itext = -1;
  TCanvas *ccan[1000];
  TH1F *frame[1000];
  TLatex *text[1000];
  TRatioPlot *rp[1000];
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
  gStyle->SetOptStat(0);
  // gStyle->SetPaperSize(TStyle::kUSLetter);
  // gStyle->SetPadBottomMargin(0.08);
  // gStyle->SetPadTopMargin(0.005);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetLabelSize(0.05, "X");
  gStyle->SetLabelSize(0.05, "Y");
  gStyle->SetTitleXSize(0.055);
  gStyle->SetTitleYSize(0.055);
  gStyle->SetTitleOffset(0.55, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetStatW(0.2);
  // gStyle->SetPalette(kBird);
  gStyle->SetPalette(kBird);
  gStyle->SetNumberContours(100);
  gStyle->SetPaintTextFormat("4.3g");
  // gStyle->SetErrorX(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetStatStyle(0);
  // gStyle->SetLineWidth(3);

  //---- paint...
  char buf[100];
  char bufb[100];
  TString rootfile;
  TString plotfile;
  TString plotfilePDF;
  TString plotfileO;
  TString plotfileC;
  // TString OutputFileBase	= outbase+outinfo;
  rootfile = loc_hists + extension + TString(".root");
  plotfile = loc_plots + extension + TString(".ps");
  plotfilePDF = loc_plots + extension + TString(".pdf");
  plotfileO = plotfilePDF + TString("(");
  plotfileC = plotfilePDF + TString("]");
  // c->SaveAs("plots/"+extension+".pdf");

 

  cout << (Njets_truth - Njets_final) / Njets_truth * 100 << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_kt << " iterations:" << endl;
  cout << "=======================zjt Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzjt_pullperf1 << " %"
       << " --- " << ptzjt_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzjt_pullperf1_final << " %"
       << " --- " << ptzjt_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;
  cout << "For " << NumIters_z << " iterations:" << endl;
  cout << "=======================zdR Pull Performance====================================" << endl;
  cout << "Uncorrected = " << ptzdR_pullperf1 << " %"
       << " --- " << ptzdR_pullperf2 << " %" << endl;
  cout << "Purity + IDS + Eff = " << ptzdR_pullperf1_final << " %"
       << " --- " << ptzdR_pullperf2_final << " %" << endl;

  cout << "===========================================================" << endl;

  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzjt_ratio_final) << endl;
  cout << "Averaged Rel. Unc. = " << GetWeightedAverage(h2_ptzdR_ratio_final) << endl;

  // TFile *file_save = new TFile("hists/HFpt_Correction.root", "RECREATE");
  // h2_correct_HFptjetpt->Write("h2_correct_HFptjetpt");
  // file_save->Close();
*/



  //file_write->Write();
  file_write->Close();
  //
}
