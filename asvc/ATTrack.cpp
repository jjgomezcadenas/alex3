
// ----------------------------------------------------------------------------
//  $Id: ATTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "ATTRack.h"
#include "AHit.h"
#include <alex/VectorOperations.h>

#include <iostream>

namespace alex {
	ATTrack::ATTrack(int Id, int particleID) 
  {
  	SetID(Id);
  	SetParticleID(particleID);
  }

  ATTrack::ATTrack(const ATTrack& att)
  {
 		SetID(att.GetID());
 		SetParticleID(att.GetParticleID());
 		VDelete(fHits);

    std::vector<AHit*> hits = att.GetHits();
    for (auto hit : hits)
    {
      AddHit(hit);
    }
  }

  void ATTrack::AddHit(const AHit* ahit)
  {
    fHits.push_back(new AHit(*ahit));
  }
	  
  void ATTrack::DisplayInfo(std::ostream& s) const
  	{
   	s << std::endl;    
    
   	s << "*** TTrack ID = " << GetID();
   	s << "  from Particle " << GetParticleID() << std::endl;
   	s << "* Hits Collection: " <<  std::endl;

    const std::vector<AHit*> hits = GetHits();
    for (auto hit : hits)
    {
      s << hit <<  std::endl;
    }
  }
}


std::ostream& operator << (std::ostream& s, const alex::ATTrack& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}