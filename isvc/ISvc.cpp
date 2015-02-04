
// ----------------------------------------------------------------------------
//  $Id: ISvc.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <TStopwatch.h>
#include <alex/ISvc.h>
#include <alex/LogUtil.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>

using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {

//--------------------------------------------------------------------
void IreneManager::Init(std::string debugLevel)
//--------------------------------------------------------------------
  {
    fDebugLevel = debugLevel;
    SetDebugLevel(debugLevel);
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "IreneManager::Init()" ;
    //fRandom = new TRandom2();
  }


// //--------------------------------------------------------------------
//   void IreneManager::InitDst(std::string fileName, const irene::Event* ievt)
// //--------------------------------------------------------------------
//   {
//     fIfile = new TFile(fileName.c_str(), "READ");
//     fEvtTree = dynamic_cast<TTree*>(fIfile->Get("EVENT"));
//     fEvtTree->SetBranchAddress("EventBranch", &ievt);
//   }


// //--------------------------------------------------------------------
//   int IreneManager::DstEntries()
// //--------------------------------------------------------------------
//   {
//     return (int) fEvtTree->GetEntries();
//   }


// //--------------------------------------------------------------------
//   int IreneManager::DstGetEntry(int ivt) 
// //--------------------------------------------------------------------
//   {
//     return fEvtTree->GetEntry(ivt);
//   }


//--------------------------------------------------------------------
  void IreneManager::LoadEvent(const irene::Event* ievt)
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "***** IreneManager::LoadEvent " << ievt->GetID();

    fIevt = ievt;

    

    //FetchElectrons();
    //FetchPMaxElectrons();

    klog << log4cpp::Priority::DEBUG << "IreneManager:: Fill true hits" ;
    fTrueHits.clear();
    fIevt->FillHitVector(fTrueHits, "ACTIVE");
    klog << log4cpp::Priority::DEBUG << "Size of hit vector =" << fTrueHits.size(); 

    klog << log4cpp::Priority::DEBUG << "IreneManager:: Fill tracks" ;
    fIreneTracks = fIevt->Tracks();
    klog << log4cpp::Priority::DEBUG << "Size of tracks vector =" << fIreneTracks.size();

    klog << log4cpp::Priority::DEBUG << "IreneManager:: Fill particles" ;
    fIreneParticles= fIevt->Particles();
    klog << log4cpp::Priority::DEBUG << "Size of particles vector =" << fIreneParticles.size();

    // for (auto track: fIreneTracks)
    // {
    //   auto particle = track->GetParticle();
    //   if (particle->GetParticleID() == fBetasMax.first->GetParticleID())
    //   {
    //     fBetasMaxHits.first = track->GetHits();
    //   }
    //   else if (GetNumberOfPrimaryElectrons() >= 2 && 
    //     particle->GetParticleID() == fBetasMax.second->GetParticleID())
    //   {

    //     fBetasMaxHits.second = track->GetHits();
    //   }
    // }

    klog << log4cpp::Priority::DEBUG << "IreneManager::Compute True Vertex" ;
    GetTrueVertex();

  }


//--------------------------------------------------------------------
  const irene::Event& IreneManager::GetEvent()
//--------------------------------------------------------------------
  {
    return *fIevt;
  }

//--------------------------------------------------------------------
  void IreneManager::GetTrueVertex()
//--------------------------------------------------------------------
  { 
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog.debug("In IreneManager::GetTrueVertex(): Fill true vertex");

    bool found=false;
    TLorentzVector Vertex;
  
    for (size_t it = 0; it < fIreneTracks.size(); it++)
    { 
      const irene::Track* itrk = fIreneTracks.at(it) ; 
      const irene::Particle* ipart= itrk->GetParticle();

      klog.debug("++++Irene particle associated to track number %lu\n",it);
    
      if (ipart->IsPrimary()) 
      {
        Vertex = ipart->GetInitialVertex();
        found = true;
        break;
      } 
    } 
  
    if (found==false)
      klog.error("Error! vertex not found!");


    for (int i=0; i< 3; i++)
        fVertex[i]= Vertex[i];
      
  }


//--------------------------------------------------------------------
  void IreneManager::PrintHits()
//--------------------------------------------------------------------
  {
    std::cout << " Irene Hits: " << std::endl;

    for(auto ihit : fTrueHits)
    {
      TLorentzVector vl = ihit.first;
      double e = ihit.second;
      std::cout 
           << " x (mm) = " << vl[0]
           << " y (mm) = " << vl[1]
           << " z (mm) = " << vl[2]
           << " edep (MeV) = " << e << std::endl;    
    }
  }
// //--------------------------------------------------------------------
//   void IreneManager::FetchElectrons() 
// //--------------------------------------------------------------------
//   {
//     fElectrons.clear();
//     fBetas.clear();
//     for (auto it = 0; it < (int) fIevt->Tracks().size(); ++it)
//     {  
//       const irene::Particle* ip= fIevt->Tracks().at(it)->GetParticle();
    
//       //if (ip->GetPDGcode() == 11 and ip->IsPrimary() == true) 
//       if (ip->GetPDGcode() == 11) 
//       {
//         fElectrons.push_back(ip);
//         if (ip->IsPrimary() == true)
//           fBetas.push_back(ip);
//       }
//     } 
//   }


// //--------------------------------------------------------------------
//   void IreneManager::FetchPMaxElectrons() 
// //--------------------------------------------------------------------
//   {
//     log4cpp::Category& klog = log4cpp::Category::getRoot();
//     klog << log4cpp::Priority::DEBUG << "IreneManager::GetPMaxElectrons()" ;

//     double pmax = 0;
//     int imax=-1;
//     int i=0;
//     for(auto beta : fBetas)
//     {
//       if (beta->Momentum() > pmax)
//       {
//         pmax = beta->Momentum();
//         imax=i;
//       }
//       i++;
//     }

//     klog << log4cpp::Priority::DEBUG << "imax =" << imax << "pmaxx = " << pmax;

//     fBetasMax.first = fBetas.at(imax);
//     if (GetNumberOfPrimaryElectrons() <2 )
//       fBetasMax.second = NULL;
//     else
//     {
//       pmax = 0;
//       int imax2=-1;
//       i=-1;
//       for(auto beta : fBetas)
//       {
//         i++;
//         if (i==imax) continue;
//         if (beta->Momentum() > pmax)
//         {
//           pmax = beta->Momentum();
//           imax2=i;
//         }
//       }
//       klog << log4cpp::Priority::DEBUG << "imax2 =" << imax2 << "pmax = " << pmax;
//       fBetasMax.second =fBetas.at(imax2);
//     }
//   }



}
