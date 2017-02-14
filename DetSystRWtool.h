
#ifndef SYSTEMATIC_H
#define SYSTEMATIC_H

#include "TSystem.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TSpline.h"
#include "TRandom3.h"
#include "TMath.h"

#include <array>
#include <vector>
#include <string>
#include <iostream>


using namespace std;

class DetSystRWtool{

  public:

    DetSystRWtool(int mySeed); 
   
    void Initialize_Detector(double Eel_sigma, double err_Eel_sigma, double err_Eel_mu, double err_el_eff, double Eel_eff_min, double Eel_eff_max,
                             double Emu_sigma, double err_Emu_sigma, double err_Emu_mu, double err_mu_eff, double Emu_eff_min, double Emu_eff_max,
                             double Ehad_sigma, double err_Ehad_sigma, double err_Ehad_mu,
                             double err_p_eff, double Ep_eff_min, double Ep_eff_max,
                             double err_pic_eff, double Epic_eff_min, double Epic_eff_max,
                             double err_pi0_eff, double Epi0_eff_min, double Epi0_eff_max);

    void Initialize_Det_electron(double E_sigma, double err_E_sigma, double err_E_mu, double err_eff, double E_eff_min, double E_eff_max);
    void Initialize_Det_muon(double E_sigma, double err_E_sigma, double err_E_mu, double err_eff, double E_eff_min, double E_eff_max);
    void Initialize_Det_hadrons(double E_sigma, double err_E_sigma, double err_E_mu, 
                                double err_p_eff, double Ep_eff_min, double Ep_eff_max,
                                double err_pic_eff, double Epic_eff_min, double Epic_eff_max,
                                double err_pi0_eff, double Epi0_eff_min, double Epi0_eff_max);

    void SetRandomSeed(int seed);
    void SetRandomThrow();
    void SetThrow(double del_sigma_el, double del_mu_el, double del_sigma_mu, double del_mu_mu, double del_sigma_had, double del_mu_had, 
                  double del_eff_el, double del_eff_mu, double del_eff_p, double del_eff_pic, double del_eff_pi0);

    void SetEvent(int sample, int lep_pdg, double Etrue_lep, double Ereco_lep,
                  double Etrue_had, double Ereco_had,
                  vector<int> pdg_reco, vector<int> pdg_true, vector<double> Etrue);

    double GetNewEreco();
    double GetNewYreco();
    double GetEffWeight();
    double GetNewSample();

    void   SetNuMode(bool nu_mode_in);
    bool   GetNuMode();

  private:

    bool   nu_mode;

    double Sigma_el;
    double Sigma_mu;
    double Sigma_had;

    double ErrSigma_el;
    double ErrMu_el;
    double ErrSigma_mu;
    double ErrMu_mu;
    double ErrSigma_had;
    double ErrMu_had;

    double DelSigma_el;
    double DelMu_el;
    double DelSigma_mu;
    double DelMu_mu;
    double DelSigma_had;
    double DelMu_had;


    double EffEmin_el;
    double EffEmax_el;
    double MaxEff_el;

    double EffEmin_mu;
    double EffEmax_mu;
    double MaxEff_mu;

    double EffEmin_p;
    double EffEmax_p;
    double MaxEff_p;

    double EffEmin_pic;
    double EffEmax_pic;
    double MaxEff_pic;

    double EffEmin_pi0;
    double EffEmax_pi0;
    double MaxEff_pi0;

    double DelEff_el;
    double DelEff_mu;
    double DelEff_p;
    double DelEff_pic;
    double DelEff_pi0;


    double E_new;
    double Elep_new;
    double Ehad_new;
    double y_new;
    double EffWeight;
    int sample_new;


    TRandom3* rand;

};

#endif



