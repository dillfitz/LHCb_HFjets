//
//  Header.h
//  
//
//  Created by Jose Arias on 4/25/23.
//

#ifndef Header_h
#define Header_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

double checkphi(double phi)
{
  double returnphi = phi;
  if(phi > 1. * TMath::Pi())
    returnphi -= 2 * TMath::Pi();
  else if(phi < -1 * TMath::Pi() )
    returnphi += 2 * TMath::Pi();
  return returnphi;
}

#endif /* Header_h */
