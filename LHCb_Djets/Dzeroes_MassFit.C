
#include <iostream>
#include <TCanvas.h>
#include <vector>
//#include "../Settings.h"
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
//#include "../LundGen.hh"
#include <cmath>
#include <TCanvas.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TStyle.h>
#include <vector>
#include "Header.h"
#include "RooAbsAnaConvPdf.h"
#include "RooAddPdf.h"
#include "RooArgusBG.h"
#include "RooCategory.h"
#include "RooConstVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooPlot.h"
#include "RooPolynomial.h"
#include "RooRealSumFunc.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1.h"

//using namespace std;
using namespace RooFit;

void Dzeroes_MassFit() {
    TFile fread("Dzeroes_Variable_Tree_19514438.root", "READ");
    TTree *Djet_tree = (TTree *)fread.Get("Djet");
    int NumEvts = Djet_tree->GetEntries();
//  cout<<Djet_tree->GetEntries()<<endl;
    cout << NumEvts << endl;

    TFile f("Dzeroes_MassFit_m_50_100.root", "RECREATE");

    double jet_pt, jet_eta;
    double jet_rap;
    double jet_px, jet_py, jet_pz, jet_e;
    double pi_px, pi_py, pi_pz, pi_e;
    double K_px, K_py, K_pz, K_e;

    double D0_ipchi2;

    // TLorentzVector

    Djet_tree->SetBranchAddress("jet_pt", &jet_pt);
    Djet_tree->SetBranchAddress("jet_eta", &jet_eta);
    Djet_tree->SetBranchAddress("jet_rap", &jet_rap);

    Djet_tree->SetBranchAddress("jet_px", &jet_px);
    Djet_tree->SetBranchAddress("jet_py", &jet_py);
    Djet_tree->SetBranchAddress("jet_pz", &jet_pz);
    Djet_tree->SetBranchAddress("jet_e", &jet_e);

    Djet_tree->SetBranchAddress("D0_ipchi2", &D0_ipchi2);

    Djet_tree->SetBranchAddress("pi_px", &pi_px);
    Djet_tree->SetBranchAddress("pi_py", &pi_py);
    Djet_tree->SetBranchAddress("pi_pz", &pi_pz);
    Djet_tree->SetBranchAddress("pi_e", &pi_e);

    Djet_tree->SetBranchAddress("K_px", &K_px);
    Djet_tree->SetBranchAddress("K_py", &K_py);
    Djet_tree->SetBranchAddress("K_pz", &K_pz);
    Djet_tree->SetBranchAddress("K_e", &K_e);


    int fitn = 1; ///DEFAULT - NO PRIOR FITTING (FASTEST)

    int nBins = 80; ///NUMBER OF BINS - UP TO YOU.  NOTE: MORE BINS = MORE DETAILED DISTRIBUTION BUT LARGER UNCERTAINTIES; LESS BINS = BETTER UNCERTAINTIES BUT WORSE RESOLUTION
    Double_t rho = 1.; ///WIDTH OF GAUSSIANS USED IN REGRESSION FIT OF COMBINATORIC BACKGROUND
    double MM = 1.865;
    double M_sigma = 0.0075;
    double WM = 7. * M_sigma;
    double DM = 0.015;
    double ipchi2_max = 5.;

    TH1D *hchi2 = new TH1D("hchi2", "hchi2", nBins, -3., 5.);
    TH1D *hchi2_bkg = new TH1D("hchi2_bkg", "hchi2", nBins, -3., 5.);
    TH1D *h1_mass = new TH1D("h1_mass", "h1_mass", nBins, MM - WM, MM + WM);

    int eventNum;
    cout << "Requested # of events" << NumEvts << endl;

    for (int ev = 0; ev < NumEvts; ev++) {
        Djet_tree->GetEntry(ev);

        if (ev % 100000 == 0) {
            cout << "Executing event " << ev << endl;
        }

        TLorentzVector HFmeson, HFjet, pi, Kmeson, Jpsi;

        HFjet.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
        pi.SetPxPyPzE(pi_px, pi_py, pi_pz, pi_e);
        Kmeson.SetPxPyPzE(K_px, K_py, K_pz, K_e);

        HFmeson = pi + Kmeson;

        double dphi_HF_jet = checkphi(checkphi(HFmeson.Phi()) - checkphi(HFjet.Phi()));
        double dy_HF_jet = HFjet.Eta() - HFmeson.Rapidity();

        if (jet_pt < 50.0) {
            continue;
        }

        // pt bins
        if (jet_pt > 100.0) {
            continue;
        }

        if (HFmeson.M() < MM - WM || HFmeson.M() > MM + WM) {
            continue;
        }

        // cout<<log10(D0_ipchi2);
        bool bkg_cond = (HFmeson.M() > MM - 7. * M_sigma && HFmeson.M() < MM - 5. * M_sigma) || (HFmeson.M() < MM + 7 * M_sigma && HFmeson.M() > MM + 5. * M_sigma);

        // bool bkg_cond = HFmeson.M() < MM - WM || HFmeson.M() > MM + WM;
        if (bkg_cond) {
            hchi2_bkg->Fill(log10(D0_ipchi2));
        }

        hchi2->Fill(log10(D0_ipchi2));

        if (log10(D0_ipchi2) > ipchi2_max) {
            continue;
        }

        h1_mass->Fill(HFmeson.M());
    }

//  TLatex latex;
    ///fitn SELECTS STRATEGY FOR FITTING OF COMBINATORIC BACKGROUND///
    //int fitn = 1; ///FIT TO BACKGROUND WITH INITIAL HESSE TURNED ON
    //int fitn = 0; ///STANDARD FIT TO BACKGROUND

    ///CHANGE FOR D0 MASS SIDEBAND
    TCanvas *cm = new TCanvas("cm", "c", 700, 900);
    cm->Divide(1, 2);
    cm->cd(1);
    ////////Chi2 Distributions////////
    RooRealVar HFMass("HFMass", "HFMass", MM - WM, MM + WM); ///LOG(CHI_IP^2) VARIABLE THAT IS FED INTO ROOFIT FUNCTIONS
    HFMass.setBins(nBins);
    RooDataHist D0Mass("D0Mass", "D0Mass", RooArgList(HFMass), h1_mass, 1.);

    // RooRealVar Mean("Mean","",MM, MM-DM,MM+DM); //
    RooRealVar Mean("Mean", "", MM - DM, MM + DM);
    //RooRealVar CBS("CBS","CBS",DM/2.,4./1000.,DM);
    RooRealVar CBS("CBS", "CBS", 4. / 1000., DM);
    RooRealVar n("n", "n", 1.);
    //RooRealVar a("a","a",2.,1.,5.);
    RooRealVar a("a", "a", 1., 5.);
    RooCBShape sig1("cb", "Signal", HFMass, Mean, CBS, a, n);

    //Sigma,f,a are obtained from fit for kinematically unbinned data, and I do the fit outside the file.
    // RooFormulaVar Sigma("Sigma","1.647*CBS",RooArgSet(CBS));
    //RooRealVar Sigma("Sigma", "Sigma", DM/2.,6./1000., DM);
    RooRealVar Sigma("Sigma", "Sigma", 6. / 1000., DM);
    RooGaussian gaus("gaus", "", HFMass, Mean, Sigma);
    RooRealVar frac("frac", "", 0.34, 0., 0.999);  //0.1, 0.34

    // f.setVal(0.667);f.setConstant();
    // a.setVal(2.444);a.setConstant();
    RooAddPdf sig("sig", "gau1+gau2", RooArgSet(sig1, gaus), RooArgSet(frac));

    RooRealVar ns("ns", "nSignal", 0., 1554617.); //5000.,
    RooExtendPdf sign("sign", "sign", sig, ns);

    //BKG component
    //RooRealVar p("p","p",0.,-1./(MM+WM),1./(MM+WM));
    RooRealVar p("p", "p", -1., 1.);
//	RooPolynomial bkg("bkg","bkg",HFMass,RooArgSet(p));
    RooChebychev bkg("bkg", "bkg", HFMass, RooArgSet(p));
    RooRealVar nb("nb", "nBKG", 0., 1554617.);  //300.,
    RooExtendPdf bkgn("bkgn", "bkgn", bkg, nb);

    //sig+bkg

    RooAddPdf model("model", "sig+bkg", RooArgSet(bkgn, sign));

    RooArgSet *params = model.getParameters(HFMass);
    // Save snapshot of prefit parameters
    RooArgSet *initParams = (RooArgSet *)params->snapshot();

    model.fitTo(D0Mass);

    /////////////////Plotting/////////////////
    double binsize = (MM + WM - (MM - WM)) / (double)nBins;
    RooPlot *xframe = HFMass.frame(Title(Form(";M_{K#pi} [GeV];Events/(%.1f MeV) ", binsize * 1000.)));
    D0Mass.plotOn(xframe, Name("D0Mass"));

    model.plotOn(xframe, Name("bkgn"), Components(bkgn), LineColor(kBlue), LineStyle(kDashed), PrintEvalErrors(-1));
    model.plotOn(xframe, Name("sign"), Components(sign), LineColor(kGreen), LineStyle(5), PrintEvalErrors(-1));
    model.plotOn(xframe, Name("model"), LineColor(kRed), PrintEvalErrors(-1));
    double chi2ndf = xframe->chiSquare(11);
    // model.plotOn(xframe, Components(sec), FillColor(kRed), FillStyle(3002), DrawOption("F"),PrintEvalErrors(-1));
    // model.plotOn(xframe, Components(comb), FillColor(kGreen+2), FillStyle(3003), DrawOption("F"),PrintEvalErrors(-1));

    xframe->Draw("SAME");
    TLegend *leg1 = new TLegend(0.65, 0.6, 0.86, 0.87);
    // leg1->SetFillColor(kWhite);
    // leg1->SetLineColor(kWhite);
    leg1->SetBorderSize(0);
    //leg1->AddEntry("D0Mass","Data p_{T} > 20 GeV/c", "PE");
    //leg1->AddEntry("D0Mass","Data 20 GeV/c < p_{T} < 30 GeV/c", "PE");
//  leg1->AddEntry("D0Mass","Data 30 GeV/c < p_{T} < 50 GeV/c", "PE");
    leg1->AddEntry("D0Mass", "Data 50 GeV/c < p_{T} < 100 GeV/c", "PE");
    leg1->AddEntry("model", "Fit model", "L");
    leg1->AddEntry("sign", "Signal", "L");
    leg1->AddEntry("bkgn", "Comb. bkg.", "L");
    leg1->AddEntry((TObject *)0, Form("#chi^{2}/ndf = %.2f", chi2ndf), "");
    leg1->AddEntry((TObject *)0, Form(" #chi^{2}_{IP, D^{0}} < %.2f", ipchi2_max), "");

    leg1->Draw("SAME");
    // res->Print();

    cm->SaveAs("D0_MassFit_m_50_100.pdf");
    cout << "Chi2/ndf = " << chi2ndf << endl;

    HFMass.setRange("signal", MM - 0.02, MM + 0.02);
    RooAbsReal *intsigX = sign.createIntegral(HFMass, NormSet(HFMass), Range("signal"));


    RooWorkspace *w = new RooWorkspace("w", "workspace");
    // w->import(sign);
    // w->import(bkgn);
    w->import(model);
    w->import(D0Mass);
    w->Print();
    w->writeToFile("workspace_Dmassfit_m_50_100.root");
    params->printLatex(Sibling(*initParams), OutputFile("D0_MassFit_m_50_100.tex"));
    f.Write();
    f.Close();

    double rec[2] = {
        ns.getValV(), ns.getError()
    };
    intsigX->Print();
    return rec;
}
