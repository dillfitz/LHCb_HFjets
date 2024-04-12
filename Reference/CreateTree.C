
void CreateTree(TString particle = "B")
{
    TString data_dir = "/Users/josearias18/Desktop/QCDc2/pythia/Data/";
    TChain *t = new TChain("Decay/DecayTree");
//	TChain *t = new TChain("Jets/DecayTree");
//    TChain *t = new TChain("mcjettuple/MCJetTree");
//    TChain *t = new TChain("MCJets/MCJetTree");
	if (particle == "B")
	{
//	  t->Add("Bjet_b_2016_MD_09082022_url333_0_800.root");
//	  t->Add("Bjet_b_2016_MD_09082022_url333_800_1429.root");
//	  t->Add("Bjet_b_2016_MU_09082022_url334_0_800.root");
//	  t->Add("Bjet_b_2016_MU_09082022_url334_800_1299.root");
//	  t->Add("Bjet_b_2017_MD_09082022_url335_0_800.root");
//	  t->Add("Bjet_b_2017_MD_09082022_url335_800_882.root");
//	  t->Add("Bjet_b_2017_MU_09082022_url336_0_800.root");
//	  t->Add("Bjet_b_2017_MU_09082022_url336_800_846.root");
//	  t->Add("Bjet_b_2018_MD_09082022_url337_0_800.root");
//	  t->Add("Bjet_b_2018_MD_09082022_url337_800_988.root");
//	  t->Add("Bjet_b_2018_MU_09082022_url338_0_800.root");
//	  t->Add("Bjet_b_2018_MU_09082022_url338_800_1042.root");
//      t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MD_11252022_url423_0_800.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MD_11252022_url423_800_1426.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MU_11252022_url424_0_800.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2016_MU_11252022_url424_800_1315.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MD_11252022_url425_0_800.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MD_11252022_url425_800_877.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MU_11252022_url426_0_800.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2017_MU_11252022_url426_800_847.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MD_11252022_url427_0_800.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MD_11252022_url427_800_989.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MU_11252022_url428_0_800.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_nojetid_2018_MU_11252022_url428_800_1040.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2016_Sim09k_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2016_Sim09k_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2016_Sim09l_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2016_Sim09l_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2016_Sim10a_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2016_Sim10a_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2017_Sim09k_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2017_Sim09k_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2017_Sim09l_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2017_Sim09l_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2017_Sim10a_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2017_Sim10a_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2018_Sim09k_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2018_Sim09k_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2018_Sim09l_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2018_Sim09l_MU_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2018_Sim10a_MD_10192023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_nojetid_DFT_2018_Sim10a_MU_10192023_full.root");
        
        //// MC (03/03/2024)
        //-rw-r--r--. 1 ichahrou z5  2094194615 Mar  3 03:12 Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09i_MD_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  2093913015 Mar  3 03:12 Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09i_MU_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  1614612201 Mar  3 03:11 Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09h_MU_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  2023916510 Mar  3 03:10 Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09i_MU_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  1661003642 Mar  3 03:08 Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09h_MU_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  2004699767 Mar  3 03:07 Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09i_MD_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  1644244197 Mar  3 03:05 Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09h_MD_03032024_full.root
//        -rw-r--r--. 1 ichahrou z5  1582529837 Mar  3 03:03 Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09h_MD_03032024_full.root
        ///// New Data
//        -rw-r--r--. 1 ichahrou z5 703789849 Mar  1 17:22 Bjet_Jpsi2MuMu_Data_HighPT_2018_MU_02292024.root
//        -rw-r--r--. 1 ichahrou z5 638182780 Mar  1 02:02 Bjet_Jpsi2MuMu_Data_HighPT_2016_MD_02292024.root
//        -rw-r--r--. 1 ichahrou z5 609459831 Mar  1 00:24 Bjet_Jpsi2MuMu_Data_HighPT_2016_MU_02292024.root
//        -rw-r--r--. 1 ichahrou z5 662654980 Mar  1 00:22 Bjet_Jpsi2MuMu_Data_HighPT_2018_MD_02292024.root
//        -rw-r--r--. 1 ichahrou z5 555560268 Mar  1 00:20 Bjet_Jpsi2MuMu_Data_HighPT_2017_MD_02292024.root
//        -rw-r--r--. 1 ichahrou z5 535853901 Mar  1 00:18 Bjet_Jpsi2MuMu_Data_HighPT_2017_MU_02292024.root
        
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09i_MD_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09i_MU_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09h_MU_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09i_MU_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09h_MU_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09i_MD_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09h_MD_03032024_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09h_MD_03032024_full.root");
        
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_Jpsi2MuMu_Data_HighPT_2018_MU_02292024.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_Jpsi2MuMu_Data_HighPT_2016_MD_02292024.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_Jpsi2MuMu_Data_HighPT_2016_MU_02292024.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_Jpsi2MuMu_Data_HighPT_2018_MD_02292024.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_Jpsi2MuMu_Data_HighPT_2017_MD_02292024.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Bjet_Jpsi2MuMu_Data_HighPT_2017_MU_02292024.root");
        
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2016_Sim09k_MD_02192024_full.root");
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09k_MD_02192024_full.root");
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09k_MD_02192024_full.root");

        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2016_Sim09l_MD_02192024_full.root");
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim09l_MD_02192024_full.root");
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim09l_MD_02192024_full.root");

        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2016_Sim10a_MD_02192024_full.root");
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2017_Sim10a_MD_02192024_full.root");
        t->Add(data_dir + "Bjet_MC_Jpsi2MuMu_HighPT_2018_Sim10a_MD_02192024_full.root");
        
        //       rsync -chavzP --stats jariasre@lxplus.cern.ch:/eos/lhcb/user/i/ichahrou/Bjet_MC_Jpsi2MuMu*02192024* /Users/josearias18/Desktop/QCDc2/pythia/Data
        //       BuPsipi_in_jet_13TeV_nojetid.root

        
	}
	
	if (particle == "D")
	{
//	  t->Add("Djet_2016_MD_09082022_url327_0_535.root");
//	  t->Add("Djet_2016_MU_09082022_url328_0_452.root");
//	  t->Add("Djet_2017_MD_09082022_url329_0_345.root");
//	  t->Add("Djet_2017_MU_09082022_url330_0_327.root");
//	  t->Add("Djet_2018_MD_09082022_url331_0_372.root");
//	  t->Add("Djet_2018_MU_09082022_url332_0_392.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2018_MU_05182023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2018_MD_05182023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2017_MU_05182023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2017_MD_05182023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2016_MU_05182023_full.root");
//        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2016_MD_05182023_full.root");
        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2018_MU_01182023_full.root");
        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2018_MD_01182023_full.root");
        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2017_MU_01182023_full.root");
        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2017_MD_01182023_full.root");
        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2016_MU_01182023_full.root");
        t->Add("/Users/josearias18/Desktop/QCDc2/pythia/Data/Djet_nojetid_2016_MD_01182023_full.root");
	}	
	
	TString className = particle;
//	className += "zeroes_Variable_Tree";
    className += "jetTree";
//    className += "jetMCTree";
	t->MakeClass(className);

}
