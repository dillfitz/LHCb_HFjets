

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



void IPFit(int NumEvts = 10000, int dataset = 1510,bool isData = true,
               bool chargedJetCut_user = false,
               bool NonPrompt = false ){

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
  extension = TString("ipfit_") + str_level + Form("_ev_%d", NumEvts)
            + Form("_ptj_%d%d", int(ptMin), int(ptMax))
            + Form("_eta_%.1f%.1f", etaMin, etaMax)
            +  str_ghost +str_charged + str_Mag
            + str_flavor +  Form("_%d", dataset);

  TString extension_wspace = TString("workspace_massfit_") + str_level + Form("_ev_%d", NumEvts)
            + Form("_ptj_%d%d", int(ptMin), int(ptMax))
            + Form("_eta_%.1f%.1f", etaMin, etaMax)
            +  str_ghost +str_charged + str_Mag
            + str_flavor +  Form("_%d", dataset);

  if(NonPrompt) extension += "_fromb";
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
  TFile fwspace(dir_deadcone + "hists/" + extension_wspace + ".root", "READ");




  double jet_pt, jet_eta, tr_jet_pt, tr_jet_eta;
  double jet_rap, tr_jet_rap;
  double jet_px, jet_py, jet_pz, jet_e;
  double Z_px, Z_py, Z_pz, Z_e;
  double pi_px, pi_py, pi_pz, pi_e;
  double K_px, K_py, K_pz, K_e;

  double tr_jet_px, tr_jet_py, tr_jet_pz, tr_jet_e;
  double tr_pi_px, tr_pi_py, tr_pi_pz, tr_pi_e;
  double tr_K_px, tr_K_py, tr_K_pz, tr_K_e;

  int nsplits, ndtrs, flav;
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

  LundTree->SetBranchAddress("flav", &flav);



  int fitn = -1; ///DEFAULT - NO PRIOR FITTING (FASTEST)

  int nBins = 140; ///NUMBER OF BINS - UP TO YOU.  NOTE: MORE BINS = MORE DETAILED DISTRIBUTION BUT LARGER UNCERTAINTIES; LESS BINS = BETTER UNCERTAINTIES BUT WORSE RESOLUTION
  Double_t rho = 1.; ///WIDTH OF GAUSSIANS USED IN REGRESSION FIT OF COMBINATORIC BACKGROUND
  double MM = 1.865;
  double M_sigma = 0.0075;
	double WM = 7.*M_sigma;
	double DM = 0.015;

  TH1D * hchi2 = new TH1D ("hchi2", "hchi2", nBins, -3., 5.);
  TH1D * hchi2_bkg = new TH1D ("hchi2_bkg", "hchi2", nBins, -3., 5.);
  TH1D * h1_mass = new TH1D("h1_mass", "h1_mass", nBins, MM-WM, MM+WM);


  int eventNum;
  cout<<"Requested # of events"<<NumEvts<<endl;
  for(int ev = 0; ev < NumEvts; ev++)
  {
    LundTree->GetEntry(ev);

    if (ev%10000==0) cout<<"Executing event "<<ev<<endl;

  if(NonPrompt){
    if(flav != 5) continue;
  }
  
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
  bool signal_cond = (HFmeson.M() > (MM - 0.02) && (HFmeson.M() < (MM + 0.02)));
  bool bkg_cond = (HFmeson.M() > (MM - WM) && HFmeson.M() < (MM - 5.*M_sigma)) || (HFmeson.M() < (MM + WM) && HFmeson.M() > (MM + 5.*M_sigma)) ;
  // bool bkg_cond = HFmeson.M() < MM - WM || HFmeson.M() > MM + WM;
  if(bkg_cond){
    hchi2_bkg->Fill(log10(D0_ipchi2));
  }
  if(signal_cond) hchi2->Fill(log10(D0_ipchi2));

  }

  RooWorkspace* wspace = (RooWorkspace*)fwspace.Get("w");

  if(wspace != NULL){

  RooExtendPdf * mass_bkgn = (RooExtendPdf*)wspace->obj("bkgn");
  RooRealVar * HFMass = (RooRealVar*)wspace->obj("HFMass");
  HFMass->setRange("signal",MM-0.02,MM+0.02);
  HFMass->setRange("sideband1",MM - 7*M_sigma,MM - 5*M_sigma);
  HFMass->setRange("sideband2",MM + 5*M_sigma,MM + 7*M_sigma);
  RooAbsReal* intbkgX = mass_bkgn->createIntegral(*HFMass,NormSet(*HFMass),Range("signal")) ;
  RooAbsReal* intbkg_sideband = mass_bkgn->createIntegral(*HFMass,NormSet(*HFMass),Range("sideband1", "sideband2")) ;
  intbkgX->Print();
  intbkg_sideband->Print();
  double bkg_scale = intbkgX->getVal()/intbkg_sideband->getVal();

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
  TCanvas * cm = new TCanvas("cm","c", 700, 900);
  cm->Divide(1, 2);
  cm->cd(1);
  ////////Chi2 Distributions////////
  RooRealVar D0_IPCHI2_OWNPV("D0_IPCHI2_OWNPV","D0_IPCHI2_OWNPV",-3.,5.);
  D0_IPCHI2_OWNPV.setBins(nBins);
  // LundTree->Draw("log10(D0_IPCHI2_OWNPV)>>hchi2", cuts, "");
  // LundTree->Draw("log10(D0_IPCHI2_OWNPV)>>hchi2_bkg", cuts_bg, "");
  // RooDataSet D0ML("D0ML","D0ML", RooArgList(D0_IPCHI2_OWNPV), hchi2, 1.);
  RooDataHist D0x2("D0x2","D0x2", RooArgList(D0_IPCHI2_OWNPV), hchi2, 1.); ///DISTRIBUTION TO FIT FULL PDF TO
  RooDataHist D0x2_bkg("D0x2_bkg","D0x2_bkg", RooArgList(D0_IPCHI2_OWNPV), hchi2_bkg, 1.); ///DISTRIBUTION TO FIT BACKGROUND TO

  ////////Prompt Signal Distribution////////
 ///THESE VARIABLES WILL LIKELY NEED TO BE UPDATED FOR D0.  IF STRUGGLING, CONSULT PARAMETERS FROM D0 GROUP: https://gitlab.cern.ch/lhcb-ift/d0-production-in-ppb-at-8-tev/-/tree/master/Preparations
 ///SYNTAX: VAR(name, title, initial guess, min, max);
 RooRealVar mux("mux","mux",.9, -0.5, 1.5); ///MEAN VALUE
 RooRealVar sigmax("sigmax","sigmax",.7,0.01,1.2); ///WIDTH
 RooRealVar epsilon("epsilon","epsilon",-.08,-.2,-.01); ///SKEW
 RooRealVar rhoL("rhoL","rhoL",-.08,-.3,-.003); ///LEFT TAIL
 RooRealVar rhoR("rhoR","rhoR",.3,-3.5,1.5); ///RIGHT TAIL
 RooBukinPdf sigx("sigx", "sigx", D0_IPCHI2_OWNPV, mux, sigmax, epsilon, rhoL, rhoR);

 /////////Secondaries Distribution/////////
 //Floating Parameter    FinalValue +/-  Error   
  // --------------------  --------------------------
  //          epsilon_sec   -1.6152e-02 +/-  1.18e-02
  //               mu_sec    1.6926e+00 +/-  2.51e-02
  //                ncomb    1.1010e+03 +/-  4.71e+02
  //                 nsec    2.3582e+04 +/-  2.02e+03
  //             rhoL_sec   -7.2724e-01 +/-  1.24e-01
  //             rhoR_sec   -2.8342e+00 +/-  2.94e-01
  //            sigma_sec    1.0616e+00 +/-  1.63e-02
 RooRealVar mu_sec, sigma_sec, epsilon_sec, rhoL_sec, rhoR_sec, nsec;
 if(NonPrompt){
  mu_sec = RooRealVar("mu_sec","mu_sec",0.5, 1.,3.5); ///MEAN VALUE
 sigma_sec = RooRealVar("sigma_sec","sigma_sec",.7,0.05,1.5); ///WIDTH
 epsilon_sec = RooRealVar("epsilon_sec","epsilon_sec",-.08,-.5,-.01); ///SKEW
 rhoL_sec = RooRealVar("rhoL_sec","rhoL_sec",-.08,-.9,-.003); ///LEFT TAIL
 rhoR_sec =  RooRealVar("rhoR_sec","rhoR_sec",.3,-3.5,1.5); ///RIGHT TAIL
 nsec = RooRealVar("nsec", "nsec", 10000, 0.,10000000.);
 }
 else{
//   mu_sec = RooRealVar("mu_sec","mu_sec",1.6926e+00); ///MEAN VALUE
//  sigma_sec = RooRealVar("sigma_sec","sigma_sec",1.0616e+00); ///WIDTH
//  epsilon_sec = RooRealVar("epsilon_sec","epsilon_sec",-1.6152e-02); ///SKEW
//  rhoL_sec = RooRealVar("rhoL_sec","rhoL_sec",-7.2724e-01); ///LEFT TAIL
//  rhoR_sec =  RooRealVar("rhoR_sec","rhoR_sec",-2.8342e+00); ///RIGHT TAIL
//  nsec = RooRealVar("nsec", "nsec", 10000, 0.,10000000.);


 mu_sec = RooRealVar("mu_sec","mu_sec",1.6926e+00, 1.,3.5); ///MEAN VALUE
 sigma_sec = RooRealVar("sigma_sec","sigma_sec",1.0616e+00,0.05,1.5); ///WIDTH
 epsilon_sec = RooRealVar("epsilon_sec","epsilon_sec",-1.6152e-02,-.5,-.01); ///SKEW
 rhoL_sec = RooRealVar("rhoL_sec","rhoL_sec",-7.2724e-01,-.9,-.003); ///LEFT TAIL
 rhoR_sec =  RooRealVar("rhoR_sec","rhoR_sec",-2.8342e+00,-3.5,0.); ///RIGHT TAIL
 nsec = RooRealVar("nsec", "nsec", 10000, 0.,10000000.);
 }
 
 RooBukinPdf sec("sec", "sig_sec", D0_IPCHI2_OWNPV, mu_sec, sigma_sec, epsilon_sec, rhoL_sec, rhoR_sec);
 
 // RooRealVar meanxG("meanxG","meanxG",2.,1.5,3.5);
 // RooRealVar sigmaxG("sigmaxG","sigmaxG",1.,0.08,2.);
 // RooGaussian sec("sec", "sec", D0_IPCHI2_OWNPV, meanxG, sigmaxG);

 //////////Background Distribution/////////

 // RooRealVar mu_comb("mu_comb","mu_comb",1.6,1.,3.5); ///MEAN VALUE
 // RooRealVar sigma_comb("sigma_comb","sigma_comb",.7,0.05,.9); ///WIDTH
 // RooRealVar epsilon_comb("epsilon_comb","epsilon_comb",-.08,-.2,-.01); ///SKEW
 // RooRealVar rhoL_comb("rhoL_comb","rhoL_comb",-.08,-.3,-.003); ///LEFT TAIL
 // RooRealVar rhoR_comb("rhoR_comb","rhoR_comb",.3,-3.5,1.5); ///RIGHT TAIL
 // RooBukinPdf comb("comb", "sig_comb", D0_IPCHI2_OWNPV, mu_comb, sigma_comb, epsilon_comb, rhoL_comb, rhoR_comb);

 // RooRealVar mu_comb("mu_comb", "mu_comb", 1.5, 1, 2);
 // RooRealVar sigma_comb("sigma_comb", "sigma_comb", 1., 0.1, 1.5);
 // RooGaussian comb("combbkg", "combbkg", D0_IPCHI2_OWNPV, mu_comb, sigma_comb);
//////////Background Distribution/////////
  //cout << nBins << endl;
  std::vector<double> means_bkg(0); ///ARRAY OF BACKGROUND LOG(CHI_IP^2) VALUES
  int num = 0;
  int num2= 0; ///SIZE OF ARRAY TO RUN GAUSSIAN REGRESSION FIT ON
  for (int j = 0; j < nBins; j++){
   if (hchi2_bkg->GetBinContent(j) > 0){
    num2 = num+hchi2_bkg->GetBinContent(j);
    means_bkg.resize(num2, hchi2_bkg->GetBinCenter(j));
    num = num + hchi2_bkg->GetBinContent(j);
   }
  }
  cout << "size: " << num2-1 << endl;
  TKDE * kde2; ///KERNEL DENSITY ESTIMATOR (GAUSSIAN IN THIS CASE)
  if (num2-1 >= 0){
    kde2 = new TKDE(num2-1, &means_bkg[0], -5., 7., "KernelTye:Gaussian", rho);
  }
  
  TF1 * func2;
  if (num2-1 >= 0){
    hchi2_bkg->Scale(1./hchi2_bkg->Integral(),"width" ); ///NORMALIZE
    //hchi2_bkg->Draw();
    func2 = kde2->GetFunction(100, -5., 7.);
    //func2->SetFillColor(kGreen);
    //func2->SetFillStyle(3003);
    //func2->SetLineWidth(0);
    //func2->Draw("SAME && FC");
  }
  RooRealVar ncomb("ncomb", "ncomb", hchi2_bkg->GetEntries()*2., hchi2_bkg->GetEntries(),hchi2_bkg->GetEntries()*3); ///NUMBER OF COMBINATORIC BACKGROUND CANDIDATES
  RooRealVar meanxG2("meanxG2","meanxG2",3.,.1,12.); 
  RooRealVar sigmaxG2("sigmaxG2","sigmaxG2", 2.126,0.5,5.);
  RooTFnPdfBinding comb("comb", "comb", func2, RooArgList(D0_IPCHI2_OWNPV)); ///PDF FOR COMBINATORIC BACKGROUND
  RooAddPdf bkgx("bkgx", "bkgx", RooArgList(sec,comb),RooArgList(nsec, ncomb)); 
  RooFitResult * resbg;
  if (fitn == 0){
    resbg = comb.fitTo(D0x2_bkg,PrintEvalErrors(-1));
  }
  if (fitn == 1){
    resbg = comb.fitTo(D0x2_bkg,PrintEvalErrors(-1),InitialHesse(true));
  }
  
  // RooRealVar nsec("nsec", "nsec", 50000., 0.,10000000.); ///NUMBER OF SECONDARY D0 CANDIDATES
//  RooRealVar ncomb("ncomb", "ncomb", hchi2_bkg->GetEntries()*bkg_scale , hchi2_bkg->GetEntries()*bkg_scale*0.95, hchi2_bkg->GetEntries()*bkg_scale*1.05); ///NUMBER OF COMBINATORIC BACKGROUND CANDIDATES

 // comb.fitTo(D0x2_bkg,PrintEvalErrors(-1));
 // mu_comb.setConstant(kTRUE);
 // sigma_comb.setConstant(kTRUE);
 // epsilon_comb.setConstant(kTRUE);
 // rhoL_comb.setConstant(kTRUE);
 // rhoR_comb.setConstant(kTRUE);

 /////////////Full Fit to Data/////////////
 RooRealVar nsigx;
 nsigx = RooRealVar("nsigx", "nsigx", 800000., 0.,10000000.);
//  if(NonPrompt) nsigx = RooRealVar("nsigx", "nsigx", 0, 0.,1.); ///NUMBER OF PROMPT SIGNAL CANDIDATES
 RooRealVar nbkgx("nbkgx", "nbkgx", 45000., 0.,10000000.); ///NUMBER OF COMBINATORIC BACKGROUND AND SECONDARY CANDIDATES
 // RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,bkgx),RooArgList(nsigx, nbkgx));
 RooAddPdf * sumx;
 sumx = new RooAddPdf("sumx", "sumx", RooArgList(sigx,comb,sec),RooArgList(nsigx,ncomb,nsec)); ///MAY YIELD BETTER FIT RESULTS IF NEEDED
 if(NonPrompt) sumx = new RooAddPdf("sumx", "sumx", RooArgList(comb, sec),RooArgList(ncomb, nsec)); ///MAY YIELD BETTER FIT RESULTS IF NEEDED
 //RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,comb),RooArgList(nsigx, ncomb)); ///IF CERTAIN OF NO OR MINIMAL SECONDARY CANDIDATES, THIS PDF MAY BE OPTIMAL
 RooFitResult * res = sumx->fitTo(D0x2,PrintEvalErrors(-1), Save());

  //---- paint setup...
 //
 int ican=-1,iframe=-1,itext=-1;
 TCanvas *ccan[1000];
 TH1F	*frame[1000];
 TLatex	*text[1000];
 TRatioPlot *rp[1000];
 for (int i=0;i<1000;i++){
   text[i]	= new TLatex();
   text[i]->SetNDC(kTRUE);
   text[i]->SetTextSize(0.06);
 }
 TLatex Tl;
 Tl.SetNDC(kTRUE);
 Tl.SetTextSize(0.04);
 //
 gStyle->SetOptStat(0);
 //gStyle->SetPaperSize(TStyle::kUSLetter);
 //gStyle->SetPadBottomMargin(0.08);
 //gStyle->SetPadTopMargin(0.005);
 gStyle->SetPadLeftMargin(0.13);
 gStyle->SetPadRightMargin(0.13);
 gStyle->SetLabelSize(0.05,"X");
 gStyle->SetLabelSize(0.05,"Y");
 gStyle->SetTitleXSize(0.055);
 gStyle->SetTitleYSize(0.055);
 gStyle->SetTitleOffset(0.55,"X");
 gStyle->SetTitleOffset(1.5,"Y");
 gStyle->SetStatW(0.2);
 // gStyle->SetPalette(kBird);
 gStyle->SetPalette(kBird);
 gStyle->SetNumberContours(100);
 gStyle->SetPaintTextFormat("4.3g");
 //gStyle->SetErrorX(0);
 gStyle->SetTitleStyle(0);
 gStyle->SetStatStyle(0);
 //gStyle->SetLineWidth(3);

 //---- paint...
 char buf[100];
 char bufb[100];
 TString rootfile;
 TString plotfile;
 TString plotfilePDF;
 TString plotfileO;
 TString plotfileC;
 //TString OutputFileBase	= outbase+outinfo;
 rootfile	= "hists/" + extension + TString(".root");
 plotfile	= "plots/"  + extension + TString(".ps");
 plotfilePDF	= "plots/" + extension + TString(".pdf");
 plotfileO	= plotfilePDF + TString("(");
 plotfileC	= plotfilePDF + TString("]");
 //c->SaveAs("plots/"+extension+".pdf");


 // Begin plotting
 //
   // Plot data and PDF overlaid
   ++ican;
   sprintf(buf,"ccan%d",ican);
   ccan[ican] = new TCanvas(buf,buf,30*ican,30*ican,800,(8.5/11.)*800);
   ccan[ican]->SetFillColor(10);
   //gPad->SetLeftMargin(0.16);
   //gPad->SetBottomMargin(0.06);
   ccan[ican]->cd(); ccan[ican]->Divide(1,2,0.0001,0.0001);

   ccan[ican]->cd(1);
   ccan[ican]->SetFillStyle(4070);

 /////////////////Plotting/////////////////
 int ndf;
 ndf = 8;
 if(NonPrompt) ndf = 7;
 double binsize = (MM+WM - (MM-WM))/(double) nBins;
 RooPlot *xframe = D0_IPCHI2_OWNPV.frame(Title(Form(";log_{10}(#chi^{2}_{IP});Events/(%.3f) ", binsize)));
 D0x2.plotOn(xframe, Name("D0x2"));
 sumx->plotOn(xframe, Name("bkgx"), Components(bkgx),LineColor(kBlack), LineStyle(kDashed),PrintEvalErrors(-1));
 sumx->plotOn(xframe, Name("sigx"), Components(sigx),LineColor(kGreen),LineStyle(5), PrintEvalErrors(-1));
 sumx->plotOn(xframe, Name("sec"), Components(sec), FillColor(kMagenta), FillStyle(3165), LineWidth(0), DrawOption("F"),PrintEvalErrors(-1));
 sumx->plotOn(xframe, Name("comb"), Components(comb), FillColor(kBlue), FillStyle(3153), LineWidth(0), DrawOption("F"),PrintEvalErrors(-1));
 sumx->plotOn(xframe, Name("sumx"), LineColor(kRed), PrintEvalErrors(-1));
 double chi2ndf = xframe->chiSquare(ndf);

 // D0x2_bkg.plotOn(xframe);
 D0x2.plotOn(xframe);
 xframe->Draw("SAME");

 RooHist* hpull = xframe->pullHist() ;

 TLegend *leg1 = new TLegend(0.65,0.6,0.86,0.87);
  // leg1->SetFillColor(kWhite);
  // leg1->SetLineColor(kWhite);
  leg1->SetBorderSize(0);
  leg1->AddEntry("D0x2","Data", "PE");
  leg1->AddEntry("sumx","Fit model","L");
  leg1->AddEntry("sigx","Signal", "L");
  leg1->AddEntry("sec","D^{0} from b", "F");
  leg1->AddEntry("comb","Comb. bkg.", "F");
  leg1->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %.2f", chi2ndf), "");
  leg1->AddEntry((TObject*)0,Form("%.0f < M_{K#pi} < %.0f [MeV]", (MM-0.02)*1000., (MM+0.02)*1000.), "");
  leg1->Draw("SAME");
 res->Print();

   leg1->Draw("SAME");

   ccan[ican]->cd();ccan[ican]->Update();
   if (ican==0){ ccan[ican]->Print(plotfileO.Data()); }
   else { ccan[ican]->Print(plotfilePDF.Data()); }


 ccan[ican]->cd(2);
   // RooPlot *xframe2 = x.frame();
   // B_mass.plotOn(xframe2);
   // model_nosec->plotOn(xframe2);
   // model_nosec->plotOn(xframe2, Components(bkg_nosec), LineStyle(kDashed), LineColor(kRed));
   // model_nosec->plotOn(xframe2, Components(sig_nosec), LineStyle(kSolid), LineColor(kGreen));
   // model_nosec->plotOn(xframe2, LineStyle(kSolid), LineColor(kBlue));
   
   ++ican;
   sprintf(buf,"ccan%d",ican);
   ccan[ican] = new TCanvas(buf,buf,30*ican,30*ican,800,(8.5/11.)*800);
   ccan[ican]->SetFillColor(10);
   //gPad->SetLeftMargin(0.16);
   //gPad->SetBottomMargin(0.06);
   ccan[ican]->cd(); ccan[ican]->Divide(1,2,0.0001,0.0001);

   RooPlot* xframe2 = D0_IPCHI2_OWNPV.frame(Title("Pull Distribution")) ;
    xframe2->addPlotable(hpull,"P") ;
    xframe2->SetMinimum(-5);
    xframe2->SetMaximum(5);

   ccan[ican]->cd(1); ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ; xframe->Draw() ;
   ccan[ican]->cd(2); ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ; xframe2->Draw() ;

   ccan[ican]->cd();ccan[ican]->Update();
   if (ican==0){ ccan[ican]->Print(plotfileO.Data()); }
   else { ccan[ican]->Print(plotfilePDF.Data()); }


   if (ican>-1){
    cout<<" You plotted "<<ican+1<<" canvasses......."<<endl;
    ccan[ican]->Print(plotfileC.Data());
  }

  if (ican>-1){
    cout<<" You plotted "<<ican+1<<" canvasses......."<<endl;
    ccan[ican]->Print(plotfileC.Data());
  }

//  cm->SaveAs("plots/" + extension + TString(".pdf"));
 cout<<"Chi2/ndf = "<<chi2ndf<<endl;
 cout<<"Background entries = "<<hchi2_bkg->GetEntries()<<endl;
 f.Write();
 f.Close();

 double rec[2] = {nsigx.getValV(), nsigx.getError()};
 return rec;



}
