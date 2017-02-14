
#include "DetSystRWtool.h"


using namespace std;


DetSystRWtool::DetSystRWtool(int mySeed){

  rand = new TRandom3();
  rand->SetSeed(mySeed);
  nu_mode = true;

} 
    
void DetSystRWtool::Initialize_Detector(double Eel_sigma, double err_Eel_sigma, double err_Eel_mu, double err_el_eff, double Eel_eff_min, double Eel_eff_max,
                                        double Emu_sigma, double err_Emu_sigma, double err_Emu_mu, double err_mu_eff, double Emu_eff_min, double Emu_eff_max,
                                        double Ehad_sigma, double err_Ehad_sigma, double err_Ehad_mu, 
                                        double err_p_eff, double Ep_eff_min, double Ep_eff_max,
                                        double err_pic_eff, double Epic_eff_min, double Epic_eff_max,
                                        double err_pi0_eff, double Epi0_eff_min, double Epi0_eff_max){

  Sigma_el      = Eel_sigma;
  ErrSigma_el   = err_Eel_sigma;
  ErrMu_el      = err_Eel_mu;

  Sigma_mu      = Emu_sigma;
  ErrSigma_mu   = err_Emu_sigma;
  ErrMu_mu      = err_Emu_mu;

  Sigma_had     = Ehad_sigma;
  ErrSigma_had  = err_Ehad_sigma;
  ErrMu_had     = err_Ehad_mu;

  EffEmin_el    = Eel_eff_min;
  EffEmax_el    = Eel_eff_max;
  MaxEff_el     = err_el_eff;

  EffEmin_mu    = Emu_eff_min;
  EffEmax_mu    = Emu_eff_max;
  MaxEff_mu     = err_mu_eff;

  EffEmin_p     = Ep_eff_min;
  EffEmax_p     = Ep_eff_max;
  MaxEff_p      = err_p_eff;

  EffEmin_pic   = Epic_eff_min;
  EffEmax_pic   = Epic_eff_max;
  MaxEff_pic    = err_pic_eff;

  EffEmin_pi0   = Epi0_eff_min;
  EffEmax_pi0   = Epi0_eff_max;
  MaxEff_pi0    = err_pi0_eff;


}

void DetSystRWtool::Initialize_Det_electron(double E_sigma, double err_E_sigma, double err_E_mu, double err_eff, double E_eff_min, double E_eff_max){

  Sigma_el      = E_sigma;
  ErrSigma_el   = err_E_sigma;
  ErrMu_el      = err_E_mu;

  EffEmin_el    = E_eff_min;
  EffEmax_el    = E_eff_max;
  MaxEff_el     = err_eff;

}

void DetSystRWtool::Initialize_Det_muon(double E_sigma, double err_E_sigma, double err_E_mu, double err_eff, double E_eff_min, double E_eff_max){

  Sigma_mu      = E_sigma;
  ErrSigma_mu   = err_E_sigma;
  ErrMu_mu      = err_E_mu;

  EffEmin_mu    = E_eff_min;
  EffEmax_mu    = E_eff_max;
  MaxEff_mu     = err_eff;

}

void DetSystRWtool::Initialize_Det_hadrons(double E_sigma, double err_E_sigma, double err_E_mu, 
                                           double err_p_eff, double Ep_eff_min, double Ep_eff_max,
                                           double err_pic_eff, double Epic_eff_min, double Epic_eff_max,
                                           double err_pi0_eff, double Epi0_eff_min, double Epi0_eff_max){

  Sigma_had     = E_sigma;
  ErrSigma_had  = err_E_sigma;
  ErrMu_had     = err_E_mu;

  EffEmin_p     = Ep_eff_min;
  EffEmax_p     = Ep_eff_max;
  MaxEff_p      = err_p_eff;

  EffEmin_pic   = Epic_eff_min;
  EffEmax_pic   = Epic_eff_max;
  MaxEff_pic    = err_pic_eff;

  EffEmin_pi0   = Epi0_eff_min;
  EffEmax_pi0   = Epi0_eff_max;
  MaxEff_pi0    = err_pi0_eff;

}

void DetSystRWtool::SetRandomThrow(){
  
  DelSigma_el   = rand->Gaus(1.0, ErrSigma_el);
  DelMu_el      = rand->Gaus(0.0, ErrMu_el);
  DelSigma_mu   = rand->Gaus(1.0, ErrSigma_mu);
  DelMu_mu      = rand->Gaus(0.0, ErrMu_mu);
  DelSigma_had  = rand->Gaus(1.0, ErrSigma_had);
  DelMu_had     = rand->Gaus(0.0, ErrMu_had);

  DelEff_el     = rand->Rndm()*2-1.0;//0.0, MaxEff_el);
  DelEff_mu     = rand->Rndm()*2-1.0;//0.0, MaxEff_mu);
  DelEff_p      = rand->Rndm()*2-1.0;//0.0, MaxEff_p);
  DelEff_pic    = rand->Rndm()*2-1.0;//0.0, MaxEff_pic);
  DelEff_pi0    = rand->Rndm()*2-1.0;//0.0, MaxEff_pi0);

  if(DelEff_el >0.0) DelEff_el *MaxEff_el;
  if(DelEff_mu >0.0) DelEff_mu *MaxEff_mu;
  if(DelEff_p  >0.0) DelEff_p  *MaxEff_p;
  if(DelEff_pic>0.0) DelEff_pic*MaxEff_pic;
  if(DelEff_pi0>0.0) DelEff_pi0*MaxEff_pi0;


  cout<<"Set Throw:"<<endl;
  cout<<"  DelSigma_el = "<<DelSigma_el<<endl;
  cout<<"  DelMu_el = "<<DelMu_el<<endl;
  cout<<"  DelSigma_mu = "<<DelSigma_mu<<endl;
  cout<<"  DelMu_mu = "<<DelMu_mu<<endl;
  cout<<"  DelSigma_had = "<<DelSigma_had<<endl;
  cout<<"  DelMu_had = "<<DelMu_had<<endl;
  cout<<"  DelEff_el = "<<DelEff_el<<endl;
  cout<<"  DelEff_mu = "<<DelEff_mu<<endl;
  cout<<"  DelEff_p = "<<DelEff_p<<endl;
  cout<<"  DelEff_pic = "<<DelEff_pic<<endl;
  cout<<"  DelEff_pi0 = "<<DelEff_pi0<<endl;

}

void DetSystRWtool::SetThrow(double del_sigma_el, double del_mu_el, double del_sigma_mu, double del_mu_mu, double del_sigma_had, double del_mu_had, 
                             double del_eff_el, double del_eff_mu, double del_eff_p, double del_eff_pic, double del_eff_pi0){

  DelSigma_el   = del_sigma_el*Sigma_el;
  DelMu_el      = del_mu_el;
  DelSigma_mu   = del_sigma_mu*Sigma_mu;
  DelMu_mu      = del_mu_mu;
  DelSigma_had  = del_sigma_had*Sigma_had;
  DelMu_had     = del_mu_had;

  DelEff_el     = del_eff_el;
  DelEff_mu     = del_eff_mu;
  DelEff_p      = del_eff_p;
  DelEff_pic    = del_eff_pic;
  DelEff_pi0    = del_eff_pi0;

}

void DetSystRWtool::SetEvent(int sample, int lep_pdg, double Etrue_lep, double Ereco_lep, 
                             double Etrue_had, double Ereco_had,
                             vector<int> pdg_reco, vector<int> pdg_true, vector<double> Etrue){

  double Emin = 1.0e-3;

  if(Ereco_lep>0.0){
    if(TMath::Abs(lep_pdg) == 13){
      
      Elep_new = (Ereco_lep - Etrue_lep)*DelSigma_el + Etrue_lep + DelMu_el;

    }else if(TMath::Abs(lep_pdg) == 11){

      Elep_new = (Ereco_lep - Etrue_lep)*DelSigma_mu + Etrue_lep + DelMu_mu;

    }else if(lep_pdg==0){
    
      Elep_new = 0.0;

    }else{

      cout<<"Unkown lepton pdg code ... Exiting ..."<<endl;
      exit(1);

    }
    if(Elep_new<=0.0) Elep_new = Emin;
  }else{
    Elep_new = 0.0;
  }

  if(Ereco_had>0.0){
    Ehad_new = (Ereco_had - Etrue_had)*DelSigma_had + Etrue_had + DelMu_had;
    if(Ehad_new<=0.0) Ehad_new = Emin;
  }else{
    Ehad_new = 0.0;
  }

  E_new = Elep_new + Ehad_new;

  y_new = 0.0;
  if(E_new>0.0) y_new = Ehad_new/E_new;

//cout<<"DelSigma_mu = "<<DelSigma_mu<<" DelMu_mu = "<<DelMu_mu<<" DelSigma_had = "<<DelSigma_had<<" DelMu_had = "<<DelMu_had<<endl;
//cout<<"Etrue_lep = "<<Etrue_lep<<" Ereco_lep = "<<Ereco_lep<<" Etrue_had = "<<Etrue_had<<" Ereco_had = "<<Ereco_had<<endl;

  if(pdg_reco.size() != pdg_true.size() || Etrue.size() != pdg_true.size()){
    cout<<"Vector sizes for true particles do not match ... Exiting ..."<<endl;
    //Etrue.resize(Ereco.size());
    exit(1);
  }

  int n_mum = 0;
  int n_mup = 0; //wrong sign muons 
  int n_el  = 0;
  int n_elp = 0; //wrong sign electrons   
  int n_p   = 0;
  int n_pic = 0;
  int n_pi0 = 0;
  int n_oth = 0;
  EffWeight = 1.0;

  for(int i=0; i<Etrue.size(); i++){
/*
cout<<"Start:"<<endl;
cout<<"  pdg_reco[i] = "<<pdg_reco[i]<<" pdg_true[i] = "<<pdg_true[i]<<endl;
cout<<"  Etrue[i] = "<<Etrue[i]<<" EffEmin_p = "<<EffEmin_p<<" EffEmax_p = "<<EffEmax_p<<" DelEff_p = "<<DelEff_p<<endl;
cout<<"    n_mum = "<<n_mum<<endl;
cout<<"    n_mup = "<<n_mup<<endl;
cout<<"    n_p   = "<<n_p<<endl;
cout<<"    n_pic = "<<n_pic<<endl;
cout<<"    n_pi0 = "<<n_pi0<<endl;
cout<<"    n_el  = "<<n_el<<endl;
cout<<"    n_oth = "<<n_oth<<endl;
*/
    if(pdg_reco[i]==0){
      //If the particle is not reco'd and is in the `threshold region' then we dicide if we wnat to keep it
      //If the particle was not recoed, and the efficiency is increased, then we keep some fraction of them
      //And assign them their true PID
      if(     TMath::Abs(pdg_true[i])==13   && (DelEff_mu  <= 0.0 || Etrue[i] < EffEmin_mu  || Etrue[i] > EffEmax_mu))  continue;
      else if(           pdg_true[i]==2212  && (DelEff_p   <= 0.0 || Etrue[i] < EffEmin_p   || Etrue[i] > EffEmax_p))   continue;
      else if(TMath::Abs(pdg_true[i])==211  && (DelEff_pic <= 0.0 || Etrue[i] < EffEmin_pic || Etrue[i] > EffEmax_pic)) continue;
      else if(TMath::Abs(pdg_true[i])==111  && (DelEff_pi0 <= 0.0 || Etrue[i] < EffEmin_pi0 || Etrue[i] > EffEmax_pi0)) continue;
      else if(TMath::Abs(pdg_true[i])==11   && (DelEff_el  <= 0.0 || Etrue[i] < EffEmin_el  || Etrue[i] > EffEmax_el))  continue;
      else if(!(TMath::Abs(pdg_true[i])==13 || TMath::Abs(pdg_true[i])==2212 || TMath::Abs(pdg_true[i])==211 ||
                TMath::Abs(pdg_true[i])==111  || TMath::Abs(pdg_true[i])==11)) continue;
      
      double rn = rand->Rndm();
      //cout<<" rn = "<<rn<<" DelEff_p = "<<TMath::Abs(DelEff_p)<<" pdg_true["<<i<<"] = "<<pdg_true[i]<<endl;
      if(                pdg_true[i]==13   && rn<TMath::Abs(DelEff_mu))  n_mum++;
      else if(           pdg_true[i]==-13  && rn<TMath::Abs(DelEff_mu))  n_mup++;
      else if(           pdg_true[i]==2212 && rn<TMath::Abs(DelEff_p))   n_p++;
      else if(TMath::Abs(pdg_true[i])==211 && rn<TMath::Abs(DelEff_pic)) n_pic++;
      else if(TMath::Abs(pdg_true[i])==111 && rn<TMath::Abs(DelEff_pi0)) n_pi0++;
      else if((pdg_true[i])==11  && rn<TMath::Abs(DelEff_el))  n_el++;
      else if((pdg_true[i])==-11  && rn<TMath::Abs(DelEff_el))  n_elp++;

    }else if(pdg_reco[i]==13){
      //We have a reco particle
      n_mum++;
      //If the particle is above or below the `threshold region' then we move on.
      if(DelEff_mu >= 0.0) continue;
      if(Etrue[i] < EffEmin_mu) continue;
      if(Etrue[i] > EffEmax_mu) continue;
      //If the particle is reco'd and in the `threshold region' then we dicide if we want to keep it
      //If the particle was recoed and the eff change is negative we remove some farction of them ... 
      if(rand->Rndm()<TMath::Abs(DelEff_mu)) n_mum--;
      //Or we just give it a weight ... but I don't think this makes sense ... 
      EffWeight *= DelEff_mu;
      //same comments for the rest of the pdg lists
    }else if(pdg_reco[i]==-13){
      //Only care about muon sign
      n_mup++;
      if(DelEff_mu >= 0.0) continue;
      if(Etrue[i] < EffEmin_mu) continue;
      if(Etrue[i] > EffEmax_mu) continue;
      if(rand->Rndm()<TMath::Abs(DelEff_mu)) n_mup--;
      EffWeight *= DelEff_mu;
    }else if(pdg_reco[i]==2212){
      n_p++;
      if(DelEff_p >= 0.0) continue;
      if(Etrue[i] < EffEmin_p) continue;
      if(Etrue[i] > EffEmax_p) continue;
      if(rand->Rndm()<TMath::Abs(DelEff_p)) n_p--;
      EffWeight *= DelEff_p;
    }else if(TMath::Abs(pdg_reco[i])==211){
      n_pic++;
      if(DelEff_pic >= 0.0) continue;
      if(Etrue[i] < EffEmin_pic) continue;
      if(Etrue[i] > EffEmax_pic) continue;
      if(rand->Rndm()<TMath::Abs(DelEff_pic)) n_pic--;
      EffWeight *= DelEff_pic;
    }else if(pdg_reco[i]==111){
      n_pi0++;
      if(DelEff_pi0 >= 0.0) continue;
      if(Etrue[i] < EffEmin_pi0) continue;
      if(Etrue[i] > EffEmax_pi0) continue;
      if(rand->Rndm()<TMath::Abs(DelEff_pi0)) n_pi0--;
      EffWeight *= DelEff_pi0;
    }else if((pdg_reco[i])==11){
      n_el++;
      if(DelEff_el >= 0.0) continue;
      if(Etrue[i] < EffEmin_el) continue;
      if(Etrue[i] > EffEmax_el) continue;
      if(rand->Rndm()<TMath::Abs(DelEff_el)) n_el--;
      EffWeight *= DelEff_el;
    }else if((pdg_reco[i])==-11){
      n_elp++;
      if(DelEff_el >= 0.0) continue;
      if(Etrue[i] < EffEmin_el) continue;
      if(Etrue[i] > EffEmax_el) continue;
      if(rand->Rndm()<TMath::Abs(DelEff_el)) n_elp--;
      EffWeight *= DelEff_el;
    }else{
      //nothing fancy for particles we do not explicitly use to define samples, but track them 
      n_oth++;
    }
/*
cout<<"End:"<<endl;
cout<<"  pdg_reco[i] = "<<pdg_reco[i]<<" pdg_true[i] = "<<pdg_true[i]<<endl;
cout<<"  Etrue[i] = "<<Etrue[i]<<" EffEmin_mu = "<<EffEmin_mu<<" EffEmax_mu = "<<EffEmax_mu<<endl;
cout<<"    n_mum = "<<n_mum<<endl;
cout<<"    n_mup = "<<n_mup<<endl;
cout<<"    n_p   = "<<n_p<<endl;
cout<<"    n_pic = "<<n_pic<<endl;
cout<<"    n_pi0 = "<<n_pi0<<endl;
cout<<"    n_el  = "<<n_el<<endl;
cout<<"    n_oth = "<<n_oth<<"\n"<<endl;
*/
  }

  //Make sure we did not give ourselves too many leptons
  //Put extra electrons in oth (as gammas), and extra muons in pic
  if(n_mum + n_mup + n_el > 1){
    if(n_el>0 && (n_mum + n_mup)>0){
      n_oth += n_el - 1;
      n_el = 1;
      n_pic += n_mum + n_mup;
      n_mum = 0;
      n_mup = 0;
    }else if(n_el>0){
      n_oth += n_el - 1;
      n_el = 1;
    }else if(n_mum + n_mup > 0){
      n_pic += n_mum + n_mup - 1;
      n_mum = 1;
      n_mup = 0;
    }
  } 
  int n_lep = n_el + n_elp + n_mum + n_mup;
  //flip muon signs around for anu mode
  if(!nu_mode){
    int n_hold = n_mum;
    n_mum = n_mup;
    n_mup = n_hold;
  }


  sample_new = -1; //if no other cathegory, undefined                                                                             

  //numu CC                                                                                                                       
  if     (n_mum==1 && n_mup==0 && n_p==0 && n_pic==0 && n_pi0==0 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 1;
  else if(n_mum==1 && n_mup==0 && n_p==1 && n_pic==0 && n_pi0==0 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 2;
  else if(n_mum==1 && n_mup==0 && n_p>1  && n_pic==0 && n_pi0==0 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 11;
  else if(n_mum==1 && n_mup==0 && n_p>=0 && n_pic==1 && n_pi0==0 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 3;
  else if(n_mum==1 && n_mup==0 && n_p>=0 && n_pic==0 && n_pi0==1 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 5;
  else if(n_mum==1 && n_mup==0 && n_p>=0 && n_pic==1 && n_pi0==1 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 6;
  else if(n_mum==1)                                               sample_new = 7;
  //numu CC Wrong sign                                                                                                            
  else if(n_mum==0 && n_mup==1 && n_p>=0 && n_pic==0 && n_pi0==0 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 13;
  else if(n_mum==0 && n_mup==1 && n_p>=0 && n_pic==1 && n_pi0==0 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 14;
  else if(n_mum==0 && n_mup==1 && n_p>=0 && n_pic==0 && n_pi0==1 && n_el==0 && n_elp==0 && n_oth==0) sample_new = 15;
  else if(n_mup==1)                                               sample_new = 16;
  //nue CC                                                                                                                        
  else if(n_mum==0 && n_mup==0 && n_p>=0 && n_pic==0 && n_pi0==0 && n_el==1 && n_elp==0 && n_oth==0) sample_new = 17;
  else if(n_mum==0 && n_mup==0 && n_p>=0 && n_pic==1 && n_pi0==0 && n_el==1 && n_elp==0 && n_oth==0) sample_new = 18;
  else if(n_mum==0 && n_mup==0 && n_p>=0 && n_pic==0 && n_pi0==1 && n_el==1 && n_elp==0 && n_oth==0) sample_new = 19;
  else if(n_el==1)                                                sample_new = 20;
  //wrong sign nue CC inclusive                                                                                                   
  else if(n_elp==1)                                               sample_new = 27;

  //NC                                                                            
  else if(n_lep==0  && n_p>=0 && n_pic==0 && n_pi0==0 && n_oth==0) sample_new = 21;
  else if(n_lep==0  && n_p>=0 && n_pic==1 && n_pi0==0 && n_oth==0) sample_new = 22;
  else if(n_lep==0  && n_p>=0 && n_pic==0 && n_pi0==1 && n_oth==0) sample_new = 23;
  else if(n_lep==0)                                                sample_new = 24;

  //specific ones                                                                                                           
  if(n_mum==0 && n_mup==0 && n_p==0 && n_pic==0 && n_pi0==0 && n_el==1 && n_elp==0 && n_oth==0) sample_new = 25;
  // until we have kinematical, Wreco information, leave those samples as they were?                                         
  //  if(n_mum==1 && n_p<=1 && n_pic==1 && n_pi0==0 && n_oth==0) sample_new = 12;                                            
  if(sample==12) sample_new = 12;
  if(sample==26) sample_new = 26;

}

double DetSystRWtool::GetNewEreco(){

  return E_new;

}

double DetSystRWtool::GetNewYreco(){

  return y_new;

}

double DetSystRWtool::GetEffWeight(){

  return EffWeight;

}

double DetSystRWtool::GetNewSample(){

  return sample_new;

}

void DetSystRWtool::SetRandomSeed(int seed){

  rand->SetSeed(seed);  

}

void DetSystRWtool::SetNuMode(bool nu_mode_in){
 
  nu_mode = nu_mode_in;

}
  
bool DetSystRWtool::GetNuMode(){

  return nu_mode;

}


