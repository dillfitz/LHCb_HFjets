

//#include "AnalyzeDijetData_withsubsets.h"
//#include "LundPlaneData.h"



// #include "HFjetLuC"

#include <TCanvas.h>
#include <vector>
#include <iostream>
#include "../Settings.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "../LundGen.hh"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooRealSumFunc.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooArgusBG.h"
#include "RooFFTConvPdf.h"
#include "RooAbsAnaConvPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"

using namespace fastjet;
using namespace std;
using namespace RooFit;



void MassFit(int NumEvts = 10000, int dataset = 1510,bool isData = true,
               bool chargedJetCut_user = false){

  bool MCflag = !isData;
  followHardest = false;
  truthLevel = false;
  chargedJetCut = chargedJetCut_user;
  if(truthLevel){
    ghostCut = false;

  }


  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;

  if (flavor == 5) {
    mass_num = 4.2;
    HF_pdgcode = 521;
  }
  else if (flavor == 4) {
    mass_num = 1.25;
    HF_pdgcode = 421;
  }
  else if (flavor == 1) {
    mass_num = 0.001;
    followHardest = true;
  }
  //
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

  if(Mag == 0) str_Mag = "_MD";
  else if (Mag == 1) str_Mag = "_MU";

  if(flavor == 1) str_flavor = "_udsg";
  else if(flavor == 4) str_flavor = "_c";
  else if(flavor == 5) str_flavor = "_b";

  // if(ptRange == 0) str_pT = "pt15pt20";
  // else if(ptRange == 1) str_pT = "pt20pt50";
  // else if(ptRange == 2) str_pT = "pt50";

  if(isData) str_level = "data";
  else{
    if(truthLevel) str_level = "truth";
    else str_level = "reco";
  }


  if(flavor == 1) str_followHard = "_hard";
  else{
    if(followHardest) str_followHard = "_hard";
    else str_followHard = "_HF";
  }



  if(ghostCut) str_ghost = Form("_ghost_%.1f", ghostProb);

  if(chargedJetCut) str_charged = "_charge";
  // TString str_trees[5];
  // str_trees[0] = "TaggedDijets/DecayTree";
  // str_trees[1] = "D0KPiJet/DecayTree";
  // str_trees[2] = "B0KPiJet/DecayTree";
  // str_trees[3] = "Jets/DecayTree";
  TString str_tree;



  TString extension;
  extension = TString("massfit_") + str_level + Form("_ev_%d", NumEvts)
            + Form("_ptj_%d%d", int(ptMin), int(ptMax))
            + Form("_eta_%.1f%.1f", etaMin, etaMax)
            +  str_ghost +str_charged + str_Mag
            + str_flavor +  Form("_%d", dataset);



  // HFjetTree Tree(0, dataset, isData);


  // int NumEvts = 0;
  // cout <<"Choose number of events (-1: All Events, or enter integer): ";
  // cin>> NumEvts;
  TString extension_read;
  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts)
            + Form("_eta_%.1f%.1f", etaMin, etaMax)
            +  str_followHard
            +  str_ghost +str_charged + str_Mag
            + str_flavor +  Form("_%d", dataset);

  TFile fread("hists/"+ extension_read+".root", "READ");
  TTree* LundTree = (TTree*)fread.Get("LundTree");
  if(NumEvts > LundTree->GetEntries())  NumEvts = LundTree->GetEntries();
  if (NumEvts == -1) NumEvts = LundTree->GetEntries();
  cout<<LundTree->GetEntries()<<endl;

  TString dir_deadcone("$LUND/Djets/");

  TFile f(dir_deadcone+"hists/"+ extension+".root", "RECREATE");



  double jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  double jet_rap, tr_jet_rap;
  double jet_px, jet_py, jet_pz, jet_e;
  double Z_px, Z_py, Z_pz, Z_e;
  double pi_px, pi_py, pi_pz, pi_e;
  double K_px, K_py, K_pz, K_e;

  double tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  double tr_pi_px, tr_pi_py, tr_pi_pz, tr_pi_e;
  double tr_K_px, tr_K_py, tr_K_pz, tr_K_e;

  int nsplits, ndtrs;
  double D0_ipchi2;
  int tr_nsplits, tr_ndtrs;
  // TLorentzVector

  LundTree->SetBranchAddress("jet_pt",&jet_pt);
  LundTree->SetBranchAddress("jet_eta",&jet_eta);
  LundTree->SetBranchAddress("jet_rap",&jet_rap);

  LundTree->SetBranchAddress("jet_px",&jet_px);
  LundTree->SetBranchAddress("jet_py",&jet_py);
  LundTree->SetBranchAddress("jet_pz",&jet_pz);
  LundTree->SetBranchAddress("jet_e",&jet_e);

  LundTree->SetBranchAddress("ndtrs", &ndtrs);
  LundTree->SetBranchAddress("nsplits", &nsplits);
  LundTree->SetBranchAddress("D0_ipchi2", &D0_ipchi2);

  LundTree->SetBranchAddress("pi_px",&pi_px);
  LundTree->SetBranchAddress("pi_py",&pi_py);
  LundTree->SetBranchAddress("pi_pz",&pi_pz);
  LundTree->SetBranchAddress("pi_e",&pi_e);

  LundTree->SetBranchAddress("K_px",&K_px);
  LundTree->SetBranchAddress("K_py",&K_py);
  LundTree->SetBranchAddress("K_pz",&K_pz);
  LundTree->SetBranchAddress("K_e",&K_e);

  LundTree->SetBranchAddress("tr_jet_pt",&tr_jet_pt);
  LundTree->SetBranchAddress("tr_jet_eta",&tr_jet_eta);
  LundTree->SetBranchAddress("tr_jet_rap",&tr_jet_rap);

  LundTree->SetBranchAddress("tr_jet_px",&tr_jet_px);
  LundTree->SetBranchAddress("tr_jet_py",&tr_jet_py);
  LundTree->SetBranchAddress("tr_jet_pz",&tr_jet_pz);
  LundTree->SetBranchAddress("tr_jet_e",&tr_jet_e);

  LundTree->SetBranchAddress("tr_pi_px",&tr_pi_px);
  LundTree->SetBranchAddress("tr_pi_py",&tr_pi_py);
  LundTree->SetBranchAddress("tr_pi_pz",&tr_pi_pz);
  LundTree->SetBranchAddress("tr_pi_e",&tr_pi_e);

  LundTree->SetBranchAddress("tr_K_px",&tr_K_px);
  LundTree->SetBranchAddress("tr_K_py",&tr_K_py);
  LundTree->SetBranchAddress("tr_K_pz",&tr_K_pz);
  LundTree->SetBranchAddress("tr_K_e",&tr_K_e);

  LundTree->SetBranchAddress("tr_ndtrs", &tr_ndtrs);
  LundTree->SetBranchAddress("tr_nsplits", &tr_nsplits);



  int fitn = 1; ///DEFAULT - NO PRIOR FITTING (FASTEST)

  int nBins = 120; ///NUMBER OF BINS - UP TO YOU.  NOTE: MORE BINS = MORE DETAILED DISTRIBUTION BUT LARGER UNCERTAINTIES; LESS BINS = BETTER UNCERTAINTIES BUT WORSE RESOLUTION
  Double_t rho = 1.; ///WIDTH OF GAUSSIANS USED IN REGRESSION FIT OF COMBINATORIC BACKGROUND
  double MM = 1.865;
  double M_sigma = 0.0075;
	double WM = 7.*M_sigma;
	double DM = 0.015;
  double ipchi2_max = 5.;

  TH1D * hchi2 = new TH1D ("hchi2", "hchi2", nBins, -3., 5.);
  TH1D * hchi2_bkg = new TH1D ("hchi2_bkg", "hchi2", nBins, -3., 5.);
  TH1D * h1_mass = new TH1D("h1_mass", "h1_mass", nBins, MM-WM, MM+WM);


  int eventNum;
  cout<<"Requested # of events"<<NumEvts<<endl;
  for(int ev = 0; ev < NumEvts; ev++)
  {
    LundTree->GetEntry(ev);

    if (ev%10000==0) cout<<"Executing event "<<ev<<endl;

  TLorentzVector HFmeson, HFjet, pi, Kmeson, Jpsi;
  TLorentzVector tr_HFmeson, tr_HFjet, tr_pi, tr_Kmeson, tr_Jpsi;
  HFjet.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
  pi.SetPxPyPzE(pi_px, pi_py, pi_pz, pi_e);
  Kmeson.SetPxPyPzE(K_px, K_py, K_pz, K_e);
  HFmeson = pi+Kmeson;

  tr_HFjet.SetPxPyPzE(tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e);
  tr_pi.SetPxPyPzE(tr_pi_px, tr_pi_py, tr_pi_pz, tr_pi_e);
  tr_Kmeson.SetPxPyPzE(tr_K_px, tr_K_py, tr_K_pz, tr_K_e);
  tr_HFmeson = tr_pi+tr_Kmeson;

  double dphi_HF_jet = checkphi(checkphi(HFmeson.Phi()) - checkphi(HFjet.Phi()));
  double dy_HF_jet = HFjet.Eta() - HFmeson.Rapidity();

  if(jet_pt < ptMin) continue;
  if(HFmeson.M() < MM - WM || HFmeson.M() > MM + WM) continue;
  // cout<<log10(D0_ipchi2);
  bool bkg_cond = (HFmeson.M() > MM - 7.*M_sigma && HFmeson.M() < MM - 5.*M_sigma) || (HFmeson.M() < MM + 7*M_sigma && HFmeson.M() > MM + 5.*M_sigma) ;
  // bool bkg_cond = HFmeson.M() < MM - WM || HFmeson.M() > MM + WM;
  if(bkg_cond){
    hchi2_bkg->Fill(log10(D0_ipchi2));
  }
  hchi2->Fill(log10(D0_ipchi2));
  if(log10(D0_ipchi2) > ipchi2_max) continue;
  h1_mass->Fill(HFmeson.M());

  }


  // TFile * f = TFile::Open("/nfs/turbo/lsa-caidala/dshangas/LHCb_MCData/Lambda/Lambda.root"); ///CHANGE FOR D0 DATA
  // TTree * t2 = (TTree *) f->Get("DecayTree"); ///
  TLatex latex;
  ///fitn SELECTS STRATEGY FOR FITTING OF COMBINATORIC BACKGROUND///
  //int fitn = 1; ///FIT TO BACKGROUND WITH INITIAL HESSE TURNED ON
  //int fitn = 0; ///STANDARD FIT TO BACKGROUND

  // TString cuts("(nPV == 1) && (PVZ > -60) && (PVZ < 120) "); ///CHANGE
  //cout << cuts << endl;
  // TString cuts_bg = cuts + " && ((D0_M > 1125) || (D0_M < 1106))"; ///CHANGE FOR D0 MASS SIDEBAND
  TCanvas * cm = new TCanvas("cm", "c", 700, 900);
  cm->Divide(1, 2);
  cm->cd(1);
  ////////Chi2 Distributions////////
  RooRealVar HFMass("HFMass","HFMass",MM-WM, MM+WM); ///LOG(CHI_IP^2) VARIABLE THAT IS FED INTO ROOFIT FUNCTIONS
  HFMass.setBins(nBins);
  RooDataHist D0Mass("D0Mass", "D0Mass", RooArgList(HFMass), h1_mass, 1.);

  RooRealVar Mean("Mean","",MM,MM-DM,MM+DM);
	RooRealVar CBS("CBS","CBS",DM/2.,4./1000.,DM);
	RooRealVar n("n","n",1.);
	RooRealVar a("a","a",2.,1.,5.);
	RooCBShape sig1("cb", "Signal",HFMass,Mean,CBS,a,n);

  //Sigma,f,a are obtained from fit for kinematically unbinned data, and I do the fit outside the file.
	// RooFormulaVar Sigma("Sigma","1.647*CBS",RooArgSet(CBS));
  RooRealVar Sigma("Sigma", "Sigma", DM/2.,6./1000., DM);
	RooGaussian gaus("gaus","",HFMass,Mean,Sigma);
	RooRealVar frac("frac","",0.1,0.,0.999);

	// f.setVal(0.667);f.setConstant();
	// a.setVal(2.444);a.setConstant();
	RooAddPdf sig("sig","gau1+gau2",RooArgSet(sig1,gaus),RooArgSet(frac));

  RooRealVar ns("ns","nSignal", 5000.,0.,1000000.);
	RooExtendPdf sign("sign","sign",sig,ns);

	//BKG component
	RooRealVar p("p","p",-0.,-1./(MM+WM),1./(MM+WM));
	RooPolynomial bkg("bkg","bkg",HFMass,RooArgSet(p));
	RooRealVar nb("nb","nBKG",500.,0.,10000000);
	RooExtendPdf bkgn("bkgn","bkgn",bkg,nb);

  //sig+bkg
	RooAddPdf model("model","sig+bkg",RooArgSet(bkgn,sign));
  model.fitTo(D0Mass);

 /////////////////Plotting/////////////////
 double binsize = (MM+WM - (MM-WM))/(double) nBins;
 RooPlot *xframe = HFMass.frame(Title(Form(";M_{K#pi} [GeV];Events/(%.1f MeV) ", binsize*1000.)));
 D0Mass.plotOn(xframe, Name("D0Mass"));

 model.plotOn(xframe, Name("bkgn"), Components(bkgn),LineColor(kBlue), LineStyle(kDashed),PrintEvalErrors(-1));
 model.plotOn(xframe, Name("sign"), Components(sign),LineColor(kGreen), LineStyle(5), PrintEvalErrors(-1));
 model.plotOn(xframe,Name("model"), LineColor(kRed), PrintEvalErrors(-1));
 double chi2ndf = xframe->chiSquare(11);
 // model.plotOn(xframe, Components(sec), FillColor(kRed), FillStyle(3002), DrawOption("F"),PrintEvalErrors(-1));
 // model.plotOn(xframe, Components(comb), FillColor(kGreen+2), FillStyle(3003), DrawOption("F"),PrintEvalErrors(-1));
 xframe->Draw("SAME");
 TLegend *leg1 = new TLegend(0.65,0.6,0.86,0.87);
  // leg1->SetFillColor(kWhite);
  // leg1->SetLineColor(kWhite);
  leg1->SetBorderSize(0);
  leg1->AddEntry("D0Mass","Data", "PE");
  leg1->AddEntry("model","Fit model","L");
  leg1->AddEntry("sign","Signal", "L");
  leg1->AddEntry("bkgn","Comb. bkg.", "L");
  leg1->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %.2f", chi2ndf), "");
  leg1->AddEntry((TObject*)0,Form(" #chi^{2}_{IP, D^{0}} < %.2f", ipchi2_max) , "");

  leg1->Draw("SAME");
 // res->Print();

 cm->SaveAs("plots/" + extension + TString(".pdf"));
 cout<<"Chi2/ndf = "<<chi2ndf<<endl;

 HFMass.setRange("signal",MM-0.02,MM+0.02);
 RooAbsReal* intsigX = sign.createIntegral(HFMass,NormSet(HFMass),Range("signal")) ;


 RooWorkspace *w = new RooWorkspace("w", "workspace");
 // w->import(sign);
 // w->import(bkgn);
 w->import(model);
 w->import(D0Mass);
 w->Print();
 w->writeToFile("hists/workspace_"+extension + ".root");
 f.Write();
 f.Close();

 double rec[2] = {ns.getValV(), ns.getError()};
 intsigX->Print();
 return rec;



}
