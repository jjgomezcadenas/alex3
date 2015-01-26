
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
    SetDebugLevel(debugLevel);

    fTrueEventEnergy = 0.;
    fRecEventEnergy = 0.;

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "AlexManager::Init()" ;
  }

  //--------------------------------------------------------------------
  void AlexService::Clear()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    //klog << log4cpp::Priority::DEBUG << "AlexManager::Clear()" ;

    fTrueEventEnergy = 0.;
    fRecEventEnergy = 0.;

    //klog << log4cpp::Priority::DEBUG << "fParticles size before VDELETE = " 
    //<< fParticles.size(); 

    VDelete(fParticles);
    VDelete(fTTracks);
    VDelete(fRTracks);

    // MUST clear after VDelete!
    fParticles.clear();
    fTTracks.clear();
    fRTracks.clear();


    //klog << log4cpp::Priority::DEBUG << "fParticles size after clear = " 
    //<< fParticles.size();

  }


  //--------------------------------------------------------------------
  void AlexService::AddParticle(const alex::AParticle* part)
  //--------------------------------------------------------------------
  {
    fParticles.push_back(new AParticle(*part));
  }


  //--------------------------------------------------------------------
  const alex::AParticle* AlexService::GetParticle(int id) const
  //--------------------------------------------------------------------
  {
    std::vector <AParticle*> parts = GetParticles();
    for (auto part : parts)
    {
      if (part->GetID() == id) return part;
    }
    std::cout << "ASvc::ERROR: Particle ID " << id << " does NOT EXIST !!" << std::endl;
    exit(0);
  }


  //--------------------------------------------------------------------
  void AlexService::AddTTrack(const alex::ATTrack* ttrack)
  //--------------------------------------------------------------------
  {
    fTrueEventEnergy += ttrack->GetEdep();
    fTTracks.push_back(new ATTrack(*ttrack));
  }


  //--------------------------------------------------------------------
  const alex::ATTrack* AlexService::GetTTrack(int id) const
  //--------------------------------------------------------------------
  {
    std::vector <ATTrack*> ttracks = GetTTracks();
    for (auto ttrack : ttracks)
    {
      if (ttrack->GetID() == id) return ttrack;
    }
    std::cout << "ASvc::ERROR: TTrack ID " << id << " does NOT EXIST !!" << std::endl;
    exit(0);
  }


  //--------------------------------------------------------------------
  void AlexService::AddRTrack(const alex::ARTrack* rtrack)
  //--------------------------------------------------------------------
  {
    fRecEventEnergy += rtrack->GetEdep();
    fRTracks.push_back(new ARTrack(*rtrack));
  }


  //--------------------------------------------------------------------
  const alex::ARTrack* AlexService::GetRTrack(int id) const
  //--------------------------------------------------------------------
  {
    std::vector <ARTrack*> rtracks = GetRTracks();
    for (auto rtrack : rtracks)
    {
      if (rtrack->GetID() == id) return rtrack;
    }
    std::cout << "ASvc::ERROR: RTrack ID " << id << " does NOT EXIST !!" << std::endl;
    exit(0);
  }

}
