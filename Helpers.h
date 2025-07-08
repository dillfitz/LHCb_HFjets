#include <vector>
#include <string>
#include <iostream>

#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TH1D.h>
#include <TRandom3.h>
//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/contrib/SoftDrop.hh"
// #include "/afs/cern.ch/work/i/ichahrou/RooUnfold/src/RooUnfoldBayes.h"
// #include "/afs/cern.ch/work/i/ichahrou/RooUnfold2.0.1/build/RooUnfoldResponse.h"

// gSystem->AddIncludePath(" -I$HOME//fastjet-install/include");
//     gSystem->Load("$HOME//fastjet-install/lib/libfastjet.so");

//using namespace fastjet;

//class MyInfo : public PseudoJet::UserInfoBase
//{
//public:
//  MyInfo(int id) : _pdg_id(id) {}
//  int pdg_id() const { return _pdg_id; }
//  int _pdg_id;
//};
///////////////////////////////////////////////////////////////
string m_jetEcPath;
const int m_jecNPvs = 2;  ///< Number of n(PV) JEC bins.
const int m_jecNEta = 10; ///< Number of eta JEC bins.
const int m_jecNCpf = 6;  ///< Number of (sum charged pT)/pT JEC bins.
const int m_jecNPhi = 3;  ///< Number of phi JEC bins.
const int m_jecNPt = 1;   ///< Number of pT JEC bins.
/// Number of PVs for the event (try RecVertices, then association).
int m_jecPvs;
/// Jet energy correction histograms.
TH1D *m_jecs[m_jecNPvs][m_jecNEta][m_jecNCpf][m_jecNPhi];

const double m_jecLimEta[m_jecNEta + 1] = {2.0, 2.2, 2.3, 2.4, 2.6, 2.8, 3.0, 3.2, 3.6, 4.2, 4.5};
const double m_jecLimCpf[m_jecNCpf + 1] = {0.06, 0.3, 0.4, 0.5, 0.6, 0.8, 1.0001};
const double m_jecLimPhi[m_jecNPhi + 1] = {0, 1.0 / 6.0 * M_PI, 1.0 / 3.0 * M_PI, 0.5 * M_PI};
const double m_jecLimPt[m_jecNPt + 1] = {5, 298};
///////////////////////////////////////////////////////////////

//double dot_pseudo(PseudoJet pj1, PseudoJet pj2);
//void decluster_jet(PseudoJet mom, PseudoJet hfhad, vector<double> &kTs, vector<double> &Erads,
//                   vector<double> &thetas, vector<double> &dRs);

double checkphi(double phi);
double folddphi(double dphi);
double checkdR(TLorentzVector v1, TLorentzVector v2);

vector<TF1 *> f1_num_vec, f1_denom_vec, f1_ratio_vec, f1_num_theory,
    f1_denom_theory, f1_ratio_theory, f1_theta_num_theory, f1_theta_denom_theory,
    f1_theta_ratio_theory, f1_theta_num, f1_theta_denom, f1_theta_ratio;
vector<double> mass_num_vec, mass_denom_vec, norm_num_vec, norm_denom_vec, norm_ratio_vec;
vector<double> mass_theta_num, mass_theta_denom, mass_theta_ratio_num, mass_theta_ratio_denom;
vector<double> norm_theta_num, norm_theta_denom, norm_theta_ratio;

std::vector<TH1D *> h1_thetas, h1_Rratios, h1_thetas_f1, h1_Rratios_f1, h1_thetas_f2, h1_Rratios_f2;
std::vector<TH1D *> h1_tr_thetas, h1_tr_Rratios, h1_tr_thetas_f1,
    h1_tr_Rratios_f1, h1_tr_thetas_f2, h1_tr_Rratios_f2;
std::vector<TH1D *> h1_meas_thetas, h1_meas_Rratios, h1_meas_thetas_f1,
    h1_meas_Rratios_f1, h1_meas_thetas_f2, h1_meas_Rratios_f2;

std::vector<TH1D *> h1_theta_ratio, h1_R_ratio;
std::vector<std::vector<TH1D *>> h1_Rratios_vec;

std::vector<TH1D *> h1_recomatch_px, h1_recomatch_py, h1_recomatch_pz, h1_recomatch_eta, h1_recomatch_phi;
std::vector<TH1D *> h1_recomatchcharged_px, h1_recomatchcharged_py, h1_recomatchcharged_pz, h1_recomatchcharged_eta, h1_recomatchcharged_phi;
std::vector<TH1D *> h1_recomatchneutral_px, h1_recomatchneutral_py, h1_recomatchneutral_pz, h1_recomatchneutral_eta, h1_recomatchneutral_phi;

std::vector<TH1D *> h1_thetaErad_proj;

//double dot_pseudo(PseudoJet pj1, PseudoJet pj2)
//{
//  return pj1.px() * pj2.px() + pj1.py() * pj2.py() + pj1.pz() * pj2.pz();
//}
//double PseudoJetAngle(PseudoJet pj1, PseudoJet pj2)
//{
//  TLorentzVector t1(pj1.px(), pj1.py(), pj1.pz(), pj1.e());
//  TLorentzVector t2(pj2.px(), pj2.py(), pj2.pz(), pj2.e());
//  return t1.Angle(t2.Vect());
//}

//bool DtrCuts(TLorentzVector dtr, double dtr_charge, double dtr_ghost, double trchi2ndf,
//             bool chargedJetCut = false, bool forTrackEff = false)
//{
//  bool dtrpt_pass(true), dtrp_pass(true), dtrchi2_pass(true), dtrcharge_pass(true), dtrghost_pass(true);
//  double min_p = 4.;
//  double min_pt = 0.25;
//  if (forTrackEff)
//  {
//    min_p = 1.;
//    min_pt = 0.1;
//  }
//  if (fabs(dtr_charge) > 0)
//  {
//    if (dtr.Pt() < min_pt /* GeV */)
//      dtrpt_pass = false;
//    if (dtr.P() < min_p || dtr.P() > 1000. /* GeV */)
//      dtrp_pass = false;
//    if (trchi2ndf > 3)
//      dtrchi2_pass = false;
//  }
//  else
//  {
//    if (dtr.P() < min_p /* GeV */ || dtr.P() > 1000.)
//      dtrp_pass = false;
//    if (dtr.Pt() < min_pt /* GeV */)
//      dtrpt_pass = false;
//  }
//  if (chargedJetCut)
//  {
//    if (fabs(dtr_charge) == 0)
//      dtrcharge_pass = false;
//  }
//  if (ghostCut)
//  {
//    if (dtr_ghost > ghostProb)
//      dtrghost_pass = false;
//  }
//  if (dtrpt_pass && dtrp_pass && dtrchi2_pass && dtrcharge_pass && dtrghost_pass)
//    return true;
//  else
//    return false;
//}

//void decluster_jet(PseudoJet mom, PseudoJet hfhad, vector<double> &kTs, vector<double> &Erads,
//                   vector<double> &thetas, vector<double> &dRs, vector<double> &etas, vector<double> &phis)
//{
//  PseudoJet dtr1, dtr2;
//  double Erad, Esoft, pt_leading, kT, theta, dR;
//  double ptsoft;
//  bool check_splitting;
//
//  while (mom.has_parents(dtr1, dtr2))
//  {
//
//    Erad = mom.e();
//    TLorentzVector Tmom(mom.px(), mom.py(), mom.pz(), mom.e());
//    TLorentzVector Tdtr1(dtr1.px(), dtr1.py(), dtr1.pz(), dtr1.e());
//    TLorentzVector Tdtr2(dtr2.px(), dtr2.py(), dtr2.pz(), dtr2.e());
//    double theta, eta, phi;
//    double dR;
//
//    if (followHardest)
//      check_splitting = (dtr1.e() > dtr2.e());
//    else
//      check_splitting = (dtr1.contains(hfhad));
//    if (check_splitting)
//    {
//      Esoft = dtr2.e();
//      ptsoft = dtr2.pt();
//      theta = Tmom.Angle(Tdtr2.Vect());
//      dR = Tmom.DeltaR(Tdtr2);
//      eta = Tdtr2.Eta();
//      phi = Tdtr2.Phi();
//      // Erad = dtr1.e();
//      pt_leading = dtr1.pt();
//      mom.reset(dtr1);
//    }
//    else
//    {
//      Esoft = dtr1.e();
//      ptsoft = dtr1.pt();
//      theta = Tmom.Angle(Tdtr1.Vect());
//      dR = Tmom.DeltaR(Tdtr1);
//      eta = Tdtr1.Eta();
//      phi = Tdtr1.Phi();
//      // Erad = dtr2.e();
//      pt_leading = dtr2.pt();
//
//      mom.reset(dtr2);
//    }
//    // kT = Esoft*sin(theta);
//
//    dR = dtr1.delta_R(dtr2);
//    kT = ptsoft * dR;
//
//    // if (kt_cut)
//    // {
//    //   //if (kT < LambdaQCD) cout<<Erad<<", ";
//    //   if (kT < LambdaQCD) continue; //Non-perturbative cut
//    // }
//    kTs.push_back(log(kT));
//    Erads.push_back(Erad);
//    thetas.push_back(log(1. / theta));
//    dRs.push_back(log(jetradius / dR));
//    etas.push_back(eta);
//    phis.push_back(phi);
//    // pt_leading.push_back(pt_leading);
//  }
//}

double checkphi(double phi)
{
  double returnphi = phi;

  if (phi > 1. * TMath::Pi())
    returnphi -= 2 * TMath::Pi();
  else if (phi < -1 * TMath::Pi())
    returnphi += 2 * TMath::Pi();

  return returnphi;
}

double folddphi(double dphi)
{
  double returndphi = dphi;
  if (dphi < 0)
    returndphi += 2. * TMath::Pi();
  if (dphi > 2. * TMath::Pi())
    returndphi -= 2. * TMath::Pi();
  if (dphi > TMath::Pi())
    returndphi = TMath::Pi() - (dphi - TMath::Pi());

  return returndphi;
}
double checkdR(TLorentzVector v1, TLorentzVector v2)
{

  double dr = -99;

  double dphi = checkphi(v1.Phi()) - checkphi(v2.Phi());
  double deta = v1.Rapidity() - v2.Rapidity();
  dphi = checkphi(dphi);

  dr = sqrt(dphi * dphi + deta * deta);

  return dr;
}
void BinLogX(TH1 *h)
{

  TAxis *axis = h->GetXaxis();
  int bins = axis->GetNbins();

  Axis_t from = TMath::Log10(axis->GetXmin());
  Axis_t to = TMath::Log10(axis->GetXmax());
  Axis_t width = (to - from) / bins;
  Axis_t *new_bins = new Axis_t[bins + 1];

  for (int i = 0; i <= bins; i++)
  {
    new_bins[i] = TMath::Power(10, from + i * width);
  }
  axis->Set(bins, new_bins);
  delete[] new_bins;
}

void NormalizeHist(TH1 *h)
{
  if (h == NULL)
    return;
  // h->Scale(1./h->Integral());
  h->Scale(1. / h->Integral(), "width");
}

void NormalizeHistScale(TH1 *h)
{
  if (h == NULL)
    return;
  // h->Scale(1./h->Integral());
  h->Scale(1.0 / h->Integral(), "width");
}

void NormalizeHist(TH2 *h)
{
  if (h == NULL)
    return;
  // h->Scale(1./h->Integral());
  h->Scale(1. / h->Integral(), "width");
}

void NormalizeHist(TH3 *h)
{
  if (h == NULL)
    return;
  // h->Scale(1./h->Integral());
  h->Scale(1. / h->Integral(), "width");
}

double eta_to_theta(double eta1, double eta2)
{
  return fabs(-2 * atan(exp(-eta1)) + 2 * atan(exp(-eta2)));
}

void fillHistos(vector<double> kTs, vector<double> Erads, vector<double> thetas,
                vector<double> dRs, TH2 *h2_thetaErad, TH2 *h2_dRErad,
                TH2 *h2_lundplane, TH2 *h2_ktdR, vector<TH1D *> h1_thetas,
                vector<TH1D *> h1_Rratios,
                TH1D *h1_erad, int &NumJets_TwoSplits, int (&theta_counter_Erad)[NumHists])
{
  if (thetas.size() > 1)
  {
    NumJets_TwoSplits++;

    for (int i = 0; i < thetas.size(); i++)
    {
      h1_erad->Fill(Erads[i]);
      if (kTs[i] > log(LambdaQCD))
      {
        h2_thetaErad->Fill(Erads[i], thetas[i]);
        h2_dRErad->Fill(Erads[i], dRs[i]);
      }
      // h2_Eradjetpt->Fill(Erads.at(i), jet_pt);
      h2_lundplane->Fill(thetas.at(i), kTs.at(i));
      h2_ktdR->Fill(dRs.at(i), kTs.at(i));

      // outstream_Erads.push_back(Erads[i]);
      // outstream_thetas.push_back(log(1./thetas[i]));

      if (kTs[i] < log(LambdaQCD))
        continue;
      if (Erad_cut)
      {
        for (int j = 0; j < NumHists; j++)
        {
          if (Erads[i] > MinErad + StepErad * j && Erads[i] < MinErad + StepErad * (j + 1))
          {

            h1_thetas[j]->Fill(exp(-1 * thetas[i]));
            h1_Rratios[j]->Fill(thetas[i]);
            theta_counter_Erad[j]++;
            break;
          }
        }
      }
    }
  }
}

void matchEmissions(vector<double> vars, vector<double> meas_vars,
                    vector<double> etas, vector<double> meas_etas,
                    vector<double> phis, vector<double> meas_phis,
                    TH1D *h1_num)
{

  int match_loc = -99;
  vector<double> bans;
  for (int i = 0; i < vars.size(); i++)
  {
    bool found_match = false;
    double min_dr = 0.1;
    for (int j = 0; j < meas_vars.size(); j++)
    {
      bool banned = false;
      for (int k = 0; k < bans.size(); k++)
      {
        if (j == bans[k])
          banned = true;
      }
      if (banned)
        continue;
      double delta_R = sqrt(pow(etas[i] - meas_etas[j], 2) + pow(checkphi(checkphi(phis[i]) - checkphi(meas_phis[j])), 2));
      if (delta_R < min_dr)
      {
        found_match = true;
        min_dr = delta_R;
        match_loc = j;
      }
    }
    if (found_match)
    {
      bans.push_back(match_loc);
      h1_num->Fill(vars[i]);
    }
  }
}
void matchEmissions(vector<double> vars1, vector<double> vars2,
                    vector<double> etas, vector<double> meas_etas,
                    vector<double> phis, vector<double> meas_phis,
                    TH2D *h2_num, bool meas_1 = false, bool meas_2 = false)
{

  int match_loc = -99;
  vector<double> bans;
  for (int i = 0; i < etas.size(); i++)
  {
    bool found_match = false;
    double min_dr = 0.1;
    for (int j = 0; j < meas_etas.size(); j++)
    {
      bool banned = false;
      for (int k = 0; k < bans.size(); k++)
      {
        if (j == bans[k])
          banned = true;
      }
      if (banned)
        continue;
      double delta_R = sqrt(pow(etas[i] - meas_etas[j], 2) + pow(checkphi(checkphi(phis[i]) - checkphi(meas_phis[j])), 2));
      // cout<<"mine = "<<etas[i]<<","<<phis[i]<<endl;
      // cout<<"minemeas_ = "<<meas_etas[j]<<","<<meas_phis[j]<<endl;
      if (delta_R < min_dr)
      {
        found_match = true;
        min_dr = delta_R;
        match_loc = j;
      }
    }
    if (found_match)
    {
      bans.push_back(match_loc);
      if (meas_1 && meas_2)
        h2_num->Fill(vars1[match_loc], vars2[match_loc]);
      else if (meas_1 && !meas_2)
        h2_num->Fill(vars1[match_loc], vars2[i]);
      else if (!meas_1 && meas_2)
        h2_num->Fill(vars1[i], vars2[match_loc]);
      else
        h2_num->Fill(vars1[i], vars2[i]);
    }
  }
}

template <typename T>
double getAverage(std::vector<T> const &v)
{
  if (v.empty())
  {
    return 0;
  }
  return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double getLargestAngle(double etaMin, double etaMax)
{
  double smallest_eta;
  if (etaMin < 0 && etaMax > 0)
    smallest_eta = 0;
  else if (fabs(etaMin) < fabs(etaMax))
    smallest_eta = etaMin;
  else
    smallest_eta = etaMax;
  double angle_high = eta_to_theta(jetradius, smallest_eta);
  return angle_high;
}

void findIntegrationBounds(vector<TH1D *> h1, vector<double> &vlow, vector<double> &vhigh)
{

  for (int i = 0; i < NumHists; i++)
  {
    int current_binlow = 1;
    int current_binhigh = 1;
    for (int j = 0; j < h1[i]->GetNbinsX(); j++)
    {
      if (h1[i]->GetBinContent(j + 1) > 0)
        current_binhigh = j + 1;
    }
    for (int j = 0; j < h1[i]->GetNbinsX(); j++)
    {
      if (h1[i]->GetBinContent(j + 1) > 0)
        current_binlow = j + 1;
      break;
    }
    vhigh.push_back(h1[i]->GetBinCenter(current_binhigh - 2));
    vlow.push_back(h1[i]->GetBinCenter(current_binlow + 2));
  }
}

void GetPulls(TH2 *hvals, TH2 *hpull, TH1 *h1)
{
  for (int i = 1; i < hvals->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < hvals->GetNbinsY() + 1; j++)
    {
      double err = hvals->GetBinError(i, j);
      double content = hvals->GetBinContent(i, j);
      if (content == 0)
        continue;
      double pull = (content) / err;
      hpull->SetBinContent(i, j, pull);
      h1->Fill(pull);
    }
  }
}
void GetPullsRatio(TH2 *hvals, TH2 *hpull, TH1 *h1)
{
  for (int i = 1; i < hvals->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < hvals->GetNbinsY() + 1; j++)
    {
      double err = hvals->GetBinError(i, j);
      double content = hvals->GetBinContent(i, j);
      if (content == 0)
        continue;
      double pull = (content - 1) / err;
      hpull->SetBinContent(i, j, pull);
      h1->Fill(pull);
    }
  }
}
void GetPullsRatio(TH2 *hvals, TH2 *hpull, TH1 *h1, int xbinsize, int ybinsize)
{
  for (int i = 1; i < xbinsize + 1; i++)
  {
    for (int j = 1; j < ybinsize + 1; j++)
    {
      double err = hvals->GetBinError(i, j);
      double content = hvals->GetBinContent(i, j);
      if (content == 0)
        continue;
      double pull = (content - 1) / err;
      hpull->SetBinContent(i, j, pull);
      h1->Fill(pull);
    }
  }
}
void GetMSE(TH2 *hunfold, TH2 *htrue, TH2 *hmse)
{
  for (int i = 1; i < hunfold->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < hunfold->GetNbinsY() + 1; j++)
    {
      // double err = hunfold->GetBinError(i, j);
      double content = hunfold->GetBinContent(i, j);
      if (content == 0)
        continue;
      double truecontent = htrue->GetBinContent(i, j);
      double mse = pow(content - truecontent, 2);
      hmse->SetBinContent(i, j, mse);
    }
  }
}
double GetPullPerformance(TH2 *hpull, double sigma)
{
  double percent;
  int num = 0;
  int denom = 0;
  for (int i = 1; i < hpull->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < hpull->GetNbinsY() + 1; j++)
    {
      // double err = hvals->GetBinError(i, j);
      double content = hpull->GetBinContent(i, j);
      if (content == 0)
        continue;
      if (fabs(content) < sigma)
        num++;
      denom++;
    }
  }
  percent = (double)num / (double)denom * 100;
  return percent;
}
double GetMSEPerformance(TH2 *hmse)
{
  double avg;
  double sum = 0;
  int denom = 0;
  for (int i = 1; i < hmse->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < hmse->GetNbinsY() + 1; j++)
    {
      // double err = hvals->GetBinError(i, j);
      double content = hmse->GetBinContent(i, j);
      if (content == 0)
        continue;
      sum += content;
      denom++;
    }
  }
  avg = sum / (double)denom;
  return sqrt(avg);
}

void SetDataStyle(TH1 *h, double markersize = 1.)
{
  if (h == NULL)
    return;
  h->SetMarkerStyle(20);
  h->SetMarkerColor(kBlack);
  h->SetLineColor(kBlack);
  h->SetMarkerSize(markersize);
}
void SetRecoStyle(TH1 *h, double markersize = 1.)
{
  if (h == NULL)
    return;
  h->SetMarkerStyle(kFullSquare);
  h->SetMarkerColor(kBlue);
  h->SetLineColor(kBlue);
  h->SetMarkerSize(markersize);
}
void SetTruthStyle(TH1 *h, double markersize = 1.)
{
  if (h == NULL)
    return;
  h->SetMarkerStyle(kFullDiamond);
  h->SetMarkerColor(kAzure-3);
  h->SetLineColor(kAzure-3);
  h->SetMarkerSize(markersize);
}
void SubtractUnity(TH2D *h2)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      // double err = hvals->GetBinError(i, j);
      if (h2->GetBinContent(i, j) != 0.)
      {
        h2->SetBinContent(i, j, h2->GetBinContent(i, j) - 1.);
      }
    }
  }
}

void SubtractUnity(TH1D *h1)
{
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    // double err = hvals->GetBinError(i, j);
    if (h1->GetBinContent(i) != 0.)
    {
      h1->SetBinContent(i, h1->GetBinContent(i) - 1.);
    }
  }
}

double GetWeightedAverage(TH2D *h2)
{
  double sumWeights = 0.;
  double num = 0.;
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      double weight = 1. / h2->GetBinError(i, j);
      double val = fabs(h2->GetBinContent(i, j) - 1.);
      if (val == 1.)
        continue;
      num += val * weight;
      sumWeights += weight;
    }
  }
  double result = num / sumWeights;
  return result;
}

double GetWeightedAverage(TH1D *h1)
{
  double sumWeights = 0.;
  double num = 0.;
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    double weight = 1. / h1->GetBinError(i);
    double val = fabs(h1->GetBinContent(i) - 1.);
    if (val == 1.)
      continue;
    num += val * weight;
    sumWeights += weight;
  }
  double result = num / sumWeights;
  return result;
}


double GetWeightedAverage(TH2D *h2, TH2D *h2_weight)
{
  double sumWeights = 0.;
  double num = 0.;
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      double val = fabs(h2->GetBinContent(i, j));
      double weight = h2_weight->GetBinContent(i, j) / h2_weight->GetBinError(i, j);
      if (val == 100.)
        continue;
      // cout<<"("<<val<<","<<weight<<")";
      num += val * weight;
      sumWeights += weight;
    }
  }
  double result = num / sumWeights;
  return result;
}

void GetErrorHist(TH2 *h2, TH2 *h2_err)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      double err = h2->GetBinError(i, j);
      h2_err->SetBinContent(i, j, err);
    }
  }
}

void SetHistConst(TH2 *h2, double val)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      h2->SetBinContent(i, j, val);
    }
  }
}
void SetHistConst(TH1 *h1, double val)
{
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    h1->SetBinContent(i, val);
  }
}
void SetHistError(TH2 *h2, TH2 *h2_err)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      h2->SetBinError(i, j, h2_err->GetBinContent(i, j) * h2->GetBinContent(i, j));
    }
  }
}
void SetHistError(TH1 *h1, TH1 *h1_err)
{
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    h1->SetBinError(i, h1_err->GetBinContent(i) * h1->GetBinContent(i));
  }
}
void SetHistErrorZero(TH2 *h2)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      h2->SetBinError(i, j, 0.);
    }
  }
}
void SetHistErrorZero(TH1 *h1)
{
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    h1->SetBinError(i, 0.);
  }
}

void SetHistErrCorr(TH2 *hist, TH2 *hist1, TH2 *hist2, double corr = 0.)
{
  for (int i = 1; i < hist->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < hist->GetNbinsY() + 1; j++)
    {
      double err1 = hist1->GetBinError(i, j);
      double err2 = hist2->GetBinError(i, j);
      hist->SetBinError(i, j, sqrt(err1 * err1 + err2 * err2 - 2 * corr * err1 * err2));
    }
  }
}

void SetHistErrCorr(TH1 *hist, TH1 *hist1, TH1 *hist2, double corr = 0.)
{
  for (int i = 1; i < hist->GetNbinsX() + 1; i++)
  {
    double err1 = hist1->GetBinError(i);
    double err2 = hist2->GetBinError(i);
    hist->SetBinError(i, sqrt(err1 * err1 + err2 * err2 - 2 * corr * err1 * err2));

  }
}

void GetSqrtHist(TH2 *h2)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      h2->SetBinContent(i, j, sqrt(h2->GetBinContent(i, j)));
    }
  }
}

void GetSqrtHist(TH1 *h1)
{
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    h1->SetBinContent(i, sqrt(h1->GetBinContent(i)));
  }
}

TH2D *GetJetPtCorrectedHist(TH3 *h3, TH1 *h1_jetpt)
{
  vector<TH2D *> proj_z;
  for (int i = 1; i < h3->GetNbinsZ() + 1; i++)
  {
    h3->GetZaxis()->SetRange(i, i);
    cout << h3->GetZaxis()->GetBinLowEdge(i) << ", " << h3->GetZaxis()->GetBinLowEdge(i + 1) << endl;
    if (h3->GetZaxis()->GetBinLowEdge(i) < ptMin - 0.1 || h3->GetZaxis()->GetBinLowEdge(i + 1) > ptMax + 0.1)
      continue;
    TH2D *h2_temp = (TH2D *)h3->Project3D(Form("z%d_yx", i));
    h2_temp->Scale(1. / h1_jetpt->GetBinContent(i));
    // h2_temp->Scale(1.);
    cout << "Correction = " << h1_jetpt->GetBinContent(i) << endl;
    proj_z.push_back(h2_temp);
  }
  TH2D *h2_res = (TH2D *)proj_z[0]->Clone("h2_res");
  for (int i = 1; i < proj_z.size(); i++)
  {
    cout << "Added " << i + 1 << "th histogram" << endl;
    h2_res->Add(proj_z[i]);
  }
  return h2_res;
}

void FixEffHist(TH2 *h2eff, TH2 *h2purity)
{
  for (int i = 1; i < h2eff->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2eff->GetNbinsY() + 1; j++)
    {
      double pur = h2purity->GetBinContent(i, j);
      double eff = h2eff->GetBinContent(i, j);
      if (eff > 1.)
      {
        h2eff->SetBinContent(i, j, 1.);
        h2purity->SetBinContent(i, j, pur / eff);
      }
    }
  }
}

void SetFeldmanErr(TH2 *h2)
{
  TFeldmanCousins tfc(0.68);
  double low, high;
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      double err = h2->GetBinError(i, j);
      double val = h2->GetBinContent(i, j);
      if (val < 40)
      {
        low = tfc.CalculateLowerLimit(val, 0.);
        high = tfc.CalculateUpperLimit(val, 0.);
        h2->SetBinError(i, j, (low + high) / 2.);
      }
      else
      {
        h2->SetBinError(i, j, err);
      }
    }
  }
}

TLorentzVector JEC(TLorentzVector HFjet, double cpf, TH1D *m_jecs[m_jecNPvs][m_jecNEta][m_jecNCpf][m_jecNPhi])
{

  double pt(HFjet.Pt()), eta(HFjet.Eta()), phi(HFjet.Phi());
  int iPvs(m_jecPvs - 1), iEta(0), iCpf(0), iPhi(0);
  double m_jetEcShift = 0;

  phi = abs(abs(phi) - M_PI / 2.0);
  if (iPvs > m_jecNPvs - 1)
    iPvs = m_jecNPvs - 1;
  if (iPvs < 0)
    iPvs = 0;
  if (eta > m_jecLimEta[m_jecNEta])
    eta = m_jecLimEta[m_jecNEta];
  if (cpf > m_jecLimCpf[m_jecNCpf])
    cpf = m_jecLimCpf[m_jecNCpf];
  if (phi > m_jecLimPhi[m_jecNPhi])
    phi = m_jecLimPhi[m_jecNPhi];
  if (pt < m_jecLimPt[0])
    pt = m_jecLimPt[0];
  if (pt > m_jecLimPt[m_jecNPt])
    pt = m_jecLimPt[m_jecNPt];
  while (eta > m_jecLimEta[iEta])
    ++iEta;
  if (iEta > 0)
    --iEta;
  while (cpf > m_jecLimCpf[iCpf])
    ++iCpf;
  if (iCpf > 0)
    --iCpf;
  while (phi > m_jecLimPhi[iPhi])
    ++iPhi;
  if (iPhi > 0)
    --iPhi;
  // cout<<iPvs<<","<<iEta<<","<<iCpf<<","<<iPhi<<endl;
  TH1D *hst = m_jecs[iPvs][iEta][iCpf][iPhi];
  double err(hst->GetBinError(hst->FindBin(pt)));
  double cor(hst->Interpolate(pt) + m_jetEcShift * err);

  return HFjet * cor;
}

void PaintOverflow(TH1 *h)
{
  // This function paint the histogram h with an extra bin for overflows

  const char *name = h->GetName();
  const char *title = h->GetTitle();
  Int_t nx = h->GetNbinsX() + 1;
  Double_t x1 = h->GetBinLowEdge(1);
  Double_t bw = h->GetBinWidth(nx);
  Double_t x2 = h->GetBinLowEdge(nx) + bw;

  // Book a temporary histogram having ab extra bin for overflows
  TH1F *htmp = new TH1F(name, title, nx, x1, x2);

  // Fill the new hitogram including the extra bin for overflows
  for (Int_t i = 1; i <= nx; i++)
  {
    htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
  }

  // Fill the underflows
  htmp->Fill(x1 - 1, h->GetBinContent(0));

  // Restore the number of entries
  htmp->SetEntries(h->GetEntries());

  // Draw the temporary histogram
  htmp->Draw("SAME");
  gPad->SetLogy();
  TText *t = new TText(x2 - bw / 2, h->GetBinContent(nx), "Overflow");
  t->SetTextAngle(90);
  t->SetTextAlign(12);
  t->SetTextSize(0.03);
  ;
  t->Draw("SAME");
}

void SmearObservables(TH3 *h3, TH3 *h3_data, TRandom3 *myRNG)
{
  cout << "Smearing Observables" << endl;
  for (int i = 1; i < h3->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h3->GetNbinsY() + 1; j++)
    {
      for (int k = 1; k < h3->GetNbinsZ() + 1; k++)
      {
        double sigma = h3_data->GetBinError(i, j, k);
        double data_val = h3_data->GetBinContent(i, j, k);
        double rand;
        if (sigma == data_val)
        {
          sigma = sqrt(data_val);
        }
        rand = myRNG->Gaus(1, sigma / data_val);
        rand = (rand < 0) ? 1. : rand;
        double val = h3->GetBinContent(i, j, k);
        if (data_val > 0)
        {
          // cout << sigma << ", " << data_val << ", " << rand << endl;
          h3->SetBinContent(i, j, k, val * rand);
        }
      }
    }
  }
}

void SmearObservables(TH2 *h2, TH2 *h2_data, TRandom3 *myRNG)
{
  cout << "Smearing Observables" << endl;
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {
      double sigma = h2_data->GetBinError(i, j);
      double data_val = h2_data->GetBinContent(i, j);
      double rand;
      if (sigma == data_val)
      {
        sigma = sqrt(data_val);
      }
      rand = myRNG->Gaus(1, sigma / data_val);
      rand = (rand < 0) ? 1. : rand;
      double val = h2->GetBinContent(i, j);
      if (data_val > 0)
      {
        // cout << sigma << ", " << data_val << ", " << rand << endl;
        h2->SetBinContent(i, j, val * rand);
      }
    }
  }
}

void SmearObservables(TH1 *h1, TH1 *h1_data, TRandom3 *myRNG)
{
  cout << "Smearing Observables" << endl;
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {

    double sigma = h1_data->GetBinError(i);
    double data_val = h1_data->GetBinContent(i);
    double rand;
    if (sigma == data_val)
    {
      sigma = sqrt(data_val);
    }
    rand = myRNG->Gaus(1, sigma / data_val);
    rand = (rand < 0) ? 1. : rand;
    double val = h1->GetBinContent(i);
    if (data_val > 0)
    {
      // cout << sigma << ", " << data_val << ", " << rand << endl;
      h1->SetBinContent(i, val * rand);
    }
  }
}

void SmearDtrPt(TLorentzVector &dtr, double charge, double id, TRandom3 *myRNG)
{
  if (fabs(charge) > 0)
  {
    double rand = myRNG->Gaus(1, 0.03);
    dtr.SetPxPyPzE(dtr.Px() * rand,
                   dtr.Py() * rand,
                   dtr.Pz() * rand,
                   dtr.E() * rand);
  }
  else
  {
    // dE/E = a/sqrt(E) + b + c/E
    // a = 10%
    // b = 1%
    // c is small
    double b, a, e;
    if (abs(id) == 22 || abs(id) == 111)
    {
      b = 0.01;
      a = 0.1;
    }
    else
    {
      b = 0.09;
      a = 0.67;
    }

    e = dtr.E();
    double sigma = sqrt(b * b + a / sqrt(e) * a / sqrt(e));
    double rand = myRNG->Gaus(1, sigma);
    dtr.SetPxPyPzE(dtr.Px() * rand,
                   dtr.Py() * rand,
                   dtr.Pz() * rand,
                   dtr.E() * rand);
  }
}
bool DropFSP(double prob, TRandom3 *myUniform)
{
  double rand = myUniform->Uniform(1.);
  if (rand < prob)
    return true;
  else
    return false;
}
bool DropFSPHist(TLorentzVector dtr, TH2 *h2, TRandom3 *myUniform)
{
  double rand = myUniform->Uniform(1.);
  int pbin = h2->GetXaxis()->FindBin(dtr.P());
  int etabin = h2->GetYaxis()->FindBin(dtr.Eta());
  double ratio = h2->GetBinContent(pbin, etabin);
  double prob_trk = fabs(ratio - 1.);
  if (rand < prob_trk)
    return true;
  else
    return false;
}

void MakeHistPositive(TH3 *h3)
{
  for (int i = 1; i < h3->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h3->GetNbinsY() + 1; j++)
    {
      for (int k = 1; k < h3->GetNbinsZ() + 1; k++)
      {
        if (h3->GetBinContent(i, j, k) < 0)
          h3->SetBinContent(i, j, k, 0.);
      }
    }
  }
}
void MakeHistPositive(TH2 *h2)
{
  for (int i = 1; i < h2->GetNbinsX() + 1; i++)
  {
    for (int j = 1; j < h2->GetNbinsY() + 1; j++)
    {

      if (h2->GetBinContent(i, j) < 0)
        h2->SetBinContent(i, j, 0.);
    }
  }
}
void MakeHistPositive(TH1 *h1)
{
  for (int i = 1; i < h1->GetNbinsX() + 1; i++)
  {
    if (h1->GetBinContent(i) < 0)
      h1->SetBinContent(i, 0.);
  }
}

int SampleTH1(TH1D *hist, TRandom3 *randomGenerator)
{
  int numBins = hist->GetNbinsX();
  double cumulativeProbabilities[numBins + 1];

  // Fill the array with cumulative probabilities
  cumulativeProbabilities[0] = 0.0;
  for (int i = 1; i <= numBins; ++i)
  {
    cumulativeProbabilities[i] = cumulativeProbabilities[i - 1] + hist->GetBinContent(i);
  }

  // Generate a random number between 0 and 1
  // TRandom3 randomGenerator;

  double randomValue = randomGenerator->Uniform();

  // Find the bin corresponding to the generated random number
  int selectedBin = 0;
  for (int i = 1; i <= numBins; ++i)
  {
    if (randomValue <= cumulativeProbabilities[i])
    {
      selectedBin = i;
      break;
    }
  }

  // Get the interval corresponding to the selected bin
  double binLowEdge = hist->GetXaxis()->GetBinLowEdge(selectedBin);
  double binWidth = hist->GetXaxis()->GetBinWidth(selectedBin);

  double intervalStart = binLowEdge;
  double intervalEnd = binLowEdge + binWidth;

  // Output the result
  // std::cout << "Generated random number: " << randomValue << std::endl;
  // std::cout << "Selected bin: " << selectedBin << std::endl;
  // std::cout << "Corresponding interval: [" << intervalStart << ", " << intervalEnd << "]" << std::endl;

  return selectedBin;
}

// Returns JES + JER scale factor as a function of jet pT (in GeV)
// Values and function provided by Ezra Lesser (thank you!)
double get_JES_JER(const double jet_pt, TRandom3 *myRNG, bool do_sys = false) {
  double jes_var = 1, jer_var = 1;

  // Low-multiplicity (N_consit < 10) fits
  if (do_sys) {
      if      (jet_pt < 10) { jes_var = 0.904; jer_var = 0.006; }
      else if (jet_pt < 12) { jes_var = 0.936; jer_var = 0.180; }
      else if (jet_pt < 15) { jes_var = 0.924; jer_var = 0.264; }
      else if (jet_pt < 17) { jes_var = 0.972; jer_var = 0.192; }
      else if (jet_pt < 20) { jes_var = 0.970; jer_var = 0.100; }
      else if (jet_pt < 25) { jes_var = 0.976; jer_var = 0.114; }
      else if (jet_pt < 35) { jes_var = 0.984; jer_var = 0.036; }
      else if (jet_pt < 50) { jes_var = 1.000; jer_var = 0.144; }
      else                  { jes_var = 1.008; jer_var = 0.126; }
  }

  // Nominal (inclusive Z+jet) fits
  else {
      if      (jet_pt < 10) { jes_var = 0.912; jer_var = 0.006; }
      else if (jet_pt < 12) { jes_var = 0.948; jer_var = 0.132; }
      else if (jet_pt < 15) { jes_var = 0.944; jer_var = 0.192; }
      else if (jet_pt < 17) { jes_var = 0.976; jer_var = 0.114; }
      else if (jet_pt < 20) { jes_var = 0.972; jer_var = 0.096; }
      else if (jet_pt < 25) { jes_var = 0.976; jer_var = 0.138; }
      else if (jet_pt < 35) { jes_var = 0.984; jer_var = 0.054; }
      else if (jet_pt < 50) { jes_var = 1.000; jer_var = 0.144; }
      else                  { jes_var = 1.008; jer_var = 0.120; }
  }

  return jes_var * myRNG->Gaus(1, jer_var);
}



