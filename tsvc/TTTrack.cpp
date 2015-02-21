// ----------------------------------------------------------------------------
//  $Id: TTTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/TTTrack.h>
#include <alex/ATTrack.h>

ClassImp(alex::TTTrack)

namespace alex {

  // ATTrack::ATTrack() : ABTrack::ABTrack() 
  // {
  //   fParticleID=-1;
  // };


  // ATTrack::ATTrack(int id, int particleId) : ABTrack::ABTrack(id)
  // {
  //   SetParticleID(particleId);
  // }

  // ATTrack::~ATTrack() 
  // {
  //   log4cpp::Category& klog = log4cpp::Category::getRoot();
  //   klog << log4cpp::Priority::INFO << "ATTrack::~ATTrack()";
  // }


  TTTrack::TTTrack(const ATTrack& att) : ATTrack(att)
  {
    //ATTrack::ATTrack(att);
 		//SetParticleID(att.GetParticleID());
  }


}

