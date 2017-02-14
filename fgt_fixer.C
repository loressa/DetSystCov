#define fgt_fixer_cxx
#include "fgt_fixer.h"

#include "string.h"

#include <TH2.h>
#include <TMatrixD.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

void fgt_fixer::Loop()
{
  if (fChain == 0) return;

  TFile * f = new TFile("fgt_events_nu.root","RECREATE");
  f->cd();
  TTree * out_tree = new TTree("dune_dst","dune_dst");

  //  out_tree->Branch("sample"        ,&out_sample        ,"sample/I"      );
  //out_tree->Branch("reactionmode"  ,&out_reactionmode  ,"reactionmode/I");
  //out_tree->Branch("y_true", &out_y_true, "y_true/F");
  
  Int_t           out_trueFSParticles;
  Int_t           out_trueFSParticles_pdg[kMaxtrueFSParticles];   //[trueFSParticles_]                                          
  Int_t           out_trueFSParticles_id[kMaxtrueFSParticles];   //[trueFSParticles_]                                             
  Float_t         out_trueFSParticles_energy[kMaxtrueFSParticles];   //[trueFSParticles_]    

  Int_t           out_recoFSParticles;
  Int_t           out_recoFSParticles_pdg[kMaxrecoFSParticles];   //[recoFSParticles_]                                          
  Int_t           out_recoFSParticles_id[kMaxrecoFSParticles];   //[recoFSParticles_]                                             
  Float_t         out_recoFSParticles_energy[kMaxrecoFSParticles];   //[trueFSParticles_]    

  Int_t           out_sample_reco;
  Int_t           out_reaction_reco;
  Float_t         out_Ev_reco;
  Float_t         out_y_reco;

  out_tree->Branch("trueFSParticles", &out_trueFSParticles, "trueFSParticles/I");
  out_tree->Branch("trueFSParticles.pdg", out_trueFSParticles_pdg, "trueFSParticles.pdg[trueFSParticles]/I");//!
  out_tree->Branch("trueFSParticles.id", out_trueFSParticles_id, "trueFSParticles.id[trueFSParticles]/I");//!
  out_tree->Branch("trueFSParticles.energy", out_trueFSParticles_energy, "trueFSParticles.energy[trueFSParticles]/F");//!

 out_tree->Branch("sample_reco"        ,&out_sample_reco       ,"sample_reco/I"      );
 out_tree->Branch("reaction_reco"  ,&out_reaction_reco ,"reaction_reco/I");
 out_tree->Branch("Ev_reco"       ,&out_Ev_reco       ,"Ev_reco/F"     );
 out_tree->Branch("y_reco"        ,&out_y_reco        ,"y_reco/F"      );

 out_tree->Branch("recoFSParticles", &out_recoFSParticles, "recoFSParticles/I");
 out_tree->Branch("recoFSParticles.pdg", out_recoFSParticles_pdg, "recoFSParticles.pdg[recoFSParticles]/I");//!
 out_tree->Branch("recoFSParticles.id", out_recoFSParticles_id, "recoFSParticles.id[recoFSParticles]/I");//!
 out_tree->Branch("recoFSParticles.energy", out_recoFSParticles_energy, "recoFSParticles.energy[recoFSParticles]/F");//!

  TH1D* wgt = new TH1D("wgt","wgt", 80, -5, 3);

  //Number of input entries (i.e. events)
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  std::cout << "nentries = " << nentries << std::endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    if(jentry%1000==0) 
      cout<<"On event "<<jentry<<" of "<<nentries<<endl;

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if((recoFSParticles>kMaxrecoFSParticles)||(trueFSParticles>kMaxtrueFSParticles)) continue;
    
    //Now store for the output tree
    out_Ev_reco      = Ev_reco;
    out_y_reco       = y_reco;
    out_sample_reco  = sample_reco;
    out_reaction_reco = reaction_reco;

    out_recoFSParticles = recoFSParticles;

    for(int k = 0; k <recoFSParticles; k++)
      {
	out_recoFSParticles_pdg[k] = recoFSParticles_pdg[k];
	out_recoFSParticles_id[k] = recoFSParticles_id[k];
	out_recoFSParticles_energy[k] = recoFSParticles_energy[k];
      }

    out_trueFSParticles = trueFSParticles;

    for(int k = 0; k < trueFSParticles; k++)
      {
	out_trueFSParticles_pdg[k] = trueFSParticles_pdg[k];
	out_trueFSParticles_id[k] = trueFSParticles_id[k];
	out_trueFSParticles_energy[k] = trueFSParticles_energy[k];
      }
       

    //FGT weight calculation
    int FGTweight(-1);
    // Chris's FGT target function starts here

    // For two types of interactions we will use the STT events                                                                       
    bool neutrino_electron_scattering = ( sample_reco == 25 );
    bool nu_e_CC = ( sample_reco >= 17 && sample_reco <= 20 ); // 4 different nu_e CC modes
    
    // Figure out if the reco interaction vertex is in one of the filled target modules                                             
    bool targetModule = ( (recoVtxZ > 260.608 && recoVtxZ < 261.309) || // Ca target (no enclosure simulated)           
                          (recoVtxZ > 267.508 && recoVtxZ < 272.792) || // Filled Ar 1 (including C tube)                
                          (recoVtxZ > 278.991 && recoVtxZ < 284.275) || // Filled Ar 2 (including C tube)                 
                          (recoVtxZ > 290.474 && recoVtxZ < 295.759) ); // Filled Ar 3 (including C tube)  

    // or in the empty target module                                                                       
    bool emptyTargetModule = (recoVtxZ > 301.917 && recoVtxZ < 307.202); // C tube filled with air 
    
    // or in the STT; we will not use events just downstream of the target region, or in the tubes between target modules           
    bool STT = (recoVtxZ > 315.25); // downstream boundary already enforced in FGT code 
    
    // true target nucleus A                                                                                                   
    int tgtA = (target%10000)/10; // 10LZZZAAAI is nucleus, %10000 pulls off AAAI, integer division by 10 strips last digit

    // If it's nu-e scattering or nu_e CC, then keep the events iff they are in the STT                                         
    if( neutrino_electron_scattering || nu_e_CC ) {
      if( STT ) FGTweight=1;
      else FGTweight=0; // don't use event in VALOR                                                                                 
    }
    else{
      // For nu_mu CC, and NC of any flavor: keep only target module events                                                        
      // For 2+ tracks, we get vertex resoution ~100 microns, assume perfect and keep true 40Ar and 40Ca only, with no subtraction  
      // For 1 track, we only know the event happened somewhere in the target module                                                   
      // subtract the empty module, with a factor of 3 because there are 3 filled modules to subtract                                 
      // this neglects z-dependent acceptance effects, if there are any                                                             
      // NC pi0 we probably don't have good enough direction resolution on the photons to get a great vertex                         
      // but let's assume we can get it to within the target module, and treat it like a 1-track event                                
      
      // isFound == true for reconstructed particles, but photons and pi0s will not have tracks                                       
      int ntracks = 0;
      int npi0 = 0;
      for( int ip = 0 ; ip < recoFSParticles ; ip++ ) {
	int pdg = recoFSParticles_pdg[ip];
	if( /*p.isFound && */ pdg != 22 && pdg != 111 ) ntracks++;
	if( /*p.isFound && */ pdg == 111 ) npi0++;
      }
      
      
      if( ntracks >= 2 ) {
	if( targetModule && tgtA == 40 ) FGTweight=1;
	else FGTweight=0; // don't use event in VALOR
      }
      else{
	
	if( ntracks == 1 || npi0 >= 1 ) {
	  if( targetModule ) FGTweight=1;
	  else if( emptyTargetModule ) FGTweight=-3;
	  else FGTweight=0;
	}
	else{
	  // if there are particles, but no tracks and no pi0s then we have single gammas and we will have no vertex resolution so throw 
	  if( recoFSParticles ) FGTweight=0;
	  
	  // Also can have 0 reconstructed particles                                                                                 
	  // These are events that are not reconstructed, and they will have an undefined sample code                                  
	  // We want to keep them to study how often the various event categories fail to be reconstructed at all                      
	  // But if we only keep Ca or Ar target events, then we only want to know how often this happens for true target events         
	  else{
	    if( targetModule && tgtA == 40 ) FGTweight=1;
	    else FGTweight=0;
	  }
	}
      }
    }
  
    //Fill tree only if weight is 1
    if(FGTweight==1)
      out_tree->Fill();
    
    wgt->Fill(FGTweight);

  }

  out_tree->Write();
  cout<<"Written "<<out_tree->GetEntries()<<" events"<<endl;
  wgt->Write();
  f->Close();
  
}









