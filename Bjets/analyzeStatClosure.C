void analyzeStatClosure()
{
    TH1D *z3_pt4 = new TH1D("z3_pt4", "", 20, 0.5, 1.5);
    TH1D *z10_pt4 = new TH1D("z10_pt4", "", 20, 0.9, 1.1);

    int nRuns = 10;
    TFile *infile = new TFile("../../root_files/BjetsMC/closure_ev_-1_ptj_5100_eta_2.54.0_HF_ghost_0.4_b_PID_iters_4_91599_91599.root", "READ");
    TFile *outfile = new TFile("../../root_files/BjetsMC/stat_closure_analysis.root", "RECREATE");
    for (int i=0; i<nRuns; i++)
    {
        TH1D *htemp = (TH1D*)infile->Get(Form("z_ratio_smear%d_pt4", i));
        std::cout << "htemp Bin 3 : " << htemp->GetBinContent(3) << std::endl; 
        z3_pt4->Fill(htemp->GetBinContent(3));
        z10_pt4->Fill(htemp->GetBinContent(10));
        //z3_pt4->Draw();
    }
    z3_pt4->Write();
    z10_pt4->Write();
    outfile->Close();
}