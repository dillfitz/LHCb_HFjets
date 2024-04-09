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
//#include "../Settings.h"

using namespace RooFit;

void MassFit_MisID()
{

  double mup_px, mup_py, mup_pz, mup_e;
  double mum_px, mum_py, mum_pz, mum_e;
  double pi_px, pi_py, pi_pz, pi_e;
  double jet_pt;

  int nBins = 20;
  double mass_low = 5.0;
  double mass_high = 5.7;

  TFile fread("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/BBjetMisID_MC_BH_nojetid_663602.root  ", "READ");
  TFile f("/Users/josearias18/Desktop/QCDc2/pythia/Root_Files/Bjets/MFit_MisID_MC_50100_BH.root", "RECREATE");
    
  TH1F *h1_mass = (TH1F*)fread.Get("m_50_100");
    
  //TH1D * h1_mass = new TH1D ("h1_mass", "", nBins, mass_low, mass_high);
  //TH1D * h1_mass_all = new TH1D ("h1_mass_all", "", nBins+17, mass_low, mass_high);


   // S e t u p   c o m p o n e n t   p d f s
   // ---------------------------------------

   // Declare observable x
   RooRealVar x("x", "x", mass_low, mass_high);
   // Generate a data sample of 1000 events in x from model
   RooDataHist B_mass("B_mass","B_mass", RooArgList(x), h1_mass, 1.);

   x.setBins(nBins);

   // Create resonant background
   //DCB parameters
   RooRealVar mu("mu","mu",5.31,5.2,5.4);
   RooRealVar width("width","width",0.1,0.,1.);
   RooRealVar alpha1("alpha1","alpha1",1.,0.,10.);
   RooRealVar p1("p1","p1",1.,0.,10.);
   RooRealVar alpha2("alpha2","alpha2",1.,0.,10.);
   RooRealVar p2("p2","p2",1.,0.,10.);

   RooCrystalBall dcbPdf("dcbPdf","DoubleSidedCB",x,mu,width,alpha1,p1,alpha2,p2);

   // Build Chebychev polynomial pdf
   RooRealVar a1("a1", "a1",  1.0 , 1.0, 100.);
   RooRealVar a2("a2", "a2",  -2.0 , -2.0, 2.0); //-1
   RooPolynomial bkg("bkg", "Background", x, RooArgList(a1, a2));

   // ---------------------------------------------
   // M E T H O D   1 - T w o   R o o A d d P d f s
   // =============================================

   // A d d   s i g n a l   c o m p o n e n t s
   // ------------------------------------------

   // Sum the signal components into a composite signal pdf
   RooRealVar nsig("nsig", "fraction in signal",  200. , 100., 10000000.);
   RooRealVar nbkg("nbkg", "fraction of background", 10.0 , 0., 10000000.); //1.25136e-05


   // S a m p l e ,   f i t   a n d   p l o t   m o d e l
   // ---------------------------------------------------
   x.setRange("comb1", 5., 5.1);
   // Fit model to data
   // bkg.fitTo(B_mass, Range("comb1"));

   // RooAddPdf * model;
   // if(isData) model =new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, sig, tanhpdf), RooArgList(bkgfrac,tanhfrac));
   RooAddPdf * model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, dcbPdf), RooArgList(nbkg, nsig));
   // model->fitTo(B_mass, Range("noSec"), PrintEvalErrors(-1), Save(true));
   model->fitTo(B_mass, PrintEvalErrors(-1), Save(true));
    //model->chi2FitTo(B_mass, PrintEvalErrors(-1), Save(true));
    //model->Fit(B_mass, PrintEvalErrors(-1), Save(true));
    
   // Plot data and PDF overlaid
   TCanvas* c = new TCanvas("c", "c", 700, 900);
   c->Divide(1, 2);
   c->cd(1);
   gPad->SetLogy();
   double binsize = (mass_high - mass_low)/(double) nBins;
   RooPlot *xframe = x.frame(Title(Form(";M_{#mu#mu#pi} [GeV];Events/(%.1f MeV) ", binsize*1000.)));
   B_mass.plotOn(xframe, Name("B_mass"), MarkerSize(0.6));
   model->plotOn(xframe );
   // xframe2->addObject(xframe->pullHist());

   // Overlay the background component of model with a dashed line
   model->plotOn(xframe, Name("sig"), Components(dcbPdf), LineStyle(5), LineColor(kGreen+2));
   // model->plotOn(xframe, Components(sig2), LineStyle(kSolid), LineColor(kMagenta));
   model->plotOn(xframe, Name("bkg"), Components(bkg), LineStyle(kDashed), LineColor(kBlue));
   model->plotOn(xframe, Name("model"), LineWidth(1), LineStyle(kSolid), LineColor(kRed)); // LineWidth(1),
   Double_t chi2 = xframe->chiSquare(10);


   cout<<"Chi2/dof = "<<chi2<<endl;

   // Overlay the background+sig2 components of model with a dotted line
   // model->plotOn(xframe, Components(RooArgSet(bkg, sig2)), LineStyle(kDotted));
   // h1_mass_all->Draw("SAME");
   xframe->Draw("SAME");
   TLegend *leg1 = new TLegend(0.15,0.6,0.3,0.87);
    // leg1->SetFillColor(kWhite);
    // leg1->SetLineColor(kWhite);
    leg1->SetBorderSize(0);
//    leg1->AddEntry("B_mass","DiMuon p_{T} > 20 GeV/c ", "PE");
//    leg1->AddEntry("B_mass","DiMuon 20 GeV/c < p_{T} < 30 GeV/c ", "PE");
//        leg1->AddEntry("B_mass","DiMuon 30 GeV/c < p_{T} < 50 GeV/c ", "PE");
    leg1->AddEntry("B_mass","DiMuon 50 GeV/c < p_{T} < 100 GeV/c ", "PE");
//    leg1->AddEntry("B_mass","BHadron p_{T} > 20 GeV/c ", "PE");

    
    leg1->AddEntry("model","Fit model","L");
    leg1->AddEntry("sig","Signal", "L");
    leg1->AddEntry("bkg","Comb bkg", "L");
    leg1->AddEntry((TObject*)0, Form("#chi^{2}/ndf = %.2f", chi2), "");
    leg1->Draw("SAME");
   xframe->SetMinimum(1);
   // xframe2->SetMinimum(-5) ;
   // xframe2->SetMaximum(+5) ;
   // xframe2->Draw() ;

   c->cd(2);
   xframe->Draw("SAME");
   leg1->Draw("SAME");
    RooArgSet *params = model->getParameters(x);
    RooArgSet *initParams = (RooArgSet *)params->snapshot();
   //c->SaveAs("MFit_Int_OnlyB_MisID_MC.pdf");
//c->SaveAs("MFit_Int_All_MisID_MC.pdf");
   //c->SaveAs("MFit_2030_OnlyB_MisID_MC.pdf");
   //c->SaveAs("MFit_2030_All_MisID_MC.pdf");
   // c->SaveAs("MFit_3050_All_MisID_MC.pdf");
   //c->SaveAs("MFit_50100_OnlyB_MisID_MC.pdf");
   c->SaveAs("/Users/josearias18/Desktop/QCDc2/pythia/Plots/Bjets/BMFit_m50100_MisID_MC_BH.pdf");
  params->printLatex(Sibling(*initParams), OutputFile("/Users/josearias18/Desktop/QCDc2/pythia/RooFit_tex_Files/BMFit_m50100_MisID_MC_BH.tex"));


   f.Write();
   f.Close();
}
