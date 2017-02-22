#define dune_dst_cxx
#include "dune_dst.h"

#include "string.h"

#include <TH2.h>
#include <TMatrixD.h>
#include <TMatrixF.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "DetSystRWtool.h"
#include "DetSystRWtool.cxx"

void dune_dst::Loop(int mySeed)
{
  //Array of pairs of min,max bin limits per sample 
  Int_t SampleLimits[27][2]=
    {//Ordered to match sample numbers as they are used inside VALOR
      {0,8}, //numu CC 1 track 0 pi - 1
      {9,17}, //numu CC 2 tracks 0 pi - 2
      {48,56},//numu CC 1 piC - 3
      {-1,-1}, //4
      {57,65},//numu CC 1 pi0 - 5
      {66,74},//numu CC 1piC+1pi0 - 6
      {75,85}, //numu CC other - 7
      {-1,-1},//8
      {-1,-1},//9
      {-1,-1},//10
      {18,32},//numu CC N tracks 0 pi - 11
      {33,47},//numu CC 3 tracks delta - 12
      {86,90}, //numu CC wrong sign 0 pi -13
      {91,98}, //numu CC wrong sign 1piC - 14
      {99,101}, //numu CC wrong sign 1pi0 -15
      {102,102}, //numu CC wrong other -16
      {103,111},//nue CC 0 pi -17
      {112,120}, //nue CC 1 piC -18
      {121,129}, //nue CC 1 pi0 -19
      {130,140}, //nue CC other -20
      {143,145}, //NC 0 pi -21
      {146,148}, //NC 1 piC -22
      {149,151}, //NC 1 pi0 -23
      {152,154}, //NC other -24 
      {155,155}, //e-scattering -25
      {156,156}, //IMD -26
      {141,142}//nue CC wrong sign -27
    };

  //array of pairs of limits in Ereco energy for every bin 
  Float_t ErecoRange[314][2]=
    {                                                                                                                   
      // FHC       
      {  0.0 , 3.0      } , //numu CC 1 track 0 pi, bin 0                                                                    
      {  3.0 , 120.} , //numu CC 1 track 0 pi, bin 1                                                                         
      {  0.0 , 2.0      } , //numu CC 1 track 0 pi, bin 2                                                                    
      {  2.0 , 3.0      } , //numu CC 1 track 0 pi, bin 3                                                                    
      {  3.0 , 5.0      } , //numu CC 1 track 0 pi, bin 4                                                                    
      {  0.0 , 2.0      } , //numu CC 1 track 0 pi, bin 5                                                                    
      {  2.0 , 3.0      } , //numu CC 1 track 0 pi, bin 6                                                                    
      {  3.0 , 5.0      } , //numu CC 1 track 0 pi, bin 7                                                                    
      {  5.0 , 120.} , //numu CC 1 track 0 pi, bin 8 //                                                                      
      {  0.0 , 3.0      } , //numu CC 2 tracks 0 pi, bin 0                                                                   
      {  3.0 , 120.} , //numu CC 2 tracks 0 pi, bin 1                                                                        
      {  0.0 , 2.0      } , //numu CC 2 tracks 0 pi, bin 2                                                                   
      {  2.0 , 3.0      } , //numu CC 2 tracks 0 pi, bin 3                                                                   
      {  3.0 , 5.0      } , //numu CC 2 tracks 0 pi, bin 4                                                                   
      {  0.0 , 2.0      } , //numu CC 2 tracks 0 pi, bin 5                                                                   
      {  2.0 , 3.0      } , //numu CC 2 tracks 0 pi, bin 6                                                                   
      {  3.0 , 5.0      } , //numu CC 2 tracks 0 pi, bin 7                                                                   
      {  5.0 , 120.} , //numu CC 2 tracks 0 pi, bin 8 //                                                                     
      {  0.0 , 3.0      } , //numu CC N tracks 0 pi, bin 0                                                                   
      {  3.0 , 120.} ,  //numu CC N tracks 0 pi, bin 1                                                                       
      {  0.0 , 2.0      } ,  //numu CC N tracks 0 pi, bin 2                                                                  
      {  2.0 , 3.0      } ,  //numu CC N tracks 0 pi, bin 3                                                                  
      {  3.0 , 5.0      } ,  //numu CC N tracks 0 pi, bin 4                                                                  
      {  5.0 , 7.5      } ,  //numu CC N tracks 0 pi, bin 5                                                                  
      {  0.0 , 2.0      } ,  //numu CC N tracks 0 pi, bin 6                                                                  
      {  2.0 , 3.0      } ,  //numu CC N tracks 0 pi, bin 7 
      {  3.0 , 5.0      } ,  //numu CC N tracks 0 pi, bin 8                                                                  
      {  5.0 , 7.5      } ,  //numu CC N tracks 0 pi, bin 9                                                                  
      {  0.0 , 2.0      } ,  //numu CC N tracks 0 pi, bin 10                                                                 
      {  2.0 , 3.0      } ,  //numu CC N tracks 0 pi, bin 11                                                                 
      {  3.0 , 5.0      } ,  //numu CC N tracks 0 pi, bin 12                                                                 
      {  5.0 , 7.5      } ,  //numu CC N tracks 0 pi, bin 13                                                                 
      {  7.5 , 120.} ,  //numu CC N tracks 0 pi, bin 14 //                                                                   
      {  0.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 0                                                        
      {  3.0 , 120.} ,  //numu CC 3 tracks delta-enhanced, bin 1                                                             
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 2                                                        
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 3                                                        
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 4                                                        
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 5                                                        
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 6                                                        
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 7                                                        
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 8                                                        
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 9                                                        
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 10                                                       
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 11                                                       
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 12                                                       
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 13                   
      {  5.0 , 120.} ,  //numu CC 3 tracks delta-enhanced, bin 14 // 
      {  0.0 , 3.0      } ,  //numu CC 1 pi charged, bin 0                                                                   
      {  3.0 , 120.} ,  //numu CC 1 pi charged, bin 1                                                                        
      {  0.0 , 1.0      } , //numu CC 1 pi charged, bin 2            
      {  1.0 , 5.0      } , //numu CC 1 pi charged, bin 3                                                                    
      {  0.0 , 1.0      } , //numu CC 1 pi charged, bin 4                                                                    
      {  1.0 , 5.0      } , //numu CC 1 pi charged, bin 5                                                                    
      {  0.0 , 1.0      } , //numu CC 1 pi charged, bin 6                                                                    
      {  1.0 , 5.0      } , //numu CC 1 pi charged, bin 7                                                           
      {  5.0 , 120.} , //numu CC 1 pi charged, bin 8 //     
      {  0.0 , 3.0      } , //numu CC 1 pi0, bin 0                                                                           
      {  3.0 , 120.} ,  //numu CC 1 pi0, bin 1                                                                               
      {  0.0 , 1.0      } , //numu CC 1 pi0, bin 2                 
      {  1.0 , 5.0      } , //numu CC 1 pi0, bin 3                                                                           
      {  0.0 , 1.0      } , //numu CC 1 pi0, bin 4                                                                           
      {  1.0 , 5.0      } , //numu CC 1 pi0, bin 5                                                                           
      {  0.0 , 1.0      } , //numu CC 1 pi0, bin 6                                                                           
      {  1.0 , 5.0      } , //numu CC 1 pi0, bin 7 
      {  5.0 , 120.} ,  //numu CC 1 pi0, bin 8  //                                                                           
      {  0.0 ,    3.0   } , //numu CC 1 piC + 1 pi0, bin 0                                                                   
      {  3.0 , 120.} ,  //numu CC 1 piC + 1 pi0, bin 1  
      {  0.0 ,    1.0   } , //numu CC 1 piC + 1 pi0, bin 2                                                                   
      {  1.0 ,    3.0   } ,//numu CC 1 piC + 1 pi0, bin 3                                                                    
      {  3.0 ,    5.0   } , //numu CC 1 piC + 1 pi0, bin 4                                                                   
      {  0.0 ,    1.0   } , //numu CC 1 piC + 1 pi0, bin 5                                                                   
      {  1.0 ,    3.0   } , //numu CC 1 piC + 1 pi0, bin 6  
      {  3.0 ,    5.0   } , //numu CC 1 piC + 1 pi0, bin 7                                                                   
      {  5.0 , 120.} ,  //numu CC 1 piC + 1 pi0, bin 8 //                                                                    
      {  0.0 ,    3.0   } , //numu CC other, bin 0                                                                           
      {  3.0 , 120.} ,  //numu CC other, bin 1                                                                               
      {  0.0 ,    1.0   } , //numu CC other, bin 2                                                                           
      {  1.0 ,    3.0   } , //numu CC other, bin 3                                                                           
      {  3.0 ,    5.0   } , //numu CC other, bin 4                                                                           
      {  5.0 ,    7.5   } , //numu CC other, bin 5                                                                           
      {  0.0 ,    1.0   } , //numu CC other, bin 6                                                                           
      {  1.0 ,    3.0   } , //numu CC other, bin 7                                                                           
      {  3.0 ,    5.0   } , //numu CC other, bin 8                                                                           
      {  5.0 ,    7.5   } , //numu CC other, bin 9                                                                           
      {  7.5 , 120.} ,  //numu CC other, bin 10  // 
      {  0.0 ,    3.0   } , //numu CC wrong sign 0 pi, bin 0                                                                 
      {  3.0 , 120.} ,  //numu CC wrong sign 0 pi, bin 1                                                                     
      {  0.0 ,    5.0   } , //numu CC wrong sign 0 pi, bin 2 
      {  0.0 ,    5.0   } , //numu CC wrong sign 0 pi, bin 3  
      {  5.0 , 120.} ,//numu CC wrong sign 0 pi, bin 4  //                                                                   
      {  0.0 ,    3.0   } ,  //numu CC wrong sign 1 pi charged, bin 0                                                        
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 1                                                             
      {  0.0 ,    3.0   } , //numu CC wrong sign 1 pi charged, bin 2                                                         
      {  0.0 ,    3.0   } , //numu CC wrong sign 1 pi charged, bin 3                                                         
      {  0.0 ,    3.0   } , //numu CC wrong sign 1 pi charged, bin 4                                                         
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 5                                                             
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 6   
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 7   //                                                        
      {  0.0 ,    3.0   } ,  //numu CC wrong sign 1 pi 0, bin 0   
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi 0, bin 1                                                                   
      {  0.0 , 120.} ,  //numu CC wrong sign 1 pi 0, bin 2  //                                                               
      {  0.0 , 120.} ,  //numu CC wrong sign other, bin 0 //    
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 0                                                                             
      {  3.0 , 120.} ,  //nue CC 0 pi, bin 1                                                                                 
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 2 
      {  3.0 ,    5.0   } , //nue CC 0 pi, bin 3                                                                             
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 4                                                                             
      {  3.0 ,    5.0   } , //nue CC 0 pi, bin 5                                                                             
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 6                                                                             
      {  3.0 ,    5.0   } , //nue CC 0 pi, bin 7                                                                             
      {  5.0 , 120.} ,  //nue CC 0 pi, bin 8   //                                                                            
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 0  
      {  3.0 , 120.} ,  //nue CC 1 pi charged, bin 1   
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 2                                                                     
      {  3.0 ,    5.0   } , //nue CC 1 pi charged, bin 3                                                                     
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 4                                                                     
      {  3.0 ,    5.0   } , //nue CC 1 pi charged, bin 5                                                                     
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 6                                                                     
      {  3.0 ,    5.0   } , //nue CC 1 pi charged, bin 7                                                                     
      {  5.0 , 120.} ,  //nue CC 1 pi charged, bin 8  // 
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 0 
    {  3.0 , 120.} ,  //nue CC 1 pi0, bin 1                                                                                
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 2 
      {  3.0 ,    5.0   } , //nue CC 1 pi0, bin 3                                                                            
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 4                                                                            
      {  3.0 ,    5.0   } , //nue CC 1 pi0, bin 5                                                                            
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 6                                                                            
      {  3.0 ,    5.0   } , //nue CC 1 pi0, bin 7                                                                            
      {  5.0 , 120.} ,  //nue CC 1 pi0, bin 8   //                                                                          
      {  0.0 ,    3.0   } , //nue CC other, bin 0                                                                            
      {  3.0 , 120.} ,  //nue CC other, bin 1            
      {  0.0 ,    3.0   } , //nue CC other, bin 2                                                                            
      {  3.0 ,    7.5   } , //nue CC other, bin 3                                                                            
      {  7.5 , 120.} ,  //nue CC other, bin 4                                                                                
      {  0.0 ,    3.0   } , //nue CC other, bin 5                                                                            
      {  3.0 ,    7.5   } , //nue CC other, bin 6                                                                            
      {  7.5 , 120.} ,  //nue CC other, bin 7                                                                      
      {  0.0 ,    3.0   } , //nue CC other, bin 8                                                                            
      {  3.0 ,    7.5   } , //nue CC other, bin 9  
      {  7.5 , 120.} ,  //nue CC other, bin 10  //                                                                           
      {  0.0 , 120.} ,  //nue CC wrong sign, bin 0                                                                           
      {  0.0 , 120.} ,  //nue CC wrong sign, bin 1 //                                                                        
      {  0.0 ,   1.0    } , //NC 0 pi, bin 0             
      {  1.0 ,   3.0    } ,  //NC 0 pi, bin 1                                                                                
      {  3.0 , 120.} ,  //NC 0 pi, bin 2  //                                                                   
      {  0.0 ,   1.0    } , //NC 1 pi charged, bin 0                                                                         
      {  1.0 ,   3.0    } ,  //NC 1 pi charged, bin 1                                                                        
      {  3.0 , 120.} ,  //NC 1 pi charged, bin 2   //   
      {  0.0 ,   1.0    } , //NC 1 pi0, bin 0                                                                                
      {  1.0 ,   3.0    } ,  //NC 1 pi0, bin 1                                                                               
      {  3.0 , 120.} ,  //NC 1 pi0, bin 2   //                                                                               
      {  0.0 ,   1.0    } , //NC other, bin0                                                                                 
      {  1.0 ,   3.0    } ,  //NC other, bin 1             
      {  3.0 , 120.} ,   //NC other, bin 2 //                                                                                
      {  0.0 , 120.} ,  //e-scattering bin 0 //                                                                              
      {  0.0 , 120.} ,  // IMD, bin 0 //    
      //RHC
      {  0.0 , 3.0      } , //numu CC 1 track 0 pi, bin 0                                                                    
      {  3.0 , 120.} , //numu CC 1 track 0 pi, bin 1                                                                         
      {  0.0 , 2.0      } , //numu CC 1 track 0 pi, bin 2                                                                    
      {  2.0 , 3.0      } , //numu CC 1 track 0 pi, bin 3                                                                    
      {  3.0 , 5.0      } , //numu CC 1 track 0 pi, bin 4                                                                    
      {  0.0 , 2.0      } , //numu CC 1 track 0 pi, bin 5                                                                    
      {  2.0 , 3.0      } , //numu CC 1 track 0 pi, bin 6                                                                    
      {  3.0 , 5.0      } , //numu CC 1 track 0 pi, bin 7                                                                    
      {  5.0 , 120.} , //numu CC 1 track 0 pi, bin 8 //                                                                      
      {  0.0 , 3.0      } , //numu CC 2 tracks 0 pi, bin 0                                                                   
      {  3.0 , 120.} , //numu CC 2 tracks 0 pi, bin 1                                                                        
      {  0.0 , 2.0      } , //numu CC 2 tracks 0 pi, bin 2                                                                   
      {  2.0 , 3.0      } , //numu CC 2 tracks 0 pi, bin 3                                                                   
      {  3.0 , 5.0      } , //numu CC 2 tracks 0 pi, bin 4                                                                   
      {  0.0 , 2.0      } , //numu CC 2 tracks 0 pi, bin 5                                                                   
      {  2.0 , 3.0      } , //numu CC 2 tracks 0 pi, bin 6                                                                   
      {  3.0 , 5.0      } , //numu CC 2 tracks 0 pi, bin 7                                                                   
      {  5.0 , 120.} , //numu CC 2 tracks 0 pi, bin 8 //                                                                     
      {  0.0 , 3.0      } , //numu CC N tracks 0 pi, bin 0                                                                   
      {  3.0 , 120.} ,  //numu CC N tracks 0 pi, bin 1                                                                       
      {  0.0 , 2.0      } ,  //numu CC N tracks 0 pi, bin 2                                                                  
      {  2.0 , 3.0      } ,  //numu CC N tracks 0 pi, bin 3                                                                  
      {  3.0 , 5.0      } ,  //numu CC N tracks 0 pi, bin 4                                                                  
      {  5.0 , 7.5      } ,  //numu CC N tracks 0 pi, bin 5                                                                  
      {  0.0 , 2.0      } ,  //numu CC N tracks 0 pi, bin 6                                                                  
      {  2.0 , 3.0      } ,  //numu CC N tracks 0 pi, bin 7 
      {  3.0 , 5.0      } ,  //numu CC N tracks 0 pi, bin 8                                                                  
      {  5.0 , 7.5      } ,  //numu CC N tracks 0 pi, bin 9                                                                  
      {  0.0 , 2.0      } ,  //numu CC N tracks 0 pi, bin 10                                                                 
      {  2.0 , 3.0      } ,  //numu CC N tracks 0 pi, bin 11                                                                 
      {  3.0 , 5.0      } ,  //numu CC N tracks 0 pi, bin 12                                                                 
      {  5.0 , 7.5      } ,  //numu CC N tracks 0 pi, bin 13                                                                 
      {  7.5 , 120.} ,  //numu CC N tracks 0 pi, bin 14 //                                                                   
      {  0.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 0                                                        
      {  3.0 , 120.} ,  //numu CC 3 tracks delta-enhanced, bin 1                                                             
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 2                                                        
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 3                                                        
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 4                                                        
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 5                                                        
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 6                                                        
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 7                                                        
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 8                                                        
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 9                                                        
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 10                                                       
      {  0.0 , 1.0      } ,  //numu CC 3 tracks delta-enhanced, bin 11                                                       
      {  1.0 , 3.0      } ,  //numu CC 3 tracks delta-enhanced, bin 12                                                       
      {  3.0 , 5.0      } ,  //numu CC 3 tracks delta-enhanced, bin 13                   
      {  5.0 , 120.} ,  //numu CC 3 tracks delta-enhanced, bin 14 // 
      {  0.0 , 3.0      } ,  //numu CC 1 pi charged, bin 0                                                                   
      {  3.0 , 120.} ,  //numu CC 1 pi charged, bin 1                                                                        
      {  0.0 , 1.0      } , //numu CC 1 pi charged, bin 2            
      {  1.0 , 5.0      } , //numu CC 1 pi charged, bin 3                                                                    
      {  0.0 , 1.0      } , //numu CC 1 pi charged, bin 4                                                                    
      {  1.0 , 5.0      } , //numu CC 1 pi charged, bin 5                                                                    
      {  0.0 , 1.0      } , //numu CC 1 pi charged, bin 6                                                                    
      {  1.0 , 5.0      } , //numu CC 1 pi charged, bin 7                                                           
      {  5.0 , 120.} , //numu CC 1 pi charged, bin 8 //     
      {  0.0 , 3.0      } , //numu CC 1 pi0, bin 0                                                                           
      {  3.0 , 120.} ,  //numu CC 1 pi0, bin 1                                                                               
      {  0.0 , 1.0      } , //numu CC 1 pi0, bin 2                 
      {  1.0 , 5.0      } , //numu CC 1 pi0, bin 3                                                                           
      {  0.0 , 1.0      } , //numu CC 1 pi0, bin 4                                                                           
      {  1.0 , 5.0      } , //numu CC 1 pi0, bin 5                                                                           
      {  0.0 , 1.0      } , //numu CC 1 pi0, bin 6                                                                           
      {  1.0 , 5.0      } , //numu CC 1 pi0, bin 7 
      {  5.0 , 120.} ,  //numu CC 1 pi0, bin 8  //                                                                           
      {  0.0 ,    3.0   } , //numu CC 1 piC + 1 pi0, bin 0                                                                   
      {  3.0 , 120.} ,  //numu CC 1 piC + 1 pi0, bin 1  
      {  0.0 ,    1.0   } , //numu CC 1 piC + 1 pi0, bin 2                                                                   
      {  1.0 ,    3.0   } ,//numu CC 1 piC + 1 pi0, bin 3                                                                    
      {  3.0 ,    5.0   } , //numu CC 1 piC + 1 pi0, bin 4                                                                   
      {  0.0 ,    1.0   } , //numu CC 1 piC + 1 pi0, bin 5                                                                   
      {  1.0 ,    3.0   } , //numu CC 1 piC + 1 pi0, bin 6  
      {  3.0 ,    5.0   } , //numu CC 1 piC + 1 pi0, bin 7                                                                   
      {  5.0 , 120.} ,  //numu CC 1 piC + 1 pi0, bin 8 //                                                                    
      {  0.0 ,    3.0   } , //numu CC other, bin 0                                                                           
      {  3.0 , 120.} ,  //numu CC other, bin 1                                                                               
      {  0.0 ,    1.0   } , //numu CC other, bin 2                                                                           
      {  1.0 ,    3.0   } , //numu CC other, bin 3                                                                           
      {  3.0 ,    5.0   } , //numu CC other, bin 4                                                                           
      {  5.0 ,    7.5   } , //numu CC other, bin 5                                                                           
      {  0.0 ,    1.0   } , //numu CC other, bin 6                                                                           
      {  1.0 ,    3.0   } , //numu CC other, bin 7                                                                           
      {  3.0 ,    5.0   } , //numu CC other, bin 8                                                                           
      {  5.0 ,    7.5   } , //numu CC other, bin 9                                                                           
      {  7.5 , 120.} ,  //numu CC other, bin 10  // 
      {  0.0 ,    3.0   } , //numu CC wrong sign 0 pi, bin 0                                                                 
      {  3.0 , 120.} ,  //numu CC wrong sign 0 pi, bin 1                                                                     
      {  0.0 ,    5.0   } , //numu CC wrong sign 0 pi, bin 2 
      {  0.0 ,    5.0   } , //numu CC wrong sign 0 pi, bin 3  
      {  5.0 , 120.} ,//numu CC wrong sign 0 pi, bin 4  //                                                                   
      {  0.0 ,    3.0   } ,  //numu CC wrong sign 1 pi charged, bin 0                                                        
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 1                                                             
      {  0.0 ,    3.0   } , //numu CC wrong sign 1 pi charged, bin 2                                                         
      {  0.0 ,    3.0   } , //numu CC wrong sign 1 pi charged, bin 3                                                         
      {  0.0 ,    3.0   } , //numu CC wrong sign 1 pi charged, bin 4                                                         
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 5                                                             
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 6   
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi charged, bin 7   //                                                        
      {  0.0 ,    3.0   } ,  //numu CC wrong sign 1 pi 0, bin 0   
      {  3.0 , 120.} ,  //numu CC wrong sign 1 pi 0, bin 1                                                                   
      {  0.0 , 120.} ,  //numu CC wrong sign 1 pi 0, bin 2  //                                                               
      {  0.0 , 120.} ,  //numu CC wrong sign other, bin 0 //    
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 0                                                                             
      {  3.0 , 120.} ,  //nue CC 0 pi, bin 1                                                                                 
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 2 
      {  3.0 ,    5.0   } , //nue CC 0 pi, bin 3                                                                             
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 4                                                                             
      {  3.0 ,    5.0   } , //nue CC 0 pi, bin 5                                                                             
      {  0.0 ,    3.0   } , //nue CC 0 pi, bin 6                                                                             
      {  3.0 ,    5.0   } , //nue CC 0 pi, bin 7                                                                             
      {  5.0 , 120.} ,  //nue CC 0 pi, bin 8   //                                                                            
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 0  
      {  3.0 , 120.} ,  //nue CC 1 pi charged, bin 1   
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 2                                                                     
      {  3.0 ,    5.0   } , //nue CC 1 pi charged, bin 3                                                                     
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 4                                                                     
      {  3.0 ,    5.0   } , //nue CC 1 pi charged, bin 5                                                                     
      {  0.0 ,    3.0   } , //nue CC 1 pi charged, bin 6                                                                     
      {  3.0 ,    5.0   } , //nue CC 1 pi charged, bin 7                                                                     
      {  5.0 , 120.} ,  //nue CC 1 pi charged, bin 8  // 
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 0 
      {  3.0 , 120.} ,  //nue CC 1 pi0, bin 1                                                                                
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 2 
      {  3.0 ,    5.0   } , //nue CC 1 pi0, bin 3                                                                            
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 4                                                                            
      {  3.0 ,    5.0   } , //nue CC 1 pi0, bin 5                                                                            
      {  0.0 ,    3.0   } , //nue CC 1 pi0, bin 6                                                                            
      {  3.0 ,    5.0   } , //nue CC 1 pi0, bin 7                                                                            
      {  5.0 , 120.} ,  //nue CC 1 pi0, bin 8   //                                                                          
      {  0.0 ,    3.0   } , //nue CC other, bin 0                                                                            
      {  3.0 , 120.} ,  //nue CC other, bin 1            
      {  0.0 ,    3.0   } , //nue CC other, bin 2                                                                            
      {  3.0 ,    7.5   } , //nue CC other, bin 3                                                                            
      {  7.5 , 120.} ,  //nue CC other, bin 4                                                                                
      {  0.0 ,    3.0   } , //nue CC other, bin 5                                                                            
      {  3.0 ,    7.5   } , //nue CC other, bin 6                                                                            
      {  7.5 , 120.} ,  //nue CC other, bin 7                                                                      
      {  0.0 ,    3.0   } , //nue CC other, bin 8                                                                            
      {  3.0 ,    7.5   } , //nue CC other, bin 9  
      {  7.5 , 120.} ,  //nue CC other, bin 10  //                                                                           
      {  0.0 , 120.} ,  //nue CC wrong sign, bin 0                                                                           
      {  0.0 , 120.} ,  //nue CC wrong sign, bin 1 //                                                                        
      {  0.0 ,   1.0    } , //NC 0 pi, bin 0             
      {  1.0 ,   3.0    } ,  //NC 0 pi, bin 1                                                                                
      {  3.0 , 120.} ,  //NC 0 pi, bin 2  //                                                                   
      {  0.0 ,   1.0    } , //NC 1 pi charged, bin 0                                                                         
      {  1.0 ,   3.0    } ,  //NC 1 pi charged, bin 1                                                                        
      {  3.0 , 120.} ,  //NC 1 pi charged, bin 2   //   
      {  0.0 ,   1.0    } , //NC 1 pi0, bin 0                                                                                
      {  1.0 ,   3.0    } ,  //NC 1 pi0, bin 1                                                                               
      {  3.0 , 120.} ,  //NC 1 pi0, bin 2   //                                                                               
      {  0.0 ,   1.0    } , //NC other, bin0                                                                                 
      {  1.0 ,   3.0    } ,  //NC other, bin 1             
      {  3.0 , 120.} ,   //NC other, bin 2 //                                                                                
      {  0.0 , 120.} ,  //e-scattering bin 0 //                                                                              
      {  0.0 , 120.}   // IMD, bin 0 //    
    };
  
  //array of pairs of limits in Yreco energy for every bin per sample
  Float_t YrecoRange[314][2] = 
    {
      // FHC                                                                                                           
      {  0.0 , 0.02     },  //numu CC 1 track 0 pi, bin 0                                                                
      {  0.0 , 0.02     },  //numu CC 1 track 0 pi, bin 1                                                              
      { 0.02 , 0.5      },  //numu CC 1 track 0 pi, bin 2                                                                 
      { 0.02 , 0.5      },  //numu CC 1 track 0 pi, bin 3                                                                
      { 0.02 , 0.5      },  //numu CC 1 track 0 pi, bin 4                                                                
      {  0.5 , 1.0},  //numu CC 1 track 0 pi, bin 5                                                                    
      {  0.5 , 1.0},  //numu CC 1 track 0 pi, bin 6                                                                    
      {  0.5 , 1.0},  //numu CC 1 track 0 pi, bin 7                                                                     
      { 0.02 , 1.0},  //numu CC 1 track 0 pi, bin 8  //                                                                     
      { 0.0  , 0.02     },  //numu CC 2 tracks 0 pi, bin 0                                                            
      { 0.0  , 0.02     },  //numu CC 2 tracks 0 pi, bin 1                                                             
      { 0.02 , 0.5      },  //numu CC 2 tracks 0 pi, bin 2                                                              
      { 0.02 , 0.5      },  //numu CC 2 tracks 0 pi, bin 3                                                                  
      { 0.02 , 0.5      },  //numu CC 2 tracks 0 pi, bin 4                                                                
      { 0.5  , 1.0},  //numu CC 2 tracks 0 pi, bin 5                                                                       
      { 0.5  , 1.0},  //numu CC 2 tracks 0 pi, bin 6                                                                     
      { 0.5  , 1.0},  //numu CC 2 tracks 0 pi, bin 7                                                                   
      { 0.02 , 1.0},  //numu CC 2 tracks 0 pi, bin 8  //                                                                 
      { 0.0  , 0.02     },  //numu CC N tracks 0 pi, bin 0                                                               
      { 0.0  , 0.02     },  //numu CC N tracks 0 pi, bin 1                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 2                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 3                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 4                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 5                                                              
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 6                                                            
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 7                                                              
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 8                                                             
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 9 
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 10     
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 11                                                                
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 12                                                                  
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 13                                                                 
      { 0.02 , 1.0},  //numu CC N tracks 0 pi, bin 14   //                                                             
      { 0.0  , 0.02     }, //numu CC 3 tracks delta enhanced, bin 0                                                    
      { 0.0  , 0.02     }, //numu CC 3 tracks delta enhanced, bin 1                                                    
      { 0.02 , 0.3      }, //numu CC 3 tracks delta enhanced, bin 2                                                    
      { 0.02 , 0.3      },//numu CC 3 tracks delta enhanced, bin 3   
      { 0.02 , 0.3      },  //numu CC 3 tracks delta enhanced, bin 4                                                    
      { 0.3  , 0.5      },  //numu CC 3 tracks delta enhanced, bin 5                                                    
      { 0.3  , 0.5      },  //numu CC 3 tracks delta enhanced, bin 6 
      { 0.3  , 0.5      },  //numu CC 3 tracks delta enhanced, bin 7                                                   
      { 0.5  , 0.7      },  //numu CC 3 tracks delta enhanced, bin 8                                       
      { 0.5  , 0.7      },  //numu CC 3 tracks delta enhanced, bin 9   
      { 0.5  , 0.7      },  //numu CC 3 tracks delta enhanced, bin 10                                                  
      { 0.7  , 1.0},  //numu CC 3 tracks delta enhanced, bin 11                                                          
      { 0.7  , 1.0},  //numu CC 3 tracks delta enhanced, bin 12                                                           
      { 0.7  , 1.0},  //numu CC 3 tracks delta enhanced, bin 13                                                        
      { 0.02 , 1.0},  //numu CC 3 tracks delta enhanced, bin 14  //    
      { 0.0  , 0.02     },  //numu CC 1 pi charged, bin 0
      { 0.0  , 0.02     },  //numu CC 1 pi charged, bin 1
      { 0.02 , 0.3      },  //numu CC 1 pi charged, bin 2
      { 0.02 , 0.3      },  //numu CC 1 pi charged, bin 3                                                                 
      { 0.3  , 0.7      },  //numu CC 1 pi charged, bin 4                                                               
      { 0.3  , 0.7      },  //numu CC 1 pi charged, bin 5                                                              
      { 0.7  , 1.0},  //numu CC 1 pi charged, bin 6                                                                   
      { 0.7  , 1.0},  //numu CC 1 pi charged, bin 7  
      { 0.02 , 1.0},  //numu CC 1 pi charged, bin 8   //                                                                    
      { 0.0  , 0.02     },  //numu CC 1 pi0, bin 0                                                                          
      { 0.0  , 0.02     },  //numu CC 1 pi0, bin 1  
      { 0.02 , 0.3      },  //numu CC 1 pi0, bin 2                        
      { 0.02 , 0.3      },  //numu CC 1 pi0, bin 3                                                                     
      { 0.3  , 0.7      },  //numu CC 1 pi0, bin 4                                                                    
      { 0.3  , 0.7      },  //numu CC 1 pi0, bin 5                                                                    
      { 0.7  , 1.0},  //numu CC 1 pi0, bin 6        
      { 0.7  , 1.0},  //numu CC 1 pi0, bin 7                                                                           
      { 0.02 , 1.0},  //numu CC 1 pi0, bin 8  //                                                                        
      { 0.0  , 0.02     },  //numu CC 1pic+1pi0, bin 0                                                                 
      { 0.0  , 0.02     },  //numu CC 1pic+1pi0, bin 1                                                                
      { 0.02 , 0.5      },  //numu CC 1pic+1pi0, bin 2                                                                
      { 0.02 , 0.5      },  //numu CC 1pic+1pi0, bin 3                                                                 
      { 0.02 , 0.5      },  //numu CC 1pic+1pi0, bin 4                                                                 
      { 0.5  , 1.0},  //numu CC 1pic+1pi0, bin 5                                                                        
      { 0.5  , 1.0},  //numu CC 1pic+1pi0, bin 6                                                                       
      { 0.5  , 1.0},  //numu CC 1pic+1pi0, bin 7                                                                       
      { 0.02 , 1.0},  //numu CC 1pic+1pi0, bin 8                                                                       
      { 0.0  , 0.02     },  //numu CC other, bin 0                                                                     
      { 0.0  , 0.02     },  //numu CC other, bin 1                                                                      
      { 0.02 , 0.5      },  //numu CC other, bin 2                                                                      
      { 0.02 , 0.5      },  //numu CC other, bin 3                                                                      
      { 0.02 , 0.5      },  //numu CC other, bin 4                                                                     
      { 0.02 , 0.5      },  //numu CC other, bin 5                                                                     
      { 0.5  , 1.0},  //numu CC other, bin 6                                                                           
      { 0.5  , 1.0},  //numu CC other, bin 7                                                                            
      { 0.5  , 1.0},  //numu CC other, bin 8                                                                          
      { 0.5  , 1.0},  //numu CC other, bin 9                                                                          
      { 0.02 , 1.0},  //numu CC other, bin 10  //                                                                        
      { 0.0  , 0.02     },  //numu CC wrong sign 0 pi, bin 0                                                             
      { 0.0  , 0.02     },  //numu CC wrong sign 0 pi, bin 1                                                           
      { 0.02 , 0.5      },  //numu CC wrong sign 0 pi, bin 2                                                           
      { 0.5  , 1.0},  //numu CC wrong sign 0 pi, bin 3                                                               
      { 0.02 , 1.0},  //numu CC wrong sign 0 pi, bin 4    //                                                         
      { 0.0  , 0.02     },  //numu CC wrong sign 1 pi charged, bin 0    
      { 0.0  , 0.02     },  //numu CC wrong sign 1 pi charged, bin  1                                                  
      { 0.02 , 0.3      },  //numu CC wrong sign 1 pi charged, bin 2                                                    
      { 0.3  , 0.7      },  //numu CC wrong sign 1 pi charged, bin 3                                                   
      { 0.7  , 1.0},  //numu CC wrong sign 1 pi charged, bin 4                                                          
      { 0.02 , 0.3      },  //numu CC wrong sign 1 pi charged, bin 5                                                   
      { 0.3  , 0.7      },  //numu CC wrong sign 1 pi charged, bin 6                                                   
      { 0.7  , 1.0},  //numu CC wrong sign 1 pi charged, bin 7  //                                                          
      { 0.0  , 0.02     },   //numu CC wrong sign 1 pi0, bin 0                                                             
      { 0.0  , 0.02     },  //numu CC wrong sign 1 pi0, bin 1                                                             
      { 0.02 , 1.0},   //numu CC wrong sign 1 pi0, bin 2  //                                                           
      { 0.0  , 1.0},  //numu CC wrong sign other, bin 0  //                                                           
      { 0.0  , 0.02     },  //nue CC 0 pi, bin 0                                                                      
      { 0.0  , 0.02     },  //nue CC 0 pi, bin 1     
      { 0.02 , 0.3      },  //nue CC 0 pi, bin 2                                                                          
      { 0.02 , 0.3      },  //nue CC 0 pi, bin 3                                                                     
      { 0.3  , 0.5      },  //nue CC 0 pi, bin 4                                                                            
      { 0.3  , 0.5      },  //nue CC 0 pi, bin 5                                                                        
      { 0.5  , 1.0},  //nue CC 0 pi, bin 6                                                                             
      { 0.5  , 1.0},  //nue CC 0 pi, bin 7                                                                             
      { 0.02 , 1.0},  //nue CC 0 pi, bin 8   //   
      { 0.0  , 0.02     },  //nue CC 1 pi charged, bin 0 
      { 0.0  , 0.02     },  //nue CC 1 pi charged, bin 1 
      { 0.02 , 0.3      },  //nue CC 1 pi charged, bin 2   
      { 0.02 , 0.3      },  //nue CC 1 pi charged, bin 3                                                               
      { 0.3  , 0.5      },  //nue CC 1 pi charged, bin 4                                                                
      { 0.3  , 0.5      },  //nue CC 1 pi charged, bin 5                                                              
      { 0.5  , 1.0},  //nue CC 1 pi charged, bin 6                                                                      
      { 0.5  , 1.0},  //nue CC 1 pi charged, bin 7                                                                     
      { 0.02 , 1.0},  //nue CC 1 pi charged, bin 8   //                                                   
      { 0.0  , 0.02     },  //nue CC 1 pi0, bin 0                                                         
      { 0.0  , 0.02     },  //nue CC 1 pi0, bin 1                                                                        
      { 0.02 , 0.3      },  //nue CC 1 pi0, bin 2 
      { 0.02 , 0.3      },  //nue CC 1 pi0, bin 3                                                                         
      { 0.3  , 0.5      },  //nue CC 1 pi0, bin 4                                                                       
      { 0.3  , 0.5      },  //nue CC 1 pi0, bin 5                                                                       
      { 0.5  , 1.0},  //nue CC 1 pi0, bin 6                                                                             
      { 0.5  , 1.0},  //nue CC 1 pi0, bin 7                                                                            
      { 0.02 , 1.0},  //nue CC 1 pi0, bin 8   //                                                                            
      { 0.0  , 0.02     },  //nue CC other, bin 0                                                                     
      { 0.0  , 0.02     },  //nue CC other, bin 1                                                                        
      { 0.02 , 0.3      },  //nue CC other, bin 2                                                                      
      { 0.02 , 0.3      },  //nue CC other, bin 3                                                                      
      { 0.02 , 0.3      },  //nue CC other, bin 4                                                                    
      { 0.3  , 0.7      },  //nue CC other, bin 5                                                                  
      { 0.3  , 0.7      },  //nue CC other, bin 6                                                                  
      { 0.3  , 0.7      },  //nue CC other, bin 7                                                                  
      { 0.7  , 1.0},  //nue CC other, bin 8                                                                              
      { 0.7  , 1.0},  //nue CC other, bin 9                                                                            
      { 0.7  , 1.0},  //nue CC other, bin 10  //                                                                       
      { 0.0  , 0.02     },  //nue CC wrong sign, bin 0                                                                
      { 0.02 , 1.0},  //nue CC wrong sign, bin 1 //                                                                     
      { 0.0  , 1.0},  //NC 0 pi, bin 0                                                                                   
      { 0.0  , 1.0},  //NC 0 pi, bin 1                                                                                  
      { 0.0  , 1.0},  //NC 0 pi, bin 2 //                                                                               
      { 0.0  , 1.0},  //NC 1 pi C, bin 0                                                                               
      { 0.0  , 1.0},  //NC 1 pi C, bin 1                                                                               
      { 0.0  , 1.0},  //NC 1 pi C, bin 2  //                                                                           
      { 0.0  , 1.0},  //NC 1 pi0, bin 0                                                                                
      { 0.0  , 1.0},  //NC 1 pi0, bin 1                                                                                 
      { 0.0  , 1.0},  //NC 1 pi0, bin 2 //                                                                               
      { 0.0  , 1.0},  //NC other, bin 0                                                                                 
      { 0.0  , 1.0},   //NC other, bin 1                                                                                
      { 0.0  , 1.0},   //NC other, bin 2  //                                                                             
      { 0.0  , 1.0},  //e-scattering   
      { 0.0  , 1.0},  // IMD 
      //RHC
          {  0.0 , 0.02     },  //numu CC 1 track 0 pi, bin 0                                                                
      {  0.0 , 0.02     },  //numu CC 1 track 0 pi, bin 1                                                              
      { 0.02 , 0.5      },  //numu CC 1 track 0 pi, bin 2                                                                 
      { 0.02 , 0.5      },  //numu CC 1 track 0 pi, bin 3                                                                
      { 0.02 , 0.5      },  //numu CC 1 track 0 pi, bin 4                                                                
      {  0.5 , 1.0},  //numu CC 1 track 0 pi, bin 5                                                                    
      {  0.5 , 1.0},  //numu CC 1 track 0 pi, bin 6                                                                    
      {  0.5 , 1.0},  //numu CC 1 track 0 pi, bin 7                                                                     
      { 0.02 , 1.0},  //numu CC 1 track 0 pi, bin 8  //                                                                     
      { 0.0  , 0.02     },  //numu CC 2 tracks 0 pi, bin 0                                                            
      { 0.0  , 0.02     },  //numu CC 2 tracks 0 pi, bin 1                                                             
      { 0.02 , 0.5      },  //numu CC 2 tracks 0 pi, bin 2                                                              
      { 0.02 , 0.5      },  //numu CC 2 tracks 0 pi, bin 3                                                                  
      { 0.02 , 0.5      },  //numu CC 2 tracks 0 pi, bin 4                                                                
      { 0.5  , 1.0},  //numu CC 2 tracks 0 pi, bin 5                                                                       
      { 0.5  , 1.0},  //numu CC 2 tracks 0 pi, bin 6                                                                     
      { 0.5  , 1.0},  //numu CC 2 tracks 0 pi, bin 7                                                                   
      { 0.02 , 1.0},  //numu CC 2 tracks 0 pi, bin 8  //                                                                 
      { 0.0  , 0.02     },  //numu CC N tracks 0 pi, bin 0                                                               
      { 0.0  , 0.02     },  //numu CC N tracks 0 pi, bin 1                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 2                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 3                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 4                                                              
      { 0.02 , 0.3      },  //numu CC N tracks 0 pi, bin 5                                                              
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 6                                                            
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 7                                                              
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 8                                                             
      { 0.3  , 0.7      },  //numu CC N tracks 0 pi, bin 9 
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 10     
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 11                                                                
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 12                                                                  
      { 0.7  , 1.0},  //numu CC N tracks 0 pi, bin 13                                                                 
      { 0.02 , 1.0},  //numu CC N tracks 0 pi, bin 14   //                                                             
      { 0.0  , 0.02     }, //numu CC 3 tracks delta enhanced, bin 0                                                    
      { 0.0  , 0.02     }, //numu CC 3 tracks delta enhanced, bin 1                                                    
      { 0.02 , 0.3      }, //numu CC 3 tracks delta enhanced, bin 2                                                    
      { 0.02 , 0.3      },//numu CC 3 tracks delta enhanced, bin 3   
      { 0.02 , 0.3      },  //numu CC 3 tracks delta enhanced, bin 4                                                    
      { 0.3  , 0.5      },  //numu CC 3 tracks delta enhanced, bin 5                                                    
      { 0.3  , 0.5      },  //numu CC 3 tracks delta enhanced, bin 6 
      { 0.3  , 0.5      },  //numu CC 3 tracks delta enhanced, bin 7                                                   
      { 0.5  , 0.7      },  //numu CC 3 tracks delta enhanced, bin 8                                       
      { 0.5  , 0.7      },  //numu CC 3 tracks delta enhanced, bin 9   
      { 0.5  , 0.7      },  //numu CC 3 tracks delta enhanced, bin 10                                                  
      { 0.7  , 1.0},  //numu CC 3 tracks delta enhanced, bin 11                                                          
      { 0.7  , 1.0},  //numu CC 3 tracks delta enhanced, bin 12                                                           
      { 0.7  , 1.0},  //numu CC 3 tracks delta enhanced, bin 13                                                        
      { 0.02 , 1.0},  //numu CC 3 tracks delta enhanced, bin 14  //    
      { 0.0  , 0.02     },  //numu CC 1 pi charged, bin 0
      { 0.0  , 0.02     },  //numu CC 1 pi charged, bin 1
      { 0.02 , 0.3      },  //numu CC 1 pi charged, bin 2
      { 0.02 , 0.3      },  //numu CC 1 pi charged, bin 3                                                                 
      { 0.3  , 0.7      },  //numu CC 1 pi charged, bin 4                                                               
      { 0.3  , 0.7      },  //numu CC 1 pi charged, bin 5                                                              
      { 0.7  , 1.0},  //numu CC 1 pi charged, bin 6                                                                   
      { 0.7  , 1.0},  //numu CC 1 pi charged, bin 7  
      { 0.02 , 1.0},  //numu CC 1 pi charged, bin 8   //                                                                    
      { 0.0  , 0.02     },  //numu CC 1 pi0, bin 0                                                                          
      { 0.0  , 0.02     },  //numu CC 1 pi0, bin 1  
      { 0.02 , 0.3      },  //numu CC 1 pi0, bin 2                        
      { 0.02 , 0.3      },  //numu CC 1 pi0, bin 3                                                                     
      { 0.3  , 0.7      },  //numu CC 1 pi0, bin 4                                                                    
      { 0.3  , 0.7      },  //numu CC 1 pi0, bin 5                                                                    
      { 0.7  , 1.0},  //numu CC 1 pi0, bin 6        
      { 0.7  , 1.0},  //numu CC 1 pi0, bin 7                                                                           
      { 0.02 , 1.0},  //numu CC 1 pi0, bin 8  //                                                                        
      { 0.0  , 0.02     },  //numu CC 1pic+1pi0, bin 0                                                                 
      { 0.0  , 0.02     },  //numu CC 1pic+1pi0, bin 1                                                                
      { 0.02 , 0.5      },  //numu CC 1pic+1pi0, bin 2                                                                
      { 0.02 , 0.5      },  //numu CC 1pic+1pi0, bin 3                                                                 
      { 0.02 , 0.5      },  //numu CC 1pic+1pi0, bin 4                                                                 
      { 0.5  , 1.0},  //numu CC 1pic+1pi0, bin 5                                                                        
      { 0.5  , 1.0},  //numu CC 1pic+1pi0, bin 6                                                                       
      { 0.5  , 1.0},  //numu CC 1pic+1pi0, bin 7                                                                       
      { 0.02 , 1.0},  //numu CC 1pic+1pi0, bin 8                                                                       
      { 0.0  , 0.02     },  //numu CC other, bin 0                                                                     
      { 0.0  , 0.02     },  //numu CC other, bin 1                                                                      
      { 0.02 , 0.5      },  //numu CC other, bin 2                                                                      
      { 0.02 , 0.5      },  //numu CC other, bin 3                                                                      
      { 0.02 , 0.5      },  //numu CC other, bin 4                                                                     
      { 0.02 , 0.5      },  //numu CC other, bin 5                                                                     
      { 0.5  , 1.0},  //numu CC other, bin 6                                                                           
      { 0.5  , 1.0},  //numu CC other, bin 7                                                                            
      { 0.5  , 1.0},  //numu CC other, bin 8                                                                          
      { 0.5  , 1.0},  //numu CC other, bin 9                                                                          
      { 0.02 , 1.0},  //numu CC other, bin 10  //                                                                        
      { 0.0  , 0.02     },  //numu CC wrong sign 0 pi, bin 0                                                             
      { 0.0  , 0.02     },  //numu CC wrong sign 0 pi, bin 1                                                           
      { 0.02 , 0.5      },  //numu CC wrong sign 0 pi, bin 2                                                           
      { 0.5  , 1.0},  //numu CC wrong sign 0 pi, bin 3                                                               
      { 0.02 , 1.0},  //numu CC wrong sign 0 pi, bin 4    //                                                         
      { 0.0  , 0.02     },  //numu CC wrong sign 1 pi charged, bin 0    
      { 0.0  , 0.02     },  //numu CC wrong sign 1 pi charged, bin  1                                                  
      { 0.02 , 0.3      },  //numu CC wrong sign 1 pi charged, bin 2                                                    
      { 0.3  , 0.7      },  //numu CC wrong sign 1 pi charged, bin 3                                                   
      { 0.7  , 1.0},  //numu CC wrong sign 1 pi charged, bin 4                                                          
      { 0.02 , 0.3      },  //numu CC wrong sign 1 pi charged, bin 5                                                   
      { 0.3  , 0.7      },  //numu CC wrong sign 1 pi charged, bin 6                                                   
      { 0.7  , 1.0},  //numu CC wrong sign 1 pi charged, bin 7  //                                                          
      { 0.0  , 0.02     },   //numu CC wrong sign 1 pi0, bin 0                                                             
      { 0.0  , 0.02     },  //numu CC wrong sign 1 pi0, bin 1                                                             
      { 0.02 , 1.0},   //numu CC wrong sign 1 pi0, bin 2  //                                                           
      { 0.0  , 1.0},  //numu CC wrong sign other, bin 0  //                                                           
      { 0.0  , 0.02     },  //nue CC 0 pi, bin 0                                                                      
      { 0.0  , 0.02     },  //nue CC 0 pi, bin 1     
      { 0.02 , 0.3      },  //nue CC 0 pi, bin 2                                                                          
      { 0.02 , 0.3      },  //nue CC 0 pi, bin 3                                                                     
      { 0.3  , 0.5      },  //nue CC 0 pi, bin 4                                                                            
      { 0.3  , 0.5      },  //nue CC 0 pi, bin 5                                                                        
      { 0.5  , 1.0},  //nue CC 0 pi, bin 6                                                                             
      { 0.5  , 1.0},  //nue CC 0 pi, bin 7                                                                             
      { 0.02 , 1.0},  //nue CC 0 pi, bin 8   //   
      { 0.0  , 0.02     },  //nue CC 1 pi charged, bin 0 
      { 0.0  , 0.02     },  //nue CC 1 pi charged, bin 1 
      { 0.02 , 0.3      },  //nue CC 1 pi charged, bin 2   
      { 0.02 , 0.3      },  //nue CC 1 pi charged, bin 3                                                               
      { 0.3  , 0.5      },  //nue CC 1 pi charged, bin 4                                                                
      { 0.3  , 0.5      },  //nue CC 1 pi charged, bin 5                                                              
      { 0.5  , 1.0},  //nue CC 1 pi charged, bin 6                                                                      
      { 0.5  , 1.0},  //nue CC 1 pi charged, bin 7                                                                     
      { 0.02 , 1.0},  //nue CC 1 pi charged, bin 8   //                                                   
      { 0.0  , 0.02     },  //nue CC 1 pi0, bin 0                                                         
      { 0.0  , 0.02     },  //nue CC 1 pi0, bin 1                                                                        
      { 0.02 , 0.3      },  //nue CC 1 pi0, bin 2 
      { 0.02 , 0.3      },  //nue CC 1 pi0, bin 3                                                                         
      { 0.3  , 0.5      },  //nue CC 1 pi0, bin 4                                                                       
      { 0.3  , 0.5      },  //nue CC 1 pi0, bin 5                                                                       
      { 0.5  , 1.0},  //nue CC 1 pi0, bin 6                                                                             
      { 0.5  , 1.0},  //nue CC 1 pi0, bin 7                                                                            
      { 0.02 , 1.0},  //nue CC 1 pi0, bin 8   //                                                                            
      { 0.0  , 0.02     },  //nue CC other, bin 0                                                                     
      { 0.0  , 0.02     },  //nue CC other, bin 1                                                                        
      { 0.02 , 0.3      },  //nue CC other, bin 2                                                                      
      { 0.02 , 0.3      },  //nue CC other, bin 3                                                                      
      { 0.02 , 0.3      },  //nue CC other, bin 4                                                                    
      { 0.3  , 0.7      },  //nue CC other, bin 5                                                                  
      { 0.3  , 0.7      },  //nue CC other, bin 6                                                                  
      { 0.3  , 0.7      },  //nue CC other, bin 7                                                                  
      { 0.7  , 1.0},  //nue CC other, bin 8                                                                              
      { 0.7  , 1.0},  //nue CC other, bin 9                                                                            
      { 0.7  , 1.0},  //nue CC other, bin 10  //                                                                       
      { 0.0  , 0.02     },  //nue CC wrong sign, bin 0                                                                
      { 0.02 , 1.0},  //nue CC wrong sign, bin 1 //                                                                     
      { 0.0  , 1.0},  //NC 0 pi, bin 0                                                                                   
      { 0.0  , 1.0},  //NC 0 pi, bin 1                                                                                  
      { 0.0  , 1.0},  //NC 0 pi, bin 2 //                                                                               
      { 0.0  , 1.0},  //NC 1 pi C, bin 0                                                                               
      { 0.0  , 1.0},  //NC 1 pi C, bin 1                                                                               
      { 0.0  , 1.0},  //NC 1 pi C, bin 2  //                                                                           
      { 0.0  , 1.0},  //NC 1 pi0, bin 0                                                                                
      { 0.0  , 1.0},  //NC 1 pi0, bin 1                                                                                 
      { 0.0  , 1.0},  //NC 1 pi0, bin 2 //                                                                               
      { 0.0  , 1.0},  //NC other, bin 0                                                                                 
      { 0.0  , 1.0},   //NC other, bin 1                                                                                
      { 0.0  , 1.0},   //NC other, bin 2  //                                                                             
      { 0.0  , 1.0},  //e-scattering   
      { 0.0  , 1.0}  // IMD 

    };


  if (fChain == 0) return;

  //Number of input entries (i.e. events in the file(s) provided)
  Long64_t nentries = fChain->GetEntries();
  //  std::cout << "nentries = " << nentries << std::endl;

  Long64_t nbytes = 0, nb = 0;

  //vector to store the number of events in each bin for each tweak
  //Note: edit ntweaks as to run as many tweaks per jobs as you want
  const unsigned int ntweaks = 1;
  TMatrixF vec(314,ntweaks);

  //Dummy detector def for testing.
  //This is the code to setup and initialise the reweighter

  DetSystRWtool* Dummy = new DetSystRWtool(mySeed);

  //optional histograms
  //TH2D* Enew_vs_Eold = new TH2D("Enew_vs_Eold", "Enew_vs_Eold", 1200, 0, 120, 1200, 0,120);
  //  TH2D* samplenew_vs_sampleold = new TH2D("samplenew_vs_sampleold", "samplenew_vs_sampleold", 28,0,28,28,0,28);
  //  TH2D* ynew_vs_yold = new TH2D("ynew_vs_yold", "ynew_vs_yold", 1000,0,1,1000,0,1);

  for(unsigned int itweak = 0; itweak < ntweaks; itweak++)
    {      
      //A few contatiners to be used in the loop below
      bool IsLep;
      int lep_PDGreco;
      int lep_PDGtrue;
      double lep_Ereco;
      double lep_Etrue;
      double had_Etrue;
      double had_Ereco;
      vector<int> hads_PDG;
      vector<int> hads_PDGreco;
      vector<int> hads_PDGtrue;
      vector<double> hads_Etrue;
      vector<double> hads_Ereco;
      vector<bool> hads_IsReco;
      
      bool true_part_found = false;
      bool reco_part_found = false;
      
      bool antinu(false);//
      //Note: hack for the moment, to separate nu and nubar contributions
      //number of entries for first file (neutrino mode) added by hand here
      Long64_t entries_nu(1052779);

      //we start with neutrino
      //FHC mode, FGT numbers by Dan
      Dummy->SetNuMode(true);
      Dummy->Initialize_Detector(0.0559,0.10,0.01,1.00,0.100,0.105,
				 0.0560,0.10,0.01,0.98,0.115,1.20,
				 0.1697,0.16,0.03,
				 0.97,0.955,1.65,
				 0.98,0.145,1.20,
				 0.82,0.145,0.30);
     
      //End Det Class Init
      Dummy->SetRandomThrow();
 
      for (Long64_t jentry=0; jentry<nentries;jentry++) {
	
	if(jentry%1000==0) cout<<"On event "<<jentry<<" of "<<nentries<<endl;
	
	//separate neutrino and antineutrino
        if(jentry<entries_nu)
	  antinu = false;
	else 
	  antinu = true;

	//change to antineutrino
	if(jentry==entries_nu) //to do it only once
	  {
	    //RHC mode
	    Dummy->SetNuMode(false);
	    Dummy->Initialize_Detector(0.0554,0.10,0.01,1.00,0.100,0.105,
				       0.0563,0.10,0.01,0.98,0.115,0.90,
				       0.1625,0.16,0.03,
				       0.97,0.955,1.65,
				       0.98,0.145,0.90,
				       0.82,0.145,0.30);
	  }

	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;
	
	if((recoFSParticles>kMaxrecoFSParticles)||(trueFSParticles>kMaxtrueFSParticles)) continue;
	
	//Get event info and pass it to the Det Class
	//This is the code in the event looper to give the reweighter an event and get back 'new' sample and kineamtics
	//Essentally you need to give the reweighter the true and reco Elep and Ehad
	//as well as the list of hadronic particles and their properties
	//this fills the appropriate containers
	IsLep = false;
	lep_PDGreco = 0;
	lep_PDGtrue = 0;
	lep_Ereco = 0.0;
	lep_Etrue = 0.0;
	had_Etrue = 0.0;
	had_Ereco = 0.0;
	hads_PDG.clear();
	hads_PDGreco.clear();
	hads_PDGtrue.clear();
	hads_Etrue.clear();
	hads_Ereco.clear();
	hads_IsReco.clear();
	

	for(int i = 0; i < trueFSParticles; ++i){
	  if(abs(trueFSParticles_pdg[i])==11 || abs(trueFSParticles_pdg[i])==13){
	    lep_Etrue  = trueFSParticles_energy[i];
	    lep_PDGtrue  = trueFSParticles_pdg[i];
	  }else{
	    for(int k = 0; k < recoFSParticles; ++k) 
	      if(recoFSParticles_id[k]==trueFSParticles_id[i]){
		had_Etrue += trueFSParticles_energy[i];
		if(trueFSParticles_pdg[i]==2212) had_Etrue -= 0.93827;
	      }
	  }
	}
	
	for(int i = 0; i < trueFSParticles; ++i){
	  hads_Etrue.push_back(trueFSParticles_energy[i]);
	  hads_PDGtrue.push_back(trueFSParticles_pdg[i]);
	  hads_PDGreco.push_back(0);
	  for(int k = 0; k < recoFSParticles; ++k){
	    if(recoFSParticles_id[k]==trueFSParticles_id[i]){
	      hads_PDGreco.back() = recoFSParticles_pdg[k];
	    }
	  }
	}

	for(int k = 0; k < recoFSParticles; ++k){
	  if(abs(recoFSParticles_pdg[k])==11 || abs(recoFSParticles_pdg[k])==13){
	    lep_PDGreco = recoFSParticles_pdg[k];
	    lep_Ereco = recoFSParticles_energy[k];
	  }else{
	    had_Ereco += recoFSParticles_energy[k];
	    if(recoFSParticles_pdg[k]==2212) had_Ereco -= 0.93827;
	  }
	}


	Dummy->SetEvent(sample_reco, lep_PDGreco,
			lep_Etrue, lep_Ereco,
			had_Etrue, had_Ereco,
			hads_PDGreco, hads_PDGtrue, hads_Etrue);
	
	//See what the Det class came up with for this throw
    //Once the event info is passed to the reweighter it automatically calculates the 'new' values
    //and you can access them through these methods ...
    //These are then used to fill new histograms, like kNewHist[Dummy->GetNewSample()]->Fill(Dummy->GetNewEreco(),Dummy->GetNewYreco())
    //where kNewHist is an array of 2D histograms, one for each sample code, containing 2D hists of Ereco-vs-y_reco
    //you can also just fill vectors or TTree branchses with these values to build histograms later



    //    cout<<"Ereco old: "<<Ev_reco<<" new: "<<Dummy->GetNewEreco()<<endl;
    //cout<<"Yreco old: "<<y_reco<<" new: "<<Dummy->GetNewYreco()<<endl;
    //cout<<"Weight old: 1.0 new: "<<Dummy->GetEffWeight()<<endl;
    //cout<<"Sample old: "<<sample_reco<<" new: "<<Dummy->GetNewSample()<<endl;
    //    cout<<"\n"<<endl;


    //There is a second method in DetSystRWtool which calculates a weight
    //but doesnt make sense
    //    double wgt = Dummy->GetEffWeight();
    //    Weight->Fill(wgt);
    Int_t index(0);
    int new_sample = Dummy->GetNewSample();
    double new_Ereco = Dummy->GetNewEreco();
    double new_Yreco = Dummy->GetNewYreco();

    //if sample is undefined, continue
    if (sample_reco==-1)
      continue;
    if (new_sample==-1)
      continue;
    
    //sample ordering starts in 1 (skipping 0 in SampleLimits), but array index start from 0
    int init = SampleLimits[new_sample-1][0];
    int final = SampleLimits[new_sample-1][1];
    
    Int_t index(0);
    for (int i = init; i<=final; i++)
      {
	if((new_Ereco>=ErecoRange[i][0])&&
	   (new_Ereco<=ErecoRange[i][1])&&
	   (new_Yreco>=YrecoRange[i][0])&&
	   (new_Yreco<=YrecoRange[i][1]))
	  {
	    index = i;
	    //std::cout << "index = " << index << std::endl;  
	  }
	//
      }
    //nu-nubar separation - index for nubar is the same displaced by 157
    if(antinu)
      index = index+157;

    //Chris: here when adding the event to the appropriate vector component, it takes into account the weight,
    //so those events with -3 should be added with that weight                                                               
    vec[index][itweak]+= 1.0*fgtweight; // wgt; //if using the second method, wgt should go there instead   
    Enew_vs_Eold->Fill(Ev_reco,new_Ereco);
    ynew_vs_yold->Fill(y_reco,new_Yreco);
    samplenew_vs_sampleold->Fill(sample_reco,new_sample);
    //        cout<<"Ereco: "<<Ev_reco<<" , Yreco: "<<y_reco<< " and Sample: "<<sample_reco<< " - index = " << index << endl;

      }//entries
    }//tweaks

  //write output
  TFile output_file("det_eff_fgt.root","RECREATE");
  output_file.cd();
  vec.Write("vec");
  //  Enew_vs_Eold->Write("Enew_vs_Eold");
  //  ynew_vs_yold->Write("ynew_vs_yold");
  //  samplenew_vs_sampleold->Write("samplenew_vs_sampleold");

}









