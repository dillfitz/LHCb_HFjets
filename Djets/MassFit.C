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
#include "Settings.h"
#include "../Helpers.h"

using namespace RooFit;

void MassFit(int NumEvts = 10000,
             int dataset = 1510,
             bool isData = true,
             bool WTA_cut = false,
             bool IPCut = true,
             bool DoRecSelEff = 0,
             bool DoSystematic = 0,
             float ptmin_user = pTLow,
             float ptmax_user = 250)
{
    bool MCflag = !isData;
    followHardest = false;
    truthLevel = false;
    chargedJetCut = false;
    ptMin = ptmin_user;
    ptMax = ptmax_user;
    if (truthLevel)
    {
        ghostCut = false;
    }
    int year = (dataset / 10000) % 10;
    int ptrange = (dataset / 1000) % 10;
    int flavor = (dataset / 100) % 10;
    int prompt_int = (dataset / 10) % 10;
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
    TString str_DTF = "";
    TString str_PID = "";
    TString str_year = "";
    TString str_WTA = "";
    TString str_IPCut = "";
    if (year == 6)
        str_year = "2016";
    else if (year == 7)
        str_year = "2017";
    else if (year == 8)
        str_year = "2018";
    if (DTF_cut)
        str_DTF = "_DTF";
    if (PID_cut)
        str_PID = "_PID";

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

    str_WTA = WTA_cut ? "_WTA" : "";
    str_IPCut = IPCut ? "" : "_noip";

    TString extension, extension_reco, extension_misid;
    TString extension_read, extension_RootFiles, extension_RootFilesMC;

    extension_RootFiles = isData ? TString("../../root_files/Djets/") : TString("../../root_files/DjetsMC/");
    extension_RootFilesMC = TString("../../root_files/DjetsMC/");

    extension_reco = TString("massfit_") + "reco" + Form("_ev_%d", -1) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_ghost + str_charged + str_Mag + str_flavor + str_WTA + Form("_%d", dataset);
    extension_misid = TString("massfit_") + "reco" + Form("_ev_%d", -1) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_ghost + str_charged + str_flavor + Form("_%d", 90499);

    extension = TString("massfit_") + str_level + Form("_ev_%d", NumEvts) + Form("_ptj_%d%d", int(ptMin), int(ptMax)) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_ghost + str_charged + str_Mag + str_flavor + str_WTA + str_IPCut + Form("_%d", dataset);

    if (DoRecSelEff)
    {
        extension = "recselsys_" + extension;
        extension_reco = "recselsys_" + extension_reco;
    }
    if (DoSystematic)
    {
        extension = "sys_" + extension;
        // extension_reco = "recselsys_" + extension_reco;
    }
    cout << extension << endl;
    cout << extension_reco << endl;
    // Setup Tree
    // TString dir_deadcone("$LUND/D2KKPi/");
    // extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);

    // TFile fread(dir_deadcone + "hists/" + extension_read + ".root", "READ");

    TChain *DTree = new TChain("DTree", "");
    vector<int> vec_datasets;
    int Mags[2] = {0, 1};
    int years[3] = {6, 7, 8};
    int prompts[2] = {0, 1};
    int ptranges[6] = {1, 2, 3, 4, 5, 6};
    if (isData)
        vec_datasets = {60490, 60491};
    // vec_datasets = {99499};
    else
        vec_datasets = {61400, 61401, 62400, 62401, 63400, 63401, 64400, 64401, 65400, 65401};
    // else
    // {

    //     for (int i = 0; i < 2; i++)
    //     {
    //         if (Mag == 0 && Mags[i] != 0)
    //             continue;
    //         if (Mag == 1 && Mags[i] != 1)
    //             continue;

    //         for (int j = 0; j < 2; j++)
    //         {
    //             if (prompt_int == 0 && prompts[j] != 0)
    //                 continue;
    //             if (prompt_int == 1 && prompts[j] != 1)
    //                 continue;
    //             for (int k = 0; k < 6; k++)
    //             {
    //                 if (ptranges[k] == 1 || ptranges[k] == 5)
    //                     continue;

    //                 if (ptrange == 1 && ptranges[k] != 1)
    //                     continue;
    //                 if (ptrange == 2 && ptranges[k] != 2)
    //                     continue;
    //                 if (ptrange == 3 && ptranges[k] != 3)
    //                     continue;
    //                 if (ptrange == 4 && ptranges[k] != 4)
    //                     continue;
    //                 if (ptrange == 5 && ptranges[k] != 5)
    //                     continue;
    //                 if (ptrange == 6 && ptranges[k] != 6)
    //                     continue;
    //                 for (int l = 0; l < 3; l++)
    //                 {
    //                     if (year == 6 && years[l] != 6)
    //                         continue;
    //                     if (year == 7 && years[l] != 7)
    //                         continue;
    //                     if (year == 8 && years[l] != 8)
    //                         continue;
    //                     int num = 10000 * years[l] + 1000 * ptranges[k] + 400 + 10 * prompts[j] + Mags[i];
    //                     cout << num << endl;
    //                     cout << years[l] << ", " << ptranges[k] << ", " << prompts[j] << ", " << Mags[i] << endl;
    //                     vec_datasets.push_back(num);
    //                 }
    //             }
    //         }
    //     }
    // }
    // if (year == 9 && JetMeth != 9)
    // {
    for (int i = 0; i < vec_datasets.size(); i++)
    {
        Mag = (vec_datasets[i] / 1) % 10;
        if (Mag == 0)
            str_Mag = "_MD";
        else if (Mag == 1)
            str_Mag = "_MU";
        extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", vec_datasets[i]);
        cout << extension_read << endl;
        DTree->Add(extension_RootFiles + extension_read + ".root/DTree");
    }
    // }
    // else
    // {
    //     extension_read = TString("tree_") + str_level + Form("_ev_%d", NumEvts) + Form("_eta_%.1f%.1f", etaMin, etaMax) + str_followHard + str_ghost + str_charged + str_Mag + str_flavor + Form("_%d", dataset);
    //     DTree->Add(dir_deadcone + "hists/" + extension_read + ".root/DTree");
    // }
    if (NumEvts > DTree->GetEntries())
        NumEvts = DTree->GetEntries();
    if (NumEvts == -1)
        NumEvts = DTree->GetEntries();
    cout << DTree->GetEntries() << endl;

    float K_px, K_py, K_pz, K_e;
    float pi0_px, pi0_py, pi0_pz, pi0_e;
    float pi_px, pi_py, pi_pz, pi_e, pi_PIDK, K_PIDK;
    float jet_pt, dtf_mass, chi2ndf_dtf, tau_dtf;
    float HF_px, HF_py, HF_pz, HF_e;
    float jet_px, jet_py, jet_pz, jet_e;
    float tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e;
    float Phi_CHI2NDOF, Phi_BPVDLS, Phi_CHI2, Phi_FDCHI2, Phi_IPCHI2;
    float D0_CHI2NDOF, D0_CHI2, D0_IPCHI2;
    float dphi;
    float jet_eta;
    float WTA_dist;
    double ptweight;
    bool isTrueDjet, TOS;
    int nSV;
    bool L0Dec, Hlt1Dec, Hlt2Dec;

    DTree->SetBranchAddress("jet_px", &jet_px);
    DTree->SetBranchAddress("jet_py", &jet_py);
    DTree->SetBranchAddress("jet_pz", &jet_pz);
    DTree->SetBranchAddress("jet_e", &jet_e);

    DTree->SetBranchAddress("HF_px", &HF_px);
    DTree->SetBranchAddress("HF_py", &HF_py);
    DTree->SetBranchAddress("HF_pz", &HF_pz);
    DTree->SetBranchAddress("HF_e", &HF_e);

    DTree->SetBranchAddress("tr_HF_px", &tr_HF_px);
    DTree->SetBranchAddress("tr_HF_py", &tr_HF_py);
    DTree->SetBranchAddress("tr_HF_pz", &tr_HF_pz);
    DTree->SetBranchAddress("tr_HF_e", &tr_HF_e);

    DTree->SetBranchAddress("D0_IPCHI2", &D0_IPCHI2);
    DTree->SetBranchAddress("D0_CHI2", &D0_CHI2);
    DTree->SetBranchAddress("D0_CHI2NDOF", &D0_CHI2NDOF);

    DTree->SetBranchAddress("Phi_FDCHI2", &Phi_FDCHI2);
    DTree->SetBranchAddress("Phi_CHI2", &Phi_CHI2);
    DTree->SetBranchAddress("Phi_CHI2NDOF", &Phi_CHI2NDOF);
    DTree->SetBranchAddress("Phi_BPVDLS", &Phi_BPVDLS);

    DTree->SetBranchAddress("K_px", &K_px);
    DTree->SetBranchAddress("K_py", &K_py);
    DTree->SetBranchAddress("K_pz", &K_pz);
    DTree->SetBranchAddress("K_e", &K_e);

    DTree->SetBranchAddress("pi_px", &pi_px);
    DTree->SetBranchAddress("pi_py", &pi_py);
    DTree->SetBranchAddress("pi_pz", &pi_pz);
    DTree->SetBranchAddress("pi_e", &pi_e);
    DTree->SetBranchAddress("pi_PIDK", &pi_PIDK);

    DTree->SetBranchAddress("pi0_px", &pi0_px);
    DTree->SetBranchAddress("pi0_py", &pi0_py);
    DTree->SetBranchAddress("pi0_pz", &pi0_pz);
    DTree->SetBranchAddress("pi0_e", &pi0_e);

    DTree->SetBranchAddress("jet_pt", &jet_pt);
    DTree->SetBranchAddress("jet_eta", &jet_eta);

    DTree->SetBranchAddress("dphi", &dphi);
    DTree->SetBranchAddress("nSV", &nSV);
    DTree->SetBranchAddress("dtf_mass", &dtf_mass);
    DTree->SetBranchAddress("chi2ndf_dtf", &chi2ndf_dtf);
    DTree->SetBranchAddress("tau_dtf", &tau_dtf);
    DTree->SetBranchAddress("isTrueDjet", &isTrueDjet);

    DTree->SetBranchAddress("TOS", &TOS);
    DTree->SetBranchAddress("WTA_dist", &WTA_dist);
    DTree->SetBranchAddress("ptweight", &ptweight);

    DTree->SetBranchAddress("L0Dec", &L0Dec);
    // DTree->SetBranchAddress("L0TIS", &L0TIS);

    DTree->SetBranchAddress("Hlt1Dec", &Hlt1Dec);
    DTree->SetBranchAddress("Hlt2Dec", &Hlt2Dec);

    float MassHF = 1.864;
    float SigmaHF = 0.75 * 1e-3;
    float mass_low = 1.864 - 3 * 0.06;
    float mass_high = 2.1;
    if (isData)
        mass_high = 1.99;
    vector<TH1D *> h1_mass_HFpt;
    vector<float> vec_bkg_frac, vec_res_frac, vec_bkg_yield, vec_sig_yield;
    vector<float> vec_Mass_D0_fit;

    TFile f(extension_RootFiles + extension + ".root", "RECREATE");

    int nBins = 80;
    float binsize;
    // int nBins[ptHFbinsize] = {100, 100, 100, 100, 100, 100};
    for (int i = 0; i < ptHFbinsize; i++)
    {
        if (!isData)
        {
            if (i >= ptHFbinsize - 5) // 2
            {
                nBins = 20;
            }
            else
            {
                nBins = 60;
            }
        }
        else
        {
            if (i <= 2) // 2
            {
                nBins = 40;
            }
            else if ((i > 2) && (i >= ptHFbinsize - 2)) // 2
            {
                nBins = 20;
            }
            else
            {
                nBins = 80;
            }
        }
        TH1D *h1_temp = new TH1D(Form("h1_mass%d", i), "", nBins, mass_low, mass_high);
        h1_mass_HFpt.push_back(h1_temp);
        binsize = (mass_high - mass_low) / (float)nBins;
    }

    TH1D *h1_mass = new TH1D("h1_mass", "", nBins, mass_low, mass_high);
    TH1D *h1_mass_all = new TH1D("h1_mass_all", "", nBins + 17, 4.8, mass_high);
    TH1D *h1_MassMin = new TH1D("h1_MassMin", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_MassMax = new TH1D("h1_MassMax", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband1Min = new TH1D("h1_Sideband1Min", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband1Max = new TH1D("h1_Sideband1Max", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband2Min = new TH1D("h1_Sideband2Min", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband2Max = new TH1D("h1_Sideband2Max", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband1Min_forSysNear = new TH1D("h1_Sideband1Min_forSysNear", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband1Max_forSysNear = new TH1D("h1_Sideband1Max_forSysNear", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband2Min_forSysNear = new TH1D("h1_Sideband2Min_forSysNear", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband2Max_forSysNear = new TH1D("h1_Sideband2Max_forSysNear", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband1Min_forSysFar = new TH1D("h1_Sideband1Min_forSysFar", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband1Max_forSysFar = new TH1D("h1_Sideband1Max_forSysFar", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband2Min_forSysFar = new TH1D("h1_Sideband2Min_forSysFar", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_Sideband2Max_forSysFar = new TH1D("h1_Sideband2Max_forSysFar", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_BkgScale = new TH1D("h1_BkgScale", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_BkgScale_forSysNear = new TH1D("h1_BkgScale_forSysNear", "", ptHFbinsize, ptHF_binedges);
    TH1D *h1_BkgScale_forSysFar = new TH1D("h1_BkgScale_forSysFar", "", ptHFbinsize, ptHF_binedges);

    if (isData)
        NumEvts = 5000000;
    for (int ev = 0; ev < NumEvts; ev++)
    {
        DTree->GetEntry(ev);

        // if (ptweight == ptweights[1])
        //     ptweight = ptweights[1] * signal_eff[1];
        // if (ptweight == ptweights[2])
        //     ptweight = ptweights[2] * signal_eff[2];
        // if (ptweight == ptweights[3])
        //     ptweight = ptweights[3] * signal_eff[3];
        // if (ptweight == ptweights[4])
        //     ptweight = ptweights[4] * signal_eff[4];
        // if (ptweight == ptweights[5])
        //     ptweight = ptweights[5] * signal_eff[5];
        // if (ptweight == ptweights[6])
        //     ptweight = ptweights[6] * signal_eff[6];

        // ptweight /= (ptweights[2] * signal_eff[2]);

        // if (isData)
        ptweight = 1.0;

        if (ev % 100000 == 0)
            cout << "Executing event " << ev << endl;

        TLorentzVector HFmeson, HFjet, pi, K, pi0, tr_HFmeson;
        K.SetPxPyPzE(K_px, K_py, K_pz, K_e);
        pi.SetPxPyPzE(pi_px, pi_py, pi_pz, pi_e);
        // HFmeson = Kp + Km + pi;
        HFmeson.SetPxPyPzE(HF_px, HF_py, HF_pz, HF_e);
        tr_HFmeson.SetPxPyPzE(tr_HF_px, tr_HF_py, tr_HF_pz, tr_HF_e);
        HFjet.SetPxPyPzE(jet_px, jet_py, jet_pz, jet_e);
        pi0.SetPxPyPzE(pi0_px, pi0_py, pi0_pz, pi0_e);

        // if (HFjet.Rapidity() < etaMin || HFjet.Rapidity() > etaMax)
        //     continue;
        if (jet_pt > ptMax)
            continue;
        if (jet_pt < ptMin)
            continue;
        if (!L0Dec && isData)
            continue;
        if (!Hlt1Dec && isData)
            continue;
        // if (WTA_cut && (WTA_dist > WTA_max))
        //     continue;

        // if (K_PIDK < 7 || pi_PIDK > 0)
        //     continue;
        // if (K.Pt() < 1.7 || pi.Pt() < 1.7)
        //     continue;
        // if (fabs(pi0.M() - 0.135) > 0.015)
        //     continue;

        // if (IPCut)
        if (isData && log10(D0_IPCHI2) > ipmax)
            continue;
        if (DoRecSelEff)
        {
            // cout << D0_IPCHI2 << ", " << D0_CHI2 << ", " << Phi_CHI2 << ", " << Phi_CHI2NDOF << ", " << sqrt(Phi_FDCHI2) << endl;
            // if (D0_IPCHI2 > 22)
            //     continue;
            // if (D0_CHI2 > 42)
            //     continue;
            // if (Phi_CHI2 > 22)
            //     continue;
            // if (Phi_CHI2NDOF > 18)
            //     continue;
            // if (fabs(Phi_BPVDLS) < 2.8)
            //     continue;
        }

        // if(dtf_chi2ndf > 5) continue;
        // cout<<dtf_mass<<endl;
        // float hfmass = HFmeson.M();
        float hfmass = dtf_mass;
        if (!isData)
        {
            // cout << HFmeson.Pt() << ", " << tr_HFmeson.Pt() << endl;
            // if (fabs(HFmeson.Pt() - tr_HFmeson.Pt()) / tr_HFmeson.Pt() > 0.05)
            //     continue;
            // cout << tr_HFmeson.M() << endl;
            // cout << isTrueDjet << ",";
            if (!isTrueDjet)
                continue;
        }
        // h1_mass->Fill(HFmeson.M());
        // h1_mass_all->Fill(HFmeson.M());
        h1_mass->Fill(hfmass, ptweight);
        h1_mass_all->Fill(hfmass, ptweight);

        for (int i = 0; i < ptHFbinsize; i++)
        {
            if (HFmeson.Pt() > ptHF_binedges[i] && HFmeson.Pt() < ptHF_binedges[i + 1])
            {
                h1_mass_HFpt[i]->Fill(hfmass, ptweight);
                break;
            }
        }
    }

    //---- paint setup...
    //
    int ican = -1, iframe = -1, itext = -1;
    TCanvas *ccan[1000];
    TH1F *frame[1000];
    TLatex *text[1000];
    TRatioPlot *rp[1000];
    for (int i = 0; i < 1000; i++)
    {
        text[i] = new TLatex();
        text[i]->SetNDC(kTRUE);
        text[i]->SetTextSize(0.06);
    }
    TLatex Tl;
    Tl.SetNDC(kTRUE);
    Tl.SetTextSize(0.03);
    //
    gStyle->SetCanvasDefH(2000);
    gStyle->SetCanvasDefW(3508);
    //
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
    gStyle->SetTitleOffset(1.5, "Y");
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
    TString plotextension = isData ? TString("../../plots/Djets/") : TString("../../plots/DjetsMC/");
    rootfile = extension_RootFiles + extension + TString(".root");
    plotfile = plotextension + extension + TString(".ps");

    plotfilePDF = plotextension + extension + TString(".pdf");
    plotfileO = plotfilePDF + TString("(");
    plotfileC = plotfilePDF + TString("]");

    // Plot data and PDF overlaid
    ican = 0;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 2100, 1800);
    ccan[ican]->SetFillColor(10);

    // gPad->SetBottomMargin(0.06);
    ccan[ican]->cd();
    ccan[ican]->Divide(3, 5, 0.0001, 0.0001);

    ican = 1;
    sprintf(buf, "ccan%d", ican);
    ccan[ican] = new TCanvas(buf, buf, 2100, 1800);
    ccan[ican]->SetFillColor(10);

    // gPad->SetBottomMargin(0.06);
    ccan[ican]->cd();
    ccan[ican]->Divide(3, 5, 0.0001, 0.0001);
    // c->SaveAs("plots/"+extension+".pdf");
    // h1_mass->Scale(1./h1_mass->GetEntries());

    std::ofstream SigParams("csv/signal_" + extension + ".csv");
    std::ofstream BkgParams("csv/bkg_" + extension + ".csv");
    // std::ofstream ResonantParams("csv/res_" + extension + ".csv");
    if (DoSystematic)
    {
        SigParams << "m,t,n,nsig,fraction" << endl;
    }
    else
        SigParams << "mu,sigma1,sigma2,alpha1,n1,n1_2,alpha2,n2,n2_2,nsig" << endl;

    BkgParams << "a0,a1,a2,nbkg,fraction" << endl;

    // S e t u p   c o m p o n e n t   p d f s
    // ---------------------------------------

    // Declare observable x
    for (int i = 0; i < ptHFbinsize; i++)
    {
        if (!isData)
        {
        }

        if (i >= ptHFbinsize - 2)
        {
            nBins = 60;
        }
        else
        {
            nBins = 80;
        }

        binsize = (mass_high - mass_low) / (float)nBins;

        TFile *file_workspace = new TFile(extension_RootFilesMC + Form("workspace%d_", i) + extension_reco + ".root", "READ");

        TFile *file_workspace_misid = new TFile(extension_RootFilesMC + TString("MisID/") + Form("workspace%d_", i) + extension_misid + TString(".root"), "READ");

        std::cout << extension_RootFilesMC << Form("workspace%d_", i) << extension_reco << ".root" << std::endl;
        std::cout << extension_RootFilesMC << TString("MisID/") << extension_misid << TString(".root");

        if (file_workspace_misid == NULL)
        {
            cout << "no file at " << extension_misid << endl;
        }
        RooWorkspace *w_read = (RooWorkspace *)file_workspace->Get(Form("w%d", i));
        RooWorkspace *w_read_misid = (RooWorkspace *)file_workspace_misid->Get(Form("w%d", i));
        RooRealVar *sigma_ratio, *mean, *sigma1, *sigma2, *sigma_gauss;
        RooRealVar *mu_sig, *alpha1_sig, *alpha2_sig, *p1_sig, *p2_sig;
        RooRealVar *mu_sig2, *alpha1_sig2, *alpha2_sig2, *p1_sig2, *p2_sig2;
        RooRealVar *mu, *width, *alpha1, *alpha2, *p1, *p2;

        RooRealVar HFMass("HFMass", "HFMass", mass_low, mass_high);
        RooDataHist B_mass("B_mass", "B_mass", RooArgList(HFMass), h1_mass_HFpt[i], 1.);

        HFMass.setBins(nBins);

        // Create two Gaussian PDFs g1(HFMass,mean1,sigma) anf g2(HFMass,mean2,sigma) and their parameters
        ////////////////////////////////////////////////////
        // build siganl
        ///////////////////////////////////////////////////

        sigma_ratio = new RooRealVar("sigma_ratio", "sigma_ratio", 1.52571 / 0.856549);
        mean = new RooRealVar("mean", "mean of gaussians", MassHF, 1.8, 1.9);
        sigma1 = new RooRealVar("sigma1", "width of gaussians", 0.0374032, 0.008, 0.05);
        sigma2 = new RooRealVar("sigma2", "width of gaussians", 0.01, 0.008, 0.05); // CHANGE
        sigma_gauss = new RooRealVar("sigma_gauss", "width of gaussians", 0.0091, 0.008, 0.1);
        // RooFormulaVar sigma2("sigma2", "width of gaussians", "sigma1*sigma_ratio", RooArgList(sigma1,sigma_ratio)); //CHANGE
        // if(isData){
        //   sigma2.setVal(0.01);
        //   // sigma2.setConstant(kTRUE);
        // }
        RooGaussian gauss1("gauss_sig1", "Signal component 1", HFMass, *mean, *sigma1);
        RooGaussian gauss2("gauss_sig2", "Signal component 2", HFMass, *mean, *sigma2);

        mu_sig = new RooRealVar("mu_sig", "mu", MassHF, 1.8, 1.9);
        alpha1_sig = new RooRealVar("alpha1_sig", "alpha1", 2., 0.01, 10.);
        alpha2_sig = new RooRealVar("alpha2_sig", "alpha2", 2., 0.01, 10.);

        alpha1_sig2 = new RooRealVar("alpha1_sig2", "alpha1", 2., 0.01, 10.);
        alpha2_sig2 = new RooRealVar("alpha2_sig2", "alpha2", 2., 0.01, 10.);
        // p1_sig = RooRealVar("p1_sig", "p1", 1., 0.6, 4.);
        // p2_sig = RooRealVar("p2_sig", "p2", 1., 0.6, 4.);
        p1_sig = new RooRealVar("p1_sig", "p1", 2., 1., 6.);
        p2_sig = new RooRealVar("p2_sig", "p2", 3., 1., 6.);

        p1_sig2 = new RooRealVar("p1_sig2", "p1", 2., 1., 6.);
        p2_sig2 = new RooRealVar("p2_sig2", "p2", 3., 1., 6.);
        // p1_sig->setConstant(kTRUE);
        // p2_sig->setConstant(kTRUE);
        // p1_sig2->setConstant(kTRUE);
        // p2_sig2->setConstant(kTRUE);
        // Or, Create signal from two Crystal Ball functions
        // These parameters have been derived from simulation

        if (isData && w_read != NULL)
        {
            cout << "Fixing tail parameters!" << endl;
            mu_sig = (RooRealVar *)w_read->obj("mu_sig");
            alpha1_sig = (RooRealVar *)w_read->obj("alpha1_sig");
            alpha2_sig = (RooRealVar *)w_read->obj("alpha2_sig");
            p1_sig = (RooRealVar *)w_read->obj("p1_sig");
            p2_sig = (RooRealVar *)w_read->obj("p2_sig");
            sigma1 = (RooRealVar *)w_read->obj("sigma1");
            // sigma2 = (RooRealVar *)w_read->obj("sigma2");
            sigma_gauss = (RooRealVar *)w_read->obj("sigma_gauss");
            // p1_sig2 = (RooRealVar *)w_read->obj("p1_sig2");
            // p2_sig2 = (RooRealVar *)w_read->obj("p2_sig2");
            // mu_sig.setConstant(kTRUE);
            // sigma1->setConstant(kTRUE);
            sigma_gauss->setConstant(kTRUE);
            // sigma2->setConstant(kTRUE);
            alpha1_sig->setConstant(kTRUE);
            alpha2_sig->setConstant(kTRUE);
            p1_sig->setConstant(kTRUE);
            p2_sig->setConstant(kTRUE);
            // p1_sig2->setConstant(kTRUE);
            // p2_sig2->setConstant(kTRUE);
        }

        // Define the CB functions
        RooCrystalBall dcbPdf_sig1("dcbPdf_sig1", "floatSidedCB_sig1", HFMass, *mu_sig, *sigma1, *alpha1_sig, *p1_sig, *alpha2_sig, *p2_sig);
        // RooCrystalBall dcbPdf_sig2("dcbPdf_sig2", "floatSidedCB_sig2", HFMass, *mu_sig, *sigma2, *alpha1_sig, *p1_sig2, *alpha2_sig, *p2_sig2);
        RooCrystalBall dcbPdf_sig2("dcbPdf_sig2", "floatSidedCB_sig2", HFMass, *mu_sig, *sigma2, *alpha1_sig, *p1_sig, *alpha2_sig, *p2_sig);
        RooGaussian gauss_sig("gauss_sig", "Signal component 1", HFMass, *mu_sig, *sigma_gauss);

        // Number of signal events
        RooRealVar *nsig1 = new RooRealVar("nsig1", "fraction of component 1 in signal", 0.8, 0.5, 1.);
        // RooRealVar *nsig1 = new RooRealVar("nsig1", "fraction of component 1 in signal", 0., 0., 0.);

        // Choose if you want two CB functions as signal, or two Gaussians.

        // RooAddPdf sig("sig", "Signal", RooArgList(gauss1, gauss2), RooArgList(*nsig1));
        // RooAddPdf sig("sig", "Signal", RooArgList(dcbPdf_sig1, dcbPdf_sig2), RooArgList(*nsig1));
        RooAddPdf sig("sig", "Signal", RooArgList(dcbPdf_sig1, gauss_sig), RooArgList(*nsig1));

        RooRealVar *sig2_m = new RooRealVar("sig2_m", "sig2_m", MassHF, MassHF - SigmaHF, MassHF + SigmaHF);
        RooRealVar *sig2_n = new RooRealVar("sig2_n", "sig2_n", 5.);
        sig2_n->setConstant(kTRUE);
        RooRealVar *sig2_t = new RooRealVar("sig2_t", "sig2_t", 0.02, 0.001, 0.3);

        RooGenericPdf sig2("student-t", "", "tgamma((sig2_n+1)/2)/(tgamma(sig2_n/2)*sqrt(TMath::Pi()*sig2_n)*sig2_t) * pow(1+(1/sig2_n * pow((HFMass-sig2_m)/sig2_t, 2)), (-1-sig2_n)/2)", RooArgList(HFMass, *sig2_m, *sig2_n, *sig2_t));

        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Build linear background PDF, for combinatoric background
        ///////////////////////////////////////////////////

        // RooGenericPdf bkg("bkg", "Background", "a2*x +a1", RooArgSet(x, a2, a1));

        // RooRealVar * a0("c0","coefficient #0", 1.0,-1.,1.) ;

        // RooRealVar * a1("c1", "coefficient #1", -0.1, -1., -0.00001);
        // RooRealVar * a2("c2", "coefficient #2", -0.1, -1., -0.001);
        // RooChebychev bkg("bkg", "background p.d.f.", HFMass, RooArgList(a1, a2));

        RooRealVar *a2 = new RooRealVar("c2", "coefficient #2", -0.1, -1., -0.001);
        RooRealVar *a1 = new RooRealVar("exp_c", "exp_c", -2., -4, -0.1);
        RooExponential bkg("bkg", "bkg", HFMass, *a1);

        // Define the shape parameters
        RooRealVar *m0 = new RooRealVar("m0", "Threshold mass", 1.85, 1.8, 1.9, "GeV/c^2");
        RooRealVar *c = new RooRealVar("c", "Shape parameter", 10.0, 0.0, 50.0);
        RooRealVar *a = new RooRealVar("a", "Power parameter", 1.0, 0.0, 5.0);
        RooRealVar *b = new RooRealVar("b", "Power parameter", 1.0, 0.0, 5.0);

        // Create the PDF
        // RooDstD0BG bkg("bkg", "DstD0 Background PDF", HFMass, *m0, *c, *a, *b);

        //  RooRealVar * a2("a2", "a2", -1, -2, -0.1);
        // RooRealVar * a1("a1", "a1", 2, 0., 9.);
        // RooPolynomial bkg("bkg", "Background", HFMass, RooArgList(a1, a2));

        RooRealVar *a0_cheb = new RooRealVar("a0_cheb", "a0_cheb", -0.5, -5, 1);
        RooRealVar *a1_cheb = new RooRealVar("a1_cheb", "a1_cheb", -0.2, -10, -0.001);
        RooRealVar *a2_cheb = new RooRealVar("a2_cheb", "a2_cheb", -0.2, -10, -0.001);
        // RooChebychev bkg_cheb("bkg_cheb", "Background_cheb", HFMass, RooArgSet(*a0_cheb, *a1_cheb, *a2_cheb));
        // RooChebychev bkg_cheb("bkg_cheb", "Background_cheb", HFMass, RooArgSet(*a0_cheb, *a1_cheb));
        RooChebychev bkg_cheb("bkg_cheb", "Background_cheb", HFMass, RooArgSet(*a0_cheb));
        // RooRealVar *dst_m0 = new RooRealVar("m0", "Threshold Mass", MassHF - 0.8); // Approximate mass of D0 in GeV/c^2
        // RooRealVar *dst_c = new RooRealVar("dst_c", "Shape Parameter c", 0.01, 0.001, 0.1);
        // RooRealVar *dst_a = new RooRealVar("dst_a", "Shape Parameter a", 1.0, 1.0, 10.0);
        // RooRealVar *dst_b = new RooRealVar("dst_b", "Shape Parameter b", 0.0, -0.5, 0.5);
        // RooDstD0BG bkg_Dst("bkg_dstd0bg", "bkg_dstd0bg", HFMass, *dst_m0, *dst_a, *dst_b, *dst_c);
        // dst_m0->setConstant(kTRUE);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Fractions
        ///////////////////////////////////////////////////

        // RooRealVar nsig2("nsig2", "fraction of component 2 in signal", 0.6, 0., 1.);
        RooRealVar *nsig = new RooRealVar("nsig", "fraction in signal", 10000, 0., 10000000.);
        // RooRealVar nsig2("nsig2", "fraction of component 2 in signal", 0.6, 0., 1.);
        RooRealVar *nbkg = new RooRealVar("nbkg", "fraction of background", 500, 0., 100000);
        // S a m p l e ,   f i t   a n d   p l o t   m o d e l
        // ---------------------------------------------------
        HFMass.setRange("comb1", 2, 2.1);
        HFMass.setRange("comb2", RooConst(mass_low), RooConst(mass_low + 0.1));
        HFMass.setRange("Full", mass_low, mass_high);

        // Fit model to data
        //  bkg.fitTo(B_mass, Range("comb1"));
        //  a1.setConstant(kTRUE);
        //  a2.setConstant(kTRUE);
        // tanhpdf.fitTo(B_mass, Range("tanh"));
        // res_comp1.fitTo(B_mass, Range("reso1"));
        // res_comp2.fitTo(B_mass, Range("reso2"));
        RooAddPdf *model;
        // if(isData) model =new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, sig, tanhpdf), RooArgList(bkgfrac,tanhfrac));
        if (isData)
        {
            if (DoSystematic)
            {
                model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg_cheb, sig2), RooArgList(*nbkg, *nsig));
            }
            else
            {
                // model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg_cheb, sig), RooArgList(*nbkg, *nsig));
                model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, sig), RooArgList(*nbkg, *nsig));

                // model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg_Dst, sig), RooArgList(*nbkg, *nsig));
            }
        }
        //  else model = new RooAddPdf("model", "g1+g2+a", RooArgList(bkg, sig), RooArgList(nbkg, nsig));
        else
        {
            model = new RooAddPdf("model", "g1+g2+a", RooArgList(sig), RooArgList(*nsig));
            // model = new RooAddPdf("model", "g1+g2+a", RooArgList(sig2), RooArgList(*nsig));
        }

        RooFitResult *fitresult = model->fitTo(B_mass, PrintEvalErrors(-1), Save(true));
        // RooMsgService::instance().setSilentMode(true);
        // RooStats::SPlot *sData = new RooStats::SPlot("sData", "An SPlot",
        //                                              B_mass, model, RooArgList(nsig, nbkg, nres));

        // Begin plotting
        //
        ican = 0;
        ccan[ican]->cd(i + 1);
        gPad->SetRightMargin(0.12);
        gPad->SetLeftMargin(0.12);
        ccan[ican]->SetFillStyle(4070);
        RooPlot *xframe = HFMass.frame(Title(Form(";M_{D^{0}} [GeV];Events/(%.1f MeV) ", binsize * 1000.)));
        xframe->SetTitleOffset(0.9, "Y");
        xframe->SetTitleOffset(0.9, "X");
        // model->paramOn(xframe, Layout(0.6, 0.9, 0.9));
        // xframe->getAttText()->SetTextSize(0.02);
        B_mass.plotOn(xframe, Name("B_mass"));
        // model->plotOn(xframe);

        // Overlay the background component of model with a dashed line
        model->plotOn(xframe, Name("sig"), Components(sig), LineStyle(5), LineColor(kGreen + 2), LineWidth(1.));
        // sig.plotOn(xframe, Name("sig"), LineStyle(kSolid), LineColor(kGreen), Range("Full"));
        // model->plotOn(xframe, Components(sig2), LineStyle(kSolid), LineColor(kMagenta));
        model->plotOn(xframe, Name("bkg"), Components(bkg), LineStyle(kDashed), LineColor(kBlue), LineWidth(1.));
        model->plotOn(xframe, Name("bkg_cheb"), Components(bkg_cheb), LineStyle(kDashed), LineColor(kBlue), LineWidth(1.));
        // model->plotOn(xframe, Name("bkg_Dst"), Components(bkg_Dst), LineStyle(kDashed), LineColor(kBlue), LineWidth(1.));

        // model->plotOn(xframe, Name("exp_bkg"), Components(exp_bkg), LineStyle(kDashed), LineColor(kBlue));
        model->plotOn(xframe, Name("model"), LineStyle(kSolid), LineColor(kRed), LineWidth(1.));
        RooHist *hpull = xframe->pullHist();
        xframe->SetMaximum(30000);
        float chi2;
        if (isData)
            chi2 = xframe->chiSquare(10);
        else
            chi2 = xframe->chiSquare(10);

        // exp_bkg.plotOn(xframe, LineColor(kMagenta));

        // Overlay the background+sig2 components of model with a dotted line
        // model->plotOn(xframe, Components(RooArgSet(bkg, sig2)), LineStyle(kDotted));
        // h1_mass_all->Draw("SAME");
        xframe->Draw("SAME");
        gPad->SetLogy();
        xframe->SetMinimum(1.);

        TLegend *leg1 = new TLegend(0.14, 0.45, 0.24, 0.87);
        leg1->SetTextSize(0.07);
        // leg1->SetFillColor(kWhite);
        // leg1->SetLineColor(kWhite);
        leg1->SetBorderSize(0);
        leg1->AddEntry("B_mass", "Data", "PE");
        leg1->AddEntry("model", "Fit model", "L");
        leg1->AddEntry("sig", "Signal", "L");
        leg1->AddEntry("bkg", "Comb bkg", "L");
        // leg1->AddEntry((TObject*)0, "", "");
        leg1->AddEntry((TObject *)0, Form("#chi^{2}/ndf = %.2f", chi2), "");
        leg1->AddEntry((TObject *)0, Form("%.1f < p_{T}^{HF} < %.1f GeV", ptHF_binedges[i], ptHF_binedges[i + 1]), "");

        leg1->Draw("SAME");
        // xframe->SetT
        // xframe2->SetMaximum(+5) ;
        // xframe2->Draw() ;

        ican = 1;
        ccan[ican]->cd(i + 1);
        gPad->SetRightMargin(0.12);
        gPad->SetLeftMargin(0.12);
        ccan[ican]->SetFillStyle(4070);
        RooPlot *xframe2 = HFMass.frame(Title(Form(";M_{D^{0}} [GeV];Events/(%.1f MeV) ", binsize * 1000.)));
        xframe2->SetTitleOffset(0.7, "Y");
        xframe2->SetTitleOffset(0.9, "X");
        B_mass.plotOn(xframe2, Name("B_mass"));
        // model->plotOn(xframe2);

        // Overlay the background component of model with a dashed line
        model->plotOn(xframe2, Name("sig"), Components(sig), LineStyle(5), LineColor(kGreen + 2), LineWidth(1.));
        // sig.plotOn(xframe2, Name("sig"), LineStyle(kSolid), LineColor(kGreen), Range("Full"));
        // model->plotOn(xframe2, Components(sig2), LineStyle(kSolid), LineColor(kMagenta));
        model->plotOn(xframe2, Name("bkg"), Components(bkg), LineStyle(kDashed), LineColor(kBlue), LineWidth(1.));
        model->plotOn(xframe2, Name("bkg_cheb"), Components(bkg_cheb), LineStyle(kDashed), LineColor(kBlue), LineWidth(1.));
        // model->plotOn(xframe2, Name("exp_bkg"), Components(exp_bkg), LineStyle(kDashed), LineColor(kBlue));
        model->plotOn(xframe2, Name("model"), LineStyle(kSolid), LineColor(kRed), LineWidth(1.));

        // exp_bkg.plotOn(xframe2, LineColor(kMagenta));

        // Overlay the background+sig2 components of model with a dotted line
        // model->plotOn(xframe2, Components(RooArgSet(bkg, sig2)), LineStyle(kDotted));
        // h1_mass_all->Draw("SAME");
        xframe2->Draw("SAME");
        // gPad->SetLogy();
        xframe2->SetMinimum(0.);
        leg1->Draw("SAME");

        RooWorkspace *w = new RooWorkspace(Form("w%d", i), Form("workspace%d", i));
        // w->import(sign);
        // w->import(bkgn);
        w->import(*model);
        w->import(B_mass);
        w->Print();
        w->writeToFile(Form(extension_RootFiles + "workspace%d_", i) + extension + ".root");

        cout << "Chi2/dof = " << chi2 << endl;
        // cout << sigma_arg->getVal() << endl;
        cout << "a1 = " << a1->getVal() << endl;
        cout << "a2 = " << a2->getVal() << endl;
        cout << "sigma1 = " << sigma1->getVal() << endl;
        cout << "sigma2 = " << sigma2->getVal() << endl;

        float MassMu;

        float MassSigma;
        // cout << "Nsig1 = " << nsig1->getVal() << endl;
        if (DoSystematic)
        {
            MassMu = sig2_m->getVal();
            MassSigma = sig2_t->getVal();
            cout << "MassMu = " << sig2_m->getVal() << endl;
            cout << "MassSigma = " << sig2_t->getVal() << endl;
        }
        else
        {
            MassMu = mu_sig->getVal();
            if (nsig1->getVal() > 0.5)
                MassSigma = sigma1->getVal();
            else
                MassSigma = sigma2->getVal();

            cout << MassSigma << ", " << sigma1->getVal() << ", " << sigma2->getVal() << endl;
        }

        float MassUp = MassMu + 2. * MassSigma;
        float MassDown = MassMu - 2. * MassSigma;
        Sideband1_Min = MassMu - 9 * MassSigma;
        Sideband1_Max = MassMu - 5 * MassSigma;
        Sideband2_Min = MassMu + 5 * MassSigma;
        Sideband2_Max = MassMu + 9 * MassSigma;

        // if (Sideband1_Min < 1.921)
        // {
        //     Sideband1_Min = 1.921;
        //     Sideband1_Max = 1.93;
        // }
        // if (Sideband2_Max > 2.039)
        // {
        //     Sideband2_Min = 2.02;
        //     Sideband2_Max = 2.039;
        // }

        float Sideband1_Min_forSysNear = Sideband1_Min + MassSigma;
        float Sideband1_Max_forSysNear = Sideband1_Max;
        float Sideband2_Min_forSysNear = Sideband2_Min;
        float Sideband2_Max_forSysNear = Sideband2_Max - MassSigma;

        float Sideband1_Min_forSysFar = Sideband1_Min;
        float Sideband1_Max_forSysFar = Sideband1_Max - MassSigma;
        float Sideband2_Min_forSysFar = Sideband2_Min + MassSigma;
        float Sideband2_Max_forSysFar = Sideband2_Max;

        cout << MassDown << ", " << MassUp << endl;
        cout << "Sideband1: " << Sideband1_Min << ", " << Sideband1_Max << endl;
        cout << "Sideband2: " << Sideband2_Min << ", " << Sideband2_Max << endl;
        HFMass.setRange("signal", MassDown, MassUp);
        HFMass.setRange("sideband1", Sideband1_Min, Sideband1_Max);
        HFMass.setRange("sideband2", Sideband2_Min, Sideband2_Max);

        HFMass.setRange("sideband1_forSysNear", Sideband1_Min_forSysNear, Sideband1_Max_forSysNear);
        HFMass.setRange("sideband2_forSysNear", Sideband2_Min_forSysNear, Sideband2_Max_forSysNear);
        HFMass.setRange("sideband1_forSysFar", Sideband1_Min_forSysFar, Sideband1_Max_forSysFar);
        HFMass.setRange("sideband2_forSysFar", Sideband2_Min_forSysFar, Sideband2_Max_forSysFar);
        // HFMass.setRange("signal", MassMin, MassMax);

        // intsigX = sig->createIntegral(*HFMass, NormSet(*HFMass), Range("signal"));
        // intbkgX = bkg->createIntegral(*HFMass, NormSet(*HFMass), Range("signal"));
        RooAbsReal *intsigX;
        RooAbsReal *intbkgX, *intbkgSide, *intbkgSideLeft, *intbkgSideRight;
        intsigX = sig.createIntegral(HFMass, NormSet(HFMass), Range("signal"));
        intbkgX = bkg.createIntegral(HFMass, NormSet(HFMass), Range("signal"));

        intbkgSide = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband1", "sideband2"));
        intbkgSideLeft = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband1"));
        intbkgSideRight = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband2"));

        RooAbsReal *intbkgSide_forSysNear = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband1_forSysNear", "sideband2_forSysNear"));
        RooAbsReal *intbkgSideLeft_forSysNear = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband1_forSysNear"));
        RooAbsReal *intbkgSideRight_forSysNear = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband2_forSysNear"));
        RooAbsReal *intbkgSide_forSysFar = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband1_forSysFar", "sideband2_forSysFar"));
        RooAbsReal *intbkgSideLeft_forSysFar = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband1_forSysFar"));
        RooAbsReal *intbkgSideRight_forSysFar = bkg.createIntegral(HFMass, NormSet(HFMass), Range("sideband2_forSysFar"));

        float sig_yield = intsigX->getVal() * nsig->getVal();
        float bkg_yield = intbkgX->getVal() * nbkg->getVal();
        float bkg_frac = (bkg_yield) / (sig_yield + bkg_yield);
        float sig_frac = (sig_yield) / (sig_yield + bkg_yield);

        float bkg_scale = intbkgX->getVal() / intbkgSide->getVal();
        float bkg_scale_forSysNear = intbkgX->getVal() / intbkgSide_forSysNear->getVal();
        float bkg_scale_forSysFar = intbkgX->getVal() / intbkgSide_forSysFar->getVal();
        // cout << "Bkg Yield = " << intbkgX->getVal() << endl;
        // cout << "Sig Yield = " << intsigX->getVal() << endl;
        cout << "Signal Yield = " << sig_yield << endl;
        cout << "Bkg Fraction = " << bkg_frac << endl;
        cout << "Area_Sig / Area_Sideband = " << bkg_scale << endl;
        cout << "Area left side / Area right side = " << intbkgSideLeft->getVal() / intbkgSideRight->getVal() << endl;

        float Mass_D0_fitted = mu_sig->getVal();

        vec_Mass_D0_fit.push_back(Mass_D0_fitted);

        vec_bkg_frac.push_back(bkg_frac);
        vec_bkg_yield.push_back((bkg_yield));
        vec_sig_yield.push_back(sig_yield);

        h1_MassMax->SetBinContent(i + 1, MassUp);
        h1_MassMin->SetBinContent(i + 1, MassDown);

        h1_Sideband1Min->SetBinContent(i + 1, Sideband1_Min);
        h1_Sideband1Max->SetBinContent(i + 1, Sideband1_Max);
        h1_Sideband2Min->SetBinContent(i + 1, Sideband2_Min);
        h1_Sideband2Max->SetBinContent(i + 1, Sideband2_Max);

        h1_Sideband1Min_forSysNear->SetBinContent(i + 1, Sideband1_Min_forSysNear);
        h1_Sideband1Max_forSysNear->SetBinContent(i + 1, Sideband1_Max_forSysNear);
        h1_Sideband2Min_forSysNear->SetBinContent(i + 1, Sideband2_Min_forSysNear);
        h1_Sideband2Max_forSysNear->SetBinContent(i + 1, Sideband2_Max_forSysNear);

        h1_Sideband1Min_forSysFar->SetBinContent(i + 1, Sideband1_Min_forSysFar);
        h1_Sideband1Max_forSysFar->SetBinContent(i + 1, Sideband1_Max_forSysFar);
        h1_Sideband2Min_forSysFar->SetBinContent(i + 1, Sideband2_Min_forSysFar);
        h1_Sideband2Max_forSysFar->SetBinContent(i + 1, Sideband2_Max_forSysFar);

        h1_BkgScale->SetBinContent(i + 1, bkg_scale);

        h1_BkgScale_forSysNear->SetBinContent(i + 1, bkg_scale_forSysNear);
        h1_BkgScale_forSysFar->SetBinContent(i + 1, bkg_scale_forSysFar);

        // Add a vertical dashed line at x = 2

        double x_linelow = MassDown;
        TLine *linelow = new TLine(x_linelow, xframe->GetMinimum(), x_linelow, xframe->GetMaximum());
        linelow->SetLineColorAlpha(kGreen + 1, 1.0);
        linelow->SetLineStyle(3); // Dashed line
        linelow->SetLineWidth(2);
        double x_linehigh = MassUp;
        TLine *linehigh = new TLine(x_linehigh, xframe->GetMinimum(), x_linehigh, xframe->GetMaximum());
        linehigh->SetLineColorAlpha(kGreen + 1, 1.0);
        linehigh->SetLineStyle(3); // Dashed line
        linehigh->SetLineWidth(2);

        double x_sideline1low = Sideband1_Min;
        TLine *sideline1low = new TLine(x_sideline1low, xframe->GetMinimum(), x_sideline1low, xframe->GetMaximum());
        sideline1low->SetLineColorAlpha(kBlue + 1, 1.0);
        sideline1low->SetLineStyle(3); // Dashed line
        sideline1low->SetLineWidth(2);
        double x_sideline1high = Sideband1_Max;
        TLine *sideline1high = new TLine(x_sideline1high, xframe->GetMinimum(), x_sideline1high, xframe->GetMaximum());
        sideline1high->SetLineColorAlpha(kBlue + 1, 1.0);
        sideline1high->SetLineStyle(3); // Dashed line
        sideline1high->SetLineWidth(2);

        double x_sideline2low = Sideband2_Min;
        TLine *sideline2low = new TLine(x_sideline2low, xframe->GetMinimum(), x_sideline2low, xframe->GetMaximum());
        sideline2low->SetLineColorAlpha(kBlue + 1, 1.0);
        sideline2low->SetLineStyle(3); // Dashed line
        sideline2low->SetLineWidth(2);
        double x_sideline2high = Sideband2_Max;
        TLine *sideline2high = new TLine(x_sideline2high, xframe->GetMinimum(), x_sideline2high, xframe->GetMaximum());
        sideline2high->SetLineColorAlpha(kBlue + 1, 1.0);
        sideline2high->SetLineStyle(3); // Dashed line
        sideline2high->SetLineWidth(2);

        ican = 0;
        ccan[ican]->cd(i + 1);
        if (isData)
        {
            linelow->Draw("SAME");
            linehigh->Draw("SAME");
            sideline1low->Draw("SAME");
            sideline1high->Draw("SAME");
            sideline2low->Draw("SAME");
            sideline2high->Draw("SAME");
        }

        linelow->SetY1(xframe2->GetMinimum());
        linehigh->SetY1(xframe2->GetMinimum());
        sideline1low->SetY1(xframe2->GetMinimum());
        sideline1high->SetY1(xframe2->GetMinimum());
        sideline2low->SetY1(xframe2->GetMinimum());
        sideline2high->SetY1(xframe2->GetMinimum());

        linelow->SetY2(xframe2->GetMaximum());
        linehigh->SetY2(xframe2->GetMaximum());
        sideline1low->SetY2(xframe2->GetMaximum());
        sideline1high->SetY2(xframe2->GetMaximum());
        sideline2low->SetY2(xframe2->GetMaximum());
        sideline2high->SetY2(xframe2->GetMaximum());

        ican = 1;
        ccan[ican]->cd(i + 1);
        if (isData)
        {
            linelow->Draw("SAME");
            linehigh->Draw("SAME");
            sideline1low->Draw("SAME");
            sideline1high->Draw("SAME");
            sideline2low->Draw("SAME");
            sideline2high->Draw("SAME");
        }

        if (!DoSystematic)
        {
            SigParams
                << mu_sig->getVal() << "," << sigma1->getVal() << "," << sigma2->getVal() << "," << alpha1_sig->getVal() << "," << p1_sig->getVal() << "," << p1_sig2->getVal() << "," << alpha2_sig->getVal() << "," << p2_sig->getVal() << "," << p2_sig2->getVal() << "," << nsig->getVal() << ", " << sig_frac << endl;
        }
        else
            SigParams
                << sig2_m->getVal() << "," << sig2_t->getVal() << "," << sig2_n->getVal() << "," << nsig->getVal() << ", " << sig_frac << endl;

        BkgParams << a0_cheb->getVal() << "," << a1_cheb->getVal() << "," << a2_cheb->getVal() << "," << nbkg->getVal() << ", " << bkg_frac << endl;
    }

    // ++ican;
    // sprintf(buf, "ccan%d", ican);
    // ccan[ican] = new TCanvas(buf, buf, 30 * ican, 30 * ican, 800, (8.5 / 11.) * 800);
    // ccan[ican]->SetFillColor(10);
    // // gPad->SetLeftMargin(0.16);
    // // gPad->SetBottomMargin(0.06);
    // ccan[ican]->cd();
    // ccan[ican]->Divide(1, 2, 0.0001, 0.0001);

    // RooPlot *xframe2 = HFMass.frame(Title("Pull Distribution"));
    // xframe2->addPlotable(hpull, "P");

    // ccan[ican]->cd(1);
    // ;
    // gPad->SetLeftMargin(0.15);
    // xframe->GetYaxis()->SetTitleOffset(1.6);
    // xframe->Draw();
    // ccan[ican]->cd(2);
    // ;
    // gPad->SetLeftMargin(0.15);
    // xframe->GetYaxis()->SetTitleOffset(1.6);
    // xframe2->Draw();

    // ccan[ican]->cd();
    // ccan[ican]->Update();
    // if (ican == 0)
    // {
    //   ccan[ican]->Print(plotfileO.Data());
    // }
    // else
    // {
    //   ccan[ican]->Print(plotfilePDF.Data());
    // }

    ican = 0;
    // Return to the main canvas to draw the label
    ccan[ican]->cd(); // This ensures we are in the main canvas, not a sub-pad

    // Create the diagonal label
    TText *label = new TText();
    label->SetTextSize(0.15);                 // Adjust size
    label->SetTextAlign(22);                  // Center alignment
    label->SetTextAngle(45);                  // Rotate diagonally
    label->SetTextColorAlpha(kGray + 2, 0.3); // Semi-transparent gray text

    // Use NDC coordinates for positioning (bottom-left to top-right)
    // label->DrawTextNDC(0.5, 0.5, "LHCb Unofficial");

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

    ican = 1;
    // Return to the main canvas to draw the label
    ccan[ican]->cd(); // This ensures we are in the main canvas, not a sub-pad

    // label->DrawTextNDC(0.5, 0.5, "LHCb Unofficial");

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

    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "   Mass D0 (PDG): " << 1.86484 << " GeV " << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < vec_bkg_frac.size(); i++)
    {
        cout << ptHF_binedges[i] << " < pT < " << ptHF_binedges[i + 1] << ": Mass = " << vec_Mass_D0_fit[i] << " || Signal = " << vec_sig_yield[i] << ", Background = " << vec_bkg_yield[i]
             << ", Bkg Frac = " << vec_bkg_frac[i] * 100 << " %" << endl;
    }
    float sigyield = std::accumulate(vec_sig_yield.begin(), vec_sig_yield.end(), 0);
    cout << "Total Signal Yield = " << sigyield << endl;

    // cout<<exp_c->getVal()<<endl;

    SigParams.close();
    BkgParams.close();

    f.Write();
    f.Close();
}
