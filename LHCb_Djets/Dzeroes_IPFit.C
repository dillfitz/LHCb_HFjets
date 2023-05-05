#include <iostream>
#include <TCanvas.h>
#include <vector>
#include "Header.h"
//#include "../Settings.h"
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
//#include "../LundGen.hh"
#include "Dzeroes_Variable_Tree.h"  //*       '      .    ,       .    .    ,
#include "RooAbsAnaConvPdf.h"       //     .   *        .     *        .      .
#include "RooArgusBG.h"             //               .            **           *
#include "RooCategory.h"            //   \ /         ,    .      (__)   ,       ,
#include "RooDataHist.h"            //  - * -     *           '  (..)     .        |
#include "RooDataSet.h"             //.  / \     ,       .        \/     .       - * -
#include "RooFFTConvPdf.h"          //   .                   '   / \\        ,     |
#include "RooGaussian.h"            //  ,      *         *      /   /\\   .              .
#include "RooGlobalFunc.h"          //    *           .        /\\ /               .
#include "RooPlot.h"                //_|_    ,   .    ,       /  \\ .      ,      *
#include "RooRealSumFunc.h"         // |  .     ,       .    *        , .           .
#include "RooRealVar.h"             // .    ,  *   .        .    '        .  *          .
#include "RooSimultaneous.h"        //                     The Milky Way

using namespace std;
using namespace RooFit;

void Dzeroes_IPFit() {
    TFile fread("Dzeroes_Variable_Tree_19514438.root", "READ");

    TTree *Djet_tree = (TTree *)fread.Get("Djet");
    int NumEvts = Djet_tree->GetEntries();
    cout << Djet_tree->GetEntries() << endl;

    TFile f("LogIPChiSquared.root", "RECREATE");
    TFile fwspace("workspace_Dmassfit_m.root", "READ");

    double jet_pt, jet_eta, jet_rap;
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


    int fitn = 1; ///DEFAULT - NO PRIOR FITTING (FASTEST) //-1

    int nBins = 500; ///NUMBER OF BINS - UP TO YOU.  NOTE: MORE BINS = MORE DETAILED DISTRIBUTION BUT LARGER UNCERTAINTIES; LESS BINS = BETTER UNCERTAINTIES BUT WORSE RESOLUTION
    Double_t rho = 1.; ///WIDTH OF GAUSSIANS USED IN REGRESSION FIT OF COMBINATORIC BACKGROUND
    double MM = 1.86487; //1.865
    double M_sigma = 0.0114; //changed
//    double WM = 6.0 * M_sigma; //before 7, 1.935- //6.15
    double WM = ((1.86487-1.8125)/(0.0114))*M_sigma;
    double DM = 0.015;
//    double L_M
    

    TH1D *hchi2 = new TH1D("hchi2", "hchi2", nBins, -3., 5.);
    TH1D *hchi2_bkg = new TH1D("hchi2_bkg", "hchi2", nBins, -3., 5.);
    TH1D *h1_mass = new TH1D("h1_mass", "h1_mass", nBins, 1.805, 1.935); //1.805 1.935 MM - WM , MM+WM

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

        if (jet_pt < 20.0) {
            continue;
        }

        if (HFmeson.M() < MM - WM || HFmeson.M() > MM + WM) {
            continue;
        }

        // cout<<log10(D0_ipchi2);
        bool signal_cond = (HFmeson.M() > (MM - 2.0*M_sigma) && (HFmeson.M() < (MM + 2.0*M_sigma)));
        bool bkg_cond = (HFmeson.M() > (MM - WM) && HFmeson.M() < (MM - 3.0 * M_sigma)) || (HFmeson.M() < (MM + WM) && HFmeson.M() > (MM + 3.0 * M_sigma));

        // bool bkg_cond = HFmeson.M() < MM - WM || HFmeson.M() > MM + WM;
        if (bkg_cond) {
            hchi2_bkg->Fill(log10(D0_ipchi2));
        }

        if (signal_cond) {
            hchi2->Fill(log10(D0_ipchi2));
        }
    }
    
                                    //*        (__)
                                    // \       (oo)
                                    //  \-------\/
                                    //   |     ||
                                    //   ||----||
                                    //  (oo)  (oo)
                                    //rollerskating cow

    RooWorkspace *wspace = (RooWorkspace *)fwspace.Get("w");
    RooExtendPdf *mass_bkgn = (RooExtendPdf *)wspace->obj("bkgn");
    RooRealVar *HFMass = (RooRealVar *)wspace->obj("HFMass");
    HFMass->setRange("signal", MM - 0.02, MM + 0.02); //Good
    //HFMass->setRange("sideband1", MM - 6. * M_sigma, MM - 3.0 * M_sigma); //7 , 5
    HFMass->setRange("sideband1", MM - ((1.86487-1.8125)/(0.0114)) * M_sigma, MM - 3.0 * M_sigma); //7 , 5
    HFMass->setRange("sideband2", MM + 3.0 * M_sigma, MM + ((1.9175-1.86487)/(0.0114)) * M_sigma); //5.25
    RooAbsReal *intbkgX = mass_bkgn->createIntegral(*HFMass, NormSet(*HFMass), Range("signal"));
    RooAbsReal *intbkg_sideband = mass_bkgn->createIntegral(*HFMass, NormSet(*HFMass), Range("sideband1", "sideband2"));
    intbkgX->Print();
    intbkg_sideband->Print();
    double bkg_scale = intbkgX->getVal() / intbkg_sideband->getVal();

    TLatex latex;

    TCanvas *cm = new TCanvas("cm", "c", 700, 900);
    cm->Divide(1, 2);
    cm->cd(1);
    ////////Chi2 Distributions////////
    RooRealVar D0_IPCHI2_OWNPV("D0_IPCHI2_OWNPV", "D0_IPCHI2_OWNPV", -3., 5.);
    D0_IPCHI2_OWNPV.setBins(nBins);

    RooDataHist D0x2("D0x2", "D0x2", RooArgList(D0_IPCHI2_OWNPV), hchi2, 1.); ///DISTRIBUTION TO FIT FULL PDF TO
    RooDataHist D0x2_bkg("D0x2_bkg", "D0x2_bkg", RooArgList(D0_IPCHI2_OWNPV), hchi2_bkg, 1.); ///DISTRIBUTION TO FIT BACKGROUND TO

    ////////Prompt Signal Distribution////////
    ///THESE VARIABLES WILL LIKELY NEED TO BE UPDATED FOR D0.  IF STRUGGLING, CONSULT PARAMETERS FROM D0 GROUP: https://gitlab.cern.ch/lhcb-ift/d0-production-in-ppb-at-8-tev/-/tree/master/Preparations
    ///SYNTAX: VAR(name, title, initial guess, min, max);
    RooRealVar mux("mux", "mux", .9, -5., 1.5); ///MEAN VALUE     -1. 0.9
    RooRealVar sigmax("sigmax", "sigmax", .7, 0.05, 0.9); ///WIDTH
    RooRealVar epsilon("epsilon", "epsilon", -.08, -.2, -.01); ///SKEW  -0.08 -.2
    RooRealVar rhoL("rhoL", "rhoL", -.08, -.3, -.003); ///LEFT TAIL
    RooRealVar rhoR("rhoR", "rhoR", 0.3, -3.5, 1.5); ///RIGHT TAIL
    RooBukinPdf sigx("sigx", "sigx", D0_IPCHI2_OWNPV, mux, sigmax, epsilon, rhoL, rhoR);

    /////////Secondaries Distribution/////////
    RooRealVar mu_sec("mu_sec", "mu_sec", 1.5, 1., 3.5); ///MEAN VALUE
    RooRealVar sigma_sec("sigma_sec", "sigma_sec", .7, 0.05, 0.9); ///WIDTH
    RooRealVar epsilon_sec("epsilon_sec", "epsilon_sec", -.08, -.2, -.01); ///SKEW
    RooRealVar rhoL_sec("rhoL_sec", "rhoL_sec", -.08, -.3, -.003); ///LEFT TAIL
    RooRealVar rhoR_sec("rhoR_sec", "rhoR_sec", .3, -3.5, 1.5); ///RIGHT TAIL
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

    //cout << nBins << endl;
    std::vector < double > means_bkg(0); ///ARRAY OF BACKGROUND LOG(CHI_IP^2) VALUES
    int num = 0;
    int num2 = 0; ///SIZE OF ARRAY TO RUN GAUSSIAN REGRESSION FIT ON

    for (int j = 0; j < nBins; j++) {
        if (hchi2_bkg->GetBinContent(j) > 0) {
            num2 = num + hchi2_bkg->GetBinContent(j);
            means_bkg.resize(num2, hchi2_bkg->GetBinCenter(j));
            num = num + hchi2_bkg->GetBinContent(j);
        }
    }

    cout << "size: " << num2 - 1 << endl;
    TKDE *kde2; ///KERNEL DENSITY ESTIMATOR (GAUSSIAN IN THIS CASE)

    if (num2 - 1 >= 0) {
        kde2 = new TKDE(num2 - 1, &means_bkg[0], -3., 5., "KernelTye:Gaussian", rho);
    }

    TF1 *func2;

    if (num2 - 1 >= 0) {
        hchi2_bkg->Scale(1. / hchi2_bkg->Integral(), "width"); ///NORMALIZE
        //hchi2_bkg->Draw();
        func2 = kde2->GetFunction(100, -3., 5.);
        //func2->SetFillColor(kGreen);
        //func2->SetFillStyle(3003);
        //func2->SetLineWidth(0);
        //func2->Draw("SAME && FC");
    }

    RooTFnPdfBinding comb("comb", "comb", func2, RooArgList(D0_IPCHI2_OWNPV)); ///PDF FOR COMBINATORIC BACKGROUND
    RooRealVar nsec("nsec", "nsec", 50000., 0., 10000000.); ///NUMBER OF SECONDARY D0 CANDIDATES
    RooRealVar ncomb("ncomb", "ncomb", hchi2_bkg->GetEntries() *bkg_scale, hchi2_bkg->GetEntries() *bkg_scale *0.95, hchi2_bkg->GetEntries() *bkg_scale *1.05); ///NUMBER OF COMBINATORIC BACKGROUND CANDIDATES
    RooRealVar meanxG2("meanxG2", "meanxG2", 3., .1, 12.);
    RooRealVar sigmaxG2("sigmaxG2", "sigmaxG2", 2.126, 0.5, 5.);
    RooAddPdf bkgx("bkgx", "bkgx", RooArgList(sec, comb), RooArgList(nsec, ncomb));
    RooFitResult *resbg;

    if (fitn == 0) {
        resbg = comb.fitTo(D0x2_bkg, PrintEvalErrors(-1));
    }

    if (fitn == 1) {
        resbg = comb.fitTo(D0x2_bkg, PrintEvalErrors(-1), InitialHesse(true));
    }

    // comb.fitTo(D0x2_bkg,PrintEvalErrors(-1));
    // mu_comb.setConstant(kTRUE);
    // sigma_comb.setConstant(kTRUE);
    // epsilon_comb.setConstant(kTRUE);
    // rhoL_comb.setConstant(kTRUE);
    // rhoR_comb.setConstant(kTRUE);

    /////////////Full Fit to Data/////////////
    RooRealVar nsigx("nsigx", "nsigx", 800000., 0., 10000000.); ///NUMBER OF PROMPT SIGNAL CANDIDATES
    RooRealVar nbkgx("nbkgx", "nbkgx", 45000., 0., 10000000.); ///NUMBER OF COMBINATORIC BACKGROUND AND SECONDARY CANDIDATES
    // RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,bkgx),RooArgList(nsigx, nbkgx));
    RooAddPdf sumx("sumx", "sumx", RooArgList(sigx, comb, sec), RooArgList(nsigx, ncomb, nsec)); ///MAY YIELD BETTER FIT RESULTS IF NEEDED
    //RooAddPdf sumx("sumx", "sumx", RooArgList(sigx,comb),RooArgList(nsigx, ncomb)); ///IF CERTAIN OF NO OR MINIMAL SECONDARY CANDIDATES, THIS PDF MAY BE OPTIMAL
    RooFitResult *res = sumx.fitTo(D0x2, PrintEvalErrors(-1), Save());

    /////////////////Plotting/////////////////
    double binsize = (MM + WM - (MM - WM)) / (double)nBins*1000.0;
    RooPlot *xframe = D0_IPCHI2_OWNPV.frame(Title(Form(";log_{10}(#chi^{2}_{IP});Events/(%.3f MeV) ", binsize)));
    D0x2.plotOn(xframe, Name("D0x2"), MarkerSize(0.2));
    sumx.plotOn(xframe, Name("sumx"), LineColor(kRed), PrintEvalErrors(-1), LineWidth(2));
// double chi2ndf = xframe->chiSquare(13);
    double chi2ndf = xframe->chiSquare(13);
    sumx.plotOn(xframe, Name("bkgx"), Components(bkgx), LineColor(kBlack), LineStyle(kDashed), PrintEvalErrors(-1));
    sumx.plotOn(xframe, Name("sigx"), Components(sigx), LineColor(kGreen), LineStyle(5), PrintEvalErrors(-1));
    sumx.plotOn(xframe, Name("sec"), Components(sec), FillColor(kMagenta), FillStyle(3165), LineWidth(0), DrawOption("F"), PrintEvalErrors(-1));
    sumx.plotOn(xframe, Name("comb"), Components(comb), FillColor(kBlue), FillStyle(3153), LineWidth(0), DrawOption("F"), PrintEvalErrors(-1));
    // D0x2_bkg.plotOn(xframe);
    D0x2.plotOn(xframe, MarkerSize(0.2));
    xframe->Draw("SAME");

    TLegend *leg1 = new TLegend(0.65, 0.6, 0.86, 0.87);
    // leg1->SetFillColor(kWhite);
    // leg1->SetLineColor(kWhite);
    leg1->SetBorderSize(0);
    leg1->AddEntry("D0x2", "Data", "PE");
    leg1->AddEntry("sumx", "Fit model", "L");
    leg1->AddEntry("sigx", "Signal", "L");
    leg1->AddEntry("sec", "D^{0} from b", "F");
    leg1->AddEntry("comb", "Comb. bkg.", "F");
    leg1->AddEntry((TObject *)0, Form("#chi^{2}/ndf = %.2f", chi2ndf), "");
    leg1->AddEntry((TObject *)0, Form("%.0f < M_{K#pi} < %.0f [MeV]", (MM - 0.02) * 1000., (MM + 0.02) * 1000.), "");
    leg1->Draw("SAME");
    res->Print();

    cm->cd(2);
    hchi2_bkg->Draw();

    cm->SaveAs("LogIPChiSquared_Fits.pdf");
    cout << "Chi2/ndf = " << chi2ndf << endl;
    cout << "Background entries = " << hchi2_bkg->GetEntries() << endl;
    f.Write();
    f.Close();

    double rec[2] = {
        nsigx.getValV(), nsigx.getError()
    };
    return rec;
    

                                                        //          (__)
                                                        //        /  .\/.     ______
                                                        //       |  /\_|     |      \
                                                        //       |  |___     |       |
                                                        //       |   ---@    |_______|
                                                        //    *  |  |   ----   |    |
                                                        //     \ |  |_____
                                                        //      \|________|
                                                        //CompuCow Discovers Bug in Compiler
                                                        //

}
