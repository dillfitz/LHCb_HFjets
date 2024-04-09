#include "JpsiMCTree.C"
#include "JpsiTree.C"
#include <vector>
#include <iostream>
#include "Settings.h"
#include "../Helpers.h"
#include "../LundGen.hh"
// using namespace fastjet;
using namespace std;
// using namespace RooFit;

void TriggerEff(int NumEvts = 10000, int dataset = 1510,
                bool isData = false)
{

    int NumEvtsTruth = NumEvts;
    int NumEvtsReco = NumEvts;

    bool MCflag = !isData;
    followHardest = false;
    truthLevel = false;
    if (truthLevel)
    {
        ghostCut = false;
    }
    int year = (dataset / 10000) % 10;
    int JetMeth = (dataset / 1000) % 10;
    int flavor = (dataset / 100) % 10;
    int ptRange = (dataset / 10) % 10;
    int Mag = (dataset / 1) % 10;
    int HF_pdgcode = -99;

    int dataset_closure;
    if (Mag == 0)
        dataset_closure = dataset + 1;
    else if (Mag == 1)
        dataset_closure = dataset - 1;
    else
        dataset_closure = dataset;

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
    TString str_year = "2016";
    TString str_DTF = "";
    TString str_PID = "";
    TString str_charged = "";
    TString str_GS = "";

    if (year == 6)
        str_year = "2016";
    else if (year == 7)
        str_year = "2017";
    else if (year == 8)
        str_year = "2018";

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

    if (DTF_cut)
        str_DTF = "_DTF";
    if (PID_cut)
        str_PID = "_PID";

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

    // TString str_trees[5];
    // str_trees[0] = "TaggedDijets/DecayTree";
    // str_trees[1] = "D0KPiJet/DecayTree";
    // str_trees[2] = "B0KPiJet/DecayTree";
    // str_trees[3] = "Jets/DecayTree";
    TString str_tree;

    TString extension;
    extension = TString("trig_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + str_DTF + str_PID + str_GS + Form("_%d", dataset);

    JpsiTree RecoTree(0, dataset, 0);
    JpsiMCTree TruthTree(0, dataset, 0);

    TString dir_deadcone("$LUND/Bjets/");

    TFile f(dir_deadcone + "hists/" + extension + ".root", "RECREATE");

    TH1F *h1_TIS = new TH1F("h1_TIS", "", ptJpsibinsize, ptJpsi_binedges);
    TH1F *h1_TISTOS = new TH1F("h1_TISTOS", "", ptJpsibinsize, ptJpsi_binedges);

    TH2F *h2_denom_ptrap = new TH2F("h2_denom_ptrap", "", ptJpsibinsize, ptJpsi_binedges, HFetabinsize, HFeta_binedges);
    TH2F *h2_num_ptrap = new TH2F("h2_num_ptrap", "", ptJpsibinsize, ptJpsi_binedges, HFetabinsize, HFeta_binedges);
    TH2F *h2_numTOS_ptrap = new TH2F("h2_numTOS_ptrap", "", ptJpsibinsize, ptJpsi_binedges, HFetabinsize, HFeta_binedges);

    cout << "Total number of events = " << RecoTree.fChain->GetEntries() << endl;
    if (NumEvtsReco == -1)
        NumEvtsReco = RecoTree.fChain->GetEntries();
    for (int ev = 0; ev < NumEvtsReco; ev++)
    {
        RecoTree.GetEntry(ev);
        if (ev % 100000 == 0)
            cout << "Executing event " << ev << endl;
        TLorentzVector Jpsi(RecoTree.J_psi_1S_PX / 1000.,
                            RecoTree.J_psi_1S_PY / 1000.,
                            RecoTree.J_psi_1S_PZ / 1000.,
                            RecoTree.J_psi_1S_PE / 1000.);
        h2_num_ptrap->Fill(Jpsi.Pt(), Jpsi.Rapidity());

        bool jpsi_L0 = RecoTree.J_psi_1S_L0MuonDecision_TOS || RecoTree.J_psi_1S_L0DiMuonDecision_TOS;
        bool jpsi_Hlt1 = RecoTree.J_psi_1S_Hlt1DiMuonHighMassDecision_TOS;
        bool jpsi_Hlt2 = RecoTree.J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS;
        bool TOS = jpsi_L0 && jpsi_Hlt1 && jpsi_Hlt2;

        if (TOS)
            h2_numTOS_ptrap->Fill(Jpsi.Pt(), Jpsi.Rapidity());
    }

    cout << "Total number of events = " << TruthTree.fChain->GetEntries() << endl;

    if (NumEvtsTruth == -1)
        NumEvtsTruth = TruthTree.fChain->GetEntries();

    // for (int ev = 0; ev < NumEvtsTruth; ev++)
    // {
    //     TruthTree.GetEntry(ev);
    //     if (ev % 10000 == 0)
    //         cout << "Executing event " << ev << endl;
    //     TLorentzVector Jpsi(TruthTree.J_psi_1S_TRUEP_X / 1000.,
    //                         TruthTree.J_psi_1S_TRUEP_Y / 1000.,
    //                         TruthTree.J_psi_1S_TRUEP_Z / 1000.,
    //                         TruthTree.J_psi_1S_TRUEP_E / 1000.);
    //     h2_denom_ptrap->Fill(Jpsi.Pt(), Jpsi.Rapidity());
    //     // cout << Jpsi.Pt() << ", " << Jpsi.Rapidity() << " --  ";
    // }
    TH1F *h1_trig_eff = (TH1F *)h1_TISTOS->Clone("h1_trig_eff");
    h1_trig_eff->Divide(h1_trig_eff, h1_TIS, 1, 1, "B");

    cout << h2_denom_ptrap->Integral() << ", " << h2_num_ptrap->Integral() << endl;

    // TH2F *h2_efficiency_Jpsiptrap = (TH2F *)h2_num_ptrap->Clone("h2_trig_eff");
    // h2_efficiency_Jpsiptrap->Divide(h2_efficiency_Jpsiptrap, h2_denom_ptrap, 1, 1, "B");

    TH2F *h2_efficiency_Jpsiptrap = (TH2F *)h2_numTOS_ptrap->Clone("h2_trig_eff");
    h2_efficiency_Jpsiptrap->Divide(h2_efficiency_Jpsiptrap, h2_num_ptrap, 1, 1, "B");

    // gROOT->ProcessLine(".L $LUND/lhcbStyle.C");
    // gROOT->ProcessLine(".x $LUND/lhcbStyle.C");
    // gROOT->ProcessLine(".x lhcbStyle2D.C");
    //---- paint setup...
    //
    int ican = -1, iframe = -1, itext = -1;
    TCanvas *ccan[1000];
    TH1F *frame[1000];
    TLatex *text[1000];
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
    Int_t lhcbFont = 132; // Old LHCb style: 62;
    // Line thickness
    Double_t lhcbWidth = 2.00; // Old LHCb style: 3.00;
    // Text size
    Double_t lhcbTSize = 0.06;

    // gROOT->SetStyle("Plain");
    // gStyle->SetCanvasDefH(1414);
    // gStyle->SetCanvasDefW(1000);
    gStyle->SetOptStat(0);
    // gStyle->SetPaperSize(TStyle::kUSLetter);
    gStyle->SetPadBottomMargin(0.2);
    // gStyle->SetPadTopMargin(0.005);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetLabelSize(0.05, "X");
    gStyle->SetLabelSize(0.05, "Y");
    gStyle->SetTitleXSize(0.055);
    gStyle->SetTitleYSize(0.055);
    gStyle->SetTitleOffset(0.55, "X");
    gStyle->SetTitleOffset(1., "Y");
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
    rootfile = TString(dir_deadcone + "hists/") + extension + TString(".root");
    plotfile = TString(dir_deadcone + "plots/") + extension + TString(".ps");
    plotfilePDF = TString(dir_deadcone + "plots/") + extension + TString(".pdf");
    plotfileO = plotfilePDF + TString("(");
    plotfileC = plotfilePDF + TString("]");
    // c->SaveAs("plots/"+extension+".pdf");

    // c1->SaveAs(Form("plots_misc/Misc_%s"+extension+".pdf", file_name.c_str()));
    // cout<<"...outbase   = "<<outbase.Data()<<endl;
    // cout<<"...rootfile  = "<<rootfile.Data()<<endl;
    // cout<<"...plotfile  = "<<plotfile.Data()<<endl;

    // //
    //
    ++ican;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 1);
    ccan[ican]->SetFillColor(10);
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0.06);
    gPad->SetRightMargin(0.15);
    ccan[ican]->cd();
    ccan[ican]->Divide(2, 2);

    ccan[ican]->cd(1);
    SetTruthStyle(h1_trig_eff);
    h1_trig_eff->Draw("P E SAME");
    h1_trig_eff->SetMinimum(0.);
    h1_trig_eff->SetMaximum(1.2);

    ccan[ican]->cd(2);
    for (int i = 0; i < HFetabinsize; i++)
    {
        // ccan[ican]->cd(i + 1);

        TH1D *h1_temp = (TH1D *)h2_efficiency_Jpsiptrap->ProjectionX(Form("htempeff%d_jpsiptrap", i), i + 1, i + 1);
        h1_temp->SetMarkerStyle(i + 20);
        h1_temp->SetMarkerColor(i + 1);
        h1_temp->SetMarkerSize(0.6);
        h1_temp->SetLineColor(i + 1);
        h1_temp->Draw("PE1SAME");
        h1_temp->SetMaximum(1.05);
        h1_temp->SetMinimum(0.);
        h1_temp->SetTitle("; p_{T}^{HF} [GeV]; Efficiency");
        h1_temp->SetTitleOffset(1.2);
        h1_temp->GetXaxis()->CenterTitle(false);

        // legendptmass->AddEntry(h1_temp, Form("%.1f < #eta < %.1f GeV", HFeta_binedges[i], HFeta_binedges[i + 1]));
    }

    ccan[ican]->cd();
    ccan[ican]->Update();
    if (ican == 0)
    {
        ccan[ican]->Print(plotfileO.Data());
    }
    else
    {
        ccan[ican]->Print(plotfilePDF.Data());
    }

    if (ican > -1)
    {
        cout << " You plotted " << ican + 1 << " canvasses......." << endl;
        ccan[ican]->Print(plotfileC.Data());
    }

    f.Write();
    f.Close();
}