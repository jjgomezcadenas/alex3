// ----------------------------------------------------------------------------
//  $Id: ATTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/ATTrack.h>
#include <alex/AHit.h>
#include <alex/VectorOperations.h>

#include <iostream>

ClassImp(alex::ATTrack)

namespace alex {

  ATTrack::ATTrack() : ABTrack::ABTrack() 
  {
    fParticleID=-1;
  };


  ATTrack::ATTrack(int id, int particleId) : ABTrack::ABTrack(id)
  {
    SetParticleID(particleId);
  }


  ATTrack::ATTrack(const ATTrack& att) : ABTrack::ABTrack(att)
  {
 		SetParticleID(att.GetParticleID());
  }

	  
  void ATTrack::DisplayInfo(std::ostream& s) const
  {
    ABTrack::DisplayInfo(s);
   	s << "* Origin: Particle ID " << GetParticleID() << std::endl;
  }


  std::string ATTrack::PrintInfo() const
  {
    std::stringstream s;
    DisplayInfo(s);
    return s.str();
  }

}


std::ostream& operator << (std::ostream& s, const alex::ATTrack& att) 
{
  att.DisplayInfo(s);
  return s; 
}
