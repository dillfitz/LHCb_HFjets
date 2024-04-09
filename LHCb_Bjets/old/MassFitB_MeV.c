//#define MassFitB_MeV_cxx
#include "RooAddPdf.h"
#include "RooConstVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolynomial.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TH1.h"
//#include "Settings.h"
#include <cmath>
#include <TCanvas.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TStyle.h>
#include <vector>
#include "TFile.h"
#include "TH1.h"

using namespace RooFit;

void MassFitB_MeV() {
//         (__)
//       /   @@      ______
//      |  /\_|     |      \
//      |  |___     |       |
//      |   ---@    |_______|
//      |  |   ----   |    |
//      |  |_____
//*____/|________|
//CompuCow After an All-niter

    int nBins = 100;
    double mass_high = 5.7;
    double mass_low = 5.0;

    //TFile fread("BJetsNoJetID_MsCut_All_DiMuon_1979178.root", "READ");
    //TFile f("MassFitB_All_50_100_DM.root", "RECREATE");
    //TFile fread("BJetsNoJetID_MsCut_OnlyB_DiMuon_1979178.root", "READ");
    //TFile f("MassFitB_OnlyB_50_100_DM.root", "RECREATE");

    //TFile fread("BJetsNoJetID_MassCut_OnlyB_841656.root", "READ");
    //TFile f("MassFitB_OnlyB_50_100_BH.root", "RECREATE");
    //TFile f("MassFitB_OnlyB_BH.root", "RECREATE");

    TFile fread("BJetsNoJetID_MassCut_All_841656.root", "READ");
    TFile f("MassFitB_All_50_100_BH.root", "RECREATE");

    TH1F *bMassfit = (TH1F *)fread.Get("m_50_100");
    //TH1F *bMassfit = (TH1F*)fread.Get("m_50_100");
    //bMassfit->GetXaxis()->SetRangeUser(5000.0/1000, 5700.0/1000);


    // S e t u p   c o m p o n e n t   p d f s
    // --------------------------------------- //

    // Declare observable x
    RooRealVar x("x", "x", mass_low, mass_high);
    // Generate a data sample of 1000 events in x from model
    RooDataHist B_mass("B_mass", "B_mass", RooArgList(x), bMassfit, 1.);

    x.setBins(nBins);

    // Create two Gaussian PDFs g1(x,mean1,sigma) anf g2(x,mean2,sigma) and their parameters
    ////////////////////////////////////////////////////
    // build signal
    ///////////////////////////////////////////////////

    // From simulation: massfit_reco_ev_-1_ptj_20150_eta_2.54.0_HF_ghost_0.5_b_90599.pdf
    // Signal: DoubleSidedCB
    // Background: Quadratic
    //  EXT PARAMETER                                INTERNAL      INTERNAL
    // NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE
    //  1  alpha1_sig   1.63822e+00   2.27641e-02   7.55669e-05  -6.89239e-01
    //  2  alpha2_sig   2.71078e+00   5.11079e-02   1.25443e-04  -4.08903e-01
    //  3  mu_sig       5.28036e+00   7.73468e-05   3.76861e-04   1.01738e+00
    //  4  nbkg         1.85875e+03   1.09603e+02   4.30800e-05  -1.48454e+00
    //  5  nsig         9.05636e+04   3.17363e+02   3.13537e-05  -9.59445e-01
    //  6  nsig1        2.21352e-01   2.20313e-02   3.51248e-04  -5.91126e-01
    //  7  p1_sig       2.85142e+00   1.43404e-01   3.50861e-04  -3.75085e-01
    //  8  p2_sig       1.16884e+00   8.95618e-02   3.20207e-04  -8.33455e-01
    //  9  sigma1       3.15958e-02   9.27469e-04   4.00448e-04   1.83058e-01
    // 10  sigma2       1.78528e-02   1.77464e-04   1.00775e-04  -2.69847e+00
    
    RooRealVar sigma_ratio("sigma_ratio", "sigma_ratio", 1.78528 / 3.15958);
    RooRealVar mean("mean", "mean of gaussians", 5.279, 5.27, 5.282);  //5.282
    RooRealVar sigma1("sigma1", "width of gaussians", 0.03, 0.008, 0.07);
    RooRealVar sigma2("sigma2", "width of gaussians", 0.035, 0.009, 0.07);  //CHANGE
    // RooFormulaVar sigma2("sigma2", "width of gaussians", "sigma1*sigma_ratio", RooArgList(sigma1,sigma_ratio)); //CHANGE
    // if(isData){
    //   sigma2.setVal(0.01);
    //   // sigma2.setConstant(kTRUE);
    // }
    RooGaussian gauss1("gauss_sig1", "Signal component 1", x, mean, sigma1);
    RooGaussian gauss2("gauss_sig2", "Signal component 2", x, mean, sigma2);

    // Or, Create signal from two Crystal Ball functions
    // These parameters have been derived from simulation

    RooRealVar mu_sig, alpha1_sig, alpha2_sig, p1_sig, p2_sig;

    mu_sig = RooRealVar("mu_sig", "mu", 5.276, 5.26, 5.282);
    alpha1_sig = RooRealVar("alpha1_sig", "alpha1", 1.63822e+00); //CHANGE
    p1_sig = RooRealVar("p1_sig", "p1", 2.85142e+00); //CHANGE
    alpha2_sig = RooRealVar("alpha2_sig", "alpha2", 2.71078e+00); //CHANGE
    p2_sig = RooRealVar("p2_sig", "p2", 1.16884e+00); //CHANGE

//     //Define the CB functions
    RooCrystalBall dcbPdf_sig1("dcbPdf_sig1", "DoubleSidedCB_sig1", x, mu_sig, sigma1, alpha1_sig, p1_sig, alpha2_sig, p2_sig);
    RooCrystalBall dcbPdf_sig2("dcbPdf_sig2", "DoubleSidedCB_sig2", x, mu_sig, sigma2, alpha1_sig, p1_sig, alpha2_sig, p2_sig);

//     //Number of signal events
    RooRealVar nsig1("nsig1", "fraction of component 1 in signal", 0.3, 0., 1.);
//
//     // Choose if you want two CB functions as signal, or two Gaussians.
//
    //RooAddPdf sig("sig", "Signal", RooArgList(gauss1, gauss2), RooArgList(nsig1));
    RooAddPdf sig("sig", "Signal", RooArgList(dcbPdf_sig1, dcbPdf_sig2), RooArgList(nsig1));
//
//
//     //
    RooRealVar mean_nosec("mean_nosec", "mean of gaussians", 5.279, 5.25, 5.285);
    RooRealVar sigma1_nosec("sigma1_nosec", "width of gaussians", 0.05, 0, 0.1);
    RooRealVar sigma2_nosec("sigma2_nosec", "width of gaussians", 0.01, 0, 0.1);

    RooGaussian sig1_nosec("sig1", "Signal component 1", x, mean_nosec, sigma1_nosec);
    RooGaussian sig2_nosec("sig2", "Signal component 2", x, mean_nosec, sigma2_nosec);

    RooRealVar nsig1_nosec("nsig1_nosec", "fraction of component 1 in signal", 0.3, 0., 1.);
    RooAddPdf sig_nosec("sig_nosec", "Signal", RooArgList(sig1_nosec, sig2_nosec), RooArgList(nsig1_nosec));



    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // build resonant structure, values from simulation
    ///////////////////////////////////////////////////
    //  EXT PARAMETER                APPROXIMATE     INTERNAL      INTERNAL
    // NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE
    //  1  a1           6.43008e-01   8.56674e-05   1.54803e-02  -1.41025e+00
    //  2  a2          -1.19108e-01   1.08566e+00   1.01677e-02  -1.19391e-01
    //  3  alpha1       1.72233e+00   2.60362e-02   8.63029e-04  -7.14890e-01
    //  4  alpha2       7.67677e-01   5.81233e-03   5.15204e-04  -1.00931e+00
    //  5  mu           5.33183e+00   6.36345e-05   1.12015e-04   2.66817e-01
    //  6  nbkg         4.71399e+01   3.32483e+02   2.31091e-03  -1.55706e+00
    //  7  nsig         3.84348e+04   6.12826e+01   2.73946e-04  -1.17614e+00
    //  8  p1           1.73799e+00   9.69703e-02   2.26342e-03  -7.10748e-01
    //  9  p2           2.09840e+00   3.32066e-02   1.24263e-03  -6.19123e-01
    // 10  width        2.62897e-02   4.95521e-05   2.87488e-04  -1.24508e+00

    // Marcos MisID simulations
    //
    // Back-to-Back Cut pt>20 GeV/c //
//     RooRealVar mu("mu","mu", 5.33145e+00);
//     RooRealVar width("width","width",2.41931e-02);
//     RooRealVar alpha1("alpha1","alpha1",1.58367e+00);
//     RooRealVar alpha2("alpha2","alpha2",6.81775e-01);
//     RooRealVar p1("p1","p1",2.50675e+00);
//     RooRealVar p2("p2","p2",2.54975e+00);

    // Back-to-Back Cut 20<pt<30 GeV/c //
//     RooRealVar mu("mu","mu", 5.33163e+00);
//     RooRealVar width("width","width",2.40792e-02);
//     RooRealVar alpha1("alpha1","alpha1",1.58424e+00);
//     RooRealVar alpha2("alpha2","alpha2",6.79837e-01);
//     RooRealVar p1("p1","p1",2.58692e+00);
//     RooRealVar p2("p2","p2",2.57868e+00);

    // Back-to-Back Cut 30<pt<50 GeV/c //
//     RooRealVar mu("mu","mu", 5.32977e+00);
//     RooRealVar width("width","width",2.31727e-02);
//     RooRealVar alpha1("alpha1","alpha1",1.34413e+00);
//     RooRealVar alpha2("alpha2","alpha2",6.13680e-01);
//     RooRealVar p1("p1","p1",4.78424e+00);
//     RooRealVar p2("p2","p2",3.06414e+00);

    // Back-to-Back Cut 50<pt<100 GeV/c //
//    RooRealVar mu("mu","mu", 5.33304e+00);
//    RooRealVar width("width","width",3.21125e-02);
//    RooRealVar alpha1("alpha1","alpha1",5.03474e+00);
//    RooRealVar alpha2("alpha2","alpha2",8.52233e-01);
//    RooRealVar p1("p1","p1",2.55645e+00);
//    RooRealVar p2("p2","p2",3.21125e+00);

    //No Back-to-Back Cut pt>20 GeV/c
//    RooRealVar mu("mu","mu", 5.33138e+00);
//    RooRealVar width("width","width",2.44110e-02);
//    RooRealVar alpha1("alpha1","alpha1",1.5827e+00);
//    RooRealVar alpha2("alpha2","alpha2",6.73688e-01);
//    RooRealVar p1("p1","p1",2.4699e+00);
//    RooRealVar p2("p2","p2",2.56793e+00);

    //No Back-to-Back Cut 20<pt<30 GeV/c
//    RooRealVar mu("mu","mu", 5.33140e+00);
//    RooRealVar width("width","width",2.41013e-02);
//    RooRealVar alpha1("alpha1","alpha1",1.58972e+00);
//    RooRealVar alpha2("alpha2","alpha2",6.66027e-01);
//    RooRealVar p1("p1","p1",2.47458e+00);
//    RooRealVar p2("p2","p2",2.61347e+00);
//
    //No Back-to-Back Cut 30<pt<50 GeV/c
//    RooRealVar mu("mu","mu", 5.33130e+00);
//    RooRealVar width("width","width",2.54564e-02);
//    RooRealVar alpha1("alpha1","alpha1",1.53177+00);
//    RooRealVar alpha2("alpha2","alpha2",6.90474e-01);
//    RooRealVar p1("p1","p1",2.99343e+00);
//    RooRealVar p2("p2","p2",2.63195e+00);

    //No Back-to-Back Cut 50<pt<100 GeV/c
    RooRealVar mu("mu", "mu", 5.32954e+00);
    RooRealVar width("width", "width", 2.76279e-02);
    RooRealVar alpha1("alpha1", "alpha1", 1.63195e+00);
    RooRealVar alpha2("alpha2", "alpha2", 6.35866e-01);
    RooRealVar p1("p1", "p1", 2.57232e+00);
    RooRealVar p2("p2", "p2", 3.41858e+00);

    RooCrystalBall dcbPdf("dcbPdf", "DoubleSidedCB", x, mu, width, alpha1, p1, alpha2, p2);

    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Build argus background PDF, I can't get this to work, so DISREGARD FOR NOW!
    /////////////////////////////////////////////////////////////////////////////////

    RooRealVar m_arg("m_arg", "m", 5.15, 5.1, 5.17);  // The peak position of the Argus function
    RooRealVar c_arg("c_arg", "c", -20, -30, -1);  // The curvature parameter of the Argus function
    RooRealVar n_arg("n_arg", "n", 0.5);  // The power-law index of the Argus function

    RooRealVar mean_arg("mean_arg", "mean", 0);  // The mean of the Gaussian function
    // RooFormulaVar sigma_arg("sigma_arg", "sigma", "sqrt(sigma1*sigma1*nsig1 + (1-nsig1)*sigma2*sigma2)", RooArgList(sigma1, sigma2, nsig1));  // The standard deviation of the Gaussian function
    RooRealVar sigma_arg("sigma_arg", "sigma", 0.01, 0.001, 0.05);

    // Create the Argus function and the Gaussian function
    RooArgusBG argus("argus", "argus", x, m_arg, c_arg, n_arg);
    RooGaussian gauss_arg("gauss_arg", "Signal component 2", x, mean_arg, sigma_arg);

    RooFFTConvPdf argxgauss("argxgauss", "argus (X) gauss", x, argus, gauss_arg);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Build tanh background PDF, left shoulder background
    ///////////////////////////////////////////////////

    RooRealVar b1("b1", "scale", 0.015, 0.001, 0.04);
    //RooRealVar b2("b2", "scale", 0.015, 0.001, 0.07);
    RooRealVar s1("s1", "shift", 5.14, 5.12, 5.16);
    //RooRealVar s2("s2", "shift", 4.95, 4.92, 4.96);
    RooGenericPdf tanhpdf("tanhpdf", "tanhpdf", "1 - tanh((x-s1)/b1)", RooArgSet(x, b1, s1));
    // RooGenericPdf tanhpdf("tanhpdf", "tanhpdf", "tanh((x-s2)/b2) - tanh((x-s1)/b1)", RooArgSet(x, b1, b2, s1, s2));


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Build linear background PDF, for combinatoric background
    ///////////////////////////////////////////////////

    // RooRealVar a2("a2", "a2", -0.5, -1, 1.);
    RooRealVar a1("a1", "a1", 2, 0., 9.);
    RooRealVar a2("a2", "a2", -1, -2, -0.1);
    RooPolynomial bkg("bkg", "Background", x, RooArgList(a1, a2));
    // RooGenericPdf bkg("bkg", "Background", "a2*x +a1", RooArgSet(x, a2, a1));

    RooRealVar exp_c("exp_c", "exp_c", -0.01, -1, -0.0001);
    RooExponential exp_bkg("exp_bkg", "exp_bkg", x, exp_c);

    RooRealVar a0_nosec("a0_nosec", "a0_nosec", 0.5, -1, 1.);
    RooRealVar a1_nosec("a1_nosec", "a1_nosec", 0.2, 0., 1.);
    RooChebychev bkg_nosec("bkg_nosec", "Background_nosec", x, RooArgSet(a0_nosec, a1_nosec));


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Fractions
    ///////////////////////////////////////////////////

    // RooRealVar nsig2("nsig2", "fraction of component 2 in signal", 0.6, 0., 1.);
    RooRealVar nsig("nsig", "fraction in signal", 8000, 3000.0, 10000000.);  // 2.43994e+04

    // RooRealVar nsig2("nsig2", "fraction of component 2 in signal", 0.6, 0., 1.);
    RooRealVar nsig_nosec("nsig_nosec", "fraction in signal", 500, 100., 10000000.);
    RooRealVar nbkg_nosec("nbkg_nosec", "fraction of background", 200, 100., 10000000.);
    RooRealVar nres_nosec("nres_nosec", "fraction of background", 200, 100., 10000000.);

    RooRealVar nbkg("nbkg", "fraction of background", 800, 600., 1000000.);
    RooRealVar ntanh("ntanh", "fraction of background", 800, 600., 10000000.);
    //RooRealVar nres0("nres0", "fraction of background", 100, 0., 10000000.);
    //RooFormulaVar nres("nres", "new frac. in bckg", "0.0384*nres0*nsig", RooArgList(nres0, nsig)); //914.946 0.2354 0.0384*
    RooFormulaVar nres("nres", "new frac. in bckg", "0.0384*nsig", RooArgList(nsig));


    // S a m p l e ,   f i t   a n d   p l o t   m o d e l
    // ---------------------------------------------------
    x.setRange("comb1", 5.550, 5.7);
    x.setRange("comb2", RooConst(mass_low), RooConst(mass_low + 0.1));
    x.setRange("tanh", 5.000, 5.2);
    x.setRange("noSec", 5.18, 5.6);
    x.setRange("Full", mass_low, mass_high);


    // Fit model to data
    bkg.fitTo(B_mass, Range("comb1", "comb2"));
    exp_bkg.fitTo(B_mass, Range("comb1", "comb2"));
    a1.setConstant(kTRUE);
    a2.setConstant(kTRUE);
    exp_c.setConstant(kTRUE);
    bkg_nosec.fitTo(B_mass, Range("comb1"));
    // tanhpdf.fitTo(B_mass, Range("tanh"));
    // res_comp1.fitTo(B_mass, Range("reso1"));
    // res_comp2.fitTo(B_mass, Range("reso2"));
    RooAddPdf *model, *model_nosec;

    model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, sig, tanhpdf, dcbPdf), RooArgList(nbkg, nsig, ntanh, nres));

    model_nosec = new RooAddPdf("model_nosec", "g1+g2+a", RooArgList(bkg_nosec, sig_nosec, dcbPdf), RooArgList(nbkg_nosec, nsig_nosec, nres_nosec));
    // model->fitTo(B_mass, Range("noSec"), PrintEvalErrors(-1), Save(true));

    // Make list of model parameters
    RooArgSet *params = model->getParameters(x);
    // Save snapshot of prefit parameters
    RooArgSet *initParams = (RooArgSet *)params->snapshot();


    model->fitTo(B_mass, PrintEvalErrors(-1), Save(true));
    model_nosec->fitTo(B_mass, Range("noSec"), PrintEvalErrors(-1), Save(true));


    // Plot data and PDF overlaid
    TCanvas *c = new TCanvas("c", "c", 700, 900);
    c->Divide(1, 2);
    c->SetFillStyle(4070);
    c->cd(1);
    double binsize = (mass_high - mass_low) / (double)nBins;
    RooPlot *xframe = x.frame(Title(Form(";M_{#mu#muK} [GeV];Events/(%.1f MeV) ", binsize * 1000.)));
    // model->paramOn(xframe, Layout(0.6, 0.9, 0.9));
    // xframe->getAttText()->SetTextSize(0.02);
    B_mass.plotOn(xframe, Name("B_mass"));
    model->plotOn(xframe);
    // xframe2->addObject(xframe->pullHist());

    // Overlay the background component of model with a dashed line
    model->plotOn(xframe, Name("sig"), Components(sig), LineStyle(5), LineColor(kGreen + 2));
    // sig.plotOn(xframe, Name("sig"), LineStyle(kSolid), LineColor(kGreen), Range("Full"));
    // model->plotOn(xframe, Components(sig2), LineStyle(kSolid), LineColor(kMagenta));
    model->plotOn(xframe, Name("tanhpdf"), Components(tanhpdf), FillColor(TColor::GetColorTransparent(kCyan, 0.7)), FillStyle(4070), LineWidth(0), DrawOption("F"));
    //model->plotOn(xframe, Name("argxgauss"), Components(argxgauss), FillColor(kCyan), DrawOption("F"));
    model->plotOn(xframe, Name("bkg"), Components(bkg), LineStyle(kDashed), LineColor(kBlue));
    model->plotOn(xframe, Name("dcbPdf"), Components(dcbPdf), FillColor(TColor::GetColorTransparent(kMagenta, 0.7)), FillStyle(3165), LineWidth(0), DrawOption("F"));
    model->plotOn(xframe, Name("model"), LineStyle(kSolid), LineColor(kRed));
    double chi2;
//     if(isData)
    chi2 = xframe->chiSquare(9);  //changed from 10 to 9
//     else chi2 = xframe->chiSquare(10);


    // exp_bkg.plotOn(xframe, LineColor(kMagenta));

    // Overlay the background+sig2 components of model with a dotted line
    // model->plotOn(xframe, Components(RooArgSet(bkg, sig2)), LineStyle(kDotted));
    // h1_mass_all->Draw("SAME");
    xframe->Draw("SAME");
    gPad->SetLogy();
    xframe->SetMinimum(1.);

    TLegend *leg1 = new TLegend(0.6, 0.6, 0.87, 0.88);
    // leg1->SetFillColor(kWhite);
    // leg1->SetLineColor(kWhite);
    leg1->SetBorderSize(0);
    //leg1->AddEntry("B_mass","Data", "PE");

    //leg1->AddEntry("B_mass","Bhadron Stream All p_{T} > 20 GeV/c", "PE");
    //leg1->AddEntry("B_mass","Bhadron All 20 GeV/c < p_{T} < 30 GeV/c", "PE");
    //leg1->AddEntry("B_mass","Bhadron All 30 GeV/c < p_{T} < 50 GeV/c ", "PE");
    leg1->AddEntry("B_mass", "Bhadron All 50 GeV/c < p_{T} < 100 GeV/c ", "PE");

    //leg1->AddEntry("B_mass","Bhadron Stream p_{T} > 20 GeV/c", "PE");
    //leg1->AddEntry("B_mass","Bhadron Stream 20 GeV/c < p_{T} < 30 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Bhadron Stream 30 GeV/c < p_{T} < 50 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Bhadron Stream 50 GeV/c < p_{T} < 100 GeV/c ", "PE");

    //leg1->AddEntry("B_mass","Dimuon Stream p_{T} > 20 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Dimuon 20 GeV/c < p_{T} < 30 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Dimuon 30 GeV/c < p_{T} < 50 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Dimuon 50 GeV/c < p_{T} < 100 GeV/c ", "PE");

    //leg1->AddEntry("B_mass","Dimuon All p_{T} > 20 GeV/c", "PE");
    //leg1->AddEntry("B_mass","Dimuon All 20 GeV/c < p_{T} < 30 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Dimuon All 30 GeV/c < p_{T} < 50 GeV/c ", "PE");
    //leg1->AddEntry("B_mass","Dimuon All 50 GeV/c < p_{T} < 100 GeV/c ", "PE");

    leg1->AddEntry("model", "Fit model", "L");
    leg1->AddEntry("sig", "Signal", "L");
    leg1->AddEntry("bkg", "Comb. bkg.", "L");
    leg1->AddEntry("tanhpdf", "Part. Rec. bkg.", "F");
    leg1->AddEntry("dcbPdf", "misID bkg.", "F");
    leg1->AddEntry((TObject *)0, Form("#chi^{2}/ndf = %.2f", chi2), "");

    leg1->Draw("SAME");
    // xframe->SetT
    // xframe2->SetMaximum(+5) ;
    // xframe2->Draw() ;

    c->cd(2);
    // RooPlot *xframe2 = x.frame();
    // B_mass.plotOn(xframe2);
    // model_nosec->plotOn(xframe2);
    // model_nosec->plotOn(xframe2, Components(bkg_nosec), LineStyle(kDashed), LineColor(kRed));
    // model_nosec->plotOn(xframe2, Components(sig_nosec), LineStyle(kSolid), LineColor(kGreen));
    // model_nosec->plotOn(xframe2, LineStyle(kSolid), LineColor(kBlue));
    xframe->Draw("SAME");
    leg1->Draw("SAME");

    //c->SaveAs("BMassFit_AllDiMuon_MeV.pdf");
    //c->SaveAs("BMassFit_All_20_30_DiMuon_MeV.pdf");
    //c->SaveAs("BMassFit_All_30_50_DiMuon_MeV.pdf");
    //c->SaveAs("BMassFit_All_50_100_DiMuon_MeV.pdf");

    //c->SaveAs("BMassFit_OnlyB_DiMuon_MeV.pdf");
    //c->SaveAs("BMassFit_OnlyB_20_30_DiMuon_MeV.pdf");
    //c->SaveAs("BMassFit_OnlyB_30_50_DiMuon_MeV.pdf");
    //c->SaveAs("BMassFit_OnlyB_50_100_DiMuon_MeV.pdf");

    //c->SaveAs("BMassFit_All_Bhadron_MeV.pdf");
    //c->SaveAs("BMassFit_All_20_30_Bhadron_MeV.pdf");
    //c->SaveAs("BMassFit_All_30_50_Bhadron_MeV.pdf");
    c->SaveAs("BMassFit_All_50_100_Bhadron_MeV.pdf");

    // c->SaveAs("BMassFit_OnlyB_Bhadron_MeV.pdf");
    //c->SaveAs("BMassFit_OnlyB_20_30_Bhadron_MeV.pdf");
    //c->SaveAs("BMassFit_OnlyB_30_50_Bhadron_MeV.pdf");
    //c->SaveAs("BMassFit_OnlyB_50_100_Bhadron_MeV.pdf");

    cout << "Chi2/dof = " << chi2 << endl;
    //cout<<sigma_arg.getVal()<<endl;
    cout << "a1 = " << a1.getVal() << endl;
    cout << "a1 = " << a2.getVal() << endl;
    cout << "sigma2 = " << sigma2.getVal() << endl;
    cout << "nres = " << nres.getVal() << endl;
    // cout<<exp_c.getVal()<<endl;
    params->printLatex(Sibling(*initParams), OutputFile("BMass_BH_All_50_100_params.tex"));


    f.Write();
    f.Close();
}
