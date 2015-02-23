
// ----------------------------------------------------------------------------
//  $Id: ASvc.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <TStopwatch.h>
#include <alex/ASvc.h>
#include <alex/LogUtil.h>
#include <alex/VectorOperations.h>
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
  void AlexService::Init(std::string debugLevel)
  //--------------------------------------------------------------------
  {
    fDebugLevel = debugLevel;
    SetDebugLevel(fDebugLevel);

    fTrueEventEnergy = 0.;
    fRecEventEnergy = 0.;

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "AlexManager Initialized" ;
  }

  //--------------------------------------------------------------------
  void AlexService::Clear()
  //--------------------------------------------------------------------
  {
    SetDebugLevel(fDebugLevel);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "AlexService::Clear()" ;

    fTrueEventEnergy = 0.;
    fRecEventEnergy = 0.;

    klog << log4cpp::Priority::DEBUG << "fParticles size before VDELETE = " 
    << fParticles.size(); 

    klog << log4cpp::Priority::DEBUG << "fTTracks size before VDELETE = " 
    << fTTracks.size();

    klog << log4cpp::Priority::DEBUG << "fRTracks size before VDELETE = " 
    << fRTracks.size(); 

    for (auto particle: fParticles)
    {
      klog << log4cpp::Priority::DEBUG << particle->PrintInfo() ;
    }

    VDelete(fParticles);

    klog << log4cpp::Priority::DEBUG << "fParticles size after VDELETE = " 
    << fParticles.size(); 

    for (auto ttrack: fTTracks)
    {
      klog << log4cpp::Priority::DEBUG << ttrack->PrintInfo() ;
    }

    VDelete(fTTracks);

    klog << log4cpp::Priority::DEBUG << "fTTracks size after VDELETE = " 
    << fTTracks.size();

    VDelete(fRTracks);

    // MUST clear after VDelete!
    fParticles.clear();
    fTTracks.clear();
    fRTracks.clear();

    klog << log4cpp::Priority::DEBUG << "fParticles size after clear = " 
    << fParticles.size();

    klog << log4cpp::Priority::DEBUG << "+++All vectors cleared+++ " ;

  }


  //--------------------------------------------------------------------
  void AlexService::AddParticle(alex::AParticle* part)
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "In AlexService::AddParticle() " ;
    
    fParticles.push_back(part);
  }


  //--------------------------------------------------------------------
  alex::AParticle* AlexService::GetParticle(int id) const
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    std::vector <AParticle*> parts = GetParticles();

    for (auto part : parts)
    {
      if (part->GetID() == id) return part;
    }
    klog << log4cpp::Priority::FATAL  << "ASvc::ERROR: Particle ID " 
    << id << " does NOT EXIST !!" ;
    exit(-1);
  }


  //--------------------------------------------------------------------
  void AlexService::AddTTrack(alex::ATTrack* ttrack)
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "In AlexService::AddTTrack() " ;
    
    fTrueEventEnergy += ttrack->GetEdep();
    fTTracks.push_back(ttrack);
  }


  //--------------------------------------------------------------------
   alex::ATTrack* AlexService::GetTTrack(int id) const
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    std::vector <ATTrack*> ttracks = GetTTracks();
    for (auto ttrack : ttracks)
    {
      if (ttrack->GetID() == id) return ttrack;
    }
    
    klog << log4cpp::Priority::FATAL  << "ASvc::ERROR: TTrack ID " 
    << id << " does NOT EXIST !!" ;
    exit(-1);
  }


  //--------------------------------------------------------------------
  void AlexService::AddRTrack(alex::ARTrack* rtrack)
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "In AlexService::AddRTrack() " ;
    
    fRecEventEnergy += rtrack->GetEdep();
    fRTracks.push_back(rtrack);
  }


  //--------------------------------------------------------------------
   alex::ARTrack* AlexService::GetRTrack(int id) const
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    std::vector <ARTrack*> rtracks = GetRTracks();
    for (auto rtrack : rtracks)
    {
      if (rtrack->GetID() == id) return rtrack;
    }
    klog << log4cpp::Priority::FATAL  << "ASvc::ERROR: RTrack ID " 
    << id << " does NOT EXIST !!" ;

    exit(-1);
  }


  //--------------------------------------------------------------------
  double AlexService::GetHitsDist(alex::AHit* hit1, alex::AHit* hit2) const
  //--------------------------------------------------------------------
  {
    TVector3 pos1 = hit1->GetPosition();
    TVector3 pos2 = hit2->GetPosition();
    TVector3 distV = pos1 - pos2;
    return distV.Mag();
  }


  //--------------------------------------------------------------------
  double AlexService::GetTracksDist(alex::ABTrack* trk1, alex::ABTrack* trk2) const
  //--------------------------------------------------------------------
  {
    double trksDist = 1000.;
    for (auto hit1 : trk1->GetHits()) {
      for (auto hit2 : trk2->GetHits()) {
        double hitsDist = GetHitsDist(hit1, hit2);
        if (hitsDist < trksDist) trksDist = hitsDist;
      }
    }

    return trksDist;
  }

}
