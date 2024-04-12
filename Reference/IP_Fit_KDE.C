#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <array>
#include <vector>
#include <string>
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
#include "TF1.h"

double * Fit(){
  using namespace RooFit;
  using namespace std;
  TFile * f = TFile::Open("/nfs/turbo/lsa-caidala/dshangas/LHCb_MCData/Lambda/Lambda.root"); ///CHANGE FOR D0 DATA
  TTree * t2 = (TTree *) f->Get("DecayTree"); ///
  TLatex latex;
  
  ///fitn SELECTS STRATEGY FOR FITTING OF COMBINATORIC BACKGROUND///
  //int fitn = 1; ///FIT TO BACKGROUND WITH INITIAL HESSE TURNED ON
  //int fitn = 0; ///STANDARD FIT TO BACKGROUND
  int fitn = -1; ///DEFAULT - NO PRIOR FITTING (FASTEST)
  
  int nBins = 80; ///NUMBER OF BINS - UP TO YOU.  NOTE: MORE BINS = MORE DETAILED DISTRIBUTION BUT LARGER UNCERTAINTIES; LESS BINS = BETTER UNCERTAINTIES BUT WORSE RESOLUTION
  Double_t rho = 1.; ///WIDTH OF GAUSSIANS USED IN REGRESSION FIT OF COMBINATORIC BACKGROUND
  
  TString cuts("(nPV == 1) && (PVZ > -60) && (PVZ < 120)"); ///CHANGE
  //cout << cuts << endl;
  TString cuts_bg = cuts + " && ((L0_M > 1125) || (L0_M < 1106))"; ///CHANGE FOR D0 MASS SIDEBAND
  TCanvas * cm = new TCanvas("cm");

  ////////Chi2 Distributions////////
  RooRealVar L0_IPCHI2_OWNPV("L0_IPCHI2_OWNPV","L0_IPCHI2_OWNPV",-5.,7); ///LOG(CHI_IP^2) VARIABLE THAT IS FED INTO ROOFIT FUNCTIONS
  L0_IPCHI2_OWNPV.setBins(nBins);
  TH1D * hchi2 = new TH1D ("hchi2", "hchi2", nBins, -5., 7.);
  TH1D * hchi2_bkg = new TH1D ("hchi2_bkg", "hchi2", nBins, -5., 7.);
  t2->Draw("log10(L0_IPCHI2_OWNPV)>>hchi2", cuts, "");
  t2->Draw("log10(L0_IPCHI2_OWNPV)>>hchi2_bkg", cuts_bg, "");
  RooDataHist L0x2("L0x2","L0x2", RooArgList(L0_IPCHI2_OWNPV), hchi2, 1.); ///DISTRIBUTION TO FIT FULL PDF TO
  RooDataHist L0x2_bkg("L0x2_bkg","L0x2_bkg", RooArgList(L0_IPCHI2_OWNPV), hchi2_bkg, 1.); ///DISTRIBUTION TO FIT BACKGROUND TO

  ////////Prompt Signal Distribution////////
  ///THESE VARIABLES WILL LIKELY NEED TO BE UPDATED FOR D0.  IF STRUGGLING, CONSULT PARAMETERS FROM D0 GROUP: https://gitlab.cern.ch/lhcb-ift/d0-production-in-ppb-at-8-tev/-/tree/master/Preparations
  ///SYNTAX: VAR(name, title, initial guess, min, max);
  RooRealVar mux("mux","mux",.9,-5.,1.5); ///MEAN VALUE
  RooRealVar sigmax("sigmax","sigmax",.7,0.05,.9); ///WIDTH
  RooRealVar epsilon("epsilon","epsilon",-.08,-.2,-.01); ///SKEW
  RooRealVar rhoL("rhoL","rhoL",-.08,-.3,-.003); ///LEFT TAIL
  RooRealVar rhoR("rhoR","rhoR",.3,-3.5,1.5); ///RIGHT TAIL
  RooBukinPdf sigx("sigx", "sigx", L0_IPCHI2_OWNPV, mux, sigmax, epsilon, rhoL, rhoR);
  
  /////////Secondaries Distribution/////////
  RooRealVar nsec("nsec", "nsec", 1, 0.,10000000.); ///NUMBER OF SECONDARY D0 CANDIDATES
  RooRealVar meanxG("meanxG","meanxG",4.,1.75,5.5);
  RooRealVar sigmaxG("sigmaxG","sigmaxG",1.3,0.08,4.);
  RooGaussian sec("sec", "sec", L0_IPCHI2_OWNPV, meanxG, sigmaxG);

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
  RooRealVar ncomb("ncomb", "ncomb", 1.0e2, 0.,10000000.); ///NUMBER OF COMBINATORIC BACKGROUND CANDIDATES
  RooRealVar meanxG2("meanxG2","meanxG2",3.,.1,12.); 
  RooRealVar sigmaxG2("sigmaxG2","sigmaxG2", 2.126,0.5,5.);
  RooTFnPdfBinding comb("comb", "comb", func2, RooArgList(L0_IPCHI2_OWNPV)); ///PDF FOR COMBINATORIC BACKGROUND
  RooAddPdf bkgx("bkgx", "bkgx", RooArgList(sec,comb),RooArgList(nsec, ncomb)); 
  RooFitResult * resbg;
  if (fitn == 0){
    resbg = comb.fitTo(L0x2_bkg,PrintEvalErrors(-1));
  }
  if (fitn == 1){
    resbg = comb.fitTo(L0x2_bkg,PrintEvalErrors(-1),InitialHesse(true));
  }

  /////////////Full Fit to Data/////////////
  RooRealVar nsigx("nsigx", "nsigx", 800000., 0.,10000000.); ///NUMBER OF PROMPT SIGNAL CANDIDATES
  RooRealVar nbkgx("nbkgx", "nbkgx", 45000., 0.,10000000.); ///NUMBER OF COMBINATORIC BACKGROUND AND SECONDARY CANDIDATES
  RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,bkgx),RooArgList(nsigx, nbkgx));
  //RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,comb,sec),RooArgList(nsigx,ncomb,nsec)); ///MAY YIELD BETTER FIT RESULTS IF NEEDED
  //RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,comb),RooArgList(nsigx, ncomb)); ///IF CERTAIN OF NO OR MINIMAL SECONDARY CANDIDATES, THIS PDF MAY BE OPTIMAL
  RooFitResult * res = sumx.fitTo(L0x2,PrintEvalErrors(-1), Save());

  /////////////////Plotting/////////////////
  RooPlot* xframe = L0_IPCHI2_OWNPV.frame();
  L0x2.plotOn(xframe);
  sumx.plotOn(xframe,PrintEvalErrors(-1));
  sumx.plotOn(xframe, Components(bkgx),LineColor(kBlack), LineStyle(kDashed),PrintEvalErrors(-1));
  sumx.plotOn(xframe, Components(sigx),LineColor(kGreen),PrintEvalErrors(-1));
  sumx.plotOn(xframe, Components(sec), FillColor(kRed), FillStyle(3002), DrawOption("F"),PrintEvalErrors(-1));
  sumx.plotOn(xframe, Components(comb), FillColor(kGreen+2), FillStyle(3003), DrawOption("F"),PrintEvalErrors(-1));
  xframe->SetTitle("D^{0}");
  xframe->SetXTitle("log_{10}(#chi^{2}_{IP})");
  xframe->SetYTitle("Candidates");
  L0x2.plotOn(xframe);
  xframe->Draw();
  res->Print();

  double rec[2] = {nsigx.getValV(), nsigx.getError()};
  return rec;
}
