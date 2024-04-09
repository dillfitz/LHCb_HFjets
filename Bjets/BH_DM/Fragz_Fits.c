//  FF(z) Fits

//#define Fragz_Fitz_cxx
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
//#include "Settings.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include "TH1.h"
#include "TFile.h"
#include <vector>
#include <cmath>
#include <TMath.h>
#include <stdio.h>

using namespace RooFit;

void Fragz_Fits()
{
    //int nBins = 175;
    int nBins = 45;
    double z_low = 0.0;
    double z_high = 1.0;
    
    TFile fread("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/B_BH_Observables.root", "READ");
    TFile f("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/Fragz_BH_Fits_Data.root", "RECREATE");
    
    //TH1F *bzfit = (TH1F*)fread.Get("z");
    //bzfit->GetXaxis()->SetRangeUser(0.003, 0.999);
    
    TH1F *bzfit = new TH1F("bzfit","F(z)" , nBins, 0.0, 1.05);
    bzfit = (TH1F*)fread.Get("z");
    
    
    //RooRealVar x1("x1", "x1", 0.0, 1.0);
//    RooRealVar x("x", "x", 0.5, 0.9555);
    RooRealVar x("x", "x", 0.03, 0.98); //BEST!!!
 
    RooDataHist B_z("B_z","B_z", RooArgList(x), bzfit, 1.0);
    
    //RooDataHist B_z1("B_z1","B_z1", RooArgList(x), bzfit, 1.);
    
    x.setBins(nBins);
    //x1.setBins(nBins);

    
    // Lund-Bowler FFs
    RooRealVar a("a", "a", 1.0, 0.1, 40.0);
    RooRealVar b("b", "b", 3.5, 1.0, 60.0);
//    RooRealVar rb("rb", "rb", 1.0, 0.01, 10.0);
//    RooRealVar mt("mt", "mt", 50.0, 10., 100.);
    
    //RooGenericPdf genpdf1("genpdf1", "genpdf1", "( (1/x)*pow(1-x, alpha1)*exp(-beta1/x) )", RooArgList(x, alpha1, beta1));
//    RooGenericPdf genpdf("genpdf", "genpdf", "( (1/(pow(x, 1+rb*mt) ) )*pow(1-x, a)*exp(-mt/x) )", RooArgList(x, rb, mt, a));
    
    
    RooGenericPdf genpdf("genpdf", "genpdf", "( (1/x)*pow(1-x, a)*exp(-b/x) )", RooArgList(x, a, b));
    
//    fractions in signal
   // 59868.9 +/- 603.499,nb = 224172
    RooRealVar nb("nb", "fraction of B frag", 300, 10., 10000000.);
    //RooRealVar ng0("ng0", "fraction of g splits 0", 500, 300., 10000000.);
    //RooFormulaVar ng("ng", "new frac. in g splits", "1/2*nb", RooArgList( nb));
//    RooRealVar ng("ng", "fraction of g split", 200, 100., 10000000.);
    
    
//    x.setRange("first", 0.05, 0.955);
//    x.setRange("second", 0.05, 0.955);
    
    //x.setRange("first", 0.01, 0.999);
    x.setRange("gauss", 0.01, 0.6); //0.999
    x.setRange("second", 0.05, 0.955);
    x.setRange("full", 0.01, 0.98);
    //x.setRange("Full", z_low, z_high);

    //sig.fitTo(B_z, Range("gauss"));
//    genpdf1.chi2FitTo(B_z, Range("gauss"));
    genpdf.fitTo(B_z, Range("full"));
//    genpdf1.fitTo(B_z, Range("gauss"));
//    genpdf.fitTo(B_z, Range("second"));


    RooAddPdf * model;

    //RooRealVar bkgfrac("bkgfrac", "fraction of background", 300, 100., 100000.);
    //model = new RooAddPdf("model", "g1+g2+a", RooArgList(sig, genpdf), RooArgList(ng, nb));
   // model = new RooAddPdf("model", "g1+g2+a", RooArgList(genpdf1, genpdf), RooArgList(ng, nb));
    model = new RooAddPdf("model", "g1+g2+a", RooArgList( genpdf), RooArgList(nb));

    
    RooArgSet *params = model->getParameters(x);

    RooArgSet *initParams = (RooArgSet *)params->snapshot();
    
    model->fitTo(B_z, Range("full"), PrintEvalErrors(-1), Save(true));
//    model->fitTo(B_z, Range("full"), PrintEvalErrors(-1), Save(true));
    
    // Plot data and PDF overlaid
    TCanvas* c = new TCanvas("c", "c", 700, 900);
    c->Divide(1, 2);
    c->SetFillStyle(4070);
    
    c->cd(1);
//    double binsize = (z_high - z_low)/(double) nBins;
    
    RooRealVar x0("x0","x0",0.0, 1.05);
    
    RooPlot *xframe0 = x0.frame(Title("; z ;F(z) " ) );
    RooPlot *xframe = x.frame(Title("; z ;F(z) ") );
    //B_z.plotOn(xframe, Name("B_z"), Range("full"));
    B_z.plotOn(xframe, Name("B_z"), MarkerSize(0.68));
    
    model->plotOn(xframe0);

    // Overlay the background component of model with a dashed line
    //model->plotOn(xframe, Name("sig"), Components(sig), LineStyle(5), LineColor(kGreen+2));
//    model->plotOn(xframe, Name("genpdf1"), Components(genpdf1), LineStyle(5), LineColor(kGreen+2));
    model->plotOn(xframe, Name("genpdf"), Components(genpdf),  LineStyle(kDashed), LineColor(kBlue));
    model->plotOn(xframe, Name("model"), LineColor(kRed));
    
    double chi2;

    chi2 = xframe->chiSquare(4); //changed from 10 to 9

    xframe->Draw("SAME");
    gPad->SetLogy();
    //xframe->SetMinimum(1.) ;

    TLegend *leg1 = new TLegend(0.12,0.7,0.3,0.87);
 
     leg1->SetBorderSize(0);

    leg1->AddEntry("B_z","BHadron p_{T} > 20 GeV/c ", "PE");

     leg1->AddEntry("model","Fit model","L");
     //leg1->AddEntry("sig","Gluon Splits", "L");
//     leg1->AddEntry("genpdf1","Gluon Splits", "L");
     leg1->AddEntry("genpdf","Lund FF", "L");

     leg1->AddEntry((TObject*)0, Form("#chi^{2}/ndf = %.2f", chi2), "");

    leg1->Draw("SAME");
    //xframe->SetAxisRange(0., 1.);

    c->cd(2);
    
    RooAddPdf * model1;
    //model1 = new RooAddPdf("model1", "g1+g2+a", RooArgList(sig, genpdf), RooArgList(ng, nb));
    //model1 = new RooAddPdf("model1", "g1+g2+a", RooArgList(genpdf1, genpdf), RooArgList(ng, nb));
    model1 = new RooAddPdf("model1", "g1+g2+a", RooArgList( genpdf), RooArgList( nb));
   
//    RooArgSet *params1 = model1->getParameters(x);
//
//    RooArgSet *initParams1 = (RooArgSet *)params1->snapshot();
    model1->fitTo(B_z, PrintEvalErrors(-1), Save(true));
//    model1->fitTo(B_z, PrintEvalErrors(-1), Save(true));
    
    RooPlot *xframe1 = x.frame(Title("; z ; F(z)"));
    B_z.plotOn(xframe1, Name("B_z"));
    
    model1->plotOn(xframe0);
    
    //model1->plotOn(xframe1, Name("sig"), Components(sig), LineStyle(5), LineColor(kGreen+2));
//    model1->plotOn(xframe1, Name("genpdf1"), Components(genpdf1), LineStyle(5), LineColor(kGreen+2));
    model1->plotOn(xframe1, Name("genpdf"), Components(genpdf), LineStyle(kDashed), LineColor(kBlue));
    model1->plotOn(xframe1, Name("model1"), LineStyle(kSolid), LineColor(kRed));
    
    xframe1->Draw("SAME");
    
    TLegend *leg2 = new TLegend(0.12,0.6,0.4,0.88);
 
     leg2->SetBorderSize(0);

    leg2->AddEntry("B_z","MC Data  p_{T} > 20 GeV/c ", "PE");

     leg2->AddEntry("model1","Fit model","L");
     //leg2->AddEntry("sig","Gluon Splits", "L");
//     leg2->AddEntry("genpdf1","Gluon Splits", "L");
     leg2->AddEntry("genpdf","Lund-Bowler FF", "L");

     leg2->AddEntry((TObject*)0, Form("#chi^{2}/ndf = %.2f", chi2), "");

    leg2->Draw("SAME");

   
    c->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/plots/Bjets/FF_B_z_BH.pdf");

    cout<<"Chi2/dof = "<<chi2<<endl;
//
//    cout<<"alpha = "<<alpha.getVal()<<endl;
//    cout<<"beta = "<<beta.getVal()<<endl;
//    cout<<"a = "<<a.getVal()<<endl;
//    cout<<"b = "<<b.getVal()<<endl;
//    cout<<"gluon fraction = "<<ng.getVal()<<endl;
    cout<<"b fraction = "<<nb.getVal()<<endl;

    f.Write();
    f.Close();

    
   //

    
}


