#include "../Settings.h"

void SBsubCrossCheck()
{

    gStyle->SetOptStat(0);

    TFile *infile_upper = new TFile("../../../root_files/Bjets/Systematics/massfitsysupper_sys_ev_-1_ptj_10100_eta_2.54.0_HF_ghost_0.4_b_PID_iters_4_91599.root", "READ");
    TFile *infile_lower = new TFile("../../../root_files/Bjets/Systematics/massfitsyslower_sys_ev_-1_ptj_10100_eta_2.54.0_HF_ghost_0.4_b_PID_iters_4_91599.root", "READ");
    TFile *infile_total = new TFile("../../../root_files/Bjets/Systematics/total_sys_ev_-1_ptj_10100_eta_2.54.0_HF_ghost_0.4_b_PID_iters_4_91599.root", "READ");

    TCanvas *c0 = new TCanvas("c0");

    TLegend *leg_z = new TLegend(0.7, 0.1, 0.9, 0.3);
    for (int i=1; i<ptbinsize; i++)
    {
        TH1D *z_sys_upper_temp = (TH1D*)infile_upper->Get(Form("z_pt%d_ratio", i));
        TH1D *z_sys_lower_temp = (TH1D*)infile_lower->Get(Form("z_pt%d_ratio", i));
        TH1D *z_sys_sbsub_temp = (TH1D*)infile_total->Get(Form("z_sys_sbsub_pt%d", i));
        TH1D *z_sys_total_temp = (TH1D*)infile_total->Get(Form("z_sys_total_pt%d", i));

        z_sys_upper_temp->SetMarkerStyle(kFullCircle);
        z_sys_upper_temp->SetMarkerColor(kBlue);
        z_sys_upper_temp->SetLineColor(kBlue);

        z_sys_lower_temp->SetMarkerStyle(kFullSquare);
        z_sys_lower_temp->SetMarkerColor(kRed);
        z_sys_lower_temp->SetLineColor(kRed);

        z_sys_sbsub_temp->SetMarkerStyle(kFullDiamond);
        z_sys_sbsub_temp->SetMarkerSize(1.5);
        z_sys_sbsub_temp->SetMarkerColor(kBlack);
        z_sys_sbsub_temp->SetLineColor(kBlack);

        z_sys_total_temp->SetFillColorAlpha(16, 0.3);
        z_sys_total_temp->SetLineColor(kBlack);

        z_sys_upper_temp->SetTitle(Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
        z_sys_upper_temp->Draw("P");
        z_sys_lower_temp->Draw("P SAME");
        z_sys_sbsub_temp->Draw("P SAME");
        z_sys_total_temp->Draw("HIST SAME");

        if (i==1)
        {
            leg_z->AddEntry(z_sys_upper_temp, "Upper SB sys");
            leg_z->AddEntry(z_sys_lower_temp, "Lower SB sys");
            leg_z->AddEntry(z_sys_sbsub_temp, "Nominal SB sys");
            leg_z->AddEntry(z_sys_total_temp, "Total sys");
        }

        leg_z->Draw("SAME");


        c0->SaveAs(Form("../../../plots/Bjets/Systematics/z_sys_sbsub_crosscheck_pt%d.png", i));
    }

    TLegend *leg_jt = new TLegend(0.7, 0.1, 0.9, 0.3);
    for (int i=1; i<ptbinsize; i++)
    {
        TH1D *jt_sys_upper_temp = (TH1D*)infile_upper->Get(Form("jt_pt%d_ratio", i));
        TH1D *jt_sys_lower_temp = (TH1D*)infile_lower->Get(Form("jt_pt%d_ratio", i));
        TH1D *jt_sys_sbsub_temp = (TH1D*)infile_total->Get(Form("jt_sys_sbsub_pt%d", i));
        TH1D *jt_sys_total_temp = (TH1D*)infile_total->Get(Form("jt_sys_total_pt%d", i));

        jt_sys_upper_temp->SetMarkerStyle(kFullCircle);
        jt_sys_upper_temp->SetMarkerColor(kBlue);
        jt_sys_upper_temp->SetLineColor(kBlue);

        jt_sys_lower_temp->SetMarkerStyle(kFullSquare);
        jt_sys_lower_temp->SetMarkerColor(kRed);
        jt_sys_lower_temp->SetLineColor(kRed);

        jt_sys_sbsub_temp->SetMarkerStyle(kFullDiamond);
        jt_sys_sbsub_temp->SetMarkerSize(1.5);
        jt_sys_sbsub_temp->SetMarkerColor(kBlack);
        jt_sys_sbsub_temp->SetLineColor(kBlack);

        jt_sys_total_temp->SetFillColorAlpha(16, 0.3);
        jt_sys_total_temp->SetLineColor(kBlack);

        jt_sys_upper_temp->SetTitle(Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
        jt_sys_upper_temp->Draw("P");
        jt_sys_lower_temp->Draw("P SAME");
        jt_sys_sbsub_temp->Draw("P SAME");
        jt_sys_total_temp->Draw("HIST SAME");

        if (i==1)
        {
            leg_jt->AddEntry(jt_sys_upper_temp, "Upper SB sys");
            leg_jt->AddEntry(jt_sys_lower_temp, "Lower SB sys");
            leg_jt->AddEntry(jt_sys_sbsub_temp, "Nominal SB sys");
            leg_jt->AddEntry(jt_sys_total_temp, "Total sys");
        }

        leg_jt->Draw("SAME");


        c0->SaveAs(Form("../../../plots/Bjets/Systematics/jt_sys_sbsub_crosscheck_pt%d.png", i));
    }

    TLegend *leg_r = new TLegend(0.7, 0.1, 0.9, 0.3);
    for (int i=1; i<ptbinsize; i++)
    {
        TH1D *r_sys_upper_temp = (TH1D*)infile_upper->Get(Form("r_pt%d_ratio", i));
        TH1D *r_sys_lower_temp = (TH1D*)infile_lower->Get(Form("r_pt%d_ratio", i));
        TH1D *r_sys_sbsub_temp = (TH1D*)infile_total->Get(Form("r_sys_sbsub_pt%d", i));
        TH1D *r_sys_total_temp = (TH1D*)infile_total->Get(Form("r_sys_total_pt%d", i));

        r_sys_upper_temp->SetMarkerStyle(kFullCircle);
        r_sys_upper_temp->SetMarkerColor(kBlue);
        r_sys_upper_temp->SetLineColor(kBlue);

        r_sys_lower_temp->SetMarkerStyle(kFullSquare);
        r_sys_lower_temp->SetMarkerColor(kRed);
        r_sys_lower_temp->SetLineColor(kRed);

        r_sys_sbsub_temp->SetMarkerStyle(kFullDiamond);
        r_sys_sbsub_temp->SetMarkerSize(1.5);
        r_sys_sbsub_temp->SetMarkerColor(kBlack);
        r_sys_sbsub_temp->SetLineColor(kBlack);

        r_sys_total_temp->SetFillColorAlpha(16, 0.3);
        r_sys_total_temp->SetLineColor(kBlack);

        r_sys_upper_temp->SetTitle(Form(" %.1f < p_{T, j} < %.1f GeV", pt_binedges[i], pt_binedges[i + 1]));
        r_sys_upper_temp->Draw("P");
        r_sys_lower_temp->Draw("P SAME");
        r_sys_sbsub_temp->Draw("P SAME");
        r_sys_total_temp->Draw("HIST SAME");

        if (i==1)
        {
            leg_r->AddEntry(r_sys_upper_temp, "Upper SB sys");
            leg_r->AddEntry(r_sys_lower_temp, "Lower SB sys");
            leg_r->AddEntry(r_sys_sbsub_temp, "Nominal SB sys");
            leg_r->AddEntry(r_sys_total_temp, "Total sys");
        }

        leg_r->Draw("SAME");


        c0->SaveAs(Form("../../../plots/Bjets/Systematics/r_sys_sbsub_crosscheck_pt%d.png", i));
    }    
 
}