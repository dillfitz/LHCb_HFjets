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

#include "../Reference/Settings.h"

using namespace RooFit;

void UnbinnedMassFit(int NumEvts = 10000, int dataset = 1510, bool isData = true,
             bool followHardest_user = false, bool chargedJetCut_user = false)
{
  bool MCflag = !isData;
  followHardest = followHardest_user;
  truthLevel = false;
  chargedJetCut = chargedJetCut_user;
  if (truthLevel)
  {
    ghostCut = false;
  }
  int JetMeth = (dataset / 1000) % 10;
  int flavor = (dataset / 100) % 10;
  int ptRange = (dataset / 10) % 10;
  int Mag = (dataset / 1) % 10;
  int HF_pdgcode = -99;
  if (flavor == 5)
  {
    mass_num = 4.2;
    HF_pdgcode = 521;
  }
  else if (flavor == 4)
  {
    mass_num = 1.25;
    HF_pdgcode = 421;
  }
  else if (flavor == 1)
  {
    mass_num = 0.001;
    followHardest = true;
  }
  TString str_Mag = "";
  TString str_pT = "";
  TString str_level = "";
  TString str_followHard = "";
  TString str_flavor = "";
  TString str_ghost = "";
  TString str_charged = "";
  if (Mag == 0)
    str_Mag = "_MD";
  else if (Mag == 1)
    str_Mag = "_MU";
  if (flavor == 1)
    str_flavor = "_udsg";
  else if (flavor == 4)
    str_flavor = "_c";
  else if (flavor == 5)
    str_flavor = "_b";
  if (isData)
    str_level = "data";
  else
  {
    if (truthLevel)
      str_level = "truth";
    else
      str_level = "reco";
  }
  if (flavor == 1)
    str_followHard = "_hard";
  else
  {
    if (followHardest)
      str_followHard = "_hard";
    else
      str_followHard = "_HF";
  }

  if (ghostCut)
    str_ghost = Form("_ghost_%.1f", ghostProb);

  if (chargedJetCut)
    str_charged = "_charge";

    
    TString extension_read, extension_RootFilesMC_misID, extension;
    
  extension = TString("massfit_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
  // Setup Tree

    extension_RootFilesMC_misID = TString("../../root_files/BjetsMC/MisID/");
    
  extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

  TFile fread( extension_RootFilesMC_misID + extension_read + ".root", "READ");
  TFile f(extension_RootFilesMC_misID  + extension + ".root", "RECREATE");
  TTree *BTree = (TTree *)fread.Get("BTree");
  if (NumEvts > BTree->GetEntries())
    NumEvts = BTree->GetEntries();
  if (NumEvts == -1)
    NumEvts = BTree->GetEntries();
  cout << BTree->GetEntries() << endl;
    
//  double mup_px, mup_py, mup_pz, mup_e;
//  double mum_px, mum_py, mum_pz, mum_e;
//  double pi_px, pi_py, pi_pz, pi_e;
//  double jet_pt, jet_rap, bmass_dtf, dtf_chi2ndf;
    float jet_pt, jet_rap;
    float mup_px, mup_py, mup_pz, mup_e;
    float mum_px, mum_py, mum_pz, mum_e;
    float pi_px, pi_py, pi_pz, pi_e;
    float bmass_dtf, dtf_chi2ndf;

  BTree->SetBranchAddress("mum_px", &mum_px);
  BTree->SetBranchAddress("mum_py", &mum_py);
  BTree->SetBranchAddress("mum_pz", &mum_pz);
  BTree->SetBranchAddress("mum_e", &mum_e);

  BTree->SetBranchAddress("mup_px", &mup_px);
  BTree->SetBranchAddress("mup_py", &mup_py);
  BTree->SetBranchAddress("mup_pz", &mup_pz);
  BTree->SetBranchAddress("mup_e", &mup_e);

  BTree->SetBranchAddress("pi_px", &pi_px);
  BTree->SetBranchAddress("pi_py", &pi_py);
  BTree->SetBranchAddress("pi_pz", &pi_pz);
  BTree->SetBranchAddress("pi_e", &pi_e);

  BTree->SetBranchAddress("jet_pt", &jet_pt);
  BTree->SetBranchAddress("jet_rap", &jet_rap);
  BTree->SetBranchAddress("bmass_dtf", &bmass_dtf);
  BTree->SetBranchAddress("dtf_chi2ndf", &dtf_chi2ndf);

  int nBins = 100;
  double mass_low = 5.15;
  double mass_high = 5.55;
  double pionMass = 0.139570;
  double kaonMass = 0.493677;
  double jpsiMass = 3.096916;

  if (isData)
    mass_low = 5.;
  TH1D *h1_mass = new TH1D("h1_mass", "", nBins, mass_low, mass_high);
  TH1D *h1_mass_all = new TH1D("h1_mass_all", "", nBins + 17, mass_low, mass_high);
  for (int ev = 0; ev < NumEvts; ev++)
  {
    BTree->GetEntry(ev);

    if (ev % 10000 == 0)
      cout << "Executing event " << ev << endl;
    // if (jet_pt < ptMin)
    //   continue;
    if (jet_rap < etaMin || jet_rap > etaMax)
      continue;
    TLorentzVector HFmeson, HFjet, mum, mup, pion, jpsi, Bfromjet;
    mup.SetPxPyPzE(mup_px, mup_py, mup_pz, mup_e);
    mum.SetPxPyPzE(mum_px, mum_py, mum_pz, mum_e);
    jpsi = mup + mum;
    jpsi.SetE(sqrt(jpsi.E() * jpsi.E() - jpsi.M() * jpsi.M() + jpsiMass * jpsiMass));
    pion.SetPxPyPzE(pi_px, pi_py, pi_pz, pi_e);
    HFmeson = jpsi + pion;

    // cout << pion.M() << ", " << jpsi.M() << endl;
    // cout<<HFmeson.M()<<endl;
    // h1_mass->Fill(bmass_dtf);
    // h1_mass_all->Fill(bmass_dtf);
    h1_mass->Fill(HFmeson.M());
    h1_mass_all->Fill(HFmeson.M());
    // if (dataset == 92599)
    // {
    //   h1_mass->Fill(bmass_dtf);
    //   h1_mass_all->Fill(bmass_dtf);
    // }
    // else
    // {
    //   h1_mass->Fill(HFmeson.M());
    //   h1_mass_all->Fill(HFmeson.M());
    // }
  }
  // h1_mass->Scale(1./h1_mass->GetEntries());

  // S e t u p   c o m p o n e n t   p d f s
  // ---------------------------------------

  // Declare observable x
  RooRealVar x("x", "x", mass_low, mass_high);
  // Generate a data sample of 1000 events in x from model
  RooDataHist B_mass("B_mass", "B_mass", RooArgList(x), h1_mass, 1.);
//    RooDataHist B_mass("B_mass", "B_mass", RooArgList(x), h1_mass_all, 1.);

  x.setBins(nBins);

  // Create resonant background
  // DCB parameters
  
//    RooRealVar mu("mu","mu",5.32631e+00,5.2,5.4);
//    RooRealVar width("width","width",0.014,0.005, 1.);
//    RooRealVar alpha1("alpha1","alpha1",1.59571e+00,0.,10.);
//    RooRealVar alpha2("alpha2","alpha2",4.58619e-01 ,0.,10.);
    
  RooRealVar mu("mu", "mu", 5.32631e+00, 5.25, 5.45); //
  RooRealVar width("width", "width", 1.48430e-02, 0.005, 1.); //
//    RooRealVar width("width", "width", 1.1e-02, 0.005, 1.); //
  RooRealVar alpha1("alpha1", "alpha1", 1.59571e+00, 0., 5.); //
  RooRealVar alpha2("alpha2", "alpha2", 4.58619e-01, 0., 5.); //

//    RooRealVar p1("p1","p1",1.,0.,10.);
//    RooRealVar p2("p2","p2",1.,0.,10.);

  RooRealVar p1("p1", "p1", 1.0, 1.0, 1.0); //
  RooRealVar p2("p2", "p2", 2.0, 2.0, 2.0);//

  RooCrystalBall dcbPdf("dcbPdf", "DoubleSidedCB", x, mu, width, alpha1, p1, alpha2, p2);

  // Build Chebychev polynomial pdf
//    RooRealVar a1("a1", "a1",  1.0 , 1.0, 100.);
//    RooRealVar a2("a2", "a2",  -2.0 , -2.0, 2.0); //-1

  RooRealVar a1("a1", "a1", 2, 0., 100.);//
  RooRealVar a2("a2", "a2", -1, -1, 1); //
  RooPolynomial bkg("bkg", "Background", x, RooArgList(a1, a2));

  // ---------------------------------------------
  // M E T H O D   1 - T w o   R o o A d d P d f s
  // =============================================

  // A d d   s i g n a l   c o m p o n e n t s
  // ------------------------------------------

  // Sum the signal components into a composite signal pdf
  RooRealVar nsig("nsig", "fraction in signal", 900, 0., 1000000.);
//    RooRealVar nbkg("nbkg", "fraction of background", 200, 0., 1000000);
  RooRealVar nbkg("nbkg", "fraction of background", 0., 0., 0.);

  // S a m p l e ,   f i t   a n d   p l o t   m o d e l
  // ---------------------------------------------------
  x.setRange("comb1", 5., 5.1);
  // Fit model to data
//   bkg.fitTo(B_mass, Range("comb1"));

  // RooAddPdf * model;
  // if(isData) model =new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, sig, tanhpdf), RooArgList(bkgfrac,tanhfrac));
  RooAddPdf *model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, dcbPdf), RooArgList(nbkg, nsig));

  // model->fitTo(B_mass, Range("noSec"), PrintEvalErrors(-1), Save(true));
  model->fitTo(B_mass, PrintEvalErrors(-1), Save(true));

  // Plot data and PDF overlaid
  TCanvas *c = new TCanvas("c", "c", 700, 900);
  c->Divide(1, 2);
  c->cd(1);
  gPad->SetLogy();
  double binsize = (mass_high - mass_low) / (double)nBins;
  RooPlot *xframe = x.frame(Title(Form(";M_{#mu#mu#pi} [GeV];Events/(%.1f MeV) ", binsize * 1000.)));
  B_mass.plotOn(xframe, Name("B_mass"));
  model->plotOn(xframe);
  // xframe2->addObject(xframe->pullHist());

  // Overlay the background component of model with a dashed line
  model->plotOn(xframe, Name("sig"), Components(dcbPdf), LineStyle(5), LineColor(kGreen + 2));
  // model->plotOn(xframe, Components(sig2), LineStyle(kSolid), LineColor(kMagenta));
  model->plotOn(xframe, Name("bkg"), Components(bkg), LineStyle(kDashed), LineColor(kBlue));
  model->plotOn(xframe, Name("model"), LineStyle(kSolid), LineColor(kRed));
  Double_t chi2 = xframe->chiSquare(10);

  cout << "Chi2/dof = " << chi2 << endl;

  // Overlay the background+sig2 components of model with a dotted line
  // model->plotOn(xframe, Components(RooArgSet(bkg, sig2)), LineStyle(kDotted));
  // h1_mass_all->Draw("SAME");
  xframe->Draw("SAME");
  TLegend *leg1 = new TLegend(0.15, 0.6, 0.3, 0.87);
  // leg1->SetFillColor(kWhite);
  // leg1->SetLineColor(kWhite);
  leg1->SetBorderSize(0);
  leg1->AddEntry("B_mass", "Data", "PE");
  leg1->AddEntry("model", "Fit model", "L");
  leg1->AddEntry("sig", "Signal", "L");
  leg1->AddEntry("bkg", "Comb bkg", "L");
  leg1->AddEntry((TObject *)0, Form("#chi^{2}/ndf = %.2f", chi2), "");
  leg1->Draw("SAME");
  xframe->SetMinimum(1);
  // xframe2->SetMinimum(-5) ;
  // xframe2->SetMaximum(+5) ;
  // xframe2->Draw() ;

  c->cd(2);
  xframe->Draw("SAME");
  leg1->Draw("SAME");
 TString plotextension = TString("../../plots/BjetsMC/");
  c->SaveAs(plotextension + extension + TString(".pdf"));

  f.Write();
  f.Close();
}
