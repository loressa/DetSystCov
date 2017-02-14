#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TArrayF.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TChain.h>
#include <TChainElement.h>

void make_cov_matrix()
{

  const int n_files = 1000;
  const int tweaks_per_file = 10;
  const int n_tweaks = n_files*tweaks_per_file;
  const int n_bins_init = 314;
  const int n_bins_final = 310; //removing IMD and e-nu for the moment

  TMatrixD vec_total(n_bins_init,n_tweaks);
  TVectorD nom(n_bins_init);
  TVectorD mean(n_bins_init);

  TFile * total_vector_file = TFile::Open("total_det_syst_vector.root");
  total_vector_file.cd();
  for (int i = 0; i<n_bins_init; i++)
    {
      for(int j=0; j<n_tweaks; j++)
	vec_total(i,j)=total_vector(i,j);
    }  
  
  TMatrixD cov(n_bins_init,n_bins_init);
  TMatrixD frac_cov(n_bins_init,n_bins_init);
  TMatrixD cor(n_bins_init,n_bins_init);

  TMatrixD cov_final(n_bins_final,n_bins_final);
  TMatrixD frac_cov_final(n_bins_final,n_bins_final);
  TMatrixD cor_final(n_bins_final,n_bins_final);

  //calculate mean vector   
  for (int i =0; i<n_bins_init; i++){
    double x = 0;
    for (int k =0; k<n_tweaks; k++){
      x+=vec_total[i][k];
    }
    mean[i]=x/n_tweaks;
  }
  //  mean.Print();


  //initialization
  for (int i =0; i<n_bins_init; i++){
    for (int j =0; j<n_bins_init; j++){
      cov[i][j]=0;
      frac_cov[i][j]=0;
      cor[i][j]=0;
    }
  }

  
  //covariance matrix
  for (int i =0; i<n_bins_init; i++){
    for (int j =0; j<n_bins_init; j++){
      double entry = 0;
      for (int l =0; l<n_tweaks; l++){
        double x = vec_total[i][l]-mean[i];
        double y = vec_total[j][l]-mean[j];
        entry+=x*y;
      }
      if((mean[i]!=0) && (mean[j])!=0)
	{
	  cov[i][j]=entry/n_tweaks;
	  frac_cov[i][j]=cov[i][j]/(mean[i]*mean[j]);
	}
    }
  }

  
  //correlation matrices                                                                                                    
  for (int i =0; i<n_bins_init; i++){
    for (int j =0; j<n_bins_init; j++){
      if(cov[i][i]*cov[j][j]!=0)
        cor[i][j]=cov[i][j]/sqrt(cov[i][i]*cov[j][j]);
    }
  }
  
  //final matrices, same but dropping IMD and e-nu 
  for (int i =0; i<n_bins_init-2; i++){
    for (int j =0; j<n_bins_init-2; j++){
      int i_matrix = 0, j_matrix = 0;
      if(i<155) i_matrix = i;
      else i_matrix = i-2;
      if(j<155) j_matrix = j;
      else j_matrix = j-2;
      if((i!=155) && (i!=156) && (j!=155) && (j!=156))
	{
	  cov_final[i_matrix][j_matrix]=cov[i][j];
	  frac_cov_final[i_matrix][j_matrix]=frac_cov[i][j];
	  cor_final[i_matrix][j_matrix]=cor[i][j];
	}
    }
  }

  //write out
  TFile * cov_file = new TFile("mean_fgt.root","RECREATE");
  cov_file->cd(); 
  mean.Write("mean");
  cov_file->Close();
  cor.Write("cor");
  
  cov_final.Write("cov");
  frac_cov_final.Write("frac_cov");
  cor_final.Write("cor");
  cov_file->Close();

}
